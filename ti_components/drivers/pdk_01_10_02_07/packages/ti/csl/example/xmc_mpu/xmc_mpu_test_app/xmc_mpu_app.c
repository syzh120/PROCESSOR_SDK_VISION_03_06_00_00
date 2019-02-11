/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \file     xmc_mpu_app.c
 *
 *  \brief    This file contains example usage for Extended Memory Controller
 *            (XMC) and Memory Protection Unit (MPU) in C66x device on TDA2x
 *            and TDA3x platform
 *
 *  \details  This will demonstrate implementation of access restrictions
 *            to different memory regions from C66x DSP.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <c6x.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* Memory region labelled ASIL will be read-only (RO) for USER mode.
 * Memory region labelled QM will be read-write (RW) for USER mode.
 * All memory will be read-write (RW) for SUPERVISOR mode
 */
/* DDR Memory used for Memory access checks  */
#define QM_REGION_EMIF_START     (0x80010000U)
#define QM_REGION_EMIF_END       (0x80020000U)
#define ASIL_REGION_EMIF_START   (0x80020000U)
#define ASIL_REGION_EMIF_END     (0x80030000U)

/* OCMC Memory used for Memory access checks  */
#define QM_REGION_L3OCMC_START   (0x40300000U)
#define QM_REGION_L3OCMC_END     (0x40310000U)
#define ASIL_REGION_L3OCMC_START (0x40310000U)
#define ASIL_REGION_L3OCMC_END   (0x40320000U)

/* L2 Memory used for Memory access checks  */
/* Don't use first page as that is used for interrupt vector tables */
#define QM_L2RAM_START         (SOC_DSP_L2_BASE + DSPICFG_L2_PGSZ)
#define QM_L2RAM_END           (QM_L2RAM_START + DSPICFG_L2_PGSZ)
#define ASIL_L2RAM_START       (QM_L2RAM_END)
#define ASIL_L2RAM_END         (ASIL_L2RAM_START + DSPICFG_L2_PGSZ)

#define DSPXMC_USR_RO_PRV_RW (DSPXMC_ALLOW_SR | \
                              DSPXMC_ALLOW_SW | \
                              DSPXMC_ALLOW_SX | \
                              DSPXMC_ALLOW_UR | \
                              DSPXMC_ALLOW_UX)

#define DSPXMC_USR_RW_PRV_RW (DSPXMC_USR_RO_PRV_RW | DSPXMC_ALLOW_UW)

#define DSPICFG_USR_RO_PRV_RW (DSPICFG_L2MPPA_LOCAL | \
                               DSPICFG_L2MPPA_SR |    \
                               DSPICFG_L2MPPA_SW |    \
                               DSPICFG_L2MPPA_SX |    \
                               DSPICFG_L2MPPA_UR |    \
                               DSPICFG_L2MPPA_UX)

#define DSPICFG_USR_RW_PRV_RW (DSPICFG_USR_RO_PRV_RW | DSPICFG_L2MPPA_UW)

#define EDMA3_CC_REGION_DSP   (2U)

/* Keys to lock/unlock MPU and XMC registers
 * Default state is unlocked. Locking is optional.
 * Keys can be changed by user.
 */
#define MPLK_KEY0   0xABCD1234U
#define MPLK_KEY1   0x1234ABCDU
#define MPLK_KEY2   0xA1B2C3D4U
#define MPLK_KEY3   0x4D3C2B1AU

typedef void (*OsalIntrFuncPtr)(uint32_t arg0);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define MEM_CHK_BUF_SZ 0x40U
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#pragma DATA_SECTION(".scratch_section");
#else
#pragma DATA_ALIGN(scratchBuffer, 32)
#pragma DATA_SECTION(scratchBuffer,".scratch_section");
#endif
volatile uint32_t scratchBuffer[MEM_CHK_BUF_SZ >> 2U];
#ifdef __cplusplus
#pragma DATA_ALIGN(32)
#pragma DATA_SECTION(".scratch_section");
#else
#pragma DATA_ALIGN(randomNums, 32)
#pragma DATA_SECTION(randomNums,".scratch_section");
#endif
volatile uint32_t randomNums[MEM_CHK_BUF_SZ >> 2U] =
{
    0xAAAAAAAAU,
    0x55555555U,
    0xBBBBBBBBU,
    0xCCCCCCCCU,
    0x80808080U,
    0xA0A0A0A0U,
    0x50505050U,
    0x12345678U,
    0x22222222U,
    0xDDDDDDDDU,
    0x11111111U,
    0xEEEEEEEEU,
    0x00000000U,
    0x33331111U,
    0x99997777U,
    0x05050505U
};
int32_t           gTestStatus = STW_SOK;

uint32_t          gIntrToHandle[] =
{
    INTH_INT_ID_MDMAERR,
    INTH_INT_ID_L1D_PROT_CPU,
    INTH_INT_ID_L1D_PROT_DMA,
    INTH_INT_ID_L1P_PROT_CPU,
    INTH_INT_ID_L1P_PROT_DMA,
    INTH_INT_ID_L2_PROT_CPU,
    INTH_INT_ID_L2_PROT_DMA,
    INTH_INT_ID_L3_BUS_ERR
};

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Initialize memory region specified by startAddr and endAddr
 *
 */
void initMem(uint32_t startAddr, uint32_t endAddr);

/**
 * \brief   Initialize memory regions under test
 *
 */
static void initAllMemory();

/**
 * \brief   Sets up different regions in XMC with different access permissions
 *
 */
static void setupXMC();

/**
 * \brief   Sets up different regions in L2RAM with different access permissions
 *
 */
static void setupL2MPU();

/**
 * \brief   Validate CPU Read Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 */
uint32_t validateCpuReadAccess(uint32_t startAddr, uint32_t endAddr);


/**
 * \brief   Validate CPU Write Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 */
uint32_t validateCpuWriteAccess(uint32_t startAddr, uint32_t endAddr);

/**
 * \brief   Common implementation to check access permissions with specified
 *          CPU mode
 *
 * \param   none
 *
 * \return  errorOccured    >0 if unexpected failure to read/write, 0 otherwise
 */
uint32_t validateAccessPermissions(uint32_t cpuMode);

/**
 * \brief   Configure EDMA to transfer a 2D block.
 *          Function will configure, trigger and wait for transfer completion.
 *
 * \param   dst     Source Address of the block
 * \param   src     Source Address of the block
 * \param   x       Width of the block in 32bit words
 * \param   y       Height of the block
 *
 * \retval  none.
 */
static void edmaTransfer2d(uint32_t dst, uint32_t src, uint32_t x, uint32_t y)
{
    uint32_t          base_address  = SOC_DSP_EDMA_CC_BASE;
    uint32_t          edma_ch_num   = 0;
    uint32_t          edma_tcc_num  = 0;
    uint32_t          edma_evtq_num = 0;
    uint32_t          i;
    uint32_t          aCnt = x * 4;
    uint32_t          bCnt = y;
    uint32_t          cCnt = 1U;
    EDMA3CCPaRAMEntry edmaParam;

    EDMA3RequestChannel(base_address,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edma_ch_num,
                        edma_tcc_num,
                        edma_evtq_num);

    edmaParam.opt      = 0;
    edmaParam.srcAddr  = src;
    edmaParam.destAddr = dst;
    edmaParam.aCnt     = aCnt;
    edmaParam.bCnt     = bCnt;
    edmaParam.cCnt     = cCnt;
    edmaParam.srcBIdx  = aCnt;
    edmaParam.destBIdx = aCnt;
    edmaParam.srcCIdx  = aCnt;
    edmaParam.destCIdx = aCnt;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |= (EDMA3_OPT_TCINTEN_MASK |
                          EDMA3_OPT_ITCINTEN_MASK |
                          ((edma_tcc_num << EDMA3_OPT_TCC_SHIFT) &
                       EDMA3_OPT_TCC_MASK));

    EDMA3SetPaRAM(base_address, edma_ch_num, &edmaParam);

    /*
     * Transfer is done in a sync mode
     * Number of triggers required are bCnt * cCnt
     */
    for (i = 0; i < (bCnt * cCnt); i++)
    {
        EDMA3EnableTransfer(base_address, edma_ch_num, EDMA3_TRIG_MODE_MANUAL);
        while ((EDMA3GetIntrStatus(base_address) & (0x1 << edma_tcc_num)) !=
               (0x1 << edma_tcc_num)) ;
        EDMA3ClrIntr(base_address, edma_tcc_num);
    }
}

 /**
 * \brief   Interrupt handler for XMC/MPU/MDMA errors
 *
 * \param   arg     Interrupt ID
 *
 * \retval  none.
 */
