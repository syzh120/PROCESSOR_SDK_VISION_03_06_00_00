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
 *  \defgroup CSL_MMCSD MMCSD
 *
 *  @{
 */
 /**
 *  \file   mmcsd.h
 *
 *  \brief  HS MMC/SD APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

#ifndef HS_MMCSD_H_
#define HS_MMCSD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_mmc.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/*
* \breid Macros that can be passed to configure Standby mode
* @{
*/
#define HS_MMCSD_STANDBY_FORCE      (MMC_SYSCONFIG_STANDBYMODE_FORCE << \
                                     MMC_SYSCONFIG_STANDBYMODE_SHIFT)
#define HS_MMCSD_STANDBY_NONE       (MMC_SYSCONFIG_STANDBYMODE_NOIDLE << \
                                     MMC_SYSCONFIG_STANDBYMODE_SHIFT)
#define HS_MMCSD_STANDBY_SMART      (MMC_SYSCONFIG_STANDBYMODE_SMART << \
                                     MMC_SYSCONFIG_STANDBYMODE_SHIFT)
#define HS_MMCSD_STANDBY_SMARTWAKE  (MMC_SYSCONFIG_STANDBYMODE_SMARTWAKE << \
                                     MMC_SYSCONFIG_STANDBYMODE_SHIFT)
/* @} */

/*
* \breif Macros that can be passed to configure clock activity during wake up period
* @{
*/
#define HS_MMCSD_CLOCK_OFF          (MMC_SYSCONFIG_CLOCKACTIVITY_NONE << \
                                     MMC_SYSCONFIG_CLOCKACTIVITY_SHIFT)
#define HS_MMCSD_FCLK_OFF           (MMC_SYSCONFIG_CLOCKACTIVITY_OCP << \
                                     MMC_SYSCONFIG_CLOCKACTIVITY_SHIFT)
#define HS_MMCSD_ICLK_OFF           (MMC_SYSCONFIG_CLOCKACTIVITY_FUNC << \
                                     MMC_SYSCONFIG_CLOCKACTIVITY_SHIFT)
#define HS_MMCSD_CLOCK_ON           (MMC_SYSCONFIG_CLOCKACTIVITY_BOTH << \
                                     MMC_SYSCONFIG_CLOCKACTIVITY_SHIFT)
/* @} */

/*
* \breif Macros that can be passed to configure idle modes
* @{
*/
#define HS_MMCSD_SMARTIDLE_FORCE     (MMC_SYSCONFIG_SIDLEMODE_FORCE << \
                                      MMC_SYSCONFIG_SIDLEMODE_SHIFT)
#define HS_MMCSD_SMARTIDLE_NONE      (MMC_SYSCONFIG_SIDLEMODE_NOIDLE << \
                                      MMC_SYSCONFIG_SIDLEMODE_SHIFT)
#define HS_MMCSD_SMARTIDLE_SMART     (MMC_SYSCONFIG_SIDLEMODE_SMART << \
                                      MMC_SYSCONFIG_SIDLEMODE_SHIFT)
#define HS_MMCSD_SMARTIDLE_SMARTWAKE (MMC_SYSCONFIG_SIDLEMODE_SMARTWAKE << \
                                      MMC_SYSCONFIG_SIDLEMODE_SHIFT)
/* @} */

/*
* \breif Macros that can be passed to configure wakeup modes
* @{
*/
#define HS_MMCSD_WAKEUP_ENABLE       (MMC_SYSCONFIG_ENAWAKEUP_ENABLE << \
                                      MMC_SYSCONFIG_ENAWAKEUP_SHIFT)
#define HS_MMCSD_WAKEUP_DISABLE      (MMC_SYSCONFIG_ENAWAKEUP_DISABLED << \
                                      MMC_SYSCONFIG_ENAWAKEUP_SHIFT)
/* @} */

/*
* \breif Macros that can be passed to configure auto idle modes
* @{
*/
#define HS_MMCSD_AUTOIDLE_ENABLE     (MMC_SYSCONFIG_AUTOIDLE_ON << \
                                      MMC_SYSCONFIG_AUTOIDLE_SHIFT)
#define HS_MMCSD_AUTOIDLE_DISABLE    (MMC_SYSCONFIG_AUTOIDLE_OFF << \
                                      MMC_SYSCONFIG_AUTOIDLE_SHIFT)
/* @} */

/*
* \breif Macros that can be used for SD controller DMA request configuration
* @{
*/
#define HS_MMCSD_DMAREQ_EDGETRIG    (MMC_CON_SDMA_LNE_EARLYDEASSERT << \
                                     MMC_CON_SDMA_LNE_SHIFT)
#define HS_MMCSD_DMAREQ_LVLTRIG     (MMC_CON_SDMA_LNE_LATEDEASSERT << \
                                     MMC_CON_SDMA_LNE_SHIFT)
/* @} */

/*
* \breif Macros that can be used for SD controller dual rate configuration
* @{
*/
#define HS_MMCSD_DUALRATE_ENABLE    (MMC_CON_DDR_DDRMODE << MMC_CON_DDR_SHIFT)
#define HS_MMCSD_DUALRATE_DISABLE   (MMC_CON_DDR_NORMALMODE << \
                                     MMC_CON_DDR_SHIFT)
/* @} */

/*
* \breif Macros that can be used for selecting the bus/data width
* HS_MMCSD_BUS_WIDTH 8BIT is not supported for tda3xx Platform
* @{
*/
#define HS_MMCSD_BUS_WIDTH_4BIT    (0x4U)
#define HS_MMCSD_BUS_WIDTH_8BIT    (0x8U)
#define HS_MMCSD_BUS_WIDTH_1BIT    (0x1U)
/* @} */

/*
* \breif Macros that can be used for starting/stopping a init stream
* @{
*/
#define HS_MMCSD_INIT_START         (MMC_CON_INIT_INITSTREAM << \
                                     MMC_CON_INIT_SHIFT)
#define HS_MMCSD_INIT_STOP          (MMC_CON_INIT_NOINIT << MMC_CON_INIT_SHIFT)
/* @} */

/*
* \breif Macros that can be used for setting drain type
*/
#define HS_MMCSD_OPENDRAIN          (MMC_CON_OD_OPENDRAIN << MMC_CON_OD_SHIFT)

/*
* \breif Macros that can be used for forming the MMC/SD command
* Here\n
** cmd     : SD/MMC command number enumeration
** type    : specifies suspend upon CMD52 or resume upon CMD52 or abort upon
**           CMD52/12.
** restype : no response, or response with or without busy
** rw      : direction of data transfer
* @{
*/
#define HS_MMCSD_CMD(cmd, type, restype, rw)    ((cmd) << MMC_CMD_INDX_SHIFT | \
                                                 (type) | (restype) | (rw))

#define HS_MMCSD_NO_RESPONSE            (MMC_CMD_RSP_TYPE_NORSP << \
                                         MMC_CMD_RSP_TYPE_SHIFT)
#define HS_MMCSD_136BITS_RESPONSE       (MMC_CMD_RSP_TYPE_LGHT36 << \
                                         MMC_CMD_RSP_TYPE_SHIFT)
#define HS_MMCSD_48BITS_RESPONSE        (MMC_CMD_RSP_TYPE_LGHT48 << \
                                         MMC_CMD_RSP_TYPE_SHIFT)
#define HS_MMCSD_48BITS_BUSY_RESPONSE   (MMC_CMD_RSP_TYPE_LGHT48B << \
                                         MMC_CMD_RSP_TYPE_SHIFT)

#define HS_MMCSD_CMD_TYPE_NORMAL        (MMC_CMD_CMD_TYPE_NORMAL << \
                                         MMC_CMD_CMD_TYPE_SHIFT)
#define HS_MMCSD_CMD_TYPE_SUSPEND       (MMC_CMD_CMD_TYPE_SUSPEND << \
                                         MMC_CMD_CMD_TYPE_SHIFT)
#define HS_MMCSD_CMD_TYPE_FUNCSEL       (MMC_CMD_CMD_TYPE_RESUME << \
                                         MMC_CMD_CMD_TYPE_SHIFT)
#define HS_MMCSD_CMD_TYPE_ABORT         (MMC_CMD_CMD_TYPE_ABORT << \
                                         MMC_CMD_CMD_TYPE_SHIFT)

#define HS_MMCSD_CMD_DIR_READ           (MMC_CMD_DDIR_READ << \
                                         MMC_CMD_DDIR_SHIFT)
#define HS_MMCSD_CMD_DIR_WRITE          (MMC_CMD_DDIR_WRITE << \
                                         MMC_CMD_DDIR_SHIFT)
#define HS_MMCSD_CMD_DIR_DONTCARE       (MMC_CMD_DDIR_WRITE << \
                                         MMC_CMD_DDIR_SHIFT)
/* @} */

/*
* \breif Macros that can be used for checking the present state of the host controller
* @{
*/
#define HS_MMCSD_CARD_WRITEPROT        (MMC_PSTATE_WP_MASK)
#define HS_MMCSD_CARD_INSERTED         (MMC_PSTATE_CINS_MASK)
#define HS_MMCSD_CARD_STABLE           (MMC_PSTATE_CSS_MASK)
#define HS_MMCSD_BUFFER_READABLE       (MMC_PSTATE_BRE_MASK)
#define HS_MMCSD_BUFFER_WRITEABLE      (MMC_PSTATE_BWE_MASK)
#define HS_MMCSD_READ_INPROGRESS       (MMC_PSTATE_RTA_MASK)
#define HS_MMCSD_WRITE_INPROGRESS      (MMC_PSTATE_WTA_MASK)
/* @} */

/*
* \breif Macros that can be used for configuring the power and transfer parameters
* @{
*/
#define HS_MMCSD_BUS_VOLT_1P8          (MMC_HCTL_SDVS_1V8 << \
                                        MMC_HCTL_SDVS_SHIFT)
#define HS_MMCSD_BUS_VOLT_3P0          (MMC_HCTL_SDVS_3V0 << \
                                        MMC_HCTL_SDVS_SHIFT)
#define HS_MMCSD_BUS_VOLT_3P3          (MMC_HCTL_SDVS_3V3 << \
                                        MMC_HCTL_SDVS_SHIFT)
#define HS_MMCSD_BUS_POWER_ON          ((uint32_t) MMC_HCTL_SDBP_PWRON << \
                                        MMC_HCTL_SDBP_SHIFT)
#define HS_MMCSD_BUS_POWER_OFF         (MMC_HCTL_SDBP_PWROFF << \
                                        MMC_HCTL_SDBP_SHIFT)
#define HS_MMCSD_BUS_HIGHSPEED         (MMC_HCTL_HSPE_HIGHSPEED << \
                                        MMC_HCTL_HSPE_SHIFT)
#define HS_MMCSD_BUS_STDSPEED          (MMC_HCTL_HSPE_NORMALSPEED << \
                                        MMC_HCTL_HSPE_SHIFT)
/* @} */

/*
* \breif Macros that can be used for setting the clock, timeout values
* @{
*/
#define HS_MMCSD_DATA_TIMEOUT(n)        ((((n) - \
                                           13) & 0xF) << MMC_SYSCTL_DTO_SHIFT)
#define HS_MMCSD_CLK_DIVIDER(n)         (((n) & 0x3FF) << MMC_SYSCTL_CLKD_SHIFT)
#define HS_MMCSD_CARDCLOCK_ENABLE       (MMC_SYSCTL_CEN_ENABLE << \
                                         MMC_SYSCTL_CEN_SHIFT)
#define HS_MMCSD_CARDCLOCK_DISABLE      (MMC_SYSCTL_CEN_DISABLE << \
                                         MMC_SYSCTL_CEN_SHIFT)
#define HS_MMCSD_INTCLOCK_ON            ((uint32_t) MMC_SYSCTL_ICE_OSCILLATE << \
                                         MMC_SYSCTL_ICE_SHIFT)
#define HS_MMCSD_INTCLOCK_OFF           (MMC_SYSCTL_ICE_STOP << \
                                         MMC_SYSCTL_ICE_SHIFT)
/* @} */

/*
* \breif Macros that can be used for resetting controller lines
* @{
*/
#define HS_MMCSD_DATALINE_RESET         (MMC_SYSCTL_SRD_MASK)
#define HS_MMCSD_CMDLINE_RESET          (MMC_SYSCTL_SRC_MASK)
#define HS_MMCSD_ALL_RESET              (MMC_SYSCTL_SRA_MASK)
/* @} */

/*
* \breif Macros that can be used for interrupt enable/disable and status get
* operations
* @{
*/
#define HS_MMCSD_INTR_BADACCESS         (MMC_IE_BADA_ENABLE_MASK)
#define HS_MMCSD_INTR_CARDERROR         (MMC_IE_CERR_ENABLE_MASK)
#define HS_MMCSD_INTR_ADMAERROR         (MMC_IE_ADMAE_ENABLE_MASK)
#define HS_MMCSD_INTR_ACMD12ERR         (MMC_IE_ACE_ENABLE_MASK)
#define HS_MMCSD_INTR_DATABITERR        (MMC_IE_DEB_ENABLE_MASK)
#define HS_MMCSD_INTR_DATACRCERR        (MMC_IE_DCRC_ENABLE_MASK)
#define HS_MMCSD_INTR_DATATIMEOUT       (MMC_IE_DTO_ENABLE_MASK)
#define HS_MMCSD_INTR_CMDINDXERR        (MMC_IE_CIE_ENABLE_MASK)
#define HS_MMCSD_INTR_CMDBITERR         (MMC_IE_CEB_ENABLE_MASK)
#define HS_MMCSD_INTR_CMDCRCERR         (MMC_IE_CCRC_ENABLE_MASK)
#define HS_MMCSD_INTR_CMDTIMEOUT        (MMC_IE_CTO_ENABLE_MASK)
#define HS_MMCSD_INTR_CARDINS           (MMC_IE_CINS_ENABLE_MASK)
#define HS_MMCSD_INTR_BUFRDRDY          (MMC_IE_BRR_ENABLE_MASK)
#define HS_MMCSD_INTR_BUFWRRDY          (MMC_IE_BWR_ENABLE_MASK)
#define HS_MMCSD_INTR_TRNFCOMP          (MMC_IE_TC_ENABLE_MASK)
#define HS_MMCSD_INTR_CMDCOMP           (MMC_IE_CC_ENABLE_MASK)

#define HS_MMCSD_STAT_BADACCESS         (MMC_STAT_BADA_MASK)
#define HS_MMCSD_STAT_CARDERROR         (MMC_STAT_CERR_MASK)
#define HS_MMCSD_STAT_ADMAERROR         (MMC_STAT_ADMAE_MASK)
#define HS_MMCSD_STAT_ACMD12ERR         (MMC_STAT_ACE_MASK)
#define HS_MMCSD_STAT_DATABITERR        (MMC_STAT_DEB_MASK)
#define HS_MMCSD_STAT_DATACRCERR        (MMC_STAT_DCRC_MASK)
#define HS_MMCSD_STAT_ERR               (MMC_STAT_ERRI_MASK)
#define HS_MMCSD_STAT_DATATIMEOUT       (MMC_STAT_DTO_MASK)
#define HS_MMCSD_STAT_CMDINDXERR        (MMC_STAT_CIE_MASK)
#define HS_MMCSD_STAT_CMDBITERR         (MMC_STAT_CEB_MASK)
#define HS_MMCSD_STAT_CMDCRCERR         (MMC_STAT_CCRC_MASK)
#define HS_MMCSD_STAT_CMDTIMEOUT        (MMC_STAT_CTO_MASK)
#define HS_MMCSD_STAT_CARDINS           (MMC_STAT_CINS_MASK)
#define HS_MMCSD_STAT_BUFRDRDY          (MMC_STAT_BRR_MASK)
#define HS_MMCSD_STAT_BUFWRRDY          (MMC_STAT_BWR_MASK)
#define HS_MMCSD_STAT_TRNFCOMP          (MMC_STAT_TC_MASK)
#define HS_MMCSD_STAT_CMDCOMP           (MMC_STAT_CC_MASK)

