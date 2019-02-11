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
 * \ingroup SYSTEM_LINK_API System Link API
 *
 * @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file system_common.h
 *
 * \brief This module has the system data structures and constants shared
 *        across the processors.
 *
 * \version 0.0 (Jun 2013) : [KC] First Version
 * \version 0.1 (Jun 2013) : [KC] Updates as per code review comments
 * \version 0.2 (Aug 2013) : [KC] Added CMDs and structures to print statistics
 * \version 0.2 (Mar 2015) : [YM] Added rmpsg message types and changed endpts
 *
 *******************************************************************************
 */

#ifndef SYSTEM_COMMON_H_
#define SYSTEM_COMMON_H_

/*******************************************************************************
 * Include files
 *******************************************************************************
 */


/*******************************************************************************
 * Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 * \brief Frequency values of various cores set explicitly during system init
 *
 *******************************************************************************
 */
#if defined(TDA2XX_BUILD)
#define SYSTEM_DSP_FREQ            (600000000U)
#define SYSTEM_EVE_FREQ            (267500000U)
#define SYSTEM_IPU_FREQ            (212000000U)
#define SYSTEM_A15_FREQ            (588000000U)
#endif

#if defined(TDA2PX_BUILD)
#define SYSTEM_DSP_FREQ            (600000000U)
#define SYSTEM_EVE_FREQ            (267500000U)
#define SYSTEM_IPU_FREQ            (212000000U)
#define SYSTEM_A15_FREQ            (588000000U)
#endif

#if defined(TDA3XX_BUILD)
#define SYSTEM_DSP_FREQ            (500000000U)
#define SYSTEM_EVE_FREQ            (250000000U)
#define SYSTEM_IPU_FREQ            (212000000U)
#endif

#if defined(TDA2EX_BUILD)
#define SYSTEM_DSP_FREQ            (600000000U)
#define SYSTEM_IPU_FREQ            (212000000U)
#define SYSTEM_A15_FREQ            (588000000U)
#endif

/**
 *******************************************************************************
 *
 * \brief System command to create a link
 *
 * \param Void *    [IN] Link specific parameters
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_CREATE                   (0x00000000U)

/**
 *******************************************************************************
 *
 * \brief System command to start a link
 *
 * \param None
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_START                    (0x00000001U)

/**
 *******************************************************************************
 *
 * \brief System command to stop a link
 *
 * \param None
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_STOP                     (0x00000002U)

/**
 *******************************************************************************
 *
 * \brief System command to delete a link
 *
 * \param None
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_DELETE                   (0x00000003U)

/**
 *******************************************************************************
 *
 * \brief System command to send data a link
 *
 * \param None
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_NEW_DATA                 (0x00000004U)

/**
 *******************************************************************************
 *
 * \brief System command to get information about a link. Normally this is
 *        used by a link to get the previous link's System_LinkInfo
 *
 * \param System_LinkInfo * [OUT] Link information
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_GET_INFO                 (0x00000005U)

/**
 *******************************************************************************
 *
 * \brief System command to print link statistics
 *
 * \param None
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_PRINT_STATISTICS         (0x00000FFFU)

/**
 *******************************************************************************
 *
 * \brief System command to print buffer related statistics for a link
 *
 * \param None
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_PRINT_BUFFER_STATISTICS  (0x00000007U)

/**
 *******************************************************************************
 *
 * \brief System commands with link-specific interpretation
 *
 * \param Link-specific
 *
 *******************************************************************************
 */
#define SYSTEM_CMD_USER0 (0x00000008U)
#define SYSTEM_CMD_USER1 (0x00000009U)
#define SYSTEM_CMD_USER2 (0x0000000AU)

/**
 *******************************************************************************
 *
 * \brief The line and event ID of IPC Notify
 *
 *******************************************************************************
 */
#define SYSTEM_IPC_NOTIFY_LINE_ID   (0U)
#define SYSTEM_IPC_NOTIFY_EVENT_ID  (15U)

/**
 *******************************************************************************
 *
 * \brief Define the IPC Message Queue heap and message parameters.
 *
 *******************************************************************************
 */

static inline void* SystemIpcMsgqPayloadPtr(const void* msg);

/**
 * \brief Remote end point, This will be created on slave cores
 */
#define SYSTEM_RPMSG_ENDPT_REMOTE          (80U)

/**
 * \brief This will be created at host and used by rpmsg notify module
 *        to receive notifications from slave
 */
#define SYSTEM_RPMSG_NOTIFY_ENDPT_HOST     (81U)

/**
 * \brief This will be created at host and used by rpmsg msgQ module
 *        to receive data messages from slave
 */
#define SYSTEM_RPMSG_MSGQ_DATA_ENDPT_HOST  (82U)

