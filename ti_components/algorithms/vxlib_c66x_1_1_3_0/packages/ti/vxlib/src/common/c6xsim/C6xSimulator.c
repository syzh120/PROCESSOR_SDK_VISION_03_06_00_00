/****************************************************************************/
/*  C6xSimulator.c                                                          */
/*  Copyright (c) 1997-2005  Texas Instruments Incorporated                 */
/****************************************************************************/

/****************************************************************************/
/* the includes                                                             */
/****************************************************************************/
#include <math.h>
#include <float.h>
#include <stdio.h>

#include "C6xSimulator.h"                 // intrinsics prototypes
#include "_C6xSimulator_priv.h"           // private defs for C6xSimulator
#include "C6xSimulator_type_modifiers.h"  // define/undefine typing keywords

#define DEPRECATE_MSG(old, new)                                  \
    do {                                                          \
        static int    msg_emitted = 0;                                \
        if( !msg_emitted ) {                                          \
            fputs(# old " is deprecated in favor of " # new ".\n"     \
                  "See http://processors.wiki.ti.com/index.php/C6000_Intrinsics_and_Type_Double\n", stderr); }                                        \
        msg_emitted = 1;                                           \
    } while( 0 )

/****************************************************************************/
/* the defines                                                              */
/****************************************************************************/
#define DSP_CSR_SAT                       (1 << 9)

/****************************************************************************/
/* the globals                                                              */
/****************************************************************************/

/*
 *  The assumption is that users calling intrinsics such as _gmpy()
 *  will set the value of GPLYA before intrinsic entry.
 *  CSR is used in C6xSimulator to check if saturation occurred - since
 *  same test is often done in DSP code, equivalent functionality is kept.
 */
volatile uint32    CSR;  /* control status register */

#ifdef TMS320C64X
volatile uint32    GFPGFR; /* Galois field polynomial generator */
/* function register                 */
#endif

#ifdef TMS320C64PX
volatile uint32    GPLYA; /* GMPY Polynomial - A Side */
volatile uint32    GPLYB; /* GMPY Polynomial - B Side */
#endif

/****************************************************************************/
/* The functions for the TMS320C62X DSP, the TMS320C64X DSP and the         */
/* TMS320C64+ DSP                                                           */
/****************************************************************************/

#ifdef TMS320C62X
int32 _abs(int32 a)
{
    int32    y32;

    if( a == (int32)MIN_INT32 ) {
        y32 = MAX_INT32;
    } else if( a < 0 ) {
        y32 = -a;
    } else {
        y32 = a;
    }

    return (y32);
} /* end of _abs() function */

int32 _add2(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    y32.x2.lo = a32.x2.lo + b32.x2.lo;
    y32.x2.hi = a32.x2.hi + b32.x2.hi;
    return (y32.x1);
} /* end of _add2() function */

uint32 _clr(uint32 a, uint32 b, uint32 c)
{
    uint32    k, y32u;

    y32u = a;

    for( k=b; k <= c; k++ ) {
        y32u &= ~(1 << k);
    }

    return (y32u);
} /* end of _clr() function */

uint32 _clrr(uint32 a, int32 b)
{
    uint32    start, stop, y32u;

    if((b < 0) || (b > 0x03FF)) {
        return (FAIL);
    }

    start = b >> 5;
    stop = b & 0x01F;

    y32u = _clr(a, start, stop);

    return (y32u);
} /* end of _clrr() function */

int40 _dtol(uint64_d a)
{
    union reg40    y40;
    union reg64    a64;

    a64.x1u_d = a;

    // Fix for BZ 2272.  Code here formerly masked off the upper 24-bits of
    // the double.  Note the type reg40 is still used.  If the values come
    // back out of the reg40 with the fields x2.hi and x2.lo, then only
    // the lower 40-bits of the value are read.  But the x1 field, which is
    // implemented under the covers with a 64-bit type, still has the full
    // 64-bits assigned here.  This models how it works on the C6000 compiler,
    // for better or worse.  Note the code for BZ 1590 was removed, as it
    // no longer applied after these changes
    y40.x1 = a64.x1_ll;

    return (y40.x1);
} /* end of _dtol() function */

int40 _f2tol(__float2_t a)
{
    union reg40    y40;
    union reg64    a64;

    // Only this line is different from _dtol
    a64.x1u_ll = (uint64_ll) a.word1 << 32 | a.word0;

    y40.x1 = a64.x1_ll;

    return (y40.x1);
} /* end of _f2tol() function */

int32 _ext(int32 a, uint32 b, uint32 c)
{
    int32    y32;

    y32 = (a << b) >> c;

    return (y32);
} /* end of _ext() function */

int32 _extr(int32 a, int32 b)
{
    int32     y32;
    uint32    lshift, rshift;

    lshift = (b >> 5) & 0x1F;
    rshift = b & 0x01F;

    y32 = _ext(a, lshift, rshift);

    return (y32);
} /* end of _extr() function */

uint32 _extu(uint32 a, uint32 b, uint32 c)
{
    uint32    y32u;

    y32u = (a << b) >> c;

    return (y32u);
} /* end of _extu() function */

uint32 _extur(uint32 a, int32 b)
{
    uint32    lshift, rshift, y32u;

    if((b < 0) || (b > 0x03FF)) {
        return (FAIL);
    }

    lshift = b >> 5;
    rshift = b & 0x01F;

    y32u = _extu(a, lshift, rshift);

    return (y32u);
} /* end of _extur() function */

uint32 _ftoi(float32 a)
{
    union reg32    y32;

    y32.xf = a;

    return (y32.x1u);
} /* end of _ftoi() function */

uint32 _hi(uint64_d a)
{
    uint32         y32u;
    union reg64    a64;

    DEPRECATE_MSG(_hi, _hill);

    a64.x1u_d = a;

    y32u = _hill(a64.x1_ll);

    return (y32u);
} /* end of _hi() function */

uint32 _hill(int64_ll a)
{
    uint32         y32u;
    union reg64    a64;

    a64.x1_ll = a;

    y32u = a64.x2u.hi;

    return (y32u);
} /* end of _hill() function */

uint64_d _itod(uint32 a, uint32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_itod, itoll);

    y64.x1_ll = _itoll(a, b);

    return (y64.x1u_d);
} /* end of _itod() function */

double64 _ftod(float32 a, float32 b)  // Added in v7.2.x compiler
{
    union reg64    y64;

    y64.x2f.hi = a;
    y64.x2f.lo = b;

    return (y64.x1_d64);
} /* end of _ftod() function */

__float2_t _ftof2(float32 a, float32 b)  // Added in v7.2.x compiler
{
    union reg32   *p32;
    __float2_t     y;

    p32 = (union reg32 *) &a;
    y.word1 = p32->x1u;

    p32 = (union reg32 *) &b;
    y.word0 = p32->x1u;

    return (y);
} /* end of _ftof2() function */

float32 _itof(uint32 a)
{
    union reg32    y32;

    y32.x1u = a;

    return (y32.xf);
} /* end of _itof() function */

/* Fix for BZ 1679.  Return type must be *signed* 64-bit long to match   */
/* c6x.h                                                                 */
int64_ll _itoll(uint32 a, uint32 b)
{
    union reg64    y64;

    y64.x2u.hi = a;
    y64.x2u.lo = b;

    return (y64.x1_ll);
} /* end of _itoll() function */

int40 _labs(int40 a)
{
    union reg40    a40, y40;

    a40.x1 = a;

    /* Fix for BZ 1590.  All reg40 local variables must have their .x1[u]  */
    /* fields initialized.  The underlying size of reg40 is 64-bits.  The  */
    /* fields in the .x2[u] struct are only 40-bits.  Thus, assigning only */
    /* to .x2[u] fields may leave garbage in the upper 24 bits.            */
    y40.x1 = 0;

    if((a40.x2.hi == MIN_INT40_HI) && (a40.x2.lo == MIN_INT40_LO)) {
        y40.x2.hi = MAX_INT40_HI;
        y40.x2.lo = MAX_INT40_LO;
    } else if( a40.x2.hi < 0 ) {
        if( a40.x2.lo == 0 ) {
            y40.x2.hi = ~(a40.x2.hi - 1);
            y40.x2.lo = ~a40.x2.lo;
        } else {
            y40.x2.hi = ~a40.x2.hi;
            y40.x2.lo = ~(a40.x2.lo - 1);
        }
    } else {
        y40.x2.hi = a40.x2.hi;
        y40.x2.lo = a40.x2.lo;
    }

    return (y40.x1);
} /* end of _labs() function */

uint32 _lmbd(uint32 a, uint32 b)
{
    uint32    y32u;
    uint32    m32u;

    y32u = 0;
    m32u = MIN_INT32;

    if( a == 1 ) {
        while((b & m32u) == 0 ) {
            m32u >>= 1;
            y32u++;
            if( y32u == 32 ) {
                return (y32u);
            }
        }
    } else {
        while((b & m32u) != 0 ) {
            m32u >>= 1;
            y32u++;
            if( y32u == 32 ) {
                return (y32u);
            }
        }
    }

    return (y32u);
} /* end of _lmbd() function */

uint32 _lnorm(int40 a)
{
    uint32         y32u;
    union reg40    a40, b40, m40;

    a40.x1 = a;

    /* Fix for BZ 1590.  All reg40 local variables must have their .x1[u]  */
    /* fields initialized.  The underlying size of reg40 is 64-bits.  The  */
    /* fields in the .x2[u] struct are only 40-bits.  Thus, assigning only */
    /* to .x2[u] fields may leave garbage in the upper 24 bits.            */
    b40.x1u = 0;
    m40.x1u = 0;

    y32u = 0;
    m40.x2u.hi = (uint8)MIN_INT40_HI >> 1;
    m40.x2u.lo = (uint32)MIN_INT40_LO >> 1;

    if( a40.x2.hi < 0 ) {
        b40.x2u.hi = ~a40.x2.hi;
        b40.x2u.lo = ~a40.x2.lo;
    } else {
        b40.x2u.hi = a40.x2.hi;
        b40.x2u.lo = a40.x2.lo;
    }

    if((b40.x2u.hi == 0) && (b40.x2u.lo == 0)) {
        return (39);
    }

    while((b40.x2u.hi & m40.x2u.hi) != m40.x2u.hi ) {
        b40.x2u.hi = (b40.x2u.hi << 1) | (b40.x2u.lo >> 31);
        b40.x2u.lo <<= 1;
        y32u++;
    }

    return (y32u);
} /* end of _lnorm() function */

uint32 _lo(uint64_d a)
{
    uint32         y32u;
    union reg64    a64;

    DEPRECATE_MSG(_lo, _loll);

    a64.x1u_d = a;

    y32u = _loll(a64.x1_ll);

    return (y32u);
} /* end of _lo() function */

uint32 _loll(int64_ll a)
{
    uint32         y32u;
    union reg64    a64;

    a64.x1_ll = a;

    y32u = a64.x2u.lo;

    return (y32u);
} /* end of _loll() function */

int40 _lsadd(int32 a, int40 b)
{
    int16          k;
    union reg40    b40, c40, y40, y40tmp;

    b40.x1 = b;

    /* Fix for BZ 1590.  All reg40 local variables must have their .x1[u]  */
    /* fields initialized.  The underlying size of reg40 is 64-bits.  The  */
    /* fields in the .x2[u] struct are only 40-bits.  Thus, assigning only */
    /* to .x2[u] fields may leave garbage in the upper 24 bits.            */
    c40.x1    = 0;
    y40.x1    = 0;
    y40tmp.x1 = 0;

    c40.x2.hi = (a < 0) ? MAX_UINT8 : 0;
    c40.x2.lo = a;

    y40.x2.hi = b40.x2.hi;
    y40.x2.lo = b40.x2.lo;

    /* perform binary addition */
    for( k=0; k < 40; k++ ) {
        y40tmp.x2.hi = y40.x2.hi ^ c40.x2.hi;
        y40tmp.x2.lo = y40.x2.lo ^ c40.x2.lo;

        c40.x2.hi &= y40.x2.hi;
        c40.x2.lo &= y40.x2.lo;

        c40.x2.hi <<= 1;
        if( c40.x2.lo & MIN_INT32 ) {
            c40.x2.hi |= 0x1;
        }
        c40.x2.lo <<= 1;

        y40.x2.hi = y40tmp.x2.hi;
        y40.x2.lo = y40tmp.x2.lo;
    }

    /* see if saturation is required */
    /* see if a and b have the same sign */
    if(((a ^ (int32)b40.x2.hi) & MIN_INT32) == 0 ) {
        /* if the sign changed, sat */
        if((a ^ (int32)y40.x2.hi) & MIN_INT32 ) {
            y40.x2.hi = (a < 0) ? MIN_INT40_HI : MAX_INT40_HI;
            y40.x2.lo = (a < 0) ? MIN_INT40_LO : MAX_INT40_LO;
            CSR |= DSP_CSR_SAT;
        }
    }

    return (y40.x1);
} /* end of _lsadd() function */

int40 _lssub(int32 a, int40 b)
{
    int16          k;
    union reg40    b40, c40, y40, y40tmp;

    b40.x1 = b;

    /* Fix for BZ 1590.  All reg40 local variables must have their .x1[u]  */
    /* fields initialized.  The underlying size of reg40 is 64-bits.  The  */
    /* fields in the .x2[u] struct are only 40-bits.  Thus, assigning only */
    /* to .x2[u] fields may leave garbage in the upper 24 bits.            */
    c40.x1    = 0;
    y40.x1    = 0;
    y40tmp.x1 = 0;

    c40.x2.hi = (a < 0) ? MAX_UINT8 : 0;
    c40.x2.lo = a;

    /* negate b, ie y = -b */
    if( b40.x2.lo == 0 ) {
        y40.x2.hi = ~b40.x2.hi + 1;
        y40.x2.lo = ~b40.x2.lo;
    } else {
        y40.x2.hi = ~b40.x2.hi;
        y40.x2.lo = ~b40.x2.lo + 1;
    }

    /* perform binary addition */
    for( k=0; k < 40; k++ ) {
        y40tmp.x2.hi = y40.x2.hi ^ c40.x2.hi;
        y40tmp.x2.lo = y40.x2.lo ^ c40.x2.lo;

        c40.x2.hi &= y40.x2.hi;
        c40.x2.lo &= y40.x2.lo;

        c40.x2.hi <<= 1;
        if( c40.x2.lo & MIN_INT32 ) {
            c40.x2.hi |= 0x1;
        }
        c40.x2.lo <<= 1;

        y40.x2.hi = y40tmp.x2.hi;
        y40.x2.lo = y40tmp.x2.lo;
    }

    /* see if saturation is required */
    /* see if a and b are different sign */
    if(((a ^ (int32)b40.x2.hi) & MIN_INT32) != 0 ) {
        /* if the sign changed, sat */
        if((a ^ (int32)y40.x2.hi) & MIN_INT32 ) {
            y40.x2.hi = (a < 0) ? MIN_INT40_HI : MAX_INT40_HI;
            y40.x2.lo = (a < 0) ? MIN_INT40_LO : MAX_INT40_LO;
            CSR |= DSP_CSR_SAT;
        }
    }

    return (y40.x1);
} /* end of _lssub() function */

