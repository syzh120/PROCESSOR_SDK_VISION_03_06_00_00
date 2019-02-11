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
/**
 *  @file       ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h
 *
 *  @brief      IRES EDMA3CHAN PROTOCOL Interface Definitions -
 *              Allows algorithms to request and receive handles representing
 *              EDMA3 resources associated with a single EDMA3 channel.
 */

/**
 *  @addtogroup ti_sdo_fc_ires_edma3chan_IRES_EDMA3CHAN IRES EDMA3 Protocol
 *
 *              Allows algorithms to request and receive handles representing
 *              EDMA3 resources associated with a single EDMA3 channel.
 */

#ifndef ti_sdo_fc_ires_edma3chan_IRES_EDMA3CHAN_
#define ti_sdo_fc_ires_edma3chan_IRES_EDMA3CHAN_

/** @ingroup    ti_sdo_fc_ires_edma3Chan_IRES_EDMA3CHAN */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/xdas.h>
#include <ti/xdais/ires_common.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_EDMA3CHAN_PROTOCOLNAME     "ti.sdo.fc.ires.edma3chan"

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for EDMA3CHAN
 *              functions.
 *
 * @remarks     For example,
 *                  Diags_setMask(EDMA3CHAN_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define EDMA3CHAN_MODNAME  "ti.sdo.fc.ires.edma3chan"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for the base type of IRES_EDMA3CHAN resource
 *          (Oldest version supported)
 */
static IRES_ProtocolRevision IRES_EDMA3CHAN_PROTOCOLREVISION = {1, 0, 0};

#endif

/**
 * @brief   Protocol Revision for the 1.0.0 version of resource
 */
#define IRES_EDMA3CHAN_PROTOCOLREVISION_1_0_0 {1, 0, 0}
#define IRES_EDMA3CHAN_SETPROTOCOLREVISION_1_0_0(rev) {(rev)->Major = 1; \
        (rev)->Source = 0; (rev)->Radius = 0;}

/**
 * @brief   Protocol Revision for the 2.0.0 version of resource
 */
#define IRES_EDMA3CHAN_PROTOCOLREVISION_2_0_0 {2, 0, 0}
#define IRES_EDMA3CHAN_SETPROTOCOLREVISION_2_0_0(rev) {(rev)->Major = 2; \
        (rev)->Source = 0; (rev)->Radius = 0;}

/**
 * @brief       Maximum number of params and tccs that can be requested in one
 *              handle
 */
#define IRES_EDMA3CHAN_MAXPARAMS        512
#define IRES_EDMA3CHAN_MAXTCCS          32
#define IRES_EDMA3CHAN_NUMDESTTYPES     8

/**
 * @brief       Macros to represent different PaRam, Channel and tcc types
 */
#define IRES_EDMA3CHAN_PARAM_ANY        512
#define IRES_EDMA3CHAN_PARAM_NONE       513
#define IRES_EDMA3CHAN_TCC_ANY          514
#define IRES_EDMA3CHAN_TCC_NONE         515
#define IRES_EDMA3CHAN_EDMACHAN_ANY     516
#define IRES_EDMA3CHAN_QDMACHAN_ANY     516
#define IRES_EDMA3CHAN_CHAN_NONE        518

/**
 *  @brief      Handle to "logical" EDMA3CHAN resource, version {1,0,0}
 */
typedef struct IRES_EDMA3CHAN_Obj *IRES_EDMA3CHAN_Handle;

/**
 *  @brief      Handle to "logical" EDMA3CHAN resource, version {2,0,0}
 */
typedef struct IRES_EDMA3CHAN2_Obj *IRES_EDMA3CHAN2_Handle;

/**
 * @brief       Representation of actual PaRam hardware registers
 *
 * @sa  http://processors.wiki.ti.com/index.php/EDMA3
 */
