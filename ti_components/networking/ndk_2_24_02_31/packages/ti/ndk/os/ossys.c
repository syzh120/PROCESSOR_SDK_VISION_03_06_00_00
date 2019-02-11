/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * */
/*
 * ======== ossys.c ========
 *
 * General System Functions
 *
 * This module is a bit of a catch-all for things that don't have
 * another home.
 *
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <netmain.h>
#include <_oskern.h>
#include <ctype.h>

/* Configuration */
OSENVCFG _oscfg = { DEF_DBG_PRINT_LEVEL, DEF_DBG_ABORT_LEVEL,
                    OS_TASKPRILOW_DEF, OS_TASKPRINORM_DEF,
                    OS_TASKPRIHIGH_DEF, OS_TASKPRIKERN_DEF,
                    OS_TASKSTKLOW_DEF, OS_TASKSTKNORM_DEF,
                    OS_TASKSTKHIGH_DEF };
/*
 *  ======== DbgPrintf ========
 *  Print Debug Messages to Log
 */
void DbgPrintf(uint Level, char *fmt, ... )
{
    uint Time, TimeMS;

    if( Level >= DBG_PRINT_LEVEL )
    {
        VaList arg_ptr;

        /* Get the log time */
        Time = llTimerGetTime(&TimeMS) - llTimerGetStartTime();

        /* pre-pend a time stamp */
        System_printf("%05d.%03d ", Time, TimeMS);

        /* print the format string */
        va_start(arg_ptr, fmt);
        System_vprintf(fmt, arg_ptr);
        va_end(arg_ptr);

        /* append newline to match original DbgPrintf implementation */
        System_printf("\n");
    }

    if(Level >= DBG_ABORT_LEVEL) {
        NC_NetStop(-1);
    }
}

/*
 *  ======== NDK_vsprintf ========
 *  NDK wrapper for sprintf function in order to remove miniPrintf
 *  and/or RTS dependency.
 */
int NDK_vsprintf(char *s, const char *format, va_list arg)
{
    return (System_vsprintf(s, (xdc_String)format, arg));
}

/*
 *  ======== NDK_sprintf ========
 *  NDK wrapper for sprintf function in order to remove miniPrintf
 *  and/or RTS dependency.
 */
int NDK_sprintf(char *s, const char *format, ...)
{
    int    ret_val;
    VaList arg_ptr;

    /* use XDC tools to do our dirty work */
    va_start(arg_ptr, format);
    ret_val = NDK_vsprintf(s, format, arg_ptr);
    va_end(arg_ptr);

    return (ret_val);
}

/*
 *  ======== stricmp ========
 *  Case insensitive string compare
 *  GNU compiler already defines this; TI code gen tools do not so add it here
 */
#if defined (__TI_COMPILER_VERSION__) || defined (__IAR_SYSTEMS_ICC__)
int stricmp( const char *s1, const char *s2)
{
    for ( ; (tolower(*s1) == tolower(*s2)); s1++, s2++)
        if (*s1 == '\0') return(0);   /* EOS */
    /*  Not equal */
    return( *s1 - *s2 );
}
#endif
