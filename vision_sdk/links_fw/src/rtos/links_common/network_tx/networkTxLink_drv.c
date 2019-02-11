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


 /*****************************************************************************
  *  INCLUDE FILES
  *****************************************************************************
  */
#include "networkTxLink_priv.h"

#define NETWORK_TX_SERVER_CLOSED        (0U)
#define NETWORK_TX_SERVER_LISTEN        (1U)
#define NETWORK_TX_SERVER_CONNECTED     (2U)

#define NETWORK_TX_SERVER_POLL_TIMEOUT  (10U)

/*****************************************************************************
 *  Function declarations
 *****************************************************************************
 */
Int32 NetworkTxLink_drvWaitConnect(NetworkTxLink_Obj *pObj,
                                    NetworkTxLink_NetworkTxObj *pNetTxObj);
Int32 NetworkTxLink_drvWriteHeader(NetworkTxLink_Obj *pObj,
                                    NetworkTxLink_NetworkTxObj *pNetTxObj,
                                    NetworkRx_CmdHeader *pHeader);
Int32 NetworkTxLink_drvWritePayload(NetworkTxLink_Obj *pObj,
                        NetworkTxLink_NetworkTxObj *pNetTxObj,
                        UInt32 numBuf,
                        UInt8  *bufAddr[],
                        UInt32 bufSize[]);

Int32 NetworkTxLink_drvCreate(NetworkTxLink_Obj *pObj)
{
    NetworkTxLink_NetworkTxObj *pNetTxObj = &pObj->netTxObj;
    Int32 status;

    Network_sessionOpen(NULL);

    status = Network_open(
                    &pNetTxObj->sockObj,
                    pObj->createArgs.networkServerPort
                    );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    pNetTxObj->state = NETWORK_TX_SERVER_LISTEN;

    Vps_printf(" NETWORK_TX: NETWORK_TX: Server listening (port=%d) !!!\n",
        pObj->createArgs.networkServerPort);

    return status;
}

Int32 NetworkTxLink_drvDelete(NetworkTxLink_Obj *pObj)
{
    NetworkTxLink_NetworkTxObj *pNetTxObj = &pObj->netTxObj;
    Int32 status;

    status = Network_close(&pNetTxObj->sockObj, (Bool)TRUE);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    Network_sessionClose(NULL);

#if (defined(NSP_TFDTP_INCLUDE))
    /* Make sure TFDTP is not alredy closed by client disconnection  */
    if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
    {
        if(NULL != pNetTxObj->sockObj.hTfdtp)
        {
            /* Close TFDTP channel */
            Network_deInitTfdtpChannel(&pNetTxObj->sockObj, TFDTP_CHANNEL_MODE_TX);
            /* If TFDTP mode is enabled, close TFDTP stack */
            Network_deInitTfdtp(&pNetTxObj->sockObj);
        }
    }
#endif
    pNetTxObj->state = NETWORK_TX_SERVER_CLOSED;

    Vps_printf(" NETWORK_TX: NETWORK_TX: Server Closed (port=%d) !!!\n",
        pObj->createArgs.networkServerPort);

    return status;
}

Int32 NetworkTxLink_drvWaitConnect(NetworkTxLink_Obj *pObj,
                                    NetworkTxLink_NetworkTxObj *pNetTxObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 isConnected;

    if(pNetTxObj->state == NETWORK_TX_SERVER_LISTEN)
    {
        isConnected = Network_waitConnect(
                    &pNetTxObj->sockObj,
                    NETWORK_TX_SERVER_POLL_TIMEOUT);

        /* MISRA.UNREACH.GEN
         * MISRAC_2004 Rule_14.1
         * MISRAC_WAIVER:
         * Code is currently unreachable but as the implementation of the
         * function changes, it will not be unreachable.
         */
        if((Int32)TRUE == isConnected)
        {
            /* connected to client */
            pNetTxObj->state = NETWORK_TX_SERVER_CONNECTED;

#if (defined(NSP_TFDTP_INCLUDE))
            if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
            {
                /* If TFDTP mode is enabled, open TFDTP stack */
                Network_initTfdtp(&pNetTxObj->sockObj);
                /* Get channel open parameters from client & open TFDTP channel */
                Network_getTfdtpChParams(&pNetTxObj->sockObj, TFDTP_CHANNEL_MODE_TX);
                /* Open TFDTP channel */
                Network_initTfdtpChannel(&pNetTxObj->sockObj, TFDTP_CHANNEL_MODE_TX);
                /* Start TFDTP */
                Network_startTfdtp(&pNetTxObj->sockObj);
            }
#endif

            Vps_printf(" NETWORK_TX: NETWORK_TX: Connected to client (port=%d) !!!\n",
                pObj->createArgs.networkServerPort);
        }
        else
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    return status;
}

Int32 NetworkTxLink_drvWriteHeader(NetworkTxLink_Obj *pObj,
                                    NetworkTxLink_NetworkTxObj *pNetTxObj,
                                    NetworkRx_CmdHeader *pHeader)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pHeader->header = NETWORK_TX_HEADER;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * This is used to ensure address alignment required by hardware.
     */
    /* write header to client, if write failed, then client
     * disconnected, so go back to listening
     */
    status = Network_write(&pNetTxObj->sockObj,
                (UInt8*)pHeader,
                sizeof(NetworkRx_CmdHeader)
                );

    /* MISRA.UNREACH.GEN
     * MISRAC_2004 Rule_14.1
     * MISRAC_WAIVER:
     * Code is currently unreachable but as the implementation of the
     * function changes, it will not be unreachable.
     */
    if(status!=SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf(" NETWORK_TX: NETWORK_TX: Disconnected from client "
                   "while writing header (port=%d)!!!\n",
                    pObj->createArgs.networkServerPort
                   );

        Network_close(&pNetTxObj->sockObj, FALSE);

#if (defined(NSP_TFDTP_INCLUDE))
        /* Close TFDTP channel and deinit TFDTP stack, otherwise
         * after client reconnection TFDTP will not have free
         * channel and fail */
        if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
        {
            /* Close TFDTP channel */
            Network_deInitTfdtpChannel(&pNetTxObj->sockObj, TFDTP_CHANNEL_MODE_TX);
            /* Close TFDTP handle and stop TFDTP (No separate stop function ) */
            Network_deInitTfdtp(&pNetTxObj->sockObj);
        }
#endif
        pNetTxObj->state = NETWORK_TX_SERVER_LISTEN;
    }

    return status;
}

Int32 NetworkTxLink_drvWritePayload(NetworkTxLink_Obj *pObj,
                        NetworkTxLink_NetworkTxObj *pNetTxObj,
                        UInt32 numBuf,
                        UInt8  *bufAddr[],
                        UInt32 bufSize[])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;
    Ptr alignedBufPtr;
    UInt32 alignedBufSize;
    UInt32 bufAddrInInt;
#if (defined(NSP_TFDTP_INCLUDE))
    UInt32 ack;
    Int32 retry;
#endif

    for(i=0; i<numBuf; i++)
    {
        if(status==SYSTEM_LINK_STATUS_SOK)
        {
            alignedBufSize =  bufSize[i] + 128U;
            alignedBufSize = SystemUtils_align(alignedBufSize, 128U);
            /* MISRA.CAST.PTR_TO_INT
            * MISRAC_2004 Rule_11.3
            * MISRAC_WAIVER:
            * This is used to ensure address alignment required by hardware.
            */
            bufAddrInInt = (UInt32)bufAddr[i];
            bufAddrInInt = SystemUtils_floor(bufAddrInInt, 128U);
            alignedBufPtr = (Ptr)bufAddrInInt;
            Cache_inv(
                    alignedBufPtr,
                    alignedBufSize,
                    (UInt16)Cache_Type_ALLD,
                    (Bool)TRUE
                    );
            if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP)
            {
                status = Network_write(&pNetTxObj->sockObj,
                            bufAddr[i],
                            bufSize[i]
                            );
            }
#if (defined(NSP_TFDTP_INCLUDE))
            else if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
            {
                if (pNetTxObj->sockObj.retryCount > 0U)
                {
                    retry = pNetTxObj->sockObj.retryCount;
                    do
                    {
                        status = Network_tfdtpWrite(&pNetTxObj->sockObj,
                                bufAddr[i],
                                bufSize[i]
                                );

                        ack = Network_tfdtpWaitAck(&pNetTxObj->sockObj);
#if (defined(SYSTEM_DEBUG_NULL_RT))
                        if(ack != TFDTP_TRANSMIT_OK)
                        {
                            Vps_printf("NETWORK_TX: TFDTP client sent NACK, retrying !");
                        }
#endif
                        retry--;
                    }
                    while ((retry >= 0) && (ack != TFDTP_TRANSMIT_OK));

                    if( ack != TFDTP_TRANSMIT_OK)
                    {
                        Vps_printf("NETWORK_TX: Network_tfdtpWrite() Failed for BUF%d !!", i);
                    }
                }
                else
                {
                    status = Network_tfdtpWrite(&pNetTxObj->sockObj,
                            bufAddr[i],
                            bufSize[i]
                            );
                }
            }
#endif
            else
            {
                Vps_printf(" NETWORK_TX: Invalid transmitDataType \n");
            }
            /* MISRA.UNREACH.GEN
             * MISRAC_2004 Rule_14.1
             * MISRAC_WAIVER:
             * Code is currently unreachable but as the implementation of the
             * function changes, it will not be unreachable.
             */
            if(status!=SYSTEM_LINK_STATUS_SOK)
            {
                Vps_printf(" NETWORK_TX: NETWORK_TX: Disconnected from client "
                           "while writing payload (port=%d)!!!\n",
                            pObj->createArgs.networkServerPort
                           );
                Network_close(&pNetTxObj->sockObj, FALSE);
#if (defined(NSP_TFDTP_INCLUDE))
                if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
                {
                    /* Close TFDTP channel */
                    Network_deInitTfdtpChannel(&pNetTxObj->sockObj, TFDTP_CHANNEL_MODE_TX);
                    /* Close TFDTP handle and stop TFDTP (No separate stop function ) */
                    Network_deInitTfdtp(&pNetTxObj->sockObj);
                }
#endif
                pNetTxObj->state = NETWORK_TX_SERVER_LISTEN;
                break;
            }

#if (defined(SYSTEM_DEBUG_NULL_RT))
            Vps_printf(" NETWORK_TX: NETWORK_TX: BUF%d: %d bytes sent (port=%d)!!!\n",
                i,
                bufSize[i],
                pObj->createArgs.networkServerPort
                );
#endif
        }
    }

    return status;
}

