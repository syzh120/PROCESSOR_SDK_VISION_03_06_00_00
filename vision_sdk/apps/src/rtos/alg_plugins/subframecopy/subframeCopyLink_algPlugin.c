/******************************************************************************
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
******************************************************************************/

 /**
 *******************************************************************************
 * \file subframeCopyLink_algPlugin.c
 *
 * \brief Algorithm for subframe copy on EVE
 *
 *        This algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *        It registers interrupts on VIP to recieve frame and subframe complete
 *        events. This algorithm  then does a frame copy, one subframe ar a time
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "subframeCopyLink_priv.h"
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopy_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = ALGORITHM_LINK_EVE_ALG_SUBFRAMECOPY;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_SubframeCopyCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_SubframeCopyProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_SubframeCopyControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_SubframeCopyStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_SubframeCopyDelete;

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Callback function triggerred from ISR when frame is completed.
 *
 * \param
 *
 * \return  void, as its called from context of ISR
 *
 *******************************************************************************
 */
static void AlgorithmLink_SubframeCopyFrameCompleteCallback
                            (AlgorithmLink_SubframeCopyObj *pSubframeCopyObj)
{
    Int32 status;
    UInt32 cmdType;

    if(!pSubframeCopyObj->isFirstSubFrameRecv)
    {
        /* Initially some  dummy frame complete ISRs are triggerred which
        * need to be ignored till avalid subframe is recieved
        */
        return;
    }

    /*
    * Store a frame complete entry in new data command queue
    * The entries in the command queue are processed in
    * AlgorithmLink_SubframeCopyProcess call in task context
    */
    cmdType = SUBFRAME_ALGLINK_NEWDATA_IS_FRAME;
    status = Utils_quePut(&pSubframeCopyObj->newDataCmdQ,
                        (Ptr)cmdType, BSP_OSAL_NO_WAIT);
    /*
    * Asserting since this queue overflowing means data processing rate is slow
    * which will cause cbuf data to be overwritten and hence corruption of
    * output frame.
    */
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Send new data command to the alg plugin task
    Utils_tskSendCmd(pSubframeCopyObj->ptsk, SYSTEM_CMD_NEW_DATA, NULL);

    return;
}

/**
 *******************************************************************************
 *
 * \brief Callback function triggerred from ISR when subframe is recieved.
 *
 * \param
 *
 * \return  void, as its called from context of ISR
 *
 *******************************************************************************
 */
static void AlgorithmLink_SubframeCopySubFrameCallback
                            (AlgorithmLink_SubframeCopyObj *pSubframeCopyObj)
{
    Int32 status;
    UInt32 cmdType;

    if(!pSubframeCopyObj->isFirstSubFrameRecv)
    {
        /*
        * First subframe is recieved.Till first subframe is recieved the dummy
        * frame complete events need to be ignored
        */
        pSubframeCopyObj->isFirstSubFrameRecv = TRUE;
    }

    /*
    * Store a subframe complete entry in new data command queue
    * The entries in the command queue are processed in
    * AlgorithmLink_SubframeCopyProcess call in task context
    */
    cmdType = SUBFRAME_ALGLINK_NEWDATA_IS_SUBFRAME;
    status = Utils_quePut(&pSubframeCopyObj->newDataCmdQ,
                        (Ptr)cmdType, BSP_OSAL_NO_WAIT);

    /*
    * Asserting since this queue overflowing means data processing rate is slow
    * which will cause cbuf data to be overwritten and hence corruption of
    * output frame.
    */
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Send new data command to the alg plugin task
    Utils_tskSendCmd(pSubframeCopyObj->ptsk, SYSTEM_CMD_NEW_DATA, NULL);

    return;
}

/**
 *******************************************************************************
 *
 * \brief ISR function, registered with VIP.
 *
 * It detects a frame or subframe complete event and triggers appropriate
 * callback functions.
 *
 *******************************************************************************
 */
void AlgorithmLink_SubframeCopyVip_Isr_Func (void *pPtr)
{
    AlgorithmLink_SubframeCopyObj *pSubframeCopyObj;
    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)pPtr;

    //If frame is completed
    if(Utils_VIP_Interrupt_IsFrame())
    {
        //Trigger frame complete callback
        AlgorithmLink_SubframeCopyFrameCompleteCallback(pSubframeCopyObj);
        //Clear the frame complete register locations
        Utils_VIP_Interrupt_Clearframe_Interrupts();
    }

    //If subframe is completed
    if(Utils_VIP_Interrupt_IsSubframe())
    {
        //Trigger subframe complete callback
        AlgorithmLink_SubframeCopySubFrameCallback(pSubframeCopyObj);
        //Clear the subframe complete register locations
        Utils_VIP_Interrupt_ClearSubframe_Interrupts();
    }

    //end of interrupt processing
    Utils_VIP_Interrupt_EndOfInterrupt();
}

/**
 *******************************************************************************
 *
 * \brief Initialize the given System_Buffer array using the given Frame List.
 *
 *      The links communicate with each other using the System_Buffer. However,
 *      the frames are in FVID2_Frame format.   This function converts the
 *      given FVID2_Frame list into System_Buffer array. Also, it initializes
 *      the System_Buffer payload and other required fields. The caller must
 *      ensure that the number of frames in the FrameList match the number of
 *      elements in the system buffer and payload array.
 *
 * \param  pObj         [IN] Algorithm link object handle
 * \param pFrameList    [IN] FVID2 Frame List used to initialize System_Buffer
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgorithmLink_SubframeCopyInitSystemBuffer(void *pObj,
                                                    FVID2_FrameList *pFrameList)
{
    AlgorithmLink_SubframeCopyObj *pSubframeCopyObj;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_LinkChInfo *pQueChInfo;
    System_Buffer *buffers;
    System_VideoFrameBuffer *videoFrames;
    UInt32 i, planes;;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pOutputQInfo = &pSubframeCopyObj->outputQInfo;
    pQueChInfo = &(pOutputQInfo->queInfo.chInfo[0]);

    /*
     * buffers and videoFrames point to contiguous buffers and video frame
     * buffers respectively. Initialize all the buffers and video frame
     * buffers.
     */
    buffers = pSubframeCopyObj->buffers;
    memset(buffers, 0, sizeof(*buffers)*pFrameList->numFrames);

    videoFrames = pSubframeCopyObj->videoFrames;
    memset(videoFrames, 0, sizeof(*videoFrames)*pFrameList->numFrames);

    /*
     * Initialize System Buffer using the FVID2 frame information and
     * associate the System_VideoFrameBuffer as payload to the
     * System_Buffer.
     */
    for (i = 0; i < pFrameList->numFrames; i++)
    {
        buffers[i].bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        buffers[i].chNum       = pFrameList->frames[i]->chNum;
        buffers[i].payloadSize = sizeof(System_VideoFrameBuffer);
        buffers[i].payload     = &videoFrames[i];

        /*
        * Inistialise the channel info in video frames with corres entries
        * from the output queue channel info
        */
        videoFrames[i].chInfo.height = pQueChInfo->height;
        videoFrames[i].chInfo.width = pQueChInfo->width;
        videoFrames[i].chInfo.flags = pQueChInfo->flags;
        for (planes = 0; planes < SYSTEM_MAX_PLANES; planes++)
        {
            videoFrames[i].bufAddr[planes] =
                                pFrameList->frames[i]->addr[0][planes];
            videoFrames[i].chInfo.pitch[planes] = pQueChInfo->pitch[planes];
        }

        //Put the system buffers onto the empty queue
        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, &buffers[i]);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Allocate frames for capture. Queue allocated frames to capture driver
 *
 *
 * \param  pObj         [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgorithmLink_SubframeCopyAllocFrames(void *pObj)
{
    AlgorithmLink_SubframeCopyObj *pSubframeCopyObj;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_LinkChInfo *pQueChInfo;
    FVID2_FrameList frameList;
    FVID2_Frame *frames;
    FVID2_Format format;
    UInt32 numFrames, frameId, cbCrHeight;
    Int32 status;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    /*
     * Bound the numBufs between min and max supported
     */
    if (pSubframeCopyObj->numBufs > SUBFRAME_COPY_LINK_MAX_FRAMES)
    {
        Vps_printf(" ALG_SUBFRAME: WARNING: Create args numBufs[%d] > max[%d]"
                    " Overriding create args !!!",
                    pSubframeCopyObj->numBufs,
                    SUBFRAME_COPY_LINK_MAX_FRAMES);
        pSubframeCopyObj->numBufs = SUBFRAME_COPY_LINK_MAX_FRAMES;
    }
    if (pSubframeCopyObj->numBufs < SUBFRAME_COPY_LINK_MIN_FRAMES)
    {
        Vps_printf(" ALG_SUBFRAME: WARNING: Create args numBufs[%d] < min[%d] "
                   "Overriding create args !!!",
                   pSubframeCopyObj->numBufs,
                   SUBFRAME_COPY_LINK_MIN_FRAMES);
        pSubframeCopyObj->numBufs = SUBFRAME_COPY_LINK_MIN_FRAMES;
    }

    /*
    * subframe copy algplugin has a single output queue and a single channel
    * support.
    */
    numFrames = pSubframeCopyObj->numBufs;
    pOutputQInfo = &pSubframeCopyObj->outputQInfo;
    pQueChInfo = &(pOutputQInfo->queInfo.chInfo[0]);
    frames = &pSubframeCopyObj->frames[0];

    /*
     * fill format with channel specific values
     */
    format.chNum = 0;
    format.width = pQueChInfo->width;
    format.height = pQueChInfo->height;
    format.pitch[0] = pQueChInfo->pitch[0];
    format.pitch[1] = pQueChInfo->pitch[1];
    format.pitch[2] = pQueChInfo->pitch[2];
    format.fieldMerged[0] = FALSE;
    format.fieldMerged[1] = FALSE;
    format.fieldMerged[2] = FALSE;
    format.dataFormat = (System_VideoDataFormat)
                     System_Link_Ch_Info_Get_Flag_Data_Format(pQueChInfo->flags);
    format.scanFormat = (System_VideoScanFormat)
                     System_Link_Ch_Info_Get_Flag_Scan_Format(pQueChInfo->flags);
    format.bpp = FVID2_BPP_BITS8;

    //Compute cbCrHeight based on dataformat.
    if (format.dataFormat == SYSTEM_DF_YUV422I_YUYV)
    {
        cbCrHeight = pQueChInfo->height;
    }
    else if(format.dataFormat == SYSTEM_DF_YUV420SP_UV)
    {
        cbCrHeight = pQueChInfo->height/2;
    }
    else
    {
        UTILS_assert(NULL);
    }

    /*
     * alloc memory based on 'format'
     * Allocated frame info is put in frames[]
     */
    status = Utils_memFrameAlloc(&format,
                                frames,
                                numFrames,
                                cbCrHeight);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * init frameList for list of frames that are queued
     */
    frameList.perListCfg = NULL;
    frameList.reserved = NULL;
    for (frameId = 0; frameId < numFrames; frameId++)
    {
        frames[frameId].perFrameCfg = NULL;
        frames[frameId].subFrameInfo = NULL;
        frames[frameId].appData = NULL;
        frames[frameId].reserved = NULL;

        frameList.frames[frameId] = &frames[frameId];
    }
    frameList.numFrames = numFrames;

    /*
     * Initialize the system buffer with the video frame buffer
     * payload and initialize the payload with the frame data pointer
     */
    status = AlgorithmLink_SubframeCopyInitSystemBuffer(pObj,&frameList);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for subframe copy algorithm link
 *
 * \param  pObj             [IN] Algorithm link object handle
 * \param  pCreateParams    [IN] subframe capture link create parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopyCreate(void * pObj, void * pCreateParams)
{
    AlgorithmLink_SubframeCopyCreateParams *pPrm;
    AlgorithmLink_SubframeCopyObj *pSubframeCopyObj;
    System_LinkInfo prevLinkInfo;
    System_LinkQueInfo  pQueInfo;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_LinkChInfo *pOutQChInfo, *pInQChInfo;
    CaptureLink_Subframe_Info *pCaptureLinkSubframeInfo;
    System_VideoDataFormat dataFormat;
    UInt32 i, prevLinkId, numOutputQ;
    Int32 status;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                                Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                                sizeof(AlgorithmLink_SubframeCopyObj), 32);
    UTILS_assert(pSubframeCopyObj != NULL);

    /*
     * Algorithm specific object Pointer gets recorded in algorithmParams
     */
    AlgorithmLink_setAlgorithmParamsObj(pObj, pSubframeCopyObj);

    pSubframeCopyObj->ptsk = &(((AlgorithmLink_Obj *)pObj)->tsk);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    pPrm = (AlgorithmLink_SubframeCopyCreateParams *)pCreateParams;
    memcpy(&pSubframeCopyObj->createArgs, pPrm, sizeof(*pPrm));

    /*
    * Get information from previous link regarding the input queue.
    * The inChannelId in create params indicate the channel this alg plugin
    * needs to process from prev links output queue
    */
    prevLinkId = pSubframeCopyObj->createArgs.inQueParams.prevLinkId;
    status = System_linkGetInfo(prevLinkId, &prevLinkInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    pQueInfo = prevLinkInfo.queInfo
                    [pSubframeCopyObj->createArgs.inQueParams.prevLinkQueId];
    pInQChInfo = &(pQueInfo.chInfo[pSubframeCopyObj->createArgs.inChannelId]);

    /*
     * Populating parameters corresponding to Q usage of subframe copy
     * algorithm link
     */
    pOutputQInfo = &pSubframeCopyObj->outputQInfo;
    numOutputQ = 1;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->queInfo.numCh = 1;
    pOutQChInfo = &(pOutputQInfo->queInfo.chInfo[0]);

    /*
     * Certain channel info parameters simply get defined by previous link
     * channel info. Hence copying them to output channel info
     */
    dataFormat = (System_VideoDataFormat)
                    System_Link_Ch_Info_Get_Flag_Data_Format(pInQChInfo->flags);
    UTILS_assert(dataFormat == SYSTEM_DF_YUV422I_YUYV ||
                 dataFormat == SYSTEM_DF_YUV420SP_UV);
    pOutQChInfo->width = pInQChInfo->width;
    pOutQChInfo->height = pInQChInfo->height;
    pOutQChInfo->startX = pInQChInfo->startX;
    pOutQChInfo->startY = pInQChInfo->startY;
    for (i = 0; i < SYSTEM_MAX_PLANES; i++)
        pOutQChInfo->pitch[i] = pInQChInfo->pitch[i];
    pOutQChInfo->flags = pInQChInfo->flags;

    /*
     * Initializations needed for book keeping of buffer handling.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                0,
                                NULL,
                                numOutputQ,
                                pOutputQInfo
                                );

    pSubframeCopyObj->numBufs = pSubframeCopyObj->createArgs.numBufs;

    /*
     * Query previous link for details on the VIP output frome.
     * This frame is allocated by prev capture link in the OCMC region as a
     * circular buffer
     */
    pCaptureLinkSubframeInfo = &pSubframeCopyObj->captureLinkSubframeInfo;
    memset(pCaptureLinkSubframeInfo,0, sizeof(CaptureLink_Subframe_Info));
    pCaptureLinkSubframeInfo->inChannelId
                    = pSubframeCopyObj->createArgs.inChannelId;
    status = System_linkControl(
                    pSubframeCopyObj->createArgs.inQueParams.prevLinkId,
                    CAPTURE_LINK_GET_SUBFRAME_INFO,
                    pCaptureLinkSubframeInfo,
                    sizeof(CaptureLink_Subframe_Info),
                    TRUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Allocate frames for output queue
     */
    status = AlgorithmLink_SubframeCopyAllocFrames(pObj);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Create EDMA for transerring subframe data onto output frames
    AlgorithmLink_SubframeCopyEDMACreate(pSubframeCopyObj);

    /*
    * Create and initialise the new data command queue
    * This queue is used to store frame/subframe complete events as they arise
    * in context of an ISR. Once Process API is called on this alg plugin
    * the entries in the command queue are processed in the order they arrived.
    */
    for (i = 0; i < UTILS_ARRAYSIZE(pSubframeCopyObj->cmdQ); i++)
    {
        pSubframeCopyObj->cmdQ[i] = SUBFRAME_ALGLINK_NEWDATA_IS_INVALID;
    }
    status = Utils_queCreate
                        (&pSubframeCopyObj->newDataCmdQ,
                        UTILS_ARRAYSIZE(pSubframeCopyObj->cmdQ),
                        pSubframeCopyObj->cmdQ,
                        UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Assign pointer to link stats object */
    pSubframeCopyObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj),"ALG_SUB_FRAME_COPY");
    UTILS_assert(NULL != pSubframeCopyObj->linkStatsInfo);

    pSubframeCopyObj->subFrameNum = 0;
    pSubframeCopyObj->isFirstFrameRecv = FALSE;
    pSubframeCopyObj->isFirstSubFrameRecv = FALSE;
    pSubframeCopyObj->dropFrame = FALSE;

    //Compute number of vertical lines in each subframe
    pSubframeCopyObj->numSubframesInEachFrame
        = pOutQChInfo->height / pCaptureLinkSubframeInfo->numLinesPerSubFrame;
    if(pOutQChInfo->height % pCaptureLinkSubframeInfo->numLinesPerSubFrame)
            pSubframeCopyObj->numSubframesInEachFrame++;

    //Number of lines remaining to be processed for current frame.
    pSubframeCopyObj->numLinesRemainInCurFrame = pOutQChInfo->height;

    pSubframeCopyObj->sysBufCurrentlyFilling = NULL;

    /* Clear older interrupts */
    Utils_VIP_Interrupt_Clearframe_Interrupts();
    Utils_VIP_Interrupt_ClearSubframe_Interrupts();

    /*
    *Register for interrupts from VIP for frame and subframe completion
    * events.
    */
    pSubframeCopyObj->hwiHandle = NULL;
    pSubframeCopyObj->hwiHandle = Utils_EVE_RegisterInterrupts_FromVIP(
                            UTILS_IRQ_XBAR_VIP1_IRQ_2,
                            UTILS_IRQ_XBAR_EVE_VIP,
                            (Hwi_FuncPtr)(&AlgorithmLink_SubframeCopyVip_Isr_Func),
                            pSubframeCopyObj);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Process the subframe data
 *
 * This function gets called in response to ISR registered with VIP.
 *
 * \param  pObj             [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgorithmLink_SubframeCopyProcessSubframeData
                                                                (void * pObj)
{
    AlgorithmLink_SubframeCopyObj * pSubframeCopyObj;
    CaptureLink_Subframe_Info *pCaptureLinkSubframeInfo;
    System_Buffer *pBuf;
    System_VideoFrameBuffer *videoFrame;
    System_VideoDataFormat dataFormat;
    UInt32 *pInPtr[2], *pOutPtr[2];
    Ptr pOcmcPlane[2];
    UInt32 outPitch[2], inPitch[2], subframeOffset[2],heightSubframe;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    /*
    * If this is first subframe in the frame, i.e. no system buffer has been
    * obtained for this frame yet, then get an buffer from output queue
    */
    if(pSubframeCopyObj->sysBufCurrentlyFilling == NULL)
    {
        //Its a single channel, single output q ,hence their ids are 0
        status = AlgorithmLink_getEmptyOutputBuffer(pObj,0,0,&pBuf);
        if(status != SYSTEM_LINK_STATUS_SOK)
        {
            //If downstream link is slow then current frame needs to be dropped
            pSubframeCopyObj->dropFrame = TRUE;
            return SYSTEM_LINK_STATUS_SOK;
        }
        pSubframeCopyObj->sysBufCurrentlyFilling = pBuf;
    }
    else
    {
        //Buffer is the system buffer being filled for current frame
        pBuf = pSubframeCopyObj->sysBufCurrentlyFilling;
    }

    UTILS_assert(pBuf->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
    videoFrame = pBuf->payload;
    dataFormat = (System_VideoDataFormat)
        System_Link_Ch_Info_Get_Flag_Data_Format(videoFrame->chInfo.flags);
    UTILS_assert(dataFormat == SYSTEM_DF_YUV422I_YUYV ||
                 dataFormat == SYSTEM_DF_YUV420SP_UV);

    pCaptureLinkSubframeInfo = &pSubframeCopyObj->captureLinkSubframeInfo;

    //Process the subframe data based on data format.
    if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
    {
        //There is a single plane for YUVdata
        pOcmcPlane[0] = (Ptr)pCaptureLinkSubframeInfo->ocmcCBufVirtAddr[0];

        //initialising input and output pitch
        outPitch[0] = inPitch[0] = videoFrame->chInfo.pitch[0];

        /*
        * computing the offset for reading/writing current subframe within the
        * full frame
        */
        subframeOffset[0]
                    = pSubframeCopyObj->subFrameNum
                    * pCaptureLinkSubframeInfo->numLinesPerSubFrame
                    * videoFrame->chInfo.pitch[0];

        //Compute input and output pointers in frame for current subframe
        pInPtr[0] = (UInt32 *)((UInt8 *)pOcmcPlane[0] + subframeOffset[0]);
        pOutPtr[0] = (UInt32 *)
                    ((UInt8 *)videoFrame->bufAddr[0] + subframeOffset[0]);
    }
    else if(dataFormat == SYSTEM_DF_YUV420SP_UV)
    {
        //Two planes for Y and UV seperately
        pOcmcPlane[0] = (Ptr)pCaptureLinkSubframeInfo->ocmcCBufVirtAddr[0];
        pOcmcPlane[1] = (Ptr)pCaptureLinkSubframeInfo->ocmcCBufVirtAddr[1];

        //initialising input and output pitch for both planes
        outPitch[0] = inPitch[0] = videoFrame->chInfo.pitch[0];
        outPitch[1] = inPitch[1] = videoFrame->chInfo.pitch[1];

        /*
        * computing the offset for reading/writing current subframe within the
        * full frame
        */
        subframeOffset[0]
                    = pSubframeCopyObj->subFrameNum
                    * pCaptureLinkSubframeInfo->numLinesPerSubFrame
                    * videoFrame->chInfo.pitch[0];
        subframeOffset[1]
                    = pSubframeCopyObj->subFrameNum
                    * pCaptureLinkSubframeInfo->numLinesPerSubFrame/2
                    * videoFrame->chInfo.pitch[1];

        //Compute input and output pointers in frame for current subframe
        pInPtr[0] = (UInt32 *)((UInt8 *)pOcmcPlane[0] + subframeOffset[0]);
        pInPtr[1] = (UInt32 *)((UInt8 *)pOcmcPlane[1]+ subframeOffset[1]);
        pOutPtr[0] = (UInt32 *)
                    ((UInt8 *)videoFrame->bufAddr[0] + subframeOffset[0]);
        pOutPtr[1] = (UInt32 *)
                    ((UInt8 *)videoFrame->bufAddr[1]+ subframeOffset[1]);
    }

    /*
    * If number of lines remaining in current frame are smaller than the
    * default subframe height then read only remaining lines
    */
    if(pSubframeCopyObj->numLinesRemainInCurFrame
                < pCaptureLinkSubframeInfo->numLinesPerSubFrame)
        heightSubframe = pSubframeCopyObj->numLinesRemainInCurFrame;
    else
        heightSubframe = pCaptureLinkSubframeInfo->numLinesPerSubFrame;

    /*
    * Do an EDMA transfer of subframe data from ocmc cbuf virtual address to
    * corresponding location in video frame
    */
    status = AlgorithmLink_SubframeCopyEDMACopy(pSubframeCopyObj,(UInt32 **)pInPtr,
        (UInt32 **)pOutPtr,videoFrame->chInfo.width, heightSubframe,
        inPitch, outPitch,dataFormat);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Recompute number of lines remaining to be processed in current frame
    pSubframeCopyObj->numLinesRemainInCurFrame -=heightSubframe;
    pSubframeCopyObj->subFrameNum++;

    return  status;
}

/**
 *******************************************************************************
 *
 * \brief Process frame completion
 *
 * This function gets called in response to ISR registered with VIP.
 *
 * \param  pObj             [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgorithmLink_SubframeCopyProcessFrameData(void * pObj)
{
    AlgorithmLink_SubframeCopyObj * pSubframeCopyObj;
    System_BufferList outputBufListReturn;
    System_LinkChInfo *pOutQChInfo;
    System_Buffer *sysBuf;
    Int32 outputQId, status = SYSTEM_LINK_STATUS_SOK;
    System_LinkStatistics *linkStatsInfo;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pSubframeCopyObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    if(pSubframeCopyObj->isFirstFrameRecv==FALSE)
    {
        //Initialise when first frame is recicved.
        pSubframeCopyObj->isFirstFrameRecv = TRUE;
        Utils_resetLinkStatistics(&linkStatsInfo->linkStats,1,1);
        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    /*
    * If there are still lines remaing in current frame and this frame is not
    * marked for getting dropped then process the last subframe
    */
    if(pSubframeCopyObj->numLinesRemainInCurFrame&&!pSubframeCopyObj->dropFrame)
        AlgorithmLink_SubframeCopyProcessSubframeData(pObj);

    UTILS_assert(pSubframeCopyObj->subFrameNum
                <=pSubframeCopyObj->numSubframesInEachFrame);

    if(pSubframeCopyObj->subFrameNum
        == pSubframeCopyObj->numSubframesInEachFrame
        && !pSubframeCopyObj->dropFrame)
    {
        /* Send the frame to next link only if all subframe in this frame are
        * recieved. Else drop the frame
        */
        sysBuf = pSubframeCopyObj->sysBufCurrentlyFilling;

        // Update the timestamp at this point when frame is available
        sysBuf->srcTimestamp = Utils_getCurGlobalTimeInUsec();
        sysBuf->frameId = 0;
        sysBuf->linkLocalTimestamp = sysBuf->srcTimestamp;

        Utils_updateLatency(&linkStatsInfo->linkLatency,
                            sysBuf->linkLocalTimestamp);
        Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                            sysBuf->srcTimestamp);

        linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

        /*
         * Putting filled buffer into output full buffer Q
         * Note that this does not mean algorithm has freed the output buffer
         */
        outputQId = 0;
        status = AlgorithmLink_putFullOutputBuffer(pObj,outputQId,sysBuf);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        /*
         * Send command to link for availability the buffer in output queue.
         */
        System_sendLinkCmd(pSubframeCopyObj->createArgs.outQueParams.nextLink,
                           SYSTEM_CMD_NEW_DATA,
                           NULL);

        /*
         * Releasing (Free'ing) output buffer, since algorithm does not need
         * it for any future usage.
         * In case of INPLACE computation, there is no need to free output
         * buffer, since it will be freed as input buffer.
         */
        outputBufListReturn.numBuf = 1;
        outputBufListReturn.buffers[0] = sysBuf;
        status = AlgorithmLink_releaseOutputBuffer(pObj,
                                          outputQId,
                                          &outputBufListReturn);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        //Drop the frame

        linkStatsInfo->linkStats.outBufErrorCount++;
        linkStatsInfo->linkStats.chStats[0].outBufDropCount[0]++;
    }

    //Reset all the relavant counters/datastructures at frame boundaries
    pSubframeCopyObj->subFrameNum = 0;
    pOutQChInfo = &(pSubframeCopyObj->outputQInfo.queInfo.chInfo[0]);
    pSubframeCopyObj->numLinesRemainInCurFrame = pOutQChInfo->height;
    pSubframeCopyObj->sysBufCurrentlyFilling = NULL;
    pSubframeCopyObj->dropFrame = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for subframe copy algorithm link
 *
 *        This function executes on the EVE The processor gets locked with
 *        execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopyProcess(void * pObj)
{
    AlgorithmLink_SubframeCopyObj * pSubframeCopyObj;
    Int32 status;
    UInt32 cmdType;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    Utils_linkStatsCollectorProcessCmd(pSubframeCopyObj->linkStatsInfo);

    do
    {
        /*
        * Process all the commands in the command queue, till the queue gets
        * empty
        */
        status = Utils_queGet(&pSubframeCopyObj->newDataCmdQ,
                  (Ptr *)&cmdType,
                  1,
                  BSP_OSAL_NO_WAIT);
        if(status != SYSTEM_LINK_STATUS_SOK)
            break;

        //Based on command type process either a subframe or frame completion.
        switch(cmdType)
            {
            case SUBFRAME_ALGLINK_NEWDATA_IS_SUBFRAME:
                if(!pSubframeCopyObj->dropFrame)
                    status = AlgorithmLink_SubframeCopyProcessSubframeData(pObj);
                break;
            case SUBFRAME_ALGLINK_NEWDATA_IS_FRAME:
                status = AlgorithmLink_SubframeCopyProcessFrameData(pObj);
                break;
            default:
                UTILS_assert(NULL);
            };
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }while(1);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for frame copy algo
 *
 * \param  pObj                  [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopyControl(void * pObj,
                                                void * pControlParams)
{
    /* If during processing any control param arrives, it will cause subframes
    * to get dropped leading to corruption.
    * This functions needs to be implemented with lot of considertations for
    * subframe algplugin
    */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for subframe copy algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopyStop(void * pObj)
{
    AlgorithmLink_SubframeCopyObj * pSubframeCopyObj;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    /*
    * Ideally registration and deregistration of interrupts should happen in
    * Start-Stop function. But since Start algplugin is not available by design
    * its being done in create-delete. Hence as workaround atleast next frame
    * is dropped. The assumption is Stop to prev link will reach immediately
    * which will stop frame processing
    */
    Utils_queReset(&pSubframeCopyObj->newDataCmdQ);
    pSubframeCopyObj->dropFrame = TRUE;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Free the allocated frames
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static Int32 AlgorithmLink_SubframeCopyFreeFrames(void * pObj)
{
    AlgorithmLink_SubframeCopyObj *pSubframeCopyObj;
    AlgorithmLink_OutputQueueInfo *pOutputQInfo;
    System_LinkChInfo *pQueChInfo;
    FVID2_Format format;
    FVID2_Frame *pFrames;
    UInt32 cbCrHeight;
    Int32 status;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    pOutputQInfo = &pSubframeCopyObj->outputQInfo;
    pQueChInfo = &(pOutputQInfo->queInfo.chInfo[0]);
    pFrames = &pSubframeCopyObj->frames[0];

    /*
     *     fill format with channel specific values
     */
    format.chNum = 0;
    format.width = pQueChInfo->width;
    format.height = pQueChInfo->height;
    format.pitch[0] = pQueChInfo->pitch[0];
    format.pitch[1] = pQueChInfo->pitch[1];
    format.pitch[2] = pQueChInfo->pitch[2];
    format.fieldMerged[0] = FALSE;
    format.fieldMerged[1] = FALSE;
    format.fieldMerged[2] = FALSE;
    format.dataFormat = (System_VideoDataFormat)
                     System_Link_Ch_Info_Get_Flag_Data_Format(pQueChInfo->flags);
    format.scanFormat = (System_VideoScanFormat)
                     System_Link_Ch_Info_Get_Flag_Scan_Format(pQueChInfo->flags);
    format.bpp = FVID2_BPP_BITS8;
    if (format.dataFormat == SYSTEM_DF_YUV422I_YUYV)
    {
        cbCrHeight = pQueChInfo->height;
    }
    else if(format.dataFormat == SYSTEM_DF_YUV420SP_UV)
    {
        cbCrHeight = pQueChInfo->height/2;
    }
    else
    {
        UTILS_assert(NULL);
    }
    status = Utils_memFrameFree(&format, pFrames,
                                pSubframeCopyObj->numBufs, cbCrHeight);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for subframe copy algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopyDelete(void * pObj)
{
    AlgorithmLink_SubframeCopyObj * pSubframeCopyObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pSubframeCopyObj = (AlgorithmLink_SubframeCopyObj *)
                    AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pSubframeCopyObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    // Unregister the interrupts from VIP
    Utils_EVE_UnregisterInterrupts_FromVIP(&pSubframeCopyObj->hwiHandle);

    // Delete the command data queue
    status = Utils_queDelete(&pSubframeCopyObj->newDataCmdQ);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Free the allocated frames
    status = AlgorithmLink_SubframeCopyFreeFrames(pObj);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    //Delete the EDMA object
    status = AlgorithmLink_SubframeCopyEDMADelete(pSubframeCopyObj);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                       pSubframeCopyObj, sizeof(AlgorithmLink_SubframeCopyObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pEdgeDetectionObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_SubframeCopyPrintStatistics(void *pObj,
                       AlgorithmLink_SubframeCopyObj *pSubframeCopyObj)
{
    UTILS_assert(NULL != pSubframeCopyObj->linkStatsInfo);

    Utils_printLinkStatistics(
        &pSubframeCopyObj->linkStatsInfo->linkStats,
        "ALG_SUBFRAME_COPY",
        TRUE);

    Utils_printLatency("ALG_SUBFRAME_COPY",
                       &pSubframeCopyObj->linkStatsInfo->linkLatency,
                       &pSubframeCopyObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}