static void dspErrHandler(void *arg)
{
    uint32_t faultAddr = 0U;
    uint32_t errType   = (uint32_t) arg;
    switch (errType)
    {
        case INTH_INT_ID_MDMAERR:
            UARTConfigPuts(uartBaseAddr, "MDMAERR\r\n", -1);
            faultAddr = DSPXMCGetFaultAddr(SOC_DSP_XMC_CTRL_BASE);
            DSPXMCClearFaultRegs(SOC_DSP_XMC_CTRL_BASE);
            DSPICFGClearMdmaErrEvt(SOC_DSP_ICFG_BASE);
            break;
        case INTH_INT_ID_L1D_PROT_CPU:
        case INTH_INT_ID_L1D_PROT_DMA:
            UARTConfigPuts(uartBaseAddr, "L1D Memory Protection\r\n", -1);
            faultAddr = DSPICFGGetL1DMPUFaultAddr(SOC_DSP_ICFG_BASE);
            DSPICFGClearL1DMPUFaultRegs(SOC_DSP_ICFG_BASE);
            break;
        case INTH_INT_ID_L1P_PROT_CPU:
        case INTH_INT_ID_L1P_PROT_DMA:
            UARTConfigPuts(uartBaseAddr, "L1P Memory Protection\r\n", -1);
            faultAddr = DSPICFGGetL1PMPUFaultAddr(SOC_DSP_ICFG_BASE);
            DSPICFGClearL1PMPUFaultRegs(SOC_DSP_ICFG_BASE);
            break;
        case INTH_INT_ID_L2_PROT_CPU:
        case INTH_INT_ID_L2_PROT_DMA:
            UARTConfigPuts(uartBaseAddr, "L2 Memory Protection\r\n", -1);
            faultAddr = DSPICFGGetL2MPUFaultAddr(SOC_DSP_ICFG_BASE);
            DSPICFGClearL2MPUFaultRegs(SOC_DSP_ICFG_BASE);
            break;
        case INTH_INT_ID_L3_BUS_ERR:
            UARTConfigPuts(uartBaseAddr, "L3 error\r\n", -1);
            break;
    }
	UARTConfigPrintf(uartBaseAddr, "Fault address: 0x%08x!!!\r\n\0", faultAddr);
}

/**
 * \brief   Example NMI handler for DSP
 *
 * \param   none.
 *
 * \retval  none.
 */
static void dspNmi(void *arg)
{
    volatile int a = 1;
    UARTConfigPuts(uartBaseAddr, "Exception occured.. ignoring \r\n", -1);
	ECR = 0x2;
    return;
}

