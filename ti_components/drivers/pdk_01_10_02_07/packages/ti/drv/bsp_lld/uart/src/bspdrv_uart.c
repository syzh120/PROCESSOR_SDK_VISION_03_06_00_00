/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
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
 *  \file   bspdrv_uart.c
 *
 *  \brief  IOM Driver implementation for Uart device.
 *          This file contains the driver implementation for the Uart device.
 */

/* ========================================================================= */
/*                          INCLUDE FILES                                    */
/* ========================================================================= */

#include <string.h>
#include <assert.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/System.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <bspdrv_uartPriv.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

/* Include Family specific hwi files */
#if defined (__TI_ARM_V7M4__) || defined (BUILD_M3)
#include <ti/sysbios/family/arm/m3/Hwi.h>
#elif defined (_TMS320C6X)
#include <ti/sysbios/family/c64p/Hwi.h>
#elif defined (__ARM_ARCH_7A__)
#include <ti/sysbios/family/arm/gic/Hwi.h>
#elif defined (BUILD_A8)
#include <ti/sysbios/family/arm/a8/intcps/Hwi.h>
#elif defined (BUILD_ARP32)
#include <ti/sysbios/family/arp32/Hwi.h>
#else
#include <ti/sysbios/hal/Hwi.h>
#endif

#include <ti/csl/soc.h>

#include <ti/sysbios/family/arm/ducati/dm8148/IntMux.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

/* -------- constants -------- */
const Uart_Params              Uart_PARAMS =
{
    TRUE,                     /* cacheEnable                    */
    BSP_UART_FIFO_SIZE,       /* chunksize                      */
    TRUE,                     /* fifoEnable                     */
    UART_OPMODE_DMAINTERRUPT, /* opMode                         */
    FALSE,                    /* loopbackEnabled                */
    UART_BAUDRATE_115_2K,     /* baudRate                       */
    UART_NUMSTOPBITS_1,       /* stopBits                       */
    UART_CHARLEN_8,           /* charLen                        */
    UART_PARITY_NO,           /* parity                         */
    UART_RXTRIGLVL_8,         /* rxThreshold                    */
    UART_TXTRIGLVL_56,        /* txThreshold                    */

    {
        /* fc                             */
        UART_FCTYPE_NONE,
        UART_FCPARAM_TXNONE,
        UART_FCPARAM_RXNONE
    },
    0,                      /* edmaRxTC                       */
    0,                      /* edmaTxTC                       */
    0,                      /* hwiNumber                      */
    0xFFFFFFFFU,            /* polledModeTimeout              */
    FALSE,                  /* PRCM control disabled          */
    UART_PLLDOMAIN_0,       /* PLL domain used by the driver  */
    NULL,                   /* prcmHandle                     */
    0                       /* prcm device ID                 */
};
/**
 *  \brief  Default Channel parameters for Rx
 */
volatile const Uart_ChanParams Uart_defaultRxChanParams = {NULL};

/**
 *  \brief  Default Channel parameters for Tx
 */
const Uart_ChanParams          Uart_defaultTxChanParams = {NULL};

/* ========================================================================= */
/*                       GLOBAL MODULE STATE                                 */
/* ========================================================================= */
/**
 *  \brief  Array which is part of Uart Module State
 */
static Bool gUartModInUse[CSL_UART_PER_CNT];
/**
 *  \brief  Uart Module State Object
 */
static Uart_Module_State       Uart_module = {&gUartModInUse[0]};
/**
 *  \brief  Array of Uart instance State objects array
 */
static Uart_Object             Uart_Instances[CSL_UART_PER_CNT];

/* ========================================================================= */
/*                        LOCAL FUNCTION PROTOTYPES                          */
/* ========================================================================= */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C"
{
#endif
static Int uartMdBindDev(Ptr *devp, Int devId, Ptr devParams);

static Int uartMdUnBindDev(Ptr devp);

static Int uartMdCreateChan(Ptr             *chanp,
                            Ptr              devp,
                            String           name,
                            Int              mode,
                            Ptr              chanParams,
                            IOM_TiomCallback cbFxn,
                            Ptr              cbArg);

static Int uartMdDeleteChan(Ptr chanp);

static Int uartMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket);

static Int uartMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArg);

static Void uartIsr(UArg arg);
static Void doNothing(UInt32 tcc, EDMA3_RM_TccStatus edmaStatus, Ptr appData);

#ifdef __cplusplus
}
#endif
static Int32 uartBaudRateChangeIoctl(Uart_Object *instHandle, Ptr cmdArgs);

static Void uartTxSwiHandler(UArg arg0, UArg unUsedArg);

static Void uartRxSwiHandler(UArg arg0, UArg unUsedArg);

static Bool uartStatusIsDataReady(Uart_ChanObj *chanHandle, Error_Block *eb);

static Void uartRegisterInterrupt(Ptr             inDevp,
                                  UInt16          hwiNumber,
                                  UInt32          evt,
                                  Uart_pspUartIsr intIsr,
                                  Error_Block    *eb);

static Void uartConfigure(Uart_Object          *instHandle,
                          const Uart_DevParams *openParams,
                          Error_Block          *eb);

#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
static Int32 uartValidateParams(const Uart_Params *openParams,
                                Error_Block       *eb);
#endif

static Void uartHwSetup(const Uart_Object    *instHandle,
                        const Uart_DevParams *currentParams);

static Int32 uartSubmitIoReq(Uart_ChanObj *chanHandle,
                             IOM_Packet   *ioPacket,
                             Error_Block  *eb);

static Void uartCancelCurrentIo(Uart_ChanObj *chanHandle,
                                IOM_Packet   *ioPacket);

static UInt32 uartXfer(Uart_ChanObj *chanHandle,
                       UInt8        *buffer,
                       UInt32        numBytes,
                       Error_Block  *eb);

static Int32 uartSubmitIoReqPolled(Uart_ChanObj *chanHandle,
                                   IOM_Packet   *ioPacket,
                                   Error_Block  *eb);

static Int32 uartSubmitIoReqIntDma(Uart_ChanObj *chanHandle,
                                   IOM_Packet   *ioPacket,
                                   UInt32        hwiKey,
                                   Error_Block  *eb);

static Void uartCancelAllIo(Uart_ChanObj *chanHandle);

static inline Void uartUnRegisterInterrupt(Uart_Object *instHandle,
                                           UInt16       hwiNumber,
                                           UInt32       evt);
static Void uartIntrHandler(Uart_ChanObj *chanHandle);

static inline UInt8 uartReadByte(Uart_Object *instHandle);

static inline Void uartWriteByte(const Uart_Object *instHandle, Char data);

static Void uartSetBaudRate(const Uart_Object *instHandle, UInt32 baudRate);

static inline UInt32 uartGetLineStatus(Uart_Object const *instHandle);
static Bool uartOsCheckTimeOut(UInt64 startValue, UInt32 timeout);

static Int32 uartHandleRxError(Uart_ChanObj *chanHandle, Error_Block *eb);

#ifdef BIOS_PWRM_ENABLE
static Int32 UartRegisterNotification(Uart_Object *instHandle);

static Int32 UartUnregisterNotification(Uart_Object *instHandle);

static PWRM_NotifyResponse UartNotifyCallback(PWRM_Event eventType,
                                              Arg        eventArg1,
                                              Arg        eventArg2,
                                              Arg        clientArg);

static PWRM_NotifyResponse UartSuspendCurrentIops(Uart_Object *instHandle,
                                                  PWRM_Event   eventType);

static Int32 UartCalculateConstraints(Uart_Object *instHandle);

static Int32 UartUnregisterConstraints(Uart_Object *instHandle);

static Int32 UartCalculateClockSettings(Uart_Object  *instHandle,
                                        UInt32        setpoint,
                                        Uart_BaudRate opFreq,
                                        UInt32       *prescale);

static Int32 UartConfigureNewClkSettings(Uart_Object *instHandle,
                                         UInt32       prescale);

static PWRM_NotifyResponse UartConfigureNewVfSettings(Uart_Object *instHandle,
                                                      Uns          eventArg1,
                                                      Uns          eventArg2);
#endif

static UInt32 uartFifoWrite(const Uart_ChanObj *chanHandle,
                            const UInt8        *buffer,
                            UInt32              nwrite);

static UInt32 uartFifoRead(Uart_ChanObj *chanHandle,
                           UInt8        *buffer,
                           UInt32        bufSize,
                           Error_Block  *eb);
/* ========================================================================= */
/*                        GLOBAL VARIABLE                                    */
/* ========================================================================= */

const IOM_Fxns Uart_IOMFXNS =
{
    &uartMdBindDev,
    &uartMdUnBindDev,
    &uartMdControlChan,
    &uartMdCreateChan,
    &uartMdDeleteChan,
    &uartMdSubmitChan
};

/* ========================================================================= */
/*                          FUNCTION DEFINTIONS                              */
/* ========================================================================= */

/* Edma dummy transfer */
static Void doNothing(UInt32 tcc, EDMA3_RM_TccStatus edmaStatus, Ptr appData)
{
    /* DO NOTHING (This is a callback for the dummy transfer)                 */
}

/* ========================================================================== */
/*                           MODULE FUNCTIONS                                 */
/* ========================================================================== */

/**
 *  \brief  Function called by Bios during instance initialisation
 *
 *  \return None
 */
Void Uart_init(Void)
{
    Int i;

    for (i = (Int) 0; i < (Int) CSL_UART_PER_CNT; i++)
    {
        /* have to initialize statically */
        /*
         * Misra Waiver Reason
         * Pointer access of inUse done with in allocated limit
         * CSL_UART_PER_CNT,
         * which is allocated at static Bool gUartModInUse[CSL_UART_PER_CNT];
         * line 108
         */
        Uart_module.inUse[i] = (Bool) FALSE;
        memset((Void *) &Uart_Instances[i], (Int) 0x0, sizeof (Uart_Object));
    }
}

/**
 *  \brief  Function called by Bios during instance initialisation
 *
 *  \param  devp       [OUT]  pointer to Uart driver object
 *  \param  devId      [IN]   device Id
 *  \param  devParams  [IN]   device Parameters
 *
 *  \return IOM_COMPLETED   if success
 *          Error ID        in case of error
 *
 *  \enter  *devp           must be a valid pointer and should not be null.
 *          devParams       must be a valid pointer and should not be null.
 *          devId           must be a valid device number (<CSL_UART_PER_CNT)
 *
 *  \leave  Not Implemented.
 */
static Int uartMdBindDev(Ptr *devp, Int devId, Ptr devParams)
{
    Int32        retVal     = IOM_COMPLETED;
    Uart_Params *params     = NULL;
    Uart_Object *instHandle = NULL;
    Swi_Params   swiParams  = {0};

    /* Begin parameter checking
     *                                                 */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == devParams) || ((Int) CSL_UART_PER_CNT < devId))
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    params     = (Uart_Params *) devParams;
    instHandle = &Uart_Instances[devId];
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    retVal = uartValidateParams(params, NULL);
    /*
     * Misra Waiver Reason
     * Pointer access of inUse done with in allocated limit CSL_UART_PER_CNT,
     * there is a check of  in line 336 devId
     * which is allocated at static Bool gUartModInUse[CSL_UART_PER_CNT];
     * line 108
     */
    if (((Bool) TRUE == Uart_module.inUse[devId]) ||
        (UART_DRIVERSTATE_DELETED != instHandle->devState) ||
        ((0 == params->hwiNumber) && (UART_OPMODE_POLLED != params->opMode)) ||
        (IOM_COMPLETED != retVal))
    {
        /* Driver not in deleted (initial) state or in use               */
        retVal = IOM_EBADMODE;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                   */

    if (IOM_COMPLETED == retVal)
    {
        /*
         * Misra Waiver Reason
         * Pointer access of inUse done with in allocated limit
         * CSL_UART_PER_CNT,
         * there is a check of  in line 336 devId
         * which is allocated at static Bool gUartModInUse[CSL_UART_PER_CNT];
         * line 108
         */
        /* set the status of the module as in use                            */
        Uart_module.inUse[devId] = (Bool) TRUE;

        /* initialise the soc specific information                           */
        if (0 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART1_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT0;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART0_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART0_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_0_MODULE_FREQ;
        }
        else if (1 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART2_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT1;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART1_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART1_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_1_MODULE_FREQ;
        }
        else if (2 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART3_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT2;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART2_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART2_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_2_MODULE_FREQ;
        }
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (TI814X_BUILD)
        else if (3 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART4_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT3;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART3_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART3_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_3_MODULE_FREQ;
        }
        else if (4 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART5_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT4;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART4_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART4_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_4_MODULE_FREQ;
        }
        else if (5 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART6_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT5;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART5_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART5_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_5_MODULE_FREQ;
        }
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
        else if (6 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART7_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT6;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART6_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART6_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_6_MODULE_FREQ;
        }
        else if (7 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART8_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT7;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART7_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART7_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_7_MODULE_FREQ;
        }
        else if (8 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART9_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT8;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART8_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART8_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_8_MODULE_FREQ;
        }
        else if (9 == devId)
        {
            instHandle->deviceInfo.baseAddress = SOC_UART10_BASE;
            instHandle->deviceInfo.cpuEventNumber
                = (UInt32) CSL_INTC_EVENTID_UARTINT9;
            instHandle->deviceInfo.rxDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART9_RX;
            instHandle->deviceInfo.txDmaEventNumber
                = (UInt32) CSL_EDMA3_CHA_UART9_TX;
            instHandle->deviceInfo.inputFrequency = CSL_UART_9_MODULE_FREQ;
        }
#endif
#endif
        else
        {
            /*Do Nothing*/
        }

#if defined (TI814x_M3) || defined (C6A811x_M3)
        instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn =
            (Bool) FALSE;
        instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped =
            BSP_UART_INVALID_INT_NUM;
#endif

        instHandle->xmtChanObj.status         = UART_DRIVERSTATE_CLOSED;
        instHandle->xmtChanObj.mode           = UART_OUTPUT;
        instHandle->xmtChanObj.cbFxn          = NULL;
        instHandle->xmtChanObj.cbArg          = NULL;
        instHandle->xmtChanObj.activeIOP      = NULL;
        instHandle->xmtChanObj.bytesRemaining = 0;
        instHandle->xmtChanObj.chunkSize      = 0;
        instHandle->xmtChanObj.devHandle      = NULL;
        instHandle->xmtChanObj.errors         = 0;
        instHandle->xmtChanObj.hEdma          = Uart_defaultTxChanParams.hEdma;
        instHandle->xmtChanObj.edmaTcc        =
            instHandle->deviceInfo.txDmaEventNumber;
        instHandle->xmtChanObj.edmaChId =
            instHandle->deviceInfo.txDmaEventNumber;
        instHandle->xmtChanObj.edmaTC            = params->edmaTxTC;
        instHandle->xmtChanObj.edmaLinkChId      = EDMA3_DRV_LINK_CHANNEL;
        instHandle->xmtChanObj.edmaLinkChPhyAddr = 0U;
        instHandle->xmtChanObj.optFlag           = (Bool) FALSE;

        instHandle->xmtChanObj.gblErrCbkFxn = NULL;
        instHandle->xmtChanObj.gblErrCbkArg = NULL;

        /* Initailize Rx Channel members                                     */
        instHandle->rcvChanObj.status         = UART_DRIVERSTATE_CLOSED;
        instHandle->rcvChanObj.mode           = UART_INPUT;
        instHandle->rcvChanObj.cbFxn          = NULL;
        instHandle->rcvChanObj.cbArg          = NULL;
        instHandle->rcvChanObj.activeIOP      = NULL;
        instHandle->rcvChanObj.bytesRemaining = 0;
        instHandle->rcvChanObj.chunkSize      = 0;
        instHandle->rcvChanObj.devHandle      = NULL;
        instHandle->rcvChanObj.errors         = 0;
        instHandle->rcvChanObj.hEdma          = Uart_defaultTxChanParams.hEdma;
        instHandle->rcvChanObj.edmaTcc        =
            instHandle->deviceInfo.rxDmaEventNumber;
        instHandle->rcvChanObj.edmaChId =
            instHandle->deviceInfo.rxDmaEventNumber;
        instHandle->rcvChanObj.edmaLinkChId      = EDMA3_DRV_LINK_CHANNEL;
        instHandle->rcvChanObj.edmaLinkChPhyAddr = 0U;
        instHandle->rcvChanObj.edmaTC  = params->edmaRxTC;
        instHandle->rcvChanObj.optFlag = (Bool) FALSE;

        instHandle->rcvChanObj.gblErrCbkFxn = NULL;
        instHandle->rcvChanObj.gblErrCbkArg = NULL;

        /* Inintialize Statistics members                                     */
        instHandle->stats.rxBytes        = 0;
        instHandle->stats.txBytes        = 0;
        instHandle->stats.overrun        = 0;
        instHandle->stats.rxTimeout      = 0;
        instHandle->stats.rxFramingError = 0;
        instHandle->stats.rxBreakError   = 0;
        instHandle->stats.rxParityError  = 0;

        instHandle->devParams.fifoEnable      = params->fifoEnable;
        instHandle->devParams.loopbackEnabled = params->loopbackEnabled;
        instHandle->devParams.baudRate        = params->baudRate;
        instHandle->devParams.stopBits        = params->stopBits;
        instHandle->devParams.charLen         = params->charLen;
        instHandle->devParams.parity          = params->parity;
        instHandle->devParams.rxThreshold     = params->rxThreshold;
        instHandle->devParams.txThreshold     = params->txThreshold;
        instHandle->devParams.fc.fcType       = params->fc.fcType;
        instHandle->devParams.fc.fcParamTx    = params->fc.fcParamTx;
        instHandle->devParams.fc.fcParamRx    = params->fc.fcParamRx;
        instHandle->devParams.fifoEnable      = params->fifoEnable;
        instHandle->polledModeTimeout         = params->polledModeTimeout;
        instHandle->prcmHandle = params->prcmHandle;
        instHandle->prcmDevId  = params->prcmDevId;

        instHandle->opMode         = params->opMode;
        instHandle->devState       = UART_DRIVERSTATE_DELETED;
        instHandle->hwiNumber      = params->hwiNumber;
        instHandle->chunkSize      = params->chunkSize;
        instHandle->enableCache    = params->enableCache;
        instHandle->instNum        = (UInt32) devId;
        instHandle->txTskletHandle = NULL;
        instHandle->rxTskletHandle = NULL;
        instHandle->uartConfigured = (Bool) FALSE;

        /* Construct Queue */
        Queue_construct(&(instHandle->xmtChanObj.queuePendingList), NULL);
        Queue_construct(&(instHandle->rcvChanObj.queuePendingList), NULL);

#ifdef BIOS_PWRM_ENABLE
        instHandle->pwrmInfo.pllDomain = params->pllDomain;
        memset((Void *) &instHandle->pwrmInfo, (Int) 0x00,
               sizeof (Uart_PwrmInfo));
#endif

        if ((UART_OPMODE_INTERRUPT == instHandle->opMode) ||
            (UART_OPMODE_DMAINTERRUPT == instHandle->opMode))
        {
            /* Creating Tasklet(SWI)to schedule TX empty interrupt cause.    *
             * Becz TX empty handler requires a  wait for the transmitter    *
             * to become empty in order to write 64 bytes into FIFO. This    *
             * delay in Uart HWI handler context shall cause interrupt       *
             * latencies for other HWIs which are having less priority       *
             * than Uart HWI. Thus scheduling this TX processing in          *
             * Tasklet(SWI) context for better system performance.           */
            Swi_Params_init(&swiParams);

            /* modify the default parameters with the required params        */
            swiParams.priority = BSP_UART_TASKLET_PRIORITY;
            /*
             * Misra Waiver Reason
             * Pointer to Integer Cast:
             */
            swiParams.arg0 = (UArg) & instHandle->xmtChanObj;
            /* create the task that will be used for buffering tx data       */
            Swi_construct(&instHandle->txTskletStruct, uartTxSwiHandler,
                          &swiParams,
                          NULL);
            instHandle->txTskletHandle = Swi_handle(&instHandle->txTskletStruct);
            /*
             * Misra Waiver Reason
             * Pointer to Integer Cast:
             */
            swiParams.arg0 = (UArg) & instHandle->rcvChanObj;
            Swi_construct(&instHandle->rxTskletStruct, uartRxSwiHandler,
                          &swiParams,
                          NULL);
            instHandle->rxTskletHandle = Swi_handle(&instHandle->rxTskletStruct);

            if ((NULL == instHandle->txTskletHandle) ||
                (NULL == instHandle->rxTskletHandle))
            {
                retVal = IOM_EBADARGS;
                System_printf(
                    "uartMdBindDev: Creating Tasklet handle failed\r\n");
            }
        }
        else if (UART_OPMODE_POLLED == instHandle->opMode)
        {
            /* polled mode of operation                                      */
            Semaphore_construct(&instHandle->readSyncSem, (Int32) 1, NULL);
            Semaphore_construct(&instHandle->writeSyncSem, (Int32) 1, NULL);
        }
        else
        {
            /* DMA Mode - Need not register Swi Handlers */
        }

        if ((IOM_COMPLETED == retVal)
            && (FALSE == instHandle->devParams.prcmPwrmEnable))
        {
#ifdef BIOS_PWRM_ENABLE
            retVal = (Int32) PWRM_setDependency(
                (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId);
#else
            /* power on using PRCM API
             *                                        */

#endif
        }

#ifdef BIOS_PWRM_ENABLE
        if ((IOM_COMPLETED == retVal) &&
            (TRUE == instHandle->devParams.prcmPwrmEnable))
        {
            /* unregister all the PWRM event notifications                   */
            retVal = UartRegisterNotification(instHandle);
        }
#endif
        if (IOM_COMPLETED == retVal)
        {
            instHandle->devState = UART_DRIVERSTATE_CREATED;
            *devp = (Ptr) instHandle;
        }
    }
    return ((Int) retVal);
}

/*
 *  \brief  Function called by Bios during closing of the instance
 *
 *  \param  devp       [IN]  pointer to Uart driver object
 *
 *  \return IOM_COMPLETED   if success
 *          Error ID        in case of error
 *
 *  \enter  devp       must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int uartMdUnBindDev(Ptr devp)
{
    Uart_Object *instHandle = NULL;
    Int32        retVal     = IOM_COMPLETED;
    Swi_Struct  *uartSwiStruct;

    /* Begin parameter checking
     *                                                 */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == devp)
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    instHandle = (Uart_Object *) devp;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == instHandle) ||
        (CSL_UART_PER_CNT <= instHandle->instNum) ||
        (UART_DRIVERSTATE_CREATED != instHandle->devState) ||
        (UART_DRIVERSTATE_CLOSED != instHandle->xmtChanObj.status) ||
        (UART_DRIVERSTATE_CLOSED != instHandle->rcvChanObj.status))
    {
        retVal = IOM_EBADARGS;
    }
}

#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
       /* End parameter checking
        *                                                   */

    if (IOM_COMPLETED == retVal)
    {
        /* Unregister interrupts                                             */
        uartUnRegisterInterrupt(instHandle,
                                (UInt16) instHandle->hwiNumber,
                                (UInt32) instHandle->deviceInfo.cpuEventNumber);

        /* Deleting Tasklet handler                                          */
        if (NULL != instHandle->txTskletHandle)
        {
            uartSwiStruct = Swi_struct(instHandle->txTskletHandle);
            Swi_destruct(uartSwiStruct);
        }

        if (NULL != instHandle->rxTskletHandle)
        {
            uartSwiStruct = Swi_struct(instHandle->rxTskletHandle);
            Swi_destruct(uartSwiStruct);
        }

        retVal = Uart_localPrcmOn(instHandle, NULL);

        if (IOM_COMPLETED == retVal)
        {
            retVal = Uart_localPrcmOff(instHandle, NULL);
        }

        if ((IOM_COMPLETED == retVal)
            && (FALSE == instHandle->devParams.prcmPwrmEnable))
        {
#ifdef BIOS_PWRM_ENABLE
            /* power off  using PWRM API                                     */
            retVal = (Int32) PWRM_releaseDependency(
                (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId);
#else
            /* power off using PRCM API                               */

#endif
        }

#ifdef BIOS_PWRM_ENABLE
        if ((IOM_COMPLETED == retVal) &&
            (TRUE == instHandle->devParams.prcmPwrmEnable))
        {
            /* register the notify function for the PWRM events              */
            retVal = UartUnregisterNotification(instHandle);
        }
#endif
        instHandle->devState = UART_DRIVERSTATE_DELETED;
        /*
         * Misra Waiver Reason
         * instHandle->instNum check done for CSL_UART_PER_CNT
         * Pointer access of inUse done with in allocated limit
         * CSL_UART_PER_CNT,
         * which is allocated at static Bool gUartModInUse[CSL_UART_PER_CNT];
         * line 108
         */
        Uart_module.inUse[instHandle->instNum] = (Bool) FALSE;
    }
    return ((Int) retVal);
}

/* ========================================================================= */
/*                           IOM FUNCTIONS                                   */
/* ========================================================================= */

/**
 *  \brief  Creates a communication channel in specified mode to communicate
 *          data between the application and the Uart device instance. This
 *          function sets the required hardware configurations for the data
 *          transactions.it returns configured channel handle to application.
 *          which will be used in all further transactions with the channel.
 *
 *          This function is called in response to a SIO_create call.
 *  \param     chanp        [OUT]    channel object pointer
 *  \param     devp         [IN]     pointer to uart instance
 *  \param     name         [IN]     Uart Instance name like Uart0
 *  \param     mode         [IN]     channel  mode -> input or output
 *  \param     chanParams   [IN]     channel parameters from user
 *  \param     cbFxn        [IN]     callback function pointer
 *  \param     cbArg        [IN]     callback function Arguments
 *
 *  \return    IOM_COMPLETED   if success
 *             Error ID        in case of error
 *
 *  \enter     chanp      must be a valid pointer and should not be null.
 *             devp       must be a valid pointer and should not be null.
 *             name       must be a valid name.
 *             mode       must be a valid mode, either input or output.
 *             chanParams must be a valid pointer and should not be null.
 *             cbFxn      must be a valid pointer and should not be null.
 *             cbArg      must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int uartMdCreateChan(Ptr             *chanp,
                            Ptr              devp,
                            String           name,
                            Int              mode,
                            Ptr              chanParams,
                            IOM_TiomCallback cbFxn,
                            Ptr              cbArg)
{
    Uart_Object        *instHandle  = NULL;
    Uart_ChanObj       *chanHandle  = NULL;
    Bool                bFalseWhile = (Bool) TRUE;
    UInt32              key         = 0;
    Bool                pscPwrOn    = (Bool) FALSE;
    Int32               retVal      = IOM_COMPLETED;
    Int32               status      = IOM_COMPLETED;
    Uart_ChanParams    *chanparams  = NULL;
    UInt32              reqTcc;
    EDMA3_RM_EventQueue queueNum = 0;

    /* Begin parameter checking
     *                                                 */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == cbFxn) ||
        (NULL == cbArg) ||
        ((IOM_INPUT != mode) && (IOM_OUTPUT != mode)) ||
        (NULL == devp) ||
        (NULL == chanp))
    {
        retVal = IOM_EBADARGS;
    }
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                   */

    if (IOM_COMPLETED == retVal)
    {
        do
        {
            bFalseWhile = (Bool) FALSE;
            instHandle  = (Uart_Object *) devp;

            /* To remove the compiler warnings                               */
            if (NULL != name)
            {
                name = name;
            }

            chanparams = (Uart_ChanParams *) chanParams;
            /* check the current mode of operation and assign suitable handle */
            if (IOM_INPUT == mode)
            {
                chanHandle = (Uart_ChanObj *) &instHandle->rcvChanObj;
            }
            else
            {
                chanHandle = (Uart_ChanObj *) &instHandle->xmtChanObj;
            }

            /* Begin parameter checking
             *                                                 */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
            /* check if the channel was already opened.if already open then  *
             * flag error and bail out                                       */
            if ((NULL == chanHandle) ||
                (UART_DRIVERSTATE_OPENED == chanHandle->status))
            {
                retVal = IOM_EBADARGS;
            }

            if ((IOM_COMPLETED == retVal) &&
                ((UART_OPMODE_DMAINTERRUPT == instHandle->opMode) &&
                 ((NULL == chanparams) ||
                  (NULL == chanparams->hEdma))))
            {
                retVal = IOM_EBADARGS;
            }

#endif      /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
            /* End parameter checking
             *                                                   */
            if (IOM_COMPLETED == retVal)
            {
                /* enter critical section
                 *                                       */
                key = (UInt32) Hwi_disable();

                /* Mark channel status as allocated.
                 *                            */
                chanHandle->status = UART_DRIVERSTATE_OPENED;

                /* exit critical section
                 *                                        */
                Hwi_restore(key);

                chanHandle->mode      = (Uart_IoMode) (mode);
                chanHandle->devHandle = instHandle;

                /* Assign the respective callback function
                 *                       */
                chanHandle->cbFxn = cbFxn;
                chanHandle->cbArg = (Ptr) cbArg;

                retVal   = Uart_localPrcmOn(instHandle, NULL);
                pscPwrOn = (Bool) TRUE;
            }
            else
            {
                break;
            }

#if defined (TI814x_M3) || defined (C6A811x_M3)
            if (IOM_COMPLETED == status)
            {
                if (TRUE == chanparams->crossBarEvtParam.isCrossBarIntEn)
                {
                    instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn =
                        chanparams->crossBarEvtParam.isCrossBarIntEn;
                    instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped =
                        chanparams->crossBarEvtParam.intNumToBeMapped;
                }
                else
                {
                    instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn
                        = (Bool) FALSE;
                    instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped
                        = 0xFF;
                }
            }
#endif

            /* enter critical section                                         */
            key = (UInt32) Hwi_disable();

            if (FALSE == instHandle->uartConfigured)
            {
                instHandle->uartConfigured = (Bool) TRUE;

                /* exit critical section                                      */
                Hwi_restore(key);

#ifdef BIOS_PWRM_ENABLE
                if ((IOM_COMPLETED == status) &&
                    (TRUE == instHandle->devParams.prcmPwrmEnable))
                {
                    status = UartCalculateConstraints(instHandle);
                }
#endif
                /* Configure Uart hw for communication parameters only once   *
                 * and for the second channels create call - we need to skip  *
                 * this function call                                         */
                uartConfigure(instHandle, &instHandle->devParams, NULL);

                if ((UART_OPMODE_INTERRUPT == instHandle->opMode) ||
                    (UART_OPMODE_DMAINTERRUPT == instHandle->opMode))
                {
                    /* Register interrupts                                    */
                    uartRegisterInterrupt(
                        (Ptr) instHandle,
                        (UInt16) instHandle->hwiNumber,
                        (UInt32) instHandle->deviceInfo.cpuEventNumber,
                        &uartIsr,
                        NULL);
                }
            }
            else
            {
                /* exit critical section                                      */
                Hwi_restore(key);
            }
            if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
            {
                if (NULL != chanparams->hEdma)
                {
                    chanHandle->hEdma = chanparams->hEdma;

                    status = (Int32) EDMA3_DRV_requestChannel(
                        (EDMA3_DRV_Handle) chanHandle->hEdma,
                        &chanHandle->edmaChId,
                        &chanHandle->edmaTcc,
                        (EDMA3_RM_EventQueue) chanHandle->edmaTC,
                        &Uart_localIsrEdma,
                        (void *) chanHandle);

                    if (IOM_COMPLETED != status)
                    {
                        status = IOM_EBADARGS;
                        System_printf("uartMdCreateChan: Uart_E_badArgs");
                    }

                    /* For requesting for a Dummy PaRam set                   */
                    /* Misra C Literal Unisgned Suffix Waiver Reason: Macro in
                     * EDMA LLD */

                    chanHandle->edmaLinkChId = EDMA3_DRV_LINK_CHANNEL;
                    /* Misra C Literal Unisgned Suffix Waiver Reason: Macro in
                     * EDMA LLD */
                    reqTcc = EDMA3_DRV_TCC_ANY;

                    status = EDMA3_DRV_requestChannel(
                        chanHandle->hEdma,
                        &chanHandle->edmaLinkChId,
                        &reqTcc,
                        queueNum,
                        &doNothing,
                        NULL);

                    if (IOM_COMPLETED == status)
                    {
                        status = EDMA3_DRV_getPaRAMPhyAddr(
                            chanHandle->hEdma,
                            chanHandle->edmaLinkChId,
                            &chanHandle->edmaLinkChPhyAddr);
                    }

                    if (IOM_COMPLETED != status)
                    {
                        status = IOM_EBADARGS;
                    }
                }
                else /* if EDMA handle is NULL                               */
                {
                    System_printf("uartMdCreateChan: Uart_E_badArgs");
                    status = IOM_EBADARGS;
                }
            }
            chanHandle->activeBuf      = NULL;
            chanHandle->activeIOP      = NULL;
            chanHandle->bytesRemaining = 0;
            /* If fifo is enabled then transfer chunk could be FIFO size else *
             * only one byte can be trasferred per interrupt                  */
            if (TRUE == instHandle->devParams.fifoEnable)
            {
                chanHandle->chunkSize = instHandle->chunkSize;
            }
            else
            {
                chanHandle->chunkSize = BSP_UART_FIFO_DISABLED_CHUNK_SIZE;
            }

            if ((UART_OPMODE_POLLED != instHandle->opMode)
                && (UART_INPUT == chanHandle->mode))
            {
                /* Enabling Line Status Interrupt if receive channel is
                 * created, in order to process Line status error interrupts. */
                UARTIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) UART_INTR_RLS);
            }
        }
        while (bFalseWhile);
        if ((Bool) TRUE == pscPwrOn)
        {
            status = Uart_localPrcmOff(instHandle, NULL);

            if (IOM_COMPLETED == retVal)
            {
                retVal = status;
            }
        }

        if (IOM_COMPLETED != retVal)
        {
            *chanp = NULL;
        }
        else
        {
            *chanp = (Ptr) chanHandle;
        }
    }

    return ((Int) retVal);
}

/**
 *  \brief    This function is called by the application to close a previously
 *            opened channel.it deletes the channel so that it is not available
 *            for further transactions. All the allocated resources are freed &
 *            the channel will be ready for the "open" operation once again.
 *
 *  \param    chanp      [IN]   Handle to the channel.
 *
 *  \return   IOM_COMPLETED   if success
 *            Error ID        in case of error
 *
 *  \enter    chanp      must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int uartMdDeleteChan(Ptr chanp)
{
    Uart_Object  *instHandle = NULL;
    Uart_ChanObj *chanHandle = NULL;
    UInt32        key        = 0;
    Int32         retVal     = IOM_COMPLETED;
    UInt32        isTxFifoEmpty, txFifoTimeout;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == chanp)
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    chanHandle = (Uart_ChanObj *) chanp;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((UART_DRIVERSTATE_OPENED != chanHandle->status))
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    instHandle = (Uart_Object *) chanHandle->devHandle;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == instHandle)
    {
        retVal = IOM_EBADARGS;
    }
}
}
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if (IOM_COMPLETED == retVal)
    {
        if ((Bool) TRUE ==
            Queue_empty(Queue_handle(&(chanHandle->queuePendingList))))
        {
            /*  Close EDMA Channel                                            */
            if ((UART_OPMODE_DMAINTERRUPT == instHandle->opMode))
            {
                EDMA3_DRV_freeChannel(
                    chanHandle->hEdma,
                    chanHandle->edmaChId);

                /* free the already allocated PaRAM entries               */
                EDMA3_DRV_freeChannel(
                    chanHandle->hEdma,
                    chanHandle->edmaLinkChId);
            }

            if (UART_OUTPUT == chanHandle->mode)
            {
                /* Wait for TX to complete the transfer */
                txFifoTimeout = BSP_UART_TRANSMITEMPTY_TRIALCOUNT;
                while (txFifoTimeout > 0U)
                {
                    /* Get TX FIFO status */
                    isTxFifoEmpty = UARTSpaceAvail(
                        (UInt32) instHandle->deviceInfo.baseAddress);
                    if ((UInt32) TRUE == isTxFifoEmpty)
                    {
                        /* FIFO and Shift register is empty */
                        break;
                    }

                    Task_sleep((UInt32) BSP_UART_TX_FIFO_WAIT_PERIOD);
                    txFifoTimeout--;
                }

                if (txFifoTimeout == 0U)
                {
                    System_printf(
                        "uartMdDeleteChan: Warning: TX FIFO not empty!!");
                }
            }

            key = (UInt32) Hwi_disable();

            /* Free this channel resource                                     */
            chanHandle->status = UART_DRIVERSTATE_CLOSED;

            if (IOM_COMPLETED == Uart_localPrcmOn(instHandle, NULL))
            {
                /* Disable Uart interrupt causes                              */
                if (UART_INPUT == chanHandle->mode)
                {
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) (UART_INTR_RLS | UART_INTR_RHR));
                }
                else
                {
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) (UART_INTR_THR));
                }
                retVal = Uart_localPrcmOff(instHandle, NULL);
            }

            /* Reset the error callback pointer to NULL                       */
            chanHandle->gblErrCbkFxn = NULL;
            chanHandle->gblErrCbkArg = NULL;

            Hwi_restore(key);
        }
        else /* Some IOPs are pending                                         */
        {
            retVal = IOM_EBADMODE;
            System_printf("uartMdDeleteChan: Uart_E_iopPendingError");
        }
        /* Updates the channel port Void                                      */
        chanHandle->devHandle = NULL;
    }

#ifdef BIOS_PWRM_ENABLE
    if (IOM_COMPLETED == retVal)
    {
        /* if both the channels are deleted then unregister all the contraints
         */
        if ((UART_DRIVERSTATE_CLOSED == instHandle->xmtChanObj.status) &&
            (UART_DRIVERSTATE_CLOSED == instHandle->rcvChanObj.status))
        {
            retVal = UartUnregisterConstraints(instHandle);
        }
    }
#endif
    return ((Int) retVal);
}

/**
 *  \brief Submit a I/O packet to a channel for processing
 *
 *   The GIO layer calls this function to cause the mini-driver
 *   to process the IOM_Packet for read/write operations.
 *
 *  \param   chanp      [IN]  Handle to the channel
 *  \param   ioPacket   [IN]  Pointer to packet to be submitted
 *
 *  \return  IOM_COMPLETED, if packet is fully processed
 *           IOM_PENDING,   if packet is not fully processed
 *           negative error in case of error
 *
 *  \enter   chanp      must be a valid pointer and should not be null.
 *           ioPacket   must be a valid pointer and should not be null.
 *
 *
 *  \leave  Not Implemented.
 */
static Int uartMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket)
{
    Uart_ChanObj *chanHandle = NULL;
    Uart_Object  *instHandle = NULL;
    Bool          pscPwrOn   = (Bool) FALSE;
    Int32         retVal     = IOM_COMPLETED;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    /* The read and write command should give a proper buffer                 *
     * hence check if the buffer pointer is not null                          */
    if ((NULL == chanp) || (NULL == ioPacket) ||
        (((IOM_ABORT != ioPacket->cmd) && (IOM_FLUSH != ioPacket->cmd))
         && ((NULL == ioPacket->addr) || (0 == ioPacket->size))))
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    chanHandle = (Uart_ChanObj *) chanp;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((UART_DRIVERSTATE_OPENED != chanHandle->status) ||
        (NULL == chanHandle->devHandle))
    {
        retVal = IOM_EBADARGS;
    }
    else
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    instHandle = (Uart_Object *) chanHandle->devHandle;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
}
}
#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                    */

    if (IOM_COMPLETED == retVal)
    {
        /* check the command and process it stream will take care that        *
         * proper command is passed hence no need to check it once again      */
        if ((IOM_READ == ioPacket->cmd) || (IOM_WRITE == ioPacket->cmd))
        {
            /* request will be posted for processing. Now depending on        *
             * The mode of operation we need to either Wait for               *
             * processing to complete or the callback function to be          *
             * called                                                         */
            retVal = Uart_localPrcmOn(instHandle, NULL);

            if (IOM_COMPLETED == retVal)
            {
                pscPwrOn = (Bool) TRUE;
                retVal   = uartSubmitIoReq((Uart_ChanObj *) chanHandle,
                                           ioPacket, NULL);
            }
        }
        else if ((UART_OPMODE_POLLED != instHandle->opMode) &&
                 ((IOM_ABORT == ioPacket->cmd) || (IOM_FLUSH == ioPacket->cmd)))
        {
            /* we will try and abort all the packets except if the driver is  *
             * in the POLLED mode as in polled mode we will be executing in   *
             * task context and till it return control to application, an     *
             * abort call cannot come to us                                   */
            uartCancelAllIo(chanHandle);
        }
        else
        {
            /* unknown command has been passed to the driver hence set the    *
             * status of the command as error                                 */
            retVal = IOM_EBADARGS;
        }
    }

    /* update the status of the IO packet here                                */
    if (IOM_COMPLETED == retVal)
    {
        if ((UART_OPMODE_POLLED == instHandle->opMode) &&
            ((Bool) TRUE == pscPwrOn))
        {
            retVal = Uart_localPrcmOff(instHandle, NULL);
        }
    }
    else if (IOM_PENDING == retVal)
    {
        retVal = IOM_PENDING;
    }
    else
    {
        if ((Bool) TRUE == pscPwrOn)
        {
            /* The submit did not succeed hence power off the module.         */
            Uart_localPrcmOff(instHandle, NULL);
        }
        retVal = IOM_EBADIO;
    }
    return (retVal);
}

