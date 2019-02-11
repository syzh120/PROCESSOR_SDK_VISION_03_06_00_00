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
  ******************************************************************************
 * \file dispDistSrcLink_tsk.c
 *
 * \brief  This file has the implementation of  Disp Dist Src Link
 **
 *           This file implements the state machine logic for this link.
 *           A message command will cause the state machine
 *           to take some action and then move to a different state.
 *
 * \version 0.0 (Nov 2017) : [BJ] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <vdrm_controller/v_controller_if.h>
#include "dispDistSrcLink_priv.h"

/*******************************************************************************
 *  This part cannot be completely misra compliant.
 *  This part cannot adhere to coding standards.
 *******************************************************************************
 */
#include <stdint.h>
#include <stdbool.h>

#include <errno.h>
#include <sys/ioctl.h>

#include <drm_fourcc.h>
#include <xf86drm.h>

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
DispDistSrcLink_Obj gDispDistSrcLink_obj[DISP_DIST_SRC_LINK_OBJ_MAX];

Int32 DispDistSrcLink_create(DispDistSrcLink_Obj * pObj,
                         const DispDistSrcLink_CreateParams * pPrm);
Int32 DispDistSrcLink_start(DispDistSrcLink_Obj * pObj);

Int32 DispDistSrcLink_processData(DispDistSrcLink_Obj * pObj);
Int32 DispDistSrcLink_stop(DispDistSrcLink_Obj * pObj);
Int32 DispDistSrcLink_delete(DispDistSrcLink_Obj * pObj);
Int32 DispDistSrcLink_tskRun(DispDistSrcLink_Obj * pObj, OSA_TskHndl * pTsk,
                         OSA_MsgHndl ** pMsg, Bool * done, Bool * ackMsg);
Int32 DispDistSrcLink_printBufferStatus(DispDistSrcLink_Obj * pObj);
Int32 DispDistSrcLink_printLinkStats(DispDistSrcLink_Obj * pObj);
Int32 DispDistSrcLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 DispDistSrcLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList* pBufList);
Int32 DispDistSrcLink_getInfo(Void * ptr, System_LinkInfo * info);

int DispDistSrcLink_tskMain(struct OSA_TskHndl *pTsk, OSA_MsgHndl *pMsg, Uint32 curState );


/**
 ******************************************************************************
 *
 * \brief Return buffer allocation information for a given width,height,format
 *
 ******************************************************************************
 */
static Void DispDistSrcLink_planeInfoForWidthAndFormat(UInt32 width, UInt32 height, System_VideoDataFormat format, UInt32 plane,
                                                       UInt32 *stride, UInt32 *allocHeight, UInt32 *bpp, UInt32 *allocWidth)
{
    UInt32 _allocWidth = 0, _bpp = 0, _allocHeight = 0, _stride = 0;

    switch(format) {
        case SYSTEM_DF_ARGB32_8888:
        case SYSTEM_DF_BGRX24_8888:
            if(plane == 0)
            {
                _allocWidth = width;
                _bpp = 32;
                _allocHeight = height;
                _stride = _allocWidth * (_bpp / 8);
            }
            else
            {
                _allocWidth = 0;
                _bpp = 0;
                _allocHeight = 0;
                _stride = _allocWidth * (_bpp / 8);
            }
            break;
        default:
            OSA_assert(0);
            break;
    }

    if(allocWidth)
        *allocWidth = _allocWidth;
    if(stride)
        *stride = _stride;
    if(allocHeight)
        *allocHeight = _allocHeight;
    if(bpp)
        *bpp = _bpp;
}

/**
 ******************************************************************************
 *
 * \brief Convert DRM FOURCC to System_Data_Format.
 *
 ******************************************************************************
 */
System_VideoDataFormat DispDistSrcLink_toSystemDataFormat(UInt32 drm_format)
{
    if(drm_format == DRM_FORMAT_ARGB8888)
    {
        return SYSTEM_DF_ARGB32_8888;
    }
    else if (drm_format == DRM_FORMAT_XRGB8888)
    {
        return SYSTEM_DF_BGRX24_8888;
    }
    else
    {
        OSA_assert(0);
        return 0;
    }
}

