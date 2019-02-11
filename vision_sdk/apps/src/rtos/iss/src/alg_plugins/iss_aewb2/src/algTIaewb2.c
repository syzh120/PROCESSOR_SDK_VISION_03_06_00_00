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
 * \file algTIaewb.c
 *
 * \brief  This file contains plug in functions for algorithm plugin
 *         Link
 *
 * \version 0.0 (Nov 2014) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include "../inc/iawb.h"
#include "../inc/iae.h"
#include "./awb_ti.h"
#include "./ae_ti.h"
#include "../inc/TI_aaa_awb.h"
#include "./algTIaewbPriv.h"
#include "../inc/TI_aewb.h"
#include <src/rtos/utils_common/include/utils_mem.h>

/* Enable this macro to use IPNC AEWB implementation */
/* #define ALG_AEWB_USE_CNSR_AEWB_IMPL */

//#define AWB_DEBUG

extern awb_calc_data_t awb_calc_data2;

//static UInt32 numChannels_2A;

typedef enum{
    DRV_IMGS_SENSOR_MODE_640x480 = 0,
    DRV_IMGS_SENSOR_MODE_720x480,
    DRV_IMGS_SENSOR_MODE_800x600,
    DRV_IMGS_SENSOR_MODE_1024x768,
    DRV_IMGS_SENSOR_MODE_1280x720,
    DRV_IMGS_SENSOR_MODE_1280x960,
    DRV_IMGS_SENSOR_MODE_1280x1024,
    DRV_IMGS_SENSOR_MODE_1600x1200,
    DRV_IMGS_SENSOR_MODE_1920x1080,
    DRV_IMGS_SENSOR_MODE_2048x1536,
    DRV_IMGS_SENSOR_MODE_2592x1920
} DRV_IMGS_SENSOR_MODE;


static int TI_2A_config(
    ALG_aewbObj *aewbObj,
    int flicker_detection,
    int saldre);
static int ALG_aewb2Control(ALG_aewbObj *aewbObj, ALG_Output *output);

static void TIAE_applySettings(ALG_aewbObj *aewbObj, ALG_Output *output,
    int actStep, int step);

/** \brief Static inline function to check if the given mode supports AE or not
 *  returns TRUE if AE is supported in given mode or FALSE
 */
