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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <system_cfg.h>
#include <include/link_api/system.h>
#include <src/rtos/utils_common/include/network_api.h>
#include <src/rtos/utils_common/include/network_tfdtp_api.h>

typedef struct {
    UInt32 initFlag;
    /**< Bool to specify TFDTP stack open done or not */
    UInt32 deviceIpAddr;
    /**< Interface IP address obtained through NDK IP address hook function */
}Chains_tfdtpStatus;

Chains_tfdtpStatus gTfdtpObj = {0U, 0U};

int32_t Network_tfdtpTxDoneCb(tfdtp_tx_buf_handle_t appTxBuffh, void *cbdata, UInt32 channelNum);
int32_t Network_tfdtpRxDoneCb(tfdtp_rx_buf_handle_t appRxBuffh, void *cbdata, UInt32 channelNum);
void Network_tfdtpPrintFxn(const char *str);
void Network_ndkIPAddrHookFxn(IPN IPAddr, uint IfIdx, uint fAdd);

void Network_tfdtpPrintFxn(const char *str)
{
    Vps_printf(str);
}

/* Get IP Address NDK hook function.
 * This function is called from NDK every time IP address changes */
void Network_ndkIPAddrHookFxn(IPN IPAddr, uint IfIdx, uint fAdd)
{
    /* We are doing network to host conversion as TFDTP driver will also does
     * same. So effectively we negating that it here */
    gTfdtpObj.deviceIpAddr = (UInt32)(ntohl((UInt32)IPAddr));
}

int32_t Network_tfdtpTxDoneCb(tfdtp_tx_buf_handle_t appTxBuffh, void *cbdata, UInt32 channelNum)
{
    BspOsal_semPost((BspOsal_SemHandle) cbdata);
    return 0;
}

int32_t Network_tfdtpRxDoneCb(tfdtp_rx_buf_handle_t appRxBuffh, void *cbdata, UInt32 channelNum)
{
    BspOsal_semPost((BspOsal_SemHandle) cbdata);
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief   TFDTP Open function.
 *
 *          Init Function to reset TFDTP Parameters & open TFDTP stack handle
 *          This function should be called from the here as it needs Device IP
 *          address.
 *
 * \return tfdtp_handle_t returns tfdtp handle
 *
 *******************************************************************************
*/
tfdtp_handle_t Network_tfdtpOpen(void)
{
    tfdtp_handle_t         tfdtpHandle = NULL;

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    TFDTP_OpenPrm_t tfdtpOpenPrm;
    Int32 timeoutInMsec = 100;

    if (0U == gTfdtpObj.initFlag)
    {
        while ((gTfdtpObj.deviceIpAddr == 0U) && (timeoutInMsec > 0))
        {
            /* Wait for IP address */
            Task_sleep(10U);
            timeoutInMsec -= 10;
        }

        tfdtpOpenPrm.rxUdpPort     = NETWORK_TFDTP_RXFILTER_UDP_PORT;
        tfdtpOpenPrm.myIpAddr      = gTfdtpObj.deviceIpAddr;
        tfdtpOpenPrm.printFxnCb    = &Network_tfdtpPrintFxn;
        tfdtpHandle  = TFDTP_open(&tfdtpOpenPrm);
        if (NULL != tfdtpHandle)
        {
            Vps_printf(" NETWORK: TFDTP Stack Opened!!!\n");
            gTfdtpObj.initFlag = 1U;
        }
        else
        {
            Vps_printf(" NETWORK: Unable to open TFDTP!!!\n");
        }
    }
    else
    {
        gTfdtpObj.initFlag++;
        tfdtpHandle  = TFDTP_open(NULL);
    }
#endif
#endif

    return tfdtpHandle;
}

/**
 *******************************************************************************
 *
 * \brief   TFDTP Close function.
 *
 *          Deinit Function to reset TFDTP Parameters & close TFDTP stack handle
 *          This function will be called from the NDK close hook function.
 *
 *******************************************************************************
*/
void Network_tfdtpClose(tfdtp_handle_t hTfdtph)
{
#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    if (0U != gTfdtpObj.initFlag)
    {
        TFDTP_close(hTfdtph);
        gTfdtpObj.initFlag--;
        Vps_printf(" NETWORK: TFDTP Stack Closed!!!\n");
    }
    else
    {
        Vps_printf(" NETWORK: Closing upopened TFDTP stack!!!\n");
    }

#endif
#endif

}

void Network_initTfdtp(Network_SockObj *pObj)
{

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    pObj->hTfdtp = Network_tfdtpOpen();
    UTILS_assert(pObj->hTfdtp != NULL);

    pObj->tfdtpRxChObj.rxFrameDone = BspOsal_semCreate((Int32)0, (Bool)FALSE);
    UTILS_assert(pObj->tfdtpRxChObj.rxFrameDone != NULL);

    pObj->tfdtpTxChObj.txFrameDone = BspOsal_semCreate((Int32)0, (Bool)TRUE);
    UTILS_assert(pObj->tfdtpTxChObj.txFrameDone != NULL);

#endif
#endif
    return;
}

void Network_deInitTfdtp(Network_SockObj *pObj)
{

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    Network_tfdtpClose(pObj->hTfdtp);

    pObj->hTfdtp = NULL;

    BspOsal_semPost(pObj->tfdtpRxChObj.rxFrameDone);
    BspOsal_semPost(pObj->tfdtpTxChObj.txFrameDone);

    BspOsal_semDelete(&pObj->tfdtpRxChObj.rxFrameDone);
    BspOsal_semDelete(&pObj->tfdtpTxChObj.txFrameDone);

#endif
#endif
    return;
}

void Network_getTfdtpChParams(Network_SockObj *pObj, Tfdtp_channelType chType)
{
#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    NetworkTfdtp_channelParams hostParams;
    UInt32 size = sizeof (NetworkTfdtp_channelParams);
    Int32 status = 0;

    /* Host will send Host IP & MAC address and Channel ID via TCP. */
    status = Network_read(pObj, (UInt8 *) &hostParams, &size);

    if (0 == status)
    {


        if ( TFDTP_CHANNEL_MODE_TX == chType )
        {
            Vps_printf(" NETWORK: TFDTP Tx HOST IP Address = 0x%x", hostParams.IPAddress);

            Network_tfdtpTxChObj *pTfdtpTxChObj = &pObj->tfdtpTxChObj;

            pTfdtpTxChObj->tfdtpTxChOpenPrms.channelId  = hostParams.channelId;
            pTfdtpTxChObj->tfdtpTxChOpenPrms.hostIpAddr = hostParams.IPAddress;
            memcpy( pTfdtpTxChObj->tfdtpTxChOpenPrms.hostMacAddr, hostParams.MACAddr,
                                sizeof(pTfdtpTxChObj->tfdtpTxChOpenPrms.hostMacAddr) );

        }
        else
        {
            Vps_printf(" NETWORK: TFDTP Rx HOST IP Address = 0x%x", hostParams.IPAddress);
            pObj->tfdtpRxChObj.tfdtpRxChOpenPrms.channelId  = hostParams.channelId;
        }
        pObj->retryCount = hostParams.retryCount;
    }
    else
    {
        Vps_printf(" NETWORK: TFDTP Channel Parameter Read Failed !!!\n");
    }
#endif
#endif
}

Int32 Network_submitTfdtpRxBufs(tfdtp_rx_channel_handle_t hTfdtpRxCh,
                                tfdtp_rx_buf_details_t bufArrayDesc)
{
    Int32 status = 0;

#if defined(NSP_TFDTP_INCLUDE)
#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    UInt32 bufIdx;

    if (bufArrayDesc->bufCount > TFDTP_MAX_APP_BUF_CNT)
    {
        bufArrayDesc->bufCount = TFDTP_MAX_APP_BUF_CNT;
    }

    for (bufIdx = 0U; bufIdx < bufArrayDesc->bufCount; bufIdx++)
    {

        bufArrayDesc->appBufArray[bufIdx].bufState = BUFF_EMPTY;
    }

    /* Submit buffers to TFDTP channels */
    status = TFDTP_submitRxBuf(hTfdtpRxCh, bufArrayDesc);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

#endif
#endif

    return status;
}

void Network_initTfdtpChannel(Network_SockObj *pObj, Tfdtp_channelType chType)
{
#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    if ( TFDTP_CHANNEL_MODE_TX == chType )
    {
        Network_tfdtpTxChObj *pTfdtpTxChObj = &pObj->tfdtpTxChObj;

        if ( (0U != pTfdtpTxChObj->tfdtpTxChOpenPrms.hostIpAddr) ||
             (0U != pTfdtpTxChObj->tfdtpTxChOpenPrms.hostUdpPort) )
        {

            /* The rest of the fields will be set as the followings. */
            pTfdtpTxChObj->tfdtpTxChOpenPrms.hostUdpPort = NETWORK_TFDTP_HOST_UDP_PORT;

            pTfdtpTxChObj->tfdtpTxChOpenPrms.tx_cb_fxn = &Network_tfdtpTxDoneCb;
            pTfdtpTxChObj->tfdtpTxChOpenPrms.tx_cb_data = (void *) pTfdtpTxChObj->txFrameDone;

            /* Open TFDTP channel */
            pTfdtpTxChObj->hTfdtpTxCh = TFDTP_openTxChannel(pObj->hTfdtp,
                                                            &pTfdtpTxChObj->tfdtpTxChOpenPrms);
            if (pTfdtpTxChObj->hTfdtpTxCh == NULL)
            {
                Vps_printf(" NETWORK: Failed to open TFDTP Tx channel !!!\n");
                UTILS_assert(FALSE);
            }
            Vps_printf(" NETWORK: TFDTP Tx channel opened !!!\n");
        }
        else
        {
            Vps_printf(" NETWORK: TFDTP Channel paramters not correct !!!\n");
            UTILS_assert(FALSE);
        }
    }
    else
    {
        Network_tfdtpRxChObj *pTfdtpRxChObj =  &pObj->tfdtpRxChObj;
        /* The rest of the fields will be set as the followings. */
        pTfdtpRxChObj->tfdtpRxChOpenPrms.rcv_cb_fxn = &Network_tfdtpRxDoneCb;
        pTfdtpRxChObj->tfdtpRxChOpenPrms.rcv_cb_data = (void *) pTfdtpRxChObj->rxFrameDone;

        /* Open TFDTP channel */
        pTfdtpRxChObj->hTfdtpRxCh = TFDTP_openRxChannel(pObj->hTfdtp,
                                                        &pTfdtpRxChObj->tfdtpRxChOpenPrms);
        if (pTfdtpRxChObj->hTfdtpRxCh == NULL)
        {
            Vps_printf(" NETWORK: Failed to open TFDTP Rx channel !!!\n");
            UTILS_assert(FALSE);
        }
        Vps_printf(" NETWORK: TFDTP Rx channel opened !!!\n");
    }
#endif
#endif

}

void Network_deInitTfdtpChannel(Network_SockObj *pObj, Tfdtp_channelType chType)
{
#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    if ( TFDTP_CHANNEL_MODE_RX == chType )
    {
        if(NULL != pObj->tfdtpRxChObj.hTfdtpRxCh)
        {
            TFDTP_closeRxChannel(pObj->tfdtpRxChObj.hTfdtpRxCh);
            pObj->tfdtpRxChObj.hTfdtpRxCh = NULL;
        }
        else
        {
            Vps_printf(" NETWORK: Closing unopened TFDTP channel!!!\n");
        }
    }
    else
    {
        if(NULL != pObj->tfdtpTxChObj.hTfdtpTxCh)
        {
            TFDTP_closeTxChannel(pObj->tfdtpTxChObj.hTfdtpTxCh);
            pObj->tfdtpTxChObj.hTfdtpTxCh = NULL;
        }
        else
        {
            Vps_printf(" NETWORK: Closing unopened TFDTP channel!!!\n");
        }
    }

#endif
#endif
}

void Network_startTfdtp(Network_SockObj *pObj)
{
#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    Int32 status;

    status = TFDTP_start(pObj->hTfdtp);
    if (0 != status)
    {
        Vps_printf(" NETWORK: Failed to start TFDTP transfer!!!\n");
        UTILS_assert(FALSE);
    }

    Vps_printf(" NETWORK: TFDTP started !!!\n");
#endif
#endif

}

Int32 Network_tfdtpRead(Network_SockObj *pObj, UInt8 *dataBuf, const UInt32 *dataSize)
{
    Int32 status = 0;

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    tfdtp_rx_buf_details_t pBufArray = &pObj->tfdtpRxChObj.bufArrayDesc;
    Bool ret;

    pBufArray->appBufArray[0].bufPtr = dataBuf;
    pBufArray->bufCount = 1;
    pBufArray->bufSize = *dataSize;
    pBufArray->channelNum = 0;

    TFDTP_submitRxBuf(pObj->tfdtpRxChObj.hTfdtpRxCh, pBufArray);

    /* Wait for Frame RX to complete. */
    ret = (Int32) BspOsal_semWait(pObj->tfdtpRxChObj.rxFrameDone, TFDTP_RX_TIMEOUT);

    if (FALSE == ret)
    {
        /* RX timeout */
        status = -1;
    }
#endif
#endif

    return status;
}

Int32 Network_tfdtpWrite(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize)
{
    Int32 status = 0;

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    tfdtp_tx_buf_t appTxBuf;
    tfdtp_tx_buf_t *pTxBuf = &appTxBuf;

    appTxBuf.hTfdtpTxCh = pObj->tfdtpTxChObj.hTfdtpTxCh;
    appTxBuf.needsFlushing  = false;
    appTxBuf.pData = dataBuf;
    appTxBuf.size = dataSize;

    TFDTP_submitTxBuf(pObj->hTfdtp, &pTxBuf, 1U);

    /* Wait for Frame TX to complete. */
    BspOsal_semWait(pObj->tfdtpTxChObj.txFrameDone, BSP_OSAL_WAIT_FOREVER);
#endif
#endif

    return status;
}

UInt32 Network_tfdtpWaitAck(Network_SockObj *pObj)
{
    UInt32 cmd = 0U;

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    UInt32 size = sizeof (UInt32);
    Int32 status = 0;

    /* Host will send status via TCP. */
    status = Network_read(pObj, (UInt8 *) &cmd, &size);

    if (0U != status)
    {
        Vps_printf(" NETWORK: TFDTP Transmit Ack Read Failed !!!\n");
        cmd = TFDTP_TRANSMIT_INVALID;
    }

#endif
#endif

    return cmd;
}

Int32 Network_tfdtpSendAck(Network_SockObj *pObj, UInt32 ack)
{
    Int32 status = 0;

#if defined(NSP_TFDTP_INCLUDE)

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    /* Send ACK to host via TCP. */
    status = Network_write(pObj, (UInt8 *) &ack, sizeof(UInt32));

    if (0U != status)
    {
        Vps_printf(" NETWORK: TFDTP Transmit Ack Send Failed !!!\n");
    }

#endif
#endif

    return status;
}
