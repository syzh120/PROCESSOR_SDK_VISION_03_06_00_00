/*
 * Copyright (c) 2012 - 2013, Texas Instruments Incorporated
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
 *
 */
/**
 *  @file       ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h
 *
 *  @brief      IRES PROTOCOL HDVICP2 Interface Definitions -
 *              Allows algorithms to request and receive handles representing
 *              the HDVICP2 resource.
 */

/**
 *  @addtogroup ti_sdo_fc_ires_hdvicp_IRES_HDVICP2 IRES HDVICP2 Protocol
 *
 *              Allows algorithms to request and receive handles representing
 *              HDVICP2 resources.
 */

#ifndef ti_sdo_fc_ires_hdvicp_IRES_HDVICP2_
#define ti_sdo_fc_ires_hdvicp_IRES_HDVICP2_

/** @ingroup    ti_sdo_fc_ires_hdvicp_IRES_HDVICP2 */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/xdas.h>
#include <ti/xdais/ires_common.h>
#include <ti/xdais/ires.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_HDVICP2_PROTOCOLNAME       "ti.sdo.fc.ires.hdvicp.hdvicp2"

/**
 * @brief       HDVICP2 module name
 *
 * @remarks     This name can be passed to Diags_setMask() to enable/disable
 *              logging for this module.  For example,
 *                  Diags_setMask(HDVICP2_MODNAME"+EX1234567");
 *              enables all Log statements in this module.
 *
 * @remarks     Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define HDVICP2_MODNAME  "ti.sdo.fc.ires.hdvicp2"


/**
 * @brief Used to specify the resource required in the protocol args,
 *        resource manager will return
 *        an HDVICP2 resource that is available to the scratch group.
 */
#define IRES_HDVICP2_ID_ANY             -2

/**
 * @brief Used to specify the resource required for protocol args, late acquire
 *        implies that no resource is to be returned right now, resource will be
 *        acquired later in the process call, using the acquire fxn returned
 *        via the IRES_HDVICP2_Handle.
 */
#define IRES_HDVICP2_ID_LATE_ACQUIRE    -1

/**
 * @brief       Invalid address
 *
 * @remarks     Indicates the address returned in the IRES_HDVICP2_Handle
 *              is not yet valid, and should not be used.
 */
#define IRES_HDVICP2_INVALID_ADDR 0xFFFFFFFF

/**
 * @brief       Wait forever (never timeout)
 *
 * @remarks     Used to indicate to IRES_HDVICP2_Obj::wait() that the call
 *              should never timeout.
 */
#define IRES_HDVICP2_TIMEOUTFOREVER ((UInt)(-1))

/**
 *  @brief      Unknown late acquire argument.
 *
 *  @remarks    This definition should be used when a particular algorithm
 *              doesn't have an application-provided late acquire argument.
 *              The codec should supply IRES_HDVICP2_UNKNOWNLATEACQUIREARG
 *              as the argument to acquire() in this case.
 *
 *  @sa XDM_CmdId::XDM_SETLATEACQUIREARG
 */
#define IRES_HDVICP2_UNKNOWNLATEACQUIREARG (-1)

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision IRES_HDVICP2_PROTOCOLREVISION = {1, 0, 0};

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_HDVICP2_Obj *IRES_HDVICP2_Handle;


/**
 *  @brief      Timeout value to be used by implementation of
 *              IRES_HDVICP2_Handle:wait function
 */
extern unsigned int ti_sdo_fc_ires_hdvicp_HDVICP2_timeoutVal;

/**
 *  @brief
 */
typedef IRES_YieldArgs (* ti_sdo_fc_ires_hdvicp_HDVICP2_GetYieldArgsFxn)
        (Int scratchId);

/**
 *  @brief
 */
typedef Void (* ti_sdo_fc_ires_hdvicp_HDVICP2_YieldFxn)
        (IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt,
        IRES_YieldArgs args);



/**
 *  @brief      HDVICP2 Protocol Arguments definition.
 */
typedef struct IRES_HDVICP2_ProtocolArgs {

    IRES_ProtocolArgs base;     /**< Base protocol Args */
    XDAS_Int32 id;              /**< HDVICP2 resource being requested.
                                 *
                                 *   @remarks   Could be 0, 1, 2,
                                 *              IRES_HDVICP2_ID_ANY or
                                 *              IRES_HDVICP2_ID_LATE_ACQUIRE.
                                 */
} IRES_HDVICP2_ProtocolArgs;

/**
 *  @brief          Callback function signature, used by the IRES_HDVICP2_
 *                  Handle's configure function
 */
typedef void (*IRES_HDVICP2_CallbackFxn)(IALG_Handle handle, Void * args);

/**
 *  @brief          Describes the status/history of the HDVICP2 unit that is
 *                  returned by the acquire call. This information can be
 *                  used by the codec to avoid reloading the data memory or
 *                  the program memory in the HDVICP2.
 *
 *  @enumWarning
 */
typedef enum IRES_HDVICP2_Status {
    SAMECODEC = 0,          /**< Same codec was granted this unit, last time */
    SAMECODECTYPE = 1,      /**< Different codec, but of the same codec class
                                was granted this unit last time */
    DIFFERENTCODEC = 2      /**< Completely different codec ran last time */
} IRES_HDVICP2_Status;


/**
 *  @brief          IRES_HDVICP2_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource.
 */
