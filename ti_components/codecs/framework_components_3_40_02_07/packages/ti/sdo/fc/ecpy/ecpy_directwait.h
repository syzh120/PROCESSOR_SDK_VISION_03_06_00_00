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
 *  ======== ecpy_directwait.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_DIRECTWAIT_
#define ti_sdo_fc_ecpy_ECPY_DIRECTWAIT_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/**
 *  @brief      Wait for all data transfers on a logical channel to complete.
 *
 *  @param[in]  handle      ECPY channel handle.
 *
 *  @pre        Valid channel handle
 *  @pre        Channel must be in 'active' state.
 *  @pre        ECPY_directStartEdma has been called to submit an EDMA transfer
 *              on this channel.
 *  @pre        No ECPY_directWait() called since the last time a transfer on
 *              this channel has been started.
 *
 *  @remarks    This function will not return until all the data
 *              transfers on the given channel have completed.
 */
#if defined(ECPY_DIRECTWAIT_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_directWait(ECPY_Handle restrict pHandle)
{
    volatile unsigned int  *iprRegister; /* Interrupt pending register */
    volatile unsigned int  *icrRegister; /* Interrupt clear register */
    unsigned int            tccMask;
    ECPY_ScratchObj *handle = pHandle->scratchPtr;
#if !(defined(ECPY_DIRECTWAIT_INLINE) || defined(ECPY_INLINE_ALL))
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);

    Log_print1(Diags_ENTRY, "[+E] ECPY_directWait> Enter (handle=0x%x)",
            (IArg)handle);
#endif

    /*
     * For performance use the IPR Register pointer and tcc mask
     * that is cached in the handle:
     */
    tccMask = handle->iprBitMask;
    iprRegister = (volatile unsigned int  *)handle->iprRegisterAddr;
    /* ICR/ICRH Register is fixed offset away from IPR/IPRH */
    icrRegister = (volatile unsigned int  *)(iprRegister+2);

    /*
     * Poll the EDMA3 Interrupt Pending Register (IPR or IPRH) until the
     * transfer completion code (TCC) assigned to the channel gets set.
     * The "direct" APIs do not maintain channel state for 'transferPending'
     * so, each ECPY_directStartEdma call must be matched by exactly one
     * ECPY_directWait call.
     */
    while( ! ((*iprRegister) & tccMask) ) {
        /* Check EDMA3_IPR register until the TCC bit is set */
        ;
    }

    /*  Clear TCC by writing to EDMA3_ICR Reg */
    *icrRegister = tccMask;

#if !(defined(ECPY_DIRECTWAIT_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print0(Diags_EXIT, "[+X] ECPY_directWait> Exit");
#endif

}
# endif /* ti_sdo_fc_ecpy_ECPY_DIRECTWAIT_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
