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

#ifndef SYSTEM_IPC_IF_H_
#define SYSTEM_IPC_IF_H_

 /**
 *******************************************************************************
 *
 * \file system_ipc_if.h IPC Data structure interface
 *
 * \brief  Data structures that are exchanged across CPUs
 *         during IPC
 *
 *******************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/system_inter_link_api.h>
#include <include/link_api/system_work_queue_ipc_if.h>

/*******************************************************************************
 *  Define's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Max size of message send via System_linkControl API
 *******************************************************************************
 */
#define SYSTEM_IPC_MSG_SIZE_MAX     (4U*1024U)
/**
 *******************************************************************************
 * \brief Max possible IPC OUT link instances on a given CPU
 *******************************************************************************
 */
#define SYSTEM_IPC_OUT_LINK_MAX     (10U)

/**
 *******************************************************************************
 * \brief Max possible AUTOSAR IPC OUT link instances on a given CPU
 *******************************************************************************
 */
#define SYSTEM_AUTOSAR_IPC_OUT_LINK_MAX     (1U)

/**
 *******************************************************************************
 * \brief Max number of elements in IPC Out Link queue
 *******************************************************************************
 */
#define SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS        (10U)

/**
 *******************************************************************************
 * \brief Network console SHM size
 *******************************************************************************
 */
#define NETWORK_CONS_RX_SHM_SIZE    (512)

/**
 *******************************************************************************
 * \brief Network console SHM size
 *******************************************************************************
 */
#define NETWORK_CONS_TX_SHM_SIZE    (15*1024)

/**
 *******************************************************************************
 * \brief Structure that is exchange across CPUs when sending message via
 *        System_linkControl API
 *******************************************************************************
 */
typedef struct {

    uint32_t payload[(uint32_t)SYSTEM_IPC_MSG_SIZE_MAX/sizeof(uint32_t)];
    /**< Payload of message being sent to a given CPU */
} System_IpcMsg;

/**
 *******************************************************************************
 * \brief Shared memory structure that holds message structures for all CPUs
 *******************************************************************************
 */
typedef struct {

    System_IpcMsg procMsg[SYSTEM_PROC_MAX];
    /**< Per CPU message structure */

} System_IpcMsgSharedMemObj;

/**
 *******************************************************************************
 * \brief Data structure representing IPC Queue header in shared memory
 *
 *        Typically user does not need to know internals of this
 *        data structure
 *******************************************************************************
*/
typedef struct {

  volatile uint32_t curRd;
  /**< Current read index */

  volatile uint32_t curWr;
  /**< Current write index  */

  volatile uint32_t elementSize;
  /**< Size of individual element in units of bytes */

  volatile uint32_t maxElements;
  /**< Max elements that be present in the queue  */

} System_IpcQueHeader;

/**
 *******************************************************************************
 * \brief Data structure representing IPC Queue in shared memory including its
 *        queue memory
 *******************************************************************************
*/
typedef struct {

    System_IpcQueHeader queHeader;
    /**< IPC Queue header */

    uint32_t            queMem[SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U];
    /**< Memory associated with this queue
     *   One additional element is needed in queue to keep track of queue full
     *   condition so one queue entry gets wasted
     */

} System_IpcQueObj;


/**
 *******************************************************************************
 * \brief Network Console IPC memory
 *******************************************************************************
*/
typedef struct {

    System_IpcQueHeader queHeader;
    /**< IPC Queue header */

    uint8_t             queMem[NETWORK_CONS_RX_SHM_SIZE];
    /**< Memory associated with this queue */

} NetworkCons_RxShm;

/**
 *******************************************************************************
 * \brief Network Console IPC memory
 *******************************************************************************
*/
typedef struct {

    System_IpcQueHeader queHeader;
    /**< IPC Queue header */

    uint8_t             queMem[NETWORK_CONS_TX_SHM_SIZE];
    /**< Memory associated with this queue */

} NetworkCons_TxShm;

/**
 *******************************************************************************
 * \brief Data structure all IPC Queue's on a given CPU including the memory
 *        associated with System_IpcBuffers that are exchanged
 *******************************************************************************
*/
typedef struct {

    System_IpcQueObj    queOut2InObj[SYSTEM_IPC_OUT_LINK_MAX];
    /**< IPC Queue objects for each IPC Out link on a given CPU */

    System_IpcQueObj    queIn2OutObj[SYSTEM_IPC_OUT_LINK_MAX];
    /**< IPC Queue objects for each IPC Out link on a given CPU */

    System_IpcBuffer    queElements[SYSTEM_IPC_OUT_LINK_MAX][SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS];
    /**< IPC Buffer elements for each IPC Out link on a given CPU */

} System_IpcQueProcObj;

/**
 *******************************************************************************
 * \brief Data structure representing all IPC Queue's on a all CPU's
 *******************************************************************************
*/
typedef struct {

    System_IpcQueProcObj    ipcQueProcObj[SYSTEM_PROC_MAX];

} System_IpcQueSharedMemObj;

/**
 *******************************************************************************
 * \brief Data structure representing IPC Queue in shared memory including its
 *        queue memory
 *******************************************************************************
*/
typedef struct {

    System_IpcQueHeader queHeader;
    /**< IPC Queue header */

    uint32_t            queMem[SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS+1U];
    /**< Memory associated with this queue
     *   One additional element is needed in queue to keep track of queue full
     *   condition so one queue entry gets wasted
     */

} System_autosarIpcQueObj;

/**
 *******************************************************************************
 * \brief Data structure all IPC Queue's on a given CPU including the memory
 *        associated with System_IpcBuffers that are exchanged
 *******************************************************************************
*/
typedef struct {

    System_autosarIpcQueObj    queA2VObj[SYSTEM_AUTOSAR_IPC_OUT_LINK_MAX];
    /**< IPC Queue objects for each IPC Out link on a given CPU */

    System_autosarIpcQueObj    queV2AObj[SYSTEM_AUTOSAR_IPC_OUT_LINK_MAX];
    /**< IPC Queue objects for each IPC Out link on a given CPU */

    System_AutosarIpcBuffer  queElements[SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS];
    /**< IPC Buffer elements for each IPC Out link on a given CPU */

} System_autosarQueProcObj;

/**
 *******************************************************************************
 * \brief Data structure representing all IPC Queue's on a all CPU's
 *******************************************************************************
*/
typedef struct {

    System_autosarQueProcObj    autosarIpcQueProcObj[2U];

    uint32_t ipcInitDone;
} System_autosarQueSharedMemObj;
/**
 *******************************************************************************
 * \brief Data structure representing all IPC information across all CPUs
 *******************************************************************************
*/
typedef struct {

    System_IpcQueSharedMemObj ipcQueObj;
    System_IpcMsgSharedMemObj ipcMsgObj;
    System_autosarQueSharedMemObj autosarIpcQueObj;
    NetworkCons_TxShm         networkConsTxShm;
    NetworkCons_RxShm         networkConsRxShm;
    System_WorkIpcObj         workIpcObj;
} System_IpcSharedMemObj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

/*******************************************************************************
 *  \brief Get pointer to message payload for a given procId
 *
 *  \param procId [IN] Processor ID
 *******************************************************************************
 */
System_IpcMsg *System_ipcGetMsg(uint32_t procId);

/*******************************************************************************
 *  \brief Get pointer to IPC Out link IPC Que object for OUT to IN Que
 *
 *  \param ipcOutLinkId [IN] Link ID of IPC Out link
 *
 *******************************************************************************
 */
System_IpcQueObj *System_ipcGetIpcOut2InQue(uint32_t ipcOutLinkId);

/*******************************************************************************
 *  \brief Get pointer to IPC Out link IPC Que object for IN to OUT Que
 *
 *  \param ipcOutLinkId [IN] Link ID of IPC Out link
 *
 *******************************************************************************
 */
System_IpcQueObj *System_ipcGetIpcIn2OutQue(uint32_t ipcOutLinkId);

/*******************************************************************************
 *  \brief Get pointer to IPC System buffer given IPC link ID and element index
 *
 *  \param ipcOutLinkId [IN] Link ID of IPC Out link
 *  \param idx        [IN] Index of element
 *
 *******************************************************************************
 */
System_IpcBuffer *System_ipcGetIpcBuffer(uint32_t ipcOutLinkId, uint32_t idx);

/*******************************************************************************
 *  \brief Get pointer to IPC Queue for Network Console RX
 *******************************************************************************
 */
NetworkCons_RxShm *System_networkConsGetRxQue(void);

/*******************************************************************************
 *  \brief Get pointer to IPC Queue for Network Console TX
 *******************************************************************************
 */
NetworkCons_TxShm *System_networkConsGetTxQue(void);

/*******************************************************************************
 *  \brief Get pointer to IPC Object for WorkQ
 *******************************************************************************
 */
System_WorkIpcObj *System_workQGetIpcObj(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


