/*
 *  Copyright (C) 2015-2018 Texas Instruments Incorporated
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
 *  \file     l3_firewall_mreqDomain_eve_app.c
 *
 *  \brief    This file contains L3FW test code for checking OCMC firewall.
 *
 *  \details  This application will produce violation by writing into write
 *            protected area. This has to be run along with
 *            'l3_firewall_mreqDomain_app'.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Needed by A15 App */
#define APP_L3FW_REGION_TARGET_ADDR1        (SOC_OCMC_RAM2_BASE)
#define APP_L3FW_REGION_START_ADDR1         (SOC_OCMC_RAM2_BASE + 0x0000U)
#define APP_L3FW_REGION_END_ADDR1           (SOC_OCMC_RAM2_BASE + 0x1000U)
#define APP_L3FW_REGION_TARGET_ADDR2        (SOC_OCMC_RAM2_BASE)
#define APP_L3FW_REGION_START_ADDR2         (SOC_OCMC_RAM2_BASE + 0x1000U)
#define APP_L3FW_REGION_END_ADDR2           (SOC_OCMC_RAM2_BASE + 0x2000U)
/**
 * \brief  This macro defines the Boolean that is used for True.
 */
#define SUCCESS                                        ((uint32_t) 1U)
/**
 * \brief  This macro defines the Boolean that is used for False.
 */
#define FAIL                                           ((uint32_t) 0U)

/* Needed by EVE app */
/* Address macros for violations */
#define APP_EVE1_VIOLATION_ADDR            (APP_L3FW_REGION_START_ADDR2 + 0x4U)
/** Access any address within region */
#define APP_EVE2_VIOLATION_ADDR            (APP_L3FW_REGION_START_ADDR1 + 0x4U)
/** Access any address within region */
#define APP_EVE_CORE_ID_EVE1                     (0)
#define APP_EVE_CORE_ID_EVE2                     (1U)


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/* None */
