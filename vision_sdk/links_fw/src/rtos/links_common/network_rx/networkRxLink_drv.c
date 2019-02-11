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
#include "networkRxLink_priv.h"

 /*****************************************************************************
  *  Function declarations
  *****************************************************************************
  */
Int32 NetworkRxLink_drvWaitConnect(NetworkRxLink_Obj *pObj,
                                       NetworkRxLink_NetworkRxObj *pNetRxObj);
Int32 NetworkRxLink_drvWriteHeader(NetworkRxLink_Obj *pObj,
                                       NetworkRxLink_NetworkRxObj *pNetRxObj,
                                       NetworkRx_CmdHeader *pHeader);
Int32 NetworkRxLink_drvReadHeader(NetworkRxLink_Obj *pObj,
                                      NetworkRxLink_NetworkRxObj *pNetRxObj,
                                      NetworkRx_CmdHeader *pHeader);
Int32 NetworkRxLink_drvReadPayload(NetworkRxLink_Obj *pObj,
                                       NetworkRxLink_NetworkRxObj *pNetRxObj,
                                       UInt32 numBuf,
                                       UInt8  *bufAddr[],
                                       UInt32 bufSize[]);

#define NETWORK_RX_SERVER_CLOSED        (0U)
#define NETWORK_RX_SERVER_LISTEN        (1U)
#define NETWORK_RX_SERVER_CONNECTED     (2U)

#define NETWORK_RX_SERVER_POLL_TIMEOUT  (10U)

Int32 NetworkRxLink_drvCreate(NetworkRxLink_Obj *pObj)
{
    NetworkRxLink_NetworkRxObj *pNetRxObj = &pObj->netRxObj;
    Int32 status;

    Network_sessionOpen(NULL);

    status = Network_open(&pNetRxObj->sockObj,
                          pObj->createArgs.networkServerPort);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    pNetRxObj->state = NETWORK_RX_SERVER_LISTEN;

    Vps_printf(" NETWORK_RX: NETWORK_RX: Server listening (port=%d) !!!\n",
        pObj->createArgs.networkServerPort);

    return status;
}

Int32 NetworkRxLink_drvDelete(NetworkRxLink_Obj *pObj)
{
    NetworkRxLink_NetworkRxObj *pNetRxObj = &pObj->netRxObj;
    Int32 status;

    status = Network_close(&pNetRxObj->sockObj, (Bool)TRUE);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    Network_sessionClose(NULL);

#if (defined(NSP_TFDTP_INCLUDE))
    /* Make sure TFDTP is not alredy closed by client disconnection  */
    if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
    {
        if(NULL != pNetRxObj->sockObj.hTfdtp)
        {
            /* Close TFDTP channel */
            Network_deInitTfdtpChannel(&pNetRxObj->sockObj, TFDTP_CHANNEL_MODE_RX);
            /* If TFDTP mode is enabled, close TFDTP stack */
            Network_deInitTfdtp(&pNetRxObj->sockObj);
        }
    }
#endif

    pNetRxObj->state = NETWORK_RX_SERVER_CLOSED;

    Vps_printf(" NETWORK_RX: NETWORK_RX: Server Closed (port=%d) !!!\n",
        pObj->createArgs.networkServerPort);

    return status;
}

