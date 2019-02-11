/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file M2mVpeScale_test.c
 *
 *  \brief VPS VPE memory to memory driver example file.
 *
 *  Default Settings:
 *  -----------------
 *
 *  This illustrates the VPE memory to memory operation.
 *  It takes 10 frames of 720x240 YUV420 (NV12) interlaced input from the
 *  user. It performs deinterlacing and scale it to 360x240 YUYV422
 *  progressive output via WB0 path.
 *
 *  Other Configuration Options:
 *  ----------------------------
 *
 *  Input Format:
 *      Set VPE_IN_FMT to FVID2_DF_YUV422I_YUYV or FVID2_DF_YUV420SP_UV or
 *  FVID2_DF_YUV422SP_UV.
 *
 *  Output Format:
 *      Set VPE_OUT_FMT to FVID2_DF_YUV422I_YUYV or FVID2_DF_YUV420SP_UV or
 *  FVID2_DF_YUV422SP_UV, FVID2_DF_RGB24_888 or FVID2_DF_YUV444I.
 *
 *  Input Scan Format:
 *      Set VPE_IN_SCAN_FORMAT to FVID2_SF_INTERLACED/FVID2_SF_PROGRESSIVE.
 *  This will determine whether deinterlacer will be used or not.
 *
 *  Input/Output Buffer Dimension:
 *      Set the corresponding macros below VPE_OUT_WIDTH and VPE_OUT_HEIGHT
 *  to the desired value.
 *
 *  Number of Channels:
 *      Set VPE_NUM_CHANNELS to desired value. In the current application,
 *  all the channels uses the same input buffer but allocation of output
 *  buffers is separate for each of the channels.
 *
 *  VPE Input and Output Memory Type:
 *      When tiler is used, this application uses tiled buffer to perform the
 *  deinterlacing operation. But the input and output buffers used to load and
 *  store video is still in non-tiled memory space so that user could use
 *  non-tiled video content for load/store. This application does the
 *  non-tiled to tiled conversion by copying the input buffer to tiled space
 *  before submitting request to driver and by copying the tiled output buffer
 *  to non-tiled space after the request is complete.
 *  Note: When input is in tiled mode, VPE_IN_FMT could not be set to
 *  FVID2_DF_YUV422I_YUYV.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <M2mVpeScale_utils.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Uncomment this to get test VPE operation */
/* #define VPE_TEST_FMD */

/* Number of channels to submit per call. */
#define VPE_NUM_CHANNELS                (1U)

/* VPE input/output memory type - Tiled or Non-Tiled.
 * Tiler not supportted for TDA2Ex platform. */
#define VPE_IN_MEM_TYPE                 (VPS_VPDMA_MT_NONTILEDMEM)
#define VPE_OUT_MEM_TYPE                (VPS_VPDMA_MT_NONTILEDMEM)

/* Tiler orientation bits. Set this to BSPUTILS_TILER_ORI_NONE
 * or any | combination of BSPUTILS_TILER_ORI_X_FLIP,
 * BSPUTILS_TILER_ORI_Y_FLIP and BSPUTILS_TILER_ORI_XY_SWAP. */
#define VPE_IN_ORI_MODE                 (BSPUTILS_TILER_ORI_NONE)
#define VPE_OUT_ORI_MODE                (BSPUTILS_TILER_ORI_NONE)

/* Input frame video parameters. */
#define VPE_IN_WIDTH                    (720U)

/* VPE writeback output frame video parameters. */
#define VPE_OUT_WIDTH                   (360U)
#define VPE_OUT_HEIGHT                  (240U)
#define VPE_OUT_FMT                     (FVID2_DF_YUV422I_YUYV)

/* Uncomment this to get VPE peformance numbers */
#ifndef VPE_TEST_FMD
/* #define                                 VPE_PRF_TEST */
#endif

/* Number of loop count. */
#ifdef VPE_PRF_TEST
#define VPE_TOTAL_LOOP_COUNT            (10000U)
#else
#define VPE_TOTAL_LOOP_COUNT            (1U * VPE_NUM_IN_BUFFERS)
#endif

#ifndef SC_APP_TEST_SUBFRAME

/* Number of input buffers to allocate. This should be less than
 * VPE_MAX_IN_BUFFERS macro. */
#ifdef VPE_TEST_FMD
#define VPE_NUM_IN_BUFFERS              (20U)
#else
#define VPE_NUM_IN_BUFFERS              (10U)
#endif

/*
 * Height of VPE input frame. When VPE is deinterlacing, it should be
 * height of a field, otherwise it should be height of the entire frame.
 */
#define VPE_IN_HEIGHT                   (240U)
#define VPE_IN_FMT                      (FVID2_DF_YUV420SP_UV)
/*
 * Input/output buffer scan format. This will determine whether deinterlacer
 * will be used or not.
 */
#define VPE_IN_SCAN_FORMAT              (FVID2_SF_INTERLACED)
#define VPE_OUT_SCAN_FORMAT             (FVID2_SF_PROGRESSIVE)

#else /* #ifndef SC_APP_TEST_SUBFRAME */

/* Number of subframes per frame for subframe based processing */
#define SUBFRAMES_PER_FRAME             (4)
/* Number of input buffers to allocate. This should be less than
 * VPE_MAX_IN_BUFFERS macro. */
#define VPE_NUM_IN_BUFFERS              (1U)
/*
 * Height of VPE input frame. When VPE is deinterlacing, it should be
 * height of a field, otherwise it should be height of the entire frame.
 */
#define VPE_IN_HEIGHT                   (480U)
#define VPE_IN_FMT                      (FVID2_DF_YUV420SP_UV)
/*
 * Input/output buffer scan format. This will determine whether deinterlacer
 * will be used or not.
 */
#define VPE_IN_SCAN_FORMAT              (FVID2_SF_PROGRESSIVE)
#define VPE_OUT_SCAN_FORMAT             (FVID2_SF_PROGRESSIVE)

#endif /* #ifndef SC_APP_TEST_SUBFRAME */

/* Test application stack size. */
#define APP_TSK_STACK_SIZE              (10U * 1024U)

/* Check whether user provided buffer is more than what we could support */
#if (VPE_NUM_IN_BUFFERS > VPE_MAX_IN_BUFFERS)
#error "Increase VPE_MAX_IN_BUFFERS as per the changed VPE_NUM_IN_BUFFERS"
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void App_m2mVpeTestTask(void);
static Int32 App_m2mVpeTest(App_M2mVpeObj *appObj);
static Int32 App_m2mVpeAppCbFxn(Fvid2_Handle handle,
                                Ptr          appData,
                                Ptr          reserved);
static Int32 App_m2mVpeAppErrCbFxn(Fvid2_Handle handle,
                                   Ptr          appData,
                                   void        *errList,
                                   Ptr          reserved);
static void App_m2mVpeUpdateProcList(App_M2mVpeObj     *appObj,
                                     Fvid2_ProcessList *pList);
static void App_m2mVpeInitVariables(App_M2mVpeObj *appObj);
static void App_m2mVpeInitFrame(Fvid2_Frame *frm, UInt32 chNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(AppM2mVpeTestTaskStack, 32)
#pragma DATA_SECTION(AppM2mVpeTestTaskStack, ".bss:taskStackSection")
#endif
/* Test application stack. */
static UInt8            AppM2mVpeTestTaskStack[APP_TSK_STACK_SIZE];

/* M2M VPE application object per handle. */
static App_M2mVpeObj    M2mVpeObjs;

extern Semaphore_Handle AppTestCompleteSem;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  App_m2mVpeCreateTsk
 *  M2M VPE Application create task function.
 */
Task_Handle App_m2mVpeCreateTsk(void)
{
    Task_Params tskPrms;
    Task_Handle tskHandle;

    Task_Params_init(&tskPrms);
    tskPrms.stack     = AppM2mVpeTestTaskStack;
    tskPrms.stackSize = APP_TSK_STACK_SIZE;
    tskHandle         =
        Task_create((Task_FuncPtr) App_m2mVpeTestTask, &tskPrms, NULL);

    return (tskHandle);
}

/**
 *  App_m2mVpeTestTask
 *  M2M VPE Application test task.
 */
static void App_m2mVpeTestTask(void)
{
    char           userInput;
    Int32          retVal;
    App_M2mVpeObj *appObj;
    char           fileNameString[100];
    char           fileStr[30];
    UInt32         bytesRead, bytesWritten;

    /* Init application object with selected option */
    appObj                 = &M2mVpeObjs;
    appObj->numCh          = VPE_NUM_CHANNELS;
    appObj->inMemType      = VPE_IN_MEM_TYPE;
    appObj->outMemType     = VPE_OUT_MEM_TYPE;
    appObj->inOriMode      = VPE_IN_ORI_MODE;
    appObj->isInDimSwapped = (UInt32) FALSE;
    if ((VPS_VPDMA_MT_TILEDMEM == appObj->inMemType) &&
        (appObj->inOriMode & BSPUTILS_TILER_ORI_XY_SWAP))
    {
        appObj->isInDimSwapped = (UInt32) TRUE;
    }
    appObj->outOriMode      = VPE_OUT_ORI_MODE;
    appObj->isOutDimSwapped = (UInt32) FALSE;
    if ((VPS_VPDMA_MT_TILEDMEM == appObj->outMemType) &&
        (appObj->outOriMode & BSPUTILS_TILER_ORI_XY_SWAP))
    {
        appObj->isOutDimSwapped = (UInt32) TRUE;
    }
    appObj->numInBuffers = VPE_NUM_IN_BUFFERS;
    appObj->inWidth      = VPE_IN_WIDTH;
    appObj->inHeight     = VPE_IN_HEIGHT;
    appObj->inDrvWidth   = appObj->inWidth;
    appObj->inDrvHeight  = appObj->inHeight;
    if (TRUE == appObj->isInDimSwapped)
    {
        appObj->inDrvWidth  = appObj->inHeight;
        appObj->inDrvHeight = appObj->inWidth;
    }
    appObj->inDataFmt    = VPE_IN_FMT;
    appObj->outWidth     = VPE_OUT_WIDTH;
    appObj->outHeight    = VPE_OUT_HEIGHT;
    appObj->outDrvWidth  = appObj->outWidth;
    appObj->outDrvHeight = appObj->outHeight;
    if (TRUE == appObj->isOutDimSwapped)
    {
        appObj->outDrvWidth  = appObj->outHeight;
        appObj->outDrvHeight = appObj->outWidth;
    }
    appObj->outDataFmt = VPE_OUT_FMT;
    appObj->drvInst    = VPS_M2M_INST_VPE1;
    appObj->inScanFmt  = VPE_IN_SCAN_FORMAT;
    appObj->outScanFmt = VPE_OUT_SCAN_FORMAT;

    if (1U == appObj->numCh)
    {
        appObj->numOutBuffers = appObj->numInBuffers;
    }
    else
    {
        appObj->numOutBuffers = appObj->numInBuffers * appObj->numCh;
    }

    /* Allocate input and output buffers */
    retVal = App_m2mVpeAllocBuf(appObj);
    if (FVID2_SOK != retVal)
    {
        GT_3trace(BspAppTrace, GT_ERR,
                  "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal, __LINE__);
    }

    if (FVID2_SOK == retVal)
    {
        GT_6trace(
            BspAppTrace, GT_INFO,
            "%s: Load %d %s video frames/fields of size %dx%d to location: 0x%p\r\n",
            APP_NAME, appObj->numInBuffers,
            Fvid2_getDataFmtString(appObj->inDataFmt), appObj->inWidth,
            appObj->inHeight, appObj->inLoadBuf);
        BspUtils_appGetFileName(fileNameString,
                                sizeof(fileNameString),
                                "vpe",
                                appObj->inDataFmt,
                                appObj->inWidth,
                                appObj->inHeight);
        GT_0trace(BspAppTrace, GT_INFO,
                  "Trying to Load buffer from SD card. \r\n" );
        if (BSP_SOK != BspUtils_appLoadFileFromSd(
                fileNameString,
                "/vpe_input_files",
                (void *) appObj->inLoadBuf,
                appObj->numInBuffers * appObj->inBufSize,
                &bytesRead))
        {
            GT_0trace(BspAppTrace, GT_INFO,
                "Couldnot Load buffer from SD card.\r\n"
                "waiting for 1 min to load buffer from scripting console"
                "Press any key (in UART console) after loading buffer\r\n");

            BspUtils_appPrintLoadRawCmd(
                "vpe",
                (void *) appObj->inLoadBuf,
                appObj->inDataFmt,
                appObj->inWidth,
                appObj->inHeight);
            BspUtils_uartGetChar(&userInput, 60);
            BspOsal_cacheWbInv(appObj->inLoadBuf,
                               (appObj->numInBuffers * appObj->inBufSize),
                               BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
        }

        /* Copy input video to tiled input buffer */
        App_m2mVpeCopyToTilerMem(appObj);

        /* Run the test */
        retVal = App_m2mVpeTest(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_3trace(BspAppTrace, GT_ERR,
                      "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal,
                      __LINE__);
        }

        /* Copy processed tiled output video to output save buffer */
        App_m2mVpeCopyFromTilerMem(appObj);

        /* Wait for user to save the output buffers */
        if ((FVID2_SOK == retVal) && (NULL != appObj->outSaveBuf))
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      "%s: Save output buffers to file...\r\n", APP_NAME);
            snprintf(fileStr, sizeof(fileStr), "vpeInst%uCh%u",
                     (unsigned int) appObj->drvInst,
                     (unsigned int) appObj->numCh);
            BspUtils_appGetFileName(fileNameString,
                                    sizeof(fileNameString),
                                    fileStr,
                                    appObj->outDataFmt,
                                    appObj->outWidth,
                                    appObj->outHeight);
            if (BSP_SOK != BspUtils_appSaveFileToSd(
                    fileNameString,
                    "/vpe_output_files",
                    appObj->outSaveBuf,
                    (appObj->numOutBuffers * appObj->outBufSize),
                    &bytesWritten))
            {
                GT_0trace(BspAppTrace, GT_INFO,
                    "Couldnot save buffer to SD card. \r\n"
                    "waiting for 2 min to save buffer from scripting console"
                    "Press any key (in UART console) after saving buffer.\r\n");
                BspOsal_cacheInv(appObj->outSaveBuf,
                                (appObj->numOutBuffers * appObj->outBufSize),
                                BSP_OSAL_CT_ALL, BSP_OSAL_WAIT_FOREVER);
                BspUtils_appPrintSaveRawCmd(
                    fileStr,
                    appObj->outSaveBuf,
                    appObj->outDataFmt,
                    appObj->outWidth,
                    appObj->outHeight,
                    (appObj->numOutBuffers * appObj->outBufSize));
                BspUtils_uartGetChar(&userInput, 120);
            }
        }

        /* Free the allocated buffer memory */
        retVal = App_m2mVpeFreeBuf(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_3trace(BspAppTrace, GT_ERR,
                      "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal,
                      __LINE__);
        }

        GT_1trace(BspAppTrace, GT_INFO, "%s: Test Successfull!!\r\n", APP_NAME);

        /* Test complete. Signal it */
        Semaphore_post(AppTestCompleteSem);

        GT_1trace(BspAppTrace, GT_INFO,
                  APP_NAME ": Max stack used by test task: %d bytes\r\n",
                  BspOsal_getTaskStackUsage(NULL));
    }

    return;
}

/**
 *  App_m2mVpeTest
 *  M2M VPE test function.
 */
static Int32 App_m2mVpeTest(App_M2mVpeObj *appObj)
{
    Int32               retVal        = FVID2_SOK;
    Int32               cleanupRetVal = FVID2_SOK;
    UInt32              chCnt;
    Semaphore_Params    semPrms;
    Fvid2_CbParams      cbPrms;
    Fvid2_ProcessList  *pList;
    Vps_M2mCreateStatus createStatus;
    BspUtils_PrfTsHndl *prfTsHandle;
#ifdef  SC_APP_TEST_SUBFRAME
    Int32               subFrameNum;
#endif

    Semaphore_Params_init(&semPrms);
    appObj->reqCompleteSem = Semaphore_create(0, &semPrms, NULL);
    if (NULL == appObj->reqCompleteSem)
    {
        GT_1trace(BspAppTrace, GT_ERR, "%s: Sem alloc failed\r\n", APP_NAME);
        retVal = FVID2_EALLOC;
    }
    if (FVID2_SOK == retVal)
    {
        /* Start the TimeStamp Calculation */
        prfTsHandle = BspUtils_prfTsCreate(APP_NAME ":");

        /* Initialize the frame pointers and other variables */
        App_m2mVpeInitVariables(appObj);

        /* Open the driver */
        Fvid2CbParams_init(&cbPrms);
        cbPrms.cbFxn       = &App_m2mVpeAppCbFxn;
        cbPrms.errCbFxn    = &App_m2mVpeAppErrCbFxn;
        cbPrms.errList     = &appObj->errProcessList;
        cbPrms.appData     = appObj;
        appObj->fvidHandle = Fvid2_create(
            FVID2_VPS_M2M_DRV,
            appObj->drvInst,
            &appObj->createPrms,
            &createStatus,
            &cbPrms);
        if (NULL == appObj->fvidHandle)
        {
            GT_3trace(BspAppTrace, GT_ERR,
                      "%s: Error %d @ line %d\r\n", __FUNCTION__,
                      createStatus.retVal,
                      __LINE__);
            retVal = (createStatus.retVal);
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Set VPE params for each channel */
        for (chCnt = 0U; chCnt < appObj->numCh; chCnt++)
        {
            retVal = Fvid2_control(
                appObj->fvidHandle,
                IOCTL_VPS_M2M_SET_VPE_PARAMS,
                &appObj->vpePrms[chCnt],
                NULL);
            if (FVID2_SOK != retVal)
            {
                GT_1trace(BspAppTrace, GT_ERR,
                          "%s: Programming of VPE params failed\r\n", APP_NAME);
                break;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Print the driver status information */
        GT_2trace(BspAppTrace, GT_INFO,
                  "%s: M2M VPE Driver Opened for Instance %d!!\r\n",
                  APP_NAME, appObj->drvInst);
        BspUtils_appPrintM2mVpeCreateStatus(&createStatus);

        /* Program the scaler coefficients */
        retVal = App_m2mVpeProgramScCoeff(appObj);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(BspAppTrace, GT_ERR,
                      "%s: Programming of coefficients failed\r\n", APP_NAME);
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Allocate DEI context buffers */
        retVal = BspUtils_appAllocDeiCtxBuffer(
            appObj->fvidHandle,
            appObj->numCh);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(BspAppTrace, GT_ERR,
                      "%s: Allocation of context buffer failed\r\n", APP_NAME);
        }
    }
    if (FVID2_SOK == retVal)
    {
        appObj->fid = 0U;
        /* Use the same process list for all request */
        pList = &appObj->processList;

        /* Start the load calculation */
        BspUtils_prfLoadCalcStart();
        BspUtils_prfTsBegin(prfTsHandle);

        while (appObj->completedLoopCnt < VPE_TOTAL_LOOP_COUNT)
        {
            /* Update the buffer address */
            App_m2mVpeUpdateProcList(appObj, pList);

#ifndef SC_APP_TEST_SUBFRAME

#ifdef VPE_TEST_FMD
            /* Set the DEI film mode enable
             * This step must be here in order to enable FMD for DEI and as a
             * result start the FMD interrupts */
            if (0 == appObj->completedLoopCnt)
            {
                /* Enable FMD for DEI */
                retVal = App_m2mVpeSetFmdCfg(appObj, 1U);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(
                        BspAppTrace, GT_ERR,
                        "%s: DEI film mode enable/disable config failed\r\n",
                        APP_NAME);
                }
            }
#endif
            if (FVID2_SOK == retVal)
            {
                /* Process frames */
                retVal = Fvid2_processFrames(appObj->fvidHandle, pList);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(BspAppTrace, GT_ERR,
                              "%s: Processing of the request failed\r\n",
                              APP_NAME);
                }
            }
            if (FVID2_SOK == retVal)
            {
                /* Wait till frames get processed */
                Semaphore_pend(appObj->reqCompleteSem, BIOS_WAIT_FOREVER);

                /* Get the processed frames */
                retVal = Fvid2_getProcessedFrames(
                    appObj->fvidHandle,
                    pList,
                    FVID2_TIMEOUT_NONE);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(BspAppTrace, GT_ERR,
                              "%s: Get processed request failed\r\n", APP_NAME);
                }
            }

#else       /* subframe based processing */

            /* subframe by subframe processing. */
            for (subFrameNum = 0; subFrameNum < SUBFRAMES_PER_FRAME;
                 subFrameNum++)
            {
                Fvid2_Frame *inFrm;

                inFrm = pList->inFrameList[0]->frames[0];

                /* update subframe info in process list */
                inFrm->subFrameInfo->subFrameNum = subFrameNum;
                inFrm->subFrameInfo->numInLines  =
                    (subFrameNum + 1) * (appObj->inHeight / SUBFRAMES_PER_FRAME);

                /* Process frames */
                retVal = Fvid2_processFrames(appObj->fvidHandle, pList);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(BspAppTrace, GT_ERR,
                              "%s: Processing of the request failed\r\n",
                              APP_NAME);
                }

                if (FVID2_SOK == retVal)
                {
                    /* Wait till frames get processed */
                    Semaphore_pend(appObj->reqCompleteSem, BIOS_WAIT_FOREVER);

                    /* Get the processed frames */
                    retVal = Fvid2_getProcessedFrames(
                        appObj->fvidHandle,
                        pList,
                        FVID2_TIMEOUT_NONE);
                    if (FVID2_SOK != retVal)
                    {
                        GT_1trace(BspAppTrace, GT_ERR,
                                  "%s: Get processed request failed\r\n",
                                  APP_NAME);
                    }
                }
                if (FVID2_SOK != retVal)
                {
                    break;
                }
            }
#endif
            if (FVID2_SOK != retVal)
            {
                break;
            }

            appObj->completedLoopCnt++;
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Release the context fields */
        retVal = Fvid2_stop(appObj->fvidHandle, NULL);
        if (retVal != FVID2_SOK)
        {
            GT_1trace(BspAppTrace, GT_ERR,
                      "%s: Releasing held context fields failed\r\n", APP_NAME);
        }

        /* Dequeue all the request from driver */
        while (1U)
        {
            /* Get the processed frames */
            cleanupRetVal = Fvid2_getProcessedFrames(
                appObj->fvidHandle,
                pList,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK == cleanupRetVal)
            {
                appObj->completedLoopCnt++;
                GT_2trace(BspAppTrace, GT_INFO, "%s: Loop count: %d\r\n",
                          APP_NAME, appObj->completedLoopCnt);
            }
            else if (FVID2_ENO_MORE_BUFFERS == cleanupRetVal)
            {
                GT_1trace(BspAppTrace, GT_INFO,
                          "%s: All request dequeued from driver\r\n", APP_NAME);
                break;
            }
            else if (FVID2_EAGAIN == cleanupRetVal)
            {
                /* Still request pending with driver. Try after sometime. */
                Task_yield();
            }
            else
            {
                GT_3trace(BspAppTrace, GT_ERR,
                          "%s: Error %d @ line %d\r\n",
                          __FUNCTION__, cleanupRetVal, __LINE__);
                break;
            }
        }

        /* End of timestamp addition */
        BspUtils_prfTsEnd(prfTsHandle, VPE_TOTAL_LOOP_COUNT * appObj->numCh);
        /* Stop the load calculation */
        BspUtils_prfLoadCalcStop();

/* Print load only if its enabled else it might be wrong for very less frames */
#ifdef VPE_PRF_TEST
        /* Print the load */
        BspUtils_prfLoadPrintAll(TRUE);
        /* print the fps based on TimeStamp */
        BspUtils_prfTsPrint(prfTsHandle, TRUE);
#endif

        /* Reset the load */
        BspUtils_prfLoadCalcReset();
        /* Delete the timestamp instance */
        BspUtils_prfTsDelete(prfTsHandle);

        /* Free DEI context buffers */
        cleanupRetVal = BspUtils_appFreeDeiCtxBuffer(
            appObj->fvidHandle,
            appObj->numCh);
        if (FVID2_SOK != cleanupRetVal)
        {
            GT_1trace(BspAppTrace, GT_ERR,
                      "%s: Freeing of context buffer failed\r\n", APP_NAME);
            if (FVID2_SOK == retVal)
            {
                /* If processing was successful, return status of cleanup. */
                retVal = cleanupRetVal;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        /* Close driver */
        cleanupRetVal = Fvid2_delete(appObj->fvidHandle, NULL);
        if (FVID2_SOK != cleanupRetVal)
        {
            GT_3trace(BspAppTrace, GT_ERR,
                      "%s: Error %d @ line %d\r\n", __FUNCTION__, retVal,
                      __LINE__);
            if (FVID2_SOK == retVal)
            {
                /* If processing was successful, return status of cleanup. */
                retVal = cleanupRetVal;
            }
        }
    }
    if (FVID2_SOK == retVal)
    {
        Semaphore_delete(&appObj->reqCompleteSem);
        if (FVID2_SOK == retVal)
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      "%s: VPE Memory Driver Test Successfull!!\r\n", APP_NAME);
        }
        else
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      "%s: VPE Memory Driver Test Failed!!\r\n", APP_NAME);
        }

        GT_3trace(BspAppTrace, GT_INFO,
                  "%s: Desc Min Free %d, BSS Min Free %d!!\r\n", APP_NAME,
                  0, 0);
    }

    return (retVal);
}

