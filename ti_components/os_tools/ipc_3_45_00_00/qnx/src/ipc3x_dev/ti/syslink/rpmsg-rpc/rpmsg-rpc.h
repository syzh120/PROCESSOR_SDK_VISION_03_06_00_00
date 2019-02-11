/**
 *  @file   rpmsg-omxdrv.h
 *
 *  @brief      Definitions of rpmsg-omxdrv internal types and structures.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2011-2012, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */


#ifndef RPMSGRPC_DRV_H_0xf2ba
#define RPMSGRPC_DRV_H_0xf2ba


#if defined (__cplusplus)
extern "C" {
#endif

#include <ti/ipc/rpmsg_rpc.h>

/* =============================================================================
 *  Macros and types
 * =============================================================================
 */

/** The applicable types of messages that the HOST may send the SERVICE.
 */
enum rppc_msg_type {
    /** Ask Service for channel information, uses \ref OmapRpc_ChannelInfo */
    RPPC_MSG_QUERY_CHAN_INFO = 0,
    /** The return message from OMAPRPC_MSG_QUERY_CHAN_INFO*/
    RPPC_MSG_CHAN_INFO = 1,
    /** Ask the Service Instance to send information about the Service.
     * Uses \ref OmapRpc_QueryFunction */
    RPPC_MSG_QUERY_FUNCTION = 2,
    /** The return message from OMAPRPC_QUERY_INSTANCE,
     * which contains the information about the instance.
     * Uses \ref OmapRpc_Instance_Info */
    RPPC_MSG_FUNCTION_INFO = 3,
    /** Ask the ServiceMgr to create a new instance of the service.
     * No secondary data is needed. */
    RPPC_MSG_CREATE_INSTANCE = 6,
    /** The return message from OMAPRPC_CREATE_INSTANCE,
     * contains the new endpoint address in the OmapRpc_InstanceHandle */
    RPPC_MSG_INSTANCE_CREATED = 8,
    /** Ask the Service Mgr to destroy an instance */
    RPPC_MSG_DESTROY_INSTANCE = 4,
    /** The return message from OMAPRPC_DESTROY_INSTANCE.
     * contains the old endpoint address in the OmapRpc_InstanceHandle */
    RPPC_MSG_INSTANCE_DESTROYED = 7,
    /** Ask the Service Instance to call a particular function */
    RPPC_MSG_CALL_FUNCTION = 5,
    /** The return values from a function call */
    RPPC_MSG_FUNCTION_RETURN = 9,
    /** Returned from either the ServiceMgr or Service Instance
     * when an error occurs */
    RPPC_MSG_ERROR = 10,
    /** \hidden used to define the max msg enum, not an actual message */
    RPPC_MSG_MAX
};

struct rppc_msg_header {
    uint32_t  msg_type;    /**< @see rppc_msg_type */
    uint32_t  msg_len;     /**< The length of the message data in bytes */
};

struct rppc_instance_handle {
    uint32_t endpoint_address;
    uint32_t status;
};

struct rppc_channel_info {
    UInt32 num_funcs;      /**< The number of functions supported on this endpoint */
};

#define RPPC_TRANS_SIZE(num)   (sizeof(struct rppc_param_translation) * num)

#define RPPC_PARAM_SIZE(num)   (sizeof(struct rppc_function) +\
                                RPPC_TRANS_SIZE(num))

/*!
 *  @brief  Max number of user processes supported
 */
#define  MAX_PROCESSES          256u

/*!
 *  @brief  Max number of connections supported
 */
#define  MAX_CONNS              64

/*!
 *  @brief  Number of event entries to cache
 */
#define  CACHE_NUM              10

/*!
 *  @brief  Structure that defines the MsgList elem
 */
typedef struct MsgList {
    int index;
    int num_events;
    struct MsgList *next;
    struct MsgList *prev;
} MsgList_t;

/*!
 *  @brief  Structure that defines the Waiting Readers list element
 */
typedef struct WaitingReaders {
    int rcvid;
    struct WaitingReaders *next;
} WaitingReaders_t;


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* RPMSGRPC_DRV_H_0xf2ba */