/**
 ******************************************************************************
 *
 * \brief Deletes a created System_Buffer when putEmptyBuffers is called
 *
 * This link does not allocate buffers at create. It allocates System_buffers
 * when a buffer from v_controller is available. So that buffer must be
 * destroyed when its returned by teh next link
 *
 * \param  pObj          [IN] Disp Dist source link global handle
 * \param  buf           [IN] Buffer to be deleted 
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
static Int32 DispDistSrcLink_deleteBuffer(DispDistSrcLink_Obj *pObj, System_Buffer *buf)
{
    free(buf->payload);
    free(buf);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Convert a v_controller buffer to System_Buffer and send to this link 
 *
 * \param  pObj          [IN] Disp Dist source link global handle
 * \param  nb            [IN] v_ctrl_event_new_buffer event containing buffer
 *                            information
 *
 ******************************************************************************
 */
Void DispDistSrcLink_sendNewBuffer(DispDistSrcLink_Obj *pObj, struct v_ctrl_event_new_buffer *nb)
{
    Int32 status;

    System_Buffer *buf;
    System_VideoFrameBuffer *vidBuffer;
    System_LinkChInfo *pChInfo;
    struct v_ctrl_provider_gem_to_paddr paddr;
    int ret;

    buf = calloc(sizeof(System_Buffer), 1);
    buf->bufType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
    buf->chNum = 0;
    buf->frameId = 0;
    buf->srcTimestamp = OSA_getCurGlobalTimeInUsec();
    buf->hlosTranslationDisable = TRUE;

    vidBuffer = calloc(sizeof(System_VideoFrameBuffer), 1);
    pChInfo = &vidBuffer->chInfo;
    pChInfo->pitch[0] = nb->pitches[0];
    pChInfo->pitch[1] = nb->pitches[1];
    pChInfo->pitch[2] = nb->pitches[2];
    pChInfo->width = nb->width;
    pChInfo->height = nb->height;
    pChInfo->startX = 0;
    pChInfo->startY = 0;
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags, DispDistSrcLink_toSystemDataFormat(nb->drm_format));
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags, SYSTEM_SF_PROGRESSIVE);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags, SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

    if(nb->v_gem_handle[0])
    {
        memset(&paddr, 0, sizeof(paddr));
        paddr.v_gem_handle = nb->v_gem_handle[0];
        ret = ioctl(pObj->v_fd, V_CTRL_IOCTL_PROVIDER_GEM_TO_PADDR, &paddr);
        OSA_assert(ret == 0);
        vidBuffer->bufAddr[0] = (Void *)paddr.paddr + nb->offsets[0];
    }

    if(nb->v_gem_handle[1])
    {
        memset(&paddr, 0, sizeof(paddr));
        paddr.v_gem_handle = nb->v_gem_handle[1];
        ret = ioctl(pObj->v_fd, V_CTRL_IOCTL_PROVIDER_GEM_TO_PADDR, &paddr);
        OSA_assert(ret == 0);
        vidBuffer->bufAddr[1] = (Void *)paddr.paddr + nb->offsets[1];
    }

    if(nb->v_gem_handle[2])
    {
        memset(&paddr, 0, sizeof(paddr));
        paddr.v_gem_handle = nb->v_gem_handle[2];
        ret = ioctl(pObj->v_fd, V_CTRL_IOCTL_PROVIDER_GEM_TO_PADDR, &paddr);
        OSA_assert(ret == 0);
        vidBuffer->bufAddr[2] = (Void *)paddr.paddr + nb->offsets[2];
    }

    buf->payload = vidBuffer;
    buf->payloadSize = sizeof(System_VideoFrameBuffer);


    //Vps_printf("%s recieved a buffer %08x, %08x, %08x\n", pObj->tskName, vidBuffer->bufAddr[0], vidBuffer->bufAddr[1], vidBuffer->bufAddr[2]);

    status = OSA_quePut(&pObj->outThrBufQue, (Int32)(buf), OSA_TIMEOUT_FOREVER);
    OSA_assert(status == OSA_SOK);

    status = System_sendLinkCmd(pObj->tskId, SYSTEM_CMD_NEW_DATA, NULL);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

}

/**
 ******************************************************************************
 *
 * \brief Process one v_controller event.
 *
 * \param  pObj          [IN] Disp Dist source link global handle
 * \param  e             [IN] event to process
 *
 ******************************************************************************
 */
