/*
 *  Copyright (C) 2016-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   interrupt.c
 *
 *  \brief  Interrupt related APIs.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <interrupt.h>
#include <arp32_wugen.h>
#include <arp32.h>
#include <inth.h>


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void Intc_IntClrPend(uint16_t intrNum)
{

}

void Intc_Init(void)
{

}

void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, const void *fun_arg)
{
    EVE_INTH_InterruptRegister((uint8_t) intrNum, (uint32_t)fptr, fun_arg);

}

void Intc_IntUnregister(uint16_t intrNum)
{
    EVE_INTH_InterruptUnregister((uint8_t) intrNum);
}

void Intc_IntPrioritySet(uint16_t intrNum,
                         uint16_t priority,
                         uint8_t hostIntRoute)
{
    EVE_INTH_InterruptPrioritySet(intrNum, priority);
}

void Intc_SystemEnable(uint16_t intrNum)
{
    EVE_INTH_InterruptEnable((uint8_t) intrNum);
}

void Intc_SystemDisable(uint16_t intrNum)
{
    EVE_INTH_InterruptDisable((uint8_t) intrNum);
}

uint8_t Intc_IntDisable(void)
{
    _disable_interrupts();
    return 0U;
}

void Intc_IntEnable(uint32_t status)
{
    _enable_interrupts();
}

/********************************* End of file ******************************/
