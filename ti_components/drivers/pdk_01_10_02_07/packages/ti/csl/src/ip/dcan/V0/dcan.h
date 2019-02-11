/*
 *  Copyright (C) 2013-2016 Texas Instruments Incorporated - www.ti.com/
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
 *
 */
/**
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_DCAN DCAN
 *
 *  @{
 */
/**
 * \file       dcan.h
 *
 * \brief      This file contains the function prototypes for the device
 *             abstraction layer of DCAN. It also contains necessary
 *             structure, enum and macro definitions
 *             DCAN : Controller Area Network Controller module
 *
 */
#ifndef DCAN_H_
#define DCAN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_dcan.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  \brief Maximum message length in bytes that can be transmitted or received
 *  in a single message object
 */
#define DCAN_MAX_MSG_LENGTH              (8U)

/**
 *  \brief Maximum message objects that can be stored in Message RAM
 */
#define DCAN_MAX_MSG_OBJECTS             (64U)

/**
 *  \brief Invalid Message Object
 */
#define DCAN_INVALID_MSG_OBJECT          (0U)

/** \brief Message Object Size*/
#define DCAN_MSG_OBJ_SIZE                (0x20U)

/**
 *  \brief Mask used to deduce whether single bit error is detected or not
 */
#define DCAN_ECC_SB_ERR_STS          (DCAN_ECC_CSR_SE_FLAG_MASK)

/**
 *  \brief Mask used to deduce whether double bit error is detected or not
 */
#define DCAN_ECC_DB_ERR_STS          (DCAN_ECC_CSR_DE_FLAG_MASK)

/** \brief Error Status is updated*/
#define DCAN_ERR_STS_UPDATED           (0x8000U)

/** \brief Mask value for Extended Message Identifier, As [28:0] are valid bits
    for Extended Message Identifier */
#define DCAN_MSGID_MASK_XTD          (0x1FFFFFFFU)

/** \brief Mask value for Standard Message Identifier, As [28:18] are valid bits
    for Standard Message Identifier */
#define DCAN_MSGID_MASK_STD          (0x1FFC0000U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to set the direction of message object
 */
typedef enum dcanDirection
{
    DCAN_DIR_RX = DCAN_IFARB_DIR_RECEIVE,
    /**< Direction of message object is receive */
    DCAN_DIR_TX = DCAN_IFARB_DIR_TRANSMIT
                  /**< Direction of message object is transmit */
} dcanDirection_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN error and status
 *            values
 */
typedef enum dcanErrStsMask
{
    DCAN_ES_MASK_NO_ERR = DCAN_ES_LEC_EN_1_0X0,
    /**< LEC error code : No error */
    DCAN_ES_MASK_STUFF_ERR = DCAN_ES_LEC_EN_2_0X1,
    /**< LEC error code : Stuff error */
    DCAN_ES_MASK_FORM_ERR = DCAN_ES_LEC_EN_3_0X2,
    /**< LEC error code : Form error */
    DCAN_ES_MASK_ACK_ERR = DCAN_ES_LEC_EN_4_0X3,
    /**< LEC error code : Ack error */
    DCAN_ES_MASK_BIT1_ERR = DCAN_ES_LEC_EN_5_0X4,
    /**< LEC error code : Bit1 error */
    DCAN_ES_MASK_BIT0_ERR = DCAN_ES_LEC_EN_6_0X5,
    /**< LEC error code : Bit0 error */
    DCAN_ES_MASK_CRC_ERR = DCAN_ES_LEC_EN_7_0X6,
    /**< LEC error code : CRC error */
    DCAN_ES_MASK_NO_EVENT = DCAN_ES_LEC_EN_8_0X7,
    /**< LEC error code : No event detected */
    DCAN_ES_MASK_TX_OK = DCAN_ES_TXOK_MASK,
    /**< DCAN transmitted a message successfully */
    DCAN_ES_MASK_RX_OK = DCAN_ES_RXOK_MASK,
    /**< DCAN received a message successfully */
    DCAN_ES_MASK_ERR_PASSIVE = DCAN_ES_EPASS_MASK,
    /**< DCAN is in Error passive state */
    DCAN_ES_MASK_ERR_WARNING = DCAN_ES_EWARN_MASK,
    /**< DCAN has crossed the error warning limit */
    DCAN_ES_MASK_BUS_OFF = DCAN_ES_BOFF_MASK,
    /**< DCAN is in bus-off state */
    DCAN_ES_MASK_PARITY_ERR = DCAN_ES_PER_MASK,
    /**< Parity error is detected */
    DCAN_ES_MASK_WAKEUP_PENDING = DCAN_ES_WAKEUP_PND_MASK,
    /**< Wakeup pending */
    DCAN_ES_MASK_POWER_DOWN = DCAN_ES_PDA_MASK
                              /**< DCAN is in local power down mode */
} dcanErrStsMask_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN error counter
 *            register values
 */