/**
 *  App_m2mVpeAppCbFxn
 *  Driver callback function.
 */
static Int32 App_m2mVpeAppCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32          retVal = FVID2_SOK;
    App_M2mVpeObj *appObj = (App_M2mVpeObj *) appData;

    /* Transfer complete. Signal it */
    Semaphore_post(appObj->reqCompleteSem);

    return (retVal);
}

/**
 *  App_m2mVpeAppErrCbFxn
 *  Driver error callback function.
 */
static Int32 App_m2mVpeAppErrCbFxn(Fvid2_Handle handle,
                                   Ptr          appData,
                                   void        *errList,
                                   Ptr          reserved)
{
    Int32 retVal = FVID2_SOK;

    GT_0trace(BspAppTrace, GT_ERR, "Error occurred!!\r\n");

    return (retVal);
}

/**
 *  App_m2mVpeUpdateProcList
 *  Updates the process list with the next request buffer information.
 */
static void App_m2mVpeUpdateProcList(App_M2mVpeObj     *appObj,
                                     Fvid2_ProcessList *pList)
{
    UInt32           frmCnt, tempVar;
    UInt32           cbCrWidth, cbCrHeight;
    UInt32           inAddrY, inAddrCbCr;
    UInt32           outAddrY, outAddrCbCr;
    Fvid2_Frame     *frm;
    Fvid2_FrameList *inFrmList;
    Fvid2_FrameList *outFrmList = NULL;

    inFrmList  = pList->inFrameList[0U];
    outFrmList = pList->outFrameList[0U];

    /* Use the same input buffer for all channels */
    if (appObj->numInBuffers == appObj->inBufIdx)
    {
        appObj->inBufIdx = 0U;
    }

    for (frmCnt = 0U; frmCnt < appObj->numCh; frmCnt++)
    {
        /* Use different output buffer for each channel */
        if (appObj->numOutBuffers == appObj->outBufIdx)
        {
            appObj->outBufIdx = 0U;
        }
        if (VPS_VPDMA_MT_TILEDMEM == appObj->inMemType)
        {
            inAddrY = BspUtils_tilerGetOriAddr(
                (UInt32) appObj->inBufY[appObj->inBufIdx],
                BSPUTILS_TILER_CNT_8BIT,
                appObj->inOriMode,
                appObj->inWidth,
                appObj->inHeight);
            cbCrWidth  = appObj->inWidth;
            cbCrHeight = appObj->inHeight;
            if (Fvid2_isDataFmtYuv420Sp(appObj->inDataFmt))
            {
                if (TRUE == appObj->isInDimSwapped)
                {
                    cbCrWidth /= 2U;
                }
                else
                {
                    cbCrHeight /= 2U;
                }
            }
            inAddrCbCr = BspUtils_tilerGetOriAddr(
                (UInt32) appObj->inBufCbCr[appObj->inBufIdx],
                BSPUTILS_TILER_CNT_16BIT,
                appObj->inOriMode,
                cbCrWidth,
                cbCrHeight);
        }
        else
        {
            inAddrY    = (UInt32) appObj->inBufY[appObj->inBufIdx];
            inAddrCbCr = (UInt32) appObj->inBufCbCr[appObj->inBufIdx];
        }

        /* Update the VPE In list */
        frm = inFrmList->frames[frmCnt];
        /* Check if given frame was held back by driver, if so get the space
         * for frame description from context frames space */
        if (frm == NULL)
        {
            if (appObj->deiBypassFlag == TRUE)
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          "%s: Frames not returned in bypass@ line %d\r\n",
                          __FUNCTION__, __LINE__);
            }

            tempVar = appObj->freeCntxFrameIndex[frmCnt];
            if (tempVar < VPE_NO_OF_BUF_REQ_BEFORE_RES)
            {
                frm = &(appObj->cntxFrames[frmCnt][tempVar]);
                appObj->freeCntxFrameIndex[frmCnt]++;
            }
            else
            {
                GT_2trace(BspAppTrace, GT_ERR,
                          "%s: Error Out of context buf@ line %d\r\n",
                          __FUNCTION__, __LINE__);
                break;
            }
            inFrmList->frames[frmCnt] = frm;
        }
        if (appObj->deiBypassFlag == TRUE)
        {
            frm->fid          = FVID2_FID_FRAME;
            frm->subFrameInfo = &appObj->subFrameInfoIn[frmCnt];
            if (Fvid2_isDataFmtSemiPlanar(appObj->inDataFmt))
            {
                frm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_Y_ADDR_IDX] =
                    (UInt8 *) inAddrY;
                frm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_CBCR_ADDR_IDX] =
                    (UInt8 *) inAddrCbCr;
            }
            else
            {
                frm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_INT_ADDR_IDX] =
                    (UInt8 *) inAddrY;
            }
        }
        else
        {
            if (0U == appObj->fid)
            {
                frm->fid = FVID2_FID_TOP;
            }
            else
            {
                frm->fid = FVID2_FID_BOTTOM;
            }
            if (Fvid2_isDataFmtSemiPlanar(appObj->inDataFmt))
            {
                frm->addr[FVID2_FIELD_MODE_ADDR_IDX][FVID2_YUV_SP_Y_ADDR_IDX] =
                    (UInt8 *) inAddrY;
                frm->addr[FVID2_FIELD_MODE_ADDR_IDX]
                [FVID2_YUV_SP_CBCR_ADDR_IDX] = (UInt8 *) inAddrCbCr;
            }
            else
            {
                frm->addr[FVID2_FIELD_MODE_ADDR_IDX][FVID2_YUV_INT_ADDR_IDX] =
                    (UInt8 *) inAddrY;
            }
        }

        /* Update the VPE writeback Out list */
        if (VPS_VPDMA_MT_TILEDMEM == appObj->outMemType)
        {
            outAddrY = BspUtils_tilerGetOriAddr(
                (UInt32) appObj->outBufY[appObj->outBufIdx],
                BSPUTILS_TILER_CNT_8BIT,
                appObj->outOriMode,
                appObj->outWidth,
                appObj->outHeight);
            cbCrWidth  = appObj->outWidth;
            cbCrHeight = appObj->outHeight;
            if (Fvid2_isDataFmtYuv420Sp(appObj->outDataFmt))
            {
                if (TRUE == appObj->isOutDimSwapped)
                {
                    cbCrWidth /= 2U;
                }
                else
                {
                    cbCrHeight /= 2U;
                }
            }
            outAddrCbCr = BspUtils_tilerGetOriAddr(
                (UInt32)
                appObj->outBufCbCr[appObj->outBufIdx],
                BSPUTILS_TILER_CNT_16BIT,
                appObj->outOriMode,
                cbCrWidth,
                cbCrHeight);
        }
        else
        {
            outAddrY    = (UInt32) appObj->outBufY[appObj->outBufIdx];
            outAddrCbCr = (UInt32) appObj->outBufCbCr[appObj->outBufIdx];
        }
        frm               = outFrmList->frames[frmCnt];
        frm->fid          = FVID2_FID_FRAME;
        frm->subFrameInfo = &appObj->subFrameInfoOut[frmCnt];
        if (Fvid2_isDataFmtSemiPlanar(appObj->outDataFmt))
        {
            frm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_Y_ADDR_IDX] =
                (UInt8 *) outAddrY;
            frm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_SP_CBCR_ADDR_IDX] =
                (UInt8 *) outAddrCbCr;
        }
        else
        {
            frm->addr[FVID2_FRAME_ADDR_IDX][FVID2_YUV_INT_ADDR_IDX] =
                (UInt8 *) outAddrY;
        }

        appObj->outBufIdx++;
    }

    /* Updated the number of frames present - would have been cleared */
    inFrmList->numFrames = appObj->numCh;
    pList->numInLists    = 1U;
    appObj->fid          = appObj->fid ^ 1U;
    appObj->inBufIdx++;

    return;
}

