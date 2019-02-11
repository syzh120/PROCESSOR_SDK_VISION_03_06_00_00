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

/*      Copyright (C) 2009-2016 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ALIGN_SIMD(a)     (((a) + VCOP_SIMD_WIDTH-1U) & ~(VCOP_SIMD_WIDTH-1U))

#define MAX_OUTPUT_VALUE (32767)
#define MIN_OUTPUT_VALUE (-32768)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_tx_decoding_kernel
 *
 *  @desc     This kernel does tx decoding by multiplying data received by all the receivers
 *                 by a matrix of dimens tx X tx. This kernel has a foreach loop and each iteration
 *                works on 8 points at a time
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This data is an array of pointers. for kth for each iteration
 *                          the pointer in this array buffer should point to k * VCOP_SIMD_WIDTH
 *                          Size of this buffer should be numTx * numRx * numHorzPtPerAntenna * sizeof(int16_t) * 2 * numRows
 *
 *                  txDecodingCoeff :
 *                          Pointer storing the coefficient of tx decoding.
 *                          Size of this buffer should be numTx * numTx
 *
 *                  numTx :
 *                          Number of transmitters in the sytem
 *                  numRx :
 *                          Number of receivers in the sytem
 *                  numRows :
 *                          Number of rows to work with
 *                  numHorzPtPerAntenna :
 *                          Number of horizontal points in the input buffer per antenna
 *                  offsetBwTx :
 *                          Offset in bytes between two transmitter data
 *                  offsetBwRx :
 *                          Offset in bytes between two receiver data
 *                  pitch :
 *                          Offset in bytes to jump from one line to next line
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  None
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Output buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. This data is an array of pointers. for kth for each iteration
 *                          the pointer in this array buffer should point to k * VCOP_SIMD_WIDTH
 *                          Size of this buffer should be numTx * numRx * numHorzPtPerAntenna * sizeof(int16_t) * 2 * numRows
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                         inputData : IBUFLA
 *                         outputData : IBUFHA
 *                         txDecodingCoeff : WMEM
 *
 *  @constraints Following constraints
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_tx_decoding_kernel
(
  __vptr_int16_arr inputData,
  __vptr_int16     txDecodingCoeff,
  __vptr_int16_arr outputData,
  unsigned short  numTx,
  unsigned short  numRx,
  unsigned short  numRows,
  unsigned short  numHorzPtPerAntenna,
  unsigned short  offsetBwTx,
  unsigned short  offsetBwRx,
  unsigned short  pitch
)
{
  __vector VDataR;
  __vector VDataI;
  __vector VTxCoeff;
  __vector VOutR;
  __vector VOutI;

  __agen inAddr;
  __agen coeffAddr;
  __agen outAddr;

  foreach(I0, numHorzPtPerAntenna/ VCOP_SIMD_WIDTH, 4)
  {
    for ( int rowIdx = 0; rowIdx < numRows; rowIdx++)
    {
      for ( int rxIdx = 0; rxIdx < numRx; rxIdx++)
      {
        for ( int txOutIdx = 0; txOutIdx < numTx; txOutIdx++)
        {
          VOutR = 0;
          VOutI = 0;

          for ( int txInIdx = 0; txInIdx < numTx; txInIdx++)
          {
            inAddr = txInIdx * offsetBwTx +
                     rxIdx * offsetBwRx +
                     rowIdx * pitch;

            coeffAddr = txInIdx * numTx * sizeof(*txDecodingCoeff) +
                        txOutIdx * sizeof(*txDecodingCoeff);
            (VDataR, VDataI) = inputData[I0][inAddr].deinterleave();
            VTxCoeff         = txDecodingCoeff[coeffAddr].onept();

            VOutR += (VDataR * VTxCoeff).round(15);
            VOutI += (VDataI * VTxCoeff).round(15);
          }

          outAddr = txOutIdx * offsetBwTx+
                    rxIdx * offsetBwRx+
                    rowIdx * pitch;

          outputData[I0][outAddr].interleave() = (VOutR, VOutI);

        }
      }
    }
  }
}

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_peak_detection_energy_across_antenna
 *
 *  @desc     This kernel computes the energy at each point and sum the energy
 *                across all antenna for the same point
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputData :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension  numAntennas x numDetections.
 *                          Size of this buffer should be numHorzPtPerAntenna *numRows * numAntennas * sizeof(int16_t) * 2
 *                  numRows :
 *                          Number of rows in the input block
 *                  numAntennas :
 *                          Total number of antennnas in the system
 *                  numHorzPtPerAntenna :
 *                          Number of horizontal points in the input buffer per antenna
 *                  pitch :
 *                          Offset in bytes to jump from one line to next line in input buffer
 *
 *  @scratch   This kernel needs  following scratch buffers
 *
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output energy of this kernel which is
 *                          stored in uint32_t container.
 *                          Size of this buffer should be ( (numRows * numHorzPtPerAntenna) * size(uint32_t) )
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                         inputData, outputData should be in different memory
 *
 *  @constraints Following constraints
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_energy_across_antenna
(
  __vptr_int16    inputData,
  __vptr_uint32   outputData,
  unsigned short  numRows,
  unsigned short  numAntennas,
  unsigned short  numHorzPtPerAntenna,
  unsigned short  pitch
)
{
  __agen addr0;
  __vector VInDataReal1;
  __vector VInDataImg1;

  __vector VInDataReal2;
  __vector VInDataImg2;

  __vector VOutEnergy1;
  __vector VOutEnergy2;


  __agen inAddr;
  __agen outAddr;

  /* Processing two rows at a time */
  for ( int rowIdx = 0; rowIdx< numRows/2; rowIdx++)
  {
    for ( int idx = 0; idx < (numHorzPtPerAntenna/ VCOP_SIMD_WIDTH); idx++)
    {
      VOutEnergy1 = 0;
      VOutEnergy2 = 0;
      for ( int antennaIdx = 0; antennaIdx < numAntennas; antennaIdx++)
      {
        inAddr = antennaIdx * numHorzPtPerAntenna * sizeof(*inputData) * 2 +
                 idx * VCOP_SIMD_WIDTH * sizeof(*inputData) * 2 +
                 rowIdx * pitch * 2;/* as we are working with 2 rows at a time */

        (VInDataReal1, VInDataImg1) = inputData[inAddr].deinterleave();
        (VInDataReal2, VInDataImg2) = (inputData + pitch)[inAddr].deinterleave();

        VOutEnergy1 += VInDataReal1 * VInDataReal1;
        VOutEnergy2 += VInDataReal2 * VInDataReal2;

        VOutEnergy1 += VInDataImg1 * VInDataImg1;
        VOutEnergy2 += VInDataImg2 * VInDataImg2;
      }

      outAddr = idx * VCOP_SIMD_WIDTH * sizeof(*outputData)  +
                rowIdx * sizeof(*outputData) * numHorzPtPerAntenna * 2;/* as we are working with 2 rows at a time */

      outputData[outAddr] = VOutEnergy1.saturate();
      (outputData + sizeof(*outputData) * numHorzPtPerAntenna)[outAddr] = VOutEnergy2.saturate();
    }
  }
}




/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_peak_detection_binlog_energy_scaling
 *
 *  @desc     This kernel computes computes the log2 of energy (32 bit) and store the output in 16 bit
 *                container. Following is the explanation of this kernel
 *                Binary Log can be computed as follows (log used here is log in base 2
 *                Any number X can be written as 2^m ( 1 + aplha) where 0<= alpha < 1
 *                log X = m + log ( 1 + aplha)
 *                If n is preccision for alpha, i.e. we  have 2^n enteries in lookup table to store log(1+aplha)
 *                log X =~ m + log (  1 + (floor(2^n * alpha)) / 2^n)
 *                Index for LUT is in Qn format  alpha = (X * 2^n/ 2^m ) - 2^n
 *                Which can also be written as X>> (m -n) - 2^n
 *                Here we can avoid substraction by 2^n if we store index as 1+alpha
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy :
 *                          Input buffer containing data 16 bit signed data with real and imaginary part
 *                          interleaved. Input buffer is of dimension  numAntennas x numDetections.
 *                          Size of this buffer should be numHorzPtPerAntenna *numRows * numAntennas * sizeof(int16_t) * 2
 *                  lutTable :
 *                          LUT table to store the LUT of log (  1 + (floor(2^n * alpha)) / 2^n). LUT values are stored in Q format
 *                           which is given by lutQFormat parameter. The index of LUT will be given by 1+alpha.
 *                           Size of this buffer should be 2 * ( 1<< alphaQFormat). Multiplication by 2 because we are allocating
 *                          double the size of LUT so that we can avoid substraction by 2^n
 *                  scatterIndex :
 *                          Pointer to the index to be used for pScatter. This should be such that
 *                           all 8 lanes of a vector goes to different memory bank.
 *                           size of this buffer should be VCOP_SIMD_WIDTH * sizeof(uint16_t)
 *                  outputPitch :
 *                          Pitch in bytes used to store the output as transpose. Pitch should be chosen in a way
 *                          that it is greater than 9 ( in terms of number of words) and is an odd number
 *                  lutQFormat :
 *                          Q Format to be used to store the LUT table
 *                  alphaQFormat :
 *                          Q Format to be used finding the index corresponding to LUT table
 *                  numRows :
 *                          Number of rows in the input block
 *                  numHorzPtPerAntenna :
 *                          Number of horizontal points in the input buffer per antenna
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  indexBuf
 *                        This is a scratch buf used to store the index for LUT table
 *                  lutValue
 *                        This is a scratch buf used to store the LUT value after reading from LUT table
 *  @outputs   This kernel produce following outputs
 *                  outputData
 *                          Pointer to the output buffer containing the output energy of this kernel which is
 *                          stored in uint32_t container.
 *                          Size of this buffer should be ( (numRows * numHorzPtPerAntenna) * size(uint32_t) )
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputEnergy : IBUFLA
 *                 indexBuf : IBUFLA
 *                 lmbdBuf : WMEM
 *                 lutTable : WMEM
 *                 scatterIndex : WMEM
 *                 outputEnergy : IBUFHA
 *
 *  @constraints Following constraints
 *                numHorzPtPerAntenna should be multiple of VCOP_SIMD_WIDTH
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_binlog_energy_scaling
(
  __vptr_uint32   inputEnergy,
  __vptr_uint16   indexBuf,
  __vptr_uint8    lmbdBuf,
  __vptr_uint16   lutTable,
  __vptr_uint16   lutValue,
  __vptr_uint16   scatterIndex,
  __vptr_uint16   outputEnergy,
  unsigned short  outputPitch,
  unsigned char   lutQFormat,
  unsigned char   alphaQFormat,
  unsigned short  numRows,
  unsigned short  numHorzPtPerAntenna
)
{
  __agen addr0;
  __vector VInEnergy1;
  __vector VInEnergy2;


  __vector VM1, VM2;
  __vector VN, VK1;

  __vector VShift1, VShift2;
  __vector VIndex1, VIndex2;

  VK1 = 1;
  VN  = alphaQFormat;
  addr0 = 0;

  for ( int rowIdx = 0; rowIdx< numRows/2; rowIdx++)
  {
    for ( int idx = 0; idx < (numHorzPtPerAntenna/ VCOP_SIMD_WIDTH); idx++)
    {
      __agen inAddr;
      __agen indexAddr;
      __agen lmbdAddr;

      inAddr = idx * VCOP_SIMD_WIDTH * sizeof(*inputEnergy) +
               rowIdx * sizeof(*inputEnergy) *  numHorzPtPerAntenna * 2;

      lmbdAddr = idx * VCOP_SIMD_WIDTH * sizeof(*lmbdBuf) +
                rowIdx * sizeof(*lmbdBuf) * numHorzPtPerAntenna * 2;

      indexAddr = idx * VCOP_SIMD_WIDTH * sizeof(*indexBuf)+
                rowIdx * sizeof(*indexBuf) * numHorzPtPerAntenna * 2;

      VInEnergy1 = inputEnergy[inAddr];
      VInEnergy2 = (inputEnergy + sizeof(*inputEnergy) *  numHorzPtPerAntenna)[inAddr];

      VM1 = leading_bit(VInEnergy1, VK1);
      VM2 = leading_bit(VInEnergy2, VK1);

      VShift1 = VN - VM1; /* calculate the negative shift for doing right shift */
      VShift2 = VN - VM2;

      VIndex1 = VInEnergy1 << VShift1;
      VIndex2 = VInEnergy2 << VShift2;

      lmbdBuf[lmbdAddr]   = VM1.saturate();/* Saturate to make -1 value to zero. This case will happen when energy is zero */
      (lmbdBuf + sizeof(*lmbdBuf) * numHorzPtPerAntenna)[lmbdAddr]   = VM2.saturate();/* Saturate to make -1 value to zero. This case will happen when energy is zero */
      indexBuf[indexAddr] = VIndex1;
      (indexBuf + sizeof(*indexBuf) * numHorzPtPerAntenna)[indexAddr] = VIndex2;
    }
  }

#define NUM_TBLS (8U)
#define NUM_PTS_TLU (1U)

  _LOOKUP(NUM_TBLS, NUM_PTS_TLU);
  for ( int idx = 0; idx < ((numHorzPtPerAntenna *numRows ) / (VCOP_SIMD_WIDTH)); idx++)
  {
    __agen indexAddr;
    __agen tableAddr;
    __agen outAddr;

    __vector VIndex;
    __vector VLUTvalue;

    indexAddr = idx * VCOP_SIMD_WIDTH * sizeof(*indexBuf);

    outAddr = idx * VCOP_SIMD_WIDTH * sizeof(*lutValue);


    tableAddr = 0;

    VIndex = indexBuf[indexAddr];
    VLUTvalue = lutTable[tableAddr].lookup(VIndex);
    lutValue[outAddr].table_npt() = VLUTvalue;
  }

  __vector VScatterIndex;

  VScatterIndex = scatterIndex[addr0].npt();

/* Processing two rows at a time */
  for ( int rowIdx = 0; rowIdx< numRows/2; rowIdx++)
  {
    for ( int idx = 0; idx < (numHorzPtPerAntenna/ VCOP_SIMD_WIDTH); idx++)
    {
      __agen lmbdAddr;
      __agen lutValAddr;
      __agen outAddr;

      __vector VIndex;
      __vector VLutValue1, VLutValue2;
      __vector VOutEnergy1, VOutEnergy2;
      __vector VLutQFormat;

      lmbdAddr = idx * VCOP_SIMD_WIDTH * sizeof(*lmbdBuf) +
                rowIdx * sizeof(*lmbdBuf) * numHorzPtPerAntenna * 2;

      lutValAddr = idx * VCOP_SIMD_WIDTH * sizeof(*indexBuf) +
                rowIdx * sizeof(*indexBuf) * numHorzPtPerAntenna * 2;

      outAddr = idx * outputPitch * VCOP_SIMD_WIDTH +
                rowIdx * sizeof(*outputEnergy) * 2;

      VLutQFormat = lutQFormat;

      VM1 = lmbdBuf[lmbdAddr];
      VM2 = (lmbdBuf + sizeof(*lmbdBuf) * numHorzPtPerAntenna)[lmbdAddr];

      VLutValue1 = lutValue[lutValAddr];
      VLutValue2 = (lutValue + sizeof(*lutValue) * numHorzPtPerAntenna)[lutValAddr];

      VM1 = VM1 << VLutQFormat;
      VM2 = VM2 << VLutQFormat;

      VOutEnergy1 = VM1 + VLutValue1;
      VOutEnergy2 = VM2 + VLutValue2;

      outputEnergy[outAddr].p_scatter(VScatterIndex) = VOutEnergy1;
      (outputEnergy + sizeof(*outputEnergy))[outAddr].p_scatter(VScatterIndex) = VOutEnergy2;

    }
  }
}


#define VCOP_2SIMD_WIDTH (2*VCOP_SIMD_WIDTH)
/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_peak_detection_cell_sum
 *
 *  @desc     This kernel computes computes the cell sum using the energy buffer
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy1 :
 *                          Input buffer containing data 16 bit energy of first (numVertPoint/2) rows
 *                          Size of this buffer should be numHorzPoint *(numVertPoint /2) * sizeof(uint16_t)
 *                  inputEnergy2 :
 *                          Input buffer containing data 16 bit energy of  (numVertPoint/2 + 1) to
 *                          numVertPoint rows.
 *                          Size of this buffer should be numHorzPoint *(numVertPoint /2)  * sizeof(uint16_t)
 *                  noiseLen :
 *                          Noise length to be used to calculate the nosie floor
 *                  gaurdLen :
 *                          gaurd length to be used to to skip gaurd cells
 *                  numHorzPoint :
 *                          Number of horizontal points in the input block
 *                  numVertPoint :
 *                          Number of rows in the input block
 *                  inputDataPitch :
 *                          Offset in bytes to jump from one line to other line in input buffer
 *                  cellSumPitch :
 *                          Offset in bytes to jump from one line to other line in cell sum buffer
 *                  shift :
 *                         Shift to be applied to the output
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  NONE
 *
 *  @outputs   This kernel produce following outputs
 *                  cellSum
 *                          Pointer to the output buffer containing the cell sum of this kernel which is
 *                          stored in uint16_t container.
 *                          Size of this buffer should be ( ((numVertPoint + 2 * (noiseLen + gaurdLen)) *
 *                          numHorzPtPerAntenna) * size(uint16_t) )
 *                  cellSumOneLine
 *                          This buffer stores a copy of cell sum for initial one line for both energy1 and energy2
 *                          buffers without doing any saturation.
 *                          Size of this buffer should be ( (numHorzPtPerAntenna) * size(uint32_t) * 2 )
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputEnergy1 : IBUFLA
 *                 inputEnergy2 : IBUFHA
 *                 cellSum : WMEM
 *                 cellSumOneLine : IBUFHA
 *
 *  @constraints Following constraints
 *                numHorzPoint should be multiple of VCOP_SIMD_WIDTH
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_cell_sum
(
  __vptr_uint16   inputEnergy1,
  __vptr_uint16   inputEnergy2,
  __vptr_uint16   cellSum,
  __vptr_uint32   cellSumOneLine,
  unsigned short  noiseLen,
  unsigned short  gaurdLen,
  unsigned short  numHorzPoint,
  unsigned short  numVertPoint,
  unsigned short  inputDataPitch,
  unsigned short  cellSumPitch,
  unsigned short  shift
)
{

  __agen addr0;
  __vector VOut1,VOut2;
  __vector VSum1,VSum2;

  /* Find the sum of first noiseLen rows */
  for ( int horzIdx = 0; horzIdx < numHorzPoint/VCOP_SIMD_WIDTH;horzIdx++)
  {
    __agen addrOut1;
    __agen addrOut2;
    VSum1 = 0;
    VSum2 = 0;
    for ( int idx = 0; idx< noiseLen;idx++)
    {
      __agen addrIn;
      __vector VIn1, VIn2;
      __vector VInPlusN1, VInPlusN2 ;

      addrIn = horzIdx * sizeof(*inputEnergy1) * VCOP_SIMD_WIDTH +
               idx * inputDataPitch;

      VIn1 = inputEnergy1[addrIn].npt();
      VIn2 = inputEnergy2[addrIn].npt();

      VSum1 = VSum1 + VIn1;
      VSum2 = VSum2 + VIn2;
    }
    addrOut1 = horzIdx * sizeof(*cellSum) * VCOP_SIMD_WIDTH;
    addrOut2 = horzIdx * sizeof(*cellSumOneLine) * VCOP_SIMD_WIDTH;

    (cellSum + ((noiseLen + gaurdLen)* cellSumPitch))[addrOut1].npt() =  VSum1.saturate(0,0x00007FFF).truncate(shift);
    (cellSum + (((numVertPoint/2)+ (noiseLen + gaurdLen)) * cellSumPitch))[addrOut1].npt() =  VSum2.saturate(0,0x00007FFF).truncate(shift);
    /* Store the first row sum without saturation also so that all subsequent sum are correct */
    cellSumOneLine[addrOut2].npt() = VSum1;
    (cellSumOneLine + numHorzPoint * sizeof(*cellSumOneLine))[addrOut2].npt() = VSum2;

  }

  /* Now cell sum can be found by adding new row and substracting the previous row */
  for ( int horzIdx = 0; horzIdx < numHorzPoint/ VCOP_SIMD_WIDTH;horzIdx++)
  {
     __agen addrFirstRow = horzIdx * sizeof(*cellSumOneLine)* VCOP_SIMD_WIDTH;

    VSum1 = cellSumOneLine[addrFirstRow].npt();
    VSum2 = (cellSumOneLine + numHorzPoint * sizeof(*cellSumOneLine))[addrFirstRow].npt();

    for ( int vertIdx = 0; vertIdx < (numVertPoint/2) - 1;vertIdx++)
    {
      __agen addrIn;
      __agen addrOut;
      __vector VIn1, VIn2;
      __vector VInPlusN1, VInPlusN2 ;

      addrIn  = horzIdx * sizeof(*inputEnergy1) * VCOP_SIMD_WIDTH +
                (vertIdx)* inputDataPitch;

      addrOut = horzIdx * sizeof(*cellSum) * VCOP_SIMD_WIDTH + (vertIdx) * cellSumPitch;


      VIn1      = inputEnergy1[addrIn];
      VIn2      = inputEnergy2[addrIn];
      VInPlusN1 = (inputEnergy1 + noiseLen * inputDataPitch)[addrIn].npt();
      VInPlusN2 = (inputEnergy2 + noiseLen * inputDataPitch)[addrIn].npt();

      VSum1 = VSum1 - VIn1;
      VSum2 = VSum2 - VIn2;

      VSum1 = VSum1 + VInPlusN1;
      VSum2 = VSum2 + VInPlusN2;

      /* saturate the output to 15 bit unsigned number just to make sure that noise floor will never
      reach beyond 16 bit otherwise EVE multiplier will fail */
      (cellSum + ((noiseLen + gaurdLen + 1)* cellSumPitch))[addrOut] = VSum1.saturate(0,0x00007FFF).truncate(shift);
      (cellSum + (((numVertPoint/2)+ (noiseLen + gaurdLen) + 1)* cellSumPitch))[addrOut] = VSum2.saturate(0,0x00007FFF).truncate(shift);
    }
  }


  /* Pad Cell cum buffer by duplicating the rows till noiseLen + gaurdLen on both side of the cell sum buffer ( in vertical direction) */
  for ( int horzIdx = 0; horzIdx < numHorzPoint/VCOP_SIMD_WIDTH;horzIdx++)
  {
    __agen addrOut;
    VSum1 = 0;
    VSum2 = 0;
    for ( int idx = 0; idx< noiseLen + gaurdLen ;idx++)
    {
      __agen addrIn;
      __vector VIn1, VIn2;
      __vector VInPlusN1, VInPlusN2 ;

      addrIn = horzIdx * sizeof(*cellSum) * VCOP_SIMD_WIDTH +
               idx * (cellSumPitch);
      addrOut = horzIdx * sizeof(*cellSum) * VCOP_SIMD_WIDTH +
                     idx * (cellSumPitch);

      VIn1 = (cellSum + (noiseLen + 2 * gaurdLen + 1) * cellSumPitch)[addrIn].npt();
      VIn2 = (cellSum + (numVertPoint - 1 * (noiseLen + gaurdLen)) * cellSumPitch)[addrIn].npt();

      cellSum[addrOut] = VIn1;
      (cellSum + (numVertPoint + 1 + gaurdLen) * cellSumPitch)[addrOut] = VIn2;


    }

  }

}

#define PEAK_DETECTION_MAX_NUM_DETECTION (2000 / VCOP_SIMD_WIDTH)

/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_peak_detection_CFARCA_thresholding
 *
 *  @desc     This kernel does CFAR CA detector and store the output coordinates
 *
 *  @inputs   This kernel takes following Inputs
 *                  inputEnergy :
 *                          Input energy buffer containing 16 bit energy
 *                          Size of this buffer should be numHorzPoint *numVertPoint  * sizeof(uint16_t)
 *                  cellSum :
 *                          Buffer which stores the cell sum computed byt the previous kernel
 *                         Size of this buffer should be ( ((numVertPoint + 2 * (noiseLen + gaurdLen)) *
 *                          numHorzPtPerAntenna) * size(uint16_t) )
 *                  idxBuf :
 *                         Buffer to store the index of doppler dimension.Refer testbench to see how it is
 *                         computed
 *                         Size of this buffer should be ( numHorzPtPerAntenna * 2 * size(uint16_t) )
 *                  dopplerIdxOffsetBuf :
 *                         Offset to be added to the doppler index
 *                         Size of this buffer should be  size(uint32_t) )
 *                  numDetections :
 *                         Buffer to store the number of detections
 *                         Size of this buffer should be ( VCOP_SIMD_WIDTH * 2 * size(uint16_t) )
 *                  offsetBwTwoInBuf :
 *                          Offset in bytes between inputEnergy1 and inputEnergy2 as used in vcop_peak_detection_cell_sum kernel
 *                  noiseLen :
 *                          Noise length to be used to calculate the nosie floor
 *                  gaurdLen :
 *                          gaurd length to be used to to skip gaurd cells
 *                  numHorzPointActual :
 *                          Number of actual horizontal points in the input block
 *                  numHorzPoint :
 *                          Number of horizontal points in the input block. when numHorzPointActual == 8
 *                          then numHorzPoint = 16 rest all cases numHorzPoint =  8
 *                  numVertPointActual :
 *                          Number of actual vertical in the input block.
 *                  numVertPoint :
 *                          Number of vertical in the input block. When numHorzPointActual == 8
 *                          then numVertPoint = numVertPointActual / 2 rest all cases numVertPoint =  numVertPointActual
 *                  cellSumPitchActual :
 *                          Actual Offset in bytes to jump from one line to other line in cell sum buffer
 *                  cellSumPitch :
 *                          When numHorzPointActual == 8.
 *                           then cellSumPitch = cellSumPitchActual *2 rest all cases cellSumPitch =  cellSumPitchActual
 *                  inputDataPitchActual :
 *                          Actual Offset in bytes to jump from one line to other line input buffer
 *                  inputDataPitch :
 *                          When numHorzPointActual == 8.
 *                           then inputDataPitch = inputDataPitchActual *2 rest all cases inputDataPitch =  inputDataPitchActual
 *                  vertCoordinateShift :
 *                           A value of 16 indicates that horz corrdinate is stored in upper 16 bit and
 *                           vert coordinate is stored in lower 16 bit. A value of 0 indicates that horz coordinate is stored
 *                            in lower 16 bit and vertical coordinate is stored in upper 16 bits
 *                 horzIdxUpdateOffset :
 *                             Amount to add to the horizontal offset after each kernel call. For doppler case this should be set to
 *                            zero.
 *                  threshold :
 *                         Threshold to be used for CFAR CA DB.
 *                          Original equation of CFAR CA detector is CUT > T * NF, where T can be written as C1/ 2^C2
 *                          Same equation in log domain becomes
 *                          log(CUT)> log(T) + log(NF)
 *                          =  log(CUT) -  log(NF)> log(C1) - C2
 *                          So threshold here is log(C1) - C2.
 *                          Q format for threshold should be same as lutQFormat used during energy computation
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                  binaryMask
 *                          Buffer to store the binary mask
 *                          Size of this buffer should be numHorzPoint * numVertPoint
 *
 *  @outputs   This kernel produce following outputs
 *                  outRangeDopplerBuf
 *                          Pointer to the output buffer storing the range and doppler coordinate  for each detection
 *                  outEnergyBuf
 *                          Pointer to the output buffer storing the energy for each detection
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                 inputEnergy : IBUFLA and IBUFHA
 *                 cellSum : WMEM
 *                 binaryMask : WMEM
 *                 outRangeDopplerBuf : IBUFLA
 *                 outEnergyBuf: IBUFHA
 *                 dopplerIdxOffsetBuf : WMEM
 *                  numDetections : IBUFHA
 *  @constraints Following constraints
 *                numHorzPoint should be multiple of VCOP_SIMD_WIDTH ( an power of 2.
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_peak_detection_CFARCA_thresholding
(
  __vptr_uint16   inputEnergy,
  __vptr_uint16   cellSum,
  __vptr_uint8    binaryMask,
  __vptr_uint32   outRangeDopplerBuf,
  __vptr_uint16   outEnergyBuf,
  __vptr_uint32   idxBuf,/* Store index left shifted by 16*/
  __vptr_uint32   horzIdxOffsetBuf,
  __vptr_uint16   numDetections,
  unsigned int     offsetBwTwoInBuf,
  unsigned short   noiseLen,
  unsigned short   gaurdLen,
  unsigned short   numHorzPointActual,
  unsigned short   numHorzPoint,
  unsigned short   numVertPointActual,
  unsigned short   numVertPoint,
  unsigned short   cellSumPitchActual,
  unsigned short   cellSumPitch ,
  unsigned short   inputDataPitchActual,
  unsigned short   inputDataPitch,
  unsigned short   vertCoordinateShift,
  unsigned short   horzIdxUpdateOffset,
  signed short   threshold
)
{
  __vector VLeftNoiseFloor1, VLeftNoiseFloor2;
  __vector VRightNoiseFloor1, VRightNoiseFloor2;
  __vector VCutVal1, VCutVal2;
  __vector VNoiseFloor1, VNoiseFloor2;
  __vector VMask1, VMask2;
  __vector VThreshold;
  __vector VMaxNumDetections;
  __vector VExitCondition;
  __agen addr0 = 0;


  for( int bufIdx = 0; bufIdx < 2; bufIdx++)
  {
    for ( int dopplerIdx = 0; dopplerIdx < numHorzPoint /VCOP_2SIMD_WIDTH;dopplerIdx++)
    {
      for ( int rangeIdx = 0; rangeIdx < numVertPoint/2;rangeIdx++)
      {
        __agen addrNoiseFloor;
        __agen addrEnergy;
        __agen addrMask;

        addrNoiseFloor = rangeIdx * cellSumPitch +
                         dopplerIdx * VCOP_2SIMD_WIDTH * sizeof(*cellSum) +
                         bufIdx * (numVertPoint/2) * cellSumPitch;

        addrEnergy     = rangeIdx * inputDataPitch +
                         dopplerIdx * VCOP_2SIMD_WIDTH * sizeof(*inputEnergy) +
                         bufIdx * offsetBwTwoInBuf;

        addrMask        = rangeIdx * numHorzPoint * sizeof(*binaryMask) +
                         dopplerIdx * VCOP_2SIMD_WIDTH * sizeof(*binaryMask) +
                         bufIdx * (numVertPoint/2) * numHorzPoint * sizeof(*binaryMask)  ;

        (VLeftNoiseFloor1, VLeftNoiseFloor2)   = cellSum[addrNoiseFloor].deinterleave();
        (VRightNoiseFloor1, VRightNoiseFloor2) = (cellSum + ( noiseLen + (2 * gaurdLen + 1)) * cellSumPitchActual )[addrNoiseFloor].deinterleave();
        (VCutVal1,VCutVal2) = (inputEnergy)[addrEnergy].deinterleave();

        VThreshold = threshold;

        VMask1 = 0;
        VMask2 = 0;

        VNoiseFloor1 = VLeftNoiseFloor1 + VRightNoiseFloor1;
        VNoiseFloor2 = VLeftNoiseFloor2 + VRightNoiseFloor2;

        VCutVal1 = VCutVal1 - VNoiseFloor1;
        VCutVal2 = VCutVal2 - VNoiseFloor2;

        VMask1 = ( VCutVal1 > VThreshold);
        VMask2 = ( VCutVal2 > VThreshold);

        binaryMask[addrMask].interleave() = (VMask1, VMask2);
      }
    }
  }

  __vector VMask;
  __vector VFinalHorzIdx;
  __vector VEnergy;
  __vector VVertIdx;
  __vector VHorzIdx;
  __vector VNoiseLen;
  __vector VGaurdLen;
  __vector VRangeDoppler;
  __vector VCurrHorzIdx;
  __vector VVertCoordinateShift;
  __vector VNumDetections;

  VNoiseLen = noiseLen;
  VGaurdLen = gaurdLen;
  VVertCoordinateShift = vertCoordinateShift;

  VExitCondition = 0;
  VNumDetections = 0;
  VMaxNumDetections = PEAK_DETECTION_MAX_NUM_DETECTION;

  VCurrHorzIdx = horzIdxOffsetBuf[addr0].onept();
  for( int bufIdx = 0; bufIdx < 2; bufIdx++)
  {
    for ( int horzIdx = 0; horzIdx < numHorzPointActual / VCOP_SIMD_WIDTH;horzIdx++)
    {
      __agen addrIdx;
      addrIdx = horzIdx * VCOP_SIMD_WIDTH * sizeof(*idxBuf) +
                bufIdx * numHorzPointActual * sizeof(*idxBuf);

      VHorzIdx = idxBuf[addrIdx].npt();

      for ( int vertIdx = 0; vertIdx < numVertPointActual/2;vertIdx++)
      {
        __agen addrMask;

        __agen addrEnergy;

        addrMask = vertIdx * numHorzPointActual * sizeof(*binaryMask) +
                   horzIdx * VCOP_SIMD_WIDTH * sizeof(*binaryMask) +
                   bufIdx * numHorzPointActual * sizeof(*binaryMask) * (numVertPointActual/2);


        addrEnergy = vertIdx * inputDataPitchActual +
                   horzIdx * VCOP_SIMD_WIDTH * sizeof(*inputEnergy) +
                   bufIdx * offsetBwTwoInBuf;

        VMask = binaryMask[addrMask].npt();

        VEnergy = (inputEnergy)[addrEnergy].npt();

        VVertIdx = vertIdx;

        VVertIdx = VVertIdx << VVertCoordinateShift;
        VFinalHorzIdx  = VHorzIdx + VCurrHorzIdx;

        VRangeDoppler = VVertIdx + VFinalHorzIdx;

        VNumDetections += VMask;

        VExitCondition = pack ( VNumDetections >= VMaxNumDetections );

        outRangeDopplerBuf[collate(VMask)] = VRangeDoppler;
        outEnergyBuf[collate(VMask)] = VEnergy;
        numDetections[addr0]         = VNumDetections;

        if (VExitCondition[0]) goto end_loop; /* we don't want to add more elements if maxNumElmts reached */
      }
    }
  }

end_loop:;


  VCurrHorzIdx = horzIdxOffsetBuf[addr0].onept();

  __vector VNumHorzPt;
  __vector VUpdateDopplerIdx;
  VNumHorzPt = horzIdxUpdateOffset;

  for(int i = 0; i < 1; i++)
  {
      __vector VTotalDetections;
      VTotalDetections = 0;

      for(int j = 0; j < 8; j++)
      {
          __agen addrIn;

          addrIn = j * sizeof(*numDetections);
          VNumDetections = (numDetections)[addrIn].onept();
          VTotalDetections += VNumDetections;

          VUpdateDopplerIdx  = VCurrHorzIdx + VNumHorzPt;

      }
      numDetections[addr0].onept() = VTotalDetections;
      horzIdxOffsetBuf[addr0].onept() = VUpdateDopplerIdx;
  }
}


void vcop_peak_detection_transpose
(
  __vptr_uint16   inputEnergy1,
  __vptr_uint16   inputEnergy2,
  __vptr_uint16   outputEnergy,
  __vptr_uint16   scatterIndex,
  unsigned short  numHorzPoint,
  unsigned short  numVertPoint,
  unsigned short  transposePitch,
  unsigned short  numExtraLines
)
{
  __vector VIn1, VIn2;
  __agen   addr0;
  __vector VScatterIndex;

  addr0 = 0;
  VScatterIndex = scatterIndex[addr0].npt();

  for ( int horzIdx = 0; horzIdx < numHorzPoint/(2 * VCOP_SIMD_WIDTH);horzIdx++)
  {
    for ( int vertIdx = 0; vertIdx < (numVertPoint);vertIdx++)
    {
      __agen addrIn  = vertIdx * (numHorzPoint/2) * sizeof(*inputEnergy1) +
                       horzIdx * VCOP_SIMD_WIDTH * sizeof(*inputEnergy1);
      __agen addrOut = vertIdx * sizeof(*outputEnergy) +
                       horzIdx * VCOP_SIMD_WIDTH * transposePitch;

      VIn1 = inputEnergy1[addrIn].npt();
      VIn2 = inputEnergy2[addrIn].npt();

      outputEnergy[addrOut].p_scatter(VScatterIndex) = VIn1;
      (outputEnergy + transposePitch * (numHorzPoint/2))[addrOut].p_scatter(VScatterIndex) = VIn2;

    }
  }

  __vector VIn3, VIn4;
  __vector VIn5, VIn6;

  for ( int horzIdx = 0; horzIdx < numVertPoint/ VCOP_2SIMD_WIDTH;horzIdx++)
  {
    for ( int vertIdx = 0; vertIdx < (numHorzPoint/2);vertIdx++)
    {
      __agen addrIn  = vertIdx * transposePitch +
                       horzIdx * VCOP_2SIMD_WIDTH * sizeof(*outputEnergy);
      __agen addrOut = vertIdx * numVertPoint * sizeof(*inputEnergy1) +
                       horzIdx * VCOP_2SIMD_WIDTH * sizeof(*inputEnergy1);

      ( VIn3, VIn4 )= outputEnergy[addrIn].deinterleave();
      ( VIn5, VIn6 ) = (outputEnergy + transposePitch * (numHorzPoint/2))[addrIn].deinterleave();

      inputEnergy1[addrOut].interleave() = ( VIn3, VIn4 );
      inputEnergy2[addrOut].interleave() = ( VIn5, VIn6 );
    }
  }

  for ( int horzIdx = 0; horzIdx < numVertPoint/ VCOP_2SIMD_WIDTH;horzIdx++)
  {
    for ( int vertIdx = 0; vertIdx < numExtraLines;vertIdx++)
    {
      __agen addrIn  = (vertIdx)* transposePitch +
                       horzIdx * VCOP_2SIMD_WIDTH * sizeof(*outputEnergy);
      __agen addrOut = vertIdx * numVertPoint * sizeof(*inputEnergy1) +
                       horzIdx * VCOP_2SIMD_WIDTH * sizeof(*inputEnergy1);

      ( VIn3, VIn4 )= (outputEnergy + (numHorzPoint/2) * transposePitch)[addrIn].deinterleave();

      (inputEnergy1 + (numHorzPoint/2)* numVertPoint * sizeof(*inputEnergy1))[addrOut].interleave() = ( VIn3, VIn4 );
    }
  }


}
