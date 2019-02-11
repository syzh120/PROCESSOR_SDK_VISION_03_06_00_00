/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 * \file tidlLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for algorithm plugin
 *         Link
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "tidlLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_mem_cfg.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */
#define OUTPUT_DATAQ_SIZE  ((TIDL_NUM_OUT_BUFS * 4))
#define OUTPUT_OFFSET_SIZE  (OUTPUT_DATAQ_SIZE)
/* TIDL_NUM_OUT_BUFS * size of int32 * 2 place holder for dataoffset and buff start*/
/* To enable Real Time Debug */
//#define RT_DEBUG
#ifdef RT_DEBUG
#ifdef BUILD_DSP
void _TSC_enable();
long long _TSC_read();
#endif
#endif
/**
 *******************************************************************************
 *
 * \brief Implementation of function to putEmptyCb()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 putEmptyCb(Void *ptr, UInt16 queId, System_BufferList *pBufList)
{
    AlgorithmLink_Obj *pObj = (AlgorithmLink_Obj*)ptr;
    Utils_tskSendCmd(&pObj->tsk, SYSTEM_CMD_NEW_DATA, NULL);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemAlloc()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tidlAlgMemAlloc(AlgorithmLink_tidlObj *pAlgObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    Utils_HeapId heapId;
    AlgorithmLink_tidlCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;

    for(cnt = 0;cnt < pAlgObj->numMemRec;cnt ++)
    {
        switch(pAlgObj->memRec[cnt].space)
        {
            case IALG_SARAM0:
                if(NULL != pLinkCreatePrms->ocmcAddr)
                {
                    /* Allocate memory from the OCMC */
                    pAlgObj->memRec[cnt].base = (Void*)pLinkCreatePrms->ocmcAddr;
                    UTILS_assert(NULL != pAlgObj->memRec[cnt].base);

                    memset(
                        pAlgObj->memRec[cnt].base,
                        0x00,
                        pAlgObj->memRec[cnt].size);
                }
                else
                {
                    pAlgObj->memRec[cnt].base = Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pAlgObj->memRec[cnt].size,
                                                    pAlgObj->memRec[cnt].alignment);
                    UTILS_assert(NULL != pAlgObj->memRec[cnt].base);
                }
                break;

            case IALG_DARAM0:
                /* on EVE it is DMEM */
                pAlgObj->memRec[cnt].base = Utils_memAlloc(
                                                UTILS_HEAPID_L2_LOCAL,
                                                pAlgObj->memRec[cnt].size,
                                                pAlgObj->memRec[cnt].alignment);
                UTILS_assert(NULL != pAlgObj->memRec[cnt].base);
                break;

            case IALG_DARAM1:
#ifdef BUILD_DSP
                /* on DSP it is L2 heap */
                heapId = UTILS_HEAPID_L2_LOCAL;
#else
                heapId = UTILS_HEAPID_DDR_CACHED_SR;
