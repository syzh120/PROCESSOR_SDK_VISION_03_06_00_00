/*
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
*/

/**
 *******************************************************************************
 * \file sgxFrmcpyLink_drv.c
 *
 * \brief  This file has the implementation of SgxFrmcpy Link
 *
 *         SgxFrmcpy Link is used to feed video frames to SGX for
 *         rendering.
 *
 * \version 0.0 (Jun 2014) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "sgxFrmcpyLink_priv.h"

/**
 *******************************************************************************
 *
 * \brief SgxFrmcpy link create function
 *
 *        This Set the Link and driver create time parameters.
 *        - Get the channel info from previous link
 *        - create the semaphore required for simply link
 *        - Set the internal data structures
 *        - Set the default sgxFrmcpy channel number
 *        - Call the driver create and control functions
 *        - Invoke Priming and start the driver
 *        - Create the link periodic object
 *
 * \param   pObj     [IN] SgxFrmcpy Link Instance handle
 * \param   pPrm     [IN] SgxFrmcpy link create parameters
 *                        This need to be configured by the application
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvCreate(SgxFrmcpyLink_Obj *pObj,
                               SgxFrmcpyLink_CreateParams *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Create in progress for resolution: %dx%d !!!\n",
                 pPrm->displayWidth, pPrm->displayHeight);

#endif

    memcpy(&pObj->createArgs, pPrm, sizeof(*pPrm));

    status = System_linkGetInfo(pPrm->inQueParams.prevLinkId,
                                &pObj->inTskInfo);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
    OSA_assert(pPrm->inQueParams.prevLinkQueId < pObj->inTskInfo.numQue);

    memcpy(&pObj->inQueInfo,
           &pObj->inTskInfo.queInfo[pPrm->inQueParams.prevLinkQueId],
           sizeof(pObj->inQueInfo));


    memset(&pObj->eglWindowObj, 0, sizeof(pObj->eglWindowObj));
    pObj->eglWindowObj.width = pPrm->displayWidth;
    pObj->eglWindowObj.height = pPrm->displayHeight;

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
        System_Link_Ch_Info_Set_Flag_Data_Format(pObj->tskInfo.queInfo[0].chInfo[0].flags, SYSTEM_DF_ABGR32_8888);

    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    OSA_resetLatency(&pObj->linkLatency);
    OSA_resetLatency(&pObj->srcToLinkLatency);

    OSA_resetLinkStatistics(&pObj->linkStats, pObj->inQueInfo.numCh, 0);

    pObj->isFirstFrameRecv = FALSE;

    /* For SGX profiling */
    system_create_pvrscope_profile_data(&pObj->pvrscopeObj);

    if (pObj->createArgs.bEglInfoInCreate) {
        status = SgxFrmcpyLink_drvDoProcessEglInfo(pObj,
                (struct control_srv_egl_ctx *)pObj->createArgs.EglInfo);

        switch(pPrm->renderType)
        {
            default:
            case SGXFRMCPY_RENDER_TYPE_1x1:
                status = SgxRender1x1_setup(&pObj->render1x1Obj);
                break;
            case SGXFRMCPY_RENDER_TYPE_3D_CUBE:
                status = SgxRenderKmsCube_setup(&pObj->renderKmsCubeObj);
                break;
            case SGXFRMCPY_RENDER_TYPE_2x2:
                status = SgxRender2x2_setup(&pObj->render2x2Obj);
                break;
            case SGXFRMCPY_RENDER_TYPE_2x4:
                status = SgxRender2x4_setup(&pObj->render2x4Obj);
                break;
            case SGXFRMCPY_RENDER_TYPE_3x3:
                status = SgxRender3x3_setup(&pObj->render3x3Obj);
                break;
        }
    }

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Create Done for resolution: %dx%d !!!\n",
                 pPrm->displayWidth, pPrm->displayHeight);
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
 * \param   pObj        [IN] SgxFrmcpy Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvPrintStatistics(SgxFrmcpyLink_Obj *pObj)
{
    OSA_printLinkStatistics(&pObj->linkStats, "SGXFRMCPY", TRUE);

    OSA_printLatency("SGXFRMCPY",
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 SgxFrmcpyLink_drvDoProcessEglInfo(SgxFrmcpyLink_Obj *pObj, struct control_srv_egl_ctx *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pObj->eglWindowObj.chInfo.flags = pObj->tskInfo.queInfo[0].chInfo[0].flags;
    status = System_eglWindowOpen(&pObj->eglWindowObj, pPrm);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    pObj->tskInfo.queInfo[0].chInfo[0].width = pObj->eglWindowObj.chInfo.width;
    pObj->tskInfo.queInfo[0].chInfo[0].height = pObj->eglWindowObj.chInfo.height;
    pObj->tskInfo.queInfo[0].chInfo[0].pitch[0] = pObj->eglWindowObj.chInfo.pitch[0];
    pObj->tskInfo.queInfo[0].chInfo[0].flags = pObj->eglWindowObj.chInfo.flags;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function de-queue and process/sgxFrmcpy the input frames
 *
 *        Function perform the following operations
 *        - De-queue the frames from the Driver which are already sgxFrmcpyed
 *        - Free-up these frames by send back to previous link
 *        - Get/De-queue the valid frames from the input queue
 *        - Populate/Map Drm frame structure from system buffer
 *        - Submit these full frames to sgxFrmcpy driver
 *        - Immediately Free-up the frames which are not part of the sgxFrmcpy
 *
 * \param   pObj     [IN] SgxFrmcpy Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvDoProcessFrames(SgxFrmcpyLink_Obj *pObj)
{
    System_BufferList bufList;
    System_BufferList freeBufList;
    UInt32 freeBufNum, frameIdx;
    System_LinkInQueParams *pInQueParams;
    System_VideoFrameBuffer *pVideoFrame;
    System_VideoFrameCompositeBuffer *pVideoCompositeFrame;
    System_Buffer *pBuffer = NULL;
    GLuint texYuv[8] = {0};
    System_EglTexProperty texProp;

    pObj->linkStats.newDataCmdCount++;

    pInQueParams = &pObj->createArgs.inQueParams;
    /* queue frames if any */

    System_getLinksFullBuffers(pInQueParams->prevLinkId,
                               pInQueParams->prevLinkQueId,
                               &bufList);
    freeBufNum = 0;

    for(frameIdx=0; frameIdx<bufList.numBuf; frameIdx++)
    {
        if(pObj->isFirstFrameRecv==FALSE)
        {
            pObj->isFirstFrameRecv = TRUE;

            OSA_resetLinkStatistics(
                    &pObj->linkStats,
                    pObj->inQueInfo.numCh,
                    0);

            OSA_resetLatency(&pObj->linkLatency);
            OSA_resetLatency(&pObj->srcToLinkLatency);
        }

        pBuffer = bufList.buffers[frameIdx];

        if(pBuffer==NULL)
            continue;


        if(pBuffer->chNum < pObj->linkStats.numCh)
        {
            pObj->linkStats.chStats[pBuffer->chNum].inBufRecvCount++;
        }

        if(pBuffer->chNum == 0)
        {
            pBuffer->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();

            pObj->linkStats.chStats[pBuffer->chNum].inBufProcessCount++;

            texProp.width      = pObj->inQueInfo.chInfo[pBuffer->chNum].width;
            texProp.height     = pObj->inQueInfo.chInfo[pBuffer->chNum].height;
            texProp.pitch[0]   = pObj->inQueInfo.chInfo[pBuffer->chNum].pitch[0];
            texProp.pitch[1]   = pObj->inQueInfo.chInfo[pBuffer->chNum].pitch[1];
            texProp.dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(pObj->inQueInfo.chInfo[pBuffer->chNum].flags);

            if(pBuffer->bufType==SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
            {
                pVideoFrame = pBuffer->payload;
                OSA_assert(pVideoFrame != NULL);

#if defined (QNX_BUILD)
                texYuv[0] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->bufAddr[0]);
#else
                texYuv[0] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
#endif

                if(pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_2x2 ||
                    pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_2x4 ||
                    pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_3x3)

                {
#if defined (QNX_BUILD)
                    texYuv[1] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->bufAddr[0]);
                    texYuv[2] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->bufAddr[0]);
                    texYuv[3] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->bufAddr[0]);
#else
                    texYuv[1] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
                    texYuv[2] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
                    texYuv[3] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
#endif
                }

                if(pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_2x4 ||
                        pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_3x3)
                {
                    texYuv[4] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
                    texYuv[5] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
                    texYuv[6] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);
                    texYuv[7] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoFrame->dmaFd[0]);

                }

            }
            else
            if(pBuffer->bufType==SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
            {
                pVideoCompositeFrame = pBuffer->payload;
                OSA_assert(pVideoCompositeFrame != NULL);

                /* pick CH0 by default */
#if defined (QNX_BUILD)
                texYuv[0] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][0]);
#else
                texYuv[0] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][0]);
