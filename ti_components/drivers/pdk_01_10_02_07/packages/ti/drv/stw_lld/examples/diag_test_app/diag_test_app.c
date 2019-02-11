/*
 *  Copyright (c) Texas Instruments Incorporated 2015-2017
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
 *  \file     diag_test_app.c
 *
 *  \brief    This file contains test code for diagLib for all modules.
 *
 *  \details  Internal pad loopback is run by configuring the same signal
 *  as both input and output.
 *  Values of the Tx and Rx buffers are comapred.
 *
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/pm/pmhal.h>

#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#include <ti/drv/stw_lld/platform/platform.h>

#include <ti/drv/vps/include/osal/bsp_osal.h>

#if defined (SOC_TDA3XX)
#include <ti/drv/stw_lld/uartconsole/uartConsole.h>
#include <ti/diag/diagLib_adc.h>
#include <ti/diag/diagLib_crc.h>
#include <ti/drv/stw_lld/platform/stw_platform.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#endif
#include <ti/diag/diagLib_ecc.h>
#include <ti/diag/diagLib_mcspi.h>
#include <ti/diag/diagLib_can.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define EDMA3_CC_REGION_M4              (1U)
#define XBAR_CPU                        (CPU_IPU1)

/* IRQ Instances for Safety IP modules */
#define XBAR_INST_ADC                   (XBAR_INST_IPU1_IRQ_34)
#define XBAR_INST_CRC                   (XBAR_INST_IPU1_IRQ_35)
#define XBAR_INST_EDMA                  (XBAR_INST_IPU1_IRQ_36)
#define XBAR_INST_ECC_EMIF              (XBAR_INST_IPU1_IRQ_37)
#define XBAR_INST_ECC_OCMC              (XBAR_INST_IPU1_IRQ_25)

/* IRQ numbers for Safety IP modules */
#define DIAGLIB_APP_ADC_INT             (34U)
#define DIAGLIB_APP_CRC_INT             (35U)
#define DIAGLIB_APP_EDMA3_INT           (36U)
#define EMIF_ECC_ERR_INT                (37U)
#define OCMC_RAM_ECC_ERR_INT            (25U)
#define ABORT_INT                       (160U)

/* Default EMIF Macro definitions */
#define DIAGLIB_APP_EMIF_START_ADDR             (0x80000000)
#define DIAGLIB_APP_EMIF_ECC_1B_ERR_THRSH_VAL   (0x1)
#define DIAGLIB_APP_EMIF_ECC_START_ADDR         (0x90000000)
#define DIAGLIB_APP_EMIF_ECC_END_ADDR           (0x9001FFFF)
#define DIAGLIB_APP_EMIF_ECC_ERR_ADDR           (0x90000100)

/* Default OCMC Macro definitions */
#define DIAGLIB_APP_OCMC_ECC_START_ADDR         (0x40311100)

/* Macros to enable Test and repective ISR */
#define MODULE_TEST_DISABLED             (0x0U)
#define MODULE_TEST_ENABLED              (0xAU)
#define MODULE_ISR_ENABLED               (0xBU)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* Variables for ADC diagLib */
#if defined (SOC_TDA3XX)
static DiagLib_AdcStartupParams_t    gStartupParams;
static DiagLib_AdcTestParams_t       gInputParams;
static DiagLib_AdcTestResultParams_t gOutputParams[DIAGLIB_ADC_MAX_NUM_CH];
static volatile DiagLib_AdcObj_t     gAdcObj;
static volatile int32_t gAdcTest = MODULE_TEST_ENABLED;

/* Variables for CRC diagLib */
static DiagLib_CrcTestParams_t       gCrcTestParams;
static DiagLib_CrcOutParams_t        gCrcOutParams;
static DiagLib_CrcObj_t gCrcObj;
static volatile int32_t gCrcTest = MODULE_TEST_ENABLED;
#endif

/* Variables for McSPI diagLib */
static DiagLib_McspiTestParams_t     gTestParams;
static DiagLib_McspiObj_t gMcspiObj;
static volatile int32_t gSpiTest = MODULE_TEST_ENABLED;

/* Variables for ECC diagLib */
static DiagLib_EccTestParams_t       gEccTestParams;
static volatile DiagLib_EccObj_t     gEccObj;
static volatile int32_t gEccEmifTest = MODULE_TEST_ENABLED;
static volatile int32_t gEccOcmcTest = MODULE_TEST_ENABLED;

/* Variable for CAN diaglib */
static DiagLib_CanTestParam_t        gCanTestParam;
static volatile int32_t gCanTest = MODULE_TEST_ENABLED;

/* Status variable */
static volatile int32_t gTestStatus;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief Function to initialize UART console.
 *
 * \param   none.
 *
 * \retval  status          Configuration status.
 */
static int32_t UARTInit(void);
/**
 * \brief Function to initialize safety IP configuration.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DiagAppInit(void);
/**
 * \brief Function to de-initialize safety IP configuration.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void DiagAppDeinit(void);
/**
 * \brief   Function to unclock crossbar interrupts from different
 *          safety IP modules.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppIrqConnect(void);
/**
 * \brief   This function is to enable or disable given interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void eccEnableIntr(uint32_t intrNum, uint32_t enable);
/**
 * \brief   Function to unlock CAN IP crossbar interrupts.
 *
 * \param   Enum for the type of test #DiagLib_CanTestType_t.
 *
 * \retval  none.
 */
static void AppCanIrqConnect(uint32_t canBase, uint32_t testType);

