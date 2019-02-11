/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *
 */

/**
 *  \file     sbl_test_auto.c
 *
 *  \brief   This file contains functions which is used to load the multi-core
 *           application image file and stores the test result of application
 *           image file
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_API.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/boot/sbl_auto/sbl_app/src/test_auto/sbl_test_auto.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>

#if defined (SOC_TDA3XX)
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_tda3xx.h>
#include <ti/csl/cslr_rti.h>
#include <ti/csl/csl_rti.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/cslr_mmu.h>
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_wd_timer.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Macro to configure buffer size for 64 bit integer */
#define SBL_INT_DIGITS                         (19U)

#define TEST_ID_BUFFER_SIZE                    (4U)
#define LINE_BUFFER_SIZE                       (200U)

#if defined (SOC_TDA3XX)
/* DRM_BASE_SUSPEND_CTRL20 base address for RTI Suspend line  */
#define SOC_I_DRM_BASE_SUSPEND_CTRL20          (0x250U)

/* Suspend lines for RTI module : 1
 * As it is not mapped to any core, so suspend line status is independent of
 * core status
 */
#define SBL_RTI_SUSPEND_LINE_CORE_IPU_C1       (0x00000011U)

/* RTI_4 module base address*/
#define SBL_RTI_MODULE                         (SOC_RTI4_BASE)

/* RTI : Frequency of 32K clock Source*/
#define SBL_RTI_CLOCK_SOURCE_32KHZ_FREQ_KHz    (32U)

/* To select clock frequency of 32KHz for RTI module clock source*/
#define SBL_RTI_CLOCK_SOURCE_32KHZ \
    (CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_XREF_CLK)
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/*MPU System interrupt number for WDT*/
#define SBL_WD_TIMER_DELAY_INT    (uint16_t) (80)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* Room for SBL_INT_DIGITS digits, - and '\0' */
char gBuf[SBL_INT_DIGITS + 2U];

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief This structure defines Starterware App Testcase Parameters
 */
typedef struct sblAppTestCaseParams
{
    char     appImageFile[200];
    /**< STW AppImage file name */
    uint32_t wdgTimeout;
    /**< WDG Timeout Value */
    uint32_t checkTestStatus;
    /**< Flag to enable/disable check test result status  */
    uint32_t boardType;
    /**< Board Type*/
} sblAppTestCaseParams_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function is used to parse the STW App list file and then
 *          updates the starterware test case parameter structure  based on
 *          testcase Info file. It will print the STW test result summary on
 *          UART console at the end of test
 *
 * \param   appInfoFile    STW App Info file name
 * \param   appResultFile  STW App Test Result file name
 * \param   appListFile    STW AppImage List file name
 * \param   appTcPrms      Starterware Application Image Test case Parameters.
 *                         Refer struct #sblAppTestCaseParams_t for
 *                         details.
 *
 * \return  retVal       STW_SOK   : Success If no error has occured
 *                       STW_EFAIL : Failure If error has occured
 */
static int32_t SblGetAppInfo(const char             *appInfoFile,
                             char                   *appResultFile,
                             char                   *appListFile,
                             sblAppTestCaseParams_t *appTcPrms);

/**
 * \brief   This function is used to update the STW test result status in result
 *          file in SD card and then updates the next testcase info in STW
 *          testcase info file which is to be tested then will do cold reset
 *
 * \param   appInfoFile    STW App Info file name
 * \param   appResultFile  STW App Test Result file name
 * \param   appListFile    STW AppImage List file name
 *
 * \return  retVal       STW_SOK   : Success If no error has occured
 *                       STW_EFAIL : Failure If error has occured
 */
static int32_t SblUpdateTestAppResult(char *appInfoFile,
                                      char *appResultFile,
                                      char *appListFile);
/**
 * \brief   This function converts integer value to string
 *
 * \param   integerVal    Value of Integer
 *
 * \return  Returns the string value of the corresponding integer value
 */
static char *SblIntToStrConv(int32_t integerVal);

/**
 * \brief   This function converts string to integer value
 *
 * \param   str    Represents a string
 *
 * \return  Returns the integer value of the corresponding string  value
 */
