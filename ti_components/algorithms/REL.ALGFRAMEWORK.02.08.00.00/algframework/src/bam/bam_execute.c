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





/**
 *  @file       bam_execute.c
 *
 *  @brief      This file defines functions for BAM Graph execution
 */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#pragma RESET_MISRA ("required")

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

#include "bam_construct_int.h"

#include "bam_kernel_interface.h"
#include "bam_execute_int.h"
#include "edma_bam_interface.h"
#include "edma_utils_memcpy.h"
#include "bam_utils.h"

#include "edma_utils.h"

static uint32_t BAM_logPerf[3];

static BAM_Status BAM_execute(const BAM_GraphDef *graphDef);
static BAM_Status BAM_DSP_computeWrapper(void *context);

static BAM_Status BAM_execute(const BAM_GraphDef *graphDef)
{
    volatile BAM_Status status = BAM_S_SUCCESS;
    volatile int32_t edmaKernelErr = DMANODE_EDMA_ERR_SUCCESS;
    volatile uint32_t edmaSinkKernelErr = DMANODE_EDMA_ERR_SUCCESS;
    int32_t          edmaSinkStatus = 0;
    volatile int32_t kernelId = 0;
    volatile BAM_NodeDef (*node)[];
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    volatile uint32_t nodeIndex = 0;

    volatile uint32_t sourceNodeIndex = 0;
    volatile uint32_t sinkNodeIndex = 0;
    volatile uint32_t computeNodeIndex = 0;
    volatile uint32_t ARP32computeNodeIndex= 0;

    volatile uint32_t flag = 0;

    volatile BAM_KernelFunc kernelComputeSourceArr[BAM_MAX_NODES];
    volatile BAM_KernelFunc kernelComputeSinkArr[BAM_MAX_NODES];
    volatile BAM_KernelFunc kernelWaitSourceArr[BAM_MAX_NODES];
    volatile BAM_KernelFunc kernelWaitSinkArr[BAM_MAX_NODES];
    volatile void *kernelContextSourceArr[BAM_MAX_NODES];
    volatile void *kernelContextSinkArr[BAM_MAX_NODES];

    BAM_KernelFunc kernelCompute[BAM_MAX_NODES];
    BAM_KernelFunc kernelComputeTemp;
    BAM_KernelCustom kernelCustomTemp;
    void *computeContext[BAM_MAX_NODES];
    BAM_ARP32KernelComputeContext ARP32KernelComputeContext[BAM_MAX_NODES];
    uint32_t numComputeNodes = 0;
    uint8_t (*context)[];
    void* (*context2)[];



#ifndef BAM_EN_MULTIPLE_DMANODE_SUPPORT
    BAM_KernelFunc kernelComputeSource = 0, kernelComputeSink = 0, kernelWaitSource = 0, kernelWaitSink = 0;
    volatile void *kernelContextSource = 0, *kernelContextSink = 0;
#endif

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    /* Initialize array elements to 0 */
    for (nodeIndex = 0; nodeIndex <BAM_MAX_NODES; nodeIndex++) {
        kernelComputeSourceArr[nodeIndex]= NULL;
        kernelComputeSinkArr[nodeIndex]= NULL;
        kernelWaitSourceArr[nodeIndex]= NULL;
        kernelWaitSinkArr[nodeIndex]= NULL;
        kernelContextSourceArr[nodeIndex]= NULL;
        kernelContextSinkArr[nodeIndex]= NULL;
        kernelCompute[nodeIndex] = NULL;
        computeContext[nodeIndex] = NULL;
    }

#ifdef PROFILING
    /* #define SPLIT_PROFILING */
    uint32_t t0, t1, t2, t3;
    uint32_t profile[10];
#endif
#ifdef PROFILING
    BAM_PROFILE_INIT;
    profile[0] = 0;
    profile[1] = 0;
    profile[2] = 0;
    profile[3] = 0;
    profile[4] = 0;
    profile[5] = 0;
    profile[6] = 0;
#endif

    VCOP_SET_MEM_VIEW ((uint32_t)ALIAS_128K_VIEW);

#ifdef PROFILING
    t0 = BAM_PROFILE_READ;
#endif

    node = (volatile BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelExecFuncDB);

    numComputeNodes= graphDef->params.numComputeNodes;

/* CHECK_MISRA("-14.6")  -> Disable rule 14.16 */
/* Iteration statement has more than one break or goto for loop termination. */
/* Deviation allowed because the goto are forward goto that jumps to the same location. They are used to exit the loop upon error */
    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        if((*node)[nodeIndex].nodeType == BAM_NODE_SOURCE)
        {
            kernelId = (*node)[nodeIndex].kernelInfo.kernelId;
            kernelComputeSourceArr[sourceNodeIndex] = (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCompute;
            kernelWaitSourceArr[sourceNodeIndex] = (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelWait;
            kernelContextSourceArr[sourceNodeIndex] = (*node)[nodeIndex].kernelContext;
            sourceNodeIndex++;
        }
        else if((*node)[nodeIndex].nodeType == BAM_NODE_SINK)
        {
            kernelId = (*node)[nodeIndex].kernelInfo.kernelId;
            kernelComputeSinkArr[sinkNodeIndex] = (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCompute;
            kernelWaitSinkArr[sinkNodeIndex] = (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelWait;
            kernelContextSinkArr[sinkNodeIndex] = (*node)[nodeIndex].kernelContext;
            sinkNodeIndex++;
        }
        else
        {
            /* compute nodes */
            kernelId = (*node)[nodeIndex].kernelInfo.kernelId;

            kernelComputeTemp= (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCompute;
            kernelCustomTemp= (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCustom;

            if (((*node)[nodeIndex].kernelInfo.coreType== BAM_EVE_ARP32) ||((*node)[nodeIndex].kernelInfo.coreType == BAM_DSP_C66x) ||((*node)[nodeIndex].kernelInfo.coreType == BAM_DSP_C71x)) {
                if (kernelComputeTemp!= NULL) {
                    uint8_t (*pContextArgs)[];

                    kernelCompute[computeNodeIndex]= (((*node)[nodeIndex].kernelInfo.coreType == BAM_DSP_C66x) || ((*node)[nodeIndex].kernelInfo.coreType == BAM_DSP_C71x)) ? &BAM_DSP_computeWrapper : &BAM_ARP32_computeWrapper;
                    computeContext[computeNodeIndex]= (void*)&ARP32KernelComputeContext[ARP32computeNodeIndex];
                    ARP32KernelComputeContext[ARP32computeNodeIndex].kernelCompute= kernelComputeTemp;
                    ARP32KernelComputeContext[ARP32computeNodeIndex].context[0]= (*node)[nodeIndex].kernelContext;
                    context= (uint8_t (*)[])ARP32KernelComputeContext[ARP32computeNodeIndex].context[0];
/* CHECK_MISRA("-10.5")  -> Disable rule 10.5 */
/* The result of bitwise operation on unsigned char or short is not cast back to original type. */
/* It seems like a false positive because type of kernelContextSize is uint32_t, not unsigned char or unsigned short */
                    ARP32KernelComputeContext[ARP32computeNodeIndex].context[1]= (void*)&((*context)[(uint32_t)BAM_ALIGN_WORD((*node)[nodeIndex].kernelInfo.kernelContextSize)]);
/*RESET_MISRA("10.5")  -> Reset rule 10.5*/
                    ARP32KernelComputeContext[ARP32computeNodeIndex].pingpongFlag= BUF_PING;
                    ARP32KernelComputeContext[ARP32computeNodeIndex].kernelWaitSource= NULL;

                    context2= (void* (*)[])ARP32KernelComputeContext[ARP32computeNodeIndex].context[0];
                    pContextArgs= (uint8_t(*)[])(void*)&((*context2)[(*node)[nodeIndex].kernelInfo.numRecInternal + (*node)[nodeIndex].kernelInfo.numInputDataBlocks + (*node)[nodeIndex].kernelInfo.numOutputDataBlocks]);

                    ARP32KernelComputeContext[ARP32computeNodeIndex].pArgs[0]= &(*pContextArgs)[0];
/* CHECK_MISRA("-10.5")  -> Disable rule 10.5 */
/* The result of bitwise operation on unsigned char or short is not cast back to original type. */
/* It seems like a false positive because type of kernelContextSize is uint32_t, not unsigned char or unsigned short */
                    ARP32KernelComputeContext[ARP32computeNodeIndex].pArgs[1]= &((*pContextArgs)[(uint32_t)BAM_ALIGN_WORD((*node)[nodeIndex].kernelInfo.kernelContextSize)]);
/*RESET_MISRA("10.5")  -> Reset rule 10.5*/
                    ARP32KernelComputeContext[ARP32computeNodeIndex].argsAndPrivContextSize= (*node)[nodeIndex].kernelInfo.kernelContextSize - (sizeof(void*)*((*node)[nodeIndex].kernelInfo.numRecInternal + (*node)[nodeIndex].kernelInfo.numInputDataBlocks + (*node)[nodeIndex].kernelInfo.numOutputDataBlocks));

                    ARP32computeNodeIndex++;
                }
                else {
                    status= status = BAM_E_INVALID_PTR;
                    goto Exit;
                }
            }
            else {
                if (kernelComputeTemp!= NULL) {
                    kernelCompute[computeNodeIndex]= kernelComputeTemp;
                    computeContext[computeNodeIndex] = (*node)[nodeIndex].kernelContext;
                }
                else if (kernelCustomTemp!= NULL){
#ifndef HOST_EMULATION
                    /* CHECK_MISRA("-11.1 -11.4")  -> Disable rule 11.1 11.4*/
                    /* Cast between a function pointer and a non-integral type. */
                    /* Cast between a pointer to object type and a different pointer to object type */
                    /* Deviation requested because it would be difficult to fix it without affecting performance issue */
                    kernelCompute[computeNodeIndex]= (BAM_KernelFunc)kernelCustomTemp;
                    /*RESET_MISRA("11.1 11.4")  -> Reset rule 11.1 11.4*/
#else
                    kernelCompute[computeNodeIndex]= (BAM_KernelFunc)kernelCustomTemp;
#endif
                    computeContext[computeNodeIndex] = *((uint16_t**)(*node)[nodeIndex].kernelContext);
                }
                else {
                    status= status = BAM_E_INVALID_PTR;
                    goto Exit;
                }

            }

            computeNodeIndex++;
        }
    }
    /*RESET_MISRA("14.6")  -> Reset rule 14.6  */

#ifndef BAM_EN_MULTIPLE_DMANODE_SUPPORT
    kernelComputeSource = kernelComputeSourceArr[0];
    kernelComputeSink = kernelComputeSinkArr[0];
    kernelContextSource = kernelContextSourceArr[0];
    kernelContextSink   = kernelContextSinkArr[0];

#ifndef CORE_DSP
    if (ARP32computeNodeIndex)
	{
        ARP32KernelComputeContext[0].kernelWaitSource= kernelWaitSourceArr[0];
        ARP32KernelComputeContext[0].kernelWaitSink= kernelWaitSinkArr[0];
        /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
        /* Cast operation removes const or volatile modifier from a pointer or reference */
        /* Not a problem, it doesn't affect the functional behaviour of the code  */
        ARP32KernelComputeContext[0].kernelContextSource= (void*)kernelContextSourceArr[0];
        ARP32KernelComputeContext[0].kernelContextSink= (void*)kernelContextSinkArr[0];
        /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
        kernelWaitSource= &BAM_dummyKernelFunc;
        kernelWaitSink= &BAM_dummyKernelFunc;
    }
    else
#endif
	{
        kernelWaitSource = kernelWaitSourceArr[0];
        kernelWaitSink = kernelWaitSinkArr[0];
    }
#endif

    flag = (uint32_t)BUF_PING;
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);


#ifdef SPLIT_PROFILING
    t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
    /** EDMA trigger for first block of Source **/
#if !(HOST_EMULATION && CORE_EVE)
    /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
    /* Cast operation removes const or volatile modifier from a pointer or reference */
    /* Not a problem, it doesn't affect the functional behaviour of the code  */
    edmaKernelErr = kernelComputeSource((void *)kernelContextSource);
    /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif
#endif

#ifdef _BAM_DEBUG
    if ((edmaKernelErr != DMANODE_EDMA_ERR_SUCCESS))
    {
        goto Exit;
    }
#endif
#ifdef SPLIT_PROFILING
    t3 = BAM_PROFILE_READ;
    profile[2] += t3 - t2;
#endif

#ifdef SPLIT_PROFILING
    t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
    /** EDMA wait for first block of Source to finish**/
#if !(HOST_EMULATION && CORE_EVE)
    /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
    /* Cast operation removes const or volatile modifier from a pointer or reference */
    /* Not a problem, it doesn't affect the functional behaviour of the code  */
    edmaKernelErr = kernelWaitSourceArr[0]((void *)kernelContextSourceArr[0]);
    /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif
#endif

#ifdef _BAM_DEBUG
    if ((edmaKernelErr != DMANODE_EDMA_ERR_SUCCESS))
    {
        goto Exit;
    }
#endif
#ifdef SPLIT_PROFILING
    t3 = BAM_PROFILE_READ;
    profile[4] += t3 - t2;
#endif

    while (edmaSinkStatus != 1)
    {


        flag = VCOP_BUF_SWITCH_TOGGLE(flag);

#ifdef SPLIT_PROFILING
        t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
        /** Trigger Sink Channels */
        /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
        /* Cast operation removes const or volatile modifier from a pointer or reference */
        /* Not a problem, it doesn't affect the functional behaviour of the code  */

        edmaSinkStatus = kernelComputeSink((void *)kernelContextSink);

        /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif

#ifdef _BAM_DEBUG
        if (!((edmaSinkKernelErr == DMANODE_EDMA_ERR_SUCCESS) || (edmaSinkKernelErr == DMANODE_EDMA_ERR_LAST_BLOCK)))
        {
            goto Exit;
        }
#endif
#ifdef SPLIT_PROFILING
        t3 = BAM_PROFILE_READ;
        profile[3] += t3 - t2;
#endif

#ifdef SPLIT_PROFILING
        t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
        /** Trigger Source Channels */
        /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
        /* Cast operation removes const or volatile modifier from a pointer or reference */
        /* Not a problem, it doesn't affect the functional behaviour of the code  */
        edmaKernelErr = kernelComputeSource((void *)kernelContextSource);
        /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif

#ifdef _BAM_DEBUG
        if ((edmaKernelErr != DMANODE_EDMA_ERR_SUCCESS))
        {
            goto Exit;
        }
#endif
#ifdef SPLIT_PROFILING
        t3 = BAM_PROFILE_READ;
        profile[2] += t3 - t2;
#endif

        /** Call VCOP kernels */
        for (computeNodeIndex = 0; computeNodeIndex < numComputeNodes; computeNodeIndex++)
        {

#ifdef _BAM_DEBUG
            PRINTF("Executing kernel %d \n", computeNodeIndex);
#endif
#ifdef SPLIT_PROFILING
            t2 = BAM_PROFILE_READ;
#endif
            /* Issue observed here on -o3 mode, when the return value is removed */
            edmaKernelErr = kernelCompute[computeNodeIndex](computeContext[computeNodeIndex]);
            /* _vcop_vloop_done(); */
#ifdef SPLIT_PROFILING
            t3 = BAM_PROFILE_READ;
            profile[1] += t3 - t2;
#endif
        }


#ifdef SPLIT_PROFILING
        t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
        /** Wait for SOURCE EDMA channels to finish  */
        /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
        /* Cast operation removes const or volatile modifier from a pointer or reference */
        /* Not a problem, it doesn't affect the functional behaviour of the code  */
        edmaKernelErr = kernelWaitSource((void *)kernelContextSource);
        /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif

#ifdef _BAM_DEBUG
        if ((edmaKernelErr != DMANODE_EDMA_ERR_SUCCESS))
        {
            goto Exit;
        }
#endif
#ifdef SPLIT_PROFILING
        t3 = BAM_PROFILE_READ;
        profile[4] += t3 - t2;
#endif

#ifdef SPLIT_PROFILING
        t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
        /** Wait for SINK EDMA channels to finish  */
        /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
        /* Cast operation removes const or volatile modifier from a pointer or reference */
        /* Not a problem, it doesn't affect the functional behaviour of the code  */
        edmaSinkKernelErr |= kernelWaitSink((void *)kernelContextSink);
        /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif

#ifdef _BAM_DEBUG
        if ((edmaSinkKernelErr != DMANODE_EDMA_ERR_SUCCESS))
        {
            goto Exit;
        }
#endif
#ifdef SPLIT_PROFILING
        t3 = BAM_PROFILE_READ;
        profile[5] += t3 - t2;
#endif
        /** Wait for VCOP kernels to finish  */
        _vcop_vloop_done();
    }

    flag = VCOP_BUF_SWITCH_TOGGLE(flag);

#ifdef SPLIT_PROFILING
    t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
    /** Transfer last SINK blocks */
    /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
    /* Cast operation removes const or volatile modifier from a pointer or reference */
    /* Not a problem, it doesn't affect the functional behaviour of the code  */
    edmaSinkStatus = kernelComputeSink((void *)kernelContextSink);
    /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif

#ifdef _BAM_DEBUG
    if (!((edmaSinkKernelErr == DMANODE_EDMA_ERR_SUCCESS) || (edmaSinkKernelErr == DMANODE_EDMA_ERR_LAST_BLOCK)))
    {
        goto Exit;
    }
#endif
#ifdef SPLIT_PROFILING
    t3 = BAM_PROFILE_READ;
    profile[3] += t3 - t2;
#endif

#ifdef SPLIT_PROFILING
    t2 = BAM_PROFILE_READ;
#endif

#ifdef BAM_EN_MULTIPLE_DMANODE_SUPPORT
#else
    /** Wait for transfer of last SINK blocks */
    /* CHECK_MISRA("-11.8")  -> Disable rule 11.8 */
    /* Cast operation removes const or volatile modifier from a pointer or reference */
    /* Not a problem, it doesn't affect the functional behaviour of the code  */
    edmaKernelErr = kernelWaitSinkArr[0]((void *)kernelContextSinkArr[0]);
    /*RESET_MISRA("11.8")  -> Reset rule 11.8*/
#endif

#ifdef _BAM_DEBUG
    if ((edmaKernelErr != DMANODE_EDMA_ERR_SUCCESS))
    {
        goto Exit;
    }
#endif
#ifdef SPLIT_PROFILING
    t3 = BAM_PROFILE_READ;
    profile[5] += t3 - t2;
#endif

#ifdef PROFILING
    t1 = BAM_PROFILE_READ;
    profile[0] = t1 - t0;
#endif

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

#ifdef PROFILING
    PRINTF ("--ARP32 cycles--\n");
    PRINTF ("Kernel Compute Nodes=  %ld\n", profile[1]);
    PRINTF ("Source EDMA Trigger =  %ld\n", profile[2]);
    PRINTF ("Sink EDMA Trigger   =  %ld\n", profile[3]);
    PRINTF ("Source EDMA wait    =  %ld\n", profile[4]);
    PRINTF ("Sink EDMA wait      =  %ld\n", profile[5]);
    PRINTF ("Total measured      =  %ld\n", profile[0]);
    PRINTF ("Total Calculated    =  %ld\n", profile[1]+profile[2]+profile[3]+profile[4]+profile[5]);
#endif
    Exit:
    status = edmaKernelErr;   /* Change this later according to error code. */
    return (status);
}


BAM_Status BAM_controlGraphNode(const BAM_GraphDef *graphDef, uint8_t nodeIndex, void *ctlArg)
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_NodeDef (*nodeArr)[];
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    int32_t edmaKernelErr = DMANODE_EDMA_ERR_SUCCESS;
    uint8_t kernelId = 0;

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    /* Calculate source node array in graph definition record */
    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelExecFuncDB);

    kernelId = (*nodeArr)[nodeIndex].kernelInfo.kernelId;
    if ((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCtl != NULL)
    {
        edmaKernelErr = (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCtl((*nodeArr)[nodeIndex].kernelContext,
                ctlArg);
    }

    Exit:
    status = edmaKernelErr;   /* Change this later according to error code. */
    return (status);

}

int32_t BAM_initGraphInstance(const BAM_GraphHandle graphHandle) {

    int32_t status = BAM_S_SUCCESS;
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    BAM_NodeDef (*node)[];
    uint8_t kernelId = 0;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    uint32_t nodeIndex = 0;

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* Calculate source node array in graph definition record */
    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelExecFuncDB);

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++) {
        kernelId = (*node)[nodeIndex].kernelInfo.kernelId;

        if ((graphDef->initInstanceDone == 0) &&
                ((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitInstance != NULL)) {
            (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitInstance((*node)[nodeIndex].kernelContext);
        }
    }

    graphDef->initInstanceDone = 1;

    return status;

}

/* process */
int32_t BAM_process(const BAM_GraphHandle graphHandle, const BAM_InArgs *inArgs, BAM_OutArgs *outArgs, const BAM_ProcessHints *hints)
{
    int32_t status = BAM_S_SUCCESS;
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    BAM_NodeDef (*node)[];
    uint8_t kernelId = 0;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    uint32_t nodeIndex = 0;
    int32_t offset;
    uint8_t (*context)[];

    if ((graphDef->params.numSourceNodes > 1) || (graphDef->params.numSinkNodes > 1))
    {
        PRINTF("More than 1 source/sink nodes not supported. (Although more than one channel in single node are supported)");
        status = BAM_E_FAIL;
        goto Exit;
    }

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* Calculate source node array in graph definition record */
    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelExecFuncDB);

    BAM_logPerf[0]= (uint32_t)BAM_PROFILE_READ;

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        /* Relocate node[nodeIndex].kernelContext since it is a pointer. If graphDef changes location from last location specified by thisPtr
         * then every node[nodeIndex].kernelContext needs to reflect the new location
         */

        /* CHECK_MISRA("-17.4")  -> Disable rule 17.4 */
        /* Pointer is used in arithmetic or array index expression */
        /* Deviation is allowed because there is no other way to obtain the offset between these two pointers */
        offset= (uint8_t*)graphDef - (uint8_t*)(graphDef->thisPtr);
        /* RESET_MISRA("17.4")  -> Reset rule 17.4*/
        context= (uint8_t (*)[])(*node)[nodeIndex].kernelContext;
        (*node)[nodeIndex].kernelContext= (void*)&((*context)[offset]);

        kernelId = (*node)[nodeIndex].kernelInfo.kernelId;

        if ((graphDef->initInstanceDone == 0) &&
                ((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitInstance != NULL))
        {
            (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitInstance((*node)[nodeIndex].kernelContext);
        }

        /* We only want to execute the kernelInitFrame for slice index #0 e.g. at the beginning of a new frame
         * For subsequent slices, we just want to resume the processing without any re-initialization.
         * */
        if ((inArgs->sliceIndex==0) && ((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitFrame != NULL))
        {
            (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitFrame((*node)[nodeIndex].kernelContext);
        }
    }

    /* Update thisPtr with the current location of graphDef */
    graphDef->thisPtr= (void*)graphDef;
    graphDef->initInstanceDone = 1;

    BAM_logPerf[1]= (uint32_t)BAM_PROFILE_READ;

    /* execute loop */
    status = BAM_execute(graphDef);

    BAM_logPerf[2]= (uint32_t)BAM_PROFILE_READ;

    if (status != BAM_S_SUCCESS)
    {
        PRINTF("BAM_Execute() returned error = %d!!!", status);
        goto Exit;
    }

    Exit:
    /* The line below is added to ensure compatibility with any subsequent applets that rely on vcop_malloc() to allocate memory blocks.
       Since BAM_execute() overwrites the image buffers and working buffer, any metadata associated to the heap residing in image buffer
       and working buffer becomes corrupted. Calling vcop_minit() resets the metadata to the initial working state.
    */
#ifdef CORE_EVE
    vcop_minit();
#endif
    return (status);
}


int32_t BAM_processSingleBlock(const BAM_GraphHandle graphHandle, const BAM_InBufs *inBufs, const BAM_OutBufs *outBufs, const BAM_InArgs *inArgs, BAM_OutArgs *outArgs, const BAM_ProcessHints *hints) {

    int32_t status = BAM_S_SUCCESS;
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    int8_t i = 0;
    BAM_NodeDef (*node)[];
    uint8_t kernelId = 0;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    uint32_t nodeIndex = 0;
    uint16_t numRecOutputDataBlock= 0;
    BAM_DataBlockDef *pOutDataBlock= NULL;
    BAM_DataBlockDef *pInDataBlock= NULL;
    uint8_t *extMemPtr;
    uint8_t (*buf)[];
    BAM_DataBlockDef (*dataBlockArr)[];
    BAM_KernelFunc kernelComputeTemp;
    BAM_KernelCustom kernelCustomTemp;
    BAM_ARP32KernelComputeContext ARP32KernelComputeContext;
    int32_t offset;
    uint8_t (*context)[];
    BAM_BufDesc    *(*inBufDesc)[];
    BAM_BufDesc    *(*outBufDesc)[];

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    inBufDesc  = (BAM_BufDesc *(*)[])(void*)inBufs->bufDesc;
    outBufDesc  = (BAM_BufDesc *(*)[])(void*)outBufs->bufDesc;

    /* Calculate source node array in graph definition record */
    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    dataBlockArr = (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);
    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelExecFuncDB);

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        /* Relocate node[nodeIndex].kernelContext since it is a pointer. If graphDef changes location from last location specified by thisPtr
         * then it every node[nodeIndex].kernelContext needs to reflect the new location
         */
        /* CHECK_MISRA("-17.4")  -> Disable rule 17.4 */
        /* Pointer is used in arithmetic or array index expression */
        /* Deviation is allowed because there is no other way to obtain the offset between these two pointers */
        offset= (uint8_t*)graphDef - (uint8_t*)(graphDef->thisPtr);
        /* RESET_MISRA("17.4")  -> Reset rule 17.4*/
        context= (uint8_t (*)[])(*node)[nodeIndex].kernelContext;
        (*node)[nodeIndex].kernelContext= (void*)&((*context)[offset]);

        kernelId = (*node)[nodeIndex].kernelInfo.kernelId;

        if ((graphDef->initInstanceDone == 0) &&
                ((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitInstance != NULL))
        {
            (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitInstance((*node)[nodeIndex].kernelContext);
        }

        if((hints->priority== BAM_SINGLE_BLOCK) && ((*node)[nodeIndex].nodeType == BAM_NODE_SOURCE))
        {

            numRecOutputDataBlock =  (*node)[nodeIndex].kernelInfo.numOutputDataBlocks;

            if (numRecOutputDataBlock != inBufs->numBufs) {
                status= BAM_E_FAIL;
                goto Exit;
            }

            for (i = 0; i < inBufs->numBufs; i++)
            {
                buf= (uint8_t (*)[])(*inBufDesc)[i]->buf;
                extMemPtr= &(*buf)[((*inBufDesc)[i]->sliceOffset.y * (*inBufDesc)[i]->bufSize.pitch) + (*inBufDesc)[i]->sliceOffset.x];

                pOutDataBlock= &(*dataBlockArr)[(*node)[nodeIndex].outDataBlockIndex[i]];

                EDMA_UTILS_memcpy2D(pOutDataBlock->mem.base, extMemPtr,  (*inBufDesc)[i]->bufSize.width, (*inBufDesc)[i]->bufSize.height, (*inBufDesc)[i]->bufSize.width, (*inBufDesc)[i]->bufSize.pitch);
            }

        }
    }

    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP, IBUFLA_VCOP);
    /* CHECK_MISRA("-14.6")  -> Disable rule 14.16 */
    /* Iteration statement has more than one break or goto for loop termination. */
    /* Deviation allowed because the goto are forward goto that jumps to the same location. They are used to exit the loop upon error */
    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        if((*node)[nodeIndex].nodeType >= BAM_NODE_COMPUTE)
        {
            kernelId = (*node)[nodeIndex].kernelInfo.kernelId;

            /* We only want to execute the kernelInitFrame for slice index #0 e.g. at the beginning of a new frame
             * For subsequent slices, we just want to resume the processing without any re-initialization.
             * */
            if ((inArgs->sliceIndex==0) && ((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitFrame != NULL))
            {
                VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
                (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelInitFrame((*node)[nodeIndex].kernelContext);
                VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP, IBUFLA_VCOP);
            }

            kernelComputeTemp= (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCompute;
            kernelCustomTemp= (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCustom;

            if ((*node)[nodeIndex].kernelInfo.coreType== BAM_EVE_ARP32) {
                if (kernelComputeTemp!= NULL) {

                    ARP32KernelComputeContext.kernelCompute= kernelComputeTemp;
                    ARP32KernelComputeContext.context[0]= (*node)[nodeIndex].kernelContext;
                    ARP32KernelComputeContext.pingpongFlag= BUF_PING;
                    ARP32KernelComputeContext.kernelWaitSource= NULL;
                    ARP32KernelComputeContext.argsAndPrivContextSize = 0;
                    BAM_ARP32_computeWrapper(&ARP32KernelComputeContext);

                }
                else {
                    status= status = BAM_E_INVALID_PTR;
                    goto Exit;
                }

            }
            else {

                if (kernelComputeTemp!= NULL) {
                    kernelComputeTemp((*node)[nodeIndex].kernelContext);
                }
                else if (kernelCustomTemp!= NULL){
                    kernelCustomTemp(*((uint16_t**)(*node)[nodeIndex].kernelContext));
                }
                else {
                    status= status = BAM_E_INVALID_PTR;
                    goto Exit;
                }

            }

        }

    }
/* RESET_MISRA("14.6")  -> Reset rule 14.6*/
    _vcop_vloop_done();

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    if (hints->priority== BAM_SINGLE_BLOCK) {
        for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
        {
            if((*node)[nodeIndex].nodeType == BAM_NODE_SINK)
            {

                for (i = 0; i < outBufs->numBufs; i++)
                {
                    buf= (uint8_t (*)[])(*outBufDesc)[i]->buf;
                    extMemPtr= &(*buf)[((*outBufDesc)[i]->sliceOffset.y * (*outBufDesc)[i]->bufSize.pitch) + (*outBufDesc)[i]->sliceOffset.x];

                    pInDataBlock= &(*dataBlockArr)[(*node)[nodeIndex].inDataBlockIndex[i]];

                    EDMA_UTILS_memcpy2D(extMemPtr,  pInDataBlock->mem.base, (*outBufDesc)[i]->bufSize.width, (*outBufDesc)[i]->bufSize.height, (*outBufDesc)[i]->bufSize.pitch, (*outBufDesc)[i]->bufSize.width);
                }
            }
        }
    }


    /* About thisPtr with the current location of graphDef */
    graphDef->thisPtr= (void*)graphDef;
    graphDef->initInstanceDone = 1;

    Exit:
    return (status);
}

uint32_t BAM_getKernelsInitCycles(void) {

    return (BAM_logPerf[1] - BAM_logPerf[0]);

}

uint32_t BAM_getKernelsExecCycles(void) {

    return (BAM_logPerf[2] - BAM_logPerf[1]);

}


/**
 *    Context Save
 */
int32_t BAM_contextSaveMemRec(BAM_MemRec *memRec)
{
    int32_t status = BAM_S_SUCCESS;

    if((memRec->size != 0) && (memRec->base !=NULL) && (memRec->ext != NULL) &&
            (memRec->attrs.memAttrs == BAM_MEMATTRS_PERSIST))
    {

        status = EDMA_UTILS_memcpy2D(memRec->ext,
                (const void*)memRec->base,
                (uint16_t)memRec->size,(uint16_t)1, (int16_t)0, (int16_t)0);
        if(status != 0)
        {
            status = BAM_E_FAIL;
        }
    }

    return status;
}


/**
 *    Context Restore
 */
int32_t BAM_contextRestoreMemRec(BAM_MemRec *memRec)
{
    int32_t status = BAM_S_SUCCESS;

    if((memRec->size != 0) && (memRec->base !=NULL) && (memRec->ext != NULL) &&
            (memRec->attrs.memAttrs == BAM_MEMATTRS_PERSIST))
    {
        status = EDMA_UTILS_memcpy2D(memRec->base,
                (const void*)memRec->ext,
                (uint16_t)memRec->size, (uint16_t)1 , (int16_t)0, (int16_t)0);
        if(status != 0)
        {
            status = BAM_E_FAIL;
        }

    }

    return status;
}


/**
 *    Context Restore
 */
int32_t BAM_activateGraph(const BAM_GraphHandle graphHandle)
{
    int32_t status = BAM_S_SUCCESS;

    /* restore graph handle memrec */
    BAM_NodeDef (*node)[];
    uint8_t dataBlkIndex = 0, nodeIndex = 0;
    BAM_MemRec *memRecToBeRestored = 0;

    /* get the restored graph handle */
    const BAM_GraphDef *graphDef = (const BAM_GraphDef *)graphHandle;

    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        /* restore internal data blocks.*/
        for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++)
        {
            memRecToBeRestored = &((*node)[nodeIndex].internalBlock[dataBlkIndex]);
            status = BAM_contextRestoreMemRec(memRecToBeRestored);
        }
    }

    return status;
}


/**
 *    Context Save
 */
int32_t BAM_deActivateGraph(const BAM_GraphHandle graphHandle)
{
    int32_t status = BAM_S_SUCCESS;

    BAM_NodeDef (*node)[];
    uint8_t dataBlkIndex = 0, nodeIndex = 0;
    BAM_MemRec *memRecToBeSaved = 0;

    /* get the restored graph handle */
    const BAM_GraphDef *graphDef = (const BAM_GraphDef *)(const void *)graphHandle;

    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        /* save internal data blocks.*/
        for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++)
        {
            memRecToBeSaved = &((*node)[nodeIndex].internalBlock[dataBlkIndex]);
            status = BAM_contextSaveMemRec(memRecToBeSaved);
            if(status != BAM_S_SUCCESS)
            {
                break;
            }
        }
    }


    return status;
}


BAM_Status BAM_ARP32_computeWrapper(void *context) {

    uint32_t status = BAM_S_SUCCESS;
    BAM_ARP32KernelComputeContext *c = (BAM_ARP32KernelComputeContext *)context;

    /* Wait for completion of vcop processing before ARP32 touches the image buffers */
    _vcop_vloop_done();
    /* kernelWaitSource is non NULL only for the first ARP32 node encountered
     * in order to force BAM to wait for completion of the EDMA before switching the buffers
     * The reason is that when ALIAS view is used, the EDMA relies on the setting of the buffer switch
     * to know which buffer it has to access. Changing buffer switch on the fly during a transfer leads
     * to unexpected results so we need to wait for the transfer to complete.
     * */
    if (c->kernelWaitSource){
        status= c->kernelWaitSource(c->kernelContextSource);
        status= (status | c->kernelWaitSink(c->kernelContextSink));
    }

    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    if (c->pingpongFlag== BUF_PING) {
        status= (status | c->kernelCompute(c->context[0]));
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP, IBUFLA_VCOP);
        c->pingpongFlag= BUF_PONG;
        /* Need to copy part of context to c->context[1] in case the execution modifies any of the private or arg value */
        if (c->argsAndPrivContextSize) {
            memcpy(c->pArgs[1], c->pArgs[0], c->argsAndPrivContextSize);
        }

    }
    else {
        status= (status | c->kernelCompute(c->context[1]));
        VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);
        c->pingpongFlag= BUF_PING;
        /* Need to copy part of context to c->context[0] in case the execution modifies any of the private or arg value */
        if (c->argsAndPrivContextSize) {
            memcpy(c->pArgs[0], c->pArgs[1], c->argsAndPrivContextSize);
        }
    }

    return (BAM_Status)status;
}

BAM_Status BAM_DSP_computeWrapper(void *context) {

    uint32_t status = BAM_S_SUCCESS;
    BAM_ARP32KernelComputeContext *c = (BAM_ARP32KernelComputeContext *)context;


    if (c->pingpongFlag== BUF_PING) {
        status= (status | c->kernelCompute(c->context[0]));
        c->pingpongFlag= BUF_PONG;
        /* Need to copy part of context to c->context[1] in case the execution modifies any of the private or arg value */
        if (c->argsAndPrivContextSize) {
            memcpy(c->pArgs[1], c->pArgs[0], c->argsAndPrivContextSize);
        }
    }
    else {
        status= (status | c->kernelCompute(c->context[1]));
        c->pingpongFlag= BUF_PING;
        /* Need to copy part of context to c->context[0] in case the execution modifies any of the private or arg value */
        if (c->argsAndPrivContextSize) {
            memcpy(c->pArgs[0], c->pArgs[1], c->argsAndPrivContextSize);
        }
    }

    return (BAM_Status)status;
}

BAM_Status BAM_dummyKernelFunc(void *context) {
    return BAM_S_SUCCESS;
}

BAM_Status BAM_controlNode(BAM_GraphHandle graphHandle, uint8_t nodeIndex, void *controlArgs) {

    /* get the restored graph handle */
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    const BAM_KernelExecFuncDBdef (*kernelExecFuncDbArray)[];
    void *kernelContext= NULL;
    int32_t status = BAM_S_SUCCESS;
    uint8_t kernelId = 0;
    BAM_NodeDef (*node)[];
    int32_t offset;
    uint8_t (*context)[];

    kernelExecFuncDbArray= (const BAM_KernelExecFuncDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelExecFuncDB);
    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    /* Lookup kernelContext and relocate it since it is a pointer because graphDef can change location from last location specified by thisPtr
     */
/* CHECK_MISRA("-17.4")  -> Disable rule 17.4 */
/* Pointer is used in arithmetic or array index expression */
/* Deviation is allowed because there is no other way to obtain the offset between these two pointers */
    offset= (uint8_t*)graphDef - (uint8_t*)(graphDef->thisPtr);
/* RESET_MISRA("17.4")  -> Reset rule 17.4*/
    context= (uint8_t (*)[])(*node)[nodeIndex].kernelContext;
    kernelContext= (void*)&((*context)[offset]);

    kernelId = (*node)[nodeIndex].kernelInfo.kernelId;
    if((*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCtl != NULL) {
        status= (*kernelExecFuncDbArray)[kernelId].kernelExecFunc->kernelCtl(kernelContext, controlArgs);
    }
    else
    {
        status= BAM_E_UNSUPPORTED;
    }
    return status;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */
