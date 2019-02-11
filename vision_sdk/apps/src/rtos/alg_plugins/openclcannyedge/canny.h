/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
#ifndef _OPENCL_CANNY_H_
#define _OPENCL_CANNY_H_

typedef struct
{
	char *data;
	cl_mem buf;
	unsigned int size;
	unsigned int rows;
	unsigned int cols;
	unsigned int steps;
	unsigned int offset;
}opencl_buf;
inline unsigned int divUp(unsigned int total, unsigned int grain);


void calcSobelRowPass_opencl(cl_context, cl_command_queue, cl_kernel, opencl_buf bufsource, opencl_buf bufDxbuf, opencl_buf bufDybuf,
                        UInt32 *inPtr[], UInt32 *outPtr[], UInt32 inPitch[],UInt32 outPitch[]);
void calcMagnitude_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf dxbuf, opencl_buf dybuf, opencl_buf dx, opencl_buf dy, opencl_buf mag,int rwos, int cols, char L2gradient);
void calcMap_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf dx, opencl_buf dy, opencl_buf mag,
                opencl_buf map, int rows, int cols, short low_thresh, short high_thresh,
                UInt32 *inPtr[],UInt32 *outPtr[],UInt32 inPitch[],UInt32 outPitch[],UInt32 numPlanes,UInt32 height,
                UInt32 wordWidth,opencl_buf trackBuf1, opencl_buf counter);

void edgesBlob_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf map,
                 opencl_buf trackBuf1, opencl_buf counter, int rows, int cols);

void getEdges_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf map, opencl_buf dst, int rows, int cols);
void add_ocl_logo(
             UInt32 *inPtr[],
             UInt32 *outPtr[],
             UInt32 inPitch[],
             UInt32 outPitch[]
             );
void set_chroma(
             UInt32 *inPtr[],
             UInt32 *outPtr[],
             UInt32 inPitch[],
             UInt32 outPitch[],
             UInt32 numPlanes,
             UInt32 height,
             UInt32 wordWidth
             );
#endif