static int32_t SblStrToIntConv(const char *str);

/**
 * \brief   This function updates test result status
 *
 * \param   appResultFile   STW App Test Result file name
 * \param   appListFile     STW AppImage List file name
 * \param   stwTestno       STW test case number which is defined in appListFile
 *
 * \return  retVal      STW_SOK   : Success If test result status is updated
 *                      STW_EFAIL : Failure If test result status is not updated
 */
static int32_t SblUpdateAppTestResult(const char   *appResultFile,
                                      char         *appListFile,
                                      int32_t       stwTestno);

/**
 * \brief   This function parse appList file to retrieve test case parameters
 *
 * \param   appResultFile   STW App Test Result file name
 * \param   tcPrms          STW App Image Test case Parameters.
 *                          Refer struct #sblAppTestCaseParams_t for details.
 * \param   validTc         Whether the tcNum is valid or not
 * \param   tcNum           STW test case number which is defined in appListFile
 *
 * \return  Returns whether testcase is valid or not then if testcase is valid
 *          updates the test case parameters
 */
static void SblGetAppTestCaseParams(const char             *appListFile,
                                    sblAppTestCaseParams_t *tcPrms,
                                    uint32_t               *validTc,
                                    uint32_t                tcNum);

/**
 * \brief   This function prints test result on UART console at the end of test
 *
 * \param   appResultFile   STW App Test Result file name
 *
 * \return  None
 */
static void SblAppPrintTestResult(char *appResultFile);

#if defined (SOC_TDA3XX)
/**
 * \brief   This function configure RTIto generate Reset based on STW AppImage
 *          WDG timeout defined in AppList file and then disables Unicache
 *
 * \return  None
 */
static void SblRTIConfig(void);
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/**
 * \brief   This function configure WDT to generate Reset based on STW AppImage
 *          WDG timeout defined in AppList file
 *
 * \return  None
 */
static void SblWdtimerConfig(void);

extern int32_t SblUtilsDummyDDRRead(void       *dstAddr,
                                    const void *srcAddr,
                                    uint32_t    length);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* Global variable used to store WDG timeOut Value */
uint32_t   gWdgTimeout;

/* Global variable for referencing the App Image File Pointer */
extern FIL gAppImageSDFilePtr;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t SBLLoadTestAutoAppImage(sbllibAppImageParseParams_t *imageParams,
                                uint32_t                     resetStatus)
{
    int32_t                retVal = STW_EFAIL;
    FRESULT                fresult;
    MMC_INST_t             num;
    stwAppInitParams_t     stwAppInitParamsVal;
    char stwAppInfoFile[50]   = "CurTC.txt";
    char stwAppResultFile[50] = "Result.txt";
    char stwAppListFile[50]   = "applist.txt";
    sblAppTestCaseParams_t tcPrms;

    stwAppInitParamsVal.isI2cInitReq       = TRUE;
    stwAppInitParamsVal.isUartInitReq      = FALSE;
    stwAppInitParamsVal.enablePrintEvmInfo = (uint32_t) FALSE;

    retVal = StwUtils_appDefaultInit(stwAppInitParamsVal);
    if (STW_SOK != retVal)
    {
        UARTprintf("\nSystem Init Failed while configuring MMC \n");
    }

#if defined (SOC_TDA3XX)
    num = MMC4_INST;
#else
    num = MMC1_INST;
#endif

#if defined (SOC_TDA3XX)
    /*IOExpander mux config : Mux F : MMC4*/
    BOARDSelectDevice(DEVICE_ID_MMC, DEVICE_MMC_INST_ID_4);
#endif

    if (0 != HSMMCSDInit(num))
    {
        UARTprintf("\n No valid SD card \n");
        retVal = STW_EFAIL;
    }
    else
    {
        if (resetStatus == 1U)
        {
            retVal = SblUpdateTestAppResult(stwAppInfoFile,
                                            stwAppResultFile,
                                            stwAppListFile);
        }
        else
        {
            retVal = SblGetAppInfo(stwAppInfoFile,
                                   stwAppResultFile,
                                   stwAppListFile,
                                   &tcPrms);

            fresult = f_open(&gAppImageSDFilePtr, tcPrms.appImageFile,
                             (BYTE) FA_READ);
            if (FR_OK != fresult)
            {
                UARTprintf("\n AppImage File open fails \n");
                StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_AINF);
                retVal = STW_EFAIL;
            }
            else
            {
#if defined (SOC_TDA3XX)
                SBLLibRegisterImageCopyCallback(&SBLUtilsSDFileRead,
                                                &SBLUtilsDDRReadEdma,
                                                &SBLUtilsSDFileSeek);
                imageParams->appImageOffset = 0U;
                retVal = SBLLibMultiCoreImageParseV2(imageParams);
#else
                SBLLibRegisterImageCopyCallback(&SBLUtilsSDFileRead,
                                                &SBLUtilsDDRReadEdma,
                                                &SBLUtilsSDFileSeek);
                imageParams->appImageOffset = 0U;
                retVal = SBLLibMultiCoreImageParseV1(imageParams);
#endif
                f_close(&gAppImageSDFilePtr);
                UARTprintf(
                    "\n====================================================================");
                UARTprintf("\n\nSBL Test Automation: App Started: ");
                UARTprintf("%s ", tcPrms.appImageFile);
                UARTprintf("(TimeOut: ");
                UARTprintf("%dSecs)\n", gWdgTimeout);
                /* For STW Test Automation, Initially Test result is logged as
                 * Started,
                 * Based on test status will update the status as Pass / Fail
                 */
                StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_INIT);
            }
        }
    }
    return retVal;
}

