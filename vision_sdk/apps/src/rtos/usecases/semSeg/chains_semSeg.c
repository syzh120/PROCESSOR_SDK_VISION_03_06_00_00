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
#include "chains_semSeg_priv.h"
#include "chains_semSeg.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_tidl.h>
#include <src/include/chains_common_osal.h>
#include "itidl_ti.h"
#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */
#define SEMSEG_INPUT_WIDTH          (1024)
#define SEMSEG_INPUT_HEIGHT         (512)

#define DEC_OUT_WIDTH               (1024)
#define DEC_OUT_HEIGHT              (512)

#define SEMSEG_DISPLAY_WIDTH        (1536)
#define SEMSEG_DISPLAY_HEIGHT       (768)
#define SEMSEG_DISPLAY_STARTX       (1920 - SEMSEG_DISPLAY_WIDTH)/2
#define SEMSEG_DISPLAY_STARTY       (64)

/* Semantic Segmenation input fps */
/* This should be based on the TIDL performance on 4 EVEs */
/* It should be less than the cumulative TIDL performance on 4 EVEs */
/* For eg if each TIDL is giving performace of 3 fps then it should be less than (4 x 3)*/
#define SEMSEG_FPS                  (8)

#define SEMSEG_FPS_OPPHIGH          (12)

#define SEMSEG_FPS_OPPNOM           (8)

#define OPP_HIGH_FREQUENCY          (650U)

/* Palettes used for color look up */
#define MAX_NUM_PALETTE             (10)

#define SYNC_DELTA                  (10)

/* The threshold should be more than the TIDL process time */
/* For eg. if TIDL process time is 400 msec then this should be more than 400 msec */
#define SYNC_THRESHOLD              (600)

/* OCMC */
#define OCMC_1_BASE_ADDRESS         (0x40300000U)
#define OCMC_1_SIZE                 (512 * 1024)

#define OCMC_2_BASE_ADDRESS         (0x40400000U)
#define OCMC_2_SIZE                 (1024 * 1024)

#define OCMC_3_BASE_ADDRESS         (0x40500000U)
#define OCMC_3_SIZE                 (1024 * 1024)

#define NET_BIN_FILE                "NET_SEMSEG.BIN"
#define PARAMS_BIN_FILE             "PRM_SEMSEG.BIN"

/* Num of TIDL processing pipelines */
#define NUM_PIPELINES               (4)

/* DSP */
#define TIDL_COREID_DSP1            (1)
#define TIDL_LAYER_GROUPID_DSP1     (1)
#define TIDL_COREID_DSP2            (1)
#define TIDL_LAYER_GROUPID_DSP2     (1)

/* EVE */
#define TIDL_COREID_EVE1            (1)
#define TIDL_LAYER_GROUPID_EVE1     (1)
#define TIDL_COREID_EVE2            (1)
#define TIDL_LAYER_GROUPID_EVE2     (1)
#define TIDL_COREID_EVE3            (1)
#define TIDL_LAYER_GROUPID_EVE3     (1)
#define TIDL_COREID_EVE4            (1)
#define TIDL_LAYER_GROUPID_EVE4     (1)

/* Graphics window is just below the video window */
#define GRAPHICS_WIDTH              (1920)
#define GRAPHICS_HEIGHT             (1080 - SEMSEG_DISPLAY_STARTY - SEMSEG_DISPLAY_HEIGHT)

/*******************************************************************************
 *  STRUCTURES
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  chains_semSegAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    chains_semSegObj ucObj;
    UInt32 displayWidth;
    UInt32 displayHeight;
    Chains_Ctrl *chainsCfg;

    TIDL_CreateParams *pAlgCreateParams;

    UInt16 colPalette[MAX_NUM_PALETTE];

} chains_semSegAppObj;

chains_semSegAppObj gChainsObjSemSeg;

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
static char semSegRunTimeMenu[] = {
"\n "
"\n ===================="
"\n Chains Run-time Menu"
"\n ===================="
"\n "
"\n 0: Stop Chain"
"\n "
"\n 1: Pause Chain"
"\n 2: Resume Chain"
"\n "
"\n 3: Show ALL palettes"
"\n 4: Show only ROAD palette"
"\n 5: Show only PEDESTRIAN palette"
"\n 6: Show only ROAD SIGN palette"
"\n 7: Show only VEHICLE palette"
"\n "
"\n p: Print Statistics"
"\n "
"\n Enter Choice: "
"\n "
};


static Void semSegInit(chains_semSegAppObj *pObj)
{
    /* Read the network file */
    Chains_tidlReadNet(&pObj->pAlgCreateParams->net, NET_BIN_FILE);

    /* Allocate memory for the net */
    Chains_tidlAllocNetParamsMem(&pObj->pAlgCreateParams->net);

    /* Fill the new parameters */
    Chains_tidlFillNetParamsMem(&pObj->pAlgCreateParams->net, PARAMS_BIN_FILE);

    /* Init all the 3 instances of the OCMC */
    Utils_cbufOcmcInit(UTILS_OCMC_RAM1);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM2);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM3);
}


static Void semSegDeInit(chains_semSegAppObj *pObj)
{
    /* Free the net memories */
    Chains_tidlFreeNetParamsMem(&pObj->pAlgCreateParams->net);
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
 * \param   pObj  [IN] chains_semSegAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_semSeg_StartApp(chains_semSegAppObj *pObj)
{
    Chains_memPrintHeapStatus();
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
    chains_semSeg_Start(&pObj->ucObj);
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
 * \param   pObj   [IN]   chains_semSegAppObj
 *
 *******************************************************************************
*/
Void chains_semSeg_StopAndDelete(chains_semSegAppObj *pObj)
{
    chains_semSeg_Stop(&pObj->ucObj);
    chains_semSeg_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

static UInt16 rgb2uv(UInt8 r, UInt8 g, UInt8 b)
{
    Int32 U,V;

    U = ((((b * 0x020C) - (r * 0x0078) - (g * 0x0194)) + 0x0200) >> 10) + 0x80;
    V = ((((r * 0x020C) - (g * 0x01DC) - (b * 0x0030)) + 0x0200) >> 10) + 0x80;

    return ((UInt16)(((V << 8) & 0xFF00) | (U & 0xFF)));
}

/**
 *******************************************************************************
 *
 * \brief   Semantic Segmentation
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void chains_semSeg_SetAppPrms(chains_semSegObj *pUcObj, Void *appObj)
{
    chains_semSegAppObj *pObj = (chains_semSegAppObj*)appObj;
    UInt32 frequency =  0;
    UInt32 semSegFps = 8;

    ChainsCommon_GetDisplayWidthHeight(
                                pObj->chainsCfg->displayType,
                                &pObj->displayWidth,
                                &pObj->displayHeight);

    frequency = Utils_getClkHz(UTILS_CLK_ID_EVE) / 1000000U;
    /*
     * Set the framerate according to the frequency
     */
    if (frequency >= OPP_HIGH_FREQUENCY)
    {
        semSegFps = SEMSEG_FPS_OPPHIGH;
    }
    else
    {
        semSegFps = SEMSEG_FPS_OPPNOM;
    }

    ChainsCommon_SetFileRxPrms(
                        &pUcObj->NullSourcePrm,
                        &pUcObj->DecodePrm,
                        DEC_OUT_WIDTH,
                        DEC_OUT_HEIGHT,
                        1,                  /* numCh */
                        semSegFps);        /* fps */

    /* SetFileRxPrm sets the file open to inHeader and inData overriding the same*/
    strncpy(pUcObj->NullSourcePrm.channelParams[0].nameDataFile, "inData_semSeg", 260);
    strncpy(pUcObj->NullSourcePrm.channelParams[0].nameIndexFile, "inHeader_semSeg", 260);

    /* YUV420SP to planar RGB conversion */
    pUcObj->Alg_tidlpreprocPrm.outPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpreprocPrm.numOutputQueues = NUM_PIPELINES;
    pUcObj->Alg_tidlpreprocPrm.procMode = TIDLPREPROC_LINK_PROCMODE_Y2R;

    /* TIDL on EVE1 */
    pUcObj->Alg_tidl_Eve1Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_Eve1Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_Eve1Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_Eve1Prm.curCoreId = TIDL_COREID_EVE1;
    pUcObj->Alg_tidl_Eve1Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE1;
    pUcObj->Alg_tidl_Eve1Prm.ocmcAddr = OCMC_3_BASE_ADDRESS;

    /* TIDL on EVE2 */
    pUcObj->Alg_tidl_Eve2Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_Eve2Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_Eve2Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_Eve2Prm.curCoreId = TIDL_COREID_EVE2;
    pUcObj->Alg_tidl_Eve2Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE2;
    pUcObj->Alg_tidl_Eve2Prm.ocmcAddr = OCMC_3_BASE_ADDRESS + (OCMC_3_SIZE/2);

    /* TIDL on EVE3 */
    pUcObj->Alg_tidl_Eve3Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_Eve3Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_Eve3Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_Eve3Prm.curCoreId = TIDL_COREID_EVE3;
    pUcObj->Alg_tidl_Eve3Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE3;
    pUcObj->Alg_tidl_Eve3Prm.ocmcAddr = OCMC_1_BASE_ADDRESS;

    /* TIDL on EVE4 */
    pUcObj->Alg_tidl_Eve4Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_Eve4Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_Eve4Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_Eve4Prm.curCoreId = TIDL_COREID_EVE4;
    pUcObj->Alg_tidl_Eve4Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE4;
    pUcObj->Alg_tidl_Eve4Prm.ocmcAddr = OCMC_2_BASE_ADDRESS;

    /*  bitmap color table look up
        There are 5 palettes */
    pObj->colPalette[0] = \
            rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
    pObj->colPalette[1] = \
            rgb2uv(PALETTE_ROAD_RED, PALETTE_ROAD_GREEN, PALETTE_ROAD_BLUE);
    pObj->colPalette[2] = \
            rgb2uv(PALETTE_PED_RED, PALETTE_PED_GREEN, PALETTE_PED_BLUE);
    pObj->colPalette[3] = \
            rgb2uv(PALETTE_SIGN_RED, PALETTE_SIGN_GREEN, PALETTE_SIGN_BLUE);
    pObj->colPalette[4] = \
            rgb2uv(PALETTE_VEH_RED, PALETTE_VEH_GREEN, PALETTE_VEH_BLUE);

    pUcObj->Alg_tidlpostprocPrm.outDataFormat = SYSTEM_DF_YUV420SP_UV;
    pUcObj->Alg_tidlpostprocPrm.outWidth = SEMSEG_INPUT_WIDTH;
    pUcObj->Alg_tidlpostprocPrm.outHeight = SEMSEG_INPUT_HEIGHT;
    pUcObj->Alg_tidlpostprocPrm.colPalette565 = pObj->colPalette;
    pUcObj->Alg_tidlpostprocPrm.inPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpostprocPrm.numInputQueues = NUM_PIPELINES;
    pUcObj->Alg_tidlpostprocPrm.mode = TIDLPOSTPROC_MODE_CLUT;

    /* Sync parameters */
    pUcObj->SyncPrm.syncDelta = SYNC_DELTA;
    pUcObj->SyncPrm.syncThreshold = SYNC_THRESHOLD;

    /* Y and UV copy */
    pUcObj->Alg_tidlpostproc_cpyPrm.outDataFormat = SYSTEM_DF_YUV420SP_UV;
    pUcObj->Alg_tidlpostproc_cpyPrm.outWidth = SEMSEG_INPUT_WIDTH;
    pUcObj->Alg_tidlpostproc_cpyPrm.outHeight = SEMSEG_INPUT_HEIGHT;
    pUcObj->Alg_tidlpostproc_cpyPrm.numInputQueues = 1;
    pUcObj->Alg_tidlpostproc_cpyPrm.mode = TIDLPOSTPROC_MODE_COPY;

    ChainsCommon_SetDisplayPrms(
                                &pUcObj->DisplayPrm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = SEMSEG_DISPLAY_WIDTH;
    pUcObj->DisplayPrm.rtParams.tarHeight = SEMSEG_DISPLAY_HEIGHT;
    pUcObj->DisplayPrm.rtParams.posX = SEMSEG_DISPLAY_STARTX;
    pUcObj->DisplayPrm.rtParams.posY = SEMSEG_DISPLAY_STARTY;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight);

    /* Graphics source parameters */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = GRAPHICS_WIDTH;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = GRAPHICS_HEIGHT;
    pUcObj->GrpxSrcPrm.semSegOverlay = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = SEMSEG_INPUT_WIDTH;
    pUcObj->GrpxSrcPrm.captureHeight = SEMSEG_INPUT_HEIGHT;

    /* Graphics Display parameters */
    /* Graphics display will be at the end of the video display window */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = GRAPHICS_WIDTH;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = GRAPHICS_HEIGHT;
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = \
            (pUcObj->DisplayPrm.rtParams.posY + SEMSEG_DISPLAY_HEIGHT);
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}

static Void pauseSemSeg(chains_semSegAppObj *pObj)
{
    Int32 status;

    status = System_linkControl(
                    pObj->ucObj.NullSourceLinkID,
                    NULL_SRC_LINK_CMD_PAUSE,
                    NULL,
                    0,
                    TRUE);
    UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);
}

static Void resumeSemSeg(chains_semSegAppObj *pObj)
{
    Int32 status;

    status = System_linkControl(
                    pObj->ucObj.NullSourceLinkID,
                    NULL_SRC_LINK_CMD_RESUME,
                    NULL,
                    0,
                    TRUE);
    UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);
}

