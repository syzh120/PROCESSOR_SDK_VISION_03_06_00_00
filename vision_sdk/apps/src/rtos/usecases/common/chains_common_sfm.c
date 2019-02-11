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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <src/include/chains_common_sfm.h>

#define SFM_CAM_PRM_FILE_MAX_SIZE          (12*30*60*60)
#define SFM_GROUNDPLANE_EQ_FILE_MAX_SIZE   ( 3*30*60*60)

#define INPUT_MAX_FRAMES (6400)

Chains_SfmObj gChains_sfmObj;

static UInt32 getFrameId(UInt8 *addr, UInt32 lineOffset)
{
#define FRAME_NUM_SIZE     (3)
#define FRAME_NUM_OFFSET   (5)

    UInt8 *curAddr;
    UInt32 i;
    UInt32 frameNum = 0;

    Cache_inv(
        addr+lineOffset*FRAME_NUM_OFFSET,
        lineOffset*FRAME_NUM_SIZE,
        Cache_Type_ALL,
        TRUE);

    for(i=0;i<32;i++)
    {
        curAddr = addr + lineOffset*(FRAME_NUM_OFFSET+FRAME_NUM_SIZE/2) + FRAME_NUM_OFFSET
                + i*FRAME_NUM_SIZE + FRAME_NUM_SIZE/2;

        if(*curAddr>=0x80)
        {
            frameNum |= (1<<i);
        }
    }

    return frameNum;
}

Void ChainsCommon_Sfm_CaptureSetCurrentFrameNum(UInt32 frameNum)
{
    UInt32 oldIntState = Hwi_disable();

    gChains_sfmObj.curFrameNum = frameNum;

    Hwi_restore(oldIntState);
}

UInt32 ChainsCommon_Sfm_CaptureGetCurrentFrameNum()
{
    UInt32 frameNum;
    UInt32 oldIntState = Hwi_disable();

    frameNum = gChains_sfmObj.curFrameNum;

    Hwi_restore(oldIntState);

    return frameNum;
}

Int32 ChainsCommon_Sfm_CaptureCallback(Void *appObj,
                            System_Buffer *pBuffer)
{
    System_VideoFrameBuffer *pVidFrame;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pVidFrame = pBuffer->payload;

    if(gChains_sfmObj.useDummyFrameId)
    {
        pBuffer->frameId = gChains_sfmObj.dummyFrameNum;
        gChains_sfmObj.dummyFrameNum++;
        /* wraparound */
        if(gChains_sfmObj.dummyFrameNum > INPUT_MAX_FRAMES)
        {
            gChains_sfmObj.dummyFrameNum = 0;
        }
    }
    else
    {
        pBuffer->frameId = getFrameId(pVidFrame->bufAddr[0], gChains_sfmObj.capturePitch);
    }

    #if 0
    if(pBuffer->frameId!=gChains_sfmObj.prevFrameId)
    #endif
    {
        Bool doSkip;

        status = SYSTEM_LINK_STATUS_SOK;

        doSkip = Utils_doSkipBuf(&gChains_sfmObj.skipFrames);
        if(doSkip)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }
    #if 0
    else
    {
        /* repeated frame, drop it */
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    #endif

    if(status == SYSTEM_LINK_STATUS_SOK && gChains_sfmObj.prevFrameId != (UInt32)-1)
    {
        if( (gChains_sfmObj.prevFrameId+1) != pBuffer->frameId)
        {
            gChains_sfmObj.frameSkipCount++;
            #if 0
            Vps_printf(" CHAINS: SFM: Capture skipped %d frames (%d, %d) !!\n",
                gChains_sfmObj.frameSkipCount,
                gChains_sfmObj.prevFrameId,
                pBuffer->frameId
            );
            #endif
        }
    }

    gChains_sfmObj.prevFrameId = pBuffer->frameId;

    if(status == SYSTEM_LINK_STATUS_SOK)
    {
        ChainsCommon_Sfm_CaptureSetCurrentFrameNum(pBuffer->frameId);
    }

    return status;
}

Void ChainsCommon_Sfm_SetCaptureCallback(CaptureLink_CreateParams *pPrm)
{
    pPrm->callback = ChainsCommon_Sfm_CaptureCallback;
    pPrm->appObj   = &gChains_sfmObj;

    /* do not skip frames in driver */
    pPrm->vipInst[0].outParams[0].frameSkipMask = 0;
    pPrm->vipInst[0].numBufs = 8;

    gChains_sfmObj.capturePitch = SystemUtils_align(pPrm->vipInst[0].outParams[0].width, 16);
}

Void ChainsCommon_Sfm_SetDecLinkCallback(DecLink_CreateParams *pPrm)
{
    pPrm->callback = ChainsCommon_Sfm_CaptureCallback;
    pPrm->appObj   = &gChains_sfmObj;

    gChains_sfmObj.capturePitch = SystemUtils_align(1920 + 64, 16);
}


Void ChainsCommon_Sfm_ReadCamPrmFromFile(AlgorithmLink_SfmCreateParams *pSfmPrm, char *camPrmfileName)
{
    Int32 status;
    UInt32 dataSize = 0, copySize;

    gChains_sfmObj.pCamPrmBuf
        = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, SFM_CAM_PRM_FILE_MAX_SIZE, 128);
    UTILS_assert(gChains_sfmObj.pCamPrmBuf!=NULL);

    gChains_sfmObj.pGroundPlaneEqBuf
        = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR, SFM_GROUNDPLANE_EQ_FILE_MAX_SIZE, 128);
    UTILS_assert(gChains_sfmObj.pGroundPlaneEqBuf!=NULL);



    status = Utils_fileReadFile(
                camPrmfileName,
                gChains_sfmObj.pCamPrmBuf,
                SFM_CAM_PRM_FILE_MAX_SIZE,
                &dataSize
                );
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    copySize = ALG_SFM_CAMERA_INTRENSIC_PARAM_SIZE*sizeof(float);

    memcpy(
        pSfmPrm->cameraIntrinsicParams,
        gChains_sfmObj.pCamPrmBuf,
        copySize
        );

    pSfmPrm->cameraExtrinsicParamsBufAddr
        =  (UInt32)gChains_sfmObj.pCamPrmBuf + copySize;

    pSfmPrm->cameraExtrinsicParamsBufSize = dataSize - copySize;
    pSfmPrm->cameraExtrinsicParamsDataSize =
        pSfmPrm->cameraExtrinsicParamsBufSize;

}

/**
 *******************************************************************************
 *
 * \brief   Set Algorithm related parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_Sfm_SetSfmPrm(
                    CaptureLink_CreateParams *pCapturePrm,
                    AlgorithmLink_SparseOpticalFlowCreateParams *pAlgSofPrm,
                    AlgorithmLink_SfmCreateParams *pSfmPrm,
                    AlgorithmLink_FcwCreateParams *pFcwPrm,
                    AlgorithmLink_ObjectDrawCreateParams *pDrawPrm,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height,
                    UInt32 sfmTrackPoints,
                    char *sfmCamPrmFile
                    )
{
    if(pCapturePrm)
    {
        ChainsCommon_Sfm_SetCaptureCallback(pCapturePrm);
    }
    if(pAlgSofPrm)
    {
        ChainsCommon_SetSOFConfig(pAlgSofPrm,
                                   startX,
                                   startY,
                                   width,
                                   height,
                                   sfmTrackPoints);
    }

    if(pSfmPrm)
    {
        pSfmPrm->maxTrackPoints = sfmTrackPoints;
        pSfmPrm->numOutBuffers  = 8;

        ChainsCommon_Sfm_ReadCamPrmFromFile(pSfmPrm, sfmCamPrmFile);

        if(pFcwPrm)
        {
            pFcwPrm->numOutBuffers = 8;
            pFcwPrm->minObjDist = 0;
            pFcwPrm->maxObjDist = 60.0;
            pFcwPrm->minObjHeight = 0.65;
            pFcwPrm->maxObjHeight = 2.6;
            pFcwPrm->imageWidth =  width;
            pFcwPrm->imageHeight = height;
            pFcwPrm->frameRate = OUTPUT_FPS;
            pFcwPrm->camHeightInMeter = 1.58;
            pFcwPrm->camOffsetInMeter = 1.4;

            memcpy(
                pFcwPrm->cameraIntrinsicParams,
                pSfmPrm->cameraIntrinsicParams,
                sizeof(pFcwPrm->cameraIntrinsicParams)
                );
        }
    }



    if(pDrawPrm)
    {
        pDrawPrm->imgFrameStartX = startX;
        pDrawPrm->imgFrameStartY = startY;
        pDrawPrm->imgFrameWidth  = width;
        pDrawPrm->imgFrameHeight = height;
        pDrawPrm->sofMaxTrackPoints = sfmTrackPoints;
        pDrawPrm->numOutBuffers  = 8;
        pDrawPrm->numDrawAlg = 1;
        pDrawPrm->drawAlgId[0] = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SFM;
        pDrawPrm->drawOption |= ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SFM;

    }
}

Void ChainsCommon_Sfm_Init(Bool useDummyFrameId)
{
    gChains_sfmObj.prevFrameId = (UInt32)-1;
    gChains_sfmObj.pCamPrmBuf = NULL;
    gChains_sfmObj.pGroundPlaneEqBuf = NULL;
    gChains_sfmObj.frameSkipCount = 0;
    gChains_sfmObj.dummyFrameNum = 0;
    gChains_sfmObj.useDummyFrameId = useDummyFrameId;
    gChains_sfmObj.curFrameNum = 0;

    Utils_resetSkipBufContext(&gChains_sfmObj.skipFrames,
        INPUT_FPS,
        OUTPUT_FPS
        );
}

Void ChainsCommon_Sfm_DeInit()
{
    if(gChains_sfmObj.pCamPrmBuf)
    {
        Int32 status;

        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, gChains_sfmObj.pCamPrmBuf, SFM_CAM_PRM_FILE_MAX_SIZE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK );
    }

    if(gChains_sfmObj.pGroundPlaneEqBuf)
    {
        Int32 status;

        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, gChains_sfmObj.pGroundPlaneEqBuf, SFM_GROUNDPLANE_EQ_FILE_MAX_SIZE);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK );
    }

    gChains_sfmObj.prevFrameId = (UInt32)-1;
    gChains_sfmObj.pCamPrmBuf = NULL;
    gChains_sfmObj.pGroundPlaneEqBuf = NULL;
}
