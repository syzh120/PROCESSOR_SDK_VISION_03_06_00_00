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
 *  \defgroup BSP_DRV_UART_API UART Driver API
 *
 *  @{
 */

/**
 *  \file bsp_uart.h
 *
 *  \brief Introduction
 *
 *  This file contains the interfaces, data types and symbolic definitions
 *  that are needed by the application to utilize the serivces of the UART
 *  device driver.
 *
 *  UART Controller
 *  This module is a Universal Asynchronous Receiver/Transmitter (UART) with a
 *  VBUS slave interface. This module performs serial-to-parallel conversion on
 *  data received from a peripheral device or modem, and parallel-to-serial
 *  conversion on data received from the VBUS central resource. The UART module
 *  includes complete modem control capability and an interrupt system that can
 *  be tailored to minimize software management of the communication link. This
 *  module also includes a programmable baud rate generator capable of dividing
 *  a reference clock by divisors from 1 to 65,535 to produce a 16 x clock
 *  driving the internal logic.
 *
 *  SYS/BIOS System
 *  SYS/BIOS is a real time kernel provided by TI to use with its
 *  DSP processors.
 *
 *  IMP: Define to turn OFF parameter checking.
 *  Use -DPSP_DISABLE_INPUT_PARAMETER_CHECK when building library
 *
 */

#ifndef BSP_UART_H_
#define BSP_UART_H_

#include <xdc/std.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/csl/csl_uart.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Number of channels per uart instance
 */
#define BSP_UART_NUM_CHANS (2)

/**
 *  \brief Maximum number of iterations allowed within ISR to check the
 *         RX/TX status.
 */
#define BSP_UART_MAX_ISR_LOOP (UInt32) (5)

/**
 *  \brief Tasklet priority for TX interrupt handling in SWI context of DSP
 */
#define BSP_UART_TASKLET_PRIORITY (1)

/**
 *  \brief Uart FIFO Size
 */
#define BSP_UART_FIFO_SIZE (64U)

/**
 *  \brief Baud Rate Multiplier
 */
#ifdef PLATFORM_ZEBU
    #define BSP_UART_BAUD_MULTIPLIER (13U)
/**
 *  \brief Uart Mode
 */
    #define UART_OPER_MODE UART13x_OPER_MODE
#else
    #define BSP_UART_BAUD_MULTIPLIER (16U)
/**
 *  \brief Uart Mode
 */
    #define UART_OPER_MODE (UART16x_OPER_MODE)
#endif


/**
 *  \brief Timeout in ms used for TX FIFO empty at the time of delete. Three
 *  seconds is more than sufficient to transfer 64 bytes (FIFO size) at the
 *  lowest baud rate of 2400.
 */
#define BSP_UART_TRANSMITEMPTY_TRIALCOUNT   (3000U)

/**
 * \brief Value to be used for infinte wait in case of polled mode timeout
 */
#define BSP_UART_TIMEOUT_WAIT_FOREVER     (0xFFFFFFFFU)

/**
 * Below are configurtable, need to recompile after change.
 */

/**
 *  \brief Enable debug print support for UART driver
 */
#define BSP_UART_DEBUG_PRINT_ENABLE (FALSE)

/**
 *  \brief Enable to have parameter validation in the public functions
 */
#define BSP_UART_PARAM_CHECK_ENABLE (TRUE)

/**
 *  \brief Enable buffering support for UART driver
 */
#define BSP_UART_TX_BUFFERING_ENABLE (FALSE)

/**
 *  \brief number of instances supported by the driver
 */
#define BSP_UART_NUM_INSTANCES (4U)

/**
 *  \brief Enable/disable the support for BIOS power management
 */
#define BSP_UART_BIOS_PWRM_ENABLE (FALSE)

/**
 *  \brief  Uart Baud Rate
 */
typedef enum
{
    UART_BAUDRATE_2_4K = 2400U,
    /**< Baudrate 2400    bps   */
    UART_BAUDRATE_4_8K = 4800U,
    /**< Baudrate 4800    bps   */
    UART_BAUDRATE_9_6K = 9600U,
    /**< Baudrate 9600    bps   */
    UART_BAUDRATE_19_2K = 19200U,
    /**< Baudrate 19200   bps   */
    UART_BAUDRATE_38_4K = 38400U,
    /**< Baudrate 38400   bps   */
    UART_BAUDRATE_57_6K = 57600U,
    /**< Baudrate 57600   bps   */
    UART_BAUDRATE_115_2K = 115200U,
    /**< Baudrate 115200  bps   */
    UART_BAUDRATE_3686_4K = 3686400U
                            /**< Baudrate 3686400  bps   */
} Uart_BaudRate;

/**
 *
 *  \brief  Uart Character Length
 *  IMP: The enum values should not be changed since it represents the
 *       actual register configuration values used to configure the Uart in
 *       this SoC by the Uart driver
 */
typedef enum
{
    UART_CHARLEN_5 = 0x0U,
    /**< Character Length 5  bits  */
    UART_CHARLEN_6 = 0x1U,
    /**< Character Length 6  bits  */
    UART_CHARLEN_7 = 0x2U,
    /**< Character Length 7  bits  */
    UART_CHARLEN_8 = 0x3U
                     /**< Character Length 8  bits  */
} Uart_CharLen;

/**
 *
 *  \brief  Receive Uart Flow Control Parameters
 *  IMP: User to select the mode of Uart Software and Hardware flow Control
 *       SW flow control is not supported in this driver implementation
 *
 */

typedef enum
{
    UART_FCPARAM_RXNONE = 0,
    /**< no flow control            */
    UART_FCPARAM_RXXONXOFF_2 = 1,
    /**< xon-xoff 2 flow control    */
    UART_FCPARAM_RXXONXOFF_1 = 2,
    /**< xon-xoff 1 flow control    */
    UART_FCPARAM_RXXONXOFF_12 = 3,
    /**< xon-xoff 12 flow control   */
    UART_FCPARAM_AUTO_RTS = 0x40
                            /**< rts flow control             */
} Uart_FcParamRx;

/**
 *
 *  \brief  Transmit Uart Flow Control Parameters
 *  IMP: User to select the mode of Uart Software and Hardware flow Control
 *       SW flow control is not supported in this driver implementation
 *
 */

typedef enum
{
    UART_FCPARAM_TXNONE = 0,
    /**< no flow control            */
    UART_FCPARAM_TXXONXOFF_2 = 4,
    /**< xon-xoff 2 flow control    */
    UART_FCPARAM_TXXONXOFF_1 = 8,
    /**< xon-xoff 1 flow control    */
    UART_FCPARAM_TXXONXOFF_12 = 0x0C,
    /**< xon-xoff 12 flow control   */
    UART_FCPARAM_AUTO_CTS = 0x80
                            /**< cts flow control             */
} Uart_FcParamTx;

/**
 *
 *  \brief  Uart Flow Control
 *  IMP: The enum values should not be changed since it represents the
 *       actual register configuration values used to configure the Uart in
 *       this SoC by the Uart driver
 */
typedef enum
{
    UART_FCTYPE_NONE = 0,
    /**< No Flow Control        */
    UART_FCTYPE_SW = 1,
    /**< Software Flow Control  */
    UART_FCTYPE_HW = 2
                     /**< Hardware Flow Control  */
} Uart_FcType;

/**
 *
 *  \brief Uart Stop Bits
 *  IMP: The enum values should not be changed since it represents the
 *       actual register configuration values used to configure the Uart in
 *       this SoC by the Uart driver
 */
typedef enum
{
    UART_NUMSTOPBITS_1 = 0U,
    /**< Stop Bits 0    bits    */
    UART_NUMSTOPBITS_1_5 = 0x2U,
    /**< Stop Bits 1.5  bits    */
    UART_NUMSTOPBITS_2 = 0x4U
                         /**< Stop Bits 2    bits    */
} Uart_NumStopBits;

/**
 *
 *  \brief  Uart OpMode
 *  IMP: Enumeration of the different modes of operation available for the
 *       Uart device.
 */
typedef enum
{
    UART_OPMODE_POLLED = 0,
    /**< Polled Mode            */
    UART_OPMODE_INTERRUPT,
    /**< Interrupt Mode         */
    UART_OPMODE_DMAINTERRUPT
    /**< DMA Mode               */
} Uart_OpMode;

/**
 *
 *  \brief  Uart Parity
 *  IMP: The enum values should not be changed since it represents the
 *       actual register configuration values used to configure the Uart in
 *       this SoC by the Uart driver
 */
typedef enum
{
    UART_PARITY_NO = 0,
    /**< Parity Bits NONE   bits        */
    UART_PARITY_ODD = 8,
    /**< Parity Bits ODD    bits        */
    UART_PARITY_EVEN = 0x18,
    /**< Parity Bits EVEN   bits        */
    UART_PARITY_FORCED0 = 0x38,
    /**< Parity Bits FORCED '0' bits    */
    UART_PARITY_FORCED1 = 0x28
                          /**< Parity Bits FORCED '1' bits      */
} Uart_Parity;

/**
 *
 * \brief   Uart Rx Trigger Level Param
 * IMP: The enum values should not be changed since it represents the
 *          actual register configuration values used to configure the Uart in
 *          this SoC by the Uart driver
 */
typedef enum
{
    UART_RXTRIGLVL_8 = 8,
    /**< Trigger Level 8    */
    UART_RXTRIGLVL_16 = 16,
    /**< Trigger Level 16   */
    UART_RXTRIGLVL_56 = 56,
    /**< Trigger Level 56   */
    UART_RXTRIGLVL_60 = 60
                        /**< Trigger Level 60   */
} Uart_RxTrigLvl;

/**
 *
 * \brief   Uart Tx Trigger Level Param
 * IMP: The enum values should not be changed since it represents the
 *      actual register configuration values used to configure the Uart in
 *      this SoC by the Uart driver
 */
typedef enum
{
    UART_TXTRIGLVL_8 = 8,
    /**< Trigger Level 8    */
    UART_TXTRIGLVL_16 = 16,
    /**< Trigger Level 16   */
    UART_TXTRIGLVL_32 = 32,
    /**< Trigger Level 32   */
    UART_TXTRIGLVL_56 = 56
                        /**< Trigger Level 56   */
} Uart_TxTrigLvl;

/**
 *
 *  \brief  Uart Ioctl commands
 */
typedef enum
{
    IOCTL_UART_SET_BAUD = 128,
    /**< Set baud rate, cmdArg = Uart_BaudRate *                              */
    IOCTL_UART_SET_STOPBITS,
    /**< Set number of stop bits, cmdArg = Uart_NumStopBits *                 */
    IOCTL_UART_SET_DATABITS,
    /**< Set number of Data bits, cmdArg = Uart_CharLen *                     */
    IOCTL_UART_SET_PARITY,
    /**< Set parity type, cmdArg = Uart_Parity *                              */
    IOCTL_UART_SET_FLOWCONTROL,
    /**< Set flowcontrol, cmdArg = Uart_FlowControl *                         */
    IOCTL_UART_SET_TRIGGER_LEVEL,
    /**< Changing Trigger level, cmdArg = Uart_RxTrigLvl *                    */
    IOCTL_UART_RESET_RX_FIFO,
    /**< Resets the Uart HW RX FIFO, cmdArg = NONE                            */
    IOCTL_UART_RESET_TX_FIFO,
    /**< Resets the Uart HW TX FIFO, cmdArg = NONE                            */
    IOCTL_UART_CANCEL_CURRENT_IO,
    /**< Cancel the current IO in TX or RX channel, cmdArg = NONE             */
    IOCTL_UART_GET_STATS,
    /**< Getting the Uart stats for DDC, cmdArg = Uart_Stats *                */
    IOCTL_UART_CLEAR_STATS,
    /**< Clearing the Stats of DDC, cmdArg = NONE                             */
    IOCTL_UART_FLUSH_ALL_REQUEST,
    /**< Flush all IO requests , cmdArg = NONE                                */
    IOCTL_UART_SET_POLLEDMODETIMEOUT,
    /**< Set Polled Mode timeout, cmdArg = timeout value in ticks             */
    IOCTL_UART_SET_ERROR_CALLBACK,
    /**< Set error callback function, cmdArg =  pointer to callback structure */
    IOCTL_UART_GET_FIFO_STATUS
    /**< Get the Uart FIFO and shift register status. Depending on the handle
     *   this will return either the RX FIFO status or TX FIFO status.
     *   cmdArg = Uart_FifoStats *                                            */
} Uart_IOCTL;

/**
 *
 * \brief  PLL domain to be used by the device
 */
typedef enum
{
    UART_PLLDOMAIN_0 = 0,
    /**< PLL domain 0          */

    UART_PLLDOMAIN_1 = 1,
    /**< PLL domain 1          */

    UART_PLLDOMAIN_NONE = 2
                          /**< Not in any pll domain */
} Uart_pllDomain;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Uart_TrigLvl
 *  \brief Uart TrigLvl Configuration
 */
typedef struct
{
    Int32 rxTrigLvl;
    /**<Refer #Uart_RxTrigLvl for valid values        */
    Int32 txTrigLvl;
    /**<Refer #Uart_TxTrigLvl for valid values        */
} Uart_TrigLvl;

/**
 *  struct Uart_CrossBarEvtParam
 *  \brief Structure to get the user param to enable the cross bar interrupt on
 *  M3 core
 */
typedef struct
{
    Bool  isCrossBarIntEn;
    /**< Cross bar interrupt enable        */
    UInt8 intNumToBeMapped;
    /**< Interrupt number to be maped     */
} Uart_CrossBarEvtParam;

/**
 *  struct Uart_ChanParams
 *  \brief  Uart channel config parameters
 *  IMP: Uart Channel Params passed to Uart_open function
 */
typedef struct
{
    Ptr                   hEdma;
    /**< EDMA handle. */
    Uart_CrossBarEvtParam crossBarEvtParam;
    /**< cross bar event params. */
} Uart_ChanParams;

/**
 *  struct Uart_FlowControl
 *  \brief  Uart Flow Control Configuration
 */
typedef struct
{
    Int32 fcType;
    /**< Flow Control type
     *  Refer #Uart_FcType for valid values */
    Int32 fcParamTx;
    /**< Transmit Flow Control param
     *  Refer #Uart_FcParamTx for valid values */
    Int32 fcParamRx;
    /**< Receive Flow Control param
     *  Refer #Uart_FcParamRx for valid values */
} Uart_FlowControl;

/**
 *  struct Uart_Stats
 *  \brief Uart Statistics Collection Object
 *  IMP: Statistics are collected on a per-device basis for Uart.
 */
typedef struct
{
    UInt32 rxBytes;
    /**< Number bytes received          */
    UInt32 txBytes;
    /**< Number bytes transmitted       */
    UInt32 overrun;
    /**< Number of overrun errors       */
    UInt32 rxTimeout;
    /**< Number of Rx timeouts          */
    UInt32 rxFramingError;
    /**< Number of Rx Framing errors    */
    UInt32 rxBreakError;
    /**< Number of Rx Break Errors      */
    UInt32 rxParityError;
    /**< Number of Rx Parity Errors     */
} Uart_Stats;

/**
 *  struct Uart_FifoStats
 *  \brief Uart FIFO Status
 */
typedef struct
{
    Bool   isFifoEmpty;
    /**< FIFO is empty or not. */
    Bool   isTxShiftRegEmpty;
    /**< Transmit shift register is empty or not. Applicable only for TX
     *   channel handle. */
    UInt32 fifoLevel;
    /**< Number of bytes in FIFO. */
} Uart_FifoStats;

/**
 *  struct Uart_Params
 *  \brief Uart Instance configuration parameters
 *  A pointer to such a structure is used when driver is instantiated
 */
typedef struct
{
    Bool             enableCache;
    /**< Driver will use cache APIs   */
    UInt32           chunkSize;
    /**< Chunksize                    */
    Bool             fifoEnable;
    /**< Fifo mode of Operation       */
    Int32            opMode;
    /**< Driver operational mode
     *  Refer #Uart_OpMode for valid values */
    Bool             loopbackEnabled;
    /**< LoopBack Mode flag           */
    Int32            baudRate;
    /**< Baudrate of Operation
     *  Refer #Uart_BaudRate for valid values */
    Int32            stopBits;
    /**< Stopbits of Operation
     *  Refer #Uart_NumStopBits for valid values */
    Int32            charLen;
    /**< Character Length
     *  Refer #Uart_CharLen for valid values */
    Int32            parity;
    /**< Parity of Operation
     *  Refer #Uart_Parity for valid values */
    Int32            rxThreshold;
    /**< Rx FIFO trigger level
     *  Refer #Uart_RxTrigLvl for valid values */
    Int32            txThreshold;
    /**< Rx FIFO trigger level
     *  Refer #Uart_TxTrigLvl for valid values */
    Uart_FlowControl fc;
    /**< Flow Control                 */
    UInt16           edmaRxTC;
    /**< Edma Rx TC                   */
    UInt16           edmaTxTC;
    /**< Edma Tx TC                   */
    UInt16           hwiNumber;
    /**< Hwi number used for uart isr */
    UInt32           polledModeTimeout;
    /**< Timeout used in polled mode. The timeout is based on BIOS
     *   Timestamp_get32()/Timestamp_get64() tick period.
     *   A value of BSP_UART_TIMEOUT_WAIT_FOREVER could be used to make the
     *   timeout as forever (infinite wait).
     *   Note that the timeout value includes the actual RX/TX time as well. */
    Bool             prcmPwrmEnable;
    /**< PSC control enable disable   */
    Int32            pllDomain;
    /**< Pll domain where the device is configured.
     *   Refer #Uart_pllDomain for valid values         */

    Ptr              prcmHandle;
    /**< prcmHandle                                                           *
     *  This option enables the user to specify the Handle to the PRCM module.
     *
     *  It is required to specify the handle to the prcm module to enable the
     *  UART module in the prcm.
     *
     *  Default value is NULL.
     *
     *  It is important to create the prcm module before  creating the
     *  uart driver instance.                                                 */

    Int prcmDevId;
    /**< prcm device ID               */
} Uart_Params;

/**
 * \brief Global error callback structure
 * This is the global error callback function for the UART driver.
 * This function is called directly called from ISR context in case of
 * error. The first argument passed to this function is the user supplied
 * callback argument, the second argument is the status of the line
 * Since this function is called from an ISR context,care should be taken
 * that this function conforms to ISR coding guidelines.
 */
typedef void (*Uart_GblErrCallback)(UInt32 arg1, UInt32 arg2, UInt32 arg3);

typedef struct
{
    Uart_GblErrCallback gblErrCbkFxn;
    /**< Error callback fxn               */
    Ptr                 gblErrCbkArg;
    /**< Arguments to Error callback fxn               */
} Uart_GblErrCbk;

/**
 *  \brief Default Uart_Params struct
 *
 *  Following values are defaults and application can assign and change
 *  interested parameters.
 *
 *  const struct Uart_Params Uart_PARAMS = {
 *
 *      TRUE,                   enableCache;
 *
 *      BSP_UART_FIFO_SIZE,     chunkSize
 *
 *      TRUE,                   fifoEnable
 *
 *      UART_OPMODE_INTERRUPT,  opMode
 *
 *      FALSE,                  loopbackEnabled
 *
 *      UART_BAUDRATE_115_2K,   baudRate
 *
 *      UART_NUMSTOPBITS_1,     stopBits
 *
 *      UART_CHARLEN_8,         charLen
 *
 *      UART_PARITY_NO,         parity
 *
 *      UART_RXTRIGLVL_8,       rxThreshold
 *
 *      UART_TXTRIGLVL_56,      txThreshold
 *
 *      {                       fc
 *          UART_FCTYPE_NONE,
 *          UART_FCPARAM_TXNONE,
 *          UART_FCPARAM_RXNONE
 *      },
 *
 *      0,                      edmaRxTC
 *
 *      0,                      edmaTxTC
 *
 *      0,                      hwiNumber
 *
 *      0xffffffff,             polledModeTimeout
 *
 *      false,                  prcmPwrmEnable
 *
 *      UART_PLLDOMAIN_0,       pllDomain
 *
 *      NULL,                   prcmHandle
 *
 *      0                       prcmDevId
 *
 *  };
 */
extern const Uart_Params Uart_PARAMS;

/**
 *  \brief Uart IOM_Fxns table
 *
 *  Driver function table to be used by applications.
 */
extern const IOM_Fxns    Uart_IOMFXNS;

/**
 *  \brief    Initializes Uart instances which are statically allocated *
 *  This function needs to ve be called at part of BIOS initialization by
 *  setting initFxn for that particular UDEV instance or by calling this
 *  function as part of user specific initFxn.
 */
void Uart_init(void);

#ifdef __cplusplus
}
#endif

#endif /*BSP_UART_H_ */

/*  @}  */
/**
 * \mainpage  BSP UART Driver
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * BSP UART Driver contains the interfaces, data types and symbolic definitions
 *  that are needed by the application to utilize the services of the UART
 *  device driver.
 *
 * <b>
 * Also refer to top level user guide for detailed features,
 * limitations and usage description.
 * </b>
 *
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */

