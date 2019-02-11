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
#include "chains_tidlOD_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_tidl.h>
#include <src/include/chains_common_osal.h>
#include "itidl_ti.h"
#include "iop_ti.h"
#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */

#define TIDL_NUM_ARGS               (8)
#define TIDL_SSD_UC_CFG_FILE            "TIDL_SSD_CFG.TXT"

/* Num of TIDL processing pipelines */
#define NUM_PIPELINES               (4)

/* Semantic Segmenation input fps */
/* This should be based on the TIDL performance on 4 EVEs */
/* It should be less than the cumulative TIDL performance on 4 EVEs */
/* For eg if each TIDL is giving performace of 3 fps then it should be less than (4 x 3)*/
#define TIDL_OD_FPS_OPPHIGH          (NUM_PIPELINES * 6)

#define TIDL_OD_FPS_OPPNOM           (NUM_PIPELINES * 5)

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

/* DSP */
#define TIDL_COREID_DSP1            (1)
#define TIDL_LAYER_GROUPID_DSP1     (2)
#define TIDL_COREID_DSP2            (1)
#define TIDL_LAYER_GROUPID_DSP2     (2)

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
#define GRAPHICS_HEIGHT             (1080 - 64)

/*******************************************************************************
 *  STRUCTURES
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  chains_tidlODAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    chains_tidlODObj ucObj;
    UInt32 displayWidth;
    UInt32 displayHeight;
    Chains_Ctrl *chainsCfg;
    TIDL_CreateParams *pAlgCreateParams;
    TIOP_CreateParams *pTiopAlgCreateParams;
    UInt32 inWidth;
    UInt32 inHeight;
    char inFileName[64U];
    char inFileHDRName[64U];
    char netFileName[64U];
    char paramFileName[64U];
    UInt32 inputFps;
    float threshold;
} chains_tidlODAppObj;

chains_tidlODAppObj gChainsObjtidlOD;

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
static char tidlODRunTimeMenu[] = {
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
"\n p: Print Statistics"
"\n "
"\n Enter Choice: "
"\n "
};

static Void chains_tidlOD_SetVPEPrms(
                    VpeLink_CreateParams *pPrm,
                    UInt32 numCh,
                    UInt32 displayWidth,
                    UInt32 displayHeight,
                    UInt32 inputWidth,
                    UInt32 inputHeight
                    )
{
    UInt16 chId;

    pPrm->enableOut[0] = TRUE;

    for(chId = 0; chId < numCh; chId++)
    {
        pPrm->chParams[chId].outParams[0].numBufsPerCh = 6;

        pPrm->chParams[chId].outParams[0].width = displayWidth;
        pPrm->chParams[chId].outParams[0].height = displayHeight;
        pPrm->chParams[chId].outParams[0].dataFormat = SYSTEM_DF_YUV420SP_UV;

        pPrm->chParams[chId].scCfg.bypass       = FALSE;
        pPrm->chParams[chId].scCfg.nonLinear    = FALSE;
        pPrm->chParams[chId].scCfg.stripSize    = 0;

        pPrm->chParams[chId].scCropCfg.cropStartX = 32;
        pPrm->chParams[chId].scCropCfg.cropStartY = 24;
        pPrm->chParams[chId].scCropCfg.cropWidth = inputWidth-32;
        pPrm->chParams[chId].scCropCfg.cropHeight = inputHeight-24;
    }
}

static Void tidlODInit(chains_tidlODAppObj *pObj)
{
    /* Read the network file */
    Chains_tidlReadNet(&pObj->pAlgCreateParams->net, pObj->netFileName);

    /* Allocate memory for the net */
    Chains_tidlAllocNetParamsMem(&pObj->pAlgCreateParams->net);

    /* Fill the new parameters */
    Chains_tidlFillNetParamsMem(&pObj->pAlgCreateParams->net, pObj->paramFileName);

    /* Init all the 3 instances of the OCMC */
    Utils_cbufOcmcInit(UTILS_OCMC_RAM1);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM2);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM3);
}


static Void tidlODDeInit(chains_tidlODAppObj *pObj)
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
 * \param   pObj  [IN] chains_tidlODAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_tidlOD_StartApp(chains_tidlODAppObj *pObj)
{
    Chains_memPrintHeapStatus();
    ChainsCommon_StartDisplayDevice(pObj->chainsCfg->displayType);
    chains_tidlOD_Start(&pObj->ucObj);
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
 * \param   pObj   [IN]   chains_tidlODAppObj
 *
 *******************************************************************************
*/
Void chains_tidlOD_StopAndDelete(chains_tidlODAppObj *pObj)
{
    chains_tidlOD_Stop(&pObj->ucObj);
    chains_tidlOD_Delete(&pObj->ucObj);

    ChainsCommon_StopDisplayCtrl();
    ChainsCommon_StopDisplayDevice(pObj->chainsCfg->displayType);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}


static Void ChainsCommon_tidlODSetObjectDrawPrms(
            AlgorithmLink_ObjectDrawCreateParams *pOdDrawPrm,
            chains_tidlODAppObj *pObj)
{

    pOdDrawPrm->imgFrameStartX   = 0;
    pOdDrawPrm->imgFrameStartY   = 0;
    pOdDrawPrm->imgFrameWidth   = pObj->inWidth;
    pOdDrawPrm->imgFrameHeight  = pObj->inHeight;
    pOdDrawPrm->numOutBuffers    = 3;
    pOdDrawPrm->objectRectThickness = 1;
    pOdDrawPrm->objectTsrDrawTrafficSigns = FALSE;
    pOdDrawPrm->laneThickness = 2;
    pOdDrawPrm->laneDrawLines = FALSE;
    pOdDrawPrm->laneScaleX = 2.0;
    pOdDrawPrm->laneScaleY = 2.0;
    pOdDrawPrm->drawOption = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALL;
    pOdDrawPrm->numDrawAlg = 0;
    pOdDrawPrm->scoreThreshold = pObj->threshold;
    pOdDrawPrm->drawAlgId[pOdDrawPrm->numDrawAlg]
            = ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_TIDL_OD;
    pOdDrawPrm->numDrawAlg++;
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
Void chains_tidlOD_SetAppPrms(chains_tidlODObj *pUcObj, Void *appObj)
{
    UInt32 FileReadFps = TIDL_OD_FPS_OPPNOM;

    chains_tidlODAppObj *pObj = (chains_tidlODAppObj*)appObj;

    /*
     * Set the framerate according to the frequency
     */
    FileReadFps = pObj->inputFps;

    ChainsCommon_GetDisplayWidthHeight(
                                pObj->chainsCfg->displayType,
                                &pObj->displayWidth,
                                &pObj->displayHeight);

    ChainsCommon_SetFileRxPrms(
                        &pUcObj->NullSourcePrm,
                        &pUcObj->DecodePrm,
                        pObj->inWidth,
                        pObj->inHeight,
                        1,                  /* numCh */
                        FileReadFps);        /* fps */

    /* SetFileRxPrm sets the file open to inHeader and inData overriding the same*/
    strncpy(pUcObj->NullSourcePrm.channelParams[0].nameDataFile, pObj->inFileName, sizeof(pObj->inFileName));
    strncpy(pUcObj->NullSourcePrm.channelParams[0].nameIndexFile, pObj->inFileHDRName, 260);

    chains_tidlOD_SetVPEPrms(
                    &pUcObj->VPEPrm,
                    1,
                    pObj->inWidth,
                    pObj->inHeight,
                    pObj->inWidth,
                    pObj->inHeight
                    );

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

    /* TIDL on DSP */
    pUcObj->Alg_tidl_DspPrm.cacheInvInBuf = 1;
    pUcObj->Alg_tidl_DspPrm.cacheWbOutBuf = 1;
    pUcObj->Alg_tidl_DspPrm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_DspPrm.curCoreId = TIDL_COREID_DSP1;
    pUcObj->Alg_tidl_DspPrm.currLayersGroupId = TIDL_LAYER_GROUPID_DSP1;

    /* TIOP params */
    pObj->pTiopAlgCreateParams->inMaxWidth  = pObj->inWidth;
    pObj->pTiopAlgCreateParams->inMaxHeight = pObj->inHeight;
    pUcObj->Alg_tiopPrm.pAlgCreateParams = pObj->pTiopAlgCreateParams;
    pUcObj->Alg_tiopPrm.cacheInvInBuf = TRUE;
    pUcObj->Alg_tiopPrm.cacheWbOutBuf = TRUE;

    /* Sync parameters */
    pUcObj->SyncPrm.syncDelta = SYNC_DELTA;
    pUcObj->SyncPrm.syncThreshold = SYNC_THRESHOLD;

    ChainsCommon_tidlODSetObjectDrawPrms(&pUcObj->Alg_ObjectDrawPrm,pObj);
    ChainsCommon_SetDisplayPrms(
                                &pUcObj->DisplayPrm,
                                NULL,
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight);

    pUcObj->DisplayPrm.rtParams.tarWidth = pObj->inWidth*2;
    pUcObj->DisplayPrm.rtParams.tarHeight = pObj->inHeight*2;
    pUcObj->DisplayPrm.rtParams.posX = ((1920 - (pObj->inWidth*2))/2);
    pUcObj->DisplayPrm.rtParams.posY = 64;
    pUcObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                                pObj->chainsCfg->displayType,
                                pObj->displayWidth,
                                pObj->displayHeight);

    /* Graphics source parameters */
    pUcObj->GrpxSrcPrm.grpxBufInfo.dataFormat = SYSTEM_DF_BGR16_565;
    pUcObj->GrpxSrcPrm.grpxBufInfo.width = GRAPHICS_WIDTH;
    pUcObj->GrpxSrcPrm.grpxBufInfo.height = (GRAPHICS_HEIGHT - (pObj->inHeight*2));
    pUcObj->GrpxSrcPrm.tidlOdOverlay = TRUE;
    pUcObj->GrpxSrcPrm.captureWidth = pObj->inWidth;
    pUcObj->GrpxSrcPrm.captureHeight = pObj->inHeight;

    /* Graphics Display parameters */
    /* Graphics display will be at the end of the video display window */
    pUcObj->Display_GrpxPrm.rtParams.tarWidth = GRAPHICS_WIDTH;
    pUcObj->Display_GrpxPrm.rtParams.tarHeight = (GRAPHICS_HEIGHT - (pObj->inHeight*2));
    pUcObj->Display_GrpxPrm.rtParams.posX = 0;
    pUcObj->Display_GrpxPrm.rtParams.posY = \
            (pUcObj->DisplayPrm.rtParams.posY + (pObj->inHeight*2));
    pUcObj->Display_GrpxPrm.displayId = DISPLAY_LINK_INST_DSS_GFX1;
}

static Void pausetidlOD(chains_tidlODAppObj *pObj)
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

static Void resumetidlOD(chains_tidlODAppObj *pObj)
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

/**
 *******************************************************************************
 *
 * \brief   Parse the TIDL config file
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
static Int32 parseInputCfg(chains_tidlODAppObj *pObj)
{
    Int32 fd;
    char string[256U];
    char *pArg, *pVal;
    UInt32 numArg = 0;

    fd = ChainsCommon_Osal_fileOpen(
                    TIDL_SSD_UC_CFG_FILE,
                    CHAINSCOMMON_OSAL_FILEMODE_READ);
    if(-1 != fd)
    {
        while(NULL != File_gets(string, 256U, fd))
        {
            pArg = strtok(string, "=");
            pVal = strtok(NULL, "\0");
            if(NULL != pArg)
            {
                if(0 == strcmp(pArg,"inputWidth"))
                {
                    pObj->inWidth = atoi(pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"inputHeight"))
                {
                    pObj->inHeight = atoi(pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"inputFile"))
                {
                    strcpy(pObj->inFileName,pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"inputHDRFile"))
                {
                    strcpy(pObj->inFileHDRName,pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"netFileName"))
                {
                    strcpy(pObj->netFileName,pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"paramFileName"))
                {
                    strcpy(pObj->paramFileName,pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"fps"))
                {
                    pObj->inputFps = atoi(pVal);
                    numArg ++;
                }
                else if(0 == strcmp(pArg,"threshold"))
                {
                    pObj->threshold = atof(pVal);
                    numArg ++;
                }
            }
        }

        ChainsCommon_Osal_fileClose(fd);

        if(TIDL_NUM_ARGS != numArg)
        {
            Vps_printf(" TIDL: Insufficient no of configuration parameters ...");
            return SYSTEM_LINK_STATUS_EFAIL;
        }
        else
        {
            Vps_printf(" TIDL Configuration parameters");
            Vps_printf(" -----------------------------");
            Vps_printf(" inputWidth         = %d\n",pObj->inWidth);
            Vps_printf(" inputHeight        = %d\n",pObj->inHeight);
            Vps_printf(" inputFile          = %s\n",pObj->inFileName);
            Vps_printf(" inputFile          = %s\n",pObj->inFileHDRName);
            Vps_printf(" netFileName        = %s\n",pObj->netFileName);
            Vps_printf(" paramFileName      = %s\n",pObj->paramFileName);
            Vps_printf(" inputfps           = %d\n",pObj->inputFps);
            Vps_printf(" threshold          = %f\n",pObj->threshold);
            Vps_printf(" -----------------------------");

            return SYSTEM_LINK_STATUS_SOK;
        }
    }
    else
    {
        Vps_printf(" Use case config file (%s) is NOT present ...",\
                                                        TIDL_SSD_UC_CFG_FILE);
        return SYSTEM_LINK_STATUS_EFAIL;
    }
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
Void Chains_tidlOD(Chains_Ctrl *chainsCfg)
{
    char ch;
    Bool done = FALSE;

    parseInputCfg(&gChainsObjtidlOD);
    gChainsObjtidlOD.chainsCfg = chainsCfg;

    /* Allocate the Algorithm create structure */
    gChainsObjtidlOD.pAlgCreateParams = ChainsCommon_Osal_memAlloc(
                                        sizeof(TIDL_CreateParams),
                                        32);
    UTILS_assert(NULL != gChainsObjtidlOD.pAlgCreateParams);

    gChainsObjtidlOD.pTiopAlgCreateParams = ChainsCommon_Osal_memAlloc(
                                        sizeof(TIOP_CreateParams),
                                        32);
    UTILS_assert(NULL != gChainsObjtidlOD.pTiopAlgCreateParams);

    /* Semantic Segmentation Init */
    tidlODInit(&gChainsObjtidlOD);

    chains_tidlOD_Create(&gChainsObjtidlOD.ucObj, &gChainsObjtidlOD);

    chains_tidlOD_StartApp(&gChainsObjtidlOD);

    do
    {
        Vps_printf(tidlODRunTimeMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;

            case '1':
                pausetidlOD(&gChainsObjtidlOD);
                break;

            case '2':
                resumetidlOD(&gChainsObjtidlOD);
                break;

            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_tidlOD_printStatistics(&gChainsObjtidlOD.ucObj);
                break;

            default:
                break;
        }
    }while(FALSE == done);

    chains_tidlOD_StopAndDelete(&gChainsObjtidlOD);

    /* Semantic Segmentation DeInit */
    tidlODDeInit(&gChainsObjtidlOD);

    /* Free the Algorithm create structure */
    ChainsCommon_Osal_memFree(
                gChainsObjtidlOD.pAlgCreateParams,
                sizeof(TIDL_CreateParams));

    ChainsCommon_Osal_memFree(
                gChainsObjtidlOD.pTiopAlgCreateParams,
                sizeof(TIOP_CreateParams));
}
