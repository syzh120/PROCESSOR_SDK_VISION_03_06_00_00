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

/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_COEF      sizeof(*f_coef)
#define VECTORSZ_COEF    (VCOP_SIMD_WIDTH * ELEMSZ_COEF)

#define ELEMSZ_FLG       sizeof(*smpl_flag)

#define ELEMSZ_OUT       sizeof(*inter_out)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define ELEMSZ_OUTFINAL   sizeof(*out)
#define VECTORSZ_OUTFINAL (VCOP_SIMD_WIDTH * ELEMSZ_OUTFINAL)

#define SAT_LO_CHAR           (0)
#define SAT_HI_CHAR           (255)
#define SAT_LO_SHORT          (0)
#define SAT_HI_SHORT          (65535)


void vcop_FilterPoly_ushort_short_ushort
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".
    __vptr_int16   f_coef,       // Pointer to cofficient array of type 'type_coef'.
    __vptr_uint8   smpl_flag,    // Pointer to sampling flag array of type char.
    __vptr_uint16  inter_out,    // Pointer to output array of "type_output".
    __vptr_uint8   out,          // Pointer to reordered output array of "type_outputfinal".
    int            w_input,      // Width of the input image in pixels.
    int            ntaps,        // No of coefficients per stage of polyphase.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            w_out,        // Width of the output image in pixels.
    int            h_out,        // Height of the output image in pixels.
    int            D,            // Downsampling value.
    int            U,            // Upsampling value.
    int            loop_end,     // Loop limit giving number of phases for polyphase
    int            rnd_shift     // Rounding and shifting amount.
)
{

    __vector Vcoef, Vin, Vflg, Vout;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /* performance: ((U/D + 1) * ntaps)/8 cyc/pix                        */
    /*-------------------------------------------------------------------*/

    _COLLATE(inter_out);
    for (int I1 = 0; I1 < w_compute/VCOP_SIMD_WIDTH; I1++)
    {
        for (int I2 = 0; I2 < h_compute; I2++)
        {
            /*-----------------------------------------------------------*/
            /* Looping over the coefficients incorporating both the up   */
            /* and downsampling values.                                  */
            /* loop_end can be thought of as the total number of phases. */
            /* loop_end = U/D + 1                                        */
            /*-----------------------------------------------------------*/

            for (int I3 = 0; I3 < loop_end; I3++)
            {
                __agen FlagAddr;

                /*-------------------------------------------------------*/
                /* For all pixels in the X-direction, we loop over       */
                /* write inter_out only the relevant output pixels in the*/
                /* vertical direction.                                   */
                /*-------------------------------------------------------*/

                FlagAddr = I3 * ELEMSZ_FLG + I2 * loop_end * ELEMSZ_FLG;

                Vflg = smpl_flag[FlagAddr].onept();

                Vout = 0;

                for (int I4 = 0; I4 < ntaps; I4++ )
                {
                     __agen CoefAddr, InAddr;

                     /*--------------------------------------------------*/
                     /* We loop over the coefficients repeatedly where   */
                     /* loop_end gives the number of phases.             */
                     /*--------------------------------------------------*/

                     CoefAddr =  I4 * U * ELEMSZ_COEF + I3 * D * ELEMSZ_COEF;

                     /*--------------------------------------------------*/
                     /* We loop over all input pixels in the course of   */
                     /* filtering operation.                             */
                     /*--------------------------------------------------*/

                     InAddr   =  I4 * w_input * ELEMSZ_IN +
                                 I2 * w_input * ELEMSZ_IN +
                                 I1 * VCOP_SIMD_WIDTH * ELEMSZ_IN;

                     Vcoef    =  f_coef[CoefAddr].onept();
                     Vin      =  in[InAddr].npt();

                     Vout    +=  (Vin * Vcoef);

                }

                /*-------------------------------------------------------*/
                /* Round and shift the output here.                      */
                /* Saturate to 16 bit unsigned values if needed here     */
                /*-------------------------------------------------------*/

                inter_out[collate(Vflg)] = Vout.round(rnd_shift).saturate(SAT_LO_CHAR, SAT_HI_CHAR);
            }
        }
    }

    /*-------------------------------------------------------------------*/
    /* Loop to reorder the collated pixels.                              */
    /* performance: (1/8) cyc/pix                                        */
    /*-------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < h_out; I1++)
    {
        for (int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  =  I2 * h_out * VCOP_SIMD_WIDTH * ELEMSZ_OUT + I1 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;
            outAddr =  I2 * VCOP_SIMD_WIDTH * ELEMSZ_OUTFINAL + I1 * w_compute * ELEMSZ_OUTFINAL;

            Vin = inter_out[inAddr].npt();

            out[outAddr].npt() = Vin;
        }
    }
}

