/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 *  ======== Ip.xs ========
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
 *  ======== module$validate ========
 */
function module$validate()
{
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
     *  Ensure that user didn't leave "obtain IP address automatically" check
     *  box unchecked AND address field as null or "" (unchecking this checkbox
     *  implies that the user wants a static IP, however if the user didn't
     *  enter one, the app will still run as a DHCP client due to the original
     *  design of setting address="" for DHCP Client
     */
    if ((this.address == "null" || this.address == null || this.address == "")
            && this.autoIp == false) {
        var errMsg = "Illegal value for IP address: " +
                this.address;
        this.$logFatal(errMsg, this);
    }
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

    var GetSet = xdc.module("xdc.services.getset.GetSet");

    // ensure that changes to any config trigger updates to GUI
    GetSet.init(this);

    // trigger updateDhcpClientFlags() when the user enables/disables any flag
    GetSet.onSet(this, "IfIdXValid",    updateDhcpClientFlags);
    GetSet.onSet(this, "ResolveIP",     updateDhcpClientFlags);
    GetSet.onSet(this, "CallByIP",      updateDhcpClientFlags);
    GetSet.onSet(this, "RestartIPTerm", updateDhcpClientFlags);

    // run it once to ensure mode is initialized
    updateDhcpClientFlags("dhcpClientMode", this.dhcpClientMode);

    // trigger updateIpAddress() when the user enables/disables the auto IP box
    GetSet.onSet(this, "autoIp", updateIpAddress);

    // run it once to ensure 'address' is initialized
    updateDhcpClientFlags("autoIp", this.autoIp);

    // trigger validateIpAddress() when the user enters a static address
    GetSet.onSet(this, "address", validateIpAddress);

    // trigger validateIpAddress() when the user enters an IP mask
    GetSet.onSet(this, "mask", validateIpAddress);

    // trigger validateIpAddress() when the user enters a gateway IP address
    GetSet.onSet(this, "gatewayIpAddr", validateIpAddress);
}

/*
 *  ======== updateDhcpClientFlags ========
 *
 *  This function runs each time the user checks or unchecks one of the core run
 *  flags checkboxes.  It then updates the 'mode' variable to be the result of
 *  OR-ing all checked flags together.  If a flag is un-checked, the code
 *  clears that flags bits (this is to handle the case of the user first
 *  checking a checkbox, and then un-checking it).
 */
function updateDhcpClientFlags(field, value)
{
    var Ip = xdc.module("ti.ndk.config.Ip");

    if (this.IfIdXValid) {
        // the user checked the IFIDXVALID box, so turn on those bits
        this.dhcpClientMode |= Ip.CIS_FLG_IFIDXVALID;
    }
    else {
        // the user un-checked the IFIDXVALID box, so turn off those bits
        this.dhcpClientMode &= ~(Ip.CIS_FLG_IFIDXVALID);
    }

    if (this.ResolveIP) {
        // the user checked the RESOLVEIP box, so turn on those bits
        this.dhcpClientMode |= Ip.CIS_FLG_RESOLVEIP;
    }
    else {
        // the user un-checked the RESOLVEIP box, so turn off those bits
        this.dhcpClientMode &= ~(Ip.CIS_FLG_RESOLVEIP);
    }

    if (this.CallByIP) {
        // the user checked the CALLBYIP box, so turn on those bits
        this.dhcpClientMode |= Ip.CIS_FLG_CALLBYIP;
    }
    else {
        // the user un-checked the CALLBYIP box, so turn off those bits
        this.dhcpClientMode &= ~(Ip.CIS_FLG_CALLBYIP);
    }

    if (this.RestartIPTerm) {
        // the user checked the RESTARTIPTERM box, so turn on those bits
        this.dhcpClientMode |= Ip.CIS_FLG_RESTARTIPTERM;
    }
    else {
        // the user un-checked the RESTARTIPTERM box, so turn off those bits
        this.dhcpClientMode &= ~(Ip.CIS_FLG_RESTARTIPTERM);
    }
}

/*
 *  ======== updateIpAddress ========
 *
 *  This function runs each time the user checks or unchecks the checkbox
 *  labeled "obtain IP address automatically" (config var 'autoIp').
 *  
 *  The original logic of the Ip module is to use DHCP to get an IP address if
 *  the address field is the empty string or null.  So, this setter ensures that
 *  Ip.address is "" or null when that the check box is checked to cause the
 *  DHCP client code to be generated by the Ip.xdt template.
 *
 *  If the user un-checks the check box, the previous value of Ip.address is
 *  restored.
 */
function updateIpAddress(field, value)
{
    var Ip = xdc.module("ti.ndk.config.Ip");

    /*
     *  previousIp is a static variable.  This check will be true on the first
     *  run of this function, and will initialize previousIp in this case.
     */
    if (typeof(updateIpAddress.previousIp) == 'undefined') {
        updateIpAddress.previousIp = "192.168.1.2";
    }

    // The user checked the check box
    if (value == true) {
        /*
         *  User wants to obtain IP addr automatically.  Set IP address = "".
         *  Save previous IP addr if user entered one.
         */
        if (Ip.address == "") {
            updateIpAddress.previousIp = "";
        }
        else if (Ip.address == null || Ip.address == "null") {
            updateIpAddress.previousIp = "null";
        }
        else {
            // user entered an address. Save the value they entered
            updateIpAddress.previousIp = Ip.address;

            // set address to "" to allow DHCP client code to generate
            Ip.address = "";
        }
    }
    else {
        // user un-checked the check box. Restore IP.address to its prev value
        Ip.address = updateIpAddress.previousIp;
    }
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
    var Ip = xdc.module("ti.ndk.config.Ip");
    /*
     *  Since Ip.address == "" or == null results in DHCP Client mode, we must
     *  determine if the user has set the address field to ""/null, or if the
     *  config system has set it.  If the user did this, it is an error.  If the
     *  system did this, we must allow it.
     */
    if (!(Ip.autoIp) &&
            (Ip.address == "" || Ip.address == null || Ip.address == "null")) {
        /*
         *  The user has set address to ""/null while leaving autoIp unchecked.
         *  Must protect against empty or null static IP, as this results in
         *  app running as a DHCP client when the user wants a static IP!
         */
        throw ("Error: Invalid IP address!");
    }
    else if (Ip.address == "" || Ip.address == null || Ip.address == "null" ||
            Ip.address.toLowerCase() == "none") {
        // config system erased address to enable DHCP Client mode, do nothing.
        return;
    }
    else {
        // check IP address format
        if (!(Ip.address.match(IP_V4_ADDRESS_PATTERN))) {
            throw ("Error: Invalid IP address!");
        }
        else {
            // IP valid
            return;
        }
    }
}
