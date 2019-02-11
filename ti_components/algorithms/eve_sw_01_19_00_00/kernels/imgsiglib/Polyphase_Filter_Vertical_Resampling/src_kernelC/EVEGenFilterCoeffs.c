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
#include <math.h>

short GenResamplingCoeffs
(
    int   U,                 // Up sampling value
    int   D,                 // Down sampling value
    int   taps,              // original number of taps 
    short *coeffs,           // pointer to coefficient array
    unsigned char *sampling_pattern, //Pattern (mask) for predicated stores
    int   *pattern_size      // Size of the pattern array
) 
{
    int   i, j, k;
    int   resample_max_ud;
    float sample;
    short ntaps;
    float pi;
    float sum;
    int val, limit, prev_index;
    float filt_coef[256] = {0.0};

    /*-------------------------------------------------------------------*/
    /* Filter built for taps * max(U,D). Choose something reasonable!    */
    /*-------------------------------------------------------------------*/

    pi = (float) atan(1.0) * taps;
    resample_max_ud = (U >= D) ? U : D;
    
    /* first generate (4*max_ud)-tap filter coefficients */
    
    for (i = 0; i < taps * resample_max_ud; i++) 
    {
        /*---------------------------------------------------------------*/
        /* Get the sample or step values here, window for coefficients   */
        /*---------------------------------------------------------------*/

        if (i <= (taps/2) * resample_max_ud) 
            sample = (float) (i / ((taps/2.0) * resample_max_ud));
        else
            sample = (float) ((taps * resample_max_ud - i)/((taps/2.0) * resample_max_ud));
        
        /*---------------------------------------------------------------*/
        /* Computing the filter coefficients, center coef has max value. */
        /*---------------------------------------------------------------*/

        if (i == (taps/2) * resample_max_ud) 
            filt_coef[i] = 1.0;
        else
            filt_coef[i] = sample * (float) sin((pi * (i - (taps/2) * resample_max_ud))/resample_max_ud)
                / ((pi * (i - (taps/2) * resample_max_ud)) / resample_max_ud);
        
    }

    /*-------------------------------------------------------------------*/
    /* taps/polyfilter => total_taps (in this case "i")/U.               */
    /*-------------------------------------------------------------------*/
    ntaps = i/U;

  /* next normalize each phase */
  for (i = 0; i < U; i++) 
  {
      sum = 0.0;
      for (j = i; j < taps * resample_max_ud; j += U)
          sum += filt_coef[j];  

      for (j = i; j < taps * resample_max_ud; j += U) 
          coeffs[j] = (short) ((filt_coef[j] / sum) * 4096);
  }    

  
  /*-------------------------------------------------------------------*/
  /* For U/D generate the flag information giving sampling pattern.    */
  /*-------------------------------------------------------------------*/

    limit = (U > D) ? U : D;

    k = 0;
    prev_index = 1;
    for (i = 0; i < limit + 1; i++)
    {
        for ( j = 0; j < U/D + 1; j++)
        {
            val = (int) floor(j + (i * U/D) + 0.5);
            if (val == prev_index)
            {
                sampling_pattern[k-1] = 0;
                sampling_pattern[k++] = 1;
            }
            else sampling_pattern[k++] = 1;

            prev_index = val;
        }
    }

    /*-------------------------------------------------------------------*/
    /* We write the pattern size out so we know the size to replicate    */
    /* for writing the flags needed for doing collated stores. Due to    */
    /* the fact that we have only 4 levels of nested looping in VCOP, we */
    /* have to write the output address pattern as a repetitive pattern  */
    /* of *pattern_size and repeat it over to account for the size of    */
    /* filter.                                                           */
    /*-------------------------------------------------------------------*/

    *pattern_size = (U > D) ? ((limit  - 1) * (U/D + 1)) : (limit * (U/D + 1));

#if 0
    if (U > D)
    {
        printf("\nSampling pattern is: \n\n");
        for (i = 0; i < ((limit  - 1) * (U/D + 1)); i++)
        {
            printf("%d, ", sampling_pattern[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\nSampling pattern is: \n\n");
        for (i = 0; i < (limit * (U/D + 1)); i++)
        {
            printf("%d, ", sampling_pattern[i]);
        }

        printf("\n");
    }
#endif

   return ntaps;
} 




