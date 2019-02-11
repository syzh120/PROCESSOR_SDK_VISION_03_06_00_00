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
/**
 *  @file       ti/sdo/fc/ecpy/ecpy_util.h
 *
 *  @brief      DSP-side ECPY Library utility definitions.
 */

/**
 *  @defgroup   ti_sdo_fc_ecpy_ECPY_UTIL ECPY Utility Module
 *
 *              Utility data structures and functions for the ECPY library.
 */

#ifndef ti_sdo_fc_ecpy_ECPY_UTIL_
#define ti_sdo_fc_ecpy_ECPY_UTIL_

/** @ingroup    ti_sdo_fc_ecpy_ECPY_UTIL */
/*@{*/

/* Definitions are mostly for internal use, but are accessible if needed. */



/*
 * This is used to ensure that routines that were previously compiled
 * with inline ECPY functions are compatible with the current version
 * of ECPY.
 * Therefore, whenever the ECPY code is modified such that it is no
 * longer compatible with the previous inline versions, the final
 * two digits of __ECPY_inlineCompatibilityKey_NN should be incremented.
 * In that way, if in fact the code and version name does change, then
 * code with inline ECPY functions that was previously compiled will
 * show an unresolved reference when linking.  This will indicate
 * an incompatibility.
 */
#define ECPY_INLINE_COMPATIBILITY_KEY_NAME ECPY_inlineCompatibilityKey_01
#define ECPY_VERSION_MACRO    asm (" .ref _ECPY_inlineCompatibilityKey_01");

/*
 *  Bits to set in PaRam Register Opts field.
 */
#define ECPY_PARAMOPTS_ABSYNC    (0x1 << 2)
#define ECPY_PARAMOPTS_TCC_INTEN (0x1 << 20)
#define ECPY_PARAMOPTS_TCCHEN    (0x1 << 22)
#define ECPY_PARAMOPTS_ITCCHEN   (0x1 << 23)
#define ECPY_PARAMOPTS_STATIC    (0x1 << 3)
#define ECPY_PARAMOPTS_TCCMODE   (0x1 << 11)

/* TCC bits in Opts field of PaRam */
#define ECPY_PARAMOPTS_TCCMASK    0x3f000
#define ECPY_PARAMOPTS_TCCSHIFT   12       /* TCC starts at bit 12 of opts */
#define ECPY_PARAMOPTS_TCCBITS(tcc) ((tcc) << 12)



/**
 *  @brief  ECPY_ScratchObj defines the structure of the dma channel handle
 *          that is used to manage state about the EDMA3 channel.
 */
typedef struct ECPY_ScratchObj {

    IRES_EDMA3CHAN2_Obj *iresHandle;

    /* cache fields from ires handle.  was conditional on  _CACHE_IRES */
    short assignedEdmaChannelIndex;
    short assignedNumPaRams;
    unsigned int * assignedPaRamAddresses;
    unsigned int * queueMap;

    unsigned int optLinked;       /* PaRAM's OPT for intermediate transfers */
    unsigned int optFinalStaticOff;   /* PaRAM's OPT for the FINAL transfer */
    unsigned int iprRegisterAddr; /* Interrupt pending register */
    unsigned int iprBitMask;      /* Bit mask contining '1' corr to TCC */
    unsigned int esrRegisterAddr; /* Event Set Register Addr corr to channel */
    unsigned int esrBitMask;      /* Bit mask contining '1' corr to channel */
    short transferPending;
    short finalTransferNo;        /* TransferNo of the last transfer in a */
                                  /* linked transfer */
    IRES_EDMA3CHAN_PaRamStruct *firstPARAMShadow;

} ECPY_ScratchObj;

/**
 *  @brief  ECPY_Obj defines the structure of the persistent dma channel handle
 *           that is used to manage state about the EDMA3 channel.
 */
typedef struct ECPY_Obj {

    IRES_EDMA3CHAN2_Obj *iresHandle;
    ECPY_ScratchObj     *scratchPtr;
    short scratchId;
} ECPY_Obj;

typedef union {
    struct {
#ifdef xdc_target__bigEndian
        /*
         *  Switching endianness of the processor swaps
         *  the addresses of the 16-bit PaRam fields.
         */
        short    hi16;
        short    lo16;
#else
        short    lo16;
        short    hi16;
#endif
    } field;
    unsigned int val32;
} ECPY_Packed32;

/* EDMA3 PaRAM register structure redefined with 32-bit register fields
* for acnt_bcnt, elementIndexes, and frameIndexes.
*/
typedef struct _PaRamStruct {
    unsigned int   opt;
    unsigned int   src;
    ECPY_Packed32  acnt_bcnt;
    unsigned int   dst;
    ECPY_Packed32  elementIndexes;
#ifdef xdc_target__bigEndian
    unsigned short bCntrld;
    unsigned short link;
#else
    unsigned short link;
    unsigned short bCntrld;
#endif
    ECPY_Packed32  frameIndexes;
#ifdef xdc_target__bigEndian
    unsigned short rsvd;
    unsigned short ccnt;
#else
    unsigned short ccnt;
    unsigned short rsvd;
#endif
} *PaRamStructPtr;


