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

/**
 *******************************************************************************
 *
 * \file CannyEdgeDSPAlgo.c
 *
 * \brief Algorithm for Alg_CannyEdge on DSP
 *
 *        This Alg_CannyEdge algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *        This algorithm does a frame copy. Height and width gets decided during
 *        Create. If height / width needs to be altered, then control call
 *        needs to be done.
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <CL/cl.h>
#include "iOpenClCannyEdgeAlgo.h"
#include <include/link_api/system_trace.h>
#define OpenCL_debug 1
#include "kernel/imgproc_canny.dsp_h"




/**
 *******************************************************************************
 *
 * \brief Implementation of create for frame copy algo
 *
 * \param  pCreateParams    [IN] Creation parameters for frame copy Algorithm
 *
 * \return  Handle to algorithm
 *
 *******************************************************************************
 */
Alg_OpenCLCannyEdge_Obj * Alg_OpenCLCannyEdgeCreate(
                        Alg_OpenCLCannyEdgeCreateParams *pCreateParams)
{

    Alg_OpenCLCannyEdge_Obj * pAlgHandle;
    volatile Int32 enableDebug = 0;
    int i;
#ifdef OpenCL_debug
    char platform_name[128];
    char platform_vendor[128];
    cl_uint max_compute_units;
    cl_uint max_wi_dims;
    size_t max_wi_sizes[3];
    size_t max_wg_size;
#endif
    int input_width = 1280;
    int input_height =720;
    cl_int err     = CL_SUCCESS;
    const char* Kernel_name[] = { "calcSobelRowPass", "calcMagnitude_buf","calcMap", "getEdges","edgesblob"};//, "edgesHysteresisGlobal",  };
	cl_int binaryStatus;
    unsigned char *programBinary = (unsigned char*)&imgproc_canny_dsp_bin;

    pAlgHandle = (Alg_OpenCLCannyEdge_Obj *) malloc(sizeof(Alg_OpenCLCannyEdge_Obj));

    UTILS_assert(pAlgHandle != NULL);

    pAlgHandle->maxHeight   = pCreateParams->maxHeight;
    pAlgHandle->maxWidth    = pCreateParams->maxWidth;




/* OpenCL instance is created here */
#if 1
    err = clGetPlatformIDs(2, pAlgHandle->platform, NULL);
    err = clGetPlatformInfo(pAlgHandle->platform[0], CL_PLATFORM_NAME, 128, platform_name, NULL);
    err = clGetPlatformInfo(pAlgHandle->platform[0], CL_PLATFORM_VENDOR, 128, platform_vendor, NULL);
    Vps_printf("Platform Name: %s\n", platform_name);
    Vps_printf("Platform Vendor: %s\n", platform_vendor);
    err = clGetDeviceIDs(pAlgHandle->platform[0], CL_DEVICE_TYPE_DEFAULT, 1, &pAlgHandle->device, NULL);
    Vps_printf("Device Create Error: %d\n", (int)err);
    err = clGetDeviceInfo(pAlgHandle->device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &max_compute_units, NULL);
    err = clGetDeviceInfo(pAlgHandle->device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &max_wi_dims, NULL);
    err = clGetDeviceInfo(pAlgHandle->device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 3 * sizeof(cl_uint), max_wi_sizes, NULL);
    err = clGetDeviceInfo(pAlgHandle->device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_uint), &max_wg_size, NULL);
    Vps_printf("Max Compute Units: %d\n", (int)max_compute_units );
    Vps_printf("Max Work Item Dimensions: %d\n", (int)max_wi_dims);
    Vps_printf("Max Work Item Sizes: %d, %d, %d\n", max_wi_sizes[0], max_wi_sizes[1], max_wi_sizes[2]);
    Vps_printf("Max Work Group Size: %d\n", max_wg_size);
    pAlgHandle->context = clCreateContext(NULL, 1, &pAlgHandle->device, NULL, NULL, &err);
    Vps_printf("Context Create Error: %d\n", (int)err);
    pAlgHandle->queue = clCreateCommandQueue(pAlgHandle->context, pAlgHandle->device, CL_QUEUE_PROFILING_ENABLE, &err);
    Vps_printf("Quque Create Error: %d\n", (int)err);
    pAlgHandle->program = clCreateProgramWithBinary(pAlgHandle->context,1,&pAlgHandle->device,
                                        &imgproc_canny_dsp_bin_len,
                                        (const unsigned char**)&programBinary,
                                        &binaryStatus,
                                        &err);

     if ((err!= CL_SUCCESS) || (binaryStatus != CL_SUCCESS))
    {
     Vps_printf("Error in building binary");
    }

    err = clBuildProgram(pAlgHandle->program, 1, &pAlgHandle->device, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        // Determine the reason for the error
        char buildLog[16384];
        clGetProgramBuildInfo(pAlgHandle->program, pAlgHandle->device, CL_PROGRAM_BUILD_LOG,
                              sizeof(buildLog), buildLog, NULL);

        //std::cerr << "Error in program: " << std::endl;
        //std::cerr << buildLog << std::endl;
        clReleaseProgram(pAlgHandle->program);
    }

    Vps_printf("Success in building binary");
    for(i= 0; i <NO_KERNEL; i++ )
    {

      pAlgHandle->kernel[i] = clCreateKernel(pAlgHandle->program, Kernel_name[i], &err);
      Vps_printf("Kernel Create Error: %d\n", (int)err);
    }

    /* Allocate and create all tem buffers*/
	pAlgHandle->edge.cols = input_width+16;
	pAlgHandle->edge.rows = (input_height + 2) ;//* 2;
	pAlgHandle->edge.size = pAlgHandle->edge.cols*pAlgHandle->edge.rows*sizeof(cl_short);
	pAlgHandle->edge.data =(char*) malloc(pAlgHandle->edge.size);
	pAlgHandle->edge.offset = 0;
	pAlgHandle->edge.steps = 2080;
	pAlgHandle->dxbuf.cols = input_width;
	pAlgHandle->dxbuf.rows = input_height;
	pAlgHandle->dxbuf.size = pAlgHandle->dxbuf.cols*pAlgHandle->dxbuf.rows*sizeof(cl_short);
	pAlgHandle->dxbuf.data = (char*)malloc(2*pAlgHandle->dxbuf.size);
	pAlgHandle->dxbuf.offset = 0;
	pAlgHandle->dxbuf.steps = input_width *sizeof(cl_short);

	pAlgHandle->dybuf.cols = input_width;
	pAlgHandle->dybuf.rows = input_height;
	pAlgHandle->dybuf.size = pAlgHandle->dybuf.cols*pAlgHandle->dybuf.rows*sizeof(cl_short);
	pAlgHandle->dybuf.data = (char*)(pAlgHandle->dxbuf.data + pAlgHandle->dxbuf.size);//(char*)malloc(pAlgHandle->dybuf.size );
	pAlgHandle->dybuf.offset = 0;
	pAlgHandle->dybuf.steps = input_width *sizeof(cl_short);
	pAlgHandle->dx.cols = input_width;
	pAlgHandle->dx.rows = input_height;
	pAlgHandle->dx.size = pAlgHandle->dx.cols*pAlgHandle->dx.rows*sizeof(cl_short);
	pAlgHandle->dx.data = (char*)malloc(pAlgHandle->dx.size);
	pAlgHandle->dx.offset = 0;
	pAlgHandle->dx.steps = input_width *sizeof(cl_short);
	pAlgHandle->dy.cols = input_width;
	pAlgHandle->dy.rows = input_height;
	pAlgHandle->dy.size = pAlgHandle->dy.cols*pAlgHandle->dy.rows*sizeof(cl_short);
	pAlgHandle->dy.data = (char*)malloc(pAlgHandle->dy.size);
	pAlgHandle->dy.offset = 0;
	pAlgHandle->dy.steps = input_width *sizeof(cl_short);
	pAlgHandle->trackBuf1.cols = (input_height*input_width);
	pAlgHandle->trackBuf1.rows = 1;
	pAlgHandle->trackBuf1.size = (pAlgHandle->trackBuf1.cols*pAlgHandle->trackBuf1.rows*sizeof(cl_int));
	pAlgHandle->trackBuf1.data = pAlgHandle->dxbuf.data;
	pAlgHandle->trackBuf1.steps = pAlgHandle->trackBuf1.cols * sizeof(cl_int);
	pAlgHandle->trackBuf1.offset = 0;

	pAlgHandle->trackBuf2.cols = (input_height*input_width);
	pAlgHandle->trackBuf2.rows = 1;
	pAlgHandle->trackBuf2.size = (pAlgHandle->trackBuf2.cols*pAlgHandle->trackBuf2.rows*sizeof(cl_int));
