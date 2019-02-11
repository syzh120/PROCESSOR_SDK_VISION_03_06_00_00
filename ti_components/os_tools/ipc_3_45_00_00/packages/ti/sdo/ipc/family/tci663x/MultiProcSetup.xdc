/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 */
/*
 *  ======== MultiProcSetup.xdc ========
 */

import xdc.runtime.Assert;

/*!
 *  ======== MultiProcSetup ========
 */

module MultiProcSetup
{
    /*!
     * By default the MultiProcSetup module will set the ID at startup.
     *
     * By setting this flag to false, the initialization step is suppressed.
     */
    config Bool configureProcId = true;

    /*!
     *  Assert raised when the target core is not in the MultiProc name list
     */
    config Assert.Id A_invalidProcessor  = {
        msg: "A_invalidProcessor: This core is not present in the MultiProc name list"
    };

internal:
    /*  Map the clusterId to the coreId (only for DSP processors)
     *
     *  The procMap array is indexed by clusterId. The element value
     *  is the coreId (equivalent to DNUM).
     */
    config UInt16 procMap[];

    /*  Maximum number of processors on this device
     *
     *  We consider the CortexA15 quad-core processor to be one
     *  logical processor. There are up to eight DSP processors.
     */
    config UInt16 segmentSize = 9;

    /*
     *  ======== getProcId ========
     *  Returns the MultiProc ID corresponding to the given coreId
     */
    UInt16 getProcId(UInt coreId);

    Void init();
}
