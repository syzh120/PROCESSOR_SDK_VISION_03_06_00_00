/*!
 *  \file   cpsw.h
 *
 *  \brief  GMAC_SW_ APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

/*
 * Copyright (C) 2010-2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _GMAC_SW_H_
#define _GMAC_SW_H_



#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>

/* OS/Posix headers */

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*
** Macros which can be used as 'mode' to pass to the API GMAC_SW_SlTransferModeSet
*/
#define GMAC_SW_SLIVER_NON_GIG_FULL_DUPLEX        GMAC_SW_SL_MACCONTROL_FULLDUPLEX
#define GMAC_SW_SLIVER_NON_GIG_HALF_DUPLEX        (0x00u)
#define GMAC_SW_SLIVER_GIG_FULL_DUPLEX            GMAC_SW_SL_MACCONTROL_GIG
#define GMAC_SW_SLIVER_INBAND                     GMAC_SW_SL_MACCONTROL_EXT_EN

/*
** Macros which can be used as 'statFlag' to the API GMAC_SW_SlMACStatusGet
*/
#define GMAC_SW_SLIVER_STATE                      GMAC_SW_SL_MACSTATUS_IDLE
#define GMAC_SW_SLIVER_EXT_GIG_INPUT_BIT          GMAC_SW_SL_MACSTATUS_EXT_GIG
#define GMAC_SW_SLIVER_EXT_FULL_DUPLEX_BIT        GMAC_SW_SL_MACSTATUS_EXT_FULLDUPLEX
#define GMAC_SW_SLIVER_RX_FLOWCTRL                GMAC_SW_SL_MACSTATUS_RX_FLOW_ACT
#define GMAC_SW_SLIVER_TX_FLOWCTRL                GMAC_SW_SL_MACSTATUS_TX_FLOW_ACT

/*
** Macros returned by API GMAC_SW_SlMACStatusGet
*/
#define GMAC_SW_SLIVER_STATE_IDLE                 GMAC_SW_SL_MACSTATUS_IDLE
#define GMAC_SW_SLIVER_EXT_GIG_INPUT_HIGH         GMAC_SW_SL_MACSTATUS_EXT_GIG
#define GMAC_SW_SLIVER_EXT_FULL_DUPLEX_HIGH       GMAC_SW_SL_MACSTATUS_EXT_FULLDUPLEX
#define GMAC_SW_SLIVER_RX_FLOWCTRL_ACTIVE         GMAC_SW_SL_MACSTATUS_RX_FLOW_ACT
#define GMAC_SW_SLIVER_TX_FLOWCTRL_ACTIVE         GMAC_SW_SL_MACSTATUS_TX_FLOW_ACT

/*
** Macros which can be passed asi 'intFlag' to the API GMAC_SW_WrCoreIntEnable
** , GMAC_SW_WrCoreIntDisable and GMAC_SW_WrCoreIntStatusGet
*/
#define GMAC_SW_CORE_INT_RX_THRESH                (0x00u)
#define GMAC_SW_CORE_INT_RX_PULSE                 (0x04u)
#define GMAC_SW_CORE_INT_TX_PULSE                 (0x08u)
#define GMAC_SW_CORE_INT_MISC                     (0x0Cu)

/*
** Macros which can be passed as 'statFlag' to the API GMAC_SW_WrRGMIIStatusGet
*/
#define GMAC_SW_RGMII2_DUPLEX                     GMAC_SW_WR_RGMII_CTL_RGMII2_FULLDUPLEX
#define GMAC_SW_RGMII2_SPEED                      GMAC_SW_WR_RGMII_CTL_RGMII2_SPEED
#define GMAC_SW_RGMII2_LINK_STAT                  GMAC_SW_WR_RGMII_CTL_RGMII2_LINK
#define GMAC_SW_RGMII1_DUPLEX                     GMAC_SW_WR_RGMII_CTL_RGMII1_FULLDUPLEX
#define GMAC_SW_RGMII1_SPEED                      GMAC_SW_WR_RGMII_CTL_RGMII1_SPEED
#define GMAC_SW_RGMII1_LINK_STAT                  GMAC_SW_WR_RGMII_CTL_RGMII1_LINK

