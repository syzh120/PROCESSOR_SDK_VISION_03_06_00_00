#ifndef VLIB_PLATFORMS_H__
#define VLIB_PLATFORMS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef _HOST_BUILD

    #include "c6xsim/C6xSimulator.h"
    #include <assert.h>
    #define restrict
    #define _nassert assert
    #define __int40_t              long long
    #ifdef _MSC_VER /* If using MS Visual Studio Compiler */
        #define inline            __inline
        #define memalign(x, y)      _aligned_malloc(y, x)
        #define align_free         _aligned_free
        #define SET_ALIGN(x, y)     __declspec(align(y))
        #if !defined(__cplusplus)
            #if (_MSC_VER < 1800) /* Before MS Visual Studio 2013 (v12), C99 was not supported */
                typedef unsigned int _Bool;
                #define bool _Bool
                #define round(x)           ((x) + 0.5)
            #else
                #include <stdbool.h>
            #endif
        #endif
    #else
        #define align_free (free)
        #define SET_ALIGN(x, y)
    #endif
    #define CODE_SECTION(a, b)

#else  /* _HOST_BUILD */

    #include <c6x.h>
    #define align_free (free)
    #define SET_ALIGN(x, y)

    /* ----------------------------------------------------------------
     *  MISRAC Rules 19.4, 19.7, 19.10, 19.13 Deviation: These rules
     *  are concerned with the different interpretations of macros
     *  across compilers, however, the follow 2 lines are a construction
     *  taken directly from the DSP compiler documentation regarding
     *  the use of pragma macro redirection.  Since this section is only
     *  applicable to the DSP compiler (explicitly using the else condition
     *  of the _HOST_BUILD macro, these instances are acceptable.
     * ---------------------------------------------------------------- */
    #define EMIT_PRAGMA(x) _Pragma(#x)
    #define CODE_SECTION(fn, section) EMIT_PRAGMA(CODE_SECTION(fn, section))

#endif /* _HOST_BUILD */



#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* ! VLIB_PLATFORMS_H__ */