typedef struct  IRES_HDVICP2_Obj {

    IRES_Obj ires;                     /**< Base IRES_Obj struct */
    Void *info;                        /**< Reserved for future use */
    XDAS_Int32 id;                     /**< HDVICP2 id granted
                                        *
                                        *  @remark  Could be 0, 1, 2, or
                                        *           LATE_ACQUIRE
                                        */
    XDAS_Void *registerBaseAddress;    /**< Register space base address of the
                                        *   HDVICP2 being granted
                                        */
    XDAS_Void *memoryBaseAddress;      /**< Memory space base address of the
                                        *   HDVICP2 being granted
                                        */
    XDAS_Void *resetControlAddress;    /**< HDVICP reset controller address
                                        *
                                        *   @remarks    bit 0 -> ICONT1 reset,
                                        *               bit 1 -> ICONT2 reset
                                        */

/**
 *  @brief          Acquire the HDVICP2 resource.
 *
 *  @remarks        This call acquires the HDVICP resource which the alg may
 *                  (or may not) have specifically requested.
 *
 *  @remarks        The returned @c hdvicp2Status indicates the status of
 *                  the particular HDVICP2 unit that is returned.
 *                  @sa IRES_HDVICP2_Status
 *
 *  @remarks        The @c configurationId argument is a codec specified
 *                  parameter that is both an input and output parameter.  It
 *                  specifies the mode in which this particular HDVICP2 was
 *                  used last time, and the mode in which it will be
 *                  used this time.
 *
 *  @remarks        This API takes a @c yieldContext as argument, as it may
 *                  yield the processor to higher priority codecs in the
 *                  system.
 *
 *  @remarks        @c lateAcquireId is an optionally framework supplied
 *                  parameter (sometimes provided via an XDM control() call
 *                  setting the XDM_SETLATEACQUIREARG. If not supplied, the
 *                  codec should pass the value
 *                  #IRES_HDVICP2_UNKNOWNLATEACQUIREARG.
 *
 *  @sa         IRES_HDVICP2_UNKNOWNLATEACQUIREARG
 */
    XDAS_Void (*acquire)(IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj * hdvicpHandle,
            IRES_YieldContext * yieldCtxt, XDAS_UInt32 * hdvicp2Status,
            XDAS_UInt32 *configurationId, XDAS_Int32 lateAcquireArg);

/**
 *  @brief      Release the HDVICP2 resource.
 *
 *  @remarks    This makes the resource available for use by other algorithms.
 */
    XDAS_Void (*release)(IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj * hdvicpHandle);

/**
 *  @brief      Reacquire the HDVICP2 resource recent released.
 *
 *  @returns    XDAS_TRUE       The resource was not yet acquired by another
 *                              algorithm, and the resource handle is still
 *                              valid.
 *  @returns    XDAS_FALSE      The resource is no longer available and has been
 *                              deactivated.
 */
    XDAS_UInt32 (*reacquireIfOwner)(IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj * hdvicpHandle);

/**
 *  @brief      Register a callback function with a HDVICP2 instance.
 *
 *  @remarks    The callback is invoked when an interrupt fires after
 *              processing data.
 *
 *  @remarks    It is the algorithm's responsibility to configure the HDVICP2
 *              to process data and fire the interrupt when done.
 */
    XDAS_Void (*configure)(IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj * hdvicpHandle,
            IRES_HDVICP2_CallbackFxn cbFunctionPtr, XDAS_Void * cbArgs);

/**
 *  @brief      Wait until the HDVICP2 is done processing and then return.
 *
 *  @remarks    This is a blocking call, unless a positive timeout value
 *              is configured, inwhich case the call returns after timeout.
 *
 *  @remarks    This function is passed a yieldContext, and will relinquish
 *              the processor while it waits for the HDVICP2 to finish the
 *              processing and return from wait.
 *
 *  @returns    XDAS_TRUE       Success
 *  @returns    XDAS_FALSE      Failure/Timeout
 */
    XDAS_UInt32 (*wait)(IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj *hdvicpHandle,
            IRES_YieldContext * yieldCtxt);

/**
 *  @brief      Processing has completed.
 *
 *  @remarks    This is called from within the interrupt handler function when
 *              processing completes, and is used to unblock the wait() API.
 *
 *  @remarks    Typically, this is called from within the algortihm's callback
 *              function (see acquire() call).
 */
    XDAS_Void (*done) (IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj *hdvicpHandle);
/**
 *  @brief      Reset the HDVICP2.
 *
 *  @remarks    This can be called by the algorithm to "reset" the HDVICP2, and
 *              is usually called when an acquired HDVICP2 is "dirty", i.e, it
 *              requires both program/data reload.
 *
 *  @remarks    It works off a configured maximum reset cycle delay.
 *
 *  @returns    XDAS_TRUE       Success
 *  @returns    XDAS_FALSE      Failure
 */
    XDAS_UInt32 (*reset)(IALG_Handle algHandle,
            struct IRES_HDVICP2_Obj *hdvicpHandle);

} IRES_HDVICP2_Obj;


/**
 * @brief           HDVICP2 Register Layout
 */
typedef struct IRES_HDVICP2_RegisterLayer {

    int size;
    /* TBD */
} IRES_HDVICP2_RegisterLayer;

/**
 * @brief       Static Resource Properties
 */
typedef struct IRES_HDVICP2_Properties {

    int size;
    IRES_HDVICP2_RegisterLayer *globalRegs;      /* Register layer of HDVICP2 */
} IRES_HDVICP2_Properties;

typedef IRES_Status (*ti_sdo_fc_ires_hdvicp_HDVICP2_GetHdvicp2Fxn)
        (XDAS_Int32 *Id, IALG_Handle alg, IRES_HDVICP2_Handle handle);

typedef IRES_Status (*ti_sdo_fc_ires_hdvicp_HDVICP2_FreeHdvicp2Fxn)
       (XDAS_Int32 Id, IALG_Handle alg, IRES_HDVICP2_Handle handle);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif
