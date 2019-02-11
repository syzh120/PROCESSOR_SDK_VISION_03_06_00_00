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

#ifndef VCOP_HOUGH_FOR_LINES_CN_H_
#define VCOP_HOUGH_FOR_LINES_CN_H_


/* ==================================================
 *  @func     vcop_hough_for_lines_cn
 *
 *  @desc     Reference C implementation to  voted array of rho ( for fix theta)
 *                for all (listSize) the edge list points given as input
 *
 *  @inputs   This kernel takes following Inputs
 *                  pEdgeMapList :
 *                          Pointer to the edge list which is in packed format with x coordinate followed by y.
 *                          Both x and y are 16 bit quantity. Size of this buffer should be listSize * 2 * sizeof(uint16_t)
 *                  pCosSinThetaMulNormQ15 :
 *                          This is pointer to the buffer which contains precalculated values of cos(theta) * normFactor
 *                           followed by sin(theta) * normactor which are  signed quantity in Q15 format.  Where
 *                           normactor = (rhoMaxLength / (2 * diameter)
 *                           diameter = sqrt( imgWidth^2 + imgHeight ^2 ) which can be approximated to
 *                                             sqrt(2) * max (imgWidth, imgHeight)
 *                           Size of this array should be 2 * sizeof(uint16_t)
 *                  listSize :
 *                          Size of edge list in terms on number of edges
 *                  rhoMaxLength :
 *                          Maximum value which rho could take
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  intermIndexArray :
 *                          This is pointer  to an intermediate scratch buffer which contains the rho values calculated
 *                          for each edge point in the list. Size of this buffer should be (listsize * uint16_t)
 *
 *  @outputs   This kernel produce following outputs
 *                  votedRhoArray:
 *                          Pointer to the buffer which will store voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * 2 )
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_hough_for_lines_cn
(
  unsigned short        * pEdgeMapList,
  short                 * pCosSinThetaMulNormQ15,
  unsigned short        * intermIndexArray,
  unsigned short        * votedRhoArray,
  unsigned short          listSize,
  unsigned short          rhoMaxLength
);

/* ==================================================
 *  @func     vcop_merge_voted_rho_array_cn
 *
 *  @desc     Referrence C code to merge two voted rho array
 *
 *  @inputs   This kernel takes following Inputs
 *                  votedRhoArrayCurr:
 *                          Pointer to the buffer which contain  voted rho ( per theta) for current theta. Size of this buffer
 *                          should be (rhoMaxLength * (uint16_t) )
 *                  rhoMaxLength :
 *                          Maximum value which rho could take( should be same as the one used in previous kernel)
 *
 *  @outputs   This kernel produce following outputs
 *                  votedRhoArray :
 *                          Pointer to the buffer containing which will contains updated voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * sizeof(uint16_t))
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_merge_voted_rho_array_cn
(
  unsigned short *  votedRhoArrayCurr,
  unsigned short *  votedRhoArray,
  unsigned short    rhoMaxLength
);

#endif /* VCOP_HOUGH_FOR_LINES_CN_H_ */


