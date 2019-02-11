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
 *  \file   bsp_mcspi.c
 *
 *  \brief  IOM implementation for the McSPI device
 *
 *  This file implements the IOM for the McSPI device for SYS BIOS operating
 *  system
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <string.h>
#include <assert.h>

#include <xdc/std.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>

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

#include <ti/sysbios/family/arm/ducati/dm8148/IntMux.h>

#include <ti/drv/bsp_lld/mcspi/bsp_mcspi.h>
#include <bsp_mcspiPriv.h>
#include <ti/csl/csl_mcspi.h>
#include <ti/csl/soc.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#include <ti/drv/pm/pmhal.h>
/** @brief Base address of MCSPI memory mapped registers                      */
#define SOC_MCSPI0_REGS                    (SOC_MCSPI1_BASE)
#define SOC_MCSPI1_REGS                    (SOC_MCSPI2_BASE)
#define SOC_MCSPI2_REGS                    (SOC_MCSPI3_BASE)
#define SOC_MCSPI3_REGS                    (SOC_MCSPI4_BASE)
#endif

const Mcspi_Params        Mcspi_PARAMS = {
    0,
    /* instNum                */
    MCSPI_OPMODE_POLLED,
    /* opMode                 */
    16,
    /* hwiNumber              */
    FALSE,
    /* enableCache            */
    0,
    /* edma3EventQueue        */
    {
        MCSPI_COMMMODE_MASTER,
        /* masterOrSlave          */
        MCSPI_SINGLE_CHANNEL,
        /* singleOrMultiChEnable  */
        MCSPI_PINOPMODE_4PIN,
        /* pinOpModes             */
        1,
        /* fifoRxTrigLvl          */
        1,
        /* fifoTxTrigLvl          */
        {
            {
                MCSPI_LEN_8BIT,
                /* charLength                */
                FALSE,
                /* multiWordAccessEnable     */
                FALSE,
                /* spiChipSelectEnablePol    */
                MCSPI_MODE0,
                /* clockMode                 */
                0,
                /* clockRatioExtension       */
                MCSPI_NO_DELAY,
                /* spiWordInitDelay          */
                MCSPI_BOTH_RXTX,
                /* trasmitReceiveMode        */
                FALSE,
                /* granularityEnable         */
                3000000,
                /* busFreq                   */
                FALSE,
                /* spienHighPolarity         */
                MCSPI_SPIEN_0,
                /* slaveModeChipSelect       */
                MCSPI_IN,
                /* spiDat0Dir                */
                MCSPI_OUT,
                /* spiDat1Dir                */
            },
            {
                MCSPI_LEN_8BIT,
                /* charLength             */
                FALSE,
                /* multiWordAccessEnable  */
                TRUE,
                /* spiChipSelectEnablePol */
                MCSPI_MODE0,
                /* clockMode              */
                0,
                /* clockRatioExtension    */
                MCSPI_NO_DELAY,
                /* spiWordInitDelay       */
                MCSPI_BOTH_RXTX,
                /* trasmitReceiveMode     */
                FALSE,
                /* granularityEnable      */
                3000000,
                /* busFreq                */
                FALSE,
                /* spienHighPolarity      */
                MCSPI_SPIEN_0,
                /* slaveModeChipSelect    */
                MCSPI_IN,
                /* spiDat0Dir             */
                MCSPI_OUT,
                /* spiDat1Dir             */
            },
            {
                MCSPI_LEN_8BIT,
                /* charLength             */
                FALSE,
                /* multiWordAccessEnable  */
                TRUE,
                /* spiChipSelectEnablePol */
                MCSPI_MODE0,
                /* clockMode              */
                0,
                /* clockRatioExtension    */
                MCSPI_NO_DELAY,
                /* spiWordInitDelay       */
                MCSPI_BOTH_RXTX,
                /* trasmitReceiveMode     */
                FALSE,
                /* granularityEnable      */
                3000000,
                /* busFreq                */
                FALSE,
                /* spienHighPolarity      */
                MCSPI_SPIEN_0,
                /* slaveModeChipSelect    */
                MCSPI_IN,
                /* spiDat0Dir             */
                MCSPI_OUT,
                /* spiDat1Dir             */
            },
            {
                MCSPI_LEN_8BIT,
                /* charLength             */
                FALSE,
                /* multiWordAccessEnable  */
                TRUE,
                /* spiChipSelectEnablePol */
                MCSPI_MODE0,
                /* clockMode              */
                0,
                /* clockRatioExtension    */
                MCSPI_NO_DELAY,
                /* spiWordInitDelay       */
                MCSPI_BOTH_RXTX,
                /* trasmitReceiveMode     */
                FALSE,
                /* granularityEnable      */
                3000000,
                /* busFreq                */
                FALSE,
                /* spienHighPolarity      */
                MCSPI_SPIEN_0,
                /* slaveModeChipSelect    */
                MCSPI_IN,
                /* spiDat0Dir             */
                MCSPI_OUT,
                /* spiDat1Dir             */
            },
        },
    },
    FALSE,
    /* prcmPwrmEnable           */
    PLLDOMAIN_0,
    /* pllDomain                */
    0xffffffffU,
    /* polledModeTimeout        */
    0,
    /* prcmDevId                */
    FALSE
    /* enableErrIntr            */
};

/* ========================================================================== */
/*                       GLOBAL MODULE STATE                                  */
/* ========================================================================== */
/**
 *  \brief  Array which is part of Spi Module State
 */
static Bool               gMcspiModInUse[CSL_MCSPI_PER_CNT];
/**
 *  \brief  Spi Module State Object
 */
static Mcspi_Module_State Mcspi_module = {&gMcspiModInUse[0]};
/**
 *  \brief  Array of Spi instance State objects array
 */
static Mcspi_Object       Mcspi_Instances[CSL_MCSPI_PER_CNT];
/**
 *
 * \brief  structure Holding the information specific to an instance.
 */
static Mcspi_HwInfo       Mcspi_deviceInstInfo[CSL_MCSPI_PER_CNT];

/* ========================================================================== */
/*                     Debug function DECLARATION                             */
/* ========================================================================== */

static inline Void DBG_PRINT_ERR(const Char *a);

/* ========================================================================== */
/*                     Debug function DEFINITIONS                             */
/* ========================================================================== */

static inline Void DBG_PRINT_ERR(const Char *a)
{
    System_printf("*ERROR* Line: %d, File: %s - ", __LINE__, __FILE__);
    System_printf(a);
}

/* ========================================================================== */
/*                        GLOBAL VARIABLE                                     */
/* ========================================================================== */
/* This is maintained to create a linkin PaRam Set                            */
UInt32         Mcspi_edmaChanNum[MCSPI_MAX_CHAN_SUPPORTED];

/* ========================================================================== */
/*                        LOCAL FUNCTION PROTOTYPES                           */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static Int mcspiMdBindDev(Ptr *devp, Int devId, Ptr devParams);
static Int mcspiMdUnBindDev(Ptr devp);
static Int mcspiMdCreateChan(Ptr             *chanp,
                             Ptr              devp,
                             String           name,
                             Int              mode,
                             Ptr              chanParams,
                             IOM_TiomCallback cbFxn,
                             Ptr              cbArg);
static Int mcspiMdDeleteChan(Ptr chanp);
static Int mcspiMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket);
static Int mcspiMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArg);
#ifdef __cplusplus
}
#endif
const IOM_Fxns Mcspi_IOMFXNS =
{
    &mcspiMdBindDev,
    &mcspiMdUnBindDev,
    &mcspiMdControlChan,
    &mcspiMdCreateChan,
    &mcspiMdDeleteChan,
    &mcspiMdSubmitChan,
};

static Int32 mcspiSetupConfig(const Mcspi_Object  *instHandle,
                              const Mcspi_ChanObj *chanHandle,
                              Error_Block         *eb);
static Int32 mcspiChannelConf(Mcspi_Object        *instHandle,
                              const Mcspi_ChanObj *chanHandle,
                              Error_Block         *eb);
static Int mcspiTransfer(Mcspi_Object          *instHandle,
                         Mcspi_ChanObj         *chanHandle,
                         const Mcspi_DataParam *dataparam,
                         Error_Block           *eb);
static Int mcspiSlavePrime(Mcspi_Object          *instHandle,
                           Mcspi_ChanObj         *chanHandle,
                           const Mcspi_DataParam *dataparam);

static Int32 mcspiPolledModeTransfer(Mcspi_ChanObj *chanHandle, Error_Block *eb);
static Void mcspiRegisterIntrHandler(Int       instNum,
                                     UInt32    intNum,
                                     Mcspi_isr intIsr,
                                     Ptr       mcspiObj);
static Void mcspiUnregisterIntrHandler(Mcspi_Object *instHandle, UInt32 intNum);

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static Void mcspiIntrHandler(Ptr arg);
static Void mcspiSlaveIntrHandler(Ptr arg);
#ifdef __cplusplus
}
#endif

static Void mcspiCompleteIOInIsr(Mcspi_Object *instHandle);

static Void mcspiHandleErrors(Mcspi_Object  *instHandle,
                              Mcspi_ChanObj *chanHandle,
                              UInt32         intStatus);
static Void mcspiIoctl(Ptr            handle,
                       Mcspi_ioctlCmd cmd,
                       Ptr            cmdArg,
                       Ptr            param,
                       Error_Block   *eb);
static Void mcspiCancelAllIo(Mcspi_Object  *instHandle,
                             Mcspi_ChanObj *chanHandle);
static Void mcspiChIntrInit(const Mcspi_Object  *instHandle,
                            const Mcspi_ChanObj *chanHandle,
                            Bool                 enable);
static Bool mcspiCheckTimeOut(UInt32 startValue, UInt32 timeout);

static Int32 mcspiPolledOrInterruptTransferStart(Mcspi_Object  *instHandle,
                                                 Mcspi_ChanObj *chanHandle,
                                                 IOM_Packet    *ioPacket);
static Int32 mcspiSlaveTransferStart(Mcspi_Object  *instHandle,
                                     Mcspi_ChanObj *chanHandle,
                                     IOM_Packet    *ioPacket);
static void mcspiUpdateChanHandleFromIop(Mcspi_Object  *instHandle,
                                         Mcspi_ChanObj *chanHandle,
                                         IOM_Packet    *ioPacket);

static Void mcspiIntrStatus(const Mcspi_ChanObj *chanHandle,
                            const UInt32        *irqStatus,
                            UInt32              *txEmptyBits,
                            UInt32              *rxFullBits,
                            UInt32              *eowBit);

/* ========================================================================== */
/*                          FUNCTION DEFINTIONS                               */
/* ========================================================================== */

/* ========================================================================== */
/*                           MODULE FUNCTIONS                                 */
/* ========================================================================== */

/**
 *  \brief  Function called by Bios during instance initialisation
 *
 */
Void Mcspi_init(Void)
{
    Int i;

    for (i = (Int) 0; i < (Int) CSL_MCSPI_PER_CNT; i++)
    {
        /* have to initialize statically                                      */
        Mcspi_module.inUse[i] = (Bool) FALSE;
        memset((Void *) &Mcspi_Instances[i], (Int) 0x0, sizeof (Mcspi_Object));
    }

    /* Populating the Mcspi_deviceInstInfo structure */
    /* McSPI Instance 0*/
    Mcspi_deviceInstInfo[0].baseAddress    = (UInt32) SOC_MCSPI0_REGS;
    Mcspi_deviceInstInfo[0].cpuEventNumber =
        (UInt32) CSL_INTC_EVENTID_MCSPIINT0;
    Mcspi_deviceInstInfo[0].numOfPhyChannels =
        (UInt32) CSL_MCSPI_0_NumOfPhyChannels;
    Mcspi_deviceInstInfo[0].dmaEvtList[0].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI0_RX;
    Mcspi_deviceInstInfo[0].dmaEvtList[0].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI0_TX;
    Mcspi_deviceInstInfo[0].dmaEvtList[1].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA1_MCSPI0_RX;
    Mcspi_deviceInstInfo[0].dmaEvtList[1].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA1_MCSPI0_TX;
    Mcspi_deviceInstInfo[0].dmaEvtList[2].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA2_MCSPI0_RX;
    Mcspi_deviceInstInfo[0].dmaEvtList[2].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA2_MCSPI0_TX;
    Mcspi_deviceInstInfo[0].dmaEvtList[3].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA3_MCSPI0_RX;
    Mcspi_deviceInstInfo[0].dmaEvtList[3].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA3_MCSPI0_TX;
    Mcspi_deviceInstInfo[0].inputFrequency = (UInt32) CSL_MCSPI_0_MODULE_FREQ;

    Mcspi_deviceInstInfo[0].maxChipSelect = (UInt32) 0U;

    /* McSPI Instance 1 */
    Mcspi_deviceInstInfo[1].baseAddress    = (UInt32) SOC_MCSPI1_REGS;
    Mcspi_deviceInstInfo[1].cpuEventNumber =
        (UInt32) CSL_INTC_EVENTID_MCSPIINT1;
    Mcspi_deviceInstInfo[1].numOfPhyChannels =
        (UInt32) CSL_MCSPI_1_NumOfPhyChannels;
    Mcspi_deviceInstInfo[1].dmaEvtList[0].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI1_RX;
    Mcspi_deviceInstInfo[1].dmaEvtList[0].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI1_TX;
    Mcspi_deviceInstInfo[1].dmaEvtList[1].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA1_MCSPI1_RX;
    Mcspi_deviceInstInfo[1].dmaEvtList[1].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA1_MCSPI1_TX;
    /* The rx/tx event numbers '0xFFFF' are invalid                  */
    Mcspi_deviceInstInfo[1].dmaEvtList[2].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[1].dmaEvtList[2].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[1].dmaEvtList[3].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[1].dmaEvtList[3].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[1].inputFrequency = (UInt32) CSL_MCSPI_1_MODULE_FREQ;
    Mcspi_deviceInstInfo[1].maxChipSelect  = (UInt32) 0;

    /* McSPI Instance 2 */
    Mcspi_deviceInstInfo[2].baseAddress    = (UInt32) SOC_MCSPI2_REGS;
    Mcspi_deviceInstInfo[2].cpuEventNumber =
        (UInt32) CSL_INTC_EVENTID_MCSPIINT2;
    Mcspi_deviceInstInfo[2].numOfPhyChannels =
        (UInt32) CSL_MCSPI_2_NumOfPhyChannels;
    Mcspi_deviceInstInfo[2].dmaEvtList[0].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI2_RX;
    Mcspi_deviceInstInfo[2].dmaEvtList[0].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI2_TX;
    Mcspi_deviceInstInfo[2].dmaEvtList[1].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA1_MCSPI2_RX;
    Mcspi_deviceInstInfo[2].dmaEvtList[1].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA1_MCSPI2_TX;
    /* The rx/tx event numbers '0xFFFF' are invalid                  */
    Mcspi_deviceInstInfo[2].dmaEvtList[2].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[2].dmaEvtList[2].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[2].dmaEvtList[3].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[2].dmaEvtList[3].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[2].inputFrequency = (UInt32) CSL_MCSPI_2_MODULE_FREQ;
    Mcspi_deviceInstInfo[2].maxChipSelect  = (UInt32) 0;

    /* McSPI Instance 3 */
    Mcspi_deviceInstInfo[3].baseAddress    = (UInt32) SOC_MCSPI3_REGS;
    Mcspi_deviceInstInfo[3].cpuEventNumber =
        (UInt32) CSL_INTC_EVENTID_MCSPIINT3;
    Mcspi_deviceInstInfo[3].numOfPhyChannels =
        (UInt32) CSL_MCSPI_3_NumOfPhyChannels;
    Mcspi_deviceInstInfo[3].dmaEvtList[0].rxDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI3_RX;
    Mcspi_deviceInstInfo[3].dmaEvtList[0].txDmaEventNumber =
        (UInt32) CSL_EDMA3_CHA0_MCSPI3_TX;
    /* The rx/tx event numbers '0xFFFF' are invalid                  */
    Mcspi_deviceInstInfo[3].dmaEvtList[1].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[3].dmaEvtList[1].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[3].dmaEvtList[2].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[3].dmaEvtList[2].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[3].dmaEvtList[3].rxDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[3].dmaEvtList[3].txDmaEventNumber = (UInt32) 0xFFFF;
    Mcspi_deviceInstInfo[3].inputFrequency = (UInt32) CSL_MCSPI_3_MODULE_FREQ;
    Mcspi_deviceInstInfo[3].maxChipSelect  = (UInt32) 0;
}

/**
 *  \brief  Function called by Bios during instance initialisation
 *
 *
 *  \return IOM_COMPLETED    if success
 *          Error ID                 in case of error
 */
static Int mcspiMdBindDev(Ptr *devp, Int devId, Ptr devParams)
{
    Int32  status = IOM_COMPLETED;
    Mcspi_ChanObj      *chanHandle = NULL;
    const Mcspi_Params *params     = NULL;
    Mcspi_Object       *instHandle = NULL;
    UInt32 phyChCnt;
    UInt32 logChCnt;
    UInt32 i;

/* Begin parameter checking                                                   */
    if (((Int) CSL_MCSPI_PER_CNT <= devId) ||
        ((Bool) TRUE == Mcspi_module.inUse[devId]))
    {
        status = IOM_EBADARGS;
    }
/* End parameter checking                                                     */
    if (IOM_COMPLETED == status)
    {
        if (devParams == NULL)
        {
            params = &Mcspi_PARAMS;
        }
        else
        {
            params = (Mcspi_Params *) devParams;
        }

        if (params->instNum != devId)
        {
            status = IOM_EBADARGS;
        }
    }
    if (IOM_COMPLETED == status)
    {
        instHandle = &Mcspi_Instances[devId];
        Mcspi_module.inUse[devId] = (Bool) TRUE;

        /* set state to created  if validation and obj population is done     */
        instHandle->instNum         = params->instNum;
        instHandle->enableCache     = params->enableCache;
        instHandle->opMode          = params->opMode;
        instHandle->hwiNumber       = params->hwiNumber;
        instHandle->spiHWconfig     = params->spiHWCfgData;
        instHandle->edma3EventQueue = params->edma3EventQueue;

        /* To indicate whether the channel is openned in Single master
         * mode or not. Since any one of the channels can be openned in the
         * single master mode. Dynamic switching between the channels are not
         * supported
         */
        instHandle->isSingleChMasterMode = (Bool) FALSE;
        instHandle->polledModeTimeout    = params->polledModeTimeout;

        /* To indicate whether the channel is openned with FIFO enabled
         * or not, since any one of the 'n' channels can be openned with the
         * FIFO enabled option.
         */
        instHandle->isFifoEnabled        = (Bool) FALSE;
        instHandle->prcmPwrmEnable       = params->prcmPwrmEnable;
        instHandle->numOpens             = (UInt32) 0;
        instHandle->devState             = (Int32) MCSPI_DRIVERSTATE_CREATED;
        instHandle->dmaChanAllocated     = (Bool) FALSE;
        instHandle->currentActiveChannel = NULL;

        /* To indicate that the channel is openned in slave mode, since only
         * one channel can be openned in the slave mode i.e channel '0'
         */
        instHandle->isSlaveChannelOpened = (Bool) FALSE;

        instHandle->mcspiPwrmInfo.pllDomain       = params->pllDomain;
        instHandle->mcspiPwrmInfo.ioSuspend       = (Bool) FALSE;
        instHandle->mcspiPwrmInfo.constraintMask  = (UInt32) 0;
        instHandle->mcspiPwrmInfo.dependencyCount = (UInt32) 0;

        instHandle->hwiHandle = NULL;

        /* initialize Statistics members                                      */
        instHandle->stats.rxBytes          = (UInt32) 0;
        instHandle->stats.txBytes          = (UInt32) 0;
        instHandle->stats.pendingPacket    = (UInt32) 0;
        instHandle->stats.rxOverrunError   = (UInt32) 0;
        instHandle->stats.timeoutError     = (UInt32) 0;
        instHandle->stats.txUnderFlowError = (UInt32) 0;
        instHandle->stats.rxOverFlowError  = (UInt32) 0;

        instHandle->deviceInfo.baseAddress =
            Mcspi_deviceInstInfo[params->instNum].baseAddress;
        instHandle->deviceInfo.inputFrequency =
            Mcspi_deviceInstInfo[params->instNum].inputFrequency;
        instHandle->deviceInfo.cpuEventNumber =
            Mcspi_deviceInstInfo[params->instNum].cpuEventNumber;
        instHandle->numOfPhyChannels =
            Mcspi_deviceInstInfo[params->instNum].numOfPhyChannels;
        instHandle->deviceInfo.numOfPhyChannels =
            Mcspi_deviceInstInfo[params->instNum].numOfPhyChannels;
        instHandle->deviceInfo.baseAddress =
            Mcspi_deviceInstInfo[params->instNum].baseAddress;
#if (defined (TI814x_M3) || defined (C6A811x_M3))
        instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn  = (Bool) FALSE;
        instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped = (Uint8) 0xFF;
#endif
        /* This is redundant info, to get the dma events from the soc.xs      */
        for (i = (UInt32) 0; i < instHandle->numOfPhyChannels; i++)
        {
            instHandle->deviceInfo.dmaEvtList[i].rxDmaEventNumber =
                Mcspi_deviceInstInfo[params->instNum].
                dmaEvtList[i].rxDmaEventNumber;
            instHandle->deviceInfo.dmaEvtList[i].txDmaEventNumber =
                Mcspi_deviceInstInfo[params->instNum].
                dmaEvtList[i].txDmaEventNumber;
        }
        instHandle->deviceInfo.prcmInstance =
            Mcspi_deviceInstInfo[params->instNum].prcmInstance;
        instHandle->deviceInfo.pwrmPrcmId =
            Mcspi_deviceInstInfo[params->instNum].pwrmPrcmId;
        instHandle->deviceInfo.maxChipSelect =
            Mcspi_deviceInstInfo[params->instNum].maxChipSelect;

        /* The multi channel spi has got 4 - physical channel and
         * "MCSPI_NUM_LOG_CHANS" of logical channel
         */
        for (phyChCnt = (UInt32) 0; phyChCnt < instHandle->numOfPhyChannels;
             phyChCnt++)
        {
            for (logChCnt = (UInt32) 0; logChCnt < (UInt32) MCSPI_NUM_LOG_CHANS;
                 logChCnt++)
            {
                chanHandle = &instHandle->chanObj[phyChCnt]
                             [logChCnt];
                chanHandle->chanNum      = phyChCnt;
                chanHandle->cbFxn        = NULL;
                chanHandle->cbArg        = NULL;
                chanHandle->mode         = IOM_OUTPUT;
                chanHandle->instHandle   = NULL;
                chanHandle->channelState = (Int32) MCSPI_DRIVERSTATE_CLOSED;
                chanHandle->pendingState = (Bool) 0;
                chanHandle->abortAllIo   = (Bool) 0;
                chanHandle->currError    = (UInt32) 0;
                chanHandle->txBufFlag    = (Bool) FALSE;
                chanHandle->rxBufFlag    = (Bool) FALSE;
                chanHandle->txBufferLen  = (UInt32) 0;
                chanHandle->rxBufferLen  = (UInt32) 0;
                chanHandle->taskPriority = (UInt32) MAX_CHAN_PRIORITY;
                chanHandle->cfgChfmt     = params->spiHWCfgData.
                                           configChfmt[phyChCnt];

                /* The fifo trigger levels are not configured for the time
                 * being,
                 * am using default values.
                 */
                chanHandle->fifoEnable        = (Bool) FALSE;
                chanHandle->dmaEnable         = (Bool) FALSE;
                chanHandle->wordCntInFifoMode = (UInt32) 0;

                chanHandle->activeIOP           = NULL;
                chanHandle->dataParam.outBuffer = NULL;
                chanHandle->dataParam.inBuffer  = NULL;
                chanHandle->dataParam.bufLen    = (UInt32) 0;
                chanHandle->dataParam.flags     = (UInt32) 0;
                chanHandle->dataParam.param     = NULL;

                chanHandle->nextIop[0].iop         = NULL;
                chanHandle->nextIop[0].txBuffer    = NULL;
                chanHandle->nextIop[0].txBufferLen = 0;
                chanHandle->nextIop[0].txBufFlag   = (Bool) FALSE;
                chanHandle->nextIop[1].iop         = NULL;
                chanHandle->nextIop[1].txBuffer    = NULL;
                chanHandle->nextIop[1].txBufferLen = 0;
                chanHandle->nextIop[1].txBufFlag   = (Bool) FALSE;

                chanHandle->txBuffer           = NULL;
                chanHandle->rxBuffer           = NULL;
                chanHandle->taskPriority       = (UInt32) 1;
                chanHandle->txBufferLen        = (UInt32) 0;
                chanHandle->rxBufferLen        = (UInt32) 0;
                chanHandle->chipSelTimeControl = (Int32) MCSPI_CLK_CYCLE0;
                chanHandle->edmaCbCheck        = (UInt32) FALSE;
                chanHandle->enableErrIntr      = params->enableErrIntr;

                chanHandle->hEdma = NULL;

                /* The channel specific dma events are being populated here   */
                chanHandle->rxDmaEventNumber =
                    Mcspi_deviceInstInfo[params->instNum].
                    dmaEvtList[phyChCnt].rxDmaEventNumber;
                chanHandle->txDmaEventNumber =
                    Mcspi_deviceInstInfo[params->instNum].
                    dmaEvtList[phyChCnt].txDmaEventNumber;

                /* initialize the transceive buffers                          */
                memset(chanHandle->txTransBuf, 0x00,
                       sizeof (chanHandle->txTransBuf));
                memset(chanHandle->rxTransBuf, 0x00,
                       sizeof (chanHandle->rxTransBuf));
            }
        }
        *devp = (Ptr) instHandle;

        /* The semaphore needed for the syncronisation of the driver in the
         * POLLED mode will be created here.
         * A semaphore is need to synchronize the request for data transfer on a
         * single logical channel at a time.
         */
        if (MCSPI_OPMODE_POLLED == instHandle->opMode)
        {
            Semaphore_construct(&instHandle->syncSem, (Int32) 1, NULL);

            /* power management not supported for slave mode                  */
            if ((TRUE == instHandle->prcmPwrmEnable) &&
                (MCSPI_COMMMODE_SLAVE == instHandle->spiHWconfig.masterOrSlave))
            {
                status = IOM_EBADARGS;
            }
        }

        if ((IOM_COMPLETED == status) &&
            (FALSE == instHandle->prcmPwrmEnable))
        {
            /* power on using PRCM API                                        */
        }
    }
    return (status);
}