Void DispDistSrcLink_processEvent(DispDistSrcLink_Obj *pObj, struct v_ctrl_event *e)
{
    struct v_ctrl_event_new_buffer *nb;
    System_VideoDataFormat format = System_Link_Ch_Info_Get_Flag_Data_Format(pObj->linkInfo.queInfo[0].chInfo[0].flags);
    UInt32 width = pObj->linkInfo.queInfo[0].chInfo[0].width;
    UInt32 height = pObj->linkInfo.queInfo[0].chInfo[0].height;
    UInt32 stride0 = pObj->linkInfo.queInfo[0].chInfo[0].pitch[0];
    UInt32 stride1 = pObj->linkInfo.queInfo[0].chInfo[0].pitch[1];
    UInt32 stride2 = pObj->linkInfo.queInfo[0].chInfo[0].pitch[2];

    if (e->type == V_CTRL_EVENT_TYPE_NEW_BUFFER)
    {
        nb = (struct v_ctrl_event_new_buffer *)e;
        OSA_assert(nb->prov_id == pObj->provider_id);

        if(nb->valid)
        {
            if(nb->width == width && nb->height == height &&
                    DispDistSrcLink_toSystemDataFormat(nb->drm_format) == format &&
                    nb->pitches[0] == stride0 &&
                    nb->pitches[1] == stride1 &&
                    nb->pitches[2] == stride2)
            {
                DispDistSrcLink_sendNewBuffer(pObj, nb);
            }

        }
        else
        {
            //TODO: Maybe, send a dummy
        }
    }
    else
    {
        OSA_assert(0);
    }
}

/**
 ******************************************************************************
 *
 * \brief Process multiple events in a buffer.
 *
 * \param  pObj          [IN] Disp Dist source link global handle
 * \param  buffer        [IN] Buffer containing the events
 * \param  pObj          [IN] Size of buffer
 *
 ******************************************************************************
 */
Void DispDistSrcLink_processEvents(DispDistSrcLink_Obj *pObj, UInt8 *buffer, UInt32 sz)
{
    UInt32 offset = 0;
    struct v_ctrl_event *e;

    while(offset < sz) {
        e = (struct v_ctrl_event *)&buffer[offset];
        OSA_assert(e->length > 0);
        OSA_assert(e->length <= (sz - offset));

        DispDistSrcLink_processEvent(pObj, e);
        offset += e->length;
    }
    OSA_assert(offset == sz);
}

/**
 ******************************************************************************
 *
 * \brief Worker thread function to process v_controller events.
 *
 ******************************************************************************
 */
Void *DispDistSrcLink_workLoop(Void *arg)
{
    int ret;
    fd_set fds;
    struct timeval interval;
    UInt8 *buffer;

    DispDistSrcLink_Obj *pObj = (DispDistSrcLink_Obj *)arg;

    buffer = malloc(DISP_DIST_SRC_LINK_EVENT_BUF_SZ);

    while(1)
    {
        FD_ZERO(&fds);
        FD_SET(pObj->v_fd, &fds);
        interval.tv_sec = 0;
        interval.tv_usec = 1000;
        ret = select(pObj->v_fd + 1, &fds, NULL, NULL, &interval);
        if (ret == 0)
        {
            continue;
        }
        else if(ret < 0)
        {
            if(errno == EINTR)
            {
                continue;
            }
            else
            {
                OSA_assert(0);
            }
        }
        else
        {
            if (FD_ISSET(pObj->v_fd, &fds))
            {
                ret = read(pObj->v_fd, buffer, DISP_DIST_SRC_LINK_EVENT_BUF_SZ);
                if(ret > 0)
                {
                    DispDistSrcLink_processEvents(pObj, buffer, ret);
                }
            }
        }
    }

    return NULL;
}

