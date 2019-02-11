/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
  ******************************************************************************
 * \file dataCollectLink_tsk.c
 *
 * \brief Stores task-related functions for the data collection link
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains_common_osal.h>
#include "dataCollectLink_priv.h"
#include "diskBucketMgr.h"

#define dc_dbg(fmt, ...) Vps_printf("[DATA COLLECT] " fmt, ##__VA_ARGS__)

void DataCollectLink_updateTiming(DataCollectLink_Obj *pObj, uint32_t startTime);
Bucket::DataFormat DataCollectLink_getBucketDataFormat(DataCollectLink_Obj *pObj,
                                                       uint32_t systemBufferDataFormat);

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
DataCollectLink_Obj gDataCollectLink_obj[DATA_COLLECT_LINK_OBJ_MAX];

/**
 * Helper function to reset all link information statistics
 */
void DataCollectLink_drvResetStats(DataCollectLink_Obj * pObj)
{
    pObj->minTime = 0xFFFF;
    pObj->maxTime = 0;
    pObj->numFrames = 0;
    pObj->totalTime = 0;
    pObj->realMissCount = 0;
    OSA_resetLinkStatistics(&pObj->linkStats, pObj->inQueInfo.numCh, 1);
}

/**
 *******************************************************************************
 * \brief DataCollect Link can be used to take input from a link and then without doing
 *   anything return it back to the same link. This useful when a link output
 *   cannot be given to any other link for testing purpose we just want to run
 *   a given link but not really use the output. In such cases the output queue
 *   of link can be connected to a DataCollect link. The dataCollect link will operate like
 *   any other link from interface point of view. But it wont do anything with
 *   the frames it gets. It will simply return it back to the sending link. This
 *   function simply does the following
 *
 *     - Copies the user passed create params into the link object create params
 *     - resets received frame count to zero
 *
 * \param  pObj     [IN]  DataCollect link instance handle
 * \param  pPrm     [IN]  Create params for DataCollect link
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
int32_t DataCollectLink_drvCreate(DataCollectLink_Obj *pObj, DataCollectLink_CreateParams *pPrm)
{
    System_LinkInfo     inTskInfo;
    int32_t             status;
    Bucket::ConfigFileInfo CfgFiles;
    uint32_t i;

    dc_dbg("Create in progress !!!\n");

    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));
    if (pObj->createArgs.numInQue > DATA_COLLECT_LINK_MAX_IN_QUE)
    {
        dc_dbg("%d input queues specified but only ONE is permitted!", pObj->createArgs.numInQue);
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    status = System_linkGetInfo(pPrm->inQueParams.prevLinkId, &inTskInfo);
    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        dc_dbg("Unable to read previous link information!\n");
        return status;
    }

    if (pPrm->inQueParams.prevLinkQueId >= inTskInfo.numQue)
    {
        dc_dbg("Invalid queue ID present for previous link output.\n");
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    pObj->inQueInfo = inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId];
    pObj->bucket = NULL;

    if (pObj->createArgs.dumpDataType == DATA_COLLECT_LINK_COPY_TYPE_FILE)
    {
        dc_dbg("Open Disk Bucket Mgr !!!\n");
        pObj->bucket = new DiskBucketMgr();
        CfgFiles.numFiles = pObj->createArgs.numConfigFiles;
        for (i = 0U; i < pObj->createArgs.numConfigFiles; i++)
        {
            UTILS_assert(pObj->createArgs.configBufParams[i].pConfigBuf != NULL);

            CfgFiles.configFile[i].addr = (UInt8 *) ChainsCommon_Osal_getVirtAddr(
                                                        (UInt32) pObj->createArgs.configBufParams[i].pConfigBuf);
            CfgFiles.configFile[i].size = pObj->createArgs.configBufParams[i].bufSize;
        }
        status = pObj->bucket->bucketOpen(
                                          pObj->createArgs.filePath,
                                          &CfgFiles,
                                          0,
                                          Bucket::OPEN_MODE_CREATE,
                                          DATA_COLLECT_BUCKET_MAX_BYTES
                                          );
        if (status != 0)
        {
            dc_dbg("Open Disk Bucket Mgr Failed!\n");
            return SYSTEM_LINK_STATUS_EFAIL;
        }
        pObj->enableDataCollect = TRUE;
    }
    else
    {
        dc_dbg("Only DATA_COLLECT_LINK_COPY_TYPE_FILE is supported!\n");
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    pObj->isFirstFrameRecv = FALSE;
    DataCollectLink_drvResetStats(pObj);
    dc_dbg("Create done !!!\n");
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 * Actually do the hard work of dumping data frames received from a previous link
 * @param[in] pObj Pointer to data collect state object
 * @param[in] pBuf Received buffer to be dumped to disk
 * @return SYSTEM_LINK_STATUS_OK if dumped fine, SYSTEM_LINK_STATUS_EFAIL otherwise
 */
int32_t DataCollectLink_drvDumpFrames(DataCollectLink_Obj * pObj, const System_Buffer *pBuf)
{
    System_LinkChInfo *pChInfo;
    UInt32 dataFormat, curTime;
    int32_t status;

    // If this channel is disabled in configuration, skip it
    if (pObj->createArgs.disableChannel[pBuf->chNum])
    {
        pObj->linkStats.chStats[pBuf->chNum].inBufDropCount++;
        return SYSTEM_LINK_STATUS_SOK;
    }

    if((pObj->createArgs.dumpDataType == DATA_COLLECT_LINK_COPY_TYPE_FILE)
            &&
       (pBuf!=NULL)
            &&
       (pBuf->chNum < pObj->inQueInfo.numCh))
    {
        pChInfo = &pObj->inQueInfo.chInfo[pBuf->chNum];

        pObj->linkStats.chStats[pBuf->chNum].inBufRecvCount++;

        if((pBuf->bufType == SYSTEM_BUFFER_TYPE_METADATA))
        {
            System_MetaDataBuffer *pMetaData = (System_MetaDataBuffer *) pBuf->payload;
            Bucket::BufInfo bufInfo;

            bufInfo.numPlanes = pMetaData->numMetaDataPlanes;
            bufInfo.dataFormat = Bucket::DATA_FORMAT_RAW8;
            bufInfo.timestamp = pBuf->srcTimestamp;
            bufInfo.chId = pBuf->chNum;
            bufInfo.width = 0;
            bufInfo.height = 0;

            for (uint32_t i = 0; i < pMetaData->numMetaDataPlanes; ++i)
            {
                bufInfo.pitchOrMetaSize[i] = pMetaData->metaFillLength[i];
                bufInfo.size[i] = pMetaData->metaFillLength[i];
                bufInfo.addr[i] = pMetaData->bufAddr[i];
            }

            curTime = OSA_getCurGlobalTimeInMsec();

            status = pObj->bucket->bucketWrite(&bufInfo);
            if(status<0)
            {
                /* disk full or disk not available, so skip file write's */
                pObj->createArgs.dumpDataType = DATA_COLLECT_LINK_COPY_TYPE_NONE;
            }

            pObj->linkStats.chStats[pBuf->chNum].inBufProcessCount++;
            pObj->numFrames++;
            DataCollectLink_updateTiming(pObj, curTime);
        }
        else if (SYSTEM_BUFFER_TYPE_VIDEO_FRAME == pBuf->bufType)
        {
            System_VideoFrameBuffer *pVidFrame = (System_VideoFrameBuffer *) pBuf->payload;
            Bucket::BufInfo bufInfo;

            dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

            if((dataFormat==SYSTEM_DF_YUV422I_YUYV)
                ||
                (dataFormat==SYSTEM_DF_YUV422I_UYVY)
                ||
                (dataFormat==SYSTEM_DF_RGB16_565)
                ||
                (dataFormat==SYSTEM_DF_BGR16_565))
            {
                bufInfo.numPlanes = 1;
                bufInfo.size[0] = pChInfo->pitch[0]*pChInfo->height;

            }
            if(dataFormat==SYSTEM_DF_YUV420SP_UV)
            {
                if(pObj->createArgs.enableLumaOnlyDump)
                {
                    bufInfo.numPlanes = 1;
                    bufInfo.size[0] = pChInfo->pitch[0]*pChInfo->height;
                }
                else
                {
                    bufInfo.numPlanes = 2;
                    bufInfo.size[0] = pChInfo->pitch[0]*pChInfo->height;
                    bufInfo.size[1] = pChInfo->pitch[1]*pChInfo->height/2;
                }
            }

            bufInfo.dataFormat = DataCollectLink_getBucketDataFormat(pObj, dataFormat);

            if(pObj->bucket && pObj->enableDataCollect && pVidFrame)
            {
                bufInfo.width = pChInfo->width;
                bufInfo.height = pChInfo->height;
                bufInfo.addr[0] = pVidFrame->bufAddr[0];
                bufInfo.addr[1] = pVidFrame->bufAddr[1];
                bufInfo.pitchOrMetaSize[0] = pChInfo->pitch[0];
                bufInfo.pitchOrMetaSize[1] = pChInfo->pitch[1];
                bufInfo.timestamp = pBuf->srcTimestamp;
                bufInfo.chId = pBuf->chNum;

                curTime = OSA_getCurGlobalTimeInMsec();

                for(int i=0; i<bufInfo.numPlanes; i++)
                {
                    OSA_cacheInv(bufInfo.addr[i], bufInfo.size[i]);
                }

                status = pObj->bucket->bucketWrite(&bufInfo);
                if(status<0)
                {
                    /* disk full or disk not available, so skip file write's */
                    pObj->createArgs.dumpDataType = DATA_COLLECT_LINK_COPY_TYPE_NONE;
                }

                pObj->linkStats.chStats[pBuf->chNum].inBufProcessCount++;
                pObj->numFrames++;
                DataCollectLink_updateTiming(pObj, curTime);
            }
        }
        else if (SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER == pBuf->bufType)
        {
            System_VideoFrameCompositeBuffer *pVidFrameComposite =
                (System_VideoFrameCompositeBuffer *) pBuf->payload;
            Bucket::BufInfo bufInfo;

            dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

            if((dataFormat==SYSTEM_DF_YUV422I_YUYV)
                ||
                (dataFormat==SYSTEM_DF_YUV422I_UYVY)
                ||
                (dataFormat==SYSTEM_DF_RGB16_565)
                ||
                (dataFormat==SYSTEM_DF_BGR16_565))
            {
                bufInfo.numPlanes = 1;
                bufInfo.size[0] = pChInfo->pitch[0]*pChInfo->height;
            }
            if(dataFormat==SYSTEM_DF_YUV420SP_UV)
            {
                if(pObj->createArgs.enableLumaOnlyDump)
                {
                    bufInfo.numPlanes = 1;
                    bufInfo.size[0] = pChInfo->pitch[0]*pChInfo->height;
                }
                else
                {
                    bufInfo.numPlanes = 2;
                    bufInfo.size[0] = pChInfo->pitch[0]*pChInfo->height;
                    bufInfo.size[1] = pChInfo->pitch[1]*pChInfo->height/2;
                }
            }

            bufInfo.dataFormat = DataCollectLink_getBucketDataFormat(pObj, dataFormat);
            bufInfo.width = pChInfo->width;
            bufInfo.height = pChInfo->height;
            bufInfo.pitchOrMetaSize[0] = pChInfo->pitch[0];
            bufInfo.pitchOrMetaSize[1] = pChInfo->pitch[1];
            bufInfo.timestamp = pBuf->srcTimestamp;

            if(pObj->bucket && pObj->enableDataCollect && pVidFrameComposite)
            {
                curTime = OSA_getCurGlobalTimeInMsec();

                for(UInt32 chId=0; chId<pVidFrameComposite->numFrames; chId++)
                {
                    bufInfo.chId = chId;
                    bufInfo.addr[0] = pVidFrameComposite->bufAddr[0][chId];
                    bufInfo.addr[1] = pVidFrameComposite->bufAddr[1][chId];

                    for(int i=0; i<bufInfo.numPlanes; i++)
                    {
                        OSA_cacheInv(bufInfo.addr[i], bufInfo.size[i]);
                    }

                    status = pObj->bucket->bucketWrite(&bufInfo);
                    if(status<0)
                    {
                        /* disk full or disk not available, so skip file write's */
                        pObj->createArgs.dumpDataType = DATA_COLLECT_LINK_COPY_TYPE_NONE;
                        break;
                    }
                }
                pObj->linkStats.chStats[pBuf->chNum].inBufProcessCount++;
                pObj->numFrames++;
                DataCollectLink_updateTiming(pObj, curTime);
            }
        }
        else if (SYSTEM_BUFFER_TYPE_BITSTREAM == pBuf->bufType)
        {
            System_BitstreamBuffer *pBitstream = (System_BitstreamBuffer *) pBuf->payload;

            Bucket::BufInfo bufInfo;
            bufInfo.numPlanes = 1;
            bufInfo.size[0] = pBitstream->fillLength;
            bufInfo.dataFormat = Bucket::DATA_FORMAT_BITSTREAM;
            bufInfo.width = pBitstream->width;
            bufInfo.height = pBitstream->height;
            bufInfo.pitchOrMetaSize[0] = 0;
            bufInfo.pitchOrMetaSize[1] = 0;
            bufInfo.timestamp = pBuf->srcTimestamp;
            bufInfo.chId = pBuf->chNum;
            bufInfo.addr[0] = pBitstream->bufAddr;

            if (pObj->bucket && pObj->enableDataCollect)
            {
                curTime = OSA_getCurGlobalTimeInMsec();
                OSA_cacheInv(bufInfo.addr[0], bufInfo.size[0]);

                status = pObj->bucket->bucketWrite(&bufInfo);
                if(status<0)
                {
                    /* disk full or disk not available, so skip file write's */
                    pObj->createArgs.dumpDataType = DATA_COLLECT_LINK_COPY_TYPE_NONE;
                }

                pObj->linkStats.chStats[pBuf->chNum].inBufProcessCount++;
                pObj->numFrames++;
                DataCollectLink_updateTiming(pObj, curTime);
            }
        }
        else
        {
            /* MISRA-C Fix */
            pObj->linkStats.chStats[pBuf->chNum].inBufDropCount++;
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 * Update timing statistics based on current time given that processing started at a specific time
 * for the current frame
 * @param[in] pObj Data collect state object
 * @param[in] startTime the time that the current frame started being saved
 */
void DataCollectLink_updateTiming(DataCollectLink_Obj *pObj, uint32_t startTime)
{
    uint32_t delta = OSA_getCurGlobalTimeInMsec() - startTime;

    pObj->totalTime += delta;

    if (delta < pObj->minTime)
        pObj->minTime = delta;

    if (delta > pObj->maxTime)
        pObj->maxTime = delta;

    if (delta >= 33)
    {
        #if 0
        Vps_printf(" DATA_COLLECT: Potential real time miss !!! (cur=%d msecs, avg=%d msecs)\n",
                   curTime,
                   pObj->totalTime/pObj->numFrames);
        #endif
        pObj->realMissCount++;
    }
}

/**
 * Get the correct Bucket::DataFormat value given a system data format enum value; this is valid
 * only for SYSTEM_BUFFER_TYPE_VIDEO_FRAME and SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER because
 * metadata buffers must always be raw type
 * @param[in] pObj Data collect state object for configuration data
 * @param[in] systemBufferDataFormat The data format stored in the link's channel flags
 * @return Bucket::DataFormat appropriate tag for the data written to file
 */
Bucket::DataFormat DataCollectLink_getBucketDataFormat(DataCollectLink_Obj *pObj,
                                                       uint32_t systemBufferDataFormat)
{
    switch (systemBufferDataFormat)
    {
        case SYSTEM_DF_YUV422I_YUYV:
        case SYSTEM_DF_YUV422I_UYVY:
            return Bucket::DATA_FORMAT_YUV422I;
        case SYSTEM_DF_YUV420SP_UV:
            if (pObj->createArgs.enableLumaOnlyDump)
                return Bucket::DATA_FORMAT_Y8;
            return Bucket::DATA_FORMAT_YUV420SP;
        default:
            return Bucket::DATA_FORMAT_RAW8;
    }
}

/**
 *******************************************************************************
 *
 * \brief Print IPC link related statistics
 *
 * \param  pObj     [IN] Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DataCollectLink_drvPrintStatistics(DataCollectLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    char  tskName[32];

    sprintf(tskName, "DATA_COLLECT_%u", (unsigned int)pObj->linkInstId);

    OSA_printLinkStatistics(&pObj->linkStats, tskName, TRUE);

    if(pObj->numFrames)
    {
        Vps_printf(" \n");
        Vps_printf(" DATA_COLLECT: Number of frames processed is %d in avg %d msecs/frames (min = %d ms, max = %d ms)\n",
            pObj->numFrames, (UInt32)(pObj->totalTime/pObj->numFrames), pObj->minTime, pObj->maxTime);
        Vps_printf(" DATA_COLLECT: Number of potential real time misses is %d\n", pObj->realMissCount);
        Vps_printf(" \n");
    }

    DataCollectLink_drvResetStats(pObj);

    return status;
}

/**
 *******************************************************************************
 * \brief DataCollect Link just receives incoming buffers and returns back to the
 *   sending link. This function does the same
 *
 * \param  pObj     [IN]  DataCollect link instance handle
 *
 * \return status   SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DataCollectLink_drvProcessFrames(DataCollectLink_Obj * pObj)
{
    System_LinkInQueParams *pInQueParams;
    System_BufferList bufList;
    uint32_t bufId;

    pInQueParams = &pObj->createArgs.inQueParams;
    System_getLinksFullBuffers(pInQueParams->prevLinkId, pInQueParams->prevLinkQueId, &bufList);

    if (bufList.numBuf)
    {
        for (bufId = 0; bufId < bufList.numBuf; bufId++)
        {
            if (pObj->isFirstFrameRecv==FALSE)
            {
                pObj->isFirstFrameRecv = TRUE;
                DataCollectLink_drvResetStats(pObj);
            }

            DataCollectLink_drvDumpFrames(pObj, bufList.buffers[bufId]);
        }

        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId, &bufList);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function implements the following.
 *    Accepts commands for
 *     - Creating DataCollect link
 *     - Arrival of new data
 *     - Deleting DataCollect link
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 *******************************************************************************
 */
Int32 DataCollectLink_tskMain(struct OSA_TskHndl * pTsk, OSA_MsgHndl * pMsg, UInt32 curState)
{
    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    DataCollectLink_Obj *pObj = (DataCollectLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        OSA_tskAckOrFreeMsg(pMsg, SYSTEM_LINK_STATUS_EFAIL);
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    status = DataCollectLink_drvCreate(pObj, (DataCollectLink_CreateParams*)OSA_msgGetPrm(pMsg));
    OSA_tskAckOrFreeMsg(pMsg, status);

    if (status != SYSTEM_LINK_STATUS_SOK)
        return status;

    done = FALSE;
    ackMsg = FALSE;

    while (!done)
    {
        status = OSA_tskWaitMsg(pTsk, &pMsg);
        if (status != OSA_SOK)
            break;

        cmd = OSA_msgGetCmd(pMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_START:
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
            case SYSTEM_CMD_STOP:
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
            case SYSTEM_CMD_DELETE:
                done = TRUE;
                ackMsg = TRUE;
                break;
            case SYSTEM_CMD_NEW_DATA:
                OSA_tskAckOrFreeMsg(pMsg, status);

                DataCollectLink_drvProcessFrames(pObj);
                break;
            case DATA_COLLECT_LINK_CMD_RESUME:
                pObj->enableDataCollect = TRUE;
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
            case DATA_COLLECT_LINK_CMD_PAUSE:
                pObj->enableDataCollect = FALSE;
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
            case SYSTEM_CMD_PRINT_STATISTICS:

                status = DataCollectLink_drvPrintStatistics(pObj);

                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
            default:
                OSA_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    if(pObj->bucket)
    {
        pObj->bucket->bucketClose();
        delete pObj->bucket;
        pObj->bucket = NULL;
    }

    if (ackMsg && pMsg != NULL)
        OSA_tskAckOrFreeMsg(pMsg, status);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Init function for DataCollect link. This function does the following for each
 *   DataCollect link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */

Int32 DataCollectLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 dataCollectId;
    DataCollectLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();
    char    name[] = "DataCollect";

    for (dataCollectId = 0; dataCollectId < DATA_COLLECT_LINK_OBJ_MAX; dataCollectId++)
    {
        pObj = &gDataCollectLink_obj[dataCollectId];

        memset(pObj, 0, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId,
                                          SYSTEM_LINK_ID_DATA_COLLECT_0 + dataCollectId);

        pObj->linkInstId = dataCollectId;

        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers= NULL;
        linkObj.linkPutEmptyBuffers= NULL;
        linkObj.getLinkInfo = NULL;

        System_registerLink(pObj->tskId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * ipcOutLink_tskMain is called when a message command is received.
         */
        status = OSA_tskCreate(&pObj->tsk,
                               DataCollectLink_tskMain,
                               OSA_THR_PRI_DEFAULT,
                               DATA_COLLECT_LINK_TSK_STACK_SIZE,
                               0,
                               pObj,
                               name);
        OSA_assert(status == OSA_SOK);


    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for DataCollect link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DataCollectLink_deInit(void)
{
    UInt32 dataCollectId;

    for (dataCollectId = 0; dataCollectId < DATA_COLLECT_LINK_OBJ_MAX; dataCollectId++)
    {
        OSA_tskDelete(&gDataCollectLink_obj[dataCollectId].tsk);
    }
    return SYSTEM_LINK_STATUS_SOK;
}


