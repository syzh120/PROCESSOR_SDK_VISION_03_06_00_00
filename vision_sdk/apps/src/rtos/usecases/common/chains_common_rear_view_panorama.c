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

#ifndef _chains_vipStereoCameraDisplay_Defines_H_
#define _chains_vipStereoCameraDisplay_Defines_H_


#include <src/include/chains_common.h>
#include <src/rtos/utils_common/include/utils_tsk.h>


#define SYNC_DELTA_IN_MSEC                    (16)
#define SYNC_DROP_THRESHOLD_IN_MSEC           (33)
#define LINK_NUM_BUFFERS                      (6)
#define LINK_NUM_BUFFERS_IT                   (6)



////////////////////////////////////////////////////////////////////////
// Defines

////////////////////////////////////////////////////////////////////////
// Panorama Specific Defines
 
#define RVP_DATA_FORMAT                                         (SYSTEM_DF_YUV420SP_UV)
#define DISPLAY_OUTPUT_WIDTH                                    (1920)
#define DISPLAY_OUTPUT_HEIGHT                                   (1080)
#define PANORAMA_OUTPUT_POSX                                    (0)
#define PANORAMA_OUTPUT_POSY                                    (120)
    
#define LVDS_CAPTURE_WIDTH                                      (1280)
#define LVDS_CAPTURE_HEIGHT                                     (720)

#define IMAGE_TRANSFORM_INPUT_WIDTH           	                (LVDS_CAPTURE_WIDTH)
#define IMAGE_TRANSFORM_INPUT_HEIGHT           	                (LVDS_CAPTURE_HEIGHT)
#define IMAGE_TRANSFORM_OUTPUT_WIDTH                            (1920)
#define IMAGE_TRANSFORM_OUTPUT_HEIGHT                           (480)
#define	NUM_CAMERAS                                             (4)
#define NUM_CAPTURE_CH                                          (4)

#define TIGHT_SYNC_DELTA_IN_MSEC                                (16)
#define LOOSE_SYNC_DELTA_IN_MSEC                                (0x7FFFFFFF)

#define TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC                       (33)
#define LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC                       (0x7FFFFFFF)


////////////////////////////////////////////////////////////////////////
// Stereo Disparity Algorithm Defines	

#define ALIGN(a,b) ((((a) + ((1<<(b)) - 1)) >> (b)) <<(b))

#define DISPARITY_TI_LEFT_TO_RIGHT                              0
#define DISPARITY_TI_RIGHT_TO_LEFT                              1

#define CAPTURE_SENSOR_WIDTH                                    1280
#define CAPTURE_SENSOR_HEIGHT                                   720

#define STEREO_OUTPUT_WIDTH                                     640
#define STEREO_OUTPUT_HEIGHT                                    360

#define STEREO_CALIB_LUT_QSPI_OFFSET                            (29U*1024U*1024U)
#define STEREO_CALIB_LUT_HEADER_SIZE                            (16U)
#define STEREO_CALIB_LUT_TAG_ID                                 (0x00CCAABBU)

/** Post Processing */

// Original Defines	
#define POSTPROC_COST_MAX_THRESHOLD                             85
#define POSTPROC_CONF_MIN_THRSESHOLD                            98
#define POSTPROC_HOLEFILLING_STRENGTH                           0
#define POSTPROC_TEXTURE_LUMALOTHRESH                           0
#define POSTPROC_TEXTURE_LUMAHITHRESH                           100
#define POSTPROC_TEXTURE_THRESHOLD                              90
#define POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD                    255 //(L/R check)
#define POSTPROC_MAX_DISP_DISSIMILARITY                         0
#define POSTPROC_MIN_CONFIDENT_N_SEG                            0
#define POSTPROC_TEMPORAL_FILTER_NUM_FRAMES                     3
#define POSTPROC_MIN_DISPARITY_DISPLAY                          0
#define POSTPROC_COLORMAP_INDEX                                 0

// RVP Specific Defines
#define POSTPROC_IMAGE_WIDTH                                    LVDS_CAPTURE_WIDTH
#define POSTPROC_IMAGE_HEIGHT                                   LVDS_CAPTURE_HEIGHT
#define POSTPROC_CROP_STARTX                                    0
#define POSTPROC_CROP_STARTY                                    0
#define POSTPROC_CROP_WIDTH                                     STEREO_OUTPUT_WIDTH
#define POSTPROC_CROP_HEIGHT                                    STEREO_OUTPUT_HEIGHT



/** Remap */

// Original Defines	
#define REMAP_OUTPUT_BLOCK_WIDTH                                16 //128
#define REMAP_OUTPUT_BLOCK_HEIGHT                               16 //8

// RVP Specific Defines	
#define REMAP_IMAGE_WIDTH                                       736 //800 // Original Define called REMAP_WIDTH
#define REMAP_IMAGE_HEIGHT                                      384 // Original Define called REMAP_HEIGHT
#define REMAP_CROP_STARTX                                       0
#define REMAP_CROP_STARTY                                       0
#define REMAP_CROP_WIDTH                                   	    CAPTURE_SENSOR_WIDTH 
#define REMAP_CROP_HEIGHT                                   	CAPTURE_SENSOR_HEIGHT


/** Disparity */

// Original Defines	
#define NUM_DISPARITIES                                         64 //128
#define DISPARITY_STEP_SIZE                                     2 //4
#define DISPARITY_OUTPUT_ROI_WIDTH                              640
#define DISPARITY_OUTPUT_ROI_HEIGHT                             360
#define DISPARITY_INPUT_BIT_DEPTH                               32
#define DISPARITY_WIN_WIDTH                                     11
#define DISPARITY_WIN_HEIGHT                                    11
#define DISPARITY_SEARCH_DIR                                    DISPARITY_TI_LEFT_TO_RIGHT
#define DISPARITY_EXRA_RIGHT_LEFT_DISP_MAP                      0 //(1- L/R check)

