/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
 * ======== cio.c ========
 *  Sample Printf-based implementation of ti/xdais/trace.h
 */

#include <xdc/std.h>
#include <stdio.h>
#include <ti/xdais/trace.h>

/* Funtion that implements the printf based 'assert' function */
XDAS_Int32 ti_xdais_utils_trace_cio_assert(IALG_Handle alg, XDAS_Int32 mask,
        String format, String arg1, XDAS_Int32 arg2);

/* Funtion that implements the printf based 'trace' function */
XDAS_Int32 ti_xdais_utils_trace_cio_print(IALG_Handle alg, XDAS_Int32 mask,
        String format, ...);

/* ti/xdais/trace.h exposes the symbol XDAIS_TRACE_assert that needs to be
   defined by a suitable implementation of the 'assert' function */
XDAIS_TRACE_AssertFxn XDAIS_TRACE_assert = &ti_xdais_utils_trace_cio_assert;

/* ti/xdais/trace.h exposes the symbol XDAIS_TRACE_print that needs to be
   defined by a suitable implementation of the 'print' function */

XDAIS_TRACE_PrintFxn XDAIS_TRACE_print = &ti_xdais_utils_trace_cio_print;

extern XDAS_UInt32 ti_xdais_utils_trace_cio_globalMask;
/*
 * ======== ti_xdais_utils_trace_cio_assert ========
 * Spins in a while loop when alg makes an assert call, after printing out
 * the assert information.
 */
XDAS_Int32 ti_xdais_utils_trace_cio_assert(IALG_Handle alg, XDAS_Int32 mask,
        String format, String arg1, XDAS_Int32 arg2)
{
    ti_xdais_utils_trace_cio_print(alg, mask, format, arg1, arg2);

    while(1);

    /* never return */
}


/*
 *  ======== ti_xdais_utils_trace_cio_print ========
 */
XDAS_Int32 ti_xdais_utils_trace_cio_print(IALG_Handle alg, XDAS_Int32 mask,
        String format, ...)
{
    Int arg1, arg2, arg3, arg4, arg5, arg6;
    va_list va;

    /* Extract the arguments */
    va_start(va, format);

    arg1 = va_arg(va, Int);
    arg2 = va_arg(va, Int);
    arg3 = va_arg(va, Int);
    arg4 = va_arg(va, Int);
    arg5 = va_arg(va, Int);
    arg6 = va_arg(va, Int);

    va_end(va);

    /* Simple implementation of trace, ignores the mask.
       We could expose APIs that allow you to set different trace levels for
       different algorithm handles. For simplicity, we use global trace levels
    */

    /* Print the trace message if global trace is enabled for this level  */
    if (ti_xdais_utils_trace_cio_globalMask & mask)
        printf(format, arg1, arg2, arg3, arg4, arg5, arg6);

    return (1);
}

