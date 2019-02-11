/*
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
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

/*============================================================================
 *  @file   GptCfg.c
 *
 *  @brief  GP Timer configuration
 */

#include <ti/ipc/Std.h>
#include <Gpt.h>

/*
 *  ======== ti_ipc_Gpt_cfg ========
 *  The GP Timer configuration object
 */
Gpt_Config ti_ipc_Gpt_cfg = {
    /* List the processor that uses each timer as a watchdog timer */
    .wdtOwnerProcessor   = {
        NULL,     /* GPT_TIMER_1 */
        NULL,     /* GPT_TIMER_2 */
        NULL,     /* GPT_TIMER_3 */
        "IPU2",   /* GPT_TIMER_4 */
        NULL,     /* GPT_TIMER_5 */
        NULL,     /* GPT_TIMER_6 */
        "IPU1",   /* GPT_TIMER_7 */
        "IPU1",   /* GPT_TIMER_8 */
        "IPU2",   /* GPT_TIMER_9 */
        "DSP1",   /* GPT_TIMER_10 */
        NULL      /* GPT_TIMER_11 */
    }
};