/**
 * \brief   This function is to enable or disable given interrupt.
 *
 * \param   TRUE/FALSE for Enable/Disable.
 *
 * \retval  none.
 */
static void canEnableIntr(uint32_t enable);

/**
 * \brief   This is common Interrupt Service Routine for all registered
 *          interrupts.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void isrDiagTest(void *handle);

/**
 * \brief   Function to test the Internal loop back for SOC_DCAN1_BASE
 *
 * \param   none.
 *
 * \retval  none.
 */
static void Dcan1IntLoopbackTest();

/**
 * \brief   Function to test the External loop back for SOC_DCAN1_BASE
 *
 * \param   none.
 *
 * \retval  none.
 */
static void Dcan1ExtLoopbackTest();

/**
 * \brief   Function to test single/double bit parity error for SOC_DCAN1_BASE
 *
 * \param   none.
 *
 * \retval  none.
 */
static void Dcan1ParityTest();

/**
 * \brief   Function to test the Internal loop back for SOC_DCAN2_BASE
 *
 * \param   none.
 *
 * \retval  none.
 */
static void Dcan2IntLoopbackTest();

/**
 * \brief   Function to test the External loop back for SOC_DCAN2_BASE
 *
 * \param   none.
 *
 * \retval  none.
 */
static void Dcan2ExtLoopbackTest();

/**
 * \brief   Function to test single/double bit parity error for SOC_DCAN2_BASE
 *
 * \param   none.
 *
 * \retval  none.
 */
