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
 * \defgroup ENCODE_LINK_API Video Encode Link API
 *
 * \brief  This module has the interface for using Encoder Link
 *
 *    Video Encode Link can be used to take input from a link & after doing
 *    Video Encode like H264/MJPEG, can output the frames to output queue.
 *
 *    Along with the above, this link also supports the dynamically updating
 *    parameters of a particular codec for a desired outcome.
 *
 *    Encoder Link integrated HDVICP codec, support multi channel encode.
 *    Video Encode Link can be used to encode a bitstream of different
 *    codec types such as
 *         - MJPEG
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file encLink.h
 *
 * \brief Video Encoder Link API
 *
 * \version 0.0 (April 2013) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef ENC_LINK_H_
#define ENC_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 *   \brief Maximum number of output queues the encode link supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ENC_LINK_MAX_OUT_QUE                ((UInt32) 1)

/**
 *******************************************************************************
 *
 *   \brief Max channels per link the encode link supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ENC_LINK_MAX_CH                     ((UInt32) 8)

/**
 *******************************************************************************
 *
 *   \brief Max number of buffer pools in encode link supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ENC_LINK_MAX_BUF_ALLOC_POOLS        ((UInt32) 8)

/**
 *******************************************************************************
 *
 *   \brief Max number of ROIs supported in ENC link currently
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define ENC_LINK_CURRENT_MAX_ROI            ((UInt32) 4)

/* @} */


/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ENC_LINK_API_CMD ENCODE Link Control Commands
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *   \brief Link CMD: Get Codec Params
 *
 *   Get ENC Codec Params dynamically
 *
 *   \param EncLink_GetDynParams * [OUT] Enc Get Codec parameters
 *******************************************************************************
 */
#define ENC_LINK_CMD_GET_CODEC_PARAMS       (0x5002)

/**
 *******************************************************************************
 *   \brief Link CMD: Set Bitrate Rate
 *
 *   Set ENC output bitrate dynamically
 *
 *   \param EncLink_ChBitRateParams * [IN] Enc BitRate parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_BITRATE      (0x5003)

/**
 *******************************************************************************
 *   \brief Link CMD: Set Frame Rate
 *
 *   Set ENC output frame rate dynamically
 *
 *   \param EncLink_ChFpsParams * [IN] Enc FPS parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_FPS          (0x5004)

/**
 *******************************************************************************
 *   \brief Link CMD: Set Input Frame Rate
 *
 *   Set ENC Input frame rate dynamically
 *
 *   \param EncLink_ChInputFpsParam * [IN] Enc Input FPS parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_INPUT_FPS    (0x5005)

/**
 *******************************************************************************
 *   \brief Link CMD: Enable channel
 *
 *   \param EncLink_ChannelInfo * [IN] enable channel
 *******************************************************************************
 */
#define ENC_LINK_CMD_ENABLE_CHANNEL         (0x5006)

/**
 *******************************************************************************
 *   \brief Link CMD: Disable channel
 *
 *   \param EncLink_ChannelInfo * [IN] disable channel
 *******************************************************************************
 */
#define ENC_LINK_CMD_DISABLE_CHANNEL        (0x5007)

/* @} */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Video buffer layout options.
 *         Used only for Interlaced (field vise) encoding.
 *         In one buffer it can have
 *             Both TOP and BOTTOM fields interleaved
 *             Both TOP and BOTTOM fields separate
 *             Only TOP field, no BOTTOM field
 *             Only BOTTOM field, no TOP field
 *
 *        This enum indicates whether process call is done at a field
 *        level or frame level
 *******************************************************************************
 */
typedef enum {
    VENC_FIELD_INTERLEAVED = 0,
    /**< Buffer layout is interleaved.
         This mode is not supported with RDK */
    VENC_FIELD_SEPARATED = 1,
    /**< Buffer layout is field separated. */
    VENC_TOP_ONLY = 2,
    /**< Buffer contains only top field.
         This mode is not yet validated with RDK */
    VENC_BOTTOM_ONLY = 3,
    /**< Buffer contains only bottom field.
         This mode is not yet validated with RDK */
    VENC_FIELD_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
} VENC_VideoLayout;

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the Encoder Rate-control type
 *
 *******************************************************************************
 */
typedef enum
{
    VENC_RATE_CTRL_VBR = 0,
    /**< Variable Bitrate: For Local Storage*/
    VENC_RATE_CTRL_CBR = 1,
    /**< Constant Bitrate, Low Delay: For Video Conferencing*/
    VENC_RATE_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
} VENC_RATE_CTRL_E;

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the EncodingPreset types
 *
 *******************************************************************************
 */
typedef enum {
    VENC_XDM_DEFAULT = 0,
    /**< Default setting of encoder. See codec specific
         documentation for its encoding behaviour */
    VENC_XDM_HIGH_QUALITY = 1,
    /**< High quality encoding. */
    VENC_XDM_HIGH_SPEED = 2,
    /**< High speed encoding. */
    VENC_XDM_USER_DEFINED = 3,
    /**< User defined configuration, using advanced parameters */
    VENC_XDM_HIGH_SPEED_MED_QUALITY = 4,
    /**< High speed, medium quality encoding */
    VENC_XDM_MED_SPEED_MED_QUALITY = 5,
    /**< Medium speed, medium quality encoding */
    VENC_XDM_MED_SPEED_HIGH_QUALITY = 6,
    /**< Medium speed, high quality encoding */
    VENC_XDM_ENCODING_PRESET_MAX  = 7,
    /**< Max value for this enum */
    VENC_XDM_PRESET_DEFAULT = VENC_XDM_MED_SPEED_MED_QUALITY,
    /**< Default setting of encoder.  See codec specific
         documentation for its encoding behaviour */
    VENC_XDM_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
} VENC_XDM_EncodingPreset;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure define Encode link channel dynamic Get config params
 *
 *          Defines encoder dynamic parameters that can be probed dynamically
 *          on a per channel basis for the encode link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 inputWidth;
    /**< Encoder input width */
    UInt32 inputHeight;
    /**< Encoder input height */
    UInt32 targetBitRate;
    /**< Modified encoder bit rate value in bits/sec format */
    UInt32 targetFps;
    /**< Modified encoder Frames per second (FPS) value in fps x 1000 format */
    UInt32 intraFrameInterval;
    /**< Modified encoder intraFrame rate value */

} EncLink_GetDynParams;

/**
 *******************************************************************************
 *
 *   \brief Structure define Encode link channel dynamic set config params
 *
 *          Defines encoder channel ID, params of this channel can be changed
 *          dynamically on a per channel basis for the encode link.
 *          used in multiple APIs, For Ex. Force I-frames/IDR parameters
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 chId;
    /**< Encoder channel number */
} EncLink_ChannelInfo;

/**
 *******************************************************************************
 *
 *   \brief Structure define Encode link channel dynamic set config params
 *
 *          Defines encoder bitRate parameters that can be changed dynamically
 *          on a per channel basis for the encode link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 targetBitRate;
    /**< Modified encoder bit rate value in bits/sec format */
} EncLink_ChBitRateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure define Encode link channel dynamic set config params
 *
 *          Defines encoder FPS parameters that can be changed dynamically
 *          on a per channel basis for the encode link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 targetFps;
    /**< Modified encoder Frames per second (FPS) value in fps x 1000 format */
    UInt32 targetBitRate;
    /**< Modified encoder bit rate value in bits/sec format */
} EncLink_ChFpsParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link channel set input frame-rate
 *
 *          Defines encoder input FPS param that can be changed dynamically
 *          on a per channel basis for the encode link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 inputFps;
    /**< input Modified encoder Frames per second (FPS) value */
} EncLink_ChInputFpsParam;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link real time parameters
 *
 *          Defines those parameters that can be changed dynamically
 *          on a per channel basis for the Encode link
 *
 *******************************************************************************
 */