/**
 ******************************************************************************
 *
 * \brief Process the buffer data in response to a callback.
 *
 * This function gets called in response to a callback. It puts buffers into
 * link output queue and sends message to next link
 *
 * \param  pObj          [IN] Disp Dist source link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_processData(DispDistSrcLink_Obj * pObj)
{
    Int32 status;
    System_Buffer *pBuffer;

    if(pObj->isFirstBufferSent==FALSE)
    {
        pObj->isFirstBufferSent = TRUE;

        /*
        * Reset the null src link statistics when first buffer is ready to be
        * sent to next link.
        */
        OSA_resetLinkStatistics(&pObj->linkStats, 1, 1);
        OSA_resetLatency(&pObj->linkLatency);
        OSA_resetLatency(&pObj->srcToLinkLatency);
    }

    pObj->linkStats.newDataCmdCount++;

    pObj->linkStats.chStats[0].inBufRecvCount++;
    pObj->linkStats.chStats[0].inBufProcessCount++;

    if(pObj->outSerial - pObj->inSerial >= DISP_DIST_SRC_MAX_OUT_BUFS)
    {
        pObj->linkStats.chStats[0].outBufDropCount[0]++;

        status = OSA_queGet(&pObj->outThrBufQue, (Int32 *)(&pBuffer), OSA_TIMEOUT_NONE);
        OSA_assert(status == OSA_SOK);

        status = DispDistSrcLink_deleteBuffer(pObj, pBuffer);
        OSA_assert(status == OSA_SOK);
    }
    else
    {
        pObj->linkStats.chStats[0].outBufCount[0]++;
        pObj->outSerial++;
        System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                               SYSTEM_CMD_NEW_DATA, NULL);
    }


    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Callback function to give full buffers to the next link
 *
 * Disp Dist Source link sends message to next link about availability of buffers.
 * Next link calls this function to get full buffers from its o/p queue
 *
 * \param  ptr          [IN] Task Handle
 * \param  queId        [IN] queId from which buffers are required.
 * \param  pBufList     [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 DispDistSrcLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    DispDistSrcLink_Obj *pObj = (DispDistSrcLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    OSA_assert(queId < DISP_DIST_SRC_LINK_MAX_OUT_QUE);
    OSA_assert(pBufList != NULL);

    status = OSA_queGet(&pObj->outThrBufQue, (Int32 *)(&pBufList->buffers[0]), OSA_TIMEOUT_NONE);
    OSA_assert(status == OSA_SOK);

    pObj->linkStats.getFullBufCount++;
    pBufList->numBuf = 1;

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Callback function link to get empty buffers from next link.
 *
 *
 * \param  ptr          [IN] Task Handle
 * \param  queId        [IN] queId from which buffers are required.
 * \param  pBufList     [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 DispDistSrcLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList* pBufList)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;
    UInt32 bufId;

    DispDistSrcLink_Obj *pObj = (DispDistSrcLink_Obj *) pTsk->appData;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    OSA_assert(queId < DISP_DIST_SRC_LINK_MAX_OUT_QUE);
    OSA_assert(pBufList != NULL);

    for (bufId = 0; bufId < pBufList->numBuf; bufId++)
    {
        OSA_assert(bufId < SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);
        OSA_assert(pBufList->buffers[bufId]->chNum == 0);

        status = DispDistSrcLink_deleteBuffer(pObj, pBufList->buffers[bufId]);
        OSA_assert(status == OSA_SOK);

        pObj->linkStats.putEmptyBufCount++;
	pObj->inSerial++;

    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Get the buffer and queue information about source link.
 *
 * \param  ptr  [IN] Task Handle
 * \param  info [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
*/
Int32 DispDistSrcLink_getInfo(Void * ptr, System_LinkInfo * info)
{
    OSA_TskHndl *pTsk = (OSA_TskHndl *) ptr;

    DispDistSrcLink_Obj *pObj = (DispDistSrcLink_Obj *) pTsk->appData;

    memcpy(info, &pObj->linkInfo, sizeof(System_LinkInfo));

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief Function to start the link.
 *
 * This function signals the workder thread to send a new buffer
 *
 * \param  pObj           [IN] Disp Dist Src link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_start(DispDistSrcLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    struct v_ctrl_provider_create create = {0};
    int ret;

    pObj->v_fd = open((const char *)pObj->createArgs.vDrmControllerName, O_RDWR);
    OSA_assert(pObj->v_fd >= 0);

    create.object_id = pObj->createArgs.vDrmControllerObjectId;
    if(pObj->createArgs.vDrmControllerObjectType == DISP_DIST_SRC_LINK_DRM_OBJECT_TYPE_CRTC)
    {
        create.connection_type = V_CTRL_CONNECTION_TYPE_CRTC;
    }
    else if(pObj->createArgs.vDrmControllerObjectType == DISP_DIST_SRC_LINK_DRM_OBJECT_TYPE_PLANE)
    {
        create.connection_type = V_CTRL_CONNECTION_TYPE_PLANE;
    }
    else
    {
        OSA_assert(0);
    }

    ret = ioctl(pObj->v_fd, V_CTRL_IOCTL_PROVIDER_CREATE, &create);
    OSA_assert(ret == 0);

    pObj->provider_id = create.prov_id;

    /* Now, create the worker thread and wait for its signal */
    status = OSA_thrCreate(&pObj->workThread, DispDistSrcLink_workLoop, OSA_THR_PRI_DEFAULT, OSA_THR_STACK_SIZE_DEFAULT, pObj);
    OSA_assert(status == OSA_SOK);
    return status;
}

/**
 ******************************************************************************
 *
 * \brief Function to stop the link.
 *
 * Post this call, buffers will not be sent to output queue
 *
 * \param  pObj           [IN] Null Src link global handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_stop(DispDistSrcLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    struct v_ctrl_provider_destroy destroy = {0};
    int ret;

    status = OSA_thrDelete(&pObj->workThread);
    OSA_assert(status == OSA_SOK);

    destroy.prov_id = pObj->provider_id;
    ret = ioctl(pObj->v_fd, V_CTRL_IOCTL_PROVIDER_DESTROY, &destroy);
    OSA_assert(ret == 0);

    close(pObj->v_fd);

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Disp Dist Src API for link. Link gets created using this function.
 *
 * Sets up link data structure, allocates and queue buffers. Makes link ready
 * for operation.
 *
 * \param  pObj     [IN] Disp Dist Src link global handle
 * \param  pPrm    [IN] Disp Dist Src link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_create(DispDistSrcLink_Obj * pObj,
                         const DispDistSrcLink_CreateParams * pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkChInfo *pChInfo;

    /*
    *Copying Create arguments into Link object from the parametes passed by app
    */
    memcpy(&pObj->createArgs, pPrm, sizeof(pObj->createArgs));

    /*
    *Setting info for next link
    */
    memset(&pObj->linkInfo, 0, sizeof(System_LinkInfo));
    pObj->linkInfo.numQue = 1;
    pObj->linkInfo.queInfo[0].numCh = 1;

    pChInfo = &pObj->linkInfo.queInfo[0].chInfo[0];

    DispDistSrcLink_planeInfoForWidthAndFormat(pObj->createArgs.width, pObj->createArgs.height, pObj->createArgs.format, 0, &pChInfo->pitch[0], NULL, NULL, NULL);
    DispDistSrcLink_planeInfoForWidthAndFormat(pObj->createArgs.width, pObj->createArgs.height, pObj->createArgs.format, 1, &pChInfo->pitch[1], NULL, NULL, NULL);
    DispDistSrcLink_planeInfoForWidthAndFormat(pObj->createArgs.width, pObj->createArgs.height, pObj->createArgs.format, 2, &pChInfo->pitch[2], NULL, NULL, NULL);
    pChInfo->width = pObj->createArgs.width;
    pChInfo->height = pObj->createArgs.height;
    pChInfo->startX = 0;
    pChInfo->startY = 0;
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags, pObj->createArgs.format);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags, SYSTEM_SF_PROGRESSIVE);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags, SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

    status = OSA_queCreate(&pObj->outThrBufQue, DISP_DIST_SRC_LINK_QUEUE_LEN);
    OSA_assert(status == OSA_SOK);

    /*This flag is set when first buffer is sent to next link.
    * Resetting it at create time.
    */
    pObj->isFirstBufferSent = (Bool)FALSE;

    pObj->inSerial = 0;
    pObj->outSerial = 0;

    return status;
}

/**
 ******************************************************************************
 *
 * \brief Delete disp dist source link
 *
 *
 * \param  pObj         [IN] Disp Dist source link object
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_delete(DispDistSrcLink_Obj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = OSA_queDelete(&pObj->outThrBufQue);
    OSA_assert(status == OSA_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print statistics like FPS, callback time etc.
 *
 *  \param pObj         [IN] Disp Dist Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DispDistSrcLink_printLinkStats(DispDistSrcLink_Obj * pObj)
{
    OSA_printLinkStatistics(&pObj->linkStats,
                              "DISP_DIST_SRC",
                              (Bool)TRUE);

    OSA_printLatency("DISP_DIST_SRC",
                       &pObj->linkLatency,
                       &pObj->srcToLinkLatency,
                        TRUE
                       );
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print disp dist source link buffer statistics
 *
 *  \param pObj         [IN] Disp dist Source link object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DispDistSrcLink_printBufferStatus(DispDistSrcLink_Obj * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 ******************************************************************************
 *
 * \brief This function is the implementation of Run state of link.
 *
 * In this state link waits for command from application or next link.
 * Basically all are control commands except the new_data command where link
 * puts data in
 * output queue. After that it sends command to next link.
 *
 * \param  pObj     [IN] Null Src link object
 * \param  pTsk     [IN] Null Src link Task handle
 * \param  pMsg     [IN] Message for the link. Contains command and args.
 * \param  done     [IN] Flag to exit idle state.
 * \param  ackMsg   [IN] Flag to decide whether to send ack message or not
 *                          to caller
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 ******************************************************************************
 */
Int32 DispDistSrcLink_tskRun(DispDistSrcLink_Obj * pObj, OSA_TskHndl * pTsk,
                         OSA_MsgHndl ** pMsg, Bool * done, Bool * ackMsg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool runDone, runAckMsg;
    OSA_MsgHndl *pRunMsg;
    UInt32 cmd;

    /* READY loop done and ackMsg status */
    *done = (Bool)FALSE;
    *ackMsg = (Bool)FALSE;
    *pMsg = NULL;

    /* RUN loop done and ackMsg status */
    runDone = (Bool)FALSE;
    runAckMsg = (Bool)FALSE;

    /* RUN state loop */
    while (!runDone)
    {
        /* wait for message */
        status = OSA_tskWaitMsg(pTsk, &pRunMsg);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }

        /* extract message command from message */
        cmd = OSA_msgGetCmd(pRunMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_NEW_DATA:
                /* ACK or free message before proceding */
                OSA_tskAckOrFreeMsg(pRunMsg, status);

                /* new data needs to be processed*/
                status = DispDistSrcLink_processData(pObj);
                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    /* in case of error exit RUN loop */
                    runDone = (Bool)TRUE;

                    /* since message is already ACK'ed or free'ed do not ACK
                                    * or free it again */
                    runAckMsg = (Bool)FALSE;
                }
                break;

            case SYSTEM_CMD_STOP:
                /* stop RUN loop and goto READY state */
                runDone = (Bool)TRUE;

                /* ACK message after actually stopping outside the RUN loop */
                runAckMsg = (Bool)TRUE;
                break;

            case SYSTEM_CMD_DELETE:

                /* stop RUN loop and goto IDLE state */

                /* exit RUN loop */
                runDone = (Bool)TRUE;

                /* exit READY loop */
                *done = (Bool)TRUE;

                /* ACK message after exiting READY loop */
                *ackMsg = (Bool)TRUE;

                /* Pass the received message to the READY loop */
                *pMsg = pRunMsg;

                break;

            case SYSTEM_CMD_PRINT_STATISTICS:
                /* print the null source link statistics*/
                DispDistSrcLink_printLinkStats(pObj);
                /* ACK or free message before proceding */
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            case SYSTEM_CMD_PRINT_BUFFER_STATISTICS:
                /* print the null source link output buffer queue status*/
                DispDistSrcLink_printBufferStatus(pObj);
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;

            default:

                /* invalid command for this state ACK it, continue RUN loop */
                OSA_tskAckOrFreeMsg(pRunMsg, status);
                break;
        }

    }

    /* RUN loop exited, stop the link */
    DispDistSrcLink_stop(pObj);

    /* ACK message if not ACKed earlier */
    if (runAckMsg)
    {
        OSA_tskAckOrFreeMsg(pRunMsg, status);
    }

    return status;
}

/**
 ******************************************************************************
 *
 * \brief This function is the implementation of Idle state.
 *
 * \param  pTsk [IN] Task Handle
 * \param  pMsg [IN] Message Handle
 *
 * \return  void
 *
 ******************************************************************************
 */
int DispDistSrcLink_tskMain(struct OSA_TskHndl *pTsk, OSA_MsgHndl *pMsg, Uint32 curState )
{
    UInt32 cmd = OSA_msgGetCmd(pMsg);
    Bool ackMsg, done = (Bool)FALSE;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    DispDistSrcLink_Obj *pObj;

    /* IDLE state */

    pObj = (DispDistSrcLink_Obj *) pTsk->appData;

    if (cmd != SYSTEM_CMD_CREATE)
    {
        /* invalid command recived in IDLE status, be in IDLE state and ACK
        * with error status */
        OSA_tskAckOrFreeMsg(pMsg, OSA_EFAIL);
        return OSA_EFAIL;
    }

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        /* Create command received, create the link */
        status = DispDistSrcLink_create(pObj, OSA_msgGetPrm(pMsg));

        /* ACK based on create status */
        OSA_tskAckOrFreeMsg(pMsg, status);

        /* create success, entering READY state */
        done = (Bool)FALSE;
        ackMsg = (Bool)FALSE;
    }

    /* READY state loop */
    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        while (!done)
        {
            /* wait for message */
            status = OSA_tskWaitMsg(pTsk, &pMsg);
            if (status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }

            /* extract message command from message */
            cmd = OSA_msgGetCmd(pMsg);

            switch (cmd)
            {
                case SYSTEM_CMD_START:
                    /* Start mull source driver */
                    status = DispDistSrcLink_start(pObj);

                    /* ACK based on create status */
                    OSA_tskAckOrFreeMsg(pMsg, status);

                    /* if start status is error then remain in READY state */
                    if (status == SYSTEM_LINK_STATUS_SOK)
                    {
                        /* start success, entering RUN state */
                        status =
                            DispDistSrcLink_tskRun(
                                pObj, pTsk, &pMsg, &done, &ackMsg);
                    }

                    break;
                case SYSTEM_CMD_DELETE:
                    /* exit READY state */
                    done = (Bool)TRUE;
                    ackMsg = (Bool)TRUE;
                    break;

                default:
                    /* invalid command for this state ACK it and continue READY
                     * loop */
                    OSA_tskAckOrFreeMsg(pMsg, status);
                    break;
            }
        }

        /* exiting READY state, delete link */
        DispDistSrcLink_delete(pObj);

        /* ACK message if not previously ACK'ed */
        if ((pMsg != NULL) && ((Bool)TRUE == ackMsg))
        {
            OSA_tskAckOrFreeMsg(pMsg, status);
        }
    }

    /* entering IDLE state */
    return OSA_SOK;
}



