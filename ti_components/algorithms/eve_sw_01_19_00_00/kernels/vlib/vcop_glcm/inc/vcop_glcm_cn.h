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
/*  @file : vcop_glcm_cn.h                                                  */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Gray-level Co-occerence Matrix.                            */
/*                                                                          */
/*  vcop_glcm_cn                                                            */
/*      This is the c-reference for the vcop_glcm kernel. This              */
/*      routine accepts an 8-bit input image and outputs gray-level         */
/*      co-occurrence matrices or gray tone spatial dependency matrices     */
/*      for each of the directions of analysis specified by the user.       */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/*  void vcop_glcm_cn(uint8_t  *pInput,                                     */
/*                    uint16_t *pCoMatrix,                                  */
/*                    uint16_t imageWidth,                                  */
/*                    uint16_t imageHeight,                                 */
/*                    uint16_t imagePitch,                                  */
/*                    uint8_t  numLevels,                                   */
/*                    uint8_t  numOffsets,                                  */
/*                    int8_t*  rowOffsets,                                  */
/*                    int8_t*  colOffsets)                                  */
/*                                                                          */
/*  pInput        :  [in] Pointer to grayscale input image, 8 bit           */
/*                   unsigned. This image will be scaled and quantized      */
/*                   to the range [0, numLevels-1].                         */
/*  pCoMatrix     :  [out] Pointer to output Co-Occurrence Matrices, each   */
/*                   of size numLevels x numLevels. The function outputs    */
/*                   one GLCM matrix per direction of analysis.             */
/*  imageWidth    :  Image width                                            */
/*  imageHeight   :  Image height                                           */
/*  imagePitch    :  Image pitch/stride                                     */
/*  numLevels     :  Number of gray-levels to be used for GLCM computation  */
/*  numOffsets    :  Number of directions over which analysis need to be    */
/*                   performed                                              */
/*  rowOffsets    :  Array of number of rows between the pixel of interest  */
/*                   and its neighbor. The array contains as many elements  */
/*                   as numOffsets.                                         */
/*  colOffsets    :  Array of number of columns between the pixel of        */
/*                   interest and its neighbor. The array contains as many  */
/*                   elements as numOffsets.                                */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*  @version 0.1 (Jan 2014) : Base version.                                 */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_GLCM_CN
#define _VCOP_GLCM_CN

int32_t vcop_glcm_cn(uint8_t  *pInput,
                  uint16_t *pCoMatrix,
                  uint16_t imageWidth,
                  uint16_t imageHeight,
                  uint16_t imagePitch,
                  uint8_t  numLevels,
                  uint8_t  numOffsets,
                  char    *rowOffsets,
                  char    *colOffsets);

#endif /* _VCOP_GLCM_CN */
