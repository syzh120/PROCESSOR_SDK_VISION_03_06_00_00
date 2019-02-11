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
 * \file encLink_priv.h Encode Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Encode link instance/handle object
 *         - All the local data structures
 *         - Codec interfaces
 *
 * \version 0.0 (April 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _ENC_LINK_PRIV_H_
#define _ENC_LINK_PRIV_H_

#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/gates/GateMutexPri.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <include/link_api/encLink.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include <include/link_api/system_debug.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec_prf.h>
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <src/rtos/utils_common/include/utils_buf_ext.h>
#include "encLink_algIf.h"
#include "encLink_jpeg_priv.h" //Added MJPEG Encoder Support
#include "encLink_h264_priv.h" //Added H264 Encoder Support


/* =============================================================================
 * All success and failure codes for the module
 * ========================================================================== */

/** @brief Operation successful. */
#define ENC_LINK_S_SUCCESS                   (0)

/** @brief General Failure */
#define ENC_LINK_E_FAIL                      (-1)

/** @brief Argument passed to function is invalid. */
#define ENC_LINK_E_INVALIDARG                (-2)

/** @brief Encoder algorithm create failed */
#define ENC_LINK_E_ALGCREATEFAILED           (-3)

/** @brief RMAN assign resource failed */
#define ENC_LINK_E_RMANRSRCASSIGNFAILED      (-4)

/** @brief XDM_SETPARAM failed */
#define ENC_LINK_E_ALGSETPARAMSFAILED        (-5)

/** @brief Unknown codec type failed */
#define ENC_LINK_E_UNSUPPORTEDCODEC          (-6)

/** @brief Creation of task failed */

#define ENC_LINK_E_TSKCREATEFAILED           (-7)

/** @brief XDM_GETBUFINFO failed */
#define ENC_LINK_E_ALGGETBUFINFOFAILED       (-8)

#define ENC_LINK_OBJ_MAX                     (1)

#define ENC_LINK_MAX_OUT_FRAMES_PER_CH       (SYSTEM_LINK_FRAMES_PER_CH + 2)

#define ENC_LINK_MAX_OUT_FRAMES              (ENC_LINK_MAX_CH*ENC_LINK_MAX_OUT_FRAMES_PER_CH)

#define ENC_LINK_CMD_GET_PROCESSED_DATA      (0x6000)

/** \Dec command to send late ACK */
#define ENC_LINK_CMD_LATE_ACK                (0x6001)

#define ENC_LINK_MAX_REQ                     (ENC_LINK_MAX_OUT_FRAMES)

#define ENC_LINK_MAX_REQ_OBJ_DUMMY           (ENC_LINK_MAX_CH * 2)

#define ENC_LINK_PROCESS_TSK_STACK_SIZE      (8 * KB)

#define ENC_LINK_MAX_TASK_NAME_SIZE          (32)

#define ENC_LINK_TASK_POLL_DURATION_MS       (8)

#define ENC_LINK_REQLIST_MAX_REQOBJS         (4)
#define ENC_LINK_NUM_ALGPROCESS_PER_HDVICP_ACQUIRE                       (8)
#define ENC_LINK_DEFAULT_ALGPARAMS_STARTX                                (0)
#define ENC_LINK_DEFAULT_ALGPARAMS_STARTY                                (0)
#define ENC_LINK_DEFAULT_ALGPARAMS_MVACCURACY  \
                                             (IVIDENC2_MOTIONVECTOR_QUARTERPEL)
#define ENC_LINK_DEFAULT_ALGPARAMS_TARGETFRAMERATEX1000                  (30000)
#define ENC_LINK_DEFAULT_ALGPARAMS_REFFRAMERATEX1000                     (30000)

/**
 *****************************************************************************
 * @def    ENC_LINK_DEFAULT_ALGPARAMS_MAXINTERFRAMEINTERVAL
 * @brief  Default interframe interval
 *
 * I to P frame distance. e.g. = 1 if no B frames, 2 to insert one B frame.
 * @remarks   This is used for setting the maximum number of B frames
 *            between two refererence frames.
 *****************************************************************************
*/
#define ENC_LINK_DEFAULT_ALGPARAMS_MAXINTERFRAMEINTERVAL         (1)
#define ENC_LINK_DEFAULT_ALGPARAMS_INTRAFRAMEINTERVAL            (30)
#define ENC_LINK_DEFAULT_ALGPARAMS_ENCODINGPRESET                (XDM_DEFAULT)
#define ENC_LINK_DEFAULT_ALGPARAMS_ANALYTICINFO                  (0)
#define ENC_LINK_DEFAULT_ALGPARAMS_ENABLEWATERMARKING            (0)
#define ENC_LINK_DEFAULT_ALGPARAMS_INPUTFRAMERATE                (30)
#define ENC_LINK_DEFAULT_ALGPARAMS_RATECONTROLPRESET             (IVIDEO_STORAGE)
#define ENC_LINK_DEFAULT_ALGPARAMS_TARGETBITRATE                 (2 * 1000 * 1000)
#define ENC_LINK_DEFAULT_ALGPARAMS_MAXBITRATE                    (-1)
#define ENC_LINK_DEFAULT_ALGPARAMS_VBRDURATION                   (8)
#define ENC_LINK_DEFAULT_ALGPARAMS_VBRSENSITIVITY                (0)
#define ENC_LINK_DEFAULT_ALGPARAMS_QPMIN                         (0)
#define ENC_LINK_DEFAULT_ALGPARAMS_QPMAX                         (40)
#define ENC_LINK_DEFAULT_ALGPARAMS_QPINIT                        (-1)


/** @brief Enclink internal to limit the input bitrate range to
           greater than 16 * 1024 for H264 and MJPEG*/
#define ENC_LINK_MIN_ALGPARAMS_TARGETBITRATE         (16*1024)

/** @brief Enclink internal to limit the input bitrate
           range to greater than 1 * 1024 for MPEG4*/
#define ENC_LINK_MIN_ALGPARAMS_MPEG4_TARGETBITRATE   (1*1024)

/** @brief Enclink internal values to set the QP parameters */
#define  ENC_LINK_MIN_ALGPARAMS_H264_QPMIN     (0)
#define  ENC_LINK_MAX_ALGPARAMS_H264_QPMIN     (51)
#define  ENC_LINK_MIN_ALGPARAMS_H264_QPMAX     (0)
#define  ENC_LINK_MAX_ALGPARAMS_H264_QPMAX     (51)
#define  ENC_LINK_MIN_ALGPARAMS_H264_QPI       (-1)
#define  ENC_LINK_MAX_ALGPARAMS_H264_QPI       (51)
#define  ENC_LINK_MIN_ALGPARAMS_H264_QPP       (-1)
#define  ENC_LINK_MAX_ALGPARAMS_H264_QPP       (51)
#define  ENC_LINK_MIN_ALGPARAMS_MPEG4_QPMIN    (1)
#define  ENC_LINK_MAX_ALGPARAMS_MPEG4_QPMIN    (31)
#define  ENC_LINK_MIN_ALGPARAMS_MPEG4_QPMAX    (1)
#define  ENC_LINK_MAX_ALGPARAMS_MPEG4_QPMAX    (31)
#define  ENC_LINK_MIN_ALGPARAMS_MPEG4_QPI      (1)
#define  ENC_LINK_MAX_ALGPARAMS_MPEG4_QPI      (31)
#define  ENC_LINK_MIN_ALGPARAMS_MPEG4_QPP      (1)
#define  ENC_LINK_MAX_ALGPARAMS_MPEG4_QPP      (31)
#define  ENC_LINK_MIN_ALGPARAMS_MJPEG_QF       (2)
#define  ENC_LINK_MAX_ALGPARAMS_MJPEG_QF       (97)

/**
 *****************************************************************************
 * @def    ENC_LINK_SETCONFIG_BITMASK
 * @brief  Bit mask values for each dynamic encoder configuration paramters
 *****************************************************************************
*/
#define ENC_LINK_SETCONFIG_BITMASK_BITRATE                  (0)
#define ENC_LINK_SETCONFIG_BITMASK_FPS                      (1)
#define ENC_LINK_SETCONFIG_BITMASK_INTRAI                   (2)
#define ENC_LINK_SETCONFIG_BITMASK_FORCEI                   (3)
#define ENC_LINK_SETCONFIG_BITMASK_QPI                      (4)
#define ENC_LINK_SETCONFIG_BITMASK_QPP                      (5)
#define ENC_LINK_SETCONFIG_BITMASK_RCALGO                   (6)
#define ENC_LINK_SETCONFIG_BITMASK_VBRD                     (7)
#define ENC_LINK_SETCONFIG_BITMASK_VBRS                     (8)
#define ENC_LINK_SETCONFIG_BITMASK_ROI                      (9)
#define ENC_LINK_SETCONFIG_BITMASK_PACKETSIZE               (10)
#define ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE              (0xFFFFFFFF)

#define ENC_LINK_MV_DATA_SIZE           (8 * 1024)


/* =============================================================================
 * All the below Link CMD are not exposed to link interface level as of now.
 * Will be used in future, when integrate H264 or MPEG4 encoders
 * ========================================================================== */

/**
 *******************************************************************************
 *   \brief Link CMD: Set Intra Frame Interval
 *
 *   Set ENC Intra frame interval  dynamically
 *
 *   \param EncLink_ChIntraFrIntParams * [IN] Enc Intra Frame Interval parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_INTRAI       (0x5011)
/**
 *******************************************************************************
 *   \brief Link CMD: Set Force I-Frame
 *
 *   Defines encoder Force I-frames/IDR parameters that can be changed
 *   dynamically on a per channel basis for the encode link
 *   Set ENC to force an I-Frame dynamically
 *
 *   \param EncLink_ChannelInfo * [IN] Enc Force I-Frame parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_FORCEI       (0x5012)
/**
 *******************************************************************************
 *   \brief Link CMD: Set Rate Control Algorithm
 *
 *   Set ENC Rate control algorithm dynamically
 *
 *   \param EncLink_ChRcAlgParams * [IN] Enc  Rate control algorithm parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_RCALGO       (0x5013)
/**
 *******************************************************************************
 *   \brief Link CMD: Set Quantization Parameters for I/IDR frames
 *
 *   Set ENC Quantization Parameters for I/IDR frames dynamically
 *
 *   \param EncLink_ChQPParams * [IN] Enc Quantization Parameter
 *          for I/IDR frames
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_QP_I         (0x5014)
/**
 *******************************************************************************
 *   \brief Link CMD: Set Quantization Parameters for P frames
 *
 *   Set ENC Quantization Parameters for P frames dynamically
 *
 *   \param EncLink_ChQPParams * [IN] Enc Quantization Parameter for P frames
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_QP_P         (0x5015)
/**
 *******************************************************************************
 *   \brief Link CMD: Set a Flag to Dump a JPEG frame
 *
 *   Set ENC Flag to Dump a JPEG frame dynamically
 *
 *   \param EncLink_ChannelInfo * [IN] Enc Flag to Dump a JPEG frame parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_SNAPSHOT     (0x5016)
/**
 *******************************************************************************
 *   \brief Link CMD: Set VBR Duration
 *
 *   Set ENC VBR Duration to switch states dynamically
 *
 *   \param EncLink_ChCVBRDurationParams * [IN] Enc VBR Duration parameter
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_VBRD         (0x5017)
/**
 *******************************************************************************
 *   \brief Link CMD: Set VBR Sensitivity
 *
 *   Set ENC VBR Sensitivity dynamically
 *
 *   \param EncLink_ChCVBRSensitivityParams * [IN] Enc Intra Frame
 *          Interval parameter
*/
#define ENC_LINK_CMD_SET_CODEC_VBRS         (0x5018)
/**
 *******************************************************************************
 *   \brief Link CMD: Set ROI parameters
 *
 *   Set ENC ROI dynamically
 *
 *   \param EncLink_ChROIParams * [IN] Enc ROI parameters
 *******************************************************************************
 */
#define ENC_LINK_CMD_SET_CODEC_ROI          (0x5019)

/**
 *******************************************************************************
 *   \brief Link CMD: Codec Alg type change
 *
 *   \param EncLink_ChSwitchCodecTypeParams * [IN] codec Alg create params
 *******************************************************************************
 */
#define ENC_LINK_CMD_SWITCH_CODEC_CHANNEL    (0x501A)

/**
 *******************************************************************************
 *  \brief Enc link channel dynamic set config params
 *
 *  Defines encoder intraFrameInterval parameters that can be changed
 *  dynamically on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChIntraFrIntParams
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 intraFrameInterval;
    /**< Modified encoder intraFrame rate value */
} EncLink_ChIntraFrIntParams;

/**
 *******************************************************************************
 *  \brief Enc link channel dynamic set config params
 *
 *  Defines encoder RateControl Algorithm parameter that can be changed
 *  dynamically on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChRcAlgParams
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 rcAlg;
    /**< Modified encoder intraFrame rate value */
} EncLink_ChRcAlgParams;

/**
 *******************************************************************************
 *  \brief Enc link channel dynamic set config params
 *
 *  Defines encoder QP min,max,init parameters that can be changed dynamically
 *  on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChQPParams
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 qpMin;
    /**< Modified encoder qpMin value */
    UInt32 qpMax;
    /**< Modified encoder qpMax value */
    Int32 qpInit;
    /**< Modified encoder qpInit value */
} EncLink_ChQPParams;

/**
 *******************************************************************************
 *  \brief Enc link channel dynamic set config params
 *
 *  Defines encoder CVBR duration parameters that can be changed dynamically
 *  on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChCVBRDurationParams
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 vbrDuration;
    /**< Modified encoder VBRDuration value */
} EncLink_ChCVBRDurationParams;

/**
 *******************************************************************************
 *  \brief Enc link channel dynamic set config params
 *
 *  Defines encoder CVBR sensitivity parameters that can be changed dynamically
 *  on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChCVBRSensitivityParams
{
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 vbrSensitivity;
    /**< Modified encoder VBRSensitivity value */
} EncLink_ChCVBRSensitivityParams;

/**
 *******************************************************************************
 *  \brief Enc link channel ROI set config params
 *
 *  Defines encoder ROI parameters that can be changed dynamically
 *  on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChROIParams {
    UInt32 chId;
    /**< Encoder channel number */
    UInt32 numOfRegion;
    /**< Number of ROIs to be passed to codec */
    UInt32 startX[ENC_LINK_CURRENT_MAX_ROI];
    /**< X co-ordinate of region */
    UInt32 startY[ENC_LINK_CURRENT_MAX_ROI];
    /**< Y co-ordinate of region */
    UInt32 width[ENC_LINK_CURRENT_MAX_ROI];
    /**< width of region */
    UInt32 height[ENC_LINK_CURRENT_MAX_ROI];
    /**< height of region */
    UInt32 type[ENC_LINK_CURRENT_MAX_ROI];
    /**< Type of each ROI */
    UInt32 roiPriority[ENC_LINK_CURRENT_MAX_ROI];
    /**< Priority of each ROI */
} EncLink_ChROIParams;

/**
 *******************************************************************************
 *  \brief Enc link channel dynamic codec type switch params
 *
 *  Defines encoder data structure to switch the codec type dynamically
 *  on a per channel basis for the encode link
 *******************************************************************************
 */
typedef struct EncLink_ChSwitchCodecTypeParams
{
    UInt32 switchCodecFlag;
    /**< Set to 1 if enable codec switch,
      * Added for checking the validity before the codec switch */
    UInt32 chId;
    /**< Encoder channel number */
    EncLink_ChCreateParams algCreatePrm;
    /**< channel specific create time paramters */
} EncLink_ChSwitchCodecTypeParams;

