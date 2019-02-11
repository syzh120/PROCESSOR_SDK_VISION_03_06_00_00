/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== Settings.xs ========
 */

/*
 *  ======== setDeviceAliases ========
 */
function setDeviceAliases(settingsTable, aliasTable)
{
    /* Number of times to call the outer loop */
    var numLoops = 6;

    /*
     *  Execute the 2nd loop 'numLoops' times to allow aliases of aliases
     *  to be applied to the table
     */
    for (var i = 0; i < numLoops; i++) {
        for (var device in aliasTable) {
            for each (var alias in aliasTable[device]) {
                /*
                 *  Define the alias only if the alias doesn't already exist
                 *  in the table and if the device does exist in the table.
                 */
                if (settingsTable[alias] == null &&
                    settingsTable[device] != null) {
                    settingsTable[alias] = settingsTable[device];
                }
            }
        }
    }
}

/*
 *  ======== setCatalogAliases ========
 */
function setCatalogAliases(settingsTable, aliasTable)
{
    for (var catalogName in settingsTable) {
        if (aliasTable[catalogName] != null) {
            var catalogAlias = aliasTable[catalogName];
            if (settingsTable[catalogAlias] == null) {
                settingsTable[catalogAlias] = settingsTable[catalogName];
                continue;
            }
            for (var deviceName in settingsTable[catalogName]) {
                settingsTable[catalogAlias][deviceName] =
                    settingsTable[catalogName][deviceName];
            }
        }
    }
}

/*
 *  ======== deviceSupportCheck ========
 *  Check validity of device
 */
function deviceSupportCheck()
{
    var deviceName;

    /* look for exact match */
    for (deviceName in procNames) {
        if (deviceName == Program.cpu.deviceName) {
            return deviceName;
        }
    }

    /* now look for wild card match */
    for (deviceName in procNames) {
        if (Program.cpu.deviceName.match(deviceName)) {
            return deviceName;
        }
    }
}

/*
 *  ======== catalogAliases ========
 *  Aliases for catalog
 */
var catalogAliases = {
    'ti.catalog.arm.cortexm3' : ['ti.catalog.arm'],
}

/*
 *  ======== deviceAliases ========
 *  Aliases for devices used in IPC
 */
var deviceAliases = {
    'TMS320C6472'       : ['TMS320CTCI6486'],
    'TMS320C6474'       : ['TMS320CTCI6488'],
    'TMS320DA830'       : ['OMAPL138',
                           'OMAPL137'],
    'OMAP3530'          : ['TMS320C3430'],
    'TMS320TI816X'      : ['TMS320CDM740',
                           'TMS320DM8148',
                           'TMS320DM8168',
                           'TMS320C6A8168',
                           'TMS320C6A8149',
                           'TMS320TI811X',
                           'TMS320TI813X',
                           'TMS320TI814X'],
    'TMS320C6678'       : ['TMS320TCI6608',
                           'TMS320C6674',
                           'TMS320C6672'],
    'TMS320C6670'       : ['TMS320TCI6616',
                           'TMS320CTCI6497',
                           'TMS320CTCI6498',
                           'TMS320TCI6618',
                           'TMS320TCI6614',
                           'TMS320C6657'],
    'TMS320TCI6634'     : ['TMS320C66AK2E05',
                           'TMS320C66AK2H12',
                           'TMS320TCI6630K2L',
                           'TMS320TCI6636',
                           'TMS320TCI6638',
                           'Kepler'],
    'TMS320C66AK2H12'   : ['TCI66AK2G02',
                           'TCI6636K2H'],
    'TMS320C66AK2E05'   : ['C66AK2E05'],
    'TMS320TCI6630K2L'  : ['TCI6630K2L'],
    'LM3.*'             : ['LM4.*'],
    'Vayu'              : ['DRA7XX']
}

/*
 *  ======== procNames ========
 */