/**
 *  \brief   This function executes a control command passed by the application
 *
 *   The application's request for a IOCTL to be executed is routed here by the
 *   stream. if the command is supported then the control command is executed.
 *
 *  \param    chanp      [IN]    Channel handle
 *  \param    cmd        [IN]    control command given by the application
 *  \param    cmdArgs    [IN]    Optional argss required for command execution
 *
 *  \return   IOM_COMPLETED, if success
 *            negative error in case of error
 *
 *  \enter    chanp      must be a valid pointer and should not be null.
 *            cmd        must be a valid IOCTL command.
 *            cmdArg     must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Int uartMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArg)
{
    Uart_Object  *instHandle = NULL;
    Uart_ChanObj *chanHandle = NULL;
    Int32         retVal     = IOM_COMPLETED;
    UInt32        hwiKey     = 0;

    /* Begin parameter checking
     *                                                  */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if (NULL == chanp)
    {
        retVal = IOM_EBADARGS;
    }
    /* These command do not
     * cmdARg. Hence this check
     */
    if ((IOM_COMPLETED == retVal) && ((cmd != IOCTL_UART_RESET_TX_FIFO) &&
                                      (cmd != IOCTL_UART_RESET_RX_FIFO) &&
                                      (cmd != IOCTL_UART_CANCEL_CURRENT_IO) &&
                                      (cmd != IOCTL_UART_CLEAR_STATS) &&
                                      (cmd != IOCTL_UART_FLUSH_ALL_REQUEST)))
    {
        if (NULL == cmdArg)
        {
            retVal = IOM_EBADARGS;
        }
    }

    if (IOM_COMPLETED == retVal)
    {
#endif /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
       /* get the handle to the channel to send the ICOTL to                 */
    chanHandle = (Uart_ChanObj *) chanp;
    instHandle = (Uart_Object *) chanHandle->devHandle;
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
    if ((NULL == instHandle) ||
        (UART_DRIVERSTATE_OPENED != chanHandle->status))
    {
        retVal = IOM_EBADARGS;
    }
}

