/*
 *  Copyright (c) 2011-2015, Texas Instruments Incorporated
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

/* Standard headers */
#include <ti/syslink/Std.h>

/*QNX specific header include */
#include <errno.h>
#include <unistd.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/netmgr.h>
#include <sys/rsrcdbmgr.h>
#include <sys/rsrcdbmsg.h>
#undef QNX_PM_ENABLE
#ifdef QNX_PM_ENABLE
#include <sys/powman.h>
#include <cpu_dll_msg.h>
#endif

/* Module headers */
#include <ipu_pm.h>
#include <_ipu_pm.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <time.h>
#include <sys/siginfo.h>
#include <stdbool.h>
#include <ti/ipc/MultiProc.h>
#include <ti/syslink/ProcMgr.h>
#include <OMAP5430BenelliProc.h>
#include <ArchIpcInt.h>
#include <_Omap5430IpcInt.h>

#include <OMAP5430BenelliHalReset.h>

//#include <camera/camdrv.h>
#include <Bitops.h>
#include <_rpmsg.h>

#ifndef IPC_SYSBIOS_SMP
#define CORE0    "CORE0"
#else
#define CORE0    "IPU"
#endif

/* Defines the ipu_pm state object, which contains all the module
 * specific information. */
struct ipu_pm_module_object {
    atomic_t ref_count;
    /* Reference count */
    ipu_pm_config cfg;
    /* Module configuration */
    pthread_mutex_t mtx;
    /* Handle of gate to be used for local thread safety */
    int ivahd_use_cnt;
    /* Count of ivahd users */
    int ivaseq0_use_cnt;
    /* Count of ivaseq0 users */
    int ivaseq1_use_cnt;
    /* Count of ivaseq1 users */
    ProcMgr_Handle proc_handles[MultiProc_MAXPROCESSORS];
    /* Array of processor handles */
    uint32_t loaded_procs;
    /* Info on which procs are loaded */
    uint32_t proc_state;
    /* Current state of the remote procs */
    timer_t hibernation_timer;
    /* Timer used for hibernation */
    int hib_timer_state;
    /* State of the hibernation timer */
    OsalIsr_Handle gpt9IsrObject;
    /* ISR handle for gpt9 WDT */
    OsalIsr_Handle gpt11IsrObject;
    /* ISR handle for gpt11 WDT */
    OsalIsr_Handle gpt6IsrObject;
    /* ISR handle for gpt6 WDT */
    bool attached[MultiProc_MAXPROCESSORS];
    /* Indicates whether the ipu_pm module is attached. */
    bool is_setup;
    /* Indicates whether the ipu_pm module is setup. */
};

static struct ipu_pm_module_object ipu_pm_state = {
    .ivahd_use_cnt = 0,
    .loaded_procs = 0,
    .proc_state = 0,
} ;

extern Bool ipc_hib_enable;
extern uint32_t ipc_hib_timeout;
extern Bool ipc_hib_hibernating;
extern pthread_mutex_t ipc_hib_mutex;
extern pthread_cond_t ipc_hib_cond;

#undef BENELLI_SELF_HIBERNATION

/* A9 state flag 0000 | 0000 Benelli internal use*/
#define CORE0_PROC_DOWN        0x00010000
#define CORE1_PROC_DOWN        0x00020000

#define CORE0_LOADED 0x1
#define CORE1_LOADED 0x2
#define DSP_LOADED   0x4

#ifdef BENELLI_SELF_HIBERNATION
/* A9-M3 mbox status */
#define A9_M3_MBOX 0x4A0F4000
#define MBOX_MESSAGE_STATUS 0x000000CC

/* Flag provided by BIOS */
#define IDLE_FLAG_BENELLI_ADDR_MAP_BASE 0x9F0F0000
#define IDLE_FLAG_PHY_ADDR_OFFSET   0x2D8

/* BIOS flags states for each core in IPU */
static void *core0Idle = NULL;
static void *core1Idle = NULL;
static void *a9_m3_mbox = NULL;
static void *m3_clkstctrl = NULL;

#define NUM_IDLE_CORES ((in32((uintptr_t)core1Idle) << 1) + \
                        (in32((uintptr_t)core0Idle)))
#define PENDING_MBOX_MSG in32((uintptr_t)a9_m3_mbox + MBOX_MESSAGE_STATUS)

extern Bool rpmsg_resmgr_allow_hib (UInt16 proc_id);
#endif

#ifdef QNX_PM_ENABLE
static struct powauth *ipc_auth_active = NULL;
static struct powauth *ipc_auth_oswr = NULL;

enum {core_active, core_inactive, core_off};
static int ipu_pm_powman_init(void);
static void tell_powman_auth_oswr(int need);
static BOOL oswr_prevent = FALSE;

#endif

typedef struct GPTIMER_REGS {
    uint32_t tidr;
    uint32_t space[3];
    uint32_t tiocp_cfg;
    uint32_t space1[3];
    uint32_t reserved;
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
} GPTIMER_REGS;

#define OMAP54XX_IRQ_GPT6 74
#define OMAP54XX_IRQ_GPT9 77
#define OMAP54XX_IRQ_GPT11 79

#define GPTIMER3_BASE        0x48034000
#define GPTIMER4_BASE        0x48036000
#define GPTIMER9_BASE        0x4803E000
#define GPTIMER11_BASE       0x48088000
#define GPTIMER5_BASE        0x40138000
#define GPTIMER6_BASE        0x4013A000

static void *GPT3Base = 0;
static void *GPT3ClkCtrl =0;
static bool GPT3Saved = FALSE;
static bool GPT3InUse = FALSE;
static void *GPT4Base = 0;
static void *GPT4ClkCtrl =0;
static bool GPT4Saved = FALSE;
static bool GPT4InUse = FALSE;
static void *GPT5Base = 0;
static void *GPT5ClkCtrl =0;
static bool GPT5Saved = FALSE;
static bool GPT5InUse = FALSE;
static void *GPT6Base = 0;
static void *GPT6ClkCtrl =0;
static bool GPT6Saved = FALSE;
static bool GPT6InUse = FALSE;
static void *GPT9Base = 0;
static void *GPT9ClkCtrl =0;
static bool GPT9Saved = FALSE;
static bool GPT9InUse = FALSE;
static void *GPT11Base = 0;
static void *GPT11ClkCtrl =0;
static bool GPT11Saved = FALSE;
static bool GPT11InUse = FALSE;

static GPTIMER_REGS GPT3Reg_saved;
static GPTIMER_REGS GPT4Reg_saved;
static GPTIMER_REGS GPT5Reg_saved;
static GPTIMER_REGS GPT6Reg_saved;
static GPTIMER_REGS GPT9Reg_saved;
static GPTIMER_REGS GPT11Reg_saved;

static void *prm_base_va = NULL;
static void *cm2_base_va = NULL;
static void *cm_core_aon_base_va = NULL;

#define MAX_DUCATI_CHANNELS   4
#define DUCATI_CHANNEL_START 25
#define DUCATI_CHANNEL_END   28
static bool DMAAllocation = false;
#ifdef QNX_PM_ENABLE
static rsrc_request_t sdma_req;
#endif

// Note, the number of camera modes is tied to enum campower_mode_t, which can
// be found in camera/camdrv.h
#define NUM_CAM_MODES 3
static unsigned last_camera_req[NUM_CAM_MODES];
static unsigned last_led_req = 0;

enum processor_version {
    OMAP_5430_es10 = 0,
    OMAP_5430_es20,
    ERROR_CONTROL_ID = -1,
    INVALID_SI_VERSION = -2
};

#define PRM_SIZE                    0x2000
#define PRM_BASE                    0x4AE06000
#define PRM_CM_SYS_CLKSEL_OFFSET    0x110
//IVA_PRM registers for OMAP5 ES1.0
#define PM_IVA_PWRSTCTRL_OFFSET     0xF00
#define PM_IVA_PWRSTST_OFFSET       0xF04
#define RM_IVA_RSTCTRL_OFFSET       0xF10
#define RM_IVA_IVA_CONTEXT_OFFSET   0xF24
//IVA_PRM registers for OMAP5 ES2.0
#define PM_IVA_PWRSTCTRL_ES20_OFFSET     0x1200
#define PM_IVA_PWRSTST_ES20_OFFSET       0x1204
#define RM_IVA_RSTCTRL_ES20_OFFSET       0x1210
#define RM_IVA_IVA_CONTEXT_ES20_OFFSET   0x1224

#define CM2_SIZE                        0x2000
#define CM2_BASE                        0x4A008000
#define CM_L3_2_L3_2_CLKCTRL_OFFSET     0x820
#define CM_MPU_M3_CLKCTRL_OFFSET        0x900

//IVA_CM_CORE registers for OMAP5 ES1.0
#define CM_IVA_CLKSTCTRL_OFFSET       0xF00
#define CM_IVA_IVA_CLKCTRL_OFFSET   0xF20
#define CM_IVA_SL2_CLKCTRL_OFFSET     0xF28
//IVA_CM_CORE registers for OMAP5 ES2.0
#define CM_IVA_CLKSTCTRL_ES20_OFFSET       0x1200
#define CM_IVA_IVA_CLKCTRL_ES20_OFFSET     0x1220
#define CM_IVA_SL2_CLKCTRL_ES20_OFFSET     0x1228

// CM_L4PER GPTIMER offsets for OMAP5 ES1.0
#define CM_L4PER_GPTIMER3_CLKCTRL_ES1_0_OFFSET  0x1440
#define CM_L4PER_GPTIMER4_CLKCTRL_ES1_0_OFFSET  0x1448
#define CM_L4PER_GPTIMER9_CLKCTRL_ES1_0_OFFSET  0x1450
#define CM_L4PER_GPTIMER11_CLKCTRL_ES1_0_OFFSET 0x1430

// CM_L4PER GPTIMER offsets for OMAP5 ES2.0
#define CM_L4PER_TIMER3_CLKCTRL_ES2_0_OFFSET  0x1040
#define CM_L4PER_TIMER4_CLKCTRL_ES2_0_OFFSET  0x1048
#define CM_L4PER_TIMER9_CLKCTRL_ES2_0_OFFSET  0x1050
#define CM_L4PER_TIMER11_CLKCTRL_ES2_0_OFFSET 0x1030

#define CM_CORE_AON_SIZE                  0x1000
#define CM_CORE_AON_BASE                  0x4A004000
#define CM_ABE_CLKSTCTRL_OFFSET           0x500
#define CM_ABE_TIMER5_CLKCTRL_OFFSET      0x568
#define CM_ABE_TIMER6_CLKCTRL_OFFSET      0x570

#define IVAHD_FREQ_MAX_IN_HZ 532000000

#define ID_CODE_BASE   0x4A002000
#define ID_CODE_OFFSET 0x204

#define OMAP5430_ES10    0x0B942
#define OMAP5432_ES10    0x0B998
#define OMAP5430_ES20    0x1B942
#define OMAP5432_ES20    0x1B998

#ifdef QNX_PM_ENABLE
static dvfsMsg_t dvfsMessage;
static int cpudll_coid = -1;
static reply_getListOfDomainOPPs_t cpudll_iva_opp = { {0} };  /* for result of getDomainOPP (IVA)*/
static reply_getListOfDomainOPPs_t cpudll_core_opp = { {0} };  /* for result of getDomainOPP (CORE)*/
#endif