uint64_d _ltod(int40 a)
{
    union reg40    a40;
    union reg64    y64;

    a40.x1 = a;

    y64.x2.hi = (uint32)(a40.x2.hi & MAX_UINT8);
    y64.x2.lo = a40.x2.lo;

    return (y64.x1u_d);
} /* end of _ltod() function */

__float2_t _ltof2(int40 a)
{
    union reg40    a40;
    __float2_t     yf2;

    a40.x1 = a;

    yf2.word1 = (uint32)(a40.x2.hi & MAX_UINT8);
    yf2.word0 = a40.x2.lo;

    return (yf2);
}

int32 _mpy(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = a32.x2.lo * b32.x2.lo;

    return (y32);
} /* end of _mpy() function */

int32 _mpyh(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = a32.x2.hi * b32.x2.hi;

    return (y32);
} /* end of _mpyh() function */

int32 _mpyhsu(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = a32.x2.hi * b32.x2u.hi;

    return (y32);
} /* end of _mpyhsu() function */

uint32 _mpyhu(uint32 a, uint32 b)
{
    uint32         y32u;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1u = b;

    y32u = a32.x2u.hi * b32.x2u.hi;

    return (y32u);
} /* end of _mpyhu() function */

int32 _mpyhus(uint32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1 = b;

    y32 = a32.x2u.hi * b32.x2.hi;

    return (y32);
} /* end of _mpyhus() function */

int32 _mpyhl(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = a32.x2.hi * b32.x2.lo;

    return (y32);
} /* end of _mpyhl() function */

uint32 _mpyhlu(uint32 a, uint32 b)
{
    uint32         y32u;
    union reg32    a32u, b32u;

    a32u.x1 = a;
    b32u.x1 = b;

    y32u = a32u.x2u.hi * b32u.x2u.lo;

    return (y32u);
} /* end of _mpyhlu() function */

int32 _mpyhslu(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = a32.x2.hi * b32.x2u.lo;

    return (y32);
} /* end of _mpyhslu() function */

int32 _mpyhuls(uint32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1 = b;

    y32 = a32.x2u.hi * b32.x2.lo;

    return (y32);
} /* end of _mpyhuls() function */

int32 _mpylh(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = a32.x2.lo * b32.x2.hi;

    return (y32);
} /* end of _mpylh() function */

uint32 _mpylhu(uint32 a, uint32 b)
{
    uint32         y32u;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1u = b;

    y32u = a32.x2u.lo * b32.x2u.hi;

    return (y32u);
} /* end of _mpylhu() function */

int32 _mpylshu(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = a32.x2.lo * b32.x2u.hi;

    return (y32);
} /* end of _mpylshu() function */

int32 _mpyluhs(uint32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1 = b;

    y32 = a32.x2u.lo * b32.x2.hi;

    return (y32);
} /* end of _mpyluhs() function */

int32 _mpysu(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = a32.x2.lo * b32.x2u.lo;

    return (y32);
} /* end of _mpysu() function */

uint32 _mpyu(uint32 a, uint32 b)
{
    uint32         y32u;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1u = b;

    y32u = a32.x2u.lo * b32.x2u.lo;

    return (y32u);
} /* end of _mpyu() function */

int32 _mpyus(uint32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1 = b;

    y32 = a32.x2u.lo * b32.x2.lo;

    return (y32);
} /* end of _mpyus() function */

uint32 _norm(int32 a)
{
    uint32    b32u, m32u, y32u;

    y32u = 0;
    m32u = (uint32)MIN_INT32 >> 1;

    if( a < 0 ) {
        b32u = ~a;
    } else {
        b32u = a;
    }

    if( b32u == 0 ) {
        return (31);
    }

    while((b32u & m32u) != m32u ) {
        b32u <<= 1;
        y32u++;
    }

    return (y32u);
} /* end of _norm() function */

int32 _sadd(int32 a, int32 b)
{
    int32    y32;

    y32 = a + b;

    /* see if saturation is required */
    /* see if a and b have the same sign */
    if(((a ^ b) & MIN_INT32) == 0 ) {
        /* if the sign changed, sat */
        if((a ^ y32) & MIN_INT32 ) {
            y32 = (a < 0) ? MIN_INT32 : MAX_INT32;
            CSR |= DSP_CSR_SAT;
        }
    }

    return (y32);
} /* end of _sadd() function */

int32 _sat(int40 a)
{
    int32          y32;
    union reg40    a40;

    a40.x1 = a;

    if( a40.x2.hi > 0 || ((a40.x2.hi == 0) && (a40.x2.lo & MIN_INT32))) {
        y32 = MAX_INT32;
    } else if((a40.x2.hi < 0) && (a40.x2.lo == 0)) {
        y32 = MIN_INT32;
    } else {
        y32 = a40.x2.lo;
    }

    return (y32);
} /* end of _sat() function */

uint32 _set(uint32 a, uint32 b, uint32 c)
{
    uint32    k, y32u;

    y32u = a;

    for( k=b; k <= c; k++ ) {
        y32u |= 1 << k;
    }

    return (y32u);
} /* end of _set() function */

uint32 _setr(uint32 a, int32 b)
{
    uint32    start, stop, y32u;

    start = (b >> 5) & 0x1F;
    stop = b & 0x01F;

    y32u = _set(a, start, stop);

    return (y32u);
} /* end of _setr() function */

int32 _smpy(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = (a32.x2.lo * b32.x2.lo) << 1;

    if( y32 == MIN_INT32 ) {
        y32 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }

    return (y32);
} /* end of _smpy() function */

int32 _smpyh(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = (a32.x2.hi * b32.x2.hi) << 1;

    if( y32 == MIN_INT32 ) {
        y32 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }

    return (y32);
} /* end of _smpyh() function */

int32 _smpyhl(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = (a32.x2.hi * b32.x2.lo) << 1;

    if( y32 == MIN_INT32 ) {
        y32 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }

    return (y32);
} /* end of _smpyhl() function */

int32 _smpylh(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = (a32.x2.lo * b32.x2.hi) << 1;

    if( y32 == MIN_INT32 ) {
        y32 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }

    return (y32);
} /* end of _smpylh() function */

int32 _sshl(int32 a, uint32 b)
{
    int32    tmp;
    int32    y32;

    if( a == 0 ) {
        y32 = 0;
    } else if( b > 31 ) {
        if( a > 0 ) {
            y32 = MAX_INT32;
            CSR |= DSP_CSR_SAT;
        } else {
            y32 = MIN_INT32;
            CSR |= DSP_CSR_SAT;
        }
    } else {
        if( a > 0 ) {
            tmp = MAX_INT32 >> b;
            if( a > tmp ) {
                y32 = MAX_INT32;
                CSR |= DSP_CSR_SAT;
            } else {
                y32 = a << b;
            }
        } else {
            tmp = MIN_INT32 >> b;
            if( a < tmp ) {
                y32 = MIN_INT32;
                CSR |= DSP_CSR_SAT;
            } else {
                y32 = a << b;
            }
        }
    }

    return (y32);
} /* end of _sshl() function */

int32 _ssub(int32 a, int32 b)
{
    int32    y32;

    y32 = a - b;

    /* see if saturation is required */
    /* see if and b have the same sign */
    if(((a ^ b) & MIN_INT32) != 0 ) {
        /* if the sign changed, sat */
        if((a ^ y32) & MIN_INT32 ) {
            y32 = (a < 0) ? MIN_INT32 : MAX_INT32;
            CSR |= DSP_CSR_SAT;
        }
    }

    return (y32);
} /* end of _ssub() function */

int32 _sub2(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    y32.x2.lo = a32.x2.lo - b32.x2.lo;
    y32.x2.hi = a32.x2.hi - b32.x2.hi;
    return (y32.x1);
} /* end of _sub2() function */

uint32 _subc(uint32 a, uint32 b)
{
    uint32    y32;

    if( a >= b ) {
        y32 = ((a - b) << 1) + 1;
    } else {
        y32 = a << 1;
    }

    return (y32);
} /* end of _subc() function */

#endif


/***************************************************************************/
/* the additional functions for the TMS320C64X DSP and the TMS320C64+X DSP */

#ifdef TMS320C64X
int32 _abs2(int32 a)
{
    union reg32    a32, y32;

    a32.x1 = a;

    if( a32.x2.lo == MIN_INT16 ) {
        y32.x2.lo = MAX_INT16;
    } else if( a32.x2.lo < 0 ) {
        y32.x2.lo = -a32.x2.lo;
    } else {
        y32.x2.lo = a32.x2.lo;
    }

    if( a32.x2.hi == MIN_INT16 ) {
        y32.x2.hi = MAX_INT16;
    } else if( a32.x2.hi < 0 ) {
        y32.x2.hi = -a32.x2.hi;
    } else {
        y32.x2.hi = a32.x2.hi;
    }

    return (y32.x1);
} /* end of _abs2() function */

int32 _add4(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    y32.x4.lo1 = a32.x4.lo1 + b32.x4.lo1;
    y32.x4.lo2 = a32.x4.lo2 + b32.x4.lo2;
    y32.x4.hi1 = a32.x4.hi1 + b32.x4.hi1;
    y32.x4.hi2 = a32.x4.hi2 + b32.x4.hi2;

    return (y32.x1);
} /* end of _add4() function */

int32 _avg2(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    y32.x2.lo = (a32.x2.lo + b32.x2.lo + 1) >> 1;
    y32.x2.hi = (a32.x2.hi + b32.x2.hi + 1) >> 1;

    return (y32.x1);
} /* end of _avg2() function */

uint32 _avgu4(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x4u.lo1 = (a32.x4u.lo1 + b32.x4u.lo1 + 1) >> 1;
    y32.x4u.lo2 = (a32.x4u.lo2 + b32.x4u.lo2 + 1) >> 1;
    y32.x4u.hi1 = (a32.x4u.hi1 + b32.x4u.hi1 + 1) >> 1;
    y32.x4u.hi2 = (a32.x4u.hi2 + b32.x4u.hi2 + 1) >> 1;

    return (y32.x1u);
} /* end of _avgu4() function */

uint32 _bitc4(uint32 a)
{
    uint16         k;
    union reg32    a32, y32;

    a32.x1u = a;

    y32.x1u = 0;

    for( k=0; k < 8; k++ ) {
        if( a32.x4u.lo1 & (1 << k)) {
            y32.x4u.lo1++;
        }
        if( a32.x4u.lo2 & (1 << k)) {
            y32.x4u.lo2++;
        }
        if( a32.x4u.hi1 & (1 << k)) {
            y32.x4u.hi1++;
        }
        if( a32.x4u.hi2 & (1 << k)) {
            y32.x4u.hi2++;
        }
    }

    return (y32.x1u);
} /* end of _bitc4() function */

uint32 _bitr(uint32 a)
{
    uint16    i;
    uint32    k, x, y32;

    x = a;
    y32 = 0;

    k = 1 << 31;

    for( i=0; i < 32; i++ ) {
        y32=y32 + k * (x & 0x01);
        k = k >> 1;
        x = x >> 1;
    }

    return (y32);
} /* end of _bitr() function */

int32 _cmpeq2(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = 0;

    if( a32.x2.lo == b32.x2.lo ) {
        y32 += 1;
    }
    if( a32.x2.hi == b32.x2.hi ) {
        y32 += 2;
    }

    return (y32);
} /* end of _cmpeq2() function */

int32 _cmpeq4(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = 0;

    if( a32.x4.lo1 == b32.x4.lo1 ) {
        y32 += 1;
    }
    if( a32.x4.lo2 == b32.x4.lo2 ) {
        y32 += 2;
    }
    if( a32.x4.hi1 == b32.x4.hi1 ) {
        y32 += 4;
    }
    if( a32.x4.hi2 == b32.x4.hi2 ) {
        y32 += 8;
    }

    return (y32);
} /* end of _cmpeq4() function */

int32 _cmpgt2(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = 0;

    if( a32.x2.lo > b32.x2.lo ) {
        y32 += 1;
    }
    if( a32.x2.hi > b32.x2.hi ) {
        y32 += 2;
    }

    return (y32);
} /* end of _cmpgt2() function */

uint32 _cmpgtu4(uint32 a, uint32 b)
{
    uint32         y32u;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1u = b;

    y32u = 0;

    if( a32.x4u.lo1 > b32.x4u.lo1 ) {
        y32u += 1;
    }
    if( a32.x4u.lo2 > b32.x4u.lo2 ) {
        y32u += 2;
    }
    if( a32.x4u.hi1 > b32.x4u.hi1 ) {
        y32u += 4;
    }
    if( a32.x4u.hi2 > b32.x4u.hi2 ) {
        y32u += 8;
    }

    return (y32u);
} /* end of _cmpgtu4() function */

uint32 _deal(uint32 a)
{
    int16          k;
    union reg32    y32;

    y32.x1u = 0;

    for( k=31; k >= 0; k-=2 ) {
        if( a & (1 << k)) {
            y32.x2u.hi += 1 << (k >> 1);
        }
        if( a & (1 << (k - 1))) {
            y32.x2u.lo += 1 << (k >> 1);
        }
    }

    return (y32.x1u);
} /* end of _deal() function */

int32 _dotp2(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    if((a == 0x80008000) && (b == 0x80008000)) {
        y32 = MIN_INT32;
    } else {
        y32 = a32.x2.hi * b32.x2.hi + a32.x2.lo * b32.x2.lo;
    }

    return (y32);
} /* end of _dotp2() function */

int32 _dotpn2(int32 a, int32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1 = b;

    y32 = a32.x2.hi * b32.x2.hi - a32.x2.lo * b32.x2.lo;

    return (y32);
} /* end of _dotpn2() function */

int32 _dotpnrsu2(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = (a32.x2.hi * b32.x2u.hi - a32.x2.lo * b32.x2u.lo + 0x8000) >> 16;

    return (y32);
} /* end of _dotpnrsu2() function */

