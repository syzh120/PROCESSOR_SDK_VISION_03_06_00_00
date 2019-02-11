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
 * \ingroup CAPTURE_LINK_API
 * \defgroup CAPTURE_LINK_IMPL Capture Link Implementation
 *
 * @{
 */

 /**
 *******************************************************************************
 *
 * \file captureLink_priv.h Capture link private header file.
 *
 * \brief  This file is a private header file for capture link implementation.
 *
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of capture link.
 *
 *         Links and chains operate on channel number to identify the buffers
 *         from different sources and streams.
 *         Capture link needs to populate the channel number field in the
 *         system buffer which gets exchanged across links. This channel
 *         number is identification of stream. Each link produces frames with
 *         channel number starting from 0 till N-1 (where N is number of
 *         streams produced by link) Capture for example can produce upto
 *         12 streams, so each stream will have unique ID starting from 0 to
 *         N-1. Below shows the channel assignment in case capture is producing
 *         12 streams.
 *
 *         For single channel per port and single output per channel
 *
 *         Capture driver                          Output      Output Que
 *         channelNum                              QUE ID      channelNum
 *         0           CH0 VIP1 Slice 0 PortA          0           0
 *         1           CH0 VIP1 Slice 0 PortB          0           1
 *         2           CH0 VIP1 Slice 1 PortA          0           2
 *         3           CH0 VIP1 Slice 1 PortB          0           3
 *         4           CH0 VIP2 Slice 0 PortA          0           4
 *         5           CH0 VIP2 Slice 0 PortB          0           5
 *         6           CH0 VIP2 Slice 1 PortA          0           6
 *         7           CH0 VIP2 Slice 1 PortB          0           7
 *         8           CH0 VIP3 Slice 0 PortA          0           8
 *         9           CH0 VIP3 Slice 0 PortB          0           9
 *         10          CH0 VIP3 Slice 1 PortA          0           10
 *         11          CH0 VIP3 Slice 1 PortB          0           11
 *
 *
 * \version 0.0 (Jun 2013) : [HS] First version
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 * \version 0.2 (Jul 2014) : [VT] Add subframe support

 *******************************************************************************
 */

#ifndef CAPTURE_LINK_PRIV_H_
#define CAPTURE_LINK_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/captureLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max Number of capture link instances supported
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_OBJ_MAX                     (2U)

/**
 *******************************************************************************
 *
 * \brief Number of VBI lines
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_RAW_VBI_LINES       (40U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of output queues that capture link supports.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_MAX_OUT_QUE         (1U)

/**
 *******************************************************************************
 *
 * \brief Number of frames (buffers) allocated per channel of capture.
 *
 *        Capture driver requires 3 buffers in driver queue thats why we are
 *        queuing 5 frames for it. 2 will be used by display
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_FRAMES_PER_CH     (SYSTEM_LINK_FRAMES_PER_CH + 1U)

/**
 *******************************************************************************
 *
 * \brief Minimum number of frames (buffers) required for doing capture without
 *        dropping frames.
 *
 *        If application provides numBufs less than
 *        CAPTURE_LINK_MIN_FRAMES_PER_CH it will be overridden to
 *        CAPTURE_LINK_MIN_FRAMES_PER_CH
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_MIN_FRAMES_PER_CH  (4U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of frames getting allocated for capture link.
 *
 *        If application provides numBufs more than
 *        CAPTURE_LINK_MAX_FRAMES_PER_CH it will be overridden to
 *        CAPTURE_LINK_MAX_FRAMES_PER_CH
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */

#define CAPTURE_LINK_MAX_FRAMES_PER_CH     (SYSTEM_LINK_MAX_FRAMES_PER_CH)


/**
 *******************************************************************************
 *
 * \brief Maximum number of channels in a handle
 *
 *        Currently more than one channel per handle is not supported
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_MAX_CH_PER_HANDLE              (1U)

/**
 *******************************************************************************
 *
 * \brief Maximum streams of a channel in a handle
 *
 *        Currently more than two streams per handle is not supported
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_MAX_STREAMS_PER_HANDLE         (2U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of frames getting allocated for entire capture Link.
 *
 *        This is to allocate frame container statically, which will point to
 *        actual frames. Frames will be allocated based on application requests
 *        but frame containers are always allocated at init time that is max
 *        of frames possible.
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_MAX_FRAMES_PER_HANDLE \
    (CAPTURE_LINK_MAX_STREAMS_PER_HANDLE* \
     CAPTURE_LINK_MAX_CH_PER_HANDLE* \
      SYSTEM_LINK_MAX_FRAMES_PER_CH \
    )

/**
 *******************************************************************************
 *
 * \brief Number of Slices to be allocated per circular buffer
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_NUM_SUBFRAME_PER_CBUF          (2U)


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 * \brief Forward declaration of capture object.
 *
 *******************************************************************************
 */

typedef struct CaptureLink_Obj_t CaptureLink_Obj;


/**
 *******************************************************************************
 *
 *  \brief  Structure containing information for each instance of capture
 *          driver link operates on.
 *
 *******************************************************************************
*/
typedef struct {

    UInt32 instId;
    /**< Caputre driver instance ID */

    Vps_CaptCreateParams createArgs;
    /**< Capture driver create parameters */

    Vps_CaptCreateStatus createStatus;
    /**< Capture driver status params while creating capture driver */

    Vps_CaptVipParams    vipPrms;
    /**< VIP parameters for capture driver */

    Vps_VipPortConfig    vipPortCfg;
    /** Port configuration for VIP */

    Vps_CaptVipScParams  scPrms;
    /**< Capture driver scalar configuration */

    Vps_CaptDssWbParams dssWbPrms;
    /**< DSS WB Capture driver configuration */

    FVID2_CbParams cbPrm;
    /**< Callback parameters for capture driver */

    FVID2_Handle captureVipHandle;
    /**< Place holder for handle returned by capture driver */

    FVID2_Frame frames[CAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< FVID2_Frames to handle the capture buffers */

    System_Buffer buffers[CAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[CAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Payload for System buffers */

    UInt32 numBufs;
    /**< Number of buffers allocated for this instance */

    UInt32  bufferWidth;
    /**< Width of the buffers allocated */

    UInt32 bufferHeight[SYSTEM_MAX_PLANES];
    /**< Height of buffers allocated. Height may be different for different
     *   planes for semi planer data   */

    CaptureLink_Obj *parent;
    /**< Holder for Capture link object. This is to get the captureLink object
     *   from Instance object. */

    Bool isSubframeEnabled;
    /**< Flag to indicate if sub-frame capture mode is enabled */

    UInt8 *bufBaseAddr[CAPTURE_LINK_MAX_STREAMS_PER_HANDLE]
                [CAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Base address of buffer for this instance and this stream */

    UInt32 bufSize[CAPTURE_LINK_MAX_STREAMS_PER_HANDLE]
                [CAPTURE_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Total buffer size for this instance and this stream */

    UInt32 frameId;
    /**< Incrementing counter giving id to the dequeued frame */
} CaptureLink_InstObj;


/**
 *******************************************************************************
 *
 *  \brief  Structure containing Link object information
 *
 *
 *******************************************************************************
 */
struct CaptureLink_Obj_t
{
    UInt32 linkId;
    /**< Link ID for this object */

    Utils_TskHndl tsk;
    /**< Handle to capture link task */

    CaptureLink_CreateParams createArgs;
    /**< Create params for capture link */

    Utils_BufHndl bufQue;
    /**< Handle to buffer queue */

    FVID2_Handle fvidHandleVipAll;
    /**< Global handle for capture driver */

    CaptureLink_InstObj instObj[SYSTEM_CAPTURE_VIP_INST_MAX +
                                SYSTEM_CAPTURE_DSSWB_INST_MAX];
    /**< Array of capture link instance objects. Fields specific to instance */

    System_LinkInfo info;
    /**< Capture link information */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by capture link */

    UInt32  chToInstMap[CAPTURE_LINK_MAX_CH_PER_OUT_QUE];
    /**< Channel to instance map. Which channel is mapped to which instance
     * of capture driver  */

    UInt32 mapInstId[64];
    /**< Array to map the instId, increased as DSS WB ID is 33 */

    #if 0
    Utils_LinkStatistics    linkStats;
    /**< links statistics like frames captured, dropped etc */
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

    UInt32  statsStartTime;
    /**< Time at which capture is started */

    UInt32 fvid2DrvChNumOffset;
    /**< Offset to add to CH Num given to FVID2 driver to make CH Num unique across all capture link instances */

};



Int32 CaptureLink_getInfo(Void * ptr, System_LinkInfo * info);
Int32 CaptureLink_getFullBuffers(Void * ptr, UInt16 queId,
                                 System_BufferList * pBufList);
Int32 CaptureLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                                  System_BufferList * pBufList);

Int32 CaptureLink_drvCreate(CaptureLink_Obj * pObj,
                            const CaptureLink_CreateParams * pPrm);

Int32 CaptureLink_drvStart(CaptureLink_Obj * pObj);
Int32 CaptureLink_drvProcessData(CaptureLink_Obj * pObj, UInt32 instId);
Int32 CaptureLink_drvStop(CaptureLink_Obj * pObj);
Int32 CaptureLink_drvDelete(CaptureLink_Obj * pObj);
Int32 CaptureLink_drvAllocAndQueueFrames(CaptureLink_Obj * pObj,
                                         CaptureLink_InstObj * pDrvObj);
Int32 CaptureLink_drvFreeFrames(const CaptureLink_Obj * pObj,
                                CaptureLink_InstObj * pDrvObj);

UInt32 CaptureLink_drvIsDataFormatTiled(CaptureLink_InstObj * pDrvObj,
                                        UInt16 streamId);

Int32 CaptureLink_drvPutEmptyBuffers(CaptureLink_Obj * pObj,
                                    const System_BufferList * pBufList);

Int32 CaptureLink_drvPrintStatus(CaptureLink_Obj * pObj);

Int32 CaptureLink_printBufferStatus(CaptureLink_Obj * pObj);

Int32 CaptureLink_drvAllocAndQueueExtraFrames(CaptureLink_Obj * pObj,
                                              UInt32 instId, UInt32 streamId,
                                              UInt32 chId);
Int32 CaptureLink_drvFreeExtraFrames(CaptureLink_Obj * pObj);

Int32 CaptureLink_drvSetScParams(CaptureLink_Obj * pObj,
                                 CaptureLink_ScParams *pPrm);

Void CaptureLink_printDetailedStatistics(
                                CaptureLink_Obj * pObj,
                                 UInt32       execTime);

Int32 CaptureLink_subframe_drvGetVIPOutFrameInfo
                                (CaptureLink_Obj * pObj,
                                CaptureLink_Subframe_Info *pCaptureLinkSubframeInfo);

Int32 CaptureLink_subframe_drvAllocAndQueueFrames
                        (CaptureLink_Obj * pObj, CaptureLink_InstObj * pDrvObj);

Int32 CaptureLink_subframe_drvFreeFrames(CaptureLink_Obj * pObj,
                                                CaptureLink_InstObj * pDrvObj);

void CaptureLink_dispWbCreateInst(CaptureLink_Obj * pObj, UInt16 instId);

Int32 CaptureLink_drvCallback(FVID2_Handle handle, Ptr appData, Ptr reserved);

Int32 CaptureLink_drvUpdateFrmSkip(CaptureLink_Obj * pObj, UInt32 frmSkipInp);

#endif

/* @} */
