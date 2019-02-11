/*
 * sample_tci6636k2h_int_reg.c
 *
 * Platform specific interrupt registration and un-registration routines.
 *
 * Copyright (C) 2012-2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/family/arm/a15/tci66xx/CpIntc.h>
#include <ti/sysbios/family/arm/a15/Mmu.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

extern unsigned int ccXferCompInt[][EDMA3_MAX_REGIONS];
extern unsigned int ccErrorInt[];
extern unsigned int tcErrorInt[][EDMA3_MAX_TC];
extern unsigned int numEdma3Tc[];

void (*ptrEdma3TcIsrHandler[EDMA3_MAX_TC])(uint32_t arg) =
                                                {
                                                &lisrEdma3TC0ErrHandler0,
                                                &lisrEdma3TC1ErrHandler0,
                                                &lisrEdma3TC2ErrHandler0,
                                                &lisrEdma3TC3ErrHandler0,
                                                &lisrEdma3TC4ErrHandler0,
                                                &lisrEdma3TC5ErrHandler0,
                                                &lisrEdma3TC6ErrHandler0,
                                                &lisrEdma3TC7ErrHandler0,
                                                };

/* This variable has to be used as an extern */
uint32_t gpp_num = 0;

Hwi_Handle hwiCCXferCompInt;
Hwi_Handle hwiCCErrInt;
Hwi_Handle hwiTCErrInt[EDMA3_MAX_TC];

/* Mapped CIC2 output interrupt number for EDMA3 CC Err interrupt */
uint32_t edma3ccErrorHostInt[5] = {29u, 30u, 31u, 32u, 33u};

/* Mapped CIC2 output interrupt number for EDMA3 TC Err interrupt */
uint32_t edma3tcErrorHostInt[5][EDMA3_MAX_TC] = {
    {34u, 35u, 0u, 0u, 0u, 0u, 0u, 0u},
    {36u, 37u, 38u, 39u, 0u, 0u, 0u, 0u},
    {40u, 41u, 42u, 43u, 0u, 0u, 0u, 0u},
    {44u, 45u, 0u, 0u, 0u, 0u, 0u, 0u},
    {46u, 47u, 0u, 0u, 0u, 0u, 0u, 0u},
};

/**  To Register the ISRs with the underlying OS, if required */
void registerEdma3Interrupts (uint32_t edma3Id)
{
    static UInt32 cookie = 0;
    uint32_t numTc = 0;

    Hwi_Params hwiParams;
    Error_Block eb;

    int32_t intNum;

    /* EDMA3 CC transfer complete interrupt */

    /* Initialize the Error Block                                             */
    Error_init(&eb);

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    /* Initialize the HWI parameters with user specified values */
    Hwi_Params_init(&hwiParams);

    /* argument for the ISR */
    hwiParams.arg = edma3Id;

    hwiCCXferCompInt = Hwi_create(ccXferCompInt[edma3Id][gpp_num],
                			((Hwi_FuncPtr)&lisrEdma3ComplHandler0),
                			(const Hwi_Params *) (&hwiParams),
                			&eb);
    if ((bool)TRUE == Error_check(&eb))
    {
        System_printf("ccXfercompInt HWI Create Failed\n", Error_getCode(&eb));
    }

    /* EDMA3 CC error interrupt */
    Error_init(&eb);

    /* Map system interrupt to Host interrupt */
    CpIntc_mapSysIntToHostInt(ccErrorInt[edma3Id],
								edma3ccErrorHostInt[edma3Id]);

    /* Plug the function and argument for System interrupt then enable it */
    CpIntc_dispatchPlug(ccErrorInt[edma3Id],
						(CpIntc_FuncPtr)(lisrEdma3CCErrHandler0),
						edma3Id,
						TRUE);

    /* Enable Host interrupt */
    CpIntc_enableHostInt(edma3ccErrorHostInt[edma3Id]);

    /* Get the ARM Hwi interrupt number associated with Host interrupt */
    intNum = CpIntc_getIntNum(edma3ccErrorHostInt[edma3Id]);

    /* Initialize the Hwi parameters */
    Hwi_Params_init(&hwiParams);
    hwiParams.arg = (uint32_t)CpIntc_getHostIntKey(edma3ccErrorHostInt[edma3Id]);
    hwiParams.enableInt = TRUE;
    Hwi_create(intNum, &CpIntc_dispatch, &hwiParams, &eb);

    if ((bool)TRUE == Error_check(&eb))
    {
        System_printf("ccErrorInt HWI Create Failed\n",Error_getCode(&eb));
    }

    /* TC Error ISR */
    while (numTc < numEdma3Tc[edma3Id])
    {
        Error_init(&eb);

        CpIntc_mapSysIntToHostInt(tcErrorInt[edma3Id][numTc],
								edma3tcErrorHostInt[edma3Id][numTc]);
        CpIntc_dispatchPlug(tcErrorInt[edma3Id][numTc],
						(CpIntc_FuncPtr)(ptrEdma3TcIsrHandler[numTc]),
						edma3Id,
						TRUE);
        CpIntc_enableHostInt(edma3tcErrorHostInt[edma3Id][numTc]);
        intNum = CpIntc_getIntNum(edma3tcErrorHostInt[edma3Id][numTc]);

        Hwi_Params_init(&hwiParams);
        hwiParams.arg = (uint32_t)CpIntc_getHostIntKey(edma3tcErrorHostInt[edma3Id][numTc]);
        hwiParams.enableInt = TRUE;
        hwiTCErrInt[numTc] = Hwi_create(intNum, &CpIntc_dispatch, &hwiParams, &eb);

        if ((bool)TRUE == Error_check(&eb))
        {
            System_printf("tcErrorInt HWI Create Failed\n",Error_getCode(&eb));
        }

        numTc++;
    }

    /* Restore interrupts */
    Hwi_restore(cookie);
}

/**  To Unregister the ISRs with the underlying OS, if previously registered. */
void unregisterEdma3Interrupts (unsigned int edma3Id)
{
    static UInt32 cookie = 0;
    uint32_t numTc = 0;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    Hwi_delete(&hwiCCXferCompInt);

    CpIntc_disableHostInt(edma3ccErrorHostInt[edma3Id]);
    Hwi_delete(&hwiCCErrInt);

    while (numTc < numEdma3Tc[edma3Id])
    {
        CpIntc_disableHostInt(edma3tcErrorHostInt[edma3Id][numTc]);
        Hwi_delete(&hwiTCErrInt[numTc]);
        numTc++;
    }

    /* Restore interrupts */
    Hwi_restore(cookie);
}