#endif  /* PSP_DISABLE_INPUT_PARAMETER_CHECK */
    /* End parameter checking
     *                                                   */
    if (IOM_COMPLETED == retVal)
    {
        UInt32 lineStatus = 0;
        /* Get the Line status of Uart. Uart ioctl commands to change baud   *
         * rate, stop bit, data bit, parity, flow control and other clock    *
         * related paramters should not be allowed when IO is on progress    *
         * ie. TX FIFO is not empty                                          */
        lineStatus =
            UARTSpaceAvail((UInt32) instHandle->deviceInfo.baseAddress);

        /*
         * =======================IOCTL_UART_SET_BAUD==========================
         */
        if (IOCTL_UART_SET_BAUD == cmd)
        {
            /* If TX FIFO is empty, then process this command                */
            if ((UInt32) FALSE != lineStatus)
            {
                retVal = uartBaudRateChangeIoctl((Uart_Object *) instHandle,
                                                 (Ptr) cmdArg);
            }
            else
            {
                /* IO operation is going on. Baud rate change should not      *
                 * be entertained.                                            */
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * ===============IOCTL_UART_SET_STOPBITS==============================
         */
        else if (IOCTL_UART_SET_STOPBITS == cmd)
        {
            /* If TX FIFO is empty, then process this command               */
            if ((UInt32) FALSE != lineStatus)
            {
                UInt32           lcrRegValue = 0;

                Uart_NumStopBits stopBits = UART_NUMSTOPBITS_1;
                stopBits = *((Uart_NumStopBits *) cmdArg);

                lcrRegValue =
                    UARTRegConfigModeEnable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        UART_REG_OPERATIONAL_MODE);

                if ((UART_CHARLEN_5 == (lcrRegValue &
                                        UART_LCR_CHAR_LENGTH_MASK))
                    && (UART_NUMSTOPBITS_2 == stopBits))
                {
                    retVal = IOM_EBADARGS;
                }
                else
                {
                    /* Perform error checking on stop bits                    */
                    switch (stopBits)
                    {
                        case UART_NUMSTOPBITS_1:
                        case UART_NUMSTOPBITS_1_5:
                        case UART_NUMSTOPBITS_2:
                            /* Setting the stop bits
                             *                             */
                            if (UART_NUMSTOPBITS_1_5 == stopBits)
                            {
                                UARTLineCharacConfig(
                                    (UInt32)
                                    instHandle->deviceInfo.
                                    baseAddress,
                                    (UInt32) (
                                        UART_LCR_NB_STOP_NB_STOP_VALUE_1
                                        <<
                                        UART_LCR_NB_STOP_SHIFT),
                                    (UInt32) (lcrRegValue &
                                              UART_LCR_PARITY_EN_MASK));
                            }
                            else
                            {
                                UARTLineCharacConfig(
                                    (UInt32)
                                    instHandle->deviceInfo.
                                    baseAddress,
                                    (UInt32) stopBits |
                                    UART_LCR_CHAR_LENGTH_MASK,
                                    (UInt32) (lcrRegValue &
                                              UART_LCR_PARITY_EN_MASK));
                            }
                            break;
                        default:
                            retVal = IOM_EBADARGS;
                            break;
                    }

                    if (IOM_COMPLETED == retVal)
                    {
                        /* Update instance object */
                        instHandle->devParams.stopBits = stopBits;
                    }
                }
            }
            else
            {
                /* IO operation is going. Stop bit change should not be       *
                 * entertained.                                               */
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * ================IOCTL_UART_SET_DATABITS=============================
         */
        else if (IOCTL_UART_SET_DATABITS == cmd)
        {
            /* If TX FIFO is empty, then process this command                 */
            if ((UInt32) FALSE != lineStatus)
            {
                UInt32       lcrRegValue = 0;
                Uart_CharLen charLen     = UART_CHARLEN_8;
                charLen = *((Uart_CharLen *) cmdArg);

                lcrRegValue = UARTRegConfigModeEnable(
                    (UInt32)
                    instHandle->deviceInfo.
                    baseAddress,
                    UART_REG_OPERATIONAL_MODE);

                /* Perform error checking on character bits                   */
                switch (charLen)
                {
                    case UART_CHARLEN_5:
                    case UART_CHARLEN_6:
                    case UART_CHARLEN_7:
                    case UART_CHARLEN_8:
                        /* Setting the character length                       */
                        UARTLineCharacConfig(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            (UInt32) charLen,
                            (UInt32) (lcrRegValue & UART_LCR_PARITY_EN_MASK));
                        break;
                    default:
                        retVal = IOM_EBADARGS;
                        break;
                }

                if (IOM_COMPLETED == retVal)
                {
                    /* Update instance object */
                    instHandle->devParams.charLen = charLen;
                }
            }
            else
            {
                /* IO operation is going. Stop bit change should not be       *
                 * entertained.                                               */
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * ==================IOCTL_UART_SET_PARITY=============================
         */
        else if (IOCTL_UART_SET_PARITY == cmd)
        {
            /* If TX FIFO is empty, then process this command                 */
            if ((UInt32) FALSE != lineStatus)
            {
                UInt32 lcrRegValue = 0;
                Int32  parity;

                parity = *((Uart_Parity *) cmdArg);

                lcrRegValue = UARTRegConfigModeEnable(
                    (UInt32)
                    instHandle->deviceInfo.
                    baseAddress,
                    UART_REG_OPERATIONAL_MODE);

                /* Perform error checking on parity bits                      */
                switch (parity)
                {
                    case UART_PARITY_ODD:
                    case UART_PARITY_EVEN:
                    case UART_PARITY_NO:
                        /* Setting the parity                                 */
                        UARTLineCharacConfig(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            (UInt32) (lcrRegValue &
                                      (UART_LCR_NB_STOP_MASK |
                                       UART_LCR_CHAR_LENGTH_MASK)),
                            (UInt32) parity);
                        break;
                    default:
                        retVal = (IOM_EBADARGS);
                        break;
                }

                if (IOM_COMPLETED == retVal)
                {
                    /* Update instance object */
                    instHandle->devParams.parity = parity;
                }
            }
            else
            {
                /* IO operation is going. Parity change should not be         *
                 * entertained.                                               */
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * =============IOCTL_UART_SET_FLOWCONTROL=============================
         */
        else if (IOCTL_UART_SET_FLOWCONTROL == cmd)
        {
            /* If TX FIFO is empty, then process this command                 */
            if ((UInt32) FALSE != lineStatus)
            {
                Uart_FlowControl *fc = NULL;
                fc = (Uart_FlowControl *) cmdArg;

                switch (fc->fcType)
                {
                    case UART_FCTYPE_HW:
                        /* Enable HW flow control   */
                        if ((UART_FCPARAM_AUTO_CTS == fc->fcParamTx) &&
                            (UART_FCPARAM_AUTO_RTS != fc->fcParamRx))
                        {
                            UARTAutoRTSAutoCTSControl(
                                (UInt32)
                                instHandle->deviceInfo.
                                baseAddress,
                                UART_AUTO_CTS_ENABLE,
                                UART_AUTO_RTS_DISABLE);
                        }
                        else /* Auto RTS and auto CTS */
                        {
                            UARTAutoRTSAutoCTSControl(
                                (UInt32)
                                instHandle->deviceInfo.
                                baseAddress,
                                UART_AUTO_CTS_ENABLE,
                                UART_AUTO_RTS_ENABLE);
                        }
                        break;

                    case UART_FCTYPE_NONE:
                        /* Disable Autoflow control   */
                        UARTAutoRTSAutoCTSControl(
                            (UInt32)
                            instHandle->deviceInfo.
                            baseAddress,
                            UART_AUTO_CTS_DISABLE,
                            UART_AUTO_RTS_DISABLE);
                        break;

                    case UART_FCTYPE_SW:
                        /* Not supported by the driver */
                        retVal = IOM_EBADARGS;
                        break;

                    default:
                        retVal = IOM_ENOTIMPL;
                        break;
                }

                if (IOM_COMPLETED == retVal)
                {
                    /* Update instance object */
                    instHandle->devParams.fc.fcType    = fc->fcType;
                    instHandle->devParams.fc.fcParamTx = fc->fcParamTx;
                    instHandle->devParams.fc.fcParamRx = fc->fcParamRx;
                }
            }
            else
            {
                /* IO operation is going. Parity change should not be
                 * entertained.                                               */
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * ==============IOCTL_UART_SET_TRIGGER_LEVEL==========================
         */
        else if (IOCTL_UART_SET_TRIGGER_LEVEL == cmd)
        {
            /* set the trigger level for the Rx FIFo                          */
            /* If TX FIFO is empty, then process this command                 */
            if ((UInt32) FALSE != lineStatus)
            {
                UInt32 fcrValue = 0;
                /* Validate params and FIFO Enable                            */
                if (TRUE == instHandle->devParams.fifoEnable)
                {
                    Uart_TrigLvl *trigLevel;

                    trigLevel = (Uart_TrigLvl *) cmdArg;

                    /* Make FCR value */
                    retVal =
                        Uart_localMakeFCR(instHandle, trigLevel, &fcrValue);
                    if (IOM_COMPLETED == retVal)
                    {
                        /* Update instance object */
                        instHandle->devParams.txThreshold =
                            trigLevel->txTrigLvl;
                        instHandle->devParams.rxThreshold =
                            trigLevel->rxTrigLvl;

                        /* Write into FCR                                     */
                        UARTFIFOCtrlRegWrite(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            (UInt32) fcrValue);
                    }
                }
                else
                {
                    retVal = IOM_EBADMODE;
                }
            }
            else
            {
                /* IO operation is going. Parity change should not be         *
                 * entertained.                                               */
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * =================IOCTL_UART_RESET_TX_FIFO===========================
         */
        else if (IOCTL_UART_RESET_TX_FIFO == cmd)
        {
            /* check if FIFO is supported and then reset the TX  FIFO         */
            if ((TRUE == instHandle->devParams.fifoEnable) &&
                (UART_OUTPUT == chanHandle->mode))
            {
                UInt32       fcrValue;
                Uart_TrigLvl trigLevel;

                trigLevel.txTrigLvl = instHandle->devParams.txThreshold;
                trigLevel.rxTrigLvl = instHandle->devParams.rxThreshold;

                /* Make FCR value */
                retVal = Uart_localMakeFCR(instHandle, &trigLevel, &fcrValue);
                if (IOM_COMPLETED == retVal)
                {
                    /* Set TXFIFO Clear Bit */
                    fcrValue |= UART_FCR_TX_FIFO_CLEAR_MASK;

                    /* Write into FCR */
                    UARTFIFOCtrlRegWrite(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) fcrValue);
                }
            }
            else
            {
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * =================IOCTL_UART_RESET_RX_FIFO===========================
         */
        else if (IOCTL_UART_RESET_RX_FIFO == cmd)
        {
            /* check if FIFO is supported and then reset RX FIFO              */
            if ((TRUE == instHandle->devParams.fifoEnable) &&
                (UART_INPUT == chanHandle->mode))
            {
                UInt32       fcrValue;
                Uart_TrigLvl trigLevel;

                trigLevel.txTrigLvl = instHandle->devParams.txThreshold;
                trigLevel.rxTrigLvl = instHandle->devParams.rxThreshold;

                /* Make FCR value */
                retVal = Uart_localMakeFCR(instHandle, &trigLevel, &fcrValue);
                if (IOM_COMPLETED == retVal)
                {
                    /* Set RXFIFO Clear Bit */
                    fcrValue |= UART_FCR_RX_FIFO_CLEAR_MASK;

                    /* Write into FCR */
                    UARTFIFOCtrlRegWrite(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) fcrValue);
                }
            }
            else
            {
                retVal = IOM_EBADMODE;
            }
        }
        /*
         * ===================IOCTL_UART_CANCEL_CURRENT_IO=====================
         */
        else if (IOCTL_UART_CANCEL_CURRENT_IO == cmd)
        {
            /* Cancel the current IO on the channel                          */
            uartCancelCurrentIo(chanHandle, NULL);
        }
        /*
         * ======================IOCTL_UART_GET_STATS==========================
         */
        else if (IOCTL_UART_GET_STATS == cmd)
        {
            /* copy the statistics for the channel                           */
            *(Uart_Stats *) cmdArg = instHandle->stats;
        }
        /*
         * ==================IOCTL_UART_CLEAR_STATS============================
         */
        else if (IOCTL_UART_CLEAR_STATS == cmd)
        {
            /* clear the data statistics stored for the channel              */
            memset(
                (Void *) &instHandle->stats,
                (Int) 0x00,
                sizeof (Uart_Stats));
        }
        /*
         * ===============IOCTL_UART_SET_POLLEDMODETIMEOUT=====================
         */
        else if (IOCTL_UART_SET_POLLEDMODETIMEOUT == cmd)
        {
            /* Update the polledModeTimeout value                            */
            instHandle->polledModeTimeout = *((UInt32 *) cmdArg);
        }
        /*
         * ===============Uart_IOCTL_SET_ERRORCALLBACK=========================
         */
        else if (IOCTL_UART_SET_ERROR_CALLBACK == cmd)
        {
            hwiKey = Hwi_disable();

            /* To register a callback funtion for error notification         */
            chanHandle->gblErrCbkFxn =
                ((Uart_GblErrCbk *) cmdArg)->gblErrCbkFxn;
            chanHandle->gblErrCbkArg =
                ((Uart_GblErrCbk *) cmdArg)->gblErrCbkArg;

            Hwi_restore(hwiKey);
        }
        /*
         * ================IOCTL_UART_FLUSH_ALL_REQUEST========================
         */
        else if (IOCTL_UART_FLUSH_ALL_REQUEST == cmd)
        {
            /* flush all the requests queued up in the driver                */
            hwiKey = Hwi_disable();

            if (UART_OPMODE_DMAINTERRUPT != instHandle->opMode)
            {
                chanHandle->abortAllIo = (Bool) TRUE;
            }
            uartCancelAllIo((Uart_ChanObj *) chanHandle);

            Hwi_restore(hwiKey);
        }
        /*
         * ==================IOCTL_UART_GET_FIFO_STATUS========================
         */
        else if (IOCTL_UART_GET_FIFO_STATUS == cmd)
        {
            Uart_FifoStats *fifoStats = (Uart_FifoStats *) cmdArg;

            hwiKey = Hwi_disable();

            fifoStats->isFifoEmpty       = (Bool) FALSE;
            fifoStats->isTxShiftRegEmpty = (Bool) FALSE;
            fifoStats->fifoLevel         = 0U;

            lineStatus = UARTReadStatus(
                (UInt32) instHandle->deviceInfo.baseAddress);

            if (UART_OUTPUT == chanHandle->mode)
            {
                if ((lineStatus & UART_LSR_TX_FIFO_E_MASK) != 0U)
                {
                    fifoStats->isFifoEmpty = (Bool) TRUE;
                }
                if ((lineStatus & UART_LSR_TX_SR_E_MASK) != 0U)
                {
                    fifoStats->isTxShiftRegEmpty = (Bool) TRUE;
                }
                fifoStats->fifoLevel = UARTTxFIFOLevelGet(
                    (UInt32) instHandle->deviceInfo.baseAddress);
            }
            else if (UART_INPUT == chanHandle->mode)
            {
                if ((lineStatus & UART_LSR_RX_FIFO_E_MASK) != 0U)
                {
                    fifoStats->isFifoEmpty = (Bool) TRUE;
                }
                fifoStats->fifoLevel = UARTRxFIFOLevelGet(
                    (UInt32) instHandle->deviceInfo.baseAddress);
            }
            else
            {
                retVal = IOM_EBADMODE;
            }

            Hwi_restore(hwiKey);
        }
        else
        {
            /* unrecognised Ioctl is passed,hence status not implemented      */
            System_printf("\r\nuartMdControlChan: IOM_ENOTIMPL\r\n");
            retVal = IOM_ENOTIMPL;
        }
    }
    if  (IOM_COMPLETED != retVal)
    {
        retVal = IOM_EBADARGS;
    }
    return (retVal);
}

/* ========================================================================== */
/*                            LOCAL  FUNCTIONS                                */
/* ========================================================================== */

/**
 * \brief    This function implements the baud rate change IOCTL.
 *
 * \param    instHandle   [IN]    Pointer to the device Object
 * \param    cmdArgs      [IN]    Argument for the command.
 *
 * \return   IOM_COMPLETED                if success
 *           IOM_EBADARGS,IOM_EBADMODE    if failure
 *
 * \enter    instHandle must be valid pointer non NULL pointer
 *
 * \leave    Not Implemented.
 */
static Int32 uartBaudRateChangeIoctl(Uart_Object *instHandle, Ptr cmdArgs)
{
    Uart_BaudRate baudRate = UART_BAUDRATE_115_2K;
#ifdef BIOS_PWRM_ENABLE
    PWRM_Domain   domain   = PWRM_CPU;
    UInt32        setpoint = 0x00;
    UInt32        prescale = 0x00;
#endif
    Int32         status = IOM_COMPLETED;

    assert(NULL != cmdArgs);
    assert(NULL != instHandle);

    /* Perform error checking on baud rate                                    */
    baudRate = *((Uart_BaudRate *) cmdArgs);

    switch (baudRate)
    {
        case UART_BAUDRATE_2_4K:
        case UART_BAUDRATE_4_8K:
        case UART_BAUDRATE_9_6K:
        case UART_BAUDRATE_19_2K:
        case UART_BAUDRATE_38_4K:
        case UART_BAUDRATE_57_6K:
        case UART_BAUDRATE_115_2K:
        case UART_BAUDRATE_3686_4K:
            instHandle->devParams.baudRate = baudRate;
            uartSetBaudRate((Uart_Object *) instHandle, *(UInt32 *) cmdArgs);
            break;
        /* Note: Tested only upto this baud rate                          */
        default:
#ifdef BIOS_PWRM_ENABLE
            /* update the baudrate in to the instHandle                       */
            instHandle->devParams.baudRate = baudRate;

            /* unregister the old constraints                                 */
            status = UartUnregisterConstraints(instHandle);

            /* calculate the contraints for this new baudrate                 */
            status |= UartCalculateConstraints(instHandle);

            if (IOM_COMPLETED == status)
            {
                /* check what clock domain is supported by the device         */
                if (UART_PLLDOMAIN_0 != instHandle->pwrmInfo.pllDomain)
                {
                    domain = PWRM_PER;
                }

                /* get the information regarding the active set point         */
                if (PWRM_SOK == PWRM_getCurrentSetpoint(domain, &setpoint))
                {
                    status = UartCalculateClockSettings(
                        instHandle,
                        setpoint,
                        instHandle->devParams.baudRate,
                        &prescale);
                }
                else
                {
                    status = IOM_EBADMODE;
                }

                /* check if the calculation of new prescaler value for the new*
                 * baud rate is successful also check if the prescaler is     *
                 * within the permissible limits                              */
                if ((IOM_COMPLETED == status) &&
                    ((1 <= prescale) && (prescale <= 0xFFFFU)))
                {
                    /* calculation of the prescaler value is successful.Hence *
                     * update the hardware with the new prescaler values      */
                    status = UartConfigureNewClkSettings(instHandle, prescale);
                }
            }
#else
            /* Unsupported Baudrates */
            status = IOM_EBADARGS;
            System_printf("uartBaudRateChangeIoctl: Unsupported Baudrates");
            break;
#endif
    }
    return (status);
}

/**
 *
 *   This function is invoked in order for to register Uart interrupts
 *   with the requested interrupt handler with the OS (BIOS) and enables
 *   the interrupt.
 *
 *  \param    devp         [IN]    Pointer to the device
 *  \param    intNum       [IN]    interrupt number
 *  \param    evt          [IN]    event number
 *  \param    intIsr       [IN]    ISR function pointer
 *  \param    eb           [OUT]   error block pointer
 *
 *  \return   void
 *
 *  \enter    inDevp    must be valid pointer to Uart Obj & should not be null
 *            hwiNumber must be a valid hardware interrupt number
 *            evt       must be a valid event number
 *            intIsr    must be a valid pointer to ISR function and should
 *                      not be  null.
 *            eb        if null raise error and aborts the program, if not null
 *                      and valid raises error but shall allow continuation of
 *                      execution
 *
 *
 *
 *  \leave    Not Implemented.
 */
static Void uartRegisterInterrupt(Ptr             inDevp,
                                  UInt16          hwiNumber,
                                  UInt32          evt,
                                  Uart_pspUartIsr intIsr,
                                  Error_Block    *eb)
{
    Uart_Object  *instHandle = (Uart_Object *) inDevp;
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    Hwi_Params    hwiParams;
    Error_Block   ebl;
    static UInt32 cookie = 0;
#if defined (TI814x_M3) || defined (C6A811x_M3)
    UInt          intMuxNum = 0;
#else
    UInt32        tempCastIsr;
#endif
#else
    static UInt32 hwiKey = 0;
#endif

    assert(NULL != intIsr);
    assert(NULL != inDevp);
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)

    /* Initialize the Error Block                                             */
    Error_init(&ebl);

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    /* Initialize the HWI parameters with user specified values               */
    Hwi_Params_init(&hwiParams);

    /* argument to be passed to the ISR function                              */
    hwiParams.arg = (UArg) instHandle; /* Misra Pointer to Cast Waiver */

#if defined (TI814x_M3) || defined (C6A811x_M3)
    hwiParams.enableInt = (Bool) TRUE;

    if (TRUE == instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn)
    {
        /* (....intNumToBeMapped - CSL_INTMUX_OFFSET) gives the IntMux
         * number, which has to be mapped to the cross bar event.
         * Eg: if intNumToBeMapped = 42 (I2CINT1) then
         * (42 - CSL_INTMUX_OFFSET) becomes 19, which is nothing but the
         * int mux number. This int mux number (19) will be then mapped to
         * the cross bar event [Eg: Cross bar event for I2CINT2 is 04]
         */
        intMuxNum =
            (UInt32) ((UInt32) instHandle->deviceInfo.crossBarEvtParam.
                      intNumToBeMapped
                      - CSL_INTMUX_OFFSET);
        IntMux_setEvent(intMuxNum, evt);

        /* Create a corresponding interrupt handler. Notice that Ducati
         * interrupt number
         * (instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped)
         * corresponds to IntMux
         * ((instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped) -
         * CSL_INTMUX_OFFSET)
         */

        Hwi_construct(
            &instHandle->hwiStruct,
            (Int32) instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped,
            intIsr,
            &hwiParams, &ebl);
        instHandle->hwiHandle = Hwi_handle(&instHandle->hwiStruct);
    }
    else
    {
        Hwi_construct(&instHandle->hwiStruct, (Int32) evt, intIsr, &hwiParams,
                      &ebl);
        instHandle->hwiHandle = Hwi_handle(&instHandle->hwiStruct);
    }

#else

    tempCastIsr = (UInt32) intIsr;
    /* Misra Issue: Cast between func pointer and non-integral */
    Hwi_construct(&instHandle->hwiStruct, (Int32) evt,
                  (Hwi_FuncPtr) tempCastIsr, &hwiParams,
                  &ebl);
    instHandle->hwiHandle = Hwi_handle(&instHandle->hwiStruct);
#endif

    if ((Bool) TRUE == Error_check(&ebl))
    {
        System_printf("HWI Create Failed\r\n");
    }

    Hwi_enableInterrupt(evt);
    /* Restore interrupts */
    Hwi_restore(cookie);
#else

    hwiKey = (UInt32) Hwi_disable();

    EventCombiner_dispatchPlug(
        (UInt32) evt, (EventCombiner_FuncPtr) intIsr,
        (UArg) instHandle, (Bool) TRUE);
    /* Enabling the event                                                     */
    EventCombiner_enableEvent((UInt32) evt);

    /* Enabling the HWI_ID where corresponding ECM group is configured        */
    Hwi_enableInterrupt(hwiNumber);

    /* Enabling the interrupts                                                */
    Hwi_restoreInterrupt(hwiNumber, hwiKey);
#endif
}

/**
 * \brief    uartUnRegisterInterrupt
 *
 *           This function is invoked to unregister and disable interrupt
 *           handler and interrupt cause respectively.
 *
 * \param    instHandle  [IN]    Handle to the Uart driver Object
 * \param    intNum      [IN]    interrupt number
 * \param    evt         [IN]    event number
 *
 * \return   None
 *
 * \enter    intNum    must be a valid hardware interrupt number
 *           evt       must be a valid event number
 *
 * \leave    Not Implemented.
 */
static inline Void uartUnRegisterInterrupt(Uart_Object *instHandle,
                                           UInt16       hwiNumber,
                                           UInt32       evt)
{
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    Hwi_Struct *uartHwiStruct;
#endif
    assert(NULL != instHandle);

    /* done to remove compiler warning                                        */
    hwiNumber = hwiNumber;

#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    uartHwiStruct = Hwi_struct(instHandle->hwiHandle);
    Hwi_disableInterrupt(evt);

    Hwi_destruct(uartHwiStruct);

    if (uartHwiStruct != NULL)
    {
        memset(uartHwiStruct, 0, sizeof (Hwi_Struct));
    }
    instHandle->hwiHandle = NULL;
#else
    /* Disable the event                                                      */
    EventCombiner_disableEvent((UInt32) evt);
#endif
}

/**
 *  \brief   Perform read/write transfer
 *
 *           This function is called from ISR and Task context to do transfer
 *
 *  \param   chanHandle     [IN]     Handle to the channel
 *
 *  \return If successful, returns IOM_COMPLETED else PSP Error
 *
 *  \enter   chanHandle  must be a valid pointer and should not be null.
 *
 *  \leave   Not Implemented.
 *
 */
static Void uartIntrHandler(Uart_ChanObj *chanHandle)
{
    UInt32       xfer       = 0;
    IOM_Packet  *ioPacket   = NULL;
    Uart_Object *instHandle = NULL;
#ifdef BIOS_PWRM_ENABLE
    PWRM_Status  status = PWRM_SOK;
    UInt32       count  = 0x00;
#endif

    assert(NULL != chanHandle);
    instHandle = (Uart_Object *) (chanHandle->devHandle);
    assert(NULL != instHandle);

    /* If this is called from SWI(Tasklet) context                            */
    if (UART_OPMODE_INTERRUPT == instHandle->opMode)
    {
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
        Hwi_disableInterrupt(instHandle->deviceInfo.cpuEventNumber);
#else
        EventCombiner_disableEvent(
            (UInt32) instHandle->deviceInfo.cpuEventNumber);
#endif
    }

    ioPacket = chanHandle->activeIOP;

    if (NULL != ioPacket)
    {
        xfer = uartXfer(
            chanHandle,
            chanHandle->activeBuf,
            chanHandle->bytesRemaining,
            NULL);

        chanHandle->bytesRemaining -= xfer;
        chanHandle->activeBuf      += xfer;
        /* Misra C Waiver Reason
         * Pointer Arithmetic, xfer size is always less than or equal to
         * bytesRemaining
         * activeBuf starts with Application Buffer, bytesRemaining starts with
         * App Buffer Size
         * Hence the pointer arithmetic operations are within this limit
         * Application needs to send proper buffer size
         */
        if (UART_INPUT == chanHandle->mode)
        {
            instHandle->stats.rxBytes += xfer;
            /* Re-enable the interrupt here, because it was disabled in ISR   *
             * before posting the SWI. This interrupt will be aprropriately   *
             * disabled below                                                 */
            if ((UART_OPMODE_POLLED != instHandle->opMode) &&
                (0 != chanHandle->bytesRemaining))
            {
                UARTIntEnable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) UART_INTR_RHR);
            }
        }
        else
        {
            instHandle->stats.txBytes += xfer;
            /* Re-enable the interrupt here, because it was disabled in ISR   *
             * before posting the SWI. This interrupt will be aprropriately   *
             * disabled below                                                 */
            if ((UART_OPMODE_POLLED != instHandle->opMode) &&
                (0 != chanHandle->bytesRemaining))
            {
                UARTIntEnable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) UART_INTR_THR);
            }
        }

        if ((0 == chanHandle->bytesRemaining) &&
            (TRUE != chanHandle->abortAllIo))
        {
            if (UART_INPUT == chanHandle->mode)
            {
                if (UART_OPMODE_POLLED != instHandle->opMode)
                {
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_RHR);
                }
            }
            else
            {
                if (UART_OPMODE_POLLED != instHandle->opMode)
                {
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_THR);
                }
            }

            /* Get next IOP from RX pending list - do this before             *
             * notifyCompletion is called as it will manipulate the           *
             * next and prev pointers of iop disturbing the pending list      */
            if (0 != chanHandle->errors)
            {
                ioPacket->status = IOM_EBADIO;
            }
            else
            {
                ioPacket->status = IOM_COMPLETED;
            }

            /* Perform the operation to complete the IO                       */
            Uart_localCompleteCurrentIO(chanHandle);

#ifdef BIOS_PWRM_ENABLE
            if (FALSE == instHandle->pwrmInfo.ioSuspend)
            {
#endif
            Uart_loadPendedIops(chanHandle);
#ifdef BIOS_PWRM_ENABLE
        }
        else
        {
            if (TRUE == instHandle->devParams.prcmPwrmEnable)
            {
                /* set the current active IOP as NULL                     */
                chanHandle->activeIOP = NULL;
                instHandle->devState  = UART_DRIVERSTATE_PWRM_SUSPEND;

                if ((NULL == instHandle->rcvChanObj.activeIOP) &&
                    (NULL == instHandle->xmtChanObj.activeIOP))
                {
                    /* if both the channels are inactive then reset the   *
                     * io suspend flag                                    */
                    instHandle->pwrmInfo.ioSuspend = FALSE;

                    if ((PWRM_GOINGTOSLEEP ==
                         instHandle->pwrmInfo.pwrmEvent) ||
                        (PWRM_GOINGTODEEPSLEEP ==
                         instHandle->pwrmInfo.pwrmEvent))
                    {
                        /* reduce the dependency count                    */
                        status =
                            PWRM_getDependencyCount(
                                (PWRM_Resource) instHandle->deviceInfo.
                                pwrmPrcmId,
                                &count);

                        instHandle->pwrmInfo.dependencyCount = count;

                        if (PWRM_SOK == status)
                        {
                            while (count > 0)
                            {
                                status =
                                    PWRM_releaseDependency(
                                        (PWRM_Resource)
                                        instHandle->
                                        deviceInfo.pwrmPrcmId);

                                if (PWRM_SOK != status)
                                {
                                    break;
                                }
                                count--;
                            }
                        }
                    }
                    /* call the delayed completion function               */
                    (instHandle->pwrmInfo.delayedCompletionFxn \
                     [instHandle->pwrmInfo.pwrmEvent])();
                }
            }
        }
#endif
        }
        /* for bytesRemaining equals to Zero
         *                                */
    }
    /* iop NULL condition
     *                                                   */

    /* If this is called from SWI(Tasklet) context                            */
    if (UART_OPMODE_INTERRUPT == instHandle->opMode)
    {
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
        Hwi_enableInterrupt(instHandle->deviceInfo.cpuEventNumber);
#else
        EventCombiner_enableEvent(instHandle->deviceInfo.cpuEventNumber);
#endif
    }
}

#ifndef BIOS_PWRM_ENABLE
/**
 *  \brief   interface for configuring the Uart controller for a specific baud
 *           rate of operation
 *
 * \param  instHandle  [IN]   Uart driver structure
 * \param  baudRAte    [IN]   The baud rate to be configured.
 *
 * \return None
 *
 * \enter   instHandle  must be a valid pointer and should not be null.
 *          baudRate    must be a valid baudRate value.
 *
 * \leave   Not Implemented.
 */
static Void uartSetBaudRate(const Uart_Object *instHandle, UInt32 baudRate)
{
    UInt32 value = 0;

    assert(NULL != instHandle);

    value = (UInt32) ((instHandle->deviceInfo.inputFrequency) /
                      (UInt32) ((UInt32) BSP_UART_BAUD_MULTIPLIER *
                                (UInt32) baudRate));
    /* Enables mode B to access the DLL and DLH registres                     */
    UARTDivisorLatchWrite(
        (UInt32) instHandle->deviceInfo.baseAddress,
        (UInt32) value);
}

#endif

/**
 *  \brief Configure Uart device HW
 *
 *   This function is used to set up the hardware for the current settings
 *  "param" points to the hardware config and other open params.
 *
 *  \param  instHandle    [IN]   Handle to the Uart driver object
 *  \param  openParams    [IN]   Parameters passed by the user
 *  \param  eb            [OUT]  Pointer to error block
 *
 *  \return IOM_COMPLETED in case of sucess or
 *          E_badArgs in case of error
 *
 *  \enter  instHandle must be a valid pointer and should not be null.
 *          openParams must be a valid pointer and should not be null.
 *          eb         if null raise error and aborts the program, if not null
 *                     and valid raises error but shall allow continuation of
 *                     execution
 *
 *  \leave  Not Implemented.
 */
static Void uartConfigure(Uart_Object          *instHandle,
                          const Uart_DevParams *openParams,
                          Error_Block          *eb)
{
    UInt32 operMode = 0;

    assert(NULL != instHandle);

    assert(NULL != openParams);

    /* Switch to mode B to access EFR                                         */
    /* Set the ENHANCEDEN Bit Field to Enable access to the MCR & IER reg     */
    /* Setting the EFR[4] bit to 1. */
    UARTEnhanFuncEnable((UInt32) instHandle->deviceInfo.baseAddress);

    /* Force LCR[6] to zero, to avoid UART breaks and LCR[7] to zero to access*
     * MCR reg */
    UARTRegConfModeRestore((UInt32) instHandle->deviceInfo.baseAddress,
                           (UInt32) 0x00U);

    /* RESET MCR Reg                                                          */
    UARTModemControlReset((UInt32) instHandle->deviceInfo.baseAddress);

    /* Disable all interrupts                                                 */
    UARTIntDisable((UInt32) instHandle->deviceInfo.baseAddress,
                   (UInt32) 0xFFU);

    /* Put the module in Disable State                                        */
    operMode = UARTOperatingModeSelect(
        (UInt32) instHandle->deviceInfo.baseAddress,
        (UInt32) UART_DISABLED_MODE);

    /* Reset Uart and setup hardware params                                   */
    UARTModuleReset((UInt32) instHandle->deviceInfo.baseAddress);

    /* Configuring UART in 13x(Zebu)/16x(Silicon) Mode */
    operMode = UARTOperatingModeSelect(
        (UInt32) instHandle->deviceInfo.baseAddress,
        (UInt32) UART_OPER_MODE);

    operMode = operMode; /* Done to avoid compiler warnings */

    instHandle->devParams.fifoEnable = openParams->fifoEnable;

    uartHwSetup(instHandle, &instHandle->devParams);

    /* If the set parameters set the HW Flowcontrol                           */
    if (UART_FCTYPE_HW == openParams->fc.fcType)
    {
        /* Enable HW flow control                                             */
        if ((UART_FCPARAM_AUTO_CTS == openParams->fc.fcParamTx)
            && (UART_FCPARAM_AUTO_RTS != openParams->fc.fcParamRx))
        {
            UARTAutoRTSAutoCTSControl(
                (UInt32) instHandle->deviceInfo.baseAddress,
                UART_AUTO_CTS_ENABLE,
                UART_AUTO_RTS_DISABLE);
        }
        else /* Auto RTS and auto CTS
              *                                            */
        {
            UARTAutoRTSAutoCTSControl(
                (UInt32) instHandle->deviceInfo.baseAddress,
                UART_AUTO_CTS_ENABLE,
                UART_AUTO_RTS_ENABLE);
        }
    }

    /* Enable Loopback                                                        */
    if ((Bool) TRUE == openParams->loopbackEnabled)
    {
        UARTLoopbackModeControl(
            (UInt32) instHandle->deviceInfo.baseAddress,
            (UInt32) UART_LOOPBACK_MODE_ENABLE);
    }
}

/**
 *  \brief    Validating Parameters passed to the Uart
 *
 *   This function is invoked in order to statically validate the
 *   various parameters passed to the Uart like baud Rate,Stop Bits,etc.
 *
 *  \param    instHandle   [IN]    Pointer to the Uart driver object
 *  \param    openParams   [IN]    Parameters passed to be vaildated
 *  \param    eb           [OUT]   pointer to error block
 *
 *  \return
 *            IOM_COMPLETED   if success
 *            Error ID  in case of error
 *
 *  \enter    instHandle must be a valid pointer and should not be null.
 *            openParams must be a valid pointer and should not be null.
 *            eb         if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
#ifndef PSP_DISABLE_INPUT_PARAMETER_CHECK
static Int32 uartValidateParams(const Uart_Params *openParams,
                                Error_Block       *eb)
{
    Int32 retVal = IOM_COMPLETED;
    assert(NULL != openParams);

    /* operational mode verification                                          */
    switch (openParams->opMode)
    {
        case UART_OPMODE_POLLED:
        case UART_OPMODE_INTERRUPT:
        case UART_OPMODE_DMAINTERRUPT:
            break;
        default:
            retVal = IOM_EBADARGS;
            break;
    }

    /* Get the stop bits from user configuration                              */
    switch (openParams->stopBits)
    {
        case UART_NUMSTOPBITS_1:
        case UART_NUMSTOPBITS_1_5:
        case UART_NUMSTOPBITS_2:
            break;

        default:
            retVal = IOM_EBADARGS;
            break;
    }

    /* Get the char len from user configuration                               */
    switch (openParams->charLen)
    {
        case UART_CHARLEN_5:
        case UART_CHARLEN_6:
        case UART_CHARLEN_7:
        case UART_CHARLEN_8:
            break;

        default:
            retVal = IOM_EBADARGS;
            break;
    }

    /* Get the parity from user configuration                                 */
    switch (openParams->parity)
    {
        case UART_PARITY_ODD:
        case UART_PARITY_EVEN:
        case UART_PARITY_FORCED0:
        case UART_PARITY_FORCED1:
        case UART_PARITY_NO:
            break;

        default:
            retVal = IOM_EBADARGS;
            break;
    }

    /* Update baud rate                                                       */
    switch (openParams->baudRate)
    {
        case UART_BAUDRATE_2_4K:
        case UART_BAUDRATE_4_8K:
        case UART_BAUDRATE_9_6K:
        case UART_BAUDRATE_19_2K:
        case UART_BAUDRATE_38_4K:
        case UART_BAUDRATE_57_6K:
        case UART_BAUDRATE_115_2K:
        case UART_BAUDRATE_3686_4K:
            /* Note: Tested upto this baudrate */
            break;
        default:
            retVal = IOM_EBADARGS;
            break;
    }

    /* Update receive threshold                                               */
    switch (openParams->rxThreshold)
    {
        case UART_RXTRIGLVL_8:
        case UART_RXTRIGLVL_16:
        case UART_RXTRIGLVL_56:
        case UART_RXTRIGLVL_60:
            break;
        default:
            retVal = IOM_EBADARGS;
            break;
    }

    /* Update Transmit threshold                                              */
    switch (openParams->txThreshold)
    {
        case UART_TXTRIGLVL_8:
        case UART_TXTRIGLVL_16:
        case UART_TXTRIGLVL_32:
        case UART_TXTRIGLVL_56:
            break;
        default:
            retVal = IOM_EBADARGS;
            break;
    }

    if ((0U == openParams->chunkSize) ||
        (openParams->chunkSize > BSP_UART_FIFO_SIZE))
    {
        retVal = IOM_EBADARGS;
    }

    return (retVal);
}

#endif

/**
 * \brief   Initialize the Uart device by setting the hardware registers
 *
 * \param   instHandle      [IN]     Handle to the Uart driver object
 * \param   currentParams   [IN]     Pointer for the Hardware configuration
 *
 * \return  Void
 *
 * \enter   instHandle    must be a valid pointer and should not be null.
 *          currentParams must be a valid pointer and should not be null.
 *
 * \leave   Not Implemented.
 */
static Void uartHwSetup(const Uart_Object    *instHandle,
                        const Uart_DevParams *currentParams)
{
    Int32 retVal;
    UInt32 regVal = 0x00;
    UInt32 divVal = 0x00;
#ifdef BIOS_PWRM_ENABLE
    Uns setpoint       = 0x00;
    PWRM_Domain domain = PWRM_CPU;
#endif

    assert(NULL != instHandle);
    assert(NULL != currentParams);

#ifdef BIOS_PWRM_ENABLE
    if (TRUE == instHandle->devParams.prcmPwrmEnable)
    {
        /* check what clock domain is supported by the device                 */
        if (UART_PLLDOMAIN_0 != instHandle->pwrmInfo.pllDomain)
        {
            domain = PWRM_PER;
        }

        retVal = (Int32) PWRM_getCurrentSetpoint(domain, &setpoint);

        if (PWRM_SOK == retVal)
        {
            retVal = UartCalculateClockSettings(
                instHandle,
                setpoint,
                currentParams->baudRate,
                &divVal);
        }
    }
    else
    {
#endif
    /* get the divisor  */
    divVal = (UInt32) (instHandle->deviceInfo.inputFrequency /
                       ((UInt32) BSP_UART_BAUD_MULTIPLIER *
                        (UInt32) currentParams->baudRate));

#ifdef BIOS_PWRM_ENABLE
}

#endif

    /********************** FIFOs and DMA Settings ****************************/

    UARTFIFOCtrlRegWrite((UInt32) instHandle->deviceInfo.baseAddress,
                         (UInt32) 0x00U);

    regVal = 0;

    if (TRUE == currentParams->fifoEnable)
    {
        Uart_TrigLvl trigLevel;

        trigLevel.txTrigLvl = currentParams->txThreshold;
        trigLevel.rxTrigLvl = currentParams->rxThreshold;

        /* Make FCR value */
        retVal = Uart_localMakeFCR(instHandle, &trigLevel, &regVal);
        assert(IOM_COMPLETED == retVal);

        regVal |= UART_FCR_TX_FIFO_CLEAR_MASK;
        regVal |= UART_FCR_RX_FIFO_CLEAR_MASK;
    }

    if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
    {
        regVal |= UART_FCR_DMA_MODE_MASK;
    }

    UARTFIFOCtrlRegWrite((UInt32) instHandle->deviceInfo.baseAddress,
                         (UInt32) regVal);

    /*************** Protocol, Baud Rate, and Interrupt Settings **************/

    /* Configure the Line control parameters and put the module in general    *
     * access mode
     *                                                               */
    regVal = 0;
    regVal = ((UInt32) currentParams->charLen
              | (UInt32) currentParams->stopBits
              | (UInt32) currentParams->parity);

    UARTRegConfModeRestore((UInt32) instHandle->deviceInfo.baseAddress,
                           (UInt32) regVal);

    /* Switch to register configuration mode B to access the DLL & DLH reg    */
    /* Load the new divisor value                                             */
    UARTDivisorLatchWrite((UInt32) instHandle->deviceInfo.baseAddress,
                          (UInt32) divVal);

    /* Disables writing to IER bits 4-7, FCR bits 4-5, and MCR bits 5-7       */
    /* Restrore back the LCR Value                                            */
    UARTRegConfigModeEnable((UInt32) instHandle->deviceInfo.baseAddress,
                            UART_REG_OPERATIONAL_MODE);
}

/**
 *  \brief   This function writes a byte to the Uart device
 *
 *  \param   instHandle  [IN]     Handle to the Uart driver Object
 *
 *  \return  Data read is returned
 *
 *  \enter   instHandle must be a valid pointer and should not be null.
 *
 *  \leave   Not Implemented.
 */
static inline UInt8 uartReadByte(Uart_Object *instHandle)
{
    Int8 rbr = 0;
    volatile UInt32 waitCount = BSP_UART_ERROR_COUNT;
    UInt32 err;

    assert(NULL != instHandle);

    err = UARTRxErrorGet(
        (UInt32) (instHandle->deviceInfo.baseAddress));
    /* Read and throw Erroneous bytes from RxFIFO                             */
    while (0U != err)
    {
        rbr = UARTFIFOCharGet((UInt32) (instHandle->deviceInfo.baseAddress));
        instHandle->stats.rxFramingError++;
        instHandle->rcvChanObj.errors++;
        waitCount--;

        err = UARTRxErrorGet(
            (UInt32) (instHandle->deviceInfo.baseAddress));
        if (0U == waitCount)
        {
            break;
        }
    }
    /* Read non-erroneous byte from RxFIFO                                    */
    rbr = UARTFIFOCharGet((UInt32) (instHandle->deviceInfo.baseAddress));

    return (UInt8) rbr;
}

/**
 *  \brief   This function writes a byte to the Uart device
 *
 * \param   instHandle  [IN]     Handle to the Uart driver Object
 * \param   data        [IN]     data to be written to the device
 *
 * \return  None
 *
 * \enter   instHandle must be a valid pointer and should not be null.
 *          data       must be a valid data value.
 *
 * \leave   Not Implemented.
 */
static inline Void uartWriteByte(const Uart_Object *instHandle, Char data)
{
    assert(NULL != instHandle);
    UARTFIFOCharPut(
        (UInt32) (instHandle->deviceInfo.baseAddress),
        (UInt8) data);
}

/**
 *  \brief    Getting the line status for errors or data ready
 *
 *  \param    instHandle [IN]  pointer to Uart driver object
 *
 *  \return   value of the lins status register
 *
 *  \enter    instHandle must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 *
 */
static inline UInt32 uartGetLineStatus(Uart_Object const *instHandle)
{
    UInt32 regVal = 0;

    assert(NULL != instHandle);
    regVal = (UInt32) UARTReadStatus(
        (UInt32) instHandle->deviceInfo.baseAddress);
    return regVal;
}

/**
 *  \brief   checks if a timeout has happened from the given time.
 *
 *  This function checks if the timeout with respect to the start time has
 *  occured. The timeout and the start time is also input to the function.
 *
 * \param   startValue  [IN]   Start value
 * \param   timeout     [IN]   Timeout value
 *
 * \return  TRUE   if time out occured.
 *          FALSE  if time out has not occured.
 *
 * \enter   startValue  must be a valid start value
 *          timeout     must be a valid timeout value
 *
 * \leave   Not Implemented.
 *
 */
static Bool uartOsCheckTimeOut(UInt64 startValue, UInt32 timeout)
{
    UInt64 checkValue;
    Bool retVal = (Bool) TRUE;

    /* get the current tick value and compare with the start value            */
    checkValue = BspOsal_getTimestamp64();

    if (checkValue < startValue)
    {
        checkValue =
            (UInt64) ((BSP_UART_OS_CHECKTIMEOUT_COUNT_VALUE - startValue)
                      + checkValue) + (UInt64) (1U);
    }
    else
    {
        checkValue = checkValue - startValue;
    }

    /* if the difference between the current tick and start tick is greater   *
     * than start tick then set retval to TRUE to indicate time out           */
    if ((checkValue < timeout) ||
        (BSP_UART_TIMEOUT_WAIT_FOREVER == timeout))
    {
        retVal = (Bool) FALSE;
    }
    else
    {
        retVal = (Bool) TRUE;
    }

    return retVal;
}

/**
 *  \brief   Read/Write operation are performed in polled mode
 *
 *  This function performs the read/write operation as requested by the
 *  application in the submitted io packet. it submits the packets in the
 *  POLLED mode.
 *
 *  \param  chanHandle  [IN]  Handle to the Channel
 *  \param  ioPacket    [IN]  Packet passed by the stream layer
 *  \param  eb          [OUT] pointer to the error block
 *
 *  \return If successful, returns IOM_COMPLETED else Error id
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          ioPacket     must be a valid pointer and should not be null.
 *          eb           if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
static Int32 uartSubmitIoReqPolled(Uart_ChanObj *chanHandle,
                                   IOM_Packet   *ioPacket,
                                   Error_Block  *eb)
{
    Int32 retVal      = IOM_COMPLETED;
    UInt32 lineStatus = 0;
    UInt64 currentTick;
    Bool timeoutElapsed       = FALSE;
    Uart_Object   *instHandle = NULL;

    assert(NULL != chanHandle);
    assert(NULL != ioPacket);

    /* Get the handle to the instance    */
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    /* This submit does not allow a second request (from different            *
     * task ) when we are in polled mode                                      */
    if (NULL != chanHandle->activeIOP)
    {
        /* already an active iop is present hence cannot queue another        *
         * request in polled mode                                             */
        ioPacket->status = IOM_EBADIO;
        ioPacket->size   = 0;
        retVal           = IOM_EBADIO;
    }
    else
    {
        /* No active iop hence can queue our request                          */
        chanHandle->errors         = 0;
        chanHandle->activeIOP      = ioPacket;
        chanHandle->activeBuf      = (UInt8 *) ioPacket->addr;
        chanHandle->bytesRemaining = ioPacket->size;
        retVal = IOM_EBADIO;

        /* Update current tick value to perform timeout operation             */
        currentTick = BspOsal_getTimestamp64();
        while ((FALSE == timeoutElapsed)
               && (0 != chanHandle->bytesRemaining))
        {
            /* This is a common func where we transfer DATA                   */
            uartIntrHandler(chanHandle);
            /* Check whether timeout happened or not                          */
            timeoutElapsed =
                uartOsCheckTimeOut(currentTick, instHandle->polledModeTimeout);

            /* sleep only if in a task context and not in SWI or HWI          */
            if (BIOS_ThreadType_Task == BIOS_getThreadType())
            {
                Task_sleep((UInt32) BSP_UART_TPOLL_MSECS);
            }
        }

        if ((0 == chanHandle->bytesRemaining)
            && (0 == chanHandle->errors))
        {
            do
            {
                lineStatus = (UInt32) uartGetLineStatus(instHandle);
            }
            while ((UInt32) (UART_LSR_TX_FIFO_E_MASK |
                             UART_LSR_TX_SR_E_MASK) !=
                   (lineStatus & (UInt32) (UART_LSR_TX_FIFO_E_MASK |
                                           UART_LSR_TX_SR_E_MASK)));

            retVal = IOM_COMPLETED;
        }

        if ((Bool) TRUE == timeoutElapsed)
        {
            /* Return IOM completed so that application gets whatever bytes are
             * received. Set the IO packet status as timeout so that
             * application can handle the timeout value returned by
             * GIO submit */
            retVal           = IOM_COMPLETED;
            ioPacket->status = IOM_ETIMEOUT;
            ioPacket->size   = ioPacket->size - chanHandle->bytesRemaining;

            /* Perform the operation to complete the IO
             *                          */
            Uart_localCompleteCurrentIO(chanHandle);
        }
    }

    return retVal;
}

/**
 *  \brief   Read/Write operation are performed in polled mode
 *
 *  This function performs the read/write operation as requested by the
 *  application in the submitted io packet. It submits the packets in the
 *  interrupt or DMA mode without buffering enabled.
 *
 *  \param  chanHandle  [IN]  Handle to the Channel
 *  \param  ioPacket    [IN]  Packet passed by the stream layer
 *  \param  hwiKey      [IN]  value required for restoring interrupts
 *  \param  eb          [OUT] pointer to the error block
 *
 *  \return If successful, returns IOM_COMPLETED else Error id
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          ioPacket     must be a valid pointer and should not be null.
 *          hwiKey       must be a valid hwiKey value.
 *          eb           if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
static Int32 uartSubmitIoReqIntDma(Uart_ChanObj *chanHandle,
                                   IOM_Packet   *ioPacket,
                                   UInt32        hwiKey,
                                   Error_Block  *eb)
{
    Int32 retVal = IOM_COMPLETED;
    Uart_Object   *instHandle = NULL;
    Void *tempQueueCastPacket;
    assert(NULL != chanHandle);
    assert(NULL != ioPacket);

    /* get the handle the instance                                            */
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    /* To remove the compiler warning                                         */
    hwiKey = hwiKey;

    /* If not in polled mode,then it may be in INT or DMA mode.               *
     * Disable the interrupts.Check if any IOP is active, if yes              *
     * check if the new IOP has a timeout value. If not then post             *
     * an error. else enque the iop into the list and return back.Also check  *
     * if the driver is in power saving state                                 */
    if ((NULL != chanHandle->activeIOP) ||
        (UART_DRIVERSTATE_PWRM_SUSPEND == instHandle->devState))
    {
        tempQueueCastPacket = (Void *) ioPacket;
        /* Queue it and update the return value                               */
        Queue_put(Queue_handle(&(chanHandle->queuePendingList)),
                  (Queue_Elem *) tempQueueCastPacket); /* Misra CAST.PTR */
        ioPacket->status = IOM_PENDING;
        retVal           = IOM_PENDING;
    }
    else
    {
        /* No other IOP is active, We can process this IOP, set               *
         * it as active IOP                                                   */
        chanHandle->activeIOP      = ioPacket;
        chanHandle->activeBuf      = (UInt8 *) ioPacket->addr;
        chanHandle->bytesRemaining = ioPacket->size;
        chanHandle->errors         = 0;

        /* Enable Interrupt before Edma Transfer to avoid Timing issue between
         * the data transmission and interrupt enable. In UARTIntEnable Hal,
         * The upper 4 bits of IER is only written after EFR[4] is set, So
         * switching b/w the
         * modes and writing in to the registers is happening, whereas it is not
         * required while writing it to lower 4 bits of IER. So, It is suggested
         * to call UARTIntEnable hal befor edma Transfer fxn being called
         */
        if (UART_OPMODE_DMAINTERRUPT != instHandle->opMode)
        {
            if (UART_INPUT == chanHandle->mode)
            {
                UARTIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) UART_INTR_RHR);
            }
            else
            {
                UARTIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) UART_INTR_THR);
            }
        }
        else
        {
            /* In case of DMA mode enable line status interrupt only to handle
             * RX errors */
            if (UART_INPUT == chanHandle->mode)
            {
                UARTIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) UART_INTR_RLS);
            }
        }

        if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
        {
            /* If DMA mode then start the DMA                                 */
            retVal = Uart_localStartEdmaTransfer(
                chanHandle,
                (UInt32) ioPacket->cmd,
                NULL);
        }
        if  (IOM_COMPLETED == retVal)
        {
            retVal = IOM_PENDING;
        }
    }
    /* end of buffer mode check
     *                                              */

    return retVal;
}

