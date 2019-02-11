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
 *  \ingroup PM_HAL PM HAL API
 *  \defgroup TEMPERATURE Temperature Configuration
 *   The Temperature (BGAP) HAL Configuration provides API to read the junction
 *   temperature of the different BGAP temperature sensors available in the SoC.
 *   This HAL allows setting of the right threshold values for the Temperature
 *   hot and cold interrupts.
 *
 * @{
 */

/**
 *  \file  pmhal_bgap.h
 *
 *  \brief This file contains the interface declaration for the Temperature HAL.
 *
 *           The Temperature HAL supports the following features:
 *         - To return the temperature of a given voltage domain.
 *         - To return the average voltage of a given voltage domain since the
 *           last clear accumulator.
 *         - To clear the fifo & accumulator of the band gap temperature sensors
 *         - To freeze the update of the band gap FIFOs of the desired voltage
 *           domain.
 *         - To mask/unmask the hot event for the given voltage rail.
 *         - To set the desired delay between two temperature measurements.
 *         - To set the desired sidle mode for the band gap sensors.
 *         - To set the band gap threshold hot and cold value for the alert
 *           operation.
 *         - To check if a given voltage domain has the hot/cold alert set.
 *         - To read the fifo entries for a given voltage domain. Return the
 *           fifo entry one is looking for.
 */

#ifndef PMHAL_BGAP_H_
#define PMHAL_BGAP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
/** \brief Max number of FIFOs supported */
#define PMHAL_BGAP_MAX_NUM_FIFOS           (5U)

/** \brief Number of FSMs for Temperature Sensors */
#define PMHAL_BGAP_NUM_FSM                  (5U)

#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)

/** \brief Max number of FIFOs supported */
#define PMHAL_BGAP_MAX_NUM_FIFOS            (1U)

/** \brief Number of FSMs for Temperature Sensors */
#define PMHAL_BGAP_NUM_FSM                  (1U)

#endif
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief FSM delay counter (COUNTER_DELAY) valid values
 */
typedef enum pmhalBgapBandgapCntDelay
{
    PMHAL_BGAP_BAND_GAP_IMMEDIATE = 0x0U,
    /**< Immediately start the temperature measurement */
    PMHAL_BGAP_BAND_GAP_1_MS = 0x1U,
    /**< Start the temperature measurement after 1 ms*/
    PMHAL_BGAP_BAND_GAP_10_MS = 0x2U,
    /**< Start the temperature measurement after 10 ms*/
    PMHAL_BGAP_BAND_GAP_100_MS = 0x3U,
    /**< Start the temperature measurement after 100 ms*/
    PMHAL_BGAP_BAND_GAP_250_MS = 0x4U,
    /**< Start the temperature measurement after 250 ms*/
    PMHAL_BGAP_BAND_GAP_500_MS = 0x5U,
    /**< Start the temperature measurement after 500 ms*/
    PMHAL_BGAP_BAND_GAP_MAX = PMHAL_BGAP_BAND_GAP_500_MS + 1U
                              /**< Max temperature measurement delay */
} pmhalBgapBandgapCntDelay_t;

/**
 * \brief Band Gap Sensor valid SIDLE modes. The SIDLE modes for BGAP sensor is
 *        different than the other modules on the basis of the actual value to
 *        be programmed in the register. Hence use this enumeration and not
 *        the module mode SIDLE.
 */
typedef enum pmhalBgapBandgapSIdleMode
{
    PMHAL_BGAP_BAND_GAP_NO_IDLE = 0x0U,
    /**< Band Gap Sensor no idle mode */
    PMHAL_BGAP_BAND_GAP_FORCE_IDLE = 0x1U,
    /**< Band Gap Sensor force idle mode */
    PMHAL_BGAP_BAND_GAP_SMART_IDLE = 0x2U,
    /**< Band Gap Sensor smart idle mode */
    PMHAL_BGAP_BAND_GAP_MAX_SIDLE =
        PMHAL_BGAP_BAND_GAP_SMART_IDLE + 1U
        /**< Max allowed Slave Idle mode */
} pmhalBgapBandgapSIdleMode_t;

/**
 * \brief  Temperature Range for a given ADC value.
 */
typedef struct pmhalBgapRange
{
    int32_t minTemp;
    /**< Minimum temperature value of the range of temperatures which
     *  correspond to the ADC value in milli degree Celsius.
     */
    int32_t maxTemp;
    /**< Maximum temperature value of the range of temperatures which correspond
     *   to the ADC value in milli degree Celsius.
     */
} pmhalBgapRange_t;

/**
 * \brief  Temperature Sensor FIFO Entry
 */
typedef struct pmhalBgapFifoEntry
{
    uint32_t dtempTag;
    /**< FIFO entries maintained by the BGAP FSM */
    uint32_t dtempValue;
    /**< Value of the temperature measured  */
} pmhalBgapFifoEntry_t;

/* ========================================================================== */
/*                      Global Variables Declarations                         */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/** \brief  Get the Band gap Temperature Sensor value for a given voltage domain
 *
 *  \param  voltId          Unique voltage domain ID. Refer enum
 *                          #pmhalPrcmVdId_t for details.
 *  \param  currTempRange   Pointer to the current temperature range. Gives the
 *                          max and min temperature which corresponds to the
 *                          read ADC value.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS   If the temperature is read correctly.
 *                        - #PM_BADARGS   If the voltage ID is invalid.
 */
int32_t PMHALBgapGetCurrTemperature(pmhalPrcmVdId_t   voltId,
                                    pmhalBgapRange_t *currTempRange);

/** \brief  Clear the accumulator and the FIFO entries of the band gap
 *          temperature sensors.
 *
 *  \param  voltId          Unique voltage domain ID. Refer enum
 *                          #pmhalPrcmVdId_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS   If the sensor read registers are
 *                                       cleared correctly.
 *                        - #PM_BADARGS   If the voltage ID is invalid.
 */
int32_t PMHALBgapClearState(pmhalPrcmVdId_t voltId);

/** \brief  Enable a Hot alert event for the threshold temperature set by the
 *          API PMHALBgapSetHotThreshold.
 *
 *  \param  voltId          Unique voltage domain ID. Refer enum
 *                          #pmhalPrcmVdId_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS   If the hot event is enabled correctly.
 *                        - #PM_BADARGS   If the voltage ID is invalid.
 */
int32_t PMHALBgapEnableHotEvent(pmhalPrcmVdId_t voltId);

/** \brief  Disable a Hot alert event for the threshold temperature set by the
 *          API PMHALBgapSetHotThreshold.
 *
 *  \param  voltId          Unique voltage domain ID. Refer enum
 *                          #pmhalPrcmVdId_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS  If the hot event is disabled correctly.
 *                        - #PM_BADARGS  If the voltage ID is invalid.
 */
int32_t PMHALBgapDisableHotEvent(pmhalPrcmVdId_t voltId);

/** \brief  Enable a Cold alert event for the threshold temperature set by the
 *          API PMHALBgapSetColdThreshold.
 *
 *  \param  voltId          Unique voltage domain ID. Refer enum
 *                          #pmhalPrcmVdId_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS  If the cold event is enabled correctly.
 *                        - #PM_BADARGS  If the voltage ID is invalid.
 */
int32_t PMHALBgapEnableColdEvent(pmhalPrcmVdId_t voltId);

/** \brief  Disable a Cold alert event for the threshold temperature set by the
 *          API PMHALBgapSetColdThreshold.
 *
 *  \param  voltId          Unique voltage domain ID. Refer enum
 *                          #pmhalPrcmVdId_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS  If the cold event is disabled correctly
 *                        - #PM_BADARGS  If the voltage ID is invalid.
 */
int32_t PMHALBgapDisableColdEvent(pmhalPrcmVdId_t voltId);

/** \brief  The start of temperature measurement is initiated automatically
 *          by each FSM after it goes out of reset state. To control the main
 *          delay between two measurements the CTRL_CORE_BANDGAP_MASK_1[29:27]
 *          COUNTER_DELAY bit field is used. This API sets this field.
 *
 *  \param  tDelay          Unique delay value ID. Refer enum
 *                          #pmhalBgapBandgapCntDelay_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS   If the delay is programmed correctly.
 *                        - #PM_BADARGS   If the delay is not supported.
 */
int32_t PMHALBgapSetMeasureDelay(pmhalBgapBandgapCntDelay_t tDelay);

/** \brief  The Temperature Sensors FSMs comply with the PRCM slave idle
 *          protocol. They share common functional clock (L3INSTR_TS_GCLK),
 *          which is automatically gated by PRCM depending on the value of the
 *          CTRL_CORE_BANDGAP_MASK_1[31:30] SIDLEMODE bit field. This field is
 *          set by this API.
 *
 *  \param  mode            Unique idle mode to be set . Refer enum
 *                          #pmhalBgapBandgapSIdleMode_t for details.
 *
 *  \return status          Status of the API call.
 *                        - #PM_SUCCESS  If the slave idle mode is programmed
 *                                       correctly.
 *                        - #PM_BADARGS  If the slave idle mode is not supported
 */
int32_t PMHALBgapSetSIldeMode(pmhalBgapBandgapSIdleMode_t mode);

/** \brief  This API configures the high temperature threshold for generating
 *          thermal alerts through programming the
 *          CTRL_CORE_BANDGAP_THRESHOLD_x[25:16] THOLD_HOT_x bit fields.
 *
 *  \param  voltId              Unique voltage domain ID. Refer enum
 *                              #pmhalPrcmVdId_t for details.
 *  \param  tempInMilliDegree   Temperature Threshold in milli Degree Celsius.
 *
 *  \return status              Status of the API call.
 *                            - #PM_SUCCESS   If the threshold is programmed
 *                                           correctly.
 *                            - #PM_BADARGS   If the voltage domain is not
 *                                           correct or the temperature is
 *                                           out of the range supported.
 */
int32_t PMHALBgapSetHotThreshold(pmhalPrcmVdId_t voltId,
                                 int32_t         tempInMilliDegree);

/** \brief  This API configures the Low temperature threshold for generating
 *          thermal alerts through programming the
 *          CTRL_CORE_BANDGAP_THRESHOLD_x[25:16] THOLD_COLD_x bit fields.
 *
 *  \param  voltId              Unique voltage domain ID. Refer enum
 *                              #pmhalPrcmVdId_t for details.
 *  \param  tempInMilliDegree   Temperature Threshold in milli Degree Celsius.
 *
 *  \return status              Status of the API call.
 *                            - #PM_SUCCESS   If the threshold is programmed
 *                                           correctly.
 *                            - #PM_BADARGS   If the voltage domain is not
 *                                           correct or the temperature is
 *                                           out of the range supported.
 */
int32_t PMHALBgapSetColdThreshold(pmhalPrcmVdId_t voltId,
                                  int32_t         tempInMilliDegree);

/** \brief  This API returns the configured high temperature threshold
 *          range programmed into the
 *          CTRL_CORE_BANDGAP_THRESHOLD_x[25:16] THOLD_HOT_x bit fields.
 *
 *  \param  voltId               Unique voltage domain ID. Refer enum
 *                               #pmhalPrcmVdId_t for details.
 *  \param  thresholdTempRange   Pointer to the threshold temperature range.
 *                               Gives the max and min temperature which
 *                               corresponds to the read threshold ADC value.
 *
 *  \return status               Status of the API call.
 *                             - #PM_SUCCESS   If the threshold is read
 *                                            correctly.
 *                             - #PM_BADARGS   If the voltage domain is not
 *                                            correct.
 */
int32_t PMHALBgapGetHotThreshold(pmhalPrcmVdId_t   voltId,
                                 pmhalBgapRange_t *thresholdTempRange);

/** \brief  This API returns the configured low temperature threshold
 *          range programmed into the
 *          CTRL_CORE_BANDGAP_THRESHOLD_x[25:16] THOLD_COLD_x bit fields.
 *
 *  \param  voltId                  Unique voltage domain ID. Refer enum
 *                                  #pmhalPrcmVdId_t for details.
 *  \param  thresholdTempRange      Pointer to the threshold temperature range.
 *                                  Gives the max and min temperature which
 *                                  corresponds to the read threshold ADC value.
 *
 *  \return status                  Status of the API call.
 *                                - #PM_SUCCESS   If the threshold is read
 *                                                correctly.
 *                                - #PM_BADARGS   If the voltage domain is not
 *                                               correct.
 */
int32_t PMHALBgapGetColdThreshold(pmhalPrcmVdId_t   voltId,
                                  pmhalBgapRange_t *thresholdTempRange);

/** \brief  The non masked (raw) comparator outputs are available for reading
 *          through the corresponding bits in the CTRL_CORE_BANDGAP_STATUS_1 and
 *          CTRL_CORE_BANDGAP_STATUS_2 registers. The high temperature threshold
 *          comparator outputs are read through the HOT_x bits using this API.
 *
 *  \param  voltId              Unique voltage domain ID. Refer enum
 *                              #pmhalPrcmVdId_t for details.
 *  \param  hotStatus           High temperature threshold comparator output
 *
 *  \return status              Status of the API call.
 *                              - #PM_SUCCESS   If the output is read correctly.
 *                              - #PM_BADARGS   If the voltage domain is not
 *                                           correct or the pointer hotStatus
 *                                           is NULL.
 */
int32_t PMHALBgapGetHotAlertStatus(pmhalPrcmVdId_t voltId, uint32_t *hotStatus);

/** \brief  The non masked (raw) comparator outputs are available for reading
 *          through the corresponding bits in the CTRL_CORE_BANDGAP_STATUS_1 and
 *          CTRL_CORE_BANDGAP_STATUS_2 registers. The low temperature threshold
 *          comparator outputs are read through the COLD_x bits using this API.
 *
 *  \param  voltId              Unique voltage domain ID. Refer enum
 *                              #pmhalPrcmVdId_t for details.
 *  \param  coldStatus          Low temperature threshold comparator output
 *
 *  \return status              Status of the API call.
 *                             - #PM_SUCCESS   If the output is read correctly.
 *                             - #PM_BADARGS   If the voltage domain is not
 *                                           correct or the pointer coldStatus
 *                                           is NULL.
 */
int32_t PMHALBgapGetColdAlertStatus(pmhalPrcmVdId_t voltId,
                                    uint32_t       *coldStatus);

/** \brief  The CTRL_MODULE_CORE_IRQ_THERMAL_ALERT signal is also routed to
 *          the CTRL_CORE_BANDGAP_STATUS_1[31] ALERT bit. Value of 0x1 indicates
 *          that the CTRL_MODULE_CORE_IRQ_THERMAL_ALERT signal is asserted.
 *          Software can use this interrupt to implement the device thermal
 *          management policy. This API can be used to wait for the clearing of
 *          the alert signal as the temperature of the voltage domains drop
 *          below their threshold.
 *
 *  \param  timeOut     Time out to wait till the temperature drops below the
 *                      threshold and the alert signal is cleared.
 *                      Valid values are PM_TIMEOUT_INFINITE (wait infinitely)
 *                      or any non zero time out value.
 *
 *  \return status      Status of the API call.
 *                      - #PM_SUCCESS   If the alert is cleared.
 *                      - #PM_BADARGS   If the timeout value provided is 0.
 *                      - #PM_FAIL      If the alert is not cleared in the given
 *                                   timeOut.
 */
int32_t PMHALBgapWaitForAlertClear(uint32_t timeOut);

/** \brief  Each time one of the CTRL_CORE_TEMP_SENSOR_x[9:0] BGAP_DTEMP_x bit
 *          fields is updated with new temperature value, this value is also
 *          automatically stored into a 5-level deep FIFO and a time stamp is
 *          registered too. This API helps read the value for a given entry
 *          number.
 *
 *  \param  voltId            Unique voltage domain ID. Refer enum
 *                            #pmhalPrcmVdId_t for details.
 *  \param  entryNum          Entry number of the FIFO. Has to be lesser than
 *                            number supported in the SoC. Number starts from
 *                            0 which corresponds to the most recent entry.
 *  \param  fifoEntry         The Bandgap sensor fifo entry value is returned
 *                            corresponding to the given voltage domain and
 *                            entry number.
 *
 *  \return status             Status of the API call.
 *                           - #PM_SUCCESS   If the FIFO entry is read correctly
 *                           - #PM_BADARGS   If the voltage domain is not
 *                                           correct or the pointer fifoEntry
 *                                           is NULL or the entryNum is higher
 *                                           than supported.
 */
int32_t PMHALBgapGetFifoEntry(pmhalPrcmVdId_t       voltId,
                              uint32_t              entryNum,
                              pmhalBgapFifoEntry_t *fifoEntry);

#ifdef __cplusplus
}
#endif

#endif

/* @} */


