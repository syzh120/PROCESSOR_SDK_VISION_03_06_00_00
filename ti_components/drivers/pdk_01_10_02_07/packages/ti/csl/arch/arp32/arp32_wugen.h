/*
 *  Copyright (C) 2014-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup CSL_ARCH_ARP32
 *  \defgroup CSL_ARCH_ARP32_WUGEN WUGEN
 *
 *  @{
 */
/**
 *  \file  arp32_wugen.h
 *
 *  \brief This file contains the API prototypes for configuring ARP32_WAKEUPEN
 *         for EVE
 */

#ifndef ARP32_WUGEN_H
#define ARP32_WUGEN_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to initialize ARP32_WUGEN. All wakeup events will
 *          be disabled after initialization.
 *
 * \return  None.
 *
 **/
void ARP32_WUGEN_IRQ_Init(void);

/**
 * \brief  Disables all wakeup events for CPU.
 *
 * \return   None
 *
 **/
void ARP32_WUGEN_IRQ_DisableAll(void);

/**
 * \brief  Configure wakeup events by looking up the ARP32 interrupt settings.
 *
 * \return   None
 *
 **/
void ARP32_WUGEN_IRQ_Interrupt_Lookup(void);

/**
 * \brief   This API enables the ARP32 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void ARP32_WUGEN_IRQ_Enable(uint16_t intrNum);

/**
 * \brief   This API disables the ARP32 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void ARP32_WUGEN_IRQ_Disable(uint16_t intrNum);

#ifdef __cplusplus
}
#endif
#endif
 /** @} */
