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
 * \file hw_pmhal_common_vmdata.h
 *
 * \brief   This file contains the APIs to access the voltage domain structure.
 */

#ifndef HW_PMHAL_VM_COMMON_DATA_
#define HW_PMHAL_VM_COMMON_DATA_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "pmhal_prcm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Mask for the AVS Class-0 Voltage in mV of
 *          STD_FUSE_OPP_VMIN register*/
#define PMHAL_VM_STD_FUSE_OPP_VMIN_AVS0_MASK          (0x0FFFU)

/** \brief Shift for the AVS Class-0 Voltage in mV of
 *          STD_FUSE_OPP_VMIN register*/
#define PMHAL_VM_STD_FUSE_OPP_VMIN_AVS0_SHIFT         (0U)

/** \brief Mask for the VSETABB - The ABB LDO voltage of
 *          STD_FUSE_OPP_VMIN register*/
#define PMHAL_VM_STD_FUSE_OPP_VMIN_VSETABB_MASK       (0x1F00000U)

/** \brief Shift for the VSETABB - The ABB LDO voltage of
 *          STD_FUSE_OPP_VMIN register*/
#define PMHAL_VM_STD_FUSE_OPP_VMIN_VSETABB_SHIFT      (20U)

/** \brief Mask for the ABBEN - Enable bit for ABB of
 *          STD_FUSE_OPP_VMIN register*/
#define PMHAL_VM_STD_FUSE_OPP_VMIN_ABBEN_MASK         (0x2000000U)

/** \brief Shift for the ABBEN - Enable bit for ABB of
 *          STD_FUSE_OPP_VMIN register*/
#define PMHAL_VM_STD_FUSE_OPP_VMIN_ABBEN_SHIFT        (25U)

/** \brief Min percentage value of the AVS voltage for
 *          a given OPP is 3.5% less. Divide by 1000 when using this macro */
#define PMHAL_VM_AVS_MIN_VOLTAGE_AVS_PERCENTAGE          (1000U - 35U)

/** \brief Max percentage value of the AVS voltage for
 *          a given OPP is 5% more. Divide by 1000 when using this macro */
#define PMHAL_VM_AVS_MAX_VOLTAGE_AVS_PERCENTAGE          (1000U + 50U)

/** \brief  ABB Wait Count Value. This determines how many microseconds ABB LDO
 *          waits in-order to achieve the targeted voltage on the ABB LDO.
 */
#define PMHAL_VM_ABB_SR2_WTCNT_TIME (50U)

/** \brief Common Shift for SLDO_CTRL Register RETMODE_ENABLE */
#define PMHAL_VM_SLDO_CTRL_RETMODE_ENABLE_SHIFT \
    (PRM_SLDO_CORE_CTRL_RETMODE_ENABLE_SHIFT)

/** \brief Common Shift for SLDO_CTRL Register SRAMLDO_STATUS */
#define PMHAL_VM_SLDO_CTRL_SRAMLDO_STATUS_SHIFT \
    (PRM_SLDO_CORE_CTRL_SRAMLDO_STATUS_SHIFT)

/** \brief Common Shift for SLDO_CTRL Register SRAM_IN_TRANSITION */
#define PMHAL_VM_SLDO_CTRL_SRAM_IN_TRANSITION_SHIFT \
    (PRM_SLDO_CORE_CTRL_SRAM_IN_TRANSITION_SHIFT)

/** \brief Number of packages for device */
#define PMHAL_VM_NUM_PACKAGES               (2U)

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Voltage specific details of an Operating Performance Point (OPP)
 */
