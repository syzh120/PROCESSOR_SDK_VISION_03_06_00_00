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

#ifndef VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN
#define VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN

/* ==================================================
 *  @func     vcop_canny_bin_indexing
 *
 *  @desc     This function implements natural C of binning of edges into 4 cases:
 *                Case 1: Edges lying between -22.5 to +22.5 : output Index < 4
 *                Case 2: Edges lying between +22.5 to +67.5 : output Index == 4
 *                Case 3: Edges lying between +67.5 to +112.5 : output Index > 5
 *                Case 1: Edges lying between +112.5  to +157.5 : output Index == 5
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
 *
 *                  pGy :
 *                          Gradient in Y direction
 *
 *                  computeWidth :
 *                          Compute width
 *                  computeHeight :
 *                          Compute height
 *                  pitch :
 *                          Pitch of the input
 *
 *  @scratch   This func needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN produce following outputs
 *                  pIndex :
 *                          This is the pointer which contains the index corresponding to the edge as
 *                           described in the description
 *
 *  @remarks
 *                NONE
 *
 *  @constraints Following constraints
 *                NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_bin_indexing_cn(
    int16_t   *pGx,
    int16_t   *pGy,
    uint8_t   *pIndex,
    uint16_t   computeWidth,
    uint16_t   computeHeight,
    uint16_t   pitch);

/* ==================================================
 *  @kernel     vcop_canny_nms_max_cases
 *
 *  @desc     This kernel finds the maximum of all the pixel for all 4 cases along the
 *                Direction of edge. 4 cases are described as :
 *                Case 1: Edges lying between -22.5 to +22.5 : output Index < 4
 *                Case 2: Edges lying between +22.5 to +67.5 : output Index == 4
 *                Case 3: Edges lying between +67.5 to +112.5 : output Index > 5
 *                Case 1: Edges lying between +112.5  to +157.5 : output Index == 5
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
 *                   NONE
 *
 *  @constraints Following constraints
 *                    NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_nms_max_cases_cn
(
    uint16_t   *pMag,
    uint16_t   *pCase1Max,
    uint16_t   *pCase2Max,
    uint16_t   *pCase3Max,
    uint16_t   *pCase4Max,
    uint16_t computeWidth,
    uint16_t computeHeight,
    uint16_t pitch
);

/* ==================================================
 *  @func     vcop_canny_nms_double_thresholding
 *
 *  @desc     This function uses the previous two functions  to do NMS and also
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
 *                   NONE
 *
 *  @constraints Following constraints
 *                    NONE
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_canny_nms_double_thresholding_cn
(
    uint8_t    *pIndex,
    uint16_t   *pCase1Max,
    uint16_t   *pCase2Max,
    uint16_t   *pCase3Max,
    uint16_t   *pCase4Max,
    uint8_t    *pOutVal,
    uint8_t     lowThreshold,
    uint8_t     highThreshold,
    uint16_t width,
    uint16_t height,
    uint16_t pitch,
    uint16_t outputPitch
);


#endif /* VCOP_CANNY_NON_MAXIMUM_SUPPRESSION_CN */

/* ======================================================================== */
/*  End of file:  vcop_canny_non_maximum_suppression_cn.h                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