/* Note that the field descriptions were originally taken from SPRU996. */
typedef struct IRES_EDMA3CHAN_PaRamStruct {
    unsigned int opt;                /**< Channel options.
                                      *
                                      *   @remarks  Transfer configuration
                                      *             options.
                                      */
    unsigned int src;                /**< Channel source address.
                                      *
                                      *   @remarks  The byte address from which
                                      *             data is transferred.
                                      */
    unsigned short acnt;             /**< Count for first dimension.
                                      *
                                      *   @remarks  Unsigned value specifying
                                      *             the number of contiguous
                                      *             bytes within an array
                                      *             (first dimention of the
                                      *             transfer).
                                      *
                                      *   @remarks  Valid values range from
                                      *             1 to 65535 inclusive.
                                      */
    unsigned short bcnt;             /**< Count for second dimension.
                                      *
                                      *   @remarks  Unsigned value specifying
                                      *             the number of arrays in a
                                      *             frame, where an array is
                                      *             @c acnt bytes.
                                      *
                                      *   @remarks  Valid values range from
                                      *             1 to 65535 inclusive.
                                      */
    unsigned int dst;                /**< Channel destination address.
                                      *
                                      *   @remarks  The byte address to which
                                      *             data is transferred.
                                      */
    unsigned short srcElementIndex;  /**< Source @c bcnt index.
                                      *
                                      *   @remarks  Signed value specifying
                                      *             the byte address offset
                                      *             between source arrays within
                                      *             a frame (2nd dimension).
                                      *
                                      *   @remarks  Valid values range from
                                      *             -32768 to 32767 inclusive.
                                      */
    unsigned short dstElementIndex;  /**< Destination @c bcnt index.
                                      *
                                      *   @remarks  Signed value specifying
                                      *             the byte address offset
                                      *             between destination arrays
                                      *             within a frame (2nd
                                      *             dimension).
                                      *
                                      *   @remarks  Valid values range from
                                      *             -32768 to 32767 inclusive.
                                      */
    unsigned short link;             /**< Link address.
                                      *
                                      *   @remarks  The PaRAM address containing
                                      *             the PaRAM set to be linked
                                      *             (copied from) when the
                                      *             current PaRAM set is
                                      *             exhausted.
                                      *
                                      *   @remarks  A value of 0xffff specifies
                                      *             a null link.
                                      */
    unsigned short bCntrld;          /**< @c bcnt reload.
                                      *
                                      *   @remarks  The count value used to
                                      *             reload @c bcnt when @c bcnt
                                      *             decrements to 0 (TR is
                                      *             submitted for the last
                                      *             array in 2nd dimension).
                                      *
                                      *   @remarks  This is only relevant in
                                      *             A-synchronized transfers.
                                      */
    unsigned short srcFrameIndex;    /**< Source ccnt index.
                                      *
                                      *   @remarks  Signed value specifying the
                                      *             byte address offset between
                                      *             frames within a block (3rd
                                      *             dimension).
                                      *
                                      *   @remarks  Valid values range from
                                      *             -32768 to 32767 inclusive.
                                      *
                                      *   @remarks  For A-synchronized
                                      *             transfers, the byte address
                                      *             offset from the beginning
                                      *             of the last source array in
                                      *             a frame to the beginning of
                                      *             the first source array in
                                      *             the next frame.
                                      *
                                      *   @remarks  For AB-synchronized
                                      *             transfers, the byte address
                                      *             offset from the beginning
                                      *             of the first source array
                                      *             in a frame to the beginning
                                      *             of the first source array
                                      *             in the next frame.
                                      */
    unsigned short dstFrameIndex;    /**< Destination ccnt index.
                                      *
                                      *   @remarks  Signed value specifying the
                                      *             byte address offset between
                                      *             frames within a block (3rd
                                      *             dimension).
                                      *
                                      *   @remarks  Valid values range from
                                      *             -32768 to 32767 inclusive.
                                      *
                                      *   @remarks  For A-synchronized
                                      *             transfers, the byte address
                                      *             offset from the beginning
                                      *             of the last destination
                                      *             array in a frame to the
                                      *             beginning of the first
                                      *             destination array in the
                                      *             next frame.
                                      *
                                      *   @remarks  For AB-synchronized
                                      *             transfers, the byte address
                                      *             offset from the beginning
                                      *             of the first destination
                                      *             array in a frame to the
                                      *             beginning of the first
                                      *             destination array in the
                                      *             next frame.
                                      */
    unsigned short ccnt;             /**< Count for 3rd dimension
                                      *
                                      *   @remarks  Unsigned value specifying
                                      *             the number of frames in a
                                      *             block, where a frame is
                                      *             @c bcnt arrays of @c acnt
                                      *             bytes.
                                      *
                                      *   @remarks  Valid values range from
                                      *             1 to 65535 inclusive.
                                      */
    unsigned short rsvd;             /**< Reserved. */
} IRES_EDMA3CHAN_PaRamStruct;


