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
#include "chains_issIspSimcop_Display_priv.h"
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include <src/rtos/iss/include/app_util_iss.h>


/*
 * AEWB algorithm memory requirement cannot be calculated upfront.
 * This size is known by running the use-case once with large size
 * and then checking the log for unused memory in AEWB algorithm
 */
#define ALG_AEWB_MEM_SIZE                           (896*1024)


Int32 Utils_fileWriteFile(char *fileName, Uint8 *addr, Uint32 size);



/* returns 0 if does not exist, 1 if it does */
Int32 xUtils_fileExists( char *fileName )
{
    Int32 retVal = 0;
    Int32 hndlFile;

    hndlFile = File_open(fileName, "rb");

    if(hndlFile < 0)
    {
    retVal = 0;
    } else {
    retVal = 1;
    }
    File_close( hndlFile );

    return retVal;
}

/* creates a filepath from an index and the fmt with a %u in it
 * tries to find the next available unused value
 */
Int32 xUtils_nextAvailableFile( char * buf, char * fmt, Int32 theIndex )
{
sprintf( buf, fmt, theIndex );

while( xUtils_fileExists( buf ) && theIndex < 9999 )
{
Vps_printf( "filename %s %d exists... skipping\n", buf, theIndex );
theIndex++;
    sprintf( buf, fmt, theIndex );
}

if( theIndex >= 9999 ) {
theIndex = 0;
    sprintf( buf, fmt, theIndex );
}
return theIndex;
}

Int32 lastExposureTime = 0;

Int32 xUtils_fileWriteInfo( char * filename, char * extra )
{
Int32 status = 0;
char buf [200];

sprintf( buf, "%s, %u, %s\n", filename, lastExposureTime, extra );

status = Utils_fileWriteFile( filename, (Uint8 *)buf, strlen( buf ));

return status;
}


/**
 *******************************************************************************
 *
 *  \brief  SingleCameraFrameCopyObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issIspSimcop_DisplayObj  ucObj;

    IssM2mSimcopLink_ConfigParams   simcopConfig;
    vpsissldcConfig_t               ldcCfg;
    vpsissvtnfConfig_t              vtnfCfg;

    UInt32                          captureOutWidth;
    UInt32                          captureOutHeight;
    UInt32                          displayWidth;
    UInt32                          displayHeight;

    Chains_Ctrl                    *chainsCfg;

    IssM2mSimcopLink_OperatingMode  simcopMode;
    Bool                            bypassVtnf;
    Bool                            bypassLdc;

    AppUtils_Obj             appSensInfo;
} chains_issIspSimcop_DisplayAppObj;


char gChains_IssIspSimcop_Display_runTimeMenu[] = {
"\r\n "
"\r\n ===================="
"\r\n Chains Run-time Menu"
"\r\n ===================="
"\r\n "
"\r\n 0: Stop Chain"
"\r\n "
"\r\n 1: Toggle VTNF ON/OFF"
"\r\n 2: Toggle LDC  ON/OFF"
"\r\n 3: Save Captured Frame"
"\r\n 4: Save SIMCOP Output Frame"
"\r\n 5: Save ISP Output Frame"
#ifdef ISS_ENABLE_DEBUG_TAPS
"\r\n 6: Enable Resizer Output"
"\r\n 7: Enable IPIPE Output"
"\r\n 8: Enable GLBCE Output"
"\r\n 9: Enable IPIPEIF Output"
"\r\n a: Enable Intermediate Output"
#endif
"\r\n "
"\r\n p: Print Performance Statistics "
"\r\n "
"\r\n Enter Choice: "
"\r\n "
};

/*
 * This function shows an example of allocating memory for
 * a link from within the use-case instead of from within the link
 *
 * This allows user's to potentially allocate memory statically outside of
 * link implementation and then pass the memory to the link during use-case
 * create.
 *
 * If user wants the link to allocate memory then dont set below parameters
 * <link create params>.memAllocInfo.memSize,
 * <link create params>.memAllocInfo.memAddr
 */
