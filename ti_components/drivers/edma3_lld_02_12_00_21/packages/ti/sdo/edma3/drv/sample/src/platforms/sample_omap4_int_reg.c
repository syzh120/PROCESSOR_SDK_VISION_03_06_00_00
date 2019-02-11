/*
 * sample_da830_int_reg.c
 *
 * Platform specific interrupt registration and un-registration routines.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
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
#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/family/c64p/Hwi.h>

#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

// #include <stdio.h>
/**
  * EDMA3 TC ISRs which need to be registered with the underlying OS by the user
  * (Not all TC error ISRs need to be registered, register only for the
  * available Transfer Controllers).
  */
void (*ptrEdma3TcIsrHandler[EDMA3_MAX_TC])(unsigned int arg) =
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

extern unsigned int ccXferCompInt[][EDMA3_MAX_REGIONS];
extern unsigned int ccErrorInt[];
extern unsigned int tcErrorInt[][EDMA3_MAX_TC];
extern unsigned int numEdma3Tc[];

/**
 * Variables which will be used internally for referring the hardware interrupt
 * for various EDMA3 interrupts.
 */
extern unsigned int hwIntXferComp;
extern unsigned int hwIntCcErr;
extern unsigned int hwIntTcErr;

extern unsigned int dsp_num;

/**  To Register the ISRs with the underlying OS, if required. */
void registerEdma3Interrupts (unsigned int edma3Id)
    {
    static UInt32 cookie = 0;
    unsigned int numTc = 0;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    /* Enable the Xfer Completion Event Interrupt */
    EventCombiner_dispatchPlug(ccXferCompInt[edma3Id][dsp_num],
    						(EventCombiner_FuncPtr)(&lisrEdma3ComplHandler0),
                        	NULL, 1);
    EventCombiner_enableEvent(ccXferCompInt[edma3Id][dsp_num]);

    /* Enable the CC Error Event Interrupt */
    EventCombiner_dispatchPlug(ccErrorInt[edma3Id],
    						(EventCombiner_FuncPtr)(&lisrEdma3CCErrHandler0),
    						NULL, 1);
    EventCombiner_enableEvent(ccErrorInt[edma3Id]);

    /* Enable the TC Error Event Interrupt, according to the number of TCs. */
    while (numTc < numEdma3Tc[edma3Id])
	    {
        EventCombiner_dispatchPlug(tcErrorInt[edma3Id][numTc],
                            (EventCombiner_FuncPtr)(ptrEdma3TcIsrHandler[numTc]),
                            NULL, 1);
        EventCombiner_enableEvent(tcErrorInt[edma3Id][numTc]);
        numTc++;
    	}

   /**
    * Enabling the HWI_ID.
    * EDMA3 interrupts (transfer completion, CC error etc.)
    * correspond to different ECM events (SoC specific). These ECM events come
    * under ECM block XXX (handling those specific ECM events). Normally, block
    * 0 handles events 4-31 (events 0-3 are reserved), block 1 handles events
    * 32-63 and so on. This ECM block XXX (or interrupt selection number XXX)
    * is mapped to a specific HWI_INT YYY in the tcf file. So to enable this
    * mapped HWI_INT YYY, one should use the corresponding bitmask in the
    * API C64_enableIER(), in which the YYY bit is SET.
    */
 	Hwi_enableInterrupt(hwIntXferComp);
 	Hwi_enableInterrupt(hwIntCcErr);
 	Hwi_enableInterrupt(hwIntTcErr);

    /* Restore interrupts */
    Hwi_restore(cookie);
    }

/**  To Unregister the ISRs with the underlying OS, if previously registered. */
void unregisterEdma3Interrupts (unsigned int edma3Id)
    {
	static UInt32 cookie = 0;
    unsigned int numTc = 0;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    /* Disable the Xfer Completion Event Interrupt */
	EventCombiner_disableEvent(ccXferCompInt[edma3Id][dsp_num]);

    /* Disable the CC Error Event Interrupt */
	EventCombiner_disableEvent(ccErrorInt[edma3Id]);

    /* Enable the TC Error Event Interrupt, according to the number of TCs. */
    while (numTc < numEdma3Tc[edma3Id])
    	{
        EventCombiner_disableEvent(tcErrorInt[edma3Id][numTc]);
        numTc++;
    	}

    /* Restore interrupts */
    Hwi_restore(cookie);
    }