typedef enum dcanErrCntrMask
{
    DCAN_EC_MASK_TX_ERR = DCAN_ERRC_TEC_MASK,
    /**< DCAN transmit error counter */
    DCAN_EC_MASK_RX_ERR = DCAN_ERRC_REC_MASK,
    /**< DCAN receive error counter */
    DCAN_EC_MASK_RX_ERR_PASSIVE = DCAN_ERRC_RP_MASK
                                  /**< DCAN receive error passive */
} dcanErrCntrMask_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN test modes
 */
typedef enum dcanTestMode
{
    DCAN_TEST_MODE_NONE,
    /**< All DCAN test mode is disabled. Use for normal operation. */
    DCAN_TEST_MODE_SILENT,
    /**< DCAN Silent test mode */
    DCAN_TEST_MODE_LPBACK,
    /**< DCAN loopback test mode */
    DCAN_TEST_MODE_LPBACK_SILENT,
    /**< DCAN loopback with silent test mode */
    DCAN_TEST_MODE_EXT_LPBACK
    /**< DCAN external loopback test mode */
} dcanTestMode_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN interrupt lines
 */
typedef enum dcanIntrLineNum
{
    DCAN_INTR_LINE_NUM_0,
    /**< DCAN interrupt line 0 */
    DCAN_INTR_LINE_NUM_1
    /**< DCAN interrupt line 1 */
} dcanIntrLineNum_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN interface
 *            registers
 */
typedef enum dcanIfRegNum
{
    DCAN_IF_REG_NUM_1 = 1U,
    /**< DCAN interface register number 1 used for both read and write */
    DCAN_IF_REG_NUM_2 = 2U,
    /**< DCAN interface register number 2 used for both read and write */
    DCAN_IF_REG_NUM_3 = 3U
                        /**< DCAN interface register number 3 used only for read
                         */
} dcanIfRegNum_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN Identifier Type
 */
typedef enum dcanXidType
{
    DCAN_XID_11_BIT,
    /**< 11bit DCAN Identifier */
    DCAN_XID_29_BIT
    /**< 29bit DCAN Identifier */
} dcanXidType_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN mode of
 *            operation
 */
typedef enum dcanMode
{
    DCAN_MODE_NORMAL,
    /**< DCAN normal mode */
    DCAN_MODE_INIT
    /**< DCAN initialization mode */
} dcanMode_t;

/**
 *  \brief    Enumerates the values used to represent the DCAN parity error
 *            status
 */
typedef enum dcanParityErrSts
{
    DCAN_PARITY_ERR_STS_MSG_NUM = DCAN_PERR_MESSAGE_NUMBER_MASK,
    /**< Mask used to deduce the message number which caused the Parity error */
    DCAN_PARITY_ERR_STS_WORD_NUM = DCAN_PERR_WORD_NUMBER_MASK
                                   /**< Mask used to deduce the word number
                                    *   which caused the Parity error */
} dcanParityErrSts_t;

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
/**
 *  \brief    Enumerates the values used to represent the DCAN ECC Diagnostic
 *            status information
 */
