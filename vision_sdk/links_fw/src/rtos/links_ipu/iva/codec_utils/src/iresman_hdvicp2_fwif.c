/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file iresman_hdvicp2_fwif.c
 *
 * \brief  IVA codec Appl plug-in functions are implemented
 *         This file contains implementation for IRESMAN APIs configure, wait
 *         and done. It also contains the ISR and SWI function implementations
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

/****************************************************************
*  INCLUDE FILES
****************************************************************/
#include <string.h>
#include <src/rtos/links_ipu/iva/codec_utils/src/dbc.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
//#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Gate.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <src/rtos/links_ipu/iva/codec_utils/hdvicp2_config.h>
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec_prf.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

/****************************************************************
* DEFINES
****************************************************************/

/** Interrupt number corresponding to IVAHD interrupt lines */
#define IVAHD_INTRPT_ID 38

/****************************************************************
* STRUCTURE DEFINITIONS
****************************************************************/

/** ========================================================================== */
/** IRESMAN_HDVICP2_SWIarg  describes the SWI Argument list.
*
* @param  cbFunctionPtr  Callback function pointer
* @param  algHandle      Algorithm Handle
* @param  cbArgs         Arguments to the callback function
*
*/
/** ========================================================================== */
typedef struct IRESMAN_HDVICP2_SWIarg {
    IRES_HDVICP2_CallbackFxn cbFunctionPtr;
    IALG_Handle algHandle;
    Void *cbArgs;
    int id;
} IRESMAN_HDVICP2_SWIarg;

typedef struct _IRESMAN__HDVICP2_context {
    /** Handle to SWI returned from Swi_create */
    Swi_Handle swiHandle;
    Swi_Struct swiStruct;
    IRESMAN_HDVICP2_SWIarg swiArg;

    /** Global variable to hold the semaphore handle */
    BspOsal_SemHandle semHandle;

    /** Handle to HWI returned from Hwi_create function */
    Hwi_Handle hwiHandle;
    Hwi_Struct hwiStruct;

    /** Flag to restrict HWI create to first time */
    int initialized;

	Bool inIVAHDprocess;
} IRESMAN__HDVICP2_context;

/****************************************************************
* FUNCTION PROTOTYPES
****************************************************************/
void IRESMAN_HDVICP2_ISR(UArg hwiArgs);
void IRESMAN_HDVICP2_SwiFunc(UArg swiArgs, UArg swiArgs_2);

/****************************************************************
* GLOBALS
****************************************************************/
#define MAX_IVAHD 1

IRESMAN__HDVICP2_context _HDVICP2_context[MAX_IVAHD] = { 0 };

static int _first_time = 0;

/** ========================================================================== */
/**
* IRESMAN_HDVICP2_ISR(hwiArgs) : Call-Back function tied to IVAHD-0.
* As with Ducati a single IVA-HD resource is tied this id shall be zero.
*
* @param hwiArgs     Parameter configuration for HWI's - indicates IVAHD number
*
* @return           None
*/
/** ========================================================================== */

void IRESMAN_HDVICP2_ISR(UArg hwiArgs)
{
    /* hwiArgs indicates the IVAHD number */
    if (hwiArgs == 0)
    {
        Hwi_disableInterrupt(IVAHD_INTRPT_ID);
    }
#ifdef UTILS_ENCDEC_HDVICP_PROFILE
    {
        UInt32 curTime = Utils_encdecGetTime();

        g_HDVICP_logTbl[0].totalWait2Isr +=
            (curTime - g_HDVICP_logTbl[0].tempWaitTime);
        g_HDVICP_logTbl[0].tempPrevTime = curTime;
    }
#endif
    Swi_post(_HDVICP2_context[hwiArgs].swiHandle);
}

/** ========================================================================== */
/**
* IRESMAN_HDVICP2_SwiFunc(swiArgs, swiArgs_2) : Swi triggered by the ISR func
* Releases the semaphore that "wait" is pending on
*
* @param swiArgs     Parameter properties for SWI
* @param swiArgs_2   Parameter add to conform to XDC func. signature
*
* @return           None
*/
/** ========================================================================== */

