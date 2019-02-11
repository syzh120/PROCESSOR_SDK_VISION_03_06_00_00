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
 * \file decLink_priv.h Decode Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Decode link instance/handle object
 *         - All the local data structures
 *         - Codec interfaces
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _DEC_LINK_PRIV_H_
#define _DEC_LINK_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/gates/GateMutexPri.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include <include/link_api/decLink.h>
#include <include/link_api/system_debug.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec_prf.h>
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include "decLink_err.h"
#include "decLink_algIf.h"
#include "decLink_jpeg_priv.h"
#include "decLink_h264_priv.h"
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_buf_ext.h>


/**
 *******************************************************************************
 *
 *   \brief Link CMD: Dec command to open a new channel
 *          Application can use this command to create/open
 *          an alreday excisting channel
 *
 *   SUPPORTED platforms - Not validated this as of today
 *
 *   \param DecLink_CreateChannelInfo *pPrm [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DEC_LINK_CMD_CREATE_CHANNEL          (0x200A)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Dec command to close channel
 *          Application can use this command to delete/close
 *          an alreday created/opened channel
 *
 *   SUPPORTED platforms - Not validated this as of today
 *
 *   \param DecLink_ChannelInfo *pPrm [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DEC_LINK_CMD_DELETE_CHANNEL          (0x200B)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Dec command to set trick play configuration
 *          Application can use this Dec command to set trick play configuration
 *
 *   SUPPORTED platforms - Not validated this as of today
 *
 *   \param DecLink_TPlayConfig *pPrm [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DEC_LINK_CMD_SET_TRICKPLAYCONFIG     (0x200C)

/**
 *******************************************************************************
 *   DecLink defines
 *
 *******************************************************************************
 */
#define DEC_LINK_OBJ_MAX                     (1)

#define DEC_LINK_MAX_OUT_FRAMES_PER_CH       (SYSTEM_LINK_FRAMES_PER_CH)

#define DEC_LINK_MAX_OUT_FRAMES              (DEC_LINK_MAX_CH*DEC_LINK_MAX_OUT_FRAMES_PER_CH)

#define DEC_LINK_CMD_GET_PROCESSED_DATA      (0x6000)

#define DEC_LINK_CMD_LATE_ACK                (0x6001)

#define DEC_LINK_MAX_REQ                     (DEC_LINK_MAX_OUT_FRAMES)

#define DEC_LINK_MAX_REQ_OBJ_DUMMY           (DEC_LINK_MAX_CH * 2)

#define DEC_LINK_PROCESS_TSK_SIZE            (8 * KB)

#define DEC_LINK_MAX_TASK_NAME_SIZE          (32)

#define DEC_LINK_TASK_POLL_DURATION_MS       (8)

#define DEC_LINK_STATS_START_THRESHOLD       (5)

#define DEC_LINK_REQLIST_MAX_REQOBJS         (4)

#define DEC_LINK_MAX_DUP_PER_FRAME           (4)

#define DEC_LINK_MAX_DUP_FRAMES              (DEC_LINK_MAX_OUT_FRAMES)

#define DEC_LINK_FRAMESKIP_DUE2ACCUM_THRESHOLD                 (2)

#define DEC_LINK_DEFAULT_ALGPARAMS_TARGETBITRATE               (2 * 1000 * 1000)
#define DEC_LINK_DEFAULT_ALGPARAMS_TARGETFRAMERATE                          (30)
#define DEC_LINK_DEFAULT_ALGPARAMS_DECODEHEADER                  (XDM_DECODE_AU)
#define DEC_LINK_DEFAULT_ALGPARAMS_FRAMESKIPMODE                (IVIDEO_NO_SKIP)
#define DEC_LINK_DEFAULT_ALGPARAMS_NEWFRAMEFLAG                      (XDAS_TRUE)
#define DEC_LINK_DEFAULT_ALGPARAMS_DISPLAYWIDTH                              (0)
#define DEC_LINK_DEFAULT_ALGPARAMS_DISPLAYDELAY       (IVIDDEC3_DECODE_ORDER)
//#define DEC_LINK_DEFAULT_ALGPARAMS_DISPLAYDELAY    (IVIDDEC3_DISPLAY_DELAY_2)

/**
 *******************************************************************************
 *   DecLink request object types
 *
 *******************************************************************************
 */
typedef enum DecLink_ReqObjType_e
{
    DEC_LINK_REQ_OBJECT_TYPE_REGULAR,
    DEC_LINK_REQ_OBJECT_TYPE_DUMMY_CHDELETE,
    DEC_LINK_REQ_OBJECT_TYPE_DUMMY_FLUSHFRAME
} DecLink_ReqObjType_e;

