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
 * \defgroup SYSTEM_IMPL   System framework implementation
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file system_priv_common.h
 *
 * \brief  Header file for all system link internal APIs.
 *
 * \version 0.0 (Jun 2013) : [KC] First version taken from DVR RDK and
 *                                cleaned up for Vision_sdk
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 *
 *******************************************************************************
 */

#ifndef SYSTEM_PRIV_COMMON_H_
#define SYSTEM_PRIV_COMMON_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_tsk.h>
#include <src/rtos/utils_common/include/utils_buf.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/include/utils_taskTimer.h>

#include <include/link_api/system.h>
#include <include/link_api/system_common.h>
#include <include/link_api/systemLink_common.h>

#include <ti/drv/vps/include/vps_capture.h>
#include <ti/drv/vps/include/vps_displayCtrl.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/include/dss/vps_displayDss.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#ifndef RADAR_ONLY
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>
#include <ti/xdais/dm/ividenc2.h>
#endif
#include <src/rtos/utils_common/src/utils_link_stats_collector.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */



/**
 * @def   SYSTEM_LINK_FRAMES_PER_CH
 * @brief COntrols the default number of buffers allocated per channel in each link
 */

/**
 *******************************************************************************
 *
 * \brief Macro defining default frames allocated per channel for link.
 *
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_FRAMES_PER_CH   (4U)

/**
 *******************************************************************************
 *
 * \brief Macro defining max frames allocated per channel for link.
 *
 *        If user gives channels more than max it will be overridden by this
 *        number inside link.
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_MAX_FRAMES_PER_CH   (16U)


/*


    Capture driver task inside HDVPSS driver is set to HIGHEST priority.

    No other task MUST be highest priority
*/

/**
 *******************************************************************************
 *
 * \brief Message Q task priority
 *
 *
 *******************************************************************************
 */
#define SYSTEM_MSGQ_TSK_PRI              (13U)

/**
 *******************************************************************************
 *
 * \brief IPC Link task priority
 *
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_MULTI_MBX_TSK_PRI     (12U)

/**
 *******************************************************************************
 *
 * \brief IPC Link task priority
 *
 *
 *******************************************************************************
 */
#define IPC_LINK_TSK_PRI                 (12U)
/**
 *******************************************************************************
 *
 * \brief Dup link task priority
 *
 *
 *******************************************************************************
 */
#define DUP_LINK_TSK_PRI                 (12U)
/**
 *******************************************************************************
 *
 * \brief Gate link task priority
 *
 *
 *******************************************************************************
 */
#define GATE_LINK_TSK_PRI                (12U)
/**
 *******************************************************************************
 *
 * \brief Sync link task priority
 *
 *
 *******************************************************************************
 */
#define SYNC_LINK_TSK_PRI                (12U)
/**
 *******************************************************************************
 *
 * \brief Merge link task priority
 *
 *
 *******************************************************************************
 */

#define MERGE_LINK_TSK_PRI               (12U)
/**
 *******************************************************************************
 *
 * \brief Null link task priority
 *
 *
 *******************************************************************************
 */
#define NULL_LINK_TSK_PRI               (4U)

/**

 *******************************************************************************
 *
 * \brief Network Tx link task priority
 *
 *
 *******************************************************************************
 */
#define NETWORK_TX_LINK_TSK_PRI               (4U)

/**

 *******************************************************************************
 *
 * \brief Network Rx link task priority
 *
 *
 *******************************************************************************
 */
#define NETWORK_RX_LINK_TSK_PRI               (4U)
/**
 *******************************************************************************
 *
 * \brief Graphic Src link task priority
 *
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_TSK_PRI               (1U)

/**
 *******************************************************************************
 *
 * \brief capture link task priority
 *
 *
 *******************************************************************************
 */

#define CAPTURE_LINK_TSK_PRI             (10U)

/**
 *******************************************************************************
 *
 * \brief Iss capture link task priority
 *
 *
 *******************************************************************************
 */

#define ISSCAPTURE_LINK_TSK_PRI             (10U)

/**
 *******************************************************************************
 *
 * \brief Iss m2m isp link task priority
 *
 *
 *******************************************************************************
 */

#define ISSM2MISP_LINK_TSK_PRI             (10U)

/**
 *******************************************************************************
 *
 * \brief Iss simcop isp link task priority
 *
 *
 *******************************************************************************
 */

#define ISSM2MSIMCOP_LINK_TSK_PRI             (10U)

/**
 *******************************************************************************
 *
 * \brief Iss m2m isp link task priority
 *
 *
 *******************************************************************************
 */

#define ISS_RESIZER_LINK_TSK_PRI	(8U)

/**
 *******************************************************************************
 *
 * \brief AvbRx link task priority
 *
 *
 *******************************************************************************
 */
#define AVB_RX_LINK_TSK_PRI             (10U)

/**
 *******************************************************************************
 *
 * \brief AvbTx link task priority
 *
 *
 *******************************************************************************
 */
#define AVB_TX_LINK_TSK_PRI             (4U)

/**
 *******************************************************************************
 *
 * \brief TfdtpRx link task priority
 *
 *
 *******************************************************************************
 */
#define TFDTP_RX_LINK_TSK_PRI             (10U)


/**
 *******************************************************************************
 *
 * \brief VPE link task priority
 *
 *
 *******************************************************************************
 */
#define VPE_LINK_TSK_PRI                 (8U)

/**
 *******************************************************************************
 *
 * \brief DSSM2MWB link task priority
 *
 *
 *******************************************************************************
 */
#define DSSM2MWB_LINK_TSK_PRI           (8U)

/**
 *******************************************************************************
 *
 * \brief Software Mosaic link task priority
 *
 *
 *******************************************************************************
 */
#define SW_MS_LINK_TSK_PRI               (8U)
/**
 *******************************************************************************
 *
 * \brief Select link task priority
 *
 *
 *******************************************************************************
 */
#define SELECT_LINK_TSK_PRI              (12U)

/**
 *******************************************************************************
 *
 * \brief Null Source link task priority
 *
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_TSK_PRI               (10U)

/**
 *******************************************************************************
 *
 * \brief Display link task priority
 *
 *
 *******************************************************************************
 */
#define DISPLAY_LINK_TSK_PRI             (9U)
/**
 *******************************************************************************
 *
 * \brief Display controller link task priority
 *
 *
 *******************************************************************************
 */
#define DISPLAYCTRL_LINK_TSK_PRI         (4U)
/**
 *******************************************************************************
 *
 * \brief Display Multi Pipe link task priority
 *
 *
 *******************************************************************************
 */
#define DISPLAY_MULTI_PIPE_LINK_TSK_PRI  (9U)

/**
 *******************************************************************************
 *
 * \brief System task priority
 *
 *
 *******************************************************************************
 */
#ifdef SRV_FAST_BOOT_INCLUDE
    /*
     *  For SRV fast boot there is a thread created for doing the DSP load
        in parallel whose priority should be lower than the system task.
        And priority of 1 is the least.
     */
    #define SYSTEM_TSK_PRI                   (2U)
#else
    #define SYSTEM_TSK_PRI                   (1U)
#endif

/**
 *******************************************************************************
 *
 * \brief Algorithm link task priority
 *
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_TSK_PRI             (2U)

/**
 *******************************************************************************
 *
 * \brief Remote Debug client task priority
 *
 *
 *******************************************************************************
 */
#define REMOTE_LOG_CLIENT_TSK_PRI      (1U)

/**
 *******************************************************************************
 *
 * \brief DEC link task priority
 *
 *
 *******************************************************************************
 */
#define DEC_LINK_TSK_PRI                 (8U)

/**
 *******************************************************************************
 *
 * \brief ENC link task priority
 *
 *
 *******************************************************************************
 */
#define ENC_LINK_TSK_PRI                 (7U)

/**
 *******************************************************************************
 *
 * \brief Task size for links using large stack like capture and display links.
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_STACK_SIZE_LARGE      (32U*KB)
/**
 *******************************************************************************
 *
 * \brief Task size for links using medium stack
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_STACK_SIZE_MEDIUM     (16U*KB)
/**
 *******************************************************************************
 *
 * \brief Task size for links using small stack like select link
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_STACK_SIZE_SMALL      ( 8U*KB)

/**
 *******************************************************************************
 *
 * \brief Max task size
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_STACK_SIZE_MAX        (SYSTEM_TSK_STACK_SIZE_LARGE)

/**
 *******************************************************************************
 *
 * \brief Default task stack size
 *
 *******************************************************************************
 */