void IRESMAN_HDVICP2_SwiFunc(UArg swiArgs, UArg swiArgs_2)
{
    IRESMAN_HDVICP2_SWIarg *CB;
    IALG_Handle algHandle;
    Void *cbArgs;
    IRES_HDVICP2_CallbackFxn cbFunctionPtr;

    DBC_require(swiArgs);

    CB = (IRESMAN_HDVICP2_SWIarg *) swiArgs;

    algHandle = CB->algHandle;
    cbArgs = CB->cbArgs;
    cbFunctionPtr = CB->cbFunctionPtr;

    cbFunctionPtr(algHandle, cbArgs);

    /** Clear the interrupt line for IVAHD-0
     * TODO: For multiple IVAHD's plugin
     * the corresponding interrupt line clear here */
    if (CB->id == 0)
    {
        Hwi_clearInterrupt(IVAHD_INTRPT_ID);
        Hwi_enableInterrupt(IVAHD_INTRPT_ID);
    }
}

/*----------------------------------------------------------------------------*/
/* Hex code to set for Stack setting, Interrupt vector setting */
/* and instruction to put ICONT in WFI mode.  */
/* This shall be placed at TCM_BASE_ADDRESS of given IVAHD, which is */
/* 0x0000 locally after reset.  */
/*----------------------------------------------------------------------------*/
#define LENGTH_BOOT_CODE  14
/**
 *  Macro defining ICONT1 DTCM offset from the base address
*/
#define ICONT1_DTCM_OFFSET 0x00000000
/**
 *  Macro defining ICONT2 DTCM offset from the base address
*/
#define ICONT2_DTCM_OFFSET 0x00010000
/**
 *  Macro defining ICONT1 ITCM offset from the base address
*/
#define ICONT1_ITCM_OFFSET 0x00008000
/**
 *  Macro defining ICONT2 ITCM offset from the base address
*/
#define ICONT2_ITCM_OFFSET 0x00018000

const unsigned int IVAHD_memory_wfi[LENGTH_BOOT_CODE] = {
    0xEA000006,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xE3A00000,
    0xEE070F9A,
    0xEE070F90,
    0xE3A00000,
    0xEAFFFFFE,
    0xEAFFFFF1
};

/** ========================================================================== */
/**
* HDVICP_Configure(algHandle, iresHandle, cbFunctionPtr, cbArgs) :
* This API ties the ISR function to the HDVICP interrupt
* Also, creates the semaphore with 0 count and creates the Swi obj
*
* @param algHandle     Algorithm Handle
* @param iresHandle    IRES Handle
* @param cbFunctionPtr Pointer to the callback function
* @param cbArgs        Argument to be passed to the callback function
*
* @return           None
*/
/** ========================================================================== */
extern Hwi_Handle ti_sdo_fc_ires_hdvicp_HDVICP2_hwi0;

