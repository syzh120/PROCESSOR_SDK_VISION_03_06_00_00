/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif



void vcop_fft_1024_32x16t_stage1_0
(
    __vptr_int32      Pin_xyL0_0123,
    __vptr_int32      Pin_xyL0_4567,
    __vptr_int32      Pin_xyL1_0123,
    __vptr_int32      Pin_xyL1_4567,
    __vptr_int32      Pin_xyL2_0123,
    __vptr_int32      Pin_xyL2_4567,
    __vptr_int32      Pin_xyL3_0123,
    __vptr_int32      Pin_xyL3_4567,
    __vptr_int32      Pou_xyL0_0123,
    __vptr_int32      Pou_xyL0_4567,
    __vptr_int32      Pou_xyL1_0123,
    __vptr_int32      Pou_xyL1_4567,
    __vptr_int32      Pou_xyL2_0123,
    __vptr_int32      Pou_xyL2_4567,
    __vptr_int32      Pou_xyL3_0123,
    __vptr_int32      Pou_xyL3_4567
)
{
    /*------------------------------------------------------------------------*/
    /* In the first stage of the FFT, for stage 1, we read points every 256   */
    /* complex points away. Here the primary obstacle is the inability to     */
    /* also load the twiddle factors, hence we break each stage into two      */
    /* seperate loops. The first loop does a radix-4 decomposition without    */
    /* the twiddle factor multiplies.                                         */
    /*------------------------------------------------------------------------*/

    for (int I3 = 0; I3 < 32; I3++)
    {
        /*--------------------------------------------------------------------*/
        /* We work on 8 radix-4 complex butterflies in parallel, so offset    */
        /* amount is 64 bytes, as we advance from one row to another.         */
        /*--------------------------------------------------------------------*/

         __agen  Addr_in  =  I3 * 64;

         __vector VXY_L0_0123;
         __vector VXY_L0_4567;
         __vector VXY_L1_0123;
         __vector VXY_L1_4567;
         __vector VXY_L2_0123;
         __vector VXY_L2_4567;
         __vector VXY_L3_0123;
         __vector VXY_L3_4567;

         __vector VY_L0_01234567, VX_L0_01234567;
         __vector VY_L1_01234567, VX_L1_01234567;
         __vector VY_L2_01234567, VX_L2_01234567;
         __vector VY_L3_01234567, VX_L3_01234567;

         __vector Vxh0,  Vxl0;
         __vector Vxh1,  Vxl1;
         __vector Vxh20, Vxl20;
         __vector Vxh21, Vxl21;

         __vector V_x0r, V_xt2;
         __vector V_xt1, V_xt3;
         __vector V_y0i, V_yt2;
         __vector V_yt3, V_yt1;

        /*--------------------------------------------------------------------*/
        /*  The base pointers for the four legs of the butterflies are        */
        /*  passed in from outside, seperated as 256 points apart.            */
        /*--------------------------------------------------------------------*/

         VXY_L0_0123 =  Pin_xyL0_0123[Addr_in];
         VXY_L0_4567 =  Pin_xyL0_4567[Addr_in];
         VXY_L1_0123 =  Pin_xyL1_0123[Addr_in];
         VXY_L1_4567 =  Pin_xyL1_4567[Addr_in];
         VXY_L2_0123 =  Pin_xyL2_0123[Addr_in];
         VXY_L2_4567 =  Pin_xyL2_4567[Addr_in];
         VXY_L3_0123 =  Pin_xyL3_0123[Addr_in];
         VXY_L3_4567 =  Pin_xyL3_4567[Addr_in];

         /*---------------------------------------------------------------------*/
         /* Apply a de-interleave step to bring all X's and Y's together.       */
         /*---------------------------------------------------------------------*/

         (VX_L0_01234567, VY_L0_01234567)  =  (VXY_L0_0123, VXY_L0_4567).deinterleave();
         (VX_L1_01234567, VY_L1_01234567)  =  (VXY_L1_0123, VXY_L1_4567).deinterleave();
         (VX_L2_01234567, VY_L2_01234567)  =  (VXY_L2_0123, VXY_L2_4567).deinterleave();
         (VX_L3_01234567, VY_L3_01234567)  =  (VXY_L3_0123, VXY_L3_4567).deinterleave();

         /*----------------------------------------------------------------------*/
         /* Mathematical equations for a radix-4 DIF style decomposition.        */
         /*                                                                      */
         /*  x_0 = x[0];                   x_1 = x[1];                           */
         /*  x_l1_0 = x[l1  ];             x_l1_1 = x[l1+1];                     */
         /*  x_l2_0 = x[l2  ];             x_l2_1 = x[l2+1];                     */
         /*  x_h2_0 = x[h2  ];             x_h2_1 = x[h2+1];                     */
         /*                                                                      */
         /*  xh0_0  = x_0    + x_l1_0;     xh1_0  = x_1    + x_l1_1;             */
         /*  xl0_0  = x_0    - x_l1_0;     xl1_0  = x_1    - x_l1_1;             */
         /*                                                                      */
         /*  xh20_0 = x_h2_0 + x_l2_0;     xh21_0 = x_h2_1 + x_l2_1;             */
         /*  xl20_0 = x_h2_0 - x_l2_0;     xl21_0 = x_h2_1 - x_l2_1;             */
         /*----------------------------------------------------------------------*/


         (Vxh0,  Vxl0)   = (VX_L0_01234567, VX_L2_01234567).addsub();
         (Vxh1,  Vxl1)   = (VY_L0_01234567, VY_L2_01234567).addsub();
         (Vxh20, Vxl20)  = (VX_L1_01234567, VX_L3_01234567).addsub();
         (Vxh21, Vxl21)  = (VY_L1_01234567, VY_L3_01234567).addsub();

         (V_x0r,  V_xt2) = (Vxh0, Vxh20).addsub();
         (V_xt1,  V_xt3) = (Vxl0, Vxl21).addsub();
         (V_y0i,  V_yt2) = (Vxh1, Vxh21).addsub();
         (V_yt3,  V_yt1) = (Vxl1, Vxl20).addsub();

         Pou_xyL0_0123[Addr_in]  =  V_x0r;
         Pou_xyL0_4567[Addr_in]  =  V_y0i;

         Pou_xyL1_0123[Addr_in]  =  V_xt1;
         Pou_xyL1_4567[Addr_in]  =  V_yt1;

         Pou_xyL2_0123[Addr_in]  =  V_xt2;
         Pou_xyL2_4567[Addr_in]  =  V_yt2;

         Pou_xyL3_0123[Addr_in]  =  V_xt3;
         Pou_xyL3_4567[Addr_in]  =  V_yt3;
   }
}