Int32 NetworkRxLink_drvWaitConnect(NetworkRxLink_Obj *pObj,
                                       NetworkRxLink_NetworkRxObj *pNetRxObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 isConnected;

    if(pNetRxObj->state == NETWORK_RX_SERVER_LISTEN)
    {
        isConnected = Network_waitConnect(
                    &pNetRxObj->sockObj,
                    NETWORK_RX_SERVER_POLL_TIMEOUT);

        /* MISRA.UNREACH.GEN
         * MISRAC_2004 Rule_14.1
         * MISRAC_WAIVER:
         * Code is currently unreachable but as the implementation of the function
         * changes, it will not be unreachable.
         */
        if((Int32)TRUE == isConnected)
        {
            /* connected to client */
            pNetRxObj->state = NETWORK_RX_SERVER_CONNECTED;

#if (defined(NSP_TFDTP_INCLUDE))
            if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
            {
                /* If TFDTP mode is enabled, open TFDTP stack */
                Network_initTfdtp(&pNetRxObj->sockObj);
                /* Get channel open parameters from client & open TFDTP channel */
                Network_getTfdtpChParams(&pNetRxObj->sockObj, TFDTP_CHANNEL_MODE_RX);
                /* Open TFDTP channel */
                Network_initTfdtpChannel(&pNetRxObj->sockObj,TFDTP_CHANNEL_MODE_RX);
                /* Start TFDTP */
                Network_startTfdtp(&pNetRxObj->sockObj);
            }
#endif

            Vps_printf(" NETWORK_RX: NETWORK_RX: Connected to client (port=%d) !!!\n",
                pObj->createArgs.networkServerPort);
        }
        else
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    return status;
}

Int32 NetworkRxLink_drvWriteHeader(NetworkRxLink_Obj *pObj,
                                       NetworkRxLink_NetworkRxObj *pNetRxObj,
                                       NetworkRx_CmdHeader *pHeader)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pHeader->header = NETWORK_RX_HEADER;

    /* MISRA.CAST.PTR
     * MISRAC_2004 Rule_11.4
     * MISRAC_WAIVER:
     * This is a generic prototype which supports all dataTypes.
     * This typecasting is necessary.
     */
    /* write header to client, if write failed, then client
     * disconnected, so go back to listening
     */
    status = Network_write(&pNetRxObj->sockObj,
                           (UInt8*)pHeader,
                           sizeof(NetworkRx_CmdHeader));

    /* MISRA.UNREACH.GEN
     * MISRAC_2004 Rule_14.1
     * MISRAC_WAIVER:
     * Code is currently unreachable but as the implementation of the function
     * changes, it will not be unreachable.
     */
    if(status != SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf(" NETWORK_RX: NETWORK_RX: Disconnected from client "
                   "while writing header (port=%d)!!!\n",
                    pObj->createArgs.networkServerPort
                   );

        Network_close(&pNetRxObj->sockObj, (Bool)FALSE);

#if (defined(NSP_TFDTP_INCLUDE))
        /* Close TFDTP channel and deinit TFDTP stack, otherwise
         * after client reconnection TFDTP will not have free
         * channel and fail */
        if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
        {
            /* Close TFDTP channel */
            Network_deInitTfdtpChannel(&pNetRxObj->sockObj, TFDTP_CHANNEL_MODE_RX);
            /* Close TFDTP handle and stop TFDTP (No separate stop function ) */
            Network_deInitTfdtp(&pNetRxObj->sockObj);
        }
#endif
        pNetRxObj->state = NETWORK_RX_SERVER_LISTEN;
    }

    return status;
}

Int32 NetworkRxLink_drvReadHeader(NetworkRxLink_Obj *pObj,
                                      NetworkRxLink_NetworkRxObj *pNetRxObj,
                                      NetworkRx_CmdHeader *pHeader)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 dataSize;

    /* read reply */
    dataSize = sizeof(NetworkRx_CmdHeader);
    /* MISRA.CAST.PTR
     * MISRAC_2004 Rule_11.4
     * MISRAC_WAIVER:
     * This is a generic prototype which supports all dataTypes.
     * This typecasting is necessary.
     */
    status = Network_read(&pNetRxObj->sockObj,
                          (UInt8*)pHeader,
                          &dataSize);

    /* MISRA.UNREACH.GEN
     * MISRAC_2004 Rule_14.1
     * MISRAC_WAIVER:
     * Code is currently unreachable but as the implementation of the function
     * changes, it will not be unreachable.
     */
    if(status != SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf(" NETWORK_RX: NETWORK_RX: Disconnected from client "
                   "while reading header (port=%d)!!!\n",
                    pObj->createArgs.networkServerPort
                   );

        Network_close(&pNetRxObj->sockObj, (Bool)FALSE);

#if (defined(NSP_TFDTP_INCLUDE))
        /* Close TFDTP channel and deinit TFDTP stack, otherwise
         * after client reconnection TFDTP will not have free
         * channel and fail */
        if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
        {
            Network_deInitTfdtpChannel(&pNetRxObj->sockObj, TFDTP_CHANNEL_MODE_RX);
            Network_deInitTfdtp(&pNetRxObj->sockObj);
        }
#endif
        pNetRxObj->state = NETWORK_RX_SERVER_LISTEN;
    }
    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        if((pHeader->header != NETWORK_RX_HEADER) ||
           (pHeader->dataSize == 0))
        {
            /* invalid header or no data to read */
            status = SYSTEM_LINK_STATUS_EFAIL;
            Vps_printf(" NETWORK_RX: NETWORK_RX: Invalid header received"
                       " (port=%d)!!!\n",
                        pObj->createArgs.networkServerPort
                       );

        }
    }

    return status;
}