void HDVICP_Configure(IALG_Handle algHandle,
                      struct IRES_HDVICP2_Obj *iresHandle,
                      IRES_HDVICP2_CallbackFxn cbFunctionPtr, Void * cbArgs)
{
    Hwi_Params hwiParams;
    Swi_Params swiParams;
    Error_Block eb;

    Error_init(&eb);

    DBC_require(iresHandle);

    if (_first_time == 0)
    {
        memset(_HDVICP2_context, 0x00, sizeof(_HDVICP2_context));
        _first_time = 1;
    }

    /*-----------------------------------------------------------------------*/
    /* Initialize the Handle to the MB processing function that is */
    /* required to be called by the ISR.  */
    /*-----------------------------------------------------------------------*/
    _HDVICP2_context[iresHandle->id].swiArg.algHandle = algHandle;

    /*-----------------------------------------------------------------------*/
    /* Initialize the global function ptr to the MB processing function */
    /* which will be called from the ISR.  */
    /*-----------------------------------------------------------------------*/
    _HDVICP2_context[iresHandle->id].swiArg.cbFunctionPtr = cbFunctionPtr;

    /*-----------------------------------------------------------------------*/
    /* Initialize the Argument to the MB processing function that is */
    /* required to be called by the ISR.  */
    /*-----------------------------------------------------------------------*/
    _HDVICP2_context[iresHandle->id].swiArg.cbArgs = cbArgs;
    _HDVICP2_context[iresHandle->id].swiArg.id = iresHandle->id;

    if (!_HDVICP2_context[iresHandle->id].initialized)
    {
        _HDVICP2_context[iresHandle->id].initialized = 1;

        /* create a Swi to be called to release the semaphore in "done" */
        Swi_Params_init(&swiParams);
        swiParams.arg0 = (UArg) (&_HDVICP2_context[iresHandle->id].swiArg);
        Swi_construct(&_HDVICP2_context[iresHandle->id].swiStruct,
                      IRESMAN_HDVICP2_SwiFunc, &swiParams, &eb);
        _HDVICP2_context[iresHandle->id].swiHandle =
            Swi_handle(&_HDVICP2_context[iresHandle->id].swiStruct);

        /* configure interrupt table with the ISR function */
        Hwi_Params_init(&hwiParams);
        hwiParams.arg = iresHandle->id;

        _HDVICP2_context[iresHandle->id].hwiHandle =
            Hwi_handle(&_HDVICP2_context[iresHandle->id].hwiStruct);

        /*--------------------------------------------------------------------*/
        /* Create the semaphore for indicating IVAHD-codec start/end.  */
        /* Create the semaphore with count = 0.  */
        /*--------------------------------------------------------------------*/

        _HDVICP2_context[iresHandle->id].semHandle =
            BspOsal_semCreate(0, FALSE);

    }

    return;
}

/** ========================================================================== */
/**
* HDVICP_Wait(handle, iresHandle, yieldCtxt) :
* Pends for the semaphore that is posted by "done"
*
* @param handle        Algorithm Handle
* @param iresHandle    IRES Handle
* @param yieldCtxt     <TBD>
*
* @return           None
*/
/** ========================================================================== */
XDAS_UInt32 HDVICP_Wait(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle,
                        IRES_YieldContext * yieldCtxt)
{

    DBC_require(iresHandle);
#ifdef UTILS_ENCDEC_HDVICP_PROFILE
    {
        UInt32 curTime = Utils_encdecGetTime();

        g_HDVICP_logTbl[iresHandle->id].totalAcquire2wait +=
            (curTime - g_HDVICP_logTbl[iresHandle->id].tempAcquireTime);
        g_HDVICP_logTbl[iresHandle->id].tempWaitTime = curTime;
    }
#endif
    /* pend for the semaphore ie. block on the semaphore */
    _HDVICP2_context[iresHandle->id].inIVAHDprocess = TRUE;
    BspOsal_semWait(_HDVICP2_context[iresHandle->id].semHandle,
                   BSP_OSAL_WAIT_FOREVER);

	_HDVICP2_context[iresHandle->id].inIVAHDprocess = FALSE;
    DBC_ensure(success);

    return (XDAS_TRUE);
}

/** ========================================================================== */
/**
* HDVICP_Done(handle, iresHandle) :
* This function will be called by the interrupt handler
* function when it detects an end-of-frame processing
*
* @param handle        Algorithm Handle
* @param iresHandle    IRES Handle
*
* @return           None
*/
/** ========================================================================== */

void HDVICP_Done(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
    DBC_require(iresHandle);
#ifdef UTILS_ENCDEC_HDVICP_PROFILE
    {
        UInt32 curTime = Utils_encdecGetTime();

        g_HDVICP_logTbl[iresHandle->id].totalIsr2Done +=
            (curTime - g_HDVICP_logTbl[iresHandle->id].tempPrevTime);
        g_HDVICP_logTbl[iresHandle->id].totalWait2Done +=
            (curTime - g_HDVICP_logTbl[iresHandle->id].tempWaitTime);
        g_HDVICP_logTbl[iresHandle->id].tempPrevTime = curTime;
    }
#endif
    BspOsal_semPost(_HDVICP2_context[iresHandle->id].semHandle);
}