#define HS_MMCSD_SIGEN_BADACCESS        (MMC_ISE_BADA_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CARDERROR        (MMC_ISE_CERR_SIGEN_MASK)
#define HS_MMCSD_SIGEN_ADMAERROR        (MMC_ISE_ADMAE_SIGEN_MASK)
#define HS_MMCSD_SIGEN_ACMD12ERR        (MMC_ISE_ACE_SIGEN_MASK)
#define HS_MMCSD_SIGEN_DATABITERR       (MMC_ISE_DEB_SIGEN_MASK)
#define HS_MMCSD_SIGEN_DATACRCERR       (MMC_ISE_DCRC_SIGEN_MASK)
#define HS_MMCSD_SIGEN_DATATIMEOUT      (MMC_ISE_DTO_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CMDINDXERR       (MMC_ISE_CIE_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CMDBITERR        (MMC_ISE_CEB_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CMDCRCERR        (MMC_ISE_CCRC_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CMDTIMEOUT       (MMC_ISE_CTO_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CARDINS          (MMC_ISE_CINS_SIGEN_MASK)
#define HS_MMCSD_SIGEN_BUFRDRDY         (MMC_ISE_BRR_SIGEN_MASK)
#define HS_MMCSD_SIGEN_BUFWRRDY         (MMC_ISE_BWR_SIGEN_MASK)
#define HS_MMCSD_SIGEN_TRNFCOMP         (MMC_ISE_TC_SIGEN_MASK)
#define HS_MMCSD_SIGEN_CMDCOMP          (MMC_ISE_CC_SIGEN_MASK)
/* @} */

/*
* \breif Macros that can be used for checking the capabilites of the controller
* @{
*/
#define HS_MMCSD_SUPPORT_VOLT_1P8       (MMC_CAPA_VS18_MASK)
#define HS_MMCSD_SUPPORT_VOLT_3P0       (MMC_CAPA_VS30_MASK)
#define HS_MMCSD_SUPPORT_VOLT_3P3       (MMC_CAPA_VS33_MASK)
#define HS_MMCSD_SUPPORT_DMA            (MMC_CAPA_DS_MASK)
#define HS_MMCSD_SUPPORT_HIGHSPEED      (MMC_CAPA_HSS_MASK)
#define HS_MMCSD_SUPPORT_BLOCKLEN       (MMC_CAPA_MBL_MASK)
/* @} */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Soft reset the MMC/SD controller
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 *
 * \return   0   on reset success
 *          -1   on reset fail
 *
 **/
int32_t HSMMCSDSoftReset(uint32_t baseAddr);

/**
 * \brief   Soft reset the MMC/SD controller lines
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   flag          reset flags indicating the lines to be reset.
 *
 * flag can take the following values \n
 * HS_MMCSD_DATALINE_RESET \n
 * HS_MMCSD_CMDLINE_RESET \n
 * HS_MMCSD_ALL_RESET \n
 *
 * \return   0   on reset success
 *          -1   on reset fail
 *
 **/
int32_t HSMMCSDLinesReset(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   Configure the MMC/SD controller standby, idle and wakeup modes
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   config        The standby, idle and wakeup modes
 *
 * flag can take the values (or a combination of the following)\n
 *     HS_MMCSD_STANDBY_xxx - Standby mode configuration \n
 *     HS_MMCSD_CLOCK_xxx - Clock mode configuration \n
 *     HS_MMCSD_SMARTIDLE_xxx - Smart IDLE mode configuration \n
 *     HS_MMCSD_WAKEUP_xxx - Wake up configuration \n
 *     HS_MMCSD_AUTOIDLE_xxx - Auto IDLE mode configuration \n
 *
 * \return  None.
 *
 **/
void HSMMCSDSystemConfig(uint32_t baseAddr, uint32_t config);

/**
 * \brief   Configure the MMC/SD bus width
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   width         SD/MMC bus width
 *
 * width can take the values \n
 *     HS_MMCSD_BUS_WIDTH_8BIT \n
 *     HS_MMCSD_BUS_WIDTH_4BIT \n
 *     HS_MMCSD_BUS_WIDTH_1BIT \n
 *
 * \return  None.
 *
 **/
void HSMMCSDBusWidthSet(uint32_t baseAddr, uint32_t width);

/**
 * \brief   Configure the MMC/SD bus voltage
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   volt          SD/MMC bus voltage
 *
 * volt can take the values \n
 *     HS_MMCSD_BUS_VOLT_1P8 \n
 *     HS_MMCSD_BUS_VOLT_3P0 \n
 *     HS_MMCSD_BUS_VOLT_3P3 \n
 *
 * \return  None.
 *
 **/
void HSMMCSDBusVoltSet(uint32_t baseAddr, uint32_t volt);

/**
 * \brief   Turn MMC/SD bus power on / off
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   pwr           power on / off setting
 *
 * pwr can take the values \n
 *     HS_MMCSD_BUS_POWER_ON \n
 *     HS_MMCSD_BUS_POWER_OFF \n
 *
 * \return  0 if the operation succeeded
 *         -1 if the operation failed
 *
 **/
int32_t HSMMCSDBusPower(uint32_t baseAddr, uint32_t pwr);

/**
 * \brief   Turn Internal clocks on / off
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   pwr           clock on / off setting
 *
 * pwr can take the values \n
 *     HS_MMCSD_INTCLOCK_ON \n
 *     HS_MMCSD_INTCLOCK_OFF \n
 *
 * \return  0 if the operation succeeded
 *         -1 if the operation failed
 *
 **/
int32_t HSMMCSDIntClock(uint32_t baseAddr, uint32_t pwr);

/**
 * \brief   Get the internal clock stable status
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   retry         retry times to poll for stable
 *
 * \note: if retry is zero the status is not polled. If it is non-zero status
 *        is polled for retry times
 *
 * \return  1 if the clock is stable
 *          0 if the clock is not stable
 *
 **/
uint32_t HSMMCSDIsIntClockStable(uint32_t baseAddr, uint32_t retry);

/**
 * \brief   Set the supported voltage list
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   volt          Supported bus voltage
 *
 * volt can take the values (or a combination of)\n
 *     HS_MMCSD_SUPPORT_VOLT_1P8 \n
 *     HS_MMCSD_SUPPORT_VOLT_3P0 \n
 *     HS_MMCSD_SUPPORT_VOLT_3P3 \n
 *
 * \return  None.
 *
 **/
void HSMMCSDSupportedVoltSet(uint32_t baseAddr, uint32_t volt);

/**
 * \brief   Check if the controller supports high speed
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 *
 * \return  0 if high speed is not supported
 *          1 if high speed is supported
 *
 **/
uint32_t HSMMCSDIsHSupported(uint32_t baseAddr);

/**
 * \brief   Set data timeout value
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   timeout       the data time out value
 *
 * Timeout value is the exponential of 2, as mentioned in the controller
 * reference manual.\n
 *
 * \note: Please use HS_MMCSD_DATA_TIMEOUT(n) for setting this value\n
 *        13 <= n <= 27
 *
 * \return  None.
 *
 **/
void HSMMCSDDataTimeoutSet(uint32_t baseAddr, uint32_t timeout);

/**
 * \brief   Set output bus frequency
 *
 * \param   baseAddr      Base Address of the MMC/SD controller Registers.
 * \param   freq_in       The input/ref frequency to the controller
 * \param   freq_out      The required output frequency on the bus
 * \param   bypass        If the reference clock is to be bypassed
 *
 * \return   0  on clock enable success
 *          -1  on clock enable fail
 *
 * \note: If the clock is set properly, the clocks are enabled to the card with
 * the return of this function
 **/
int32_t HSMMCSDBusFreqSet(uint32_t baseAddr, uint32_t freq_in,
                          uint32_t freq_out, uint32_t bypass);

/**
 * \brief   Sends INIT stream to the card
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 *
 * \return   1  If INIT command could be initiated
 *           0  If INIT command could not be completed/initiated
 *
 **/
int32_t HSMMCSDInitStreamSend(uint32_t baseAddr);

/**
 * \brief   Enables the controller events to set flags in status register
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific event required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_INTR_xxx
 *
 * \note: This function only enables the reflection of events in status
 * register. To enable events to generate a h/w interrupt request
 * \see HSMMCSDIntrEnable()
 *
 * \return   none
 *
 **/
void HSMMCSDIntrStatusEnable(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   Disables the controller events to set flags in status register
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific event required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_INTR_xxx
 *
 * \note: This function only enables the reflection of events in status
 * register. To disable events to generate a h/w interrupt request \see
 * HSMMCSDIntrEnable()
 *
 * \return   none
 *
 **/
void HSMMCSDIntrStatusDisable(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   Enables the controller events to generate a h/w interrupt request
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific event required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_SIGEN_xxx
 *
 * \return   none
 *
 **/
void HSMMCSDIntrEnable(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   Gets the status bits from the controller
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific status required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_STAT_xxx
 *
 * \return   status flags
 *
 **/
uint32_t HSMMCSDIntrStatusGet(uint32_t baseAddr, uint32_t flag);

/**
 * \brief   Clear the status bits from the controller
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers.
 * \param   flag        Specific status required;
 *
 * flag can take the following (or combination of) values \n
 * HS_MMCSD_STAT_xxx
 *
 * \return   none
 *
 **/
void HSMMCSDIntrStatusClear(uint32_t baseAddr, uint32_t flag);

/**
 * \brief    Checks if the command is complete
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    retry       retry times to poll for completion
 *
 * \return   1 if the command is complete
 *           0 if the command is not complete
 **/
uint32_t HSMMCSDIsCmdComplete(uint32_t baseAddr, uint32_t retry);

/**
 * \brief    Checks if the transfer is complete
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    retry       retry times to poll for completion
 *
 * \return   1 if the transfer is complete
 *           0 if the transfer is not complete
 **/
uint32_t HSMMCSDIsXferComplete(uint32_t baseAddr, uint32_t retry);

/**
 * \brief    Set the block length/size for data transfer
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    blklen      Command to be passed to the controller/card
 *
 * \note: blklen should be within the limits specified by the controller/card
 *
 * \return   none
 **/
void HSMMCSDBlkLenSet(uint32_t baseAddr, uint32_t blklen);

/**
 * \brief    Pass the MMC/SD command to the controller/card
 *
 * \param   baseAddr    Base Address of the MMC/SD controller Registers
 * \param   cmd         Command to be passed to the controller/card
 * \param   cmdarg      argument for the command
 * \param   data        data pointer, if it is a data command, else must be null
 * \param   nblks       data length in number of blocks (multiple of BLEN)
 * \param   dmaEn       Should dma be enabled (1) or disabled (0)
 *
 * \note: Please use HS_MMCSD_CMD(cmd, type, restype, rw) to form command
 *
 * \return   none
 **/
void HSMMCSDCommandSend(uint32_t baseAddr, uint32_t cmd,
                        uint32_t cmdarg, const void *data,
                        uint32_t nblks, uint32_t dmaEn);

/**
 * \brief    Get the command response from the conntroller
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    rsp         pointer to buffer which is to be filled with the
 *                       response
 *
 * \note: that this function shall return the values from all response
 * registers. Hence, rsp, must be a pointer to memory which can hold max
 * response length. It is the responsibility of the caller to use only the
 * required/relevant parts of the response
 *
 * \return   none
 **/
void HSMMCSDResponseGet(uint32_t baseAddr, uint32_t *rsp);

/**
 * \brief    Send the data to the card from the conntroller
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 * \param    data        pointer to buffer which is to be filled with the data
 * \param    len         length of the data
 *
 * \note: this function reads the data in chunks of 32 bits (4-byte words).
 * Hence, the len should be multiple of 4-byte words
 *
 * \return   none
 **/
void HSMMCSDDataGet(uint32_t baseAddr, uint8_t *data, uint32_t len);

/**
 * \brief    Check if the card is inserted and detected
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 *
 * \return   0  if the card is not inserted and detected
 *           1  if the card is inserted and detected
 *
 * \note: that this functional may not be available for all instances of the
 * controler. This function, is only useful of the controller has a dedicated
 * card detect pin. If not, the card detection mechanism is application
 * implementation specific
 **/
uint32_t HSMMCSDIsCardInserted(uint32_t baseAddr);

/**
 * \brief    Check if the card is write protected
 *
 * \param    baseAddr    Base Address of the MMC/SD controller Registers
 *
 * \return   0  if the card is not write protected
 *           1  if the card is write protected
 * \note: that this functional may not be available for all instances of the
 * controler. This function, is only useful of the controller has a dedicated
 * write protect detect pin. If not, the write protect detection mechanism is
 * application implementation specific
 **/
uint32_t HSMMCSDIsCardWriteProtected(uint32_t baseAddr);

#ifdef __cplusplus
}
#endif
#endif
 /** @} */
/********************************* End of file ******************************/