/**
 *  vpsInitDefaultSubFramePrms
 *  Sets the default parameters for sub-frame level processing .
 */
#ifdef SC_APP_TEST_SUBFRAME
static void vpsInitDefaultSubFramePrms(App_M2mVpeObj      *appObj,
                                       Vps_SubFrameParams *slcPrms)
{
    if (appObj->deiBypassFlag == TRUE)
    {
        slcPrms->subFrameEnable      = TRUE;
        slcPrms->numLinesPerSubFrame = (appObj->inHeight / SUBFRAMES_PER_FRAME);
    }
    else /* SubFrame mode will not work if DEI is active */
    {
        slcPrms->subFrameEnable      = FALSE;
        slcPrms->numLinesPerSubFrame = (appObj->inHeight / SUBFRAMES_PER_FRAME);
        GT_0trace(BspAppTrace, GT_INFO,
                  "SubFrame Mode disabled as DEI is enabled: "
                  "disable DEI to use subframe mode\r\n");
    }
}

#endif

/**
 *  vpsInitDefaultScCropPrms
 *  Sets the default scaler and crop parameters.
 */
static void vpsInitDefaultScCropPrms(const App_M2mVpeObj *appObj,
                                     Vps_ScConfig        *scCfg,
                                     Fvid2_CropConfig    *cropCfg)
{
    scCfg->bypass        = FALSE;
    scCfg->nonLinear     = FALSE;
    scCfg->stripSize     = 0U;
    scCfg->enablePeaking = TRUE;
    /* Edge detect is enabled for the SC_H and is dont care for all other
     * scalers */
    scCfg->enableEdgeDetect = TRUE;
    scCfg->advCfg           = NULL;

    cropCfg->cropStartX = 0U;
    cropCfg->cropStartY = 0U;
    cropCfg->cropWidth  = appObj->inDrvWidth;
    if (TRUE == appObj->deiBypassFlag)
    {
        cropCfg->cropHeight = appObj->inDrvHeight;
    }
    else
    {
        cropCfg->cropHeight = appObj->inDrvHeight * 2U;
    }

    return;
}

