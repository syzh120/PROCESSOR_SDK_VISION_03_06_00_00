/*
 * Copyright (c) 2014-2015, Texas Instruments Incorporated
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
#ifndef _GPT_H
#define _GPT_H

#include <stdint.h>

#if defined (__cplusplus)
extern "C" {
#endif

/* List of timers */
/* The QNX BSP fully enables GP Timers 1-11, thus we support the same set */
typedef enum {
    GPT_TIMER_1 = 0,
    GPT_TIMER_2,
    GPT_TIMER_3,
    GPT_TIMER_4,
    GPT_TIMER_5,
    GPT_TIMER_6,
    GPT_TIMER_7,
    GPT_TIMER_8,
    GPT_TIMER_9,
    GPT_TIMER_10,
    GPT_TIMER_11,
    GPT_TIMER_NUM,
    GPT_TIMER_INVALID
} Gpt_Nums;

typedef struct Gpt_Config {
    char * wdtOwnerProcessor[GPT_TIMER_NUM];
} Gpt_Config;

/* Gpt configuration structure */
extern Gpt_Config ti_ipc_Gpt_cfg;

/* Enable GP timers */
int Gpt_setup(Gpt_Config * cfg);

/* Disable GP timers */
int Gpt_destroy();

/* Wire the Watchdog interrupts to trigger recovery */
int Gpt_wdt_attach(int proc_id);

/* Un-hook the Watchdog interrupt handler */
int Gpt_wdt_detach(int proc_id);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* _GPT_H */
