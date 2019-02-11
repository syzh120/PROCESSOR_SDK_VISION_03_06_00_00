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


/**
 *******************************************************************************
 *  @func          vcop_fast9_cn
 *  @brief         This is natural C implementation of FAST9 corner detection
 *  @param [in]    input   : Pointer to input 8-bit image
 *  @param [in]    output  : Pointer to output binary image
 *
 *  Output format of the buffer is crtical to know. It is as described
 *  OutputWidth of the buffer is ROUNDUP ((in_w-6)/8)
 *  OutputHeight of the buffer is in_h
 *  The way corners are stored are packed..... so pixel 0 being corner
 *  or not is represnted by bit 0 of byte 0 in output buffer. The first byte
 *  bit 0 in output buffer belongs to pixel at (3,3) in input buffer. and per row
 *  key point desiction of width-6 pixels are reported back
 *  since there are possibly width - 6 key points in a line and to fit them in
 *  packed form width-6 has to be multiple of 8. If not then last byte in each
 *  line contains the few extra bits having zero
 *  example if width = 400, then width - 6 = 394. and outwidth would
 *  ROUNDUP(394/8) = 50 and 6 upper bits in last byte would be 0. First byte indicates
 *  cornerness of pixel 3 (bit0),4,5,6,7,8,9,10 (bit7) and it continues...
 *
 *  @param [in]    threshold : Threshold for corner detection
 *  @param [in]    pitch  : Pitch of input buffer
 *  @param [in]    in_w : Width of input buffer for which corner detction has
 *                 to be performed
 *  @param [in]    in_h : Height of input buffer for which corner detction has
 *                 to be performed
 *  @return        None
 *******************************************************************************
 */
#include <stdint.h>

void vcop_fast9_cn
(
 uint8_t *input,
 uint8_t *output,
 uint8_t threshold,
 uint32_t pitch,
 uint32_t in_w,
 uint32_t in_h
) ;
