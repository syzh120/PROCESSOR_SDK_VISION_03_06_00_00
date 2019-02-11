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
 *  \file bspdrv_uartPriv.h
 *
 *  \brief Internal Driver header file
 *  @{
 */
#ifndef BSP_DRV_UART_DRIV_H_
#define BSP_DRV_UART_DRIV_H_

#include <xdc/std.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Swi.h>
#include <xdc/runtime/Error.h>
#include <ti/drv/bsp_lld/uart/bsp_uart.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

/* Include Family specific hwi files */
#if defined (__TI_ARM_V7M4__) || defined (BUILD_M3)
#include <ti/sysbios/family/arm/m3/Hwi.h>
#elif defined (_TMS320C6X)
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>
#elif defined (__ARM_ARCH_7A__)
#include <ti/sysbios/family/arm/gic/Hwi.h>
#elif defined (BUILD_A8)
#include <ti/sysbios/family/arm/a8/intcps/Hwi.h>
#elif defined (BUILD_ARP32)
#include <ti/sysbios/family/arp32/Hwi.h>
#else
#include <ti/sysbios/hal/Hwi.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BSP_UART_TPOLL_MSECS                    (1U)
/**< Poll time in milliSeconds                                                */

#define BSP_UART_TXRX_ENABLE                    (0xE003U)
/**< Mask to enable Rx and Tx                                                 */

#define BSP_UART_TXRX_DISABLE                   (0x0000U)
/**< Mask to edisable Rx and Tx                                               */

#define BSP_UART_OPT_TCINTEN_SHIFT              (0x00000014U)
/**< Interrupt enable bit in OPT register for edma                            */

#define BSP_UART_OPT_TCINTEN          (1U)
/**< Interrupt enable bit value in OPT register for edma                      */

#define BSP_UART_MAX_PWRM_EVENTS                (PWRM_INVALIDEVENT)
/**< Max number of PWRM events for which the uart will register               */

#define BSP_UART_MAX_PWRM_CONSTRAINTS           (PWRM_DISALLOWEDSLEEPSTATE_MASK)
/**< Max number of constraints for which a moudule can register               */

#define BSP_UART_TRANSMITTER_EMPTY              (0x20U)
/**< Bit position to find if the transmitter is empty                         */

#define BSP_UART_FIFO_DISABLED_CHUNK_SIZE           (1U)
/**< Chunk Size When FIFO is Disabled                                         */

#define BSP_UART_ISR_STATUS             (0x01U)
/**< ISR status initial value                                                 */

#define BSP_UART_OS_CHECKTIMEOUT_COUNT_VALUE    (0xFFFFFFFFFFFFFFFFU)
/**< Count Value for OS CHECK TIME OUT                                        */

#define BSP_UART_DELAY_COUNT_VALUE          (0xFFFFFU)
/**< Delay Count Value                                                        */

#define BSP_UART_INVALID_INT_NUM            (0xFFU)
/**< Invalid Interrupt Number                                                 */

#define BSP_UART_EDMA_BASE_ADDR                 (0x40000000U)
/**< EDMA_BASE_ADDR for DM814x DSP                                            */

#define BSP_UART_EDMA3CC_OPT_TCC_MASK           (0x0003F000U)
/**< EDMA OPT TCC Mask value                                                  */

#define BSP_UART_EDMA3CC_OPT_TCC_SHIFT          (0x0000000CU)
/**< EDMA OPT TCC Shift value                                                 */

#define BSP_UART_ERROR_COUNT            (0x00FFFFFFU)
/**< Count Value to check error in the recieved byte                          */

#define BSP_UART_EDMA3CC_OPT_FIFO_WIDTH         (0xFFFFF8FFU)
/**< Set FIFO Width for edma transfer                                         */

#define BSP_UART_EDMA3CC_OPT_SAM_CONST_MODE         (0x00000001U)
/**< Set SAM in Constant Addressing Mode                                      */

#define BSP_UART_EDMA3CC_OPT_DAM_CONST_MODE         (0x00000002U)
/**< Set DAM in Constant Addressing Mode                                      */

#define BSP_UART_EDMA3CC_OPT_SAM_INCR_MODE          (0xFFFFFFFEU)
/**< Set SAM in Increment Mode                                                */

#define BSP_UART_EDMA3CC_OPT_DAM_INCR_MODE          (0xFFFFFFFDU)
/**< Set DAM in Increment Mode                                                */

#define BSP_UART_EDMA3CC_OPT_SYNC_AB            (0x00000004U)
/**< It is AB-synchronized                                                    */

#define BSP_UART_EDMA3CC_OPT_SYNC_MASK_VALUE            (0xFFFFFFFFU)
/**< Mask Value for Transfer Synchronization                                  */

#define BSP_UART_EDMA3CC_PARAM_LINK_ADDRESS         (0xFFFFU)
/**< Set link Address                                                         */

#define BSP_UART_EDMA3CC_PARAM_LINK_ADDR_MASK_VALUE         (0x0000FFFFU)
/**< link Address Mask Value                                                  */

#define BSP_UART_EDMA3CC_PARAM_ACNT         (1U)
/**< aCnt Value                                                               */

#define BSP_UART_EDMA3CC_SRC_BINDEX         (1U)
/**< Src BIndex Value                                                         */

#define BSP_UART_EDMA3CC_DST_BINDEX         (1U)
/**< Dst BIndex Value                                                         */

#define BSP_UART_EDMA3CC_OPT_SYNC_A         (0x01U)
/**< It is A-synchronized                                                     */

#define BSP_UART_EDMA3CC_OPT_SYNCDIM_SHIFT          (3U)
/**< Transfer synchronization dimension Shift Value                           */

#define BSP_UART_EDMA3CC_COUNT_VALUE            (UInt32) (0xFFFFU)
/**< Count Value                                                              */

#define BSP_UART_TX_FIFO_WAIT_PERIOD        (1U)

/**
 *  enum Uart_DriverState
 *  \brief   Uart driver state enums used to track the driver state
 */
typedef enum
{
    UART_DRIVERSTATE_DELETED,
    UART_DRIVERSTATE_CREATED,
    UART_DRIVERSTATE_INITIALIZED,
    UART_DRIVERSTATE_OPENED,
    UART_DRIVERSTATE_CLOSED,
    UART_DRIVERSTATE_DEINITIALIZED,
    UART_DRIVERSTATE_POWERED_DOWN,
    UART_DRIVERSTATE_PWRM_SUSPEND
} Uart_DriverState;

/**
 *  enum Uart_Intr
 *  \brief   Uart Interrupts
 */
typedef enum
{
    UART_INTR_RHR = 1U,
    /**< Data ready in receive register                                     */
    UART_INTR_THR = 2U,
    /**< Transmitter empty interrupt                                        */
    UART_INTR_RLS = 4U,
    /**< A line status changed or an error condition was detected           */
    UART_INTR_MS = 8U,
    /**< Modem status interrupt                                             */
    UART_INTR_ALL = 0xFU
                    /**< All interrupts */
} Uart_Intr;

/**
 *  enum Uart_IoMode
 *  \brief  Mode is INPUT or OUTPUT
 */
typedef enum
{
    UART_INPUT = 1,
    UART_OUTPUT
} Uart_IoMode;

/**
 *  struct Uart_DevParams
 *  \brief  Internal data structure maintaining Uart device instance options
 */
typedef struct
{
    Bool             fifoEnable;
    /**< enable fifo                            */
    Bool             loopbackEnabled;
    /**< Enable loopback                        */
    Int32            baudRate;
    /**< Baudrate of Operation
     *  Refer #Uart_BaudRate for valid values   */
    Int32            stopBits;
    /**< Stopbits of Operation
     *  Refer #Uart_NumStopBits for valid values */
    Int32            charLen;
    /**< Character Length
     *  Refer #Uart_CharLen for valid values    */
    Int32            parity;
    /**< Parity of Operation
     *  Refer #Uart_Parity for valid values     */
    Int32            rxThreshold;
    /**< Rx FIFO trigger level
     *  Refer #Uart_RxTrigLvl for valid values */
    Int32            txThreshold;
    /**< Rx FIFO trigger level
     *  Refer #Uart_TxTrigLvl for valid values */
    Uart_FlowControl fc;
    /**< Flow Control                           */
    UInt16           softTxFifoThreshold;
    /**< softTxFifoThreshold                    */
    Bool             prcmPwrmEnable;
    /**< Enable power management                */
} Uart_DevParams;

/**
 *  struct Uart_HwInfo
 *  \brief  Uart structure to hold the instance specific information.
 */
typedef struct
{
    UInt32                baseAddress;
    UInt32                cpuEventNumber;
    UInt32                rxDmaEventNumber;
    UInt32                txDmaEventNumber;
    UInt32                inputFrequency;
    UInt32                pwrmPrcmId;

#if defined (TI814x_M3) || defined (C6A811x_M3)
    Uart_CrossBarEvtParam crossBarEvtParam;
    /* Cross bar event params                                                 */
#endif
} Uart_HwInfo;

#ifdef BIOS_PWRM_ENABLE
/**
 *  struct Uart_PwrmInfo
 *  \brief  Structure for holding the PWRM related info
 */
typedef struct
{
    Int32                 pllDomain;
    /**< Pll domain to be used for the device
     *  Refer #Uart_pllDomain for valid values         */
    Bool                  ioSuspend;
    /**< whether the driver is in IO suspend mode (PWRM change is in progress)*/

    UInt32                constraintMask;
    /**< Constraint mask (for information only)                               */

    UInt32                dependencyCount;
    /**< Current dependency count when the driver is going for sleep or
     * deepsleep                                                              */

    PWRM_Event            pwrmEvent;
    /**< Current pwrm event being processed                                   */

    PWRM_NotifyHandle     notifyHandle[Uart_MAX_PWRM_EVENTS];
    /**< Handles required for unregistering of the events with PWRM           */

    Fxn                   delayedCompletionFxn[Uart_MAX_PWRM_EVENTS];
    /**< delayed completion callback function pointer                         */

    PWRM_ConstraintHandle constraintHandle[Uart_MAX_PWRM_CONSTRAINTS];
    /**< Handles required for unregistering of the constraints with PWRM      */
} Uart_PwrmInfo;
#endif

/**
 *  struct Uart_ChanObj
 *  \brief  Structure of the channel object
 */
typedef struct
{
    Int32               status;
    /**< Flag to tell channel object resource is used or free
     *  Refer #Uart_DriverState for valid values                              */

    Int32               mode;
    /**< mode of the channel i.e INPUT or OUTPUT mode
     *  Refer #Uart_IoMode for valid values                                   */

    IOM_TiomCallback    cbFxn;
    /**< Callback to the application                                          */

    Ptr                 cbArg;
    /**< Argument to be passed in the callback                                */

    Queue_Struct        queuePendingList;
    /**< pending Iop List head                                                */

    IOM_Packet         *activeIOP;
    /**< Current Active Packet under progress in the channel                  */

    UInt8              *activeBuf;
    /**< Buffer address of the current packet                                 */

    UInt32              bytesRemaining;
    /**< Bytes remaining for the completion of the current packet             */

    UInt32              chunkSize;
    /**< No. of bytes to be transferred per operation (i.e FIFO Size or 1)    */

    Ptr                 devHandle;
    /**< Handle to the Device                                                 */

    UInt32              errors;
    /**< Counts how many errors encountered per IOP request                   */

    Ptr                 hEdma;
    /**< Handle to DMA object                                                 */

    UInt32              edmaTcc;
    /**< Transfer complete code number                                        */

    UInt32              edmaChId;
    /**< DMA Channel                                                          */

    UInt16              edmaTC;
    /**< EDMA TC to be used                                                   */

    UInt32              edmaLinkChId;
    /**< DMA Link Channel - used to transfer last non-multiple of threshold
     *   bytes. */
    UInt32              edmaLinkChPhyAddr;
    /**< DMA Link Channel physical address. */

    Bool                ioCompleted;
    /**< To workaround the EDMA error interrupt issue                         */

    Bool                optFlag;
    /**< Flag used to get paramSet register value in EDMA mode                */

    UInt32              optValue;
    /**< Used to store opt value in PaRAM register                            */

    Uart_GblErrCallback gblErrCbkFxn;
    /**< Function registered to notify of error conditions                    */

    Ptr                 gblErrCbkArg;
    /**< Callback argument to be used by the driver for the callback          */

    Bool                abortAllIo;
    /* Flag to indicate that the packet abort is in progress                  */
} Uart_ChanObj;

/**
 *  struct Uart_Module_State
 *  \brief module-wide state
 *
 *  inUse in module state points to an array whose size is soc specific
 *  Pointer used to match IDriver codebase.
 */
typedef struct
{
    Bool *inUse;
    /**< Maintain inUse state of each uart device                             */
} Uart_Module_State;

/**
 *  struct Uart_Object
 *  \brief per-instance state
 */
typedef struct
{
    UInt32                instNum;
    /**< Instance number or device ID of the UART                             */

    UInt32                chunkSize;
    /**< Chunksize                                                            */

    Int32                 opMode;
    /**< Mode of operation
     *  Refer #Uart_IoMode for valid values                                   */

    Uart_DevParams        devParams;
    /**< Uart device Params                                                   */

    Int32                 devState;
    /**< Driver State (deleted or created)
     *  Refer #Uart_DriverState for valid values
     *  */

    Uart_ChanObj          xmtChanObj;
    /**< transmiiter channel                                                  */

    Uart_ChanObj          rcvChanObj;
    /**< receiver channel                                                     */

    Uart_HwInfo           deviceInfo;
    /**< Instance specific information                                        */

    UInt16                hwiNumber;
    /**< Hardware interrupt Number                                            */

    Bool                  enableCache;
    /**< Submitted buffers are in cacheable memory                            */

    Uart_Stats            stats;
    /**< UART specific stats                                                  */

    Swi_Handle            txTskletHandle;
    /**< Tasklet(Software int) handle                                         */

    Swi_Struct            txTskletStruct;
    /** Struct for static alloc of txTskletHandle                             */

    Swi_Handle            rxTskletHandle;
    /**< Tasklet(Software int) handle                                         */

    Swi_Struct            rxTskletStruct;
    /** Struct for static alloc of rxTskletHandle                             */

    UInt32                polledModeTimeout;
    /**< Timeout used in polled mode - could be changed by an IOCTL           */

    Semaphore_Struct      readSyncSem;
    /**< sync semaphore object for uart read (used in the polled mode transfer
     * for sync between multiple tasks IO submit requests)
     */

    Semaphore_Struct      writeSyncSem;
    /**< sync semaphore object for uart write (used in the polled mode transfer
     * for sync between multiple tasks IO submit requests)
     */

    Bool                  uartConfigured;
    /**< This boolean ensures that Uart is configured only once               */
#ifdef BIOS_PWRM_ENABLE
    Uart_pwrmInfo         pwrmInfo;
#endif
    /**< structure to hold the PWMR related information                       */

    Hwi_Handle            hwiHandle;
    /**< Handle to the HWI created (only used in case of ARM)                 */

    Hwi_Struct            hwiStruct;
    /** Struct for static alloc of hwiHandle                                  */

    Ptr                   prcmHandle;
    /**< Handle to the prcm instance to be used to switch on the instance     */

    Int                   prcmDevId;
    /**< prcm device ID */

#if defined (TI814x_M3) || defined (C6A811x_M3)
    Uart_CrossBarEvtParam crossBarEvtParam;
    /* Cross bar event params                                                 */
#endif
} Uart_Object;

/* ========================================================================== */
/*                             Shared Functions                               */
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
typedef void (*Uart_pspUartIsr)(UArg arg);
#ifdef __cplusplus
}
#endif
extern void Uart_localIsrEdma(UInt32 tcc, EDMA3_RM_TccStatus status,
                              Ptr appData);

extern Int32 Uart_localStartEdmaTransfer(Uart_ChanObj *chanHandle,
                                         UInt32        cmd,
                                         Error_Block  *eb);

Int32 Uart_localPrcmOn(const Uart_Object *instHandle, Error_Block *eb);
Int32 Uart_localPrcmOff(const Uart_Object *instHandle, Error_Block *eb);
extern void Uart_localCompleteCurrentIO(Uart_ChanObj *chanHandle);
extern void Uart_loadPendedIops(Uart_ChanObj *chanHandle);
Int32 Uart_localMakeFCR(const Uart_Object  *instHandle,
                        const Uart_TrigLvl *trigLevel,
                        UInt32             *fcrValue);

#ifdef __cplusplus
}
#endif

#endif  /*BSP_DRIV_UART_DRIV_H_ */

/*  @}  */
