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
 *  ======== ecpy_directstartedma.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_DIRECTSTARTEDMA__
#define ti_sdo_fc_ecpy_ECPY_DIRECTSTARTEDMA__

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/**
 *  ======== ECPY_directStartEdma ========
 *
 *  @brief      Submit a single or linked transfer using the most recently
 *              modified EDMA3 Physical PaRAM transfer parameter settings.
 *
 *  @param[in]  handle   channel handle.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *  @pre        Channel must be in 'configured' state.
 *
 */
#if defined(ECPY_DIRECTSTARTEDMA_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_directStartEdma(ECPY_Handle pHandle)
{
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

#if !(defined(ECPY_DIRECTSTARTEDMA_INLINE) || defined(ECPY_INLINE_ALL))
    /* entry log/assertion checks when not inlining ECPY_directStartEdma */
    Log_print1(Diags_ENTRY, "[+E] ECPY_directStartEdma> Enter (handle=0x%x)",
            (IArg)handle);
#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */
#endif /* not inlined */
    /*
     * Start an EDMA manual triggered transfer using the most recent
     * Physical EDMA PARAM values. If the previous transfer was a Linked
     * transfer, the 1st PARAM must be directConfigure()'ed before calling
     * this function. This functions does not use shadow PaRAMs to retain
     * logical channel PARAM settings.
     */

    /* Manually trigger EDMA transfer by setting the ESR bit corresponding
     * to the EDMA channel
     */
    *(volatile unsigned int *)handle->esrRegisterAddr = handle->esrBitMask;

#if !(defined(ECPY_DIRECTSTARTEDMA_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print0(Diags_EXIT, "[+X] ECPY_directStartEdma> Exit");
#endif
}

# endif /* ti_sdo_fc_ecpy_ECPY_DIRECTSTARTEDMA__ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