// Input array related
//


#define IN_JUMP      (256)
#define COMPL        (2)
#define I4_INC       (256)
#define I3_INC       (1)
#define IN_ELEMSZ    (sizeof (*out))                             //  4
#define IN_VECTORSZ  (COMPL * (VCOP_SIMD_WIDTH/2) * IN_ELEMSZ)   //  32
#define I4_IN_JUMP   (I4_INC  * COMPL * IN_ELEMSZ)                   // 256 * 2 * 4
#define I3_IN_JUMP   (I3_INC  * COMPL * VCOP_SIMD_WIDTH * IN_ELEMSZ) // 1   * 8 * 2 * 4

// Input array related.

#define  TW_ELEMSZ   (sizeof (*CS))
#define  I4_TW_INC   (1)
#define  I3_TW_INC   (3)
#define  TW_VECTORSZ (VCOP_SIMD_WIDTH   * TW_ELEMSZ)   // 16
#define  I4_TW_JUMP  (I4_TW_INC * COMPL * TW_VECTORSZ) // 2 * 16
#define  I3_TW_JUMP  (I3_TW_INC * COMPL * TW_VECTORSZ) // 3 * 2 * 16

void vcop_fft_1024_32x16t_stage1_1
(
    __vptr_uint16  inp1_l,
    __vptr_int16   inp1_h,
    __vptr_int16   CS,
    __vptr_int32   out
)
{
    /*--------------------------------------------------------------------------*/
    /* Process the 32 sets of 3-twiddle factors, which is why outer loop iter.  */
    /* 32 times, inner loop iterates 3 times. In the inner most loop, we        */
    /* perform a 16 x 32 multiply, with input being 32-bit and twiddle being    */
    /* 16-bit.                                                                  */
    /*--------------------------------------------------------------------------*/

    for (int I3 = 0; I3 < 32; I3++)
    {
        for (int I4 = 0; I4 < 3; I4++)
        {
            __vector   VA,     VB,     VC;
            __vector   VG,     VE,     VF;
            __vector   Vacc2,  Vacc4;
            __vector   Vacc6,  Vacc8;
            __vector   Vout0,  Vout1;

            __agen Addr_in    =   (I4 * I4_IN_JUMP + I3 * I3_IN_JUMP);
            __agen Addr_iw    =   (I4 * I4_TW_JUMP + I3 * I3_TW_JUMP);

            (VG,VC)    =   CS[Addr_iw].deinterleave(); //S01234567:C01234567

            VA         =   inp1_h[Addr_in].ds2();   // XYS0123
            VB         =   inp1_l[Addr_in].ds2();   // XYU0123

            VE         =   (inp1_h + IN_VECTORSZ)[Addr_in].ds2();  // XYS4567
            VF         =   (inp1_l + IN_VECTORSZ)[Addr_in].ds2();  // XYU4567

            /*-------------------------------------------------------------*/
            /* Initialize accumulators.                                    */
            /*-------------------------------------------------------------*/

            Vout0      =   0;
            Vout1      =   0;

            /*-------------------------------------------------------------*/
            /*  Regular sequence for doing a 16 x 32 multiply, being       */
            /*  formed from 16 x 16 multiplies.                            */
            /*                                                             */
            /*  Vacc2      =   (VB * VC).round(15);  // XU * C01234567     */
            /*  Vacc4      =   (VF * VG).round(15);  // YU * S01234567     */
            /*                                                             */
            /*  Vacc2     +=   (VA * VC) << 1;       // XS * C01234567     */
            /*  Vacc4     +=   (VE * VG) << 1;       // YS * S01234567     */
            /*                                                             */
            /*  Vacc6      =   (VB * VG).round(15);  // XU * S01234567     */
            /*  Vacc8      =   (VF * VC).round(15);  // YU * C01234567     */
            /*                                                             */
            /*  Vacc6     +=   (VA * VG) << 1;       // XS * S01234567     */
            /*  Vacc8     +=   (VE * VC) << 1;       // YS * C01234567     */
            /*                                                             */
            /*  Vout0      =    Vacc4 +  Vacc2;      // SY + XC            */
            /*  Vout1      =    Vacc8 -  Vacc6;      // CY - SX            */
            /*-------------------------------------------------------------*/

            Vout0     +=   (VB * VC).round(15);  // XU * C01234567
            Vout1     +=   (VF * VC).round(15);  // YU * C01234567

            Vout0     +=   (VF * VG).round(15);  // YU * S01234567
            Vout1     -=   (VB * VG).round(15);  // XU * S01234567

            Vout0     +=   (VA * VC) << 1;       // XS * C01234567
            Vout1     -=   (VA * VG) << 1;       // XS * S01234567

            Vout0     +=   (VE * VG) << 1;       // YS * S01234567
            Vout1     +=   (VE * VC) << 1;       // YS * C01234567

            (out)[Addr_in]                = Vout0;
            (out + IN_VECTORSZ)[Addr_in]  = Vout1;
       }
   }
}

/*------------------------------------------------------------------------*/
/* In Stage 2, we do 4 sets of 64-point FFT's, with the legs being        */
/* 64 complex points apart. The multiplication of the twiddle             */
/* factors is delayed to a seperate loop. Remmeber to scale by            */
/* complex * sizeof (data) ie 2 x 4 to get byte offsets.                  */
/*------------------------------------------------------------------------*/

#define CPLX          (2)
#define I3_S2_JMP     (256)
#define I4_STAGE2_JMP (VCOP_SIMD_WIDTH * CPLX * sizeof (*Pin_xyL0_0123)) // 64
#define I3_STAGE2_JMP (I3_S2_JMP       * CPLX * sizeof (*Pin_xyL0_0123)) // 256 * 8

void vcop_fft_1024_32x16t_stage2_0
(
    __vptr_int32      Pin_xyL0_0123,
    __vptr_int32      Pin_xyL0_4567,
    __vptr_int32      Pin_xyL1_0123,
    __vptr_int32      Pin_xyL1_4567,
    __vptr_int32      Pin_xyL2_0123,
    __vptr_int32      Pin_xyL2_4567,
    __vptr_int32      Pin_xyL3_0123,
    __vptr_int32      Pin_xyL3_4567,
    __vptr_int32      Pou_xyL0_0123,
    __vptr_int32      Pou_xyL0_4567,
    __vptr_int32      Pou_xyL1_0123,
    __vptr_int32      Pou_xyL1_4567,
    __vptr_int32      Pou_xyL2_0123,
    __vptr_int32      Pou_xyL2_4567,
    __vptr_int32      Pou_xyL3_0123,
    __vptr_int32      Pou_xyL3_4567
)
{
    for (int I3 = 0; I3 < 4;  I3++)
    {
        for (int I4 = 0; I4 < 8; I4++)
        {
             __agen  Addr_in  =  I4 * I4_STAGE2_JMP + I3 * I3_STAGE2_JMP;

             __vector VXY_L0_0123;
             __vector VXY_L0_4567;
             __vector VXY_L1_0123;
             __vector VXY_L1_4567;
             __vector VXY_L2_0123;
             __vector VXY_L2_4567;
             __vector VXY_L3_0123;
             __vector VXY_L3_4567;

             __vector VY_L0_01234567, VX_L0_01234567;
             __vector VY_L1_01234567, VX_L1_01234567;
             __vector VY_L2_01234567, VX_L2_01234567;
             __vector VY_L3_01234567, VX_L3_01234567;

             __vector Vxh0,  Vxl0;
             __vector Vxh1,  Vxl1;
             __vector Vxh20, Vxl20;
             __vector Vxh21, Vxl21;

             __vector V_x0r, V_xt2;
             __vector V_xt1, V_xt3;
             __vector V_y0i, V_yt2;
             __vector V_yt3, V_yt1;

             __vector OXY_L0_4567, OXY_L0_0123;
             __vector OXY_L1_4567, OXY_L1_0123;
             __vector OXY_L2_4567, OXY_L2_0123;
             __vector OXY_L3_4567, OXY_L3_0123;

             VX_L0_01234567 =  Pin_xyL0_0123[Addr_in];
             VY_L0_01234567 =  Pin_xyL0_4567[Addr_in];
             VX_L1_01234567 =  Pin_xyL1_0123[Addr_in];
             VY_L1_01234567 =  Pin_xyL1_4567[Addr_in];
             VX_L2_01234567 =  Pin_xyL2_0123[Addr_in];
             VY_L2_01234567 =  Pin_xyL2_4567[Addr_in];
             VX_L3_01234567 =  Pin_xyL3_0123[Addr_in];
             VY_L3_01234567 =  Pin_xyL3_4567[Addr_in];

             (Vxh0,  Vxl0)   = (VX_L0_01234567, VX_L2_01234567).addsub();
             (Vxh1,  Vxl1)   = (VY_L0_01234567, VY_L2_01234567).addsub();
             (Vxh20, Vxl20)  = (VX_L1_01234567, VX_L3_01234567).addsub();
             (Vxh21, Vxl21)  = (VY_L1_01234567, VY_L3_01234567).addsub();

             (V_x0r,  V_xt2) = (Vxh0, Vxh20).addsub();
             (V_xt1,  V_xt3) = (Vxl0, Vxl21).addsub();
             (V_y0i,  V_yt2) = (Vxh1, Vxh21).addsub();
             (V_yt3,  V_yt1) = (Vxl1, Vxl20).addsub();

             Pou_xyL0_0123[Addr_in]  =   V_x0r;
             Pou_xyL0_4567[Addr_in]  =   V_y0i;

             Pou_xyL1_0123[Addr_in]  =   V_xt1;
             Pou_xyL1_4567[Addr_in]  =   V_yt1;

             Pou_xyL2_0123[Addr_in]  =   V_xt2;
             Pou_xyL2_4567[Addr_in]  =   V_yt2;

             Pou_xyL3_0123[Addr_in]  =   V_xt3;
             Pou_xyL3_4567[Addr_in]  =   V_yt3;
       }
   }
}


/*------------------------------------------------------------------------*/
/* In the twiddle factor loop, innermost loop iterates 3 times, 8 such    */
/* sets followed by twiddle factor re-use, which is why I2_TW_INC2 is     */
/* 0.                                                                     */
/*------------------------------------------------------------------------*/


#define IN_JUMP2      (256)
#define COMPL2        (2)
#define I4_INC2       (64)
#define I3_INC2       (1)
#define I2_INC2       (256)
#define IN_ELEMSZ2    (sizeof (*out))                                    //  4
#define IN_VECTORSZ2  (COMPL2   * (VCOP_SIMD_WIDTH/2) * IN_ELEMSZ2)      //  32
#define I4_IN_JUMP2   (I4_INC2  * COMPL2 * IN_ELEMSZ2)                   //  64  * 2 * 4
#define I3_IN_JUMP2   (I3_INC2  * COMPL2 * VCOP_SIMD_WIDTH * IN_ELEMSZ2) //   1  * 8 * 2 * 4
#define I2_IN_JUMP2   (I2_INC2  * COMPL2 * IN_ELEMSZ2)                   //  256 * 2 * 4

// Twiddle array related.

#define  TW_ELEMSZ2   (sizeof (*CS))
#define  I4_TW_INC2   (1)
#define  I3_TW_INC2   (3)
#define  I2_TW_INC2   (0)

#define  TW_VECTORSZ2 (VCOP_SIMD_WIDTH     * TW_ELEMSZ2)  // 16
#define  I4_TW_JUMP2  (I4_TW_INC2 * COMPL2 * TW_VECTORSZ2) // 1 * 2 * 16
#define  I3_TW_JUMP2  (I3_TW_INC2 * COMPL2 * TW_VECTORSZ2) // 3 * 2 * 16
#define  I2_TW_JUMP2  (I2_TW_INC2 * COMPL2 * TW_VECTORSZ2) // 0 * 2 * 16


void vcop_fft_1024_32x16t_stage2_1
(
    __vptr_uint16  inp1_l,
    __vptr_int16   inp1_h,
    __vptr_int16   CS,
    __vptr_int32   out
)
{
    for (int I2 = 0; I2 < 4;  I2++)
    {
         __vector   VA,     VB,     VC;
         __vector   VG,     VE,     VF;
         __vector   Vacc2,  Vacc4;
         __vector   Vacc6,  Vacc8;
         __vector   Vout0,  Vout1;

        for (int I3 = 0; I3 < 8; I3++)
        {
            for (int I4 = 0; I4 < 3; I4++)
            {

                __agen Addr_in    =   (I4 * I4_IN_JUMP2 + I3 * I3_IN_JUMP2 + I2 * I2_IN_JUMP2);
                __agen Addr_iw    =   (I4 * I4_TW_JUMP2 + I3 * I3_TW_JUMP2 + I2 * I2_TW_JUMP2);

                (VG,VC)    =   CS[Addr_iw].deinterleave(); //S01234567:C01234567

                VA         =   inp1_h[Addr_in].ds2();   // XYS0123
                VB         =   inp1_l[Addr_in].ds2();   // XYU0123

                VE         =   (inp1_h + IN_VECTORSZ)[Addr_in].ds2();  // XYS4567
                VF         =   (inp1_l + IN_VECTORSZ)[Addr_in].ds2();  // XYU4567

                Vout0      =   0;
                Vout1      =   0;

                Vout0     +=   (VB * VC).round(15);  // XU * C01234567
                Vout1     +=   (VF * VC).round(15);  // YU * C01234567

                Vout0     +=   (VF * VG).round(15);  // YU * S01234567
                Vout1     -=   (VB * VG).round(15);  // XU * S01234567

                Vout0     +=   (VA * VC) << 1;       // XS * C01234567
                Vout1     -=   (VA * VG) << 1;       // XS * S01234567

                Vout0     +=   (VE * VG) << 1;       // YS * S01234567
                Vout1     +=   (VE * VC) << 1;       // YS * C01234567

                (out)[Addr_in]                = Vout0;
                (out + IN_VECTORSZ)[Addr_in]  = Vout1;
           }
       }
   }
}


/*------------------------------------------------------------------------*/
/* In Stage 3, we start to get ready to do digit reversal, by writing     */
/* the data out in a transposed fashion. We use the first half of the     */
/* array to store the X data, and second half to store out Y data.        */
/* This step hence needs to be done out of place.                         */
/*------------------------------------------------------------------------*/

#define COMPL_SZ      (2)
#define NUM_BANKS     (8)
#define IN_ELEM_SZ    (sizeof (*Pin_xyL0_0123))
#define I4_RD_IN_INCR (NUM_BANKS * COMPL_SZ * IN_ELEM_SZ)  // 64
#define I3_RD_IN_INCR (64        * COMPL_SZ * IN_ELEM_SZ)  // 512
#define I2_RD_IN_INCR (128       * COMPL_SZ * IN_ELEM_SZ)  // 1024
#define I1_RD_IN_INCR (256       * COMPL_SZ * IN_ELEM_SZ)  // 2048

#define BANK_SZ       (4)                                         // bank size in bytes
#define I4_WR_OU_INCR (NUM_BANKS * (NUM_BANKS + 1) * IN_ELEM_SZ)  // 8 * 9 * 4
#define I3_WR_OU_INCR (4         *  IN_ELEM_SZ)                   // 4 * 4
#define I2_WR_OU_INCR (64        * (NUM_BANKS + 1) * IN_ELEM_SZ)  // 64 * 9 * 4
#define I1_WR_OU_INCR (BANK_SZ)                                   // 4


void vcop_fft_1024_32x16t_stage3_0
(
    __vptr_int32      Pin_xyL0_0123,
    __vptr_int32      Pin_xyL0_4567,
    __vptr_int32      Pin_xyL1_0123,
    __vptr_int32      Pin_xyL1_4567,
    __vptr_int32      Pin_xyL2_0123,
    __vptr_int32      Pin_xyL2_4567,
    __vptr_int32      Pin_xyL3_0123,
    __vptr_int32      Pin_xyL3_4567,
    __vptr_int32      Pou_xyL0_0123,
    __vptr_int32      Pou_xyL0_4567,
    __vptr_int32      Pou_xyL1_0123,
    __vptr_int32      Pou_xyL1_4567,
    __vptr_int32      Pou_xyL2_0123,
    __vptr_int32      Pou_xyL2_4567,
    __vptr_int32      Pou_xyL3_0123,
    __vptr_int32      Pou_xyL3_4567
)
{
    for (int I1 = 0; I1 < 4;  I1++)
    {
        for (int I2 = 0; I2 < 2; I2++)
        {
            for (int I3 = 0; I3 < 2; I3++)
            {
                for (int I4 = 0; I4 < 2; I4++)
                {
                    __agen  Addr_in = I4 * I4_RD_IN_INCR + I3 * I3_RD_IN_INCR + I2 * I2_RD_IN_INCR + I1 * I1_RD_IN_INCR;
                    __agen  Addr_ou = I4 * I4_WR_OU_INCR + I3 * I3_WR_OU_INCR + I2 * I2_WR_OU_INCR + I1 * I1_WR_OU_INCR;

                   __vector VXY_L0_0123;
                   __vector VXY_L0_4567;
                   __vector VXY_L1_0123;
                   __vector VXY_L1_4567;
                   __vector VXY_L2_0123;
                   __vector VXY_L2_4567;
                   __vector VXY_L3_0123;
                   __vector VXY_L3_4567;

                   __vector VY_L0_01234567, VX_L0_01234567;
                   __vector VY_L1_01234567, VX_L1_01234567;
                   __vector VY_L2_01234567, VX_L2_01234567;
                   __vector VY_L3_01234567, VX_L3_01234567;

                   __vector Vxh0,  Vxl0;
                   __vector Vxh1,  Vxl1;
                   __vector Vxh20, Vxl20;
                   __vector Vxh21, Vxl21;

                   __vector V_x0r, V_xt2;
                   __vector V_xt1, V_xt3;
                   __vector V_y0i, V_yt2;
                   __vector V_yt3, V_yt1;

                   VX_L0_01234567 =  Pin_xyL0_0123[Addr_in];
                   VY_L0_01234567 =  Pin_xyL0_4567[Addr_in];
                   VX_L1_01234567 =  Pin_xyL1_0123[Addr_in];
                   VY_L1_01234567 =  Pin_xyL1_4567[Addr_in];
                   VX_L2_01234567 =  Pin_xyL2_0123[Addr_in];
                   VY_L2_01234567 =  Pin_xyL2_4567[Addr_in];
                   VX_L3_01234567 =  Pin_xyL3_0123[Addr_in];
                   VY_L3_01234567 =  Pin_xyL3_4567[Addr_in];

                   (Vxh0,  Vxl0)   = (VX_L0_01234567, VX_L2_01234567).addsub();
                   (Vxh1,  Vxl1)   = (VY_L0_01234567, VY_L2_01234567).addsub();
                   (Vxh20, Vxl20)  = (VX_L1_01234567, VX_L3_01234567).addsub();
                   (Vxh21, Vxl21)  = (VY_L1_01234567, VY_L3_01234567).addsub();

                   (V_x0r,  V_xt2) = (Vxh0, Vxh20).addsub();
                   (V_xt1,  V_xt3) = (Vxl0, Vxl21).addsub();
                   (V_y0i,  V_yt2) = (Vxh1, Vxh21).addsub();
                   (V_yt3,  V_yt1) = (Vxl1, Vxl20).addsub();

                   Pou_xyL0_0123[Addr_ou].offset_np1()  =   V_x0r;
                   Pou_xyL0_4567[Addr_ou].offset_np1()  =   V_y0i;

                   Pou_xyL1_0123[Addr_ou].offset_np1()  =   V_xt1;
                   Pou_xyL1_4567[Addr_ou].offset_np1()  =   V_yt1;

                   Pou_xyL2_0123[Addr_ou].offset_np1()  =   V_xt2;
                   Pou_xyL2_4567[Addr_ou].offset_np1()  =   V_yt2;

                   Pou_xyL3_0123[Addr_ou].offset_np1()  =   V_xt3;
                   Pou_xyL3_4567[Addr_ou].offset_np1()  =   V_yt3;
                }
            }
       }
   }
}

