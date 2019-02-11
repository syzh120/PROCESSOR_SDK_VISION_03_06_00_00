/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
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

/*!
 *   \file  timer_.h
 *
 *   \brief
 *      Private helper file used for timing stats
 *
 */


#ifndef TIMER__H_
#define TIMER__H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/

#if defined(CORTEX_MX)
#define SYSTICKREG                (*((volatile uint32_t*)0xE000E010U))
#define SYSTICKREL                (*((volatile uint32_t*)0xE000E014U))
#define SYSTICKVAL                (*((volatile uint32_t*)0xE000E018U))
static inline void TIMER_START(void)
{
    /*Systick Initialisation */
    /* Do nothing since M3/M4 SysTick is used for SysBios clock */
}

static inline uint32_t TIMER_READ(void)
{
  uint32_t cntl = SYSTICKVAL;
  return (cntl);
}

static inline uint32_t TIMER_DIFF(uint32_t time1, uint32_t time2)
{
  return (time1 >= time2) ? (time1 - time2) : (time1 + (SYSTICKREL-time2));
}

static inline uint32_t TIMER_READ_AND_DIFF(uint32_t time1)
{
  uint32_t time2 = TIMER_READ();
  return TIMER_DIFF(time1, time2);
}
#elif defined(CORTEX_AX)
static inline void TIMER_START(void)
{
    /*Systick Initialisation */
    /* Do nothing since M3/M4 SysTick is used for SysBios clock */
}

static inline uint32_t TIMER_READ(void)
{
    return (0);
}

static inline uint32_t TIMER_DIFF(uint32_t time1, uint32_t time2)
{
    return (time2 >= time1) ? (time2 - time1) : (time2 + (UINT32_MAX-time1));
}

static inline uint32_t TIMER_READ_AND_DIFF(uint32_t time1)
{
    uint32_t time2 = TIMER_READ();
    return TIMER_DIFF(time1, time2);
}
#elif defined(__TMS320C6X__)
#include <c6x.h>
static inline void TIMER_START(void)
{
    TSCL = 0;
}

static inline uint64_t TIMER_READ(void)
{
    uint32_t cntl = TSCL;
    return ((uint64_t) _itoll( TSCH, cntl ));
}

static inline uint64_t TIMER_DIFF(uint32_t time1, uint32_t time2)
{
    return (time2 >= time1) ? (time2 - time1) : (time2 + (UINT64_MAX-time1));
}

static inline uint64_t TIMER_READ_AND_DIFF(uint32_t time1)
{
    uint64_t time2 = TIMER_READ();
    return TIMER_DIFF(time1, time2);
}
#endif


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* TIMER__H_ */