/**
 *  \brief   Read/Write operation are performed
 *
 *  This function performs the read/write operation as requested by the
 *  application in the submitted io packet. it can operate in POLLED and
 *  INTERRUPT and DMA modes.
 *
 *  \param  chanHandle  [IN]  Handle to the Channel
 *  \param  ioPacket    [IN]  Packet passed by the stream layer
 *  \param  eb          [OUT] pointer to the error block
 *
 *  \return If successful, returns IOM_COMPLETED else IOM_EBADIO
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          ioPacket     must be a valid pointer and should not be null.
 *          eb           if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
static Int32 uartSubmitIoReq(Uart_ChanObj *chanHandle,
                             IOM_Packet   *ioPacket,
                             Error_Block  *eb)
{
    Int32 retVal = IOM_COMPLETED;
    Uart_Object  *instHandle = NULL;
    /* Validating all the input parameters inputs                             */
    assert(NULL != chanHandle);
    assert(NULL != ioPacket);

    /* get the handle the instance                                            */
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    /* If polled mode is set with the active iop as the received iop call     *
     * the function "uartRxIntrHandler" where the control will block          *
     * till it gets the requested number of bytes.                            */
    if (UART_OPMODE_POLLED == instHandle->opMode)
    {
        if (UART_DRIVERSTATE_PWRM_SUSPEND != instHandle->devState)
        {
            /* we will protect this function with a semaphore because in case *
             * of multiple tasks submitting the IO requests we will be running*
             * in to race conditions hence in polled mode we will only allow  *
             * only one task to complete the request in polled mode. and the  *
             * other task will be pending on the semaphore.(until the first   *
             * task has completed the IO). We need to have seperate protection *
             * for both read and write as hardware is capable of servicing read
             * and write independently as it have different buffer for TX
             * and RX otherwise read would block. Write and vice versa.
             * Hence provided semaphore protection for read and write
             * independently
             */
            if (IOM_READ == ioPacket->cmd)
            {
                Semaphore_pend(
                    Semaphore_handle(&(instHandle->readSyncSem)),
                    (UInt32) BIOS_WAIT_FOREVER);
            }
            else if (IOM_WRITE == ioPacket->cmd)
            {
                Semaphore_pend(
                    Semaphore_handle(&(instHandle->writeSyncSem)),
                    (UInt32) BIOS_WAIT_FOREVER);
            }
            else
            {
                retVal = IOM_EBADMODE;
            }

            if (IOM_COMPLETED == retVal)
            {
                retVal = uartSubmitIoReqPolled(chanHandle, ioPacket, NULL);

#ifdef BIOS_PWRM_ENABLE
                if (((Bool) TRUE == instHandle->devParams.prcmPwrmEnable) &&
                    ((Bool) TRUE == instHandle->pwrmInfo.ioSuspend))
                {
                    /* set the current active IOP as NULL */
                    chanHandle->activeIOP = NULL;

                    /* set the driver state as suspended to prevent any new IOP
                     *from getting loaded */
                    instHandle->devState = UART_DRIVERSTATE_PWRM_SUSPEND;

                    if ((NULL == instHandle->rcvChanObj.activeIOP) &&
                        (NULL == instHandle->xmtChanObj.activeIOP))
                    {
                        /* if both the channels are inactive then reset the io
                         *suspend flag */
                        instHandle->pwrmInfo.ioSuspend = (Bool) FALSE;

                        /* call the delayed completion function */
                        (instHandle->pwrmInfo.delayedCompletionFxn \
                         [instHandle->pwrmInfo.pwrmEvent])();
                    }
                }
#endif
                /* we have completed the IO processing hence post  semaphore */
                if (IOM_READ == ioPacket->cmd)
                {
                    Semaphore_post(Semaphore_handle(&(instHandle->
                                                      readSyncSem)));
                }
                else if (IOM_WRITE == ioPacket->cmd)
                {
                    Semaphore_post(Semaphore_handle(&(instHandle->
                                                      writeSyncSem)));
                }
                else
                {
                    retVal = IOM_EBADMODE;
                }
            }
        }
        else
        {
            /* Driver is in power saving mode and cannot accept new IOs */
            System_printf("uartSubmitIoReq: Uart_E_EBADMODE");
            retVal = IOM_EBADMODE;
        }
    }
    else
    {
        UInt32 hwiKey = 0;

        /* interrupt mode of operation                                        */
        /* disable the interrupts                                             */
        hwiKey = (UInt32) Hwi_disable();
        retVal = uartSubmitIoReqIntDma(chanHandle, ioPacket, hwiKey, NULL);
        Hwi_restore(hwiKey);
    }
    return retVal;
}

/**
 *  \brief   Cancels the current ioo transaction on the channel
 *
 *   Cancel IO function - cancels the current request only.
 *   Used for canceling the request incase of an Timeout
 *
 *  \param  chanHandle  [IN]    Handle to the Channel
 *  \param  ioPacket    [IN]    Stream IO Packet to be completed
 *
 *  \return None
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          ioPacket     must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 *
 */
static Void uartCancelCurrentIo(Uart_ChanObj *chanHandle,
                                IOM_Packet   *ioPacket)
{
    UInt32 hwiKey           = 0;
    Uart_Object *instHandle = NULL;
    Void *ioCastPacket;

    assert(NULL != chanHandle);
    assert((NULL != chanHandle->devHandle));
    instHandle = (Uart_Object *) chanHandle->devHandle;

    /* Protect from Uart interrupt and task switching so that                 *
     * the process of cancellation is not interrupted                         */
    hwiKey = Hwi_disable();

    /* if iop passed is null the update iop with active iop which is to       *
     * be cancelled                                                           */
    if (NULL == ioPacket)
    {
        ioPacket = chanHandle->activeIOP;
    }

    if (chanHandle->activeIOP == ioPacket)
    {
        /* Current IOP                                                        */
        if (NULL != chanHandle->activeIOP)
        {
            chanHandle->bytesRemaining = 0;

            if (UART_INPUT == chanHandle->mode)
            {
                ((Uart_Object *) chanHandle->devHandle)->stats.rxBytes
                    += ioPacket->size;
            }
            else
            {
                ((Uart_Object *) chanHandle->devHandle)->stats.txBytes
                    += ioPacket->size;
            }

            ioPacket->status = IOM_ABORTED;
            Uart_localCompleteCurrentIO(chanHandle);

            if (FALSE ==
                Queue_empty(Queue_handle(&(chanHandle->queuePendingList))))
            {
                /* The last Active IOP got completed, so need                 *
                 * to modify this pointer                                     */
                ioPacket =
                    (IOM_Packet *) Queue_get(Queue_handle(&(chanHandle->
                                                            queuePendingList)));

                chanHandle->activeIOP      = ioPacket;
                chanHandle->activeBuf      = (UInt8 *) ioPacket->addr;
                chanHandle->bytesRemaining = (Int) ioPacket->size;
                chanHandle->errors         = 0;
            }
            else
            {
                chanHandle->activeIOP = NULL;

                Uart_localPrcmOn(instHandle, NULL);

                if (UART_INPUT == chanHandle->mode)
                {
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_RHR);
                }
                else
                {
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_THR);
                }

                Uart_localPrcmOff(instHandle, NULL);
            }
        }
    }
    else
    {
        ioCastPacket = (Void *) ioPacket;
        Queue_remove((Queue_Elem *) ioCastPacket); /* MISRA CST.PTR */
    }
    Hwi_restore(hwiKey);
}

/**
 *  \brief Cancels all iops in the tx/rx channel
 *
 *   This function cancels all the request pending with the Channel.
 *
 *  \param  chanHandle   [IN]   Handle to the Channel Object
 *
 *  \return None
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Void uartCancelAllIo(Uart_ChanObj *chanHandle)
{
    IOM_Packet          *ioPacket   = NULL;
    Uart_Object         *instHandle = NULL;

    /* validate params                                                        */
    assert(NULL != chanHandle);
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    ioPacket = chanHandle->activeIOP;

    if (NULL != ioPacket)
    {
        /* active IOP is present.Hence we will abort the same here            */
        if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
        {
            UInt32 localcCnt = 0;
            UInt32 localbCnt = 0;
            UInt32 localaCnt = 0;

            /* we will disable the edma transfer because a transfer might be  *
             * in progress                                                    */
            EDMA3_DRV_disableTransfer(
                (EDMA3_DRV_Handle) chanHandle->hEdma,
                chanHandle->edmaChId,
                EDMA3_DRV_TRIG_MODE_EVENT);

            /* Get the current value of counts for the actual data transfered */
            EDMA3_DRV_getPaRAMField(
                (EDMA3_DRV_Handle) chanHandle->hEdma,
                chanHandle->edmaChId,
                EDMA3_DRV_PARAM_FIELD_CCNT,
                &localcCnt);

            EDMA3_DRV_getPaRAMField(
                (EDMA3_DRV_Handle) chanHandle->hEdma,
                chanHandle->edmaChId,
                EDMA3_DRV_PARAM_FIELD_BCNT,
                &localbCnt);

            EDMA3_DRV_getPaRAMField(
                (EDMA3_DRV_Handle) chanHandle->hEdma,
                chanHandle->edmaChId,
                EDMA3_DRV_PARAM_FIELD_ACNT,
                &localaCnt);
            ioPacket->size = ioPacket->size -
                             (localaCnt * localbCnt * localcCnt);
        }
        else
        {
            /* for interrupt base transactions                                */
            if (UART_INPUT == chanHandle->mode)
            {
                UARTIntDisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) UART_INTR_RHR);
            }
            else
            {
                UARTIntDisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) UART_INTR_THR);
            }
            ioPacket->size = ioPacket->size - chanHandle->bytesRemaining;
        }

        /* active packet is available we will abort it                        */
        ioPacket->status           = IOM_ABORTED;
        chanHandle->bytesRemaining = 0;

        if (UART_INPUT == chanHandle->mode)
        {
            instHandle->stats.rxBytes += ioPacket->size;
        }
        else
        {
            instHandle->stats.txBytes += ioPacket->size;
        }

        /* switch OFF the module in the PRCM                                  */
        Uart_localPrcmOff(instHandle, NULL);

        /* callback function is available or not                              */
        if ((NULL != chanHandle->cbFxn) &&
            (UART_OPMODE_POLLED != instHandle->opMode))
        {
            /* Invoke Application callback for this channel                   */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
        }
        chanHandle->activeIOP = NULL;
    }

    /* Empty the pendList queue. Common for DMA/Interrupt Transactions        */
    while ((Bool) TRUE !=
           Queue_empty(Queue_handle(&(chanHandle->queuePendingList))))
    {
        ioPacket = (IOM_Packet *)
                   Queue_get(Queue_handle(&(chanHandle->queuePendingList)));

        ioPacket->status = IOM_ABORTED;
        ioPacket->size   = 0;

        /* switch OFF the module in the PRCM                                  */
        Uart_localPrcmOff(instHandle, NULL);

        /* callback function is available or not                              */
        if ((NULL != chanHandle->cbFxn) &&
            (UART_OPMODE_POLLED != instHandle->opMode))
        {
            /* Invoke Application callback for this channel                   */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
        }
    }

    if (UART_OPMODE_DMAINTERRUPT != instHandle->opMode)
    {
        /* reset the abort FLAG                                               */
        chanHandle->abortAllIo = (Bool) FALSE;
    }
}

/**
 * \brief   This function completes the processing of the current active IOP.
 *          it calls the call back function registered with it so that the
 *          IOP processing is completed.
 *
 * \param   chanHandle   [IN]  Handle to the channel
 *
 * \return  None
 *
 * \enter   chanHandle   must be a valid pointer and should not be null.
 *
 * \leave   Not Implemented.
 */
Void Uart_localCompleteCurrentIO(Uart_ChanObj *chanHandle)
{
    Uart_Object         *instHandle = NULL;
    UInt32 hwiKey = 0;

    hwiKey = Hwi_disable();

    assert(NULL != chanHandle);
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    /* call the application completion callback function registered           *
     * with us during opening of the channel                                  */
    if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg) &&
        (UART_OPMODE_POLLED != instHandle->opMode) &&
        (NULL != chanHandle->activeIOP))
    {
        /* Update the packet status                                           */
        if (0 != chanHandle->errors)
        {
            /* Priority is for the appropriate status set before calling this *
             * completion function for the IOP                                */
            if (IOM_COMPLETED == chanHandle->activeIOP->status)
            {
                chanHandle->activeIOP->status = IOM_EBADIO;
            }
            else if (IOM_ETIMEOUT == chanHandle->activeIOP->status)
            {
                chanHandle->activeIOP->status = IOM_COMPLETED;
            }
            else
            {
                /* MISRA C Compliance */
                /* Do Nothing. Need not update the Packet Status for this
                 *condition */
            }
        }
        else
        {
            chanHandle->activeIOP->status = IOM_COMPLETED;
        }

        /* Update the size                                                    */
        if (UART_OPMODE_INTERRUPT == instHandle->opMode)
        {
            chanHandle->activeIOP->size =
                chanHandle->activeIOP->size - chanHandle->bytesRemaining;
        }

        if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
        {
            EDMA3_DRV_PaRAMRegs paramSet =
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            UInt32 bytesRemain = 0;

            /* Get the PaRAM set for default parameters                       */
            EDMA3_DRV_getPaRAM((EDMA3_DRV_Handle) chanHandle->hEdma,
                               chanHandle->edmaChId,
                               &paramSet);
            /* calculate the amount of bytes remaining                        */
            bytesRemain = (paramSet.aCnt * paramSet.bCnt * paramSet.cCnt);
            chanHandle->activeIOP->size =
                chanHandle->activeIOP->size - bytesRemain;
        }
        else
        {
            /* Do nothing - poll mode is handled in transfer function itself  */
        }

        /* switch OFF the module in the PRCM                                  */
        Uart_localPrcmOff(instHandle, NULL);

        /* when setting the status of the IOP,priority is given to the error  *
         * generated by the IOP. if the IOP has completed successfully, then  *
         * the priority will be for the error (if any) generated by the PRCM  *
         * while switching off the module                                     */
        if (IOM_COMPLETED == chanHandle->activeIOP->status)
        {
            Int32 retVal = IOM_COMPLETED;

            chanHandle->activeIOP->status = retVal;
        }

        if ((NULL != chanHandle->cbFxn) &&
            (UART_OPMODE_POLLED != instHandle->opMode))
        {
            /* Invoke Application callback for this channel                   */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, chanHandle->activeIOP);
        }
    }

    chanHandle->activeIOP = NULL;

    Hwi_restore(hwiKey);
}

/**
 *  \brief  Receiver Errors
 *
 *  This function finds errors on the Receiver buffer.
 *
 *  \param  chanHandle     [IN]   Handle of the Channel Object
 *  \param  eb             [OUT]  Error block
 *
 *  \return If successful, returns IOM_COMPLETED
 *          or IOM_EBADARGS in case of error
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          eb           if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
static Int32 uartHandleRxError(Uart_ChanObj *chanHandle, Error_Block *eb)
{
    UInt32 status            = 0;
    UInt32 iteration         = 0;
    Int32 retVal             = IOM_COMPLETED;
    Int8 tempByte            = 0;
    Uart_Object  *instHandle = NULL;
#ifdef BIOS_PWRM_ENABLE
    Uns count = 0x00;
#endif
    assert(NULL != chanHandle);
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    /* check for the errors and if there is any error update the stats        */
    status = (UInt32) UARTReadStatus(
        (UInt32) instHandle->deviceInfo.baseAddress);
    status &= (UART_LSR_RX_FIFO_STS_MASK |
               UART_LSR_RX_BI_MASK |
               UART_LSR_RX_FE_MASK |
               UART_LSR_RX_PE_MASK |
               UART_LSR_RX_OE_MASK |
               UART_LSR_RX_FIFO_E_MASK);

    /* Notify the upper layer about the errors, if notification is registered */
    if (NULL != chanHandle->gblErrCbkFxn)
    {
        /* Misra Pointer to Int - We will be sending the address of Arg Pointer
         * to the CallbkFxn */
        (*chanHandle->gblErrCbkFxn)((UInt32) chanHandle->gblErrCbkArg,
                                    status, NULL);
    }

    if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
    {
        /* Disable the EDMA
         *                                                   */
        EDMA3_DRV_disableLogicalChannel(
            (EDMA3_DRV_Handle) chanHandle->hEdma,
            chanHandle->edmaChId,
            EDMA3_DRV_TRIG_MODE_EVENT);
    }

    if ((UInt32) UART_LSR_RX_OE_MASK == (status & (UInt32) UART_LSR_RX_OE_MASK))
    {
        instHandle->stats.overrun++;
        chanHandle->errors++;
    }

    if ((UInt32) UART_LSR_RX_FIFO_STS_MASK ==
        (status & (UInt32) UART_LSR_RX_FIFO_STS_MASK))
    {
        if ((UInt32) UART_LSR_RX_FE_MASK ==
            (status & (UInt32) UART_LSR_RX_FE_MASK))
        {
            instHandle->stats.rxFramingError++;
            chanHandle->errors++;
        }

        if ((UInt32) UART_LSR_RX_PE_MASK ==
            (status & (UInt32) UART_LSR_RX_PE_MASK))
        {
            instHandle->stats.rxParityError++;
            chanHandle->errors++;
        }

        if ((UInt32) UART_LSR_RX_BI_MASK ==
            (status & (UInt32) UART_LSR_RX_BI_MASK))
        {
            instHandle->stats.rxBreakError++;
            chanHandle->errors++;
        }
    }

    /* Clearing Receive Errors(FE,BI,PE)by reading erroneous data from RX FIFO
     */
    /* Iteration count: Worst case = FIFO size                                */
    if ((Bool) TRUE == instHandle->devParams.fifoEnable)
    {
        /* Iteration count:  FIFO size(64)  if FIFO enabled                   */
        iteration = BSP_UART_FIFO_SIZE;
    }
    else
    {
        iteration = BSP_UART_FIFO_DISABLED_CHUNK_SIZE;
    }

    do
    {
        /* Read and throw error byte                                          */
        /* Till Line status int is pending                                    */
        tempByte = UARTFIFOCharGet(
            (UInt32) instHandle->deviceInfo.baseAddress);
        /* To remove compiler "unused" warnings                               */
        tempByte = tempByte;

        iteration--;

        status = (UInt32) UARTReadStatus(
            (UInt32) instHandle->deviceInfo.baseAddress);
        status &= (UART_LSR_RX_FIFO_STS_MASK |
                   UART_LSR_RX_BI_MASK |
                   UART_LSR_RX_FE_MASK |
                   UART_LSR_RX_PE_MASK |
                   UART_LSR_RX_OE_MASK |
                   UART_LSR_RX_FIFO_E_MASK);
    }
    while ((status != 0) && (iteration != 0));

    if (NULL != chanHandle->activeIOP)
    {
        Uart_localCompleteCurrentIO(chanHandle);
    }
#ifdef BIOS_PWRM_ENABLE
    if (TRUE == instHandle->pwrmInfo.ioSuspend)
    {
#endif
    Uart_loadPendedIops(chanHandle);
#ifdef BIOS_PWRM_ENABLE
}

else
{
    if ((TRUE == instHandle->devParams.prcmPwrmEnable) &&
        (TRUE == instHandle->pwrmInfo.ioSuspend))
    {
        /* set the current active IOP as NULL                             */
        chanHandle->activeIOP = NULL;
        instHandle->devState  = UART_DRIVERSTATE_PWRM_SUSPEND;

        if ((NULL == instHandle->rcvChanObj.activeIOP) &&
            (NULL == instHandle->xmtChanObj.activeIOP))
        {
            /* if both the channels are inactive then reset               *
             * the io suspend flag                                        */
            instHandle->pwrmInfo.ioSuspend = FALSE;

            if ((PWRM_GOINGTOSLEEP == instHandle->pwrmInfo.pwrmEvent) ||
                (PWRM_GOINGTODEEPSLEEP == instHandle->pwrmInfo.pwrmEvent))
            {
                /* reduce the dependency count                            */
                status = PWRM_getDependencyCount(
                    (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId,
                    &count);

                instHandle->pwrmInfo.dependencyCount = count;

                if (PWRM_SOK == status)
                {
                    while (count > 0)
                    {
                        status = PWRM_releaseDependency(
                            (PWRM_Resource)
                            instHandle->deviceInfo.pwrmPrcmId);

                        if (PWRM_SOK != status)
                        {
                            break;
                        }
                        count--;
                    }
                }
            }
            /* call the delayed completion function                       */
            (instHandle->pwrmInfo.delayedCompletionFxn \
             [instHandle->pwrmInfo.pwrmEvent])();
        }
    }
}
#endif
    return retVal;
}

/**
 * \brief   checks if the data is ready
 *
 * \param   chanHandle   [IN]     Handle to the channel Object
 * \param   eb           [OUT]    pointer to the error block
 *
 * \return  TRUE  if data is ready
 *          FALSE  if not ready
 *
 * \enter  chanHandle   must be a valid pointer and should not be null.
 *         eb           if null raise error and aborts the program, if not null
 *                      and valid raises error but shall allow continuation of
 *                      execution
 *
 * \leave  Not Implemented.
 */
static Bool uartStatusIsDataReady(Uart_ChanObj *chanHandle, Error_Block *eb)
{
    UInt32 status = 0;
    Bool retVal   = FALSE;
    Uart_Object  *instHandle = NULL;

    assert(NULL != chanHandle);
    instHandle = (Uart_Object *) chanHandle->devHandle;
    assert(NULL != instHandle);

    status = (UInt32) UARTReadStatus(
        (UInt32) instHandle->deviceInfo.baseAddress);

    /* Added for error checks                                                 */
    if ((UInt32) UART_LSR_RX_FIFO_STS_MASK ==
        (status & (UInt32) UART_LSR_RX_FIFO_STS_MASK))
    {
        uartHandleRxError(chanHandle, NULL);
    }
    /* Caution: This should be under if else of error check since
     * the RX error handler clears the FIFO. Hence the status we have read
     * before this call will become stale. Hence the data will not be
     * ready in FIFO. Otherwise we will read the FIFO register which has
     * a infinite loop for data ready and the code hangs there till user
     * gives any character!! */
    else if ((UInt32) UART_LSR_RX_FIFO_E_MASK ==
             (status & (UInt32) UART_LSR_RX_FIFO_E_MASK))
    {
        retVal = (Bool) TRUE;
    }
    else
    {
        /* Do nothing */
    }

    return retVal;
}

/**
 *  \brief  Write into TX FIFO
 *
 *  This function writes into TX FIFO from the iop buffer
 *
 *  \param  chanHandle    [IN]             Handle of the Channel Object
 *  \param  buffer        [IN]             Buffer for the operation
 *  \param  nwrite        [IN]             Number of bytes left to be written
 *
 *  \return Number of bytes written
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          buffer       must be a valid pointer and should not be null.
 *          nwrite       must be a valid nwrite value.
 *
 *  \leave  Not Implemented.
 */
