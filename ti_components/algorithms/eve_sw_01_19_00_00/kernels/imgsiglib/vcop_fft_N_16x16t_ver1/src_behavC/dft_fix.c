/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vcop_fft_N_16x16t_c.h"

#define Qpt (15)
#define Qs   32767
#define Qr   16384
#define Qsx  64

/*******************************************************/
/*  DFT routine: O(N^2) routine                        */
/*                                                     */
/*  Integer version of DFT for C6200                   */
/*                                                     */
/* data_in: interleaved real-complex samples           */
/* wn:      twiddle factors array                      */
/* data_out: DFT results as output                     */
/* N: N complex points                                 */
/*                                                     */
/* Actually length of each array is 2N                 */
/*                                                     */
/* Verified bit-exact results with gcc and cl6x 3.10   */
/* Verified bit-exact results with Matlab routine      */
/*                                                     */
/* Source: P.M.Embree and Bruce Kimble                 */
/*                                                     */
/* Converted orig. source to C6200                     */
/*******************************************************/

void dft_float( float *data_in, float * w, int N, float *data_out)
{
  int k, n,p;
  float *in_real,  *in_imag;
  float *w_real,   *w_imag;
  float *o_real,   *o_imag;
  float *inptr,    *optr, *wptr;
  float  sum_real, sum_imag;
  float  tmp_real, tmp_imag;

  in_real = data_in;
  in_imag = data_in + 1;
  w_real  = w;
  w_imag  = w + 1;
  o_real  = data_out;
  o_imag  = data_out + 1;

  for ( k = 0; k < N; k++)
  {

     optr   = data_out + (2*k);
     o_real = optr;
     o_imag = optr + 1;
     in_real = data_in;
     in_imag = data_in + 1;  

     sum_real = *in_real;
     sum_imag = *in_imag;

     for ( n = 1; n < N; n++)
     {
         p = (int)((n*k) %N);
         wptr  = w       + (2*p);
         inptr = data_in + (2*n);

         w_real   = wptr;
         w_imag   = wptr + 1;

         in_real  = inptr;
         in_imag  = inptr + 1;

         tmp_real = (in_real[0]*w_real[0] - in_imag[0]*w_imag[0]);
         tmp_imag = (in_real[0]*w_imag[0] + in_imag[0]*w_real[0]);

         sum_real += tmp_real;
         sum_imag += tmp_imag;
    }

    *o_real = sum_real;
    *o_imag = sum_imag;
   }        
}


void dft_fix(short *data_in, short *w, int N, short *data_out)
{
  int k, n,p;
  short *in_real,  *in_imag;
  short *w_real,   *w_imag;
  short *o_real,   *o_imag;
  short *inptr,    *optr, *wptr;
  short sum_real, sum_imag;
  short tmp_real, tmp_imag;

  in_real = data_in;
  in_imag = data_in + 1;
  w_real  = w;
  w_imag  = w + 1;
  o_real  = data_out;
  o_imag  = data_out + 1;

  for (k = 0; k < N; k++)
  {

     optr   = data_out + (2*k);
     o_real = optr;
     o_imag = optr + 1;
     in_real = data_in;
     in_imag = data_in + 1;  

     sum_real = *in_real;
     sum_imag = *in_imag;

     for (n = 1; n < N; n++)
     {
         p = (int)((n*k) %N);
         wptr  = w       + (2*p);
         inptr = data_in + (2*n);

         w_real   = wptr;
         w_imag   = wptr + 1;

         in_real  = inptr;
         in_imag  = inptr + 1;

         tmp_real = (int) ((in_real[0]*w_real[0] - in_imag[0]*w_imag[0] + 0x4000) >> 15);
         tmp_imag = (int) ((in_real[0]*w_imag[0] + in_imag[0]*w_real[0] + 0x4000) >> 15);

         sum_real += tmp_real;
         sum_imag += tmp_imag;
    }

    *o_real = sum_real;
    *o_imag = sum_imag;
   }        
}

#define PI 3.14159265358979323846
#pragma DATA_ALIGN (w_new , 8);
#pragma DATA_ALIGN (inpu , 8);
#pragma DATA_ALIGN (outpu , 8);

