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

#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define   VCOP_2SIMD_WIDTH   (2 * VCOP_SIMD_WIDTH)
#define   ALIGN_2SIMD(a)   (((a) + 2*VCOP_SIMD_WIDTH-1) & ~(2*VCOP_SIMD_WIDTH-1))


/* normFactMulDiam = Normalisation factor  * diameter */
/* normFactMulDiam = (rhoMaxLength/(diameter * 2 ))  * diameter */
/* normFactMulDiam = (rhoMaxLength / 2) */
#define NORM_MUL_NORMFACTOR_Q15 ((rhoMaxLength << 15) / 2)

#define EDGELIST_ELEM_SIZE (sizeof(*pEdgeMapList))
#define OUT_INDEX_ELEM_SIZE (sizeof(*intermIndexArray))
#define VOTED_ARRAY_ELEM_SIZE (sizeof(*votedRhoArray8Copy))

#define NUM_HIST_COPY  (8)

/* ==================================================
 *  @kernel     vcop_hough_for_lines
 *
 *  @desc     This kernel calculates the 8 copy voted array of rho ( for fix theta)
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
 *                  votedRhoArray8Copy :
 *                          Pointer to the buffer which will store the 8 copies of voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * 2 * 8)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          pEdgeMapList -> VCOP_IBUFLA
 *                          pCosSinThetaMulNormQ15 -> VCOP_WMEM
 *                          intermIndexArray -> VCOP_IBUFHA
 *                          votedRhoArray8Copy -> VCOP_WMEM
 *
 *  @constraints Following constraints
 *                          listSize should be multiple of 16
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_hough_for_lines
(
  __vptr_uint16           pEdgeMapList,
  __vptr_int16            pCosSinThetaMulNormQ15,
  __vptr_uint16           intermIndexArray,
  __vptr_uint16           votedRhoArray8Copy,
  unsigned short          listSize,
  unsigned short          rhoMaxLength
)
{

  /* Loop 1 : Find the rho values for corresponding to the current theta for list size edge elements*/
  __vector vSinLutQ8;
  __vector vCosLutQ8;
  __vector vEdge_x1;
  __vector vEdge_y1;
  __vector vEdge_x2;
  __vector vEdge_y2;
  __vector vTempX_1;
  __vector vTempX_2;
  __vector vTempY_1;
  __vector vTempY_2;
  __vector vNormMulDiamQ15;
  __vector vSinMulNormQ15;
  __vector vCosMulNormQ15;
  __agen   thetaAddr = 0;

  vNormMulDiamQ15 = NORM_MUL_NORMFACTOR_Q15;

  /* Load ( sin(theta) * normFactor ) and ( cos(theta) * normFactor ) values from  pCosSinThetaMulNormQ15*/
  vCosMulNormQ15 = pCosSinThetaMulNormQ15[thetaAddr].onept();
  vSinMulNormQ15 = (pCosSinThetaMulNormQ15 + 2)[thetaAddr].onept();


  for (int listCount = 0; listCount < (listSize) / VCOP_2SIMD_WIDTH; listCount++)
  {
    __agen edgeMapAddr = listCount * VCOP_2SIMD_WIDTH * EDGELIST_ELEM_SIZE * 2;
    __agen outIndexAddr = listCount * OUT_INDEX_ELEM_SIZE * VCOP_2SIMD_WIDTH;

    /* Get alternate edges using deinterleave loads */
    (vEdge_x1,vEdge_y1) = pEdgeMapList[edgeMapAddr].deinterleave();
    /* To use both functional unit  get another set of edge points */
    (vEdge_x2,vEdge_y2) = (pEdgeMapList + 32)[edgeMapAddr].deinterleave();

    /* We have to implment following equation */
    /* rho = (x*cos(theta) + y*sin(theta) + diameter) * normFactor */
    /* Above equation is split as follows */

    /* rho = x* (normFactor * cos(theta)) +  y * (normFactor *  sin(theta)) + (diameter * normFactor) */

    vTempX_1 = vCosMulNormQ15 * vEdge_x1;
    vTempX_2 = vCosMulNormQ15 * vEdge_x2;

    vTempY_1 = vSinMulNormQ15 * vEdge_y1;
    vTempY_2 = vSinMulNormQ15 * vEdge_y2;

    /* rho  = temp1 + temp2 + (diameter * normFactor)*/
    vTempX_1 += vNormMulDiamQ15 + vTempY_1 ;
    vTempX_2 += vNormMulDiamQ15 + vTempY_2 ;

    /* It is impornant to note that output wont bit match with reference at this stage becase of interleave loads*/
    intermIndexArray[outIndexAddr].interleave() = (vTempX_1, vTempX_2).round(15);

  }


  /* Loop 2 to clear histogram memory */
  for (int rhoCount = 0; rhoCount < ((ALIGN_2SIMD(rhoMaxLength) * 8)/VCOP_2SIMD_WIDTH ); rhoCount++)
  {
    __vector vZero1;
    __vector vZero2;
    __agen   addGen = rhoCount * VOTED_ARRAY_ELEM_SIZE * VCOP_2SIMD_WIDTH;

    vZero1 = 0;
    vZero2 = 0;
    votedRhoArray8Copy[addGen].interleave() = (vZero1,vZero2);
  }

  /*Loop 3 : Update votedRhoArray based on the index calculated in Loop 1 */

  /*--------------------------------------------------------------*/
  /*  Define explicitly that loop below is a histogram loop.      */
  /*--------------------------------------------------------------*/
  _HISTOGRAM(NUM_HIST_COPY);

  for (int listCount = 0 ; listCount < listSize / (NUM_HIST_COPY); listCount++ )
  {
    __vector vWeight;
    __vector vData;
    __vector vIndex;

    __agen histAgen = 0;
    __agen indexAddr = 0;

    indexAddr = listCount * OUT_INDEX_ELEM_SIZE * NUM_HIST_COPY;
    vWeight = 1;
    vIndex  = intermIndexArray[indexAddr];

    vData   = votedRhoArray8Copy[histAgen].hist_update
              (vIndex.saturate(0, (rhoMaxLength - 1)), vWeight);


  }

}


