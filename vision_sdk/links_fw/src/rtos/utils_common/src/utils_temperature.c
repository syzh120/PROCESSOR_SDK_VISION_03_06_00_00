/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_temperature.c
 *
 * \brief  APIs to execute CPU Junction temperature and alerts an interrupt on
 *         core
 *
 * \version 0.0 (Jan 2015) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_temperature.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>

/**
 *******************************************************************************
 * \brief Macro
 *******************************************************************************
 */

#define TEMP_IRQ_NO                      ((UInt32)61U)
/**< \brief IRQ number for Temperature Sensor Interrupt */

#define HOT_EVT_TEMP_THRESH              ((UInt32)80000U)
/**< \brief Default HOT temperature Threshold Value */

#define MAX_HOT_EVT_TEMP_THRESH          ((UInt32)120000U)
/**< \brief Maximum HOT temperature Threshold Value */

#define COLD_EVT_TEMP_THRESH             ((UInt32)10000U)
/**< \brief Cold temperature Threshold Value */

#define MIN_COLD_EVT_TEMP_THRESH         ((UInt32)0x0U)
/**< \brief Minimum COLD temperature Threshold Value */

#define DEFAULT_STEP_SIZE                ((UInt32)5000U)
/**< \brief Default Step Size */

#define DEFAULT_COUNTER_DELAY            (PMHAL_BGAP_BAND_GAP_1_MS)
/**< \brief Default value of the counter delay */

#if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD) || defined(TDA2PX_BUILD)
char *voltageDomain_t_names[] =
{
    "PMHAL_PRCM_VD_MPU",
    "PMHAL_PRCM_VD_CORE",
    "PMHAL_PRCM_VD_IVAHD",
    "PMHAL_PRCM_VD_DSPEVE",
    "PMHAL_PRCM_VD_GPU",
};
#elif defined(TDA3XX_BUILD)
char *voltageDomain_t_names[] =
{
    "PMHAL_PRCM_VD_CORE",
    "PMHAL_PRCM_VD_DSPEVE",
};
#endif
/**< Voltage domains present in Platforms  */

/**
 ******************************************************************************
 *
 * \brief Utils Temperature Object.
 *        This object is used to save the hot and cold event thresholds and
 *        the step size for thermal hysterisis. In case of limp home mode
 *        the structure holds the variables to increase or reset FPS.
 *
 ******************************************************************************
 */
typedef struct {
    pmhalPrcmVdId_t voltId;
    /*< Voltage Domain ID of the Temperature object */
    Int32   hotEventThreshold;
    /*< Threshold at which the Hot event is raised. Fps is reduced at this
     *  point.
     */
    Int32   coldEventThreshold;
    /*< Threshold at which the cold event is raised. The FPS is reset to
     *  application programmed after this point.
     */
    UInt32  stepSize;
    /*< Step difference between the temperatures of hot and cold events
     *  between hot and cold event threshold. Used in thermal hysterisis
     */
    UInt32 limpHomeModeActive;
    /*< Flag to Indicate if Limp Home Mode is Active */
} Utils_TempObj;

Utils_TempObj gUtils_tempObj[PMHAL_BGAP_NUM_FSM];
BspOsal_IntrHandle gUtils_tempHwiHandle;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

static void Utils_tempBgapIntInit(void);

Void Utils_tempBgapEventIsr(UArg arg);

/**
 *******************************************************************************
 *
 * \brief   DeInit during system turndown
 *
 * \return NONE
 *
 *******************************************************************************
*/
Void Utils_tempConfigDeInit(void)
{
/*
 * Deinit if any thread created here.
 */
    Hwi_clearInterrupt(TEMP_IRQ_NO);
    Hwi_disableInterrupt(TEMP_IRQ_NO);

    BspOsal_unRegisterIntr(&gUtils_tempHwiHandle);

    IntXbar_disconnectIRQ(TEMP_IRQ_NO);
}

/**
 *******************************************************************************
 *
 * \brief Prepare the Temperature Configuration .
 *          The hot cold and step size are set for default
 *
 * \return NONE
 *
 *******************************************************************************
 */
