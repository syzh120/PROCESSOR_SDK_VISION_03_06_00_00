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
 *  ======== ecpy_setfinal.h ========
 */

#ifdef ti_sdo_fc_ecpy_ECPY_

#ifndef ti_sdo_fc_ecpy_ECPY_SETFINAL_
#define ti_sdo_fc_ecpy_ECPY_SETFINAL_

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ecpy/ecpy_util.h>

/*
 *  ======== ECPY_setfinal ========
 *
 *  @brief      Indicate that a given transfer will be the last in a sequence
 *              of linked transfers.
 *
 *              This API can be used to dynamically change the number of
 *              transfers in a linked transfers.
 *
 *  @param[in]  handle      ECPY channel handle.
 *  @param[in]  transferNo  Indicates which transfer that will be the last
 *                          in the set of linked transfers. (This is the same
 *                          value that was passed to ECPY_configure()).
 *
 *  @remarks    This API can be used if a channel was created to
 *              transfer numTransfers linked transfers, but at
 *              some point, it may be that fewer transfers than
 *              numTransfers should be started.
 *
 *  @remarks    This API configures both 'direct' params as well as shadow
 *              paRAMs.
 *
 *  @pre        Valid channel handle.
 *  @pre        Channel must be in 'active' state.
 *
 *  @post       ECPY Handle's state is updated with 'current' last transferNo.
 *  @post       If current 'final' is > previous 'final' transfer, fix the
 *              link field of the previous 'final' transfer to link to the
 *              next transfer!
 */
#if defined(ECPY_SETFINAL_INLINE) || defined(ECPY_INLINE_ALL)
ECPY_VERSION_MACRO
static __inline
#endif
Void ECPY_setFinal(ECPY_Handle pHandle, short transferNo)
{
    PaRamStructPtr paRamThis;
    ECPY_ScratchObj *handle = pHandle->scratchPtr;

    /* use handle with cached IRES info */
    ECPY_ScratchObj * iresHandle = handle;

    short numTotalPaRams = iresHandle->assignedNumPaRams;
    short prevFinal = handle->finalTransferNo;

#if !(defined(ECPY_SETFINAL_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */
    Log_print2(Diags_ENTRY, "[+E] ECPY_setFinal> Enter "
            "(handle=0x%x, transferNo=%d)", (IArg)handle, (IArg)(transferNo ));

#ifdef _DEBUG_
    Assert_isTrue(handle != NULL, (Assert_Id)NULL);
    Assert_isTrue(transferNo > 0, (Assert_Id)NULL);
    Assert_isTrue(transferNo <= iresHandle->assignedNumPaRams, (Assert_Id)NULL);

#endif /* _DEBUG_ defined only for debug profile */
#endif /* only for non-inlined*/

    if (numTotalPaRams == 1) {
        return;
    }

    handle->finalTransferNo = transferNo; /* this xfer becomes the final */

    /*
     *  Reset the link id of the previous transfer that was configured as
     *  final, unless it is the last PaRam allocated to the channel.
     */
    if ((prevFinal < numTotalPaRams) && (prevFinal != transferNo)) {
        PaRamStructPtr paRamPrevFinal;

        /* If prevFinal was 1st xfer, update the shadow PaRAMs . */
        if (prevFinal == 1) {
            paRamPrevFinal = (PaRamStructPtr)(handle->firstPARAMShadow);

        } else {
            /* modify the assigned Physical PaRAM directly */
            paRamPrevFinal = (PaRamStructPtr)
                    iresHandle->assignedPaRamAddresses[prevFinal-1];
        }
        /* IRES assigned addresses cached in the handle */
        paRamPrevFinal->link = (unsigned short)
                ((Uns)(iresHandle->assignedPaRamAddresses[prevFinal]) & 0xFFFF);

        /*
         * Make what used to be Final a Linked/Intermediate transfer:
         * Unset TCC_INTEN and STATIC, and Set TCCHEN & TCCMODE
         * NOTE: can't simply set 'paRamPrevFinal->opt = handle->optLinked'
         *       since we don't know if ITCCHEN is 1 or 0 without checking CCNT
         */
        if (paRamPrevFinal->ccnt > 1) {
            paRamPrevFinal->opt = handle->optLinked | ECPY_PARAMOPTS_ITCCHEN;
        } else {
            paRamPrevFinal->opt = handle->optLinked;
        }
        /*
         * This makes sure we use the TCCMODE info from the handle's optLinked,
         * since this may have been modified via ECPY_setEarlyCompletion after
         * the channel was created
         */
    }

    /* If setting 1st xfer as Final, update the shadow PaRAMs . */
    if (transferNo == 1) {
        paRamThis = (PaRamStructPtr)handle->firstPARAMShadow;

    } else {
        /* modify the assigned Physical PaRAM directly */
        paRamThis = (PaRamStructPtr)
                iresHandle->assignedPaRamAddresses[transferNo-1];
    }

    /* Set no link for final PaRam */
    paRamThis->link = 0xffff;

    /*
     * Set this as a Final transfer:
     * Set TCC_INTEN, and UnSet TCCHEN & TCCMODE
     */
    paRamThis->opt |= (ECPY_PARAMOPTS_TCC_INTEN);
    paRamThis->opt &= ~(ECPY_PARAMOPTS_TCCMODE | ECPY_PARAMOPTS_TCCHEN);

#if !(defined(ECPY_SETFINAL_INLINE) || defined(ECPY_INLINE_ALL))
    /* Log and Assert only when not inlined */
    Log_print0(Diags_EXIT, "[+E] ECPY_setFinal> Exit");
#endif /* not inlined */
}

#endif /* ti_sdo_fc_ecpy_ECPY_SETFINAL_ */
#else
#error "ti/sdo/fc/ecpy/ecpy.h must be included first"
#endif
