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
 *  ======== ecpy_configure16.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_CONFIGURE16_
#define ti_sdo_fc_ecpy_ECPY_CONFIGURE16_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/*
 *  ======== ECPY_configure16 ========
 */
#if defined(ECPY_CONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_configure16(ECPY_Handle restrict pHandle,
    ECPY_ParamField16b fieldId, unsigned short value, short transferNo)
{
    IRES_EDMA3CHAN_PaRamStruct * restrict paRam;
    UInt registerValue32;
    UInt offsetAligned32;
    UInt *regPtr;
    ECPY_ScratchObj *handle = pHandle->scratchPtr;
    ECPY_ScratchObj * iresHandle = handle;

#if !(defined(ECPY_CONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */
    Log_print4(Diags_ENTRY, "[+E] ECPY_configure16> Enter"
            " (handle=0x%x, fieldId=0x%x, value=0x%x, trasnferNo=%d",
            (IArg)handle, (IArg)fieldId, (IArg)value, (IArg)transferNo);

    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(transferNo > 0, (Assert_Id)NULL);
    Assert_isTrue(transferNo <= handle->iresHandle->assignedNumPaRams,
                  (Assert_Id)NULL);
#endif /* not inlined */


    /* For transfer #1 always update the shadow PaRAM */
    if (transferNo == 1) {
        paRam = (IRES_EDMA3CHAN_PaRamStruct *)handle->firstPARAMShadow;

    } else {
        paRam = (IRES_EDMA3CHAN_PaRamStruct *)
                iresHandle->assignedPaRamAddresses[transferNo-1];
    }

    /* to update a 16bit field in a 32bit register we first read the 32bit
     * register, update
     */
    /* mask the rightmost 2 bits of fieldId to get a 32-bit aligned offset*/
    offsetAligned32 = fieldId & 0xFFFC;

    regPtr = (UInt *)((Char *)paRam + offsetAligned32);
    registerValue32 = *regPtr;
    registerValue32 &= ((UInt)0xFFFF0000 >> ((fieldId & 0x02) << 3));
    registerValue32 |= (value << ((fieldId & 0x02) << 3));
    *regPtr = registerValue32;

    /* when using non-DIRECT APIs, OPT always has STATIC bit off,
     * so nothing more needs to be done when CCNT > 1
     */
    if (fieldId == ECPY_PARAMFIELD_NUMFRAMES) {

        if  (value > 1) { /* 3D transfer */
            /* intermediate 3D transfer => enable ITCCHEN */
            paRam->opt |= ECPY_PARAMOPTS_ITCCHEN;
        }
        else {
            /* non3D transfer => ensure ITCCHEN is 0 to support dummy trnsfrs */
            paRam->opt &= ~(ECPY_PARAMOPTS_ITCCHEN);
        }
    }

#if !(defined(ECPY_CONFIGURE16_INLINE) || defined(ECPY_INLINE_ALL))
    Log_print0(Diags_EXIT, "[+X] ECPY_configure16> Exit");
#endif
}
#endif /* ti_sdo_fc_ecpy_ECPY_CONFIGURE16_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