#endif

                pAlgObj->memRec[cnt].base = Utils_memAlloc(
                                                heapId,
                                                pAlgObj->memRec[cnt].size,
                                                pAlgObj->memRec[cnt].alignment);
                UTILS_assert(NULL != pAlgObj->memRec[cnt].base);
                break;

            default:
                /* Allocate memory from the DDR */
                if(cnt == 0)
                {
                    /*  First memRec is algorithm handle */
                    /*  It is allocated from Local DDR */
                    heapId = UTILS_HEAPID_DDR_CACHED_LOCAL;
                }
                else
                {
                    heapId = UTILS_HEAPID_DDR_CACHED_SR;
                }

                pAlgObj->memRec[cnt].base = Utils_memAlloc(
                                                heapId,
                                                pAlgObj->memRec[cnt].size,
                                                pAlgObj->memRec[cnt].alignment);
                UTILS_assert(NULL != pAlgObj->memRec[cnt].base);

                break;
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tidlAlgMemFree(AlgorithmLink_tidlObj *pAlgObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    Utils_HeapId heapId;
    AlgorithmLink_tidlCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;

    for(cnt = 0;cnt < pAlgObj->numMemRec;cnt ++)
    {
        switch(pAlgObj->memRec[cnt].space)
        {
            case IALG_SARAM0:
                if(NULL == pLinkCreatePrms->ocmcAddr)
                {
                    Utils_memFree(
                        UTILS_HEAPID_DDR_CACHED_SR,
                        pAlgObj->memRec[cnt].base,
                        pAlgObj->memRec[cnt].size);
                }
                break;

            case IALG_DARAM0:
                Utils_memFree(
                    UTILS_HEAPID_L2_LOCAL,
                    pAlgObj->memRec[cnt].base,
                    pAlgObj->memRec[cnt].size);
                break;

            case IALG_DARAM1:
#ifdef BUILD_DSP
                heapId = UTILS_HEAPID_L2_LOCAL;
#else
                heapId = UTILS_HEAPID_DDR_CACHED_SR;
#endif
                Utils_memFree(
                    heapId,
                    pAlgObj->memRec[cnt].base,
                    pAlgObj->memRec[cnt].size);

                break;

            default:
                if(cnt == 0)
                {
                    /*  First memRec is algorithm handle */
                    /*  It is allocated from Local DDR */
                    heapId = UTILS_HEAPID_DDR_CACHED_LOCAL;
                }
                else
                {
                    heapId = UTILS_HEAPID_DDR_CACHED_SR;
                }

                Utils_memFree(
                        heapId,
                        pAlgObj->memRec[cnt].base,
                        pAlgObj->memRec[cnt].size);

                break;
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tidlCacheInvNetBuf(sTIDL_Network_t *net)
{
    UInt32 i, dataSize;

    Cache_inv(
        (UInt8*)net,
        sizeof(sTIDL_Network_t),
        Cache_Type_ALLD,
        TRUE);

    for(i = 0; i < net->numLayers; i++)
    {
        if((TIDL_ConvolutionLayer == net->TIDLLayers[i].layerType) ||
           (TIDL_Deconv2DLayer == net->TIDLLayers[i].layerType))
        {
            dataSize = \
                (net->TIDLLayers[i].layerParams.convParams.numInChannels * \
                    net->TIDLLayers[i].layerParams.convParams.numOutChannels * \
                    net->TIDLLayers[i].layerParams.convParams.kernelW * \
                    net->TIDLLayers[i].layerParams.convParams.kernelH)/ \
                    net->TIDLLayers[i].layerParams.convParams.numGroups;

            Cache_inv(
                (UInt8*)net->TIDLLayers[i].layerParams.convParams.weights.ptr,
                dataSize,
                Cache_Type_ALLD,
                TRUE);

            if(net->TIDLLayers[i].layerParams.convParams.enableBias)
            {
                dataSize = \
                    net->TIDLLayers[i].layerParams.convParams.numOutChannels;

                Cache_inv(
                    (UInt8*)net->TIDLLayers[i].layerParams.convParams.bias.ptr,
                    dataSize * 2,
                    Cache_Type_ALLD,
                    TRUE);
            }
        }
        else if(TIDL_BiasLayer == net->TIDLLayers[i].layerType)
        {
            dataSize = net->TIDLLayers[i].layerParams.biasParams.numChannels;

            Cache_inv(
                (UInt8*)net->TIDLLayers[i].layerParams.biasParams.bias.ptr,
                dataSize * 2,
                Cache_Type_ALLD,
                TRUE);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tidlIsInDataBuff(
                    sTIDL_Network_t *pTIDLNetStructure,
                    Int32 dataId,
                    Int32 layersGroupId)
{
    Int32 i, j;

    for(i = 0 ; i < pTIDLNetStructure->numLayers; i++)
    {
        for(j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
        {
            if((pTIDLNetStructure->TIDLLayers[i].layersGroupId == layersGroupId) &&
               (pTIDLNetStructure->TIDLLayers[i].inData[j].dataId == dataId))
            {
                return 1;
            }
        }
    }

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static UInt32 tidlGetNumInputBuffers(
                    AlgorithmLink_tidlObj *pAlgObj,
                    sTIDL_Network_t *net,
                    IVISION_BufDesc *BufDescList,
                    UInt32 layersGroupId)
{
    Int32 i, j;
    UInt16 numBuffs = 0;
    UInt16 tidlMaxPad = TIDL_MAX_PAD_SIZE;

    for(i = 0; i < net->numLayers; i++)
    {
        if(net->TIDLLayers[i].layersGroupId != layersGroupId)
        {

            for(j = 0; j < net->TIDLLayers[i].numOutBufs; j++)
            {
                if(tidlIsInDataBuff(net, net->TIDLLayers[i].outData[j].dataId, layersGroupId))
                {
                    BufDescList[numBuffs].numPlanes = 1;
                    BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.x = 0;
                    BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.y = 0;

                    BufDescList[numBuffs].bufPlanes[0].width = \
                                net->TIDLLayers[i].outData[j].dimValues[3] + (2 * tidlMaxPad);
                    BufDescList[numBuffs].bufPlanes[0].height = \
                                net->TIDLLayers[i].outData[j].dimValues[1] * \
                                    (net->TIDLLayers[i].outData[j].dimValues[2] + (2 * tidlMaxPad));
                    BufDescList[numBuffs].bufPlanes[0].frameROI.width = net->TIDLLayers[i].outData[j].dimValues[3];
                    BufDescList[numBuffs].bufPlanes[0].frameROI.height = net->TIDLLayers[i].outData[j].dimValues[2];
                    BufDescList[numBuffs].bufferId = net->TIDLLayers[i].outData[j].dataId;

                    pAlgObj->inBufSize[numBuffs] = \
                        BufDescList[numBuffs].bufPlanes[0].width * BufDescList[numBuffs].bufPlanes[0].height;

                    numBuffs++;
                }
            }
        }
    }

    return numBuffs;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tidlIsOutDataBuff(
                        sTIDL_Network_t *pTIDLNetStructure,
                        Int32 dataId,
                        Int32 layersGroupId)
{
    Int32 i,j;

    for(i = 0 ; i < pTIDLNetStructure->numLayers; i++)
    {
        for(j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
        {
            if((pTIDLNetStructure->TIDLLayers[i].layersGroupId != layersGroupId) &&
               (pTIDLNetStructure->TIDLLayers[i].inData[j].dataId == dataId))
            {
                return 1;
            }
        }
    }

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static UInt32 tidlGetNumOutputBuffers(
                    AlgorithmLink_tidlObj *pAlgObj,
                    sTIDL_Network_t *net,
                    IVISION_BufDesc *BufDescList,
                    UInt32 layersGroupId)
{
    Int32 i, j;
    UInt16 numBuffs = 0;
    UInt16 tidlMaxPad = TIDL_MAX_PAD_SIZE;

    for(i = 0; i < net->numLayers; i++)
    {
        if(net->TIDLLayers[i].layersGroupId == layersGroupId)
        {
            for(j = 0; j < net->TIDLLayers[i].numOutBufs; j++)
            {
                if(tidlIsOutDataBuff(net, net->TIDLLayers[i].outData[j].dataId, layersGroupId))
                {
                    BufDescList[numBuffs].numPlanes = 1;
                    BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.x = 0;
                    BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.y = 0;

                    BufDescList[numBuffs].bufPlanes[0].width = \
                            net->TIDLLayers[i].outData[j].dimValues[3] + (2 * tidlMaxPad);
                    BufDescList[numBuffs].bufPlanes[0].height = \
                            net->TIDLLayers[i].outData[j].dimValues[1] * \
                                (net->TIDLLayers[i].outData[j].dimValues[2] + (2 * tidlMaxPad));
                    BufDescList[numBuffs].bufPlanes[0].frameROI.width = net->TIDLLayers[i].outData[j].dimValues[3];
                    BufDescList[numBuffs].bufPlanes[0].frameROI.height = net->TIDLLayers[i].outData[j].dimValues[2];
                    BufDescList[numBuffs].bufferId = net->TIDLLayers[i].outData[j].dataId;

                    pAlgObj->outBufSize[numBuffs] = net->TIDLLayers[i].outData[j].pitch[0];

                    numBuffs++;
                }
            }
        }
    }

    return numBuffs;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to putEmptyCb()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 tidlCacheWb(UInt32 addr, UInt32 size)
{
    Cache_wb(
        (Ptr)addr,
        size,
        Cache_Type_ALL,
        TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tidlAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tidlCreateAlgInstance(AlgorithmLink_tidlObj *pAlgObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, algStatus;
    UInt32 buffCnt;
    AlgorithmLink_tidlCreateParams *pLinkCreatePrms = \
                        &pAlgObj->algLinkCreateParams;
    TIDL_CreateParams *pAlgCreateParams = \
            (TIDL_CreateParams*)pLinkCreatePrms->pAlgCreateParams;

    /* Cache Invalidate the Net buffers read by the use case */
    tidlCacheInvNetBuf(&pAlgCreateParams->net);

    pAlgCreateParams->visionParams.algParams.size = \
                                                    sizeof(TIDL_CreateParams);
    if((TRUE == pLinkCreatePrms->cacheInvInBuf) &&
       (TRUE == pLinkCreatePrms->cacheWbOutBuf))
    {
        pAlgCreateParams->visionParams.cacheWriteBack = tidlCacheWb;
    }
    else
    {
        pAlgCreateParams->visionParams.cacheWriteBack = NULL;
    }

#ifdef BUILD_DSP
    pAlgCreateParams->l1MemSize = TIDL_LINK_MIN_DSPL1_SIZE;
    pAlgCreateParams->l2MemSize = UTILS_MEM_HEAP_L2_SIZE - (64 * KB);
#else
    pAlgCreateParams->l1MemSize = (UTILS_MEM_HEAP_L2_SIZE - (1 * KB));
    pAlgCreateParams->l2MemSize = TIDL_LINK_MIN_EVEL2_SIZE;
#endif
    pAlgCreateParams->l3MemSize = TIDL_LINK_MIN_L3_SIZE;

    pAlgCreateParams->quantHistoryParam1   = 20;
    pAlgCreateParams->quantHistoryParam2   = 5;
    pAlgCreateParams->quantMargin          = 0;
    pAlgCreateParams->optimiseExtMem       = TIDL_optimiseExtMemL1;
    pAlgCreateParams->net.interElementSize = 4;

    pAlgCreateParams->currCoreId = pLinkCreatePrms->curCoreId;
    pAlgCreateParams->currLayersGroupId = pLinkCreatePrms->currLayersGroupId;

    pAlgObj->numMemRec = TIDL_VISION_FXNS.ialg.algNumAlloc();
    pAlgObj->memRecSize = pAlgObj->numMemRec * sizeof(IALG_MemRec);
    pAlgObj->memRec = (IALG_MemRec*)Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                        pAlgObj->memRecSize,
                                        128);
    UTILS_assert(NULL != pAlgObj->memRec);

    algStatus = TIDL_VISION_FXNS.ialg.algAlloc(
                                (IALG_Params*)(pAlgCreateParams),
                                NULL,
                                pAlgObj->memRec);
    if(IALG_EOK != algStatus)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        status = tidlAlgMemAlloc(pAlgObj);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        pAlgObj->handle = (IM_Fxns*)pAlgObj->memRec[0].base;

        algStatus = TIDL_VISION_FXNS.ialg.algInit(
                                    (IALG_Handle)(&pAlgObj->handle),
                                    pAlgObj->memRec,
                                    NULL,
                                    (IALG_Params *)(pAlgCreateParams));
        UTILS_assert(IALG_EOK == algStatus);

        /* Query the no of input and output buffers */
        pAlgObj->numInputBuffers = tidlGetNumInputBuffers(
                                        pAlgObj,
                                        &pAlgCreateParams->net,
                                        pAlgObj->inBufDesc,
                                        pLinkCreatePrms->currLayersGroupId);
        pAlgObj->numInputQueues = 1;

        /* Currently in algplugin number of input Q is set to 1 only
           Need to have a get numInPutQueue in case of enhancement  */

        for (buffCnt = 0;buffCnt < pAlgObj->numInputBuffers;buffCnt++)
        {
            pAlgObj->inBufDescList[buffCnt] = &pAlgObj->inBufDesc[buffCnt];
        }

        pAlgObj->numOutputBuffers = tidlGetNumOutputBuffers(
                                        pAlgObj,
                                        &pAlgCreateParams->net,
                                        pAlgObj->outBufDesc,
                                        pLinkCreatePrms->currLayersGroupId);
        pAlgObj->numOutputQueues = 1;
        /* Currently in algplugin number of output Q is set to 1 only
           Need to have a get numOutputQueue in case of enhancement  */

        for (buffCnt = 0;buffCnt < pAlgObj->numOutputBuffers;buffCnt++)
        {
            pAlgObj->outBufDescList[buffCnt] = &pAlgObj->outBufDesc[buffCnt];
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to create()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlCreate(void *pObj,void *pCreateParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, bufIdx, index,buffCnt;
    AlgorithmLink_tidlObj *pAlgObj;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_Buffer *pSystemBuffer;
    System_MetaDataBuffer *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_tidlObj*)Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                        sizeof(AlgorithmLink_tidlObj),
                                        128);
    UTILS_assert(NULL != pAlgObj);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    /* Save the create parameters */
    memcpy(
        &pAlgObj->algLinkCreateParams,
        pCreateParams,
        sizeof(AlgorithmLink_tidlCreateParams));

    /*********************************************************/
    /*              TIDL ALG CREATE                          */
    /*********************************************************/
    tidlCreateAlgInstance(pAlgObj);
    /*********************************************************/

    /* Create temp queues for input buffers */
    for(queId = 0;queId < pAlgObj->numInputQueues;queId++)
    {
        status = Utils_queCreate(
                    &pAlgObj->tmpInQueue[queId].queHandle,
                    ALGORITHM_LINK_MAX_QUEUELENGTH,
                    &pAlgObj->tmpInQueue[queId].queMem,
                    UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        pAlgObj->inBufList[queId] = NULL;
    }

    /* Create output empty queues */
    pOutputQInfo = &pAlgObj->outputQInfo[0];
    for(queId = 0;queId < pAlgObj->numOutputQueues;queId++)
    {
        pOutputQInfo[queId].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
        pOutputQInfo[queId].queInfo.numCh = 1;
    }

    AlgorithmLink_queueInfoInit(
                        pObj,
                        0,
                        NULL,
                        pAlgObj->numOutputQueues,
                        pOutputQInfo);

    /* Allocate output buffers and queue them in the empty queues */
    for(queId = 0;queId < pAlgObj->numOutputQueues;queId++)
    {
        for(bufIdx = 0;bufIdx < TIDL_LINK_NUM_BUF_QUEUE;bufIdx++)
        {
            index = (queId * TIDL_LINK_NUM_BUF_QUEUE) + bufIdx;
            pSystemBuffer = &pAlgObj->buffers[index];
            pMetaDataBuffer = &pAlgObj->metaDataBuffers[index];

            pSystemBuffer->bufType = SYSTEM_BUFFER_TYPE_METADATA;
            pSystemBuffer->payload = pMetaDataBuffer;
            pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
            pSystemBuffer->chNum = 0;

            pMetaDataBuffer->numMetaDataPlanes = 1;
            pMetaDataBuffer->metaBufSize[0] = 0;

            for(buffCnt = 0 ; buffCnt < pAlgObj->numOutputBuffers; buffCnt++)
            {
                pMetaDataBuffer->metaBufSize[0] += pAlgObj->outBufSize[buffCnt];
            }

            if (index == 0)
                pMetaDataBuffer->metaBufSize[0] = pMetaDataBuffer->metaBufSize[0] + OUTPUT_OFFSET_SIZE + (4 * TIDL_MAX_ALG_OUT_BUFS);
            else
                pMetaDataBuffer->metaBufSize[0] = pMetaDataBuffer->metaBufSize[0] + OUTPUT_OFFSET_SIZE;

            pMetaDataBuffer->bufAddr[0] = Utils_memAlloc(
                                            UTILS_HEAPID_DDR_CACHED_SR,
                                            pMetaDataBuffer->metaBufSize[0],
                                            128);
            UTILS_assert(NULL != pMetaDataBuffer->bufAddr[0]);

            /* Put empty buffer to empty queue */
            status = AlgorithmLink_putEmptyOutputBuffer(
                                            pObj,
                                            queId,
                                            pSystemBuffer);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }

        pAlgObj->outBufList[queId] = NULL;
    }

    pAlgObj->numInBufReceived = 0;
    pAlgObj->numOutBufReceived = 0;

    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
                                            AlgorithmLink_getLinkId(pObj),
                                            "ALG_TIDL");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    pAlgObj->isFirstFrameRecv = FALSE;

    /*  Register a call back function for put empty buffers where we can send
        NEW_DATA_CMD to process pending buffers in the temp queue */
    AlgorithmLink_registerPutEmptyBuffersPlugin(pObj, putEmptyCb);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to delete()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlDelete(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, algStatus;
    UInt32 queId, bufIdx, index;
    System_MetaDataBuffer *pMetaDataBuffer;
    AlgorithmLink_tidlObj *pAlgObj = \
            (AlgorithmLink_tidlObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);

    /*********************************************************/
    /*              TIDL ALG DELETE                          */
    /*********************************************************/
    algStatus = pAlgObj->handle->ivision->ialg.algFree(
                                                (IALG_Handle)(pAlgObj->handle),
                                                pAlgObj->memRec);
    UTILS_assert(IALG_EOK == algStatus);

    status = tidlAlgMemFree(pAlgObj);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                    pAlgObj->memRec,
                    pAlgObj->memRecSize);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    /*********************************************************/

    /* Delete the temp input buffer queues */
    for(queId = 0;queId < pAlgObj->numInputQueues;queId++)
    {
        status = Utils_queDelete(&pAlgObj->tmpInQueue[queId].queHandle);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    /* There is no alg queue deinit function defined */

    /* Free the output buffers */
    for(queId = 0;queId < pAlgObj->numOutputQueues;queId++)
    {
        for(bufIdx = 0;bufIdx < TIDL_LINK_NUM_BUF_QUEUE;bufIdx++)
        {
            index = (queId * TIDL_LINK_NUM_BUF_QUEUE) + bufIdx;
            pMetaDataBuffer = &pAlgObj->metaDataBuffers[index];

            if (index == 0)
                pMetaDataBuffer->bufAddr[0] = (void *)((char *)pMetaDataBuffer->bufAddr[0] - (4 * TIDL_MAX_ALG_OUT_BUFS));

            status = Utils_memFree(
                            UTILS_HEAPID_DDR_CACHED_SR,
                            pMetaDataBuffer->bufAddr[0],
                            pMetaDataBuffer->metaBufSize[0]);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }
    }

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                    pAlgObj,
                    sizeof(AlgorithmLink_tidlObj));
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to process()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlProcess(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, algStatus;
    UInt32 queId, bufIdx,offsetSize,buffCnt,buffsize;
    System_BufferList inputBufList;
    System_BufferList bufListReturn;
    System_Buffer *pSysBuffer;
    System_MetaDataBuffer *pMetaDataBuf;
    System_VideoFrameBuffer *pVidDataBuf;
    Void *inBufAddr[TIDL_LINK_MAX_NUM_BUFFERS], *outBufAddr[TIDL_LINK_MAX_NUM_BUFFERS];
    AlgorithmLink_tidlObj *pAlgObj = \
            (AlgorithmLink_tidlObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    AlgorithmLink_tidlCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;
    System_LinkStatistics *linkStatsInfo = pAlgObj->linkStatsInfo;

    TIDL_InArgs inArgs;
    TIDL_outArgs outArgs;
    IVISION_InBufs inBufs;
    IVISION_OutBufs outBufs;

#ifdef RT_DEBUG
    UInt64 tsc_start, tsc_cycles;
#endif

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pAlgObj->isFirstFrameRecv == FALSE)
    {
        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    /* Get all the input buffers */
    for (queId = 0;queId < pAlgObj->numInputQueues;queId++)
    {
        /* Dequeue the buffer only if not yet received */
        if(NULL == pAlgObj->inBufList[queId])
        {
            if(0 != \
                Utils_queGetQueuedCount(&pAlgObj->tmpInQueue[queId].queHandle))
            {
                /* There are full buffers in the temp input queue */
                status = Utils_queGet(
                                &pAlgObj->tmpInQueue[queId].queHandle,
                                (Ptr*)&pAlgObj->inBufList[queId],
                                1U,
                                BSP_OSAL_NO_WAIT);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                pAlgObj->numInBufReceived ++;
            }
            else
            {
                /*  Temp input queue is empty get the full buffers from
                    previous links */
                System_getLinksFullBuffers(
                            pLinkCreatePrms->inQueParams[queId].prevLinkId,
                            pLinkCreatePrms->inQueParams[queId].prevLinkQueId,
                            &inputBufList);

                if(inputBufList.numBuf > 0)
                {
                    pAlgObj->inBufList[queId] = inputBufList.buffers[0];

                    pAlgObj->numInBufReceived++;

                    /*  If more than 1 buffers dequeued then queue them in temp
                        input queue */
                    for (bufIdx = 1;bufIdx < inputBufList.numBuf;bufIdx++)
                    {
                        status = Utils_quePut(
                                      &pAlgObj->tmpInQueue[queId].queHandle,
                                      inputBufList.buffers[bufIdx],
                                      BSP_OSAL_NO_WAIT);
                        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
                    }

                    linkStatsInfo->linkStats.chStats[queId].inBufRecvCount += \
                                                        inputBufList.numBuf;
                }
            }
        }
    }

    if(pAlgObj->numInBufReceived == pAlgObj->numInputQueues)
    {
        /*  All the required input buffers are received now get all the output
            buffers */
        for (queId = 0;queId < pAlgObj->numOutputQueues;queId++)
        {
            if(NULL == pAlgObj->outBufList[queId])
            {
                status = AlgorithmLink_getEmptyOutputBuffer(
                                                pObj,
                                                queId,
                                                0,
                                                &pAlgObj->outBufList[queId]);
                if(SYSTEM_LINK_STATUS_SOK == status)
                {
                    pAlgObj->numOutBufReceived++;

                    /*  Using the source time stamp of the first input buffer for all
                        the output buffers */
                    pAlgObj->outBufList[queId]->frameId = \
                                        pAlgObj->inBufList[queId]->frameId;

                    pAlgObj->outBufList[queId]->srcTimestamp = \
                                        pAlgObj->inBufList[queId]->srcTimestamp;
                    pAlgObj->outBufList[queId]->linkLocalTimestamp = \
                                        Utils_getCurGlobalTimeInUsec();

                    pSysBuffer = pAlgObj->outBufList[queId];
                    pMetaDataBuf = (System_MetaDataBuffer*)pSysBuffer->payload;

                    if (pAlgObj->isFirstFrameRecv == FALSE)
                    {
                        memcpy(pMetaDataBuf->bufAddr[0], (void *)(pAlgObj->outBufSize), (4 * TIDL_MAX_ALG_OUT_BUFS));
                        pMetaDataBuf->bufAddr[0] = (void *)((char *)pMetaDataBuf->bufAddr[0] + (4 * TIDL_MAX_ALG_OUT_BUFS));
                    }
                    outBufAddr[queId] = (void *)((UInt32)pMetaDataBuf->bufAddr[0]);
                    /* 1st buff is the start address*/
                    pAlgObj->outBufDesc[0].bufPlanes[0].buf = outBufAddr[queId];
                    buffsize = 0;
                    for(buffCnt = 1; buffCnt < pAlgObj->numOutputBuffers; buffCnt++)
                    {
                        buffsize += pAlgObj->outBufSize[buffCnt-1];
                    /* increment the buffaddr by the previous buff size*/
                        pAlgObj->outBufDesc[buffCnt].bufPlanes[0].buf = \
                            (void*)((UInt32)outBufAddr[queId] + buffsize);
                    }
                }
            }
        }

        if(pAlgObj->numOutBufReceived == pAlgObj->numOutputQueues)
        {
            /* All the input and output buffers are available */
            for (queId = 0;queId < pAlgObj->numInputQueues;queId++)
            {
                pSysBuffer = pAlgObj->inBufList[queId];
                if(SYSTEM_BUFFER_TYPE_METADATA == pSysBuffer->bufType)
                {
                    pMetaDataBuf = (System_MetaDataBuffer*)pSysBuffer->payload;
                    inBufAddr[queId] = pMetaDataBuf->bufAddr[0];
                    if (pAlgObj->isFirstFrameRecv == FALSE)
                    {
                        memcpy((void *)pAlgObj->inBufSize, (void *)((UInt32)pMetaDataBuf->bufAddr[0] - (4 * TIDL_MAX_ALG_OUT_BUFS)), (4 * TIDL_MAX_ALG_OUT_BUFS));
                    }
                }
                else if(SYSTEM_BUFFER_TYPE_VIDEO_FRAME == pSysBuffer->bufType)
                {
                    pVidDataBuf = (System_VideoFrameBuffer*)pSysBuffer->payload;
                    inBufAddr[queId] = pVidDataBuf->bufAddr[0];
                }

                if(TRUE == pLinkCreatePrms->cacheInvInBuf)
                {
                    Cache_inv(
                        inBufAddr[queId],
                        pAlgObj->inBufSize[queId],
                        Cache_Type_ALL,
                        TRUE);
                }

                pAlgObj->inBufDesc[0].bufPlanes[0].buf = inBufAddr[queId];
                buffsize = 0;
                for(buffCnt = 1; buffCnt < pAlgObj->numInputBuffers; buffCnt++)
                {
                    buffsize += pAlgObj->inBufSize[buffCnt-1];
                    pAlgObj->inBufDesc[buffCnt].bufPlanes[0].buf = \
                            (void*)((UInt32)inBufAddr[queId] + buffsize);
                }
            }

            offsetSize = (pMetaDataBuf->metaBufSize[0] - OUTPUT_DATAQ_SIZE);
            /********************************
             *     ALG PROCESS START        *
             ********************************/
            inBufs.numBufs = pAlgObj->numInputBuffers;
            inBufs.bufDesc = pAlgObj->inBufDescList;

            outBufs.numBufs = pAlgObj->numOutputBuffers;
            outBufs.bufDesc = pAlgObj->outBufDescList;

            inArgs.iVisionInArgs.size = sizeof(TIDL_InArgs);
            inArgs.iVisionInArgs.subFrameInfo = 0;

            outArgs.iVisionOutArgs.size = sizeof(TIDL_outArgs);
            if(SYSTEM_BUFFER_TYPE_METADATA == pSysBuffer->bufType)
            {
                memcpy(&inArgs.dataQ[0],(Int32*)((Int32)(pMetaDataBuf->bufAddr[0]) + offsetSize),(OUTPUT_DATAQ_SIZE));
            }
#ifdef RT_DEBUG
#ifdef BUILD_DSP
            _TSC_enable();
            tsc_start = (UInt64)_TSC_read();
#else
            tsc_start = _tsc_gettime();
#endif
#endif
            algStatus = pAlgObj->handle->ivision->algProcess(
                                    (IVISION_Handle)pAlgObj->handle,
                                    &inBufs,
                                    &outBufs,
                                    (IVISION_InArgs*)&inArgs,
                                    (IVISION_OutArgs*)&outArgs);
            UTILS_assert(IALG_EFAIL != algStatus);

            if(SYSTEM_BUFFER_TYPE_VIDEO_FRAME == pSysBuffer->bufType)
            {
                /* In case of eve metadata is present only for output*/
                memcpy((Int32*)((Int32)pMetaDataBuf->bufAddr[0] + offsetSize),&outArgs.dataQ[0],(OUTPUT_DATAQ_SIZE));
            }
#ifdef RT_DEBUG
#ifdef BUILD_DSP
            tsc_cycles   = (UInt64)_TSC_read() - tsc_start;
#else
            tsc_cycles   = _tsc_gettime() - tsc_start;
#endif
            Vps_printf("#### tsc_cycles = %ld\n",tsc_cycles);
#endif
            /********************************
             *     ALG PROCESS END          *
             ********************************/

            for (queId = 0;queId < pAlgObj->numOutputQueues;queId++)
            {
                if(SYSTEM_BUFFER_TYPE_METADATA == pSysBuffer->bufType)
                {
                    UInt32 offsetMetadata;

                    offsetMetadata = pAlgObj->outBufDescList[0][0].bufPlanes[0].width;
                    pSysBuffer = pAlgObj->outBufList[queId];
                    pMetaDataBuf = (System_MetaDataBuffer*)pSysBuffer->payload;

                    *(UInt32*)((UInt32)pMetaDataBuf->bufAddr[0]) = offsetMetadata;
                }

                if(TRUE == pLinkCreatePrms->cacheWbOutBuf)
                {
                    Cache_wb(
                        pMetaDataBuf->bufAddr[0],
                        pMetaDataBuf->metaBufSize[0],
                        Cache_Type_ALL,
                        TRUE);
                }

                Utils_updateLatency(
                                &linkStatsInfo->linkLatency,
                                pAlgObj->outBufList[queId]->linkLocalTimestamp);
                Utils_updateLatency(
                                &linkStatsInfo->srcToLinkLatency,
                                pAlgObj->outBufList[queId]->srcTimestamp);

                linkStatsInfo->linkStats.chStats[queId].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats[queId].outBufCount[0]++;

                status = AlgorithmLink_putFullOutputBuffer(
                                                    pObj,
                                                    queId,
                                                    pAlgObj->outBufList[queId]);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                /* Notify the next link */
                System_sendLinkCmd(
                            pLinkCreatePrms->outQueParams[queId].nextLink,
                            SYSTEM_CMD_NEW_DATA,
                            NULL);

                bufListReturn.numBuf = 1;
                bufListReturn.buffers[0] = pAlgObj->outBufList[queId];
                status = AlgorithmLink_releaseOutputBuffer(
                                                   pObj,
                                                   queId,
                                                   &bufListReturn);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                pAlgObj->outBufList[queId] = NULL;
            }

            /* Release the input buffers back to the previous links */
            for (queId = 0;queId < pAlgObj->numInputQueues;queId++)
            {
                inputBufList.numBuf = 1;
                inputBufList.buffers[0] = pAlgObj->inBufList[queId];

                System_putLinksEmptyBuffers(
                                pLinkCreatePrms->inQueParams[queId].prevLinkId,
                                pLinkCreatePrms->inQueParams[queId].prevLinkQueId,
                                &inputBufList);

                pAlgObj->inBufList[queId] = NULL;
            }

            pAlgObj->numInBufReceived = 0;
            pAlgObj->numOutBufReceived = 0;
        }
    }
    if (pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to print statistics()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlPrintStatistics(void *pObj,AlgorithmLink_tidlObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(
                    &pAlgObj->linkStatsInfo->linkStats,
                    "ALG_TIDL",
                    TRUE);

    Utils_printLatency(
                    "ALG_TIDL",
                    &pAlgObj->linkStatsInfo->linkLatency,
                    &pAlgObj->linkStatsInfo->srcToLinkLatency,
                    TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to control()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlControl(void *pObj,void *pControlParams)
{
    AlgorithmLink_tidlObj *pAlgObj;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;

    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgorithmLink_tidlObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */

    switch(pAlgLinkControlPrm->controlCmd)
    {
        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_tidlPrintStatistics(pObj, pAlgObj);
            break;

        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to stop()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidlStop(void *pObj)
{
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of gAlign algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tidl_initPluginDsp(Void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate = AlgorithmLink_tidlCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = AlgorithmLink_tidlProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = AlgorithmLink_tidlControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop = AlgorithmLink_tidlStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete = AlgorithmLink_tidlDelete;

    algId = ALGORITHM_LINK_DSP_ALG_TIDL;
    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmLink_tidl_initPluginEve(Void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate = AlgorithmLink_tidlCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = AlgorithmLink_tidlProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = AlgorithmLink_tidlControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop = AlgorithmLink_tidlStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete = AlgorithmLink_tidlDelete;

    algId = ALGORITHM_LINK_EVE_ALG_TIDL;
    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/* Dummy fn remove later */
Void profiler_init(Void)
{
    return;
}

