/*
*
* Copyright (c) 2007-2017 Texas Instruments Incorporated
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

/*                                                                            */
/* NAME: vcop_compute_rBrief                                                  */
/*                                                                            */
/* AUTHOR: Shashank Dabral (shashank@ti.com)                                  */
/* Modified by: Prashanth R V (p-viswanath@ti.com                             */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "vcop_compute_rBrief" takes an input array and                */
/* computes the brief descriptor for a 48x48 patch around a featuer           */
/* The function has the following prototype:                                  */
/*                                                                            */
/*  __vptr_int8    moments_col_mask,       // Mask for Moment calculation     */
/*  __vptr_int16   moments_col_sum,        // Ptr for storing sum of cols     */
/*  __vptr_uint8   moments_row_mask,       // Ptr to tranposed moment mask    */
/*  __vptr_int16   moments_row_sum,        // ptr for storing sum of rows     */
/*  __vptr_int16   moments_m10,            // Ptr for storing m10 (x moment)  */
/*  __vptr_int16   moments_m01,            // Ptr for storing m01 (y moment)  */
/*  __vptr_uint16  arctan_xthr,            // Threshold to multiply with m10  */
/*  __vptr_uint8   arctan_pack_decision,   // Bin decision for y>(x *hr)      */
/*  __vptr_int16   cos_array_ptr,          // Ptr to cos matrix               */
/*  __vptr_int16   sin_array_ptr,          // Ptr to sin matrix               */
/*  __vptr_uint16  offset_ptr,   // Offset ptr for transpose of i/p 48x48 blk */
/*  __vptr_int16   cos_ptr,          // Ptr to selected cos angle (wedge)     */
/*  __vptr_int16   sin_ptr,          // Ptr to selected sin angle (wedge)     */
/*  __vptr_uint8  input_image_ptr,   // Ptr to input block (Points to start   */
/*                                   // of of the block of 53x48              */
/*                                   // which includes 5x48 zero pad          */
/*  __vptr_int16 col_sum_ptr,         // Ptr for storing column sums          */
/*                                    // Points to zero pad regions for cols  */
/*  __vptr_int16 row_col_sum_ct_ptr,  // Ptr to Row/Col sums (5x5 sum)        */
/*  __vptr_int8  in_src_dst_x_ptr,   // X co-od of 0 deg src-dst mat (256x2)  */
/*  __vptr_int8  in_src_dst_y_ptr,   // Y co-od of 0 deg src-dst mat (256x2)  */
/*  __vptr_int8  rot_src_dst_ptr_x,   // X co-od of Rotated src matrix (256)  */
/*  __vptr_int8  rot_src_dst_ptr_y,   // Y co-od of Rotated src matrix (256)  */
/*  __vptr_uint16  rot_src_lin_ptr,   // Linearized  rotated src matrix (256) */
/*  __vptr_uint16  rot_dst_lin_ptr,   // Linearized  rotated dst matrix (256) */
/*  __vptr_int16  tlu_src_ptr,        // src 5x5 sum (256 selected)           */
/*  __vptr_int16  tlu_dst_ptr,        // dst 5x5 sum (256 seelcted)           */
/*  __vptr_uint8  true_descriptor_optr // Brief Descriptor (Output)           */
/*                                                                            */
/*                                                                            */
/* ASSUMPTIONS:                                                               */
/*                                                                            */
/* This function expects all buffers to be 32 byte aligned.                   */
/* The patch size aorund a feature is expected to be 48x48 and it is verified */
/* for a patch size of 48 only.                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2014.                                  */
/*============================================================================*/

/* ------------------------------------------------------------- */
/* Source image dimensions                                       */
/* ------------------------------------------------------------- */
// The minimum size of patch can be calculated as (sqrt(2) * 13)*2 +1
// This provides a patch of 39x39. We need a border of 2 in each of the
// four edges, so a patch of 43x43 is the Minimum requirement.
// The patch is extended to 48x48 to make it a multiple of 8, though true
// patch size is 47x47 (Since patch size needs to be odd).
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define MOMENTS_PATCH_SIZE (32)
#define MOMENTS_OFFSET     (MOMENTS_PATCH_SIZE  + 4)
// Offset should ensure that the next entry is in a different bank

#define PATCH_SIZE (48)
#define PATCH_SIZE_P2 (PATCH_SIZE + 2)
#define STRIDE PATCH_SIZE


#define INELEMSZ            sizeof(*input_image_ptr)
#define INVECTORSZ        (VCOP_SIMD_WIDTH*INELEMSZ)

#define OUTELEMSZ          sizeof(*col_sum_ptr)
#define OUTVECTORSZ        (VCOP_SIMD_WIDTH*OUTELEMSZ)

#define RND_BITS             14
#define MOMENTS_RND_BITS     4
#define MOMENTS_RND_BITS_2   3
#define ARCTAN_RND_BITS      8
// Thresholds are U4Q12

#define NUM_TBLS (2)
#define NUM_PTS_TLU (1)
#define NUM_TBLS_1 (1)


void vcop_compute_rBrief
(
        __vptr_int8    moments_col_mask,         // Mask for Moment calculation
        __vptr_int16   moments_col_sum,          // Ptr for storing sum of cols
        __vptr_int8    moments_row_mask,         // Ptr to tranposed moment mask
        __vptr_int16   moments_row_sum,          // ptr for storing sum of rows
        __vptr_int16   moments_m10,              // Ptr for storing m10 (x moment)
        __vptr_int16   moments_m01,              // Ptr for storing m01 (y moment)
        __vptr_uint16  arctan_xthr,              // Threshold to multiply with m10
        __vptr_uint8   arctan_pack_decision,     // Bin decision for y>(x *hr)
        __vptr_int16   cos_array_ptr,            // Ptr to cos matrix
        __vptr_int16   sin_array_ptr,            // Ptr to sin matrix
        __vptr_uint16  offset_ptr,               // Ptr containing offsets (Increments of 34)
        __vptr_int16   cos_ptr,                  // Ptr to selected cos angle
        __vptr_int16   sin_ptr,                  // Ptr to selected sin angle
        __vptr_uint8  input_image_ptr,           // input 1 data pointer
        __vptr_int16 col_sum_ptr,                // Ptr for column sums
        __vptr_int16 row_col_sum_ct_ptr,         // Centre of row_col_sum for tlu
        __vptr_int8  in_src_dst_x_ptr,           // input 0 degree  src-dst mat (256 pairs)
        __vptr_int8  in_src_dst_y_ptr,           // input 0 degree  src-dst mat (256 pairs)
        __vptr_int8  rot_src_dst_ptr_x,          // Rotated src-dst matrix
        __vptr_int8  rot_src_dst_ptr_y,          // Rotated src-dst matrix
        __vptr_uint16  rot_src_lin_ptr,          // Linearized  rotated src matrix
        __vptr_uint16  rot_dst_lin_ptr,          // Linearized  rotated dst matrix
        __vptr_int16  tlu_src_ptr,               // output  5x5 tlu src
        __vptr_int16  tlu_dst_ptr,               // output  5x5 tlu dst
        __vptr_uint8  true_descriptor_optr       // Brief Descriptor (Output)

)

{

    __agen Addr_off;
    __vector Voff;

    Addr_off = 0;

    // Loop-1
    /* Compute the column sum/row sum for 32x32 patch around the keypoint weighted by the moment mask */
    /* At the end of the loop, we have 16 sums stored out, which would added in the next loop */
    for (int I3 = 0; I3 < 1; I3++)
    {

        __vector Vin1, Vin3;                 // input1
        __vector Vin2, Vin4;                 // input Col mask
        __vector Vin5, Vin6;                 // input Row mask
        __vector VSum1, VSum2;
        __vector VSum3, VSum4;

        __agen Addr_out;
        __agen Addr_in1;
        __agen Addr_mask1;
        VSum1     = 0;
        VSum2     = 0;
        VSum3     = 0;
        VSum4     = 0;
        Addr_out  = 0;
        // Loop-1
        /* In first pass, try to get the sum of each column/row.          */
        for (int I1 = 0; I1 < MOMENTS_PATCH_SIZE/(2*VCOP_SIMD_WIDTH); I1++)
            // Process in batches of 16 columns
        {
            for (int I2 = 0; I2 < MOMENTS_PATCH_SIZE;I2++)
                // Generate 8 outputs which are weighted sum of 32 pixels
                // At the same time store transposed data for row sums
            {
                Addr_in1   = I1*2*INVECTORSZ + I2*STRIDE*INELEMSZ;
                Addr_mask1 = I1*2*INVECTORSZ + I2*MOMENTS_PATCH_SIZE*INELEMSZ;
                // Equivalent to (Moments_patch-size+4) *8

                (Vin1, Vin3) = (input_image_ptr + (5*PATCH_SIZE + 8*PATCH_SIZE + 8)*sizeof(*input_image_ptr))[Addr_in1].deinterleave();
                (Vin2, Vin4) = moments_col_mask[Addr_mask1].deinterleave();
                (Vin5, Vin6) = moments_row_mask[Addr_mask1].deinterleave();

                VSum1     += Vin1*Vin2;
                VSum2     += Vin3*Vin4;
                VSum3     += Vin1*Vin5;
                VSum4     += Vin3*Vin6;

            } // for I2

        } //for I1
        moments_col_sum[Addr_out].interleave()= (VSum1,VSum2).saturate();
        moments_row_sum[Addr_out].interleave()= (VSum3,VSum4).saturate();
    }

    // Loop-2
    /* In second pass, use one.pt loads to sum up all the column sums/row sums  */
    for (int I1 = 0; I1 <1; I1++)
    {
        __agen Addr_in1;
        __agen Addr_out;
        __vector Vin1, Vin2;
        __vector VSum1, VSum2;
        Addr_out    = I1*OUTELEMSZ;
        VSum1       = 0;
        VSum2       = 0;
        for (int I2 = 0; I2 < MOMENTS_PATCH_SIZE/2;I2++)
        {
            Addr_in1   = I2*OUTELEMSZ;
            Vin1       = moments_col_sum[Addr_in1].onept();
            Vin2       = moments_row_sum[Addr_in1].onept();
            VSum1       += Vin1;
            VSum2       += Vin2;
        } // I2

        moments_m10[Addr_out].onept()  = VSum1.saturate();
        moments_m01[Addr_out].onept()  = VSum2.saturate();
    } // I1

    // Loop-3
    /**********************************************************************/
    /* CAlculate arc tan (y (m01)/x (m10)) using the following steps      */
    /* 1: Calculate abs(x) * thr                                          */
    /* 2: Calculate abs(y) > abs(x) * thr                                 */
    /* 3: Pack and do bitc add                                            */
    /* 4: Choose correct offset based on sign of x & y                    */
    /**********************************************************************/

    __vector V_offset;
    V_offset = 0;
    for (int I1 = 0; I1 <1; I1++)
    {
        __agen Addr_in1, Addr_out;
        __vector Vxthr;
        __vector Vx;  // M10
        __vector Vy;  // M01
        __vector Vx_abs;
        __vector Vx_multhr;
        __vector Vy_abs;
        __vector V_decision;

        Addr_in1   = I1*OUTELEMSZ;  //U16
        Addr_out   = I1*INELEMSZ; //U8
        Vxthr      = arctan_xthr[Addr_in1];
        Vx         = moments_m10[Addr_in1].onept();
        Vy         = moments_m01[Addr_in1].onept();
        Vx_abs     = abs(Vx) ;
        Vy_abs     = abs(Vy);
        Vx_multhr  = (Vx_abs * Vxthr).round(ARCTAN_RND_BITS); // Round by 8 bits to get same precision as y
        V_decision = pack(Vy_abs >= Vx_multhr);// Replicates decision 8 times
        V_offset   = count_bits(V_decision); //8 bits
    } // I1


    /**********************************************************************/
    /*   sign(x)    sign(y)   x^y      x1      x0      offset
0          0       0       24      0         0
0          1       1       24      0         24
1          0       1       8       16        8
1          1       0       8       16        16
     */
    /**********************************************************************/
    // Loop-4
    for (int I1 = 0; I1 <1; I1++)
    {
        __agen Addr_in1, Addr_out;
        __vector Vx_sign, Vy_sign, Vxy_xor;
        __vector Vk_0, Vk_8, Vk_16, Vk_24;
        __vector Vx, Vx_0, Vx_1;  // M10
        __vector Vy;  // M01
        __vector Vquad_offset;

        Vx_0 = 0;
        Vx_1 = 24;
        Vk_0 = 0;
        Vk_8 = 8;
        Vk_16 = 16;
        Addr_in1   = I1*OUTELEMSZ;  //U16
        Addr_out   = I1*INELEMSZ; //U8
        Vx         = moments_m10[Addr_in1].onept();
        Vy         = moments_m01[Addr_in1].onept();
        Vx_sign    = Vk_0 > Vx;
        Vy_sign    = Vk_0 > Vy;
        Vxy_xor    = Vx_sign ^ Vy_sign;

        Vx_0       = select(Vx_sign,Vk_16, Vx_0);
        Vx_1       = select(Vx_sign,Vk_8, Vx_1);
        Vquad_offset = Vx_0;
        Vquad_offset = select(Vxy_xor,Vx_1,Vquad_offset);
        Vquad_offset += V_offset;
        arctan_pack_decision[Addr_out] =  Vquad_offset;
    } // I1

    Addr_off = 0;
    Voff     = offset_ptr[Addr_off];

    // In order to compute the descriptor, we need to smoothen the 48x48 patch
    // Hence, each pixel in the 48x48 patch is replaced by the 5x5 sum

    // Loop-5
    // This loop performs column sum followed by transpose
    for (int I1 = 0; I1 < PATCH_SIZE/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __vector Vin1, Vin3;                 // input1
        __vector Vin2, Vin4;                 // input2
        __vector VSum1, VSum2;
        VSum1     = 0;
        VSum2     = 0;
        for (int I2 = 0; I2 < PATCH_SIZE;I2++)
            // We generate 32 outputs, first 6 are redundant
        {
            __agen Addr_sub;
            __agen Addr_out;
            Addr_sub = I1*2*INVECTORSZ + I2*STRIDE*INELEMSZ ;
            // For every block of 48x8 (shorts), the output is put in a 50*8(shorts) array
            // Equivalent to 48*8.5; So it occupies 9 lines of 48 shorts each.
            // Next block of 48x8 can be started at an offset of 48*9
            Addr_out = I1*2*(PATCH_SIZE_P2*8)* OUTELEMSZ + I2*OUTELEMSZ;
            // Make address contiguous

            (Vin1, Vin3)     = input_image_ptr[Addr_sub].deinterleave();
            (Vin2, Vin4)     = (input_image_ptr + 5*PATCH_SIZE*sizeof(*input_image_ptr))[Addr_sub].deinterleave();

            (Vin1, Vin3).interleave();
            (Vin2, Vin4).interleave();

            VSum1     += Vin2;
            VSum2     += Vin4;

            VSum1     -= Vin1;
            VSum2     -= Vin3;

            (col_sum_ptr + 5*PATCH_SIZE_P2*sizeof(*col_sum_ptr))[Addr_out].p_scatter(Voff) = VSum1;
            (col_sum_ptr + 5*PATCH_SIZE_P2*sizeof(*col_sum_ptr) + (PATCH_SIZE_P2*8)*OUTELEMSZ)[Addr_out].p_scatter(Voff) = VSum2;
        } // for I2
    } //for I1


    // Notes:
    // Output comes out transposed
    // Need to take care of that in brief calculation stage

    // Loop-6
    // This loop performs row sum to get the final 5x5 sum
    for (int I1 = 0; I1 < PATCH_SIZE/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __vector Vin1,Vin3;                 // input1
        __vector Vin2,Vin4;                 // input2
        __vector VSum1, VSum2;

        VSum1    = 0;
        VSum2    = 0;
        for (int I2 = 0; I2 < PATCH_SIZE; I2++)
        {
            __agen Addr_sub;
            __agen Addr_out;

            Addr_sub = I1*2*OUTVECTORSZ + I2*PATCH_SIZE_P2*OUTELEMSZ;
            // Input is stored as 48 consecutive elements followed by a step of2.
            // Each Mac should move by 50 Every iteration of inner loop
            Addr_out = I1*4*OUTVECTORSZ + I2*(PATCH_SIZE*2)*OUTELEMSZ; //Output eventually comes out as a 32x32
            // Addr_out is now stepping with a gap in between to enable other copy to be stored


            (Vin1,Vin3)  = col_sum_ptr[Addr_sub].deinterleave(); //5 rows above first valid output
            (Vin2,Vin4)  = (col_sum_ptr + 5*PATCH_SIZE_P2*sizeof(*col_sum_ptr))[Addr_sub].deinterleave();

            (Vin1, Vin3).interleave();
            (Vin2, Vin4).interleave();

            VSum1      += Vin2;
            VSum2      += Vin4;

            VSum1      -= Vin1;
            VSum2      -= Vin3;

            row_col_sum_ct_ptr[Addr_out] = VSum1;
            (row_col_sum_ct_ptr + 2*OUTVECTORSZ)[Addr_out] = VSum2;

            (row_col_sum_ct_ptr + 8*sizeof(*row_col_sum_ct_ptr))[Addr_out] = VSum1;
            (row_col_sum_ct_ptr + 8*sizeof(*row_col_sum_ct_ptr) + 2*OUTVECTORSZ)[Addr_out] = VSum2;

        } // I2
    } // I1


    /*----------------------------------------------------------------------------*/
    /* 1 Index is absorbed as the indexed address of sin/cos is provided here     */
    /* 2 Reading the first location of sinc/cos table.                            */
    /* 3 Use cos/sin from step-2 and read 512 entries from in1_ptr, create rot    */
    /*   512 locations                                                            */
    /* 4 Assume in_ptr store x,y (with x at lower address)                        */
    /* 5 Performance should be 4 cycles/iteration = 2*512/8 = 128 cycles          */
    /*----------------------------------------------------------------------------*/
    /**********************************************************************/
    /* Use the offset to read sin/cos table */
    /* Select desired sin/cos value and store in sin/cos_ptr              */
    /**********************************************************************/
    // Loop-7
    _LOOKUP(NUM_TBLS_1, NUM_PTS_TLU);
    for (int I2 = 0; I2 <1 ; I2++)
    {
        __vector Vindex, Vtabledata;
        __agen table_addr = 0;
        __agen index_addr = I2*INELEMSZ*NUM_TBLS_1;
        __agen out_addr   = I2*OUTELEMSZ*NUM_TBLS_1;

        Vindex            = arctan_pack_decision[index_addr];
        Vtabledata        = sin_array_ptr[table_addr].lookup(Vindex);
        sin_ptr[out_addr].table_npt() = Vtabledata;
    } // int I2

    // Loop-8
    _LOOKUP(NUM_TBLS_1, NUM_PTS_TLU);
    for (int I2 = 0; I2 <1 ; I2++)
    {
        __vector Vindex, Vtabledata;
        __agen table_addr = 0;
        __agen index_addr = I2*INELEMSZ*NUM_TBLS_1;
        __agen out_addr   = I2*OUTELEMSZ*NUM_TBLS_1;

        Vindex            = arctan_pack_decision[index_addr];
        Vtabledata        = cos_array_ptr[table_addr].lookup(Vindex);
        cos_ptr[out_addr].table_npt() = Vtabledata;
    } // int I2


    // Loop-9
    // Use the cos and sin values looked up to compupte the rotated x,y co-ordinates
    for (int I1 = 0; I1 < 512/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr_1;
        __agen Addr_2;
        __vector Vin_x_1, Vin_x_2;
        __vector Vin_y_1, Vin_y_2;
        __vector cos_phi;
        __vector sin_phi;
        __vector Vout_x_1, Vout_x_2;
        __vector Vout_y_1, Vout_y_2;

        Addr_1   = I1*0; //16bits for cos etc
        cos_phi  = cos_ptr[Addr_1].onept();
        sin_phi  = sin_ptr[Addr_1].onept();

        Addr_2                = I1*INVECTORSZ*2;
        (Vin_x_1,Vin_x_2)     = in_src_dst_x_ptr[Addr_2].deinterleave();
        (Vin_y_1,Vin_y_2)     = in_src_dst_y_ptr[Addr_2].deinterleave();


        Vout_x_1        = Vin_x_1 * cos_phi; //_mul32;
        Vout_x_2        = Vin_x_2 * cos_phi; //_mul32;

        Vout_x_1       -= Vin_y_1 * sin_phi; //_mul32;
        Vout_x_2       -= Vin_y_2 * sin_phi; // _mul32; // 2 cycles

        Vout_y_1        = Vin_y_1 * cos_phi;
        Vout_y_1       += Vin_x_1 * sin_phi;

        Vout_y_2        = Vin_y_2 * cos_phi;
        Vout_y_2       += Vin_x_2 * sin_phi; // 2 cycles

        rot_src_dst_ptr_x[Addr_2].interleave() =  (Vout_x_1,Vout_x_2).round(RND_BITS);
        rot_src_dst_ptr_y[Addr_2].interleave() =  (Vout_y_1,Vout_y_2).round(RND_BITS);

    } // For I1


    /* Linearized address can be obtained using Vin_y *width + Vin_x */
    /* However since the matrix is transposed we have to perform     */
    /* Vin_x * width + Vin_y.                                        */

    // Loop-10
    for (int I1 = 0; I1 < 256/(2*VCOP_SIMD_WIDTH); I1++)
    {
        __agen Addr_2, Addr_3;
        __vector Vin_x_1, Vin_x_2, Vin_x_3, Vin_x_4;
        __vector Vin_y_1, Vin_y_2, Vin_y_3, Vin_y_4;
        __vector Vout_y_1, Vout_y_2, Vout_y_3, Vout_y_4;
        __vector Vconst;
        __vector V_width;
        Vconst                =   1225; // 25*48 + 25
        V_width               = PATCH_SIZE;

        Addr_2                =   I1*2*INVECTORSZ;
        Addr_3                =   I1*2*OUTVECTORSZ;
        (Vin_x_1,Vin_x_2)     =   rot_src_dst_ptr_x[Addr_2].deinterleave();
        (Vin_y_1,Vin_y_2)     =   rot_src_dst_ptr_y[Addr_2].deinterleave();

        (Vin_x_3,Vin_x_4)     =   (rot_src_dst_ptr_x + 256*sizeof(*rot_src_dst_ptr_x))[Addr_2].deinterleave();
        (Vin_y_3,Vin_y_4)     =   (rot_src_dst_ptr_y + 256*sizeof(*rot_src_dst_ptr_y))[Addr_2].deinterleave();


        Vout_y_1              =  Vconst + Vin_y_1;
        Vout_y_1              += Vin_x_1 * V_width;

        Vout_y_3             =   Vin_y_3 + Vconst;
        Vout_y_3             +=  Vin_x_3 * V_width;

        Vout_y_2              =  Vconst + Vin_y_2;
        Vout_y_2              += Vin_x_2 * V_width;

        Vout_y_4             =   Vin_y_4 + Vconst;
        Vout_y_4             +=  Vin_x_4 * V_width;

        rot_src_lin_ptr[Addr_3].interleave()       = (Vout_y_1, Vout_y_2);
        rot_dst_lin_ptr[Addr_3].interleave()       = (Vout_y_3, Vout_y_4);
    }// for I1


    // Loop-11
    // Look up the 5x5 sum based on the src index
    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
    for (int I2 = 0; I2 <256/2 ; I2++)
    {
        __vector Vindex, Vtabledata;
        __agen table_addr = 0;
        __agen index_addr = I2*OUTELEMSZ*NUM_TBLS;
        __agen out_addr   = I2*OUTELEMSZ*NUM_TBLS;

        Vindex            = rot_src_lin_ptr[index_addr];
        Vtabledata        = row_col_sum_ct_ptr[table_addr].lookup(Vindex);
        tlu_src_ptr[out_addr].table_npt() = Vtabledata;
    } // int I2


    // Loop-12
    // Look up the 5x5 sum based on the dst index
    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
    for (int I2 = 0; I2 <256/2 ; I2++)
    {
        __vector Vindex, Vtabledata;
        __agen table_addr = 0;
        __agen index_addr = I2*OUTELEMSZ*NUM_TBLS;
        __agen out_addr   = I2*OUTELEMSZ*NUM_TBLS;

        Vindex            = rot_dst_lin_ptr[index_addr];
        Vtabledata        = row_col_sum_ct_ptr[table_addr].lookup(Vindex);
        tlu_dst_ptr[out_addr].table_npt() = Vtabledata;
    } // int I2


    // Loop-13
    // Compare the src and dst looked up values to get the descriptor
    for (int I2 = 0; I2 <256/(2*VCOP_SIMD_WIDTH) ; I2++)
    {
        __vector Vin_x_1, Vin_x_2;
        __vector Vin_y_1, Vin_y_2;
        __agen Addr_1, Addr_2;
        __vector   Vout_1, Vout_2;
        __vector   VSum1, VSum2;
        Addr_1                 = I2 * 2 * OUTVECTORSZ;
        Addr_2                 = I2 * 2 * INELEMSZ;
        (Vin_x_1, Vin_x_2)     = tlu_src_ptr[Addr_1].deinterleave();
        (Vin_y_1, Vin_y_2)     = tlu_dst_ptr[Addr_1].deinterleave();
        //compare vin_x_1 and vin_x_2

        (Vin_x_1, Vin_x_2).interleave();
        (Vin_y_1, Vin_y_2).interleave();

        Vout_1                 = pack(Vin_x_1 >= Vin_y_1);
        Vout_2                 = pack(Vin_x_2 >= Vin_y_2);

        VSum1                  = ~Vout_1;
        VSum2                  = ~Vout_2;

        true_descriptor_optr[Addr_2].onept() = VSum1;
        (true_descriptor_optr + INELEMSZ)[Addr_2].onept() = VSum2;

    } //for I2


} // End of function
/*----------------------------------------------------------------------------*/
/* End of file: vcop_vcop_compute_rBrief_kernel.k                              */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2014.                                  */
/*============================================================================*/
