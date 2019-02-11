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
 *  @file       ti/xdais/dm/split/ividdec2.h
 *
 *  @brief      This header defines all types, constants, enums, and functions
 *              that are common across all split IVIDDEC2-based codecs.
 */
/**
 *  @addtogroup   ti_xdais_dm_split_IVIDDEC2 XDM IVIDDEC2-based Video Decoder Split Interface
 *
 *  This is the XDM split video decoder interface.
 */

#ifndef ti_xdais_dm_split_IVIDDEC2_
#define ti_xdais_dm_split_IVIDDEC2_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "../xdm.h"

#include "../ividdec2.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_split_IVIDDEC2 */
/*@{*/

/**
 *  @brief      This must be the first field of all IVIDDEC2FRONT
 *              instance objects.
 */
typedef struct IVIDDEC2FRONT_Obj {
    struct IVIDDEC2FRONT_Fxns *fxns;
} IVIDDEC2FRONT_Obj;


/**
 *  @brief      Opaque handle to an IVIDDEC2FRONT objects.
 */
typedef struct IVIDDEC2FRONT_Obj *IVIDDEC2FRONT_Handle;

/**
 *  @brief      This must be the first field of all IVIDDEC2BACK
 *              instance objects.
 */
typedef struct IVIDDEC2BACK_Obj {
    struct IVIDDEC2BACK_Fxns *fxns;
} IVIDDEC2BACK_Obj;


/**
 *  @brief      Opaque handle to an IVIDDEC2BACK objects.
 */
typedef struct IVIDDEC2BACK_Obj *IVIDDEC2BACK_Handle;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @remarks    All fields correspond to latest IVIDDEC2FRONT_Fxns::process()
 *              call on the particular instance of the decoder.
 *
 *  @sa         IVIDDEC2FRONT_Fxns::control()
 */
typedef struct IVIDDEC2FRONT_Status {
    XDM_ContextInfo contextInfo;/**< Context info.
                                 *
                                 *   @remarks   Only valid when the cmd issued
                                 *              to control() is
                                 *              XDM_GETCONTEXTINFO.
                                 */
    XDAS_Int32 nextPartRequiredFlag;  /**< Flag indicating whether the
                                 *   next part in the split codec must be
				 *   called or not.
				 *
				 *   @remarks   If the control() call returned
                                 *              IVIDDEC2_EOK, and this
                                 *              @c nextPartRequiredFlag
                                 *              field is XDAS_TRUE,
                                 *              the application must
                                 *              call the next part in
                                 *              the split codec.
                                 *
                                 *   @remarks   If the control() call returned
                                 *              failure (i.e.,
                                 *              something other than
                                 *              IVIDDEC2_EOK), the
                                 *              codec must set this
                                 *              field to XDAS_FALSE.
                                 *              Further information
                                 *              about the failure can
                                 *              be obtained via the
                                 *              @c partialExtendedError
                                 *              field.
				 */
    XDAS_Int32 partialExtendedError; /**< @extendedErrorField
                                 *
                                 *   @remarks   This field should be
                                 *              filled by the codec
                                 *              if the control() call
                                 *              does not return
                                 *              IVIDDEC2_EOK.  Otherwise,
                                 *              it is an undefined output
                                 *              field.
                                 */
    IVIDDEC2_Status fullStatus; /**< Complete status results.
                                 *
                                 *   @extensibleStruct
                                 *
                                 *   @remarks   The @c size field of this
                                 *              structure must be
                                 *              filled by the
                                 *              application before
                                 *              calling control().
                                 *              This is necessary even
                                 *              if the FRONT codec is
                                 *              unable to complete the
                                 *              request (e.g., the
                                 *              codec sets the
                                 *              @c nextPartRequiredFlag
                                 *              to XDAS_TRUE) and
                                 *              further parts of
                                 *              the codec must be
                                 *              called.  This @c size
                                 *              field indicates to the
                                 *              codec whether any
                                 *              codec-specific
                                 *              extensions are
                                 *              requested.
                                 *
                                 *   @remarks   The @c fullStatus.size
                                 *              field should only
                                 *              indicate the size of
                                 *              the [potentially
                                 *              extended]
                                 *              @c fullStatus
                                 *              structure.
                                 *
                                 *   @remarks   This field should be used if
                                 *              @c nextPartRequiredFlag is
                                 *              XDAS_FALSE.
                                 *
                                 *   @remarks   This struct, with the
                                 *              exception of the
                                 *              @c size field,
                                 *              will be populated by
                                 *              the codec.  If the
                                 *              control() call returns
                                 *              IVIDDEC2_EOK, the
                                 *              application must
                                 *              inspect the
                                 *              @c nextPartRequiredFlag
                                 *              field to determine
                                 *              whether it must
                                 *              call the next part
                                 *              or whether this
                                 *              @c fullStatus field
                                 *              contains the
                                 *              complete results
                                 *              of the control()
                                 *              call.
                                 *
                                 *   @remarks   The @c fullStatus.data
                                 *              field should not be
                                 *              used to provide
                                 *              buffers to split
                                 *              codecs.  In the same
                                 *              way the application
                                 *              provides data buffers
                                 *              to process() via an
                                 *              XDM_Context argument,
                                 *              control() does the
                                 *              same.  As a result,
                                 *              the
                                 *              @c fullStatus.data
                                 *              field is ignored
                                 *              and unused in this
                                 *              struct.
                                 *
                                 *   @remarks   If control() is called with
                                 *              the #XDM_GETVERSION
                                 *              command, the
                                 *              application must
                                 *              provide the buffer
                                 *              into which the codec
                                 *              will place its version
                                 *              string in the
                                 *              @c context->outBuffers[0]
                                 *              field.
                                 */
} IVIDDEC2FRONT_Status;


