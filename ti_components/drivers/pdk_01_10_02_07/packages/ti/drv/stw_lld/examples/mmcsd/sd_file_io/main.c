/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *   Component:      examples
 *
 *   Filename:           main.c
 *
 *   Description:    Test application for MMCSD & FAT Filesystem. Open an file
 *                   & read the content & send to UARTConsole
 *
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/soc.h>

#include <ti/csl/csl_edma.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_API.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/pm/pmhal.h>

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define IO_EXPANDER_SA (0x21)

#define BASE_BOARD     ('1')
#define JAMR3_BOARD    ('2')
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
signed char _srcBuffm[] =
    "Testing File read/write functions on SD CARD... ";
int32_t     gTestStatus = STW_SOK;

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
void MMCSD_LDO_PWR(void);
void mmc1PinMux(void);
void mmc3PinMux(void);
void mainMenu(char *option);
#endif

void delay(uint32_t delay);

void fileIoTest(void);
void mmc4PinMux(void);

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
int main(void)
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    char                 mainMenuOption;
#endif
    volatile int8_t      appDone = 1U;
    stwAppInitParams_t   stwAppInitParams;
    int32_t              retVal;
    stwAppDeInitParams_t stwAppDeInitParams;

    BspOsal_cacheEnable(BSP_OSAL_CT_ALL);

    StwUtils_appInitParams_init(&stwAppInitParams);
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        UARTprintf("\r\nSystem Init Failed ");
        gTestStatus = STW_EFAIL;
    }

    /* EDMA3 Init */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    mainMenu(&mainMenuOption);

    if (BASE_BOARD == mainMenuOption)
    {
        mmc1PinMux();

        HSMMCSDInit(MMC1_INST);

        UARTPuts("\r\n SD Card Init Done. \r\n", -1);

        fileIoTest();
    }
    else if (JAMR3_BOARD == mainMenuOption)
    {
        mmc3PinMux();

        HSMMCSDInit(MMC3_INST);

        UARTPuts("\r\n SD Card Init Done. \r\n", -1);

        fileIoTest();
    }
    else
    {
        UARTPuts("\r\nSD Card Init not done. Not a valid main menu option \r\n", -1);
    }
#elif defined (SOC_TDA3XX)
    mmc4PinMux();

    HSMMCSDInit(MMC4_INST);

    UARTPuts("\r\n SD Card Init Done. \r\n", -1);

    fileIoTest();
#endif

    UARTPuts("\r\nSD CARD FILE IO board diagnostic test exiting...", -1);

    /* System De init */
    stwAppDeInitParams.isI2cDeInitReq = TRUE;
    retVal = StwUtils_appDefaultDeInit(stwAppDeInitParams);
    if (retVal != STW_SOK)
    {
        UARTprintf("\r\nSystem DeInit Failed ");
        gTestStatus = STW_EFAIL;
    }

    if (gTestStatus == STW_SOK)
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
        UARTPuts("\r\n SD CARD FILE IO Test Pass", -1);
    }
    else
    {
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_FAIL);
        UARTPuts("\r\n SD CARD FILE IO Test Fail", -1);
    }

    while (appDone) ;

    return 0;
}

void fileIoTest(void)
{
    char    *filename = "TestFile";
    FIL      fp;
    FRESULT  fresult;
    UINT     bytes_read = 0;
    uint32_t Max_read   = sizeof (_srcBuffm);
    char     buffptr[sizeof (_srcBuffm)];
    uint32_t loopcount = 1000U, cnt;

    fresult = f_open(&fp, filename, FA_WRITE);
    if (fresult != FR_OK)
    {
        /*If file does not exist. Create new one*/
        fresult = f_open(&fp, filename, FA_CREATE_NEW);
        if (fresult != FR_OK)
        {
            UARTPuts("\r\n File create error \r\n", -1);
            while (1) ;
        }
        else
        {
            f_close(&fp);
            /*Open handle to the newly created file*/
            fresult = f_open(&fp, filename, FA_WRITE);
        }
    }

    cnt = 0U;
    while (cnt < loopcount)
    {
        fresult = f_write(&fp, &_srcBuffm, sizeof (_srcBuffm), &bytes_read);
        if (fresult != FR_OK)
        {
            UARTPuts("\r\n File write error \r\n", -1);
            while (1) ;
        }
        cnt++;
    }
    f_close(&fp);

    fresult = f_open(&fp, filename, FA_READ);
    if (fresult != FR_OK)
    {
        UARTPuts("\r\n File open error \r\n", -1);
        while (1) ;
    }

    cnt = 0U;
    while (cnt < loopcount)
    {
        fresult = f_read(&fp, (void *) buffptr, Max_read, (UINT *) &bytes_read);
        if (fresult != FR_OK)
        {
            UARTPuts("\r\n File read error \r\n", -1);
            while (1) ;
        }
        if (memcmp(buffptr, _srcBuffm, bytes_read) != 0)
        {
            UARTPuts("\r\n Data mismatch!!\r\n", -1);
            while (1) ;
        }
        cnt++;
    }
    f_close(&fp);

    /*print the file content*/
    UARTPuts(buffptr, bytes_read);

    UARTPuts("\r\n FILEIO testapp completed successfully \r\n", -1);
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
void mmc1PinMux()
{
    uint32_t tmpRegVal;
    /*MMC1- CM_L3INIT_MMC1_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL);
    tmpRegVal |= 0x03000000;
    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC1_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc1  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC1, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);
    MMCSD_LDO_PWR();

    /*MMC1 PAD Configuration*/
    PlatformMMCSD1SetPinMux();
}

void mmc3PinMux()
{
    uint32_t tmpRegVal;
    /*MMC3- CM_L4INIT_MMC3_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC3_CLKCTRL);
    tmpRegVal |= 0x02000000;
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC3_CLKCTRL, tmpRegVal);

    /*Enable the module - mmc3  */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_MMC3, PMHAL_PRCM_MODULE_MODE_ENABLED,
                       PM_TIMEOUT_INFINITE);

    /*MMC3 PAD Configuration*/
    PlatformMMCSD3SetPinMux();

    HSMMCSDInit(MMC3_INST);
}

void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\r\n\r\n**** SD CARD FILE IO TEST ****", -1);
        UARTPuts("\r\nMenu:", -1);
        UARTPuts("\r\n1. Base  board SD CARD", -1);
        UARTPuts("\r\n2. JAMR3 board SD CARD", -1);
        UARTPuts("\r\nx. Exit", -1);
        UARTPuts("\r\nSelect test board : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if (BASE_BOARD == *option || JAMR3_BOARD == *option
            || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\r\nEnter Valid option\r\n", -1);
        }
    }
}

#endif

void delay(uint32_t delay)
{
    volatile uint32_t i;
    for (i = 0; i < (1000 * delay); ++i) ;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
void   MMCSD_LDO_PWR()
{
    /*CTRL_CORE_CONTROL_PBIAS*/

    uint32_t reg_val = 0;

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);

    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    delay(10); /* wait 10 us */
    reg_val &= ~CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    /*Enable SDCARD_BIAS_VMODE*/
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK; /* 3v */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    reg_val = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE + CTRL_CORE_CONTROL_PBIAS);
    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);
    delay(150); /* wait 10 us */

    reg_val |= CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_PBIAS, reg_val);

    delay(150); /* wait 10 us */
}

#endif

#if defined (SOC_TDA3XX)

void mmc4PinMux()
{
    uint32_t tmpRegVal;
    /*MMC4- CM_L4INIT_MMC4_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL);
    tmpRegVal |= 0x02000000;
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, tmpRegVal);

    /*MMC4 PRCM config*/
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL, 0x2);

    /*MMC4 PAD Configuration*/
    PlatformMMCSD4SetPinMux();

    /*Todo IOExpander mux config : Mux F : MMC4*/
    BOARDSelectDevice(DEVICE_ID_MMC, DEVICE_MMC_INST_ID_4);
}

#endif
/***************************** End Of File ***********************************/