/* The values, one of which will be returned by GMAC_SW_WrRGMIIStatusGet */
#define GMAC_SW_RGMII2_DUPLEX_FULL                GMAC_SW_WR_RGMII_CTL_RGMII2_FULLDUPLEX
#define GMAC_SW_RGMII2_DUPLEX_HALF                (0x00u)
#define GMAC_SW_RGMII2_SPEED_10M                  (0x00u << GMAC_SW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT)
#define GMAC_SW_RGMII2_SPEED_100M                 (0x01u << GMAC_SW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT)
#define GMAC_SW_RGMII2_SPEED_1000M                (0x02u << GMAC_SW_WR_RGMII_CTL_RGMII2_SPEED_SHIFT)
#define GMAC_SW_RGMII2_LINK_UP                    GMAC_SW_WR_RGMII_CTL_RGMII2_LINK
#define GMAC_SW_RGMII2_LINK_DOWN                  (0x00u)
#define GMAC_SW_RGMII1_DUPLEX_FULL                GMAC_SW_WR_RGMII_CTL_RGMII1_FULLDUPLEX
#define GMAC_SW_RGMII1_DUPLEX_HALF                (0x00u)
#define GMAC_SW_RGMII1_SPEED_10M                  (0x00u << GMAC_SW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT)
#define GMAC_SW_RGMII1_SPEED_100M                 (0x01u << GMAC_SW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT)
#define GMAC_SW_RGMII1_SPEED_1000M                (0x02u << GMAC_SW_WR_RGMII_CTL_RGMII1_SPEED_SHIFT)
#define GMAC_SW_RGMII1_LINK_UP                    GMAC_SW_WR_RGMII_CTL_RGMII1_LINK
#define GMAC_SW_RGMII1_LINK_DOWN                  (0x00u)

/*
** Macros which can be passed as 'pacFlag' to the API GMAC_SW_WrIntPacingEnable
** GMAC_SW_WrIntPacingDisable
*/
#define GMAC_SW_INT_PACING_C0_RX_PULSE            (0x01 << GMAC_SW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define GMAC_SW_INT_PACING_C0_TX_PULSE            (0x02 << GMAC_SW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define GMAC_SW_INT_PACING_C1_RX_PULSE            (0x04 << GMAC_SW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define GMAC_SW_INT_PACING_C1_TX_PULSE            (0x08 << GMAC_SW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define GMAC_SW_INT_PACING_C2_RX_PULSE            (0x10 << GMAC_SW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)
#define GMAC_SW_INT_PACING_C2_TX_PULSE            (0x20 << GMAC_SW_WR_INT_CONTROL_INT_PACE_EN_SHIFT)

/*
** Macros which can be passed as 'portState' to GMAC_SW_ALEPortStateSet
*/
#define GMAC_SW_ALE_PORT_STATE_FWD                (0x03u)
#define GMAC_SW_ALE_PORT_STATE_LEARN              (0x02u)
#define GMAC_SW_ALE_PORT_STATE_BLOCKED            (0x01u)
#define GMAC_SW_ALE_PORT_STATE_DISABLED           (0x00u)

/*
** Macros which can be passed as 'eoiFlag' to GMAC_SW_CPDMAEndOfIntVectorWrite
*/
#define GMAC_SW_EOI_TX_PULSE                      (0x02u)
#define GMAC_SW_EOI_RX_PULSE                      (0x01u)
#define GMAC_SW_EOI_RX_THRESH_PULSE               (0x00u)
#define GMAC_SW_EOI_MISC_PULSE                    (0x03u)

/*
** Macro which can be passed as 'statFlag' to GMAC_SW_CPDMAStatusGet
** The same value can be used to compare against the idle status
*/
#define CPDMA_STAT_IDLE                        (GMAC_SW_CPDMA_DMASTATUS_IDLE)

/*
** Macro which can be passed as 'statFlag' to GMAC_SW_CPDMAStatusGet
*/
#define CPDMA_STAT_TX_HOST_ERR_CODE            (GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE)

/* The return values for the above 'statFlag' */
#define CPDMA_STAT_TX_NO_ERR                   (0x00u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_SOP_ERR                  (0x01u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_OWN_ERR                  (0x02u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_ZERO_DESC                (0x03u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_ZERO_BUF_PTR             (0x04u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_ZERO_BUF_LEN             (0x05u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_TX_PKT_LEN_ERR              (0x06u << GMAC_SW_CPDMA_DMASTATUS_TX_HOST_ERR_CODE_SHIFT)

/*
** Macro which can be passed as 'statFlag' to GMAC_SW_CPDMAStatusGet
*/
#define CPDMA_STAT_RX_HOST_ERR_CODE            (GMAC_SW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE)

/* The return values for the above 'statFlag' */
#define CPDMA_STAT_RX_NO_ERR                   (0x00u << GMAC_SW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_OWN_NOT_SET              (0x02u << GMAC_SW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_ZERO_BUF_PTR             (0x04u << GMAC_SW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_ZERO_BUF_LEN             (0x05u << GMAC_SW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)
#define CPDMA_STAT_RX_SOP_BUF_LEN_ERR          (0x06u << GMAC_SW_CPDMA_DMASTATUS_RX_HOST_ERR_CODE_SHIFT)

/*
** Macros which can be passed as 'statFlag' to GMAC_SW_CPDMAStatusGet
*/
#define CPDMA_STAT_TX_HOST_ERR_CHAN            (GMAC_SW_CPDMA_DMASTATUS_TX_ERR_CH | 0x10u)
#define CPDMA_STAT_RX_HOST_ERR_CHAN            (GMAC_SW_CPDMA_DMASTATUS_RX_ERR_CH | 0x08u)

/*
** Macro which can be passed as 'cfg' to the API GMAC_SW_CPDMAConfig
** The values for individual fields are also listed below.
*/
#define CPDMA_CFG(tx_rlim, rx_cef, cmd_idle, rx_offlen_blk, rx_own, tx_ptype) \
             (tx_rlim | rx_cef | cmd_idle | rx_offlen_blk | rx_own | tx_ptype)
/* Values for 'tx_rlim' */
#define CPDMA_CFG_TX_RATE_LIM_CH_7             (0x80u << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_6        (0xC0u << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_5        (0xE0u << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_4        (0xF0u << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_3        (0xF8u << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_2        (0xFCu << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_1        (0xFEu << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)
#define CPDMA_CFG_TX_RATE_LIM_CH_7_TO_0        (0xFFu << GMAC_SW_CPDMA_DMACONTROL_TX_RLIM_SHIFT)

/* Values for 'rx_cef' */
#define CPDMA_CFG_COPY_ERR_FRAMES              (GMAC_SW_CPDMA_DMACONTROL_RX_CEF)
#define CPDMA_CFG_NO_COPY_ERR_FRAMES           (0x00u)

/* Values for 'cmd_idle' */
#define CPDMA_CFG_IDLE_COMMAND                 (GMAC_SW_CPDMA_DMACONTROL_CMD_IDLE)
#define CPDMA_CFG_IDLE_COMMAND_NONE            (0x00u)

/* Values for 'rx_offlen_blk' */
#define CPDMA_CFG_BLOCK_RX_OFF_LEN_WRITE       (GMAC_SW_CPDMA_DMACONTROL_RX_OFFLEN_BLOCK)
#define CPDMA_CFG_NOT_BLOCK_RX_OFF_LEN_WRITE   (0x00u)

/* Values for 'rx_own' */
#define CPDMA_CFG_RX_OWN_1                     (GMAC_SW_CPDMA_DMACONTROL_RX_OWNERSHIP)
#define CPDMA_CFG_RX_OWN_0                     (0x00u)

/* Values for 'tx_ptype' */
#define CPDMA_CFG_TX_PRI_ROUND_ROBIN           (GMAC_SW_CPDMA_DMACONTROL_TX_PTYPE)
#define CPDMA_CFG_TX_PRI_FIXED                 (0x00u)

/*
** Macros which can be passed as 'intType' to GMAC_SW_CPDMARxIntStatRawGet
** and GMAC_SW_CPDMARxIntStatMaskedGet
*/
#define CPDMA_RX_INT_THRESH_PEND               (0x08u)
#define CPDMA_RX_INT_PULSE_PEND                (0x00u)

#define GMAC_SW_MAX_NUM_ALE_ENTRY                 (1024)
#define GMAC_SW_SIZE_CPPI_RAM                     (8192)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*
** Structure to save GMAC_SW context
*/
typedef struct cpswContext
{
    uint32_t aleBase;
    uint32_t ssBase;
    uint32_t port1Base;
    uint32_t port2Base;
    uint32_t cpdmaBase;
    uint32_t cppiRamBase;
    uint32_t wrBase;
    uint32_t sl1Base;
    uint32_t sl2Base;
    uint32_t aleCtrl;
    uint32_t alePortCtl[3];
    uint32_t aleEntry[GMAC_SW_MAX_NUM_ALE_ENTRY * 3];
    uint32_t ssStatPortEn;
    uint32_t port1SaHi;
    uint32_t port1SaLo;
    uint32_t port2SaHi;
    uint32_t port2SaLo;
    uint32_t port1TxInCtl;
    uint32_t port1Vlan;
    uint32_t port2TxInCtl;
    uint32_t port2Vlan;
    uint32_t cpdmaRxFB;
    uint32_t cpdmaTxCtl;
    uint32_t cpdmaRxCtl;
    uint32_t cpdmaRxHdp;
    uint32_t txIntMaskSet;
    uint32_t rxIntMaskSet;
    uint32_t wrCoreIntTxPulse;
    uint32_t wrCoreIntRxPulse;
    uint32_t sl1MacCtl;
    uint32_t sl2MacCtl;
    uint32_t cppiRam[GMAC_SW_SIZE_CPPI_RAM];
}
GMAC_SW_CONTEXT;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*
** Prototypes for the APIs
*/

