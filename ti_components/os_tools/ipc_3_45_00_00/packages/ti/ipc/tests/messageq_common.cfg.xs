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

var Memory = xdc.useModule('xdc.runtime.Memory');
var Semaphore = xdc.useModule('ti.sysbios.knl.Semaphore');
var BIOS = xdc.useModule('ti.sysbios.BIOS');
BIOS.heapSize = 0x10000;
BIOS.libType = BIOS.LibType_Custom;

var Task = xdc.useModule('ti.sysbios.knl.Task');
Task.deleteTerminatedTasks = true;

var Idle = xdc.useModule('ti.sysbios.knl.Idle');
Idle.addFunc('&VirtQueue_cacheWb');

var System = xdc.useModule('xdc.runtime.System');
var SysMin = xdc.useModule('xdc.runtime.SysMin');
System.SupportProxy = SysMin;

var Diags = xdc.useModule('xdc.runtime.Diags');

xdc.useModule("ti.ipc.namesrv.NameServerRemoteRpmsg");

print ("Program.cpu.deviceName = " + Program.cpu.deviceName);
print ("Program.platformName = " + Program.platformName);
if (Program.cpu.deviceName == "OMAPL138") {
    xdc.useModule('ti.ipc.family.omapl138.VirtQueue');
    xdc.useModule('ti.sdo.ipc.family.da830.InterruptDsp');

    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    MultiProc.setConfig("DSP", ["HOST", "DSP"]);

    /* Enable Memory Translation module that operates on the Resource Table */
    var Resource = xdc.useModule('ti.ipc.remoteproc.Resource');
    Resource.loadSegment = Program.platform.dataMemory;

    Program.sectMap[".text:_c_int00"] = new Program.SectionSpec();
    Program.sectMap[".text:_c_int00"].loadSegment = "DDR";
    Program.sectMap[".text:_c_int00"].loadAlign = 0x400;

    var Hwi = xdc.useModule('ti.sysbios.family.c64p.Hwi');
    Hwi.enableException = true;

    var Cache = xdc.useModule('ti.sysbios.family.c64p.Cache');
    /* Set 0xc4000000 -> 0xc4ffffff to be non-cached for shared memory IPC */
    Cache.MAR192_223 = 0x00000010;

    var Timer = xdc.useModule('ti.sysbios.timers.timer64.Timer');
    var Clock = xdc.useModule('ti.sysbios.knl.Clock');
    Timer.timerSettings[1].master = true;
    Timer.defaultHalf = Timer.Half_LOWER;
    Clock.timerId = 1;

    SysMin.bufSize  = 0x8000;

    /*  COMMENT OUT TO SHUT OFF LOG FOR BENCHMARKS: */
    /*
    Diags.setMaskMeta("ti.sdo.ipc.family.da830.InterruptDsp", Diags.USER1,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.family.omapl138.VirtQueue", Diags.USER1,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.transports.TransportRpmsg",
        Diags.INFO|Diags.USER1|Diags.STATUS,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.namesrv.NameServerRemoteRpmsg", Diags.INFO,
        Diags.ALWAYS_ON);
    */

    /* Enable runtime Diags_setMask() for non-XDC spec'd modules: */
    /*
    var Text = xdc.useModule('xdc.runtime.Text');
    Text.isLoaded = true;
    var Registry = xdc.useModule('xdc.runtime.Registry');
    Registry.common$.diags_INFO  = Diags.ALWAYS_ON;
    Registry.common$.diags_STATUS = Diags.ALWAYS_ON;
    Registry.common$.diags_LIFECYCLE = Diags.ALWAYS_ON;
    Diags.setMaskEnabled = true;
    */
}
else if (Program.platformName.match(/6614/)) {
    var VirtQueue = xdc.useModule('ti.ipc.family.tci6614.VirtQueue');
    var Interrupt = xdc.useModule('ti.ipc.family.tci6614.Interrupt');

    /* Note: MultiProc_self is set during VirtQueue_init based on DNUM. */
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');
    MultiProc.setConfig(null, ["HOST", "CORE0", "CORE1", "CORE2", "CORE3"]);

    Program.sectMap[".text:_c_int00"] = new Program.SectionSpec();
    Program.sectMap[".text:_c_int00"].loadSegment = "L2SRAM";
    Program.sectMap[".text:_c_int00"].loadAlign = 0x400;

    var Hwi = xdc.useModule('ti.sysbios.family.c64p.Hwi');
    Hwi.enableException = true;

    /* This makes the vrings address range 0xa0000000 to 0xa1ffffff uncachable.
       We assume the rest is to be left cacheable.
       Per sprugw0b.pdf
        0184 8280h MAR160 Memory Attribute Register 160 A000 0000h - A0FF FFFFh
        0184 8284h MAR161 Memory Attribute Register 161 A100 0000h - A1FF FFFFh
    */
    var Cache = xdc.useModule('ti.sysbios.family.c66.Cache');
    /*  This doesn't work:
         Cache.MAR160_191 = 0xFFFFFFFC;
         So, need to do this:
    */
    Cache.setMarMeta(0xA0000000, 0x1FFFFFF, 0);

    Program.global.sysMinBufSize = 0x8000;
    SysMin.bufSize  =  Program.global.sysMinBufSize;

    /* Enable Memory Translation module that operates on the Resource Table */
    var Resource = xdc.useModule('ti.ipc.remoteproc.Resource');
    Resource.loadSegment = Program.platform.dataMemory;

    /*  COMMENT OUT TO SHUT OFF LOG FOR BENCHMARKS: */
    /*
    Diags.setMaskMeta("ti.ipc.family.tci6614.Interrupt", Diags.USER1,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.family.tci6614.VirtQueue", Diags.USER1,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.transports.TransportRpmsg",
        Diags.INFO|Diags.USER1|Diags.STATUS,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.namesrv.NameServerRemoteRpmsg", Diags.INFO,
        Diags.ALWAYS_ON);
    */
}
else if (Program.platformName.match(/simKepler/) ||
        Program.cpu.deviceName.match(/^TMS320C66AK2E05$/) ||
        Program.cpu.deviceName.match(/^TMS320C66AK2H12$/) ||
        Program.cpu.deviceName.match(/^TCI66AK2G02$/) ||
        Program.cpu.deviceName.match(/^TMS320TCI663(0K2L|6|8)$/)) {
    var VirtQueue = xdc.useModule('ti.ipc.family.tci6638.VirtQueue');

    /* Note: MultiProc_self is set during VirtQueue_init based on DNUM. */
    var MultiProc = xdc.useModule('ti.sdo.utils.MultiProc');

    switch (Program.cpu.deviceName) {
        case "TMS320C66AK2E05":
        case "TCI66AK2G02":
            MultiProc.setConfig(null,
                    ["HOST", "CORE0"]);
            break;

        case "TMS320TCI6630K2L":
            MultiProc.setConfig(null,
                    ["HOST", "CORE0", "CORE1", "CORE2", "CORE3"]);
            break;

        case "TMS320TCI6636":
        case "TMS320TCI6638":
        case "TMS320C66AK2H12":
            MultiProc.setConfig(null,
                    ["HOST", "CORE0", "CORE1", "CORE2", "CORE3",
                    "CORE4", "CORE5", "CORE6", "CORE7"]);
            break;
    }

    Program.sectMap[".text:_c_int00"] = new Program.SectionSpec();
    Program.sectMap[".text:_c_int00"].loadSegment = "L2SRAM";
    Program.sectMap[".text:_c_int00"].loadAlign = 0x400;

    var Hwi = xdc.useModule('ti.sysbios.family.c64p.Hwi');
    Hwi.enableException = true;

    /* This makes the vrings address range 0xa0000000 to 0xa1ffffff uncachable.
       We assume the rest is to be left cacheable.
       Per sprugw0b.pdf
        0184 8280h MAR160 Memory Attribute Register 160 A000 0000h - A0FF FFFFh
        0184 8284h MAR161 Memory Attribute Register 161 A100 0000h - A1FF FFFFh
    */
    var Cache = xdc.useModule('ti.sysbios.family.c66.Cache');
    /*  This doesn't work:
         Cache.MAR160_191 = 0xFFFFFFFC;
         So, need to do this:
    */
    /* TBD: Update for Kepler: */
    Cache.setMarMeta(0xA0000000, 0x1FFFFFF, 0);

    Program.global.sysMinBufSize = 0x2000;
    SysMin.bufSize  =  Program.global.sysMinBufSize;

    /* Enable Memory Translation module that operates on the Resource Table */
    var Resource = xdc.useModule('ti.ipc.remoteproc.Resource');
    Resource.loadSegment = Program.platform.dataMemory;

    /*  COMMENT OUT TO SHUT OFF LOG FOR BENCHMARKS: */
    /*
     Diags.setMaskMeta("ti.ipc.family.tci6638.VirtQueue", Diags.USER1,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.transports.TransportRpmsg",
        Diags.INFO|Diags.USER1|Diags.STATUS,
        Diags.ALWAYS_ON);
    Diags.setMaskMeta("ti.ipc.namesrv.NameServerRemoteRpmsg", Diags.INFO,
        Diags.ALWAYS_ON);
    */
}
else {
    throw("messageq_common.cfg.xs: Did not match any platform!");
}

Hwi.enableException = true;

xdc.useModule('ti.ipc.ipcmgr.IpcMgr');
BIOS.addUserStartupFunction('&IpcMgr_ipcStartup');

var HeapBuf = xdc.useModule('ti.sysbios.heaps.HeapBuf');
var params = new HeapBuf.Params;
params.align = 8;
params.blockSize = 512;
params.numBlocks = 64;
var msgHeap = HeapBuf.create(params);

var MessageQ  = xdc.useModule('ti.sdo.ipc.MessageQ');
MessageQ.registerHeapMeta(msgHeap, 0);

var Assert = xdc.useModule('xdc.runtime.Assert');
var Defaults = xdc.useModule('xdc.runtime.Defaults');
var Text = xdc.useModule('xdc.runtime.Text');
Text.isLoaded = true;

var LoggerSys = xdc.useModule('xdc.runtime.LoggerSys');
var LoggerSysParams = new LoggerSys.Params();

Defaults.common$.logger = LoggerSys.create(LoggerSysParams);

var VirtioSetup = xdc.useModule('ti.ipc.transports.TransportRpmsgSetup');
VirtioSetup.common$.diags_INFO = Diags.RUNTIME_OFF;

var Main = xdc.useModule('xdc.runtime.Main');
Main.common$.diags_ASSERT = Diags.ALWAYS_ON;
Main.common$.diags_INTERNAL = Diags.ALWAYS_ON;

xdc.loadPackage('ti.ipc.transports').profile = 'release';