static int32_t SblGetAppInfo(const char             *appInfoFile,
                             char                   *appResultFile,
                             char                   *appListFile,
                             sblAppTestCaseParams_t *appTcPrms)
{
    int32_t  retVal       = STW_SOK;
    TCHAR    stwTestId[TEST_ID_BUFFER_SIZE] = "\0";
    TCHAR    *stwTestIdPtr;
    uint8_t  numBytes     = 2U;
    UINT     bytesWritten = 0U;
    int32_t  stwTestno;
    FRESULT  fresult;
    FIL      stwAppInfoFilePtr, stwAppResultFilePtr;
    uint32_t validStwAppTc;

    stwTestIdPtr = stwTestId;

    /* To check whether Test case file is existing or not */
    fresult = f_open(&stwAppInfoFilePtr, appInfoFile, (BYTE) FA_READ);

    /* File does not exist . So create a new file*/
    if (fresult == FR_NO_FILE)
    {
        fresult = f_open(&stwAppInfoFilePtr,
                         appInfoFile,
                         (BYTE) ((uint32_t)FA_CREATE_NEW | (uint32_t)FA_WRITE));

        if (fresult != FR_OK)
        {
            UARTprintf("\n App TestCase Info File Create fails \n");
            retVal = STW_EFAIL;
        }

        if (retVal == STW_SOK)
        {
            /* Prints EVM Info */
            StwUtils_appPrintInfo();

            stwTestId[0] = (char) '1';
            stwTestId[1] = (char) 0;
            numBytes     = 2U;

            fresult = f_write(&stwAppInfoFilePtr,
                              (void *) stwTestIdPtr,
                              (UINT) numBytes,
                              (UINT *) &bytesWritten);

            if ((fresult != FR_OK) || (numBytes != bytesWritten))
            {
                fresult = FR_INVALID_DRIVE;
                UARTprintf("\n App TestCase Info file write  fails\n");
                retVal = STW_EFAIL;
            }
            f_close(&stwAppInfoFilePtr);

            /* To check whether Result file is existing or not */
            fresult = f_open(&stwAppResultFilePtr, appResultFile, (BYTE) FA_READ);

            /* Result File exists then delete the Result file during Init
             * phase*/
            if (fresult == FR_OK)
            {
                f_close(&stwAppResultFilePtr);
                f_unlink(appResultFile);
            }

            fresult = f_open(&stwAppInfoFilePtr, appInfoFile, (BYTE) FA_READ);
            if (fresult != FR_OK)
            {
                UARTprintf("\n App TestCase Info File Read fails \n");
                retVal = STW_EFAIL;
            }
        }
    }
    if (retVal == STW_SOK)
    {
        if (NULL ==
            f_gets(stwTestIdPtr, ((int32_t)TEST_ID_BUFFER_SIZE * (int32_t)sizeof(TCHAR)),
                   &stwAppInfoFilePtr))
        {
            fresult = FR_INVALID_DRIVE;
            UARTprintf("\n App TestCase Info File read  fails\n");
            retVal = STW_EFAIL;
        }
    }
    if (retVal == STW_SOK)
    {
        f_close(&stwAppInfoFilePtr);

        /* Open the testcase */
        stwTestno = SblStrToIntConv(stwTestIdPtr);
        SblGetAppTestCaseParams(appListFile,
                                appTcPrms,
                                &validStwAppTc,
                                (uint32_t)stwTestno);
        if (validStwAppTc == 0)
        {
            UARTprintf("\n");
            UARTprintf(
                "\n-----------------------------------------------------------------");
            UARTprintf("\nTest Result Summary");
            UARTprintf(
                "\n-----------------------------------------------------------------\n");
            f_unlink(appInfoFile);
            SblAppPrintTestResult(appResultFile);
            UARTprintf(
                "-----------------------------------------------------------------");
            while (1)
            {
                /* Nothing to do here. */
            }
        }
        gWdgTimeout = appTcPrms->wdgTimeout;
    }

    return retVal;
}