#define M0 64
short w_new[2    * M0];
short inpu [2    * M0];
short outpu[2    * M0];
short data_in[2  * M0];
short data_out[2 * M0];
short wv[2 * M0 + 24];
short wv_mod[2 * M0 + 24];
short wn[2 * M0];
float wf[2 * M0];
float xf[2 * M0];
float yf[2 * M0];

static short d2s(double d)
{
    if (d >=  32767.0) return  32767;
    if (d <= -32768.0) return -32768;
    return (short)d;
}

void gen_twiddle(short *w, int n, double scale)
{
    int i, j, k;

    for (j = 1, k = 0; j < n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j << 1)
        {
            printf ("i:%d, j:%d \n", i, j);

            w[k + 11] = d2s(scale * cos(6.0 * PI * (i + j) / n));
            w[k + 10] = d2s(scale * sin(6.0 * PI * (i + j) / n));
            w[k +  9] = d2s(scale * cos(6.0 * PI * (i    ) / n));
            w[k +  8] = d2s(scale * sin(6.0 * PI * (i    ) / n));

            w[k +  7] = d2s(scale * cos(4.0 * PI * (i + j) / n));
            w[k +  6] = d2s(scale * sin(4.0 * PI * (i + j) / n));
            w[k +  5] = d2s(scale * cos(4.0 * PI * (i    ) / n));
            w[k +  4] = d2s(scale * sin(4.0 * PI * (i    ) / n));

            w[k +  3] = d2s(scale * cos(2.0 * PI * (i + j) / n));
            w[k +  2] = d2s(scale * sin(2.0 * PI * (i + j) / n));
            w[k +  1] = d2s(scale * cos(2.0 * PI * (i    ) / n));
            w[k +  0] = d2s(scale * sin(2.0 * PI * (i    ) / n));

            k += 12;
        }

    }

    printf ("k Original approach %d \n", k);

    w[2*n - 1] = w[2*n - 3] = w[2*n - 5] = 32767;
    w[2*n - 2] = w[2*n - 4] = w[2*n - 6] = 0; 
}

void print_twiddle(FILE *fp, short *w, int N)
{
   int i;

   fprintf (fp, "short w_vector[%d] = \n", N);

   for (i = 0; i < (N + 8); i++)
   {
       fprintf (fp, "0x%.4X, 0x%.4X, ", (w[2*i] & 0xFFFF), (w[2*i +1] & 0xFFFF));
       if ((i+1)%4 == 0) fprintf (fp, "\n");
   }
}


void gen_twiddle_vector (short *w, int n, double scale, short *wc)
{
    int i, j, k, kc;


    for (j = 1, k = 0, kc = 0; j < n >> 2; j = j << 2)
    {

        for (i = 0; i < n >> 2; )
        {
            wc [kc + 0]  = w[k +  0] = d2s(scale * sin(2.0 * PI * (i) / n));
            wc [kc + 1]  = w[k +  1] = d2s(scale * cos(2.0 * PI * (i) / n));
            wc [kc + 16] = w[k +  4] = d2s(scale * sin(4.0 * PI * (i) / n));
            wc [kc + 17] = w[k +  5] = d2s(scale * cos(4.0 * PI * (i) / n));
            wc [kc + 32] = w[k +  8] = d2s(scale * sin(6.0 * PI * (i) / n));
            wc [kc + 33] = w[k +  9] = d2s(scale * cos(6.0 * PI * (i) / n));
            
            wc [kc + 2]  = w[k +  2] = d2s(scale * sin(2.0 * PI * (i + j) / n));
            wc [kc + 3]  = w[k +  3] = d2s(scale * cos(2.0 * PI * (i + j) / n));
            wc [kc + 18] = w[k +  6] = d2s(scale * sin(4.0 * PI * (i + j) / n));
            wc [kc + 19] = w[k +  7] = d2s(scale * cos(4.0 * PI * (i + j) / n));
            wc [kc + 34] = w[k + 10] = d2s(scale * sin(6.0 * PI * (i + j) / n));
            wc [kc + 35] = w[k + 11] = d2s(scale * cos(6.0 * PI * (i + j) / n));

            k  += 12;
            kc += 4;

            wc [kc + 0]  = w[k +  0] = d2s(scale * sin(2.0 * PI * (i + 2*j) / n));
            wc [kc + 1]  = w[k +  1] = d2s(scale * cos(2.0 * PI * (i + 2*j) / n));
            wc [kc + 16] = w[k +  4] = d2s(scale * sin(4.0 * PI * (i + 2*j) / n));
            wc [kc + 17] = w[k +  5] = d2s(scale * cos(4.0 * PI * (i + 2*j) / n));
            wc [kc + 32] = w[k +  8] = d2s(scale * sin(6.0 * PI * (i + 2*j) / n));
            wc [kc + 33] = w[k +  9] = d2s(scale * cos(6.0 * PI * (i + 2*j) / n));
            
            wc [kc + 2]  = w[k +  2] = d2s(scale * sin(2.0 * PI * (i + 3*j) / n));
            wc [kc + 3]  = w[k +  3] = d2s(scale * cos(2.0 * PI * (i + 3*j) / n));
            wc [kc + 18] = w[k +  6] = d2s(scale * sin(4.0 * PI * (i + 3*j) / n));
            wc [kc + 19] = w[k +  7] = d2s(scale * cos(4.0 * PI * (i + 3*j) / n));
            wc [kc + 34] = w[k + 10] = d2s(scale * sin(6.0 * PI * (i + 3*j) / n));
            wc [kc + 35] = w[k + 11] = d2s(scale * cos(6.0 * PI * (i + 3*j) / n));

            k  += 12;
            kc += 4;

            i += (4 * j);

            if (i < (n >> 2))
            {
                wc [kc + 0]  = w[k +  0] = d2s(scale * sin(2.0 * PI * (i) / n));
                wc [kc + 1]  = w[k +  1] = d2s(scale * cos(2.0 * PI * (i) / n));
                wc [kc + 16] = w[k +  4] = d2s(scale * sin(4.0 * PI * (i) / n));
                wc [kc + 17] = w[k +  5] = d2s(scale * cos(4.0 * PI * (i) / n));
                wc [kc + 32] = w[k +  8] = d2s(scale * sin(6.0 * PI * (i) / n));
                wc [kc + 33] = w[k +  9] = d2s(scale * cos(6.0 * PI * (i) / n));
                
                wc [kc + 2]  = w[k +  2] = d2s(scale * sin(2.0 * PI * (i + j) / n));
                wc [kc + 3]  = w[k +  3] = d2s(scale * cos(2.0 * PI * (i + j) / n));
                wc [kc + 18] = w[k +  6] = d2s(scale * sin(4.0 * PI * (i + j) / n));
                wc [kc + 19] = w[k +  7] = d2s(scale * cos(4.0 * PI * (i + j) / n));
                wc [kc + 34] = w[k + 10] = d2s(scale * sin(6.0 * PI * (i + j) / n));
                wc [kc + 35] = w[k + 11] = d2s(scale * cos(6.0 * PI * (i + j) / n));

                k  += 12;
                kc += 4;

                wc [kc + 0]  = w[k +  0] = d2s(scale * sin(2.0 * PI * (i + 2*j) / n));
                wc [kc + 1]  = w[k +  1] = d2s(scale * cos(2.0 * PI * (i + 2*j) / n));
                wc [kc + 16] = w[k +  4] = d2s(scale * sin(4.0 * PI * (i + 2*j) / n));
                wc [kc + 17] = w[k +  5] = d2s(scale * cos(4.0 * PI * (i + 2*j) / n));
                wc [kc + 32] = w[k +  8] = d2s(scale * sin(6.0 * PI * (i + 2*j) / n));
                wc [kc + 33] = w[k +  9] = d2s(scale * cos(6.0 * PI * (i + 2*j) / n));
                
                wc [kc + 2]  = w[k +  2] = d2s(scale * sin(2.0 * PI * (i + 3*j) / n));
                wc [kc + 3]  = w[k +  3] = d2s(scale * cos(2.0 * PI * (i + 3*j) / n));
                wc [kc + 18] = w[k +  6] = d2s(scale * sin(4.0 * PI * (i + 3*j) / n));
                wc [kc + 19] = w[k +  7] = d2s(scale * cos(4.0 * PI * (i + 3*j) / n));
                wc [kc + 34] = w[k + 10] = d2s(scale * sin(6.0 * PI * (i + 3*j) / n));
                wc [kc + 35] = w[k + 11] = d2s(scale * cos(6.0 * PI * (i + 3*j) / n));

                k   += 12;
                kc  +=  4;
                kc  += 32;

                i += (4 * j);
            }
           

        }

    }

    printf ("k Modified approach %d \n", k);

    w[2*n - 1] = w[2*n - 3] = w[2*n - 5] = 32767;
    w[2*n - 2] = w[2*n - 4] = w[2*n - 6] = 0; 
}







