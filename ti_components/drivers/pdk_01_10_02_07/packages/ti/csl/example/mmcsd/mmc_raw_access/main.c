/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *   \file    main.c
 *
 *   \brief   Test application for MMC Sector raw read and write
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_mmcsd.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/soc.h>
#include <ti/csl/example/utils/common/inc/app_utils.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define BUFFER_SIZE    (512)
#define BIT(x) (1 << x)

/* SD Commands enumeration */
#define SD_CMD(x)   (x)

/* Command/Response flags for notifying some information to controller */
#define SD_CMDRSP_NONE      BIT(0)
#define SD_CMDRSP_STOP      BIT(1)
#define SD_CMDRSP_FS        BIT(2)
#define SD_CMDRSP_ABORT     BIT(3)
#define SD_CMDRSP_BUSY      BIT(4)
#define SD_CMDRSP_136BITS   BIT(5)
#define SD_CMDRSP_DATA      BIT(6)
#define SD_CMDRSP_READ      BIT(7)
#define SD_CMDRSP_WRITE     BIT(8)

/* Check RCA/status */
#define SD_RCA_ADDR(rca)             ((rca & 0xFFFF0000) >> 16)
#define SD_RCA_STAT(rca)             (rca & 0x0xFFFF)

/*To use UARTConfigPuts function for prints*/
#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
uint32_t baseAddress  = CSL_MPU_MMC2_REGS;
#ifndef SOC_L3INIT_CM_CORE_BASE
#define SOC_L3INIT_CM_CORE_BASE CSL_MPU_L3INIT_CM_CORE_REGS
#endif
#ifndef SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE
#define SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE CSL_MPU_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_REGS
#endif
#define CTRL_CORE_CONTROL_PBIAS CSL_CONTROL_CORE_PAD_CONTROL_PBIAS
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK CSL_CONTROL_CORE_PAD_CONTROL_PBIAS_SDCARD_BIAS_PWRDNZ_MASK
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK CSL_CONTROL_CORE_PAD_CONTROL_PBIAS_SDCARD_IO_PWRDNZ_MASK
#define CTRL_CORE_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK CSL_CONTROL_CORE_PAD_CONTROL_PBIAS_SDCARD_BIAS_VMODE_MASK
#endif

/*TODO PDK: hardcoded */
#define MMCSD_IN_FREQ                    (96000000) /* 96MHz */
#define MMCSD_INIT_FREQ                  (400000)   /* 400kHz */
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
uint32_t          baseAddress       = SOC_MMC2_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
uint32_t          baseAddress       = SOC_MMC2_BASE;
#endif

typedef struct _mmcsdCmd {
    unsigned int idx;
    unsigned int flags;
    unsigned int arg;
    signed char *data;
    unsigned int nblks;
    unsigned int rsp[4];
}mmcsdCmd;

uint32_t          hsmmcsd_dataLen   = 0;
uint32_t          hsmmcsd_blockSize = 0;
volatile uint8_t *hsmmcsd_buffer    = 0;
uint32_t          hsmmcsd_cid[4], hsmmcsd_rca, hsmmcsd_csd[4];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* MMC module enable functions */
static int32_t mmc2init(void);
void MMCSD_LDO_PWR(void);
void delay(uint32_t delay);

/* MMCSD Host Controller Functions */
static int32_t mmcHostCtrlInit(void);
unsigned int HSMMCSDCmdSend(mmcsdCmd *c);
static int32_t HSMMCSDCmdStatusGet(void);
static void HSMMCSDXferSetup(unsigned char rwFlag,
                            void         *ptr,
                            unsigned int  nBlks);
static unsigned int HSMMCSDXferStatusGet();

/* MMC Card Protocol Functions */
int32_t MMCSDCardReset(void);
int32_t MMCSDCardInit(void);
int32_t mmcBlockReadWrite(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO | 
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
    /*Pad configurations */
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A19,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A20,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A21,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A22,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A23,0x40001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A24,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A25,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A26,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A27,0x60001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_CS1,0x60001);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A19,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A20,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A21,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A22,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A23,0x40001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A24,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A25,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A26,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A27,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_CS1,0x60001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
    AppUtils_defaultInit();
