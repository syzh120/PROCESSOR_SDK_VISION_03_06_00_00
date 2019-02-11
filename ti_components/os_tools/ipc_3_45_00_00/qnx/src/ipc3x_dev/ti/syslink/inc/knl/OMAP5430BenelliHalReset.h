/**
 *  @file   OMAP5430BenelliHalReset.h
 *
 *  @brief      Reset control module header file.
 *
 *              This module is responsible for handling reset-related hardware-
 *              specific operations.
 *              The implementation is specific to OMAP5430Benelli.
 *
 *
 *  @ver        02.00.00.44_pre-alpha3
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2013, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

#ifndef OMAP5430BENELLIHALRESET_H_0xbbef
#define OMAP5430BENELLIHALRESET_H_0xbbef


/* Module level headers */
#include <_ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 *  See _ProcDefs.h
 * =============================================================================
 */
#define INREG32(x) in32(x)
#define OUTREG32(x, y) out32(x, y)
#define SETBITREG32(x, y) OUTREG32(x, (INREG32(x) | (1 << y)))
#define CLRBITREG32(x, y) OUTREG32(x, (INREG32(x) & ~(1 << y)))
#define TESTBITREG32(x, y) (((INREG32(x) & (1 << y)) >> y) & 0x1)

#define CORE_PRM_BASE                   0x4ae06700

#define RM_IPU_RSTCTRL_OFFSET        0x210
#define RM_IPU_RSTCTRL               (CORE_PRM_BASE + RM_IPU_RSTCTRL_OFFSET)
#define RM_IPU_RST1_BIT              0
#define RM_IPU_RST1                  (1 << RM_IPU_RST1_BIT)
#define RM_IPU_RST2_BIT              1
#define RM_IPU_RST2                  (1 << RM_IPU_RST2_BIT)
#define RM_IPU_RST3_BIT              2
#define RM_IPU_RST3                  (1 << RM_IPU_RST3_BIT)

#define RM_IPU_RSTST_OFFSET          0x214
#define RM_IPU_RSTST                 (CORE_PRM_BASE + RM_IPU_RSTST_OFFSET)
#define RM_IPU_RST1ST_BIT            0
#define RM_IPU_RST1ST                (1 << RM_IPU_RST1ST_BIT)
#define RM_IPU_RST2ST_BIT            1
#define RM_IPU_RST2ST                (1 << RM_IPU_RST2ST_BIT)
#define RM_IPU_RST3ST_BIT            2
#define RM_IPU_RST3ST                (1 << RM_IPU_RST3ST_BIT)

#define CORE_CM2_BASE                   0x4a008700

#define CM_IPU_CLKSTCTRL_OFFSET      0x200
#define CM_IPU_CLKSTCTRL             (CORE_CM2_BASE + CM_IPU_CLKSTCTRL_OFFSET)
#define CM_IPU_CLKSTCTRL_CTRL_BITMASK 0x3
#define CM_IPU_CLKSTCTRL_CTRL_NO_SLEEP 0x0
#define CM_IPU_CLKSTCTRL_CTRL_SW_SLEEP 0x1
#define CM_IPU_CLKSTCTRL_CTRL_SW_WKUP 0x2
#define CM_IPU_CLKSTCTRL_CTRL_HW_AUTO 0x3
#define CM_IPU_CLKSTCTRL_CLKACTIVITY_BIT 8
#define CM_IPU_CLKSTCTRL_CLKACTIVITY_ON 0x1

#define CM_IPU_IPU_CLKCTRL_OFFSET 0x220
#define CM_IPU_IPU_CLKCTRL        (CORE_CM2_BASE + CM_IPU_IPU_CLKCTRL_OFFSET)
#define CM_IPU_IPU_CLKCTRL_MODULEMODE_BITMASK 0x3
#define CM_IPU_IPU_CLKCTRL_MODULEMODE_DISABLE 0x0
#define CM_IPU_IPU_CLKCTRL_MODULEMODE_HWAUTO 0x1

/* DSP PRCM Regs*/
#define CM_DSP_CLKSTCTRL      0x4A004400
#define CM_DSP_STATICDEP      0x4A004404
#define CM_DSP_DYNMICDEP      0x4A004408
#define CM_DSP_DSP_CLKCTRL    0x4A004420
#define PM_DSP_PWRSTCTRL      0x4aE06400
#define PM_DSP_PWRSTST        0x4AE06404
#define RM_DSP_RSTCTRL        0x4AE06410
#define RM_DSP_RSTST          0x4AE06414

#define RM_DSP_DSP_CONTEXT    0x4AE06424

#define RM_DSP_RSTCTRL_BIT              0x0
#define RM_DSP_RSTST_BIT                0x0
#define RM_DSP_MMU_RSTCTRL_BIT          0x1
#define RM_DSP_RST                      0x0
#define CM_DSP_CLKSTCTRL_CTRL_BITMASK   0x3
#define CM_DSP_CLKSTCTRL_CTRL_HW_AUTO   0x3



/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to control reset operations for this slave device. */


Int OMAP5430BENELLI_halResetCtrl (Ptr halObj, Processor_ResetCtrlCmd cmd);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* OMAP5430BenelliHalReset_H_0xbbec */
