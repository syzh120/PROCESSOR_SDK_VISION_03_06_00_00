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
#include <src/include/chains_common.h>
#include <src/include/chains_common_tidl.h>
#include <src/include/chains_common_osal.h>
#include "itidl_ti.h"
#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>
#include <src/rtos/utils_common/include/utils_tsk.h>
#include "UsecaseDsp/chains_tidlDsp_priv.h"
#include "UsecaseEve/chains_tidlEve_priv.h"
#include "UsecaseDspTda3x/chains_tidlDspTda3x_priv.h"
#include "UsecaseEveTda3x/chains_tidlEveTda3x_priv.h"
#include "chains_tidl.h"

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */

#define TIDL_FILEWRITE_TASK_STACK_SIZE      (32 * KB)

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */

chains_tidlAppObj gChainsObjTidl;

#pragma DATA_ALIGN(fileWriteTaskStack, 32)
#pragma DATA_SECTION(fileWriteTaskStack, ".bss:taskStackSection")
static UInt8 fileWriteTaskStack[TIDL_FILEWRITE_TASK_STACK_SIZE];

static char tidlCoreMenu[] = {
"\n "
"\n ===================="
"\n Core Menu"
"\n ===================="
"\n "
"\n 1: DSP"
"\n 2: EVE"
"\n "
"\n Enter Choice: "
"\n "
};

static char tidlUseCaseModeMenu[] = {
"\n "
"\n ===================="
"\n Use case Mode"
"\n ===================="
"\n "
"\n 1: Dump Output Frames to file"
"\n 2: Free Run (Output Frames are not dumped)"
"\n "
"\n Enter Choice: "
"\n "
};

static char tidlRunTimeMenu[] = {
"\n "
"\n ===================="
"\n Chains Run-time Menu"
"\n ===================="
"\n "
"\n 0: Stop Chain"
"\n "
"\n p: Print Statistics"
"\n "
"\n Enter Choice: "
"\n "
};

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief   TIDL Init
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
static Void tidlInit(chains_tidlAppObj *pObj)
{
    /* Read the network file */
    Chains_tidlReadNet(&pObj->pAlgCreateParams->net, pObj->netFileName);

    /* Allocate memory for the net */
    Chains_tidlAllocNetParamsMem(&pObj->pAlgCreateParams->net);

    /* Fill the new parameters */
    Chains_tidlFillNetParamsMem(&pObj->pAlgCreateParams->net, pObj->paramFileName);

    /* Init all the 3 instances of the OCMC */
    Utils_cbufOcmcInit(UTILS_OCMC_RAM1);
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
    Utils_cbufOcmcInit(UTILS_OCMC_RAM2);
    Utils_cbufOcmcInit(UTILS_OCMC_RAM3);
#endif
}


/**
 *******************************************************************************
 *
 * \brief   Deinit TIDL
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
static Void tidlDeInit(chains_tidlAppObj *pObj)
{
    /* Free the net memories */
    Chains_tidlFreeNetParamsMem(&pObj->pAlgCreateParams->net);
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
static Int32 parseCfg(chains_tidlAppObj *pObj)
{
    Int32 fd;
    char string[256U];
    char *pArg, *pVal;
    UInt32 numArg = 0;

    fd = ChainsCommon_Osal_fileOpen(
                    TIDL_UC_CFG_FILE,
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
                else if(0 == strcmp(pArg,"outputFile"))
                {
                    strcpy(pObj->outFileName,pVal);
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
            Vps_printf(" outputFile         = %s\n",pObj->outFileName);
            Vps_printf(" netFileName        = %s\n",pObj->netFileName);
            Vps_printf(" paramFileName      = %s\n",pObj->paramFileName);
            Vps_printf(" -----------------------------");

            return SYSTEM_LINK_STATUS_SOK;
        }
    }
    else
    {
        Vps_printf(" Use case config file (%s) is NOT present ...",\
                                                        TIDL_UC_CFG_FILE);
        return SYSTEM_LINK_STATUS_EFAIL;
    }
}

/**
 *******************************************************************************
 *
 * \brief   chains_tidl_CreateApp
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_tidlAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_tidl_CreateApp(chains_tidlAppObj *pObj)
{
    switch(pObj->tidlCore)
    {
        case TIDL_CORE_DSP:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlDsp_Create(&pObj->dspUcObj, pObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlDspTda3x_Create(&pObj->dspUcTda3xObj, pObj);
#endif
            break;

        default:
        case TIDL_CORE_EVE:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlEve_Create(&pObj->eveUcObj, pObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlEveTda3x_Create(&pObj->eveUcTda3xObj, pObj);
#endif
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   chains_tidl_StartApp
 *
 *          Function sends a control command to capture and display link to
 *          to Start all the required links . Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] chains_tidlAppObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_tidl_StartApp(chains_tidlAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    switch(pObj->tidlCore)
    {
        case TIDL_CORE_DSP:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlDsp_Start(&pObj->dspUcObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlDspTda3x_Start(&pObj->dspUcTda3xObj);
#endif
            break;

        default:
        case TIDL_CORE_EVE:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlEve_Start(&pObj->eveUcObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlEveTda3x_Start(&pObj->eveUcTda3xObj);
#endif
            break;
    }

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   chains_tidl_StopAndDelete
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
Void chains_tidl_StopAndDelete(chains_tidlAppObj *pObj)
{
    switch(pObj->tidlCore)
    {
        case TIDL_CORE_DSP:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlDsp_Stop(&pObj->dspUcObj);
            chains_tidlDsp_Delete(&pObj->dspUcObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlDspTda3x_Stop(&pObj->dspUcTda3xObj);
            chains_tidlDspTda3x_Delete(&pObj->dspUcTda3xObj);
#endif
            break;

        default:
        case TIDL_CORE_EVE:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlEve_Stop(&pObj->eveUcObj);
            chains_tidlEve_Delete(&pObj->eveUcObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlEveTda3x_Stop(&pObj->eveUcTda3xObj);
            chains_tidlEveTda3x_Delete(&pObj->eveUcTda3xObj);
#endif
            break;
    }

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
}

/**
 *******************************************************************************
 *
 * \brief   chains_tidl_printStatisticsApp
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
Void chains_tidl_printStatisticsApp(chains_tidlAppObj *pObj)
{
    switch(pObj->tidlCore)
    {
        case TIDL_CORE_DSP:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlDsp_printStatistics(&pObj->dspUcObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlDspTda3x_printStatistics(&pObj->dspUcTda3xObj);
#endif
            break;

        default:
        case TIDL_CORE_EVE:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            chains_tidlEve_printStatistics(&pObj->eveUcObj);
#endif
#ifdef TDA3XX_BUILD
            chains_tidlEveTda3x_printStatistics(&pObj->eveUcTda3xObj);
#endif
            break;
    }
}

/**
 *******************************************************************************
 *
 * \brief   inputEofCb
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
static Void inputEofCb(UInt32 numFrames)
{
    /* End of input file reached */
    Vps_printf(" No of input frames = %d\n",numFrames);
    gChainsObjTidl.outNumFrames = numFrames;
    BspOsal_semPost(gChainsObjTidl.eofSem);
}

