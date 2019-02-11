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
 *  \file     sbl_tda2xx_main.c
 *
 *  \brief    This file contains the SBL main function which calls the SOC Init
 *            and slave core boot up functions in sequence.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/stw_lld/uartconsole/uartConsole.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/csl_emif.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_tda2xx.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda2xx.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_ddr_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <sbl_tda2xx_priv.h>
#if defined (SBL_TEST_AUTO_BUILD)
#include <ti/boot/sbl_auto/sbl_app/src/test_auto/sbl_test_auto.h>
#endif

#if defined (BOOTMODE_QSPI)
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macro containing MPU frequency used to calculate SBL time */
#define MPU_TIMER_REFERENCE_VAL                     ((uint64_t) 750U * 1000U)

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
 * \brief   This function acts as a wrapper for SBL print function.
 *
 * \param   message       Message to be printed.
 *
 * \retVal  None.
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
 * \retVal  None.
 */
static void SblPrintBootCycles(const char *cyclesString, uint32_t bootCycles);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/*
 * Variable for version 1 of Meta Header structure
 */
sbllibMetaHeaderV1_t    sblAppMetaHeaderV1;

/*
 * Variable for version 2 of Meta Header structure
 */
sbllibMetaHeaderV2_t    sblAppMetaHeaderV2;

/*
 * Variable for RPRC Header structure
 */
sbllibRPRCImageHeader_t sblAppRPRCHeader;

/*
 * Variable for storing the AVS-0 status
 */
int32_t gSetVoltRailsStatus;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    int32_t                     retVal = STW_SOK;
    uint32_t                    oppId;
    uint32_t                    sblBuildMode;
    uint32_t                    edmaChNum   = 1U;
    uint32_t                    edmaTccNum  = 1U;
    uint32_t                    edmaEvtqNum = 0U;
    uint32_t                    timeValSblStart, timeValSblEnd;
    uint32_t                    timeValAppImgLoadStart, timeValAppImgLoadEnd;
    uint32_t                    timeValSblInitStart, timeValSblInitEnd;
    uint32_t                    timeValSocInitStart, timeValSocInitEnd;
    uint32_t                    timeValDdrConfigStart, timeValDdrConfigEnd;
    uint32_t                    timeValSlaveCoreBootupStart,
                                timeValSlaveCoreBootupEnd;
    uint32_t                    timeValStartIpu1_0;
    sbllibEntryPoints_t         sblEntryPoints =
    {{0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U}};
    sbllibAppImageParseParams_t appImgParams;
    pmhalPrcmDpllConfig_t      *dpllParams;
    EntryFuncPtr_t              mpuCore0EntryFuncPtr;
    pmhalPrcmSysClkVal_t        sysClkFreq = PMHALCMGetSysClockFreqEnum();

    /* For test automation, SBL Library Init Params are not needed which
     * disables SBL prints
     */
#if !(defined (SBL_TEST_AUTO_BUILD))
    sbllibInitParams_t          sblInitPrms;
    /* Default initialization of SBL Lib Params */
    SBLLibInitParamsInit(&sblInitPrms);
    /* Assign SBL Params */
    sblInitPrms.printFxn = &SblPrintFunction;
    SBLLibInit(&sblInitPrms);
#else
    uint32_t                    wdtResetStatus = 0;
    SBLLibInit(NULL);
#endif

#ifdef SBL_DEV_BUILD
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_DEV;
#else
    sblBuildMode = SBLLIB_SBL_BUILD_MODE_PROD;
#endif

    /* PMU Clock counter reset */
    ARM_CCNT_Enable();

    timeValSblStart     = ARM_CCNT_Read();
    timeValSblInitStart = ARM_CCNT_Read();

    /* Get SBL's OPP */
    oppId = SBLGetOppId();

    /* AVS-0 has already been done in NOR bootmode */
#if (defined (BOOTMODE_QSPI) || defined (BOOTMODE_SD))
    uint32_t                    bootMode;

    /* Initialize gSetVoltRailsStatus */
    gSetVoltRailsStatus = 0;

    /* Setting AVS Class-0 and the ABB for supported voltage rails */
    retVal = SBLUtilsConfigAllVoltageRails(oppId);

    if (PM_SUCCESS != retVal)
    {
        gSetVoltRailsStatus = STW_EFAIL;
    }
    else
    {
#if defined (SOC_TDA2PX)
        bootMode = SBLGetBootMode();
        SBLUtilsScaleIODelay(bootMode);
#else
        uint32_t                    siliconRev;

        siliconRev = SBLLibGetSiliconRev();
        /* Don't Recalibrate IO Delay for ES1.0 TDA2xx device*/
        if (0U != siliconRev)
        {
            bootMode = SBLGetBootMode();
            /* IO re-calibration is done for a sample pin configuration using
             * SR1.1 IO delay values. Update based on application pin mux
             * configuration and silicon revision
             */
            SBLUtilsScaleIODelay(bootMode);
        }
#endif
    }
#endif

    retVal = SBLUtilsConfigPowerDomains();

    /* Unlock MMR registers */
    SBLLibUnlockControlModuleMMR();

    /* Initializing the ARM Interrupt Controller */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Refresh the WDT to 3 mins & enable delay interrupt */
    SBLUtilsWDTimerBegin();

    /* Configure DPLL CORE */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_CORE,
                                     sysClkFreq,
                                     oppId,
                                     &dpllParams);

    /* This selects CORE_IPU_ISS_BOOST_CLK as IPU functional clock */
    PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX, PMHAL_PRCM_DPLL_CORE);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_CORE,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* Configure DPLL PER */
    retVal += SBLLibGetDpllStructure(PMHAL_PRCM_DPLL_PER,
                                     sysClkFreq,
                                     SBLLIB_PRCM_DPLL_OPP_NOM,
                                     &dpllParams);

    retVal += PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_PER,
                                   dpllParams,
                                   PM_TIMEOUT_INFINITE);

    /* UART Initialization */
#if defined (TDA2XX_MC_BUILD)
    SBLUtilsPrintfInit(UART3_INST);
#else
    SBLUtilsPrintfInit(UART1_INST);
#endif

#if defined (SOC_TDA2PX)
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO, "\n TDA2Px SBL Boot \n");
#else
#if defined (SOC_DRA75x)
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO, "\n DRA75x SBL Boot \n");
#else
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO, "\n TDA2xx SBL Boot \n");
#endif
#endif

    /* Open up firewalls if we are on HS devices.
     * This is an empty function for GP devices.
     */
    SBLLibHSOpenL3Firewalls();

    /* For TestAutomation : SBL checks for whether last reset is cold reset or
     * watchdog timer reset
     */
#if defined (SBL_TEST_AUTO_BUILD)
    wdtResetStatus = SBLTestAutoCheckWDTResetStatus();
#endif

    /* gSetVoltRailsStatus would have been set to 0 if AVS-0 and ABB are done
     * correctly, else it would have a value -1.
     */
    if ((0 != gSetVoltRailsStatus) || (STW_SOK != retVal))
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n SBL Initial Config Failed \n");
    }

    timeValSblInitEnd = ARM_CCNT_Read();

    timeValSocInitStart = ARM_CCNT_Read();

    /* Configure DPLLs */
    /* If the oppIs is OPP_PLUS, configure the clocks for OPP_NOM,
     * After all clocks are configured, reconfigure the clocks for OPP_PLUS. */
    if(oppId == SBLLIB_PRCM_DPLL_OPP_PLUS)
    {
        SBLUtilsConfigMultiOppDpll(SBLLIB_PRCM_DPLL_OPP_NOM);
        SBLUtilsConfigSingleOppDpll();
    }
    else
    {
        SBLUtilsConfigMultiOppDpll(oppId);
        SBLUtilsConfigSingleOppDpll();
    }

    /* Enable the Clock Domains */
    SBLUtilsConfigClockDomains();

    /* Enable the Modules */
    SBLUtilsConfigModules();

    /* Configure PADs for TI TDA3xx EVM */
#if defined (TDA2XX_MC_BUILD)
    SBLConfigTIMCEVMPad();
#else
    SBLConfigTIEVMPad();
#endif

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n TI EVM PAD Config Completed \n");

    retVal = SBLUtilsConfigStaticDependency();

    if (0 != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Static Dependency config Failed \n");
    }

    timeValSocInitEnd = ARM_CCNT_Read();

    timeValDdrConfigStart = ARM_CCNT_Read();

    /* Configure EMIF DDR3 */
    SBLUtilsDDR3Config((uint32_t) SBL_LIB_CONFIG_DDR_SPEED);

#if (SBL_LIB_CONFIG_ENABLE_EMIF_ECC == 1)
    /* Disable EMIF ECC */
    EMIFConfigECCDisableEcc(SOC_EMIF1_CONF_REGS_BASE);

    retVal = SBLUtilsEmifECCConfigure();

    if (0 != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n EMIF ECC configuration failed \n");
    }
#endif

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n DDR Config Completed \n");

    timeValDdrConfigEnd = ARM_CCNT_Read();

    timeValAppImgLoadStart = ARM_CCNT_Read();

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA, \
                        edmaChNum,
                        edmaTccNum,
                        edmaEvtqNum);

    /* Reset the slave cores */
    SBLLibResetAllSlaveCores();

#if (SBL_LIB_CONFIG_DSP1_PARITY_CHECK == 1)
    SBLUtilsInitDspL2RAM(SBLLIB_CORE_ID_DSP1);
#endif
#if (SBL_LIB_CONFIG_DSP2_PARITY_CHECK == 1)
    SBLUtilsInitDspL2RAM(SBLLIB_CORE_ID_DSP2);
#endif

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n App Image Download Begins \n");

    /* Initialize App Image Params */
    SBLLibAppImageParamsInit(&appImgParams);
    appImgParams.appImgMetaHeaderV1 = &sblAppMetaHeaderV1;
    appImgParams.appImgMetaHeaderV2 = &sblAppMetaHeaderV2;
    appImgParams.appImgRPRCHeader   = &sblAppRPRCHeader;
    appImgParams.entryPoints        = &sblEntryPoints;
    appImgParams.ddrAppImageAddress = SBLUtilsGetDDRAppCopyAddress();

#if defined SBL_TEST_AUTO_BUILD
    /*Load the Test Automation App Image*/
    retVal = SBLLoadTestAutoAppImage(&appImgParams, wdtResetStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n No valid Test Automation App Image is available \n");
    }
#else
    /* Load the App Image */
    retVal = SBLLoadAppImage(&appImgParams);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Valid App Image is not Available \n");
    }
    else
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n App Image Download Completed \n");
    }
#endif

    timeValAppImgLoadEnd = ARM_CCNT_Read();

    timeValSlaveCoreBootupStart = ARM_CCNT_Read();

#if defined (SBL_TEST_AUTO_BUILD)
    /* Test environment configuration for Test Automation */
    SBLTestAutoEnvCfg();
#else
    /* Refresh the WDT to 3 mins & disable DLY interrupt */
    SBLUtilsWDTimerEnd();
#endif

    /* Deinit the AINTC & Disable ARM IRQ */
    Intc_IntDisable();

    /* Release the slave cores out of reset */
    SBLLibMPUCPU1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_MPU_CPU1],
                         sblBuildMode);
    timeValStartIpu1_0 = SBLUtilsRead32KTimer();
    SBLLibIPUBringUp(SBLLIB_CORE_ID_IPU1,
                     sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU0],
                     sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU1_CPU1],
                     sblBuildMode);
    SBLLibIPUBringUp(SBLLIB_CORE_ID_IPU2,
                     sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU2_CPU0],
                     sblEntryPoints.entryPoint[SBLLIB_CORE_ID_IPU2_CPU1],
                     sblBuildMode);

    SBLLibDSP1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1],
                      sblBuildMode);
    SBLLibDSP2BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2],
                      sblBuildMode);
    SBLLibEVE1BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1],
                      sblBuildMode);
    SBLLibEVE2BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE2],
                      sblBuildMode);
#if defined (SOC_TDA2XX)
    SBLLibEVE3BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE3],
                      sblBuildMode);
    SBLLibEVE4BringUp(sblEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE4],
                      sblBuildMode);
#endif
    timeValSlaveCoreBootupEnd = ARM_CCNT_Read();

    /* For OPP_PLUS re configure the DPLLs at this point. */
    if(oppId == SBLLIB_PRCM_DPLL_OPP_PLUS)
    {
        SBLUtilsConfigMultiOppDpll(oppId);
    }

    EDMA3Deinit(SOC_EDMA_TPCC_BASE_VIRT, 0);

    timeValSblEnd = ARM_CCNT_Read();

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_IMP_INFO,
        "\n*****************************************************************\n");
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_IMP_INFO,
        "\n PMCCNTR counts once every 64 clock cycles, multiple by 64 to get actual CPU cycles \n");
    SblPrintBootCycles("SBL Initial Config Cycles",
                       (timeValSblInitEnd - timeValSblInitStart));
    SblPrintBootCycles("SOC Init Cycles",
                       (timeValSocInitEnd - timeValSocInitStart));
    SblPrintBootCycles("DDR Config Clock Cycles",
                       (timeValDdrConfigEnd - timeValDdrConfigStart));
    SblPrintBootCycles("App Image Load Cycles",
                       (timeValAppImgLoadEnd - timeValAppImgLoadStart));
    SblPrintBootCycles("Slave Core Bootup Cycles",
                       (timeValSlaveCoreBootupEnd - timeValSlaveCoreBootupStart));
    SblPrintBootCycles("SBL Boot-up Cycles", (timeValSblEnd - timeValSblStart));
    SblPrintBootCycles("Time at which SBL started IPU1_0", timeValStartIpu1_0);
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO,
        "\n*****************************************************************\n");

    /* Jump to MPU CPU0's entry point */
    if (0U != sblEntryPoints.entryPoint[SBLLIB_CORE_ID_MPU_CPU0])
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Jumping to MPU CPU0 App \n");
        UARTWaitUntilTransmitComplete();
        mpuCore0EntryFuncPtr =
            (EntryFuncPtr_t) (sblEntryPoints.entryPoint[
                                  SBLLIB_CORE_ID_MPU_CPU0]);
        mpuCore0EntryFuncPtr();
    }
    else
    {
#ifndef SBL_DEV_BUILD
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                     "\n Putting MPU in Retention... \n");

        MPU_WUGEN_0_DisableAll();

        PMHALPdmSetPDState(PMHAL_PRCM_PD_MPU,
                           PMHAL_PRCM_PD_STATE_RETENTION,
                           PM_TIMEOUT_NOWAIT);
        PMHALPdmSetLogicRetState(PMHAL_PRCM_PD_MPU,
                                 PMHAL_PRCM_PD_RET_STATUS_CSWR);

        PMHALPdmSetMemRetState(PMHAL_PRCM_PD_MPU,
                               PMHAL_PRCM_PHY_MEM_MPU_L2,
                               PMHAL_BANK_RET_ON);
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_MPU,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_NOWAIT);

        PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
#else
        volatile uint32_t spin = 1U;
        while (spin) ;
#endif
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void SblPrintBootCycles(const char *cyclesString, uint32_t bootCycles)
{
    /* For Test Automation : SBL prints are disabled */
#if !(defined (SBL_TEST_AUTO_BUILD))
    uint32_t cyclesInMsInt = 0U, cyclesInMsFrac = 0U;

    cyclesInMsInt =
        (uint32_t) (((uint64_t) bootCycles * 64U) / MPU_TIMER_REFERENCE_VAL);

    cyclesInMsFrac =
        (uint32_t) (((((uint64_t) bootCycles * 64U) % MPU_TIMER_REFERENCE_VAL)
                     * 100U) / MPU_TIMER_REFERENCE_VAL);

    UARTprintf("\n %s - %d  (%d.%02d ms)",
               cyclesString, bootCycles, cyclesInMsInt, cyclesInMsFrac);
#endif
}

#if !(defined (SBL_TEST_AUTO_BUILD))
static void SblPrintFunction(const char *message)
{
    UARTPuts(message, -((int32_t) 1));
}

#endif

