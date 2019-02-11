/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \defgroup CSL_MCASP McASP
 *
 *  @{
 */
 /**
 *  \file   mcasp.h
 *
 *  \brief  McASP API prototypes and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 *
 **/

#ifndef MCASP_H_
#define MCASP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_mcasp.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define MCASP_RESET                             ((uint32_t) 0x00U)
#define MCASP_ENABLE                            ((uint32_t) 0x01U)
#define MCASP_DISABLE                           ((uint32_t) 0x00U)

#define RX                                0x00U
#define TX                                0x01U

/*
 * \name Macros to combine to pass as formatVal to the API McASPTxFmtSet.
 *  @{
*/
/* Transmit Sync Bit delay */
#define MCASP_TX_SYNC_DELAY_0BIT          ((uint32_t) MCASP_TXFMT_XDATDLY_0BIT \
                                           << MCASP_TXFMT_XDATDLY_SHIFT)
#define MCASP_TX_SYNC_DELAY_1BIT          ((uint32_t) MCASP_TXFMT_XDATDLY_1BIT \
                                           << MCASP_TXFMT_XDATDLY_SHIFT)
#define MCASP_TX_SYNC_DELAY_2BIT          ((uint32_t) MCASP_TXFMT_XDATDLY_2BIT \
                                           << MCASP_TXFMT_XDATDLY_SHIFT)

/* Bit Stream output, whether MSB or LSB shall be out first */
#define MCASP_TX_BITSTREAM_LSB_FIRST      (0x0U)
#define MCASP_TX_BITSTREAM_MSB_FIRST      (0x00008000U)

/* Padding options for unused bits */
#define MCASP_TX_PAD_WITH_0               (0x00000000U)
#define MCASP_TX_PAD_WITH_1               (0x00002000U)
#define MCASP_TX_PAD_WITH_PBIT(n)         ((0x00004000U) | \
                                           ((n) << MCASP_TXFMT_XPBIT_SHIFT))

/* Transmit slot size to be used */
#define MCASP_TX_SLOTSIZE_8BITS           (MCASP_TXFMT_XSSZ_8BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)
#define MCASP_TX_SLOTSIZE_12BITS          (MCASP_TXFMT_XSSZ_12BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)
#define MCASP_TX_SLOTSIZE_16BITS          (MCASP_TXFMT_XSSZ_16BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)
#define MCASP_TX_SLOTSIZE_20BITS          (MCASP_TXFMT_XSSZ_20BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)
#define MCASP_TX_SLOTSIZE_24BITS          (MCASP_TXFMT_XSSZ_24BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)
#define MCASP_TX_SLOTSIZE_28BITS          (MCASP_TXFMT_XSSZ_28BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)
#define MCASP_TX_SLOTSIZE_32BITS          (MCASP_TXFMT_XSSZ_32BITS \
                                           << MCASP_TXFMT_XSSZ_SHIFT)

/* Transmit buffer write origin */
#define MCASP_TX_BUF_DMAPORT              (0x0U)
#define MCASP_TX_BUF_PERICONFIGPORT       (0x8U)

/* Rotate value for the transmit rotate right format unit */
#define MCASP_TX_ROT_RIGHT_NONE           (MCASP_TXFMT_XROT_NONE)
#define MCASP_TX_ROT_RIGHT_4BITS          (MCASP_TXFMT_XROT_4BITS)
#define MCASP_TX_ROT_RIGHT_8BITS          (MCASP_TXFMT_XROT_8BITS)
#define MCASP_TX_ROT_RIGHT_12BITS         (MCASP_TXFMT_XROT_12BITS)
#define MCASP_TX_ROT_RIGHT_16BITS         (MCASP_TXFMT_XROT_16BITS)
#define MCASP_TX_ROT_RIGHT_20BITS         (MCASP_TXFMT_XROT_20BITS)
#define MCASP_TX_ROT_RIGHT_24BITS         (MCASP_TXFMT_XROT_24BITS)
#define MCASP_TX_ROT_RIGHT_28BITS         (MCASP_TXFMT_XROT_28BITS)
/* @} */

/*
 * \name Macros to combine to pass as formatVal to the API McASPRxFmtSet.
 *  @{
*/
/* Receive Bit delay */
#define MCASP_RX_SYNC_DELAY_0BIT          ((uint32_t) MCASP_RXFMT_RDATDLY_0BIT \
                                           << MCASP_RXFMT_RDATDLY_SHIFT)
#define MCASP_RX_SYNC_DELAY_1BIT          ((uint32_t) MCASP_RXFMT_RDATDLY_1BIT \
                                           << MCASP_RXFMT_RDATDLY_SHIFT)
#define MCASP_RX_SYNC_DELAY_2BIT          ((uint32_t) MCASP_RXFMT_RDATDLY_2BIT \
                                           << MCASP_RXFMT_RDATDLY_SHIFT)

/* Bit Stream input, whether MSB or LSB shall be out first */
#define MCASP_RX_BITSTREAM_LSB_FIRST      (0x0U)
#define MCASP_RX_BITSTREAM_MSB_FIRST      (0x00008000U)

/* Padding options for unused bits */
#define MCASP_RX_PAD_WITH_0               (0x00000000U)
#define MCASP_RX_PAD_WITH_1               (0x00002000U)
#define MCASP_RX_PAD_WITH_PBIT(n)         ((0x00004000U) | \
                                           ((n) << MCASP_RXFMT_RPBIT_SHIFT))

/* Receive slot size to be used */
#define MCASP_RX_SLOTSIZE_8BITS           (MCASP_RXFMT_RSSZ_8BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)
#define MCASP_RX_SLOTSIZE_12BITS          (MCASP_RXFMT_RSSZ_12BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)
#define MCASP_RX_SLOTSIZE_16BITS          (MCASP_RXFMT_RSSZ_16BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)
#define MCASP_RX_SLOTSIZE_20BITS          (MCASP_RXFMT_RSSZ_20BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)
#define MCASP_RX_SLOTSIZE_24BITS          (MCASP_RXFMT_RSSZ_24BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)
#define MCASP_RX_SLOTSIZE_28BITS          (MCASP_RXFMT_RSSZ_28BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)
#define MCASP_RX_SLOTSIZE_32BITS          (MCASP_RXFMT_RSSZ_32BITS \
                                           << MCASP_RXFMT_RSSZ_SHIFT)

/* Receive buffer origin */
#define MCASP_RX_BUF_DMAPORT              (0x0U)
#define MCASP_RX_BUF_PERICONFIGPORT       (0x8U)

/* Rotate value for the receive rotate right format unit */
#define MCASP_RX_ROT_RIGHT_NONE           (MCASP_RXFMT_RROT_NONE)
#define MCASP_RX_ROT_RIGHT_4BITS          (MCASP_RXFMT_RROT_4BITS)
#define MCASP_RX_ROT_RIGHT_8BITS          (MCASP_RXFMT_RROT_8BITS)
#define MCASP_RX_ROT_RIGHT_12BITS         (MCASP_RXFMT_RROT_12BITS)
#define MCASP_RX_ROT_RIGHT_16BITS         (MCASP_RXFMT_RROT_16BITS)
#define MCASP_RX_ROT_RIGHT_20BITS         (MCASP_RXFMT_RROT_20BITS)
#define MCASP_RX_ROT_RIGHT_24BITS         (MCASP_RXFMT_RROT_24BITS)
#define MCASP_RX_ROT_RIGHT_28BITS         (MCASP_RXFMT_RROT_28BITS)
/* @} */

/*
 * \name Macros which can be passed as txMode to McASPTxFmtI2SSet API.
 *  @{
*/
#define MCASP_TX_MODE_NON_DMA             (MCASP_TX_BUF_PERICONFIGPORT)
#define MCASP_TX_MODE_DMA                 (MCASP_TX_BUF_DMAPORT)
/* @} */

/*
 * \name Macros which can be passed as rxMode to McASPRxFmtI2SSet API.
 *  @{
 */
#define MCASP_RX_MODE_NON_DMA             (MCASP_RX_BUF_PERICONFIGPORT)
#define MCASP_RX_MODE_DMA                 (MCASP_RX_BUF_DMAPORT)
/* @} */

/*
 * \name Macros which can be passed as fsWidth to McASPTxFrameSyncCfg API.
 * @{
*/
#define MCASP_TX_FS_WIDTH_BIT             (0x00000000U)
#define MCASP_TX_FS_WIDTH_WORD            (0x00000001U)
/* @} */

/*
 * \name Macros which can be passed as fsSetting to McASPTxFrameSyncCfg API.
 * @{
*/
#define MCASP_TX_FS_INT_BEGIN_ON_RIS_EDGE  (0x00000002U)
#define MCASP_TX_FS_INT_BEGIN_ON_FALL_EDGE (0x00000003U)
#define MCASP_TX_FS_EXT_BEGIN_ON_RIS_EDGE  (0x00000000U)
#define MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE (0x00000001U)

#define MCASP_TX_FS_INTERNAL               (0x00000002U)
#define MCASP_TX_FS_EXTERNAL               (0x00000000U)
/* @} */

/*
 * \name Macros which can be passed as fsWidth to McASPRxFrameSyncCfg API.
 * @{
*/
#define MCASP_RX_FS_WIDTH_BIT             (0x00000000U)
#define MCASP_RX_FS_WIDTH_WORD            (0x00000010U)
/* @} */

/*
 * \name Macros which can be passed as fsSetting to McASPRxFrameSyncCfg API.
 * @{
*/
#define MCASP_RX_FS_INT_BEGIN_ON_RIS_EDGE  (0x00000002U)
#define MCASP_RX_FS_INT_BEGIN_ON_FALL_EDGE (0x00000003U)
#define MCASP_RX_FS_EXT_BEGIN_ON_RIS_EDGE  (0x00000000U)
#define MCASP_RX_FS_EXT_BEGIN_ON_FALL_EDGE (0x00000001U)

#define MCASP_RX_FS_INTERNAL               (0x00000002U)
#define MCASP_RX_FS_EXTERNAL               (0x00000000U)
/* @} */

/*
 * \name Macros which can be passed as clkSrc to McASPTxClkCfg API and
 * McASPTxClkStart API.
 * @{
*/
#define MCASP_TX_CLK_INTERNAL             (0x00008020U)
#define MCASP_TX_CLK_EXTERNAL             (0x00000000U)
#define MCASP_TX_CLK_MIXED                (0x00000020U)
/* @} */

/*
 * \name Macros which can be passed as clkSrc to McASPRxClkCfg API and
 * McASPRxClkStart API.
 * @{
*/
#define MCASP_RX_CLK_INTERNAL             (0x00008020U)
#define MCASP_RX_CLK_EXTERNAL             (0x00000000U)
#define MCASP_RX_CLK_MIXED                (0x00000020U)
/* @} */

/*
 * \name Macros which can be passed as polarity to McASPTxClkPolaritySet API.
 * @{
*/
#define MCASP_TX_CLK_POL_RIS_EDGE         (0x00000000U)
#define MCASP_TX_CLK_POL_FALL_EDGE        (0x00000080U)
/* @} */

/*
 * \name Macros which can be passed as polarity to McASPRxClkPolaritySet API.
 * @{
*/
#define MCASP_RX_CLK_POL_RIS_EDGE         (0x00000080U)
#define MCASP_RX_CLK_POL_FALL_EDGE        (0x00000000U)
/* @} */

/*
 * \name Macros which can be passed as polarity to the API McASPTxHFClkPolaritySet.
 * @{
*/
#define MCASP_TX_HI_FREQ_CLK_NO_INVERT    (0x00000000U)
#define MCASP_TX_HI_FREQ_CLK_INVERT       (MCASP_AHCLKXCTL_HCLKXP_MASK)
/* @} */

/*
 * \name Macros which can be passed as polarity to the API McASPRxHFClkPolaritySet.
 * @{
*/
#define MCASP_RX_HI_FREQ_CLK_NO_INVERT    (0x00000000U)
#define MCASP_RX_HI_FREQ_CLK_INVERT       (MCASP_AHCLKRCTL_HCLKRP_MASK)
/* @} */

/*
 * \name Macros which can be passed as intMask to the APIs McASPTxIntEnable/Disable
 * intMask can be an OR combination of the below macros
 * @{
*/
#define MCASP_TX_STARTOFFRAME             (MCASP_EVTCTLX_XSTAFRM_MASK)
#define MCASP_TX_DATAREADY                (MCASP_EVTCTLX_XDATA_MASK)
#define MCASP_TX_LASTSLOT                 (MCASP_EVTCTLX_XLAST_MASK)
#define MCASP_TX_DMAERROR                 (MCASP_EVTCTLX_XDMAERR_MASK)
#define MCASP_TX_CLKFAIL                  (MCASP_EVTCTLX_XCKFAIL_MASK)
#define MCASP_TX_SYNCERROR                (MCASP_EVTCTLX_XSYNCERR_MASK)
#define MCASP_TX_UNDERRUN                 (MCASP_EVTCTLX_XUNDRN_MASK)
/* @} */

/*
 * \name Macros which can be passed as intMask to the APIs McASPRxIntEnable/Disable
 * intMask can be an OR combination of the below macros
 * @{
*/
#define MCASP_RX_STARTOFFRAME             (MCASP_EVTCTLR_RSTAFRM_MASK)
#define MCASP_RX_DATAREADY                (MCASP_EVTCTLR_RDATA_MASK)
#define MCASP_RX_LASTSLOT                 (MCASP_EVTCTLR_RLAST_MASK)
#define MCASP_RX_DMAERROR                 (MCASP_EVTCTLR_RDMAERR_MASK)
#define MCASP_RX_CLKFAIL                  (MCASP_EVTCTLR_RCKFAIL_MASK)
#define MCASP_RX_SYNCERROR                (MCASP_EVTCTLR_RSYNCERR_MASK)
#define MCASP_RX_OVERRUN                  (MCASP_EVTCTLR_ROVRN_MASK)
/* @} */

/*
 * \name Macros which can be used in pinMask to the APIs
 * McASPPinDirOutput and SetMcASPPinDirInputSet, McASPPinMcASPSet
 * and McASPPinGPIOSet
 * @{
*/
#define MCASP_PIN_AFSR                    (MCASP_PDIR_AFSR_MASK)
#define MCASP_PIN_ACLKR                   (MCASP_PDIR_ACLKR_MASK)
#define MCASP_PIN_AFSX                    (MCASP_PDIR_AFSX_MASK)
#define MCASP_PIN_AHCLKX                  (MCASP_PDIR_AHCLKX_MASK)
#define MCASP_PIN_ACLKX                   (MCASP_PDIR_ACLKX_MASK)
#define MCASP_PIN_AMUTE                   (MCASP_PDIR_AMUTE_MASK)
#define MCASP_PIN_AXR(n)                  (1U << (n))
/* @} */

/*
 * \name Macros which can be passed as pinState to the API McASPTxAMuteEnable
 * @{
*/
#define MCASP_AMUTE_PIN_HIGH              (0x00000001)
#define MCASP_AMUTE_PIN_LOW               (0x00000002)
/* @} */

/*
 * \name Macros which can be passed as clkDiv to the API McASPTxClkCheckConfig
 * @{
*/
#define MCASP_TX_CLKCHCK_DIV1             (MCASP_TXCLKCHK_XPS_DIVBY1)
#define MCASP_TX_CLKCHCK_DIV2             (MCASP_TXCLKCHK_XPS_DIVBY2)
#define MCASP_TX_CLKCHCK_DIV4             (MCASP_TXCLKCHK_XPS_DIVBY4)
#define MCASP_TX_CLKCHCK_DIV8             (MCASP_TXCLKCHK_XPS_DIVBY8)
#define MCASP_TX_CLKCHCK_DIV16            (MCASP_TXCLKCHK_XPS_DIVBY16)
#define MCASP_TX_CLKCHCK_DIV32            (MCASP_TXCLKCHK_XPS_DIVBY32)
#define MCASP_TX_CLKCHCK_DIV64            (MCASP_TXCLKCHK_XPS_DIVBY64)
#define MCASP_TX_CLKCHCK_DIV128           (MCASP_TXCLKCHK_XPS_DIVBY128)
#define MCASP_TX_CLKCHCK_DIV256           (MCASP_TXCLKCHK_XPS_DIVBY256)
/* @} */

/*
 * \name Macros which can be passed as clkDiv to the API McASPRxClkCheckConfig
 * @{
*/
#define MCASP_RX_CLKCHCK_DIV1             (MCASP_RXCLKCHK_RPS_DIVBY1)
#define MCASP_RX_CLKCHCK_DIV2             (MCASP_RXCLKCHK_RPS_DIVBY2)
#define MCASP_RX_CLKCHCK_DIV4             (MCASP_RXCLKCHK_RPS_DIVBY4)
#define MCASP_RX_CLKCHCK_DIV8             (MCASP_RXCLKCHK_RPS_DIVBY8)
#define MCASP_RX_CLKCHCK_DIV16            (MCASP_RXCLKCHK_RPS_DIVBY16)
#define MCASP_RX_CLKCHCK_DIV32            (MCASP_RXCLKCHK_RPS_DIVBY32)
#define MCASP_RX_CLKCHCK_DIV64            (MCASP_RXCLKCHK_RPS_DIVBY64)
#define MCASP_RX_CLKCHCK_DIV128           (MCASP_RXCLKCHK_RPS_DIVBY128)
#define MCASP_RX_CLKCHCK_DIV256           (MCASP_RXCLKCHK_RPS_DIVBY256)
/* @} */

/*
 * \name Macros which can be passed as usrDataBits to the APIs
 * McASPDITChanUsrDataWrite and McASPDITChanUsrDataRead.
 * @{
*/
#define MCASP_DIT_USRDATA_BITS_0_31       (0x00000000)
#define MCASP_DIT_USRDATA_BITS_32_63      (0x00000001)
#define MCASP_DIT_USRDATA_BITS_64_95      (0x00000002)
#define MCASP_DIT_USRDATA_BITS_96_127     (0x00000003)
#define MCASP_DIT_USRDATA_BITS_128_159    (0x00000004)
#define MCASP_DIT_USRDATA_BITS_160_191    (0x00000005)
/* @} */

/*
 * \name Macros for tokens returned by the API McASPTxStatusGet
 * @{
*/
#define MCASP_TX_STAT_ERR                 (uint32_t) (MCASP_TXSTAT_XERR_MASK)
#define MCASP_TX_STAT_DMAERR              (uint32_t) (MCASP_TXSTAT_XDMAERR_MASK)
#define MCASP_TX_STAT_STARTOFFRAME        (uint32_t) (MCASP_TXSTAT_XSTAFRM_MASK)
#define MCASP_TX_STAT_DATAREADY           (uint32_t) (MCASP_TXSTAT_XDATA_MASK)
#define MCASP_TX_STAT_LASTSLOT            (uint32_t) (MCASP_TXSTAT_XLAST_MASK)
#define MCASP_TX_STAT_CURRSLOT_EVEN       (uint32_t) ( \
        MCASP_TXSTAT_XTDMSLOT_MASK)
#define MCASP_TX_STAT_CURRSLOT_ODD        (uint32_t) (0x00000000)
#define MCASP_TX_STAT_CLKFAIL             (uint32_t) (MCASP_TXSTAT_XCKFAIL_MASK)
#define MCASP_TX_STAT_SYNCERR             (uint32_t) ( \
        MCASP_TXSTAT_XSYNCERR_MASK)
#define MCASP_TX_STAT_UNDERRUN            (uint32_t) (MCASP_TXSTAT_XUNDRN_MASK)
/* @} */

/*
 * \name Macros for tokens returned by the API McASPRxStatusGet
 * @{
*/
#define MCASP_RX_STAT_ERR                 (uint32_t) (MCASP_RXSTAT_RERR_MASK)
#define MCASP_RX_STAT_DMAERR              (uint32_t) (MCASP_RXSTAT_RDMAERR_MASK)
#define MCASP_RX_STAT_STARTOFFRAME       (uint32_t) (MCASP_RXSTAT_RSTAFRM_MASK)
#define MCASP_RX_STAT_DATAREADY           (uint32_t) (MCASP_RXSTAT_RDATA_MASK)
#define MCASP_RX_STAT_LASTSLOT            (uint32_t) (MCASP_RXSTAT_RLAST_MASK)
#define MCASP_RX_STAT_CURRSLOT_EVEN       (uint32_t) ( \
        MCASP_RXSTAT_RTDMSLOT_MASK)
#define MCASP_RX_STAT_CURRSLOT_ODD        (uint32_t) (0x00000000)
#define MCASP_RX_STAT_CLKFAIL             (uint32_t) (MCASP_RXSTAT_RCKFAIL_MASK)
#define MCASP_RX_STAT_SYNCERR             (uint32_t) ( \
        MCASP_RXSTAT_RSYNCERR_MASK)
#define MCASP_RX_STAT_OVERRUN             (uint32_t) (MCASP_RXSTAT_ROVRN_MASK)
/* @} */

/*
 * \name Valid idleMode Values
 * @{
*/
#define MCASP_IDLEMODE_FORCEIDLE        (uint32_t) (0x0)
#define MCASP_IDLEMODE_NOIDLE           (uint32_t) (0x1)
#define MCASP_IDLEMODE_SMARTIDLE        (uint32_t) (0x2)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum for McASP Loop-Back Order Bit.
 */
typedef enum mcaspLpbkOrder
{
    MCASP_LPBK_ORDER_ODD_TO_EVEN_SERIALIZERS = MCASP_LBCTL_ORD_ODD,
    /**< Odd serializers N + 1 transmit to even serializers N that
         receive. The corresponding serializers must be programmed
         properly. */
    MCASP_LPBK_ORDER_EVEN_TO_ODD_SERIALIZERS = MCASP_LBCTL_ORD_EVEN
    /**< Even serializers N transmit to odd serializers N+1 that
         receive. The corresponding serializers must be programmed
         properly. */
}mcaspLpbkOrder_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Resets the Transmit section of the McASP
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPTxReset(uint32_t baseAddr);

/**
 * \brief   Resets the Receive section of the McASP
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPRxReset(uint32_t baseAddr);

/**
 * \brief   Enables the Write FIFO for McASP. This shall be done before
 *          taking McASP out of Reset. First this API sets the FIFO parameters
 *          keeping the FIFO disabled. Then it enables the FIFO
 *
 * \param   baseAddr      Base Address of the McASP FIFO Registers.
 * \param   numTxSer      Number of Transmit Serializers to be used.
 * \param   minWdPerSer   The minimum number of words per serializer
 *                        to be available in FIFO to issue a DMA event.
 *
 * \return  None.
 *
 **/
extern void McASPWriteFifoEnable(uint32_t baseAddr, uint32_t numTxSer,
                                 uint32_t minWdPerSer);

/**
 * \brief   Enables the Read FIFO for McASP. This shall be done before
 *          taking McASP out of Reset. First this API sets the FIFO parameters
 *          keeping the FIFO disabled. Then it enables the FIFO
 *
 * \param   baseAddr      Base Address of the McASP FIFO Registers.
 * \param   numRxSer      Number of Receive Serializers to be used.
 * \param   minWdPerSer   The minimum number of words per serializer
 *                        to be available in FIFO to issue a DMA event.
 *
 * \return  None.
 *
 **/
extern void McASPReadFifoEnable(uint32_t baseAddr, uint32_t numRxSer,
                                uint32_t minWdPerSer);

/**
 * \brief   Sets the Format Mask for McASP Transmit section. The bits of
 *          the mask, which are set are transmitted out of McASP. The bits
 *          which are clear are padded according to the format settings.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   mask          Mask Value to be written, corresponding bits will
 *                        be transmitted out of McASP without any change
 *
 * \return  None.
 *
 **/
extern void McASPTxFmtMaskSet(uint32_t baseAddr, uint32_t mask);

/**
 * \brief   Sets the Format Mask for McASP Receive section. The bits of
 *          the mask, which are set are returned to the CPU/DMA. The bits
 *          which are clear are padded according to the format settings.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   mask          Mask Value to be written, corresponding bits will
 *                        be returned to the CPU/DMA
 *
 * \return  None.
 *
 **/
extern void McASPRxFmtMaskSet(uint32_t baseAddr, uint32_t mask);

/**
 * \brief   Sets the format for Transmit section of McASP with the format value
 *          input.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   formatVal     The format to be written to the transmit section
 *
 *    The formatVal shall be a logical OR combination of the parameters \n
 *     1. Transmit Sync Bit Dealy, which can take one of the values \n
 *            MCASP_TX_SYNC_DELAY_0BIT \n
 *            MCASP_TX_SYNC_DELAY_1BIT \n
 *            MCASP_TX_SYNC_DELAY_2BIT \n
 *
 *     2. Bit Stream Output, which can take one of the values \n
 *            MCASP_TX_BITSTREAM_LSB_FIRST \n
 *            MCASP_TX_BITSTREAM_MSB_FIRST \n
 *
 *     3. Padding Options, which can take one of the values \n
 *            MCASP_TX_PAD_WITH_0 \n
 *            MCASP_TX_PAD_WITH_1 \n
 *            MCASP_TX_PAD_WITH_PBIT(n) - pad the extra bytes with the
 *                                        n-th pad bit \n
 *
 *     4. Transmit Slot Size, which can take one of the values \n
 *            MCASP_TX_SLOTSIZE_8BITS \n
 *            MCASP_TX_SLOTSIZE_12BITS \n
 *            MCASP_TX_SLOTSIZE_16BITS \n
 *            MCASP_TX_SLOTSIZE_20BITS \n
 *            MCASP_TX_SLOTSIZE_24BITS \n
 *            MCASP_TX_SLOTSIZE_28BITS \n
 *            MCASP_TX_SLOTSIZE_32BITS \n
 *
 *     5. Transmit Buffer Origin, which can take one of the values \n
 *            MCASP_TX_BUF_DMAPORT \n
 *            MCASP_TX_BUF_PERICONFIGPORT \n
 *
 *     6. Value for Transmit Rotate unit, which can take one of the values \n
 *            MCASP_TX_ROT_RIGHT_NONE \n
 *            MCASP_TX_ROT_RIGHT_4BITS \n
 *            MCASP_TX_ROT_RIGHT_8BITS \n
 *            MCASP_TX_ROT_RIGHT_12BITS \n
 *            MCASP_TX_ROT_RIGHT_16BITS \n
 *            MCASP_TX_ROT_RIGHT_20BITS \n
 *            MCASP_TX_ROT_RIGHT_24BITS \n
 *            MCASP_TX_ROT_RIGHT_28BITS \n
 *
 *     For example, the reset value is
 *      (MCASP_TX_SYNC_DELAY_0BIT | MCASP_TX_BITSTREAM_LSB_FIRST |
 *       MCASP_TX_PAD_WITH_0 | MCASP_TX_SLOTSIZE_8BITS | MCASP_TX_BUF_DMAPORT |
 *       MCASP_TX_ROT_RIGHT_NONE)
 *
 * \return  None.
 *
 **/
extern void McASPTxFmtSet(uint32_t baseAddr, uint32_t formatVal);

/**
 * \brief   Sets the format for Receive section of McASP with the format value
 *          input.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   formatVal     The format to be written to the Receive section
 *
 *    The formatVal shall be a logical OR combination of the parameters \n
 *     1. Receive Bit Dealy, which can take one of the values \n
 *            MCASP_RX_SYNC_DELAY_0BIT \n
 *            MCASP_RX_SYNC_DELAY_1BIT \n
 *            MCASP_RX_SYNC_DELAY_2BIT \n
 *
 *     2. Receive serial bit stream order, which can take one of the values \n
 *            MCASP_RX_BITSTREAM_LSB_FIRST \n
 *            MCASP_RX_BITSTREAM_MSB_FIRST \n
 *
 *     3. Padding Options, which can take one of the values \n
 *            MCASP_RX_PAD_WITH_0 \n
 *            MCASP_RX_PAD_WITH_1 \n
 *            MCASP_RX_PAD_WITH_RPBIT(n) - pad the extra bytes with the
 *                                         n-th pad bit \n
 *
 *     4. Receive Slot Size, which can take one of the values \n
 *            MCASP_RX_SLOTSIZE_8BITS \n
 *            MCASP_RX_SLOTSIZE_12BITS \n
 *            MCASP_RX_SLOTSIZE_16BITS \n
 *            MCASP_RX_SLOTSIZE_20BITS \n
 *            MCASP_RX_SLOTSIZE_24BITS \n
 *            MCASP_RX_SLOTSIZE_28BITS \n
 *            MCASP_RX_SLOTSIZE_32BITS \n
 *
 *     5. Receive Buffer Origin, which can take one of the values \n
 *            MCASP_RX_BUF_DMAPORT \n
 *            MCASP_RX_BUF_PERICONFIGPORT \n
 *
 *     6. Value for Receive Rotate unit, which can take one of the values \n
 *            MCASP_RX_ROT_RIGHT_NONE \n
 *            MCASP_RX_ROT_RIGHT_4BITS \n
 *            MCASP_RX_ROT_RIGHT_8BITS \n
 *            MCASP_RX_ROT_RIGHT_12BITS \n
 *            MCASP_RX_ROT_RIGHT_16BITS \n
 *            MCASP_RX_ROT_RIGHT_20BITS \n
 *            MCASP_RX_ROT_RIGHT_24BITS \n
 *            MCASP_RX_ROT_RIGHT_28BITS \n
 *
 *     For example, the reset value is
 *      (MCASP_RX_SYNC_DELAY_0BIT | MCASP_RX_BITSTREAM_LSB_FIRST |
 *       MCASP_RX_PAD_WITH_0 | MCASP_RX_SLOTSIZE_8BITS | MCASP_RX_BUF_DMAPORT |
 *       MCASP_RX_ROT_RIGHT_NONE)
 *
 * \return  None.
 *
 **/
extern void McASPRxFmtSet(uint32_t baseAddr, uint32_t formatVal);

/**
 * \brief   Sets the I2S format in the Transmit Format unit.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   wordSize      The word size in bits.
 * \param   slotSize      Slot size in bits.
 * \param   txMode        The mode of Transmission.
 *             txMode can take one of the values \n
 *                  MCASP_TX_MODE_NON_DMA - transmission without using DMA \n
 *                  MCASP_TX_MODE_DMA - DMA is used for transmission
 *
 * \return  None.
 *
 *  Note : The Frame Sync shall be separately configured for I2S.
 *         It is assumed that the word size is a multiple of 8.
 *
 **/

extern void McASPTxFmtI2SSet(uint32_t baseAddr, uint32_t wordSize,
                             uint32_t slotSize, uint32_t txMode);

/**
 * \brief   Sets the I2S format in the Receive Format unit.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   wordSize      The word size in bits.
 * \param   slotSize      Slot size in bits.
 * \param   rxMode        The mode of reception.
 *             rxMode can take one of the values \n
 *                  MCASP_RX_MODE_NON_DMA - reception without using DMA \n
 *                  MCASP_RX_MODE_DMA - DMA is used for reception
 *
 * \return  None.
 *
 *  Note : The Frame Sync shall be separately configured for I2S.
 *         It is assumed that the word size is a multiple of 8.
 *
 **/

extern void McASPRxFmtI2SSet(uint32_t baseAddr, uint32_t wordSize,
                             uint32_t slotSize, uint32_t rxMode);

/**
 * \brief   Configures the Transmit Frame Sync signal.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   fsMode        The mode of Transmission
 * \param   fsWidth       The width of frame sync signal
 * \param   fsSetting     The signal settings for frame sync
 *
 *    fsMode is 0 for burst mode \n
 *    0x1 < fsMode < 0x21 for TDM mode with fsMode number of slots.
 *    Hence, fsMode = 2 for I2S mode \n
 *    fsMode is 384 for 384 slot DIT mode \n
 *
 *    fsWidth can take the values \n
 *         MCASP_TX_FS_WIDTH_BIT \n
 *         MCASP_TX_FS_WIDTH_WORD \n
 *
 *    fsSetting can take the values \n
 *         MCASP_TX_FS_INT_BEGIN_ON_RIS_EDGE - fs source is internal \n
 *         MCASP_TX_FS_INT_BEGIN_ON_FALL_EDGE - fs source is internal \n
 *         MCASP_TX_FS_EXT_BEGIN_ON_RIS_EDGE - fs source is external \n
 *         MCASP_TX_FS_EXT_BEGIN_ON_FALL_EDGE - fs source is external \n
 *
 * \return  None.
 *
 **/
extern void McASPTxFrameSyncCfg(uint32_t baseAddr, uint32_t fsMode,
                                uint32_t fsWidth, uint32_t fsSetting);

/**
 * \brief   Configures the Receive Frame Sync signal.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   fsMode        The mode of Reception
 * \param   fsWidth       The width of frame sync signal
 * \param   fsSetting     The signal settings for frame sync
 *
 *    fsMode is 0 for burst mode \n
 *    0x1 < fsMode < 0x21 for TDM mode with fsMode number of slots.
 *    Hence, fsMode = 2 for I2S mode \n
 *    fsMode is 384 for 384 slot DIR mode \n
 *
 *    fsWidth can take the values \n
 *         MCASP_RX_FS_WIDTH_BIT \n
 *         MCASP_RX_FS_WIDTH_WORD \n
 *
 *    fsSetting can take the values \n
 *         MCASP_RX_FS_INT_BEGIN_ON_RIS_EDGE - fs source is internal \n
 *         MCASP_RX_FS_INT_BEGIN_ON_FALL_EDGE - fs source is internal \n
 *         MCASP_RX_FS_EXT_BEGIN_ON_RIS_EDGE - fs source is external \n
 *         MCASP_RX_FS_EXT_BEGIN_ON_FALL_EDGE - fs source is external \n
 *
 * \return  None.
 *
 **/
extern void McASPRxFrameSyncCfg(uint32_t baseAddr, uint32_t fsMode,
                                uint32_t fsWidth, uint32_t fsSetting);

/**
 * \brief   Configures the clock for the Transmit Section for outputing bits.
 *          The source and divide values shall be pre-determined.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The source of the clock
 * \param   mixClkDiv     Value which divides the mixed clock
 * \param   auxClkDiv     Value which divides the internal high frequency clock
 *
 *    clkSrc can take the values \n
 *         MCASP_TX_CLK_INTERNAL \n
 *         MCASP_TX_CLK_EXTERNAL \n
 *         MCASP_TX_CLK_MIXED \n
 *
 *    mixClkDiv can take the values \n
 *         0x00 to 0x1Fh \n
 *
 *    auxClkDiv can take the values \n
 *         0x00 to 0xFFFh \n
 *
 * \return  None.
 *
 * Note: If external clock is selected, the divide values will not be used. \n
 *       If mixed clock is selected, the clock divide mixClkDiv only
 *       will be used. \n
 *       If internal clock is selected, both the divide values will be used.
 *
 **/
extern void McASPTxClkCfg(uint32_t baseAddr, uint32_t clkSrc,
                          uint32_t mixClkDiv, uint32_t auxClkDiv);

/**
 * \brief   Configures the clock for the Receive Section for receiving bits.
 *          The source and divide values shall be pre-determined.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The source of the clock
 * \param   mixClkDiv     Value which divides the mixed clock
 * \param   auxClkDiv     Value which divides the internal high frequency clock
 *
 *    clkSrc can take the values \n
 *         MCASP_RX_CLK_INTERNAL \n
 *         MCASP_RX_CLK_EXTERNAL \n
 *         MCASP_RX_CLK_MIXED \n
 *
 *    mixClkDiv can take the values \n
 *         0x00 to 0x1Fh \n
 *
 *    auxClkDiv can take the values \n
 *         0x00 to 0xFFFh \n
 *
 * \return  None.
 *
 * Note: If external clock is selected, the divide values will not be used. \n
 *       If mixed clock is selected, the clock divide mixClkDiv only
 *       will be used. \n
 *       If internal clock is selected, both the divide values will be used.
 *
 **/
extern void McASPRxClkCfg(uint32_t baseAddr, uint32_t clkSrc,
                          uint32_t mixClkDiv, uint32_t auxClkDiv);

/**
 * \brief   Sets the polarity of the Transmitter Clock. If an external receiver
 *          samples data on the falling edge of the serial clock,  the
 *          transmitter  must shift data out on the rising edge of the
 *          serial clock and vice versa.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      Polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_TX_CLK_POL_RIS_EDGE \n
 *         MCASP_TX_CLK_POL_FALL_EDGE \n
 *
 * \return  None.
 *
 **/
extern void McASPTxClkPolaritySet(uint32_t baseAddr, uint32_t polarity);

/**
 * \brief   Sets the Transmitter bit clock divide ratio.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkDiv        Clock divider to be chosen
 *
 *    clkDiv can take the values \n
 *         0h (R/W) = Divide-by-1. \n
 *         1h (R/W) = Divide-by-2. \n
 *         2h (R/W) = Divide-by-3 to divide-by-32 from 2h to 1Fh. \n
 *
 * \return  None.
 *
 **/
extern void McASPTxClkDivSet(uint32_t baseAddr, uint32_t clkDiv);


/**
 * \brief   Sets the polarity of the Rceiver Clock. If an external receiver
 *          shifts data on the falling edge of the serial clock,  the
 *          receiver  must sample the data on the rising edge of the
 *          serial clock and vice versa.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      Polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_RX_CLK_POL_RIS_EDGE \n
 *         MCASP_RX_CLK_POL_FALL_EDGE \n
 *
 * \return  None.
 *
 **/

extern void McASPRxClkPolaritySet(uint32_t baseAddr, uint32_t polarity);

/**
 * \brief   Sets the polarity/inversion of the  High Frequency clock. This is
 *          valid if the transmitter clock source is internal or mixed.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_TX_HI_FREQ_CLK_INVERT \n
 *         MCASP_TX_HI_FREQ_CLK_NO_INVERT \n
 *
 * \return  None.
 *
 **/

extern void McASPTxHFClkPolaritySet(uint32_t baseAddr,
                                    uint32_t polarity);

/**
 * \brief   Sets the polarity/inversion of the  High Frequency clock. This is
 *          valid if the receiver clock source is internal or mixed.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   polarity      Polarity to be chosen
 *
 *    polarity can take the values \n
 *         MCASP_RX_HI_FREQ_CLK_INVERT \n
 *         MCASP_RX_HI_FREQ_CLK_NO_INVERT \n
 *
 * \return  None.
 *
 **/

extern void McASPRxHFClkPolaritySet(uint32_t baseAddr,
                                    uint32_t polarity);

/**
 * \brief   Synchronizes the transmitter and receiver Clocks
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/

extern void McASPTxRxClkSyncEnable(uint32_t baseAddr);

/**
 * \brief   Disable synchronization of the transmitter and receiver Clocks
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/

extern void McASPTxRxClkSyncDisable(uint32_t baseAddr);

/**
 * \brief   Sets a serializer as transmitter
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer which is to be used as Transmitter.
 *
 * \return  None.
 *
 **/
extern void McASPSerializerTxSet(uint32_t baseAddr, uint32_t serNum);

/**
 * \brief   Sets a serializer as receiver
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer which is to be used as Receiver.
 *
 * \return  None.
 *
 **/

extern void McASPSerializerRxSet(uint32_t baseAddr, uint32_t serNum);

/**
 * \brief   Inactivates a serializer.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer which is to be inactivated.
 *
 * \return  None.
 *
 **/
extern void McASPSerializerInactivate(uint32_t baseAddr,
                                      uint32_t serNum);

/**
 * \brief   Configures a McASP pin as an output pin.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured as output
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n
 *                MCASP_PIN_ACLKR \n
 *                MCASP_PIN_AFSX \n
 *                MCASP_PIN_AHCLKX \n
 *                MCASP_PIN_ACLKX \n
 *                MCASP_PIN_AMUTE \n
 *                MCASP_PIN_AXR(n) - For serializer 'n'
 *
 * \return  None.
 *
 **/
extern void McASPPinDirOutputSet(uint32_t baseAddr, uint32_t pinMask);

/**
 * \brief   Configures a McASP pin as an input pin.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured as input
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n
 *                MCASP_PIN_ACLKR \n
 *                MCASP_PIN_AFSX \n
 *                MCASP_PIN_AHCLKX \n
 *                MCASP_PIN_ACLKX \n
 *                MCASP_PIN_AMUTE \n
 *                MCASP_PIN_AXR(n) - For serializer 'n'
 *
 * \return  None.
 *
 **/
extern void McASPPinDirInputSet(uint32_t baseAddr, uint32_t pinMask);

/**
 * \brief   Sets McASP pins to use for McASP functionality
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured for McASP.
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n
 *                MCASP_PIN_ACLKR \n
 *                MCASP_PIN_AFSX \n
 *                MCASP_PIN_AHCLKX \n
 *                MCASP_PIN_ACLKX \n
 *                MCASP_PIN_AMUTE \n
 *                MCASP_PIN_AXR(n) - For serializer 'n'
 *
 * \return  None.
 *
 **/
extern void McASPPinMcASPSet(uint32_t baseAddr, uint32_t pinMask);

/**
 * \brief   Sets McASP pins as GPIO for general purpose use
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   pinMask       Mask of the pins to be configured as GPIO.
 *            pinMask can be a combination of the below values \n
 *                MCASP_PIN_AFSR  \n
 *                MCASP_PIN_AHCLKR \n
 *                MCASP_PIN_ACLKR \n
 *                MCASP_PIN_AFSX \n
 *                MCASP_PIN_AHCLKX \n
 *                MCASP_PIN_ACLKX \n
 *                MCASP_PIN_AMUTE \n
 *                MCASP_PIN_AXR(n) - For serializer 'n'
 *
 * \return  None.
 *
 **/
extern void McASPPinGPIOSet(uint32_t baseAddr, uint32_t pinMask);

/**
 * \brief   Sets the active time slot for the Transmitter section. The
 *          bit which is set in the mask will indicate that data will be
 *          transmitted during that time slot.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   slotMask      The time slot mask.
 *
 * \return  None.
 *
 **/
extern void McASPTxTimeSlotSet(uint32_t baseAddr, uint32_t slotMask);

/**
 * \brief   Sets the active time slot for the receiver section. The
 *          bit which is set in the mask will indicate that data will be
 *          shifted in during that time slot.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   slotMask      The time slot mask.
 *
 * \return  None.
 *
 **/
extern void McASPRxTimeSlotSet(uint32_t baseAddr, uint32_t slotMask);

/**
 * \brief   Disables the specified Transmitter interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The transmitter interrupts to be disabled
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_TX_STARTOFFRAME \n
 *                 MCASP_TX_DATAREADY \n
 *                 MCASP_TX_LASTSLOT \n
 *                 MCASP_TX_DMAERROR \n
 *                 MCASP_TX_CLKFAIL \n
 *                 MCASP_TX_SYNCERROR \n
 *                 MCASP_TX_UNDERRUN
 *
 * \return  None.
 *
 **/
extern void McASPTxIntDisable(uint32_t baseAddr, uint32_t intMask);

/**
 * \brief   Disables the specified Receiver interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The receive interrupts to be disabled
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_RX_STARTOFFRAME \n
 *                 MCASP_RX_DATAREADY \n
 *                 MCASP_RX_LASTSLOT \n
 *                 MCASP_RX_DMAERROR \n
 *                 MCASP_RX_CLKFAIL \n
 *                 MCASP_RX_SYNCERROR \n
 *                 MCASP_RX_OVERRUN
 *
 * \return  None.
 *
 **/
extern void McASPRxIntDisable(uint32_t baseAddr, uint32_t intMask);

/**
 * \brief   Enables the specified Transmitter interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The transmitter interrupts to be enabled
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_TX_STARTOFFRAME \n
 *                 MCASP_TX_DATAREADY \n
 *                 MCASP_TX_LASTSLOT \n
 *                 MCASP_TX_DMAERROR \n
 *                 MCASP_TX_CLKFAIL \n
 *                 MCASP_TX_SYNCERROR \n
 *                 MCASP_TX_UNDERRUN
 *
 * \return  None.
 *
 **/
extern void McASPTxIntEnable(uint32_t baseAddr, uint32_t intMask);

/**
 * \brief   Enables the specified Receiver interrupts.
 *
 * \param   baseAddr     Base Address of the McASP Module Registers.
 * \param   intMask      The receive interrupts to be enabled
 *            intMask can be a logical OR combination of the values \n
 *                 MCASP_RX_STARTOFFRAME \n
 *                 MCASP_RX_DATAREADY \n
 *                 MCASP_RX_LASTSLOT \n
 *                 MCASP_RX_DMAERROR \n
 *                 MCASP_RX_CLKFAIL \n
 *                 MCASP_RX_SYNCERROR \n
 *                 MCASP_RX_OVERRUN
 *
 * \return  None.
 *
 **/
extern void McASPRxIntEnable(uint32_t baseAddr, uint32_t intMask);

/**
 * \brief   Starts the McASP Transmitter Clock.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The transmitter clock source.
 *
 *    clkSrc can take the values \n
 *         MCASP_TX_CLK_INTERNAL \n
 *         MCASP_TX_CLK_EXTERNAL \n
 *         MCASP_TX_CLK_MIXED \n
 *
 * \return  None.
 *
 **/
extern void McASPTxClkStart(uint32_t baseAddr, uint32_t clkSrc);

/**
 * \brief   Starts the McASP Receiver Clock.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkSrc        The receiver clock source.
 *
 *    clkSrc can take the values \n
 *         MCASP_RX_CLK_INTERNAL \n
 *         MCASP_RX_CLK_EXTERNAL \n
 *         MCASP_RX_CLK_MIXED \n
 *
 * \return  None.
 *
 **/
extern void McASPRxClkStart(uint32_t baseAddr, uint32_t clkSrc);

/**
 * \brief   Activates the Transmit Serializers
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPTxSerActivate(uint32_t baseAddr);

/**
 * \brief   Activates the Receive Serializers
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPRxSerActivate(uint32_t baseAddr);

/**
 * \brief   Enables the McASP Transmission. When this API is called,
 *          The transmit state machine and the frame sync generators are
 *          released from reset. The McASP starts transmission on the
 *          first frame sync after this.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPTxEnable(uint32_t baseAddr);

/**
 * \brief   Enables the McASP Reception. When this API is called,
 *          The receive state machine and the frame sync generators are
 *          released from reset. The McASP starts reception on the
 *          first frame sync after this.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPRxEnable(uint32_t baseAddr);

/**
 * \brief   Configures the transmitter clock check circuit.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkDiv        Divide value for the McASP system clock. The McASP
 *                        system clock is divided with this value before
 *                        passing to the clock check circuit
 * \param   boundMin      Transmit clock minimum boundary
 * \param   boundMax      Transmit clock maximum boundary
 *            clkDiv can take one of the following values \n
 *               MCASP_TX_CLKCHCK_DIV1 \n
 *               MCASP_TX_CLKCHCK_DIV2 \n
 *               MCASP_TX_CLKCHCK_DIV4 \n
 *               MCASP_TX_CLKCHCK_DIV8 \n
 *               MCASP_TX_CLKCHCK_DIV16 \n
 *               MCASP_TX_CLKCHCK_DIV32 \n
 *               MCASP_TX_CLKCHCK_DIV64 \n
 *               MCASP_TX_CLKCHCK_DIV128 \n
 *               MCASP_TX_CLKCHCK_DIV256
 *
 *            boundMin can take values between \n
 *               0x00 - 0xFFh
 *
 *            boundMax can take values between \n
 *               0x00 - 0xFFh
 *
 * \return  None.
 *
 **/
extern void McASPTxClkCheckConfig(uint32_t baseAddr, uint32_t clkDiv,
                                  uint8_t boundMin, uint8_t boundMax);

/**
 * \brief   Configures the receiver clock check circuit.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   clkDiv        Divide value for the McASP system clock. The McASP
 *                        system clock is divided with this value prior to
 *                        passing to the clock check circuit
 * \param   boundMin      Receive clock minimum boundary
 * \param   boundMax      Receive clock maximum boundary
 *            clkDiv can take one of the following values \n
 *               MCASP_RX_CLKCHCK_DIV1 \n
 *               MCASP_RX_CLKCHCK_DIV2 \n
 *               MCASP_RX_CLKCHCK_DIV4 \n
 *               MCASP_RX_CLKCHCK_DIV8 \n
 *               MCASP_RX_CLKCHCK_DIV16 \n
 *               MCASP_RX_CLKCHCK_DIV32 \n
 *               MCASP_RX_CLKCHCK_DIV64 \n
 *               MCASP_RX_CLKCHCK_DIV128 \n
 *               MCASP_RX_CLKCHCK_DIV256
 *
 *            boundMin can take values between \n
 *               0x00 - 0xFFh
 *
 *            boundMax can take values between \n
 *               0x00 - 0xFFh
 *
 * \return  None.
 *
 **/
extern void McASPRxClkCheckConfig(uint32_t baseAddr, uint32_t clkDiv,
                                  uint8_t boundMin, uint8_t boundMax);

/**
 * \brief   Writes to a transmit buffer through peripheral configuration port.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer number
 * \param   data          Data to be written
 *
 * \return  None.
 *
 **/
extern void McASPTxBufWrite(uint32_t baseAddr, uint32_t serNum,
                            uint32_t data);

/**
 * \brief   Reads a receive buffer through peripheral configuration port.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 * \param   serNum        Serializer number
 *
 * \return  Buffer contents
 *
 **/
extern uint32_t McASPRxBufRead(uint32_t baseAddr, uint32_t serNum);

/**
 * \brief   Gets the status of McASP transmission.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  Status of McASP Transmission. This is the contents of the
 *          register XSTAT. \n
 *          The below tokens can be used for each status bits returned. \n
 *              MCASP_TX_STAT_ERR  \n
 *              MCASP_TX_STAT_DMAERR \n
 *              MCASP_TX_STAT_STARTOFFRAME \n
 *              MCASP_TX_STAT_DATAREADY \n
 *              MCASP_TX_STAT_LASTSLOT \n
 *              MCASP_TX_STAT_CURRSLOT_EVEN \n
 *              MCASP_TX_STAT_CURRSLOT_ODD \n
 *              MCASP_TX_STAT_CLKFAIL \n
 *              MCASP_TX_STAT_SYNCERR \n
 *              MCASP_TX_STAT_UNDERRUN
 *
 **/
extern uint32_t McASPTxStatusGet(uint32_t baseAddr);

/**
 * \brief   Gets the status of McASP reception
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  Status of McASP reception. This is the contents of the
 *          register RSTAT. \n
 *          The below tokens can be used for each status bits returned. \n
 *              MCASP_RX_STAT_ERR  \n
 *              MCASP_RX_STAT_DMAERR \n
 *              MCASP_RX_STAT_STARTOFFRAME \n
 *              MCASP_RX_STAT_DATAREADY \n
 *              MCASP_RX_STAT_LASTSLOT \n
 *              MCASP_RX_STAT_CURRSLOT_EVEN \n
 *              MCASP_RX_STAT_CURRSLOT_ODD \n
 *              MCASP_RX_STAT_CLKFAIL \n
 *              MCASP_RX_STAT_SYNCERR \n
 *              MCASP_RX_STAT_OVERRUN
 *
 **/
extern uint32_t McASPRxStatusGet(uint32_t baseAddr);

/**
 * \brief   Resets the global control of McASP Transmit and Receive sections.
 *
 * \param   baseAddr      Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPGlobalCtlReset(uint32_t baseAddr);

/**
 * \brief   Sets the global control register for McASP Transmit and Receive
 *          sections.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   globalCtlVal   Value to be written, corresponding bits will
 *                         be set in the McASP global control register
 *
 * \note    For 'globalCtlVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPGlobalCtlSet(uint32_t baseAddr, uint32_t globalCtlVal);

/**
 * \brief   Reads the global control register of McASP Transmit and Receive
 *          sections.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  This API will return the present state of the global control
 *          register value.
 *
 **/
extern uint32_t McASPGlobalCtlGet(uint32_t baseAddr);

/**
 * \brief   Reads the Transmit global control section of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  present state of the TX global control
 *
 **/
extern uint32_t McASPTxGlobalCtlGet(uint32_t baseAddr);

/**
 * \brief   This call reads the Receive global control register of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  present state of the RX global control
 *
 **/
extern uint32_t McASPRxGlobalCtlGet(uint32_t baseAddr);

/**
 * \brief   Sets the global control register for McASP Transmit section.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   txGlobalCtlVal Value to be written, corresponding bits will
 *                         be set in the McASP TX global control register
 *
 * \note    For 'txGlobalCtlVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPTxGlobalCtlSet(uint32_t baseAddr, uint32_t txGlobalCtlVal);

/**
 * \brief   Sets the global control register for McASP Receive section.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   rxGlobalCtlVal Value to be written, corresponding bits will
 *                         be set in the McASP TX global control register
 *
 * \note    For 'rxGlobalCtlVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPRxGlobalCtlSet(uint32_t baseAddr, uint32_t rxGlobalCtlVal);

/**
 * \brief   Disables the Write FIFO of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPWriteFifoDisable(uint32_t baseAddr);

/**
 * \brief   Disables the Read FIFO of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  None.
 *
 **/
extern void McASPReadFifoDisable(uint32_t baseAddr);

/**
 * \brief   Reads the Transmit FIFO status of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Transmit FIFO status of McASP.
 *
 **/
extern uint32_t McASPTxFifoStatusGet(uint32_t baseAddr);

/**
 * \brief   Reads the Receive FIFO status of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Receive FIFO status of McASP.
 *
 **/
extern uint32_t McASPRxFifoStatusGet(uint32_t baseAddr);

/**
 * \brief   Reads the Transmit Interrupt status of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Transmit Interrupt status of McASP.
 *
 **/
extern uint32_t McASPTxIntrStatusGet(uint32_t baseAddr);

/**
 * \brief   Reads the Receive Interrupt status of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Receive Interrupt status of McASP.
 *
 **/
extern uint32_t McASPRxIntrStatusGet(uint32_t baseAddr);

/**
 * \brief   Reads the Format Mask for McASP Transmit section. The bits of
 *          the mask, which are set are transmitted out of McASP. The bits
 *          which are cleared are padded according to the format settings.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Transmit format Mask register value.
 *
 **/
extern uint32_t McASPTxFmtMaskGet(uint32_t baseAddr);

/**
 * \brief   Reads the Format Mask for McASP Receive section. The bits of
 *          the mask, which are set are returned to the CPU/DMA. The bits
 *          which are cleared are padded according to the format settings.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Receive format Mask register value.
 *
 **/
extern uint32_t McASPRxFmtMaskGet(uint32_t baseAddr);

/**
 * \brief   Reads the format for Transmit section of McASP
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Transmit format register value.
 *
 **/
extern uint32_t McASPTxFmtGet(uint32_t baseAddr);

/**
 * \brief   Reads the format for Receive section of McASP
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Receive format register value.
 *
 **/
extern uint32_t McASPRxFmtGet(uint32_t baseAddr);

/**
 * \brief   Reads the Transmit Frame Sync or Receive frame sync depending
 *          on the 'txOrRx' flag
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   txOrRx         Transmit or Receive
 *
 *    'txOrRx' can take the values \n
 *          TX \n
 *          RX \n
 *
 * \return  TX/RX Frame Sync control register value.
 *
 **/
extern uint32_t McASPTxRxFrameSyncRead(uint32_t baseAddr,
                                       uint8_t  txOrRx);

/**
 * \brief   Sets a serializer to user specified value
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   serNum         Serializer which needs to be set
 * \param   serCtlVal      Serializer control value specified by user
 *
 * \note    For 'serCtlVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPSerializerSet(uint32_t baseAddr, uint32_t serNum,
                               uint32_t serCtlVal);

/**
 * \brief   Reads from a specified serializer.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   serNum         Serializer which needs to be set
 *
 * \return  serializer value specified by user
 *
 **/
extern uint32_t McASPSerializerGet(uint32_t baseAddr, uint32_t serNum);

/**
 * \brief   Gives the transmit ready status of the serializer
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   serNum         Serializer which is used as Transmitter.
 *
 * \return  TRUE or FALSE.
 *
 **/
extern uint8_t McASPIsSerializerXmtReady(uint32_t baseAddr, uint32_t serNum);

/**
 * \brief   Gives the receive ready status of the specified serializer
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   serNum         Serializer which is used as Receiver.
 *
 * \return  receive ready status of the serializer.
 *
 **/
extern uint8_t McASPIsSerializerRcvReady(uint32_t baseAddr, uint32_t serNum);

/**
 * \brief   Reads the active time slot for the receiver/transmitter
 *          section. The bit which is set in the mask will indicate which data
 *          will be shifted out during that time slot.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   txOrRx         Transmit or Receive
 *
 *    'txOrRx' can take the values \n
 *          TX \n
 *          RX \n
 *
 * \return  RX/TX Time slot mask.
 *
 **/
extern uint32_t McASPTxRxTimeSlotGet(uint32_t baseAddr, uint8_t txOrRx);

/**
 * \brief   Configures the transmitter clock check circuit of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   tClkChkVal     Value to be written
 *
 * \note    For 'tClkChkVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPTxClkCheckRegWrite(uint32_t baseAddr, uint32_t tClkChkVal);

/**
 * \brief   Reads the transmitter clock check circuit register of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  contents of the TXCLKCHK register.
 *
 **/
extern uint32_t McASPTxClkCheckRegRead(uint32_t baseAddr);

/**
 * \brief     This call writes to the receiver clock check circuit of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   rClkChkVal     Value to be written
 *
 * \note    For 'rClkChkVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPRxClkCheckRegWrite(uint32_t baseAddr, uint32_t rClkChkVal);

/**
 * \brief   Reads the receiver clock check circuit register of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Contents of the register, RXCLKCHK. \n
 *
 **/
extern uint32_t McASPRxClkCheckRegRead(uint32_t baseAddr);

/**
 * \brief   Disables the specified Transmitter interrupts.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   intMask        The transmitter interrupts to be disabled
 *            'intMask' can be a logical OR combination of the values \n
 *                 MCASP_TX_STARTOFFRAME \n
 *                 MCASP_TX_DATAREADY \n
 *                 MCASP_TX_LASTSLOT \n
 *                 MCASP_TX_DMAERROR \n
 *                 MCASP_TX_CLKFAIL \n
 *                 MCASP_TX_SYNCERROR \n
 *                 MCASP_TX_UNDERRUN
 *
 * \return  None.
 *
 **/
extern void McASPTxIntDisable(uint32_t baseAddr, uint32_t intMask);

/**
 * \brief   Disables the specified Receiver interrupts.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   intMask        The receive interrupts to be disabled
 *            'intMask' can be a logical OR combination of the values \n
 *                 MCASP_RX_STARTOFFRAME \n
 *                 MCASP_RX_DATAREADY \n
 *                 MCASP_RX_LASTSLOT \n
 *                 MCASP_RX_DMAERROR \n
 *                 MCASP_RX_CLKFAIL \n
 *                 MCASP_RX_SYNCERROR \n
 *                 MCASP_RX_OVERRUN
 *
 * \return  None.
 *
 **/
extern void McASPRxIntDisable(uint32_t baseAddr, uint32_t intMask);

/**
 * \brief   Sets the status of McASP transmission.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \param   statusVal      'statusVal' to be set.
 *              Following values can be used to write to status register to
 *              clear corresponding bits \n
 *              MCASP_TX_STAT_ERR  \n
 *              MCASP_TX_STAT_DMAERR \n
 *              MCASP_TX_STAT_STARTOFFRAME \n
 *              MCASP_TX_STAT_DATAREADY \n
 *              MCASP_TX_STAT_LASTSLOT \n
 *              MCASP_TX_STAT_CURRSLOT_EVEN \n
 *              MCASP_TX_STAT_CURRSLOT_ODD \n
 *              MCASP_TX_STAT_CLKFAIL \n
 *              MCASP_TX_STAT_SYNCERR \n
 *              MCASP_TX_STAT_UNDERRUN
 *
 **/
extern void McASPTxStatusSet(uint32_t baseAddr, uint32_t statusVal);

/**
 * \brief   Sets the status of McASP reception
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \param   statusVal      'statusVal' to be set.
 *              Following values can be used to write to status register to
 *              clear corresponding bits \n
 *              MCASP_RX_STAT_ERR  \n
 *              MCASP_RX_STAT_DMAERR \n
 *              MCASP_RX_STAT_STARTOFFRAME \n
 *              MCASP_RX_STAT_DATAREADY \n
 *              MCASP_RX_STAT_LASTSLOT \n
 *              MCASP_RX_STAT_CURRSLOT_EVEN \n
 *              MCASP_RX_STAT_CURRSLOT_ODD \n
 *              MCASP_RX_STAT_CLKFAIL \n
 *              MCASP_RX_STAT_SYNCERR \n
 *              MCASP_RX_STAT_OVERRUN
 *
 **/
extern void McASPRxStatusSet(uint32_t baseAddr, uint32_t statusVal);

/**
 * \brief   Configures the Loopback control register of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   dlbCtlVal      Loopback control register value
 *
 * \note    For 'dlbCtlVal' refer hw_mcasp.h for the bit field desciptions
 *
 * \return  None.
 *
 **/
extern void McASPDlbRegWrite(uint32_t baseAddr, uint32_t dlbCtlVal);

/**
 * \brief   Reads the loopback control register of McASP.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  Loopback control register contents
 *
 **/
extern uint32_t McASPDlbRegRead(uint32_t baseAddr);

/**
 * \brief   Writes to the DIT mode control register.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   dITModeCtlVal  DIT mode control register value that needs to be set.
 *
 * \note    For 'dITModeCtlVal' refer hw_mcasp.h for the bit field descriptions
 *
 * \return  None.
 *
 **/
extern void McASPDITModeCtlWrite(uint32_t baseAddr, uint32_t dITModeCtlVal);

/**
 * \brief   Reads the DIT mode control register.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  DIT mode control register contents.
 *
 **/
extern uint32_t McASPDITModeCtlRead(uint32_t baseAddr);

/**
 * \brief   Sets the DIT Left Channel Status Register
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   leftChanNum    Left Channel Number.
 * \param   setVal         Value to be set.
 *
 * \return  None.
 *
 **/
extern void McASPDITLeftChanStatusSet(uint32_t baseAddr,
                                      uint32_t leftChanNum,
                                      uint32_t setVal);

/**
 * \brief   Sets the DIT Left Channel Status Register
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   rightChanNum   Right Channel Number.
 * \param   setVal         Value to be set.
 *
 * \return  None.
 *
 **/
extern void McASPDITRightChanStatusSet(uint32_t baseAddr,
                                       uint32_t rightChanNum,
                                       uint32_t setVal);

/**
 * \brief   Writes to the Left User Data RAM (DITUDRA/B0-5)
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   leftChanNum    Left Channel Number.
 * \param   setVal         UserDataRam Value to be set.
 *
 * \return  None.
 *
 **/
extern void McASPDITLeftUserDataRamSet(uint32_t baseAddr,
                                       uint32_t leftChanNum,
                                       uint32_t setVal);

/**
 * \brief   Writes to the Right User Data RAM (DITUDRB/B0-5)
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   rightChanNum   Right Channel Number.
 * \param   setVal         UserDataRam Value to be set.
 *
 * \return  None.
 *
 **/
extern void McASPDITRightUserDataRamSet(uint32_t baseAddr,
                                        uint32_t rightChanNum,
                                        uint32_t setVal);

/**
 * \brief   Reads the polarity of the Rceiver Clock.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  RX Clock polarity.
 *
 **/
extern uint32_t McASPRxClkPolarityGet(uint32_t baseAddr);

/**
 * \brief   Reads the polarity of the Transmitter Clock.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  TX Clock polarity.
 *
 **/
extern uint32_t McASPTxClkPolarityGet(uint32_t baseAddr);

/**
 * \brief   Reads the the Transmitter clock divide ratio.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  TX bit clock divide ratio.
 *
 **/
extern uint32_t McASPTxClkDivGet(uint32_t baseAddr);

/**
 * \brief   Reads the polarity of the Rceiver High Clock.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  RX HiClock polarity.
 *
 **/
extern uint32_t McASPRxHClkPolarityGet(uint32_t baseAddr);

/**
 * \brief   Reads the polarity of the Transmitter High Clock.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  TX HiClock polarity.
 *
 **/
extern uint32_t McASPTxHClkPolarityGet(uint32_t baseAddr);

/**
 * \brief   Returns the current transmitter slot.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  current transmit slot.
 *
 **/
extern uint16_t McASPCurrTransmitSlot(uint32_t baseAddr);

/**
 * \brief   Returns the current receiver slot.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return  current receive slot.
 *
 **/
extern uint16_t McASPCurrReceiveSlot(uint32_t baseAddr);

/**
 * \brief   Writes to the transmit/receiver DMA event control register
 *          depending on the 'txOrRx' flag set
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   txOrRx         Transmit or receive
 * \param   txRxDmaCntrlVal Value to be written to the TX/RX DMA control reg \n
 *
 *              Following values can be used for 'txOrRx' \n
 *              TX for transmit \n
 *              RX for receive \n
 *
 * \note    For 'txRxDmaCntrlVal' refer hw_mcasp.h for bit field descriptions
 *
 * \return  Transmit/Receive data DMA request.
 *
 **/
extern void McASPTxRxDMAEvtCntrlWrite(uint32_t baseAddr,
                                      uint8_t  txOrRx,
                                      uint32_t txRxDmaCntrlVal);

/**
 * \brief   Reads the transmit/receiver DMA event control register
 *          depending on the 'txOrRx' flag set
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   txOrRx         Transmit or receive
 *              Following values can be used for 'txOrRx' \n
 *              TX for transmit \n
 *              RX for receive \n
 *
 * \return  Transmit/Receive data DMA request.
 *
 **/
extern uint32_t McASPTxRxDMAEvtCntrlRead(uint32_t baseAddr,
                                         uint8_t  txOrRx);

/**
 * \brief   Returns true or false, depending on the corresponding
 *          transmit error status bit if is set or not
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   errFlag        errFlag whose status needs to be read
 *              Following values can be used to read tx status register \n
 *              MCASP_TX_STAT_ERR  \n
 *              MCASP_TX_STAT_DMAERR \n
 *              MCASP_TX_STAT_DATAREADY \n
 *              MCASP_TX_STAT_CLKFAIL \n
 *              MCASP_TX_STAT_SYNCERR \n
 *              MCASP_TX_STAT_UNDERRUN
 *
 * \return  True or False
 *
 **/
extern uint8_t McASPTxErrStatus(uint32_t baseAddr, uint32_t errFlag);

/**
 * \brief   Returns true or false, depending on the corresponding
 *          receive error status bit if is set or not
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 * \param   errFlag        errFlag whose status needs to be read
 *              Following values can be used to read tx status register \n
 *              MCASP_RX_STAT_ERR  \n
 *              MCASP_RX_STAT_DMAERR \n
 *              MCASP_RX_STAT_DATAREADY \n
 *              MCASP_RX_STAT_CLKFAIL \n
 *              MCASP_RX_STAT_SYNCERR \n
 *              MCASP_RX_STAT_OVERRUN
 *
 * \return  True or False
 *
 **/
extern uint8_t McASPRxErrStatus(uint32_t baseAddr, uint32_t errFlag);

/**
 * \brief   Returns the RSMRST and RFRST field values of RGBLCTL
 *          register.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return
 *          0x00         - Both receive frame generator sync and receive state
 *                         machine are reset.
 *          0x01         - Only receive state machine is active.
 *          0x10         - Only receive frame sync generator is active.
 *          0x11         - Both receive frame generator sync and receive state
 *                         machine are active.
 *
 */
extern uint8_t McASPGetSmFsRcv(uint32_t baseAddr);

/**
 * \brief   Returns the XSMRST and XFRST field values of XGBLCTL
 *          register.
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \return
 *          0x00         - Both transmit frame generator sync and transmit state
 *                         machine are reset.
 *          0x01         - Only transmit state machine is active.
 *          0x10         - Only transmit frame sync generator is active.
 *          0x11         - Both transmit frame generator sync and transmit state
 *                         machine are active.
 *
 */
extern uint8_t McASPGetSmFsXmt(uint32_t baseAddr);

/**
 * \brief   Sets  the desired Power IdleMode Configuration
 *
 * \param   baseAddr       Base Address of the McASP Module Registers.
 *
 * \param   idleMode       idleMode setting.
 *              Following values can be used to set Power Idle Configuration \n
 *              MCASP_IDLEMODE_FORCEIDLE  \n
 *              MCASP_IDLEMODE_NOIDLE  \n
 *              MCASP_IDLEMODE_SMARTIDLE  \n
 * \return  None.
 *
 */
extern void McASPSetPowerIdleConfig(uint32_t baseAddr, uint32_t idleMode);

/**
 * \brief     This function enables Digital loop-back for McASP module.
 *
 * \param     baseAddr        Base Address of the McASP registers.
 * \param     enableLpbk      Digital loop-back is enabled  if it is TRUE.
 *                            Digital loop-back is disabled  if it is FALSE.
 * \param     order           Loopback order bit when loopback mode is enabled
 *                            Refer enum #mcaspLpbkOrder_t.
 *
 * \return    None
 *
 */
void MCASPDigitalLpbkEnable(uint32_t baseAddr,
                            uint32_t enableLpbk,
                            uint32_t order);

#ifdef __cplusplus
}
#endif
#endif /* __HAL_MCASP_H__ */
 /** @} */
/********************************* End of file ******************************/
