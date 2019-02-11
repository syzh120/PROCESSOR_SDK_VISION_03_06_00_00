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
 *  \file stwutils_app.c
 *
 *  \brief This file implements application level generic helper functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/boards/src/stw_boardPriv.h>
#include <ti/drv/stw_lld/platform/stw_platform.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#include <ti/drv/pm/pmhal.h>
#endif
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_synctimer.h>
#if defined (__TI_ARM_V7M4__) && (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX))
    #include <ti/csl/arch/csl_arch.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** brief 32K Timer frequency */
#define STWUTILS_APP_32K_TIMER_FREQ        (32000U)

/** brief Overflow count value for 32bit counter */
#define STWUTILS_APP_COUNTER_MAX_COUNT     (0xFFFFFFFFU)

/** \brief Offset of DRM SUSPEND_CTRL31 register */
#define DRM_SUSPEND_CTRL31                 (0x27CU)
/** \brief DRM_SUSPEND_CTRL31 is mapped to COUNTER_32K Suspend Output line */
#define DRM_SUSPEND_CTRL_COUNTER_32K       (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL31)

#if defined (SOC_TDA3XX)
/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU_C0             (0x3U)
#else
/** \brief DRM SUSPEND Source as A15 */
#define DRM_SUSPEND_SRC_MPU_C0             (0x5U)
#endif

/** \brief Delay for SBL running on host proc to complete */
#define STWUTILS_APP_SBL_DELAY             (100U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure to store app objects.
 */
typedef struct stwUtils_AppObj
{
    Bool             initDone;
    /**< Initialization done flag. */
    platformId_t     platfrmId;
    /**< Platform identifier. */
    platformCpuRev_t cpuRev;
    /**< CPU version identifier. */
} stwUtils_AppObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  None
 */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief STW Utils app object used for storing semaphore handle, flags etc. */
static stwUtils_AppObj_t gStwUtilsAppObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  StwUtils_appInit
 *  \brief STW application utils init function.
 */
int32_t StwUtils_appInit(void)
{
    int32_t retVal = STW_SOK;
    stwUtils_AppObj_t *appObj = &gStwUtilsAppObj;

    memset(appObj, (int32_t) 0, sizeof (*appObj));

    /* Get platform type, board and CPU revisions */
    appObj->platfrmId = PLATFORMGetId();
    if ((appObj->platfrmId == PLATFORM_ID_UNKNOWN) ||
        (appObj->platfrmId >= PLATFORM_ID_MAX))
    {
        UARTprintf("\r\nError: Unrecognized platform!!");
        retVal = STW_EFAIL;
    }
    appObj->cpuRev = PLATFORMGetCpuRev();
    if (appObj->cpuRev >= PLATFORM_CPU_REV_MAX)
    {
        UARTprintf("\r\nError: Unrecognized CPU version!!");
        retVal = STW_EFAIL;
    }

    if (STW_SOK == retVal)
    {
        appObj->initDone = (Bool) TRUE;
    }

    return (retVal);
}

/**
 *  StwUtils_appDeInit
 *  \brief STW application utils deinit function.
 */
int32_t StwUtils_appDeInit(void)
{
    int32_t retVal = STW_SOK;
    stwUtils_AppObj_t *appObj = &gStwUtilsAppObj;

    appObj->initDone = (Bool) FALSE;

    return (retVal);
}

/**
 *  StwUtils_appDefaultInit
 *  \brief STW application utils function to call all the default init
 *  functions.
 */