// RVP Specific Defines
#define DISPARITY_IMAGE_WIDTH                                   640
#define DISPARITY_IMAGE_HEIGHT                                  360
#define DISPARITY_CROP_STARTX                                   0
#define DISPARITY_CROP_STARTY                                   0
#define DISPARITY_CROP_WIDTH                                    LVDS_CAPTURE_WIDTH
#define DISPARITY_CROP_HEIGHT                                   LVDS_CAPTURE_HEIGHT
#define DISPARITY_OUTPUT_WIDTH                                  REMAP_IMAGE_WIDTH
#define DISPARITY_OUTPUT_HEIGHT                                 REMAP_IMAGE_HEIGHT
#define DISPARITY_OUTPUT_POSX                                   (DISPLAY_OUTPUT_WIDTH/2 - DISPARITY_OUTPUT_WIDTH/2)
#define DISPARITY_OUTPUT_POSY                                   (DISPLAY_OUTPUT_HEIGHT*3/4 - DISPARITY_OUTPUT_HEIGHT/2)



/** Census */

#define CENSUS_INPUT_BIT_DEPTH                                  8
#define CENSUS_WIN_WIDTH                                        9
#define CENSUS_WIN_HEIGHT                                       9
#define CENSUS_WIN_HORZ_STEP                                    2
#define CENSUS_WIN_VERT_STEP                                    2




////////////////////////////////////////////////////////////////////////
// Structs

/** RVP_Stereo_ImageDims */	
typedef struct
{
    UInt32 disparityOutputRoiWidth; /* Input parameter */
    UInt32 disparityOutputRoiHeight; /* Input parameter */
    UInt32 disparityInputImageWidth;
    UInt32 disparityInputImageHeight;
    UInt32 disparityInputLeftImageStartX;
    UInt32 disparityInputLeftImageStartY;
    UInt32 disparityInputRightImageStartX;
    UInt32 disparityInputRightImageStartY;
    
    UInt32 censusOutputRoiWidth;
    UInt32 censusOutputRoiHeight;
    UInt32 censusInputImageWidth;
    UInt32 censusInputImageHeight;
    UInt32 censusInputImageStartX;
    UInt32 censusInputImageStartY;
    
    UInt32 remapImageWidth;
    UInt32 remapImageHeight;
    
    UInt32 origRoiStartX;
    UInt32 origRoiStartY;
} RVP_Stereo_ImageDims;
/** RVP_Stereo_ConfigurableCreateParams */
typedef struct
{
    UInt32              numDisparities;
    
    UInt32              disparityStepSize;
    Uint32              disparitySearchDir;
    UInt32              disparitySupportWinWidth;
    UInt32              disparitySupportWinHeight;
    
    UInt32              leftRightCheckEna;
    
    UInt32              censusWinWidth;
    UInt32              censusWinHeight;
    UInt32              censusWinHorzStep;
    UInt32              censusWinVertStep;
    
    UInt32              postproc_colormap_index;
} RVP_Stereo_ConfigurableCreateParams;

RVP_Stereo_ConfigurableCreateParams pRVPStereoParams;
RVP_Stereo_ImageDims pRVPStereoImDims;


////////////////////////////////////////////////////////////////////////
// Local Functions

static void ChainsCommon_RVP_SetSyncPrm( SyncLink_CreateParams *pPrm,
                                         UInt32 syncMode)
{
    if(syncMode == 1)
    {
        pPrm->syncDelta = TIGHT_SYNC_DELTA_IN_MSEC;
        pPrm->syncThreshold = TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC;
    }
    else
    {
        pPrm->syncDelta = LOOSE_SYNC_DELTA_IN_MSEC;
        pPrm->syncThreshold = LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC;
    }

}

static void ChainsCommon_RVP_SetDisplayPrm( DisplayLink_CreateParams *pDisplay_PanoramaPrm,
                                            DisplayLink_CreateParams *pDisplay_DisparityPrm,
                                            DisplayLink_CreateParams *pDisplay_GrpxPrm,
                                            UInt32 displayWidth,
                                            UInt32 displayHeight)
{
	DisplayLink_CreateParams *pPrm;
    float displayWidthScale = 1;
    float displayHeightScale = 1;
    UInt32 disparity_outputWidth, panorama_outputWidth;
    UInt32 disparity_outputHeight, panorama_outputHeight;
    UInt32 disparity_posX, panorama_posX;
    UInt32 disparity_posY, panorama_posY;

    displayWidthScale = (1920.0)/displayWidth;
    displayHeightScale = (1080.0)/displayHeight;
    panorama_outputWidth = IMAGE_TRANSFORM_OUTPUT_WIDTH;
    panorama_outputHeight = IMAGE_TRANSFORM_OUTPUT_HEIGHT;
    disparity_outputWidth = DISPARITY_OUTPUT_WIDTH;
    disparity_outputHeight = DISPARITY_OUTPUT_HEIGHT;
    panorama_posX = PANORAMA_OUTPUT_POSX;
    panorama_posY = PANORAMA_OUTPUT_POSY;
    disparity_posX = DISPARITY_OUTPUT_POSX;
    disparity_posY = DISPARITY_OUTPUT_POSY;

    if(pDisplay_PanoramaPrm){
        pPrm                        = pDisplay_PanoramaPrm;
        pPrm->rtParams.tarWidth     = (float)panorama_outputWidth  / displayWidthScale;
        pPrm->rtParams.tarHeight    = (float)panorama_outputHeight / displayHeightScale;
        pPrm->rtParams.posX         = (float)panorama_posX / displayWidthScale;
        pPrm->rtParams.posY         = (float)panorama_posY / displayHeightScale;
        pPrm->displayId             = DISPLAY_LINK_INST_DSS_VID1;}
    if(pDisplay_DisparityPrm){
        pPrm = pDisplay_DisparityPrm;
        pPrm->rtParams.tarWidth     = (float)disparity_outputWidth  / displayWidthScale;
        pPrm->rtParams.tarHeight    = (float)disparity_outputHeight / displayHeightScale;
        pPrm->rtParams.posX         = (float)disparity_posX / displayWidthScale;
        pPrm->rtParams.posY         = (float)disparity_posY / displayHeightScale;
        pPrm->displayId             = DISPLAY_LINK_INST_DSS_VID2;}
    if(pDisplay_GrpxPrm){
        pPrm = pDisplay_GrpxPrm;
        pPrm->rtParams.tarWidth     = displayWidth;
        pPrm->rtParams.tarHeight    = displayHeight;
        pPrm->rtParams.posX         = 0;
        pPrm->rtParams.posY         = 0;
        pPrm->displayId             = DISPLAY_LINK_INST_DSS_GFX1;}
}

