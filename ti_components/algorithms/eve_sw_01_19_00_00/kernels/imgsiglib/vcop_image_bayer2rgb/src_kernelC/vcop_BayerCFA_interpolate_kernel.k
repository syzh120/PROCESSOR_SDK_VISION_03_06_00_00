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


/*-----------------------------------------------------------------*/
/* NAME : vcop_BayerCFA_interpolate                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The "vcop_BayerCFA_interpolate" code accepts 8 or 16-bit data   */
/* in the form of 8 or 16-bit Bayer Pattern, and writes out        */
/* the result as separate R, G and B planes. The output is         */
/* interpolated data to match the input width and height.          */
/* Interpolation is carried out by averaging the left and right    */
/* pixels, or the top and bottom pixels as the case may be.        */
/* In some cases, all four of the top-bottom-left-right pixels are */
/* used to compute the center pixel value.                         */
/*                                                                 */
/*                                                                 */
/* The Bayer pattern is as follows:                                */
/* -------------------------------                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/*                                                                 */
/* After demosiacing or deinterleaving step we get:                */
/* ------------------------------------------------                */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/*                                                                 */
/* R  rx R  rx R  rx R                                             */
/* ry rz ry rz ry rz ry                                            */
/* R  rx R  rx R  rx R                                             */
/* ry rz ry rz ry rz ry                                            */
/*                                                                 */
/* G gx G  gx G  gx G                                              */
/* G gy G  gy G  gy G                                              */
/* G gx G  gx G  gx G                                              */
/* G gy G  gy G  gy G                                              */
/*                                                                 */
/* At this stage, bx, by, bz, rx, ry, rz, gx, gy are zeros.        */
/*                                                                 */
/* After interpolating we get:                                     */
/* ---------------------------                                     */
/* Where bx = (Bleft + Bright)/2                                   */
/* Where by = (Btop  + Bbottom)/2                                  */
/* Where bz = (Bleft + Bright + Btop + Bbottom)/4                  */
/*                                                                 */
/* Where rx = (Rleft + Rright)/2                                   */
/* Where ry = (Rtop  + Rbottom)/2                                  */
/* Where rz = (Rleft + Rright + Rtop + Rbottom)/4                  */
/*                                                                 */
/* Where gx = (Gleft + Gright)/2                                   */
/* Where gy = (Gtop  + Gbottom)/2                                  */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_BayerCFA_Interpolate_char                             */
/* (                                                               */
/*     __vptr_uint8   CFA_char,                                    */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint8   R_char,                                      */
/*     __vptr_uint8   G_char,                                      */
/*     __vptr_uint8   B_char                                       */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop__BayerCFA_Interpolate_short                           */
/* (                                                               */
/*     __vptr_uint16  CFA_short,                                   */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint16  R_short,                                     */
/*     __vptr_uint16  G_short,                                     */
/*     __vptr_uint16  B_short                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* BayerCFA_interpolate_char: (2/16 * 1/3) + 13/16 = 0.85 cyc/pix  */
/* BayerCFA_interpolate_short: (2/16 * 1/3) + 13/16 = 0.85 cyc/pix */
/*                                                                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH   (VCOP_SIMD_WIDTH * 2)

#define ELEMSZ_IN_CHAR     sizeof(*CFA_char)
#define VECTORSZ_IN_CHAR  (ELEMSZ_IN_CHAR * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN_SHORT     sizeof(*CFA_short)
#define VECTORSZ_IN_SHORT  (ELEMSZ_IN_SHORT * VCOP_SIMD_WIDTH)

/* * * * * * * * * * * * * * * * * * * * */
void vcop_BayerCFA_interpolate_short_BGGR
(
    __vptr_uint16  CFA_short,
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    __vptr_uint16  R_short,
    __vptr_uint16  G_short,
    __vptr_uint16  B_short,
    unsigned int   out_stride
)
{
    __vector Vzero_a, Vzero_b;

    /*------------------------------------------------------------*/
    /* The Bayer pattern is as follows:                           */
    /* -------------------------------                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /*                                                            */
    /* DEMOSAICing STEP                                           */
    /* First step is to copy the R, G and B pixels which exist to */
    /* the separate R, G and B planes keeping their locations     */
    /* the same as the input array. This means, there are holes   */
    /* in these planar arrays which will eventually be filled     */
    /* with the interpolated values.                              */
    /*                                                            */
    /* This step also does the interleave step for G plane by     */
    /* using the top and bottom pixels that are already read-in.  */
    /* This step takes and extra cycle as we need to make copies  */
    /* of some of the registers due to their odd/even numbering.  */
    /* Due to this, this loop takes 3 cycles to process 16 pixs.  */
    /*                                                            */
    /* Performance: 2/16 * (1/3) cyc/pix                          */
    /*------------------------------------------------------------*/

    Vzero_a =  0;
    Vzero_b =  0;

    for (int I3 = 0; I3 < ((blk_h/2) +1); I3++)
    {
        __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;

        for (int I4 = 0; I4 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I4++)
        {
            __agen Addr_in, Addr_out;

            Addr_in  = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 *  in_w * ELEMSZ_IN_SHORT;
            Addr_out     = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VB0, VG0) = CFA_short[Addr_in].deinterleave();  // ibufla
            (VG1, VR0) = (CFA_short + (in_w * ELEMSZ_IN_SHORT))[Addr_in].deinterleave(); // ibufla

            /*----------------------------------------------------*/
            /* Make copies to work atruncate the odd/even register*/
            /* usage issue. Even numbered registers cannot be the */
            /* first register in a register pair during store.    */
            /*----------------------------------------------------*/

            VB0_copy = VB0;
            VR0_copy = VR0;

            B_short[Addr_out].interleave()  = (VB0_copy, Vzero_a); // ibufha
            G_short[Addr_out].skip()  = VG0; // wbuf

            R_short[Addr_out].interleave() = (VR0_copy, Vzero_b);  // ibufha
            (G_short + (out_stride * ELEMSZ_IN_SHORT))[Addr_out].skip() = VG1; // wbuf
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /* Performance: (3/16) * 2 * (1/2) cyc/pix                    */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < ((blk_h/2)+1); I3++)
    {
        __vector VB0, VB1, VR0, VR1, Vrx, Vbx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            VB0 = B_short[Addr].ds2();
            VB1 = (B_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            VR0 = R_short[Addr].ds2();
            VR1 = (R_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vbx = VB0 + VB1;
            Vrx = VR0 + VR1;

            (B_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vbx.truncate(1);
            (R_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vrx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /* performance: 3/8 cyc/pix                                   */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < (blk_h+1); I3++)
    {
        __vector VG0, VG1, Vgx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * out_stride * ELEMSZ_IN_SHORT;

            VG0 = G_short[Addr].ds2();
            VG1 = (G_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vgx = VG0 + VG1;

            (G_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vgx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 2 (Vertical compute):                   */
    /* ------------------------------------------                 */
    /* Here by = (Btop  + Bbottom)/2                              */
    /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* bz = (Btop_new + Bbottom_new)/2                            */
    /*                                                            */
    /* Here ry = (Rtop  + Rbottom)/2                              */
    /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* rz = (Rtop_new + Rbottom_new)/2                            */
    /*                                                            */
    /* Performance: 4/16 * (1/2) * 2 = cycles + H/2 + (R, B)      */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_w/VCOP_2SIMD_WIDTH; I3++)
    {
        __vector VB0_lp3, VB1_lp3, VR0_lp3, VR1_lp3, Vb0, Vb1, Vr0, Vr1;
        __vector VR2, VR3, VB2, VB3;

        __agen Addr_toprow;

        Addr_toprow = I3 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT;

        (VB0_lp3, VB1_lp3) = B_short[Addr_toprow].deinterleave();
        (VR0_lp3, VR1_lp3) = R_short[Addr_toprow].deinterleave();

        for (int I4 = 0; I4 < blk_h/2; I4++)
        {
            __agen Addr;

            Addr  = I3 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I4 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VB2, VB3) = (B_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();
            (VR2, VR3) = (R_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();

            Vb0 = (VB0_lp3 + VB2);
            Vb1 = (VB1_lp3 + VB3);

            Vr0 = (VR0_lp3 + VR2);
            Vr1 = (VR1_lp3 + VR3);

            VB0_lp3 = VB2;          // Save bottom pixels as 'new' top pixel
            VB1_lp3 = VB3;          // Save bottom pixels as 'new' top pixel
            VR0_lp3 = VR2;          // Save bottom pixels as 'new' top pixel
            VR1_lp3 = VR3;          // Save bottom pixels as 'new' top pixel

            (B_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vb0, Vb1).truncate(1);
            (R_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vr0, Vr1).truncate(1);
        }
    }
}

void vcop_BayerCFA_interpolate_short_GRBG
(
    __vptr_uint16  CFA_short,
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    __vptr_uint16  R_short,
    __vptr_uint16  G_short,
    __vptr_uint16  B_short,
    unsigned int   out_stride
)
{
    __vector Vzero_a, Vzero_b;
    /*------------------------------------------------------------*/
    /* The Bayer pattern is as follows:                           */
    /* -------------------------------                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /* G R G R G R G R                                            */
    /* B G B G B G B G                                            */
    /*                                                            */
    /* DEMOSAICing STEP                                           */
    /* First step is to copy the R, G and B pixels which exist to */
    /* the separate R, G and B planes keeping their locations     */
    /* the same as the input array. This means, there are holes   */
    /* in these planar arrays which will eventually be filled     */
    /* with the interpolated values.                              */
    /*                                                            */
    /* This step also does the interleave step for G plane by     */
    /* using the top and bottom pixels that are already read-in.  */
    /* This step takes and extra cycle as we need to make copies  */
    /* of some of the registers due to their odd/even numbering.  */
    /* Due to this, this loop takes 3 cycles to process 16 pixs.  */
    /*                                                            */
    /* Performance: 2/16 * (1/3) cyc/pix                          */
    /*------------------------------------------------------------*/

    Vzero_a =  0;
    Vzero_b =  0;

    for (int I3 = 0; I3 < ((blk_h/2) +1); I3++)
    {
        __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;

        for (int I4 = 0; I4 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I4++)
        {
            __agen Addr_in, Addr_out;

            Addr_in  = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 *  in_w * ELEMSZ_IN_SHORT;
            Addr_out     = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VG0, VR0) = CFA_short[Addr_in].deinterleave();  // ibufla
            (VB0, VG1) = (CFA_short + (in_w * ELEMSZ_IN_SHORT))[Addr_in].deinterleave(); // ibufla

            /*----------------------------------------------------*/
            /* Make copies to work atruncate the odd/even register*/
            /* usage issue. Even numbered registers cannot be the */
            /* first register in a register pair during store.    */
            /*----------------------------------------------------*/

            VB0_copy = VB0;
            VR0_copy = VR0;

            B_short[Addr_out].interleave()  = (VB0_copy, Vzero_a); // ibufha
            G_short[Addr_out].skip()  = VG0; // wbuf

            R_short[Addr_out].interleave() = (VR0_copy, Vzero_b);  // ibufha
            (G_short + (out_stride * ELEMSZ_IN_SHORT))[Addr_out].skip() = VG1; // wbuf
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /* Performance: (3/16) * 2 * (1/2) cyc/pix                    */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < ((blk_h/2)+1); I3++)
    {
        __vector VB0, VB1, VR0, VR1, Vrx, Vbx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            VB0 = B_short[Addr].ds2();
            VB1 = (B_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            VR0 = R_short[Addr].ds2();
            VR1 = (R_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vbx = VB0 + VB1;
            Vrx = VR0 + VR1;

            (B_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vbx.truncate(1);
            (R_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vrx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /* performance: 3/8 cyc/pix                                   */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < (blk_h+1); I3++)
    {
        __vector VG0, VG1, Vgx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * out_stride * ELEMSZ_IN_SHORT;

            VG0 = G_short[Addr].ds2();
            VG1 = (G_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vgx = VG0 + VG1;

            (G_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vgx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 2 (Vertical compute):                   */
    /* ------------------------------------------                 */
    /* Here by = (Btop  + Bbottom)/2                              */
    /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* bz = (Btop_new + Bbottom_new)/2                            */
    /*                                                            */
    /* Here ry = (Rtop  + Rbottom)/2                              */
    /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* rz = (Rtop_new + Rbottom_new)/2                            */
    /*                                                            */
    /* Performance: 4/16 * (1/2) * 2 = cycles + H/2 + (R, B)      */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_w/VCOP_2SIMD_WIDTH; I3++)
    {
        __vector VB0_lp3, VB1_lp3, VR0_lp3, VR1_lp3, Vb0, Vb1, Vr0, Vr1;
        __vector VR2, VR3, VB2, VB3;

        __agen Addr_toprow;

        Addr_toprow = I3 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT;

        (VB0_lp3, VB1_lp3) = B_short[Addr_toprow].deinterleave();
        (VR0_lp3, VR1_lp3) = R_short[Addr_toprow].deinterleave();

        for (int I4 = 0; I4 < blk_h/2; I4++)
        {
            __agen Addr;

            Addr  = I3 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I4 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VB2, VB3) = (B_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();
            (VR2, VR3) = (R_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();

            Vb0 = (VB0_lp3 + VB2);
            Vb1 = (VB1_lp3 + VB3);

            Vr0 = (VR0_lp3 + VR2);
            Vr1 = (VR1_lp3 + VR3);

            VB0_lp3 = VB2;          // Save bottom pixels as 'new' top pixel
            VB1_lp3 = VB3;          // Save bottom pixels as 'new' top pixel
            VR0_lp3 = VR2;          // Save bottom pixels as 'new' top pixel
            VR1_lp3 = VR3;          // Save bottom pixels as 'new' top pixel

            (B_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vb0, Vb1).truncate(1);
            (R_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vr0, Vr1).truncate(1);
        }
    }
}

void vcop_BayerCFA_interpolate_short_RGGB
(
    __vptr_uint16  CFA_short,
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    __vptr_uint16  R_short,
    __vptr_uint16  G_short,
    __vptr_uint16  B_short,
    unsigned int   out_stride
)
{
    __vector Vzero_a, Vzero_b;

    /*------------------------------------------------------------*/
    /* The Bayer pattern is as follows:                           */
    /* -------------------------------                            */
    /* R G R G R G R G                                           */
    /* G B G B G B G B                                           */
    /* R G R G R G R G                                           */
    /* G B G B G B G B                                           */
    /* R G R G R G R G                                           */
    /* G B G B G B G B                                           */
    /*                                                            */
    /* DEMOSAICing STEP                                           */
    /* First step is to copy the R, G and B pixels which exist to */
    /* the separate R, G and B planes keeping their locations     */
    /* the same as the input array. This means, there are holes   */
    /* in these planar arrays which will eventually be filled     */
    /* with the interpolated values.                              */
    /*                                                            */
    /* This step also does the interleave step for G plane by     */
    /* using the top and bottom pixels that are already read-in.  */
    /* This step takes and extra cycle as we need to make copies  */
    /* of some of the registers due to their odd/even numbering.  */
    /* Due to this, this loop takes 3 cycles to process 16 pixs.  */
    /*                                                            */
    /* Performance: 2/16 * (1/3) cyc/pix                          */
    /*------------------------------------------------------------*/

    Vzero_a =  0;
    Vzero_b =  0;

    for (int I3 = 0; I3 < ((blk_h/2) +1); I3++)
    {
        __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;

        for (int I4 = 0; I4 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I4++)
        {
            __agen Addr_in, Addr_out;

            Addr_in  = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 *  in_w * ELEMSZ_IN_SHORT;
            Addr_out     = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VR0, VG0) = CFA_short[Addr_in].deinterleave();  // ibufla
            (VG1, VB0) = (CFA_short + (in_w * ELEMSZ_IN_SHORT))[Addr_in].deinterleave(); // ibufla

            /*----------------------------------------------------*/
            /* Make copies to work atruncate the odd/even register*/
            /* usage issue. Even numbered registers cannot be the */
            /* first register in a register pair during store.    */
            /*----------------------------------------------------*/

            VB0_copy = VB0;
            VR0_copy = VR0;

            B_short[Addr_out].interleave()  = (VB0_copy, Vzero_a); // ibufha
            G_short[Addr_out].skip()  = VG0; // wbuf

            R_short[Addr_out].interleave() = (VR0_copy, Vzero_b);  // ibufha
            (G_short + (out_stride * ELEMSZ_IN_SHORT))[Addr_out].skip() = VG1; // wbuf
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /* Performance: (3/16) * 2 * (1/2) cyc/pix                    */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < ((blk_h/2)+1); I3++)
    {
        __vector VB0, VB1, VR0, VR1, Vrx, Vbx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            VB0 = B_short[Addr].ds2();
            VB1 = (B_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            VR0 = R_short[Addr].ds2();
            VR1 = (R_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vbx = VB0 + VB1;
            Vrx = VR0 + VR1;

            (B_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vbx.truncate(1);
            (R_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vrx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /* performance: 3/8 cyc/pix                                   */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < (blk_h+1); I3++)
    {
        __vector VG0, VG1, Vgx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * out_stride * ELEMSZ_IN_SHORT;

            VG0 = G_short[Addr].ds2();
            VG1 = (G_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vgx = VG0 + VG1;

            (G_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vgx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 2 (Vertical compute):                   */
    /* ------------------------------------------                 */
    /* Here by = (Btop  + Bbottom)/2                              */
    /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* bz = (Btop_new + Bbottom_new)/2                            */
    /*                                                            */
    /* Here ry = (Rtop  + Rbottom)/2                              */
    /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* rz = (Rtop_new + Rbottom_new)/2                            */
    /*                                                            */
    /* Performance: 4/16 * (1/2) * 2 = cycles + H/2 + (R, B)      */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_w/VCOP_2SIMD_WIDTH; I3++)
    {
        __vector VB0_lp3, VB1_lp3, VR0_lp3, VR1_lp3, Vb0, Vb1, Vr0, Vr1;
        __vector VR2, VR3, VB2, VB3;

        __agen Addr_toprow;

        Addr_toprow = I3 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT;

        (VB0_lp3, VB1_lp3) = B_short[Addr_toprow].deinterleave();
        (VR0_lp3, VR1_lp3) = R_short[Addr_toprow].deinterleave();

        for (int I4 = 0; I4 < blk_h/2; I4++)
        {
            __agen Addr;

            Addr  = I3 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I4 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VB2, VB3) = (B_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();
            (VR2, VR3) = (R_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();

            Vb0 = (VB0_lp3 + VB2);
            Vb1 = (VB1_lp3 + VB3);

            Vr0 = (VR0_lp3 + VR2);
            Vr1 = (VR1_lp3 + VR3);

            VB0_lp3 = VB2;          // Save bottom pixels as 'new' top pixel
            VB1_lp3 = VB3;          // Save bottom pixels as 'new' top pixel
            VR0_lp3 = VR2;          // Save bottom pixels as 'new' top pixel
            VR1_lp3 = VR3;          // Save bottom pixels as 'new' top pixel

            (B_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vb0, Vb1).truncate(1);
            (R_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vr0, Vr1).truncate(1);
        }
    }
}

void vcop_BayerCFA_interpolate_short_GBRG
(
    __vptr_uint16  CFA_short,
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    __vptr_uint16  R_short,
    __vptr_uint16  G_short,
    __vptr_uint16  B_short,
    unsigned int   out_stride
)
{
    __vector Vzero_a, Vzero_b;

    /*------------------------------------------------------------*/
    /* The Bayer pattern is as follows:                           */
    /* -------------------------------                            */
    /* G B G B G B G B                                           */
    /* R G R G R G R G                                           */
    /* G B G B G B G B                                           */
    /* R G R G R G R G                                           */
    /* G B G B G B G B                                           */
    /* R G R G R G R G                                           */
    /*                                                            */
    /* DEMOSAICing STEP                                           */
    /* First step is to copy the R, G and B pixels which exist to */
    /* the separate R, G and B planes keeping their locations     */
    /* the same as the input array. This means, there are holes   */
    /* in these planar arrays which will eventually be filled     */
    /* with the interpolated values.                              */
    /*                                                            */
    /* This step also does the interleave step for G plane by     */
    /* using the top and bottom pixels that are already read-in.  */
    /* This step takes and extra cycle as we need to make copies  */
    /* of some of the registers due to their odd/even numbering.  */
    /* Due to this, this loop takes 3 cycles to process 16 pixs.  */
    /*                                                            */
    /* Performance: 2/16 * (1/3) cyc/pix                          */
    /*------------------------------------------------------------*/

    Vzero_a =  0;
    Vzero_b =  0;

    for (int I3 = 0; I3 < ((blk_h/2) +1); I3++)
    {
        __vector VB0, VB0_copy, VR0, VR0_copy, VR1, VG0, VG1;

        for (int I4 = 0; I4 < ((blk_w/VCOP_2SIMD_WIDTH)+1); I4++)
        {
            __agen Addr_in, Addr_out;

            Addr_in  = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 *  in_w * ELEMSZ_IN_SHORT;
            Addr_out     = I4 * 2 * VECTORSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VG0, VB0) = CFA_short[Addr_in].deinterleave();  // ibufla
            (VR0, VG1) = (CFA_short + (in_w * ELEMSZ_IN_SHORT))[Addr_in].deinterleave(); // ibufla

            /*----------------------------------------------------*/
            /* Make copies to work atruncate the odd/even register*/
            /* usage issue. Even numbered registers cannot be the */
            /* first register in a register pair during store.    */
            /*----------------------------------------------------*/

            VB0_copy = VB0;
            VR0_copy = VR0;

            B_short[Addr_out].interleave()  = (VB0_copy, Vzero_a); // ibufha
            G_short[Addr_out].skip()  = VG0; // wbuf

            R_short[Addr_out].interleave() = (VR0_copy, Vzero_b);  // ibufha
            (G_short + (out_stride * ELEMSZ_IN_SHORT))[Addr_out].skip() = VG1; // wbuf
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 1 (Horizontal compute):                 */
    /* ------------------------------------------                 */
    /* Where bx = (Bleft + Bright)/2                              */
    /*                                                            */
    /* Where rx = (Rleft + Rright)/2                              */
    /*                                                            */
    /* Performance: (3/16) * 2 * (1/2) cyc/pix                    */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < ((blk_h/2)+1); I3++)
    {
        __vector VB0, VB1, VR0, VR1, Vrx, Vbx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * 2 * out_stride * ELEMSZ_IN_SHORT;

            VB0 = B_short[Addr].ds2();
            VB1 = (B_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            VR0 = R_short[Addr].ds2();
            VR1 = (R_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vbx = VB0 + VB1;
            Vrx = VR0 + VR1;

            (B_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vbx.truncate(1);
            (R_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vrx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Where gx = (Gleft + Gright)/2                              */
    /* performance: 3/8 cyc/pix                                   */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < (blk_h+1); I3++)
    {
        __vector VG0, VG1, Vgx;

        for (int I4 = 0; I4 < blk_w/VCOP_2SIMD_WIDTH; I4++)
        {
            __agen Addr;

            Addr  = I4 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I3 * out_stride * ELEMSZ_IN_SHORT;

            VG0 = G_short[Addr].ds2();
            VG1 = (G_short + (2 * ELEMSZ_IN_SHORT))[Addr].ds2();

            Vgx = VG0 + VG1;

            (G_short + ELEMSZ_IN_SHORT)[Addr].skip() = Vgx.truncate(1);
        }
    }

    /*------------------------------------------------------------*/
    /* Interpolation Step 2 (Vertical compute):                   */
    /* ------------------------------------------                 */
    /* Here by = (Btop  + Bbottom)/2                              */
    /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* bz = (Btop_new + Bbottom_new)/2                            */
    /*                                                            */
    /* Here ry = (Rtop  + Rbottom)/2                              */
    /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
    /* This can be also computed in a 2nd pass as:                */
    /* rz = (Rtop_new + Rbottom_new)/2                            */
    /*                                                            */
    /* Performance: 4/16 * (1/2) * 2 = cycles + H/2 + (R, B)      */
    /*------------------------------------------------------------*/

    for (int I3 = 0; I3 < blk_w/VCOP_2SIMD_WIDTH; I3++)
    {
        __vector VB0_lp3, VB1_lp3, VR0_lp3, VR1_lp3, Vb0, Vb1, Vr0, Vr1;
        __vector VR2, VR3, VB2, VB3;

        __agen Addr_toprow;

        Addr_toprow = I3 * 2 * VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT;

        (VB0_lp3, VB1_lp3) = B_short[Addr_toprow].deinterleave();
        (VR0_lp3, VR1_lp3) = R_short[Addr_toprow].deinterleave();

        for (int I4 = 0; I4 < blk_h/2; I4++)
        {
            __agen Addr;

            Addr  = I3 * 2 *  VCOP_SIMD_WIDTH * ELEMSZ_IN_SHORT + I4 * 2 * out_stride * ELEMSZ_IN_SHORT;

            (VB2, VB3) = (B_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();
            (VR2, VR3) = (R_short + (2 * out_stride * ELEMSZ_IN_SHORT))[Addr].deinterleave();

            Vb0 = (VB0_lp3 + VB2);
            Vb1 = (VB1_lp3 + VB3);

            Vr0 = (VR0_lp3 + VR2);
            Vr1 = (VR1_lp3 + VR3);

            VB0_lp3 = VB2;          // Save bottom pixels as 'new' top pixel
            VB1_lp3 = VB3;          // Save bottom pixels as 'new' top pixel
            VR0_lp3 = VR2;          // Save bottom pixels as 'new' top pixel
            VR1_lp3 = VR3;          // Save bottom pixels as 'new' top pixel

            (B_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vb0, Vb1).truncate(1);
            (R_short + ( out_stride * ELEMSZ_IN_SHORT))[Addr].interleave() = (Vr0, Vr1).truncate(1);
        }
    }
}
/* * * * * * * * * * * * * * * * * * * * */
