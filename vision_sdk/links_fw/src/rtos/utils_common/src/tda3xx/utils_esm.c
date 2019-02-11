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
 * \file utils_esm.c
 *
 * \brief Utility functions for using ESM on TDA3x.
 *
 * \version 0.0 (Jan 2016) : [CSG] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <xdc/std.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_esm.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/drv/pm/pmhal.h>
#include "utils_common/include/utils_esm.h"
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ESM_IPU_INTR_ID             (68U)
#define ESM_MAX_EVENTS_SUPPORTED    (10U)

static Void Utils_esmISR(UArg ctx);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* Interrupt handles */
static BspOsal_IntrHandle   gEsmHwiHandle = NULL;
static UInt32               argArray[ESM_MAX_EVENTS_SUPPORTED] = {0};
static BspOsal_IntrFuncPtr  fxnArray[ESM_MAX_EVENTS_SUPPORTED] = {0};
static UInt32               evtArray[ESM_MAX_EVENTS_SUPPORTED] = {0};


/* ========================================================================== */
/*                         Function definitions                               */
/* ========================================================================== */

static Void Utils_esmISR(UArg ctx)
{
    UInt32 i;
    UInt32 status;
    BspOsal_IntrFuncPtr fxnPtr;
    for(i = 0; i < ESM_MAX_EVENTS_SUPPORTED; i++)
    {
        if(NULL != fxnArray[i])
        {
            status = ESMGetIntrStatus(SOC_ESM_BASE, evtArray[i]);
            if(0U != status)
            {
                Vps_printf(" ESM-UTILS: Event %d occurred!!\n", evtArray[i]);
                fxnPtr = fxnArray[i];
                fxnPtr(argArray[i]);
            }
            ESMClearIntrStatus(SOC_ESM_BASE, evtArray[i]);
        }
    }
}

BspOsal_IntrHandle System_esmRegisterEvent(UInt32 eventId,
                                           BspOsal_IntrFuncPtr func,
                                           const Void *arg0)
{
    UInt32 i;
    UTILS_assert(NULL != func);
    for(i = 0; i < ESM_MAX_EVENTS_SUPPORTED; i++)
    {
        /* MISRA.CAST.Func.Ptr
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
         */
        if(NULL == fxnArray[i])
        {
            fxnArray[i] = func;
            argArray[i] = (UInt32)arg0;
            evtArray[i] = eventId;
            ESMEnableIntr(SOC_ESM_BASE, eventId);
            ESMSetIntrPriorityLvl(
                SOC_ESM_BASE, eventId, ESM_INTR_PRIORITY_LEVEL_HIGH);
            break;
        }
    }

    if(ESM_MAX_EVENTS_SUPPORTED == i)
    {
        i = 0;
        Vps_printf(" ESM-UTILS: Exceeded max supported events!!\n");
    }
    else
    {
        i = i + 1U;
    }

    /* MISRA.CAST.Func.Ptr
     * MISRAC_2004_Rule_11.1
     * MISRAC_WAIVER:
     * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
     */
    return (BspOsal_IntrHandle)i;
}

void System_esmUnRegisterEvent(const BspOsal_IntrHandle *pIntrHandle)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule_11.3
     * MISRAC_WAIVER:
     * Passing pointer arguments to ISR and callback functions which
     * takes arguments as UInt32 for legacy reasons and vice-versa.
     */
    i = *(UInt32 const*)pIntrHandle;
    /* Handles can take values from 1 to ESM_MAX_EVENTS_SUPPORTED */
    if((i == 0) ||
       (i > ESM_MAX_EVENTS_SUPPORTED))
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if(SYSTEM_LINK_STATUS_SOK == status)
    {
        i = i - 1U;
        if(NULL == fxnArray[i])
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if(SYSTEM_LINK_STATUS_SOK == status)
    {
        ESMDisableIntr(SOC_ESM_BASE, evtArray[i]);
        fxnArray[i] = NULL;
        argArray[i] = NULL;
        evtArray[i] = 0;
    }
    else
    {
        Vps_printf(" ESM-UTILS: Exceeded max supported events!!\n");
    }
}

void System_esmInit(void)
{
    Int32 status;
    status = PMHALModuleModeSet(PMHAL_PRCM_MOD_ESM,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    UTILS_assert(0 == status);

    if(NULL == gEsmHwiHandle)
    {
       /* MISRA.CAST.Func.Ptr
        * MISRAC_2004_Rule_11.1
        * MISRAC_WAIVER:
        * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
        */
        /* Enable interrupt in XBAR and register ISR */
        IntXbar_connectIRQ(ESM_IPU_INTR_ID, ESM_IRQ_HIGH);
        gEsmHwiHandle =
            BspOsal_registerIntr(ESM_IPU_INTR_ID,
                                 (BspOsal_IntrFuncPtr) &Utils_esmISR,
                                 NULL);

        ESMSetMode(SOC_ESM_BASE, ESM_OPERATION_MODE_NORMAL);
    }
}

void System_esmDeInit(void)
{
    if(NULL != gEsmHwiHandle)
    {
        /* Enable interrupt in XBAR and register ISR */
        IntXbar_disconnectIRQ(ESM_IPU_INTR_ID);
        /* De-register ISRs */
        BspOsal_unRegisterIntr(&gEsmHwiHandle);
        gEsmHwiHandle = NULL;
    }
}