int32_t StwUtils_appDefaultInit(stwAppInitParams_t stwAppInitPrms)
{
    int32_t              retVal = STW_SOK;
    boardInitParams_t    boardInitPrms;
    deviceInitParams_t   deviceInitPrms;
    platformInitParams_t platInitPrms;

    BoardInitParams_init(&boardInitPrms);
    /* Override board detection if I2C is disabled */
    if (((Bool) TRUE) != ((Bool) stwAppInitPrms.isI2cInitReq))
    {
        boardInitPrms.boardId      = BOARD_UNKNOWN;
        boardInitPrms.baseBoardRev = BOARD_REV_UNKNOWN;
        boardInitPrms.dcBoardRev   = BOARD_REV_UNKNOWN;
    }

    retVal = BOARDInit(&boardInitPrms);
    if (STW_SOK == retVal)
    {
        PLATFORMInitParams_init(&platInitPrms);
        retVal = PLATFORMInit(&platInitPrms);
        if (STW_SOK != retVal)
        {
            UARTprintf("\r\nError: Platform Init failed!!");
        }
    }
    else
    {
        UARTprintf("\r\nError: BOARDInit Init failed!!");
    }

    if (STW_SOK == retVal)
    {
        retVal = StwUtils_appUartModuleInit(stwAppInitPrms.isUartInitReq);
        if (STW_SOK != retVal)
        {
            UARTprintf(
                "\r\nError: StwUtils_appUartModuleInit Init failed!!");
        }
    }

    if (STW_SOK == retVal)
    {
        /* Override I2C init for non-EVM builds */
        if (PLATFORM_ID_EVM != PLATFORMGetId())
        {
            stwAppInitPrms.isI2cInitReq = (uint32_t) FALSE;
        }
        if (stwAppInitPrms.isI2cInitReq)
        {
            DEVICEInitParams_init(&deviceInitPrms);

            deviceInitPrms.isI2cProbingReq = (uint32_t) FALSE;

            retVal += DEVICEInit(&deviceInitPrms);
            if (LLD_HSI2C_SUCCESS != retVal)
            {
                UARTprintf("\r\nError: Device Init failed!!");
            }
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        retVal += StwUtils_appInit();
        if (STW_SOK != retVal)
        {
            UARTprintf("\r\nError: App Utils Init failed!!");
        }
    }

    if (stwAppInitPrms.enablePrintEvmInfo)
    {
        StwUtils_appPrintInfo();
    }

    return (retVal);
}

void StwUtils_appPrintInfo(void)
{
    /* Print platform info*/
    UARTprintf("\r\n \r");
    PLATFORMPrintInfo();
    BOARDPrintInfo();
    UARTprintf("\r\n \r");
}

/**
 *  StwUtils_appDefaultDeInit
 *  \brief STW application utils function to call all the default de-init
 *  functions.
 */
int32_t StwUtils_appDefaultDeInit(stwAppDeInitParams_t stwAppDeInitPrms)
{
    int32_t retVal = STW_SOK;

    retVal = StwUtils_appDeInit();
    if (STW_SOK != retVal)
    {
        UARTprintf("\r\nError: App Utils De-Init failed!!");
    }
    /* Override I2C de-init for non-EVM builds */
    if (PLATFORM_ID_EVM != PLATFORMGetId())
    {
        stwAppDeInitPrms.isI2cDeInitReq = (uint32_t) FALSE;
    }

    if (((Bool) TRUE) == ((Bool) stwAppDeInitPrms.isI2cDeInitReq))
    {
        retVal = DEVICEDeInit(NULL);
        if (STW_SOK != retVal)
        {
            UARTprintf("\r\nError: Device De-Init failed!!");
        }
    }

    retVal = PLATFORMDeInit(NULL);
    if (STW_SOK != retVal)
    {
        UARTprintf("\r\nError: STW Platform De-Init failed!!");
    }

    retVal = BOARDDeInit(NULL);
    if (STW_SOK != retVal)
    {
        UARTprintf("\r\nError: STW Board De-Init failed!!");
    }

    return (retVal);
}

int32_t StwUtils_appUartModuleInit(uint32_t uartInitReq)
{
    int32_t  retVal = STW_SOK;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
    uint32_t uartInstId;
    pmhalPrcmModuleId_t pmModInstId;

    if (uartInitReq)
    {
        uartInstId = BOARDGetConsoleInstID();
        if (uartInstId == DEVICE_UART_INST_ID_3)
        {
            pmModInstId = PMHAL_PRCM_MOD_UART3;
        }
        else if (uartInstId == DEVICE_UART_INST_ID_1)
        {
            pmModInstId = PMHAL_PRCM_MOD_UART1;
        }
        else
        {
            retVal = STW_EFAIL;
        }

        if (retVal == STW_SOK)
        {
            /*Enable the module - uart*/
            retVal = PMHALModuleModeSet(pmModInstId,
                                        PMHAL_PRCM_MODULE_MODE_ENABLED,
                                        PM_TIMEOUT_INFINITE);
            if (retVal != PM_SUCCESS)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                UARTStdioInit();
            }
        }
    }
#endif
    return retVal;
}