/**
 *  vpsSetDefaultChPrms
 *  Sets the default channel parameters.
 */
static void vpsSetDefaultChPrms(const App_M2mVpeObj *appObj,
                                Vps_M2mVpeParams    *vpePrms,
                                UInt32               chNum)
{
    Fvid2_Format *fmt;

    /* Init the module parameters */
    VpsM2mVpeParams_init(vpePrms);
    vpePrms->chNum      = chNum;
    vpePrms->inMemType  = appObj->inMemType;
    vpePrms->outMemType = appObj->outMemType;

    /* Set the FVID2 format for VPE input */
    fmt         = &vpePrms->inFmt;
    fmt->chNum  = chNum;
    fmt->width  = appObj->inDrvWidth;
    fmt->height = appObj->inDrvHeight;
    if (Fvid2_isDataFmtSemiPlanar(appObj->inDataFmt))
    {
        fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX]          = appObj->inPitchY;
        fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]       = appObj->inPitchCbCr;
        fmt->fieldMerged[FVID2_YUV_SP_Y_ADDR_IDX]    = FALSE;
        fmt->fieldMerged[FVID2_YUV_SP_CBCR_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
        if (Fvid2_isDataFmtYuv420Sp(appObj->inDataFmt))
        {
            fmt->bpp = FVID2_BPP_BITS12;
        }
    }
    else
    {
        fmt->pitch[FVID2_YUV_INT_ADDR_IDX]       = appObj->inPitchY;
        fmt->fieldMerged[FVID2_YUV_INT_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
    }
    fmt->dataFormat = appObj->inDataFmt;
    fmt->scanFormat = appObj->inScanFmt;

    /* Set the FVID2 format for VPE writeback output */
    fmt         = &vpePrms->outFmt;
    fmt->chNum  = chNum;
    fmt->width  = appObj->outDrvWidth;
    fmt->height = appObj->outDrvHeight;
    if (Fvid2_isDataFmtSemiPlanar(appObj->outDataFmt))
    {
        fmt->pitch[FVID2_YUV_SP_Y_ADDR_IDX]          = appObj->outPitchY;
        fmt->pitch[FVID2_YUV_SP_CBCR_ADDR_IDX]       = appObj->outPitchCbCr;
        fmt->fieldMerged[FVID2_YUV_SP_Y_ADDR_IDX]    = FALSE;
        fmt->fieldMerged[FVID2_YUV_SP_CBCR_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
        if (Fvid2_isDataFmtYuv420Sp(appObj->outDataFmt))
        {
            fmt->bpp = FVID2_BPP_BITS12;
        }
    }
    else
    {
        fmt->pitch[FVID2_YUV_INT_ADDR_IDX]       = appObj->outPitchY;
        fmt->fieldMerged[FVID2_YUV_INT_ADDR_IDX] = FALSE;
        fmt->bpp = FVID2_BPP_BITS16;
        if ((FVID2_DF_RGB24_888 == appObj->outDataFmt) ||
            (FVID2_DF_YUV444I == appObj->outDataFmt))
        {
            fmt->bpp = FVID2_BPP_BITS24;
        }
    }
    fmt->dataFormat = appObj->outDataFmt;
    fmt->scanFormat = appObj->outScanFmt;

    vpePrms->deiCfg.bypass = appObj->deiBypassFlag;
    vpsInitDefaultScCropPrms(appObj, &vpePrms->scCfg, &vpePrms->scCropCfg);

    /* Disable scalers if input and output dimensions are same */
    if (TRUE == appObj->deiBypassFlag)
    {
        if ((appObj->inDrvWidth == appObj->outDrvWidth) &&
            (appObj->inDrvHeight == appObj->outDrvHeight))
        {
            vpePrms->scCfg.bypass = TRUE;
        }
        else
        {
            vpePrms->scCfg.bypass = FALSE;
        }
    }
    else
    {
        if ((appObj->inDrvWidth == appObj->outDrvWidth) &&
            ((appObj->inDrvHeight * 2U) == appObj->outDrvHeight))
        {
            vpePrms->scCfg.bypass = TRUE;
        }
        else
        {
            vpePrms->scCfg.bypass = FALSE;
        }
    }

    /* Set sub-frame params */
    VpsSubFrameParams_init(&vpePrms->subFramePrms);
#ifdef SC_APP_TEST_SUBFRAME
    vpsInitDefaultSubFramePrms(appObj, &vpePrms->subFramePrms);
#endif

    return;
}

/**
 *  App_m2mVpeInitVariables
 *  Initialize the global variables and frame pointers.
 */
static void App_m2mVpeInitVariables(App_M2mVpeObj *appObj)
{
    UInt32 chCnt, frmCnt, fListCnt, cntxIndex;
    Fvid2_Frame       *frm;
    Fvid2_FrameList   *fList;
    Fvid2_ProcessList *pList;
    Vps_M2mVpeParams  *vpePrms;

    /* Set this first as other functions need this to be done first */
    if (appObj->inScanFmt == appObj->outScanFmt)
    {
        appObj->deiBypassFlag = TRUE;
    }
    else
    {
        appObj->deiBypassFlag = FALSE;
    }

    /* Init create params */
    VpsM2mCreateParams_init(&appObj->createPrms);
    appObj->createPrms.numCh           = appObj->numCh;
    appObj->createPrms.chInQueueLength = VPS_M2M_DEF_QUEUE_LEN_PER_CH;
#ifdef VPE_TEST_FMD
    appObj->createPrms.isDeiFmdEnable = TRUE;
#else
    appObj->createPrms.isDeiFmdEnable = FALSE;
#endif

    for (chCnt = 0U; chCnt < appObj->numCh; chCnt++)
    {
        vpePrms = &appObj->vpePrms[chCnt];

        /* Init channel params */
        vpsSetDefaultChPrms(appObj, vpePrms, chCnt);
    }

    /* Init other globals used in buffer exchange */
    appObj->inBufIdx         = 0;
    appObj->outBufIdx        = 0;
    appObj->completedLoopCnt = 0;

    pList = &appObj->processList;
    Fvid2ProcessList_init(pList);
    pList->inFrameList[0U]  = &appObj->frameList[0U];
    pList->outFrameList[0U] = &appObj->frameList[1U];
    pList->numInLists       = 1U;
    pList->numOutLists      = 1U;

    for (fListCnt = 0U; fListCnt < VPE_NUM_FRAMELIST_PER_PLIST; fListCnt++)
    {
        fList = &appObj->frameList[fListCnt];
        Fvid2FrameList_init(fList);
        fList->numFrames = appObj->numCh;
        for (frmCnt = 0U; frmCnt < appObj->numCh; frmCnt++)
        {
            frm = &appObj->frames[fListCnt][frmCnt];
            fList->frames[frmCnt] = frm;
            App_m2mVpeInitFrame(frm, frmCnt);
        }
    }

    for (chCnt = 0x0; chCnt < VPS_M2M_MAX_CH_PER_HANDLE; chCnt++)
    {
        Fvid2SubFrameInfo_init(&appObj->subFrameInfoIn[chCnt]);
        Fvid2SubFrameInfo_init(&appObj->subFrameInfoOut[chCnt]);
        appObj->freeCntxFrameIndex[chCnt] = 0x0;
        for (cntxIndex = 0x0;
             cntxIndex < VPE_NO_OF_BUF_REQ_BEFORE_RES;
             cntxIndex++)
        {
            App_m2mVpeInitFrame(&(appObj->cntxFrames[chCnt][cntxIndex]),
                                chCnt);
        }
    }

    /* Init error process list */
    BspUtils_memset(
        &appObj->errProcessList,
        0U,
        sizeof (appObj->errProcessList));

    return;
}

static void App_m2mVpeInitFrame(Fvid2_Frame *frm, UInt32 chNum)
{
    Fvid2Frame_init(frm);
    frm->chNum = chNum;

    return;
}

