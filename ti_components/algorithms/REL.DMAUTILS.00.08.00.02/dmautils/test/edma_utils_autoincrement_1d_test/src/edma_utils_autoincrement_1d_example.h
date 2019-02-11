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

/*============================================================================*/
/*============================================================================*/

/**
----------------------------------------------------------------------------
@file    edma_utils_autoincrement_1d_example.h
@brief   Demostrates a simple example of auto increment DMA to allow DSP to
operate a function on internal memory and transfer back the result.
@version 0.0 (Apr 2017) : First version
----------------------------------------------------------------------------
*/

#ifndef EDMA_UTILS_AUTOINCREMENT_1D_EXAMPLE_H_
#define EDMA_UTILS_AUTOINCREMENT_1D_EXAMPLE_H_

/*
 This function accepts an input image in external memory and write back to
 external memory after performing a horizontal flip of the image.
 The function can be called to work on direct external memory with cache
 by setting useDMA = 0
 The function can also be called to work using DMA, in that case user should
 provide internal memory buffer pointed by pIntMmeBase and available size
 by setting intMemSize. In case the internal memory is not sufficient, the
 function returns -1 and prints the required memory size

 whiel using DMA; this function tarnsfers an entire row of data in internal
 memory, then performs the flip operation and writes the result in internal
 memory. The result is then transfered back to external memory using DMA.
 In order to have DMA and CPU operate in parallel, 2 instances of input and
 output are created in internal memory

 The prupose of the function is to act as an example for DMA usage so the
 default core function of fliping the image is in natural C

*/
int32_t flipHorizontal(
  uint8_t*   pInput,
  uint8_t*   pOutput,
  uint16_t   width,
  uint16_t   height,
  uint16_t   inPitch,
  uint16_t   outPitch,
  uint8_t*   pIntMmeBase,
  uint32_t   intMemSize,
  uint8_t    useDMA
  );


#endif /*EDMA_UTILS_AUTOINCREMENT_1D_EXAMPLE_H_*/
