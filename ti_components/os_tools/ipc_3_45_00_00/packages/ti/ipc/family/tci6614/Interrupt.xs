/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 *  ======== Interrupt.xs ========
 */

var deviceSettings = {
    'TMS320TCI6614' : {
        IPCGR0:         0x02620240,
        IPCAR0:         0x02620280,
        IPCGRH:         0x0262027C,
        IPCARH:         0x026202BC,
        KICK0:          0x02620038,
        KICK1:          0x0262003C,
        INTERDSPINT:    90,
        DSPINT:         5,
    },
}
var Settings = xdc.loadCapsule('ti/sdo/ipc/family/Settings.xs');
Settings.setDeviceAliases(deviceSettings, Settings.deviceAliases);
var Hwi         = null;
var Interrupt = null;
var MultiProc   = null;

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    var settings = deviceSettings[Program.cpu.deviceName];
    if (settings == undefined) {
        this.$logError(Program.cpu.deviceName + " unsupported", this);

        /* Early return so we don't dereference settings object below */
        return;
    }

    this.IPCGR0         = settings.IPCGR0;
    this.IPCAR0         = settings.IPCAR0;
    this.IPCGRH         = settings.IPCGRH;
    this.IPCARH         = settings.IPCARH;
    this.KICK0          = settings.KICK0;
    this.KICK1          = settings.KICK1;
    this.INTERDSPINT    = settings.INTERDSPINT;
    this.DSPINT         = settings.DSPINT;
}
/*
 *  ======== module$use ========
 */
function module$use()
{
    Interrupt     = this;

    Hwi         = xdc.useModule("ti.sysbios.family.c64p.Hwi");
    MultiProc   = xdc.useModule("ti.sdo.utils.MultiProc");
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    var fxnTable = Interrupt.$object.fxnTable;

    /* The function table length should be the number of IPCAR bits */
    fxnTable.length = 32;
    for (var i = 0; i < fxnTable.length; i++) {
        fxnTable[i].func = null;
        fxnTable[i].arg = 0;
    }

    mod.numPlugged = 0;
}
