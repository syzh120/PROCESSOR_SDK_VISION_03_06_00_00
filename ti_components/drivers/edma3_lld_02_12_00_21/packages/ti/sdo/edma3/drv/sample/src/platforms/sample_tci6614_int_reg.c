/*
 * sample_tci6614_int_reg.c
 *
 * Platform specific interrupt registration and un-registration routines.
 *
 * Copyright (C) 2011-2017 Texas Instruments Incorporated - http://www.ti.com/
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
#include <ti/sysbios/family/c64p/Hwi.h>
#include <ti/sysbios/family/c64p/EventCombiner.h>
#include <ti/sysbios/family/c66/tci66xx/CpIntc.h>

#include <ti/sdo/edma3/rm/sample/bios6_edma3_rm_sample.h>

extern unsigned int ccXferCompInt[][EDMA3_MAX_REGIONS];
extern unsigned int ccErrorInt[];
extern unsigned int tcErrorInt[][EDMA3_MAX_TC];
extern unsigned int numEdma3Tc[];

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

unsigned int hwiInterrupt = 8;

/* Host interrupts for transfer completion */
//unsigned int ccXferHostInt[NUM_EDMA3_INSTANCES][NUM_DSPS] = {
unsigned int ccXferHostInt[3][4] = {
										{8u, 24u, 40u, 56u},
										{9u, 25u, 41u, 57u},
										{10u, 26u, 42u, 58u},
										};
unsigned int edma3ErrHostInt[3][4] = {
										{11u, 27u, 43u, 59u},
										{12u, 28u, 44u, 60u},
										{13u, 29u, 45u, 61u},
										};


extern unsigned int dsp_num;

/**  To Register the ISRs with the underlying OS, if required */
void registerEdma3Interrupts (unsigned int edma3Id)
    {
    static UInt32 cookie = 0;
    Int eventId = 0;	/* GEM event id */
	unsigned int numTc = 0;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

	/* Transfer completion ISR */
	CpIntc_dispatchPlug(ccXferCompInt[edma3Id][dsp_num],
						lisrEdma3ComplHandler0,
						edma3Id,
						TRUE);
	CpIntc_mapSysIntToHostInt(0, ccXferCompInt[edma3Id][dsp_num],
								ccXferHostInt[edma3Id][dsp_num]);
	CpIntc_enableHostInt(0, ccXferHostInt[edma3Id][dsp_num]);
    eventId = CpIntc_getEventId(ccXferHostInt[edma3Id][dsp_num]);
    EventCombiner_dispatchPlug (eventId, CpIntc_dispatch,
                                ccXferHostInt[edma3Id][dsp_num], TRUE);
	EventCombiner_enableEvent(eventId);

	/* CC Error ISR */
	CpIntc_dispatchPlug(ccErrorInt[edma3Id], lisrEdma3CCErrHandler0,
						edma3Id, TRUE);
	CpIntc_mapSysIntToHostInt(0, ccErrorInt[edma3Id],
								edma3ErrHostInt[edma3Id][dsp_num]);
	/* TC Error ISR */
    while (numTc < numEdma3Tc[edma3Id])
	    {
		CpIntc_dispatchPlug(tcErrorInt[edma3Id][numTc],
							(CpIntc_FuncPtr )(ptrEdma3TcIsrHandler[numTc]),
							edma3Id, TRUE);
		CpIntc_mapSysIntToHostInt(0, tcErrorInt[edma3Id][numTc],
									edma3ErrHostInt[edma3Id][dsp_num]);
        numTc++;
    	}
	/* Enable the host interrupt which is common for both CC and TC error */
	CpIntc_enableHostInt(0, edma3ErrHostInt[edma3Id][dsp_num]);
    eventId = CpIntc_getEventId(edma3ErrHostInt[edma3Id][dsp_num]);
    EventCombiner_dispatchPlug (eventId, CpIntc_dispatch,
                                edma3ErrHostInt[edma3Id][dsp_num], TRUE);
	EventCombiner_enableEvent(eventId);

    Hwi_enableInterrupt(hwiInterrupt);

    /* enable the 'global' switch */
    CpIntc_enableAllHostInts(0);

    /* Restore interrupts */
    Hwi_restore(cookie);
    }

/**  To Unregister the ISRs with the underlying OS, if previously registered. */
void unregisterEdma3Interrupts (unsigned int edma3Id)
    {
    static UInt32 cookie = 0;
    Int eventId = 0;	/* GEM event id */

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

	/* Transfer completion ISR */
	CpIntc_disableHostInt(0, ccXferHostInt[edma3Id][dsp_num]);
    eventId = CpIntc_getEventId(ccXferHostInt[edma3Id][dsp_num]);
	EventCombiner_disableEvent(eventId);

	/* CC/TC Error ISR */
	CpIntc_disableHostInt(0, edma3ErrHostInt[edma3Id][dsp_num]);
    eventId = CpIntc_getEventId(edma3ErrHostInt[edma3Id][dsp_num]);
	EventCombiner_disableEvent(eventId);

    /* Restore interrupts */
    Hwi_restore(cookie);
    }

/**
 * \brief   enableXferCompInterrupt
 *
 * This function enables the tranfer completion interrupt of EDMA3.
 *
 * \return  nil
 */
void enableXferCompInterrupt(uint32_t edma3Id)
{
	int32_t eventId = 0;	/* GEM event id */
    eventId = CpIntc_getEventId(ccXferHostInt[edma3Id][dsp_num]);
	EventCombiner_enableEvent(eventId);
}

/**
 * \brief   disableXferCompInterrupt
 *
 * This function disables the tranfer completion interrupt of EDMA3.
 *
 * \return  nil
 */
void disableXferCompInterrupt(uint32_t edma3Id)
{
    int32_t eventId = 0;	/* GEM event id */
    eventId = CpIntc_getEventId(ccXferHostInt[edma3Id][dsp_num]);
	EventCombiner_disableEvent(eventId);
}

/**
 * \brief   enableErrorInterrupt
 *
 * This function enables the error interrupt of EDMA3.
 *
 * \return  nil
 */
void enableErrorInterrupt(uint32_t edma3Id)
{
    int32_t eventId = 0;	/* GEM event id */
    eventId = CpIntc_getEventId(edma3ErrHostInt[edma3Id][dsp_num]);
	EventCombiner_enableEvent(eventId);
}

/**
 * \brief   disableErrorInterrupt
 *
 * This function disables the error interrupt of EDMA3.
 *
 * \return  nil
 */
void disableErrorInterrupt(uint32_t edma3Id)
{
    int32_t eventId = 0;	/* GEM event id */
    eventId = CpIntc_getEventId(edma3ErrHostInt[edma3Id][dsp_num]);
	EventCombiner_disableEvent(eventId);
}

