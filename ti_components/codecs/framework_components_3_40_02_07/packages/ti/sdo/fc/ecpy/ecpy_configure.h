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
 *  ======== ecpy_configure.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_CONFIGURE_
#define ti_sdo_fc_ecpy_ECPY_CONFIGURE_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/*
 *  ======== ECPY_configure ========
 */
/**
 *  @brief      Configure all DMA transfer settings for the logical channel.
 *
 *  @param[in]  handle      IRES_EDMA3CHAN channel handle.
 *  @param[in]  params      DMA transfer specific parameters used to
 *                          configure this logical DMA channel.
 *  @param[in]  transferNo  Indicates the individual transfer to be
 *                          configured using the passed 'params'
 *
 *  @pre        channel must be in active state
 *  @pre        valid  handle
 *  @pre        0 < transferNo <= originally requested number of transfers
 */
#if defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_configure(ECPY_Handle pHandle, ECPY_Params * restrict params,
    short transferNo)
{
    IRES_EDMA3CHAN_PaRamStruct * restrict paRam;
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

    /* use handle with cached IRES info */
    ECPY_ScratchObj *iresHandle = handle;

#if !(defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */

    Log_print2(Diags_ENTRY, "[+E] ECPY_configure> Enter "
            "(handle=0x%x, transferNo=%d)", (IArg)handle, (IArg)transferNo);

#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);

    if ((transferNo == 0) || (transferNo > iresHandle->assignedNumPaRams)) {

        Log_print2(Diags_USER4, "[+4] ECPY_configure> ERROR! (transferNo=%d) "
            " should be non-Zero and less than assignedNumPaRams:%d",
        (IArg)transferNo, (IArg)iresHandle->assignedNumPaRams);
    }
    Assert_isTrue(transferNo <= iresHandle->assignedNumPaRams, (Assert_Id)NULL);
    Assert_isTrue((transferNo > 0), (Assert_Id)NULL);

#endif /* _DEBUG_ defined only for debug profile */
#endif /* not inlined */

    /*
     * Always update shadow params of the 1st transfer.
     * When using Linked or single 3D transfers the physical PaRam of the
     * 1st trasfer gets overwritten , so it needs to be recorded in a shadow
     * memory and written out to physical PaRAM before each 'start'.
     */
    if (transferNo == 1) {
        /* 1st transfer updates the shadow PaRAM */
        paRam = (IRES_EDMA3CHAN_PaRamStruct *)handle->firstPARAMShadow;

    } else {
        /* modify the assigned Physical PaRAM directly */
        paRam = (IRES_EDMA3CHAN_PaRamStruct *)
                iresHandle->assignedPaRamAddresses[transferNo-1];
    }

    _updatePaRam(handle, paRam, params, transferNo);

#if !(defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */
    Log_print2(Diags_EXIT, "[+E] ECPY_configure> Exit "
            "(handle=0x%x, transferNo=%d)", (IArg)handle, (IArg)transferNo);
#endif /* not inlined */
}

#endif /* ti_sdo_fc_ecpy_ECPY_CONFIGURE_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
