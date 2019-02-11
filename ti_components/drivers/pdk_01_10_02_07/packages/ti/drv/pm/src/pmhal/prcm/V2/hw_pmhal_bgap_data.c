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
 * \file hw_pmhal_bgap_data.c
 *
 * \brief   Band gap Temperature Sensor data for the different voltage domains
 *          is defined in this file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include "pmhal_bgap.h"
#include "hw_pmhal_bgap_data.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**< \brief Global Structure to store the Temperature Band Gap Sensors data
 *          arranged based on the voltage domain.
 */
const pmhalBgapVoltDomBandgapData_t gPmhalBgapVoltDomBandgapData[
    PMHAL_BGAP_NUM_FSM] =
{
    /* PMHAL_PRCM_VD_CORE */
    {
        (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_TEMP_SENSOR),
        /* tempSensorAddr             */
        (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_BANDGAP_MASK_1),
        /* bandgapMaskAddr            */
        CTRL_CORE_BANDGAP_MASK_1_COLD_SHIFT,
        /* bandgapMaskColdShift       */
        CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_SHIFT,
        /* bandgapMaskClearAccShift   */
        (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_BANDGAP_THRESHOLD),
        /* bandgapThreshAddr      */
        (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_BANDGAP_STATUS_1),
        /* bandgapStatusAddr          */
        CTRL_CORE_BANDGAP_STATUS_1_COLD_SHIFT,
        /* bandgapColdEvtStatusShift  */
        (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
         CTRL_CORE_DTEMP_0)
        /* bandgapDtempFifo0Addr      */
    }
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* None */

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