/**
 *******************************************************************************
 *
 * \brief   setNullSrcPrm
 *
 *          Function sends a control command to capture and display link to
 *          to delete all the prior created links
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   chains_tidlAppObj
 *
 *******************************************************************************
*/
static Void setNullSrcPrm(chains_tidlAppObj *pObj)
{
    System_LinkChInfo *pChInfo;
    NullSrcLink_CreateParams *pNullSrcPrm;

    switch(pObj->tidlCore)
    {
        case TIDL_CORE_DSP:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            pNullSrcPrm = &pObj->dspUcObj.NullSourcePrm;
#endif
#ifdef TDA3XX_BUILD
            pNullSrcPrm = &pObj->dspUcTda3xObj.NullSourcePrm;
#endif
            break;

        default:
        case TIDL_CORE_EVE:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
            pNullSrcPrm = &pObj->eveUcObj.NullSourcePrm;
#endif
#ifdef TDA3XX_BUILD
            pNullSrcPrm = &pObj->eveUcTda3xObj.NullSourcePrm;
#endif
            break;
    }

    NullSrcLink_CreateParams_Init(pNullSrcPrm);

    if(TRUE == pObj->enableOutFileWrite)
    {
        /*  For the file write mode the Null source latency is high
            to allow for file write delays */
        pNullSrcPrm->timerPeriodMilliSecs = NULLSRC_TIMER_PERIOD_FW;
    }
    else
    {
        pNullSrcPrm->timerPeriodMilliSecs = NULLSRC_TIMER_PERIOD;
    }
    pNullSrcPrm->outQueInfo.numCh = 1;
    pNullSrcPrm->channelParams[0].numBuffers = 4;

    pChInfo = &pNullSrcPrm->outQueInfo.chInfo[0];

    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                            SYSTEM_DF_BGR24_888);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                            SYSTEM_SF_PROGRESSIVE);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                            SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
    pChInfo->width = pObj->inWidth;
    pChInfo->height = pObj->inHeight;
    pChInfo->startX = 0;
    pChInfo->startY = 0;
    pChInfo->pitch[0] = SystemUtils_align(pChInfo->width * 3, 32);
    pChInfo->pitch[1] = SystemUtils_align(pChInfo->width * 3, 32);

    pNullSrcPrm->channelParams[0].fileReadMode = NULLSRC_LINK_FILEREAD_RUN_TIME;
    strncpy(pNullSrcPrm->channelParams[0].nameDataFile, pObj->inFileName, 260);

    if(TRUE == pObj->enableOutFileWrite)
    {
        pNullSrcPrm->inEofCb = inputEofCb;
    }
    else
    {
        pNullSrcPrm->inEofCb = NULL;
    }
}


static Void dumpOutCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg)
{
    Int32 status;
    UInt32 inBufOffset;
    System_Buffer *pFrameBuf = (System_Buffer*)pBuf;
    System_MetaDataBuffer *pMetaDataBuf = \
                                (System_MetaDataBuffer*)pFrameBuf->payload;
    chains_tidlAppObj *pObj = (chains_tidlAppObj*)arg;
    Utils_DmaCopyFill2D dmaPrm;

    pObj->curOutputBufAddr = pObj->outputBuf[pObj->curOutBuf];
    pObj->curOutBuf = (pObj->curOutBuf == 0)?1:0;
    pObj->curQue = pFrameBuf->chNum;

    Cache_inv(
        pMetaDataBuf->bufAddr[0],
        ((pObj->inWidth + (2 * TIDL_MAX_PAD_SIZE)) * \
                                (pObj->inHeight + (2 * TIDL_MAX_PAD_SIZE))),
        Cache_Type_ALL,
        TRUE);

    /* Remove the padding */
    dmaPrm.srcPitch[0] = (pObj->inWidth + (2 * TIDL_MAX_PAD_SIZE));
    inBufOffset = \
                ((dmaPrm.srcPitch[0] * TIDL_MAX_PAD_SIZE) + TIDL_MAX_PAD_SIZE);
    dmaPrm.dataFormat = SYSTEM_DF_RAW08;
    dmaPrm.destAddr[0] = (Ptr)(pObj->curOutputBufAddr);
    dmaPrm.destAddr[1] = NULL;
    dmaPrm.destPitch[0] = pObj->inWidth;
    dmaPrm.destPitch[1] = 0;
    dmaPrm.destStartX = 0;
    dmaPrm.destStartY = 0;
    dmaPrm.width = pObj->inWidth;
    dmaPrm.height = pObj->inHeight;
    dmaPrm.srcAddr[0] = (Ptr)((UInt32)pMetaDataBuf->bufAddr[0] + inBufOffset);
    dmaPrm.srcAddr[1] = NULL;
    dmaPrm.srcPitch[1] = 0;
    dmaPrm.srcStartX = 0;
    dmaPrm.srcStartY = 0;

    status = Utils_dmaCopy2D(&pObj->dumpFramesDmaObj, &dmaPrm, 1U);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);

    Cache_wb(
        (Ptr)pObj->curOutputBufAddr,
        (pObj->inWidth * pObj->inHeight),
        Cache_Type_ALL,
        TRUE);

    /* Post file write sem */
    BspOsal_semPost(pObj->fileWriteSem);
}

/* Background low priority task for writing the output frame to file */
Void fileWriteTaskMain(UArg arg1, UArg arg2)
{
    Bool dump;
    chains_tidlAppObj *pObj = (chains_tidlAppObj*)arg1;

    while(1)
    {
        BspOsal_semWait(pObj->fileWriteSem, BSP_OSAL_WAIT_FOREVER);

        dump = TRUE;
        if(0 != pObj->outNumFrames)
        {
            if(pObj->outFrameNum == pObj->outNumFrames)
            {
                /* All the frames are dumped */
                dump = FALSE;
            }
        }

        if(TRUE == dump)
        {
            /* Write the output buffer to file */
            ChainsCommon_Osal_fileWrite(
                            pObj->outFp,
                            (UInt8*)pObj->curOutputBufAddr,
                            (pObj->inWidth * pObj->inHeight));
            Vps_printf(" ########## FRAME # %d, QUEUE = %d ###########\n",\
                                            pObj->outFrameNum++,pObj->curQue);
        }
    }
}

#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
/**
 *******************************************************************************
 *
 * \brief   chains_tidlEve_SetAppPrms
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
Void chains_tidlEve_SetAppPrms(chains_tidlEveObj *pUcObj, Void *appObj)
{
    chains_tidlAppObj *pObj = (chains_tidlAppObj*)appObj;

    /* Null Source Parameters */
    setNullSrcPrm(pObj);

    /* TIDL Pre Process */
    pUcObj->Alg_tidlpreprocPrm.outPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpreprocPrm.numOutputQueues = NUM_PIPELINES;
    pUcObj->Alg_tidlpreprocPrm.procMode = TIDLPREPROC_LINK_PROCMODE_RGBPAD;

    /*
     *  Set the TIDL algorithm parameters for all the 'NUM_PIPELINES' instances.
     *  Make sure to distribute the OCMC instance across the algorithm
     *  instances like OCMC_1 for TIDL_1 and OCMC_2 for TIDL_2
     */

    /* TIDL on EVE1 */
    pUcObj->Alg_tidl_1Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_1Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_1Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_1Prm.curCoreId = TIDL_COREID_EVE1;
    pUcObj->Alg_tidl_1Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE1;
    pUcObj->Alg_tidl_1Prm.ocmcAddr = OCMC_1_BASE_ADDRESS;

    /* Null Link */
    if(TRUE == pObj->enableOutFileWrite)
    {
        pUcObj->NullPrm.appCb = dumpOutCb;
        pUcObj->NullPrm.appCbArg = pObj;
    }
    else
    {
        pUcObj->NullPrm.appCb = NULL;
        pUcObj->NullPrm.appCbArg = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief   chains_tidlDsp_SetAppPrms
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
Void chains_tidlDsp_SetAppPrms(chains_tidlDspObj *pUcObj, Void *appObj)
{
    chains_tidlAppObj *pObj = (chains_tidlAppObj*)appObj;

    /* Null Source Parameters */
    setNullSrcPrm(pObj);

    /* TIDL Pre Process */
    pUcObj->Alg_tidlpreprocPrm.outPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpreprocPrm.numOutputQueues = NUM_PIPELINES;
    pUcObj->Alg_tidlpreprocPrm.procMode = TIDLPREPROC_LINK_PROCMODE_RGBPAD;

    /*
     *  Set the TIDL algorithm parameters for all the 'NUM_PIPELINES' instances.
     */

    /* TIDL on DSP1 */
    pUcObj->Alg_tidl_1Prm.cacheInvInBuf = 1;
    pUcObj->Alg_tidl_1Prm.cacheWbOutBuf = 1;
    pUcObj->Alg_tidl_1Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_1Prm.curCoreId = TIDL_COREID_EVE1;
    pUcObj->Alg_tidl_1Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE1;
    pUcObj->Alg_tidl_1Prm.ocmcAddr = NULL;

    /* Null Link */
    if(TRUE == pObj->enableOutFileWrite)
    {
        pUcObj->NullPrm.appCb = dumpOutCb;
        pUcObj->NullPrm.appCbArg = pObj;
    }
    else
    {
        pUcObj->NullPrm.appCb = NULL;
        pUcObj->NullPrm.appCbArg = NULL;
    }
}
#endif

#ifdef TDA3XX_BUILD
/**
 *******************************************************************************
 *
 * \brief   chains_tidlEve_SetAppPrms
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
Void chains_tidlEveTda3x_SetAppPrms(chains_tidlEveTda3xObj *pUcObj, Void *appObj)
{
    chains_tidlAppObj *pObj = (chains_tidlAppObj*)appObj;

    /* Null Source Parameters */
    setNullSrcPrm(pObj);

    /* TIDL Pre Process */
    pUcObj->Alg_tidlpreprocPrm.outPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpreprocPrm.numOutputQueues = 1U;
    pUcObj->Alg_tidlpreprocPrm.procMode = TIDLPREPROC_LINK_PROCMODE_RGBPAD;

    /*
     *  Set the TIDL algorithm parameters for all the 'NUM_PIPELINES' instances.
     *  Make sure to distribute the OCMC instance across the algorithm
     *  instances like OCMC_1 for TIDL_1 and OCMC_2 for TIDL_2
     */

    /* TIDL on EVE1 */
    pUcObj->Alg_tidl_1Prm.cacheInvInBuf = 0;
    pUcObj->Alg_tidl_1Prm.cacheWbOutBuf = 0;
    pUcObj->Alg_tidl_1Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_1Prm.curCoreId = TIDL_COREID_EVE1;
    pUcObj->Alg_tidl_1Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE1;
    pUcObj->Alg_tidl_1Prm.ocmcAddr = OCMC_1_BASE_ADDRESS;

    /* Null Link */
    if(TRUE == pObj->enableOutFileWrite)
    {
        pUcObj->NullPrm.appCb = dumpOutCb;
        pUcObj->NullPrm.appCbArg = pObj;
    }
    else
    {
        pUcObj->NullPrm.appCb = NULL;
        pUcObj->NullPrm.appCbArg = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief   chains_tidlDsp_SetAppPrms
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
Void chains_tidlDspTda3x_SetAppPrms(chains_tidlDspTda3xObj *pUcObj, Void *appObj)
{
    chains_tidlAppObj *pObj = (chains_tidlAppObj*)appObj;

    /* Null Source Parameters */
    setNullSrcPrm(pObj);

    /* TIDL Pre Process */
    pUcObj->Alg_tidlpreprocPrm.outPad = TIDL_MAX_PAD_SIZE;
    pUcObj->Alg_tidlpreprocPrm.numOutputQueues = 1U;
    pUcObj->Alg_tidlpreprocPrm.procMode = TIDLPREPROC_LINK_PROCMODE_RGBPAD;

    /*
     *  Set the TIDL algorithm parameters for all the 'NUM_PIPELINES' instances.
     */

    /* TIDL on DSP1 */
    pUcObj->Alg_tidl_1Prm.cacheInvInBuf = 1;
    pUcObj->Alg_tidl_1Prm.cacheWbOutBuf = 1;
    pUcObj->Alg_tidl_1Prm.pAlgCreateParams = pObj->pAlgCreateParams;
    pUcObj->Alg_tidl_1Prm.curCoreId = TIDL_COREID_EVE1;
    pUcObj->Alg_tidl_1Prm.currLayersGroupId = TIDL_LAYER_GROUPID_EVE1;
    pUcObj->Alg_tidl_1Prm.ocmcAddr = NULL;

    /* Null Link */
    if(TRUE == pObj->enableOutFileWrite)
    {
        pUcObj->NullPrm.appCb = dumpOutCb;
        pUcObj->NullPrm.appCbArg = pObj;
    }
    else
    {
        pUcObj->NullPrm.appCb = NULL;
        pUcObj->NullPrm.appCbArg = NULL;
    }
}
#endif

/**
 *******************************************************************************
 *
 * \brief   chanis_tidl
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
Void Chains_tidl(Chains_Ctrl *chainsCfg)
{
    char ch;
    Bool done = FALSE;
    Int32 status;
    Utils_DmaChCreateParams dmaParams;
    UInt32 nullSourceLinkID;

    /* Parse the Use Case Config file */
    if(SYSTEM_LINK_STATUS_SOK == parseCfg(&gChainsObjTidl))
    {
        gChainsObjTidl.chainsCfg = chainsCfg;

        /*  TIDL Core selection
            DSP/EVE */
        Vps_printf(tidlCoreMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                gChainsObjTidl.tidlCore = TIDL_CORE_DSP;
                break;
            default:
            case '2':
                gChainsObjTidl.tidlCore = TIDL_CORE_EVE;
                break;
        }

        /*  TIDL Use case Mode selection
            File Dump/Free Run */
        Vps_printf(tidlUseCaseModeMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            default:
            case '1':
                gChainsObjTidl.enableOutFileWrite = TRUE;
                break;
            case '2':
                gChainsObjTidl.enableOutFileWrite = FALSE;
                break;
        }

        /* Allocate the Algorithm create structure */
        gChainsObjTidl.pAlgCreateParams = ChainsCommon_Osal_memAlloc(
                                            sizeof(TIDL_CreateParams),
                                            32);
        UTILS_assert(NULL != gChainsObjTidl.pAlgCreateParams);

        if(TRUE == gChainsObjTidl.enableOutFileWrite)
        {
            /* EDMA channel for dumping the frame */
            Utils_DmaChCreateParams_Init(&dmaParams);
            status = Utils_dmaCreateCh(&gChainsObjTidl.dumpFramesDmaObj, &dmaParams);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            /* Semaphore to flag end of input */
            gChainsObjTidl.eofSem = BspOsal_semCreate(0, (Bool) TRUE);
            UTILS_assert(NULL != gChainsObjTidl.eofSem);

            /* Allocate buffer to copy the output frame after removing the padding */
            gChainsObjTidl.outputBuf[0] = (UInt32)ChainsCommon_Osal_memAlloc(
                                        (gChainsObjTidl.inWidth * gChainsObjTidl.inHeight),
                                        32);
            UTILS_assert(NULL != gChainsObjTidl.outputBuf[0]);

            gChainsObjTidl.outputBuf[1] = (UInt32)ChainsCommon_Osal_memAlloc(
                                        (gChainsObjTidl.inWidth * gChainsObjTidl.inHeight),
                                        32);
            UTILS_assert(NULL != gChainsObjTidl.outputBuf[1]);

            /* Open the output file */
            gChainsObjTidl.outFp = ChainsCommon_Osal_fileOpen(
                                        gChainsObjTidl.outFileName,
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
            UTILS_assert(-1 != gChainsObjTidl.outFp);

            /* File Writer Task */
            gChainsObjTidl.fileWriteTask = BspOsal_taskCreate(
                                            (BspOsal_TaskFuncPtr)fileWriteTaskMain,
                                           "ChainsCommon_TIDL_FileWriteTsk",
                                            TIDL_UC_FILEWRITE_TSK_PRI,
                                            fileWriteTaskStack,
                                            sizeof(fileWriteTaskStack),
                                            &gChainsObjTidl,
                                            UTILS_TSK_AFFINITY_CORE0);
            UTILS_assert(NULL != gChainsObjTidl.fileWriteTask);

            /* Semaphore for file write sync */
            gChainsObjTidl.fileWriteSem = BspOsal_semCreate(0, (Bool) TRUE);
            UTILS_assert(NULL != gChainsObjTidl.fileWriteSem);

            gChainsObjTidl.outFrameNum = 0;
            gChainsObjTidl.outNumFrames = 0;
            gChainsObjTidl.curOutBuf = 0;
        }

        /* TIDL init */
        tidlInit(&gChainsObjTidl);

        chains_tidl_CreateApp(&gChainsObjTidl);
        chains_tidl_StartApp(&gChainsObjTidl);

        if(TRUE == gChainsObjTidl.enableOutFileWrite)
        {
            /* Wait for processing of all the frames */
            BspOsal_semWait(gChainsObjTidl.eofSem, BSP_OSAL_WAIT_FOREVER);

            ChainsCommon_PrintStatistics();
            chains_tidl_printStatisticsApp(&gChainsObjTidl);

            switch(gChainsObjTidl.tidlCore)
            {
                case TIDL_CORE_DSP:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
                    nullSourceLinkID = gChainsObjTidl.dspUcObj.NullSourceLinkID;
#endif
#ifdef TDA3XX_BUILD
                    nullSourceLinkID = gChainsObjTidl.dspUcTda3xObj.NullSourceLinkID;
#endif
                    break;

                default:
                case TIDL_CORE_EVE:
#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
                    nullSourceLinkID = gChainsObjTidl.eveUcObj.NullSourceLinkID;
#endif
#ifdef TDA3XX_BUILD
                    nullSourceLinkID = gChainsObjTidl.eveUcTda3xObj.NullSourceLinkID;
#endif
                    break;
            }

            /* Pause the Null Source Link */
            status = System_linkControl(
                            nullSourceLinkID,
                            NULL_SRC_LINK_CMD_PAUSE,
                            NULL,
                            0,
                            TRUE);
            UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);

            /* Wait till all the output frames are dumped */
            while(gChainsObjTidl.outFrameNum < gChainsObjTidl.outNumFrames)
            {
                Task_sleep(500);
            }
        }
        else
        {
            do
            {
                Vps_printf(tidlRunTimeMenu);
                ch = Chains_readChar();

                switch(ch)
                {
                    case '0':
                        done = TRUE;
                        break;

                    case 'p':
                    case 'P':
                        ChainsCommon_PrintStatistics();
                        chains_tidl_printStatisticsApp(&gChainsObjTidl);
                        break;

                    default:
                        break;
                }
            }while(FALSE == done);
        }

        chains_tidl_StopAndDelete(&gChainsObjTidl);

        /* TIDL DeInit */
        tidlDeInit(&gChainsObjTidl);

        if(TRUE == gChainsObjTidl.enableOutFileWrite)
        {
            ChainsCommon_Osal_fileClose(gChainsObjTidl.outFp);

            BspOsal_taskDelete(&gChainsObjTidl.fileWriteTask);

            BspOsal_semDelete(&gChainsObjTidl.fileWriteSem);

            BspOsal_semDelete(&gChainsObjTidl.eofSem);

            Utils_dmaDeleteCh(&gChainsObjTidl.dumpFramesDmaObj);

            ChainsCommon_Osal_memFree(
                        (Ptr)gChainsObjTidl.outputBuf[0],
                        (gChainsObjTidl.inWidth * gChainsObjTidl.inHeight));

            ChainsCommon_Osal_memFree(
                        (Ptr)gChainsObjTidl.outputBuf[1],
                        (gChainsObjTidl.inWidth * gChainsObjTidl.inHeight));
        }

        /* Free the Algorithm create structure */
        ChainsCommon_Osal_memFree(
                    gChainsObjTidl.pAlgCreateParams,
                    sizeof(TIDL_CreateParams));
    }

    Vps_printf(" ############## END OF TIDL FILE I/O USE CASE ###############");
}