#define MEMORY_BANK_STRIDE (8*4)
#define TRANSPOSE_STRIDE ((ALIGN_2SIMD(rhoMaxLength) / 4 + 1) * 4)

/* ==================================================
 *  @kernel     vcop_merge_voted_rho_array
 *
 *  @desc     This kernel merges  the 8 copy voted array of rho ( for fix theta)
 *                calculated using above kernel to give a single voted rho array
 *
 *  @inputs   This kernel takes following Inputs
 *                  votedRhoArray8Copy :
 *                          Pointer to the buffer which contain  the 8 copies of voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * (uint16_t) * 8)
 *                  votedRhoArray :
 *                          Pointer to the buffer containing which voted rho ( per theta) that needs to get updated. Size of this buffer
 *                          should be (rhoMaxLength * sizeof(uint16_t))
 *                  offsetArray :
 *                          This is pointer to the buffer which contains precalculated offsets for scatter store. The offsets
 *                          are chosen such that after scatter store all enteries should go in a different bank. It is observed
 *                          that if we chose any odd number (in terms of words) greater than 8 then it will automatically
 *                          result into scatter store enteries to go into all different banks.  This offsets can be found by first
 *                          caluclating the stride considering the array is of rhoMaxLength. We have split the intermediate
 *                           transpose buffers into 2 hence for rhoMaxLength array total bytes = rhoMaxLength * sizeof(uint16_t).
 *                          Bytes per intermediate transpose buffer will be rhoMaxLength * sizeof(uint16_t)/2 . Now first convert it
 *                          to numer of words =  (rhoMaxLength * sizeof(uint16_t)) / 2)/ 4. Now we can choose next odd
 *                          word number lets say it is transposeStrideInWords
 *                          interimTransposeStride = transposeStrideInWords * 4. OffsetArray should contain interimTransposeStride
 *                          for all 8 elements ( interimTransposeStride * i) where i  0,1....7
 *                           Size of this array should be 8 * sizeof(uint16_t)
 *                  rhoMaxLength :
 *                          Maximum value which rho could take( should be same as the one used in previous kernel)
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  interimTransposeBuf1 :
 *                          This is pointer  to an intermediate scratch buffer to store the transpose
 *                          for each edge point in the list. Size of this buffer should be (interimTransposeStride  * 8)
 *
 *                  interimTransposeBuf2 :
 *                          This is pointer  to an intermediate scratch buffer to store the transpose
 *                          for each edge point in the list. Size of this buffer should be (interimTransposeStride  * 8)
 *
 *  @outputs   This kernel produce following outputs
 *                  votedRhoArray :
 *                          Pointer to the buffer containing which will contains updated voted rho ( per theta). Size of this buffer
 *                          should be (rhoMaxLength * sizeof(uint16_t))
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          votedRhoArray8Copy -> VCOP_WMEM
 *                          votedRhoArray          -> VCOP_IBUFHA
 *                          interimTransposeBuf1 -> VCOP_IBUFHA
 *                          interimTransposeBuf2 -> VCOP_WMEM
 *                          offsetArray                -> VCOP_WMEM
 *
 *
  *  @constraints Following constraints
 *                          rhoMaxLength  should be multiple of 16
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_merge_voted_rho_array
(
  __vptr_uint16   votedRhoArray8Copy,
  __vptr_uint16   votedRhoArray,
  __vptr_uint16   interimTransposeBuf1,
  __vptr_uint16   interimTransposeBuf2,
  __vptr_uint16   offsetArray,
  unsigned short  rhoMaxLength
)
{
  __vector vData1;
  __vector vData2;

  __vector vOffset;
   __agen offsetAddr = 0;

  vOffset = offsetArray[offsetAddr].npt();


  for ( int rhoCount = 0 ; rhoCount < ( ALIGN_2SIMD(rhoMaxLength)/ 2 ); rhoCount++)
  {

    __agen inAddr = rhoCount * MEMORY_BANK_STRIDE;
    __agen outAddr1 = rhoCount * 2;


    (vData1,vData2) = votedRhoArray8Copy[inAddr].deinterleave();
    /* Store these vector in transpose format with stride of more than rhoMaxLength /2 */
    interimTransposeBuf1[outAddr1].p_scatter(vOffset) = vData1;
    interimTransposeBuf2[outAddr1].p_scatter(vOffset) = vData2;
  }

  for ( int rhoCount = 0 ; rhoCount < ( ALIGN_2SIMD(rhoMaxLength)/ VCOP_2SIMD_WIDTH); rhoCount++)
  {
    __agen addrIn = rhoCount * 2 * VCOP_2SIMD_WIDTH;
    __vector vSum1;
    __vector vSum2;

    /* Load the previous votedRhoArray value to start */
    (vSum1,vSum2) = votedRhoArray[addrIn].deinterleave();

    for ( int i = 0 ; i < VCOP_SIMD_WIDTH ; i++)
    {
       __agen inAddr;
       __vector inData1;
       __vector inData2;
      inAddr = rhoCount * 2 * VCOP_SIMD_WIDTH +   TRANSPOSE_STRIDE * i ;

      inData1 = interimTransposeBuf1[inAddr].npt();
      inData2 = interimTransposeBuf2[inAddr].npt();

      vSum1 += inData1;
      vSum2 += inData2;

    }

    votedRhoArray[addrIn].interleave() = (vSum1, vSum2);
  }

}

