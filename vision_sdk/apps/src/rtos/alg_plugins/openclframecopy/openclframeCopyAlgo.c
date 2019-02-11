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
 * \file frameCopyDSPAlgo.c
 *
 * \brief Algorithm for Alg_FrameCopy on DSP
 *
 *        This Alg_FrameCopy algorithm is only for demonstrative purpose.
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
#include "iOpenClFrameCopyAlgo.h"
#include <include/link_api/system_trace.h>
#define OpenCL_debug 1
#include "kernel/copy.dsp_h"
cl_program CreateProgramFromBinary(cl_context context, cl_device_id device);

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
Alg_OpenCLFrameCopy_Obj * Alg_OpenCLFrameCopyCreate(
                        Alg_OpenCLFrameCopyCreateParams *pCreateParams)
{

    Alg_OpenCLFrameCopy_Obj * pAlgHandle;
    volatile Int32 enableDebug = 0;
#ifdef OpenCL_debug
    char platform_name[128];
    char platform_vendor[128];
    cl_uint max_compute_units;
    cl_uint max_wi_dims;
    size_t max_wi_sizes[3];
    size_t max_wg_size;
#endif
    cl_int err     = CL_SUCCESS;
    cl_int binaryStatus;
    unsigned char *programBinary = (unsigned char *)&copy_dsp_bin;

    pAlgHandle = (Alg_OpenCLFrameCopy_Obj *) malloc(sizeof(Alg_OpenCLFrameCopy_Obj));

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
                                        &copy_dsp_bin_len,
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

    pAlgHandle->kernel = clCreateKernel(pAlgHandle->program, "Copy", &err);
    Vps_printf("Kernel Create Error: %d\n", (int)err);

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
Int32 Alg_OpenCLFrameCopyProcess(Alg_OpenCLFrameCopy_Obj *algHandle,
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
    size_t global_size[3] = {1024, 1, 1};
    size_t local_size[3] = {1024, 1, 1};
    cl_ulong start_time, end_time;

    Int32 rowIdx;
    Int32 colIdx;

    UInt32 wordWidth;
    UInt32 numPlanes;
    UInt32 cols;
    UInt32 rows;
    UInt32 inpitch;
    UInt32 outpitch;

    UInt32 vector_size;

    cl_mem bufVecA;
    cl_mem bufVecB;

    UInt32 info[10];

    UInt32 *inputPtr;
    UInt32 *outputPtr;

    Uint32 inputPitch;
    Uint32 outputPitch;

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
        vector_size = wordWidth*height;

    }
    else if(dataFormat == SYSTEM_DF_YUV420SP_UV)
    {
        numPlanes = 2;
        wordWidth = (width)>>2;
        vector_size = wordWidth*height;
    }
    else
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }


    inpitch = inPitch[0];
    outpitch = outPitch[0];
    cols = wordWidth;
    rows =height;
    inputPtr  = inPtr[0];
    outputPtr = outPtr[0];

    global_size[0] = 1;
    global_size[1] = 1;
    local_size[0] = 1;
    local_size[1] = 1;

   /*
     * For Luma plane of 420SP OR RGB OR 422IL
     */

    bufVecA = clCreateBuffer(algHandle->context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, vector_size * sizeof(cl_int), inputPtr, &err);
    if(err != 0)
      Vps_printf("Buffer Create Error: %d\n", (int)err);
    bufVecB = clCreateBuffer(algHandle->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, vector_size * sizeof(cl_int), outputPtr, &err);
    if(err != 0)
     Vps_printf("Buffer Create Error: %d\n", (int)err);


    err = clSetKernelArg(algHandle->kernel, 0, sizeof(cl_mem), (void*)&bufVecA);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);
    err = clSetKernelArg(algHandle->kernel, 1, sizeof(cl_mem), (void*)&bufVecB);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 2, sizeof(cl_mem), (void*)&rows);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 3, sizeof(cl_mem), (void*)&cols);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

     err = clSetKernelArg(algHandle->kernel, 4, sizeof(cl_mem), (void*)&inpitch);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 5, sizeof(cl_mem), (void*)&outpitch);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);




    err = clEnqueueNDRangeKernel(algHandle->queue, algHandle->kernel, 3, NULL, global_size, local_size, 0, NULL, &algHandle->event);

    clWaitForEvents(1, &algHandle->event);
    err = clEnqueueReadBuffer(algHandle->queue, bufVecB, CL_TRUE, 0, vector_size * sizeof(cl_int), outputPtr, 0, NULL, NULL);

    clGetEventProfilingInfo(algHandle->event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &start_time, NULL);
    clGetEventProfilingInfo(algHandle->event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &end_time, NULL);
    end_time = end_time-start_time;

    clReleaseEvent(algHandle->event);
    clReleaseMemObject(bufVecA);
    clReleaseMemObject(bufVecB);


 if(numPlanes == 2)
    {
        inputPtr  = inPtr[1];
        outputPtr = outPtr[1];
        inpitch = inPitch[1];
        outpitch = outPitch[1];
        cols = wordWidth;
        rows =height;
        global_size[0] = 1;
        global_size[1] = 1;
        local_size[0] = 1;
        local_size[1] = 1;

     bufVecA = clCreateBuffer(algHandle->context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, vector_size * sizeof(cl_int), inputPtr, &err);
    if(err != 0)
      Vps_printf("Buffer Create Error: %d\n", (int)err);
    bufVecB = clCreateBuffer(algHandle->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, vector_size * sizeof(cl_int), outputPtr, &err);
    if(err != 0)
     Vps_printf("Buffer Create Error: %d\n", (int)err);


    err = clSetKernelArg(algHandle->kernel, 0, sizeof(cl_mem), (void*)&bufVecA);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 1, sizeof(cl_mem), (void*)&bufVecB);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 2, sizeof(cl_mem), (void*)&rows);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 3, sizeof(cl_mem), (void*)&cols);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

     err = clSetKernelArg(algHandle->kernel, 4, sizeof(cl_mem), (void*)&inpitch);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);

    err = clSetKernelArg(algHandle->kernel, 5, sizeof(cl_mem), (void*)&outpitch);
    if(err != 0)
     Vps_printf("Kernel Set Arg Error: %d\n", (int)err);


    err = clEnqueueNDRangeKernel(algHandle->queue, algHandle->kernel, 3, NULL, global_size, local_size, 0, NULL, &algHandle->event);

    clWaitForEvents(1, &algHandle->event);
    err = clEnqueueReadBuffer(algHandle->queue, bufVecB, CL_TRUE, 0, vector_size * sizeof(cl_int), outputPtr, 0, NULL, NULL);

    clReleaseEvent(algHandle->event);
    clReleaseMemObject(bufVecA);
    clReleaseMemObject(bufVecB);
    }


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
Int32 Alg_OpenCLFrameCopyControl(Alg_OpenCLFrameCopy_Obj          *pAlgHandle,
                           Alg_OpenCLFrameCopyControlParams *pControlParams)
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
Int32 Alg_OpenCLFrameCopyStop(Alg_OpenCLFrameCopy_Obj *algHandle)
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
Int32 Alg_OpenCLFrameCopyDelete(Alg_OpenCLFrameCopy_Obj *algHandle)
{
    clReleaseKernel(algHandle->kernel);
    clReleaseCommandQueue(algHandle->queue);
    clReleaseProgram(algHandle->program);
    clReleaseContext(algHandle->context);

    free(algHandle);
    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
