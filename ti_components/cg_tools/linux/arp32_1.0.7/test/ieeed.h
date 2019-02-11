/****************************************************************************/
/*  ieeed.h          v1.0.7                                                 */
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

#ifndef __ieeed__
#define __ieeed__

#include <limits.h>
#include "access.h"

__EXTERN double _absd(double x);
__EXTERN double _negd(double x);

__EXTERN double _addd(double left, double right);
__EXTERN double _subd(double left, double right);
__EXTERN double _mpyd(double left, double right);
__EXTERN double _divd(double left, double right);

__EXTERN int _cmpd(double left,
                 double right); /* <0 if LT, 0 if EQ, >0 if GT     */
                                /* no correct result if NaN source */

__EXTERN int _eqld(double left, double right);
__EXTERN int _neqd(double left, double right);
__EXTERN int _leqd(double left, double right);
__EXTERN int _geqd(double left, double right);
__EXTERN int _lssd(double left, double right);
__EXTERN int _gtrd(double left, double right);


/* char <-> double */
__EXTERN double        _fltcd(  signed char x);
__EXTERN double        _fltbd(unsigned char x);
__EXTERN   signed char _fixdc(double x);
__EXTERN unsigned char _fixdb(double x);

/* short <-> double */
__EXTERN double         _fltsid(         short x);
__EXTERN double         _fltusd(unsigned short x);
__EXTERN short          _fixdsi(double x);
__EXTERN unsigned short _fixdus(double x);

/* int <-> double */
__EXTERN double   _fltid(int      x);
__EXTERN double   _fltud(unsigned x);
__EXTERN int      _fixdi(double x);
__EXTERN unsigned _fixdu(double x);

/* long <-> double */
__EXTERN double        _fltlid(         long x);
__EXTERN double        _fltuld(unsigned long x);
__EXTERN long          _fixdli(double x);
__EXTERN unsigned long _fixdul(double x);


/* float <-> double */
__EXTERN float  _cvtdf(double x); /* slim from double to float  */
__EXTERN double _cvtfd(float  x); /* grow from float  to double */

#include "unaccess.h"

#endif /* __ieeed__*/