/*------------------------------------------------------------------------*/
/* In the twiddle factor loop, we first process successive inputs, re-    */
/* using twiddle factors by doing a one-pt load, for the next level of    */
/* loop we have to jump by 16 rows each of 36 bytes, followed by 8        */
/* rows of 9*4, followed by 64 rows of 9*4, to complete the bottom        */
/* half as data is organized as follows:                                  */
/*                                                                        */
/* 0x0 0x100 0x200 0x300 0x40 0x140 0x240 0x340                           */
/* 0x1 0x101..............................0x341                           */
/* ..                                                                     */
/* 0x7....................................0x347                           */
/* 0x8....................................0x348                           */
/* 0x10...................................0x350                           */
/* ...                                                                    */
/* 0x18...................................0x358                           */
/* 0x20...................................0x360                           */
/* ...                                                                    */
/* 0x30...................................0x370                           */
/* ...                                                                    */
/* 0x3F...................................0x37F                           */
/* 0x7F...................................0x3BF                           */
/* ...                                                                    */
/* 0xFF 0x1FF.............................0x43F                           */
/*------------------------------------------------------------------------*/

#define IN_JUMP3      (256)
#define I4_INC3       (1)                                        // 1  row of 9 words
#define I3_INC3       (2 * VCOP_SIMD_WIDTH)                      // 16 rows of 9 words
#define I2_INC3       (VCOP_SIMD_WIDTH)                          // 4  words
#define I1_INC3       (64)                                       // 64
#define IN_ELEMSZ3    (sizeof (*out_x))                          //  4
#define IN_VECTORSZ3  ((VCOP_SIMD_WIDTH + 1) * IN_ELEMSZ3)       //  36

#define I4_IN_JUMP3   (I4_INC3  *  IN_VECTORSZ3)                 //   1 *  9  *  4
#define I3_IN_JUMP3   (I3_INC3  *  IN_VECTORSZ3)                 //  16 *  9  *  4
#define I2_IN_JUMP3   (I2_INC3  *  IN_VECTORSZ3)                 //  8  *  9  *  4
#define I1_IN_JUMP3   (I1_INC3  *  IN_VECTORSZ3)                 //  64 *  9  *  4

// Input array related.

#define  TW_ELEMSZ3   (sizeof (*C))
#define  COMPL3       (2)
#define  I4_TW_INC3   (1)
#define  I3_TW_INC3   (8)
#define  I2_TW_INC3   (24)
#define  I1_TW_INC3   (0)

#define  TW_VECTORSZ3 (VCOP_SIMD_WIDTH     * TW_ELEMSZ3)  // 16
#define  I4_TW_JUMP3  (I4_TW_INC3 * COMPL3 * TW_ELEMSZ3) // 1  * 2 *  2
#define  I3_TW_JUMP3  (I3_TW_INC3 * COMPL3 * TW_ELEMSZ3) // 8  * 2 *  2
#define  I2_TW_JUMP3  (I2_TW_INC3 * COMPL3 * TW_ELEMSZ3) // 24 * 2 *  2
#define  I1_TW_JUMP3  (I1_TW_INC3 * COMPL3 * TW_ELEMSZ3) // 0

#define OU_ELEMSZ3  (sizeof (*out_x))
#define OU_VECSZ3   (VCOP_SIMD_WIDTH * OU_ELEMSZ3)
#define I4_OU_JUMP3 ((VCOP_SIMD_WIDTH + 1) * OU_ELEMSZ3)                            // 36
#define I3_OU_JUMP3 (( 2 * VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1)) * OU_ELEMSZ3)   // 576
#define I2_OU_JUMP3 (( VCOP_SIMD_WIDTH     * (VCOP_SIMD_WIDTH + 1)) * OU_ELEMSZ3)   // 288
#define I1_OU_JUMP3 (( 64                  * (VCOP_SIMD_WIDTH + 1)) * OU_ELEMSZ3)   // 2304

