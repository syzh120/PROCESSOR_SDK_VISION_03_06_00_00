/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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




#ifndef BAM_CONSTRUCT_H
#define BAM_CONSTRUCT_H

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#ifndef HOST_EMULATION
#include <stdbool.h>
#endif
#pragma RESET_MISRA ("required")

#include "bam_common.h"
#include "bam_kernel_interface.h"


#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */


#define BAM_INVALID_KERNEL_ID       0xFFFFFFFFU     /**< Kernel ID showing invalid kernel*/

/**
 *  @brief      The following symbols are used to set any variable of type BAM_CoreType
 */
#define BAM_EVE                        0 /**< kernel is implemented using EVE's ARP32 and VCOP instruction set only */
#define BAM_EVE_ARP32            1 /**< kernel is implemented using EVE's ARP32 instruction set only (not VCOP involved) */
#define BAM_DSP_C64x             20 /**< kernel is implemented using C64x fixed point instruction set only */
#define BAM_DSP_C67x             21 /**< kernel is implemented using C67x fixed point and floating point instruction set only */
#define BAM_DSP_C66x             22 /**< kernel is implemented using C66x fixed point and floating point instruction set only */
#define BAM_DSP_C71x             23 /**< kernel is implemented using C71x fixed point and floating point instruction set only */
#define BAM_ARM_M3                30 /**< kernel is implemented using M3 instruction set only */
#define BAM_ARM_M4                31 /**< kernel is implemented using M4 instruction set only */
#define BAM_ARM_A8                32 /**< kernel is implemented using A8 instruction set only */
#define BAM_ARM_A15              33 /**< kernel is implemented using A15 instruction set only */
#define BAM_ARM_NEON            40 /**< kernel is implemented using Neon instruction set only */

/**
 *  @brief      Groups different size variables involved in BAM graph creation. Although this structure is
 *              not directly used by any BAM APIs, it is generally used by applet's function such as ALGO_NAME_TI_getGraphMemReq(BAM_GraphMemReq * memReq)
 *              to faciliate the communication of memory requirements between the IVISION interface and the BAM graph.
 *              In particular, ALGO_NAME_32_TI_alloc() calls ALGO_NAME_TI_getGraphMemReq(BAM_GraphMemReq * memReq).
 */
typedef struct
{
    uint32_t graphObjSize; /**< graph object size in bytes */
    uint32_t graphScratchSize; /**< graph scratch size in bytes */
    uint32_t graphcontextSize; /**< graph context size in bytes */
    uint32_t graphArgsSize; /**< graph argument size in bytes */
} BAM_GraphMemReq;

/**
 *  @brief      Groups different pointers involved in BAM graph creation. Although this structure is
 *              not directly used by any BAM APIs, it is generally used by applet's function such as ALGO_NAME_TI_graphCreate(BAM_GraphMem *graphMem, <ALGO_NAME>_32_TI_graphCreateParams * createParams)
 *              to faciliate the communication of pointers between the IVISION interface and the BAM graph.
 *              In particular, ALGO_NAME_32_TI_init() calls ALGO_NAME_TI_graphCreate(BAM_GraphMemReq * memReq).
 */
typedef struct
{
    void * graphObj; /**< Pointer to graph object */
    void * graphScratch; /**< Pointer to graph scratch */
    void * graphcontext; /**< Pointer to graph context */
    void * graphArgs; /**< Pointer to graph arguments */
} BAM_GraphMem;


/**
 *  @brief      Initializes a Kernel database.
 *
 *  @param[in]  kernelDBDef      Pointer to global kernel database information structure that will be initialized
 *
 *  @retval     BAM_S_SUCCESS               Graph successfully created. Pointer to graph object is returned in pGraphHandle.
 *  @retval     BAM_E_DATABASE_KERNELID     BAM error code returned by BAM_initKernelDB() when a kernelID value doesn't follow a sequential increasing order
 *
 *  @remarks    This function must be called once before the kernel database is passed to the BAM_createGraph() function through the createParams structure.
 *
 */
BAM_Status BAM_initKernelDB(const BAM_KernelDBdef *kernelDBDef);

/**
 *  @brief      Create the graph
 *
 *  @param[in]  createParams    Points to the structure BAM_CreateGraphParams that specifies the graph parameters to be created.
 *  @param[out] pGraphHandle    Points to the location where the graph handler will be written to.
 *  @retval     BAM_S_SUCCESS   Graph successfully created. Pointer to graph object is returned in pGraphHandle.
 *  @retval     BAM_E_UNSUPPORTED optimizeBlockDim set to true while useSmartMemAlloc set to false
 *  @retval     BAM_E_INVALID_MEM_SIZE Allocated space in on-chip or external memories too small. Increase createParams->onChipScratchMemSize or createParams->extMemSize.
 *  @retval     BAM_E_BLOCK_DIM_TOO_BIG Could not allocate memory for all internal and output memory records. Some argument values cause the memory size to exceed the amount of on-chip memory.\n
 *                                      Reduce arguments such as block width or block height to correct the condition.
 *
 *  Create the graph using the description pointed by createParams of type BAM_CreateGraphParams which contains a list of the nodes with their arguments as well as a list to the edges.
 *
 * If createParams->optimizeBlockDim== true, this function optimize the graph by maximizing the processing block width and block height while keeping all the memory record allocations succesful.
 *
 * The search for the best block width is done by iteratively incrementing optParams->blockWidth until the internal memory allocation returned
 * fails. The increment step is createParams->blockDimParams->blockWidthStep, usually equal to 16 in order to align with the processor's number of SIMD ways.
 * In each iteration the function initKernelsArgsFunc() is called to reinitialize the kernel arguments that depend on the optParams->blockWidth value.
 * The function initKernelsArgsFunc() is implemented by the application and is invoked as a callback.
 * In normal behaviour, at least one iteration will succesfully allocate memory.
 *
 */
BAM_Status BAM_createGraph(BAM_CreateGraphParams *createParams, BAM_GraphHandle *pGraphHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BAM_CONSTRUCT_H */
