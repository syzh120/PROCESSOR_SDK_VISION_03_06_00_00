/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2016
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file st_vpeTestCase.c
 *
 *  \brief Code for testing VPE driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <testLib/st_vpe.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 st_vpeCreatePhase(st_VpeHandleObj *hObj);
static Int32 st_vpeDeletePhase(st_VpeHandleObj *hObj);
static Int32 st_vpeRunPhase(st_VpeHandleObj *hObj);
static Int32 st_vpeProcessFrames(st_VpeHandleObj *hObj);

static Int32 st_vpeCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved);
static Int32 st_vpeErrCbFxn(Fvid2_Handle handle,
                            Ptr          appData,
                            Void        *errList,
                            Ptr          reserved);
static void st_vpeUpdateProcList(st_VpeHandleObj   *hObj,
                                 Fvid2_ProcessList *pList);

static Void st_vpeClkHandler(UArg arg);
static Int32 st_vpeSaveOutputToFile(st_VpeHandleObj *hObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  st_vpeMainTestCase
 *  VPE test function.
 */
Int32 st_vpeMainTestCase(st_VpeHandleObj *hObj)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    Bool   createFlag;
    UInt32 openCloseCnt, startStopCnt;

    if (hObj->handleCfg.openCloseCnt > 1u)
    {
        GT_2trace(hObj->traceMask, GT_INFO,
                  "%s: |Open/Close Test Case: %d times|\r\n",
                  APP_NAME, hObj->handleCfg.openCloseCnt);
    }
    openCloseCnt = 0u;
    while (openCloseCnt < hObj->handleCfg.openCloseCnt)
    {
        /* Create phase */
        createFlag = FALSE;
        retVal     = st_vpeCreatePhase(hObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(hObj->traceMask, GT_ERR, "Create phase failed\r\n");
        }
        else
        {
            createFlag = TRUE;
        }

        if (FVID2_SOK == retVal)
        {
            if ((1u == hObj->handleCfg.openCloseCnt) &&
                (hObj->handleCfg.startStopCnt > 1u))
            {
                GT_2trace(hObj->traceMask, GT_INFO,
                          "%s: |Start/Stop Test Case: %d times|\r\n",
                          APP_NAME, hObj->handleCfg.startStopCnt);
            }
            startStopCnt = 0u;
            while (startStopCnt < hObj->handleCfg.startStopCnt)
            {
                retVal = st_vpeRunPhase(hObj);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(hObj->traceMask, GT_ERR,
                              "Run phase failed @ %d start/stop count\r\n",
                              startStopCnt);
                    break;
                }
                startStopCnt++;
                if ((startStopCnt > 0u) &&
                    ((startStopCnt % (START_STOP_CNT_SS / 10u)) == 0u))
                {
                    GT_2trace(hObj->traceMask, GT_INFO,
                              "%s: Start/Stop Test Count: %d\r\n",
                              APP_NAME, startStopCnt);
                }
            }
        }

        if (FVID2_SOK == retVal)
        {
            /* Save output - for the last open-close count */
            if ((openCloseCnt == (hObj->handleCfg.openCloseCnt - 1u)) &&
                (TRUE == hObj->sysCtrl->fileIoEnable))
            {
                retVal = st_vpeSaveOutputToFile(hObj);
            }
        }

        if (TRUE == createFlag)
        {
            /* Delete phase */
            tempRetVal = st_vpeDeletePhase(hObj);
            if (FVID2_SOK != tempRetVal)
            {
                retVal = tempRetVal;
                GT_0trace(hObj->traceMask, GT_ERR, "Delete phase failed\r\n");
            }
        }

        if (FVID2_SOK != retVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      "Open/Close failed @ %d count\r\n", openCloseCnt);
            break;
        }

        openCloseCnt++;
        if ((openCloseCnt > 0u) &&
            ((openCloseCnt % (OPEN_CLOSE_CNT_OC / 10u)) == 0u))
        {
            GT_2trace(hObj->traceMask, GT_INFO,
                "%s: Open/Close Test Count: %d\r\n", APP_NAME, openCloseCnt);
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_2trace(hObj->traceMask, GT_INFO,
                  "%s: VPE Test Case %d Successful!!\r\n",
                  APP_NAME, hObj->testPrms->testCaseId);
    }
    else
    {
        GT_2trace(hObj->traceMask, GT_INFO,
                  "%s: VPE Test Case %d Failed!!\r\n",
                  APP_NAME, hObj->testPrms->testCaseId);
    }

    return (retVal);
}

