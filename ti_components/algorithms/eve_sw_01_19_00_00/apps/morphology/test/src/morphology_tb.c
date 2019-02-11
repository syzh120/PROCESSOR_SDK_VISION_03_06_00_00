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


/*==========================================================================*/
/**
*  @file:      morphology_tb.c
*
*  @brief:     This file contains test code for morphology applet
*
*
*  @date:      December 2014
*
*  @description:
*    This file contains test code to validate the frame level applet for
*    morphology. It also checks the output against c reference
*    outputs and profiles the performance and computes the system
*    overheads.
**/
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>
#pragma RESET_MISRA ("required")

#include "xdais_types.h"

#include "evestarterware.h"
#include "alg_osal.h"
#include "eve_profile.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"

#include "morphology_config.h"
#include "imorphology_ti.h"
#include "vcop_grayscale_morphology_c.h"
#include "vcop_vec_bin_image_dilate_cross_c.h"
#include "vcop_vec_bin_image_dilate_mask_c.h"
#include "vcop_vec_bin_image_dilate_square_c.h"
#include "vcop_vec_bin_image_erode_cross_c.h"
#include "vcop_vec_bin_image_erode_mask_c.h"
#include "vcop_vec_bin_image_erode_square_c.h"
#include "vcop_vec_bin_image_morph_diff_c.h"


#define ENABLE_TRACES     (0U)
#define ENABLE_PROFILE    (1U)
#define COMPARE_REFERENCE (1U)

#define PACKED_PIXEL_COUNT       (8U)

#define MAX_CONFIG_LINE_SIZE     (300U)
#define MAX_FILE_NAME_SIZE       (200U)
#define MAX_PARAM_STRING_SIZE    (30U)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERROR_MSG() TEST_PRINTF("Error at line: %5d in file: %22s of function: %s\n",__LINE__,__FILE__,__FUNCTION__)
#define ALIGN(x,y)        (((x + y - 1)/y)*y)


#define DMEM_SIZE (16*1024U)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;


TIMemObject memObj_DMEM;
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else {
      memRec[i].base = (Void *) malloc( memRec[i].size);
    }
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
  }
  return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space != IALG_DARAM0) {
        free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;


char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(sMorphology_Config* params)
{
  uint16_t i;

  strcpy((char *)params->testCaseName, "GrayscaleMorphology_Dilation_Rect");
  strcpy((char *)params->inImage, "");
  strcpy((char *)params->outImage, "");
  strcpy((char *)params->desc, "");
  params->performanceTestcase = 1;

  params->inImageType    = MORPHOLOGY_TI_GRAYSCALE_IMAGE;

  params->morphologyMode = MORPHOLOGY_TI_DILATE;
  params->seShape        = MORPHOLOGY_TI_RECT_SE;

  params->srcWidth       = 768;
  params->srcPitch       = 768;
  params->srcHeight      = 512;

  params->seWidth        = 3;
  params->seHeight       = 3;
  for ( i = 0; i < MAX_COEFFICIENT_SIZE; i++)
  {
    params->seCoefficient[i] = 1;
  }
}

char* getOperationName(MORPHOLOGY_TI_Operation operation,
                              MORPHOLOGY_TI_StructuringElementShape seShape,
                              MORPHOLOGY_TI_ImageType imageType,
                              char* name)
{
  switch(imageType)
  {
    case MORPHOLOGY_TI_BINARY_IMAGE:
        strcpy(name, "Binary   ");
        break;
    case MORPHOLOGY_TI_GRAYSCALE_IMAGE:
        strcpy(name, "Grayscale");
        break;
  }

  switch(operation)
  {
    case MORPHOLOGY_TI_DILATE:
        strcat(name, " Dilation");
        break;
    case MORPHOLOGY_TI_ERODE:
        strcat(name, " Erosion");
        break;
    case MORPHOLOGY_TI_OPEN:
        strcat(name, " Opening");
        break;
    case MORPHOLOGY_TI_CLOSE:
        strcat(name, " Closing");
        break;
    case MORPHOLOGY_TI_TOPHAT:
        strcat(name, " TopHat ");
        break;
    case MORPHOLOGY_TI_BOTTOMHAT:
        strcat(name, " BotHat ");
        break;
    case MORPHOLOGY_TI_GRADIENT:
        strcat(name, " Gradient");
        break;
  }

  switch(seShape)
  {
    case MORPHOLOGY_TI_CUSTOM_SE:
        strcat(name, ": Custom SE");
        break;
    case MORPHOLOGY_TI_RECT_SE:
        strcat(name, ": Rect SE");
        break;
    case MORPHOLOGY_TI_CROSS_SE:
        strcat(name, ": Cross SE");
        break;
  }

  return name;
}


void vcop_grayscale_morph_mask_cn(
    uint16_t         blk_w,        // width of input block, in elements
    uint16_t         line_ofst,    // offset between input lines, in elements
    uint16_t         blk_h,        // height of input block
    uint8_t         *data_ptr,     // input data pointer
    uint16_t         se_w,         // width of structuring element block, in elements
    uint16_t         se_h,         // height of structuring element block
    uint8_t         *se_ptr,       // structuring element data pointer
    uint8_t         *refl_se_ptr,  // Reflected structuring element data pointer
    uint8_t         *scratch1_ptr, // scratch 1 pointer
    uint8_t         *scratch2_ptr, // scratch 2 pointer
    uint8_t         *output_ptr,   // output data pointer
    MORPHOLOGY_TI_Operation operation)  // Grayscale Morphology Operation
{
  switch(operation)
  {
    case MORPHOLOGY_TI_DILATE:
        vcop_grayscale_dilate_mask_cn(blk_w, line_ofst, blk_h,
            data_ptr, se_w, se_h, refl_se_ptr, output_ptr);
        break;

    case MORPHOLOGY_TI_ERODE:
        vcop_grayscale_erode_mask_cn(blk_w, line_ofst, blk_h,
            data_ptr, se_w, se_h, se_ptr, output_ptr);
        break;

    case MORPHOLOGY_TI_OPEN:
        vcop_grayscale_open_mask_cn(blk_w, line_ofst, blk_h,
            data_ptr, se_w, se_h, se_ptr, refl_se_ptr, scratch1_ptr, output_ptr);
        break;

    case MORPHOLOGY_TI_CLOSE:
      vcop_grayscale_close_mask_cn(blk_w, line_ofst, blk_h,
          data_ptr, se_w, se_h, se_ptr, refl_se_ptr, scratch1_ptr, output_ptr);
        break;

    case MORPHOLOGY_TI_TOPHAT:
      vcop_grayscale_tophat_mask_cn(blk_w, line_ofst, blk_h,
          data_ptr, se_w, se_h, se_ptr, refl_se_ptr, scratch1_ptr, output_ptr);
        break;

    case MORPHOLOGY_TI_BOTTOMHAT:
      vcop_grayscale_bottomhat_mask_cn(blk_w, line_ofst, blk_h,
          data_ptr, se_w, se_h, se_ptr, refl_se_ptr, scratch1_ptr, output_ptr);
        break;

    case MORPHOLOGY_TI_GRADIENT:
      vcop_grayscale_morph_grad_mask_cn(blk_w, line_ofst, blk_h,
          data_ptr, se_w, se_h, se_ptr, refl_se_ptr, scratch1_ptr, scratch2_ptr, output_ptr);
        break;
  }
}

/* TO BE REMOVED */
#define vcop_vec_bin_morp_diff_cn()

void vcop_binary_morph_mask_cn(
    uint16_t         blk_w,        // width of input block, in elements
    uint16_t         line_ofst,    // offset between input lines, in elements
    uint16_t         blk_h,        // height of input block
    uint32_t        *data_ptr,     // input data pointer
    const char      *se_ptr,       // structuring element data pointer
    const char      *refl_se_ptr,  // Reflected structuring element data pointer
    uint32_t        *scratch1_ptr, // scratch 1 pointer
    uint32_t        *scratch2_ptr, // scratch 2 pointer
    uint32_t        *output_ptr,   // output data pointer
    MORPHOLOGY_TI_Operation operation)  // Grayscale Morphology Operation
{
  uint8_t    i;
  char seComp_ptr[MORPHOLOGY_TI_BINARY_SE_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT];


  for(i = 0; i < MORPHOLOGY_TI_BINARY_SE_WIDTH*MORPHOLOGY_TI_BINARY_SE_HEIGHT; i++)
  {
    if(se_ptr[i] != 0)
    {
      seComp_ptr[i] = 0;
    } else
    {
      seComp_ptr[i] = 1;
    }
  }


  switch(operation)
  {
    case MORPHOLOGY_TI_DILATE:
        vcop_vec_bin_image_dilate_mask_cn(data_ptr, output_ptr, refl_se_ptr, blk_w,
            line_ofst, blk_h);
        break;

    case MORPHOLOGY_TI_ERODE:
        vcop_vec_bin_image_erode_mask_cn(data_ptr, output_ptr, seComp_ptr, blk_w,
            line_ofst, blk_h);
        break;

    case MORPHOLOGY_TI_OPEN:
        vcop_vec_bin_image_erode_mask_cn(data_ptr, scratch1_ptr, seComp_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_dilate_mask_cn(scratch1_ptr, output_ptr, refl_se_ptr, blk_w,
            line_ofst, blk_h);
        break;

    case MORPHOLOGY_TI_CLOSE:
        vcop_vec_bin_image_dilate_mask_cn(data_ptr, scratch1_ptr, refl_se_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_erode_mask_cn(scratch1_ptr, output_ptr, seComp_ptr, blk_w,
            line_ofst, blk_h);
        break;

    case MORPHOLOGY_TI_TOPHAT:
        vcop_vec_bin_image_erode_mask_cn(data_ptr, output_ptr, seComp_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_dilate_mask_cn(output_ptr, scratch1_ptr, refl_se_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_morph_diff_cn(blk_w, line_ofst, blk_h,
            (uint32_t *)((uint8_t *)data_ptr + 2*line_ofst/8), 2, scratch1_ptr, 0, output_ptr);
        break;

    case MORPHOLOGY_TI_BOTTOMHAT:
        vcop_vec_bin_image_dilate_mask_cn(data_ptr, output_ptr, refl_se_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_erode_mask_cn(output_ptr, scratch1_ptr, seComp_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_morph_diff_cn(blk_w, line_ofst, blk_h, scratch1_ptr, 0,
            (uint32_t *)((uint8_t *)data_ptr + 2*line_ofst/8), 2, output_ptr);
        break;

    case MORPHOLOGY_TI_GRADIENT:
        vcop_vec_bin_image_dilate_mask_cn(data_ptr, scratch1_ptr, refl_se_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_erode_mask_cn(data_ptr, scratch2_ptr, seComp_ptr, blk_w,
            line_ofst, blk_h);

        vcop_vec_bin_image_morph_diff_cn(blk_w, line_ofst, blk_h,
            scratch1_ptr, 0, scratch2_ptr, 0, output_ptr);
        break;
  }
}


int32_t morphologyTest(sMorphology_Config* params)
{
#if (ENABLE_PROFILE)
  uint64_t     profile_tsc, profile_sctm;
#endif
  uint8_t     *input = NULL, *output = NULL, *refOutput = NULL, *scratchBuf1 = NULL, *scratchBuf2 = NULL;
  uint8_t     *seReflBuf = NULL, *seBuf = NULL, bitMask, pixelsPerElem;
  int32_t      i, j, numMemRec, status, fail = 0, outPadX, outPadY, outPadBitX, dstPitch;
  TI_FILE     *fp;
  char         desc[30];
  IALG_MemRec *memRec;
  char        *statusStr = NULL;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *    handle;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  MORPHOLOGY_TI_CreateParams   createParams;

  MORPHOLOGY_TI_InArgs  inArgs;
  MORPHOLOGY_TI_OutArgs outArgs;

  IVISION_InBufs        inBufs;
  IVISION_OutBufs       outBufs;

  IVISION_BufDesc    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[MORPHOLOGY_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc    outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[MORPHOLOGY_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(MORPHOLOGY_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(MORPHOLOGY_TI_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if (ENABLE_PROFILE)
  profiler_init();
#endif

  /*-----------------------------------------------------------------
  Set buffer descriptor pointers array base
  -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs  = MORPHOLOGY_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs = MORPHOLOGY_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < MORPHOLOGY_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]  = &inBufDesc[i];
  }

  for(i = 0 ; i < MORPHOLOGY_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i] = &outBufDesc[i];
  }

  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.srcType                     = params->inImageType;
  createParams.visionParams.algParams.size = sizeof(MORPHOLOGY_TI_CreateParams);
  createParams.visionParams.cacheWriteBack = NULL;

#if (ENABLE_PROFILE)
  profiler_initStack(profiler_getSP());
  profiler_start();
#endif

  /*-----------------------------------------------------------------
  Query algorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/
  numMemRec = MORPHOLOGY_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));

  status = MORPHOLOGY_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Morphology Applet Create Done\n");
#endif

  /*-----------------------------------------------------------------
  Allocate memory for all the mem records
  Application has to implement the below function
  Refer the example implementation below in this file
  -----------------------------------------------------------------*/
  status = TestApp_AllocMemRecords(memRec, numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = MORPHOLOGY_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
                                                   memRec,
                                                   NULL,
                                                   (IALG_Params *)(&createParams));

#if (ENABLE_PROFILE)
  profiler_end_print(0);
/*  profile_create_tsc = gTest_TI_profileTsc;  */
#endif

  handle = (IM_Fxns *) memRec[0].base;

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }

#if ENABLE_TRACES
  TEST_PRINTF("Morphology Applet Init Done\n");
#endif

  inArgs.morphologyOperation = params->morphologyMode;
  inArgs.seShape             = params->seShape;
  inArgs.seWidth             = params->seWidth;
  inArgs.seHeight            = params->seHeight;

  /*-----------------------------------------------------------------
  Calculate padx and pady
  -----------------------------------------------------------------*/
  outPadX = ((params->morphologyMode == MORPHOLOGY_TI_DILATE) ||
             (params->morphologyMode == MORPHOLOGY_TI_ERODE)  ||
             (params->morphologyMode == MORPHOLOGY_TI_GRADIENT)) ? (params->seWidth-1) : 2*(params->seWidth-1);
  outPadY = ((params->morphologyMode == MORPHOLOGY_TI_DILATE) ||
             (params->morphologyMode == MORPHOLOGY_TI_ERODE)  ||
             (params->morphologyMode == MORPHOLOGY_TI_GRADIENT)) ? (params->seHeight-1) : 2*(params->seHeight-1);
  if( createParams.srcType == MORPHOLOGY_TI_BINARY_IMAGE)
  {
    outPadX = 0; /*as difference is in terms of bits and not bytes. */
    pixelsPerElem = PACKED_PIXEL_COUNT;
  }
  else
  {
    pixelsPerElem = 1;
  }

  /*-----------------------------------------------------------------
  Set buffer descriptor
  -----------------------------------------------------------------*/
  /*-----------------------------------------------------------------
  Input buffer
  -----------------------------------------------------------------*/
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].numPlanes = 1;
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].frameROI.topLeft.x = 0;
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].frameROI.topLeft.y = 0;
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].frameROI.width = params->srcWidth;
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].frameROI.height = params->srcHeight;

  /* Input buffer should have worst case padding of 64 + outPadY + 1 lines. The 1 line of padding at the end of buffer
         is to account for the extra read of last line as read will be ALIGN_TO_64(params->srcWidth). */
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].width  = params->srcPitch;
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].height = params->srcHeight + 64 + outPadY + 1;
  inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].buf =
       malloc(inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].width *
              inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER].bufPlanes[0].height);

  /*-----------------------------------------------------------------
  Structuring Element buffer
  -----------------------------------------------------------------*/
  if( params->seShape == MORPHOLOGY_TI_CUSTOM_SE )
  {
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].numPlanes = 1;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].frameROI.topLeft.x = 0;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].frameROI.topLeft.y = 0;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].width = params->seWidth;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].height = params->seHeight;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].frameROI.width = params->seWidth;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].frameROI.height = params->seHeight;
    inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].buf =
         malloc(inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].width *
                inBufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER].bufPlanes[0].height);

    inBufs.numBufs   = MORPHOLOGY_TI_BUFDESC_IN_TOTAL;
  } else
  {
    inBufs.numBufs   = MORPHOLOGY_TI_BUFDESC_IN_TOTAL - 1;
  }

  /*-----------------------------------------------------------------
  Output buffer
  -----------------------------------------------------------------*/
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].numPlanes = 1;
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].frameROI.topLeft.x = 0;
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].frameROI.topLeft.y = 0;
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].frameROI.width  = params->srcWidth  - outPadX;
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].frameROI.height = params->srcHeight - outPadY;
  if( createParams.srcType == MORPHOLOGY_TI_BINARY_IMAGE)
  {
    /* For Binary morphology: params->srcWidth  - outPadX is the minimum dstPitch supported.
            dstPitch can be any value higher than that. */
    dstPitch = params->srcWidth - outPadX;
  }
  else
  {
    /* For Grayscale morphology: the output buffer pitch should be a multiple of 64. */
    dstPitch = ALIGN((params->srcWidth  - outPadX), 64);
  }
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].width  = dstPitch;
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].height = params->srcHeight + 64;
  outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].buf =
       malloc(outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].width *
              outBufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER].bufPlanes[0].height);


  /*-----------------------------------------------------------------
  Allocate Buffers
  -----------------------------------------------------------------*/
  input  = (uint8_t *) inBufs.bufDesc[MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf;
  output = (uint8_t *)outBufs.bufDesc[MORPHOLOGY_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf;

  if( params->seShape == MORPHOLOGY_TI_CUSTOM_SE )
  {
    seBuf = (uint8_t *)inBufs.bufDesc[MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER]->bufPlanes[0].buf;
  } else
  {
    seBuf = (uint8_t *)malloc(params->seWidth * params->seHeight);
  }

  seReflBuf   = (uint8_t *)malloc(params->seWidth  * params->seHeight);
  refOutput   = (uint8_t *)malloc(params->srcPitch * params->srcHeight);
  scratchBuf1 = (uint8_t *)malloc(params->srcPitch * params->srcHeight);
  scratchBuf2 = (uint8_t *)malloc(params->srcPitch * params->srcHeight);

  /*-----------------------------------------------------------------
        Open Input File. If non existant, fill input with data.
        -----------------------------------------------------------------*/
  /*-----------------------------------------------------------------
        The input (binary packed image) for binary morphology is assumed to be in memory
        in the following format at ascending Bit locations:
        P7 P6 ..... P0 P15 P14 ... P8 .....
        where Pi is the pixel of image at location i along horizontal direction.
        It is like an inverted byte packed format.
        -----------------------------------------------------------------*/
  fp = FOPEN((char *)params->inImage, "rb");
  if(fp == NULL)
  {
    srand(1);
    for(i = 0; i < params->srcPitch * params->srcHeight; i++)
    {
       input[i] = rand() % 256;
    }
  } else
  {
      FREAD(input, 1, params->srcPitch * params->srcHeight, fp);
      FCLOSE(fp);
  }

  /*-----------------------------------------------------------------
        Fill output and reference Output buffers with 0.
        -----------------------------------------------------------------*/
  memset(output,    0, dstPitch         * params->srcHeight);
  memset(refOutput, 0, params->srcPitch * params->srcHeight);


  /*-----------------------------------------------------------------
        Fill Structuring Element buffer.
        -----------------------------------------------------------------*/
  switch ( params->seShape)
  {
    case MORPHOLOGY_TI_CUSTOM_SE:
      memset(seBuf, 0, params->seWidth*params->seHeight);

      for(i = 0; i < params->seHeight * params->seWidth; i++)
      {
          seBuf[i] = params->seCoefficient[i];
      }

    break;
    case MORPHOLOGY_TI_RECT_SE:
      memset(seBuf, 1, params->seWidth * params->seHeight);

    break;
    case MORPHOLOGY_TI_CROSS_SE:
      memset(seBuf, 0, params->seWidth * params->seHeight);

      for(i = 0; i < params->seHeight; i++)
      {
        seBuf[i*params->seWidth + (params->seWidth-1)/2] = 1;
      }
      for(i = 0; i < params->seWidth; i++)
      {
        seBuf[((params->seHeight-1)/2)*params->seWidth + i] = 1;
      }

    break;
  }

  for(i = 0; i < params->seHeight * params->seWidth; i++)
  {
      seReflBuf[i] = seBuf[(params->seHeight * params->seWidth - 1) - i];
  }


  /*-----------------------------------------------------------------
        Process.
        -----------------------------------------------------------------*/
#if ENABLE_TRACES
  TEST_PRINTF("Processing start \n");
#endif
#if (ENABLE_PROFILE)
  profiler_start();
#endif

  status = handle->ivision->algProcess((IVISION_Handle)handle,
                                        &inBufs,
                                        &outBufs,
                                       (IVISION_InArgs *)&inArgs,
                                       (IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
  profiler_end_print(1);

  profile_tsc  = gTest_TI_profileTsc;
  profile_sctm = gTest_TI_profileSctm[0];
#endif

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Processing End\n");
#endif

  /*-----------------------------------------------------------------
        Dump output image.
        -----------------------------------------------------------------*/
  fp = FOPEN((char *)params->outImage, "wb");

  if(fp != NULL)
  {
      FWRITE(output, 1, params->srcPitch * params->srcHeight, fp);
      FCLOSE(fp);
  }

#ifdef COMPARE_REFERENCE
  /*---------------------------------------------------------------------*/
  /*  Call the natural C implementation for grayscale morphology funcs.  */
  /*---------------------------------------------------------------------*/
  if( createParams.srcType == MORPHOLOGY_TI_GRAYSCALE_IMAGE)
  {
    vcop_grayscale_morph_mask_cn(params->srcWidth,
                                 params->srcPitch,
                                 params->srcHeight,
                                 input,
                                 params->seWidth,
                                 params->seHeight,
                                 seBuf,
                                 seReflBuf,
                                 scratchBuf1,
                                 scratchBuf2,
                                 refOutput,
                                 (MORPHOLOGY_TI_Operation)params->morphologyMode);
  }
  else
  {
    vcop_binary_morph_mask_cn(params->srcWidth * PACKED_PIXEL_COUNT,
                              params->srcPitch * PACKED_PIXEL_COUNT,
                              params->srcHeight,
                              (uint32_t *)  input,
                              (const char *)seBuf,
                              (const char *)seReflBuf,
                              (uint32_t *)  scratchBuf1,
                              (uint32_t *)  scratchBuf2,
                              (uint32_t *)  refOutput,
                              (MORPHOLOGY_TI_Operation)params->morphologyMode);

    outPadBitX = ((params->morphologyMode == MORPHOLOGY_TI_DILATE) ||
                  (params->morphologyMode == MORPHOLOGY_TI_ERODE)  ||
                  (params->morphologyMode == MORPHOLOGY_TI_GRADIENT)) ? (params->seHeight-1) : 2*(params->seHeight-1);

    /* Zeroing the last few (2 or 4) invalid bits. */
    if(outPadBitX == 2)
    {
        bitMask = 0x3f;
    }
    else
    {
        bitMask = 0x0f;
    }

    /* Masking out end bits of last byte of image. Since the byte is inverted, we need to mask the top 2 or 4 bits of the byte. */
    /* The end bits of the last byte of every line should be masked out. */
    for(i = 0; i < (params->srcHeight - outPadY); i++)
    {
      output[   i*dstPitch         + (params->srcWidth - outPadX - 1)] &= bitMask;
      refOutput[i*params->srcPitch + (params->srcWidth - outPadX - 1)] &= bitMask;
    }
  }

  fail = 0;

  /* The kernel will generate output with a pitch of dstPitch whereas the
         Natural C will generate output with a pitch of srcPitch. */
  for(i = 0; i < (params->srcHeight - outPadY); i++)
  {
    for(j = 0; j < (params->srcWidth - outPadX); j++)
    {
      if(output[i*dstPitch + j] != refOutput[i*params->srcPitch + j])
      {
        fail = 1;
        TEST_PRINTF("row:%d, col:%d, out:%u, EOut:%u \n",
                    i, j, output[i*dstPitch+j], refOutput[i*params->srcPitch+j]);
        break;
      }
    }
  }
#endif

  statusStr = fail ? "FAILED" : "PASSED";

  profiler_printStatus(fail);

#if (ENABLE_PROFILE)
  TEST_PRINTF("\n%-30s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s\n", \
          "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
          "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
#if (VCOP_HOST_EMULATION)
  profile_sctm = 1;
  profile_tsc = 1;
#endif
  TEST_PRINTF("%-30s %10s %10d %10d %10d %15lld %15.2f %20.2f %10.2f %16.2f    SE size = %dx%d, overhead=%d%%\n",
      getOperationName((MORPHOLOGY_TI_Operation)params->morphologyMode,
                       (MORPHOLOGY_TI_StructuringElementShape)params->seShape,
                       (MORPHOLOGY_TI_ImageType)params->inImageType,
                        desc),
      statusStr,
      params->srcWidth * pixelsPerElem,
      params->srcHeight,
      1,
      profile_tsc,
      profile_tsc/1000000.0,
      30*(profile_tsc/1000000.0),
      profile_tsc/((float)params->srcWidth * pixelsPerElem * params->srcHeight),
      profile_tsc/500000.0,
      params->seHeight,
      params->seWidth,
      ((profile_tsc - profile_sctm)*100)/profile_sctm);
#endif

  fflush(stdout);

EXIT_LOOP:

  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);

  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec, numMemRec);
  if(status != IALG_EOK) {
    PRINT_ERROR_MSG();
  }

  if ( memRec != NULL ) {
    free(memRec);
  }
  if ( input != NULL ) {
    free(input);
  }
  if (output != NULL) {
    free(output);
  }
  if ( refOutput != NULL ) {
    free(refOutput);
  }
  if (scratchBuf1 != NULL) {
    free(scratchBuf1);
  }
  if (scratchBuf2 != NULL) {
    free(scratchBuf2);
  }
  if (seBuf != NULL) {
    free(seBuf);
  }
  if (seReflBuf != NULL) {
    free(seReflBuf);
  }

#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif

  return status;
}


int main(int argc, char *argv[])
{
  TI_FILE *fp;
  char     configFile[FILE_NAME_SIZE] = {0};
  char     configLine[MAX_CONFIG_LINE_SIZE];
  char     configParam[MAX_PARAM_STRING_SIZE];
  int8_t  *LinePtr;
  int32_t  lineNum = -1, config_cmd, status = 0;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  report_printAppletInfo((int8_t *)"MORPHOLOGY_TI_VISION");

  while ( 1 )
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
    {
      break;
    }
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);

    if(config_cmd == 0)
    {
      TEST_PRINTF("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFile);

      TEST_PRINTF("\n Processing config file %s !\n", configFile);

      fillDefaultConfig(&gConfig_morphology);

      status = readparamfile(configFile, &gsTokenMap_morphology[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)gConfig_morphology.testCaseName, (int8_t *)gConfig_morphology.desc,
                            gConfig_morphology.performanceTestcase);
      printparams(&gsTokenMap_morphology[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_morphology),
                            sizeof(sMorphology_Config));

      /* Validate the applet */
      status = morphologyTest(&gConfig_morphology);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      TEST_PRINTF(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }

  }

  FCLOSE(fp);

#if VCOP_HOST_EMULATION
    printf("Press any key to continue ...\n");
    scanf("%c", configFile);
#endif

  return status;
}

