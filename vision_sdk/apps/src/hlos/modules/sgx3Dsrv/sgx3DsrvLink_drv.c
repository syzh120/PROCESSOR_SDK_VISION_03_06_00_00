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
 * \file sgx3DsrvLink_drv.c
 *
 * \brief  This file has the implementation of Sgx3Dsrv Link
 *
 *         Sgx3Dsrv Link is used to feed video frames to SGX for
 *         rendering.
 *         The rendered output will be pushed to display via DRM.
 *
 * \version 0.0 (Jun 2014) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sgx3DsrvLink_priv.h"
#include <links_fw/src/hlos/osa/include/osa_mem.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef USE_STANDALONE_LUT
#include "links_fw/src/hlos/system/sgxRenderUtils/standalone/GAlignLUT.c"
#include "links_fw/src/hlos/system/sgxRenderUtils/standalone/BlendLUT3D.c"
#endif

/**
 *******************************************************************************
 *
 * \brief Sgx3Dsrv link create function
 *
 *        This Set the Link and driver create time parameters.
 *        - Get the channel info from previous link
 *        - Set the internal data structures
 *        - Call the create and control functions
 *
 * \param   pObj     [IN] Sgx3Dsrv Link Instance handle
 * \param   pPrm     [IN] Sgx3Dsrv link create parameters
 *                        This need to be configured by the application
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsrvLink_drvCreate(Sgx3DsrvLink_Obj *pObj,
                             Sgx3DsrvLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32                  inQue, channelId;
    Sgx3DsrvLink_InputQueId inputQId;
    UInt32                  prevChInfoFlags;
    System_LinkChInfo     * pPrevChInfo;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Create in progress !!!\n");
#endif

    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    OSA_assert(pPrm->numInQue <= SGX3DSRV_LINK_IPQID_MAXIPQ);

    for (inQue = 0; inQue < pPrm->numInQue; inQue++)
    {
        status = System_linkGetInfo(pPrm->inQueParams[inQue].prevLinkId,
                                    &pObj->inTskInfo[inQue]);

        OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
        OSA_assert(pPrm->inQueParams[inQue].prevLinkQueId <
                   pObj->inTskInfo[inQue].numQue);
        memcpy(&pObj->inQueInfo[inQue],
               &pObj->inTskInfo[inQue].queInfo[pPrm->inQueParams[inQue].prevLinkQueId],
               sizeof(pObj->inQueInfo));
    }

    Vps_printf(" SGX3DSRV_LINK_IPQID_MULTIVIEW Height: %d Width:%d\n",
                pObj->inTskInfo[0].queInfo[pPrm->inQueParams[0].prevLinkQueId].chInfo[0].width,
                pObj->inTskInfo[0].queInfo[pPrm->inQueParams[0].prevLinkQueId].chInfo[0].height);

    OSA_assert(pObj->createArgs.inBufType[SGX3DSRV_LINK_IPQID_MULTIVIEW] ==
                     SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER);
    OSA_assert(pObj->createArgs.inBufType[SGX3DSRV_LINK_IPQID_PALUT] ==
                     SYSTEM_BUFFER_TYPE_METADATA);
    OSA_assert(pObj->createArgs.inBufType[SGX3DSRV_LINK_IPQID_GALUT] ==
                     SYSTEM_BUFFER_TYPE_METADATA);
    OSA_assert(pObj->createArgs.inBufType[SGX3DSRV_LINK_IPQID_BLENDLUT] ==
                     SYSTEM_BUFFER_TYPE_METADATA);

    inputQId = SGX3DSRV_LINK_IPQID_MULTIVIEW;
    channelId = 0;
    pPrevChInfo   =
        &(pObj->inQueInfo[inputQId].chInfo[channelId]);

    if(SGX3DSRV_LINK_INPUTRES_2MP == pObj->createArgs.inputRes)
    {
        OSA_assert(pObj->createArgs.maxOutputWidth  <= SGX3DSRV_LINK_OUTPUT_FRAME_WIDTH_2MP);
    }
    else
    {
        OSA_assert(pObj->createArgs.maxOutputWidth  <= SGX3DSRV_LINK_OUTPUT_FRAME_WIDTH);
    }
    OSA_assert(pObj->createArgs.maxOutputHeight <= SGX3DSRV_LINK_OUTPUT_FRAME_HEIGHT);

    memset(&pObj->eglWindowObj, 0, sizeof(pObj->eglWindowObj));

    if(SGX3DSRV_LINK_INPUTRES_2MP == pObj->createArgs.inputRes)
    {
        pObj->eglWindowObj.width = SGX3DSRV_LINK_OUTPUT_FRAME_WIDTH_2MP;
    }
    else
    {
        pObj->eglWindowObj.width = SGX3DSRV_LINK_OUTPUT_FRAME_WIDTH;
    }
    pObj->eglWindowObj.height = SGX3DSRV_LINK_OUTPUT_FRAME_HEIGHT;

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
    pObj->inPitch[0] = pPrevChInfo->pitch[0];
    pObj->inPitch[1] = pPrevChInfo->pitch[1];

    if((pPrevChInfo->width > pObj->createArgs.maxInputWidth)
       ||
       (pPrevChInfo->height > pObj->createArgs.maxInputHeight)
      )
    {
      OSA_assert(NULL);
    }

    /*
     * Creation of local input Qs for SGX3DSRV_LINK_IPQID_MULTIVIEW and
     * SGX3DSRV_LINK_IPQID_PALUT.
     * For ALGLINK_SYNTHESIS_IPQID_GALUT, always just one entry is kept.
     */
    inputQId = SGX3DSRV_LINK_IPQID_MULTIVIEW;
    status  = OSA_queCreate(&(pObj->localInputQ[inputQId].queHandle),
                               SGX3DSRV_LINK_MAX_LOCALQUEUELENGTH);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    inputQId = SGX3DSRV_LINK_IPQID_PALUT;
    status  = OSA_queCreate(&(pObj->localInputQ[inputQId].queHandle),
                               SGX3DSRV_LINK_MAX_LOCALQUEUELENGTH);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    OSA_resetLatency(&pObj->linkLatency);
    OSA_resetLatency(&pObj->srcToLinkLatency);

    pObj->numInputChannels = 1;
    OSA_resetLinkStatistics(&pObj->linkStats, pObj->numInputChannels, 1);

    pObj->isFirstFrameRecv     = FALSE;
    pObj->receivedGALUTFlag    = FALSE;
    pObj->receivedBlendLUTFlag = FALSE;
    pObj->receivedFirstPALUTFlag = FALSE;
    pObj->render3DSRVObj.enableContinousTransitions = pObj->createArgs.enableContinousTransitions;

    /* For SGX profiling */
    system_create_pvrscope_profile_data(&pObj->pvrscopeObj);

    if (pObj->createArgs.bEglInfoInCreate) {
        status = Sgx3DsrvLink_drvDoProcessEglInfo(pObj,
                (struct control_srv_egl_ctx *)pObj->createArgs.EglInfo);
    }

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Create Done !!!\n");
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
 * \param   pObj        [IN] Sgx3Dsrv Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsrvLink_drvPrintStatistics(Sgx3DsrvLink_Obj *pObj)
{
    OSA_printLinkStatistics(&pObj->linkStats, "SGX3DSRV", TRUE);

    OSA_printLatency("SGX3DSRV",
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Sgx3DsrvLink_drvUpdateRenderedView(Sgx3DsrvLink_Obj *pObj)
{
    render_process_keys(pObj->renderCfgPrms.inputChar);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Sgx3DsrvLink_drvDoProcessEglInfo(Sgx3DsrvLink_Obj *pObj, struct control_srv_egl_ctx *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pObj->eglWindowObj.chInfo.flags = pObj->tskInfo.queInfo[0].chInfo[0].flags;
    status = System_eglWindowOpen(&pObj->eglWindowObj, pPrm);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    pObj->tskInfo.queInfo[0].chInfo[0].width = pObj->eglWindowObj.chInfo.width;
    pObj->tskInfo.queInfo[0].chInfo[0].height = pObj->eglWindowObj.chInfo.height;
    pObj->tskInfo.queInfo[0].chInfo[0].pitch[0] = pObj->eglWindowObj.chInfo.pitch[0];
    pObj->tskInfo.queInfo[0].chInfo[0].flags = pObj->eglWindowObj.chInfo.flags;

    pObj->render3DSRVObj.screen_width = pObj->eglWindowObj.width;
    pObj->render3DSRVObj.screen_height = pObj->eglWindowObj.height;
    pObj->render3DSRVObj.LUT3D = NULL;
    pObj->render3DSRVObj.blendLUT3D = NULL;
    pObj->render3DSRVObj.cam_width = pObj->createArgs.maxInputWidth;
    pObj->render3DSRVObj.cam_height = pObj->createArgs.maxInputHeight;
    pObj->render3DSRVObj.cam_bpp = 12;
    if(SGX3DSRV_LINK_INPUTRES_2MP == pObj->createArgs.inputRes)
    {
        OSA_assert(pObj->createArgs.maxInputWidth <= SGX3DSRV_LINK_INPUT_FRAME_WIDTH_2MP);
        OSA_assert(pObj->createArgs.maxInputHeight <= SGX3DSRV_LINK_INPUT_FRAME_HEIGHT_2MP);
    }
    else
    {
        OSA_assert(pObj->createArgs.maxInputWidth <= SGX3DSRV_LINK_INPUT_FRAME_WIDTH);
        OSA_assert(pObj->createArgs.maxInputHeight <= SGX3DSRV_LINK_INPUT_FRAME_HEIGHT);
    }

    status = render_setup(&pObj->render3DSRVObj);

    if(SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" SGX3DSRV Link: Pl. make sure CALMAT.BIN and LENS.BIN files are present at /opt/vision_sdk folder\n");
        Vps_printf(" SGX3DSRV Link: CALMAT.BIN is generated after running the SRV Calibration Use case\n");
    }

    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

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
 * \param   pObj     [IN] Sgx3Dsrv Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsrvLink_getInputFrameData(Sgx3DsrvLink_Obj * pObj)
{
    Sgx3DsrvLink_InputQueId      inputQId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSysBufferInput;
    Sgx3DsrvLink_CreateParams  * pPrm;
    System_MetaDataBuffer      * pPALUTBuffer;
    System_MetaDataBuffer      * pGALUTBuffer;
    System_MetaDataBuffer      * pBlendLUTBuffer;

    pPrm = &pObj->createArgs;

    /*
     * Get Input buffers from previous link for
     * Qid = SGX3DSRV_LINK_IPQID_MULTIVIEW and queue them up locally.
     */
    inputQId = SGX3DSRV_LINK_IPQID_MULTIVIEW;

    System_getLinksFullBuffers(
        pPrm->inQueParams[inputQId].prevLinkId,
        pPrm->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput = inputBufList.buffers[bufId];

            /*TBD: Check for parameter correctness. If in error, return input*/

            if (pSysBufferInput != NULL)
            {
                status = OSA_quePut(
                            &(pObj->localInputQ[inputQId].queHandle),
                            (Int32) pSysBufferInput,
                            OSA_TIMEOUT_NONE);
                OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }

    /*
     * Get Input buffers from previous link for
     * Qid = SGX3DSRV_LINK_IPQID_PALUT and queue them up locally.
     */
    inputQId = SGX3DSRV_LINK_IPQID_PALUT;

    System_getLinksFullBuffers(
        pPrm->inQueParams[inputQId].prevLinkId,
        pPrm->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput = inputBufList.buffers[bufId];

            pPALUTBuffer = pSysBufferInput->payload;
            OSA_memCacheInv(
                        (UInt32)pPALUTBuffer->bufAddr[0],
                        pPALUTBuffer->metaBufSize[0]);

            /*TBD: Check for parameter correctness. If in error, return input*/
            status = OSA_quePut(
                        &(pObj->localInputQ[inputQId].queHandle),
                        (Int32) pSysBufferInput,
                        OSA_TIMEOUT_NONE);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            pObj->receivedFirstPALUTFlag = TRUE;
        }
    }

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_SYNTHESIS_IPQID_GALUT and store latest copy locally.
     */
    inputQId = SGX3DSRV_LINK_IPQID_GALUT;
    System_getLinksFullBuffers(
        pPrm->inQueParams[inputQId].prevLinkId,
        pPrm->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            /*
             * At any point in time, Synthesis link will hold only one GA LUT.
             * So whenever GA LUT is received, the previously received one
             * will be released and the newly received one will be archived.
             */
            if(pObj->receivedGALUTFlag == TRUE)
            {
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pObj->sysBufferGALUT;

                if(inputBufListReturn.numBuf)
                {
                    System_putLinksEmptyBuffers(pPrm->inQueParams[inputQId].prevLinkId,
                                                pPrm->inQueParams[inputQId].prevLinkQueId,
                                                &inputBufListReturn);
                }

                pObj->receivedGALUTFlag = FALSE;
            }

            pObj->sysBufferGALUT = inputBufList.buffers[bufId];

            pGALUTBuffer = pObj->sysBufferGALUT->payload;
            OSA_memCacheInv(
                        (UInt32)pGALUTBuffer->bufAddr[0],
                        pGALUTBuffer->metaBufSize[0]);

            /*TBD: Check for parameter correctness. If in error, return input*/
            pObj->receivedGALUTFlag = TRUE;
#ifdef SYSTEM_DEBUG_DISPLAY
            //Vps_printf (" SGX3DSRV Link - GA LUT received !!! \n");
#endif
        }
    }

    /*
     * Get Input buffers from previous link for
     * Qid = SGX3DSRV_LINK_IPQID_BLENDLUT and store latest copy locally.
     */
    inputQId = SGX3DSRV_LINK_IPQID_BLENDLUT;
    System_getLinksFullBuffers(
        pPrm->inQueParams[inputQId].prevLinkId,
        pPrm->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            /*
             * At any point in time, Synthesis link will hold only one GA LUT.
             * So whenever GA LUT is received, the previously received one
             * will be released and the newly received one will be archived.
             */
            if(pObj->receivedBlendLUTFlag == TRUE)
            {
                inputBufListReturn.numBuf     = 1;
                inputBufListReturn.buffers[0] = pObj->sysBufferBlendLUT;

                if(inputBufListReturn.numBuf)
                {
                    System_putLinksEmptyBuffers(pPrm->inQueParams[inputQId].prevLinkId,
                                                pPrm->inQueParams[inputQId].prevLinkQueId,
                                                &inputBufListReturn);
                }

                pObj->receivedBlendLUTFlag = FALSE;
            }

            pObj->sysBufferBlendLUT = inputBufList.buffers[bufId];

            pBlendLUTBuffer = pObj->sysBufferBlendLUT->payload;
            OSA_memCacheInv(
                        (UInt32)pBlendLUTBuffer->bufAddr[0],
                        pBlendLUTBuffer->metaBufSize[0]);

            /*TBD: Check for parameter correctness. If in error, return input*/
            pObj->receivedBlendLUTFlag = TRUE;
#ifdef SYSTEM_DEBUG_DISPLAY
            Vps_printf (" SGX3DSRV Link - Blending LUT received !!! \n");
#endif
        }
    }


    pObj->linkStats.newDataCmdCount++;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function de-queue and process/sgx3Dsrv the input frames
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
 * \param   pObj     [IN] Sgx3Dsrv Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
volatile static unsigned int gDebug_IsCalibDone = 0;
Int32 Sgx3DsrvLink_drvDoProcessFrames(Sgx3DsrvLink_Obj *pObj)
{
    Sgx3DsrvLink_CreateParams  * pPrm;
    Sgx3DsrvLink_InputQueId      inputQId;
    UInt32                       channelId = 0;
    Int32                        status = SYSTEM_LINK_STATUS_SOK;
    System_BufferList            inputBufListReturn;
    System_Buffer              * pSystemBufferMultiview;
    System_Buffer              * pSystemBufferPALUT;
    Bool                         isProcessCallDoneFlag;
    System_MetaDataBuffer      * pPALUTBuffer;
    System_MetaDataBuffer      * pGALUTBuffer;
    System_MetaDataBuffer      * pBlendLUTBuffer;
    System_VideoFrameCompositeBuffer *pVideoCompositeFrame;
    GLuint                       texYuv[4] = {0};
    System_EglTexProperty        texProp;
    System_VideoFrameCompositeBuffer videoCompositeFrame;
    UInt32 offsetY, offsetUV;

    pPrm = &pObj->createArgs;

    Sgx3DsrvLink_getInputFrameData(pObj);

    /*
     * Continous loop to perform synthesis as long as
     * input buffers are available.
     */
    while(1)
    {
      isProcessCallDoneFlag = FALSE;
      /* Checking if all the inputs are available */

      if(pObj->receivedGALUTFlag == TRUE
              &&
         pObj->receivedBlendLUTFlag == TRUE
              &&
         pObj->receivedFirstPALUTFlag == TRUE
              &&
         OSA_queGetQueuedCount(
              &(pObj->localInputQ[SGX3DSRV_LINK_IPQID_MULTIVIEW].queHandle))>0
       )
       {

        pSystemBufferPALUT = NULL;
        status = OSA_queGet(
                    &(pObj->localInputQ[SGX3DSRV_LINK_IPQID_PALUT].
                        queHandle),
                    (Int32 *) &pSystemBufferPALUT,
                    OSA_TIMEOUT_NONE);

        if (pSystemBufferPALUT != NULL)
        {
            pObj->sysBufferPALUT = pSystemBufferPALUT;
        }

        pPALUTBuffer = (System_MetaDataBuffer *)pObj->sysBufferPALUT->payload;
        OSA_assert (pPALUTBuffer != NULL);

        pGALUTBuffer = (System_MetaDataBuffer *)pObj->sysBufferGALUT->payload;
        OSA_assert (pGALUTBuffer != NULL);

        pBlendLUTBuffer = (System_MetaDataBuffer *)pObj->sysBufferBlendLUT->payload;
        OSA_assert (pBlendLUTBuffer != NULL);

        if(pObj->isFirstFrameRecv==FALSE)
        {
            pObj->isFirstFrameRecv = TRUE;

            OSA_resetLinkStatistics(
                    &pObj->linkStats,
                    pObj->numInputChannels,
                    1);

            OSA_resetLatency(&pObj->linkLatency);
            OSA_resetLatency(&pObj->srcToLinkLatency);
        }

        /*
         * Reaching here means output buffers are available.
         * Hence getting inputs from local Queus
         */
        pSystemBufferMultiview = NULL;
        status = OSA_queGet(
                  &(pObj->localInputQ[SGX3DSRV_LINK_IPQID_MULTIVIEW].
                      queHandle),
                  (Int32 *) &pSystemBufferMultiview,
                  OSA_TIMEOUT_NONE);

        /* Submit the SRV frames to SGX processing & DRM display */
        if (pSystemBufferMultiview != NULL && status == SYSTEM_LINK_STATUS_SOK)
        {
            channelId = pSystemBufferMultiview->chNum;
            if(channelId < pObj->linkStats.numCh)
            {
                pObj->linkStats.chStats[channelId].inBufRecvCount++;
                pObj->linkStats.chStats[channelId].inBufProcessCount++;
                pObj->linkStats.chStats[channelId].outBufCount[0]++;
            }

            pSystemBufferMultiview->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();

            inputQId = SGX3DSRV_LINK_IPQID_MULTIVIEW;

            texProp.width      = pObj->inQueInfo[inputQId].chInfo[channelId].width;
            texProp.height     = pObj->inQueInfo[inputQId].chInfo[channelId].height;
            texProp.pitch[0]   = pObj->inQueInfo[inputQId].chInfo[channelId].pitch[0];
            texProp.pitch[1]   = pObj->inQueInfo[inputQId].chInfo[channelId].pitch[1];
            texProp.dataFormat = pObj->inDataFormat;

#ifndef USE_STANDALONE_LUT
            // Do we need to specify the stitched frame resolution ?
            // Do we need to set any other parameters in render3DSRVObj ?
        if(TRUE == pObj->createArgs.enableAdaptiveBowl)
        {
            pObj->render3DSRVObj.LUT3D = (void *) pGALUTBuffer->bufAddr[0];
            //pObj->render3DSRVObj.blendLUT3D = (void *) pBlendLUTBuffer->bufAddr[0];

        }
        else
        {
            //pObj->render3DSRVObj.LUT3D = (void *) pGALUTBuffer->bufAddr[0];
            //pObj->render3DSRVObj.blendLUT3D = (void *) pBlendLUTBuffer->bufAddr[0];
        }
            pObj->render3DSRVObj.PALUT3D = (void *) pPALUTBuffer->bufAddr[0];

#else
            //Use standalone version of LUTs
            //FOR DEBUG ONLY
            //pObj->render3DSRVObj.LUT3D = (void *) GAlignLUT;
            //pObj->render3DSRVObj.blendLUT3D = (void *) BlendLUT3D;

#endif

#if 0  // Enable Dumping out of the tables
            {

            FILE *fp1;
            //FILE *fp2;

            gDebug_IsCalibDone++;
            if (gDebug_IsCalibDone == 250)
            {
                fp1=fopen("/mnt/TDA2X/3DLUT.BIN", "w+b");
                //fp2=fopen("./3DBLENDLUT.bin", "w+b");

                if (fp1 == NULL)
                {
                    printf("fp1 open error\n");
                }

                fwrite(pObj->render3DSRVObj.blendLUT3D, (2*POINTS_WIDTH*POINTS_HEIGHT*sizeof(BLENDLUT_DATATYPE)), 1, fp2);


                int closeErrorCheck = fclose(fp1);
                if (closeErrorCheck != 0)
                {
                    printf("error closing file\n");
                }
                //fclose(fp2);
                printf("Printing done\n");
            }
            }
#endif

            if(pSystemBufferMultiview->bufType==SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
            {
                pVideoCompositeFrame = (System_VideoFrameCompositeBuffer *)
                                       (pSystemBufferMultiview->payload);
                OSA_assert(pVideoCompositeFrame != NULL);

                videoCompositeFrame = *pVideoCompositeFrame;

                /* The below cropping feature will not work for UV plane as the SGX side
                 * code assume UV planes are immediately after the Y plane. So cropping
                 * works only for Y plane correctly, but this will not take for UV plane
                 * even if the Link modify the address. SGX side Algo needs to be modified
                 * to pick UV plane address separately, without assume UV planes are
                 * immediately after the Y plane
                 */
                if ((videoCompositeFrame.chInfo.startX!=0) || (videoCompositeFrame.chInfo.startY!=0))
                {
                    offsetY  = videoCompositeFrame.chInfo.pitch[0]*videoCompositeFrame.chInfo.startY
                             + videoCompositeFrame.chInfo.startX;
                    offsetUV = videoCompositeFrame.chInfo.pitch[1]*videoCompositeFrame.chInfo.startY/2
                             + videoCompositeFrame.chInfo.startX;
                    videoCompositeFrame.bufAddr[0][0] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[0][0] + offsetY);
                    videoCompositeFrame.bufAddr[0][1] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[0][1] + offsetY);
                    videoCompositeFrame.bufAddr[0][2] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[0][2] + offsetY);
                    videoCompositeFrame.bufAddr[0][3] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[0][3] + offsetY);
                    videoCompositeFrame.bufAddr[1][0] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[1][0] + offsetUV);
                    videoCompositeFrame.bufAddr[1][1] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[1][1] + offsetUV);
                    videoCompositeFrame.bufAddr[1][2] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[1][2] + offsetUV);
                    videoCompositeFrame.bufAddr[1][3] =
                        (UInt8 *) ((UInt32)videoCompositeFrame.bufAddr[1][3] + offsetUV);
                }
                /* pick CH0 by default */
                // TODO: check that the A15 mapped address is not NULL
#if defined (QNX_BUILD)
                texYuv[0] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.bufAddr[0][0]);
                texYuv[1] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.bufAddr[0][1]);
                texYuv[2] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.bufAddr[0][2]);
                texYuv[3] = System_eglGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.bufAddr[0][3]);
