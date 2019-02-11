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
 *  @file       ti/xdais/dm/ividenc.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video encoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDENC   IVIDENC - XDM Video Encoder Interface
 *
 *  This is the XDM IVIDENC Video Encoder Interface.
 *
 *  @deprecated This XDM video encoder interface has been deprecated, and
 *              superceeded by newer IVIDENCx video encoder interfaces.
 */

#ifndef ti_xdais_dm_IVIDENC_
#define ti_xdais_dm_IVIDENC_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>

/*
 * By definition, this interface is 0.9 XDM.  Before including xdm.h,
 * define XDM_INCLUDE_DOT9_SUPPORT
 */
#ifndef XDM_INCLUDE_DOT9_SUPPORT
#define XDM_INCLUDE_DOT9_SUPPORT
#endif
#include "xdm.h"
#include "ivideo.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDENC */
/*@{*/

#define IVIDENC_CID      "ti.xdais.dm.IVIDENC"  /**< IVIDENC Class ID */

#define IVIDENC_ERUNTIME  XDM_ERUNTIME          /**< General runtime failure. */
#define IVIDENC_EOK       XDM_EOK               /**< @copydoc XDM_EOK */
#define IVIDENC_EFAIL     XDM_EFAIL             /**< @copydoc XDM_EFAIL */

/**
 *  @brief      This must be the first field of all IVIDENC
 *              instance objects.
 */
typedef struct IVIDENC_Obj {
    struct IVIDENC_Fxns *fxns;
} IVIDENC_Obj;


/**
 *  @brief      Opaque handle to an IVIDENC objects.
 */
typedef struct IVIDENC_Obj *IVIDENC_Handle;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDENC instance objects.
 *
 *  @remarks    The application should set the parameters to 0 to use
 *              the algorithm's default values.
 *
 *  @extensibleStruct
 */
typedef struct IVIDENC_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 encodingPreset;  /**< Encoding preset. */
    XDAS_Int32 rateControlPreset;/**< @copydoc IVIDEO_RateControlPreset
                                 *
                                 *   @sa IVIDEO_RateControlPreset
                                 */
    XDAS_Int32 maxHeight;       /**< Maximum height. */
    XDAS_Int32 maxWidth;        /**< Maximum width. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate * 1000. */
    XDAS_Int32 maxBitRate;      /**< Maximum bit rate, bits per second. */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 maxInterFrameInterval;/**< I to P frame distance. e.g. = 1 if
                                      *   no B frames, 2 to insert one B frame.
                                      */
    XDAS_Int32 inputChromaFormat;/**< Chroma format for the input buffer.
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDAS_Int32 inputContentType;/**< Video content type of the buffer being
                                 *   encoded.
                                 *
                                 *   @sa IVIDEO_ContentType
                                 */
} IVIDENC_Params;


/**
 *  @brief      This structure defines the codec parameters that can be
 *              modified after creation via control() calls.
 *
 *  @remarks    It is not necessary that given implementation support all
 *              dynamic parameters to be configurable at run time.  If a
 *              particular algorithm does not support run-time updates to
 *              a parameter that the application is attempting to change
 *              at runtime, it may indicate this as an error.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC_Fxns::control()
 */
typedef struct IVIDENC_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 inputHeight;     /**< Input frame height. */
    XDAS_Int32 inputWidth;      /**< Input frame width. */
    XDAS_Int32 refFrameRate;    /**< Reference or input frame rate * 1000. */
    XDAS_Int32 targetFrameRate; /**< Target frame rate * 1000. */
    XDAS_Int32 targetBitRate;   /**< Target bit rate in bits per second. */
    XDAS_Int32 intraFrameInterval;/**< I frame interval.  For example,
                                 *   30.
                                 */
    XDAS_Int32 generateHeader;  /**< @copydoc XDM_EncMode
                                 *
                                 *   @sa XDM_EncMode
                                 */
    XDAS_Int32 captureWidth;    /**< DEFAULT(0): use imagewidth as
                                 *   pitch else use given capture
                                 *   width for pitch provided it
                                 *   is greater than image width.
                                 */
    XDAS_Int32 forceIFrame;     /**< Force the current frame to be encoded
                                 *   as an I-frame. */
} IVIDENC_DynamicParams;

/**
 *  @brief      Defines the input arguments for all IVIDENC instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC_Fxns::process()
 */
typedef struct IVIDENC_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
} IVIDENC_InArgs;

/**
 *  @brief      Defines instance status parameters
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC_Fxns::control()
 */
typedef struct IVIDENC_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM_AlgBufInfo bufInfo;     /**< Input and output buffer information.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */
} IVIDENC_Status;


/**
 *  @brief      Defines the run time output arguments for all IVIDENC
 *              instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDENC_Fxns::process()
 */
typedef struct IVIDENC_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDAS_Int32 bytesGenerated;  /**< Bytes generated by the encode. */
    XDAS_Int32 encodedFrameType;/**< @copydoc IVIDEO_FrameType
                                 *
                                 *   @sa IVIDEO_FrameType
                                 */
    XDAS_Int32 inputFrameSkip;  /**< Frame Skip Mode.  See #IVIDEO_SkipMode. */
    IVIDEO_BufDesc reconBufs;   /**< Reconstruction Frames. */
} IVIDENC_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDENC module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDENC_Fxns::control()
 */
typedef  IALG_Cmd IVIDENC_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDENC objects.
 */
typedef struct IVIDENC_Fxns {
    IALG_Fxns   ialg;             /**< XDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video encoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in]  inBufs          Input buffer descriptors.
 *  @param[in,out] outBufs      Output buffer descriptors.  The algorithm
 *                              may modify the output buffer pointers.
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
 *              IVIDENC_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDENC_OutArgs structure.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The buffers in @c inBufs are
 *              owned by the calling application.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IVIDENC_OutArgs#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*process)(IVIDENC_Handle handle, XDM_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs,
        IVIDENC_OutArgs *outArgs);

/**
 *  @brief      Control behavior of an algorithm.
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
 *              IVIDENC_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDENC_Status structure.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c params.
 *              That is, the data pointed to by this parameter must be
 *              treated as read-only.
 *
 *  @retval     IALG_EOK        Success.
 *  @retval     IALG_EFAIL      Failure.  See IVIDENC_Status#extendedError
 *                              for more detailed further error conditions.
 */
    XDAS_Int32 (*control)(IVIDENC_Handle handle, IVIDENC_Cmd id,
        IVIDENC_DynamicParams *params, IVIDENC_Status *status);

} IVIDENC_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
