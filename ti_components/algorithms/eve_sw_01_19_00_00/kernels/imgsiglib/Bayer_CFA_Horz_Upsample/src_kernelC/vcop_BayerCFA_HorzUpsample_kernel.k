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


/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_BayerCFA_HorzUpsample, horizontal upsampling of Bayer CFA   */
/*     data for the VICP library.                                           */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_BayerCFA_HorzUpsample_ushort_short_ushort                  */
/*      (                                                                   */
/*          unsigned short *in,                                             */
/*          short          *f,                                              */
/*          unsigned short *out,                                            */
/*          int            w_input,                                         */
/*          int            ntaps,                                           */
/*          int            w_compute,                                       */
/*          int            h_compute,                                       */
/*          int            w_out,                                           */
/*          int            U,                                               */
/*          int            type_output,                                     */
/*          int            rnd_shift                                        */
/*          );                                                              */
/*                                                                          */
/*                                                                          */
/*     *in         :  Pointer to an input array of "type_input".            */
/*     *f          :  Pointer to coefficient array of type 'type_coef'.     */
/*     *out        :  Pointer to output array of "type_output".             */
/*     w_input     :  Width of the input image in pixels.                   */
/*     ntaps       :  No of coefficients per stage of polyphase.            */
/*     w_compute   :  Compute width in pixels.                              */
/*     h_compute   :  Compute height in pixels.                             */
/*     w_out       :  Width of the output image in pixels.                  */
/*     U           :  Upsampling value.                                     */
/*     type_output :  0 - BYTE,  1 - SHORT                                  */
/*     rnd_shift   :  Rounding and shifting amount.                         */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     resamples that block based on up and down-sampling values, using the */
/*     polyphase filtering approach.                                        */
/*                                                                          */
/*     The coefficients used are provided in the coefficient array and are  */
/*     computed externally in the GenFilterCoeffs() function. A "NUM_TAPS"  */
/*     value is also returned to the calling function by GenFilterCoeffs()  */
/*     and is used by BayerCFA_HorzUpsample_ushort_short_ushort()           */
/*     function as the "ntaps" value.                                       */
/*                                                                          */
/*     PERFORMANCE:                                                         */
/*     ntaps/U cyc/pix                                                      */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define VCOP_2SIMD_WIDTH (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_COEF      sizeof(*f_coef)
#define VECTORSZ_COEF    (VCOP_SIMD_WIDTH * ELEMSZ_COEF)

#define ELEMSZ_OUT       sizeof(*out)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define SAT_LO_CHAR           (0)
#define SAT_HI_CHAR           (255)
#define SAT_LO_SHORT          (0)
#define SAT_HI_SHORT          (65535)


void vcop_BayerCFA_HorzUpsample_ushort_short_ushort
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".
    __vptr_int16   f_coef,       // Pointer to cofficient array of type 'type_coef'.
    __vptr_uint16  out,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            ntaps,        // No of coefficients per stage of polyphase.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            w_out,        // Width of the output image in pixels.
    int            U,            // Upsampling value.
    int            type_output,  // 0 - BYTE,  1 - SHORT
    int            rnd_shift     // Rounding and shifting amount.
)
{

    __vector Vcoef, Vin, Vout;

    /*-----------------------------------------------------------------------*/
    /* Actual filter processing. w_compute is divided by 2 as we are dealing */
    /* with CFA input array, having BGBGBG or  GRGRGR pattern.               */
    /* Hence we loop twice in an inner loop, so as we grab the same set of   */
    /* coefficients a second time to process the pixels accordingly.         */
    /* First B, then G for 1st row...                                        */
    /* First G, then R for 2nd row and so on....                             */
    /*-----------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute; I1++) // lpend1
    {
        for (int I2 = 0; I2 < w_compute/2; I2++) //lpend2
        {
            for (int I3 = 0; I3 < 2; I3++)
            {
                __agen OutAddr;

                /*-----------------------------------------------------------*/
                /* For all pixels in the X-direction, we loop over           */
                /* write out only the relevant output pixels in the          */
                /* vertical direction. NOTE SKIP STORE FEATURE USED HERE     */
                /*-----------------------------------------------------------*/

                OutAddr = I1 * w_out * ELEMSZ_OUT +
                          I2 * 2 * U * ELEMSZ_OUT +
                          I3 * ELEMSZ_OUT;

                /*----------------------------------------------------------*/
                /* We loop over 'ntaps' coefficients, for each phase. The   */
                /* phases are hidden here as we loop over ntaps coefficients*/
                /* and compute the output of all phases in one loop.        */
                /*----------------------------------------------------------*/

                Vout = 0;

                for (int I4 = 0; I4 < ntaps; I4++ )
                {
                    __agen CoefAddr, InAddr;

                    CoefAddr =  I4 * U * ELEMSZ_COEF;

                    /*------------------------------------------------------*/
                    /* We loop over all input pixels in the course of       */
                    /* filtering operation.                                 */
                    /*------------------------------------------------------*/

                    InAddr   =   I4 * 2 * ELEMSZ_IN +
                                 I3 * ELEMSZ_IN +
                                 I2 * 2 * ELEMSZ_IN +
                                 I1 * w_input * ELEMSZ_IN;

                    Vcoef    =  f_coef[CoefAddr].npt();
                    Vin      =  in[InAddr].onept();

                    Vout    +=  (Vin * Vcoef);
                }

                /*-----------------------------------------------------------*/
                /* Round and shift the output here.                          */
                /* Saturate to 16 bit unsigned values if needed here         */
                /* Skip store U (or phases) number of valid output elements. */
                /*-----------------------------------------------------------*/

                out[OutAddr].skip() = Vout.round(rnd_shift).saturate(SAT_LO_CHAR, SAT_HI_CHAR);
            }
        }
    }
}