/**
 *  @brief      EDMA3 Linked Transfer Protocol Arguments definition.
 *
 *  @remarks    When requesting resources on a device on which DCHMAP feature
 *              does not exist, please follow these rules:
 *              -# Break up requests into LOGICAL channel requests and requests
 *              for PaRams.
 *              -# Logical Qdma/Edma  channel => Q/E channel + PaRam + TCC
 *              -# Avoid requesting EDMA3 resources of specific number, for
 *              most transfers an "ANY" type request should be sufficient
 *              -# For linked transfers, request a Logical channel in one
 *              descriptor, and "N" contiguous Params in another descriptor
 *              -# If a logical channel request is combined with a request for
 *              multiple Params or Tccs, this might result in an inefficient
 *              allocation of resources, and in some cases, simplifying
 *              assumptions about the resource requests may be made by the
 *              allocator.
 */
typedef struct IRES_EDMA3CHAN_ProtocolArgs {
    int     size;                 /**< Size of this structure. */
    IRES_RequestMode mode;        /**< Resource request type.
                                   *
                                   *   @sa      IRES_RequestMode
                                   */
    short   numPaRams;            /**< Number of params requested.
                                   *
                                   *   @remarks Must be between 0 and
                                   *            #IRES_EDMA3CHAN_MAXPARAMS - 1
                                   *            inclusive.
                                   */
    short   paRamIndex;           /**< Describe type of paRams required.
                                   *
                                   *   @remarks If @c numParams > 1 and
                                   *            requesting contiguous Params,
                                   *            this field indicates the start
                                   *            index of the PaRam block.
                                   *            Otherwise, set this field to
                                   *            #IRES_EDMA3CHAN_PARAM_ANY.
                                   */
    short   numTccs;              /**< Number of Tcc(s) requested.
                                   *
                                   *   @remarks Must be between 0 and
                                   *            #IRES_EDMA3CHAN_MAXTCCS -1
                                   *            inclusive.
                                   */
    short   tccIndex;             /**< The type of tccs requested.
                                   *
                                   *   @remarks If @c numParams > 1 and
                                   *            requesting contiguous Params,
                                   *            this field indicates the start
                                   *            index of the Tcc block.
                                   *            Otherwise, set this field to
                                   *            #IRES_EDMA3CHAN_TCC_ANY.
                                   */
    short   qdmaChan;             /**< QDMA channel required, if any.
                                   *
                                   *   @remarks If a QDMA channel is not
                                   *            needed, set this field to
                                   *            #IRES_EDMA3CHAN_CHAN_NONE.
                                   */
    short   edmaChan;             /**< Edma channel required if any.
                                   *
                                   *   @remarks If a QDMA channel is not
                                   *            needed, set this field to
                                   *            #IRES_EDMA3CHAN_CHAN_NONE.
                                   *
                                   *   @remarks If a single EDMA channel is
                                   *            requested with a single Tcc in
                                   *            one resource descriptor, then
                                   *            resource allocator will attempt
                                   *            to allocate
                                   *            EDMA Channel # N = Tcc # N, and
                                   *            will fail if that is
                                   *            unavailable.
                                   */
    short contiguousAllocation;   /**< Flag indicating if contiguous allocation
                                   * of PaRams and Tccs is required.
                                   */

    short shadowPaRamsAllocation;  /**< Flag indicating if shadow PaRams
                                    * need to be allocated.
                                    */
} IRES_EDMA3CHAN_ProtocolArgs;

/**
 *  @brief      Object returned to the algorithm requesting EDMA3 resources.
 *
 *  @remarks    IRES_EDMA3CHAN_Obj extends the generic IRES_Obj structure.
 *
 *  @remarks    IRES_EDMA3CHAN2_Obj corresponds to
 *              #IRES_EDMA3CHAN_PROTOCOLREVISION_1_0_0.
 *
 *  @sa         IRES_EDMA3CHAN2_Obj
 */
typedef struct  IRES_EDMA3CHAN_Obj {

    IRES_Obj ires;
    IRES_EDMA3CHAN_PaRamStruct * shadowPaRams;  /**< Actual programmed shadow
                                                 *   paRam entries.
                                                 */
    unsigned int * assignedPaRamAddresses;      /**< Physical Addresses of
                                                 *    assigned paRams.
                                                 */
    short * assignedPaRamIndices;               /**< Assigned paRam Indices */
    short * assignedTccIndices;                 /**< Assigned Tcc Indices */
    short assignedNumPaRams;                    /**< Number of assigned paRams*/
    short assignedNumTccs;                      /**< Number of assigned tccs */
    short assignedQdmaChannelIndex;             /**< Assigned QDMA channel.
                                                 *
                                                 *   @remarks   This may be
                                                 *     #IRES_EDMA3CHAN_CHAN_NONE
                                                 *              if no QDMA
                                                 *              channel was
                                                 *              requested.
                                                 */
    short assignedEdmaChannelIndex;             /**< Assigned EDMA channel.
                                                 *
                                                 *   @remarks   This may be
                                                 *     #IRES_EDMA3CHAN_CHAN_NONE
                                                 *              if no EDMA
                                                 *              channel was
                                                 *              requested.
                                                 */
    unsigned int esrBitMaskL;                   /**< Event set register bit mask
                                                 *   (low).
                                                 *
                                                 *   @remarks   Used with
                                                 *              @c esrBitMaskH
                                                 *              to trigger
                                                 *              EDMA channel
                                                 *              (if requested).
                                                 */
    unsigned int esrBitMaskH;                   /**< Event set register bit mask
                                                 *   (high).
                                                 *
                                                 *   @remarks   Used with
                                                 *              @c esrBitMaskL
                                                 *              to trigger
                                                 *              EDMA channel
                                                 *              (if requested).
                                                 */
    unsigned int iprBitMaskL;                   /**< Interrupt pending register
                                                 *   bit mask (low).
                                                 *
                                                 *   @remarks   Used with
                                                 *              @c iprBitMaskH
                                                 *              to pend on
                                                 *              transfer
                                                 *              completion.
                                                 */
    unsigned int iprBitMaskH;                   /**< Interrupt pending register
                                                 *   bit mask (high).
                                                 *
                                                 *   @remarks   Used with
                                                 *              @c iprBitMaskL
                                                 *              to pend on
                                                 *              transfer
                                                 *              completion.
                                                 */
} IRES_EDMA3CHAN_Obj;

/**
 *  @brief      Defines the shadow register part of the EDMA3 CC Register Layer.
 */
typedef struct IRES_EDMA3CHAN_EDMA3ShadowRegister {
    volatile unsigned int ER;
    volatile unsigned int ERH;
    volatile unsigned int ECR;
    volatile unsigned int ECRH;
    volatile unsigned int ESR;
    volatile unsigned int ESRH;
    volatile unsigned int CER;
    volatile unsigned int CERH;
    volatile unsigned int EER;
    volatile unsigned int EERH;
    volatile unsigned int EECR;
    volatile unsigned int EECRH;
    volatile unsigned int EESR;
    volatile unsigned int EESRH;
    volatile unsigned int SER;
    volatile unsigned int SERH;
    volatile unsigned int SECR;
    volatile unsigned int SECRH;
    volatile unsigned char RSVD0[8];
    volatile unsigned int IER;
    volatile unsigned int IERH;
    volatile unsigned int IECR;
    volatile unsigned int IECRH;
    volatile unsigned int IESR;
    volatile unsigned int IESRH;
    volatile unsigned int IPR;
    volatile unsigned int IPRH;
    volatile unsigned int ICR;
    volatile unsigned int ICRH;
    volatile unsigned int IEVAL;
    volatile unsigned char RSVD1[4];
    volatile unsigned int QER;
    volatile unsigned int QEER;
    volatile unsigned int QEECR;
    volatile unsigned int QEESR;
    volatile unsigned int QSER;
    volatile unsigned int QSECR;
    volatile unsigned char RSVD2[360];

} IRES_EDMA3CHAN_EDMA3ShadowRegister;

/**
 *  @brief      Defines the Region Enable register part of the EDMA3 CC Register
 *              Layer.
 */
typedef struct IRES_EDMA3CHAN_EDMA3DraeRegister {
    volatile unsigned int DRAE;
    volatile unsigned int DRAEH;
} IRES_EDMA3CHAN_EDMA3DraeRegister;

/**
 * @brief       Defines the EDMA3 CC Register Layout
 */
