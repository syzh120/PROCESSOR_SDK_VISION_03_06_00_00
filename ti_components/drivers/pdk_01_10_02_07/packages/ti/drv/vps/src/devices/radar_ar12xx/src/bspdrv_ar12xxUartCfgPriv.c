/*
 *   Copyright (c) Texas Instruments Incorporated 2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file   bspdrv_ar12xxUartCfgPriv.c
 *
 *  \brief  This file contains function definitions used privately by the
 *          AR12xx Radar sensor driver for UART configuration.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bspdrv_ar12xxPriv.h>
#include <ti/csl/soc.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <xdc/runtime/Error.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** AR12xx boot mode Opcode for Acknowledge */
#define BSP_AR12XX_UART_FLASHLDR_ACK               (0xCCU)
/** AR12xx Flashloader Synchronization pattern */
#define BSP_AR12XX_UART_FLASHLDR_SYNC_PATTERN      (0xAAU)
/** Maximum buffer size for transmit and recieve */
#define BSP_AR12XX_UART_MAX_BUFFER_SIZE             (1024U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Constant list of module base addresses for UART */
static const UInt32 gUartModuleAddrList[BSP_AR12XX_NUM_UART_INST] =
{
    SOC_UART1_BASE,
    SOC_UART2_BASE,
    SOC_UART3_BASE
};

/* String identifiers for the UART driver names */
static char        *gUartDriverNames[BSP_AR12XX_NUM_UART_INST] =
{
    "/uart0",
    "/uart1",
    "/uart2"
};

/* Character Buffer to read from the UART */
#ifndef __cplusplus
#pragma DATA_ALIGN(gUartRxMsgBuffer, 128);
#else
#pragma DATA_ALIGN(128);
#endif
static UInt8        gUartRxMsgBuffer[BSP_AR12XX_UART_MAX_BUFFER_SIZE];

/* Message Buffer to used to transmit via UART */
#ifndef __cplusplus
#pragma DATA_ALIGN(gUartTxMsgBuffer, 128);
#else
#pragma DATA_ALIGN(128);
#endif
static UInt8        gUartTxMsgBuffer[BSP_AR12XX_UART_MAX_BUFFER_SIZE];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* MISRA.FUNC.NOPROT.CALL Rule 8.2 fix */
static inline void ti_sysbios_io_GIO_Params_init(ti_sysbios_io_GIO_Params *prms);

/**
 *  \brief  PRCM Enable function to power up the UART modules.
 *
 *  \param  instId      UART Instance ID.
 *
 *  \return retVal      BSP_SOK if the power is enabled. Other error codes are
 *                      returned in case of failure.
 */
