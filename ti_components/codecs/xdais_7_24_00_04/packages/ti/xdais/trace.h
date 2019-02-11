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
 *  ======== trace.h ========
 */

/**
 *  @file       ti/xdais/trace.h
 *
 *  @brief      Provides producers of content the ability to,
 *              in a runtime-independant way, add tracing.
 */
/**
 *  @defgroup   ti_xdais_TRACE        XDAIS Trace Support (Experimental)
 *
 *  @brief      The XDAIS Trace module.  Provides producers of algs
 *              the ability to, in a runtime-independant way, add tracing.
 *
 *  @remarks    Note
 *
 */
/*  Note        There are two definitions that affect which portions of trace
 *              are actually compiled into the client: @c XDAIS_TRACE_OUT and
 *              @c XDAIS_TRACE_ASSERT. If @c XDAIS_TRACE_OUT is set to 0 then all trace
 *              statements (except for assertions) will be compiled
 *              out of the client. If @c XDAIS_TRACE_ASSERT is set to 0 then
 *              assertions will be compiled out of the
 *              client.
 */

#ifndef ti_xdais_TRACE_
#define ti_xdais_TRACE_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_TRACE */
/*@{*/

#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>

/** @cond INTERNAL */
#ifndef XDAIS_TRACE_OUT
#define XDAIS_TRACE_OUT 0 /* 0 = "trace compiled out"; 1 = "trace active" */
#endif

#ifndef XDAIS_TRACE_ASSERT
#define XDAIS_TRACE_ASSERT 0 /* 0 = "trace-asserts compiled out"; 1 = "active"*/
#endif

/** @endcond */

/*
 *  New trace Class definitions.
 *
 * New proposal for how we should use different tracing classes: {
 *
 * - TRACE_ENTER (class 0): On entry to *and exit from* functions: consider
 *                       in general this class to be of interest to users
 * - TRACE_1CLASS : debugging info of interest to module developer only
 *
 * - TRACE_2CLASS : info for developer that *might* be of interest to users
 *
 * - TRACE_3CLASS : open (module developer can creatively use this one)
 *
 * - TRACE_4CLASS : info for developer that's likely to be important to the user
 *
 * - TRACE_5CLASS : benchmarking
 *
 * - TRACE_6CLASS : warnings
 *
 * - TRACE_7CLASS : errors
 *
 * }
 */

/**
 * @brief       Class Ids for tracing at different levels within functions.
 */
#define TRACE_ENTER        ((UInt8)0x01)
#define TRACE_1CLASS       ((UInt8)0x02)   /**< User classId 1. */
#define TRACE_2CLASS       ((UInt8)0x04)   /**< User classId 2. */
#define TRACE_3CLASS       ((UInt8)0x08)   /**< User classId 3. */
#define TRACE_4CLASS       ((UInt8)0x10)   /**< User classId 4. */

/**
 * @brief       User classId 5.  By convention, used for benchmarking related
 *              tracing.
 */
#define TRACE_5CLASS       ((UInt8)0x20)

/**
 * @brief       User classId 6.  By convention, used for internal warning related
 *              tracing.
 */
#define TRACE_6CLASS       ((UInt8)0x40)

/**
 * @brief       User classId 7.  By convention, used for internal error related
 *              tracing.
 */
#define TRACE_7CLASS       ((UInt8)0x80)

/**
 * @brief       Function prototype for the Assert function
 */
typedef XDAS_Int32 (* XDAIS_TRACE_AssertFxn)(IALG_Handle alg,
        XDAS_Int32 classId, String format, String arg1, XDAS_Int32 arg2);

/**
 * @brief       Function prototype for the Trace print function
 */
typedef XDAS_Int32 (* XDAIS_TRACE_PrintFxn)(IALG_Handle alg, XDAS_Int32 classId,
        String format, ...);
/*
 *  ======== XDAIS_TRACE_print ========
 */