#endif
}

int main(void)
{
    int32_t            retVal = STW_SOK;
    volatile uint32_t  done   = 1;

    /* Clock and pinmux settings */
    retVal = mmc2init();

    retVal += mmcHostCtrlInit();
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\nmmc Host Ctrl init Done.", -1);

        retVal = MMCSDCardInit();
    }
    if (retVal == STW_SOK)
    {
        retVal = mmcBlockReadWrite();
    }
    if (retVal == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\nData Read Write from eMMC Successful",-1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\nData Read Write from eMMC Failed",-1);
    }
    while (done) ;

    return 0;
}

int32_t mmcBlockReadWrite(void)
{
    int32_t  status = STW_SOK;
    mmcsdCmd cmd;
    uint8_t  flashReadData[BUFFER_SIZE];
    uint8_t  flashWriteData[BUFFER_SIZE];
    uint32_t i, n;
    /* TODO: Get the number of blocks from csd */
    uint32_t numBlocks = 50;
    uint32_t address;

    for (i = 0; i < BUFFER_SIZE; i++)
    {
        flashReadData[i]  = 0;
        flashWriteData[i] = i;
    }
    for (i = 0; i < numBlocks; i++)
    {
        address = hsmmcsd_blockSize * i;
        HSMMCSDXferSetup(0, &flashWriteData[0], 1);
        cmd.flags = SD_CMDRSP_WRITE | SD_CMDRSP_DATA;
        cmd.arg   = address;
        cmd.nblks = 1;
        cmd.idx   = SD_CMD(24);
        status    = HSMMCSDCmdSend(&cmd);
        if (status != STW_SOK)
        {
            return STW_EFAIL;
        }
        HSMMCSDXferStatusGet();

        cmd.idx   = SD_CMD(23);
        cmd.flags = 0;
        cmd.arg   = i;
        status    = HSMMCSDCmdSend(&cmd);
        if (status != STW_SOK)
        {
            return STW_EFAIL;
        }

        /* read from sector*/
        HSMMCSDXferSetup(1, &flashReadData[0], 1);
        cmd.idx   = SD_CMD(17);
        cmd.flags = SD_CMDRSP_READ | SD_CMDRSP_DATA;
        cmd.arg   = address;
        cmd.nblks = 1;
        status    = HSMMCSDCmdSend(&cmd);
        HSMMCSDXferStatusGet();
        for (n = 0; n < hsmmcsd_blockSize; n++)
        {
            if (flashReadData[n] != flashWriteData[n])
            {
                status = STW_EFAIL;
                UARTConfigPuts(uartBaseAddr,"\nData Mismatch error for block no %u address %u",
                            -1);
                UARTConfigPutNum(uartBaseAddr,n);
                break;
            }
        }
        if (status != STW_SOK)
        {
            break;
        }
        /* Reset the read data buffer */
        for (n = 0; n < hsmmcsd_blockSize; n++)
        {
            flashReadData[n] = 0;
        }
    }
    return status;
}

/* MMC module enable functions */
int32_t mmc2init(void)
{
    uint32_t tmpRegVal;
    /*MMC2- CM_L3INIT_MMC2_CLKCTRL */
    tmpRegVal  = HW_RD_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC2_CLKCTRL);
    tmpRegVal |= 0x03000000;
    HW_WR_REG32(SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_MMC2_CLKCTRL, tmpRegVal);

    MMCSD_LDO_PWR();
    
    /*MMC1 PAD Configuration*/
    padConfig_prcmEnable();
    
    /*Enable the module - mmc2  */
    HW_WR_FIELD32_RAW(0x4A009330,0x00000003U,0U,0x02U);

    return STW_SOK;
}

