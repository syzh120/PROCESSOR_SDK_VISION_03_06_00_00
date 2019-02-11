/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define Q_FORMAT_SHIFT (14U)
#define TAN_22_5_Q (6786)
#define TAN_67_5_Q (39554)

#define   VCOP_2SIMD_WIDTH   (2 * VCOP_SIMD_WIDTH)

#define ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))

#if (VCOP_HOST_EMULATION)
#include "vcop.h"
#endif


/* ==================================================
 *  @kernel     vcop_canny_bin_indexing
 *
 *  @desc     This kernel does the binning of edges into 4 cases:
 *                Case 1: Edges lying between -22.5 to +22.5 : output Index < 4
 *                Case 2: Edges lying between +22.5 to +67.5 : output Index == 4
 *                Case 3: Edges lying between +67.5 to +112.5 : output Index > 5
 *                Case 4: Edges lying between +112.5  to +157.5 : output Index == 5
 *                This kernel uses following three conditions
 *                Condition 1 :  abs(gy) > gx * tan(22.5)
 *                Condition 1 :  abs(gy) > gx * tan(67.5)
 *                Condition 3 :  Gx^Gy < 0
 *
 *                Following is the truth tables implemented in this kernel:
 *                               Condition1   Condition2  Condition3
 *                 Case 1    0                  0               0
 *                 Case 1    0                  0               1
 *                 Case 1    0                  1               0
 *                 Case 1    0                  1               1
 *                 Case 2    1                  0               0
 *                 Case 4    1                  0               1
 *                 Case 3    1                  1               0
 *                 Case 3    1                  1               1
 *
 *  @inputs   This kernel takes following Inputs
 *                  pGx :
 *                          Gradient in X direction
 *                          Size of this buffer should be ALIGN_2SMID(computeWidth) * computeHeight  * sizeof(int16_t)
 *                  pGy :
 *                          Gradient in Y direction
 *                          Size of this buffer should be ALIGN_2SMID(computeWidth) * computeHeight  * sizeof(int16_t)
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  pIndex :
 *                          This is the pointer which contains the index corresponding to the edge as
 *                           described in the description
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   This kernel is compute bound so buffer placement doesnt matter
 *
 *  @constraints Following constraints
 *                    Input data should be word aligned
 *                     pitch should be multiple of 4
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_bin_indexing(
    __vptr_int16   pGx,
    __vptr_int16   pGy,
    __vptr_uint8   pIndex,
    unsigned short computeWidth,
    unsigned short computeHeight,
    unsigned short pitch
)
{

    __vector VK1, VK2;
    __vector VKtan22_5Q;
    __vector VKtan67_5Q;

    __vector Gx1, Gx2;
    __vector Gy1, Gy2;
    __vector VGxTan22_5_1, VGxTan22_5_2;
    __vector VGxTan67_5_1, VGxTan67_5_2;

    __vector Vindex1, Vindex2;
    __vector VKzero;
    __vector VKQshift;

    /*---------------------------------------------------------------------*/
    /*  The instructions in the C code are manually re-arranged for using  */
    /*  less than 16 registers.                                            */
    /*---------------------------------------------------------------------*/

    VK1    = 1U;
    VK2    = 2U;


    for (int row = 0; row < computeHeight; row++)
    {
        for (int col = 0; col < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; col++)
        {
            __agen AddrIn,AddrOut;

            AddrIn  = row * pitch * sizeof(*pGx)   + col * VCOP_2SIMD_WIDTH * sizeof(*pGx);
            AddrOut = row * pitch * sizeof(*pIndex) + col * VCOP_2SIMD_WIDTH * sizeof(*pIndex);


            VKzero   = 0U;
            VKQshift = Q_FORMAT_SHIFT;

            VKtan22_5Q = TAN_22_5_Q;
            VKtan67_5Q = TAN_67_5_Q;

            (Gx1, Gx2)       =  pGx[AddrIn].deinterleave();
            (Gy1, Gy2)       =  pGy[AddrIn].deinterleave();

            /* This condition is to check whether edge lies in 1st and 3rd quadrant (Gx^Gy > 0) or
                    2nd and 4th quadrant (Gx^Gy < 0) */
            Vindex1 = (Gx1 ^ Gy1);
            Vindex2 = (Gx2 ^ Gy2);

            Vindex1 = (Vindex1 < VKzero); /* Condition 3 */
            Vindex2 = (Vindex2 < VKzero); /* Condition 3 */

            Gx1  = abs(Gx1);
            Gx2  = abs(Gx2);

            Gy1  = abs(Gy1);
            Gy2  = abs(Gy2);

            Gy1 = Gy1 << VKQshift;
            Gy2 = Gy2 << VKQshift;

            VGxTan22_5_1 = Gx1 * VKtan22_5Q;
            VGxTan22_5_2 = Gx2 * VKtan22_5Q;

            VGxTan67_5_1 = Gx1 * VKtan67_5Q;
            VGxTan67_5_2 = Gx2 * VKtan67_5Q;

            /* This condition is to check if abs(gy) < gx * tan(22.5)  */

            Gx1 = (Gy1 > VGxTan22_5_1); /* Condition 1 */
            Gx2 = (Gy2 > VGxTan22_5_2 );/* Condition 1 */

            /* This condition is to check if abs(gy) > gx * tan(67.5)  */
            Gy1 = Gy1 > VGxTan67_5_1;/* Condition 2 */
            Gy2 = Gy2 > VGxTan67_5_2;/* Condition 2 */


            Vindex1 |= (Gx1 << VK2);
            Vindex2 |= (Gx2 << VK2);

            Vindex1 |= (Gy1 << VK1);
            Vindex2 |= (Gy2 << VK1);

            pIndex[AddrOut].interleave()= (Vindex1, Vindex2);

        }
    }
}

/* ==================================================
 *  @kernel     vcop_canny_nms_max_cases
 *
 *  @desc     This kernel finds the maximum of all the pixel for all 4 cases along the
 *                Direction of edge. 4 cases are described as :
 *                Case 1: Edges lying between -22.5 to +22.5 : output Index < 4
 *                Case 2: Edges lying between +22.5 to +67.5 : output Index == 4
 *                Case 3: Edges lying between +67.5 to +112.5 : output Index > 5
 *                Case 4: Edges lying between +112.5  to +157.5 : output Index == 5
 *
 *  @inputs   This kernel takes following Inputs
 *                  pMag :
 *                          Gradient Magnitude
 *                          Size of this buffer should be ALIGN_2SMID(computeWidth) * computeHeight  * sizeof(int16_t)
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  pCase1Max :
 *                          Maximum of the three pixel along the direction of case 1
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase2Max :
 *                          Maximum of the three pixel along the direction of case 2
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase3Max :
 *                          Maximum of the three pixel along the direction of case 3
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase4Max :
 *                          Maximum of the three pixel along the direction of case 4
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   This kernel is compute bound so buffer placement doesnt matter
 *
 *  @constraints Following constraints
 *                    All input/output pointers should be word aligned
 *                    Pitch should be multiple of 2
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_nms_max_cases
(
    __vptr_uint16   pMag,
    __vptr_uint16   pCase1Max,
    __vptr_uint16   pCase2Max,
    __vptr_uint16   pCase3Max,
    __vptr_uint16   pCase4Max,
    unsigned short computeWidth,
    unsigned short computeHeight,
    unsigned short pitch
)
{
    __vector magTopRowOdd, magTopRowEven;
    __vector magTopRowOddPlus2, magTopRowEvenPlus2;

    __vector magMidRowOdd, magMidRowEven;
    __vector magMidRowOddPlus2, magMidRowEvenPlus2;

    __vector magBotRowOdd, magBotRowEven;
    __vector magBotRowOddPlus2, magBotRowEvenPlus2;

    __vector Vcase1MaxOdd, Vcase1MaxEven;
    __vector Vcase2MaxOdd, Vcase2MaxEven;
    __vector Vcase3MaxOdd, Vcase3MaxEven;
    __vector Vcase4MaxOdd, Vcase4MaxEven;

    __vector VcenterPixelEven, VcenterPixelOdd;
    __vector Vflag1, Vflag2;


    for (int row = 0; row < computeHeight; row++)
    {
        for (int col = 0; col < ALIGN_2SIMD(computeWidth)/VCOP_2SIMD_WIDTH; col++)
        {
            __agen addrMag, addrOut;

            addrMag   = col * sizeof(*pMag) * VCOP_2SIMD_WIDTH + row * pitch * sizeof(*pMag);
            addrOut   = col * sizeof(*pCase1Max) * VCOP_2SIMD_WIDTH + row * pitch * sizeof(*pCase1Max);

            (magTopRowOdd , magTopRowEven)  = (pMag)[addrMag].deinterleave();
            (magTopRowOddPlus2 , magTopRowEvenPlus2)  = (pMag + sizeof(*pMag) * 2)[addrMag].deinterleave();

            (magMidRowOdd , magMidRowEven)  = (pMag + pitch * sizeof(*pMag))[addrMag].deinterleave();
            (magMidRowOddPlus2, magMidRowEvenPlus2)  = (pMag + pitch * sizeof(*pMag) + sizeof(*pMag) * 2)[addrMag].deinterleave();

            (magBotRowOdd , magBotRowEven)  = (pMag + 2 * pitch * sizeof(*pMag) * 1)[addrMag].deinterleave();
            (magBotRowOddPlus2, magBotRowEvenPlus2)  = (pMag + 2 * pitch * sizeof(*pMag) + sizeof(*pMag) * 2)[addrMag].deinterleave();

            VcenterPixelEven = magMidRowEven;
            VcenterPixelOdd  = magMidRowOddPlus2;

            /* Case 1: Left Center (LC) and Right Center (RC) */
            /* LC : 1 3 5 7  9   11 13 15 */ /* 2 4 6 8   10 12 14 16 */
            /* RC : 3 5 7 9  11 13 15 17*/ /*  4 6 8 10 12  14 16 18 */
            Vcase1MaxOdd  = max(magMidRowOdd,  magMidRowOddPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag1 = VcenterPixelEven >= Vcase1MaxOdd;
            Vcase1MaxOdd = VcenterPixelEven * Vflag1;
            Vcase1MaxEven = max(magMidRowEven,  magMidRowEvenPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag2 = (VcenterPixelOdd >= Vcase1MaxEven);
            Vcase1MaxEven = VcenterPixelOdd * Vflag2;

            /* Case 3: Top Center(TC) and Bottom Center (BC )*/
            /* TC: 2 4 6 8 10 12 14 16 */ /* 3 5 7 9 11 13 15 17 */
            /* BC: 2 4 6 8 10 12 14 16 */ /* 3 5 7 9 11 13 15 17 */
            Vcase3MaxEven = max(magTopRowEven, magBotRowEven);
            /* Now find whether center pixel is maximum or not */
            Vflag1 = (VcenterPixelEven >= Vcase3MaxEven);
            Vcase3MaxEven = VcenterPixelEven * Vflag1;
            Vcase3MaxOdd  = max(magTopRowOddPlus2, magBotRowOddPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag2  = (VcenterPixelOdd >= Vcase3MaxOdd);
            Vcase3MaxOdd = VcenterPixelOdd * Vflag2;

            /* Case 4:  Top Left(TL) and Bottom Right (BR) */
            /* TL : 1 3 5 7 9   11 13 15 */ /* 2 4 6 8   10 12 14 16*/
            /* BR : 3 5 7 9 11 13 15 17 */ /* 4 6 8 10 12 14 16 18 */
            Vcase4MaxOdd  = max(magTopRowOdd, magBotRowOddPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag1  = (VcenterPixelEven >= Vcase4MaxOdd);
            Vcase4MaxOdd = VcenterPixelEven * Vflag1;
            Vcase4MaxEven = max(magTopRowEven, magBotRowEvenPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag2 = (VcenterPixelOdd >= Vcase4MaxEven);
            Vcase4MaxEven = VcenterPixelOdd * Vflag2;

            /* Case 2: Bottom Left (BL) and Top Right (TR) */
            /* BL : 1 3 5 7 9   11 13 15 */ /* 2 4 6 8   10 12 14 16*/
            /* TR : 3 5 7 9 11 13 15 17 */ /* 4 6 8 10 12 14 16 18 */
            Vcase2MaxOdd = max(magBotRowOdd, magTopRowOddPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag1 = (VcenterPixelEven >= Vcase2MaxOdd);
            Vcase2MaxOdd = VcenterPixelEven * Vflag1;
            Vcase2MaxEven = max(magBotRowEven, magTopRowEvenPlus2);
            /* Now find whether center pixel is maximum or not */
            Vflag2 = (VcenterPixelOdd >= Vcase2MaxEven);
            Vcase2MaxEven = VcenterPixelOdd * Vflag2;

            /* This extra instruction is required because register allocation fails if we use
                    interleave store of (Vcase3MaxEven , Vcase3MaxOdd) */
            (Vcase3MaxEven , Vcase3MaxOdd).interleave();

            pCase1Max[addrOut].interleave() = (Vcase1MaxOdd, Vcase1MaxEven);
            pCase2Max[addrOut].interleave() = (Vcase2MaxOdd, Vcase2MaxEven);
            /* Not using interleave store here as allocation is failing if we do so */
            pCase3Max[addrOut].npt() = Vcase3MaxEven;
            (pCase3Max + VCOP_SIMD_WIDTH * sizeof(*pCase3Max))[addrOut].npt() = Vcase3MaxOdd;

            pCase4Max[addrOut].interleave() = (Vcase4MaxOdd, Vcase4MaxEven);

        }
    }
}


/* ==================================================
 *  @kernel     vcop_canny_nms_double_thresholding
 *
 *  @desc     This kernel uses the previous two kernels to do NMS and also
 *                apply double threshold to give an image whose output is
 *                0 for pixels which are below low threshold
 *                1 for pixels which are above low threshold and below High Threshold
 *                255 for pixels which are above High Threshold
 *
 *
 *  @inputs   This kernel takes following Inputs
 *                  pIndex :
 *                          This is the pointer which contains the index corresponding to the edge as
 *                           described in the description
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *
 *                  pCase1Max :
 *                          Maximum of the three pixel along the direction of case 1
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase2Max :
 *                          Maximum of the three pixel along the direction of case 2
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase3Max :
 *                          Maximum of the three pixel along the direction of case 3
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  pCase4Max :
 *                          Maximum of the three pixel along the direction of case 4
 *                          Size of this buffer should be  ALIGN_2SMID(computeWidth) * computeHeight
 *                          Output pitch will be same as pitch
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *                  outputPitch :
 *                          Pitch of the input
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  pOutVal :
 *                   Gives double thresholded output as
 *                0 for pixels which are below low threshold
 *                1 for pixels which are above low threshold and below High Threshold
 *                255 for pixels which are above High Threshold
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                   This kernel is compute bound so buffer placement doesnt matter
 *
 *  @constraints Following constraints
 *                    All input/output pointers should be word aligned
 *                    Pitch should be multiple of 4
 *                    outputPitch should be multiple of 4
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_nms_double_thresholding
(
    __vptr_uint8    pIndex,
    __vptr_uint16   pCase1Max,
    __vptr_uint16   pCase2Max,
    __vptr_uint16   pCase3Max,
    __vptr_uint16   pCase4Max,
    __vptr_uint8    pOutVal,
    unsigned char   lowThreshold,
    unsigned char   highThreshold,
    unsigned short  width,
    unsigned short  height,
    unsigned short  pitch,
    unsigned short  outputPitch
)
{
    __vector Vindex1, Vindex2;
    __vector VcenterPix1, VcenterPix2;
    __vector Vcase2Max_1, Vcase2Max_2;
    __vector Vcase3Max_1, Vcase3Max_2;
    __vector Vcase4Max_1, Vcase4Max_2;
    __vector VlowThreshold, VhighThreshold;
    __vector Vmask1, Vmask2;

/* Reusing some of the existing allocated registers */
#define VoutVal1 Vcase2Max_1
#define VoutVal2 Vcase2Max_2
#define Vk5 Vk4
#define Vk0 Vcase3Max_1

    __vector Vk4;
    __vector Vk1;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < ALIGN_2SIMD(width)/VCOP_2SIMD_WIDTH; col++)
        {
            __agen addrIndex, addrCaseVal, addrOut;

            addrIndex   = col * sizeof(*pIndex) * VCOP_2SIMD_WIDTH + row * pitch * sizeof(*pIndex);
            addrCaseVal = col * sizeof(*pCase1Max) * VCOP_2SIMD_WIDTH + row * pitch * sizeof(*pCase1Max);
            addrOut     = col * sizeof(*pOutVal) * VCOP_2SIMD_WIDTH + row * outputPitch * sizeof(*pOutVal);
             /* First Valid Value of pIndex starts from location (1,1) */
            (Vindex1, Vindex2) = (pIndex + sizeof(*pIndex) + pitch * sizeof(*pIndex))[addrIndex].deinterleave();
            (VcenterPix1, VcenterPix2) = pCase1Max[addrCaseVal].deinterleave();
            (Vcase2Max_1, Vcase2Max_2) = pCase2Max[addrCaseVal].deinterleave();
            (Vcase3Max_1, Vcase3Max_2) = pCase3Max[addrCaseVal].deinterleave();
            (Vcase4Max_1, Vcase4Max_2) = pCase4Max[addrCaseVal].deinterleave();

            Vk1   = 1;
            Vk4   = 4;

            VhighThreshold = highThreshold;
            VlowThreshold  = lowThreshold;

            Vmask1 = (Vindex1 == Vk4);
            Vmask2 = (Vindex2 == Vk4);

            VcenterPix1 = select(Vmask1, Vcase2Max_1, VcenterPix1);
            VcenterPix2 = select(Vmask2, Vcase2Max_2, VcenterPix2);

            /* We are driving the value of 5 from exsitsing registers as we dont have enough register to store all constants */
            Vk5 = Vk4 + Vk1;

            Vmask1 = (Vindex1 == Vk5);
            Vmask2 = (Vindex2 == Vk5);

            VcenterPix1 = select(Vmask1, Vcase4Max_1, VcenterPix1);
            VcenterPix2 = select(Vmask2, Vcase4Max_2, VcenterPix2);

            Vmask1 = (Vindex1 > Vk5);
            Vmask2 = (Vindex2 > Vk5);

            VcenterPix1 = select(Vmask1, Vcase3Max_1, VcenterPix1);
            VcenterPix2 = select(Vmask2, Vcase3Max_2, VcenterPix2);

            Vmask1 = VcenterPix1 >= VlowThreshold;
            Vmask2 = VcenterPix2 >= VlowThreshold;

            /* We are driving the value of Vk0 from exsitsing registers as we dont have enough register to store all constants */
            Vk0  = Vk1 - Vk1;

            VoutVal1 = Vk0;
            VoutVal2 = Vk0;

            VoutVal1 = select(Vmask1, Vk1, VoutVal1);
            VoutVal2 = select(Vmask2, Vk1, VoutVal2);

            Vmask1 = VcenterPix1 >= VhighThreshold;
            Vmask2 = VcenterPix2 >= VhighThreshold;

            VoutVal1 = select(Vmask1, Vk5, VoutVal1);
            VoutVal2 = select(Vmask2, Vk5, VoutVal2);

            pOutVal[addrOut].interleave() = (VoutVal1, VoutVal2).saturate(0,0,5,255);
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_canny_non_maximum_suppression_kernel.k               */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

