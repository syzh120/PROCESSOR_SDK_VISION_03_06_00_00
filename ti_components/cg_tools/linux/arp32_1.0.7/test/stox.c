/****************************************************************************/
/*  stox.c  ##                                                              */
/*                                                                          */
/* Copyright (c) 1993-2015 Texas Instruments Incorporated                   */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/*                                                                          */
/*  _Stox() functions for interfacing to C++ library                        */
/****************************************************************************/
#include <stdlib.h>

long _Stolx(const char *s, char **endptr, int base, int *perr)
{
   return strtol(s, endptr, base);
}

unsigned long _Stoulx(const char *s, char **endptr, int base, int *perr)
{
   return strtoul(s, endptr, base); 
}

#if defined(_LLONG_AVAILABLE)
long long _Stollx(const char *s, char **endptr, int base, int *perr)
{
   return strtoll(s, endptr, base); 
}

unsigned long long _Stoullx(const char *s, char **endptr, int base, int *perr)
{
   return strtoull(s, endptr, base); 
}
#endif

double _Stodx(const char *s, char **endptr, long pten, int *perr)
{
    double x = strtod(s, endptr);

    if (pten < 0)
       do x /= 10.0; while (++pten < 0); 
    else if (pten > 0)
       do x *= 10.0; while (--pten > 0); 

    return (x);
}

float _Stofx(const char *s, char **endptr, long pten, int *perr)
{
   return (float)_Stodx(s, endptr, pten, perr);  
}

long double _Stoldx(const char *s, char **endptr, long pten, int *perr)
{
    long double x;
    long double strtold(const char *st, char **endptr); 

    x = strtold(s, endptr);

    if (pten < 0)
       do x /= 10.0; while (++pten < 0); 
    else if (pten > 0)
       do x *= 10.0; while (--pten > 0); 

    return (x);
}