/**
 *  st_vpeCreatePhase
 *  Performs all create time operations.
 */
static Int32 st_vpeCreatePhase(st_VpeHandleObj *hObj)
{
    Int32        retVal = FVID2_SOK, tempRetVal;
    UInt32       chCnt;
    Bool         initVarFlag, ctxAllocFlag;
    UInt32       clkTicks;
    Clock_Params clkPrms;

    /* Initialize and allocate handles */
    initVarFlag  = FALSE;
    ctxAllocFlag = FALSE;
    retVal       = st_vpeInitVariables(hObj);
    if (FVID2_SOK == retVal)
    {
        initVarFlag = TRUE;
    }

    if (hObj->handleCfg.taskCtxEnable == TRUE)
    {
        /* Currently disabling Async mode for Task context
         * due to a bug in UT. */
        hObj->handleCfg.asyncQueEnable = FALSE;
    }

    /* In case of Async Q De-Q create timer object */
    if (hObj->handleCfg.asyncQueEnable == TRUE)
    {
        /* Initialize Clock Params and create Clock Object */
        hObj->asyncCbCnt   = 0;
        hObj->asyncTimerOn = FALSE;
        Clock_Params_init(&clkPrms);
        clkPrms.period    = 5;
        clkPrms.startFlag = FALSE;
        clkPrms.arg       = (UArg) hObj;
        GT_0trace(hObj->traceMask, GT_INFO1, "Creating clock async object\r\n");
        hObj->asyncClkHandle =
            Clock_create(st_vpeClkHandler, 5, &clkPrms, NULL);
        if (NULL == hObj->asyncClkHandle)
        {
            GT_0trace(hObj->traceMask, GT_ERR, "Clock create failed\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if (FVID2_SOK == retVal)
    {
        hObj->cbParams.cbFxn    = &st_vpeCbFxn;
        hObj->cbParams.errCbFxn = &st_vpeErrCbFxn;
        hObj->cbParams.errList  = &hObj->errProcessList;
        hObj->cbParams.appData  = hObj;

        /* In case of async queing change the Callback function */
        if (hObj->handleCfg.asyncQueEnable == TRUE)
        {
            /* Determine the random time value here as it cannot
             * be done in the Callback function */
            clkTicks = BspOsal_getCurTimeInMsec();
            srand(clkTicks);
            hObj->asyncTimerValue  = rand();
            hObj->asyncTimerValue %= 200;
        }

        /* Open the driver */
        hObj->fvidHandle = Fvid2_create(
            FVID2_VPS_M2M_DRV,
            hObj->drvInst,
            &hObj->createPrms,
            &hObj->createStatus,
            &hObj->cbParams);
        if (NULL == hObj->fvidHandle)
        {
            GT_0trace(hObj->traceMask, GT_ERR, "VPE driver create failed\r\n");
            retVal = hObj->createStatus.retVal;
        }
        else
        {
            GT_assert(hObj->traceMask,
                      (hObj->createStatus.retVal == FVID2_SOK));
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Set VPE params for each channel */
        for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
        {
            retVal = Fvid2_control(
                hObj->fvidHandle,
                IOCTL_VPS_M2M_SET_VPE_PARAMS,
                &hObj->chObj[chCnt].vpePrms,
                NULL);
            if (FVID2_SOK != retVal)
            {
                GT_2trace(
                    hObj->traceMask, GT_ERR,
                    "%s: Programming of VPE params failed for %d channel\r\n",
                    APP_NAME, chCnt);
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Program the scaler coefficients */
        retVal = st_vpeProgramScCoeff(hObj);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      "%s: Programming of coefficients failed\r\n", APP_NAME);
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate DEI context buffers */
        retVal = BspUtils_appAllocDeiCtxBuffer(
            hObj->fvidHandle,
            hObj->numCh);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      "%s: Allocation of context buffer failed\r\n", APP_NAME);
        }
        else
        {
            ctxAllocFlag = TRUE;
        }
    }

    if (FVID2_SOK == retVal)
    {
        GT_2trace(hObj->traceMask, GT_INFO1,
                  "%s: VPE Driver Opened for Instance %d!!\r\n",
                  APP_NAME, hObj->drvInst);
        st_vpePrintM2mVpeCreateStatus(hObj, &hObj->createStatus);
    }

    /*
     * Deallocate resource/close handles if error occurs
     */
    if (FVID2_SOK != retVal)
    {
        /* Delete instance of clock created in case of Async De-Q */
        if (NULL != hObj->asyncClkHandle)
        {
            Clock_delete(&hObj->asyncClkHandle);
            hObj->asyncClkHandle = NULL;
        }

        if (NULL != hObj->fvidHandle)
        {
            if (TRUE == ctxAllocFlag)
            {
                tempRetVal = BspUtils_appFreeDeiCtxBuffer(
                    hObj->fvidHandle,
                    hObj->numCh);
                if (FVID2_SOK != tempRetVal)
                {
                    GT_1trace(hObj->traceMask, GT_ERR,
                              "%s: Freeing of context buffer failed\r\n",
                              APP_NAME);
                }
            }

            /* Close driver */
            tempRetVal = Fvid2_delete(hObj->fvidHandle, NULL);
            if (FVID2_SOK != tempRetVal)
            {
                GT_0trace(hObj->traceMask, GT_ERR, "VPE delete failed\r\n");
            }
        }

        if (TRUE == initVarFlag)
        {
            /* Free allocated handles */
            st_vpeFreeVariables(hObj);
        }
    }

    return (retVal);
}

/**
 *  st_vpeDeletePhase
 *  Performs all delete time operations.
 */
static Int32 st_vpeDeletePhase(st_VpeHandleObj *hObj)
{
    Int32 retVal = FVID2_SOK, tempRetVal;

    /* Delete instance of clock created in case of Async De-Q */
    if (NULL != hObj->asyncClkHandle)
    {
        Clock_delete(&hObj->asyncClkHandle);
        hObj->asyncClkHandle = NULL;
    }

    if (NULL != hObj->fvidHandle)
    {
        tempRetVal = BspUtils_appFreeDeiCtxBuffer(
            hObj->fvidHandle,
            hObj->numCh);
        if (FVID2_SOK != tempRetVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      "%s: Freeing of context buffer failed\r\n", APP_NAME);
            retVal = tempRetVal;
        }

        /* Close driver */
        tempRetVal = Fvid2_delete(hObj->fvidHandle, NULL);
        if (FVID2_SOK != tempRetVal)
        {
            GT_0trace(hObj->traceMask, GT_ERR, "VPE delete failed\r\n");
            retVal = tempRetVal;
        }
        hObj->fvidHandle = NULL;
    }

    /* Free allocated handles */
    st_vpeFreeVariables(hObj);

    return (retVal);
}

/**
 *  st_vpeRunPhase
 *  Performs all run time operations.
 */
static Int32 st_vpeRunPhase(st_VpeHandleObj *hObj)
{
    Int32  retVal = FVID2_SOK;
    UInt32 frmCnt, fListCnt;
    UInt32 startTime, endTime;
    UInt32 chCnt, crcValue, chCrcIdx;
    Int32  subFrmNum;
    Fvid2_Frame       *frm, *subFrm;
    Fvid2_FrameList   *fList;
    Fvid2_ProcessList *pList;

    /* Use the same process list for all request */
    pList = &hObj->processList;

    /* Re-init proc list, as during driver stop, out frame list is set to 0
     * by driver to give back the retained context input buffers */
    pList->inFrameList[0u]  = &hObj->frameList[0u];
    pList->outFrameList[0u] = &hObj->frameList[1u];
    pList->numInLists       = 1u;
    pList->numOutLists      = 1u;

    if (TRUE == hObj->handleCfg.prfEnable)
    {
        /* Start the load calculation */
        BspUtils_prfLoadCalcStart();
        BspUtils_prfTsBegin(hObj->prfTsHandle);
    }
    startTime = BspOsal_getCurTimeInMsec();

    /* Init frame list */
    for (fListCnt = 0u; fListCnt < VPE_NUM_FRAMELIST_PER_PLIST; fListCnt++)
    {
        fList = &hObj->frameList[fListCnt];
        Fvid2FrameList_init(fList);
        fList->numFrames = hObj->numCh;
        for (frmCnt = 0u; frmCnt < hObj->numCh; frmCnt++)
        {
            frm = &hObj->frames[fListCnt][frmCnt];
            fList->frames[frmCnt] = frm;
            Fvid2Frame_init(frm);
            frm->chNum = frmCnt;
        }
    }

    /* Caution: Assuming 1st channel num slice is same for all channels */
    if (TRUE == hObj->chObj[0u].chCfg.subFrmPrms.subFrameEnable)
    {
        while (hObj->completedLoopCnt < hObj->handleCfg.loopCnt)
        {
            /* Update the buffer address */
            st_vpeUpdateProcList(hObj, pList);

            for (subFrmNum = 0;
                 subFrmNum < hObj->chObj[0u].chCfg.numSubFrmPerFrm;
                 subFrmNum++)
            {
                /* update subframe info in process list for all channels */
                for (frmCnt = 0u; frmCnt < hObj->numCh; frmCnt++)
                {
                    subFrm = pList->inFrameList[0]->frames[frmCnt];
                    subFrm->subFrameInfo->subFrameNum = subFrmNum;
                    subFrm->subFrameInfo->numInLines  =
                        (subFrmNum + 1u) *
                        (hObj->chObj[frmCnt].chCfg.subFrmPrms.
                         numLinesPerSubFrame);
                }

                /* Process slice */
                retVal = Fvid2_processFrames(hObj->fvidHandle, pList);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(hObj->traceMask, GT_ERR,
                              "%s: Processing of the request failed\r\n",
                              APP_NAME);
                    break;
                }

                /* Wait till frames get processed */
                Semaphore_pend(hObj->reqCompleteSem, BIOS_WAIT_FOREVER);

                /* Get the processed slice */
                retVal = Fvid2_getProcessedFrames(
                    hObj->fvidHandle,
                    pList,
                    FVID2_TIMEOUT_NONE);
                if (FVID2_SOK != retVal)
                {
                    GT_1trace(hObj->traceMask, GT_ERR,
                              "%s: DeQueuing failed\r\n", APP_NAME);
                    break;
                }
            }
            hObj->completedLoopCnt++;
        }
    }
    else
    {
        /*
         * Prime buffers!!!
         */
        /* Update the buffer address */
        st_vpeUpdateProcList(hObj, pList);

        /* Process frames */
        retVal = Fvid2_processFrames(hObj->fvidHandle, pList);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      "%s: Processing of the request failed\r\n", APP_NAME);
        }

        if (FVID2_SOK == retVal)
        {
            if (TRUE == hObj->handleCfg.taskCtxEnable)
            {
                while (hObj->completedLoopCnt < hObj->handleCfg.loopCnt)
                {
                    /* Wait till frames get processed */
                    Semaphore_pend(hObj->reqCompleteSem, BIOS_WAIT_FOREVER);

                    /* Process frames */
                    retVal = st_vpeProcessFrames(hObj);
                    if (FVID2_SOK != retVal)
                    {
                        break;
                    }
                }
            }
            else
            {
                /* Wait for all frames to get processed from ISR context */
                Semaphore_pend(hObj->reqCompleteSem, BIOS_WAIT_FOREVER);
            }

            if (TRUE == hObj->handleCfg.prfEnable)
            {
                BspUtils_prfTsEnd(
                    hObj->prfTsHandle,
                    (hObj->handleCfg.loopCnt * hObj->numCh));
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Release the context fields */
        retVal = Fvid2_stop(hObj->fvidHandle, NULL);
        if (FVID2_SOK != retVal)
        {
            GT_1trace(hObj->traceMask, GT_ERR,
                      "%s: Releasing held context fields failed\r\n", APP_NAME);
        }
    }

    if (FVID2_SOK == retVal)
    {
        endTime = BspOsal_getCurTimeInMsec();

        if (TRUE == hObj->handleCfg.prfEnable)
        {
            /* Calculate performance number */
            st_vpeCalcPerformance(hObj, (endTime - startTime));

            /* Stop the load calculation */
            BspUtils_prfLoadCalcStop();
            /* Print the load */
            BspUtils_prfLoadPrintAll(TRUE);
            /* print the fps based on TimeStamp */
            BspUtils_prfTsPrint(hObj->prfTsHandle, TRUE);

            /* Reset the load */
            BspUtils_prfLoadCalcReset();
        }

        /* Dequeue all the request from driver */
        while (1u)
        {
            /* Get the processed frames */
            retVal = Fvid2_getProcessedFrames(
                hObj->fvidHandle,
                pList,
                FVID2_TIMEOUT_NONE);
            if (FVID2_SOK == retVal)
            {
                hObj->completedLoopCnt++;
                GT_2trace(hObj->traceMask, GT_INFO1, "%s: Loop count: %d\r\n",
                          APP_NAME, hObj->completedLoopCnt);
            }
            else if (FVID2_ENO_MORE_BUFFERS == retVal)
            {
                retVal = FVID2_SOK;
                break;
            }
            else if (FVID2_EAGAIN == retVal)
            {
                /* Still request pending with driver. Try after sometime. */
                Task_yield();
            }
            else
            {
                GT_0trace(hObj->traceMask, GT_ERR, "DeQueuing failed\r\n");
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Print the status */
        if (hObj->traceMask == (GT_INFO1 | GT_TraceState_Enable))
        {
            st_vpePrintTimeStatus(hObj, FALSE);
        }
    }

    if ((TRUE == hObj->testPrms->crcCheckEnable) &&
        (Bsp_platformGetId() == BSP_PLATFORM_ID_EVM))
    {
        chCrcIdx = hObj->startChIdx;
        for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
        {
            crcValue =
                st_calcBufferCrc(
                    hObj->chObj[chCnt].outSaveBuf,
                    hObj->chObj[chCnt].outSaveBufSize);
            GT_3trace(hObj->traceMask, GT_INFO,
                      "%s: CH%d CRC32 value: 0x%0.8x!!\r\n",
                      APP_NAME, chCnt, crcValue);
            if (crcValue != hObj->testPrms->crcValue[chCrcIdx])
            {
                GT_4trace(
                    hObj->traceMask, GT_INFO,
                    "%s: Warning: CH%d CRC32 value 0x%0.8x doesn't match "
                    "with expected CRC32 of 0x%0.8x!!\r\n",
                    APP_NAME, chCnt, crcValue,
                    hObj->testPrms->crcValue[chCrcIdx]);
            }
            chCrcIdx++;
        }
    }

    return (retVal);
}

/**
 *  st_vpeProcessFrames
 *  Performs dequeue/process/queue operations.
 */
static Int32 st_vpeProcessFrames(st_VpeHandleObj *hObj)
{
    Int32  retVal = FVID2_SOK;
    Fvid2_ProcessList  *pList;
    UInt32 clkTicks, timePeriod;
    Int32  noCntIncrFlag = 0u;

    /* Dequeue buffer from driver */
    pList  = &hObj->processList;
    retVal = Fvid2_getProcessedFrames(
        hObj->fvidHandle,
        pList,
        FVID2_TIMEOUT_NONE);
    if ((FVID2_SOK != retVal) && (FVID2_EAGAIN == retVal))
    {
        /* Driver could return error if no buffers are to be dequeued */
        retVal        = FVID2_SOK;
        noCntIncrFlag = 1;
    }
    else if ((FVID2_SOK != retVal) && (FVID2_EAGAIN != retVal))
    {
        GT_0trace(hObj->traceMask, GT_ERR, "DeQueuing failed\r\n");
        noCntIncrFlag = 1;
    }
    else
    {
        noCntIncrFlag = 0;

        if (FALSE == hObj->handleCfg.asyncQueEnable)
        {
            /* Update the buffer address */
            st_vpeUpdateProcList(hObj, pList);

            /* Process frames */
            retVal = Fvid2_processFrames(hObj->fvidHandle, pList);
            if (FVID2_SOK != retVal)
            {
                GT_0trace(hObj->traceMask, GT_ERR, "Queuing failed\r\n");
            }
        }
    }

    hObj->completedLoopCnt++;
    if ((TRUE == hObj->sysCtrl->rtPrintEnable) &&
        (hObj->completedLoopCnt % 2000u == 0u))
    {
        if (0u == hObj->taskId)
        {
            st_vpePrintTimeStatus(hObj, TRUE);
        }

        Bsp_rprintf("<%d> %s: Loop count: %8d\r\n",
                    BspOsal_getCurTimeInMsec(), APP_NAME,
                    hObj->completedLoopCnt);
    }

    if ((retVal == FVID2_SOK) && (0u == noCntIncrFlag))
    {
        /* Increment Callback count */
        if (FVID2_SOK == retVal)
        {
            hObj->asyncCbCnt++;
        }

        /* Start timer for queing frames after random no of ticks */
        if (FALSE == hObj->asyncTimerOn)
        {
            if (TRUE == hObj->handleCfg.taskCtxEnable)
            {
                clkTicks = BspOsal_getCurTimeInMsec();
                srand(clkTicks);
                timePeriod = rand();
                GT_1trace(hObj->traceMask, GT_DEBUG,
                          "Random value = %d\r\n", timePeriod);
                timePeriod %= 200;
                hObj->asyncTimerValue = timePeriod;
            }
            Clock_setTimeout(hObj->asyncClkHandle, hObj->asyncTimerValue);
            Clock_start(hObj->asyncClkHandle);
            hObj->asyncTimerOn = TRUE;
        }
    }

    return (retVal);
}

/**
 *  st_vpeCbFxn
 *  Driver callback function.
 */
static Int32 st_vpeCbFxn(Fvid2_Handle handle, Ptr appData, Ptr reserved)
{
    Int32            retVal = FVID2_SOK;
    UInt32           elaspedTime, curTime;
    st_VpeHandleObj *hObj = (st_VpeHandleObj *) appData;

    curTime     = BspOsal_getCurTimeInMsec();
    elaspedTime = curTime - hObj->lastCbTime;
    if (hObj->lastCbTime != 0u)
    {
        hObj->totalCbTime += elaspedTime;
        hObj->totalCbCount++;
        if (elaspedTime > hObj->maxCbTime)
        {
            hObj->maxCbTime = elaspedTime;
        }
        if (elaspedTime < hObj->minCbTime)
        {
            hObj->minCbTime = elaspedTime;
        }
    }
    hObj->lastCbTime = curTime;

    if (TRUE == hObj->handleCfg.taskCtxEnable)
    {
        /* Buffer ready to dequeue. Signal it */
        Semaphore_post(hObj->reqCompleteSem);
    }
    else
    {
        /* Process frames from ISR context */
        retVal = st_vpeProcessFrames(hObj);

        if (hObj->completedLoopCnt >= hObj->handleCfg.loopCnt)
        {
            Semaphore_post(hObj->reqCompleteSem);
        }
    }

    return (retVal);
}

/**
 *  st_vpeErrCbFxn
 *  Driver error callback function.
 */
static Int32 st_vpeErrCbFxn(Fvid2_Handle handle,
                            Ptr          appData,
                            Void        *errList,
                            Ptr          reserved)
{
    Int32 retVal          = FVID2_SOK;
    st_VpeHandleObj *hObj = (st_VpeHandleObj *) appData;

    GT_0trace(hObj->traceMask, GT_ERR, "Error occurred!!\r\n");

    return (retVal);
}

/**
 *  st_vpeUpdateProcList
 *  Updates the process list with the next request buffer information.
 */
static void st_vpeUpdateProcList(st_VpeHandleObj   *hObj,
                                 Fvid2_ProcessList *pList)
{
    UInt32           frmCnt, tempVar;
    UInt32           inAddrY, inAddrCbCr;
    UInt32           outAddrY, outAddrCbCr;
    Fvid2_Frame     *frm;
    Fvid2_FrameList *inFrmList;
    Fvid2_FrameList *outFrmList = NULL;
    st_VpeChObj     *chObj;

    inFrmList  = pList->inFrameList[0u];
    outFrmList = pList->outFrameList[0u];

    for (frmCnt = 0u; frmCnt < hObj->numCh; frmCnt++)
    {
        chObj = &hObj->chObj[frmCnt];
        if (chObj->inBufInfo->bufCfg.numBuffers == chObj->inBufIdx)
        {
            chObj->inBufIdx = 0u;
        }

        /* Use different output buffer for each channel */
        if (chObj->numOutBuffers == chObj->outBufIdx)
        {
            chObj->outBufIdx = 0u;
        }
        inAddrY    = (UInt32) chObj->inBufInfo->yBufAddrEven[chObj->inBufIdx];
        inAddrCbCr = (UInt32) chObj->inBufInfo->cBufAddrEven[chObj->inBufIdx];

        /* Update the VPE In list */
        frm = inFrmList->frames[frmCnt];
        /* Check if given frame was held back by driver, if so get the space
         * for frame description from context frames space */
        if (frm == NULL)
        {
            if (chObj->deiBypassFlag == TRUE)
            {
                GT_2trace(hObj->traceMask, GT_ERR,
                          "%s: Frames not returned in bypass@ line %d\r\n",
                          __FUNCTION__, __LINE__);
            }

            tempVar = chObj->freeCntxFrameIndex;
            if (tempVar < VPE_NO_OF_BUF_REQ_BEFORE_RES)
            {
                frm = &(chObj->cntxFrames[tempVar]);
                chObj->freeCntxFrameIndex++;
            }
            else
            {
                GT_2trace(hObj->traceMask, GT_ERR,
                          "%s: Error Out of context buf@ line %d\r\n",
                          __FUNCTION__, __LINE__);
                break;
            }
            inFrmList->frames[frmCnt] = frm;
        }
        if (chObj->deiBypassFlag == TRUE)
        {
            frm->fid          = FVID2_FID_FRAME;
            frm->subFrameInfo = &chObj->subFrameInfoIn;
            if (Fvid2_isDataFmtSemiPlanar(hObj->chObj->chCfg.inDataFmt))
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
            if (0u == chObj->fid)
            {
                frm->fid = FVID2_FID_TOP;
            }
            else
            {
                frm->fid = FVID2_FID_BOTTOM;
            }
            if (Fvid2_isDataFmtSemiPlanar(chObj->chCfg.inDataFmt))
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

        /*
         * Update the VPE writeback Out list
         */
        /* Check whether we need to drop this frame */
        if ((TRUE == hObj->handleCfg.frmDropEnable) &&
            (((hObj->handleCfg.frmDropPattern >> (chObj->submittedFrames % 30U))
              & 0x01u) != 0u))
        {
            outAddrY    = NULL;
            outAddrCbCr = NULL;
        }
        else
        {
            outAddrY    = (UInt32) chObj->outBufY[chObj->outBufIdx];
            outAddrCbCr = (UInt32) chObj->outBufCbCr[chObj->outBufIdx];
        }
        frm               = outFrmList->frames[frmCnt];
        frm->fid          = FVID2_FID_FRAME;
        frm->subFrameInfo = &chObj->subFrameInfoOut;
        if (Fvid2_isDataFmtSemiPlanar(chObj->chCfg.outDataFmt))
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

        /* Increment the input frame index only every frameSwitchRate frames */
        chObj->submittedFrames++;
        if (0u == (chObj->submittedFrames % hObj->handleCfg.frameSwitchRate))
        {
            chObj->inBufIdx++;
        }
        chObj->outBufIdx++;
        chObj->fid = chObj->fid ^ 1u;
    }

    /* Updated the number of frames present - would have been cleared */
    inFrmList->numFrames = hObj->numCh;
    pList->numInLists    = 1u;

    return;
}

/**
 * st_vpeClkHandler
 * \brief Function to handle time-Out of asynch Q-DeQ Timer
 * \arg   arg : Argument to function of type st_VpeHandleObj
 */
static Void st_vpeClkHandler(UArg arg)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cbCnt;
    UInt32 cookie;
    Fvid2_ProcessList *pList;
    st_VpeHandleObj *hObj = (st_VpeHandleObj *) arg;

    pList = &hObj->processList;

    /* Disable Interrupts */
    cookie = Hwi_disable();

    for (cbCnt = 0u; cbCnt < hObj->asyncCbCnt; cbCnt++)
    {
        /* Update the buffer address */
        st_vpeUpdateProcList(hObj, pList);

        /* Process frames */
        retVal = Fvid2_processFrames(hObj->fvidHandle, pList);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(hObj->traceMask, GT_ERR, "Queuing failed\r\n");
        }
    }

    Clock_stop(hObj->asyncClkHandle);
    hObj->asyncTimerOn = FALSE;
    hObj->asyncCbCnt   = 0u;

    /* Enable Interrupts again */
    Hwi_restore(cookie);

    return;
}

static Int32 st_vpeSaveOutputToFile(st_VpeHandleObj *hObj)
{
    Int32        retVal = FVID2_SOK;
    UInt32       chCnt;
    UInt32       printOutWidth;
    UInt32       bytesToWrite, bytesWritten;
    UInt8       *curWrPtr;
    Char         fileStr[200u];
    Char        *fmtName;
    FILE        *fHandle;
    st_VpeChObj *chObj;

    for (chCnt = 0u; chCnt < hObj->numCh; chCnt++)
    {
        printOutWidth = 0u;
        fHandle       = NULL;
        chObj         = &hObj->chObj[chCnt];
        if (Fvid2_isDataFmtSemiPlanar(chObj->chCfg.outDataFmt))
        {
            printOutWidth = chObj->outPitchY;
        }
        else if (Fvid2_isDataFmtYuv422I(chObj->chCfg.outDataFmt))
        {
            printOutWidth = chObj->outPitchY / 2u;
        }
        else if ((FVID2_DF_RGB24_888 == chObj->chCfg.outDataFmt) ||
                 (FVID2_DF_YUV444I == chObj->chCfg.outDataFmt))
        {
            printOutWidth = chObj->outPitchY / 3u;
        }
        else
        {
            /* Other formats not supported */
            retVal = FVID2_EFAIL;
        }

        if (FVID2_DF_YUV422I_YUYV == chObj->chCfg.outDataFmt)
        {
            fmtName = "yuyv422";
        }
        else if (FVID2_DF_YUV422I_YVYU == chObj->chCfg.outDataFmt)
        {
            fmtName = "yvyu422";
        }
        else if (FVID2_DF_YUV422I_UYVY == chObj->chCfg.outDataFmt)
        {
            fmtName = "uyvy422";
        }
        else if (FVID2_DF_YUV422I_VYUY == chObj->chCfg.outDataFmt)
        {
            fmtName = "vyuy422";
        }
        else if (FVID2_DF_YUV420SP_UV == chObj->chCfg.outDataFmt)
        {
            fmtName = "nv12";
        }
        else if (FVID2_DF_YUV420SP_VU == chObj->chCfg.outDataFmt)
        {
            fmtName = "nv21";
        }
        else if (FVID2_DF_YUV422SP_UV == chObj->chCfg.outDataFmt)
        {
            fmtName = "nv16";
        }
        else if (FVID2_DF_YUV422SP_VU == chObj->chCfg.outDataFmt)
        {
            fmtName = "yuv422spvu";
        }
        else if (FVID2_DF_YUV444I == chObj->chCfg.outDataFmt)
        {
            fmtName = "yuv444";
        }
        else if (FVID2_DF_RGB24_888 == chObj->chCfg.outDataFmt)
        {
            fmtName = "rgb888";
        }
        else
        {
            fmtName = "unknownformat";
        }

        snprintf(
            fileStr, sizeof (fileStr),
#if defined(__GNUC__) && !defined(__ti__)
            "%s\\vpeUtTC%4dCh%d_%s_prog_packed_%d_%d.tigf",
#else
            "%s\\vpeUtTC%0.4dCh%d_%s_prog_packed_%d_%d.tigf",
#endif
            hObj->sysCtrl->filePath, (unsigned int)  hObj->testPrms->testCaseId,
            (unsigned int) (hObj->startChIdx + chObj->chId), fmtName,
            (unsigned int) printOutWidth, (unsigned int) chObj->chCfg.outHeight);

        if (FVID2_SOK == retVal)
        {
            GT_2trace(hObj->traceMask, GT_INFO,
                "%s: Writing output to file: %s...\r\n", APP_NAME, fileStr);
            /* Open File */
            fHandle = fopen(fileStr, "wb");
            if (NULL == fHandle)
            {
                GT_1trace(hObj->traceMask, GT_ERR,
                          "File open failed: %s\r\n", fileStr);
                retVal = FVID2_EFAIL;
            }
            else
            {
                bytesWritten = 0u;
                curWrPtr     = chObj->outSaveBuf;
                while (bytesWritten < chObj->outSaveBufSize)
                {
                    bytesToWrite = 4 * 1024u;
                    if ((chObj->outSaveBufSize - bytesWritten) < bytesToWrite)
                    {
                        bytesToWrite = chObj->outSaveBufSize - bytesWritten;
                    }

                    if (fwrite(curWrPtr, 1, bytesToWrite, fHandle) <
                        bytesToWrite)
                    {
                        GT_0trace(hObj->traceMask, GT_ERR,
                                  "File write failed\r\n");
                        retVal = FVID2_EFAIL;
                        break;
                    }
                    curWrPtr     += bytesToWrite;
                    bytesWritten += bytesToWrite;
                }
            }

            if (NULL != fHandle)
            {
                fclose(fHandle);
                fHandle = NULL;
            }
            GT_1trace(hObj->traceMask, GT_INFO,
                      "%s: File write complete!!\r\n", APP_NAME);
        }

        if (FVID2_SOK != retVal)
        {
            break;
        }
    }

    return (retVal);
}

