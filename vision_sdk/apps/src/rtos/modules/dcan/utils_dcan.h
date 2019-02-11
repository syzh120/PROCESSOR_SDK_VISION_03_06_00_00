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
 *
 * \defgroup UTILS_DCAN_API Utility functions for DCAN
 *
 * \brief This module define APIs for DCAn
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_dcan.h
 *
 * \brief Utility functions for DCAN
 *
 *******************************************************************************
 */

#ifndef _UTILS_DCAN_H_
#define _UTILS_DCAN_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/link_api/system.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Text.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Cache.h>


#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_remote_log_if.h>

#include <include/link_api/system_inter_link_api.h>
#include <include/link_api/systemLink_common.h>
#include <ti/csl/csl_dcan.h>


typedef struct dcanMsg_tag
{
    UInt32 msgId;
    dcanMsgParams_t  appMsgPrms;
} dcanMsg_t;

typedef Void (*dcanMsgCallback)(dcanMsg_t *msg);


typedef struct dcanConfig_tag
{
    UInt32 enableLoopback;  /*!< Enable DCAN internal loopback */
    UInt32 enablePeriodicTx;/*!< Enable DCAN Tx thread         */
    UInt32 enableSendRxAck; /*!< Enable sending of Ack on DCAN Rx processing */
    UInt32 enableReceiveRxAck; /*!< Enable recv of txAck */
    UInt32 txMsgId;         /*!< DCAN Tx Msg Id */
    UInt32 rxMsgId;         /*!< DCAN Rx Msg id */
    UInt32 txAckMsgId;      /*!< MsgId of Tx  Ack Msg */
    UInt32 rxAckMsgId;      /*!< MsgId of Rx  Ack Msg */
    UInt32 txMsgPeriod_ms;  /*!< Duration in ms when Tx msg needs to be xmitted*/
    UInt32 dcanCntrlIntrId; /*!< IRQ number to use for DCAN controller interrupt */
    UInt32 dcanRxTskPri;    /*!< Priority of the DCAN Rx thread */
    UInt32 dcanTxTskPri;    /*!< Priority of the DCAN Tx thread */
    UInt32 dcanBaudRate_hz; /*!< DCAN bus baud rate */
    UInt32 dcanInputClk_hz; /*!< DCAN input clock */
    UInt32 enableTxMsgCycle;/*!< Enable cycling of msg bytes in dcan tx msg */
    dcanMsgParams_t dcanTxPrdMsg;/*!< DCAN periodic Tx Msg */
    dcanMsgCallback rxMsgCb;/*!< Handler of DCAN Rx Msgs */
    dcanMsgCallback rxAckMsgCb;/*!< Handler of DCAN Rx Ack Msgs */
} dcanConfig_t;


Void Utils_dcanInit(dcanConfig_t *dcanCfg);
Void Utils_dcanDeInit(void);
void Utils_dcanWriteMsg(dcanMsg_t *msg);



#endif /* ifndef _UTILS_H_ */

/* @} */
