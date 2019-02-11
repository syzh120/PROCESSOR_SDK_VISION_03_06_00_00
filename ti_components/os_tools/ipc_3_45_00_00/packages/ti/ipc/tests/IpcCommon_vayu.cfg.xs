/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 *  The SysMin used here vs StdMin, as trace buffer address is required for
 *  Linux trace debug driver, plus provides better performance.
 */
var System      = xdc.useModule('xdc.runtime.System');
var SysMin      = xdc.useModule('ti.trace.SysMin');
System.SupportProxy = SysMin;
SysMin.bufSize  = 0x8000;

/* Define default memory heap properties */
var Memory      = xdc.useModule('xdc.runtime.Memory');
Memory.defaultHeapSize = 0x20000;

/* Modules used in the virtqueue/RPMessage/ServiceMgr libraries: */
var Semaphore   = xdc.useModule('ti.sysbios.knl.Semaphore');
var BIOS        = xdc.useModule('ti.sysbios.BIOS');

/* Reduces code size, by only pulling in modules explicitly referenced: */
BIOS.libType    = BIOS.LibType_Custom;

xdc.loadPackage('ti.sdo.ipc.family.vayu');
xdc.useModule('ti.sdo.ipc.family.vayu.InterruptIpu');
xdc.loadPackage('ti.ipc.rpmsg');
xdc.loadPackage('ti.ipc.family.vayu');

/* TBD:
xdc.loadPackage('ti.srvmgr');
xdc.useModule('ti.srvmgr.omx.OmxSrvMgr');
xdc.loadPackage('ti.resmgr');
*/

/* Enable Memory Translation module that operates on the BIOS Resource Table */
var Resource = xdc.useModule('ti.ipc.remoteproc.Resource');

var HeapBuf   = xdc.useModule('ti.sysbios.heaps.HeapBuf');
var List      = xdc.useModule('ti.sdo.utils.List');

/* ti.grcm Configuration */
/* TBD:
var rcmSettings = xdc.useModule('ti.grcm.Settings');
rcmSettings.ipc = rcmSettings.IpcSupport_ti_sdo_ipc;
xdc.useModule('ti.grcm.RcmServer');
*/
xdc.useModule('ti.sysbios.xdcruntime.GateThreadSupport');
var GateSwi   = xdc.useModule('ti.sysbios.gates.GateSwi');

var Task          = xdc.useModule('ti.sysbios.knl.Task');
Task.common$.namedInstance = true;

var Assert = xdc.useModule('xdc.runtime.Assert');
var Defaults = xdc.useModule('xdc.runtime.Defaults');
var Diags = xdc.useModule('xdc.runtime.Diags');
var LoggerSys = xdc.useModule('xdc.runtime.LoggerSys');
var LoggerSysParams = new LoggerSys.Params();

/* Enable Logger: */
Defaults.common$.logger = LoggerSys.create(LoggerSysParams);

/* Enable runtime Diags_setMask() for non-XDC spec'd modules: */
var Text = xdc.useModule('xdc.runtime.Text');
Text.isLoaded = true;
var Registry = xdc.useModule('xdc.runtime.Registry');
Registry.common$.diags_ENTRY = Diags.RUNTIME_OFF;
Registry.common$.diags_EXIT  = Diags.RUNTIME_OFF;
Registry.common$.diags_USER1 = Diags.RUNTIME_OFF;
Registry.common$.diags_INFO  = Diags.RUNTIME_OFF;
Registry.common$.diags_LIFECYCLE = Diags.RUNTIME_OFF;
Registry.common$.diags_STATUS = Diags.RUNTIME_OFF;
Diags.setMaskEnabled = true;

var Main = xdc.useModule('xdc.runtime.Main');
Main.common$.diags_ASSERT = Diags.ALWAYS_ON;
Main.common$.diags_INTERNAL = Diags.ALWAYS_ON;

var Hwi = xdc.useModule('ti.sysbios.family.arm.m3.Hwi');
Hwi.enableException = true;
Hwi.nvicCCR.DIV_0_TRP = 1;

/* Include stack debug helper */
/* TBD:
var StackDbg = xdc.useModule('ti.deh.StackDbg');
*/

var dmTimer = xdc.useModule('ti.sysbios.timers.dmtimer.Timer');
/* dmTimer 0 mapped to GPT1 */
dmTimer.timerSettings[0].baseAddr = 0x6AE18000;
/* dmTimer 1 mapped to GPT2 */
dmTimer.timerSettings[1].baseAddr = 0x68032000;
/* dmTimer 2 mapped to GPT3 */
dmTimer.timerSettings[2].baseAddr = 0x68034000;
/* dmTimer 3 mapped to GPT4 */
dmTimer.timerSettings[3].baseAddr = 0x68036000;
/* dmTimer 4 mapped to GPT5 */
dmTimer.timerSettings[4].baseAddr = 0x68820000;
/* dmTimer 5 mapped to GPT6 */
dmTimer.timerSettings[5].baseAddr = 0x68822000;
/* dmTimer 6 mapped to GPT7 */
dmTimer.timerSettings[6].baseAddr = 0x68034000;
/* dmTimer 7 mapped to GPT8 */
dmTimer.timerSettings[7].baseAddr = 0x68036000;
/* dmTimer 8 mapped to GPT9 */
dmTimer.timerSettings[8].baseAddr = 0x6803E000;
/* dmTimer 9 mapped to GPT10 */
dmTimer.timerSettings[9].baseAddr = 0x68086000;
/* dmTimer 10 mapped to GPT11 */
dmTimer.timerSettings[10].baseAddr = 0x68088000;
/* dmTimer 11 mapped to GPT12 */
dmTimer.timerSettings[11].baseAddr = 0x6AE20000;
/* dmTimer 12 mapped to GPT13 */
dmTimer.timerSettings[12].baseAddr = 0x68828000;
/* dmTimer 13 mapped to GPT14 */
dmTimer.timerSettings[13].baseAddr = 0x6882A000;
/* dmTimer 14 mapped to GPT15 */
dmTimer.timerSettings[14].baseAddr = 0x6882C000;
/* dmTimer 15 mapped to GPT16 */
dmTimer.timerSettings[15].baseAddr = 0x6882E000;

/* Skip the Timer frequency verification check. Need to remove this later */
dmTimer.checkFrequency = false;

/* Match this to the SYS_CLK frequency sourcing the dmTimers.
 * Not needed once the SYS/BIOS family settings is updated. */
dmTimer.intFreq.hi = 0;
dmTimer.intFreq.lo = 19200000;

/* Override the internal sysTick timer with dmTimer for Bios Timer */
var halTimer = xdc.useModule('ti.sysbios.hal.Timer');
halTimer.TimerProxy = dmTimer;

/* Version module */
/* ???
xdc.useModule('ti.utils.Version');
*/