int32 _dotprsu2(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = (a32.x2.hi * b32.x2u.hi + a32.x2.lo * b32.x2u.lo + 0x8000) >> 16;

    return (y32);
} /* end of _dotprsu2() function */

int32 _dotpsu4(int32 a, uint32 b)
{
    int32          y32;
    union reg32    a32, b32;

    a32.x1 = a;
    b32.x1u = b;

    y32 = a32.x4.hi2 * b32.x4u.hi2 + a32.x4.hi1 * b32.x4u.hi1
          + a32.x4.lo2 * b32.x4u.lo2 + a32.x4.lo1 * b32.x4u.lo1;

    return (y32);
} /* end of _dotpsu4() function */

uint32 _dotpu4(uint32 a, uint32 b)
{
    uint32         y32u;
    union reg32    a32, b32;

    a32.x1u = a;
    b32.x1u = b;

    y32u = a32.x4u.hi2 * b32.x4u.hi2 + a32.x4u.hi1 * b32.x4u.hi1
           + a32.x4u.lo2 * b32.x4u.lo2 + a32.x4u.lo1 * b32.x4u.lo1;

    return (y32u);
} /* end of _dotpu4() function */

int32 _gmpy4(int32 a, int32 b)
{
    uint16         k, m, mask;
    int32          maxpower2;
    uint32         poly, c, ytmp[4];
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    m = (GFPGFR >> 24) + 1;
    poly = (GFPGFR & 0xFF) | 0x100;

    mask = 1;

    /* zero out the tmp array */
    for( k=0; k < 4; k++ ) {
        ytmp[k] = 0;
    }

    /* multiply the four sets of polynomials together */
    for( k=0; k < 8; k++ ) {
        c = mask & a32.x4u.hi2;
        ytmp[3] ^= b32.x4u.hi2 * c;

        c = mask & a32.x4u.hi1;
        ytmp[2] ^= b32.x4u.hi1 * c;

        c = mask & a32.x4u.lo2;
        ytmp[1] ^= b32.x4u.lo2 * c;

        c = mask & a32.x4u.lo1;
        ytmp[0] ^= b32.x4u.lo1 * c;

        mask <<= 1;
    }

    /* divide each result by the generator polynomial */
    for( k=0; k < 4; k++ ) {
        maxpower2 = 30 - _norm(ytmp[k]);

        while( maxpower2 >= m ) {
            c = poly << (maxpower2 - m);
            ytmp[k] ^= c;
            maxpower2 = 30 - _norm(ytmp[k]);
        }
    }

    y32.x4u.hi2 = (uint8)ytmp[3];
    y32.x4u.hi1 = (uint8)ytmp[2];
    y32.x4u.lo2 = (uint8)ytmp[1];
    y32.x4u.lo1 = (uint8)ytmp[0];

    return (y32.x1);
} /* end of _gmpy4() function */

int40 _ldotp2(int32 a, int32 b)
{
    uint16         k;
    union reg32    a32, b32;
    union reg64    c64, y64, y64tmp;

    a32.x1 = a;
    b32.x1 = b;

    if((a == 0x80008000) && (b == 0x80008000)) {
        y64.x2.hi = 0x00000000;
        y64.x2.lo = MIN_INT32;
    } else {
        c64.x2.lo = a32.x2.hi * b32.x2.hi;
        if( c64.x2.lo < 0 ) {
            c64.x2.hi = MAX_UINT32;
        } else {
            c64.x2.hi = 0;
        }

        y64.x2.lo = a32.x2.lo * b32.x2.lo;
        if( y64.x2.lo < 0 ) {
            y64.x2.hi = MAX_UINT32;
        } else {
            y64.x2.hi = 0;
        }

        /* perform binary addition */
        for( k=0; k < 64; k++ ) {
            y64tmp.x2.hi = y64.x2.hi ^ c64.x2.hi;
            y64tmp.x2.lo = y64.x2.lo ^ c64.x2.lo;

            c64.x2.hi &= y64.x2.hi;
            c64.x2.lo &= y64.x2.lo;

            c64.x2.hi <<= 1;
            if( c64.x2.lo & MIN_INT32 ) {
                c64.x2.hi |= 0x1;
            }
            c64.x2.lo <<= 1;

            y64.x2.hi = y64tmp.x2.hi;
            y64.x2.lo = y64tmp.x2.lo;
        }
    }

    return (y64.x1_ll);
} /* end of _ldotp2() function */

int32 _max2(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    if( a32.x2.hi > b32.x2.hi ) {
        y32.x2.hi = a32.x2.hi;
    } else {
        y32.x2.hi = b32.x2.hi;
    }

    if( a32.x2.lo > b32.x2.lo ) {
        y32.x2.lo = a32.x2.lo;
    } else {
        y32.x2.lo = b32.x2.lo;
    }

    return (y32.x1);
} /* end of _max2() function */

uint32 _maxu4(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    if( a32.x4u.hi2 > b32.x4u.hi2 ) {
        y32.x4u.hi2 = a32.x4u.hi2;
    } else {
        y32.x4u.hi2 = b32.x4u.hi2;
    }

    if( a32.x4u.hi1 > b32.x4u.hi1 ) {
        y32.x4u.hi1 = a32.x4u.hi1;
    } else {
        y32.x4u.hi1 = b32.x4u.hi1;
    }

    if( a32.x4u.lo2 > b32.x4u.lo2 ) {
        y32.x4u.lo2 = a32.x4u.lo2;
    } else {
        y32.x4u.lo2 = b32.x4u.lo2;
    }

    if( a32.x4u.lo1 > b32.x4u.lo1 ) {
        y32.x4u.lo1 = a32.x4u.lo1;
    } else {
        y32.x4u.lo1 = b32.x4u.lo1;
    }

    return (y32.x1u);
} /* end of _maxu4() function */

int32 _min2(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    if( a32.x2.hi < b32.x2.hi ) {
        y32.x2.hi = a32.x2.hi;
    } else {
        y32.x2.hi = b32.x2.hi;
    }

    if( a32.x2.lo < b32.x2.lo ) {
        y32.x2.lo = a32.x2.lo;
    } else {
        y32.x2.lo = b32.x2.lo;
    }

    return (y32.x1);
} /* end of _min2() function */

uint32 _minu4(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    if( a32.x4u.hi2 < b32.x4u.hi2 ) {
        y32.x4u.hi2 = a32.x4u.hi2;
    } else {
        y32.x4u.hi2 = b32.x4u.hi2;
    }

    if( a32.x4u.hi1 < b32.x4u.hi1 ) {
        y32.x4u.hi1 = a32.x4u.hi1;
    } else {
        y32.x4u.hi1 = b32.x4u.hi1;
    }

    if( a32.x4u.lo2 < b32.x4u.lo2 ) {
        y32.x4u.lo2 = a32.x4u.lo2;
    } else {
        y32.x4u.lo2 = b32.x4u.lo2;
    }

    if( a32.x4u.lo1 < b32.x4u.lo1 ) {
        y32.x4u.lo1 = a32.x4u.lo1;
    } else {
        y32.x4u.lo1 = b32.x4u.lo1;
    }

    return (y32.x1u);
} /* end of _minu4() function */

uint64_d _mpy2(int32 a, int32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_mpy2, _mpy2ll);

    y64.x1_ll = _mpy2ll(a, b);

    return (y64.x1_d);
} /* end of _mpy2() function */

int64_ll _mpy2ll(int32 a, int32 b)
{
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1 = b;

    y64.x2.hi = a32.x2.hi * b32.x2.hi;
    y64.x2.lo = a32.x2.lo * b32.x2.lo;

    return (y64.x1_ll);
} /* end of _mpy2ll() function */

int64_ll _mpyhill(int32 a, int32 b)
{
    int8           neg_y;
    uint16         abs_ahi, abs_ahi_error;
    uint32         abs_b_error;
    uint32         ahi_bhi, ahi_blo;
    uint32         tmp1, tmp2, tmp3;
    uint32         tmp1n, tmp2n, tmp3n;
    union reg32    a32, b32, abs_b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1 = b;

    if((a32.x2.hi == MIN_INT16) && (b == MIN_INT32)) {
        y64.x2u.hi = 0x4000;
        y64.x2u.lo = 0x00000000;
    }
    /* Fix for CQ #24738.  Checking for zero here keeps general case  */
    /* code simpler.  Avoids odd check for neg_value * zero.          */
    else if((a32.x2.hi == 0) || (b == 0)) {
        return (0);
    } else {
        /* determine sign of the result */
        neg_y = ((a32.x2.hi ^ b32.x2.hi) & MIN_INT16) ? 1 : 0;

        /* compute the absolute values */
        abs_ahi = _abs(a32.x2.hi);
        abs_b32.x1u = _abs(b);

        if( a32.x2.hi == MIN_INT16 ) {
            abs_ahi_error = 1;
        } else {
            abs_ahi_error = 0;
        }

        if( b == MIN_INT32 ) {
            abs_b_error = 1;
        } else {
            abs_b_error = 0;
        }

        /* perform the unsigned multiplies */
        ahi_bhi = abs_ahi * abs_b32.x2u.hi;
        ahi_blo = abs_ahi * abs_b32.x2u.lo;

        /* compute the first term */
        tmp1 = (ahi_blo & MAX_UINT16);

        /* compute the second term */
        tmp2 = (ahi_bhi & MAX_UINT16) + (ahi_blo >> 16);

        /* compute the third term */
        tmp3 = (ahi_bhi >> 16) + (tmp2 >> 16);

        /* remove any carry over bits */
        tmp2 &= MAX_UINT16;

        /* perform any correction for the error in the abs calculation */
        /* NOTE: only one error can occur due to earlier check         */
        if( abs_ahi_error ) {
            tmp1 += abs_b32.x2u.lo;
            tmp2 += abs_b32.x2u.hi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
        } else if( abs_b_error ) {
            tmp1 += abs_ahi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
        }

        if( neg_y ) {
            /* convert to a negative number */
            /* ~x + 1                       */
            tmp1n = tmp1 ^ MAX_UINT16;
            tmp2n = tmp2 ^ MAX_UINT16;
            tmp3n = tmp3 ^ MAX_UINT16;

            tmp1n += 1;
            tmp2n += (tmp1n >> 16);
            tmp3n += (tmp2n >> 16);

            /* remove any carry over bits   */
            tmp1n &= MAX_UINT16;
            tmp2n &= MAX_UINT16;

            y64.x2u.hi = (MAX_UINT16 << 16) | tmp3n;
            y64.x2u.lo = (tmp2n << 16) | tmp1n;
        } else {
            y64.x2u.hi = tmp3;
            y64.x2u.lo = (tmp2 << 16) | tmp1;
        }
    }

    return (y64.x1_ll);
} /* end of _mpyhill() function */

uint64_d _mpyhi(int32 a, int32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_mpyhi, _mpyhill);

    y64.x1_ll = _mpyhill(a, b);

    return (y64.x1u_d);
} /* end of _mpyhi() function */

//----------------------------------------------------------------------------
// BZ 2077.  Completely rewritten.  Now performs multiply, addition, and
// shift all in 64-bit math, returning the lower 32-bits.  Note the BZ was
// reported against _mpylir, but this function needs all the same changes.
//----------------------------------------------------------------------------
int32 _mpyhir(int32 a, int32 b)
{
    union reg32    a32;
    union reg64    a64, b64, y64;

    a32.x1 = a;
    if((a32.x2.hi == MIN_INT16) && (b == MIN_INT32)) {
        CSR |= DSP_CSR_SAT;
        return (MAX_INT32);
    }

    a64.x1_ll = a32.x2.hi;
    b64.x1_ll = b;
    y64.x1_ll = (a64.x1_ll * b64.x1_ll + 0x4000) >> 15;

    return (y64.x2.lo);
}

int64_ll _mpylill(int32 a, int32 b)
{
    int8           neg_y;
    uint16         abs_alo, abs_alo_error;
    uint32         abs_b_error;
    uint32         alo_bhi, alo_blo;
    uint32         tmp1, tmp2, tmp3;
    uint32         tmp1n, tmp2n, tmp3n;
    union reg32    a32, b32, abs_b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1 = b;

    if((a32.x2.lo == MIN_INT16) && (b == MIN_INT32)) {
        y64.x2u.hi = 0x4000;
        y64.x2u.lo = 0x00000000;
    }
    /* Fix for CQ #24738.  Checking for zero here keeps general case  */
    /* code simpler.  Avoids odd check for neg_value * zero.          */
    else if((a32.x2.lo == 0) || (b == 0)) {
        return (0);
    } else {
        /* determine sign of the result */
        neg_y = ((a32.x2.lo ^ b32.x2.hi) & MIN_INT16) ? 1 : 0;

        /* compute the absolute values */
        abs_alo = _abs(a32.x2.lo);
        abs_b32.x1u = _abs(b);

        if( a32.x2.lo == MIN_INT16 ) {
            abs_alo_error = 1;
        } else {
            abs_alo_error = 0;
        }

        if( b == MIN_INT32 ) {
            abs_b_error = 1;
        } else {
            abs_b_error = 0;
        }

        /* perform the unsigned multiplies */
        alo_bhi = abs_alo * abs_b32.x2u.hi;
        alo_blo = abs_alo * abs_b32.x2u.lo;

        /* compute the first term */
        tmp1 = (alo_blo & MAX_UINT16);

        /* compute the second term */
        tmp2 = (alo_bhi & MAX_UINT16) + (alo_blo >> 16);

        /* compute the third term */
        tmp3 = (alo_bhi >> 16) + (tmp2 >> 16);

        /* remove any carry over bits */
        tmp2 &= MAX_UINT16;

        /* perform any correction for the error in the abs calculation */
        /* NOTE: only one error can occur due to earlier check         */
        if( abs_alo_error ) {
            tmp1 += abs_b32.x2u.lo;
            tmp2 += abs_b32.x2u.hi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
        } else if( abs_b_error ) {
            tmp1 += abs_alo;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
        }

        if( neg_y ) {
            /* convert to a negative number */
            /* ~x + 1                       */
            tmp1n = tmp1 ^ MAX_UINT16;
            tmp2n = tmp2 ^ MAX_UINT16;
            tmp3n = tmp3 ^ MAX_UINT16;

            tmp1n += 1;
            tmp2n += (tmp1n >> 16);
            tmp3n += (tmp2n >> 16);

            /* remove any carry over bits   */
            tmp1n &= MAX_UINT16;
            tmp2n &= MAX_UINT16;

            y64.x2u.hi = (MAX_UINT16 << 16) | tmp3n;
            y64.x2u.lo = (tmp2n << 16) | tmp1n;
        } else {
            y64.x2u.hi = tmp3;
            y64.x2u.lo = (tmp2 << 16) | tmp1;
        }
    }

    return (y64.x1_ll);
} /* end of _mpylill() function */