typedef enum dcanEccDiagErrStsMask
{
    DCAN_ECC_DIAG_SB_ERR_STS = DCAN_ECC_DIAG_STATUS_SE_FLAG_MASK,
    /**< Mask used to deduce whether single bit error diagnostic is detected or
     *not */
    DCAN_ECC_DIAG_DB_ERR_STS = DCAN_ECC_DIAG_STATUS_DE_FLAG_MASK
                               /**< Mask used to deduce whether double bit error
                                *   diagnostic is detected or not */
} dcanEccDiagErrStsMask_t;
#endif

/**
 *  \brief    Enumerates the values used to represent the DCAN Frame Type
 */
typedef enum dcanFrameType
{
    DCAN_DATA_FRAME,
    /**< Data Frame */
    DCAN_REMOTE_FRAME
    /**< Remote Frame */
} dcanFrameType_t;

/* ========================================================================== */
/*                          Structure Declarations                            */
/* ========================================================================== */

/** \brief Structure holding bit time parameters for DCAN
 */
typedef struct dcanBitTimeParams
{
    uint32_t baudRatePrescaler;
    /**< Baud rate prescaler
     *   Value by which the CAN_CLK frequency is divided for generating the bit
     *   time quanta. The bit time is built up from a multiple of this quanta
     *   Valid programmed values are 0 to 63. The actual BRP value interpreted
     *   for the bit timing will be programmed as BRP value + 1
     */
    uint32_t syncJumpWidth;
    /**< Synchronization Jump Width
     *   Valid programmed values are 0 to 3. The actual SJW value interpreted
     *   for the synchronization will be as programmed SJW value + 1
     */
    uint32_t timeSegment1;
    /**< Time segment before the sample point
     *   Valid programmed values are 1 to 15. The actual TSeg1 value interpreted
     *   for the bit timing will be programmed as TSeg1 value + 1
     */
    uint32_t timeSegment2;
    /**< Time segment after the sample point
     *   Valid programmed values are 0 to 7. The actual TSeg2 value which is
     *   interpreted for the bit timing will be the programmed as
     *   TSeg2 value + 1
     */
    uint32_t baudRatePrescalerExt;
    /**< Baud rate prescaler extension
     *   Valid programmed values are 0 to 15. By programming BRPE the baud rate
     *   prescaler can be extended to values up to 1024
     */
} dcanBitTimeParams_t;

/** \brief Structure holding configuration parameters of DCAN module
 */
typedef struct dcanCfgParams
{
    uint32_t parityEnable;
    /**< Parity /ECC Enable or Disable for Tda2xx/Tda3xx
     *   Valid values: TRUE or FALSE
     */
    uint32_t eccModeEnable;
    /**< Enable/disable SECDED single bit error correction
     *   Valid values: TRUE or FALSE. This is used only for TDA3xx platform
     */
    uint32_t eccDiagModeEnable;
    /**< Enable/disable SECDED Diagnostic Mode
     *   Valid values: TRUE or FALSE. This is used only for TDA3xx platform
     */
    uint32_t sbeEventEnable;
    /**< Enable/disable SECDED single bit error event
     *   Valid values: TRUE or FALSE. This is used only for TDA3xx platform
     */
    uint32_t intrLine0Enable;
    /**< Interrupt line 0 enable/disable. Valid values: TRUE or FALSE */
    uint32_t intrLine1Enable;
    /**< Interrupt line 1 enable/disable. Valid values: TRUE or FALSE */
    uint32_t stsChangeIntrEnable;
    /**< Status Change Interrupt enable/disable. Valid values: TRUE or FALSE */
    uint32_t errIntrEnable;
    /**< Error Interrupt enable/disable. Valid values: TRUE or FALSE */
    uint32_t if1DmaEnable;
    /**< IF1 DMA enable/disable. Valid values: TRUE or FALSE */
    uint32_t if2DmaEnable;
    /**< IF2 DMA enable/disable. Valid values: TRUE or FALSE */
    uint32_t if3DmaEnable;
    /**< IF3 DMA enable/disable. Valid values: TRUE or FALSE */
    uint32_t autoRetransmitDisable;
    /**< Disable Automatic retransmission of failure messages :
     *   Valid values: TRUE or FALSE
     */
    uint32_t autoBusOnEnable;
    /**< Auto Bus on enable/disable. Valid values: TRUE or FALSE */
    uint32_t autoBusOnTimerVal;
    /**< Auto Bus-On Timer Value in OCP clocks
     *   Valid only when autoBusOnEnable is set
     */
    uint32_t testModeEnable;
    /**< Test Mode enable/disable. Valid values: TRUE or FALSE */
    uint32_t testMode;
    /**< Test mode. For valid values refer enum #dcanTestMode_t
     *   Valid only when testModeEnable is set
     */
    uint32_t ramAccessEnable;
    /**< Direct access to the RAM is enabled/disabled while in test mode
     *   Valid only when testModeEnable is set - Valid values: TRUE or FALSE
     */
} dcanCfgParams_t;

/** \brief Structure holding common configuration parameters of tx /rx of DCAN
 *         module
 */
typedef struct dcanMsgObjCfgParams
{
    uint32_t direction;
    /**< Message object direction.For valid values refer
     *   enum #dcanDirection_t
     */
    uint32_t xIdFlagMask;
    /**< Extended Identifier IDE bit Mask: Valid values: TRUE or FALSE
     *   Valid only for RX
     */
    uint32_t dirMask;
    /**< Message Direction Mask: Valid values: TRUE or FALSE
     *   Valid only for RX
     */
    uint32_t msgIdentifierMask;
    /**< Identifier Mask - [28:0] are valid bits.
     *   [28:18]: Standard Identifier Mask, [17:0]: Extended Identifier Mask
     *   Valid only for RX
     */
    uint32_t xIdFlag;
    /**< Extended IDE Flag : Standard / Extended Identifier
     *   For valid values refer enum # dcanXidType_t
     */
    uint32_t msgIdentifier;
    /**< Message Identifier - [28:0]  are valid bits
     *   [28:18]: Standard Identifier , [17:0]: Extended Identifier
     */
    uint32_t msgValid;
    /**< Valid or Invalid Message Objects.Valid values: TRUE or FALSE */
    uint32_t uMaskUsed;
    /**< Use mask (Msk[28:0], MXtd, and MDir) for acceptance filtering or not
     *   Valid only for RX
     */
    uint32_t intEnable;
    /**< Interrupt Enable : IntPnd will be triggered or not after the
     *   successful transmission/reception of a frame
     *   Valid values: TRUE or FALSE
     */
    uint32_t remoteEnable;
    /**< At the reception of a remote frame, TxRqst bit is changed
     *   Valid only for TX - Valid values: TRUE or FALSE
     */
    uint32_t fifoEOBFlag;
    /**<  Message object is part of FIFO Buffer or not
     *    Valid values: TRUE or FALSE
     */
} dcanMsgObjCfgParams_t;

/** \brief Structure holding transfer parameters of DCAN module
 */
typedef struct dcanMsgParams
{
    uint32_t dataLength;
    /**<  Message object data length - Valid values: 1 to 8 */
    uint32_t msgLostFlag;
    /**< At the reception of a Message, Message is received or lost
     *   Valid only for RX - Valid values: TRUE or FALSE
     */
    uint32_t rxIdType;
    /**< Extended IDE Type : Standard / Extended Identifier. Valid only for Rx
     *   For valid values refer enum # dcanXidType_t
     */
    uint32_t rxMsgIdentifier;
    /**< Message Identifier - [28:0]  are valid bits. Valid only for Rx
     *   [28:18]: Standard Identifier , [17:0]: Extended Identifier
     */
    uint32_t rxFrameType;
    /**< Received Frame is Data Frame / Remote Frame. Valid only for Rx
     *   For valid values refer enum # dcanFrameType_t
     */
    uint8_t  msgData[DCAN_MAX_MSG_LENGTH];
    /**< Data Value to be transmitted */
} dcanMsgParams_t;

typedef dcanMsgParams_t dcanTxParams_t;
typedef dcanMsgParams_t dcanRxParams_t;

/** \brief Structure holding DCAN ECC Error status.
 */
typedef struct dcanEccErrStatus
{
    uint32_t singleBitErr;
    /**<  DCAN ECC : When one bit Error occured on Message Ram */
    uint32_t doubleBitErr;
    /**<  DCAN ECC : When two bits Error occured on Message Ram */
} dcanEccErrStatus_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief     This API will reset the DCAN module and configure the DCAN TX/RX
 *            IO Control register
 *
 * \param     baseAddr    Base Address of the DCAN module Register
 * \param     timeOut     Timeout value
 *
 * \return    STW_SOK on success else STW_EFAIL when DCAN reset fails
 *
 * \note      This API has to be called before the driver can be used
 */
int32_t DCANReset(uint32_t baseAddr, uint32_t timeOut);

/**
 * \brief     This API will configure the operating mode of DCAN
 *            In Init mode the communication on CAN bus is stopped and the
 *            controller needs to be placed in Init mode for initialization
 *            To start communication on CAN bus please keep the DCAN controller
 *            in Normal mode of operation
 *
 * \param     baseAddr    Base Address of the DCAN module Register
 * \param     mode        DCAN mode to be configured
 *                        For valid values refer enum #dcanMode_t
 *
 * \return    None
 */
void DCANSetMode(uint32_t baseAddr, uint32_t mode);

/**
 * \brief   This API configures bit time parameters for DCAN module
 *
 * \param   baseAddr       Base Address of the DCAN module Register
 * \param   pBitTimePrms   Pointer which holds DCAN bit time parameters
 *
 * \return  None
 */
void DCANSetBitTime(uint32_t baseAddr, const dcanBitTimeParams_t *pBitTimePrms);

/**
 * \brief     This API configures DCAN controller
 *
 * \param     baseAddr     Base Address of the DCAN module Register
 * \param     pDcanCfgPrms Pointer which holds DCAN controller config parameters
 *
 * \return    None
 *
 * \note      The API DCANReset has to be called before this API can
 *            be used
 */
void DCANConfig(uint32_t baseAddr, const dcanCfgParams_t *pDcanCfgPrms);

/**
 * \brief     This API configures DCAN TX/RX message object
 *
 * \param     baseAddr          Base Address of the DCAN module register
 * \param     msgObj            Message object number of CAN node
 *                              Valid values: 1 to 64
 * \param     ifRegNum          DCAN interface register number
 *                              For valid value refer enum #dcanIfRegNum_t
 * \param     pMsgObjCfgPrms    Pointer which holds DCAN message object Config
 *                              parameters of TX/RX
 *
 * \return    STW_SOK on success else STW_EFAIL when IF register busy flag is
 *            set
 */
int32_t DCANConfigMsgObj(uint32_t                     baseAddr,
                         uint32_t                     msgObj,
                         uint32_t                     ifRegNum,
                         const dcanMsgObjCfgParams_t *pMsgObjCfgPrms);

/**
 * \brief     This API transmits a CAN message and writes a CAN message into a
 *            CAN message object
 *
 * \param     baseAddr    Base Address of the DCAN module register
 * \param     msgObj      Message object number of CAN node
 *                        Valid values: 1 to 64
 * \param     ifRegNum    DCAN interface register number
 *                        For valid values refer enum #dcanIfRegNum_t
 * \param     pDcanTxPrms Pointer which holds DCAN transmit parameters
 * \param     timeOut     Timeout value
 *
 * \return    STW_SOK on success else STW_EFAIL when IF register busy flag is
 *            set
 */
int32_t DCANTransmitData(uint32_t              baseAddr,
                         uint32_t              msgObj,
                         uint32_t              ifRegNum,
                         const dcanTxParams_t *pDcanTxPrms,
                         uint32_t              timeOut);

/**
 * \brief     This API gets received CAN message from message RAM
 *
 * \param     baseAddr       Base Address of the DCAN module register
 * \param     msgObj         Message object number of CAN node
 *                           Valid values : 1 to 64
 *
 * \param     ifRegNum       DCAN interface register number
 *                           For valid values refer enum #dcanIfRegNum_t
 * \param     pDcanRxPrms    Pointer which holds DCAN receive parameters
 * \param     timeOut        Timeout value
 *
 * \return    STW_SOK on success else STW_EFAIL when IF register busy flag is
 *            set
 *
 * \note      The API will receive valid data of size dataLength, msgIdType,
 *            Frame Type, msgIdentifier of the received CAN message
 */
int32_t DCANGetData(uint32_t        baseAddr,
                    uint32_t        msgObj,
                    uint32_t        ifRegNum,
                    dcanRxParams_t *pDcanRxPrms,
                    uint32_t        timeOut);

/**
 * \brief     This API returns Tx message object transmission status whether Tx
 *            message object has a pending Tx request or not
 *
 * \param     baseAddr    Base Address of the DCAN module register
 * \param     msgObj      Message object number of CAN node
 *                        Valid values: 1 to 64
 *
 * \return    FALSE when data transmission is successful else TRUE when data
 *            transmission is not successful
 */
uint32_t DCANIsTxMsgPending(uint32_t baseAddr, uint32_t msgObj);

/**
 * \brief     This API returns Rx message object reception status whether Rx
 *            message object has a pending Rx data or not
 *
 * \param     baseAddr    Base Address of the DCAN module register
 * \param     msgObj      Message object number of CAN node
 *                        Valid values: 1 to 64
 *
 * \return     TRUE when new data has arrived else FALSE when new data has not
 *             arrived
 */
uint32_t DCANHasRxMsgArrived(uint32_t baseAddr, uint32_t msgObj);

/**
 * \brief     This API checks for whether msgObj is valid or not
 *
 * \param     baseAddr         Base Address of the DCAN Module Registers.
 * \param     msgObj           Message object number whose message valid status
 *                             is to be returned.
 *
 * \return    TRUE when message object is valid else FALSE when message object
 *            is invalid
 */
uint32_t DCANIsMsgValid(uint32_t baseAddr, uint32_t msgObj);

/**
 * \brief     This API checks for whether DCAN IF Register is busy or not
 *
 * \param     baseAddr       Base Address of the DCAN module register
 * \param     ifRegNum       DCAN interface register number
 *                           For valid values refer enum #dcanIfRegNum_t
 *
 * \return     TRUE when DCAN IF Register is busy else FALSE when DCAN IF
 *             Register is not busy
 */
uint32_t DCANIsIfRegBusy(uint32_t baseAddr, uint32_t ifRegNum);

/**
 * \brief     This API will configure which interrupt line is used to service
 *            interrupts for message objects
 *
 * \param     baseAddr         Base Address of the DCAN module register
 * \param     msgObj           Message object number
 * \param     intrLineNum      Interrupt line number to be configured
 *                             For valid values refer enum #dcanIntrLineNum_t
 *
 * \return    None
 */
void DCANConfigIntrMux(uint32_t baseAddr,
                       uint32_t intrLineNum,
                       uint32_t msgObj);