/* SubSystem Reset */
extern void     GMAC_SW_SSReset(uint32_t baseAddr);

/* Sliver APIs */
extern void     GMAC_SW_SlReset(uint32_t baseAddr);
extern void     GMAC_SW_SlControlExtEnable(uint32_t baseAddr);
extern void     GMAC_SW_SlGigModeForceEnable(uint32_t baseAddr);
extern void     GMAC_SW_SlGigModeForceDisable(uint32_t baseAddr);
extern void     GMAC_SW_SlTransferModeSet(uint32_t baseAddr, uint32_t mode);
extern uint32_t GMAC_SW_SlMACStatusGet(uint32_t baseAddr, uint32_t statFlag);
extern void     GMAC_SW_SlRxMaxLenSet(uint32_t baseAddr, uint32_t rxMaxLen);
extern void     GMAC_SW_SlGMIIEnable(uint32_t baseAddr);
extern void     GMAC_SW_SlRGMIIEnable(uint32_t baseAddr);

/* RGMII/RMII Wrapper APIs */
extern void     GMAC_SW_WrReset(uint32_t baseAddr);
extern void     GMAC_SW_WrControlRegReset(uint32_t baseAddr);
extern void     GMAC_SW_WrCoreIntEnable(uint32_t baseAddr, uint32_t core,
                         uint32_t channel, uint32_t intFlag);
extern void     GMAC_SW_WrCoreIntDisable(uint32_t baseAddr, uint32_t core,
                          uint32_t channel, uint32_t intFlag);
extern uint32_t GMAC_SW_WrCoreIntStatusGet(uint32_t baseAddr, uint32_t core,
                                    uint32_t channel, uint32_t intFlag);
extern uint32_t GMAC_SW_WrRGMIIStatusGet(uint32_t baseAddr, uint32_t statFlag);

/* Adress Lookup Engine APIs */
extern void     GMAC_SW_ALEInit(uint32_t baseAddr);
extern void     GMAC_SW_ALEPortStateSet(uint32_t baseAddr, uint32_t portNum, uint32_t portState);
extern uint32_t GMAC_SW_ALEPortStateGet(uint32_t baseAddr, uint32_t portNum);
extern void     GMAC_SW_ALETableEntrySet(uint32_t baseAddr, uint32_t aleTblIdx,
                          uint32_t *aleEntryPtr);
extern void     GMAC_SW_ALETableEntryGet(uint32_t baseAddr, uint32_t aleTblIdx,
                          uint32_t *aleEntryPtr);
extern uint32_t GMAC_SW_ALEPrescaleGet(uint32_t baseAddr);
extern void     GMAC_SW_ALEPrescaleSet(uint32_t baseAddr, uint32_t psVal);
extern void     GMAC_SW_ALEBypassEnable(uint32_t baseAddr);
extern void     GMAC_SW_ALEBypassDisable(uint32_t baseAddr);
extern void     GMAC_SW_ALERateLimitTXMode(uint32_t baseAddr);
extern void     GMAC_SW_ALERateLimitRXMode(uint32_t baseAddr);
extern void     GMAC_SW_ALERateLimitEnable(uint32_t baseAddr);
extern void     GMAC_SW_ALERateLimitDisable(uint32_t baseAddr);
extern void     GMAC_SW_ALEAUTHModeSet(uint32_t baseAddr);
extern void     GMAC_SW_ALEAUTHModeClear(uint32_t baseAddr);
extern void     GMAC_SW_ALEUnknownUntaggedEgressSet(uint32_t baseAddr,
                                            uint32_t ueVal);
extern void     GMAC_SW_ALEUnknownRegFloodMaskSet(uint32_t baseAddr,
                                          uint32_t rfmVal);
extern void     GMAC_SW_ALEUnknownUnRegFloodMaskSet(uint32_t baseAddr,
                                            uint32_t ufmVal);
extern void     GMAC_SW_ALEUnknownMemberListSet(uint32_t baseAddr,
                                        uint32_t mlVal);
extern void     GMAC_SW_ALEBroadcastRateLimitSet(uint32_t baseAddr,
                                         uint32_t portNum,
                                         uint32_t bplVal);
extern void     GMAC_SW_ALEMulticastRateLimitSet(uint32_t baseAddr,
                                         uint32_t portNum,
                                         uint32_t mplVal);
