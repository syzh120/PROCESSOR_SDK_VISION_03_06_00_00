/*
*
* Copyright (c) 2001-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#define MPY16X32R(x,y) \
    (((int)((short)(x) * (unsigned short)(y) + 0x4000) >> 15) + \
     ((int)((short)(x) * (short)((y) >> 16)) << 1))

#pragma CODE_SECTION(fft16x16t_cn,   ".text:ansi");
static const char Copyright[] = "Copyright (C) 2000 Texas Instruments "
                                 "Incorporated.  All Rights Reserved.";

#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------------------*/
/* The following macro is used to obtain a digit reversed index, of a given */
/* number i, into j where the number of bits in "i" is "m". For the natural */
/* form of C code, this is done by first interchanging every set of "2 bit" */
/* pairs, followed by exchanging nibbles, followed by exchanging bytes, and */
/* finally halfwords. To give an example, condider the following number:    */
/*                                                                          */
/* N = FEDCBA9876543210, where each digit represents a bit, the following   */
/* steps illustrate the changes as the exchanges are performed:             */
/* M = DCFE98BA54761032 is the number after every "2 bits" are exchanged.   */
/* O = 98BADCFE10325476 is the number after every nibble is exchanged.      */
/* P = 1032547698BADCFE is the number after every byte is exchanged.        */
/* Since only 16 digits were considered this represents the digit reversed  */
/* index. Since the numbers are represented as 32 bits, there is one more   */
/* step typically of exchanging the half words as well.                     */
/*--------------------------------------------------------------------------*/


#if 0
# define DIG_REV(i, m, j) ((j) = (_shfl(_rotl(_bitr(_deal(i)), 16)) >> (m)))
#else
# define DIG_REV(i, m, j)                                                   \
    do {                                                                    \
        unsigned _ = (i);                                                   \
        _ = ((_ & 0x33333333) <<  2) | ((_ & ~0x33333333) >>  2);           \
        _ = ((_ & 0x0F0F0F0F) <<  4) | ((_ & ~0x0F0F0F0F) >>  4);           \
        _ = ((_ & 0x00FF00FF) <<  8) | ((_ & ~0x00FF00FF) >>  8);           \
        _ = ((_ & 0x0000FFFF) << 16) | ((_ & ~0x0000FFFF) >> 16);           \
        (j) = _ >> (m);                                                     \
    } while (0)
#endif

#define restrict 

/*==========================================================================*/
/* fft16x16t_cn  - bevavioural code/ natural c                              */
/*==========================================================================*/

void fft32x16t_cn(const short *restrict ptr_w, int  npoints, int *ptr_x, 
                  int *ptr_y) 
{
    int   i, j, l1, l2, h2, predj, tw_offset, stride, fft_jmp;
    int xt0_0, yt0_0, xt1_0, yt1_0, xt2_0, yt2_0;
    int xt0_1, yt0_1, xt1_1, yt1_1, xt2_1, yt2_1;
    int xh0_0, xh1_0, xh20_0, xh21_0, xl0_0, xl1_0, xl20_0, xl21_0;
    int xh0_1, xh1_1, xh20_1, xh21_1, xl0_1, xl1_1, xl20_1, xl21_1;
    int x_0, x_1, x_2, x_3, x_l1_0, x_l1_1, x_l1_2, x_l1_3, x_l2_0, x_l2_1;
    int xh0_2, xh1_2, xl0_2, xl1_2, xh0_3, xh1_3, xl0_3, xl1_3;
    int x_4, x_5, x_6, x_7, x_l2_2, x_l2_3, x_h2_0, x_h2_1, x_h2_2, x_h2_3;
    int x_8, x_9, x_a, x_b, x_c, x_d, x_e, x_f;
    short si10, si20, si30, co10, co20, co30;
    short si11, si21, si31, co11, co21, co31;
    int   *x, *x2, *x0;
    int   *y0, *y1, *y2, *y3;
    int   n00, n10, n20, n30, n01, n11, n21, n31;
    int   n02, n12, n22, n32, n03, n13, n23, n33;
    int   y0r, y0i, y4r, y4i;
    int   n0, j0;
    int   radix,  m;
    int   norm;

    const short *w;


    /*---------------------------------------------------------------------*/
    /* Determine the magnitude od the number of points to be transformed.  */
    /* Check whether we can use a radix4 decomposition or a mixed radix    */
    /* transformation, by determining modulo 2.                            */
    /*---------------------------------------------------------------------*/

    for (i = 31, m = 1; (npoints & (1 << i)) == 0; i--, m++) ;
    radix     =   m & 1 ? 2 :  4;
    norm      =   m - 2;

    /*----------------------------------------------------------------------*/
    /* The stride is quartered with every iteration of the outer loop. It   */
    /* denotes the seperation between any two adjacent inputs to the butter */
    /* -fly. This should start out at N/4, hence stride is initially set to */
    /* N. For every stride, 6*stride twiddle factors are accessed. The      */
    /* "tw_offset" is the offset within the current twiddle factor sub-     */
    /* table. This is set to zero, at the start of the code and is used to  */
    /* obtain the appropriate sub-table twiddle pointer by offseting it     */
    /* with the base pointer "ptr_w".                                       */
    /*----------------------------------------------------------------------*/

    stride     =   npoints; 
    tw_offset  =   0;
    fft_jmp    =   6 * stride;


    while (stride > radix)
    {
        /*-----------------------------------------------------------------*/
        /* At the start of every iteration of the outer loop, "j" is set   */
        /* to zero, as "w" is pointing to the correct location within the  */
        /* twiddle factor array. For every iteration of the inner loop     */
        /* 6 * stride twiddle factors are accessed. For eg,                */
        /*                                                                 */
        /* #Iteration of outer loop  # twiddle factors    #times cycled    */
        /*  1                          6 N/4               1               */
        /*  2                          6 N/16              4               */
        /*  ...                                                            */
        /*-----------------------------------------------------------------*/

        j         = 0;
        fft_jmp >>= 2;

        /*-----------------------------------------------------------------*/
        /* Set up offsets to access "N/4", "N/2", "3N/4" complex point or  */
        /* "N/2", "N", "3N/2" half word                                    */
        /*-----------------------------------------------------------------*/

        h2 = stride>>1;
        l1 = stride;
        l2 = stride + (stride >> 1);

        /*-----------------------------------------------------------------*/
        /*  Reset "x" to point to the start of the input data array.       */
        /* "tw_offset" starts off at 0, and increments by "6 * stride"     */
        /*  The stride quarters with every iteration of the outer loop     */
        /*-----------------------------------------------------------------*/

        x = ptr_x;
        w = ptr_w + tw_offset;
        tw_offset += fft_jmp;
        stride >>=   2;

        /*----------------------------------------------------------------*/
        /* The following loop iterates through the different butterflies, */
        /* within a given stage. Recall that there are logN to base 4     */
        /* stages. Certain butterflies share the twiddle factors. These   */
        /* are grouped together. On the very first stage there are no     */
        /* butterflies that share the twiddle factor, all N/4 butter-     */
        /* flies have different factors. On the next stage two sets of    */
        /* N/8 butterflies share the same twiddle factor. Hence after     */
        /* half the butterflies are performed, j the index into the       */
        /* factor array resets to 0, and the twiddle factors are reused.  */
        /* When this happens, the data pointer 'x' is incremented by the  */
        /* fft_jmp amount. In addition the following code is unrolled to  */
        /* perform "2" radix4 butterflies in parallel.                    */
        /*----------------------------------------------------------------*/


        for (i = 0; i < npoints; i += 8)
        {
            /*------------------------------------------------------------*/
            /* Read the first 12 twiddle factors, six of which are used   */
            /* for one radix 4 butterfly and six of which are used for    */
            /* next one.                                                  */
            /*------------------------------------------------------------*/

            co10 = w[j+1];    si10 = w[j+0];
            co11 = w[j+3];    si11 = w[j+2];
            co20 = w[j+5];    si20 = w[j+4];
            co21 = w[j+7];    si21 = w[j+6];
            co30 = w[j+9];    si30 = w[j+8];
            co31 = w[j+11];   si31 = w[j+10];

            /*------------------------------------------------------------*/
            /* Read in the first complex input for the butterflies.       */
            /* 1st complex input to 1st butterfly: x[0] + jx[1]           */
            /* 1st complex input to 2nd butterfly: x[2] + jx[3]           */
            /*------------------------------------------------------------*/

            x_0 = x[0];       x_1 = x[1];
            x_2 = x[2];       x_3 = x[3];

            /*------------------------------------------------------------*/
            /* Read in the complex inputs for the butterflies. Each of the*/
            /* successive complex inputs of the butterfly are seperated   */
            /* by a fixed amount known as stride. The stride starts out   */
            /* at N/4, and quarters with every stage.                     */
            /*------------------------------------------------------------*/

            x_l1_0 = x[l1  ]; x_l1_1 = x[l1+1];
            x_l1_2 = x[l1+2]; x_l1_3 = x[l1+3];

            x_l2_0 = x[l2  ]; x_l2_1 = x[l2+1];
            x_l2_2 = x[l2+2]; x_l2_3 = x[l2+3];

            x_h2_0 = x[h2  ]; x_h2_1 = x[h2+1];
            x_h2_2 = x[h2+2]; x_h2_3 = x[h2+3];

            /*-----------------------------------------------------------*/
            /* Two butterflies are evaluated in parallel. The following  */
            /* results will be shown for one butterfly only, although    */
            /* both are being evaluated in parallel.                     */
            /*                                                           */
            /* Perform radix2 style DIF butterflies.                     */
            /*-----------------------------------------------------------*/

            xh0_0  = x_0    + x_l1_0;     xh1_0  = x_1    + x_l1_1;
            xh0_1  = x_2    + x_l1_2;     xh1_1  = x_3    + x_l1_3;
            xl0_0  = x_0    - x_l1_0;     xl1_0  = x_1    - x_l1_1;
            xl0_1  = x_2    - x_l1_2;     xl1_1  = x_3    - x_l1_3;

            xh20_0 = x_h2_0 + x_l2_0;     xh21_0 = x_h2_1 + x_l2_1;
            xh20_1 = x_h2_2 + x_l2_2;     xh21_1 = x_h2_3 + x_l2_3;
            xl20_0 = x_h2_0 - x_l2_0;     xl21_0 = x_h2_1 - x_l2_1;
            xl20_1 = x_h2_2 - x_l2_2;     xl21_1 = x_h2_3 - x_l2_3;

            /*-----------------------------------------------------------*/
            /* Derive output pointers using the input pointer "x"        */
            /*-----------------------------------------------------------*/

            x0 = x;
            x2 = x0;

            /*-----------------------------------------------------------*/
            /* When the twiddle factors are not to be re-used, j is      */
            /* incremented by 12, to reflect the fact that 12 half words */
            /* are consumed in every iteration. The input data pointer   */
            /* increments by 4. Note that within a stage, the stride     */
            /* does not change and hence the offsets for the other three */
            /* legs, 0, h2, l1, l2.                                      */
            /*-----------------------------------------------------------*/

            j += 12;
            x += 4;

            predj = (j - fft_jmp);
            if (!predj) x += fft_jmp;
            if (!predj) j = 0;

            /*----------------------------------------------------------*/
            /* These four partial results can be re-written to show     */
            /* the underlying DIF structure similar to radix2 as        */
            /* follows:                                                 */
            /*                                                          */
            /* X(4k)  = (x(n)+x(n + N/2)) + (x(n+N/4)+ x(n + 3N/4))     */
            /* X(4k+1)= (x(n)-x(n + N/2)) -j(x(n+N/4) - x(n + 3N/4))    */
            /* x(4k+2)= (x(n)+x(n + N/2)) - (x(n+N/4)+ x(n + 3N/4))     */
            /* X(4k+3)= (x(n)-x(n + N/2)) +j(x(n+N/4) - x(n + 3N/4))    */
            /*                                                          */
            /* which leads to the real and imaginary values as foll:    */
            /*                                                          */
            /* y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20           */
            /* y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21           */
            /* y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21           */
            /* y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20           */
            /* y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20           */
            /* y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21           */
            /* y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21           */
            /* y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20           */
            /* ---------------------------------------------------------*/


            y0r   = xh0_0 + xh20_0; y0i   = xh1_0 + xh21_0;
            y4r   = xh0_1 + xh20_1; y4i   = xh1_1 + xh21_1;

            xt0_0 = xh0_0 - xh20_0;  yt0_0 = xh1_0 - xh21_0;
            xt0_1 = xh0_1 - xh20_1;  yt0_1 = xh1_1 - xh21_1;

            xt1_0 = xl0_0 + xl21_0;  yt2_0 = xl1_0 + xl20_0;
            xt2_0 = xl0_0 - xl21_0;  yt1_0 = xl1_0 - xl20_0;
            xt1_1 = xl0_1 + xl21_1;  yt2_1 = xl1_1 + xl20_1;
            xt2_1 = xl0_1 - xl21_1;  yt1_1 = xl1_1 - xl20_1;

            /*---------------------------------------------------------*/
            /* Store out first output, of the four outputs of a radix4 */
            /* butterfly. Since two such radix4 butterflies are per-   */
            /* formed in parallel, there are 2 such 1st outputs.       */
            /*---------------------------------------------------------*/

            x2[0] = y0r;             x2[1] = y0i;
            x2[2] = y4r;             x2[3] = y4i;

            /*---------------------------------------------------------*/
            /* Perform twiddle factor multiplies of three terms,top    */
            /* term does not have any multiplies. Note the twiddle     */
            /* factors for a normal FFT are C + j (-S). Since the      */
            /* factors that are stored are C + j S, this is            */
            /* corrected for in the multiplies.                        */
            /*                                                         */
            /* Y1 = (xt1 + jyt1) (c + js) = (xc + ys) + (yc -xs)       */
            /* Perform the multiplies using 16 by 32 multiply macro    */
            /* defined. This treats the twiddle factor as 16 bits      */
            /* and incoming data as 32 bits.                           */
            /*---------------------------------------------------------*/

            x2[h2  ] = MPY16X32R(si10 , yt1_0) + MPY16X32R(co10 , xt1_0);
            x2[h2+1] = MPY16X32R(co10 , yt1_0) - MPY16X32R(si10 , xt1_0);

            x2[h2+2] = MPY16X32R(si11 , yt1_1) + MPY16X32R(co11 , xt1_1);
            x2[h2+3] = MPY16X32R(co11 , yt1_1) - MPY16X32R(si11 , xt1_1);

            x2[l1  ] = MPY16X32R(si20 , yt0_0) + MPY16X32R(co20 , xt0_0);
            x2[l1+1] = MPY16X32R(co20 , yt0_0) - MPY16X32R(si20 , xt0_0);

            x2[l1+2] = MPY16X32R(si21 , yt0_1) + MPY16X32R(co21 , xt0_1);
            x2[l1+3] = MPY16X32R(co21 , yt0_1) - MPY16X32R(si21 , xt0_1);

            x2[l2  ] = MPY16X32R(si30 , yt2_0) + MPY16X32R(co30 , xt2_0);
            x2[l2+1] = MPY16X32R(co30 , yt2_0) - MPY16X32R(si30 , xt2_0);

            x2[l2+2] = MPY16X32R(si31 , yt2_1) + MPY16X32R(co31 , xt2_1);
            x2[l2+3] = MPY16X32R(co31 , yt2_1) - MPY16X32R(si31 , xt2_1);
        }

		 stage++;
    }

    /*-----------------------------------------------------------------*/
    /* The following code performs either a standard radix4 pass or a  */
    /* radix2 pass. Two pointers are used to access the input data.    */
    /* The input data is read "N/4" complex samples apart or "N/2"     */
    /* words apart using pointers "x0" and "x2". This produces out-    */
    /* puts that are 0, N/4, N/2, 3N/4 for a radix4 FFT, and 0, N/8    */
    /* N/2, 3N/8 for radix 2.                                          */
    /*-----------------------------------------------------------------*/

    y0 = ptr_y;
    y2 = ptr_y + (int) npoints;
    x0 = ptr_x;
    x2 = ptr_x + (int) (npoints >> 1);

    if (radix == 2)
    {
      /*----------------------------------------------------------------*/
      /* The pointers are set at the following locations which are half */
      /* the offsets of a radix4 FFT.                                   */
      /*----------------------------------------------------------------*/

      y1 = y0 + (int) (npoints >> 2);
      y3 = y2 + (int) (npoints >> 2);
      l1 = norm + 1;
      j0 = 8;
      n0 = npoints>>1;
    } 
    else 
    {
      y1 = y0 + (int) (npoints >> 1);
      y3 = y2 + (int) (npoints >> 1);
      l1 = norm + 2;
      j0 = 4;
      n0 = npoints >> 2;
    }

    /*--------------------------------------------------------------------*/
    /* The following code reads data indentically for either a radix 4    */
    /* or a radix 2 style decomposition. It writes out at different       */
    /* locations though. It checks if either half the points, or a        */
    /* quarter of the complex points have been exhausted to jump to       */
    /* pervent double reversal.                                           */
    /*--------------------------------------------------------------------*/

    j = 0;

    fprintf (fp, "    .short ");
    for ( i = 0; i < npoints; i+= 4)
    {
        DIG_REV(j, l1, h2);
        fprintf (fp, "%4d, ", (4 * h2));
        j += 4;
        if ((j > 4) && (j%32) == 0) fprintf (fp, "    ; /* %4d to %4d */ \n", (j - 32), (j - 4));
        if ((j > 4) && (j%32) == 0) fprintf (fp, "    .short ");
    }

    fclose (fp);


    j = 0;



    for (i = 0; i < npoints; i += 8)
    {

        /*----------------------------------------------------------------*/
        /* Digit reverse the index starting from 0. The increment to "j"  */
        /* is either by 4, or 8.                                          */
        /*----------------------------------------------------------------*/

        DIG_REV(j, l1, h2);


        /*----------------------------------------------------------------*/
        /* Read in the input data, from the first eight locations. These  */
        /* are transformed either as a radix4 or as a radix 2.            */
        /*----------------------------------------------------------------*/   

        x_0 = x0[0];             x_1 = x0[1];
        x_2 = x0[2];             x_3 = x0[3];
        x_4 = x0[4];             x_5 = x0[5];
        x_6 = x0[6];             x_7 = x0[7];
        x0 += 8;

        xh0_0 = x_0 + x_4;       xh1_0 = x_1 + x_5;
        xl0_0 = x_0 - x_4;       xl1_0 = x_1 - x_5;
        xh0_1 = x_2 + x_6;       xh1_1 = x_3 + x_7;
        xl0_1 = x_2 - x_6;       xl1_1 = x_3 - x_7;

        n00 = xh0_0 + xh0_1; n01 = xh1_0 + xh1_1;
        n10 = xl0_0 + xl1_1; n11 = xl1_0 - xl0_1;
        n20 = xh0_0 - xh0_1; n21 = xh1_0 - xh1_1;
        n30 = xl0_0 - xl1_1; n31 = xl1_0 + xl0_1; 

        if (radix == 2)
        {
             /*-------------------------------------------------------------*/
             /* Perform radix2 style decomposition.                         */
             /*-------------------------------------------------------------*/   
             n00 = x_0 + x_2;     n01 = x_1 + x_3;
             n20 = x_0 - x_2;     n21 = x_1 - x_3;
             n10 = x_4 + x_6;     n11 = x_5 + x_7;
             n30 = x_4 - x_6;     n31 = x_5 - x_7;
        }

        y0[2*h2] = n00;           y0[2*h2 + 1] = n01;
        y1[2*h2] = n10;           y1[2*h2 + 1] = n11;
        y2[2*h2] = n20;           y2[2*h2 + 1] = n21;
        y3[2*h2] = n30;           y3[2*h2 + 1] = n31;

       
        

        /*----------------------------------------------------------------*/
        /* Read in ht enext eight inputs, and perform radix4 or radix2    */
        /* decomposition.                                                 */
        /*----------------------------------------------------------------*/

        x_8 = x2[0];              x_9 = x2[1];
        x_a = x2[2];              x_b = x2[3];
        x_c = x2[4];              x_d = x2[5];
        x_e = x2[6];              x_f = x2[7];
        x2 += 8;

        xh0_2 = x_8 + x_c;        xh1_2  = x_9 + x_d;
        xl0_2 = x_8 - x_c;        xl1_2  = x_9 - x_d;
        xh0_3 = x_a + x_e;        xh1_3 = x_b + x_f;
        xl0_3 = x_a - x_e;        xl1_3 = x_b - x_f;

        n02 = xh0_2 + xh0_3;      n03 = xh1_2 + xh1_3;
        n12 = xl0_2 + xl1_3;      n13 = xl1_2 - xl0_3;
        n22 = xh0_2 - xh0_3;      n23 = xh1_2 - xh1_3;
        n32 = xl0_2 - xl1_3;      n33 = xl1_2 + xl0_3; 

        if (radix == 2)
        {
          n02 = x_8 + x_a;        n03 = x_9 + x_b;
          n22 = x_8 - x_a;        n23 = x_9 - x_b;
          n12 = x_c + x_e;        n13 = x_d + x_f;
          n32 = x_c - x_e;        n33 = x_d - x_f;
        }

        /*-----------------------------------------------------------------*/
        /* Points that are read from succesive locations map to y, y[N/4]  */
        /* y[N/2], y[3N/4] in a radix4 scheme, y, y[N/8], y[N/2],y[5N/8]   */
        /*-----------------------------------------------------------------*/ 

        y0[2*h2+2] = n02;         y0[2*h2+3] = n03;
        y1[2*h2+2] = n12;         y1[2*h2+3] = n13;
        y2[2*h2+2] = n22;         y2[2*h2+3] = n23;
        y3[2*h2+2] = n32;         y3[2*h2+3] = n33;

        

        /*-----------------------------------------------------------------*/
        /* Increment "j" by "j0". If j equals n0, then increment both "x0" */
        /* and "x2" so that double inversion is avoided.                   */
        /*-----------------------------------------------------------------*/

        j += j0;

       
        

        if (j == n0)
        {
           j  += n0;
           x0 += (int) npoints>>1;
           x2 += (int) npoints>>1;
        }
    }
}

/*==========================================================================*/
/*      Copyright (C) 1997-2000 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
