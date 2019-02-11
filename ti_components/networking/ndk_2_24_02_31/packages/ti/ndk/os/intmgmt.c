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
 * */
/*
 * ======== intmgmt.c ========
 *
 * Interrupt Management wrapper written to abstract out
 * OS (BIOS6) specific interrupt management calls.
 *
 */

#include <string.h>

#include <stkmain.h>

#include <xdc/std.h>
#include <xdc/runtime/Error.h>

#include <ti/sysbios/hal/Hwi.h>

#if defined(_TMS320C6X)
#include <ti/sysbios/family/c64p/EventCombiner.h> 
#endif

/* The system events 0-3 are reserved and used for system
 * reset, NMI etc. Hence cannot be used for individual 
 * masked interrupts.
 */
#define     MIN_EVENT_ID        3
#define     MAX_EVENT_ID        128

/*
 * TODO: re-visit if this module should do the range checking or
 * rely on SYS/BIOS to do it. Note that the ranges are ISA-specific.
 */
#if defined(_TMS320C6X)
#define     MIN_INTVECT_ID      3
#define     MAX_INTVECT_ID      15
#else
#define     MIN_INTVECT_ID      1
#define     MAX_INTVECT_ID      63
#endif

/*
 * Hack to work around Interrupt API limitations and SYS/BIOS issues.
 * Does not work with interrupts that use ECM (currently none known).
 *
 */
static Hwi_Handle hwiTable[MAX_INTVECT_ID + 1] = {(Hwi_Handle)1};

/**
 *  @b Interrupt_add
 *  @n
 *  Validates the interrupt setup parameters and sets up the 
 *  interrupt using BIOS. Uses the Hardware Interrupt Selector (Hwi)
 *  selector module of BIOS if a single system event is being
 *  mapped directly to a DSP interrupt vector. Alternatively,
 *  this function chooses the Event Combiner Manager (ECM) module
 *  of BIOS for setting up interrupts, if more than one system
 *  event needs to be combined into a DSP interrupt vector (C6000 DSPs only).
 *
 *  @param[in]  myIntSetup
 *      Pointer to the Interrupt Setup object filled in by the 
 *      user.
 *
 *  @retval
 *      1       -   Invalid Interrupt Setup Parameters
 *      0       -   Success
 */
UINT32  Interrupt_add(IntSetup* myIntSetup)
{
#if defined(_TMS320C6X)
    UINT32      i;
#endif
    Hwi_Params  hwi_params;
    Error_Block eb;
    Hwi_Handle  hHwi;

    if (hwiTable[0] == (Hwi_Handle)1) {
	memset(hwiTable, 0, sizeof(hwiTable));
    }

    if(!myIntSetup || !myIntSetup->sysEvtCount || !myIntSetup->pCallbackFxn)
    {
        /* Invalid Interrupt setup arguments. Return error */
        return 1;
    }

    /* Initialize the error block. */
    Error_init(&eb);
                
    if(myIntSetup->sysEvtCount == 1)
    {
        /* One to One mapping between the system event and the
         * interrupt vector. We can use Hwi module of the BIOS
         * to configure this interrupt.
         */
      if (myIntSetup->intVectId > MIN_INTVECT_ID && myIntSetup->intVectId < MAX_INTVECT_ID)
        {
            Hwi_Params_init (&hwi_params);

            hwi_params.arg          =   (UArg) myIntSetup->pCallbackArg;
            hwi_params.enableInt    =   1;
            hwi_params.eventId      =   myIntSetup->sysEvtId[0];
            hwi_params.maskSetting  =   ti_sysbios_hal_Hwi_MaskingOption_SELF;

            if ((hHwi = Hwi_create (myIntSetup->intVectId, (ti_sysbios_hal_Hwi_FuncPtr) myIntSetup->pCallbackFxn, &hwi_params, &eb)) == NULL)
            {
                DbgPrintf(DBG_ERROR,"Interrupt_add(): could not configure the interrupt.");
                DbgPrintf(DBG_ERROR, Error_getMsg(&eb));
            }
	    /* save the handle so we can delete it later */
	    hwiTable[myIntSetup->intVectId] = hHwi;
        }
        else
        {
            /* The interrupt vector configured is invalid. Only 
             * MAX_NUM_INTERRUPTS (128) are defined by C64x+ devices.
             * Return error.
             */
            return 1;
        }
    }
    else
    {
#if defined(_TMS320C6X)
        /* Multiple interrupt vectors combined to a single 
         * system event. We will have to use the ECM module
         * of BIOS to configure this interrupt.
         */
        for (i = 0; i < myIntSetup->sysEvtCount; i++)
        {
            if( myIntSetup->sysEvtId[i] > MIN_EVENT_ID && myIntSetup->sysEvtId[i] < MAX_EVENT_ID )
            {
	            EventCombiner_dispatchPlug (myIntSetup->sysEvtId[i],(EventCombiner_FuncPtr) myIntSetup->pCallbackFxn, 
                                            (UArg) myIntSetup->pCallbackArg, (Bool) myIntSetup->bEnable);

            }
            else
            {
                /* Invalid system event number. Valid system event numbers can range
                 * between 4-127. Return error.
                 */
                return 1;
            }
        }
#else
        /*
         * ARM does not support EventCombiner, return error. 
         */
        return 1;
#endif
    }

    /* Return Success */
    return 0;
}

/**
 *  @b Interrupt_delete
 *  @n
 *
 *  @param[in]  myIntSetup
 *      Pointer to the Interrupt Setup object filled in by the 
 *      user.
 *
 *  @retval
 *      0       -   Success (Always returns success)
 */
#define Hwi_getHandle(id) (Hwi_module->dispatchTable[(id)])

UINT32 Interrupt_delete(IntSetup* myIntSetup)
{
    Hwi_Handle hwi;

    if ((hwi = hwiTable[myIntSetup->intVectId]) != NULL) {
	Hwi_delete(&hwi);
    }
    
    return 0;
}

/**
 *  @b Interrupt_enable
 *  @n
 *  Validates the interrupt setup parameters and enables the 
 *  interrupt using BIOS defined constructs. 
 *
 *  @param[in]  myIntSetup
 *      Pointer to the Interrupt Setup object filled in by the 
 *      user.
 *
 *  @retval
 *      1       -   Invalid Interrupt Setup Parameters
 *      0       -   Success
 */
UINT32 Interrupt_enable(IntSetup* myIntSetup)
{
#if defined(_TMS320C6X)
    UINT32      i;
#endif

    if(!myIntSetup || !myIntSetup->sysEvtCount || !myIntSetup->pCallbackFxn)
    {
        /* Invalid Interrupt setup arguments. Return error */
        return 1;
    }

    if(myIntSetup->sysEvtCount == 1)
    {
        /* One to One mapping between the system event and the
         * interrupt vector. We can use HWI module of the BIOS
         * to configure this interrupt.
         */
        Hwi_enableInterrupt (myIntSetup->sysEvtId[0]);
    }
#if defined(_TMS320C6X)
    else
    {
        /* Multiple interrupt vectors combined to a single 
         * system event. We will have to use the ECM module
         * of BIOS to configure this interrupt.
         */
        for (i = 0; i < myIntSetup->sysEvtCount; i++)
        {
            EventCombiner_enableEvent (myIntSetup->sysEvtId[i]);
        }
    }
#endif

    /* Return Success */
    return 0;
}

/**
 *  @b Interrupt_disable
 *  @n
 *  Validates the interrupt setup parameters and disables the 
 *  interrupt using BIOS defined constructs. 
 *
 *  @param[in]  myIntSetup
 *      Pointer to the Interrupt Setup object filled in by the 
 *      user.
 *
 *  @retval
 *      1       -   Invalid Interrupt Setup Parameters
 *      0       -   Success
 */
UINT32 Interrupt_disable(IntSetup* myIntSetup)
{
#if defined(_TMS320C6X)
    UINT32      i;
#endif

    if(!myIntSetup || !myIntSetup->sysEvtCount || !myIntSetup->pCallbackFxn)
    {
        /* Invalid Interrupt setup arguments. Return error */
        return 1;
    }

    if(myIntSetup->sysEvtCount == 1)
    {
        /* One to One mapping between the system event and the
         * interrupt vector. We can use HWI module of the BIOS
         * to configure this interrupt.
         */
        Hwi_disableInterrupt (myIntSetup->sysEvtId[0]);
    }
#if defined(_TMS320C6X)
    else
    {
        /* Multiple interrupt vectors combined to a single 
         * system event. We will have to use the ECM module
         * of BIOS to configure this interrupt.
         */
        for (i = 0; i < myIntSetup->sysEvtCount; i++)
        {
            EventCombiner_disableEvent (myIntSetup->sysEvtId[i]);
        }
    }
#endif

    /* Return Success */
    return 0;
}