int32_t StwUtils_appGetCharTimeout(int8_t *ch, uint32_t msec)
{
    int32_t  retVal = STW_SOK;
    uint32_t startCount, elapsedCount, cycleDelay;
    int32_t  status;

    /* To config 32K Counter in run state when A15(Tda2xx)/M4(Tda3xx) is
     * halted */
    StwUtils_appConfig32KCounterSuspendState();

    retVal     = StwUtils_appGet32KCounterValue(&startCount);
    cycleDelay = (msec * STWUTILS_APP_32K_TIMER_FREQ) / 1000U;
    do
    {
        *ch = UARTGetcNonBlocking();
        if (*ch !=  -((int32_t) 1))
        {
            retVal = STW_SOK;
            break;
        }
        retVal = STW_EFAIL;
        status = StwUtils_appGetElapsedValue(startCount, &elapsedCount);
    } while ((STW_SOK == status) && (elapsedCount <= cycleDelay));

    return (retVal);
}

int32_t StwUtils_appGetNumTimeout(int32_t *num, uint32_t msec)
{
    int32_t  retVal = STW_SOK;
    int8_t ch;
    uint32_t startCount, elapsedCount = 0U, cycleDelay;
    int32_t  status, value = 0, sign = 1;

    /* To config 32K Counter in run state when A15(Tda2xx)/M4(Tda3xx) is
     * halted */
    StwUtils_appConfig32KCounterSuspendState();

    retVal     = StwUtils_appGet32KCounterValue(&startCount);
    cycleDelay = (msec * STWUTILS_APP_32K_TIMER_FREQ) / 1000U;
    do
    {
        ch = UARTGetcNonBlocking();
        if (ch !=  -((int32_t) 1))
        {
            if ((int8_t) '-' == ch)
            {
                UARTPutc((uint8_t) '-');
                sign =  -((int32_t) 1);
            }
            else
            {
                UARTPutc((uint8_t) ch);
                value = (value * 10) + ((int32_t) ch - 0x30);
            }
            do
            {
                ch = UARTGetcNonBlocking();
                if (ch !=  -((int32_t) 1))
                {
                    /* Echoing the typed characters to the serial console.*/
                    UARTPutc((uint8_t) ch);
                    /*
                    ** Checking if the entered character is a carriage return.
                    ** Pressing the 'Enter' key on the keyboard executes a
                    ** carriage return on the serial console.
                    */
                    if ((int8_t) '\r' == ch)
                    {
                        break;
                    }
                    /*
                    ** Subtracting 0x30 to convert the representation of the digit
                    ** from ASCII to hexadecimal.
                    */
                    value = (value * 10) + ((int32_t) ch - 0x30);
                }
                retVal = STW_EFAIL;
                status = StwUtils_appGetElapsedValue(startCount, &elapsedCount);
            } while ((STW_SOK == status) && (elapsedCount <= cycleDelay));
            if(elapsedCount <= cycleDelay)
            {
                value = value * sign;
                retVal = STW_SOK;
                *num = value;
            }
            break;
        }
        retVal = STW_EFAIL;
        status = StwUtils_appGetElapsedValue(startCount, &elapsedCount);
    } while ((STW_SOK == status) && (elapsedCount <= cycleDelay));

    return (retVal);
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
int32_t StwUtils_appGet32KCounterValue(uint32_t *value)
{
    *value = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    return STW_SOK;
}

int32_t StwUtils_appGetElapsedValue(uint32_t  value,
                                    uint32_t *elapsedValue)
{
    uint32_t currVal;

    currVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    if (currVal < value)
    {
        /* Counter overflow occured */
        currVal       = (STWUTILS_APP_COUNTER_MAX_COUNT - value) + currVal + 1U;
        *elapsedValue = currVal;
    }
    else
    {
        *elapsedValue = currVal - value;
    }

    return STW_SOK;
}

#endif

#if defined (__TI_ARM_V7M4__) && (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX))
void StwUtils_appConfigIPU1DefaultAMMU(void)
{
    ammuPageConfig_t pageConfig = {0U};

    /* 0th large page mapping: P.A. 0x40000000U V.A 0x40000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 0U;
    pageConfig.policyRegVal    = 0x00000007;
    pageConfig.physicalAddress = 0x40000000U;
    pageConfig.logicalAddress  = 0x40000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st large page mapping: P.A. 0x80000000U V.A 0x80000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 1U;
    pageConfig.policyRegVal    = 0x000B0007;
    pageConfig.physicalAddress = 0x80000000U;
    pageConfig.logicalAddress  = 0x80000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 2nd large page mapping: P.A. 0xA0000000U V.A 0xA0000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 2U;
    pageConfig.policyRegVal    = 0x00020007;
    pageConfig.physicalAddress = 0xA0000000U;
    pageConfig.logicalAddress  = 0xA0000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 3rd large page mapping: P.A. 0x40000000U V.A 0x60000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_LARGE;
    pageConfig.ammuPageNum     = 3U;
    pageConfig.policyRegVal    = 0x00000007;
    pageConfig.physicalAddress = 0x40000000U;
    pageConfig.logicalAddress  = 0x60000000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 0th small page mapping: P.A. 0x55020000U V.A. 0x00000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = 0x0001000B;
    pageConfig.ammuPageNum     = 0;
    pageConfig.logicalAddress  = 0x00000000U;
    pageConfig.physicalAddress = 0x55020000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);

    /* 1st small page mapping: P.A. 0x55080000U V.A. 0x40000000U */
    pageConfig.ammuPageType    = AMMU_PAGE_TYPE_SMALL;
    pageConfig.policyRegVal    = 0x0000000B;
    pageConfig.ammuPageNum     = 1;
    pageConfig.logicalAddress  = 0x40000000U;
    pageConfig.physicalAddress = 0x55080000U;
    AMMUConfigPage(SOC_IPU1_UNICACHE_MMU_BASE, &pageConfig);
}

#endif

void StwUtils_appLogTestResult(uint32_t testResult)
{
    /* Writing result to OCMC RAM */
    HW_WR_REG32(STWUTILS_APP_TST_ADDR, testResult);
#if (defined (AVV_TEST_AUTO_BUILD))
    /* Generate Global Warm reset to the devcie */
    HW_WR_REG32((SOC_DEVICE_PRM_BASE +PRM_RSTCTRL) ,
                HW_RD_REG32(SOC_DEVICE_PRM_BASE + PRM_RSTCTRL) | 0x00000001);
#endif
}

void StwUtils_appConfig32KCounterSuspendState(void)
{
#if defined (SOC_TDA3XX) && !(defined (__TI_ARM_V7M4__))
    /* Suspend Input Line : IPU_C0
     * Suspend Output Line : DRM_SUSPEND_CTRL_COUNTER_32K
     * This makes sure when M4 is halt, 32K Counter is not halted
     */
    HW_WR_REG32(DRM_SUSPEND_CTRL_COUNTER_32K,
                (((uint32_t) DRM_SUSPEND_SRC_IPU_C0 << 4U) | 0x0U));

#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /* As L3_INSTR is not connected to EVE1_P1 , so we cant able to configure
     * DRM_SUSPEND_CTRL_COUNTER_32K for EVE
     */
#if defined (__TI_ARM_V7M4__) || defined (_TMS320C6X)
    /* Suspend Input Line : MPU_C0
     * Suspend Output Line : DRM_SUSPEND_CTRL_COUNTER_32K
     * This makes sure when A15 is halt, 32K Counter is not halted
     */
    HW_WR_REG32(DRM_SUSPEND_CTRL_COUNTER_32K,
                (((uint32_t) DRM_SUSPEND_SRC_MPU_C0 << 4U) | 0x0U));
#endif
#endif
}

uint32_t StwUtils_appCheckTestResult(void)
{
    uint32_t testResult;

    testResult = HW_RD_REG32(STWUTILS_APP_TST_ADDR);

    return testResult;
}

void StwUtils_appWaitForSbl(void)
{
#if defined (__TI_ARM_V7M4__) || defined (_TMS320C6X) || defined (BUILD_ARP32)
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || (defined (SOC_TDA3XX) && !defined (__TI_ARM_V7M4__))
    uint32_t startCount, elapsedCount, cycleDelay;
    int32_t  status;

    /* To config 32K Counter in run state when A15(Tda2xx)/M4(Tda3xx) is halted
     */
    StwUtils_appConfig32KCounterSuspendState();

    status     = StwUtils_appGet32KCounterValue(&startCount);
    cycleDelay = (STWUTILS_APP_SBL_DELAY * STWUTILS_APP_32K_TIMER_FREQ) / 1000U;

    if (STW_SOK == status)
    {
        do
        {
            status = StwUtils_appGetElapsedValue(startCount, &elapsedCount);
        } while ((cycleDelay >= elapsedCount) && (STW_SOK == status));
    }
#endif
#endif
    return;
}