void padConfig_prcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t main(void)
{
    uint32_t            errorOccured = 0U;
    volatile uint32_t   delay;
    int32_t             status, i, temp;
    uint32_t            errHandlerCount = sizeof (gIntrToHandle) /
                                          sizeof (uint32_t);
    OsalIntrFuncPtr         fxn;

    padConfig_prcmEnable();


    UARTConfigPuts(uartBaseAddr, "\r\nXMC MPU Test Application\r\n", -1);

    /* EDMA setup */
    EDMAsetRegion(EDMA3_CC_REGION_DSP);
    EDMA3Init(SOC_DSP_EDMA_CC_BASE, 0);

    /* Initialize interrupt handlers */
    Intc_Init();
    /* Enable all interrupts */
    Intc_IntEnable(0);
    /* Register exception and NMI handler */
    Intc_IntRegister(1, (IntrFuncPtr) dspNmi, NULL);

    for (i = 0; i < errHandlerCount; i++)
    {
        Intc_IntRegister((uint16_t) gIntrToHandle[i],
                         (IntrFuncPtr) dspErrHandler,
                         (void *) gIntrToHandle[i]);
        Intc_IntPrioritySet((uint16_t) gIntrToHandle[i],
                            (uint16_t) 1,
                            (uint8_t) 0);
        Intc_SystemEnable((uint16_t) gIntrToHandle[i]);
    }

    /* Clear older error status to ensure correct interrupt generation */
    DSPICFGClearMdmaErrEvt(SOC_DSP_ICFG_BASE);
    DSPICFGClearL1DMPUFaultRegs(SOC_DSP_ICFG_BASE);
    DSPICFGClearL1PMPUFaultRegs(SOC_DSP_ICFG_BASE);
    DSPICFGClearL2MPUFaultRegs(SOC_DSP_ICFG_BASE);

    /* Show interrupt due to 0x0 read access */
    temp  = *(volatile uint32_t *) 0x0U;
    delay = 1000U;
    while (delay--) ;

    /* Show interrupt due to 0x0 write access */
    *(volatile uint32_t *) 0x0U = temp;
    delay = 1000U;
    while (delay--) ;

    /* Show interrupt due to invalid memory read access at 0x100 */
    temp  = *(volatile uint32_t *) 0x100U;
    delay = 1000U;
    while (delay--) ;

    /* Show interrupt due to invalid memory write access at 0x100 */
    *(volatile uint32_t *) 0x100U = temp;
    delay = 1000U;
    while (delay--) ;

    /* Show error due to USER mode access to XMC registers */
    DSP_setCpuMode(DSP_CPU_MODE_USR);
    *(volatile uint32_t *) SOC_DSP_XMC_CTRL_BASE = 0;
    DSP_setCpuMode(DSP_CPU_MODE_SPV);
    delay = 1000U;
    while (delay--) ;

    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1D,
                       DSPICFG_CACHE_SIZE_L1_DISABLED);
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L1P,
                       DSPICFG_CACHE_SIZE_L1_32K);
    DSPICFGCacheEnable(SOC_DSP_ICFG_BASE,
                       DSPICFG_MEM_L2,
                       DSPICFG_CACHE_SIZE_L2_64K);

    /* CPU mode switch is redundant - done only to indicate dependency of
     * setupXMC() and setupL2MPU() on CPU mode */
    DSP_setCpuMode(DSP_CPU_MODE_SPV);
    setupXMC();
    setupL2MPU();

    /* CPU mode switch is redundant - done only to indicate dependency of
     * initAllMemory() on CPU mode */
    DSP_setCpuMode(DSP_CPU_MODE_SPV);
    /* Initialize all memories to allow access permissions check */
    initAllMemory();

    /* Verify access permissions in SUPERVISOR mode */
    errorOccured += validateAccessPermissions(DSP_CPU_MODE_SPV);

    /* CPU mode switch is redundant - done only to indicate dependency of
     * initAllMemory() on CPU mode */
    DSP_setCpuMode(DSP_CPU_MODE_SPV);
    /* Initialize all memories to allow access permissions check */
    initAllMemory();

    /* Verify access permissions in USER mode */
    errorOccured += validateAccessPermissions(DSP_CPU_MODE_USR);

    if (0U == errorOccured)
    {
        UARTConfigPuts(uartBaseAddr, "Testcase PASS\r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "Testcase FAIL\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    /* Unlock all memory at the end of test-case */
    DSP_setCpuMode(DSP_CPU_MODE_SPV);
    status = DSPICFGMemoryProtectionUnlock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTConfigPuts(uartBaseAddr, "Unable to unlock XMC registers\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    if (gTestStatus == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr, "Starting Exception Handler test.", -1);
        UARTConfigPuts(uartBaseAddr,
                       "Execution is not expected to return from the exception handler\r\n", -1);
       UARTConfigPuts(uartBaseAddr, "XMC MPU Test completed\r\n", -1);
        /* Show Exception generated due to NULL pointer usage in code */
        fxn = NULL;
        fxn(0);
        delay = 1000U;
        while (delay--) ;
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nXMC MPU Test Fail", -1);
    }

    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

/**
 * \brief   Initialize memory region specified by startAddr and endAddr
 *
 */
void initMem(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t addr;
    for (addr = startAddr; addr < endAddr; addr += 4)
    {
        HW_WR_REG32(addr, addr);
    }
}

/**
 * \brief   Initialize memory regions under test
 *
 */
static void initAllMemory()
{
    initMem(QM_REGION_EMIF_START, QM_REGION_EMIF_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          QM_REGION_EMIF_START,
                          (QM_REGION_EMIF_END - QM_REGION_EMIF_START));

    initMem(ASIL_REGION_EMIF_START, ASIL_REGION_EMIF_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          ASIL_REGION_EMIF_START,
                          (ASIL_REGION_EMIF_END - ASIL_REGION_EMIF_START));

    initMem(QM_REGION_L3OCMC_START, QM_REGION_L3OCMC_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          QM_REGION_L3OCMC_START,
                          (QM_REGION_L3OCMC_END - QM_REGION_L3OCMC_START));

    initMem(ASIL_REGION_L3OCMC_START, ASIL_REGION_L3OCMC_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          ASIL_REGION_L3OCMC_START,
                          (ASIL_REGION_L3OCMC_END - ASIL_REGION_L3OCMC_START));

    initMem(QM_L2RAM_START, QM_L2RAM_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          QM_L2RAM_START,
                          (QM_L2RAM_END - QM_L2RAM_START));

    initMem(ASIL_L2RAM_START, ASIL_L2RAM_END);
    DSPICFGCacheWriteBack(SOC_DSP_ICFG_BASE,
                          ASIL_L2RAM_START,
                          (ASIL_L2RAM_END - ASIL_L2RAM_START));
}

/**
 * \brief   Sets up different regions in XMC with different access permissions
 *
 */
static void setupXMC()
{
    int32_t status;
    /* In case you are using breakpoints for debugging, ensure that
     * code region has full access permissions
     */
    status = DSPICFGMemoryProtectionUnlock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTConfigPuts(uartBaseAddr, "Unable to unlock XMC registers\r\n", -1);
    }

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x2U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         QM_REGION_EMIF_START,     /* inpBAddress   */
                         QM_REGION_EMIF_START,     /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RW_PRV_RW);    /* permsFieldVal */

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x3U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         ASIL_REGION_EMIF_START,   /* inpBAddress   */
                         ASIL_REGION_EMIF_START,   /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RO_PRV_RW);    /* permsFieldVal */

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x4U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         QM_REGION_L3OCMC_START,   /* inpBAddress   */
                         QM_REGION_L3OCMC_START,   /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RW_PRV_RW);    /* permsFieldVal */

    DSPXMCSetMPAXSegment(SOC_DSP_XMC_CTRL_BASE,    /* baseAddress   */
                         0x5U,                     /* segmentId     */
                         DSPXMC_SEGSZ_64KB,        /* segmentSize   */
                         ASIL_REGION_L3OCMC_START, /* inpBAddress   */
                         ASIL_REGION_L3OCMC_START, /* repAddressL   */
                         0x0U,                     /* repAddressH   */
                         DSPXMC_USR_RO_PRV_RW);    /* permsFieldVal */

    status = DSPICFGMemoryProtectionLock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTConfigPuts(uartBaseAddr, "Unable to lock XMC registers\r\n", -1);
        gTestStatus = STW_EFAIL;
    }
}

/**
 * \brief   Sets up different regions in L2RAM with different access permissions
 *
 */
static void setupL2MPU()
{
    int32_t status;
    /* In case you are using breakpoints for debugging, ensure that
     * code region has full access permissions
     */
    status = DSPICFGMemoryProtectionUnlock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTConfigPuts(uartBaseAddr, "Unable to unlock XMC registers\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    DSPICFGSetAttribute(SOC_DSP_ICFG_BASE,
                        DSPICFG_MEM_L2,
                        QM_L2RAM_START,
                        DSPICFG_USR_RW_PRV_RW);

    DSPICFGSetAttribute(SOC_DSP_ICFG_BASE,
                        DSPICFG_MEM_L2,
                        ASIL_L2RAM_START,
                        DSPICFG_USR_RO_PRV_RW);

    status = DSPICFGMemoryProtectionLock(
        SOC_DSP_ICFG_BASE, MPLK_KEY0, MPLK_KEY1, MPLK_KEY2, MPLK_KEY3);
    if (STW_SOK != status)
    {
        UARTConfigPuts(uartBaseAddr, "Unable to lock XMC registers\r\n", -1);
        gTestStatus = STW_EFAIL;
    }
}

/**
 *******************************************************************************
 *
 * \brief   Validate CPU Read Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateCpuReadAccess(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t errorOccured = 0U, addr, val;

    for (addr = startAddr; addr < endAddr; addr += sizeof (uint32_t))
    {
        val = HW_RD_REG32(addr);
        if (val != addr)
        {
            errorOccured = 1U;
        }
    }

    if (0U != errorOccured)
    {
        UARTConfigPuts(uartBaseAddr, "Error occurred in READ\r\n", -1);
        gTestStatus = STW_EFAIL;
    }

    return errorOccured;
}

/**
 *******************************************************************************
 *
 * \brief   Validate CPU Write Access
 *
 * \param   startAddr       Start Address of region to check
 * \param   endAddr         End Address of region to check
 *
 * \return  errorOccured    1 if failure to read, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateCpuWriteAccess(uint32_t startAddr, uint32_t endAddr)
{
    uint32_t errorOccured = 0U, addr, i, wval, rval;

    for (addr = startAddr; addr < endAddr; addr += MEM_CHK_BUF_SZ)
    {
        memset((void *) (&scratchBuffer[0]), 0x0, MEM_CHK_BUF_SZ);
        memcpy((void *) addr, (void *) (&randomNums[0]), MEM_CHK_BUF_SZ);

        DSPICFGCacheWriteBackInvalidateAll(SOC_DSP_ICFG_BASE, DSPICFG_MEM_L2);

        if ((QM_L2RAM_START == startAddr) ||
            (ASIL_L2RAM_START == startAddr))
        {
            memcpy((void *) (&scratchBuffer[0]), (void *) addr, MEM_CHK_BUF_SZ);
        }
        else
        {
            /* Use EDMA read to avoid cache */
            edmaTransfer2d((uint32_t) (&scratchBuffer[0]),
                           addr,
                           (MEM_CHK_BUF_SZ >> 2),
                           1U);
        }
        for (i = 0; i < (MEM_CHK_BUF_SZ >> 2); i++)
        {
            wval = randomNums[i];
            rval = scratchBuffer[i];
            if (rval != wval)
            {
                errorOccured = 1U;
            }
        }
    }

    if (0U != errorOccured)
    {
        UARTConfigPuts(uartBaseAddr, "Error occurred in WRITE\r\n", -1);
    }

    return errorOccured;
}

/**
 *******************************************************************************
 *
 * \brief   Common implementation to check access permissions with specified
 *          CPU mode
 *
 * \return  errorOccured    >0 if unexpected failure to read/write, 0 otherwise
 *
 *******************************************************************************
 */
uint32_t validateAccessPermissions(uint32_t cpuMode)
{
    uint32_t errorOccured = 0U, retVal;

    DSP_setCpuMode(cpuMode);

    UARTConfigPuts(uartBaseAddr, "Checking CPU DDR/OCMC READ Access for USR_RW region\r\n", -1);
    errorOccured += validateCpuReadAccess(QM_REGION_EMIF_START,
                                          QM_REGION_EMIF_END);
    errorOccured += validateCpuReadAccess(QM_REGION_L3OCMC_START,
                                          QM_REGION_L3OCMC_END);

    UARTConfigPuts(uartBaseAddr, "Checking CPU DDR/OCMC READ Access for USR_RO region\r\n", -1);
    errorOccured += validateCpuReadAccess(ASIL_REGION_EMIF_START,
                                          ASIL_REGION_EMIF_END);
    errorOccured += validateCpuReadAccess(ASIL_REGION_L3OCMC_START,
                                          ASIL_REGION_L3OCMC_END);

    UARTConfigPuts(uartBaseAddr, "Checking CPU L2 RAM READ Access for USR_RW region\r\n", -1);
    errorOccured += validateCpuReadAccess(QM_L2RAM_START,
                                          QM_L2RAM_END);
    UARTConfigPuts(uartBaseAddr, "Checking CPU L2 RAM READ Access for USR_RO region\r\n", -1);
    errorOccured += validateCpuReadAccess(ASIL_L2RAM_START,
                                          ASIL_L2RAM_END);

    UARTConfigPuts(uartBaseAddr, "Checking CPU DDR/OCMC WRITE Access for USR_RW region\r\n", -1);
    errorOccured += validateCpuWriteAccess(QM_REGION_EMIF_START,
                                           QM_REGION_EMIF_END);
    errorOccured += validateCpuWriteAccess(QM_REGION_L3OCMC_START,
                                           QM_REGION_L3OCMC_END);

    UARTConfigPuts(uartBaseAddr, "Checking CPU DDR/OCMC WRITE Access for USR_RO region\r\n", -1);

    if (DSP_CPU_MODE_USR == cpuMode)
    {
        UARTConfigPuts(uartBaseAddr, "Disabling interrupt since expecting errors\r\n", -1);
        DSP_setCpuMode(DSP_CPU_MODE_SPV);
        Intc_SystemDisable(INTH_INT_ID_MDMAERR);
        DSP_setCpuMode(cpuMode);
    }
    retVal = validateCpuWriteAccess(ASIL_REGION_EMIF_START,
                                    ASIL_REGION_EMIF_END);

    if (DSP_CPU_MODE_SPV == cpuMode)
    {
        errorOccured += retVal;
    }
    else
    {
        DSP_setCpuMode(DSP_CPU_MODE_SPV);
        UARTConfigPuts(uartBaseAddr, "Restore interrupt. Will get interrupt for old errors\r\n", -1);
        Intc_SystemEnable(INTH_INT_ID_MDMAERR);
        DSP_setCpuMode(cpuMode);
        if (0U == retVal)
        {
            errorOccured = 1U;
        }
    }

    if (DSP_CPU_MODE_USR == cpuMode)
    {
        UARTConfigPuts(uartBaseAddr, "Disabling interrupt since expecting errors\r\n", -1);
        DSP_setCpuMode(DSP_CPU_MODE_SPV);
        Intc_SystemDisable(INTH_INT_ID_MDMAERR);
        DSP_setCpuMode(cpuMode);
    }
    retVal = validateCpuWriteAccess(ASIL_REGION_L3OCMC_START,
                                    ASIL_REGION_L3OCMC_END);
    if (DSP_CPU_MODE_SPV == cpuMode)
    {
        errorOccured += retVal;
    }
    else
    {
        DSP_setCpuMode(DSP_CPU_MODE_SPV);
        UARTConfigPuts(uartBaseAddr, "Restore interrupt. Will get interrupt for old errors\r\n", -1);
        Intc_SystemEnable(INTH_INT_ID_MDMAERR);
        DSP_setCpuMode(cpuMode);
        if (0U == retVal)
        {
            errorOccured = 1U;
        }
    }


    UARTConfigPuts(uartBaseAddr, "Checking CPU L2 RAM WRITE Access for USR_RW region\r\n", -1);
    errorOccured += validateCpuWriteAccess(QM_L2RAM_START,
                                           QM_L2RAM_END);

    UARTConfigPuts(uartBaseAddr, "Checking CPU L2 RAM WRITE Access for USR_RO region\r\n", -1);
    if (DSP_CPU_MODE_USR == cpuMode)
    {
        UARTConfigPuts(uartBaseAddr, "Disabling interrupt since expecting errors\r\n", -1);
        DSP_setCpuMode(DSP_CPU_MODE_SPV);
        Intc_SystemDisable(INTH_INT_ID_L2_PROT_CPU);
        Intc_SystemDisable(INTH_INT_ID_L2_PROT_DMA);
        DSP_setCpuMode(cpuMode);
    }
    retVal = validateCpuWriteAccess(ASIL_L2RAM_START,
                                    ASIL_L2RAM_END);
    if (DSP_CPU_MODE_SPV == cpuMode)
    {
        errorOccured += retVal;
    }
    else
    {
        DSP_setCpuMode(DSP_CPU_MODE_SPV);
        UARTConfigPuts(uartBaseAddr, "Restore interrupt. Will get interrupt for old errors\r\n", -1);
        Intc_SystemEnable(INTH_INT_ID_L2_PROT_CPU);
        Intc_SystemEnable(INTH_INT_ID_L2_PROT_DMA);
        DSP_setCpuMode(cpuMode);
        if (0U == retVal)
        {
            errorOccured = 1U;
        }
    }

    return errorOccured;
}
