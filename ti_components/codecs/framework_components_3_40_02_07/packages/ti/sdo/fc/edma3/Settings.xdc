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
 * ======== Settings.xdc ========
 * Configuration for the EDMA3 module to be able to create handles to the
 * resource handles for various scratch groups.
 */


@Template("./Settings.xdt")

metaonly module Settings {

    /*!
     * ======== controllerId =======
     * Id of the EDMA3 instance that will be used to request resources from.
     * If this platform is natively supported by this module and the default
     * configurations are being used, this Id is used to determine, which EDMA3
     * instance to request resources from.
     */
    config UInt controllerId = 0;

    /*!
     * ======== region ========
     * Id of the EDMA3 Region we will program with the assigned Resources etc.
     * If this platform is natively supported by this module and the default
     * configurations are being used, region number is used to determine,
     * which region of the EDMA3 configuration to request resources from.
     * On most heterogenous devices:
     * Region number 1 usually corresponds to DSP.
     * Region number 0 usually corresponds to ARM.
     * On most multicore devices:
     * Region number n corresponds to Core number n.
     */
    config UInt region = 1;

    /*!
     * ======== globalConfig ========
     * If a platform is not natively supported by this module or if the default
     * number of EDMA3 hardware resources is to be overriden for some reason,
     * this configuration is required to set the SOC specific details of EDMA3
     * Set this parameter to the name of a structure of type
     * EDMA3_GblConfigParams (defined in edma3_config.h).
     * far EDMA3_GblConfigParams _globalConfig;
     *
     *  Note:- This is required to be supplied ONLY if application is built for      *  DSP target.
     */
    config String globalConfig = null;

    /*!
     * ======== regionConfig ========
     * If a platform is not natively supported by this module or if the default
     * number of resources available to a particular region are to be overriden,
     * region specific configuration can be specified directly via this
     * parameter.
     * Set this parameter to the name of a structure of type
     * EDMA3_InstanceInitConfg (defined in edma3_config.h).
     * far EDMA3_InstanceInitConfg _regionConfig;
     *
     *  Note:- This is required to be supplied ONLY if application is built for      *  DSP target.
     */
    config String regionConfig = null;

    /*!
     * ======= createRMObj =======
     * Boolean value indicating if EDMA3 LLD RM object needs to be created by
     * FC or if it is going to be supplied by the driver or app etc.
     * TRUE by default. Should be set to FALSE in cases where the LLD is being
     * used, or if the app is supplying the semaphore functions for RM creation.
     */
    config bool createRMObj = true;

    /*!
     * ======== contiguousPaRams ========
     * Boolean value indicating if PaRams assigned to scratch groups need to be
     * contiguous or not
     */
    config bool contiguousPaRams = true;

    const UInt EDMA3_MAXGROUPS = 20;  /*! Maximum number of groups for sharing
                                 EDMA3 resources. */
    const UInt EDMA3_MAXTCS = 8;

    /*!
     * ======== globalInit ========
     * This flag decides if EDMA3 global registers and PaRam entries will be
     * initialized by this module.
     * If building this app for a system where ARM-side (or other) drivers might     * perform EDMA3 intialization, set this to false so it doesn't overwrite
     * the ARM-side setup.
     *
     *  Note:- This is required to be supplied ONLY if application is built for
     *  DSP target.
     */
    config Bool globalInit = false;


    /*!
     * ======== maxTccs ========
     * Arrays containing the maximum number of TCCs that will be assigned to
     * groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     *
     *  Note:- This is required to be supplied ONLY if application is built for
     *  DSP target.
     */
    config UInt maxTccs[EDMA3_MAXGROUPS];

    /*!
     * ======== maxPaRams ========
     * Arrays containing the maximum number of PaRams that will be assigned to
     * groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     *
     *  Note:- This is required to be supplied ONLY if application is built for
     *  DSP target.
     */
    config UInt maxPaRams[EDMA3_MAXGROUPS];

    /*!
     * ======== maxEdmaChannels ========
     * Array containing the maximum number of Edma Channels that will be
     * assigned to groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     * On devices where DCHMAP doesn't exist, it is recommended to request as
     * many channels as PaRams requested
     *
     *  Note:- This is required to be supplied ONLY if application is built for
     *  DSP target.
     */
    config UInt maxEdmaChannels[EDMA3_MAXGROUPS];

    /*!
     * ======== maxQdmaChannels ========
     * Array containing the maximum number of Qdma Channels that will be
     * assigned to groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     *
     *  Note:- This is required to be supplied ONLY if application is built for
     *  DSP target.
     */
    config UInt maxQdmaChannels[EDMA3_MAXGROUPS];

    /*!
     *  ======== persistentAllocFxn ========
     *  Function for allocating persistent memory for RMAN's and other IRESMAN
     *  implementation's internal objects.
     *
     *  Note:- This is required to be supplied ONLY if
     *  {@link ti.sdo.fc.rman.RMAN#useDSKT2} is set to `false`.
     */
    config String persistentAllocFxn = null;

    /*!
     *  ======== persistentFreeFxn ========
     *  Function for freeing persistent memory used by RMAN and other IRESMAN
     *  implementation's internal objects.
     *
     *  Note:- This is required to be supplied ONLY if
     *  {@link ti.sdo.fc.rman.RMAN#useDSKT2} is set to `false`.
     */
    config String persistentFreeFxn = null;

    /*!
     *  ======== semCreateFxn ========
     * Function to create semaphores used by various individual resource
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void * _semCreate(Int key, Int count);
     */
    config String semCreateFxn = null;

    /*!
     *  ======== semDeleteFxn ========
     * Function to delete semaphores used by various individual resource
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Void _semDelete(Void * sem);
     */
    config String semDeleteFxn = null;

    /*!
     *  ======== semPendFxn ========
     * Function to pend on semaphores used by various resource manager(s)
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Int _semPend(Void * sem, UInt32 timeout);
     */
    config String semPendFxn = null;

    /*!
     *  ======== semPostFxn ========
     * Function to post on Semaphores used by various resource manager(s)
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void _semPost(Void * sem);
     */
    config String semPostFxn = null;

    /*!
     * ======== maxAlgs ========
     * Maximum number of algorithm instances that will be created
     */
    config UInt maxAlgs = 32;

    /*!
     * ========= maxRequests ======
     * Maximum number of "active" resource requests that will be
     * made by the algorithms in each scratch group
     */
    config UInt maxRequests = 64;

    /*!
     * ======= intMemoryQ =======
     * Configuration to setup Queue # to be used to internal memory writes,
     * Multiple Queues can be configured for same type of memory writes to allow
     * load balancing for performance.
     * This is required to be supplied ONLY if application is built for DSP
     * target .
     */
    config UInt intMemoryQ0;
    config UInt intMemoryQ1;
    config UInt intMemoryQ2;

    /*!
     * ======= extMemoryQ =======
     * Configuration to setup Queue # to be used to external memory writes
     * Multiple Queues can be configured for same type of memory writes to allow
     * load balancing for performance.
     * This is required to be supplied ONLY if application is built for DSP
     * target .
     */
    config UInt extMemoryQ0;
    config UInt extMemoryQ1;
    config UInt extMemoryQ2;

    /*
     * ======= otherQ =======
     * Configuration to setup Queue # for "Other", possibly peripheral, writes.
     * Multiple Queues can be configured for same type of memory writes to allow
     * load balancing for performance.
     * This is required to be supplied ONLY if application is built for DSP
     * target .
     */
    config UInt otherQ0;
    config UInt otherQ1;

    /*!
     * ======== eventQueueSetup ========
     * This flag decides if EDMA3 global registers related to Transfer
     * Controller/Queues should be programmed.
     * If using on a device where ARM-side drivers might perform the
     * intialization, set this to false so it doesn't overwrite the ARM-side
     * setup.
     * This is required to be supplied ONLY if application is built for
     * DSP target.
     */
    config Bool eventQueueSetup = false;

    /*!
     * ======= defaultQ =======
     * Default queue assignment for all channels allocated for this app. When
     * channels are first granted to the algorithm, they will be mapped to this
     * Event Queue.
     */
    config UInt defaultQ = 0;

    /*
     * ======= queueTCMap =======
     * Maps Event queues to TCs. Default mapping is from Queue #n to TC #n
     * If modifying this, please ensure that queue setup for different types
     * of writes has been adjusted accordingly.
     * By default Queue # N gets mapped to TC # N
     * If certain queue mappings are not to be overridden, set those entries in
     * array to -1.
     */
    config Int queueTCMap[EDMA3_MAXTCS];

    /*
     * ======= queuePriority =======
     * Assigns priority to different queues. This priority has an effect during
     * arbitration of transfers within the SCR.
     * For consistency, program the higher priority queues (lower #) with a
     * higher priority (lower #).
     * Note:- The higher priority queues (lower #) also get serviced first by
     * the transfer controller.
     * By default, Queue # N, has priority# N.
     * If certain queue priorities are not to be overridden, set entries in
     * array to -1.
     */
    config Int queuePriority[EDMA3_MAXTCS];

    /*!
     *  ======== ipcKeyBase ========
     *  Linux only. Base value of keys of Linux IPC objects used by
     *  EDMA3. The IPC objects created by EDMA3 will use keys starting
     *  at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for EDMA3. The default value of ipcKeyBase is
     *  ascii code for "3AMD".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using EDMA3 that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x33414D44;
}