static UInt32 uartFifoWrite(const Uart_ChanObj *chanHandle,
                            const UInt8        *buffer,
                            UInt32              nwrite)
{
    UInt32 size                  = nwrite;
    UInt32 lineStatus            = 0;
    UInt32 tempChunksize         = 0;
    Uart_Object      *instHandle = NULL;
    Int32 maxTrialCount          = (Int32) BSP_UART_TRANSMITEMPTY_TRIALCOUNT;

    assert(NULL != chanHandle);
    assert(NULL != buffer);

    instHandle = (Uart_Object *) chanHandle->devHandle;

    assert(NULL != instHandle);

    if (UART_OPMODE_POLLED == instHandle->opMode)
    {
        /* Load the chunk size(fifo size)                                         */
        tempChunksize = chanHandle->chunkSize;
        /* Before we could write 'chunksize' no. of bytes, we should have
         * 'chunk size' no. of free buffers. Hence, we check for shiftregister
         * empty (ensure the FIFO is empty) to write chunksize bytes */
        do
        {
            lineStatus = (UInt32) UARTReadStatus(
                (UInt32) instHandle->deviceInfo.baseAddress);
            maxTrialCount--;
        }
        while (((UInt32) (UART_LSR_TX_SR_E_MASK | UART_LSR_TX_FIFO_E_MASK) !=
                ((UInt32) (UART_LSR_TX_SR_E_MASK |
                           UART_LSR_TX_FIFO_E_MASK) & lineStatus))
               && (0 < maxTrialCount));
    }
    else
    {
        /* In interrupt mode write only threshold level of data when FIFO
         * is enabled */
        if (TRUE == instHandle->devParams.fifoEnable)
        {
            tempChunksize = instHandle->devParams.txThreshold;
        }
        else
        {
            tempChunksize = BSP_UART_FIFO_DISABLED_CHUNK_SIZE;
        }
    }

    if (maxTrialCount > 0)
    {
        while (((tempChunksize > 0) && (nwrite > 0)))
        {
            /* Writing to the H/w                                             */
            uartWriteByte((Uart_Object *) chanHandle->devHandle,
                          (Char) (*buffer));
            /* Misra C Waiver Reason
             * Pointer Arithmetic,
             */
            buffer++;
            nwrite--;
            tempChunksize--;
        }
    }

    /* Returns the size actually written                                      */
    return (size - nwrite);
}

/**
 *  \brief  Read from RX FIFO
 *
 *   This function Reads from the RX FIFO into the iop buffer
 *
 *  \param  chanHandle  [IN]    Handle of the Channel Object
 *  \param  buffer      [IN]    Buffer for the operation
 *  \param  bufSize     [IN]    No. of bytes left to be read
 *
 *  \return No. of bytes read
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          buffer       must be a valid pointer and should not be null.
 *          bufSize      must be a valid buffer size value.
 *          eb           if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
static UInt32 uartFifoRead(Uart_ChanObj *chanHandle,
                           UInt8        *buffer,
                           UInt32        bufSize,
                           Error_Block  *eb)
{
    UInt32 size    = bufSize;
    Bool isRxReady = FALSE;

    assert(NULL != buffer);
    assert(NULL != chanHandle);
    isRxReady = uartStatusIsDataReady(chanHandle, NULL);

    while (((Bool) TRUE == isRxReady) && (0U != bufSize))
    {
        /* once the H/w is ready  reading from the H/w                        */
        *buffer = (UInt8) uartReadByte((Uart_Object *) chanHandle->devHandle);
        /*
         * Misra.PTR.ARITHMETIC
         */
        buffer++;
        --bufSize;

        isRxReady = uartStatusIsDataReady(chanHandle, NULL);
    }

    return (size - bufSize);
}

/**
 *  \brief    This function reads or writes the data depending on the
 *            channel type.
 *
 *  \param    chanHandle        [IN]    Handle to the Channel
 *  \param    buffer            [IN]    Buffer for the transfer
 *  \param    numBytes          [IN]    No. of bytes to be transferred
 *  \param    eb                [IN]    pointer to error block
 *
 *  \return   No of bytes processed.
 *
 *  \enter  chanHandle   must be a valid pointer and should not be null.
 *          buffer       must be a valid pointer and should not be null.
 *          numBytes     must be a valid number of bytes value.
 *          eb           if null raise error and aborts the program, if not null
 *                       and valid raises error but shall allow continuation of
 *                       execution
 *
 *  \leave  Not Implemented.
 */
static UInt32 uartXfer(Uart_ChanObj *chanHandle,
                       UInt8        *buffer,
                       UInt32        numBytes,
                       Error_Block  *eb)
{
    UInt32 xferedBytes = 0;

    assert(NULL != buffer);
    assert(NULL != chanHandle);
    /* Depending on the mode call its respective functions                    */
    if (UART_INPUT == chanHandle->mode)
    {
        /* receive channel hence read the data                                */
        xferedBytes = uartFifoRead((Uart_ChanObj *) chanHandle,
                                   (UInt8 *) buffer,
                                   (UInt32) numBytes,
                                   NULL);
    }
    else
    {
        /* transmit channel hence write the data                              */
        xferedBytes = uartFifoWrite((Uart_ChanObj *) chanHandle,
                                    (UInt8 *) buffer,
                                    (UInt32) numBytes);
    }

    /* return the number of bytes processed(read or written)                  */
    return (xferedBytes);
}

/**
 * \brief Uart ISR
 *
 *  This function is the ISR for the entire Uart device. This routine further
 *  processes the exact cause of interrupt by reading IIR
 *
 * \param  arg  [IN]    Handle to the Uart driver object
 *
 * \return If successful, returns IOM_COMPLETED or IOM error codes
 *
 * \enter  arg   must be a valid pointer and should not be null.
 *
 * \leave  Not Implemented.
 */
static Void uartIsr(UArg arg)
{
    volatile UInt32 status       = BSP_UART_ISR_STATUS;
    UInt32 intrCnt               = 0;
    Uart_Object      *instHandle = NULL;
    UInt32 tempMcr               = 0;
    Uart_ChanObj     *chanHandle = NULL;
    UInt32 xfer = 0;

#ifdef BIOS_PWRM_ENABLE
    Uns count = 0x00;
#else
    IOM_Packet  *ioPacket = NULL;
#endif

    assert((UArg) NULL != arg);
    /* To remove the compiler warning                                         */
    tempMcr = tempMcr;

    instHandle = (Uart_Object *) arg; /* MISRA POINTER TO INT */

    while (((UInt32) UART_INT_PENDING ==
            (UARTIntPendingStatusGet((UInt32) instHandle->deviceInfo.
                                     baseAddress)))
           && ((intrCnt) < (BSP_UART_MAX_ISR_LOOP)))
    {
        intrCnt++;

        status = UARTIntIdentityGet((UInt32) instHandle->deviceInfo.baseAddress);

        /*  check for any line error while transfer                           */
        if ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_3 ==
            ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_3 &
             (status >> UART_IIR_IT_TYPE_SHIFT)))
        {
            /* call this function when ther is any line error                 */
            uartHandleRxError(&(instHandle->rcvChanObj), NULL);
        }
        else if (UART_OPMODE_INTERRUPT == instHandle->opMode)
        {
            if ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_2 ==
                ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_2 &
                 (status >> UART_IIR_IT_TYPE_SHIFT)))
            {
                /* check whether any character timeout happened
                 *                  */
                if ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_6 ==
                    ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_6 &
                     (status >> UART_IIR_IT_TYPE_SHIFT)))
                {
                    chanHandle = &(instHandle->rcvChanObj);
                    /* if timeout error then update stats                     */
                    instHandle->stats.rxTimeout++;

                    /* Increment the error count                              */
                    chanHandle->errors++;

                    /* Update the IOP with proper status                      */
                    chanHandle->activeIOP->status = IOM_ETIMEOUT;

                    /* Transfer the remanant bytes if any are remaining in the*
                     * FIFO                                                   */
                    xfer = uartFifoRead((Uart_ChanObj *) chanHandle,
                                        chanHandle->activeBuf,
                                        (UInt32) chanHandle->bytesRemaining,
                                        NULL);

                    chanHandle->bytesRemaining -= xfer;
                    chanHandle->activeBuf      += xfer;
                    /*
                     * Misra.PTR.ARITHMETIC
                     */
                    instHandle->stats.rxBytes += xfer;

                    /* Disable the RX interrupts before completing. If only   *
                     * there is a packet for processing it shall be re-enabled
                     */
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) (UART_INTR_RLS | UART_INTR_RHR));

                    /* Perform the operation to complete the IO               */
                    Uart_localCompleteCurrentIO(chanHandle);
#ifdef BIOS_PWRM_ENABLE
                    if ((TRUE == instHandle->devParams.prcmPwrmEnable) &&
                        (TRUE == instHandle->pwrmInfo.ioSuspend))
                    {
                        /* set the current active IOP as NULL                 */
                        chanHandle->activeIOP = NULL;
                        instHandle->devState  = UART_DRIVERSTATE_PWRM_SUSPEND;

                        if ((NULL == instHandle->rcvChanObj.activeIOP) &&
                            (NULL == instHandle->xmtChanObj.activeIOP))
                        {
                            /* if both the channels are inactive then reset   *
                             * the io suspend flag                            */
                            instHandle->pwrmInfo.ioSuspend = FALSE;

                            if ((PWRM_GOINGTOSLEEP ==
                                 instHandle->pwrmInfo.pwrmEvent) ||
                                (PWRM_GOINGTODEEPSLEEP ==
                                 instHandle->pwrmInfo.pwrmEvent))
                            {
                                /* reduce the dependency count                */
                                status =
                                    PWRM_getDependencyCount(
                                        (PWRM_Resource)
                                        instHandle->
                                        deviceInfo.pwrmPrcmId,
                                        &count);

                                instHandle->pwrmInfo.dependencyCount = count;

                                if (PWRM_SOK == status)
                                {
                                    while (count > 0)
                                    {
                                        status =
                                            PWRM_releaseDependency(
                                                (PWRM_Resource)
                                                instHandle->deviceInfo.
                                                pwrmPrcmId);

                                        if (PWRM_SOK != status)
                                        {
                                            break;
                                        }
                                        count--;
                                    }
                                }
                            }
                            /* call the delayed completion function           */
                            (instHandle->pwrmInfo.delayedCompletionFxn \
                             [instHandle->pwrmInfo.pwrmEvent])();
                        }
                    }
#else
                    /* Now that we have just completed the current IOP        *
                     * we proceed to check if there are still packets         *
                     * pending in pending queue                               */
                    if (FALSE == Queue_empty(
                            Queue_handle(&(chanHandle->queuePendingList))))
                    {
                        /* we have atleast one packet                         */
                        ioPacket =
                            (IOM_Packet *)
                            Queue_get(Queue_handle(&(chanHandle->
                                                     queuePendingList)));

                        /* validate and update the iop                        */
                        if (NULL != ioPacket)
                        {
                            chanHandle->activeIOP = ioPacket;
                            chanHandle->activeBuf =
                                (UInt8 *) ioPacket->addr;
                            chanHandle->bytesRemaining = ioPacket->size;
                            chanHandle->errors         = 0;
                        }
                        UARTIntEnable(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            (UInt32) (UART_INTR_RLS | UART_INTR_RHR));
                    }
                    else
                    {
                        chanHandle->activeIOP = NULL;
                    }
#endif
                }
                else
                {
                    /* Disable the receive interrupt until current interrupt  *
                     * is processed. Re-enabled again in uartIntrHandler()    */
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_RHR);

                    /* uartIntrHandler(&(instHandle->rcvChanObj));            */
                    Swi_post(instHandle->rxTskletHandle);
                }
            }
            else
            {
                /* check whether Tx register is empty or not                  */
                if ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_1 ==
                    ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_1 &
                     (status >> UART_IIR_IT_TYPE_SHIFT)))
                {
                    /* Disable the transmit interrupt until current interrupt *
                     * is processed. Re-enabled again in uartIntrHandler()    */
                    UARTIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_THR);

                    /* uartIntrHandler(&(instHandle->xmtChanObj));            */
                    Swi_post(instHandle->txTskletHandle);
                }
                else
                {
                    /* check modem status                                     */
                    if ((UInt32) UART_IIR_IT_TYPE_IT_TYPE_VALUE_0 ==
                         (status >> UART_IIR_IT_TYPE_SHIFT))
                    {
                        /* Read the MSR to clear Modem Status Int cause       */
                        tempMcr = UARTModemStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress);
                    }
                }
            }
        }
        else
        {
            /* Do nothing                                                     */
        }
    }
}

/**
 *  \brief  The entry function for Tx Swi Handler
 *
 *  \param  arg0       [IN]  Handle of the Channel Object
 *  \param  unUsedArg  [IN]  Handle to unused arguments
 *
 *  \return None
 *
 *  \enter  arg0        must be a valid pointer and should not be null.
 *          unUsedArg   must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Void uartTxSwiHandler(UArg arg0, UArg unUsedArg)
{
    Uart_ChanObj *chanHandle = NULL;
    assert((UArg) NULL != arg0);

    chanHandle = (Uart_ChanObj *) arg0; /* Misra Point to Int */

    /* To remove the compiler warning                                         */
    unUsedArg = unUsedArg;
    uartIntrHandler(chanHandle);
}

/**
 *  \brief  The entry function for Rx Swi Handler
 *
 *  \param  arg0       [IN]  Handle of the Channel Object
 *  \param  unUsedArg  [IN]  Handle to unused arguments
 *
 *  \return None
 *
 *  \enter  arg0        must be a valid pointer and should not be null.
 *          unUsedArg   must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */
static Void uartRxSwiHandler(UArg arg0, UArg unUsedArg)
{
    Uart_ChanObj *chanHandle = NULL;
    assert((UArg) NULL != arg0);

    /* To remove the compiler warning                                         */
    unUsedArg = unUsedArg;

    chanHandle = (Uart_ChanObj *) arg0; /* Misra Point to Int */

    uartIntrHandler(chanHandle);
}

/* ============================================================================
**/
/*                             PWRM FUNCTIONS                                 */
/* ============================================================================
**/

/**
 * \brief    Uart_localLpscOn
 *           This function is invoked to power on the UART peripheral in the
 *           PRCM.
 *
 * \note     Note that this function uses different functions to power ON the
 *           module, depending on whether the PWRM is enabled in this driver
 *           or NOT
 *
 * \param    chanHandle    [IN]    handle to the IO channel
 * \param    eb            [OUT]   pointer to user supplied error block
 *
 * \return   None. (check error block for any errors)
 *
 * \enter    chanHandle must be a valid channel object
 *           The driver/channel should be in opened state.
 *
 * \leave    Not Implemented.
 */
Int32 Uart_localPrcmOn(const Uart_Object *instHandle, Error_Block *eb)
{
    Int32 status = IOM_COMPLETED;
    assert(NULL != instHandle);

    if (TRUE == instHandle->devParams.prcmPwrmEnable)
    {
#ifdef BIOS_PWRM_ENABLE
        /* power on using PWRM API                                            */
        status = (Int32) PWRM_setDependency(
            (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId);
#else
        /* power on using PRCM API                                            */

#endif
    }
    return (status);
}

/**
 * \brief    Uart_localLpscOff
 *           This function is invoked to power off the peripheral in the PRCM.
 *
 * \param    chanHandle    [IN]    channel handle
 * \param    eb            [OUT]   pointer to user supplied error block
 *
 * \return   None. (check error block for any errors)
 *
 * \enter    chanHandle must be a valid channel object
 *           No pending IO
 *
 * \leave    Not Implemented.
 */
Int32 Uart_localPrcmOff(const Uart_Object *instHandle, Error_Block *eb)
{
    Int32 status = IOM_COMPLETED;
    UInt32 isTxFifoEmpty, txFifoTimeout;

    assert(NULL != instHandle);

    if (TRUE == instHandle->devParams.prcmPwrmEnable)
    {
        /* Wait for TX to complete the transfer */
        txFifoTimeout = BSP_UART_TRANSMITEMPTY_TRIALCOUNT;
        while (txFifoTimeout > 0U)
        {
            isTxFifoEmpty = UARTSpaceAvail(
                (UInt32) instHandle->deviceInfo.baseAddress);
            if ((UInt32) TRUE == isTxFifoEmpty)
            {
                /* FIFO and Shift register is empty */
                break;
            }

            Task_sleep((UInt32) BSP_UART_TX_FIFO_WAIT_PERIOD);
            txFifoTimeout--;
        }

#ifdef BIOS_PWRM_ENABLE
        /* power off  using PWRM API                                          */
        status = (Int32) PWRM_releaseDependency(
            (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId);
#else
        /* power off using PRCM API                                           */

#endif
    }

    return (status);
}

/**
 * \brief     This function restores the driver to the original state that is it
 *            resumes the normal operation of the driver by picking the IOPs
 *            from the pending queue and putting it to the active IOP.
 *
 * \param     instHandle  [IN]   Handle to the device instance object
 * \param     eb          [OUT]  pointer to user supplied error block
 *
 * \enter     instHandle is a valid non NULL pointer
 *
 * \leave     Not implemented
 */
Void Uart_loadPendedIops(Uart_ChanObj *chanHandle)
{
    Uart_Object          *instHandle = NULL;

    assert(NULL != chanHandle);
    assert(NULL != chanHandle->devHandle);

    instHandle = (Uart_Object *) chanHandle->devHandle;

    if (FALSE == Queue_empty(Queue_handle(&(chanHandle->queuePendingList))))
    {
        IOM_Packet   *ioPacket = NULL;

        /* we have atleast one packet                                         */
        ioPacket = (IOM_Packet *) Queue_get(
            Queue_handle(&(chanHandle->queuePendingList)));

        /* validate and update the iop                                        */
        if (NULL != ioPacket)
        {
            chanHandle->activeIOP      = ioPacket;
            chanHandle->activeBuf      = (UInt8 *) ioPacket->addr;
            chanHandle->bytesRemaining = ioPacket->size;
            chanHandle->errors         = 0;

            if (UART_OPMODE_INTERRUPT == instHandle->opMode)
            {
                if (UART_INPUT == chanHandle->mode)
                {
                    UARTIntEnable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) (UART_INTR_RHR | UART_INTR_RLS));
                }
                else
                {
                    UARTIntEnable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) UART_INTR_THR);
                }
            }
            if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
            {
                Uart_localStartEdmaTransfer(chanHandle, ioPacket->cmd, NULL);
            }
        }
    }
    else
    {
        chanHandle->activeIOP = NULL;
    }
}

Int32 Uart_localMakeFCR(const Uart_Object  *instHandle,
                        const Uart_TrigLvl *trigLevel,
                        UInt32             *fcrValue)
{
    Int32 retVal = IOM_COMPLETED;
    UInt32 value;
    assert(NULL != instHandle);
    assert(NULL != trigLevel);
    assert(NULL != fcrValue);

    value = 0U;
    if (TRUE == instHandle->devParams.fifoEnable)
    {
        switch (trigLevel->rxTrigLvl)
        {
            case UART_RXTRIGLVL_8:
                value |= UART_FCR_RX_FIFO_TRIG_8CHAR;
                /* Receive FIFO trigger level 8 chars    */
                break;

            case UART_RXTRIGLVL_16:
                value |= UART_FCR_RX_FIFO_TRIG_16CHAR
                         << UART_FCR_RX_FIFO_TRIG_SHIFT;
                /* Receive FIFO trigger level 16 chars   */
                break;

            case UART_RXTRIGLVL_56:
                value |= UART_FCR_RX_FIFO_TRIG_56CHAR
                         << UART_FCR_RX_FIFO_TRIG_SHIFT;
                /* Receive FIFO trigger level 56 chars   */
                break;

            case UART_RXTRIGLVL_60:
                value |= UART_FCR_RX_FIFO_TRIG_60CHAR
                         << UART_FCR_RX_FIFO_TRIG_SHIFT;
                /* Receive FIFO trigger level 60 chars   */
                break;
            default:
                retVal = IOM_EBADARGS;
                break;
        }

        switch (trigLevel->txTrigLvl)
        {
            case UART_TXTRIGLVL_8:
                value |= UART_FCR_TX_FIFO_TRIG_8SPACES;
                /* Transmit FIFO trigger level 8 Spaces  */
                break;

            case UART_TXTRIGLVL_16:
                value |= UART_FCR_TX_FIFO_TRIG_16SPACES
                         << UART_FCR_TX_FIFO_TRIG_SHIFT;
                /* Transmit FIFO trigger level 16 Spaces */
                break;

            case UART_TXTRIGLVL_32:
                value |= UART_FCR_TX_FIFO_TRIG_32SPACES
                         << UART_FCR_TX_FIFO_TRIG_SHIFT;
                /* Transmit FIFO trigger level 32 Spaces */
                break;

            case UART_TXTRIGLVL_56:
                value |= UART_FCR_TX_FIFO_TRIG_56SPACES
                         << UART_FCR_TX_FIFO_TRIG_SHIFT;
                /* Transmit FIFO trigger level 56 Spaces */
                break;
            default:
                retVal = IOM_EBADARGS;
                break;
        }
    }

    if (IOM_COMPLETED == retVal) /* If valid trigger level passed */
    {
        if (UART_OPMODE_DMAINTERRUPT == instHandle->opMode)
        {
            /* Set DMAMODE bit */
            value |= UART_FCR_DMA_MODE_MASK;
        }
        if (TRUE == instHandle->devParams.fifoEnable)
        {
            /* Set FIFO enable bit */
            value |= UART_FCR_FIFO_EN_MASK;
        }
    }

    *fcrValue = value;

    return (retVal);
}