Int32 NetworkTxLink_drvSendData(NetworkTxLink_Obj * pObj, UInt32 queId,
                                 UInt32 channelId,
                                 const System_Buffer *pBuffer)
{
    NetworkTxLink_NetworkTxObj *pNetTxObj = &pObj->netTxObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_VideoDataFormat dataFormat;
    System_VideoFrameBuffer *videoFrame;
    System_VideoFrameCompositeBuffer *compVideoFrame;
    System_BitstreamBuffer *bitstreamBuf;
    System_MetaDataBuffer *metaBuf;
    System_LinkChInfo *pChInfo;
    UInt16 i;

    status = NetworkTxLink_drvWaitConnect(pObj, pNetTxObj);

    if(pNetTxObj->state == NETWORK_TX_SERVER_CONNECTED)
    {
        NetworkRx_CmdHeader cmdHeader;
        UInt32 bufSize;
#if (defined(NSP_TFDTP_INCLUDE))
        UInt32 ack;
#endif

        memset(&cmdHeader, 0, sizeof(cmdHeader));

        cmdHeader.chNum = channelId;

        pChInfo = &pObj->inQueInfo[queId].chInfo[channelId];

        switch(pBuffer->bufType)
        {
            case SYSTEM_BUFFER_TYPE_BITSTREAM:
                bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

                /* right now only MJPEG TX is supported */
                cmdHeader.numBuf = 1;
                cmdHeader.payloadType = NETWORK_RX_TYPE_BITSTREAM_MJPEG;
                cmdHeader.dataSize = bitstreamBuf->fillLength; /* max buffer size */
                break;

            case SYSTEM_BUFFER_TYPE_METADATA:
                metaBuf = (System_MetaDataBuffer *)pBuffer->payload;

                /* right now only MJPEG TX is supported */
                cmdHeader.numBuf = 1U;
                cmdHeader.payloadType = NETWORK_RX_TYPE_META_DATA;
                cmdHeader.dataSize = 0; /* max buffer size */

                for(i=0; i<metaBuf->numMetaDataPlanes; i++)
                {
                    cmdHeader.dataSize += metaBuf->metaFillLength[i];
                }
                break;

            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                videoFrame = (System_VideoFrameBuffer*)pBuffer->payload;
                dataFormat = (System_VideoDataFormat)
                    System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                {
                    cmdHeader.numBuf = 1;
                    bufSize =
                    (pChInfo->pitch[0U] * pChInfo->height) +
                    ((pChInfo->pitch[1U] * pChInfo->height) / 2U);

                    cmdHeader.payloadType =
                        NETWORK_RX_TYPE_VIDEO_FRAME_YUV420SP_UV;
                }
                else
                {
                    cmdHeader.numBuf = 1;
                    bufSize = pChInfo->pitch[0U] * pChInfo->height;

                    cmdHeader.payloadType =
                        NETWORK_RX_TYPE_VIDEO_FRAME_YUV422I_YUYV;
                }

                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    cmdHeader.dataSize = bufSize; /* max buffer size */
                    cmdHeader.width = pChInfo->width;
                    cmdHeader.height = pChInfo->height;
                    cmdHeader.pitch[0U] = pChInfo->pitch[0U];
                    cmdHeader.pitch[1U] = pChInfo->pitch[1U];
                }

                break;

            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER:
                compVideoFrame = (System_VideoFrameCompositeBuffer*)pBuffer->payload;
                dataFormat = (System_VideoDataFormat)
                                    System_Link_Ch_Info_Get_Flag_Data_Format(pChInfo->flags);

                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                {
                    cmdHeader.numBuf = compVideoFrame->numFrames;
                    bufSize =
                    (pChInfo->pitch[0U] * pChInfo->height) +
                    ((pChInfo->pitch[1U] * pChInfo->height) / 2U);

                    cmdHeader.payloadType =
                        NETWORK_RX_TYPE_VIDEO_FRAME_YUV420SP_UV;
                }
                else
                {
                    cmdHeader.numBuf = 1;
                    bufSize = pChInfo->pitch[0U] * pChInfo->height * compVideoFrame->numFrames;

                    cmdHeader.payloadType =
                        NETWORK_RX_TYPE_VIDEO_FRAME_YUV422I_YUYV;
                }

                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    cmdHeader.dataSize = bufSize;/* compVideoFrame->numFrames; max buffer size */
                    cmdHeader.width = pChInfo->width;
                    cmdHeader.height = pChInfo->height;
                    cmdHeader.pitch[0U] = pChInfo->pitch[0U];
                    cmdHeader.pitch[1U] = pChInfo->pitch[1U];
                }

                break;

            default:
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
        }

        /* If no payload in the buffer, return */
        if(cmdHeader.dataSize !=0)
        {
            if(status==SYSTEM_LINK_STATUS_SOK)
            {
                status = NetworkTxLink_drvWriteHeader(pObj, pNetTxObj, &cmdHeader);

    #if (defined(NSP_TFDTP_INCLUDE))
                /* In case of TFDTP we take ACK for header as well. This is needed
                 * as sometimes PC network stack buffers the header data and acks
                 * to sender. For TCP/IP header info is given when next data comesThis
                 * but for TFDTP this causes incorrect header info as header info still
                 * buffered by stack.*/
                if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
                {
                    if(status==SYSTEM_LINK_STATUS_SOK)
                    {
                        ack = Network_tfdtpWaitAck(&pNetTxObj->sockObj);
                        if (ack != TFDTP_TRANSMIT_OK)
                        {
                            status = SYSTEM_LINK_STATUS_EFAIL;
                        }
                    }
                }
#endif
            }

            if(status==SYSTEM_LINK_STATUS_SOK)
            {
                UInt32 numBuf;
                UInt8 *dataAddr[SYSTEM_MAX_META_DATA_PLANES];
                UInt32 dataSize[SYSTEM_MAX_META_DATA_PLANES];

                /* read payload data */
                switch(pBuffer->bufType)
                {
                    case SYSTEM_BUFFER_TYPE_BITSTREAM:
                        numBuf = 1U;
                        dataAddr[0U] = bitstreamBuf->bufAddr;
                        dataSize[0U] = cmdHeader.dataSize;
                        break;

                    case SYSTEM_BUFFER_TYPE_METADATA:
                        /* Sending all metadataplanes as single buffer, application needs to allocate
                         * all buffers consecutively */
                        numBuf = 1U;
                        dataSize[0U] = 0U;
                        dataAddr[0U] = metaBuf->bufAddr[0];

                        for(i=0; i<metaBuf->numMetaDataPlanes; i++)
                        {
                            dataSize[0] += metaBuf->metaFillLength[i];
                        }
                        break;

                    case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:

                        if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                        {
                            if (pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP)
                            {
                                /* For TFDTP we send both buffers in single go */
                                numBuf = 1U;
                                dataAddr[0U] = videoFrame->bufAddr[0U];
                                dataSize[0U] = ( (cmdHeader.pitch[0U]*cmdHeader.height) +
                                        ((cmdHeader.pitch[1U] * cmdHeader.height)/2U) );
                                UTILS_assert( dataSize[0U] == cmdHeader.dataSize );

                            }
                            else
                            {
                                numBuf = 2U;
                                dataAddr[0U] = videoFrame->bufAddr[0U];
                                dataAddr[1U] = videoFrame->bufAddr[1U];
                                dataSize[0U] = cmdHeader.pitch[0U]*cmdHeader.height;
                                dataSize[1U] =
                                (cmdHeader.pitch[1U] * cmdHeader.height)/2U;
                                UTILS_assert(
                                    (dataSize[0U]+dataSize[1U]) == cmdHeader.dataSize );
                            }

                        }
                        else
                        {
                            numBuf = 1U;
                            dataAddr[0] = videoFrame->bufAddr[0U];
                            dataSize[0] =
                                cmdHeader.pitch[0U] * cmdHeader.height;
                            UTILS_assert( dataSize[0] == cmdHeader.dataSize );
                        }
                        break;

                    case SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER:

                        UTILS_assert(pObj->createArgs.transmitDataType == NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP);

                        if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                        {
                            /* For TFDTP we send both buffers in single go */
                            numBuf = compVideoFrame->numFrames;

                            for (i = 0; i < numBuf; i++)
                            {
                                dataAddr[i] = compVideoFrame->bufAddr[0U][i];
                                dataSize[i] = ( (cmdHeader.pitch[0U]*cmdHeader.height) +
                                       ((cmdHeader.pitch[1U] * cmdHeader.height)/2U) ) ;


                                UTILS_assert( dataSize[i] == cmdHeader.dataSize );
                            }

                        }
                        else
                        {
                            numBuf = 1U;
                            dataAddr[0] = compVideoFrame->bufAddr[0U][0];
                            dataSize[0] =
                                cmdHeader.pitch[0U] * cmdHeader.height * compVideoFrame->numFrames;
                            UTILS_assert( dataSize[0] == cmdHeader.dataSize );
                        }
                        break;

                    default:
                        /* Can never reach here */
                        UTILS_assert((Bool)FALSE);
                        break;
                }


                status = NetworkTxLink_drvWritePayload(
                        pObj, pNetTxObj, numBuf, dataAddr, dataSize);
            }
        }
    }
    
    return status;
}