typedef struct
{
    Int32 intraFrameInterval;
    /**< Intra frame interval in frames */
    Int32 targetBitRate;
    /**< Target bitrate of the encoder */
    Int32 interFrameInterval;
    /**< Inter frame interval in frames */
    Int32 mvAccuracy;
    /**< motion vector search accuracy @sa IVIDENC2_MotionVectorAccuracy */
    Int32 inputFrameRate;
    /**< to configure the encode link frame rate control  */
    Int32 rcAlg;
    /**< Rate-control Algorithm type */
    Int32 qpMin;
    /**< QP Min value */
    Int32 qpMax;
    /**< QP Max value */
    Int32 qpInit;
    /**< QP Init value */
    Int32 vbrDuration;
    /**< to configure the encode link cvbr duration  */
    Int32 vbrSensitivity;
    /**< to configure the encode link cvbe sensitivity  */
    Int32 maxPicSizeRatioI;
    /**< to configure the encode link maxPicSizeRatio for I-Frame */
} EncLink_ChDynamicParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link create time channel parameters
 *
 *          Defines those parameters that can be configured/set during the
 *          create time on a per channel basis for the Encode link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 format;
    /**< Coding type @sa System_IVideoFormat */
    Int32 profile;
    /**< Codec profile */
    UInt32 dataLayout;
    /**< Video buffer layout, @sa VENC_VideoLayout */
    UInt32 fieldMergeEncodeEnable;
    /**< Enable this option to Encode 2 fields in same Encode link call
         ie. both Top & Bottom field in same input buffer with Top filed
         followed by bottom field data in field seperated mode */
    Int32 enableAnalyticinfo;
    /**< Enable this option to generate MV Data in the bit stream */
    Int32 enableWaterMarking;
    /**< Enable this option to Insert Water Mark SEI message in the bitstream */
    Int32 maxBitRate;
    /** < Maximum Bit Rate for encode*/
    Int32 encodingPreset;
    /**< Enum identifying predefined encoding presets @sa XDM_EncodingPreset */
    Int32 rateControlPreset;
    /**<  Enum identifying predefined rate control presets
          @sa IVIDEO_RateControlPreset  */
    UInt32 enableHighSpeed;
    /**< Boolean to be set when this channel needs to be encoded in
         HIGH_SPEED mode. Requires encoding preset to be USER_DEFINED */
    UInt32 enableSVCExtensionFlag;
    /**< enable this option to insert svc extension headers into h.264 frames */
    Int32 numTemporalLayer;
    /**< Denotes the number of temporal layers that the encoder output
         bitstream will have. Default is the 1 for H.264 encoder link
         channels and is DONT CARE for both encoders */
    EncLink_ChDynamicParams defaultDynamicParams;
    /**< Create time default dynamic params */
    UInt32 overrideInputScanFormat;
    /**< TRUE : Use fieldPicEncode irrespective of i/p frame type.
         FALSE: Use i/p frame scanformat to decide encoding type.
     */
    UInt32 fieldPicEncode;
    /**< Valid only if overrideInputScanFormat is TRUE.
         TRUE : Force interlace encoding mode irrespective of i/p frame type.
         FALSE: Force progressive encoding mode irrespective of i/p frame type.
     */
    Int32 IDRFrameInterval;
    /**< IDR Frame interval value */
} EncLink_ChCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Encode link create time parameters
 *
 *          This structure is used to create and configure a Encode link
 *          instance.
 *
 *******************************************************************************
 */
typedef struct
{
    System_LinkInQueParams      inQueParams;
    /**< Input queue information. */
    System_LinkOutQueParams     outQueParams;
    /**< Output queue information. */
    EncLink_ChCreateParams      chCreateParams[ENC_LINK_MAX_CH];
    /**< Encoder link channel create params */
    UInt32                      numBufPerCh[ENC_LINK_MAX_BUF_ALLOC_POOLS];
    /**< Number of buffer to allocate per channel per buffr pool */
} EncLink_CreateParams;

/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline void EncLink_CreateParams_Init(EncLink_CreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Encode link register and init function
 *
 *          For each Encode instance
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EncLink_init(void);

/**
 *******************************************************************************
 *
 *   \brief Encode link de-register and de-init function
 *
 *          For each Encode instance
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 EncLink_deInit(void);

/**
 *******************************************************************************
 *
 *   \brief Function to initialize the Encode Link Create Params
 *
 *          Sets default values for Encode link create time
 *          link & channel parameters.
 *          User/App can override these default values later.
 *
 *   \param pPrm [OUT] Default information
 *
 *   \return void
 *
 *******************************************************************************
 */
static inline void EncLink_CreateParams_Init(EncLink_CreateParams *pPrm)
{
    UInt32 i;
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(EncLink_CreateParams));

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;

    /* when set 0, encoder will take default value based on system
       defined default on BIOS side */
    for (i = 0U; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 0U;
    }

    for (i = 0U; i < ENC_LINK_MAX_CH; i++)
    {
        pPrm->chCreateParams[i].dataLayout = VENC_FIELD_SEPARATED;
        pPrm->chCreateParams[i].fieldMergeEncodeEnable = (UInt32) FALSE;
        pPrm->chCreateParams[i].overrideInputScanFormat = (UInt32) FALSE;
        pPrm->chCreateParams[i].fieldPicEncode = (UInt32) FALSE;
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
