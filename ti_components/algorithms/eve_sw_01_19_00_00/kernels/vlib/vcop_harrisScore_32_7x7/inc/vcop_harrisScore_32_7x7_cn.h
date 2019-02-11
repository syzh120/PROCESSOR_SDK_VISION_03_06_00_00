/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2013 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_harrisScore_32_7x7_CN
#define _vcop_harrisScore_32_7x7_CN  1

int vcop_harrisScore_32_7x7_cn
(
    const short *  gradX,
    const short *  gradY,
    int width,
    int height,
    unsigned int srcPitch,
    unsigned int dstPitch,
    unsigned char windowSize,
    int *  outm,
    unsigned short k
);

/* ==================================================
 *  @function     vcop_harrisScore_32_methodB_cn
 *
 *  @desc     This function calculates the Harris Score defined as the trace of the matrix :
 *                 Score = gradX^2 + gradY^2
 *
 *  @inputs   This kernel takes following Inputs
 *                  gradX :
 *                          Pointer to the gradient in X direction. Size of this buffer should be inBlockWidth * inBlockHeight * sizeof(uint16_t)
 *                  gradY :
 *                          Pointer to the gradient in Y direction. Size of this buffer should be inBlockWidth * inBlockHeight * sizeof(uint16_t)
 *                  inBlockWidth :
 *                          Width of the input block
 *                  inBlockHeight :
 *                          Height of the input block
 *                  srcPitch :
 *                          Pitch of the input block
 *                  dstPitch :
 *                          Pitch for the output score
 *                  windowSize :
 *                          Size of the window. Should be an odd number
 *
 *  @outputs   This kernel produce following outputs
 *                  outm :
 *                          Pointer to the buffer which will store the score caluclated by this kernel. Size of this buffer
 *                          should be (inBlockWidth - (windowSize - 1) )* (inBlockWidth - (windowSize - 1) ) * sizeof(uint32_t))
 *
 *  @constraints Following constraints
 *
 *  @return    NONE
 *
 *  =======================================================
 */
int vcop_harrisScore_32_methodB_cn
(
    const int16_t *gradX,
    const int16_t *gradY,
    uint16_t      inBlockWidth,
    uint16_t      inBlockHeight,
    uint16_t      srcPitch,
    uint16_t      dstPitch,
    uint8_t       windowSize,
    uint32_t      *outm
);

#endif

/* ======================================================================== */
/*            End of file:  vcop_harrisScore_32_7x7_c.h                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