/* common PARAM update portion of _configure and _directConfigure functions */
static __inline Void
_updatePaRam(ECPY_ScratchObj *handle, IRES_EDMA3CHAN_PaRamStruct *paRam,
        ECPY_Params * restrict params, short transferNo)
{
    ECPY_Packed32 _packed_acnt_bcnt;
    ECPY_Packed32 _packed_elementIndexes;
    ECPY_Packed32 _packed_frameIndexes;

    /* iresHandle is cached */
    ECPY_ScratchObj *iresHandle = handle;

    PaRamStructPtr paRamPtr = (PaRamStructPtr)paRam;

    /* Final transfer's OPT's STATIC bit will ON initially, and will be
     * cleared/unset iff later we discover it is a 3D xfer */
    unsigned int staticBit = ECPY_PARAMOPTS_STATIC;
    unsigned int itcchenBit = 0x0;

    /* #1 - Source address */
    paRamPtr->src = (unsigned int)params->srcAddr;

    /* #2 */
    _packed_acnt_bcnt.field.lo16 = params->elementSize; /* must always be set */

    /* #3 - Destination address */
    paRamPtr->dst = (unsigned int)params->dstAddr;

    if (params->transferType != ECPY_1D1D) {

        /* Field #2: update with 2nd dimension */
        _packed_acnt_bcnt.field.hi16 = params->numElements;

        /* Field #3: set Element Indexes for 2D */
        if (params->transferType == ECPY_1D2D) {
            _packed_elementIndexes.field.lo16 = params->elementSize;
            _packed_elementIndexes.field.hi16 = params->dstElementIndex;
        }
        else if (params->transferType == ECPY_2D1D) {
            _packed_elementIndexes.field.lo16 = params->srcElementIndex;
            _packed_elementIndexes.field.hi16 = params->elementSize;
        } else { /* 2D2D */
            _packed_elementIndexes.field.lo16 = params->srcElementIndex;
            _packed_elementIndexes.field.hi16 = params->dstElementIndex;
        }
        /* Element Indexes only get set for non 1D1D transfers */
        paRamPtr->elementIndexes.val32 = _packed_elementIndexes.val32;
    } else { /* 1D1D */
        _packed_acnt_bcnt.field.hi16 = 1;
    }

    paRamPtr->acnt_bcnt.val32 = _packed_acnt_bcnt.val32;

    if (params->numFrames <= 1) {
        paRamPtr->ccnt = 1;
    }
    else {
        /* 3D Transfer */
        paRamPtr->ccnt = params->numFrames;
        _packed_frameIndexes.field.lo16 = params->srcFrameIndex;
        _packed_frameIndexes.field.hi16 = params->dstFrameIndex;
        /* Frame Indexes only get set for 3D transfers :- numFrames/CCNT > 1 */
        paRamPtr->frameIndexes.val32 = _packed_frameIndexes.val32;

        /*
         * reset staticBit (OPT's STATIC bit) and enable ITCCHEN
         * since it is a 2D transter
         */
        staticBit = 0x0;
        itcchenBit = ECPY_PARAMOPTS_ITCCHEN;
    }

#if !(defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_DIRECTCONFIGURE_INLINE) ||\
      defined(ECPY_INLINE_ALL))

    Log_print5(Diags_USER4, "[+4] ECPY_configure> src 0x%x, "
            "dst 0x%x, acnt 0x%x, bcnt 0x%x ccnt 0x%x",
            (IArg)(paRam->src), (IArg)(paRam->dst),
            (IArg)(paRam->acnt), (IArg)(paRam->bcnt),
            (IArg)(paRam->ccnt));

    Log_print3(Diags_USER4, "[+4] ECPY_configure> bcnt reload"
            " 0x%x, srcIndex 0x%x, dstIndex 0x%x",
            (IArg)(paRam->bCntrld), (IArg)(paRam->srcElementIndex),
            (IArg)(paRam->dstElementIndex));
#endif /* not inlined */

    if ((transferNo != handle->finalTransferNo) &&
            (transferNo < iresHandle->assignedNumPaRams)) {
        /*  == INTERMEDIATE Transfer ==
         *  Setup this param's link field to point to the NEXT transfer when
         *  setting up linked transfers we assign PARAM addresses in
         *  descending order, so that the last entry is the first transfer,
         *  etc., handle's paRamAddr is pointing to the 'last' PARAM entry
         *  assigned to the channel handle (along with the preceding
         *  "numTransfer" PARAM entries.
         */
        /* #5 */
        /* addressed from IRES cached in handle */
        paRamPtr->link = (unsigned short)
                ((handle->assignedPaRamAddresses[transferNo]) & 0xFFFF);

        /* initialize OPT from the create time configured value for linking */
        /* set ITCCHEN bit based on whether it is 3D transfer or not */
        paRamPtr->opt = handle->optLinked | itcchenBit;

#if !(defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_DIRECTCONFIGURE_INLINE) ||\
      defined(ECPY_INLINE_ALL))

        Log_print2(Diags_USER4, "[+4] ECPY_configure> Link this"
                " transfer to 0x%x Opt is 0x%x",
                (IArg)(paRam->link), (IArg)(paRam->opt));
#endif /* not inlined */
    }
    else {
        /* == Single transfer or the FINAL transfer of a linked set */
        /* #5 - Set no link for final PaRam */
        paRamPtr->link = 0xffff;

        /* #0 */
        /* initialize OPT from the create time configured value for FINAL */
        paRamPtr->opt = handle->optFinalStaticOff | staticBit | itcchenBit;

#if !(defined(ECPY_CONFIGURE_INLINE) || defined(ECPY_DIRECTCONFIGURE_INLINE) ||\
      defined(ECPY_INLINE_ALL))

        Log_print2(Diags_USER4, "[+4] ECPY_configure> Mark as Final "
                " transfer setting Link to 0x%x Opt is 0x%x",
                (IArg)(paRam->link), (IArg)(paRam->opt));
#endif /* not inlined */
    }
}

/*@}*/

#endif  /* ti_sdo_fc_ecpy_ECPY_UTIL_ */