XDAS_Int32 IVAHD_Standby_power_on_uboot(IRES_HDVICP2_Handle iresHandle)
{

    unsigned int length = 0;

    /*------------------------------------------------------------------------*/
    /* Assigment of pointers */
    /* A generic code shall take all address as input parameters */
    /*------------------------------------------------------------------------*/
    volatile unsigned int *prcm_ivahd_icont_rst_cntl_addr =
        (unsigned int *) iresHandle->resetControlAddress;
    volatile unsigned int *icont1_itcm_base_addr =
        (unsigned int *) ((unsigned long) (iresHandle->registerBaseAddress) +
                          ICONT1_ITCM_OFFSET);
    volatile unsigned int *icont2_itcm_base_addr =
        (unsigned int *) ((unsigned long) (iresHandle->registerBaseAddress) +
                          ICONT2_ITCM_OFFSET);
    /**-----------------------------------------------------------------------*
     * Set IVAHD in reset mode to enable downloading of boot code             *
     * Please note that this state can be SKIPPED if IVAHD is alredy in reset *
     * state during uboot and reset is not de-asserted                        *
     * Set bit0 to 1 to put ICONT1 in reset state                             *
     * Set bit1 to 1 to put ICONT2 in reset state                             *
     *------------------------------------------------------------------------*/
    *prcm_ivahd_icont_rst_cntl_addr |= 0x00000003;

    /*------------------------------------------------------------------------*/
    /* Copy boot code to ICONT1 & INCOT2 memory */
    /*------------------------------------------------------------------------*/
    for (length = 0; length < LENGTH_BOOT_CODE; length++)
    {
        *icont1_itcm_base_addr++ = IVAHD_memory_wfi[length];
        *icont2_itcm_base_addr++ = IVAHD_memory_wfi[length];
    }
    /*------------------------------------------------------------------------*/
    /* Take IVAHD out of reset mode.  */
    /* Set bit0 to 0 to take ICONT1 out of reset state */
    /* Set bit1 to 0 to take ICONT1 out of reset state */
    /* This implies ICONT inside IVAHD will exectute WFI */
    /*------------------------------------------------------------------------*/
    *prcm_ivahd_icont_rst_cntl_addr &= 0xFFFFFFFC;

    /*------------------------------------------------------------------------*/
    /* As ICONT goes in WFI and there are no pending VDMA transction */
    /* entire IVAHD will be go in standby mode and PRCM will fully control */
    /* further managment of IVAHD power state */
    /*------------------------------------------------------------------------*/

    return (1);
}

/**
*  SL2 Base Address, Register's Base Address & PRCM Base Address Set
*  Based on Host Type Used
*/
#define IVAHD_HOST_REG_BASE     (0x5A000000)
#define IVAHD_HOST_SL2_BASE     (0x5B000000)
#define PRCM_BASE_ADDR          (0x4AE06F00)

#define WR_MEM_32(addr, data) *(volatile unsigned int*)(addr) =(unsigned int)(data)
#define RD_MEM_32(addr) *(volatile unsigned int*)(addr)

Int g_TurnOnPowerDomainForIVA_done = FALSE;

void TurnOnPowerDomainForIVA(void)
{
  /* PM_IVAHDx_PWRSTCTRL.POWERSTATE = 0x3; */
  //WR_MEM_32(PRM_IVAHD0 , 3);

  Hwi_setFunc(ti_sdo_fc_ires_hdvicp_HDVICP2_hwi0, IRESMAN_HDVICP2_ISR, 0);
}

#if 0

UInt   RESET_COUNT[3];

