/*======================================================================= */
/*  TEXAS INSTRUMENTS, INC.                                                */
/*                                                                         */
/*  DSPLIB  DSP Signal Processing Library                                  */
/*                                                                         */
/*  This library contains proprietary intellectual property of Texas       */
/*  Instruments, Inc.  The library and its source code are protected by    */
/*  various copyrights, and portions may also be protected by patents or   */
/*  other legal protections.                                               */
/*                                                                         */
/*  This software is licensed for use with Texas Instruments TMS320        */
/*  family DSPs.  This license was provided to you prior to installing     */
/*  the software.  You may review this license by consulting the file      */
/*  TI_license.PDF which accompanies the files in this library.            */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/* DSP_fir_cplx_hM4X4.c -- Complex FIR Filter                              */
/*                   Optimized C Implementation (w/ Intrinsics)            */
/*                                                                         */
/*  Usage                                                                  */
/*     This routine is C-callable and can be called as:                    */
/*                                                                         */
/*     void DSP_fir_cplx_hM4X4 (                                           */
/*         const short *restrict x,                                        */
/*         const short *restrict h,                                        */
/*         short *restrict r,                                              */
/*         int nh,                                                         */
/*         int nr,                                                         */
/*     )                                                                   */
/*                                                                         */
/*     x[2*(nr+nh-1)] : Complex input data. x must point to x[2*(nh-1)].   */
/*     h[2*nh]        : Complex coefficients (in normal order).            */
/*     r[2*nr]        : Complex output data.                               */
/*     nh             : Number of complex coefficients.                    */
/*     nr             : Number of complex output samples.                  */
/*                                                                         */
/*  Description                                                            */
/*      This complex FIR computes nr complex output samples using nh       */
/*      complex coefficients. It operates on 16-bit data with a 32-bit     */
/*      accumulate. Each array consists of an even and odd term with even  */
/*      terms representing the real part of the element and the odd terms  */
/*      the imaginary part. The pointer to input array x must point to the */
/*      (nh)th complex sample, i.e. element 2*(nh-1), upon entry to the    */
/*      function. The coefficients are expected in normal order.           */
/*                                                                         */
/*  Assumptions                                                            */
/*     Arrays x, h, and r do not overlap                                   */
/*     nr >= 8; nr % 4 == 0                                                */
/*     nh >= 4; nh % 4 == 0                                                */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#pragma CODE_SECTION(DSP_fir_cplx_hM4X4, ".text:optimized");

#include "DSP_fir_cplx_hM4X4.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSP_fir_cplx_hM4X4 (
    const short *restrict x,    /* Input array [nr+nh-1 elements] */
    const short *restrict h,    /* Coeff array [nh elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nh,                     /* Number of coefficients         */
    int nr                      /* Number of output samples       */
)
{
    int i, j, imag_real_0, imag_real_1, imag_real_2, imag_real_3;    
    long long h_3210, x_3210,x_7654,x_ba98;
    long long real0imag0, real1imag1, real2imag2, real3imag3;  
    __x128_t  x_54_32_76_54, x_98_76_ba_98, re1im1re0im0, re3im3re2im2;

    /*--------------------------------------------------------------------*/
    /* _nasserts are used to inform the compiler that the input, filter,  */
    /* output arrays are word or double word aligned. In addition the  #  */
    /* filter taps and output samples is stated to be even.               */
    /*--------------------------------------------------------------------*/
    _nassert((int)nr >= 8);
    _nassert((int)nr % 4 == 0);
    _nassert((int)nh >= 4);
    _nassert((int)nh % 4 == 0);

    /*--------------------------------------------------------------------*/
    /* Inform the compiler that the following loop will iterate at least  */
    /* twice and that the # output samples is a multiple of 4.            */
    /*--------------------------------------------------------------------*/
    #pragma MUST_ITERATE(2,,1)
    for (i = 0; i < 2*nr; i += 8) {
        /*----------------------------------------------------------------*/
        /* Zero out accumulators for 4 complex output samples             */
        /*----------------------------------------------------------------*/
        real0imag0 = real1imag1=0;
        real2imag2 = real3imag3=0;
        
        x_ba98 = _mem8((void *)&x[i+4]);
        x_7654 = _mem8((void *)&x[i]);    

        /*----------------------------------------------------------------*/
        /* Inform compiler that filter taps is at least 4, and a multiple */
        /* of 4.                                                          */
        /*----------------------------------------------------------------*/
        _nassert((int)nr >= 8);
        _nassert((int)nr % 4 == 0);
        _nassert((int)nh >= 4);
        _nassert((int)nh % 4 == 0);

        #pragma MUST_ITERATE(2,,2)
        #pragma UNROLL(2)
        for (j = 0; j < 2*nh; j += 4) {
            /*------------------------------------------------------------*/
            /* Perform double word loads using intrinsic                  */   
            /*------------------------------------------------------------*/
            h_3210 = _amem8((void *)&h[j]);

            /*------------------------------------------------------------*/
            /* Load input data using Double word loads.                   */
            /*------------------------------------------------------------*/
            x_3210 = _mem8((void *)&x[i - j - 4]);
              
            /*------------------------------------------------------------*/
            /* Create 2*2 complex matrix for _cmatmpy intrinsic           */
            /* Perform complex matrix multiply using _cmatmpy             */
            /*------------------------------------------------------------*/
            x_54_32_76_54 = _llto128(_dmv(_loll(x_7654),_hill(x_3210)),x_7654); 
            re1im1re0im0  = _cmatmpy(h_3210,x_54_32_76_54);

            /*------------------------------------------------------------*/
            /* Create 2*2 complex matrix for _cmatmpy intrinsic           */
            /* Perform complex matrix multiply using _cmatmpy             */
            /*------------------------------------------------------------*/            
            x_98_76_ba_98 = _llto128(_dmv(_loll(x_ba98),_hill(x_7654)),x_ba98);
            re3im3re2im2  = _cmatmpy(h_3210,x_98_76_ba_98);
            
            /*------------------------------------------------------------*/
            /* Accumalate 4 complex output using _dadd()                  */
            /*------------------------------------------------------------*/
            real0imag0 = _dadd(real0imag0,_lo128(re1im1re0im0));
            real1imag1 = _dadd(real1imag1,_hi128(re1im1re0im0));
            real2imag2 = _dadd(real2imag2,_lo128(re3im3re2im2));
            real3imag3 = _dadd(real3imag3,_hi128(re3im3re2im2));            
             
            /*------------------------------------------------------------*/
            /* Save inputs for the next iteration                         */
            /*------------------------------------------------------------*/                            
            x_ba98 = x_7654;        
            x_7654 = x_3210;
        }

        /*----------------------------------------------------------------*/
        /*  Shift out accumulated sum, pack and store as double words     */
        /*----------------------------------------------------------------*/
        real0imag0 = _dshl(real0imag0,1);
        real1imag1 = _dshl(real1imag1,1);
        real2imag2 = _dshl(real2imag2,1);
        real3imag3 = _dshl(real3imag3,1);  
            
        imag_real_0 = _packh2(_hill(real0imag0), _loll(real0imag0));
        imag_real_1 = _packh2(_hill(real1imag1), _loll(real1imag1));
        imag_real_2 = _packh2(_hill(real2imag2), _loll(real2imag2));
        imag_real_3 = _packh2(_hill(real3imag3), _loll(real3imag3));
                
        _amem8(&r[i])   = _dcrot270(_itoll(imag_real_1, imag_real_0));
        _amem8(&r[i+4]) = _dcrot270(_itoll(imag_real_3, imag_real_2));        
    }
}

/*-----------------------------------------------------------*/
/*  Big Endian version                                       */
/*-----------------------------------------------------------*/
#else
void DSP_fir_cplx_hM4X4 (
    const short *restrict x,    /* Input array [nr+nh-1 elements] */
    const short *restrict h,    /* Coeff array [nh elements]      */
    short       *restrict r,    /* Output array [nr elements]     */
    int nh,                     /* Number of coefficients         */
    int nr                      /* Number of output samples       */
)
{
    int i, j, real_imag_0, real_imag_1, real_imag_2, real_imag_3;    
    long long h_0123, x_0123 ,x_4567 ,x_89ab;
    long long imag0real0, imag1real1, imag2real2, imag3real3;  
    __x128_t  x_45_67_23_45, x_89_ab_67_89, im0re0im1re1, im2re2im3re3;  

    /*--------------------------------------------------------------------*/
    /* _nasserts are used to inform the compiler that the input, filter,  */
    /* output arrays are word or double word aligned. In addition the  #  */
    /* filter taps and output samples is stated to be even.               */
    /*--------------------------------------------------------------------*/
    _nassert((int)nr >= 8);
    _nassert((int)nr % 4 == 0);
    _nassert((int)nh >= 4);
    _nassert((int)nh % 4 == 0);

    /*--------------------------------------------------------------------*/
    /* Inform the compiler that the following loop will iterate at least  */
    /* twice and that the # output samples is a multiple of 4.            */
    /*--------------------------------------------------------------------*/
    #pragma MUST_ITERATE(2,,1)
    for (i = 0; i < 2*nr; i += 8) {
        /*----------------------------------------------------------------*/
        /* Zero out accumulators for 4 complex output samples             */
        /*----------------------------------------------------------------*/
        imag0real0 = imag1real1=0;
        imag2real2 = imag3real3=0;
        
        x_89ab = _mem8((void *)&x[i+4]);
        x_4567 = _mem8((void *)&x[i]);    

        /*----------------------------------------------------------------*/
        /* Inform compiler that filter taps is at least 4, and a multiple */
        /* of 4.                                                          */
        /*----------------------------------------------------------------*/
        _nassert((int)nr >= 8);
        _nassert((int)nr % 4 == 0);
        _nassert((int)nh >= 4);
        _nassert((int)nh % 4 == 0);

        #pragma MUST_ITERATE(2,,2)
        #pragma UNROLL(2)
        for (j = 0; j < 2*nh; j += 4) {
            /*------------------------------------------------------------*/
            /* Perform double word loads using intrinsic                  */   
            /*------------------------------------------------------------*/
            h_0123 = _amem8((void *)&h[j]);
            /*------------------------------------------------------------*/
            /* Load input data using Double word loads.                   */
            /*------------------------------------------------------------*/
            x_0123 = _mem8((void *)&x[i - j - 4]);
              
            /*------------------------------------------------------------*/
            /* Create 2*2 complex matrix for _cmatmpy intrinsic           */
            /* Perform complex matrix multiply using _cmatmpy             */
            /*------------------------------------------------------------*/
            x_45_67_23_45 = _llto128(x_4567,_dmv(_loll(x_0123),_hill(x_4567))); 
            im0re0im1re1  = _cmatmpy(h_0123,x_45_67_23_45);

            /*------------------------------------------------------------*/
            /* Create 2*2 complex matrix for _cmatmpy intrinsic           */
            /* Perform complex matrix multiply using _cmatmpy             */
            /*------------------------------------------------------------*/            
            x_89_ab_67_89 = _llto128(x_89ab,_dmv(_loll(x_4567),_hill(x_89ab)));
            im2re2im3re3  = _cmatmpy(h_0123,x_89_ab_67_89);
            
            /*------------------------------------------------------------*/
            /* Accumalate 4 complex output using _dadd()                  */
            /*------------------------------------------------------------*/
            imag0real0 = _dadd(imag0real0,_hi128(im0re0im1re1));
            imag1real1 = _dadd(imag1real1,_lo128(im0re0im1re1));
            imag2real2 = _dadd(imag2real2,_hi128(im2re2im3re3));
            imag3real3 = _dadd(imag3real3,_lo128(im2re2im3re3));            
             
            /*------------------------------------------------------------*/
            /* Save inputs for the next iteration                         */
            /*------------------------------------------------------------*/                            
            x_89ab = x_4567;        
            x_4567 = x_0123;
        }

        /*----------------------------------------------------------------*/
        /*  Shift out accumulated sum, pack and store as double words     */
        /*----------------------------------------------------------------*/
        imag0real0 = _dshl(imag0real0,1);
        imag1real1 = _dshl(imag1real1,1);
        imag2real2 = _dshl(imag2real2,1);
        imag3real3 = _dshl(imag3real3,1);  
              
        real_imag_0 = _packh2(_hill(imag0real0), _loll(imag0real0));
        real_imag_1 = _packh2(_hill(imag1real1), _loll(imag1real1));
        real_imag_2 = _packh2(_hill(imag2real2), _loll(imag2real2));
        real_imag_3 = _packh2(_hill(imag3real3), _loll(imag3real3));
                                                                     
        _amem8(&r[i])   = _itoll(real_imag_0, real_imag_1);
        _amem8(&r[i+4]) = _itoll(real_imag_2, real_imag_3);
    }
}
#endif

/* ======================================================================= */
/*  End of file:  DSP_fir_cplx_hM4X4.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

