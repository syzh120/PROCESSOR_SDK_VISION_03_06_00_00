/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bsputils_fileio.c
 *
 *  \brief This file implements helper functions for accessing the sd card.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/csl/soc.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_API.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_edma.h>
#include <ti/sdo/edma3/drv/src/edma3.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#endif
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  None
 */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    BspOsal_SemHandle edmaDone;
    EDMA3_DRV_Handle  hEdma;
    Bool              sdInitDone;
    Bool              sdCardNotPresent;
} SdFileSys_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void HSMMCSDEdmaCallback(uint32_t tcc, EDMA3_RM_TccStatus status,
                                void *appData);
static EDMA3_DRV_Result HSMMCSDEdmaAllocCh(const hsmmcsdEdmaParam_t *pEdmaParam);
static EDMA3_DRV_Result HSMMCSDEdmaTrigger(const hsmmcsdEdmaParam_t *pEdmaParam,
                                           EDMA3_DRV_TrigMode        mode);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SdFileSys_Obj gSdFileSysObj = {0};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 BspUtils_initFileio(void *hEdma)
{
    Int32 retVal = BSP_SOK;
    if (gSdFileSysObj.sdInitDone == FALSE)
    {
        if (hEdma == NULL)
        {
            retVal = BSP_EFAIL;
        }
        if (retVal == BSP_SOK)
        {
            BspUtils_memset((Ptr) & gSdFileSysObj, 0, sizeof (gSdFileSysObj));
            gSdFileSysObj.hEdma    = (EDMA3_DRV_Handle) hEdma;
            gSdFileSysObj.edmaDone = BspOsal_semCreate((Int32) 0,
                                                       (Bool) TRUE);
            gSdFileSysObj.sdCardNotPresent = FALSE;
        }
        gSdFileSysObj.sdInitDone = TRUE;
    }
    return BSP_SOK;
}

Int32 BspUtils_deinitFileio(void)
{
    if (gSdFileSysObj.sdInitDone == TRUE)
    {
        BspOsal_semDelete(&gSdFileSysObj.edmaDone);
        gSdFileSysObj.sdInitDone = FALSE;
        BspUtils_memset((Ptr) & gSdFileSysObj, 0, sizeof (gSdFileSysObj));
    }
    return BSP_SOK;
}

Int32 BspUtils_appLoadFileFromSd(const Char *fileName,
                                 const Char *dirName,
                                 void       *bufAddr,
                                 UInt32      bufSize,
                                 UInt32     *bytesRead)
{
    FIL     fp;
    FRESULT fresult = FR_OK;
    Int32   retVal  = BSP_SOK;
    UInt32  startTime, endTime;

    if ((gSdFileSysObj.sdInitDone != TRUE) ||
        (gSdFileSysObj.sdCardNotPresent == TRUE))
    {
        fresult = FR_NOT_READY;
    }

    if (fresult == FR_OK)
    {
        if (dirName != NULL)
        {
            fresult = f_chdir(dirName);
            if (fresult != FR_OK)
            {
                if ((fresult == FR_NOT_READY) || (fresult == FR_DISK_ERR))
                {
                    gSdFileSysObj.sdCardNotPresent = TRUE;
                }
                else
                {
                    GT_1trace(BspAppTrace, GT_INFO,
                              "FatFs: CD to dir %s failed \r\n", dirName);
                }
            }
        }
        else
        {
            /* Dir name is NULL. Change dir to root dir */
            fresult = f_chdir("/");
            if (fresult != FR_OK)
            {
                if ((fresult == FR_NOT_READY) || (fresult == FR_DISK_ERR))
                {
                    gSdFileSysObj.sdCardNotPresent = TRUE;
                }
                else
                {
                    GT_0trace(BspAppTrace, GT_INFO,
                              "FatFs: CD to root dir failed \r\n");
                }
            }
        }
    }

    if (fresult == FR_OK)
    {
        fresult = f_open(&fp, fileName, (BYTE) FA_READ);
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG,
                      "File open error \r\n");
        }
        else
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      "Loading File %s from SD Card...\r\n", fileName);
            startTime = BspOsal_getCurTimeInMsec();
            fresult   = f_read(&fp, bufAddr, bufSize, (UINT *)bytesRead);
            endTime   = BspOsal_getCurTimeInMsec();
            if (fresult != FR_OK)
            {
                GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File read failed \r\n");
            }
            f_close(&fp);
            GT_2trace(BspAppTrace, GT_INFO,
                      "File Size: %d bytes, Time Taken: %d ms!!\r\n",
                      *bytesRead, (endTime - startTime));
        }
    }

    if (fresult == FR_OK)
    {
        retVal = BSP_SOK;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

Int32 BspUtils_appSaveFileToSd(const Char *fileName,
                               const Char *dirName,
                               const void *bufAddr,
                               UInt32      bufSize,
                               UInt32     *bytesWritten)
{
    FIL     fp;
    FRESULT fresult = FR_OK;
    Int32   retVal  = BSP_SOK;
    UInt32  startTime, endTime;

    if ((gSdFileSysObj.sdInitDone != TRUE) ||
        (gSdFileSysObj.sdCardNotPresent == TRUE))
    {
        fresult = FR_NOT_READY;
    }

    if (fresult == FR_OK)
    {
        if (dirName != NULL)
        {
            fresult = f_chdir(dirName);
            if ((fresult == FR_NOT_READY) || (fresult == FR_DISK_ERR))
            {
                gSdFileSysObj.sdCardNotPresent = TRUE;
            }
            else
            {
                if (fresult == FR_NO_PATH)
                {
                    fresult = f_mkdir(dirName);
                    if (fresult == FR_OK)
                    {
                        fresult = f_chdir(dirName);
                    }
                }
                if (fresult != FR_OK)
                {
                    GT_1trace(BspAppTrace, GT_INFO,
                              "FatFs: CD to dir %s failed \r\n", dirName);
                }
            }
        }
        else
        {
            /* Dir name is NULL. Change dir to root dir */
            fresult = f_chdir("/");
            if (fresult != FR_OK)
            {
                if ((fresult == FR_NOT_READY) || (fresult == FR_DISK_ERR))
                {
                    gSdFileSysObj.sdCardNotPresent = TRUE;
                }
                else
                {
                    GT_0trace(BspAppTrace, GT_INFO,
                              "FatFs: CD to root dir failed \r\n");
                }
            }
        }
    }

    if (fresult == FR_OK)
    {
        fresult = f_open(&fp, fileName, (BYTE) FA_WRITE);
    }
    if (fresult == FR_OK)
    {
        f_close(&fp);
        GT_0trace(BspAppTrace, GT_DEBUG,
                  "File already exists on SD card. Delete it.\r\n");
        fresult = f_unlink(fileName);
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File delete failed \r\n");
        }
    }
    if ((fresult == FR_OK) || (fresult == FR_NO_FILE))
    {
        fresult = f_open(&fp, fileName, (BYTE) FA_CREATE_NEW);
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File create failed \r\n");
        }
        else
        {
            f_close(&fp);
            /*Open handle to the newly created file*/
            fresult = f_open(&fp, fileName, (BYTE) FA_WRITE);
        }
    }
    if (fresult == FR_OK)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "Saving buffer at address 0x%.8x to file %s in Sd Card \r\n",
                  bufAddr, fileName);
        startTime = BspOsal_getCurTimeInMsec();
        fresult   = f_write(&fp, bufAddr, bufSize, (UINT *)bytesWritten);
        endTime   = BspOsal_getCurTimeInMsec();
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File write failed \r\n");
        }
        f_close(&fp);
        GT_2trace(BspAppTrace, GT_INFO,
                  "File Size %d, Time taken to write is %d ms \r\n",
                  *bytesWritten, (endTime - startTime));
    }

    if (fresult == FR_OK)
    {
        retVal = BSP_SOK;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

static void HSMMCSDEdmaCallback(uint32_t tcc, EDMA3_RM_TccStatus status,
                                void *appData)
{
    BspOsal_semPost(gSdFileSysObj.edmaDone);
}

static EDMA3_DRV_Result HSMMCSDEdmaAllocCh(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result     edma3Result = EDMA3_DRV_SOK;
    EDMA3_RM_TccCallback tccCb;
    UInt32 edmaChId, tccId;

    tccId    = pEdmaParam->chan;
    edmaChId = pEdmaParam->chan;

    /* MISRA.CAST.FUNC_PTR:MISRAC_2004 Rule_11.1
     * MISRAC_WAIVER:
     * Typecasting callback function to EDMA callback function */
    tccCb = (EDMA3_RM_TccCallback) & HSMMCSDEdmaCallback;

    edma3Result = EDMA3_DRV_requestChannel(
        gSdFileSysObj.hEdma,
        (uint32_t *) &edmaChId,
        (uint32_t *) &tccId,
        (EDMA3_RM_EventQueue) 0,
        tccCb, (void *) edmaChId);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
    {
        /* DMA XBar instance number is (channel number +1) in this case.
         * This might be different in other cases. Please refer TRM.
         */
        DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       EDMA, pEdmaParam->chan + 1U,
                       (xbar_evt_t) (pEdmaParam->dreq + 1U));
    }
#endif

    return edma3Result;
}

static EDMA3_DRV_Result HSMMCSDEdmaTrigger(const hsmmcsdEdmaParam_t *pEdmaParam,
                                           EDMA3_DRV_TrigMode        mode)
{
    EDMA3_DRV_Result edma3Result;
    uint16_t         tccStatus;

    edma3Result = EDMA3_DRV_checkAndClearTcc(gSdFileSysObj.hEdma,
                                             pEdmaParam->chan,
                                             &tccStatus);
    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = EDMA3_DRV_clearErrorBits(gSdFileSysObj.hEdma,
                                               pEdmaParam->chan);

        if (EDMA3_DRV_SOK == edma3Result)
        {
            /* clear pending status, if any */
            BspOsal_semWait(gSdFileSysObj.edmaDone, BSP_OSAL_NO_WAIT);

            edma3Result = EDMA3_DRV_enableTransfer(
                gSdFileSysObj.hEdma,
                pEdmaParam->chan,
                mode);
        }
    }

    return edma3Result;
}

uint32_t HSMMCSDEdmaCopy(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result    edma3Result;
    EDMA3_DRV_PaRAMRegs edmaParam;

    HSMMCSDEdmaAllocCh(pEdmaParam);

    edmaParam.srcAddr  = pEdmaParam->srcBfr;
    edmaParam.destAddr = pEdmaParam->dstBfr;
    edmaParam.aCnt     = pEdmaParam->length;
    edmaParam.bCnt     = 1;
    edmaParam.cCnt     = 1;
    edmaParam.linkAddr = 0xFFFF;
    edmaParam.opt      =
        ((pEdmaParam->chan << EDMA3_CCRL_OPT_TCC_SHIFT)
         & EDMA3_CCRL_OPT_TCC_MASK
        )
        | ((UInt32) EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
        | ((UInt32) EDMA3_CCRL_OPT_TCINTEN_ENABLE
           << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
    ;

    edma3Result = EDMA3_DRV_setPaRAM(
        gSdFileSysObj.hEdma,
        pEdmaParam->chan,
        &edmaParam
        );
    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = HSMMCSDEdmaTrigger(pEdmaParam, EDMA3_DRV_TRIG_MODE_MANUAL);
        if (EDMA3_DRV_SOK == edma3Result)
        {
            HSMMCSDEdmaWaitTransfer(pEdmaParam->chan);
        }
    }

    HSMMCSDEdmaClose(pEdmaParam);

    return 1U;
}

uint32_t HSMMCSDEdmaTransfer(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result    edma3Result;
    EDMA3_DRV_PaRAMRegs edmaParam;
    uint32_t aCntValue, bCntValue, cCntValue;

    HSMMCSDEdmaAllocCh(pEdmaParam);

    /*calculate the aCnt, bCnt & cCnt values for AB-SYNC mode*/
    if (pEdmaParam->length < pEdmaParam->blockSize)
    {
        aCntValue = 4U;
        bCntValue = pEdmaParam->length / 4U;
        cCntValue = 1U;
    }
    else
    {
        aCntValue = 4U;
        bCntValue = pEdmaParam->blockSize / 4U;
        cCntValue = pEdmaParam->length / pEdmaParam->blockSize;
    }

    /* Program the PaRam set*/
    edmaParam.srcAddr  = pEdmaParam->srcBfr;
    edmaParam.destAddr = pEdmaParam->dstBfr;
    edmaParam.aCnt     = aCntValue;
    edmaParam.bCnt     = bCntValue;
    edmaParam.cCnt     = cCntValue;
    if (pEdmaParam->rwflag == FLAG_READ)
    {
        edmaParam.srcBIdx  = 0;
        edmaParam.destBIdx = 4;
        edmaParam.srcCIdx  = 0;
        edmaParam.destCIdx = aCntValue * bCntValue;
    }
    else
    {
        edmaParam.srcBIdx  = 4;
        edmaParam.destBIdx = 0;
        edmaParam.srcCIdx  = aCntValue * bCntValue;
        edmaParam.destCIdx = 0;
    }
    edmaParam.bCntReload = bCntValue;
    edmaParam.linkAddr   = 0xFFFF;
    edmaParam.opt        =
        ((pEdmaParam->chan << EDMA3_CCRL_OPT_TCC_SHIFT)
         & EDMA3_CCRL_OPT_TCC_MASK
        )
        | ((UInt32) EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT)
        | ((UInt32) EDMA3_CCRL_OPT_TCINTEN_ENABLE
           << EDMA3_CCRL_OPT_TCINTEN_SHIFT)
    ;

    edma3Result = EDMA3_DRV_setPaRAM(
        gSdFileSysObj.hEdma,
        pEdmaParam->chan,
        &edmaParam
        );
    if (EDMA3_DRV_SOK == edma3Result)
    {
        edma3Result = HSMMCSDEdmaTrigger(pEdmaParam, EDMA3_DRV_TRIG_MODE_EVENT);
    }

    return 1U;
}

uint32_t HSMMCSDEdmaClose(const hsmmcsdEdmaParam_t *pEdmaParam)
{
    EDMA3_DRV_Result edma3Result;
    uint16_t         tccStatus;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)

    /* Disconnect the event source & channel map */
    DMAXBARDisconnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                      pEdmaParam->chan + 1U);
#endif

    EDMA3_DRV_checkAndClearTcc(
        gSdFileSysObj.hEdma,
        pEdmaParam->chan,
        &tccStatus);
    EDMA3_DRV_clearErrorBits(
        gSdFileSysObj.hEdma,
        pEdmaParam->chan
        );

    edma3Result = EDMA3_DRV_freeChannel(
        gSdFileSysObj.hEdma,
        pEdmaParam->chan
        );
    GT_assert(BspAppTrace, (edma3Result == EDMA3_DRV_SOK));

    return 1U;
}

void HSMMCSDEdmaWaitTransfer(uint32_t edmaChan)
{
    BspOsal_semWait(gSdFileSysObj.edmaDone, BSP_OSAL_WAIT_FOREVER);
}

void HSMMCSDUartPuts(const char *string)
{
    #ifdef UTILS_FILE_API_DEBUG
    printf(string);
    #endif
}

void HSMMCSDUARTPutNum(int32_t value)
{
    #ifdef UTILS_FILE_API_DEBUG
    printf("%d", value);
    #endif
}