/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDDEC2FRONT instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC2FRONT_Fxns::process()
 */
typedef struct IVIDDEC2FRONT_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bytesConsumed;   /**< Number of bytes consumed during the
                                 *   process() call.
                                 */
} IVIDDEC2FRONT_OutArgs;


/**
 *  @brief      Defines all of the operations on IVIDDEC2FRONT objects.
 */
typedef struct IVIDDEC2FRONT_Fxns {
    IALG_Fxns ialg;               /**< XDAIS algorithm interface.
                                   *
                                   *   @sa IALG_Fxns
                                   */

/**
 *  @brief      Basic video decoding call
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[in,out] context      Context provided to, and managed by the
 *                              split codec.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @remarks    The application must call IVIDDEC2FRONT::control() with
 *              #XDM_GETCONTEXTINFO to obtain the minimum buffer sizes
 *              the codec requires.
 *
 *  @remarks    @c context includes input and output buffers, intermediate
 *              buffers, and other values used by the codec.  See
 *              #XDM_Context for more details.
 *
 *  @pre        @c context->numInBufs will indicate the total number of input
 *              buffers supplied for input frame, and conditionally, the
 *              encoders MB data buffer.
 *
 *  @pre        If IVIDDEC2_DynamicParams::mbDataFlag was set to #XDAS_FALSE
 *              in a previous control() call, the application only needs to
 *              provide buffers for reconstruction frames.
 *
 *  @pre        If IVIDDEC2_DynamicParams::mbDataFlag was set to #XDAS_TRUE
 *              in a previous control() call,
 *              @c context->outBufs[context->numOutBufs - 1] is a buffer
 *              descriptor into which the algorithm will write MB data
 *              for each macro block.  The size of the MB data buffer
 *              will vary based on the decoder type.  H.264 may
 *              generate N264 bytes per MB, while Mpeg2 may generate
 *              NMP2 bytes.  The exact size of the buffers should be
 *              obtained by calling the algorithm's control() method
 *              with XDM_GETBUFINFO.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDDEC2_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDDEC2FRONT_OutArgs structure.
 *
 *  @pre        @c context must not be NULL, and must point to a valid
 *              XDM_Context structure.
 *
 *  @pre        @c context->inBufs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c context->inBufs[0].bufSize bytes in length.
 *
 *  @pre        @c context->outBufs[0] must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c context->outBufs[0].bufSize bytes in length.
 *
 *  @pre        @c context->numInOutBufs must be zero (0).
 *
 *  @pre        The buffers in @c context->inBufs and @c context->outBufs are
 *              physically contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c context->inBufs, with the exception of
 *              @c context->inBufs[].accessMask.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The algorithm <b>must</b> modify the contents of
 *              @c context->inBufs[].accessMask and appropriately indicate the
 *              mode in which each of the buffers in @c context->inBufs were
 *              read.  For example, if the algorithm only read from
 *              @c context->inBufs[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c context->inBufs and @c context->outBufs are
 *              not owned by the calling application.
 *
 *  @post       The buffers in @c context->algContext and
 *              @c context->intermediateBufs[] are owned by the calling
 *              application, but must be provided - unmodified - to the
 *              next part in this split codec.
 *
 *  @retval     IVIDDEC2_EOK            @copydoc IVIDDEC2_EOK
 *  @retval     IVIDDEC2_EFAIL          @copydoc IVIDDEC2_EFAIL
 *                                      See IVIDDEC2_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC2_EUNSUPPORTED   @copydoc IVIDDEC2_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDDEC2FRONT_Handle handle, IVIDDEC2_InArgs *inArgs,
        XDM_Context *context, IVIDDEC2FRONT_OutArgs *outArgs);


/**
 *  @brief      Control behavior of an algorithm.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  id              Command id.  See #XDM_CmdId.
 *  @param[in]  params          Dynamic parameters.  This is a required
 *                              parameter.
 *  @param[in,out] context      Context provided to, and managed by the
 *                              split codec.
 *  @param[out] status          Output results.  This is a required parameter.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c params must not be NULL, and must point to a valid
 *              IVIDDEC2_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDDEC2FRONT_Status structure.
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
 *  @remark     @c context <i>may</i> be NULL.  The FRONT part of a codec
 *              <i>may</i> be capable of completely handling the control()
 *              command.  The codec indicates this  the application is sure the
 *              FRONT part of the codec can return and must point to a valid
 *              XDM_Context structure.
 *
 *
 *  @retval     IVIDDEC2_EOK            @copydoc IVIDDEC2_EOK
 *  @retval     IVIDDEC2_EFAIL          @copydoc IVIDDEC2_EFAIL
 *                                      See IVIDDEC2_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC2_EUNSUPPORTED   @copydoc IVIDDEC2_EUNSUPPORTED
 */
    XDAS_Int32 (*control)(IVIDDEC2FRONT_Handle handle, IVIDDEC2_Cmd id,
        IVIDDEC2_DynamicParams *params, XDM_Context *context,
        IVIDDEC2FRONT_Status *status);

} IVIDDEC2FRONT_Fxns;


/**
 *  @brief      Defines all of the operations on IVIDDEC2BACK objects.
 */
typedef struct IVIDDEC2BACK_Fxns {
    IALG_Fxns   ialg;             /**< XDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video decoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in,out] context      Context provided to, and managed by the
 *                              split codec.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c context must not be NULL, and must point to a valid
 *              XDM_Context structure.
 *
 *  @pre        @c context->numInOutBufs must be zero (0).
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDDEC2_OutArgs structure.
 *
 *  @post       The buffers in @c context are
 *              owned by the calling application.
 *
 *  @retval     IVIDDEC2_EOK            @copydoc IVIDDEC2_EOK
 *  @retval     IVIDDEC2_EFAIL          @copydoc IVIDDEC2_EFAIL
 *                                      See IVIDDEC2_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC2_EUNSUPPORTED   @copydoc IVIDDEC2_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDDEC2BACK_Handle handle, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs);


/**
 *  @brief      Control behavior of an algorithm.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  context         Codec context.  This is a required
 *                              parameter.
 *  @param[out] status          Output results.  This is a required parameter.
 *
 *  @pre        @c handle must be a valid algorithm instance handle.
 *
 *  @pre        @c context must not be NULL, and must point to a valid
 *              XDM_Context structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDDEC2_Status structure.
 *
 *  @pre        If a buffer is provided in the @c status->data field,
 *              it must be physically contiguous and owned by the calling
 *              application.
 *
 *  @post       If a buffer was provided in the @c status->data field,
 *              it is owned by the calling application.
 *
 *  @retval     IVIDDEC2_EOK            @copydoc IVIDDEC2_EOK
 *  @retval     IVIDDEC2_EFAIL          @copydoc IVIDDEC2_EFAIL
 *                                      See IVIDDEC2_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC2_EUNSUPPORTED   @copydoc IVIDDEC2_EUNSUPPORTED
 */
    XDAS_Int32 (*control)(IVIDDEC2BACK_Handle handle,
        XDM_Context *context, IVIDDEC2_Status *status);

} IVIDDEC2BACK_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