static Int32 Bsp_ar12xxUartPrcmEnable(UInt32 instId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_ar12xxUartInit(Bsp_ar12xxObj *pObj)
{
    Int32           retVal = BSP_SOK;
    Int32          dev = 0;
    Uart_ChanParams chanParams;
    UInt32          uartDevId;
    GIO_Params      ioParams;

    /* Use this structure to ensure we do not have multiple handles for the
     * same uart instance. For every UART instance indexed by the UART ID,
     * the corresponding devID is mentioned for the handle to be copied.
     */
    for (uartDevId = 0; uartDevId < BSP_AR12XX_NUM_UART_INST; uartDevId++)
    {
        /* Initializing to 0xFF first */
        pObj->uartDevMap[uartDevId] = 0xFF;
    }
    for (dev = 0; dev < pObj->initPrmsCopy.numRadarDevicesInCascade; dev++)
    {
        Error_Block     eb;
        uartDevId = pObj->initPrmsCopy.devParams[dev].uartDevInst;
        if (uartDevId < BSP_AR12XX_NUM_UART_INST)
        {
            if (pObj->uartDevMap[uartDevId] == 0xFF)
            {
                /* Enable the Uart Module */
                retVal = Bsp_ar12xxUartPrcmEnable(uartDevId);

                if (BSP_SOK == retVal)
                {
                    /* Check if the UART Dev is already getting used */

                    Error_init(&eb);

                    /* Initialize channel attributes. */
                    GIO_Params_init(&ioParams);

                    /* initialise the edma library and get the EDMA handle */
                    chanParams.hEdma = NULL;

                    /* Cross bar evt disabled */
                    chanParams.crossBarEvtParam.isCrossBarIntEn = (UInt32) FALSE;
                    /* Invalid number */
                    chanParams.crossBarEvtParam.intNumToBeMapped = 0xFF;

                    ioParams.chanParams = (Ptr) & chanParams;

                    /* create the required channels(TX/RX) for the UART demo */
                    pObj->uartTxHandle[dev] =
                        (GIO_Handle) GIO_create((xdc_String) gUartDriverNames[uartDevId],
                                                (UInt32) GIO_OUTPUT, &ioParams,
                                                &eb);
                    pObj->uartRxHandle[dev] =
                        (GIO_Handle) GIO_create((xdc_String) gUartDriverNames[uartDevId],
                                                (UInt32) GIO_INPUT, &ioParams,
                                                &eb);
                    pObj->uartDevMap[uartDevId] = dev;
                }
            }
            else
            {
                pObj->uartTxHandle[dev] = 
                    pObj->uartTxHandle[pObj->uartDevMap[uartDevId]];
                pObj->uartRxHandle[dev] = 
                    pObj->uartRxHandle[pObj->uartDevMap[uartDevId]];
            }
            if ((pObj->uartTxHandle[dev] == NULL) || (pObj->uartRxHandle[dev] == NULL))
            {
                retVal = BSP_EFAIL;
            }
        }
    }
    return retVal;
}

Int32 Bsp_ar12xxUartConnect(UInt32 deviceId, Bsp_ar12xxObj *pObj)
{
    Int32 status = BSP_SOK;

    if (pObj->initPrmsCopy.devParams[deviceId].uartDevInst <
        BSP_AR12XX_NUM_UART_INST)
    {
        /* Programming the BREAK_EN bit in LCR. */
        UARTBreakCtl(gUartModuleAddrList[
                     pObj->initPrmsCopy.devParams[deviceId].uartDevInst],
                     UART_BREAK_COND_ENABLE);
        BspOsal_sleep(100U);
        /* Wait for acknowledgement from the AR12xx */
        status = Bsp_ar12xxUartReadAck(deviceId, pObj);
        if (status == BSP_SOK)
        {
            /* Programming the BREAK_EN bit in LCR. */
            UARTBreakCtl(gUartModuleAddrList[
                pObj->initPrmsCopy.devParams[deviceId].uartDevInst],
                UART_BREAK_COND_DISABLE);
        }
    }
    return status;
}

Int32 Bsp_ar12xxUartReadAck(UInt32 deviceId, Bsp_ar12xxObj *pObj)
{
    Int32  status  = BSP_SOK;
    size_t len     = sizeof (UInt8);
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
    gUartRxMsgBuffer[0] = (UInt8) 0;
    /* Wait for the acknowledgement from AR12xx */
    do
    {
        status =
            (Int32) GIO_read(pObj->uartRxHandle[deviceId],
                             (xdc_Ptr) gUartRxMsgBuffer,
                             (xdc_SizeT *) &len);
        timeout--;
    } while ((gUartRxMsgBuffer[0] != (UInt8) BSP_AR12XX_UART_FLASHLDR_ACK)
             && (timeout != 0U));
    if (gUartRxMsgBuffer[0] != (UInt8) BSP_AR12XX_UART_FLASHLDR_ACK)
    {
        status = BSP_EFAIL;
    }
    return status;
}

Int32 Bsp_ar12xxUartSendPacket(UInt32         deviceId,
                               Bsp_ar12xxObj *pObj,
                               UInt8         *buffer,
                               UInt32         length)
{
    Int32  status        = BSP_SOK;
    UInt32 i             = 0U;
    UInt32 localCheckSum = 0U;
    UInt32 localMsgSize  = 0U;
    UInt32 txLength      = 0U;

    for (i = 0U; i < length; i++)
    {
        localCheckSum = localCheckSum + (UInt32) (buffer[i]);
    }
    /* Find the local checksum in 8 bits */
    localCheckSum = localCheckSum & 0xFFU;

    /* Get the local message size in less than 16 bits */
    localMsgSize = (length + sizeof (UInt16)) & 0xFFFFU;

    /* Send the Sync Patter to the AR12 */
    gUartTxMsgBuffer[0] = (UInt8) BSP_AR12XX_UART_FLASHLDR_SYNC_PATTERN;
    txLength = sizeof (UInt8);
    status   = (Int32) GIO_write(pObj->uartTxHandle[deviceId],
                                 (xdc_Ptr) & gUartTxMsgBuffer,
                                 (xdc_SizeT *) &txLength);
    if (status == BSP_SOK)
    {
        /* Send the Message Length. Change the endianness before sending */
        gUartTxMsgBuffer[0U] = (UInt8) ((localMsgSize & 0xFF00U) >> 8U);
        gUartTxMsgBuffer[1U] = (UInt8) (localMsgSize & 0xFFU);
        txLength = sizeof (UInt16);
        status   = (Int32) GIO_write(pObj->uartTxHandle[deviceId],
                                     (xdc_Ptr) & gUartTxMsgBuffer,
                                     (xdc_SizeT *) &txLength);
    }
    if (status == BSP_SOK)
    {
        /* Send the local checksum */
        gUartTxMsgBuffer[0U] = (UInt8) localCheckSum;
        txLength = sizeof (UInt8);
        status   = (Int32) GIO_write(pObj->uartTxHandle[deviceId],
                                     (xdc_Ptr) & gUartTxMsgBuffer,
                                     (xdc_SizeT *) &txLength);
    }
    if (status == BSP_SOK)
    {
        /* Write the input message */
        status = (Int32) GIO_write(pObj->uartTxHandle[deviceId], (xdc_Ptr) buffer,
                                   (xdc_SizeT *) &length);
    }
    return status;
}

Int32 Bsp_ar12xxUartRecvPacket(UInt32 deviceId, 
                               Bsp_ar12xxObj *pObj,
                               UInt32 length)
{
    UInt32 len           = sizeof (UInt16);
    Int32  status        = BSP_SOK;
    UInt32 i             = 0U;
    UInt32 localChecksum = 0U;
    UInt32 msgSizeLocal  = 0U;
    UInt8  recdCheckSum  = (UInt8) 0;

    /* Read the message Header - This is not used and can be discarded */
    status = (Int32) GIO_read(pObj->uartRxHandle[deviceId],
                              (xdc_Ptr) gUartRxMsgBuffer,
                              (xdc_SizeT *) &len);

    /* Read the message size and subtract 16 bits from it to get the net size */
    if (status == BSP_SOK)
    {
        status = (Int32) GIO_read(pObj->uartRxHandle[deviceId],
                                  (xdc_Ptr) gUartRxMsgBuffer,
                                  (xdc_SizeT *) &len);
    }
    if (status == BSP_SOK)
    {
        msgSizeLocal = ((UInt32) gUartRxMsgBuffer[0U] << 8U) |
                       (UInt32) gUartRxMsgBuffer[1U];
        msgSizeLocal -= sizeof (UInt16);
        if (msgSizeLocal != length)
        {
            status = BSP_EFAIL;
        }
    }
    if (status == BSP_SOK)
    {
        len = sizeof (UInt8);
        /* Read the CRC Check sum */
        status = (Int32) GIO_read(pObj->uartRxHandle[deviceId],
                                  gUartRxMsgBuffer, &len);
    }
    /* Read the full buffer */
    if (status == BSP_SOK)
    {
        recdCheckSum = gUartRxMsgBuffer[0U];
        status       = (Int32) GIO_read(pObj->uartRxHandle[deviceId],
                                        (xdc_Ptr) gUartRxMsgBuffer,
                                        (xdc_SizeT *) &msgSizeLocal);
    }
    if (status == BSP_SOK)
    {
        gUartTxMsgBuffer[0U] = BSP_AR12XX_UART_FLASHLDR_ACK;
        len    = sizeof (UInt8);
        status = (Int32) GIO_write(pObj->uartTxHandle[deviceId],
                                   (xdc_Ptr) gUartTxMsgBuffer,
                                   (xdc_SizeT *) &len);
    }

    for (i = 0U; i < msgSizeLocal; i++)
    {
        localChecksum += (UInt32) gUartRxMsgBuffer[i];
    }
    localChecksum = localChecksum & 0xFFU;

    if (localChecksum != recdCheckSum)
    {
        status = BSP_EFAIL;
    }
    return status;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static Int32 Bsp_ar12xxUartPrcmEnable(UInt32 instId)
{
    Int32 retVal = BSP_SOK;
    pmhalPrcmModuleSIdleState_t sIdleState;
    /* Constant list of module IDs for GPIO */
    const pmhalPrcmModuleId_t gUartModuleIdList[BSP_AR12XX_NUM_UART_INST] = {
        PMHAL_PRCM_MOD_UART1,
        PMHAL_PRCM_MOD_UART2,
        PMHAL_PRCM_MOD_UART3
    };

    retVal = (Int32) PMHALModuleSIdleStatusGet(gUartModuleIdList[instId],
                                               &sIdleState);
    if ((retVal == BSP_SOK) &&
        (sIdleState == PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED))
    {
        /* Enable the PRCM for GPIO instance */
        retVal = PMHALModuleModeSet(gUartModuleIdList[instId],
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
    }
    return retVal;
}