#else
                texYuv[0] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.dmaFd[0][0]);
                texYuv[1] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.dmaFd[0][1]);
                texYuv[2] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.dmaFd[0][2]);
                texYuv[3] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, videoCompositeFrame.dmaFd[0][3]);

#endif
            }
            else
            {
                Vps_printf(" SGX3DSRV Link: ERROR: Recevied invalid buffer type !!!\n");
                OSA_assert(0);
            }
#if 1
            render_renderFrame(
                            &pObj->render3DSRVObj,
                            &pObj->eglWindowObj,
                            texYuv
                            );
#else
            OSA_assert (texYuv != NULL);
#endif

            System_eglSwap(&pObj->eglWindowObj, pSystemBufferMultiview->srcTimestamp);

            pObj->linkStats.chStats[pSystemBufferMultiview->chNum].outBufCount[0]++;

            OSA_updateLatency(&pObj->linkLatency,
                              pSystemBufferMultiview->linkLocalTimestamp);
            OSA_updateLatency(&pObj->srcToLinkLatency,
                              pSystemBufferMultiview->srcTimestamp);
        }

        isProcessCallDoneFlag = TRUE;

        /*
         * Releasing (Free'ing) Input buffers, since algorithm does not need
         * it for any future usage.
         */
        if (pSystemBufferMultiview != NULL)
        {
          inputQId                      = SGX3DSRV_LINK_IPQID_MULTIVIEW;
          inputBufListReturn.numBuf     = 1;
          inputBufListReturn.buffers[0] = pSystemBufferMultiview;
          if(inputBufListReturn.numBuf)
          {
              System_putLinksEmptyBuffers(pPrm->inQueParams[inputQId].prevLinkId,
                                          pPrm->inQueParams[inputQId].prevLinkQueId,
                                          &inputBufListReturn);
          }
        }

        if (pSystemBufferPALUT != NULL)
        {
          inputQId                      = SGX3DSRV_LINK_IPQID_PALUT;
          inputBufListReturn.numBuf     = 1;
          inputBufListReturn.buffers[0] = pSystemBufferPALUT;
          if(inputBufListReturn.numBuf)
          {
              System_putLinksEmptyBuffers(pPrm->inQueParams[inputQId].prevLinkId,
                                          pPrm->inQueParams[inputQId].prevLinkQueId,
                                          &inputBufListReturn);
          }
        }

        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA, NULL);
      }

      if(isProcessCallDoneFlag == FALSE)
      {
          /* TBD - the drop frame staus update is kept here temperally.
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
 * \brief This function delete the sgx3Dsrv link & driver
 *
 *        De-queue any frames which are held inside the driver, then
 *        - Delete the simply driver
 *        - delete the semaphore and other link data structures
 *        - delete the link periodic object
 *
 * \param   pObj     [IN] Sgx3Dsrv Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 Sgx3DsrvLink_drvDelete(Sgx3DsrvLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Sgx3DsrvLink_InputQueId inputQId;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Delete in progress !!!\n");
#endif

    /*
     * Deletion of local input Qs for SGX3DSRV_LINK_IPQID_MULTIVIEW and
     * SGX3DSRV_LINK_IPQID_PALUT.
     * For ALGLINK_SYNTHESIS_IPQID_GALUT, always just one entry is kept.
     */
    inputQId = SGX3DSRV_LINK_IPQID_MULTIVIEW;
    status = OSA_queDelete(&(pObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    inputQId = SGX3DSRV_LINK_IPQID_PALUT;
    status = OSA_queDelete(&(pObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    render_teardown(&pObj->render3DSRVObj);
    status = System_eglWindowClose(&pObj->eglWindowObj);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    /* For SGX profiling */
    system_delete_pvrscope_profile_data(&pObj->pvrscopeObj);

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Delete Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function start the simply driver
 *
 *        Primming of a few frames are required to start the Sgx3Dsrv driver.
 *        Use blank buffers to prime and start the simply driver even
 *        before the actual frames are received by the sgx3Dsrv link. This
 *        primming is done while sgx3Dsrv link create. Start shall be called
 *        only after the link create function
 *
 * \param   pObj     [IN] Sgx3Dsrv Link Instance handle
 *
 * \return  status
 *
 *******************************************************************************
 */
Int32 Sgx3DsrvLink_drvStart(Sgx3DsrvLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Start in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Start Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function stop the simply driver
 *
 *        When ever the driver is stopped, enable the sgx3Dsrv link periodic
 *        call back function. This will initiate to free-up the input frames
 *        in STOP state. The driver call back will be stopped when sgx3Dsrv
 *        driver stop is done
 *
 * \param   pObj     [IN] Sgx3Dsrv Link Instance handle
 *
 * \return  status
 *
 *******************************************************************************
 */
Int32 Sgx3DsrvLink_drvStop(Sgx3DsrvLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Stop in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGX3DSRV Link: Stop Done !!!\n");
#endif

    return status;
}

/* Nothing beyond this point */

