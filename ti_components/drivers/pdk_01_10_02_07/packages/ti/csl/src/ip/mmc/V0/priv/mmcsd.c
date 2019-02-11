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
 *  \file   mmcsd.c
 *
 *  \brief  Device abstraction layer for HS MMC/SD
 *
 *   This file contains the device abstraction layer APIs for HS MMC/SD.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_mmcsd.h>
#include <ti/csl/csl_types.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t HSMMCSDSoftReset(uint32_t baseAddr)
{
    int32_t           retval  = STW_SOK;
    volatile uint32_t timeout = 0xFFFFU;

    HW_WR_FIELD32(baseAddr + MMC_SYSCONFIG, MMC_SYSCONFIG_SOFTRESET,
                  MMC_SYSCONFIG_SOFTRESET_ST_RST_W);

    do {
        if (HW_RD_FIELD32(baseAddr + MMC_SYSSTATUS, MMC_SYSSTATUS_RESETDONE) ==
            MMC_SYSSTATUS_RESETDONE_DONE)
        {
            break;
        }
        timeout--;
    } while (timeout > 0U);

    if (0U == timeout)
    {
        retval = STW_EFAIL;
    }
    return retval;
}

int32_t HSMMCSDLinesReset(uint32_t baseAddr, uint32_t flag)
{
    int32_t           retval      = STW_SOK;
    uint32_t          sysCtlValue = 0;
    volatile uint32_t timeout     = 0xFFFFU;

    sysCtlValue  = HW_RD_REG32(baseAddr + MMC_SYSCTL);
    sysCtlValue |= flag;
    HW_WR_REG32(baseAddr + MMC_SYSCTL, sysCtlValue);

    do {
        if ((HW_RD_REG32(baseAddr + MMC_SYSCTL) & flag) == (uint32_t)0U)
        {
            break;
        }
        timeout--;
    } while (timeout > 0U);

    if (0U == timeout)
    {
        retval = STW_EFAIL;
    }

    return retval;
}

void HSMMCSDSystemConfig(uint32_t baseAddr, uint32_t config)
{
    uint32_t sysConfigValue = HW_RD_REG32(baseAddr + MMC_SYSCONFIG);
    sysConfigValue &= ~((uint32_t) MMC_SYSCONFIG_STANDBYMODE_MASK |
                        (uint32_t) MMC_SYSCONFIG_CLOCKACTIVITY_MASK |
                        (uint32_t) MMC_SYSCONFIG_SIDLEMODE_MASK |
                        (uint32_t) MMC_SYSCONFIG_ENAWAKEUP_MASK |
                        (uint32_t) MMC_SYSCONFIG_AUTOIDLE_MASK);

    sysConfigValue |= config;
    HW_WR_REG32(baseAddr + MMC_SYSCONFIG, sysConfigValue);
}

void HSMMCSDBusWidthSet(uint32_t baseAddr, uint32_t width)
{
    switch (width)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_AM574x)
        case HS_MMCSD_BUS_WIDTH_8BIT:
            HW_WR_FIELD32(baseAddr + MMC_CON, MMC_CON_DW8,
                          MMC_CON_DW8_8BITMODE);
            break;
#endif
        case HS_MMCSD_BUS_WIDTH_4BIT:
            HW_WR_FIELD32(baseAddr + MMC_CON, MMC_CON_DW8,
                          MMC_CON_DW8_1_4BITMODE);
            HW_WR_FIELD32(baseAddr + MMC_HCTL, MMC_HCTL_DTW,
                          MMC_HCTL_DTW_4_BITMODE);
            break;
        case HS_MMCSD_BUS_WIDTH_1BIT:
            HW_WR_FIELD32(baseAddr + MMC_CON, MMC_CON_DW8,
                          MMC_CON_DW8_1_4BITMODE);
            HW_WR_FIELD32(baseAddr + MMC_HCTL, MMC_HCTL_DTW,
                          MMC_HCTL_DTW_1_BITMODE);
            break;
        default:
            break;
    }
}

void HSMMCSDBusVoltSet(uint32_t baseAddr, uint32_t volt)
{
    HW_WR_FIELD32(baseAddr + MMC_HCTL, MMC_HCTL_SDVS,
                  volt >> MMC_HCTL_SDVS_SHIFT);
}

int32_t HSMMCSDBusPower(uint32_t baseAddr, uint32_t pwr)
{
    int32_t           retval  = STW_SOK;
    volatile uint32_t timeout = 0xFFFFFU;

    HW_WR_FIELD32(baseAddr + MMC_HCTL, MMC_HCTL_SDBP,
                  pwr >> MMC_HCTL_SDBP_SHIFT);

    if (pwr == HS_MMCSD_BUS_POWER_ON)
    {
        do {
            if ((HW_RD_REG32(baseAddr + MMC_HCTL) & MMC_HCTL_SDBP_MASK) != 0U)
            {
                break;
            }
            timeout--;
        } while (timeout > 0U);
    }

    if (timeout == 0)
    {
        retval = STW_EFAIL;
    }
    return retval;
}

int32_t HSMMCSDIntClock(uint32_t baseAddr, uint32_t pwr)
{
    int32_t retval = STW_SOK;

    HW_WR_FIELD32(baseAddr + MMC_SYSCTL, MMC_SYSCTL_ICE,
                  pwr >> MMC_SYSCTL_ICE_SHIFT);

    if (pwr == HS_MMCSD_INTCLOCK_ON)
    {
        if (HSMMCSDIsIntClockStable(baseAddr, (uint32_t) 0xFFFFU) == 0U)
        {
            retval = STW_EFAIL;
        }
    }

    return retval;
}

uint32_t HSMMCSDIsIntClockStable(uint32_t baseAddr, uint32_t retry)
{
    volatile uint32_t status = 0;

    do {
        status = HW_RD_FIELD32(baseAddr + MMC_SYSCTL, MMC_SYSCTL_ICS);
        if ((status == 1U) || (retry == 0U))
        {
            break;
        }
        retry--;
    } while (retry > 0U);

    return status;
}

void HSMMCSDSupportedVoltSet(uint32_t baseAddr, uint32_t volt)
{
    uint32_t capaValue = HW_RD_REG32(baseAddr + MMC_CAPA);
    capaValue &= ~(MMC_CAPA_VS18_MASK | MMC_CAPA_VS30_MASK |
                   MMC_CAPA_VS33_MASK);
    capaValue |= volt;
    HW_WR_REG32(baseAddr + MMC_CAPA, capaValue);
}

uint32_t HSMMCSDIsHSupported(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + MMC_CAPA, MMC_CAPA_HSS);
}

void HSMMCSDDataTimeoutSet(uint32_t baseAddr, uint32_t timeout)
{
    HW_WR_FIELD32(baseAddr + MMC_SYSCTL, MMC_SYSCTL_DTO,
                  timeout >> MMC_SYSCTL_DTO_SHIFT);
}

int32_t HSMMCSDBusFreqSet(uint32_t baseAddr, uint32_t freq_in,
                          uint32_t freq_out, uint32_t bypass)
{
    volatile uint32_t clkd   = 0;
    int32_t           retval = STW_SOK;

    /* First enable the internal clocks */
    retval = HSMMCSDIntClock(baseAddr, (uint32_t) HS_MMCSD_INTCLOCK_ON);

    if ((bypass == (uint32_t) 0) && (STW_SOK == retval))
    {
        /* Calculate and program the divisor */
        clkd = freq_in / freq_out;
        if (clkd < (uint32_t) 2)
        {
            clkd = 2U;
        }
        else if (clkd > (uint32_t) 1023)
        {
            clkd = 1023U;
        }
        else
        {
            clkd = clkd;
        }

        /* Do not cross the required freq */
        while ((freq_in / clkd) > freq_out)
        {
            if (clkd == 1023U)
            {
                /* Return we we cannot set the clock freq */
                retval = STW_EFAIL;
                break;
            }

            clkd++;
        }
        if (STW_SOK == retval)
        {
            HW_WR_FIELD32(baseAddr + MMC_SYSCTL, MMC_SYSCTL_CLKD, clkd);

            /* Wait for the interface clock stabilization */
            if (HSMMCSDIsIntClockStable(baseAddr,
                                        (uint32_t) 0xFFFFU) == (uint32_t) 0)
            {
                retval = STW_EFAIL;
            }

            if (STW_SOK == retval)
            {
                /* Enable clock to the card */
                HW_WR_FIELD32(baseAddr + MMC_SYSCTL, MMC_SYSCTL_CEN,
                              MMC_SYSCTL_CEN_ENABLE);
            }
        }
    }

    return retval;
}

int32_t HSMMCSDInitStreamSend(uint32_t baseAddr)
{
    uint32_t status;
    uint32_t mmcCmdZero     = 0x0U;
    uint32_t mmcCmdComplete = 0xFFFFU;

    /* Enable the command completion status to be set */
    HSMMCSDIntrStatusEnable(baseAddr, (uint32_t) HS_MMCSD_SIGEN_CMDCOMP);

    /* Initiate the INIT command */
    HW_WR_FIELD32(baseAddr + MMC_CON, MMC_CON_INIT,
                  MMC_CON_INIT_INITSTREAM);
    HW_WR_REG32(baseAddr + MMC_CMD, mmcCmdZero);

    status = HSMMCSDIsCmdComplete(baseAddr, mmcCmdComplete);

    HW_WR_FIELD32(baseAddr + MMC_CON, MMC_CON_INIT,
                  MMC_CON_INIT_NOINIT);
    /* Clear all status */
    HSMMCSDIntrStatusClear(baseAddr, 0xFFFFFFFFU);

    return (int32_t) status;
}

void HSMMCSDIntrStatusEnable(uint32_t baseAddr, uint32_t flag)
{
    uint32_t ieValue = HW_RD_REG32(baseAddr + MMC_IE);
    ieValue |= flag;
    HW_WR_REG32(baseAddr + MMC_IE, ieValue);
}

void HSMMCSDIntrStatusDisable(uint32_t baseAddr, uint32_t flag)
{
    uint32_t ieValue = HW_RD_REG32(baseAddr + MMC_IE);
    ieValue &= ~flag;
    HW_WR_REG32(baseAddr + MMC_IE, ieValue);
}

void HSMMCSDIntrEnable(uint32_t baseAddr, uint32_t flag)
{
    uint32_t iseValue = HW_RD_REG32(baseAddr + MMC_ISE);
    iseValue |= flag;
    HW_WR_REG32(baseAddr + MMC_ISE, iseValue);
    HSMMCSDIntrStatusEnable(baseAddr, flag);
}

uint32_t HSMMCSDIntrStatusGet(uint32_t baseAddr, uint32_t flag)
{
    return HW_RD_REG32(baseAddr + MMC_STAT) & flag;
}

void HSMMCSDIntrStatusClear(uint32_t baseAddr, uint32_t flag)
{
    HW_WR_REG32(baseAddr + MMC_STAT, flag);
}

uint32_t HSMMCSDIsCmdComplete(uint32_t baseAddr, uint32_t retry)
{
    volatile uint32_t status = 0;

    do {
        status = HW_RD_FIELD32(baseAddr + MMC_STAT, MMC_STAT_CC);
        if ((status == 1U) || (retry == 0U))
        {
            break;
        }
        retry--;
    } while (retry > 0U);

    return status;
}

uint32_t HSMMCSDIsXferComplete(uint32_t baseAddr, uint32_t retry)
{
    volatile uint32_t status = 0;

    do {
        status = HW_RD_FIELD32(baseAddr + MMC_STAT, MMC_STAT_TC);
        if ((status == 1U) || (retry == 0U))
        {
            break;
        }
        retry--;
    } while (retry > 0U);

    return status;
}

void HSMMCSDBlkLenSet(uint32_t baseAddr, uint32_t blklen)
{
    HW_WR_FIELD32(baseAddr + MMC_BLK, MMC_BLK_BLEN,
                  blklen >> MMC_BLK_BLEN_SHIFT);
}

void HSMMCSDCommandSend(uint32_t baseAddr, uint32_t cmd,
                        uint32_t cmdarg, const void *data,
                        uint32_t nblks, uint32_t dmaEn)
{
    if (data != NULL)
    {
        cmd |= MMC_CMD_DP_MASK | MMC_CMD_MSBS_MASK | MMC_CMD_BCE_MASK;
    }

    if (dmaEn == 1U)
    {
        cmd |= MMC_CMD_DE_MASK;
    }

    /* Set the block information; block length is specified separately */
    HW_WR_FIELD32(baseAddr + MMC_BLK, MMC_BLK_NBLK, nblks);

    /* Set the command/command argument */
    HW_WR_REG32(baseAddr + MMC_ARG, cmdarg);
    HW_WR_REG32(baseAddr + MMC_CMD, cmd);
}

void HSMMCSDResponseGet(uint32_t baseAddr, uint32_t *rsp)
{
    rsp[0] = HW_RD_REG32(baseAddr + MMC_RSP10);
    rsp[1] = HW_RD_REG32(baseAddr + MMC_RSP32);
    rsp[2] = HW_RD_REG32(baseAddr + MMC_RSP54);
    rsp[3] = HW_RD_REG32(baseAddr + MMC_RSP76);
}

void HSMMCSDDataGet(uint32_t baseAddr, uint8_t *data, uint32_t len)
{
    uint32_t i;

    for (i = 0; i < (len / 4U); i++)
    {
        ((uint32_t *) data)[i] = HW_RD_REG32(baseAddr + MMC_DATA);
    }
}

uint32_t HSMMCSDIsCardInserted(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + MMC_PSTATE, MMC_PSTATE_CINS);
}

uint32_t HSMMCSDIsCardWriteProtected(uint32_t baseAddr)
{
    return HW_RD_FIELD32(baseAddr + MMC_PSTATE, MMC_PSTATE_WP);
}
/********************************* End of file ******************************/