static Void enablePalette(chains_semSegAppObj *pObj, UInt32 option)
{
    switch(option)
    {
        case 0: /* ALL */
            pObj->colPalette[0] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[1] = \
                rgb2uv(PALETTE_ROAD_RED, PALETTE_ROAD_GREEN, PALETTE_ROAD_BLUE);
            pObj->colPalette[2] = \
                rgb2uv(PALETTE_PED_RED, PALETTE_PED_GREEN, PALETTE_PED_BLUE);
            pObj->colPalette[3] = \
                rgb2uv(PALETTE_SIGN_RED, PALETTE_SIGN_GREEN, PALETTE_SIGN_BLUE);
            pObj->colPalette[4] = \
                rgb2uv(PALETTE_VEH_RED, PALETTE_VEH_GREEN, PALETTE_VEH_BLUE);
            break;
        case 1: /* ROAD */
            pObj->colPalette[0] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[1] = \
                rgb2uv(PALETTE_ROAD_RED, PALETTE_ROAD_GREEN, PALETTE_ROAD_BLUE);
            pObj->colPalette[2] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[3] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[4] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            break;
        case 2: /* PEDESTRIAN */
            pObj->colPalette[0] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[1] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[2] = \
                rgb2uv(PALETTE_PED_RED, PALETTE_PED_GREEN, PALETTE_PED_BLUE);
            pObj->colPalette[3] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[4] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            break;
        case 3: /* ROAD SIGN */
            pObj->colPalette[0] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[1] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[2] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[3] = \
                rgb2uv(PALETTE_SIGN_RED, PALETTE_SIGN_GREEN, PALETTE_SIGN_BLUE);
            pObj->colPalette[4] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            break;
        case 4: /* VEHICLE */
            pObj->colPalette[0] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[1] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[2] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[3] = \
                rgb2uv(PALETTE_NONE_RED, PALETTE_NONE_GREEN, PALETTE_NONE_BLUE);
            pObj->colPalette[4] = \
                rgb2uv(PALETTE_VEH_RED, PALETTE_VEH_GREEN, PALETTE_VEH_BLUE);
            break;
    }

    Cache_wb(
        (UInt8*)pObj->colPalette,
        (MAX_NUM_PALETTE * 2),
        Cache_Type_ALLD,
        TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   Semantic Segmentation
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void Chains_semSeg(Chains_Ctrl *chainsCfg)
{
    char ch;
    Bool done = FALSE;

    gChainsObjSemSeg.chainsCfg = chainsCfg;

    /* Allocate the Algorithm create structure */
    gChainsObjSemSeg.pAlgCreateParams = ChainsCommon_Osal_memAlloc(
                                        sizeof(TIDL_CreateParams),
                                        32);
    UTILS_assert(NULL != gChainsObjSemSeg.pAlgCreateParams);

    /* Semantic Segmentation Init */
    semSegInit(&gChainsObjSemSeg);

    chains_semSeg_Create(&gChainsObjSemSeg.ucObj, &gChainsObjSemSeg);

    chains_semSeg_StartApp(&gChainsObjSemSeg);

    do
    {
        Vps_printf(semSegRunTimeMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':
                pauseSemSeg(&gChainsObjSemSeg);
                break;

            case '2':
                resumeSemSeg(&gChainsObjSemSeg);
                break;

            case '3':
                enablePalette(&gChainsObjSemSeg, 0);
                break;

            case '4':
                enablePalette(&gChainsObjSemSeg, 1);
                break;

            case '5':
                enablePalette(&gChainsObjSemSeg, 2);
                break;

            case '6':
                enablePalette(&gChainsObjSemSeg, 3);
                break;

            case '7':
                enablePalette(&gChainsObjSemSeg, 4);
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_semSeg_printStatistics(&gChainsObjSemSeg.ucObj);
                break;

            default:
                break;
        }
    }while(FALSE == done);

    chains_semSeg_StopAndDelete(&gChainsObjSemSeg);

    /* Semantic Segmentation DeInit */
    semSegDeInit(&gChainsObjSemSeg);

    /* Free the Algorithm create structure */
    ChainsCommon_Osal_memFree(
                gChainsObjSemSeg.pAlgCreateParams,
                sizeof(TIDL_CreateParams));
}