typedef struct IRES_EDMA3CHAN_EDMA3RegisterLayer {
    volatile unsigned int REV;
    volatile unsigned int CCCFG;
    volatile unsigned char RSVD0[248];
    volatile unsigned int DCHMAP[64];
    volatile unsigned int QCHMAP[8];
    volatile unsigned char RSVD1[32];
    volatile unsigned int DMAQNUM[8];
    volatile unsigned int QDMAQNUM;
    volatile unsigned char RSVD2[28];
    volatile unsigned int QUETCMAP;
    volatile unsigned int QUEPRI;
    volatile unsigned char RSVD3[120];
    volatile unsigned int EMR;
    volatile unsigned int EMRH;
    volatile unsigned int EMCR;
    volatile unsigned int EMCRH;
    volatile unsigned int QEMR;
    volatile unsigned int QEMCR;
    volatile unsigned int CCERR;
    volatile unsigned int CCERRCLR;
    volatile unsigned int EEVAL;
    volatile unsigned char RSVD4[28];
    IRES_EDMA3CHAN_EDMA3DraeRegister DRA[8];
    volatile unsigned int QRAE[8];
    volatile unsigned char RSVD5[96];
    volatile unsigned int QUEEVTENTRY[8][16];
    volatile unsigned int QSTAT[8];
    volatile unsigned int QWMTHRA;
    volatile unsigned int QWMTHRB;
    volatile unsigned char RSVD6[24];
    volatile unsigned int CCSTAT;
    volatile unsigned char RSVD7[188];
    volatile unsigned int AETCTL;
    volatile unsigned int AETSTAT;
    volatile unsigned int AETCMD;
    volatile unsigned char RSVD8[244];
    volatile unsigned int MPFAR;
    volatile unsigned int MPFSR;
    volatile unsigned int MPFCR;
    volatile unsigned int MPPAG;
    volatile unsigned int MPPA[8];
    volatile unsigned char RSVD9[2000];
    volatile unsigned int ER;
    volatile unsigned int ERH;
    volatile unsigned int ECR;
    volatile unsigned int ECRH;
    volatile unsigned int ESR;
    volatile unsigned int ESRH;
    volatile unsigned int CER;
    volatile unsigned int CERH;
    volatile unsigned int EER;
    volatile unsigned int EERH;
    volatile unsigned int EECR;
    volatile unsigned int EECRH;
    volatile unsigned int EESR;
    volatile unsigned int EESRH;
    volatile unsigned int SER;
    volatile unsigned int SERH;
    volatile unsigned int SECR;
    volatile unsigned int SECRH;
    volatile unsigned char RSVD10[8];
    volatile unsigned int IER;
    volatile unsigned int IERH;
    volatile unsigned int IECR;
    volatile unsigned int IECRH;
    volatile unsigned int IESR;
    volatile unsigned int IESRH;
    volatile unsigned int IPR;
    volatile unsigned int IPRH;
    volatile unsigned int ICR;
    volatile unsigned int ICRH;
    volatile unsigned int IEVAL;
    volatile unsigned char RSVD11[4];
    volatile unsigned int QER;
    volatile unsigned int QEER;
    volatile unsigned int QEECR;
    volatile unsigned int QEESR;
    volatile unsigned int QSER;
    volatile unsigned int QSECR;
    volatile unsigned char RSVD12[3944];
    IRES_EDMA3CHAN_EDMA3ShadowRegister SHADOW[8];
    volatile unsigned char RSVD13[4096];
    IRES_EDMA3CHAN_PaRamStruct PARAMENTRY[512];
} IRES_EDMA3CHAN_EDMA3RegisterLayer;

/**
 * @brief       Static Resource Properties
 */
