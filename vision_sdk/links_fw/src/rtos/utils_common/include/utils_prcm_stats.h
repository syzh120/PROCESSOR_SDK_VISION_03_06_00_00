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
 *
 * \ingroup UTILS_API
 * \defgroup UTILS_PRCM_STATS_API PRCM Statistics APIs
 *
 * \brief  APIs to execute CPU PRCM Stats
 *
 * @{
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file utils_prcm_stats.h
 *
 * \brief Prcm Print Stats
 *
 * \version 0.0 First version : [CM] First version
 *
 *******************************************************************************
*/

#ifndef UTILS_PRCM_STATS_H_
#define UTILS_PRCM_STATS_H_


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>

/*******************************************************************************
 *  Functions
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \brief Print the temperature value for Available Temperature
 *        Sensor for given Voltage Id.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintTempValues(UInt32 voltId);

/**
 *******************************************************************************
 *
 * \brief Print the Voltage value for Available Voltage rails corrosponding to
 *         given voltage id
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintVoltageValues(UInt32 voltId);

/**
 *******************************************************************************
 *
 * \brief Print all the Voltage value for available Voltage Rails.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllVoltageValues(void);

/**
 *******************************************************************************
 *
 * \brief Print all the temperature value for Available Temperature Sensor.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllVDTempValues(void);

/**
 *******************************************************************************
 *
 * \brief Print all PRCM Register data and the current state .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmDumpRegisterData(void);

/**
 *******************************************************************************
 *
 * \brief Print all Dpll Register data and the current state .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllDpllValues(void);

/**
 *******************************************************************************
 *
 * \brief Init PMLIB ClockRate . Initialize during system init
 *
 * \return None
 *
 *******************************************************************************
 */
Int32 Utils_prcmClockRateInit(void);

/**
 *******************************************************************************
 *
 * \brief Print all CPU Frequency .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllCPUFrequency(void);

/**
 *******************************************************************************
 *
 * \brief Print all the Peripheral Frequency .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllPeripheralsFrequency(void);

/**
 *******************************************************************************
 *
 * \brief Print all Module current state .
 *        Print the Module SIDLE State,
 *                Clock Activity State,
 *                  Power Domain State.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllModuleState(void);

/**
 *******************************************************************************
 *
 * \brief Dummy I2C initialization function for PMIC Communication.
 *
 * \return None
 *
 *******************************************************************************
 */
Int32 Utils_prcmVoltageInit(Void);

/**
 *******************************************************************************
 *
 * \brief Initialize the INA226 to print the power consumption
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintPowerConsumptionInit(Void);

/**
 *******************************************************************************
 *
 * \brief Print Power consumption
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintPowerConsumption(Void);

#endif

/* @} */
