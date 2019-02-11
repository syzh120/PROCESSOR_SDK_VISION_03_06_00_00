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
/* NAME: vcop_horizontal_non_max_suppression_kernel                           */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*     This kernel implements vcop functions required for sparse N-point      */
/*     non maximal suppression in X direction                                 */
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

#define ELEMSZ           sizeof(*pInXY)
#define SCORESZ          sizeof(*Score)
#define ELEM_VECTORSZ    (VCOP_SIMD_WIDTH*ELEMSZ)
#define SCORE_VECTORSZ    (VCOP_SIMD_WIDTH*SCORESZ)

#define LSHIFT6  6
#define LSHIFT12 12

void vcop_horizontal_non_max_suppression
(
    __vptr_uint32       pInXY,
    unsigned short      num_corners,
    unsigned short      max_corners,
    __vptr_uint16       Score,
    __vptr_uint32       pack_XY,
    __vptr_uint16       nms_X_Score,
    __vptr_uint8        Id_list
)
{

    // Loop 1 - Do NMS in x direction
    // Data arranged in buckets of Y

    for(int I2 = 0; I2 < 1; I2++)
    {
        __agen Addr0 = I2;
        __vector id;

        id = Id_list[Addr0];

        for(int I3 = 0; I3 < (num_corners+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
        {
            __vector Vin1, Vin2, Vin3;
            __vector Vscore1, Vscore2, Vscore3;
            __vector Vnf1, Vnf2; // mask of check for neighbor XY
            __vector Vsf1, Vsf2; // mask of check for neighbor score
            __vector Vf1, Vf2; // final masks
            __vector Vconst, Vzero, Vone;
            __vector Vmask1, Vmask2;
            __vector Vconst6, Vconst12, Vconst8;

            Vconst6 = LSHIFT6;
            Vconst12 = LSHIFT12;
            Vconst8 = 8;

            Vconst = 0x10000;
            Vzero = 0;
            Vmask1 = 0xFFFF0000;
            Vmask2 = 0x0000FFFF;
            Vone = 1;

            __agen Addr1 = I3*ELEM_VECTORSZ;
            __agen Addr2 = I3*SCORE_VECTORSZ;

            Vin1 = pInXY[Addr1];
            Vin2 = (pInXY+ELEMSZ)[Addr1];
            Vin3 = (pInXY+2*ELEMSZ)[Addr1];

            Vscore1 = Score[Addr2];
            Vscore2 = (Score+SCORESZ)[Addr2];
            Vscore3 = (Score+2*SCORESZ)[Addr2];

            Vin1 += Vconst;    // X+1 for left neighbor check
            Vin3 -= Vconst;    // X-1 for right neighbor check

            Vnf1 = (Vin1 == Vin2);  // Check if center = left neighbor; X = X-1? and Y = Y?
            Vnf2 = (Vin3 == Vin2);  // Check if center = right neighbor; X = X+1? and Y = Y?

            Vsf1 = Vscore2 <= Vscore1;   // Check if center score < left neighbor score
            Vsf2 = Vscore2 <= Vscore3;   // check if center score < right neighbor score

            Vf1 = Vnf1 & Vsf1;  // Final mask of neighbor and score for left neighbor,
            Vf2 = Vnf2 & Vsf2;  // Final mask of neighbor and score for right neighbor,

            // If 1, neighbor exists and score is less than neighbor. Hence needs to be suppressed
            // If 0, preserve the score and XY
            Vf1 |= Vf2;

            Vf2   = Vone - Vf1;   // Invert the mask Vf1

            Vnf1 = Vin2 & Vmask1;
            Vnf2 = Vin2 & Vmask2;

            Vsf1 = (Vnf1 << Vconst6); // Since X is in the upper 16 bit, shift left by 6
            Vsf2 = (Vnf2 << Vconst12); // Since Y is in lower 16 bit, shift left by 12

            // Pack X,Y with Id: X - 10bit, Y - 10bit, Id: 12bit
            Vsf2 |= Vsf1 | id; // Pack Id in a vector form
            id += Vconst8;     // Increment Id by VCOP_SIMD_WIDTH

            // Predicated store of score - Store zero if Vf1 = 1, else keep score as is
            (nms_X_Score+SCORESZ)[Addr2] = Vzero.predicate(Vf1);
            (nms_X_Score+SCORESZ)[Addr2] = Vscore2.predicate(Vf2);

            (pack_XY + sizeof(*pack_XY))[Addr1] = Vsf2;
        }
    }

    // Loop 2: Do NMS for 1st element
    for(int I3 = 0; I3 < 1; I3++)
    {
        __agen Addr0;
        Addr0 = I3;

        __vector Score_zero;
        __vector Score1;
        __vector Vconst6, Vconst12;
        __vector Vconst;
        __vector Vx1, Vy1;
        __vector Vin1, Vin2;
        __vector Vout1;
        __vector Vzero;
        __vector Vmask1, Vmask2;
        __vector Vnf1;
        __vector Vsf1;
        __vector Vf1;
        __vector Vone;

        Vconst6 = LSHIFT6;
        Vconst12 = LSHIFT12;
        Vzero = 0;
        Vconst = 0x10000;
        Vmask1 = 0xFFFF0000;
        Vmask2 = 0x0000FFFF;
        Vone = 1;

        Vin1 = pInXY[Addr0].onept();
        Vin2 = (pInXY+ELEMSZ)[Addr0].onept();

        Score_zero = Score[Addr0].onept();
        Score1     = (Score + SCORESZ)[Addr0].onept();

        /* Check if 1 element is a neighbor of 2nd */
        Vin2 -= Vconst;
        Vy1 = Vin1 & Vmask2;

        Vsf1 = (Score_zero <= Score1);
        Vnf1 = (Vin1 == Vin2);

        Vf1 = Vnf1 & Vsf1;  // Final mask of neighbor and score for left neighbor,
        Vx1 = Vin1 & Vmask1;

        Vnf1 = Vone - Vf1;
        Vout1 = Vx1 << Vconst6;

        Vout1 |= Vy1 << Vconst12;

        Vout1 |= Vzero;

        pack_XY[Addr0].onept() = Vout1;
        // Predicated store of score - Store zero if Vf1 = 1, else keep score as is
        nms_X_Score[Addr0].onept()  = Vzero.predicate(Vf1);
        nms_X_Score[Addr0].onept()  = Score_zero.predicate(Vnf1);
    }


    for(int I3 = 0; I3 < 1; I3++)
    {
        __agen Addr0;
        Addr0 = I3;

        __vector Score_last;
        __vector Score_last_1;
        __vector Vconst6, Vconst12;
        __vector Vconst;
        __vector Vx1, Vy1;
        __vector Vin1, Vin2;
        __vector Vout1;
        __vector Vzero, Vlast;
        __vector Vmask1, Vmask2;
        __vector Vnf1;
        __vector Vsf1;
        __vector Vf1;
        __vector Vone;

        Vconst6 = LSHIFT6;
        Vconst12 = LSHIFT12;
        Vzero = 0;
        Vlast = num_corners - 1;
        Vconst = 0x10000;
        Vmask1 = 0xFFFF0000;
        Vmask2 = 0x0000FFFF;
        Vone = 1;

        Vin1 = (pInXY + (num_corners - 2)*ELEMSZ)[Addr0].onept();
        Vin2 = (pInXY + (num_corners - 1)*ELEMSZ)[Addr0].onept();

        Score_last_1 = (Score + (num_corners - 2)*SCORESZ)[Addr0].onept();
        Score_last   = (Score + (num_corners - 1)*SCORESZ)[Addr0].onept();

        /* Check if last element is a neighbor of last but 1 */
        Vin1 += Vconst;
        Vy1 = Vin2 & Vmask2;

        Vsf1 = (Score_last <= Score_last_1);
        Vnf1 = (Vin1 == Vin2);

        Vx1 = Vin2 & Vmask1;
        Vf1 = Vnf1 & Vsf1;  // Final mask of neighbor and score for left neighbor,

        Vnf1 = Vone - Vf1;
        Vout1 = Vx1 << Vconst6;

        Vout1 |= Vy1 << Vconst12;

        Vout1 |= Vlast;

        (pack_XY + (num_corners - 1)*sizeof(*pack_XY) )[Addr0].onept() = Vout1;

        // Predicated store of score - Store zero if Vf1 = 1, else keep score as is
        (nms_X_Score + (num_corners - 1)*SCORESZ)[Addr0].onept()  = Vzero.predicate(Vf1);
        (nms_X_Score + (num_corners - 1)*SCORESZ)[Addr0].onept()  = Score_last.predicate(Vnf1);
    }

    for(int I3=0; I3 < (max_corners-num_corners+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
    {
        __agen Addr0, Addr1;

        Addr0 = I3*VCOP_SIMD_WIDTH*ELEMSZ;
        Addr1 = I3*VCOP_SIMD_WIDTH*SCORESZ;
        __vector Vzero;

        Vzero = 0;

        (nms_X_Score + num_corners*SCORESZ)[Addr1] = Vzero;
        (pack_XY + num_corners*ELEMSZ)[Addr0] = Vzero;

    }

}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_horizontal_non_max_suppression_kernel.k                  */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