static void ChainsCommon_RVP_SetVpePrm(     VpeLink_CreateParams *pVPE_RemapInPrm,
                                            VpeLink_CreateParams *pVPE_PostProcOutPrm,
                                            VpeLink_CreateParams *pVPE_ImgTransformOutPrm,
                                            VpeLink_CreateParams *pVPE_ImgTransformInPrm)
{
    VpeLink_CreateParams *pPrm;
    VpeLink_ChannelParams *chPrms;
    /*UInt32 chId;
    UInt32 outId = 0;*/

    if(pVPE_RemapInPrm){
        pVPE_RemapInPrm->enableOut[0] = TRUE;
        pPrm = pVPE_RemapInPrm;
        chPrms = &pPrm->chParams[0];
        chPrms->outParams[0].numBufsPerCh = VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
        chPrms->outParams[0].width 	  	  = REMAP_IMAGE_WIDTH;
        chPrms->outParams[0].height       = REMAP_IMAGE_HEIGHT;
        chPrms->outParams[0].dataFormat   = RVP_DATA_FORMAT;

        chPrms->scCropCfg.cropStartX = REMAP_CROP_STARTX;
        chPrms->scCropCfg.cropStartY = REMAP_CROP_STARTX;
        chPrms->scCropCfg.cropWidth  = REMAP_CROP_WIDTH;
        chPrms->scCropCfg.cropHeight = REMAP_CROP_HEIGHT;
      }


    /*for(chId = 0; chId < 2; chId++){
        if(pVPE_RemapInPrm){
            pVPE_RemapInPrm->enableOut[0] = TRUE;
            pPrm = pVPE_RemapInPrm;
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh = VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
            chPrms->outParams[outId].width 	  	  = REMAP_IMAGE_WIDTH;
            chPrms->outParams[outId].height       = REMAP_IMAGE_HEIGHT;
            chPrms->outParams[outId].dataFormat   = RVP_DATA_FORMAT;

            chPrms->scCropCfg.cropStartX = REMAP_CROP_STARTX;
            chPrms->scCropCfg.cropStartY = REMAP_CROP_STARTX;
            //CAPTURE_SENSOR_WIDTH;
            chPrms->scCropCfg.cropWidth  = REMAP_CROP_WIDTH;
            //CAPTURE_SENSOR_HEIGHT;
            chPrms->scCropCfg.cropHeight = REMAP_CROP_HEIGHT;}
        if(pVPE_PostProcOutPrm){
            pVPE_PostProcOutPrm->enableOut[0] = TRUE;
            pPrm = pVPE_PostProcOutPrm;
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh = VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
            chPrms->outParams[outId].width 		  = POSTPROC_IMAGE_WIDTH;
            chPrms->outParams[outId].height 	  = POSTPROC_IMAGE_HEIGHT;
            chPrms->outParams[outId].dataFormat   = RVP_DATA_FORMAT;

            chPrms->scCropCfg.cropStartX = POSTPROC_CROP_STARTX;
            chPrms->scCropCfg.cropStartY = POSTPROC_CROP_STARTY;
            chPrms->scCropCfg.cropWidth  = POSTPROC_CROP_WIDTH;
            chPrms->scCropCfg.cropHeight = POSTPROC_CROP_HEIGHT;}
        if(pVPE_ImgTransformOutPrm){
            pVPE_ImgTransformOutPrm->enableOut[0] = TRUE;
            pPrm = pVPE_ImgTransformOutPrm;
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh = VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
            chPrms->outParams[outId].width        = DISPARITY_IMAGE_WIDTH;
            chPrms->outParams[outId].height       = DISPARITY_IMAGE_HEIGHT;
            chPrms->outParams[outId].dataFormat   = RVP_DATA_FORMAT;
            chPrms->scCropCfg.cropStartX = DISPARITY_CROP_STARTX;
            chPrms->scCropCfg.cropStartY = DISPARITY_CROP_STARTY;
            chPrms->scCropCfg.cropWidth  = DISPARITY_CROP_WIDTH;
            chPrms->scCropCfg.cropHeight = DISPARITY_CROP_HEIGHT;}
        if(pVPE_ImgTransformInPrm){
            pVPE_ImgTransformInPrm->enableOut[0] = TRUE;
            pPrm = pVPE_ImgTransformInPrm;
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh = VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
            chPrms->outParams[outId].width        = 1280;
            chPrms->outParams[outId].height       = 720;
            chPrms->outParams[outId].dataFormat   = RVP_DATA_FORMAT;
            chPrms->scCropCfg.cropStartX = 0;
            chPrms->scCropCfg.cropStartY = 0;
            chPrms->scCropCfg.cropWidth  = 896;
            chPrms->scCropCfg.cropHeight = 384;}

            }*/
}

static void ChainsCommon_RVP_SetSelectPrm(  SelectLink_CreateParams *pSelect_DisparityPrm,
                                            SelectLink_CreateParams *pSelect_PanoramaPrm)
{
    SelectLink_CreateParams *pPrm;

    if(pSelect_DisparityPrm){
        pPrm                             = pSelect_DisparityPrm;
        pPrm->numOutQue                  = 1;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 2;
        pPrm->outQueChInfo[0].inChNum[0] = 2;
        pPrm->outQueChInfo[0].inChNum[1] = 1;}
    if(pSelect_PanoramaPrm){
        pPrm                             = pSelect_PanoramaPrm;
        pPrm->numOutQue                  = 1;
        pPrm->outQueChInfo[0].outQueId   = 0;
        pPrm->outQueChInfo[0].numOutCh   = 3;
        pPrm->outQueChInfo[0].inChNum[0] = 0;
        pPrm->outQueChInfo[0].inChNum[1] = 1;
        pPrm->outQueChInfo[0].inChNum[2] = 3;
    }
}


static void ChainsCommon_RVP_SetAlgDmaSwMsPrm(  AlgorithmLink_DmaSwMsCreateParams *pPrm,
                                                UInt32 outputWidth,
                                                UInt32 outputHeight)
{
    UInt32 algId;
    AlgorithmLink_DmaSwMsLayoutWinInfo *pWinInfo;

    if(pPrm){
        algId = ALGORITHM_LINK_IPU_ALG_DMA_SWMS;

        pPrm->baseClassCreate.algId     = algId;
        pPrm->maxOutBufWidth            = outputWidth;
        pPrm->maxOutBufHeight           = outputHeight;
        pPrm->numOutBuf                 = 4;
        pPrm->useLocalEdma              = FALSE;

        pPrm->initLayoutParams.numWin       = 1;
        pPrm->initLayoutParams.outBufWidth  = pPrm->maxOutBufWidth;
        pPrm->initLayoutParams.outBufHeight = pPrm->maxOutBufHeight;

        pWinInfo = &pPrm->initLayoutParams.winInfo[0];
        pWinInfo->chId 		= 0;
        pWinInfo->inStartX  = 0;
        pWinInfo->inStartY  = 0;
        pWinInfo->width     = outputWidth;
        pWinInfo->height    = outputHeight;
        pWinInfo->outStartX = 0;
        pWinInfo->outStartY = 0;}
}

static void ChainsCommon_RVP_SetGrpxSrcPrms(    GrpxSrcLink_CreateParams *pPrm,
                                                UInt32 displayWidth,
                                                UInt32 displayHeight,
                                                Bool enableDisparityLayout,
                                                Bool enableCarOverlay)
{
    if(pPrm){
        pPrm->grpxBufInfo.dataFormat    = SYSTEM_DF_BGR16_565;
        pPrm->grpxBufInfo.height        = displayHeight;
        pPrm->grpxBufInfo.width         = displayWidth;

        pPrm->enableRearViewPanoramaLayout  = TRUE;
        pPrm->statsDisplayEnable            = TRUE;
        pPrm->enableRVPDisparityLayout      = enableDisparityLayout;
        pPrm->enableCarOverlay              = enableCarOverlay;}
}


////////////////////////////////////////////////////////////////////////
// RVP Specific Functions

static void ChainsCommon_RVP_SetImageTransformAlgPrms(  AlgorithmLink_ImageTransformCreateParams    *pPrm,
                                                UInt16                                      inputWidth,
                                                UInt16                                      inputHeight,
                                                UInt16                                      outputWidth,
                                                UInt16                                      outputHeight,
                                                unsigned char                               imageTransformMode)
{
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_IMAGETRANSFORM;
    pPrm->maxOutputWidth        = outputWidth;
    pPrm->maxOutputHeight       = outputHeight;
    pPrm->maxInputWidth         = inputWidth;
    pPrm->maxInputHeight        = inputHeight;
    pPrm->numCameras            = NUM_CAMERAS;
    pPrm->dataFormat            = RVP_DATA_FORMAT;
    pPrm->numOutBuffers = LINK_NUM_BUFFERS_IT;
    pPrm->imageTransformMode    = imageTransformMode;
}

static void ChainsCommon_RVP_SetSeamDetectionAlgPrms(   AlgorithmLink_SeamDetectionCreateParams     *pPrm,
                                                UInt16                                      inputWidth,
                                                UInt16                                      inputHeight,
                                                UInt16                                      outputWidth,
                                                UInt16                                      outputHeight,
                                                unsigned char                               seamDetectionMode)
{
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_SEAMDETECTION;
    pPrm->maxOutputWidth        = outputWidth;
    pPrm->maxOutputHeight       = outputHeight;
    pPrm->maxInputWidth         = inputWidth;
    pPrm->maxInputHeight        = inputHeight;
    pPrm->numCameras            = NUM_CAMERAS;
    pPrm->dataFormat            = RVP_DATA_FORMAT;
    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
    pPrm->seamDetectionMode     = seamDetectionMode;
}

