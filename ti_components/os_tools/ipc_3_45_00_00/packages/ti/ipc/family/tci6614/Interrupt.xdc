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
 *  ======== Interrupt.xdc ========
 */

/*!
 *  ======== Interrupt ========
 *  TCI6614 IPC interrupt manager
 */

@ModuleStartup

module Interrupt inherits ti.sdo.ipc.notifyDrivers.IInterrupt
{

    const UInt INVALIDPAYLOAD = 0xFFFFFFFF;

    /*!
     *  ======== enableKick ========
     *  If set to 'true' IPC will unlock the KICK registers on C66x devices
     *
     *  IPC unlocks the KICK registers on the local core if (and only if) all
     *  the following conditions are met:
     *  - This configuration is set to 'true'
     *  - SharedRegion #0 is valid and the local core is its owner
     *  - SharedRegion #0 is not valid and the local core is CORE0
     */
    config Bool enableKick = true;

    /*!
     *  ======== Interrupt_intClearAll ========
     *  Clear all pending interrupts.
     */
    Void intClearAll();

    /*!
     *  ======== Interrupt_checkAndClear =======
     *  Check to see that interrupt is set, if so clear it and return 1.
     */
    UInt checkAndClear(UInt16 remoteProcId, IntInfo *intInfo);

internal:

    /*! Source ID bit position for CORE0 */
    const UInt SRCS_BITPOS_CORE0 = 4;

    /*! Source ID bit position for HOST */
    const UInt SRCS_BITPOS_HOST = 31;

    /*! Ptr to the IPC Generation Registers */
    config Ptr IPCGR0;

    /*! Ptr to the IPC Acknowledgment Registers */
    config Ptr IPCAR0;

    /*! Ptr to the IPC Host Generation Host Register */
    config Ptr IPCGRH;

    /*! Ptr to the IPC Acknowledgement Host Register */
    config Ptr IPCARH;

    /*! Ptr to the KICK0 Bootcfg Registers */
    config Ptr KICK0;

    /*! Ptr to the KICK1 Bootcfg Registers */
    config Ptr KICK1;

    /*! Inter-processor interrupt id (varies per device) */
    config UInt INTERDSPINT;

    /*! Vector interrupt id for Hwi_create */
    config UInt DSPINT;

    /*! Function table */
    struct FxnTable {
        Fxn    func;
        UArg   arg;
    }


    /*!
     *  ======== isr ========
     *  Stub function plugged as interrupt handler
     */
    Void isr(UArg arg);

    struct Module_State {
        FxnTable   fxnTable[];  /* indexed by Source ID bit pos */
        UInt       numPlugged;  /* # of times the interrupt was registered */
    };
}
