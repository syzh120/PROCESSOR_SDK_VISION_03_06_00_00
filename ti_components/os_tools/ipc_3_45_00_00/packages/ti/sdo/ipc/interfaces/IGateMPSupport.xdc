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
 */
/*
 *  ======== IGateMPSupport.xdc ========
 *
 */

import xdc.runtime.IGateProvider;

/*!
 *  ======== IGateMPSupport ========
 */
interface IGateMPSupport inherits IGateProvider
{
    /*!
     *  ======== getNumResources ========
     *  Returns the number of resources offered by the GateMP delegate
     */
    metaonly UInt getNumResources();

    /*!
     *  ======== getReservedMask ========
     *  @_nodoc
     *  Used by GateMP to query which HW resources are reserved
     */
    @DirectCall
    Bits32 *getReservedMask();

    /*!
     *  ======== sharedMemReq ========
     *  Amount of shared memory required for creation of each instance
     *
     *  The value returned by this function may depend on the cache alignment
     *  requirements for the shared region from which memory will be used.
     *
     *  @param(params)      Pointer to the parameters that will be used in
     *                      the create.
     *
     *  @a(returns)         Number of MAUs needed to create the instance.
     */
    @DirectCall
    SizeT sharedMemReq(const Params *params);

    /*!
     *  ======== getRemoteStatus$view ========
     *  @_nodoc
     *  ROV helper function that returns the status of the remote gate
     *
     *  @b(returns)     Gate status
     */
    metaonly String getRemoteStatus$view(IGateProvider.Handle handle);

instance:

    /*!
     *  Logical resource id
     */
    config UInt resourceId = 0;

    /*! @_nodoc
     *  ======== openFlag ========
     */
    config Bool openFlag = false;

    /*!
     *  ======== regionId ========
     *  @_nodoc
     *  Shared Region Id
     *
     *  The ID corresponding to the shared region in which this shared instance
     *  is to be placed.
     */
    config UInt16 regionId = 0;

    /*!
     *  ======== sharedAddr ========
     *  Physical address of the shared memory
     *
     *  This parameter is only used by GateMP delegates that use shared memory
     */
    config Ptr sharedAddr = null;

    /*!
     *  ======== create ========
     *  Create a remote gate instance.
     *
     *  A Non-NULL gate for local protection must be passed to the create
     *  call.  If no local protection is desired, a
     *  {@link xdc.runtime.GateNull} handle must be passed in.
     *
     *  @param(localGate)       Gate to use for local protection.
     */
    create(IGateProvider.Handle localGate);
}
