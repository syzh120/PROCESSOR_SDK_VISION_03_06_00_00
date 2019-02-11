/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2017
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
 *  \defgroup PM_HAL PMHAL
 *
 *  PMHAL provides low level APIs which allow:
 *      - Programming PRCM registers
 *          - Power Domain Manager (PDM)
 *          - Clock Domain Manager (CM)
 *          - Reset Manager (RM)
 *          - Module Manager (MM)
 *      - Programming Temperature Sensor Registers (Temp)
 *      - Programming Voltage Domain AVS and ABB (VM)
 *      - Programming board specific PMIC
 *
 */
 
/**
 *  \file      pmhal.h
 *
 *  \brief     This file contains all includes related to PM Hardware
 *             abstraction layer.
 *
 */

#ifndef PMHAL_TOP_H_
#define PMHAL_TOP_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/prcm/hw_pmhal_data_names.h>
#include <ti/drv/pm/include/prcm/pmhal_bgap.h>
#include <ti/drv/pm/include/prcm/pmhal_clocktree.h>
#include <ti/drv/pm/include/prcm/pmhal_cm.h>
#include <ti/drv/pm/include/prcm/pmhal_i2cComm.h>
#include <ti/drv/pm/include/prcm/pmhal_ina226.h>
#include <ti/drv/pm/include/prcm/pmhal_mm.h>
#include <ti/drv/pm/include/prcm/pmhal_mpu_lprm.h>
#include <ti/drv/pm/include/prcm/pmhal_pdm.h>
#include <ti/drv/pm/include/prcm/pmhal_pmic.h>
#include <ti/drv/pm/include/prcm/pmhal_pmicComm.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm_includes.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm_modinc.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm_stats.h>
#include <ti/drv/pm/include/prcm/pmhal_prm_int.h>
#include <ti/drv/pm/include/prcm/pmhal_rm.h>
#include <ti/drv/pm/include/prcm/pmhal_sd.h>
#include <ti/drv/pm/include/prcm/pmhal_vm.h>
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
#include <ti/drv/pm/include/prcm/pmhal_videopll.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_TOP_H_ */