/**
 * \brief     This API returns interrupt line status of DCAN
 *
 * \param     baseAddr         Base Address of the DCAN module register
 * \param     intrLineNum      DCAN interrupt line number
 *                             For valid values refer enum #dcanIntrLineNum_t
 *
 * \return    message object number with highest pending interrupt or
 *            number which indicates Source of the interrupt
 *            0x0000        : No interrupt is pending
 *            0x0001-0x0040 : Message object Number which caused the interrupt
 *            0x0041-0x7FFF : Unused
 *            0x8000        : DCAN_ES value is not 0x07.
 *            0x8001-0xFFFF : Unused
 */
uint32_t DCANGetIntrStatus(uint32_t baseAddr, uint32_t intrLineNum);

/**
 * \brief     This API returns message object interrupt pending status
 *
 * \param     baseAddr    Base Address of the DCAN module register
 * \param     msgObj      Message object number of CAN node
 *                        Valid values: 1 to 64
 *
 * \return     TRUE when message object has pending interrupt else FALSE when
 *             message object has no pending interrupt
 */
uint32_t DCANIsMsgObjIntrPending(uint32_t baseAddr, uint32_t msgObj);

/**
 * \brief   This API will clear the interrupt pending status of received message
 *          objects after a new message is received
 *
 * \param   baseAddr      Base Address of the DCAN module register
 * \param   msgObj        Message object number of CAN node
 *                        Valid values : 1 to 64
 * \param   ifRegNum      DCAN interface register number
 *                        For valid values refer enum #dcanIfRegNum_t
 * \return  None
 */
void DCANIntrClearStatus(uint32_t baseAddr, uint32_t msgObj, uint32_t ifRegNum);

/**
 * \brief     This API will read the error and status information of DCAN
 *            controller
 *
 * \param     baseAddr         Base Address of the DCAN module register
 *
 * \return    Returns the error and status values.For valid values refer
 *            enum #dcanErrStsMask_t
 *
 * \note      Reading the error and status register will clear/set certain bits
 *            in the error and status register. For more information please
 *            refer the DCAN Technical Reference Manual(TRM). For debug support,
 *            the auto clear functionality of error and status register is
 *            disabled when in debug/suspend mode
 */
uint32_t DCANGetErrStatus(uint32_t baseAddr);

/**
 * \brief     This API will read the error counter status of DCAN
 *
 * \param     baseAddr         Base Address of the DCAN module register
 *
 * \return    Returns the error counter status values. For valid values refer
 *            enum #dcanErrCntrMask_t
 */
uint32_t DCANGetErrCntrStatus(uint32_t baseAddr);

/**
 * \brief     This API will read the DCAN parity error status
 *
 * \param     baseAddr         Base Address of the DCAN module register
 *
 * \return    Returns the DCAN parity error status. For valid values refer
 *            enum #dcanParityErrSts_t
 */
uint32_t DCANGetParityErrStatus(uint32_t baseAddr);

/**
 * \brief     This API returns message object number where DCAN ECC Single
 *            Bit Error is detected
 *
 * \param     baseAddr  Base Address of the DCAN module register
 *
 * \return    retVal    Returns the message object number where DCAN ECC Single
 *                      Bit Error is detected
 *                      For Tda2xx it returns DCAN_INVALID_MSG_OBJECT
 *
 * \note      This API is valid only for Tda3xx
 */
uint32_t DCANGetMsgObjBitErrDetected(uint32_t baseAddr);

/**
 * \brief     This API will read the ECC diagnostic status information of DCAN
 *            controller
 *
 * \param     baseAddr         Base Address of the DCAN module register
 *
 * \return    Returns the ECC disagnostic error status information.
 *            For valid values refer enum dcanEccDiagErrStsMask_t
 *
 * \note      This API is valid only for Tda3xx
 */
uint32_t DCANGetEccDiagErrStatus(uint32_t baseAddr);

/**
 * \brief     This API will read the ECC error status information of DCAN
 *            controller
 *
 * \param     baseAddr         Base Address of the DCAN module register
 *
 * \return    Returns the ECC error status information.
 *
 * \note      This API is valid only for Tda3xx
 */