/**
 *  \brief  Function called by Bios during closing of the instance
 *
 *
 *  \return None
 */
static Int mcspiMdUnBindDev(Ptr devp)
{
    Int32         result     = IOM_COMPLETED;
    Mcspi_Object *instHandle = NULL;

/* Begin parameter checking                                                   */
    if (NULL == devp)
    {
        result = IOM_EBADARGS;
    }
    if (IOM_COMPLETED == result)
    {
        UInt32 instNum = ((Mcspi_Object *) devp)->instNum;
        if (CSL_MCSPI_PER_CNT <= instNum)
        {
            result = IOM_EBADARGS;
        }
    }
/* End parameter checking                                                     */

    if (IOM_COMPLETED == result)
    {
        instHandle = (Mcspi_Object *) devp;

        /* set driver state to deleted                                        */
        instHandle->numOpens = (UInt32) 0;
        instHandle->devState = (Int32) MCSPI_DRIVERSTATE_DELETED;
        Mcspi_module.inUse[instHandle->instNum] = (Bool) FALSE;

        if (FALSE == instHandle->prcmPwrmEnable)
        {
            /* power OFF using PSC API                                        */
        }
    }
    return ((Int) result);
}

/* ========================================================================== */
/*                              IOM FUNCTIONS                                 */
/* ========================================================================== */

/**
 *  \brief  Creates a communication channel in specified mode to communicate
 *          data between the application and the SPI device instance. This
 *          function sets the required hardware configurations for the data
 *          transactions.it returns configured channel handle to application.
 *          which will be used in all further transactions with the channel.
 *
 *          This function is called in response to a SIO_create call.
 *
 * \param     obj          [IN]     Spi driver object
 * \param     name         [IN]     Spi Instance name like Spi0
 * \param     mode         [IN]     channel  mode -> input or output
 * \param     chanParams   [IN]     channel parameters from user
 * \param     cbFxn        [IN]     callback function pointer
 * \param     cbArg        [IN]     callback function Arguments
 *
 * \return    channel handle in case of success
 *            NULL   in case of failure
 *
 */
static Int mcspiMdCreateChan(Ptr             *chanp,
                             Ptr              devp,
                             String           name,
                             Int              mode,
                             Ptr              chanParams,
                             IOM_TiomCallback cbFxn,
                             Ptr              cbArg)
{
    Mcspi_Object     *instHandle  = NULL;
    Mcspi_ChanObj    *chanHandle  = NULL;
    Mcspi_ChanParams *pChanParams = NULL;
    UInt32 hwiKey              = 0x00;
    UInt32 chanCount           = 0;
    Int32 status               = IOM_COMPLETED;
    Task_Handle       thisTask = NULL;
    UInt32 chanNum             = 0;

/* Begin parameter checking                                                   */
    if ((NULL == devp) || (NULL == cbFxn) || (NULL == cbArg) ||
        (NULL == chanParams))
    {
        status = IOM_EBADARGS;
    }
    else
    {
        instHandle = (Mcspi_Object *) devp;
    }
/* End parameter checking                                                     */

    if (IOM_COMPLETED == status)
    {
        /* To remove the compiler warnings                                    */
        if (NULL != name)
        {
            name = name;
        }

        pChanParams = (Mcspi_ChanParams *) chanParams;
        chanNum     = pChanParams->chanNum;

#if (defined (TI814x_M3) || defined (C6A811x_M3))

        if ((Bool) TRUE == pChanParams->crossBarEvtParam.isCrossBarIntEn)
        {
            instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn =
                pChanParams->crossBarEvtParam.isCrossBarIntEn;
            instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped =
                pChanParams->crossBarEvtParam.intNumToBeMapped;
        }
        else
        {
            instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn =
                (Bool) FALSE;
            instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped =
                (UInt8) 0xFF;
        }
#endif

        /* Power on the module                                            */
        Mcspi_localPrcmOn(instHandle, NULL);

        /* Get the channel handler from the 'instHandle' and channel number
         */
        for (chanCount = 0; chanCount < MCSPI_NUM_LOG_CHANS; chanCount++)
        {
            if (instHandle->chanObj[chanNum][chanCount].instHandle == NULL)
            {
                /* Assignment of channel                                  */
                chanHandle = &instHandle->chanObj[chanNum][chanCount];
                break;
            }
        }

        /* Check if channel is NULL                                       */
        if (NULL == chanHandle)
        {
            DBG_PRINT_ERR("Channel handle is NULL\r\n");
            status = IOM_EBADARGS;
        }
        else
        {
            /* update the instance Handle pointer                         */
            chanHandle->instHandle = (Ptr) instHandle;

            /* update the channel mode,callback function and args         */
            chanHandle->mode    = mode;
            chanHandle->cbFxn   = cbFxn;
            chanHandle->cbArg   = cbArg;
            chanHandle->chanNum = chanNum;

            /* The task priorities for the channels.                      */
            if (BIOS_ThreadType_Task == BIOS_getThreadType())
            {
                /* Returns a handle to the currently executing
                 * Task object();
                 */
                thisTask = Task_self();

                /* Get task priority( Task_Handle handle );               */
                chanHandle->taskPriority = Task_getPri(thisTask);
            }

            chanHandle->hEdma = pChanParams->hEdma;
            chanHandle->chipSelTimeControl =
                pChanParams->chipSelTimeControl;

            if (pChanParams->useAppSpecifiedDmaEvtNumbers == TRUE)
            {
                /* Update the dma channel numbers as specified by the app */
                chanHandle->rxDmaEventNumber = pChanParams->rxDmaEventNumber;
                chanHandle->txDmaEventNumber = pChanParams->txDmaEventNumber;
            }

            if (TRUE == instHandle->isSingleChMasterMode)
            {
                DBG_PRINT_ERR("This Instance is already opened in "
                              "single channel master mode  \r\n");
                status = IOM_EBADARGS;
            }

            if (IOM_COMPLETED == status)
            {
                if (((Bool) TRUE == instHandle->isFifoEnabled) &&
                    ((Bool) TRUE == pChanParams->fifoEnable))
                {
                    DBG_PRINT_ERR("FIFO is already being used, "
                                  "cannot open the channel\r\n");
                    status = IOM_EBADARGS;
                }
                else
                {
                    if (TRUE == pChanParams->fifoEnable)
                    {
                        instHandle->isFifoEnabled = (Bool) TRUE;
                    }
                    else
                    {
                        instHandle->isFifoEnabled = (Bool) FALSE;
                    }

                    chanHandle->fifoEnable = pChanParams->fifoEnable;

                    if (((Bool) TRUE == instHandle->isSingleChMasterMode) &&
                        ((UInt32) 0 != instHandle->numOpens))
                    {
                        DBG_PRINT_ERR(
                            "This instance is for single channel "
                            "master mode So can open only "
                            "one channel\r\n");
                        status = IOM_EBADARGS;
                    }
                    else
                    {
                        if ((MCSPI_MULTI_CHANNEL ==
                             instHandle->spiHWconfig.singleOrMultiChEnable)
                            &&
                            (TRUE == pChanParams->spiChipSelectHold))
                        {
                            DBG_PRINT_ERR("SPIEN hold (FORCE bit) is "
                                          "invalid in MULTI channel mode,"
                                          "cannot open the channel\r\n");
                            status = IOM_EBADARGS;
                        }
                        else
                        {
                            chanHandle->spiChipSelectHold =
                                pChanParams->spiChipSelectHold;
                        }

                        if (IOM_COMPLETED == status)
                        {
                            /* To aVoid hazardous behavior, it is advised to
                             * reset the module before changing from MASTER
                             * mode to SLAVE mode or from SLAVE mode to
                             * MASTER mode.
                             */

                            /* Since the communication mode cannot be
                             * changed dynamically (not supported), the
                             * below piece of code may not be useful at
                             * this time.
                             */
                            if (((TRUE ==
                                  instHandle->isSlaveChannelOpened) &&
                                 (MCSPI_COMMMODE_MASTER ==
                                  instHandle->spiHWconfig.masterOrSlave))
                                ||
                                ((FALSE ==
                                  instHandle->isSlaveChannelOpened) &&
                                 (MCSPI_COMMMODE_SLAVE ==
                                  instHandle->spiHWconfig.masterOrSlave)))
                            {
                                McSPIReset(
                                    (UInt32)
                                    instHandle->deviceInfo.
                                    baseAddress);
                            }

                            if (MCSPI_COMMMODE_SLAVE ==
                                instHandle->spiHWconfig.masterOrSlave)
                            {
                                if ((UInt32) 0 == chanNum)
                                {
                                    /* Since we donot support multi channel
                                     * slave and also only one logical
                                     * channel can be opened for slave mode
                                     */
                                    if ((Bool) FALSE ==
                                        instHandle->isSlaveChannelOpened)
                                    {
                                        instHandle->isSlaveChannelOpened =
                                            (Bool) TRUE;
                                    }
                                    else
                                    {
                                        DBG_PRINT_ERR(
                                            "Multi-channel is not"
                                            "supported in slave mode\r\n");
                                        status = IOM_EBADARGS;
                                    }
                                }
                                else
                                {
                                    /* Since only channel '0' can be used in
                                     * the slave mode
                                     */
                                    DBG_PRINT_ERR(
                                        "Only Channel 0 can be "
                                        "used in the slave mode\r\n");
                                    status = IOM_EBADARGS;
                                }
                            }
                            else
                            {
                                /* The request is for McSPI in Master mode*/
                            }

                            /* Update the hardware if it is first open    */
                            if ((IOM_COMPLETED == status) &&
                                (0 == instHandle->numOpens))
                            {
                                hwiKey = (UInt32) Hwi_disable();

                                if (MCSPI_OPMODE_POLLED !=
                                    instHandle->opMode)
                                {
                                    if ((MCSPI_COMMMODE_SLAVE ==
                                         instHandle->spiHWconfig.masterOrSlave)
                                        &&
                                        (instHandle->opMode ==
                                         MCSPI_OPMODE_INTERRUPT))
                                    {
                                        mcspiRegisterIntrHandler(
                                            instHandle->instNum,
                                            instHandle->deviceInfo.
                                            cpuEventNumber,
                                            mcspiSlaveIntrHandler,
                                            instHandle);
                                    }
                                    else
                                    {
                                        mcspiRegisterIntrHandler(
                                            instHandle->instNum,
                                            instHandle->deviceInfo.
                                            cpuEventNumber,
                                            mcspiIntrHandler,
                                            instHandle);
                                    }
                                }

                                if ((TRUE == MCSPI_EDMAENABLE) &&
                                    (MCSPI_OPMODE_DMAINTERRUPT ==
                                     instHandle->opMode))
                                {
                                    if (IOM_COMPLETED !=
                                        Mcspi_localSetupEdmaDuringOpen(
                                            chanHandle))
                                    {
                                        status = IOM_EBADARGS;
                                    }
                                }

                                if (IOM_COMPLETED == status)
                                {
                                    /* Reset the Mcspi module                 */
                                    McSPIReset(
                                        (UInt32)
                                        instHandle->deviceInfo.
                                        baseAddress);

                                    /* Initialize hardware                */
                                    status = mcspiSetupConfig(instHandle,
                                                              chanHandle,
                                                              NULL);
                                }

                                /* restore the interrupts                 */
                                Hwi_restore(hwiKey);
                            }

                            /* The channel parameters are being set here,
                             * but channel is being enabled if FIFO is
                             * disabled, otherwise channel is not enabled.
                             */
                            if (IOM_COMPLETED == status)
                            {
                                if (MCSPI_DRIVERSTATE_OPENED !=
                                    chanHandle->channelState)
                                {
                                    status = mcspiChannelConf(instHandle,
                                                              chanHandle,
                                                              NULL);
                                }
                                else
                                {
                                    DBG_PRINT_ERR(
                                        "This Channel is already "
                                        "in use \r\n");
                                    status = IOM_EBADARGS;
                                }
                            }

                            if (IOM_COMPLETED == status)
                            {
                                Queue_construct(
                                    &(chanHandle->queuePendingList), NULL);
                                if ((TRUE == MCSPI_EDMAENABLE) &&
                                    (MCSPI_OPMODE_DMAINTERRUPT ==
                                     instHandle->opMode))
                                {
                                    Queue_construct(
                                        &(chanHandle->queueFloatingList),
                                        NULL);
                                }
                            }
                        }
                    }
                }
            }
        }
        Mcspi_localPrcmOff(instHandle, NULL);
    }

    if (IOM_COMPLETED == status)
    {
        /* Increment open count and return driver handle                      */
        ++instHandle->numOpens;
        chanHandle->channelState = (Int32) MCSPI_DRIVERSTATE_OPENED;
        *chanp = (Ptr) chanHandle;
    }
    else
    {
        /* channel opening failed                                            */
        *chanp = NULL;
    }

    return ((Int) status);
}

/**
 *  \brief    This function is called by the application to close a previously
 *            opened channel.it deletes the channel so that it is not available
 *            for further transactions. All the allocated reqources are freed &
 *            the channel will be ready for the "open" operation once again.
 *
 *  \param    instHandle [IN]   Mcspi driver structure
 *            chanp      [IN]   Handle to the channel.
 *            eb         [OUT]  pointer to the error information block.
 *
 *  \return   None
 */
static Int mcspiMdDeleteChan(Ptr chanp)
{
    Mcspi_Object  *instHandle;
    Mcspi_ChanObj *chanHandle = NULL;
    Int32          status     = IOM_COMPLETED;

/* Begin parameter checking                                                   */
    if (NULL == chanp)
    {
        status = IOM_EBADARGS;
    }
    else if ((NULL == ((Mcspi_ChanObj *) chanp)->instHandle) ||
             (MCSPI_DRIVERSTATE_OPENED !=
              ((Mcspi_ChanObj *) chanp)->channelState))
    {
        status = IOM_EBADARGS;
    }
    else
    {
        chanHandle = (Mcspi_ChanObj *) chanp;
        if (NULL != chanHandle->instHandle)
        {
            instHandle = (Mcspi_Object *) chanHandle->instHandle;
        }
        else
        {
            status = IOM_EBADARGS;
        }
    }

/* End parameter checking                                                     */

    if (IOM_COMPLETED == status)
    {
        Mcspi_ChanObj *pchanHandle = NULL;
        pchanHandle = (Mcspi_ChanObj *) chanp;

        /* check if the channel is already open so that it can be closed      */
        if ((NULL == pchanHandle->instHandle)
            || (MCSPI_DRIVERSTATE_OPENED != pchanHandle->channelState))
        {
            status = IOM_EBADMODE;
        }
        else
        {
            UInt32 hwintKey = (UInt32) 0;

            /*  Check for any IO is pending, if yes then cancel io            */
            if ((Bool) TRUE == pchanHandle->pendingState)
            {
                mcspiIoctl(pchanHandle, IOCTL_MCSPI_CANCEL_PENDING_IO, NULL,
                           NULL, NULL);
            }

            /* disable the global interrupts                                  */
            hwintKey = Hwi_disable();

            /* decrement the number of open channels as we are closing the
             * channel
             */
            --instHandle->numOpens;

            /* enable the global interrupts                                   */
            Hwi_restore(hwintKey);

            if ((UInt32) 0 == instHandle->numOpens)
            {
                /* All the channels are closed hence unregister the
                 * interrupts
                 */
                if (instHandle->opMode != MCSPI_OPMODE_POLLED)
                {
                    mcspiUnregisterIntrHandler(
                        instHandle,
                        instHandle->deviceInfo.cpuEventNumber);
                }

                if ((TRUE == MCSPI_EDMAENABLE)
                    && (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode))
                {
                    UInt32 linkCnt = (UInt32) 0x00;

                    /* Disable the current transfer to make sure that
                     * there is no running EDMA transfer taking place         */
                    if (IOM_COMPLETED == status)
                    {
                        status = (Int32) EDMA3_DRV_disableTransfer(
                            chanHandle->hEdma,
                            instHandle->deviceInfo.
                            dmaEvtList[pchanHandle->chanNum].rxDmaEventNumber,
                            EDMA3_DRV_TRIG_MODE_EVENT);
                    }
                    if (IOM_COMPLETED == status)
                    {
                        status = (Int32) EDMA3_DRV_disableTransfer(
                            chanHandle->hEdma,
                            instHandle->deviceInfo.
                            dmaEvtList[pchanHandle->chanNum].txDmaEventNumber,
                            EDMA3_DRV_TRIG_MODE_EVENT);
                    }
                    if (IOM_COMPLETED == status)
                    {
                        status = EDMA3_DRV_freeChannel(
                            pchanHandle->hEdma,
                            instHandle->deviceInfo.
                            dmaEvtList[pchanHandle->chanNum].rxDmaEventNumber);
                    }
                    if (IOM_COMPLETED == status)
                    {
                        status = EDMA3_DRV_freeChannel(
                            pchanHandle->hEdma,
                            instHandle->deviceInfo.
                            dmaEvtList[pchanHandle->chanNum].txDmaEventNumber);
                    }
                    else
                    {
                        status = IOM_EBADARGS;
                    }

                    if (IOM_COMPLETED == status)
                    {
                        status = EDMA3_DRV_freeChannel(pchanHandle->hEdma,
                                                       Mcspi_edmaChanNum[
                                                           pchanHandle->
                                                           chanNum]);
                    }

                    if (IOM_COMPLETED == status)
                    {
                        /* free the EDMA PaRAM entries used for Pingpong
                         * buffering */
                        for (linkCnt = (UInt32) 0; linkCnt < MCSPI_MAXLINKCNT;
                             linkCnt++)
                        {
                            if (IOM_COMPLETED == status)
                            {
                                status = EDMA3_DRV_freeChannel(
                                    pchanHandle->hEdma,
                                    pchanHandle->pramTblRx[linkCnt]);
                            }
                            else
                            {
                                status = IOM_EBADARGS;
                            }
                            if (IOM_COMPLETED == status)
                            {
                                status = EDMA3_DRV_freeChannel(
                                    pchanHandle->hEdma,
                                    pchanHandle->pramTblTx[linkCnt]);
                            }
                            else
                            {
                                status = IOM_EBADARGS;
                                break;
                            }
                        }
                    }
                }

                if (IOM_COMPLETED == status)
                {
                    /* Disable the channels                                   */
                    McSPIChannelDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
                    if ((Bool) TRUE == chanHandle->spiChipSelectHold)
                    {
                        McSPICSDeAssert(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }
                }
            }
            if (IOM_COMPLETED == status)
            {
                instHandle->isFifoEnabled        = (Bool) FALSE;
                instHandle->isSingleChMasterMode = (Bool) FALSE;

                instHandle->isSlaveChannelOpened = (Bool) FALSE;
                pchanHandle->instHandle          = NULL;

                /* Reset the state variables                                  */
                pchanHandle->cbFxn        = NULL;
                pchanHandle->cbArg        = NULL;
                pchanHandle->mode         = IOM_OUTPUT;
                pchanHandle->pendingState = (Bool) FALSE;
                pchanHandle->abortAllIo   = (Bool) FALSE;
                pchanHandle->currError    = (Int32) 0;
                pchanHandle->txBufFlag    = (Bool) FALSE;
                pchanHandle->rxBufFlag    = (Bool) FALSE;
                pchanHandle->txBufferLen  = (UInt32) 0;
                pchanHandle->rxBufferLen  = (UInt32) 0;
                pchanHandle->hEdma        = NULL;
                pchanHandle->submitCount  = (Int32) 0x00;

                /* reset the channel priority                                 */
                pchanHandle->taskPriority = (UInt32) MAX_CHAN_PRIORITY;

                /* Updated the driver state                                   */
                pchanHandle->channelState = (Int32) MCSPI_DRIVERSTATE_CLOSED;

                /* Intialise the transceive buffers                           */
                memset(pchanHandle->txTransBuf, 0x00,
                       sizeof (pchanHandle->txTransBuf));
                memset(pchanHandle->rxTransBuf, 0x00,
                       sizeof (pchanHandle->rxTransBuf));
            }
        }
    }
    return ((Int) status);
}

/**
 *  \brief    Submit a I/O packet to a channel for processing
 *
 *   The GIO layer calls this function to cause the mini-driver
 *   to process the IOM_Packet for read/write operations.
 *
 *  \param   instHandle [IN]  Spi driver structure pointer
 *  \param   chanp      [IN]  Handle to the channel
 *  \param   ioPacket   [IN]  Pointer to packet to be submitted
 *  \Param   eb         [OUT] error block
 *
 *  \return  IOM_COMPLETED, if packet is fully processed
 *           IOM_PENDING,   if packet is not fully processed
 *           IOM_EBADIO      if error in processing
 */
static Int mcspiMdSubmitChan(Ptr chanp, IOM_Packet *ioPacket)
{
    Mcspi_Object    *instHandle = NULL;
    Mcspi_ChanObj   *chanHandle = NULL;
    Mcspi_DataParam *dataparam  = NULL;
    UInt32           hwiKey     = (UInt32) 0x00;
    Int32 status = IOM_COMPLETED;
    Void *tempCastIoPtr;
    IOM_Packet      *ioPacketProcess = NULL;

/* Begin parameter checking                                                   */
    if ((NULL == chanp) || (NULL == ioPacket) || (NULL == ioPacket->addr))
    {
        status = IOM_EBADARGS;
    }
    else if ((IOM_ABORT == ioPacket->cmd) || (IOM_FLUSH == ioPacket->cmd))
    {
        status = IOM_EBADARGS;
        DBG_PRINT_ERR("IOM_ABORT and IOM_FLUSH not supported\r\n");
    }
    else if ((IOM_READ != ioPacket->cmd) && (IOM_WRITE != ioPacket->cmd))
    {
        status = IOM_EBADARGS;
    }
    else
    {
        chanHandle = (Mcspi_ChanObj *) chanp;
        if (NULL != chanHandle)
        {
            instHandle = (Mcspi_Object *) chanHandle->instHandle;

            if (NULL == instHandle)
            {
                status = IOM_EBADARGS;
            }
        }

        if ((IOM_ABORT != ioPacket->cmd) && (IOM_FLUSH != ioPacket->cmd))
        {
            dataparam = (Mcspi_DataParam *) ioPacket->addr;
        }
    }
/* End parameter checking                                                     */

    if (IOM_COMPLETED == status)
    {
        /* Validate the packet send by the user                           */
        if ((ioPacket->cmd == IOM_READ)
            || (ioPacket->cmd == IOM_WRITE))
        {
            if (ioPacket->addr == NULL)
            {
                status = IOM_EBADARGS;
            }
        }

        if (IOM_COMPLETED == status)
        {
            dataparam = (Mcspi_DataParam *) ioPacket->addr;

            /* obtain the Handle to the channel                           */
            chanHandle = (Mcspi_ChanObj *) chanp;

            /* Validating State of the channel                            */
            if (MCSPI_DRIVERSTATE_OPENED != chanHandle->channelState)
            {
                status = IOM_EBADARGS;
            }
            else
            {
                if ((NULL == dataparam->outBuffer) &&
                    (NULL == dataparam->inBuffer))
                {
                    status = IOM_EBADARGS;
                }
                else
                {
                    if (dataparam->bufLen == 0)
                    {
                        status = IOM_EBADARGS;
                    }

                    if (IOM_COMPLETED == status)
                    {
                        /* if the transfer is in DMA mode                 */
                        if ((TRUE == MCSPI_EDMAENABLE) &&
                            (MCSPI_OPMODE_DMAINTERRUPT ==
                             instHandle->opMode))
                        {
                            /* Validate the buffer alignment if mode is DMA
                             */
                            if (((UInt32) 0 !=
                                 (((UInt32) dataparam->outBuffer) %
                                  (UInt32) 32)) ||
                                ((UInt32) 0 !=
                                 (((UInt32) dataparam->inBuffer) %
                                  (UInt32) 32)))
                            {
                                status = IOM_EBADARGS;
                            }
                        }

                        /* check for zero '0' timeout in polled mode */
                        if ((IOM_COMPLETED == status) &&
                            (0 == instHandle->polledModeTimeout) &&
                            (MCSPI_OPMODE_POLLED == instHandle->opMode))
                        {
                            status = IOM_EBADARGS;
                        }

                        /* call the power ON function to switch on the
                         * module in PRCM
                         */
                        Mcspi_localPrcmOn(instHandle, NULL);

                        if (IOM_COMPLETED == status)
                        {
                            /* protect the "currentActiveChannel"     */
                            hwiKey = Hwi_disable();

                            /* check whether to process the packet or
                             * queue it up
                             */
                            if ((NULL ==
                                 instHandle->currentActiveChannel) &&
                                (MCSPI_DRIVERSTATE_PWRM_SUSPEND !=
                                 instHandle->devState))
                            {
                                if ((MCSPI_COMMMODE_SLAVE ==
                                     instHandle->spiHWconfig.masterOrSlave) &&
                                    (instHandle->opMode ==
                                     MCSPI_OPMODE_INTERRUPT))
                                {
                                    if ((Bool) TRUE ==
                                        Queue_empty(Queue_handle(&(chanHandle->
                                                                   queuePendingList))))
                                    {
                                        /* This is the first buffer just prime
                                         *this */
                                        tempCastIoPtr = (Void *) ioPacket;
                                        Queue_put(Queue_handle(
                                                      &(chanHandle->
                                                        queuePendingList)),
                                                  (Queue_Elem *) tempCastIoPtr);
                                        ioPacketProcess = NULL;
                                        status          = IOM_PENDING;
                                        Hwi_restore(hwiKey);
                                    }
                                    else
                                    {
                                        /* This is the not the first buffer.
                                         * Put current packet in queue. */
                                        tempCastIoPtr = (Void *) ioPacket;
                                        Queue_put(Queue_handle(
                                                      &(chanHandle->
                                                        queuePendingList)),
                                                  (Queue_Elem *) tempCastIoPtr);
                                        /* Get the top element in queue. */
                                        ioPacketProcess =
                                            (IOM_Packet *) Queue_get(
                                                Queue_handle(&(
                                                                 chanHandle
                                                                 ->
                                                                 queuePendingList)));

                                        instHandle->currentActiveChannel =
                                            (Mcspi_ChanObj *) chanHandle;
                                        Hwi_restore(hwiKey);
                                        status = mcspiSlaveTransferStart(
                                            instHandle, chanHandle,
                                            ioPacketProcess);
                                    }
                                }
                                else
                                {
                                    ioPacketProcess = ioPacket;
                                    instHandle->currentActiveChannel =
                                        (Mcspi_ChanObj *) chanHandle;

                                    /* critical section ends              */
                                    Hwi_restore(hwiKey);

                                    /* There is no current active packet in
                                     * the
                                     * driver hence we can load this request
                                     * directly
                                     */
                                    if (MCSPI_OPMODE_DMAINTERRUPT !=
                                        instHandle->opMode)
                                    {
                                        status =
                                            mcspiPolledOrInterruptTransferStart(
                                                instHandle,
                                                chanHandle,
                                                ioPacketProcess);
                                    }
                                    else
                                    {
                                        status =
                                            mcspiEdmaModeTransfer(
                                                instHandle,
                                                chanHandle,
                                                ioPacketProcess);
                                    }
                                }
                            }
                            else
                            {
                                /* This means some IO from some channel
                                 * is
                                 * in progress we may need to queue the
                                 * request in pending queue for this
                                 * channel
                                 * once the control comes to the
                                 * completion
                                 * of the current IO, the queue will be
                                 * processed and this IO will be
                                 * programmed
                                 * in the priority based implementation,
                                 * please note that only the channel
                                 * that
                                 * was created from the task with high
                                 * priority would be processed first
                                 */
                                if (MCSPI_OPMODE_POLLED !=
                                    chanHandle->channelState)
                                {
                                    tempCastIoPtr = (Void *) ioPacket;
                                    Queue_put(Queue_handle(&(chanHandle
                                                             ->
                                                             queuePendingList)),
                                              (Queue_Elem *) tempCastIoPtr);

                                    instHandle->stats.pendingPacket++;
                                    status = IOM_PENDING;
                                }
                                else
                                {
                                    /* polled mode does not support
                                     * queuing of packets
                                     */
                                    status = IOM_EBADMODE;
                                }
                                /* end critical section
                                 *                  */
                                Hwi_restore(hwiKey);
                            }
                        }
                    }
                }
            }
        }
    }

    if (IOM_COMPLETED == status)
    {
        /* if it is polled mode of operation we will power off the module     *
         * after every IOP.Hence power off the module                         */
        if (MCSPI_OPMODE_POLLED == instHandle->opMode)
        {
            Mcspi_localPrcmOff(instHandle, NULL);
        }
    }
    else if (IOM_PENDING == status)
    {
        status = IOM_PENDING;
    }
    else
    {
        if (instHandle != NULL)
        {
            Mcspi_localPrcmOff(instHandle, NULL);
        }
        status = IOM_EBADIO;
    }
    return ((Int) status);
}

/**
 *  \brief   This function executes a control command passed by the application
 *
 *   The application's request for a IOCTL to be executed is routed here by the
 *   stream. if the command is supported then the control command is executed.
 *
 *  \param    instHandle [IN]    Mcspi driver structure
 *  \param    chanp      [IN]    Channel handle
 *  \param    cmd        [IN]    control command given by the application
 *  \param    cmdArgs    [IN]    Optional args required for command execution
 *  \param    eb         [OUT]   error block
 *
 *  \return   None
 */
static Int mcspiMdControlChan(Ptr chanp, Uns cmd, Ptr cmdArg)
{
    Mcspi_ChanObj *chanHandle = NULL;
    Int32          status     = IOM_COMPLETED;

/* Begin parameter checking                                                   */
    if (NULL == chanp)
    {
        /* invalid params have been detected                                  */
        status = IOM_EBADARGS;
    }
    else
    {
        chanHandle = (Mcspi_ChanObj *) chanp;

        if (MCSPI_DRIVERSTATE_OPENED != chanHandle->channelState)
        {
            status = IOM_EBADARGS;
        }
    }

/* End parameter checking                                                     */

    if (IOM_COMPLETED == status)
    {
        /* call the function to execute the control commands              */
        mcspiIoctl(chanHandle, (Mcspi_ioctlCmd) cmd, (Ptr) cmdArg, NULL, NULL);
    }

    return ((Int) status);
}

/* ========================================================================== */
/*                            LOCAL  FUNCTIONS                                */
/* ========================================================================== */

/**
 *  \brief  This function Updates current Buffer to program EDMA.
 *
 *  \param  chanHandle [IN]  Handle to channel.
 *  \param  ioPacket   [IN]  pointer to the ioPacket
 *
 *  \return None
 *
 *  \enter  Not implemented
 *
 *  \leave  Not implemented
 */

Void Mcspi_UpdateBuffToPrgmEdma(Mcspi_ChanObj    *chanHandle,
                                const IOM_Packet *ioPacket)
{
    Mcspi_DataParam *dataparam = NULL;
    UInt32           tempCastBuffer;

    dataparam = (Mcspi_DataParam *) ioPacket->addr;

    assert(NULL != dataparam);

    /* Check if the inBuffer or the outBuffer is NULL i.e,not supplied and
     * update respective buffer appropriately with driver buffer */
    if (NULL == dataparam->inBuffer)
    {
        /* user has not suppiled the IN buffer */
        chanHandle->rxBufFlag = (Bool) FALSE;

        /* align the buffer in case of edma mode only */
        tempCastBuffer = (((UInt32) & chanHandle->rxTransBuf[0]) +
                          (UInt32) (0x1F)) & (UInt32) 0xFFFFFFE0U;
        chanHandle->rxBuffer = (UInt8 *) (tempCastBuffer);

        /* update the details of the out buffer here as it cannot be NULL
         * (condition already checked) */
        chanHandle->txBufFlag   = (Bool) TRUE;
        chanHandle->txBuffer    = dataparam->outBuffer;
        chanHandle->rxBufferLen = dataparam->bufLen;
        chanHandle->txBufferLen = dataparam->bufLen;
    }
    else if (NULL == dataparam->outBuffer)
    {
        /* user has not suppiled the IN buffer*/
        chanHandle->txBufFlag = (Bool) FALSE;

        /* align the buffer in case of edma mode only */
        tempCastBuffer = (((UInt32) & chanHandle->txTransBuf[0]) +
                          (UInt32) (0x1F)) & (UInt32) 0xFFFFFFE0U;
        chanHandle->txBuffer = (UInt8 *) (tempCastBuffer);

        /* update the details of the "inbuffer" here as it cannot be NULL
         * (condition already checked) */
        chanHandle->rxBufFlag   = (Bool) TRUE;
        chanHandle->rxBuffer    = dataparam->inBuffer;
        chanHandle->rxBufferLen = dataparam->bufLen;
        chanHandle->txBufferLen = dataparam->bufLen;
    }
    else
    {
        /* Both the buffers are valid         */
        chanHandle->rxBufFlag   = (Bool) TRUE;
        chanHandle->txBufFlag   = (Bool) TRUE;
        chanHandle->rxBuffer    = dataparam->inBuffer;
        chanHandle->txBuffer    = dataparam->outBuffer;
        chanHandle->rxBufferLen = dataparam->bufLen;
        chanHandle->txBufferLen = dataparam->bufLen;
    }
}

/**
 *  \brief  This function loads the packets to the actual EDMA paramset.
 *
 *  \param  chanHandle [IN]  Handle to channel.
 *  \param  ioPacket   [IN]  pointer to the ioPacket
 *
 *  \return None
 *
 *  \enter  Not implemented
 *
 *  \leave  Not implemented
 */

Void Mcspi_localLoadPktToEdma(Mcspi_ChanObj    *chanHandle,
                              const IOM_Packet *ioPacket)
{
    Mcspi_Object *instHandle    = NULL;
    Int32         status        = IOM_COMPLETED;
    Bool          falseWhile    = (Bool) TRUE;
    UInt16        tempRxTrigLvl = 0;
    UInt16        tempTxTrigLvl = 0;
    UInt32        numSpiWords   = 0;

    assert(NULL != chanHandle);
    assert(NULL != ioPacket);

    instHandle = (Mcspi_Object *) chanHandle->instHandle;
    assert(NULL != instHandle);

    tempRxTrigLvl = instHandle->spiHWconfig.fifoRxTrigLvl;
    tempTxTrigLvl = instHandle->spiHWconfig.fifoTxTrigLvl;

    do
    {
        falseWhile = (Bool) FALSE;

        status = Mcspi_localUpdtDtPktToLnkPrms(chanHandle, ioPacket);

        if (IOM_COMPLETED != status)
        {
            status = IOM_EBADIO;
            break;
        }

        chanHandle->nextLinkParamSetToBeUpdated = (UInt32) 0;

/***************************** Program FIFO Configuration *********************/
        /* write 'chanHandle->rxBufferLen' to the MCSPI_XFERLEVEL[WCNT]
         * register, right now, maximum of 4 bytes are programmed. Once
         * this works, then can try with the more number of bytes
         * (like 32 bytes)
         */
        if (TRUE == chanHandle->fifoEnable)
        {
            if (chanHandle->cfgChfmt.charLength <= 8)
            {
                numSpiWords = chanHandle->rxBufferLen;
                if (tempRxTrigLvl < (UInt16) 1)
                {
                    tempRxTrigLvl = (UInt16) 1;
                }
                if (tempTxTrigLvl < (UInt16) 1)
                {
                    tempTxTrigLvl = (UInt16) 1;
                }
            }
            else if (chanHandle->cfgChfmt.charLength <= 16)
            {
                numSpiWords = chanHandle->rxBufferLen / (UInt32) 2;
                if (tempRxTrigLvl < (UInt16) 2)
                {
                    tempRxTrigLvl = (UInt16) 2;
                }
                if (tempTxTrigLvl < (UInt16) 2)
                {
                    tempTxTrigLvl = (UInt16) 2;
                }
            }
            else if (chanHandle->cfgChfmt.charLength <= 32)
            {
                numSpiWords = chanHandle->rxBufferLen / (UInt32) 4;
                if (tempRxTrigLvl < (UInt16) 4)
                {
                    tempRxTrigLvl = (UInt16) 4;
                }
                if (tempTxTrigLvl < (UInt16) 4)
                {
                    tempTxTrigLvl = (UInt16) 4;
                }
            }
            else
            {
                /* Do Nothing */
            }
            if (TRUE == chanHandle->rxBufFlag)
            {
                McSPIWordCountSet(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt16) numSpiWords);
            }
            McSPIFIFOTrigLvlSet(
                (UInt32) instHandle->deviceInfo.baseAddress,
                (UInt8) tempRxTrigLvl,
                (UInt8) tempTxTrigLvl,
                (UInt32) chanHandle->cfgChfmt.
                trasmitReceiveMode);
        }
        else
        {
            /* Do nothing */
        }

/***************************** Program the RX side ****************************/
        /* This is the first packet. we would have update the main params *
         * with the ioPacket. we will now just start the transfer so that *
         * the packet is transferred                                      */
        status = EDMA3_DRV_enableTransfer(chanHandle->hEdma,
                                          chanHandle->rxDmaEventNumber,
                                          EDMA3_DRV_TRIG_MODE_EVENT);

        if (IOM_COMPLETED != status)
        {
            System_printf("\r\nSPI Test: EDMA Transfer Enable failed");
        }

/***************************** Program the TX side ****************************/
        status = EDMA3_DRV_enableTransfer((chanHandle->hEdma),
                                          chanHandle->txDmaEventNumber,
                                          EDMA3_DRV_TRIG_MODE_EVENT);

        if (IOM_COMPLETED != status)
        {
            System_printf("SPI Test: EDMA Transfer Enable failed\r\n");
        }

/********************************* Enable SPI EDMA ****************************/

        /* Enable the FIFO */
        if (TRUE == chanHandle->fifoEnable)
        {
            McSPIRxFIFOConfig(
                (UInt32) instHandle->deviceInfo.baseAddress,
                (UInt32) MCSPI_RX_FIFO_ENABLE,
                chanHandle->chanNum);

            McSPITxFIFOConfig(
                (UInt32) instHandle->deviceInfo.baseAddress,
                (UInt32) MCSPI_TX_FIFO_ENABLE,
                chanHandle->chanNum);
        }
        /* Enable McSPI DMA for transaction
         * MCSPI_CH(chanNum)CONF -> DMAR bit for receive DMA
         */
        McSPIDMAEnable((UInt32) instHandle->deviceInfo.baseAddress,
                       ((UInt32) MCSPI_DMA_RX_EVENT |
                        (UInt32) MCSPI_DMA_TX_EVENT),
                       chanHandle->chanNum);
        /* In case of FIFO enable, the XFERLEVEL will be programmed. The channel
         * needs to be enabled only after programming the XFERLEVEL. Because of
         * this the channel is enabled here */
        McSPIChannelEnable(
            (UInt32) instHandle->deviceInfo.baseAddress,
            chanHandle->chanNum);

        if (TRUE == chanHandle->spiChipSelectHold)
        {
            McSPICSAssert((UInt32) instHandle->deviceInfo.baseAddress,
                          chanHandle->chanNum);
        }
    } while (falseWhile);
}

/**
 * \brief  This function is to enable/disable the perticular channel
 * \param  instHandle  [IN]    McSPI Instance handle
 *         chanNum     [IN]    channel num
 *         enable      [IN]    enable/disable the channel
 * \return Nothing
 *
 */
Void Mcspi_ChOnOff(const Mcspi_Object *instHandle, UInt32 chanNum, Bool enable)
{
    if (chanNum < 4U)
    {
        if ((Bool) TRUE == enable)
        {
            McSPIChannelEnable(instHandle->deviceInfo.baseAddress, chanNum);
        }
        else
        {
            McSPIChannelDisable(instHandle->deviceInfo.baseAddress, chanNum);
        }
    }
}

/**
 *  \brief  This function is being used to initialize the McSPI module
 *
 *  \param  instHandle      Instance handler
 *  \param  chanHandle      Channel Handler
 *  \param  eb              Pointer to Error Block
 *
 *  \return Void
 *
 *  \enter  instHandle   must be a valid instance handler
 *          chanHandle   must be a valid channel handler
 *          eb           must be a valid pointer to error block
 *
 */

static Int32 mcspiSetupConfig(const Mcspi_Object *instHandle,
                              const Mcspi_ChanObj *chanHandle, Error_Block *eb)
{
    Int32 status = IOM_COMPLETED;

    /* Module control register setup MCSPI_MODULCTRL
     * The FIFO data will be managed by TX(i) and RX(i) registers
     * FDAA bit to Disable the FIFO
     */
    McSPIFIFODatManagementConfig(
        (UInt32) instHandle->deviceInfo.baseAddress,
        (UInt32) MCSPI_FDAA_DISABLE);

    /* MOA bit - Disable the multiple word access                             */
    McSPIMultipleWordAccessConfig(
        (UInt32) instHandle->deviceInfo.baseAddress,
        (UInt32) MCSPI_MOA_DISABLE);

    if (MCSPI_COMMMODE_MASTER == instHandle->spiHWconfig.masterOrSlave)
    {
        /* MS bit - enable the master mode by clearing the MS bit             */
        McSPIMasterModeEnable((UInt32) instHandle->deviceInfo.baseAddress);
    }
    else if (MCSPI_COMMMODE_SLAVE == instHandle->spiHWconfig.masterOrSlave)
    {
        if ((UInt32) 0 == chanHandle->chanNum)
        {
            /* MS bit - enable the slave mode */
            McSPISlaveModeEnable(
                (UInt32) instHandle->deviceInfo.baseAddress);
        }
        else
        {
            /* error:Other than the channel '0', no channels cannot be
             * used in slave mode */
            DBG_PRINT_ERR("Only Channel 0 can be used in the slave mode\r\n");
            status = IOM_EBADARGS;
        }
    }
    else
    {
        DBG_PRINT_ERR("There is no other mode except SLAVE/MASTER \r\n");
        status = IOM_EBADARGS;
    }

    /* System configuration register setup - MCSPI_SYSCONFIG                  */
    /* CLOCKACTIVITY bit - OCP and Functional clocks are maintained           */
    /* SIDLEMODE     bit - Ignore the idle request and configure in normal mode
     */
    /* AUTOIDLE      bit - Disbale (OCP clock is running free, no gating)     */
    /* Write the values into the MCSPI_SYSCONFIG                              */
    MCSPISysConfigSetup((UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) MCSPI_CLOCKS_OCP_ON_FUNC_ON,
                        (UInt32) MCSPI_SIDLEMODE_NO,
                        (UInt32) MCSPI_WAKEUP_DISABLE,
                        (UInt32) MCSPI_AUTOIDLE_OFF);
    return status;
}

/**
 *  \brief  This function is being used to configure the physical channel
 *
 *  \param  instHandle      Instance handler
 *  \param  chanHandle      Channel Handler
 *  \param  eb              Pointer to Error Block
 *
 *  \return Void
 *
 *  \enter  instHandle   must be a valid instance handler
 *          chanHandle   must be a valid channel handler
 *          eb           must be a valid pointer to error block
 *
 */
static Int32 mcspiChannelConf(Mcspi_Object *instHandle,
                              const Mcspi_ChanObj *chanHandle, Error_Block *eb)
{
    UInt32 dataLineCommMode = 0;
    Int32  status           = IOM_COMPLETED;

    if (MCSPI_COMMMODE_MASTER == instHandle->spiHWconfig.masterOrSlave)
    {
        McSPIClkConfig((UInt32) instHandle->deviceInfo.baseAddress,
                       instHandle->deviceInfo.inputFrequency,
                       chanHandle->cfgChfmt.busFreq,
                       chanHandle->chanNum,
                       chanHandle->cfgChfmt.clockMode);
    }
    else
    {
        /* Slave mode: No need to set up the clock                            */
    }

    /* The FIFO is enabled as and when required in DMA mode of operation
     * FFER bit - by default it will be disabled                              */
    if (FALSE != chanHandle->fifoEnable)
    {
        McSPIRxFIFOConfig((UInt32) instHandle->deviceInfo.baseAddress,
                          (UInt32) MCSPI_RX_FIFO_ENABLE,
                          chanHandle->chanNum);
    }
    else
    {
        /* Do Nothing */
    }

    /* FFEW    bit - by default it will be disabled                           */
    if (FALSE != chanHandle->fifoEnable)
    {
        McSPITxFIFOConfig((UInt32) instHandle->deviceInfo.baseAddress,
                          (UInt32) MCSPI_TX_FIFO_ENABLE,
                          chanHandle->chanNum);
    }
    else
    {
        /* Do Nothing */
    }

    /* TCS     bit - enable the user defined params                           */
    McSPICSTimeControlSet((UInt32) instHandle->deviceInfo.baseAddress,
                          chanHandle->chipSelTimeControl,
                          chanHandle->chanNum);

    /* SBPOL   bit - default value (start bit mode not supported)             */
    /* SBPOL   bit - default value (start bit mode not supported)             */

    /* SBE     bit - default value (start bit mode not supported)             */

    if ((MCSPI_COMMMODE_SLAVE == instHandle->spiHWconfig.masterOrSlave) &&
        (0 == chanHandle->chanNum))
    {
        /* SPIENSLV bit - select appropriate chip select provided by the
         * application.
         */
        McSPISetSlaveChipSel((UInt32) instHandle->deviceInfo.baseAddress,
                             chanHandle->chanNum,
                             chanHandle->cfgChfmt.slaveModeChipSelect);
    }

    if (((MCSPI_IN == chanHandle->cfgChfmt.spiDat0Dir) &&
         (MCSPI_IN == chanHandle->cfgChfmt.spiDat1Dir)) &&
        (MCSPI_BOTH_RXTX == chanHandle->cfgChfmt.trasmitReceiveMode))
    {
        DBG_PRINT_ERR("Dat0 and Dat1 configured as Tx in transmit-receive mode"
                      "is NOT SUPPORTED!!!\r\n");
        status = IOM_EBADARGS;
    }

    if ((MCSPI_OUT == chanHandle->cfgChfmt.spiDat0Dir) &&
        (MCSPI_IN == chanHandle->cfgChfmt.spiDat1Dir))
    {
        dataLineCommMode = (UInt32) MCSPI_DATA_LINE_COMM_MODE_6;
    }
    else if ((MCSPI_IN == chanHandle->cfgChfmt.spiDat0Dir) &&
             (MCSPI_OUT == chanHandle->cfgChfmt.spiDat1Dir))
    {
        dataLineCommMode = (UInt32) MCSPI_DATA_LINE_COMM_MODE_1;
    }
    else if ((MCSPI_OUT == chanHandle->cfgChfmt.spiDat0Dir) &&
             (MCSPI_OUT == chanHandle->cfgChfmt.spiDat1Dir))
    {
        dataLineCommMode = (UInt32) MCSPI_DATA_LINE_COMM_MODE_4;
    }
    else
    {
        DBG_PRINT_ERR("Only (Dat0 - IN, Dat1 - OUT) and "
                      "(Dat0 - OUT,Dat1 - IN) and "
                      "LOOPBACK Mode are supported"
                      " No other modes are supported!!!\r\n");
        status = IOM_EBADARGS;
    }

    /* The PIN34 and INITDLY is only supported in single channel master
     * mode. There is some confusion that, the PIN34 mode is supported in slave
     * mode or not. This has to be verified. At this moment only master mode
     * has the PIN34 support.
     */
    if ((IOM_COMPLETED == status) &&
        ((MCSPI_COMMMODE_MASTER == instHandle->spiHWconfig.masterOrSlave) &&
         (MCSPI_SINGLE_CHANNEL ==
          instHandle->spiHWconfig.singleOrMultiChEnable) &&
         (TRUE != instHandle->isSingleChMasterMode)))
    {
        instHandle->isSingleChMasterMode = (Bool) TRUE;
        /* SINGLE  bit - enable the single master mode                        */

        if (MCSPI_PINOPMODE_3PIN == instHandle->spiHWconfig.pinOpModes)
        {
            /* PIN34   bit - enable the 3 pin mode                            */
            McSPICSDisable((UInt32) instHandle->deviceInfo.baseAddress);
        }
        else if (MCSPI_PINOPMODE_4PIN == instHandle->spiHWconfig.pinOpModes)
        {
            /* PIN34   bit - enable the 4 pin mode                            */
            McSPICSEnable((UInt32) instHandle->deviceInfo.baseAddress);
        }
        else
        {
            DBG_PRINT_ERR(" Invalid pin op mode\r\n");
            status = IOM_EBADARGS;
        }

        /* INTDLY      bit - No delay                                         */
        McSPIInitDelayConfig((UInt32) instHandle->deviceInfo.baseAddress,
                             instHandle->spiHWconfig. \
                             configChfmt[chanHandle->chanNum].spiWordInitDelay);

        McSPIMasterModeConfig((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) MCSPI_SINGLE_CH,
                              chanHandle->cfgChfmt.trasmitReceiveMode,
                              dataLineCommMode,
                              chanHandle->chanNum);
    }
    else if ((MCSPI_COMMMODE_SLAVE == instHandle->spiHWconfig.masterOrSlave) &&
             (MCSPI_SINGLE_CHANNEL ==
              instHandle->spiHWconfig.singleOrMultiChEnable))
    {
        status = (Int32) MCSPIPinDirSet(
            (UInt32) instHandle->deviceInfo.baseAddress,
            (UInt32) chanHandle->cfgChfmt.trasmitReceiveMode,
            dataLineCommMode,
            chanHandle->chanNum);
    }
    else if (TRUE == instHandle->isSingleChMasterMode)
    {
        DBG_PRINT_ERR("This Instance is already opened in single channel"
                      " master mode  \r\n");
        status = IOM_EBADARGS;
    }
    else if ((IOM_COMPLETED == status) &&
             ((MCSPI_COMMMODE_MASTER ==
               instHandle->spiHWconfig.masterOrSlave) &&
              (MCSPI_MULTI_CHANNEL ==
               instHandle->spiHWconfig.singleOrMultiChEnable) &&
              (TRUE != instHandle->isSingleChMasterMode)))
    {
        McSPIMasterModeConfig((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) MCSPI_MULTI_CH,
                              chanHandle->cfgChfmt.trasmitReceiveMode,
                              dataLineCommMode,
                              chanHandle->chanNum);
    }
    else
    {
        DBG_PRINT_ERR("SPIEN hold (FORCE bit) is "
                      "invalid in MULTI channel mode,"
                      "cannot open the channel\r\n");
        status = IOM_EBADARGS;
    }
    if (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode)
    {
        /* DMAR    bit - disable -  Enable whenever required since only
         * one channel can use dma fifo at a time
         */

        /* DMAW    bit - enable                                               */
        McSPIDMADisable((UInt32) instHandle->deviceInfo.baseAddress,
                        ((UInt32) MCSPI_DMA_RX_EVENT |
                         (UInt32) MCSPI_DMA_TX_EVENT),
                        chanHandle->chanNum);
    }

    /* TRM     bit - enable 'Both_RxTx' - only a supported mode               */

    /* WL bit - write user specified val 'charLength'. First make WL bits
     * (11:7) to zero, then write the required value
     */
    McSPIWordLengthSet((UInt32) instHandle->deviceInfo.baseAddress,
                       MCSPI_WORD_LENGTH((chanHandle->cfgChfmt.
                                          charLength)),
                       chanHandle->chanNum);

    /* EPOL    bit - use 'spiChipSelectEnablePol'                             */
    if (TRUE == chanHandle->cfgChfmt.spiChipSelectEnablePol)
    {
        McSPICSPolarityConfig((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) MCSPI_CS_POL_HIGH,
                              chanHandle->chanNum);
    }
    else
    {
        McSPICSPolarityConfig((UInt32) instHandle->deviceInfo.baseAddress,
                              (UInt32) MCSPI_CS_POL_LOW,
                              chanHandle->chanNum);
    }
    return status;
}

static void mcspiUpdateChanHandleFromIop(Mcspi_Object  *instHandle,
                                         Mcspi_ChanObj *chanHandle,
                                         IOM_Packet    *ioPacket)
{
    const Mcspi_DataParam *dataparam;
    dataparam = (Mcspi_DataParam *) ioPacket->addr;
    /* Check if the inBuffer or the outBuffer is NULL i.e,not supplied and
     * update respective buffer appropriately with driver buffer */
    if (NULL == dataparam->inBuffer)
    {
        /* user has not suppiled the IN buffer */
        chanHandle->rxBufFlag = (Bool) FALSE;

        /* No alignment required here*/
        chanHandle->rxBuffer = (UInt8 *) &chanHandle->rxTransBuf[0];

        /* update the details of the out buffer here as it cannot be NULL
         * (condition already checked) */
        chanHandle->txBufFlag   = (Bool) TRUE;
        chanHandle->txBuffer    = dataparam->outBuffer;
        chanHandle->rxBufferLen = dataparam->bufLen;
        chanHandle->txBufferLen = dataparam->bufLen;
    }
    else if (NULL == dataparam->outBuffer)
    {
        /* user has not suppiled the IN buffer*/
        chanHandle->txBufFlag = (Bool) FALSE;

        /* No alignment required here     */
        chanHandle->txBuffer = (UInt8 *) &chanHandle->txTransBuf[0];

        /* update the details of the "inbuffer" here as it cannot be NULL
         * (condition already checked) */
        chanHandle->rxBufFlag   = (Bool) TRUE;
        chanHandle->rxBuffer    = dataparam->inBuffer;
        chanHandle->rxBufferLen = dataparam->bufLen;
        chanHandle->txBufferLen = dataparam->bufLen;
    }
    else
    {
        /* Both the buffers are valid */
        chanHandle->rxBufFlag   = (Bool) TRUE;
        chanHandle->txBufFlag   = (Bool) TRUE;
        chanHandle->rxBuffer    = dataparam->inBuffer;
        chanHandle->txBuffer    = dataparam->outBuffer;
        chanHandle->rxBufferLen = dataparam->bufLen;
        chanHandle->txBufferLen = dataparam->bufLen;
    }

    /* No transfer is happening in any of the channels in this instance of the
     * driver. So for sure we can initiate the transfer here itself */
    chanHandle->activeIOP = (IOM_Packet *) ioPacket;
}

static Int32 mcspiPolledOrInterruptTransferStart(Mcspi_Object  *instHandle,
                                                 Mcspi_ChanObj *chanHandle,
                                                 IOM_Packet    *ioPacket)
{
    Int32 status;
    const Mcspi_DataParam *dataparam;

    mcspiUpdateChanHandleFromIop(instHandle, chanHandle, ioPacket);
    /* Call the mcspiTransfer data transfer through hardware */
    dataparam = (Mcspi_DataParam *) ioPacket->addr;
    status    = (Int32) mcspiTransfer(instHandle, chanHandle, dataparam, NULL);

    return status;
}

static Int32 mcspiSlaveTransferStart(Mcspi_Object  *instHandle,
                                     Mcspi_ChanObj *chanHandle,
                                     IOM_Packet    *ioPacket)
{
    Int32 status = IOM_PENDING;
    const Mcspi_DataParam *dataparam;

    mcspiUpdateChanHandleFromIop(instHandle, chanHandle, ioPacket);
    /* Call the mcspiTransfer data transfer through hardware */
    dataparam = (Mcspi_DataParam *) ioPacket->addr;
    mcspiSlavePrime(instHandle, chanHandle, dataparam);
    return status;
}

static Int mcspiSlavePrime(Mcspi_Object          *instHandle,
                           Mcspi_ChanObj         *chanHandle,
                           const Mcspi_DataParam *dataparam)
{
    Int32            retVal = IOM_PENDING;
    UInt32           wordLength, loopCount;
    UInt32           txData, i;
    Bool             primeFromNextIop = (Bool) FALSE;
    Mcspi_DataParam *nextIopDataParam;
    UInt32           hwiKey = (UInt32) 0;
    UInt32           tempRxTrigLvl;
    UInt32           tempTxTrigLvl;
    UInt32           tempPtrVal;

    /* Validate the input parameter of the function                           */
    assert(NULL != instHandle);
    assert(NULL != dataparam);
    assert(NULL != chanHandle);

    if (dataparam->bufLen <= (UInt32) 0)
    {
        retVal = IOM_EBADARGS;
    }
    if (retVal == IOM_PENDING)
    {
        if (chanHandle->cfgChfmt.charLength <= 8U)
        {
            wordLength = 1U;
        }
        else if (chanHandle->cfgChfmt.charLength <= 16U)
        {
            wordLength = 2U;
        }
        else if (chanHandle->cfgChfmt.charLength <= 32U)
        {
            wordLength = 4U;
        }
        else
        {
            retVal = IOM_EBADARGS;
        }
    }
    if (retVal == IOM_PENDING)
    {
        chanHandle->currError = (Int32) 0;

        if (TRUE == chanHandle->fifoEnable)
        {
            tempRxTrigLvl = instHandle->spiHWconfig.fifoRxTrigLvl;
            tempTxTrigLvl = instHandle->spiHWconfig.fifoTxTrigLvl;

            /* Updatte the word lenght                                    */
            if (tempRxTrigLvl < wordLength)
            {
                tempRxTrigLvl = wordLength;
            }
            if (tempTxTrigLvl < wordLength)
            {
                tempTxTrigLvl = wordLength;
            }

            /* set word count to 0 in case of slave mode */
            McSPIWordCountSet(instHandle->deviceInfo.baseAddress, 0U);
            /* Update the trigger levels */
            McSPIFIFOTrigLvlSet(
                (UInt32) instHandle->deviceInfo.baseAddress,
                (UInt8) tempRxTrigLvl,
                (UInt8) tempTxTrigLvl,
                (UInt32) MCSPI_TX_RX_MODE);
        }
        mcspiChIntrInit(instHandle, chanHandle, (Bool) TRUE);

        /* Fill the Tx buffer */
        McSPIChannelEnable((UInt32) instHandle->deviceInfo.baseAddress,
                           chanHandle->chanNum);
        if (TRUE == chanHandle->fifoEnable)
        {
            loopCount = tempTxTrigLvl / wordLength;
            /* FIFO trigger level can be set max to half the total fifo size.
             * Fill twice the fifo trig level in the fifo. Either from current
             * IOP or from the next IOP from queue. */
            if (chanHandle->txBufferLen >=
                (instHandle->spiHWconfig.fifoRxTrigLvl * 2U))
            {
                primeFromNextIop = (Bool) FALSE;
                loopCount        = loopCount * 2U;
            }
            else
            {
                primeFromNextIop = (Bool) TRUE;
            }
        }
        else
        {
            loopCount        = (UInt32) 1U;
            primeFromNextIop = (Bool) FALSE;
        }
        for (i = 0; i < loopCount; i++)
        {
            tempPtrVal = (UInt32) chanHandle->txBuffer;
            /* Write the data to be transmitted */
            if (wordLength == 1U)
            {
                txData = (UInt32) (*((UInt8 *) tempPtrVal));
            }
            else if (wordLength == 2U)
            {
                txData = (UInt32) (*((UInt16 *) tempPtrVal));
            }
            else if (wordLength == 4U)
            {
                txData = (UInt32) (*((UInt32 *) tempPtrVal));
            }
            else
            {
                retVal = IOM_EBADARGS;
            }
            McSPITransmitData(instHandle->deviceInfo.baseAddress, txData,
                              chanHandle->chanNum);
            if ((Bool) TRUE == chanHandle->txBufFlag)
            {
                chanHandle->txBuffer += wordLength;
            }
            /* decrement the buffer length */
            chanHandle->txBufferLen   -= (UInt32) wordLength;
            instHandle->stats.txBytes += (UInt32) wordLength;
        }
        if (primeFromNextIop == (Bool) TRUE)
        {
            /* Start of Critical Section while accessing the queue. */
            hwiKey = (UInt32) Hwi_disable();
            /* Fetch the Next io packet. */
            if (FALSE ==
                Queue_empty(Queue_handle(&(chanHandle->queuePendingList))))
            {
                chanHandle->nextIop[0].iop = (IOM_Packet *) Queue_get(
                    Queue_handle(&(chanHandle->queuePendingList)));

                /* End of Critical Section. */
                Hwi_restore(hwiKey);
                nextIopDataParam =
                    (Mcspi_DataParam *) chanHandle->nextIop[0].iop->addr;
                if (nextIopDataParam->outBuffer != NULL)
                {
                    chanHandle->nextIop[0].txBuffer =
                        nextIopDataParam->outBuffer;
                    chanHandle->nextIop[0].txBufFlag = (Bool) TRUE;
                }
                else
                {
                    chanHandle->nextIop[0].txBuffer =
                        (UInt8 *) &chanHandle->txTransBuf[0];
                    chanHandle->nextIop[0].txBufFlag = (Bool) FALSE;
                }
                chanHandle->nextIop[0].txBufferLen = nextIopDataParam->bufLen;

                /* Copy loopCount number of bytes to Tx FIFO from next IOP. */
                for (i = 0; i < loopCount; i++)
                {
                    tempPtrVal = (UInt32) chanHandle->nextIop[0].txBuffer;
                    /* Write the data to be transmitted */
                    if (wordLength == 1U)
                    {
                        txData = (UInt32) (*((UInt8 *) tempPtrVal));
                    }
                    else if (wordLength == 2U)
                    {
                        txData = (UInt32) (*((UInt16 *) tempPtrVal));
                    }
                    else if (wordLength == 4U)
                    {
                        txData = (UInt32) (*((UInt32 *) tempPtrVal));
                    }
                    else
                    {
                        retVal = IOM_EBADARGS;
                    }
                    McSPITransmitData(instHandle->deviceInfo.baseAddress,
                                      txData,
                                      chanHandle->chanNum);
                    if ((Bool) TRUE == chanHandle->nextIop[0].txBufFlag)
                    {
                        chanHandle->nextIop[0].txBuffer += wordLength;
                    }
                    /* decrement the buffer length */
                    chanHandle->txBufferLen   -= (UInt32) wordLength;
                    instHandle->stats.txBytes += (UInt32) wordLength;
                }
            }
            else
            {
                /* End of Critical Section. */
                Hwi_restore(hwiKey);
            }
        }
    }
    return ((Int) retVal);
}

/**
 * \brief  Function call for spi data transfer. It transfer data as transcieve
 *          operation.Uses a local driver buffer is the user has not supplied
 *          the buffer.
 *
 * \param  instHandle  [IN]    McSPI Instance handle
 * \param  chanHandle  [IN]    McSPI Channel handle
 * \param  dataparam   [IN]    User data parameters for data Source.
 * \param  eb          [OUT]   Error Block
 *
 * \return IOM_COMPLETED if success
 *         Suitable error code
 *
 * \enter  instHandle  must be a valid pointer and should not be null.
 *         chanHandle  must be a valid pointer and should not be null.
 *         dataParam   must be a valid pointer and should not be null.
 *         eb          if null raise error and aborts the program, if not null
 *                     and valid raises error but shall allow continuation of
 *                     execution
 *
 * \leave  Not Implemented.
 */
static Int mcspiTransfer(Mcspi_Object          *instHandle,
                         Mcspi_ChanObj         *chanHandle,
                         const Mcspi_DataParam *dataparam,
                         Error_Block           *eb)
{
    Int32  retVal = IOM_COMPLETED;
    UInt32 tempReg;
    /* Validate the input parameter of the function                           */
    assert(NULL != instHandle);
    assert(NULL != dataparam);

    assert(NULL != chanHandle);

    /* upadate the channel variables if it is required and also check the
     * input parameters
     */
    chanHandle->currError = (Int32) 0;

    /*======================== POLLED MODE ==================================*/
    if (MCSPI_OPMODE_POLLED == instHandle->opMode)
    {
        if (Semaphore_pend(Semaphore_handle(&(instHandle->syncSem)),
                           instHandle->polledModeTimeout) == (Bool) TRUE)
        {
            /* Process only if no active IOP is present and the driver is not
             * in a PWRM suspend state                                        */
            retVal = mcspiPolledModeTransfer(chanHandle, NULL);
            Semaphore_post(Semaphore_handle(&(instHandle->syncSem)));
        }
        else
        {
            retVal = IOM_ETIMEOUT;
        }
    }
    /*======================== INTERRUPT MODE=================================*/
    if (MCSPI_OPMODE_INTERRUPT == instHandle->opMode)
    {
        UInt32 hwiKey = (UInt32) 0;
        retVal = IOM_PENDING;

        /* Populate the user sent params to spi object structure
         * So device can use all the information when running at  ISR.        */

        /* Start of Critical Section                                          */
        hwiKey = (UInt32) Hwi_disable();
        if (dataparam->bufLen > (UInt32) 0)
        {
            tempReg = McSPIChannelStatusGet(instHandle->deviceInfo.baseAddress,
                                            chanHandle->chanNum);
            /* remove any stale data from the RX side                         */
            while ((UInt32) 0 != (tempReg & MCSPI_CH0STAT_RXS_MASK))
            {
                /* Read before Write to remove any stale data                 */
                *(chanHandle->rxBuffer) =
                    (UInt8) McSPIReceiveData(instHandle->deviceInfo.baseAddress,
                                             chanHandle->chanNum);
                /* dont increment the buffer as this is just reading stale data
                 */
                tempReg = McSPIChannelStatusGet(
                    instHandle->deviceInfo.baseAddress,
                    chanHandle->chanNum);
            }

            if (TRUE == chanHandle->fifoEnable)
            {
                UInt32 spiWordCount;
                UInt32 tempRxTrigLvl = instHandle->spiHWconfig.fifoRxTrigLvl;
                UInt32 tempTxTrigLvl = instHandle->spiHWconfig.fifoTxTrigLvl;

                /* Updatte the word lenght                                    */
                if (chanHandle->cfgChfmt.charLength <= (Int32) 8)
                {
                    spiWordCount = chanHandle->rxBufferLen;
                    if (tempRxTrigLvl < 1U)
                    {
                        tempRxTrigLvl = 1U;
                    }
                    if (tempTxTrigLvl < 1U)
                    {
                        tempTxTrigLvl = 1U;
                    }
                }
                else if (chanHandle->cfgChfmt.charLength <= (Int32) 16)
                {
                    spiWordCount = chanHandle->rxBufferLen / (UInt32) 2;
                    if (tempRxTrigLvl < 2U)
                    {
                        tempRxTrigLvl = 2U;
                    }
                    if (tempTxTrigLvl < 2U)
                    {
                        tempTxTrigLvl = 2U;
                    }
                }
                else if (chanHandle->cfgChfmt.charLength <= (Int32) 32)
                {
                    spiWordCount = chanHandle->rxBufferLen / (UInt32) 4;
                    if (tempRxTrigLvl < 4U)
                    {
                        tempRxTrigLvl = 4U;
                    }
                    if (tempTxTrigLvl < 4U)
                    {
                        tempTxTrigLvl = 4U;
                    }
                }
                else
                {
                    retVal = IOM_EBADARGS;
                }
                if (retVal == IOM_PENDING)
                {
                    McSPIWordCountSet(instHandle->deviceInfo.baseAddress,
                                      (UInt16) spiWordCount);
                    /* Update the trigger levels */
                    McSPIFIFOTrigLvlSet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt8) tempRxTrigLvl,
                        (UInt8) tempRxTrigLvl,
                        (UInt32) MCSPI_TX_RX_MODE);
                }
            }
            if (retVal == IOM_PENDING)
            {
                mcspiChIntrInit(instHandle, chanHandle, (Bool) TRUE);

                /* Enable the channel
                 * write '1' to the bit0 of MCSPI_CH(chanNum)CTRL register to
                 * enable the channel;
                 */
                McSPIChannelEnable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    chanHandle->chanNum);

                if (TRUE == chanHandle->spiChipSelectHold)
                {
                    McSPICSAssert(instHandle->deviceInfo.baseAddress,
                                  chanHandle->chanNum);
                }
            }
        }
        /* End of Critical Section                                            */
        Hwi_restore(hwiKey);
    }
    return ((Int) retVal);
}

/**
 *  \brief  function is used to transfer data in polled mode
 *
 *  This function is used to transfer data in polled mode.
 *
 *  \param  chanHandle  [IN]    Channel handle
 *  \param  eb          [OUT]   error block
 *
 *  \return IOM_COMPLETED in case of success
 *          IOM_EBADIO in case of failure
 *
 *  \enter  chanHandle  must be a valid pointer and should not be null.
 *          eb          if null raise error and aborts the program, if not null
 *                      and valid raises error but shall allow continuation of
 *                      execution
 *
 *  \leave  Not Implemented.
 */

static Int32 mcspiPolledModeTransfer(Mcspi_ChanObj *chanHandle, Error_Block *eb)
{
    Int32  status  = IOM_COMPLETED;
    Bits32 timeCnt = 0;
    UInt32 ioCount = 0;
    Mcspi_Object       *instHandle = NULL;
    Mcspi_DataParam    *dataParam  = NULL;
    UInt32 tempReg = 0;
    UInt16 twoByteLocalBuffer;
    UInt32 fourByteLocalBuffer;
    Void  *localBufferDataPtr;
    Bool   isTimeOutError     = (Bool) FALSE;
    UInt8  oneByteLocalBuffer = 0;
    UInt64 tempU64Val;
    UInt32 tempU32Val;

    assert(NULL != chanHandle);

    instHandle = (Mcspi_Object *) chanHandle->instHandle;
    assert(NULL != instHandle);

    /* When the interrupt capability of an event is disabled in the
     * MCSPI_IRQENABLE register, the interrupt line is not asserted, and the
     * status bits in the MCSPI_IRQSTATUS register can be polled by software to
     * detect when the corresponding event occurs.
     */

    /* In multi channel master mode, it is important not to overwrite the
     * bits of other channels when initializing MCSPI_IRQSTATUS &
     * MCSPI_IRQENABLE.
     */
    mcspiChIntrInit((Mcspi_Object *) instHandle,
                    (Mcspi_ChanObj *) chanHandle,
                    (Bool) FALSE);

    /* Enable the channel
     * write '1' to the bit0 of MCSPI_CH(chanNum)CTRL register to enable
     * the channel
     */
    McSPIChannelEnable((UInt32) instHandle->deviceInfo.baseAddress,
                       chanHandle->chanNum);

    if ((Bool) TRUE == chanHandle->spiChipSelectHold)
    {
        McSPICSAssert((UInt32) instHandle->deviceInfo.baseAddress,
                      chanHandle->chanNum);
    }

    /* To get current ticks to find out the data transfer timeout             */
    timeCnt = Timestamp_get32();

    dataParam = (Mcspi_DataParam *) chanHandle->activeIOP->addr;
    assert(NULL != dataParam);

    if (chanHandle->cfgChfmt.charLength <= 8)
    {
        do
        {
            if ((Bool) FALSE ==
                mcspiCheckTimeOut(timeCnt, instHandle->polledModeTimeout))
            {
                if ((Bool) TRUE == chanHandle->txBufFlag)
                {
                    tempReg = (UInt32) 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    isTimeOutError = (Bool) FALSE;
                    while (((UInt32) 0 ==
                            (tempReg & (UInt32) MCSPI_CH0STAT_TXS_MASK)) &&
                           ((Bool) TRUE != isTimeOutError))
                    {
                        Task_yield();
                        tempReg = (UInt32) 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);

                        /* Check if the timeout has occured waiting for
                         * the tx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Tx\r\n");
                            instHandle->stats.timeoutError++;
                            isTimeOutError = (Bool) TRUE;
                        }
                    }
                    McSPITransmitData(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) * (chanHandle->txBuffer),
                        chanHandle->chanNum);

                    chanHandle->txBufferLen--;
                    chanHandle->txBuffer++;
                }

                if ((Bool) TRUE == chanHandle->rxBufFlag)
                {
                    tempReg = (UInt32) 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
                    isTimeOutError = (Bool) FALSE;
                    while (((UInt32) 0 ==
                            (tempReg & MCSPI_CH0STAT_RXS_MASK)) &&
                           ((Bool) TRUE != isTimeOutError))
                    {
                        Task_yield();
                        tempReg = 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);

                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Rx\r\n");
                            instHandle->stats.timeoutError++;
                            isTimeOutError = (Bool) TRUE;
                        }
                    }

                    chanHandle->rxBufferLen--;
                    oneByteLocalBuffer =
                        (UInt8) McSPIReceiveData(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);

                    tempU32Val =
                        ((UInt32) 1 <<
                         ((UInt32) (chanHandle->cfgChfmt.charLength)));
                    tempU32Val = tempU32Val - (UInt32) 1;
                    tempU32Val = ((UInt32) oneByteLocalBuffer) & tempU32Val;
                    *chanHandle->rxBuffer = (UInt8) tempU32Val;

                    chanHandle->rxBuffer++;
                    ioCount++;
                }
                else
                {
                    tempReg = (UInt32) 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
                    while ((UInt32) 0 == (tempReg & MCSPI_CH0STAT_RXS_MASK))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Rx\r\n");
                            instHandle->stats.timeoutError++;
                            break;
                        }

                        tempReg = (UInt32) 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }
                    chanHandle->rxBufferLen--;
                    *chanHandle->rxBuffer =
                        (UInt8) McSPIReceiveData(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                }
            }
            else
            {
                status = IOM_EBADIO;
                DBG_PRINT_ERR("Time out in Rx\r\n");
                instHandle->stats.timeoutError++;
                break;
            }
        } while ((0 != chanHandle->rxBufferLen) &&
                 (0 != chanHandle->txBufferLen));
    }
    else if (chanHandle->cfgChfmt.charLength <= 16)
    {
        do
        {
            if (FALSE ==
                mcspiCheckTimeOut(timeCnt, instHandle->polledModeTimeout))
            {
                if (TRUE == chanHandle->txBufFlag)
                {
                    tempReg = 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    while ((UInt32) 0 == (tempReg & MCSPI_CH0STAT_TXS_MASK))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Tx\r\n");
                            instHandle->stats.timeoutError++;
                            break;
                        }

                        tempReg = 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }

                    chanHandle->txBufferLen -= 2;
                    localBufferDataPtr       = (Void *) chanHandle->txBuffer;
                    twoByteLocalBuffer       = *(UInt16 *) localBufferDataPtr;
                    McSPITransmitData(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) twoByteLocalBuffer,
                        chanHandle->chanNum);
                    chanHandle->txBuffer += 2;
                }

                if (TRUE == chanHandle->rxBufFlag)
                {
                    tempReg = 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    while ((UInt32) 0 == (tempReg & MCSPI_CH0STAT_RXS_MASK))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting
                         * for the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Rx\r\n");
                            instHandle->stats.timeoutError++;
                            break;
                        }

                        tempReg = 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }

                    chanHandle->rxBufferLen -= 2;
                    localBufferDataPtr       = (Void *) chanHandle->rxBuffer;
                    twoByteLocalBuffer       =
                        (UInt16) McSPIReceiveData(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);

                    tempU32Val =
                        ((UInt32) 1 <<
                         ((UInt32) (chanHandle->cfgChfmt.charLength)));
                    tempU32Val = tempU32Val - (UInt32) 1;
                    tempU32Val = ((UInt32) twoByteLocalBuffer) & tempU32Val;
                    *((UInt16 *) localBufferDataPtr) = (UInt16) tempU32Val;

                    chanHandle->rxBuffer += 2;
                    ioCount += (UInt32) 2;
                }
                else
                {
                    tempReg = 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    while ((UInt32) 0 == (tempReg & MCSPI_CH0STAT_RXS_MASK))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Rx\r\n");
                            instHandle->stats.timeoutError++;
                            break;
                        }

                        tempReg = 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }

                    chanHandle->rxBufferLen--;

                    localBufferDataPtr = (Void *) chanHandle->rxBuffer;
                    twoByteLocalBuffer =
                        (UInt16) McSPIReceiveData(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    *((UInt16 *) localBufferDataPtr) = twoByteLocalBuffer;
                }
            }
        } while ((0 != chanHandle->rxBufferLen) &&
                 (0 != chanHandle->txBufferLen));
    }
    else if (chanHandle->cfgChfmt.charLength <= 32)
    {
        do
        {
            if ((FALSE == mcspiCheckTimeOut(timeCnt,
                                            instHandle->polledModeTimeout)))
            {
                if (TRUE == chanHandle->txBufFlag)
                {
                    tempReg = 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    while ((UInt32) 0 == (tempReg & MCSPI_CH0STAT_TXS_MASK))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Tx\r\n");
                            instHandle->stats.timeoutError++;
                            break;
                        }

                        tempReg = 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }

                    chanHandle->txBufferLen -= 4;
                    localBufferDataPtr       = (Void *) chanHandle->txBuffer;
                    fourByteLocalBuffer      = *(UInt32 *) localBufferDataPtr;
                    McSPITransmitData(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        fourByteLocalBuffer,
                        chanHandle->chanNum);
                    chanHandle->txBuffer += 4;
                }

                if ((Bool) TRUE == chanHandle->rxBufFlag)
                {
                    tempReg = 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    while ((UInt32) 0 == (tempReg & MCSPI_CH0STAT_RXS_MASK))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Rx\r\n");
                            instHandle->stats.timeoutError++;
                            break;
                        }

                        tempReg = 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }

                    chanHandle->rxBufferLen -= 4;
                    localBufferDataPtr       = (Void *) chanHandle->rxBuffer;
                    fourByteLocalBuffer      =
                        (UInt32) McSPIReceiveData(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);

                    tempU64Val =
                        ((UInt64) 1 <<
                         ((UInt64) (chanHandle->cfgChfmt.charLength)));
                    tempU64Val = tempU64Val - (UInt64) 1;
                    tempU32Val = (UInt32) tempU64Val;
                    *((UInt32 *) localBufferDataPtr) = fourByteLocalBuffer &
                                                       tempU32Val;

                    chanHandle->rxBuffer += 4;
                    ioCount += (UInt32) 4;
                }
                else
                {
                    tempReg = 0;
                    tempReg = McSPIChannelStatusGet(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

                    isTimeOutError = (Bool) FALSE;

                    while (((UInt32) 0 ==
                            (tempReg & MCSPI_CH0STAT_RXS_MASK)) &&
                           ((Bool) TRUE != isTimeOutError))
                    {
                        Task_yield();
                        /* check if the timeout has occured waiting for
                         * the rx data
                         */
                        if ((Bool) TRUE == mcspiCheckTimeOut(timeCnt,
                                                             instHandle->
                                                             polledModeTimeout))
                        {
                            status = IOM_EBADIO;
                            DBG_PRINT_ERR("Time out in Rx\r\n");
                            instHandle->stats.timeoutError++;
                            isTimeOutError = (Bool) TRUE;
                        }

                        tempReg = (UInt32) 0;
                        tempReg = McSPIChannelStatusGet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    }
                    chanHandle->rxBufferLen--;

                    localBufferDataPtr  = (Void *) chanHandle->rxBuffer;
                    fourByteLocalBuffer =
                        (UInt32) McSPIReceiveData(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            chanHandle->chanNum);
                    *((UInt32 *) localBufferDataPtr) = fourByteLocalBuffer;
                }
            }
        } while ((0 != chanHandle->rxBufferLen) &&
                 (0 != chanHandle->txBufferLen));
    }
    else
    {
        status = IOM_EBADIO;
        DBG_PRINT_ERR("Invalid Mcspi word data length\r\n");
    }

    /* Disable the channel: write '0' to the bit0 of MCSPI_CH(chanNum)CTRL
     * register to disable the channel
     */
    McSPIChannelDisable((UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);

    if ((Bool) TRUE == chanHandle->spiChipSelectHold)
    {
        McSPICSDeAssert((UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
    }

    /* There is no transaction for now.It will be set again when there is
     * actually transaction to be started
     */
    chanHandle->pendingState         = (Bool) FALSE;
    instHandle->currentActiveChannel = NULL;

    return (status);
}

/**
 *  \brief  function is used to transfer data in DMA mode
 *
 *  This function is used to transfer data in DMA mode.
 *
 *  \param  instHandle  [IN]    Instance handle
 *  \param  chanHandle  [IN]    Channel handle
 *  \param  ioPacket    [IN]    pointer to packet to be submitted
 *
 *  \return IOM_PENDING  in case of success
 *          IOM_EBADARGS in case of failure
 *
 *  \enter  instHandle  must be a valid pointer and should not be null.
 *            chanHandle  must be a valid pointer and should not be null.
 *
 *  \leave  Not Implemented.
 */

Int32 mcspiEdmaModeTransfer(const Mcspi_Object *instHandle,
                            Mcspi_ChanObj      *chanHandle,
                            IOM_Packet         *ioPacket)
{
    Int32 status = IOM_COMPLETED;

    assert(NULL != chanHandle);
    assert(NULL != instHandle);
    assert(NULL != ioPacket);

    Mcspi_UpdateBuffToPrgmEdma(chanHandle, ioPacket);

    /* No transfer is happening in any of the channels in this instance of the
     * driver. So for sure we can initiate the transfer here itself */
    chanHandle->activeIOP =
        (IOM_Packet *) ioPacket;

    /* load this request in to the EDMA paramsets                     */
    Mcspi_localLoadPktToEdma(chanHandle, ioPacket);
    if (IOM_COMPLETED == status)
    {
        /* return the status as pending as the packet will complete later     */
        status = IOM_PENDING;
    }
    return status;
}

/**
 *  \brief  Register interrupt with BIOS and enable them
 *
 *  \param  instNum      Instance number
 *  \param  intNum       Interrupt number
 *  \param  initIsr      Function Pointer to ISR function
 *  \param  spiObj       Handle to be passed to ISR function
 *
 *  \return Void
 *
 *  \enter  instNum   must be a valid instance number
 *          intNum    must be a valid hardware interrupt number
 *          initIsr   must be a valid pointer to ISR function and should
 *                    not be  null.
 *          spiObj    must be valid pointer to SPI instance & should not be null
 *
 *  \leave  Not Implemented.
 */
static Void mcspiRegisterIntrHandler(Int       instNum,
                                     UInt32    intNum,
                                     Mcspi_isr intIsr,
                                     Ptr       mcspiObj)
{
    Mcspi_Object *instHandle = (Mcspi_Object *) mcspiObj;
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    Hwi_Params    hwiParams;
    Error_Block   ebl;
#if (defined (TI814x_M3) || defined (C6A811x_M3))
    UInt          intMuxNum = 0;
#endif
#endif
    UInt32        tempCastIsrPtr;

    assert(NULL != instHandle);
    assert(NULL != intIsr);

#if defined (__TMS470__) || defined (__ARM_ARCH_7A__) /* ARM & M3 */
    /* Initialize the Error Block                                             */
    Error_init(&ebl);

    /* Initialize the HWI parameters with user specified values               */
    Hwi_Params_init(&hwiParams);
    /* argument to be passed to the ISR function                              */
    hwiParams.arg = (UArg) instHandle;

#if (defined (TI814x_M3) || defined (C6A811x_M3))
    hwiParams.enableInt = (Bool) TRUE;

    if (TRUE == instHandle->deviceInfo.crossBarEvtParam.isCrossBarIntEn)
    {
        Hwi_disableInterrupt(
            instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped);

        /* (....intNumToBeMapped - CSL_INTMUX_OFFSET) gives the IntMux
         * number, which has to be mapped to the cross bar event.
         * Eg: if intNumToBeMapped = 42 (I2CINT1) then
         * (42 - CSL_INTMUX_OFFSET) becomes 19, which is nothing but the
         * int mux number. This int mux number (19) will be then mapped to
         * the cross bar event [Eg: Cross bar event for I2CINT2 is 04]
         */
        intMuxNum = (instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped -
                     (UInt) CSL_INTMUX_OFFSET);
        IntMux_setEvent(intMuxNum, intNum);

        /* Create a corresponding interrupt handler. Notice that Ducati
         * interrupt number
         * (instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped)
         * corresponds to IntMux
         * ((instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped) -
         * CSL_INTMUX_OFFSET)
         */
        tempCastIsrPtr = (UInt32) intIsr;
        Hwi_construct(&instHandle->hwiStruct,
                      instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped,
                      (Hwi_FuncPtr) tempCastIsrPtr, &hwiParams,
                      NULL);
        instHandle->hwiHandle = Hwi_handle(&instHandle->hwiStruct);

        Hwi_enableInterrupt(
            instHandle->deviceInfo.crossBarEvtParam.intNumToBeMapped);
    }
    else
    {
        Hwi_disableInterrupt(intNum);
        tempCastIsrPtr = (UInt32) intIsr;
        Hwi_construct(&instHandle->hwiStruct, (Int32) intNum,
                      (Hwi_FuncPtr) tempCastIsrPtr, &hwiParams,
                      NULL);
        instHandle->hwiHandle = Hwi_handle(&instHandle->hwiStruct);
        Hwi_enableInterrupt(intNum);
    }
#else /* A8 Core */ /* M4 Core TDA2xx */

    Hwi_disableInterrupt(intNum);

    tempCastIsrPtr = (UInt32) intIsr;
    Hwi_construct(&instHandle->hwiStruct, (Int32) intNum,
                  (Hwi_FuncPtr) tempCastIsrPtr, &hwiParams,
                  NULL);
    instHandle->hwiHandle = Hwi_handle(&instHandle->hwiStruct);
    Hwi_enableInterrupt(intNum);
#endif

#else /* C674 */
      /* Mapping the event id to the ECM Dispatch of the SYS/BIOS
       *              */
    EventCombiner_dispatchPlug((UInt32) intNum,
                               (EventCombiner_FuncPtr) intIsr,
                               (UArg) instHandle,
                               TRUE);

    /* Enabling the event                                                     */
    EventCombiner_enableEvent((UInt32) intNum);

    /* Enabling the HWI_ID                                                    */
    Hwi_enableInterrupt(instHandle->hwiNumber);

#endif
}

/**
 *  \brief  Disable and Un-Register interrupt with BIOS.
 *
 *  \param  instHandle  [IN]   Handle to the device instance
 *  \param  intNum    Interrupt number
 *
 *  \return None
 *
 *  \enter  instHandle must be a valid pointer and should not be null.
 *          intNum     must be a valid hardware interrupt number
 *
 *  \leave  Not Implemented.
 */
static Void mcspiUnregisterIntrHandler(Mcspi_Object *instHandle, UInt32 intNum)
{
#if defined (__TMS470__) || defined (__ARM_ARCH_7A__)
    Hwi_Struct *mcspiHwiStruct;
    mcspiHwiStruct = Hwi_struct(instHandle->hwiHandle);
    Hwi_disableInterrupt(intNum);

    Hwi_destruct(mcspiHwiStruct);

    if (mcspiHwiStruct != NULL)
    {
        memset(mcspiHwiStruct, 0, sizeof (Hwi_Struct));
    }
    instHandle->hwiHandle = NULL;
#else
    /* Disabling the interrupts                                               */
    EventCombiner_disableEvent((UInt32) intNum);
#endif
}

/**
 *  \brief  Get the interrupt status for a specific channel.
 *
 *  \param  ChanHandle  [IN]   Handle to the channel
 *          irqStatus   [IN]   IRQSTATUS register value
 *          txEmptyBits [OUT]  To indicate the int for tx empty
 *          rxFullBits  [OUT]  To indicate the int for rx full
 *  \return None
 *
 */

static Void mcspiIntrStatus(const Mcspi_ChanObj *chanHandle,
                            const UInt32        *irqStatus,
                            UInt32              *txEmptyBits,
                            UInt32              *rxFullBits,
                            UInt32              *eowBit)
{
    UInt32 chanNum = (UInt32) 0xFFFFFFFFU;

    chanNum = chanHandle->chanNum;

    /* Get the channel specific irq status                                    */
    switch (chanNum)
    {
        case 0:
            *txEmptyBits = ((*irqStatus & MCSPI_IRQSTATUS_TX0_EMPTY_MASK) >>
                            MCSPI_IRQSTATUS_TX0_EMPTY_SHIFT);
            *rxFullBits = ((*irqStatus & MCSPI_IRQSTATUS_RX0_FULL_MASK) >>
                           MCSPI_IRQSTATUS_RX0_FULL_SHIFT);
            break;

        case 1U:
            *txEmptyBits = ((*irqStatus & MCSPI_IRQSTATUS_TX1_EMPTY_MASK) >>
                            MCSPI_IRQSTATUS_TX1_EMPTY_SHIFT);
            *rxFullBits = ((*irqStatus & MCSPI_IRQSTATUS_RX1_FULL_MASK) >>
                           MCSPI_IRQSTATUS_RX1_FULL_SHIFT);
            break;

        case 2U:
            *txEmptyBits = ((*irqStatus & MCSPI_IRQSTATUS_TX2_EMPTY_MASK) >>
                            MCSPI_IRQSTATUS_TX2_EMPTY_SHIFT);
            *rxFullBits = ((*irqStatus & MCSPI_IRQSTATUS_RX2_FULL_MASK) >>
                           MCSPI_IRQSTATUS_RX2_FULL_SHIFT);
            break;

        case 3U:
            *txEmptyBits = ((*irqStatus & MCSPI_IRQSTATUS_TX3_EMPTY_MASK) >>
                            MCSPI_IRQSTATUS_TX3_EMPTY_SHIFT);
            *rxFullBits = ((*irqStatus & MCSPI_IRQSTATUS_RX3_FULL_MASK) >>
                           MCSPI_IRQSTATUS_RX3_FULL_SHIFT);
            break;

        default:
            DBG_PRINT_ERR("Invalid channel number\r\n");
            break;
    }
    *eowBit = ((*irqStatus & MCSPI_IRQSTATUS_EOW_MASK) >>
               MCSPI_IRQSTATUS_EOW_SHIFT);
}

/*
 * \fn     Void mcspiIntrHandler()
 *
 * \brief  Interrupt handler for SPI Device
 *
 *         It will check the errors and the data transfer either read or write
 *         is done.
 *
 * \param  instHandle  [IN]    Pointer to the spi driver object
 *
 * \return None
 *
 * \enter  instHandle  must be a valid pointer and should not be null.
 *
 * \leave  Not Implemented.
 */
static Void mcspiIntrHandler(Ptr arg)
{
    Mcspi_ChanObj *chanHandle = 0;
    UInt32         intStatus  = (UInt32) 0, intFlags;
    Mcspi_Object  *instHandle;
    instHandle = (Mcspi_Object *) arg;
    UInt32         txEmptyBit, rxFullBit, irqStatus, eowBit;
    UInt32         txrxThisIteration = 0;
    UInt32         loopCount         = 0;
    UInt32         i;
    void          *localBufferDataPtr;
    UInt16         twoByteLocalBuffer;
    UInt32         fourByteLocalBuffer;
    UInt8          oneByteLocalBuffer = 0;
    UInt64         tempU64Val;
    UInt32         tempU32Val;
    UInt32         tempRxTrigLvl;
    UInt32         tempTxTrigLvl;
    UInt32         wordLength;

    if ((NULL != instHandle) && (NULL != instHandle->currentActiveChannel))
    {
        chanHandle = instHandle->currentActiveChannel;

        if (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode)
        {
            /* EDMA operation - only process these if the error interrupt
             * is set
             */
            intStatus = McSPIIntStatusGet(
                (UInt32) instHandle->deviceInfo.baseAddress);

            /* Error handler function - only process these if the error
             * interrupt is set
             */
            mcspiHandleErrors((Mcspi_Object *) instHandle,
                              (Mcspi_ChanObj *) chanHandle,
                              (UInt32) intStatus);
        }
        else if (MCSPI_OPMODE_INTERRUPT == instHandle->opMode)
        {
            irqStatus = McSPIIntStatusGet(
                (UInt32) instHandle->deviceInfo.baseAddress);

            txEmptyBit = (UInt32) 0;
            rxFullBit  = (UInt32) 0;
            eowBit     = (UInt32) 0;

            /* Here the main consideration is, where to specify the number of
             * words to be received/transmitted.
             */

            mcspiIntrStatus(chanHandle, &irqStatus, &txEmptyBit, &rxFullBit,
                            &eowBit);

            /* Receive data Handling is done here                             */
            if ((UInt32) 0 != rxFullBit)
            {
                txrxThisIteration = 1U;
                if ((UInt32) 0 != chanHandle->rxBufferLen)
                {
                    if ((Bool) TRUE == chanHandle->abortAllIo)
                    {
                        mcspiCompleteIOInIsr(instHandle);
                    }
                    else
                    {
                        intFlags =
                            ((UInt32) MCSPI_IRQSTATUS_RX0_FULL_MASK <<
                             (chanHandle->chanNum * 4U));
                        McSPIIntStatusClear(
                            instHandle->deviceInfo.baseAddress, intFlags);
                        if (chanHandle->cfgChfmt.charLength <= (Int32) 8)
                        {
                            if ((TRUE == chanHandle->fifoEnable) &&
                                (instHandle->spiHWconfig.fifoRxTrigLvl >= 1U))
                            {
                                if (chanHandle->rxBufferLen <
                                        instHandle->spiHWconfig.fifoRxTrigLvl)
                                {
                                    loopCount =
                                            chanHandle->rxBufferLen;
                                }
                                else
                                {
                                    loopCount =
                                            instHandle->spiHWconfig.fifoRxTrigLvl;
                                }
                            }
                            else
                            {
                                loopCount = (UInt32) 1;
                            }
                            for (i = 0; i < loopCount; i++)
                            {
                                oneByteLocalBuffer = (UInt8) McSPIReceiveData(
                                    instHandle->deviceInfo.baseAddress,
                                    chanHandle->chanNum);

                                tempU32Val =
                                    ((UInt32) 1 <<
                                     ((UInt32) (chanHandle->cfgChfmt.charLength)));
                                tempU32Val = tempU32Val - (UInt32) 1;
                                tempU32Val = ((UInt32) oneByteLocalBuffer) &
                                             tempU32Val;
                                *chanHandle->rxBuffer = (UInt8) tempU32Val;

                                if (TRUE == chanHandle->rxBufFlag)
                                {
                                    chanHandle->rxBuffer++;
                                }
                                /* decrement the buffer length
                                 *                   */
                                chanHandle->rxBufferLen--;
                                instHandle->stats.rxBytes++;
                            }
                        }
                        else if (chanHandle->cfgChfmt.charLength <= (Int32) 16)
                        {
                            if ((TRUE == chanHandle->fifoEnable) &&
                                (instHandle->spiHWconfig.fifoRxTrigLvl >= 2U))
                            {
                                if (chanHandle->rxBufferLen <
                                        instHandle->spiHWconfig.fifoRxTrigLvl)
                                {
                                    loopCount =
                                            chanHandle->rxBufferLen /
                                            (UInt32) 2;
                                }
                                else
                                {
                                    loopCount =
                                            instHandle->spiHWconfig.fifoRxTrigLvl /
                                            (UInt32) 2;
                                }
                            }
                            else
                            {
                                loopCount = (UInt32) 1;
                            }
                            for (i = 0; i < loopCount; i++)
                            {
                                localBufferDataPtr =
                                    (Void *) chanHandle->rxBuffer;
                                twoByteLocalBuffer =
                                    (UInt16) McSPIReceiveData(
                                        instHandle->deviceInfo.baseAddress,
                                        chanHandle->chanNum);

                                tempU32Val =
                                    ((UInt32) 1 <<
                                     ((UInt32) (chanHandle->cfgChfmt.charLength)));
                                tempU32Val = tempU32Val - (UInt32) 1;
                                tempU32Val = ((UInt32) twoByteLocalBuffer) &
                                             tempU32Val;
                                *((UInt16 *) localBufferDataPtr) =
                                    (UInt16) tempU32Val;

                                if (TRUE == chanHandle->rxBufFlag)
                                {
                                    chanHandle->rxBuffer += (UInt32) 2;
                                }
                                /* decrement the buffer length
                                 *                   */
                                chanHandle->rxBufferLen   -= (UInt32) 2;
                                instHandle->stats.rxBytes += (UInt32) 2;
                            }
                        }
                        else if (chanHandle->cfgChfmt.charLength <= (Int32) 32)
                        {
                            if ((TRUE == chanHandle->fifoEnable) &&
                                (instHandle->spiHWconfig.fifoRxTrigLvl >= 4U))
                            {
                                if (chanHandle->rxBufferLen <
                                        instHandle->spiHWconfig.fifoRxTrigLvl)
                                {
                                    loopCount =
                                            chanHandle->rxBufferLen /
                                            (UInt32) 4;
                                }
                                else
                                {
                                    loopCount =
                                            instHandle->spiHWconfig.fifoRxTrigLvl /
                                            (UInt32) 4;
                                }
                            }
                            else
                            {
                                loopCount = (UInt32) 1;
                            }
                            for (i = 0; i < loopCount; i++)
                            {
                                localBufferDataPtr =
                                    (Void *) chanHandle->rxBuffer;
                                fourByteLocalBuffer =
                                    McSPIReceiveData(
                                        instHandle->deviceInfo.baseAddress,
                                        chanHandle->chanNum);

                                tempU64Val =
                                    ((UInt64) 1 <<
                                     ((UInt64) (chanHandle->cfgChfmt.charLength)));
                                tempU64Val = tempU64Val - (UInt64) 1;
                                tempU32Val = (UInt32) tempU64Val;
                                *((UInt32 *) localBufferDataPtr) =
                                    fourByteLocalBuffer & tempU32Val;

                                if (TRUE == chanHandle->rxBufFlag)
                                {
                                    chanHandle->rxBuffer += 4;
                                }
                                /* decrement the buffer length
                                 *                   */
                                chanHandle->rxBufferLen   -= (UInt32) 4;
                                instHandle->stats.rxBytes += (UInt32) 4;
                            }
                        }
                        else
                        {
                            DBG_PRINT_ERR("Invalid spi word data lenght \r\n");
                        }
                    }
                }
            }

            /* Transmit data Handling is done here                            */
            if ((UInt32) 0 != txEmptyBit)
            {
                txrxThisIteration = 1U;
                if ((UInt32) 0 != chanHandle->txBufferLen)
                {
                    if ((Bool) TRUE == chanHandle->abortAllIo)
                    {
                        mcspiCompleteIOInIsr(instHandle);
                    }
                    else
                    {
                        intFlags =
                            ((UInt32) MCSPI_IRQSTATUS_TX0_EMPTY_MASK <<
                             (chanHandle->chanNum * 4U));
                        McSPIIntStatusClear(
                            instHandle->deviceInfo.baseAddress, intFlags);
                        /* Write the data to be transmitted                   */
                        if (chanHandle->cfgChfmt.charLength <= (Int32) 8)
                        {
                            if ((TRUE == chanHandle->fifoEnable) &&
                                (instHandle->spiHWconfig.fifoTxTrigLvl >= 1U))
                            {
                                if (chanHandle->txBufferLen <
                                        instHandle->spiHWconfig.fifoTxTrigLvl)
                                {
                                    loopCount =
                                            chanHandle->txBufferLen;
                                }
                                else
                                {
                                    loopCount =
                                            instHandle->spiHWconfig.fifoTxTrigLvl;
                                }
                            }
                            else
                            {
                                loopCount = (UInt32) 1;
                            }
                            for (i = 0; i < loopCount; i++)
                            {
                                McSPITransmitData(
                                    instHandle->deviceInfo.baseAddress,
                                    (UInt32) (*chanHandle->txBuffer),
                                    chanHandle->chanNum);

                                if ((Bool) TRUE == chanHandle->txBufFlag)
                                {
                                    chanHandle->txBuffer++;
                                }

                                /* decrement the buffer length
                                 *                   */
                                chanHandle->txBufferLen   -= (UInt32) 1;
                                instHandle->stats.txBytes += (UInt32) 1;
                            }
                        }
                        else if (chanHandle->cfgChfmt.charLength <= (Int32) 16)
                        {
                            if ((TRUE == chanHandle->fifoEnable) &&
                                (instHandle->spiHWconfig.fifoTxTrigLvl >= 2U))
                            {
                                if (chanHandle->txBufferLen <
                                        instHandle->spiHWconfig.fifoTxTrigLvl)
                                {
                                    loopCount =
                                            chanHandle->txBufferLen/ (UInt32)2;
                                }
                                else
                                {
                                    loopCount =
                                            instHandle->spiHWconfig.fifoTxTrigLvl / (UInt32)2;
                                }
                            }
                            else
                            {
                                loopCount = (UInt32) 1;
                            }
                            for (i = 0; i < loopCount; i++)
                            {
                                /* Write the data to be transmitted
                                 *              */
                                localBufferDataPtr =
                                    (Void *) chanHandle->txBuffer;
                                twoByteLocalBuffer =
                                    *((UInt16 *) localBufferDataPtr);
                                McSPITransmitData(
                                    instHandle->deviceInfo.baseAddress,
                                    (UInt32) twoByteLocalBuffer,
                                    chanHandle->chanNum);
                                if ((Bool) TRUE == chanHandle->txBufFlag)
                                {
                                    chanHandle->txBuffer += 2;
                                }
                                /* decrement the buffer length
                                 *                   */
                                chanHandle->txBufferLen   -= (UInt32) 2;
                                instHandle->stats.txBytes += (UInt32) 2;
                            }
                        }
                        else if (chanHandle->cfgChfmt.charLength <= (Int32) 32)
                        {
                            if ((TRUE == chanHandle->fifoEnable) &&
                                (instHandle->spiHWconfig.fifoTxTrigLvl >= 4U))
                            {
                                if (chanHandle->txBufferLen <
                                        instHandle->spiHWconfig.fifoTxTrigLvl)
                                {
                                    loopCount =
                                            chanHandle->txBufferLen/ (UInt32)4;
                                }
                                else
                                {
                                    loopCount =
                                            instHandle->spiHWconfig.fifoTxTrigLvl / (UInt32)4;
                                }
                            }
                            else
                            {
                                loopCount = (UInt32) 1;
                            }
                            for (i = 0; i < loopCount; i++)
                            {
                                /* Write the data to be transmitted
                                 *              */
                                localBufferDataPtr =
                                    (Void *) chanHandle->txBuffer;
                                fourByteLocalBuffer =
                                    *((UInt32 *) localBufferDataPtr);
                                McSPITransmitData(
                                    instHandle->deviceInfo.baseAddress,
                                    fourByteLocalBuffer,
                                    chanHandle->chanNum);
                                if ((Bool) TRUE == chanHandle->txBufFlag)
                                {
                                    chanHandle->txBuffer += 4;
                                }
                                /* decrement the buffer length
                                 *                   */
                                chanHandle->txBufferLen   -= (UInt32) 4;
                                instHandle->stats.txBytes += (UInt32) 4;
                            }
                        }
                        else
                        {
                            DBG_PRINT_ERR("Invalid spi word data lenght \r\n");
                        }
                    }
                }
            }

            if (TRUE == chanHandle->fifoEnable)
            {
                if ((chanHandle->txBufferLen <
                     instHandle->spiHWconfig.fifoTxTrigLvl) &&
                    (chanHandle->rxBufferLen <
                     instHandle->spiHWconfig.fifoTxTrigLvl))
                {
                    if (chanHandle->cfgChfmt.charLength <= (Int32) 8)
                    {
                        while (0 != chanHandle->txBufferLen)
                        {
                            /* Write the data to be transmitted               */
                            McSPITransmitData(
                                instHandle->deviceInfo.baseAddress,
                                (UInt32) (*(chanHandle->txBuffer)),
                                chanHandle->chanNum);
                            if ((Bool) TRUE == chanHandle->txBufFlag)
                            {
                                chanHandle->txBuffer++;
                            }
                            /* decrement the buffer length                    */
                            chanHandle->txBufferLen   -= (UInt32) 1;
                            instHandle->stats.txBytes += (UInt32) 1;
                        }
                        wordLength = 1U;
                    }
                    else if (chanHandle->cfgChfmt.charLength <= (Int32) 16)
                    {
                        while (0 != chanHandle->txBufferLen)
                        {
                            /* Write the data to be transmitted               */
                            localBufferDataPtr = (Void *) chanHandle->txBuffer;
                            twoByteLocalBuffer =
                                *((UInt16 *) localBufferDataPtr);
                            McSPITransmitData(
                                instHandle->deviceInfo.baseAddress,
                                (UInt32) twoByteLocalBuffer,
                                chanHandle->chanNum);
                            if ((Bool) TRUE == chanHandle->txBufFlag)
                            {
                                chanHandle->txBuffer += 2;
                            }
                            /* decrement the buffer length                    */
                            chanHandle->txBufferLen   -= (UInt32) 2;
                            instHandle->stats.txBytes += (UInt32) 2;
                        }
                        wordLength = 2U;
                    }
                    else if (chanHandle->cfgChfmt.charLength <= (Int32) 32)
                    {
                        while (0 != chanHandle->txBufferLen)
                        {
                            /* Write the data to be transmitted               */
                            localBufferDataPtr  = (Void *) chanHandle->txBuffer;
                            fourByteLocalBuffer =
                                *((UInt32 *) localBufferDataPtr);
                            McSPITransmitData(
                                instHandle->deviceInfo.baseAddress,
                                fourByteLocalBuffer,
                                chanHandle->chanNum);
                            if ((Bool) TRUE == chanHandle->txBufFlag)
                            {
                                chanHandle->txBuffer += 4;
                            }
                            /* decrement the buffer length                    */
                            chanHandle->txBufferLen   -= (UInt32) 4;
                            instHandle->stats.txBytes += (UInt32) 4;
                        }
                        wordLength = 4U;
                    }
                    else
                    {
                        DBG_PRINT_ERR("Invalid spi word data lenght \r\n");
                        wordLength = 0xFFU;
                    }
                    if ((wordLength != 0xFFU) && (chanHandle->rxBufferLen != 0))
                    {
                        tempRxTrigLvl = chanHandle->rxBufferLen;
                        tempTxTrigLvl = instHandle->spiHWconfig.fifoTxTrigLvl;

                        /* Updatte the word lenght                                    */
                        if (tempRxTrigLvl < wordLength)
                        {
                            tempRxTrigLvl = wordLength;
                        }
                        if (tempTxTrigLvl < wordLength)
                        {
                            tempTxTrigLvl = wordLength;
                        }

                        /* Update the trigger levels */
                        McSPIFIFOTrigLvlSet(
                            (UInt32) instHandle->deviceInfo.baseAddress,
                            (UInt8) tempRxTrigLvl,
                            (UInt8) tempTxTrigLvl,
                            (UInt32) MCSPI_TX_RX_MODE);
                    }
                }
            }
            if ((UInt32) 0 != eowBit)
            {
                McSPIIntStatusClear(instHandle->deviceInfo.baseAddress,
                                    MCSPI_IRQSTATUS_EOW_MASK);
                if ((Uint32) 0 != chanHandle->rxBufferLen)
                {
                    txrxThisIteration = 1U;
                    if (chanHandle->cfgChfmt.charLength <= (Int32) 8)
                    {
                        while ((Uint32) 0 != chanHandle->rxBufferLen)
                        {
                            *chanHandle->rxBuffer = (UInt8) McSPIReceiveData(
                                instHandle->deviceInfo.baseAddress,
                                chanHandle->chanNum);
                            if (TRUE == chanHandle->rxBufFlag)
                            {
                                chanHandle->rxBuffer++;
                            }
                            /* decrement the buffer length                    */
                            chanHandle->rxBufferLen--;
                            instHandle->stats.rxBytes++;
                        }
                    }
                    else if (chanHandle->cfgChfmt.charLength <= (Int32) 16)
                    {
                        while ((Uint32) 0 != chanHandle->rxBufferLen)
                        {
                            localBufferDataPtr = (Void *) chanHandle->rxBuffer;
                            twoByteLocalBuffer =
                                (UInt16) McSPIReceiveData(
                                    instHandle->deviceInfo.baseAddress,
                                    chanHandle->chanNum);
                            *((UInt16 *) localBufferDataPtr) =
                                twoByteLocalBuffer;
                            if (TRUE == chanHandle->rxBufFlag)
                            {
                                chanHandle->rxBuffer += 2;
                            }
                            /* decrement the buffer length                    */
                            chanHandle->rxBufferLen   -= (UInt32) 2;
                            instHandle->stats.rxBytes += (UInt32) 2;
                        }
                    }
                    else if (chanHandle->cfgChfmt.charLength <= (Int32) 32)
                    {
                        while ((Uint32) 0 != chanHandle->rxBufferLen)
                        {
                            localBufferDataPtr  = (Void *) chanHandle->rxBuffer;
                            fourByteLocalBuffer =
                                McSPIReceiveData(
                                    instHandle->deviceInfo.baseAddress,
                                    chanHandle->chanNum);
                            *((UInt32 *) localBufferDataPtr) =
                                fourByteLocalBuffer;
                            if (TRUE == chanHandle->rxBufFlag)
                            {
                                chanHandle->rxBuffer += 4;
                            }
                            /* decrement the buffer length                    */
                            chanHandle->rxBufferLen   -= (UInt32) 4;
                            instHandle->stats.rxBytes += (UInt32) 4;
                        }
                    }
                    else
                    {
                        DBG_PRINT_ERR("Invalid spi word data lenght \r\n");
                    }
                }
            }

            intStatus = irqStatus;
            /* Only error bits are captured.                                  */
            intStatus &= (UInt32) 0x0000222A;

            /* only process these if the error interrupt is set               */
            mcspiHandleErrors(instHandle, chanHandle, intStatus);
            /* Call Next Setp only if any of the rxFullBit or txEmptyBit were  *
             * set, Otherwise its a dummy interrupt and nect transfer is       *
             * already riggered */

            if (0U != txrxThisIteration)
            {
                if ((((UInt32) 0 == chanHandle->rxBufferLen) &&
                     ((UInt32) 0 == chanHandle->txBufferLen)) ||
                    ((Int32) 0 != chanHandle->currError))
                {
                    mcspiCompleteIOInIsr(instHandle);
                }
            }
        }
        else
        {
            DBG_PRINT_ERR("Invalid OpMode \r\n");
        }
    }
}

static Void mcspiSlaveIntrHandler(Ptr arg)
{
    Mcspi_Object    *instHandle;
    Mcspi_ChanObj   *chanHandle = NULL;
    UInt32           txEmptyBit, rxFullBit, irqStatus, eowBit;
    UInt32           wordLength, loopCount;
    UInt32           rxData, txData, i;
    Mcspi_DataParam *dataparam   = NULL;
    UInt8          **txBufferPtr = NULL;
    UInt32           hwiKey      = (UInt32) 0x00;
    UInt32           intFlags;
    UInt32          *txBufLengthPtr = NULL;
    Int32 status = IOM_COMPLETED;
    UInt32           tempPtrVal;

    instHandle = (Mcspi_Object *) arg;
    if ((NULL == instHandle) || (NULL == instHandle->currentActiveChannel) ||
        (MCSPI_OPMODE_INTERRUPT != instHandle->opMode))
    {
        status = IOM_EBADIO;
    }
    if (status == IOM_COMPLETED)
    {
        chanHandle = instHandle->currentActiveChannel;
        irqStatus  = McSPIIntStatusGet(
            (UInt32) instHandle->deviceInfo.baseAddress);

        txEmptyBit = (UInt32) 0;
        rxFullBit  = (UInt32) 0;
        eowBit     = (UInt32) 0;
        mcspiIntrStatus(chanHandle, &irqStatus, &txEmptyBit, &rxFullBit,
                        &eowBit);
        if ((UInt32) 0 == rxFullBit)
        {
            DBG_PRINT_ERR("Rx Overflow Interrupt \r\n");
            /* TODO: Add Rx Overflow interrupt handling. If FIFO is enabled,
             * the data in FIFO is corrupted, we should flush fifo, reset IP.
             * return error status to application */
            status = IOM_EBADIO;
        }
    }
    if (status == IOM_COMPLETED)
    {
        /* rx Full interrupt is set.
         * In McSPI Slave ISR only Rx full interrupt is enabled.
         * Both Receive and Transmit data Handling is done here. */
        intFlags = ((UInt32) MCSPI_IRQSTATUS_RX0_FULL_MASK <<
                    (chanHandle->chanNum * 4U));
        McSPIIntStatusClear(instHandle->deviceInfo.baseAddress,
                            intFlags);

        /* Get the tx Buffer from current IOP or from the next IOPs */
        if (0 == chanHandle->txBufferLen)
        {
            /* Tx Buf length in current IOP is 0. Get Buffet ptr from next
             * io packet in pending queue. */

            /* start the critical section */
            hwiKey = (UInt32) Hwi_disable();

            if (chanHandle->nextIop[0].iop == NULL)
            {
                if (chanHandle->nextIop[1].iop != NULL)
                {
                    /* if nextIop[1] has valid IOP copy to nextIOP[0] */
                    chanHandle->nextIop[0].iop =
                        chanHandle->nextIop[1].iop;
                    chanHandle->nextIop[0].txBuffer =
                        chanHandle->nextIop[1].txBuffer;
                    chanHandle->nextIop[0].txBufferLen =
                        chanHandle->nextIop[1].txBufferLen;
                    chanHandle->nextIop[0].txBufFlag =
                        chanHandle->nextIop[1].txBufFlag;
                    chanHandle->nextIop[0].iop         = NULL;
                    chanHandle->nextIop[0].txBuffer    = NULL;
                    chanHandle->nextIop[0].txBufferLen = 0;
                    chanHandle->nextIop[0].txBufFlag   = (Bool) FALSE;
                    txBufferPtr    = &chanHandle->nextIop[0].txBuffer;
                    txBufLengthPtr = &(chanHandle->nextIop[0].txBufferLen);
                }
                else
                {
                    /* Get the next IOP from queue if present */
                    if ((Bool) FALSE ==
                        Queue_empty(Queue_handle(&chanHandle->queuePendingList)))
                    {
                        chanHandle->nextIop[0].iop =
                            (IOM_Packet *) Queue_get(Queue_handle(&(chanHandle
                                                                    ->
                                                                    queuePendingList)));
                        dataparam =
                            (Mcspi_DataParam *) chanHandle->nextIop[0].iop->
                            addr;
                        chanHandle->nextIop[0].txBufferLen = dataparam->bufLen;
                        if (dataparam->outBuffer != NULL)
                        {
                            chanHandle->nextIop[0].txBuffer =
                                dataparam->outBuffer;
                            chanHandle->nextIop[0].txBufFlag = (Bool) TRUE;
                        }
                        else
                        {
                            chanHandle->nextIop[0].txBuffer =
                                (UInt8 *) &chanHandle->txTransBuf[0];
                            chanHandle->nextIop[0].txBufFlag = (Bool) FALSE;
                        }
                        txBufferPtr    = &chanHandle->nextIop[0].txBuffer;
                        txBufLengthPtr = &(chanHandle->nextIop[0].txBufferLen);
                    }
                }
            }
            else
            {
                if (chanHandle->nextIop[0].txBufferLen == 0)
                {
                    if (chanHandle->nextIop[1].iop != NULL)
                    {
                        txBufferPtr    = &chanHandle->nextIop[1].txBuffer;
                        txBufLengthPtr = &(chanHandle->nextIop[1].txBufferLen);
                    }
                    else
                    {
                        /* Get the next IOP from queue if present */
                        if ((Bool) FALSE ==
                            Queue_empty(Queue_handle(&chanHandle->
                                                     queuePendingList)))
                        {
                            chanHandle->nextIop[1].iop =
                                (IOM_Packet *) Queue_get(Queue_handle(&(
                                                                          chanHandle
                                                                          ->
                                                                          queuePendingList)));
                            dataparam =
                                (Mcspi_DataParam *) chanHandle->nextIop[1].iop
                                ->addr;
                            chanHandle->nextIop[1].txBufferLen =
                                dataparam->bufLen;
                            if (dataparam->outBuffer != NULL)
                            {
                                chanHandle->nextIop[1].txBuffer =
                                    dataparam->outBuffer;
                                chanHandle->nextIop[1].txBufFlag = (Bool) TRUE;
                            }
                            else
                            {
                                chanHandle->nextIop[1].txBuffer =
                                    (UInt8 *) &chanHandle->txTransBuf[0];
                                chanHandle->nextIop[1].txBufFlag = (Bool) FALSE;
                            }
                            txBufferPtr    = &chanHandle->nextIop[1].txBuffer;
                            txBufLengthPtr =
                                &(chanHandle->nextIop[1].txBufferLen);
                        }
                    }
                }
                else
                {
                    txBufferPtr    = &chanHandle->nextIop[0].txBuffer;
                    txBufLengthPtr = &(chanHandle->nextIop[0].txBufferLen);
                }
            }
            /* End critical section */
            Hwi_restore(hwiKey);
        }
        else
        {
            txBufferPtr    = &chanHandle->txBuffer;
            txBufLengthPtr = &(chanHandle->txBufferLen);
        }

        /* Get the current word length and loopcount for Tx and Rx */
        if (chanHandle->cfgChfmt.charLength <= 8U)
        {
            wordLength = 1U;
        }
        else if (chanHandle->cfgChfmt.charLength <= 16U)
        {
            wordLength = 2U;
        }
        else if (chanHandle->cfgChfmt.charLength <= 32U)
        {
            wordLength = 4U;
        }
        else
        {
            status = IOM_EBADIO;
        }
    }

    if (status == IOM_COMPLETED)
    {
        if ((TRUE == chanHandle->fifoEnable) &&
            (instHandle->spiHWconfig.fifoTxTrigLvl >= wordLength))
        {
            loopCount = instHandle->spiHWconfig.fifoTxTrigLvl / wordLength;
        }
        else
        {
            loopCount = (UInt32) 1;
        }

        /* If tx buff is not NULL Read from Tx Buff and write to McSPI Tx.
         * Read from McSPI Rx and put in Rx Buff. */
        for (i = 0; i < loopCount; i++)
        {
            if ((txBufferPtr != NULL) && (*txBufferPtr != NULL))
            {
                tempPtrVal = (UInt32) (*txBufferPtr);
                /* Write the data to be transmitted */
                if (wordLength == 1U)
                {
                    txData = (UInt32) (*((UInt8 *) tempPtrVal));
                }
                else if (wordLength == 2U)
                {
                    txData = (UInt32) (*((UInt16 *) tempPtrVal));
                }
                else if (wordLength == 4U)
                {
                    txData = (UInt32) (*((UInt32 *) tempPtrVal));
                }
                else
                {
                    status = IOM_EBADIO;
                    txData = 0;
                }
                McSPITransmitData(instHandle->deviceInfo.baseAddress, txData,
                                  chanHandle->chanNum);
                if ((Bool) TRUE == chanHandle->txBufFlag)
                {
                    *txBufferPtr += wordLength;
                }
                /* decrement the buffer length */
                *txBufLengthPtr           -= (UInt32) wordLength;
                instHandle->stats.txBytes += (UInt32) wordLength;
            }

            /* Read the received data */
            rxData = McSPIReceiveData(instHandle->deviceInfo.baseAddress,
                                      chanHandle->chanNum);
            tempPtrVal = (UInt32) (chanHandle->rxBuffer);
            if (wordLength == 1U)
            {
                *((UInt8 *) tempPtrVal) = (UInt8) rxData;
            }
            else if (wordLength == 2U)
            {
                *((UInt16 *) tempPtrVal) = (UInt16) rxData;
            }
            else if (wordLength == 4U)
            {
                *((UInt32 *) tempPtrVal) = (UInt32) rxData;
            }
            else
            {
                status = IOM_EBADIO;
            }
            if ((Bool) TRUE == chanHandle->rxBufFlag)
            {
                chanHandle->rxBuffer += wordLength;
            }
            /* decrement the buffer length */
            chanHandle->rxBufferLen   -= (UInt32) wordLength;
            instHandle->stats.rxBytes += (UInt32) wordLength;
        }

        /* Complete current IOP and Give app callback if Rx Buf length is 0.
         * Also start next IOP is provided by app and its in queue. */
        if (chanHandle->rxBufferLen == 0)
        {
            /* call the application completion callback function registered
             * with us during opening of the channel. */
            if (NULL != chanHandle->cbFxn)
            {
                if (TRUE == chanHandle->rxBufFlag)
                {
                    chanHandle->activeIOP->size -= chanHandle->rxBufferLen;
                }
                else
                {
                    chanHandle->activeIOP->size -= chanHandle->txBufferLen;
                }

                /* Invoke Application callback for this channel */
                (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg,
                                     chanHandle->activeIOP);
                chanHandle->activeIOP = NULL;
            }
            if ((chanHandle->nextIop[0].iop == NULL) &&
                (chanHandle->nextIop[1].iop == NULL))
            {
                /* Current IOP is completed and No IOPs present in the queue.
                 * disable all the spi transfers */
                McSPIChannelDisable((UInt32) instHandle->deviceInfo.baseAddress,
                                    chanHandle->chanNum);
                instHandle->currentActiveChannel = NULL;
            }
            else
            {
                /* Program the Next io packet in channel object */
                mcspiUpdateChanHandleFromIop(instHandle, chanHandle,
                                             chanHandle->nextIop[0].iop);
                dataparam =
                    (Mcspi_DataParam *) chanHandle->nextIop[0].iop->addr;
                /* Update Current TX Buffer and Buffer Length */
                chanHandle->txBufferLen = chanHandle->nextIop[0].txBufferLen;
                if (dataparam->outBuffer != NULL)
                {
                    chanHandle->txBuffer = chanHandle->nextIop[0].txBuffer;
                }
                /* Make the nextIop[0].iop as NULL will be updated in
                 * next ISR */
                chanHandle->nextIop[0].iop         = NULL;
                chanHandle->nextIop[0].txBuffer    = NULL;
                chanHandle->nextIop[0].txBufferLen = 0;
                chanHandle->nextIop[0].txBufFlag   = (Bool) FALSE;
            }
        }
    }
}

/**
 *  \brief   function is used after the completion of ISR
 *
 * This function is called after Interrupt routine is proccessed out.
 * This functions ensure whether driver is ready for next operation or not.
 * Also it gets the next available channel to be processed for data transfer.
 *
 * \param   instHandle [IN] pointer to the spi driver object
 *
 * \return  None
 *
 * \enter   instHandle  must be a valid pointer and should not be null.
 *
 * \leave   Not Implemented.
 */
static Void mcspiCompleteIOInIsr(Mcspi_Object *instHandle)
{
    Mcspi_ChanObj *chanHandle = NULL;
    IOM_Packet    *ioPacket   = NULL;
    UInt32         hwiKey     = (UInt32) 0x00;

    chanHandle = instHandle->currentActiveChannel;

    /* Check the Pending State                                                */
    if (TRUE == chanHandle->abortAllIo)
    {
        /* Error of Cancel IO                                                 */
        chanHandle->activeIOP->status = IOM_ABORT;

        /* Disable Receive and transmit interrupts                            */
        mcspiChIntrInit((Mcspi_Object *) instHandle,
                        (Mcspi_ChanObj *) chanHandle, FALSE);
    }
    else
    {
        chanHandle->activeIOP->status = chanHandle->currError;

        /* Disable Receive and transmit interrupts                            */
        mcspiChIntrInit(instHandle, chanHandle, FALSE);
    }

    /* disable all the spi transfers                                          */
    McSPIChannelDisable((UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
    if ((Bool) TRUE == chanHandle->spiChipSelectHold)
    {
        McSPICSDeAssert((UInt32) instHandle->deviceInfo.baseAddress,
                        chanHandle->chanNum);
    }
    /* TBD:Clear all the interrupts here, only related to the perticular
     * channel
     */
    mcspiChIntrStatClear(instHandle, chanHandle);

    /* call the application completion callback function registered
     * with us during opening of the channel
     */
    if (NULL != chanHandle->cbFxn)
    {
        if (TRUE == chanHandle->txBufFlag)
        {
            chanHandle->activeIOP->size -= chanHandle->txBufferLen;
        }
        else
        {
            chanHandle->activeIOP->size -= chanHandle->rxBufferLen;
        }

        /* power off the module                                               */
        Mcspi_localPrcmOff(instHandle, NULL);

        if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg))
        {
            /* Invoke Application callback for this channel
             *                    */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, chanHandle->activeIOP);
        }
    }

    /* There is no transaction for now.It will be set again when actual
     * transaction is to be started.
     */

    chanHandle->pendingState = (Bool) FALSE;
    chanHandle->activeIOP    = NULL;
    chanHandle->currError    = 0;

    /* Check if the abort flag is set for this channel. If set, we need to
     * remove all (empty) the pending packets from the list and send it back
     * to the upper layer. We do it here because, the packets should be dealt
     * with  in FIFO order
     */
    if (TRUE == chanHandle->abortAllIo)
    {
        while (FALSE == Queue_empty(Queue_handle(&(
                                                     chanHandle->
                                                     queuePendingList))))
        {
            /* we have atleast one packet                                     */
            ioPacket = (IOM_Packet *) Queue_get(
                Queue_handle(&(chanHandle->queuePendingList)));

            if (NULL != ioPacket)
            {
                ioPacket->status = IOM_ABORT;
                ioPacket->size   = 0;

                /* power off the module                                       */
                Mcspi_localPrcmOff(instHandle, NULL);

                /* Invoke Application callback for this channel               */
                if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg))
                {
                    (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
                }

                instHandle->stats.pendingPacket--;
            }
        }
        chanHandle->abortAllIo = (Bool) FALSE;
    }
    else
    {
        /* Initiate next transfer if any in pending queue */
        /* start the critical section                                         */
        hwiKey = (UInt32) Hwi_disable();
        /* If pending queue is empty no other IOPs disable interrupt */
        if ((Bool) TRUE ==
            Queue_empty(Queue_handle(&chanHandle->queuePendingList)))
        {
            /* No transfer pending on Current instance */
            instHandle->currentActiveChannel = NULL;
            /* End critical section */
            Hwi_restore(hwiKey);
        }
        else
        {
            /* Get next IO packet and end interrupt */
            ioPacket = (IOM_Packet *)
                       Queue_get(Queue_handle(&(chanHandle->queuePendingList)));
            Hwi_restore(hwiKey);
            mcspiPolledOrInterruptTransferStart(instHandle, chanHandle,
                                                ioPacket);
        }
    }
}

/**
 *  \brief  Function to process error interrutps during McSPI transfer
 *
 *         It will check the following errors like bit error, desync error
 *         parity error, overrun error.
 *
 *  \param  instHandle  [IN]    Pointer to the spi driver object
 *  \param  chanHandle  [IN]    Pointer to the spi channel object
 *  \param  intStatus   [IN]    Current interrupt status
 *  \return None
 */
static Void mcspiHandleErrors(Mcspi_Object  *instHandle,
                              Mcspi_ChanObj *chanHandle,
                              UInt32         intStatus)
{
    Bool isSpiError = FALSE;

    if ((NULL != instHandle) && (NULL != chanHandle))
    {
        switch (chanHandle->chanNum)
        {
            case 0:
                if ((UInt32) 0 != (intStatus &
                                   (UInt32) (MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK
                                             |
                                             (UInt32)
                                             MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK)))
                {
                    /* rxo overflow is valid only in slave mode           */
                    if (((Int32) MCSPI_COMMMODE_SLAVE ==
                         instHandle->spiHWconfig.masterOrSlave) &&
                        (((UInt32) intStatus &
                          (UInt32) MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK) !=
                         (UInt32) 0))
                    {
                        instHandle->stats.rxOverrunError++;
                    }
                    else
                    {
                        instHandle->stats.txUnderFlowError++;
                    }
                    isSpiError = (Bool) TRUE;
                }
                break;

            case 1:
                if ((UInt32) 0 != (intStatus &
                                   (UInt32) MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK))
                {
                    instHandle->stats.txUnderFlowError++;
                    isSpiError = (Bool) TRUE;
                }
                break;

            case 2:
                if ((UInt32) 0 != (intStatus &
                                   (UInt32) MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK))
                {
                    instHandle->stats.txUnderFlowError++;
                    isSpiError = (Bool) TRUE;
                }
                break;

            case 3:
                if ((UInt32) 0 != (intStatus &
                                   (UInt32) MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK))
                {
                    instHandle->stats.txUnderFlowError++;
                    isSpiError = (Bool) TRUE;
                }
                break;

            default:
                DBG_PRINT_ERR("Only four channel are supported\r\n");
                break;
        }

        if ((Bool) TRUE == isSpiError)
        {
            if ((TRUE == MCSPI_EDMAENABLE) &&
                (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode))
            {
                /* Disable the Tx and Rx  DMA transfers here                  */
                EDMA3_DRV_disableLogicalChannel(
                    (
                        EDMA3_DRV_Handle)
                    chanHandle->hEdma,
                    chanHandle->rxDmaEventNumber,
                    EDMA3_DRV_TRIG_MODE_EVENT);

                EDMA3_DRV_disableLogicalChannel(
                    (
                        EDMA3_DRV_Handle)
                    chanHandle->hEdma,
                    chanHandle->txDmaEventNumber,
                    EDMA3_DRV_TRIG_MODE_EVENT);

                EDMA3_DRV_setOptField((EDMA3_DRV_Handle) chanHandle->hEdma,
                                      chanHandle->rxDmaEventNumber,
                                      EDMA3_DRV_OPT_FIELD_TCC,
                                      chanHandle->rxDmaEventNumber);

                EDMA3_DRV_setOptField((EDMA3_DRV_Handle) chanHandle->hEdma,
                                      chanHandle->txDmaEventNumber,
                                      EDMA3_DRV_OPT_FIELD_TCC,
                                      chanHandle->txDmaEventNumber);

                EDMA3_DRV_setOptField((EDMA3_DRV_Handle) chanHandle->hEdma,
                                      chanHandle->rxDmaEventNumber,
                                      EDMA3_DRV_OPT_FIELD_TCC,
                                      chanHandle->rxDmaEventNumber);

                McSPIDMADisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    ((UInt32) MCSPI_DMA_RX_EVENT | (UInt32) MCSPI_DMA_TX_EVENT),
                    chanHandle->chanNum);
            }

            if ((TRUE == MCSPI_EDMAENABLE) &&
                (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode))
            {
                EDMA3_DRV_PaRAMRegs paramSet = {0};
                UInt32 bytesRemain           = 0;
                UInt32 actualSize = 0;
                IOM_Packet         *ioPacket = NULL;

                /* check how many bytes were xferred before EDMA was stopped  */
                EDMA3_DRV_getPaRAM(chanHandle->hEdma,
                                   chanHandle->rxDmaEventNumber,
                                   &paramSet);

                bytesRemain = (paramSet.aCnt * paramSet.bCnt);
                ioPacket    = chanHandle->activeIOP;

                assert(NULL != ioPacket);

                /* update the amount of bytes processed                       */
                actualSize      = ioPacket->size;
                ioPacket->size -= bytesRemain;

                instHandle->stats.rxBytes += (actualSize - bytesRemain);

                EDMA3_DRV_getPaRAM(chanHandle->hEdma,
                                   chanHandle->txDmaEventNumber,
                                   &paramSet);

                bytesRemain = (paramSet.aCnt * paramSet.bCnt);

                instHandle->stats.txBytes += (actualSize - bytesRemain);

                /* Update the status for this IOP                             */
                chanHandle->activeIOP->status = chanHandle->currError;

                Mcspi_localCompleteIOedmaCbk(instHandle);
            }
        }
    }
    return;
}

/**
 *  \brief  IO Control for McSPI device. Currently it is used for loopback only
 *
 * \param  handle      [IN]    McSpi Driver Channel handle.
 * \param  cmd         [IN]    Command to do operation.
 * \param  cmdArg      [IN]    Additional parameters required for the command
 * \param  param       [IN]    For future reference.
 * \param  eb          [OUT]   error block
 *
 * \return None
 *
 * \enter  handle   must be a valid pointer and should not be null.
 *         cmd      must be a valid IOCTL command.
 *         cmdArg   must be a valid pointer and should not be null.
 *         param    must be a valid pointer and should not be null.
 *         eb       if null raise error and aborts the program, if not null
 *                  and valid raises error but shall allow continuation of
 *                  execution
 *
 * \leave  Not Implemented.
 */
static Void mcspiIoctl(Ptr            handle,
                       Mcspi_ioctlCmd cmd,
                       Ptr            cmdArg,
                       Ptr            param,
                       Error_Block   *eb)
{
    Mcspi_ChanObj *chanHandle = NULL;
    Mcspi_Object  *instHandle = NULL;

    assert(NULL != handle);
    chanHandle = (Mcspi_ChanObj *) handle;
    instHandle = (Mcspi_Object *) chanHandle->instHandle;
    assert(NULL != instHandle);

    /* To remove the compiler warnings                                        */
    if (NULL != param)
    {
        param = param;
    }

    /* power ON the module                                                    */
    Mcspi_localPrcmOn(instHandle, NULL);

    if (IOCTL_MCSPI_SET_SPIEN_POLARITY == cmd)
    {
        Bool *spiEnHighPol;
        assert(NULL != cmdArg);

        spiEnHighPol = (Bool *) cmdArg;
        chanHandle->cfgChfmt.spiChipSelectEnablePol = (Bool) * spiEnHighPol;

        /* now set the value to the register                                  */
        if (TRUE == chanHandle->cfgChfmt.spiChipSelectEnablePol)
        {
            McSPICSPolarityConfig(
                (UInt32) instHandle->deviceInfo.baseAddress,
                (UInt32) MCSPI_CS_POL_HIGH,
                chanHandle->chanNum);
        }
        else
        {
            McSPICSPolarityConfig(
                (UInt32) instHandle->deviceInfo.baseAddress,
                (UInt32) MCSPI_CS_POL_LOW,
                chanHandle->chanNum);
        }
    }
    else if (IOCTL_MCSPI_SET_POLLEDMODETIMEOUT == cmd)
    {
        assert(NULL != cmdArg);

        /* Update the polledModeTimeout value                                 */
        instHandle->polledModeTimeout = *((UInt32 *) cmdArg);
    }
    else if (IOCTL_MCSPI_CANCEL_PENDING_IO == cmd)
    {
        UInt32 hwiKey = (UInt32) 0;
        /* Start of Critical Section                                          */
        hwiKey = (UInt32) Hwi_disable();

        if (MCSPI_OPMODE_DMAINTERRUPT != instHandle->opMode)
        {
            /* set the FLAG so that the IO packet can be aborted              */
            chanHandle->abortAllIo = (Bool) TRUE;
        }

        if (MCSPI_OPMODE_POLLED != instHandle->opMode)
        {
            mcspiCancelAllIo(instHandle, chanHandle);
        }

        /* End of Critical Section                                            */
        Hwi_restore(hwiKey);
    }
    else     /*IOCTL_MCSPI_SET_TRIGGER_LVL == cmd*/
    {
        if (MCSPI_OPMODE_POLLED != instHandle->opMode)
        {
            Mcspi_FifoTrigLvl *trigLevel = (Mcspi_FifoTrigLvl *) cmdArg;

            if ((MCSPI_TX_FIFO_LEN >= trigLevel->txTriggerLvl) &&
                (0 != trigLevel->txTriggerLvl))
            {
                instHandle->spiHWconfig.fifoTxTrigLvl = trigLevel->txTriggerLvl;
            }
            else
            {
                DBG_PRINT_ERR("Invalid Tx trigger level\r\n");
            }

            if ((MCSPI_RX_FIFO_LEN >= trigLevel->rxTriggerLvl) &&
                (0 != trigLevel->rxTriggerLvl))
            {
                instHandle->spiHWconfig.fifoRxTrigLvl = trigLevel->rxTriggerLvl;
            }
            else
            {
                DBG_PRINT_ERR("Rx Invalid trigger level\r\n");
            }
        }
        else
        {
            DBG_PRINT_ERR("Trigger level cant be used in the Polled mode\r\n");
        }
    }

    /* power OFF the module
     *                                                                        */
    Mcspi_localPrcmOff(instHandle, NULL);
}

/*
 *  \brief  Aborts all the pending IO in the driver.
 *
 *          This function is used to abort all the pending IO in the driver,
 *          including the current active IO.
 *
 * \param   instHandle  [IN]   Handle to the device instance
 * \param   chanHandle  [IN]   Channel handle
 *
 * \return  NONE
 *
 */
static Void mcspiCancelAllIo(Mcspi_Object  *instHandle,
                             Mcspi_ChanObj *chanHandle)
{
    UInt32      edmaNum     = 0x00;
    UInt32      bytesRemain = 0x00;
    IOM_Packet *ioPacket    = NULL;

    assert(NULL != chanHandle);
    assert(NULL != instHandle);

    /* check if the current channel to abort is having an active IOP          */
    if ((chanHandle == instHandle->currentActiveChannel) &&
        (NULL != chanHandle->activeIOP))
    {
        /* we need to abort all the IOP's held by the driver and return the
         * same to the application
         */
        if ((TRUE == MCSPI_EDMAENABLE) &&
            (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode))
        {
            EDMA3_DRV_PaRAMRegs paramSet = {0};

            /* The driver is running in the DMA mode of operation. Hence
             * first stop the DMA engine
             */
            EDMA3_DRV_disableLogicalChannel(chanHandle->hEdma,
                                            chanHandle->rxDmaEventNumber,
                                            EDMA3_DRV_TRIG_MODE_EVENT);

            EDMA3_DRV_disableLogicalChannel(chanHandle->hEdma,
                                            chanHandle->txDmaEventNumber,
                                            EDMA3_DRV_TRIG_MODE_EVENT);

            if (TRUE == chanHandle->txBufFlag)
            {
                edmaNum = chanHandle->txDmaEventNumber;
            }
            else
            {
                edmaNum = chanHandle->rxDmaEventNumber;
            }

            /* check how many bytes were transferred before the EDMA was
             * stopped
             */
            EDMA3_DRV_getPaRAM(chanHandle->hEdma, edmaNum, &paramSet);

            bytesRemain = (paramSet.aCnt * paramSet.bCnt * paramSet.cCnt);
        }
        else
        {
            /* interrupt mode of operation                                    */
            if (TRUE == chanHandle->txBufFlag)
            {
                bytesRemain = chanHandle->txBufferLen;
            }
            else
            {
                bytesRemain = chanHandle->rxBufferLen;
            }
        }

        /* get the current active packet                                      */
        ioPacket = chanHandle->activeIOP;

        /* active packet is available we will abort it                        */
        ioPacket->status = IOM_ABORT;

        chanHandle->rxBufferLen = 0;
        chanHandle->txBufferLen = 0;

        /* update the amount of bytes processed                               */
        ioPacket->size -= bytesRemain;

        instHandle->stats.rxBytes += ioPacket->size;
        instHandle->stats.txBytes += ioPacket->size;

        /* power OFF the module here                                          */
        Mcspi_localPrcmOff(instHandle, NULL);

        /* callback function is available or not                              */
        if ((NULL != chanHandle->cbFxn) && (NULL != chanHandle->cbArg) &&
            (MCSPI_OPMODE_POLLED != instHandle->opMode))
        {
            /* Invoke Application callback for this channel                   */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
        }

        chanHandle->activeIOP    = NULL;
        chanHandle->pendingState = (Bool) FALSE;
        chanHandle->currError    = 0;
    }

    /* Empty the pendList queue. Common for DMA/Interrupt Transactions        */
    while ((Bool) TRUE !=
           Queue_empty(Queue_handle(&(chanHandle->queuePendingList))))
    {
        ioPacket = (IOM_Packet *)
                   Queue_get(Queue_handle(&(chanHandle->queuePendingList)));

        ioPacket->status = IOM_ABORT;
        instHandle->stats.pendingPacket--;
        ioPacket->size = (UInt32) 0;

        /* power OFF the module here                                          */
        Mcspi_localPrcmOff(instHandle, NULL);

        /* callback function is available or not                              */
        if ((NULL != chanHandle->cbFxn) &&
            (NULL != chanHandle->cbArg))
        {
            /* Invoke Application callback for this channel                   */
            (*chanHandle->cbFxn)((Ptr) chanHandle->cbArg, ioPacket);
        }
    }

    chanHandle->abortAllIo   = (Bool) FALSE;
    chanHandle->activeIOP    = NULL;
    chanHandle->pendingState = (Bool) FALSE;
    chanHandle->currError    = (Int32) 0;

    /* No more packets to load.Disable the interrupts                         */
    mcspiChIntrInit(instHandle, chanHandle, FALSE);

    if ((chanHandle == instHandle->currentActiveChannel)
        || (NULL == instHandle->currentActiveChannel))
    {
        instHandle->currentActiveChannel = NULL;
        /* get the channel with highest priority                              */
        Mcspi_localGetNextChannel(instHandle,
                                  &(instHandle->currentActiveChannel));
        /* store for local use                                                */
        chanHandle = instHandle->currentActiveChannel;
    }
    else
    {
        chanHandle = NULL;
    }

    /* check and load next pending packet                                     */
    if (NULL != chanHandle)
    {
        /* we have atleast one packet                                         */
        ioPacket = (IOM_Packet *) Queue_get(
            Queue_handle(&(chanHandle->queuePendingList)));
        instHandle->stats.pendingPacket--;

        /* validate and update the iop                                        */
        if (NULL != ioPacket)
        {
            Mcspi_DataParam *dataParam = NULL;

            chanHandle->activeIOP = (IOM_Packet *) ioPacket;
            dataParam = (Mcspi_DataParam *) ioPacket->addr;

            assert(NULL != dataParam);

            /* Set the current buffer params correctly                        */
            chanHandle->currError = (Int32) 0;

            /* Check if the inBuffer or the outBuffer is NULL i.e,not
             * supplied and update respective buffer appropriately with
             * driver buffer
             */
            if (NULL == dataParam->inBuffer)
            {
                /* user has not suppiled the IN buffer                        */
                chanHandle->rxBufFlag = (Bool) FALSE;

                /* No alignment required here                                 */
                chanHandle->rxBuffer = (UInt8 *) &chanHandle->rxTransBuf[0];

                /* update the details of the out buffer here as it cannot
                 * be NULL (condition already checked)
                 */
                chanHandle->txBufFlag   = (Bool) TRUE;
                chanHandle->txBuffer    = dataParam->outBuffer;
                chanHandle->rxBufferLen = dataParam->bufLen;
                chanHandle->txBufferLen = dataParam->bufLen;
            }
            else if (NULL == dataParam->outBuffer)
            {
                /* user has not suppiled the IN buffer                        */
                chanHandle->txBufFlag = (Bool) FALSE;

                /* No alignment required here                                 */
                chanHandle->txBuffer = (UInt8 *) &chanHandle->txTransBuf[0];

                /* update the details of the "inbuffer" here as it cannot
                 * be NULL (condition already checked)
                 */
                chanHandle->rxBufFlag   = (Bool) TRUE;
                chanHandle->rxBuffer    = dataParam->inBuffer;
                chanHandle->rxBufferLen = dataParam->bufLen;
                chanHandle->txBufferLen = dataParam->bufLen;
            }
            else
            {
                /* Both the buffers are valid                                 */
                chanHandle->rxBufFlag   = (Bool) TRUE;
                chanHandle->txBufFlag   = (Bool) TRUE;
                chanHandle->rxBuffer    = dataParam->inBuffer;
                chanHandle->txBuffer    = dataParam->outBuffer;
                chanHandle->rxBufferLen = dataParam->bufLen;
                chanHandle->txBufferLen = dataParam->bufLen;
            }

            if ((dataParam->bufLen) > (UInt32) 0)
            {
                /* Enabling receive and error interrupts                      */
                mcspiChIntrInit(instHandle, chanHandle, (Bool) TRUE);
            } /**< if currBuffLen
               *                                             */
        }
    }
    else
    {
        /* Do nothing                                                         */
    }
}

/**
 *  \brief  function is used enable or disable the interrupt
 */

static Void mcspiChIntrInit(const Mcspi_Object  *instHandle,
                            const Mcspi_ChanObj *chanHandle,
                            Bool                 enable)
{
    UInt32 enIntr  = 0;
    UInt32 chanNum = chanHandle->chanNum;

    switch (chanNum)
    {
        case 0:
            if ((Bool) TRUE == enable)
            {
                /* For polled mode of operation, no need to enable the
                 * interrupt
                 */
                if (MCSPI_OPMODE_POLLED == instHandle->opMode)
                {
                    DBG_PRINT_ERR("No interrupt for polled mode"
                                  " of operation\r\n");
                }
                /* For DMA mode of operation, enable only the
                 * Error interrupts if 'enableErrIntr' flag is set
                 */
                else if (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode)
                {
                    /* Disable all Interrupts since it is DMA mode */
                    McSPIIntDisable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) 0xFFFF);

                    if ((Int32) MCSPI_COMMMODE_SLAVE ==
                        instHandle->spiHWconfig.masterOrSlave)
                    {
                        /* rxo overflow is valid only in slave mode*/
                        enIntr =
                            (UInt32) MCSPI_INT_RX0_OVERFLOW;
                    }
                    else
                    {
                        /* Enable only error interrupts */
                        enIntr = (
                            MCSPI_INT_TX_UNDERFLOW(chanNum) |
                            (UInt32) MCSPI_INT_RX0_OVERFLOW);
                    }
                    McSPIIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                                   enIntr);
                }
                else
                {
                    /* Enable all channel '0' interrupts                  */
                    enIntr = (UInt32) 0;
                    if ((Int32) MCSPI_COMMMODE_SLAVE ==
                        instHandle->spiHWconfig.masterOrSlave)
                    {
                        /* rxo overflow is valid only in slave mode*/
                        enIntr = (MCSPI_IRQENABLE_RX0_FULL_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK);
                    }
                    else
                    {
                        enIntr = (MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_MASK |
                                  MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX0_FULL_ENABLE_MASK);
                    }
                    if ((TRUE == chanHandle->fifoEnable) &&
                        ((Int32) MCSPI_COMMMODE_MASTER ==
                         instHandle->spiHWconfig.masterOrSlave))
                    {
                        /* Enable EOW only in master mode */
                        enIntr |= MCSPI_IRQSTATUS_EOW_MASK;
                    }
                    McSPIIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                                   enIntr);
                }
            }
            else
            {
                /* Mask OFF all the interrupts */
                McSPIIntDisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) 0xFFFF);
            }
            break;

        case 1U:
            if ((Bool) TRUE == enable)
            {
                if (MCSPI_OPMODE_POLLED == instHandle->opMode)
                {
                    DBG_PRINT_ERR("No interrupt for polled mode"
                                  " of operation\r\n");
                }
                /* For DMA mode of operation, enable only the
                 * Error interrupts if 'enableErrIntr' flag is set
                 */
                else if (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode)
                {
                    /* Enable  channel '1' Error interrupts               */
                    McSPIIntEnable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_MASK);
                }
                /* Interrupt Mode of Operation                              */
                else
                {
                    /* Enable all channel '1' interrupts                  */
                    enIntr = (UInt32) 0;
                    if ((Int32) MCSPI_COMMMODE_SLAVE ==
                        instHandle->spiHWconfig.masterOrSlave)
                    {
                        /* rxo overflow is valid only in slave mode*/
                        enIntr = (MCSPI_IRQENABLE_RX1_FULL_ENABLE_MASK);
                    }
                    else
                    {
                        enIntr = (MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_MASK |
                                  MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX1_FULL_ENABLE_MASK);
                    }
                    if ((TRUE == chanHandle->fifoEnable) &&
                        ((Int32) MCSPI_COMMMODE_MASTER ==
                         instHandle->spiHWconfig.masterOrSlave))
                    {
                        enIntr |= MCSPI_IRQSTATUS_EOW_MASK;
                    }
                    McSPIIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                                   enIntr);
                }
            }
            else
            {
                /* Disable all Interrupts */
                McSPIIntDisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) 0xFFFF);
            }
            break;

        case 2U:
            if ((Bool) TRUE == enable)
            {
                if (MCSPI_OPMODE_POLLED == instHandle->opMode)
                {
                    DBG_PRINT_ERR("No interrupt for polled mode"
                                  " of operation\r\n");
                }
                /* For DMA mode of operation, enable only the
                 * Error interrupts if 'enableErrIntr' flag is set
                 */
                else if (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode)
                {
                    /* Enable  channel '2' Error interrupts               */
                    McSPIIntEnable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_MASK);
                }
                /* Interrupt Mode of Operation                              */
                else
                {
                    /* Enable all channel '2' interrupts                  */
                    enIntr = (UInt32) 0;
                    if ((Int32) MCSPI_COMMMODE_SLAVE ==
                        instHandle->spiHWconfig.masterOrSlave)
                    {
                        /* rxo overflow is valid only in slave mode*/
                        enIntr = (MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX2_FULL_ENABLE_MASK);
                    }
                    else
                    {
                        enIntr = (MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_MASK |
                                  MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX2_FULL_ENABLE_MASK);
                    }
                    if (TRUE == chanHandle->fifoEnable)
                    {
                        enIntr |= MCSPI_IRQSTATUS_EOW_MASK;
                    }
                    McSPIIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                                   enIntr);
                }
            }
            else
            {
                /* Disable all Interrupts */
                McSPIIntDisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) 0xFFFF);
            }
            break;

        case 3U:
            if ((Bool) TRUE == enable)
            {
                if (MCSPI_OPMODE_POLLED == instHandle->opMode)
                {
                    DBG_PRINT_ERR("No interrupt for polled mode"
                                  " of operation\r\n");
                }
                /* For DMA mode of operation, enable only the
                 * Error interrupts if 'enableErrIntr' flag is set
                 */
                else if (MCSPI_OPMODE_DMAINTERRUPT == instHandle->opMode)
                {
                    /* Enable  channel '3' Error interrupts               */
                    McSPIIntEnable(
                        (UInt32) instHandle->deviceInfo.baseAddress,
                        (UInt32) MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_MASK);
                }
                /* Interrupt Mode of Operation                              */
                else
                {
                    /* Enable all channel '3' interrupts                  */
                    enIntr = (UInt32) 0;
                    if ((Int32) MCSPI_COMMMODE_SLAVE ==
                        instHandle->spiHWconfig.masterOrSlave)
                    {
                        /* rxo overflow is valid only in slave mode*/
                        enIntr = (MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX3_FULL_ENABLE_MASK);
                    }
                    else
                    {
                        enIntr = (MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_MASK |
                                  MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_MASK |
                                  MCSPI_IRQENABLE_RX3_FULL_ENABLE_MASK);
                    }
                    if (TRUE == chanHandle->fifoEnable)
                    {
                        enIntr |= MCSPI_IRQSTATUS_EOW_MASK;
                    }
                    McSPIIntEnable((UInt32) instHandle->deviceInfo.baseAddress,
                                   enIntr);
                }
            }
            else
            {
                McSPIIntDisable(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    (UInt32) 0xFFFF);
            }
            break;

        default:
            DBG_PRINT_ERR("Invalid channel \r\n");
            break;
    }
}

/**
 *  \brief  function is used clear the interrupt
 */
Void mcspiChIntrStatClear(const Mcspi_Object  *instHandle,
                          const Mcspi_ChanObj *chanHandle)
{
    UInt32 clrIntr = (UInt32) 0;
    UInt32 chanNum = chanHandle->chanNum;

    switch (chanNum)
    {
        case 0:
            /* For polled mode of operation, no need to enable the
             * interrupt
             */
            if (MCSPI_OPMODE_POLLED == instHandle->opMode)
            {
                DBG_PRINT_ERR("No interrupt for polled mode"
                              " of operation\r\n");
            }
            else
            {
                /* clear all channel '0' interrupts                       */
                clrIntr = (UInt32) 0;
                if ((MCSPI_COMMMODE_SLAVE ==
                     instHandle->spiHWconfig.masterOrSlave))
                {
                    /* rxo overflow is valid only in slave mode*/
                    clrIntr = (MCSPI_IRQSTATUS_TX0_EMPTY_MASK |
                               MCSPI_IRQSTATUS_RX0_FULL_MASK |
                               MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK);
                }
                else
                {
                    clrIntr = (MCSPI_IRQSTATUS_TX0_EMPTY_MASK |
                               MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK |
                               MCSPI_IRQSTATUS_RX0_FULL_MASK);
                }
                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    clrIntr);
            }

            break;

        case 1U:
            if (MCSPI_OPMODE_POLLED == instHandle->opMode)
            {
                DBG_PRINT_ERR("No interrupt for polled mode"
                              " of operation\r\n");
            }
            else
            {
                /* Enable all channel '0' interrupts                      */
                clrIntr = (UInt32) 0;
                clrIntr = (MCSPI_IRQSTATUS_TX1_EMPTY_MASK |
                           MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK |
                           MCSPI_IRQSTATUS_RX1_FULL_MASK);

                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    clrIntr);
            }

            break;

        case 2U:
            if (MCSPI_OPMODE_POLLED == instHandle->opMode)
            {
                DBG_PRINT_ERR("No interrupt for polled mode"
                              " of operation\r\n");
            }
            else
            {
                /* Enable all channel '0' interrupts                      */
                clrIntr = (UInt32) 0;
                clrIntr = (MCSPI_IRQSTATUS_TX2_EMPTY_MASK |
                           MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK |
                           MCSPI_IRQSTATUS_RX2_FULL_MASK);

                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    clrIntr);
            }

            break;

        case 3U:
            if (MCSPI_OPMODE_POLLED == instHandle->opMode)
            {
                DBG_PRINT_ERR("No interrupt for polled mode"
                              "of operation\r\n");
            }
            else
            {
                /* Enable all channel '0' interrupts                      */
                clrIntr = (UInt32) 0;
                clrIntr = (MCSPI_IRQSTATUS_TX3_EMPTY_MASK |
                           MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK |
                           MCSPI_IRQSTATUS_RX3_FULL_MASK);

                McSPIIntStatusClear(
                    (UInt32) instHandle->deviceInfo.baseAddress,
                    clrIntr);
            }

            break;

        default:
            DBG_PRINT_ERR("Bad channel \r\n");
            break;
    }
}

/**
 *  \brief  function is used get the next channel
 *
 *  This function is used to get the next highest priority channel. Also it
 *  checks for any pending data in that stream.
 * \param   instHandle  [IN]   device instance handle
 * \param   pChanHandle [IN]   channel handle
 *
 * \return  TRUE   if time out occured.
 */

Void Mcspi_localGetNextChannel(Mcspi_Object   *instHandle,
                               Mcspi_ChanObj **pChanHandle)
{
    UInt32 counter = (UInt32) 0;
    UInt32 chanIndexWithMaxPri = (UInt32) MCSPI_NUM_LOG_CHANS;
    UInt32 lastFoundMaxPri     = (UInt32) 0;
    UInt32 chanNum = (UInt32) 0;

    /* Since each physical channel can have NUM_LOG_CHANS number of logical
     * channels
     */
    for (counter = (UInt32) 0; counter < MCSPI_NUM_LOG_CHANS; counter++)
    {
        if ((MCSPI_DRIVERSTATE_OPENED == instHandle->chanObj[chanNum][counter].
             channelState)
            && (lastFoundMaxPri < instHandle->chanObj[chanNum][counter].
                taskPriority))
        {
            if ((Bool) FALSE == Queue_empty(
                    Queue_handle(&(instHandle->chanObj[chanNum][counter].
                                   queuePendingList))))
            {
                lastFoundMaxPri = instHandle->chanObj[chanNum][counter].
                                  taskPriority;
                chanIndexWithMaxPri = counter;
            }
        }
    }

    if ((UInt32) MCSPI_NUM_LOG_CHANS != chanIndexWithMaxPri)
    {
        *pChanHandle = &(instHandle->chanObj[chanNum][chanIndexWithMaxPri]);
    }
    else
    {
        *pChanHandle = NULL;
    }
}

/*
 *  \brief  Aborts all the pending IO in the driver.
 *
 *  This function checks if the timeout with respect to the start time has
 *  occured. The timeout and the start time is also input to the function.
 *  it checks the current time and compares with the recorded start time value
 *  and then specified timeout. The function returns TRUE in case of time out
 *  else FALSE is returned.
 *
 * \param   startValue  [IN]   Start value
 * \param   timeout     [IN]   Timeout value
 *
 * \return  TRUE   if time out occured.
 *          FALSE  if time out has not occured.
 *
 * \enter  startValue  must be a valid start value
 *         timeout     must be a valid timeout value
 *
 * \leave  Not Implemented.
 *
 *
 */
static Bool mcspiCheckTimeOut(UInt32 startValue, UInt32 timeout)
{
    UInt32 checkValue = (UInt32) 0;
    Bool   retVal     = (Bool) TRUE;

    /* get the current tick value and compare with the start value            */
    checkValue = (UInt32) Timestamp_get32();

    /* check if the current tick count counter has overflowed and suitably
     * calculate the elapsed time
     */
    if (checkValue < startValue)
    {
        checkValue =
            (UInt32) (((0xFFFFFFFFU) - startValue) + checkValue) + (UInt32) (1U);
    }
    else
    {
        checkValue = checkValue - startValue;
    }

    /* If the elapsed time is greater than start tick then set retval to TRUE
     * to indicate time out else send false
     */
    if (checkValue < timeout)
    {
        retVal = (Bool) FALSE;
    }
    else
    {
        retVal = (Bool) TRUE;
    }
    return retVal;
}

/*============================================================================*/
/*                             PRCM FUNCTIONS                                 */
/*============================================================================*/

/**
 *  \brief    Mcspi_localPrcmOn
 *
 *            This function is invoked to power on the SPI peripheral and
 *            configure it according to the operating mode. Note that this
 *            function uses different functions to power ON the module,
 *            depending on the PWRM is enabled in this driver or NOT
 *
 *  \param    instHandle  [IN] Handle to the device instance
 *
 *  \return   IOM_COMPLETED in case of success, an ERROR code in case
 *            of error.
 *
 *  \enter    instHandle    must be a valid pointer
 *
 *  \leave    Not Implemented.
 */
Void Mcspi_localPrcmOn(const Mcspi_Object *instHandle, Error_Block *eb)
{
    assert(NULL != instHandle);

    if (TRUE == instHandle->prcmPwrmEnable)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
        pmErrCode_t retVal = PM_SUCCESS;
        /* Constant list of module IDs for McSPI */
        const pmhalPrcmModuleId_t mcspiModuleIdList[] = {
            PMHAL_PRCM_MOD_MCSPI1,
            PMHAL_PRCM_MOD_MCSPI2,
            PMHAL_PRCM_MOD_MCSPI3,
            PMHAL_PRCM_MOD_MCSPI4
        };
        /* Enable the clocks for the McSPI Module */
        retVal = (pmErrCode_t) PMHALModuleModeSet(
            mcspiModuleIdList[instHandle->instNum],
            PMHAL_PRCM_MODULE_MODE_ENABLED,
            PM_TIMEOUT_INFINITE);
        assert(PM_SUCCESS == retVal);
#endif
    }
}

/**
 * \brief    Mcspi_localPrcmOff
 *
 *           This function is invoked to power off the module.
 *
 * \param    instHandle  [IN] Handle to the device instance
 *
 * \return   IOM_COMPLETED in case of success, an ERROR code in case
 *           of error.
 *
 * \enter    instHandle must be a valid channel object
 *           No pending IO
 *
 * \leave    Not Implemented.
 */
Void Mcspi_localPrcmOff(const Mcspi_Object *instHandle, Error_Block *eb)
{
    assert(NULL != instHandle);

    if (TRUE == instHandle->prcmPwrmEnable)
    {
        ; /* Do not turn off */
    }
}

