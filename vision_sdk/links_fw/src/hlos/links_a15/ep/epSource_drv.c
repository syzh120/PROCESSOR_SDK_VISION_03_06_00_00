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
 *         between Vision subsystem and VIVI framework
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "epLink_priv.h"
#include <include/link_api/system_common.h>
#include <links_fw/src/hlos/osa/include/osa_mem.h>

/**
 *******************************************************************************
 *
 * \brief Create Endpoint(EP) source driver
 *
 *        Following happens during create phase,
 *        - Call 'set link info' to create the chaanel configuration.
 *          When the next link asks link info it gives back
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSourceCreate(EpLink_obj *pObj, EpLink_ConfigSource *srcCfg)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Create in progress !!!\n",
               pObj->instId
               );
#endif
    /**
     * The srcCfg must have been populated by the application
     * TODO check sanity of the information.
     */
    pObj->linkInfo.numQue = 1;
    memcpy(&pObj->linkInfo.queInfo[0], &srcCfg->queInfo, sizeof(System_LinkQueInfo));

    status = OSA_bufCreate(&pObj->outBufQue, FALSE, FALSE);

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Create Done !!!\n",
           pObj->instId
          );
#endif
    /**
     * TODO
     * reset timestamp to cmpute latency.
     */
    return status;
}


/**
 *******************************************************************************
 *
 * \brief Start Endpoint(EP) Source driver
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSourceStart(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Start in progress !!!\n",
               pObj->instId
               );
#endif

    /* currently nothing to do */

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Start Done !!!\n",
           pObj->instId
          );
#endif

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Stop Endpoint(EP) Source driver
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSourceStop(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Stop in progress !!!\n",
               pObj->instId
               );
#endif

    /* currently nothing to do */

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Stop Done !!!\n",
           pObj->instId
          );
#endif

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete Endpoint(EP) Source driver
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSourceDelete(EpLink_obj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Delete in progress !!!\n",
               pObj->instId
               );
#endif
    /**
     * We will just close the que at this stage
     *
     * TODO we will have to do something more here for a source link.
     * The source link will receive callbacks from next link on the return
     * path of the buffers. And it will execute asynchronously in the context
     * of another thread. However, the link might have been deleted and que
     * closed. We shouldn't be calling the post_buf() in that case.
     *
     * However, we can rely on the fact that trying to post a buffer to an
     * already closed mqueue will fail! 
     * This problem wouldn't occur for the sink because its previous
     * links would have stopped giving data to it, via SYSTEM_CMD_NEW_DATA.
     *
     * We should try to flush the input message queue.
     *
     */
    status = EpLink_drvCloseQueHandle(pObj);

    /* We need to clean up the source's local buffer que */
    OSA_bufDelete(&pObj->outBufQue);

#ifdef SYSTEM_DEBUG_EP
    Vps_printf(" EP_%u   : EP_SOURCE Delete Done !!!\n",
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
 *        - Application will provide buffers through VIVI.
 *        - Post the buffers into a local Que and send command to next link
 *
 * \param  pObj     [IN]  Link object
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EpLink_drvSourceProcessBuffers(EpLink_obj *pObj, System_Buffer *pBuffer)
{
    Int32 status    = SYSTEM_LINK_STATUS_SOK;

    /**
     * At this point we are assuming the input addresses are all virtual.
     * And we dont neecd to perform any conversion.
     */

    /**
     * TODO
     * update timestamp to cmpute latency.
     */
    pBuffer->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();
    status = OSA_bufPutFullBuffer(&pObj->outBufQue, pBuffer);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = System_sendLinkCmd(pObj->createArgs.outQueParams.nextLink,
                    SYSTEM_CMD_NEW_DATA, NULL);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to get empty buffers from next
 *        link.
 *
 *        We are going to put the buffers into queue from where VIVI can pick
 *
 *
 * \param  pObj     [IN]  Link object
 * \param  pBufList [IN] Pointer to Buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EpLink_drvSourcePutEmptyBuffers(EpLink_obj *pObj,
                                    System_BufferList *pBufList)
{

    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 i ;

    System_Buffer     *pBuffer;

    OSA_assert(pBufList->numBuf >= 1);
    for (i = 0; i < pBufList->numBuf; i++) {
        pBuffer = pBufList->buffers[i];

        /**
         * At this point we are assuming the input addresses are all virtual.
         * And we dont neecd to perform any conversion.
         */

        /**
         * TODO
         * update timestamp to cmpute latency.
         */
        pBuffer->linkLocalTimestamp = OSA_getCurGlobalTimeInUsec();
        status = (pObj->post_buf)(&pObj->ep_ctx, pBuffer);
        if (status < 0)
            Vps_printf("EP_%u   : EP_SOURCE: Failed to queue buffer\n", pObj->instId);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Callback function implemented by link to provide full buffers to next
 *        link.
 *
 * \param  pObj     [IN]  Link object
 * \param  pBufList [IN] Pointer to Buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EpLink_drvSourceGetFullBuffers(EpLink_obj *pObj,
                                    System_BufferList *pBufList)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /**
     * At this point we are assuming the input addresses are all virtual.
     * And we dont neecd to perform any conversion.
     */
    status =  OSA_bufGetFull(&pObj->outBufQue, pBufList, OSA_TIMEOUT_NONE);

    return status;
}

