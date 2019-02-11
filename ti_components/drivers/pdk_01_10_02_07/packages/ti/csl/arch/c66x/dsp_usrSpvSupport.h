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
 *  \ingroup CSL_ARCH_C66X
 *  \defgroup CSL_ARCH_C66X_USR_SPRT CPU Mode
 *
 *  @{
 */
/**
 *  \file  dsp_usrSpvSupport.h
 *
 *  \brief This file contains the API prototypes for configuring mode of
 *         DSP (User/Supervisor)
 */
#ifndef DSP_USRSPVSUPPORT_H_
#define DSP_USRSPVSUPPORT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief CPU mode: SUPERVISOR */
#define DSP_CPU_MODE_SPV     (0x0U)

/** \brief CPU mode: USER */
#define DSP_CPU_MODE_USR     (0x1U)

/**
 * \brief   Set the DSP CPU mode to requested value.
 *          This will set up the SWENR handler internally on first execution.
 *
 * \param   mode Requested mode. 0 => Supervisor mode, 1 => User mode
 *
 * \return  none
 */
void DSP_setCpuMode(uint32_t mode);

/**
 * \brief   Get the current mode of CPU
 *
 * \return  0 => Supervisor mode, 1 => User mode
 */
uint32_t DSP_getCpuMode(void);

#ifdef __cplusplus
}
#endif

#endif
 /** @} */
