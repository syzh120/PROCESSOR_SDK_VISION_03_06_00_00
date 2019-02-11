/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *
 */
/*
 *  ======== iresman_hdvicp2_setup.c ========
 */

/* This difine must precede inclusion of any xdc header files */
#define Registry_CURDESC ti_sdo_fc_ires_hdvicp2_desc

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/knl/Semaphore.h>
#include <xdc/runtime/knl/ISemaphore.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Registry.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV
#include "ires_hdvicp2.h"
#include "hdvicp2.h"
#include "_hdvicp2.h"


/* Call to obtain yield arguments for a particular scratch group */
extern IRES_YieldArgs (* ti_sdo_fc_ires_hdvicp_HDVICP2_getYieldArgs)
        (Int scratchId);

/* Call to release group lock/context etc */
extern Void (* ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease)
        (IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt,
        IRES_YieldArgs args);

/* Call to re-acquire group lock/context etc */
extern Void (* ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire)
        (IRES_YieldResourceType resource, IRES_YieldContextHandle ctxt,
        IRES_YieldArgs args);


extern ISemaphore_Handle ti_sdo_fc_ires_hdvicp_HDVICP2_semArray[];

/*  extern Semaphore_Handle ti_sdo_fc_ires_hdvicp_HDVICP2_getSem(int index);*/

extern IRES_HDVICP2_CallbackFxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackFxn[];

extern IALG_Handle ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackAlg[];

extern Void * ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackArgs[];

extern Registry_Desc ti_sdo_fc_ires_hdvicp2_desc;

/* ========================================================================== */
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
/* ========================================================================== */

void ti_sdo_fc_ires_hdvicp_HDVICP2_configure(IALG_Handle algHandle,
        struct IRES_HDVICP2_Obj * iresHandle,
        IRES_HDVICP2_CallbackFxn cbFunctionPtr, Void * cbArgs)
{
    int index = iresHandle->id;

    Log_print4(Diags_ENTRY, "[+E] ti_sdo_fc_ires_hdvicp_HDVICP2_configure> "
            "Enter (algHandle=0x%x, iresHandle=0x%x, cbFunctionPtr=0x%x, "
            "cbArgs=0x%x)\n", (IArg)algHandle, (IArg)iresHandle,
            (IArg)cbFunctionPtr, (IArg)cbArgs);

    ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackFxn[index] = cbFunctionPtr;
    ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackAlg[index] = algHandle;
    ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackArgs[index] = cbArgs;

    Log_print0(Diags_EXIT,
                "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_configure> Exit\n");

}

/* ========================================================================== */
/*
* HDVICP_Wait(handle, iresHandle, yieldCtxt) :
* Pends for the semaphore that is posted by "done"
*
* @param handle        Algorithm Handle
* @param iresHandle    IRES Handle
* @param yieldCtxt     <TBD>
*
* @return           None
*/
/* ========================================================================== */

Bool ti_sdo_fc_ires_hdvicp_HDVICP2_wait(IALG_Handle handle,
        IRES_HDVICP2_Handle iresHandle, IRES_YieldContext * yieldCtxt)
{
    Bool success;
    IRES_YieldArgs yieldArgs;
    unsigned int timeout = ti_sdo_fc_ires_hdvicp_HDVICP2_timeoutVal;

    Error_Block eb;

    Error_init(&eb);

    Log_print3(Diags_ENTRY, "[+E] ti_sdo_fc_ires_hdvicp_HDVICP2_wait> "
            "Enter (algHandle=0x%x, iresHandle=0x%x, yieldCtxt=0x%x)\n",
            (IArg)handle, (IArg)iresHandle, (IArg)yieldCtxt);


/* TODO: Need to release scratch group lock before pending */
    yieldArgs = ti_sdo_fc_ires_hdvicp_HDVICP2_getYieldArgs(
            ((IRES_HDVICP2_IntObj *)iresHandle)->scratchGroup);

    if (timeout == IRES_HDVICP2_TIMEOUTFOREVER) {
        timeout = Semaphore_FOREVER;
    }

    ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease(IRES_ALL, yieldCtxt, yieldArgs);

    /* pend for the semaphore ie. block on the semaphore */
    success = Semaphore_pend(ti_sdo_fc_ires_hdvicp_HDVICP2_semArray
            [iresHandle->id], timeout, &eb);

    if ((success != Semaphore_PendStatus_SUCCESS) || (Error_check(&eb))) {

        Log_print2(Diags_EXIT,
                "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_wait> Bad return from "
                "Semaphore_pend status=%d error block=0x%x\n", (Int)success,
                (unsigned int)(eb.msg));

        Log_print0(Diags_EXIT,
                "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_wait> Exit "
                "(status=FALSE)\n");

        return (FALSE);
    }

    ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire(IRES_ALL, yieldCtxt, yieldArgs);

    Log_print0(Diags_EXIT,
            "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_wait> Exit (status=TRUE)\n");

    return (TRUE);
}

/* ========================================================================== */
/*
* HDVICP_Done(handle, iresHandle) :
* This function will be called by the interrupt handler
* function when it detects an end-of-frame processing
*
* @param handle        Algorithm Handle
* @param iresHandle    IRES Handle
*
* @return           None
*/
/* ========================================================================== */

void ti_sdo_fc_ires_hdvicp_HDVICP2_done(IALG_Handle handle,
        IRES_HDVICP2_Handle iresHandle)
{
    Error_Block eb;

    Log_print2(Diags_ENTRY, "[+E] ti_sdo_fc_ires_hdvicp_HDVICP2_done> "
            "Enter (algHandle=0x%x, iresHandle=0x%x)\n",
            (IArg)handle, (IArg)iresHandle);

    Error_init(&eb);
    Semaphore_post(ti_sdo_fc_ires_hdvicp_HDVICP2_semArray[iresHandle->id],
            &eb);
    if (Error_check(&eb)) {
        Assert_isTrue(0, (Assert_Id)NULL);
    }

    Log_print0(Diags_EXIT,
                "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_done> Exit\n");
}

XDAS_UInt32 ti_sdo_fc_ires_hdvicp_HDVICP2_reset_Netra(IALG_Handle algHandle,
        IRES_HDVICP2_Handle iresHandle)
{
    volatile unsigned int *ivahd_reset_addr = NULL;
    volatile unsigned int *ivahd_reset_status_addr = NULL;
    volatile unsigned int *ivahd_ivahd_clkcntrl_addr = NULL;
    volatile unsigned int *ivahd_sl2_clkcntrl_addr = NULL;
    volatile unsigned int temp;

    Log_print2(Diags_ENTRY, "[+E] ti_sdo_fc_ires_hdvicp_HDVICP2_reset> "
            "Enter (algHandle=0x%x, iresHandle=0x%x)\n",
            (IArg)algHandle, (IArg)iresHandle);

    ivahd_reset_addr =  (unsigned int *)iresHandle->resetControlAddress;

    ivahd_reset_status_addr = (unsigned int *)ivahd_reset_addr + 1 ;

    ivahd_ivahd_clkcntrl_addr = (unsigned int *)((unsigned int)ivahd_reset_addr
             - 0x610 + 0x20);

    ivahd_sl2_clkcntrl_addr = (unsigned int *)((unsigned int)
            ivahd_ivahd_clkcntrl_addr + 4);


    *ivahd_ivahd_clkcntrl_addr = (unsigned int )0x0;

    do {
        temp = *ivahd_ivahd_clkcntrl_addr;
        temp = ((temp >> 16) & 3);
    } while (temp != 0x3);

    *ivahd_sl2_clkcntrl_addr = (unsigned int )0x0;

    do {
        temp = *ivahd_sl2_clkcntrl_addr;
        temp = ((temp >> 16) & 3);
    } while (temp != 0x3);

    *ivahd_reset_status_addr = (unsigned int)0x7;
    *ivahd_reset_addr = (unsigned int)0x7;

    *ivahd_sl2_clkcntrl_addr = (unsigned int )0x2;
    *ivahd_ivahd_clkcntrl_addr = (unsigned int )0x2;

    *ivahd_reset_addr = (unsigned int)0x3;

    do {
        temp = *ivahd_ivahd_clkcntrl_addr;
        temp = ((temp >> 16) & 3);
    } while (temp != 0x0);

    do {
        temp = *ivahd_sl2_clkcntrl_addr;
        temp = ((temp >> 16) & 3);
    } while (temp != 0x0);

    do {
        temp = *ivahd_reset_status_addr;
        temp = ((temp >> 2) & 1);
    } while (temp != 1);

#if 0
    *ivahd_reset_addr |=  0x00000007;

    if (ti_sdo_fc_ires_hdvicp_HDVICP2_clearPRCMRegister)
        *ivahd_reset_status_addr |= 0x7;


    while (waitCount--)  {

        if (*ivahd_reset_status_addr & 0x00000007) {
             *ivahd_reset_addr &=  0xFFFFFFFB;

            Log_print0(Diags_EXIT,
                    "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_reset> Exit "
                    "(status=XDAS_TRUE)\n");

            return (XDAS_TRUE);
        }

   }

    return (XDAS_FALSE);
#endif


    Log_print0(Diags_EXIT,
           "[+X] ti_sdo_fc_ires_hdvicp_HDVICP2_reset> Exit "
           "(status=XDAS_FALSE)\n");

    return (XDAS_TRUE);
}


XDAS_UInt32 ti_sdo_fc_ires_hdvicp_HDVICP2_reset_Omap(IALG_Handle algHandle,
        IRES_HDVICP2_Handle iresHandle)
{
    volatile unsigned int * ivahd_reset_addr = NULL;
    volatile unsigned int * ivahd_reset_status_addr = NULL;
    volatile unsigned int * ivahd_ivahd_clkcntrl_addr = NULL;
    volatile unsigned int * ivahd_ivahd_clkcntrl_status_addr = NULL;
    volatile unsigned int * ivahd_sl2_clkcntrl_addr = NULL;

        /*Reset IVA HD,SL2 and ICONTs */
    ivahd_reset_addr = (volatile unsigned int *)
            (iresHandle->resetControlAddress);

    ivahd_reset_status_addr = (volatile unsigned int *)
            (((unsigned int)ivahd_reset_addr) + 4);
    ivahd_ivahd_clkcntrl_status_addr  = (volatile unsigned int *)
            (((unsigned int)ivahd_reset_addr) - 0x2FE010);
    ivahd_ivahd_clkcntrl_addr = (volatile unsigned int *)(((unsigned int)
            ivahd_ivahd_clkcntrl_status_addr) + 0x20);
    ivahd_sl2_clkcntrl_addr = (volatile unsigned int *)(((unsigned int)
            ivahd_ivahd_clkcntrl_status_addr) + 0x28);

    /* First put IVA into HW Auto mode */
    *ivahd_ivahd_clkcntrl_status_addr |= 0x3;

   /* Wait for IVA HD to  standby */
    while (!((*ivahd_ivahd_clkcntrl_addr) & 0x40000));

    /*Disable IVAHD and SL2 modules*/
    *ivahd_ivahd_clkcntrl_addr = 0;
    *ivahd_sl2_clkcntrl_addr = 0;

    /*Ensure that IVAHD and SL2 are disabled*/
    do {
        if((*ivahd_ivahd_clkcntrl_addr) & 0x00030000) {
            break;
        }
    } while (1);

    do {
        if((*ivahd_sl2_clkcntrl_addr) & 0x00030000) {
            break;
        }
    } while (1);

    /*Reset IVAHD sequencers and SL2*/
    *ivahd_reset_addr |= 7;

    /*Check if modules are reset*/

    /*First clear the status bits*/
    *ivahd_reset_status_addr |= 7;

    /*Wait for confirmation that the systems have been reset*/
    /*THIS CHECK MAY NOT BE NECESSARY, AND MOST OF ALL GIVEN OUR STATE, MAY NOT
BE POSSIBLE*/

    /* Ensure that the wake up mode is set to SW_WAKEUP */
    *ivahd_ivahd_clkcntrl_status_addr &= 0x2;

    /*Enable IVAHD and SL2 modules*/
    *ivahd_ivahd_clkcntrl_addr = 1;
    *ivahd_sl2_clkcntrl_addr = 1;

    /*Deassert the SL2 reset*/
    *ivahd_reset_addr &= 0xFFFFFFFB;

   /*Ensure that IVAHD and SL2 are enabled*/
    do {
        if(!((*ivahd_ivahd_clkcntrl_addr) & 0x00030000)) {
            break;
        }
    } while (1);

    do {
        if(!((*ivahd_sl2_clkcntrl_addr) & 0x00030000)) {
            break;
        }
    } while (1);

    return (XDAS_TRUE);
}