int main( )
{
        int i;
        int j;
        double b;
        double c;
        double M=32767.0;

        

        float arg;
        short *wrptr, *wiptr;
        short *orptr, *oiptr;
        short *ornptr,*oinptr;
        float sig;
        float err;

        int   N = 64;
        int   entries, k;

        FILE  *fp;

        arg   = 8*atan(1.0)/N;
        wrptr = wn;
        wiptr = wn+1;

        for (i=0; i< N; i++)
        {
            *wrptr =  (short) ((float) cos(arg*i) * Qs);
            *wiptr = -(short) ((float) sin(arg*i) * Qs);

             wf[2*i]    = (float) (cos(arg * i));
             wf[2*i +1] = -(float) (sin(arg * i)); 

             wrptr += 2;
             wiptr += 2;
        }


        for (i=j=0;i< N;i++,j+=2)
        {
                #if 0
                b = 0;
                c = Qsx  * sin(PI*6*i/16);
                #else
                b = rand() % Qsx;
                c = rand() % Qsx;
                #endif

                inpu[j]   = (short) b;
                inpu[j+1] = (short)c;
                data_in[j] = inpu[j];
                data_in[j+1] = inpu[j+1];
                xf[j]      = (float) inpu[j];
                xf[j +1]   = (float) inpu[j+1];

        }

        fp = fopen ("data.dat", "w");
        if (!fp) printf ("\n Unable to open file");
        if (!fp) exit (-1);

        fprintf (fp, "short x[2048] = { \n");
        for (i = 0; i < N; i++)
        {
            fprintf (fp, "0x%.4X, 0x%.4X, ", (inpu[2*i] & 0xFFFF), (inpu[2*i + 1] & 0xFFFF));
            if ((i+1)%4 == 0) fprintf (fp, "\n");
        }
        fprintf (fp, "}\n");


        printf("Running Floating point DFT \n");
        dft_float(xf,wf,N, yf);
        printf("Finishing DFT float \n");


        printf("Running Fixed point DFT \n");
        dft_fix(data_in,wn,N, data_out);
        printf("Finishing DFT \n");
 
        printf("Gen. twiddle \n");
        gen_twiddle(w_new, N, M);
        printf("Finished twiddle \n");

        printf("Running fft16x16t\n");
        fft16x16t_cn(w_new, N,inpu,outpu);
        printf("Finishing fft16x16t\n");

 
        printf("Gen. vector twiddle \n");
        gen_twiddle_vector (wv, N, M, wv_mod);
        print_twiddle(fp, wv_mod, N);
        printf("Finished vector twiddle \n");

        if (memcmp (wv, w_new, sizeof (w_new))) 
        {
            printf ("Fail in transformation \n");
        }

        #if 0
        for ( i = 0; i < N; i++)
        {
            printf ("i:%d, wvr:%d, wvi:%d, wvmodr:%d, wvmodi:%d \n",
                     i,    w_new[2*i], w_new[2*i + 1], wv[2*i], wv[2*i + 1]
                   );
        }
        #endif


        fclose (fp);


        

        sig = 0;
        err = 0;

        for (i=0; i<N; i++)
        {
            #if 1
            printf("i:%d, dftfr:%f, dftfi:%f, fftr:%d, ffti:%d \n",
                    i, yf[2*i], yf[2*i + 1], outpu[2*i], outpu[2*i + 1]);
            #endif

            #if 0
            sig = sig + (*orptr * *orptr) + (*oiptr * *oiptr);
            err = err + ((*ornptr - *orptr) * (*ornptr - *orptr))
                      + ((*oinptr - *oiptr) * (*oinptr - *oiptr));
            #else
            sig = sig + (yf[2*i] * yf[2*i]) + (yf[2*i +1] * yf[2*i + 1]);
            err = err + (((outpu[2*i] - yf[2*i])* (outpu[2*i] - yf[2*i])) + ((outpu[2*i + 1] - yf[2*i + 1])* (outpu[2*i + 1] - yf[2*i + 1])));
            #endif
        }

        if (err < 0) err = -err;
    

        printf("sig:%f, err:%f, SNR:%f \n", sig, err, 10 * log(sig/err));

               
        return(0);

}  







