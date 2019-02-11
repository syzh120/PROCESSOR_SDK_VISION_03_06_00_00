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
#include <src/rtos/utils_common/include/utils_temperature.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include <src/include/link_stats_monitor.h>
#include <src/rtos/iss/include/iss_dcc_nw_handler.h>
#include <src/rtos/iss/include/iss_sensors.h>

#define AVB_TALKER_MAX_FRAME_SIZE 1000000

/* AVBTP Subtype for compressed video format */
#define AVB_TX_LINK_SUBTYPE_CVF             (0x3)

/* CV format subtype */
/* CVF - format subtypes */
#define AVB_TX_LINK_CVF_SUBTYPE_MJPEG       (0x0)
#define AVB_TX_LINK_CVF_SUBTYPE_H264        (0x1)
#define AVB_TX_LINK_CVF_SUBTYPE_JPEG2000    (0x2)

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void ChainsCommon_Init()
{

#if A15_TARGET_OS_BIOS
    Board_init();
    #if defined(FATFS_PROC_TO_USE_IPU1_0)
    File_init();
    #endif
    Lcd_init();
#endif

#ifdef ENABLE_UART_LOG
    System_uartInit();

    /* let the pending prints from other processor's finish */
    if(!System_isFastBootEnabled() &&
       !System_isSrvFastBootEnabled())
    {
        Task_sleep(1000);
    }
#endif
    Utils_prcmClockRateInit();
    Utils_prcmPrintPowerConsumptionInit();

    if(!System_isFastBootEnabled() &&
       !System_isSrvFastBootEnabled())
    {
        SplitLink_init();
#ifdef ULTRASONIC_INCLUDE
#ifdef PGA460
        UltrasonicCaptureLink_init(USM_ID_PGA460);
#elif PGA450
        UltrasonicCaptureLink_init(USM_ID_PGA450);
#endif
#endif
        System_qspiInit();
        ChainsCommon_Stereo_Init();
    }

    DisplayMpLink_init();
    GrpxSrcLink_init();
    ChainsCommon_SetSystemL3DmmPri();
#ifdef ISS_INCLUDE
    Iss_DccCmdHandler_Init();
    IssSensor_Init();
#endif
    Utils_statCollectorInit(); /* Initializing the statCollector */
    Chains_linkStatsMonitorInit();
}

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void ChainsCommon_DeInit()
{
    GrpxSrcLink_deInit();

    if(!System_isFastBootEnabled())
    {
        SplitLink_deInit();
#ifdef ULTRASONIC_INCLUDE
#ifdef PGA460
        UltrasonicCaptureLink_deInit(USM_ID_PGA460);
#elif PGA450
        UltrasonicCaptureLink_deInit(USM_ID_PGA450);
#endif
#endif
    }

#if A15_TARGET_OS_BIOS
    Lcd_deInit();
    #if defined(FATFS_PROC_TO_USE_IPU1_0)
    File_deInit();
    #endif
    Board_deInit();
#endif

    DisplayMpLink_deInit();
#ifdef ISS_INCLUDE
    Iss_DccCmdHandler_DeInit();
#endif
    Utils_statCollectorDeInit();
    Chains_linkStatsMonitorDeInit();
}

/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters for single camera capture mode
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SingleCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight,
                        Chains_CaptureSrc captureSrc
                        )
{
    UInt32 i, streamId;
    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrms;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));
    /* For SCV usecase number of camera is always 1 */
    pPrm->numVipInst = 1;
    pPrm->numDssWbInst = 0;

#ifdef TDA2EX_BUILD
#ifndef ROBUST_RVC_INCLUDE
    /* Select Ethernet port connection depending upon capture source type */
    ChainsCommon_tda2exSelectPHY(captureSrc);
#endif
#endif

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInprms = &pInstPrm->inParams;
        pInstPrm->vipInstId     =   i;
#ifdef TDA2EX_BUILD
        //This change is done for supporting tda2ex
        pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
#endif
        if( (captureSrc == CHAINS_CAPTURE_SRC_OV10635) ||
            (captureSrc == CHAINS_CAPTURE_SRC_OV10635_LVDS) )
        {
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else if(captureSrc == CHAINS_CAPTURE_SRC_DM388)
        {
            pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_24BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_RGB24_888;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

            /* Without clk inversion, saturation artifacts are seen on the screen when DM388
             * captures and tda2xx displays on HDMI. This is board specific fix and needed
             * only for MONSTERCAM.
             */
            Bsp_platformSetVipClkInversion(pInstPrm->vipInstId, TRUE);

        }
        else if(captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158)
        {
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_ES;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight/2;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_INTERLACED;

        }
        else if (captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   1280;
            pInprms->height     =    720;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        }
        else if (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P)
        {


            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_AVID_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   1920;
            pInprms->height     =   1080;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422I_UYVY;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else if((captureSrc == CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL) ||
                (captureSrc == CHAINS_CAPTURE_SRC_AR0132MONOCHROME_PARALLEL))
        {
            pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_BAYER_GRBG;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else if(captureSrc == CHAINS_CAPTURE_SRC_OV490)
        {
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_BAYER_GRBG;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }

        else
        {
            /* Nothing here. To avoid MISRA C warnings */
        }

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   captureOutWidth;
            pOutprms->height        =   captureOutHeight;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;

            if(captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158)
            {
                pOutprms->width         =   captureOutWidth;
                pOutprms->height        =   captureOutHeight/2;
                pOutprms->dataFormat    =   SYSTEM_DF_YUV422I_YUYV;
                pOutprms->maxWidth      =   pOutprms->width;
                pOutprms->maxHeight     =   pOutprms->height;
            }

            if((pInprms->width != pOutprms->width) ||
                (pInprms->height != pOutprms->height))
            {
                pOutprms->scEnable      =   TRUE;
            }
            else
            {
                pOutprms->scEnable      =   FALSE;
            }
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

            if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
            {
                pOutprms->dataFormat    =   SYSTEM_DF_YUV422I_UYVY;
            }
            if((captureSrc == CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL) ||
               (captureSrc == CHAINS_CAPTURE_SRC_AR0132MONOCHROME_PARALLEL))
            {
                /* Keeping the bayer output format, so that next link (ISP)
                   can understand dataformat */
                pOutprms->dataFormat    =   SYSTEM_DF_BAYER_GRBG;
            }

            if(captureSrc==CHAINS_CAPTURE_SRC_HDMI_720P
                ||
               captureSrc==CHAINS_CAPTURE_SRC_HDMI_1080P
                ||
               captureSrc==CHAINS_CAPTURE_SRC_DM388
            )
            {
                /* skip alternate frame to make it 30fps output */
                pOutprms->frameSkipMask
                    = 0x2AAAAAAA;
            }
        }
        pScPrms = &pInstPrm->scPrms;
        pScPrms->inCropCfg.cropStartX = 0;
        pScPrms->inCropCfg.cropStartY = 0;
        pScPrms->inCropCfg.cropWidth = pInprms->width;
        pScPrms->inCropCfg.cropHeight = pInprms->height;

        pScPrms->scCfg.bypass       = FALSE;
        pScPrms->scCfg.nonLinear    = FALSE;
        pScPrms->scCfg.stripSize    = 0;

        pScPrms->userCoeff = FALSE;

        /* pScPrms->scCoeffCfg is not reuquired in case
         * pScPrms->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;



        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                                SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;
        pPortCfg->actCropEnable             =   TRUE;

        if ((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
            (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
        {
            pPortCfg->actCropEnable         =   FALSE;
            if(Bsp_platformIsTda3xxFamilyBuild())
            {
                pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
                pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_LOW;
                pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_LOW;
            }
        }

        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            pPortCfg->disCfg.lineCaptureStyle   =   SYSTEM_VIP_LINE_CAPTURE_STYLE_HSYNC;
            pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_VSYNC;
            pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
            pPortCfg->comCfg.ancChSel8b         =   SYSTEM_VIP_ANC_CH_SEL_DONT_CARE;
            pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_FALLING;
        }

        if(captureSrc == CHAINS_CAPTURE_SRC_VIDDEC_TVP5158)
        {
            pPortCfg->syncType                              =   SYSTEM_VIP_SYNC_TYPE_EMB_SINGLE_422_YUV;
            pPortCfg->actCropEnable                         =   FALSE;
            pPortCfg->comCfg.expectedNumLines               =   0;
            pPortCfg->comCfg.expectedNumPix                 =   0;
            pPortCfg->actCropCfg.cropCfg.cropWidth          =   0;
            pPortCfg->actCropCfg.cropCfg.cropHeight         =   0;
        }

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters for Stereo camera capture mode
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_StereoCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight,
                        Chains_CaptureSrc captureSrc
                        )
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrms;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));
    /* For SCV usecase number of camera is always 1 */
    pPrm->numVipInst = 2;
    pPrm->numDssWbInst = 0;

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInprms = &pInstPrm->inParams;
        if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            if (i==0)
            {
                pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
            }
            else
            {
                pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
            }
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422I_UYVY;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else
        {
            /* Nothing here. To avoid MISRA C warnings */
        }

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   captureOutWidth;
            pOutprms->height        =   captureOutHeight;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            if((pInprms->width != pOutprms->width) ||
                (pInprms->height != pOutprms->height))
            {
                pOutprms->scEnable      =   TRUE;
            }
            else
            {
                pOutprms->scEnable      =   FALSE;
            }
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

            if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
            {
                pOutprms->dataFormat    =   SYSTEM_DF_YUV422I_UYVY;
            }

            /* skip alternate frame to make it 30fps output */
            pOutprms->frameSkipMask
                = 0x20202020;
        }
        pScPrms = &pInstPrm->scPrms;
        pScPrms->inCropCfg.cropStartX = 0;
        pScPrms->inCropCfg.cropStartY = 0;
        pScPrms->inCropCfg.cropWidth = pInprms->width;
        pScPrms->inCropCfg.cropHeight = pInprms->height;

        pScPrms->scCfg.bypass       = FALSE;
        pScPrms->scCfg.nonLinear    = FALSE;
        pScPrms->scCfg.stripSize    = 0;

        pScPrms->userCoeff = FALSE;

        /* pScPrms->scCoeffCfg is not reuquired in case
         * pScPrms->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;



        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                                SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;
        pPortCfg->actCropEnable             =   TRUE;

        if ((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
            (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
        {
            pPortCfg->actCropEnable         =   FALSE;
        }

        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            pPortCfg->disCfg.lineCaptureStyle   =   SYSTEM_VIP_LINE_CAPTURE_STYLE_HSYNC;
            pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_VSYNC;
            pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
            pPortCfg->comCfg.ancChSel8b         =   SYSTEM_VIP_ANC_CH_SEL_DONT_CARE;
            pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_FALLING;
        }

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters for TDA2x Stereo camera capture mode
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_TDA2x_StereoCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight,
                        Chains_CaptureSrc captureSrc,
                        UInt32 portId[],
                        UInt32 numLvdsCh
                        )
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrms;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));
    /* For SCV usecase number of camera is always 1 */
    pPrm->numVipInst = numLvdsCh;
    pPrm->numDssWbInst = 0;

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInprms = &pInstPrm->inParams;
        if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            if (i==0)
            {
                pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
            }
            else
            {
                pInstPrm->vipInstId     =   SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
            }
            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_16BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422I_UYVY;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }
        else
        {
            UTILS_assert(portId != NULL);
            pInstPrm->vipInstId     =   portId[i];

            pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
            pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
            pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
            pInstPrm->numStream     =   1;

            pInprms->width      =   captureInWidth;
            pInprms->height     =   captureInHeight;
            pInprms->dataFormat =   SYSTEM_DF_YUV422P;
            pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;
        }

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   captureOutWidth;
            pOutprms->height        =   captureOutHeight;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            if((pInprms->width != pOutprms->width) ||
                (pInprms->height != pOutprms->height))
            {
                pOutprms->scEnable      =   TRUE;
            }
            else
            {
                pOutprms->scEnable      =   FALSE;
            }
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

            if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
            {
                pOutprms->dataFormat    =   SYSTEM_DF_YUV422I_UYVY;
            }

            /* skip alternate frame to make it 30fps output */
            pOutprms->frameSkipMask
                = 0x20202020;
        }
        pScPrms = &pInstPrm->scPrms;
        pScPrms->inCropCfg.cropStartX = 0;
        pScPrms->inCropCfg.cropStartY = 0;
        pScPrms->inCropCfg.cropWidth = pInprms->width;
        pScPrms->inCropCfg.cropHeight = pInprms->height;

        pScPrms->scCfg.bypass       = FALSE;
        pScPrms->scCfg.nonLinear    = FALSE;
        pScPrms->scCfg.stripSize    = 0;

        pScPrms->userCoeff = FALSE;

        /* pScPrms->scCoeffCfg is not reuquired in case
         * pScPrms->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;



        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                                SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;
        pPortCfg->actCropEnable             =   TRUE;

        if ((captureSrc == CHAINS_CAPTURE_SRC_HDMI_720P) ||
            (captureSrc == CHAINS_CAPTURE_SRC_HDMI_1080P))
        {
            pPortCfg->actCropEnable         =   FALSE;
        }

        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        if(captureSrc == CHAINS_CAPTURE_SRC_AR0132RCCC)
        {
            pPortCfg->disCfg.lineCaptureStyle   =   SYSTEM_VIP_LINE_CAPTURE_STYLE_HSYNC;
            pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_VSYNC;
            pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_LOW;
            pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
            pPortCfg->comCfg.ancChSel8b         =   SYSTEM_VIP_ANC_CH_SEL_DONT_CARE;
            pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_FALLING;
        }

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set Capture Create Parameters for multi camera capture mode
 *
 * \param   pPrm         [IN]  CaptureLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_MultiCam_SetCapturePrms(
                        CaptureLink_CreateParams *pPrm,
                        UInt32 captureInWidth,
                        UInt32 captureInHeight,
                        UInt32 portId[],
                        UInt32 numLvdsCh
                        )
{
    UInt32 i, streamId;

    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrm;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(*pPrm));

    pPrm->numVipInst = numLvdsCh;
    pPrm->numDssWbInst = 0;

#ifdef TDA2EX_BUILD
    /* Select Ethernet port connection depending upon capture source type
     * We are passing CHAINS_CAPTURE_SRC_OV10635 as capture source as it is
     * 8 bit */

    ChainsCommon_tda2exSelectPHY(CHAINS_CAPTURE_SRC_OV10635);
#endif

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];

        UTILS_assert(portId != NULL);
        pInstPrm->vipInstId     =   portId[i];

        pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
        pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
        pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_FRM_DROP;
        pInstPrm->numStream     =   1;

        pInprms = &pInstPrm->inParams;

        pInprms->width      =   captureInWidth;
        pInprms->height     =   captureInHeight;
        pInprms->dataFormat =   SYSTEM_DF_YUV422P;
        pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   pInprms->width;
            pOutprms->height        =   pInprms->height;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV420SP_UV;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            pOutprms->scEnable      =   FALSE;

            /* sub-frame not supported, set to FALSE */
            pOutprms->subFrmPrms.subFrameEnable = FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0;

        }
        pScPrm = &pInstPrm->scPrms;
        pScPrm->inCropCfg.cropStartX = 0;
        pScPrm->inCropCfg.cropStartY = 0;
        pScPrm->inCropCfg.cropWidth = pInprms->width;
        pScPrm->inCropCfg.cropHeight = pInprms->height;

        pScPrm->scCfg.bypass       = FALSE;
        pScPrm->scCfg.nonLinear    = FALSE;
        pScPrm->scCfg.stripSize    = 0;

        pScPrm->userCoeff = FALSE;

        /* pScPrm->scCoeffCfg is not reuquired in case
         * pScPrm->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   FALSE;

        pPortCfg->intfCfg.clipActive    =   FALSE;
        pPortCfg->intfCfg.clipBlank     =   FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0;
        pPortCfg->disCfg.fidSkewPreCnt      =   0;
        pPortCfg->disCfg.lineCaptureStyle   =
                                SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
                            SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   FALSE;
        pPortCfg->comCfg.enablePort         =   FALSE;
        pPortCfg->comCfg.expectedNumLines   =   pInprms->height;
        pPortCfg->comCfg.expectedNumPix     =   pInprms->width;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;

        pPortCfg->actCropEnable                         =   TRUE;
        pPortCfg->actCropCfg.srcNum                     =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   pInprms->width;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   pInprms->height;

        pPortCfg->ancCropCfg.srcNum                     =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0;

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT + 2;
    }
}

Void ChainsCommon_MultiCam_SetCroppingPrms(
                        CaptureLink_CreateParams *pPrm,
                        Uint32 inWidth,
                        Uint32 inHeight,
                        Uint32 outWidth,
                        Uint32 outHeight)
{
    Uint32 i;
    Uint32 streamId;
    if (inWidth > outWidth)
    {
        // Center crop all cameras in the X direction
        for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {

            pPrm->vipInst[i].vipPortCfg.actCropCfg.cropCfg.cropStartX = (inWidth - outWidth) / 2;
            pPrm->vipInst[i].vipPortCfg.actCropCfg.cropCfg.cropWidth  = outWidth;

            for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                    streamId++)
            {
                pPrm->vipInst[i].outParams[streamId].width=outWidth;
            }
        }
    }
    else if (inHeight > outHeight)
    {
        // Center crop all cameras in the Y direction
        for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++)
        {
            pPrm->vipInst[i].vipPortCfg.actCropCfg.cropCfg.cropStartY = (inHeight - outHeight) / 2;
            pPrm->vipInst[i].vipPortCfg.actCropCfg.cropCfg.cropHeight = outHeight;

            for (streamId = 0; streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                    streamId++)
            {
                pPrm->vipInst[i].outParams[streamId].height=outHeight;
            }
        }
    }
}


/**
 *******************************************************************************
 *
 * \brief   Set AVBRX Create Parameters
 *
 *          It is called in Create function.
 *          All AVBRX parameters are set.
 *
 * \param   pPrm         [IN]    AvbRxLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SetAvbRxPrm(       AvbRxLink_CreateParams *pAvbPrm,
                                     UInt32 maxWidth,
                                     UInt32 maxHeight,
                                     UInt32 numCh)
{
    UInt32 nIdx;
    UInt8 stream_ID[][8] =
    {
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE1}, //front
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE0}, //right
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE2}, //back
        {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xE3}, //left
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x03},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x04}
    };
    UInt8 SrcMACAdd[][6] =
    {
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05}
    };

    for (nIdx = 0; nIdx < numCh; nIdx++)
    {
        memcpy(pAvbPrm->streamId[nIdx], stream_ID[nIdx],sizeof(stream_ID[nIdx]));
        memcpy(pAvbPrm->srcMacId[nIdx], SrcMACAdd[nIdx],sizeof(SrcMACAdd[nIdx]));
    }
    pAvbPrm->numCameras = numCh;
    pAvbPrm->numBufs = AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT;
    pAvbPrm->buffSize = AVB_TALKER_MAX_FRAME_SIZE;
    pAvbPrm->width  = maxWidth;
    pAvbPrm->height = maxHeight;
}

/**
 *******************************************************************************
 *
 * \brief   Set AVBTX Create Parameters
 *
 *          It is called in Create function.
 *          All AVBTX parameters are set.
 *
 * \param   pPrm         [IN]    AvbTxLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SetAvbTxPrm(       AvbTxLink_CreateParams *pAvbPrm,
                                     UInt32 numCh,
                                     System_IVideoFormat codecType)
{
    UInt32 nIdx;
    UInt8 dstMacId[][8] =
    {
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
    };

    /*
     * Current AVB Implementation doesn't use configurable stream id, streamId
     * for the different AVB talkers is made using src address and talker index
     * combination.
     */
    UInt8 stream_ID[][8] =
    {
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x03},
        {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x04}
    };

    UInt8 SrcMACAdd[][6] =
    {
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
        {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
    };

    /* Set default Subtype - Compressed Video Format (0x3) */
    UInt32 avbTpSubType[AVB_TX_LINK_MAX_TALKERS_DEFAULT] = {AVB_TX_LINK_SUBTYPE_CVF,
                                                            AVB_TX_LINK_SUBTYPE_CVF,
                                                            AVB_TX_LINK_SUBTYPE_CVF,
                                                            AVB_TX_LINK_SUBTYPE_CVF};

    UInt32 cvFormatSubType[AVB_TX_LINK_MAX_TALKERS_DEFAULT] = {AVB_TX_LINK_CVF_SUBTYPE_H264,
                                                            AVB_TX_LINK_CVF_SUBTYPE_H264,
                                                            AVB_TX_LINK_CVF_SUBTYPE_H264,
                                                            AVB_TX_LINK_CVF_SUBTYPE_H264};
    for (nIdx = 0; nIdx < numCh; nIdx++)
    {
        memcpy(pAvbPrm->streamId[nIdx], stream_ID[nIdx],sizeof(stream_ID[nIdx]));
        memcpy(pAvbPrm->srcMacId[nIdx], SrcMACAdd[nIdx],sizeof(SrcMACAdd[nIdx]));
        memcpy(pAvbPrm->dstMacId[nIdx], dstMacId[nIdx],sizeof(dstMacId[nIdx]));
        pAvbPrm->avbTpSubType[nIdx] = avbTpSubType[nIdx];
        /* Set AVBTP cvFormattype as per encoding format */
        if (SYSTEM_IVIDEO_H264HP == codecType)
        {
            pAvbPrm->cvFormatSubType[nIdx] = AVB_TX_LINK_CVF_SUBTYPE_H264;
        }
        else if (SYSTEM_IVIDEO_MJPEG == codecType)
        {
            pAvbPrm->cvFormatSubType[nIdx] = AVB_TX_LINK_CVF_SUBTYPE_MJPEG;
        }
        else
        {
            pAvbPrm->cvFormatSubType[nIdx] = cvFormatSubType[nIdx];
        }
    }

}

/**
 *******************************************************************************
 *
 * \brief   Set Decode Create Parameters
 *
 *          It is called in Create function.
 *          All decoder parameters are set.
 *
 * \param   pPrm         [IN]    DecodeLink_CreateParams
 *
 *******************************************************************************
*/
Void ChainsCommon_SetDecodePrm(     DecLink_CreateParams *pDecPrm,
                                     UInt32 maxWidth,
                                     UInt32 maxHeight,
                                     UInt32 numCh,
                                     System_IVideoFormat codecType)
{
    UInt32 chId;
    DecLink_ChCreateParams *decPrm;

    for (chId = 0; chId<numCh; chId++)
    {
        UTILS_assert (chId < DEC_LINK_MAX_CH);
        decPrm = &pDecPrm->chCreateParams[chId];

        decPrm->dpbBufSizeInFrames  = DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT;
        decPrm->algCreateStatus     = DEC_LINK_ALG_CREATE_STATUS_CREATE;
        decPrm->decodeFrameType     = DEC_LINK_DECODE_ALL;

        decPrm->processCallLevel    = DEC_LINK_FRAMELEVELPROCESSCALL;
        decPrm->targetMaxWidth      = maxWidth;
        decPrm->targetMaxHeight     = maxHeight;
        decPrm->numBufPerCh         = DEC_LINK_NUM_BUFFERS_PER_CHANNEL;
        decPrm->defaultDynamicParams.targetBitRate = 10 * 1000 * 1000;
        decPrm->defaultDynamicParams.targetFrameRate = 30;
        decPrm->fieldMergeDecodeEnable = FALSE;

        switch (codecType)
        {
            case SYSTEM_IVIDEO_MJPEG: /* MJPEG */
                decPrm->format = SYSTEM_IVIDEO_MJPEG;
                decPrm->profile = 0;
                decPrm->displayDelay = 0;
                break;

            case SYSTEM_IVIDEO_H264HP: /* H264 */
                decPrm->format = SYSTEM_IVIDEO_H264HP;
                decPrm->profile = 3;
                decPrm->displayDelay = 0;
                break;

            default: /* D1 */
                printf("\r\nCodec Type: %d, returning \n", codecType);
                UTILS_assert(FALSE);
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set SOF configuration
 *
 *******************************************************************************
*/
Void ChainsCommon_SetSOFConfig(
                                 AlgorithmLink_SparseOpticalFlowCreateParams *pAlgSofPrm,
                                 UInt32 startX,
                                 UInt32 startY,
                                 UInt32 width,
                                 UInt32 height,
                                 UInt32 sfmTrackPoints)
{
    UInt8 i;

    pAlgSofPrm->imgFrameStartX = startX;
    pAlgSofPrm->imgFrameStartY = startY;
    pAlgSofPrm->imgFrameWidth  = width;
    pAlgSofPrm->imgFrameHeight  = height;

    pAlgSofPrm->enableRoi  = TRUE;
    pAlgSofPrm->roiWidth   = 1264;
    pAlgSofPrm->roiHeight  = 222;
    pAlgSofPrm->roiStartX  = 0;
    pAlgSofPrm->roiStartY  = 330;

    pAlgSofPrm->numOutBuffers = 8;

    pAlgSofPrm->trackErrThr = 441;
    pAlgSofPrm->trackMinFlowQ4 = 0;
    pAlgSofPrm->trackNmsWinSize = 3;

    pAlgSofPrm->numLevels = 5;
    pAlgSofPrm->keyPointDetectMethod = 1;
    pAlgSofPrm->keyPointDetectInterval = 0;
    pAlgSofPrm->maxNumKeyPoints = sfmTrackPoints;
    pAlgSofPrm->maxPrevTrackPoints  = 768;
    pAlgSofPrm->fast9Threshold = 80;
    pAlgSofPrm->scoreMethod = 0;
    pAlgSofPrm->harrisScaling = 1350;
    pAlgSofPrm->nmsThreshold = 1350;
    pAlgSofPrm->harrisScoreMethod = 1;
    pAlgSofPrm->harrisWindowSize = 2;
    pAlgSofPrm->suppressionMethod = 0;

    pAlgSofPrm->trackOffsetMethod = 0;

    pAlgSofPrm->maxItersLK[0]  = 8;
    pAlgSofPrm->maxItersLK[1]  = 7;
    pAlgSofPrm->maxItersLK[2]  = 7;
    pAlgSofPrm->maxItersLK[3]  = 6;
    pAlgSofPrm->maxItersLK[4]  = 6;
    pAlgSofPrm->maxItersLK[5]  = 10;
    pAlgSofPrm->maxItersLK[6]  = 10;
    pAlgSofPrm->maxItersLK[7]  = 10;

    for(i=0; i<PYRAMID_LK_TRACKER_TI_MAXLEVELS;i++)
    {
        pAlgSofPrm->minErrValue[i] = 51;
        pAlgSofPrm->searchRange[i] = 12;
    }

    pAlgSofPrm->compositeBufferInput = -1;

}

/**
 *******************************************************************************
 *
 * \brief   Set NullSrc and Decode Create Parameters
 *******************************************************************************
*/
Void ChainsCommon_SetNetworkRxPrms(
                        NetworkRxLink_CreateParams *pPrm,
                        DecLink_CreateParams *pDecPrm,
                        UInt32 maxWidth,
                        UInt32 maxHeight,
                        UInt32 numCh,
                        UInt32 fps /* in msecs */
                        )
{
    UInt32 chId;
    DecLink_ChCreateParams *decPrm;
    System_LinkChInfo *pChInfo;

    pPrm->outQueInfo.numCh = numCh;

    pPrm->timerPeriodMilliSecs = 1000/fps;

    for (chId = 0; chId < pPrm->outQueInfo.numCh; chId++)
    {
        pPrm->channelParams[chId].numBuffers = 5;

        pChInfo = &pPrm->outQueInfo.chInfo[chId];

        if(pDecPrm)
        {
            pChInfo->flags = System_Link_Ch_Info_Set_Flag_Bitstream_Format(pChInfo->flags,
                                                    SYSTEM_BITSTREAM_CODING_TYPE_MJPEG);
            pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                               SYSTEM_BUFFER_TYPE_BITSTREAM);
        }
        else
        {
            pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                                    SYSTEM_DF_YUV420SP_UV);

            pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                               SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
        }

        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                                    SYSTEM_SF_PROGRESSIVE);
        pChInfo->width = maxWidth;
        pChInfo->height = maxHeight;
        pChInfo->startX = 0;
        pChInfo->startY = 0;
        pChInfo->pitch[0] = SystemUtils_align(pChInfo->width, 32);
        pChInfo->pitch[1] = SystemUtils_align(pChInfo->width, 32);

    }

    pPrm->networkServerPort = NETWORK_RX_SERVER_PORT;
    /* Select network mode for null source link */
    ChainsCommon_networkRxSetMode(pPrm);

    if(pDecPrm)
    {
        for (chId = 0; chId<numCh; chId++)
        {
            decPrm = &pDecPrm->chCreateParams[chId];

            decPrm->dpbBufSizeInFrames  = DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT;
            decPrm->algCreateStatus     = DEC_LINK_ALG_CREATE_STATUS_CREATE;
            decPrm->decodeFrameType     = DEC_LINK_DECODE_ALL;

            decPrm->format              = SYSTEM_IVIDEO_MJPEG;
            decPrm->processCallLevel    = DEC_LINK_FRAMELEVELPROCESSCALL;
            decPrm->targetMaxWidth      = SystemUtils_align(maxWidth, 32);
            decPrm->targetMaxHeight     = SystemUtils_align(maxHeight, 32);
            decPrm->numBufPerCh         = 4;
            decPrm->defaultDynamicParams.targetBitRate = 10 * 1000 * 1000;
            decPrm->defaultDynamicParams.targetFrameRate = 30;
            decPrm->fieldMergeDecodeEnable = FALSE;

            switch (decPrm->format)
            {
                case SYSTEM_IVIDEO_MJPEG: /* MJPEG */
                    decPrm->profile = 0;
                    decPrm->displayDelay = 0;
                    break;
                default:
                    Vps_printf(" CHAINS: ERROR: Un-supported codec type: %d !!! \n", decPrm->format);
                    UTILS_assert(FALSE);
                    break;
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set NullSrc and Decode Create Parameters
 *******************************************************************************
*/
Void ChainsCommon_SetFileRxPrms(
                        NullSrcLink_CreateParams *pPrm,
                        DecLink_CreateParams *pDecPrm,
                        UInt32 maxWidth,
                        UInt32 maxHeight,
                        UInt32 numCh,
                        UInt32 fps /* in msecs */
                        )
{
    UInt32 chId;
    DecLink_ChCreateParams *decPrm;
    System_LinkChInfo *pChInfo;

    pPrm->outQueInfo.numCh = numCh;



    pPrm->outQueInfo.numCh = 1;

    pPrm->timerPeriodMilliSecs = (1000/fps);

    for (chId = 0; chId < pPrm->outQueInfo.numCh; chId++)
    {
        pPrm->channelParams[chId].numBuffers = 4;

        pChInfo = &pPrm->outQueInfo.chInfo[chId];

        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                                    SYSTEM_DF_YUV420SP_UV);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                                    SYSTEM_SF_PROGRESSIVE);
        pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                               /*SYSTEM_BUFFER_TYPE_VIDEO_FRAME*/
                                               SYSTEM_BUFFER_TYPE_BITSTREAM);
        pChInfo->width = maxWidth;
        pChInfo->height = maxHeight;
        pChInfo->startX = 0;
        pChInfo->startY = 0;
        pChInfo->pitch[0] = SystemUtils_align(pChInfo->width, 32);
        pChInfo->pitch[1] = SystemUtils_align(pChInfo->width, 32);

        pPrm->channelParams[chId].fileReadMode = NULLSRC_LINK_FILEREAD_RUN_TIME;

        strncpy(pPrm->channelParams[chId].nameDataFile, "inData", 260);
        strncpy(pPrm->channelParams[chId].nameIndexFile, "inHeader", 260);
    }

    pPrm->dataRxMode = NULLSRC_LINK_DATA_RX_MODE_FILE;

    if(pDecPrm)
    {
        for (chId = 0; chId < numCh; chId++)
        {
            UTILS_assert (chId < DEC_LINK_MAX_CH);
            decPrm = &pDecPrm->chCreateParams[chId];

            decPrm->dpbBufSizeInFrames  = DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT;
            decPrm->algCreateStatus     = DEC_LINK_ALG_CREATE_STATUS_CREATE;
            decPrm->decodeFrameType     = DEC_LINK_DECODE_ALL;

            decPrm->processCallLevel    = DEC_LINK_FRAMELEVELPROCESSCALL;
            decPrm->targetMaxWidth      = maxWidth;
            decPrm->targetMaxHeight     = maxHeight;
            decPrm->numBufPerCh         = 8;
            decPrm->defaultDynamicParams.targetBitRate = 10*1000*1000;
            decPrm->defaultDynamicParams.targetFrameRate = fps;
            decPrm->fieldMergeDecodeEnable = FALSE;

            /* H.264 */
            decPrm->format = SYSTEM_IVIDEO_H264HP;
            decPrm->profile = 3;
            decPrm->displayDelay = 0;
        }
        ChainsCommon_Sfm_SetDecLinkCallback(pDecPrm);
    }
}
/**
 *******************************************************************************
 * \brief   Set create parameters for NullSrc
 *******************************************************************************
*/
Void chains_networkRxDecDisplay_SetNullSrcPrms(
                                     UInt32 maxWidth,
                                     UInt32 maxHeight,
                                     UInt32 numCh)
{
}

#ifdef TDA2EX_BUILD
/**
 *******************************************************************************
 *
 * \brief   This function selectes the ethernet port & PHY muxes for the use case.
 *          For TDA2EX RevA & RevB we use PHY1 along with Port0.
 *          For RevC we use PHY0/1 depending on use-case.
 *              for 16bit HDMI capture  - use Ethernet port 0 (PHY0)
 *              for 4-ch LVDS           - use Ethernet port 1 (PHY1)
 * \return  None
 *******************************************************************************
*/
void ChainsCommon_tda2exSelectPHY(Chains_CaptureSrc captureSrc)
{
    Bsp_BoardRev boardRev = Bsp_boardGetBaseBoardRev();

    if ( (BSP_BOARD_REV_B == boardRev) || (BSP_BOARD_REV_A == boardRev) )
    {
        Bsp_boardSelectDevice(BSP_DRV_ID_ENET_PHY_DP83865,
                              BSP_DEVICE_ENET_PHY_DP83865_INST_ID_0);
    }
    else
    {
        if ((CHAINS_CAPTURE_SRC_HDMI_1080P == captureSrc) ||
            (CHAINS_CAPTURE_SRC_HDMI_720P == captureSrc) )
        {
            Bsp_boardSelectDevice(BSP_DRV_ID_ENET_PHY_DP83865,
                                  BSP_DEVICE_ENET_PHY_DP83865_INST_ID_0);
        }
        else
        {
            Bsp_boardSelectDevice(BSP_DRV_ID_ENET_PHY_DP83865,
                                  BSP_DEVICE_ENET_PHY_DP83865_INST_ID_1);
        }
    }
}
#endif
