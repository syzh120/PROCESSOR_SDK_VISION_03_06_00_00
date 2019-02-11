/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#include "ecc_ocmc.h"

/* ----------------- Function prototypes ------------------ */
static int32_t ocmcRamSecErrTest(char ocmcEccMode);
static int32_t ocmcRamDedErrTest(char ocmcEccMode);
static int32_t ocmcRamAddrErrTest(char ocmcEccMode);

static void PlatformEDMAWkupDepEnable(void);
static int32_t ocmcRamInitEccMem();
/* -------------------------------------------------------- */

/* ----------------- Global variables ----------------- */
volatile uint32_t  gEccErrAddr       = 0;
uint32_t           gEccErrBitMask[4] = {0};
uint32_t           gOcmcEccMode;
uint32_t           gOcmcTestVal;

uint32_t           srcBuff[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
/* ---------------------------------------------------- */

/* Function handles OCMC ECC test submenu */
void mainSubMenuOcmcRamEccTest(char *option, char *mode)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** OCMC RAM ECC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. OCMC RAM SEC ERR ECC test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. OCMC RAM DED ERR ECC test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n3. OCMC RAM ADDRESS ERR ECC test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect OCMC RAM ECC TEST : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (OCMC_RAM_ECC_SEC_TEST == *option ||
            OCMC_RAM_ECC_DED_TEST == *option ||
            OCMC_RAM_ECC_ADDR_ERR_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nEnter Valid option\r\n", -1);
        }
    }

    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** OCMC RAM ECC MODE ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. OCMC FULL ECC Mode", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. OCMC BLOCK ECC Mode", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect OCMC RAM ECC MODE : ", -1);
        /* Get option */
        UARTConfigGets(uartBaseAddr, mode, 1);

        if (OCMC_RAM_FULL_ECC_MODE == *mode ||
            OCMC_RAM_BLOCK_ECC_MODE == *mode ||
            EXIT(*mode))
        {
            gOcmcEccMode = *mode;
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nEnter Valid option\r\n", -1);
        }
    }
}

/* Interrupt handler for OCMC Single bit error
 * Just checks and clears error status as the correction happens
 * automatically
 */
void isrOcmcRamSecErr()
{
    gEccErrAddr = OCMCEccErrTraceAddrGet(OCMC_RAM_APP_INST,
                                         OCMC_ECC_SEC_ERR);

    gEccErrBitMask[0] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_0);
    gEccErrBitMask[1] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_1);
    gEccErrBitMask[2] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_2);
    gEccErrBitMask[3] = OCMCSecEccErrDistributionStatusGet(
        OCMC_RAM_APP_INST,
        OCMC_ECC_SEC_ERR_DIST_3);

    OCMCEccErrClearTraceHist(OCMC_RAM_APP_INST,
                             OCMC_CLEAR_SEC_ERROR_HIST |
                             OCMC_CLEAR_SEC_BIT_DIST_HIST);

    OCMCIntStatusEnableClear(OCMC_RAM_APP_INST,
                             0,
                             OCMC_ECC_SEC_ERROR_FOUND);
}

/* Interrupt handler for OCMC Double bit error
 * This writes back the original pattern to fix error
 * NOTE: In real application this may need to be handled as a serious
 * error based on application needs.
 */
void isrOcmcRamDedErr()
{
    gTest_Addr = NULL;

    gEccErrAddr = OCMCEccErrTraceAddrGet(SOC_OCMC_RAM1_CFG_BASE,
                                         OCMC_ECC_DED_ERR);

    OCMCEccErrClearTraceHist(SOC_OCMC_RAM1_CFG_BASE,
                             OCMC_CLEAR_DED_ERROR_HIST);

    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0,
                             OCMC_ECC_DED_ERROR_FOUND);

    OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x18);
    gTest_Addr[0] = PATTERN_DATA;

    if (OCMC_RAM_FULL_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_FULL_ECC_ENABLE, 0, 1, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_BLOCK_ECC_ENABLE, 0, 1, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(SOC_OCMC_RAM1_CFG_BASE, 1, 0);
    }
}

/* Interrupt handler for OCMC Ram Address error
 * This writes back the original pattern to fix error
 * NOTE: In real application this may need to be handled as a serious
 * error based on application needs.
 */
void isrOcmcRamAddrErr()
{
    gTest_Addr = NULL;

    gEccErrAddr = OCMCEccErrTraceAddrGet(SOC_OCMC_RAM1_CFG_BASE,
                                         OCMC_ECC_ADDR_ERR);

    OCMCEccErrClearTraceHist(SOC_OCMC_RAM1_CFG_BASE,
                             OCMC_CLEAR_ADDR_ERROR_HIST);

    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0,
                             OCMC_ECC_ADDR_ERROR_FOUND);

    OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_NON_ECC_CODE_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x10);
    gTest_Addr[0] = gOcmcTestVal;

    if (OCMC_RAM_FULL_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_FULL_ECC_ENABLE, 0, 1, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == gOcmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_BLOCK_ECC_ENABLE, 0, 1, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(SOC_OCMC_RAM1_CFG_BASE, 1, 0);
    }
}

/* Function performs the OCMC ECC error test based on command line options
 */
int32_t ocmcRamEccTest(void)
{
    int32_t retVal = STW_SOK;
    char    mainSubMenuOption, ocmcEccMode;

    while (1)
    {
        mainSubMenuOcmcRamEccTest(&mainSubMenuOption, &ocmcEccMode);

        gEccErrAddr       = 0;
        gEccErrBitMask[0] = 0;
        gEccErrBitMask[1] = 0;
        gEccErrBitMask[2] = 0;
        gEccErrBitMask[3] = 0;

        if (OCMC_RAM_ECC_SEC_TEST == mainSubMenuOption)
        {
            retVal = ocmcRamSecErrTest(ocmcEccMode);
        }
        else if (OCMC_RAM_ECC_DED_TEST == mainSubMenuOption)
        {
            retVal = ocmcRamDedErrTest(ocmcEccMode);
        }
        else if (OCMC_RAM_ECC_ADDR_ERR_TEST == mainSubMenuOption)
        {
            retVal = ocmcRamAddrErrTest(ocmcEccMode);
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\n OCMC RAM ECC test exiting...", -1);
            break;
        }
    }
    return retVal;
}

/* Function to enable Wakeup Dependency fo EDMA */
static void PlatformEDMAWkupDepEnable(void)
{
    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC1_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC1_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPTC2_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPTC2_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }

    HW_WR_REG32(SOC_CORE_CM_CORE_BASE + PM_L3MAIN1_TPCC_WKDEP, 0x1);
    while ((HW_RD_REG32(SOC_CORE_CM_CORE_BASE +
                        PM_L3MAIN1_TPCC_WKDEP) & 0x00030000U) != 0x0)
    {
        ;
    }
}

