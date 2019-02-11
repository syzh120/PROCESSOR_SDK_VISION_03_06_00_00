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
 *  \file bsp_mcspiPriv.h
 *
 *  \brief MCSPI Driver private header file.
 *  @{
 */

#ifndef BSP_MCSPIPRIV_H_
#define BSP_MCSPIPRIV_H_

#include <xdc/std.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Swi.h>

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

#include <xdc/runtime/Error.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Error codes for return types                                          */
/** Base error code                                                       */
#define ERROR_BASE                        (-11)

/** SPI receive overrun error code                                        */
#define RECEIVE_OVERRUN_ERR               (ERROR_BASE - 1)

/** SPI time out error code                                               */
#define TIMEOUT_ERR                       (ERROR_BASE - 5)

/** SPI Cancel IO error code                                              */
#define CANCEL_IO_ERROR                   (ERROR_BASE - 7)

#define MAX_CHAN_PRIORITY                 (32)
/** This priority is defined so that any channel which is created by the ISR
 * can have a maximum priority of 16, the bios task will then only have a
 * maximum priority of 15.Hence the channels submitting requests from ISR
 * will have more priority always during IO                               */

/** SPI Interrupt register mask                                           */
#define INTERRUPT_MASK                    (0xFFFF)

/** Flag to indicate that Reception EDMA callback has occured             */
#define MCSPI_RX_EDMA_CALLBACK_OCCURED    (0x2U)

/** Flag to indicate that Transmission EDMA callback has occured          */
#define MCSPI_TX_EDMA_CALLBACK_OCCURED    (0x1U)

/** SPI 8 bit character length                                            */
#define MCSPI_EDMA_8_BIT_CHAR_LEN         (8U)

/** CNT flag to indicate in EDMA Transfer                                 */
#define MCSPI_ACNT_FLAG                   (2U)

/** Destination flag to indicate in EDMA Transfer                         */
#define MCSPI_DEST_INDEX_FLAG             (1U)

/** Interrupt enable bit in OPT register for edma                         */
#define MCSPI_OPT_TCINTEN_SHIFT           (0x00000014U)

#define MCSPI_MAXLINKCNT                  (2U)
/**<  Maximum number of EDMA jobs linked at a time (Must be 2).           */

/**<  Transmit EDMA channel event queue number                            */
#define MCSPI_TXEVENTQUE                  (0U)

/**<  Receive EDMA channel event queue number                             */
#define MCSPI_RXEVENTQUE                  (1U)

/**<  Generic invalidate status                                           */
#define MCSPI_STATUS_INVALID              (0xFFFF)

/**<  Generic validate status                                             */
#define MCSPI_STATUS_VALID                (0x1)

#define MCSPI_OPT_SYNCDIM_SHIFT           (0x00000002U)
/**<  Sync Type AB set bit of OPT register for edma                       */

#define MCSPI_OPT_TCC_SHIFT               (0x0000000CU)
/**<  TCC set bit in OPT register for edma                                */

#define MCSPI_OPT_TCC_MASK                (0x0003F000U)
/**<  Tcc mask in OPT register for edma                                   */

#define MCSPI_OPT_TCCMOD_SHIFT            (0x0000000BU)
/**< Transfer completion selection bit                                    */

#define MCSPI_CNT_MAX_VAL                 (0xFFFFU)
/**<  Max possible value of aCnt, bCnt and cCnt                           */

#define Mcspi_SWI_PRIORITY                (0x01)
/**< Priority of the swi thread which handles the interrupts              */

#define MCSPI_EDMA3CC_OPT_FIFO_WIDTH      (0xFFFFF8FFU)
/**< Set FIFO Width for edma transfer                                     */

#define MCSPI_EDMA3CC_OPT_SAM_CONST_MODE  (0x00000001U)
/**< Set SAM in Constant Addressing Mode                                  */

#define MCSPI_EDMA3CC_OPT_DAM_CONST_MODE  (0x00000002U)
/**< Set DAM in Constant Addressing Mode                                  */

#define MCSPI_EDMA3CC_OPT_SAM_INCR_MODE   (0xFFFFFFFEU)
/**< Set SAM in Increment Mode                                            */

#define MCSPI_EDMA3CC_OPT_DAM_INCR_MODE   (0xFFFFFFFDU)
/**< Set DAM in Increment Mode                                            */

#define MCSPI_EDMA3CC_OPT_SAM_DAM_INCR_MODE (0xFFFFFFFCU)
/**< Set DAM in Increment Mode                                            */

#define MCSPI_EDMA3CC_OPT_SYNC_AB         (0x00000004U)
/**< It is AB-synchronized                                                */

#define MCSPI_EDMA3CC_OPT_SYNC_MASK_VALUE (0xFFFFFFFFU)
/**< Mask Value for Transfer Synchronization                              */

#define MCSPI_EDMA3CC_PARAM_LINK_ADDRESS  (0xFFFFU)
/**< Set link Address                                                     */

#define MCSPI_EDMA3CC_PARAM_LINK_ADDR_MASK_VALUE (0x0000FFFFU)
/**< link Address Mask Value                                              */

#define MCSPI_EDMA3CC_PARAM_ACNT          (1U)
/**< aCnt Value                                                           */

#define MCSPI_EDMA3CC_OPT_STATIC_SHIFT    (0x00000003U)
/**< STATIC Token                                                         */

#define MCSPI_EDMA3CC_SRC_BINDEX          (1U)
/**< Src BIndex Value                                                     */

#define MCSPI_EDMA3CC_DST_BINDEX          (1U)
/**< Dst BIndex Value                                                     */

#define MCSPI_EDMA3CC_OPT_SYNC_A          (0x01U)
/**< It is A-synchronized                                                 */

#define MCSPI_EDMA3CC_OPT_SYNCDIM_SHIFT   (3U)
/**< Transfer synchronization dimension Shift Value                       */

#define MCSPI_EDMA3CC_COUNT_VALUE         (0xFFFFU)
/**< Count Value                                                          */

#define MCSPI_MAX_PWRM_EVENTS             (PWRM_INVALIDEVENT)
/**< Max number of PWRM events for which the mcasp will register          */

#define MCSPI_MAX_PWRM_CONSTRAINTS        (PWRM_DISALLOWEDSLEEPSTATE_MASK)
/**< Max number of constraints for which a moudule can register           */

/** McSpi driver state
 *  McSPi driver state enums used to track the driver state.
 */
typedef enum
{
    MCSPI_DRIVERSTATE_DELETED,

    MCSPI_DRIVERSTATE_CREATED,

    MCSPI_DRIVERSTATE_INITIALIZED,

    MCSPI_DRIVERSTATE_OPENED,

    MCSPI_DRIVERSTATE_CLOSED,

    MCSPI_DRIVERSTATE_DEINITIALIZED,

    MCSPI_DRIVERSTATE_POWERED_DOWN,

    MCSPI_DRIVERSTATE_PWRM_SUSPEND
} Mcspi_DriverState;

/**
 *  \brief  Uart structure to hold the instance specific information.
 */
typedef struct
{
    UInt32                 baseAddress;
    UInt32                 cpuEventNumber;
    UInt32                 numOfPhyChannels;
    DmaEvtList             dmaEvtList[MCSPI_MAX_CHAN_SUPPORTED];
    UInt32                 inputFrequency;
    UInt32                 pwrmPrcmId;
    UInt32                 prcmInstance;
    UInt32                 maxChipSelect;
#if defined (TI814x_M3)
    Mcspi_CrossBarEvtParam crossBarEvtParam;
#endif
} Mcspi_HwInfo;

typedef struct
{
    IOM_Packet *iop;
    /** Current IO packet                                                 */

    UInt8      *txBuffer;
    /**< User(or driver) buffer for TX operation of transceive operation  */

    UInt32      txBufferLen;
    /**< Length of the TX buffer                                          */

    Bool        txBufFlag;
} Mcspi_Next_Iop;

/**
 *  \brief  Structure of the channel object
 */
typedef struct
{
    UInt32            mode;
    /** channel's mode of operation(Input or output)                      */

    UInt32            chanNum;

    Int32             channelState;
    /** Mcspi_DriverState - state of the SPI Either created or deleted    */

    IOM_TiomCallback  cbFxn;
    /** to notify client when I/O complete                                */

    Ptr               cbArg;
    /**  argument for cbFxn()                                             */

    Ptr               instHandle;
    /** Spi Handle to access the spi params                               */

    Ptr               hEdma;
    /** Handle used for Edma                                              */

    UInt32            wordCntInFifoMode;
    /** To keep track of the number of word transfered.                   */

    UInt32            rxDmaEventNumber;
    /** The edma event for a Rx specific channel                          */

    UInt32            txDmaEventNumber;
    /** The edma event for a Tx specific channel                          */

    Bool              dmaEnable;
    /** TRUE  - DMA enabled, FALSE - DMA disabled                         */

    Bool              fifoEnable;
    /** TRUE  - FIFO enabled, FALSE - FIFO disabled                       */

    Bool              spiChipSelectHold;
    /** Sets the FORCE bit in the Conf register, if the slave requires to
     * hold the SPIEN during its transaction the user can select this as a
     * channel parameter
     * TRUE  -  SPIEN will be held its active state
     * FALSE -  SPIEN will not be held its active state after each and every spi
     * word transaction
     */

    IOM_Packet       *activeIOP;
    /** Current IO packet                                                 */

    Mcspi_DataParam   dataParam;
    /** Current data transfer parameters                                  */

    Bool              pendingState;
    /** Shows whether io is in pending state or not                       */

    Bool              abortAllIo;
    /** Shows whether all IO should be aborted                            */

    Int32             currError;
    /** current error flag                                                */

    UInt8            *txBuffer;
    /**< User(or driver) buffer for TX operation of transceive operation  */

    UInt8            *rxBuffer;
    /**< User(or driver) buffer for RX operation of transceive operation  */

    Queue_Struct      queuePendingList;
    /** pending Iop List head                                             */

    UInt32            taskPriority;
    /**this will hold the priority of the task that created this channel  */

    UInt32            txBufferLen;
    /**< Length of the TX buffer                                          */

    UInt32            rxBufferLen;
    /**< Length of the RX buffer                                          */

    Bool              txBufFlag;
    /**< Flag to indicate if the TX buffer is suppiled by user or is NULL *
     * (TRUE if user has supplied else FALSE)                             */

    Bool              rxBufFlag;
    /**< Flag to indicate if the TX buffer is suppiled by user or is NULL *
     * (TRUE if user has supplied else FALSE)                             */

    UInt8             txTransBuf[128];
    /** Buffer to be used when the user supplied buffer is NULL           */

    UInt8             rxTransBuf[128];
    /** Buffer to be used when the user supplied buffer is NULL           */

    Mcspi_ConfigChfmt cfgChfmt;
    /** Data Format Configuration values                                  */

    Int32             chipSelTimeControl;
    /** Mcspi_ChipSelTimectrl -
     * Number of interface clock cycles introduced between CS toggling and
     * first or last edge of SPI clock*/

    Queue_Struct      queueFloatingList;
    /**<  list to manage floating packets in DMA                          */

    IOM_Packet       *tempPacket;
    /**<  Temp IOP holder                                                 */

    volatile Bool     isTempPacketValid;
    /**<  Valid packet flag in EDMA callback                              */

    Int32             submitCount;
    /**<  Number of submit calls pending                                  */

    UInt32            pramTblRx[2U];
    /**<  Logical channel numbers of EDMA, which are used for linking     */

    UInt32            pramTblAddrRx[2U];
    /**<  Physical address of logical channel numbers of EDMA, which      *
     * are used for linking                                               */

    UInt32            pramTblTx[2U];
    /**<  Logical channel numbers of EDMA, which are used for linking     */

    UInt32            pramTblAddrTx[2U];
    /**<  Physical address of logical channel numbers of EDMA, which      *
     * are used for linking                                               */

    UInt32            nextLinkParamSetToBeUpdated;
    /**<  Used to store the next index of link param to be updated        */

    Int               currentPacketErrorStatus;
    /**<  This member will hold the error status -normally updated from   *
     * cpu interrupt thread and is used in EDMA completion thread for     *
     * updating the error code in IOP                                     */

    volatile UInt32   edmaCbCheck;
    /** Use to check occurance of EDMA callback                           */

    Bool              enableErrIntr;
    /** This boolean enables/disables error Interrupts in DMA mode of
     * operation                                                          */
    Mcspi_Next_Iop    nextIop[2];
} Mcspi_ChanObj;

/**
 *  \brief module-wide state
 *
 *  inUse in module state points to an array whose size is soc specific
 *  Pointer used to match IDriver codebase.
 */
typedef struct
{
    Bool *inUse;
    /**< Maintain inUse state of each McSPI device                        */
} Mcspi_Module_State;

/*--------------------------internal structures --------------------------*/
/** instance structure
 *
 * There is one instance structure per SPI instance. maximum number of
 * structures is given by {@link #numInstances}
 */
typedef struct
{
    Int                    instNum;
    /** Instance number of this instance                                   */

    Int32                  devState;
    /** Mcspi_DriverState -
     * state of the SPI Either created or deleted
     */

    Int32                  opMode;
    /** Mcspi_OpMode - Mode of operation                                   */

    Mcspi_HwInfo           deviceInfo;
    /** instance specific information                                      */

    Mcspi_ChanObj          chanObj[MCSPI_MAX_CHAN_SUPPORTED][
        MCSPI_NUM_LOG_CHANS];
    /** channel objects for the SPI                                        */

    UInt32                 numOpens;
    /** Number of channels opened                                          */

    Int32                  edma3EventQueue;
    /** Edma event Q to be requested, while requesting an EDMA3 channel    */

    Bool                   isSingleChMasterMode;
    /** This is to indicate that the single channel master mode is enabled,
     * if it is set then no other channel is allowed to open
     */

    Bool                   isFifoEnabled;
    /** To indicate that the fifo is enabled or not. If it is enabled then
     * this variable will be TRUE, otherwise FALSE.
     */

    UInt32                 numOfPhyChannels;
    /** The number of physical channels available in a perticular spi
     * instance
     */

    UInt16                 hwiNumber;
    /** Hardware interrupt number                                          */

    Bool                   enableCache;
    /** Submitted buffers are in cacheable memory                          */

    HWConfigData           spiHWconfig;
    /** SPI Hardware configurations                                        */

    Bool                   dmaChanAllocated;
    /** Flag to inidicate EDMA channels allocation status                  */

    UInt32                 polledModeTimeout;
    /** Timeout to for the io operation                                    */

    Mcspi_ChanObj         *currentActiveChannel;
    /** This specifies the current active channel                          */

    Bool                   isSlaveChannelOpened;
    /**This boolean track for having only one slave channel                */

    Semaphore_Struct       syncSem;
    /** Semaphore to sync multiple tasks during the polled mode operation  */

    Bool                   prcmPwrmEnable;
    /** Option to enable or disable the PSC control in the driver          */

    pwrmInfo               mcspiPwrmInfo;
    /** structure to hold the PWMR related information                     */

    Int                    prcmDevId;
    /** prcm device ID                                                     */

    Hwi_Handle             hwiHandle;
    /** Handle to the HWI created (only used in case of ARM)               */

    Hwi_Struct             hwiStruct;
    /** Struct for static alloc of hwiHandle                               */

    Stats                  stats;
    /** This is to collect the statistics info                             */
#if defined (TI814x_M3)
    Mcspi_CrossBarEvtParam crossBarEvtParam;
    /** Cross bar event params                                             */
#endif
} Mcspi_Object;

/** ISR function pointer definition                                        */
typedef void (*Mcspi_isr)(Ptr arg0);

/* ========================================================================== */
/*                             Shared Functions                               */
/* ========================================================================== */

Int32 Mcspi_localEdmaChannelRequest(Mcspi_Object  *instHandle,
                                    Mcspi_ChanObj *chanHandle,
                                    Error_Block   *eb);

Int Mcspi_localEdmaTransfer(Mcspi_Object    *instHandle,
                            Mcspi_DataParam *dataParam);

Void Mcspi_localCallbackReceive(UInt               tcc,
                                EDMA3_RM_TccStatus edmaStatus,
                                Ptr                appData);

Void Mcspi_localCallbackTransmit(UInt               tcc,
                                 EDMA3_RM_TccStatus edmaStatus,
                                 Ptr                appData);

Void  Mcspi_localGetNextChannel(Mcspi_Object   *instHandle,
                                Mcspi_ChanObj **pChanHandle);

Void Mcspi_localPrcmOn(const Mcspi_Object *instHandle, Error_Block *eb);

Void Mcspi_localPrcmOff(const Mcspi_Object *instHandle, Error_Block *eb);

Void Mcspi_localCompleteIOedmaCbk(Mcspi_Object *instHandle);

Void Mcspi_ChOnOff(const Mcspi_Object *instHandle, UInt32 chanNum, Bool enable);

extern UInt32 Mcspi_edmaChanNum[MCSPI_MAX_CHAN_SUPPORTED];

/************** EDMA Related ************/

Int32 Mcspi_localSetupEdmaDuringOpen(Mcspi_ChanObj *chanHandle);
Void Mcspi_localLoadPktToEdma(Mcspi_ChanObj    *chanHandle,
                              const IOM_Packet *ioPacket);
Int32 Mcspi_localUpdtDtPktToLnkPrms(Mcspi_ChanObj    *chanHandle,
                                    const IOM_Packet *ioPacket);
Int32 Mcspi_localEdmaChanPaRAMsetup(Mcspi_ChanObj *chanHandle);
Int32 Mcspi_localEdmaUpdateParams(Mcspi_ChanObj       *chanHandle,
                                  EDMA3_DRV_PaRAMRegs *rxParamSet,
                                  EDMA3_DRV_PaRAMRegs *txParamSet);
Void Mcspi_UpdateBuffToPrgmEdma(Mcspi_ChanObj    *chanHandle,
                                const IOM_Packet *ioPacket);
Int32 mcspiEdmaModeTransfer(const Mcspi_Object *instHandle,
                            Mcspi_ChanObj      *chanHandle,
                            IOM_Packet         *ioPacket);
Void mcspiChIntrStatClear(const Mcspi_Object  *instHandle,
                          const Mcspi_ChanObj *chanHandle);
#ifdef __cplusplus
}
#endif

#endif  /*BSP_MCSPIPRIV_H_ */

/*  @}  */
