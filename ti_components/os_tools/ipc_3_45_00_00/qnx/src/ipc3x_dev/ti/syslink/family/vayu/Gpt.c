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

/* Standard headers */
#include <ti/syslink/Std.h>

/* QNX specific header include */
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>

#include <hw/inout.h>
#include <sys/mman.h>

#include <OsalIsr.h>
#include <ti/syslink/ProcMgr.h>
#include <ti/syslink/utils/Trace.h>
#include <MultiProc.h>
#include <_MultiProc.h>
#include <Gpt.h>


/* Start a software forced wake-up */
#define SW_WKUP                           0x2

/* Start a software forced wake-up */
#define HW_AUTO                           0x3

/* Explicitly enable a module */
#define MOD_ENABLE                        0x2

/* Disable a module */
#define MOD_DISABLE                       0xFFFFFFFC

/*
 * Empirically determined delay that is necessary between when the clock domain
 * is enabled and when the status bit is updated
 */
#define DELAY                             100

/* Module idle status mask */
#define IDLEST_MASK                       0x30000

/* Module mode mask */
#define MODULEMODE_MASK                   0x3

/* Masks for timer registers */
#define GPT_TWPS_W_PEND_TCLR              0x1
#define GPT_TCLR_STOP_MASK                0xfffffffe

/* Registers for clock management of timers in IPU power domain */
#define CM_CORE_AON__IPU_SIZE             0x100
#define CM_CORE_AON__IPU_BASE             0x4A005500
#define CM_IPU_CLKSTCTRL_OFFSET           0x40
#define CM_IPU_TIMER5_CLKCTRL_OFFSET      0x58
#define CM_IPU_TIMER6_CLKCTRL_OFFSET      0x60
#define CM_IPU_TIMER7_CLKCTRL_OFFSET      0x68
#define CM_IPU_TIMER8_CLKCTRL_OFFSET      0x70

/* Size of timer register sets */
#define TIMER_REG_SIZE 0x1000

/* Timer physical base addresses */
static uint32_t gptPhyBase[GPT_TIMER_NUM] = {
    0x4AE18000,  /* GPT_TIMER_1  */
    0x48032000,  /* GPT_TIMER_2  */
    0x48034000,  /* GPT_TIMER_3  */
    0x48036000,  /* GPT_TIMER_4  */
    0x48820000,  /* GPT_TIMER_5  */
    0x48822000,  /* GPT_TIMER_6  */
    0x48824000,  /* GPT_TIMER_7  */
    0x48826000,  /* GPT_TIMER_8  */
    0x4803E000,  /* GPT_TIMER_9  */
    0x48086000,  /* GPT_TIMER_10 */
    0x48088000,  /* GPT_TIMER_11 */
};

/*
 * Interrupts for GPTimers used as watchdog
 * They correspond to MPU_IRQ numbers + 32
 * This works for Timers 1-11
 */
#define VAYU_IRQ_GPT(x)  (37 + (x) + 32)

/* GPTimer registers */
typedef struct Gpt_Regs {
    uint32_t tidr;
    uint32_t space[3];
    uint32_t tiocp_cfg;
    uint32_t space1[3];
    uint32_t eoi;
    uint32_t irqstatus_raw;
    uint32_t irqstatus;
    uint32_t irqenable_set;
    uint32_t irqenable_clr;
    uint32_t irqwakeen;
    uint32_t tclr;
    uint32_t tcrr;
    uint32_t tldr;
    uint32_t ttgr;
    uint32_t twps;
    uint32_t tmar;
    uint32_t tcar1;
    uint32_t tsicr;
    uint32_t tcar2;
    uint32_t tpir;
    uint32_t tnir;
    uint32_t tcvr;
    uint32_t tocr;
    uint32_t towr;
} Gpt_Regs;

/*
 * Defines the state object, which contains all the module
 * specific information.
 */
struct Gpt_module_object {
    uintptr_t cmCoreAonBaseVa;
    /* base address to CM_CORE_AON__IPU */
    bool isSetup;
    /* Indicates whether the module is setup. */
    bool isAttached[MultiProc_MAXPROCESSORS];
    /* Indicates whether the module is attached. */
    OsalIsr_Handle gptIsrObjects[GPT_TIMER_NUM];
    /* ISR handle for Watchdog timers */
    void *         gptBaseAddr[GPT_TIMER_NUM];
    /* Virtual base addresses of GPTimer registers */
    ProcMgr_Handle proc_handles[MultiProc_MAXPROCESSORS];
    /* Array of processor handles */
    char **  wdtOwnerProcessor;
    /* Define the processor which owns a given gptimer as watchdog timer */
};

static struct Gpt_module_object gptState = {
    .cmCoreAonBaseVa = NULL,
    .isSetup = false
};

/* Enable a particular timer by setting its module mode */
static int enable(uintptr_t reg)
{
    int max_tries = DELAY;

    out32(reg, MOD_ENABLE);
    do {
        if (!(in32(reg) & IDLEST_MASK)) {
            break;
        }
    } while (--max_tries);

    if (max_tries == 0) {
        return -EIO;
    }
    else {
        return EOK;
    }
}