#define SYSTEM_DEFAULT_TSK_STACK_SIZE    (SYSTEM_TSK_STACK_SIZE_LARGE)

/**
 *******************************************************************************
 *
 * \brief Task size for system task
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_STACK_SIZE            (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for capture link task
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task stack size for ISS capture link task
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task stack size for ISS M2M ISP link task
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task stack size for ISS M2M ISP link task
 *
 *******************************************************************************
 */
#define ISS_RESIZER_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for AvbRx link task
 *
 *******************************************************************************
 */
#define AVB_RX_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for AvbTx link task
 *
 *******************************************************************************
 */
#define AVB_TX_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for TfdtpRx link task
 *
 *******************************************************************************
 */
#define TFDTP_RX_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for VPE link task
 *
 *******************************************************************************
 */
#define VPE_LINK_TSK_STACK_SIZE          (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for DSSM2MWB link task
 *
 *******************************************************************************
 */
#define DSSM2MWB_LINK_TSK_STACK_SIZE    (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for Display link task
 *
 *******************************************************************************
 */
#define DISPLAY_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Display link task
 *
 *******************************************************************************
 */
#define DISPLAY_MULTI_PIPE_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Display controller link task
 *
 *******************************************************************************
 */
#define DISPLAYCTRL_LINK_TSK_STACK_SIZE  (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Software mosaic link task
 *
 *******************************************************************************
 */
#define SW_MS_LINK_TSK_STACK_SIZE        (SYSTEM_DEFAULT_TSK_STACK_SIZE)

/**
 *******************************************************************************
 *
 * \brief Task size for Duplicate link task
 *
 *******************************************************************************
 */
#define DUP_LINK_TSK_STACK_SIZE          (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Gate link task
 *
 *******************************************************************************
 */
#define GATE_LINK_TSK_STACK_SIZE          (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Duplicate link task
 *
 *******************************************************************************
 */
#define SYNC_LINK_TSK_STACK_SIZE          (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for merge link task
 *
 *******************************************************************************
 */
#define MERGE_LINK_TSK_STACK_SIZE        (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for MessageQ link task
 *
 *******************************************************************************
 */
#define SYSTEM_MSGQ_TSK_STACK_SIZE       (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Select link task
 *
 *******************************************************************************
 */
#define SELECT_LINK_TSK_STACK_SIZE       (SYSTEM_TSK_STACK_SIZE_SMALL)
/**
 *******************************************************************************
 *
 * \brief Task size for Graphic link task
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_TSK_STACK_SIZE         (SYSTEM_TSK_STACK_SIZE_SMALL)
/**
 *******************************************************************************
 *
 * \brief Task size for Null link task
 *
 *******************************************************************************
 */
#define NULL_LINK_TSK_STACK_SIZE         (SYSTEM_TSK_STACK_SIZE_SMALL)
/**
 *******************************************************************************
 *
 * \brief Task size for network link task
 *
 *******************************************************************************
 */
#define NETWORK_TX_LINK_TSK_STACK_SIZE         (SYSTEM_TSK_STACK_SIZE_SMALL)
/**
 *******************************************************************************
 *
 * \brief Task size for network rx link task
 *
 *******************************************************************************
 */
#define NETWORK_RX_LINK_TSK_STACK_SIZE         (SYSTEM_TSK_STACK_SIZE_SMALL)

/**
 * \brief Task size for remote debug client task
 *
 *******************************************************************************
 */
#define REMOTE_LOG_CLIENT_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Null Source link task
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Decode link task
 *
 *******************************************************************************
 */
#define DEC_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)
/**
 *******************************************************************************
 *
 * \brief Task size for Encode link task
 *
 *******************************************************************************
 */
#define ENC_LINK_TSK_STACK_SIZE      (SYSTEM_DEFAULT_TSK_STACK_SIZE)


/**
 *******************************************************************************
 * \brief Link state: Idle, i.e not created state.
 *                    At system init or after 'delete'
 *******************************************************************************
 */
#define SYSTEM_LINK_STATE_IDLE          (0U)

/**
 *******************************************************************************
 * \brief Link state: After 'create' but before 'start'
 *******************************************************************************
 */
