/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== OmapRpc.h ========
 *  OMAP Remote Procedure Call Driver.
 *
 */

#ifndef ti_srvmgr_OmapRpc__include
#define ti_srvmgr_OmapRpc__include

#include <ti/grcm/RcmServer.h>
#include <ti/ipc/mm/MmType.h>


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OmapRpc_S_SUCCESS
 *  @brief  Operation is successful.
 */
#define OmapRpc_S_SUCCESS              (0)

/*!
 *  @def    OmapRpc_E_FAIL
 *  @brief  Operation is not successful.
 */
#define OmapRpc_E_FAIL                 (-1)

#define OmapRpc_NUM_PARAMETERS(size) \
    ((size)/sizeof(struct OmapRpc_Parameter))

#define OmapRpc_PAYLOAD(ptr, type) \
    ((struct type *)&(ptr)[sizeof(struct OmapRpc_MsgHeader)])

#define OmapRpc_PARAM(param, type) ((param).size == sizeof(type) ? (type)(param).data : 0)

#define OmapRpc_Stringerize(func)   #func

#define OmapRpc_dimof(x)    (sizeof(x)/sizeof((x)[0]))

#define OmapRpc_DESC_EXEC_SYNC  (0x0100)
#define OmapRpc_DESC_EXEC_ASYNC (0x0200)
#define OmapRpc_DESC_SYM_ADD    (0x0300)
#define OmapRpc_DESC_SYM_IDX    (0x0400)
#define OmapRpc_DESC_CMD        (0x0500)
#define OmapRpc_DESC_TYPE_MASK  (0x0F00)
#define OmapRpc_JOBID_DISCRETE  (0)
#define OmapRpc_POOLID_DEFAULT  (0x8000)

#define OmapRpc_SET_FXN_IDX(idx)    ((idx) | 0x80000000)
#define OmapRpc_FXN_MASK(idx)       ((idx) & 0x7FFFFFFF)

#define OMAPRPC_MAX_CHANNEL_NAMELEN (64)
#define OMAPRPC_MAX_FUNC_NAMELEN    (64)
#define OMAPRPC_MAX_NUM_PARAMS      (10)
#define OMAPRPC_MAX_INST_NAMELEN    (48)

typedef enum OmapRpc_InfoType {
    /** The function signature */
    OmapRpc_InfoType_FUNC_SIGNATURE = 1,
    /** The number of times a function has been called */
    OmapRpc_InfoType_NUM_CALLS,
    /** The performance information releated to the function */
    OmapRpc_InfoType_FUNC_PERFORMANCE,

    /** @hidden used to define the maximum info type */
    OmapRpc_InfoType_MAX
} OmapRpc_InfoType;

/** The applicable types of messages that the HOST may send the SERVICE.
 */
typedef enum OmapRpc_MsgType {
    /** Ask Service for channel information, uses \ref OmapRpc_ChannelInfo */
    OmapRpc_MsgType_QUERY_CHAN_INFO = 0,
    /** The return message from OMAPRPC_MSG_QUERY_CHAN_INFO*/
    OmapRpc_MsgType_CHAN_INFO = 1,
    /** Ask the Service Instance to send information about the Service.
     * Uses \ref OmapRpc_QueryFunction */
    OmapRpc_MsgType_QUERY_FUNCTION = 2,
    /** The return message from OMAPRPC_QUERY_INSTANCE,
     * which contains the information about the instance.
     * Uses \ref OmapRpc_Instance_Info */
    OmapRpc_MsgType_FUNCTION_INFO = 3,
    /** Ask the ServiceMgr to create a new instance of the service.
     * No secondary data is needed. */
    OmapRpc_MsgType_CREATE_INSTANCE = 6,
    /** The return message from OMAPRPC_CREATE_INSTANCE,
     * contains the new endpoint address in the OmapRpc_InstanceHandle */
    OmapRpc_MsgType_INSTANCE_CREATED = 8,
    /** Ask the Service Mgr to destroy an instance */
    OmapRpc_MsgType_DESTROY_INSTANCE = 4,
    /** The return message from OMAPRPC_DESTROY_INSTANCE.
     * contains the old endpoint address in the OmapRpc_InstanceHandle */
    OmapRpc_MsgType_INSTANCE_DESTROYED = 7,
    /** Ask the Service Instance to call a particular function */
    OmapRpc_MsgType_CALL_FUNCTION = 5,
    /** The return values from a function call */
    OmapRpc_MsgType_FUNCTION_RETURN = 9,
    /** Returned from either the ServiceMgr or Service Instance
     * when an error occurs */
    OmapRpc_MsgType_ERROR = 10,
    /** \hidden used to define the max msg enum, not an actual message */
    OmapRpc_MsgType_MAX
} OmapRpc_MsgType;

typedef enum OmapRpc_ErrorType {
    /**< No errors to report */
    OmapRpc_ErrorType_NONE = 0,
    /**< Not enough memory exist to process request */
    OmapRpc_ErrorType_NOT_ENOUGH_MEMORY,
    /**< The instance died */
    OmapRpc_ErrorType_INSTANCE_DIED,
    /**< Some resource was unavailable. */
    OmapRpc_ErrorType_RESOURCE_UNAVAILABLE,
    /**< A provided parameter was either out of range, incorrect or NULL */
    OmapRpc_ErrorType_BAD_PARAMETER,
    /**< The requested item is not supported */
    OmapRpc_ErrorType_NOT_SUPPORTED,

    /** @hidden used to define the max error value */
    OmapRpc_ErrorType_MAX_VALUE
} OmapRpc_ErrorType;

typedef struct OmapRpc_CreateInstance {
    Char name[OMAPRPC_MAX_INST_NAMELEN];
} OmapRpc_CreateInstance;

typedef struct OmapRpc_ChannelInfo {
    UInt32 numFuncs;        /**< The number of functions supported on this endpoint */
} OmapRpc_ChannelInfo;

typedef struct OmapRpc_FuncPerf {
    UInt32 clocksPerSec;
    UInt32 clockCycles;
} OmapRpc_FuncPerf;

/** The parameter direction as relative to the function it describes */
typedef enum OmapRpc_Direction {
    OmapRpc_Direction_In = 0,
    OmapRpc_Direction_Out,
    OmapRpc_Direction_Bi,
    OmapRpc_Direction_MAX
} OmapRpc_Direction;

typedef enum OmapRpc_Param_Type {
    OmapRpc_Param_VOID = 0,
    OmapRpc_Param_S08,
    OmapRpc_Param_U08,
    OmapRpc_Param_S16,
    OmapRpc_Param_U16,
    OmapRpc_Param_S32,
    OmapRpc_Param_U32,
    OmapRpc_Param_S64,
    OmapRpc_Param_U64,

    OmapRpc_Param_PTR = 0x80,   /**< Logically OR'd with lower type to make a
                                     pointer to the correct type */
    OmapRpc_Param_MAX
} OmapRpc_Param_Type;

#define OmapRpc_PtrType(type)   ((type) | OmapRpc_Param_PTR)

typedef struct OmapRpc_ParamSignature {
    UInt32 direction;   /**< @see OmapRpc_Direction */
    UInt32 type;        /**< @see OmapRpc_Param_Type */
    UInt32 count;       /**< Used to do some basic sanity checking on array bounds */
} OmapRpc_ParamSignature;

/**
 * This is the data structure that represents the function signature.
 * @note The first parameter (params[0]) is the return value.
 */
typedef struct OmapRpc_FuncSignature {
    Char name[OMAPRPC_MAX_FUNC_NAMELEN];
    UInt32 numParam;
    OmapRpc_ParamSignature params[OMAPRPC_MAX_NUM_PARAMS+1];
} OmapRpc_FuncSignature;

/**
 * \brief Function Query Structure.
 * \details This is used by the host first to ask the remote side for details
 * about it's published functions
 */
typedef struct OmapRpc_QueryFunction {
    UInt32 infoType;        /**< @see OmapRpc_InfoType */
    UInt32 funcIndex;       /**< The function index to query */
    union info {
        UInt32 numCalls;
        OmapRpc_FuncPerf performance;
        OmapRpc_FuncSignature signature;
    } info;
} OmapRpc_QueryFunction;

/** @brief The generic OMAPRPC message header.
 * (actually a copy of omx_msg_hdr which is a copy of an RCM header)
 */
typedef struct OmapRpc_MsgHeader {
    UInt32 msgType;    /**< @see OmapRpc_MsgType */
    UInt32 msgLen;     /**< The length of the message data in bytes */
} OmapRpc_MsgHeader;

typedef struct OmapRpc_InstanceHandle {
    UInt32 endpointAddress;
    UInt32 status;
} OmapRpc_InstanceHandle;

typedef struct OmapRpc_Error {
    UInt32 endpointAddress;
    UInt32 status;
} OmapRpc_Error;

typedef struct OmapRpc_Parameter {
    SizeT size;
    SizeT data;
} OmapRpc_Parameter;

/** This is actually a frankensteined structure of RCM */
typedef struct OmapRpc_Packet{
    UInt16  desc;       /**< @see RcmClient_Packet.desc */
    UInt16  msgId;      /**< @see RcmClient_Packet.msgId */
    UInt16  poolId;     /**< @see RcmClient_Message.poolId */
    UInt16  jobId;      /**< @see RcmClient_Message.jobId */
    UInt32  fxnIdx;     /**< @see RcmClient_Message.fxnIdx */
    Int32   result;     /**< @see RcmClient_Message.result */
    UInt32  dataSize;   /**< @see RcmClient_Message.data_size */
} OmapRpc_Packet;

/** An OmapRpc Function is really an RCM function */
typedef RcmServer_MsgFxn OmapRpc_Function;

/**
 * \brief The Function Declaration Structure.
 * \details This structure is used to declare the function signature and their
 * associated functions
 */
typedef struct OmapRpc_FuncDeclaration {
    OmapRpc_Function      function;  /**< \brief The function pointer */
    OmapRpc_FuncSignature signature; /**< \brief The signature of the function */
} OmapRpc_FuncDeclaration;

typedef struct OmapRpc_Object *OmapRpc_Handle;
typedef Void (*OmapRpc_SrvDelNotifyFxn)(Void);

OmapRpc_Handle OmapRpc_createChannel(String channelName, UInt16 dstProc,
        UInt32 port, RcmServer_Params *rcmParams, MmType_FxnSigTab *fxnSigTab,
        OmapRpc_SrvDelNotifyFxn srvDelCBFunc);

Int OmapRpc_deleteChannel(OmapRpc_Handle handle);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

/*@}*/
#endif /* ti_srvmgr_OmapRpc__include */
