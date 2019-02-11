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
 *  @file       ti/xdais/dm/ividdec1.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the video decoder
 *              algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IVIDDEC1   IVIDDEC1 - XDM Video Decoder Interface
 *
 *  This is the XDM IVIDDEC1 Video Decoder Interface.
 *
 *  @deprecated This XDM video decoder interface has been deprecated, and
 *              superceeded by newer IVIDDECx video decoder interfaces.
 */

#ifndef ti_xdais_dm_IVIDDEC1_
#define ti_xdais_dm_IVIDDEC1_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>
#include "xdm.h"
#include "ivideo.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IVIDDEC1 */
/*@{*/

#define IVIDDEC1_EOK       XDM_EOK             /**< @copydoc XDM_EOK */
#define IVIDDEC1_EFAIL     XDM_EFAIL           /**< @copydoc XDM_EFAIL */
#define IVIDDEC1_EUNSUPPORTED XDM_EUNSUPPORTED /**< @copydoc XDM_EUNSUPPORTED */

/**
 *  @brief      This must be the first field of all IVIDDEC1
 *              instance objects.
 */
typedef struct IVIDDEC1_Obj {
    struct IVIDDEC1_Fxns *fxns;
} IVIDDEC1_Obj;


/**
 *  @brief      Opaque handle to an IVIDDEC1 objects.
 */
typedef struct IVIDDEC1_Obj  *IVIDDEC1_Handle;


/**
 *  @brief      Video decoder output frame order.
 *
 *  @enumWarning
 *
 *  @sa IVIDDEC1_DynamicParams::frameOrder
 */
typedef enum {
    IVIDDEC_DISPLAY_ORDER = 0,  /**< The decoder provides decoded output in
                                 *   in the actual order of displaying the
                                 *   output buffer.  The codec assumes the
                                 *   responsibility of reordering the frames.
                                 *
                                 *   @remarks   The output buffer will be
                                 *              delayed by one frame,
                                 *              regardless of whether the frame
                                 *              contains I/P or I/P/B frames.
                                 *
                                 *   @remarks   This is the default mode.
                                 *
                                 *   @remarks   This mode is required to be
                                 *              supported by all video decoder
                                 *              codecs.
                                 */
    IVIDDEC_DECODE_ORDER = 1,   /**< The decoder provides decoded output in the
                                 *   the order of decoding.  There will be no
                                 *   delay in the output buffers.
                                 *
                                 *   @remarks   It is the application's
                                 *              responsibility to handle the
                                 *              frame re-ordering.
                                 *
                                 *   @remarks   This mode is optional.  If it
                                 *              is not supported by the
                                 *              decoder, IVIDDEC_EUNSUPPORTED
                                 *              will be returned.
                                 */

    /** Default setting. */
    IVIDDEC_FRAMEORDER_DEFAULT = IVIDDEC_DISPLAY_ORDER
} IVIDDEC1_FrameOrder;


/**
 *  @brief      Defines the creation time parameters for
 *              all IVIDDEC1 instance objects.
 *
 *  @extensibleStruct
 */
typedef struct IVIDDEC1_Params {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 maxHeight;       /**< Maximum video height in pixels. */
    XDAS_Int32 maxWidth;        /**< Maximum video width in pixels. */
    XDAS_Int32 maxFrameRate;    /**< Maximum frame rate in fps * 1000.
                                 *   For example, if max frame rate is 30
                                 *   frames per second, set this field
                                 *   to 30000.
                                 */
    XDAS_Int32 maxBitRate;      /**< Maximum bit rate, bits per second.
                                 *   For example, if bit rate is 10 Mbps, set
                                 *   this field to 10000000
                                 */
    XDAS_Int32 dataEndianness;  /**< Endianness of output data.
                                 *
                                 *   @sa    XDM_DataFormat
                                 */
    XDAS_Int32 forceChromaFormat;/**< @copydoc XDM_ChromaFormat
                                 *
                                 *   @sa    XDM_ChromaFormat
                                 */
} IVIDDEC1_Params;


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
 *  @sa         IVIDDEC1_Fxns::control()
 */
typedef struct IVIDDEC1_DynamicParams {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 decodeHeader;    /**< @copydoc XDM_DecMode
                                 *
                                 *   @sa XDM_DecMode
                                 */
    XDAS_Int32 displayWidth;    /**< Pitch.  If set to zero, use the decoded
                                 *   image width.  Else, use given display
                                 *   width in pixels.
                                 */
    XDAS_Int32 frameSkipMode;   /**< @copydoc IVIDEO_FrameSkip
                                 *
                                 *   @sa IVIDEO_FrameSkip
                                 */
    XDAS_Int32 frameOrder;      /**< @copydoc IVIDDEC1_FrameOrder
                                 *
                                 *   @sa IVIDDEC1_FrameOrder
                                 */
    XDAS_Int32 newFrameFlag;    /**< Flag to indicate that the algorithm should
                                 *   start a new frame.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *   @remarks   This is useful for error
                                 *              recovery, for example when the
                                 *              end of frame cannot be detected
                                 *              by the codec but is known to the
                                 *              application.
                                 */
    XDAS_Int32 mbDataFlag;      /**< Flag to indicate that the algorithm should
                                 *   generate MB Data in addition to decoding
                                 *   the data.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 *
                                 *   @sa IVIDDEC1_OutArgs::mbDataBuf
                                 */
} IVIDDEC1_DynamicParams;


/**
 *  @brief      Defines the input arguments for all IVIDDEC1 instance
 *              process function.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC1_Fxns::process()
 */
typedef struct IVIDDEC1_InArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 numBytes;        /**< Size of input data in bytes, provided
                                 *   to the algorithm for decoding.
                                 */
    XDAS_Int32 inputID;         /**< The decoder will attach
                                 *   this ID with the corresponding output
                                 *   frames.
                                 *
                                 *   @remarks   This is useful when frames
                                 *   require re-ordering (e.g. B frames).
                                 *
                                 *   @remarks   When there is no re-ordering,
                                 *   IVIDDEC1_OutArgs#outputID will be same
                                 *   as this inputID field.
                                 *
                                 *   @remarks   Zero (0) is not a supported
                                 *              inputID.  This value is
                                 *              reserved for cases when there
                                 *              is no output buffer provided in
                                 *              IVIDDEC1_OutArgs::displayBufs.
                                 *
                                 *   @sa IVIDDEC1_OutArgs::outputID.
                                 */
} IVIDDEC1_InArgs;


/**
 *  @brief      Defines instance status parameters.
 *
 *  @extensibleStruct
 *
 *  @remarks    All fields correspond to latest IVIDDEC1_Fxns::process() call
 *              on the particular instance of the decoder.
 *
 *  @sa         IVIDDEC1_Fxns::control()
 */
typedef struct IVIDDEC1_Status {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 extendedError;   /**< @extendedErrorField */
    XDM1_SingleBufDesc data;    /**< Buffer descriptor for data passing.
                                 *
                                 *   @remarks   If this field is not used,
                                 *              the application <b>must</b>
                                 *              set @c data.buf to NULL.
                                 *
                                 *   @remarks   This buffer can be used as
                                 *              either input or output,
                                 *              depending on the command.
                                 *
                                 *   @remarks   The buffer will be provided
                                 *              by the application, and
                                 *              returned to the application
                                 *              upon return of the
                                 *              IVIDDEC1_Fxns.control()
                                 *              call.  The algorithm must
                                 *              not retain a pointer to this
                                 *              data.
                                 *
                                 *   @sa    #XDM_GETVERSION
                                 */
    XDAS_Int32 outputHeight;    /**< Output height in pixels. */
    XDAS_Int32 outputWidth;     /**< Output width in pixels. */
    XDAS_Int32 frameRate;       /**< Average frame rate in fps * 1000.
                                 *   For example, if average frame rate is 30
                                 *   frames per second, this field should be
                                 *   30000.
                                 */
    XDAS_Int32 bitRate;         /**< Average bit rate, in bits per second. */
    XDAS_Int32 contentType;     /**< @copydoc IVIDEO_ContentType
                                 *
                                 *   @sa IVIDEO_ContentType
                                 */
    XDAS_Int32 outputChromaFormat; /**< @copydoc XDM_ChromaFormat
                                 *
                                 *   @sa XDM_ChromaFormat
                                 */
    XDM_AlgBufInfo bufInfo;     /**< Input and output buffer information.
                                 *
                                 *   @sa    XDM_AlgBufInfo
                                 */
} IVIDDEC1_Status;


#define IVIDDEC1_FREE_BUFF_SIZE 16 /**< Maximum buffer that can be freed up in a
                                 *   single process call
                                 */


/**
 *  @brief      Defines the run time output arguments for
 *              all IVIDDEC1 instance objects.
 *
 *  @extensibleStruct
 *
 *  @sa         IVIDDEC1_Fxns::process()
 */
typedef struct IVIDDEC1_OutArgs {
    XDAS_Int32 size;            /**< @sizeField */
    XDAS_Int32 bytesConsumed;   /**< Number of bytes consumed during the
                                 *   process() call.
                                 */
    XDAS_Int32 outputID[XDM_MAX_IO_BUFFERS]; /**< Output ID corresponding
                                 *   to displayBufs[].
                                 *
                                 *   @remarks   A value of zero (0) indicates
                                 *              an invalid ID.  The first zero
                                 *              entry in array will indicate
                                 *              end of valid outputIDs within
                                 *              the array.  Hence the
                                 *              application can stop reading the
                                 *              array when it encounters the
                                 *              first zero entry.
                                 *
                                 *   @sa IVIDDEC1_OutArgs#displayBufs
                                 *   @sa IVIDDEC1_InArgs#inputID
                                 */
    IVIDEO1_BufDesc decodedBufs; /**< The decoder fills this structure with
                                 *   buffer pointers to the decoded frame.
                                 *   Related information fields for the
                                 *   decoded frame are also populated.
                                 *
                                 *   When frame decoding is not complete, as
                                 *   indicated by @c outBufsInUseFlag,
                                 *   the frame data in this structure will be
                                 *   incomplete.  However, the algorithm will
                                 *   provide incomplete decoded frame data
                                 *   in case application may choose to use
                                 *   it for error recovery purposes.
                                 *
                                 *   @sa IVIDDEC1_OutArgs#outBufsInUseFlag
                                 */
    IVIDEO1_BufDesc displayBufs[XDM_MAX_IO_BUFFERS]; /**< Array
                                 *   containing display frames
                                 *   corresponding to valid ID entries
                                 *   in the @c outputID[] array.
                                 *
                                 *   @remarks   Entries in the array
                                 *              corresponding to invalid
                                 *              ID values (zero) in
                                 *              @c outputID[] will set
                                 *              zero value for the following
                                 *              fields in the IVIDEO1_BufDesc
                                 *              structure:  @c numBufs,
                                 *              @c frameWidth, @c frameHeight,
                                 *              and @c framePitch.
                                 *
                                 *   @remarks   Implied by the previous remark,
                                 *              as this array corresponds to
                                 *              buffer IDs indicated by
                                 *              @c outputID[], elements of
                                 *              this array are undefined if
                                 *              the corresponding @c outputID[]
                                 *              element is zero (0).
                                 */
    XDAS_Int32 outputMbDataID;  /**< Output ID corresponding with the MB Data
                                 *
                                 *   @remarks   This will be set to zero when
                                 *              there is no MB Data Buffer
                                 */
    XDM1_SingleBufDesc mbDataBuf; /**< The decoder populates the last buffer
                                 *   among the buffers supplied within
                                 *   outBufs->bufs[] with the decoded MB data
                                 *   generated by the ECD module. The pointer
                                 *   buffer along with the buffer size is
                                 *   output via this buffer descriptor.
                                 */
    XDAS_Int32 freeBufID[IVIDDEC1_FREE_BUFF_SIZE]; /**< This is an
                                 *   array of inputID's corresponding to the
                                 *   buffers that have been unlocked in the
                                 *   current process call.
                                 *
                                 *   @remarks   Buffers returned to the
                                 *              application for display (via
                                 *              IVIDDEC1_OutArgs#displayBufs)
                                 *              continue to be owned by the
                                 *              algorithm until they are
                                 *              released - indicated by
                                 *              the ID being returned in this
                                 *              @c freeBuf array.
                                 *
                                 *   @remarks   The buffers released by the
                                 *              algorithm are indicated by
                                 *              their non-zero ID (previously
                                 *              provided via
                                 *              IVIDDEC1_InArgs#inputID).
                                 *
                                 *   @remarks   A value of zero (0) indicates
                                 *              an invalid ID.  The first zero
                                 *              entry in array will indicate
                                 *              end of valid freeBufIDs within
                                 *              the array.  Hence the
                                 *              application can stop searching
                                 *              the array when it encounters the
                                 *              first zero entry.
                                 *
                                 *   @remarks   If no buffer was unlocked in
                                 *              the process call,
                                 *              @c freeBufID[0] will
                                 *              have a value of zero.
                                 *
                                 *   @sa IVIDDEC1_InArgs#inputID
                                 *   @sa IVIDDEC1_OutArgs#displayBufs
                                 */
    XDAS_Int32 outBufsInUseFlag; /**< Flag to indicate that the @c outBufs
                                 *   provided with the process() call are in
                                 *   use.  No outBufs are required to be
                                 *   supplied with the next process() call.
                                 *
                                 *   @remarks   Valid values are XDAS_TRUE
                                 *              and XDAS_FALSE.
                                 */

} IVIDDEC1_OutArgs;