/**
 *******************************************************************************
 *
 *   \brief Dec link channel craete ChannelInfo params
 *
 *          Defines the complete set of parameters that can be
 *          required for dynamically add/create/open a new channel
 *          to the excisting decode link
 *
 *******************************************************************************
 */
typedef struct DecLink_CreateChannelInfo
{
    UInt32 chId;
    /**< chId of the new channel */
    System_LinkChInfo   chInfo;
    /**< channel specific link configuration parameters */
    DecLink_ChCreateParams createPrm;
    /**< channel specific create time paramters */
} DecLink_CreateChannelInfo;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Decode link trickplay configure parameters
 *
 *          Defines those parameters that can be configured/set
 *          during dec link per channel vise Trickplay mode
 *
 *******************************************************************************
 */
typedef struct DecLink_TPlayConfig
{
    UInt32 chId;
    /**< Decoder channel number */
    UInt32 inputFps;
    /**< FrameRate at which Decoder is getting the data */
    UInt32 targetFps;
    /**< Target FrameRate for TrickPlay. TrickPlay will generate
         target frame rate from the input framerate */
} DecLink_TPlayConfig;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link Output channel Object
 *
 *******************************************************************************
 */
typedef struct DecLink_OutChObj {
    UInt32 outNumFrames;
    FVID2_Format outFormat;
    EncDec_ResolutionClass reslutionClass;
    System_Buffer outFramesPool[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH*2];
    System_VideoFrameBuffer videoFrames[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH*2];
    Utils_EncDecLinkPvtInfo linkPvtInfo[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH*2];
    Utils_QueHandle outFrameQue;
    System_Buffer *outFrameQueMem[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH*2];
    System_Buffer *outFrames[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH];
    System_Buffer allocFrames[DEC_LINK_MAX_NUM_OUT_BUF_PER_CH];
    /**< Payload for System buffers */
} DecLink_OutChObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link Output queue Object
 *
 *******************************************************************************
 */
typedef struct DecLink_OutObj {
    UInt32 totalNumOutBufs;
    Utils_BufHndlExt bufOutQue;
    DecLink_OutChObj outChObj[DEC_LINK_MAX_CH];
} DecLink_OutObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link internal request queue Object
 *
 *******************************************************************************
 */
typedef struct {
    System_Buffer *InBuf;
    System_BufferList OutFrameList;
    DecLink_ReqObjType_e type;
} DecLink_ReqObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link request queue list
 *
 *******************************************************************************
 */
typedef struct DecLink_ReqList {
    UInt32 numReqObj;
    DecLink_ReqObj *reqObj[DEC_LINK_REQLIST_MAX_REQOBJS];
} DecLink_ReqList;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link Alg/Codec object
 *
 *******************************************************************************
 */
typedef struct DecLink_algObj {
    union {
        DecLink_JPEGObj jpegAlgIfObj;
        DecLink_H264Obj h264AlgIfObj;
    } u;
    DecLink_AlgCreateParams algCreateParams;
    DecLink_AlgDynamicParams algDynamicParams;
    System_Buffer *prevOutFrame;
    IRES_ResourceDescriptor resDesc[DEC_LINK_MAX_NUM_RESOURCE_DESCRIPTOR];
} DecLink_algObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link T-play channel Object
 *
 *******************************************************************************
 */
typedef struct DecLink_TrickPlayObj {
    Bool skipFrame;
    /* Data structure for frame skip to achieve expected output frame rate */
    Utils_BufSkipContext frameSkipCtx;
} DecLink_TrickPlayObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link channel Object
 *
 *******************************************************************************
 */
typedef struct DecLink_ChObj {
    Utils_QueHandle inQue;
    DecLink_algObj algObj;
    Bool IFrameOnlyDecode;
    Bool disableChn;
    Bool skipFrame;
    UInt32 allocPoolID;
    UInt32 processReqestCount;
    UInt32 getProcessDoneCount;
    UInt32 numBufsInCodec;
    UInt32 algCreateStatusLocal;
    System_Buffer *inBitBufMem[DEC_LINK_MAX_REQ];
    System_Buffer dummyBitBuf;
    DecLink_TrickPlayObj trickPlayObj;
    Bool isFirstIDRFrameFound;
    Bool skipFrameDue2AccumuInNextLink;
} DecLink_ChObj;

/**
 *******************************************************************************
 *   \brief Structure defines the Decode link Dup Object
 *
 *******************************************************************************
 */
typedef struct DecLink_DupObj {
    Utils_QueHandle dupQue;
    System_Buffer *dupQueMem[DEC_LINK_MAX_DUP_FRAMES];
    System_Buffer dupFrameMem[DEC_LINK_MAX_DUP_FRAMES];
    Utils_EncDecLinkPvtInfo linkPvtInfo[DEC_LINK_MAX_DUP_FRAMES];
} DecLink_DupObj;

/**
 *******************************************************************************
 *   \brief Structure defines the top level Decode link Object
 *
 *******************************************************************************
 */
typedef struct DecLink_Obj {
    UInt32 linkId;
    char name[32];
    Utils_TskHndl tsk;
    System_LinkInfo inTskInfo;
    System_LinkQueInfo inQueInfo;
    DecLink_OutObj outObj;
    struct decDummyReqObj_s {
        DecLink_ReqObj reqObjDummy[DEC_LINK_MAX_REQ_OBJ_DUMMY];
        Utils_QueHandle reqQueDummy;
        DecLink_ReqObj *reqQueMemDummy[DEC_LINK_MAX_REQ_OBJ_DUMMY];
    } decDummyReqObj;
    DecLink_ReqObj reqObj[DEC_LINK_MAX_REQ];
    Utils_QueHandle reqQue;
    DecLink_ReqObj *reqQueMem[DEC_LINK_MAX_REQ];
    volatile Utils_EncDec_LinkState state;
    Bool isReqPend;
    System_LinkInfo info;
    DecLink_ChObj chObj[DEC_LINK_MAX_CH];
    DecLink_CreateParams createArgs;
    DecLink_DupObj dupObj;
    Utils_QueHandle processDoneQue;
    DecLink_ReqObj *processDoneQueMem[DEC_LINK_MAX_OUT_FRAMES];
    struct decProcessTsk_s {
        BspOsal_TaskHandle tsk;
        char name[DEC_LINK_MAX_TASK_NAME_SIZE];
        Utils_QueHandle processQue;
        DecLink_ReqObj *processQueMem[DEC_LINK_MAX_OUT_FRAMES];
    } decProcessTsk[NUM_HDVICP_RESOURCES];
    Bool newDataProcessOnFrameFree;

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
} DecLink_Obj;

/*******************************************************************************
 *  Decode Link Private Functions
 *******************************************************************************
 */
Int32 DecLink_getInfo(Void * pTsk, System_LinkInfo * info);
Int32 DecLink_getFullFrames(Void * ptr, UInt16 queId,
                            System_BufferList * pBufList);
Int32 DecLink_putEmptyFrames(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList);

Int32 DecLink_codecCreate(DecLink_Obj * pObj, DecLink_CreateParams * pPrm);
Int32 DecLink_codecProcessData(DecLink_Obj * pObj);
Int32 DecLink_codecGetProcessedDataMsgHandler(DecLink_Obj * pObj);
Int32 DecLink_codecStop(DecLink_Obj * pObj);
Int32 DecLink_codecDelete(DecLink_Obj * pObj);
Int32 DecLink_codecDisableChannel(DecLink_Obj * pObj,
                              DecLink_ChannelInfo* params);
Int32 DecLink_codecEnableChannel(DecLink_Obj * pObj,
                              DecLink_ChannelInfo* params);
Int32 DecLink_setTPlayConfig(DecLink_Obj * pObj,
                              DecLink_TPlayConfig* params);
Int32 DecLink_getCurLinkID(Void * key);
Int32 DecLink_codecGetProcessedDataMsgHandler(DecLink_Obj * pObj);
Int32 DecLink_codecFreeProcessedFrames(DecLink_Obj * pObj,
                                       System_BufferList * freeFrameList);

Int32 Declink_jpegDecodeFrame(DecLink_Obj * pObj,
                              DecLink_ReqObj * pReqObj,
                              System_BufferList * freeFrameList);
Int32 Declink_h264DecodeFrame(DecLink_Obj * pObj,
                              DecLink_ReqObj * pReqObj,
                              System_BufferList * freeFrameList);

Int32 DecLinkH264_codecFlush(DecLink_ChObj *pChObj,
                             IH264VDEC_InArgs *inArgs,
                             IH264VDEC_OutArgs *outArgs,
                             XDM2_BufDesc *inputBufDesc,
                             XDM2_BufDesc *outputBufDesc,
                             IH264VDEC_Handle handle,
                             System_BufferList *freeFrameList,
                             Bool hardFlush);

Int32 DecLink_printStatistics (DecLink_Obj * pObj, Bool resetAfterPrint);
Int32 DecLink_resetStatistics(DecLink_Obj * pObj);
Int32 DecLink_printBufferStatus (DecLink_Obj * pObj);
Int32 DecLink_codecCreateChannelHandler(DecLink_Obj * pObj,
                                        DecLink_CreateChannelInfo* params);
Int32 DecLink_codecDeleteChannelHandler(DecLink_Obj * pObj,
                                        DecLink_ChannelInfo* params);
Int32 DecLink_getBufferStatus (DecLink_Obj * pObj,DecLink_BufferStats *bufStats);

#endif

/* Nothing beyond this point */