static void ChainsCommon_RVP_SetStitchingAlgPrms(   AlgorithmLink_StitchingCreateParams     *pPrm,
                                                UInt16                                      inputWidth,
                                                UInt16                                      inputHeight,
                                                UInt16                                      outputWidth,
                                                UInt16                                      outputHeight,
                                                unsigned char                               stitchingMode)
{
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_STITCHING;
    pPrm->maxOutputWidth        = outputWidth;
    pPrm->maxOutputHeight       = outputHeight;
    pPrm->maxInputWidth         = inputWidth;
    pPrm->maxInputHeight        = inputHeight;
    pPrm->numCameras            = NUM_CAMERAS;
    pPrm->dataFormat            = RVP_DATA_FORMAT;
    pPrm->numOutBuffers         = LINK_NUM_BUFFERS;
    pPrm->stitchingMode         = stitchingMode;
}
////////////////////////////////////////////////////////////////////////
// Disparity Specific Functions


static void ChainsCommon_RVP_initImageDims(RVP_Stereo_ImageDims *imDim, RVP_Stereo_ConfigurableCreateParams *pStereoParams)
{
    {
        pRVPStereoParams.numDisparities             = NUM_DISPARITIES;

        pRVPStereoParams.disparitySearchDir         = DISPARITY_SEARCH_DIR;
        pRVPStereoParams.disparityStepSize          = DISPARITY_STEP_SIZE;
        pRVPStereoParams.disparitySupportWinWidth   = DISPARITY_WIN_WIDTH;
        pRVPStereoParams.disparitySupportWinHeight  = DISPARITY_WIN_HEIGHT;

        pRVPStereoParams.leftRightCheckEna          = DISPARITY_EXRA_RIGHT_LEFT_DISP_MAP;

        pRVPStereoParams.censusWinWidth             = CENSUS_WIN_WIDTH;
        pRVPStereoParams.censusWinHeight            = CENSUS_WIN_HEIGHT;
        pRVPStereoParams.censusWinHorzStep          = CENSUS_WIN_HORZ_STEP;
        pRVPStereoParams.censusWinVertStep          = CENSUS_WIN_VERT_STEP;

        pRVPStereoParams.postproc_colormap_index    = POSTPROC_COLORMAP_INDEX;

        pRVPStereoImDims.disparityOutputRoiWidth  = STEREO_OUTPUT_WIDTH;
        pRVPStereoImDims.disparityOutputRoiHeight = STEREO_OUTPUT_HEIGHT;
    
        pRVPStereoImDims.remapImageWidth  = REMAP_IMAGE_WIDTH;
        pRVPStereoImDims.remapImageHeight = REMAP_IMAGE_HEIGHT;
    }
        
    imDim->disparityInputImageWidth= ALIGN(imDim->disparityOutputRoiWidth + pStereoParams->numDisparities - 1 + pStereoParams->disparitySupportWinWidth - 1, 4);
    imDim->disparityInputImageHeight= ALIGN(imDim->disparityOutputRoiHeight + pStereoParams->disparitySupportWinHeight - 1, 3);

    if (pStereoParams->disparitySearchDir== DISPARITY_TI_RIGHT_TO_LEFT) {
        imDim->disparityInputLeftImageStartX= ((pStereoParams->disparitySupportWinWidth - 1) >> 1);
    }
    else {
        imDim->disparityInputLeftImageStartX= pStereoParams->numDisparities - 1 + ((pStereoParams->disparitySupportWinWidth - 1) >> 1);
    }

    imDim->disparityInputLeftImageStartY= ((pStereoParams->disparitySupportWinHeight - 1) >> 1);

    imDim->disparityInputRightImageStartX= ((pStereoParams->disparitySupportWinWidth - 1) >> 1);
    imDim->disparityInputRightImageStartY= ((pStereoParams->disparitySupportWinHeight - 1) >> 1);

    imDim->censusOutputRoiWidth= imDim->disparityInputImageWidth;
    imDim->censusOutputRoiHeight= imDim->disparityInputImageHeight;

    if (imDim->remapImageWidth== 0 || imDim->remapImageHeight== 0) {

        imDim->censusInputImageWidth= imDim->censusOutputRoiWidth + pStereoParams->censusWinWidth - 1;
        /* round up to multiple of REMAP_OUTPUT_BLOCK_WIDTH */
        imDim->censusInputImageWidth= ((imDim->censusInputImageWidth + (REMAP_OUTPUT_BLOCK_WIDTH-1))/REMAP_OUTPUT_BLOCK_WIDTH)*REMAP_OUTPUT_BLOCK_WIDTH;

        imDim->censusInputImageHeight= imDim->censusOutputRoiHeight + pStereoParams->censusWinHeight - 1;
        /* round up to multiple of REMAP_OUTPUT_BLOCK_HEIGHT */
        imDim->censusInputImageHeight= ((imDim->censusInputImageHeight + (REMAP_OUTPUT_BLOCK_HEIGHT-1))/REMAP_OUTPUT_BLOCK_HEIGHT)*REMAP_OUTPUT_BLOCK_HEIGHT;
    }
    else {
        imDim->censusInputImageWidth= imDim->remapImageWidth;
        imDim->censusInputImageHeight= imDim->remapImageHeight;
    }

    imDim->censusInputImageStartX= ((pStereoParams->censusWinWidth - 1)>>1);
    imDim->censusInputImageStartY= ((pStereoParams->censusWinHeight - 1)>>1);

    imDim->remapImageWidth= imDim->censusInputImageWidth;
    imDim->remapImageHeight= imDim->censusInputImageHeight;

    imDim->origRoiStartX= imDim->censusInputImageStartX + imDim->disparityInputLeftImageStartX;
    imDim->origRoiStartY= imDim->censusInputImageStartY + imDim->disparityInputLeftImageStartY;

    //Vps_printf(" \n imDim->origRoiStartX = %d \n imDim->origRoiStartX = %d \n", imDim->origRoiStartX, imDim->origRoiStartY);

}

static void ChainsCommon_RVP_SetRemapMergeAlgPrms( AlgorithmLink_RemapMergeCreateParams *pPrm,
                                                   RVP_Stereo_ImageDims *imDims)
{
    UInt32 qspiBufHeader[SYSTEM_QSPI_READ_WRITE_SIZE];

    pPrm->imageWidth    = REMAP_CROP_WIDTH;
    pPrm->imageHeight   = REMAP_CROP_HEIGHT;

    pPrm->coordMapList        = 1;
    pPrm->isSrcMapFloat       = 0;
    pPrm->srcFormat           = 0;
    pPrm->dstFormat           = 0;
    pPrm->srcStride           = pPrm->roiWidth  = pPrm->dstStride = imDims->remapImageWidth;
    pPrm->srcHeight           = pPrm->roiHeight = imDims->remapImageHeight;
    pPrm->blockWidthBB        = REMAP_OUTPUT_BLOCK_WIDTH;
    pPrm->blockHeightBB       = REMAP_OUTPUT_BLOCK_HEIGHT;
    pPrm->blockWidthTile      = 80;
    pPrm->blockHeightTile     = 40;
    pPrm->tileWidth           = 40;
    pPrm->tileHeight          = 50;
    pPrm->enableMerge         = 0;
    pPrm->interpolationLuma   = 1;
    pPrm->interpolationChroma = 0;
    pPrm->mapQshift           = 2;
    pPrm->rightShift          = 0;
    pPrm->sat_high            = 255;
    pPrm->sat_high_set        = 255;
    pPrm->sat_low             = 0;
    pPrm->sat_low_set         = 0;

    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
    /* Reading calibration tables from QSPI */
    /* Read the Header first */
    System_qspiReadSector(  (UInt32)qspiBufHeader,
                            STEREO_CALIB_LUT_QSPI_OFFSET,
                            SystemUtils_align(STEREO_CALIB_LUT_HEADER_SIZE, SYSTEM_QSPI_READ_WRITE_SIZE));
    if (STEREO_CALIB_LUT_TAG_ID == qspiBufHeader[0]){
        /* Read bin file size */
        pPrm->calibLUTBufPrms.calibLUTBufSize = qspiBufHeader[1] - STEREO_CALIB_LUT_HEADER_SIZE;
        pPrm->calibLUTBufPrms.pCalibLUTBuf    = Utils_memAlloc(     UTILS_HEAPID_DDR_CACHED_SR,
                                                                    SystemUtils_align(pPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE), /* Padd with QSPI_READ_WRITE_SIZE as  System_qspiReadSector writes in granularity of QSPI_READ_WRITE_SIZE bytes*/
                                                                    32);
        UTILS_assert(pPrm->calibLUTBufPrms.pCalibLUTBuf != NULL);
        pPrm->calibLUTBufPrms.isValid = TRUE;
        /* Read the binary file */
        System_qspiReadSector(  (UInt32)pPrm->calibLUTBufPrms.pCalibLUTBuf,
                                STEREO_CALIB_LUT_QSPI_OFFSET+STEREO_CALIB_LUT_HEADER_SIZE,
                                SystemUtils_align(pPrm->calibLUTBufPrms.calibLUTBufSize, SYSTEM_QSPI_READ_WRITE_SIZE));}
    else{
        pPrm->calibLUTBufPrms.isValid= FALSE;}
}


static void ChainsCommon_RVP_SetCensusAlgPrms(  AlgorithmLink_CensusCreateParams *pPrm,
                                            RVP_Stereo_ImageDims *imDims,
                                            RVP_Stereo_ConfigurableCreateParams *pStereoParams)
{
    pPrm->imageRoiWidth     = imDims->censusOutputRoiWidth;
    pPrm->imageRoiHeight    = imDims->censusOutputRoiHeight;

    pPrm->inputBitDepth     = CENSUS_INPUT_BIT_DEPTH;
    pPrm->winWidth          = pStereoParams->censusWinWidth;
    pPrm->winHeight         = pStereoParams->censusWinHeight;
    pPrm->winHorzStep       = pStereoParams->censusWinHorzStep;
    pPrm->winVertStep       = pStereoParams->censusWinVertStep;

    pPrm->srcImageWidth     = imDims->censusInputImageWidth;
    pPrm->srcImageHeight    = imDims->censusInputImageHeight;

    pPrm->numOutBuffers = LINK_NUM_BUFFERS;
}

static void ChainsCommon_RVP_SetDisparityAlgPrms(  AlgorithmLink_DisparityHamDistCreateParams *pPrm,
                                            RVP_Stereo_ImageDims *imDims,
                                            RVP_Stereo_ConfigurableCreateParams *pStereoParams)
{
    pPrm->imageRoiWidth       = imDims->disparityOutputRoiWidth;
    pPrm->imageRoiHeight      = imDims->disparityOutputRoiHeight;
    
    pPrm->inputBitDepth     = DISPARITY_INPUT_BIT_DEPTH;
    pPrm->winWidth          = pStereoParams->disparitySupportWinWidth;
    pPrm->winHeight         = pStereoParams->disparitySupportWinHeight;
    pPrm->numDisparities    = pStereoParams->numDisparities;
    pPrm->disparityStep     = pStereoParams->disparityStepSize;
    pPrm->searchDir         = pStereoParams->disparitySearchDir;
    pPrm->extraRightLeftMap = pStereoParams->leftRightCheckEna;

    pPrm->srcImageWidth = imDims->disparityInputImageWidth;
    pPrm->srcImageHeight = imDims->disparityInputImageHeight;

    pPrm->inputLeftImageStartX= imDims->disparityInputLeftImageStartX;
    pPrm->inputLeftImageStartY= imDims->disparityInputLeftImageStartY;
    pPrm->inputRightImageStartX= imDims->disparityInputRightImageStartX;
    pPrm->inputRightImageStartY= imDims->disparityInputRightImageStartY;

    pPrm->numOutBuffers             = LINK_NUM_BUFFERS;
}


static void ChainsCommon_RVP_SetStereoPostProcessPrms(  AlgorithmLink_StereoPostProcessCreateParams *pPrm,
                                                    RVP_Stereo_ImageDims *imDims,
                                                    RVP_Stereo_ConfigurableCreateParams *pStereoParams)
{
    pPrm->numOutBuffers             = LINK_NUM_BUFFERS;
    pPrm->maxImageRoiWidth      = imDims->disparityOutputRoiWidth;
    pPrm->maxImageRoiHeight     = imDims->disparityOutputRoiHeight;
    pPrm->inputBitDepth         = CENSUS_INPUT_BIT_DEPTH;
    pPrm->censusWinWidth        = pStereoParams->censusWinWidth;
    pPrm->censusWinHeight       = pStereoParams->censusWinHeight;
    pPrm->disparityWinWidth     = pStereoParams->disparitySupportWinWidth;
    pPrm->disparityWinHeight    = pStereoParams->disparitySupportWinHeight;
    pPrm->numDisparities    = pStereoParams->numDisparities;
    pPrm->disparityStep         = pStereoParams->disparityStepSize;
    pPrm->disparitySearchDir         = pStereoParams->disparitySearchDir;
    pPrm->costMaxThreshold        = POSTPROC_COST_MAX_THRESHOLD;
    pPrm->minConfidenceThreshold  = POSTPROC_CONF_MIN_THRSESHOLD;
    pPrm->holeFillingStrength  = POSTPROC_HOLEFILLING_STRENGTH;
    pPrm->textureLumaLoThresh= POSTPROC_TEXTURE_LUMALOTHRESH;
    pPrm->textureLumaHiThresh= POSTPROC_TEXTURE_LUMAHITHRESH;
    pPrm->textureThreshold= POSTPROC_TEXTURE_THRESHOLD;
    pPrm->lrMaxDiffThreshold= POSTPROC_LEFTRIGHT_MAXDIFF_THRESHOLD;
    pPrm->maxDispDissimilarity= POSTPROC_MAX_DISP_DISSIMILARITY;
    pPrm->minConfidentNSegment= POSTPROC_MIN_CONFIDENT_N_SEG;
    pPrm->censusSrcImageWidth = imDims->censusInputImageWidth;
    pPrm->censusSrcImageHeight = imDims->censusInputImageHeight;
    pPrm->temporalFilterNumFrames= POSTPROC_TEMPORAL_FILTER_NUM_FRAMES;
    pPrm->minDisparityToDisplay= POSTPROC_MIN_DISPARITY_DISPLAY;
    pPrm->colorMapIndex= pStereoParams->postproc_colormap_index;
    pPrm->disparityExtraRightLeft= pStereoParams->leftRightCheckEna;
    pPrm->imageStartX= imDims->origRoiStartX;
    pPrm->imageStartY= imDims->origRoiStartY;
    pPrm->useGrayScale = TRUE;
    pPrm->enable16BitsDispOut = FALSE;
}

void ChainsCommon_RVP_Delete( AlgorithmLink_RemapMergeCreateParams *pAlg_RemapMergePrm)
{
    if(pAlg_RemapMergePrm->calibLUTBufPrms.isValid	){
        Utils_memFree(  UTILS_HEAPID_DDR_CACHED_SR,
                        pAlg_RemapMergePrm->calibLUTBufPrms.pCalibLUTBuf,
                        pAlg_RemapMergePrm->calibLUTBufPrms.calibLUTBufSize);}
}


////////////////////////////////////////////////////////////////////////
// Core Common Function

void ChainsCommon_RVP_SetParams(
        CaptureLink_CreateParams    *pCapturePrm,
        SelectLink_CreateParams     *pSelect_DisparityPrm,
        SelectLink_CreateParams     *pSelect_PanoramaPrm,
        SyncLink_CreateParams       *pSync_PanoramaPrm,
        SyncLink_CreateParams       *pSync_RemapOutPrm,
        VpeLink_CreateParams        *pVPE_RemapInPrm,
        VpeLink_CreateParams        *pVPE_PostProcOutPrm,
        VpeLink_CreateParams        *pVPE_ImgTransformOutPrm,
        VpeLink_CreateParams        *pVPE_ImgTransformInPrm,
        GrpxSrcLink_CreateParams    *pGrpxSrcPrm,
        DisplayLink_CreateParams    *pDisplay_PanoramaPrm,
        DisplayLink_CreateParams    *pDisplay_DisparityPrm,
        DisplayLink_CreateParams    *pDisplay_GrpxPrm,

        AlgorithmLink_ImageTransformCreateParams    *pAlg_ImageTransformPrm,
        AlgorithmLink_SeamDetectionCreateParams     *pAlg_SeamDetectionPrm,
        AlgorithmLink_StitchingCreateParams         *pAlg_StitchingPrm,
        AlgorithmLink_RemapMergeCreateParams        *pAlg_RemapMergePrm,
        AlgorithmLink_CensusCreateParams            *pAlg_CensusPrm,
        AlgorithmLink_DisparityHamDistCreateParams  *pAlg_DisparityHamDistPrm,
        AlgorithmLink_StereoPostProcessCreateParams *pAlg_StereoPostProcessPrm,
        AlgorithmLink_DmaSwMsCreateParams           *pAlg_DmaSwMPrm,

        Chains_CaptureSrc 	captureSrc,
        Chains_DisplayType  displayType,

        unsigned char stitchingMode,
        unsigned char seamDetectionMode,
        unsigned char imageTransformMode,

        Bool enableDisparityLayout,
        Bool enableCarOverlay,
        UInt32 simcopOutputWidth,
        UInt32 simcopOutputHeight)
{

    UInt32 displayWidth, displayHeight;
    UInt32 imageTransformOutputWidth, imageTransformOutputHeight;
    UInt32 imageTransformInputWidth, imageTransformInputHeight;
#ifdef TDA2XX_FAMILY_BUILD
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    UInt32 numLvdsCh;
    numLvdsCh 	 = NUM_CAPTURE_CH;
#endif
    ChainsCommon_RVP_initImageDims(&pRVPStereoImDims, &pRVPStereoParams);

    imageTransformInputWidth   = IMAGE_TRANSFORM_INPUT_WIDTH;
    imageTransformInputHeight  = IMAGE_TRANSFORM_INPUT_HEIGHT;
    imageTransformOutputWidth  = IMAGE_TRANSFORM_OUTPUT_WIDTH;
    imageTransformOutputHeight = IMAGE_TRANSFORM_OUTPUT_HEIGHT;

    if(displayType){
        ChainsCommon_GetDisplayWidthHeight(displayType,
                                           &displayWidth,
                                           &displayHeight);}

#ifdef TDA2XX_FAMILY_BUILD
    if(pCapturePrm){
        ChainsCommon_MultiCam_StartCaptureDevice(CHAINS_CAPTURE_SRC_OV10635,
                                                    portId,
                                                    numLvdsCh);
        ChainsCommon_MultiCam_SetCapturePrms(pCapturePrm,
                                                    LVDS_CAPTURE_WIDTH,
                                                    LVDS_CAPTURE_HEIGHT,
                                                    portId,
                                                    numLvdsCh);
    }
    else
        UTILS_assert(pCapturePrm != NULL);
#endif

    ////////////////////////////////////////////////////////////////////
    // Algorithm Setup

    if(pAlg_ImageTransformPrm){
        ChainsCommon_RVP_SetImageTransformAlgPrms(  pAlg_ImageTransformPrm,
                                                    imageTransformInputWidth,
                                                    imageTransformInputHeight,
                                                    imageTransformOutputWidth,
                                                    imageTransformOutputHeight,
                                                    imageTransformMode);}
    if(pAlg_SeamDetectionPrm){
        ChainsCommon_RVP_SetSeamDetectionAlgPrms(   pAlg_SeamDetectionPrm,
                                                    simcopOutputWidth,
                                                    simcopOutputHeight,
                                                    imageTransformOutputWidth,
                                                    imageTransformOutputHeight,
                                                    seamDetectionMode);}
    if(pAlg_StitchingPrm){
        ChainsCommon_RVP_SetStitchingAlgPrms(       pAlg_StitchingPrm,
                                                    simcopOutputWidth,
                                                    simcopOutputHeight,
                                                    imageTransformOutputWidth,
                                                    imageTransformOutputHeight,
                                                    stitchingMode);}
    if(pAlg_RemapMergePrm){
        ChainsCommon_RVP_SetRemapMergeAlgPrms (     pAlg_RemapMergePrm,
                                                    &pRVPStereoImDims);}
    if(pAlg_CensusPrm){
        ChainsCommon_RVP_SetCensusAlgPrms (         pAlg_CensusPrm,
                                                    &pRVPStereoImDims,
                                                    &pRVPStereoParams);}
    if(pAlg_DisparityHamDistPrm){
        ChainsCommon_RVP_SetDisparityAlgPrms (      pAlg_DisparityHamDistPrm,
                                                    &pRVPStereoImDims,
                                                    &pRVPStereoParams);}
    if(pAlg_StereoPostProcessPrm){
        ChainsCommon_RVP_SetStereoPostProcessPrms ( pAlg_StereoPostProcessPrm,
                                                    &pRVPStereoImDims,
                                                    &pRVPStereoParams);}
    if(pAlg_DmaSwMPrm){
        ChainsCommon_RVP_SetAlgDmaSwMsPrm(  pAlg_DmaSwMPrm,
                                            imageTransformOutputWidth,
                                            imageTransformOutputHeight);}
    
    ////////////////////////////////////////////////////////////////////
    // General Setup

    if(pSync_PanoramaPrm || pSync_RemapOutPrm){
        ChainsCommon_RVP_SetSyncPrm(    pSync_PanoramaPrm ,0);
        ChainsCommon_RVP_SetSyncPrm(    pSync_RemapOutPrm ,1);}

    if(pSelect_DisparityPrm || pSelect_PanoramaPrm){
        ChainsCommon_RVP_SetSelectPrm(  pSelect_DisparityPrm,
                                        pSelect_PanoramaPrm);}

    if(pVPE_RemapInPrm || pVPE_PostProcOutPrm || pVPE_ImgTransformOutPrm || pVPE_ImgTransformInPrm){
        ChainsCommon_RVP_SetVpePrm(     pVPE_RemapInPrm,
                                        pVPE_PostProcOutPrm,
                                        pVPE_ImgTransformOutPrm,
                                        pVPE_ImgTransformInPrm);}
    if(pGrpxSrcPrm){
        ChainsCommon_RVP_SetGrpxSrcPrms(pGrpxSrcPrm,
                                        displayWidth,
                                        displayHeight,
                                        enableDisparityLayout,
                                        enableCarOverlay);}
    if(pDisplay_PanoramaPrm || pDisplay_DisparityPrm || pDisplay_GrpxPrm){
        ChainsCommon_RVP_SetDisplayPrm( pDisplay_PanoramaPrm,
                                        pDisplay_DisparityPrm,
                                        pDisplay_GrpxPrm,
                                        displayWidth,
                                        displayHeight);

    ChainsCommon_StartDisplayCtrl(      displayType,
                                        displayWidth,
                                        displayHeight);}

 }


#endif
