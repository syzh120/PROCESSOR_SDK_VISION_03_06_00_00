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

/*                                                                          */
/*  @file : vcop_binary_masking_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for binary masking kernel.                   */
/*                                                                          */
/*  @version 0.1 (Mar 2015) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_BINARY_MASKING_CN_H_
#define VCOP_BINARY_MASKING_CN_H_


/*-----------------------------------------------------------------------*/
/* ==================================================
 *  @kernel     vcop_binary_masking_cm
 *
 *  @desc     This function does the "AND" operation on a byte mask containing 0 and 1 with
 *                a bit packed mask binary image
 *
 *  @inputs   This kernel takes following Inputs
 *                  inByteData :
 *                          Input byte data containing only 0 and 1
 *                          Size of this buffer should be blockWidth * blockHeight * sizeof(uint8_t)
 *                  inBitPackedData :
 *                          Input bit data containing bit packed data
 *                          Size of this buffer should be blockWidth /8 * blockHeight * sizeof(uint8_t)
 *                  computeWidth :
 *                          Width of the output of this kernel.
 *                  computeHeight :
 *                          Width of the output of this kernel.
 *                  inputByteDataPitch :
 *                          Pitch in bytes for the byte data
 *                  inputBitDataPitch :
 *                          Pitch in bytes for the bit packed data
 *                  outputPitch :
 *                          Pitch of the output data
 *
 *  @scratch   This kernel needs  following scratch buffers
 *                          None
 *
 *  @outputs   This kernel produce following outputs
 *                  outBitPackedData
 *                          Pointer to the output buffer containing the output of this kernel in bit packed data
 *                          Size of this buffer should be ( (computeWidth) / 8 * computeHeight * size(int8_t)
 *
 *  @remarks  Following is the buffer placement assumed for optimal performance of this kernel
 *                          Compute bound case so buffer placement could be anywhere
 *
 *  @constraints Following constraints
 *                          None
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_binary_masking_cn
(
  uint8_t  *inByteData,
  uint8_t  *inBitPackedData,
  uint8_t  *outBitPackedData,
  unsigned short computeWidth,
  unsigned short computeHeight,
  unsigned short inputByteDataPitch,
  unsigned short inputBitDataPitch,
  unsigned short outputPitch
);

#endif /* VCOP_BINARY_MASKING_CN_H_ */

