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
 *  ======== ecpy_directconfigure16.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_DIRECTCONFIGURE16_
#define ti_sdo_fc_ecpy_ECPY_DIRECTCONFIGURE16_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/*
 *  ======== ECPY_directConfigure16 ========
 */
#if defined(ECPY_DIRECTCONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_directConfigure16(ECPY_Handle restrict pHandle,
    ECPY_ParamField16b fieldId, unsigned short value, short transferNo)
{
    IRES_EDMA3CHAN_PaRamStruct * restrict paRam;
    ECPY_ScratchObj * restrict handle = pHandle->scratchPtr;
    ECPY_ScratchObj * restrict iresHandle = handle;

    UInt registerValue32;
    UInt offsetAligned32;
    UInt *regPtr;

#if !(defined(ECPY_DIRECTCONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL))
    /* When not inlined. */
    Log_print4(Diags_ENTRY, "[+E] ECPY_directConfigure16b> Enter"
            " (handle=0x%x, fieldId=0x%x, value=0x%x, trasnferNo=%d",
            (IArg)handle, (IArg)fieldId, (IArg)value, (IArg)transferNo);
#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(transferNo > 0, (Assert_Id)NULL);
    Assert_isTrue(transferNo <= iresHandle->assignedNumPaRams, (Assert_Id)NULL);

#endif /* _DEBUG_ defined only for debug profile */
#endif /* when not inlined */

    paRam = (IRES_EDMA3CHAN_PaRamStruct *)
            iresHandle->assignedPaRamAddresses[transferNo-1];

    /* mask the rightmost 2 bits of fieldId to get a 32-bit aligned offset*/
    offsetAligned32 = fieldId & 0xFFFC;
    regPtr = (UInt *)((Char *)paRam + offsetAligned32);
    /*
     * to update a 16bit field in a 32bit register we first read the 32bit
     * register and then update the 16bit field and write back the 32bit reg.
     */
    registerValue32 = *regPtr;
    registerValue32 &= ((UInt)0xFFFF0000 >> ((fieldId & 0x02) << 3));
    registerValue32 |= (value << ((fieldId & 0x02) << 3));
    *regPtr = registerValue32;

    if (fieldId == ECPY_PARAMFIELD_NUMFRAMES) {

        if  (value > 1) { /* 3D transfer */

            if (handle->finalTransferNo == transferNo) {

                /* 3D Final transfer */
                /* set ITCCHEN to 1' and reset OPT.STATIC bit (set to 0) */
                paRam->opt = handle->optFinalStaticOff | ECPY_PARAMOPTS_ITCCHEN;
            } else {
                /* intermediate 3D transfer => enable ITCCHEN */
                paRam->opt |= ECPY_PARAMOPTS_ITCCHEN;
            }
        }
        else {
            /* not 3D transfer => ensure ITCCHEN=0 to support dummy trnsfers */
            paRam->opt &= ~(ECPY_PARAMOPTS_ITCCHEN);
            if (handle->finalTransferNo == transferNo) {

                /* final non-3D transfer, so additionally turn STATIC bit ON */
                paRam->opt |= (ECPY_PARAMOPTS_STATIC);
            }
        }
    }
#if !(defined(ECPY_DIRECTCONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print0(Diags_EXIT, "[+E] ECPY_directConfigure16> Exit");
#endif /* when not inlined */
}
#endif /* ti_sdo_fc_ecpy_ECPY_DIRECTCONFIGURE16_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
