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
/*  @file : vcop_contrast_stretching_cn.h                                              */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  functions for a contrast stretching.                   */
/*                                                                          */
/*  @version 0.1 (May 2014) : Base version.                                 */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_CONTRAST_STRETCHING_CN_
#define VCOP_CONTRAST_STRETCHING_CN_

#define MAX_PIXEL_VAL (255)

/**
 *******************************************************************************
 *  @func          vcop_histogram_8c_word_cn
 *  @brief         This is function is reference C Implementation of histogram for 8 bit
 *                    gray scale image. This function gives a 32 bit histogram for 8 bit
 *                    input image data.
 *  @param [in]   inputImage : Pointer to input image
 *  @param [in]   width   : Width of input Image
 *  @param [in]   height   : Height of input Image
 *  @param [in]   inPitch   : Pitch of input Image
 *  @param [out] histogram8Copy   : Pointer to the output 8 copy histogram
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t vcop_histogram_8c_word_cn(uint8_t * inputData,
                            uint16_t  width,
                            uint16_t  height,
                            uint16_t  inPitch,
                            uint32_t * histogram8Copy);



/**
 *******************************************************************************
 *  @func          vcop_contrast_stretching_cn
 *  @brief         This is function is reference C Implementation of contrast stretching kernel.
 *  @param [in]   inputImage : Pointer to input image
 *  @param [out] outputImage : Pointer to output image
 *  @param [in]   width   : Width of input Image
 *  @param [in]   height   : Height of input Image
 *  @param [in]   inPitch   : Pitch of input Image
 *  @param [in]   outPitch   : Pitch of output Image
 *  @param [in]  minVal   : Minimum value of the histogram for stretching
 *  @param [in]  scaleFactorQ16   : Scaling factor in Q16 format. Scale factor is
 *                                             calculated using following formula.
 *                               1 / ( maxVal - minVal) in Q16 format;
 *
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t vcop_contrast_stretching_cn(uint8_t * inputImage,
                            uint8_t * outputImage,
                            uint16_t  width,
                            uint16_t  height,
                            uint16_t  inPitch,
                            uint16_t  outPitch,
                            uint32_t  minVal,
                            uint32_t  scaleFactorQ16);

/**
 *******************************************************************************
 *  @func          vcop_histogram_8c_word_sum_cn
 *  @brief         This is function is reference C Implementation of summing 8 histogram
 *                    generated using 8 channel histrogram to generate a single histogram
 *  @param [in] histogram8Copy   : Pointer to the output 8 copy histogram
 *  @param [out] histogram   : Pointer to single copy of histogram
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
void vcop_histogram_8c_word_sum_cn
(
    uint32_t  *histogram8Copy,
    uint32_t  *histogram
);

#endif /* VCOP_CONTRAST_STRETCHING_CN_ */

