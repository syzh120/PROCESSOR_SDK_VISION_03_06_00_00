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
 * \file tiopLink_algPlugin.c
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
#include "tiopLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_mem_cfg.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */
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
 * \brief Implementation of function to tiopGetNumInputBuffers()
 * \return  Number of buffers
 *
 *******************************************************************************
 */
static Int32 tiopGetNumInputBuffers(AlgorithmLink_tiopObj *pAlgObj,
                                            TIOP_CreateParams *pAlgCreateParams, 
                                            IVISION_BufDesc   *BufDescList)
{
    Int32 i;
    UInt16 numBuffs = 0;

    for(i = 0; i < TIOP_INPUT_TOTAL_FRAMES; i++)
    {
        /* In each input, one buffer is for input frame data and one for 
           to hold it's dectection list */
        BufDescList[numBuffs].numPlanes  = TIOP_IN_BUFDESC_TOTAL;

        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.topLeft.x = 0;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.topLeft.y = 0;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.width = \
            pAlgCreateParams->inMaxWidth;;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.height = \
            pAlgCreateParams->inMaxHeight;

        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].width = pAlgCreateParams->inMaxWidth;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].height = pAlgCreateParams->inMaxHeight;

        pAlgObj->inBufSize[numBuffs][TIOP_IN_BUFDESC_INPUT_FRAME] = \
            BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].width * BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].height;

        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.topLeft.x = 0;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.topLeft.y = 0;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.width = \
            TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.height = 1;

        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].width = \
            TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].height = 1;

        pAlgObj->inBufSize[numBuffs][TIOP_IN_BUFDESC_DETECTION_LIST] = \
            BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].width * BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].height;

        BufDescList[numBuffs].bufferId = (i+1); // Should start with 1     
        numBuffs++;
    }
    return numBuffs;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to tiopGetNumOutputBuffers()
 * \return  Number of buffers
 *
 *******************************************************************************
 */