enum {
    RPRM_GPTIMER    = 0,
    RPRM_IVAHD  = 1,
    RPRM_IVASEQ0    = 2,
    RPRM_IVASEQ1    = 3,
    RPRM_L3BUS  = 4,
    RPRM_ISS    = 5,
    RPRM_FDIF   = 6,
    RPRM_SL2IF  = 7,
    RPRM_AUXCLK = 8,
    RPRM_REGULATOR  = 9,
    RPRM_GPIO   = 10,
    RPRM_SDMA   = 11,
    RPRM_IPU    = 12,
    RPRM_DSP    = 13,
    RPRM_I2C    = 14,
    RPRM_CAMERA = 15,
    RPRM_LED    = 16,
    RPRM_MAX
};

enum processor_version get_omap_version (void)
{
    uintptr_t id_code_base = NULL;
    enum processor_version omap_rev;
    uint32_t reg;

    id_code_base = mmap_device_io(0x1000, ID_CODE_BASE);
    if (id_code_base == MAP_DEVICE_FAILED){
        GT_setFailureReason (curTrace, GT_4CLASS, "get_omap_version",
                             ERROR_CONTROL_ID,
                             "Unable to map ID_CODE register");
        return ERROR_CONTROL_ID;
    }

    reg = in32(id_code_base + ID_CODE_OFFSET);
    reg &= 0xFFFFF000;
    reg = reg >> 12;

    switch (reg) {
        case OMAP5430_ES10:
        case OMAP5432_ES10:
            omap_rev = OMAP_5430_es10;
            break;

        case OMAP5430_ES20:
        case OMAP5432_ES20:
            omap_rev = OMAP_5430_es20;
            break;

        default:
            omap_rev = INVALID_SI_VERSION;
            break;
    }

    if (id_code_base)
        munmap_device_io(id_code_base, 0x1000);

    return omap_rev;
}

/* Function to Map the required registers for
* GPT configuration
*/
int map_gpt_regs(void)
{
    int retval = 0;
    enum processor_version omap_rev;
    uint32_t cm_l4per_gpt3_offset;
    uint32_t cm_l4per_gpt4_offset;
    uint32_t cm_l4per_gpt9_offset;
    uint32_t cm_l4per_gpt11_offset;

    omap_rev = get_omap_version();
    if (omap_rev < 0) {
        GT_setFailureReason (curTrace, GT_4CLASS, "map_gpt_regs",
                             omap_rev, "Error while reading the OMAP REVISION");
        return -EIO;
    }

    if (omap_rev == OMAP_5430_es20) {
        cm_l4per_gpt3_offset = CM_L4PER_TIMER3_CLKCTRL_ES2_0_OFFSET;
        cm_l4per_gpt4_offset = CM_L4PER_TIMER4_CLKCTRL_ES2_0_OFFSET;
        cm_l4per_gpt9_offset = CM_L4PER_TIMER9_CLKCTRL_ES2_0_OFFSET;
        cm_l4per_gpt11_offset = CM_L4PER_TIMER11_CLKCTRL_ES2_0_OFFSET;
    }
    else {
        cm_l4per_gpt3_offset = CM_L4PER_GPTIMER3_CLKCTRL_ES1_0_OFFSET;
        cm_l4per_gpt4_offset = CM_L4PER_GPTIMER4_CLKCTRL_ES1_0_OFFSET;
        cm_l4per_gpt9_offset = CM_L4PER_GPTIMER9_CLKCTRL_ES1_0_OFFSET;
        cm_l4per_gpt11_offset = CM_L4PER_GPTIMER11_CLKCTRL_ES1_0_OFFSET;
    }

    GPT3ClkCtrl = cm2_base_va + cm_l4per_gpt3_offset;

    GPT3Base = (void *)mmap_device_io(0x1000, GPTIMER3_BASE);
    if ((uintptr_t)GPT3Base == MAP_DEVICE_FAILED) {
        retval = -ENOMEM;
        GPT3Base = NULL;
        goto exit;
    }

    GPT4ClkCtrl = cm2_base_va + cm_l4per_gpt4_offset;

    GPT4Base = (void *)mmap_device_io(0x1000, GPTIMER4_BASE);
    if ((uintptr_t)GPT4Base == MAP_DEVICE_FAILED) {
        retval = -ENOMEM;
        GPT4Base = NULL;
        goto exit;
    }

    GPT9ClkCtrl = cm2_base_va + cm_l4per_gpt9_offset;

    GPT9Base = (void *)mmap_device_io(0x1000, GPTIMER9_BASE);
    if ((uintptr_t)GPT9Base == MAP_DEVICE_FAILED) {
        retval = -ENOMEM;
        GPT9Base = NULL;
        goto exit;
    }

    GPT11ClkCtrl = cm2_base_va + cm_l4per_gpt11_offset;

    GPT11Base = (void *)mmap_device_io(0x1000, GPTIMER11_BASE);
    if ((uintptr_t)GPT11Base == MAP_DEVICE_FAILED) {
        retval = -ENOMEM;
        GPT11Base = NULL;
        goto exit;
    }

    GPT5ClkCtrl = cm_core_aon_base_va + CM_ABE_TIMER5_CLKCTRL_OFFSET;

    GPT5Base = (void *)mmap_device_io(0x1000, GPTIMER5_BASE);
    if ((uintptr_t)GPT5Base == MAP_DEVICE_FAILED) {
        retval = -ENOMEM;
        GPT5Base = NULL;
        goto exit;
    }

    GPT6ClkCtrl = cm_core_aon_base_va + CM_ABE_TIMER6_CLKCTRL_OFFSET;

    GPT6Base = (void *)mmap_device_io(0x1000, GPTIMER6_BASE);
    if ((uintptr_t)GPT6Base == MAP_DEVICE_FAILED) {
        retval = -ENOMEM;
        GPT6Base = NULL;
        goto exit;
    }

    return EOK;

exit:
    GPT6ClkCtrl = NULL;
    if (GPT5Base) {
        munmap(GPT5Base, 0x1000);
        GPT5Base = NULL;
    }
    GPT5ClkCtrl = NULL;
    if (GPT11Base) {
        munmap(GPT11Base, 0x1000);
        GPT11Base = NULL;
    }
    GPT11ClkCtrl = NULL;
    if (GPT9Base) {
        munmap(GPT9Base, 0x1000);
        GPT9Base = NULL;
    }
    GPT9ClkCtrl = NULL;
    if (GPT4Base) {
        munmap(GPT4Base, 0x1000);
        GPT4Base = NULL;
    }
    GPT4ClkCtrl = NULL;
    if (GPT3Base) {
        munmap(GPT3Base, 0x1000);
        GPT3Base = NULL;
    }
    GPT3ClkCtrl = NULL;
    return retval;
}

void unmap_gpt_regs(void)
{
    if(GPT11Base != NULL)
        munmap(GPT11Base, 0x1000);

    GPT11Base = NULL;

    GPT11ClkCtrl = NULL;

    if(GPT9Base != NULL)
        munmap(GPT9Base, 0x1000);

    GPT9Base = NULL;

    GPT9ClkCtrl = NULL;

    if(GPT4Base != NULL)
        munmap(GPT4Base, 0x1000);

    GPT4Base = NULL;

    GPT4ClkCtrl = NULL;

    if(GPT3Base != NULL)
        munmap(GPT3Base, 0x1000);

    GPT3Base = NULL;

    GPT3ClkCtrl = NULL;

    if(GPT5Base != NULL)
        munmap(GPT5Base, 0x1000);

    GPT5Base = NULL;

    GPT5ClkCtrl = NULL;

    if(GPT6Base != NULL)
        munmap(GPT6Base, 0x1000);

    GPT6Base = NULL;

    GPT6ClkCtrl = NULL;
}

#ifndef IPC_DISABLE_WATCHDOG

/* Interrupt clear function*/
static Bool ipu_pm_clr_gptimer_interrupt(Ptr fxnArgs)
{
    UINT32 reg;
    uint32_t num = (uint32_t)fxnArgs;
    GPTIMER_REGS *GPTRegs = NULL;

    if (num == GPTIMER_3) {
        GPTRegs = GPT3Base;
    }
    else if (num == GPTIMER_4) {
        GPTRegs = GPT4Base;
    }
    else if (num == GPTIMER_9) {
        GPTRegs = GPT9Base;
    }
    else if (num == GPTIMER_11) {
        GPTRegs = GPT11Base;
    }
    else if (num == GPTIMER_5) {
        GPTRegs = GPT5Base;
    }
    else if (num == GPTIMER_6) {
        GPTRegs = GPT6Base;
    }
    else {
        return TRUE;
    }

    reg = in32((uintptr_t)&GPTRegs->irqstatus);
    reg |= 0x2;

    /*Clear Overflow event */
    out32((uintptr_t)&GPTRegs->irqstatus, reg);
    reg = in32((uintptr_t)&GPTRegs->irqstatus);

    /*Always return TRUE for ISR*/
    return TRUE;
}

/* ISR for GP Timer*/
static Bool ipu_pm_gptimer_interrupt(Ptr fxnArgs)
{
    int num;
    uint16_t core0_id = MultiProc_getId(CORE0);
#ifndef IPC_SYSBIOS_SMP
    uint16_t core1_id = MultiProc_getId("CORE1");
#else
    uint16_t core1_id = core0_id;
#endif
    uint16_t dsp_id = MultiProc_getId("DSP");

    switch ((uint32_t)fxnArgs) {
        case GPTIMER_9:
            num = 9;
            ProcMgr_setState(ipu_pm_state.proc_handles[core0_id],
                             ProcMgr_State_Watchdog);
            break;
        case GPTIMER_11:
            num = 11;
            ProcMgr_setState(ipu_pm_state.proc_handles[core1_id],
                             ProcMgr_State_Watchdog);
            break;
        case GPTIMER_6:
            num = 6;
            ProcMgr_setState(ipu_pm_state.proc_handles[dsp_id],
                             ProcMgr_State_Watchdog);
            break;
        default:
            num = 0;
            break;
    }
    // what to do here?
    GT_1trace(curTrace, GT_4CLASS,
              "ipu_pm_gptimer_interrupt: GPTimer %d expired!", num);

    return 0;
}
#endif

