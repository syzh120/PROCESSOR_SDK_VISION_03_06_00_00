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
 * \file epLink.c
 *
 * \brief  This file has the implementation of Endpoint Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (May 2015) : [SM] First version of endpoint sink driver
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "epLink_priv.h"
#include <links_fw/src/hlos/osa/include/osa_mem.h>

/**
 *******************************************************************************
 *
 * \brief Create Endpoint(EP) sink driver
 *
 *        Following happens during create phase,
 *        - Call 'get link info' on previous link.
 *          When link from other processors asks link info it gives back
 *          this link info to the next link (Endpoint)
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSinkCreate(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Create in progress !!!\n",
               pObj->instId
               );
#endif

    /* get previous link info */
    status = System_linkGetInfo(
                    pObj->createArgs.inQueParams.prevLinkId,
                    &pObj->linkInfo);

    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* validate previous link que ID */
    OSA_assert(pObj->createArgs.inQueParams.prevLinkQueId <
                  pObj->linkInfo.numQue);

    /*
     * Setup current link que information
     * Current queue is considered to have one output queue
     * with que information same as selected previous link queue
     */
    pObj->linkInfo.numQue = 1;
    memcpy(&pObj->linkInfo.queInfo[0],
           &pObj->linkInfo.queInfo
                [pObj->createArgs.inQueParams.prevLinkQueId],
           sizeof(pObj->linkInfo.queInfo[0]));

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Create Done !!!\n",
           pObj->instId
          );
#endif
    OSA_resetLatency(&pObj->srcToEpSinkLatency);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Start Endpoint(EP) sink driver
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSinkStart(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Start in progress !!!\n",
               pObj->instId
               );
#endif

    /* currently nothing to do */

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Start Done !!!\n",
           pObj->instId
          );
#endif

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Stop Endpoint(EP) sink driver
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSinkStop(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Stop in progress !!!\n",
               pObj->instId
               );
#endif

    /* currently nothing to do */

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Stop Done !!!\n",
           pObj->instId
          );
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete Endpoint(EP) sink driver
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSinkDelete(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Delete in progress !!!\n",
               pObj->instId
               );
#endif
    /**
     * We will just close the que at this stage
     *
     */
    status = EpLink_drvCloseQueHandle(pObj);

    if (pObj->srcToEpSinkLatency.count) {
        Vps_printf("Source to EpSink %x Latency : Avg = %8d us, Min = %8d us, Max = %8d us, \r\n",
                     pObj->linkId,
                     (UInt32)(pObj->srcToEpSinkLatency.accumulatedLatency/pObj->srcToEpSinkLatency.count),
                     (UInt32)pObj->srcToEpSinkLatency.minLatency,
                     (UInt32)pObj->srcToEpSinkLatency.maxLatency
                 );
        Vps_printf("\n");
    }
    OSA_resetLatency(&pObj->srcToEpSinkLatency);

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SINK Delete Done !!!\n",
           pObj->instId
          );
#endif

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Process buffer's
 *
 *        - Previous link will notify when buffers are available
 *            to be sent across processors
 *
 *        - Pick the buffers from the bufList and post it to the que
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSinkProcessBuffers(EpLink_obj *pObj)
{
    Int32 i;
    Int32 status    = SYSTEM_LINK_STATUS_SOK;
    System_Buffer     *pBuffer;
    System_BufferList bufList;

#if !defined(LINUX_BUILD)
    System_BufferType buf_type;
    System_VideoFrameCompositeBuffer *compBuf;
    System_VideoFrameBuffer *vidBuf;
    System_EglPixmapVideoFrameBuffer *eglBuf;
    System_LinkChInfo *chInfo;
    System_LinkChInfo *srcChInfo;
    srcChInfo = &pObj->linkInfo.queInfo[0].chInfo[0];
    Int32 j;
#endif


    bufList.numBuf = 0;

    status = System_getLinksFullBuffers(
                    pObj->createArgs.inQueParams.prevLinkId,
                    pObj->createArgs.inQueParams.prevLinkQueId,
                    &bufList);

    for (i=0; i < bufList.numBuf; i++) {

        pBuffer = bufList.buffers[i];
        OSA_assert(pBuffer != NULL);

        /* let's update the timestamp at which we received the buffer */
        pBuffer->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();

#if !defined(LINUX_BUILD)
        buf_type = pBuffer->bufType;
        if (buf_type == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER) {
            /* Composite video frame - multiple frames in the same buffer
             * interprete payload as System_VideoFrameCompositeBuffer */
            compBuf = pBuffer->payload;
            chInfo = &compBuf->chInfo;
            compBuf->flags = srcChInfo->flags;
            for (j=0; j<compBuf->numFrames; j++) {
#ifndef QNX_BUILD
                /* TODO Handle multi-planar buffers */
                compBuf->bufAddr[0][j] = (Void*) OSA_memVirt2Phys((UInt32)compBuf->bufAddr[0][j],
                                                              OSA_MEM_REGION_TYPE_AUTO);
#endif
            }
        } else if (buf_type == SYSTEM_BUFFER_TYPE_VIDEO_FRAME) {
            /* Single video frame - only one frame in the buffer
             * interprete payload as System_VideoFrameBuffer */
            vidBuf = pBuffer->payload;
            chInfo = &vidBuf->chInfo;
            vidBuf->flags = srcChInfo->flags;
#ifndef QNX_BUILD
            vidBuf->bufAddr[0] = (Void*) OSA_memVirt2Phys((UInt32)vidBuf->bufAddr[0],
                                                          OSA_MEM_REGION_TYPE_AUTO);
#endif
        } else if (buf_type == SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME) {
            eglBuf = pBuffer->payload;
            chInfo = &eglBuf->chInfo;
            eglBuf->flags = srcChInfo->flags;
        } else {
            status    = SYSTEM_LINK_STATUS_EFAIL;
            return status;
        }

        chInfo->flags = srcChInfo->flags;
        chInfo->startY = srcChInfo->startY;
        chInfo->startY = srcChInfo->startY;
        chInfo->width = srcChInfo->width;
        chInfo->height = srcChInfo->height;

        for(j=0; j<SYSTEM_MAX_PLANES; j++) {
            chInfo->pitch[j] = srcChInfo->pitch[j];
        }
#endif
        /* we are now ready to post the buffer into the que */
        status = (pObj->post_buf)(&pObj->ep_ctx, pBuffer);
        if (status < 0)
            Vps_printf("EP_%u   : EP_SINK: Failed to queue buffer\n", pObj->instId);

        /* let's find the latency now */
        OSA_updateLatency(&pObj->srcToEpSinkLatency, pBuffer->srcTimestamp);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 *        We are going to call the 'putEmptyBuf' callback function of the
 *        preceding link.
 *
 * \param  pObj     [IN]  Link object
 * \param  pBufList [IN] Pointer to link information handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EpLink_drvSinkPutEmptyBuffers(EpLink_obj *pObj,
                                    System_BufferList *pBufList)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
#ifndef QNX_BUILD
    Int32 j;
    System_Buffer     *pBuffer;
    System_BufferType buf_type;
    System_VideoFrameCompositeBuffer *compBuf;
    System_VideoFrameBuffer *vidBuf;

    OSA_assert(pBufList->numBuf == 1);

    pBuffer = pBufList->buffers[0];
    buf_type = pBuffer->bufType;

    if (buf_type == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER) {
            /* Composite video frame - multiple frames in the same buffer
             * interprete payload as System_VideoFrameCompositeBuffer */
            compBuf = pBuffer->payload;
            for (j=0; j<compBuf->numFrames; j++) {
                /* TODO Handle multi-planar buffers */
                compBuf->bufAddr[0][j] = (Void*) OSA_memPhys2Virt((UInt32)compBuf->bufAddr[0][j],
                                                              OSA_MEM_REGION_TYPE_AUTO);
            }
    } else if (buf_type == SYSTEM_BUFFER_TYPE_VIDEO_FRAME) {
            /* Single video frame - only one frame in the buffer
             * interprete payload as System_VideoFrameBuffer */
             vidBuf = pBuffer->payload;
             vidBuf->bufAddr[0] = (Void*) OSA_memPhys2Virt((UInt32)vidBuf->bufAddr[0],
                                                          OSA_MEM_REGION_TYPE_AUTO);
    }
#endif

    status = System_putLinksEmptyBuffers(
            pObj->createArgs.inQueParams.prevLinkId,
            pObj->createArgs.inQueParams.prevLinkQueId,
            pBufList);

    return status;
}
