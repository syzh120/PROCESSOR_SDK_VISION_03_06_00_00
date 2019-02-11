/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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

#include <xdc/std.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/hdvicp/hdvicp2.h>

#include <xdc/runtime/knl/SemThread.h>
#include <xdc/runtime/knl/ISemaphore.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/heaps/HeapMem.h>


/* Params specific to HDVICP2 module */
__FAR__ HDVICP2_Params HDVICP2_PARAMS = {
    NULL,
    NULL,
    NULL,
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    },
   /* resetControlAddress[HDVICP2_MAXRESOURCES] */
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    },
    /* registerBaseAddress[HDVICP2_MAXRESOURCES] */
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    },
    NULL
};


__FAR__ Int HDVICP2_MAXRESOURCES = 10;

/* Timeout value set by the framework */
__FAR__ unsigned int ti_sdo_fc_ires_hdvicp_HDVICP2_timeoutVal =
        IRES_HDVICP2_TIMEOUTFOREVER;

/* Number of HDVICP2 resources to be managed */
__FAR__ unsigned int _HDVICP2_NUMRESOURCES = (unsigned int)0;

/* Base key value for HDVICP Linux IPC objects */
__FAR__ UInt32 _HDVICP2_ipcKeyBase = 0x32564448;

/* Flag that says whether to clear the PRCM register during reset, or not */
__FAR__ XDAS_UInt32 ti_sdo_fc_ires_hdvicp_HDVICP2_clearPRCMRegister = FALSE;

/* Function to be used to obtain yield arguments for a particular scratch grp*/
ti_sdo_fc_ires_hdvicp_HDVICP2_GetYieldArgsFxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_getYieldArgs = DSKT2_getYieldArgs;

ti_sdo_fc_ires_hdvicp_HDVICP2_YieldFxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_yieldRelease = DSKT2_contextRelease;

ti_sdo_fc_ires_hdvicp_HDVICP2_YieldFxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_yieldAcquire = DSKT2_contextAcquire;

ti_sdo_fc_ires_hdvicp_HDVICP2_GetHdvicp2Fxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_getHdvicp2Fxn = NULL;

ti_sdo_fc_ires_hdvicp_HDVICP2_FreeHdvicp2Fxn
        ti_sdo_fc_ires_hdvicp_HDVICP2_freeHdvicp2Fxn = NULL;

/* BIOS support */

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>

/* Array of callback functions */
__FAR__ IRES_HDVICP2_CallbackFxn
    ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackFxn[] = {
        NULL,
        NULL,
        NULL
};

/* Array of IALG_Handles callback */
__FAR__ IALG_Handle ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackAlg[] = {
    NULL,
    NULL,
    NULL
};

/* Array of Callback arguments */
__FAR__ Void * ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackArgs[]  = {
    NULL,
    NULL,
    NULL
};

/* Declaration of Hwi, Swi and Semaphore Handles */
__FAR__ ti_sysbios_hal_Hwi_Handle
    ti_sdo_fc_ires_hdvicp_HDVICP2_hwi[] = {
        NULL,
        NULL,
        NULL
    };

__FAR__ ti_sysbios_knl_Swi_Handle
    ti_sdo_fc_ires_hdvicp_HDVICP2_swi[] = {
        NULL,
        NULL,
        NULL
    };

__FAR__ UInt ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[] = {
    0,  /* hdvicp0 */
    0,  /* hdvicp1 */
    0,   /* hdvicp2 */
};

/* Array of Sempahore handles */
__FAR__ xdc_runtime_knl_ISemaphore_Handle
        ti_sdo_fc_ires_hdvicp_HDVICP2_semArray[] = {
        NULL,
        NULL,
        NULL
};

void ti_sdo_fc_ires_hdvicp_HDVICP2_hwiFunc(UArg arg)
{
    if (arg < _HDVICP2_NUMRESOURCES) {

        /* Disable interrupt */
        ti_sysbios_hal_Hwi_disableInterrupt((UInt)
                (ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[arg]));

        /* Post swi */
        ti_sysbios_knl_Swi_post(ti_sdo_fc_ires_hdvicp_HDVICP2_swi[arg]);
    }
}


/* Function to plug into SWI */
void ti_sdo_fc_ires_hdvicp_HDVICP2_swiFunc(UArg arg1, UArg arg2) {

    /* Use the args to call some cbFunction */
    if (ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackFxn[arg1] != NULL) {
        (ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackFxn[arg1])
                (ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackAlg[arg1],
                ti_sdo_fc_ires_hdvicp_HDVICP2_CallBackArgs[arg1]);
    }

    ti_sysbios_hal_Hwi_clearInterrupt((UInt)
            ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[arg1]);
    ti_sysbios_hal_Hwi_enableInterrupt((UInt)
            ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[arg1]);
}

Bool ti_sdo_fc_ires_hdvicp_HDVICP2_semInit()
{
    ISemaphore_Handle handle = NULL;
    SemThread_Handle  sem;
    Hwi_Handle        hwi;
    Swi_Handle        swi;
    Swi_Params        swiParams;
    Hwi_Params        hwiParams;
    char *     hwiName = "ti_sdo_fc_ires_hdvicp_HDVICP2_hwi";
    char *     swiName = "ti_sdo_fc_ires_hdvicp_HDVICP2_swi";
    Int               i;

    for (i = 0; i < _HDVICP2_NUMRESOURCES; i++) {
        /* Create an Swi object */
        Swi_Params_init(&swiParams);

        swiParams.arg0 = i;
        swiParams.arg1 = 0;
        swiParams.__iprms.name = swiName;

        swi = Swi_create(ti_sdo_fc_ires_hdvicp_HDVICP2_swiFunc, &swiParams,
                NULL);
        if (swi == NULL) {
            return (FALSE);
        }

        ti_sdo_fc_ires_hdvicp_HDVICP2_swi[i] = swi;

        Hwi_Params_init(&hwiParams);
        hwiParams.__iprms.name = hwiName;

        /* Create Hwi object */
        hwi = Hwi_create(ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[i],
                ti_sdo_fc_ires_hdvicp_HDVICP2_hwiFunc, NULL, NULL);
        if (hwi == NULL) {
            return (FALSE);
        }

        ti_sdo_fc_ires_hdvicp_HDVICP2_hwi[i] = hwi;

        /* Create a semaphore with count 0 */
        sem = SemThread_create(0, NULL, NULL);

        handle = xdc_runtime_knl_SemThread_Handle_upCast(sem);
        if (handle != NULL) {
            ti_sdo_fc_ires_hdvicp_HDVICP2_semArray[i] =  handle;
        }
        else {
            return (FALSE);
        }
    }

    return (TRUE);
}