Void Utils_tempConfigInit(void)
{
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;

    PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_IMMEDIATE);
    /* For Errata ID: i827 */
    PMHALBgapSetSIldeMode(PMHAL_BGAP_BAND_GAP_NO_IDLE);

    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        gUtils_tempObj[voltId].voltId = voltId;
        gUtils_tempObj[voltId].hotEventThreshold = HOT_EVT_TEMP_THRESH;
        gUtils_tempObj[voltId].coldEventThreshold = COLD_EVT_TEMP_THRESH;
        Vps_printf(
                " UTILS_TEMP: Voltage [%s], Hot Threshold = [%d.%d], \
Cold Threshold = [%d.%d]\n",
                voltageDomain_t_names[voltId],
                gUtils_tempObj[voltId].hotEventThreshold/1000,
                abs(gUtils_tempObj[voltId].hotEventThreshold) % 1000,
                gUtils_tempObj[voltId].coldEventThreshold/1000,
                abs(gUtils_tempObj[voltId].coldEventThreshold) % 1000);

        gUtils_tempObj[voltId].stepSize = DEFAULT_STEP_SIZE;
        gUtils_tempObj[voltId].limpHomeModeActive = UTILS_TEMP_LIMP_HOME_INACTIVE;
        PMHALBgapSetColdThreshold(voltId,
                gUtils_tempObj[voltId].coldEventThreshold);
        PMHALBgapSetHotThreshold(voltId,
                gUtils_tempObj[voltId].hotEventThreshold);
    }
    Utils_tempBgapIntInit();
    PMHALBgapSetMeasureDelay(DEFAULT_COUNTER_DELAY);
}

/**
 *******************************************************************************
 *
 * \brief Change Hot Threshold Value for given Voltage Id
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_tempChangeHotThreshold(Int32 Value)
{
    UInt32 cookie;
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
    /* Disable the system interrupt */
    Hwi_disableInterrupt(TEMP_IRQ_NO);
    cookie = Hwi_disable();
    PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_IMMEDIATE);
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        gUtils_tempObj[voltId].hotEventThreshold = Value;
        PMHALBgapSetHotThreshold(voltId,
                gUtils_tempObj[voltId].hotEventThreshold);
    }
    PMHALBgapSetMeasureDelay(DEFAULT_COUNTER_DELAY);
    Hwi_restore(cookie);
    /* Clear any pending interrupts */
    Hwi_clearInterrupt(TEMP_IRQ_NO);
     /* Enable the system interrupt */
    Hwi_enableInterrupt(TEMP_IRQ_NO);
}

/**
 *******************************************************************************
 *
 * \brief Change Cold Threshold Value for given Voltage Id
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_tempChangeColdThreshold(Int32 Value)
{
    UInt32 cookie;
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
    /* Disable the system interrupt */
    Hwi_disableInterrupt(TEMP_IRQ_NO);
    cookie = Hwi_disable();
    PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_IMMEDIATE);
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        gUtils_tempObj[voltId].coldEventThreshold = Value;
        PMHALBgapSetColdThreshold(voltId,
                gUtils_tempObj[voltId].coldEventThreshold);
    }
    PMHALBgapSetMeasureDelay(DEFAULT_COUNTER_DELAY);
    Hwi_restore(cookie);
    /* Clear any pending interrupts */
    Hwi_clearInterrupt(TEMP_IRQ_NO);
     /* Enable the system interrupt */
    Hwi_enableInterrupt(TEMP_IRQ_NO);
}

/**
 *******************************************************************************
 *
 * \brief Change the Temperature Step Window
 *
 * \param   Value     New Step Size Value
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_tempChangeStepSize(UInt32 Value)
{
    UInt32 cookie;
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;

    cookie = Hwi_disable();
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        gUtils_tempObj[voltId].stepSize = Value;
    }
    Hwi_restore(cookie);
}

/**
 *******************************************************************************
 *
 * \brief Read the Temperature Hot Threshold
 *
 * \param   voltId     Voltage Id of the Temperature Sensor.
 *
 * \return  Hot event Threshold
 *
 *******************************************************************************
 */
Int32 Utils_tempGetHotThreshold(UInt32 voltId)
{
    return gUtils_tempObj[voltId].hotEventThreshold;
}

/**
 *******************************************************************************
 *
 * \brief Read the Temperature Cold Threshold
 *
 * \param   voltId     Voltage Id of the Temperature Sensor.
 *
 * \return  Cold event Threshold
 *
 *******************************************************************************
 */
Int32 Utils_tempGetColdThreshold(UInt32 voltId)
{
    return gUtils_tempObj[voltId].coldEventThreshold;
}