int ipu_pm_gpt_enable(int num)
{
    GPTIMER_REGS * GPTRegs = NULL;
    uintptr_t GPTClkCtrl = NULL;
    int max_tries = 100;

    if (num == GPTIMER_3) {
        GPTClkCtrl = (uintptr_t)GPT3ClkCtrl;
        GPTRegs = GPT3Base;
        GPT3InUse = TRUE;
    }
    else if (num == GPTIMER_4) {
        GPTClkCtrl = (uintptr_t)GPT4ClkCtrl;
        GPTRegs = GPT4Base;
        GPT4InUse = TRUE;
    }
    else if (num == GPTIMER_9) {
        GPTClkCtrl = (uintptr_t)GPT9ClkCtrl;
        GPTRegs = GPT9Base;
        GPT9InUse = TRUE;
    }
    else if (num == GPTIMER_11) {
        GPTClkCtrl = (uintptr_t)GPT11ClkCtrl;
        GPTRegs = GPT11Base;
        GPT11InUse = TRUE;
    }
    else if (num == GPTIMER_5) {
        GPTClkCtrl = (uintptr_t)GPT5ClkCtrl;
        GPTRegs = GPT5Base;
        GPT5InUse = TRUE;
        // make sure abe clock is enabled as it is source for gpt5
        out32((uintptr_t)(cm_core_aon_base_va + CM_ABE_CLKSTCTRL_OFFSET), 0x2);
    }
    else if (num == GPTIMER_6) {
        GPTClkCtrl = (uintptr_t)GPT6ClkCtrl;
        GPTRegs = GPT6Base;
        GPT6InUse = TRUE;
        // make sure abe clock is enabled as it is source for gpt6
        out32((uintptr_t)(cm_core_aon_base_va + CM_ABE_CLKSTCTRL_OFFSET), 0x2);
    }
    else {
        return -EINVAL;
    }

    /* Enable GPT MODULEMODE and set CLKSEL to SYS_CLK*/
    out32(GPTClkCtrl, 0x2);
    do {
        if (!(in32(GPTClkCtrl) & 0x30000))
            break;
    } while (--max_tries);
    if (max_tries == 0) {
        ipu_pm_gpt_disable(num);
        return -EIO;
    }

    /* Set Smart-idle wake-up-capable */
    out32((uintptr_t)&GPTRegs->tiocp_cfg, 0xC);

    return EOK;
}

int ipu_pm_gpt_disable(int num)
{
    uintptr_t GPTClkCtrl = NULL;
    GPTIMER_REGS *GPTRegs = NULL;
    UINT32 reg = 0;

    if (num == GPTIMER_3) {
        GPTClkCtrl = (uintptr_t)GPT3ClkCtrl;
        GPTRegs = GPT3Base;
        GPT3InUse = FALSE;
    }
    else if (num == GPTIMER_4) {
        GPTClkCtrl = (uintptr_t)GPT4ClkCtrl;
        GPTRegs = GPT4Base;
        GPT4InUse = FALSE;
    }
    else if (num == GPTIMER_9) {
        GPTClkCtrl = (uintptr_t)GPT9ClkCtrl;
        GPTRegs = GPT9Base;
        GPT9InUse = FALSE;
    }
    else if (num == GPTIMER_11) {
        GPTClkCtrl = (uintptr_t)GPT11ClkCtrl;
        GPTRegs = GPT11Base;
        GPT11InUse = FALSE;
    }
    else if (num == GPTIMER_5) {
        GPTClkCtrl = (uintptr_t)GPT5ClkCtrl;
        GPTRegs = GPT5Base;
        GPT5InUse = FALSE;
    }
    else if (num == GPTIMER_6) {
        GPTClkCtrl = (uintptr_t)GPT6ClkCtrl;
        GPTRegs = GPT6Base;
        GPT6InUse = FALSE;
    }
    else {
        return -EINVAL;
    }

    /*Check if Clock is Enabled*/
    reg = in32(GPTClkCtrl);
    if ((reg & 0x3) == 0x2) {
        /* Clear any pending interrupt to allow idle */
        reg = in32((uintptr_t)&GPTRegs->irqstatus);
        if (reg) {
            out32((uintptr_t)&GPTRegs->irqstatus, reg);
        }

        /*Disable the Timer*/
        reg = in32(GPTClkCtrl);
        reg &= 0xFFFFFFFC;
        out32(GPTClkCtrl, reg);
    }
    else {
        GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_gpt_disable", -EINVAL,
                            "gpt clock is not enabled!");
        return -EINVAL;
    }
    return EOK;
}

int ipu_pm_gpt_start (int num)
{
    GPTIMER_REGS * GPTRegs = NULL;
    uint32_t reg = 0;

    if (num == GPTIMER_3) {
        GPTRegs = GPT3Base;
    }
    else if (num == GPTIMER_4) {
        GPTRegs = GPT4Base;
    }
    else if (num == GPTIMER_9) {
        GPTRegs = GPT9Base;
    }
    else if (num == GPTIMER_11) {
        GPTRegs = GPT11Base;
    }
    else if (num == GPTIMER_5) {
        GPTRegs = GPT5Base;
    }
    else if (num == GPTIMER_6) {
        GPTRegs = GPT6Base;
    }
    else {
        return -EINVAL;
    }

    /*Start the Timer*/
    reg = in32((uintptr_t)&GPTRegs->tclr);
    reg |=0x1;
    out32((uintptr_t)&GPTRegs->tclr, reg);

    return EOK;
}

int ipu_pm_gpt_stop(int num)
{
    uintptr_t GPTClkCtrl = NULL;
    GPTIMER_REGS * GPTRegs = NULL;
    uint32_t reg = 0;

    if (num == GPTIMER_3) {
        GPTClkCtrl = (uintptr_t)GPT3ClkCtrl;
        GPTRegs = GPT3Base;
    }
    else if (num == GPTIMER_4) {
        GPTClkCtrl = (uintptr_t)GPT4ClkCtrl;
        GPTRegs = GPT4Base;
    }
    else if (num == GPTIMER_9) {
        GPTClkCtrl = (uintptr_t)GPT9ClkCtrl;
        GPTRegs = GPT9Base;
    }
    else if (num == GPTIMER_11) {
        GPTClkCtrl = (uintptr_t)GPT11ClkCtrl;
        GPTRegs = GPT11Base;
    }
    else if (num == GPTIMER_5) {
        GPTClkCtrl = (uintptr_t)GPT5ClkCtrl;
        GPTRegs = GPT5Base;
    }
    else if (num == GPTIMER_6) {
        GPTClkCtrl = (uintptr_t)GPT6ClkCtrl;
        GPTRegs = GPT6Base;
    }
    else {
        return -EINVAL;
    }

    /*Check if Clock is Enabled*/
    reg = in32(GPTClkCtrl);
    if ((reg & 0x3) == 0x2) {

        /*Stop the Timer*/
        reg = in32((uintptr_t)&GPTRegs->tclr);
        reg &=0xFFFFFFFE;
        out32((uintptr_t)&GPTRegs->tclr, reg);
    }
    else {
        GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_gpt_stop", -EINVAL,
                            "gpt clock is not enabled!");
        return -EINVAL;
    };

    return EOK;
}

void save_gpt_context(int num)
{
    GPTIMER_REGS *GPTRegs = NULL;
    GPTIMER_REGS *GPTSaved = NULL;
    bool *GPTRestore = NULL;

    if (num == GPTIMER_3) {
        GPTRegs = GPT3Base;
        GPTSaved = &GPT3Reg_saved;
        GPTRestore = &GPT3Saved;
    }
    else if (num == GPTIMER_4) {
        GPTRegs = GPT4Base;
        GPTSaved = &GPT4Reg_saved;
        GPTRestore = &GPT4Saved;
    }
    else if (num == GPTIMER_9) {
        GPTRegs = GPT9Base;
        GPTSaved = &GPT9Reg_saved;
        GPTRestore = &GPT9Saved;
    }
    else if (num == GPTIMER_11) {
        GPTRegs = GPT11Base;
        GPTSaved = &GPT11Reg_saved;
        GPTRestore = &GPT11Saved;
    }
    else if (num == GPTIMER_5) {
        GPTRegs = GPT5Base;
        GPTSaved = &GPT5Reg_saved;
        GPTRestore = &GPT5Saved;
    }
    else if (num == GPTIMER_6) {
        GPTRegs = GPT6Base;
        GPTSaved = &GPT6Reg_saved;
        GPTRestore = &GPT6Saved;
    }
    else {
        return;
    }

    GPTSaved->tiocp_cfg = in32((uintptr_t)&GPTRegs->tiocp_cfg);
    GPTSaved->tcrr = in32((uintptr_t)&GPTRegs->tcrr);
    GPTSaved->irqenable_set = in32((uintptr_t)&GPTRegs->irqenable_set);
    GPTSaved->irqstatus_raw = in32((uintptr_t)&GPTRegs->irqstatus_raw);
    GPTSaved->irqstatus = in32((uintptr_t)&GPTRegs->irqstatus);
    GPTSaved->irqwakeen = in32((uintptr_t)&GPTRegs->irqwakeen);
    GPTSaved->tclr = in32((uintptr_t)&GPTRegs->tclr);
    GPTSaved->tldr = in32((uintptr_t)&GPTRegs->tldr);
    GPTSaved->ttgr = in32((uintptr_t)&GPTRegs->ttgr);
    GPTSaved->tmar = in32((uintptr_t)&GPTRegs->tmar);
    GPTSaved->tsicr = in32((uintptr_t)&GPTRegs->tsicr);
    *GPTRestore = TRUE;
}

void restore_gpt_context(int num)
{
    GPTIMER_REGS *GPTRegs = NULL;
    GPTIMER_REGS *GPTSaved = NULL;
    bool *GPTRestore = NULL;

    if (num == GPTIMER_3) {
        GPTRegs = GPT3Base;
        GPTSaved = &GPT3Reg_saved;
        GPTRestore = &GPT3Saved;
    }
    else if (num == GPTIMER_4) {
        GPTRegs = GPT4Base;
        GPTSaved = &GPT4Reg_saved;
        GPTRestore = &GPT4Saved;
    }
    else if (num == GPTIMER_9) {
        GPTRegs = GPT9Base;
        GPTSaved = &GPT9Reg_saved;
        GPTRestore = &GPT9Saved;
    }
    else if (num == GPTIMER_11) {
        GPTRegs = GPT11Base;
        GPTSaved = &GPT11Reg_saved;
        GPTRestore = &GPT11Saved;
    }
    else if (num == GPTIMER_5) {
        GPTRegs = GPT5Base;
        GPTSaved = &GPT5Reg_saved;
        GPTRestore = &GPT5Saved;
    }
    else if (num == GPTIMER_6) {
        GPTRegs = GPT6Base;
        GPTSaved = &GPT6Reg_saved;
        GPTRestore = &GPT6Saved;
    }
    else {
        return;
    }

    if (*GPTRestore) {
        *GPTRestore = FALSE;
        out32((uintptr_t)&GPTRegs->tiocp_cfg, GPTSaved->tiocp_cfg);
        out32((uintptr_t)&GPTRegs->irqenable_set, GPTSaved->irqenable_set);
        out32((uintptr_t)&GPTRegs->tcrr, GPTSaved->tcrr);
        out32((uintptr_t)&GPTRegs->irqstatus_raw, GPTSaved->irqstatus_raw);
        out32((uintptr_t)&GPTRegs->irqstatus, GPTSaved->irqstatus);
        out32((uintptr_t)&GPTRegs->irqwakeen, GPTSaved->irqwakeen);
        out32((uintptr_t)&GPTRegs->tclr, GPTSaved->tclr);
        out32((uintptr_t)&GPTRegs->tldr, GPTSaved->tldr);
        out32((uintptr_t)&GPTRegs->ttgr, GPTSaved->ttgr);
        out32((uintptr_t)&GPTRegs->tmar, GPTSaved->tmar);
        out32((uintptr_t)&GPTRegs->tsicr, GPTSaved->tsicr);
    }
}

int ipu_pm_ivaseq0_disable()
{
    uintptr_t pm_base = 0;
    uint32_t reg = 0;
    enum processor_version omap_rev;
    uint32_t rm_iva_rstctrl_offset;

    pthread_mutex_lock(&ipu_pm_state.mtx);

    if (ipu_pm_state.ivaseq0_use_cnt-- == 1) {
        pm_base = (uintptr_t)prm_base_va;

        omap_rev = get_omap_version();
        if (omap_rev < 0) {
            GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivaseq0_disable",
                                 omap_rev, "Error while reading the OMAP REVISION");
            return -EIO;
        }

        if (omap_rev == OMAP_5430_es20) {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
        }
        else {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
        }

        reg = in32(pm_base + rm_iva_rstctrl_offset);
        reg |= 0x1;
        out32(pm_base + rm_iva_rstctrl_offset, reg);
    }
    else {
        GT_0trace(curTrace, GT_3CLASS, "ivaseq0 still in use");
    }

    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return EOK;
}

int ipu_pm_ivaseq0_enable()
{
    uintptr_t pm_base = 0;
    uint32_t reg = 0;
    enum processor_version omap_rev;
    uint32_t rm_iva_rstctrl_offset;

    pthread_mutex_lock(&ipu_pm_state.mtx);
    if (++ipu_pm_state.ivaseq0_use_cnt == 1) {
        pm_base = (uintptr_t)prm_base_va;

        omap_rev = get_omap_version();
        if (omap_rev < 0) {
            GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivaseq0_disable",
                                 omap_rev, "Error while reading the OMAP REVISION");
            return -EIO;
        }

        if (omap_rev == OMAP_5430_es20) {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
        }
        else {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
        }

        reg = in32(pm_base + rm_iva_rstctrl_offset);
        reg &= 0xFFFFFFFE;
        out32(pm_base + rm_iva_rstctrl_offset, reg);
    }
    else {
        GT_0trace(curTrace, GT_3CLASS, "ivaseq0 still in use");
    }

    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return EOK;
}

int ipu_pm_ivaseq1_disable()
{
    uintptr_t pm_base = 0;
    uint32_t reg = 0;
    enum processor_version omap_rev;
    uint32_t rm_iva_rstctrl_offset;

    pthread_mutex_lock(&ipu_pm_state.mtx);

    if (ipu_pm_state.ivaseq1_use_cnt-- == 1) {
        pm_base = (uintptr_t)prm_base_va;

        omap_rev = get_omap_version();
        if (omap_rev < 0) {
            GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivaseq0_disable",
                                 omap_rev, "Error while reading the OMAP REVISION");
            return -EIO;
        }

        if (omap_rev == OMAP_5430_es20) {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
        }
        else {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
        }

        reg = in32(pm_base + rm_iva_rstctrl_offset);
        reg |= 0x2;
        out32(pm_base + rm_iva_rstctrl_offset, reg);
    }
    else {
        GT_0trace(curTrace, GT_3CLASS, "ivaseq1 still in use");
    }

    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return EOK;
}

int ipu_pm_ivaseq1_enable()
{
    uintptr_t pm_base = 0;
    uint32_t reg = 0;
    enum processor_version omap_rev;
    uint32_t rm_iva_rstctrl_offset;

    pthread_mutex_lock(&ipu_pm_state.mtx);
    if (++ipu_pm_state.ivaseq1_use_cnt == 1) {
        pm_base = (uintptr_t)prm_base_va;

        omap_rev = get_omap_version();
        if (omap_rev < 0) {
            GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivaseq0_disable",
                                 omap_rev, "Error while reading the OMAP REVISION");
            return -EIO;
        }

        if (omap_rev == OMAP_5430_es20) {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
        }
        else {
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
        }

        reg = in32(pm_base + rm_iva_rstctrl_offset);
        reg &= 0xFFFFFFFD;
        out32(pm_base + rm_iva_rstctrl_offset, reg);
    }
    else {
        GT_0trace(curTrace, GT_3CLASS, "ivaseq1 still in use");
    }

    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return EOK;
}

int ipu_pm_ivahd_disable()
{
    uintptr_t pm_base = 0;
    uintptr_t cm_base = 0;
    uint32_t reg = 0;
    int max_tries = 100;
    enum processor_version omap_rev;
    uint32_t pm_iva_pwrstctrl_offset;
    uint32_t cm_iva_clkstctrl_offset;
    uint32_t cm_iva_iva_clkctrl_offset;
    uint32_t cm_iva_sl2_clkctrl_offset;
    uint32_t rm_iva_rstctrl_offset;

    pthread_mutex_lock(&ipu_pm_state.mtx);

    if (ipu_pm_state.ivahd_use_cnt-- == 1) {
        omap_rev = get_omap_version();
        if (omap_rev < 0) {
            GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivahd_disable",
                                 omap_rev, "Error while reading the OMAP REVISION");
            return -EIO;
        }
        pm_base = (uintptr_t)prm_base_va;
        cm_base = (uintptr_t)cm2_base_va;

        if (omap_rev == OMAP_5430_es20) {
            pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_ES20_OFFSET;
            cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_ES20_OFFSET;
            cm_iva_iva_clkctrl_offset = CM_IVA_IVA_CLKCTRL_ES20_OFFSET;
            cm_iva_sl2_clkctrl_offset = CM_IVA_SL2_CLKCTRL_ES20_OFFSET;
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
        }
        else {
            pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_OFFSET;
            cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_OFFSET;
            cm_iva_iva_clkctrl_offset = CM_IVA_IVA_CLKCTRL_OFFSET;
            cm_iva_sl2_clkctrl_offset = CM_IVA_SL2_CLKCTRL_OFFSET;
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
        }

        reg = in32(pm_base + pm_iva_pwrstctrl_offset);
        reg &= 0xFFFFFFFC;
        reg |= 0x00000002;
        out32(pm_base + pm_iva_pwrstctrl_offset, reg);

        /* Ensure that the wake up mode is set to SW_WAKEUP */
        out32(cm_base + cm_iva_clkstctrl_offset, 0x00000002);

        /* Check the standby status */
        do {
            if (((in32(cm_base + cm_iva_iva_clkctrl_offset) & 0x00040000) != 0x0))
                break;
        } while (--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** Error in IVAHD standby status");
        }

        // IVAHD_CM2:CM_IVAHD_IVAHD_CLKCTRL
        out32(cm_base + cm_iva_iva_clkctrl_offset, 0x00000000);

        max_tries = 100;
        do {
            if((in32(cm_base + cm_iva_iva_clkctrl_offset) & 0x00030000) == 0x30000)
                break;
        } while (--max_tries);
        if (max_tries == 0) {
           GT_0trace(curTrace, GT_4CLASS," ** Error in IVAHD standby status");
        }

        // IVAHD_CM2:CM_IVAHD_SL2_CLKCTRL
        out32(cm_base + cm_iva_sl2_clkctrl_offset, 0x00000000);

        max_tries = 100;
        do {
            if((in32(cm_base + cm_iva_sl2_clkctrl_offset) & 0x00030000) == 0x30000);
                break;
        } while (--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** Error in SL2 CLKCTRL");
        }

        /* put IVA into HW Auto mode */
        out32(cm_base + cm_iva_clkstctrl_offset, 0x00000003);

        max_tries = 100;
        /* Check CLK ACTIVITY bit */

        while(((in32(cm_base + cm_iva_clkstctrl_offset) & 0x00000100) != 0x0) && --max_tries);
        if (max_tries == 0)
            GT_0trace(curTrace, GT_4CLASS, "IPC: ivahd_disable: WARNING - CLK ACTIVITY bit did not go off");

        // IVA sub-system resets - Assert reset for IVA logic and SL2
        out32(pm_base + rm_iva_rstctrl_offset, 0x00000004);
        max_tries = 200;
        while(--max_tries);

        // IVA sub-system resets - Assert reset for IVA logic, SL2, and sequencer1
        out32(pm_base + rm_iva_rstctrl_offset, 0x00000005);
        max_tries = 200;
        while(--max_tries);

        // IVA sub-system resets - Assert reset for IVA logic, SL2, sequencer1 and sequencer2
        out32(pm_base + rm_iva_rstctrl_offset, 0x00000007);
    }
    else {
        GT_0trace(curTrace, GT_3CLASS, "ivahd still in use");
    }

    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return EOK;
}

int ipu_pm_ivahd_enable()
{
    uintptr_t pm_base = 0;
    uintptr_t cm_base = 0;
    uint32_t reg = 0;
    unsigned int pwrst = 0;
    int max_tries = 100;
    enum processor_version omap_rev;
    uint32_t pm_iva_pwrstctrl_offset;
    uint32_t cm_iva_clkstctrl_offset;
    uint32_t cm_iva_iva_clkctrl_offset;
    uint32_t cm_iva_sl2_clkctrl_offset;
    uint32_t rm_iva_rstctrl_offset;
    uint32_t rm_iva_iva_context_offset;
    uint32_t pm_iva_pwrstst_offset;

    pthread_mutex_lock(&ipu_pm_state.mtx);

    if (++ipu_pm_state.ivahd_use_cnt == 1) {
        pm_base = (uintptr_t)prm_base_va;
        cm_base = (uintptr_t)cm2_base_va;

        omap_rev = get_omap_version();
        if (omap_rev < 0) {
            GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivahd_enable",
                                 omap_rev, "Error while reading the OMAP REVISION");
            return -EIO;
        }

        if (omap_rev == OMAP_5430_es20) {
            pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_ES20_OFFSET;
            cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_ES20_OFFSET;
            cm_iva_iva_clkctrl_offset = CM_IVA_IVA_CLKCTRL_ES20_OFFSET;
            cm_iva_sl2_clkctrl_offset = CM_IVA_SL2_CLKCTRL_ES20_OFFSET;
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
            rm_iva_iva_context_offset = RM_IVA_IVA_CONTEXT_ES20_OFFSET;
            pm_iva_pwrstst_offset = PM_IVA_PWRSTST_ES20_OFFSET;
        }
        else {
            pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_OFFSET;
            cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_OFFSET;
            cm_iva_iva_clkctrl_offset = CM_IVA_IVA_CLKCTRL_OFFSET;
            cm_iva_sl2_clkctrl_offset = CM_IVA_SL2_CLKCTRL_OFFSET;
            rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
            rm_iva_iva_context_offset = RM_IVA_IVA_CONTEXT_OFFSET;
            pm_iva_pwrstst_offset = PM_IVA_PWRSTST_OFFSET;
        }
        /* Read the IVAHD Context register to check if the memory content has been lost */
        reg = in32(pm_base + rm_iva_iva_context_offset);
        /* Clear the context register by writing 1 to bit 8,9 and 10 */
        out32(pm_base + rm_iva_iva_context_offset, 0x700);

        /*Display power state*/
        pwrst = in32(pm_base + pm_iva_pwrstst_offset);
        GT_1trace(curTrace, GT_4CLASS, "###: off state reg bit = 0x%x\n", (pwrst & 0x03000003));
        /*Clear the power status reg by writting 1'a into the requred bits*/
        out32(pm_base + pm_iva_pwrstst_offset, 0x03000000);

        /* Ensure power state is set to ON */
        reg = in32(pm_base + pm_iva_pwrstctrl_offset);
        reg &= 0xFFFFFFFC;
        reg |= 0x00000003;
        out32(pm_base + pm_iva_pwrstctrl_offset, reg);

        /* Ensure that the wake up mode is set to SW_WAKEUP */
        out32(cm_base + cm_iva_clkstctrl_offset, 0x00000002);

        max_tries = 100;
        while(((in32(pm_base + pm_iva_pwrstst_offset) & 0x00100000) != 0) && --max_tries);
        if (max_tries == 0)
            GT_0trace(curTrace, GT_4CLASS, "IPC: ivahd_enable: WARNING - PwrSt did not transition");

        // IVAHD_CM2:CM_IVAHD_IVAHD_CLKCTRL
        out32(cm_base + cm_iva_iva_clkctrl_offset, 0x00000001);

        // IVAHD_CM2:CM_IVAHD_SL2_CLKCTRL
        out32(cm_base + cm_iva_sl2_clkctrl_offset, 0x00000001);

        /* Wait until the CLK_ACTIVITY bit is set */
        max_tries = 100;
        while (((in32(cm_base + cm_iva_clkstctrl_offset) & 0x00000100) == 0x0) && --max_tries);
        if (max_tries == 0)
            GT_0trace(curTrace, GT_4CLASS, "IPC: ivahd_enable: WARNING - Clk_ACTIVITY bit is not set");

        /* Release ICONT1 and SL2/IVAHD first, wait for few usec  then release ICONT2 */
        reg = in32(pm_base + rm_iva_rstctrl_offset);
        reg &= 0xFFFFFFFB;
        out32(pm_base + rm_iva_rstctrl_offset, reg);

        max_tries = 100;
        usleep(100);
        do {
            if((in32(cm_base + cm_iva_iva_clkctrl_offset) & 0x00030000) == 0x0)
                break;
        } while(--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** Error in IVAHD clk control");
            return -EIO;
        }

        max_tries = 100;
        do {
            if((in32(cm_base + cm_iva_sl2_clkctrl_offset) & 0x00030000) == 0x00000)
                break;
        } while(--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** Error in SL2 clk control");
            return -EIO;
        }

        max_tries = 100;
        do {
            if((in32(cm_base + CM_L3_2_L3_2_CLKCTRL_OFFSET) & 0x30001) == 0x00001)
                break;
        } while(--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** Error in L3 clk control");
            return -EIO;
        }

        /* Ensure IVAHD and SL2 is functional */
        max_tries = 100;
        do {
        if((in32(cm_base + cm_iva_iva_clkctrl_offset) & 0x00030001) == 0x00001)
            break;
        } while(--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** IVAHD is not functional");
            return -EIO;
        }

        max_tries = 100;
        do {
            if((in32(cm_base + cm_iva_sl2_clkctrl_offset) & 0x00030001) == 0x00001)
                break;
        } while(--max_tries);
        if (max_tries == 0) {
            GT_0trace(curTrace, GT_4CLASS," ** SL2 is not functional");
            return -EIO;
        }
    } else {
        GT_0trace(curTrace, GT_3CLASS, "ivahd already acquired");
    }

    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return EOK;
}