//	trackBuf2.data = (char*)malloc(trackBuf2.cols*trackBuf2.rows*sizeof(cl_short));
	pAlgHandle->trackBuf2.steps = pAlgHandle->trackBuf2.cols * sizeof(cl_int);
	pAlgHandle->trackBuf2.offset = 0;

	pAlgHandle->mag.cols = pAlgHandle->edge.cols ;
	pAlgHandle->mag.rows = pAlgHandle->edge.rows / 2;
	pAlgHandle->mag.size = (pAlgHandle->mag.cols)*pAlgHandle->mag.rows*sizeof(cl_short);
	pAlgHandle->mag.data = pAlgHandle->edge.data+8;
	pAlgHandle->mag.offset = 0;
	pAlgHandle->mag.steps = pAlgHandle->mag.cols*sizeof(cl_short);

	pAlgHandle->map.cols = pAlgHandle->edge.cols;
	pAlgHandle->map.rows = pAlgHandle->edge.rows;
	pAlgHandle->map.size = pAlgHandle->map.cols*pAlgHandle->map.rows*sizeof(cl_char);
	pAlgHandle->map.data = (char*) malloc(pAlgHandle->map.size);
	pAlgHandle->map.offset = 0;
	pAlgHandle->map.steps = pAlgHandle->map.cols*sizeof(cl_char);

	pAlgHandle->counter.cols = 1;
	pAlgHandle->counter.rows = 1;
	pAlgHandle->counter.size = pAlgHandle->counter.cols*pAlgHandle->counter.rows*sizeof(cl_int);
	pAlgHandle->counter.data = (char*)pAlgHandle->edge.data;
	pAlgHandle->counter.offset = 0;
	pAlgHandle->counter.steps = 32;
