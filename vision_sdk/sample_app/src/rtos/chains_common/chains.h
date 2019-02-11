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
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_CHAIN APIs for selecting the usecase chain.
 *
 * \brief  APIs for selecting the required usecase chain and run
 *         time menu configurations .
 *         It also provide API's for instrumentation of load and heap usage
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains.h
 *
 * \brief APIs for selecting the required usecase chain.
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef _CHAINS_H_
#define _CHAINS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/board.h>
#include <src/rtos/utils_common/include/utils_uart.h>
#include <src/rtos/utils_common/include/utils_qspi.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_l3_emif_bw.h>
#include <src/rtos/utils_common/include/utils_boot_slaves.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <ti/sysbios/knl/Task.h>
#include <include/link_api/displayCtrlLink.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
typedef struct Chains_CommonObj_t {

    UInt32  lcdInstId;
    UInt32  displayCtrlLinkId;

    DisplayCtrlLink_ConfigParams dctrlCfgPrms;
    DisplayCtrlLink_OvlyPipeParams pipeParams[4];
    DisplayCtrlLink_OvlyParams ovlyParams;

} Chains_CommonObj;
/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
 typedef enum {
     CHAINS_DISPLAY_TYPE_HDMI_720P = 0U,
     /**< Output displayed on HDMI in 720P resolution */

     CHAINS_DISPLAY_TYPE_HDMI_1080P,
     /**< Output displayed on HDMI in 1080P resolution */

     CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM,
     /**< Output displayed on HDMI in XGA resolution using 8bit TDM mode */

     CHAINS_DISPLAY_TYPE_HDMI_WXGA
     /**< Output displayed on HDMI in WXGA, Supported only on TDA3xx */

 } Chains_DisplayType;
/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief   Read a charater from UART or CCS console
 *
 * \return character that is read
 *
 *******************************************************************************
*/
Void ChainsCommon_Init();

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void ChainsCommon_DeInit();

/**
 *******************************************************************************
 *
 * \brief   Main call for usecase selection and configuration
 *
 *          Chains_main is called form the main of main_ipu1_0.c .
 *          This is the entry point for usecase selection.
 *          Board, LCD initializations and demo selections are performed.
 *          It waits in a while loop till the end of demo/usecase is triggred
 *
 *******************************************************************************
*/
char ChainsCommon_readChar();

/**
 *******************************************************************************
 *
 * \brief   Main call for usecase selection and configuration
 *
 *          Chains_main is called form the main of main_ipu1_0.c .
 *          This is the entry point for usecase selection.
 *          Board, LCD initializations and demo selections are performed.
 *          It waits in a while loop till the end of demo/usecase is triggred
 *
 *******************************************************************************
*/
Void Chains_main();

/**
 *******************************************************************************
 *
 * \brief   Print Load Calculation.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_prfCpuLoadPrint();

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


Void ChainsCommon_PrintStatistics();

/**
 *******************************************************************************
 *
 * \brief   Main call for usecase selection and configuration
 *
 *          Chains_main is called form the main of main_ipu1_0.c .
 *          This is the entry point for usecase selection.
 *          Board, LCD initializations and demo selections are performed.
 *          It waits in a while loop till the end of demo/usecase is triggred
 *
 *******************************************************************************
*/
Void Chains_nullSrc_display();

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
