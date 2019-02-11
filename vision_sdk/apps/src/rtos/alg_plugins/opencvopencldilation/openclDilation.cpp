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
 * \file openclDilation.cpp
 *
 * \brief OpenCV OpenCL Dilation algo on A15
 *
 *        This OpenCV OpenCL Dilation algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *        This algorithm does a OpenCV OpenCL Dilation. Height and width gets decided during
 *        Create. If height / width needs to be altered, then control call
 *        needs to be done.
 *
 * \version 0.0 (September 2016) : [SN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "iOpenCLDilation.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/release_static_vars.hpp>
#include <unistd.h>

/*
 * \brief global structure to contain input output image pointers
 */
kernelArgs gOpenCLDilationKernelArgs;
/*
 * \brief Control flag to notify when the compute thread has started
 */
Int32 gOpenCLDilationThreadStarted = 0;
/*
 * \brief Variable that contains the thread exit status
 */
Int32 gOpenCLDilationThreadRtn = 0;
/*
 * \brief Global mutex variable
 */
static pthread_mutex_t gOpenCLDilationMtx;
/*
 * \brief Control flag to wait for consume thread to finish the compute
 */
static Int32 g_cac;

/*
 * \brief OpenCV compute Thread
 */

void* openclDilationThreadFunc(void* args)
{
    while(1)
    {
        cv::Mat openCLDilationInputMat;
        cv::Mat openCLDilationOutputMat;
        cv::UMat openCLDilationInputUMat;
        cv::UMat openCLDilationOutputUMat;

        if(!gOpenCLDilationThreadStarted)
        {
            cv::ocl::setUseOpenCL(1);
            gOpenCLDilationThreadStarted = 1;
        }

        /* wait for the produce thread to point to the current input
         * and output buffers
         */
        while(!g_cac)
        {
            usleep(1000);
        }

        pthread_mutex_lock(&gOpenCLDilationMtx);

        /*
         * \brief Compute using OpenCV
         */
        openCLDilationInputMat  = cv::cvarrToMat(gOpenCLDilationKernelArgs.inputImage, false);
        openCLDilationOutputMat = cv::cvarrToMat(gOpenCLDilationKernelArgs.outputImage, false);

        openCLDilationInputUMat = openCLDilationInputMat.getUMat(cv::ACCESS_RW);
        openCLDilationOutputUMat = openCLDilationOutputMat.getUMat(cv::ACCESS_RW);

        cv::dilate(openCLDilationInputUMat, openCLDilationOutputUMat, cv::Mat());

        openCLDilationInputUMat.release();
        openCLDilationOutputUMat.release();
        openCLDilationInputMat.release();
        openCLDilationOutputMat.release();

        g_cac = 0;

        pthread_mutex_unlock(&gOpenCLDilationMtx);
    }
    pthread_exit(&gOpenCLDilationThreadRtn);
    return ((void*) 0);
}

void iOpenCLDilation(Alg_OpenCVOpenCLDilation_Obj *algHandle)
{
    /*
     * \brief Control flag to acknowledge if thread needs to be started
     *        The second variable is needed to skip compute for first
     *        frame as the pthread consumes some time to get created
     *        and start running
     */
    Int32 openCLDilationStartPthd = 0;
    openCLDilationStartPthd = algHandle->openclDilationStartPthd;

    if(!openCLDilationStartPthd)
    {
        algHandle->openclDilationStartPthd = 1;
        /*
         * \brief Initializing all the global variables
         */
        gOpenCLDilationThreadRtn = 0;
        gOpenCLDilationMtx = algHandle->mtx;
        g_cac = 0;
        gOpenCLDilationThreadStarted = 0;

        gOpenCLDilationKernelArgs.inputImage = NULL;
        gOpenCLDilationKernelArgs.outputImage = NULL;
    }

    pthread_mutex_lock(&gOpenCLDilationMtx);
    /*
     * \brief Pointing to the input and output buffers
     */
    gOpenCLDilationKernelArgs.inputImage = algHandle->inputImage;
    gOpenCLDilationKernelArgs.outputImage = algHandle->outputImage;
    g_cac = 1;
    pthread_mutex_unlock(&gOpenCLDilationMtx);

    if(gOpenCLDilationThreadStarted)
    {
        /* wait for the compute thread to finish if it has started */
        while(g_cac)
        {usleep(1000);}
    }

    if(!openCLDilationStartPthd)
    {
        openCLDilationStartPthd = 1;
        openclDilationThreadCreate(algHandle);
    }
}

/*
 * \brief OpenCV cleanup
 */

void iOpenCLDilationDelete()
{
    cv::release_static_vars();
    generic_printf("Cleaned up OpenCV inits!!");
}