#if 1
	pAlgHandle->dxbuf.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->dxbuf.size, pAlgHandle->dxbuf.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	pAlgHandle->dybuf.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->dybuf.size, pAlgHandle->dybuf.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	pAlgHandle->dx.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->dx.size, pAlgHandle->dx.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);
	pAlgHandle->dy.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->dy.size, pAlgHandle->dy.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	pAlgHandle->trackBuf1.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->trackBuf1.size, pAlgHandle->trackBuf1.data,
                                             &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);
/*	trackBuf2.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, trackBuf2.cols*trackBuf2.rows* sizeof(cl_short), dy.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);
*/
	pAlgHandle->mag.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->mag.size, pAlgHandle->mag.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	pAlgHandle->map.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, pAlgHandle->map.size, pAlgHandle->map.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);

	pAlgHandle->counter.buf = clCreateBuffer(pAlgHandle->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, pAlgHandle->counter.size, pAlgHandle->counter.data, &err);
	if (err != 0)
		printf("Error: %d\n", (int)err);

#endif




  do
   {

   }while (enableDebug);

#endif
    return pAlgHandle;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for frame copy algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned.
 *
 * \param  algHandle    [IN] Algorithm object handle
 * \param  inPtr[]      [IN] Array of input pointers
 *                           Index 0 - Pointer to Y data in case of YUV420SP,
 *                                   - Single pointer for YUV422IL or RGB
 *                           Index 1 - Pointer to UV data in case of YUV420SP
 * \param  outPtr[]     [IN] Array of output pointers. Indexing similar to
 *                           array of input pointers
 * \param  width        [IN] width of image
 * \param  height       [IN] height of image
 * \param  inPitch[]    [IN] Array of pitch of input image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  outPitch[]   [IN] Array of pitch of output image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  dataFormat   [IN] Different image data formats. Refer
 *                           System_VideoDataFormat
 * \param  copyMode     [IN] 0 - copy by CPU, 1 - copy by DMA
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
 Int32 Alg_OpenCLCannyEdgeProcess(Alg_OpenCLCannyEdge_Obj *algHandle,
                           UInt32            *inPtr[],
                           UInt32            *outPtr[],
                           UInt32             width,
                           UInt32             height,
                           UInt32             inPitch[],
                           UInt32             outPitch[],
                           UInt32             dataFormat,
                           Uint32             copyMode
                          )
{
    cl_int err     = CL_SUCCESS;

    volatile Int32 enableDebug = 0;
    UInt32 wordWidth;
    UInt32 numPlanes;
    Int32 rowIdx;
    Int32 colIdx;
    UInt32 *inputPtr;
    UInt32 *outputPtr;


    if((width > algHandle->maxWidth) ||
       (height > algHandle->maxHeight) ||
       (copyMode != 0))
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
    {
        numPlanes = 1;
        wordWidth = (width*2)>>2;


    }
    else if(dataFormat == SYSTEM_DF_YUV420SP_UV)
    {
        numPlanes = 2;
        wordWidth = (width)>>2;

    }
    else
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }



    OpenCl_canny_edgedetect(algHandle, inPtr,outPtr,wordWidth,height,inPitch,outPitch,numPlanes);



    return SYSTEM_LINK_STATUS_SOK;
}



/**
 *******************************************************************************
 *
 * \brief Implementation of Control for frame copy algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 Alg_OpenCLCannyEdgeControl(Alg_OpenCLCannyEdge_Obj          *pAlgHandle,
                           Alg_OpenCLCannyEdgeControlParams *pControlParams)
{
    /*
     * Any alteration of algorithm behavior
     */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop for frame copy algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCLCannyEdgeStop(Alg_OpenCLCannyEdge_Obj *algHandle)
{
      return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for frame copy algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCLCannyEdgeDelete(Alg_OpenCLCannyEdge_Obj *algHandle)
{
   int i;

    free(algHandle->edge.data);
    free(algHandle->dxbuf.data);
    free(algHandle->dx.data);
    free(algHandle->dy.data);
    free(algHandle->map.data);
    clReleaseMemObject(algHandle->dxbuf.buf);
    clReleaseMemObject(algHandle->dybuf.buf);
    clReleaseMemObject(algHandle->dx.buf);
    clReleaseMemObject(algHandle->dy.buf);
    clReleaseMemObject(algHandle->mag.buf);
    clReleaseMemObject(algHandle->map.buf);
    clReleaseMemObject(algHandle->trackBuf1.buf);
    clReleaseMemObject(algHandle->counter.buf);
    for(i= 0; i <NO_KERNEL; i++ )
     clReleaseKernel(algHandle->kernel[i]);

    clReleaseCommandQueue(algHandle->queue);
    clReleaseProgram(algHandle->program);
    clReleaseContext(algHandle->context);


    free(algHandle);
    return SYSTEM_LINK_STATUS_SOK;
}





/* Nothing beyond this point */