XDAS_UInt32 HDVICP_Reset(IALG_Handle handle, IRES_HDVICP2_Handle iresHandle)
{
    IArg key;
    static Bool reset_done[3] = {FALSE,FALSE,FALSE};
    volatile unsigned int temp;
    unsigned int RM_IVAHD0_RSTCTRL =
       (unsigned int)iresHandle->resetControlAddress; //(PRCM_BASE_ADDR + 0x10)
    unsigned int RM_IVAHD0_RSTST =
       (RM_IVAHD0_RSTCTRL + 4); //(PRM_IVAHD0 + 0x14)
    unsigned int CM_IVAHD0_IVAHD_CLKCTRL =
       ((RM_IVAHD0_RSTCTRL - 0xDFE010 ) + 0x20); //(PRCM_BASE_ADDR + 0x0620)
    unsigned int CM_IVAHD0_SL2_CLKCTRL =
       (CM_IVAHD0_IVAHD_CLKCTRL + 8); //(PRCM_BASE_ADDR + 0x0624)

    key= Gate_enterSystem ();
    RESET_COUNT[iresHandle->id]++;

    if (FALSE == reset_done[iresHandle->id]) {
        IVAHD_Standby_power_on_uboot(iresHandle);
        reset_done[iresHandle->id] = TRUE;
    }

    if (FALSE == g_TurnOnPowerDomainForIVA_done){
        TurnOnPowerDomainForIVA();
        g_TurnOnPowerDomainForIVA_done = TRUE;
    }

    /* CM_IVAHD0_IVAHD_CLKCTRL. MODULEMODE = 0x0;
    while(CM_IVAHD0_IVAHD_CLKCTRL.IDLEST != 0x3); */
    WR_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL, 0);
    do {
        temp = RD_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL);
        temp = ((temp >> 16) & 3);
    } while (temp != 3);

    /* CM_IVAHD0_SL2_CLKCTRL. MODULEMODE = 0x0;
       while(CM_IVAHD0_SL2_CLKCTRL.IDLEST != 0x3); */
    WR_MEM_32(CM_IVAHD0_SL2_CLKCTRL, 0);
    do {
        temp = RD_MEM_32(CM_IVAHD0_SL2_CLKCTRL);
        temp = ((temp >> 16) & 3);
    } while (temp != 3);

    /* RM_IVAHD0_RSTST     = IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x7 :
       RM_IVAHD0_RSTCTRL = IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x7 */
    WR_MEM_32(RM_IVAHD0_RSTST, 7);
    WR_MEM_32(RM_IVAHD0_RSTCTRL, 7);

    /* CM_IVAHD0_SL2_CLKCTRL. MODULEMODE = 0x2;
       CM_IVAHD0_IVAHD_CLKCTRL. MODULEMODE = 0x2; */
    WR_MEM_32(CM_IVAHD0_SL2_CLKCTRL , 2);
    WR_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL , 2);

    /* RM_IVAHD0_RSTCTRL = !IVA_RST3 | IVA_RST2 | IVA_RST1; : 0x3 */
    WR_MEM_32(RM_IVAHD0_RSTCTRL , 3);

    /* Wait for !IDLE
    while(CM_IVAHD0_IVAHD_CLKCTRL.IDLEST != 0x0);
    while(CM_IVAHD0_SL2_CLKCTRL.IDLEST != 0x0); */
    do {
        temp = RD_MEM_32(CM_IVAHD0_IVAHD_CLKCTRL);
        temp = ((temp >> 16) & 3);
    } while (temp != 0);

    do {
        temp = RD_MEM_32(CM_IVAHD0_SL2_CLKCTRL);
        temp = ((temp >> 16) & 3);
    } while (temp != 0);

    /* while(RM_IVAHD0_RSTST.IVA_RST3 != 0x1); */
    do {
        temp = RD_MEM_32(RM_IVAHD0_RSTST);
        temp = ((temp >> 2) & 1);
    } while (temp != 1);

    Gate_leaveSystem(key);
    return (XDAS_TRUE);
}

#else

#define NULL_VALUE ((void *)0x0)

