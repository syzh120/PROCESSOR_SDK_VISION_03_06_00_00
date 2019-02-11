/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file st_mcspiDiagLibTests.c
 *
 *  \brief Common across test-cases with DiagLib.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_i2c.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <st_mcspi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define EDMA3_CC_REGION_M4              (1U)

#define XBAR_CPU                        (CPU_IPU1)
#define XBAR_INST                       (XBAR_INST_IPU1_IRQ_35)
#define EDMA3_CC_XFER_COMPLETION_INT_M4 (35U)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static DiagLib_McspiTestParams_t *gMcspiTestParams;
static DiagLib_McspiObj_t gMcspiObj;
static volatile int32_t gTestStatus;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief Function to initialize MCSPI configuration.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void McSPIInit(void);
/**
 * \brief   This Interrupt Service Routine for EDMA RX completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppMcspiTransferIsr(void *handle);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibMcspiTest_main(st_MCSPITestcaseParams_t *testPrms)
{

    gMcspiTestParams = &testPrms->diagLibTestParams;

    uint32_t tx[1024U] = {0}, rx[1024U] = {0};

    gMcspiTestParams->txBuffer = tx;
    gMcspiTestParams->rxBuffer = rx;

    /* Perform Pin-Muxing for CS0 of SPI1 Instance */
    McSPIInit();

    if(gMcspiTestParams->performCacheOps == TRUE)
    {
        BspOsal_cacheWbInvAll();
        BspOsal_cacheEnable(BSP_OSAL_CT_ALL);
    }
    else
    {
        BspOsal_cacheDisable(BSP_OSAL_CT_ALL);
    }

    /* XBar configuration */
    if(gMcspiTestParams->transferMode == DIAGLIB_MCSPI_DMA_MODE)
    {
        EDMAsetRegion(EDMA3_CC_REGION_M4);
        EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

        if (irq_xbar_success ==
            IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                           XBAR_CPU, XBAR_INST,
                           EDMA_TPCC_IRQ_REGION1))
        {
            /* Enable interrupt for EDMA RX completion */
            Intc_Init();
            Intc_IntEnable(0);
            /* Register ISR */
            Intc_IntRegister(EDMA3_CC_XFER_COMPLETION_INT_M4,
                             (IntrFuncPtr) AppMcspiTransferIsr, 0);
            Intc_SystemEnable(EDMA3_CC_XFER_COMPLETION_INT_M4);

            if(gMcspiTestParams->baseAddr == SOC_MCSPI4_BASE)
            {
                /* Connect MCSPI4 event source to EDMA */
                DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                               XBAR_INST_DMA_EDMA_DREQ_22, MCSPI4_DREQ_TX0);
                DMAXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, EDMA,
                               XBAR_INST_DMA_EDMA_DREQ_23, MCSPI4_DREQ_RX0);
            }
        }
        else
        {
            printf("Error in configuring CrossBar.\n");
        }
    }

    gTestStatus = DiagLib_mcspiStartTest(gMcspiTestParams, &gMcspiObj);
    while (gTestStatus == 1U)
    {}

    testPrms->testResult = gTestStatus;

    /* Disable the interrupt */
    Intc_SystemDisable(EDMA3_CC_XFER_COMPLETION_INT_M4);

    /* Unregister the interrupt */
    Intc_IntUnregister(EDMA3_CC_XFER_COMPLETION_INT_M4);
    Intc_IntDisable();

}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void McSPIInit(void)
{
    int32_t retVal;
#if defined (SOC_TDA3XX)
    stwAppInitParams_t stwAppInitParams;

    StwUtils_appInitParams_init(&stwAppInitParams);
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        printf("\nSystem Init Failed \n");
    }
#endif

    /*Configure Pin mux for McSPI Instance 1 (McSPI1) */
    PlatformMCSPI1SetPinMux();

    /*Configure Pin mux for McSPI Instance 2 (McSPI2) */
    PlatformMCSPI2SetPinMux();

    /*Configure Pin mux for McSPI Instance 3 (McSPI3) */
    PlatformMCSPI3SetPinMux();

    /*Configure Pin mux for McSPI Instance 4 (McSPI4) */
    PlatformMCSPI4SetPinMux();

#if defined (SOC_TDA3XX)
    /* Set Board level Muxes for SPI1 and SPI2 */
    BOARDSelectDevice(DEVICE_ID_MCSPI, DEVICE_MCSPI_INST_ID_1);

    BOARDSelectDevice(DEVICE_ID_MCSPI, DEVICE_MCSPI_INST_ID_2);
#endif
    /* Enable MCSPI 1 module */
    if(gMcspiTestParams->baseAddr == SOC_MCSPI1_BASE)
    {
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCSPI1,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            printf("Error in MCSPI 1 module enable.\n");
        }
    }

    /* Enable MCSPI 2 module */
    else if(gMcspiTestParams->baseAddr == SOC_MCSPI2_BASE)
    {
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCSPI2,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            printf("Error in MCSPI 2 module enable.\n");
        }
    }

    /* Enable MCSPI 3 module */
    else if(gMcspiTestParams->baseAddr == SOC_MCSPI3_BASE)
    {
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCSPI3,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            printf("Error in MCSPI 3 module enable.\n");
        }
    }

    /* Enable MCSPI 3 module */
    else if(gMcspiTestParams->baseAddr == SOC_MCSPI4_BASE)
    {
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCSPI4,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (PM_SUCCESS != retVal)
        {
            printf("Error in MCSPI 4 module enable.\n");
        }
    }

    /* power on the EDMA */
    PlatformEDMAWkupDepEnable();

}

static void AppMcspiTransferIsr(void *handle)
{
    gTestStatus = DiagLib_mcspiISR(gMcspiTestParams, &gMcspiObj);
}
