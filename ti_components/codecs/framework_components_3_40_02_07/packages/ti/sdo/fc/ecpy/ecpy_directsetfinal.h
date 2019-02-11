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
 *  ======== ecpy_directsetfinal.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_DIRECTSETFINAL_
#define ti_sdo_fc_ecpy_ECPY_DIRECTSETFINAL_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/*
 * ======== ECPY_directSetFinal ====================
 */
#if defined(ECPY_DIRECTSETFINAL_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_directSetFinal(ECPY_Handle pHandle, short transferNo)
{
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

    /* IRES assigned info is cached in the handle */
    ECPY_ScratchObj * iresHandle = handle;

    PaRamStructPtr paRamThis = (PaRamStructPtr)
            iresHandle->assignedPaRamAddresses[transferNo-1];
    short numTotalPaRams = iresHandle->assignedNumPaRams;
    short prevFinal = handle->finalTransferNo;

#if !(defined(ECPY_DIRECTSETFINAL_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */

    Log_print2(Diags_ENTRY, "[+E] ECPY_directSetFinal> Enter "
            "(handle=0x%x, transferNo=%d)", (IArg)handle, (IArg)(transferNo ));

#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(transferNo > 0, (Assert_Id)NULL);
    Assert_isTrue(transferNo <= iresHandle->assignedNumPaRams, (Assert_Id)NULL);
#endif /* _DEBUG_ defined only for debug profile */
#endif /* only for non-inlined */

    if (numTotalPaRams == 1) {
#if !(defined(ECPY_DIRECTSETFINAL_INLINE) || defined(ECPY_INLINE_ALL))
        Log_print0(Diags_EXIT, "[+E] ECPY_setFinal> Exit");
#endif /* only for non-inlined */

        return;
    }

    handle->finalTransferNo = transferNo; /* this xfer becomes the final */

    /*
     *  Reset the link id of the previous transfer that was configured as
     *  final, unless it is the last PaRam allocated to the channel.
     */
    if ( (prevFinal < numTotalPaRams) && (prevFinal != transferNo)) {
        PaRamStructPtr paRamPrevFinal;

        /* modify the assigned Physical PaRAM directly */
        paRamPrevFinal = (PaRamStructPtr)
        iresHandle->assignedPaRamAddresses[prevFinal-1];
        /* IRES assigned addresses cached in the handle */
        paRamPrevFinal->link = (unsigned short)
                (Uns)((iresHandle->assignedPaRamAddresses[prevFinal]) & 0xFFFF);

        /*
         * Make what used to be Final a Linked/Intermediate transfer:
         * Unset TCC_INTEN and STATIC, and Set TCCHEN & TCCMODE
         * NOTE: can't simply set 'paRamPrevFinal->opt = handle->optLinked'
         * because we don't know if ITCCHEN is 1 or 0 without checking CCNT
         */
        if (paRamPrevFinal->ccnt > 1) {
            paRamPrevFinal->opt = handle->optLinked | ECPY_PARAMOPTS_ITCCHEN;
        } else {
            paRamPrevFinal->opt = handle->optLinked;
        }
    }

    /* Set no link for final PaRam */
    paRamThis->link = 0xffff;

    /* set the OPT for the final transfer */
    if (paRamThis->ccnt > 1) {
        /* 3D transfer, so use default, where STATIC bit OFF */
        /*
         * Make this a Final transfer:
         * Set TCC_INTEN, and UnSet TCCHEN & TCCMODE
         */
        paRamThis->opt |= (ECPY_PARAMOPTS_TCC_INTEN);
        paRamThis->opt &= ~(ECPY_PARAMOPTS_TCCMODE | ECPY_PARAMOPTS_TCCHEN);

    } else {
        /* set STATIC bit ON, so that single transfers do not thrash 1st PaRAM*/
        /*
         * Make this a Final transfer:
         * Set TCC_INTEN & STATIC, and UnSet TCCHEN & TCCMODE
         */
        paRamThis->opt |= (ECPY_PARAMOPTS_TCC_INTEN | ECPY_PARAMOPTS_STATIC);
        paRamThis->opt &= ~(ECPY_PARAMOPTS_TCCMODE | ECPY_PARAMOPTS_TCCHEN);
    }

#if !(defined(ECPY_DIRECTSETFINAL_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */
    Log_print0(Diags_EXIT, "[+E] ECPY_directSetFinal> Exit");
#endif /* not inlined */
}

#endif /* ti_sdo_fc_ecpy_ECPY_DIRECTSETFINAL_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
