/****************************************************************************/
/*  ieeef.h          v1.0.7                                                 */
/*                                                                          */
/* Copyright (c) 1997-2015 Texas Instruments Incorporated                   */
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
/****************************************************************************/

#ifndef __ieeef__
#define __ieeef__

#include <limits.h>
#include "access.h"

__EXTERN float _absf(float x);
__EXTERN float _negf(float x);

__EXTERN float _addf(float left, float right);
__EXTERN float _subf(float left, float right);
__EXTERN float _mpyf(float left, float right);
__EXTERN float _divf(float left, float right);

__EXTERN int _cmpf(float left,
                 float right); /* <0 if LT, 0 if EQ, >0 if GT     */
                               /* no correct result if NaN source */

__EXTERN int _eqlf(float left, float right);
__EXTERN int _neqf(float left, float right);
__EXTERN int _leqf(float left, float right);
__EXTERN int _geqf(float left, float right);
__EXTERN int _lssf(float left, float right);
__EXTERN int _gtrf(float left, float right);


/* char <-> float */
__EXTERN float         _fltcf(  signed char x);
__EXTERN float         _fltbf(unsigned char x);
__EXTERN   signed char _fixfc(float x);
__EXTERN unsigned char _fixfb(float x);

/* short <-> float */
__EXTERN float          _fltsif(         short x);
__EXTERN float          _fltusf(unsigned short x);
__EXTERN short          _fixfsi(float x);
__EXTERN unsigned short _fixfus(float x);

/* int <-> float */
__EXTERN float    _fltif(int      x);
__EXTERN float    _fltuf(unsigned x);
__EXTERN int      _fixfi(float x);
__EXTERN unsigned _fixfu(float x);

/* long <-> float */
__EXTERN float         _fltlif(         long x);
__EXTERN float         _fltulf(unsigned long x);
__EXTERN long          _fixfli(float x);
__EXTERN unsigned long _fixful(float x);

#include "unaccess.h"

#endif /* __ieeef__*/
