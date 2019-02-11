/*****************************************************************************/
/*  ARP32.H v1.0.7                                                           */
/*                                                                           */
/* Copyright (c) 2010-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#ifndef _ARP32_H
#define _ARP32_H

#ifdef __cplusplus
extern "C"
{
#endif

#define __CONST(lb, ub)  __attribute__((constrange((lb), (ub))))
#define __BUILTIN        __attribute__((builtin))
#define __IMPURE         __attribute__((impure))
#define __BUILTIN_M      __BUILTIN __IMPURE
#define __0_31_RNG_UINT  __CONST(0, 31) unsigned int

/*---------------------------------------------------------------------------*/
/* ARP32 Standard Intrinsics                                                 */
/*---------------------------------------------------------------------------*/
int          __BUILTIN _revr (int val1, int val2);
int          __BUILTIN _rotr (int val1, int val2);
int          __BUILTIN _rotc (int val1, int val2);
int          __BUILTIN _sadd (int val1, int val2);
int          __BUILTIN _ssub (int val1, int val2);
int          __BUILTIN _norm (int val1);
int          __BUILTIN _satn (__CONST(0, 7) unsigned int val1, int val2);
int          __BUILTIN _abs  (int val1);
int          __BUILTIN _min  (int val1, int val2);
int          __BUILTIN _max  (int val1, int val2);
unsigned int __BUILTIN _minu (unsigned int val1, unsigned int val2);
unsigned int __BUILTIN _maxu (unsigned int val1, unsigned int val2);
unsigned int __BUILTIN _lmbd (__CONST(0, 1) unsigned int val1, 
                              unsigned int val2);
long long    __BUILTIN _itoll(unsigned int val1, unsigned int val2);
unsigned int __BUILTIN _hill (long long val1);
unsigned int __BUILTIN _loll (long long val1);

void         __BUILTIN_M _idle (void);
void         __BUILTIN_M _swi  (void);

/*---------------------------------------------------------------------------*/
/* ARP32 Interrupt Control Intrinsics                                        */
/*---------------------------------------------------------------------------*/
unsigned int __BUILTIN_M _get_inum(void);
unsigned int __BUILTIN_M _get_cpunum(void);
unsigned int __BUILTIN_M _enable_interrupts(void);
unsigned int __BUILTIN_M _disable_interrupts(void);
void         __BUILTIN_M _restore_interrupts(unsigned int val1);

/*---------------------------------------------------------------------------*/
/* ARP32 Time Stamp Counter Control Intrinsics                               */
/*---------------------------------------------------------------------------*/
void               __BUILTIN_M _tsc_start(void);
unsigned long long __BUILTIN_M _tsc_gettime(void);

/*---------------------------------------------------------------------------*/
/* ARP32 Standard Register-Based Bit Processing Intrinsics                   */
/*---------------------------------------------------------------------------*/
int          __BUILTIN _clrr (unsigned int val1, int val2);
int          __BUILTIN _setr (unsigned int val1, int val2);
int          __BUILTIN _extr (unsigned int val1, int val2);
unsigned int __BUILTIN _extur(unsigned int val1, int val2);

/*---------------------------------------------------------------------------*/
/* ARP32 Standard Immediate-Based Bit Processing Intrinsics                  */
/*---------------------------------------------------------------------------*/
int          __BUILTIN _ext  (__0_31_RNG_UINT val1, __0_31_RNG_UINT val2, 
                              int val3);
unsigned int __BUILTIN _extu (__0_31_RNG_UINT val1, __0_31_RNG_UINT val2, 
                              unsigned int val3);
unsigned int __BUILTIN _set  (__0_31_RNG_UINT val1, __0_31_RNG_UINT val2, 
                              unsigned int val3);
unsigned int __BUILTIN _clr  (__0_31_RNG_UINT val1, __0_31_RNG_UINT val2, 
                              unsigned int val3);

#ifdef __cplusplus
}
#endif

#endif /* _ARP32_H */
