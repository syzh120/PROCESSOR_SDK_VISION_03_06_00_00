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
 *  @file       fft_alg_int.h
 *
 *  @brief      This file defines the functions for FFT applet
 *  @version 0.0 (Mar 2016) : Base version.
 */


#ifndef FFT_ALG_INT_H_
#define FFT_ALG_INT_H_

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ifft_ti.h"
#include "fft_graph_int.h"

#define FFT_TI_MAX_PITCH_SUPPORTED (32767U)

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for rBrief applet
*/
typedef enum
{
  FFT_TI_TWIDDLE_FACTOR_BUF_IDX_1024,
  FFT_TI_TWIDDLE_FACTOR_BUF_IDX_512,
  FFT_TI_TWIDDLE_FACTOR_BUF_IDX_256,
  FFT_TI_TWIDDLE_FACTOR_BUF_IDX_128,
  FFT_TI_TWIDDLE_FACTOR_BUF_IDX_64,
  FFT_TI_TWIDDLE_FACTOR_BUF_IDX_MAX
} eTwiddleFactorBufIndex;

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for rBrief applet
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for Feature Plane computation for Luma component graph */
  FFT_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  FFT_GRAPH_OBJ_INT_MEMREC,
  FFT_GRAPH_SCRATCH_MEMREC,
  FFT_GRAPH_CONTEXT_MEMREC,
  FFT_GRAPH_ARGS_MEMREC,
  FFT_ALL_STAGE_TWIDDLE_FACTOR_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Fast9 corner detect application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct FFT_TI_Obj
  @brief  This structure is the main handle of rBrief.
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
  FFT_TI_CreateParams createParams;
  int8_t * twiddleFactorBufs[FFT_TI_TWIDDLE_FACTOR_BUF_IDX_MAX];
} FFT_TI_Obj;

typedef FFT_TI_Obj * FFT_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t FFT_TI_numAlloc(void);
int32_t FFT_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t FFT_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  FFT_TI_activate(IALG_Handle handle);
void  FFT_TI_deactivate(IALG_Handle handle);
int32_t FFT_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t FFT_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t FFT_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs, IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
XDAS_Int32 FFT_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* FFT_ALG_INT_H_ */