typedef struct pmhalVmOppVoltage
{
    uint16_t nomVoltage[PMHAL_VM_NUM_PACKAGES];
    /**< The nominal voltage of the OPP/VD. */

    uint32_t fuseOPPVminRegAddr;
    /**< The efuse register to read the AVS class-0 and ABB voltages. */

    uint32_t prmABBDoneIRQStatRegAddr;
    /**< This register provides status on interrupt events. This register
     *   varies for IPU vs. MPU and the right address needs to be set
     *   depending on where the code is executing. */

    uint32_t prmABBDoneStatMask;
    /**< The bit mask of the DONE_ST status in the IRQ Status Register. */

    uint32_t prmABBLDOSetupRegAddr;
    /**< The control register to enable/disable ABB. */

    uint32_t prmABBLDOCtrlRegAddr;
    /**< The control register to configure ABB. */

    uint32_t ctrlLDOVBBVoltageCtrlRegAddr;
    /**< The control register to set the ABB voltage (VSET_OUT). */

    uint8_t  isAVSSupported;
    /**< True if AVS is supported for this OPP */

    uint8_t  isABBSupported;
    /**< True if ABB is supported for this OPP */
} pmhalVmOppVoltage_t;

/**
 * \brief  Voltage Domain descriptor
 */
typedef struct pmhalVmVoltageDomain
{
    uint16_t                   minSafemV;
    /**< Minimum safe voltage in mV. The SoC doesn't support voltage less
     *   than this. */

    uint16_t                   maxSafemV;
    /**< Maximum safe voltage in mV. The SoC doesn't support voltage greater
     *   than this. */

    uint16_t                   minOppNommV;
    /**< Minimum OPP_NOM voltage in mV. */

    uint16_t                   maxOppNommV;
    /**< Maximum OPP_NOM voltage in mV. */

    uint32_t                   sldoSetupAddr;
    /**< Address of the register to set the corresponding voltage domain's
     *   SRAM LDO Setup */

    uint32_t                   sldoCtrlAddr;
    /**< Address of the register to set the corresponding voltage domain's
     *   SRAM LDO Control */

    uint32_t                   sLdoValidRetMode;
    /**< One Hot encoding of the valid SRAM LDO Retention states supported
     *   Refer #pmhalPrcmSramLdoRetState_t for more details */

    const pmhalVmOppVoltage_t *oppVoltages[PMHAL_VM_OPP_MAX];
    /**< The nominal voltage of each OPP supported in this VD.
     *   Some OPPs are only supported in AVS. A value of zero means that
     *   the OPP is not supported. */

    uint32_t                   oppIdArr[PMHAL_VM_OPP_MAX];
    /**< Not all voltage domains have all OPPs supported. The elements of this
     *   array ensure the getOPP function returns the right value of the opp
     *   while searching through the array */
    pmhalPrcmCpuId_t          *cpuIdArr;
    /**< Array which lists the CPUs in the given voltage domain */
    uint32_t                   numCpus;
    /**< Number of CPUs in the given voltage domain */
} pmhalVmVoltageDomain_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/**< Array of Voltage Domain Elements  */
extern const pmhalVmVoltageDomain_t gPmhalVmDomains[PMHAL_PRCM_VD_COUNT];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief            Read the voltage domain array structure.
 *
 *
 * \param vId       Voltage domain ID
 *                   Refer Enum #pmhalPrcmVdId_t
 *
 * \return vd        Pointer to voltage domain
 **/
const pmhalVmVoltageDomain_t *PmhalVmGetVoltageDomain(uint32_t vId);

/**
 * \brief            Get the OPP Voltages
 *
 *
 * \param vd          Pointer to voltage domain
 * \param oppId       The Operating point ID
 *                    Refer Enum #pmhalVmOppId_t
 *
 * \return oppVoltage Pointer to Opp structure in the voltage domain
 *
 **/
const pmhalVmOppVoltage_t *PmhalVmGetOppVoltage(
    const pmhalVmVoltageDomain_t *vd,
    uint32_t                      oppId
    );

/**
 * \brief  Return the PMIC regulator given a voltage domain.
 *
 * \param voltDomId  Voltage domain ID
 *                   Refer Enum #pmhalPrcmVdId_t for values.
 *
 * \return regId     The PMIC regulator ID. Refer #pmhalPrcmPmicRegulatorId_t
 *                   for details.
 */
pmhalPrcmPmicRegulatorId_t PmhalVmGetRegulatorId(pmhalPrcmVdId_t voltDomId);

#ifdef __cplusplus
}
#endif

#endif

