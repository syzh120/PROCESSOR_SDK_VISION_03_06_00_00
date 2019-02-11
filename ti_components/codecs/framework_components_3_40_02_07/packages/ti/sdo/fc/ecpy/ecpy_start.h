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
/*
 *  ======== ecpy_start.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_START__
#define ti_sdo_fc_ecpy_ECPY_START__

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/**
 *  ======== ECPY_start ========
 *
 *  @brief      Submit a single or linked transfer using the most recently
 *              configured transfer parameter settings.
 *
 *  @param[in]  handle   channel handle.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *  @pre        Channel must be in 'configured' state.
 *
 */
#if defined(ECPY_START_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_start(ECPY_Handle pHandle)
{
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

    /* IRES assigned info cached in the handle */
    ECPY_ScratchObj * iresHandle = handle;

    IRES_EDMA3CHAN_PaRamStruct * restrict paRam;
    IRES_EDMA3CHAN_PaRamStruct * shadow_paRam;
    int i;

#if !(defined(ECPY_START_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Asserts only when building ECPY library. Not when inlined */
    Log_print1(Diags_ENTRY, "[+E] ECPY_start> Enter (handle=0x%x)",
            (IArg)handle);
#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(handle->transferPending == FALSE, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */
#endif /* not inlined */

    /* Always update the 1st transfer's PaRAMs from its shadowParams */
    paRam =(IRES_EDMA3CHAN_PaRamStruct *)
            iresHandle->assignedPaRamAddresses[0];
    shadow_paRam = (IRES_EDMA3CHAN_PaRamStruct *)handle->firstPARAMShadow;

    /* Copy first transfer's shadow PaRAM to Phys PaRam registers */
#if !(defined(ECPY_START_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print1(Diags_USER2, "Final paRam 0x%x", (IArg)paRam);
#endif
    for (i = 0; i < 8; i++) {
        *((Uns *)paRam + i) = *((Uns *)shadow_paRam + i);
#if !(defined(ECPY_START_INLINE) || defined(ECPY_INLINE_ALL))
        Log_print2(Diags_USER2, "paRam[%d] = 0x%x", (IArg)i,
                (IArg) *((Uns *)paRam + i));
#endif
    }

    /* Set transferPending indicating a transfer has been submitted */
    handle->transferPending = 1;

    /* Manually trigger EDMA transfer by setting the ESR bit corresponding
     * to the EDMA channel
     */
    *(volatile unsigned int *)handle->esrRegisterAddr = handle->esrBitMask;

#if !(defined(ECPY_START_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print0(Diags_EXIT, "[+E] ECPY_start> Exit");
#endif /* not inlined */
}

# endif /* ti_sdo_fc_ecpy_ECPY_START__ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
