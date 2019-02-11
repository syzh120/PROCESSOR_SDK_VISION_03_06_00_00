/*
 * Copyright (c) 2010-2012, Texas Instruments Incorporated
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

import xdc.runtime.IHeap;

/*!
 *  ======== ECPY ========
 *  EDMA functional layer library.
 */

@Template("./ECPY.xdt")
metaonly module ECPY {

    config Bool cachedIresMode = true;

    /*!
     *  ======== persistentAllocFxn ========
     *  Function for allocating persistent memory for ECPY's
     *  implementation's internal objects and for allocating memory for
     *  ECPY handle objects.
     *
     *  The signature of the persistent alloc function is:
     *      extern Bool persistentAllocFxn(IALG_MemRec * memTab, Int numRecs);
     */
    config String persistentAllocFxn = null;

    /*!
     *  ======== persistentFreeFxn ========
     *  Function for freeing persistent memory allocated by ECPY.
     *
     *  The signature of hte persistentFreeFxn is:
     *
     *      extern Void persistentFreeFxn(IALG_MemRec *memTab, Int numRecs);
     */
    config String persistentFreeFxn = null;

    /*!
     *  ======== scratchAllocFxn ========
     *  Function for allocating scratch memory for ECPY Handle.
     *  The scratch memory can be overlayed with other algorithm instance's
     *  handle's that are created in the same scratch group to reduce footprint
     *  in high-density multi-channel environments.
     *
     *  The signature of the shared allocation function is:
     *
     *      extern Bool scratchAllocFxn(IALG_Handle alg, Int scratchId,
     *                                  IALG_MemRec * memTab, Int numRecs);
     */
    config String scratchAllocFxn = null;

    /*!
     *  ======== scratchFreeFxn ========
     *  Function for freeing scratch memory allocated by ECPY.
     *
     *  The signature of the scratchFreeFxn is:
     *
     *      extern Void scratchFreeFxn(Int mutexId, Void *addr, UInt size);
     */
    config String scratchFreeFxn = null;

    /*!
     *  ======== getScratchIdFxn ========
     *  Function for obtaining scratchId associated with IALG_Handle
     *  used for creating the algorithm instance.
     *  When set to null, ECPY assumes scratchId => -1
     *
     *  The signature of the getScratchIdFxn is:
     *
     *      extern Int DSKT2_getScratchId(IALG_Handle alg);
     */
    config String getScratchIdFxn = null;
}
/*
 *  @(#) ti.sdo.fc.ecpy; 1, 0, 0,10; 8-26-2010 17:48:49; /db/atree/mk/fc-n13x/src/
 */
