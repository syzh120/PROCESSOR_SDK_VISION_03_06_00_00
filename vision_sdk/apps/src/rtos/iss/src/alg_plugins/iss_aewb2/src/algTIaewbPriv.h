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

#ifndef _ISS_AEWB1_ALG_PRIV_H
#define _ISS_AEWB1_ALG_PRIV_H

#include <include/link_api/system_const.h>
#include <include/link_api/issIspConfiguration.h>
#include <algorithmLink_issAewb.h>

#define TI_AEW_WIN_HZ_CNT               (64u)
#define TI_AEW_WIN_VT_CNT               (64u)

#define ALG_AEWB_OFF            0
#define ALG_AEWB_AE             1
#define ALG_AEWB_AWB            2
#define ALG_AEWB_AEWB           3

#define ALG_VIDEO_MODE_NTSC   0
#define ALG_VIDEO_MODE_PAL    1

#define ALG_AWB_MODE_INDOOR   0
#define ALG_AWB_MODE_OUTDOOR  1

#define ALG_AE_MODE_DAY      0
#define ALG_AE_MODE_NIGHT    1

#define IMAGE_TUNE_AWB_RGB_SIZE    1024

enum {
        VIDEO_NTSC=0,
        VIDEO_PAL
};

enum {
        AEW_DISABLE = 0,
        AEW_ENABLE
};

enum {
        AE_NIGHT = 0,
        AE_DAY
};

enum {
        BACKLIGHT_LOW = 0,
        BACKLIGHT_LOW2,
        BACKLIGHT_NORMAL,
        BACKLIGHT_NORMAL2,
        BACKLIGHT_HIGH,
        BACKLIGHT_HIGH2
};

enum {

        INDOOR = 0,
        OUTDOOR,
        AWB_AUTO
};


typedef enum {
    TI2A_WB_SCENE_MODE_AUTO                = 0,
    TI2A_WB_SCENE_MODE_D65                 = 1,
    TI2A_WB_SCENE_MODE_D55                 = 2,
    TI2A_WB_SCENE_MODE_FLORESCENT          = 3,
    TI2A_WB_SCENE_MODE_INCANDESCENT        = 4
}ti2aWBSceneMode;


typedef struct _aewDataEntry {
        unsigned short window_data[8][8];
        unsigned short unsat_block_ct[8];
}aewDataEntry;

typedef struct
{
    int AutoIris;
    int saturation;
    int sharpness;
    int brightness;
    int contrast;
    int blc;
    int AWBMode;
    int AEMode;
    int Env;
    int Binning;
    int FrameRate;
    int sensorMode;

    AlgorithmLink_IssAewbMode mode;

    unsigned char  *dcc_Default_Param;
    int  dcc_init_done;
    unsigned int dccSize;
    unsigned int AFValue;

    int *g_flickerMem;
    IAEWB_Rgb *rgbData;
    aewDataEntry *aew_data;
    int aewbFrames;
    int reduceShutter, saldre, env_50_60Hz;

    unsigned char weightingMatrix[TI_AEW_WIN_HZ_CNT * TI_AEW_WIN_VT_CNT];
    unsigned char weightingMatrixSpot[TI_AEW_WIN_HZ_CNT * TI_AEW_WIN_VT_CNT];
    unsigned char weightingMatrixCenter[TI_AEW_WIN_HZ_CNT * TI_AEW_WIN_VT_CNT];

    IAE_InArgs    AE_InArgs;
    IAE_OutArgs   AE_OutArgs;
    IAE_DynamicParams aeDynamicParams;

    IAWB_InArgs   AWB_InArgs;
    IAWB_OutArgs  AWB_OutArgs;

    IALG_Handle   handle_ae;
    IALG_Handle   handle_awb;

    IALG_MemRec   memTab_ae[4];
    IALG_MemRec   memTab_awb[4];

    unsigned char *weight;

    IAEWB_StatMat IAEWB_StatMatdata;

    awb_calc_data_t calbData;
    /**< Sensor Specific Calibration Data */

    /* Configurable Parameters */
    int update;
    int flicker_sel; /* <TBR: Uday>Sel between 50/60Hz flicker*/
    int flickerFreq; /*Select custum flicker*/
    int minExposure; /*Mininum Sensor exposure*/
    int maxExposure; /*Maximum Sensor exposure*/
    int stepSize;    /*step size for the exposure variation */
    int aGainMin;    /*Minimum analog Gain*/
    int aGainMax;    /*Maximum Analog gain */
    int dGainMin;    /*Minimum digital gain*/
    int dGainMax;    /*Maximum Digital gain */
    int targetBrightnessMin; /*Minimum target bright ness */
    int targetBrightnessMax; /*Maximum target bright ness */
    int targetBrightness;    /*target brightness to be achieved*/

    int day_night;
    int wbSceneMode;

    int accValue[4];

    System_VideoDataFormat dataFormat;
    int numSteps;

    int isAwbAllocated;
    int isAeAllocated;

    int aewbNumWinH;
    int aewbNumWinV;
    int aewbNumPix;

    int aeDynParamsChanged;
    int awbCalbDataChanged;
} ALG_aewbObj;

Void Alg_setDefaults();


#endif