int ipu_pm_ivahd_off()
{
    uintptr_t pm_base = 0;
    uintptr_t cm_base = 0;
    uint32_t reg = 0;
    int32_t max_tries = 0;
    bool ivahd_enabled = false;
    bool sl2_enabled = false;
    enum processor_version omap_rev;
    uint32_t pm_iva_pwrstctrl_offset;
    uint32_t cm_iva_clkstctrl_offset;
    uint32_t cm_iva_iva_clkctrl_offset;
    uint32_t cm_iva_sl2_clkctrl_offset;
    uint32_t rm_iva_rstctrl_offset;
    uint32_t pm_iva_pwrstst_offset;

    pm_base = (uintptr_t)prm_base_va;
    cm_base = (uintptr_t)cm2_base_va;

    omap_rev = get_omap_version();
    if (omap_rev < 0) {
        GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivahd_enable",
                             omap_rev, "Error while reading the OMAP REVISION");
        return -EIO;
    }

    if (omap_rev == OMAP_5430_es20) {
        pm_iva_pwrstst_offset = PM_IVA_PWRSTST_ES20_OFFSET;
        cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_ES20_OFFSET;
        cm_iva_iva_clkctrl_offset = CM_IVA_IVA_CLKCTRL_ES20_OFFSET;
        cm_iva_sl2_clkctrl_offset = CM_IVA_SL2_CLKCTRL_ES20_OFFSET;
        pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_ES20_OFFSET;
        rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_ES20_OFFSET;
    }
    else {
        pm_iva_pwrstst_offset = PM_IVA_PWRSTST_OFFSET;
        cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_OFFSET;
        cm_iva_iva_clkctrl_offset = CM_IVA_IVA_CLKCTRL_OFFSET;
        cm_iva_sl2_clkctrl_offset = CM_IVA_SL2_CLKCTRL_OFFSET;
        pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_OFFSET;
        rm_iva_rstctrl_offset = RM_IVA_RSTCTRL_OFFSET;
    }

    reg = in32(pm_base + pm_iva_pwrstst_offset);
    reg = reg & 0x00000007;

    if (reg != 0x00000000) {
        /* set IVAHD to SW_WKUP */
        out32(cm_base + cm_iva_clkstctrl_offset, 0x2);
        max_tries = 100;
        /* Check for ivahd module and disable if it is enabled */
        if ((in32(cm_base + cm_iva_iva_clkctrl_offset) & 0x1) != 0) {
            out32(cm_base + cm_iva_iva_clkctrl_offset, 0x0);
            ivahd_enabled = 1;
        }
        /* Check for sl2 module and disable if it is enabled */
        if ((in32(cm_base + cm_iva_sl2_clkctrl_offset) & 0x1) != 0) {
            out32(cm_base + cm_iva_sl2_clkctrl_offset, 0x0);
            sl2_enabled = 1;
        }
        if (ivahd_enabled || sl2_enabled) {
            while (((in32(cm_base + cm_iva_clkstctrl_offset) & 0x00000100) == 0x0) && --max_tries);
            if (max_tries == 0) {
                GT_0trace(curTrace, GT_4CLASS,"IPU_PM:IVAHD DOMAIN is Not Enabled after retries");
            }
        }

        /* Set IVAHD PD to OFF */
        reg = in32(pm_base + pm_iva_pwrstctrl_offset);
        reg = (reg & 0xFFFFFFFC) | 0x0;
        out32(pm_base + pm_iva_pwrstctrl_offset, reg);

        max_tries = 100;
        while (((in32(pm_base + pm_iva_pwrstst_offset) & 0x00100000) != 0) && --max_tries);
        if (max_tries == 0) {
           GT_0trace(curTrace, GT_4CLASS,"IPU_PM: IVAHD Power Domain is in transition after retries");
        }

        if (ivahd_enabled) {
            max_tries = 100;
            while (((in32(cm_base + cm_iva_iva_clkctrl_offset) & 0x00030000) != 0x30000) && --max_tries);
            if (max_tries == 0) {
                GT_0trace(curTrace, GT_4CLASS,"IPU_PM: Stuck up in the IVAHD Module after retries");
            }
        }
        if (sl2_enabled) {
            max_tries = 100;
            while (((in32(cm_base + cm_iva_sl2_clkctrl_offset) & 0x00030000) != 0x30000) && --max_tries);
            if (max_tries == 0) {
                GT_0trace(curTrace, GT_4CLASS,"IPU_PM: Stuck up in the SL2 Module after retries");
            }
        }
        /* Set IVAHD to HW_AUTO */
        out32(cm_base + cm_iva_clkstctrl_offset, 0x3);
        /* Check the reset states and assert resets */
        if (in32(pm_base + rm_iva_rstctrl_offset) != 0x7) {
            out32(pm_base + rm_iva_rstctrl_offset, 0x7);
        }
    }

    return EOK;
}

int ipu_pm_ivahd_on()
{
    uintptr_t pm_base = 0;
    uintptr_t cm_base = 0;
    uint32_t reg = 0;
    enum processor_version omap_rev;
    uint32_t pm_iva_pwrstctrl_offset;
    uint32_t cm_iva_clkstctrl_offset;

    pm_base = (uintptr_t)prm_base_va;
    cm_base = (uintptr_t)cm2_base_va;

    omap_rev = get_omap_version();
    if (omap_rev < 0) {
        GT_setFailureReason (curTrace, GT_4CLASS, "ipu_pm_ivahd_enable",
                             omap_rev, "Error while reading the OMAP REVISION");
        return -EIO;
    }

    if (omap_rev == OMAP_5430_es20) {
        pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_ES20_OFFSET;
        cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_ES20_OFFSET;
    }
    else {
        pm_iva_pwrstctrl_offset = PM_IVA_PWRSTCTRL_OFFSET;
        cm_iva_clkstctrl_offset = CM_IVA_CLKSTCTRL_OFFSET;
    }

    /* Set the power state to ON */
    reg = in32(pm_base + pm_iva_pwrstctrl_offset);
    reg &= 0xFFFFFFFC;
    reg |= 0x00000002;
    out32(pm_base + pm_iva_pwrstctrl_offset, reg);

    /* Ensure that the wake up mode is set to SW_WAKEUP */
    out32(cm_base + cm_iva_clkstctrl_offset, 0x00000002);

    /* put IVA into HW Auto mode */
    reg = in32(cm_base + cm_iva_clkstctrl_offset);
    reg |= 0x00000003;
    out32(cm_base + cm_iva_clkstctrl_offset, reg);

    return EOK;
}

int ipu_pm_led_enable(unsigned int mode, unsigned int intensity)
{
    int ret = 0;

    //ret = camflash_config(mode, intensity);

    if (ret != -1)
        last_led_req = mode;

    return ret;
}

int ipu_pm_alloc_sdma(int num_chs, int* channels)
{
    GT_0trace(curTrace, GT_3CLASS, "ipu_pm_alloc_sdma++");

    if(DMAAllocation == false) {
        GT_0trace(curTrace, GT_4CLASS, "Channel pool empty");
        return -1;
    }
    GT_0trace(curTrace, GT_3CLASS, "ipu_pm_alloc_sdma--");
    return 0;
}

int ipu_pm_free_sdma(int num_chs, int* channels)
{
    GT_0trace(curTrace, GT_3CLASS, "ipu_pm_free_sdma++");

    if(DMAAllocation == false) {
        GT_0trace(curTrace, GT_4CLASS, "Channel pool empty");
        return -1;
    }
    GT_0trace(curTrace, GT_3CLASS, "ipu_pm_free_sdma--");
    return 0;
}

int ipu_pm_camera_enable(unsigned int mode, unsigned int on)
{
    int ret = 0;

    //ret = campower_config(mode, on);

    if (mode < NUM_CAM_MODES && ret == 0)
        last_camera_req[mode] = on;

    return ret;
}

int ipu_pm_get_max_freq(unsigned int proc, unsigned int * freq)
{
    int status = EOK;

    switch (proc) {
        case RPRM_IVAHD:
            /* Would like to replace the below with a call to powerman */
            *freq = IVAHD_FREQ_MAX_IN_HZ;
            break;
        default:
            status = -ENOENT;
            break;
    }

    return status;
}

