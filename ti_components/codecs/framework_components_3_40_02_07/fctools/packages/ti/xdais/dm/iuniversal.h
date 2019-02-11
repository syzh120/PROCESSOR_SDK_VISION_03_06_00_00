/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
 *  @file       ti/xdais/dm/iuniversal.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the "universal" XDM
 *              algorithm.
 */
/**
 *  @defgroup   ti_xdais_dm_IUNIVERSAL   IUNIVERSAL - XDM Beta Universal Algorithm Interface
 *
 *  This is the XDM Beta Universal Algorithm Interface.
 */

#ifndef ti_xdais_dm_IUNIVERSAL_
#define ti_xdais_dm_IUNIVERSAL_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IUNIVERSAL */
/*@{*/

#define IUNIVERSAL_EOK      XDM_EOK              /**< @copydoc XDM_EOK */
#define IUNIVERSAL_EFAIL    XDM_EFAIL            /**< @copydoc XDM_EFAIL */
#define IUNIVERSAL_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/**
 *  @brief      This must be the first field of all IUNIVERSAL
 *              instance objects.
 */
typedef struct IUNIVERSAL_Obj {
    struct IUNIVERSAL_Fxns *fxns;
} IUNIVERSAL_Obj;


/**
 *  @brief      Opaque handle to an IUNIVERSAL objects.
 */
typedef struct IUNIVERSAL_Obj  *IUNIVERSAL_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IUNIVERSAL instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IUNIVERSAL_Params {
    XDAS_Int32 size;            /**< @sizeField */
} IUNIVERSAL_Params;


/**
 *  @brief      This structure defines the codec parameters that can be
 *              modified after creation via control() calls.
 *
 *  @remarks    It is not necessary that a given implementation support all
 *              dynamic parameters to be configurable at run time.  If a
 *              particular algorithm does not support run-time updates to
 *              a parameter that the application is attempting to change
 *              at runtime, it may indicate this as an error.
 *
 *  @extensibleStruct
 *
 *  @sa         IUNIVERSAL_Fxns::control()
 */
typedef struct IUNIVERSAL_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
} IUNIVERSAL_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IUNIVERSAL instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IUNIVERSAL_Fxns::process()
 */
typedef struct IUNIVERSAL_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
} IUNIVERSAL_InArgs;


/**
 *  @brief      Defines instance status parameters (read-only).
 *
 *  @extensibleStruct
 *
 *  @sa         IUNIVERSAL_Fxns::control()
 */
typedef struct IUNIVERSAL_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM1_BufDesc data;          /**< Buffer descriptor for data passing.
                                 *
                                 *   @remarks   These buffers can be used as
                                 *              either input, output, or
                                 *              input/output buffers,
                                 *              depending on the command.
                                 *
                                 *   @remarks   The buffers will be provided
                                 *              by the application, and
                                 *              returned to the application
                                 *              upon return of the control()
                                 *              call.  The algorithm must
                                 *              not retain a pointer to this
                                 *              data.
                                 *
                                 *   @sa    #XDM_GETVERSION
                                 */
} IUNIVERSAL_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IUNIVERSAL instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IUNIVERSAL_Fxns::process()
 */
typedef struct IUNIVERSAL_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
} IUNIVERSAL_OutArgs;


/**
 *  @brief      Defines the control commands for the IUNIVERSAL module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IUNIVERSAL_Fxns::control()
 */
typedef  IALG_Cmd IUNIVERSAL_Cmd;


/**
 *  @brief      Defines all of the operations on IUNIVERSAL objects.
 */
typedef struct IUNIVERSAL_Fxns{
    IALG_Fxns   ialg;             /**< XDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic audio decoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in,out] inBufs       Input buffer descriptors.
 *  @param[in,out] outBufs      Output buffer descriptors.
 *  @param[in,out] inOutBufs    Input/Output buffer descriptors.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IUNIVERSAL_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IUNIVERSAL_OutArgs structure.
 *
 *  @pre        @c inBufs must either be NULL or point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c outBufs must either be NULL or point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c inOutBufs must either be NULL or point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        The buffers in @c inBufs, @c outBufs and @c inOutBufs are
 *              physically contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c inBufs, with the exception of @c inBufs.descs[].accessMask.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The algorithm <b>must</b> appropriately set/clear the
 *              @c XDM1_BufDesc::descs[].accessMask field in @c inBufs,
 *              @c outBufs, and @c inOutBufs.
 *              For example, if the algorithm only read from
 *              @c inBufs.descs[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c inBufs, @c outBufs, and @c inOutBufs are
 *              owned by the calling application.
 *
 *  @retval     IUNIVERSAL_EOK          @copydoc IUNIVERSAL_EOK
 *  @retval     IUNIVERSAL_EFAIL        @copydoc IUNIVERSAL_EFAIL
 *                                      See IUNIVERSAL_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IUNIVERSAL_EUNSUPPORTED @copydoc IUNIVERSAL_EUNSUPPORTED
 */
    XDAS_Int32   (*process)(IUNIVERSAL_Handle handle, XDM1_BufDesc *inBufs,
            XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs,
            IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs);


/**
 *  @brief      Control behaviour of an algorithm.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  id              Command id.  See #XDM_CmdId.
 *  @param[in]  params          Dynamic parameters.  This is a required
 *                              parameter.
 *  @param[out] status          Output results.  This is a required parameter.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c params must not be NULL, and must point to a valid
 *              IUNIVERSAL_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IUNIVERSAL_Status structure.
 *
 *  @pre        If a buffer is provided in the @c status->data field,
 *              it must be physically contiguous and owned by the calling
 *              application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @post       If a buffer was provided in the @c status->data field,
 *              it is owned by the calling application.
 *
 *  @retval     IUNIVERSAL_EOK          @copydoc IUNIVERSAL_EOK
 *  @retval     IUNIVERSAL_EFAIL        @copydoc IUNIVERSAL_EFAIL
 *                                      See IUNIVERSAL_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IUNIVERSAL_EUNSUPPORTED @copydoc IUNIVERSAL_EUNSUPPORTED
 */
    XDAS_Int32   (*control)(IUNIVERSAL_Handle handle, IUNIVERSAL_Cmd id,
        IUNIVERSAL_DynamicParams *params, IUNIVERSAL_Status *status);

} IUNIVERSAL_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
