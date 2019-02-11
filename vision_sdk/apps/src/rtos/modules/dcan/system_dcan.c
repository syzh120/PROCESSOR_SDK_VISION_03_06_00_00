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
  ******************************************************************************
 * \file system_dcan.c
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "include/link_api/grpxSrcLink.h"
#include "include/link_api/dcanCtrl_api.h"
#include "utils_dcan.h"

#define SYSTEM_DCAN_TX_PRD_MS            (10000)
#define SYSTEM_DCAN_TX_TSK_PRI           (13)
#define SYSTEM_DCAN_RX_TSK_PRI           (13)
// TDA2XX RVP uses interrupt ID 28 for VIP2
#if defined (BOARD_TYPE_TDA2XX_RVP)
#define SYSTEM_DCAN_INTR_ID              (24)
#else
#define SYSTEM_DCAN_INTR_ID              (28)
#endif
/** \brief DCAN input clock - 20MHz */
#define SYSTEM_DCAN_INPUT_CLK            (20000000U)
/** \brief DCAN output bit rate - 1MHz */
#define SYSTEM_DCAN_BIT_RATE             (1000000U)

/** \brief Used for enabling board-to-board DCAN */
#define ENABLE_B2B_DCAN_TEST             (1U)


static Void System_dcanRxMsgHandler(dcanMsg_t *rxMsg);
static Void System_dcanRxAckMsgHandler(dcanMsg_t *rxMsg);

dcanConfig_t System_dcanConfig;

static Void System_dcanInitCfgStruct(dcanConfig_t * dcanConfig)
{
    Int i;
    UInt8 msgData[] = {0xAA,0xEE,0xBB,0xFF,0xCC,0xDD,0x55,0xAA};

#if ENABLE_B2B_DCAN_TEST
    dcanConfig->enableLoopback     = FALSE;
#else
    dcanConfig->enableLoopback     = TRUE;
#endif
    dcanConfig->enablePeriodicTx   = TRUE;
    dcanConfig->rxMsgId            = 0xC1;
    dcanConfig->txMsgId            = 0xC2;
    dcanConfig->enableSendRxAck    = TRUE;
    dcanConfig->enableReceiveRxAck = TRUE;
    dcanConfig->txAckMsgId         = 0xC4;
    dcanConfig->rxAckMsgId         = 0xC5;
    dcanConfig->rxMsgCb            = System_dcanRxMsgHandler;
    dcanConfig->rxAckMsgCb         = System_dcanRxAckMsgHandler;
    dcanConfig->txMsgPeriod_ms     = SYSTEM_DCAN_TX_PRD_MS;
    dcanConfig->dcanCntrlIntrId    = SYSTEM_DCAN_INTR_ID;
    dcanConfig->dcanTxTskPri       = SYSTEM_DCAN_TX_TSK_PRI;
    dcanConfig->dcanRxTskPri       = SYSTEM_DCAN_RX_TSK_PRI;
    dcanConfig->dcanInputClk_hz    = SYSTEM_DCAN_INPUT_CLK;
    dcanConfig->dcanBaudRate_hz    = SYSTEM_DCAN_BIT_RATE;
    dcanConfig->enableTxMsgCycle   = TRUE;
    dcanConfig->dcanTxPrdMsg.dataLength = UTILS_ARRAYSIZE(msgData);
    for ( i = 0 ; i < UTILS_ARRAYSIZE(msgData); i++)
    {
        dcanConfig->dcanTxPrdMsg.msgData[i] = msgData[i];
    }
}

static Void System_dcanRxMsgHandler(dcanMsg_t *rxMsg)
{

#if ENABLE_B2B_DCAN_TEST
     GrpxSrcLink_StringRunTimePrintParams printPrms;
#endif

    if (rxMsg->appMsgPrms.dataLength)
    {
#if ENABLE_B2B_DCAN_TEST
         UTILS_COMPILETIME_ASSERT(UTILS_ARRAYSIZE(printPrms.stringInfo.string) >
                               0);
#endif
        Vps_printf("DCAN MSG Received:Id[0x%X] , Length : [%d], Data [0 .. 7]"
                   "0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X",
                    rxMsg->msgId,rxMsg->appMsgPrms.dataLength,
                    rxMsg->appMsgPrms.msgData[0],
                    rxMsg->appMsgPrms.msgData[1],
                    rxMsg->appMsgPrms.msgData[2],
                    rxMsg->appMsgPrms.msgData[3],
                    rxMsg->appMsgPrms.msgData[4],
                    rxMsg->appMsgPrms.msgData[5],
                    rxMsg->appMsgPrms.msgData[6],
                    rxMsg->appMsgPrms.msgData[7]);
#if ENABLE_B2B_DCAN_TEST
        snprintf(printPrms.stringInfo.string,
                 sizeof(printPrms.stringInfo.string) - 1,
                 "DCAN MSG ID:[0x%X]\n"
                 "DCAN MSG:0x%2X, 0x%2X, 0x%2X, 0x%2X, 0x%2X, 0x%2X, 0x%2X, 0x%2X",
                 rxMsg->msgId,
                 rxMsg->appMsgPrms.msgData[0],
                 rxMsg->appMsgPrms.msgData[1],
                 rxMsg->appMsgPrms.msgData[2],
                 rxMsg->appMsgPrms.msgData[3],
                 rxMsg->appMsgPrms.msgData[4],
                 rxMsg->appMsgPrms.msgData[5],
                 rxMsg->appMsgPrms.msgData[6],
                 rxMsg->appMsgPrms.msgData[7]);
        printPrms.stringInfo.string[sizeof(printPrms.stringInfo.string) - 1] = 0;
        printPrms.duration_ms = SYSTEM_DCAN_CTRL_DISPLAY_DURATION_MS;
        printPrms.stringInfo.fontType = SYSTEM_DCAN_CTRL_DISPLAY_FONTID;
        printPrms.stringInfo.startX  = SYSTEM_DCAN_CTRL_DISPLAY_STARTX;
        printPrms.stringInfo.startY  = SYSTEM_DCAN_CTRL_DISPLAY_STARTY;
        System_linkControl(IPU1_0_LINK(SYSTEM_LINK_ID_GRPX_SRC_0),
                           GRPX_SRC_LINK_CMD_PRINT_STRING,
                           &printPrms,
                           sizeof(printPrms),
                           TRUE);
#endif
    }
}


static Void System_dcanRxAckMsgHandler(dcanMsg_t *rxMsg)
{
    Vps_printf("DCAN TX ACk MsgId:%d,Length:%d,Payload[0]:0x%2x",
               rxMsg->msgId,
               rxMsg->appMsgPrms.dataLength,
               rxMsg->appMsgPrms.msgData[0]);
}


Void System_dcanInit()
{
    System_dcanInitCfgStruct(&System_dcanConfig);
    Utils_dcanInit(&System_dcanConfig);
}

Void System_dcanDeInit()
{
    Utils_dcanDeInit();
}