#endif
                if(pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_2x2||
                        pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_2x4 ||
                        pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_3x3)
                {
#if defined (QNX_BUILD)
                    texYuv[1] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][1]);
                    texYuv[2] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][2]);
                    texYuv[3] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->bufAddr[0][3]);
#else
                    texYuv[1] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][1]);
                    texYuv[2] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][2]);
                    texYuv[3] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][3]);
#endif
                }

                if(pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_2x4 ||
                        pObj->createArgs.renderType==SGXFRMCPY_RENDER_TYPE_3x3)
                {
                    texYuv[4] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][4]);
                    texYuv[5] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][5]);
                    texYuv[6] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][6]);
                    texYuv[7] = System_eglWindowGetTexYuv(&pObj->eglWindowObj, &texProp, pVideoCompositeFrame->dmaFd[0][7]);

                }
            }
            else
            {
                Vps_printf(" SGXFRMCPY: ERROR: Recevied invalid buffer type !!!\n");
                OSA_assert(0);
            }

            switch(pObj->createArgs.renderType)
            {
                default:
                case SGXFRMCPY_RENDER_TYPE_1x1:
                    SgxRender1x1_renderFrame(
                            &pObj->render1x1Obj,
                            &pObj->eglWindowObj,
                            texYuv[0]
                            );
                    break;
                case SGXFRMCPY_RENDER_TYPE_3D_CUBE:
                    SgxRenderKmsCube_renderFrame(
                            &pObj->renderKmsCubeObj,
                            &pObj->eglWindowObj,
                            texYuv[0]
                            );
                    break;
                case SGXFRMCPY_RENDER_TYPE_2x2:
                    SgxRender2x2_renderFrame(
                            &pObj->render2x2Obj,
                            &pObj->eglWindowObj,
                            texYuv,
                            4
                            );
                    break;
                case SGXFRMCPY_RENDER_TYPE_2x4:
                    SgxRender2x4_renderFrame(
                            &pObj->render2x4Obj,
                            &pObj->eglWindowObj,
                            texYuv,
                            8
                    );
                    break;
                case SGXFRMCPY_RENDER_TYPE_3x3:
                    SgxRender3x3_renderFrame(
                            &pObj->render3x3Obj,
                            &pObj->eglWindowObj,
                            texYuv,
                            8
                    );
                    break;

            }

            System_eglSwap(&pObj->eglWindowObj, pBuffer->srcTimestamp);

            pObj->linkStats.chStats[pBuffer->chNum].outBufCount[0]++;

            OSA_updateLatency(&pObj->linkLatency,
                                pBuffer->linkLocalTimestamp);
            OSA_updateLatency(&pObj->srcToLinkLatency,
                                pBuffer->srcTimestamp);

            System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                               SYSTEM_CMD_NEW_DATA, NULL);
        }
        else
        {
            if(pBuffer->chNum < pObj->linkStats.numCh)
            {
                pObj->linkStats.chStats[pBuffer->chNum].inBufDropCount++;
            }
        }
        OSA_assert(freeBufNum <
                   OSA_ARRAYSIZE(freeBufList.buffers));
        /* error in queuing to sgxFrmcpy, instead of asserting
            release the frame and continue
        */
        OSA_assert(pBuffer != NULL);
        freeBufList.buffers[freeBufNum] = pBuffer;
        freeBufNum++;
    }

    if (freeBufNum)
    {
        freeBufList.numBuf = freeBufNum;
        System_putLinksEmptyBuffers(pInQueParams->prevLinkId,
                                    pInQueParams->prevLinkQueId,
                                    &freeBufList);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the sgxFrmcpy link & driver
 *
 *        De-queue any frames which are held inside the driver, then
 *        - Delete the simply driver
 *        - delete the semaphore and other link data structures
 *        - delete the link periodic object
 *
 * \param   pObj     [IN] SgxFrmcpy Link Instance handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvDelete(SgxFrmcpyLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Delete in progress !!!\n");
#endif

    status = System_eglWindowClose(&pObj->eglWindowObj);
    OSA_assert(status==SYSTEM_LINK_STATUS_SOK);

    /* For SGX profiling */
    system_delete_pvrscope_profile_data(&pObj->pvrscopeObj);

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Delete Done !!!\n");
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function start the simply driver
 *
 *        Primming of a few frames are required to start the SgxFrmcpy driver.
 *        Use blank buffers to prime and start the simply driver even
 *        before the actual frames are received by the sgxFrmcpy link. This
 *        primming is done while sgxFrmcpy link create. Start shall be called
 *        only after the link create function
 *
 * \param   pObj     [IN] SgxFrmcpy Link Instance handle
 *
 * \return  status
 *
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvStart(SgxFrmcpyLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Start in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Start Done !!!\n");
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief This function stop the simply driver
 *
 *        When ever the driver is stopped, enable the sgxFrmcpy link periodic
 *        call back function. This will initiate to free-up the input frames
 *        in STOP state. The driver call back will be stopped when sgxFrmcpy
 *        driver stop is done
 *
 * \param   pObj     [IN] SgxFrmcpy Link Instance handle
 *
 * \return  status
 *
 *******************************************************************************
 */
Int32 SgxFrmcpyLink_drvStop(SgxFrmcpyLink_Obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Stop in progress !!!\n");
#endif

#ifdef SYSTEM_DEBUG_DISPLAY
    Vps_printf(" SGXFRMCPY: Stop Done !!!\n");
#endif

    return status;
}
