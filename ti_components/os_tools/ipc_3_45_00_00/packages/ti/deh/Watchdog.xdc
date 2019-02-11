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
 *  ======== Watchdog.xdc ========
 *
 */

import ti.sysbios.knl.Task;
import ti.sysbios.knl.Swi;

/*!
 *  ======== Watchdog ========
 *  Watchdog Timer module for slave processors
 *
 *  Watchdog module implements watchdog timer for remote slave processor
 *  cores using GPTimers or a dedicated WatchDog timer. The timer is started
 *  during startup/bootup time. The logic for the WD timer is as follows:
 *  1. Start GP timer during startup/boot time.
 *  2. The expiration for WD timer is 5 seconds normally, but is 10 seconds
 *     during initial boot time.
 *  3. The WD timer is restarted in the Idle task through the plugged in DEH
 *     task function, or whenever a Task switch happens or a Swi is executed.
 *  4. In SMP-mode, Hwis and Swis are executed only in Core0 and Tasks can
 *     be executed on either of the cores. Core1 stops it's Watchdog upon
 *     entering Idle task as it can stay in WFI for a long-time (atleast two
 *     tasks need to be in READY state) and restarts its Watchdog upon a task
 *     switch.
 *  5. WD Timer is stopped by MPU by disabling the timer's clock during suspend.
 *     The MPU re-enables the timer's clock upon resume.
 */

module Watchdog {

    /*! Timer Registers */
    struct TimerRegs {
        UInt tidr;
        UInt empty[3];
        UInt tiocpCfg;
        UInt empty1[3];
        UInt irq_eoi;
        UInt irqstat_raw;
        UInt tisr;      /* irqstat   */
        UInt tier;      /* irqen_set */
        UInt irqen_clr;
        UInt twer;      /* irqwaken; */
        UInt tclr;
        Int  tcrr;
        Int  tldr;
        UInt ttgr;
        UInt twps;
        UInt tmar;
        UInt tcar1;
        UInt tsicr;
        UInt tcar2;
    };

    /*! Watchdog Timer device information */
    struct TimerDevice {
        Ptr     baseAddr;
        Ptr     clkCtrl;
        Int32   intNum;
        Int     eventId;
    };

    /*! Watchdog Timer device status */
    enum Mode {
        Mode_DISABLED,      /*! Watchdog Timer is disabled. */
        Mode_ENABLED        /*! Watchdog Timer is enabled.  */
    };

    /*!
     *  Watchdog timer period (in seconds)
     */
    const UInt TIME_SEC = 5;

    /*!
     *  Watchdog timer period during boot-time (in seconds)
     */
    const UInt BOOT_TIME_SEC = 10;

    /*!
     *  ======== timerSettings ========
     *  Global Control configuration for each physical timer.
     */
    metaonly config TimerDevice timerSettings[] = [];

    metaonly config String timerIds[] = [];

    /*!
     *  ======== disableWatchdog ========
     *  Configuration that allows disabling the watchdog.
     */
    config Bool disableWatchdog = false;

    /*!
     *  ======== init ========
     *  Initialize the Watchdog module
     *
     *  @param[in](timerFxn)    ISR handler function to be executed when the
     *                          Watchdog timer expires.
     */
    Void init(Void (*timerFxn)(Void));

    /*!
     *  ======== idleBegin ========
     *  Function called when entering idle, restarts/refreshes watchdog timer
     */
    Void idleBegin();

    /*!
     *  ======== taskSwitch ========
     *  Function hook called whenever a Task switch happens. The Watchdog
     *  timer would be restarted since the scheduler is fine
     *
     *  @param(p)       Previous task handle being switched from.
     *  @param(n)       Next task handle being switched to.
     */
    Void taskSwitch(Task.Handle p, Task.Handle n);

    /*!
     *  ======== swiPrehook ========
     *  Function hook called whenever a Swi is posted, and the scheduler
     *  runs to process the Swi.
     *
     *  @param(swi)     Swi Handle that would be run
     */
    Void swiPrehook(Swi.Handle swi);

    /*!
     *  ======== isException ========
     *  Function to check if given exception is a Watchdog exception
     *
     *  @param(excNum)     Exception number that would be checked
     */
    Bool isException(UInt excNum);

internal:   /* not for client use */

    /*!
     *  ======== stop ========
     *  @_nodoc
     *  Stop the Watchdog timer.
     *
     *  @param(core)    Core id on which the function is being called. Value is
     *                  almost always 0. A non-zero value is seen only in
     *                  SMP-mode.
     */
    Void stop(Int core);

    /*!
     *  ======== start ========
     *  @_nodoc
     *  Start the Watchdog timer.
     *
     *  @param(core)    Core id on which the function is being called. Value is
     *                  almost always 0. A non-zero value is seen only in
     *                  SMP-mode.
     */
    Void start(Int core);

    /*!
     *  ======== kick ========
     *  @_nodoc
     *  Refresh or restart the Watchdog timer. This call is used
     *  internally on any condition that validates that the processor
     *  core is executing fine.
     *
     *  @param(core)    Core id on which the function is being called. Value is
     *                  almost always 0. A non-zero value is seen only in
     *                  SMP-mode.
     */
    Void kick(Int core);

    /*!
     *  ======== restore ========
     *  @_nodoc
     *  Restore the context of the Watchdog timer after a hibernation/suspend.
     *  in case the context is lost.
     */
    Void restore(Int event, Ptr data);

    /*! Module state structure */
    struct Module_State {
        TimerDevice device[];   /* watchdog timer specific data */
        Mode        status[];   /* watchdog timer status */
        Int         wdtCores;   /* number of watchdog timers (usually 1) */
    };
}