/**
 *  @brief      Conditionally emit a trace statement.
 *
 *  @param[in]  alg        IALG_Handle to identify the algorithm. This is
 *                         required because level of trace may be different
 *                         for different codecs.
 *  @param[in]  classId    ClassId associated with this trace statement.
 *  @param[in]  format     printf-style format string.
 *
 *  @remarks    This function should not be called directly.  Users should
 *              use the macros wrapping this function instead
 *              (e.g. @c TRACE_0print())
 *
 *  @remarks    Most, but not all printf format strings are supported.
 *
 *  @note       A framework-specfic implementation of this function needs to
 *              linked if an XDAIS algorithm is built with trace enabled i.e,
 *              @c XDAIS_TRACE_OUT = 1
 *
 *  @sa         XDAIS_TRACE_assert()
 */
#if (XDAIS_TRACE_OUT == 1)
extern XDAIS_TRACE_PrintFxn XDAIS_TRACE_print;
#endif

/**
 *  @brief      Conditionally set off a trace-assert
 *
 *  @param[in]  alg        IALG_Handle to identify the algorithm. This is
 *                         required because level of trace may be different
 *                         for different codecs.
 *  @param[in]  classId    ClassId associated with this trace statement.
 *  @param[in]  format     printf-style format string.
 *
 *  @remarks    This function should not be called directly.  Users should
 *              use the macro wrapping this function instead.
 *              (e.g. @c XDAIS_TRACE_assert())
 *
 *  @note       A framework-specfic implementation of this function needs to
 *              linked if an XDAIS algorithm is built with trace-asserts
 *              enabled i.e, @c XDAIS_TRACE_ASSERT = 1
 *
 *
 *  @sa         XDAIS_TRACE_print()
 */
#if (XDAIS_TRACE_ASSERT == 1)
extern XDAIS_TRACE_AssertFxn XDAIS_TRACE_assert;
#endif

#if XDAIS_TRACE_ASSERT == 0

/** @cond INTERNAL */
#define TRACE_assert( alg, classId, expr )
/** @endcond */

#else   /* XDAIS_TRACE_ASSERT == 1 */


#define TRACE_assert(alg, classId, expr) \
        (!(expr) ? \
                XDAIS_TRACE_assert((alg), (classId), "assertion violation: %s, \
        line %d\n", FILE__, __LINE__), NULL : NULL)

#endif


#if XDAIS_TRACE_OUT == 0

/** @cond INTERNAL */

#define TRACE_0print( alg, classId, format )
#define TRACE_1print( alg, classId, format, arg1 )
#define TRACE_2print( alg, classId, format, arg1, arg2 )
#define TRACE_3print( alg, classId, format, arg1, arg2, arg3 )
#define TRACE_4print( alg, classId, format, arg1, arg2, arg3, arg4 )
#define TRACE_5print( alg, classId, format, arg1, arg2, arg3, arg4, arg5 )
#define TRACE_6print( alg, classId, format, arg1, arg2, arg3, arg4, arg5, arg6 )

/** @endcond */

#else   /* XDAIS_TRACE_OUT == 1 */

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_0print(alg, classId,  format) \
        XDAIS_TRACE_print((alg), (classId), (format))

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_1print(alg, classId, format, arg1) \
        XDAIS_TRACE_print((alg), (classId), (format), (arg1))

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_2print(alg, classId, format, arg1, arg2) \
        XDAIS_TRACE_print((alg), (classId), (format), (arg1), (arg2))

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_3print(alg, classId, format, arg1, arg2, arg3) \
        XDAIS_TRACE_print((alg), (classId), (format), (arg1), (arg2), (arg3))

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_4print(alg, classId, format, arg1, arg2, arg3, arg4) \
        XDAIS_TRACE_print((alg), (classId), (format), (arg1), (arg2), (arg3), \
        (arg4))

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_5print(alg, classId, format, arg1, arg2, arg3, arg4, arg5) \
        XDAIS_TRACE_print((alg), (classId), (format), (arg1), (arg2), (arg3), \
        (arg4), (arg5))

/**
 *  @sa         XDAIS_TRACE_print()
 */
#define TRACE_6print(alg, classId, format, arg1, arg2, arg3, arg4, arg5, arg6)\
        XDAIS_TRACE_print((alg), (classId), (format), (arg1),               \
        (arg2), (arg3), (arg4), (arg5), (arg6))



#endif /* XDAIS_TRACE_OUT */

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
