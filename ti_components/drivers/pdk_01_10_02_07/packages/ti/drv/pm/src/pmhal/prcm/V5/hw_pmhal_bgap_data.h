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
 * \file    pmhal/V5/hw_pmhal_bgap_data.h
 *
 * \brief   This file contains the APIs to access the ADC to Temperature Mapping
 *          and vice versa.
 */

#ifndef HW_PMHAL_BGAP_DATA_H_
#define HW_PMHAL_BGAP_DATA_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Common shift for the THOLD COLD value */
#define PMHAL_BGAP_THOLD_COLD_SHIFT \
    (CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_COLD_MPU_SHIFT)

/** \brief Common shift for the THOLD HOT value */
#define PMHAL_BGAP_THOLD_HOT_SHIFT \
    (CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_HOT_MPU_SHIFT)

/** \brief Common mask for the THOLD COLD value */
#define PMHAL_BGAP_THOLD_COLD_MASK \
    (CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_COLD_MPU_MASK)

/** \brief Common mask for the THOLD HOT value */
#define PMHAL_BGAP_THOLD_HOT_MASK \
    (CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_HOT_MPU_MASK)

/** \brief Common Shift for the FSM conversion count */
#define PMHAL_BGAP_DTEMP_TAG_SHIFT \
    (CTRL_CORE_DTEMP_MPU_0_DTEMP_TAG_MPU_0_SHIFT)

/** \brief Common Mask for the FSM conversion count */
#define PMHAL_BGAP_DTEMP_TAG_MASK \
    (CTRL_CORE_DTEMP_MPU_0_DTEMP_TAG_MPU_0_MASK)

/** \brief Common Max value for the DTEMP TAG */
#define PMHAL_BGAP_DTEMP_TAG_MAX_VALUE \
    (PMHAL_BGAP_DTEMP_TAG_MASK >> PMHAL_BGAP_DTEMP_TAG_SHIFT)

/** \brief Common shift for the Temperature to be read */
#define PMHAL_BGAP_DTEMP_TEMPERATURE_SHIFT \
    (CTRL_CORE_DTEMP_MPU_0_DTEMP_TEMPERATURE_MPU_0_SHIFT)

/** \brief Common Mask for the Temperature to be read */
#define PMHAL_BGAP_DTEMP_TEMPERATURE_MASK \
    (CTRL_CORE_DTEMP_MPU_0_DTEMP_TEMPERATURE_MPU_0_MASK)

/** \brief Minimum supported ADC value. */
#define PMHAL_BGAP_MIN_ADC_VALUE          (540U)

/** \brief Minimum supported Temperature Value */
#define PMHAL_BGAP_MIN_TEMP_VALUE         (-40000)

/** \brief Maximum supported ADC value. */
#define PMHAL_BGAP_MAX_ADC_VALUE          (945U)

/** \brief Max supported Temperature Value */
#define PMHAL_BGAP_MAX_TEMP_VALUE         (125000)

/** \brief Number of valid ADC value to temperature range mapping */
#define PMHAL_BGAP_TOTAL_ADC_SUPPORTED \
    (PMHAL_BGAP_MAX_ADC_VALUE - PMHAL_BGAP_MIN_ADC_VALUE + 1U)

/** \brief Temperature sensor EOCZ mask */
#define PMHAL_BGAP_TEMP_SENSOR_EOCZ_MASK \
    (CTRL_CORE_TEMP_SENSOR_MPU_BGAP_EOCZ_MPU_MASK)

/** \brief Temperature sensor EOCZ shift */
#define PMHAL_BGAP_TEMP_SENSOR_EOCZ_SHIFT \
    (CTRL_CORE_TEMP_SENSOR_MPU_BGAP_EOCZ_MPU_SHIFT)

/** \brief Temperature sensor DTEMP mask */
#define PMHAL_BGAP_TEMP_SENSOR_DTEMP_MASK \
    (CTRL_CORE_TEMP_SENSOR_MPU_BGAP_DTEMP_MPU_MASK)

/** \brief Temperature sensor DTEMP shift */
#define PMHAL_BGAP_TEMP_SENSOR_DTEMP_SHIFT \
    (CTRL_CORE_TEMP_SENSOR_MPU_BGAP_DTEMP_MPU_SHIFT)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

typedef struct pmhalBgapVoltDomBandgapData
{
    uint32_t tempSensorAddr;
    /**< Temperature Sensor Register Address */
    uint32_t bandgapMaskAddr;
    /**< Band gap Mask Register Address */
    uint8_t  bandgapMaskColdShift;
    /**< Band Gap Mask Register Cold Mask Shift */
    uint8_t  bandgapMaskClearAccShift;
    /**< Band Gap mask register Clear Accumulator Shift */
    uint32_t bandgapThreshAddr;
    /**< Band Gap Threshold Address for THOLD Alert */
    uint32_t bandgapStatusAddr;
    /**< Band Gap Status Register Address */
    uint8_t  bandgapColdEvtStatusShift;
    /**< Band Gap Status Register Cold Event Shift */
    uint32_t bandgapDtempFifo0Addr;
    /**< Band Gap DTEMP FIFO 0 Address */
} pmhalBgapVoltDomBandgapData_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/** Array of Bgap ADC Elements  */
extern const pmhalBgapRange_t gPmhalBgapAdcMap[
    PMHAL_BGAP_TOTAL_ADC_SUPPORTED];

/** Array of Bgap Voltage Elements  */
extern const pmhalBgapVoltDomBandgapData_t gPmhalBgapVoltDomBandgapData[
    PMHAL_BGAP_NUM_FSM];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Returns the pointer to the temperature range for the given ADC value
 *        read from the register.
 *
 * \param adcValue       ADC Value read from the register.
 *
 * \return currTempRange Pointer to the temperature range as stored in the LUT.
 *                       NULL if ADC value is not in the supported range.
 **/
const pmhalBgapRange_t *PmhalBgapGetTemperatureRange(uint32_t adcValue);

/**
 * \brief Returns the pointer to the temperature range for the given ADC value
 *        read from the register.
 *
 * \param tempInMilliDegree Temperature in milli degree Celsius.
 *
 * \return adcValue         Corresponding ADC Value read for a valid temperature
 *                          0 - If the temperature range is not supported.
 **/
uint32_t PmhalBgapGetAdcValue(int32_t tempInMilliDegree);

#ifdef __cplusplus
}
#endif

#endif