/**
 *******************************************************************************
 *  \brief Enc link MV data element type
 *
 *  This structure usage has been described in the H264 Codec User
 *  Guide, Section "Motion Vector and SAD Access API" in much detail.
 *******************************************************************************
 */
typedef struct EncLink_h264_ElementInfo
{

    UInt32 startPos;
    /**< starting position of data from base address */
    UInt16 jump;
    /**< number of bytes to jump from current postion
        *     to get next data of this element group */
    UInt32 count;
    /**< number of data elements in this group */
}EncLink_h264_ElementInfo;

/**
 *******************************************************************************
 *  \brief Enc link MV Header data export structure
 *
 *  Defines the MV Header info structure, for easy export interface.
 *
 *  This structure usage has been described in the H264 Codec User
 *  Guide, Section "Motion Vector and SAD Access API" in much detail.
 *******************************************************************************
 */
typedef struct EncLink_h264_AnalyticHeaderInfo {

    UInt32 NumElements;
    /**< Total number of elements in the buffer */
    EncLink_h264_ElementInfo elementInfoField0SAD;
    /**< member element of SAD type in the buffer */
    EncLink_h264_ElementInfo elementInfoField1SAD;
    /**< member element of SAD type in the buffer */
    EncLink_h264_ElementInfo elementInfoField0MVL0;
    /**< member element of MVL type in the buffer */
    EncLink_h264_ElementInfo elementInfoField0MVL1;
    /**< member element of MVL type in the buffer */
    EncLink_h264_ElementInfo elementInfoField1MVL0;
    /**< member element of MVL type in the buffer */
    EncLink_h264_ElementInfo elementInfoField1MVL1;
    /**< member element of MVL type in the buffer */
} EncLink_h264_AnalyticHeaderInfo;

/** Enc link Analytic Header size */
#define ENC_LINK_SIZEOF_ANALYTICHEADERINFO    \
        (sizeof(EncLink_h264_AnalyticHeaderInfo))

/** Adding another 100 bytes just as a safety measure to the
    calculated MV buffer size*/
#define ENC_LINK_MVSIZE_SAFETY_BYTES  (100)


/** ENC_LINK_GET_MVBUF_SIZE - size calculation
 *  @brief Macro that returns max size of mv buffer for a frame
 *  MVData size =
    (76 + ( (MBs_In_Picture + 63) & 0xFFFFFFC0) * 2 + (MBs_In_Picture + 512) * 8 )
    bytes
 */
#define ENC_LINK_GET_MVBUF_SIZE(width,height)          \
        (ENC_LINK_SIZEOF_ANALYTICHEADERINFO + \
        (((((width) * (height)/ (16 * 16)) + 63) & 0xffffffc0)*2) + \
        ((((width) * (height)/ (16 * 16)) + 512) *8) + ENC_LINK_MVSIZE_SAFETY_BYTES)

/**
 ******************************************************************************
 *  \brief Enc link request object type
 ******************************************************************************
 */
typedef enum EncLink_ReqObjType_e
{
    ENC_LINK_REQ_OBJECT_TYPE_REGULAR,
    ENC_LINK_REQ_OBJECT_TYPE_DUMMY_CODEC_SWITCH
} EncLink_ReqObjType_e;

/**
 *******************************************************************************
 *   \brief Structure defines the Encode link frame skip parameters
 *
 *******************************************************************************
 */
typedef struct EncLink_processFrameRate {
   Int32 firstTime;
   Int32 inCnt;
   Int32 outCnt;
   Int32 multipleCnt;
} EncLink_processFrameRate;

/**
 *******************************************************************************
 *   \brief Structure defines the Encode link Output channel Object
 *
 *******************************************************************************
 */
typedef struct EncLink_OutObj {
    Utils_BufHndlExt bufOutQue;
    UInt32 numAllocPools;
    System_Buffer outBufs[ENC_LINK_MAX_OUT_FRAMES];
    Utils_EncDecLinkPvtInfo linkPvtInfo[ENC_LINK_MAX_OUT_FRAMES];
    System_BitstreamBuffer bitstreamBuf[ENC_LINK_MAX_OUT_FRAMES];
    UInt32 outNumBufs[UTILS_BUF_MAX_ALLOC_POOLS];
    UInt32 buf_size[UTILS_BUF_MAX_ALLOC_POOLS];
    UInt32 ch2poolMap[ENC_LINK_MAX_CH];
} EncLink_OutObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Encode link request object
 *
 *******************************************************************************
 */
typedef struct EncLink_ReqObj {
    System_BufferList InFrameList;
    System_Buffer *OutBuf;
    EncLink_ReqObjType_e type;
} EncLink_ReqObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Encode link request queue list
 *
 *******************************************************************************
 */
typedef struct EncLink_ReqList {
    UInt32 numReqObj;
    EncLink_ReqObj *reqObj[ENC_LINK_REQLIST_MAX_REQOBJS];
} EncLink_ReqList;

/**
 *******************************************************************************
 *   \brief Structure defines the Encode link Alg/Codec object
 *
 *******************************************************************************
 */
typedef struct EncLink_algObj {
    union {
        EncLink_JPEGObj jpegAlgIfObj;//Added MJPEG Encoder Support
        EncLink_H264Obj h264AlgIfObj;//Added H264 Encoder Support
    } u;
    EncLink_AlgCreateParams algCreateParams;
    EncLink_AlgDynamicParams algDynamicParams;
    UInt32 setConfigBitMask;
    UInt32 getConfigFlag;
} EncLink_algObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Encode link channel Object
 *
 *******************************************************************************
 */
typedef struct EncLink_ChObj {
    Utils_QueHandle inQue;
    EncLink_algObj algObj;
    EncLink_processFrameRate frameStatus;
    Bool disableChn;
    Int32  inputFrameRate;
    Uint32 curFrameNum;
    UInt32 nextFid;
    UInt32 allocPoolID;
    UInt32 processReqestCount;
    UInt32 getProcessDoneCount;
    System_IpcBuffer *inFrameMem[ENC_LINK_MAX_REQ];
    Bool   forceAvoidSkipFrame;
    Bool   forceDumpFrame;
    System_Buffer dummyBitBuf;
    System_Buffer dummyCodecSwitchBitBuf;
    EncLink_ChSwitchCodecTypeParams switchCodec;
    UInt32 expectedFid;
    Bool   synchToBottomField;
} EncLink_ChObj;

/**
 *******************************************************************************
 *   \brief Structure defines the top level Encode link Object
 *
 *******************************************************************************
 */
typedef struct EncLink_Obj {
    UInt32 linkId;
    char name[32];
    Utils_TskHndl tsk;
    System_LinkInfo inTskInfo;
    System_LinkQueInfo inQueInfo;
    EncLink_OutObj outObj;
    EncLink_ReqObj reqObj[ENC_LINK_MAX_REQ];
    Utils_QueHandle reqQue;
    EncLink_ReqObj *reqQueMem[ENC_LINK_MAX_REQ];
    struct encDummyReqObj_s {
        EncLink_ReqObj reqObjDummy[ENC_LINK_MAX_REQ_OBJ_DUMMY];
        Utils_QueHandle reqQueDummy;
        EncLink_ReqObj *reqQueMemDummy[ENC_LINK_MAX_REQ_OBJ_DUMMY];
    } encDummyReqObj;
    volatile Utils_EncDec_LinkState state;
    Bool isReqPend;
    System_LinkInfo info;
    EncLink_ChObj chObj[ENC_LINK_MAX_CH];
    EncLink_CreateParams createArgs;
    Utils_QueHandle processDoneQue;
    EncLink_ReqObj *processDoneQueMem[ENC_LINK_MAX_OUT_FRAMES];
    struct encProcessTsk_s {
        BspOsal_TaskHandle tsk;
        char name[ENC_LINK_MAX_TASK_NAME_SIZE];
        Utils_QueHandle processQue;
        EncLink_ReqObj *processQueMem[ENC_LINK_MAX_OUT_FRAMES];
    } encProcessTsk[NUM_HDVICP_RESOURCES];

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    Utils_MsgHndl *pMsgTmp;
    Int32 lateAckStatus;

    #if 0
    Utils_LinkStatistics linkStats;
    Utils_LatencyStats  linkLatency;
    /**< Structure to find out min, max and average latency of the link */
    Utils_LatencyStats  srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */
    #endif
    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
} EncLink_Obj;

/*******************************************************************************
 *  Encode Link Private Functions
 *******************************************************************************
 */
Int32 EncLink_getInfo(Void * pTsk, System_LinkInfo * info);
Int32 EncLink_getFullFrames(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList);
Int32 EncLink_putEmptyFrames(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList);

Int32 EncLink_codecCreate(EncLink_Obj * pObj, EncLink_CreateParams * pPrm);
Int32 EncLink_codecProcessData(EncLink_Obj * pObj);
Int32 EncLink_codecGetProcessedDataMsgHandler(EncLink_Obj * pObj);
Int32 EncLink_codecStop(EncLink_Obj * pObj);
Int32 EncLink_codecDelete(EncLink_Obj * pObj);
Int32 EncLink_getCurLinkID(Void * key);

Int32 EncLink_codecGetProcessedDataMsgHandler(EncLink_Obj * pObj);
Int32 EncLink_codecGetDynParams(EncLink_Obj * pObj,
                              EncLink_GetDynParams * params);
Int32 EncLink_codecSetBitrate(EncLink_Obj * pObj,
                              EncLink_ChBitRateParams * parms);
Int32 EncLink_codecSetFps(EncLink_Obj * pObj, EncLink_ChFpsParams * params);
Int32 EncLink_codecInputSetFps(EncLink_Obj * pObj, EncLink_ChInputFpsParam * params);
Int32 EncLink_codecSetIntraIRate(EncLink_Obj * pObj, EncLink_ChIntraFrIntParams * params);
Int32 EncLink_codecSetForceIDR(EncLink_Obj * pObj, EncLink_ChannelInfo * params);
Int32 EncLink_codecSetrcAlg(EncLink_Obj * pObj, EncLink_ChRcAlgParams* params);
Int32 EncLink_codecSetqpParamI(EncLink_Obj * pObj, EncLink_ChQPParams * params);
Int32 EncLink_codecSetqpParamP(EncLink_Obj * pObj, EncLink_ChQPParams * params);
Int32 EncLink_codecForceDumpFrame(EncLink_Obj * pObj, EncLink_ChannelInfo * params);
Int32 EncLink_codecSetVBRDuration(EncLink_Obj * pObj, EncLink_ChCVBRDurationParams *params);
Int32 EncLink_codecSetVBRSensitivity(EncLink_Obj * pObj, EncLink_ChCVBRSensitivityParams *params);
Int32 EncLink_codecSetROIPrms(EncLink_Obj * pObj, EncLink_ChROIParams * params);
Int32 EncLink_codecSwitchCodec(EncLink_Obj * pObj, EncLink_ChSwitchCodecTypeParams * params);


Int32 EncLink_codecDisableChannel(EncLink_Obj * pObj,
                              EncLink_ChannelInfo* params);
Int32 EncLink_codecEnableChannel(EncLink_Obj * pObj,
                              EncLink_ChannelInfo* params);
Bool  EncLink_doSkipFrame(EncLink_ChObj *pChObj, Int32 chId);

Int32 Enclink_jpegEncodeFrame(EncLink_ChObj * pChObj,
                              EncLink_ReqObj * pReqObj);
Int32 EncLinkJPEG_algSetConfig(EncLink_algObj * algObj);
Int32 EncLinkJPEG_algGetConfig(EncLink_algObj * algObj);
Int EncLinkJPEG_algDynamicParamUpdate(EncLink_JPEGObj * hObj,
                               EncLink_AlgCreateParams * algCreateParams,
                               EncLink_AlgDynamicParams * algDynamicParams);

Int32 Enclink_H264EncodeFrame(EncLink_ChObj * pChObj,
                                   EncLink_ReqObj * reqObj);
Int32 EncLinkH264_algSetConfig(EncLink_algObj * algObj);
Int32 EncLinkH264_algGetConfig(EncLink_algObj * algObj);
Int EncLinkH264_algDynamicParamUpdate(EncLink_H264Obj * hObj,
                               EncLink_AlgCreateParams * algCreateParams,
                               EncLink_AlgDynamicParams * algDynamicParams);

Int32 EncLink_resetStatistics(EncLink_Obj * pObj);
Int32 EncLink_printStatistics (EncLink_Obj * pObj, Bool resetAfterPrint);
Int32 EncLink_printBufferStatus (EncLink_Obj * pObj);


#endif

/* Nothing beyond this point */