/**
 *  @brief      Defines the control commands for the IVIDDEC1 module.
 *
 *  @remarks    This ID can be extended in IMOD interface for
 *              additional controls.
 *
 *  @sa         XDM_CmdId
 *
 *  @sa         IVIDDEC1_Fxns::control()
 */
typedef  IALG_Cmd IVIDDEC1_Cmd;


/**
 *  @brief      Defines all of the operations on IVIDDEC1 objects.
 */
typedef struct IVIDDEC1_Fxns {
    IALG_Fxns   ialg;             /**< XDAIS algorithm interface.
                                   *
                                   *   @sa      IALG_Fxns
                                   */

/**
 *  @brief      Basic video decoding call.
 *
 *  @param[in]  handle          Handle to an algorithm instance.
 *  @param[in,out] inBufs       Input buffer descriptors.
 *  @param[in,out] outBufs      Output buffer descriptors.  The algorithm
 *                              may modify the output buffer pointers.
 *  @param[in]  inArgs          Input arguments.  This is a required
 *                              parameter.
 *  @param[out] outArgs         Ouput results.  This is a required parameter.
 *
 *  @remarks    process() is a blocking call.  When process() returns, the
 *              algorithm's processing is complete.
 *
 *  @pre        @c inBufs->numBufs will indicate the total number of input
 *              buffers supplied for input frame, and conditionally, the
 *              encoders MB data buffer.
 *
 *  @pre        If IVIDDEC1_DynamicParams::mbDataFlag was set to #XDAS_FALSE
 *              in a previous control() call, the application only needs to
 *              provide buffers for reconstruction frames.
 *
 *  @pre        If IVIDDEC1_DynamicParams::mbDataFlag was set to #XDAS_TRUE
 *              in a previous control() call,
 *              @c outBufs->bufs[outBufs->numBufs - 1] is a buffer descriptor
 *              into which the algorithm will write MB data for each macro
 *              block.  The size of the MB data buffer will vary based on the
 *              decoder type.  H.264 may generate N264 bytes per MB, while
 *              Mpeg2 may generate NMP2 bytes.  The exact size of the buffers
 *              should be obtained by calling the algorithm's control() method
 *              with XDM_GETBUFINFO.
 *
 *  @pre        @c inArgs must not be NULL, and must point to a valid
 *              IVIDDEC1_InArgs structure.
 *
 *  @pre        @c outArgs must not be NULL, and must point to a valid
 *              IVIDDEC1_OutArgs structure.
 *
 *  @pre        @c inBufs must not be NULL, and must point to a valid
 *              XDM1_BufDesc structure.
 *
 *  @pre        @c inBufs->descs[0].buf must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c inBufs->descs[0].bufSize bytes in length.
 *
 *  @pre        @c outBufs must not be NULL, and must point to a valid
 *              XDM_BufDesc structure.
 *
 *  @pre        @c outBufs->buf[0] must not be NULL, and must point to
 *              a valid buffer of data that is at least
 *              @c outBufs->bufSizes[0] bytes in length.
 *
 *  @pre        The buffers in @c inBufs and @c outBufs are physically
 *              contiguous and owned by the calling application.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of @c inArgs.
 *
 *  @post       The algorithm <b>must not</b> modify the contents of
 *              @c inBufs, with the exception of @c inBufs.bufDesc[].accessMask.
 *              That is, the data and buffers pointed to by these parameters
 *              must be treated as read-only.
 *
 *  @post       The algorithm <b>must</b> modify the contents of
 *              @c inBufs->descs[].accessMask and appropriately indicate the
 *              mode in which each of the buffers in @c inBufs were read.
 *              For example, if the algorithm only read from
 *              @c inBufs.descs[0].buf using the algorithm processor, it
 *              could utilize #XDM_SETACCESSMODE_READ to update the appropriate
 *              @c accessMask fields.
 *              The application <i>may</i> utilize these
 *              returned values to appropriately manage cache.
 *
 *  @post       The buffers in @c inBufs are
 *              owned by the calling application.
 *
 *  @retval     IVIDDEC1_EOK            @copydoc IVIDDEC1_EOK
 *  @retval     IVIDDEC1_EFAIL          @copydoc IVIDDEC1_EFAIL
 *                                      See IVIDDEC1_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC1_EUNSUPPORTED   @copydoc IVIDDEC1_EUNSUPPORTED
 */
    XDAS_Int32 (*process)(IVIDDEC1_Handle handle, XDM1_BufDesc *inBufs,
        XDM_BufDesc *outBufs, IVIDDEC1_InArgs *inArgs,
        IVIDDEC1_OutArgs *outArgs);


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
 *              IVIDDEC1_DynamicParams structure.
 *
 *  @pre        @c status must not be NULL, and must point to a valid
 *              IVIDDEC1_Status structure.
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
 *  @retval     IVIDDEC1_EOK            @copydoc IVIDDEC1_EOK
 *  @retval     IVIDDEC1_EFAIL          @copydoc IVIDDEC1_EFAIL
 *                                      See IVIDDEC1_Status#extendedError
 *                                      for more detailed further error
 *                                      conditions.
 *  @retval     IVIDDEC1_EUNSUPPORTED   @copydoc IVIDDEC1_EUNSUPPORTED
 */
    XDAS_Int32 (*control)(IVIDDEC1_Handle handle, IVIDDEC1_Cmd id,
        IVIDDEC1_DynamicParams *params, IVIDDEC1_Status *status);

} IVIDDEC1_Fxns;


/*@}*/

#ifdef __cplusplus
}
#endif

#endif
