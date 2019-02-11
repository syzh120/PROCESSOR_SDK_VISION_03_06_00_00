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
 * \file sgx3DsfmLink_drv.c
 *
 * \brief  This file has the implementation of Sgx3Dsfm Link
 *
 *         Sgx3Dsfm Link is used to feed video frames and map information to SGX
 *         for rendering.
 *         The rendered output will be pushed to display via DRM.
 *
 * \version 0.0 (Dec 2015) : [MM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sgx3DsfmLink_priv.h"
#include <links_fw/src/hlos/osa/include/osa_mem.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *******************************************************************************
 *
 * \brief Sgx3Dsfm link create function
 *
 *        This Set the Link and driver create time parameters.
 *        - Get the channel info from previous link
 *        - Set the internal data structures
 *        - Call the create and control functions
 *
 * \param   pObj     [IN] Sgx3Dsfm Link Instance handle
 * \param   pPrm     [IN] Sgx3Dsfm link create parameters
 *                        This need to be configured by the application
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_drvCreate(Sgx3DsfmLink_Obj *pObj,
                             Sgx3DsfmLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32                  inQue, channelId;
    Sgx3DsfmLink_InputQueId inputQId;
    UInt32                  prevChInfoFlags;
    System_LinkChInfo     * pPrevChInfo;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Create in progress !!!\n");
#endif

    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    OSA_assert(pPrm->numInQue <= SGX3DSFM_LINK_IPQID_MAXIPQ);

    for (inQue = 0; inQue < pPrm->numInQue; inQue++)
    {
        status = System_linkGetInfo(pPrm->inQueParams[inQue].prevLinkId,
                                    &pObj->inTskInfo[inQue]);

        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

        OSA_assert(pPrm->inQueParams[inQue].prevLinkQueId < pObj->inTskInfo[inQue].numQue);

        memcpy(&pObj->inQueInfo[inQue],
               &pObj->inTskInfo[inQue].queInfo[pPrm->inQueParams[inQue].prevLinkQueId],
               sizeof(pObj->inQueInfo));
    }

    OSA_assert(pObj->createArgs.inBufType[SGX3DSFM_LINK_IPQID_MULTIVIEW] ==
                     SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER);
    OSA_assert(pObj->createArgs.inBufType[SGX3DSFM_LINK_IPQID_EGOPOSE] ==
                     SYSTEM_BUFFER_TYPE_METADATA);
    OSA_assert(pObj->createArgs.inBufType[SGX3DSFM_LINK_IPQID_BOXES] ==
                     SYSTEM_BUFFER_TYPE_METADATA);

    inputQId    = SGX3DSFM_LINK_IPQID_MULTIVIEW;
    channelId   = 0;
    pPrevChInfo = &(pObj->inQueInfo[inputQId].chInfo[channelId]);

    memset(&pObj->eglWindowObj, 0, sizeof(pObj->eglWindowObj));
    pObj->eglWindowObj.width = 1920;
    pObj->eglWindowObj.height = 1080;

    pObj->tskInfo.numQue = SGX_LINK_MAX_OUT_QUE;
    OSA_assert(pObj->tskInfo.numQue == 1);
    pObj->tskInfo.queInfo[0].numCh = 1;
    pObj->tskInfo.queInfo[0].chInfo[0].startX = 0;
    pObj->tskInfo.queInfo[0].chInfo[0].startY = 0;
    pObj->tskInfo.queInfo[0].chInfo[0].width = pObj->eglWindowObj.width;
    pObj->tskInfo.queInfo[0].chInfo[0].height = pObj->eglWindowObj.height;
    pObj->tskInfo.queInfo[0].chInfo[0].pitch[0] = pObj->eglWindowObj.width * 4;
    pObj->tskInfo.queInfo[0].chInfo[0].pitch[1] = pObj->eglWindowObj.width * 4;
    pObj->tskInfo.queInfo[0].chInfo[0].pitch[2] = pObj->eglWindowObj.width * 4;
    pObj->tskInfo.queInfo[0].chInfo[0].flags =
        System_Link_Ch_Info_Set_Flag_Data_Format(pObj->tskInfo.queInfo[0].chInfo[0].flags, SYSTEM_DF_ARGB32_8888);

    prevChInfoFlags    = pPrevChInfo->flags;
    pObj->inDataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);
    pObj->inPitch[0]   = pPrevChInfo->pitch[0];
    pObj->inPitch[1]   = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pObj->createArgs.inFramesWidth)
       ||
       (pPrevChInfo->height > pObj->createArgs.inFramesHeight)
      )
    {
      OSA_assert(NULL);
    }

    /********************************
     * Creation of local input Qs
     * *****************************/
    inputQId = SGX3DSFM_LINK_IPQID_MULTIVIEW;
    status   = OSA_queCreate(&(pObj->localInputQ[inputQId].queHandle),
                               SGX3DSFM_LINK_MAX_LOCALQUEUELENGTH);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    pObj->isFirstFrameRecv       = FALSE;
    pObj->receivedFirstEGOPOSEFlag = FALSE;
    pObj->receivedFirstBOXFlag     = FALSE;

    OSA_resetLatency(&pObj->linkLatency);
    OSA_resetLatency(&pObj->srcToLinkLatency);

    pObj->numInputChannels = 1;
    OSA_resetLinkStatistics(&pObj->linkStats, pObj->numInputChannels, 1);

    /* For SGX profiling */
    system_create_pvrscope_profile_data(&pObj->pvrscopeObj);

    if (pObj->createArgs.bEglInfoInCreate) {
        status = Sgx3DsfmLink_drvDoProcessEglInfo(pObj,
                (struct control_srv_egl_ctx *)pObj->createArgs.EglInfo);
    }

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Create Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function prints the Link status
 *
 *        prints the Link status, such as
 *        - FPS
 *        - Callback Intervals
 *        - Input DropCount
 *        - etc
 *
 * \param   pObj        [IN] Sgx3Dsfm Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_drvPrintStatistics(Sgx3DsfmLink_Obj *pObj)
{
    OSA_printLinkStatistics(&pObj->linkStats, "SGX3DSFM", TRUE);

    OSA_printLatency("SGX3DSFM",
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Sgx3DsfmLink_drvDoProcessEglInfo(Sgx3DsfmLink_Obj *pObj, struct control_srv_egl_ctx *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pObj->eglWindowObj.chInfo.flags = pObj->tskInfo.queInfo[0].chInfo[0].flags;
    status = System_eglWindowOpen(&pObj->eglWindowObj, pPrm);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    pObj->tskInfo.queInfo[0].chInfo[0].width = pObj->eglWindowObj.chInfo.width;
    pObj->tskInfo.queInfo[0].chInfo[0].height = pObj->eglWindowObj.chInfo.height;
    pObj->tskInfo.queInfo[0].chInfo[0].pitch[0] = pObj->eglWindowObj.chInfo.pitch[0];
    pObj->tskInfo.queInfo[0].chInfo[0].flags = pObj->eglWindowObj.chInfo.flags;

    pObj->render3DsfmObj.screen_width = pObj->eglWindowObj.width;
    pObj->render3DsfmObj.screen_height = pObj->eglWindowObj.height;
    pObj->render3DsfmObj.carScale = 22.5f;
    pObj->render3DsfmObj.inFramesWidth = (int)pObj->createArgs.inFramesWidth;
    pObj->render3DsfmObj.inFramesHeight = (int)pObj->createArgs.inFramesHeight;
    status = SgxRender3Dsfm_setup(&pObj->render3DsfmObj);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);
    pObj->render3DsfmObj.egoposePtr = NULL;
    pObj->render3DsfmObj.camposesPtr = NULL;
    pObj->render3DsfmObj.boxesPtr = NULL;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function de-queue frames/meta data from prvious link output Qs
 *
 *        Function perform the following operations
 *        - De-queue frames/meta data from prvious link output Qs
 *        - Put them in an internal Qs
 *
 * \param   pObj     [IN] Sgx3Dsfm Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_getInputFrameData(Sgx3DsfmLink_Obj * pObj)
{
    Sgx3DsfmLink_InputQueId      inputQId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSysBufferInput;
    Sgx3DsfmLink_CreateParams  * pPrm;
    System_MetaDataBuffer      * tmpMetdaDataBuffer;

    pPrm = &pObj->createArgs;

    /*******************************************************
     * Get Input buffers from previous links
     *******************************************************/

    /* SGX3DSFM_LINK_IPQID_MULTIVIEW */
    inputQId = SGX3DSFM_LINK_IPQID_MULTIVIEW;
    inputBufList.numBuf = 0;
    status = System_getLinksFullBuffers( pPrm->inQueParams[inputQId].prevLinkId,
                                         pPrm->inQueParams[inputQId].prevLinkQueId,
                                        &inputBufList);
    if(inputBufList.numBuf)
    {
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput = inputBufList.buffers[bufId];

            if(pSysBufferInput != NULL)
            {
                status = OSA_quePut(&(pObj->localInputQ[inputQId].queHandle),
                                     (Int32) pSysBufferInput,
                                      OSA_TIMEOUT_NONE);

                OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }

    /* SGX3DSFM_LINK_IPQID_EGOPOSE */
    inputQId = SGX3DSFM_LINK_IPQID_EGOPOSE;
    inputBufList.numBuf = 0;
    status = System_getLinksFullBuffers( pPrm->inQueParams[inputQId].prevLinkId,
                                         pPrm->inQueParams[inputQId].prevLinkQueId,
                                        &inputBufList);
    if(inputBufList.numBuf)
    {
        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

        for(bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            if(pObj->receivedFirstEGOPOSEFlag == TRUE)
            {
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pObj->sysBufferEGOPOSE;

                status = System_putLinksEmptyBuffers( pPrm->inQueParams[inputQId].prevLinkId,
                                                      pPrm->inQueParams[inputQId].prevLinkQueId,
                                                     &inputBufListReturn);

                OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            else
            {
                pObj->receivedFirstEGOPOSEFlag = TRUE;
            }

            pObj->sysBufferEGOPOSE = inputBufList.buffers[bufId];
            tmpMetdaDataBuffer = (System_MetaDataBuffer *)pObj->sysBufferEGOPOSE->payload;
            OSA_assert(tmpMetdaDataBuffer != NULL);
            OSA_assert(tmpMetdaDataBuffer->bufAddr[0] != NULL);
            OSA_memCacheInv((UInt32)tmpMetdaDataBuffer->bufAddr[0],
            tmpMetdaDataBuffer->metaBufSize[0]);
            OSA_assert(tmpMetdaDataBuffer->bufAddr[1] != NULL);
            OSA_memCacheInv((UInt32)tmpMetdaDataBuffer->bufAddr[1],
            tmpMetdaDataBuffer->metaBufSize[1]);
        }
    }

    /* SGX3DSFM_LINK_IPQID_BOXES */
    inputQId = SGX3DSFM_LINK_IPQID_BOXES;
    inputBufList.numBuf = 0;
    status = System_getLinksFullBuffers( pPrm->inQueParams[inputQId].prevLinkId,
                                         pPrm->inQueParams[inputQId].prevLinkQueId,
                                        &inputBufList);
    if(inputBufList.numBuf)
    {
    	OSA_assert(status              == SYSTEM_LINK_STATUS_SOK);

    	for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            if(pObj->receivedFirstBOXFlag == TRUE)
            {
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pObj->sysBufferBOXES;

                status = System_putLinksEmptyBuffers( pPrm->inQueParams[inputQId].prevLinkId,
                                                      pPrm->inQueParams[inputQId].prevLinkQueId,
                                                     &inputBufListReturn);

                OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
            else
            {
                pObj->receivedFirstBOXFlag = TRUE;
            }

            pObj->sysBufferBOXES = inputBufList.buffers[bufId];

            tmpMetdaDataBuffer = (System_MetaDataBuffer *)pObj->sysBufferBOXES->payload;
            OSA_assert(tmpMetdaDataBuffer != NULL);
            OSA_assert(tmpMetdaDataBuffer->bufAddr[0] != NULL);
            OSA_memCacheInv((UInt32)tmpMetdaDataBuffer->bufAddr[0],
            tmpMetdaDataBuffer->metaBufSize[0]);
            OSA_assert(tmpMetdaDataBuffer->bufAddr[1] != NULL);
            OSA_memCacheInv((UInt32)tmpMetdaDataBuffer->bufAddr[1],
            tmpMetdaDataBuffer->metaBufSize[1]);
        }
    }


    pObj->linkStats.newDataCmdCount++;

    return status;
}


/**
 *******************************************************************************
 *
 * \brief This function de-queue and process/sgx3Dsfm the input frames
 *
 *        Function perform the following operations
 *        - De-queue the frames from the previous link output Q
 *        - Put them in intenal link queues
 *        - Get/De-queue the valid frames from the internal queue
 *        - Populate/Map OpenGL/Drm frame structure from system buffer
 *        - Call the OpenGL/DRM process function
 *        - Free-up these frames by send back to previous link after display
 *        - Immediately Free-up the frames which are not part of the display
 *
 * \param   pObj     [IN] Sgx3Dsfm Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */

Int32 Sgx3DsfmLink_drvDoProcessFrames(Sgx3DsfmLink_Obj *pObj)
{
    Sgx3DsfmLink_CreateParams  * pPrm;
    Sgx3DsfmLink_InputQueId      inputQId;
    UInt32                       channelId = 0;
    Int32                        status = SYSTEM_LINK_STATUS_SOK;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSystemBufferMultiview;
    Bool                         isProcessCallDoneFlag;
    System_MetaDataBuffer      * pEgoposeBuffer;
    System_MetaDataBuffer      * pBoxesBuffer;
    System_VideoFrameCompositeBuffer *pVideoCompositeFrame;
    GLuint                       texYuv[5] = {0};
    System_EglTexProperty        texProp;
    Uint32                       bufferCnt;

    pPrm = &pObj->createArgs;

    Sgx3DsfmLink_getInputFrameData(pObj);

    /*
     * Continous loop to perform synthesis as long as
     * input buffers are available.
     */
    while(1)
    {
        isProcessCallDoneFlag = FALSE;

        bufferCnt = OSA_queGetQueuedCount(&(pObj->localInputQ[SGX3DSFM_LINK_IPQID_MULTIVIEW].queHandle));

        if(bufferCnt > 0
        )
        {
            /*assign poses buffer to pointer in render object*/
            if(pObj->receivedFirstEGOPOSEFlag == TRUE)
            {
              OSA_assert(pObj->sysBufferEGOPOSE != NULL);
              pEgoposeBuffer = (System_MetaDataBuffer *)pObj->sysBufferEGOPOSE->payload;
              OSA_assert(pEgoposeBuffer != NULL);
              pObj->render3DsfmObj.egoposePtr = (void *)pEgoposeBuffer->bufAddr[0];
              pObj->render3DsfmObj.camposesPtr = (void *)pEgoposeBuffer->bufAddr[1];
            }

            /*assign boxes buffer to pointer in render object*/
            if(pObj->receivedFirstBOXFlag == TRUE)
            {
              OSA_assert(pObj->sysBufferBOXES != NULL);
              pBoxesBuffer = (System_MetaDataBuffer *)pObj->sysBufferBOXES->payload;
              OSA_assert(pBoxesBuffer != NULL);
              pObj->render3DsfmObj.boxesPtr = (void *)pBoxesBuffer->bufAddr[0];
            }


            /* Reset stats */
            if(pObj->isFirstFrameRecv == FALSE)
            {
                pObj->isFirstFrameRecv = TRUE;

                OSA_resetLinkStatistics(&pObj->linkStats,
                                         pObj->numInputChannels,
                                         1);

                OSA_resetLatency(&pObj->linkLatency);
                OSA_resetLatency(&pObj->srcToLinkLatency);
            }

             /*
              * Reaching here means output buffers are available.
              * Hence getting inputs from local Queus
              */
             inputQId = SGX3DSFM_LINK_IPQID_MULTIVIEW;
             pSystemBufferMultiview = NULL;
             status = OSA_queGet(&(pObj->localInputQ[inputQId].queHandle),
                                  (Int32 *) &pSystemBufferMultiview,
                                  OSA_TIMEOUT_NONE);

             /* Submit the frames to SGX processing & DRM display */
             if((pSystemBufferMultiview != NULL) && (status == SYSTEM_LINK_STATUS_SOK))
             {
                 channelId = pSystemBufferMultiview->chNum;
                 if(channelId < pObj->linkStats.numCh)
                 {
                     pObj->linkStats.chStats[channelId].inBufRecvCount++;
                     pObj->linkStats.chStats[channelId].inBufProcessCount++;
                     pObj->linkStats.chStats[channelId].outBufCount[0]++;
                 }

                 pSystemBufferMultiview->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();

                 texProp.width      = pObj->inQueInfo[inputQId].chInfo[channelId].width;
                 texProp.height     = pObj->inQueInfo[inputQId].chInfo[channelId].height;
                 texProp.pitch[0]   = pObj->inQueInfo[inputQId].chInfo[channelId].pitch[0];
                 texProp.pitch[1]   = pObj->inQueInfo[inputQId].chInfo[channelId].pitch[1];
                 texProp.dataFormat = pObj->inDataFormat;


                 if(pSystemBufferMultiview->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
                 {
                     pVideoCompositeFrame = (System_VideoFrameCompositeBuffer *)(pSystemBufferMultiview->payload);
                     OSA_assert(pVideoCompositeFrame != NULL);

                     /* pick CH0 by default */
                     // TODO: check that the A15 mapped address is not NULL
#if defined (QNX_BUILD)
                     texYuv[0] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][0]);
                     texYuv[1] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][1]);
                     texYuv[2] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][2]);
                     texYuv[3] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][3]);
#else
                     texYuv[0] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][0]);
                     texYuv[1] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][1]);
                     texYuv[2] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][2]);
                     texYuv[3] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][3]);
