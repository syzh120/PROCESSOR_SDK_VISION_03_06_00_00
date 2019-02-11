/*
 * Copyright (c) 2011-2014, Texas Instruments Incorporated
 * Copyright (c) 2011, Google Inc
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
 *  ======== StackDbg.xdc ========
 */

/*!
 *  ======== StackDbg ========
 *
 *  Stack Debug Helper Module
 *
 */
module StackDbg {

    /*!
     * StackEntry - Structure containing elements for decoding stack
     */
    struct StackEntry {
        UInt instr;  /* address of calling instruction */
        UInt op;     /* opcode of calling instruction */
        UInt target; /* jump destination of calling instr (if immediate) */
        UInt sp;     /* ptr to work on stack that we're inspecting */
        UInt ret;    /* return address at *sp */
        UInt bogus;  /* return address matches code section, but not the other
                        criteria */
    };

    /*!
     * User-defined function pointer definition that can be called while
     * traversing the stack.  The function returns TRUE if it wants the stack
     * to continue being walked, and FALSE otherwise.
     */
    typedef Bool (*VisitFuncPtr)(StackEntry *, Void *);

    /*!
     *  ======== walkStack ========
     *  Walk the stack ranging at @base of @size bytes, starting at stack
     *  pointer @start pointing somewhere within the stack.  Walk the stack
     *  one 32-bit word at a time, calling the the caller-provided function
     *  @visit for each return address that is found.  The @visit callback
     *  is passed an instance of struct stack_entry populated, as well as an
     *  opaque user-provided value.
     */
    Void walkStack(UInt base, UInt size, UInt start, VisitFuncPtr visit,
                   Ptr user);

internal:
    struct Module_State {
        UInt    codeBegin;
        UInt    codeEnd;
    }

}