#ifdef QNX_PM_ENABLE
static int ipu_pm_power_init(void)
{
    /*Allocate SDMA channels*/
    memset(&sdma_req, 0, sizeof(sdma_req));
    sdma_req.length = MAX_DUCATI_CHANNELS;
    sdma_req.flags = RSRCDBMGR_DMA_CHANNEL | RSRCDBMGR_FLAG_RANGE;
    sdma_req.start = DUCATI_CHANNEL_START;
    sdma_req.end = DUCATI_CHANNEL_END;
    if (rsrcdbmgr_attach(&sdma_req, 1) == -1) {
        DMAAllocation = false;
        GT_1trace(curTrace, GT_4CLASS,
        "ipu_pm_power_init: DMA channel allocation FAILED: %s", strerror(errno));
    }
    else {
        GT_0trace(curTrace, GT_3CLASS,
            "ipu_pm_power_init: DMA channels ALLOCATED");
        DMAAllocation = true;
    }

    return EOK;
}

static void ipu_pm_power_deinit(void)
{
    if(DMAAllocation){
        if (rsrcdbmgr_detach(&sdma_req, 1) == -1) {
            GT_1trace(curTrace, GT_4CLASS,
                      "ipu_pm_power_deinit: DMA channel deallocation FAILED!!%s",
                      strerror(errno));
        }
        DMAAllocation = false;
    }
    return;
}

static int ipu_pm_powman_init(void)
{
    int status = EOK;

    ipc_auth_active = powman_auth_create("IPC_NEEDS_CORE_ACTIVE");
    if(!ipc_auth_active) {
        GT_setFailureReason(curTrace, GT_4CLASS, "powman_init", ENOMEM,
                "ipc_auth_active create failure");
        return -ENOMEM;

    }

    ipc_auth_oswr = powman_auth_create("IPC_NEEDS_PREVENT_OSWR");
    if(!ipc_auth_oswr) {
        GT_setFailureReason(curTrace, GT_4CLASS, "powman_init", ENOMEM,
                "ipc_auth_oswr create failure");
        return -ENOMEM;
    }

    int retry = 100;

    /* look for server  */
    cpudll_coid = name_open( CPUDLL_RECV_NAME, 0);
    while (cpudll_coid == -1 && retry-- > 0) {
        sleep(1);
        cpudll_coid = name_open (CPUDLL_RECV_NAME, 0);
    }

    if (cpudll_coid == -1) {
        GT_setFailureReason (curTrace, GT_4CLASS, "connect to cpudll", EINVAL,
                             "Couldn't connect to CPU DLL!");
        return EINVAL;
    }

    /* get IVA OPPs   */
    dvfsMessage.dvfs.type   = getListOfDomainOPPs;
    dvfsMessage.dvfs.domain = CPUDLL_OMAP_IVA;
    if (MsgSend( cpudll_coid, &dvfsMessage, sizeof( dvfsMessage ), &cpudll_iva_opp, sizeof(cpudll_iva_opp) ) == -1)  {
        GT_setFailureReason(curTrace, GT_4CLASS, "powman_init", ENOMEM,
                            "Could not get list of IVA OPPs.");
        return -ENOMEM;
    }

    /* get CORE OPPs   */
    dvfsMessage.dvfs.type   = getListOfDomainOPPs;
    dvfsMessage.dvfs.domain = CPUDLL_OMAP_CORE;
    if (MsgSend( cpudll_coid, &dvfsMessage, sizeof( dvfsMessage ), &cpudll_core_opp, sizeof(cpudll_core_opp) ) == -1)  {
        GT_setFailureReason(curTrace, GT_4CLASS, "powman_init", ENOMEM,
                            "Could not get list of Core OPPs.");
        return -ENOMEM;
    }
    return status;
}

static void ipu_pm_powman_deinit(void)
{
    int status = EOK;

    if (ipc_auth_active) {
        status = powman_auth_destroy(ipc_auth_active);
        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_powman_deinit",
                             status,
                             "powman_auth_destroy ipc_auth_active failure");
        }
        ipc_auth_active = NULL;
    }
    if (ipc_auth_oswr) {
        status = powman_auth_destroy(ipc_auth_oswr);
        if (status < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_powman_deinit",
                               status,
                               "powman_auth_destroy ipc_auth_oswr failure");
        }
        ipc_auth_oswr = NULL;
    }

    // close the channel
    dvfsMessage.dvfs.type   = (cpudll_type_e)closeClient;
    if (MsgSend( cpudll_coid, &dvfsMessage, sizeof( dvfsMessage ), NULL, 0 ) == -1) {
        GT_setFailureReason(curTrace, GT_4CLASS, "powman_deinit", ENOMEM,
                            "Could not close client connection to server.");
    }

    name_close(cpudll_coid);
    cpudll_coid = -1;
}

//no special callback needed in our case so define the default.
int powman_delayed_callback(unsigned ns, void (*func) (void *), void *data)
{
    return (powman_delayed_callback_default(ns, func, data));
}

static void tell_powman_auth_oswr(int need)
{
    int r;
    r = powman_auth_state(ipc_auth_oswr, need);
    if(r != 0) {
        GT_setFailureReason(curTrace, GT_4CLASS, "tell_powman_auth_oswr", r,
                                        "powerman authority :cannot set state");
    }
}

int ipu_pm_set_bandwidth(unsigned int bandwidth)
{
    int err;
    int oppIndex = CPUDLL_MAX_OPP_STATES-1;

    /* Camera needs OPPOV (highest OPP) which will be moving from index 1 to 2.
     * Find the greatest non-zero element to find the highest OPP and select it.
     */
    while ( (cpudll_core_opp.states[oppIndex] == 0) && (oppIndex > 0) ){
        oppIndex--;
    }

    dvfsMessage.dvfs.type   = setDomainOPP;
    dvfsMessage.dvfs.domain = CPUDLL_OMAP_CORE;

    dvfsMessage.dvfs.req_opp = cpudll_core_opp.states[ bandwidth>=COREOPP100?oppIndex:0 ];
    err = MsgSend( cpudll_coid, &dvfsMessage, sizeof( dvfsMessage ), NULL, 0 );
    if(err != EOK) {
        GT_1trace(curTrace, GT_4CLASS," ** Error setting CORE OPP: %s", strerror(errno));
    }
    return EOK;
}

int ipu_pm_set_rate(struct ipu_pm_const_req * request)
{
    int err = EOK;
    cpudll_iva_opp_t req = 0;

    if (request->target_rsrc == RPRM_IVAHD) {
        if (request->rate > FREQ_266Mhz)
            req = CPUDLL_IVA_OPPTURBO;
        else if ((request->rate > FREQ_133Mhz) &&
                 (request->rate <= FREQ_266Mhz))
            req = CPUDLL_IVA_OPP100;
        else if ((request->rate > NO_FREQ_CONSTRAINT) &&
                 (request->rate <= FREQ_133Mhz))
            req = CPUDLL_IVA_OPP50;
        else if (request->rate == NO_FREQ_CONSTRAINT)
            req = CPUDLL_IVA_OPPNONE;

        dvfsMessage.dvfs.req_opp = cpudll_iva_opp.states[req];
        dvfsMessage.dvfs.type   = setDomainOPP;
        dvfsMessage.dvfs.domain = CPUDLL_OMAP_IVA;

        err = MsgSend( cpudll_coid, &dvfsMessage, sizeof( dvfsMessage ), NULL, 0 );
        if(err != EOK) {
            GT_2trace(curTrace, GT_4CLASS," ** Error setting IVA OPP %d: %s", req, strerror(err));
        }
    }
    return err;
}
#else
int ipu_pm_set_rate(struct ipu_pm_const_req * request)
{
    return EOK;
}

int ipu_pm_set_bandwidth(unsigned int bandwidth)
{
    return EOK;
}
#endif

#ifdef BENELLI_SELF_HIBERNATION

static int configure_timer (int val, int reload)
{
    int status = 0;
    struct itimerspec timeout;
    timeout.it_value.tv_sec = val;
    timeout.it_value.tv_nsec = 0;
    timeout.it_interval.tv_sec = reload;
    timeout.it_interval.tv_nsec = 0;
    status = timer_settime(ipu_pm_state.hibernation_timer, 0, &timeout, NULL);
    if (status != 0) {
        status = -errno;
    }
    return status;
}

/* Function implements hibernation and watch dog timer
 * The functionality is based on following states
 * RESET:        Timer is disabed
 * OFF:            Timer is OFF
 * ON:            Timer running
 * HIBERNATE:    Waking up for benelli cores to hibernate
 * WD_RESET:    Waiting for Benelli cores to complete hibernation
 */
int ipu_pm_timer_state(int event)
{
    int retval = 0;

    if (!ipu_pm_state.attached)
        goto exit;

    switch (event) {
        case PM_HIB_TIMER_RESET:
            /* disable timer and remove irq handler */
            //Stop the timer
            configure_timer(0, 0);
            ipu_pm_state.hib_timer_state = PM_HIB_TIMER_RESET;
            break;

        case PM_HIB_TIMER_DELETE:
            if (ipu_pm_state.hib_timer_state == PM_HIB_TIMER_OFF) {
                /*Stop the Timer*/
                configure_timer(0, 0);
                /* Delete the timer */
                retval = timer_delete(ipu_pm_state.hibernation_timer);
               }
              break;

        case PM_HIB_TIMER_OFF:
            if (ipu_pm_state.hib_timer_state == PM_HIB_TIMER_ON) {
                /*Stop the Timer*/
                configure_timer(0, 0);
                ipu_pm_state.hib_timer_state = PM_HIB_TIMER_OFF;
            }
            break;

        case PM_HIB_TIMER_ON:
            if (ipu_pm_state.hib_timer_state == PM_HIB_TIMER_RESET||
                ipu_pm_state.hib_timer_state == PM_HIB_TIMER_OFF||
                ipu_pm_state.hib_timer_state == PM_HIB_TIMER_DELETE||
                ipu_pm_state.hib_timer_state == PM_HIB_TIMER_ON) {

                /*Enable the timer*/
                /*Start the Timer*/
                configure_timer(ipc_hib_timeout / 1000, 0);
                ipu_pm_state.hib_timer_state = PM_HIB_TIMER_ON;
            }
            break;
    }

exit:
    if (retval < 0) {
      GT_setFailureReason (curTrace,
                           GT_4CLASS,
                           "ipu_pm_timer_state",
                           retval,
                           "ipu_pm_timer_state failed");
    }

    return retval;
}

/*
  Function to save the MMU, Mailbox context before going to hibernation
 *
 */
int ipu_pm_save_ctx(int proc_id)
{
    int retval = 0;
    int flag;
    int num_loaded_cores = 0;
    int core0_loaded;
    int core1_loaded;
    unsigned long timeout;
    unsigned short core0_id = MultiProc_getId(CORE0);
    unsigned short core1_id = MultiProc_getId("CORE1");
    unsigned short dsp_id = MultiProc_getId("DSP");
    struct itimerspec value;
    uint64_t pa = 0, da = 0;
    u32 len = 0;

    /* get M3's load flag */
    core0_loaded = (ipu_pm_state.loaded_procs & CORE0_LOADED);
    core1_loaded = (ipu_pm_state.loaded_procs & CORE1_LOADED);

    /* Because of the current scheme, we need to check
     * if CORE1 is enabled and we need to shut it down too
     * CORE0 is the only one sending the hibernate message
    */
    pthread_mutex_lock(&ipu_pm_state.mtx);

    if (core0Idle == NULL) {
        if (proc_id == core0_id) {
            retval = get_res_info(RSC_SUSPENDADDR, "0", &da, &pa, &len);
            if (retval == 0) {
                /* BIOS flags to know the state of IPU cores */
                core0Idle = (void *)mmap_device_io(0x1000, ROUND_DOWN(pa, 0x1000));
                if ((uintptr_t)core0Idle == MAP_DEVICE_FAILED) {
                    core0Idle = NULL;
                    retval = -ENOMEM;
                    goto exit;
                }

                core0Idle = (void *)((uint32_t)core0Idle + ((uint32_t)pa - ROUND_DOWN((uint32_t)pa, 0x1000)));
                core1Idle = (void *)core0Idle + sizeof(void *);
            }
            else {
                goto exit;
            }
        }
    }

    if (proc_id == core0_id || proc_id == core1_id) {
        timer_gettime(ipu_pm_state.hibernation_timer, &value);
        if (value.it_value.tv_sec || value.it_value.tv_nsec)
            goto exit;

        if (!core0_loaded)
            goto exit;

        /* If already down don't kill it twice */
        if (ipu_pm_state.proc_state & CORE0_PROC_DOWN) {
            GT_0trace(curTrace, GT_4CLASS, "ipu already hibernated");
            goto exit;
        }

        !TESTBITREG32((uintptr_t)m3_clkstctrl,
                      CM_MPU_M3_CLKSTCTRL_CLKACTIVITY_BIT)) {
        retval = ArchIpcInt_sendInterrupt(core0_id,
                                          ipu_pm_state.cfg.int_id,
                                          RP_MBOX_HIBERNATION);

        num_loaded_cores = core1_loaded + core0_loaded;
        flag = 1;
        timeout = WAIT_FOR_IDLE_TIMEOUT;
        /* Wait fot Benelli to hibernate */
        do {
            /* Checking if IPU is really in idle */
            if (NUM_IDLE_CORES == num_loaded_cores) {
                flag = 0;
                break;
            } else {
                usleep(1000);
            }
        } while ( --timeout != 0);

        if (flag) {
            GT_0trace(curTrace, GT_4CLASS, "Benelli Cores are NOT really Idle");
            goto error;
        }

        ipu_pm_timer_state(PM_HIB_TIMER_OFF);
        retval = Omap5430IpcInt_mboxSaveCtxt(core0_id);
        if(retval != OMAP5430IPCINT_SUCCESS){
            GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_save_ctx",
                                retval,
                                "Error while saving the MailBox context");
            goto error;
        }

        if (core1_loaded) {
#ifndef IPC_DISABLE_WATCHDOG
            save_gpt_context(GPTIMER_11);
            ipu_pm_gpt_stop(GPTIMER_11);
            ipu_pm_gpt_disable(GPTIMER_11);
#endif
            if (GPT4InUse == TRUE)
                save_gpt_context(GPTIMER_4);

            retval = ProcMgr_control(ipu_pm_state.proc_handles[core1_id],
                                 Omap5430BenelliProc_CtrlCmd_Suspend, NULL);
            if (retval < 0) {
                GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_save_ctx",
                                    retval, "Error while suspending CORE1");
                goto error;
            }
            GT_0trace(curTrace, GT_4CLASS, "Sleep CORE1");
        }

#ifndef IPC_DISABLE_WATCHDOG
        save_gpt_context(GPTIMER_9);
        ipu_pm_gpt_stop(GPTIMER_9);
        ipu_pm_gpt_disable(GPTIMER_9);
#endif
        if (GPT3InUse == TRUE)
            save_gpt_context(GPTIMER_3);

        ipu_pm_state.proc_state |= CORE1_PROC_DOWN;
        retval = ProcMgr_control(ipu_pm_state.proc_handles[core0_id],
                                 Omap5430BenelliProc_CtrlCmd_Suspend, NULL);
        if (retval < 0) {
            GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_save_ctx", retval,
                                "Error while suspending CORE0");
            goto error;
        }
        GT_0trace(curTrace, GT_4CLASS, "Sleep CORE0");
        ipu_pm_state.proc_state |= CORE0_PROC_DOWN;

        ipu_pm_ivahd_off();

        // Advise that Ducati is hibernating
        pthread_mutex_lock(&ipc_hib_mutex);
        ipc_hib_hibernating = TRUE;
        pthread_mutex_unlock(&ipc_hib_mutex);
    }
    else if (proc_id == dsp_id) {
        //TODO: Add support for DSP.
    }
    else
        goto error;

#ifdef QNX_PM_ENABLE
    if (oswr_prevent == 1) {
        tell_powman_auth_oswr(0); // Passing 1 prevents OSWR and 0 allows OSWR
        oswr_prevent = 0;
    }
#endif
       /* If there is a message in the mbox restore
     * immediately after save.
     */
    if (PENDING_MBOX_MSG)
        goto restore;

exit:
    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return 0;
error:
    GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_save_ctx", retval,
                        "Aborting hibernation process");
    ipu_pm_timer_state(PM_HIB_TIMER_ON);
    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return retval;
restore:
    GT_0trace(curTrace, GT_4CLASS,
              "Starting restore_ctx since messages pending in mbox");
    pthread_mutex_unlock(&ipu_pm_state.mtx);
    ipu_pm_restore_ctx(proc_id);

    return retval;
}


/* Function to check if a processor is shutdown
 * if shutdown then restore context else return.
 */
int ipu_pm_restore_ctx(int proc_id)
{
    int retval = 0;
    int core0_loaded;
    int core1_loaded;
    unsigned short core0_id = MultiProc_getId(CORE0);
    unsigned short core1_id = MultiProc_getId("CORE1");
    unsigned short dsp_id = MultiProc_getId("DSP");

    /*If feature not supported by proc, return*/
    if (proc_id == dsp_id)
        return 0;

    /* Check if the M3 was loaded */
    core0_loaded = (ipu_pm_state.loaded_procs & CORE0_LOADED);
    core1_loaded = (ipu_pm_state.loaded_procs & CORE1_LOADED);

    /* Because of the current scheme, we need to check
     * if CORE1 is enable and we need to enable it too
     * In both cases we should check if for both cores
     * and enable them if they were loaded.
     */
    pthread_mutex_lock(&ipu_pm_state.mtx);

    /* Restart the hib timer */
    if (ipc_hib_enable) {
        ipu_pm_timer_state(PM_HIB_TIMER_ON);
    }
#ifdef QNX_PM_ENABLE
    if(oswr_prevent == 0) {
        tell_powman_auth_oswr(1); // Passing 1 prevents OSWR and 0 allows OSWR
        oswr_prevent = 1;
    }
#endif
    if (proc_id == core0_id || proc_id == core1_id) {
        if (!(ipu_pm_state.proc_state & CORE0_PROC_DOWN) || !core0_loaded) {
            goto exit;
        }

        if (ProcMgr_getState(ipu_pm_state.proc_handles[core0_id]) != ProcMgr_State_Suspended) {
            goto exit;
        }

        retval = Omap5430IpcInt_mboxRestoreCtxt(core0_id);
        if(retval != OMAP5430IPCINT_SUCCESS){
            GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_restore_ctx",
                                retval,
                                "Not able to restore Mail Box context");
            goto error;
        }

#ifndef IPC_DISABLE_WATCHDOG
        ipu_pm_gpt_enable(GPTIMER_9);
        restore_gpt_context(GPTIMER_9);
        ipu_pm_gpt_start(GPTIMER_9);
#endif
        if (GPT3InUse == TRUE) {
            ipu_pm_gpt_enable(GPTIMER_3);
            restore_gpt_context(GPTIMER_3);
        }

        GT_0trace(curTrace, GT_4CLASS, "Wakeup CORE0");
        ipu_pm_state.proc_state &= ~CORE0_PROC_DOWN;
        retval = ProcMgr_control(ipu_pm_state.proc_handles[core0_id],
                                 Omap5430BenelliProc_CtrlCmd_Resume, NULL);
        if (retval < 0){
            GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_restore_ctx",
                                retval, "Not able to resume CORE0");
            goto error;
        }

        if (core1_loaded) {
#ifndef IPC_DISABLE_WATCHDOG
            ipu_pm_gpt_enable(GPTIMER_11);
            restore_gpt_context(GPTIMER_11);
            ipu_pm_gpt_start(GPTIMER_11);
#endif
            if (GPT4InUse == TRUE) {
                ipu_pm_gpt_enable(GPTIMER_4);
                restore_gpt_context(GPTIMER_4);
            }

            GT_0trace(curTrace, GT_4CLASS, "Wakeup CORE1");
            ipu_pm_state.proc_state &= ~CORE1_PROC_DOWN;
            retval = ProcMgr_control(ipu_pm_state.proc_handles[core1_id],
                                     Omap5430BenelliProc_CtrlCmd_Resume, NULL);
            if (retval < 0){
                GT_setFailureReason(curTrace, GT_4CLASS, "ipu_pm_restore_ctx",
                                    retval, "Not able to resume CORE1");
                goto error;
            }
        }
        pthread_mutex_lock(&ipc_hib_mutex);
        // Once we are active, signal any thread waiting for end of hibernation
        ipc_hib_hibernating = FALSE;
        pthread_cond_broadcast(&ipc_hib_cond);
        pthread_mutex_unlock(&ipc_hib_mutex);
    }
    else
        goto error;
exit:
    /* turn on benelli hibernation timer */
    if (ipu_pm_state.hib_timer_state == PM_HIB_TIMER_OFF ||
        ipu_pm_state.hib_timer_state == PM_HIB_TIMER_RESET) {
            ipu_pm_timer_state(PM_HIB_TIMER_ON);
    }
    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return retval;
error:
    pthread_mutex_unlock(&ipu_pm_state.mtx);
    return -EINVAL;
}

/* ISR for Timer*/
static void ipu_pm_timer_interrupt (union sigval val)
{
    ipu_pm_save_ctx(MultiProc_getId(CORE0));
    return;
}
#else // BENELLI_SELF_HIBERNATION

int ipu_pm_restore_ctx(int proc_id)
{
    return 0;
}
#endif // BENELLI_SELF_HIBERNATION