Void chains_issIspSimcop_Display_SetMemAllocInfo(
                    chains_issIspSimcop_DisplayAppObj *pObj)
{
    UInt32 align = SYSTEM_BUFFER_ALIGNMENT; /* 32 byte alignment*/
    IssCaptureLink_CreateParams             *pIssCapturePrm;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    IssRszLink_CreateParams                 *pIssRszPrm;
    IssM2mSimcopLink_CreateParams           *pIssM2mSimcopPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    pIssCapturePrm    = &pObj->ucObj.IssCapturePrm;
    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pIssRszPrm        = &pObj->ucObj.IssM2mResizerPrm;
    pIssM2mSimcopPrm  = &pObj->ucObj.IssM2mSimcopPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;


    pIssCapturePrm->memAllocInfo.memSize =
          SystemUtils_align(pObj->captureOutWidth, align)
        * pObj->captureOutHeight
        * 2 /* 16-bit per pixel */
        * (pIssCapturePrm->outParams[0].numOutBuf+1)
            /* +1 for RAW data dump */
        ;

    pAlg_IssAewbPrm->memAllocInfo.memSize = ALG_AEWB_MEM_SIZE;

    pIssM2mIspPrm->memAllocInfo.memSize = 0;

    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A])
    {
#ifdef ISS_ENABLE_DEBUG_TAPS
        /* RSZ A output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszA, align)
            * pIssM2mIspPrm->channelParams[0].outParams.heightRszA
            * 2 /* YUV420/422/RAW */
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
#else
        /* RSZ A output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszA, align)
            * pIssM2mIspPrm->channelParams[0].outParams.heightRszA
            * 1.5 /* YUV420SP */
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
#endif
    }

    if( pIssM2mIspPrm->channelParams[0].operatingMode
          == ISSM2MISP_LINK_OPMODE_2PASS_WDR
       )
    {
        /* Intermediate buffer in 2 pass WDR mode */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pObj->captureOutWidth, align)
            * pObj->captureOutHeight
            * 2 /* 16-bit per pixel */
            ;
    }

    if( pIssM2mIspPrm->channelParams[0].operatingMode
          == ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED
       )
    {
        /* Intermediate buffer in 2 pass WDR mode */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].wdrOffsetPrms.width, align)
            * pIssM2mIspPrm->channelParams[0].wdrOffsetPrms.height
            * 2 /* 16-bit per pixel */
            ;
    }

    if (pIssM2mIspPrm->allocBufferForDump)
    {
        /* For Dumping Output frame */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pObj->captureOutWidth, align)
            * pObj->captureOutHeight
            * 2 /* 16-bit per pixel */
            ;
    }

    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B])
    {
        /* RSZ B output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszB, align)
            * pIssM2mIspPrm->channelParams[0].outParams.heightRszB
            * 1.5 /* YUV420SP */
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
    }

    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_H3A])
    {
        /* H3A output */
        pIssM2mIspPrm->memAllocInfo.memSize +=
              ((pIssM2mIspPrm->channelParams[0].outParams.widthRszA/
                  pIssM2mIspPrm->channelParams[0].outParams.winWidthH3a)+1)
            * ((pIssM2mIspPrm->channelParams[0].outParams.heightRszA/
                  pIssM2mIspPrm->channelParams[0].outParams.winHeightH3a)+1)
            * ( sizeof(IssAwebH3aOutSumModeOverlay)
              + sizeof(IssAwebH3aOutUnsatBlkCntOverlay) )
            * pIssM2mIspPrm->channelParams[0].numBuffersPerCh
            ;
    }

/* To support WDR, two sets of statistics must be produced, one for short exposure and the other one for long exposure
    that's why there is a factor 2
    */
    if(pIssM2mIspPrm->channelParams[0].enableOut[ISSM2MISP_LINK_OUTPUTQUE_H3A_AF])
    {
        pIssM2mIspPrm->memAllocInfo.memSize +=  SystemUtils_align(2*pIssM2mIspPrm->channelParams[0].outParams.paxelNumHaf
            *pIssM2mIspPrm->channelParams[0].outParams.paxelNumVaf*sizeof(IssAfH3aOutOverlay), 128U) /* DSP cache requires 128 bytes alignment */
            *pIssM2mIspPrm->channelParams[0].numBuffersPerCh;
    }

    pIssRszPrm->memAllocInfo.memSize =
          SystemUtils_align(pIssRszPrm->channelParams[0].outParams.widthRszA, align)
        * pIssRszPrm->channelParams[0].outParams.heightRszA
        * 1.5 /* YUV420SP */
        * pIssRszPrm->channelParams[0].numBuffersPerCh
        ;

    pIssM2mSimcopPrm->memAllocInfo.memSize =
          SystemUtils_align(pIssM2mIspPrm->channelParams[0].outParams.widthRszA, align)
        * pIssM2mIspPrm->channelParams[0].outParams.heightRszA
        * 1.5
        * (pIssM2mSimcopPrm->channelParams[0].numBuffersPerCh+1)
           /* +1 for YUV data dump */
        ;

    pIssCapturePrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssCapturePrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssCapturePrm->memAllocInfo.memAddr!=NULL);

    pAlg_IssAewbPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pAlg_IssAewbPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pAlg_IssAewbPrm->memAllocInfo.memAddr!=NULL);

    pIssM2mIspPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssM2mIspPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssM2mIspPrm->memAllocInfo.memAddr!=NULL);

    pIssRszPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssRszPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssRszPrm->memAllocInfo.memAddr!=NULL);

    pIssM2mSimcopPrm->memAllocInfo.memAddr =
        (UInt32)Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pIssM2mSimcopPrm->memAllocInfo.memSize,
                align
            );
    UTILS_assert(pIssM2mSimcopPrm->memAllocInfo.memAddr!=NULL);
}

/*
 * This function free's memory allocated by the use-case, if any
 */
Void chains_issIspSimcop_Display_FreeMemory(
                    chains_issIspSimcop_DisplayAppObj *pObj)
{
    Int32 status;
    IssCaptureLink_CreateParams             *pIssCapturePrm;
    IssM2mIspLink_CreateParams              *pIssM2mIspPrm;
    IssRszLink_CreateParams                 *pIssRszPrm;
    IssM2mSimcopLink_CreateParams           *pIssM2mSimcopPrm;
    AlgorithmLink_IssAewbCreateParams       *pAlg_IssAewbPrm;

    pIssCapturePrm    = &pObj->ucObj.IssCapturePrm;
    pIssM2mIspPrm     = &pObj->ucObj.IssM2mIspPrm;
    pIssRszPrm        = &pObj->ucObj.IssM2mResizerPrm;
    pIssM2mSimcopPrm  = &pObj->ucObj.IssM2mSimcopPrm;
    pAlg_IssAewbPrm   = &pObj->ucObj.Alg_IssAewbPrm;

    if(pIssCapturePrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssCapturePrm->memAllocInfo.memAddr,
                    pIssCapturePrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pAlg_IssAewbPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pAlg_IssAewbPrm->memAllocInfo.memAddr,
                    pAlg_IssAewbPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pIssM2mIspPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssM2mIspPrm->memAllocInfo.memAddr,
                    pIssM2mIspPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pIssRszPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssRszPrm->memAllocInfo.memAddr,
                    pIssRszPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }

    if(pIssM2mSimcopPrm->memAllocInfo.memAddr)
    {
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    (Ptr)pIssM2mSimcopPrm->memAllocInfo.memAddr,
                    pIssM2mSimcopPrm->memAllocInfo.memSize
            );
        UTILS_assert(status==0);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Display Create Parameters
 *
 *          This function is used to set the Display params.
 *          It is called in Create function. It is advisable to have
 *          chains_issIspSimcop_Display_ResetLinkPrms prior to set params
 *          so all the default params get set.
 *
 * \param   pPrm         [IN]    DisplayLink_CreateParams
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_SetDisplayPrms(
                                    DisplayLink_CreateParams *pPrm_Video,
                                    DisplayLink_CreateParams *pPrm_Grpx,
                                    DisplayLink_CreateParams *pPrm_VideoRszB,
                                    Chains_DisplayType displayType,
                                    UInt32 displayWidth,
                                    UInt32 displayHeight,
                                    UInt32 captureWidth,
                                    UInt32 captureHeight)
{
    UInt32 dispWidth, dispHeight;

    if(pPrm_Video)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Video->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        /* To maintain the aspect ratio, change the display tarWidth */
        dispWidth = captureWidth * displayHeight / captureHeight;
        dispHeight = displayHeight;

        if (dispWidth > displayWidth)
        {
            dispWidth = displayWidth;
            dispHeight = displayWidth * captureHeight / captureWidth;
        }


        pPrm_Video->rtParams.tarWidth  = dispWidth;
        pPrm_Video->rtParams.tarHeight = dispHeight;
        pPrm_Video->rtParams.posX      = (displayWidth - dispWidth) / 2U;
        pPrm_Video->rtParams.posY      = (displayHeight - dispHeight) / 2U;

        pPrm_Video->displayId          = DISPLAY_LINK_INST_DSS_VID1;
    }

    if(pPrm_VideoRszB)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_VideoRszB->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_VideoRszB->rtParams.tarWidth  = displayWidth/3;
        pPrm_VideoRszB->rtParams.tarHeight = displayHeight/3;
        pPrm_VideoRszB->rtParams.posX = displayWidth -
            pPrm_VideoRszB->rtParams.tarWidth - 10;
        pPrm_VideoRszB->rtParams.posY = displayHeight -
            pPrm_VideoRszB->rtParams.tarHeight - 10;
        pPrm_VideoRszB->displayId = DISPLAY_LINK_INST_DSS_VID2;
    }

    if(pPrm_Grpx)
    {
        if((displayType == CHAINS_DISPLAY_TYPE_SDTV_NTSC) ||
          (displayType == CHAINS_DISPLAY_TYPE_SDTV_PAL))
        {
            pPrm_Grpx->displayScanFormat = SYSTEM_SF_INTERLACED;
        }

        pPrm_Grpx->displayId = DISPLAY_LINK_INST_DSS_GFX1;
    }
}