#define SYSTEM_LINK_STATE_CREATED       (1U)

/**
 *******************************************************************************
 * \brief Link state: After 'create' and 'start'
 *******************************************************************************
 */
#define SYSTEM_LINK_STATE_RUNNING       (2U)

/**
 *******************************************************************************
 * \brief Link state: After 'stop'
 *******************************************************************************
 */
#define SYSTEM_LINK_STATE_STOPPED       (3U)

/**
 *******************************************************************************
 * \brief Core state: Core is active and ready to recieve IPC messages
 *******************************************************************************
 */
#define SYSTEM_CORE_STATE_ACTIVE        (0U)

/**
 *******************************************************************************
 * \brief Core state: Core disabled due to an RTI Expiry
 *******************************************************************************
 */
#define SYSTEM_CORE_STATE_RTI_EXPIRED   (1U)

/**
 *******************************************************************************
 * \brief Core state: Core powered down for power management
 *******************************************************************************
 */
#define SYSTEM_CORE_STATE_POWER_DOWN    (2U)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  System link structure with information of all links
 *
 *******************************************************************************
*/
typedef struct {
    Utils_MbxHndl mbx;
    /**< Hanle to mail box */
    BspOsal_TaskHandle tsk;
    /**< Handle to system link task */
    Task_FuncPtr chainsMainFunc;
    /**< Function pointer for app start function */
    System_LinkObj linkObj[SYSTEM_LINK_ID_MAX];
    /**< Array of link objects for storing link information of all links */
    SystemLink_CmdHandler systemLinkCmdHandler[SYSTEM_COMMON_MAX_CMD_HANDLERS];
    /**< Handlers for system link command's */
    UInt32 coreState[SYSTEM_PROC_MAX];
    /**< Maintain status of all the cores in the system.
     * Framework only maintains the state. It does not detect it.
     * State is queried using System_getCoreState(procId)
     * State can be set using System_setCoreState(procId, status)
     */
} System_CommonObj;

/**
 *******************************************************************************
 * \brief System object extern declaration
 *******************************************************************************
 */
extern System_CommonObj gSystem_objCommon;




Int32 System_initCommon(void);
Int32 System_deInitCommon(void);

Void System_initLinks(void);
Void System_deInitLinks(void);

Utils_TskHndl *System_getLinkTskHndl(UInt32 linkId);

void System_memPrintHeapStatus(void);

void System_enumAssertCheck(void);

Int32 System_linkControl_local(UInt32 linkId, UInt32 cmd, Void * pPrm,
                               UInt32 prmSize, Bool waitAck);
Int32 System_sendLinkCmd_local(UInt32 linkId, UInt32 cmd, Void *payload);
Int32 System_linkGetInfo_local(UInt32 linkId, System_LinkInfo * info);

Int32 System_linkControl_remote(UInt32 linkId, UInt32 cmd, Void * pPrm,
                                UInt32 prmSize, Bool waitAck);

Int32 SystemLink_init(void);
Int32 SystemLink_deInit(void);
Void  SystemLink_userCmdHandler(UInt32 cmd, Void * pPrm);
Int32 System_start(Task_FuncPtr chainsMainFunc);

Void System_triggerAppExit(void);
Void System_triggerAppExitDone(void);
Void System_triggerAppExitDone(void);

Void System_initDone(void);
Void System_testInitDone(void);
Void System_coreInitDone(UInt32 remoteCoreId);
Void System_coreTestInitDone(UInt32 remoteCoreId);
Void System_confirmInitDone(void);

UInt32 System_getCoreState(UInt32 procId);

/* Set status = SYSTEM_CORE_STATE_ACTIVE when active
 * Set status = SYSTEM_CORE_STATE_RTI_EXPIRED when the RTI timer expires
 * Set status = SYSTEM_CORE_STATE_POWER_DOWN when a request to power down
 *              the core occurs.
 * If any other value given then the status is set to default of
 * SYSTEM_CORE_STATE_POWER_DOWN.
 */
Void System_setCoreState(UInt32 procId, UInt32 status);

Utils_TskMultiMbxHndl *System_getTskMultiMbxHndl(void);

Void System_initLinks(void);
Void System_deInitLinks(void);

#endif

/* @} */