XDAS_UInt32 HDVICP_Reset(
    IALG_Handle algHandle,
struct IRES_HDVICP2_Obj * iresHandle)
{
    volatile unsigned int * resetControlRegister = NULL;
    volatile unsigned int * resetControlStatusRegister = NULL;
    volatile unsigned int * ivahdClockControlRegister = NULL;
    volatile unsigned int * ivahdClockControlStatusRegister = NULL;
    volatile unsigned int * sl2ClockControlRegister = NULL;
    volatile int debugCounter1=0,debugCounter2=0;
    Hwi_Handle hIVAIntHwiHandle = NULL_VALUE;

    hIVAIntHwiHandle = (Hwi_Handle) Hwi_getHandle(IVAHD_INTRPT_ID);
    Hwi_setFunc(hIVAIntHwiHandle, IRESMAN_HDVICP2_ISR, 0);

    /*Reset IVA HD,SL2 and ICONTs */
    /* Vayu IVA_PRM at address 0x4AE06f00 and IVA_CM_CORE 0x4A008f00 */
    /* Refer http://www-open.india.ti.com/~eda/SysArch/metadata/ic/vayu/HTML/IPU/IVA_CM_CORE.html */
    /* http://www-open.india.ti.com/~eda/SysArch/metadata/ic/vayu/HTML/IPU/IVA_PRM.html */
    resetControlRegister             =
        (volatile unsigned int *)(iresHandle->resetControlAddress);
    resetControlStatusRegister       =
        (volatile unsigned int *)(((unsigned int)resetControlRegister) + 4);
    ivahdClockControlStatusRegister  =
        (volatile unsigned int *)(((unsigned int)resetControlRegister) - 0xDFE010);
    ivahdClockControlRegister        =
        (volatile unsigned int *)(((unsigned int)ivahdClockControlStatusRegister)
        + 0x20);
    sl2ClockControlRegister          =
        (volatile unsigned int *)(((unsigned int)ivahdClockControlStatusRegister)
        + 0x28);

    /* First put IVA into HW Auto mode */
    *ivahdClockControlStatusRegister |= 0x3;

    /* Wait for IVA HD to  standby */
    while (!((*ivahdClockControlRegister) & 0x40000))
    {
        ;
    }
    /*Disable IVAHD and SL2 modules*/
    *ivahdClockControlRegister = 0;
    *sl2ClockControlRegister = 0;
    /*Ensure that IVAHD and SL2 are disabled*/
    do {
        if((*ivahdClockControlRegister) & 0x00030000) {
            break;
        }
    } while (1);

    do {
        if((*sl2ClockControlRegister) & 0x00030000) {
            break;
        }
    } while (1);
    /*Reset IVAHD sequencers and SL2*/
    *resetControlRegister |= 7;

    /*Check if modules are reset*/

    /*First clear the status bits*/
    *resetControlStatusRegister |= 7;

    /*Wait for confirmation that the systems have been reset.                 */
    /*THIS CHECK MAY NOT BE NECESSARY, AND MOST OF ALL GIVEN OUR STATE,       */
    /*MAY NOT BE POSSIBLE                                                     */

    /* Ensure that the wake up mode is set to SW_WAKEUP */
    *ivahdClockControlStatusRegister &= 0x2;

    /*Enable IVAHD and SL2 modules*/
    *ivahdClockControlRegister = 1;
    *sl2ClockControlRegister = 1;

    /*Deassert the SL2 reset*/
    *resetControlRegister &= 0xFFFFFFFB;

    /*Ensure that IVAHD and SL2 are enabled*/
    do
    {
        if(!((*ivahdClockControlRegister) & 0x00030000))
        {
            break;
        }
        /* Just to check the number of iterations taken for the modules to get*/
        /* enabled                                                            */
        debugCounter1++;
    } while (1);

    do
    {
        if(!((*sl2ClockControlRegister) & 0x00030000))
        {
            break;
        }
        /* Just to check the number of iterations taken for the modules to get*/
        /* enabled                                                            */
        debugCounter2++;
    } while (1);

    return (XDAS_TRUE);
}

#endif


/* Nothing beyond this point */



