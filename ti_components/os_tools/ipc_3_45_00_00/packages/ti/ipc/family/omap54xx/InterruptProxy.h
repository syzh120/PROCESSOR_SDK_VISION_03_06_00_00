/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== InterruptProxy.h ========
 *  Proxy Interrupt Manager
 */

#ifndef ti_ipc_rpmsg_InterruptProxy__include
#define ti_ipc_rpmsg_InterruptProxy__include

#if defined(__cplusplus)
extern "C" {
#endif

#include <ti/sysbios/hal/Hwi.h>

#define INVALIDPAYLOAD       (0xFFFFFFFF)

#if defined(M3_ONLY) || defined(SMP)
#include <ti/ipc/family/omap54xx/InterruptIpu.h>

/*
 *************************************************************************
 *                      M3 Interrupt Proxy Macros
 *************************************************************************
 */

#define InterruptProxy_intEnable        InterruptIpu_intEnable

#define InterruptProxy_intDisable       InterruptIpu_intDisable

#define InterruptProxy_intRegister      InterruptIpu_intRegister

#define InterruptProxy_intSend          InterruptIpu_intSend

#define InterruptProxy_intClear         InterruptIpu_intClear
#endif

#if defined(DSP)
#include <ti/ipc/family/omap54xx/InterruptDsp.h>

/*
 *************************************************************************
 *                      DSP Interrupt Proxy Macros
 *************************************************************************
 */
#define InterruptProxy_intEnable        InterruptDsp_intEnable

#define InterruptProxy_intDisable       InterruptDsp_intDisable

#define InterruptProxy_intRegister      InterruptDsp_intRegister

#define InterruptProxy_intSend          InterruptDsp_intSend

#define InterruptProxy_intClear         InterruptDsp_intClear
#endif

#if defined(__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_ipc_rpmsg_InterruptProxy__include */
