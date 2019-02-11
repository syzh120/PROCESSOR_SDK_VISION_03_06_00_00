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
 * \file pmhal/tda2xx/hw_pmhal_vmdata.h
 *
 * \brief   This file contains the APIs to access the voltage domain structure.
 */

#ifndef HW_PMHAL_VM_DATA_
#define HW_PMHAL_VM_DATA_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "hw_pmhal_common_vmdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Common Macro for LDOVBBDSPEVE_FBB_VSET_OUT Mask */
#define PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_VSET_OUT_MASK \
    (CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_VSET_OUT_MASK)

/** \brief Common Macro for LDOVBBDSPEVE_FBB_VSET_OUT Shift */
#define PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_VSET_OUT_SHIFT \
    (CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_VSET_OUT_SHIFT)

/** \brief Common Macro for FBB_MUX_CTRL Mask */
#define PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL_MASK \
    (CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_MASK)

/** \brief Common Macro for FBB_MUX_CTRL Shift */
#define PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL_SHIFT \
    (CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_SHIFT)

/** \brief Common Macro for FBB_MUX_CTRL OCP Value*/
#define PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL_OCP \
    (CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_OCP)

/** \brief Common Macro for FBB_MUX_CTRL EFUSE Value*/
#define PMHAL_VM_LDOVBB_VOLTAGE_CTRL_FBB_MUX_CTRL_EFUSE \
    (CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_EFUSE)

/** \brief Device Package read address */
#define PMHAL_VM_PACKAGE_READ_ADDR \
    (SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE + CTRL_WKUP_STD_FUSE_DIE_ID_2)

/** \brief Device Package read Shift */
#define PMHAL_VM_PACKAGE_BIT_SHIFT (16U)

/** \brief Device Package read Mask */
#define PMHAL_VM_PACKAGE_BIT_MASK  (0x30000U)

/** \brief Package Type 1: Corresponds to 17x17 package */
#define PMHAL_VM_PACKAGE_TYPE_0 (1U)

/** \brief Package Type 2: Corresponds to 23x23 package */
#define PMHAL_VM_PACKAGE_TYPE_1 (2U)

/** \brief Minimum Voltage that the SOC can support */
#define PMHAL_VM_MIN_SOC_VOLTAGE   (850U)

/** \brief Maximum Voltage that the SOC can support */
#define PMHAL_VM_MAX_SOC_VOLTAGE   (1250U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif

