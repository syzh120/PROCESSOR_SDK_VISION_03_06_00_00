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
 * \file chains_csi2CalMultiCam_Sgx3Dsrv.c
 *
 * \brief  Usecase file implementation
 *
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <sys/statfs.h>
#include "chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_priv.h"
#include <src/hlos/adas/include/chains.h>
#include <src/hlos/common/chains_common.h>
#include <src/hlos/system/system_gbm_allocator.h>
#include <links_fw/src/hlos/osa/include/osa_mem.h>
#include <links_fw/src/hlos/osa/include/osa_thr.h>
#include <src/include/chains_common_osal.h>

#define CAPTURE_SENSOR_WIDTH                    (1280)
#define CAPTURE_SENSOR_HEIGHT                   (720)
#define SGX3DSRV_OUTPUT_FRAME_WIDTH             (880)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT            (1080)

/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK                (800U)

/**< Number of buffers to allocate per channel */
#define CAPTURE_NUM_BUF_PER_CH                  (4U)

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC                      (33)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC             (SYNC_DELTA_IN_MSEC * 2)

/* Car Black Box Mosaic Resolution */
#define CBB_RECORD_WIDTH                        (1280)
#define CBB_RECORD_HEIGHT                       (720)

#define MAX_NUMBER_OF_CHANNELS                  (1)

#define CBB_REC_FPS                             (30)

#define CBB_REC_FILENAME                        "/mnt/cbb/cbbRec.h264"
#define CBB_REC_IDX_FILENAME                    "/mnt/cbb/cbbRecIdx.txt"

/* Setting low priority for the file write task */
#define CBB_FILEWRITE_TSK_PRI                   (4U)
#define CBB_FILEWRITE_TSK_STACK_SIZE            (OSA_TSK_STACK_SIZE_DEFAULT)

/* File write cache buffer size */
#define CBB_WRITE_CACHE_SIZE                    (6 * MB)
#define CBB_WRITE_CACHE_SIZE_IDX                (1 * MB)
#define CBB_MMCSD_FULLSIZE_MARGIN               (64)

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraViewObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {
    /**< Link Id's and device IDs to use for this use-case */
    chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBoxObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    UInt32  appCtrlLinkId;

    UInt32  captureOutWidth;
    UInt32  captureOutHeight;

    Chains_Ctrl *chainsCfg;

    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */
    Char codecType;
    Bool firstIdrFrame;
    FILE *recFp;
    FILE *recFpIdx;
    UInt32 recCount;
    Bool recEnable;
    Bool cardFull;
    char mmcSdMnt[128U];

    UInt32 fileWriteCache;
    UInt32 fileWriteCacheIdx;
    OSA_ThrHndl fileWrThr;
    Ptr fileWriteSync;
    UInt32 cacheWritePtr;
    UInt32 cacheWriteSize;
    UInt32 fileWritePtr;
    UInt32 fileWritePtrTemp;
    UInt32 fileWriteSize;
    UInt32 cacheWritePtrIdx;
    UInt32 cacheWriteSizeIdx;
    UInt32 fileWritePtrIdx;
    UInt32 fileWritePtrTempIdx;
    UInt32 fileWriteSizeIdx;
    Bool stopFileWrite;
    Bool stopFileWriteDone;

} Chains_csi2CalMultiCam_Sgx3DsrvAppObj;

static struct control_srv_egl_ctx chainsEglParams = {
    .get_egl_native_display = gbm_allocator_get_native_display,
    .get_egl_native_buffer = gbm_allocator_get_native_buffer,
    .destroy_egl_native_buffer = gbm_allocator_destroy_native_buffer,
    .wrap_native_buffers = gbm_wrap_native_buffers,
    .wrapper_get_next_buffer = gbm_wrapper_get_next_buffer,
    .wrapper_put_buffer = gbm_wrapper_put_buffer,
    .unwrap_native_buffers = gbm_unwrap_native_buffers,
};

/* Car Black Box Run time Menu */
char gChains_cbbRunTimeMenu[] = {
    "\r\n "
    "\r\n ==========================="
    "\r\n Car Black Box Run-time Menu"
    "\r\n ==========================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n 1: Start Playback"
    "\r\n 2: Stop Playback"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/*******************************************************************************
 *  FUNCTION DECLARATION
 *******************************************************************************
 */
static Void fileSync(Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj);

/**
 *******************************************************************************
 *
 * \brief   Set SGX3DSRV Link Parameters
 *
 *          It is called in Create function.

 *
 * \param   pPrm    [IN]    IpcLink_CreateParams
 *
 *******************************************************************************
*/
static Void setSgx3DsrvLinkPrms(Sgx3DsrvLink_CreateParams *prms)
{
    prms->maxOutputHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    prms->maxOutputWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    prms->maxInputHeight = CAPTURE_SENSOR_HEIGHT;
    prms->maxInputWidth = CAPTURE_SENSOR_WIDTH;
    prms->numViews = 1;
    prms->bAnimate = 1;
    prms->numInQue = SGX3DSRV_LINK_IPQID_MAXIPQ;
    prms->inBufType[0] = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    prms->inBufType[1] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[2] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[3] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->bEglInfoInCreate = TRUE;
    prms->EglInfo = (void *)&chainsEglParams;
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          Chains_lvdsMultiVipCaptureDisplay_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void setSyncPrm(
                    SyncLink_CreateParams *pPrm,
                    UInt32 numLvdsCh)
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

/**
 *******************************************************************************
 *
 * \brief   Set Display position
 *
 *          This function is used to set the sync params.
 *          It is called in Create function. It is advisable to have
 *          Chains_lvdsMultiVipCaptureDisplay_ResetLinkPrm prior to set params
 *          so all the default params get set.
 *          Number of channels to be synced and sync delta and threshold.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void setDisplayPosition(
                    DisplayLink_CreateParams *pPrm_Video,
                    UInt32 posX,
                    UInt32 posY)
{
    pPrm_Video->rtParams.posX = posX;
    pPrm_Video->rtParams.posY = posY;
}


/**
 *******************************************************************************
 *
 * \brief   Set ISS Capture parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setCaptureParams(Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj)
{
    UInt32 idx;
    IssCaptureLink_CreateParams *pCaptPrm;
    IssCaptureLink_Csi2Params *pCsi2Prm;
    IssCaptureLink_OutParams *pOutPrm;
    System_VideoDataFormat inOutDataFormat;

    pCaptPrm = &pObj->ucObj.IssCapturePrm;
    memset((void*) pCaptPrm, 0, sizeof(IssCaptureLink_CreateParams));

    pCaptPrm->videoIfMode = SYSTEM_VIFM_SCH_CSI2;
    pCaptPrm->videoIfWidth = SYSTEM_VIFW_4LANES;
    pCaptPrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;

    for (idx = 0U; idx < ISSCAPT_LINK_MAX_CMPLXIO_INST; idx++)
    {
        pCsi2Prm = &pCaptPrm->csi2Params[idx];

        pCsi2Prm->isCmplxIoCfgValid = FALSE;
        pCsi2Prm->csi2PhyClk = CAPTURE_UB964_CSI2_CLOCK;

        pCsi2Prm->cmplxIoCfg.clockLane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.clockLane.position = 1U;
        pCsi2Prm->cmplxIoCfg.data1Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data1Lane.position = 2U;
        pCsi2Prm->cmplxIoCfg.data2Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data2Lane.position = 3U;
        pCsi2Prm->cmplxIoCfg.data3Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data3Lane.position = 4U;
        pCsi2Prm->cmplxIoCfg.data4Lane.pol      = FALSE;
        pCsi2Prm->cmplxIoCfg.data4Lane.position = 5U;
    }
    /* UB964 Can support only 1 interface*/
    pCaptPrm->csi2Params[0U].isCmplxIoCfgValid = TRUE;

    if (2U == pObj->numLanesOnPhy0Csi2)
    {
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data3Lane.position = 0U;
        pCaptPrm->csi2Params[0U].cmplxIoCfg.data4Lane.position = 0U;
    }

    pCaptPrm->numCh = pObj->numCsi2Ch;

    inOutDataFormat = SYSTEM_DF_YUV422I_YUYV;

    for (idx = 0U; idx < pCaptPrm->numCh; idx++)
    {
        pOutPrm = &pCaptPrm->outParams[idx];
        pOutPrm->width          = pObj->captureOutWidth;
        pOutPrm->height         = pObj->captureOutHeight;
        pOutPrm->dataFormat     = inOutDataFormat;
        pOutPrm->inCsi2DataFormat       = SYSTEM_CSI2_YUV422_8B;
        pOutPrm->inCsi2VirtualChanNum   = idx;
        pOutPrm->maxWidth       = pObj->captureOutWidth;
        pOutPrm->maxHeight      = pObj->captureOutHeight;
        pOutPrm->numOutBuf      = CAPTURE_NUM_BUF_PER_CH;
        pOutPrm->outDataFormat  = inOutDataFormat;
        pOutPrm->outBpp         = SYSTEM_BPP_BITS16;
    }

    pCaptPrm->allocBufferForRawDump  = FALSE;

    return;
}

/**
 *******************************************************************************
 *
 * \brief   Set VPE for CSC parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setVpePrm(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numLvdsCh,
                    UInt32 OutWidth,
                    UInt32 OutHeight)
{
    UInt32 chId;
    VpeLink_ChannelParams *chPrms;
    UInt32 outId = 0;

    pPrm->enableOut[0] = TRUE;
    for (chId = 0; chId < numLvdsCh; chId++)
    {
        chPrms = &pPrm->chParams[chId];
        chPrms->outParams[outId].numBufsPerCh = 3;

        chPrms->outParams[outId].width = OutWidth;
        chPrms->outParams[outId].height = OutHeight;
        chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV420SP_UV;

        chPrms->scCfg.bypass       = FALSE;
        chPrms->scCfg.nonLinear    = FALSE;
        chPrms->scCfg.stripSize    = 0;

        chPrms->scCropCfg.cropStartX = 0;
        chPrms->scCropCfg.cropStartY = 0;
        chPrms->scCropCfg.cropWidth  = OutWidth;
        chPrms->scCropCfg.cropHeight = OutHeight;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set SW Mosaic Algorithm parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setDmaSwMsLinkParams(
                    AlgorithmLink_DmaSwMsCreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 winWidth,
                    UInt32 winHeight,
                    UInt32 outWidth,
                    UInt32 outHeight)
{
    UInt32 algId, winId;
    UInt32 useLocalEdma;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    useLocalEdma = FALSE;
    algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

    pPrm->baseClassCreate.algId   = algId;
    pPrm->numOutBuf               = 3;
    pPrm->useLocalEdma            = useLocalEdma;
    pPrm->initLayoutParams.numWin = numCh;

    pPrm->maxOutBufWidth     = outWidth;
    pPrm->maxOutBufHeight    = outHeight;

    for(winId=0; winId<pPrm->initLayoutParams.numWin; winId++)
    {
        pWinInfo = &pPrm->initLayoutParams.winInfo[winId];
        pWinInfo->chId = winId;
        pWinInfo->inStartX = 0;
        pWinInfo->inStartY = 0;
        pWinInfo->width    = winWidth;
        pWinInfo->height   = winHeight;

        /*
         *  For 4x4 layout
         */
        switch(winId)
        {
            default:
            case 0:
                pWinInfo->outStartX = 0;
                pWinInfo->outStartY = 0;
                break;
            case 1:
                pWinInfo->outStartX = winWidth;
                pWinInfo->outStartY = 0;
                break;
            case 2:
                pWinInfo->outStartX = 0;
                pWinInfo->outStartY = winHeight;
                break;
            case 3:
                pWinInfo->outStartX = winWidth;
                pWinInfo->outStartY = winHeight;
                break;
        }
    }

    pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
    pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;
}

/**
 *******************************************************************************
 *
 * \brief   Set Encoder parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setEncPrms(
                EncLink_CreateParams *pPrm,
                Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj)
{
    int i, chId;
    EncLink_ChCreateParams *pLinkChPrm;
    EncLink_ChDynamicParams *pLinkDynPrm;

    for (i = 0; i < ENC_LINK_MAX_BUF_ALLOC_POOLS; i++)
    {
        pPrm->numBufPerCh[i] = 4U;
    }

    for (chId = 0; chId < MAX_NUMBER_OF_CHANNELS; chId++)
    {
        pLinkChPrm  = &pPrm->chCreateParams[chId];
        pLinkDynPrm = &pLinkChPrm->defaultDynamicParams;

        UTILS_assert (chId < ENC_LINK_MAX_CH);

        switch (pObj->codecType)
        {
            case '0': /* MJPEG */
                pLinkChPrm->format                 = SYSTEM_IVIDEO_MJPEG;
                pLinkChPrm->profile                = 0;
                pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
                pLinkChPrm->fieldMergeEncodeEnable = FALSE;
                pLinkChPrm->enableAnalyticinfo     = 0;
                pLinkChPrm->enableWaterMarking     = 0;
                pLinkChPrm->maxBitRate             = 0;
                pLinkChPrm->encodingPreset         = 0;
                pLinkChPrm->rateControlPreset      = 0;
                pLinkChPrm->enableHighSpeed        = 0;
                pLinkChPrm->enableSVCExtensionFlag = 0;
                pLinkChPrm->numTemporalLayer       = 0;
                pLinkChPrm->overrideInputScanFormat= 0;
                pLinkChPrm->fieldPicEncode         = 0;

                pLinkDynPrm->intraFrameInterval    = 0;
                pLinkDynPrm->targetBitRate         = (10 * 1000 * 1000);
                pLinkDynPrm->interFrameInterval    = 0;
                pLinkDynPrm->mvAccuracy            = 0;
                pLinkDynPrm->inputFrameRate        = 30;
                pLinkDynPrm->rcAlg                 = 0;
                pLinkDynPrm->qpMin                 = 0;
                pLinkDynPrm->qpMax                 = 0;
                pLinkDynPrm->qpInit                = -1;
                pLinkDynPrm->vbrDuration           = 0;
                pLinkDynPrm->vbrSensitivity        = 0;
                break;

            case '1': /* H264 */
                pLinkChPrm->format                 = SYSTEM_IVIDEO_H264HP;
                pLinkChPrm->profile                = 100;
                pLinkChPrm->dataLayout             = VENC_FIELD_SEPARATED;
                pLinkChPrm->fieldMergeEncodeEnable = FALSE;
                pLinkChPrm->enableAnalyticinfo     = 0;
                pLinkChPrm->enableWaterMarking     = 0;
                pLinkChPrm->maxBitRate             = -1;
                pLinkChPrm->encodingPreset         = SYSTEM_XDM_MED_SPEED_HIGH_QUALITY;
                /* Set to SYSTEM_XDM_USER_DEFINED if SEI/meta data needs to be enabled */
                /* pLinkChPrm->encodingPreset         = SYSTEM_XDM_USER_DEFINED; */
                pLinkChPrm->rateControlPreset      = SYSTEM_IVIDEO_LOW_DELAY;
                pLinkChPrm->enableHighSpeed        = FALSE;
                pLinkChPrm->enableSVCExtensionFlag = FALSE;
                pLinkChPrm->numTemporalLayer       = 0;
                pLinkChPrm->overrideInputScanFormat= 0;
                pLinkChPrm->fieldPicEncode         = 0;
                pLinkChPrm->IDRFrameInterval       = 1;

                pLinkDynPrm->intraFrameInterval    = 30;
                pLinkDynPrm->targetBitRate         = (10 * 1000 * 1000);
                pLinkDynPrm->interFrameInterval    = 1;
                pLinkDynPrm->mvAccuracy            = SYSTEM_IVIDENC2_MOTIONVECTOR_QUARTERPEL;
                pLinkDynPrm->inputFrameRate        = 30;
                pLinkDynPrm->rcAlg                 = 0;
                pLinkDynPrm->qpMin                 = 0;
                pLinkDynPrm->qpMax                 = 51;
                pLinkDynPrm->qpInit                = 25;
                pLinkDynPrm->vbrDuration           = 8;
                pLinkDynPrm->vbrSensitivity        = 0;
                pLinkDynPrm->maxPicSizeRatioI      = 640;
                break;

            default: /* D1 */
                printf("\r\nCodec Type: %d, returning \n", pObj->codecType);
                UTILS_assert(FALSE);
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Get the MMC/SD card free space
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static long long getMmcsdfreeSpace(const char *pDisk)
{
    long long int freespace = 0;
    struct statfs disk_statfs;

    if(statfs(pDisk, &disk_statfs) >= 0)
    {
        freespace = \
                    (((long long int)disk_statfs.f_bsize * \
                    (long long int)disk_statfs.f_bfree)/(long long int)1024);
    }

    return freespace;
}

/**
 *******************************************************************************
 *
 * \brief   Call back function from Null_isp link for saving the ISP output
 *          frames
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void encFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg)
{

    System_Buffer *pFrameBuf = (System_Buffer*)pBuf;
    System_BitstreamBuffer *pBitBuf = \
                                (System_BitstreamBuffer*)pFrameBuf->payload;
    Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj = \
                        (Chains_csi2CalMultiCam_Sgx3DsrvAppObj*)arg;
    Bool enableWrite = FALSE;
    char idxString[32U];
    UInt32 idxStrLen;
    long long int mmcsdFreeSpaceKB, cacheFullSizeKB;

    if(TRUE == pObj->recEnable)
    {
        /* Wait for an IDR frame */
        if(FALSE == pObj->firstIdrFrame)
        {
            if(1 == \
                System_Bitstream_Buffer_Flag_Get_Is_Keyframe(pBitBuf->flags))
            {
                pObj->firstIdrFrame = TRUE;
                Vps_printf(" First IDR frame found");
            }
        }

        if(TRUE == pObj->firstIdrFrame)
        {
            OSA_memCacheInv((UInt32)pBitBuf->bufAddr, pBitBuf->fillLength);

            sprintf(idxString, "%d\n",pBitBuf->fillLength);
            idxStrLen = strlen(idxString);

            mmcsdFreeSpaceKB = getMmcsdfreeSpace(pObj->mmcSdMnt);
            mmcsdFreeSpaceKB -= (CBB_MMCSD_FULLSIZE_MARGIN);
            cacheFullSizeKB = \
                (long long int)\
                (((pObj->cacheWritePtr - pObj->fileWritePtrTemp) + pBitBuf->fillLength + \
                (pObj->cacheWritePtrIdx - pObj->fileWritePtrTempIdx) + idxStrLen)/1024U);

            if(cacheFullSizeKB < mmcsdFreeSpaceKB)
            {
                if((pObj->cacheWriteSize + pBitBuf->fillLength) >= \
                                                        CBB_WRITE_CACHE_SIZE)
                {
                    /* Bitstream cache */
                    pObj->fileWriteSize = \
                                (pObj->cacheWritePtr - pObj->fileWritePtrTemp);
                    pObj->fileWritePtr = pObj->fileWritePtrTemp;
                    pObj->cacheWritePtr = pObj->fileWriteCache;
                    pObj->cacheWriteSize = 0U;
                    pObj->fileWritePtrTemp = pObj->cacheWritePtr;

                    /* Index cache */
                    pObj->fileWriteSizeIdx = \
                        (pObj->cacheWritePtrIdx - pObj->fileWritePtrTempIdx);
                    pObj->fileWritePtrIdx = pObj->fileWritePtrTempIdx;
                    pObj->cacheWritePtrIdx = pObj->fileWriteCacheIdx;
                    pObj->cacheWriteSizeIdx = 0U;
                    pObj->fileWritePtrTempIdx = pObj->cacheWritePtrIdx;

                    enableWrite = TRUE;
                }

                /* Bitstream file */
                memcpy(
                    (Ptr)ChainsCommon_Osal_getVirtAddr(pObj->cacheWritePtr),
                    pBitBuf->bufAddr,
                    pBitBuf->fillLength);

                pObj->cacheWritePtr += pBitBuf->fillLength;
                pObj->cacheWriteSize += pBitBuf->fillLength;

                /* Index file */
                memcpy(
                    (Ptr)ChainsCommon_Osal_getVirtAddr(pObj->cacheWritePtrIdx),
                    idxString,
                    idxStrLen);

                pObj->cacheWritePtrIdx += idxStrLen;
                pObj->cacheWriteSizeIdx += idxStrLen;

                if((pObj->cacheWritePtr - pObj->fileWritePtrTemp) > \
                                                        CBB_WRITE_CACHE_SIZE/2)
                {
                    /* Bitstream cache */
                    pObj->fileWriteSize = \
                                (pObj->cacheWritePtr - pObj->fileWritePtrTemp);
                    pObj->fileWritePtr = pObj->fileWritePtrTemp;
                    pObj->fileWritePtrTemp = pObj->cacheWritePtr;

                    /* index cache */
                    pObj->fileWriteSizeIdx = \
                        (pObj->cacheWritePtrIdx - pObj->fileWritePtrTempIdx);
                    pObj->fileWritePtrIdx = pObj->fileWritePtrTempIdx;
                    pObj->fileWritePtrTempIdx = pObj->cacheWritePtrIdx;

                    enableWrite = TRUE;
                }

                pObj->recCount ++;
                if(0 == (pObj->recCount % CBB_REC_FPS))
                {
                    Vps_printf(" CBB_REC: %d sec\n",(pObj->recCount/CBB_REC_FPS));
                }

                if(TRUE == enableWrite)
                {
                    ChainsCommon_Osal_mutexPost(pObj->fileWriteSync);
                }
            }
            else
            {
                Vps_printf(" CBB_REC: MMC/SD card is FULL, %lld, %lld\n",cacheFullSizeKB, mmcsdFreeSpaceKB);

                /* MMC/SD card is full */
                pObj->cardFull = TRUE;

                /* Bitstream cache */
                pObj->fileWriteSize = \
                            (pObj->cacheWritePtr - pObj->fileWritePtrTemp);
                pObj->fileWritePtr = pObj->fileWritePtrTemp;

                /* Index cache */
                pObj->fileWriteSizeIdx = \
                    (pObj->cacheWritePtrIdx - pObj->fileWritePtrTempIdx);
                pObj->fileWritePtrIdx = pObj->fileWritePtrTempIdx;

                ChainsCommon_Osal_mutexPost(pObj->fileWriteSync);
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Call back function from Null_isp link for saving the ISP output
 *          frames
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void *fileWriteTaskMain(Void *prm)
{
    Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj = \
                        (Chains_csi2CalMultiCam_Sgx3DsrvAppObj*)prm;
    UInt32 writeSize;
    UInt32 start, end;

    while(pObj->stopFileWrite == FALSE)
    {
        ChainsCommon_Osal_mutexWait(pObj->fileWriteSync);

        if(TRUE == pObj->recEnable)
        {
            start = OSA_getCurTimeInMsec();
            /* Bitstream */
            writeSize = fwrite(
                        (Ptr)ChainsCommon_Osal_getVirtAddr(pObj->fileWritePtr),
                        1U,
                        pObj->fileWriteSize,
                        pObj->recFp);

            /* Index */
            fwrite(
                (Ptr)ChainsCommon_Osal_getVirtAddr(pObj->fileWritePtrIdx),
                1U,
                pObj->fileWriteSizeIdx,
                pObj->recFpIdx);
            end = OSA_getCurTimeInMsec();
            if(writeSize != pObj->fileWriteSize)
            {
                pObj->recEnable = FALSE;
                Vps_printf(" FILE_WRITE_TSK:Bitstream file write failed ...");
            }
            else
            {
                Vps_printf(" FILE_WRITE_TSK:File written %d bytes in %d msec\n", \
                                            pObj->fileWriteSize, (end - start));
            }

            if(TRUE == pObj->cardFull)
            {
                pObj->recEnable = FALSE;
                fileSync(pObj);
                fclose(pObj->recFp);
                fclose(pObj->recFpIdx);
            }
        }
    }

    pObj->stopFileWriteDone = TRUE;

    return (OSA_SOK);
}

/**
 *******************************************************************************
 *
 * \brief   Call back function from Null_isp link for saving the ISP output
 *          frames
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setNullSrcPrms(
            Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj,
            NullSrcLink_CreateParams *pPrm)
{
    UInt32 chId;
    System_LinkChInfo *pChInfo;

    NullSrcLink_CreateParams_Init(pPrm);

    pPrm->outQueInfo.numCh = 1;

    pPrm->timerPeriodMilliSecs = (1000/CBB_REC_FPS) + 1;

    for (chId = 0; chId < pPrm->outQueInfo.numCh; chId++)
    {
        pPrm->channelParams[chId].numBuffers = 4;

        pChInfo = &pPrm->outQueInfo.chInfo[chId];

        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                                            pChInfo->flags,
                                            SYSTEM_DF_YUV420SP_UV);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
                                            pChInfo->flags,
                                            SYSTEM_SF_PROGRESSIVE);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
                                            pChInfo->flags,
                                            SYSTEM_BUFFER_TYPE_BITSTREAM);
        pChInfo->width = CBB_RECORD_WIDTH;
        pChInfo->height = CBB_RECORD_HEIGHT;
        pChInfo->startX = 0;
        pChInfo->startY = 0;
        pChInfo->pitch[0] = SystemUtils_align(pChInfo->width, 32);
        pChInfo->pitch[1] = SystemUtils_align(pChInfo->width, 32);

        pPrm->channelParams[chId].fileReadMode = NULLSRC_LINK_FILEREAD_RUN_TIME;

        strncpy(pPrm->channelParams[chId].nameDataFile, CBB_REC_FILENAME, 260);
        strncpy(pPrm->channelParams[chId].nameIndexFile, CBB_REC_IDX_FILENAME, 260);
    }

    pPrm->dataRxMode = NULLSRC_LINK_DATA_RX_MODE_FILE;

    /* The Null Source is in PAUSE mode */
    pPrm->pauseLink = TRUE;
}

/**
 *******************************************************************************
 *
 * \brief   Call back function from Null_isp link for saving the ISP output
 *          frames
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void setDecodePrms(
                    Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj,
                    DecLink_CreateParams *pPrm)
{
    UInt32 chId;
    DecLink_ChCreateParams *decPrm;

    for (chId = 0; chId < MAX_NUMBER_OF_CHANNELS; chId++)
    {
        UTILS_assert (chId < DEC_LINK_MAX_CH);
        decPrm = &pPrm->chCreateParams[chId];

        decPrm->dpbBufSizeInFrames = DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT;
        decPrm->algCreateStatus = DEC_LINK_ALG_CREATE_STATUS_CREATE;
        decPrm->decodeFrameType = DEC_LINK_DECODE_ALL;

        decPrm->processCallLevel = DEC_LINK_FRAMELEVELPROCESSCALL;
        decPrm->targetMaxWidth = CBB_RECORD_WIDTH;
        decPrm->targetMaxHeight = CBB_RECORD_HEIGHT;
        decPrm->numBufPerCh = 3;
        decPrm->defaultDynamicParams.targetBitRate = (10 * 1000 * 1000);
        decPrm->defaultDynamicParams.targetFrameRate = 30;
        decPrm->fieldMergeDecodeEnable = FALSE;

        switch (pObj->codecType)
        {
            case '0': /* MJPEG */
                decPrm->format = SYSTEM_IVIDEO_MJPEG;
                decPrm->profile = 0;
                decPrm->displayDelay = 0;
                break;

            case '1': /* H264 */
                decPrm->format = SYSTEM_IVIDEO_H264HP;
                decPrm->profile = 3;
                decPrm->displayDelay = 0;
                break;

            default: /* D1 */
                printf("\r\nCodec Type: %d, returning \n", pObj->codecType);
                UTILS_assert(FALSE);
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   File Sync
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void fileSync(Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj)
{
    Int32 fd;

    fflush(pObj->recFp);
    fflush(pObj->recFpIdx);

    /* fsync makes sure the file data in the buffer is written
        back to the media */
    fd = fileno(pObj->recFp);
    fsync(fd);

    fd = fileno(pObj->recFpIdx);
    fsync(fd);

    system("sync");
}

/**
 *******************************************************************************
 *
 * \brief   Start CBB playback
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void cbbStartPlayback(
            Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj,
            char *dataFileName,
            char *idxFileName)
{
    NullSrcLink_RestartFileParams nullSrcFileRestart;

    /* Rewind the files */
    nullSrcFileRestart.chId = 0U;
    strcpy(nullSrcFileRestart.nameDataFile, dataFileName);
    strcpy(nullSrcFileRestart.nameIndexFile, idxFileName);
    System_linkControl(
            pObj->ucObj.NullSourceLinkID,
            NULL_SRC_LINK_CMD_RESTARTFILES,
            &nullSrcFileRestart,
            sizeof(NullSrcLink_RestartFileParams),
            TRUE);

    /* Resume Null source */
    System_linkControl(
            pObj->ucObj.NullSourceLinkID,
            NULL_SRC_LINK_CMD_RESUME,
            NULL,
            0U,
            TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Stop CBB Playback
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void cbbStopPlayback(Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj)
{
    /* Puase Null source */
    System_linkControl(
            pObj->ucObj.NullSourceLinkID,
            NULL_SRC_LINK_CMD_PAUSE,
            NULL,
            0U,
            TRUE);
}

/**
 *******************************************************************************
 * *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_SetAppPrms(
        chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBoxObj *pUcObj, Void *appObj)
{
    UInt32 displayWidth,displayHeight;
    Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj
            = (Chains_csi2CalMultiCam_Sgx3DsrvAppObj*)appObj;

    UInt32 svOutWidth, svOutHeight, swWinWidth, swWinHeight;

    pObj->captureOutWidth  = CAPTURE_SENSOR_WIDTH;
    pObj->captureOutHeight = CAPTURE_SENSOR_HEIGHT;

    setCaptureParams(pObj);

    setVpePrm(
            &pUcObj->VPE_sv_cscPrm,
            pObj->chainsCfg->numLvdsCh,
            pObj->captureOutWidth,
            pObj->captureOutHeight);

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->chainsCfg->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    ChainsCommon_GetDisplayWidthHeight(
                                    pObj->chainsCfg->displayType,
                                    &displayWidth,
                                    &displayHeight);

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode,
                                    pObj->chainsCfg->enableCarOverlayInAlg);

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlign3DParams(
                                    &pUcObj->Alg_GeoAlign3DPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->chainsCfg->svOutputMode);

    setSyncPrm(
            &pUcObj->SyncPrm,
            pObj->chainsCfg->numLvdsCh);

    ChainsCommon_SetDisplayPrms(
                        &pUcObj->Display_M4Prm,
                        NULL,
                        pObj->chainsCfg->displayType,
                        SGX3DSRV_OUTPUT_FRAME_WIDTH,
                        SGX3DSRV_OUTPUT_FRAME_HEIGHT);

    setSgx3DsrvLinkPrms(&pUcObj->Sgx3DsrvPrm);

    setDisplayPosition(
                        &pUcObj->Display_M4Prm,
                        0U,
                        0U);

    ChainsCommon_StartDisplayCtrl(
                        pObj->chainsCfg->displayType,
                        SGX3DSRV_OUTPUT_FRAME_WIDTH,
                        SGX3DSRV_OUTPUT_FRAME_HEIGHT);

    /***************************************************************************
            RECORD
    ***************************************************************************/
    swWinWidth = CBB_RECORD_WIDTH/2;
    swWinHeight = CBB_RECORD_HEIGHT/2;

    setVpePrm(
            &pUcObj->VPE_swmsPrm,
            pObj->chainsCfg->numLvdsCh,
            swWinWidth,
            swWinHeight);

    setSyncPrm(
            &pUcObj->Sync_swmsPrm,
            pObj->chainsCfg->numLvdsCh);

    setDmaSwMsLinkParams(
                    &pUcObj->Alg_DmaSwMsPrm,
                    pObj->chainsCfg->numLvdsCh,
                    swWinWidth,
                    swWinHeight,
                    CBB_RECORD_WIDTH,
                    CBB_RECORD_HEIGHT);

    pObj->codecType = '1';    /* H264 */
    setEncPrms(&pUcObj->EncodePrm, pObj);

    /* Record Null link call back */
    pUcObj->Null_recPrm.appCb = encFrameCb;
    pUcObj->Null_recPrm.appCbArg = pObj;

    /**************************************************************************/

    /***************************************************************************
            PLAYBACK
    ***************************************************************************/
    setNullSrcPrms(pObj, &pUcObj->NullSourcePrm);

    setDecodePrms(pObj, &pUcObj->DecodePrm);

    /* Car Black Box Playback Display */
    pUcObj->Display_M4_pbPrm.rtParams.tarWidth = \
                                (displayWidth - SGX3DSRV_OUTPUT_FRAME_WIDTH);
    pUcObj->Display_M4_pbPrm.rtParams.tarWidth &= (~0x1);
    pUcObj->Display_M4_pbPrm.rtParams.tarHeight = \
        (pUcObj->Display_M4_pbPrm.rtParams.tarWidth * CBB_RECORD_HEIGHT)/
                CBB_RECORD_WIDTH;
    pUcObj->Display_M4_pbPrm.rtParams.tarHeight &= (~0x1);
    pUcObj->Display_M4_pbPrm.rtParams.posX = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    pUcObj->Display_M4_pbPrm.rtParams.posY = \
        (displayHeight - pUcObj->Display_M4_pbPrm.rtParams.tarHeight)/2;
    pUcObj->Display_M4_pbPrm.displayId = DISPLAY_LINK_INST_DSS_VID2;
    /**************************************************************************/

    /* Enable clock for the CAL and CSI2 */
    system("omapconf write 0x4A009028 0x00040001");
    system("msleep 10");
    system("omapconf write 0x4A009038 0x00030000");
    system("msleep 10");
}

/**
 *******************************************************************************
 *
 * \brief   Start the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_csi2CalMultiCam_Sgx3DsrvAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
void chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_StartApp(
                                    Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj)
{
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = pObj->chainsCfg->numLvdsCh;

    ChainsCommon_statCollectorReset();
    ChainsCommon_memPrintHeapStatus();

    /* UB964 Init */
    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_UB964_OV1063X;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);

    chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_Start(&pObj->ucObj);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the capture display Links
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_csi2CalMultiCam_Sgx3DsrvAppObj
 *
 *******************************************************************************
*/
void chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_StopApp(
                                    Chains_csi2CalMultiCam_Sgx3DsrvAppObj *pObj)
{
    chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_Stop(&pObj->ucObj);

    chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();

    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_UB964_OV1063X;
    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                        APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
                        &pObj->vidSensorPrm,
                        sizeof(VideoSensorCreateAndStartAppPrm),
                        TRUE);

    ChainsCommon_prfLoadCalcEnable(FALSE, FALSE, FALSE);

}

/**
 *******************************************************************************
 *
 * \brief   Unmount FAT File System
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void unmountFatFs()
{
    char cmd[128U];

    sprintf(cmd, "umount /%s",MMCSD_MOUNT_PT);

    /* Unmount the SD card */
    system(cmd);
}

/**
 *******************************************************************************
 *
 * \brief   Mount the FAT File System
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void mountFatFs()
{
    char cmd[128U];

    sprintf(cmd, "mount /dev/disk/by-path/platform-4809c000.mmc-part1 /%s",\
                                                            MMCSD_MOUNT_PT);

    /* Mount the SD card */
    system(cmd);
}

/**
 *******************************************************************************
 *
 * \brief   Single Channel Capture Display usecase function
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox(Chains_Ctrl *chainsCfg)
{
    char ch, chPrev;
    UInt32 done = FALSE;
    Bool startWithCalibration;
    Chains_csi2CalMultiCam_Sgx3DsrvAppObj chainsObj;
    Int32 status;

    chainsObj.chainsCfg = chainsCfg;
    chPrev = '1';

    chainsObj.chainsCfg->numLvdsCh = 4;

    mountFatFs();

    /* File write cache memory */
    chainsObj.fileWriteCache = (UInt32)ChainsCommon_Osal_memAlloc(
                                                    CBB_WRITE_CACHE_SIZE,
                                                    128U);
    UTILS_assert(0x0 != chainsObj.fileWriteCache);

    chainsObj.cacheWritePtr = chainsObj.fileWritePtr = \
                        chainsObj.fileWritePtrTemp = chainsObj.fileWriteCache;
    chainsObj.cacheWriteSize = chainsObj.fileWriteSize = 0;

    /* Index file cache memory */
    chainsObj.fileWriteCacheIdx = (UInt32)ChainsCommon_Osal_memAlloc(
                                                    CBB_WRITE_CACHE_SIZE_IDX,
                                                    128U);
    UTILS_assert(0x0 != chainsObj.fileWriteCacheIdx);

    chainsObj.cacheWritePtrIdx = chainsObj.fileWritePtrIdx = \
                chainsObj.fileWritePtrTempIdx = chainsObj.fileWriteCacheIdx;
    chainsObj.cacheWriteSizeIdx = chainsObj.fileWriteSizeIdx = 0;

    chainsObj.fileWriteSync = ChainsCommon_Osal_mutexCreate();
    UTILS_assert(NULL != chainsObj.fileWriteSync);

    chainsObj.stopFileWrite = FALSE;

    /* Create file write task */
    status = OSA_thrCreate(
                        &chainsObj.fileWrThr,
                        fileWriteTaskMain,
                        CBB_FILEWRITE_TSK_PRI,
                        CBB_FILEWRITE_TSK_STACK_SIZE,
                        &chainsObj);
    OSA_assert(status == OSA_SOK);

    /* Create the bitstream and index files */
    system("mkdir /mnt/cbb");
    chainsObj.recEnable = TRUE;
    chainsObj.cardFull = FALSE;
    chainsObj.recFp = fopen(CBB_REC_FILENAME, "wb");
    chainsObj.recFpIdx = fopen(CBB_REC_IDX_FILENAME, "wb");
    sprintf(chainsObj.mmcSdMnt, "/%s", MMCSD_MOUNT_PT);

    if((NULL != chainsObj.recFp) && (NULL != chainsObj.recFpIdx))
    {
        do
        {
            /*  On TDA2EX
                4 Channels of 1.2 MP video could be received on 2 lanes, following
                changes would be required
                1. Set numLanesOnPhy0Csi2 to 2
                2. Set UB960 to stream on 2 lanes

                On J6 Entry
                There are only 2 lanes available, set numLanesOnPhy0Csi2 to 2
                UB960 is configured for 2 lanes for J6 E
             */
#ifdef TDA2EX_17X17
            chainsObj.numLanesOnPhy0Csi2 = 2U;
#else
            chainsObj.numLanesOnPhy0Csi2 = 4U;
#endif
            chainsObj.numCsi2Ch = chainsObj.chainsCfg->numLvdsCh;

            done = FALSE;
            /* Set startWithCalibration = TRUE to start the demo with calibration.
               Else it will use the previously calibrated LUTs */
            startWithCalibration = TRUE;
            ChainsCommon_SurroundView_CalibInit(
                                        startWithCalibration,
                                        chainsObj.chainsCfg->svOutputMode);

            if(ALGLINK_GALIGN3D_CALMODE_FORCE_USERGASGXLUT != \
              (AlgorithmLink_GAlign3DCalibrationMode)\
                                            ChainsCommon_SurroundView_getCalMode())
            {
                Vps_printf(" CHAINS: -------------------------------------------------------------------- \n");
                Vps_printf(" CHAINS: Calibrated SGX LUT is NOT present \n");
                Vps_printf(" CHAINS: Generate SGX LUT by running the 'Surround View Calibration' use case \n");
                Vps_printf(" CHAINS: -------------------------------------------------------------------- \n");

                ChainsCommon_SurroundView_CalibDeInit();

                return;
            }

            chainsObj.firstIdrFrame = FALSE;
            chainsObj.recCount = 0;

            chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_Create(&chainsObj.ucObj, &chainsObj);

            chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_StartApp(&chainsObj);

            ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

            while(!done)
            {
                Vps_printf(gChains_cbbRunTimeMenu);
                ch = Chains_readChar();

                switch(ch)
                {
                    case '0':
                        chPrev = ChainsCommon_SurroundView_MenuCalibration();
                        done = TRUE;
                        break;

                    case '1':
                        cbbStartPlayback(
                                    &chainsObj,
                                    CBB_REC_FILENAME,
                                    CBB_REC_IDX_FILENAME);
                        break;

                    case '2':
                        cbbStopPlayback(&chainsObj);
                        break;

                    case 'p':
                    case 'P':
                        ChainsCommon_PrintStatistics();
                        chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_printStatistics(&chainsObj.ucObj);
                        chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_printBufferStatistics(&chainsObj.ucObj);
                        break;
                    default:
                        Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                        break;
                }
            }

            chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox_StopApp(&chainsObj);

            ChainsCommon_SurroundView_CalibDeInit();

        } while(chPrev != '3');
    }
    else
    {
        Vps_printf(" Cannot create output files for Car Black Box");
    }

    chainsObj.fileWriteSize = \
                        (chainsObj.cacheWritePtr - chainsObj.fileWritePtrTemp);
    chainsObj.fileWritePtr = chainsObj.fileWritePtrTemp;
    chainsObj.fileWriteSizeIdx = \
            (chainsObj.cacheWritePtrIdx - chainsObj.fileWritePtrTempIdx);
    chainsObj.fileWritePtrIdx = chainsObj.fileWritePtrTempIdx;

    chainsObj.stopFileWriteDone = FALSE;
    chainsObj.stopFileWrite = TRUE;
    ChainsCommon_Osal_mutexPost(chainsObj.fileWriteSync);

    /* Wait for file write thread to exit */
    do
    {
        usleep(1000);
    }
    while(FALSE == chainsObj.stopFileWriteDone);

    if(TRUE == chainsObj.recEnable)
    {
        fileSync(&chainsObj);
        fclose(chainsObj.recFp);
        fclose(chainsObj.recFpIdx);
    }

    OSA_thrDelete(&chainsObj.fileWrThr);
    ChainsCommon_Osal_mutexDelete(chainsObj.fileWriteSync);
    ChainsCommon_Osal_memFree(
                    (Ptr)chainsObj.fileWriteCache, CBB_WRITE_CACHE_SIZE);
    ChainsCommon_Osal_memFree(
                    (Ptr)chainsObj.fileWriteCacheIdx, CBB_WRITE_CACHE_SIZE_IDX);

    unmountFatFs();
}