var procNames = {
    'TMS320CDM6446'     : ["DSP", "HOST"],
    'TMS320DA830'       : ["DSP", "HOST"],
    'OMAPL138'          : ["DSP", "HOST"],
    'TMS320TI816X'      : ["DSP", "VIDEO-M3", "VPSS-M3", "HOST"],
    'TMS320TI813X'      : ["VIDEO-M3", "VPSS-M3", "HOST"],
    'TMS320C6A8168'     : ["DSP", "VPSS-M3", "HOST"],
    'TMS320C6A8149'     : ["DSP", "EVE", "VIDEO-M3", "VPSS-M3", "HOST"],
    'TMS320C6670'       : ["CORE0", "CORE1", "CORE2", "CORE3"],
    'TMS320C6657'       : ["CORE0", "CORE1"],
    'TMS320C6672'       : ["CORE0", "CORE1"],
    'TMS320TCI6614'     : ["CORE0", "CORE1", "CORE2", "CORE3", "HOST"],
    'TMS320TCI6634'     : ["CORE0", "CORE1", "CORE2", "CORE3",
                           "CORE4", "CORE5", "CORE6", "CORE7"],

    /*
     *  Note, the name "HOST" was intentionally chosen as a proc name to
     *  accomodate TransportRpmsg, a common transport on these platforms.
     */
    'TMS320TCI6636'     : ["HOST", "CORE0", "CORE1", "CORE2", "CORE3",
                           "CORE4", "CORE5", "CORE6", "CORE7"],
    'TMS320TCI6638'     : ["HOST", "CORE0", "CORE1", "CORE2", "CORE3",
                           "CORE4", "CORE5", "CORE6", "CORE7"],
    'Kepler'            : ["HOST", "CORE0", "CORE1", "CORE2", "CORE3",
                           "CORE4", "CORE5", "CORE6", "CORE7"],
    'TMS320TCI6630K2L'  : ["HOST", "CORE0", "CORE1", "CORE2", "CORE3"],
    'TMS320C66AK2E05'   : ["HOST", "CORE0"],
    'TMS320C66AK2H12'   : ["HOST", "CORE0", "CORE1", "CORE2", "CORE3",
                           "CORE4", "CORE5", "CORE6", "CORE7"],
    'TCI66AK2G02'       : ["HOST", "CORE0"],
    'TMS320C6674'       : ["CORE0", "CORE1", "CORE2", "CORE3"],
    'TMS320C6678'       : ["CORE0", "CORE1", "CORE2", "CORE3",
                           "CORE4", "CORE5", "CORE6", "CORE7"],
    'TMS320C6472'       : ["CORE0", "CORE1", "CORE2",
                           "CORE3", "CORE4", "CORE5"],
    'TMS320C6474'       : ["CORE0", "CORE1", "CORE2"],
    'OMAP3530'          : ["DSP", "HOST"],
    'OMAP4430'          : ["DSP", "CORE0", "CORE1", "HOST"],

    /*
     * Note that only SMP-BIOS is supported on OMAP5430, so there's only
     * one "IPU" proc defined for the dual-core M4.
     */
    'OMAP5430'          : ["DSP", "IPU", "HOST"],

    'Arctic'            : ["DSP", "ARP32"],
    'LM3.*'             : [ "" ],  /* single core, any name can be used */
    'Vayu'              : ["DSP1", "DSP2", "EVE1", "EVE2", "EVE3", "EVE4",
                           "IPU1", "IPU2", "IPU1-0", "IPU1-1", "IPU2-0",
                           "IPU2-1", "HOST"],
    'TDA3X'             : ["DSP1", "DSP2", "IPU1", "IPU1-0", "IPU1-1", "EVE1"]
};
setDeviceAliases(procNames, deviceAliases);

/*
 *  ======== hostNeedsSlaveData =======
 */
var hostNeedsSlaveData = {
    'TMS320TI816X'      : 1,
    'OMAP3530'          : 1,
    'OMAP4430'          : 1,
    'TMS320CDM6446'     : 1,
    'TMS320DA830'       : 1,
    'OMAPL138'          : 1,
    'Vayu'              : 1,
    'TDA3X'             : 1
};
setDeviceAliases(hostNeedsSlaveData, deviceAliases);

/*
 *  ======== sr0MemorySetup =======
 *  The devices in this list means these devices have a slave mmu
 *  that needs to be configured by the host before the slave can proceed.
 */
var sr0MemorySetup = {
    'TMS320TI816X'      : 1,
    'OMAP3530'          : 1,
    'OMAP4430'          : 1,
};
setDeviceAliases(sr0MemorySetup, deviceAliases);

/*
 *  ======== hostProcNames =======
 *  The name of the host or master processor.
 */
var hostProcNames = {
    'TMS320CDM6446'     : ["HOST"],
    'TMS320DA830'       : ["HOST"],
    'OMAPL138'          : ["HOST"],
    'TMS320TI816X'      : ["HOST"],
    'OMAP3530'          : ["HOST"],
    'OMAP4430'          : ["HOST"],
    'TMS320C6678'       : ["CORE0"],
    'TMS320C6670'       : ["CORE0"],
    'TMS320C6472'       : ["CORE0"],
    'TMS320C6474'       : ["CORE0"],
    'TMS320C66AK2E05'   : ["HOST"],
    'TMS320TCI6630K2L'  : ["HOST"],
    'TMS320C66AK2H12'   : ["HOST"],
    'TMS320TCI6634'     : ["CORE0"],
    'TMS320TCI6636'     : ["HOST0"],
    'TMS320TCI6638'     : ["HOST0"],
    'Kepler'            : ["HOST"],
};
setDeviceAliases(hostProcNames, deviceAliases);

/*
 *  ======== nameServerRemoteDelegates ========
 */
var nameServerRemoteDelegates = {
    'OMAP3530'          : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320CDM6446'     : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320DA830'       : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320TI816X'      : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320C6678'       : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320C6670'       : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320C6472'       : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TMS320C6474'       : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'OMAP4430'          : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'Arctic'            : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'Vayu'              : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
    'TDA3X'             : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify' },
    'TMS320TCI6634'     : { del: 'ti.sdo.ipc.nsremote.NameServerRemoteNotify',},
};
setDeviceAliases(nameServerRemoteDelegates, deviceAliases);

/*
 *  ======== notifySetupDelegates ========
 */
var notifySetupDelegates = {
    'OMAP3530'          : { del: 'ti.sdo.ipc.family.omap3530.NotifySetup', },
    'TMS320CDM6446'     : { del: 'ti.sdo.ipc.family.dm6446.NotifySetup', },
    'TMS320DA830'       : { del: 'ti.sdo.ipc.family.da830.NotifySetup', },
    'TMS320TI816X'      : { del: 'ti.sdo.ipc.family.ti81xx.NotifySetup', },
    'TMS320C6A8149'     : { del: 'ti.sdo.ipc.family.c6a8149.NotifySetup', },
    'TMS320C6678'       : { del: 'ti.sdo.ipc.family.c647x.NotifySetup', },
    'TMS320C6670'       : { del: 'ti.sdo.ipc.family.c647x.NotifySetup', },
    'TMS320C6472'       : { del: 'ti.sdo.ipc.family.c647x.NotifySetup', },
    'TMS320C6474'       : { del: 'ti.sdo.ipc.family.c647x.NotifySetup', },
    'TMS320TCI6634'     : { del: 'ti.sdo.ipc.family.tci663x.NotifyCircSetup', },
    'TCI6636K2H'        : { del: 'ti.sdo.ipc.family.tci663x.NotifyCircSetup', },
    'OMAP4430'          : { del: 'ti.sdo.ipc.family.omap4430.NotifySetup', },
    'Arctic'            : { del: 'ti.sdo.ipc.family.arctic.NotifyCircSetup', },
    'LM3.*'             : { del: 'ti.sdo.ipc.notifyDrivers.NotifySetupNull', },
    'Vayu'              : { del: 'ti.sdo.ipc.family.vayu.NotifySetup', },
    'TDA3X'             : { del: 'ti.sdo.ipc.family.tda3xx.NotifySetup'  },
    'OMAP5430'          : { del: 'ti.sdo.ipc.notifyDrivers.NotifySetupNull' }

};
setDeviceAliases(notifySetupDelegates, deviceAliases);

/*
 *  ======== messageQSetupDelegates ========
 */
var messageQSetupDelegates = {
    'OMAP3530'          : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320CDM6446'     : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320DA830'       : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320TI816X'      : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320C6A8149'     : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320C6678'       : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320C6670'       : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320C6472'       : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320C6474'       : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TMS320TCI6634'     : { del: 'ti.sdo.ipc.transports.TransportShmNotifySetup', },
    'OMAP4430'          : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'Arctic'            : { del: 'ti.sdo.ipc.transports.TransportShmNotifySetup', },
    'LM3.*'             : { del: 'ti.sdo.ipc.transports.TransportNullSetup', },
    'Vayu'              : { del: 'ti.sdo.ipc.transports.TransportShmSetup', },
    'TDA3X'             : { del: 'ti.sdo.ipc.transports.TransportShmSetup' }
};
setDeviceAliases(messageQSetupDelegates, deviceAliases);

/*
 *  ======== interruptDelegates ========
 */
var interruptDelegates = {
    'ti.catalog.arm' : {
        'TMS320CDM6446' : { del: 'ti.sdo.ipc.family.dm6446.InterruptArm', },
        'TMS320DA830'   : { del: 'ti.sdo.ipc.family.da830.InterruptArm', },
        'OMAPL138'      : { del: 'ti.sdo.ipc.family.da830.InterruptArm', },
    },
    'ti.catalog.arm.cortexm3' : {
        'TMS320TI816X'  : { del: 'ti.sdo.ipc.family.ti81xx.InterruptDucati', },
        'TMS320C6A8149' : { del: 'ti.sdo.ipc.family.c6a8149.InterruptDucati', },
        'OMAP4430'      : { del: 'ti.sdo.ipc.family.omap4430.InterruptDucati', },
    },
    'ti.catalog.arm.cortexm4' : {
        'Vayu'          : { del: 'ti.sdo.ipc.family.vayu.InterruptIpu', },
        'TDA3X'         : { del: 'ti.sdo.ipc.family.tda3xx.InterruptIpu' },
    },
    'ti.catalog.arm.cortexa8' : {
        'TMS320TI816X'  : { del: 'ti.sdo.ipc.family.ti81xx.InterruptHost', },
        'TMS320C6A8149' : { del: 'ti.sdo.ipc.family.c6a8149.InterruptHost', },
        'OMAP3530'      : { del: 'ti.sdo.ipc.family.omap3530.InterruptHost', },
    },
    'ti.catalog.arm.cortexa15' : {
        'Vayu'          : { del: 'ti.sdo.ipc.family.vayu.InterruptHost', },
        'TCI66AK2G02'   : { del: 'ti.sdo.ipc.family.tci663x.Interrupt', },
        'TCI6636K2H'    : { del: 'ti.sdo.ipc.family.tci663x.Interrupt', },
        'TMS320C66AK2E05'      : { del: 'ti.sdo.ipc.family.tci663x.Interrupt', },
        'TMS320TCI6630K2L'     : { del: 'ti.sdo.ipc.family.tci663x.Interrupt', },
    },
    'ti.catalog.c6000' : {
        'OMAP3530'      : { del: 'ti.sdo.ipc.family.omap3530.InterruptDsp', },
        'TMS320CDM6446' : { del: 'ti.sdo.ipc.family.dm6446.InterruptDsp', },
        'TMS320DA830'   : { del: 'ti.sdo.ipc.family.da830.InterruptDsp', },
        'OMAPL138'      : { del: 'ti.sdo.ipc.family.da830.InterruptDsp', },
        'TMS320TI816X'  : { del: 'ti.sdo.ipc.family.ti81xx.InterruptDsp', },
        'TMS320C6A8149' : { del: 'ti.sdo.ipc.family.c6a8149.InterruptDsp', },
        'TMS320C6472'   : { del: 'ti.sdo.ipc.family.c647x.Interrupt', },
        'TMS320C6474'   : { del: 'ti.sdo.ipc.family.c647x.Interrupt', },
        'TMS320C6678'   : { del: 'ti.sdo.ipc.family.c647x.Interrupt', },
        'TMS320C6670'   : { del: 'ti.sdo.ipc.family.c647x.Interrupt', },
        'TMS320TCI6634' : { del: 'ti.sdo.ipc.family.tci663x.Interrupt', },
        'TCI6636K2H'    : { del: 'ti.sdo.ipc.family.tci663x.Interrupt', },

        'OMAP4430'      : { del: 'ti.sdo.ipc.family.omap4430.InterruptDsp', },
        'Arctic'        : { del: 'ti.sdo.ipc.family.arctic.InterruptDsp', },
        'Vayu'          : { del: 'ti.sdo.ipc.family.vayu.InterruptDsp', },
        'TDA3X'         : { del: 'ti.sdo.ipc.family.tda3xx.InterruptDsp' },
    },
    'ti.catalog.arp32' : {
        'TMS320C6A8149' : { del: 'ti.sdo.ipc.family.c6a8149.InterruptEve', },
        'Arctic'        : { del: 'ti.sdo.ipc.family.arctic.InterruptArp32', },
        'Vayu'          : { del: 'ti.sdo.ipc.family.vayu.InterruptArp32', },
        'TDA3X'         : { del: 'ti.sdo.ipc.family.tda3xx.InterruptArp32' },
    },
};
for (var family in interruptDelegates) {
    setDeviceAliases(interruptDelegates[family], deviceAliases);
}
setCatalogAliases(interruptDelegates, catalogAliases);

/*
 *  ======== spinlockDelegates ========
 */
var spinlockDelegates = {
    'ti.catalog.arm.cortexm3' : {
        'OMAP4430' : {
            baseAddr:   0x4A0F6800,
            numLocks:   32,
        },
        'TMS320TI816X' : {
            baseAddr:   0x480CA800,
            numLocks:   64,
        },
    },
    'ti.catalog.arm.cortexm4' : {
        'Vayu' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        },
        'TDA3X' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        }
    },
    'ti.catalog.arm.cortexa8' : {
        'TMS320TI816X' : {
            baseAddr:   0x480CA800,
            numLocks:   64,
        },
    },
    'ti.catalog.arm.cortexa15' : {
        'Vayu' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        },
    },
    'ti.catalog.c6000' : {
        'TMS320TI816X' : {
            baseAddr:   0x080CA800,
            numLocks:   64,
        },
        'OMAP4430' : {
            baseAddr:   0x4A0F6800,
            numLocks:   32,
        },
        'Arctic' : {
            baseAddr:   0x480CA800,
            numLocks:   64,
        },
        'Vayu' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        },
        'TDA3X' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        }
    },
    'ti.catalog.arp32' : {
        /* 	'TMS320C6A8149' : {
		    baseAddr:   0x480CA800,
		    numLocks:   64,
		},
	*/
        'Arctic' : {
            baseAddr:   0x480CA800,
            numLocks:   64,
        },
        'Vayu' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        },
        'TDA3X' : {
            baseAddr:   0x4A0F6800,
            numLocks:   256
        }
    }
}
for (var family in spinlockDelegates) {
    setDeviceAliases(spinlockDelegates[family], deviceAliases);
}
setCatalogAliases(spinlockDelegates, catalogAliases);

/*
 *  ======== hwSemDelegates ========
 */
var hwSemDelegates = {
    'ti.catalog.c6000' : {
        'TMS320C6474' : {
            baseAddr:   0x02B40100,
            queryAddr:  0x02B40300,
            numSems:    32,
        },
        'TMS320C6678' : {
            baseAddr:   0x02640100,
            queryAddr:  0x02640200,
            numSems:    32,
        },
        'TMS320C6670' : {
            baseAddr:   0x02640100,
            queryAddr:  0x02640200,
            numSems:    32,
        },
        'TMS320TCI6634' : {
            baseAddr:   0x02640100,
            queryAddr:  0x02640200,
            numSems:    32,
        }
    },
    'ti.catalog.arm.cortexa15' : {
        'TMS320C66AK2H12' : {
            baseAddr:   0x02640100,
            queryAddr:  0x02640200,
            numSems:    32,
        },
        'TMS320C66AK2E05' : {
            baseAddr:   0x02640100,
            queryAddr:  0x02640200,
            numSems:    32,
        },
        'TMS320TCI6630K2L' : {
            baseAddr:   0x02640100,
            queryAddr:  0x02640200,
            numSems:    32,
        }
    }
}
for (var family in hwSemDelegates) {
    setDeviceAliases(hwSemDelegates[family], deviceAliases);
}
setCatalogAliases(hwSemDelegates, catalogAliases);

/*
 *  ======== getGateHWSemSettings ========
 */
function getGateHWSemSettings()
{
    var errorString = "IPC does not have a default GateHWSem" +
                      " delegate for the " + deviceName + " device!";
    var catalogName = Program.cpu.catalogName;
    var deviceName = deviceSupportCheck();

    var errStr = "The device " + deviceName +
        " does not support hardware semaphores!";

    try {
        var hwSemSettings = hwSemDelegates[catalogName][deviceName];
    }
    catch(e) {
        throw new Error(errStr);
    }

    if (hwSemSettings == null) {
        throw new Error(errStr);
    }

    return (hwSemSettings);
}

/*
 *  ======== getGateHWSpinlockSettings ========
 */
function getGateHWSpinlockSettings()
{
    var errorString = "IPC does not have a default GateHWSpinlock" +
                      " delegate for the " + deviceName + " device!";
    var catalogName = Program.cpu.catalogName;
    var deviceName = deviceSupportCheck();

    var errStr = "The device " + deviceName +
        " does not support hardware spinlocks!";

    try {
        var spinLockSettings = spinlockDelegates[catalogName][deviceName];
    }
    catch(e) {
        throw new Error(errStr);
    }

    if (spinLockSettings == null) {
        throw new Error(errStr);
    }

    return (spinLockSettings);
}

/*
 *  ======== generateSlaveDataForHost ========
 */
function generateSlaveDataForHost()
{
    var deviceName = deviceSupportCheck();
    var retval = hostNeedsSlaveData[deviceName];

    /* A15 is the already the host no need to generate data */
    if ((Program.cpu.catalogName == 'ti.catalog.arm.cortexa8') ||
        (Program.cpu.catalogName == 'ti.catalog.arm.cortexa9') ||
        (Program.cpu.catalogName == 'ti.catalog.arm.cortexa15')) {
        return (false);
    }

    if (retval != null) {
        return (true);
    }

    return (false);
}

/*
 *  ======== getHostProcId ========
 */
