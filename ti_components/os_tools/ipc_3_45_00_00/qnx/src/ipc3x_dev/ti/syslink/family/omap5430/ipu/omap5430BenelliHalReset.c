/*
 * Copyright (c) 2010-2015, Texas Instruments Incorporated
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
 *  @file   omap5430BenelliHalReset.c
 *
 *  @brief      Reset control module.
 *
 *              This module is responsible for handling reset-related hardware-
 *              specific operations.
 *              The implementation is specific to OMAP5430BENELLI.
 *
 */

/*QNX specific header include */
#include <errno.h>

/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <ti/syslink/utils/Trace.h>
#include <Bitops.h>

/* Module level headers */
#include <_ProcDefs.h>
#include <Processor.h>
#include <OsalDrv.h>

/* Hardware Abstraction Layer headers */
#include <OMAP5430BenelliHal.h>
#include <OMAP5430BenelliHalReset.h>
#include "OMAP5430BenelliEnabler.h"
#include <hw/inout.h>
#include <_ipu_pm.h>
#include <ipu_pm.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
#define GPT_IRQSTATUS_OFFSET 0x28

/* =============================================================================
 * APIs called by OMAP5430BENELLIPROC module
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
OMAP5430BENELLI_halResetCtrl (Ptr halObj, Processor_ResetCtrlCmd cmd)
{
    Int                  status    = PROCESSOR_SUCCESS;
    OMAP5430BENELLI_HalObject * halObject = NULL;
    UINT32 pa;
    int counter = 10;
    UINT32 IPURstCtrl;
    UINT32 IPUClkCtrl;
    UINT32 IPURstSt;
    UINT32 IPUClkStCtrl;
    UINT32 DSPRstCtrl;
    UINT32 DSPClkCtrl;
    UINT32 DSPPwrStCtrl;
    UINT32 DSPPwrSt;
    UINT32 DSPRstSt;
    UINT32 DSPClkStCtrl;
    Int ret;

    GT_2trace (curTrace, GT_ENTER, "OMAP5430BENELLI_halResetCtrl", halObj, cmd);

    GT_assert (curTrace, (halObj != NULL));
    GT_assert (curTrace, (cmd < Processor_ResetCtrlCmd_EndValue));

    ULONG reg = 0;
    ULONG resets = 0;
    pa = RM_IPU_RSTCTRL;
    IPURstCtrl = (UINT32)OsalDrv_ioMap(pa, sizeof(ULONG));

    pa = CM_IPU_IPU_CLKCTRL;
    IPUClkCtrl = (UINT32)OsalDrv_ioMap(pa, sizeof(ULONG));

    pa = RM_IPU_RSTST;
    IPURstSt = (UINT32)OsalDrv_ioMap(pa, sizeof(ULONG));
    pa = CM_IPU_CLKSTCTRL;
    IPUClkStCtrl = (UINT32)OsalDrv_ioMap(pa, sizeof(ULONG));

    pa = PM_DSP_PWRSTCTRL;
    DSPPwrStCtrl = (UINT32)OsalDrv_ioMap(pa,sizeof(ULONG));

    pa = PM_DSP_PWRSTST;
    DSPPwrSt = (UINT32)OsalDrv_ioMap(pa,sizeof(ULONG));

    pa = RM_DSP_RSTCTRL;
    DSPRstCtrl = (UINT32)OsalDrv_ioMap(pa,sizeof(ULONG));

    pa = RM_DSP_RSTST;
    DSPRstSt = (UINT32)OsalDrv_ioMap(pa,sizeof(ULONG));

    pa = CM_DSP_DSP_CLKCTRL;
    DSPClkCtrl = (UINT32)OsalDrv_ioMap(pa,sizeof(ULONG));

    pa = CM_DSP_CLKSTCTRL;
    DSPClkStCtrl = (UINT32)OsalDrv_ioMap(pa,sizeof(ULONG));

    halObject = (OMAP5430BENELLI_HalObject *) halObj ;

    switch (cmd) {
        case Processor_ResetCtrlCmd_Reset:
        {
            switch (halObject->procId) {
                case PROCTYPE_IPU0:
#ifdef IPC_SYSBIOS_SMP
                    /* Put IPU core 1 into reset */
                    SETBITREG32(IPURstCtrl, RM_IPU_RST2_BIT);
#endif
                    /* Put IPU core 0 into reset */
                    SETBITREG32(IPURstCtrl, RM_IPU_RST1_BIT);
                    /* Read back the reset control register */
                    reg = INREG32(IPURstCtrl);

                    /* Disable the GPT3 clock, which is used by CORE0 */
                    ret = ipu_pm_gpt_stop(GPTIMER_3);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430DUCATI_halResetCtrl",
                                             status,
                                             "Failed to stop gpt 3");
                    }
                    ret = ipu_pm_gpt_disable(GPTIMER_3);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430DUCATI_halResetCtrl",
                                             status,
                                             "Failed to disable gpt 3");
                    }
                    break;
#ifndef IPC_SYSBIOS_SMP
                case PROCTYPE_IPU1:
                    /* Put IPU core 1 into reset */
                    SETBITREG32(IPURstCtrl, RM_IPU_RST2_BIT);

                    /* Disable the GPT4 clock, which is used by CORE1 */
                    ret = ipu_pm_gpt_stop(GPTIMER_4);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430DUCATI_halResetCtrl",
                                             status,
                                             "Failed to stop gpt 4");
                    }
                    ret = ipu_pm_gpt_disable(GPTIMER_4);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430DUCATI_halResetCtrl",
                                             status,
                                             "Failed to disable gpt 4");
                    }
                    break;
#endif
                case PROCTYPE_DSP:
                    SETBITREG32(DSPRstCtrl, RM_DSP_RSTCTRL_BIT);
                    ret = ipu_pm_gpt_stop(GPTIMER_5);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430DUCATI_halResetCtrl",
                                             status,
                                             "Failed to stop gpt 5");
                    }
                    ret = ipu_pm_gpt_disable(GPTIMER_5);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430DUCATI_halResetCtrl",
                                             status,
                                             "Failed to disable gpt 5");
                    }
                    break;
                default:
                    break;
            }
        }
        break;

        case Processor_ResetCtrlCmd_MMU_Reset:
        {
            switch (halObject->procId) {
                case PROCTYPE_IPU0:
                    /* Put IPU MMU into reset */
                    SETBITREG32(IPURstCtrl, RM_IPU_RST3_BIT);
                    /* Disable the IPU clock */
                    OUTREG32(IPUClkCtrl, 0x01);
                    break;
#ifndef IPC_SYSBIOS_SMP
                case PROCTYPE_IPU1:
                    break;
#endif
                case PROCTYPE_DSP:
                    SETBITREG32(DSPRstCtrl, RM_DSP_MMU_RSTCTRL_BIT);
                    break;
                default:
                    break;
            }
        }
        break;

        case Processor_ResetCtrlCmd_MMU_Release:
        {
            if(halObject->procId != PROCTYPE_DSP) {
                reg = INREG32(IPURstSt);
                if (reg != 0x0) {
                    Osal_printf("OMAP5430BENELLI_halResetCtrl: clearing reset status!");
                    OUTREG32(IPURstSt, reg);
                    do {
                        if ((reg = INREG32(IPURstSt)) == 0x0)
                        break;
                    } while (--counter);

                    if (reg == 0x0) {
                        Osal_printf("OMAP5430BENELLI_halResetCtrl: reset state reset!");
                    }
                    else {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430BENELLI_halResetCtrl", status,
                                             "Failed to clear reset status");
                    }
                }
            }
            if (status >= 0) {

                switch (halObject->procId) {
                    case PROCTYPE_IPU0:
                        /* Module is managed automatically by HW */
                        OUTREG32(IPUClkCtrl,
                                  CM_IPU_IPU_CLKCTRL_MODULEMODE_HWAUTO);
                        /* Enable the IPU clock */
                        OUTREG32(IPUClkStCtrl, CM_IPU_CLKSTCTRL_CTRL_SW_WKUP);

                        counter = 10;
                        do {
                            if (TESTBITREG32(IPUClkStCtrl,
                                             CM_IPU_CLKSTCTRL_CLKACTIVITY_BIT)) {
                                Osal_printf("IPU clock enabled:"
                                            "CORE_CM_IPU_CLKSTCTRL = 0x%x",
                                            INREG32(IPUClkStCtrl));
                                break;
                            }
                        } while (--counter);

                        if (counter == 0) {
                            Osal_printf("FAILED TO ENABLE IPU CLOCK !");
                            return PROCESSOR_E_OSFAILURE;
                        }

                        /* Check that releasing resets would indeed be
                         * effective */
                        reg =  INREG32(IPURstCtrl);
                        resets = RM_IPU_RST3 | RM_IPU_RST2 | RM_IPU_RST1;
                        if (reg != resets) {
                            Osal_printf("OMAP5430BENELLI_halResetCtrl: "
                                        "Resets in not proper state! [0x%x]",
                                        reg);
                            OUTREG32(IPURstCtrl,resets);
                            counter = 10;
                            do {
                                if ((INREG32(IPURstCtrl) & resets) == resets)
                                    break;
                            } while (--counter);

                            if (counter == 0) {
                                status = PROCESSOR_E_FAIL;
                                GT_setFailureReason (curTrace, GT_4CLASS,
                                        "OMAP5430BENELLI_halResetCtrl",
                                        status,
                                        "Failed to put resets in proper state");
                            }
                        }

                        if (status >= 0) {
                            /* De-assert RST3, and clear the Reset status */
                            Osal_printf("De-assert RST3");
                            CLRBITREG32(IPURstCtrl, RM_IPU_RST3_BIT);

                            counter = 10;
                            do {
                                if (INREG32(IPURstSt) & RM_IPU_RST3ST)
                                    break;
                            } while (--counter);
                            if (counter == 0) {
                                status = PROCESSOR_E_FAIL;
                                GT_setFailureReason (curTrace, GT_4CLASS,
                                                  "OMAP5430BENELLI_halResetCtrl",
                                                  status,
                                                  "Failed to release RST3");
                            }
                            else {
                                Osal_printf("RST3 released!");
                                SETBITREG32(IPURstSt, RM_IPU_RST3ST_BIT);
                            }
                        }
                        break;
#ifndef IPC_SYSBIOS_SMP
                    case PROCTYPE_IPU1:
                        break;
#endif
                    case PROCTYPE_DSP:
                         /* Enable the GPT5 clock, which is used by DSP */
                        ret = ipu_pm_gpt_enable(GPTIMER_5);
                        if (ret != EOK) {
                            status = PROCESSOR_E_FAIL;
                            GT_setFailureReason (curTrace, GT_4CLASS,
                                                 "OMAP5430BENELLI_halResetCtrl",
                                                 status,
                                                 "Failed to enable gpt 5");
                        }
                        else {
                            restore_gpt_context(GPTIMER_5);
                            ipu_pm_gpt_start(GPTIMER_5);
                            reg = INREG32(DSPRstSt);
                            if (reg != 0x0) {
                                Osal_printf("OMAP5430BENELLI_halResetCtrl: clearing DSP reset status!");
                                OUTREG32(DSPRstSt, reg);
                                counter = 10;
                                do {
                                    if (INREG32(DSPRstSt) == 0x0)
                                        break;
                                } while (--counter);
                                if (counter == 0) {
                                    status = PROCESSOR_E_FAIL;
                                    GT_setFailureReason (curTrace, GT_4CLASS,
                                                      "OMAP5430BENELLI_halResetCtrl",
                                                      status,
                                                      "Failed to release RST3");
                                }
                                else {
                                    Osal_printf("OMAP5430BENELLI_halResetCtrl: DSP reset state reset!");
                                }
                            }
                        }

                        if (status >= 0) {
                            reg = INREG32(DSPPwrStCtrl);
                            reg |= 0x7;
                            OUTREG32(DSPPwrStCtrl, reg);
                            reg = INREG32(DSPPwrSt);
                            /* Module is managed automatically by HW */
                            OUTREG32(DSPClkCtrl, 0x01);
                            /* Enable the DSP clock */
                            OUTREG32(DSPClkStCtrl, 0x03);
                            counter = 10;
                            do {
                                reg = INREG32(DSPClkStCtrl);
                                if (reg & 0x100) {
                                    Osal_printf("DSP clock enabled:DSP_CLKSTCTRL = 0x%x", reg);
                                    break;
                                }
                            } while (--counter);
                            if (counter == 0) {
                                status = PROCESSOR_E_FAIL;
                                GT_setFailureReason (curTrace, GT_4CLASS,
                                                     "OMAP5430BENELLI_halResetCtrl",
                                                     status,
                                                     "FAILED TO ENABLE DSP CLOCK");
                            }
                        }

                        if (status >= 0) {
                            /* Check that releasing resets would indeed be effective */
                            reg =  INREG32(DSPRstCtrl);
                            if (reg != 3) {
                                Osal_printf("proc5430_start: DSP Resets in not proper state! [0x%x]", reg);
                                OUTREG32(DSPRstCtrl,0x3);
                                counter = 1000;
                                while ((--counter)&&((INREG32(DSPRstCtrl) & 0x3) != 0x3));
                                if (counter == 0) {
                                    status = PROCESSOR_E_FAIL;
                                    GT_setFailureReason (curTrace, GT_4CLASS,
                                                         "OMAP5430BENELLI_halResetCtrl",
                                                         status,
                                                         "RESET bits not set in DSP reset Ctrl");
                                }
                            }
                            if (status >= 0) {
                                /* De-assert RST3, and clear the Reset status */
                                OUTREG32(DSPRstCtrl,0x1);
                                counter = 10;
                                do {
                                    if (INREG32(DSPRstSt) & 0x2)
                                        break;
                                } while (--counter);
                                if (counter == 0) {
                                    status = PROCESSOR_E_FAIL;
                                    GT_setFailureReason (curTrace, GT_4CLASS,
                                                         "OMAP5430BENELLI_halResetCtrl",
                                                         status,
                                                         "Failed to deassert reset 3");
                                }
                                else {
                                    /* De-assert RST3, and clear the Reset status */
                                    OUTREG32(DSPRstCtrl,0x1);
                                    counter = 10;
                                    do {
                                        if (INREG32(DSPRstSt) & 0x2)
                                            break;
                                    } while (--counter);
                                    if (counter == 0) {
                                        status = PROCESSOR_E_FAIL;
                                        GT_setFailureReason (curTrace, GT_4CLASS,
                                                             "OMAP5430BENELLI_halResetCtrl",
                                                             status,
                                                             "Failed to deassert reset 3");
                                    }
                                    else {
                                        Osal_printf("DSP:RST2 released!");
                                        OUTREG32(DSPRstSt,0x2);
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        Osal_printf("proc5430_start: ERROR input");
                        break;
                }
            }
        }
        break;

        case Processor_ResetCtrlCmd_Release:
        {
            switch (halObject->procId) {
                case PROCTYPE_IPU0:
                    /* Enable the GPT3 clock, which is used by CORE0 */
                    ret = ipu_pm_gpt_enable(GPTIMER_3);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430BENELLI_halResetCtrl",
                                             status,
                                             "Failed to enable gpt 3");
                    }
                    else {
                        restore_gpt_context(GPTIMER_3);
                        ret = ipu_pm_gpt_start(GPTIMER_3);
                        if (ret != EOK) {
                            status = PROCESSOR_E_FAIL;
                            GT_setFailureReason (curTrace, GT_4CLASS,
                                                 "OMAP5430BENELLI_halResetCtrl",
                                                 status,
                                                 "Failed to start gpt 3");
                        }
                        else {
                            /* De-assert RST1, and clear the Reset status */
                            Osal_printf("De-assert RST1");
                            CLRBITREG32(IPURstCtrl, RM_IPU_RST1_BIT);

                            counter = 10;
                            do {
                                if (INREG32(IPURstSt) & RM_IPU_RST1)
                                    break;
                            } while (--counter);
                            if (counter == 0) {
                                status = PROCESSOR_E_FAIL;
                                GT_setFailureReason (curTrace, GT_4CLASS,
                                                  "OMAP5430BENNELI_halResetCtrl",
                                                  status,
                                                  "Failed to release RST1");
                            }
                            else {
                                Osal_printf("RST1 released!");
                                SETBITREG32(IPURstSt, RM_IPU_RST1ST_BIT);

                                /* Setting to HW_AUTO Mode */
                                reg = INREG32(IPUClkStCtrl);
                                reg &= ~CM_IPU_CLKSTCTRL_CTRL_BITMASK;
                                reg |= CM_IPU_CLKSTCTRL_CTRL_HW_AUTO;
                                OUTREG32(IPUClkStCtrl, reg);
#ifdef IPC_SYSBIOS_SMP
                                /* De-assert RST2, and clear the Reset status */
                                CLRBITREG32(IPURstCtrl, RM_IPU_RST2_BIT);

                                counter = 10;
                                do {
                                    if (INREG32(IPURstSt) & RM_IPU_RST2)
                                        break;
                                } while (--counter);
                                if (counter == 0) {
                                    status = PROCESSOR_E_FAIL;
                                    GT_setFailureReason (curTrace, GT_4CLASS,
                                                         "OMAP5430BENELLI_halResetCtrl",
                                                         status,
                                                         "Failed to release RST2");
                                }
                                else {
                                    Osal_printf("RST2 released!");
                                    SETBITREG32(IPURstSt, RM_IPU_RST2ST_BIT);
                                }
#endif // ifdef IPC_SYSBIOS_SMP
                            }
                        }
                    }
                    break;
#ifndef IPC_SYSBIOS_SMP
                case PROCTYPE_IPU1:
                    /* Enable the GPT4 clock, which is used by CORE1 */
                    ret = ipu_pm_gpt_enable(GPTIMER_4);
                    if (ret != EOK) {
                        status = PROCESSOR_E_FAIL;
                        GT_setFailureReason (curTrace, GT_4CLASS,
                                             "OMAP5430BENELLI_halResetCtrl",
                                             status,
                                             "Failed to enable gpt 4");
                    }
                    else {
                        restore_gpt_context(GPTIMER_4);
                        ipu_pm_gpt_start(GPTIMER_4);

                        /* De-assert RST2, and clear the Reset status */
                        CLRBITREG32(IPURstCtrl, RM_IPU_RST2_BIT);

                        counter = 10;
                        do {
                            if (INREG32(IPURstSt) & RM_IPU_RST2)
                                break;
                        } while (--counter);
                        if (counter == 0) {
                            status = PROCESSOR_E_FAIL;
                            GT_setFailureReason (curTrace, GT_4CLASS,
                                                 "OMAP5430BENELLI_halResetCtrl",
                                                 status,
                                                 "Failed to release RST2");
                        }
                        else {
                            Osal_printf("RST2 released!");
                            SETBITREG32(IPURstSt, RM_IPU_RST2ST_BIT);

                            /* Wait until benelli is in idle */
                            //while(TESTBITREG32(IPUClkStCtrl,
                            //               CM_IPU_CLKSTCTRL_CLKACTIVITY_BIT));
                        }
                    }
                    break;
#endif
                case PROCTYPE_DSP:
                    /*De-assert RST2 and clear the Reset Status */
                    Osal_printf("De-assert DSP RST1");
                    OUTREG32(DSPRstCtrl, 0x0);
                    Osal_printf("DSP:RST2 released!");
                    OUTREG32(DSPRstSt,0x1);
                    break;
                default:
                    Osal_printf("OMAP5430BENELLI_halResetCtrl: ERROR input");
                    break;
            }
        }
        break;

        default:
        {
            /*! @retval PROCESSOR_E_INVALIDARG Invalid argument */
            status = PROCESSOR_E_INVALIDARG;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "OMAP5430BENELLI_halResetCtrl",
                                 status,
                                 "Unsupported reset ctrl cmd specified");
        }
        break;
    }
    OsalDrv_ioUnmap(IPUClkStCtrl, sizeof(ULONG));
    OsalDrv_ioUnmap(IPUClkCtrl, sizeof(ULONG));
    OsalDrv_ioUnmap(IPURstCtrl, sizeof(ULONG));
    OsalDrv_ioUnmap(IPURstSt, sizeof(ULONG));
    OsalDrv_ioUnmap(DSPClkStCtrl, sizeof(ULONG));
    OsalDrv_ioUnmap(DSPClkCtrl, sizeof(ULONG));
    OsalDrv_ioUnmap(DSPRstCtrl, sizeof(ULONG));
    OsalDrv_ioUnmap(DSPRstSt, sizeof(ULONG));
    OsalDrv_ioUnmap(DSPPwrSt, sizeof(ULONG));
    OsalDrv_ioUnmap(DSPPwrStCtrl, sizeof(ULONG));
    GT_1trace (curTrace, GT_LEAVE, "OMAP5430BENELLI_halResetCtrl", status);

    /*! @retval PROCESSOR_SUCCESS Operation successful */

    return status;
}


#if defined (__cplusplus)
}
#endif
