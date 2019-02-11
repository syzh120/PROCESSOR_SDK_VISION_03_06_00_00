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

/*! ============================================================================
 *   \file  cslr_gmacsw_cpts.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for GMAC_SW
 *
 *  ============================================================================
 */

#ifndef CSLR_GMACSW_CPTS_H_
#define CSLR_GMACSW_CPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>

/* OS/Posix headers */

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct
{
#if defined(DEVICE_CENTAURUS)
    volatile uint8_t  RSVD0[0x500U];            /* offset since union is used for Centaurus */
#endif
    volatile uint32_t CPTS_IDVER;               /* 0x000U */
    volatile uint32_t CPTS_CONTROL;
    volatile uint32_t CPTS_RFTCLK_SEL;
    volatile uint32_t CPTS_TS_PUSH;
    volatile uint32_t CPTS_TS_LOAD_VAL;         /* 0x010U */
    volatile uint32_t CPTS_TS_LOAD_EN;
#if defined(DEVICE_VAYU)
    volatile uint32_t CPTS_TS_COMP_VAL;         /* 0x018U */
    volatile uint32_t CPTS_TS_COMP_LEN;
#else
    volatile uint8_t  RSVD1[8];                 /* 0x018U */
#endif
    volatile uint32_t CPTS_INTSTAT_RAW;         /* 0x020U */
    volatile uint32_t CPTS_INTSTAT_MASKED;
    volatile uint32_t CPTS_INT_ENABLE;
    volatile uint8_t  RSVD2[4];
    volatile uint32_t CPTS_EVENT_POP;           /* 0x030U */
    volatile uint32_t CPTS_EVENT_LOW;
    volatile uint32_t CPTS_EVENT_HIGH;
#if defined(DEVICE_VAYU)
    volatile uint32_t CPTS_EVENT_DOMAIN;
    volatile uint8_t  RSVD3[192];               /* 0x040U */
#else
    volatile uint8_t  RSVD3[196];               /* 0x03CU */
#endif
}
CSL_GMACSW_cptsRegs;


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* Field Definition Macros */

/* CPTS_CONTROL */

#define CSL_GMACSW_CPTS_CONTROL_HW4_TS_PUSH_EN_MASK (0x00000800U)
#define CSL_GMACSW_CPTS_CONTROL_HW4_TS_PUSH_EN_SHIFT (0x0000000BU)
#define CSL_GMACSW_CPTS_CONTROL_HW4_TS_PUSH_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_CONTROL_HW3_TS_PUSH_EN_MASK (0x00000400U)
#define CSL_GMACSW_CPTS_CONTROL_HW3_TS_PUSH_EN_SHIFT (0x0000000AU)
#define CSL_GMACSW_CPTS_CONTROL_HW3_TS_PUSH_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_CONTROL_HW2_TS_PUSH_EN_MASK (0x00000200U)
#define CSL_GMACSW_CPTS_CONTROL_HW2_TS_PUSH_EN_SHIFT (0x00000009U)
#define CSL_GMACSW_CPTS_CONTROL_HW2_TS_PUSH_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_CONTROL_HW1_TS_PUSH_EN_MASK (0x00000100U)
#define CSL_GMACSW_CPTS_CONTROL_HW1_TS_PUSH_EN_SHIFT (0x00000008U)
#define CSL_GMACSW_CPTS_CONTROL_HW1_TS_PUSH_EN_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_CONTROL_INT_TEST_MASK (0x00000002U)
#define CSL_GMACSW_CPTS_CONTROL_INT_TEST_SHIFT (0x00000001U)
#define CSL_GMACSW_CPTS_CONTROL_INT_TEST_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_CONTROL_CPTS_EN_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_CONTROL_CPTS_EN_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_CONTROL_CPTS_EN_RESETVAL (0x00000000U)

/* CPTS_TS_PUSH */

#define CSL_GMACSW_CPTS_TS_PUSH_TS_PUSH_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_TS_PUSH_TS_PUSH_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_TS_PUSH_TS_PUSH_RESETVAL (0x00000000U)

/* CPTS_TS_LOAD_VAL */

#define CSL_GMACSW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_MASK (0xFFFFFFFFU)
#define CSL_GMACSW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_TS_LOAD_VAL_TS_LOAD_VAL_RESETVAL (0x00000000U)

/* CPTS_TS_LOAD_EN */

#define CSL_GMACSW_CPTS_TS_LOAD_EN_TS_LOAD_EN_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_TS_LOAD_EN_TS_LOAD_EN_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_TS_LOAD_EN_TS_LOAD_EN_RESETVAL (0x00000000U)

/* CPTS_INTSTAT_RAW */

#define CSL_GMACSW_CPTS_INTSTAT_MASKED_TS_PEND_RAW_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_INTSTAT_MASKED_TS_PEND_RAW_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_INTSTAT_MASKED_TS_PEND_RAW_RESETVAL (0x00000000U)

/* CPTS_INTSTAT_MASKED */

#define CSL_GMACSW_CPTS_INTSTAT_MASKED_TS_PEND_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_INTSTAT_MASKED_TS_PEND_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_INTSTAT_MASKED_TS_PEND_RESETVAL (0x00000000U)

/* CPTS_INT_ENABLE */

#define CSL_GMACSW_CPTS_INT_ENABLE_TS_PEND_EN_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_INT_ENABLE_TS_PEND_EN_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_INT_ENABLE_TS_PEND_EN_RESETVAL (0x00000000U)

/* CPTS_EVENT_POP */

#define CSL_GMACSW_CPTS_EVENT_POP_EVENT_POP_MASK (0x00000001U)
#define CSL_GMACSW_CPTS_EVENT_POP_EVENT_POP_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_EVENT_POP_EVENT_POP_RESETVAL (0x00000000U)

/* CPTS_EVENT_LOW */

#define CSL_GMACSW_CPTS_EVENT_LOW_TIMESTAMP_MASK (0xFFFFFFFFU)
#define CSL_GMACSW_CPTS_EVENT_LOW_TIMESTAMP_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_EVENT_LOW_TIMESTAMP_RESETVAL (0x00000000U)

/* CPTS_EVENT_HIGH */

#define CSL_GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER_MASK (0x1F000000U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER_SHIFT (0x00000018U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_PORT_NUMBER_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_EVENT_HIGH_EVENT_TYPE_MASK (0x00F00000U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_EVENT_TYPE_SHIFT (0x00000014U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_EVENT_TYPE_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_EVENT_HIGH_MESSAGE_TYPE_MASK (0x000F0000U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_MESSAGE_TYPE_SHIFT (0x00000010U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_MESSAGE_TYPE_RESETVAL (0x00000000U)

#define CSL_GMACSW_CPTS_EVENT_HIGH_SEQUENCE_ID_MASK (0x0000FFFFU)
#define CSL_GMACSW_CPTS_EVENT_HIGH_SEQUENCE_ID_SHIFT (0x00000000U)
#define CSL_GMACSW_CPTS_EVENT_HIGH_SEQUENCE_ID_RESETVAL (0x00000000U)




/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* CSLR_GMACSW_CPTS_H_ */

