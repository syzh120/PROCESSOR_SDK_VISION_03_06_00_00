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
 * */
/*
 *  ======== Global.xs ========
 *
 */

/*
 *  ======== module$validate ========
 */
function module$validate()
{
}

/*
 *  ======== module$meta$init ========
 *  This function is called just once when the package containing this
 *  file is first imported.
 */
function module$meta$init() 
{
    if (xdc.om.$name != "cfg") {
        return;
    }

    /* change defaults for M3 to decrease footprint */
    var tname  = Program.build.target.name;
    var suffix = Program.build.target.suffix;

    if (tname == "M3" || tname == "M4" || tname == "M4F") {
        this.lowTaskStackSize   = 2048;
        this.normTaskStackSize  = 2048;
        this.highTaskStackSize  = 2048;
        this.ndkThreadStackSize = 2048;
        this.pktNumFrameBufs    = 16;
        this.memRawPageCount    = 8;
        this.pbmDataSection     = ".bss:NDK_PACKETMEM";
        this.memDataSection     = ".bss:NDK_MMBUFFER";
    }

    /* Ensure the BIOS family cache delegates have been set up */
    xdc.loadPackage("ti.sysbios.family");

    /*
     * Determine if this processor has cache or not.  Set Ethernet frame buffer
     * size as close to 1514 octet standard as possible, depending on core:
     */
    var Settings = xdc.module("ti.sysbios.family.Settings");
    var CacheDelegate = Settings.getDefaultCacheDelegate();
    if (CacheDelegate == null) {

        /*
         * No cache on this proc, use non cache aligned value of 1514 (this
         * will help save space on memory limited MCU devices whose cores
         * do not have cache, such as M3 on Concerto).
         */
        this.pktSizeFrameBuf    = 1514;
    }
}

/*
 *  ======== module$use ========
 *  
 *  module$use() is called after the user's config script.  Changes to the
 *  configuration are allowed to be made at this time.  This method will
 *  validate the user's configuration settings.
 */
