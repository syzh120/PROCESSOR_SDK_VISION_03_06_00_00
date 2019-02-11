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
//#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "iOpenClCannyEdgeAlgo.h"
#include <include/link_api/system_trace.h>
#include "opencl_logo.h"
unsigned int divUp(unsigned int total, unsigned int grain)
{
	return (total + grain - 1) / grain;
}

Int32 OpenCl_canny_edgedetect(Alg_OpenCLCannyEdge_Obj *algHandle,
                              UInt32 *inPtr[],
                              UInt32 *outPtr[],
                              UInt32  wordWidth,
                              UInt32  height,
                              UInt32 inPitch[],
                              UInt32 outPitch[],
                              UInt32 numPlanes
                              )
{
    cl_int err     = CL_SUCCESS;
    int count = 1;
    int i;
    Int32 rowIdx;
    Int32 colIdx;
    UInt32 input_width = wordWidth << 2;
    UInt32 input_height = height;

    opencl_buf source, dst;

	source.cols = input_width;
	source.rows = input_height;
	source.data = (char*)inPtr[0];
	source.size = wordWidth*height*(sizeof(cl_int));
	source.offset = 0;
	source.steps = inPitch[0];

	dst.cols = input_width;
	dst.rows = input_height;
	dst.size = wordWidth*height*(sizeof(cl_int));
	dst.data = (char*)outPtr[0];
	dst.offset = 0;
	dst.steps = outPitch[0];


	int apperture_size = 3;
	short low_thresh = 80;
	short high_thresh = 100;
	char L2gradient = 0;

    source.buf = clCreateBuffer(algHandle->context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, source.size, source.data, &err);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);
	dst.buf = clCreateBuffer(algHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, dst.size, dst.data, &err);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);


	/* Do the sobel filter */
//	Vps_printf("Start1:\n");

	if (apperture_size == 3)
	{
		calcSobelRowPass_opencl(algHandle->context, algHandle->queue, algHandle->kernel[0],
                          source, algHandle->dxbuf, algHandle->dybuf,
                          inPtr,outPtr,inPitch,outPitch);
//Vps_printf("Start2:\n");

		calcMagnitude_opencl(algHandle->context, algHandle->queue, algHandle->kernel[1], algHandle->dxbuf, algHandle->dybuf,
                        algHandle->dx, algHandle->dy, algHandle->mag, source.rows, source.cols, L2gradient);
	}
//Vps_printf("Start3:\n");
	calcMap_opencl(algHandle->context, algHandle->queue, algHandle->kernel[2],algHandle->dx, algHandle->dy,
                 algHandle->mag, algHandle->map, dst.rows, dst.cols, low_thresh, high_thresh,
                 inPtr,outPtr,inPitch,outPitch,numPlanes,height,wordWidth,algHandle->trackBuf1,algHandle->counter);
	edgesBlob_opencl(algHandle->context, algHandle->queue, algHandle->kernel[4], algHandle->map, algHandle->trackBuf1, algHandle->counter,
                            dst.rows, dst.cols);

//Vps_printf("Start4:\n");
	getEdges_opencl(algHandle->context, algHandle->queue, algHandle->kernel[3], algHandle->map, dst, dst.rows, dst.cols);

	//add_ocl_logo(inPtr, outPtr, inPitch,outPitch);


    clFinish(algHandle->queue);
    clReleaseMemObject(source.buf);
    clReleaseMemObject(dst.buf);

    //while(1);
    return (0);
}

void calcSobelRowPass_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf src,
                        opencl_buf dx_buf, opencl_buf dy_buf,
                        UInt32 *inPtr[], UInt32 *outPtr[], UInt32 inPitch[],UInt32 outPitch[])
{
	cl_event event;
	int err;

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&src.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&dx_buf.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&dy_buf.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	err = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&src.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&dx_buf.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&dy_buf.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	size_t globalThreads[3] = { (src.cols>>4)-1, src.rows-1, 1 };
	size_t localThreads[3] = { (src.cols>>4)-1, src.rows-1, 1 };

	err = clEnqueueNDRangeKernel(queue, kernel, 3, NULL, globalThreads, localThreads, 0, NULL, &event);
	if (err != 0)
		printf("Error: %d\n", (int)err);



	clWaitForEvents(1, &event);
//	err = clEnqueueReadBuffer(queue, dx_buf.buf, CL_TRUE, 0, dx_buf.size, dx_buf.data, 0, NULL, NULL);
//	err = clEnqueueReadBuffer(queue, dy_buf.buf, CL_TRUE, 0, dy_buf.size, dy_buf.data, 0, NULL, NULL);
	clReleaseEvent(event);

}

void calcMagnitude_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf dx_buf, opencl_buf dy_buf, opencl_buf dx, opencl_buf dy, opencl_buf mag, int rows,int cols, char L2gradient)
{
	cl_event event;
	int err;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&dx_buf.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&dy_buf.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&dx.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&dy.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&mag.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&dx_buf.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 6, sizeof(cl_mem), (void*)&dy_buf.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 7, sizeof(cl_mem), (void*)&dx.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 8, sizeof(cl_mem), (void*)&dy.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 9, sizeof(cl_mem), (void*)&mag.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);






	size_t globalThreads[3] = { (cols>>3)-1, rows-2, 1 };
	size_t localThreads[3] = { (cols>>3)-1, rows-2, 1 };

	err = clEnqueueNDRangeKernel(queue, kernel, 3, NULL, globalThreads, localThreads, 0, NULL, &event);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	clWaitForEvents(1, &event);
	//err = clEnqueueReadBuffer(queue, mag.buf, CL_TRUE, 0, mag.size, mag.data, 0, NULL, NULL);
	//err = clEnqueueReadBuffer(queue, dx.buf, CL_TRUE, 0, dx.size, dx.data, 0, NULL, NULL);
	//err = clEnqueueReadBuffer(queue, dy.buf, CL_TRUE, 0, dy.size, dy.data, 0, NULL, NULL);
	clReleaseEvent(event);




}

void calcMap_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf dx, opencl_buf dy,
               opencl_buf mag, opencl_buf map, int rows, int cols, short low_thresh, short high_thresh,
                UInt32 *inPtr[], UInt32 *outPtr[], UInt32 inPitch[], UInt32 outPitch[],UInt32 numPlanes,UInt32 height,
                UInt32 wordWidth,opencl_buf trackBuf1, opencl_buf counter)
{
	cl_event event;
	int err;
	counter.data[0]=0;
	counter.data[1]=0;
	counter.data[2]=0;
	counter.data[3]=0;

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&dx.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&dy.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&mag.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&map.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&trackBuf1.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&counter.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 6, sizeof(cl_short), (void*)&low_thresh);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 7, sizeof(cl_short), (void*)&high_thresh);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 8, sizeof(cl_mem), (void*)&dx.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 9, sizeof(cl_mem), (void*)&dy.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 10, sizeof(cl_mem), (void*)&mag.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 11, sizeof(cl_mem), (void*)&map.steps);
	if (err != 0)
		printf("Error: %d\n", (int)err);


	size_t globalThreads[3] = { cols-1, rows-1, 1 };
	size_t localThreads[3] = { cols-1, rows-1, 1 };

	err = clEnqueueNDRangeKernel(queue, kernel, 3, NULL, globalThreads, localThreads, 0, NULL, &event);
	if (err != 0)
		printf("Error: %d\n", (int)err);

    set_chroma(inPtr,outPtr,inPitch,outPitch,numPlanes,height,wordWidth);

	clWaitForEvents(1, &event);
	err = clEnqueueReadBuffer(queue, counter.buf, CL_TRUE, 0, counter.size, counter.data, 0, NULL, NULL);

	clReleaseEvent(event);

}

void getEdges_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf map, opencl_buf dst, int rows, int cols)
{
	cl_event event;
	int err;
	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&map.buf);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&dst.buf);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);

	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&map.steps);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);

	err = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&dst.steps);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);


   // Vps_printf("edge0\n");
	size_t globalThreads[3] = { (cols>>2)-1, rows-1, 1 };
	size_t localThreads[3] = { (cols>>2)-1, rows-1, 1 };

	err = clEnqueueNDRangeKernel(queue, kernel, 3, NULL, globalThreads, localThreads, 0, NULL, &event);
	if (err != 0)
		Vps_printf("Error: %d\n", (int)err);


	clWaitForEvents(1, &event);
	//err = clEnqueueReadBuffer(queue, dst.buf, CL_TRUE, 0, dst.size, dst.data, 0, NULL, NULL);

	clReleaseEvent(event);

}

void edgesBlob_opencl(cl_context context, cl_command_queue queue, cl_kernel kernel, opencl_buf map, opencl_buf trackBuf1, opencl_buf counter, int rows, int cols)
{
	cl_event event;
	int err;
	cl_int stepBytes = map.steps;
	cl_int offsetBytes = map.offset;


	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&map.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&trackBuf1.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&counter.buf);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	err = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&stepBytes);
	if (err != 0)
		printf("Error: %d\n", (int)err);


	size_t globalThreads[3] = { 1, 1, 1 };
	size_t localThreads[3] = { 1, 1, 1 };

	err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, globalThreads, localThreads, 0, NULL, &event);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	clWaitForEvents(1, &event);
//	err = clEnqueueReadBuffer(queue, map.buf, CL_TRUE, 0, map.size, map.data, 0, NULL, NULL);
//	err = clEnqueueReadBuffer(queue, trackBuf1.buf, CL_TRUE, 0, trackBuf1.size, trackBuf1.data, 0, NULL, NULL);
//	err = clEnqueueReadBuffer(queue, counter.buf, CL_TRUE, 0, counter.size, counter.data, 0, NULL, NULL);

	clReleaseEvent(event);
}


void add_ocl_logo(
             UInt32 *inPtr[],
             UInt32 *outPtr[],
             UInt32 inPitch[],
             UInt32 outPitch[]
             )
{
    Int32 rowIdx;
    Int32 colIdx;
    UInt8 *inputPtr;
    UInt8 *outputPtr;
    UInt16 *outputuvPtr;
    UInt16 *inputuvPtr;


   /*copy the opencl logo */

    inputPtr  = (UInt8*)OpenCL_Logo_yuv;
    outputPtr = (UInt8*)outPtr[0];
    for(rowIdx = 0; rowIdx < 200 ; rowIdx+=2)
    {
        for(colIdx = 0; colIdx < 100 ; colIdx++)
        {
            *(outputPtr+colIdx+1180) = *(inputPtr+(colIdx<<1));
        }
        inputPtr += 2*200;
        outputPtr += (outPitch[0]);
    }

    inputuvPtr  = (UInt16*)(OpenCL_Logo_yuv+200*200);
    outputuvPtr = (UInt16*)outPtr[1];
    for(rowIdx = 0; rowIdx < 100 ; rowIdx+=2)
    {
        for(colIdx = 0; colIdx < 50 ; colIdx++)
        {
            *(outputuvPtr+colIdx+1180) = *(inputuvPtr+(colIdx<<1));

        }
        inputPtr += 2*100;
        outputPtr += (outPitch[1]>>1);
    }

}
void set_chroma(
             UInt32 *inPtr[],
             UInt32 *outPtr[],
             UInt32 inPitch[],
             UInt32 outPitch[],
             UInt32 numPlanes,
             UInt32 height,
             UInt32 wordWidth
             )

{
    Int32 rowIdx;
    Int32 colIdx;
    UInt32 *inputPtr;
    UInt32 *outputPtr;

   if(numPlanes == 2)
    {
        inputPtr  = inPtr[1];
        outputPtr = outPtr[1];
        for(rowIdx = 0; rowIdx < (height >> 1) ; rowIdx++)
        {
            for(colIdx = 0; colIdx < wordWidth ; colIdx++)
            {
                *(outputPtr+colIdx) = 0x80808080;
            }
            inputPtr += (inPitch[1] >> 2);
            outputPtr += (outPitch[1] >> 2);
        }
    }
}

