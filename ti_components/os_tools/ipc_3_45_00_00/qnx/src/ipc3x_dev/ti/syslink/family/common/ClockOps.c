/*
 *  @file   ClockOps.c
 *
 *  @brief      Generic clock module interface across platforms and OS
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2013, Texas Instruments Incorporated
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


/* Standard headers */
#include <ti/syslink/Std.h>
/* Module level headers */
#include <ti/syslink/inc/ClockOps.h>

/* standard include for reg access */
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>

//#include <ti/syslink/inc/ClockOps.h>
#include <ti/syslink/utils/Trace.h>
#include <ti/syslink/utils/String.h>


#if defined (__cplusplus)
extern "C" {
#endif

/*Function Prototypes */
void prcm_enable(UInt32 clkstctrl, UInt32 clkctrl, UInt32 regVal1, UInt32 regVal2, UInt32 cmpVal1, UInt32 cmpVal2, UInt32 wait1, UInt32 wait2);
void GEMSSClkEnable(void);
void GEMSSClkDisable(void);;
void DucatiClkEnable(void) ;
void DucatiClkDisable(void) ;
void prcm_disable_spinbox(void);
void prcm_disable_mailbox(void);
void prcm_disable_gptimer4(void);



#define LAST_CORE 1

String handleArray[] = {

"spinbox_ick",
"mailbox_ick",
"gpt4_ick",
"gpt4_fck",
"mmu_ick",
"mmu_cfg_ick",
"gem_ick" /* dsp_ick string is changed in latest linux release to gem_ick*/
};

typedef enum {
    SPINBOX=1,
    MAILBOX=2,
    IGPTIMER4=3,
    FGPTIMER4=4,
    MMU=5,
    MMUCFG=6,
    DSP=7,
    DUCATI=8
}clkType;

/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
#define PRCM_BASE_ADDR              0x48180000
#define PRCM_SIZE                   0x00003000
#define PM_ACTIVE_PWRSTST           0x00000A04

#define CM_MMU_CLKSTCTRL            0x0000140C
#define CM_ALWON_MMUDATA_CLKCTRL    0x0000159C
#define CM_MMUCFG_CLKSTCTRL         0x00001410
#define CM_ALWON_MMUCFG_CLKCTRL     0x000015A8

#define GEM_L2RAM_BASE_ADDR         0x40800000
#define GEM_L2RAM_SIZE              0x00040000
#define DSPMEM_SLEEP                0x00000650

#define OSC_0                       20
#define OSC_1                       20
#define PLL_BASE_ADDRESS            0x481C5000
#define DSP_PLL_BASE                (PLL_BASE_ADDRESS+0x080)
#define DSPBOOTADDR                 0x00000048
#define CM_ALWON_SPINBOX_CLKCTRL    0x00001598
#define CM_ALWON_MAILBOX_CLKCTRL    0x00001594
#define CM_ALWON_L3_SLOW_CLKSTCTRL  0x00001400
#define CM_ALWON_TIMER_4_CLKCTRL    0x0000157C
#define CTRL_MODULE_BASE_ADDR       0x48140000

#define RM_DEFAULT_RSTCTRL          0x00000B10
#define RM_DEFAULT_RSTST            0x00000B14
#define CM_DEFAULT_DUCATI_CLKSTCTRL 0x00000518
#define CM_DEFAULT_DUCATI_CLKCTRL   0x00000574

/* for gptimer4 fck */
#define CM_SYSCLK18_CLKSEL          0x00000378
#define CM_DMTIMER_CLKSRC           0x000002E0
#define CM_SYSCLK18_CLKSRC          0x000002F0
#define CM_DPLL_SYSCLK18_CLKSEL     (PRCM_BASE_ADDR+CM_SYSCLK18_CLKSEL)
#define SYSCLK18_CLKSRC             (PLL_BASE_ADDRESS+CM_SYSCLK18_CLKSRC)
#define DMTIMER_CLKSRC              (PLL_BASE_ADDRESS+CM_DMTIMER_CLKSRC)

#define ADPLLJ_CLKCRTL_HS2    0x00000801 //HS2 Mode,TINTZ =1  --used by all PLL's except HDMI

/* ISS PLL releated defines */
#define ISS_PLL_BASE            (PLL_BASE_ADDRESS+0x140)


//ADPLL intrnal Offset Registers
#define CLKCTRL                                 0x4
#define TENABLE                                 0x8
#define TENABLEDIV                              0xC
#define M2NDIV                                  0x10
#define MN2DIV                                  0x14
#define STATUS                                  0x24

/*!
 *  @brief  PRM address for GEM
 */
#define CM_GEM_CLKSTCTRL                0x400
/*!
 *  @brief  Clock mgmt for GEM
 */
#define CM_ACTIVE_GEM_CLKCTRL           0x420
/*!
 *  @brief  Reset control for GEM
 */
#define RM_ACTIVE_RSTCTRL               0xA10
/*!
 *  @brief  Reset status for GEM
 */
#define RM_ACTIVE_RSTST                 0xA14

#define REMAP(x)             (mmap_device_io(4,x))
#define UNMAP(x)             (munmap_device_io(x,4))
#define REGWR(x,y)           (out32(x,y))
#define REGRD(x)             (in32(x))
#define REGRDMWR(x, mask, val) REGWR(x,((REGRD(x) & mask) | val))

/* =============================================================================
 * Static globals
 * =============================================================================
 */
UInt32 refSpinCount = 0;
UInt32 refMboxCount = 0;
UInt32 refGptimer4ick = 0;
UInt32 refGptimer4fck = 0;
UInt32 refDSP = 0;
UInt32 refDucati = 0;

/*!
 *  @brief      Function returns the clock handle .
 *
 *  @clkHandle   clk handle returned to corresponding clk name
 *  @clkname     name of clk for which handle is to be obtained
 *
 */
Ptr
ClockOps_get (ClockOps_Handle handle, String clkName)
{
    clkType ctype = SPINBOX;

    if (!String_cmp(clkName,"spinbox_ick")) {
        ctype = SPINBOX;
    }
    else if (!String_cmp(clkName,"mailbox_ick")) {
        ctype = MAILBOX;
    }
    else if (!String_cmp(clkName,"gpt4_ick")) {
        ctype = IGPTIMER4;
    }
    else if (!String_cmp(clkName,"gpt4_fck")) {
        ctype = FGPTIMER4;
    }
    else if (!String_cmp(clkName,"mmu_ick")) {
        ctype = MMU;
    }
    else if (!String_cmp(clkName,"mmu_cfg_ick")) {
        ctype = MMUCFG;
    }
/* dsp_ick string is changed in latest linux release to gem_ick*/
    else if (!String_cmp(clkName,"gem_ick")) {
        ctype = DSP;
    }
    else if (!String_cmp(clkName,"ducati_ick")) {
        ctype = DUCATI;
    }
    else {
        /* should not come here */
    }

    return ((Ptr)ctype);
}

/*!
 *  @brief      Function returns the clock handle .
 *
 *  @clkHandle   clk handle returned to corresponding clk name
 *  @clkname     name of clk for which handle is to be obtained
 *
 */
Void
ClockOps_put(ClockOps_Handle handle, Ptr clkHandle)
{
    //clk_put((struct clk *)clkHandle);
}
/*!
 *  @brief      Function returns the clock handle .
 *
 *  @clkHandle   clk handle returned to corresponding clk name
 *  @clkname     name of clk for which handle is to be obtained
 *
 *  @sa         ClockOps_put
 */
Int32
ClockOps_enable(ClockOps_Handle handle, Ptr clkHandle)
{
    return 1;
}
/*!
 *  @brief      Function returns the clock handle .
 *
 *  @clkHandle   clk handle returned to corresponding clk name
 *  @clkname     name of clk for which handle is to be obtained
 *
 *  @sa         ClockOps_put
 */
Void
ClockOps_disable(ClockOps_Handle handle, Ptr clkHandle)
{
}

/*!
 *  @brief      Function returns the clock handle .
 *
 *  @clkHandle   clk handle returned to corresponding clk name
 *  @clkname     name of clk for which handle is to be obtained
 *
 *  @sa         ClockOps_put
 */
ULong
ClockOps_getRate(ClockOps_Handle handle, Ptr clkHandle)
{
    //return(clk_get_rate((struct clk *)clkHandle));
    return 1;
}

/*!
 *  @brief      Function returns the clock handle .
 *
 *  @clkHandle   clk handle returned to corresponding clk name
 *  @clkname     name of clk for which handle is to be obtained
 *
 *  @sa         ClockOps_put
 */
Int32
ClockOps_setRate(ClockOps_Handle handle, Ptr clkHandle, ULong rate)
{
    //return (clk_set_rate((struct clk *)clkHandle, rate));
    return 1;
}

void PLL_Clocks_Config(UInt32 Base_Address,UInt32 OSC_FREQ,UInt32 N,UInt32 M,UInt32 M2,UInt32 CLKCTRL_VAL)
{
}


#if defined (__cplusplus)

}
#endif