/**
 * \brief This will be created at host and used by rpmsg msgQ module
 *        to receive ack messages from slave
 */
#define SYSTEM_RPMSG_MSGQ_ACK_ENDPT_HOST   (83U)


/**
 *******************************************************************************
 *
 * \brief The names of processor cores in the system
 *
 *******************************************************************************
 */
#define SYSTEM_IPC_PROC_NAME_DSP1            "DSP1"
#define SYSTEM_IPC_PROC_NAME_DSP2            "DSP2"
#define SYSTEM_IPC_PROC_NAME_EVE1            "EVE1"
#define SYSTEM_IPC_PROC_NAME_EVE2            "EVE2"
#define SYSTEM_IPC_PROC_NAME_EVE3            "EVE3"
#define SYSTEM_IPC_PROC_NAME_EVE4            "EVE4"
#define SYSTEM_IPC_PROC_NAME_IPU1_0          "IPU1-0"
#define SYSTEM_IPC_PROC_NAME_IPU1_1          "IPU1-1"
#define SYSTEM_IPC_PROC_NAME_IPU2            "IPU2"
#define SYSTEM_IPC_PROC_NAME_A15_0           "HOST"
#define SYSTEM_IPC_PROC_NAME_INVALID         "INVALID PROC"



/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 * Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Message exchanged using the IPC message queue
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 linkId;
    /**< The unique ID of the link the message is sent to */
    UInt32 cmd;
    /**< The command passed between links */
    UInt32 prmSize;
    /**< The size of the parameter */
    UInt32 waitAck;
    /**< wait for ACK flag */
    UInt32 status;
    /**< Message passing status */

} SystemIpcMsgQ_Msg;


/*******************************************************************************
 * Functions
 *******************************************************************************
 */
static inline void* SystemIpcMsgqPayloadPtr(const void* msg)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    UInt32 temp;

/* MISRA.CAST.PTR_TO_INT
 * MISRAC_2004 Rule 11.3
 * Cast between a pointer and an integral type
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: To increment the pointer, its converted to uint32 value and
 *                  the size is added. This require conversion of pointer to
 *                  uint32 and vice versa. Since the caller of this function
 *                  will always pass the message, this is not an issue.
 */

    temp = (UInt32) msg + (UInt32) sizeof(SystemIpcMsgQ_Msg);
    return (void *)temp;
}

/**
 *******************************************************************************
 * \brief Global object for defining which Processors needs to be enabled.
 *
 * This is required to loop around the IPC attach and other ipc functions
 * based on processors enabled in links and chains.
 *
 * This array is defined in src/links_common/system/system_common.c
 *
 * \warning The araay is size is MAX + 2 to ensure we have space to hold MAX
 *          marker and invalid entry marker.
 *******************************************************************************
 */
extern UInt32 gSystem_ipcEnableProcId[SYSTEM_PROC_MAX + 2U];

/**
 *******************************************************************************
 *
 * \brief Convert from LCFW Proc ID to Syslink Proc ID
 *
 *        Syslink/IPC Proc ID could be different from Links and Chains FW
 *        Proc ID and framework does not rely on syslink/IPC Proc ID and
 *        LCFW Proc ID being same.
 *
 * \param procId    [IN] Syslink Proc ID
 *
 * \return Links & Chains FW Processor ID
 *
 *******************************************************************************
 */
UInt32 System_getSyslinkProcId(UInt32 procId);


/**
 *******************************************************************************
 *
 * \brief Convert from LCFW Proc ID to IpcLib Proc ID
 *
 *        IpcLib Proc ID could be different from Links and Chains FW
 *        Proc ID and framework does not rely on syslink/IPC Proc ID and
 *        LCFW Proc ID being same.
 *
 * \param procId    [IN] Syslink Proc ID
 *
 * \return Links & Chains FW Processor ID
 *
 *******************************************************************************
 */
UInt32 System_getIpcLibProcId(UInt32 procId);

/**
 *******************************************************************************
 *
 * \brief Configures IpcLib is SAFE_IPC_INCLUDE is yes
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_ipcInitConfig(void);

/**
 *******************************************************************************
 *
 * \brief de-initializes IpcLib is SAFE_IPC_INCLUDE is yes
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_ipcDeInitConfig(void);

/**
 *******************************************************************************
 *
 * \brief Initializes all the links required for the core
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_initLinks(void);

/**
 *******************************************************************************
 *
 * \brief De-initializes all the links of the core
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_deInitLinks(void);

/**
 *******************************************************************************
 *
 * \brief Common configuration of Main app, same for all Apps.
 *        and the Apps specific seetings can be done in apps main_<core>.c
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 main_common(void);

#endif

/* @} */