/* Function Initializes OCMC memory with DMA */
static int32_t ocmcRamInitEccMem()
{
    volatile uint32_t i;
    EDMA3CCPaRAMEntry edmaParam;
    static uint32_t   blk_size = 0xFF;
    static int32_t    buf_size = BUFFER_SIZE;
    signed char      *srcBuff1;
    signed char      *dstBuff1;
    uint32_t          edma_ch_num   = 1;
    uint32_t          edma_evtq_num = 0;
    uint32_t          edma_tcc_num  = 1;
    uint32_t          aCnt          = 16;
    uint32_t          bCnt          = 1;
    uint32_t          cCnt          = 1;
    int32_t           retVal        = STW_SOK;

    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();

    EDMAsetRegion(EDMA3_CC_REGION);

    /* Do EDMA init Done once in the beginning of application */
    EDMA3Init(EDMA_APP_INST, 0);

    srcBuff1 = (signed char *) (srcBuff);
    dstBuff1 = (signed char *) (OCMC_RAM_ECC_START_ADDR);

    while (blk_size != 0)
    {
        EDMA3RequestChannel(EDMA_APP_INST, EDMA3_CHANNEL_TYPE_DMA, edma_ch_num,
                            edma_tcc_num, edma_evtq_num);

        edmaParam.opt      = 0;
        edmaParam.srcAddr  = (uint32_t) srcBuff1;
        edmaParam.destAddr = (uint32_t) dstBuff1;
        edmaParam.aCnt     = aCnt;
        edmaParam.bCnt     = bCnt;
        edmaParam.cCnt     = cCnt;
        edmaParam.srcBIdx  = aCnt;
        edmaParam.destBIdx = aCnt;
        edmaParam.srcCIdx  = aCnt;
        edmaParam.destCIdx = aCnt;
        edmaParam.linkAddr = 0xFFFFU;
        edmaParam.opt     |=
            (EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK |
             ((edma_tcc_num << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

        EDMA3SetPaRAM(EDMA_APP_INST, edma_ch_num, &edmaParam);

        /*
         * Transfer is done in a sync mode
         * Number of triggers required are bCnt * cCnt
         */
        for (i = 0; i < (bCnt * cCnt); i++)
        {
            EDMA3EnableTransfer(EDMA_APP_INST, edma_ch_num,
                                EDMA3_TRIG_MODE_MANUAL);

            while (0U == (EDMA3GetIntrStatus(EDMA_APP_INST) &
                          ((uint32_t) 1U << edma_ch_num)))
            {
                /* Busy Loop */
            }
            EDMA3ClrIntr(EDMA_APP_INST, edma_ch_num);
        }

        for (i = 0; i < (aCnt * bCnt * cCnt); i++)
        {
            if (srcBuff1[i] != dstBuff1[i])
            {
                retVal = STW_EFAIL;
                UARTConfigPuts(uartBaseAddr, "\r\nError matching value at src and dst address", -1);
                break;
            }
        }
        dstBuff1 += buf_size;
        blk_size -= buf_size;

        if ((blk_size < BUFFER_SIZE) && (blk_size % BUFFER_SIZE) != 0)
        {
            aCnt     = blk_size;
            buf_size = blk_size;
        }
    }
    return retVal;
}

/* Function performs OCMC single bit error test
 * Initializes memory and ECC, Inserts single bit error
 * and waits for handler to finish
 */
static int32_t ocmcRamSecErrTest(char ocmcEccMode)
{
    uint32_t testVal;
    uint32_t secAutoCorrectEn = 1;
    uint32_t eccErrIntEn      = 0;
    uint32_t i;
    uint32_t eccErrAddr;
    int32_t  retVal = STW_SOK;

    gEccErrAddr = 0;
    gTest_Addr  = NULL;

    for (i = 0; i < 4; i++)
    {
        gEccErrBitMask[i] = 0;
    }

#if defined (__TI_ARM_V7M4__)
    /*XBAR Configuration for OCMC*/
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1, OCMC_RAM_ECC_ERR_INT_INDEX, CSL_XBAR_OCMC_RAM1_IRQ);
#elif defined (__ARM_ARCH_7A__)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_MPU, OCMC_RAM_ECC_ERR_INT_INDEX, CSL_XBAR_OCMC_RAM1_IRQ);
#elif defined (_TMS320C6X)
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_DSP1, OCMC_RAM_ECC_ERR_INT_INDEX, CSL_XBAR_OCMC_RAM1_IRQ);
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable OCMC interrupt*/
    Intc_IntRegister(OCMC_RAM_ECC_ERR_INT,
                     (IntrFuncPtr) isrOcmcRamSecErr,
                     NULL);

    Intc_IntPrioritySet(OCMC_RAM_ECC_ERR_INT, 1, 0);
    Intc_SystemEnable(OCMC_RAM_ECC_ERR_INT);

    OCMCSoftReset(OCMC_RAM_APP_INST);

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    retVal = ocmcRamInitEccMem();
    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC Memory Intialisation failure", -1);
    }

    OCMCIntEnable(OCMC_RAM_APP_INST, 0, OCMC_ECC_SEC_ERROR_FOUND);

    /*Configure ERR count to trigger an interrupt*/
    OCMCEccErrTraceConfig(OCMC_RAM_APP_INST,
                          OCMC_RAM_ECC_1B_ERR_THRSH_VAL,
                          0,
                          0,
                          0);

    OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x4);
    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFEFFFF;
    gTest_Addr[0] = testVal;

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    gTest_Addr = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x4);
    testVal    = gTest_Addr[0];

    while (gEccErrAddr == 0) ;

    OCMCIntDisable(OCMC_RAM_APP_INST, 0, OCMC_INTERRUPT_ALL);

    /* Disable the interrupt */
    Intc_SystemDisable(OCMC_RAM_ECC_ERR_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(OCMC_RAM_ECC_ERR_INT);

    Intc_IntDisable();

    if (gEccErrAddr != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n OCMC ECC SEC test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\n OCMC ECC SEC test successful", -1);
        for (i = 0; i < 4; i++)
        {
            if (gEccErrBitMask[i])
            {
                eccErrAddr = ((gEccErrAddr << 4) +
                              OCMC_RAM_START_ADDR + (i * 4));
                UARTConfigPuts(uartBaseAddr, "\r\nECC -- SEC ECC ERR Occured at Address : ", -1);
                UARTConfigPutHexNum(uartBaseAddr, eccErrAddr);
                UARTConfigPuts(uartBaseAddr, "\r\nECC -- SEC ECC ERR Occured at Bit Mask ", -1);
                UARTConfigPutNum(uartBaseAddr, i);
                UARTConfigPuts(uartBaseAddr, " : ", -1);
                UARTConfigPutHexNum(uartBaseAddr, gEccErrBitMask[i]);
            }
        }
    }

    return 0;
}

/* Function performs OCMC Double bit error test
 * Initializes memory and ECC, Inserts Double bit error
 * and waits for handler to finish
 */
static int32_t ocmcRamDedErrTest(char ocmcEccMode)
{
    uint32_t testVal;
    uint32_t secAutoCorrectEn = 0;
    uint32_t eccErrIntEn      = 1;
    int32_t  retVal           = STW_SOK;

    gEccErrAddr = 0;
    gTest_Addr  = NULL;

#if defined (__ARM_ARCH_7A__)
    CPUDisableCPSRABit();
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable OCMC interrupt*/
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrOcmcRamDedErr,
                     NULL);

    OCMCSoftReset(OCMC_RAM_APP_INST);

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    retVal = ocmcRamInitEccMem();
    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC Memory Intialisation failure", -1);
    }

    OCMCIntEnable(OCMC_RAM_APP_INST, 0, OCMC_ECC_DED_ERROR_FOUND);

    /*Configure ERR count to trigger an interrupt*/
    OCMCEccErrTraceConfig(OCMC_RAM_APP_INST, 0, OCMC_RAM_ECC_2B_ERR_THRSH_VAL,
                          0,
                          0);

    OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);

    gTest_Addr    = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x18);
    testVal       = gTest_Addr[0];
    testVal       = testVal & 0xFFFCFFFF;
    gTest_Addr[0] = testVal;

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    testVal = gTest_Addr[0];

    while (gEccErrAddr == 0) ;

    OCMCIntDisable(OCMC_RAM_APP_INST, 0, OCMC_INTERRUPT_ALL);

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gEccErrAddr != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n OCMC ECC DED Error Test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\n OCMC ECC DED Error test successful", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nECC -- DED ERR occured at one of these addresses \r\n ",
                 -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR));
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x4));
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x8));
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0xc));
    }

    return 0;
}

/* Function performs OCMC Ram address error test
 * Initializes memory and ECC, Inserts OCMC Ram Address error
 * and waits for handler to finish
 */
static int32_t ocmcRamAddrErrTest(char ocmcEccMode)
{
    uint32_t secAutoCorrectEn = 0;
    uint32_t eccErrIntEn      = 1;
    int32_t  retVal           = STW_SOK;

    gEccErrAddr = 0;
    gTest_Addr  = NULL;

#if defined (__ARM_ARCH_7A__)
    CPUDisableCPSRABit();
#endif

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable OCMC interrupt*/
    Intc_IntRegister(gInterruptNum,
                     (IntrFuncPtr) isrOcmcRamAddrErr,
                     NULL);

    OCMCSoftReset(OCMC_RAM_APP_INST);

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    retVal = ocmcRamInitEccMem();
    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nECC Memory Intialisation failure", -1);
    }

    OCMCIntEnable(OCMC_RAM_APP_INST, 0, OCMC_ECC_ADDR_ERROR_FOUND);

    /*Configure ERR count to trigger an interrupt*/
    OCMCEccErrTraceConfig(OCMC_RAM_APP_INST, 0, 0,
                          OCMC_RAM_ECC_ADDR_ERR_THRSH_VAL,
                          0);

    OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_NON_ECC_CODE_ACCESS, 0, 0, 0);

    gTest_Addr = (uint32_t *) (OCMC_RAM_ECC_START_ADDR + 0x10);

    gOcmcTestVal = *(uint32_t *) (gTest_Addr);
    /* Address err addr[0] = 137( 0x89) : 0x112 = 0x89 << 1. This Modifies Bit 0
     * 0f ECC bits
     */
    gTestVal = gOcmcTestVal ^ 0x112;
    *(uint32_t *) (gTest_Addr) = gTestVal;

    if (OCMC_RAM_FULL_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_FULL_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);
    }
    else if (OCMC_RAM_BLOCK_ECC_MODE == ocmcEccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(OCMC_RAM_APP_INST, OCMC_BLOCK_ECC_ENABLE,
                      secAutoCorrectEn, eccErrIntEn, 0);

        /*Enable 0 block*/
        OCMCRAMBlockEnableCtrl(OCMC_RAM_APP_INST, 1, 0);
    }

    gTestVal = *(uint32_t *) (gTest_Addr);

    while (gEccErrAddr == 0) ;

    OCMCIntDisable(OCMC_RAM_APP_INST, 0, OCMC_INTERRUPT_ALL);

    /* Unregister the interrupt */
    Intc_IntUnregister(gInterruptNum);

    Intc_IntDisable();

    if (gEccErrAddr != 0)
    {
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_EFAIL)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n OCMC ECC Address Error test Fail!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\n OCMC ECC Address Error test successful", -1);
        UARTConfigPuts(uartBaseAddr,
            "\r\nECC -- Address ERR occured at one of these addresses \r\n ",
            -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR));
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x4));
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0x8));
        UARTConfigPuts(uartBaseAddr, "\r\n", -1);
        UARTConfigPutHexNum(uartBaseAddr, ((gEccErrAddr << 4) + OCMC_RAM_START_ADDR + 0xc));
    }

    return 0;
}