static inline UInt32 algIsAeMode(UInt32 mode)
{
    if ((ALGORITHMS_ISS_AEWB_MODE_AE == mode) ||
        (ALGORITHMS_ISS_AEWB_MODE_AEWB == mode))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/** \brief Static inline function to check if the given mode supports AE or not
 *  returns TRUE if AE is supported in given mode or FALSE
 */
static inline UInt32 algIsAwbMode(UInt32 mode)
{
    if ((ALGORITHMS_ISS_AEWB_MODE_AWB == mode) ||
        (ALGORITHMS_ISS_AEWB_MODE_AEWB == mode))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void AlgSetDefaults(ALG_aewbObj *pObj)
{
    pObj->AutoIris   = 0;
    pObj->saturation = 0;
    pObj->sharpness  = 0;
    pObj->brightness = 0;
    pObj->contrast   = 0;
    pObj->blc        = 0;
    pObj->AWBMode    = 0;
    pObj->AEMode     = 0;
    pObj->Env        = 0;
    pObj->Binning    = 0;
    pObj->FrameRate  = 0;

    pObj->dcc_Default_Param = NULL;
    pObj->dcc_init_done     = FALSE;
    pObj->dccSize           = 0;
}

static void Init2ATables(ALG_aewbObj *pObj, UInt32 width, UInt32 height)
{
    int i, j;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
            {
                pObj->weightingMatrix[i*width + j] = 1;
                pObj->weightingMatrixCenter[i*width + j] = 1;
                pObj->weightingMatrixSpot[i*width + j] = 1;
            }
    }
}

void *ALG_aewb2Create(
    AlgorithmLink_IssAewbMode mode,
    int aewbNumWinH, int aewbNumWinV, int aewbNumPix,
    System_VideoDataFormat dataFormat, int numSteps,
    AlgorithmLink_IssAewbAeDynamicParams *aeDynamicPrms,
    AlgorithmLink_IssAewbAwbCalbData *calbData,
    System_LinkMemAllocInfo *pMemAllocInfo,
    UInt32 numChannels)
{
    int numMem;
    int retval;
    IAE_Params aeParams = {0};
    IAWB_Params awbParams = {0};
    ALG_aewbObj *aewbObj = NULL;

    if ((TI_AEW_WIN_HZ_CNT * TI_AEW_WIN_VT_CNT) < (aewbNumWinH*aewbNumWinV))
    {
        return NULL;
    }

    if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
    {
        aewbObj = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                sizeof(ALG_aewbObj),
                2);
    }
    else
    {
        aewbObj = (ALG_aewbObj *)System_allocLinkMemAllocInfo(
                pMemAllocInfo,
                sizeof(ALG_aewbObj),
                2);
    }
    if (NULL == aewbObj)
    {
        printf("Could not allocate memory for AEWB Object\n");
        return NULL;
    }

    memset(aewbObj, 0, sizeof(ALG_aewbObj));

    AlgSetDefaults(aewbObj);

    if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
    {
        aewbObj->rgbData = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                sizeof(IAEWB_Rgb) * aewbNumWinH * aewbNumWinV,
                2);
        aewbObj->aew_data = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                sizeof(aewDataEntry) * (aewbNumWinH * aewbNumWinV + 7) >> 3,
                2);
        aewbObj->g_flickerMem = Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                sizeof(int) * 6*1024,
                2);
    }
    else
    {
        aewbObj->rgbData =
            (IAEWB_Rgb *)System_allocLinkMemAllocInfo(
                pMemAllocInfo,
                sizeof(IAEWB_Rgb) * aewbNumWinH * aewbNumWinV,
                2);
        aewbObj->aew_data =
            (aewDataEntry *)System_allocLinkMemAllocInfo(
                pMemAllocInfo,
                sizeof(aewDataEntry) * (aewbNumWinH * aewbNumWinV + 7) >> 3,
                2);
        aewbObj->g_flickerMem =
            (int *)System_allocLinkMemAllocInfo(
                pMemAllocInfo,
                sizeof(int) * 6*1024,
                2);
    }

    if ((NULL == aewbObj->rgbData) ||
        (NULL == aewbObj->aew_data) ||
        (NULL == aewbObj->g_flickerMem))
    {
        ALG_aewb2Delete(aewbObj, pMemAllocInfo);
        aewbObj = NULL;
        return NULL;
    }

    aewbObj->reduceShutter          = 100;
    aewbObj->saldre                 = 0;
    aewbObj->env_50_60Hz            = VIDEO_PAL;
    aewbObj->mode                   = mode;

    aewbObj->update              = 0;
    aewbObj->flicker_sel         = 0;

    aewbObj->aewbNumWinH = aewbNumWinH;
    aewbObj->aewbNumWinV = aewbNumWinV;
    aewbObj->aewbNumPix = aewbNumPix;

    aewbObj->flickerFreq         = 0;
    aewbObj->minExposure         = 5000;
    aewbObj->maxExposure         = 16667;
    aewbObj->stepSize            = 200;
    aewbObj->aGainMin            = 1000;
    aewbObj->dGainMin            = 128;
    aewbObj->dGainMax            = 4092;
    aewbObj->targetBrightnessMin = 30;
    aewbObj->targetBrightnessMax = 50;
    aewbObj->targetBrightness    = 40;
    aewbObj->dataFormat          = dataFormat;
    aewbObj->numSteps            = numSteps;

    aewbObj->day_night           = AE_DAY;
    aewbObj->blc                 = BACKLIGHT_LOW;
    aewbObj->brightness          = 128;
    aewbObj->contrast            = 128;
    aewbObj->sharpness           = 128;
    aewbObj->saturation          = 128;
    aewbObj->wbSceneMode         = TI2A_WB_SCENE_MODE_AUTO;

    Init2ATables(aewbObj, aewbNumWinH, aewbNumWinV);

    /* AE is not included only in AWB mode */
    if (TRUE == algIsAeMode(mode))
    {
        aewbObj->weight = aewbObj->weightingMatrix;

        aeParams.size = sizeof(aeParams);
        aeParams.numHistory = 10;
        aeParams.numSmoothSteps = 8;
        aeParams.numChannels = numChannels;
        numMem = AE_TI_AE2.ialg.algAlloc((IALG_Params *)&aeParams, NULL,
                                         aewbObj->memTab_ae);
        while(numMem > 0)
        {
            if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
            {
                aewbObj->memTab_ae[numMem-1].base = Utils_memAlloc(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    aewbObj->memTab_ae[numMem-1].size,
                    2);
            }
            else
            {
                aewbObj->memTab_ae[numMem-1].base =
                    (void*)System_allocLinkMemAllocInfo(
                        pMemAllocInfo,
                        aewbObj->memTab_ae[numMem-1].size,
                        2);
            }

            if (NULL == aewbObj->memTab_ae[numMem-1].base)
            {
                ALG_aewb2Delete(aewbObj, pMemAllocInfo);
                return NULL;
            }

            numMem --;
        }

        aewbObj->handle_ae = (IALG_Handle)aewbObj->memTab_ae[0].base;
        retval = AE_TI_AE2.ialg.algInit(aewbObj->handle_ae, aewbObj->memTab_ae,
                                       NULL, (IALG_Params *)&aeParams);
        if(retval == -1)
        {
            ALG_aewb2Delete(aewbObj, pMemAllocInfo);
            printf("AE_TI_AE2.ialg.algInit()\n");
            return NULL;
        }

        /* Set Dynamic Parameters */
        ALG_aewb2SetAeDynParams(aewbObj, aeDynamicPrms);
    }

    /* AWB is not included only in AE mode */
    if (TRUE == algIsAwbMode(mode))
    {
        awbParams.size = sizeof(awbParams);
        awbParams.numHistory = 6;
        numMem = AWB_TI_AWB.ialg.algAlloc((IALG_Params *)&awbParams,
                                          NULL,
                                          aewbObj->memTab_awb);
        while(numMem > 0)
        {
            if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
            {
                aewbObj->memTab_awb[numMem-1].base = Utils_memAlloc(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    aewbObj->memTab_awb[numMem-1].size,
                    2);
            }
            else
            {
                aewbObj->memTab_awb[numMem-1].base =
                    (void*)System_allocLinkMemAllocInfo(
                        pMemAllocInfo,
                        aewbObj->memTab_awb[numMem-1].size,
                        2);
            }

            if (NULL == aewbObj->memTab_awb[numMem-1].base)
            {
                ALG_aewb2Delete(aewbObj, pMemAllocInfo);
                return NULL;
            }

            numMem --;
        }

        aewbObj->handle_awb = (IALG_Handle)aewbObj->memTab_awb[0].base;
        retval = AWB_TI_AWB.ialg.algInit(
                    aewbObj->handle_awb,
                    aewbObj->memTab_awb,
                    NULL,
                    (IALG_Params *)&awbParams);
        if(retval == -1)
        {
            ALG_aewb2Delete(aewbObj, pMemAllocInfo);
            printf("AWB_TI_AWB.ialg.algInit()\n");
            return NULL;
        }

        /* Set the Calibration Data */
        if (NULL != calbData)
        {
            memcpy(&aewbObj->calbData,
                   calbData,
                   sizeof(awb_calc_data_t));
        }
        else
        {
            memcpy(&aewbObj->calbData,
                   &awb_calc_data2,
                   sizeof(awb_calc_data_t));
        }
    }

    aewbObj->IAEWB_StatMatdata.winCtVert  = aewbNumWinV;
    aewbObj->IAEWB_StatMatdata.winCtHorz  = aewbNumWinH;
    aewbObj->IAEWB_StatMatdata.pixCtWin   = aewbNumPix;
    aewbObj->sensorMode = DRV_IMGS_SENSOR_MODE_1280x720;

    retval = TI_2A_config(aewbObj, 0, aewbObj->saldre);
    if(retval == -1)
    {
        ALG_aewb2Delete(aewbObj, pMemAllocInfo);
        aewbObj = NULL;
    }

    return aewbObj;
}

static int TI_2A_config(ALG_aewbObj *aewbObj, int flicker_detection, int saldre)
{
    int retval;

    /* If AE mode is included */
    if (TRUE == algIsAeMode(aewbObj->mode))
    {
        memcpy((void *)&aewbObj->AE_InArgs.statMat,
          (void *)&aewbObj->IAEWB_StatMatdata,
          sizeof(IAEWB_StatMat));

        retval = AE_TI_AE2.control((IAE_Handle)aewbObj->handle_ae,
                            IAE_CMD_SET_CONFIG, &aewbObj->aeDynamicParams,
                            NULL);
        if(retval == -1)
        {
            printf("AE_TI_AE2.control()\n");
            return retval;
        }
        aewbObj->aeDynParamsChanged = FALSE;
    }

    /* If AWB mode is included */
    if (TRUE == algIsAwbMode(aewbObj->mode))
    {
        memcpy((void *)&aewbObj->AWB_InArgs.statMat,
          (void *)&aewbObj->IAEWB_StatMatdata,
          sizeof(IAEWB_StatMat));

        /* Pass calibration data to TI AWB */
        retval = AWB_TI_AWB.control((IAWB_Handle)aewbObj->handle_awb,
                                    TIAWB_CMD_CALIBRATION,
                                    (IAWB_DynamicParams*)&aewbObj->calbData,
                                    NULL);

        if(retval == -1)
        {
            printf("AWB_TI_AWB.control()\n");
            return retval;
        }

        aewbObj->awbCalbDataChanged = FALSE;
    }

    return 0;
}

// 1 AE with ROI
static void GETTING_RGB_BLOCK_VALUE_ROI(ALG_aewbObj   *aewbObj,
                                      unsigned char *curAewbAddr,
                                      IAEWB_Rgb     *rgbData,
                                      aewDataEntry  *aew_data,
                                      int            shift,
                                      int            aew_win_vt_cnt,
                                      int            aew_win_hz_cnt)
{
    unsigned short i,j,k, numWin, idx1, idx2;
    unsigned char *AewbAddr = curAewbAddr; 
    numWin=0;

    for(i = 0; i < aew_win_vt_cnt; i++) {
        for(j = 0; j < aew_win_hz_cnt; j++) {
            IssAwebH3aOutSumModeOverlay *pAewbWinData = (IssAwebH3aOutSumModeOverlay *)curAewbAddr;

            idx1 = numWin/8;
            idx2 = numWin%8;

            aew_data[idx1].window_data[idx2][0] = pAewbWinData->subSampleAcc[0];
            aew_data[idx1].window_data[idx2][1] = pAewbWinData->subSampleAcc[1];
            aew_data[idx1].window_data[idx2][2] = pAewbWinData->subSampleAcc[2];
            aew_data[idx1].window_data[idx2][3] = pAewbWinData->subSampleAcc[3];

            curAewbAddr += sizeof(IssAwebH3aOutSumModeOverlay);

            numWin++;
            if(numWin%8==0)
            {
                IssAwebH3aOutUnsatBlkCntOverlay *pAewbUnsatBlk = (IssAwebH3aOutUnsatBlkCntOverlay*)curAewbAddr;

                for(k=0; k<8;k++)
                    aew_data[idx1].unsat_block_ct[k] = pAewbUnsatBlk->unsatCount[k];

                curAewbAddr += sizeof(IssAwebH3aOutUnsatBlkCntOverlay);
            }
        }

        if ((curAewbAddr - AewbAddr) % 32 == 16)
        {
            curAewbAddr += 16;
        }
    }

    for(i = 0; i < (aew_win_hz_cnt * aew_win_vt_cnt)>>3;i ++)
    {
        for(j = 0; j < 8; j ++)
        {
            if (SYSTEM_DF_BAYER_GRBG == aewbObj->dataFormat)
            {
                rgbData[i * 8 + j].r = aew_data[i].window_data[j][1] >> shift;
                rgbData[i * 8 + j].b = aew_data[i].window_data[j][2] >> shift;
                rgbData[i * 8 + j].g = (aew_data[i].window_data[j][0]
                + aew_data[i].window_data[j][3]+ 1) >> (1 + shift) ;
            }
            else if (SYSTEM_DF_BAYER_RGGB == aewbObj->dataFormat)
            {
                rgbData[i * 8 + j].r = aew_data[i].window_data[j][0] >> shift;
                rgbData[i * 8 + j].b = aew_data[i].window_data[j][3] >> shift;
                rgbData[i * 8 + j].g = (aew_data[i].window_data[j][1]
                + aew_data[i].window_data[j][2]+ 1) >> (1 + shift) ;
            }
            else if (SYSTEM_DF_BAYER_GBRG == aewbObj->dataFormat)
            {
                rgbData[i * 8 + j].r = aew_data[i].window_data[j][2] >> shift;
                rgbData[i * 8 + j].b = aew_data[i].window_data[j][1] >> shift;
                rgbData[i * 8 + j].g = (aew_data[i].window_data[j][0]
                + aew_data[i].window_data[j][3]+ 1) >> (1 + shift) ;
            }
            else /* Data format is SYSTEM_DF_BAYER_BGGR */
            {
                rgbData[i * 8 + j].r = aew_data[i].window_data[j][3] >> shift;
                rgbData[i * 8 + j].b = aew_data[i].window_data[j][0] >> shift;
                rgbData[i * 8 + j].g = (aew_data[i].window_data[j][1]
                + aew_data[i].window_data[j][2]+ 1) >> (1 + shift) ;
            }
        }
    }
}

static void TIAE_applySettings(ALG_aewbObj *aewbObj, ALG_Output *output,
    int actStep, int step)
{
    IAEWB_Ae *nextAe = &aewbObj->AE_OutArgs.nextAe;

    if (step == actStep)
    {
        output->analogGain = nextAe->sensorGain;
        output->digitalGain = nextAe->ipipeGain;
        output->exposureTime = nextAe->exposureTime;
        output->useAeCfg = 1;
    }
    else
    {
        output->useAeCfg = 0;
    }
}

static void TIAE_applySettings_4cam(ALG_aewbObj *aewbObj, ALG_Output *output, int actStep, int step)
{
    if (step == actStep)
    {
        int k;
        for (k = 0; k < 4; k++)
        {
            IAEWB_Ae *nextAe = &aewbObj->AE_OutArgs.cam_nextAe[k];
            output[k].analogGain = nextAe->sensorGain;
            output[k].digitalGain = nextAe->ipipeGain;
            output[k].exposureTime = nextAe->exposureTime;
            output[k].useAeCfg = 1;
        }
    }
    else
    {
        output->useAeCfg = 0;
    }
}


// split ALG_aewbRun() into 2 steps
int ALG_aewb2Run_parseH3a(void *hndl, void *h3aDataVirtAddr, UInt32 chNum, UInt32 nCam_AE)
{
    ALG_aewbObj  *aewbObj = (ALG_aewbObj *)hndl;
    if (( (aewbObj->aewbFrames) % aewbObj->numSteps) == 0)
    {
        int           vt_cnt = aewbObj->IAEWB_StatMatdata.winCtVert;
        int           hz_cnt = aewbObj->IAEWB_StatMatdata.winCtHorz;
        IAEWB_Rgb    *rgbData = aewbObj->rgbData;
        aewDataEntry *aewData = aewbObj->aew_data;
        
        if (nCam_AE > 0)
        {
            vt_cnt /= nCam_AE;
            rgbData = &rgbData[vt_cnt * hz_cnt * chNum];
            aewData = &aewData[(vt_cnt * hz_cnt >> 3) * chNum]; //lose some windows if vt_cnt*hz_cnt is not 8x
        }

        GETTING_RGB_BLOCK_VALUE_ROI(
                aewbObj,
                (unsigned char *)h3aDataVirtAddr,
                rgbData,
                aewData,
                0,
                vt_cnt,
                hz_cnt);
    }
    return 0;
}