/* Disable a particular timer by setting its module mode */
static int disable(uintptr_t reg)
{
    uint32_t value = 0;

    /*Check if Clock is Enabled*/
    value = in32(reg);
    if ((value & MODULEMODE_MASK) == MOD_ENABLE) {
        /*Disable the Timer*/
        value &= MOD_DISABLE;
        out32(reg, value);
    }

    return EOK;
}

/* Enable GP timers (only the ones in PD_IPU for now) */
static int Gpt_enable()
{
    /* make sure abe clock domain is enabled as it is source for gpt5-8 */
    out32((uintptr_t)(gptState.cmCoreAonBaseVa + CM_IPU_CLKSTCTRL_OFFSET),
        SW_WKUP);

    /* Set module mode for each timer */
    if (enable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER5_CLKCTRL_OFFSET)
        != EOK) {
        return -EIO;
    }

    if (enable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER6_CLKCTRL_OFFSET)
        != EOK) {
        return -EIO;
    }

    if (enable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER7_CLKCTRL_OFFSET)
        != EOK) {
        return -EIO;
    }

    if (enable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER8_CLKCTRL_OFFSET)
        != EOK) {
        return -EIO;
    }

    return EOK;
}

/* Disable GP timers (only the ones in PD_IPU for now) */
static int Gpt_disable()
{
    disable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER5_CLKCTRL_OFFSET);
    disable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER6_CLKCTRL_OFFSET);
    disable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER7_CLKCTRL_OFFSET);
    disable(gptState.cmCoreAonBaseVa + CM_IPU_TIMER8_CLKCTRL_OFFSET);

    /* put abe clock domain back to HW_AUTO mode */
    out32((uintptr_t)(gptState.cmCoreAonBaseVa + CM_IPU_CLKSTCTRL_OFFSET),
        HW_AUTO);

    return EOK;
}

/* Setup module */
int Gpt_setup(Gpt_Config * cfg)
{
    int i;
    int retval = EOK;

    if (cfg == NULL) {
        return -EINVAL;
    }

    if (gptState.isSetup == false) {
        gptState.isSetup = true;

        gptState.wdtOwnerProcessor = cfg->wdtOwnerProcessor;

        memset(gptState.gptIsrObjects, 0, sizeof(gptState.gptIsrObjects));
        memset(gptState.proc_handles, 0, sizeof(gptState.proc_handles));

        gptState.cmCoreAonBaseVa = (uintptr_t)mmap_device_io(
            CM_CORE_AON__IPU_SIZE, CM_CORE_AON__IPU_BASE);
        if((uintptr_t)gptState.cmCoreAonBaseVa == MAP_DEVICE_FAILED) {
            gptState.cmCoreAonBaseVa = NULL;
            retval = -errno;
            goto exit;
        }

        Gpt_enable();

        /* Map registers for watchdog timers */
        for (i = 0; i < GPT_TIMER_NUM; i++) {
            if (gptState.wdtOwnerProcessor[i] != NULL) {
                gptState.gptBaseAddr[i] = (void *)mmap_device_io(
                    TIMER_REG_SIZE, gptPhyBase[i]);
                if ((uintptr_t)gptState.gptBaseAddr[i] ==
                    MAP_DEVICE_FAILED) {
                    retval = -ENOMEM;
                    gptState.gptBaseAddr[i] = NULL;
                    goto exit;
                }
            }
            else {
                gptState.gptBaseAddr[i] = NULL;
            }
        }
    }

exit:
    if (retval != EOK) {
        Gpt_destroy();
    }
    return retval;
}

/* Finalize module */
int Gpt_destroy()
{
    int i;

    if (gptState.isSetup) {
        /* Unmap registers for watchdog timers */
        for (i = 0; i < GPT_TIMER_NUM; i++) {
            if (gptState.gptBaseAddr[i] != NULL) {
                munmap((void *)gptState.gptBaseAddr[i], TIMER_REG_SIZE);
                gptState.gptBaseAddr[i] = NULL;
            }
        }

        Gpt_disable();

        if (gptState.cmCoreAonBaseVa) {
            munmap((void *)gptState.cmCoreAonBaseVa, CM_CORE_AON__IPU_SIZE);
            gptState.cmCoreAonBaseVa = NULL;
        }

        gptState.isSetup = false;
    }
    return EOK;
}

/* Watchdog interrupt handler */
static Bool Gpt_interrupt(Ptr fxnArgs)
{
    Gpt_Nums       timer = (Gpt_Nums)fxnArgs;
    int            num = timer + 1;   /* GP timer number */
    ProcMgr_Handle procHandle;

    /* Trigger recovery by setting the ProcMgr state */
    if (gptState.wdtOwnerProcessor[timer] != NULL) {
        procHandle = gptState.proc_handles[MultiProc_getId(
            gptState.wdtOwnerProcessor[timer])];
        if (procHandle != NULL) {
            ProcMgr_setState(procHandle, ProcMgr_State_Watchdog);
        }

    }

    GT_1trace(curTrace, GT_4CLASS,
          "Gpt_interrupt: GPTimer %d expired!", num);

    return 0;
}

