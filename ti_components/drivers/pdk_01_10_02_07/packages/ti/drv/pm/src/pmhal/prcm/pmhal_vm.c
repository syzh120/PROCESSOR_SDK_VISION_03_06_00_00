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
 * \file pmhal_vm.c
 *
 * \brief   Voltage Manager API implementation.
 *
 *          The Voltage API supports the following features:
 *          - Operating Performance Point (OPP)
 *          - AVS Class-0U
 *          - Adaptive Body Bias (ABB)
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_prcm.h"
#include "pmhal_pmic.h"
#include "pmhal_vm.h"
#include "pmhal_cm.h"
#include "hw_pmhal_vmdata.h"
#include "hw_pmhal_data.h"
#include "common/hw_pmhal_common_vmdata.h"

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

/**
 * \brief Calculate the wait count (WTCNT) value. This value determines
 *        the duration ABB LDO waits to get to the target voltage. This
 *        value is in number of system clock cycles.
 *
 * \param  None
 *
 * \return Return the WTCNT value in units of 16 sys_clk cycles.
 *
 */
static uint32_t PmhalVmGetWtCnt(void);

/**
 * \brief Read the package type and determine the index of the voltage to choose
 *        in the VM database.
 *
 * \param  None
 *
 * \return nomVoltageIndex  Index of the  voltage to choose
 *                          in the VM database.
 *
 */
static uint32_t PmhalVmGetVoltageIndex(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

pmErrCode_t PMHALVMSetOpp(pmhalPrcmVdId_t voltDomId, pmhalVmOppId_t oppId,
                          uint32_t timeout)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t    *vd         = NULL;
    const pmhalVmOppVoltage_t       *oppVoltage = NULL;
    uint32_t    volt_mv         = 0U;
    uint32_t    isABBEnable     = 0U;
    uint32_t    curr_mv         = 0U;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);
    if (NULL == vd)
    {
        retVal = PM_INPUT_PARAM_BAD_VOLTAGE_ID;
    }
    else
    {
        oppVoltage = PmhalVmGetOppVoltage(vd, oppId);
        if (oppVoltage == NULL)
        {
            retVal = PM_BADARGS;
        }
    }

    if (PM_SUCCESS == retVal)
    {
        /*
         * Get the AVS Class-0U voltage to be used.
         */
        volt_mv = PMHALVMGetAVS0EfuseVoltage(voltDomId, oppId);

        if (volt_mv != 0U)
        {
            /*
            * Get the current value of the voltage rail.
            * This will be used to compare against the desired voltage.
            * If the rail is already configured for this exact voltage setting
            * there is no need to again set the voltage.
            */
            retVal = PMHALVMGetCurrentVoltage(voltDomId, &curr_mv);

            /*
             * Nothing to be done if the current voltage rail is the same
             * as the desired voltage.
             */
            if ((retVal == PM_SUCCESS) && (curr_mv != volt_mv))
            {
                /*
                 * ABB Programming Overview:
                 * -------------------------
                 *
                 * ABB LDO supports two modes, namely bypass mode and
                 * FBB mode. The mode name FBB is used for historical
                 * reason but enabling the FBB mode can result in
                 * Forward Body Bias (FBB) or Reverse Body Bias (RBB)
                 * depending on the VSET_OUT value programmed.
                 *
                 * When changing OPP, if the old OPP required ABB then,
                 * we need to disable (put ABB LDO in bypass mode),
                 * change the voltage and if the new OPP requires ABB,
                 * enable ABB.
                 *
                 * The ABB first needs to be initialized.
                 * See PMHALVMInitABB() for details.
                 *
                 * NOTE: The initialization steps need to be performed
                 *       only once at the system initialization;
                 *       however, since we don't want to maintain
                 *       state, we do the initialization every time.
                 *
                 * The Setup and Control registers to program ABB
                 * are described in PMHALVMEnableABB().
                 *
                 * NOTE: The oppVoltage structure represents the
                 *       new OPP we need to enter into; however, we need
                 *       to check if the current OPPrequired ABB. Since
                 *       the same control/retVal registers are used for
                 *       a given VD, we can use the new OPP structure
                 *       to check if the current OPP required ABB.
                 */

                pmhalPrcmPmicRegulatorId_t regId = PmhalVmGetRegulatorId(
                    voltDomId);

                if (oppVoltage->isABBSupported == TRUE)
                {
                    uint32_t vminAbbEn;

                    PMHALVMInitABB(voltDomId, oppId);
                    isABBEnable = (uint32_t) PMHALVMIsABBEnabled(voltDomId,
                                                                 oppId);
                    if (isABBEnable == TRUE)
                    {
                        retVal = PMHALVMDisableABB(voltDomId, oppId);
                    }

                    if (PM_SUCCESS == retVal)
                    {
                        retVal = PMHALPmicSetRegulatorVoltage(regId, volt_mv,
                                                              timeout,
                                                              (uint32_t) TRUE);
                    }
                    if (PM_SUCCESS == retVal)
                    {
                        vminAbbEn =
                            HW_RD_FIELD32(oppVoltage->fuseOPPVminRegAddr,
                                          PMHAL_VM_STD_FUSE_OPP_VMIN_ABBEN);

                        if (vminAbbEn != 0U)
                        {
                            retVal = PMHALVMEnableABB(voltDomId, oppId);
                        }
                    }
                }
                else
                {
                    retVal = PMHALPmicSetRegulatorVoltage(regId, volt_mv,
                                                          timeout,
                                                          (uint32_t) TRUE);
                }
            }
        }
        else
        {
            retVal = PM_VOLTAGE_INVALID;
        }
    }

    return retVal;
}

pmErrCode_t PMHALVMGetCurrentVoltage(pmhalPrcmVdId_t voltDomId,
                                     uint32_t       *voltage)
{
    pmErrCode_t retVal = PM_SUCCESS;

    /*
     * Check the input parameters.
     */
    if ((voltage == NULL) ||
        ((voltDomId >= PMHAL_PRCM_VD_COUNT) || (voltDomId < PMHAL_PRCM_VD_MIN)))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /*
         * Get the voltage regulator ID and query the PMIC to get the
         * voltage setting from that regulator.
         */
        pmhalPrcmPmicRegulatorId_t regId = PmhalVmGetRegulatorId(voltDomId);
        /*
         * Set the default voltage value. If any error conditions
         * occurs the value of voltage = 0U is given back to the caller.
         */
        *voltage = 0U;
        retVal   = PMHALPmicGetRegulatorVoltage(regId, voltage);
    }

    return retVal;
}

pmErrCode_t PMHALVMGetCurrentOpp(pmhalPrcmVdId_t voltDomId,
                                 pmhalVmOppId_t *oppId)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    uint32_t    voltage    = 0U;
    uint32_t    done       = FALSE;
    uint32_t    avsVoltage = 0U;
    const pmhalVmOppVoltage_t    *opp = NULL;
    int32_t     i;
    uint32_t    nomVoltageIndex = 0U;

    if ((voltDomId >= PMHAL_PRCM_VD_COUNT) || (oppId == NULL))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        retVal = PMHALVMGetCurrentVoltage(voltDomId, &voltage);
        vd     = PmhalVmGetVoltageDomain(voltDomId);

        if (NULL != vd)
        {
            if (PM_SUCCESS == retVal)
            {
                nomVoltageIndex = PmhalVmGetVoltageIndex();

                /*
                 * Scan through all the OPPs of a given voltage domain and
                 * find the OPP for which the voltage matches the current
                 * voltage.
                 */
                for (i = PMHAL_VM_OPP_MIN;
                     ((FALSE == done) && (i < PMHAL_VM_OPP_MAX)); i++)
                {
                    opp = PmhalVmGetOppVoltage(vd, (uint32_t) i);
                    if (opp != NULL)
                    {
                        /* Check if voltage = boot voltage */
                        if (voltage == opp->nomVoltage[nomVoltageIndex])
                        {
                            *oppId = (pmhalVmOppId_t) vd->oppIdArr[i];
                            done   = TRUE;
                        }
                        else
                        {
                            avsVoltage = 0U;
                            if (opp->isAVSSupported == TRUE)
                            {
                                pmhalPrcmPmicRegulatorId_t regId =
                                    PmhalVmGetRegulatorId(voltDomId);
                                uint32_t checkVoltage;

                                avsVoltage = PMHALVMGetAVS0EfuseVoltage(
                                    voltDomId,
                                    (pmhalVmOppId_t) i);
                                checkVoltage =
                                    PMHALPmicGetConvRegulatorVoltage(regId,
                                                                     avsVoltage);
                                if (checkVoltage == voltage)
                                {
                                    *oppId = (pmhalVmOppId_t) vd->oppIdArr[i];
                                    done   = TRUE;
                                }
                            }
                        }
                    }
                }

                /*
                 * At system start-up, AVS may not be enabled so the above code
                 * will fail to find the OPP. Make a last attempt to check
                 * against the OPP_NOM range to see if it matches.
                 */
                if ((FALSE == done) &&
                    (voltage >= vd->minOppNommV) &&
                    (voltage <= vd->maxOppNommV))
                {
                    *oppId = (pmhalVmOppId_t) PMHAL_VM_OPP_NOM;
                    done   = TRUE;
                }
            }
        }
    }

    if ((PM_SUCCESS == retVal) && (FALSE == done))
    {
        retVal = PM_OPP_INVALID;
    }

    return retVal;
}

uint32_t PMHALVMGetAVS0EfuseVoltage(pmhalPrcmVdId_t voltDomId,
                                    pmhalVmOppId_t  oppId)
{
    pmErrCode_t retVal = PM_SUCCESS;
    uint32_t voltage = 0U; /* Initialize with error value */
    uint32_t nomVoltageIndex = 0U;
    const pmhalVmVoltageDomain_t *vd         = NULL;
    const pmhalVmOppVoltage_t    *oppVoltage = NULL;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);
    if (NULL == vd)
    {
        retVal = PM_INPUT_PARAM_BAD_VOLTAGE_ID;
    }
    else
    {
        oppVoltage = PmhalVmGetOppVoltage(vd, oppId);
        if (oppVoltage == NULL)
        {
            retVal = PM_BADARGS;
        }
    }

    /*
     * Make sure AVS is supported
     */
    if ((retVal == PM_SUCCESS) &&
        (oppVoltage != NULL)   &&
        (oppVoltage->isAVSSupported == 1U))
    {
        voltage = HW_RD_FIELD32(oppVoltage->fuseOPPVminRegAddr,
                                PMHAL_VM_STD_FUSE_OPP_VMIN_AVS0);
        /*
         * Some devices may not support all of the listed OPPs and
         * therefore will not have any value populated in the eFuse. In these
         * cases 0x0000 or 0xFFFF may be expected. This helper function returns
         * a 0U in such cases to be handled by the API appropriately.
         */
        if ((voltage == 0U) || (voltage == 0xFFFU))
        {
            nomVoltageIndex = PmhalVmGetVoltageIndex();
            if(oppVoltage->nomVoltage[nomVoltageIndex] != 0U)
            {
                /*
                 * If AVS Class-0U is not supported, use the Voltage
                 * from the OPP table if a valid nomVoltage is present.
                 */
                voltage = oppVoltage->nomVoltage[nomVoltageIndex];
            }
            else
            {
                /*
                 * If AVS is not supported for the given OPP and there is no
                 * valid nom voltage defined then returns 0U.
                 */
                voltage = 0U;
            }
        }

        /*
         * Make sure the voltage value is with-in the limits for the
         * voltage domain.
         */
        if ((voltage < vd->minSafemV) || (voltage > vd->maxSafemV))
        {
            voltage = 0U;
        }
    }
    else
    {
        voltage = 0U;
    }

    return voltage;
}

uint32_t PMHALVMIsABBEnabled(pmhalPrcmVdId_t voltDomId, pmhalVmOppId_t oppId)
{
    uint32_t fbbSel, oppSel;
    uint32_t retVal = 0U;
    const pmhalVmVoltageDomain_t *vd         = NULL;
    const pmhalVmOppVoltage_t    *oppVoltage = NULL;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);

    oppVoltage = PmhalVmGetOppVoltage(vd, oppId);

    if (oppVoltage != NULL)
    {
        fbbSel = HW_RD_FIELD32(oppVoltage->prmABBLDOSetupRegAddr,
                               PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL);
        oppSel = HW_RD_FIELD32(oppVoltage->prmABBLDOCtrlRegAddr,
                               PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL);

        if ((fbbSel != 0U) && (oppSel != 0U))
        {
            retVal = 1U;
        }
        else
        {
            retVal = 0U;
        }
    }

    return retVal;
}

void PMHALVMInitABB(pmhalPrcmVdId_t voltDomId, pmhalVmOppId_t oppId)
{
    uint32_t wtcnt;
    uint32_t setupValue = 0U;
    const pmhalVmVoltageDomain_t *vd  = NULL;
    const pmhalVmOppVoltage_t    *opp = NULL;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);

    opp = PmhalVmGetOppVoltage(vd, oppId);

    /*
     * The following ABB initialization steps are required to use ABB:
     * 1. Set up the WTCNT value (see PmhalVmGetWtCnt() for details)
     * 2. Set PRM_ABBLDO_<VD>_SETUP.SR2EN to 1
     * 3. Initialize PRM_ABBLDO_<VD>_SETUP.ACTIVE_FBB_SEL to 0U. This will
     *    be programmed as needed by the OPP change.
     * 4. Ensure PRM_ABBLDO_<VD>_SETUP.NOCAP is unchanged from reset value.
     *    This value is automatically loaded.
     * 5. Ensure all other bits are zero.
     */
    if ((opp != NULL) && (opp->prmABBLDOSetupRegAddr != 0U))
    {
        /*
         * Read the NOCAP bits and retain its value; clear all other bits.
         */
        setupValue  = HW_RD_REG32(opp->prmABBLDOSetupRegAddr);
        setupValue &= PRM_ABBLDO_DSPEVE_SETUP_NOCAP_MASK;

        /*
         * Set WTCNT and SR2EN fields and write the register value.
         */
        wtcnt       = PmhalVmGetWtCnt();
        setupValue |= wtcnt << PRM_ABBLDO_DSPEVE_SETUP_SR2_WTCNT_VALUE_SHIFT;
        setupValue |= (uint32_t) PRM_ABBLDO_DSPEVE_SETUP_SR2EN_FUNCTIONAL <<
                      PRM_ABBLDO_DSPEVE_SETUP_SR2EN_SHIFT;
        HW_WR_REG32(opp->prmABBLDOSetupRegAddr, setupValue);
    }
}

pmErrCode_t PMHALVMEnableABB(pmhalPrcmVdId_t voltDomId, pmhalVmOppId_t oppId)
{
    pmErrCode_t retVal                = PM_SUCCESS;
    uint32_t    timeout               = 0U;
    uint32_t    intOccurred           = 0U;
    const pmhalVmVoltageDomain_t *vd  = NULL;
    const pmhalVmOppVoltage_t    *opp = NULL;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);

    opp = PmhalVmGetOppVoltage(vd, oppId);

    if (opp == NULL)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /*
         * ABB Programming Overview:
         * -------------------------
         *
         * ABB LDO supports two modes, namely bypass mode and FBB mode.
         * The mode name FBB is used for historical reason but enabling
         * the FBB mode can result in Forward Body Bias (FBB) or
         * Reverse Body Bias (RBB) depending on the VSET_OUT value programmed.
         *
         * The following two registers are involved in ABB Programming:
         *
         * PRM_ABBLDO_<VD>_SETUP:
         * ----------------------
         *
         *    Bits     Field
         *    ----------------------------------------------------------------
         *     0U       SR2EN: Enable/Disable ABB power management.
         *                    This is setup as part of the ABB initialization.
         *               0x0: ABB LDO is put in bypass mode
         *               0x1: ABB is enabled
         *     1       Reserved
         *     2       ACTIVE_FBB_SEL: Defines ABB LDO mode. This is programmed
         *                             as part of enable/disable ABB.
         *               0x0: ABB LDO is in bypass mode
         *               0x1: ABB LDO is in FBB mode
         *     3       Reserved
         *     4       NO CAP: Wheter ABB LDO is cap-less or not
         *               0x0: ABB LDO uses an external capacitor
         *               0x1: ABB LDO doesn't use an external capacitor
         *     5-7     Reserved
         *     8-15    SR2_WTCNT_VALUE: LDO Settling time for active-mode OPP
         *             change. Target is 40 uSec for TDA2xx. This value is in
         *             16 system clock cycles.
         *     16-31   Reserved
         *
         * PRM_ABBLDO_<VD>_CTRL:
         * ---------------------
         *
         *    Bits     Field
         *    ----------------------------------------------------------------
         *     0U-1     OPP_SEL: Select the OPP at which the voltage domain is
         *                      operating. Only the following values are valid
         *                      for TDA2xx
         *               0x0: Nominal (default)
         *               0x1: Fast OPP
         *               0x2: Nominal
         *
         *     2       OPP_CHANGE: When set to 1, initiate an OPP-based ABBLDO
         *                         setting change
         *     3-4     SR2_STATUS: Indicate the current retVal
         *               0x0: ABB LDO is in bypass mode
         *               0x2: ABB LDO is in FBB active mode
         *     5       Reserved
         *     6       SR2_IN_TRANSITION: ABB LDO is in transition state or not
         *               0x0: Not in transition
         *               0x1: Is in transition and SR2_STATUS bits
         *                    are not stable.
         *     7-31    Reserved
         *
         * ABB Initialization:
         * -------------------
         * See PMHALVMInitABB() for details.
         *
         * NOTE: The initialization steps need to be performed only once
         *       at the system initialization; however, since we don't
         *       want to maintain state, we do the initialization every time.
         *
         * ABB Enable:
         * -----------
         *
         * To basic steps to enable ABB are:
         * 1. Set the ACTIVE_FBB_SEL bit to 1
         * 2. Set the OPP_SEL to 1 (to indicate Fast OPP)
         * 3. Program the ABB voltage in the LDOVBB<VD>_FBB_VSET_OUT field.
         * 4. Set the LDOVBB<VD>_FBB_MUX_CTRL to 1. The ABB voltage setting can
         *    be read from the efuse or the override value in the VOLTAGE_CTRL
         *    register. Setting this bit to 1 ensures the value from the
         *    VOLTAGE_CTRL register is used.
         * 5. Finally trigger the ABB LDO OPP change by setting OPP_CHANGE to 1
         *
         * Additionally the following needs to be ensured:
         * 1. Clear the ABB LDO transition completion interrupt before starting
         *    the enable sequence.
         * 2. Ensure OPP_CHANGE is zero (override if not) before setting the
         *    OPP_SEL.
         * 3. After triggering the OPP Change (step 5 above) wait for the
         *    transition to complete by checking the transition interrupt.
         */
        uint32_t abbVsetOut = 0U;
        uint32_t irqStatus  = 0U;

        PMHALVMInitABB(voltDomId, oppId);

        /*
         * Clear retVal of PRCM interrupt for ABB LDO transition completion.
         */
        HW_WR_REG32(opp->prmABBDoneIRQStatRegAddr, opp->prmABBDoneStatMask);

        /*
         * Set ABB LDO FBB mode.
         */
        HW_WR_FIELD32(opp->prmABBLDOSetupRegAddr,
                      PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL,
                      PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL_FBB);

        /*
         * Ensure OPP_CHANGE is set to 0U and set OPP_SEL to Fast OPP.
         */
        HW_WR_FIELD32(opp->prmABBLDOCtrlRegAddr,
                      PRM_ABBLDO_DSPEVE_CTRL_OPP_CHANGE,
                      0x0U);
        HW_WR_FIELD32(opp->prmABBLDOCtrlRegAddr, PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL,
                      PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_FASTOPP);

        /*
         * Read the ABB VSET value from the efuse and set the
         * LDOVBBxxxVSET_OUT filed in the register
         * CTRL_<CORE|WKUP>_LDOVBB_<domain>_VOLTAGE_CTRL.
         * Also ensure that this override VSET value is used by setting the
         * MUX.
         */
        abbVsetOut = HW_RD_FIELD32(opp->fuseOPPVminRegAddr,
                                   PMHAL_VM_STD_FUSE_OPP_VMIN_VSETABB);

        HW_WR_FIELD32(opp->ctrlLDOVBBVoltageCtrlRegAddr,
                      PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_VSET_OUT,
                      abbVsetOut);

        HW_WR_FIELD32(
            opp->ctrlLDOVBBVoltageCtrlRegAddr,
            PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL,
            PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL_OCP);

        /*
         * Start the ABB LDO OPP Change.
         */
        HW_WR_FIELD32(opp->prmABBLDOCtrlRegAddr,
                      PRM_ABBLDO_DSPEVE_CTRL_OPP_CHANGE, 0x1U);

        /*
         * Wait till the transition is complete by checking the DONE bit.
         * The transition takes 50us; use 100us timeout delay to gives some
         * buffer.
         */
        timeout     = 100U;
        intOccurred = 0U;
        while ((intOccurred == 0U) && (timeout != 0U))
        {
            PMUtilsMinDelayUS((uint32_t) 1U);
            intOccurred = HW_RD_REG32(opp->prmABBDoneIRQStatRegAddr) &
                          opp->prmABBDoneStatMask;
            timeout = timeout - 1U;
        }

        if (timeout == 0U)
        {
            retVal = PM_TIMEOUT;
        }

        /*
         * Clear interrupt retVal.
         */
        irqStatus  = HW_RD_REG32(opp->prmABBDoneIRQStatRegAddr);
        irqStatus |= opp->prmABBDoneStatMask;
        HW_WR_REG32(opp->prmABBDoneIRQStatRegAddr, irqStatus);
    }
    return retVal;
}

pmErrCode_t PMHALVMDisableABB(pmhalPrcmVdId_t voltDomId, pmhalVmOppId_t oppId)
{
    pmErrCode_t retVal                = PM_SUCCESS;
    uint32_t    timeout               = 0U;
    uint32_t    intOccurred           = 0U;
    const pmhalVmVoltageDomain_t *vd  = NULL;
    const pmhalVmOppVoltage_t    *opp = NULL;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);

    opp = PmhalVmGetOppVoltage(vd, oppId);

    if (opp == NULL)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        /*
         * See the ABB Programming Overview above.
         *
         * ABB Initialization:
         * -------------------
         * See PMHALVMInitABB() for details.
         *
         * NOTE: The initialization steps need to be performed
         *       only once at the system initialization; however,
         *       since we don't want to maintain state, we do
         *       the initialization every time.
         *
         * ABB Disable:
         * -----------
         *
         * To basic steps to leave ABB (entering bypass mode) are:
         * 1. Set the ACTIVE_FBB_SEL bit to 0U
         * 2. Set the OPP_SEL to 0U (to indicate bypass mode)
         * 3. Trigger the ABB LDO OPP change by setting OPP_CHANGE to 1
         * 4. Reset the VSET_OUT and FBB_MUX to 0U.
         *
         * Additionally the following needs to be ensured:
         * 1. Clear the ABB LDO transition completion interrupt
         *    before starting the enable sequence.
         * 2. Ensure OPP_CHANGE is zero (override if not) before setting the
         *    OPP_SEL.
         * 3. After triggering the OPP Change (step 5 above) wait for the
         *    transition to complete by checking the transition interrupt.
         */
        uint32_t irqStatus = 0U;

        /*
         * Clear retVal of PRCM interrupt for ABB LDO transition completion.
         */
        HW_WR_REG32(opp->prmABBDoneIRQStatRegAddr, opp->prmABBDoneStatMask);

        /*
         * Set ABB LDO FBB mode.
         */
        HW_WR_FIELD32(opp->prmABBLDOSetupRegAddr,
                      PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL,
                      PRM_ABBLDO_DSPEVE_SETUP_ACTIVE_FBB_SEL_BYPASS);

        /*
         * Ensure OPP_CHANGE is set to 0U and set OPP_SEL to Fast OPP.
         */
        HW_WR_FIELD32(opp->prmABBLDOCtrlRegAddr,
                      PRM_ABBLDO_DSPEVE_CTRL_OPP_CHANGE,
                      0x0U);
        HW_WR_FIELD32(opp->prmABBLDOCtrlRegAddr, PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL,
                      PRM_ABBLDO_DSPEVE_CTRL_OPP_SEL_DEFAULT_NOMINAL);

        /*
         * Start the ABB LDO OPP Change.
         */
        HW_WR_FIELD32(opp->prmABBLDOCtrlRegAddr,
                      PRM_ABBLDO_DSPEVE_CTRL_OPP_CHANGE, 0x1U);

        /*
         * Wait till the transition is complete by checking the DONE bit.
         * The transition takes 50us; use 100us timeout delay to gives some
         * buffer.
         */
        timeout     = 100U;
        intOccurred = 0U;
        while ((intOccurred == 0U) && (timeout != 0U))
        {
            PMUtilsMinDelayUS((uint32_t) 1U);
            intOccurred = HW_RD_REG32(opp->prmABBDoneIRQStatRegAddr) &
                          opp->prmABBDoneStatMask;
            timeout = timeout - 1U;
        }

        if (timeout == 0U)
        {
            retVal = PM_TIMEOUT;
        }

        /*
         * Clear interrupt retVal.
         */
        irqStatus  = HW_RD_REG32(opp->prmABBDoneIRQStatRegAddr);
        irqStatus |= opp->prmABBDoneStatMask;
        HW_WR_REG32(opp->prmABBDoneIRQStatRegAddr, irqStatus);

        /*
         * Set the LDOVBBxxxVSET_OUT field and the MUX to zero.
         */
        HW_WR_FIELD32(opp->ctrlLDOVBBVoltageCtrlRegAddr,
                      PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_VSET_OUT,
                      0x0U);

        HW_WR_FIELD32(
            opp->ctrlLDOVBBVoltageCtrlRegAddr,
            PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL,
            PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL_EFUSE);
    }
    return retVal;
}

uint32_t PMHALVMSetSramLdoRetState(pmhalPrcmVdId_t            voltDomId,
                                   pmhalPrcmSramLdoRetState_t retState)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    vd = PmhalVmGetVoltageDomain(voltDomId);

    if (NULL == vd)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        uint32_t compareVal = (uint32_t) ((uint32_t) 1U << (uint32_t) retState);
        if ((uint32_t) 0U != (compareVal & vd->sLdoValidRetMode))
        {
            uint32_t addr = vd->sldoCtrlAddr;
            if (PMHAL_REG_NOTAPPLICABLE != addr)
            {
                uint32_t fieldMask = ((uint32_t) 1U <<
                                      PMHAL_VM_SLDO_CTRL_RETMODE_ENABLE_SHIFT);
                uint32_t fieldShift = PMHAL_VM_SLDO_CTRL_RETMODE_ENABLE_SHIFT;

                HW_WR_FIELD32_RAW((uint32_t) addr,
                                  (uint32_t) fieldMask,
                                  (uint32_t) fieldShift, (uint32_t) retState);
            }
            else
            {
                retVal = PM_BADARGS;
            }
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }

    return retVal;
}

uint32_t PMHALVMGetSramLdoTransState(pmhalPrcmVdId_t               voltDomId,
                                     pmhalPrcmSramLdoTransState_t *transState)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    vd = PmhalVmGetVoltageDomain(voltDomId);

    if ((NULL == vd) || (NULL == transState))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        uint32_t addr = vd->sldoCtrlAddr;
        if (PMHAL_REG_NOTAPPLICABLE != addr)
        {
            uint32_t fieldMask = ((uint32_t) 1U <<
                                  PMHAL_VM_SLDO_CTRL_SRAM_IN_TRANSITION_SHIFT);
            uint32_t fieldShift = PMHAL_VM_SLDO_CTRL_SRAM_IN_TRANSITION_SHIFT;

            *transState = (pmhalPrcmSramLdoTransState_t)
                          HW_RD_FIELD32_RAW((uint32_t) addr,
                                            (uint32_t) fieldMask,
                                            (uint32_t) fieldShift);
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    return retVal;
}

uint32_t PMHALVMGetSramLdoStatus(pmhalPrcmVdId_t           voltDomId,
                                 pmhalPrcmSramLdoStatus_t *ldoStatus)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    vd = PmhalVmGetVoltageDomain(voltDomId);

    if ((NULL == vd) || (NULL == ldoStatus))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        uint32_t addr = vd->sldoCtrlAddr;
        if (PMHAL_REG_NOTAPPLICABLE != addr)
        {
            uint32_t fieldMask = ((uint32_t) 1U <<
                                  PMHAL_VM_SLDO_CTRL_SRAMLDO_STATUS_SHIFT);
            uint32_t fieldShift = PMHAL_VM_SLDO_CTRL_SRAMLDO_STATUS_SHIFT;

            *ldoStatus = (pmhalPrcmSramLdoStatus_t)
                         HW_RD_FIELD32_RAW((uint32_t) addr,
                                           (uint32_t) fieldMask,
                                           (uint32_t) fieldShift);
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    return retVal;
}

uint32_t PMHALVMSetSramLdoSetup(pmhalPrcmVdId_t voltDomId,
                                uint32_t        setupVal)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    vd = PmhalVmGetVoltageDomain(voltDomId);

    if (NULL == vd)
    {
        retVal = PM_BADARGS;
    }
    else
    {
        uint32_t addr = vd->sldoSetupAddr;
        if (PMHAL_REG_NOTAPPLICABLE != addr)
        {
            /* To find the mask for the valid bits in the register*/
            uint32_t maskForSetup =
                (uint32_t) ((uint32_t) 1U <<
                            PMHAL_PRCM_SLDO_SETUP_BIT_SHIFT_COUNT) - 1U;
            uint32_t valToWrite = setupVal & maskForSetup;

            HW_WR_REG32(addr, valToWrite);
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    return retVal;
}

uint32_t PMHALVMGetSramLdoSetup(pmhalPrcmVdId_t voltDomId,
                                uint32_t       *setupVal)
{
    pmErrCode_t retVal = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    vd = PmhalVmGetVoltageDomain(voltDomId);

    if ((NULL == vd) || (NULL == setupVal))
    {
        retVal = PM_BADARGS;
    }
    else
    {
        uint32_t addr = vd->sldoSetupAddr;
        if (PMHAL_REG_NOTAPPLICABLE != addr)
        {
            /* To find the mask for the valid bits in the register*/
            uint32_t maskForSetup =
                (uint32_t) ((uint32_t) 1U <<
                            PMHAL_PRCM_SLDO_SETUP_BIT_SHIFT_COUNT) - 1U;
            uint32_t valToRead = HW_RD_REG32(addr);
            *setupVal = valToRead & maskForSetup;
        }
        else
        {
            retVal = PM_BADARGS;
        }
    }
    return retVal;
}

pmErrCode_t PMHALVMGetDepCpuId(pmhalPrcmCpuId_t  cpuId,
                               pmhalPrcmCpuId_t *depCpuId)
{
    pmErrCode_t retVal = PM_SUCCESS;
    if (PMHAL_PRCM_CPU_ID_UNDEF < cpuId)
    {
        *depCpuId = pmhalDepCpuList[cpuId];
    }
    else
    {
        *depCpuId = PMHAL_PRCM_CPU_ID_UNDEF;
        retVal    = PM_BADARGS;
    }
    return retVal;
}

pmErrCode_t PMHALVMGetVoltageForOpp(pmhalPrcmVdId_t voltDomId,
                                    pmhalVmOppId_t  oppId,
                                    uint32_t       *voltage)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd  = NULL;
    const pmhalVmOppVoltage_t    *opp = NULL;
    uint32_t    nomVoltageIndex       = 0U;
    uint32_t    readVoltage;

    /*
     * Check if the voltage domain id is valid and the OPP ID is valid
     * for this voltage domain.
     * PmhalVmGetVoltageDomain will return null if voltDomId is out of range.
     * PmhalVmGetOppVoltage will return null if vd is null or oppId
     * is out of range.
     */
    vd = PmhalVmGetVoltageDomain(voltDomId);

    opp = PmhalVmGetOppVoltage(vd, oppId);

    if (opp == NULL)
    {
        if (NULL == vd)
        {
            status = PM_INPUT_PARAM_BAD_VOLTAGE_ID;
        }
        else
        {
            status = PM_BADARGS;
        }
    }
    else
    {
        pmhalPrcmPmicRegulatorId_t regId =
            PmhalVmGetRegulatorId(voltDomId);
        nomVoltageIndex = PmhalVmGetVoltageIndex();
        readVoltage     = 0U;
        if (opp->isAVSSupported == TRUE)
        {
            readVoltage = PMHALVMGetAVS0EfuseVoltage(voltDomId,
                                                     (pmhalVmOppId_t) oppId);
        }
        else
        {
            readVoltage = opp->nomVoltage[nomVoltageIndex];
        }
        *voltage = PMHALPmicGetConvRegulatorVoltage(regId, readVoltage);
    }
    return status;
}

pmErrCode_t PMHALVMGetCpuInVoltageDomain(pmhalPrcmVdId_t    voltDomId,
                                         pmhalPrcmCpuId_t **cpuIdArray,
                                         uint32_t          *numCpus)
{
    pmErrCode_t status = PM_SUCCESS;
    const pmhalVmVoltageDomain_t *vd = NULL;
    vd = PmhalVmGetVoltageDomain(voltDomId);
    if (NULL == vd)
    {
        status = PM_BADARGS;
    }
    else
    {
        *cpuIdArray = vd->cpuIdArr;
        *numCpus    = vd->numCpus;
    }
    return status;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static uint32_t PmhalVmGetWtCnt(void)
{
    /*
     * The formula is as follows:
     * wtcnt = LDO settling time / (number of sys_clk cycles / SYS_CLK_RATE)
     *
     * where LDO settling time for TRA2xx is 50 uSec,
     * number of sys_clk cycles is 16  AND
     * the SYS_CLK rate is as configured by the application and can be one
     * of the following values in MHz: 12, 13, 19.2, 20, 26, 38.4
     *
     * NOTE: At present this function hard codes the sys_clk frequency
     * of 20MHz as the SBL sets this sys_clk frequency. This needs to be
     * updated to query the PRCM HAL once this API is implemented in
     * PRCM HAL.
     *
     * WTCNT values table
     *
     *      SYS_CLK (MHz)            WTCNT Value
     *      ------------------------------------
     *          12                     0x26
     *          13                     0x29
     *          19.2                   0x3C
     *          20                     0x3D
     *          26                     0x52
     *          38.4                   0x78
     */

    uint32_t wtCntVal;
    uint32_t sysClk;

    sysClk = PMHALCMGetSysClockFreq();

    wtCntVal = (((uint32_t) sysClk *
                 PMHAL_VM_ABB_SR2_WTCNT_TIME) /
                (16U * 1000U));

    return wtCntVal;
}

static uint32_t PmhalVmGetVoltageIndex(void)
{
    uint32_t nomVoltageIndex = 0U;
    uint32_t packageType     =
        HW_RD_FIELD32(PMHAL_VM_PACKAGE_READ_ADDR, PMHAL_VM_PACKAGE_BIT);
    if (PMHAL_VM_PACKAGE_TYPE_0 == packageType)
    {
        nomVoltageIndex = 1U;
    }
    else
    {
        nomVoltageIndex = 0U;
    }
    return nomVoltageIndex;
}

