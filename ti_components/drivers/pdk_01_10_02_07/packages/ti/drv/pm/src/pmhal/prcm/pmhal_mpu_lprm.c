/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 * \file pmhal_mpu_lprm.c
 *
 * \brief   MPU Local PRM interface API definition.
 *
 *          The MPU LPRM API supports the following features:
 *          - Mercury Retention Enable.
 *          - Mercury Retention Ramp Up enable + Corresponding ramp time.
 *          - Set the power state of the CPU.
 *          - Read the power status of the CPU.
 *          - Set the clock state of the CPU.
 *          - Read the standby status of the CPU.
 *
 * \note    The reset capability of MPU LPRM is handled in the Reset
 *          Manager HAL.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pmhal_prcm.h"
#include "pmhal_mpu_lprm.h"
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void PMHALMpuLprmSetMercuryRetention(void)
{
    /* In addition to the standard power-management technique supported in
     * the device, the MPU subsystem also employs an SR3-APG (SmartReflex3
     * automatic power gating) power-management technology to reduce leakage.
     * This technology allows for full logic and memories retention on MPU_C0
     * and MPU_C1 and is controlled by the MPU_PRCM. The SR3-APG
     * power-management can be enabled by setting the PRM_PSCON_COUNT[24]
     * HG_EN bit.
     */
    HW_WR_FIELD32(SOC_PRCM_MPU_DEVICE_BASE + MPU_PRM_PSCON_COUNT,
                  MPU_PRM_PSCON_COUNT_HG_EN,
                  1);
}

void PMHALMpuLprmClearMercuryRetention(void)
{
    /* The SR3-APG power-management can be disabled by clearing the
     * PRM_PSCON_COUNT[24] HG_EN bit.
     */
    HW_WR_FIELD32(SOC_PRCM_MPU_DEVICE_BASE + MPU_PRM_PSCON_COUNT,
                  MPU_PRM_PSCON_COUNT_HG_EN,
                  0);
}

int32_t PMHALMpuLprmSetHgRampParams(
    const pmhalMpuLprmHgRampParams_t *hgRampParam)
{
    pmErrCode_t status = PM_SUCCESS;

    uint32_t    rampType;

    if (NULL != hgRampParam)
    {
        /*
         * The ramp type is a single bit field. Capture this 1 bit value.
         * This is a check to ensure that the register is not programmed with
         * any value other than 1 or 0.
         *
         * The SR3-APG power-management technology implements a fast power
         * ramp-up technology. To take advantage of the fast ramp-up feature
         * in SR3-APG, software must first enable it by setting the
         * PRM_PSCON_COUNT[25] HG_RAMPUP bit to 1.
         *
         * A fail-safe mechanism is put in place to revert back to the standard
         * power ramp-up time by setting the PRM_PSCON_COUNT[25] HG_RAMPUP
         * bit to 0.
         */
        rampType = hgRampParam->hgRampType & (uint32_t) 1U;

        if ((0U == rampType) && (0U == hgRampParam->hgSlowRampTime))
        {
            status = PM_BADARGS;
        }
        else
        {
            /* Set the slow ramp time if the rampType is slow
             * The slow ramp-up time can be set through the
             * PRM_PSCON_COUNT[23:16] HG_PONOUT_2_PGDOODIN_TIME bit field
             * when the HG weak chain is used (in other words, the
             * PRM_PSCON_COUNT[25] HG_RAMPUP bit is set to 0x0).
             */
            if (0U == rampType)
            {
                HW_WR_FIELD32(SOC_PRCM_MPU_DEVICE_BASE + MPU_PRM_PSCON_COUNT,
                              MPU_PRM_PSCON_COUNT_HG_PONOUT_2_PGDOODIN_TIME,
                              hgRampParam->hgSlowRampTime);
            }

            HW_WR_FIELD32(SOC_PRCM_MPU_DEVICE_BASE + MPU_PRM_PSCON_COUNT,
                          MPU_PRM_PSCON_COUNT_HG_RAMPUP,
                          rampType);
        }
    }
    else
    {
        status = PM_BADARGS;
    }
    return status;
}

int32_t PMHALMpuLprmSetPowerMode(uint32_t cpuId, pmhalPrcmPdState_t mode)
{
    pmErrCode_t status = PM_SUCCESS;

    if (mode < PMHAL_PRCM_PD_STATUS_COUNT)
    {
        if (0U == cpuId)
        {
            /* For CPU 0 */
            HW_WR_FIELD32(SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTCTRL,
                          MPU_PM_CPU0_PWRSTCTRL_POWERSTATE,
                          mode);
        }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)

        else if (1U == cpuId)
        {
            /* For CPU 1 */
            HW_WR_FIELD32(SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTCTRL,
                          MPU_PM_CPU1_PWRSTCTRL_POWERSTATE,
                          mode);
        }
#endif
        else
        {
            status = PM_BADARGS;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALMpuLprmSetForceOff(uint32_t cpuId)
{
    pmErrCode_t status = PM_BADARGS;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    if (1U == cpuId)
    {
        /* For CPU 1 */
        /* Force Off is valid only for CPU 1 */
        HW_WR_FIELD32(SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTCTRL,
                      MPU_PM_CPU1_PWRSTCTRL_FORCED_OFF,
                      MPU_PM_CPU1_PWRSTCTRL_FORCED_OFF_OFF_FORCED);
        status = PM_SUCCESS;
    }
#endif

    return status;
}

int32_t PMHALMpuLprmClearForceOff(uint32_t cpuId)
{
    pmErrCode_t status = PM_BADARGS;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    if (1U == cpuId)
    {
        /* For CPU 1 */
        /* Force Off is valid only for CPU 1 */
        HW_WR_FIELD32(SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTCTRL,
                      MPU_PM_CPU1_PWRSTCTRL_FORCED_OFF,
                      MPU_PM_CPU1_PWRSTCTRL_FORCED_OFF_OFF_NOT_FORCED);
        status = PM_SUCCESS;
    }
#endif

    return status;
}

int32_t PMHALMpuLprmGetPowerTransitionState(uint32_t cpuId,
                                            pmhalPrcmPdTransitionState_t *
                                            inTransition)
{
    pmErrCode_t status = PM_SUCCESS;

    if (inTransition == NULL)
    {
        status = PM_BADARGS;
    }
    else if (0U == cpuId)
    {
        /* For CPU 0 */
        *inTransition = (pmhalPrcmPdTransitionState_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTST,
            MPU_PM_CPU0_PWRSTST_INTRANSITION);
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (1U == cpuId)
    {
        /* For CPU 1 */
        *inTransition = (pmhalPrcmPdTransitionState_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTST,
            MPU_PM_CPU1_PWRSTST_INTRANSITION);
    }
#endif
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALMpuLprmGetLastPowerState(uint32_t            cpuId,
                                      pmhalPrcmPdState_t *lastPowerState)
{
    pmErrCode_t status = PM_SUCCESS;

    if (lastPowerState == NULL)
    {
        status = PM_BADARGS;
    }
    else if (0U == cpuId)
    {
        /* For CPU 0 */
        *lastPowerState = (pmhalPrcmPdState_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTST,
            MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED);
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (1U == cpuId)
    {
        /* For CPU 1 */
        *lastPowerState = (pmhalPrcmPdState_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTST,
            MPU_PM_CPU1_PWRSTST_LASTPOWERSTATEENTERED);
    }
#endif
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALMpuLprmSetLastPowerState(uint32_t           cpuId,
                                      pmhalPrcmPdState_t lastPowerState)
{
    pmErrCode_t status = PM_SUCCESS;

    if (lastPowerState < PMHAL_PRCM_PD_STATUS_COUNT)
    {
        if (0U == cpuId)
        {
            /* For CPU 0 */
            HW_WR_FIELD32(SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTST,
                          MPU_PM_CPU0_PWRSTST_LASTPOWERSTATEENTERED,
                          lastPowerState);
        }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
        else if (1U == cpuId)
        {
            /* For CPU 1 */
            HW_WR_FIELD32(SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTST,
                          MPU_PM_CPU1_PWRSTST_LASTPOWERSTATEENTERED,
                          lastPowerState);
        }
#endif
        else
        {
            status = PM_BADARGS;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALMpuLprmGetPowerStatus(uint32_t                     cpuId,
                                   pmhalMpuPowerStatusParams_t *mpuPowerState)
{
    pmErrCode_t status = PM_SUCCESS;

    if (mpuPowerState == NULL)
    {
        status = PM_BADARGS;
    }
    else if (0U == cpuId)
    {
        /* For CPU 0 */
        mpuPowerState->currPowerStatus = (pmhalPrcmPdState_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTST,
            MPU_PM_CPU0_PWRSTST_POWERSTATEST);

        mpuPowerState->mpuLogicState = (uint8_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTST,
            MPU_PM_CPU0_PWRSTCTRL_LOGICRETSTATE);

        mpuPowerState->mpuL1MemoryState = (uint8_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C0_BASE + MPU_PM_CPU0_PWRSTST,
            MPU_PM_CPU0_PWRSTCTRL_L1_BANK_RETSTATE);
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (1U == cpuId)
    {
        /* For CPU 1 */
        mpuPowerState->currPowerStatus = (pmhalPrcmPdState_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTST,
            MPU_PM_CPU1_PWRSTST_POWERSTATEST);

        mpuPowerState->mpuLogicState = (uint8_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTST,
            MPU_PM_CPU1_PWRSTCTRL_LOGICRETSTATE);

        mpuPowerState->mpuL1MemoryState = (uint8_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_PRM_C1_BASE + MPU_PM_CPU1_PWRSTST,
            MPU_PM_CPU1_PWRSTCTRL_L1_BANK_RETSTATE);
    }
#endif
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALMpuLprmSetClockMode(uint32_t                 cpuId,
                                 pmhalPrcmCdClkTrnModes_t clockMode)
{
    pmErrCode_t status = PM_SUCCESS;

    if (clockMode <= PMHAL_PRCM_CD_CLKTRNMODES_MAX)
    {
        /* The MPU LPRM does not support SW_SLEEP */
        if (clockMode == PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP)
        {
            status = PM_BADARGS;
        }
        else if (0U == cpuId)
        {
            /* For CPU 0 */
            HW_WR_FIELD32(SOC_PRCM_MPU_CM_C0_BASE + MPU_CM_CPU0_CLKSTCTRL,
                          MPU_CM_CPU0_CLKSTCTRL_CLKTRCTRL,
                          (uint32_t) clockMode);
        }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
        else if (1U == cpuId)
        {
            /* For CPU 1 */
            HW_WR_FIELD32(SOC_PRCM_MPU_CM_C1_BASE + MPU_CM_CPU1_CLKSTCTRL,
                          MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL,
                          (uint32_t) clockMode);
        }
#endif
        else
        {
            status = PM_BADARGS;
        }
    }
    return status;
}

int32_t PMHALMpuLprmGetStandbyStatus(uint32_t cpuId, uint8_t *standbyEn)
{
    pmErrCode_t status = PM_SUCCESS;

    /* The MPU LPRM does not support SW_SLEEP */
    if (standbyEn == NULL)
    {
        status = PM_BADARGS;
    }
    else if (0U == cpuId)
    {
        /* For CPU 0 */
        *standbyEn = (uint8_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_CM_C0_BASE + MPU_CM_CPU0_CPU0_CLKCTRL,
            MPU_CM_CPU0_CPU0_CLKCTRL_STBYST);
    }
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
    else if (1U == cpuId)
    {
        /* For CPU 1 */
        *standbyEn = (uint8_t) HW_RD_FIELD32(
            SOC_PRCM_MPU_CM_C1_BASE + MPU_CM_CPU1_CPU1_CLKCTRL,
            MPU_CM_CPU1_CPU1_CLKCTRL_STBYST);
    }
#endif
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