/**
 *******************************************************************************
 *
 * \brief Read the Temperature Step Size
 *
 * \param   voltId     Voltage Id of the Temperature Sensor.
 *
 * \return  Step Size by which to scale hot and cold thresholds.
 *
 *******************************************************************************
 */
Int32 Utils_tempGetStepSize(UInt32 voltId)
{
    return gUtils_tempObj[voltId].stepSize;
}

/**
 *******************************************************************************
 *
 * \brief Read the Current Temperature
 *
 * \param   voltId     Voltage Id of the Temperature Sensor.
 *
 * \return  Current Temperature in milli Degrees.
 *
 *******************************************************************************
 */
Int32 Utils_tempGetCurrTemperature(UInt32 voltId)
{
    Int32 retVal = PM_SUCCESS;
    pmhalBgapRange_t currTempRange = {0, 0};

    retVal = PMHALBgapGetCurrTemperature((pmhalPrcmVdId_t)voltId,
                                            &currTempRange);
    if (PM_SUCCESS == retVal)
    {
        retVal = currTempRange.maxTemp;
    }
    else
    {
        retVal = UTILS_TEMP_INVALID;
    }

    return retVal;

}

/**
 *******************************************************************************
 *
 * \brief Print the Thermal Hot Thresholds for all Voltage Domains
 *
 * \return NONE
 *
 *******************************************************************************
 */
Void Utils_tempReadAllHotThreshold(Void)
{
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        Vps_printf(" UTILS_TEMP: Voltage Domain [ %s ] HOT Threshold = [%d.%d]\n",
             pmhalVoltageDomain_t_names[voltId],
             Utils_tempGetHotThreshold(voltId)/1000,
             abs(Utils_tempGetHotThreshold(voltId))%1000);
    }

}

/**
 *******************************************************************************
 *
 * \brief Print the Thermal Cold Thresholds for all Voltage Domains
 *
 * \return NONE
 *
 *******************************************************************************
 */
Void Utils_tempReadAllColdThreshold(Void)
{
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        Vps_printf(" UTILS_TEMP: Voltage Domain [ %s ] COLD Threshold = [%d.%d]\n",
             pmhalVoltageDomain_t_names[voltId],
             Utils_tempGetColdThreshold(voltId)/1000,
             abs(Utils_tempGetColdThreshold(voltId))%1000);
    }
}

/**
 *******************************************************************************
 *
 * \brief Update the state of the temperature object for whether the limp
 *        home mode is active or not.
 *
 * \param voltId     Voltage Domain for which the Limp Home mode needs to be
 *                   set.
 * \param state      UTILS_TEMP_LIMP_HOME_ACTIVE or
 *                   UTILS_TEMP_LIMP_HOME_INACTIVE
 *
 * \return NONE
 *
 *******************************************************************************
 */
Void Utils_tempUpdateLimpHomeState(UInt32 voltId, UInt32 state)
{
    /* Can take any value like UTILS_TEMP_LIMP_HOME_ACTIVE or
     * UTILS_TEMP_LIMP_HOME_INACTIVE*/
    gUtils_tempObj[voltId].limpHomeModeActive = state & (UInt32)0x1U;
}

/**
 *******************************************************************************
 *
 * \brief Update the state of the temperature object for whether the limp
 *        home mode is active or not.
 *
 * \param state      UTILS_TEMP_LIMP_HOME_ACTIVE or
 *                   UTILS_TEMP_LIMP_HOME_INACTIVE
 *
 * \return NONE
 *
 *******************************************************************************
 */
Void Utils_tempUpdateAllVoltLimpHomeState(UInt32 state)
{
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        /* Can take any value like UTILS_TEMP_LIMP_HOME_ACTIVE or
         * UTILS_TEMP_LIMP_HOME_INACTIVE*/
        gUtils_tempObj[voltId].limpHomeModeActive = state & (UInt32)0x1U;
    }
}

/**
 *******************************************************************************
 *
 * \brief Get the status which indicates if limp Home mode is enabled or
 *        disabled.
 *
 * \return state       UTILS_TEMP_LIMP_HOME_ACTIVE or
 *                     UTILS_TEMP_LIMP_HOME_INACTIVE
 *
 *******************************************************************************
 */
UInt32 Utils_tempGetLimpHomeState(Void)
{
    pmhalPrcmVdId_t voltId = PMHAL_PRCM_VD_CORE;
    UInt32 state = 0;
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        state = state | gUtils_tempObj[voltId].limpHomeModeActive;
    }
    return state;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/*******************************************************************************
 * \brief  Configure the Temperature Sensor Interrupt
 *
 * \return None
 *
 *******************************************************************************
 */
static void Utils_tempBgapIntInit(void)
{
    IntXbar_connectIRQ(TEMP_IRQ_NO, CTRL_MODULE_CORE_IRQ_THERMAL_ALERT);

    /* This task sleep is required to make sure that the spurious interrupts
     * if any arrive at the IPU before proceeding.
     */
    BspOsal_sleep(50U);
    /* Follow this sequence to resolve silicon Errata ID: i813 which can
     * cause a spurious interrupt.
     */
    Hwi_clearInterrupt(TEMP_IRQ_NO);

    Vps_printf(" UTILS_TEMP: TEMPERATUE INTERRUPT: HWI Create for INT%d !!!\n", TEMP_IRQ_NO);

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * Passing pointer arguments to functions which
     * takes arguments as UInt32 for legacy reasons and viceversa
     */
    gUtils_tempHwiHandle = BspOsal_registerIntr(TEMP_IRQ_NO,
                    (BspOsal_IntrFuncPtr)&Utils_tempBgapEventIsr,
                    (void*)TEMP_IRQ_NO
                    );

    if (gUtils_tempHwiHandle == NULL)
    {
        Vps_printf(" UTILS_TEMP: TEMPERATUE INTERRUPT: HWI Create Failed !!!\n");
        UTILS_assert((Bool)0);
    }

    /* Clear any previous interrupts to ensure we are not getting false interrupts */
    Hwi_clearInterrupt(TEMP_IRQ_NO);

    /* Enable the interrupt */
    Hwi_enableInterrupt(TEMP_IRQ_NO);
}

/**
 *******************************************************************************
 * \brief  Sensor interrupt service routine. This will Enable the Temperature
 *          sensor interrupt.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_tempBgapEventIsr(UArg arg)
{
    pmhalPrcmVdId_t voltId;
    volatile UInt32 hotStatus[PMHAL_BGAP_NUM_FSM] = {0U};
    volatile UInt32 coldStatus[PMHAL_BGAP_NUM_FSM] = {0U};
    UInt32 counterChangedFlag = 0U;
#ifdef TEMP_DEBUG
    Int32 retVal = PM_SUCCESS;
    pmhalBgapRange_t currTempRange = {0, 0};
#endif
    UInt32 cookie;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();
    /* Disable the system interrupt */
    Hwi_disableInterrupt(TEMP_IRQ_NO);
#ifdef TEMP_DEBUG
    Vps_printf(
            " UTILS_TEMP: ----------------------------------------------------\n");
#endif
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {
        /* First read all the status bits in one go. Reading it in phases is
         * found to give incorrect values.
         */
        PMHALBgapGetHotAlertStatus(voltId,(UInt32 *)&hotStatus[voltId]);
        PMHALBgapGetColdAlertStatus(voltId,(UInt32 *)&coldStatus[voltId]);
        counterChangedFlag = 1U;
    }
    if (1U == counterChangedFlag)
    {
        PMHALBgapSetMeasureDelay(PMHAL_BGAP_BAND_GAP_IMMEDIATE);
    }
    for(voltId = PMHAL_PRCM_VD_MIN;
            voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;
            voltId++)
    {

#ifdef TEMP_DEBUG
        /* Do a clear state before reading the current temperature.
         * Ensures the temperature read is correct.
         */
        PMHALBgapClearState(voltId);
        retVal = PMHALBgapGetCurrTemperature((pmhalPrcmVdId_t)voltId,
                                            &currTempRange);
        if (PM_SUCCESS != retVal)
        {
            Vps_printf(
                " UTILS_TEMP: Error! Could not read current temperature!! [%s]\n",
                voltageDomain_t_names[voltId]);
        }
        else
        {
            Vps_printf(
                " UTILS_TEMP: [%d.%d] deg C : Voltage Domain [%s] \n",
                currTempRange.maxTemp/1000,(abs(currTempRange.maxTemp) % 1000),
                voltageDomain_t_names[voltId]);

        }
#endif
        if(1U == hotStatus[voltId])
        {
            if(gUtils_tempObj[voltId].coldEventThreshold <= MIN_COLD_EVT_TEMP_THRESH)
            {
                PMHALBgapEnableColdEvent(voltId);
                /* App can react as temperature has increased more
                 * than threshold.
                 */
            }
            if(gUtils_tempObj[voltId].hotEventThreshold < MAX_HOT_EVT_TEMP_THRESH)
            {
#ifdef TEMP_DEBUG
                Vps_printf(
                        " UTILS_TEMP: HOT: Setting Hot Threshold to [%d.%d] deg C\
 for Voltage Domain [%s]\n",
                             gUtils_tempObj[voltId].hotEventThreshold/1000,
                             gUtils_tempObj[voltId].hotEventThreshold % 1000,
                             voltageDomain_t_names[voltId]);
#endif
                if (voltId == PMHAL_PRCM_VD_CORE)
                {
                    /* Only send one message when VD_CORE is higher. One can choose
                     * which voltage domain to send the message for.
                     */
                    System_linkControl(
                        (UInt32)SYSTEM_LINK_ID_IPU1_0,
                        (UInt32)UTILS_TEMP_CMD_EVENT_HOT,
                        (Ptr)&gUtils_tempObj[voltId].voltId,
                        sizeof(pmhalPrcmVdId_t),
                        (Bool)FALSE);
                }
            }
            else
            {
                PMHALBgapDisableHotEvent(voltId);
                Vps_printf(
                        " UTILS_TEMP: EMERGENCY!! Temperature MAX Threshold Reached...\
 Disabling Hot Event \n");
                /* Once a HOT event is received than the max hot event,
                 * App can post a semaphore to turn off certain modules to cool
                 * System , or take precaution mesaures
                 */
            }
#ifdef TEMP_DEBUG
            Vps_printf(" UTILS_TEMP: HOT: Setting Cold Threshold to [%d.%d] deg C\
 for Voltage Domain [%s]\n", gUtils_tempObj[voltId].coldEventThreshold/1000,
                             gUtils_tempObj[voltId].coldEventThreshold % 1000,
                             voltageDomain_t_names[voltId]);
#endif

        }
        if(1U == coldStatus[voltId])
        {
            if(gUtils_tempObj[voltId].hotEventThreshold >= MAX_HOT_EVT_TEMP_THRESH)
            {
                PMHALBgapEnableHotEvent(voltId);
                /* App can restart certain modules as the
                 * temperature has reduced.
                 */
            }
            if(gUtils_tempObj[voltId].coldEventThreshold > MIN_COLD_EVT_TEMP_THRESH)
            {
#ifdef TEMP_DEBUG
            Vps_printf(" UTILS_TEMP: COLD: Setting Cold Threshold to [%d.%d] deg C\
 for Voltage Domain [%s]\n", gUtils_tempObj[voltId].coldEventThreshold/1000,
                             gUtils_tempObj[voltId].coldEventThreshold % 1000,
                             voltageDomain_t_names[voltId]);
#endif
                if (voltId == PMHAL_PRCM_VD_CORE)
                {
                    /* Only send one message when VD_CORE is higher. One can choose
                     * which voltage domain to send the message for.
                     */
                    System_linkControl(
                        (UInt32)SYSTEM_LINK_ID_IPU1_0,
                        (UInt32)UTILS_TEMP_CMD_EVENT_COLD,
                        (Ptr)&gUtils_tempObj[voltId].voltId,
                        sizeof(pmhalPrcmVdId_t),
                        (Bool)FALSE);
                }
            }
            else
            {
                PMHALBgapDisableColdEvent(voltId);
                Vps_printf(
                        " UTILS_TEMP: EMERGENCY!! Temperature MIN Threshold Reached...\
 Disabling Cold Event\n ");
            }

#ifdef TEMP_DEBUG
            Vps_printf(" UTILS_TEMP: COLD: Setting Hot Threshold to [%d.%d] deg C\
 for Voltage Domain [%s]\n", gUtils_tempObj[voltId].hotEventThreshold/1000,
                             gUtils_tempObj[voltId].hotEventThreshold % 1000,
                             voltageDomain_t_names[voltId]);
#endif
        }
    }

    /* Clear any pending interrupts */
    Hwi_clearInterrupt(TEMP_IRQ_NO);
    if (1U == counterChangedFlag)
    {
        PMHALBgapSetMeasureDelay(DEFAULT_COUNTER_DELAY);
    }

    /* Restore interrupts */
    Hwi_restore(cookie);

}