Void chains_issIspSimcop_Display_SetSimcopConfig(
            chains_issIspSimcop_DisplayAppObj *pObj)
{
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    IssUtils_InitSimcopConfig(
        &pObj->simcopConfig, pObj->bypassLdc, pObj->bypassVtnf);

    IssUtils_SetimcopLdcVtnfRtConfig(
        &pObj->ldcCfg,
        &pObj->vtnfCfg,
        pObj->bypassLdc,
        pObj->bypassVtnf);

    /* MUST be called after link create and before link start */
    System_linkControl(
            pObj->ucObj.IssM2mSimcopLinkID,
            ISSM2MSIMCOP_LINK_CMD_SET_SIMCOPCONFIG,
            &pObj->simcopConfig,
            sizeof(pObj->simcopConfig),
            TRUE);
}


Void chains_issIspSimcop_Display_SetIspConfig(
            chains_issIspSimcop_DisplayAppObj *pObj)
{
    appSetDefaultIspParams(&pObj->appSensInfo);
    appSetIspParamsFromDCC(&pObj->appSensInfo);
}

Void chains_issIspSimcop_Display_setMuxes(
            chains_issIspSimcop_DisplayAppObj *pObj)
{
    /* Setup PinMux */
    ChainsPlatform_SetPinMux(pObj->chainsCfg->sensorName);

    /* Init Board Mux */
    ChainsBoard_SetBoardMux(pObj->chainsCfg->sensorName);
}

Void chains_issIspSimcop_Display_SetIssRszPrms(
        IssRszLink_CreateParams *issRszPrms,
        UInt32 outWidth,
        UInt32 outHeight)
{
    IssRszLink_ChannelParams *chPrms;

    chPrms = issRszPrms->channelParams;

    chPrms->enableOut[0U] = TRUE;
    chPrms->outParams.heightRszA = outHeight;
    chPrms->outParams.widthRszA = outWidth;
    chPrms->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_SetAppPrms(
    chains_issIspSimcop_DisplayObj *pUcObj, Void *appObj)
{
    chains_issIspSimcop_DisplayAppObj *pObj
        = (chains_issIspSimcop_DisplayAppObj*)appObj;

    ChainsCommon_GetDisplayWidthHeight(
        pObj->chainsCfg->displayType,
        &pObj->displayWidth,
        &pObj->displayHeight
        );

    pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC_VTNF;
    pObj->bypassVtnf = FALSE;
    pObj->bypassLdc  = FALSE;

    if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
        (pObj->chainsCfg->issVtnfEnable == TRUE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
        pObj->bypassVtnf = FALSE;
        pObj->bypassLdc  = TRUE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == TRUE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_LDC;
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = FALSE;
    }
    else if ((pObj->chainsCfg->issLdcEnable == FALSE) &&
             (pObj->chainsCfg->issVtnfEnable == FALSE))
    {
        pObj->simcopMode = ISSM2MSIMCOP_LINK_OPMODE_VTNF;
        pObj->bypassVtnf = TRUE;
        pObj->bypassLdc  = TRUE;
    }

    /* Initialize Simcop Pointers */
    pObj->simcopConfig.ldcConfig = &pObj->ldcCfg;
    pObj->simcopConfig.vtnfConfig = &pObj->vtnfCfg;

    /* Create the sensor now */
    strncpy(pObj->appSensInfo.sensorName, pObj->chainsCfg->sensorName,
        ISS_SENSORS_MAX_NAME);
    pObj->appSensInfo.numCh = 1;
    pObj->appSensInfo.ispOpMode = pObj->chainsCfg->ispOpMode;
    pObj->appSensInfo.simcopOpMode = pObj->simcopMode;
    pObj->appSensInfo.numCSI2Inst = 1;
    appCreateISSSensor(&pObj->appSensInfo);

    appInitIssCaptParams(&pObj->appSensInfo, pUcObj->IssCaptureLinkID,
        &pUcObj->IssCapturePrm);
    appInitIssIspParams(&pObj->appSensInfo, pUcObj->IssM2mIspLinkID,
        &pUcObj->IssM2mIspPrm);
    appInitIssSimcopParams(&pObj->appSensInfo, pUcObj->IssM2mSimcopLinkID,
        &pUcObj->IssM2mSimcopPrm);
    appInitIssAewbParams(&pObj->appSensInfo, pUcObj->Alg_IssAewbLinkID,
        &pUcObj->Alg_IssAewbPrm);

    /* Resizer B output will be shown as 1/3rd of display size */
    pUcObj->IssM2mIspPrm.channelParams[0u].outParams.widthRszB  =
        (pObj->displayWidth / 3) & (~0x1U);
    pUcObj->IssM2mIspPrm.channelParams[0u].outParams.heightRszB =
        (pObj->displayHeight / 3) & (~0x1U);

    /* Display requires around 4 buffers for 60fps chain, so increasing
       simcop output buffers to 4 */
    pUcObj->IssM2mSimcopPrm.channelParams[0u].numBuffersPerCh = 4;
    pUcObj->IssM2mResizerPrm.channelParams[0u].numBuffersPerCh = 4U;

    pUcObj->IssM2mIspPrm.allocBufferForDump = TRUE;
    pUcObj->IssCapturePrm.allocBufferForRawDump = TRUE;

    ChainsCommon_SetGrpxSrcPrms(&pUcObj->GrpxSrcPrm,
                                pObj->displayWidth,
                                pObj->displayHeight);

    chains_issIspSimcop_Display_SetIssRszPrms(
        &pUcObj->IssM2mResizerPrm,
        ((pObj->displayWidth/3) & ~0x1), /* Even value needed */
        (pObj->displayHeight/3));

    pObj->captureOutWidth = pUcObj->IssCapturePrm.outParams[0U].width;
    pObj->captureOutHeight = pUcObj->IssCapturePrm.outParams[0U].height;

    /*
     * call this function to allocate memory from use-case
     * if this function is not called memory is allocated
     * from within the respective link
     */
    chains_issIspSimcop_Display_SetMemAllocInfo(pObj);

    chains_issIspSimcop_Display_SetDisplayPrms(
        &pUcObj->Display_VideoPrm,
            &pUcObj->Display_GrpxPrm,
            &pUcObj->Display_VideoRszBPrm,
            pObj->chainsCfg->displayType,
            pObj->displayWidth,
            pObj->displayHeight,
            pUcObj->IssM2mIspPrm.channelParams[0U].outParams.widthRszA,
            pUcObj->IssM2mIspPrm.channelParams[0U].outParams.heightRszA);

    ChainsCommon_StartDisplayCtrl(
        pObj->chainsCfg->displayType,
        pObj->displayWidth,
        pObj->displayHeight);
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
 * \param   pObj  [IN] chains_issIspSimcop_DisplayAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_StartApp(chains_issIspSimcop_DisplayAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    /* Sets the Simcop Config also */
    chains_issIspSimcop_Display_SetIspConfig(pObj);
    chains_issIspSimcop_Display_SetSimcopConfig(pObj);

    chains_issIspSimcop_Display_setMuxes(pObj);

    appStartIssSensorSerDes(&pObj->appSensInfo);

    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);

    chains_issIspSimcop_Display_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
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
 * \param   pObj   [IN]   chains_issIspSimcop_DisplayAppObj
 *
 *******************************************************************************
*/
Void chains_issIspSimcop_Display_StopAndDeleteApp(chains_issIspSimcop_DisplayAppObj *pObj)
{
    chains_issIspSimcop_Display_Stop(&pObj->ucObj);
    chains_issIspSimcop_Display_Delete(&pObj->ucObj);

    chains_issIspSimcop_Display_FreeMemory(pObj);

    ChainsCommon_StopDisplayCtrl();

    appStopISSSensor(&pObj->appSensInfo);

    appDeleteISSSensor(&pObj->appSensInfo);

    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
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
Void Chains_issIspSimcop_Display(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    chains_issIspSimcop_DisplayAppObj chainsObj;
    IssM2mIspLink_IspOutputTapParams ispTapPrms;
    Int32 CapImCounter = 0;
    char fName[128];
    Int32 status = 0;
    IssCaptureLink_GetSaveFrameStatus rawSaveFrameStatus;
    IssM2mSimcopLink_GetSaveFrameStatus simcopSaveFrameStatus;
    IssM2mIspLink_GetSaveFrameStatus ispSaveFrameStatus;

    chainsObj.bypassVtnf = 0; /* KW error fix */
    chainsObj.bypassLdc  = 0; /* KW error fix */


    Vps_printf(" Entered Chains_issIspSimcop_Display \n");

    if (TRUE == IssM2mIspLink_IsWdrMode(chainsCfg->ispOpMode))
    {
        Vps_printf(" CHAINS: Please make sure BSP is build with WDR and LDC enabled !!!\n");
    }

    chainsObj.chainsCfg = chainsCfg;

    /* Initialize Video Sensor, so that Algorithm can use Params
       from Vid Sensor layer */
    chains_issIspSimcop_Display_Create(&chainsObj.ucObj, &chainsObj);
    ChainsCommon_SetIssCaptureErrorHandlingCb(chainsObj.ucObj.IssCaptureLinkID);
    chains_issIspSimcop_Display_StartApp(&chainsObj);

    while(!done)
    {
        Vps_printf(gChains_IssIspSimcop_Display_runTimeMenu);

        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case '1':
                /* toogle VTNF ON/OFF */
                chainsObj.bypassVtnf ^= 1;
                chains_issIspSimcop_Display_SetSimcopConfig(&chainsObj);
                if(chainsObj.bypassVtnf)
                {
                    Vps_printf(" CHAINS: VTNF is BYPASSED !!!\n");
                }
                else
                {
                    Vps_printf(" CHAINS: VTNF is ENABLED !!!\n");
                }
                break;
            case '2':
                /* toogle LDC ON/OFF */
                chainsObj.bypassLdc ^= 1;
                chains_issIspSimcop_Display_SetSimcopConfig(&chainsObj);
                if(chainsObj.bypassLdc)
                {
                    Vps_printf(" CHAINS: LDC is BYPASSED !!!\n");
                }
                else
                {
                    Vps_printf(" CHAINS: LDC is ENABLED !!!\n");
                }
                break;

            case '3':
                {
                /* Send command to Capture Link to save a frame */
                UInt32 chId = 0U;
                System_linkControl(
                        chainsObj.ucObj.IssCaptureLinkID,
                        ISSCAPTURE_LINK_CMD_SAVE_FRAME,
                        &chId,
                        sizeof(chId),
                        TRUE);

                        do {
                              System_linkControl(
                              chainsObj.ucObj.IssCaptureLinkID,
                              ISSCAPTURE_LINK_CMD_GET_SAVE_FRAME_STATUS,
                              &rawSaveFrameStatus,
                              sizeof(IssCaptureLink_GetSaveFrameStatus),
                              TRUE);

                        } while (rawSaveFrameStatus.isSaveFrameComplete == FALSE);
                        CapImCounter = xUtils_nextAvailableFile( fName, "raw%04u.raw", CapImCounter );

                        status = Utils_fileWriteFile( fName, (UInt8*)rawSaveFrameStatus.bufAddr, rawSaveFrameStatus.bufSize);

                        sprintf( fName, "raw%04u.txt", CapImCounter );

                        if(status)
                        {
                            Vps_printf("Error %d: Error performing file write\n",status);
                            xUtils_fileWriteInfo( fName, "RAW, Error" );
                        } else {
                            Vps_printf("Wrote image %s to file\n",fName);
                            xUtils_fileWriteInfo( fName, "RAW, OK" );
                    }

                break;
                }
            case '4':
                /* Send command to Capture Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mSimcopLinkID,
                        ISSM2MSIMCOP_LINK_CMD_SAVE_FRAME,
                        NULL,
                        0,
                        TRUE);
                        simcopSaveFrameStatus.chId = 0;
                        do {
                              System_linkControl(
                              chainsObj.ucObj.IssM2mSimcopLinkID,
                              ISSM2MSIMCOP_LINK_CMD_GET_SAVE_FRAME_STATUS,
                              &simcopSaveFrameStatus,
                              sizeof(IssM2mSimcopLink_GetSaveFrameStatus),
                              TRUE);

                        } while (simcopSaveFrameStatus.isSaveFrameComplete == FALSE);
                        CapImCounter = xUtils_nextAvailableFile( fName, "SIMCOP%04u.yuv", CapImCounter );

                        status = Utils_fileWriteFile( fName, (UInt8*)simcopSaveFrameStatus.bufAddr, simcopSaveFrameStatus.bufSize);

                        sprintf( fName, "SIMCOP%04u.txt", CapImCounter );

                        if(status)
                        {
                            Vps_printf("Error %d: Error performing file write\n",status);
                            xUtils_fileWriteInfo( fName, "NV12, Error" );
                        } else {
                            Vps_printf("Wrote image %s to file\n",fName);
                            xUtils_fileWriteInfo( fName, "NV12, OK" );
                    }

                break;
            case '5':
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SAVE_FRAME,
                        NULL,
                        0,
                        TRUE);
                        ispSaveFrameStatus.chId = 0;

                        do {
                              System_linkControl(
                              chainsObj.ucObj.IssM2mIspLinkID,
                              ISSM2MISP_LINK_CMD_GET_SAVE_FRAME_STATUS,
                              &ispSaveFrameStatus,
                              sizeof(IssCaptureLink_GetSaveFrameStatus),
                              TRUE);

                        } while (ispSaveFrameStatus.isSaveFrameComplete == FALSE);
                        CapImCounter = xUtils_nextAvailableFile( fName, "ISP%04u.yuv", CapImCounter );

                        status = Utils_fileWriteFile( fName, (UInt8*)ispSaveFrameStatus.bufAddr, ispSaveFrameStatus.bufSize);

                        sprintf( fName, "ISP%04u.txt", CapImCounter );

                        if(status)
                        {
                            Vps_printf("Error %d: Error performing file write\n",status);
                            xUtils_fileWriteInfo( fName, "NV12, Error" );
                        } else {
                            Vps_printf("Wrote image %s to file\n",fName);
                            xUtils_fileWriteInfo( fName, "NV12, OK" );
                    }

                break;
            case '6':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_RESIZER_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case '7':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_IPIPE_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case '8':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_GLBCE_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case '9':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_IPIPEIF_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case 'a':
                ispTapPrms.chId = 0U;
                ispTapPrms.outputTapModule = ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT;
                /* Send command to ISP Link to save a frame */
                System_linkControl(
                        chainsObj.ucObj.IssM2mIspLinkID,
                        ISSM2MISP_LINK_CMD_SET_TAP_PARAMS,
                        &ispTapPrms,
                        sizeof(ispTapPrms),
                        TRUE);
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_issIspSimcop_Display_printStatistics(&chainsObj.ucObj);
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_issIspSimcop_Display_StopAndDeleteApp(&chainsObj);

}

