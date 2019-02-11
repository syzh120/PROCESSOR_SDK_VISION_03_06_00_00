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
 *  \defgroup CSL_GPMC GPMC
 *
 *  @{
 */
/**
 *  \file  gpmc.h
 *
 *  \brief GPMC  APIs.
 *
 *   This file contains the device abstraction layer APIs for GPMC.
**/


#ifndef GPMC_H_
#define GPMC_H_

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_gpmc.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/*
* \brief Macros which can be used as 'mode' parameter to GPMCIdleModeSelect API.
* @{
*/
#define GPMC_IDLEMODE_FORCEIDLE                       (0U)
#define GPMC_IDLEMODE_NOIDLE                          (1U)
#define GPMC_IDLEMODE_SMARTIDLE                       (2U)
/* @} */

/*
* \brief Macros which can be used as 'configVal' parameter to GPMCAutoIdleConfig API.
* @{
*/
#define GPMC_AUTOIDLE_FREERUN                         (0U)
#define GPMC_AUTOIDLE_AUTORUN                         (1U)
/* @} */

/*
* \brief Macros which can be used as 'flag' parameter to GPMCIntStatusGet,
* GPMCIntStatusClear APIs.
* @{
*/
#define GPMC_FIFOEVENT_STATUS                         (0U)
#define GPMC_TERMINALCOUNT_STATUS                     (1U)
#define GPMC_WAIT0EDGEDETECTION_STATUS                (2U)
#define GPMC_WAIT1EDGEDETECTION_STATUS                (3U)
/* @} */

/*
* \brief Macros which can be used as 'flag' parameter to GPMCIntEnable, GPMCIntDisable
* APIs.
* @{
*/
#define GPMC_FIFOEVENT_INT                            (0U)
#define GPMC_TERMINALCOUNT_INT                        (1U)
#define GPMC_WAIT0EDGEDETECTION_INT                   (2U)
#define GPMC_WAIT1EDGEDETECTION_INT                   (3U)
/* @} */

/*
* \brief Macros which can be used as 'flag' parameter to GPMCTimeOutFeatureConfig API.
* @{
*/
#define GPMC_TIMEOUTFEATURE_ENABLE                    (1U)
#define GPMC_TIMEOUTFEATURE_DISABLE                   (0U)
/* @} */

/*
* \brief Macros which can be used as 'err' parameter to GPMCErrStatusGet API.
* @{
*/
#define GPMC_TIMEOUT_ERROR                            (0U)
#define GPMC_NOTSUPPMCMD_ERROR                        (1U)
#define GPMC_NOTSUPPADD_ERROR                         (2U)
/* @} */

/*
* \breif Macros which can be used as 'pin' parameter to GPMCWaitPinPolaritySelect,
* GPMCWaitPinStatusGet APIs.
* @{
*/
#define GPMC_WAIT_PIN0                                (0U)
#define GPMC_WAIT_PIN1                                (1U)
/* @} */

/*
* \breif Macros which can be used as 'polarity' parameter to GPMCWaitPinPolaritySelect
* API.
* @{
*/
#define GPMC_WAIT_PIN_POLARITY_LOW                    (0U)
#define GPMC_WAIT_PIN_POLARITY_HIGH                   (1U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to
* GPMCNANDForcePostedWriteFeatureConfig API.
* @{
*/
#define GPMC_FORCEPOSTEDWRITE_ENABLE                  (1U)
#define GPMC_FORCEPOSTEDWRITE_DISABLE                 (0U)
/* @} */

/*
* \breif Macros which can be used as 'csNum' parameter to GPMCFclkDividerSelect,
* GPMCTimeParaGranularitySelect, GPMCAddrDataMuxProtocolSelect,
* GPMCDevTypeSelect, GPMCDevSizeSelect, GPMCWaitPinSelect,
* GPMCWaitMonitoringTimeSelect, GPMCWaitPinMonitoringConfig,
* GPMCClkActivationTimeConfig, GPMCDevPageLenSet, GPMCWriteTypeSelect,
* GPMCReadTypeSelect, GPMCAccessTypeSelect, GPMCSyncWrapBurstConfig,
* GPMCCSTimingConfig, GPMCADVTimingConfig, GPMCWEAndOETimingConfig,
* GPMCRdAccessAndCycleTimeTimingConfig, GPMCCSConfig, GPMCBaseAddrSet,
* GPMCWrAccessAndWrDataOnADMUXBusTimingConfig, GPMCMaskAddrSet,
* GPMCycle2CycleAndTurnArndTimeTimingConfig, GPMCSNANDCmdWrite,
* GPMCNANDAddrWrite, GPMCNANDDataWrite, GPMCNANDDataRead, GPMCPrefetchCSSelect,
* GPMCECCCSSelect, GPMCECCBCHResultGet APIs.
* @{
*/
#define GPMC_CHIP_SELECT_0                            (0U)
#define GPMC_CHIP_SELECT_1                            (1U)
#define GPMC_CHIP_SELECT_2                            (2U)
#define GPMC_CHIP_SELECT_3                            (3U)
#define GPMC_CHIP_SELECT_4                            (4U)
#define GPMC_CHIP_SELECT_5                            (5U)
#define GPMC_CHIP_SELECT_6                            (6U)
#define GPMC_CHIP_SELECT_7                            (7U)
/* @} */

/*
* \breif Macros which can be used as 'divideVal' parameter to GPMCFclkDividerSelect
* API.
* @{
*/
#define GPMC_FCLK_DIV_BY_1                            (0U)
#define GPMC_FCLK_DIV_BY_2                            (1U)
#define GPMC_FCLK_DIV_BY_3                            (2U)
#define GPMC_FCLK_DIV_BY_4                            (3U)
/* @} */

/*
* \breif Macros which can be used as 'scaleftr' parameter to
* GPMCTimeparaGranularitySelect API.
* @{
*/
#define GPMC_TIMEPARAGRANULARITY_X1                   (0U)
#define GPMC_TIMEPARAGRANULARITY_X2                   (1U)
/* @} */

/*
* \breif Macros which can be used as 'protocol' parameter to
* GPMCAddrDataMuxProtocolSelect API.
* @{
*/
#define GPMC_MUXADDDATA_NOMUX                         (0U)
#define GPMC_MUXADDDATA_AADMUX                        (1U)
#define GPMC_MUXADDDATA_ADMUX                         (2U)
/* @} */

/*
* \breif Macros which can be used as 'devType' parameter to GPMCDevTypeSelect API.
* @{
*/
#define GPMC_DEVICETYPE_NORLIKE                       (0U)
#define GPMC_DEVICETYPE_NANDLIKE                      (2U)
/* @} */

/*
* \breif Macros which can be used as 'devSize' parameter to GPMCDevSizeSelect API.
* GPMC_DEVICESIZE_32BITS is supported only for tda3xx platform
* @{
*/
#define GPMC_DEVICESIZE_8BITS                         (0U)
#define GPMC_DEVICESIZE_16BITS                        (1U)
#define GPMC_DEVICESIZE_32BITS                        (2U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to GPMCWaitMonitoringTimeSelect
* API.
* @{
*/
#define GPMC_WAITMONITORINGTIME_WITH_VALIDDATA        (0U)
#define GPMC_WAITMONITORINGTIME_ONECLKB4_VALIDDATA    (1U)
#define GPMC_WAITMONITORINGTIME_TWOCLKB4_VALIDDATA    (2U)
/* @} */

/*
* \breif Macros which can be used as 'mode' parameter to GPMCWaitPinMonitoringConfig
* API.
* @{
*/
#define GPMC_MODE_READ                                (0U)
#define GPMC_MODE_WRITE                               (1U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to GPMCWaitMonitoringTimeConfig
* API.
* @{
*/
#define GPMC_WAITMONITORING_ENABLE                    (1U)
#define GPMC_WAITMONITORING_DISABLE                   (0U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to GPMCClkActivationTimeConfig
* API.
* @{
*/
#define GPMC_CLKACTIVATIONTIME_ATSTART                (0U)
#define GPMC_CLKACTIVATIONTIME_ONECLK_AFTR            (1U)
#define GPMC_CLKACTIVATIONTIME_TWOCLK_AFTR            (2U)
/* @} */

/*
* \breif Macros which can be used as 'pageLen' parameter to GPMCDevPageLenSet API.
* GPMC_DEV_PAGELENGTH_THIRTYTWO is supported only for tda3xx platform
* @{
*/
#define GPMC_DEV_PAGELENGTH_FOUR                      (0U)
#define GPMC_DEV_PAGELENGTH_EIGHT                     (1U)
#define GPMC_DEV_PAGELENGTH_SIXTEEN                   (2U)
#define GPMC_DEV_PAGELENGTH_THIRTYTWO                 (3U)
/* @} */

/*
* \breif Macros which can be used as 'writeType' parameter to GPMCWriteTypeSelect API.
* @{
*/
#define GPMC_WRITETYPE_ASYNC                          (0U)
#define GPMC_WRITETYPE_SYNC                           (1U)
/* @} */

/*
* \breif Macros which can be used as 'readType' parameter to GPMCReadTypeSelect API.
* @{
*/
#define GPMC_READTYPE_ASYNC                           (0U)
#define GPMC_READTYPE_SYNC                            (1U)
/* @} */

/*
* \breif Macros which can be used as 'AccessType' parameter to GPMCAccessTypeSelect
* API.
* @{
*/
#define GPMC_ACCESSTYPE_SINGLE                        (0U)
#define GPMC_ACCESSTYPE_MULTIPLE                      (1U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to GPMCSyncWrapBurstConfig API.
* @{
*/
#define GPMC_WRAPBURST_ENABLE                         (1U)
#define GPMC_WRAPBURST_DISABLE                        (0U)
/* @} */

/*
* \breif Macros which can be used as 'CSExtDelayFlag' parameter to
* GPMC_CS_TIMING_CONFIG macro
* @{
*/
#define GPMC_CS_EXTRA_DELAY                           (1U)
#define GPMC_CS_EXTRA_NODELAY                         (0U)
/* @} */

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         CS signal timing configuration.\n
 *
 * \param  CSWrOffTime    CS# de-assertion time from start cycle time for write
 *                        accesses in GPMC_FCLK cycles.
 *
 *         CSRdOffTime    CS# de-assertion time from start cycle time for read
 *                        accesses in GPMC_FCLK cycles
 *
 *         CSExtDelayFlag Flag to indicate whether to add half GPMC_FCLK delay
 *                        to CS or not.
 *                        This can take one of the following values :
 *                        GPMC_CS_EXTRA_DELAY --   CS# Timing control
 *                                                 signal is delayed of
 *                                                 half GPMC_FCLK cycle.
 *                        GPMC_CS_EXTRA_NODELAY -- CS# Timing control
 *                                                 signal is not delayed
 *
 *         CSOnTime       CS# assertion time from start cycle time in GPMC_FCLK
 *                        cycles.
 */

#define GPMC_CS_TIMING_CONFIG(CSWrOffTime, CSRdOffTime, CSExtDelayFlag, \
                              CSOnTime)                                 \
    ((uint32_t) (((CSWrOffTime) << GPMC_CONFIG2_N_CSWROFFTIME_SHIFT)    \
                 & GPMC_CONFIG2_N_CSWROFFTIME_MASK) |                   \
     (((CSRdOffTime) << GPMC_CONFIG2_N_CSRDOFFTIME_SHIFT)               \
      & GPMC_CONFIG2_N_CSRDOFFTIME_MASK) |                              \
     (((CSExtDelayFlag) << GPMC_CONFIG2_N_CSEXTRADELAY_SHIFT)           \
      & GPMC_CONFIG2_N_CSEXTRADELAY_MASK) |                             \
     (((CSOnTime) << GPMC_CONFIG2_N_CSONTIME_SHIFT)                     \
      & GPMC_CONFIG2_N_CSONTIME_MASK))


/*
* \breif Macros which can be used as 'ADVExtDelayFlag' parameter to
* GPMC_ADV_TIMING_CONFIG macro
* @{
*/
#define GPMC_ADV_EXTRA_DELAY                          (1U)
#define GPMC_ADV_EXTRA_NODELAY                        (0U)
/* @} */

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         ADV# signal timing configuration.\n
 *
 * \param  ADVAADMuxWrOffTime    ADV# de-assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         ADVAADMuxRdOffTime    ADV# de-assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         ADVWrOffTime          ADV# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time for write accesses
 *
 *         ADVRdOffTime          ADV# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time for write accesses
 *
 *         ADVExtDelayFlag       Flag to indicate whether to add half GPMC_FCLK
 *                               delay to ADV or not.
 *                               This can take one of the following values :
 *                               GPMC_ADV_EXTRA_DELAY --   ADV# Timing control
 *                                                         signal is delayed of
 *                                                         half GPMC_FCLK cycle.
 *                               GPMC_ADV_EXTRA_NODELAY -- ADV# Timing control
 *                                                         signal is not
 *                                                         delayed.
 *
 *         ADVAADMuxOnTime       ADV# assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the
 *                               AAD-Multiplexed protocol.
 *
 *         ADVOnTime             ADV# assertion time from start cycle time in
 *                               GPMC_FCLK cycles.
 */

#define GPMC_ADV_TIMING_CONFIG(ADVAADMuxWrOffTime, ADVAADMuxRdOffTime,      \
                               ADVWrOffTime, ADVRdOffTime, ADVExtDelayFlag, \
                               ADVAADMuxOnTime,                             \
                               ADVOnTime)                                   \
    ((uint32_t) (((ADVAADMuxWrOffTime) <<                                   \
                  GPMC_CONFIG3_N_ADVAADMUXWROFFTIME_SHIFT) &                \
                 GPMC_CONFIG3_N_ADVAADMUXWROFFTIME_MASK) |                  \
     (((ADVAADMuxRdOffTime) << GPMC_CONFIG3_N_ADVAADMUXRDOFFTIME_SHIFT) &   \
      GPMC_CONFIG3_N_ADVAADMUXRDOFFTIME_MASK) |                             \
     (((ADVWrOffTime) << GPMC_CONFIG3_N_ADVWROFFTIME_SHIFT) &               \
      GPMC_CONFIG3_N_ADVWROFFTIME_MASK) |                                   \
     (((ADVRdOffTime) << GPMC_CONFIG3_N_ADVRDOFFTIME_SHIFT) &               \
      GPMC_CONFIG3_N_ADVRDOFFTIME_MASK) |                                   \
     (((ADVExtDelayFlag) << GPMC_CONFIG3_N_ADVEXTRADELAY_SHIFT) &           \
      GPMC_CONFIG3_N_ADVEXTRADELAY_MASK) |                                  \
     (((ADVAADMuxOnTime) << GPMC_CONFIG3_N_ADVAADMUXONTIME_SHIFT) &         \
      GPMC_CONFIG3_N_ADVAADMUXONTIME_MASK) |                                \
     (((ADVOnTime) << GPMC_CONFIG3_N_ADVONTIME_SHIFT) &                     \
      GPMC_CONFIG3_N_ADVONTIME_MASK))

/*
* \breif Macros which can be used as 'OEExtDelayFlag' parameter to
* GPMC_WE_OE_TIMING_CONFIG macro
* @{
*/
#define GPMC_OE_EXTRA_DELAY                           (1U)
#define GPMC_OE_EXTRA_NODELAY                         (0U)
/* @} */

/*
* \breif Macros which can be used as 'WEExtDelayFlag' parameter to
* GPMC_WE_OE_TIMING_CONFIG macro
* @{
*/
#define GPMC_WE_EXTRA_DELAY                           (1U)
#define GPMC_WE_EXTRA_NODELAY                         (0U)
/* @} */

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         WE# and OE# signal timing configuration.\n
 *
 * \param  WEOffTime             WE# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 *         WEExtDelayFlag        Flag to indicate whether to add half GPMC_FCLK
 *                               delay to WE or not.
 *                               This can take one of the following values :
 *                               GPMC_WE_EXTRA_DELAY --   WE# Timing control
 *                                                        signal is delayed of
 *                                                        half GPMC_FCLK cycle.
 *                               GPMC_WE_EXTRA_NODELAY -- WE# Timing control
 *                                                        signal is not delayed
 *         WEOnTime              WE# assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 *         OEAADMuxOffTime       OE# de-assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         OEOffTime             OE# de-assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 *         OEExtDelayFlag        Flag to indicate whether to add half GPMC_FCLK
 *                               delay to OE or not.
 *                               This can take one of the following values :
 *                               GPMC_OE_EXTRA_DELAY --   OE# Timing control
 *                                                        signal is delayed of
 *                                                        half GPMC_FCLK cycle.
 *                               GPMC_OE_EXTRA_NODELAY -- OE# Timing control
 *                                                        signal is not delayed
 *
 *         OEAADMuxOnTime        OE# assertion time in GPMC_FCLK cycles for
 *                               first address phase when using the AAD-Mux
 *                               prorocol.
 *
 *         OEOnTime              OE# assertion time in GPMC_FCLK cycles from
 *                               start cycle time.
 *
 */

#define GPMC_WE_OE_TIMING_CONFIG(WEOffTime, WEExtDelayFlag, WEOnTime,           \
                                 OEAADMuxOffTime, OEOffTime, OEExtDelayFlag,    \
                                 OEAADMuxOnTime, OEOnTime)                      \
    ((uint32_t) (((WEOffTime) <<                                                \
                  GPMC_CONFIG4_N_WEOFFTIME_SHIFT) &                             \
                 GPMC_CONFIG4_N_WEOFFTIME_MASK) |                               \
     (((WEExtDelayFlag) <<                                                      \
       GPMC_CONFIG4_N_WEEXTRADELAY_SHIFT) & GPMC_CONFIG4_N_WEEXTRADELAY_MASK) | \
     (((WEOnTime) <<                                                            \
       GPMC_CONFIG4_N_WEONTIME_SHIFT) & GPMC_CONFIG4_N_WEONTIME_MASK) |         \
     (((OEAADMuxOffTime) <<                                                     \
       GPMC_CONFIG4_N_OEAADMUXOFFTIME_SHIFT) &                                  \
      GPMC_CONFIG4_N_OEAADMUXOFFTIME_MASK) |                                    \
     (((OEOffTime) <<                                                           \
       GPMC_CONFIG4_N_OEOFFTIME_SHIFT) & GPMC_CONFIG4_N_OEOFFTIME_MASK) |       \
     (((OEExtDelayFlag) <<                                                      \
       GPMC_CONFIG4_N_OEEXTRADELAY_SHIFT) & GPMC_CONFIG4_N_OEEXTRADELAY_MASK) | \
     (((OEAADMuxOnTime) <<                                                      \
       GPMC_CONFIG4_N_OEAADMUXONTIME_SHIFT) &                                   \
      GPMC_CONFIG4_N_OEAADMUXONTIME_MASK) |                                     \
     (((OEOnTime) <<                                                            \
       GPMC_CONFIG4_N_OEONTIME_SHIFT) & GPMC_CONFIG4_N_OEONTIME_MASK))

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         read access and cycle time timing configuration.\n
 *
 * \param  rdCycleTime           Total read cycle time in GPMC_FCLK cycles.
 *
 *         wrCycleTime           Total write cycle time in GPMC_FCLK cycles.
 *
 *         rdAccessTime          Read access time (Delay between start cycle
 *                               time and first data valid) in GPMC_FCLK cycles.
 *
 *         pageBurstAccessTime   Page burest access time (Delay between
 *                               successive words in a multiple access)in
 *                               GPMC_FCLK cycles.
 *
 */

#define GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG(rdCycleTime, wrCycleTime,         \
                                              rdAccessTime,                     \
                                              pageBurstAccessTime)              \
    ((uint32_t) (((rdCycleTime) <<                                              \
                  GPMC_CONFIG5_N_RDCYCLETIME_SHIFT) &                           \
                 GPMC_CONFIG5_N_RDCYCLETIME_MASK) |                             \
     (((wrCycleTime) <<                                                         \
       GPMC_CONFIG5_N_WRCYCLETIME_SHIFT) & GPMC_CONFIG5_N_WRCYCLETIME_MASK) |   \
     (((rdAccessTime) <<                                                        \
       GPMC_CONFIG5_N_RDACCESSTIME_SHIFT) & GPMC_CONFIG5_N_RDACCESSTIME_MASK) | \
     (((pageBurstAccessTime) <<                                                 \
       GPMC_CONFIG5_N_PAGEBURSTACCESSTIME_SHIFT) &                              \
      GPMC_CONFIG5_N_PAGEBURSTACCESSTIME_MASK))

/*
* \breif Macros which can be used as 'cycle2CycleDelaySameCSCfg' parameter to
* GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG macro
* @{
*/
#define GPMC_CYCLE2CYCLESAMECSEN_C2CDELAY             (1U)
#define GPMC_CYCLE2CYCLESAMECSEN_NOC2CDELAY           (0U)
/* @} */

/*
* \breif Macros which can be used as 'cycle2CycleDelayDiffCSCfg' parameter to
* GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG macro
* @{
*/
#define GPMC_CYCLE2CYCLEDIFFCSEN_C2CDELAY             (1U)
#define GPMC_CYCLE2CYCLEDIFFCSEN_NOC2CDELAY           (0U)
/* @} */

/*
 * \brief  This macro used to make the conf value which is used to configure the
 *         cycle to cycle and bus turn around time timing configuration.\n
 *
 * \param  cycle2CycleDelay       Cycle to cycle delay (Chip select high pulse
 *                                delay between two successive accesses)in
 *                                GPMC_FCLK cycles.
 *
 *      cycle2CycleDelaySameCSCfg Specified whether to add the cycle to cycle
 *                                delay between two successive accesses or not
 *                                (to the same chip-select).
 *                                This can take one of the following values :
 *                                GPMC_CYCLE2CYCLESAMECSEN_C2CDELAY   -- To add
 *                                                                    the delay.
 *                                GPMC_CYCLE2CYCLESAMECSEN_NOC2CDELAY -- Don't
 *                                                                add the delay.
 *
 *      cycle2CycleDelayDiffCSCfg Specified whether to add the cycle to cycle
 *                                delay between two successive accesses or not
 *                                (to the diffrent chip-select).
 *                                This can take one of the following values :
 *                                GPMC_CYCLE2CYCLEDIFFCSEN_C2CDELAY   -- To add
 *                                                                    the delay.
 *                                GPMC_CYCLE2CYCLEDIFFCSEN_NOC2CDELAY -- Don't
 *                                                                add the delay.
 *
 *         busTAtime             Bus turn aroung time between two successive
 *                               accesses to the same chip-select
 *                               (read to write) or to a diff chip-select in
 *                               GPMC_FCLK cycles.
 *
 */

#define GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG(cycle2CycleDelay,          \
                                                     cycle2CycleDelaySameCSCfg, \
                                                     cycle2CycleDelayDiffCSCfg, \
                                                     busTAtime)                 \
    ((uint32_t) (((cycle2CycleDelay) <<                                         \
                  GPMC_CONFIG6_N_CYCLE2CYCLEDELAY_SHIFT) &                      \
                 GPMC_CONFIG6_N_CYCLE2CYCLEDELAY_MASK) |                        \
     (((cycle2CycleDelaySameCSCfg) <<                                           \
       GPMC_CONFIG6_N_CYCLE2CYCLESAMECSEN_SHIFT) &                              \
      GPMC_CONFIG6_N_CYCLE2CYCLESAMECSEN_MASK) |                                \
     (((cycle2CycleDelayDiffCSCfg) <<                                           \
       GPMC_CONFIG6_N_CYCLE2CYCLEDIFFCSEN_SHIFT) &                              \
      GPMC_CONFIG6_N_CYCLE2CYCLEDIFFCSEN_MASK) |                                \
     (((busTAtime) <<                                                           \
       GPMC_CONFIG6_N_BUSTURNAROUND_SHIFT) & GPMC_CONFIG6_N_BUSTURNAROUND_MASK))

/*
* \breif Macros which can be used as 'conf' parameter to GPMCCSConfig API.
* @{
*/
#define GPMC_CS_ENABLE                                (1U)
#define GPMC_CS_DISABLE                               (0U)
/* @} */

/*
* \breif Macros which can be used as 'addrMask' parameter to GPMCSMaskAddrSet API.
* @{
*/
#define GPMC_CS_SIZE_256MB                            (0x00U)
#define GPMC_CS_SIZE_128MB                            (0x08U)
#define GPMC_CS_SIZE_64MB                             (0x0cU)
#define GPMC_CS_SIZE_32MB                             (0x0eU)
#define GPMC_CS_SIZE_16MB                             (0x0fU)
/* @} */

/*
* \breif Macros which can be used as 'accessMode' parameter to
* GPMCPREFETCHAccessModeSelect API.
* @{
*/
#define GPMC_PREFETCH_ACCESSMODE_READ                 (0U)
#define GPMC_PREFETCH_ACCESSMODE_WRITE                (1U)
/* @} */

/*
* Macros which can be used as 'syncType' parameter to
* GPMCPREFETCHSyncTypeSelect API.
* @{
*/
#define GPMC_PREFETCH_SYNCTYPE_DMA                    (1U)
#define GPMC_PREFETCH_SYNCTYPE_INT                    (0U)
/* @} */

/*
* \breif Macros which can be used as 'flag' parameter to GPMCPrefetchSyncModeConfig
* API.
* @{
*/
#define GPMC_PREFETCH_ACCESSCS_AT_START               (0U)
#define GPMC_PREFETCH_ACCESSCS_AT_STARTANDWAIT        (1U)
/* @} */

/*
* \breif Macros which can be used as 'waitPin' parameter to GPMCPrefetchWaitPinSelect
* API.
* @{
*/
#define GPMC_PREFETCH_WAITPINSELECTOR_W0              (0U)
#define GPMC_PREFETCH_WAITPINSELECTOR_W1              (1U)
/* @} */

/*
* \breif Macros which can be used as 'configVal' GPMCPrefetchAccessCycleOptConfig API.
* @{
*/
#define GPMC_PREFETCH_OPTIMIZED_ACCESS_ENABLE         (1U)
#define GPMC_PREFETCH_OPTIMIZED_ACCESS_DISABLE        (0U)
/* @} */

/*
* \breif Macros which can be used as 'configVal' parameter to
* GPMCPrefetchRRArbitrationConfig API.
* @{
*/
#define GPMC_PREFETCH_RR_ARBITRATION_ENABLE           (1U)
#define GPMC_PREFETCH_RR_ARBITRATION_DISABLE          (0U)
/* @} */

/*
* \breif Macros which can be used as 'algo' parameter to GPMCECCAlgoSelect API.
* @{
*/
#define GPMC_ECC_ALGORITHM_HAMMINGCODE                (0U)
#define GPMC_ECC_ALGORITHM_BCH                        (1U)
/* @} */

/*
* \breif Macros which can be used as 'errCorrCapVal' parameter to
* GPMCECCBCHErrCorrectionCapSelect API.
* @{
*/
#define GPMC_ECC_BCH_ERRCORRCAP_UPTO_4BITS            (0U)
#define GPMC_ECC_BCH_ERRCORRCAP_UPTO_8BITS            (1U)
#define GPMC_ECC_BCH_ERRCORRCAP_UPTO_16BITS           (2U)
/* @} */

/*
* \breif Macros which can be used as 'eccColVal' parameter to GPMCECCColumnSelect API.
* @{
*/
#define GPMC_ECC_COLUMNS_8                            (0U)
#define GPMC_ECC_COLUMNS_16                           (1U)
/* @} */

/*
* \breif Macros which can be used as 'numOfSects' parameter to
* GPMCECCBCHNumOfSectorsSelect API.
* Here 1 SECTOR = 512 bytes.
* @{
*/
#define GPMC_ECC_BCH_NUMOFSECTS_1                     (0U)
#define GPMC_ECC_BCH_NUMOFSECTS_2                     (1U)
#define GPMC_ECC_BCH_NUMOFSECTS_3                     (2U)
#define GPMC_ECC_BCH_NUMOFSECTS_4                     (3U)
#define GPMC_ECC_BCH_NUMOFSECTS_5                     (4U)
#define GPMC_ECC_BCH_NUMOFSECTS_6                     (5U)
#define GPMC_ECC_BCH_NUMOFSECTS_7                     (6U)
#define GPMC_ECC_BCH_NUMOFSECTS_8                     (7U)
/* @} */

/*
* \breif Macros which can be used as 'eccResReg' parameter to GPMCECCResultRegSelect
* API.
* @{
*/
#define GPMC_ECCPOINTER_RESULT_1                      (1U)
#define GPMC_ECCPOINTER_RESULT_2                      (2U)
#define GPMC_ECCPOINTER_RESULT_3                      (3U)
#define GPMC_ECCPOINTER_RESULT_4                      (4U)
#define GPMC_ECCPOINTER_RESULT_5                      (5U)
#define GPMC_ECCPOINTER_RESULT_6                      (6U)
#define GPMC_ECCPOINTER_RESULT_7                      (7U)
#define GPMC_ECCPOINTER_RESULT_8                      (8U)
#define GPMC_ECCPOINTER_RESULT_9                      (9U)
/* @} */

/*
* \breif Macros which can be used as 'eccSize' parameter to GPMCECCSizeValSet API.
* @{
*/
#define GPMC_ECC_SIZE_0                               (0U)
#define GPMC_ECC_SIZE_1                               (1U)
/* @} */

/*
* \breif Macros which can be used as 'eccResReg' parameter to GPMCECCResultSizeSelect
* API.
* @{
*/
#define GPMC_ECC_RESULT_1                             (1U)
#define GPMC_ECC_RESULT_2                             (2U)
#define GPMC_ECC_RESULT_3                             (3U)
#define GPMC_ECC_RESULT_4                             (4U)
#define GPMC_ECC_RESULT_5                             (5U)
#define GPMC_ECC_RESULT_6                             (6U)
#define GPMC_ECC_RESULT_7                             (7U)
#define GPMC_ECC_RESULT_8                             (8U)
#define GPMC_ECC_RESULT_9                             (9U)
/* @} */

/*
* \breif Macros which can be used as 'resIndex' parameter to GPMCECCBCHResultGet API.
* @{
*/
#define GPMC_BCH_RESULT0                             (0U)
#define GPMC_BCH_RESULT1                             (1U)
#define GPMC_BCH_RESULT2                             (2U)
#define GPMC_BCH_RESULT3                             (3U)
#define GPMC_BCH_RESULT4                             (4U)
#define GPMC_BCH_RESULT5                             (5U)
#define GPMC_BCH_RESULT6                             (6U)
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function Enables the ECC feature.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCEnable(uint32_t baseAddr);

/**
 * \brief   This function disables the ECC feature.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCDisable(uint32_t baseAddr);

/**
 * \brief   This function resets the GPMC.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 */
extern void  GPMCModuleSoftReset(uint32_t baseAddr);

/**
 * \brief   This function clears all ECC result registers.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCResultRegClear(uint32_t baseAddr);

/**
 * \brief   This function stops the PREFETCH and POST WRITE engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchEngineStop(uint32_t baseAddr);

/**
 * \brief   This function resets the FIFO pointer to 0 in prefetch mode
 *           and 40h in postwrite mode starts the PREFETCH and POST WRITE
 *           engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchEngineStart(uint32_t baseAddr);

/**
 * \brief   This function returns the address of illegal access when an error
 *          occures.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  illegalAddrVal Address of illegal access. \n
 *
 */
extern uint32_t  GPMCErrAddrGet(uint32_t baseAddr);

/**
 * \brief   This function enables the PREFETCH POSTWRITE engine. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchEngineEnable(uint32_t baseAddr);

/**
 * \brief   This function reads the IP revision code of GPMC.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  ipRev          IP revision code of GPMC.\n
 */
extern uint32_t  GPMCRevisionGet(uint32_t baseAddr);

/**
 * \brief   This function disable the PREFETCH POSTWRITE engine. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchEngineDisable(uint32_t baseAddr);

/**
 * \brief   This function returns the System Command of the transaction
 *          that caused the error.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  errCmd         System Command that caused the error. \n
 *
 */
extern uint32_t  GPMCErrSysCmdGet(uint32_t baseAddr);

/**
 * \brief   This function read the data to BCH_SWDATA register. This is used
 *          to directly padd data to the BCH ECC calculator without accessing
 *          the actual NAND flash interface.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  None.\n
 *
 */
extern uint32_t GPMCECCBCHSWDataRead(uint32_t baseAddr);
/**
 * \brief   This function returns the status of error validity.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  ErrValstatus   Error validity status. \n
 *                         0 : Error fields are no longer valid.\n
 *                         1 : Error detected and logged in the
 *                             other error fields.\n
 *
 */
extern uint32_t  GPMCErrValStatusGet(uint32_t baseAddr);

/**
 * \brief   This function enables the interrupts.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag for which interrupt has to enable.
 *                         This can take one of the following values :\n
 *                         GPMC_FIFOEVENT_INT          : For FIFOEvent
 *                                                       interrupt.\n
 *                         GPMC_TERMINALCOUNT_INT      : For TerminalCountEvent
 *                                                       interrupt.\n
 *                         GPMC_WAIT0EDGEDETECTION_INT : For Wait1 Edge
 *                                                       Detection interrupt.\n
 *                         GPMC_WAIT1EDGEDETECTION_INT : For Wait1 Edge
 *                                                       Detection interrupt.\n
 *
 *
 * \return  None. \n
 *
 */
extern void  GPMCIntEnable(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   This function gets the software resets status of GPMC.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  status         Reset status : \n
 *                            0 : Module reset is on-going.\n
 *                            1 : Module reset is completed.\n
 */
extern uint32_t  GPMCModuleResetStatusGet(uint32_t baseAddr);

/**
 * \brief   This function disable/masks the interrupts.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag for which interrupt has to mask.\n
 *                         This can take one of the following values :\n
 *                         GPMC_FIFOEVENT_INT          : For FIFOEvent
 *                                                       interrupt.\n
 *                         GPMC_TERMINALCOUNT_INT      : For TerminalCountEvent
 *                                                       interrupt.\n
 *                         GPMC_WAIT0EDGEDETECTION_INT : For Wait1 Edge
 *                                                       Detection interrupt.\n
 *                         GPMC_WAIT1EDGEDETECTION_INT : For Wait1 Edge
 *                                                       Detection interrupt. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCIntDisable(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   This function selects the Chip-select where ECC is computed.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select. \n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCCSSelect(uint32_t baseAddr, uint32_t csNum);

/**
 * \brief   This function gets the status of PREFETCH and POST WRITE engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  status         Prefetch engine status\n
 *                            0 : If engine is stopped.\n
 *                            1 : If engine is running.\n
 *
 */
extern uint32_t  GPMCPrefetchEngineStatusGet(uint32_t baseAddr);

/**
 * \brief   This function gets the number of remaining bytes to be read or to be
 *          written by the engine according to the TransferCount value.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  count value.\n
 *
 */
extern uint32_t  GPMCPrefetchCountValGet(uint32_t baseAddr);

/**
 * \brief   This function gets the PREFETCH engine FIFO threshold status. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  stauts         Threshold status.\n
 *                            1 : FIFO Pointer is greater than FIFO Threshold.\n
 *                            0 : FIFO Pointer is smaller or equal to FIFO
 *                                Threshold.\n
 *
 */
extern uint32_t  GPMCPrefetchFifoThrldStatusGet(uint32_t baseAddr);

/**
 * \brief   This function gets the FIFO pointer value of PREFETCH engine.
 *          FIFO pointer value indicates number of bytes available to be read
 *          or number of free empty place to write.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  FIFO pointer value.\n
 *
 */
extern uint32_t GPMCPrefetchFifoPtrValGet(uint32_t baseAddr);

/**
 * \brief   This function selects the ECC algorithm to use for ECC error
 *          detection and correction.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   algo        ECC algorithm to use.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_ALGORITHM_HAMMINGCODE -- For Hamming code.\n
 *                         GPMC_ECC_ALGORITHM_BCH         -- For BCH.\n
 * \return  None.\n
 *
 */
extern void GPMCECCAlgoSelect(uint32_t baseAddr, uint32_t algo);

/**
 * \brief   This function clears/resets the interrupt status.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag for which interrupt status has to reset.\n
 *                         This can take one of the following values :\n
 *                         GPMC_FIFOEVENT_STATUS         : For FIFOEvent
 *                                                         interrupt status.\n
 *                         GPMC_TERMINALCOUNT_STATUS     : For
 *                                                         TerminalCountEvent
 *                                                         interrupt status.\n
 *                         GPMC_WAIT0EDGEDETECTION_STATUS: For Wait1 Edge
 *                                                         Detection interrupt
 *                                                         status.\n
 *                         GPMC_WAIT1EDGEDETECTION_STATUS: For Wait1 Edge
 *                                                         Detection interrupt
 *                                                         status.\n
 *
 * \return  None.
 *
 */
extern void  GPMCIntStatusClear(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   This function sets the idle mode for gpmc.\n
 *
 * \param   baseAddr       Memory address of gpmc.\n
 *
 * \param   mode           Idle mode.\n
 *                         This can take one of the following values :\n
 *                         GPMC_IDLEMODE_FORCEIDLE -- for force-idle. \n
 *                         GPMC_IDLEMODE_NOIDLE    -- for no-idle. \n
 *                         GPMC_IDLEMODE_SMARTIDLE -- for smart-idle.\n
 *
 * \return  none.\n
 */
extern void  GPMCIdleModeSelect(uint32_t baseAddr, uint32_t mode);

/**
 * \brief   This function selects the chip select(CS) where Prefetch Postwrite
 *          engine is active.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select. \n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchCSSelect(uint32_t baseAddr, uint32_t csNum);

/**
 * \brief   This function write the data to BCH_SWDATA register. This is used
 *          to directly padd data to the BCH ECC calculator without accessing
 *          the actual NAND flash interface.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   bchData        BCH data to be included in the BCH calculation.
 *                         Only bits 0 to 7 are taken into account, if
 *                         the calculator is configured to use 8 bits data
 *                         using GPMCECCColumnSelect function.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCBCHSWDataWrite(uint32_t baseAddr, uint32_t bchData);

/**
 * \brief   This function returns whether passed error is occured or not.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   err            Type of the error.\n
 *                         This can take one of the following values :\n
 *                         GPMC_TIMEOUT_ERROR     -- For timeout error.\n
 *                         GPMC_NOTSUPPMCMD_ERROR -- For non-supported cmd
 *                                                   error.\n
 *                         GPMC_NOTSUPPADD_ERROR  -- For non-supported add
 *                                                   error.\n
 *
 * \return  ErrStatus \n
 *
 *                         1 : If passed argument type of error occured.\n
 *                         0 : If passed argument type of error doesn't
 *                             occured.\n
 *
 */
extern uint32_t  GPMCErrStatusGet(uint32_t baseAddr, uint32_t err);

/**
 * \brief   This function configs the internal OCP clock gating strategy.\n
 *
 * \param   baseAddr       Memory address of gpmc.\n
 *
 * \param   configVal      Config value.\n
 *                         This can take one of the following values :\n
 *                         GPMC_AUTOIDLE_FREERUN -- When Interface clock is
 *                                                  free-running. \n
 *                         GPMC_AUTOIDLE_AUTORUN -- When Automatic Interface clk
 *                                                  gating strategy is
 *                                                  applied.\n
 *
 * \return  none.\n
 */
extern void  GPMCAutoIdleConfig(uint32_t baseAddr, uint32_t configVal);

/**
 * \brief   This function selects number of columns to use for ECC
 *          calculation.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   eccColVal      ECC column value.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_COLUMNS_8   -- ECC calculated on 8
 *                         columns.\n
 *                         GPMC_ECC_COLUMNS_16  -- ECC calculated on 16
 *                         columns.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCColumnSelect(uint32_t baseAddr, uint32_t eccColVal);

/**
 * \brief   This function gets Interrupt status of interrupt passed.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag for which interrupt status has to get.\n
 *                         This can take one of the following values :\n
 *                         GPMC_FIFOEVENT_STATUS         : For FIFOEvent
 *                                                         interrupt status.\n
 *                         GPMC_TERMINALCOUNT_STATUS     : For
 *                                                         TerminalCountEvent
 *                                                         interrupt status.\n
 *                         GPMC_WAIT0EDGEDETECTION_STATUS: For Wait1 Edge
 *                                                         Detection interrupt
 *                                                         status.\n
 *                         GPMC_WAIT1EDGEDETECTION_STATUS: For Wait1 Edge
 *                                                         Detection interrupt
 *                                                         status.\n
 *
 *
 * \return  intSts         Interrupt Status. Return value meaning depends on the
 *                         interrupt flag passed. \n
 *                         if flag is GPMC_FIFOEVENT_STATUS, then \n
 *                            0 : Less than FIFOTHRESHOLD bytes are available in
 *                                prefetch/read mode.\n
 *                                Less than FIFOTHRESHOLD byte free spaces are
 *                                available in write-posting/write mode. \n
 *                            1 : Atleast FIFOTHRESHOLD bytes are available in
 *                                prefetch/read mode.\n
 *                                Atlease FIFOTHRESHOLD byte free places are
 *                                available in write-posting/write mode.\n
 *                         if flag is GPMC_TERMINALCOUNT_STATUS, then \n
 *                            0 : CountValue is greater than 0.\n
 *                            1 : CountValue is equal to 0.\n
 *                         if flag is GPMC_WAIT0EDGEDETECTION_STATUS, then \n
 *                            0 : A transition on WAIT0 input pin has not been
 *                                detected.\n
 *                            1 : A transition on WAIT0 input pin has been
 *                                detected.\n
 *                         if flag is GPMC_WAIT1EDGEDETECTION_STATUS, then \n
 *                            0 : A transition on WAIT1 input pin has not been
 *                                detected.\n
 *                            1 : A transition on WAIT1 input pin has been
 *                                detected.\n
 *
 */
extern uint32_t  GPMCIntStatusGet(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   This function configures the timeout feature.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag to indicate whether to enable or disable the
 *                         feature.\n
 *                         This can take one of the following values :\n
 *                         GPMC_TIMEOUTFEATURE_ENABLE  - To enable the timout
 *                                                       feature.\n
 *                         GPMC_TIMEOUTFEATURE_DISABLE - To disable the timout
 *                                                       feature.\n
 * \return  None. \n
 *
 */
extern void  GPMCTimeOutFeatureConfig(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   This function congigs when the PREFETCH engine has to start the
 *          access to CS.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag to specify when PREFETCH engine has to start
 *                         the access to CS.\n
 *                         This can take one of the following values :\n
 *                         GPMC_PREFETCH_ACCESSCS_AT_START       --  To start
 *                                                                   the
 *                                                                   access as
 *                                                                   soon as
 *                                                                   STARTENGINE
 *                                                                   is set.\n
 *                         GPMC_PREFETCH_ACCESSCS_AT_STARTANDWAIT -- To start
 *                                                                   the
 *                                                                   access as
 *                                                                   soon as
 *                                                                   STARTENGINE
 *                                                                   is set and
 *                                                                   non wait
 *                                                                   edge
 *                                                                   detection
 *                                                                   on the
 *                                                                   selected
 *                                                                   wait pin.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchSyncModeConfig(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   This function selects the ECC result register where the first
 *          ECC computation will be stored.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   eccResReg      ECC result register.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECCPOINTER_RESULT_1 -- ECC pointer for result 1
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_2 -- ECC pointer for result 2
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_3 -- ECC pointer for result 3
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_4 -- ECC pointer for result 4
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_5 -- ECC pointer for result 5
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_6 -- ECC pointer for result 6
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_7 -- ECC pointer for result 7
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_8 -- ECC pointer for result 8
 *                                                     register.\n
 *                         GPMC_ECCPOINTER_RESULT_9 -- ECC pointer for result 9
 *                                                     register.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCResultRegSelect(uint32_t baseAddr,
                                   uint32_t eccResReg);

/**
 * \brief   This function gets the ECC result from the ECC register.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   eccResReg      ECC result register for from which ECC value has to
 *                         retrive.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_RESULT_0 -- For ECC result 0 register.\n
 *                         GPMC_ECC_RESULT_1 -- For ECC result 1 register.\n
 *                         GPMC_ECC_RESULT_2 -- For ECC result 2 register.\n
 *                         GPMC_ECC_RESULT_3 -- For ECC result 3 register.\n
 *                         GPMC_ECC_RESULT_4 -- For ECC result 4 register.\n
 *                         GPMC_ECC_RESULT_5 -- For ECC result 5 register.\n
 *                         GPMC_ECC_RESULT_6 -- For ECC result 6 register.\n
 *                         GPMC_ECC_RESULT_7 -- For ECC result 7 register.\n
 *                         GPMC_ECC_RESULT_8 -- For ECC result 8 register.\n
 *
 * \return  ECC result.\n
 *
 */
extern uint32_t GPMCECCResultGet(uint32_t baseAddr,
                                 uint32_t eccResReg);

/**
 * \brief   This function selects the wait pin edge detector to start the
 *          PREFETCH engine in synchronized mode.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   waitPin        Wait pin to use for edge detector. \n
 *                         This can take one of the following values :\n
 *                         GPMC_PREFETCH_WAITPINSELECTOR_W0 -- To Selects
 *
 *
 *
 *                                                          Wait0EdgeDetection\n
 *                         GPMC_PREFETCH_WAITPINSELECTOR_W1 -- To Selects
 *
 *
 *
 *                                                          Wait1EdgeDetection\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchWaitPinSelect(uint32_t baseAddr,
                                      uint32_t waitPin);

/**
 * \brief   This function gets the waitpin status.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   pin            Wait pin.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WAIT_PIN0   -- For WAITPIN0.\n
 *                         GPMC_WAIT_PIN1   -- For WAITPIN1.\n
 *
 * \return  pinStatus      Pin Status.\n
 *                            0 : If the status is active low.\n
 *                            1 : If the status is active high.\n
 *
 */
extern uint32_t  GPMCWaitPinStatusGet(uint32_t baseAddr,
                                      uint32_t pin);

/**
 * \brief   This function select the synchronization type to use on FIFO
 *          threshold crossing.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   syncType       Synchronization type.\n
 *                         This can take one of the following values :\n
 *                         GPMC_PREFETCH_SYNCTYPE_DMA  -- For DMA sync mode \n
 *                         GPMC_PREFETCH_SYNCTYPE_INT  -- For INTERRUPT sync
 *                                                        mode.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchSyncTypeSelect(uint32_t baseAddr,
                                       uint32_t syncType);

/**
 * \brief   This function sets the start timeout value(TIMEOUTSTARTVALUE)
 *          of the timeout counter.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   timeoutVal     Timeout start Value in GPMC_FCLK cycles.\n
 *
 * \return  None. \n
 *
 */
extern void  GPMCTimeOutStartValSet(uint32_t baseAddr,
                                    uint32_t timeoutVal);

/**
 * \brief   This function sets the number of GPMC_FCLK cycles to be substracted
 *          from RdCycleTime,WrCycleTime, AccessTime, CSRdOffTime, CSWrOffTime,
 *          ADVRdOffTime,ADVWrOffTime, OEOffTime, WEOffTime for PREFETCH
 *          engine cycle optimization. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   cleOptVal      Cycle optimization value. This can take value from
 *                         0 to 7.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchCycleOptValSet(uint32_t baseAddr,
                                       uint32_t cleOptVal);

/**
 * \brief   This function sets the wrap mode(Spare area organization definition)
 *          for the ECC BCH algorithm.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   wrapModeVal    Wrap mode value. Value can range from 0x00 to 0x0F.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCBCHWrapModeValSet(uint32_t baseAddr,
                                     uint32_t wrapModeVal);

/**
 * \brief   This function sets the transfer count (number of bytes to be read or
 *          written by the engine to the selected CS) for the PREFETCH engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   trnsCntVal     Tranfer count value. Value can range from 0 to 2000h
 *                         i.e 8 KB.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchTrnsCntValSet(uint32_t baseAddr,
                                      uint32_t trnsCntVal);

/**
 * \brief   This function configs the PREFETCH and POSTWRITE ROUND
 *          ROBIN arbitration. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   configVal      Round Robin arbitration config value.\n
 *                         This can take one of the following values :\n
 *                         GPMC_PREFETCH_RR_ARBITRATION_ENABLE   -- To enable
 *                                                                  the Round
 *                                                                  robin
 *
 *                                                                 arbitration\n
 *                         GPMC_PREFETCH_RR_ARBITRATION_DISABLE  -- To disable
 *                                                                  the Round
 *                                                                  robin
 *
 *                                                                 arbitration\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchRRArbitrationConfig(uint32_t baseAddr,
                                            uint32_t configVal);

/**
 * \brief   This function sets the number of access to be granted to PREFETCH
 *          engine when ROUND ROBIN arbitration. i.e When an arbitration occurs
 *          between a direct memory access and a PFPW engine access, the direct
 *          memory access is always serviced. If the PFPWEnRoundRobin is enabled
 *          value set by this function plus one number of access is granted to
 *          the PREFETCH and WRITE POST engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   accessVal      Access value to set. \n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchWeightedPrioSet(uint32_t baseAddr,
                                        uint32_t accessVal);

/**
 * \brief   This function configs the access cycle optimization for PREFETCH
 *          engine. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   configVal      access cycle optimization config value.\n
 *                         This can take one of the following values :\n
 *                         GPMC_PREFETCH_OPTIMIZED_ACCESS_ENABLE  -- To enable
 *                                                                   the access
 *
 *
 *
 *                                                                optimization\n
 *                         GPMC_PREFETCH_OPTIMIZED_ACCESS_DISABLE -- To disable
 *                                                                   the access
 *
 *
 *
 *                                                                optimization\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchAccessCycleOptConfig(uint32_t baseAddr,
                                             uint32_t configVal);

/**
 * \brief   This function selects the number of sectors to process with the BCH
 *          algorithm.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   numOfSects     Number of sectors.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_BCH_NUMOFSECTS_1  -- For 1 sector (512 bytes
 *                                                       page).\n
 *                         GPMC_ECC_BCH_NUMOFSECTS_2  -- For 2 sectors. \n
 *                         GPMC_ECC_BCH_NUMOFSECTS_3  -- For 3 sectors. \n
 *                         GPMC_ECC_BCH_NUMOFSECTS_4  -- For 4 sectors. \n
 *                         GPMC_ECC_BCH_NUMOFSECTS_5  -- For 5 sectors. \n
 *                         GPMC_ECC_BCH_NUMOFSECTS_6  -- For 6 sectors. \n
 *                         GPMC_ECC_BCH_NUMOFSECTS_7  -- For 7 sectors. \n
 *                         GPMC_ECC_BCH_NUMOFSECTS_8  -- For 8 sectors
 *                                                       (4KB page).\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCBCHNumOfSectorsSelect(uint32_t baseAddr,
                                         uint32_t numOfSects);

/**
 * \brief   This function selects the access mode of the prefetch engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   accessMode     Access mode of prefetch engine.\n
 *                         This can take one of the following values :\n
 *                         GPMC_PREFETCH_ACCESSMODE_READ  -- For READ Access
 *                                                           mode.\n
 *                         GPMC_PREFETCH_ACCESSMODE_WRITE -- For WRITE Access
 *                                                            mode.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchAccessModeSelect(uint32_t baseAddr,
                                         uint32_t accessMode);

/**
 * \brief   This function sets the FIFOTHRESHOLD (maximum number of bytes read
 *          from the FIFO or written to the FIFO by the host on a DMA or
 *          interrupt request) value for the PREFETCH and POSTWRITE engine.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   fifoThrsld     FIFO threshold value. \n
 *
 * \return  None.\n
 *
 */
extern void GPMCPrefetchFifoThrldValSet(uint32_t baseAddr,
                                        uint32_t fifoThrsld);

/**
 * \brief   This function selects the Error correction capability used for BCH
 *          ECC algorithm.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   errCorrCapVal  Error correction capability value.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_BCH_ERRCORRCAP_UPTO_4BITS  -- For Up to 4
 *                                                                bits error
 *                                                                 correction.\n
 *                         GPMC_ECC_BCH_ERRCORRCAP_UPTO_8BITS  -- For Up to 8
 *                                                                 bits error
 *                                                                 correction.\n
 *                         GPMC_ECC_BCH_ERRCORRCAP_UPTO_16BITS -- For Up to 16
 *                                                                 bits error
 *                                                                 correction.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCBCHErrCorrectionCapSelect(uint32_t baseAddr,
                                             uint32_t errCorrCapVal);

/**
 * \brief   This function gets the empty write buffer status.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \return  Status         Empty buffer status.\n
 *                            0 : If the Write Buffer is not empty.\n
 *                            1 : If the Write Buffer is empty.\n
 *
 */
extern uint32_t  GPMCEmptyWriteBuffStatusGet(uint32_t baseAddr);

/**
 * \brief   This function configs the Force Posted Write feature to NAND
 *          Cmd/Add/Data location.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   flag           Flag to indicate whether to enable/disable the
 *                         Force Posted Write feature.\n
 *                         This can take one of the following values :\n
 *                         GPMC_FORCEPOSTEDWRITE_ENABLE  -- To enable the
 *                                                          feature.\n
 *                         GPMC_FORCEPOSTEDWRITE_DISABLE -- To disable
 *                                                          the feature.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCNANDForcePostedWriteFeatureConfig(uint32_t baseAddr,
                                                   uint32_t flag);

/**
 * \brief   This function sets the ECCSIZE1 value. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   eccSize        ECC size for which size has to set.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_SIZE_0 -- For ECC size 0.\n
 *                         GPMC_ECC_SIZE_1 -- For ECC size 1.\n
 *
 * \param   eccSizeVal     ECC size value.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCSizeValSet(uint32_t baseAddr, uint32_t eccSize,
                              uint32_t eccSizeVal);

/**
 * \brief   This function enables/disables the chip select. This function
 *          is called during the chip select configuration.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   conf           Flag to indicate whether to enable or disable
 *                         the Chip select.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CS_ENABLE  -- To enable the chip select.\n
 *                         GPMC_CS_DISABLE -- To disable the chip select.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCCSConfig(uint32_t baseAddr, uint32_t csNum,
                          uint32_t conf);

/**
 * \brief   This function sets the base address for the chip select spcified.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   addr           Chip Select Base address.Value can range from
 *                         0 to 0x3F\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCBaseAddrSet(uint32_t baseAddr, uint32_t csNum,
                             uint32_t addr);

/**
 * \brief   This function sets the chip select mask address or size.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param  maskaddr        Address Mask to set. \n
 *                         This can take one of the following values :\n
 *                         GPMC_CS_SIZE_256MB  -- For Chip-select size of 256
 *                         MB.\n
 *                         GPMC_CS_SIZE_128MB  -- For Chip-select size of 128
 *                         MB.\n
 *                         GPMC_CS_SIZE_64MB   -- For Chip-select size of 64
 *                         MB.\n
 *                         GPMC_CS_SIZE_32MB   -- For Chip-select size of 32
 *                         MB.\n
 *                         GPMC_CS_SIZE_16MB   -- For Chip-select size of 16
 *                         MB.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCMaskAddrSet(uint32_t baseAddr, uint32_t csNum,
                             uint32_t maskaddr);

/**
 * \brief   This function writes the NAND command to COMMAND register.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number for which NAND is interfaced.
 *                         This can take one of the following values :
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param  cmd             COMMAND to write.
 *
 * \return  None.\n
 *
 */
extern void  GPMCSNANDCmdWrite(uint32_t baseAddr, uint32_t csNum,
                               uint32_t cmd);

/**
 * \brief   This function selects the device type for the device connected to
 *          csNum.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   devType        Device Type.\n
 *                         This can take one of the following values :\n
 *                         GPMC_DEVICETYPE_NANDLIKE  -- For NAND flash like
 *                                                      devices.\n
 *                         GPMC_DEVICETYPE_NORLIKE   -- For NOR flash like
 *                                                      devices.\n
 * \return  None.\n
 *
 */
extern void  GPMCDevTypeSelect(uint32_t baseAddr, uint32_t csNum,
                               uint32_t devType);

/**
 * \brief   This function selects the device size for the device connected to
 *          csNum.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   devSize        Device Size.\n
 *                         This can take one of the following values :\n
 *                         GPMC_DEVICESIZE_8BITS   -- For 8-bit device.\n
 *                         GPMC_DEVICESIZE_16BITS  -- For 16-bit device.\n
 *                         GPMC_DEVICESIZE_32BITS  -- For 32-bit device.\n
 * \return  None.\n
 *
 */
extern void  GPMCDevSizeSelect(uint32_t baseAddr, uint32_t csNum,
                               uint32_t devSize);

/**
 * \brief   This function selects the WAIT PIN for the device connected to
 *          csNum.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   waitPin        Wait Pin.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WAIT_PIN0  -- To Select WAITPIN0.\n
 *                         GPMC_WAIT_PIN1  -- To Select WAITPIN1.\n
 * \return  None.\n
 *
 */
extern void  GPMCWaitPinSelect(uint32_t baseAddr, uint32_t csNum,
                               uint32_t waitPin);

/**
 * \brief   This function configs the timing parameters for Chip Select
 *          signal.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   conf           Configuration value for chip select timing parameters
 *                         Use the GPMC_CS_TIMING_CONFIG macro to get the value
 *                         of conf. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCCSTimingConfig(uint32_t baseAddr, uint32_t csNum,
                                uint32_t conf);

/**
 * \brief   This function writes the NAND address to ADDRESS register.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number for which NAND is interfaced.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param  addr            ADDRESS to write. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCNANDAddrWrite(uint32_t baseAddr, uint32_t csNum,
                               uint32_t addr);

/**
 * \brief   This function writes the NAND data to DATA register.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number for which NAND is interfaced.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param  data            data to write. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCNANDDataWrite(uint32_t baseAddr, uint32_t csNum,
                               uint32_t data);

/**
 * \brief   This function the data from NAND DATA register.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number for which NAND is interfaced.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \return  Read NAND data.\n
 *
 */
extern uint32_t  GPMCNANDDataRead(uint32_t baseAddr, uint32_t csNum);

/**
 * \brief   This function selects the read type.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   readType       readType for the read mode operation.\n
 *                         This can take one of the following values :\n
 *                         GPMC_READTYPE_ASYNC -- For read asynchronous.\n
 *                         GPMC_READTYPE_SYNC  -- For read synchronous.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCReadTypeSelect(uint32_t baseAddr, uint32_t csNum,
                                uint32_t readType);

/**
 * \brief   This function configs the timing parameters for ADV# signal.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   conf           Configuration value for ADV# signal timing parameters
 *                         Use the GPMC_ADV_TIMING_CONFIG macro to get the value
 *                         of conf. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCADVTimingConfig(uint32_t baseAddr, uint32_t csNum,
                                 uint32_t conf);

/**
 * \brief   This function selects the write type.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   writeType      writeType for the write mode operation.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WRITETYPE_ASYNC -- For write asynchronous.\n
 *                         GPMC_WRITETYPE_SYNC  -- For write synchronous.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCWriteTypeSelect(uint32_t baseAddr, uint32_t csNum,
                                 uint32_t writeType);

/**
 * \brief   This function sets the device page length.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   pageLen        Device Page Length.\n
 *                         This can take one of the following values :\n
 *                         GPMC_DEV_PAGELENGTH_FOUR      -- For 4 words page
 *                                                          length.\n
 *                         GPMC_DEV_PAGELENGTH_EIGHT     -- For 8 words page
 *                                                          length.\n
 *                         GPMC_DEV_PAGELENGTH_SIXTEEN   -- For 16 words page
 *                                                          length. \n
 *                         GPMC_DEV_PAGELENGTH_THIRTYTWO -- For 32 words page
 *                                                          length. \n
 * \return  None.\n
 *
 */
extern void  GPMCDevPageLenSet(uint32_t baseAddr, uint32_t csNum,
                               uint32_t pageLen);

/**
 * \brief   This function selects the FCLK DIVIDER for the chip select passed.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   divideVal      FCLK Divice value.\n
 *                         This can take one of the following values :\n
 *                         GPMC_FCLK_DIV_BY_1 -- For GPMC_CLK = (GPMC_FCLK /
 *                                               1)\n
 *                         GPMC_FCLK_DIV_BY_2 -- For GPMC_CLK = (GPMC_FCLK /
 *                                               2)\n
 *                         GPMC_FCLK_DIV_BY_3 -- For GPMC_CLK = (GPMC_FCLK /
 *                                               3)\n
 *                         GPMC_FCLK_DIV_BY_4 -- For GPMC_CLK = (GPMC_FCLK /
 *                                               4)\n
 * \return  None.\n
 *
 */
extern void  GPMCFclkDividerSelect(uint32_t baseAddr, uint32_t csNum,
                                   uint32_t divideVal);

/**
 * \brief   This function sets/selects the waitpin polarity.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   pin            Wait pin.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WAIT_PIN0   -- For WAITPIN0.\n
 *                         GPMC_WAIT_PIN1   -- For WAITPIN1.\n
 *
 * \param  polarity        Wait pin polarity.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WAIT_PIN_POLARITY_LOW  -- for active low.\n
 *                         GPMC_WAIT_PIN_POLARITY_HIGH -- for active high.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCWaitPinPolaritySelect(uint32_t baseAddr, uint32_t pin,
                                       uint32_t polarity);

/**
 * \brief   This function selects the ECC size for the ECC result register. \n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   eccResReg      ECC result register for which ECC size has to
 *                         select.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_RESULT_1 -- For ECC result 1 register.\n
 *                         GPMC_ECC_RESULT_2 -- For ECC result 2 register.\n
 *                         GPMC_ECC_RESULT_3 -- For ECC result 3 register.\n
 *                         GPMC_ECC_RESULT_4 -- For ECC result 4 register.\n
 *                         GPMC_ECC_RESULT_5 -- For ECC result 5 register.\n
 *                         GPMC_ECC_RESULT_6 -- For ECC result 6 register.\n
 *                         GPMC_ECC_RESULT_7 -- For ECC result 7 register.\n
 *                         GPMC_ECC_RESULT_8 -- For ECC result 8 register.\n
 *                         GPMC_ECC_RESULT_9 -- For ECC result 9 register.\n
 *
 * \param   eccSize        ECC size.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ECC_SIZE_0 -- For ECC size 0.\n
 *                         GPMC_ECC_SIZE_1 -- For ECC size 1.\n
 *
 * \return  None.\n
 *
 */
extern void GPMCECCResultSizeSelect(uint32_t baseAddr, uint32_t eccResReg,
                                    uint32_t eccSize);

/**
 * \brief   This function configs the timing parameters for WE# and OE#
 *          signal.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   conf           Configuration value for WE# and OE# signal timing
 *                         Parameters. Use the GPMC_WE_OE_TIMING_CONFIG macro to
 *                         get the value of conf. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCWEAndOETimingConfig(uint32_t baseAddr, uint32_t csNum,
                                     uint32_t conf);

/**
 * \brief   This function configs the wrapping burst capability.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   flag           Flag to indicate whether to enable/disable
 *                         Synchronous wrapping burst capability.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WRAPBURST_ENABLE   -- To enable the wrap burst
 *                                                     capability.\n
 *                         GPMC_WRAPBURST_DISABLE  -- To disable the wrap burst
 *                                                     capability.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCSyncWrapBurstConfig(uint32_t baseAddr, uint32_t csNum,
                                     uint32_t flag);

/**
 * \brief   This function gets the BCH result.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   resIndex       BCH ECC result index.\n
 *                         This can take one of the following values :\n
 *                         GPMC_BCH_RESULT0 -- For BCH result 0.\n
 *                         GPMC_BCH_RESULT1 -- For BCH result 1.\n
 *                         GPMC_BCH_RESULT2 -- For BCH result 2.\n
 *                         GPMC_BCH_RESULT3 -- For BCH result 3.\n
 *                         GPMC_BCH_RESULT4 -- For BCH result 4.\n
 *                         GPMC_BCH_RESULT5 -- For BCH result 5.\n
 *                         GPMC_BCH_RESULT6 -- For BCH result 6.\n
 *
 * \param   csNum          Chip Select. \n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \return  ECC result.\n
 *
 */
extern uint32_t GPMCECCBCHResultGet(uint32_t baseAddr,
                                    uint32_t resIndex,
                                    uint32_t csNum);

/**
 * \brief   This function configs the output GPMC_CLK activation time.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   flag           Flag to indicate the activation time of GPMC_CLK.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CLKACTIVATIONTIME_ATSTART     -- For First
 *                                                           rising
 *                                                           edge of GPMC_CLK at
 *                                                           start access
 *                                                           time.\n
 *                         GPMC_CLKACTIVATIONTIME_ONECLK_AFTR -- For First
 *                                                           rising
 *                                                           edge of GPMC_CLK
 *                                                           one
 *                                                           GPMC_FCLK cycle
 *                                                           aftr
 *                                                           start access
 *                                                           time.\n
 *                         GPMC_CLKACTIVATIONTIME_TWOCLK_AFTR -- For First
 *                                                           rising
 *                                                           edge of GPMC_CLK
 *                                                           two
 *                                                           GPMC_FCLK cycle
 *                                                           aftr
 *                                                           start access
 *                                                           time.\n
 * \return  None.\n
 *
 */
extern void  GPMCClkActivationTimeConfig(uint32_t baseAddr,
                                         uint32_t csNum,
                                         uint32_t flag);

/**
 * \brief   This function configs/selects the wait monitoring time for the
 *          device
 *          connected to csNum.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   flag           Flag to indicate the wait monitoring time.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WAITMONITORINGTIME_WITH_VALIDDATA  -- For wait
 *                                               pin monitoring with valid
 *                                               data.\n
 *                         GPMC_WAITMONITORINGTIME_ONECLKB4_VALIDDATA  -- For
 *                                               wait pin monitoring one
 *                                               GPMC_CLK
 *                                               before valid data. \n
 *                         GPMC_WAITMONITORINGTIME_TWOCLKB4_VALIDDATA  -- For
 *                                               wait pin monitoring two
 *                                               GPMC_CLK
 *                                               before valid data. \n
 * \return  None.\n
 *
 */
extern void  GPMCWaitMonitoringTimeSelect(uint32_t baseAddr,
                                          uint32_t csNum,
                                          uint32_t flag);

/**
 * \brief   This function selects the Address and data multiplexed protocol
 *          for the device connected to csNum.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   protocol       Protocol type.\n
 *                         This can take one of the following values :\n
 *                         GPMC_MUXADDDATA_AADMUX    -- For Address, address and
 *                                                      data(AAD) muxed
 *                                                      protocol.\n
 *                         GPMC_MUXADDDATA_NOMUX     -- For Non-muxed
 *                                                      prorocol.\n
 *                         GPMC_MUXADDDATA_ADMUX     -- For Address & Data muxed
 *                                                      protocol.\n
 * \return  None.\n
 *
 */
extern void  GPMCAddrDataMuxProtocolSelect(uint32_t baseAddr,
                                           uint32_t csNum,
                                           uint32_t protocol);

/**
 * \brief   This function selects the signals timing latencies scalar factor
 *          for the chip select.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   scaleftr       Scalar factor.\n
 *                         This can take one of the following values :\n
 *                         GPMC_TIMEPARAGRANULARITY_X1 -- For x1 latencies\n
 *                         GPMC_TIMEPARAGRANULARITY_X2 -- For x2 latencies\n
 * \return  None.\n
 *
 */
extern void  GPMCTimeParaGranularitySelect(uint32_t baseAddr,
                                           uint32_t csNum,
                                           uint32_t scaleftr);

/**
 * \brief   This function configs the RdAccessTime and CycleTime timing
 *          parameters.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   conf           Configuration value for RdAccessTime and CycleTime
 *                         timing parameters. Use the
 *                         GPMC_RDACCESS_CYCLETIME_TIMING_CONFIG macro to
 *                         get the value of conf. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCRdAccessAndCycleTimeTimingConfig(uint32_t baseAddr,
                                                  uint32_t csNum,
                                                  uint32_t conf);

/**
 * \brief   This function configs the Cycle2Cycle and BusTurnAround  timing
 *          parameters.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   conf           Configuration value for Cycle2Cycle and BusTurnAround
 *                         timing parameters. Use the
 *                         GPMC_CYCLE2CYCLE_BUSTURNAROUND_TIMING_CONFIG macro to
 *                         get the value of conf. \n
 *
 * \return  None.\n
 *
 */
extern void  GPMCycle2CycleAndTurnArndTimeTimingConfig(uint32_t baseAddr,
                                                       uint32_t csNum,
                                                       uint32_t conf);

/**
 * \brief   This function configs the access type for read and write.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   mode           Mode for which access type has to config.\n
 *                         This can take one of the following values :\n
 *                         GPMC_MODE_READ   -- To config access
 *                                             type for READ.\n
 *                         GPMC_MODE_WRITE  -- To config access
 *                                             type for WRITE.\n
 * \param   accessType     Access Type.\n
 *                         This can take one of the following values :\n
 *                         GPMC_ACCESSTYPE_SINGLE   -- For single access.\n
 *                         GPMC_ACCESSTYPE_MULTIPLE -- For multiple access.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCAccessTypeSelect(uint32_t baseAddr, uint32_t csNum,
                                  uint32_t mode, uint32_t accessType);

/**
 * \brief   This function configs the wait pin monitoring for read and write
 *          access.
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   mode           Mode for which wait monitoring has to config.\n
 *                         This can take one of the following values :\n
 *                         GPMC_MODE_READ   -- To config the  wait
 *                                              monitoring for READ.\n
 *                         GPMC_MODE_WRITE  -- To config the  wait
 *                                              monitoring for WRITE.\n
 *
 * \param   flag           Flag to indicate whether to enable/disable the wait
 *                         monitoring.\n
 *                         This can take one of the following values :\n
 *                         GPMC_WAITMONITORING_ENABLE  -- To enable the wait
 *                         monitoring.\n
 *                         GPMC_WAITMONITORING_DISABLE -- To disable the wait
 *                         monitoring.\n
 * \return  None.\n
 *
 */
extern void  GPMCWaitPinMonitoringConfig(uint32_t baseAddr, uint32_t csNum,
                                         uint32_t mode, uint32_t flag);

/**
 * \brief   This function configs the WrAccessTime, Cycle2Cycle and
 *          BusTurnAround
 *          timing parameters.\n
 *
 * \param   baseAddr       Memory address of GPMC.\n
 *
 * \param   csNum          Chip Select Number.\n
 *                         This can take one of the following values :\n
 *                         GPMC_CHIP_SELECT_0 -- For Chip Select 0.\n
 *                         GPMC_CHIP_SELECT_1 -- For Chip Select 1.\n
 *                         GPMC_CHIP_SELECT_2 -- For Chip Select 2.\n
 *                         GPMC_CHIP_SELECT_3 -- For Chip Select 3.\n
 *                         GPMC_CHIP_SELECT_4 -- For Chip Select 4.\n
 *                         GPMC_CHIP_SELECT_5 -- For Chip Select 5.\n
 *                         GPMC_CHIP_SELECT_6 -- For Chip Select 6.\n
 *                         GPMC_CHIP_SELECT_7 -- For Chip Select 7.\n
 *
 * \param   wrAccessTime   Write Access Time(Delay from StartAccessTime to the
 *                         GPMC_FCLK rising edge corresponding the GPMC_CLK
 *                         rising edge used by the attached memory for the
 *                         first data capture) in GPMC_FCLK cycles.\n
 *
 * \param   wrDataOnADmuxBus Specifies on which GPMC_FCLK rising edge the first
 *                         data of the synchronous burst write is driven in the
 *                         add/data multiplexed bus.\n
 *
 * \return  None.\n
 *
 */
extern void  GPMCWrAccessAndWrDataOnADMUXBusTimingConfig(
    uint32_t baseAddr,
    uint32_t csNum,
    uint32_t wrAccessTime,
    uint32_t
    wrDataOnADmuxBus);

#ifdef __cplusplus
}
#endif
#endif
 /** @} */
/********************************* End of file ******************************/