function getHostProcId()
{
    var MultiProc = xdc.module("ti.sdo.utils.MultiProc");
    var deviceName = deviceSupportCheck();
    var hostProcName = hostProcNames[deviceName];

    if (hostProcName == null) {
        /* The device doesn't have a core that runs a hlos */
        return (MultiProc.INVALIDID);
    }

    /*
     *  If the device may run a hlos, return the corresponding core's MultiProc
     *  id. MultiProc.INVALIDID will be returned if the core exists but isn't
     *  being used in the application
     */
    return(MultiProc.getIdMeta(String(hostProcName)));
}

/*
 *  ======== getIpcSR0Setup ========
 */
function getIpcSR0Setup()
{
    var deviceName = deviceSupportCheck();
    var memorySetup = sr0MemorySetup[deviceName];

    if (memorySetup == null) {
        /* The device has memory available to it */
        return (true);
    }
    else {
        /* The device needs host to enable memory through mmu */
        return (false);
    }
}

/*
 *  ======== getHWGate ========
 */
function getHWGate()
{
    var deviceName = deviceSupportCheck();
    if (deviceName == "TMS320C6472" ||
        deviceName == "TMS320CTCI6486") {
        return ('ti.sdo.ipc.gates.GateAAMonitor');
    }
    else if (deviceName == "TMS320C6A8149") {
        return ('ti.sdo.ipc.gates.GatePetersonN');
    }
    try {
        this.getGateHWSpinlockSettings();
        return ('ti.sdo.ipc.gates.GateHWSpinlock');
    }
    catch(e) {
    }

    try {
        this.getGateHWSemSettings();
        return ('ti.sdo.ipc.gates.GateHWSem');
    }
    catch(e) {
    }

    return('ti.sdo.ipc.gates.GatePeterson');
}

/*
 *  ======== getDefaultInterruptDelegate ========
 */
function getDefaultInterruptDelegate()
{
    var catalogName = Program.cpu.catalogName;
    var deviceName = deviceSupportCheck();

    var delegate = interruptDelegates[catalogName][deviceName];

    if (delegate == null) {
        throw new Error ("IPC does not have a default Interrupt"
            + " delegate for the " + deviceName + " device!");
    }

    return (delegate.del);
}

/*
 *  ======== getNameServerRemoteDelegate ========
 */
function getNameServerRemoteDelegate()
{
    var deviceName = deviceSupportCheck();

    var delegate = nameServerRemoteDelegates[deviceName];

    if (delegate == null) {
        delegate = { del: 'ti.sdo.utils.NameServerRemoteNull', };
    }

    return (delegate.del);
}

/*
 *  ======== getNotifySetupDelegate ========
 */
function getNotifySetupDelegate()
{
    var deviceName = deviceSupportCheck();

    var delegate = notifySetupDelegates[deviceName];

    if (delegate == null) {
        throw new Error ("IPC does not have a default NotifySetup"
            + " delegate for the " + deviceName + " device!");
    }

    return (delegate.del);
}

/*
 *  ======== getMessageQSetupDelegate ========
 */
function getMessageQSetupDelegate()
{
    var deviceName = deviceSupportCheck();

    var delegate = messageQSetupDelegates[deviceName];

    if (delegate == null) {
        throw new Error ("IPC does not have a default MessageQ setup"
            + " delegate for the " + deviceName + " device!");
    }

    return (delegate.del);
}

/*
 *  ======== procInDevice ========
 */
function procInDevice(procName)
{
    var deviceName = deviceSupportCheck();
    if (procNames[deviceName] == null) {
        throw("The device (" + Program.cpu.deviceName +
                       ") isn't supported by IPC");
    }

    /* Search through the procNames table */
    for each (name in procNames[deviceName]) {
        if (name == procName) {
            return (true);
        }
    }

    return (false);
}

/*
 *  ======== getDeviceProcNames ========
 */
function getDeviceProcNames()
{
    var deviceName = deviceSupportCheck();
    if (procNames[deviceName] == null) {
        throw("The device (" + Program.cpu.deviceName +
                       ") isn't supported by IPC");
    }

    return (procNames[deviceName]);
}
