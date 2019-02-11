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
 *  \file     sbl_tda3xx_main.c
 *
 *  \brief    This file contains the SBL main function which calls the SOC Init
 *            and slave core boot up functions in sequence.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_emif.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_emif.h>
#include <ti/csl/csl_rti.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_tda3xx.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda3xx.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_ddr_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <sbl_tda3xx_priv.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/pm/pmhal.h>
#if defined (SBL_TEST_AUTO_BUILD)
#include <ti/boot/sbl_auto/sbl_app/src/test_auto/sbl_test_auto.h>
#endif
#if defined (DEVICE_TYPE_HS)
#include <ti/boot/sbl_auto/security/include/tda3xx/tda3xx_gp_prime.h>
#endif

#if !defined (BOOTMODE_NOR)
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Define Address for SBL start time variable in NOR boot mode.
 * Should be in sync with sbl_m4_init_nor.asm
 */
#define  SBL_NOR_START_TIME_ADDRESS                    ((uint32_t) 0x003001C0U)

/* Macro to disable/enable RTI */
#define SBL_DISABLE_RTI                                ((uint32_t) TRUE)

/* Macro to lock/unlock Control Module MMR */
#define SBL_LOCK_MMR                                   ((uint32_t) FALSE)

/* Macro containing 32K Timer frequency */
#define SBL_32KTIMER_REFERENCE_VAL                     (32U * 1024U)

/* Macro containing Interrupt line Number to be used for TESOC */
#define SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER            ((uint32_t) 67U)

/* Macro containing IPU1 Core1 start address in QSPI and QSPI_SD boot mode */
#define SBL_RBL_SLAVE_CORE_START_ADDRESS_QSPI      ((uint32_t) 0x00300101U)

/* Macro containing IPU1 Core1 start address in NOR boot mode */
#define SBL_RBL_SLAVE_CORE_START_ADDRESS_NOR       ((uint32_t) 0x08000201U)

/* Macros containing IPU1 ECC Error interrupt Line numbers */
#define IPU_L2RAM_SEC_ERR_INT                      (84U)
#define IPU_L2RAM_DED_ERR_INT                      (85U)
#define IPU_L1DATA_SEC_ERR_INT                     (82U)
#define IPU_L1DATA_DED_ERR_INT                     (83U)
#define IPU_L1TAG_SEC_ERR_INT                      (80U)
#define IPU_L1TAG_DED_ERR_INT                      (81U)

/* Macro containing IPU1 RAM Size */
#define SBL_IPU1_RAM_SIZE                          ((uint32_t) 0x10000U)

/* Macro containing IPU1 UniCache Size */
#define SBL_IPU1_UNICACHE_SIZE                     ((uint32_t) 0x8000U)

/* Typedef for entry point function */
typedef void (*EntryFuncPtr_t)(void);

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function contains the code for jumping to IPU1 Core1's entry
 *          point.
 *
 * \param   None.
 *
 * \retval  None.
 */
#ifdef __cplusplus
#pragma CODE_SECTION(".ipu1_1_init");
#else
#pragma CODE_SECTION(SblIPU1Core1Init, ".ipu1_1_init");
#endif
void SblIPU1Core1Init(void);

/**
 * \brief   This function copies the vector table to IPU RAM.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblCopyVectorTable(void);

/**
 * \brief   This function configures the RGMII PADs in QSPI_SD boot mode.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    In order to use RGMII and MMC same PADs need to be configured. Thus
 *          RGMII is not configured while doing TI EVM PAD Configuration.
 */
static void SblConfigRGMIIPad(void);

/**
 * \brief   This function does the SBL configuration needed before running
 *          IPU TESOC Tests.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblConfigPreIPUTESOC(void);

/**
 * \brief   This function configures and initiates the TESOC IPU BIST.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    IPU resets after TESOC BIST and the control jumps to API
 *          SblCheckIPUBISTResult after wake-up.
 */
static void SblConfigAndInitiateIPUBIST(void);

/**
 * \brief   This function checks the TESOC IPU BIST result. The boot is aborted
 *          in case of failure.
 *
 * \param   None.
 *
 * \retval  None.
 *
 */
static void SblCheckIPUBISTResult(void);

/**
 * \brief   This function configures and initiates the TESOC tests on other
 *          domains except IPU i.e. DSP1, DSP2, EVE and ISSDSSVIP.
 *
 * \param   None.
 *
 * \retval  None.
 *
 * \note    Reset is not generated on SOC master IPU after running TESOC on
 *          these domains.
 */
static void SblConfigAndInitiateOtherTesocTests(void);

/**
 * \brief   This function does the normal SBL configuration after running IPU
 *          TESOC Tests.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblConfigPostIPUTESOC(void);

/**
 * \brief   This function acts as a wrapper for SBL print function.
 *
 * \param   message       Message to be printed.
 *
 * \retval  None.
 *
 * \note    Below ifdef __cplusplus is added so that C++ build passes without
 *          typecasting. This is because the prototype is build as C type
 *          whereas this file is build as CPP file. Hence we get C++ build
 *          error. Also if typecasting is used, then we get MisraC error
 *          Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
#if !(defined (SBL_TEST_AUTO_BUILD))
static void SblPrintFunction(const char *message);
#endif

#ifdef __cplusplus
}
#endif

/**
 * \brief   This function prints the boot-cycles in ms.
 *
 * \param   cyclesString     Description of boot cycles.
 * \param   bootCycles       Boot time in Cycles.
 *
 * \retval  None.
 */
static void SblPrintBootCycles(const char *cyclesString, uint32_t bootCycles);

#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 1)
/**
 * \brief   This function enables the ECC for IPU RAM. It primes both L1 Cache
 *          (including L1 tag) and L2 RAM before enabling.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblConfigIpuRamECC(void);
#endif

/**
 * \brief   This function sets entry point and wakes up IPU1.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblStartIPUCore1(void);

#if !defined (DEVICE_TYPE_HS)
/**
 * \brief   Dummy function to register for authenticate. Will return STW_SOK
 *          always. Used only for DEVICE_TYPE_HS
 *
 * \param   address     Unused
 * \param   size        Unused
 *
 * \retval  status      Always STW_SOK
 */
static int32_t SblDummyAuthenticateBinary(uint32_t address, uint32_t size);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern const volatile uint32_t vector_table[NUM_ELEMENTS_VECTOR_TABLE];

/**
 *  \brief Global time stamp variables. These variable can't be put in stack as
 *         reset due to TESOC test will re-initialize them.
 */
static volatile uint32_t       timeValSblStart;
static volatile uint32_t       timeValSblInitStart;
static volatile uint32_t       timeValIPUBistStart;
static volatile uint32_t       timeValIPUBistEnd;
static volatile uint32_t       timeValOtherTesocTestStart;
static volatile uint32_t       timeValOtherTesocTestEnd;
#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 1)
static volatile uint32_t       timeValIPURAMEccConfigStart;
static volatile uint32_t       timeValIPURAMEccConfigEnd;
#endif

/*
 * Variable for version 1 of Meta Header structure
 */
#ifdef __cplusplus
#pragma DATA_SECTION(".img_hdr1");
#else
#pragma DATA_SECTION(sblAppMetaHeaderV1, ".img_hdr1");
#endif
sbllibMetaHeaderV1_t           sblAppMetaHeaderV1;

/*
 * Variable for Meta Header structure
 */
#ifdef __cplusplus
#pragma DATA_SECTION(".img_hdr");
#else
#pragma DATA_SECTION(sblAppMetaHeaderV2, ".img_hdr");
#endif
sbllibMetaHeaderV2_t           sblAppMetaHeaderV2;

/*
 * Variable for RPRC Header structure
 */
#ifdef __cplusplus
#pragma DATA_SECTION(".img_hdr");
#else
#pragma DATA_SECTION(sblAppRPRCHeader, ".img_hdr");
#endif
sbllibRPRCImageHeader_t        sblAppRPRCHeader;

/* Zero array used in priming ECC protected memory */
static volatile uint32_t       gEmifEccInitBuff[32U] = {0U};

#if defined (SBL_TEST_AUTO_BUILD)
/**< \brief For TestAutomation :This global variable is used to store WDT reset
 *          status
 */
int32_t gWDTResetStatus = 0;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32_t           isTesocEnabled = FALSE;
    /* For test automation, SBL Library Init Params are not needed which
     * disables
     * SBL prints*/
#if !(defined (SBL_TEST_AUTO_BUILD))
    sbllibInitParams_t sblInitPrms;
    /* Default initialization of SBL Lib Params */
    SBLLibInitParamsInit(&sblInitPrms);
    /* Assign SBL Params */
    sblInitPrms.printFxn = &SblPrintFunction;
    SBLLibInit(&sblInitPrms);
#else
    SBLLibInit(NULL);
#endif

    /* Do initial configuration needed before IPU TESOC tests */
    SblConfigPreIPUTESOC();

    /*
     * TESOC BISTs are not supported as of now
     */
    isTesocEnabled = SBLIsTesocEnabled();

    if (TRUE == isTesocEnabled)
    {
        /* Initiate TESOC IPU BIST */
        SblConfigAndInitiateIPUBIST();
    }
    else
    {
        /* Do SBL configuration that should be done post TESOC tests */
        SblConfigPostIPUTESOC();
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

#if !(defined (SBL_TEST_AUTO_BUILD))
static void SblPrintFunction(const char *message)
{
    UARTPuts(message, UART_NUM_BYTES_CUSTOM);
}

#endif

void SblIPU1Core1Init(void)
{
    /* Warm reset does not clear AUXBOOT registers. Hence they should be cleared
     * explicitly after Core1 boot-up
     */
    /* Unlock Control Module */
    asm (" MOV R0, #0x2540");
    asm (" MOVT R0, #0x4A00");
    asm (" MOV R1, #0xAC2B");
    asm (" MOVT R1, #0x2FF1");
    asm (" STR R1, [R0]");

    /* Set AUXBOOT0 to Zero */
    asm (" MOV R0, #0x3CA8");
    asm (" MOVT R0, #0x4A00");
    asm (" MOV R1, #0x0");
    asm (" STR R1, [R0]");

    /* Set AUXBOOT1 to Zero */
    asm (" MOV R0, #0x3CAC");
    asm (" MOVT R0, #0x4A00");
    asm (" MOV R1, #0x0");
    asm (" STR R1, [R0]");

    while (0U == HW_RD_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS))
    {
        /* To remove MISRA C error */
    }

    /* IPU1 Core1 is held in WFE status by RBL. Core 0 wakes up core 1 by
     * sending event. Core 1 jumps to address specified by register
     * CTRL_CORE_SEC_ROM_AUXBOOT1 i.e. 0x00300100. Core 1 stays in while loop
     * till the time Core 0 parses the image and sets the entry point address
     * at location 0x00300180. Core 1 then branches to entry point.
     */
    asm (" MOV R0, #0x0180");
    asm (" MOVT R0, #0x0030");
    asm (" LDR R0, [R0]");
    asm (" BX R0");
}

static void SblCopyVectorTable(void)
{
    uint32_t addr   = 0x8U, index = 0U;
    uint32_t length = NUM_ELEMENTS_VECTOR_TABLE;

    for (index = 2U; index < length; index++)
    {
        HW_WR_REG32(addr, vector_table[index]);
        addr = addr + 4U;
    }
}

static void SblConfigRGMIIPad(void)
{
#if defined (BOOTMODE_QSPI_SD)

#ifndef BOARD_TYPE_TDA3XX_RVP
    /*IOExpander mux config : Mux F : EMAC0PHY */
    SBLUtilsConfigDevice(SBL_UTILS_DEVICE_ID_EMAC0PHY);
#endif

    /* Set RGMII PAD configuration */
    SBLLibRGMIISetPinMux();
#endif
}

static void SblConfigPreIPUTESOC(void)
{
    uint32_t siliconPackageType;
    int32_t  retVal = STW_SOK;
    pmhalPrcmDpllConfig_t *dpllParams;
    pmhalPrcmSysClkVal_t sysClkFreq = PMHAL_PRCM_SYSCLK_20_MHZ;
    uint32_t oppId;
    uint32_t isTesocEnabled = FALSE;

    /* Take start time-stamp and change RTI reaction */
#if defined (BOOTMODE_NOR)
    timeValSblStart = HW_RD_REG32(SBL_NOR_START_TIME_ADDRESS);
#else
    timeValSblStart = SBLUtilsRead32KTimer();
#endif

    timeValSblInitStart = SBLUtilsRead32KTimer();

    if (TRUE == SBL_DISABLE_RTI)
    {
        /* Configure DWWD Window size */
        RTIDwwdSetWindowSize(SOC_RTI1_BASE, RTI_DWWD_WINDOWSIZE_50_PERCENT);

        /* Service DWWD */
        RTIDwwdService(SOC_RTI1_BASE);

        /* Change RTI's action to interrupt */
        RTIDwwdSetReaction(SOC_RTI1_BASE, RTI_DWWD_REACTION_GENERATE_NMI);
    }

    /*
     * Wakeup IPU1-Core 1 before re-configuring AMMU if TESOC tests are
     * disabled
     */
    isTesocEnabled = SBLIsTesocEnabled();

    if (TRUE != isTesocEnabled)
    {
        SblStartIPUCore1();
    }

    /* Configure the IPU1 AMMU */
    SBLUtilsConfigIPU1DefaultAMMU();

#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 1)
    if (TRUE != isTesocEnabled)
    {
        /*
         * IPU RAM ECC should be configured before copying vector table. In case
         * TESOC is disabled, configure it here.
         */
        timeValIPURAMEccConfigStart = SBLUtilsRead32KTimer();

        SblConfigIpuRamECC();

        timeValIPURAMEccConfigEnd = SBLUtilsRead32KTimer();
    }
#endif

#if !(defined (SBL_TEST_AUTO_BUILD))
    /* Enable the IPU1's Uni-cache */
    SBLUtilsEnableIPU1Unicache();
#endif

    siliconPackageType = SBLLibGetSiliconPackageType();

    /* Copy the vector table */
    SblCopyVectorTable();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Unlock the MMR registers */
    SBLLibUnlockControlModuleMMR();

    /* Get the Sys clock1 Frequency */
    sysClkFreq = PMHALCMGetSysClockFreqEnum();

    /* Read the opp for which the SBL has been compiled */
    oppId = SBLGetOppId(siliconPackageType);

    /* Configure PRCM and Control Module registers before configuring DPLL. */
#if (SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ == (1U))
    if (oppId == SBLLIB_PRCM_DPLL_OPP_HIGH)
    {
        /* First perform all DSP and EVE PRCM transitions with OPP_OD and then
         * move to OPP High.
         */
        oppId = SBLLIB_PRCM_DPLL_OPP_OD;
    }
#endif
    retVal = SBLUtilsConfigureDspEveMux(oppId, siliconPackageType);
#if (SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ == (1U))
    oppId = SBLGetOppId(siliconPackageType);
#endif
    /* Configure DPLL CORE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_CORE,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    /* L3 clock = CORE CLK /2, L4 clock = L3 clock /2 */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L3_ICLK, (uint32_t) 2U);
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_L4_ROOT_CLK, (uint32_t) 2U);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_CORE,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* Configure DPLL PER */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_PER,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PER,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* UART Initialization */
    SBLUtilsPrintfInit(SBL_LIB_CONFIG_UART_INST);

#if defined (SOC_DRA78x)
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO, "\n DRA78x SBL Boot \n");
#else
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n TDA3xx SBL Boot \n");
#endif

    /* For TestAutomation : SBL checks for whether last reset is cold reset or
     * watchdog timer reset*/
#if defined (SBL_TEST_AUTO_BUILD)
    gWDTResetStatus = SBLTestAutoCheckWDTResetStatus();
#endif

    SBLPrintOppWarning(siliconPackageType);

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n SBL Config Before IPU TESOC BIST Failed \n");
        SBLLibAbortBoot();
    }

    /*
     * DSPs cause random issues as they are uninitialized,
     * power down DSPs
     */
    retVal = PMHALCMSetCdClockMode(
        (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP1,
        PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
        PM_TIMEOUT_NOWAIT);
    retVal += PMHALPdmSetPDState(
        PMHAL_PRCM_PD_DSP1,
        PMHAL_PRCM_PD_STATE_OFF,
        PM_TIMEOUT_NOWAIT);

    retVal += PMHALCMSetCdClockMode(
        (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP2,
        PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
        PM_TIMEOUT_NOWAIT);
    retVal += PMHALPdmSetPDState(
        PMHAL_PRCM_PD_DSP2,
        PMHAL_PRCM_PD_STATE_OFF,
        PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n PRCM Failed to Power Down DSPs, Aborting Boot\n");
        SBLLibAbortBoot();
    }
}

static void SblConfigAndInitiateIPUBIST(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;
#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC == 1)
    crcSignature_t crcSigVal;
#endif

    /* Take IPU LBIST start time-stamp */
    timeValIPUBistStart = SBLUtilsRead32KTimer();

#if (SBL_LIB_CONFIG_ENABLE_IPU_TESOC_ROM_CRC == 1)
    /* Compute CRC for IPU TESOC ROM */
    retVal = SBLUtilsComputeIPUTesocROMCRC(&crcSigVal);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n TESOC ROM CRC Computation Failed, Aborting Boot\n");
        SBLLibAbortBoot();
    }
    else
    {
        if ((TESOC_ROM_IPU_CRC_SIGNATURE_REGL != crcSigVal.regL) ||
            (TESOC_ROM_IPU_CRC_SIGNATURE_REGH != crcSigVal.regH))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n TESOC ROM CRC Match Failed, Aborting Boot\n");
            SBLLibAbortBoot();
        }
        else
        {
            /* CRC Computed is correct, do nothing */
        }
    }
#endif

    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    tesocTestConfig.testId = TESOC_TEST_ID_IPU;
    retVal = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    if (PM_SUCCESS != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n Failed to Get IPU LBIST Slice Info, Aborting Boot\n");
        SBLLibAbortBoot();
    }

    /*
     * Configure TESOC interrupt for IPU. TESOC interrupt acts as wake up
     * event for IPU to reboot.
     */
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   CPU_IPU1,
                   (SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER - 22U),
                   TESOC_IRQ_DONE);
    Intc_IntPrioritySet((uint16_t) SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER,
                        (uint16_t) 1U,
                        (uint8_t) 0U);
    Intc_SystemEnable((uint16_t) SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER);

    /* Register IPU Wake-up event instead of ISR */
    IPU_WUGEN_Enable((uint16_t) SBL_IPU_TESOC_TEST_INTR_LINE_NUMBER);

    /* Set entry point after reboot due to TESOC */
    HW_WR_REG32(SOC_SEC_EFUSE_REGISTERS_BASE +
                CTRL_CORE_SEC_ROM_CPU0_BRANCH,
                (uint32_t) &SblCheckIPUBISTResult);

    SBLLibRunTesocTest(TESOC_TEST_ID_IPU, &tesocTestConfig);
    /*
     * IPU resets after TESOC IPU BIST and hence no more execution happens after
     * this statement. After wakeup execution begins from API
     * SblCheckIPUBISTResult.
     */
}

static void SblCheckIPUBISTResult(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;

    /* Take IPU LBIST start time-stamp */
    timeValIPUBistEnd = SBLUtilsRead32KTimer();

    /* Enable IPU Core 1 After Completing TESOC IPU Test as
     * wakeup event has woken up only Core 0.
     */
    PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU1_RST, PM_TIMEOUT_NOWAIT);

    /* Start IPU Core 1 */
    SblStartIPUCore1();

    /* Configure the IPU1 AMMU */
    SBLUtilsConfigIPU1DefaultAMMU();

#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 1)
    /*
     * IPU RAM ECC should be configured before copying vector table.
     * In case IPU TESOC is enabled, configure it here.
     */
    timeValIPURAMEccConfigStart = SBLUtilsRead32KTimer();

    SblConfigIpuRamECC();

    timeValIPURAMEccConfigEnd = SBLUtilsRead32KTimer();

#endif

#if !(defined (SBL_TEST_AUTO_BUILD))
    /* Enable the IPU1's Uni-cache */
    SBLUtilsEnableIPU1Unicache();
#endif

    /* Copy the vector table */
    SblCopyVectorTable();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Assign test configuration for IPU BIST */
    tesocTestConfig.testId = TESOC_TEST_ID_IPU;
    TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    /* Clear TESOC interrupt and check TESOC IPU Test Result */
    TESOCIntrClear(SOC_TESOC_BASE, TESOC_INTR_FLAG_TEST_COMPLETION);
    /* Disable TESOC Interrupt as we dont use it for other domain tests */
    TESOCIntrDisable(SOC_TESOC_BASE,
                     TESOC_INTR_FLAG_TEST_COMPLETION);
    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n TESOC IPU Test Failed, Aborting Boot\n");
        SBLLibAbortBoot();
    }

    /* Do post IPU TESOC SBL configuration */
    SblConfigPostIPUTESOC();
}

static void SblConfigPostIPUTESOC(void)
{
    int32_t                     retVal = STW_SOK;
    uint32_t                    siliconPackageType;
    uint32_t                    sblBuildMode;
    uint32_t                    oppId;
    uint32_t                    edmaChNum   = 1U;
    uint32_t                    edmaTccNum  = 1U;
    uint32_t                    edmaEvtqNum = 0U;
    uint32_t                    isTesocEnabled;
    uint32_t                    timeValSblEnd;
    uint32_t                    timeValAppImgLoadStart, timeValAppImgLoadEnd;
    uint32_t                    timeValSblInitEnd;
    uint32_t                    timeValSocInitStart, timeValSocInitEnd;
    uint32_t                    timeValDdrConfigStart, timeValDdrConfigEnd;
    uint32_t                    timeValSlaveCoreBootupStart,
                                timeValSlaveCoreBootupEnd;
    volatile uint32_t           spin           = 1U;
    sbllibEntryPoints_t         sblEntryPoints = {0U};
    sbllibAppImageParseParams_t appImgParams;
    EntryFuncPtr_t              ipu1Core0EntryFuncPtr;
    pmhalPrcmSysClkVal_t        sysClkFreq = PMHALCMGetSysClockFreqEnum();
#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    uint32_t                    timeValEccInitStart, timeValEccInitEnd;
#endif

#if defined (SBL_DEV_BUILD)
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_DEV;
#else
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_PROD;
#endif

    siliconPackageType = SBLLibGetSiliconPackageType();

    /* Check if TESOC is enabled by SBL */
    isTesocEnabled = SBLIsTesocEnabled();

    /* Read the opp for which the SBL has been compiled */
    oppId = SBLGetOppId(siliconPackageType);

    if (SBLLIB_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n Identified 12X12 Silicon \n");
    }
    else /* SBLLIB_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n Identified 15X15 Silicon \n");
    }

    /* Configure Voltage Rails : Done after DPLL_PER to make sure
     * the I2C1 gets the 96 MHz clock.
     */
    retVal += SBLUtilsConfigAllVoltageRails(oppId);

    /* Enable the Power Domains */
    retVal += SBLUtilsConfigPowerDomains();

    /* Print error in case initial configuration not done correctly */
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n SBL Initial Config After TESOC IPU Test Failed \n");
        SBLLibAbortBoot();
    }

    timeValSblInitEnd = SBLUtilsRead32KTimer();

    timeValSocInitStart = SBLUtilsRead32KTimer();

    if (TRUE == isTesocEnabled)
    {
        /* Configure DPLL DDR and DPLL GMAC to OPP NOM. */
        SBLUtilsConfigMultiOppDpll(SBLLIB_PRCM_DPLL_OPP_NOM);
        SblConfigAndInitiateOtherTesocTests();
        /* Re Configure DPLL DDR and DPLL GMAC based on OPP after other tesoc tests. */
        if (SBLLIB_PRCM_DPLL_OPP_NOM != oppId)
        {
            SBLUtilsConfigMultiOppDpll(oppId);
        }
    }
    else
    {
        /* Skipping other TESOC BISTs */
        /* Configure DPLL DDR and DPLL GMAC. */
        SBLUtilsConfigMultiOppDpll(oppId);
    }

    /* Enable the Clock Domains */
    SBLUtilsConfigClockDomains();

    /* Enable the Modules */
    SBLUtilsConfigModules();

    /* Configure PADs for TI TDA3xx EVM */
    SBLConfigTIEVMPad();

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n TI EVM PAD Configuration Completed \n");

    timeValSocInitEnd = SBLUtilsRead32KTimer();

    timeValDdrConfigStart = SBLUtilsRead32KTimer();

    if (SBLLIB_SILICON_PACKAGE_TYPE_12X12 == siliconPackageType)
    {
        /*Configure LPDDR2 */
        #if (SBLLIB_DDR_TYPE_LPDDR2 == SBL_LIB_CONFIG_DDR_TYPE_12X12)
        SBLUtilsLPDDR2Config(
            (uint32_t) SBL_LIB_CONFIG_DDR_SPEED_12X12);
        #else
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Invalid DDR Type \n");
        SBLLibAbortBoot();
        #endif
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n DDR Configuration Completed \n");
    }
    else /* SBLLIB_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType */
    {
        /* Configure DDR */
        #if (SBLLIB_DDR_TYPE_DDR2 == SBL_LIB_CONFIG_DDR_TYPE)
        SBLUtilsDDR2Config(SBL_LIB_CONFIG_DDR_SPEED);
        #elif (SBLLIB_DDR_TYPE_DDR3 == SBL_LIB_CONFIG_DDR_TYPE)
        SBLUtilsDDR3Config(SBL_LIB_CONFIG_DDR_SPEED);
        #else
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Invalid DDR Type \n");
        SBLLibAbortBoot();
        #endif
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                     "\n DDR Configuration Completed \n");
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                 "\n TDA3xx SOC Init Completed \n");

    timeValDdrConfigEnd = SBLUtilsRead32KTimer();

#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    timeValEccInitStart = SBLUtilsRead32KTimer();

    /* Disable EMIF ECC */
    EMIFConfigECCDisableEcc(SOC_EMIF1_CONF_REGS_BASE);

    retVal = SBLUtilsEmifECCConfigure();

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EMIF ECC configuration failed \n");
    }

    timeValEccInitEnd = SBLUtilsRead32KTimer();
#endif

    timeValAppImgLoadStart = SBLUtilsRead32KTimer();

    /* Reset the slave cores */
    SBLLibResetAllSlaveCores();

#if (SBL_LIB_CONFIG_DSP1_PARITY_CHECK == 1)
    SBLUtilsInitDspL2RAM(SBLLIB_CORE_ID_DSP1);
#endif
#if (SBL_LIB_CONFIG_DSP2_PARITY_CHECK == 1)
    SBLUtilsInitDspL2RAM(SBLLIB_CORE_ID_DSP2);
#endif

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChNum,
                        edmaTccNum,
                        edmaEvtqNum);

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n App Image Download Begins \n");

    SBLLibAppImageParamsInit(&appImgParams);
#if (SBL_LIB_CONFIG_ENABLE_CRC == 1)
    SBLLibRegisterCRCCallback(&SBLUtilsComputeCRC);
    appImgParams.enableCrc = (uint32_t) TRUE;
#endif

#if !defined (DEVICE_TYPE_HS)
    SBLLibRegisterAuthenticateRPRCCallback(&SblDummyAuthenticateBinary);
#else
    SBLLibRegisterAuthenticateRPRCCallback(&SecurityLib_authenticateBinary);
#endif

    appImgParams.appImgMetaHeaderV1 = &sblAppMetaHeaderV1;
    appImgParams.appImgMetaHeaderV2 = &sblAppMetaHeaderV2;
    appImgParams.appImgRPRCHeader   = &sblAppRPRCHeader;
    appImgParams.entryPoints        = &sblEntryPoints;
    appImgParams.ddrAppImageAddress = SBLUtilsGetDDRAppCopyAddress();

#if defined SBL_TEST_AUTO_BUILD
    /*Load the Test Automation App Image*/
    retVal = SBLLoadTestAutoAppImage(&appImgParams, gWDTResetStatus);
#else
    /*Load the App Image */
    retVal = SBLLoadAppImage(&appImgParams);
#endif

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Valid App Image is not Available \n");
    }
    else
    {
        #if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_HIGH)
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n App Image Download Completed \n");
        #else
        if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
            (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0, load Completed\n");
        }
        else if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0 and IPU CPU1, load Completed\n");
        }
        else if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0, IPU CPU1 and DSP1, load Completed\n");
        }
        else if ((0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1]) &&
                 (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2]) &&
                 (0U == sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1]))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image only on IPU1 CPU0, IPU CPU1, DSP1 and DSP2, load Completed\n");
        }
        else
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_IMP_INFO,
                "\n Valid App Image on IPU1 CPU0, IPU CPU1, DSP1, DSP2 and EVE; load Completed\n");
        }
        #endif
    }

    timeValAppImgLoadEnd = SBLUtilsRead32KTimer();

    timeValSlaveCoreBootupStart = SBLUtilsRead32KTimer();

    SblConfigRGMIIPad();

    /* Evict the IPU1 Uni-cache */
    SBLUtilsEvictIPU1Unicache();

    /* Disable the IPU1 Uni-cache */
    SBLUtilsDisableIPU1Unicache();

    /* Invalidate the IPU1 Uni-cache */
    SBLUtilsInvalidateIPU1Unicache();

    SBLLibDSP1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1],
                      sblBuildMode);

    SBLLibDSP2BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2],
                      sblBuildMode);

    SBLLibEVE1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1],
                      sblBuildMode);

#if !(defined (SBL_TEST_AUTO_BUILD))
    /* Enable the IPU1 Uni-cache */
    SBLUtilsEnableIPU1Unicache();
#endif

#if (SBL_LIB_CONFIG_DSP_1000GHZ_EVE_900MHZ == (1U))
    if (oppId == SBLLIB_PRCM_DPLL_OPP_HIGH)
    {
	pmhalPrcmDpllConfig_t *dpllParams;
        retVal = SBLUtilsConfigureDspEveMux(oppId, siliconPackageType);
        /* Configure DPLL GMAC */
        retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_DSP_GMAC,
                                         sysClkFreq,
                                         oppId,
                                         &dpllParams);

        retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_DSP_GMAC,
                                       dpllParams,
                                       PM_TIMEOUT_INFINITE);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n DPLL GMAC not configured Correctly \n");
            SBLLibAbortBoot();
        }
        /* Configure DPLL EVE_VID_DSP */
        retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                                         sysClkFreq,
                                         oppId,
                                         &dpllParams);

        retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_EVE_VID_DSP,
                                       dpllParams,
                                       PM_TIMEOUT_INFINITE);
    }
#endif

    timeValSlaveCoreBootupEnd = SBLUtilsRead32KTimer();

    EDMA3Deinit(SOC_EDMA_TPCC_BASE_VIRT, 0);

    if (TRUE == SBL_LOCK_MMR)
    {
        /* Lock the MMR registers */
        SBLLibLockControlModuleMMR();
    }

    timeValSblEnd = SBLUtilsRead32KTimer();

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n*****************************************************************\n");
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n 32K Timer is used to measure cycles, divide by 32K to get time in seconds \n");
    SblPrintBootCycles("Reset to SBL Init Cycles", timeValSblStart);
#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 1)
    if (TRUE == isTesocEnabled)
    {
        SblPrintBootCycles(
            "SBL Initial Config Cycles including IPU TESOC and IPU RAM ECC",
            (timeValSblInitEnd - timeValSblInitStart));
        SblPrintBootCycles("SBL IPU BIST Cycles including IPU RAM ECC Cycles",
                           (timeValIPUBistEnd - timeValIPUBistStart));
        SblPrintBootCycles("IPU RAM ECC Cycles",
                           (timeValIPURAMEccConfigEnd -
                            timeValIPURAMEccConfigStart));
    }
    else
    {
        SblPrintBootCycles(
            "SBL Initial Config Cycles including IPU RAM ECC Cycles",
            (timeValSblInitEnd - timeValSblInitStart));
        SblPrintBootCycles("IPU RAM ECC Cycles",
                           (timeValIPURAMEccConfigEnd -
                            timeValIPURAMEccConfigStart));
    }
#endif
#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 0)
    if (TRUE == isTesocEnabled)
    {
        SblPrintBootCycles("SBL Initial Config Cycles including IPU TESOC BIST",
                           (timeValSblInitEnd - timeValSblInitStart));
        SblPrintBootCycles("SBL IPU BIST Cycles",
                           (timeValIPUBistEnd - timeValIPUBistStart));
    }
    else
    {
        SblPrintBootCycles("SBL Initial Config Cycles",
                           (timeValSblInitEnd - timeValSblInitStart));
    }
#endif
    if (TRUE == isTesocEnabled)
    {
        SblPrintBootCycles(
            "SOC Init Cycles Including TESOC Tests other than IPU",
            (timeValSocInitEnd - timeValSocInitStart));
        SblPrintBootCycles("TESOC Tests other than IPU Cycles",
                           (timeValOtherTesocTestEnd -
                            timeValOtherTesocTestStart));
    }
    else
    {
        SblPrintBootCycles("SOC Init Cycles",
                           (timeValSocInitEnd - timeValSocInitStart));
    }
    SblPrintBootCycles("DDR Config Clock Cycles",
                       (timeValDdrConfigEnd - timeValDdrConfigStart));
#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    SblPrintBootCycles("ECC Initialization Cycles",
                       (timeValEccInitEnd - timeValEccInitStart));
#endif
    SblPrintBootCycles("App Image Load Cycles",
                       (timeValAppImgLoadEnd - timeValAppImgLoadStart));
    SblPrintBootCycles("Slave Core Bootup Cycles",
                       (timeValSlaveCoreBootupEnd - timeValSlaveCoreBootupStart));
    SblPrintBootCycles("SBL Boot-up Cycles", (timeValSblEnd - timeValSblStart));
    SblPrintBootCycles("Time at which SBL started IPU1_0", timeValSblEnd);
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n*****************************************************************\n");

#if (SBL_LIB_CONFIG_DISABLE_UNICACHE == 1)
    /* Evict the IPU1 Uni-cache */
    SBLUtilsEvictIPU1Unicache();

    /* Disable the IPU1 Uni-cache */
    SBLUtilsDisableIPU1Unicache();

    /* Invalidate the IPU1 Uni-cache */
    SBLUtilsInvalidateIPU1Unicache();
#endif
#if (SBL_LIB_CONFIG_DISABLE_AMMU == 1)
    /* AMMU can be disabled only when the optimization level is lower than
     * optimization level high. Otherwise IPU1 Core1 should wait until IPU1
     * Core0 comes up and configures AMMU. Impact of disabling AMMU should be
     * analysed carefully before enabling this option
     */
    SBLUtilsDisableIPU1AMMU();
#endif /* SBL_LIB_CONFIG_DISABLE_AMMU == 1 */

    /* In case the SBL optimization level is high, IPU Core1 App has been booted
     * earlier itself before loading Image on any other cores. In other cases
     * the IPU Core1 App boots takes place here
     */
#if (SBL_OPT_LEVEL < SBLLIB_OPT_LEVEL_HIGH)
    /* Set the entry point for IPU1 Core 1 */
    if (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1])
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Jumping to IPU1 CPU1 App \n");
        HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                    sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1]);
    }
    else
    {
        /* Set while(1) loop */
        HW_WR_REG32((SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE - 1U), 0xE7FEE7FEU);

        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n No IPU1 CPU1 App Found, Switching to while Loop \n");
        HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                    SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE);
    }
#endif

#if defined SBL_TEST_AUTO_BUILD
    /* Test environment configuration for Test Automation*/
    SBLTestAutoEnvCfg();
#endif

    /* Jump to IPU1 Core 0's entry point */
    if (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0])
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Jumping to IPU1 CPU0 App \n");
        UARTWaitUntilTransmitComplete();
        ipu1Core0EntryFuncPtr =
            (EntryFuncPtr_t) (sblEntryPoints.entryPoint[
                                  SBLLIB_CORE_ID_IPU1_CPU0]);
        ipu1Core0EntryFuncPtr();
    }

    while (0U != spin)
    {
        /* To remove MISRA C error */
    }
}

static void SblPrintBootCycles(const char *cyclesString, uint32_t bootCycles)
{
    uint32_t cyclesInMsInt        = 0U, cyclesInMsFrac = 0U;
    char     bootCyclesStr[8]     = {0}, cyclesInMsIntStr[8] = {0},
             cyclesInMsFracStr[8] = {0};

    cyclesInMsInt = (bootCycles * 1000U) / SBL_32KTIMER_REFERENCE_VAL;

    cyclesInMsFrac =
        (((bootCycles *
           1000U) %
          SBL_32KTIMER_REFERENCE_VAL) * 100U) / SBL_32KTIMER_REFERENCE_VAL;

    snprintf(bootCyclesStr, (size_t) 8, "%d", bootCycles);
    snprintf(cyclesInMsIntStr, (size_t) 8, "%d", cyclesInMsInt);
    snprintf(cyclesInMsFracStr, (size_t) 8, "%02d", cyclesInMsFrac);

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, "\n ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, cyclesString);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, " - ");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, bootCyclesStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, "  (");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, cyclesInMsIntStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, ".");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, cyclesInMsFracStr);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO, " ms) \n");
}

static void SblConfigAndInitiateOtherTesocTests(void)
{
    int32_t        retVal = STW_SOK;
    tesocTestCfg_t tesocTestConfig;

    /* Test Start Time-stamp */
    timeValOtherTesocTestStart = SBLUtilsRead32KTimer();

    tesocTestConfig.testId = TESOC_TEST_ID_ISSDSSVIP;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_ISSDSSVIP, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISSDSSVIP TESOC Test Failed to Start/Finish \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISSDSSVIP TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_ISS;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_ISS, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISS TESOC Test Failed to Start/Finish \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n ISS TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_DSS;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_DSS, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSS TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSS TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_VIP;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_VIP, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n VIP TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n VIP TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_DSP1;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_DSP1, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP1 TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP1 TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_DSP2;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_DSP2, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP2 TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n DSP2 TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    tesocTestConfig.testId = TESOC_TEST_ID_EVE;
    /* Configure and enable TESOC HS divider */
    PMHALCMDpllSetClockDivider(PMHAL_PRCM_DIV_TESOC_EXT_CLK, (uint32_t) 1U);

    retVal  = TESOCGetDefaultSliceInfo(SOC_TESOC_BASE, &tesocTestConfig);
    retVal += SBLLibRunTesocTest(TESOC_TEST_ID_EVE, &tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE TESOC Test Failed to Start/Finish  \n");
        SBLLibAbortBoot();
    }

    retVal = SBLLibCheckTesocTestResult(&tesocTestConfig);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EVE TESOC Test Result: FAIL \n");
        SBLLibAbortBoot();
    }

    /* Test Complete Time-stamp */
    timeValOtherTesocTestEnd = SBLUtilsRead32KTimer();
}

#if (SBL_LIB_CONFIG_ENABLE_IPU_RAM_ECC == 1)
static void SblConfigIpuRamECC(void)
{
    uint32_t          srcBuffAddr = 0x0U;
    eccIpuMemCfgPrm_t cfgPrm;

    /* Clear older IPU L2RAM ECC Err status */
    ECCIPUMemClrErrStatus(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L2RAM);

    /* Clear older IPU L1DATA ECC Err status */
    ECCIPUMemClrErrStatus(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1DATA);

    /* Clear older IPU L1TAG ECC Err status */
    ECCIPUMemClrErrStatus(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);

    /* Disable ECC for IPU L2RAM */
    ECCIPUMemEnableEcc(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) FALSE,
                       ECC_IPU_MEM_TYPE_L2RAM);

    /* Disable ECC for IPU L1DATA */
    ECCIPUMemEnableEcc(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) FALSE,
                       ECC_IPU_MEM_TYPE_L1DATA);

    /* Disable ECC for IPU L1TAG */
    ECCIPUMemEnableEcc(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) FALSE,
                       ECC_IPU_MEM_TYPE_L1TAG);

    /* Make sure the Cache is empty before priming */
    UNICACHEWriteBackAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                         UNICACHE_WAIT_INFINITE);
    UNICACHEInvalidateAll(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          UNICACHE_WAIT_INFINITE);
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);

    /* Make current page non-cacheable */
    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_MED_POLICY(0U),
                  IPU_MED_POLICY_L1_CACHEABLE,
                  IPU_MED_POLICY_L1_CACHEABLE_DISABLE);
    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_MED_POLICY(0U),
                  IPU_MED_POLICY_L1_POSTED,
                  IPU_MED_POLICY_L1_POSTED_NON_POSTED);

    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);

    /* Enable ECC for IPU L2RAM / L1DATA / L1TAG */
    ECCIPUMemEnableEcc(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) TRUE,
                       ECC_IPU_MEM_TYPE_L2RAM);
    ECCIPUMemEnableEcc(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) TRUE,
                       ECC_IPU_MEM_TYPE_L1DATA);
    ECCIPUMemEnableEcc(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                       (uint32_t) TRUE,
                       ECC_IPU_MEM_TYPE_L1TAG);

    /* Enable EDMA module */
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TPCC,
                       PMHAL_PRCM_MODULE_MODE_AUTO,
                       PM_TIMEOUT_INFINITE);
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC1,
                       PMHAL_PRCM_MODULE_MODE_AUTO,
                       PM_TIMEOUT_INFINITE);
    PMHALModuleModeSet(PMHAL_PRCM_MOD_TPTC2,
                       PMHAL_PRCM_MODULE_MODE_AUTO,
                       PM_TIMEOUT_INFINITE);

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

    srcBuffAddr = (uint32_t) (gEmifEccInitBuff) + 0x40000000U;

    /* Prefill the IPU RAM (64 KB) using EDMA */
    SBLUtilsPreFillECCMemory((const void *) (SBLLIB_SOC_L3_IPU1_RAM_BASE),
                             (const void *) srcBuffAddr,
                             SBL_IPU1_RAM_SIZE);

    /* Prefill the IPU Cache (32 KB) */
    UNICACHEPreload(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                    SBLLIB_SOC_IPU_RAM_BASE,
                    SBL_IPU1_RAM_SIZE,
                    UNICACHE_WAIT_INFINITE);

    /* Clear IPU L1TAG ECC Err status which is generated during intialisation */
    ECCIPUMemClrErrStatus(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                          ECC_IPU_ERR_ALL,
                          ECC_IPU_MEM_TYPE_L1TAG);

    /* Clear Pending Interrupts in NVIC due to IPU L1TAG ECC Errors */
    Intc_IntClrPend(IPU_L1TAG_SEC_ERR_INT);
    Intc_IntClrPend(IPU_L1TAG_DED_ERR_INT);

    /* Enable auto correction in case of One Bit errors */
    cfgPrm.errAutoCorrectEnable = (uint32_t) TRUE;
    cfgPrm.sRespHFEnable        = (uint32_t) FALSE;
    cfgPrm.dataMask    = (uint32_t) FALSE;
    cfgPrm.eccCodeMask = (uint32_t) FALSE;
    cfgPrm.memType     = ECC_IPU_MEM_TYPE_L2RAM;
    ECCIPUMemConfig(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                    (const eccIpuMemCfgPrm_t *) &cfgPrm);
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1DATA;
    ECCIPUMemConfig(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                    (const eccIpuMemCfgPrm_t *) &cfgPrm);
    cfgPrm.memType = ECC_IPU_MEM_TYPE_L1TAG;
    ECCIPUMemConfig(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
                    (const eccIpuMemCfgPrm_t *) &cfgPrm);

    /* Make current page cacheable */
    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_MED_POLICY(0U),
                  IPU_MED_POLICY_L1_CACHEABLE,
                  IPU_MED_POLICY_L1_CACHEABLE_ENABLE);
    HW_WR_FIELD32(SOC_IPU1_UNICACHE_MMU_BASE + IPU_MED_POLICY(0U),
                  IPU_MED_POLICY_L1_POSTED,
                  IPU_MED_POLICY_L1_POSTED_POSTED);
}

#endif

static void SblStartIPUCore1(void)
{
    uint32_t ipuCore1StartAddr;

    /* Set IPU1 entry point to zero */
    HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS, 0x0U);
    #if defined (BOOTMODE_NOR)
    ipuCore1StartAddr = SBL_RBL_SLAVE_CORE_START_ADDRESS_NOR;
    #else
    ipuCore1StartAddr = SBL_RBL_SLAVE_CORE_START_ADDRESS_QSPI;
    #endif
    SBLUtilsWakeUpIPU1Core1(ipuCore1StartAddr);
}

#if !defined (DEVICE_TYPE_HS)
static int32_t SblDummyAuthenticateBinary(uint32_t address, uint32_t size)
{
    return STW_SOK;
}

#endif
