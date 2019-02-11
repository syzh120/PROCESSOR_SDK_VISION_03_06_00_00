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
 *  \defgroup BSP_DRV_MCSPI_API MCSPI Driver API
 *
 *  @{
 */

/**
 *  \file bsp_mcspi.h
 *
 *  \brief    Introduction
 *
 *  Purpose and Scope
 *  The purpose of this document is to explain the McSpi driver on the PSP
 *  Framework architecture written in SYS/BIOS
 *
 *
 *  McSpi Controller
 *  Spi is a high-speed synchronous serial input/output port that allows a
 *  serial bit stream of programmed length (one to 16 bits) to be shifted into
 *  and out of the device at a programmed bit-transfer rate. Spi is normally
 *  used for communication between the microcontroller and external peripherals
 *  or another microcontroller. Typical applications include interface to
 *  external I/O or peripheral expansion via devices such as shift
 *  registers, display drivers, and analog-to-digital converters.
 *
 *  SYS/BIOS System
 *  SYS/BIOS is a real time kernel provided by TI to use with its
 *  DSP processors.
 *
 *  Compiler defines to add/remove features
 *  Define to enable edma support.
 *
 *  Define to turn OFF parameter checking.
 *  Use -DPSP_DISABLE_INPUT_PARAMETER_CHECK when building library
 *
 */

#ifndef BSP_MCSPI_H_
#define BSP_MCSPI_H_

#include <xdc/std.h>
#include <ti/sysbios/io/IOM.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief maximum number fo instances supported by this driver. Default value
 *  will be 1. This will be updated depending on the CPU in xs file
 */
#define MCSPI_NUMINSTANCES                (1U)

/** \brief Enable/disbale the support for BIOS power management
 *                 */
#define MCSPI_BIOSPWRM_ENABLE             (FALSE)

/** \brief Local Buffer data allocation for transcieve operation.
 *               */
#define BUFFER_DATA_SIZE                  (32U)

/** \brief configuration variable for enabling or disabling the edma support
 *    */
#define MCSPI_EDMAENABLE                  (TRUE)

/** \brief enable to have parameter validation in the public functions
 *          */
#define MCSPI_PARAM_CHECK_ENABLE          (TRUE)

/** \brief
 * Max SPI driver opens - which means number of s/w channels which can be
 * opened for a single instance of SPI
 */
#define MCSPI_NUM_LOG_CHANS               (1U)

/** \brief
 * This is the edma base address added to the McSPI registers while
 * configuring the EDMA src/dst address
 */
#define MCSPI_EDMA_BASE_ADDR              (0x40000000U)

/** \brief
 * Max SPI driver opens - which means number of physical channels which can
 * be opened for a single instance of SPI.
 * The instance 0 of Spi -> 4 channels available
 * The instance 1 of Spi -> 2 channels available
 * The instance 2 of Spi -> 2 channels available
 * The instance 3 of Spi -> 1 channel  available
 */
#define MCSPI_MAX_CHAN_SUPPORTED          (4U)

/** \brief
 * The reference frequency for McSPI
 */
#define CLOCK_REF_FREQUENCY               (48000000)

/** \brief Since the McSPI support only transmit-receive mode, the FIFO
 *  is shared among transmit and receive i.e each of 32 bytes
 */
/** \brief
 * Receive FIFO lenght
 */
#define MCSPI_RX_FIFO_LEN                 (32U)

/** \brief
 * Transmit FIFO lenght
 */
#define MCSPI_TX_FIFO_LEN                 (32U)

/* ========================================================================== */
/*                           Enumerations                                     */
/* ========================================================================== */

/** \brief
 *   Enumeration of the different modes of operation available for the
 *   Spi driver.
 */
typedef enum
{
    MCSPI_OPMODE_POLLED = 0,
    /**< Polled Mode            */
    MCSPI_OPMODE_INTERRUPT,
    /**< Interrupt Mode         */
    MCSPI_OPMODE_DMAINTERRUPT
    /**< DMA Mode               */
} Mcspi_OpMode;

/** \brief  Enumeration of Master mode and slave mode of operation
 *   only one channel would be allowed to be opened in slave mode
 *   however more that one (till the max number of channel supported
 *   by driver(configurable) channel can be opened in master mode. In master
 *   mode four physical channels can be configured.
 */
typedef enum
{
    MCSPI_COMMMODE_MASTER = 0,
    /**< Master Mode               */
    MCSPI_COMMMODE_SLAVE
    /**< Slave Mode               */
} Mcspi_CommMode;

/** \brief MCSPI pin Opmode. This macro specifies the number of pins that will
 * be
 * be used by the McSpi device. This mode is used only in single channel
 * master mode
 */
typedef enum
{
    MCSPI_PINOPMODE_4PIN = 0x1,
    /**< SPI master 4 pin mode                                              */

    MCSPI_PINOPMODE_3PIN = 0x3
                           /**< SPI master 3 pin mode uses SPISCS
                            *                                  */
} Mcspi_PinOpMode;

/** \brief MCSPI serial clock mode. This macro specifies the 4 sub-modes of the
 * SPI format transfer that depends on the polarity (POL) and the phase
 * (PHA) of the SPI serial clock (SPICLK) by the McSpi device.
 */
typedef enum
{
    MCSPI_MODE0,
    /**< SPICLK active high and sampling occurs on the rising edge          */

    MCSPI_MODE1,
    /**< SPICLK active high and sampling occurs on the falling edge         */

    MCSPI_MODE2,
    /**< SPICLK active low and sampling occurs on the falling edge          */

    MCSPI_MODE3
    /**< SPICLK active low and sampling occurs on the falling edge          */
} Mcspi_ClkMode;

/** \brief This field defines the number of interface clock cycles between CS
 * toggling and first or last edge of SPI clock.
 */
typedef enum
{
    MCSPI_CLK_CYCLE0,
    /**< CLK cycle 0               */
    MCSPI_CLK_CYCLE1,
    /**< CLK cycle 1               */
    MCSPI_CLK_CYCLE2,
    /**< CLK cycle 2               */
    MCSPI_CLK_CYCLE3
    /**< CLK cycle 3               */
} Mcspi_ChipSelTimectrl;

/** \brief PLL domain to be used by the device
 *                                  */
typedef enum
{
    PLLDOMAIN_0 = 0,
    /**< PLL domain 0            */
    PLLDOMAIN_1 = 1,
    /**< PLL domain 1            */
    PLLDOMAIN_NONE = 2
                     /**< Not in any pll domain   */
} pllDomains;

/** \brief McSPI Word Length to be used by the device
 *                                  */

typedef enum
{
    MCSPI_LEN_4BIT = 0x04,
    /**< Set to Length 4               */
    MCSPI_LEN_8BIT = 0x08,
    /**< Set to Length 8               */
    MCSPI_LEN_16BIT = 0x10,
    /**< Set to Length 16               */
    MCSPI_LEN_24BIT = 0x18,
    /**< Set to Length 24               */
    MCSPI_LEN_32BIT = 0x20
                      /**< Set to Length 32               */
} Mcspi_WordLen;

/** \brief This configuration is used to have delay for the first spi word
 * transfer
 * to give time for system to complete parallel processes. This option is
 * meaningful in master mode and single channel mode.
 */
typedef enum
{
    MCSPI_NO_DELAY = 0x00,
    /**< Have No delay               */
    MCSPI_CLK_DELAY_4 = 0x01,
    /**< Delay of wordlength 4               */
    MCSPI_CLK_DELAY_8 = 0x02,
    /**< Delay of wordlength 8               */
    MCSPI_CLK_DELAY_16 = 0x03,
    /**< Delay of wordlength 16               */
    MCSPI_CLK_DELAY_32 = 0x04
                         /**< Delay of wordlength 32               */
} Mcspi_InitDelay;

/** \brief The McSPI transmit receive mode(TRM), this holds good for both master
 * as
 * well as slave mode of operation. The tx only and the rx only mode is not
 * supported.
 */
typedef enum
{
    MCSPI_BOTH_RXTX = 0x0
                      /**< Full duplex
                       */
} Mcspi_DataTransferMode;

/** \brief Chip Selects to be used by the device
 *                                  */

typedef enum
{
    MCSPI_SPIEN_0,
    /**< chip select 0               */
    MCSPI_SPIEN_1,
    /**< chip select 1               */
    MCSPI_SPIEN_2,
    /**< chip select 2               */
    MCSPI_SPIEN_3
    /**< chip select 3               */
} Mcspi_SpienSlv;

/** \brief To configure the Dat0/Dat1 as the IN(Rx) or as OUT(Tx)
 *                */
typedef enum
{
    MCSPI_IN,
    /**< Data line Direction as IN               */
    MCSPI_OUT
    /**< Data line Direction as OUTPUT               */
} Mcspi_DatalineDirection;

/** \brief This enum is used only in the master mode
 *                             */
typedef enum
{
    MCSPI_SINGLE_CHANNEL,
    /**< Use 1 channel               */
    MCSPI_MULTI_CHANNEL
    /**< Use multi channel               */
} Mcspi_ChannelMode;

/**
 *  \brief  Mcspi Ioctl commands
 */
typedef enum
{
    IOCTL_MCSPI_CANCEL_PENDING_IO = 128,
    /**< Ioctl to cancel the current pending IO packet                     */

    IOCTL_MCSPI_SET_SPIEN_POLARITY,
    /**< Ioctl to set the chip select polarity                             */

    IOCTL_MCSPI_SET_POLLEDMODETIMEOUT,
    /**< Ioctl to set the polled mode timeout                              */

    IOCTL_MCSPI_SET_TRIGGER_LVL
    /**< Ioctl to set the trigger level for FIFO                           */
} Mcspi_ioctlCmd;

/** \brief Structure to set the rx/tx trigger level using the IOCTL
 *              */
typedef struct
{
    UInt16 rxTriggerLvl;
    /**< set receive trigger level     */
    UInt16 txTriggerLvl;
    /**< set transmit trigger level     */
} Mcspi_FifoTrigLvl;

/** \brief Structure to initialize the SPI transfer format register.
 *             */
typedef struct
{
    Int32  charLength;
    /**< Mcspi_WordLen - Defines word length of the data format,
     * Legal values are b/w 4-32
     */

    Bool   multiWordAccessEnable;
    /**< This option can only be used when a channel is enabled using a
     * FIFO. It allows the system to perform multiple SPI word access for
     * a single 32-bit OCP word access. This is possible for WL < 16.
     * TRUE  - Multiple word access enabled with FIFO.
     * FLASE - Multiple word access disabled.
     */

    Bool   spiChipSelectEnablePol;
    /**< Sets the polarity of the SPIEN signal,
     * TRUE  - POLARITY HIGH
     * FALSE - POLARITY LOW
     */

    Int32  clockMode;
    /**< Mcspi_ClkMode -
     * The clock mode selection, depending on the polarity and the phase of
     * the clock
     */

    UInt32 clockRatioExtension;
    /**< This option is used to concatenate with MCSPI_CHCONF[CLKD] register
     * for clock ratio only when granularity is one clock cycle
     * (MCSPI_CHCONF[CLKG] set to 1). Then the max value reached is
     * 4096 clock divider ratio
     */

    Int32  spiWordInitDelay;
    /**< Mcspi_InitDelay -
     * This configuration is used to hav the delay for the first spi word
     * transfer to give time for system to complete parallel processes.
     * This option is meaningful in master mode and single channel mode -
     * Only 00 to 0x04 is valid.
     */

    Int32  trasmitReceiveMode;
    /**< Mcspi_DataTransferMode -
     * The McSPI transmit receive mode(TRM), this holds good for both
     * master as well as receive mode of operation
     */

    Bool   granularityEnable;
    /**<  TRUE  - Enable
     *  FALSE - Disable
     */

    UInt32 busFreq;
    /**< This is the bus frequency for this data format and maintained by
     * the driver and is opaque to the user. This value must not be
     * touched by the application!!                                       */

    Bool   spienHighPolarity;
    /**< Chip Select Polarity. Either active high/Low. Default it is
     *   set to Active Low = FALSE                                         */

    Int32  slaveModeChipSelect;
    /**< Mcspi_SpienSlv -
     * This is used in the slave mode (channel 0 only), to select the
     * proper master device
     */

    Int32  spiDat1Dir;
    /**< Mcspi_DatalineDirection -
     * To configure the Dat0/Dat1 as the IN(Rx) or as OUT(Tx)
     */
    Int32  spiDat0Dir;
    /**< Mcspi_DatalineDirection -
     * To configure the Dat0/Dat1 as the IN(Rx) or as OUT(Tx)
     */
} Mcspi_ConfigChfmt;

/** \brief SPI Hardware Configuartion Structure
 *                                  */
typedef struct
{
    Int32             masterOrSlave;
    /**< Mcspi_CommMode
     * 0 - Master Mode,
     * 1 - Slave Mode
     */

    Int32             singleOrMultiChEnable;
    /**< Mcspi_ChannelMode
     * Only used in the Master mode
     */

    Int32             pinOpModes;
    /**< Mcspi_PinOpMode
     * Only used in the single channel
     * master mode. Only 4 - pin mode is being used.
     */

    UInt16            fifoRxTrigLvl;
    /**< This can be used to configure MCSPIXFERLEVEL[AFL] - buffer almost
     * full register
     */

    UInt16            fifoTxTrigLvl;
    /**< This can be used to configure MCSPIXFERLEVEL[AEL] - buffer almost
     * empty register
     */

    Mcspi_ConfigChfmt configChfmt[MCSPI_MAX_CHAN_SUPPORTED];
    /**< Data Format Configuration values                                   */
} HWConfigData;

/** \brief  Data packet element structure passed to submit function
 *
 *  Structure for the spi specific buffer address to be passed to the
 *  Stream.
 */
typedef struct
{
    UInt8 *outBuffer;
    /**< Data buffer - During transceieve operation this buffer data is
     *                 transmitted                                        */
    UInt8 *inBuffer;
    /**< Data buffer - During transceive operation read data is stored
     *                 in this buffer                                     */
    UInt32 bufLen;
    /**< Length of the buffer                                               */

    UInt32 flags;
    /**< Flags  -     To indicate the Read / Write modes of operation       */

    Ptr    param;
    /**< Extra parameter                                                    */
} Mcspi_DataParam;

/** \brief
 * McSPI statistics Collection Object
 *
 * Statistics are collected on a per-controller basis for SPI. Hence, an
 * object of this type is found embedded in the instance structure.
 */
typedef struct
{
    UInt32 rxBytes;
    /**< Number of bytes received          */
    UInt32 txBytes;
    /**< Number of bytes transmitted       */
    UInt32 pendingPacket;
    /**< Number of pending packets         */
    UInt32 rxOverrunError;
    /**< Number of overrun errors          */
    UInt32 timeoutError;
    /**< Number of timeouts                */
    UInt32 txUnderFlowError;
    /**< tx underflow error                */
    UInt32 rxOverFlowError;
    /**< rx overflow error                 */
} Stats;

/** \brief Structure to get the user param to enable the cross bar interrupt on
 * M3
 *  core
 */
#if defined (TI814x_M3) || defined (__TI_ARM_V7M4__)
typedef struct
{
    Bool  isCrossBarIntEn;
    /**<Cross bar interrupt enable    */
    Uint8 intNumToBeMapped;
    /**< Interrupt number to be maped     */
} Mcspi_CrossBarEvtParam;
#endif

typedef struct
{
    Ptr                    hEdma;
    /**< Edma handle
     */

    Int32                  chipSelTimeControl;
    /**< Mcspi_ChipSelTimectrl
     * Number of interface clock cycles introduced between CS toggling and
     * first or last edge of SPI clock*/

    Bool                   fifoEnable;
    /**< To have the fifo or not in DMA mode. TRUE  - FIFO is enabled
     *                                      FALSE - FIFO is disabled
     */

    Bool                   spiChipSelectHold;
    /**< Sets the FORCE bit in the Conf register, if the slave requires to
     * hold the SPIEN during its transaction the user can select this as a
     * channel parameter
     * TRUE  -  SPIEN will be held its active state
     * FALSE -  SPIEN will not be held its active state after each and every spi
     * word transaction
     */

    UInt32                 chanNum;
    /**< To indicate which physical channel needs to be opened              */

#if defined (TI814x_M3) || defined (__TI_ARM_V7M4__)
    Mcspi_CrossBarEvtParam crossBarEvtParam; /**< cross bar event params     */
#endif
    Bool                    useAppSpecifiedDmaEvtNumbers;
    /**< Use Dma event Numbers passed from application.
     *   TRUE   to use the dma event numbers specified in rxDmaEventNumber and
     *          rxDmaEventNumber variables.
     *   FALSE  to use the default dma event numbers defined inside driver.
     */
    UInt32                  rxDmaEventNumber;
    /**< rx dma event number     */
    UInt32                  txDmaEventNumber;
    /**< tx dma event number     */
} Mcspi_ChanParams;

/** \brief The structure which holds the rx/tx event numbers. The event number
 * 'FFFF' is invalid.
 */
typedef struct
{
    UInt32 rxDmaEventNumber;
    /**< rx dma event number     */
    UInt32 txDmaEventNumber;
    /**< tx dma event number     */
} DmaEvtList;

/** \brief Structure for holding the PWRM related info
 *                          */
typedef struct
{
    Int32  pllDomain;
    /**< pllDomains
     * \brief Pll domain to be used for the device
     */

    Bool   ioSuspend;
    /**< \brief whether the driver in IO suspend mode (PWRM change is in
     *progress) */

    UInt32 constraintMask;
    /**< \brief Constraint mask (for information only)
     *                            */

    UInt32 dependencyCount;
    /**< \brief Current dependency count when the driver is going for sleep or
     * deepsleep
     *                                                                 */
} pwrmInfo;

/**
 *  \brief Mcspi Instance configuration parameters
 *
 *  A pointer to such a structure is used when driver is instantiated
 */
typedef struct
{
    Int          instNum;
    /**< Instance Id  */
    Int32        opMode;
    /**< Mcspi_OpMode - Driver operational mode      */
    UInt16       hwiNumber;
    /**< Hwi number used for Mcspi isr*/
    Bool         enableCache;
    /**< Cache enable/disable flag    */
    Int32        edma3EventQueue;
    /**< Driver will use cache APIs   */
    HWConfigData spiHWCfgData;
    /**< SPI Hardware Configuartion Structure */
    Bool         prcmPwrmEnable;
    /**< PRCM control enable disable  */
    Int32        pllDomain;
    /**< pllDomains - Pll domain where the device is configured     */
    UInt32       polledModeTimeout;
    /**< Timeout used in polled mode  */
    Int          prcmDevId;
    /**< prcm device ID               */
    Bool         enableErrIntr;
    /**< Enable/Disable ErrorInterrupt*/
} Mcspi_Params;

/**
 *  \brief Default Mcspi_Params struct
 *
 *  Following values are defaults and application can assign and change
 *  interested parameters.
 *
 *  const struct Mcspi_Params Mcspi_PARAMS = {
 *
 *  0,                          instNum
 *  MCSPI_OPMODE_POLLED,        opMode
 *  16,                         hwiNumber
 *  FALSE,                      enableCache
 *  0,                          edma3EventQueue
 *    {
 *        CommMode_MASTER,          masterOrSlave
 *        SINGLE_CHANNEL,           singleOrMultiChEnable
 *        PinOpMode_4PIN,           pinOpModes
 *        1,                        fifoRxTrigLvl
 *        1,                        fifoTxTrigLvl
 *        [
 *            {
 *                LEN_8BIT,         charLength
 *                FALSE,            multiWordAccessEnable
 *                FALSE,            spiChipSelectEnablePol
 *                mode0,            clockMode
 *                0,                clockRatioExtension
 *                NO_DELAY,         spiWordInitDelay
 *                BOTH_RXTX,        trasmitReceiveMode
 *                FALSE,            granularityEnable
 *                3000000,          busFreq
 *                FALSE,            spienHighPolarity
 *                SPIEN_0,          slaveModeChipSelect
 *                IN,               spiDat0Dir
 *                OUT               spiDat1Dir
 *            },
 *            {
 *                LEN_8BIT,         charLength
 *                FALSE,            multiWordAccessEnable
 *                TRUE,             spiChipSelectEnablePol
 *                mode0,            clockMode
 *                0,                clockRatioExtension
 *                NO_DELAY,         spiWordInitDelay
 *                BOTH_RXTX,        trasmitReceiveMode
 *                FALSE,            granularityEnable
 *                3000000,          busFreq
 *                FALSE,            spienHighPolarity
 *                SPIEN_0,          slaveModeChipSelect
 *                IN,               spiDat0Dir
 *                OUT               spiDat1Dir
 *            },
 *            {
 *                LEN_8BIT,         charLength
 *                FALSE,            multiWordAccessEnable
 *                TRUE,             spiChipSelectEnablePol
 *                mode0,            clockMode
 *                0,                clockRatioExtension
 *                NO_DELAY,         spiWordInitDelay
 *                BOTH_RXTX,        trasmitReceiveMode
 *                FALSE,            granularityEnable
 *                3000000,          busFreq
 *                FALSE,            spienHighPolarity
 *                SPIEN_0,          slaveModeChipSelect
 *                IN,               spiDat0Dir
 *                OUT               spiDat1Dir
 *            },
 *            {
 *                LEN_8BIT,         charLength
 *                FALSE,            multiWordAccessEnable
 *                TRUE,             spiChipSelectEnablePol
 *                mode0,            clockMode
 *                0,                clockRatioExtension
 *                NO_DELAY,         spiWordInitDelay
 *                BOTH_RXTX,        trasmitReceiveMode
 *                FALSE,            granularityEnable
 *                3000000,          busFreq
 *                FALSE,            spienHighPolarity
 *                SPIEN_0,          slaveModeChipSelect
 *                IN,               spiDat0Dir
 *                OUT               spiDat1Dir
 *            }
 *        ],
 *     }
 *     FALSE,                  prcmPwrmEnable
 *     PLLDOMAIN_0,            pllDomain
 *     BIOS_WAIT_FOREVER,      polledModeTimeout
 *
 *  };
 */

extern const Mcspi_Params Mcspi_PARAMS;

/**
 *  \brief Mcspi IOM_Fxns table
 *
 *  Driver function table to be used by applications.
 */
extern const IOM_Fxns     Mcspi_IOMFXNS;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief    Initializes McSPI instances which are statically allocated
 *
 *  This function needs to ve be called at part of BIOS initialization by
 *  setting initFxn for that particular UDEV instance or by calling this
 *  function as part of user specific initFxn.
 */
Void Mcspi_init(Void);

/**
 *  \brief    Mcspi_ChanParams structure init function.
 *
 *  \param    chanParams   [IN] Pointer to #Mcspi_ChanParams structure.
 *
 */
static inline Void Mcspi_ChanParams_init(Mcspi_ChanParams *chanParams);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
static inline Void Mcspi_ChanParams_init(Mcspi_ChanParams *chanParams)
{
    if(chanParams != NULL)
    {
        chanParams->hEdma = NULL;
        chanParams->chipSelTimeControl = 0U;
        chanParams->fifoEnable = FALSE;
        chanParams->spiChipSelectHold = FALSE;
        chanParams->chanNum = 0U;
        chanParams->useAppSpecifiedDmaEvtNumbers = FALSE;
        chanParams->rxDmaEventNumber = 0U;
        chanParams->txDmaEventNumber = 0U;
    }
}

#ifdef __cplusplus
}
#endif

#endif /*BSP_MCSPI_H_ */

/*  @}  */
/* @} */
/**
 * \mainpage  Multichannel Serial Peripheral Interface Library
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * Multichannel Serial Peripheral Interface Library(McSPI Lib) contains
 * APIs to configure McSpi Controller. Spi is a high-speed synchronous
 * serial input/output port that allows a serial bit stream of programmed
 * length (one to 16 bits) to be shifted into and out of the device at a
 * programmed bit-transfer rate. Spi is normally used for communication
 * between the micro-controller and external peripherals or another
 * micro-controller. Typical applications include interface to
 * external I/O or peripheral expansion via devices such as shift
 * registers, display drivers, and analog-to-digital converters.
 *
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */
