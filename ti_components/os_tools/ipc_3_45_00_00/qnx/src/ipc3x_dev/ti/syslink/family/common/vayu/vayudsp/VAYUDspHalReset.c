/*
 *  @file   VAYUDspHalReset.c
 *
 *  @brief      Reset control module.
 *
 *              This module is responsible for handling reset-related hardware-
 *              specific operations.
 *              The implementation is specific to VAYUDSP.
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013-2015, Texas Instruments Incorporated
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
 */

#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <Bitops.h>

/* Module level headers */
#include <_ProcDefs.h>
#include <Processor.h>

/* Hardware Abstraction Layer headers */
#include <VAYUDspHal.h>
#include <VAYUDspHalReset.h>

#include <hw/inout.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/* DSP PRCM Regs*/
#define CM_DSP_CLKSTCTRL      0x00
#define CM_DSP_STATICDEP      0x04
#define CM_DSP_DYNMICDEP      0x08
#define CM_DSP_DSP_CLKCTRL    0x20

#define PM_DSP_PWRSTCTRL      0x00
#define PM_DSP_PWRSTST        0x04
#define RM_DSP_RSTCTRL        0x10
#define RM_DSP_RSTST          0x14

#define DSP_SYS_MMU_CONFIG_OFFSET 0x18

/* =============================================================================
 * APIs called by VAYUDSPPROC module
 * =============================================================================
 */
/*!
 *  @brief      Function to control reset operations
 *
 *  @param      halObj  Pointer to the HAL object
 *  @param      cmd     Reset control command
 *  @param      arg     Arguments specific to the reset control command
 *
 *  @sa
 */
Int
VAYUDSP_halResetCtrl(Ptr halObj, VAYUDspHal_ResetCmd cmd)
{
    Int                     status = PROCESSOR_SUCCESS;
    VAYUDSP_HalObject *     halObject = NULL;
    UInt32                  cmBase;
    UInt32                  prmBase;
    UInt32                  mmuSysBase;
    UInt32                  addr;
    UInt32                  val;
    Int32                   counter = 10;

    GT_2trace(curTrace, GT_ENTER, "VAYUDSP_halResetCTRL", halObj, cmd);

    GT_assert(curTrace, (halObj != NULL));
    GT_assert(curTrace, (cmd < VAYUDspHal_Reset_EndValue));

    halObject = (VAYUDSP_HalObject *)halObj;
    cmBase = halObject->cmBase;
    prmBase = halObject->prmBase;
    mmuSysBase = halObject->mmuSysBase;

    switch (cmd) {
        case Processor_ResetCtrlCmd_Reset:
        {
            /* assert GEM global and cpu resets */
            addr = prmBase + RM_DSP_RSTCTRL;
            SETBITREG32(addr, 0x0);

        }
        break;

        case Processor_ResetCtrlCmd_MMU_Reset:
        {
            /* Assert MMU Reset */
            addr = prmBase + RM_DSP_RSTCTRL;
            SETBITREG32(addr, 0x1);

        }
        break;

        case Processor_ResetCtrlCmd_MMU_Release:
        {
            /* clear status bit, write-1 to clear bit */
            addr = prmBase + RM_DSP_RSTST;
            val = INREG32(addr);
            if (val != 0x0) {
                Osal_printf("VAYUDSP_halResetCtrl: clearing DSP reset status!\n");
                OUTREG32(addr, val);
                while ((val = INREG32(addr)) != 0x0);
                Osal_printf("VAYUDSP_halResetCtrl: DSP reset state reset!\n");
            }

            addr = prmBase + PM_DSP_PWRSTCTRL;
            val = INREG32(addr);
            val |= 0x7;
            OUTREG32(addr, val);
            addr = prmBase + PM_DSP_PWRSTST;
            val = INREG32(addr);
            /* Module is managed automatically by HW */
            addr = cmBase + CM_DSP_DSP_CLKCTRL;
            OUTREG32(addr, 0x01);
            /* Enable the DSP clock */
            addr = cmBase + CM_DSP_CLKSTCTRL;
            OUTREG32(addr, 0x02);

            do {
                val = INREG32(addr);
                if (val & 0x100) {
                    Osal_printf("DSP clock enabled:DSP_CLKSTCTRL = 0x%x\n", val);
                    break;
                }
            } while (--counter);
            if (counter == 0) {
                Osal_printf("FAILED TO ENABLE DSP CLOCK !\n");
                status = -1;
                break;
            }

            /* Check that releasing resets would indeed be effective */
            addr = prmBase + RM_DSP_RSTCTRL;
            val =  INREG32(addr);
            if (val != 3) {
                Osal_printf("DSP Resets in not proper state! [0x%x]\n", val);
                OUTREG32(addr, 0x3);
                counter = 1000;

                while ((--counter)&&((INREG32(addr) & 0x3) != 0x3));
                if (counter == 0) {
                    Osal_printf("RESET bits not set in DSP reset Ctrl!\n");
                    status = -1;
                    break;
                }
            }
            /* De-assert RST2, and clear the Reset status */
            OUTREG32(addr, 0x1);
            addr = prmBase + RM_DSP_RSTST;

            while (!((INREG32(addr))& 0x2));

            Osal_printf("DSP:RST2 released!\n");
            OUTREG32(addr, 0x2);

            /* enable MMU0 and MMU1 through global system register */
            val = INREG32(mmuSysBase + DSP_SYS_MMU_CONFIG_OFFSET);
            OUTREG32(mmuSysBase + DSP_SYS_MMU_CONFIG_OFFSET, (val & ~0x11) | 0x11);
            Osal_printf("DSP:SYS_MMU_CONFIG MMU0 and MMU1 enabled!\n");
        }
        break;

        case Processor_ResetCtrlCmd_Release:
        {
            addr = prmBase + PM_DSP_PWRSTCTRL;
            val = INREG32(addr);
            val |= 0x7;
            OUTREG32(addr, val);
            addr = prmBase + PM_DSP_PWRSTST;
            val = INREG32(addr);
            /* Module is managed automatically by HW */
            addr = cmBase + CM_DSP_DSP_CLKCTRL;
            OUTREG32(addr, 0x01);
            /* Enable the DSP clock */
            addr = cmBase + CM_DSP_CLKSTCTRL;
            OUTREG32(addr, 0x02);

            /*De-assert RST2 and clear the Reset Status */
            addr = prmBase + RM_DSP_RSTCTRL;
            Osal_printf("De-assert DSP RST1\n");
            OUTREG32(addr, 0x0);
            Osal_printf("DSP:RST1 released!\n");
            addr = prmBase + RM_DSP_RSTST;
            OUTREG32(addr, 0x1);
        }
        break;

        default:
        {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason(curTrace, GT_4CLASS,
                "VAYUDSP_halResetCtrl", status,
                "Unsupported reset ctrl cmd specified");
        }
        break;
    }

    GT_1trace(curTrace, GT_LEAVE, "VAYUDSP_halResetCtrl", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif
