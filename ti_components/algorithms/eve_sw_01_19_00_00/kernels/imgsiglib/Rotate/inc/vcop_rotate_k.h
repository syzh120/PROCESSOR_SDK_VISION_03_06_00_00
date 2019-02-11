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

#ifndef __TI_ROTATE_K_H__
#define __TI_ROTATE_K_H__

void vcop_rotate_90
(
     __vptr_uint8  in,         //  Pointer to an input array of "in_type".              
     __vptr_uint8  inter,      //  Pointer to intermediate array of "inter_type".       
     __vptr_uint8  out,        //  Pointer to output array of "out_type".               
     int img_w,                //  Width of input image in pixels.                      
     int img_h,                //  Height of the input image in pixels.                 
     int out_w,                //  Width of the output image in pixels.                 
     int out_h,                //  Height of the input image in pixels.                 
     int blk_w,                //  The compute width over which rotate values are found.
     int blk_h,                //  The compute height for rotate function.              
     int in_type,              //  0 - BYTE,  1 - SHORT                                 
     int inter_type,           //  0 - BYTE,  1 - SHORT                                 
     int out_type,             //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT           
     int angle,                //  Angle of rotation, can be 90, 180 or 270.            
     int round_shift           //  Amount of rounding and shifting on output data.      
);

void vcop_rotate_180
(
     __vptr_uint8  in, 
     __vptr_uint8  inter,
     __vptr_uint8  out,
     int img_w,
     int img_h,
     int out_w,
     int out_h,
     int blk_w, 
     int blk_h,
     int in_type,
     int inter_type,
     int out_type,
     int angle,
     int round_shift
);


void vcop_rotate_270
(
     __vptr_uint8  in, 
     __vptr_uint8  inter,
     __vptr_uint8  out,
     int img_w,
     int img_h,
     int out_w,
     int out_h,
     int blk_w, 
     int blk_h,
     int in_type,
     int inter_type,
     int out_type,
     int angle,
     int round_shift
);

#endif
