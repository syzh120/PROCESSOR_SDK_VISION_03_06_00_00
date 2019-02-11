/*
 * Copyright (c) 2012-2014 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== InterruptIpu.xdc ========
 *
 */

import ti.sdo.utils.MultiProc;

/*!
 *  ======== InterruptIpu ========
 *  IPU interrupt manager
 */
module InterruptIpu inherits ti.sdo.ipc.notifyDrivers.IInterrupt
{
    /*!
     *  Maximum number of cores
     *
     *  @_nodoc
     */
    const UInt8 NUM_CORES = 11;

    /*!
     *  Maximum number of EVE cores
     *
     *  Although your device may have fewer EVE cores, `NUM_EVES` represents
     *  the maximum number of EVEs that may be present on a Vayu system.
     */
    const UInt8 NUM_EVES = 4;

    /*!
     *  Maximum number of IPU cores
     *
     *  @_nodoc
     */
    const UInt8 NUM_Ipu_CORES = 2;

    /*!
     *  Number of internal EVE mailboxes
     *
     *  Each EVE core has 3 mailboxes.
     *
     *  Although your device may have fewer EVE cores, `NUM_EVE_MBX` represents
     *  the maximum number of EVE mailboxes (including all EVE cores) that may
     *  be present.
     */
    const UInt8 NUM_EVE_MBX = NUM_EVES * 3;

    /*!
     *  Number of System mailboxes used by IPC
     *
     *  This represents the number of System mailboxes used by IPC.  IPC
     *  currently uses system mailboxes 5, 6, 7 and 8.
     */
    const UInt8 NUM_SYS_MBX = 4;

    /*!
     *  Base address for the mailbox subsystems
     *
     *  The `mailboxBaseAddr` array indicates the virtual addresses through
     *  which IPC will access various mailboxes.  The specific mailbox addresses
     *  each array index maps to follows:
     *  @p(blist)
     *    - 0  - EVE1 MBX0
     *    - 1  - EVE1 MBX1
     *    - 2  - EVE1 MBX2 (unused, do not assign)
     *    - 3  - EVE2 MBX0
     *    - 4  - EVE2 MBX1
     *    - 5  - EVE2 MBX2 (unused, do not assign)
     *    - 6  - EVE3 MBX0
     *    - 7  - EVE3 MBX1
     *    - 8  - EVE1 MBX2 (unused, do not assign)
     *    - 9  - EVE4 MBX0
     *    - 10 - EVE4 MBX1
     *    - 11 - EVE1 MBX2 (unused, do not assign)
     *    - 12  - System Mailbox 5
     *    - 13  - System Mailbox 6
     *    - 14  - System Mailbox 7
     *    - 15  - System Mailbox 8
     *  @p
     *
     *  Note that these mailboxes are not accessible at their physical
     *  addresses (in the 0x4XXX_XXXX range).  So default virtual addresses
     *  through which these mailboxes will be accessed are assigned in the
     *  0x6XXX_XXXX range.  Users must ensure these virtual addresses are
     *  correctly mapped to the 0x4XXX_XXXX-based phys addrs in each IPUs AMMU.
     */
    config UInt32 mailboxBaseAddr[NUM_EVE_MBX + NUM_SYS_MBX];

    /*!
     * Mailbox table for storing encoded Base Address, mailbox user Id,
     * and sub-mailbox index.
     *
     *  @_nodoc
     */
    config UInt32 mailboxTable[NUM_CORES * NUM_CORES];

    /*!
     *  Base address for the Ducati CTRL register
     */
    config UInt32 ducatiCtrlBaseAddr = 0x40001000;

    /*!
     *  Processor Id table
     *
     *  @_nodoc
     */
    config UInt32 procIdTable[NUM_CORES];

internal:

    /*! Statically retrieve procIds to avoid doing this at runtime */
    config UInt eve1ProcId     = MultiProc.INVALIDID;
    config UInt eve2ProcId     = MultiProc.INVALIDID;
    config UInt eve3ProcId     = MultiProc.INVALIDID;
    config UInt eve4ProcId     = MultiProc.INVALIDID;
    config UInt dsp1ProcId     = MultiProc.INVALIDID;
    config UInt dsp2ProcId     = MultiProc.INVALIDID;
    config UInt ipu1_0ProcId   = MultiProc.INVALIDID;
    config UInt ipu2_0ProcId   = MultiProc.INVALIDID;
    config UInt hostProcId     = MultiProc.INVALIDID;
    config UInt ipu1_1ProcId   = MultiProc.INVALIDID;
    config UInt ipu2_1ProcId   = MultiProc.INVALIDID;

    /*! Function table */
    struct FxnTable {
        Fxn    func;
        UArg   arg;
    }

    /*! Stub to be plugged for inter-ducati interrupts */
    Void intShmDucatiStub(UArg arg);

    /*! Stub to be plugged for intra-ducati interrupts */
    Void intShmMbxStub(UInt16 idx);

    struct Module_State {
        /*
         * Create a function table of length 8 (Total number of cores in the
         * System) for each M4 core.
         */
        FxnTable   fxnTable[NUM_CORES];
    };
}
