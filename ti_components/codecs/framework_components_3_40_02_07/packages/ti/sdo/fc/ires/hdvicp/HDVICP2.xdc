/*
 * Copyright (c) 2012 - 2013, Texas Instruments Incorporated
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
/*!
 *  ======== HDVICP2 ========
 *  HDVICP2-specific IRES Resman and Protocol Implementation
 *
 */
@Template("./HDVICP2.xdt")

metaonly module HDVICP2 inherits ti.sdo.fc.ires.IRESMAN {

    const Int MAXRESOURCES = 10;  /*! Maximum number of HDVICP2 resources
                                      this module can manage. */
    /*!
     *  ======= memoryBaseAddress =======
     *
     */
    config UInt memoryBaseAddress[MAXRESOURCES];

    /*!
     *  ======= resetControlAddress =======
     *
     */
    config UInt resetControlAddress[MAXRESOURCES];


    /*!
     *  =======  registerBaseAddress =======
     *  Base-address of the IVA-HD register space
     *
     */
    config UInt registerBaseAddress[MAXRESOURCES];

    /*!
     *  ======= configureFxn =======
     *  Function to configure the interrupt associated with the IVAHD and
     *  register a callback function.
     *
     *  Function signature of callback is:
     *  @p(code)
     *  Void _cbFunction(Void * cbArgs);
     *
     *  Function signature of configure is:
     *  @p(code)
     *  XDAS_Void _configure(IALG_Handle algHandle,
     *          IRES_HDVICP2_Obj * hdvicpHandle,
     *          IRES_HDVICP2_CallbackFxn cbFunctionPtr, XDAS_Void * cbArgs);
     */
    config String configureFxn;

    /*!
     *  ======= waitFxn =======
     *  Function to wait on the interrupt associated with the IVAHD to fire
     *
     *  Function signature is:
     *  @p(code)
     *  XDAS_UInt32 _wait(IALG_Handle algHandle,
     *          IRES_HDVICP2_Obj * hdvicpHandle,
     *          IRES_YieldContext * yieldContext);
     */
    config String waitFxn;

    /*!
     *  ======= doneFxn =======
     *  Function indicating "done".
     *
     *  This is the function called from the ISR interrupt associated with
     *  the IVAHD to  unblock the {@link #waitFxn}.
     *
     *  Function signature is:
     *  @p(code)
     *  XDAS_Void _done(IALG_Handle algHandle, IRES_HDVICP2_Obj * hdvicpHandle);
     */
    config String doneFxn;

    /*!
     *  ======= resetFxn =======
     *  Function to reset the IVAHD.
     *
     *  This is a callback function implemented by the framework and called by
     *  the codec.
     *
     *  Function signature is:
     *  @p(code)
     *  XDAS_UInt32 _reset(IALG_Handle algHandle,
     *          IRES_HDVICP2_Obj * hdvicpHandle);
     */
    config String resetFxn;


    /*!
     *  ======= clearPRCMRegister =======
     *  Boolean value that indicates whether the PRCM register needs to be
     *  cleared in the default implementation of the "reset" function
     */
    config Bool clearPRCMRegister;

    /*!
     *  ======= timeout =======
     *  Timeout value representing "Wait forever" to be used to configure the
     *  {@link #timeout} configuration below.
     */
    const UInt FOREVER = -1;

    /*!
     *  ======= timeout =======
     * Timeout setting in microseconds, used by the "waitFxn" while waiting for      * a configured IVAHD's interrupt to fire.
     */
    config UInt timeout;

    /*!
     *  ======= delegate =======
     *  Package name that implements the above configure, wait, done, reset
     *  functions for the IVA-HD.
     */
    config String delegate;

    /*!
     *  ======== semCreateFxn ========
     * Function to create semaphores used by the resource manager
     *
     *  Function signature is:
     *  @p(code)
     * Void * _semCreate(Int key, Int count);
     */
    config String semCreateFxn = null;

    /*!
     *  ======== semDeleteFxn ========
     * Function to delete semaphores used by the resource manager
     *
     *  Function signature is:
     *  @p(code)
     *  Void _semDelete(Void * sem);
     */
    config String semDeleteFxn = null;

    /*!
     *  ======== semPendFxn ========
     * Function to pend on semaphores used by the resource manager
     *
     *  Function signature is:
     *  @p(code)
     *  Int _semPend(Void * sem, unsigned int timeout);
     */
    config String semPendFxn = null;

    /*!
     *  ======== semPostFxn ========
     * Function to post on Semaphores used by the resource manager
     *
     *  Function signature is:
     *  @p(code)
     * Void _semPost(Void * sem);
     */
    config String semPostFxn = null;

    /*!
     *  ======== ipcKeyBase ========
     *  Base value of keys of Linux IPC objects used by HDVICP2.
     *
     *  This applies only to Linux-based environments. The IPC objects
     *  created by HDVICP2 will use keys starting at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for HDVICP. The default value of ipcKeyBase is
     *  ascii code for "2VDH".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using HDVICP that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x32564448;

    /*  @_nodoc */
    override config Bool autoRegister = true;

    /*
     *  ======== getHDVICP2Fxn ========
     *  Optional plug-in function that returns an IVAHD instance. If not
     *  provided, the default scheduler will be used
     *  IRES_Status (*getHDVICP2) (Int *Id, IALG_Handle alg,
     *          IRES_HDVICP2_Handle h);
     *  Note:- This API is currently experimental
     */
    /* @_nodoc */
    config String getHDVICP2Fxn;

    /*
     *  ======== freeHDVICP2Fxn ========
     *  Optional plug-in function that frees up the IVAHD instance requested.
     *  Is required if a non-NULL getHDVICP2Fxn is provided.
     *  IRES_Status (*freeHDVICP2) (Int Id, IALG_Handle alg,
     *          IRES_HDVICP2_Handle h);
     *  Note:- This API is currently experimental
     */
    /* @_nodoc */
    config String freeHDVICP2Fxn;

    /*!
     *  ======== yieldReleaseFxn ========
     */
    config String yieldReleaseFxn;

    /*!
     *  ======== yieldAcquireFxn ========
     */
    config String yieldAcquireFxn;

    /*!
     *  ======== getYieldArgsFxn ========
     */
    config String getYieldArgsFxn;

    /*!
     *  ======== maxHdvicp2ResetDelay ========
     * Maximum number of cycles to wait for HDVICP2 to reset, after a call is
     * issued.
     */
    config UInt maxHdvicp2ResetDelay = 1000;

    /*!
     *  ======= numHdvicp2 =======
     *  If catalog part does not declare peripheral information, it can be
     *  configured here. Number of IVAHD or HDVICP2s on this part
     *  @_nodoc
     */
    config UInt numHdvicp2;

    /*
     *  ======== intArray ========
     *  If catalog part does not declare peripheral information, it can be
     *  configured here. Array of length {@link #numHdvicp2}, that declares
     *  the interrupt numbers for each IVAHD.
     *  @_nodoc
     */
    config UInt intArray[8];
}
