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

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_COEF      sizeof(*coef)
#define VECTORSZ_COEF    (VCOP_SIMD_WIDTH * ELEMSZ_COEF)

#define ELEMSZ_OUT       sizeof(*res)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define SAT_LO_UCHAR          (0)
#define SAT_HI_UCHAR          (255)
#define SAT_LO_CHAR           (-128)
#define SAT_HI_CHAR           (127)
#define SAT_LO_SHORT          (-32768)
#define SAT_HI_SHORT          (32767)

void vcop_filter_uchar_char_uchar
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_uint8   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_UCHAR, SAT_HI_UCHAR);
         }

     }
}


void vcop_filter_uchar_char_char
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int8    res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            //outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_CHAR, SAT_HI_CHAR);
         }

     }
}

void vcop_filter_uchar_char_short
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}


void vcop_filter_ushort_short_short
(
    __vptr_uint16   in,          // Pointer to an input array of "type_input".
    __vptr_int16   coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}


void vcop_filter_short_short_short
(
    __vptr_int16   in,           // Pointer to an input array of "type_input".
    __vptr_int16   coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}

void vcop_filter_ushort_ushort_short
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".
    __vptr_uint16  coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift).saturate(SAT_LO_SHORT, SAT_HI_SHORT);
         }

     }
}

void vcop_filter_ushort_short_int
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".
    __vptr_int16   coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int32   res,          // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            rnd_shift     // Rounding and shifting amount.
)
{
    __vector v_out, v_x, v_coef;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* NOT applied here, but is defered to the calling function and is   */
    /* executed on the ARP32.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute/dnsmpl_vert; I1++)
    {
        for ( int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen outAddr;

            outAddr  = I2 * VECTORSZ_OUT + I1 * (w_compute * dnsmpl_horz) * ELEMSZ_OUT;
            v_out = 0;

            for ( int I3 = 0; I3 < h_coeff; I3++)
            {
                for ( int I4 = 0; I4 < w_coeff; I4++)
                {
                    __agen coefAddr, dataAddr;

                    coefAddr = I4 * ELEMSZ_COEF + I3 * w_coeff * ELEMSZ_COEF;
                    dataAddr = I4 * ELEMSZ_IN + I3 * w_input * ELEMSZ_IN + I2 * VECTORSZ_IN + I1 * dnsmpl_vert * w_input * ELEMSZ_IN;

                    v_coef = coef[coefAddr].onept();
                    v_x    = in[dataAddr].npt();
                    v_out += v_x * v_coef;

                 }
             }

             res[outAddr].npt() = v_out.round(rnd_shift);
         }

     }
}
/*-----------------------------------------------------------------*/
/* End of file : vcop_filter_kernel.k                              */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                       */
/*=================================================================*/