static Int32 tiopGetNumOutputBuffers(AlgorithmLink_tiopObj *pAlgObj,
                                             IVISION_BufDesc   *BufDescList)
{
    Int32 numBuffs = 0;

    BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.topLeft.x = 0;
    BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.topLeft.y = 0;
    BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.width = \
        TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
    BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.height = 1;

    BufDescList[numBuffs].numPlanes  = TIOP_OUT_BUFDESC_TOTAL;
    BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].width = 
        TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
    BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].height = 1; 
    pAlgObj->outBufSize[numBuffs] = \
        BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].width * BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].height;

    return 1;
}

 /**
 *******************************************************************************
 *
 * \brief Implementation of function to tiopAlgMemAlloc()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tiopAlgMemAlloc(AlgorithmLink_tiopObj *pAlgObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    Utils_HeapId heapId;

    for(cnt = 0;cnt < pAlgObj->numMemRec;cnt ++)
    {
        switch(pAlgObj->memRec[cnt].space)
        {
            case IALG_DARAM0:
                pAlgObj->memRec[cnt].base = Utils_memAlloc(
                                                UTILS_HEAPID_L2_LOCAL,
                                                pAlgObj->memRec[cnt].size,
                                                pAlgObj->memRec[cnt].alignment);
                UTILS_assert(NULL != pAlgObj->memRec[cnt].base);
                break;

            case IALG_DARAM1:
                if (cnt == 4)
                {
                    /* We use address of TIDL L2Heap memory for larger L2 memory allocation */
                    pAlgObj->memRec[cnt].base = (void *)0x00800500;
                    break;
                }
                pAlgObj->memRec[cnt].base = Utils_memAlloc(
                                                UTILS_HEAPID_L2_LOCAL,
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
 * \brief Implementation of function to tiopAlgMemFree()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tiopAlgMemFree(AlgorithmLink_tiopObj *pAlgObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cnt;
    Utils_HeapId heapId;

    for(cnt = 0;cnt < pAlgObj->numMemRec;cnt ++)
    {
        switch(pAlgObj->memRec[cnt].space)
        {
            case IALG_DARAM0:
                Utils_memFree(
                    UTILS_HEAPID_L2_LOCAL,
                    pAlgObj->memRec[cnt].base,
                    pAlgObj->memRec[cnt].size);
                break;

            case IALG_DARAM1:
                if (cnt == 4)
                {
                    /* For larger L2 memory allocation is not done so no need to free this memory */
                    break;
                }
                Utils_memFree(
                    UTILS_HEAPID_L2_LOCAL,
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
 * \brief Implementation of function to tiopCreateAlgInstance()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 tiopCreateAlgInstance(AlgorithmLink_tiopObj *pAlgObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, algStatus;
    UInt32 buffCnt;
    AlgorithmLink_tiopCreateParams *pLinkCreatePrms = \
                        &pAlgObj->algLinkCreateParams;
    TIOP_CreateParams *pAlgCreateParams = \
            (TIOP_CreateParams*)pLinkCreatePrms->pAlgCreateParams;

    pAlgCreateParams->l1MemSize = TIOP_LINK_MIN_DSPL1_SIZE;
    pAlgCreateParams->l2MemSize = 64 * KB;

    pAlgCreateParams->numInDetections              = 20;
    pAlgCreateParams->extImagePyramidal            = 0;
    pAlgCreateParams->extOpticalFlow               = 0;
    pAlgCreateParams->harrisScoreScalingFactor     = 1310;
    pAlgCreateParams->nmsThresh                    = 286870912;
    pAlgCreateParams->numLevels                    = 4;
    pAlgCreateParams->maxItersLK                   = 10;
    pAlgCreateParams->confScoreGoodObjs            = 0.4;
    pAlgCreateParams->confScoreModObjs             = 0.12;
    pAlgCreateParams->maxOverlapThresh	           = 0.4;
    pAlgCreateParams->maxAgeThresh                 = 30;
    pAlgCreateParams->lkErrThresh                  = 500;
    pAlgCreateParams->numClasses                   = 21;

    pAlgCreateParams->visionParams.algParams.size = \
                                                    sizeof(TIOP_CreateParams);

    pAlgCreateParams->visionParams.cacheWriteBack   = NULL;
    Cache_wbInvAll();

    pAlgObj->numMemRec = TIOP_VISION_FXNS.ialg.algNumAlloc();
    pAlgObj->memRecSize = pAlgObj->numMemRec * sizeof(IALG_MemRec);
    pAlgObj->memRec = (IALG_MemRec*)Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                        pAlgObj->memRecSize,
                                        128);
    UTILS_assert(NULL != pAlgObj->memRec);

    algStatus = TIOP_VISION_FXNS.ialg.algAlloc(
                                (IALG_Params*)(pAlgCreateParams),
                                NULL,
                                pAlgObj->memRec);
    if(IALG_EOK != algStatus)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        status = tiopAlgMemAlloc(pAlgObj);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

        pAlgObj->handle = (IM_Fxns*)pAlgObj->memRec[0].base;

        algStatus = TIOP_VISION_FXNS.ialg.algInit(
                                    (IALG_Handle)(&pAlgObj->handle),
                                    pAlgObj->memRec,
                                    NULL,
                                    (IALG_Params *)(pAlgCreateParams));
        UTILS_assert(IALG_EOK == algStatus);

        /* Query the no of input and output buffers */
        pAlgObj->numInputBuffers = tiopGetNumInputBuffers(
                                        pAlgObj,
                                        pAlgCreateParams,
                                        pAlgObj->inBufDesc);
        pAlgObj->numInputQueues = 1;

        /* Currently in algplugin number of input Q is set to 1 only
           Need to have a get numInPutQueue in case of enhancement  */

        for (buffCnt = 0;buffCnt < pAlgObj->numInputBuffers;buffCnt++)
        {
            pAlgObj->inBufDescList[buffCnt] = &pAlgObj->inBufDesc[buffCnt];
        }

        pAlgObj->numOutputBuffers = tiopGetNumOutputBuffers(
                                          pAlgObj,
                                          pAlgObj->outBufDesc);
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
 * \brief Implementation of function to tiopReleaseLockedBuffer()
 * \return  free buffer on success
 *
 *******************************************************************************
 */
static System_Buffer* tiopReleaseLockedBuffer(AlgorithmLink_tiopObj *pAlgObj, UInt32 buffId[])
{
    UInt32 tmpId;
    tmpId = buffId[0];
    /*
     * Check if the buffer Id = 0 condition has reached. zero is not a 
     * valid buffer Id hence that value is used to identify the end of 
     * buffer array
     */

    if(tmpId == 0)
    {
        return NULL;
    }
    tmpId--;

    /* Set the status of the buffer to FREE */
    pAlgObj->inBufStats[tmpId].status = TIOP_FREE_BUFFER;
    return pAlgObj->inBufStats[tmpId].buffer;
}

 /**
 *******************************************************************************
 *
 * \brief Implementation of function to tiopGetFreeBufferId()
 * \return  free buffer Id on success
 *
 *******************************************************************************
 */
static Int32 tiopGetFreeBufferId(AlgorithmLink_tiopObj *pAlgObj)
{
    UInt32 buffCnt;
    for (buffCnt = 0; buffCnt < pAlgObj->numInputBuffers; buffCnt++)
    {
        if (pAlgObj->inBufStats[buffCnt].status == TIOP_FREE_BUFFER)
        {
            return buffCnt;
        }
    }
    return (-1);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of function to create()
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_tiopCreate(void *pObj,void *pCreateParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 queId, buffCnt;
    AlgorithmLink_tiopObj *pAlgObj;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    AlgorithmLink_InputQueueInfo *pInputQInfo;

    pAlgObj = (AlgorithmLink_tiopObj*)Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                        sizeof(AlgorithmLink_tiopObj),
                                        128);
    UTILS_assert(NULL != pAlgObj);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    /* Save the create parameters */
    memcpy(
        &pAlgObj->algLinkCreateParams,
        pCreateParams,
        sizeof(AlgorithmLink_tiopCreateParams));

    /********************************************** */
    /*              TIOP ALG CREATE                 */
    /************************************************/
    tiopCreateAlgInstance(pAlgObj);
    /************************************************/

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

    pInputQInfo  = &pAlgObj->inputQInfo[0];
    pOutputQInfo = &pAlgObj->outputQInfo[0];

    for(queId = 0;queId < pAlgObj->numInputQueues;queId++)
    {
        pInputQInfo[queId].qMode = ALGORITHM_LINK_QUEUEMODE_INPLACE;
        status = System_linkGetInfo(
                   pAlgObj->algLinkCreateParams.inQueParams[queId].prevLinkId, &pAlgObj->prevLinkInfo[queId]);
    }

    for(queId = 0;queId < pAlgObj->numOutputQueues;queId++)
    {
        pOutputQInfo[queId].qMode = ALGORITHM_LINK_QUEUEMODE_INPLACE;
        pOutputQInfo[queId].queInfo.numCh = 1;

        memcpy(&pOutputQInfo[queId].queInfo,
               &pAlgObj->prevLinkInfo[queId].queInfo
               [pAlgObj->algLinkCreateParams.inQueParams[queId].prevLinkQueId],
               sizeof(pOutputQInfo[queId].queInfo)
              );

        /*
         * If any output buffer Q gets used in INPLACE manner, then
         * outputQInfo.inQueParams and
         * outputQInfo.inputQId need to be populated appropriately.
         */

        memcpy((void*)(&pOutputQInfo[queId].inQueParams),
           (void*)(&pAlgObj->algLinkCreateParams.inQueParams),
            sizeof(pOutputQInfo[queId].inQueParams)
        );
    }

    AlgorithmLink_queueInfoInit(
                        pObj,
                        pAlgObj->numInputQueues,
                        pInputQInfo,
                        pAlgObj->numOutputQueues,
                        pOutputQInfo);

    pAlgObj->numInBufReceived = 0;
    pAlgObj->numOutBufReceived = 0;

    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
                                            AlgorithmLink_getLinkId(pObj),
                                            "ALG_TIOP");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    pAlgObj->isFirstFrameRecv = FALSE;

    for (queId = 0;queId < pAlgObj->numOutputQueues;queId++)
    {
        pAlgObj->metaDataBufSize[queId] = 0;
        for(buffCnt = 0 ; buffCnt < pAlgObj->numOutputBuffers; buffCnt++)
        {
            pAlgObj->metaDataBufSize[queId] += pAlgObj->outBufSize[buffCnt];
        }
        pAlgObj->metaDataBuf[queId] = (void *)Utils_memAlloc(
                                                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                                                        pAlgObj->metaDataBufSize[queId],
                                                        128);
        UTILS_assert(NULL != pAlgObj->metaDataBuf[queId]);
    }
    for (buffCnt = 0; buffCnt < pAlgObj->numInputBuffers; buffCnt++)
    {
        pAlgObj->inBufStats[buffCnt].buffer = NULL;
        pAlgObj->inBufStats[buffCnt].status = TIOP_FREE_BUFFER;
        pAlgObj->inBufStats[buffCnt].bufferId = buffCnt + 1;
    }

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
Int32 AlgorithmLink_tiopDelete(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, algStatus;
    UInt32 queId;
    AlgorithmLink_tiopObj *pAlgObj = \
            (AlgorithmLink_tiopObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);

    /************************************************/
    /*              TIOP ALG DELETE                 */
    /************************************************/
    algStatus = pAlgObj->handle->ivision->ialg.algFree(
                                                (IALG_Handle)(pAlgObj->handle),
                                                pAlgObj->memRec);
    UTILS_assert(IALG_EOK == algStatus);

    status = tiopAlgMemFree(pAlgObj);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                    pAlgObj->memRec,
                    pAlgObj->memRecSize);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    /* Delete the temp input buffer queues */
    for(queId = 0;queId < pAlgObj->numInputQueues;queId++)
    {
        status = Utils_queDelete(&pAlgObj->tmpInQueue[queId].queHandle);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    /* Free the output buffer memory */
    for (queId = 0;queId < pAlgObj->numOutputQueues;queId++)
    {
        status = Utils_memFree(
                            UTILS_HEAPID_DDR_CACHED_LOCAL,
                            pAlgObj->metaDataBuf[queId],
                            pAlgObj->metaDataBufSize[queId]);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    }

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                    pAlgObj,
                    sizeof(AlgorithmLink_tiopObj));
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
Int32 AlgorithmLink_tiopProcess(void *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK, algStatus;
    UInt32 queId, bufIdx,buffCnt,buffsize,buffsizeVideo,buffsizeMeta,bufferOffset;
    UInt32 maxNumObjectDetect, numObjectDetected;
    float *metaPtr;
    Int32 freeId;
    System_BufferList inputBufList;
    System_Buffer *pSysBuffer;
    System_VideoFrameCompositeBuffer *pCompBufIn;
    Void *inBufAddrVideo[TIOP_LINK_MAX_NUM_BUFFERS], *inBufAddrMeta[TIOP_LINK_MAX_NUM_BUFFERS], *outBufAddr[TIOP_LINK_MAX_NUM_BUFFERS];
    AlgorithmLink_tiopObj *pAlgObj = \
            (AlgorithmLink_tiopObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
    AlgorithmLink_tiopCreateParams *pLinkCreatePrms = \
                                                &pAlgObj->algLinkCreateParams;
    TIOP_CreateParams *pAlgCreateParams = \
            (TIOP_CreateParams*)pLinkCreatePrms->pAlgCreateParams;
    System_LinkStatistics *linkStatsInfo = pAlgObj->linkStatsInfo;

    TIOP_InArgs inArgs;
    TIOP_outArgs outArgs;
    IVISION_InBufs inBufs;
    IVISION_OutBufs outBufs;

#ifdef RT_DEBUG
    UInt64 tsc_start, tsc_cycles;
#endif

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if(pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;
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
            pAlgObj->numOutBufReceived++;
            outBufAddr[queId] = pAlgObj->metaDataBuf[queId];
            memset(pAlgObj->metaDataBuf[queId],-1,pAlgObj->metaDataBufSize[queId]);
            /* 1st buff is the start address*/
            pAlgObj->outBufDesc[0].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].buf = outBufAddr[queId];
            buffsize = 0;
            for(buffCnt = 1; buffCnt < pAlgObj->numOutputBuffers; buffCnt++)
            {
                buffsize += pAlgObj->outBufSize[buffCnt-1];
                /* increment the buffaddr by the previous buff size*/
                pAlgObj->outBufDesc[buffCnt].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].buf = \
                    (void*)((UInt32)outBufAddr[queId] + buffsize);
            }
        }

        if(pAlgObj->numOutBufReceived == pAlgObj->numOutputQueues)
        {
            /* All the input and output buffers are available */
            for (queId = 0;queId < pAlgObj->numInputQueues;queId++)
            {
                pSysBuffer = pAlgObj->inBufList[queId];
                UTILS_assert(SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pSysBuffer->bufType);

                freeId = tiopGetFreeBufferId(pAlgObj);
                UTILS_assert(freeId != -1);
                pAlgObj->inBufStats[freeId].buffer = pSysBuffer;
                pAlgObj->inBufStats[freeId].status = TIOP_LOCKED_BUFFER;
                pCompBufIn = (System_VideoFrameCompositeBuffer *)pSysBuffer->payload;
                inBufAddrVideo[queId] = pCompBufIn->bufAddr[0][0];
                inBufAddrMeta[queId]  = pCompBufIn->bufAddr[0][1];
                bufferOffset = *(UInt32*)(inBufAddrMeta[queId]);
                maxNumObjectDetect = (bufferOffset - 2 * TIDL_MAX_PAD_SIZE)/(sizeof(UInt32) * TIOP_OBJECT_SIZE);
                metaPtr = (float *)((char *)inBufAddrMeta[queId] + (bufferOffset*4)+4);
                if(TRUE == pLinkCreatePrms->cacheInvInBuf)
                {
                    Cache_inv(
                        inBufAddrVideo[queId],
                        pAlgObj->inBufSize[queId][TIOP_IN_BUFDESC_INPUT_FRAME],
                        Cache_Type_ALL,
                        TRUE);
                    Cache_inv(
                        inBufAddrMeta[queId],
                        pAlgObj->inBufSize[queId][TIOP_IN_BUFDESC_DETECTION_LIST],
                        Cache_Type_ALL,
                        TRUE);
                }

                pAlgObj->inBufDesc[0].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].buf = \
                        inBufAddrVideo[queId];
                pAlgObj->inBufDesc[0].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].buf = \
					        metaPtr;
                pAlgObj->inBufDesc[0].bufferId = pAlgObj->inBufStats[freeId].bufferId;
                buffsizeVideo = 0;
                buffsizeMeta  = 0;
                for(buffCnt = 1; buffCnt < pAlgObj->numInputBuffers; buffCnt++)
                {
                    buffsizeVideo += pAlgObj->inBufSize[buffCnt-1][TIOP_IN_BUFDESC_INPUT_FRAME];
                    pAlgObj->inBufDesc[buffCnt].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].buf = \
                            (void*)((UInt32)inBufAddrVideo[queId] + buffsizeVideo);

                    buffsizeMeta += pAlgObj->inBufSize[buffCnt-1][TIOP_IN_BUFDESC_DETECTION_LIST];
                    pAlgObj->inBufDesc[buffCnt].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].buf = \
                            (void*)((UInt32)metaPtr + buffsizeMeta);
                }
            }

            /********************************
             *     ALG PROCESS START        *
             ********************************/
            inBufs.numBufs = pAlgObj->numInputBuffers;
            inBufs.bufDesc = pAlgObj->inBufDescList;

            outBufs.numBufs = pAlgObj->numOutputBuffers;
            outBufs.bufDesc = pAlgObj->outBufDescList;

            inArgs.iVisionInArgs.size = sizeof(TIOP_InArgs);
            inArgs.iVisionInArgs.subFrameInfo = 0;
            inArgs.numInObjects = pAlgCreateParams->numInDetections;

            outArgs.iVisionOutArgs.size = sizeof(TIOP_outArgs);
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
                numObjectDetected = outArgs.numOutObjects;
                if (numObjectDetected > maxNumObjectDetect)
                {
                    Vps_printf("[WARNING] : TIOP is detecting more objects than TIDL\n");
                     numObjectDetected = maxNumObjectDetect;
                }
                memcpy(metaPtr, outBufAddr[queId], (numObjectDetected * sizeof(UInt32) * TIOP_OBJECT_SIZE));
                if(TRUE == pLinkCreatePrms->cacheWbOutBuf)
                {
                    Cache_wb(
                        metaPtr,
                        pAlgObj->metaDataBufSize[queId],
                        Cache_Type_ALL,
                        TRUE);
                }

                Utils_updateLatency(
                                &linkStatsInfo->linkLatency,
                                pAlgObj->inBufList[queId]->linkLocalTimestamp);
                Utils_updateLatency(
                                &linkStatsInfo->srcToLinkLatency,
                                pAlgObj->inBufList[queId]->srcTimestamp);

                linkStatsInfo->linkStats.chStats[queId].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats[queId].outBufCount[0]++;
                status = AlgorithmLink_putFullOutputBuffer(
                                                    pObj,
                                                    queId,
                                                    pAlgObj->inBufList[queId]);
                UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

                /* Notify the next link */
                System_sendLinkCmd(
                                pLinkCreatePrms->outQueParams[queId].nextLink,
                                SYSTEM_CMD_NEW_DATA,
                                NULL);
            }

            /* Release the input buffers back to the previous links */
            for (queId = 0;queId < pAlgObj->numInputQueues;queId++)
            {
                pAlgObj->inBufList[queId] = \
                              tiopReleaseLockedBuffer(pAlgObj, (UInt32 *)outArgs.iVisionOutArgs.inFreeBufIDs);
                if (pAlgObj->inBufList[queId] != NULL)
                {
                    inputBufList.numBuf = 1;
                    inputBufList.buffers[0] = pAlgObj->inBufList[queId];
                    AlgorithmLink_releaseInputBuffer(
                                            pObj,
                                            queId,
                                            pLinkCreatePrms->inQueParams[queId].prevLinkId,
                                            pLinkCreatePrms->inQueParams[queId].prevLinkQueId,
                                            &inputBufList,
                                            NULL);
                }
                pAlgObj->inBufList[queId] = NULL;
            }

            pAlgObj->numInBufReceived = 0;
            pAlgObj->numOutBufReceived = 0;
        }
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
Int32 AlgorithmLink_tiopPrintStatistics(void *pObj,AlgorithmLink_tiopObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(
                    &pAlgObj->linkStatsInfo->linkStats,
                    "ALG_TIOP",
                    TRUE);

    Utils_printLatency(
                    "ALG_TIOP",
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
Int32 AlgorithmLink_tiopControl(void *pObj,void *pControlParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_tiopObj *pAlgObj;
    AlgorithmLink_ControlParams *pAlgLinkControlPrm;

    pAlgObj = (AlgorithmLink_tiopObj*)AlgorithmLink_getAlgorithmParamsObj(pObj);
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
            AlgorithmLink_tiopPrintStatistics(pObj, pAlgObj);
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
Int32 AlgorithmLink_tiopStop(void *pObj)
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
Int32 AlgorithmLink_tiop_initPlugin(void)
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate = AlgorithmLink_tiopCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess = AlgorithmLink_tiopProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl = AlgorithmLink_tiopControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop = AlgorithmLink_tiopStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete = AlgorithmLink_tiopDelete;

    algId = ALGORITHM_LINK_DSP_ALG_TIOP;
    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}
