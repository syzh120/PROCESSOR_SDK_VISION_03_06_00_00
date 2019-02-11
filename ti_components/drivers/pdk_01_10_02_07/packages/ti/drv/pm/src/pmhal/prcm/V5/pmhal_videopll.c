/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file      pmhal_videopll.c
 *
 *  \brief     This file contains the prototypes of the APIs present in the
 *             device abstraction layer file of videopll mode. This file has
 *             functions valid only for TDA2xx.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include "stdlib.h"
#include <ti/csl/hw_types.h>
#include "pmhal_prcm.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include <ti/csl/cslr_dss.h>
#include "hw_pmhal_videopll_data.h"
#include "pmhal_videopll.h"
#include "pm_utils.h"
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Set Register value.
 */
#define SET_REG (0x1U)

/**
 * \brief Reset Register value.
 */
#define RESET_REG (0x0U)

/**
 * \brief unit bit mask value.
 */
#define UNIT_BIT_MASK (0x00000001U)

/**
 * \brief value TO ENABLE dsi power .
 *        no clock output to the DSI PHY
 */
#define ENABLE_DSIPOWER (0x02U)

/**
 * \brief value TO DISABLE dsi power .
 */
#define DISABLE_DSIPOWER (0x00U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief This API Sets the Videopll divider value .
 *
 * \param videopllId        Unique ID of the Video Pll to be set
 *
 * \param divVaule          Divider Value to be set
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmhalVideopllSetDividerValueInternal(
    pmhalPrcmNodeId_t videopllId, uint32_t divValue);

/**
 * \brief This API verifies if multiplexer clock select is valid or not.
 *
 * \param  muxId            Unique ID of the multiplexer
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 *         PM_BADARGS       Invalid multiplexer id
 */
static int32_t PmhalIsVideoMuxClkSelValid(
    pmhalPrcmVideopllDssClkSrcMuxId_t muxId);

/**
 * \brief This API Sets the Video Pll multiplier value .
 *
 * \param videopllId        Unique ID of the Video Pll to be set
 *
 * \param mulValue                Multiplier Value to be set
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */

static int32_t PmhalVideopllSetMultiplierValueInternal(
    pmhalPrcmNodeId_t videopllId, uint32_t mulValue);

/**
 * \brief This API Gets the Video Pll divider value .
 *
 * \param videopllId        Unique ID of the Video Pll to be set
 *
 * \retval Divider value    Returns the divider value set in the videopll
 *
 */
static int32_t PmhalVideopllGetDividerValueInternal(
    pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API Sets the Video Pll multiplier value .
 *
 * \param videopllId        Unique ID of the Video Pll to be set
 *
 * \retval multiplier value    Returns the mulValue value set in the videopll
 *
 */

static int32_t PmhalVideopllGetMultiplierValueInternal(
    pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API verifies if the videopllId is valid or not.
 *
 * \param videopllId        Unique ID of the videopllId.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmhalIsVideopllIdValid(pmhalPrcmNodeId_t videopllId);

/**
 * \brief This API verifies if the MuxId is valid or not.
 *
 * \param muxId             Unique ID of the muxId.
 *
 * \retval errorStatus      Status of the API call. Can be any of the following,
 *         PM_SUCCESS       Indicates the operation is success
 *         PM_FAIL          Indicates the API failed for desired functionality
 */
static int32_t PmhalIsVideoMuxIdValid(pmhalPrcmVideopllDssClkSrcMuxId_t muxId);

/**
 * \brief This API returns the configured mux value and videopll for mux A.
 *
 * \param videopllId    Unique ID of the video pll which is configured.
 * \param postDivId     Unique ID of the post divider which is configured.
 *
 * \retval None
 */
static void PmhalDsi1AClkMuxGetParent(pmhalPrcmClockId_t *videopllId,
                                      pmhalVideopllHSD_t *postDivId);

/**
 * \brief This API returns the configured mux value and videopll for mux B.
 *
 * \param videopllId    Unique ID of the video pll which is configured.
 * \param postDivId     Unique ID of the post divider which is configured.
 *
 * \retval None
 */
static void PmhalDsi1BClkMuxGetParent(pmhalPrcmClockId_t *videopllId,
                                      pmhalVideopllHSD_t *postDivId);

/**
 * \brief This API returns the configured mux value and videopll for mux C.
 *
 * \param videopllId    Unique ID of the video pll which is configured.
 * \param postDivId     Unique ID of the post divider which is configured.
 *
 * \retval None
 */
static void PmhalDsi1CClkMuxGetParent(pmhalPrcmClockId_t *videopllId,
                                      pmhalVideopllHSD_t *postDivId);

/**
 * \brief This API converts selectId to mux Id.
 *
 * \param muxId    Select Id of the mux.
 *
 * \retval Mux Id of the given mux.
 */
static uint32_t PmhalSelectIdToMuxId (uint32_t muxId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PMHALVideopllConfigure(pmhalPrcmNodeId_t            videopllId,
                               const pmhalVideopllConfig_t *pVideopllData,
                               uint32_t                     timeOut)
{
    uint32_t timeToWait;
    int32_t  prevpllMode;
    int32_t  retVal;
    int32_t  videopllStatus;
    int32_t  videopllLockStatus;
    int32_t  mulValue, dividerValue;

    if (NULL == pVideopllData)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* Check if the Video PLL ID is valid */
        retVal = PmhalIsVideopllIdValid(videopllId);

        if (videopllId != PMHAL_PRCM_DPLL_SATA)
        {
            if (PM_SUCCESS == retVal)
            {
                /* SCP Clock must be kept runnning while programming the
                 * video PLL.
                 */
                retVal = PMHALVideopllSetSCPClk(videopllId, (uint32_t) SET_REG);
            }

            if (PM_SUCCESS == retVal)
            {
                /* Enable the PLL for which the programming is to be performed */
                retVal = PMHALVideopllSetPllProgramming(
                    videopllId,
                    (uint32_t) PMHAL_VIDEOPLL_DSS_CONTROL_ENABLE);
            }

            if (PM_SUCCESS == retVal)
            {
                /* Enable the power to On state for both the PLL and the HSDIVIDER
                 * This programs the DSI_PROTOCOL_ENGINE:DSI_CLK_CTRL:PLL_PWR_CMD
                 * field.
                 */
                retVal = PMHALVideopllSetDSIPower(videopllId,
                                                  (uint32_t) ENABLE_DSIPOWER);
            }
        }
        else
        {
            retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_OCP2SCP3,
                                        PMHAL_PRCM_MODULE_MODE_AUTO,
                                        timeOut);
            if (retVal == PM_SUCCESS)
            {
                retVal = PMHALCMModuleEnableAllOptClock(PMHAL_PRCM_MOD_SATA);
            }
        }
        if (PM_SUCCESS == retVal)
        {
            /* If there is no timeout set then the code does not wait for the
             * reset status to indicate the reset has completed. In all other
             * cases the software waits for the PLL_STATUS:PLLCTRL_RESET_DONE
             * field to become 1.
             */
            if (PM_TIMEOUT_NOWAIT != timeOut)
            {
                timeToWait = timeOut;
                if (PM_TIMEOUT_INFINITE != timeOut)
                {
                    do
                    {
                        videopllStatus = PMHALVideopllGetResetStatus(videopllId);
                        timeToWait--;
                    } while ((0 == videopllStatus) && (timeToWait != 0U));
                    if (timeToWait == 0U)
                    {
                        if (0 != videopllStatus)
                        {
                            retVal = PM_FAIL;
                        }
                    }
                }
                else
                {
                    do
                    {
                        videopllStatus =
                            PMHALVideopllGetResetStatus(videopllId);
                    } while (0 == videopllStatus);
                    retVal = PM_SUCCESS;
                }
            }
            else
            {
                videopllStatus = PMHALVideopllGetResetStatus(videopllId);
                if (0 == videopllStatus)
                {
                    retVal = PM_FAIL;
                }
                else
                {
                    retVal = PM_SUCCESS;
                }
            }
        }

        if (PM_SUCCESS == retVal)
        {
            /* Read the PLL old AUTOMODE and then program the AUTOMODE
             * to Manual Mode to go ahead and program the PLL.
             */
            prevpllMode = PMHALVideopllGetPowerMode(videopllId);
            if (prevpllMode < 0)
            {
                retVal = PM_BADARGS;
            }
            else
            {
                retVal = PMHALVideopllSetAutoPowerMode(videopllId,
                                                       (uint32_t) RESET_REG);
            }
        }
        /* Enable power for the HDMI PLL Control Module */
        if ((PM_SUCCESS == retVal) && (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI))
        {
            HW_WR_FIELD32(
                      (uint32_t) SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
                      (uint32_t) HDMI_WP_PWR_CTRL_PLL_CMD,
                      (uint32_t) HDMI_WP_PWR_CTRL_PLL_CMD_STATE_ON_ALL);
            timeToWait = timeOut;
            while (HW_RD_FIELD32(SOC_HDMI_WP_BASE + HDMI_WP_PWR_CTRL,
                   HDMI_WP_PWR_CTRL_PLL_STATUS) !=
                   HDMI_WP_PWR_CTRL_PLL_STATUS_STATE_ON_ALL)
            {
                timeToWait--;
                if (timeToWait == 0U)
                {
                    retVal = PM_FAIL;
                    break;
                }
            }
        }

        if (PM_SUCCESS == retVal)
        {
            /* Read the current M and N values to see if we are programming
             * any values different than what is already programmed. Only if the
             * values are different the API will go and reprogram the M and
             * N values.
             */
            mulValue     = PmhalVideopllGetMultiplierValueInternal(videopllId);
            dividerValue = PmhalVideopllGetDividerValueInternal(videopllId) + 1;

            if ((mulValue != pVideopllData->multiplier) &&
                (0U != pVideopllData->multiplier))
            {
                retVal = PmhalVideopllSetMultiplierValueInternal(
                    videopllId, pVideopllData->multiplier);
            }
            if ((dividerValue != pVideopllData->divider) &&
                (0U != pVideopllData->divider))
            {
                retVal = PmhalVideopllSetDividerValueInternal(
                    videopllId, pVideopllData->divider);
            }
            if ((videopllId == PMHAL_PRCM_DPLL_SATA) &&
                (PM_SUCCESS == retVal))
            {
                if (pVideopllData->divider != (uint16_t)0)
                {
                    Float32 sd_value_float = (((Float32)pVideopllData->multiplier/
                        (Float32)pVideopllData->divider) + (Float32)256)/
                        (Float32)256;
                    uint32_t sd_value =  (uint32_t)sd_value_float;
                    pmhalPrcmNodeId_t vidId = PMUtilsGetVidpllId(videopllId);
                    HW_WR_FIELD32(
                          (uint32_t) pmhalVideoElems[vidId].pllConf3RegAddr,
                          (uint32_t) PMHAL_VIDEOPLL_PLL_SD,
                          (uint32_t) sd_value);
                }
                else
                {
                    retVal = PM_BADARGS;
                }
            }
            if ((pVideopllData->maxPostDivElems != 0U) &&
                (PM_SUCCESS == retVal))
            {
                /* Once M and N values have been programmed the divider
                 * configuration is updated to the new values.
                 */
                retVal = PMHALVideopllSetPostDiv(
                    videopllId,
                    pVideopllData->postDivConfList,
                    pVideopllData->maxPostDivElems);
            }
            if ((videopllId == PMHAL_PRCM_VIDEOPLL_HDMI) &&
                (PM_SUCCESS == retVal))
            {
                /* Program the sigma delta divider */
                if (pVideopllData->divider != (uint16_t)0)
                {
                    uint32_t clkInp = PMHALCMGetSysClockFreq();
                    Float32 mul = (Float32)pVideopllData->multiplier +
                                  (((Float32)pVideopllData->fracM)/(Float32)262144);
                    Float32 dcoFreq = (Float32)clkInp * ((Float32)mul/
                        (Float32)pVideopllData->divider);
                    Float32 sd_value_float = (((Float32)dcoFreq/(Float32)1000.0) + (Float32)250)/
                        (Float32)250;
                    uint32_t sd_value =  (uint32_t)sd_value_float;
                    pmhalPrcmNodeId_t vidId = PMUtilsGetVidpllId(videopllId);
                    HW_WR_FIELD32(
                          (uint32_t) pmhalVideoElems[vidId].pllConf3RegAddr,
                          (uint32_t) HDMI_PLL_CONFIGURATION3_SD,
                          (uint32_t) sd_value);
                    if ((uint32_t)dcoFreq < 1250000U)
                    {
                        HW_WR_FIELD32(
                          (uint32_t) pmhalVideoElems[vidId].pllConf2RegAddr,
                          (uint32_t) HDMI_PLL_CONFIGURATION2_SELFREQDCO,
                          (uint32_t) 0x2);
                    }
                    else
                    {
                        HW_WR_FIELD32(
                          (uint32_t) pmhalVideoElems[vidId].pllConf2RegAddr,
                          (uint32_t) HDMI_PLL_CONFIGURATION2_SELFREQDCO,
                          (uint32_t) 0x4);
                    }
                    /* Program Frac M */
                    HW_WR_FIELD32(
                          (uint32_t) pmhalVideoElems[vidId].pllConf4RegAddr,
                          (uint32_t) HDMI_PLL_CONFIGURATION4_REGM_F,
                          (uint32_t) pVideopllData->fracM);
                }
                else
                {
                    retVal = PM_BADARGS;
                }
            }
            if (PM_SUCCESS == retVal)
            {
                /* Once the post dividers are programmed the fields of
                 * PLL_CONFIGURATION2 are programmed to their desired
                 * values.
                 */
                if (videopllId == PMHAL_PRCM_DPLL_SATA)
                {
                    uint32_t clockFreq =
                        (PMHALCMGetSysClockFreq()/pVideopllData->divider) *
                        pVideopllData->multiplier;
                    /* PLL_SELFREQDCO should be set to 0x2,
                     * if 500 MHz < CLKDCOLDO [MHz] < 1000 MHz
                     */
                    if ((clockFreq < 1000000U) && (clockFreq > 500000U))
                    {
                        pVideopllData->videopllSelectConfig->pllSelFreqDco = 0x2;
                    }
                    else
                    {
                        /* PLL_SELFREQDCO should be set to 0x4,
                         * if 1000 MHz < CLKDCOLDO [MHz] < 2000 MHz
                         */
                        pVideopllData->videopllSelectConfig->pllSelFreqDco = 0x4;
                    }
                }
                retVal = PMHALVideopllSetSelectFields(
                    videopllId,
                    pVideopllData->
                    videopllSelectConfig);
            }

            if (PM_SUCCESS == retVal)
            {
                /* Request the PLL to start the locking sequence */
                retVal = PMHALVideopllSetpllGo(
                    videopllId,
                    (uint32_t)
                    PMHAL_VIDEOPLL_PLL_GO_GO);
                /* wait for pll go */
            }
            /* Once the PLL GO bit is set wait till the PLL_GO bit is
             * is cleared before reading the lock state of the PLL.
             */
            if (PM_SUCCESS == retVal)
            {
                if (PM_TIMEOUT_NOWAIT != timeOut)
                {
                    timeToWait = timeOut;

                    if (PM_TIMEOUT_INFINITE != timeOut)
                    {
                        /* Wait till timeout is not completed. */
                        do
                        {
                            videopllLockStatus = PMHALVideopllGetpllGo(
                                videopllId);
                            timeToWait--;
                        } while ((0 != videopllLockStatus) &&
                                 (timeToWait != 0U));
                        if (timeToWait == 0U)
                        {
                            if (0 != videopllLockStatus)
                            {
                                retVal = PM_FAIL;
                            }
                        }
                    }
                    else
                    {
                        /* Wait infinitely for the PLL_GO bit to be cleared */
                        do
                        {
                            videopllLockStatus =
                                PMHALVideopllGetpllGo(videopllId);
                        } while (0 != videopllLockStatus);
                        retVal = PM_SUCCESS;
                    }
                }
                else
                {
                    /* Read once to check if the PLL_GO bit is cleared */
                    videopllLockStatus = PMHALVideopllGetpllGo(videopllId);
                }
                if (videopllLockStatus != 0)
                {
                    retVal = PM_FAIL;
                }
                else
                {
                    retVal = PM_SUCCESS;
                }
            }
            /* Read the lock status to check if the PLL is indeed locked */
            if (PM_SUCCESS == retVal)
            {
                if (PM_TIMEOUT_NOWAIT != timeOut)
                {
                    timeToWait = timeOut;
                    if (PM_TIMEOUT_INFINITE != timeOut)
                    {
                        /* Read PLL_STATUS: PLL_LOCK bit to see if the PLL is
                         * locked given the timeout.
                         */
                        do
                        {
                            videopllLockStatus = PMHALVideopllGetLockStatus(
                                videopllId);
                            timeToWait--;
                        } while ((0 == videopllLockStatus) &&
                                 (timeToWait != 0U));
                        if (timeToWait == 0U)
                        {
                            if (0 == videopllLockStatus)
                            {
                                retVal = PM_FAIL;
                            }
                            else
                            {
                                retVal = PM_SUCCESS;
                            }
                        }
                    }
                    else
                    {
                        /* Read PLL_STATUS: PLL_LOCK bit infinitely to see if
                         * the PLL is locked.
                         */
                        do
                        {
                            videopllLockStatus =
                                PMHALVideopllGetLockStatus(videopllId);
                        } while (0 == videopllLockStatus);
                        retVal = PM_SUCCESS;
                    }
                }
                else
                {
                    /* Read PLL_STATUS: PLL_LOCK bit once to see if
                     * the PLL is locked.
                     */
                    videopllLockStatus = PMHALVideopllGetLockStatus(videopllId);
                    if (videopllLockStatus != 0)
                    {
                        retVal = PM_SUCCESS;
                    }
                    else
                    {
                        retVal = PM_FAIL;
                    }
                }
            }
            /* Configure the PLL power mode fields of Idle, bypass etc. based
             * on the API input.
             */
            if (PM_SUCCESS == retVal)
            {
                retVal = PMHALVideopllSetModeFields(
                    videopllId,
                    pVideopllData->
                    videopllModeConfig);
            }
        }
    }

    return retVal;
}

int32_t PMHALVideopllConfigureMux(
    pmhalPrcmVideopllDssClkSrcMuxId_t muxId,
    pmhalPrcmVideopllMuxSelectId_t    pParentNodeId)
{
    int32_t  retVal;
    uint32_t muxParentIdx;

    retVal = PmhalIsVideoMuxIdValid(muxId);
    if (PM_SUCCESS == retVal)
    {
        retVal = PmhalIsVideoMuxClkSelValid(muxId);
        if (PM_SUCCESS == retVal)
        {
            /* Loop through the list of parents a multiplxer can have and
             * find which multiplexer parent ID matched with the current
             * parent ID input. This is used to find the actual register
             * programming to be able to configure the multiplexer selection.
             */
            retVal = PM_CM_MUX_PARENT_SELECTION_INVALID;
            for (muxParentIdx = 0U;
                 muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
                 muxParentIdx++)
            {
                if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
                    nodeMuxId == pParentNodeId)
                {
                    /* Once the Parent is found program the register with the
                     * required register field value.
                     */
                    HW_WR_FIELD32_RAW(
                        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->
                        regAddr,
                        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->
                        regMask,
                        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->
                        regShift,
                        (uint32_t) pmhalVidMuxElems[muxId].
                        pSupportedEnum[muxParentIdx].nodeEnumValue);

                    retVal = PM_SUCCESS;
                    break;
                }
            }
        }
    }
    return retVal;
}

int32_t PMHALVideopllSetSCPClk(pmhalPrcmNodeId_t videopllId, uint32_t value)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the video PLL ID is correct then enable the SCP clock to
         * start or stop running based on user input.
         */
        vidId = PMUtilsGetVidpllId(videopllId);
        HW_WR_FIELD32((uint32_t) pmhalVideoElems[vidId].pllDsiRegAddr,
                      (uint32_t) PMHAL_VIDEOPLL_SCPCLK,
                      (uint32_t) value);
    }
    return retVal;
}

int32_t PMHALVideopllSetPllProgramming(pmhalPrcmNodeId_t videopllId,
                                       uint32_t          value)
{
    int32_t           retVal;
    uint32_t          mask;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the video PLL Id is correct then enable or disable the PLL and
         * HSDIVIDERs based on the user input.
         */
        vidId = PMUtilsGetVidpllId(videopllId);
        mask  = (uint32_t) ((uint32_t) UNIT_BIT_MASK << pmhalVideoElems
                            [vidId].dssPllRegShift);
        HW_WR_FIELD32_RAW((uint32_t) (DSS_PLL_CONTROL),
                          (uint32_t) mask,
                          (uint32_t) pmhalVideoElems[vidId].dssPllRegShift,
                          (uint32_t) value);
    }
    return retVal;
}

int32_t PMHALVideopllSetDSIPower(pmhalPrcmNodeId_t videopllId, uint32_t value)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the Video PLL IS is correct then program the DSI Power command
         * register field based on the register field value provided.
         */
        vidId = PMUtilsGetVidpllId(videopllId);
        HW_WR_FIELD32((uint32_t) pmhalVideoElems[vidId].pllDsiRegAddr,
                      (uint32_t) PMHAL_VIDEOPLL_PWRCMD,
                      value);
    }
    return retVal;
}

int32_t PMHALVideopllGetResetStatus(pmhalPrcmNodeId_t videopllId)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the video PLL ID is valid read the RESET_DONE status of the PLL */
        vidId  = PMUtilsGetVidpllId(videopllId);
        retVal = (int32_t) HW_RD_FIELD32(
            pmhalVideoElems[vidId].pllStatusRegAddr,
            (uint32_t)
            PMHAL_VIDEOPLL_CTRL_RESET_DONE);
    }
    return retVal;
}

int32_t PMHALVideopllSetAutoPowerMode(pmhalPrcmNodeId_t videopllId,
                                      uint32_t          value)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the video PLL ID is valid set the auto or manual modes of the
         * PLL.
         */
        vidId = PMUtilsGetVidpllId(videopllId);
        if (pmhalVideoElems[vidId].pllControlRegAddr != PMHAL_INVALID_REGADDR)
        {
            HW_WR_FIELD32((uint32_t) pmhalVideoElems[vidId].pllControlRegAddr,
                      (uint32_t) PMHAL_VIDEOPLL_AUTOMODE,
                      (uint32_t) value);
        }
    }
    return retVal;
}

int32_t PMHALVideopllGetPowerMode(pmhalPrcmNodeId_t videopllId)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the video PLL ID is valid read the mode of the
         * PLL to see if auto or manual.
         */
        vidId  = PMUtilsGetVidpllId(videopllId);
        if (pmhalVideoElems[vidId].pllControlRegAddr != PMHAL_INVALID_REGADDR)
        {
            retVal = (int32_t) HW_RD_FIELD32((uint32_t) pmhalVideoElems[vidId].
                                         pllControlRegAddr,
                                         (uint32_t) PMHAL_VIDEOPLL_AUTOMODE);
        }
    }
    return retVal;
}

int32_t PMHALVideopllGetLockStatus(pmhalPrcmNodeId_t videopllId)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* If the video PLL ID is valid read the lock status of the
         * PLL to see if locked or unlocked.
         */
        vidId  = PMUtilsGetVidpllId(videopllId);
        retVal = (int32_t) HW_RD_FIELD32(
            pmhalVideoElems[vidId].pllStatusRegAddr,
            PMHAL_VIDEOPLL_LOCK);
    }
    return retVal;
}

int32_t PMHALVideopllGetDivider(pmhalPrcmNodeId_t videopllId)
{
    int32_t retVal;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* Read the N value of the PLL */
        retVal = PmhalVideopllGetDividerValueInternal(videopllId);
    }
    return retVal;
}

int32_t PMHALVideopllGetFracMultiplier(pmhalPrcmNodeId_t videopllId)
{
    int32_t retVal;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if ((PM_SUCCESS == retVal) && (videopllId == PMHAL_PRCM_VIDEOPLL_HDMI))
    {
        pmhalPrcmNodeId_t vidId;
        vidId = PMUtilsGetVidpllId(videopllId);
        retVal = (int32_t) HW_RD_FIELD32(
                 (uint32_t) pmhalVideoElems[vidId].pllConf4RegAddr,
                 (uint32_t) HDMI_PLL_CONFIGURATION4_REGM_F);
    }
    else
    {
        retVal = 0;
    }
    return retVal;
}

int32_t PMHALVideopllGetMultiplier(pmhalPrcmNodeId_t videopllId)
{
    int32_t retVal;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* Read the M value of the PLL */
        retVal = PmhalVideopllGetMultiplierValueInternal(videopllId);
    }
    return retVal;
}

int32_t PMHALVideopllSetDivider(pmhalPrcmNodeId_t videopllId,
                                uint32_t          divValue)
{
    int32_t retVal;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* Set the N value of the PLL */
        retVal = PmhalVideopllSetDividerValueInternal(videopllId, divValue);
    }
    return retVal;
}

int32_t PMHALVideopllSetMultiplier(pmhalPrcmNodeId_t videopllId,
                                   uint32_t          mulValue)
{
    int32_t retVal;

    retVal = PmhalIsVideopllIdValid(videopllId);
    if (PM_SUCCESS == retVal)
    {
        /* Set the M value of the PLL */
        retVal = PmhalVideopllSetMultiplierValueInternal(videopllId, mulValue);
    }
    return retVal;
}

int32_t PMHALVideopllSetPostDiv(
    pmhalPrcmNodeId_t                 videopllId,
    const pmhalPrcmPllPostDivValue_t *divConfig,
    uint32_t                          maxPostDivElems)
{
    int32_t           retVal;
    uint32_t          regAddr;
    uint32_t          divElemIdx;
    uint32_t          divConfElemIdx;
    pmhalPrcmNodeId_t vidId;

    if ((NULL == divConfig) || (0U == maxPostDivElems))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsVideopllIdValid(videopllId);
        if (PM_SUCCESS == retVal)
        {
            retVal = PM_INPUT_PARAM_BAD_POST_DIV_ID;
            vidId  = PMUtilsGetVidpllId(videopllId);
            /* Loop through all the input Post dividers given by the user */
            for (divConfElemIdx = 0U;
                 divConfElemIdx < maxPostDivElems;
                 divConfElemIdx++)
            {
                /* Compare each input post divider ID with the list of
                 * post dividers supported by the PLL of interest.
                 */
                for (divElemIdx = 0U;
                     divElemIdx < pmhalVideoElems[vidId].postDividersMax;
                     divElemIdx++)
                {
                    if (pmhalVideoElems[vidId].postDividers[divElemIdx].
                        postDivId == divConfig[divConfElemIdx].postDivId)
                    {
                        /* If the post divider ID is matching find the
                         * address of the register.
                         */
                        if (PMHAL_PRCM_DPLL_POST_DIV_M4 ==
                            divConfig[divConfElemIdx].postDivId)
                        {
                            regAddr = pmhalVideoElems[vidId].
                                      pllConf1RegAddr;
                        }
                        else if (PMHAL_PRCM_DPLL_POST_DIV_M2 ==
                            divConfig[divConfElemIdx].postDivId)
                        {
                            regAddr = pmhalVideoElems[vidId].pllConf4RegAddr;
                        }
                        else
                        {
                            regAddr = pmhalVideoElems[vidId].pllConf3RegAddr;
                        }

                        /* Program the desired post divider value */
                        if (PMHAL_PRCM_VIDEOPLL_HDMI != videopllId)
                        {
                            HW_WR_FIELD32_RAW(
                            (uint32_t) regAddr,
                            (uint32_t) pmhalVideoElems[vidId].postDividers[
                                divElemIdx].postDivBitField->regMask,
                            (uint32_t) pmhalVideoElems[vidId].postDividers[
                                divElemIdx].postDivBitField->regShift,
                            (uint32_t) (divConfig[divConfElemIdx].
                                        configValue - 1));
                        }
                        else
                        {
                            /* The hsdivider for HDMI PLL is not to be
                             * subtracted by 1.
                             */
                            HW_WR_FIELD32_RAW(
                            (uint32_t) regAddr,
                            (uint32_t) pmhalVideoElems[vidId].postDividers[
                                divElemIdx].postDivBitField->regMask,
                            (uint32_t) pmhalVideoElems[vidId].postDividers[
                                divElemIdx].postDivBitField->regShift,
                            (uint32_t) (divConfig[divConfElemIdx].
                                        configValue));
                        }
                        retVal = PM_SUCCESS;
                        break;
                    }
                }
            }
        }
    }
    return retVal;
}

int32_t PMHALVideopllGetHSDivider(pmhalPrcmNodeId_t  videopllId,
                                  pmhalVideopllHSD_t videopllHSD,
                                  uint32_t          *hsdivValue)
{
    int32_t           retVal = PM_SUCCESS;
    uint32_t          regAddr;
    uint32_t          isHSDEnabled = 0U;
    pmhalPrcmNodeId_t vidId;

    if (videopllHSD > PMHAL_VIDEOPLL_HSD_MAX)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PmhalIsVideopllIdValid(videopllId);

        if (PM_SUCCESS == retVal)
        {
            vidId = PMUtilsGetVidpllId(videopllId);
            /* For a given Video PLL find if the HSDivider is enabled or not */
            if (PMHAL_VIDEOPLL_HSD_M4 == videopllHSD)
            {
                isHSDEnabled = HW_RD_FIELD32(
                    pmhalVideoElems[vidId].pllStatusRegAddr,
                    PMHAL_VIDEOPLL_M4_CLOCK_EN_ACK);
            }
            else if (PMHAL_VIDEOPLL_HSD_M6 == videopllHSD)
            {
                isHSDEnabled = HW_RD_FIELD32(
                    pmhalVideoElems[vidId].pllStatusRegAddr,
                    PMHAL_VIDEOPLL_M6_CLOCK_EN_ACK);
            }
            else if (PMHAL_VIDEOPLL_HSD_M7 == videopllHSD)
            {
                isHSDEnabled = HW_RD_FIELD32(
                    pmhalVideoElems[vidId].pllStatusRegAddr,
                    PMHAL_VIDEOPLL_M7_CLOCK_EN_ACK);
            }
            else
            {
                /* Default to 1 for the M2 divider */
                isHSDEnabled = 1U;
            }
            /* If enabled find the address of the HSDivider and read the value
             * of the programmed HSDivider.
             */
            if (1U == isHSDEnabled)
            {
                if (PMHAL_VIDEOPLL_HSD_M4 == videopllHSD)
                {
                    regAddr = pmhalVideoElems[vidId].pllConf1RegAddr;
                }
                else if (PMHAL_VIDEOPLL_HSD_M6 == videopllHSD)
                {
                    regAddr = pmhalVideoElems[vidId].pllConf3RegAddr;
                }
                else
                {
                    regAddr = pmhalVideoElems[vidId].pllConf4RegAddr;
                }
                if (regAddr != PMHAL_INVALID_REGADDR)
                {
                    *hsdivValue = HW_RD_FIELD32_RAW(
                        (uint32_t) regAddr,
                        (uint32_t) pmhalVideoElems[vidId].postDividers
                        [videopllHSD].postDivBitField->regMask,
                        (uint32_t) pmhalVideoElems[vidId].postDividers
                        [videopllHSD].postDivBitField->regShift);
                }
            }
            else
            {
                retVal = PM_VIDEOPLL_HSDIV_NOT_ENABLED;
            }
        }
    }
    return retVal;
}

int32_t PMHALVideopllGetSelectFields(
    pmhalPrcmNodeId_t            videopllId,
    pmhalVideopllSelectConfig_t *pSelectConfig)
{
    int32_t           retVal;
    uint32_t          regVal;
    pmhalPrcmNodeId_t vidId;

    if (pSelectConfig == NULL)
    {
        retVal = PM_FAIL;
    }
    else
    {
        retVal = PmhalIsVideopllIdValid(videopllId);
        if (PM_SUCCESS == retVal)
        {
            /* For a given video PLL ID read the PLL_CONFIGURATION2 clock
             * enable fields.
             */
            vidId  = PMUtilsGetVidpllId(videopllId);
            regVal = HW_RD_REG32(pmhalVideoElems[vidId].pllConf2RegAddr);
            pSelectConfig->pllRefEn = HW_GET_FIELD(regVal, PMHAL_VIDEOPLL_REFEN);

            pSelectConfig->phyClkinEn = HW_GET_FIELD(regVal,
                                                     PMHAL_VIDEOPLL_PHY_CLKINEN);

            pSelectConfig->hsdivBypass = HW_GET_FIELD(regVal,
                                                      PMHAL_VIDEOPLL_BYPASSEN);

            pSelectConfig->refSysclk = HW_GET_FIELD(regVal,
                                                    PMHAL_VIDEOPLL_REFSEL);

            pSelectConfig->clockEnM4 = HW_GET_FIELD(regVal,
                                                    PMHAL_VIDEOPLL_M4_CLOCK_EN);

            pSelectConfig->clockEnM6 = HW_GET_FIELD(regVal,
                                                    PMHAL_VIDEOPLL_M6_CLOCK_EN);

            pSelectConfig->clockEnM7 = HW_GET_FIELD(regVal,
                                                    PMHAL_VIDEOPLL_M7_CLOCK_EN);
        }
    }
    return retVal;
}

int32_t PMHALVideopllSetSelectFields(
    pmhalPrcmNodeId_t videopllId,
    const pmhalVideopllSelectConfig_t * pSelectConfig)
{
    int32_t           retVal;
    uint32_t          regVal;
    pmhalPrcmNodeId_t vidId;

    if (NULL == pSelectConfig)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /* For a given video PLL ID program the PLL_CONFIGURATION2 clock
         * enable fields.
         */
        retVal = PmhalIsVideopllIdValid(videopllId);
        if (PM_SUCCESS == retVal)
        {
            vidId  = PMUtilsGetVidpllId(videopllId);
            regVal = HW_RD_REG32(pmhalVideoElems[vidId].pllConf2RegAddr);
            if (videopllId != PMHAL_PRCM_DPLL_SATA)
            {
                HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_REFEN,
                               pSelectConfig->pllRefEn);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_PHY_CLKINEN,
                               pSelectConfig->phyClkinEn);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_BYPASSEN,
                               pSelectConfig->hsdivBypass);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_REFSEL,
                               pSelectConfig->refSysclk);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_M4_CLOCK_EN,
                               pSelectConfig->clockEnM4);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_M6_CLOCK_EN,
                               pSelectConfig->clockEnM6);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_M7_CLOCK_EN,
                               pSelectConfig->clockEnM7);
            }
            else
            {
                HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_PLL_SELFREQDCO,
                               pSelectConfig->pllSelFreqDco);
                HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_PLL_LOCKSEL,
                               pSelectConfig->pllLockSel);
            }
            HW_WR_REG32(pmhalVideoElems[vidId].pllConf2RegAddr,
                        regVal);
        }
    }
    return retVal;
}

int32_t PMHALVideopllSetpllGo(pmhalPrcmNodeId_t videopllId, uint32_t value)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);

    if (PM_SUCCESS == retVal)
    {
        /* Program the PLL_GO field to the desired user input. */
        vidId = PMUtilsGetVidpllId(videopllId);
        HW_WR_FIELD32(pmhalVideoElems[vidId].pllGoRegAddr,
                      PMHAL_VIDEOPLL_PLL_GO,
                      value);
    }
    return retVal;
}

int32_t PMHALVideopllGetpllGo(pmhalPrcmNodeId_t videopllId)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);

    if (PM_SUCCESS == retVal)
    {
        /* Read the PLL_GO field */
        vidId  = PMUtilsGetVidpllId(videopllId);
        retVal = (int32_t) HW_RD_FIELD32(pmhalVideoElems[vidId].pllGoRegAddr,
                                         PMHAL_VIDEOPLL_PLL_GO);
    }
    return retVal;
}

int32_t PMHALVideopllGetModeFields(pmhalPrcmNodeId_t          videopllId,
                                   pmhalVideopllModeConfig_t *pModeConfig)
{
    int32_t           retVal;
    uint32_t          regVal;
    pmhalPrcmNodeId_t vidId;

    if (pModeConfig == NULL)
    {
        retVal = PM_FAIL;
    }
    else
    {
        retVal = PmhalIsVideopllIdValid(videopllId);

        if (PM_SUCCESS == retVal)
        {
            /* For a given video PLL ID read the PLL_CONFIGURATION2 power
             * mode fields.
             */
            vidId = PMUtilsGetVidpllId(videopllId);

            regVal = HW_RD_REG32(pmhalVideoElems[vidId].pllConf2RegAddr);

            pModeConfig->pllIdle = HW_GET_FIELD(regVal, PMHAL_VIDEOPLL_IDLE);

            pModeConfig->pllLpMode = HW_GET_FIELD(regVal,
                                                  PMHAL_VIDEOPLL_LPMODE);
            pModeConfig->lowCurrStBy = HW_GET_FIELD(regVal,
                                                    PMHAL_VIDEOPLL_LOWCURRSTBY);
            pModeConfig->driftGuardEn = HW_GET_FIELD(regVal,
                                                     PMHAL_VIDEOPLL_IDLE);
            pModeConfig->refEn = HW_GET_FIELD(
                regVal, PMHAL_VIDEOPLL_DRIFTGUARDEN);
            pModeConfig->phyClkinEn = HW_GET_FIELD(regVal,
                                                   PMHAL_VIDEOPLL_PHY_CLKINEN);
            pModeConfig->byPassEn = HW_GET_FIELD(regVal,
                                                 PMHAL_VIDEOPLL_BYPASSEN);
            pModeConfig->hsDivbyPass = HW_GET_FIELD(regVal,
                                                    PMHAL_VIDEOPLL_HSDIVBYPASS);
        }
    }
    return retVal;
}

int32_t PMHALVideopllSetModeFields(pmhalPrcmNodeId_t                videopllId,
                                   const pmhalVideopllModeConfig_t *pModeConfig)
{
    int32_t           retVal;
    uint32_t          regVal;
    pmhalPrcmNodeId_t vidId;

    retVal = PmhalIsVideopllIdValid(videopllId);

    if (PM_SUCCESS == retVal)
    {
        if (NULL == pModeConfig)
        {
            retVal = PM_BADARGS;
        }
        else
        {
            /* For a given video PLL ID program the PLL_CONFIGURATION2 power
             * mode fields.
             */
            vidId = PMUtilsGetVidpllId(videopllId);

            regVal = HW_RD_REG32(pmhalVideoElems[vidId].pllConf2RegAddr);

            HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_IDLE, pModeConfig->pllIdle);
            if (videopllId != PMHAL_PRCM_DPLL_SATA)
            {
                HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_LPMODE,
                               pModeConfig->pllLpMode);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_LOWCURRSTBY,
                               pModeConfig->lowCurrStBy);

                HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_IDLE,
                               pModeConfig->driftGuardEn);

                HW_SET_FIELD32(regVal, PMHAL_VIDEOPLL_DRIFTGUARDEN,
                               pModeConfig->refEn);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_PHY_CLKINEN,
                               pModeConfig->phyClkinEn);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_BYPASSEN,
                               pModeConfig->byPassEn);

                HW_SET_FIELD32(regVal,
                               PMHAL_VIDEOPLL_HSDIVBYPASS,
                               pModeConfig->hsDivbyPass);
            }
            HW_WR_REG32(pmhalVideoElems[vidId].pllConf2RegAddr, regVal);
        }
    }
    return retVal;
}

int32_t PMHALVideopllGetVencSource(pmhalVideoPllVenc_t VencId,
                                   pmhalPrcmClockId_t *videopllId,
                                   pmhalVideopllHSD_t *postDivId)
{
    int32_t  retVal = PM_SUCCESS;
    uint32_t muxSelect;

    switch (VencId)
    {
        /* For the given VENC ID find which is clock source in terms of the
         * PLL which is sourcing the clock and which divider is the clock
         * getting sourced from.
         */
        case PMHAL_VIDEOPLL_VENC_LCD1:
            muxSelect = HW_RD_FIELD32(DSS_CTRL_ADDR,
                                      DSS_CTRL_LCD1_CLK_SWITCH);
            if (muxSelect == 0x1U)
            {
                PmhalDsi1AClkMuxGetParent(videopllId, postDivId);
            }
            else if (muxSelect == 0x0U)
            {
                *videopllId = PMHAL_PRCM_CLK_DSS_GFCLK;
                *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
            }
            else
            {
                /* Invalid Mux value */
                retVal = PM_BADARGS;
            }
            break;

        case PMHAL_VIDEOPLL_VENC_LCD2:
            muxSelect = HW_RD_FIELD32(DSS_CTRL_ADDR,
                                      DSS_CTRL_LCD2_CLK_SWITCH);

            if (muxSelect == 0x1U)
            {
                PmhalDsi1BClkMuxGetParent(videopllId, postDivId);
            }
            else if (muxSelect == 0x0U)
            {
                *videopllId = PMHAL_PRCM_CLK_DSS_GFCLK;
                *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
            }
            else
            {
                retVal = PM_BADARGS;
            }
            break;

        case PMHAL_VIDEOPLL_VENC_LCD3:
            muxSelect = HW_RD_FIELD32(DSS_CTRL_ADDR,
                                      DSS_CTRL_LCD3_CLK_SWITCH);
            if (muxSelect == 0x1U)
            {
                PmhalDsi1CClkMuxGetParent(videopllId, postDivId);
            }
            else if (muxSelect == 0x0U)
            {
                *videopllId = PMHAL_PRCM_CLK_DSS_GFCLK;
                *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
            }
            else
            {
                retVal = PM_BADARGS;
            }
            break;

        case PMHAL_VIDEOPLL_VENC_HDMI:
            muxSelect = HW_RD_FIELD32(DSS_CTRL_ADDR,
                                      DSS_CTRL_FCK_CLK_SWITCH);

            if (muxSelect == 0x01U)
            {
                PmhalDsi1AClkMuxGetParent(videopllId, postDivId);
            }
            else if (muxSelect == 0x02U)
            {
                PmhalDsi1BClkMuxGetParent(videopllId, postDivId);
            }
            else if (muxSelect == 0x04U)
            {
                PmhalDsi1CClkMuxGetParent(videopllId, postDivId);
            }
            else if (muxSelect == 0x03U)
            {
                *videopllId = PMHAL_PRCM_CLK_HDMI_DPLL_CLK;
                *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
            }
            else if (muxSelect == 0x0U)
            {
                *videopllId = PMHAL_PRCM_CLK_DSS_GFCLK;
                *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
            }
            else
            {
                retVal = PM_BADARGS;
            }
            break;

        default:
            retVal = PM_BADARGS;
            break;
    }
    return retVal;
}

int32_t PMHALVideopllSetLoopBw (pmhalPrcmNodeId_t            videopllId,
                                pmhalPrcmLoopBwMode_t        mode)
{
    int32_t retVal = (int32_t)PM_SUCCESS;
    uint32_t regVal = 0U;
    uint32_t incr_decrz = 0U, loopbw = 0U;
    /* Find the appropriate loop bandwidth and the increment or decrement
     * value.
     * The configuration is:
     * -----------------------------------------------------------------------------
     *  BW_INCR_DECRZ | BW_CONTROL[1:0] | BW Mode     | PLL Bandwidth       |Units
     *  --------------+-----------------+-------------+---------------------+--------
     *                |                 |             | Min  | Nom  | Max   |
     *  --------------+-----------------+-------------+------+------+-------+--------
     *  0             | 00              | 1x (Default)| 1/30 | 1/50 | 1/70  |REFCLK
     *  0             | 01              | 0.5x        | 1/60 | 1/100| 1/140 |REFCLK
     *  0             | 10              | 0.25x       | 1/120| 1/200| 1/280 |REFCLK
     *  0             | 11              | 0.125x      | 1/240| 1/400| 1/560 |REFCLK
     *  1             | 00              | 1x          | 1/30 | 1/50 | 1/70  |REFCLK
     *  1             | 01              | 2x          | 1/15 | 1/25 |  1/35 |REFCLK
     *  1             | 10              | Reserved    |      |      |       |REFCLK
     *  1             | 11              | Reserved    |      |      |       |REFCLK
     *  -----------------------------------------------------------------------------
     */
    switch (mode)
    {
        case PMHAL_PRCM_LOOP_BW_1x:
            incr_decrz = 0U;
            loopbw = 0U;
            break;
        case PMHAL_PRCM_LOOP_BW_0p5x:
            incr_decrz = 0U;
            loopbw = 1U;
            break;
        case PMHAL_PRCM_LOOP_BW_0p25x:
            incr_decrz = 0U;
            loopbw = 2U;
            break;
        case PMHAL_PRCM_LOOP_BW_0p125x:
            incr_decrz = 0U;
            loopbw = 3U;
            break;
        case PMHAL_PRCM_LOOP_BW_1x_1:
            /* Increment/decrement not available for Video PLL1/2 */
            if ((videopllId == PMHAL_PRCM_VIDEOPLL_VIDEO1) ||
               (videopllId == PMHAL_PRCM_VIDEOPLL_VIDEO2))
            {
                retVal = PM_BADARGS;
            }
            else
            {
                incr_decrz = 1U;
                loopbw = 0U;
            }
            break;
        case PMHAL_PRCM_LOOP_BW_2x:
            /* Increment/decrement not available for Video PLL1/2 */
            if ((videopllId == PMHAL_PRCM_VIDEOPLL_VIDEO1) ||
               (videopllId == PMHAL_PRCM_VIDEOPLL_VIDEO2))
            {
                retVal = PM_BADARGS;
            }
            else
            {
                incr_decrz = 1U;
                loopbw = 1U;
            }
            break;
        default:
            retVal = (int32_t)PM_BADARGS;
            break;
    }
    if (retVal == (int32_t)PM_SUCCESS)
    {
        /* Read modify and write to the register */
        regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL);
        switch(videopllId)
        {
            case PMHAL_PRCM_VIDEOPLL_VIDEO1:
                HW_SET_FIELD32(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_LOOPBW, loopbw);
                HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL, regVal);
                break;
            case PMHAL_PRCM_VIDEOPLL_VIDEO2:
                HW_SET_FIELD32(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_LOOPBW, loopbw);
                HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL, regVal);
                break;
            case PMHAL_PRCM_VIDEOPLL_HDMI:
                HW_SET_FIELD32(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_LOOPBW, loopbw);
                HW_SET_FIELD32(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_LOOPBW_INCR_DECRZ, incr_decrz);
                HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL, regVal);
                break;
            case PMHAL_PRCM_DPLL_SATA:
                regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_CONTROL_C2C);
                HW_SET_FIELD32(regVal, CTRL_CORE_CONTROL_C2C_PLL_SATA_LOOPBW, loopbw);
                HW_SET_FIELD32(regVal, CTRL_CORE_CONTROL_C2C_PLL_SATA_LOOPBW_INCR_DECRZ, incr_decrz);
                HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_CONTROL_C2C, regVal);
                break;
            default:
                retVal = PM_BADARGS;
                break;
        }
    }
    return retVal;
}

int32_t PMHALVideopllGetLoopBw (pmhalPrcmNodeId_t            videopllId,
                                pmhalPrcmLoopBwMode_t        *mode)
{
    int32_t retVal = (int32_t)PM_SUCCESS;
    uint32_t regVal = 0U;
    uint32_t incr_decrz = 0U, loopbw = 0U;
    /* Read the fields from the registers */
    regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_DSS_PLL_CONTROL);
    switch(videopllId)
    {
        case PMHAL_PRCM_VIDEOPLL_VIDEO1:
            loopbw = HW_GET_FIELD(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_LOOPBW);
            break;
        case PMHAL_PRCM_VIDEOPLL_VIDEO2:
            loopbw = HW_GET_FIELD(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_LOOPBW);
            break;
        case PMHAL_PRCM_VIDEOPLL_HDMI:
            loopbw = HW_GET_FIELD(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_LOOPBW);
            incr_decrz = HW_GET_FIELD(regVal, CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_LOOPBW_INCR_DECRZ);
            break;
        case PMHAL_PRCM_DPLL_SATA:
            regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_CONTROL_C2C);
            loopbw = HW_GET_FIELD(regVal, CTRL_CORE_CONTROL_C2C_PLL_SATA_LOOPBW);
            incr_decrz = HW_GET_FIELD(regVal, CTRL_CORE_CONTROL_C2C_PLL_SATA_LOOPBW_INCR_DECRZ);
            break;
        default:
            retVal = PM_BADARGS;
            break;
    }
    *mode = (pmhalPrcmLoopBwMode_t)((incr_decrz << 2U) | loopbw);
    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalSelectIdToMuxId (uint32_t muxId)
{
    if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_DSS_MUX_A1)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_DSS_MUX_B2)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_DSS_MUX_C12)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL1)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL1;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_DSS_MUX_AL2)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_AL2;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_A_CLK1)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_B_CLK1)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B;
    }
    else if (muxId == (uint32_t)PMHAL_PRCM_VIDEOPLL_MUX_DPLL_DSI1_C_CLK1)
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C;
    }
    else
    {
        muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX;
    }
    return muxId;
}

static void PmhalDsi1AClkMuxGetParent(pmhalPrcmClockId_t *videopllId,
                                      pmhalVideopllHSD_t *postDivId)
{
    uint32_t muxId, parentNodeId, muxParentIdx, nodeEnumValue;
    parentNodeId = PMHAL_PRCM_VIDEOPLL_MUX_INVALID;

    muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_A1;
    nodeEnumValue = HW_RD_FIELD32_RAW(
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regAddr,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regMask,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regShift);
    for (muxParentIdx = 0U;
         muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
         muxParentIdx++)
    {
        /* Find the matching parent for the register value read. */
        if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
            nodeEnumValue == nodeEnumValue)
        {
            parentNodeId = pmhalVidMuxElems[muxId].pSupportedEnum
                           [muxParentIdx].nodeMuxId;
            break;
        }
    }
    muxId = PmhalSelectIdToMuxId(parentNodeId);
    if (muxId < PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX)
    {
        nodeEnumValue = HW_RD_FIELD32_RAW(
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regAddr,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regMask,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regShift);

        for (muxParentIdx = 0U;
            muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
            muxParentIdx++)
        {
            /* Find the matching parent for the register value read. */
            if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
                nodeEnumValue == nodeEnumValue)
            {
                parentNodeId = pmhalVidMuxElems[muxId].pSupportedEnum
                            [muxParentIdx].nodeMuxId;
                break;
            }
        }
        /* From the parent Node Id derive the source Video PLL ID and the HSDivider
        */
        if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1)
        {
            *videopllId = PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_M4;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_HDMI)
        {
            *videopllId = PMHAL_PRCM_CLK_HDMI_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_M2;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA)
        {
            *videopllId = PMHAL_PRCM_CLK_SATA_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
        else
        {
            *videopllId = PMHAL_PRCM_CLK_UNDEF;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
    }
    else
    {
        *videopllId = PMHAL_PRCM_CLK_UNDEF;
        *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
    }
}

static void PmhalDsi1BClkMuxGetParent(pmhalPrcmClockId_t *videopllId,
                                      pmhalVideopllHSD_t *postDivId)
{
    uint32_t muxId, parentNodeId, muxParentIdx, nodeEnumValue;
    parentNodeId = PMHAL_PRCM_VIDEOPLL_MUX_INVALID;
    muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_B2;
    nodeEnumValue = HW_RD_FIELD32_RAW(
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regAddr,
        (	uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regMask,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regShift);
    for (muxParentIdx = 0U;
         muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
         muxParentIdx++)
    {
        /* Find the matching parent for the register value read. */
        if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
            nodeEnumValue == nodeEnumValue)
        {
            parentNodeId = pmhalVidMuxElems[muxId].pSupportedEnum
                           [muxParentIdx].nodeMuxId;
            break;
        }
    }
    muxId = PmhalSelectIdToMuxId(parentNodeId);
    if (muxId < PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX)
    {
        nodeEnumValue = HW_RD_FIELD32_RAW(
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regAddr,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regMask,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regShift);

        for (muxParentIdx = 0U;
            muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
            muxParentIdx++)
        {
            /* Find the matching parent for the register value read. */
            if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
                nodeEnumValue == nodeEnumValue)
            {
                parentNodeId = pmhalVidMuxElems[muxId].pSupportedEnum
                            [muxParentIdx].nodeMuxId;
                break;
            }
        }
        /* From the parent Node Id derive the source Video PLL ID and the HSDivider
        */
        if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1)
        {
            *videopllId = PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_M6;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2)
        {
            *videopllId = PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_M6;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_ABE)
        {
            *videopllId = PMHAL_PRCM_CLK_ABE_GICLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_HDMI)
        {
            *videopllId = PMHAL_PRCM_CLK_HDMI_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA)
        {
            *videopllId = PMHAL_PRCM_CLK_SATA_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
        else
        {
            *videopllId = PMHAL_PRCM_CLK_UNDEF;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
    }
    else
    {
        *videopllId = PMHAL_PRCM_CLK_UNDEF;
        *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
    }
}

static void PmhalDsi1CClkMuxGetParent(pmhalPrcmClockId_t *videopllId,
                                      pmhalVideopllHSD_t *postDivId)
{
    uint32_t muxId, parentNodeId, muxParentIdx, nodeEnumValue;
    parentNodeId = PMHAL_PRCM_VIDEOPLL_MUX_INVALID;
    muxId = PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_C12;
    nodeEnumValue = HW_RD_FIELD32_RAW(
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regAddr,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regMask,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regShift);
    for (muxParentIdx = 0U;
         muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
         muxParentIdx++)
    {
        /* Find the matching parent for the register value read. */
        if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
            nodeEnumValue == nodeEnumValue)
        {
            parentNodeId = pmhalVidMuxElems[muxId].pSupportedEnum
                           [muxParentIdx].nodeMuxId;
            break;
        }
    }
    muxId = PmhalSelectIdToMuxId(parentNodeId);
    if (muxId < PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX)
    {
        nodeEnumValue = HW_RD_FIELD32_RAW(
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regAddr,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regMask,
        (uint32_t) pmhalVidMuxElems[muxId].muxSelBitField->regShift);

        for (muxParentIdx = 0U;
            muxParentIdx < pmhalVidMuxElems[muxId].pSupportedEnumMax;
            muxParentIdx++)
        {
            /* Find the matching parent for the register value read. */
            if (pmhalVidMuxElems[muxId].pSupportedEnum[muxParentIdx].
                nodeEnumValue == nodeEnumValue)
            {
                parentNodeId = pmhalVidMuxElems[muxId].pSupportedEnum
                            [muxParentIdx].nodeMuxId;
                break;
            }
        }
        /* From the parent Node Id derive the source Video PLL ID and the HSDivider
        */
        if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_VIDEO1)
        {
            *videopllId = PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_M6;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_VIDEO2)
        {
            *videopllId = PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_M4;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_MUX_HDMI)
        {
            *videopllId = PMHAL_PRCM_CLK_HDMI_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
        else if (parentNodeId == PMHAL_PRCM_VIDEOPLL_DSS_ALTCLK1_DPLL_SATA)
        {
            *videopllId = PMHAL_PRCM_CLK_SATA_DPLL_CLK;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
        else
        {
            *videopllId = PMHAL_PRCM_CLK_UNDEF;
            *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
        }
    }
    else
    {
        *videopllId = PMHAL_PRCM_CLK_UNDEF;
        *postDivId  = PMHAL_VIDEOPLL_HSD_INVALID;
    }
}

static int32_t PmhalIsVideopllIdValid(pmhalPrcmNodeId_t videopllId)
{
    int32_t retVal;
    /* Check if the given video PLL ID is valid or not */
    if ((PMHAL_PRCM_VIDEOPLL_MIN <= videopllId) &&
        (PMHAL_PRCM_VIDEOPLL_COUNT > videopllId))
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

static int32_t PmhalVideopllSetMultiplierValueInternal(
    pmhalPrcmNodeId_t videopllId,
    uint32_t          mulValue)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    vidId = PMUtilsGetVidpllId(videopllId);
    /* Check if the multiplier value is valid or not and then program the
     * PLL register */
    if (mulValue < (PMHAL_VIDEOPLL_MULTI_MASK >> PMHAL_VIDEOPLL_MULTI_SHIFT))
    {
        HW_WR_FIELD32((uint32_t) pmhalVideoElems[vidId].pllConf1RegAddr,
                      (uint32_t) PMHAL_VIDEOPLL_MULTI,
                      (uint32_t) mulValue);
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_CM_DPLL_MULTIPLIER_VALUE_OUT_OF_RANGE;
    }
    return retVal;
}

static int32_t PmhalVideopllSetDividerValueInternal(
    pmhalPrcmNodeId_t videopllId,
    uint32_t          divValue)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    vidId = PMUtilsGetVidpllId(videopllId);
    /* Check if the divider value is valid or not and then program the
     * PLL register */
    if (divValue < (PMHAL_VIDEOPLL_DIV_MASK >> PMHAL_VIDEOPLL_DIV_SHIFT))
    {
        HW_WR_FIELD32((uint32_t) pmhalVideoElems[vidId].pllConf1RegAddr,
                      (uint32_t) PMHAL_VIDEOPLL_DIV,
                      (uint32_t) (divValue - 1U));
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_CM_DPLL_DIVIDER_VALUE_OUT_OF_RANGE;
    }
    return retVal;
}

static int32_t PmhalVideopllGetMultiplierValueInternal(
    pmhalPrcmNodeId_t videopllId)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    vidId = PMUtilsGetVidpllId(videopllId);

    retVal = (int32_t) HW_RD_FIELD32(
        (uint32_t) pmhalVideoElems[vidId].pllConf1RegAddr,
        (uint32_t) PMHAL_VIDEOPLL_MULTI);

    return retVal;
}

static int32_t PmhalVideopllGetDividerValueInternal(
    pmhalPrcmNodeId_t videopllId)
{
    int32_t           retVal;
    pmhalPrcmNodeId_t vidId;

    vidId = PMUtilsGetVidpllId(videopllId);

    retVal = (int32_t) HW_RD_FIELD32(
        (uint32_t) pmhalVideoElems[vidId].pllConf1RegAddr,
        (uint32_t) PMHAL_VIDEOPLL_DIV);

    return retVal;
}

static int32_t PmhalIsVideoMuxClkSelValid(
    pmhalPrcmVideopllDssClkSrcMuxId_t muxId)
{
    int32_t retVal;
    if (PMHAL_INVALID_REGADDR ==
        pmhalVidMuxElems[muxId].muxSelBitField->regAddr)
    {
        retVal = PM_CM_MUX_CLK_SEL_REGISTER_INVALID;
    }
    else
    {
        retVal = PM_SUCCESS;
    }
    return retVal;
}

static int32_t PmhalIsVideoMuxIdValid(pmhalPrcmVideopllDssClkSrcMuxId_t muxId)
{
    int32_t retVal;

    if (muxId < PMHAL_PRCM_VIDEOPLL_DSS_CLKSRC_MUX_MAX)
    {
        retVal = PM_SUCCESS;
    }
    else
    {
        retVal = PM_BADARGS;
    }
    return retVal;
}