int ipu_pm_attach(int proc_id)
{
    int retval = EOK;
#ifndef IPC_DISABLE_WATCHDOG
    OsalIsr_Params isrParams;
#endif

    if (proc_id > MultiProc_MAXPROCESSORS) {
        return -EINVAL;
    }

    if (proc_id == MultiProc_getId(CORE0)) {
        ipu_pm_state.loaded_procs |= CORE0_LOADED;
#ifndef IPC_DISABLE_WATCHDOG
        ipu_pm_gpt_enable(GPTIMER_9);
        isrParams.checkAndClearFxn = ipu_pm_clr_gptimer_interrupt;
        isrParams.fxnArgs = (Ptr)GPTIMER_9;
        isrParams.intId = OMAP54XX_IRQ_GPT9;
        isrParams.sharedInt = FALSE;
        ipu_pm_state.gpt9IsrObject =
            OsalIsr_create(&ipu_pm_gptimer_interrupt,
                           isrParams.fxnArgs, &isrParams);
        if(ipu_pm_state.gpt9IsrObject != NULL) {
            if (OsalIsr_install(ipu_pm_state.gpt9IsrObject) < 0) {
                retval = -ENOMEM;
            }
        }
        else {
            retval = -ENOMEM;
        }
#endif
#ifndef IPC_SYSBIOS_SMP
    }
    else if (proc_id == MultiProc_getId("CORE1")) {
#endif
        ipu_pm_state.loaded_procs |= CORE1_LOADED;
#ifndef IPC_DISABLE_WATCHDOG
        ipu_pm_gpt_enable(GPTIMER_11);
        isrParams.checkAndClearFxn = ipu_pm_clr_gptimer_interrupt;
        isrParams.fxnArgs = (Ptr)GPTIMER_11;
        isrParams.intId = OMAP54XX_IRQ_GPT11;
        isrParams.sharedInt = FALSE;
        ipu_pm_state.gpt11IsrObject =
            OsalIsr_create(&ipu_pm_gptimer_interrupt,
                           isrParams.fxnArgs, &isrParams);
        if(ipu_pm_state.gpt11IsrObject != NULL) {
            if (OsalIsr_install(ipu_pm_state.gpt11IsrObject) < 0) {
                retval = -ENOMEM;
            }
        }
        else {
            retval = -ENOMEM;
        }
#endif
    }
    else if (proc_id == MultiProc_getId("DSP")) {
        ipu_pm_state.loaded_procs |= DSP_LOADED;
#ifndef IPC_DISABLE_WATCHDOG
        ipu_pm_gpt_enable(GPTIMER_6);
        isrParams.checkAndClearFxn = ipu_pm_clr_gptimer_interrupt;
        isrParams.fxnArgs = (Ptr)GPTIMER_6;
        isrParams.intId = OMAP54XX_IRQ_GPT6;
        isrParams.sharedInt = FALSE;
        ipu_pm_state.gpt6IsrObject =
            OsalIsr_create(&ipu_pm_gptimer_interrupt,
                           isrParams.fxnArgs, &isrParams);
        if(ipu_pm_state.gpt6IsrObject != NULL) {
            if (OsalIsr_install(ipu_pm_state.gpt6IsrObject) < 0) {
                retval = -ENOMEM;
            }
        }
        else {
            retval = -ENOMEM;
        }
#endif
    }

    if (retval >= 0)
        retval = ProcMgr_open(&ipu_pm_state.proc_handles[proc_id], proc_id);

    if (retval < 0) {
#ifndef IPC_DISABLE_WATCHDOG
        if (proc_id == MultiProc_getId(CORE0)) {
            if (ipu_pm_state.gpt9IsrObject) {
                OsalIsr_uninstall(ipu_pm_state.gpt9IsrObject);
                OsalIsr_delete(&ipu_pm_state.gpt9IsrObject);
                ipu_pm_state.gpt9IsrObject = NULL;
            }
            ipu_pm_gpt_stop(GPTIMER_9);
            ipu_pm_gpt_disable(GPTIMER_9);
#ifndef IPC_SYSBIOS_SMP
        }
        else if (proc_id == MultiProc_getId("CORE1")) {
#endif
            if (ipu_pm_state.gpt11IsrObject) {
                OsalIsr_delete(&ipu_pm_state.gpt11IsrObject);
                ipu_pm_state.gpt11IsrObject = NULL;
            }
            ipu_pm_gpt_stop(GPTIMER_11);
            ipu_pm_gpt_disable(GPTIMER_11);
        }
        else if (proc_id == MultiProc_getId("DSP")) {
            if (ipu_pm_state.gpt6IsrObject) {
                OsalIsr_uninstall(ipu_pm_state.gpt6IsrObject);
                OsalIsr_delete(&ipu_pm_state.gpt6IsrObject);
                ipu_pm_state.gpt6IsrObject = NULL;
            }
            ipu_pm_gpt_stop(GPTIMER_6);
            ipu_pm_gpt_disable(GPTIMER_6);
        }
#endif

    }
    else {
        ipu_pm_state.attached[proc_id] = TRUE;
    }

    return retval;
}

int ipu_pm_detach(int proc_id)
{
    int retval = EOK;

    if (proc_id > MultiProc_MAXPROCESSORS) {
        return -EINVAL;
    }

    ipu_pm_state.attached[proc_id] = FALSE;

#ifdef BENELLI_SELF_HIBERNATION
    if (core0Idle != NULL) {
        munmap_device_io(ROUND_DOWN((uint32_t)core0Idle, 0x1000),
                         0x1000);
        core0Idle = NULL;
        core1Idle = NULL;
    }
#endif

    if (proc_id == MultiProc_getId(CORE0)) {
#ifndef IPC_DISABLE_WATCHDOG
        OsalIsr_uninstall(ipu_pm_state.gpt9IsrObject);
        OsalIsr_delete(&ipu_pm_state.gpt9IsrObject);
        ipu_pm_state.gpt9IsrObject = NULL;
        ipu_pm_gpt_stop(GPTIMER_9);
        ipu_pm_gpt_disable(GPTIMER_9);
#endif
        ipu_pm_state.loaded_procs &= ~CORE0_LOADED;
#ifndef IPC_SYSBIOS_SMP
    }
    else if (proc_id == MultiProc_getId("CORE1")) {
#endif
#ifndef IPC_DISABLE_WATCHDOG
        OsalIsr_uninstall(ipu_pm_state.gpt11IsrObject);
        OsalIsr_delete(&ipu_pm_state.gpt11IsrObject);
        ipu_pm_state.gpt11IsrObject = NULL;
        ipu_pm_gpt_stop(GPTIMER_11);
        ipu_pm_gpt_disable(GPTIMER_11);
#endif
        ipu_pm_state.loaded_procs &= ~CORE1_LOADED;
    }
    else if (proc_id == MultiProc_getId("DSP")) {
#ifndef IPC_DISABLE_WATCHDOG
        OsalIsr_uninstall(ipu_pm_state.gpt6IsrObject);
        OsalIsr_delete(&ipu_pm_state.gpt6IsrObject);
        ipu_pm_state.gpt6IsrObject = NULL;
        ipu_pm_gpt_stop(GPTIMER_6);
        ipu_pm_gpt_disable(GPTIMER_6);
#endif
        ipu_pm_state.loaded_procs &= ~DSP_LOADED;
    }

    if (ipu_pm_state.proc_handles[proc_id]) {
        ProcMgr_close(&ipu_pm_state.proc_handles[proc_id]);
        ipu_pm_state.proc_handles[proc_id] = NULL;
    }

    return retval;
}

int ipu_pm_setup(ipu_pm_config *cfg)
{
    int retval = EOK;
    int i = 0;
#ifdef BENELLI_SELF_HIBERNATION
    struct sigevent signal_event;
#endif

    if (ipu_pm_state.is_setup == false) {
        pthread_mutex_init(&ipu_pm_state.mtx, NULL);

        if (cfg == NULL) {
            retval = -EINVAL;
            goto exit;
        }
        if (cfg->num_procs > MultiProc_MAXPROCESSORS) {
            retval = -EINVAL;
            goto exit;
        }

        memcpy(&ipu_pm_state.cfg, cfg, sizeof(ipu_pm_config));

#ifdef BENELLI_SELF_HIBERNATION
        /* MBOX flag to check if there are pending messages */
        a9_m3_mbox = (void *)mmap_device_io(0x1000, A9_M3_MBOX);
        if ((uintptr_t)a9_m3_mbox == MAP_DEVICE_FAILED) {
            a9_m3_mbox = NULL;
            retval = -ENOMEM;
            goto exit;
        }

        if (ipc_hib_enable) {
            SIGEV_THREAD_INIT (&signal_event, ipu_pm_timer_interrupt, NULL,
                               NULL);
            retval = timer_create(CLOCK_REALTIME, &signal_event,
                                  &ipu_pm_state.hibernation_timer);
            if (retval < 0) {
                retval = -errno;
                goto exit;
            }
        }
#endif

        cm2_base_va = (void *)mmap_device_io(CM2_SIZE, CM2_BASE);
        if ((uintptr_t)cm2_base_va == MAP_DEVICE_FAILED) {
            cm2_base_va = NULL;
            retval = -errno;
            goto exit;
        }
#ifdef BENELLI_SELF_HIBERNATION
        m3_clkstctrl = cm2_base_va + CM_MPU_M3_CLKCTRL_OFFSET;
#endif

        prm_base_va = (void *)mmap_device_io(PRM_SIZE, PRM_BASE);
        if ((uintptr_t)prm_base_va == MAP_DEVICE_FAILED) {
            prm_base_va = NULL;
            retval = -errno;
            goto exit;
        }

        cm_core_aon_base_va = (void*)mmap_device_io(CM_CORE_AON_SIZE, CM_CORE_AON_BASE);
        if((uintptr_t)cm_core_aon_base_va == MAP_DEVICE_FAILED) {
            cm_core_aon_base_va = NULL;
            retval = -errno;
            goto exit;
        }

        map_gpt_regs();
#ifdef QNX_PM_ENABLE
        ipu_pm_powman_init();
        ipu_pm_power_init();
#endif
        for (i = 0; i < NUM_CAM_MODES; i++)
            last_camera_req[i] = 0;
        last_led_req = 0;

        ipu_pm_state.is_setup = true;
    }

exit:
    if (retval != EOK) {
        unmap_gpt_regs();
        if (prm_base_va) {
            munmap(prm_base_va, PRM_SIZE);
            prm_base_va = NULL;
        }
        if (cm2_base_va) {
            munmap(cm2_base_va, CM2_SIZE);
            cm2_base_va = NULL;
        }
#ifdef BENELLI_SELF_HIBERNATION
        m3_clkstctrl = NULL;

        if (a9_m3_mbox) {
            munmap(a9_m3_mbox, 0x1000);
            a9_m3_mbox = NULL;
        }
#endif
        ipu_pm_state.loaded_procs = 0;
        pthread_mutex_destroy(&ipu_pm_state.mtx);
    }
    return retval;
}

int ipu_pm_destroy()
{
    int i = 0;

    if (ipu_pm_state.is_setup) {
        for (i = 0; i < NUM_CAM_MODES; i++) {
            if (last_camera_req[i])
                ipu_pm_camera_enable(i, 0);
        }
        if (last_led_req)
            ipu_pm_led_enable(0, 0);

#ifdef QNX_PM_ENABLE
        ipu_pm_power_deinit();
        ipu_pm_powman_deinit();
#endif

        unmap_gpt_regs();
#ifdef BENELLI_SELF_HIBERNATION
        if (ipc_hib_enable) {
            /*Stop the Timer*/
            configure_timer(0, 0);
            /* Delete the timer */
            timer_delete(ipu_pm_state.hibernation_timer);
        }
        if (a9_m3_mbox) {
            munmap(a9_m3_mbox, 0x1000);
            a9_m3_mbox = NULL;
        }
        m3_clkstctrl = NULL;
#endif
        if (cm2_base_va) {
            munmap(cm2_base_va, CM2_SIZE);
            cm2_base_va = NULL;
        }
        if (prm_base_va) {
            munmap(prm_base_va, PRM_SIZE);
            prm_base_va = NULL;
        }
        pthread_mutex_destroy(&ipu_pm_state.mtx);
        ipu_pm_state.proc_state = 0;
        ipu_pm_state.loaded_procs = 0;
        ipu_pm_state.ivahd_use_cnt = 0;
        ipu_pm_state.is_setup = false;
    }
    return EOK;
}
