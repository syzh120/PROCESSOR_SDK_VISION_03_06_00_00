/*
 * Copyright (c) 2011-2015, Texas Instruments Incorporated
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
/** ============================================================================
 *  @file       _IpcPower.h
 *  ============================================================================
 */

#ifndef ti_pm__IpcPower__include
#define ti_pm__IpcPower__include

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Structures & Definitions
 * =============================================================================
 */

#define MIRQ34_SHIFT                    2
#define MIRQ37_SHIFT                    5
#define MIRQ38_SHIFT                    6
#define MIRQ39_SHIFT                    7

/*
 * First 16 interrupts are internal interrupts only and do not
 * have WUGEN bits, and a WUGEN event register can accomodate
 * 32 interrupts, with one per bit. So IRQs 17 to 48 are programmed
 * in EVT0 register and IRQs 49 to 80 are programmed in EVT0
 * register.
 */
#define MIRQ_SHIFT(irq)                 (((irq) - 16) % 32)
#define IRQWAKEEN_SHIFT(irq)            (((irq) - 32) % 32)

#define MBX_INT                         50
#define GPT3_INT                        53
#define GPT4_INT                        54
#define GPT9_INT                        55
#define GPT11_INT                       56
#define MBX6_U1_INT                     66

#define DSP_GPT5_INT                    67
#define DSP_GPT6_INT                    68
#define DSP_MBX_INT                     57

#define WUGEN_MAILBOX_BIT               (1 << MIRQ34_SHIFT)
#define WUGEN_GPT3_BIT                  (1 << MIRQ37_SHIFT)
#define WUGEN_GPT4_BIT                  (1 << MIRQ38_SHIFT)
#define WUGEN_GPT9_BIT                  (1 << MIRQ39_SHIFT)

#define WUGEN_GPT11_BIT                 (1 << MIRQ_SHIFT(GPT11_INT))
#define WUGEN_MBX6_U1_BIT               (1 << MIRQ_SHIFT(MBX6_U1_INT))

#define DSP_SYS_IRQWAKEEN_GPT5_BIT      (1 << IRQWAKEEN_SHIFT(DSP_GPT5_INT))
#define DSP_SYS_IRQWAKEEN_GPT6_BIT      (1 << IRQWAKEEN_SHIFT(DSP_GPT6_INT))
#define DSP1_SYS_IRQWAKEEN_MBX5_U0_BIT   (1 << IRQWAKEEN_SHIFT(DSP_MBX_INT))
#define DSP2_SYS_IRQWAKEEN_MBX6_U0_BIT   (1 << IRQWAKEEN_SHIFT(DSP_MBX_INT))

/* Wake-up masks for interrupts 00-31 */
#define WUGEN_MEVT0                     0x4000100C
/* Wake-up masks for interrupts 32-63 */
#define WUGEN_MEVT1                     0x40001010
/* Wake-up masks for interrupts 32-63 */
#define DSP_SYS_IRQWAKEEN0              0x01D00020
/* Wake-up masks for interrupts 64-95 */
#define DSP_SYS_IRQWAKEEN1              0x01D00024

/* Enable Mailbox, GPT3, and GPT4 interrupts as Wakeup sources */
#define OMAP_IPU_WUGEN_INT_MASK0        0
#define OMAP_IPU_WUGEN_INT_MASK1        (WUGEN_MAILBOX_BIT | \
                                         WUGEN_GPT3_BIT    | \
                                         WUGEN_GPT4_BIT)
#define VAYU_IPU2_WUGEN_INT_MASK0       0
#define VAYU_IPU2_WUGEN_INT_MASK1       (WUGEN_GPT3_BIT | \
                                         WUGEN_MBX6_U1_BIT)
#define VAYU_IPU1_WUGEN_INT_MASK0       0
#define VAYU_IPU1_WUGEN_INT_MASK1       (WUGEN_GPT11_BIT | \
                                         WUGEN_MBX6_U1_BIT)
#define VAYU_DSP1_WUGEN_INT_MASK0       (DSP1_SYS_IRQWAKEEN_MBX5_U0_BIT)
#define VAYU_DSP1_WUGEN_INT_MASK1       (DSP_SYS_IRQWAKEEN_GPT5_BIT)
#define VAYU_DSP2_WUGEN_INT_MASK0       (DSP2_SYS_IRQWAKEEN_MBX6_U0_BIT)
#define VAYU_DSP2_WUGEN_INT_MASK1       (DSP_SYS_IRQWAKEEN_GPT6_BIT)

#define M3_SCR_REG                      0xE000ED10

#define SLEEPONEXIT_BIT                 1
#define DEEPSLEEP_BIT                   2
#define SEVONPEND_BIT                   4

/* User registered functions storage element */
typedef struct IpcPower_CallbackElem {
    IpcPower_Event                  event;
    IpcPower_CallbackFuncPtr        callback;
    Ptr                             data;
    struct IpcPower_CallbackElem    *next;
} IpcPower_CallbackElem;

/* Pre-suspend function managing user callbacks */
Void IpcPower_preSuspend(Void);

/* Post-suspend function managing user callbacks */
Void IpcPower_postResume(Void);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ti_ipc__IpcPower__include */