Int32 DispDistSrcLink_init(void)
{
    Int32 status;
    System_LinkObj linkObj;
    UInt32 dispDistSrcId;
    DispDistSrcLink_Obj *pObj;
    UInt32 procId = System_getSelfProcId();

    srand(time(0));

    for (dispDistSrcId = 0U; dispDistSrcId < DISP_DIST_SRC_LINK_OBJ_MAX; dispDistSrcId ++)
    {
        pObj = &gDispDistSrcLink_obj[dispDistSrcId];

        memset(pObj, 0U, sizeof(*pObj));

        pObj->tskId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_DISPDISTSRC_LINK_0 +
            dispDistSrcId);

        memset(&linkObj, 0, sizeof(linkObj));
        linkObj.pTsk = &pObj->tsk;
        linkObj.linkGetFullBuffers  = &DispDistSrcLink_getFullBuffers;
        linkObj.linkPutEmptyBuffers = &DispDistSrcLink_putEmptyBuffers;
        linkObj.getLinkInfo         = &DispDistSrcLink_getInfo;

        System_registerLink(pObj->tskId, &linkObj);

        /*
         * Create link task, task remains in IDLE state.
         * ipcOutLink_tskMain is called when a message command is received.
         */
        snprintf(pObj->tskName, 32, "DISP_DIST_SRC_%u", (unsigned int)dispDistSrcId);
        status = OSA_tskCreate(&pObj->tsk,
                               DispDistSrcLink_tskMain,
                               DISP_DIST_SRC_LINK_TSK_PRI,
                               DISP_DIST_SRC_LINK_TSK_STACK_SIZE,
                               0,
                               pObj,
                               pObj->tskName);
        OSA_assert(status == OSA_SOK);
        Vps_printf(" %s : Init done - linkid-0x%x\n", pObj->tskName, pObj->tskId);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief De-init function for Null link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 DispDistSrcLink_deInit(void)
{
    UInt32 dispDistSrcId;

    for (dispDistSrcId = 0; dispDistSrcId < DISP_DIST_SRC_LINK_OBJ_MAX; dispDistSrcId++)
    {
        OSA_tskDelete(&gDispDistSrcLink_obj[dispDistSrcId].tsk);
        Vps_printf(" %s : DeInit done - linkid-0x%x\n",
            gDispDistSrcLink_obj[dispDistSrcId].tskName, gDispDistSrcLink_obj[dispDistSrcId].tskId);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
