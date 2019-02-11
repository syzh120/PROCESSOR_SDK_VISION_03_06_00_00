/*
 * Copyright (c) 2012-2016, Texas Instruments Incorporated
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
 *  ======== Watchdog.xs ========
 *
 */

var Watchdog = null;
var Core = null;
var MultiProc = null;
var Task = null;
var Swi  = null;
var taskHook = null;
var swiHook  = null;
var catalogName = null;
var timerIds = [];

if (xdc.om.$name == "cfg" || typeof(genCdoc) != "undefined") {
    var deviceTable = {
        "ti.catalog.c6000": {
            "OMAP5430": {
                "GPTimer5": {
                    name: "WdTimer5Dsp",    /* GpTimer 5 */
                    baseAddr: 0x01D38000,
                    clkCtrl: 0x4A004568,    /* Virtual address */
                    intNum:  14,
                    eventId: 51,
                },
                "GPTimer6": {
                    name: "WdTimer6Dsp",    /* GpTimer 6 */
                    baseAddr: 0x01D3A000,
                    clkCtrl: 0x4A004570,    /* Virtual address */
                    intNum:  15,
                    eventId: 52,
                },
                "GPTimer7": {
                    name: "WdTimer7Dsp",    /* GpTimer 7 */
                    baseAddr: 0x01D3C000,
                    clkCtrl: 0x4A004578,    /* Virtual address */
                    intNum:  4,
                    eventId: 53,
                },
                "GPTimer8": {
                    name: "WdTimer8Dsp",    /* GpTimer 8 */
                    baseAddr: 0x01D3E000,
                    clkCtrl: 0x4A004580,    /* Virtual address */
                    intNum:  5,
                    eventId: 54,
                },
                "Default": [
                    { name: "GPTimer6" },
                ]
            },
            "DRA7XX": {
                "GPTimer1": {
                    name: "WdTimer1Dsp",    /* GpTimer 1 */
                    baseAddr: 0x4AE18000,   /* Virtual address */
                    clkCtrl: 0x4AE07840,    /* Virtual address */
                    intNum:  14,
                    eventId: 63,
                },
                "GPTimer2": {
                    name: "WdTimer2Dsp",    /* GpTimer 2 */
                    baseAddr: 0x48032000,   /* Virtual address */
                    clkCtrl: 0x4A009738,    /* Virtual address */
                    intNum:  15,
                    eventId: 64,
                },
                "GPTimer3": {
                    name: "WdTimer3Dsp",    /* GpTimer 3 */
                    baseAddr: 0x48034000,   /* Virtual address */
                    clkCtrl: 0x4A009740,    /* Virtual address */
                    intNum:  14,
                    eventId: 65,
                },
                "GPTimer4": {
                    name: "WdTimer4Dsp",    /* GpTimer 4 */
                    baseAddr: 0x48036000,   /* Virtual address */
                    clkCtrl: 0x4A009748,    /* Virtual address */
                    intNum:  15,
                    eventId: 66,
                },
                "GPTimer5": {
                    name: "WdTimer5Dsp",    /* GpTimer 5 */
                    baseAddr: 0x48820000,   /* Virtual address */
                    clkCtrl: 0x4a005558,    /* Virtual address */
                    intNum:  14,
                    eventId: 67,
                },
                "GPTimer6": {
                    name: "WdTimer6Dsp",    /* GpTimer 6 */
                    baseAddr: 0x48822000,   /* Virtual address */
                    clkCtrl: 0x4A005560,    /* Virtual address */
                    intNum:  15,
                    eventId: 68,
                },
                "GPTimer7": {
                    name: "WdTimer7Dsp",    /* GpTimer 7 */
                    baseAddr: 0x48824000,   /* Virtual address */
                    clkCtrl: 0x4A005568,    /* Virtual address */
                    intNum:  14,
                    eventId: 69,
                },
                "GPTimer8": {
                    name: "WdTimer8Dsp",    /* GpTimer 8 */
                    baseAddr: 0x48826000,   /* Virtual address */
                    clkCtrl: 0x4A005570,    /* Virtual address */
                    intNum:  15,
                    eventId: 70,
                },
                "GPTimer9": {
                    name: "WdTimer9Dsp",    /* GpTimer 9 */
                    baseAddr: 0x4803E000,   /* Virtual address */
                    clkCtrl: 0x4A009750,    /* Virtual address */
                    intNum:  14,
                    eventId: 71,
                },
                "GPTimer10": {
                    name: "WdTimer10Dsp",   /* GpTimer 10 */
                    baseAddr: 0x48086000,   /* Virtual address */
                    clkCtrl: 0x4A009728,    /* Virtual address */
                    intNum:  15,
                    eventId: 72,
                },
                "GPTimer11": {
                    name: "WdTimer11Dsp",   /* GpTimer 11 */
                    baseAddr: 0x48088000,   /* Virtual address */
                    clkCtrl: 0x4A009730,    /* Virtual address */
                    intNum:  14,
                    eventId: 73,
                },
                "GPTimer12": {
                    name: "WdTimer12Dsp",   /* GpTimer 12 */
                    baseAddr: 0x4AE20000,   /* Virtual address */
                    clkCtrl: 0x4AE07848,    /* Virtual address */
                    intNum:  -1,
                    eventId: 75,
                },
                "GPTimer13": {
                    name: "WdTimer13Dsp",   /* GpTimer 13 */
                    baseAddr: 0x48828000,   /* Virtual address */
                    clkCtrl: 0x4A0097C8,    /* Virtual address */
                    intNum:  14,
                    eventId: 76,
                },
                "GPTimer14": {
                    name: "WdTimer14Dsp",   /* GpTimer 14 */
                    baseAddr: 0x4882A000,   /* Virtual address */
                    clkCtrl: 0x4A0097D0,    /* Virtual address */
                    intNum:  -1,
                    eventId: 77,
                },
                "GPTimer15": {
                    name: "WdTimer15Dsp",   /* GpTimer 15 */
                    baseAddr: 0x4882C000,   /* Virtual address */
                    clkCtrl: 0x4A0097D8,    /* Virtual address */
                    intNum:  -1,
                    eventId: 78,
                },
                "GPTimer16": {
                    name: "WdTimer16Dsp",   /* GpTimer 16 */
                    baseAddr: 0x4882E000,   /* Virtual address */
                    clkCtrl: 0x4A009830,    /* Virtual address */
                    intNum:  -1,
                    eventId: 81,
                },
                "Default": [
                    { name: "GPTimer10" },
                ]
            },
        },
        "ti.catalog.arm.cortexm4": {
            "OMAP5430": {
                "GPTimer3": {
                    name: "WdTimer3Ipu",    /* GpTimer 3 */
                    baseAddr: 0xA8034000,   /* Virtual address */
                    clkCtrl: 0xAA009040,    /* Virtual address */
                    intNum:  53,
                    eventId: -1,
                },
                "GPTimer4": {
                    name: "WdTimer4Ipu",    /* GpTimer 4 */
                    baseAddr: 0xA8036000,   /* Virtual address */
                    clkCtrl: 0xAA009048,    /* Virtual address */
                    intNum:  54,
                    eventId: -1,
                },
                "GPTimer9": {
                    name: "WdTimer9Ipu",    /* GpTimer 9 */
                    baseAddr: 0xA803E000,   /* Virtual address */
                    clkCtrl: 0xAA009050,    /* Virtual address */
                    intNum:  55,
                    eventId: -1,
                },
                "GPTimer11": {
                    name: "WdTimer11Ipu",   /* GpTimer 11 */
                    baseAddr: 0xA8088000,   /* Virtual address */
                    clkCtrl: 0xAA009030,    /* Virtual address */
                    intNum:  56,
                    eventId: -1,
                },
                "Default": [
                    { name: "GPTimer9" },
                    { name: "GPTimer11" },
                ]
            },
            "DRA7XX": {
                "GPTimer1": {
                    name: "WdTimer1Ipu",    /* GpTimer 1 */
                    baseAddr: 0x6AE18000,   /* Virtual address */
                    clkCtrl: 0x6AE07840,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer2": {
                    name: "WdTimer2Ipu",    /* GpTimer 2 */
                    baseAddr: 0x68032000,   /* Virtual address */
                    clkCtrl: 0x6A009738,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer3": {
                    name: "WdTimer3Ipu",    /* GpTimer 3 */
                    baseAddr: 0x68034000,   /* Virtual address */
                    clkCtrl: 0x6A009740,    /* Virtual address */
                    intNum:  53,
                    eventId: -1,
                },
                "GPTimer4": {
                    name: "WdTimer4Ipu",    /* GpTimer 4 */
                    baseAddr: 0x68036000,   /* Virtual address */
                    clkCtrl: 0x6A009748,    /* Virtual address */
                    intNum:  54,
                    eventId: -1,
                },
                "GPTimer5": {
                    name: "WdTimer5Ipu",    /* GpTimer 5 */
                    baseAddr: 0x68820000,   /* Virtual address */
                    clkCtrl: 0x6a005558,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer6": {
                    name: "WdTimer6Ipu",    /* GpTimer 6 */
                    baseAddr: 0x68822000,   /* Virtual address */
                    clkCtrl: 0x6A005560,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer7": {
                    name: "WdTimer7Ipu",    /* GpTimer 7 */
                    baseAddr: 0x68824000,   /* Virtual address */
                    clkCtrl: 0x6A005568,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer8": {
                    name: "WdTimer8Ipu",    /* GpTimer 8 */
                    baseAddr: 0x68826000,   /* Virtual address */
                    clkCtrl: 0x6A005570,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer9": {
                    name: "WdTimer9Ipu",    /* GpTimer 9 */
                    baseAddr: 0x6803E000,   /* Virtual address */
                    clkCtrl: 0x6A009750,    /* Virtual address */
                    intNum:  55,
                    eventId: -1,
                },
                "GPTimer10": {
                    name: "WdTimer10Ipu",   /* GpTimer 10 */
                    baseAddr: 0x68086000,   /* Virtual address */
                    clkCtrl: 0x6A009728,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer11": {
                    name: "WdTimer11Ipu",   /* GpTimer 11 */
                    baseAddr: 0x68088000,   /* Virtual address */
                    clkCtrl: 0x6A009730,    /* Virtual address */
                    intNum:  56,
                    eventId: -1,
                },
                "GPTimer12": {
                    name: "WdTimer12Ipu",   /* GpTimer 12 */
                    baseAddr: 0x6AE20000,   /* Virtual address */
                    clkCtrl: 0x6AE07848,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer13": {
                    name: "WdTimer13Ipu",   /* GpTimer 13 */
                    baseAddr: 0x68828000,   /* Virtual address */
                    clkCtrl: 0x6A0097C8,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer14": {
                    name: "WdTimer14Ipu",   /* GpTimer 14 */
                    baseAddr: 0x6882A000,   /* Virtual address */
                    clkCtrl: 0x6A0097D0,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer15": {
                    name: "WdTimer15Ipu",   /* GpTimer 15 */
                    baseAddr: 0x6882C000,   /* Virtual address */
                    clkCtrl: 0x6A0097D8,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "GPTimer16": {
                    name: "WdTimer16Ipu",   /* GpTimer 16 */
                    baseAddr: 0x6882E000,   /* Virtual address */
                    clkCtrl: 0x6A009830,    /* Virtual address */
                    intNum:  -1,
                    eventId: -1,
                },
                "Default": [
                    { name: "GPTimer9" },
                    { name: "GPTimer4" },
                ]
            },
        },
    };
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    var device;
    var found = false;

    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    Watchdog = this;

    timerIds = Watchdog.timerIds;

    catalogName = Program.cpu.catalogName;

    /* Loop through the device table */
    for (deviceName in deviceTable[catalogName]) {
        if (deviceName == Program.cpu.deviceName) {
            dflts = deviceTable[catalogName][deviceName]["Default"];
            timerIds.length = dflts.length;
            for (var id in dflts) {
                if (timerIds[id] == undefined) {
                    timerIds[id] = dflts[id].name;
                }
                device = deviceTable[catalogName][deviceName][timerIds[id]];
                if (device != undefined) {
                    var i = Watchdog.timerSettings.length++;

                    Watchdog.timerSettings[i].baseAddr = null;
                    Watchdog.timerSettings[i].clkCtrl = null;
                    Watchdog.timerSettings[i].intNum = device.intNum;
                    Watchdog.timerSettings[i].eventId = device.eventId;

                    found = true;
                }
                else {
                    print("Watchdog Timer configuration is not found for " +
                      "timer " + timerIds[id] + " for the specified device (" +
                      Program.cpu.deviceName + ").  Supported devices:");

                    for (device in deviceTable[catalogName]) {
                        print("\t" + device);
                    }

                    throw new Error ("Watchdog Timer unsupported on device!");
                }
            }

            break;
        }
    }

    if (!found) {
        print("Watchdog Timer configuration is not found for the specified " +
          "device (" + Program.cpu.deviceName + ").  Supported devices:");

        for (device in deviceTable[catalogName]) {
            print("\t" + device);
        }

        throw new Error ("Watchdog Timer unsupported on device!");
    }

    var Settings = xdc.module("ti.sysbios.family.Settings");
    var Hwi = xdc.useModule(Settings.getDefaultHwiDelegate());

    xdc.useModule('xdc.runtime.System');

    if (Program.platformName.match(/IPU/) ||
        Program.platformName.match(/ipu/)) {
        Core = xdc.module("ti.sysbios.hal.Core");
    }
    else {
        MultiProc = xdc.module('ti.sdo.utils.MultiProc');
        if (Program.platformName.match(/DSP/)) {
            xdc.useModule('ti.sysbios.family.c64p.tesla.Wugen');
        }
    }

    Task = xdc.useModule('ti.sysbios.knl.Task');
    taskHook = new Task.HookSet;

    Swi  = xdc.useModule('ti.sysbios.knl.Swi');
    swiHook  = new Swi.HookSet;
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    swiHook.beginFxn = this.swiPrehook;
    Swi.addHookSet(swiHook);

    taskHook.switchFxn = this.taskSwitch;
    Task.addHookSet(taskHook);

    /* Assign default values if not supplied through configuration */
    for (var id = 0; id < timerIds.length; id++) {
        device = deviceTable[catalogName][deviceName][timerIds[id]];
        if (Watchdog.timerSettings[id].baseAddr == null) {
            Watchdog.timerSettings[id].baseAddr = $addr(device.baseAddr);
        }
        if (Watchdog.timerSettings[id].clkCtrl == null) {
            Watchdog.timerSettings[id].clkCtrl = $addr(device.clkCtrl);
        }
    }

    mod.device.length = 1;
    mod.status.length   = 1;
    mod.wdtCores      = 1;
    if (Program.build.target.name.match(/C64T/) ||
        Program.build.target.name.match(/C66/)) {
        mod.device[0].baseAddr = Watchdog.timerSettings[0].baseAddr;
        mod.device[0].clkCtrl  = Watchdog.timerSettings[0].clkCtrl;
        mod.device[0].intNum   = Watchdog.timerSettings[0].intNum;
        mod.device[0].eventId  = Watchdog.timerSettings[0].eventId;
        mod.status[0]          = Watchdog.Mode_DISABLED;
    }
    else {
        if (Program.platformName.match(/IPU/) ||
            Program.platformName.match(/ipu/)) {
            mod.device.length       = Core.numCores;
            mod.status.length       = Core.numCores;
            mod.wdtCores            = Core.numCores;

            mod.device[0].baseAddr  = Watchdog.timerSettings[0].baseAddr;
            mod.device[0].clkCtrl   = Watchdog.timerSettings[0].clkCtrl;
            mod.device[0].intNum    = Watchdog.timerSettings[0].intNum;
            mod.device[0].eventId   = Watchdog.timerSettings[0].eventId;
            mod.status[0]           = Watchdog.Mode_DISABLED;

            mod.device[1].baseAddr  = Watchdog.timerSettings[1].baseAddr;
            mod.device[1].clkCtrl   = Watchdog.timerSettings[1].clkCtrl;
            mod.device[1].intNum    = Watchdog.timerSettings[1].intNum;
            mod.device[1].eventId   = Watchdog.timerSettings[1].eventId;
            mod.status[1]           = Watchdog.Mode_DISABLED;
        }
        else {
            if (MultiProc.id == MultiProc.getIdMeta("CORE0")) {
                mod.device[0].baseAddr  = Watchdog.timerSettings[0].baseAddr;
                mod.device[0].clkCtrl   = Watchdog.timerSettings[0].clkCtrl;
                mod.device[0].intNum    = Watchdog.timerSettings[0].intNum;
                mod.device[0].eventId   = Watchdog.timerSettings[0].eventId;
            }
            else {
                mod.device[0].baseAddr  = Watchdog.timerSettings[1].baseAddr;
                mod.device[0].clkCtrl   = Watchdog.timerSettings[1].clkCtrl;
                mod.device[0].intNum    = Watchdog.timerSettings[1].intNum;
                mod.device[0].eventId   = Watchdog.timerSettings[1].eventId;
            }
            mod.status[0]               = Watchdog.Mode_DISABLED;
        }
    }
}
