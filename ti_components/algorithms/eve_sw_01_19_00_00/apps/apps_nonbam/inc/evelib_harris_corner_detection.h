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


/** @file   evelib_harris_corner_detection.h
 *
 *  @brief  Harris Corner Detection Applet
 *
 *  @date   April 2013
 *
 */

/**
*  @brief      Compute corners for a given grayscale image using 
*              Shi & Tomasi corner detector which is based on Harris
*              Corner Detection algorithm
*
*  @param[in]  src                        source image pointer
*  @param[in]  srcImageWidth              source image width in pixels
*  @param[in]  srcImageHeight             source image height in pixels
*  @param[in]  srcBufferPitch             source buffer pitch in bytes
*  @param[in]  srcBufferHeight            source buffer height in bytes
*  @param[in]  srcBytesPP                 source bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[out] dst                        destimation image pointer
*  @param[in]  dstImageWidth              destination image width in pixels
*  @param[in]  dstImageHeight             destination image height in pixels
*  @param[in]  dstBufferPitch             destination buffer pitch in bytes
*  @param[in]  dstBufferHeight            destination buffer height in bytes
*  @param[in]  srcBlkWidth                block width of the source
*  @param[in]  srcBlkHeight               block height of the source
*  @param[in]  dstBytesPP                 dest bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[in]  harrisScoreScalingFactor   scaling factor used by harris score kernel
*  @param[in]  nmsThresh                  threshold parameter for non maximum suppression kernel
*
*  @remarks    Harris corner detector function.
*  @remarks    Currently, the algorithm works fine when srcImageWidth*srcBytesPP or srcImagePitch is a multiple of 16.
*
*  @sa         EVELIB_algoDMAAutoIncrInit(), EVELIB_algoDMAAutoIncrProcess(), EVELIB_algoDMAAutoIncrDeInit()
*/
void EVELIB_harrisCornerDetection(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcBufferPitch,
    int                 srcBufferHeight,
    unsigned int        srcBytesPP,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstBufferPitch,
    int                 dstBufferHeight,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    unsigned int        dstBytesPP,
    short               harrisScoreScalingFactor,
    short               nmsThresh
    );