void vcop_fft_1024_32x16t_stage3_1
(
    __vptr_uint16  inp1_lx,
    __vptr_int16   inp1_hx,
    __vptr_uint16  inp1_ly,
    __vptr_int16   inp1_hy,
    __vptr_int16   C,
    __vptr_int16   S,
    __vptr_int32   out_x,
    __vptr_int32   out_y
)
{
     __vector   VA,     VB,     VC;
     __vector   VG,     VE,     VF;
     __vector   Vacc2,  Vacc4;
     __vector   Vacc6,  Vacc8;
     __vector   Vout0,  Vout1;

    for (int I1 = 0; I1 < 2; I1++)
    {
        for (int I2 = 0; I2 < 2;  I2++)
        {
            for (int I3 = 0; I3 < 3; I3++)
            {
                for (int I4 = 0; I4 < 8; I4++)
                {
                    __agen Addr_in    =   (I4 * I4_IN_JUMP3 + I3 * I3_IN_JUMP3 + I2 * I2_IN_JUMP3 + I1 * I1_IN_JUMP3);
                    __agen Addr_tw    =   (I4 * I4_TW_JUMP3 + I3 * I3_TW_JUMP3 + I2 * I2_TW_JUMP3 + I1 * I1_TW_JUMP3);
                    __agen Addr_ou    =   (I4 * I4_OU_JUMP3 + I3 * I3_OU_JUMP3 + I2 * I2_OU_JUMP3 + I1 * I1_OU_JUMP3);

                    VC         =   C[Addr_tw].onept();        //C01234567
                    VG         =   S[Addr_tw].onept();        //S01234567

                    VA         =   inp1_hx[Addr_in].ds2();   // XS01234567
                    VB         =   inp1_lx[Addr_in].ds2();   // XU01234567

                    VE         =   inp1_hy[Addr_in].ds2();  // YS01234567
                    VF         =   inp1_ly[Addr_in].ds2();  // YU01234567

                    Vout0      =   0;
                    Vout1      =   0;

                    Vout0     +=   (VB * VC).round(15);  // XU * C01234567
                    Vout1     +=   (VF * VC).round(15);  // YU * C01234567

                    Vout0     +=   (VF * VG).round(15);  // YU * S01234567
                    Vout1     -=   (VB * VG).round(15);  // XU * S01234567

                    Vout0     +=   (VA * VC) << 1;       // XS * C01234567
                    Vout1     -=   (VA * VG) << 1;       // XS * S01234567

                    Vout0     +=   (VE * VG) << 1;       // YS * S01234567
                    Vout1     +=   (VE * VC) << 1;       // YS * C01234567

                    (out_x)[Addr_in]  = Vout0;
                    (out_y)[Addr_in]  = Vout1;
               }
           }
       }
   }
}

/*------------------------------------------------------------------------*/
/* Stage 4 does a decomposition of radix-4 butterflies evry 4-points      */
/* apart. Had we not transposed the FFT, these would have fallen into     */
/* the same word. This allows us to perform these calculations as usual.  */
/* Note rows are 36 bytes apart due to transposition.                     */
/*------------------------------------------------------------------------*/

#define COMPL_SZ4      (2)
#define NUM_BANKS4     (8)
#define IN_ELEM_SZ4    (sizeof (*Pin_xL0_01234567))
#define I4_RD_IN_INCR4 ((NUM_BANKS + 1) * IN_ELEM_SZ4)       //  9 * 4
#define I3_RD_IN_INCR4 (16 * (NUM_BANKS + 1) * IN_ELEM_SZ4)  // 16 * 9 * 4


void vcop_fft_1024_32x16t_stage4_0
(
    __vptr_int32      Pin_xL0_01234567,
    __vptr_int32      Pin_yL0_01234567,
    __vptr_int32      Pin_xL1_01234567,
    __vptr_int32      Pin_yL1_01234567,
    __vptr_int32      Pin_xL2_01234567,
    __vptr_int32      Pin_yL2_01234567,
    __vptr_int32      Pin_xL3_01234567,
    __vptr_int32      Pin_yL3_01234567,
    __vptr_int32      Pou_xL0_01234567,
    __vptr_int32      Pou_yL0_01234567,
    __vptr_int32      Pou_xL1_01234567,
    __vptr_int32      Pou_yL1_01234567,
    __vptr_int32      Pou_xL2_01234567,
    __vptr_int32      Pou_yL2_01234567,
    __vptr_int32      Pou_xL3_01234567,
    __vptr_int32      Pou_yL3_01234567
)
{
     for (int I3 = 0; I3 < 8; I3++)
     {
            for (int I4 = 0; I4 < 4; I4++)
            {
                    __agen  Addr_in = I4 * I4_RD_IN_INCR4 + I3 * I3_RD_IN_INCR4;

                   __vector VX_L0_01234567;
                   __vector VY_L0_01234567;
                   __vector VX_L1_01234567;
                   __vector VY_L1_01234567;
                   __vector VX_L2_01234567;
                   __vector VY_L2_01234567;
                   __vector VX_L3_01234567;
                   __vector VY_L3_01234567;

                   __vector Vxh0,  Vxl0;
                   __vector Vxh1,  Vxl1;
                   __vector Vxh20, Vxl20;
                   __vector Vxh21, Vxl21;

                   __vector V_x0r, V_xt2;
                   __vector V_xt1, V_xt3;
                   __vector V_y0i, V_yt2;
                   __vector V_yt3, V_yt1;

                   VX_L0_01234567 =  Pin_xL0_01234567[Addr_in];
                   VX_L1_01234567 =  Pin_xL1_01234567[Addr_in];
                   VX_L2_01234567 =  Pin_xL2_01234567[Addr_in];
                   VX_L3_01234567 =  Pin_xL3_01234567[Addr_in];

                   VY_L0_01234567 =  Pin_yL0_01234567[Addr_in];
                   VY_L1_01234567 =  Pin_yL1_01234567[Addr_in];
                   VY_L2_01234567 =  Pin_yL2_01234567[Addr_in];
                   VY_L3_01234567 =  Pin_yL3_01234567[Addr_in];

                   (Vxh0,  Vxl0)   = (VX_L0_01234567, VX_L2_01234567).addsub();
                   (Vxh1,  Vxl1)   = (VY_L0_01234567, VY_L2_01234567).addsub();
                   (Vxh20, Vxl20)  = (VX_L1_01234567, VX_L3_01234567).addsub();
                   (Vxh21, Vxl21)  = (VY_L1_01234567, VY_L3_01234567).addsub();

                   (V_x0r,  V_xt2) = (Vxh0, Vxh20).addsub();
                   (V_xt1,  V_xt3) = (Vxl0, Vxl21).addsub();
                   (V_y0i,  V_yt2) = (Vxh1, Vxh21).addsub();
                   (V_yt3,  V_yt1) = (Vxl1, Vxl20).addsub();

                   Pou_xL0_01234567[Addr_in] =   V_x0r;
                   Pou_yL0_01234567[Addr_in] =   V_y0i;

                   Pou_xL1_01234567[Addr_in] =   V_xt1;
                   Pou_yL1_01234567[Addr_in] =   V_yt1;

                   Pou_xL2_01234567[Addr_in] =   V_xt2;
                   Pou_yL2_01234567[Addr_in] =   V_yt2;

                   Pou_xL3_01234567[Addr_in] =   V_xt3;
                   Pou_yL3_01234567[Addr_in] =   V_yt3;
        }
    }
}





#define I4_INC4       (4)                                        // 4  rows of 9 words
#define I3_INC4       (1)                                        // 1  rows of 9 words
#define I2_INC4       (16)                                       // 64 rows of 9 words
#define IN_ELEMSZ4    (sizeof (*out_x))                          //  4
#define IN_VECTORSZ4  ((VCOP_SIMD_WIDTH + 1) * IN_ELEMSZ3)       //  36

#define I4_IN_JUMP4   (I4_INC4  *  IN_VECTORSZ4)                 //   4 *  9  *  4
#define I3_IN_JUMP4   (I3_INC4  *  IN_VECTORSZ4)                 //  16 *  9  *  4
#define I2_IN_JUMP4   (I2_INC4  *  IN_VECTORSZ4)                 //  64 *  9  *  4

// Input array related.
//

/*------------------------------------------------------------------------*/
/* Re-use 4 sets of 3 twiddle factors, placed consecutively, which is     */
/* why I2_TW_JUMP4 is 0. Remember to jump by 64 rows to get to bottom     */
/* half of input array.                                                   */
/*------------------------------------------------------------------------*/

#define  TW_ELEMSZ4   (sizeof (*CS))
#define  COMPL4       (2)
#define  I4_TW_INC4   (1)
#define  I3_TW_INC4   (3)
#define  I2_TW_INC4   (0)

#define  TW_VECTORSZ4 (VCOP_SIMD_WIDTH  * COMPL * TW_ELEMSZ4)     // 32
#define  I4_TW_JUMP4  (I4_TW_INC4 * TW_VECTORSZ4)                 // 32
#define  I3_TW_JUMP4  (I3_TW_INC4 * TW_VECTORSZ4)                 // 96
#define  I2_TW_JUMP4  (I2_TW_INC4 * TW_VECTORSZ4)                 // 0

#define OU_ELEMSZ4  (sizeof (*out_x))
#define OU_VECSZ4   ((VCOP_SIMD_WIDTH + 1) * OU_ELEMSZ4)
#define I4_OU_JUMP4 ( (4 * (VCOP_SIMD_WIDTH + 1)) * OU_ELEMSZ4)   // 144
#define I3_OU_JUMP4 (( 2 * VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1)) * OU_ELEMSZ4)   // 576
#define I2_OU_JUMP4 (( 8 * VCOP_SIMD_WIDTH * (VCOP_SIMD_WIDTH + 1)) * OU_ELEMSZ4)   // 1152

void vcop_fft_1024_32x16t_stage4_1
(
    __vptr_uint16  inp1_lx,
    __vptr_int16   inp1_hx,
    __vptr_uint16  inp1_ly,
    __vptr_int16   inp1_hy,
    __vptr_int16   CS,
    __vptr_int32   out_x,
    __vptr_int32   out_y
)
{
     __vector   VA,     VB,     VC;
     __vector   VG,     VE,     VF;
     __vector   Vacc2,  Vacc4;
     __vector   Vacc6,  Vacc8;
     __vector   Vout0,  Vout1;


      for (int I2 = 0; I2 < 8; I2++)
      {
          for (int I3 = 0; I3 < 4; I3++)
          {
              for (int I4 = 0; I4 < 3; I4++)
              {
                  __agen Addr_in    =   (I4 * I4_IN_JUMP4 + I3 * I3_IN_JUMP4 + I2 * I2_IN_JUMP4);
                  __agen Addr_tw    =   (I4 * I4_TW_JUMP4 + I3 * I3_TW_JUMP4 + I2 * I2_TW_JUMP4);
                  __agen Addr_ou    =   (I4 * I4_OU_JUMP4 + I3 * I3_OU_JUMP4 + I2 * I2_OU_JUMP4);

                  (VG,VC)    =   CS[Addr_tw].deinterleave(); //S01234567:C01234567

                  VA         =   inp1_hx[Addr_in].ds2();   // XS01234567
                  VB         =   inp1_lx[Addr_in].ds2();   // XU01234567

                  VE         =   inp1_hy[Addr_in].ds2();  // YS01234567
                  VF         =   inp1_ly[Addr_in].ds2();  // YU01234567

                  Vout0      =   0;
                  Vout1      =   0;

                  Vout0     +=   (VB * VC).round(15);  // XU * C01234567
                  Vout1     +=   (VF * VC).round(15);  // YU * C01234567

                  Vout0     +=   (VF * VG).round(15);  // YU * S01234567
                  Vout1     -=   (VB * VG).round(15);  // XU * S01234567

                  Vout0     +=   (VA * VC) << 1;       // XS * C01234567
                  Vout1     -=   (VA * VG) << 1;       // XS * S01234567

                  Vout0     +=   (VE * VG) << 1;       // YS * S01234567
                  Vout1     +=   (VE * VC) << 1;       // YS * C01234567

                 (out_x)[Addr_in]  = Vout0;
                 (out_y)[Addr_in]  = Vout1;
           }
       }
   }
}

/*------------------------------------------------------------------------*/
/* In Stage 5, we do not have any twiddle factor multiplies, except for   */
/* redundant multiplies with +j and -j, so we factor this into the grp.   */
/* of registers we pair up in addsub() instruction. Since we are storing  */
/* them out seperately as words, and this is the final stage we take      */
/* additional cycles to interleave, and then store them back. We remove   */
/* the 9/8 geometry due to tranpsoition and do digit reversal within the  */
/* sub-group, as 1 goes to 0x100, 2 goes to 0x200, and so on.             */
/*------------------------------------------------------------------------*/