static int32_t SblUpdateAppTestResult(const char   *appResultFile,
                                      char         *appListFile,
                                      int32_t       stwTestno)
{
    int32_t  retVal         = STW_SOK;
    uint8_t  numBytes       = 2U;
    UINT     bytesWritten   = 0U;
    char     stwTestId[4]   = "\0";
    char     data_read[512] = {0};
    char    *stwTestIdPtr;
    char    *destbfr;
    uint32_t testResult, validStwAppTc;
    FRESULT  fresult;
    FIL      stwAppResultFilePtr;
    sblAppTestCaseParams_t tcPrms;

    stwTestIdPtr = stwTestId;

    /* To check whether Result file is existing or not */
    fresult = f_open(&stwAppResultFilePtr, appResultFile, (BYTE) FA_WRITE);

    /* File does not exist . So create a new file*/
    if (fresult == FR_NO_FILE)
    {
        fresult = f_open(&stwAppResultFilePtr,
                         appResultFile,
                         (BYTE) ((uint32_t)FA_CREATE_NEW | (uint32_t)FA_WRITE));
        if (fresult != FR_OK)
        {
            UARTprintf("\n App Test Result File Create fails \n");
            retVal = STW_EFAIL;
        }
    }

    if (retVal == STW_SOK)
    {
        f_lseek(&stwAppResultFilePtr, stwAppResultFilePtr.fsize);

        testResult = StwUtils_appCheckTestResult();

        SblGetAppTestCaseParams(appListFile,
                                &tcPrms,
                                &validStwAppTc,
                                (uint32_t)stwTestno);

        stwTestIdPtr = SblIntToStrConv(stwTestno);

        /* Print the result in a string*/
        UARTprintf("\n\nSBL Test Automation: App Completed: ");
        UARTprintf("%s: ", tcPrms.appImageFile);

        destbfr = (char *) (data_read);
        strcpy(destbfr, stwTestIdPtr);
        numBytes = (uint8_t) strlen(destbfr);
        fresult  = f_write(&stwAppResultFilePtr,
                           (void *) destbfr,
                           (UINT) numBytes,
                           (UINT *) &bytesWritten);
        if ((fresult != FR_OK) || (numBytes != bytesWritten))
        {
            fresult = FR_INVALID_DRIVE;
            UARTprintf("\n App Test Result file write  fails\n");
            retVal = STW_EFAIL;
        }
    }

    if (retVal == STW_SOK)
    {
        strcpy(destbfr, ":");
        numBytes = (uint8_t) strlen(destbfr);
        fresult  = f_write(&stwAppResultFilePtr,
                           (void *) destbfr,
                           (UINT) numBytes,
                           (UINT *) &bytesWritten);
        if ((fresult != FR_OK) || (numBytes != bytesWritten))
        {
            fresult = FR_INVALID_DRIVE;
            UARTprintf("\n App Test Result file write  fails\n");
            retVal = STW_EFAIL;
        }
    }

    if (retVal == STW_SOK)
    {
        strcpy(destbfr, tcPrms.appImageFile);
        numBytes = (uint8_t) strlen(destbfr);
        fresult  = f_write(&stwAppResultFilePtr,
                           (void *) destbfr,
                           (UINT) numBytes,
                           (UINT *) &bytesWritten);
        if ((fresult != FR_OK) || (numBytes != bytesWritten))
        {
            fresult = FR_INVALID_DRIVE;
            UARTprintf("\n App Test Result file write  fails\n");
            retVal = STW_EFAIL;
        }
    }

    if (retVal == STW_SOK)
    {
        if (tcPrms.checkTestStatus == 1)
        {
            if (testResult == STWUTILS_APP_TST_STATUS_PASS)
            {
                strcpy(destbfr, ":Pass:\n");
                UARTprintf("Test Passed");
            }
            else if (testResult == STWUTILS_APP_TST_STATUS_FAIL)
            {
                strcpy(destbfr, ":Fail:\n");
                UARTprintf("Test Failed");
            }
            else if (testResult == STWUTILS_APP_TST_STATUS_INIT)
            {
                strcpy(destbfr, ":Hung:\n");
                UARTprintf("Test Hung");
            }
            else if (testResult == STWUTILS_APP_TST_STATUS_AINF)
            {
                strcpy(destbfr, ":AppImage Not Found:\n");
                UARTprintf("AppImage Not Found");
            }
            else
            {
                /* Nothing to do here */
            }
        }
        else
        {
            strcpy(destbfr, ":Result Ignored:\n");
            UARTprintf("Test Result Ignored");
        }

        numBytes = (uint8_t) strlen(destbfr);
        fresult  = f_write(&stwAppResultFilePtr,
                           (void *) destbfr,
                           (UINT) numBytes,
                           (UINT *) &bytesWritten);
        if ((fresult != FR_OK) || (numBytes != bytesWritten))
        {
            fresult = FR_INVALID_DRIVE;
            UARTprintf("\n App Test Result file write  fails\n");
            retVal = STW_EFAIL;
        }
    }

    if (retVal == STW_SOK)
    {
        f_close(&stwAppResultFilePtr);
        UARTprintf(
            "\n====================================================================\n");
    }
    return retVal;
}

static int32_t SblUpdateTestAppResult(char *appInfoFile,
                                      char *appResultFile,
                                      char *appListFile)

{
    int32_t retVal       = STW_SOK;
    TCHAR    stwTestId[4] = "\0";
    TCHAR   *stwTestIdPtr;
    int32_t stwTestno;
    FRESULT fresult;
    FIL     stwAppInfoFilePtr;
    volatile uint32_t done = 1U;

    stwTestIdPtr = stwTestId;

    fresult = f_open(&stwAppInfoFilePtr, appInfoFile, (BYTE) FA_READ);

    if (fresult != FR_OK)
    {
        UARTprintf("\n App TestCase Info File Open fails \n");
        retVal = STW_EFAIL;
    }

    if (retVal == STW_SOK)
    {
        if (NULL ==
            f_gets(stwTestIdPtr, ((int32_t)TEST_ID_BUFFER_SIZE * (int32_t)sizeof(TCHAR)),
                   &stwAppInfoFilePtr))
        {
            fresult = FR_INVALID_DRIVE;
            UARTprintf("\n App TestCase Info File read  fails\n");
            retVal = STW_EFAIL;
        }

        if (retVal == STW_SOK)
        {
            stwTestno = SblStrToIntConv(stwTestIdPtr);
            retVal    = SblUpdateAppTestResult(appResultFile,
                                               appListFile,
                                               stwTestno);
        }

        if (retVal == STW_SOK)
        {
            f_close(&stwAppInfoFilePtr);
            fresult = f_open(&stwAppInfoFilePtr, appInfoFile, (BYTE) FA_WRITE);

            if (fresult != FR_OK)
            {
                UARTprintf("\n App TestCase Info File Open fails \n");
                retVal = STW_EFAIL;
            }
            stwTestno    = stwTestno + 1;
            stwTestIdPtr = SblIntToStrConv(stwTestno);
            if (STW_EFAIL == f_puts(stwTestIdPtr, &stwAppInfoFilePtr))
            {
                fresult = FR_INVALID_DRIVE;
                UARTprintf("\n App TestCase Info File read  fails\n");
                retVal = STW_EFAIL;
            }
        }
        f_close(&stwAppInfoFilePtr);

        fresult = f_open(&stwAppInfoFilePtr, appInfoFile, (BYTE) FA_READ);

        if (fresult != FR_OK)
        {
            UARTprintf("\n App TestCase Info File Open fails \n");
            retVal = STW_EFAIL;
        }
        f_close(&stwAppInfoFilePtr);
    }

    if (retVal == STW_SOK)
    {
        /* TBD : Check is this workround is needed for Tda3xx*/
        /* Workaround: Configure CM_CUSTEFUSE_CLKSTCTRL in SW_WKUP Mode
         * in order to avoid hang when we do Global cold reset for multiple
         *times */
        HW_WR_FIELD32((SOC_CUSTEFUSE_CM_CORE_BASE + CM_CUSTEFUSE_CLKSTCTRL),
                      CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL,
                      CM_CUSTEFUSE_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (retVal != PM_SUCCESS)
        {
            UARTprintf("\n Failed to do cold reset \n");
            while (1U == done)
            {
                /* Noting to be done hear wait forever */
            }
        }
    }
    return retVal;
}

static void SblGetAppTestCaseParams(const char             *appListFile,
                                    sblAppTestCaseParams_t *tcPrms,
                                    uint32_t               *validTc,
                                    uint32_t                tcNum)
{
    uint32_t    srcIdx = 0, destIdx = 0;
    static char timeoutStr[20], ignoreTstStatStr[20];
    static char lineBuffer[LINE_BUFFER_SIZE];
    FIL         testCaseFp;
    FRESULT     fresult;
    int32_t    status = STW_SOK;

    /* Init same value in case of error */
    memset(lineBuffer, 0, (LINE_BUFFER_SIZE * sizeof(char)));
    tcPrms->appImageFile[0] = ((char) 0);
    tcPrms->wdgTimeout      = 1U;
    tcPrms->boardType       = 0U;

    fresult = f_open(&testCaseFp, appListFile, (BYTE) FA_READ);
    if (fresult == FR_NO_FILE)
    {
        /* TODO: Can we create the applist using FAT32 dir APIs and relying on
         * SBL magic header? */
        status = STW_EFAIL;
    }

    /* Read and skip line till required TC is reached */
    if(status == STW_SOK)
    {
        while (tcNum > 0)
        {
            if (NULL == f_gets((TCHAR *)lineBuffer,
                              ((int32_t)LINE_BUFFER_SIZE * (int32_t)sizeof(char)),
                               &testCaseFp))
            {
                /* EOF/Error */
                f_close(&testCaseFp);
                *validTc = 0;
                status = STW_EFAIL;
                break;
            }

            if (lineBuffer[srcIdx] == (char)'#')
            {
                /* Skip comments */
            }
            else
            {
                tcNum--;
            }
        }
    }
    if(status == STW_SOK)
    {
        *validTc = 1U;

        /* Now get the AppImage filename */
        destIdx = 0;
        while (srcIdx < LINE_BUFFER_SIZE)
        {
            if ((lineBuffer[srcIdx] == ((char) 0)) ||
                (lineBuffer[srcIdx] == (char)';'))
            {
                /* EOL or field end */
                tcPrms->appImageFile[destIdx] = ((char) 0);
                srcIdx++;
                destIdx++;
                break;
            }

            tcPrms->appImageFile[destIdx] = lineBuffer[srcIdx];
            srcIdx++;
            destIdx++;
        }

        /* Now get the WDG timeout value*/
        destIdx = 0;
        while ((srcIdx < sizeof (lineBuffer)) &&
               (destIdx < sizeof (timeoutStr)))
        {
            if ((lineBuffer[srcIdx] == ((char) 0)) ||
                (lineBuffer[srcIdx] == (char)';'))
            {
                /* EOL or field end */
                timeoutStr[destIdx] = ((char) 0);
                srcIdx++;
                destIdx++;
                break;
            }

            timeoutStr[destIdx] = lineBuffer[srcIdx];
            srcIdx++;
            destIdx++;
        }
        tcPrms->wdgTimeout = SblStrToIntConv(timeoutStr);

        /* Now get the checkTestStatus value*/
        destIdx = 0;
        while ((srcIdx < sizeof (lineBuffer)) &&
               (destIdx < sizeof (ignoreTstStatStr)))
        {
            if ((lineBuffer[srcIdx] == ((char) 0)) ||
                (lineBuffer[srcIdx] == (char)';'))
            {
                /* EOL or field end */
                ignoreTstStatStr[destIdx] = ((char) 0);
                srcIdx++;
                destIdx++;
                break;
            }

            ignoreTstStatStr[destIdx] = lineBuffer[srcIdx];
            srcIdx++;
            destIdx++;
        }
        tcPrms->checkTestStatus = SblStrToIntConv(ignoreTstStatStr);

        /* TODO: Get board type*/

        f_close(&testCaseFp);
    }

    return;
}

static void SblAppPrintTestResult(char *appResultFile)
{
    static char lineBuf[LINE_BUFFER_SIZE];
    FIL         testCaseFp;
    FRESULT     fresult;

    /* Init same value in case of error */
    memset(lineBuf, 0, (LINE_BUFFER_SIZE * sizeof(char)));

    fresult = f_open(&testCaseFp, appResultFile, (BYTE) FA_READ);
    if (fresult != FR_NO_FILE)
    {
        /* Print every line till EOF */
        while (NULL != f_gets((TCHAR *)lineBuf,
                              ((int32_t)LINE_BUFFER_SIZE * (int32_t)sizeof(char)),
                              &testCaseFp))
        {
            UARTprintf("%s", lineBuf);
        }
        f_close(&testCaseFp);
    }
    return;
}

#if defined (SOC_TDA3XX)

static void SblRTIConfig(void)
{
    uint32_t rtiPreload_value;
    int32_t  config_status;
    uint32_t timeOutVal;

    if (gWdgTimeout > 960U)
    {
        UARTprintf("\nNot able to Program TimeOut %d ", gWdgTimeout);
        UARTprintf(
            "\nConfiguring Max TimeOut value: 960 Secs");
    }

    /* timeout value in ms*/
    timeOutVal = gWdgTimeout * 1000U;

    /* RTI_CLOCK_SOURCE_32KHZ : SBL_RTI_CLOCK_SOURCE_32KHZ_FREQ_KHz*/
    /* Get the clock ticks for given time-out value */
    rtiPreload_value = timeOutVal * SBL_RTI_CLOCK_SOURCE_32KHZ_FREQ_KHz;

    /* Select suspend lines for RTI module : IPU_C1*/
    HW_WR_REG32(SOC_I_DRM_BASE + SOC_I_DRM_BASE_SUSPEND_CTRL20,
                SBL_RTI_SUSPEND_LINE_CORE_IPU_C1);

    /* Select RTI module clock source : SBL_RTI_CLOCK_SOURCE_32KHZ */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE +
                  CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL,
                  CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1,
                  SBL_RTI_CLOCK_SOURCE_32KHZ);

    config_status = RTIDwwdWindowConfig(SBL_RTI_MODULE,
                                        RTI_DWWD_REACTION_GENERATE_RESET,
                                        rtiPreload_value,
                                        RTI_DWWD_WINDOWSIZE_100_PERCENT);

    if (config_status == STW_EFAIL)
    {
        UARTprintf("\n Error during RTI Window configuration \n");
    }
    else
    {
        RTIDwwdCounterEnable(SBL_RTI_MODULE);
    }
}

#endif

void SBLTestAutoEnvCfg(void)
{
#if defined (SOC_TDA3XX)
    SblRTIConfig();

    /* Evict the IPU1 Uni-cache */
    UNICACHEWriteBackAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                         UNICACHE_WAIT_INFINITE);

    /* Disable the IPU1 Uni-cache */
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);

    /* Invalidate the IPU1 Uni-cache */
    UNICACHEInvalidateAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          UNICACHE_WAIT_INFINITE);
#else
    SblWdtimerConfig();
#endif
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
static void SblWdtimerConfig(void)
{
    uint32_t wdCounterVal;
    /*stop the wdtimer*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /*trigger reload*/
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x1010);
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x0101);

    /*disable DLY interrupt*/
    WDTIMERIntDisable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Disabling the wdtimer DLY interrupt in AINTC. */
    Intc_SystemDisable(SBL_WD_TIMER_DELAY_INT);

    /*Unregister the wdtimer DLY interrupt from system vector table*/
    Intc_IntUnregister(SBL_WD_TIMER_DELAY_INT);

    /* Set the count value into the counter register and the counter reload
     * register- this down counter so substract from max of 0xFFFFFFFF and
     * 0x8000U is timeout for 1 second with 31.25us clock period */
    wdCounterVal = 0xFFFFFFFFU - (0x8000U * gWdgTimeout);
    WDTIMERCounterSet(SOC_WD_TIMER2_BASE, wdCounterVal);
    WDTIMERReloadSet(SOC_WD_TIMER2_BASE, wdCounterVal);

    /*start the wdtimer*/
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

#endif

static int32_t SblStrToIntConv(const char *str)
{
    int32_t res = 0; /* Initialize result*/
    int32_t i   = 0;

    /* Iterate through all characters of input string and update result */
    while (str[i] != '\0')
    {
        res = (res * 10) + ((int32_t)str[i] - (int32_t)'0');
        i++;
    }
    /* return result*/
    return res;
}

static char *SblIntToStrConv(int32_t integerVal)
{
    /* points to terminating '\0' */
    char  *p = gBuf + SBL_INT_DIGITS + 1U;
    int32_t    temp;

    if (integerVal >= 0)
    {
        do {
            --p;
            temp        = (int32_t)'0';
            temp       += (integerVal % 10);
            *p          = (char)temp;
            integerVal /= 10;
        } while (integerVal != 0);
    }
    else              /* integerVal < 0 */
    {
        do {
            --p;
            temp        = (int32_t)'0';
            temp       -= integerVal % 10;
            *p          = (char)temp;
            integerVal /= 10;
        } while (integerVal != 0);
        --p;
        *p = (char)'-';
    }
    return p;
}

uint32_t SBLTestAutoCheckWDTResetStatus(void)
{
    int32_t  retVal         = 0;
    uint32_t resetStatus    = 0;
    uint32_t wdtResetStatus = 0;

    /* This checks for whether last reset is warm reset :
     * Checks the Reset status of watchdog Timer
     */
#if defined (SOC_TDA3XX)
    resetStatus = HW_RD_FIELD32((SOC_DEVICE_PRM_BASE + PRM_RSTST),
                                PRM_RSTST_SECURE_WDT_RST);
#else
    retVal = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_MPU_WDT_RST,
                                       &resetStatus);
    if (PM_SUCCESS != retVal)
    {
        UARTprintf(
            "\n WARM_RST : Reset Domain is not enabled or Invalid Reset Domain \n");
    }
#endif
    if (0x1U == resetStatus)
    {
        wdtResetStatus = 1U;
        UARTprintf("\n\nSBL Boot starts with warm reset");
    }
    /* This checks for whether last reset is cold reset :
     * Checks the Global Reset status for COLD_RST
     */
    retVal = PMHALResetGetGlobalStatus(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST,
                                       &resetStatus);
    if (PM_SUCCESS != retVal)
    {
        UARTprintf(
            "\n COLD_RST : Reset Domain is not enabled or Invalid Reset Domain \n");
    }
    if (0x1U == resetStatus)
    {
        wdtResetStatus = 0;
        retVal         = PMHALResetClearGlobalStatus(
            PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        UARTprintf("\nSBL Boot starts with cold reset");
    }

    return wdtResetStatus;
}

