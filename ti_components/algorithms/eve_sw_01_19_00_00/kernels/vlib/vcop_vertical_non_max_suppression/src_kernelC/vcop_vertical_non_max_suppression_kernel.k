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


/*----------------------------------------------------------------------------*/
/* NAME: vcop_vertical_non_max_suppression_kernel                           */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*     This kernel implements vcop functions required for sparse N-point      */
/*     non maximal suppression in Y direction                                 */
/* AUTHOR:                                                                    */
/*             Prashanth R V (p-viswanath@ti.com)                             */
/*                                                                            */
/* VERSION:                                                                   */
/*            1.0 (Nov 2013) : Base version.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define ELEMSZ32         sizeof(*pack_XY)
#define ELEMSZ16         sizeof(*nms_id)
#define NUM_TBLS        (1)
#define NUM_PTS_TLU     (1)

void vcop_vertical_non_max_suppression_kernel
(
    __vptr_uint32       pack_XY,
    unsigned short      num_corners,
    unsigned short      max_corners,
    __vptr_uint16       nms_X_Score,
    __vptr_uint16       nms_id,
    __vptr_uint16       nms_Y_Score,
    __vptr_uint16       nms_Y_XY,
    __vptr_uint32       nms_Y1_XY,   // 32-bit pointer of nms_Y_XY - needed for loading in loop-3
    __vptr_uint32       nms_Score,   // Score packed with Id
    __vptr_uint8        Id_list
)
{
    // Loop 1 - unpack X, Y and id
    for(int I3 = 0; I3 < (num_corners+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
    {
        __vector Vx, Vy, id;
        __vector Vin;
        __vector Vconst22, Vconst12;
        __vector Vmask1, Vmask2;
        __agen Addr1, Addr2;

        Vconst22 = -22;
        Vconst12 = -12;
        Vmask1 = 0x003FF000;
        Vmask2 = 0x00000FFF;

        Addr1 = I3*VCOP_SIMD_WIDTH*ELEMSZ32;
        Addr2 = I3*VCOP_SIMD_WIDTH*ELEMSZ16;

        Vin = pack_XY[Addr1];    // packed X,Y and ID - X[31:22], Y[21:12], Id[11:0]

        Vx = (Vin << Vconst22);  // Get X by right shift by 22
        Vy = (Vin & Vmask1);

        Vy = Vy << Vconst12;    // Get Y by mask and right shift by 12
        id = (Vin & Vmask2);    // Get Id

        nms_Y_XY[Addr1].interleave() = (Vy, Vx);   // Store XY in packed format X[31:16], Y[15:0]
        nms_id[Addr2] = id;   // Store ID - Used for LUT of score in the next loop
    }

    // Loop 2: LUT - lookup score value based on the id
    // This loop is needed since the score is not in order with respect to XY, which is sorted based on X
    // Hence, score is re-arranged using the ID extracted from the previous loop
    _LOOKUP(NUM_TBLS, NUM_PTS_TLU);

    for(int I3 = 0; I3 < num_corners; I3++)
    {
        __vector Vindex, Vtabledata;
        __agen index_addr = I3*ELEMSZ16;
        __agen table_addr = 0;
        __agen out_addr = I3*ELEMSZ16;

        Vindex = nms_id[index_addr];
        Vtabledata = nms_X_Score[table_addr].lookup(Vindex);
        nms_Y_Score[out_addr].table_npt() = Vtabledata;
    }

    // Loop 3 - Now apply NMS in Y direction
    for(int I2 = 0; I2 < 1; I2++)
    {
        __agen Addr0 = I2;
        __vector id;
        id = Id_list[Addr0];

        for(int I3 = 0; I3 < (num_corners+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
        {
            __vector Vin1, Vin2, Vin3;
            __vector Vscore1, Vscore2, Vscore3;
            __vector Vnf1, Vnf2;
            __vector Vsf1, Vsf2;
            __vector Vf1, Vf2, Vf;
            __vector Vone, Vconst8, Vconst16, Vzero;

            Vone = 1;
            Vconst8 = 8;
            Vconst16 = 16;
            Vzero = 0;

            __agen Addr1 = I3*VCOP_SIMD_WIDTH*ELEMSZ32;
            __agen Addr2 = I3*VCOP_SIMD_WIDTH*ELEMSZ16;

            Vin1 = nms_Y1_XY[Addr1]; // Use 32-bit pointer to load XY in packed format
            Vin2 = (nms_Y1_XY+ELEMSZ32)[Addr1];
            Vin3 = (nms_Y1_XY+2*ELEMSZ32)[Addr1];

            Vscore1 = nms_Y_Score[Addr2];
            Vscore2 = (nms_Y_Score+ELEMSZ16)[Addr2];
            Vscore3 = (nms_Y_Score+2*ELEMSZ16)[Addr2];

            Vin1 += Vone;   // Y+1 for top neighbor check
            Vin3 -= Vone;   // Y-1 for bottom neighbor check

            Vnf1 = (Vin2 == Vin1);  // Check if center = top; Y = Y-1? and X=X?
            Vnf2 = (Vin2 == Vin3);  // Check if cetner = bottom; Y = Y+1? and X=X?

            Vsf1 = (Vscore2 <= Vscore1);  // Check if center score < top neighbor score
            Vsf2 = (Vscore2 <= Vscore3);  // Check if center score < bottom neighbor score

            Vf1 = Vnf1 & Vsf1;  // Final mask of neighbor and score for top neighbor
            Vf2 = Vnf2 & Vsf2;  // Final mask of neighbor and score for bottom neighbor

            // Final mask
            // If 1, neighbor exists and score is less than neighbor. Hence needs to be suppressed
            // However, we need to pack score of the non-suppressed values with ID, we need to invert the mask
            Vf1 |= Vf2;
            Vin1 = Vscore2 << Vconst16; // Take score and left shift by 16

            Vf = Vone - Vf1;   // Invert the mask Vf1
            Vin1 |= id;        // Pack Score with Id in lower 16 bit

            id += Vconst8;

            // Store the packed score for only non-suppressed values - predicated on Vf
            (nms_Score+ELEMSZ32)[Addr1] = Vzero.predicate(Vf1);
            (nms_Score+ELEMSZ32)[Addr1] = Vin1.predicate(Vf);

        }
    }

    //Loop 4: Apply NMS for first corner point
    for(int I3 = 0; I3 < 1; I3++)
    {
        __agen Addr0;
        Addr0 = I3;

        __vector Score0, Score1;
        __vector Vconst16, Vzero;
        __vector Vin1;
        __vector xy0, xy1;
        __vector Vnf1;
        __vector Vsf1;
        __vector Vf1;
        __vector Vone;

        Vzero = 0;
        Vconst16 = 16;
        Vone = 1;

        Score0 = nms_Y_Score[Addr0].onept();
        Score1 = (nms_Y_Score + ELEMSZ16)[Addr0].onept();

        // Use 32-bit pointer to load XY in packed format
        xy0 = nms_Y1_XY[Addr0].onept();
        xy1 = (nms_Y1_XY+ELEMSZ32)[Addr0].onept();

        xy0 += Vone;
        Vsf1 = (Score0 <= Score1);

        Vnf1 = (xy0 == xy1);
        Vin1 = Score0 << Vconst16;

        Vf1 = Vnf1 & Vsf1;
        Vin1 |= Vzero;

        Vnf1 = Vone - Vf1;

        nms_Score[Addr0].onept() = Vzero.predicate(Vf1);
        nms_Score[Addr0].onept() = Vin1.predicate(Vnf1);
    }

    // Loop 5: apply NMS for last corner point
    for(int I3 = 0; I3 < 1; I3++)
    {
        __agen Addr0;
        Addr0 = I3;

        __vector Score_last_1, Score_last;
        __vector Vconst16, Vlast, Vid;
        __vector Vin1;
        __vector xy0, xy1;
        __vector Vnf1;
        __vector Vsf1;
        __vector Vf1;
        __vector Vone;

        Vid = num_corners-1;
        Vlast = num_corners-1;
        Vconst16 = 16;
        Vone = 1;

        Score_last = (nms_Y_Score + (num_corners - 1)*ELEMSZ16)[Addr0].onept();
        Score_last_1 = (nms_Y_Score + (num_corners - 2)*ELEMSZ16)[Addr0].onept();

        // Use 32-bit pointer to load XY in packed format
        xy0 = (nms_Y1_XY + (num_corners - 2)*ELEMSZ32)[Addr0].onept();
        xy1 = (nms_Y1_XY + (num_corners - 1)*ELEMSZ32)[Addr0].onept();

        xy0 += Vone;
        Vsf1 = (Score_last <= Score_last_1);

        Vnf1 = (xy0 == xy1);
        Vin1 = Score_last << Vconst16;

        Vf1 = Vnf1 & Vsf1;
        Vin1 |= Vlast;

        Vnf1 = Vone - Vf1;

        (nms_Score + (num_corners - 1)*ELEMSZ32)[Addr0].onept() = Vid.predicate(Vf1);
        (nms_Score + (num_corners - 1)*ELEMSZ32)[Addr0].onept() = Vin1.predicate(Vnf1);
    }

    // Pad the scores with zeros upto max_corners
    for(int I3=0; I3 < (max_corners-num_corners+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
    {
        __agen Addr0;

        Addr0 = I3*VCOP_SIMD_WIDTH*ELEMSZ32;

        __vector Vzero;

        Vzero = 0;

        (nms_Score + num_corners*ELEMSZ32)[Addr0] = Vzero;


    }

}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_vertical_non_max_suppression_kernel.k                    */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