uint64_d _mpyli(int32 a, int32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_mpyli, _mpylill);

    y64.x1_ll = _mpylill(a, b);

    return (y64.x1u_d);
} /* end of _mpyli() function */

//----------------------------------------------------------------------------
// BZ 2077.  Completely rewritten.  Now performs multiply, addition, and
// shift all in 64-bit math, returning the lower 32-bits.
//----------------------------------------------------------------------------
int32 _mpylir(int32 a, int32 b)
{
    union reg32    a32;
    union reg64    a64, b64, y64;

    a32.x1 = a;
    if((a32.x2.lo == MIN_INT16) && (b == MIN_INT32)) {
        CSR |= DSP_CSR_SAT;
        return (MAX_INT32);
    }

    a64.x1_ll = a32.x2.lo;
    b64.x1_ll = b;
    y64.x1_ll = (a64.x1_ll * b64.x1_ll + 0x4000) >> 15;

    return (y64.x2.lo);
}

int64_ll _mpysu4ll(int32 a, uint32 b)
{
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1u = b;

    y64.x4u.hi2 = a32.x4.hi2 * b32.x4u.hi2;
    y64.x4u.hi1 = a32.x4.hi1 * b32.x4u.hi1;
    y64.x4u.lo2 = a32.x4.lo2 * b32.x4u.lo2;
    y64.x4u.lo1 = a32.x4.lo1 * b32.x4u.lo1;

    return (y64.x1_ll);
} /* end of _mpysu4ll() function */

uint64_d _mpysu4(int32 a, uint32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_mpysu4, _mpysu4ll);

    y64.x1_ll = _mpysu4ll(a, b);

    return (y64.x1u_d);
} /* end of _mpysu4() function */

int64_ll _mpyu4ll(uint32 a, uint32 b)
{
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1u = a;
    b32.x1u = b;

    y64.x4u.hi2 = a32.x4u.hi2 * b32.x4u.hi2;
    y64.x4u.hi1 = a32.x4u.hi1 * b32.x4u.hi1;
    y64.x4u.lo2 = a32.x4u.lo2 * b32.x4u.lo2;
    y64.x4u.lo1 = a32.x4u.lo1 * b32.x4u.lo1;

    return (y64.x1_ll);
} /* end of _mpyu4ll() function */

uint64_d _mpyu4(uint32 a, uint32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_mpyu4, _mpyu4ll);

    y64.x1_ll = _mpyu4ll(a, b);

    return (y64.x1u_d);
} /* end of _mpyu4() function */

int32 _mvd(int32 a)
{
    return (a);
} /* end of _mvd() function */

uint32 _pack2(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x2u.hi = a32.x2u.lo;
    y32.x2u.lo = b32.x2u.lo;

    return (y32.x1u);
} /* end of _pack2() function */

uint32 _packh2(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x2u.hi = a32.x2u.hi;
    y32.x2u.lo = b32.x2u.hi;

    return (y32.x1u);
} /* end of _packh2() function */

uint32 _packh4(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x4u.hi2 = a32.x4u.hi2;
    y32.x4u.hi1 = a32.x4u.lo2;
    y32.x4u.lo2 = b32.x4u.hi2;
    y32.x4u.lo1 = b32.x4u.lo2;

    return (y32.x1u);
} /* end of _packh4() function */

uint32 _packhl2(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x2u.hi = a32.x2u.hi;
    y32.x2u.lo = b32.x2u.lo;

    return (y32.x1u);
} /* end of _packhl2() function */

uint32 _packl4(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x4u.hi2 = a32.x4u.hi1;
    y32.x4u.hi1 = a32.x4u.lo1;
    y32.x4u.lo2 = b32.x4u.hi1;
    y32.x4u.lo1 = b32.x4u.lo1;

    return (y32.x1u);
} /* end of _packl4() function */

uint32 _packlh2(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x2u.hi = a32.x2u.lo;
    y32.x2u.lo = b32.x2u.hi;

    return (y32.x1u);
} /* end of _packlh2() function */

#ifdef _MSC_VER
uint32 _rotl(uint32 a, int32 b)
#else
uint32 _rotl(uint32 a, uint32 b)
#endif
{
    uint16    shift;
    uint32    y;

    /* take 5 LSBs */
    shift = b & 0x1F;
    y = (a << shift) | (a >> (32 - shift));

    return (y);
} /* end of _rotl() function */

int32 _sadd2(int32 a, int32 b)
{
    int32          x;
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    x = a32.x2.hi + b32.x2.hi;
    if( x > MAX_INT16 ) {
        y32.x2.hi = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( x < MIN_INT16 ) {
        y32.x2.hi = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.hi = (int16)x;
    }

    x = a32.x2.lo + b32.x2.lo;
    if( x > MAX_INT16 ) {
        y32.x2.lo = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( x < MIN_INT16 ) {
        y32.x2.lo = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.lo = (int16)x;
    }

    return (y32.x1);
} /* end of _sadd2() function */

uint32 _saddu4(uint32 a, uint32 b)
{
    uint32         x;
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    x = a32.x4u.hi2 + b32.x4u.hi2;
    if( x > MAX_UINT8 ) {
        y32.x4u.hi2 = MAX_UINT8;
    } else {
        y32.x4u.hi2 = (uint8)x;
    }

    x = a32.x4u.hi1 + b32.x4u.hi1;
    if( x > MAX_UINT8 ) {
        y32.x4u.hi1 = MAX_UINT8;
    } else {
        y32.x4u.hi1 = (uint8)x;
    }

    x = a32.x4u.lo2 + b32.x4u.lo2;
    if( x > MAX_UINT8 ) {
        y32.x4u.lo2 = MAX_UINT8;
    } else {
        y32.x4u.lo2 = (uint8)x;
    }

    x = a32.x4u.lo1 + b32.x4u.lo1;
    if( x > MAX_UINT8 ) {
        y32.x4u.lo1 = MAX_UINT8;
    } else {
        y32.x4u.lo1 = (uint8)x;
    }

    return (y32.x1u);
} /* end of _saddu4() function */

int32 _saddus2(uint32 a, int32 b)
{
    int32          x;
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1 = b;

    x = a32.x2u.hi + b32.x2.hi;
    if( x > (int32)MAX_UINT16 ) {
        y32.x2.hi = (uint16)MAX_UINT16;
    } else if( x < (int32)MIN_UINT16 ) {
        y32.x2.hi = (uint16)MIN_UINT16;
    } else {
        y32.x2.hi = (uint16)x;
    }

    x = a32.x2u.lo + b32.x2.lo;
    if( x > (int32)MAX_UINT16 ) {
        y32.x2.lo = (uint16)MAX_UINT16;
    } else if( x < (int32)MIN_UINT16 ) {
        y32.x2.lo = (uint16)MIN_UINT16;
    } else {
        y32.x2.lo = (uint16)x;
    }

    return (y32.x1);
} /* end of _saddus2() function */

uint32 _shfl(uint32 a)
{
    int16          k;
    uint32         y32u;
    union reg32    a32;

    a32.x1u = a;

    y32u = 0;

    for( k=31; k >= 0; k-=2 ) {
        if( a32.x2u.hi & (1 << (k >> 1))) {
            y32u += 1 << k;
        }
        if( a32.x2u.lo & (1 << (k >> 1))) {
            y32u += 1 << (k - 1);
        }
    }

    return (y32u);
} /* end of _shfl() function */

uint32 _shlmb(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x4u.hi2 = b32.x4u.hi1;
    y32.x4u.hi1 = b32.x4u.lo2;
    y32.x4u.lo2 = b32.x4u.lo1;
    y32.x4u.lo1 = a32.x4u.hi2;

    return (y32.x1u);
} /* end of _shlmb() function */

int32 _shr2(int32 a, uint32 b)
{
    union reg32    a32, y32;

    a32.x1 = a;

    y32.x2.hi = a32.x2.hi >> b;
    y32.x2.lo = a32.x2.lo >> b;

    return (y32.x1);
} /* end of _shr2() function */

uint32 _shrmb(uint32 a, uint32 b)
{
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    y32.x4u.hi2 = a32.x4u.lo1;
    y32.x4u.hi1 = b32.x4u.hi2;
    y32.x4u.lo2 = b32.x4u.hi1;
    y32.x4u.lo1 = b32.x4u.lo2;

    return (y32.x1u);
} /* end of _shrmb() function */

uint32 _shru2(uint32 a, uint32 b)
{
    union reg32    a32, y32;

    a32.x1u = a;

    y32.x2u.hi = a32.x2u.hi >> b;
    y32.x2u.lo = a32.x2u.lo >> b;

    return (y32.x1u);
} /* end of _shru2() function */

int64_ll _smpy2ll(int32 a, int32 b)
{
    int32          x;
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1 = b;

    x = (a32.x2.lo * b32.x2.lo) << 1;
    if( x != MIN_INT32 ) {
        y64.x2.lo = x;
    } else {
        y64.x2.lo = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }

    x = (a32.x2.hi * b32.x2.hi) << 1;
    if( x != MIN_INT32 ) {
        y64.x2.hi = x;
    } else {
        y64.x2.hi = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }

    return (y64.x1_ll);
} /* end of _smpy2ll() function */

uint64_d _smpy2(int32 a, int32 b)
{
    union reg64    y64;

    DEPRECATE_MSG(_smpy2, _smpy2ll);

    y64.x1_ll = _smpy2ll(a, b);

    return (y64.x1_d);
} /* end of _smpy2() function */

int32 _spack2(int32 a, int32 b)
{
    union reg32    y32;

    if( a > MAX_INT16 ) {
        y32.x2.hi = MAX_INT16;
    } else if( a < MIN_INT16 ) {
        y32.x2.hi = MIN_INT16;
    } else {
        y32.x2.hi = (int16)a;
    }

    if( b > MAX_INT16 ) {
        y32.x2.lo = MAX_INT16;
    } else if( b < MIN_INT16 ) {
        y32.x2.lo = MIN_INT16;
    } else {
        y32.x2.lo = (int16)b;
    }

    return (y32.x1);
} /* end of _spack2() function */

uint32 _spacku4(int32 a, int32 b)
{
    union reg32    a32, b32;
    union reg32    y32;

    a32.x1 = a;
    b32.x1 = b;

    if( a32.x2.hi > (int16)MAX_UINT8 ) {
        y32.x4u.hi2 = (uint8)MAX_UINT8;
    } else if( a32.x2.hi < (int16)MIN_UINT8 ) {
        y32.x4u.hi2 = (uint8)MIN_UINT8;
    } else {
        y32.x4u.hi2 = (uint8)a32.x2.hi;
    }

    if( a32.x2.lo > (int16)MAX_UINT8 ) {
        y32.x4u.hi1 = (uint8)MAX_UINT8;
    } else if( a32.x2.lo < (int16)MIN_UINT8 ) {
        y32.x4u.hi1 = (uint8)MIN_UINT8;
    } else {
        y32.x4u.hi1 = (uint8)a32.x2.lo;
    }

    if( b32.x2.hi > (int16)MAX_UINT8 ) {
        y32.x4u.lo2 = (uint8)MAX_UINT8;
    } else if( b32.x2.hi < (int16)MIN_UINT8 ) {
        y32.x4u.lo2 = (uint8)MIN_UINT8;
    } else {
        y32.x4u.lo2 = (uint8)b32.x2.hi;
    }

    if( b32.x2.lo > (int16)MAX_UINT8 ) {
        y32.x4u.lo1 = (uint8)MAX_UINT8;
    } else if( b32.x2.lo < (int16)MIN_UINT8 ) {
        y32.x4u.lo1 = (uint8)MIN_UINT8;
    } else {
        y32.x4u.lo1 = (uint8)b32.x2.lo;
    }

    return (y32.x1u);
} /* end of _spacku4() function */

int32 _sshvl(int32 a, int32 b)
{
    int32    tmp;
    int32    y32;

    if( a == 0 ) {
        y32 = 0;
    } else if((b > 31) || (b < -31)) {
        if( a > 0 ) {
            y32 = MAX_INT32;
            CSR |= DSP_CSR_SAT;
        } else {
            y32 = MIN_INT32;
            CSR |= DSP_CSR_SAT;
        }
    } else {
        if( a > 0 ) {
            if( b > 0 ) {
                tmp = MAX_INT32 >> b;

                if( a > tmp ) {
                    y32 = MAX_INT32;
                    CSR |= DSP_CSR_SAT;
                } else {
                    y32 = a << b;
                }
            } else {
                y32 = a >> (-b);
            }
        } else {
            if( b > 0 ) {
                tmp = MIN_INT32 >> b;

                if( a < tmp ) {
                    y32 = MIN_INT32;
                    CSR |= DSP_CSR_SAT;
                } else {
                    y32 = a << b;
                }
            } else {
                y32 = a >> (-b);
            }
        }
    }

    return (y32);
} /* end of _sshvl() function */

int32 _sshvr(int32 a, int32 b)
{
    int32    tmp;
    int32    y32;

    if( a == 0 ) {
        y32 = 0;
    } else if((b > 31) || (b < -31)) {
        if( a > 0 ) {
            y32 = MAX_INT32;
            CSR |= DSP_CSR_SAT;
        } else {
            y32 = MIN_INT32;
            CSR |= DSP_CSR_SAT;
        }
    } else {
        if( a > 0 ) {
            if( b < 0 ) {
                tmp = MAX_INT32 >> (-b);

                if( a > tmp ) {
                    y32 = MAX_INT32;
                    CSR |= DSP_CSR_SAT;
                } else {
                    y32 = a << (-b);
                }
            } else {
                y32 = a >> b;
            }
        } else {
            if( b < 0 ) {
                tmp = MIN_INT32 >> (-b);

                if( a < tmp ) {
                    y32 = MIN_INT32;
                    CSR |= DSP_CSR_SAT;
                } else {
                    y32 = a << (-b);
                }
            } else {
                y32 = a >> b;
            }
        }
    }

    return (y32);
} /* end of _sshvr() function */

int32 _sub4(int32 a, int32 b)
{
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    y32.x4.lo1 = a32.x4.lo1 - b32.x4.lo1;
    y32.x4.lo2 = a32.x4.lo2 - b32.x4.lo2;
    y32.x4.hi1 = a32.x4.hi1 - b32.x4.hi1;
    y32.x4.hi2 = a32.x4.hi2 - b32.x4.hi2;

    return (y32.x1);
} /* end of _sub4() function */

int32 _subabs4(int32 a, int32 b)
{
    int32          x;
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    x = (int32)a32.x4u.hi2 - (int32)b32.x4u.hi2;
    if( x < (MIN_INT8 << 1)) {
        y32.x4u.hi2 = MAX_UINT8;
    } else if( x < 0 ) {
        y32.x4u.hi2 = (uint8)(-x);
    } else {
        y32.x4u.hi2 = (uint8)x;
    }

    x = (int32)a32.x4u.hi1 - (int32)b32.x4u.hi1;
    if( x < (MIN_INT8 << 1)) {
        y32.x4u.hi1 = MAX_UINT8;
    } else if( x < 0 ) {
        y32.x4u.hi1 = (uint8)(-x);
    } else {
        y32.x4u.hi1 = (uint8)x;
    }

    x = (int32)a32.x4u.lo2 - (int32)b32.x4u.lo2;
    if( x < (MIN_INT8 << 1)) {
        y32.x4u.lo2 = MAX_UINT8;
    } else if( x < 0 ) {
        y32.x4u.lo2 = (uint8)(-x);
    } else {
        y32.x4u.lo2 = (uint8)x;
    }

    x = (int32)a32.x4u.lo1 - (int32)b32.x4u.lo1;
    if( x < (MIN_INT8 << 1)) {
        y32.x4u.lo1 = MAX_UINT8;
    } else if( x < 0 ) {
        y32.x4u.lo1 = (uint8)(-x);
    } else {
        y32.x4u.lo1 = (uint8)x;
    }

    return (y32.x1);
} /* end of _subabs4() function */

uint32 _swap4(uint32 a)
{
    union reg32    a32, y32;

    a32.x1u = a;

    y32.x4u.hi2 = a32.x4u.hi1;
    y32.x4u.hi1 = a32.x4u.hi2;
    y32.x4u.lo2 = a32.x4u.lo1;
    y32.x4u.lo1 = a32.x4u.lo2;

    return (y32.x1u);
} /* end of _swap4() function */

uint32 _unpkhu4(uint32 a)
{
    union reg32    a32, y32;

    a32.x1u = a;

    y32.x1u = 0;

    y32.x4u.hi1 = a32.x4u.hi2;
    y32.x4u.lo1 = a32.x4u.hi1;

    return (y32.x1u);
} /* end of _unpkhu4() function */

uint32 _unpklu4(uint32 a)
{
    union reg32    a32, y32;

    a32.x1u = a;

    y32.x1u = 0;

    y32.x4u.hi1 = a32.x4u.lo2;
    y32.x4u.lo1 = a32.x4u.lo1;

    return (y32.x1u);
} /* end of _unpklu4() function */

uint32 _xpnd2(uint32 a)
{
    union reg32    y32;

    y32.x1u = 0;

    if( a & 0x02 ) {
        y32.x2u.hi = MAX_UINT16;
    }
    if( a & 0x01 ) {
        y32.x2u.lo = MAX_UINT16;
    }

    return (y32.x1u);
} /* end of _xpnd2() function */

uint32 _xpnd4(uint32 a)
{
    union reg32    y32;

    y32.x1u = 0;

    if( a & 0x08 ) {
        y32.x4u.hi2 = MAX_UINT8;
    }
    if( a & 0x04 ) {
        y32.x4u.hi1 = MAX_UINT8;
    }
    if( a & 0x02 ) {
        y32.x4u.lo2 = MAX_UINT8;
    }
    if( a & 0x01 ) {
        y32.x4u.lo1 = MAX_UINT8;
    }

    return (y32.x1u);
} /* end of _xpnd4() function */

#endif


/***************************************************************************/
/* the additional functions for the TMS320C64+X DSP                        */

#ifdef TMS320C64PX
int64_ll _addsub(int32 a, int32 b)
{
    union reg64    y64;

    y64.x2.lo = a - b;
    y64.x2.hi = a + b;

    return (y64.x1_ll);
} /* end of _addsub() function */

int64_ll _addsub2(uint32 a, uint32 b)
{
    union reg64    y64;

    y64.x2.lo = _sub2(a, b);
    y64.x2.hi = _add2(a, b);

    return (y64.x1_ll);
} /* end of _addsub2() function */

int64_ll _cmpy(uint32 a, uint32 b)
{
    int32          hi, lo;
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1 = b;

    if((a == 0x80008000) && (b == 0x80008000)) {
        lo = MAX_INT32;
        hi = 0;
        CSR |= DSP_CSR_SAT;
    } else {
        lo = a32.x2.lo * b32.x2.hi + a32.x2.hi * b32.x2.lo;
        hi = a32.x2.hi * b32.x2.hi - a32.x2.lo * b32.x2.lo;
    }

    y64.x2.hi = hi;
    y64.x2.lo = lo;

    return (y64.x1_ll);
} /* end of _cmpy() function */

uint32 _cmpyr(uint32 a, uint32 b)
{
    int32          hi, lo;
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    if((a == 0x80008000) && (b == 0x80008000)) {
        lo = MAX_INT32;
        hi = 0;
        CSR |= DSP_CSR_SAT;
    } else {
        lo = a32.x2.lo * b32.x2.hi + a32.x2.hi * b32.x2.lo;
        hi = a32.x2.hi * b32.x2.hi - a32.x2.lo * b32.x2.lo;
    }

    if( lo >= 0x7FFF8000 ) {
        y32.x2.lo = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.lo = (lo + 0x8000) >> 16;
    }

    if( hi >= 0x7FFF8000 ) {
        y32.x2.hi = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.hi = (hi + 0x8000) >> 16;
    }

    return (y32.x1u);
} /* end of _cmpyr() function */

uint32 _cmpyr1(uint32 a, uint32 b)
{
    int32          hi, lo;
    union reg32    a32, b32, y32;

    a32.x1u = a;
    b32.x1u = b;

    if((a == 0x80008000) && (b == 0x80008000)) {
        lo = MAX_INT32;
        hi = 0;
        CSR |= DSP_CSR_SAT;
    } else {
        lo = a32.x2.lo * b32.x2.hi + a32.x2.hi * b32.x2.lo;
        hi = a32.x2.hi * b32.x2.hi - a32.x2.lo * b32.x2.lo;
    }

    /*--------------------------------------------------------------------------
    Saturation, on C6X, occurs when a value, computed in a 40-bit ALU, is too
    big to be represented within 32-bits.  Even on this instruction, which only
    keeps the upper 16-bits of two different computations.  The check for
    saturation here occurs a bit earlier than on the C6X, so that the check can
    still be done in 32-bit host math.  The check occurs after the main
    computation, but before the addition of 0x4000 and left shift by 1.  So,
    the constants compared for saturation are computed:
       val : first value, in 33-bit representation, too big to fit in 32-bits
       constant = (val >> 1) - 0x4000
    --------------------------------------------------------------------------*/

    if( lo >= (int32)0x3FFFC000 ) { // (0x080000000 >> 1) - 0x4000
        y32.x2.lo = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( lo <= (int32)0xBFFFBFFF ) { // (0x17FFFFFFF >> 1) - 0x4000
        y32.x2.lo = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.lo = (lo + 0x4000) >> (16 - 1);
    }

    if( hi >= (int32)0x3FFFC000 ) { // (0x080000000 >> 1) - 0x4000h
        y32.x2.hi = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( hi <= (int32)0xBFFFBFFF ) { // 0x17FFFFFFF >> 1) - 0x4000
        y32.x2.hi = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.hi = (hi + 0x4000) >> (16 - 1);
    }

    return (y32.x1u);
} /* end of _cmpyr1() function */

int64_ll _ddotp4(uint32 a, uint32 b)
{
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1u = a;
    b32.x1u = b;

    y64.x2.lo = a32.x2.hi * b32.x4.lo2 + a32.x2.lo * b32.x4.lo1;
    y64.x2.hi = a32.x2.hi * b32.x4.hi2 + a32.x2.lo * b32.x4.hi1;

    return (y64.x1_ll);
} /* end of _ddotp4() function */

int64_ll _ddotph2(int64_ll a, uint32 b)
{
    union reg32    b32;
    union reg64    a64, y64;

    a64.x1_ll = a;
    b32.x1u = b;

    if((a64.x4.hi2 == MIN_INT16) &&
       (a64.x4.hi1 == MIN_INT16) &&
       (b == 0x80008000)) {
        y64.x2.hi = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        y64.x2.hi = a64.x4.hi2 * b32.x2.hi + a64.x4.hi1 * b32.x2.lo;
    }

    if((a64.x4.hi1 == MIN_INT16) &&
       (a64.x4.lo2 == MIN_INT16) &&
       (b == 0x80008000)) {
        y64.x2.lo = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        y64.x2.lo = a64.x4.hi1 * b32.x2.hi + a64.x4.lo2 * b32.x2.lo;
    }

    return (y64.x1_ll);
} /* end of _ddotph2() function */

uint32 _ddotph2r(int64_ll a, uint32 b)
{
    int32          tmp1, tmp2;
    union reg32    b32, y32;
    union reg64    a64;

    a64.x1_ll = a;
    b32.x1u = b;

    if((a64.x4.hi2 == MIN_INT16) &&
       (a64.x4.hi1 == MIN_INT16) &&
       (b == 0x80008000)) {
        tmp1 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        tmp1 = a64.x4.hi2 * b32.x2.hi + a64.x4.hi1 * b32.x2.lo;
        if((tmp1 >> 16) < MAX_INT16 ) {
            tmp1 += 0x00008000;
        }
    }

    if((a64.x4.hi1 == MIN_INT16) &&
       (a64.x4.lo2 == MIN_INT16) &&
       (b == 0x80008000)) {
        tmp2 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        tmp2 = a64.x4.hi1 * b32.x2.hi + a64.x4.lo2 * b32.x2.lo;
        if((tmp2 >> 16) < MAX_INT16 ) {
            tmp2 += 0x00008000;
        }
    }

    y32.x2.hi = tmp1 >> 16;
    y32.x2.lo = tmp2 >> 16;

    return (y32.x1u);
} /* end of _ddotph2r() function */

int64_ll _ddotpl2(int64_ll a, uint32 b)
{
    union reg32    b32;
    union reg64    a64, y64;

    a64.x1_ll = a;
    b32.x1u = b;

    if((a64.x4.lo2 == MIN_INT16) &&
       (a64.x4.lo1 == MIN_INT16) &&
       (b == 0x80008000)) {
        y64.x2.lo = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        y64.x2.lo = a64.x4.lo2 * b32.x2.hi + a64.x4.lo1 * b32.x2.lo;
    }

    if((a64.x4.hi1 == MIN_INT16) &&
       (a64.x4.lo2 == MIN_INT16) &&
       (b == 0x80008000)) {
        y64.x2.hi = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        y64.x2.hi = a64.x4.hi1 * b32.x2.hi + a64.x4.lo2 * b32.x2.lo;
    }

    return (y64.x1_ll);
} /* end of _ddotpl2() function */

uint32 _ddotpl2r(int64_ll a, uint32 b)
{
    int32          tmp1, tmp2;
    union reg32    b32, y32;
    union reg64    a64;

    a64.x1_ll = a;
    b32.x1u = b;

    if((a64.x4.lo2 == MIN_INT16) &&
       (a64.x4.lo1 == MIN_INT16) &&
       (b == 0x80008000)) {
        tmp1 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        tmp1 = a64.x4.lo2 * b32.x2.hi + a64.x4.lo1 * b32.x2.lo;
        if((tmp1 >> 16) < MAX_INT16 ) {
            tmp1 += 0x00008000;
        }
    }

    if((a64.x4.hi1 == MIN_INT16) &&
       (a64.x4.lo2 == MIN_INT16) &&
       (b == 0x80008000)) {
        tmp2 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    } else {
        tmp2 = a64.x4.hi1 * b32.x2.hi + a64.x4.lo2 * b32.x2.lo;
        if((tmp2 >> 16) < MAX_INT16 ) {
            tmp2 += 0x00008000;
        }
    }

    y32.x2.hi = tmp2 >> 16;
    y32.x2.lo = tmp1 >> 16;

    return (y32.x1u);
} /* end of _ddotpl2r() function */

int64_ll _dmv(uint32 a, uint32 b)
{
    union reg64    y64;

    y64.x2u.hi = a;
    y64.x2u.lo = b;

    return (y64.x1_ll);
} /* end of _dmv() function */

double64 _fdmv(float32 a, float32 b)
{
    return (_ftod(a, b));
}

__float2_t _fdmv_f2(float32 a, float32 b)
{
    return (_ftof2(a, b));
}

int64_ll _dpack2(uint32 a, uint32 b)
{
    union reg64    y64;

    y64.x2u.lo = _pack2(a, b);
    y64.x2u.hi = _packh2(a, b);

    return (y64.x1_ll);
} /* end of _dpack2() function */

int64_ll _dpackx2(uint32 a, uint32 b)
{
    union reg64    y64;

    y64.x2u.lo = _packlh2(a, b);
    y64.x2u.hi = _packlh2(b, a);

    return (y64.x1_ll);
} /* end of _dpackx2() function */

uint32 _gmpy(uint32 a, uint32 b)
{
    uint32    k, mask;
    uint32    poly;
    uint32    y, ytmp;

    y = 0;

    poly = GPLYA;
    /*  poly = GPLYB; */

    mask = 0x0100;

    for( k=0; k < 8; k++ ) {
        if( b & mask ) {
            y ^= a;
        }
        mask >>= 1;
        ytmp = y << 1;

        if( y & MIN_INT32 ) {
            y = poly ^ ytmp;
        } else {
            y = ytmp;
        }
    }

    if( b & 0x01 ) {
        y ^= a;
    }

    return (y);
} /* end of _gmpy() function */

int64_ll _mpy2ir(uint32 a, int32 b)
{
    union reg64    y64;

    y64.x2u.lo = _mpylir(a, b);
    y64.x2u.hi = _mpyhir(a, b);

    return (y64.x1_ll);
} /* end of _mpy2ir() function */

int32 _mpy32(int32 a, int32 b)
{
    int32          y32;
    union reg64    y64;

    y64.x1u_ll = _mpy32ll(a, b);

    y32 = y64.x2.lo;

    return (y32);
} /* end of _mpy32() function */

int64_ll _mpy32ll(int32 a, int32 b)
{
    int8           neg_y;
    uint32         abs_a_error;
    uint32         abs_b_error;
    uint32         ahi_bhi, ahi_blo, alo_bhi, alo_blo;
    uint32         tmp1, tmp2, tmp3, tmp4;
    uint32         tmp1n, tmp2n, tmp3n, tmp4n;
    union reg32    a32, b32, abs_a32, abs_b32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1 = b;

    if((a == MIN_INT32) && (b == MIN_INT32)) {
        y64.x2.hi = 0x40000000;
        y64.x2.lo = 0x00000000;
    } else {
        /* determine the sign of the result */
        neg_y = ((a32.x2.hi ^ b32.x2.hi) & MIN_INT16) ? 1 : 0;

        /* compute the absolute values */
        abs_a32.x1u = _abs(a);
        abs_b32.x1u = _abs(b);

        /* denote any errors in abs value */
        if( a == MIN_INT32 ) {
            abs_a_error = 1;
        } else {
            abs_a_error = 0;
        }

        if( b == MIN_INT32 ) {
            abs_b_error = 1;
        } else {
            abs_b_error = 0;
        }

        /* perform unsigned multiplications */
        ahi_bhi = abs_a32.x2u.hi * abs_b32.x2u.hi;
        ahi_blo = abs_a32.x2u.hi * abs_b32.x2u.lo;
        alo_bhi = abs_a32.x2u.lo * abs_b32.x2u.hi;
        alo_blo = abs_a32.x2u.lo * abs_b32.x2u.lo;

        /* compute the first term */
        tmp1 = (alo_blo & MAX_UINT16);

        /* compute the second term */
        tmp2 = (ahi_blo & MAX_UINT16) + (alo_bhi & MAX_UINT16) + (alo_blo >> 16);

        /* compute the third term */
        tmp3 = (ahi_bhi & MAX_UINT16) + (ahi_blo >> 16) + (alo_bhi >> 16) + (tmp2 >> 16);

        /* compute the fourth term */
        tmp4 = (ahi_bhi >> 16) + (tmp3 >> 16);

        /* remove any carry over bits */
        tmp2 &= MAX_UINT16;
        tmp3 &= MAX_UINT16;

        /* perform any correction for the error in the abs calculation */
        /* NOTE: only one error can occur due to earlier check         */
        if( abs_a_error ) {
            tmp1 += abs_b32.x2u.lo;
            tmp2 += abs_b32.x2u.hi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);
            tmp4 += (tmp3 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
            tmp3 &= MAX_UINT16;
        } else if( abs_b_error ) {
            tmp1 += abs_a32.x2u.lo;
            tmp2 += abs_a32.x2u.hi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);
            tmp4 += (tmp3 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
            tmp3 &= MAX_UINT16;
        }

        if( neg_y ) {
            /* convert to a negative number */
            /* ~x + 1                       */
            tmp1n = tmp1 ^ MAX_UINT16;
            tmp2n = tmp2 ^ MAX_UINT16;
            tmp3n = tmp3 ^ MAX_UINT16;
            tmp4n = tmp4 ^ MAX_UINT16;

            tmp1n += 1;
            tmp2n += (tmp1n >> 16);
            tmp3n += (tmp2n >> 16);
            tmp4n += (tmp3n >> 16);

            /* remove any carry over bits   */
            tmp1n &= MAX_UINT16;
            tmp2n &= MAX_UINT16;
            tmp3n &= MAX_UINT16;

            y64.x2.hi = (tmp4n << 16) | tmp3n;
            y64.x2.lo = (tmp2n << 16) | tmp1n;
        } else {
            y64.x2.hi = (tmp4 << 16) | tmp3;
            y64.x2.lo = (tmp2 << 16) | tmp1;
        }
    }

    return (y64.x1_ll);
} /* end of _mpy32ll() function */

int64_ll _mpy32su(int32 a, uint32 b)
{
    int8           neg_y;
    uint32         abs_a_error;
    uint32         ahi_bhi, ahi_blo, alo_bhi, alo_blo;
    uint32         tmp1, tmp2, tmp3, tmp4;
    uint32         tmp1n, tmp2n, tmp3n, tmp4n;
    union reg32    a32, b32, abs_a32;
    union reg64    y64;

    a32.x1 = a;
    b32.x1u = b;

    /* determine the sign of the result */
    neg_y = (a32.x2.hi & MIN_INT16) ? 1 : 0;

    /* compute the absolute value */
    abs_a32.x1u = _abs(a);

    /* denote any errors in abs value */
    if( a == MIN_INT32 ) {
        abs_a_error = 1;
    } else {
        abs_a_error = 0;
    }

    /* perform unsigned multiplications */
    ahi_bhi = abs_a32.x2u.hi * b32.x2u.hi;
    ahi_blo = abs_a32.x2u.hi * b32.x2u.lo;
    alo_bhi = abs_a32.x2u.lo * b32.x2u.hi;
    alo_blo = abs_a32.x2u.lo * b32.x2u.lo;

    /* compute the first term */
    tmp1 = (alo_blo & MAX_UINT16);

    /* compute the second term */
    tmp2 = (ahi_blo & MAX_UINT16) + (alo_bhi & MAX_UINT16) + (alo_blo >> 16);

    /* compute the third term */
    tmp3 = (ahi_bhi & MAX_UINT16) + (ahi_blo >> 16) + (alo_bhi >> 16) + (tmp2 >> 16);

    /* compute the fourth term */
    tmp4 = (ahi_bhi >> 16) + (tmp3 >> 16);

    /* remove any carry over bits */
    tmp2 &= MAX_UINT16;
    tmp3 &= MAX_UINT16;

    /* perform any correction for the error in the abs calculation */
    if( abs_a_error ) {
        tmp1 += b32.x2u.lo;
        tmp2 += b32.x2u.hi;

        tmp2 += (tmp1 >> 16);
        tmp3 += (tmp2 >> 16);
        tmp4 += (tmp3 >> 16);

        /* remove any carry over bits */
        tmp1 &= MAX_UINT16;
        tmp2 &= MAX_UINT16;
        tmp3 &= MAX_UINT16;
    }

    if( neg_y ) {
        /* convert to a negative number */
        /* ~x + 1                       */
        tmp1n = tmp1 ^ MAX_UINT16;
        tmp2n = tmp2 ^ MAX_UINT16;
        tmp3n = tmp3 ^ MAX_UINT16;
        tmp4n = tmp4 ^ MAX_UINT16;

        tmp1n += 1;
        tmp2n += (tmp1n >> 16);
        tmp3n += (tmp2n >> 16);
        tmp4n += (tmp3n >> 16);

        /* remove any carry over bits   */
        tmp1n &= MAX_UINT16;
        tmp2n &= MAX_UINT16;
        tmp3n &= MAX_UINT16;

        y64.x2u.hi = (tmp4n << 16) | tmp3n;
        y64.x2u.lo = (tmp2n << 16) | tmp1n;
    } else {
        y64.x2u.hi = (tmp4 << 16) | tmp3;
        y64.x2u.lo = (tmp2 << 16) | tmp1;
    }

    return (y64.x1_ll);
} /* end of _mpy32su() function */

int64_ll _mpy32u(uint32 a, uint32 b)
{
    uint32         ahi_bhi, ahi_blo, alo_bhi, alo_blo;
    uint32         tmp1, tmp2, tmp3, tmp4;
    union reg32    a32, b32;
    union reg64    y64;

    a32.x1u = a;
    b32.x1u = b;

    /* perform unsigned multiplications */
    ahi_bhi = a32.x2u.hi * b32.x2u.hi;
    ahi_blo = a32.x2u.hi * b32.x2u.lo;
    alo_bhi = a32.x2u.lo * b32.x2u.hi;
    alo_blo = a32.x2u.lo * b32.x2u.lo;

    /* compute the first term */
    tmp1 = (alo_blo & MAX_UINT16);

    /* compute the second term */
    tmp2 = (ahi_blo & MAX_UINT16) + (alo_bhi & MAX_UINT16) + (alo_blo >> 16);

    /* compute the third term */
    tmp3 = (ahi_bhi & MAX_UINT16) + (ahi_blo >> 16) + (alo_bhi >> 16) + (tmp2 >> 16);

    /* compute the fourth term */
    tmp4 = (ahi_bhi >> 16) + (tmp3 >> 16);

    /* remove any carry over bits */
    tmp2 &= MAX_UINT16;
    tmp3 &= MAX_UINT16;

    y64.x2u.hi = (tmp4 << 16) | tmp3;
    y64.x2u.lo = (tmp2 << 16) | tmp1;

    return (y64.x1_ll);
} /* end of _mpy32u() function */

int64_ll _mpy32us(uint32 a, int32 b)
{
    union reg64    y64;

    y64.x1u_ll = _mpy32su(b, a);

    return (y64.x1_ll);
} /* end of _mpy32us() function */

uint32 _rpack2(int32 a, int32 b)
{
    union reg32    y32;

    if( a > (MAX_INT32 >> 1)) {
        y32.x2.hi = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( a < (MIN_INT32 >> 1)) {
        y32.x2.hi = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.hi = ((a << 1) >> 16) & MAX_UINT16;
    }

    if( b > (MAX_INT32 >> 1)) {
        y32.x2.lo = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( b < (MIN_INT32 >> 1)) {
        y32.x2.lo = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.lo = ((b << 1) >> 16) & MAX_UINT16;
    }

    return (y32.x1u);
} /* end of _rpack2() function */

int64_ll _saddsub(int32 a, int32 b)
{
    union reg64    y64;

    y64.x2u.lo = _ssub(a, b);
    y64.x2u.hi = _sadd(a, b);

    return (y64.x1_ll);
} /* end of _saddsub() function */

int64_ll _saddsub2(uint32 a, uint32 b)
{
    union reg64    y64;

    y64.x2u.lo = _ssub2(a, b);
    y64.x2u.hi = _sadd2(a, b);

    return (y64.x1_ll);
} /* end of _saddsub2() function */

int64_ll _shfl3(uint32 a, uint32 b)
{
    int32          i;
    int32          b0, b1, b2;
    union reg64    y64;

    b0 = b & MAX_UINT16;
    b1 = a & MAX_UINT16;
    b2 = (a >> 16) & MAX_UINT16;

    y64.x2u.hi = 0;
    y64.x2u.lo = 0;

    /* compute bits 0 to 31 */
    for( i=0; i < 11; i++ ) {
        y64.x2u.lo |= ((b0 >> i) & 0x1) << (3 * i + 0);
        y64.x2u.lo |= ((b1 >> i) & 0x1) << (3 * i + 1);
        if( i < 10 ) {
            y64.x2u.lo |= ((b2 >> i) & 0x1) << (3 * i + 2);
        }
    }

    /* compute bit 32 */
    /* NOTE: set i=10 */
    y64.x2u.hi |= ((b2 >> 10) & 0x1) << (3 * 10 + 2 - 32);

    /* compute bits 33 to 47 */
    for( i=11; i < 16; i++ ) {
        y64.x2u.hi |= ((b0 >> i) & 0x1) << (3 * i + 0 - 32);
        y64.x2u.hi |= ((b1 >> i) & 0x1) << (3 * i + 1 - 32);
        y64.x2u.hi |= ((b2 >> i) & 0x1) << (3 * i + 2 - 32);
    }

    return (y64.x1_ll);
} /* end of _shfl3() function */

int32 _smpy32(int32 a, int32 b)
{
    int8           neg_y;
    uint32         abs_a_error;
    uint32         abs_b_error;
    uint32         ahi_bhi, ahi_blo, alo_bhi, alo_blo;
    uint32         tmp1, tmp2, tmp3, tmp4;
    uint32         tmp1n, tmp2n, tmp3n, tmp4n;
    int32          y32;
    union reg32    a32, b32, abs_a32, abs_b32;

    a32.x1 = a;
    b32.x1 = b;

    if((a == MIN_INT32) && (b == MIN_INT32)) {
        y32 = MAX_INT32;
        CSR |= DSP_CSR_SAT;
    }
    /* Fix for CQ #24738.  Checking for zero here keeps general case  */
    /* code simpler.  Avoids odd check for neg_value * zero.          */
    else if((a == 0) || (b == 0)) {
        return (0);
    } else {
        a32.x1 = a;
        b32.x1 = b;

        /* determine the sign of the result */
        neg_y = ((a32.x2.hi ^ b32.x2.hi) & MIN_INT16) ? 1 : 0;

        /* compute the absolute values */
        abs_a32.x1u = _abs(a);
        abs_b32.x1u = _abs(b);

        /* denote any errors in abs value */
        if( a == MIN_INT32 ) {
            abs_a_error = 1;
        } else {
            abs_a_error = 0;
        }

        if( b == MIN_INT32 ) {
            abs_b_error = 1;
        } else {
            abs_b_error = 0;
        }

        /* perform unsigned multiplications */
        ahi_bhi = abs_a32.x2u.hi * abs_b32.x2u.hi;
        ahi_blo = abs_a32.x2u.hi * abs_b32.x2u.lo;
        alo_bhi = abs_a32.x2u.lo * abs_b32.x2u.hi;
        alo_blo = abs_a32.x2u.lo * abs_b32.x2u.lo;

        /* compute the first term */
        tmp1 = (alo_blo & MAX_UINT16);

        /* compute the second term */
        tmp2 = (ahi_blo & MAX_UINT16) +
               (alo_bhi & MAX_UINT16) + (alo_blo >> 16);

        /* compute the third term */
        tmp3 = (ahi_bhi & MAX_UINT16) +
               (ahi_blo >> 16) + (alo_bhi >> 16) + (tmp2 >> 16);

        /* compute the fourth term */
        tmp4 = (ahi_bhi >> 16) + (tmp3 >> 16);

        /* remove any carry over bits */
        tmp2 &= MAX_UINT16;
        tmp3 &= MAX_UINT16;

        /* perform any correction for the error in the abs calculation */
        /* NOTE: only one error can occur due to earlier check         */
        if( abs_a_error ) {
            tmp1 += abs_b32.x2u.lo;
            tmp2 += abs_b32.x2u.hi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);
            tmp4 += (tmp3 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
            tmp3 &= MAX_UINT16;
        } else if( abs_b_error ) {
            tmp1 += abs_a32.x2u.lo;
            tmp2 += abs_a32.x2u.hi;

            tmp2 += (tmp1 >> 16);
            tmp3 += (tmp2 >> 16);
            tmp4 += (tmp3 >> 16);

            /* remove any carry over bits */
            tmp1 &= MAX_UINT16;
            tmp2 &= MAX_UINT16;
            tmp3 &= MAX_UINT16;
        }

        if( neg_y ) {
            /* convert to a negative number */
            /* ~x + 1                       */
            tmp1n = tmp1 ^ MAX_UINT16;
            tmp2n = tmp2 ^ MAX_UINT16;
            tmp3n = tmp3 ^ MAX_UINT16;
            tmp4n = tmp4 ^ MAX_UINT16;

            tmp1n += 1;
            tmp2n += (tmp1n >> 16);
            tmp3n += (tmp2n >> 16);
            tmp4n += (tmp3n >> 16);

            /* remove any carry over bits   */
            tmp1n &= MAX_UINT16;
            tmp2n &= MAX_UINT16;
            tmp3n &= MAX_UINT16;

            if( tmp4n > MAX_UINT16 ) {
                y32 = MIN_INT32;
            } else {
                /* Fix for BZ 1583: Insure the MSB of tmp3n is not thrown away. */
                /* Note tmp3n is not anded with MAX_UINT16.                     */
                /* Fix for BZ 1602: Copy the MSB of tmp2n into the LSB of y32.  */
                y32 =   (((tmp4n << 1) & MAX_UINT16) << 16) | (tmp3n << 1)
                      | ((tmp2n & 0x8000) != 0);
            }
        } else {
            if( tmp4 > (MAX_INT16 >> 1)) {
                y32 = MAX_INT32;
            } else {
                /* Fix for BZ 1583. Insure the MSB of tmp3 is not thrown away. */
                /* Note tmp3 is not anded with MAX_UINT16.                     */
                /* Fix for BZ 1602: Copy the MSB of tmp2 into the LSB of y32.  */
                y32 =   (((tmp4 << 1) & MAX_UINT16) << 16) | (tmp3 << 1)
                      | ((tmp2 & 0x8000) != 0);
            }
        }
    }

    return (y32);
} /* end of _smpy32() function */

int32 _ssub2(int32 a, int32 b)
{
    int32          x;
    union reg32    a32, b32, y32;

    a32.x1 = a;
    b32.x1 = b;

    x = a32.x2.hi - b32.x2.hi;
    if( x > MAX_INT16 ) {
        y32.x2.hi = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( x < MIN_INT16 ) {
        y32.x2.hi = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.hi = (int16)x;
    }

    x = a32.x2.lo - b32.x2.lo;
    if( x > MAX_INT16 ) {
        y32.x2.lo = MAX_INT16;
        CSR |= DSP_CSR_SAT;
    } else if( x < MIN_INT16 ) {
        y32.x2.lo = MIN_INT16;
        CSR |= DSP_CSR_SAT;
    } else {
        y32.x2.lo = (int16)x;
    }

    return (y32.x1);
} /* end of _ssub2() function */

uint32 _xormpy(uint32 a, uint32 b)
{
    uint32    i;
    uint32    mask, y;

    y = 0;
    mask = 0x100;

    for( i=0; i < 8; i++ ) {
        if( b & mask ) {
            y ^= a;
        }
        mask >>= 1;
        y <<= 1;
    }

    if( b & 0x1 ) {
        y ^= a;
    }

    return (y);
} /* end of _xormpy() function */

#endif

/***************************************************************************/
/* the additional functions for the TMS320C67xx DSP                        */
/***************************************************************************/
#ifdef TMS320C67X

double64 _fabs(double64 a)
{
    return (fabs(a));
}

float32 _fabsf(float32 a)
{
    return ((float32) fabs((double64) a));
}

#endif /* #ifdef TMS320C67X */

/***************************************************************************/
/* the additional functions for the TMS320C66xx DSP                        */
/***************************************************************************/
#ifdef TMS320C66X

__float2_t _complex_mpysp(__float2_t a, __float2_t b)
{
    __x128_t    tmp;

    tmp = _cmpysp(a, b);
    return (_daddsp(_hif2_128(tmp), _lof2_128(tmp)));
}

__float2_t _complex_conjugate_mpysp(__float2_t a, __float2_t b)
{
    __x128_t    tmp;

    tmp = _cmpysp(a, b);
    return (_dsubsp(_hif2_128(tmp), _lof2_128(tmp)));
}

double64 _fdmvd(float32 a, float32 b)
{
    return (_ftod(a, b));
}

__float2_t _fdmvd_f2(float32 a, float32 b)
{
    return (_ftof2(a, b));
}

#endif /* #ifdef TMS320C66X */

/*
The next four functions are added purely to allow those deprecate messages
to be emitted.  See the related comment in C6xSimulator.h.
*/

#ifdef TMS320C62X
int64_d *_amemd8_helper(void *ptr)
{
    DEPRECATE_MSG(_amemd8, _amem8);
    return ((int64_d *) ptr);
}

const int64_d *_amemd8_const_helper(void *ptr)
{
    DEPRECATE_MSG(_amemd8_const, _amem8_const);
    return ((const int64_d *) ptr);
}

#endif

#ifdef TMS320C64X
int64_d *_memd8_helper(void *ptr)
{
    DEPRECATE_MSG(_memd8, _mem8);
    return ((int64_d *) ptr);
}

const int64_d *_memd8_const_helper(void *ptr)
{
    DEPRECATE_MSG(_memd8_const, _mem8_const);
    return ((const int64_d *) ptr);
}

#endif

/*
 *  Automated Revision Information
 *  Changed: $Date: 2011-02-24 14:19:54 -0600 (Thu, 24 Feb 2011) $
 *  Revision: $Revision: 10006 $
 */

/*

C6000 Host Intrinsics Software License Agreement


IMPORTANT - PLEASE READ THE FOLLOWING LICENSE AGREEMENT CAREFULLY.
THIS IS A LEGALLY BINDING AGREEMENT.  AFTER YOU READ THIS LICENSE
AGREEMENT, YOU WILL BE ASKED WHETHER YOU ACCEPT AND AGREE TO THE
TERMS OF THIS LICENSE AGREEMENT.  DO NOT CLICK  "I HAVE READ AND AGREE"
UNLESS: (1) YOU ARE AUTHORIZED TO ACCEPT AND AGREE TO THE TERMS OF THIS
LICENSE AGREEMENT ON BEHALF OF YOURSELF AND YOUR COMPANY; AND (2) YOU
INTEND TO ENTER INTO AND TO BE BOUND BY THE TERMS OF THIS LEGALLY
BINDING AGREEMENT ON BEHALF OF YOURSELF AND YOUR COMPANY.


Important - Read carefully: This C6000 Host Intrinsics Software License
Agreement ("Agreement") is a legal agreement between you (either an
individual or entity) and Texas Instruments Incorporated ("TI").  The
"Licensed Materials" subject to this Agreement include the software
programs that TI has granted you access to download with this Agreement
and any "on-line" or electronic documentation associated with these
programs, or any portion thereof, as well as any updates or upgrades to such
software programs and documentation, if any, or any portion thereof,
provided to you in TI's sole discretion.  By installing, copying or otherwise
using the Licensed Materials you agree to abide by the following provisions.
This Agreement is displayed for you to read prior to using the Licensed
Materials.  If you choose not to accept or agree with these provisions, do not
download or install the Licensed Materials.

1.  License Grant and Use Restrictions.

a.  License Grant.  Subject to the terms of this Agreement, TI hereby
grants to you under all TI intellectual property rights embodied in the
Licensed Materials a limited, non-exclusive, non-transferable, non-
assignable, fully paid-up, royalty-free, non-sublicensable license only to
(i) use the Licensed Materials solely for the purposes of evaluating,
testing, debugging and optimizing applications ("Target Applications")
that execute solely and exclusively on processing devices manufactured
by or for TI ("TI Devices"), and (ii) make a reasonable number of copies
necessary to exercise the right granted to you in Section 1(a)(i) above.
Use of any software applications optimized or developed using the
Licensed Materials on processing devices manufactured by or for an
entity other than TI is a material breach of this Agreement.  It is also a
material breach of this license to use the Licensed Materials to assist in
the design, development or verification of a device that is instruction set
compatible with, or functionally equivalent to, a TI processing device.

b.  Contractors and Suppliers.  The licenses granted to you hereunder
shall include your on-site and off-site suppliers and independent
contractors, while such suppliers and independent contractors are
performing work for or providing services to you, provided that such
suppliers and independent contractors have executed work-for-hire
agreements with you containing terms and conditions not inconsistent
with the terms and conditions set forth in this Agreement, and provided
further that you agree you are responsible for the breach of this
Agreement by any of your suppliers or contractors to the same extent
that you would be if you breached the Agreement yourself.

c.  No Distribution License.  NOTWITHSTANDING ANYTHING TO THE
CONTRARY, THIS AGREEMENT DOES NOT CONVEY ANY
LICENSE TO DISTRIBUTE THE LICENSED MATERIALS TO ANY
THIRD PARTY.  YOU ARE REQUIRED TO EXECUTE A SEPARATE
LICENSE AGREEMENT WITH TI BEFORE DISTRIBUTING THE
LICENSED MATERIALS OR ANY PRODUCTS THAT CONTAIN THE
LICENSED MATERIALS, OR ANY DERIVATIVE THEREOF.

    d.  Limited License to TI and Covenant not to Sue.  Continuing for the
term of this Agreement, you hereby grant to TI under any of your
patents embodied in the Licensed Materials a non-transferable, non-
exclusive, non-assignable, worldwide, fully paid-up, royalty-free license
to make, use, sell, offer to sell, import, export and otherwise distribute
such Licensed Materials.  You covenant not to sue or otherwise assert
Derived Patents against TI and TI's affiliates and their licensees of the
Licensed Materials.  In the event you assign a Derived Patent, you shall
require as a condition of any such assignment that the assignee agree
to be bound by the provisions in this Section 1(d) with respect to such
Derived Patent.  Any attempted assignment or transfer in violation of
this Section 1(d) shall be null and void.  For purposes of this Agreement,
"Derived Patents" means any of your patents issuing from a patent
application that discloses and claims an invention conceived of by you
after delivery of the Licensed Materials, and derived by you from your
access to the Licensed Materials.

    e.  No Other License.  Notwithstanding anything to the contrary, nothing
in this Agreement shall be construed as a license to any intellectual
property rights of TI other than those rights embodied in the Licensed
Materials provided to you by TI.  EXCEPT AS PROVIDED HEREIN, NO
OTHER LICENSE, EXPRESS OR IMPLIED, BY ESTOPPEL OR
OTHERWISE, TO ANY OTHER TI INTELLECTUAL PROPERTY
RIGHTS IS GRANTED HEREIN.

    f.  Restrictions.

i.  You shall not disclose or distribute the source code versions of
the Licensed Materials, or any derivative thereof, to any person
other than your employees and contractors whose job
performance requires access.

ii. Use of any software application optimized or developed using
the Licensed Materials on processing devices manufactured by
or for an entity other than TI is a material breach of this
Agreement.  Use of the Licensed Materials to assist in the
design, development or verification of a device not manufactured
by or for TI is a material breach of this Agreement.  Use of the
Licensed Materials to evaluate, test, debug and optimize
applications for use with processing devices other than those
manufactured by or for TI is a material breach of this Agreement.

iii.    Other than as expressly set forth in this Section 1(f)(iii) and in
Section 1(a) above, you may not otherwise copy or reproduce
the Licensed Materials.

iv. You will not sublicense, transfer or assign the Licensed Materials
or your rights under this Agreement to any third party.

v.  You may use the Licensed Materials with Open Source Software
(as defined below) or with software developed using Open
Source Software (e.g. tools) provided you do not incorporate,
combine or distribute the Licensed Materials in a manner that
subjects the Licensed Materials, or any derivatives thereof, to
any license obligations or any other intellectual property related
terms of such Open Source Software.  "Open Source Software"
means any software licensed under terms requiring that (A) other
software ("Proprietary Software") incorporated, combined or
distributed with such software or developed using such software:
(i) be disclosed or distributed in source code form; or (ii)
otherwise be licensed on terms inconsistent with the terms of this
Agreement, including but not limited to permitting use of the
Proprietary Software on or with devices other than TI Devices, or
(B) the owner of Proprietary Software license any of its patents
to users of the Open Source Software and/or Proprietary
Software incorporated, combined or distributed with such Open
Source Software or developed using such Open Source
Software.

    g.  Termination.  This Agreement is effective until terminated.  You may
terminate this Agreement at any time by written notice to TI.  Without
prejudice to any other rights, if you fail to comply with the terms of this
Agreement, TI may terminate your right to use the Licensed Materials,
or any derivative thereof, and any applications generated using the
Licensed Materials, or any derivative thereof, upon written notice to you.
Upon expiration or termination of this Agreement, you will destroy any
and all copies of the Licensed Materials, including any derivatives
thereof, in your possession, custody or control and provide to TI a
written statement signed by your authorized representative certifying
such destruction. Except for Sections 1(a) and 1(b) and the limited
license to TI set forth in Section 1(d), all provisions of this Agreement
shall survive expiration or termination of the Agreement.

2.  Licensed Materials Ownership.  The Licensed Materials are licensed,
not sold to you, and can only be used in accordance with the terms of
this Agreement.  Subject to the licenses granted to you pursuant to this
Agreement, TI and TI's licensors own and shall continue to own all right,
title and interest in and to the Licensed Materials, including all copies
thereof.  The parties agree that all fixes, modifications and
improvements to the Licensed Materials conceived of or made by TI
that are based, either in whole or in part, on your feedback, suggestions
or recommendations are the exclusive property of TI and all right, title
and interest in and to such fixes, modifications or improvements to the
Licensed Materials will vest solely in TI.  You acknowledge and agree
that regardless of the changes made to the Licensed Materials, your
right to use any and all derivatives of the Licensed Materials shall
remain subject to the terms and conditions of this Agreement.
Moreover, you acknowledge and agree that when your independently
developed software or hardware components are combined, in whole or
in part, with the Licensed Materials, or any derivative thereof, your right
to use the Licensed Materials, or any derivative thereof, embodied in
such resulting combined work shall remain subject to the terms and
conditions of this Agreement.

3.  Intellectual Property Rights.

    a.  The Licensed Materials contain copyrighted material, trade secrets
and other proprietary information of TI and its licensors and are
protected by copyright laws, international copyright treaties and trade
secret laws, as well as other intellectual property laws.  To protect TI's
and its licensors' rights in the Licensed Materials, you agree, except as
specifically permitted by statute by a provision that cannot be waived by
contract, not to "unlock", decompile, reverse engineer, disassemble or
otherwise translate any portions of the Licensed Materials provided to
you in object code format only to a human-perceivable form nor to
permit any person or entity to do so.  You shall not remove, erase, alter,
tamper, cover or obscure any confidentiality, trade secret, proprietary or
copyright notices, trade-marks, proprietary, patent or other identifying
marks or designs printed or stamped on, affixed to, or encoded or
recorded in any component of the Licensed Materials and you shall
reproduce and include in all copies of the Licensed Materials the
copyright notice(s) and proprietary legend(s) of TI and its licensors as
they appear in the Licensed Materials.  TI reserves all rights not
specifically granted under this Agreement.

    b.  Certain Licensed Materials may be based on industry recognized
standards or software programs published by industry recognized
standards bodies and certain third parties may claim to own patents,
copyrights and other intellectual property rights that cover
implementation of those standards.  You acknowledge and agree that
this Agreement does not convey a license to any such third party
patents, copyrights and other intellectual property rights and that you
are solely responsible for any patent, copyright or other intellectual
property right claim that relates to your use or distribution of the
Licensed Materials, or your use or distribution of your products that
include or incorporate the Licensed Materials.  Moreover, you
acknowledge that any fees or royalties paid to TI pursuant to this
Agreement, as applicable, do not include any fees or royalties that may
be payable to any third party based on such third party's interests in the
Licensed Materials or any intellectual property rights that cover
implementation of any industry recognized standard, any software
program published by any industry recognized standards bodies or any
other proprietary technology.

4.  Audit Right.  At TI's request, and within thirty (30) days after receiving
written notice, you shall permit an independent auditor selected by TI to
have access, no more than once each calendar year (unless the
immediately preceding audit revealed a breach of this Agreement) and
during your regular business hours, to all of your equipment, records
and documents as may contain information bearing upon the use of the
Licensed Materials.  You shall keep full, complete, clear and accurate
records with respect to product sales and distributions for a period
beginning with the then-current calendar year and going back three (3)
years.

5.  Confidential Information.  You acknowledge and agree that the
Licensed Materials, and any derivative thereof, contain trade secrets
and other confidential information of TI and its licensors.  You agree to
use the Licensed Materials, or any derivative thereof, solely within the
scope of the licenses set forth herein, to maintain the Licensed
Materials, or any derivative thereof, in strict confidence, to use at least
the same procedures and degree of care that you use to prevent
disclosure of your own confidential information of like importance but in
no instance less than reasonable care, and to prevent disclosure of the
Licensed Materials, or any derivative thereof, to any third party, except
as may be necessary and required in connection with your rights and
obligations hereunder.  You agree to obtain executed confidentiality
agreements with your employees and contractors having access to the
Licensed Materials, or any derivative thereof, and to diligently take
steps to enforce such agreements in this respect.  TI agrees that
industry standard employment agreements used in the normal course of
your business shall satisfy the requirements of this section. TI may
disclose your contact information to TI's applicable licensors.

6.  Warranties and Limitations.  THE LICENSED MATERIALS ARE
PROVIDED "AS IS".  TI MAKES NO WARRANTY OR
REPRESENTATION, EITHER EXPRESS, IMPLIED OR STATUTORY,
REGARDING THE LICENSED MATERIALS, INCLUDING BUT NOT
LIMITED TO, ANY IMPLIED WARRANTIES OF MERCHANTABILITY
OR FITNESS FOR A PARTICULAR PURPOSE OR NON-
INFRINGEMENT OF ANY THIRD PARTY PATENTS, COPYRIGHTS,
TRADE SECRETS OR OTHER INTELLECTUAL PROPERTY RIGHTS.
YOU AGREE TO USE YOUR INDEPENDENT JUDGMENT IN
DEVELOPING YOUR PRODUCTS AND DERIVATIVES OF THE
LICENSED MATERIALS.  NOTHING CONTAINED IN THIS
AGREEMENT WILL BE CONSTRUED AS A WARRANTY OR
REPRESENTATION BY TI TO MAINTAIN PRODUCTION OF ANY TI
SEMICONDUCTOR DEVICE OR OTHER HARDWARE OR
SOFTWARE WITH WHICH THE LICENSED MATERIALS MAY BE
USED.

YOU ACKNOWLEDGE AND AGREE THAT THE LICENSED
MATERIALS MAY NOT BE INTENDED FOR PRODUCTION
APPLICATIONS AND MAY CONTAIN IRREGULARITIES AND
DEFECTS NOT FOUND IN PRODUCTION SOFTWARE.
FURTHERMORE, YOU ACKNOWLEDGE AND AGREE THAT THE
LICENSED MATERIALS HAVE NOT BEEN TESTED OR CERTIFIED
BY ANY GOVERNMENT AGENCY OR INDUSTRY REGULATORY
ORGANIZATION OR ANY OTHER THIRD PARTY ORGANIZATION.
YOU AGREE THAT PRIOR TO USING OR DISTRIBUTING ANY
COMMERCIAL PRODUCT OPTIMIZED OR DEVELOPED USING THE
LICENSED MATERIALS YOU WILL THOROUGHLY TEST THE
PRODUCT AND THE FUNCTIONALITY OF THAT PRODUCT AND BE
SOLELY RESPONSIBLE FOR ANY PROBLEMS OR FAILURES.

IN NO EVENT SHALL TI, OR ANY APPLICABLE LICENSOR, BE
LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL, PUNITIVE OR
CONSEQUENTIAL DAMAGES, HOWEVER CAUSED, ON ANY
THEORY OF LIABILITY, IN CONNECTION WITH OR ARISING OUT
OF THIS AGREEMENT OR THE USE OF THE LICENSED
MATERIALS, OR ANY DERIVATIVE THEREOF, REGARDLESS OF
WHETHER TI HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGES.  EXCLUDED DAMAGES INCLUDE, BUT ARE NOT
LIMITED TO, COST OF REMOVAL OR REINSTALLATION, OUTSIDE
COMPUTER TIME, LABOR COSTS, LOSS OF DATA, LOSS OF
GOODWILL, LOSS OF PROFITS, LOSS OF SAVINGS, OR LOSS OF
USE OR INTERRUPTION OF BUSINESS.  IN NO EVENT WILL TI'S
AGGREGATE LIABILITY UNDER THIS AGREEMENT OR ARISING
OUT OF YOUR USE OF THE LICENSED MATERIALS, OR ANY
DERIVATIVE THEREOF, EXCEED THE GREATER OF FIVE
HUNDRED U.S. DOLLARS (US$500) OR THE FEES PAID TO TI BY
YOU FOR THE LICENSED MATERIALS UNDER THIS AGREEMENT.

    Because some jurisdictions do not allow the exclusion or limitation of
incidental or consequential damages or limitation on how long an
implied warranty lasts, the above limitations or exclusions may not apply
to you.

7.  Indemnification Disclaimer.  YOU ACKNOWLEDGE AND AGREE
THAT TI SHALL NOT BE LIABLE FOR AND SHALL NOT DEFEND OR
INDEMNIFY YOU AGAINST ANY THIRD PARTY INFRINGEMENT
CLAIM THAT RELATES TO OR IS BASED ON YOUR
MANUFACTURE, USE OR DISTRIBUTION OF THE LICENSED
MATERIALS, OR ANY DERIVATIVE THEREOF, OR YOUR
MANUFACTURE, USE, OFFER FOR SALE, SALE, IMPORTATION OR
DISTRIBUTION OF YOUR PRODUCTS THAT INCLUDE OR
INCORPORATE THE LICENSED MATERIALS, OR ANY DERIVATIVE
THEREOF.

8.  No Technical Support.  TI and TI's licensors are under no obligation to
install, maintain or support the Licensed Materials, or any derivatives
thereof.

9.  Notices.  All notices to TI hereunder shall be delivered to Texas
Instruments Incorporated, 12500 TI Boulevard, Mail Station 8638,
Dallas, Texas 75243, Attention: Contracts Manager, with a copy to
Texas Instruments Incorporated, 13588 N. Central Expressway, Mail
Station 3999, Dallas, Texas 75243, Attention: Law Department - ASP.
All notices shall be deemed served when received by TI.

10. Export Control.  You hereby acknowledge that the Licensed Materials
are subject to export control under the U.S. Commerce Department's
Export Administration Regulations ("EAR").  You further hereby
acknowledge and agree that unless prior authorization is obtained from the
U.S. Commerce Department, neither you nor your customers will export,
re-export or release, directly or indirectly, any technology, software or
software source code (as defined in Part 772 of the EAR), received from
TI, or export, directly or indirectly, any direct product of such technology,
software or software source code (as defined in Part 734 of the EAR), to
any destination or country to which the export, re-export or release of the
technology, software or software source code, or direct product is
prohibited by the EAR.  You agree that none of the Licensed Materials
may be downloaded or otherwise exported or reexported (i) into (or to a
national or resident of) Cuba, Iran, North Korea, Sudan and Syria or any
other country the U.S. has embargoed goods; or (ii) to anyone on the U.S.
Treasury Department's List of Specially Designated Nationals or the U.S.
Commerce Department's Denied Persons List or Entity List.  You
represent and warrant that you are not located in, under the control of, or a
national or resident of any such country or on any such list and you will not
use or transfer the Licensed Materials for use in any sensitive nuclear,
chemical or biological weapons, or missile technology end-uses unless
authorized by the U.S. Government by regulation or specific license or for
a military end-use in, or by any military entity of Albania, Armenia,
Azerbaijan, Belarus, Cambodia, China, Georgia, Iraq, Kazakhstan,
Kyrgyzstan, Laos, Libya, Macau, Moldova, Mongolia, Russia, Tajikistan,
Turkmenistan, Ukraine, Uzbekistan and Vietnam. Any software export
classification made by TI shall be for TI's internal use only and shall not
be construed as a representation or warranty regarding the proper
export classification for such software or whether an export license or
other documentation is required for the exportation of such software.

11. Governing Law and Severability.  This Agreement will be governed by
and interpreted in accordance with the laws of the State of Texas,
without reference to conflict of laws principles.  If for any reason a court
of competent jurisdiction finds any provision of the Agreement to be
unenforceable, that provision will be enforced to the maximum extent
possible to effectuate the intent of the parties, and the remainder of the
Agreement shall continue in full force and effect.  This Agreement shall
not be governed by the United Nations Convention on Contracts for the
International Sale of Goods, or by the Uniform Computer Information
Transactions Act (UCITA).  The parties agree that non-exclusive
jurisdiction for any dispute arising out of or relating to this Agreement
lies within the courts located in the State of Texas.  Notwithstanding the
foregoing, any judgment may be enforced in any United States or
foreign court, and either party may seek injunctive relief in any United
States or foreign court.

12. PRC Provisions.  If you are located in the People's Republic of China
("PRC") or if the Licensed Materials will be sent to the PRC, the
following provisions shall apply and shall supersede any other
provisions in this Agreement concerning the same subject matter:

    a.  Registration Requirements.  You shall be solely responsible for
performing all acts and obtaining all approvals that may be required in
connection with this Agreement by the government of the PRC,
including but not limited to registering pursuant to, and otherwise
complying with, the PRC Measures on the Administration of Software
Products, Management Regulations on Technology Import-Export, and
Technology Import and Export Contract Registration Management
Rules.  Upon receipt of such approvals from the government authorities,
you shall forward evidence of all such approvals to TI for its records.  In
the event that you fail to obtain any such approval or registration, you
shall be solely responsible for any and all losses, damages or costs
resulting therefrom, and shall indemnify TI for all such losses, damages
or costs.

b.  Governing Language.  This Agreement is written and executed in
the English language.  If a translation of this Agreement is required for
any purpose, including but not limited to registration of the Agreement
pursuant to any governmental laws, regulations or rules, you shall be
solely responsible for creating such translation.  Any translation of this
Agreement into a language other than English is intended solely in order
to comply with such laws or for reference purposes, and the English
language version shall be authoritative and controlling.

c.  Export Control.

i.  Diversions of Technology.  You hereby agree that unless
prior authorization is obtained from the U.S. Department of
Commerce, neither you nor your subsidiaries or affiliates shall
knowingly export, re-export or release, directly or indirectly, any
technology, software or software source code (as defined in Part
772 of the Export Administration Regulations of the U.S.
Department of Commerce ("EAR")), received from TI or any of its
affiliated companies, or export, directly or indirectly, any direct
product of such technology, software or software source code (as
defined in Part 734 of the EAR), to any destination or country to
which the export, re-export or release of the technology, software,
software source code or direct product is prohibited by the EAR.

ii. Assurance of Compliance.  You understand and
acknowledge that products, technology (regardless of the form in
which it is provided), software or software source code, received
from TI or any of its affiliates under this Agreement may be under
export control of the United States or other countries.  You shall
comply with the United States and other applicable non-U.S. laws
and regulations governing the export, re-export and release of any
products, technology, software or software source code received
under this Agreement from TI or its affiliates.  You shall not
undertake any action that is prohibited by the EAR.  Without
limiting the generality of the foregoing, you specifically agree that
you shall not transfer or release products, technology, software or
software source code of TI or its affiliates to, or for use by, military
end users or for use in military, missile, nuclear, biological or
chemical weapons end uses.

iii.    Licenses.  Each party shall secure at its own expense, such
licenses and export and import documents as are necessary for
each respective party to fulfill its obligations under this Agreement.
If such licenses or government approvals cannot be obtained, TI
may terminate this Agreement, or shall otherwise be excused from
the performance of any obligations it may have under this
Agreement for which the licenses or government approvals are
required.

13. Contingencies.  TI shall not be in breach of this Agreement and shall
not be liable for any non-performance or delay in performance if such
non-performance or delay is due to a force majeure event or other
circumstances beyond TI's reasonable control, including but not limited
to, shortages of labor, energy, fuel, machinery or materials, technical or
yield failures, war, civil unrest, any government act, law or regulation,
including any judicial order or decree, any communication or power
failure, labor dispute, natural disaster, fire, flood, earthquake, explosion,
terrorist act or Act of God.

14. Entire Agreement.  This is the entire Agreement between you and TI
and this Agreement supersedes any prior agreement between the
parties related to the subject matter of this Agreement.  No amendment
or modification of this Agreement will be effective unless in writing and
signed by a duly authorized representative of TI.  You hereby warrant
and represent that you have obtained all authorizations and other
applicable consents required empowering you to enter into this
Agreement.





Page 1

*/