void delay(uint32_t delay)
{
    volatile uint32_t i;
    for (i = 0; i < (1000 * delay); ++i) ;
}

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

/* MMCSD Host Controller Functions */
static int32_t mmcHostCtrlInit(void)
{
    int32_t  status = STW_SOK;
    uint32_t intrMask;
    /*Refer to the MMC Host and Bus configuration steps in TRM */
    /* controller Reset */
    status = HSMMCSDSoftReset(baseAddress);
    if (status != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\nHS MMC/SD Reset failed\n\r", -1);
    }

    /* Lines Reset */
    status += HSMMCSDLinesReset(baseAddress, MMC_SYSCTL_SRA_MASK);
    /* Set supported voltage list */
    HSMMCSDSupportedVoltSet(baseAddress, MMC_CAPA_VS18_MASK |
                            MMC_CAPA_VS30_MASK);
    HSMMCSDSystemConfig(baseAddress, MMC_SYSCONFIG_AUTOIDLE_MASK);
    /* Set the bus width to 1 bit*/
    HSMMCSDBusWidthSet(baseAddress, 0x1);

    /* Set the bus voltage */
    HSMMCSDBusVoltSet(baseAddress, (MMC_HCTL_SDVS_3V0 << MMC_HCTL_SDVS_SHIFT));
    /* Bus power on */
    status +=
        HSMMCSDBusPower(baseAddress,
                        (MMC_HCTL_SDBP_PWRON << MMC_HCTL_SDBP_SHIFT));
    /* Set the initialization frequency */
    status += HSMMCSDBusFreqSet(baseAddress, MMCSD_IN_FREQ, MMCSD_INIT_FREQ, 0);

    if (0U == HSMMCSDInitStreamSend(baseAddress))
    {
        status = STW_EFAIL;
    }

    /* Enable interrupts */
    intrMask = (HS_MMCSD_INTR_CMDCOMP | HS_MMCSD_INTR_CMDTIMEOUT |
                HS_MMCSD_INTR_DATATIMEOUT | HS_MMCSD_INTR_TRNFCOMP);
    HSMMCSDIntrEnable(baseAddress, intrMask);

    if (status != STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\nMMC Host Controller init failed\n\r", -1);
    }

    return status;
}

unsigned int HSMMCSDCmdSend(mmcsdCmd *c)
{
    unsigned int cmdType = HS_MMCSD_CMD_TYPE_NORMAL;
    unsigned int dataPresent;
    unsigned int status = STW_SOK;
    unsigned int rspType;
    unsigned int cmdDir;
    unsigned int nblks;
    unsigned int cmd;

    if (c->flags & SD_CMDRSP_STOP)
    {
        cmdType = HS_MMCSD_CMD_TYPE_SUSPEND;
    }
    else if (c->flags & SD_CMDRSP_FS)
    {
        cmdType = HS_MMCSD_CMD_TYPE_FUNCSEL;
    }
    else if (c->flags & SD_CMDRSP_ABORT)
    {
        cmdType = HS_MMCSD_CMD_TYPE_ABORT;
    }

    cmdDir = (c->flags & SD_CMDRSP_READ) ? \
             HS_MMCSD_CMD_DIR_READ : HS_MMCSD_CMD_DIR_WRITE;

    dataPresent = (c->flags & SD_CMDRSP_DATA) ? 1 : 0;
    nblks       = (dataPresent == 1) ? c->nblks : 0;

    if (c->flags & SD_CMDRSP_NONE)
    {
        rspType = HS_MMCSD_NO_RESPONSE;
    }
    else if (c->flags & SD_CMDRSP_136BITS)
    {
        rspType = HS_MMCSD_136BITS_RESPONSE;
    }
    else if (c->flags & SD_CMDRSP_BUSY)
    {
        rspType = HS_MMCSD_48BITS_BUSY_RESPONSE;
    }
    else
    {
        rspType = HS_MMCSD_48BITS_RESPONSE;
    }

    cmd = HS_MMCSD_CMD(c->idx, cmdType, rspType, cmdDir);

    if (dataPresent)
    {
        HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_STAT_TRNFCOMP);

        HSMMCSDDataTimeoutSet(baseAddress, HS_MMCSD_DATA_TIMEOUT(27));
    }

    HSMMCSDCommandSend(baseAddress, cmd, c->arg, (void *) dataPresent,
                       nblks, ((uint32_t)0));

    HSMMCSDCmdStatusGet();
    if (status == STW_SOK)
    {
        HSMMCSDResponseGet(baseAddress, (uint32_t *) c->rsp);
    }

    return status;
}

static int32_t HSMMCSDCmdStatusGet(void)
{
    int32_t status = STW_SOK;

    while (1)
    {
        status = HSMMCSDIntrStatusGet(baseAddress, 0xFFFFFFFF);
        if (status & HS_MMCSD_STAT_CMDCOMP)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                   HS_MMCSD_STAT_CMDCOMP);
            break;
        }
        if (status & HS_MMCSD_STAT_ERR)
        {
            if (status & HS_MMCSD_STAT_CMDTIMEOUT)
            {
                HSMMCSDIntrStatusClear(baseAddress,
                                       HS_MMCSD_STAT_CMDTIMEOUT);
                status = STW_ETIMEOUT;
            }
            status = STW_EFAIL;
            break;
        }
    }
    return status;
}

static void HSMMCSDXferSetup(unsigned char rwFlag,
                             void         *ptr,
                             unsigned int  nBlks)
{
    HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_INTR_TRNFCOMP);

    if (rwFlag == 1)
    {
        HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_INTR_BUFRDRDY);
        HSMMCSDIntrStatusEnable(baseAddress, HS_MMCSD_INTR_BUFRDRDY);
        HSMMCSDIntrStatusDisable(baseAddress, HS_MMCSD_INTR_BUFWRRDY);
    }
    else
    {
        HSMMCSDIntrStatusClear(baseAddress, HS_MMCSD_INTR_BUFWRRDY);
        HSMMCSDIntrStatusEnable(baseAddress, HS_MMCSD_INTR_BUFWRRDY);
        HSMMCSDIntrStatusDisable(baseAddress, HS_MMCSD_INTR_BUFRDRDY);
    }

    HSMMCSDBlkLenSet(baseAddress, hsmmcsd_blockSize);
    hsmmcsd_dataLen = (nBlks * hsmmcsd_blockSize);
    hsmmcsd_buffer  = (volatile unsigned char *) ptr;
}

static unsigned int HSMMCSDXferStatusGet()
{
    volatile uint32_t status  = 0;
    int32_t           retVal  = 0;
    volatile uint32_t i       = 0, i_max = 0;
    volatile uint8_t *dst_bfr = hsmmcsd_buffer;
    volatile uint32_t temp;

    while (1)
    {
        status = HSMMCSDIntrStatusGet(baseAddress, 0xFFFFFFFF);

        if (status & HS_MMCSD_STAT_BUFRDRDY)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                    HS_MMCSD_STAT_BUFRDRDY);

            if (dst_bfr != NULL)
            {
                if (hsmmcsd_dataLen < hsmmcsd_blockSize)
                {
                    i_max = hsmmcsd_dataLen;
                }
                else
                {
                    i_max = hsmmcsd_blockSize;
                }
                /*Input data bfr will not be 4-byte aligned*/
                for (i = 0; i < i_max; i += 4)
                {
                    temp           = HW_RD_REG32(baseAddress + MMC_DATA);
                    dst_bfr[i]     = *((char *) &temp);
                    dst_bfr[i + 1] = *((char *) &temp + 1);
                    dst_bfr[i + 2] = *((char *) &temp + 2);
                    dst_bfr[i + 3] = *((char *) &temp + 3);
                }
                dst_bfr += i_max;
            }
        }
        if (status & HS_MMCSD_STAT_BUFWRRDY)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                    HS_MMCSD_STAT_BUFRDRDY);

            if (hsmmcsd_buffer != NULL)
            {
                for (i = 0; i < hsmmcsd_dataLen; i += 4)
                {
                    *((char *) &temp)     = hsmmcsd_buffer[i];
                    *((char *) &temp + 1) = hsmmcsd_buffer[i + 1];
                    *((char *) &temp + 2) = hsmmcsd_buffer[i + 2];
                    *((char *) &temp + 3) = hsmmcsd_buffer[i + 3];
                    HW_WR_REG32(baseAddress + MMC_DATA, temp);
                }
            }
        }
        if (status & HS_MMCSD_STAT_DATATIMEOUT)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                    HS_MMCSD_STAT_DATATIMEOUT);
            retVal = STW_ETIMEOUT;
            break;
        }
        if (status & HS_MMCSD_STAT_TRNFCOMP)
        {
            HSMMCSDIntrStatusClear(baseAddress,
                                    HS_MMCSD_STAT_TRNFCOMP);
            retVal = STW_SOK;
            break;
        }
    }
    return retVal;
}

/* MMC Card Protocol Functions */
int32_t MMCSDCardReset(void)
{
    int32_t  status = STW_SOK;
    mmcsdCmd cmd;

    cmd.idx   = SD_CMD(0);
    cmd.flags = SD_CMDRSP_NONE;
    cmd.arg   = 0;

    status = HSMMCSDCmdSend(&cmd);

    return status;
}

int32_t MMCSDCardInit(void)
{
    unsigned int status = 0;
    mmcsdCmd     cmd;

    /* CMD0 - reset card */
    status = MMCSDCardReset();

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }
    /* TODO: Detect mmc or sd card and do the init */

    do {
        /* CMD1 - send oper voltage */
        cmd.idx   = SD_CMD(1);
        cmd.flags = 0;
        cmd.arg   = 0xFF8000 | (0x2 << 29);

        status = HSMMCSDCmdSend(&cmd);
    } while (!(*cmd.rsp & (0x1 << 31)));
    /* Send CMD2, to get the card identification register */
    cmd.idx   = SD_CMD(2);
    cmd.flags = SD_CMDRSP_136BITS;
    cmd.arg   = 0;

    status = HSMMCSDCmdSend(&cmd);

    memcpy(&hsmmcsd_cid, cmd.rsp, 16);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }

    /* Send CMD3, to get the card relative address */
    cmd.idx   = SD_CMD(3);
    cmd.flags = 0;
    cmd.arg   = 0;

    status = HSMMCSDCmdSend(&cmd);

    hsmmcsd_rca = SD_RCA_ADDR(cmd.rsp[0]);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }
    /* Send CMD9, to get the card specific data */
    cmd.idx   = SD_CMD(9);
    cmd.flags = SD_CMDRSP_136BITS;
    cmd.arg   = hsmmcsd_rca << 16;

    status = HSMMCSDCmdSend(&cmd);

    memcpy(&hsmmcsd_csd, cmd.rsp, 16);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }

    // SD_CMD(13) to check card state
    HSMMCSDBlkLenSet(baseAddress, 512);
    cmd.idx   = SD_CMD(16);
    cmd.flags = SD_CMDRSP_NONE;
    cmd.arg   = 512;
    status    = HSMMCSDCmdSend(&cmd);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }
    else
    {
        /* TODO: Get the block size from csd */
        hsmmcsd_blockSize = 512;
    }

    /* Select the card */
    cmd.idx   = SD_CMD(7);
    cmd.flags = SD_CMDRSP_BUSY;
    cmd.arg   = hsmmcsd_rca << 16;

    status = HSMMCSDCmdSend(&cmd);

    if (status != STW_SOK)
    {
        return STW_EFAIL;
    }

    return STW_SOK;
}
/***************************** End Of File ***********************************/
