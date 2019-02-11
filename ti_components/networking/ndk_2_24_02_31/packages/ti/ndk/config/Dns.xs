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
 *  ======== Dns.xs ========
 *
 */

/*
 *  Regular expression used to validate IP address
 *
 *  ^             #  start of the line
 *  (		  #  start of group #1
 *  [01]?\\d\\d?  #  Can be one or two digits. If three digits appear, it
 *                #  must start either 0 or 1
 *                #    e.g ([0-9], [0-9][0-9],[0-1][0-9][0-9])
 *  |		  #    ...or
 *  2[0-4]\\d	  #    start with 2, follow by 0-4 and end with any digit (2[0-4][0-9]) 
 *  |             #    ...or
 *  25[0-5]       #    start with 2, follow by 5 and end with 0-5 (25[0-5]) 
 *  )		  #  end of group #2
 *  \.            #  follow by a dot "."
 *  ....          # repeat with 3 time (3x)
 *  $		  #end of the line
 */
var IP_V4_ADDRESS_PATTERN = 
        "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
        "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
        "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
        "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$";

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

    var GetSet = xdc.module("xdc.services.getset.GetSet");

    // ensure that changes to any config trigger updates to GUI
    GetSet.init(this);

    /* Trigger validateIpAddress() when the user enters an IP address */
    GetSet.onSet(this, "externDnsServIp", validateIpAddress);
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
    /*
     * use all dependent modules
     *
     * UDP/IP underlies DNS.
     */
    var Ip = xdc.useModule('ti.ndk.config.Ip');
    var Udp = xdc.useModule('ti.ndk.config.Udp');
}

/*
 *  ======== instance$meta$init ========
 *  This function is called whenever create() is called for a new instance.
 */
function instance$meta$init() 
{
    if (xdc.om.$name != "cfg") {
        return;
    }

    var GetSet = xdc.module("xdc.services.getset.GetSet");

    /* Ensure that changes to any config trigger updates to GUI */
    GetSet.init(this);

    /* Trigger updateModeFlags() when the user enables/disables any flag */
    GetSet.onSet(this, "IfIdXValid",    updateModeFlags);
    GetSet.onSet(this, "ResolveIP",     updateModeFlags);
    GetSet.onSet(this, "CallByIP",      updateModeFlags);
    GetSet.onSet(this, "RestartIPTerm", updateModeFlags);

    /* Trigger validateIpAddress() when the user enters an IP address */
    GetSet.onSet(this, "ipAddr", validateIpAddress);

    /*
     *  Must also handle reverse case - if user updates mode, make sure
     *  checkboxes in GUI reflect that.
     */
    GetSet.onSet(this, "mode", updateCheckBoxes);

    /* Run them once to ensure mode and check boxes are initialized */
    updateModeFlags("mode", this.mode);
    updateCheckBoxes("mode", this.mode);
}

/*
 *  ======== updateModeFlags ========
 *
 *  This function runs each time the user checks or unchecks one of the mode
 *  flags checkboxes.  It then updates the 'mode' variable to be the result of
 *  OR-ing all checked flags together.  If a flag is un-checked, the code
 *  clears that flags bits (this is to handle the case of the user first
 *  checking a checkbox, and then un-checking it).
 */
function updateModeFlags(field, value)
{
    var Dns = xdc.module("ti.ndk.config.Dns");

    /*
     * update temp variable to avoid calls to 'updateModeFlags' being triggered
     * multiple times.
     */
    var tempMask = this.mode;

    if (this.IfIdXValid) {
        // the user checked the IFIDXVALID box, so turn on those bits
        tempMask |= Dns.CIS_FLG_IFIDXVALID;
    }
    else {
        // the user un-checked the IFIDXVALID box, so turn off those bits
        tempMask &= ~(Dns.CIS_FLG_IFIDXVALID);
    }

    if (this.ResolveIP) {
        // the user checked the RESOLVEIP box, so turn on those bits
        tempMask |= Dns.CIS_FLG_RESOLVEIP;
    }
    else {
        // the user un-checked the RESOLVEIP box, so turn off those bits
        tempMask &= ~(Dns.CIS_FLG_RESOLVEIP);
    }

    if (this.CallByIP) {
        // the user checked the CALLBYIP box, so turn on those bits
        tempMask |= Dns.CIS_FLG_CALLBYIP;
    }
    else {
        // the user un-checked the CALLBYIP box, so turn off those bits
        tempMask &= ~(Dns.CIS_FLG_CALLBYIP);
    }

    if (this.RestartIPTerm) {
        // the user checked the RESTARTIPTERM box, so turn on those bits
        tempMask |= Dns.CIS_FLG_RESTARTIPTERM;
    }
    else {
        // the user un-checked the RESTARTIPTERM box, so turn off those bits
        tempMask &= ~(Dns.CIS_FLG_RESTARTIPTERM);
    }

    /*
     * update mode with new settings. This ensures that 'updateModeFlags' is
     * invoked only once here:
     */
    this.mode = tempMask;
}

/*
 *  ======== updateCheckBoxes ========
 *
 *  This function runs each time the user changes the mode variable, so that the
 *  flags checkboxes in the GUI match the value of mode.
 */
function updateCheckBoxes(field, value)
{
    var Dns = xdc.module("ti.ndk.config.Dns");

    var tempIfId      = false;
    var tempResolveIp = false;
    var tempCallIp    = false;
    var tempRestartIp = false;

    if (this.mode & Dns.CIS_FLG_IFIDXVALID) {
        // this flag was set in the mode param, check the IFIDXVALID check box
        tempIfId = true;
    }

    if (this.mode & Dns.CIS_FLG_RESOLVEIP) {
        // this flag was set in the mode param, check the RESOLVEIP check box
        tempResolveIp = true;
    }

    if (this.mode & Dns.CIS_FLG_CALLBYIP) {
        // this flag was set in the mode param, check the CALLBYIP check box
        tempCallIp = true;
    }

    if (this.mode & Dns.CIS_FLG_RESTARTIPTERM) {
        // this flag was set in the mode param, check the RESTARTIPTERM check box
        tempRestartIp = true;
    }

    this.IfIdXValid    = tempIfId;
    this.ResolveIP     = tempResolveIp;
    this.CallByIP      = tempCallIp;
    this.RestartIPTerm = tempRestartIp;
}

/*
 *  ======== validateIpAddress ========
 *  This function runs each time Ip.address is updated.
 *
 *  Note: it is not necessary to validate IPv6 addresses here because the NDK
 *  only supports adding IPv6 at runtime.  User must first bring up the board
 *  with an IPv4 address, then use runtime APIs (or telnet console commands)
 *  to obtain an IP address.
 */
function validateIpAddress(field, value)
{

    // must specify exact address of external DNS server */
    // check IP address format
    if (!(value.match(IP_V4_ADDRESS_PATTERN))) {

        // INADDR_ANY is OK for ipAddr config param
        if (field.match("ipAddr") && value.match("INADDR_ANY")) {
            return;
        }
        else {
            throw ("Error: Invalid IP address!");
        }
    }
    else {
        // IP valid
        return;
    }
}
