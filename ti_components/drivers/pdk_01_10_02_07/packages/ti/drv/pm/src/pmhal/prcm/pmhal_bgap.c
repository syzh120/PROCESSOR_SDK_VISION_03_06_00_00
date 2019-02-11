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
 * \file pmhal_bgap.c
 *
 *  \brief This file contains the interface definition for the Temperature HAL.
 *         The Temperature HAL supports the following features:
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_bgap.h"
#include "hw_pmhal_bgap_data.h"

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

int32_t PMHALBgapGetCurrTemperature(pmhalPrcmVdId_t   voltId,
                                    pmhalBgapRange_t *currTempRange)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;
    uint32_t    adcEoc;
    uint32_t    adcValue1 = 0U, adcValue2 = 0U, adcValue3 = 0U;
    uint32_t    adcValue  = 0U;
    const pmhalBgapRange_t *tempRangePtr;
    uint32_t    numOfMeasurements;

    if ((NULL != currTempRange) && (voltId < PMHAL_BGAP_NUM_FSM))
    {
        do
        {
            numOfMeasurements = HW_RD_FIELD32_RAW(
                (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                bandgapDtempFifo0Addr,
                (uint32_t) PMHAL_BGAP_DTEMP_TAG_MASK,
                (uint32_t) PMHAL_BGAP_DTEMP_TAG_SHIFT);
        } while (numOfMeasurements == 0U);
        addr = gPmhalBgapVoltDomBandgapData[voltId].tempSensorAddr;

        /*
         * The temperature sensor is read based on the Errata ID: i814
         * workaround. The steps are mentioned below:
         * Multiple reads to CONTROL_TEMP_SENSOR_MPU/MM/CORE[9:0]:
         * BGAP_DTEMP_MPU/MM/CORE is needed to discard false value
         * and read right value:
         *
         *  1. Perform two successive reads to BGAP_DTEMP bit field.
         *      (a) If read1 returns Val1 and read2 returns Val1, then
         *          right value is Val1.
         *      (b) If read1 returns Val1, read 2 returns Val2, a third
         *          read is needed.
         *  2. Perform third read
         *      (a) If read3 returns Val2 then right value is Val2.
         *      (b) If read3 returns Val3, then right value is Val3.
         */
        adcEoc = 1U;
        /*
         * Wait for the End of Conversion bit to go to 0. This bit is 0 when the
         * the value to be read in the Temperature register is valid.
         */
        while (0U != adcEoc)
        {
            adcEoc = HW_RD_FIELD32(addr, PMHAL_BGAP_TEMP_SENSOR_EOCZ);
        }
        /* Read the temperature ADC value */
        adcValue1 = HW_RD_FIELD32(addr, PMHAL_BGAP_TEMP_SENSOR_DTEMP);
        /* Read the temperature ADC value */
        adcValue2 = HW_RD_FIELD32(addr, PMHAL_BGAP_TEMP_SENSOR_DTEMP);
        /* Read the temperature ADC value */
        adcValue3 = HW_RD_FIELD32(addr, PMHAL_BGAP_TEMP_SENSOR_DTEMP);

        if (adcValue1 == adcValue2)
        {
            adcValue = adcValue1;
        }
        else if (adcValue2 == adcValue3)
        {
            adcValue = adcValue2;
        }
        else
        {
            adcValue = adcValue3;
        }
        /* Convert the ADC value read to a valid temperature value */
        tempRangePtr = PmhalBgapGetTemperatureRange(adcValue);

        if (NULL != tempRangePtr)
        {
            currTempRange->minTemp = tempRangePtr->minTemp;
            currTempRange->maxTemp = tempRangePtr->maxTemp;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapClearState(pmhalPrcmVdId_t voltId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    mask;
    uint32_t    value;
    pmhalBgapBandgapCntDelay_t delay;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        /* In order to make sure that the FSM has truly cleared the state of
         * the band gap the API must wait for the CLEAR_ACCUM bit to auto clear.
         * This bit does not clear till the BGAP FSM has not finished the
         * operation of clearing the BGAP state.
         * This clearing is based on the counter delay programmed. In order to
         * make sure that SW does not wait for too long for this clear to finish
         * we follow the sequence below:
         *      1.) Read the current Counter delay
         *      2.) If the counter delay is not Immediate then convert it to
         *          Immediate.
         *      3.) Set CLEAR_ACCUM bit and wait for its clearing.
         *      4.) Reconfigure the COUNTER_DELAY to the original value.
         */
        delay = (pmhalBgapBandgapCntDelay_t) HW_RD_FIELD32(
            gPmhalBgapVoltDomBandgapData[PMHAL_PRCM_VD_MIN].bandgapMaskAddr,
            CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY);
        if (delay != PMHAL_BGAP_BAND_GAP_IMMEDIATE)
        {
            HW_WR_FIELD32(
                gPmhalBgapVoltDomBandgapData[PMHAL_PRCM_VD_MIN].bandgapMaskAddr,
                CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY,
                PMHAL_BGAP_BAND_GAP_IMMEDIATE);
        }
        mask = (uint32_t) ((uint32_t) 1U <<
                           gPmhalBgapVoltDomBandgapData[voltId].
                           bandgapMaskClearAccShift);
        HW_WR_FIELD32_RAW((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                          bandgapMaskAddr,
                          (uint32_t) mask,
                          (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                          bandgapMaskClearAccShift, (uint32_t) 1U);
        do
        {
            value = HW_RD_FIELD32_RAW(
                (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                bandgapMaskAddr, (uint32_t) mask,
                (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                bandgapMaskClearAccShift);
        } while (value != 0U);

        if (delay != PMHAL_BGAP_BAND_GAP_IMMEDIATE)
        {
            HW_WR_FIELD32(
                gPmhalBgapVoltDomBandgapData[PMHAL_PRCM_VD_MIN].bandgapMaskAddr,
                CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY,
                delay);
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapEnableHotEvent(pmhalPrcmVdId_t voltId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    maskHot;
    uint32_t    shiftHot;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        /* Hot shift is always 1+ the cold shift of the mask */
        shiftHot = ((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                    bandgapMaskColdShift + (uint32_t) 1U);
        maskHot = (uint32_t) ((uint32_t) 1U << shiftHot);

        /* Setting this field would send the Alert signal out based on
         * the status of the hot event.
         */
        HW_WR_FIELD32_RAW((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                          bandgapMaskAddr,
                          (uint32_t) maskHot,
                          (uint32_t) shiftHot, (uint32_t) 1U);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapDisableHotEvent(pmhalPrcmVdId_t voltId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    maskHot;
    uint32_t    shiftHot;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        /* Hot shift is always 1+ the cold shift of the mask */
        shiftHot = ((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                    bandgapMaskColdShift + (uint32_t) 1U);
        maskHot = (uint32_t) ((uint32_t) 1U << shiftHot);

        /* Clearing this field would not send the Alert signal out based on
         * the status of the hot event.
         */
        HW_WR_FIELD32_RAW((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                          bandgapMaskAddr,
                          (uint32_t) maskHot,
                          (uint32_t) shiftHot, (uint32_t) 0U);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapEnableColdEvent(pmhalPrcmVdId_t voltId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    maskCold;
    uint32_t    shiftCold;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        shiftCold = gPmhalBgapVoltDomBandgapData[voltId].bandgapMaskColdShift;
        maskCold  = (uint32_t) ((uint32_t) 1U << shiftCold);

        /* Setting this field would send the Alert signal out based on
         * the status of the cold event.
         */
        HW_WR_FIELD32_RAW((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                          bandgapMaskAddr,
                          (uint32_t) maskCold,
                          (uint32_t) shiftCold, (uint32_t) 1U);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapDisableColdEvent(pmhalPrcmVdId_t voltId)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    maskCold;
    uint32_t    shiftCold;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        shiftCold = gPmhalBgapVoltDomBandgapData[voltId].bandgapMaskColdShift;
        maskCold  = (uint32_t) ((uint32_t) 1U << shiftCold);

        /* Clearing this field would not send the Alert signal out based on
         * the status of the cold event.
         */
        HW_WR_FIELD32_RAW((uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                          bandgapMaskAddr,
                          (uint32_t) maskCold,
                          (uint32_t) shiftCold, (uint32_t) 0U);
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapSetMeasureDelay(pmhalBgapBandgapCntDelay_t tDelay)
{
    pmErrCode_t status = PM_SUCCESS;

    /* PMHAL_PRCM_VD_MIN = PMHAL_PRCM_VD_MPU for tda2xx
     * PMHAL_PRCM_VD_MIN = PMHAL_PRCM_VD_CORE for tda3xx */

    if (tDelay < PMHAL_BGAP_BAND_GAP_MAX)
    {
        HW_WR_FIELD32(
            gPmhalBgapVoltDomBandgapData[PMHAL_PRCM_VD_MIN].bandgapMaskAddr,
            CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY,
            tDelay);
    }
    else
    {
        status = PM_BADARGS;
    }
    return status;
}

int32_t PMHALBgapSetSIldeMode(pmhalBgapBandgapSIdleMode_t mode)
{
    pmErrCode_t status = PM_SUCCESS;

    /* PMHAL_PRCM_VD_MIN = PMHAL_PRCM_VD_MPU for tda2xx
     * PMHAL_PRCM_VD_MIN = PMHAL_PRCM_VD_CORE for tda3xx
     */

    /* According to the Errata ID: i827 one should not allow setting
     * idle the Control Module MPU Bandgap (i.e. keep CTRL_CORE_BANDGAP_MASK_1
     * [31:30]SIDLEMODE=0x0)
     */

    if (PMHAL_BGAP_BAND_GAP_NO_IDLE == mode)
    {
        HW_WR_FIELD32(
            gPmhalBgapVoltDomBandgapData[PMHAL_PRCM_VD_MIN].bandgapMaskAddr,
            CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE,
            mode);
    }
    else
    {
        status = PM_BADARGS;
    }
    return status;
}

int32_t PMHALBgapSetHotThreshold(pmhalPrcmVdId_t voltId,
                                 int32_t         tempInMilliDegree)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    adcValue;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        if ((tempInMilliDegree >= PMHAL_BGAP_MIN_TEMP_VALUE) &&
            (tempInMilliDegree <= PMHAL_BGAP_MAX_TEMP_VALUE))
        {
            /* For Errata ID: i813, to avoid spurious temperature alert
             * interrupt, first disable the mask and then enable after setting
             * the desired threshold
             */
            status = (pmErrCode_t) PMHALBgapDisableHotEvent(voltId);

            if (PM_SUCCESS == status)
            {
                /* Get the ADC value from the given temperature in milli degrees
                 */
                adcValue = PmhalBgapGetAdcValue(tempInMilliDegree);

                if (0U != adcValue)
                {
                    HW_WR_FIELD32(
                        gPmhalBgapVoltDomBandgapData[voltId].bandgapThreshAddr,
                        PMHAL_BGAP_THOLD_HOT,
                        adcValue);
                }
                else
                {
                    status = PM_FAIL;
                }
                if (PM_SUCCESS == status)
                {
                    status = (pmErrCode_t) PMHALBgapEnableHotEvent(voltId);
                }
            }
        }
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

int32_t PMHALBgapSetColdThreshold(pmhalPrcmVdId_t voltId,
                                  int32_t         tempInMilliDegree)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    adcValue;

    if (voltId < PMHAL_BGAP_NUM_FSM)
    {
        if ((tempInMilliDegree >= PMHAL_BGAP_MIN_TEMP_VALUE) &&
            (tempInMilliDegree <= PMHAL_BGAP_MAX_TEMP_VALUE))
        {
            /* For Errata ID: i813, to avoid spurious temperature alert
             * interrupt, first disable the mask and then enable after setting
             * the desired threshold
             */
            status = (pmErrCode_t) PMHALBgapDisableColdEvent(voltId);

            if (PM_SUCCESS == status)
            {
                /* Get the ADC value from the given temperature in milli degrees
                 */
                adcValue = PmhalBgapGetAdcValue(tempInMilliDegree);

                if (0U != adcValue)
                {
                    HW_WR_FIELD32(
                        gPmhalBgapVoltDomBandgapData[voltId].bandgapThreshAddr,
                        PMHAL_BGAP_THOLD_COLD,
                        adcValue);
                }
                else
                {
                    status = PM_FAIL;
                }
                if (PM_SUCCESS == status)
                {
                    status = (pmErrCode_t) PMHALBgapEnableColdEvent(voltId);
                }
            }
        }
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

int32_t PMHALBgapGetHotThreshold(pmhalPrcmVdId_t   voltId,
                                 pmhalBgapRange_t *thresholdTempRange)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr, tholdTemp;
    const pmhalBgapRange_t *tempRangePtr;

    if ((voltId < PMHAL_BGAP_NUM_FSM) && (NULL != thresholdTempRange))
    {
        addr      = gPmhalBgapVoltDomBandgapData[voltId].bandgapThreshAddr;
        tholdTemp = HW_RD_FIELD32(addr, PMHAL_BGAP_THOLD_HOT);

        /* Convert the ADC value read to a valid temperature value */
        tempRangePtr = PmhalBgapGetTemperatureRange(tholdTemp);

        if (NULL != tempRangePtr)
        {
            thresholdTempRange->minTemp = tempRangePtr->minTemp;
            thresholdTempRange->maxTemp = tempRangePtr->maxTemp;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapGetColdThreshold(pmhalPrcmVdId_t   voltId,
                                  pmhalBgapRange_t *thresholdTempRange)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr, tholdTemp;
    const pmhalBgapRange_t *tempRangePtr;

    if ((voltId < PMHAL_BGAP_NUM_FSM) && (NULL != thresholdTempRange))
    {
        addr      = gPmhalBgapVoltDomBandgapData[voltId].bandgapThreshAddr;
        tholdTemp = HW_RD_FIELD32(addr, PMHAL_BGAP_THOLD_COLD);

        /* Convert the ADC value read to a valid temperature value */
        tempRangePtr = PmhalBgapGetTemperatureRange(tholdTemp);

        if (NULL != tempRangePtr)
        {
            thresholdTempRange->minTemp = tempRangePtr->minTemp;
            thresholdTempRange->maxTemp = tempRangePtr->maxTemp;
        }
        else
        {
            status = PM_FAIL;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapGetHotAlertStatus(pmhalPrcmVdId_t voltId, uint32_t *hotStatus)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    mask;
    uint32_t    shift;
    uint32_t    addr, currTemp, tholdTemp;

    if ((voltId < PMHAL_BGAP_NUM_FSM) && (NULL != hotStatus))
    {
        /* First read the status of the Hot event to check if the hot event
         * is indeed seen.
         */
        shift = (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].
                bandgapColdEvtStatusShift + (uint32_t) 1U;
        mask = (uint32_t) ((uint32_t) 1U << shift);

        *hotStatus = HW_RD_FIELD32_RAW(
            (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].bandgapStatusAddr,
            (uint32_t) mask,
            (uint32_t) shift);
        /* Once the hot event is confirmed. Reconfirm by comparing the current
         * temperature to the Hot Threshold programmed. This makes sure that
         * no spurious hot events are reported.
         */
        addr      = gPmhalBgapVoltDomBandgapData[voltId].bandgapDtempFifo0Addr;
        currTemp  = HW_RD_FIELD32(addr, PMHAL_BGAP_DTEMP_TEMPERATURE);
        addr      = gPmhalBgapVoltDomBandgapData[voltId].bandgapThreshAddr;
        tholdTemp = HW_RD_FIELD32(addr, PMHAL_BGAP_THOLD_HOT);
        /* Case 1: Hot event is false positive */
        if ((tholdTemp > currTemp) && (*hotStatus == 1U))
        {
            *hotStatus = 0U;
        }
        /* Case 2: Hot event is false negative */
        if ((tholdTemp < currTemp) && (*hotStatus == 0U))
        {
            *hotStatus = 1U;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapGetColdAlertStatus(pmhalPrcmVdId_t voltId,
                                    uint32_t       *coldStatus)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    mask;
    uint32_t    shift;
    uint32_t    addr, currTemp, tholdTemp;

    if ((voltId < PMHAL_BGAP_NUM_FSM) && (NULL != coldStatus))
    {
        /* First read the status of the Cold event to check if the Cold event
         * is indeed seen.
         */
        shift = gPmhalBgapVoltDomBandgapData[voltId].bandgapColdEvtStatusShift;
        mask  = (uint32_t) ((uint32_t) 1U << shift);

        *coldStatus = HW_RD_FIELD32_RAW(
            (uint32_t) gPmhalBgapVoltDomBandgapData[voltId].bandgapStatusAddr,
            (uint32_t) mask,
            (uint32_t) shift);
        /* Once the cold event is confirmed. Reconfirm by comparing the current
         * temperature to the Cold Threshold programmed. This makes sure that
         * no spurious cold events are reported.
         */
        addr      = gPmhalBgapVoltDomBandgapData[voltId].bandgapDtempFifo0Addr;
        currTemp  = HW_RD_FIELD32(addr, PMHAL_BGAP_DTEMP_TEMPERATURE);
        addr      = gPmhalBgapVoltDomBandgapData[voltId].bandgapThreshAddr;
        tholdTemp = HW_RD_FIELD32(addr, PMHAL_BGAP_THOLD_COLD);
        /* Case 1: Cold event is false positive */
        if ((tholdTemp < currTemp) && (*coldStatus == 1U))
        {
            *coldStatus = 0U;
        }
        /* Case 2: Cold event is false negative */
        if ((tholdTemp > currTemp) && (*coldStatus == 0U))
        {
            *coldStatus = 1U;
        }
    }
    else
    {
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapWaitForAlertClear(uint32_t timeOut)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr   =
        gPmhalBgapVoltDomBandgapData[PMHAL_PRCM_VD_MIN].bandgapMaskAddr;

    /* PMHAL_PRCM_VD_MIN = PMHAL_PRCM_VD_MPU for tda2xx
     * PMHAL_PRCM_VD_MIN = PMHAL_PRCM_VD_CORE for tda3xx */

    uint32_t    alertStatus;
    uint32_t    timeToWait;
    /* Wait for the clearing of the alert status. This may be useful while
     * waiting for the temperature to become lower upon thermal actions being
     * taken. Ideally it is okay for the CPU to go to idle and not wait in this
     * dead loop for the device temperature to go down.
     */
    if (PM_TIMEOUT_INFINITE == timeOut)
    {
        do
        {
            alertStatus = HW_RD_FIELD32(addr, CTRL_CORE_BANDGAP_STATUS_1_ALERT);
        } while (1U == alertStatus);
    }
    else if (PM_TIMEOUT_NOWAIT != timeOut)
    {
        timeToWait = timeOut;
        do
        {
            alertStatus = HW_RD_FIELD32(addr, CTRL_CORE_BANDGAP_STATUS_1_ALERT);
            timeToWait--;
        } while ((1U == alertStatus) && (0U != timeToWait));

        if (0U == timeToWait)
        {
            status = PM_FAIL;
        }
    }
    else
    {
        /* Time out of 0 does not make sense */
        status = PM_BADARGS;
    }

    return status;
}

int32_t PMHALBgapGetFifoEntry(pmhalPrcmVdId_t       voltId,
                              uint32_t              entryNum,
                              pmhalBgapFifoEntry_t *fifoEntry)
{
    pmErrCode_t status = PM_SUCCESS;
    uint32_t    addr;

    /* This is used to access the FIFO entries maintained by the BGAP FSM.
     * the index should always be lesser than the maximum number of FIFOs
     * supported by the device.
     */
    if ((voltId < PMHAL_BGAP_NUM_FSM) &&
        (NULL != fifoEntry) &&
        (entryNum < PMHAL_BGAP_MAX_NUM_FIFOS))
    {
        addr = gPmhalBgapVoltDomBandgapData[voltId].bandgapDtempFifo0Addr +
               (4U * entryNum);
        fifoEntry->dtempTag   = HW_RD_FIELD32(addr, PMHAL_BGAP_DTEMP_TAG);
        fifoEntry->dtempValue = HW_RD_FIELD32(addr,
                                              PMHAL_BGAP_DTEMP_TEMPERATURE);
    }
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

