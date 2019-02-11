/*
 * Remote processor power management
 *
 * Copyright (c) 2011-2013 Texas Instruments. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __IPU_PM_H
#define __IPU_PM_H

typedef enum {
    GPTIMER_3 = 0,
    GPTIMER_4,
    GPTIMER_5,
    GPTIMER_6,
    GPTIMER_9,
    GPTIMER_11,
    GPTIMER_MAX
} GPTIMER_NUM;

enum pm_hib_timer_event{
    PM_HIB_TIMER_RESET,
    PM_HIB_TIMER_OFF,
    PM_HIB_TIMER_ON,
    PM_HIB_TIMER_DELETE,
    PM_HIB_TIMER_WDRESET,
    PM_HIB_TIMER_EXPIRE
};

typedef enum {
    CPUDLL_IVA_OPPNONE = 0,
    CPUDLL_IVA_OPP50 = CPUDLL_IVA_OPPNONE,
    CPUDLL_IVA_OPP100,
    CPUDLL_IVA_OPPTURBO
} cpudll_iva_opp_t;

#define WAIT_FOR_IDLE_TIMEOUT    1000u

#define PM_HIB_DEFAULT_TIME        5000    /* 5 SEC    */

#endif /* __IPU_PM_H */
