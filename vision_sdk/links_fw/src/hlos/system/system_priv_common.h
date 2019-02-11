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

#ifndef _SYSTEM_PRIV_COMMON_H_
#define _SYSTEM_PRIV_COMMON_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/link_api/system.h>
#include <include/link_api/system_common.h>
#include <include/link_api/systemLink_common.h>
#include <include/link_api/system_inter_link_api.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/nullLink.h>
#include <include/link_api/nullSrcLink.h>
#include <include/link_api/dispDistSrcLink.h>
#include <include/link_api/dupLink.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/selectLink.h>
#include <include/link_api/gateLink.h>
#include <include/link_api/sgxFrmcpyLink.h>
#include <include/link_api/sgx3DsrvLink.h>
#include <include/link_api/sgx3DsfmLink.h>
#include <include/link_api/epLink.h>

#include <links_fw/src/hlos/osa/include/osa_tsk.h>
#include <links_fw/src/hlos/osa/include/osa_mutex.h>
#include <osa_que.h>
#include <osa_mem.h>
#include <osa_sem.h>

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
#define SYSTEM_LINK_FRAMES_PER_CH   (4)

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
#define SYSTEM_LINK_MAX_FRAMES_PER_CH   (16)


/*


    Capture driver task inside HDVPSS driver is set to HIGHEST priority.

    No other task MUST be highest priority
*/

/**
 *******************************************************************************
 *
 * \brief Notify task priority
 *
 *
 *******************************************************************************
 */
#define SYSTEM_RPMSG_NOTIFY_TSK_PRI              (OSA_THR_PRI_MAX)


/**
 *******************************************************************************
 *
 * \brief Message Q task priority
 *
 *
 *******************************************************************************
 */
#define SYSTEM_RPMSG_MSGQ_TSK_PRI                (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief IPC Link task priority
 *
 *
 *******************************************************************************
 */
#define IPC_LINK_TSK_PRI                         (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief System task priority
 *
 *
 *******************************************************************************
 */
#define SYSTEM_TSK_PRI                           (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief Algorithm link task priority
 *
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_TSK_PRI                   (OSA_THR_PRI_DEFAULT)


/**
 *******************************************************************************
 *
 * \brief Algorithm link task priority
 *
 *
 *******************************************************************************
 */
#define NULL_LINK_TSK_PRI                        (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief NULL SRC task priority
 *
 *
 *******************************************************************************
 */
#define NULL_SRC_LINK_TSK_PRI                    (OSA_THR_PRI_DEFAULT)


/**
 *******************************************************************************
 *
 * \brief DUP task priority
 *
 *
 *******************************************************************************
 */
#define DUP_LINK_TSK_PRI                         (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief MERGE task priority
 *
 *
 *******************************************************************************
 */
#define MERGE_LINK_TSK_PRI                       (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief SYNC task priority
 *
 *
 *******************************************************************************
 */
#define SYNC_LINK_TSK_PRI                        (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief MERGE task priority
 *
 *
 *******************************************************************************
 */
#define SELECT_LINK_TSK_PRI                      (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief SYNC task priority
 *
 *
 *******************************************************************************
 */
#define GATE_LINK_TSK_PRI                        (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief Remote Debug client task priority
 *
 *
 *******************************************************************************
 */
#define REMOTE_LOG_CLIENT_TSK_PRI                (OSA_THR_PRI_MIN)


/**
 *******************************************************************************
 *
 * \brief SgxDisplay link task priority
 *
 *
 *******************************************************************************
 */
#define SGXFRMCPY_LINK_TSK_PRI                   (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief Srv2DInfoAdas link task priority
 *
 *
 *******************************************************************************
 */
#define SRV2DINFOADAS_LINK_TSK_PRI               (OSA_THR_PRI_DEFAULT)
#define SRV3DINFOADAS_LINK_TSK_PRI               (OSA_THR_PRI_DEFAULT)
#define SRV3D_LINK_TSK_PRI                       (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief Sgx3Dsrv link task priority
 *
 *
 *******************************************************************************
 */
#define SGX3DSRV_LINK_TSK_PRI                    (OSA_THR_PRI_DEFAULT)

/**
 *******************************************************************************
 *
 * \brief Display Distributor Src link task priority
 *
 *
 *******************************************************************************
 */
#define DISP_DIST_SRC_LINK_TSK_PRI                    (OSA_THR_PRI_DEFAULT)

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
 *
 * \brief Task size for links using large stack like capture and display links.
 *
 *******************************************************************************
 */
#ifdef OPENCL_INCLUDE
#define SYSTEM_TSK_STACK_SIZE_LARGE      (64U*KB)
#else
#define SYSTEM_TSK_STACK_SIZE_LARGE      (32U*KB)
#endif
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


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 * \brief System Task Descriptor
 */
typedef struct
{
    OSA_MutexHndl           linkControlMutex;
    OSA_MbxHndl             mbx;
    System_LinkObj          linkObj[SYSTEM_LINK_ID_MAX];
    Int32                   devBufFD;
/*< Global object file desc handle for the dmabuf exporter context */
} System_CommonObj;


/**
 *******************************************************************************
 * \brief System object extern declaration
 *******************************************************************************
 */
extern System_CommonObj gSystem_objCommon;

Void System_initLinks(void);
Void System_deInitLinks(void);

OSA_TskHndl *System_getLinkTskHndl(UInt32 linkId);


Int32 System_linkControl_local(UInt32 linkId, UInt32 cmd, Void * pPrm,
                               UInt32 prmSize, Bool waitAck);
Int32 System_sendLinkCmd_local(UInt32 linkId, UInt32 cmd, Void *payload);
Int32 System_linkGetInfo_local(UInt32 linkId, System_LinkInfo * info);

Int32 System_linkControl_remote(UInt32 linkId, UInt32 cmd, Void * pPrm,
                                UInt32 prmSize, Bool waitAck);

Int32 SystemLink_init(void);
Int32 SystemLink_deInit(void);



#endif

/* @} */
