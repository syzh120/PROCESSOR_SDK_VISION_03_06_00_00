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

/*
 *******************************************************************************
 *
 * \file chains_common.h
 *
 * \brief This file contains common utility functions used by all use-cases
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_H_
#define _CHAINS_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <src/hlos/osa/include/osa.h>

// #include <include/link_stats_monitor.h>

#include <include/link_api/system.h>
#include <include/link_api/system_common.h>
#include <include/appCtrlLink.h>
#include <include/link_api/displayCtrlLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

 typedef enum {
     CHAINS_DISPLAY_TYPE_HDMI_720P,
     /**< Output displayed on HDMI in 720P resolution */
     CHAINS_DISPLAY_TYPE_HDMI_1080P,
     /**< Output displayed on HDMI in 1080P resolution */
 } Chains_DisplayType;

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
Char Chains_readChar();

/**
 *******************************************************************************
 *
 * \brief   Read an integer from UART or CCS console
 *
 * \return integer that is read
 *
 *******************************************************************************
*/
Int32 Chains_readInt();
/**
 *******************************************************************************
 *
 * \brief   Load Calculation enable/disable
 *
 *          This functions enables load profiling. A control command
 *          SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START is passed to chianed links.
 *          If parameter Enable is set true Load profiling is enabled.
 *          If printStatus is set true a System CMD to Print CPU load,
 *          Task Laod and Heap status information is sent
 *          While creating enable = TRUE , printStatus & printTskLoad = FALSE
 *          While deleting enable = FALSE , printStatus & printTskLoad = TRUE
 *
 * \param   enable               [IN]   is set true Load profiling
 *
 * \param   printStatus          [IN] true a System CMD
 *
 * \param   printTskLoad         [IN]  true a Print CPU load
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 Chains_prfLoadCalcEnable(Bool enable,
                               Bool printStatus,
                               Bool printTskLoad);

/**
 *******************************************************************************
 *
 * \brief   Print Memory Heap Statistics
 *
 *          This function send a system control message
 *           to all cores.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_memPrintHeapStatus();
Void ChainsCommon_PrintStatistics();
/**
 *******************************************************************************
 *
 * \brief   common APP CTRL Link commands for initialization
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_appCtrlCommonInit();

/**
 *******************************************************************************
 *
 * \brief   common APP CTRL Link commands for de intialization
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 ChainsCommon_appCtrlCommonDeInit();

Int32 ChainsCommon_prfLoadCalcEnable(Bool enable, Bool printStatus, Bool printTskLoad);
Int32 ChainsCommon_prfCpuLoadPrint();
Int32 ChainsCommon_memPrintHeapStatus();
Int32 ChainsCommon_statCollectorPrint();
Int32 ChainsCommon_statCollectorReset();
void  ChainsCommon_printCpuStatus();
Void ChainsCommon_GetDisplayWidthHeight(
        Chains_DisplayType displayType,
        UInt32 *displayWidth,
        UInt32 *displayHeight);
Int32 ChainsCommon_StartDisplayCtrl(
        UInt32 displayType,
        UInt32 displayWidth,
        UInt32 displayHeight);
Int32 ChainsCommon_StopDisplayCtrl();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
