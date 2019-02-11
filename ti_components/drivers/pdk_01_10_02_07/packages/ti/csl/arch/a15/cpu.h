/*
 *  Copyright (c) Texas Instruments Incorporated 2015
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
 *  \ingroup CSL_ARCH_A15
 *  \defgroup CSL_ARCH_A15_CPU CPU
 *
 *  @{
 */
/**
 *  \file  cpu.h
 *
 *  \brief This file contains the API prototypes for configuring CPU.
 */

#ifndef CPU_H_
#define CPU_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief     This API can be used to switch from any previleged mode of ARM to
 *            user mode. After this API is called, the program will continue
 *            to operate in non-privileged mode, until any exception occurs.
 *            After the exception is serviced, execution will continue in user
 *            mode.
 *
 * \return    None.
 *
 * Note : All the access to system configuration which needs privileged access
 *        shall be done before this API is called.
 **/
extern void CPUSwitchToUserMode(void);

/**
 * \brief     This API can be used to switch from user mode to privileged mode
 *            The priviledge mode will be system mode. System mode will share
 *            the same resources as user mode, but with privileges.
 *
 * \return    None.
 *
 * Note : All the access to system configuration which needs privileged access
 *        can be done after calling this API.
 **/
extern void CPUSwitchToPrivilegedMode(void);

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief     This API is called when the CPU is aborted Both IRQ and FIQ will
 *            be disabled when the CPU gets an abort and calls this API.
 *
 * \return    None.
 *
 * Note : The user can perform error handling such as an immediate reset
 *        inside this API if required.
 **/
 extern void CPUAbortHandler(void);

/**
 *
 * \brief     Wrapper function for the IRQ disable function
 *
 * \return    None.
 *
*/
extern void CPUirqd(void);

/**
 *
 * \brief     Wrapper function for the IRQ enable function
 *
 * \return    None.
 *
*/
extern void CPUirqe(void);

/**
 *
 * \brief     Wrapper function for the FIQ disable function
 *
 * \return    None.
 *
*/
extern void CPUfiqd(void);

/**
 *
 * \brief     Wrapper function for the FIQ enable function
 *
 * \return    None.
 *
*/
extern void CPUfiqe(void);

/**
 *
 * \brief     Wrapper function to send event to all cores in the cluster
 *
 * \return    None.
 *
*/
extern void CPUSendEvent(void);

/**
 *
 * \brief     Wrapper function to disable CPSR A-Bit which enables Abort interupts
 *
 * \return    None.
 *
*/
extern void CPUDisableCPSRABit(void);

/**
 *
 * \brief     Wrapper function for the IRQ status
 *
 * \return    Status.
 *
*/
extern uint32_t CPUIntStatus(void);

#ifdef __cplusplus
}
#endif
#endif /* CPU_H___ */
 /** @} */
/********************************* End of file ******************************/