extern void     GMAC_SW_ALEVIDIngressCheckSet(uint32_t baseAddr,
                                      uint32_t portNum);
extern void     GMAC_SW_ALEAgeOut(uint32_t baseAddr);
extern void     GMAC_SW_ALEVLANAwareSet(uint32_t baseAddr);
extern void     GMAC_SW_ALEVLANAwareClear(uint32_t baseAddr);

extern void     GMAC_SW_RxFlowControlEnable(uint32_t baseAddr, uint32_t portNum);
extern void     GMAC_SW_RxFlowControlDisable(uint32_t baseAddr, uint32_t portNum);
extern void     GMAC_SW_SoftwareIdleEnable(uint32_t baseAddr);
extern void     GMAC_SW_SoftwareIdleDisable(uint32_t baseAddr, uint32_t portNum);
extern void     GMAC_SW_VLANAwareEnable(uint32_t baseAddr);
extern void     GMAC_SW_VLANAwareDisable(uint32_t baseAddr);
extern void     GMAC_SW_PortSrcAddrSet(uint32_t baseAddr, unsigned char *ethAddr);

extern void     GMAC_SW_StatisticsEnable(uint32_t baseAddr);
extern uint32_t GMAC_SW_StatisticsGet(uint32_t baseAddr, uint32_t statReg);

/* CPDMA APIs */
extern void     GMAC_SW_CPDMAReset(uint32_t baseAddr);
extern void     GMAC_SW_CPDMACmdIdleEnable(uint32_t baseAddr);
extern void     GMAC_SW_CPDMACmdIdleDisable(uint32_t baseAddr);
extern void     GMAC_SW_CPDMATxIntEnable(uint32_t baseAddr, uint32_t channel);
extern void     GMAC_SW_CPDMARxIntEnable(uint32_t baseAddr, uint32_t channel);
extern void     GMAC_SW_CPDMATxIntDisable(uint32_t baseAddr, uint32_t channel);
extern void     GMAC_SW_CPDMARxIntDisable(uint32_t baseAddr, uint32_t channel);
extern void     GMAC_SW_CPDMATxEnable(uint32_t baseAddr);
extern void     GMAC_SW_CPDMARxEnable(uint32_t baseAddr);
extern void     GMAC_SW_CPDMATxHdrDescPtrWrite(uint32_t baseAddr, uint32_t descHdr,
                                uint32_t channel);
extern void     GMAC_SW_CPDMARxHdrDescPtrWrite(uint32_t baseAddr, uint32_t descHdr,
                                uint32_t channel);
extern void     GMAC_SW_CPDMAEndOfIntVectorWrite(uint32_t baseAddr, uint32_t eoiFlag);
extern void     GMAC_SW_CPDMATxCPWrite(uint32_t baseAddr, uint32_t channel,
                        uint32_t comPtr);
extern void     GMAC_SW_CPDMARxCPWrite(uint32_t baseAddr, uint32_t channel,
                        uint32_t comPtr);
extern void     GMAC_SW_CPDMANumFreeBufSet(uint32_t baseAddr, uint32_t channel,
                            uint32_t nBuf);
extern uint32_t GMAC_SW_CPDMAStatusGet(uint32_t baseAddr, uint32_t statFlag);
extern void     GMAC_SW_CPDMAConfig(uint32_t baseAddr, uint32_t cfg);
extern void     GMAC_SW_CPDMARxBufOffsetSet(uint32_t baseAddr, uint32_t bufOff);
extern uint32_t GMAC_SW_CPDMATxIntStatRawGet(uint32_t baseAddr,
                                      uint32_t chanMask);
extern uint32_t GMAC_SW_CPDMATxIntStatMaskedGet(uint32_t baseAddr,
                                         uint32_t chanMask);
extern uint32_t GMAC_SW_CPDMARxIntStatRawGet(uint32_t baseAddr,
                                      uint32_t chanMask,
                                      uint32_t intType);
extern uint32_t GMAC_SW_CPDMARxIntStatMaskedGet(uint32_t baseAddr,
                                         uint32_t channel,
                                         uint32_t intFlag);


extern void     GMAC_SW_ContextSave(GMAC_SW_CONTEXT *contextPtr);
extern void     GMAC_SW_ContextRestore(GMAC_SW_CONTEXT *contextPtr);
extern void     GMAC_SW_HostPortDualMacModeSet(uint32_t baseAddr);
extern void     GMAC_SW_PortVLANConfig(uint32_t baseAddr, uint32_t vlanId,
                               uint32_t cfiBit, uint32_t vlanPri);



/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __GMAC_SW_H__ */