uint32_t DCANGetEccErrStatus(uint32_t baseAddr);

/**
 * \brief     Enable/disable the DCAN parity/ECC
 *
 * \param     baseAddr    Base Address of the DCAN module register
 * \param     enablePMD   Enable/Disable DCAN parity(for Tda2xx)/ECC(for Tda3xx)
 *                        Valid values: TRUE or FALSE
 *
 * \return  None
 */
void DCANParityEnable(uint32_t baseAddr, uint32_t enablePMD);

/**
 * \brief     Enable/ Disable the test mode of DCAN
 *
 * \param     baseAddr         Base Address of the DCAN module register
 * \param     enableTestMode   Enable/Disable test mode of DCAN.
 *                             Valid values: TRUE or FALSE
 * \param     testMode         Select the DCAN test mode
 *                             For valid values refer enum # dcanTestMode_t
 *
 * \return  None
 */
void DCANTestModeEnable(uint32_t baseAddr,
                        uint32_t enableTestMode,
                        uint32_t testMode);

/**
 * \brief     Enable/disable the DCAN ECC Diagnostic Mode.
 *
 * \param     baseAddr              Base Address of the DCAN module register
 * \param     enableEccDiagMode     Enable/Disable DCAN ECC Diagnostic Mode
 *                                  Valid values: TRUE or FALSE
 *
 * \return  None
 *
 * \note      This API is valid only for Tda3xx
 */
void DCANEccDiagModeEnable(uint32_t baseAddr, uint32_t enableEccDiagMode);

/**
 * \brief     This API is used to Enable/disable SECDED Single bit Error
 *            correction and SECDED Single bit Error Event
 *
 * \param     baseAddr              Base Address of the DCAN module register
 * \param     enableEccMode         Enable/Disable SECDED Single bit Error
 *                                  correction.
 *                                  Valid values: TRUE or FALSE
 * \param     enableSbeEvent        Enable/Disable SECDED Single bit Error
 *                                  Event.
 *                                  Valid values: TRUE or FALSE
 *
 * \return  None
 *
 * \note      This API is valid only for Tda3xx
 */
void DCANEccModeEnable(uint32_t baseAddr,
                       uint32_t enableEccMode,
                       uint32_t enableSbeEvent);

/**
 * \brief   This function clears the error status of DCAN ECC.
 *
 * \param   baseAddr        Dcan base address
 * \param   errClr          Holds the values of which error need to be cleared.
 *                          Refer #dcanEccErrStatus_t for more details.
 *                          A value of 1 is written to these fields that need to
 *                          be cleared and 0 for those that need not be cleared.
 *
 * \return  STW_SOK on success else STW_EFAIL
 *
 * \note      This API is valid only for Tda3xx
 */
int32_t DCANClrEccErrStatus(uint32_t                  baseAddr,
                            const dcanEccErrStatus_t *errClr);

/**
 * \brief   This function clears the error status of DCAN ECC Diagnostic.
 *
 * \param   baseAddr        Dcan base address
 * \param   errClr          Holds the values of which error need to be cleared.
 *                          Refer #dcanEccErrStatus_t for more details.
 *                          A value of 1 is written to these fields that need to
 *                          be cleared and 0 for those that need not be cleared.
 *
 * \return  STW_SOK on success else STW_EFAIL
 *
 * \note      This API is valid only for Tda3xx
 */
int32_t DCANClrEccDiagErrStatus(uint32_t                  baseAddr,
                                const dcanEccErrStatus_t *errClr);

/**
 * \brief   This function clears the status of parity error on
 *          DCAN_PARITY interrupt line
 *
 * \param   baseAddr        Dcan base address
 *
 * \return  None
 */
void DCANClrParityIntrStatus(uint32_t baseAddr);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DCAN_H_ */
 /** @} */
/********************************* End of file ******************************/