static void Dcan2ParityTest();

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t main(void)
{
    emifEccCfgPrm_t          cfgPrm;
    emifEccAddrRangeCfgPrm_t addrRangeCfgPrm;

    /* Unlock Pad Config Registers */
    PlatformUnlockMMR();
    /* UART init */
    if (UARTInit() == STW_SOK)
    {
        EDMAsetRegion(EDMA3_CC_REGION_M4);
        EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

        UARTPuts("\r\nStarting application...\r\n", -1);

        /* Perform required Pin-Muxing and power on the safety IPs */
        DiagAppInit();

        AppIrqConnect();

        /* Disable cache for ECC DiagLib Test.
         * TODO: Disabling cache is giving hard fault. Needs to be fixed.
         * without this re run hangs.
         *       BspOsal_cacheWbInvAll();
         *       BspOsal_cacheDisable(BSP_OSAL_CT_ALL);
         */

        /* ECC DiagLib Test */
        #if defined (SOC_TDA2EX)
            if(PLATFORM_SILICON_PACKAGE_TYPE_17X17 == PlatformGetSiliconPackageType())
            {
                /* EMIF ECC not supported for TDA2ex 17x17 EVM. */
                gEccEmifTest = MODULE_TEST_DISABLED;
            }
        #endif
        if (MODULE_TEST_ENABLED == gEccEmifTest)
        {
            eccEnableIntr(EMIF_ECC_ERR_INT, TRUE);
            gEccEmifTest = MODULE_ISR_ENABLED;

            DiagLibEccTestParams_init(&(gEccTestParams));

            cfgPrm.addrRangeCfgPrm = &addrRangeCfgPrm;

            cfgPrm.emifStartAddr = DIAGLIB_APP_EMIF_START_ADDR;
            cfgPrm.addrRangeCfgPrm->startAddr =
                DIAGLIB_APP_EMIF_ECC_START_ADDR;
            cfgPrm.addrRangeCfgPrm->endAddr         = DIAGLIB_APP_EMIF_ECC_END_ADDR;
            cfgPrm.addrRangeCfgPrm->addrRangeNum    = EMIF_ECC_ADDR_RANGE_NUM_1;
            cfgPrm.addrRangeCfgPrm->addrRangeType   = EMIF_ECC_ADDR_RANGE_WITHIN;
            cfgPrm.addrRangeCfgPrm->enableAddrRange = TRUE;
            cfgPrm.thresholdVal = DIAGLIB_APP_EMIF_ECC_1B_ERR_THRSH_VAL;
            cfgPrm.enableRmw    = 1U;            

            EMIFConfigECCInitECCParams(SOC_EMIF1_CONF_REGS_BASE, &cfgPrm);
        #if defined (SOC_TDA2PX)
            gEccTestParams.emifPrm.eccEmifErrAddr =
                (void *) DIAGLIB_APP_EMIF_ECC_ERR_ADDR;
            gEccTestParams.eccErrCheckMode = DIAGLIB_ECC_INTERRUPT_MODE;
            gEccTestParams.testType        =
                DIAGLIB_ECC_TEST_EMIF_SUB_QUANTA_WRITE;

            gTestStatus = DiagLib_eccStartTest(&gEccTestParams,
                                               (DiagLib_EccObj_t *) &gEccObj);
            while (gTestStatus == DIAGLIB_ECC_TEST_PENDING)
            {}

            if (gTestStatus == STW_SOK)
            {
                UARTPuts("EMIF ECC Sub Quanta Write test successful\r\n", -1);
            }
            else
            {
                UARTPuts("EMIF ECC Sub Quanta Write test failed\r\n", -1);
            }
        #endif
            gEccTestParams.emifPrm.eccEmifErrAddr =
                (void *) DIAGLIB_APP_EMIF_ECC_ERR_ADDR;
            gEccTestParams.eccErrCheckMode = DIAGLIB_ECC_INTERRUPT_MODE;
            gEccTestParams.testType        =
                DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE;

            gTestStatus = DiagLib_eccStartTest(&gEccTestParams,
                                               (DiagLib_EccObj_t *) &gEccObj);
            while (gTestStatus == DIAGLIB_ECC_TEST_PENDING)
            {}

            if (gTestStatus == STW_SOK)
            {
                UARTPuts(
                    "EMIF ECC Non Quanta Multiple address write test interrupt mode successful\r\n",
                    -1);
            }
            else
            {
                UARTPuts(
                    "EMIF ECC Non Quanta Multiple address write test interrupt mode failed\r\n",
                    -1);
            }
            eccEnableIntr(EMIF_ECC_ERR_INT, FALSE);

            /* DED Error will generate hard fault. Register the interrupt handler
            * for HF interrupt(M4) or Abort Interrupt (A15) insted of DED ERR INT */
        #if defined (__TI_ARM_V7M4__)
            eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, TRUE);
        #elif defined (__ARM_ARCH_7A__)
            eccEnableIntr(ABORT_INT, TRUE);
        #endif

            gEccTestParams.emifPrm.eccEmifErrAddr =
                (void *) DIAGLIB_APP_EMIF_ECC_ERR_ADDR;
            gEccTestParams.eccErrCheckMode = DIAGLIB_ECC_INTERRUPT_MODE;
            gEccTestParams.testType        = DIAGLIB_ECC_TEST_EMIF_DED;

            gTestStatus = DiagLib_eccStartTest(&gEccTestParams,
                                               (DiagLib_EccObj_t *) &gEccObj);
            while (gTestStatus == DIAGLIB_ECC_TEST_PENDING)
            {}

            if (gTestStatus == STW_SOK)
            {
                UARTPuts("EMIF ECC DED test interrupt mode successful\r\n", -1);
            }
            else
            {
                UARTPuts("EMIF ECC DED test interrupt mode failed\r\n", -1);
            }
            gEccEmifTest = MODULE_TEST_ENABLED;
        #if defined (__TI_ARM_V7M4__)
            eccEnableIntr(EXCEPTION_M4_HARD_FAULT_NUM_3, FALSE);
        #elif defined (__ARM_ARCH_7A__)
            eccEnableIntr(ABORT_INT, FALSE);
        #endif

            gEccTestParams.emifPrm.eccEmifErrAddr =
                (void *) DIAGLIB_APP_EMIF_ECC_ERR_ADDR;
            gEccTestParams.eccErrCheckMode = DIAGLIB_ECC_POLLED_MODE;
            gEccTestParams.testType        = DIAGLIB_ECC_TEST_EMIF_SEC;

            gTestStatus = DiagLib_eccStartTest(&gEccTestParams,
                                               (DiagLib_EccObj_t *) &gEccObj);
            while (gTestStatus == DIAGLIB_ECC_TEST_PENDING)
            {}

            if (gTestStatus == STW_SOK)
            {
                UARTPuts("EMIF ECC SEC test polled mode successful\r\n", -1);
            }
            else
            {
                UARTPuts("EMIF ECC SEC test polled mode failed\r\n", -1);
            }
            gEccEmifTest = MODULE_TEST_DISABLED;
            eccEnableIntr(EMIF_ECC_ERR_INT, FALSE);
        }

        if (MODULE_TEST_ENABLED == gEccOcmcTest)
        {
            eccEnableIntr(OCMC_RAM_ECC_ERR_INT, TRUE);
            gEccOcmcTest = MODULE_ISR_ENABLED;

            DiagLibEccTestParams_init(&(gEccTestParams));

            gEccTestParams.ocmcPrm.eccOcmcMode = DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK;

            /*OCMC Ecc SEC test */
            gEccTestParams.ocmcPrm.eccOcmcRamErrAddr =
                (DIAGLIB_APP_OCMC_ECC_START_ADDR + 0x04U);
            gEccTestParams.eccErrCheckMode = DIAGLIB_ECC_INTERRUPT_MODE;
            gEccTestParams.testType        = DIAGLIB_ECC_TEST_OCMC_SEC;
            gTestStatus = DiagLib_eccStartTest(&gEccTestParams,
                                               (DiagLib_EccObj_t *) &gEccObj);
            while (gTestStatus == DIAGLIB_ECC_TEST_PENDING)
            {}

            if (gTestStatus == STW_SOK)
            {
                UARTPuts("OCMC ECC SEC test in interrupt mode successful\r\n", -1);
            }
            else
            {
                UARTPuts("OCMC ECC SEC test in interrupt mode failed\r\n", -1);
            }
            gEccOcmcTest = MODULE_TEST_DISABLED;
            eccEnableIntr(OCMC_RAM_ECC_ERR_INT, FALSE);
        }

        /* CAN diagLib test */
        if (MODULE_TEST_ENABLED == gCanTest)
        {
            gCanTest = MODULE_ISR_ENABLED;
            /* Internal loop-back test for SOC_DCAN1_BASE */
            Dcan1IntLoopbackTest();

            /* External loop-back test for SOC_DCAN1_BASE */
            Dcan1ExtLoopbackTest();

            /* single/double bit Parity test for SOC_DCAN1_BASE */
            Dcan1ParityTest();
        #if defined (SOC_TDA3XX)
            /* skip dcan 2 test cases for tda3xx PG 2.0 */
            if (PlatformGetSiliconRev() < 2U)
            {
        #endif
                /* Internal loop-back test for SOC_DCAN2_BASE */
                Dcan2IntLoopbackTest();

                /* External loop-back test for SOC_DCAN2_BASE */
                Dcan2ExtLoopbackTest();

                /* single/double bit Parity test for SOC_DCAN2_BASE */
                Dcan2ParityTest();
        #if defined (SOC_TDA3XX)
            }
        #endif

            /* Test completed */
            gCanTest = MODULE_TEST_DISABLED;
        }

        BspOsal_cacheWbInvAll();
        BspOsal_cacheEnable(BSP_OSAL_CT_ALL);
    #if defined (SOC_TDA3XX)
        if (MODULE_TEST_ENABLED == gAdcTest)
        {
            eccEnableIntr(DIAGLIB_APP_ADC_INT, TRUE);
            gAdcTest = MODULE_ISR_ENABLED;

            DiagLibAdcStartupParams_init(&gStartupParams);

            gTestStatus = DiagLib_adcStartup(&gStartupParams);
            if (STW_SOK != gTestStatus)
            {
                UARTPuts("Error in ADC divider configuration.\r\n", -1);
            }
            else
            {
                DiagLibAdcTestParams_init(&gInputParams);

                /* Configure ADC */
                /* step 3 configuration */
                /* TDA3xx RevD board: VDD_CORE_AVS is available across ADC_IN2 */
                gInputParams.chCfg[0].channel = ADC_CHANNEL_3;
                gInputParams.chCfg[0].expVltg = (uint32_t)
                    HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                  CTRL_CORE_STD_FUSE_OPP_VMIN_2,
                                  CTRL_CORE_STD_FUSE_OPP_VMIN_2);
                gInputParams.vltgDev          = 20U;

                /* Test 1: SingleShot mode Multi channel Interrupt mode*/
                gInputParams.numCh        = 1U;
                gInputParams.transferMode = DIAGLIB_ADC_INTERRUPT_MODE;
                gTestStatus = DiagLib_adcStartTest(&gInputParams, gOutputParams,
                                                   (DiagLib_AdcObj_t *) &gAdcObj);

                while (DIAGLIB_ADC_TEST_PENDING == gTestStatus)
                {}

                if (gTestStatus == STW_SOK)
                {
                    UARTPuts(
                        "SingleShot mode Single channel Interrupt mode successful\r\n",
                        -1);
                }
                else
                {
                    UARTPuts(
                        "SingleShot mode Single channel Interrupt mode failed\r\n",
                        -1);
                    UARTPuts(
                        "This example(as it is) will pass only on TDA3xx Rav.D Board and above.\r\n",
                        -1);
                    UARTPuts(
                        "Try running this application on TDA3xx Rev.D and above\r\n",
                        -1);
                }

                gAdcTest = 0;

                /* Test 2: Continuous mode Multi channel Polled mode*/
                gInputParams.transferMode = DIAGLIB_ADC_POLLED_MODE;
                gInputParams.numCh        = 1U;
                gInputParams.mode         = ADC_OPERATION_MODE_CONTINUOUS;
                gInputParams.numLoop      = 6U;
                gInputParams.timeout      = 600U;
                gTestStatus = DiagLib_adcStartTest(&gInputParams, gOutputParams,
                                                   (DiagLib_AdcObj_t *) &gAdcObj);

                while (DIAGLIB_ADC_TEST_PENDING == gTestStatus)
                {}

                if (gTestStatus == STW_SOK)
                {
                    UARTPuts(
                        "Continuous mode Single channel Polled mode successful\r\n",
                        -1);
                }
                else
                {
                    UARTPuts("Continuous mode Single channel Polled mode failed\r\n",
                             -1);
                    UARTPuts(
                        "This example(as it is) will pass only on TDA3xx Rav.D Board and above.\r\n",
                        -1);
                    UARTPuts(
                        "Try running this application on TDA3xx Rev.D and above\r\n",
                        -1);
                }
            }

            /* Power down ADC */
            DiagLib_adcShutdown(&gInputParams);
            eccEnableIntr(DIAGLIB_APP_ADC_INT, FALSE);
        }

        if (MODULE_TEST_ENABLED == gCrcTest)
        {
            eccEnableIntr(DIAGLIB_APP_CRC_INT, TRUE);
            gCrcTest = MODULE_ISR_ENABLED;

            DiagLibCrcTestParams_init(&gCrcTestParams);

            /* Test1: Semi CPU 32bit Inbuilt Compare HW CRC value with Golden CRC in
             *interrupt mode */
            gCrcTestParams.testType     = DIAGLIB_CRC_TEST_INBUILT;
            gCrcTestParams.mode         = CRC_OPERATION_MODE_SEMICPU;
            gCrcTestParams.bitSize      = DIAGLIB_CRC_BIT_32;
            gCrcTestParams.crcCheckMode = DIAGLIB_CRC_INTERRUPT_MODE;
            gTestStatus = DiagLib_crcStartTest(&gCrcTestParams, &gCrcOutParams,
                                               &gCrcObj);
            while (DIAGLIB_CRC_TEST_PENDING == gTestStatus)
            {}
            if (gTestStatus == STW_SOK)
            {
                UARTPuts(
                    "CRC HW compare with Golden CRC in semi CPU mode inbuilt successful \r\n",
                    -1);
            }
            else
            {
                UARTPuts(
                    "CRC HW compare with Golden CRC in semi CPU mode inbuilt failed\r\n",
                    -1);
            }
            gCrcTest = MODULE_TEST_DISABLED;
            eccEnableIntr(DIAGLIB_APP_CRC_INT, FALSE);
        }
    #endif

        if (MODULE_TEST_ENABLED == gSpiTest)
        {
            eccEnableIntr(DIAGLIB_APP_EDMA3_INT, TRUE);
            gSpiTest = MODULE_ISR_ENABLED;

            DiagLibMcspiTestParams_init(&gTestParams);

            gTestParams.performCacheOps = TRUE;
            gTestParams.txBuffer        = (uint32_t *) calloc(gTestParams.dataCount,
                                                              sizeof (uint32_t));
            gTestParams.rxBuffer = (uint32_t *) calloc(gTestParams.dataCount,
                                                       sizeof (uint32_t));

            /* Test 1: MCSPI 1 Internal loopback mode 0 dma mode clk 48MHz */
            gTestParams.transferMode = DIAGLIB_MCSPI_DMA_MODE;
            gTestStatus = DiagLib_mcspiStartTest(&gTestParams, &gMcspiObj);
            while (gTestStatus == 1U)
            {}

            if (gTestStatus == STW_SOK)
            {
                UARTPuts(
                    "MCSPI 1 channel 0 mode 0 32bit dma mode at 48MHz successful\r\n",
                    -1);
            }
            else
            {
                UARTPuts(
                    "MCSPI 1 channel 0 mode 0 32bit dma mode at 48MHz failed\r\n",
                    -1);
            }
            gSpiTest    = MODULE_TEST_DISABLED;
            eccEnableIntr(DIAGLIB_APP_EDMA3_INT, FALSE);
        }

        DiagAppDeinit();
    }


    UARTPuts("Application completed \r\n", -1);

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void Dcan1IntLoopbackTest()
{
    gTestStatus = DIAGLIB_CAN_TEST_OK;

    PlatformDcanClkConfig(0);

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN1RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux */
    PlatformDCAN1SetPinMux();

    /* Assign the type of test */
    gCanTestParam.testType = DIAGLIB_CAN_TEST_INT_LOOPBACK;

    gCanTestParam.canBase = SOC_DCAN1_BASE;

    AppCanIrqConnect(gCanTestParam.canBase, gCanTestParam.testType);

    canEnableIntr(TRUE);

    if (DIAGLIB_CAN_TEST_OK == gTestStatus)
    {
        gTestStatus = DiagLib_canTestParamsInit(&gCanTestParam);
    }

    if (DIAGLIB_CAN_TEST_OK != gTestStatus)
    {
        UARTPuts("DCAN1 internal loopback test failed\r\n", -1);
    }
    else
    {
        gTestStatus = DiagLib_canStartTest(&gCanTestParam);
        while (DIAGLIB_CAN_TEST_PENDING == gTestStatus)
        {
            /* Wait for the test to complete */
        }
        if (DIAGLIB_CAN_TEST_OK == gTestStatus)
        {
            UARTPuts("DCAN1 internal loopback test successful\r\n", -1);
        }
        else
        {
            UARTPuts("DCAN1 internal loopback test failed\r\n", -1);
        }
    }

    canEnableIntr(FALSE);
}

static void Dcan1ExtLoopbackTest()
{
    gTestStatus = DIAGLIB_CAN_TEST_OK;

    PlatformDcanClkConfig(0);

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN1RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Assign the type of test */
    gCanTestParam.testType = DIAGLIB_CAN_TEST_EXT_LOOPBACK;

    gCanTestParam.canBase = SOC_DCAN1_BASE;

    /* Unlock crossbar for CAN module */
    AppCanIrqConnect(gCanTestParam.canBase, gCanTestParam.testType);

    canEnableIntr(TRUE);

    if (DIAGLIB_CAN_TEST_OK == gTestStatus)
    {
        gTestStatus = DiagLib_canTestParamsInit(&gCanTestParam);
    }

    if (DIAGLIB_CAN_TEST_OK != gTestStatus)
    {
        UARTPuts("DCAN1 external loopback test failed\r\n", -1);
    }
    else
    {
        gTestStatus = DiagLib_canStartTest(&gCanTestParam);
        while (DIAGLIB_CAN_TEST_PENDING == gTestStatus)
        {
            /* Wait for the test to complete */
        }
        if (DIAGLIB_CAN_TEST_OK == gTestStatus)
        {
            UARTPuts("DCAN1 external loopback test successful\r\n", -1);
        }
        else
        {
            UARTPuts("DCAN1 external loopback test failed\r\n", -1);
        }
    }

    canEnableIntr(FALSE);
}

static void Dcan1ParityTest()
{
    int32_t status = 0;

    gTestStatus = DIAGLIB_CAN_TEST_OK;

    PlatformDcanClkConfig(0);

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN1RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Assign the type of test */
    gCanTestParam.testType = DIAGLIB_CAN_PARITY_ECC_TEST;

    gCanTestParam.canBase = SOC_DCAN1_BASE;

    /* Unlock crossbar for CAN module */
    AppCanIrqConnect(gCanTestParam.canBase, gCanTestParam.testType);

    canEnableIntr(TRUE);

    if (DIAGLIB_CAN_TEST_OK == gTestStatus)
    {
        gTestStatus = DiagLib_canTestParamsInit(&gCanTestParam);
    }

    if (DIAGLIB_CAN_TEST_OK != gTestStatus)
    {
        UARTPuts("DCAN1 ECC parity test failed\r\n", -1);
    }
    else
    {
        status = DiagLib_canStartTest(&gCanTestParam);
        if (status != DIAGLIB_CAN_TEST_PENDING)
        {
            gTestStatus = DIAGLIB_CAN_TEST_FAIL;
        }
#if defined (SOC_TDA3XX)
        while (((0 == (gTestStatus & DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED))
                || (0 == (gTestStatus & DIAGLIB_CAN_PARITY_DBE_ISR_RECEIVED)))
               && (DIAGLIB_CAN_TEST_FAIL != gTestStatus))
#else
        while ((0 == (gTestStatus & DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED))
               && (DIAGLIB_CAN_TEST_FAIL != gTestStatus))
#endif
        {
            /* Wait for the test to complete */
        }
        if (DIAGLIB_CAN_TEST_FAIL == gTestStatus)
        {
            UARTPuts("DCAN1 ECC parity test failed\r\n", -1);
        }
        else
        {
#if defined (SOC_TDA3XX)
            status = DiagLib_canParityVerifyData(&gCanTestParam);
            if (DIAGLIB_CAN_TEST_OK == status)
            {
                UARTPuts("DCAN1 ECC parity test successful\r\n", -1);
            }
            else
            {
                UARTPuts("DCAN1 ECC parity test failed\r\n", -1);
            }
#else
            UARTPuts("DCAN1 ECC parity test successful\r\n", -1);
#endif
        }
    }

    canEnableIntr(FALSE);
}

static void Dcan2IntLoopbackTest()
{
    gTestStatus = DIAGLIB_CAN_TEST_OK;

    PlatformDcanClkConfig(1);

    /* Clock Configuration. */
    PlatformDCAN2PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN2RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(1);

    /* Perform the DCAN pinmux. */
    PlatformDCAN2SetPinMux();

    /* Assign the type of test */
    gCanTestParam.testType = DIAGLIB_CAN_TEST_INT_LOOPBACK;

    gCanTestParam.canBase = SOC_DCAN2_BASE;

    /* Unlock crossbar for CAN module */
    AppCanIrqConnect(gCanTestParam.canBase, gCanTestParam.testType);

    canEnableIntr(TRUE);

    if (DIAGLIB_CAN_TEST_OK == gTestStatus)
    {
        gTestStatus = DiagLib_canTestParamsInit(&gCanTestParam);
    }

    if (DIAGLIB_CAN_TEST_OK != gTestStatus)
    {
        UARTPuts("DCAN2 internal loopback test failed\r\n", -1);
    }
    else
    {
        gTestStatus = DiagLib_canStartTest(&gCanTestParam);
        while (DIAGLIB_CAN_TEST_PENDING == gTestStatus)
        {
            /* Wait for the test to complete */
        }
        if (DIAGLIB_CAN_TEST_OK == gTestStatus)
        {
            UARTPuts("DCAN2 internal loopback test successful\r\n", -1);
        }
        else
        {
            UARTPuts("DCAN2 internal loopback test failed\r\n", -1);
        }
    }

    canEnableIntr(FALSE);
}

static void Dcan2ExtLoopbackTest()
{
    gTestStatus = DIAGLIB_CAN_TEST_OK;

    PlatformDcanClkConfig(1);

    /* Clock Configuration. */
    PlatformDCAN2PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN2RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(1);

    /* Perform the DCAN pinmux. */
    PlatformDCAN2SetPinMux();

    /* Assign the type of test */
    gCanTestParam.testType = DIAGLIB_CAN_TEST_EXT_LOOPBACK;

    gCanTestParam.canBase = SOC_DCAN2_BASE;

    /* Unlock crossbar for CAN module */
    AppCanIrqConnect(gCanTestParam.canBase, gCanTestParam.testType);

    canEnableIntr(TRUE);

    if (DIAGLIB_CAN_TEST_OK == gTestStatus)
    {
        gTestStatus = DiagLib_canTestParamsInit(&gCanTestParam);
    }

    if (DIAGLIB_CAN_TEST_OK != gTestStatus)
    {
        UARTPuts("DCAN2 external loopback test failed\r\n", -1);
    }
    else
    {
        gTestStatus = DiagLib_canStartTest(&gCanTestParam);
        while (DIAGLIB_CAN_TEST_PENDING == gTestStatus)
        {
            /* Wait for the test to complete */
        }
        if (DIAGLIB_CAN_TEST_OK == gTestStatus)
        {
            UARTPuts("DCAN2 external loopback test successful\r\n", -1);
        }
        else
        {
            UARTPuts("DCAN2 external loopback test failed\r\n", -1);
        }
    }

    canEnableIntr(FALSE);
}

static void Dcan2ParityTest()
{
    int32_t status = 0;

    gTestStatus = DIAGLIB_CAN_TEST_OK;

    PlatformDcanClkConfig(1);

    /* Clock Configuration. */
    PlatformDCAN2PrcmEnable();

    /* Perform the DCAN pinmux - RX pin as Driver OFF / GPIO pinmux. */
    PlatformDCAN2RXSetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(1);

    /* Perform the DCAN pinmux. */
    PlatformDCAN2SetPinMux();

    /* Assign the type of test */
    gCanTestParam.testType = DIAGLIB_CAN_PARITY_ECC_TEST;

    gCanTestParam.canBase = SOC_DCAN2_BASE;

    /* Unlock crossbar for CAN module */
    AppCanIrqConnect(gCanTestParam.canBase, gCanTestParam.testType);

    canEnableIntr(TRUE);

    if (DIAGLIB_CAN_TEST_OK == gTestStatus)
    {
        gTestStatus = DiagLib_canTestParamsInit(&gCanTestParam);
    }

    if (DIAGLIB_CAN_TEST_OK != gTestStatus)
    {
        UARTPuts("DCAN2 ECC parity test failed\r\n", -1);
    }
    else
    {
        status = DiagLib_canStartTest(&gCanTestParam);
        if (status != DIAGLIB_CAN_TEST_PENDING)
        {
            gTestStatus = DIAGLIB_CAN_TEST_FAIL;
        }

#if defined (SOC_TDA3XX)
        while (((0 == (gTestStatus & DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED))
                || (0 == (gTestStatus & DIAGLIB_CAN_PARITY_DBE_ISR_RECEIVED)))
               && (DIAGLIB_CAN_TEST_FAIL != gTestStatus))
#else
        while ((0 == (gTestStatus & DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED))
               && (DIAGLIB_CAN_TEST_FAIL != gTestStatus))
#endif
        {
            /* Wait for the test to complete */
        }
        if (DIAGLIB_CAN_TEST_FAIL == gTestStatus)
        {
            UARTPuts("DCAN2 ECC parity test failed\r\n", -1);
        }
        else
        {
#if defined (SOC_TDA3XX)
            status = DiagLib_canParityVerifyData(&gCanTestParam);
            if (DIAGLIB_CAN_TEST_OK == status)
            {
                UARTPuts("DCAN2 ECC parity test successful\r\n", -1);
            }
            else
            {
                UARTPuts("DCAN2 ECC parity test failed\r\n", -1);
            }
#else
            UARTPuts("DCAN2 ECC parity test successful\r\n", -1);
#endif
        }
    }

    canEnableIntr(FALSE);
}

static int32_t UARTInit(void)
{
    int32_t status = STW_SOK;
#if defined (SOC_TDA3XX)
    int32_t retVal;
    boardInitParams_t    boardInitPrms;
    deviceInitParams_t   deviceInitPrms;
    platformInitParams_t platInitPrms;


    BoardInitParams_init(&boardInitPrms);
    retVal = BOARDInit(&boardInitPrms);
    if (STW_SOK == retVal)
    {
        PLATFORMInitParams_init(&platInitPrms);
        retVal = PLATFORMInit(&platInitPrms);
        if (STW_SOK != retVal)
        {
            status = STW_EFAIL;
        }
    }
    else
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == retVal)
    {
        DEVICEInitParams_init(&deviceInitPrms);

        deviceInitPrms.isI2cProbingReq = (uint32_t) FALSE;

        retVal += DEVICEInit(&deviceInitPrms);
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            status = STW_EFAIL;
        }
    }

    if (status == STW_SOK)
    {
        BOARDConfigModulePinMux(DEVICE_ID_UART, DEVICE_UART_INST_ID_2,
                                BOARD_MODE_DEFAULT);
        BOARDSelectDevice(DEVICE_ID_UART, DEVICE_UART_INST_ID_2);

        UARTConsoleInit(UART2_INST);
        UARTPuts("\r\nUart Init Done \r\n", -1);
    }
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (status == STW_SOK)
    {
        PlatformUART1SetPinMux();

        UARTStdioInit();
        UARTPuts("\r\nUart Init Done \r\n", -1);
    }
#endif

    return status;
}
static void DiagAppInit(void)
{
    int32_t retVal;

#if defined (SOC_TDA3XX)
    /* Enable ADC module */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        UARTPuts("Error in ADC module enable.\r\n", -1);
        gAdcTest = -1;
    }

    /* Enable CRC module */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_CRC,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        UARTPuts("Error in CRC module enable.\r\n", -1);
        gCrcTest = -1;
    }
#endif

    /*Configure Pin mux for McSPI Instance 1 (McSPI1) */
    PlatformMCSPI1SetPinMux();

#if defined (SOC_TDA3XX)
    /* Set Board level Muxes for SPI1 and SPI2 */
    BOARDSelectDevice(DEVICE_ID_MCSPI, DEVICE_MCSPI_INST_ID_1);
#endif
    /* Enable MCSPI 1 module */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCSPI1,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        UARTPuts("Error in MCSPI 1 module enable.\r\n", -1);
        gSpiTest = -1;
    }

    /* power on the EDMA */
    PlatformEDMAWkupDepEnable();
}

static void DiagAppDeinit(void)
{
#if defined (SOC_TDA3XX)
    int32_t retVal;

    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_ADC,
                                PMHAL_PRCM_MODULE_MODE_DISABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        UARTPuts("Error in ADC module disable.\r\n", -1);
    }

    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_CRC,
                                PMHAL_PRCM_MODULE_MODE_DISABLED,
                                PM_TIMEOUT_INFINITE);
    if (PM_SUCCESS != retVal)
    {
        UARTPuts("Error in CRC module disable.\r\n", -1);
    }
#endif
}

static void AppIrqConnect(void)
{
#if defined (SOC_TDA3XX)
    /* XBar configuration for ADC*/
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_INST_ADC,
                       TSC_ADC_IRQ_GENINT))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring ADC CrossBar.\r\n", -1);
        gAdcTest = -1;
    }

    /* Unlock crossbar register for CRC */
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       XBAR_CPU, XBAR_INST_CRC, CRC_IRQ_CH1_CPR_COMP))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring CRC CrossBar.\r\n", -1);
        gCrcTest = -1;
    }
#endif

    /* Unlock crossbar register for EDMA */
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, XBAR_CPU,
                       XBAR_INST_EDMA, EDMA_TPCC_IRQ_REGION1))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring EDMA CrossBar.\r\n", -1);
        gSpiTest = -1;
    }

    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, XBAR_CPU,
                       XBAR_INST_ECC_EMIF, EMIF1_IRQ))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring EMIF CrossBar.\r\n", -1);
        gEccEmifTest = -1;
    }

    /*XBAR Configuration for OCMC*/
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, XBAR_CPU,
                       XBAR_INST_ECC_OCMC, OCMC_RAM1_IRQ))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring EMIF CrossBar.\r\n", -1);
        gEccOcmcTest = -1;
    }

    Intc_Init();
    Intc_IntEnable(0);
}

static void AppCanIrqConnect(uint32_t canBase, uint32_t testType)
{
    xbar_irq_t intrSource = IRQ_XBAR_RSVD;

    if (SOC_DCAN1_BASE == canBase)
    {
        if (DIAGLIB_CAN_PARITY_ECC_TEST == testType)
        {
            intrSource = DCAN1_IRQ_PARITY;
        }
        else
        {
            intrSource = DCAN1_IRQ_INT0;
        }
    }

    if (SOC_DCAN2_BASE == canBase)
    {
        if (DIAGLIB_CAN_PARITY_ECC_TEST == testType)
        {
            intrSource = DCAN2_IRQ_PARITY;
        }
        else
        {
            intrSource = DCAN2_IRQ_INT0;
        }
    }

    if (intrSource == IRQ_XBAR_RSVD)
    {
        UARTPuts("Error in configuring CAN Interrupt.\n", -1);
        gTestStatus = DIAGLIB_CAN_TEST_FAIL;
    }

    /* XBar configuration for CAN*/
#if defined (__TI_ARM_V7M4__)
    if ((gTestStatus != DIAGLIB_CAN_TEST_FAIL) &&
        (irq_xbar_success ==
         IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                        CPU_IPU1,
                        XBAR_INST_IPU1_IRQ_28,
                        intrSource)))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring CAN CrossBar.\n", -1);
        gTestStatus = DIAGLIB_CAN_TEST_FAIL;
    }

#elif defined (__ARM_ARCH_7A__)
    if ((gTestStatus != DIAGLIB_CAN_TEST_FAIL) &&
        (irq_xbar_success ==
         IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                        CPU_MPUSS,
                        XBAR_INST_MPU_IRQ_77,
                        intrSource))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTPuts("Error in configuring CAN CrossBar.\n", -1);
        gTestStatus = DIAGLIB_CAN_TEST_FAIL;
    }

#endif

    Intc_IntEnable(0);
}

static void canEnableIntr(uint32_t enable)
{
    uint32_t intrNum = 0;

#if defined (__TI_ARM_V7M4__)
    intrNum = 28;
#elif defined (__ARM_ARCH_7A__)
    intrNum = 77;
#endif

    if (TRUE == enable)
    {
        /* Enable the given interrupt */
        Intc_IntEnable(0);

        Intc_IntRegister(intrNum, (IntrFuncPtr) isrDiagTest, NULL);

        Intc_IntPrioritySet(intrNum, 1, 0);
        Intc_SystemEnable(intrNum);
    }
    else
    {
        /* Disable the interrupt */
        Intc_SystemDisable(intrNum);

        /* Unregister the interrupt */
        Intc_IntUnregister(intrNum);

        Intc_IntDisable();
    }
}

static void eccEnableIntr(uint32_t intrNum, uint32_t enable)
{
    if (TRUE == enable)
    {
        /* Enable the given interrupt */
        Intc_IntEnable(0);

        Intc_IntRegister(intrNum, (IntrFuncPtr) isrDiagTest, NULL);

        Intc_IntPrioritySet(intrNum, 1, 0);
        Intc_SystemEnable(intrNum);
    }
    else
    {
        /* Disable the interrupt */
        Intc_SystemDisable(intrNum);

        /* Unregister the interrupt */
        Intc_IntUnregister(intrNum);

        Intc_IntDisable();
    }
}

static void isrDiagTest(void *handle)
{
    int32_t status;

#if defined (SOC_TDA3XX)
    if (gAdcTest == MODULE_ISR_ENABLED)
    {
        gTestStatus = DiagLib_adcProcISR(&gInputParams, gOutputParams,
                                         (DiagLib_AdcObj_t *) &gAdcObj);
    }
    else if (gCrcTest == MODULE_ISR_ENABLED)
    {
        gTestStatus = DiagLib_crcISR(&gCrcTestParams, &gCrcOutParams, &gCrcObj);
    }
    else if (gSpiTest == MODULE_ISR_ENABLED)
#elif defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (gSpiTest == MODULE_ISR_ENABLED)
#endif
    {
        gTestStatus = DiagLib_mcspiISR(&gTestParams, &gMcspiObj);
    }
    else if ((gEccEmifTest == MODULE_ISR_ENABLED) ||
             (gEccOcmcTest == MODULE_ISR_ENABLED))
    {
        gTestStatus = DiagLib_eccISR(&gEccTestParams,
                                     (DiagLib_EccObj_t *) &gEccObj);
    }
    else if (gCanTest == MODULE_ISR_ENABLED)
    {
        status = DiagLib_canISR(&gCanTestParam);
        if (DIAGLIB_CAN_LOOPBACK_VERIFIED == status)
        {
            gTestStatus = DIAGLIB_CAN_TEST_OK;
        }
        else if ((DIAGLIB_CAN_PARITY_SBE_ISR_RECEIVED == status)
                 || (DIAGLIB_CAN_PARITY_DBE_ISR_RECEIVED == status))
        {
            /* Set corresponding bit of gTestStatus */
            gTestStatus = (gTestStatus | status);
        }
        else if (DIAGLIB_CAN_TEST_PENDING == status)
        {
            /* Do nothing */
        }
        else
        {
            gTestStatus = DIAGLIB_CAN_TEST_FAIL;
        }
    }
    else
    {
        gTestStatus = -1;
    }
}