int ALG_aewb2Run(void *hndl, void *h3aDataVirtAddr, ALG_Output *output, ALG_Output *cam_output, UInt32 chNum)
{
    ALG_aewbObj *aewbObj = (ALG_aewbObj *)hndl;
    output->useAeCfg = output->useWbCfg = 0;
    cam_output[0].useAeCfg = cam_output[0].useWbCfg  = 0;
    cam_output[1].useAeCfg = cam_output[1].useWbCfg  = 0;
    cam_output[2].useAeCfg = cam_output[2].useWbCfg  = 0;
    cam_output[3].useAeCfg = cam_output[3].useWbCfg  = 0;

    if (( (aewbObj->aewbFrames) % aewbObj->numSteps) == 0)
    {
        /* AWB only mode does not support AE */
        if (TRUE == algIsAeMode(aewbObj->mode))
        {
            output->useAeCfg = 0;
            aewbObj->AE_InArgs.curAe.apertureLevel = 1;
            aewbObj->AE_InArgs.curAe.exposureTime =
                aewbObj->AE_OutArgs.nextAe.exposureTime;
            aewbObj->AE_InArgs.curAe.sensorGain =
                aewbObj->AE_OutArgs.nextAe.sensorGain;
            aewbObj->AE_InArgs.curAe.ipipeGain =
                aewbObj->AE_OutArgs.nextAe.ipipeGain;
            aewbObj->AE_InArgs.curWb.rGain =
                aewbObj->AWB_OutArgs.nextWb.rGain;
            aewbObj->AE_InArgs.curWb.gGain =
                aewbObj->AWB_OutArgs.nextWb.gGain;
            aewbObj->AE_InArgs.curWb.bGain =
                aewbObj->AWB_OutArgs.nextWb.bGain;

            AE_TI_AE2.process(
                    (IAE_Handle)aewbObj->handle_ae,
                    &aewbObj->AE_InArgs,
                    &aewbObj->AE_OutArgs,
                    aewbObj->rgbData,
                    aewbObj->weight,
                    (void*)(&chNum));

            /* TODO: apply in IPIPE */
            output->dGain = aewbObj->AE_OutArgs.nextAe.ipipeGain >> 2;
            TIAE_applySettings(aewbObj, output, 1, 1);
            TIAE_applySettings_4cam(aewbObj, cam_output, 1, 1);

        }

        output->useWbCfg = 0;
        /* AE only mode does not support AWB */
        if (TRUE == algIsAwbMode(aewbObj->mode))
        {
            aewbObj->AWB_InArgs.curWb = aewbObj->AE_InArgs.curWb;
            aewbObj->AWB_InArgs.curAe = aewbObj->AE_InArgs.curAe;

            /* Calling AWB algorithm */
            AWB_TI_AWB.process(
                    (IAWB_Handle)aewbObj->handle_awb,
                    &aewbObj->AWB_InArgs,
                    &aewbObj->AWB_OutArgs,
                    aewbObj->rgbData,
                    NULL);

            output->useWbCfg = 1;
            output->rGain  = aewbObj->AWB_OutArgs.nextWb.rGain >> 3;
            output->grGain = aewbObj->AWB_OutArgs.nextWb.gGain >> 3;
            output->gbGain = aewbObj->AWB_OutArgs.nextWb.gGain >> 3;
            output->bGain  = aewbObj->AWB_OutArgs.nextWb.bGain >> 3;

            output->rOffset   = 0;
            output->grOffset  = 0;
            output->gbOffset  = 0;
            output->bOffset   = 0;

            output->colorTemparature = aewbObj->AWB_OutArgs.nextWb.colorTemp;
        }
    }


    /* If AWB is enabled, change color temp and rgb matrices only
       after exposure time is changed ie AE is converged */
    if ((TRUE == algIsAwbMode(aewbObj->mode)) &&
            ((aewbObj->AE_OutArgs.nextAe.exposureTime ==
              aewbObj->AE_InArgs.curAe.exposureTime) &&
             (aewbObj->AE_OutArgs.nextAe.sensorGain ==
              aewbObj->AE_InArgs.curAe.sensorGain)))
    {
        output->useColorTemp = 1;
        output->colorTemparature = aewbObj->AWB_OutArgs.nextWb.colorTemp;
    }
    else
    {
        output->useColorTemp = 0;
    }

    if (aewbObj->aewbFrames % (aewbObj->numSteps*32) == 0)
    {
#ifdef AE_DEBUG
        if (output->useAeCfg)
        {
            int i;
            for (i = 0; i < 4; i++)
            {
                Vps_printf("Ch Num = %d ExposureTime %d AnalogGain %d Digital Gain %d \n",
                    i, cam_output[i].exposureTime, cam_output[i].analogGain, cam_output[i].digitalGain);
            }
        }
#endif
#ifdef AWB_DEBUG
        if (output->useColorTemp)
        {
            Vps_printf("   WDR = %d Color Temparature = %d\n", chNum, output->colorTemparature);
        }
        if (output->useWbCfg)
        {
            Vps_printf("   WDR = %d Gains %d %d %d %d\n", chNum, output->rGain,
                    output->grGain, output->gbGain, output->bGain);
        }
#endif
    }

    aewbObj->aewbFrames ++;

    ALG_aewb2Control(aewbObj, output);

    return 0;
}


int ALG_aewb2Delete(void *hndl, System_LinkMemAllocInfo *pMemAllocInfo)
{
    int status;
    int numMem;
    ALG_aewbObj *aewbObj = (ALG_aewbObj *)hndl;

    /* No need to do anything */
    if (NULL == aewbObj)
        return 0;

    /* Free up memory allocated for the AE */
    if (NULL != aewbObj->handle_ae)
    {
        numMem = AE_TI_AE2.ialg.algFree(aewbObj->handle_ae, aewbObj->memTab_ae) + 1;
        while(numMem > 0)
        {
            if (NULL != aewbObj->memTab_ae[numMem-1].base)
            {
                if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
                {
                    status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                aewbObj->memTab_ae[numMem-1].base,
                                aewbObj->memTab_ae[numMem-1].size);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                aewbObj->memTab_ae[numMem-1].base = NULL;
            }
            numMem --;
        }
    }

    /* Free up memory allocated for the AWB */
    if (NULL != aewbObj->handle_awb)
    {
        numMem = AWB_TI_AWB.ialg.algFree(aewbObj->handle_awb, aewbObj->memTab_awb) + 1;
        while(numMem > 0)
        {
            if (NULL != aewbObj->memTab_awb[numMem-1].base)
            {
                if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
                {
                    status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                aewbObj->memTab_awb[numMem-1].base,
                                aewbObj->memTab_awb[numMem-1].size);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }
                aewbObj->memTab_awb[numMem-1].base = NULL;
            }
            numMem --;
        }
    }

    if(aewbObj->rgbData != NULL)
    {
        if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
        {
            status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                aewbObj->rgbData,
                sizeof(IAEWB_Rgb) * aewbObj->aewbNumWinH * aewbObj->aewbNumWinV);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
        aewbObj->rgbData = NULL;
    }

    if(aewbObj->aew_data != NULL)
    {
        if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
        {
            status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                aewbObj->aew_data,
                sizeof(aewDataEntry) * (aewbObj->aewbNumWinH *
                aewbObj->aewbNumWinV + 7) >> 3);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
        aewbObj->aew_data = NULL;
    }

    if(aewbObj->g_flickerMem != NULL)
    {
        if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
        {
            Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                          aewbObj->g_flickerMem,
                          sizeof(int) * 6*1024);
        }
        aewbObj->g_flickerMem = NULL;
    }

    if(System_useLinkMemAllocInfo(pMemAllocInfo)==FALSE)
    {
        Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                  aewbObj,
                  sizeof(ALG_aewbObj));
    }
    aewbObj = NULL;
    return 0;
}

int ALG_aewb2SetAeDynParams(void *hndl,
    AlgorithmLink_IssAewbAeDynamicParams *aeDynamicPrms)
{
    UInt32 i;
    ALG_aewbObj *aewbObj = (ALG_aewbObj *)hndl;
    IAE_DynamicParams *aeDynPrms;

    if (NULL == aewbObj)
        return 0;

    if (NULL == aeDynamicPrms)
        return -1;

    /* Copy AE Dynamic Parameters */
    aeDynPrms = &aewbObj->aeDynamicParams;
    aeDynPrms->size = sizeof(IAE_DynamicParams);
    aeDynPrms->numRanges = 0;

    for (i = 0u; i < aeDynamicPrms->numAeDynParams; i ++)
    {
        aeDynPrms->exposureTimeRange[i].min =
            aeDynamicPrms->exposureTimeRange[i].min;
        aeDynPrms->exposureTimeRange[i].max =
            aeDynamicPrms->exposureTimeRange[i].max;
        aeDynPrms->apertureLevelRange[i].min =
            aeDynamicPrms->apertureLevelRange[i].min;
        aeDynPrms->apertureLevelRange[i].max =
            aeDynamicPrms->apertureLevelRange[i].max;
        aeDynPrms->sensorGainRange[i].min =
            aeDynamicPrms->sensorGainRange[i].min;
        aeDynPrms->sensorGainRange[i].max =
            aeDynamicPrms->sensorGainRange[i].max;
        aeDynPrms->ipipeGainRange[i].min =
            aeDynamicPrms->ipipeGainRange[i].min;
        aeDynPrms->ipipeGainRange[i].max =
            aeDynamicPrms->ipipeGainRange[i].max;
    }
    aeDynPrms->numRanges = aeDynamicPrms->numAeDynParams;
    aeDynPrms->targetBrightnessRange.min =
        aeDynamicPrms->targetBrightnessRange.min;
    aeDynPrms->targetBrightnessRange.max =
        aeDynamicPrms->targetBrightnessRange.max;
    aeDynPrms->targetBrightness = aeDynamicPrms->targetBrightness;
    aeDynPrms->thrld = aeDynamicPrms->threshold;
    aeDynPrms->exposureTimeStepSize = aeDynamicPrms->exposureTimeStepSize;
    aeDynPrms->enableBlc = aeDynamicPrms->enableBlc;

    aewbObj->aeDynParamsChanged = TRUE;

    return 0;
}

int ALG_aewb2SetAwbCalbData(void *hndl,
    AlgorithmLink_IssAewbAwbCalbData *calbData)
{
    ALG_aewbObj *aewbObj = (ALG_aewbObj *)hndl;

    if (NULL == aewbObj)
        return 0;

    if (NULL == calbData)
        return -1;

    memcpy(&aewbObj->calbData,
           calbData,
           sizeof(awb_calc_data_t));

    aewbObj->awbCalbDataChanged = TRUE;

    return 0;
}

static int ALG_aewb2Control(ALG_aewbObj *aewbObj, ALG_Output *output)
{
    int retval;

    if (TRUE == aewbObj->aeDynParamsChanged)
    {
        /* If AE mode is included */
        if (TRUE == algIsAeMode(aewbObj->mode))
        {
            retval = AE_TI_AE2.control((IAE_Handle)aewbObj->handle_ae,
                                IAE_CMD_SET_CONFIG, &aewbObj->aeDynamicParams,
                                NULL);
            if(retval == -1)
            {
                printf("AE_TI_AE2.control()\n");
                return retval;
            }
        }

        aewbObj->aeDynParamsChanged = FALSE;
    }

    if (TRUE == aewbObj->awbCalbDataChanged)
    {
        /* If AWB mode is included */
        if (TRUE == algIsAwbMode(aewbObj->mode))
        {
            /* Pass calibration data to TI AWB */
            retval = AWB_TI_AWB.control((IAWB_Handle)aewbObj->handle_awb,
                                        TIAWB_CMD_CALIBRATION,
                                        (IAWB_DynamicParams*)&aewbObj->calbData,
                                        NULL);

            if(retval == -1)
            {
                printf("AWB_TI_AWB.control()\n");
                return retval;
            }
        }

        aewbObj->awbCalbDataChanged = FALSE;
    }

    if (aewbObj->wbSceneMode != TI2A_WB_SCENE_MODE_AUTO)
    {
        int R = 0, G = 0, B = 0;
        int base;

        if(aewbObj->wbSceneMode == TI2A_WB_SCENE_MODE_D65)
        {
            output->colorTemparature = aewbObj->calbData.default_T_H;
            R = aewbObj->calbData.ref_gray_R_1[aewbObj->calbData.default_T_H_index][0];
            G = aewbObj->calbData.ref_gray_G_1[aewbObj->calbData.default_T_H_index][0];
            B = aewbObj->calbData.ref_gray_B_1[aewbObj->calbData.default_T_H_index][0];
        }
        else if(aewbObj->wbSceneMode == TI2A_WB_SCENE_MODE_D55)
        {
            output->colorTemparature = aewbObj->calbData.default_T_MH;
            R = aewbObj->calbData.ref_gray_R_1[aewbObj->calbData.default_T_MH_index][0];
            G = aewbObj->calbData.ref_gray_G_1[aewbObj->calbData.default_T_MH_index][0];
            B = aewbObj->calbData.ref_gray_B_1[aewbObj->calbData.default_T_MH_index][0];
        }
        else if(aewbObj->wbSceneMode == TI2A_WB_SCENE_MODE_FLORESCENT)
        {
            output->colorTemparature = aewbObj->calbData.default_T_ML;
            R = aewbObj->calbData.ref_gray_R_1[aewbObj->calbData.default_T_ML_index][0];
            G = aewbObj->calbData.ref_gray_G_1[aewbObj->calbData.default_T_ML_index][0];
            B = aewbObj->calbData.ref_gray_B_1[aewbObj->calbData.default_T_ML_index][0];
        }
        else if(aewbObj->wbSceneMode == TI2A_WB_SCENE_MODE_INCANDESCENT)
        {
            output->colorTemparature = aewbObj->calbData.default_T_L;
            R = aewbObj->calbData.ref_gray_R_1[aewbObj->calbData.default_T_L_index][0];
            G = aewbObj->calbData.ref_gray_G_1[aewbObj->calbData.default_T_L_index][0];
            B = aewbObj->calbData.ref_gray_B_1[aewbObj->calbData.default_T_L_index][0];
        }

        base = 0;

        if (base < R )
            base = R;

        if (base < G )
            base = G;

        if (base < B )
            base = B;

        output->rGain    = (( base * 512 + R / 2 ) / R)/4;
        output->grGain   = (( base * 512 + G / 2 ) / G)/4;
        output->gbGain   = (( base * 512 + G / 2 ) / G)/4;
        output->bGain    = (( base * 512 + B / 2 ) / B)/4;
    }

    return 0;
}