/* Interrupt clear function*/
static Bool Gpt_clr_interrupt(Ptr fxnArgs)
{
    uintptr_t reg;
    Gpt_Nums timer = (Gpt_Nums)fxnArgs;
    Gpt_Regs *gptRegs = NULL;

    gptRegs = gptState.gptBaseAddr[timer];

    if (gptRegs == NULL) {
        return TRUE;
    }

    reg = in32((uintptr_t)&gptRegs->irqstatus);
    reg |= 0x2;

    /*Clear Overflow event */
    out32((uintptr_t)&gptRegs->irqstatus, reg);
    reg = in32((uintptr_t)&gptRegs->irqstatus);

    /*Always return TRUE for ISR*/
    return TRUE;
}

/* Stop watchdog timer */
static void Gpt_wdt_stop(int num)
{
    uintptr_t reg;
    Gpt_Regs *gptRegs = NULL;

    gptRegs = gptState.gptBaseAddr[num];

    if (gptRegs == NULL) {
        return;
    }

    reg = in32((uintptr_t)&gptRegs->tclr);
    reg &= GPT_TCLR_STOP_MASK;

    /* Clear Overflow event */
    out32((uintptr_t)&gptRegs->tclr, reg);

    reg = in32((uintptr_t)&gptRegs->twps);
    while (reg & GPT_TWPS_W_PEND_TCLR) {
        reg = in32((uintptr_t)&gptRegs->twps);
    }

    /* Clear status bits */
    reg = in32((uintptr_t)&gptRegs->irqstatus);
    if (reg) {
        out32((uintptr_t)&gptRegs->irqstatus, reg);
    }
}

/* Wire the Watchdog interrupts to trigger recovery */
int Gpt_wdt_attach(int proc_id)
{
    int retval = EOK;
    int i;
    OsalIsr_Params isrParams;

    if (proc_id > MultiProc_MAXPROCESSORS) {
        return -EINVAL;
    }

    /* Only do the setup once per processor */
    if (gptState.isAttached[proc_id]) {
        return EOK;
    }

    gptState.isAttached[proc_id] = true;

    for (i = 0; i < GPT_TIMER_NUM; i++) {
        if ((gptState.wdtOwnerProcessor[i] != NULL) &&
            (strcmp(gptState.wdtOwnerProcessor[i], MultiProc_getName(proc_id))
            == 0)) {
            isrParams.checkAndClearFxn = Gpt_clr_interrupt;
            isrParams.fxnArgs = (Ptr)i;
            isrParams.intId = VAYU_IRQ_GPT(i);
            isrParams.sharedInt = FALSE;
            gptState.gptIsrObjects[i] =
                OsalIsr_create(&Gpt_interrupt,
                           isrParams.fxnArgs, &isrParams);
            if (gptState.gptIsrObjects[i] != NULL) {
                if (OsalIsr_install(gptState.gptIsrObjects[i]) < 0) {
                    retval = -ENOMEM;
                }
            }
            else {
                retval = -ENOMEM;
            }

            if (retval >= 0) {
                if (gptState.proc_handles[proc_id] == NULL) {
                    retval = ProcMgr_open(&gptState.proc_handles[proc_id], proc_id);
                    if (retval < 0) {
                        Gpt_wdt_detach(proc_id);
                        retval = -EPERM;
                        break;
                    }
                }
            }
            else {
                if (gptState.gptIsrObjects[i]) {
                    OsalIsr_delete(&gptState.gptIsrObjects[i]);
                    gptState.gptIsrObjects[i] = NULL;
                }
                break;
            }
        }
    }

    return retval;
}

/* Un-hook the Watchdog interrupt handler */
int Gpt_wdt_detach(int proc_id)
{
    int i;

    if (proc_id > MultiProc_MAXPROCESSORS) {
        return -EINVAL;
    }

    if (gptState.isAttached[proc_id]) {
        for (i = 0; i < GPT_TIMER_NUM; i++) {
            if ((gptState.wdtOwnerProcessor[i] != NULL) &&
                (strcmp(gptState.wdtOwnerProcessor[i],
                MultiProc_getName(proc_id))) == 0) {
                /*
                 * Stop the watchdog timers. We rely on the slave processors to
                 * start them, but on unload the host should stop them to avoid
                 * getting watchdog interrupts upon reload.
                 */
                Gpt_wdt_stop(i);

                if (gptState.gptIsrObjects[i]) {
                    OsalIsr_uninstall(gptState.gptIsrObjects[i]);
                    OsalIsr_delete(&gptState.gptIsrObjects[i]);
                    gptState.gptIsrObjects[i] = NULL;
                }
                if (gptState.proc_handles[proc_id]) {
                    ProcMgr_close(&gptState.proc_handles[proc_id]);
                    gptState.proc_handles[proc_id] = NULL;
                }
            }
        }

        gptState.isAttached[proc_id] = false;
    }

    return EOK;
}
