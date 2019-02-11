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
 *  \ingroup SYSTEM_LINK_INTER_LINK_API
 *
 *  @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \file system_buffer.h
 *
 *  \brief System Buffer Data Structure definition
 *
 *******************************************************************************
 */

#ifndef SYSTEM_BUFFER_H_
#define SYSTEM_BUFFER_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Bitstream buffer payload for System_Buffer
 *
 *******************************************************************************
 */
typedef struct {

    Void   *bufAddr;
    /**< when NULL bitstream data is not present,
     *      meta data could still be present */

    UInt32 dmaFd;
    /**< userspace handle to represent buffer
     For 4.4 kernel all buffer handled by Linux need to be as dmaFd.
     Each of the bios allocaed buffer needs to be mapped to a dmaFd
    */

    UInt32  bufSize;
    /**< Total buffer size */

    UInt32  fillLength;
    /**< size of valid data inside the buffer */

    Void   *metaBufAddr;
    /**< Metadata buffer address when NULL meta data is not present */

    UInt32  metaBufSize;
    /**< meta buffer size */

    UInt32  metaFillLength;
    /**< size of valid data inside the meta data buffer  */

    UInt32  flags;
    /**< see SYSTEM_BITSTREAM_BUFFER_FLAG_* */

    UInt32  width;
    /**< Width of frame encoded inside the bitstream */

    UInt32  height;
    /**< Height of frame encoded inside the bitstream */

} System_BitstreamBuffer;


/**
 *******************************************************************************
 *
 *  \brief Possible fields inside of System_VideoFrameBuffer.flags
 *
 *   @{
 *
 *******************************************************************************
 */

/* @} */

/**
 *******************************************************************************
 *
 *  \brief Structure to hold video frame
 *
 *******************************************************************************
*/
typedef struct {

    Void              *bufAddr[SYSTEM_MAX_PLANES];
    /**< when NULL video frame data is not present,
     *   meta data could still be present
     *
     *   Index 0: Y-plane for YUV420 data format
     *   Index 1: UV-plane for YUV420 data format
     *
     *   Index 0: YUV422i, RGB565, RGB888 etc are all represented
     *           in a single plane */

    UInt32 dmaFd[SYSTEM_MAX_PLANES];
    /**< userspace handle to represent buffer
     For 4.4 kernel all buffer handled by Linux need to be as dmaFd.
     Each of the bios allocaed buffer needs to be mapped to a dmaFd
    */

    Void              *metaBufAddr;
    /**< when NULL meta data is not present */

    UInt32            metaBufSize;
    /**< Total buffer size */

    UInt32            metaFillLength;
    /**< size of valid data inside the buffer  */

    System_LinkChInfo chInfo;
    /**< Channel specific information */

    UInt32            flags;
    /**< flags here convey certain properties of the buffer, which typically
     * may change with each frame. Refer macros above to set / get values
     * into this flags.
     * flags present in System_LinkChInfo will not typically change for
     * every frame */

} System_VideoFrameBuffer;

/**
 *******************************************************************************
 *
 *  \brief Structure to hold EGLPixmap type video frame
 *
 *******************************************************************************
*/
typedef struct {

    Void              *bufAddr[SYSTEM_MAX_PLANES];
    /**< Buffer address in memory */

    UInt32 dmaFd[SYSTEM_MAX_PLANES];
    /**< userspace handle to represent buffer
     For 4.4 kernel all buffer handled by Linux need to be as dmaFd.
     Each of the bios allocaed buffer needs to be mapped to a dmaFd
    */

    Void *eglPixmap;
    /**< An EglPixmap buffer that will be consumed
     *   by an EGLLink to render on.
     *
     *   It is required to be cast into a (Void *)
     *   so that compiling other links are not
     *   dependant on linux SGX package */

    UInt32 eglSurface;
    /**< An EGL surface for this pixmap. Cast to UInt32 */

    Void *pixmapNative;
    /**< Pixmap information to be used by EGL */

#ifdef QNX_BUILD
    Void *pixmapNativePtr;
    /**< Pointer to the pixmapNative buffer */
#endif

    System_LinkChInfo chInfo;
    /**< Channel specific information */

    UInt32            flags;
    /**< flags here convey certain properties of the buffer, which typically
     * may change with each frame. Refer macros above to set / get values
     * into this flags.
     * flags present in System_LinkChInfo will not typically change for
     * every frame */

} System_EglPixmapVideoFrameBuffer;

/**
*******************************************************************************
*
*  \brief Meta data buffer payload for System_Buffer
*
*******************************************************************************
*/
typedef struct {

    UInt32 numMetaDataPlanes;
    /**< Number of valid Meta-data planes */

    Void   *bufAddr[SYSTEM_MAX_META_DATA_PLANES];
    /**< Metadata buffer address when NULL meta data is not present */

    UInt32 dmaFd[SYSTEM_MAX_META_DATA_PLANES];
    /**< userspace handle to represent buffer
     For 4.4 kernel all buffer handled by Linux need to be as dmaFd.
     Each of the bios allocaed buffer needs to be mapped to a dmaFd
    */
    UInt32  metaBufSize[SYSTEM_MAX_META_DATA_PLANES];
    /**< meta buffer size */

    UInt32  metaFillLength[SYSTEM_MAX_META_DATA_PLANES];
    /**< size of valid data inside the meta data buffer  */

    UInt32  flags;
    /**< see SYSTEM_METADATA_BUFFER_FLAG_* */

} System_MetaDataBuffer;

/**
 *******************************************************************************
 *
 * \brief Max frames that can be present in the composite video frame payload
 *
 *******************************************************************************
 */
#define SYSTEM_MAX_FRAMES_IN_COMPOSITE_BUFFER   (8U)

/**
 *******************************************************************************
 *
 * \brief Composite video frame payload in System_Buffer
 *
 *******************************************************************************
 */
typedef struct {

    UInt32  numFrames;
    /**< Number of frames in this composite buffer */

    Void   *bufAddr[SYSTEM_MAX_PLANES][SYSTEM_MAX_FRAMES_IN_COMPOSITE_BUFFER];
    /**< Video frame address */

    UInt32 dmaFd[SYSTEM_MAX_PLANES][SYSTEM_MAX_FRAMES_IN_COMPOSITE_BUFFER];
    /**< userspace handle to represent buffer
     For 4.4 kernel all buffer handled by Linux need to be as dmaFd.
     Each of the bios allocaed buffer needs to be mapped to a dmaFd
    */

    Void   *metaBufAddr[SYSTEM_MAX_FRAMES_IN_COMPOSITE_BUFFER];
    /**< when NULL meta data is not present */

    UInt32  metaBufSize;
    /**< Total buffer size */

    UInt32  metaFillLength;
    /**< size of valid data inside the buffer  */

    System_LinkChInfo chInfo;
    /**<
     *   Channel information
     *
     *   Assumes that chInfo and meta data size and meta data buffer
     *   size is same for all frames in composite buffer */

    UInt32            flags;
    /**< NOT used - for future use */

} System_VideoFrameCompositeBuffer;


/**
 *******************************************************************************
 *
 * \brief System buffer information
 *
 *        A pointer to this structure is exchange between different links.
 *        This can have different payloads for different types of data.
 *
 *******************************************************************************
 */
typedef struct System_Buffer_s {

    System_BufferType     bufType;
    /**< Buffer type, this is used to identify
     *   the payload type associated with this buffer */

    UInt32                chNum;
    /**< Channel associated with this buffer. MUST be < 255 */

    UInt64                srcTimestamp;
    /**< Timestamp updated at the source. This is the timestamp at which the
     *   source buffer was available, in units of usec's
     */

    UInt32                frameId;
    /**< Unique ID associated with a frame that is set by Source Link */

    UInt64                linkLocalTimestamp;
    /**< Timestamp at which the buffer was available at the input of the local
     *   link, in units of usec's
     */
    UInt32                payloadSize;
    /**< Payload size in bytes, MUST be < 4KB */

    Void                 *payload;
    /**< Pointer to payload data */

    /** below fields are used by specific links internally
     *   and other links should not modify their values */

    UInt32                selectOrgChNum;
    /**< used by select link, keeps
     *   track of original channel num before the select operation */

    struct System_Buffer_s *pDupOrgFrame;
     /**< used by DUP link
     * Pointer to original System_buffer in case this is a dup of original
     * buffer */

    UInt32                dupCount;
    /**< Used by DUP link
     *   Dup count in case the original system_buffer is duplicated  using
     *   dup link */

    struct System_Buffer_s *pSplitOrgFrame;
     /**< used by SPLIT link
     * Pointer to original System_buffer in case this is a split of original
     * buffer */

    UInt32                splitCount;
    /**< Used by SPLIT link
     *   Split count in case the original system_buffer is duplicated  using
     *   dup link */

    UInt32                ipcInOrgQueElem;
    /**< Used by IPC IN link to keep track of original IPC queue element */

    Void                 *pCaptureOrgBufferPtr;
    /**< Used by capture link to hold driver/algorithm specific private info */

    Void                 *pSyncLinkOrgBufferPtr;
    /**< Used by Sync Link to keep track of the original buffers */

    Void                 *pVpeLinkPrivate;
    /**< Used by VPE link to hold driver/algorithm specific private info */

    Void                 *pEncDecLinkPrivate;
    /**< Used by VDEC link to hold driver/algorithm specific private info */

    UInt64                ipcPrfTimestamp64[2U];
    /**< Used to measure IPC overheads */

    Void                 *pImgPmdLinkPrivate;
    /**< Used by the image pyramid algorithm link to hold private info */

    UInt32 hlosTranslationDisable;
    /**< Used to indicate the ipcOutLink whether to translate the bufAddrs */

} System_Buffer;

/**
 *******************************************************************************
 *
 *  \brief Max payload area size.
 *
 *         The System_Buffer can have different payloads: video frames,
 *         meta data, bitstreams or composite video frame buffer. This macro
 *         defines the maximum size of the payload.
 *         Static checks will be done during init time to make sure this
 *         condition is satisfied
 *
 *******************************************************************************
 */
#define SYSTEM_MAX_PAYLOAD_SIZE     (sizeof(System_VideoFrameCompositeBuffer))

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Get_Bitstream_Format
                                                (UInt32 container);
static inline UInt32 System_Bitstream_Buffer_Flag_Set_Bitstream_Format
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Bitstream_Buffer_Flag_Get_Is_Keyframe
                                                (UInt32 container);
static inline UInt32 System_Bitstream_Buffer_Flag_Set_Is_Keyframe
                                                (UInt32 container,UInt32 value);
static inline UInt32 System_Bitstream_Buffer_Flag_Get_Is_Flushbuf
                                                (UInt32 container);
static inline UInt32 System_Bitstream_Buffer_Flag_Set_Is_Flushbuf
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Video_Frame_Get_Flag_Fid
                                                (UInt32 container);
static inline UInt32 System_Video_Frame_Set_Flag_Fid
                                                (UInt32 container,UInt32 value);
/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Gets Type of bitstream
 *         Refer to System_BitstreamCodingType for values
 *
 *         Encoded in bit-field (0x000000FF)
 *
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Get_Bitstream_Format(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x000000FFU, 0U);
}

/**
 *******************************************************************************
 *
 *  \brief Sets Type of bitstream
 *         Refer to System_BitstreamCodingType for values
 *
 *         Encoded in bit-field (0x000000FF)
 *
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Set_Bitstream_Format(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    container = SystemUtils_pack_bitfield(container, value, 0x000000FFU, 0U);
    return container;
}

/**
 *******************************************************************************
 *
 *  \brief Gets Key frame identifier
 *
 *         Encoded in bit-field (0x00000100)
 *
 *         0: Not a key-frame
 *         1: Key-frame, ex, I-frame
 *
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Get_Is_Keyframe(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x00000100U, 8U);
}

/**
 *******************************************************************************
 *
 *  \brief Sets Key frame identifier
 *
 *         Encoded in bit-field (0x00000100)
 *
 *         0: Not a key-frame
 *         1: Key-frame, ex, I-frame
 *
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Set_Is_Keyframe(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x00000100U, 8U);
    return container;
}

/**
 *******************************************************************************
 *
 *  \brief Gets Flush Buffer identifier
 *
 *         Encoded in bit-field (0x00000200)
 *
 *         0: No Flush buffer identifier
 *         1: Flush buffer identifier
 *
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Get_Is_Flushbuf(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x00000200U, 9U);
}

/**
 *******************************************************************************
 *
 *  \brief Sets Flush Buffer identifier
 *
 *         Encoded in bit-field (0x00000200)
 *
 *         0: No Flush buffer identifier
 *         1: Flush buffer identifier
 *
 *******************************************************************************
 */
static inline UInt32 System_Bitstream_Buffer_Flag_Set_Is_Flushbuf(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x00000200U, 9U);
    return container;
}

/**
 *******************************************************************************
 *
 *  \brief Gets Field ID for interlaced video, set to 0 for progressive video
 *
 *         Encoded in bit-field (0x00000001)
 *
 *         0: even field
 *         1: odd field
 *
 *******************************************************************************
 */
static inline UInt32 System_Video_Frame_Get_Flag_Fid(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x00000001U, 0U);
}

/**
 *******************************************************************************
 *
 *  \brief Sets Field ID for interlaced video, set to 0 for progressive video
 *
 *         Encoded in bit-field (0x00000001)
 *
 *         0: even field
 *         1: odd field
 *
 *******************************************************************************
 */
static inline UInt32 System_Video_Frame_Set_Flag_Fid(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x00000001U, 0U);
    return container;
}


#endif

/* @} */
