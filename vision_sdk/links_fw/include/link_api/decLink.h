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
 * \ingroup FRAMEWORK_MODULE_API
 * \defgroup DECODE_LINK_API Video Decode Link API
 *
 * \brief  This module has the interface for using Decode Link
 *
 *         Decode Link integrated HDVICP codec, support multi channel decode.
 *         Video Decode Link can be used to decode a bitstream of different
 *         codec types such as
 *           - MJPEG
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file decLink.h
 *
 * \brief Decode Link API
 *
 * \version 0.0 (Jan 2013) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef DEC_LINK_H_
#define DEC_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/system_inter_link_api.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 *   \brief Default value of maximum number of output queues the dec link
 *          supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DEC_LINK_MAX_OUT_QUE                  ((UInt32) 1)

/**
 *******************************************************************************
 *
 *   \brief Max number of DEC channels per link supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DEC_LINK_MAX_CH                       ((UInt32) 8)

/**
 *******************************************************************************
 *
 *   \brief Maximum number of output buffers supported per channel
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DEC_LINK_MAX_NUM_OUT_BUF_PER_CH       ((UInt32) 16)

/**
 *******************************************************************************
 *
 *   \brief Default value for DPB size in frames
 *          This is valid only for H264 decode
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT   (-(Int32)1)

/**
 *******************************************************************************
 *
 *   \brief Default value for Number of buffers per channel request
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DEC_LINK_NUM_BUFFERS_PER_CHANNEL      ((UInt32) 4)

/* @} */


/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup DEC_LINK_API_CMD DECODE Link Control Commands
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Dec command to enable channel
 *          Application can use this command to enable an already
 *          disabled channel
 *
 *   SUPPORTED in ALL platforms
 *
 *   \param DecLink_ChannelInfo
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DEC_LINK_CMD_ENABLE_CHANNEL           (0x2002)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Dec command to disable channel
 *          Application can use this command to disable an alreday
 *          enabled channel
 *
 *   SUPPORTED in ALL platforms
 *
 *   \param DecLink_ChannelInfo
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DEC_LINK_CMD_DISABLE_CHANNEL          (0x2003)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Dec command to return buffer statistics
            Application can use this command to return the buffer statistics
            Mainly used for debugging purpose
 *
 *   SUPPORTED in ALL platforms
 *
 *   \param DecLink_BufferStats
 *
 *   \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DEC_LINK_CMD_GET_BUFFER_STATISTICS    (0x2004)

/* @} */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the decode process type (I/IP/All)
 *
 *          This enum is used to request decoder to decode only I, IP or ALL
 *          frame types
 *******************************************************************************
 */
typedef enum
{
  DEC_LINK_DECODE_ALL = 0,
  /**<
   * Indicates that all type of frames decoding is enabled
   * Applicable only for H264 and MPEG4 decode types
   */
  DEC_LINK_DECODE_IP_ONLY = 1,
  /**<
   * Indicates that only I/IDR and P frames decoding is enabled
   * Applicable only for H264 decode type
   */
  DEC_LINK_DECODE_I_ONLY = 2,
  /**<
   * Indicates that only I/IDR frames decoding is enabled
   * Applicable only for H264 and MPEG4 decode types
   */
  DEC_LINK_DECODE_FRAME_TYPE_FORCE32BITS = 0x7FFFFFFF
  /**< To make sure enum is 32 bits */
} DecLink_ChDecodeFrameType;

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the decode process level (filed/frame)
 *
 *          This enum indicates whether process call is done at a field
 *          level or frame level
 *******************************************************************************
 */
typedef enum
{
  DEC_LINK_FIELDLEVELPROCESSCALL = 0,
  /**
  * Indicates that process call should be at field level
  */
  DEC_LINK_FRAMELEVELPROCESSCALL = 1,
  /**
  * Indicates that process call should be at frame level
  */
  DEC_LINK_CAL_LEVEL_FORCE32BITS = 0x7FFFFFFF
  /**< To make sure enum is 32 bits */

} DecLink_ChProcessCallLevel;

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the decode channel codec create status
 *
 *          This enum indicates whether create channel really create the
 *          codec or only open the channel and neither codec instance
 *          will be created nor output buffers are allocated
 *          DEC_LINK_ALG_CREATE_STATUS_CREATE is the only option validated
 *******************************************************************************
 */
typedef enum
{
  DEC_LINK_ALG_CREATE_STATUS_DONOT_CREATE = 0,
  /**< Only the partial channel get created, neither codec instance
   *   nor the output buffers will get created.
   */
  DEC_LINK_ALG_CREATE_STATUS_CREATE = 1,
  /**< Fully functional channel will be created with Both codec
   *   instance and the output buffers created, reday to operate
   */
  DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE = 2,
  /**< Not for Application use, used by Link internals */
  DEC_LINK_ALG_CREATE_STATUS_DELETE = 3,
  /**< Not for Application use, used by Link internals */
  DEC_LINK_ALG_FORCE32BITS = 0x7FFFFFFF
  /**< To make sure enum is 32 bits */

} DecLink_ChDecodeAlgCreateStatus;


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Dec link channel info (channel number)
 *
 *          Defines the channel number of the DEC link for any channel
 *          specific dec link configuration/settings
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 chId;
    /**< Decoder channel number */
} DecLink_ChannelInfo;

/**
 *******************************************************************************
 *
 *   \brief DecLink buffer statistics structure
 *
 *          Defines the structure returned to application having the
 *          buffer statistics of one channel for the decoder link.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 numInBufQueCount;
    /**< Number of input buffers queued-in */
    UInt32 numOutBufQueCount;
    /**< Number of output buffers queued-in */
}DecLink_ChBufferStats;

/**
 *******************************************************************************
 *
 *   \brief DecLink buffer statistics structure
 *
 *          Defines the structure returned to application having the
 *          buffer statistics for a specific list of channels of the
 *          decoder link.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32  numCh;
    /**< Number of channels for buffer statistics requested */
    UInt32  chId[DEC_LINK_MAX_CH];
    /**< List of channels for which buffer statistics requested */
    DecLink_ChBufferStats stats[DEC_LINK_MAX_CH];
    /**< Buffer statistics of one channel for the decoder link */
} DecLink_BufferStats;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Decode link real time parameters
 *
 *          Defines those parameters that can be changed dynamically
 *          on a per channel basis for the decode link
 *
 *******************************************************************************
 */
typedef struct
{
    Int32 targetFrameRate;
    /**< Target frame rate of the decoder channel */
    Int32 targetBitRate;
    /**< Target bitrate of the decoder channel */
} DecLink_ChDynamicParams;

/**
 *******************************************************************************
 *  \brief Callback that is called when a frame is received at this link
 *
 *  \param appObj [IN] User pointer specified during create
 *  \param pFrame [IN] Pointer to the received frame
 *
 *  \return if return value is not SYSTEM_LINK_STATUS_SOK, frame is dropped
 *
 *******************************************************************************
 */
typedef Int32 (*DecodeLink_Callback)(Void *appObj,
                            System_Buffer *pBuffer);


/**
 *******************************************************************************
 *
 *   \brief Structure containing the Decode link create time channel parameters
 *
 *          Defines those parameters that can be configured/set during the
 *          create time on a per channel basis for the decode link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 format;
    /**< Video Codec format/type */
    Int32 profile;
    /**< Video coding profile */
    Int32 targetMaxWidth;
    /**< Target frame width of the decoder */
    Int32 targetMaxHeight;
    /**< Target frame height of the decoder */
    Int32 displayDelay;
    /**< Max number of frames delayed by decoder */
    DecLink_ChDynamicParams defaultDynamicParams;
    /**< Default dynamic params for decoder */
    UInt32 processCallLevel;
    /**< Specifies if process call is done frame level or field level
     *   See DecLink_ChProcessCallLevel for supported values
     *   For progressive mode,processCallLevel = DEC_LINK_FRAMELEVELPROCESSCALL;
     *   For interlaced  mode,processCallLevel = DEC_LINK_FIELDLEVELPROCESSCALL;
     */
    UInt32 fieldMergeDecodeEnable;
    /**< This option is applicable only for field wise (interlaced) encoding.
     *   Enable this option if the same input bit stream buffer
     *   will have both TOP and BOTTOM field data
     */
    UInt32 numBufPerCh;
    /**< Number of buffer to allocate per channel-wise */
    Int32 dpbBufSizeInFrames;
    /**< Size of the decoder picture buffer.If application
     *   knows the max number of reference frames in the
     *   stream to be fed to the decoder, it can set this
     *   value to enable reduced memory consumption.
     *   Application should set this value to default
     *   if it doesn't care about this parameter
     */
     UInt32 algCreateStatus;
    /**< See DecLink_ChDecodeAlgCreateStatus for supported values
    *    App can only configure this variable with two below values
     *         DEC_LINK_ALG_CREATE_STATUS_DONOT_CREATE -> 0
     *         DEC_LINK_ALG_CREATE_STATUS_CREATE -> 1
     *   If 0: Only the partial channel get created, neither codec instance
     *         nor the output buffers will be get created. App will be
     *         able to make this channel fully functional dynamically by
     *         calling DEC_LINK_CMD_CREATE_CHANNEL API
     *   If 1: Fully functional channel will be created with Both codec
     *         instance and the output buffers created, ready to operate
     */
    UInt32 decodeFrameType;
    /**< see DecLink_ChDecodeFrameType for supported values
    *    decodeFrameType is a Flag to decoder from application to
     *   request decoding of only I & IDR or IP or all frame types.
     *   The intention of this parameter is to have create time
     *   indication to codec for lesser memory foot print request.
     */
    UInt32 enableFrameSkipDue2AccumuInNextLink;
    /**< enableFrameSkipDue2AccumuInNextLink is a Flag to decoder
     *   from application to enable frame skip of the output frames
     *   immediately after decode and not send to next link if all
     *   output bufs are already queued in the input side of next link.
     */
    UInt32 extractJpegAppMarker;
    /**< TRUE: Extract JPEG APP marker data and place in System_Buffer
     *          as metadata
     *  FALSE: Dont extract JPEG App Marker
     */

} DecLink_ChCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Decode link create time parameters
 *
 *          This structure is used to create and configure a Decode link
 *          instance.
 *
 *******************************************************************************
 */
typedef struct
{
    System_LinkInQueParams      inQueParams;
    /**< Input queue information */
    System_LinkOutQueParams     outQueParams;
    /**< Output queue information */
    DecLink_ChCreateParams      chCreateParams[DEC_LINK_MAX_CH];
    /**< Decoder link channel create params */
    DecodeLink_Callback         callback;
    /**< User defined callback that is called when a frame is processed at
     *   this link
     */
    Void                       *appObj;
    /**< User specified pointer that is returned to user via the callback */
} DecLink_CreateParams;

/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline void DecLink_CreateParams_Init(DecLink_CreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Decode link register and init function
 *
 *          For each Decode instance
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DecLink_init(void);

/**
 *******************************************************************************
 *
 *   \brief Decode link de-register and de-init function
 *
 *          For each Decode instance
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DecLink_deInit(void);

/**
 *******************************************************************************
 *
 *   \brief Function to initialize the Decode Link Create Params
 *
 *          Sets default values for Decode link create time
 *          link & channel parameters.
 *          User/App can override these default values later.
 *
 *   \param pPrm [OUT] Default information
 *
 *   \return void
 *
 *******************************************************************************
 */
static inline void DecLink_CreateParams_Init(DecLink_CreateParams *pPrm)
{
    UInt32 i;

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    memset(pPrm, 0, sizeof(DecLink_CreateParams));

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;

    /* when set 0, decoder will take default value based on system
       defined default on BIOS side */
    for (i = 0U; i < DEC_LINK_MAX_CH; i++)
    {
        pPrm->chCreateParams[i].dpbBufSizeInFrames =
                                DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT;
        pPrm->chCreateParams[i].numBufPerCh = 0U;
        pPrm->chCreateParams[i].displayDelay = 0U;
        pPrm->chCreateParams[i].algCreateStatus =
                                DEC_LINK_ALG_CREATE_STATUS_CREATE;
        pPrm->chCreateParams[i].decodeFrameType = DEC_LINK_DECODE_ALL;
        pPrm->chCreateParams[i].enableFrameSkipDue2AccumuInNextLink =
                                                                (UInt32) FALSE;
        pPrm->chCreateParams[i].processCallLevel=
                                DEC_LINK_FRAMELEVELPROCESSCALL;
        pPrm->chCreateParams[i].fieldMergeDecodeEnable = (UInt32) FALSE;
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