Int32 NetworkRxLink_drvReadPayload(NetworkRxLink_Obj *pObj,
                                       NetworkRxLink_NetworkRxObj *pNetRxObj,
                                       UInt32 numBuf,
                                       UInt8  *bufAddr[],
                                       UInt32 bufSize[])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;
#if (defined(NSP_TFDTP_INCLUDE))
    UInt32 ack = TFDTP_TRANSMIT_OK;
    Int32 retry = 0;
#endif

    for(i=0; i<numBuf; i++)
    {
        if(status==SYSTEM_LINK_STATUS_SOK)
        {
            if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
            {
                status = Network_read(&pNetRxObj->sockObj,
                            bufAddr[i],
                            &bufSize[i]
                            );

                /* MISRA.UNREACH.GEN
                * MISRAC_2004 Rule_14.1
                * MISRAC_WAIVER:
                * Code is currently unreachable but as the implementation of the
                * function changes, it will not be unreachable.
                */
                if(status != SYSTEM_LINK_STATUS_SOK)
                {
                    Vps_printf(" NETWORK_RX: NETWORK_RX: Disconnected from client "
                            "while reading payload (port=%d)!!!\n",
                                pObj->createArgs.networkServerPort
                            );
                    Network_close(&pNetRxObj->sockObj, (Bool)FALSE);
                    pNetRxObj->state = NETWORK_RX_SERVER_LISTEN;
                    break;
                }

                /* MISRA.CAST.PTR_TO_INT
                * MISRAC_2004 Rule_11.3
                * MISRAC_WAIVER:
                * This is used to ensure address alignment required by hardware.
                */
                Cache_wb((Ptr)SystemUtils_floor((UInt32)bufAddr[i], 128U),
                        SystemUtils_align(bufSize[i] + 128U, 128U),
                        Cache_Type_ALLD,
                        (Bool)TRUE);
            }
#if (defined(NSP_TFDTP_INCLUDE))
            else if (pObj->createArgs.dataRxMode ==
                            NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
            {
                if (pNetRxObj->sockObj.retryCount > 0U)
                {
                    retry = pNetRxObj->sockObj.retryCount;
                    do
                    {
                        status = Network_tfdtpRead(&pNetRxObj->sockObj,
                                    bufAddr[i],
                                    &bufSize[i]);
                        if (0 == status)
                        {
                            ack = TFDTP_TRANSMIT_OK;
                        }
                        else
                        {
                            ack = TFDTP_TRANSMIT_FAIL;
                            Vps_printf("NETWORK_RX: Retry Network_tfdtpRead()!!");
                        }
                        status = Network_tfdtpSendAck(&pNetRxObj->sockObj, ack);
                        if (status != 0)
                        {
                            break;
                        }
                        retry--;
                    }
                    while ((retry >= 0) && (ack != TFDTP_TRANSMIT_OK));
                }
                else
                {
                    status = Network_tfdtpRead(&pNetRxObj->sockObj,
                                bufAddr[i],
                                &bufSize[i]);
                }

                if ((0 == status) && (TFDTP_TRANSMIT_OK == ack))
                {
                    /* MISRA.CAST.PTR_TO_INT
                    * MISRAC_2004 Rule_11.3
                    * MISRAC_WAIVER:
                    * This is used to ensure address alignment required by hardware.
                    */
                    Cache_wb((Ptr)SystemUtils_floor((UInt32)bufAddr[i], 128U),
                            SystemUtils_align(bufSize[i] + 128U, 128U),
                            Cache_Type_ALLD,
                            (Bool)TRUE);
                }
                else
                {
                    Vps_printf("NETWORK_RX: Network_tfdtpRead() Failed!!");
                }
            }
#endif
            else
            {
                /* Will never come here */
            }

#if (defined(SYSTEM_DEBUG_NULLSRC_RT))
            Vps_printf(" NETWORK_RX: NETWORK_RX: BUF%d: %d bytes recevied (port=%d)!!!\n",
                i,
                bufSize[i],
                pObj->createArgs.networkServerPort
                );
#endif
        }
    }

    return status;
}

Int32 NetworkRxLink_drvFillData(NetworkRxLink_Obj * pObj,
                                    UInt32 channelId,
                                    const System_Buffer *pBuffer)
{
    NetworkRxLink_NetworkRxObj *pNetRxObj = &pObj->netRxObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_VideoDataFormat dataFormat;
    System_VideoFrameBuffer *videoFrame;
    System_BitstreamBuffer *bitstreamBuf;
    System_MetaDataBuffer *metaBuf;
    UInt16 i;

    status = NetworkRxLink_drvWaitConnect(pObj, pNetRxObj);

    if(pNetRxObj->state == NETWORK_RX_SERVER_CONNECTED)
    {
        NetworkRx_CmdHeader cmdHeader;
        UInt32 bufSize;

        memset(&cmdHeader, 0, sizeof(NetworkRx_CmdHeader));

        cmdHeader.chNum = channelId;

        switch(pBuffer->bufType)
        {
            case SYSTEM_BUFFER_TYPE_BITSTREAM:
                bitstreamBuf = (System_BitstreamBuffer *)pBuffer->payload;

                /* right now only MJPEG RX is supported */
                cmdHeader.payloadType = NETWORK_RX_TYPE_BITSTREAM_MJPEG;
                cmdHeader.dataSize    = bitstreamBuf->bufSize; /* max buffer */
                break;

            case SYSTEM_BUFFER_TYPE_METADATA:
                metaBuf = (System_MetaDataBuffer *)pBuffer->payload;

                /* right now only MJPEG TX is supported */
                cmdHeader.numBuf = metaBuf->numMetaDataPlanes;
                cmdHeader.payloadType = NETWORK_RX_TYPE_META_DATA;
                cmdHeader.dataSize = 0; /* max buffer size */

                for(i=0; i<metaBuf->numMetaDataPlanes; i++)
                {
                    cmdHeader.dataSize += metaBuf->metaFillLength[i];
                }
                break;

            case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:
                videoFrame = (System_VideoFrameBuffer *)pBuffer->payload;
                dataFormat =
                    (System_VideoDataFormat)
                        System_Link_Ch_Info_Get_Flag_Data_Format(
                            videoFrame->chInfo.flags);

                if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                {
                    bufSize =
                        (videoFrame->chInfo.pitch[0] *
                         videoFrame->chInfo.height) +
                        ((videoFrame->chInfo.pitch[1] *
                          videoFrame->chInfo.height) / 2U);

                    cmdHeader.payloadType = NETWORK_RX_TYPE_VIDEO_FRAME_YUV420SP_UV;
                }
                else if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
                {
                    bufSize =
                        videoFrame->chInfo.pitch[0] * videoFrame->chInfo.height;
                    cmdHeader.payloadType =
                        NETWORK_RX_TYPE_VIDEO_FRAME_YUV422I_YUYV;
                }
                else
                {
                    status = SYSTEM_LINK_STATUS_EFAIL;
                }

                if(status==SYSTEM_LINK_STATUS_SOK)
                {
                    cmdHeader.dataSize  = bufSize; /* max buffer size */
                    cmdHeader.width     = videoFrame->chInfo.width;
                    cmdHeader.height    = videoFrame->chInfo.height;
                    cmdHeader.pitch[0U] = videoFrame->chInfo.pitch[0U];
                    cmdHeader.pitch[1U] = videoFrame->chInfo.pitch[1U];
                }

                break;

            default:
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
        }

        if(status == SYSTEM_LINK_STATUS_SOK)
        {
            status =
                NetworkRxLink_drvWriteHeader(pObj, pNetRxObj, &cmdHeader);
        }

        /* We dont receive header from client in TFDTP mode */
        if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
        {
            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                status =
                    NetworkRxLink_drvReadHeader(pObj, pNetRxObj, &cmdHeader);
            }
        }

        if(status==SYSTEM_LINK_STATUS_SOK)
        {
            UInt32 numBuf = 0U;
            UInt8 *dataAddr[2U];
            UInt32 dataSize[2U];

            /* read payload data */
            switch(pBuffer->bufType)
            {
                case SYSTEM_BUFFER_TYPE_BITSTREAM:
                    numBuf = 1U;
                    dataAddr[0U] = bitstreamBuf->bufAddr;
                    dataSize[0U] = cmdHeader.dataSize;
                    bitstreamBuf->fillLength = cmdHeader.dataSize;
                    break;


                case SYSTEM_BUFFER_TYPE_METADATA:
                    numBuf = metaBuf->numMetaDataPlanes;

                    for(i=0; i<metaBuf->numMetaDataPlanes; i++)
                    {
                        dataAddr[i] = metaBuf->bufAddr[i];
                        dataSize[i] = metaBuf->metaFillLength[i];
                    }
                    break;

                case SYSTEM_BUFFER_TYPE_VIDEO_FRAME:

                    if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
                    {
                        numBuf = 1U;
                        dataAddr[0U] = videoFrame->bufAddr[0U];
                        dataSize[0U] =
                            cmdHeader.pitch[0U] * cmdHeader.height;
                        UTILS_assert(dataSize[0U] == cmdHeader.dataSize);
                    }
                    else
                    if(dataFormat == SYSTEM_DF_YUV420SP_UV)
                    {
                        /* We dont receive header from client in TFDTP mode */
                        if (pObj->createArgs.dataRxMode == NETWORK_RX_LINK_DATA_RX_MODE_TCPIP)
                        {

                            numBuf = 2U;
                            dataAddr[0U] = videoFrame->bufAddr[0];
                            dataAddr[1U] = videoFrame->bufAddr[1];
                            dataSize[0U] = cmdHeader.pitch[0U]*cmdHeader.height;
                            dataSize[1U] =
                                (cmdHeader.pitch[1U]*cmdHeader.height) / 2U;

                            UTILS_assert(
                                (dataSize[0]+dataSize[1]) == cmdHeader.dataSize);
                        }
#if (defined(NSP_TFDTP_INCLUDE))
                        else if (pObj->createArgs.dataRxMode ==
                                                    NETWORK_RX_LINK_DATA_RX_MODE_TFDTP)
                        {
                            numBuf = 1U;
                            dataAddr[0U] = videoFrame->bufAddr[0U];
                            dataSize[0U] = bufSize;
                            UTILS_assert(dataSize[0U] == cmdHeader.dataSize);
                        }
#endif
                        else
                        {
                            /* Will never come here */
                        }
                    }
                    else
                    {
                        /* Can never reach here */
                        UTILS_assert((Bool)FALSE);
                    }
                    break;

                default:
                    /* Can never reach here */
                    UTILS_assert((Bool)FALSE);
                    break;
            }

            status = NetworkRxLink_drvReadPayload(
                                pObj, pNetRxObj, numBuf, dataAddr, dataSize);

        }
    }

    return status;
}