function module$use(mod, params)
{
    var Task = xdc.module('ti.sysbios.knl.Task');

    /*
     *  *** Verify Task Priority levels are legal ***
     */

    // Negative priority levels not allowed.  (negative pri = task blocked)
    if (this.lowTaskPriLevel < 0) {
        var errMsg = "Illegal value for Global configuration parameter " +
                "\'lowTaskPriLevel\': \'" + this.lowTaskPriLevel + "\'.  NDK " +
                "priority levels cannot be negative";
        this.$logFatal(errMsg, this);
    }

    if (this.normTaskPriLevel < 0) {
        var errMsg = "Illegal value for Global configuration parameter " +
                "\'normTaskPriLevel\': \'" + this.normTaskPriLevel + "\'.  " +
                "NDK priority levels cannot be negative";
        this.$logFatal(errMsg, this);
    }

    if (this.highTaskPriLevel < 0) {
        var errMsg = "Illegal value for Global configuration parameter " +
                "\'highTaskPriLevel\': \'" + this.highTaskPriLevel + "\'.  " +
                "NDK priority levels cannot be negative";
        this.$logFatal(errMsg, this);
    }

    if (this.kernTaskPriLevel < 0) {
        var errMsg = "Illegal value for Global configuration parameter " +
                "\'kernTaskPriLevel\': \'" + this.kernTaskPriLevel + "\'.  " +
                "NDK priority levels cannot be negative";
        this.$logFatal(errMsg, this);
    }

    /*
     *  Ensure that:
     *  
     * lowTaskPriLevel < normTaskPriLevel < highTaskPriLevel < kernTaskPriLevel
     *  
     */
    if (this.lowTaskPriLevel >= this.normTaskPriLevel) {
        var errMsg = "Illegal values for Global configuration parameters " +
                "\'lowTaskPriLevel\': \'" + this.lowTaskPriLevel +
                "\' and \'normTaskPriLevel\': \'" + this.normTaskPriLevel +
                ".  NDK priority levels must obey the relationship: " + 
                "lowTaskPriLevel < normTaskPriLevel < highTaskPriLevel < " +
                "kernTaskPriLevel";
        this.$logFatal(errMsg, this);
    }


    if (this.normTaskPriLevel >= this.highTaskPriLevel) {
        var errMsg = "Illegal values for Global configuration parameters " +
                "\'normTaskPriLevel\': \'" + this.normTaskPriLevel +
                "\' and \'highTaskPriLevel\': \'" + this.highTaskPriLevel +
                ".  NDK priority levels must obey the relationship: " + 
                "lowTaskPriLevel < normTaskPriLevel < highTaskPriLevel < " +
                "kernTaskPriLevel";
        this.$logFatal(errMsg, this);
    }

    if (this.highTaskPriLevel >= this.kernTaskPriLevel) {
        var errMsg = "Illegal values for Global configuration parameters " +
                "\'highTaskPriLevel\': \'" + this.highTaskPriLevel +
                "\' and \'kernTaskPriLevel\': \'" + this.kernTaskPriLevel +
                ".  NDK priority levels must obey the relationship: " + 
                "lowTaskPriLevel < normTaskPriLevel < highTaskPriLevel < " +
                "kernTaskPriLevel";
        this.$logFatal(errMsg, this);
    }


    /*
     *  Issue a warning if any priority level is equal to 0, as this is
     *  reserved for the idle Task.  (This is not an error).
     */

    if (this.lowTaskPriLevel == 0) {
        var errMsg = "Zero value for Global configuration parameter " +
                "\'lowTaskPriLevel\': \'" + this.lowTaskPriLevel + "\'.  " +
                "Priority zero should be reserved for the DSP/BIOS Idle Task.";
        this.$logWarning(errMsg, this);
    }

    if (this.normTaskPriLevel == 0) {
        var errMsg = "Zero value for Global configuration parameter " +
                "\'normTaskPriLevel\': \'" + this.normTaskPriLevel + "\'.  " +
                "Priority zero should be reserved for the DSP/BIOS Idle Task.";
        this.$logWarning(errMsg, this);
    }

    if (this.highTaskPriLevel == 0) {
        var errMsg = "Zero value for Global configuration parameter " +
                "\'highTaskPriLevel\': \'" + this.highTaskPriLevel + "\'.  " +
                "Priority zero should be reserved for the DSP/BIOS Idle Task.";
        this.$logWarning(errMsg, this);
    }

    if (this.kernTaskPriLevel == 0) {
        var errMsg = "Zero value for Global configuration parameter " +
                "\'kernTaskPriLevel\': \'" + this.kernTaskPriLevel + "\'.  " +
                "Priority zero should be reserved for the DSP/BIOS Idle Task.";
        this.$logWarning(errMsg, this);
    }

    /*
     *  Issue an error if any priority value is greater than the highest value
     *  allowed.
     */
    if (this.kernTaskPriLevel > Task.numPriorities) {

        var errMsg = "Illegal value for Global configuration parameter " +
                "\'kernTaskPriLevel\': \'" + this.kernTaskPriLevel + "\'.  " +
                "NDK priority levels must be less than the maximum number of " +
                "priorities allowed by the \'ti.sysbios.knl.Task\' module: " +
                Task.numPriorities;
        this.$logWarning(errMsg, this);
    }


    /*
     *  Kernel level priority must at least highTaskPriLevel + 2 (as scheduler
     *  thread must fit at priority highTaskPriLevel + 1).
     */
    if (this.kernTaskPriLevel < (this.highTaskPriLevel + 2)) {
        var errMsg = "Illegal value for Global configuration parameters " +
                "'highTaskPriLevel': '" + this.highTaskPriLevel + "' and " +
                "'kernTaskPriLevel': '" + kernTaskPriLevel + "'.  NDK kernel " +
                "priority level must be at least two priority levels " +
                "greater than NDK high priority level.";
        this.$logFatal(errMsg, this);
    }

    /*
     *  *** Verify Task stack sizes are legal ***
     */

    // verify stack sizes are positive
    if (this.lowTaskStackSize < 0) {
        var errMsg = "Illegal value for Global configuration parameters " +
                "'lowTaskStackSize': '" + this.lowTaskStackSize + "'.  NDK " +
                "stack sizes must be non-negative.";
        this.$logFatal(errMsg, this);
    }

    if (this.normTaskStackSize < 0) {
        var errMsg = "Illegal value for Global configuration parameters " +
                "'normTaskStackSize': '" + this.normTaskStackSize + "'.  NDK " +
                "stack sizes must be non-negative.";
        this.$logFatal(errMsg, this);
    }

    if (this.highTaskStackSize < 0) {
        var errMsg = "Illegal value for Global configuration parameters " +
                "'highTaskStackSize': '" + this.highTaskStackSize + "'.  NDK " +
                "stack sizes must be non-negative";
        this.$logFatal(errMsg, this);
    }

    /*
     *  Verify user has specified a set of valid flags for configuration
     *  parameter 'multiCoreStackRunMode'.
     *
     *  'multiCoreStackRunMode' can be any of the flags specified as type
     *  'StackRunModeFlags' in Global.xdc.  Since the lowest value possible is
     *  0x1 (by specifying the STACKRUN_FLG_CORE_0 flag) and the highest value
     *  possible is 0xFFFF FFFF (by OR-ing all flags together), then any value
     *  for 'multiCoreStackRunMode' outside of the range [0x1 - 0xFFFFFFFF] is
     *  illegal.
     */

    /*
     *  If multiCoreStackRunMode is 0xFFFFFFFF, must special case this because
     *  it is read as signed int (-1).
     */
    var unsStackRunMode = this.multiCoreStackRunMode;
    if (this.multiCoreStackRunMode == -1) {
   
        // convert multiCoreStackRunMode to unsigned
        var numBitsPerInt = Program.build.target.bitsPerChar *
                Program.build.target.stdTypes.t_Int.size;

        if (numBitsPerInt == 16) {
            unsStackRunMode = 0xFFFF;
        }
        else if (numBitsPerInt == 32) {
            unsStackRunMode = 0xFFFFFFFF;
        }
        else {
            var errMsg = "Error: " + numBitsPerInt + " bit processor unsupported";
            this.$logFatal(errMsg, this);
        }
    }
    if (unsStackRunMode < this.STACKRUN_FLG_CORE_0 ||
        unsStackRunMode > 0xFFFFFFFF) {

        var errMsg = "Illegal value for Global configuration parameter " +
        "\'multiCoreStackRunMode\': \'" + unsStackRunMode + "\'.  'multiCoreStackRunMode' must be set " +
                "to one of the following flags, or a combination thereof (for up to 32 cores)" +
                "by (bitwise) OR-ing them together:\n" +
                "\tGlobal.STACKRUN_FLG_CORE_0\n" +
                "\tGlobal.STACKRUN_FLG_CORE_1\n" +
                "\t...\n" +
                "\tGlobal.STACKRUN_FLG_CORE_31";
        this.$logFatal(errMsg, this);
    }

    try {
        /* newer versions SYS/BIOS's Task cleans up terminated tasks */
        if (Task.$written('deleteTerminatedTasks') != true) {
            Task.deleteTerminatedTasks = true;
        }
        else if (Task.deleteTerminatedTasks == false) {
            var errMsg = "The NDK relies on the the SYS/BIOS Task module to " +
                    "have 'Task.deleteTerminatedTasks = true'. " + 
                    "The NDK has over-written your selection.";                
            this.$logWarning(errMsg, this);
            Task.deleteTerminatedTasks = true;
        }
    }
    catch (e) {
        var errMsg = "The version of SYS/BIOS being used does not contain " +
                "support for automatic Task clean up, which is required by " +
                "this version of the NDK.  Please update your version of " +
                "SYS/BIOS to version 6.31 or greater. (" + e + ")";
        this.$logFatal(errMsg, this);
    }
}

/*!
 *  ======== addUserAccount ========
 */
function addUserAccount(account)
{
    // add the new user account to our account table
    this.userAccounts.$add(account);
}    

