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
 *  ======== ecpy_directconfigure32.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_DIRECTCONFIGURE32_
#define ti_sdo_fc_ecpy_ECPY_DIRECTCONFIGURE32_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/*
 *  ======== ECPY_directConfigure32 ========
 */
#if defined(ECPY_DIRECTCONFIGURE32_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_directConfigure32(ECPY_Handle restrict pHandle,
    ECPY_ParamField32b fieldId, unsigned int value, short transferNo)
{
    IRES_EDMA3CHAN_PaRamStruct * restrict paRam;
    ECPY_ScratchObj * restrict handle = pHandle->scratchPtr;
    ECPY_ScratchObj * restrict iresHandle = handle;

#if !(defined(ECPY_DIRECTCONFIGURE32_INLINE) || defined(ECPY_INLINE_ALL))
    /* When not inlined. */
    Log_print4(Diags_ENTRY, "[+E] ECPY_directConfigure32b> Enter"
            " (handle=0x%x, fieldId=0x%x, value=0x%x, trasnferNo=%d",
            (IArg)handle, (IArg)fieldId, (IArg)value, (IArg)transferNo);
#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(transferNo > 0, (Assert_Id)NULL);
    Assert_isTrue(transferNo <= iresHandle->assignedNumPaRams, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */
#endif /* when not inlined */

    paRam = (IRES_EDMA3CHAN_PaRamStruct *)iresHandle->
            assignedPaRamAddresses[transferNo-1];

    *((unsigned int *)((unsigned int)paRam + fieldId)) = value;

#if !(defined(ECPY_DIRECTCONFIGURE32_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print0(Diags_EXIT, "[+E] ECPY_directConfigure32> Exit");
#endif /* when not inlined */
}

#endif /* ti_sdo_fc_ecpy_ECPY_DIRECTCONFIGURE32_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
