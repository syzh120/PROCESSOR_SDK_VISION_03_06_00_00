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

#include <stdint.h>
#include <stdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_ocmc_ecc.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

#include "ocmc_common.h"

#define OCMC_BASIC_TEST       ('1')
#define OCMC_ADDR_SEQ_TEST    ('2')
#define OCMC_OVFL_MID_TEST    ('3')
#define OCMC_OVFL_WRP_TEST    ('4')
#define OCMC_UDFL_TEST        ('5')
#define OCMC_SHT_FRM_TEST     ('6')
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

#define FULL_ECC                   ('1')
#define BLOCK_ECC                  ('2')
#define NON_ECC_DATA_ACCESS        ('3')
#define NON_ECC_CODE_ACCESS        ('4')

#define IPU1_RESET_ADDRESS (0x4ae06510Ul)
#define IPU2_RESET_ADDRESS (0x4ae06910Ul)

extern uint32_t  *write_addr;
extern uint32_t  *read_addr;
extern uint32_t   nextVal;
extern uint32_t   gValue[cBufSizeInWord];

volatile uint32_t writeSequence = 0;
volatile uint32_t readSequence  = 0;
volatile uint32_t overflowMid   = 0;
volatile uint32_t newFrameStart = 0;
volatile uint32_t shortframe    = 0;
volatile uint32_t underflow     = 0;

static void mainMenu(char *option);
static void mainSubMenu(char *mainMenuOption, char *eccMode);
static int32_t ocmcBasicTest(char mainMenuOption);
static int32_t ocmcAddrSeqTest(char mainMenuOption);
static int32_t ocmcOvflMidTest(char mainMenuOption);
static int32_t ocmcOvflWrpTest(char mainMenuOption);
static int32_t ocmcShtFrmTest(char mainMenuOption);
static int32_t ocmcUDflTest(char mainMenuOption);

static int32_t ocmcInit(uint32_t *virtStartAddr, uint32_t intFlag,
                        char mainMenuOption, IntrFuncPtr funcPtr,
                        char *eccMode);
static void ocmcDeInit(uint32_t virtStartAddr);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

void ocmcUDflIsr(void *arg)
{
    if (OCMCIntStatusRawGet(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_CBUF_UNDERFLOW))
    {
        underflow = 1;
    }

    OCMCCbufErrorStatusClear(SOC_OCMC_RAM1_CFG_BASE, e_cbuf_stat_underflow, 0);
    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_INTERRUPT_ALL);

    /*write 2nd slice*/
    nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
    writeSubFrame(cBufSizeInWord, write_addr, gValue);
    write_addr += cBufSizeInWord;
}

void ocmcShtFrmTIsr(void *arg)
{
    if (OCMCIntStatusRawGet(SOC_OCMC_RAM1_CFG_BASE, 0,
                            OCMC_CBUF_SHORT_FRAME_DETECT))
    {
        shortframe = 1;
    }
    OCMCCbufErrorStatusClear(SOC_OCMC_RAM1_CFG_BASE,
                             e_cbuf_stat_short_frame_detect,
                             0);
    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_INTERRUPT_ALL);
}

void ocmcOvflWrpIsr(void *arg)
{
    UARTConfigPuts(uartBaseAddr, "\r\nRemaning slice", -1);

    if (OCMCIntStatusRawGet(SOC_OCMC_RAM1_CFG_BASE, 0,
                            OCMC_CBUF_OVER_FLOW_WRAP_FOUND))
    {
        newFrameStart = 1;
    }
    OCMCCbufErrorStatusClear(SOC_OCMC_RAM1_CFG_BASE, e_cbuf_stat_overflow_wrap,
                             0);
    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_INTERRUPT_ALL);

    /*Read 3rd slice*/
    UARTConfigPuts(uartBaseAddr, "\r\n 3rd slice ", -1);
    readSubFrame(cBufSizeInWord, read_addr);
    read_addr += cBufSizeInWord;
}

void ocmcOvflMidIsr(void *arg)
{
    UARTConfigPuts(uartBaseAddr, "\r\n1st word of 2nd slice is corrupted due to overflow", -1);

    if (OCMCIntStatusRawGet(SOC_OCMC_RAM1_CFG_BASE, 0,
                            OCMC_CBUF_OVERFLOW_MID_FOUND))
    {
        overflowMid = 1;
    }
    OCMCCbufErrorStatusClear(SOC_OCMC_RAM1_CFG_BASE, e_cbuf_stat_overflow_mid,
                             0);
    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_INTERRUPT_ALL);

    /*Read 2nd slice*/
    UARTConfigPuts(uartBaseAddr, "\r\n 2nd slice ", -1);
    readSubFrame(cBufSizeInWord, read_addr);
    read_addr += cBufSizeInWord;
}

void ocmcAddrSeqIsr(void *arg)
{
    if (OCMCIntStatusRawGet(SOC_OCMC_RAM1_CFG_BASE, 0,
                            OCMC_CBUF_WR_ADDR_SEQ_ERR))
    {
        writeSequence = 1;
    }

    if (OCMCIntStatusRawGet(SOC_OCMC_RAM1_CFG_BASE, 0,
                            OCMC_CBUF_RD_ADDR_SEQ_ERR))
    {
        readSequence = 1;
    }

    OCMCCbufErrorStatusClear(SOC_OCMC_RAM1_CFG_BASE,
                             e_cbuf_stat_wr_addr_seq_error,
                             0);
    OCMCCbufErrorStatusClear(SOC_OCMC_RAM1_CFG_BASE,
                             e_cbuf_stat_rd_addr_seq_error,
                             0);
    OCMCIntStatusEnableClear(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_INTERRUPT_ALL);
}

static void ocmcDeInit(uint32_t virtStartAddr)
{
    OCMCIntDisable(SOC_OCMC_RAM1_CFG_BASE, 0, OCMC_INTERRUPT_ALL);

    OCMC_CBUF_Heap_Free(e_ocmc_ram1, (void *) virtStartAddr);

    OCMC_CBUF_Deinit(e_ocmc_ram1);

    return;
}

static int32_t ocmcInit(uint32_t *virtStartAddr, uint32_t intFlag,
                        char mainMenuOption, IntrFuncPtr funcPtr,
                        char *eccMode)
{
    vbuf_setup_image_params_auto_addr_t iParam;
    uint32_t        exitStatus = 0;
    ocmc_ret_type_t err;

    mainSubMenu(&mainMenuOption, eccMode);
    OCMCSoftReset(SOC_OCMC_RAM1_CFG_BASE);

    OCMC_CBUF_Heap_Init(e_ocmc_ram1);

    if (mainMenuOption == OCMC_BASIC_TEST)
    {
        OCMCModeSet(SOC_OCMC_RAM1_CFG_BASE, NO_IDLE);
    }

    iParam.bytes_per_pixel = BPP;
    iParam.image_height    = HEIGHT;
    iParam.image_width     = WIDTH;
    iParam.lines_per_slice = N_LINES;
    iParam.num_slices      = NUM_SLICES_PER_CBUF;

    /* Allocate the circular buffer */
    *virtStartAddr =
        (uint32_t) (OCMC_CBUF_Heap_Alloc(e_ocmc_ram1, &iParam, &err));

    if (FULL_ECC == *eccMode)
    {
        /*Configure OCMC to Full ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_FULL_ECC_ENABLE, 0, 0, 0);
    }
    else if (BLOCK_ECC == *eccMode)
    {
        /*Configure OCMC to block ECC mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_BLOCK_ECC_ENABLE, 0, 0, 0);

        /*Enable 0 and 1 block*/
        OCMCRAMBlockEnableCtrl(SOC_OCMC_RAM1_CFG_BASE, 1, 1);
        OCMCRAMBlockEnableCtrl(SOC_OCMC_RAM1_CFG_BASE, 1, 2);
    }
    else if ((NON_ECC_DATA_ACCESS == *eccMode) &&
             (OCMC_BASIC_TEST == OCMC_BASIC_TEST))
    {
        /*Configure OCMC to Full ECC Data access mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_NON_ECC_DATA_ACCESS, 0, 0, 0);
    }
    else if ((NON_ECC_CODE_ACCESS == *eccMode) &&
             (OCMC_BASIC_TEST == OCMC_BASIC_TEST))
    {
        /*Configure OCMC to Non ECC Code access mode*/
        OCMCEccConfig(SOC_OCMC_RAM1_CFG_BASE, OCMC_NON_ECC_CODE_ACCESS, 0, 0, 0);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr, "\r\nOCMC board diagnostic test exiting...", -1);
        exitStatus = 1;
    }
    if ((mainMenuOption != OCMC_BASIC_TEST) &&
        (exitStatus != 1))
    {
        /* Configure OCMC interrupt*/

        /*XBAR Configuration*/
        CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1, OCMC_RAM1_IRQ_CROSS_BAR_INSTANCE, OCMC_RAM1_IRQ_CROSS_BAR);

        Intc_Init();
        Intc_IntEnable(0);

        Intc_IntRegister(OCMC_RAM1_IRQ_NO, funcPtr, NULL);

        Intc_IntPrioritySet(OCMC_RAM1_IRQ_NO, 1, 0);
        Intc_SystemEnable(OCMC_RAM1_IRQ_NO);

        OCMCIntEnable(SOC_OCMC_RAM1_CFG_BASE, 0, intFlag);
    }

    return exitStatus;
}

int main(void)
{
    char              mainMenuOption;
    volatile uint32_t testDone = 1;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif

    /*Bring IPU out of reset*/
    HW_WR_REG32(IPU1_RESET_ADDRESS, 0);
    HW_WR_REG32(IPU2_RESET_ADDRESS, 0);

    while (1)
    {
        mainMenu(&mainMenuOption);

        if (OCMC_BASIC_TEST == mainMenuOption)
        {
            ocmcBasicTest(mainMenuOption);
        }
        else if (OCMC_ADDR_SEQ_TEST == mainMenuOption)
        {
            ocmcAddrSeqTest(mainMenuOption);
        }
        else if (OCMC_OVFL_MID_TEST == mainMenuOption)
        {
            ocmcOvflMidTest(mainMenuOption);
        }
        else if (OCMC_OVFL_WRP_TEST == mainMenuOption)
        {
            ocmcOvflWrpTest(mainMenuOption);
        }
        else if (OCMC_UDFL_TEST == mainMenuOption)
        {
            ocmcUDflTest(mainMenuOption);
        }
        else if (OCMC_SHT_FRM_TEST == mainMenuOption)
        {
            ocmcShtFrmTest(mainMenuOption);
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nOCMC board diagnostic test exiting...", -1);
            break;
        }
    }
    while (testDone) ;
    return 0;
}

static int32_t ocmcOvflWrpTest(char mainMenuOption)
{
    uint32_t    virtStartAddr     = 0;
    uint32_t    virtStartAddrRead = 0;
    uint32_t    exitStatus        = 0;
    IntrFuncPtr funcPtr;
    char        eccMode = 0;

    funcPtr = (IntrFuncPtr) ocmcOvflWrpIsr;

    while (1)
    {
        exitStatus =
            ocmcInit(&virtStartAddr, OCMC_CBUF_OVER_FLOW_WRAP_FOUND,
                     mainMenuOption,
                     funcPtr,
                     &eccMode);
        if (exitStatus)
        {
            break;
        }

        /*Write pointer*/
        write_addr = (uint32_t *) virtStartAddr;
        uart_val_print(virtStartAddr, "\r\nWrite pointer virtual start addr = ");

        /* Get read pointer*/
        /*virtStartAddrRead = OCMCVBufStartAddrGet(SOC_OCMC_RAM1_CFG_BASE, 0);*/
        virtStartAddrRead = virtStartAddr;
        uart_val_print(virtStartAddrRead, "\r\nRead pointer virtual start addr= ");
        read_addr = (uint32_t *) (virtStartAddrRead);

        /************* first frame**************/
        nextVal = 0;
        /*write 1st slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 2nd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 2nd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 2nd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 3rd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Write pointer*/
        write_addr = (uint32_t *) virtStartAddr;

        /*
         * Reading the first frame is not yet completed but the second frame
         * starts which gives overflow WRAP error. Writing of the new frame does
         * not overlap the previous frame data as the writes are disabled till
         * new frame write and read event occurs. The frame will be discarded
         */

        /*write 1st slice of second frame*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*waiting till reading of the previous frame completes*/
        while (!newFrameStart) ;

        /*Frame start pointer*/
        read_addr = (uint32_t *) virtStartAddr;

        /********** Overflowed discarded frame *************/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n Discarded invalid frame ", -1);

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 2nd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 2nd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 2nd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 3rd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 3rd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 3rd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*Frame start pointer*/
        write_addr = (uint32_t *) virtStartAddr;
        read_addr  = (uint32_t *) virtStartAddr;

        /************  Valid third New frame***************/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n New valid frame ", -1);
        /*write 1st slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 2nd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 2nd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 2nd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 3rd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 3rd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 3rd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        ocmcDeInit(virtStartAddr);

        UARTConfigPuts(uartBaseAddr, "\r\n OCMC Overflow wrap test successful", -1);
    }
    return 0;
}

static int32_t ocmcShtFrmTest(char mainMenuOption)
{
    uint32_t    virtStartAddr     = 0;
    uint32_t    virtStartAddrRead = 0;
    uint32_t    exitStatus        = 0;
    IntrFuncPtr funcPtr;
    char        eccMode = 0;

    funcPtr = (IntrFuncPtr) ocmcShtFrmTIsr;

    while (1)
    {
        exitStatus =
            ocmcInit(&virtStartAddr, OCMC_CBUF_SHORT_FRAME_DETECT,
                     mainMenuOption,
                     funcPtr,
                     &eccMode);
        if (exitStatus)
        {
            break;
        }

        /*Write pointer*/
        write_addr = (uint32_t *) virtStartAddr;
        uart_val_print(virtStartAddr, "\r\nWrite pointer virtual start addr = ");

        /* Get read pointer*/
        // virtStartAddrRead = OCMCVBufStartAddrGet(SOC_OCMC_RAM1_CFG_BASE, 0);
        virtStartAddrRead = virtStartAddr;
        uart_val_print(virtStartAddrRead, "\r\nRead pointer virtual start addr= ");
        read_addr = (uint32_t *) (virtStartAddrRead);

        /************* first frame**************/
        nextVal = 0;
        /*write 1st slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 2nd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 2nd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord / 2, read_addr);
        read_addr += cBufSizeInWord / 2;

        /*set write pointer to frame start*/
        write_addr = (uint32_t *) virtStartAddr;

        /*write 1st slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        while (!shortframe) ;

        ocmcDeInit(virtStartAddr);

        UARTConfigPuts(uartBaseAddr, "\r\n OCMC short frame error test successful", -1);
    }
    return 0;
}

static int32_t ocmcUDflTest(char mainMenuOption)
{
    uint32_t    virtStartAddr     = 0;
    uint32_t    virtStartAddrRead = 0;
    uint32_t    value[cBufSizeInWord];
    uint32_t    exitStatus = 0;
    IntrFuncPtr funcPtr;
    char        eccMode = 0;

    funcPtr = (IntrFuncPtr) ocmcUDflIsr;

    while (1)
    {
        exitStatus =
            ocmcInit(&virtStartAddr, OCMC_CBUF_UNDERFLOW, mainMenuOption,
                     funcPtr,
                     &eccMode);
        if (exitStatus)
        {
            break;
        }

        /*Write pointer*/
        write_addr = (uint32_t *) virtStartAddr;
        uart_val_print(virtStartAddr, "\r\nWrite pointer virtual start addr = ");

        /* Get read pointer*/
        /*virtStartAddrRead = OCMCVBufStartAddrGet(SOC_OCMC_RAM1_CFG_BASE, 0);*/
        virtStartAddrRead = virtStartAddr;
        uart_val_print(virtStartAddrRead, "\r\nRead pointer virtual start addr= ");
        read_addr = (uint32_t *) (virtStartAddrRead);

        /************* first frame**************/
        nextVal = 0;
        /*write 1st slice*/
        nextVal = fillBuffer(value, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, value);
        write_addr += cBufSizeInWord;

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*Reading 2nd slice causes underflow event*/
        UARTConfigPuts(uartBaseAddr, "\r\n 2nd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*Wait till underflow error is cleared*/
        while (!underflow) ;

        /*write 3rd slice*/
        nextVal = fillBuffer(value, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, value);
        write_addr += cBufSizeInWord;

        /*Read 3rd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 3rd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        ocmcDeInit(virtStartAddr);

        UARTConfigPuts(uartBaseAddr, "\r\n OCMC Underflow test successful", -1);
    }
    return 0;
}

static int32_t ocmcOvflMidTest(char mainMenuOption)
{
    uint32_t    virtStartAddr     = 0;
    uint32_t    virtStartAddrRead = 0;
    uint32_t    exitStatus        = 0;
    IntrFuncPtr funcPtr;
    char        eccMode = 0;

    funcPtr = (IntrFuncPtr) ocmcOvflMidIsr;

    while (1)
    {
        exitStatus =
            ocmcInit(&virtStartAddr, OCMC_CBUF_OVERFLOW_MID_FOUND,
                     mainMenuOption,
                     funcPtr,
                     &eccMode);
        if (exitStatus)
        {
            break;
        }

        /*Write pointer*/
        write_addr = (uint32_t *) virtStartAddr;
        uart_val_print(virtStartAddr, "\r\nWrite pointer virtual start addr = ");

        /* Get read pointer*/
        /*virtStartAddrRead = OCMCVBufStartAddrGet(SOC_OCMC_RAM1_CFG_BASE, 0);*/
        virtStartAddrRead = virtStartAddr;
        uart_val_print(virtStartAddrRead, "\r\nRead pointer virtual start addr= ");
        read_addr = (uint32_t *) (virtStartAddrRead);

        /************* first frame**************/
        nextVal = 0;
        /*write 1st slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 2nd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*write 3rd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*waiting till reading of the previous sub frame completes*/
        while (!overflowMid) ;

        /*Read 3rd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n 3rd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        ocmcDeInit(virtStartAddr);

        UARTConfigPuts(uartBaseAddr, "\r\n OCMC Overflow mid test successful", -1);
    }
    return 0;
}

static int32_t ocmcAddrSeqTest(char mainMenuOption)
{
    uint32_t    virtStartAddr     = 0;
    uint32_t    virtStartAddrRead = 0;
    uint32_t    exitStatus        = 0;
    IntrFuncPtr funcPtr;
    char        eccMode = 0;
    funcPtr = (IntrFuncPtr) ocmcAddrSeqIsr;

    while (1)
    {
        exitStatus = ocmcInit(
            &virtStartAddr, OCMC_CBUF_WR_ADDR_SEQ_ERR |
            OCMC_CBUF_RD_ADDR_SEQ_ERR,
            mainMenuOption, funcPtr, &eccMode);
        if (exitStatus)
        {
            break;
        }

        /*Write pointer*/
        write_addr = (uint32_t *) virtStartAddr;
        uart_val_print(virtStartAddr, "\r\nWrite pointer virtual start addr = ");

        /* Get read pointer*/
        /*virtStartAddrRead = OCMCVBufStartAddrGet(SOC_OCMC_RAM1_CFG_BASE, 0);*/
        virtStartAddrRead = virtStartAddr;
        uart_val_print(virtStartAddrRead, "\r\nRead pointer virtual start addr= ");
        read_addr = (uint32_t *) (virtStartAddrRead);

        /************* first frame**************/
        nextVal = 0;
        /*write 1st slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 1st slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n 1st slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write 2nd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord;

        /*Read 2nd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n 2nd slice ", -1);
        readSubFrame(cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord;

        /*write partial 3rd slice*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord / 2, write_addr, gValue);
        write_addr += cBufSizeInWord / 2;

        /*Read partial 3rd slice*/
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n 3rd partial slice ", -1);
        readSubFrame(cBufSizeInWord / cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord / cBufSizeInWord;

        /*Set read pointer to previous subframe address*/
        read_addr -= (cBufSizeInWord + 1);

        /*Reading of the previous subframe generates read sequence error*/
        UARTConfigPuts(uartBaseAddr, 
            "\r\n\r\n *Reading of the previous subframe generates read sequence error ",
            -1);
        readSubFrame(cBufSizeInWord / cBufSizeInWord, read_addr);
        read_addr += cBufSizeInWord / cBufSizeInWord;

        while (!readSequence) ;

        UARTConfigPuts(uartBaseAddr, "\r\n OCMC read sequence error test successful", -1);

        /*Set write pointer to previous subframe address*/
        write_addr -= (cBufSizeInWord + 1);

        /*Writing to previous subframe generates write sequence error*/
        nextVal = fillBuffer(gValue, nextVal, cBufSizeInWord);
        writeSubFrame(cBufSizeInWord / cBufSizeInWord, write_addr, gValue);
        write_addr += cBufSizeInWord / cBufSizeInWord;

        while (!writeSequence) ;

        ocmcDeInit(virtStartAddr);

        UARTConfigPuts(uartBaseAddr, "\r\n OCMC write sequence error test successful", -1);
    }
    return 0;
}

static int32_t ocmcBasicTest(char mainMenuOption)
{
    uint32_t          virtStartAddr = 0;
    uint32_t         *obtWrite_addr = NULL;
    uint32_t          msgtoRx, msgfromRx = 0;
    volatile uint32_t result     = 1;
    volatile uint32_t testDone   = 1;
    uint32_t          exitStatus = 0;
    char eccMode = 0;

    while (1)
    {
        exitStatus = ocmcInit(&virtStartAddr, 0, mainMenuOption, NULL, &eccMode);
        if (exitStatus)
        {
            break;
        }
        result = 1;

        /*Wait for message from Receiver: A15( Tda2xx)/ C66x(Tda3xx)*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                                  &msgfromRx))) ;
        if (0x2233 == msgfromRx)
        {
            /* Send virtual address */
            MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                               virtStartAddr);
        }

        obtWrite_addr = (uint32_t *) virtStartAddr;

        uart_val_print(virtStartAddr, "\r\nVirtual start addr M4= ");

        /*write 1st slice*/
        *obtWrite_addr++ = 0x01;
        *obtWrite_addr++ = 0x02;
        *obtWrite_addr++ = 0x03;
        *obtWrite_addr++ = 0x04;
        /* send message to A15( Tda2xx)/ C66x(Tda3xx)*/
        msgtoRx = 1;

        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0, msgtoRx);

        /*Wait for message from A15( Tda2xx)/ C66x(Tda3xx)*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                                  &msgfromRx))) ;
        if (0x04 == msgfromRx)
        {
            uart_val_print(msgfromRx, "\r\n1st slice read complete");
        }
        else
        {
            uart_val_print(msgfromRx, "\r\n1st slice read failed");
            result = 0;
        }

        /*write 2nd slice*/
        *obtWrite_addr++ = 0x05;
        *obtWrite_addr++ = 0x06;
        *obtWrite_addr++ = 0x07;
        *obtWrite_addr++ = 0x08;
        /* send message to A15( Tda2xx)/ C66x(Tda3xx)*/
        msgtoRx = 2;

        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0, msgtoRx);

        /*Wait for message from A15( Tda2xx)/ C66x(Tda3xx)*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                                  &msgfromRx))) ;
        if (0x08 == msgfromRx)
        {
            uart_val_print(msgfromRx, "\r\n2nd slice read complete");
        }
        else
        {
            uart_val_print(msgfromRx, "\r\n2nd slice read failed");
            result = 0;
        }

        /*write 3rd slice*/
        *obtWrite_addr++ = 0x09;
        *obtWrite_addr++ = 0x0A;
        *obtWrite_addr++ = 0x0B;
        *obtWrite_addr++ = 0x0C;
        /* send message to M4*/
        msgtoRx = 3;

        MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0, msgtoRx);

        /*Wait for message from A15( Tda2xx)/ C66x(Tda3xx)*/
        while (MESSAGE_INVALID ==
               (MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                                  &msgfromRx))) ;
        if (0x0C == msgfromRx)
        {
            uart_val_print(msgfromRx, "\r\n3rd slice read complete");
        }
        else
        {
            uart_val_print(msgfromRx, "\r\n3rd slice read failed");
            result = 0;
        }

        ocmcDeInit(virtStartAddr);

        if (result)
        {
            UARTConfigPuts(uartBaseAddr, "\r\nTest Pass", -1);
        }
        else
        {
            if ('4' == eccMode)
            {
                UARTConfigPuts(uartBaseAddr, 
                    "\r\n\r\nNON_ECC_CODE_ACCESS mode is only used for DEBUG purpose",
                    -1);
                UARTConfigPuts(uartBaseAddr, "\r\nData written cannot be read from virtual buffer",
                         -1);
                UARTConfigPuts(uartBaseAddr, "\r\nTest Pass", -1);
            }
            else
            {
                UARTConfigPuts(uartBaseAddr, "\r\nTest Fail", -1);
            }
        }
    }
    return 0;
}

void mainMenu(char *option)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\n\r\n**** OCMC TEST ****", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nMenu:", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n1. OCMC Basic test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n2. OCMC Address Sequence test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n3. OCMC Overflow Mid test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n4. OCMC Overflow Wrap test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n5. OCMC Underflow test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\n6. OCMC Shortframe test", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nSelect OCMC test : ", -1);

        /* Get option */
        UARTConfigGets(uartBaseAddr, option, 1);

        if (OCMC_BASIC_TEST == *option || OCMC_ADDR_SEQ_TEST == *option ||
            OCMC_OVFL_MID_TEST == *option || OCMC_OVFL_WRP_TEST == *option ||
            OCMC_SHT_FRM_TEST == *option || OCMC_UDFL_TEST == *option ||
            EXIT(*option))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nEnter Valid option\r\n", -1);
        }
    }
}

static void mainSubMenu(char *mainMenuOption, char *eccMode)
{
    while (1)
    {
        UARTConfigPuts(uartBaseAddr, "\r\nEnter the OCMC mode", -1);
        if (*mainMenuOption == OCMC_BASIC_TEST)
        {
            UARTConfigPuts(uartBaseAddr, "\r\n1. FULL_ECC  mode ", -1);
            UARTConfigPuts(uartBaseAddr, "\r\n2. BLOCK_ECC mode ", -1);
            UARTConfigPuts(uartBaseAddr, "\r\n3. NON_ECC_DATA_ACCESS mode", -1);
            UARTConfigPuts(uartBaseAddr, "\r\n4. NON_ECC_CODE_ACCESS mode ", -1);
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\n1. FULL_ECC  mode ", -1);
            UARTConfigPuts(uartBaseAddr, "\r\n2. BLOCK_ECC mode ", -1);
        }
        UARTConfigPuts(uartBaseAddr, "\r\nx. Exit", -1);
        UARTConfigPuts(uartBaseAddr, "\r\nEnter value : ", -1);

        /* Get option */
        UARTConfigGets(uartBaseAddr, eccMode, 1);

        if (NON_ECC_DATA_ACCESS == *eccMode || NON_ECC_CODE_ACCESS ==
            *eccMode ||
            FULL_ECC == *eccMode || BLOCK_ECC == *eccMode ||
            EXIT(*eccMode))
        {
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr, "\r\nEnter Valid option\r\n", -1);
        }
    }
}
