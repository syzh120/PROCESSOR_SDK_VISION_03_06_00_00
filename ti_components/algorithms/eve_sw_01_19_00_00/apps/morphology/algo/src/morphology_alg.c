/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/**
*  @file       morphology_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for hough for lines applet
*  @version     0.0 (Dec 2013) : Base version.
*/

/* #pragma CHECK_MISRA ("none") */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/* #pragma RESET_MISRA ("required") */

#include "morphology_alg_int.h"
#include "grayscale_morphology.h"
#include "binary_morphology.h"
#include "edma_utils_memcpy.h"

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns MORPHOLOGY_TI_VISION_FXNS =
{
  {
      &MORPHOLOGY_TI_activate, /* module ID */
      &MORPHOLOGY_TI_activate,    /* activate */
      &MORPHOLOGY_TI_alloc,       /* algAlloc */
      NULL,                      /* control (not suported) */
      &MORPHOLOGY_TI_deactivate,  /* deactivate */
      &MORPHOLOGY_TI_free,        /* free */
      &MORPHOLOGY_TI_init,        /* init */
      NULL,                      /* moved (not suported) */
      &MORPHOLOGY_TI_numAlloc     /* algNumAlloc  */
  },
  &MORPHOLOGY_TI_process,
  &MORPHOLOGY_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns MORPHOLOGY_TI_IRES = {
  NULL,
  NULL,                                     /*getResourceDescriptors, */
  NULL,                                     /*numResourceDescriptors */
  NULL,                                     /*initResources,  */
  NULL,                                     /*reinitResources, */
  NULL,                                     /*deinitResources, */
  NULL,                                     /*activateResource,*/
  NULL,                                     /*activateAllResources, */
  NULL,                                     /*deactivateResource,   */
  NULL                                      /*deactivateAllResources */
};

/**
* Other exposed functions
*/
int32_t MORPHOLOGY_TI_numAlloc(void)
{
  return NUM_MEMRECS;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t MORPHOLOGY_TI_alloc(const IALG_Params *params,
                                       IALG_Fxns **parentFxns,
                                       IALG_MemRec       memRec[])
{
  /*-----------------------------------------------------------------------------*/
  /*  For memory record ALG_HANDLE_INT_MEMREC ,                                    */
  /*  which is a scratch buffer in IALG_DARAM0 (DMEM), it must be preceded    */
  /*  by a persistent memory record in IALG_EXTERNAL of the same size.         */
  /*  This persistent record will be used to backup the following scratch             */
  /*  memory record during context saving when MORPHOLOGY_TI_deactivate */
  /*  is called. Likewise when MORPHOLOGY_TI_activate it called,                      */
  /*  the content of the persistent memory record is copied back to the            */
  /*  scratch memory record in IALG_DARAM0 (DMEM).                                    */
  /*-----------------------------------------------------------------------------*/
  memRec[ALG_HANDLE_MEMREC].size          = sizeof(MORPHOLOGY_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment     = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(MORPHOLOGY_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

  return (IALG_EOK);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t MORPHOLOGY_TI_init(IALG_Handle        handle,
                                     const IALG_MemRec  memRec[],
                                     IALG_Handle        parent,
                                     const IALG_Params *params)
{

  MORPHOLOGY_TI_Handle        algHandle    = (MORPHOLOGY_TI_Handle)(void *)memRec[ALG_HANDLE_MEMREC].base;
  const MORPHOLOGY_TI_CreateParams *createParams = (const MORPHOLOGY_TI_CreateParams *)(const void *)params;
  int32_t                     status = IALG_EOK;


  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec, memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  algHandle->ivision = &MORPHOLOGY_TI_VISION_FXNS;
  algHandle->srcType = createParams->srcType;

  if(algHandle->srcType == MORPHOLOGY_TI_GRAYSCALE_IMAGE)
  {
    Grayscale_Morphology_Init(&algHandle->grayscaleMorphologyHandle);
  }
  else
  {
    Binary_Morphology_Init(&algHandle->binaryMorphologyHandle);
  }

  /*-----------------------------------------------------------------------*/
  /* State to indicate that internal context of algorithm is not active    */
  /*-----------------------------------------------------------------------*/
  algHandle->algState = ALG_NOT_ACTIVE;

  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t MORPHOLOGY_TI_control(IVISION_Handle     handle,
                                          IALG_Cmd           cmd,
                                          const IALG_Params *inParams,
                                          IALG_Params       *outParams)
{
  return (IALG_EOK);
}

/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
/* CHECK_MISRA("-16.7")  -> Disable rule 16.7 */
/* Pointer parameter inBufs and outBufs are not used to modify the addressed object but is not declared as a pointer to const */
/* Deviation is allowed because this function is of type IVISION_Fxns : algProcess in order to be ASSIGNED IVISION_Fxns */
int32_t MORPHOLOGY_TI_process(IVISION_Handle   handle,
                                           IVISION_InBufs  *inBufs,
                                           IVISION_OutBufs *outBufs,
                                           IVISION_InArgs  *inArgs,
                                           IVISION_OutArgs *outArgs)
{
/*RESET_MISRA("16.7")  -> Reset rule 16.7  */
  MORPHOLOGY_TI_Handle  algHandle = (MORPHOLOGY_TI_Handle)(void *)handle;
  MORPHOLOGY_TI_Handle  intAlgHandle;
  MORPHOLOGY_TI_InArgs *morphologyInArgs = (MORPHOLOGY_TI_InArgs *)(void *)inArgs;
  IVISION_BufDesc    *(*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    *(*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_TOTAL];
  int32_t               status = IALG_EOK;
  uint8_t              *seBuf, *inBuf, *outBuf, outPadY;

  inBufDesc  = (IVISION_BufDesc *(*)[MORPHOLOGY_TI_BUFDESC_IN_TOTAL])(void *)inBufs->bufDesc;
  outBufDesc = (IVISION_BufDesc *(*)[MORPHOLOGY_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

  /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
  /* GOTO is used at error check to jump to end of function, to exit.   */
  /*-----------------------------------------------------------------------*/
  /* Error check                                                */
  /*-----------------------------------------------------------------------*/
  if ( inArgs->size != sizeof(MORPHOLOGY_TI_InArgs))
  {
    status = IALG_EFAIL;
    goto Exit;
  }

  if ( morphologyInArgs->seShape >= MORPHOLOGY_TI_SE_SHAPE_MAX )
  {
    status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_SHAPE;
    goto Exit;
  }

  if ( algHandle->srcType == MORPHOLOGY_TI_GRAYSCALE_IMAGE)
  {
    if ( morphologyInArgs->seWidth > MORPHOLOGY_TI_MAX_GRAYSCALE_SE_WIDTH )
    {
      status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_DIMENSION;
      goto Exit;
    }

    if ( morphologyInArgs->seHeight > MORPHOLOGY_TI_MAX_GRAYSCALE_SE_HEIGHT )
    {
      status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_DIMENSION;
      goto Exit;
    }
  }
  else
  {
    if ( morphologyInArgs->seWidth != MORPHOLOGY_TI_BINARY_SE_WIDTH )
    {
      status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_DIMENSION;
      goto Exit;
    }

    if ( morphologyInArgs->seHeight != MORPHOLOGY_TI_BINARY_SE_HEIGHT )
    {
      status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_DIMENSION;
      goto Exit;
    }
  }

  if ( morphologyInArgs->morphologyOperation >= MORPHOLOGY_TI_OPERATION_MAX )
  {
    status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_OPERATION;
    goto Exit;
  }

  if ( algHandle->srcType >= MORPHOLOGY_TI_IMAGE_TYPES_MAX )
  {
    status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_IMAGE_TYPE;
    goto Exit;
  }

  if ( morphologyInArgs->seShape == MORPHOLOGY_TI_CUSTOM_SE )
  {
    if ( inBufs->numBufs != 2 )
    {
      status = IVISION_ERRORTYPE_NUM_INBUF_EXCEEDED;
      goto Exit;
    }
  } else
  {
    if ( inBufs->numBufs != 1 )
    {
      status = IVISION_ERRORTYPE_NUM_INBUF_EXCEEDED;
      goto Exit;
    }
  }

  /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
  /* Redundant parentheses are added for code readability and is waived.   */

  outPadY = ((morphologyInArgs->morphologyOperation == MORPHOLOGY_TI_DILATE) ||
             (morphologyInArgs->morphologyOperation == MORPHOLOGY_TI_ERODE)  ||
             (morphologyInArgs->morphologyOperation == MORPHOLOGY_TI_GRADIENT))
             ? (morphologyInArgs->seHeight - 1) : 2*(morphologyInArgs->seHeight - 1);

  if ( (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height <
      ((*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height + 64U + outPadY + 1U))
  {
    status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_INPUTBUF_DIMENSION;
    goto Exit;
  }

  if ( (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].height <
      ((*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.height + 64U + outPadY))
  {
    status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_OUTPUTBUF_DIMENSION;
    goto Exit;
  }

  if ( algHandle->srcType == MORPHOLOGY_TI_GRAYSCALE_IMAGE)
  {
    if ( ((*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width % 64U) != 0 )
    {
      status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_OUTPUTBUF_DIMENSION;
      goto Exit;
    }
  }
  else
  {
    if ( (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width
                                                                > BIN_MORPH_MAX_IMAGE_WIDTH )
    {
      status = MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_INPUTBUF_DIMENSION;
      goto Exit;
    }
  }
  /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  MORPHOLOGY_TI_activate((IALG_Handle)(void *)handle);

  intAlgHandle = (MORPHOLOGY_TI_Handle)(void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;

  if ( morphologyInArgs->seShape == MORPHOLOGY_TI_CUSTOM_SE )
  {
    seBuf = (uint8_t *)(*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER]->bufPlanes[0].buf;
  } else
  {
    seBuf = NULL;
  }

  inBuf = *(uint8_t (*)[])(*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf +
                         ((*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.y *
                          (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width) +
                          (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.topLeft.x;

  outBuf = *(uint8_t (*)[])(*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf +
                          ((*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.topLeft.y *
                           (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width) +
                           (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.topLeft.x;


  if( intAlgHandle->srcType == MORPHOLOGY_TI_GRAYSCALE_IMAGE )
  {
    Grayscale_Morphology_Process(&intAlgHandle->grayscaleMorphologyHandle,
                               inBuf,
                               (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width,
                               (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height,
                               (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width,
                               outBuf,
                               (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.width,
                               (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.height,
                               (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width,
                               seBuf,
                               morphologyInArgs->seWidth,
                               morphologyInArgs->seHeight,
                               morphologyInArgs->seShape,
                               morphologyInArgs->morphologyOperation);
  } else
  {
    Binary_Morphology_Process(&intAlgHandle->binaryMorphologyHandle,
                               inBuf,
                               (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width,
                               (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height,
                               (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width,
                               outBuf,
                               (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.width,
                               (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].frameROI.height,
                               (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width,
                               seBuf,
                               morphologyInArgs->seShape,
                               morphologyInArgs->morphologyOperation);
  }


Exit:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  outArgs->inFreeBufIDs[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER] = (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufferId ;
  outArgs->inFreeBufIDs[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER]    = (*inBufDesc)[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER]->bufferId ;
  outArgs->inFreeBufIDs[MORPHOLOGY_TI_BUFDESC_IN_TOTAL]       = 0 ;

  outArgs->outFreeBufIDs[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]    = (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufferId ;
  outArgs->outFreeBufIDs[MORPHOLOGY_TI_BUFDESC_OUT_TOTAL]     = 0 ;

  (*outBufDesc)[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].accessMask = IVISION_ACCESSMODE_HWA;

  /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

  return status;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
void  MORPHOLOGY_TI_activate(IALG_Handle handle)
{
  MORPHOLOGY_TI_Handle algHandle = (MORPHOLOGY_TI_Handle)(void *)handle;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[ALG_HANDLE_INT_MEMREC].base,
                        (const void *)algHandle->memRec[ALG_HANDLE_MEMREC].base,
                        (uint16_t)    algHandle->memRec[ALG_HANDLE_INT_MEMREC].size,
                        (uint16_t)1,
                        (int16_t) 0,
                        (int16_t) 0);

    algHandle->algState = ALG_ACTIVE;
  }

  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do de-activation of algorithm. All scratch memory*/
/* are stoed to external memory in this                                     */
/* Refer algDeActivate function for details in ialg.h file                  */
/*--------------------------------------------------------------------------*/
void  MORPHOLOGY_TI_deactivate(IALG_Handle handle)
{
  MORPHOLOGY_TI_Handle algHandle = (MORPHOLOGY_TI_Handle)(void *)handle;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_ACTIVE)
  {
    EDMA_UTILS_memcpy2D((void *)      algHandle->memRec[ALG_HANDLE_MEMREC].base,
                        (const void *)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base,
                        (uint16_t)    algHandle->memRec[ALG_HANDLE_INT_MEMREC].size,
                        (uint16_t)1,
                        (int16_t) 0,
                        (int16_t) 0);

    algHandle->algState = ALG_NOT_ACTIVE;
  }

  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
int32_t MORPHOLOGY_TI_free(IALG_Handle handle, IALG_MemRec memRec[])
{
  MORPHOLOGY_TI_Handle algHandle = (MORPHOLOGY_TI_Handle)(void *)handle;

  memcpy(memRec, algHandle->memRec, sizeof(IALG_MemRec)*algHandle->numMemRecs);

  if(algHandle->srcType == MORPHOLOGY_TI_GRAYSCALE_IMAGE)
  {
    Grayscale_Morphology_Deinit(&algHandle->grayscaleMorphologyHandle);
  }
  else
  {
    Binary_Morphology_Deinit(&algHandle->binaryMorphologyHandle);
  }

  return (IALG_EOK);
}

