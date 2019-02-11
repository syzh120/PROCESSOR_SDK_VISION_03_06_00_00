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
 * \file mcal_ipc_lib.c
 *
 * \brief  This file has the implementation of IPC IN Link API
 *
 *         This file implements the software logic needed to exchange frames
 *         between processors
 *
 * \version 0.0 (Aug 2018) : [AKG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "mcal_rx_tx.h"

Cdd_IpcCfg gIpcInitCfg;
BspOsal_IntrHandle gIntrHandle;

 /*******************************************************************************
 *  Function Prototype's
 *******************************************************************************
 */
Void Cdd_IpcMbxIsrNewMsg(Cdd_IpcCoreId rCoreId);

/**
 *******************************************************************************
 *
 * \brief MCU Init
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void McalIpc_mcuInit(Void)
{
    static Mcu_IrqXbarConfigType      gIpcCddAppMcuIrqXbarConfig[] =
    {
        [0] =
        {
#ifdef IPC_LIB_INCLUDE
        .Mcu_IrqXbarIntrSource = MCU_IRQXBAR_INTR_SRC_MBX_7_USER_3,
        .Mcu_IrqXbarInst       = MCU_IRQXBAR_INST_IPU_IRQ_69
#else
        .Mcu_IrqXbarIntrSource = MCU_IRQXBAR_INTR_SRC_MBX_5_USER_3,
        .Mcu_IrqXbarInst       = MCU_IRQXBAR_INST_IPU_IRQ_73
#endif
        },
    };

    /* PRM is not done here, entity outside should have to do it */
    static Mcu_ConfigType             gIpcCddAppMcuConfig =
    {
        .Mcu_ResetMode           = MCU_PERFORM_RESET_MODE_COLD,
        .Mcu_ConfigRamSection    = (const Mcu_RamSectionConfigType *)NULL_PTR,
        .Mcu_NumberOfRamSectors  = 0U,
        .Mcu_PrcmConfig          = (const Mcu_PrcmConfigType *)NULL_PTR,
                                    /* PRCM Not being done */
        .Mcu_NumberOfPrcmModules = 0U,
        .Mcu_IrqXbarConfig       = &gIpcCddAppMcuIrqXbarConfig[0],
        .Mcu_NumberOfIrqSources  = 1,
        .Mcu_ClockConfig         = (const Mcu_ClockConfigType *) NULL_PTR,
        .Mcu_NumberOfClockConfig = 0
    };

    Mcu_Init(&gIpcCddAppMcuConfig);
}

/**
 *******************************************************************************
 *
 * \brief MCU Init
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void McalIpc_mcuDeInit(Void)
{
    Mcu_DeInit();
}
/**
 *******************************************************************************
 *
 * \brief Registered ISR
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void IpcIsr(Void)
{
    Cdd_IpcMbxIsrNewMsg(IPC_CORE_1);
}

/**
 *******************************************************************************
 *
 * \brief Register Interrupt Handle
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void McalIpc_registerInterruptHandle(Void)
{
    uint32 intNum;
#ifdef IPC_LIB_INCLUDE
    intNum = 69;
#else
    intNum = 73;
#endif
    gIntrHandle = BspOsal_registerIntr(intNum,
                                      (BspOsal_IntrFuncPtr)IpcIsr,
                                       NULL);
    UTILS_assert(gIntrHandle != NULL);
}

/**
 *******************************************************************************
 *
 * \brief Un-Register Interrupt Handle
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void McalIpc_unRegisterInterruptHandle(Void)
{
    BspOsal_unRegisterIntr(&gIntrHandle);
}

/**
 *******************************************************************************
 *
 * \brief Ser IPC Config
 *
 * \param pCfg      [IN]     IPC Config
 *
 *******************************************************************************
 */
Void McalIpc_initIpcConfig(Cdd_IpcCfg *pCfg)
{
    /* Recommended config */
    const extern Cdd_IpcCfg CddIpcDriver_0;
    const Cdd_IpcHwMailboxCfg *tempMbxCfg;

    pCfg->ownCoreId             = CddIpcDriver_0.ownCoreId;
    pCfg->numCore               = CddIpcDriver_0.numCore;
    pCfg->remoteCoreId[0U]      = CddIpcDriver_0.remoteCoreId[0U];

    pCfg->readTimeout           = CddIpcDriver_0.readTimeout;
    pCfg->writeTimeout          = CddIpcDriver_0.writeTimeout;

#ifdef IPC_LIB_INCLUDE
    tempMbxCfg = &CddIpcDriver_0.ownRxMbCfg[0U];

    pCfg->ownRxMbCfg[0U].mailBoxId      = 7;
    pCfg->ownRxMbCfg[0U].fifoToBeUsed   = 5;
    pCfg->ownRxMbCfg[0U].userId         = 3;
    pCfg->ownRxMbCfg[0U].reserved       = tempMbxCfg->reserved;

    tempMbxCfg = &CddIpcDriver_0.ownTxMbCfg[0U];
    pCfg->ownTxMbCfg[0U].mailBoxId      = 7;
    pCfg->ownTxMbCfg[0U].fifoToBeUsed   = 7;
    pCfg->ownTxMbCfg[0U].userId         = 2;
    pCfg->ownTxMbCfg[0U].reserved       = tempMbxCfg->reserved;
#else
    tempMbxCfg = &CddIpcDriver_0.ownRxMbCfg[0U];

    pCfg->ownRxMbCfg[0U].mailBoxId      = 5;
    pCfg->ownRxMbCfg[0U].fifoToBeUsed   = 7;
    pCfg->ownRxMbCfg[0U].userId         = 3;
    pCfg->ownRxMbCfg[0U].reserved       = tempMbxCfg->reserved;

    tempMbxCfg = &CddIpcDriver_0.ownTxMbCfg[0U];
    pCfg->ownTxMbCfg[0U].mailBoxId      = 6;
    pCfg->ownTxMbCfg[0U].fifoToBeUsed   = 2;
    pCfg->ownTxMbCfg[0U].userId         = 3;
    pCfg->ownTxMbCfg[0U].reserved       = tempMbxCfg->reserved;
#endif
}

/**
 *******************************************************************************
 *
 * \brief MCAL IPC Init
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void Mcal_IpcInit(Void)
{
    McalIpc_mcuInit();
    McalIpc_registerInterruptHandle();
    McalIpc_initIpcConfig(&gIpcInitCfg);
    Cdd_IpcInit(&gIpcInitCfg);

    /* Setting the state for IPU2 */
    Utils_setAppInitState(SYSTEM_PROC_IPU2, CORE_APP_INITSTATUS_TEST_INIT_DONE);
}

/**
 *******************************************************************************
 *
 * \brief MCAL IPC De-Init
 *
 * \param NULL
 *
 *******************************************************************************
 */
Void Mcal_IpcDeInit(Void)
{
    McalIpc_unRegisterInterruptHandle();
    Cdd_IpcDeinit(&gIpcInitCfg);
    McalIpc_mcuDeInit();
}
/**
 *******************************************************************************
 *
 * \brief MCAL Lib Event Callback
 *
 * \param
 *
 *******************************************************************************
 */
FUNC(void, CDD_IPC_APP_CODE) Cdd_IpcEventNotification(
                                VAR(Cdd_IpcCoreId, AUTOMATIC) remoteProcId,
                                VAR(uint32, AUTOMATIC) eventId,
                                VAR(uint32, AUTOMATIC) payLoad,
                                P2CONST(void, AUTOMATIC, CDD_APP_DATA) pAppArg,
                                VAR(uint32, AUTOMATIC) status)
{
    if (status != SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf("MCAL: Error received on IPC! %d", status);
    }
    if ((eventId != MCAL_TX_BUFF_FREE_IPC_EVENT_ID) && (eventId != MCAL_RX_NEW_BUFF_IPC_EVENT_ID))
    {
        Vps_printf("MCAL: Unexpected event ID received on IPC! %d", eventId);
    }
    else if (eventId == MCAL_TX_BUFF_FREE_IPC_EVENT_ID)
    {
        McalTx_releaseData();
    }
    else
    {
        McalRx_processData();
    }
}

Std_ReturnType Det_ReportError(uint16 ModuleId,
                               uint8  InstanceId,
                               uint8  ApiId,
                               uint8  ErrorId)
{
    Vps_printf(" MCAL Error : Det : API [%d] error code [%d]\n",
                        ApiId, ErrorId);
    UTILS_assert(FALSE);
    return (E_OK);
}
void SchM_Enter_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0(void)
{
    return;
}

void SchM_Exit_Cdd_Ipc_IPC_EXCLUSIVE_AREA_0(void)
{
    return;
}