typedef struct IRES_EDMA3CHAN_Properties {

    unsigned int        numDmaChannels;         /**< Total number of DMA Channel
                                                 *   supported by the EDMA3
                                                 */
    unsigned int        numQdmaChannels;        /**< Total number of QDMA
                                                 *   Channels supported by the
                                                 *  EDMA3 Controller.
                                                 */
    unsigned int        numTccs;                /**< Total number of Tccs
                                                 *   supported by the EDMA3.
                                                 */
    unsigned int        numPaRAMSets;           /**< Total number of PaRAM Sets
                                                 *   supported by the EDMA3.
                                                 */
    unsigned int        numEvtQueue;            /**< Total number of Event
                                                 *    Queues in the EDMA3.
                                                 */
    unsigned int        numTcs;                 /**< Total number of Transfer
                                                 *   Controllers (TCs) in the
                                                 *   EDMA3 Controller.
                                                 */
    unsigned int        numRegions;             /**< Number of Regions on the
                                                 *   EDMA3 controller.
                                                 */

    /**
     * @brief  Channel mapping existence
     *
     * A value of 0 (No channel mapping) implies that there is fixed association
     * for a channel number to a parameter entry number or, in other words,
     * PaRAM entry n corresponds to channel n.
     */
    unsigned short dmaChPaRAMMapExists;

    unsigned short memProtectionExists;         /**< Existence of memory
                                                 *   protection feature.
                                                 */

    IRES_EDMA3CHAN_EDMA3RegisterLayer *globalRegs; /**< Pointer to Global
                                                 *   Register region of CC
                                                 *   Registers.
                                                 */
} IRES_EDMA3CHAN_Properties;

/**
 *  @brief          Describes the Destination type of DMA writes
 *                  This information is used to distribute different types of
 *                  DMA writes to different EDMA3 Queues.
 *
 *  @enumWarning
 */
typedef enum IRES_EDMA3CHAN_DmaDestType {
    INTMEMORY0 = 0,
    INTMEMORY1 = 1,
    INTMEMORY2 = 2,
    EXTMEMORY0 = 3,
    EXTMEMORY1 = 4,
    EXTMEMORY2 = 5,
    OTHER0     = 6,
    OTHER1     = 7
} IRES_EDMA3CHAN_DmaDestType;

/**
 *  @brief      Object returned to the algorithm requesting EDMA3 resources.
 *
 *  @remarks    IRES_EDMA3CHAN2_Obj extends the generic IRES_Obj structure.
 *
 *  @remarks    IRES_EDMA3CHAN2_Obj corresponds to
 *              #IRES_EDMA3CHAN_PROTOCOLREVISION_2_0_0.
 *
 *  @remarks    IRES_EDMA3CHAN2_Obj has been enhanced from #IRES_EDMA3CHAN_Obj's
 *              #IRES_EDMA3CHAN_PROTOCOLREVISION_1_0_0 with the addition of the
 *              @c queueMap field.
 *
 *  @remarks    Request this version of resource by specifying
 *              revision {2,0,0} when requesting the IRES_EDMA3CHAN
 *              resource.
 *
 *  @sa         IRES_EDMA3CHAN_Obj
 */
typedef struct  IRES_EDMA3CHAN2_Obj {

    IRES_Obj ires;

    /** @copydoc IRES_EDMA3CHAN_Obj::shadowPaRams */
    IRES_EDMA3CHAN_PaRamStruct * shadowPaRams;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedPaRamAddresses */
    unsigned int * assignedPaRamAddresses;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedPaRamIndices */
    short * assignedPaRamIndices;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedTccIndices */
    short * assignedTccIndices;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedNumPaRams */
    short assignedNumPaRams;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedNumTccs */
    short assignedNumTccs;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedQdmaChannelIndex */
    short assignedQdmaChannelIndex;

    /** @copydoc IRES_EDMA3CHAN_Obj::assignedEdmaChannelIndex */
    short assignedEdmaChannelIndex;

    /** @copydoc IRES_EDMA3CHAN_Obj::esrBitMaskL */
    unsigned int esrBitMaskL;

    /** @copydoc IRES_EDMA3CHAN_Obj::esrBitMaskH */
    unsigned int esrBitMaskH;

    /** @copydoc IRES_EDMA3CHAN_Obj::iprBitMaskL */
    unsigned int iprBitMaskL;

    /** @copydoc IRES_EDMA3CHAN_Obj::iprBitMaskH */
    unsigned int iprBitMaskH;

    XDAS_Int32 * queueMap;                  /**< Write-destination to event
                                             *   queue map.
                                             *
                                             *   @remarks   This table,
                                             *              indexed by
                                             *      #IRES_EDMA3CHAN_DmaDestType,
                                             *              returns the mapping
                                             *              of types of
                                             *              DMA-write
                                             *              destinations to
                                             *              event queues.
                                             *
                                             *   @sa  IRES_EDMA3CHAN_DmaDestType
                                             */
} IRES_EDMA3CHAN2_Obj;

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif
