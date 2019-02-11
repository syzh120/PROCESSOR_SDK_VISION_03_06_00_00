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
 *  \file stw_qspiConfig.h
 *
 *  \brief This file defines the common configurations like flash cmd config etc...
 */

#ifndef STW_QSPI_CONFIG_H_
#define STW_QSPI_CONFIG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_qspi.h>
#include <st_qspi.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define QSPI_NUM_FLASHCMD_CFG   (sizeof (gStQSPIFlashCmdCfg) / \
                               sizeof (st_QSPIFlashCmdCfg))


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Defines the various QSPI Flash Command Configuration */
static st_QSPIFlashCmdCfg gStQSPIFlashCmdCfg[] =
{
    {
        ST_QSPI_FLASH_RDCMD_CFGID_DEFAULT,
        {
                8U,
                QSPI_CMD_READ,
                0U,
                32U,
                0U,
                0U,
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE,
                32U,
                0U,
        },
    },
    {
        ST_QSPI_FLASH_RDCMD_CFGID_QREAD,
        {
            8U,
            QSPI_CMD_FAST_QREAD,
            0U,
            32U,
            0U,
            8U,
            QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD,
            32U,
            0U,
        },
    },
    {
        ST_QSPI_FLASH_RDCMD_CFGID_FASTREAD,
        {
            8U,
            QSPI_CMD_FAST_READ,
            0U,
            32U,
            0U,
            8U,
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE,
            32U,
            0U,
        },
    },
    {
        ST_QSPI_FLASH_RDCMD_CFGID_DREAD,
        {
            8U,
            QSPI_CMD_FAST_DREAD,
            0U,
            32U,
            0U,
            8U,
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL,
            32U,
            0U,
        },
    },
    {
        ST_QSPI_FLASH_IDCMD_CFGID_DEFAULT,
        {
            8U,
            QSPI_CMD_MFGID,
            0U,
            24U,
            0U,
            0U,
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE,
            8U,
            2U,
        },
    },
    {
        ST_QSPI_FLASH_WRCMD_CFGID_DEFAULT,
        {
            8U,
            QSPI_CMD_WRITE,
            0U,
            32U,
            0U,
            0U,
            QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE,
            32U,
            0U,
        },
    },
    {
        ST_QSPI_FLASH_SECTERASECMD_CFGID_DEFAULT,
        {
            8U,
            QSPI_CMD_BLKERASE,
            0U,
            32U,
            0U,
            0U,
            0U,
            0U,
            0U,
        },
    },
    {
        ST_QSPI_FLASH_SUBSECTERASECMD_CFGID_DEFAULT,
        {
                8U,
                QSPI_CMD_PAGEERASE,
                0U,
                32U,
                0U,
                0U,
                0U,
                0U,
                0U,
        },
    },
    {
        ST_QSPI_FLASH_FULLERASECMD_CFGID_DEFAULT,
        {
                8U,
                QSPI_CMD_FULLERASE,
                0U,
                0U,
                0U,
                0U,
                0U,
                0U,
                0U,
        },
    },
    {
        ST_QSPI_FLASH_STATCMD_CFGID_DEFAULT,
        {
                8U,
                QSPI_CMD_RDSR,
                0U,
                0U,
                0U,
                0U,
                QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE,
                8U,
                1U,
        },
    },
    {
        ST_QSPI_FLASH_WRENCMD_CFGID_DEFAULT,
        {
                8U,
                QSPI_CMD_WREN,
                0U,
                0,
                0U,
                0U,
                0U,
                0U,
                0U,
        },
    },
};

#endif /* #ifndef STW_QSPI_CONFIG_H_ */