#endif
                 }
                 else
                 {
                     Vps_printf(" SGX3DSFM Link: ERROR: Received invalid buffer type !!!\n");
                     OSA_assert(0);
                 }

                 /* *****************************
                  * Call Main Render Function
                  * *****************************/
                 if (pObj->receivedFirstEGOPOSEFlag && pObj->receivedFirstBOXFlag)
                 {
                     SgxRender3Dsfm_renderFrame(&pObj->render3DsfmObj, texYuv);
                 }

                 System_eglSwap(&pObj->eglWindowObj, pSystemBufferMultiview->srcTimestamp);

                 pObj->linkStats.chStats[pSystemBufferMultiview->chNum].outBufCount[0]++;

                 OSA_updateLatency(&pObj->linkLatency, pSystemBufferMultiview->linkLocalTimestamp);
                 OSA_updateLatency(&pObj->srcToLinkLatency, pSystemBufferMultiview->srcTimestamp);
             }

             isProcessCallDoneFlag = TRUE;

             /*
              * Releasing (Free'ing) Input buffers, since algorithm does not need
              * it for any future usage.
              */
             if(pSystemBufferMultiview != NULL)
             {
                 inputQId                      = SGX3DSFM_LINK_IPQID_MULTIVIEW;
                 inputBufListReturn.numBuf     = 1;
                 inputBufListReturn.buffers[0] = pSystemBufferMultiview;

                 System_putLinksEmptyBuffers( pPrm->inQueParams[inputQId].prevLinkId,
                                              pPrm->inQueParams[inputQId].prevLinkQueId,
                                             &inputBufListReturn);
             }

             System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA, NULL);
        } /* End of if(bufferCnt > 0)*/

        if(isProcessCallDoneFlag == FALSE)
        {
            /* TBD - the drop frame status update is kept here temporarily.
             * This should done if output buffer is not available, and this
             * will be done when DRM is removed out from this link */
             pObj->linkStats.inBufErrorCount++;

             break;
        }
    } /* End of while(1) */

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the sgx3Dsfm link & driver
 *
 *        De-queue any frames which are held inside the driver, then
 *        - Delete the simply driver
 *        - delete the semaphore and other link data structures
 *        - delete the link periodic object
 *
 * \param   pObj     [IN] Sgx3Dsfm Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_drvDelete(Sgx3DsfmLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Sgx3DsfmLink_InputQueId inputQId;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Delete in progress !!!\n");
#endif

    /**************************************************************
     * Deletion of local input Qs
     * ************************************************************/
    inputQId = SGX3DSFM_LINK_IPQID_MULTIVIEW;
    status = OSA_queDelete(&(pObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_eglWindowClose(&pObj->eglWindowObj);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    /* For SGX profiling */
    system_delete_pvrscope_profile_data(&pObj->pvrscopeObj);

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Delete Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function start the simply driver
 *
 *        Primming of a few frames are required to start the Sgx3Dsfm driver.
 *        Use blank buffers to prime and start the simply driver even
 *        before the actual frames are received by the sgx3Dsfm link. This
 *        primming is done while sgx3Dsfm link create. Start shall be called
 *        only after the link create function
 *
 * \param   pObj     [IN] Sgx3Dsfm Link Instance handle
 *
 * \return  status
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_drvStart(Sgx3DsfmLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Start in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Start Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function stop the simply driver
 *
 *        When ever the driver is stopped, enable the sgx3Dsfm link periodic
 *        call back function. This will initiate to free-up the input frames
 *        in STOP state. The driver call back will be stopped when sgx3Dsfm
 *        driver stop is done
 *
 * \param   pObj     [IN] Sgx3Dsfm Link Instance handle
 *
 * \return  status
 *
 *******************************************************************************
 */
Int32 Sgx3DsfmLink_drvStop(Sgx3DsfmLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Stop in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSFM Link: Stop Done !!!\n");
#endif

    return status;
}

/* Nothing beyond this point */

