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
 *  \details  This application will produce violation by writing/reading
*             into write/read protected area. This has to be run along with
 *            'l3_firewall_mreqDomain_app' which runs on A15.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "arp32.h"
#include <l3_firewall_mreqDomain.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
uint32_t uartBaseAddr = SOC_UART1_BASE;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    uint32_t cpu_num;
	volatile uint32_t tempVar = 0;

    /*
	 * 0x40400000 - 0x40401000 - EVE1 RW, EVE2 No Access - Region 1
	 * 0x40401000 - 0x40402000 - EVE2 RW, EVE1 No Access - Region 2
	 */
    /*Set MMU to no idle mode*/

    cpu_num = _get_cpunum();
	/* EVE 1 */
	if (cpu_num == (uint32_t)APP_EVE_CORE_ID_EVE1)
	{
		/* Will cause the fault */
        tempVar = HW_RD_REG32(APP_EVE1_VIOLATION_ADDR);
	}
	else if (cpu_num == (uint32_t)APP_EVE_CORE_ID_EVE2)
	{
		/* Will cause the fault */
        HW_WR_REG32(APP_EVE2_VIOLATION_ADDR, 0xDEADDEADU);
	}

	return 0;
}
