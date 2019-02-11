/*
 *  @file   VAYUIpuCore0HalReset.c
 *
 *  @brief      Reset control module.
 *
 *              This module is responsible for handling reset-related hardware-
 *              specific operations.
 *              The implementation is specific to VAYUIPUCORE0.
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
#include <VAYUIpuHal.h>
#include <VAYUIpuCore0HalReset.h>

#include <hw/inout.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/* M4 PRCM Regs*/
#define RM_IPU_RSTCTRL_OFFSET        0x210
#define RM_IPU_RSTST_OFFSET          0x214

#define CM_IPU_CLKSTCTRL_OFFSET      0x200
#define CM_IPU_IPU_CLKCTRL_OFFSET    0x220

/*
 * empirically determined delay that is necessary between when the IPU
 * clock is enabled and when the status bit is set
 */
#define DELAY                        100

/*
 * IPU1 functional clock selection
 * 0: DPLL_ABE_X2_CLK
 * 1: CORE_IPU_ISS_BOOST_CLK
 */
#define USE_CORE_IPU_ISS_BOOST_CLK   1

#if USE_CORE_IPU_ISS_BOOST_CLK
#define IPU1_CLKSEL                  0x1000000
#else
#define IPU1_CLKSEL                  0x0
#endif

/* =============================================================================
 * APIs called by VAYUIPUCORE0PROC module
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
VAYUIPUCORE0_halResetCtrl (Ptr halObj, Processor_ResetCtrlCmd cmd)
{
    Int                 status    = PROCESSOR_SUCCESS;
    VAYUIPU_HalObject * halObject = NULL;
    UInt32              cmBase;
    UInt32              prmBase;
    UInt32              reg       = 0;
    UInt32              counter   = DELAY;

    GT_2trace (curTrace, GT_ENTER, "VAYUIPUCORE0_halResetCtrl", halObj, cmd);

    GT_assert (curTrace, (halObj != NULL));
    GT_assert (curTrace, (cmd < Processor_ResetCtrlCmd_EndValue));

    halObject = (VAYUIPU_HalObject *) halObj ;
    cmBase = halObject->cmBase;
    prmBase = halObject->prmBase;

    switch (cmd) {
        case Processor_ResetCtrlCmd_Reset:
        {
            /*Put Benelli M4_0 and M4_1 to Reset*/
            /* Put IPU core 0 and core 1 into reset */
            SETBITREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 1);
            SETBITREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 0);
            /* Read back the reset control register */
            reg = INREG32(prmBase + RM_IPU_RSTCTRL_OFFSET);
        }
        break;

        case Processor_ResetCtrlCmd_MMU_Reset:
        {
            /* Put IPU MMU into reset */
            SETBITREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 0x2);
            /* Disable the IPU clock */
            OUTREG32(cmBase + CM_IPU_IPU_CLKCTRL_OFFSET, 0x01);
        }
        break;

        case Processor_ResetCtrlCmd_MMU_Release:
        {
            reg = INREG32(prmBase + RM_IPU_RSTST_OFFSET);
            if (reg != 0x0) {
                Osal_printf("VAYUIPUCORE0_halResetCtrl: clearing reset status!\n");
                OUTREG32(prmBase + RM_IPU_RSTST_OFFSET, reg);
                while ((reg = INREG32(prmBase + RM_IPU_RSTST_OFFSET)) != 0x0);
                Osal_printf("VAYUIPUCORE0_halResetCtrl: reset state reset!\n");
            }
            /* Module is managed automatically by HW */
            if (halObject->procId == MultiProc_getId("IPU1")) {
                /* For IPU1, select CORE_IPU_ISS_BOOST_CLK as functional clk */
                OUTREG32(cmBase + CM_IPU_IPU_CLKCTRL_OFFSET, 0x1 | IPU1_CLKSEL);
            }
            else {
                OUTREG32(cmBase + CM_IPU_IPU_CLKCTRL_OFFSET, 0x1);
            }
            /* Enable the IPU clock */
            OUTREG32(cmBase + CM_IPU_CLKSTCTRL_OFFSET, 0x2);

            do {
                if (TESTBITREG32(cmBase + CM_IPU_CLKSTCTRL_OFFSET,
                                 8)) {
                    Osal_printf("IPU clock enabled:"
                                "CORE_CM_IPU_CLKSTCTRL = 0x%x\n",
                                INREG32(cmBase + CM_IPU_CLKSTCTRL_OFFSET));
                    break;
                }
            } while (--counter);

            if (counter == 0) {
                Osal_printf("FAILED TO ENABLE IPU CLOCK !\n");
                return PROCESSOR_E_OSFAILURE;
            }

            /* Check that releasing resets would indeed be effective */
            reg =  INREG32(prmBase + RM_IPU_RSTCTRL_OFFSET);
            if (reg != 0x7) {
                Osal_printf("VAYUIPUCORE0_halResetCtrl: "
                            "Resets in not proper state! [0x%x]\n",
                            reg);
                OUTREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 0x7);
                while ((INREG32(prmBase + RM_IPU_RSTCTRL_OFFSET) & 0x7) != 0x7);
            }

            /* De-assert RST3, and clear the Reset status */
            Osal_printf("De-assert RST3\n");
            CLRBITREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 2);

            while (!(INREG32(prmBase + RM_IPU_RSTST_OFFSET) & 0x4));
            Osal_printf("RST3 released!\n");
            SETBITREG32(prmBase + RM_IPU_RSTST_OFFSET, 2);
        }
        break;

        case Processor_ResetCtrlCmd_Release:
        {
            /*Bring Benelli M4_0 and M4_1 out of Reset*/
            /* De-assert RST1 and RST2, and clear the Reset status */
            Osal_printf("De-assert RST1\n");
            CLRBITREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 0);
            Osal_printf("De-assert RST2\n");
            CLRBITREG32(prmBase + RM_IPU_RSTCTRL_OFFSET, 1);

            while (!(INREG32(prmBase + RM_IPU_RSTST_OFFSET) & 0x3));
            Osal_printf("RST1 & RST2 released!");
            SETBITREG32(prmBase + RM_IPU_RSTST_OFFSET, 0);
            SETBITREG32(prmBase + RM_IPU_RSTST_OFFSET, 1);

            /* Setting to HW_AUTO Mode */
            reg = INREG32(cmBase + CM_IPU_CLKSTCTRL_OFFSET);
            reg &= ~0x3;
            reg |= 0x3;
            OUTREG32(cmBase + CM_IPU_CLKSTCTRL_OFFSET, reg);
        }
        break;

        case Processor_ResetCtrlCmd_PeripheralUp:
        {
            /* Nothing to be done to bringup the peripherals for this device. */
        }
        break;

        default:
        {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "VAYUIPUCORE0_halResetCtrl",
                                 status,
                                 "Unsupported reset ctrl cmd specified");
        }
        break ;
    }

    GT_1trace (curTrace, GT_LEAVE, "VAYUIPUCORE0_halResetCtrl",status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif
