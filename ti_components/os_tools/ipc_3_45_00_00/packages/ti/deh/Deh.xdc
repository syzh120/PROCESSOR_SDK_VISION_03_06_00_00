/*
 * Copyright (c) 2011-2014, Texas Instruments Incorporated
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
 *  ======== Deh.xdc ========
 *
 */

import ti.sysbios.knl.Task;
import ti.sysbios.knl.Swi;

/*!
 *  ======== Deh ========
 *  Device Error Handler
 *
 *  Exceptions that are unrecoverable need to be communicated to
 *  the host processor so that it can print debug information, do
 *  resource cleanup and ultimately reload a slave processor. The
 *  notification mechanism for sending events to the host processor
 *  has been consolidated in this module.
 */

@Template("./Deh.xdt")
@ModuleStartup
module Deh {

    /*!
     *  Exception Registers
     *
     *  Exception registers that will be filled in by the exception handler.
     *  NOTE: This is currently handling only ARM cores.
     */
    struct ExcRegs {
        Ptr  r0;    /* CPU registers */
        Ptr  r1;
        Ptr  r2;
        Ptr  r3;
        Ptr  r4;
        Ptr  r5;
        Ptr  r6;
        Ptr  r7;
        Ptr  r8;
        Ptr  r9;
        Ptr  r10;
        Ptr  r11;
        Ptr  r12;
        Ptr  sp;
        Ptr  lr;
        Ptr  pc;
        Ptr  psr;
        Ptr  ICSR;  /* NVIC registers */
        Ptr  MMFSR;
        Ptr  BFSR;
        Ptr  UFSR;
        Ptr  HFSR;
        Ptr  DFSR;
        Ptr  MMAR;
        Ptr  BFAR;
        Ptr  AFSR;
    };

    /*!
     *  Crash dump buffer size
     *
     *  Size of the buffer that will be used to store the crash dump data.
     *
     *  Default is 0x200 bytes
     */
    config SizeT bufSize = 0x200;

    /*!
     *  ======== sectionName ========
     *  Section where the internal character crashdump buffer is placed
     */
    metaonly config String sectionName = null;

    /*!
     *  ======== excHandler ========
     *  The exception handler function to be plugged into the hook exposed by
     *  BIOS for M3/M4 targets.
     *
     *  @param(excStack)    Stack pointer containing the exception data
     *  @param(lr)          Link register value
     */
    Void excHandler(UInt *excStack, UInt lr);

    /*!
     *  ======== excHandlerDsp ========
     *  Exception handler function to be plugged into the BIOS exception hook
     *  for C6x targets.
     */
    Void excHandlerDsp();

    /*!
     *  ======== idleBegin ========
     *  Idle function to be added to the Idle task. This function will be
     *  deprecated soon, and replaced directly with the equivalent function
     *  in the Watchdog module.
     */
    Void idleBegin();


internal:   /* not for client use */

    /*! Module state structure */
    struct Module_State {
        Char        outbuf[];      /* the output buffer */
        SizeT       isrStackSize;  /* stack info for ISR/SWI */
        Ptr         isrStackBase;
    };
}
