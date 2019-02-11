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
 * \ingroup VPE_LINK_API
 * \defgroup VPE_LINK_IMPL VPE Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file vpeLink_priv.h VPE Link private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - VPE link instance/handle object
 *         - All the local data structures
 *         - VPE BSP driver interfaces
 *
 * \version 0.0 (Sept 2013) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef VPE_LINK_PRIV_H_
#define VPE_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/vpeLink.h>

#include <ti/drv/vps/include/vpe/vps_m2m.h>

#include <ti/drv/vps/include/vpe/vps_m2mVpe.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max Number of VPE link instances supported
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_LINK_OBJ_MAX                     (4U)

/**
 *******************************************************************************
 *
 *   \brief Define the Max Number of output buffers per channel of VPE link
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_LINK_MAX_OUT_FRAMES_PER_CH       (10U)

#define VPE_MAX_DROP_BUFFER_WIDTH            (1920U)
#define VPE_MAX_DROP_BUFFER_HEIGHT           (1080U)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the VPE link Output object
 *
 *          This includes the output side
 *          - Queues
 *          - System buffers
 *          - FVID2 frames
 *
 *******************************************************************************
*/
typedef struct {
    Utils_BufHndl bufOutQue;
    /**< Output buffer queue */
    FVID2_Frame frames[VPE_LINK_MAX_CH][VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< FVID2_Frames to handle the output buffers */
    System_Buffer buffers[VPE_LINK_MAX_CH][VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< System buffer data structure to exchange buffers between links */
    System_VideoFrameBuffer videoFrames[VPE_LINK_MAX_CH][VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< Payload for System buffers */
    UInt32 numFrames[VPE_LINK_MAX_CH];
    /**< Number of output buffers per channel */
    Utils_QueHandle emptyBufQue[VPE_LINK_MAX_CH];
    /**< VPE link output side empty buffer queue */
    System_Buffer *bufsMem[VPE_LINK_MAX_CH][VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /** Holds individual channel empty buffers */
    UInt8 *bufBaseAddr[VPE_LINK_MAX_CH][VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< Base address of buffer for this output and this CH */
    UInt32 bufSize[VPE_LINK_MAX_CH][VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< Total buffer size for this for this output and this CH */

} VpeLink_OutObj;

/**
 *******************************************************************************
 *
 *   \brief Data Structure for the VPE link Input side object
 *
 *          This includes the Input side FVID2 free Queues
 *          and the FVID2 frames
 *
 *******************************************************************************
*/
typedef struct {
    Utils_QueHandle fvidFrameQueue;
    /**< Free FVID2 Frames queue for mapping system buffers from input queue */
    FVID2_Frame frames[VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< FVID2 Frames to interface with the VPE driver */
    FVID2_Frame *fvidFrameQueueMem[VPE_LINK_MAX_OUT_FRAMES_PER_CH];
    /**< FVID2 Frames Queue Mem */
} VpeLink_InObj;

/**
 *******************************************************************************
 *
 *   \brief VPE link Channel specific instance object
 *
 *          This structure contains
 *          - All the channel specific local data structures
 *          - VPS/BSP Data structures required for VPE BSP driver interfaces
 *          - All fields to support the CH vise stats and status information
 *
 *******************************************************************************
*/
typedef struct {
    Bool enableOut[VPE_LINK_OUT_QUE_ID_MAX];
    /**< Output Queue enable/disable flag */
    Utils_BufHndl inQue;
    /**< CH specific intermediate Queue */
    UInt32 nextFid;
    /**< Expected FID info for the next field */
    FVID2_Format outFormat[VPE_LINK_OUT_QUE_ID_MAX];
    /**< Structure to hold the output buffer format,
     *   such as width, height, pitch, data format, scan format etc */
    Vps_ScConfig scCfg[VPE_LINK_OUT_QUE_ID_MAX];
    /**< Structure to hold the scalar config parameters */
    Fvid2_CropConfig scCropCfg[VPE_LINK_OUT_QUE_ID_MAX];
    /**< Structure to hold the scalar crop config parameters */
    Vps_DeiRtConfig deiRtCfg;
    /**< Structure to hold the VPE DEI RT parameters */
    Vps_M2mVpeRtParams vpeRtPrm;
    /**< Data structure used for VPE RT parameters update */
    Vps_FrameParams vpeInFrmPrms;
    /**< Structure to hold the VPE input frame RT parameters */
    Vps_FrameParams vpeRtOutFrmPrm[VPE_LINK_OUT_QUE_ID_MAX];
    /**< Structure to hold the VPE output frame RT parameters */
    Bool chRtOutInfoUpdate[VPE_LINK_OUT_QUE_ID_MAX];
    /**< flag is check the RT param update */
    Bool chRtEnableOutQFlag;
    /**< Flag is check alternative/fid vise output QueueID update */
    UInt32 chRtOutInfoUpdateWhileDrop;
    /**< Queue ID to check whether RT update required while frame drop */

    Utils_BufSkipContext frameSkipCtx [VPE_LINK_OUT_QUE_ID_MAX];
    /**< Data structure for frame skip to achieve expected output frame rate */

    FVID2_Frame *pInFrameN_1;
    /**< Previous (N-1th) FVID2 frame,
      *  used only while useOverridePrevFldBuf = TRUE */
    FVID2_Frame *pInFrameN_2;
    /**< Previous (N-2th) FVID2 frame,
      *  used only while useOverridePrevFldBuf = TRUE */
    VpeLink_InObj inObj;
    /**< VPE link Input side object, for FVID2 freeQ and frame */
} VpeLink_ChObj;

/**
 *******************************************************************************
 *
 *   \brief Data Structure for VPE request object,
 *          This is for the Link internal, and is the object hold all the
 *          required informations to invoking the BSP driver processing call
 *
 *******************************************************************************
*/
typedef struct {
    FVID2_ProcessList processList;
    /**< FVID2 process list - BSP data structure, hold the in/out frame lists */
    FVID2_FrameList inFrameList;
    /**< Input frame list, to hold the input frames */
    FVID2_FrameList outFrameList;
    /**< Output frame list, to hold the output frames */
    UInt32 outListQueIdMap[VPE_LINK_MAX_CH];
    /**< Data structure to store the output ID for each output frames */
    Vps_M2mVpeOverridePrevFldBuf prevFldBuf;
    /**< Data structure to hold the previous field buffer,
      *  used only while useOverridePrevFldBuf = TRUE */
    FVID2_FrameList inFrameListN;
    /**< Frame list to hold the previous (Nth) field buffers,
      *  used only while useOverridePrevFldBuf = TRUE */
    FVID2_FrameList inFrameListN_1;
    /**< Frame list to hold the previous (N-1th) field buffers,
      *  used only while useOverridePrevFldBuf = TRUE */
    FVID2_FrameList inFrameListN_2;
    /**< Frame list to hold the previous (N-2th) field buffers,
      *  used only while useOverridePrevFldBuf = TRUE */
} VpeLink_ReqObj;

/**
 *******************************************************************************
 *
 *   \brief VPE link instance object
 *
 *          This structure contains
 *          - All the local data structures
 *          - VPS/BSP Data structures required for VPE BSP driver interfaces
 *          - All fields to support the Link stats and status information
 *
 *******************************************************************************
*/
typedef struct {
    UInt32 linkId;
    /**< placeholder to store the link task Id */
    char name[32];
    /**< Link name */
    Utils_TskHndl tsk;
    /**< placeholder to store the link task handler */
    VpeLink_CreateParams createArgs;
    /**< VPE link create time parameters */
    System_LinkInfo inTskInfo;
    /**< Specifies a place holder that describe the LINK information */
    System_LinkQueInfo inQueInfo;
    /**< Input Q channel specific info, read from the outQ of previous LINK */
    VpeLink_ReqObj reqObj;
    /**< Link internal data structure, object hold all the required
     *   informations to invoking the BSP driver processing call */
    VpeLink_OutObj outObj[VPE_LINK_OUT_QUE_ID_MAX];
    /**<  Data Structure to hold the VPE link Output object*/
    System_LinkInfo info;
    /**< VPE link output queue info, the next link query & use this info */
    UInt32 isStopSupported;
    /**< Flag to indicate if FVID2_Stop is supported or not */
    Vps_M2mVpeParams drvChArgs[VPE_LINK_MAX_CH];
    /**< VPS driver channel vise create time parameters */
    Vps_M2mCreateParams drvCreateArgs;
    /**< VPS driver create parameters */
    Vps_M2mCreateStatus drvCreateStatus;
    /**< VPS driver create status */
    FVID2_Handle fvidHandle;
    /**< VPE/ISS driver instance - FVID2 driver handle */
    FVID2_ProcessList errProcessList;
    /**< VPS error process list */
    VpeLink_ChObj chObj[VPE_LINK_MAX_CH];
    /**< VPE link channel specific Object */
    UInt32 drvInstId;
    /**< VPE driver instance ID */
    FVID2_Frame inFrame;
    /**< FVID2 frame - VPE link input side common frame */
    FVID2_Frame outFrameDrop;
    /**< FVID2 frame - VPE link output side common frame,
     *   used while when output side frame drop */
    BspOsal_SemHandle complete;
    /**< Semaphore for the VPE process complete */
    UInt32 givenInFrames;
    /**< Number of frames given to the driver */
    UInt32 returnedInFrames;
    /**< Number of frames returned by the driver, This is required because
     *   Even though all the requests are addressed, the driver would have held
     *   back couple of input fields as context fields, use this to get them */
    Bool loadUpsampleCoeffs;
    /**< Flag to load the up scaling coefficients */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Used to log the memory usage of the VPE link */
    UInt32 useOverridePrevFldBuf;
    /**< flag to enable "override previous field buf" mode
     *   Currently set to FALSE inside the Link and not exposed as LINK API */

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

    UInt32  isAllocDropBuffer;
    /**< Flag to inform the link to allocate dummy buffer for dropped frame
         Used only for VPE on TDA2xx.*/
} VpeLink_Obj;

/*******************************************************************************
 *  VPE Link Private Functions
 *******************************************************************************
 */
Int32 VpeLink_getLinkInfo(Void * pTsk, System_LinkInfo * info);
Int32 VpeLink_getFullBuffers(Void * ptr, UInt16 queId,
                             System_BufferList * pBufList);
Int32 VpeLink_putEmptyBuffers(Void * ptr, UInt16 queId,
                              System_BufferList * pBufList);
Int32 VpeLink_drvCreate(VpeLink_Obj * pObj,const VpeLink_CreateParams * pPrm);
Int32 VpeLink_drvProcessData(VpeLink_Obj * pObj);
Int32 VpeLink_drvGetProcessedData(VpeLink_Obj * pObj);
Int32 VpeLink_drvStop(VpeLink_Obj * pObj);
Int32 VpeLink_drvDelete(VpeLink_Obj * pObj);
Int32 VpeLink_drvSetChannelInfo(VpeLink_Obj * pObj,const VpeLink_ChannelInfo *channelInfo);
Int32 VpeLink_drvSetFrameRate(VpeLink_Obj * pObj,const VpeLink_ChFpsParams * params);
Int32 VpeLink_printStatistics (const VpeLink_Obj *pObj, Bool resetAfterPrint);
Int32 VpeLink_printBufferStatus(VpeLink_Obj * pObj);
Int32 VpeLink_drvSetChDynamicOutputRes(VpeLink_Obj * pObj,
                                       const VpeLink_ChDynamicSetOutRes * params);
Int32 VpeLink_drvGetChDynamicOutputRes(VpeLink_Obj * pObj,
                                       VpeLink_ChDynamicSetOutRes * params);
Int32 VpeLink_drvCreateChObj(VpeLink_Obj * pObj, UInt32 chId);
Int32 VpeLink_drvCreateFvidObj(VpeLink_Obj * pObj);
Int32 VpeLink_drvAllocCtxMem(VpeLink_Obj * pObj);
Int32 VpeLink_drvSetScCoeffs(VpeLink_Obj * pObj);
Int32 VpeLink_drvUpdateScCropPrm(VpeLink_Obj * pObj, UInt32 chId,
                                 Bool rtPrmUpdate);
Int32 VpeLink_drvFreeCtxMem(VpeLink_Obj * pObj);
static Int32 VpeLink_drvReleaseContextField(VpeLink_Obj * pObj);
Void VpeLink_drvCreateFvidFrameQueue(VpeLink_Obj *pObj, UInt32 chId);
Int32 VpeLink_drvFvidCb(FVID2_Handle handle, Ptr appData, Ptr reserved);
Int32 VpeLink_drvFvidErrCb(FVID2_Handle handle,
                           Ptr appData, Ptr errList, Ptr reserved);
Int32 VpeLink_drvUpdateInputRtPrm(VpeLink_Obj * pObj,
                                 FVID2_Frame *pInFrame, UInt32 chId);
Int32 VpeLink_drvReleaseFrames(VpeLink_Obj * pObj,
                               const FVID2_FrameList * inFrameList,
                               const FVID2_FrameList * outFrameList);
Int32 VpeLink_drvQueueFramesToChQue(VpeLink_Obj * pObj);
void VpeLink_drvFreeFvidFrames(VpeLink_Obj *pObj,
                               const FVID2_FrameList *freeFrameList);
Int32 VpeLink_drvSetFmdCfg(VpeLink_Obj * pObj, UInt16 fmdEnable);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
