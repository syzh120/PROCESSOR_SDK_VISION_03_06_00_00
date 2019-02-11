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
 *  @file       yuv_padding_alg_int.h
 *
 *  @brief      This file defines the functions for yuv padding
 *  @date   05 Mar 2014
 */


#ifndef YUV_PADDING_ALG_INT_H
#define YUV_PADDING_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
/*#pragma CHECK_MISRA ("none")*/
#include <xdais_types.h>
/*#pragma RESET_MISRA ("required")*/

#include "iyuv_padding_ti.h"
#include "yuv_padding_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for image pyra,id application
*/
typedef enum
{
  /* Memory records for handle */
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for graph */
  GRAPH_OBJ_MEMREC,
  GRAPH_OBJ_INT_MEMREC,
  GRAPH_SCRATCH_MEMREC,
  GRAPH_CONTEXT_MEMREC,
  GRAPH_ARGS_MEMREC,
  GRAPH_YUV_LINE_INT_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;


/**
  @struct YUV_PADDING_TI_Obj
  @brief  This structure is the main handle of
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
*/
typedef struct
{
  const IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  graphMem;
  YUV_PADDING_TI_CreateParams createParams ;
} YUV_PADDING_TI_Obj;

typedef YUV_PADDING_TI_Obj * YUV_PADDING_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
XDAS_Int32 YUV_PADDING_TI_numAlloc(void);
XDAS_Int32 YUV_PADDING_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec *memRec);
XDAS_Int32 YUV_PADDING_TI_init(IALG_Handle handle,
  const IALG_MemRec *memRec, IALG_Handle parent, const IALG_Params *params);
XDAS_Void  YUV_PADDING_TI_activate(IALG_Handle handle);
XDAS_Void  YUV_PADDING_TI_deactivate(IALG_Handle handle);
XDAS_Int32 YUV_PADDING_TI_free(IALG_Handle handle, IALG_MemRec *memRec);

XDAS_Int32 YUV_PADDING_TI_control(IVISION_Handle Handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

XDAS_Int32 YUV_PADDING_TI_process(IVISION_Handle Handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 YUV_PADDING_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* YUV_PADDING_ALG_INT_H */

