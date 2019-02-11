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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "network_cons_priv.h"
#include <src/rtos/utils_common/include/utils_tsk.h>

#define NETWORK_CONS_TX_TSK_STACK_SIZE  (16*KB)
#define NETWORK_CONS_TX_TSK_PRI         (4)

#define NETWORK_CONS_RX_TSK_STACK_SIZE  (16*KB)
#define NETWORK_CONS_RX_TSK_PRI         (4)

/**
 *******************************************************************************
 * \brief  Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gNetworkConsRx_tskStack, 32)
#pragma DATA_SECTION(gNetworkConsRx_tskStack, ".bss:taskStackSection")
UInt8 gNetworkConsRx_tskStack[NETWORK_CONS_RX_TSK_STACK_SIZE];

#pragma DATA_ALIGN(gNetworkConsTx_tskStack, 32)
#pragma DATA_SECTION(gNetworkConsTx_tskStack, ".bss:taskStackSection")
UInt8 gNetworkConsTx_tskStack[NETWORK_CONS_TX_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief stores all module related information
 *******************************************************************************
 */
NetworkCons_Obj gNetworkCons_obj;

Void NetworkConsTx_tskMain(UArg arg0, UArg arg1)
{
    NetworkCons_Obj *pObj = (NetworkCons_Obj*)arg0;
    Int32 status;
    UInt32 dataLen;

    Task_sleep(1000);

    Vps_printf(
        " NETWORK_CONS_TX: Starting TX (port=%d) !!!\n", pObj->txPort
        );

    Network_sessionOpen(NULL);

    status = Network_open(&pObj->sockObjTx, pObj->txPort);
    UTILS_assert(status==0);

    Vps_printf(
        " NETWORK_CONS_TX: Starting TX ... DONE (port=%d) !!!\n", pObj->txPort
        );

    pObj->txState = NETWORK_CONS_LISTEN;

    while(!gNetworkCons_obj.tskExitTx)
    {
        if(pObj->txState == NETWORK_CONS_LISTEN)
        {
            Bool isConnected;

            isConnected = Network_waitConnect(&pObj->sockObjTx, 1000);
            if(isConnected==TRUE)
            {
                pObj->txState = NETWORK_CONS_CONNECTED;
            }
        }

        if(pObj->txState == NETWORK_CONS_CONNECTED)
        {
            dataLen = sizeof(pObj->txData);

            NetworkCons_txReadString(pObj->txData, &dataLen);


            if( dataLen > 0)
            {
                status = Network_write(&pObj->sockObjTx,
                               (UInt8*)pObj->txData,
                               dataLen);

                if(status!=0)
                {
                    Network_close(&pObj->sockObjTx, FALSE);
                    pObj->txState = NETWORK_CONS_LISTEN;
                }
            }
            else
            {
                Task_sleep(1);
            }
        }
    }

    Vps_printf(
        " NETWORK_CONS_TX: Closing TX (port=%d) !!!\n", pObj->txPort
        );

    /* close socket */
    Network_close(&pObj->sockObjTx, TRUE);
    pObj->txState = NETWORK_CONS_CLOSED;

    Network_sessionClose(NULL);

    Vps_printf(
        " NETWORK_CONS_TX: Closing TX ... DONE (port=%d) !!!\n", pObj->txPort
        );
}

Void NetworkConsRx_tskMain(UArg arg0, UArg arg1)
{
    NetworkCons_Obj *pObj = (NetworkCons_Obj*)arg0;
    Int32 status;
    UInt32 dataLen;
    UInt8 rxData;

    Task_sleep(1000);

    Vps_printf(
        " NETWORK_CONS_RX: Starting RX (port=%d) !!!\n", pObj->rxPort
        );

    Network_sessionOpen(NULL);

    status = Network_open(&pObj->sockObjRx, pObj->rxPort);
    UTILS_assert(status==0);

    Vps_printf(
        " NETWORK_CONS_RX: Starting RX ... DONE (port=%d) !!!\n", pObj->rxPort
        );

    pObj->rxState = NETWORK_CONS_LISTEN;

    while(!gNetworkCons_obj.tskExitRx)
    {
        if(pObj->rxState == NETWORK_CONS_LISTEN)
        {
            Bool isConnected;

            isConnected = Network_waitConnect(&pObj->sockObjRx, 1000);
            if(isConnected==TRUE)
            {
                pObj->rxState = NETWORK_CONS_CONNECTED;
            }
        }

        if(pObj->rxState == NETWORK_CONS_CONNECTED)
        {
            dataLen = 1;

            status = Network_read(&pObj->sockObjRx,
                           &rxData,
                           &dataLen);

            if(status!=0)
            {
                Network_close(&pObj->sockObjRx, FALSE);
                pObj->rxState = NETWORK_CONS_LISTEN;
            }
            else
            {
                if(dataLen > 0)
                {
                    if(rxData != '\r' && rxData != '\t' && rxData != '\b' && rxData != 0)
                    {
                        NetworkCons_rxWriteChar(rxData);
                    }
                }
            }
        }
    }

    Vps_printf(
        " NETWORK_CONS_RX: Closing RX (port=%d) !!!\n", pObj->rxPort
        );

    /* close socket */
    Network_close(&pObj->sockObjRx, TRUE);
    pObj->rxState = NETWORK_CONS_CLOSED;

    Network_sessionClose(NULL);

    Vps_printf(
        " NETWORK_CONS_RX: Closing RX ... DONE (port=%d) !!!\n", pObj->rxPort
        );
}

Int32 NetworkCons_init()
{
    memset(&gNetworkCons_obj, 0, sizeof(gNetworkCons_obj));
    /* Done earlier to make sure the shared memory is ready to
     * recieve.
     */
    //NetworkCons_shmCreate();

    gNetworkCons_obj.txPort = NETWORK_CONS_TX_PORT;
    gNetworkCons_obj.rxPort = NETWORK_CONS_RX_PORT;

    /*
     * Create task
     */
    gNetworkCons_obj.taskTx = BspOsal_taskCreate(
                                (BspOsal_TaskFuncPtr)NetworkConsTx_tskMain,
                                "Network Console Tx Task",
                                NETWORK_CONS_TX_TSK_PRI,
                                gNetworkConsTx_tskStack,
                                sizeof(gNetworkConsTx_tskStack),
                                &gNetworkCons_obj,
                                UTILS_TSK_AFFINITY_CORE0
                            );
    UTILS_assert(gNetworkCons_obj.taskTx != NULL);

    /*
     * Create task
     */
    gNetworkCons_obj.taskRx = BspOsal_taskCreate(
                                (BspOsal_TaskFuncPtr)NetworkConsRx_tskMain,
                                "Network Console Rx Task",
                                NETWORK_CONS_RX_TSK_PRI,
                                gNetworkConsRx_tskStack,
                                sizeof(gNetworkConsRx_tskStack),
                                &gNetworkCons_obj,
                                UTILS_TSK_AFFINITY_CORE0
                            );
    UTILS_assert(gNetworkCons_obj.taskRx != NULL);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 NetworkCons_deInit()
{
    gNetworkCons_obj.tskExitTx = TRUE;
    gNetworkCons_obj.tskExitRx = TRUE;

    Task_sleep(1);

    BspOsal_taskDelete(&gNetworkCons_obj.taskTx);
    BspOsal_taskDelete(&gNetworkCons_obj.taskRx);

    NetworkCons_shmDelete();

    return SYSTEM_LINK_STATUS_SOK;
}