void vcop_fft_1024_32x16t_stage5
(
    __vptr_int32      Pxi0,
    __vptr_int32      Pyi0,
    __vptr_int32      Pxi1,
    __vptr_int32      Pyi1,
    __vptr_int32      Pxi2,
    __vptr_int32      Pyi2,
    __vptr_int32      Pxi3,
    __vptr_int32      Pyi3,
    __vptr_int32      Pox0,
    __vptr_int32      Poy0,
    __vptr_int32      Pox1,
    __vptr_int32      Poy1,
    __vptr_int32      Pox2,
    __vptr_int32      Poy2,
    __vptr_int32      Pox3,
    __vptr_int32      Poy3
)
{
   for (int I2 = 0; I2 < 2;  I2++)
   {
       for (int I3 = 0; I3 < 4; I3++)
       {
           for (int I4 = 0; I4 < 4; I4++)
           {
               __vector   VnX0_76543210;
               __vector   VnY0_76543210;
               __vector   VnX1_76543210;
               __vector   VnY1_76543210;
               __vector   VnX2_76543210;
               __vector   VnY2_76543210;
               __vector   VnX3_76543210;
               __vector   VnY3_76543210;

               __vector   Vxh0_0, Vxl0_0;
               __vector   Vxh1_0, Vxl1_0;
               __vector   Vxh0_1, Vxl0_1;
               __vector   Vxh1_1, Vxl1_1;

               __vector   V_n00,  V_n20;
               __vector   V_n10,  V_n30;
               __vector   V_n01,  V_n21;
               __vector   V_n31,  V_n11;

               __agen  Addr_in = I4 * 144 + I3 * 144 * 4  + I2 * 144 * 16;
               __agen  Addr_ou = I4 * 512 + I3 * 128      + I2 * 64;

               /*--------------------------------------------------------------*/
               /*  x_0    = x[0];       x_1 = x[1];                            */
               /*  x_2    = x[2];       x_3 = x[3];                            */
               /*  x_h2_0 = x[h2  ];    x_h2_1 = x[h2+1];                      */
               /*  x_h2_2 = x[h2+2];    x_h2_3 = x[h2+3];                      */
               /*  x_l1_0 = x[l1  ];    x_l1_1 = x[l1+1];                      */
               /*  x_l1_2 = x[l1+2];    x_l1_3 = x[l1+3];                      */
               /*  x_l2_0 = x[l2  ];    x_l2_1 = x[l2+1];                      */
               /*  x_l2_2 = x[l2+2];    x_l2_3 = x[l2+3];                      */
               /*--------------------------------------------------------------*/

               VnX0_76543210 =  Pxi0[Addr_in];
               VnY0_76543210 =  Pyi0[Addr_in];
               VnX1_76543210 =  Pxi1[Addr_in];
               VnY1_76543210 =  Pyi1[Addr_in];
               VnX2_76543210 =  Pxi2[Addr_in];
               VnY2_76543210 =  Pyi2[Addr_in];
               VnX3_76543210 =  Pxi3[Addr_in];
               VnY3_76543210 =  Pyi3[Addr_in];

               /*-------------------------------------------------------------*/
               /*  y0r = x0r + x2r +  x1r +  x3r    =  xh0 + xh20             */
               /*  y0i = x0i + x2i +  x1i +  x3i    =  xh1 + xh21             */
               /*  y1r = x0r - x2r + (x1i -  x3i)   =  xl0 + xl21             */
               /*  y1i = x0i - x2i - (x1r -  x3r)   =  xl1 - xl20             */
               /*  y2r = x0r + x2r - (x1r +  x3r)   =  xh0 - xh20             */
               /*  y2i = x0i + x2i - (x1i +  x3i    =  xh1 - xh21             */
               /*  y3r = x0r - x2r - (x1i -  x3i)   =  xl0 - xl21             */
               /*  y3i = x0i - x2i + (x1r -  x3r)   =  xl1 + xl20             */
               /*                                                             */
               /*  xh0  = x0r   +   x2r;   xl0  = x0r   -   x2r;              */
               /*  xh1  = x0i   +   x2i;   xl1  = x0i   -   x2i;              */
               /*  xh20 = x1r   +   x3r;   xl20 = x1r   -   x3r;              */
               /*  xh21 = x1i   +   x3i;   xl21 = x1i   -   x3i;              */
               /*                                                             */
               /* ------------------------------------------------------------*/

               (Vxh0_0, Vxl0_0)  =  (VnX0_76543210, VnX2_76543210).addsub();
               (Vxh1_0, Vxl1_0)  =  (VnY0_76543210, VnY2_76543210).addsub();

               (Vxh0_1, Vxl0_1)  =  (VnX1_76543210, VnX3_76543210).addsub();
               (Vxh1_1, Vxl1_1)  =  (VnY1_76543210, VnY3_76543210).addsub();

               /*----------------------------------------------------------------*/
               /*  n00 = xh0_0 + xh0_1;       n01 = xh1_0 + xh1_1;               */
               /*  n10 = xl0_0 + xl1_1;       n11 = xl1_0 - xl0_1;               */
               /*  n20 = xh0_0 - xh0_1;       n21 = xh1_0 - xh1_1;               */
               /*  n30 = xl0_0 - xl1_1;       n31 = xl1_0 + xl0_1;               */
               /*                                                                */
               /*----------------------------------------------------------------*/

               (V_n00, V_n20) =  (Vxh0_0,  Vxh0_1).addsub();
               (V_n10, V_n30) =  (Vxl0_0,  Vxl1_1).addsub();

               (V_n01, V_n21) =  (Vxh1_0,  Vxh1_1).addsub();
               (V_n31, V_n11) =  (Vxl1_0,  Vxl0_1).addsub();

               /*----------------------------------------------------------------*/
               /* y0[2*h2] = n00;           y0[2*h2 + 1] = n01;                  */
               /* y1[2*h2] = n10;           y1[2*h2 + 1] = n31;                  */
               /* y2[2*h2] = n20;           y2[2*h2 + 1] = n21;                  */
               /* y3[2*h2] = n11;           y3[2*h2 + 1] = n30;                  */
               /*----------------------------------------------------------------*/

               (V_n00,  V_n01).interleave();
               (V_n10,  V_n11).interleave();
               (V_n20,  V_n21).interleave();
               (V_n30,  V_n31).interleave();

               Pox0[Addr_ou]  =  V_n00;
               Poy0[Addr_ou]  =  V_n01;
               Pox1[Addr_ou]  =  V_n10;
               Poy1[Addr_ou]  =  V_n11;
               Pox2[Addr_ou]  =  V_n20;
               Poy2[Addr_ou]  =  V_n21;
               Pox3[Addr_ou]  =  V_n30;
               Poy3[Addr_ou]  =  V_n31;
           }
       }
   }
}

/*----------------------------------------------------------------------------------*/
/*  End of file: vcop_fft_1024_32x16t_kernel.k                                      */
/*==================================================================================*/
/*  Texas Instruments Incorporated: 2012-2016.                                      */
/*----------------------------------------------------------------------------------*/

