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
 * \file CaptureLink_subframe__drv.c
 *
 * \brief  This file contains subframe related implementation for capture link
 *
 * \version 0.0 (Jul 2014) : [VT] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "captureLink_priv.h"
#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
Int32 CaptureLink_subframe_drvAllocOCMCFrame(
                    const FVID2_Format * pFormat,
                  FVID2_Frame * pFrame,
                  UInt32 numLinesPerSlice);

/**
 *******************************************************************************
 *
 * \brief   This functions fills the information of VIP Output frame  into
 *          the OCMC info buffer pointer passed to it.
            The subframe copy  link queries this information from capture link.
 * \param   pObj            [IN] subframe capture link global handle
 *          pCaptureLinkSubframeInfo [IN] ocmc buffer i.e. VIP output buffer info.
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_subframe_drvGetVIPOutFrameInfo
                            (CaptureLink_Obj *pObj,
                            CaptureLink_Subframe_Info *pCaptureLinkSubframeInfo)
{
    UInt32  planeCnt, instId, streamId;
    Vps_CaptVipOutInfo *pOutInfo;
    Vps_CaptCreateParams *pVipCreateArgs;
    CaptureLink_InstObj * pDrvObj;

    /* Get the VIP instance id based on the qChannel id passed by subframe copy
    * alg plugin
    */
    instId = pObj->chToInstMap[pCaptureLinkSubframeInfo->inChannelId];
    pDrvObj = &pObj->instObj[instId];
    pVipCreateArgs = &pDrvObj->createArgs;

    /* Get the atream id based on the qChannel id passed by subframe copy
    * alg plugin
    */
    for (streamId = 0U; streamId < pVipCreateArgs->numStream; streamId++)
    {
        if( (pVipCreateArgs->chNumMap[streamId][0]) == (pCaptureLinkSubframeInfo->inChannelId+pObj->fvid2DrvChNumOffset))
        {
            break;
        }
    }
    pOutInfo = &pDrvObj->vipPrms.outStreamInfo[streamId];

    /*
     * Fill the OCMC buffer information
     */
    pCaptureLinkSubframeInfo->numLinesPerSubFrame
                                    = pOutInfo->subFrmPrms.numLinesPerSubFrame;

    for (planeCnt = 0U; planeCnt < SYSTEM_MAX_PLANES; planeCnt++)
    {
        pCaptureLinkSubframeInfo->ocmcCBufVirtAddr[planeCnt]
                        = (UInt32)pDrvObj->frames[0].addr[0][planeCnt];
    }
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3:Cast between a pointer and an integral type
     * State: Defer -> Waiver -> Case by case
     * For array indexing .
     */

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Allocates OCMC frames.
 *
 *
 * \param   pFormat     [IN] data format
 *          pFrame      [IN] frame pointer to store allocated data
 *          numLinesPerSlice [IN] number of vertical lines per slice
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_subframe_drvAllocOCMCFrame(
                    const FVID2_Format * pFormat,
                  FVID2_Frame * pFrame,
                  UInt32 numLinesPerSlice)
{
    Ptr virtStartAddr = 0;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /* Initialise the OCMC Cbuf for allocating data from OCMC_RAM1 region */
    Utils_cbufOcmcInit(UTILS_OCMC_RAM1);

    /* Allocate frames from OCMC region as circular buffers */
    switch (pFormat->dataFormat)
    {
        case FVID2_DF_YUV422I_YUYV:
            /* Actualy memory allocated in only for numLinesPerSlice but for
            * app we recieve a virtual address pointer and access data as if
            * a full frame is present there
            */
            virtStartAddr =  Utils_cbufOcmcAlloc
                                    (UTILS_OCMC_RAM1,
                                    pFormat->bpp,
                                    pFormat->width,
                                    VpsUtils_align(pFormat->height, 2U),
                                    numLinesPerSlice,
                                    CAPTURE_LINK_NUM_SUBFRAME_PER_CBUF);
            UTILS_assert(virtStartAddr !=NULL);

            /* Single plan as its is YUV422I format */
            memset(pFrame, 0, sizeof(*pFrame));
            pFrame->chNum = pFormat->chNum;
            pFrame->addr[0][0] = virtStartAddr;
            break;

        case FVID2_DF_YUV420SP_UV:
            /* Since is it YUV420sp format two seperate circular buffers are
             * allocated for Y and UV planes
             */
            memset(pFrame, 0, sizeof(*pFrame));
            pFrame->chNum = pFormat->chNum;
            virtStartAddr =  Utils_cbufOcmcAlloc
                                    (UTILS_OCMC_RAM1,
                                    1U,
                                    pFormat->width,
                                    VpsUtils_align(pFormat->height, 2U),
                                    numLinesPerSlice,
                                    CAPTURE_LINK_NUM_SUBFRAME_PER_CBUF);
            UTILS_assert(virtStartAddr !=NULL);
            pFrame->addr[0][0] = virtStartAddr;

            virtStartAddr =  Utils_cbufOcmcAlloc
                                    (UTILS_OCMC_RAM1,
                                    1U,
                                    pFormat->width,
                                    VpsUtils_align(pFormat->height/2U, 2U),
                                    numLinesPerSlice/2U,
                                    CAPTURE_LINK_NUM_SUBFRAME_PER_CBUF);
            UTILS_assert(virtStartAddr !=NULL);
            /* assign pointer for C plane */
            pFrame->addr[0][1] = (UInt8 *) virtStartAddr;
            break;
        default:
            /* illegal data format */
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Allocate frames for capture. Queue allocated frames to capture driver
 *
 *
 *  \param pObj         [IN] Capture link object
 *  \param pDrvObj      [IN] Capture link instance object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_subframe_drvAllocAndQueueFrames
                        (CaptureLink_Obj * pObj,CaptureLink_InstObj * pDrvObj)
{
    Int32 status;
    UInt32 streamId;
    FVID2_Frame *frame;
    FVID2_FrameList frameList;
    FVID2_Format format;
    Vps_CaptVipOutInfo *pOutInfo;

    /*
     * for every stream and channel in a capture handle
     */
    for (streamId = 0U; streamId < (UInt32)pDrvObj->createArgs.numStream; streamId++)
    {
        pOutInfo = &pDrvObj->vipPrms.outStreamInfo[streamId];

        /*
         * fill format with channel specific values
         */
        format.chNum =
            pDrvObj->createArgs.chNumMap[streamId][0];

        format.width = pDrvObj->bufferWidth;
        format.height = pDrvObj->bufferHeight[0];

        format.pitch[0] = pOutInfo->outFmt.pitch[0];
        format.pitch[1] = pOutInfo->outFmt.pitch[1];
        format.pitch[2] = pOutInfo->outFmt.pitch[2];
        format.fieldMerged[0] = FALSE;
        format.fieldMerged[1] = FALSE;
        format.fieldMerged[2] = FALSE;
        format.dataFormat = pOutInfo->outFmt.dataFormat;
        format.scanFormat = FVID2_SF_PROGRESSIVE;
        format.bpp = FVID2_BPP_BITS8;                  /* ignored */

        if (format.dataFormat == FVID2_DF_RAW_VBI)
        {
                format.height = CAPTURE_LINK_RAW_VBI_LINES;
        }

        frame = &pDrvObj->frames[0];

        /* Allocate frame in OCMC region as circular buffers based on format
        * and number of lines in each subframe.
        */
        status = CaptureLink_subframe_drvAllocOCMCFrame(&format,
                frame,
                pOutInfo->subFrmPrms.numLinesPerSubFrame);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        frame->perFrameCfg = NULL;
        frame->subFrameInfo = NULL;
        frame->appData = NULL;
        frame->reserved = NULL;

        /*
         * Set number of frame in frame list. Only a single frame is allocated
         * and queued.
         */
        frameList.numFrames = 1;
        frameList.frames[0] = frame;


        /*
         * queue the frames in frameList
         */
        status =
            FVID2_queue(pDrvObj->captureVipHandle, &frameList, streamId);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    return SYSTEM_LINK_STATUS_SOK;
}



/**
 *******************************************************************************
 *
 * \brief Free the allocated frames
 *
 *
 *  \param pObj         [IN] Capture link object
 *  \param pDrvObj      [IN] Capture link instance object
 *
 *  \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_subframe_drvFreeFrames(CaptureLink_Obj * pObj,
                                CaptureLink_InstObj * pDrvObj)
{
    UInt16 streamId, planeCnt;
    FVID2_Frame *pFrame;

    UTILS_assert(pDrvObj->createArgs.numStream
                    <=CAPTURE_LINK_MAX_STREAMS_PER_HANDLE);

    /*
     * for every stream and channel in a capture handle
     */
    for (streamId = 0; streamId < pDrvObj->createArgs.numStream; streamId++)
    {
        pFrame = &pDrvObj->frames[0];

        for (planeCnt = 0; planeCnt < SYSTEM_MAX_PLANES; planeCnt++)
        {
            if((pFrame->addr[0][planeCnt]))
            {
                Utils_cbufOcmcFree(UTILS_OCMC_RAM1, (pFrame->addr[0][planeCnt]));
            }
        }

        Utils_cbufOcmcDeInit(UTILS_OCMC_RAM1);
    }
    return SYSTEM_LINK_STATUS_SOK;
}