#ifdef BIOS_PWRM_ENABLE
/**
 * \brief     This function registers with the BIOS PWRM module for all the
 *            possible power management events.
 *
 * \param     instHandle [IN] Handle to the driver instance object
 *
 * \return    None
 *
 * \enter     instHandle is a NON null valid pointer
 *
 * \leave     Not implemented
 */
static Int32 UartRegisterNotification(Uart_Object *instHandle)
{
    UInt32 eventCnt    = 0x00;
    PWRM_Status retVal = PWRM_SOK;
    Int32 status       = IOM_COMPLETED;

    assert(NULL != instHandle);

    /* register for the events to be notified by the driver                   */
    for (eventCnt = 0; eventCnt < BSP_UART_MAX_PWRM_EVENTS; eventCnt++)
    {
        /* register the notify function for the PWRM event                    */
        retVal = PWRM_registerNotify(
            (PWRM_Event) eventCnt,
            NULL,
            UartNotifyCallback,
            (Arg) instHandle,
            &(instHandle->pwrmInfo.notifyHandle[eventCnt]),
            &(instHandle->pwrmInfo.delayedCompletionFxn[eventCnt]));

        if (PWRM_SOK != retVal)
        {
            status = IOM_EBADARGS;
            break;
        }
    }
    return (status);
}

/**
 * \brief     This function unregisters all the power management events
 *            which were previously registered by the driver instance.
 *
 * \param     instHandle [IN] Handle to the driver instance object
 *
 * \return    IOM_COMPLETED in case of success
 *            IOM_EBADARGS  in case of error
 *
 * \enter     instHandle is a NON null valid pointer
 *
 * \leave     Not implemented
 */
static Int32 UartUnregisterNotification(Uart_Object *instHandle)
{
    UInt32 eventCnt    = 0x00;
    PWRM_Status retVal = PWRM_SOK;
    Int32 status       = IOM_COMPLETED;

    assert(NULL != instHandle);

    for (eventCnt = 0; eventCnt < BSP_UART_MAX_PWRM_EVENTS; eventCnt++)
    {
        /* register the notify function for the PWRM event                    */
        if (NULL != (instHandle->pwrmInfo.notifyHandle[eventCnt]))
        {
            retVal = PWRM_unregisterNotify(
                (instHandle->pwrmInfo.notifyHandle[eventCnt]));

            if (PWRM_SOK != retVal)
            {
                status = IOM_EBADARGS;
                break;
            }
            else
            {
                instHandle->pwrmInfo.notifyHandle[eventCnt] = 0x00;
            }
        }
    }
    return (status);
}

/**
 * \brief     This function is the notify function called by the BIOS whenever
 *            a power event occurs in the system.This function handles the
 *            power events and calls the appropriate functions to process the
 *            same.
 *
 * \param     eventType [IN] power event type
 * \param     eventArg1 [IN] event-specific argument
 * \param     eventArg2 [IN] event-specific argument
 * \param     clientArg [IN] argument passed by the PWRM module(usually
 *                          (supplied during the registration of the notifyFxn)
 *
 * \return    None
 *
 * \enter     eventType is a valid event
 *
 * \leave     Not implemented
 */
static PWRM_NotifyResponse UartNotifyCallback(PWRM_Event eventType,
                                              Arg        eventArg1,
                                              Arg        eventArg2,
                                              Arg        clientArg)
{
    Uart_Object          *instHandle = NULL;
    PWRM_NotifyResponse pwrmStatus   = PWRM_NOTIFYDONE;
    PWRM_Status status = PWRM_SOK;

    assert(NULL != clientArg);

    instHandle = (Uart_Object *) clientArg;
    assert(NULL != instHandle);

    /* check the event notified by the PWRM module and process accordingly    */
    switch (eventType)
    {
        case PWRM_GOINGTOSLEEP:
        case PWRM_GOINGTOSTANDBY:
        case PWRM_GOINGTODEEPSLEEP:
            pwrmStatus = UartSuspendCurrentIops(instHandle, eventType);
            break;
        case PWRM_PENDING_CPU_SETPOINTCHANGE:
        case PWRM_PENDING_PER_SETPOINTCHANGE:
            /* CPU or PERIPHERAL domain V/F setpoint or a sleep command is    *
             * issued hence we will complete the current IO and suspend all   *
             * the pending IOs                                                */
            if (((PWRM_PENDING_CPU_SETPOINTCHANGE == eventType) &&
                 (UART_PLLDOMAIN_0 == instHandle->pwrmInfo.pllDomain)) ||
                ((PWRM_PENDING_PER_SETPOINTCHANGE == eventType) &&
                 (UART_PLLDOMAIN_1 == instHandle->pwrmInfo.pllDomain)))
            {
                pwrmStatus = UartSuspendCurrentIops(instHandle, eventType);
            }
            break;
        case PWRM_DONE_CPU_SETPOINTCHANGE:
        case PWRM_DONE_PER_SETPOINTCHANGE:
            /* The pending CPU setpoint change has now been made.Hence now we *
             * will recalculate the new settings for this instance and then   *
             * restore the pending state of the driver                        */
            if (((PWRM_DONE_CPU_SETPOINTCHANGE == eventType) &&
                 (UART_PLLDOMAIN_0 == instHandle->pwrmInfo.pllDomain)) ||
                ((PWRM_DONE_PER_SETPOINTCHANGE == eventType) &&
                 (UART_PLLDOMAIN_1 == instHandle->pwrmInfo.pllDomain)))
            {
                pwrmStatus = UartConfigureNewVfSettings(
                    instHandle,
                    eventArg1,
                    eventArg2);
            }

            if (PWRM_NOTIFYDONE == pwrmStatus)
            {
                /* Resume both the channels                                   */
                uartConfigure(instHandle, &instHandle->devParams);
                Uart_loadPendedIops(&instHandle->xmtChanObj);
                Uart_loadPendedIops(&instHandle->rcvChanObj);
                /* update the state of the driver                             */
                instHandle->devState = UART_DRIVERSTATE_CREATED;
            }
            break;
        case PWRM_AWAKEFROMSLEEP:
        case PWRM_AWAKEFROMDEEPSLEEP:
            /* restore the dependency count                                   */
            while (instHandle->pwrmInfo.dependencyCount > 0)
            {
                status = PWRM_setDependency(
                    (PWRM_Resource) instHandle->deviceInfo.pwrmPrcmId);

                if (PWRM_SOK != status)
                {
                    break;
                }
                instHandle->pwrmInfo.dependencyCount--;
            }

            if (PWRM_SOK == status)
            {
                /* Resume both the channels                                   */
                uartConfigure(instHandle, &instHandle->devParams);
                Uart_loadPendedIops(&instHandle->xmtChanObj);
                Uart_loadPendedIops(&instHandle->rcvChanObj);
                /* update the state of the driver                             */
                instHandle->devState = UART_DRIVERSTATE_CREATED;
            }
            else
            {
                pwrmStatus = PWRM_NOTIFYNOTDONE;
            }
            break;
        case PWRM_AWAKEFROMSTANDBY:
            /* Resume both the channels                                       */
            uartConfigure(instHandle, &instHandle->devParams);
            Uart_loadPendedIops(&instHandle->xmtChanObj);
            Uart_loadPendedIops(&instHandle->rcvChanObj);
            /* update the state of the driver                                 */
            instHandle->devState = UART_DRIVERSTATE_CREATED;
            break;
        default:
            break;
    }

    return (pwrmStatus);
}

/**
 * \brief    This function configures the driver so that the current IOP can be
 *           completed and then supends all the remaining IOPs.
 *
 * \param    instHandle [IN] Handle to the device instance object
 * \param    eventType  [IN] event which has caused this notification call to
 *                           driver
 *
 * \return   PWRM_NOTIFYDONE    if no IOPs are pending else
 *           PWRM_NOTIFYNOTDONE if IOPs are pending in the driver.
 */
static PWRM_NotifyResponse UartSuspendCurrentIops(Uart_Object *instHandle,
                                                  PWRM_Event   eventType)
{
    UInt32 hwiKey = 0x00;
    PWRM_NotifyResponse status = PWRM_NOTIFYDONE;

    assert(NULL != instHandle);

    hwiKey = Hwi_disable();

    /* check if both of the channels have any active IOP                      */
    if ((NULL == instHandle->rcvChanObj.activeIOP) &&
        (NULL == instHandle->xmtChanObj.activeIOP))
    {
        /* No IOP is pending currently. we can return the status of the       *
         * notify call as sucess                                              */
        instHandle->devState = UART_DRIVERSTATE_PWRM_SUSPEND;
        status = PWRM_NOTIFYDONE;
    }
    else
    {
        /* There are some IOPs pending,hence we will complete processing      *
         * of this request in the ISR context(task in case of polled mode)    *
         * by calling the delayed completion function                         */
        status = PWRM_NOTIFYNOTDONE;
        instHandle->pwrmInfo.ioSuspend = TRUE;
        instHandle->pwrmInfo.pwrmEvent = eventType;
    }

    Hwi_restore(hwiKey);
    return (status);
}

/**
 * \brief     This function calculates the constraints for a device at all
 *            the setpoints supported for the SOC. it then registers the
 *            appropriate contraints for each of the setpoints not supported.
 *
 * \param     instHandle [IN] Handle to the driver instance object
 *
 * \return    IOM_COMPLETED in case of success
 *            IOM_EBADMODE  in case of error
 *
 * \enter     instHandle is a NON null valid pointer
 */
static Int32 UartCalculateConstraints(Uart_Object *instHandle)
{
    Uns numberSetpoints        = 0x00;
    Uns setpoint               = 0x00;
    UInt32 prescale            = 0x00;
    UInt32 mask                = 0x00;
    Int32 status               = IOM_COMPLETED;
    PWRM_Constraint constraint = PWRM_DISALLOWEDSLEEPSTATE_MASK;
    PWRM_Status retVal         = PWRM_SOK;
    PWRM_Domain domain         = PWRM_CPU;

    assert(NULL != instHandle);

    /* check what clock domain is supported by the device                     */
    if (UART_PLLDOMAIN_0 == instHandle->pwrmInfo.pllDomain)
    {
        domain     = PWRM_CPU;
        constraint = PWRM_DISALLOWED_CPU_SETPOINT_MASK;
    }
    else
    {
        domain     = PWRM_PER;
        constraint = PWRM_DISALLOWED_PER_SETPOINT_MASK;
    }

    /* get the number of supported setpoint info for this instance            */
    retVal = PWRM_getNumSetpoints(domain, &numberSetpoints);

    if (PWRM_SOK == retVal)
    {
        /* calculate the contraints for the required bus frequency            */
        for (setpoint = 0x00; setpoint < numberSetpoints; setpoint++)
        {
            status = UartCalculateClockSettings(
                instHandle,
                setpoint,
                instHandle->devParams.baudRate,
                &prescale);

            if (IOM_COMPLETED == status)
            {
                if ((1 > prescale) || (prescale > 0xFFFFU))
                {
                    /* register the constraint for this setpoint              */
                    mask |= (1 << setpoint);
                }
            }
            else
            {
                retVal = PWRM_EINVALIDVALUE;
                break;
            }
        }

        /* check if this instance has already registered some constraint      *
         * if so then unregister those before registering the new             *
         * contraints(for CPU or PER event's unsupported DVFS only)           */
        if (PWRM_SOK == retVal)
        {
            if (NULL != instHandle->pwrmInfo.constraintHandle[constraint - 1])
            {
                retVal =
                    PWRM_unregisterConstraint(
                        instHandle->pwrmInfo.constraintHandle[constraint - 1]);
            }

            /* register the new set of constraints (only if any contraints    *
             * are present)                                                   */
            if ((PWRM_SOK == retVal) && (0 != mask))
            {
                /* store the value of the constraint mask being registered    */
                instHandle->pwrmInfo.constraintMask = mask;

                retVal =
                    PWRM_registerConstraint(
                        constraint,
                        mask,
                        &instHandle->pwrmInfo.constraintHandle[constraint - 1]);
            }
        }
    }

    if (PWRM_SOK != retVal)
    {
        /* failed in calculating the constraints                              */
        status = IOM_EBADMODE;
    }
    return (status);
}

/**
 * \brief      This function calculates clock settings for the new DVFS set
 *             point.
 *
 * \param      instHandle [IN] Handle to the device instance object
 * \param      eventArg1  [IN] previous set point.
 * \param      eventArg2  [IN] current set point
 *
 * \return     PWRM_SOK incase that the prescaler values for the new set point
 *             are calculated successfully else an appropriate error code is
 *             returned
 *
 * \enter      instHandle is a valid non NULL pointer
 *
 * \leave      Not imeplemented
 */
static PWRM_NotifyResponse UartConfigureNewVfSettings(Uart_Object *instHandle,
                                                      Uns          eventArg1,
                                                      Uns          eventArg2)
{
    UInt32 prescale = 0x00;
    PWRM_NotifyResponse retVal = PWRM_NOTIFYDONE;
    Int32 status = IOM_COMPLETED;

    /* This function will calculate the settings for the new set point and    *
     * also indicate if this is a valid setpoint                              */
    assert(NULL != instHandle);

    /* check if both the set points are not the same                          */
    if (eventArg1 != eventArg2)
    {
        /* The DVFS set point change has happened successfully.calculate the  *
         * new prescaler value                                                */
        status = UartCalculateClockSettings(
            instHandle,
            eventArg2,
            instHandle->devParams.baudRate,
            &prescale);

        if ((IOM_COMPLETED == status) &&
            ((1 <= prescale) && (prescale <= 0xFFFFU)))
        {
            /* calculation of the prescaler value is successful.Hence update  *
             * the hardware with the new prescaler values                     */
            status = UartConfigureNewClkSettings(instHandle, prescale);
        }
        else
        {
            status = IOM_EBADARGS;
        }
    }

    if (IOM_COMPLETED != status)
    {
        retVal = PWRM_NOTIFYERROR;
    }

    return (retVal);
}

/**
 * \brief     This function calculates the required prescaler values
 *            for the required ouput frequency for a given setpoint.
 *
 * \param     instHandle [IN]  Handle to the driver instance object
 * \param     setpoint   [IN]  setpoint for which the prescaler is calculated.
 * \param     opFreq     [IN]  desired module IO frequency
 * \param     prescale   [OUT] calculated prescaler value.
 *
 * \return    IOM_COMPLETED if the calculation is completed.
 *            IOM_EBADMODE  if the calcualtion failed for some reason.
 *
 * \enter     instHandle is a valid non null pointer
 *            prescalar is a non null pointer.
 *
 * \leave     Not implemented
 *
 * \note      Please note that the calculated prescaler values are not validated
 *            in this function.
 */
static Int32 UartCalculateClockSettings(Uart_Object  *instHandle,
                                        UInt32        setpoint,
                                        Uart_BaudRate opFreq,
                                        UInt32       *prescale)
{
    PWRM_Status retVal  = PWRM_SOK;
    PWRM_Domain domain  = PWRM_CPU;
    Uns numberSetpoints = 0x00;
    Uns frequency       = 0x00;
    Uns voltage         = 0x00;
    UInt32 sysclkDiv    = 0x00;
    Int32 status        = IOM_COMPLETED;

    assert((NULL != instHandle) && (NULL != prescale));

    /* check what clock domain is supported by the device                     */
    if (UART_PLLDOMAIN_0 == instHandle->pwrmInfo.pllDomain)
    {
        domain = PWRM_CPU;
    }
    else
    {
        domain = PWRM_PER;
    }

    /* get the number of supported setpoint info for this instance            */
    retVal = PWRM_getNumSetpoints(domain, &numberSetpoints);

    if (PWRM_SOK == retVal)
    {
        /* calculate the sysclk divisor value                                 */
        retVal = PWRM_getSetpointInfo(
            domain,
            (numberSetpoints - 1U),
            &frequency,
            &voltage);

        if (PWRM_SOK == retVal)
        {
            /* calculate the sysclk divisor value                             */
            sysclkDiv = ((frequency * 1000)
                         / instHandle->deviceInfo.inputFrequency);

            /* get the information about the current set point                */
            retVal = PWRM_getSetpointInfo(
                domain,
                setpoint,
                &frequency,
                &voltage);

            if (PWRM_SOK == retVal)
            {
                /* calculate the new prescaler values                         */
                (*prescale) = (((frequency * 1000) / sysclkDiv) /
                               ((UInt32) BSP_UART_BAUD_MULTIPLIER *
                                (UInt32) opFreq));
            }
        }
    }

    if (PWRM_SOK != retVal)
    {
        status = IOM_EBADMODE;
    }
    return (status);
}

/**
 * \brief     This function configures the Uart device with the new prescalar
 *            values.
 *
 * \param     instHandle [IN]  Handle to the driver instance object
 * \param     prescale   [IN]  prescaler value to program.
 *
 * \return    IOM_COMPLETED  if sucessful
 *            IOM_EBADARGS   in case of error
 *
 * \enter     instHandle is a valid non null pointer
 *            prescalar is a valid value
 *
 * \leave     Not implemented
 *
 */
static Int32 UartConfigureNewClkSettings(Uart_Object *instHandle,
                                         UInt32       prescale)
{
    Int32 status   = IOM_EBADARGS;
    UInt32 tempLcr = 0;

    assert(NULL != instHandle);

    /* switch on the module in the PRCM                                       */
    if (IOM_COMPLETED == Uart_localPrcmOn(instHandle))
    {
        UARTDivisorLatchWrite(
            (UInt32) instHandle->deviceInfo.baseAddress,
            (UInt32) prescale);

        /* switch off the module in PRCM                                      */
        status = Uart_localPrcmOff(instHandle);
    }

    return (status);
}

/**
 * \brief     This function unregisters all the constraints for the given device
 *            instance.
 *
 * \param     instHandle [IN]  Handle to the driver instance object
 *
 * \return    IOM_COMPLETED in case of success
 *            IOM_EBADMODE in case of failure
 *
 * \enter     instHandle is a valid non null pointer
 *
 * \leave     Not implemented
 */
static Int32 UartUnregisterConstraints(Uart_Object *instHandle)
{
    Int32 status       = IOM_COMPLETED;
    PWRM_Status retVal = PWRM_SOK;
    UInt32 count       = 0x00;

    assert(NULL != instHandle);

    for (count = 0; count < BSP_UART_MAX_PWRM_CONSTRAINTS; count++)
    {
        if (NULL != instHandle->pwrmInfo.constraintHandle[count])
        {
            retVal = PWRM_unregisterConstraint(
                instHandle->pwrmInfo.constraintHandle[count]);

            if (PWRM_SOK != retVal)
            {
                status = IOM_EBADMODE;
                break;
            }
            else
            {
                instHandle->pwrmInfo.constraintHandle[count] = 0x00;
            }
        }
    }
    return (status);
}

#endif
/* ========================================================================== */
/*                              END OF FILE                                   */
/* ========================================================================== */
