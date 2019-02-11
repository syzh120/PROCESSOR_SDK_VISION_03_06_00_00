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
 * \file iOpenCVOpenCLDilationAlgo.h
 *
 * \brief Interface file for Alg_OpenCVOpenCLDilation algorithm on A15
 *
 *        This Alg_OpenCVOpenCLDilation algorithm is only for demonstrative purpose. 
 *        It is NOT product quality.
 *
 * \version 0.0 (September 2016) : [SN] First version
 *
 *******************************************************************************
 */

#ifndef _IOPENCVOPENCLDILATIONALGO_H_
#define _IOPENCVOPENCLDILATIONALGO_H_

/* opencv headers */

#include <opencv/highgui.h>
/* Using BIOS pthreads */
#include <ti/sysbios/posix/pthread.h> 
#include <opencv2/genericio/generic_io.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define myAssert(retc) \
    if(retc) \
    { \
        return; \
    }

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure for OpenCV OpenCL Dilation algoirthm object
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                   maxHeight;
    /**< Max height of the frame */
    UInt32                   maxWidth;
    /**< max width of the frame */
    IplImage*                inputImage;
    /* opencv input image */
    IplImage*                outputImage;
    /* opencv output image */
    pthread_attr_t           pAttrs;
    /* pthread attribute */
    pthread_t                openclDilationThread;
    /* pthread thread */
    pthread_mutex_t          mtx;
    /* pthread mutex */
    UInt32                   openclDilationStartPthd;
    /* control flag to know if the compute thread has started */
} Alg_OpenCVOpenCLDilation_Obj;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the OpenCV OpenCL Dilation create time parameters
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                   maxHeight;
    /**< Max height of the frame */
    UInt32                   maxWidth;
    /**< max width of the frame */ 
} Alg_OpenCVOpenCLDilationCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the OpenCV OpenCL Dilation control parameters
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                   xxx;
    /**< Any parameters which can be used to alter the algorithm behavior */
} Alg_OpenCVOpenCLDilationControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Declaration of function to be executed by pthread task which will 
 *        be running OpenCV OpenCL Dilation function
 *
 * \param  pAlgHandle    [IN] algorithm handle structure that contains the 
 *                            input / output pointers is passed
 *
 * \return  nothing
 *
 *******************************************************************************
 */

void openclDilationThreadCreate(Alg_OpenCVOpenCLDilation_Obj *pAlgHandle);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for OpenCV OpenCL Dilation algo
 *
 * \param  pCreateParams    [IN] Creation parameters for OpenCV OpenCL Dilation
 *                               Algorithm
 *
 * \return  Handle to algorithm
 *
 *******************************************************************************
 */
Alg_OpenCVOpenCLDilation_Obj * Alg_OpenCVOpenCLDilationCreate(
                        Alg_OpenCVOpenCLDilationCreateParams *pCreateParams);

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for OpenCVOpenCLDilation algo
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
Int32 Alg_OpenCVOpenCLDilationProcess(Alg_OpenCVOpenCLDilation_Obj *algHandle,
                           UInt32            *inPtr[],
                           UInt32            *outPtr[],
                           UInt32             width,
                           UInt32             height,
                           UInt32             inPitch[],
                           UInt32             outPitch[],
                           UInt32             dataFormat, 
                           Uint32             copyMode
                          );

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for OpenCV OpenCL Dilation algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCVOpenCLDilationControl(Alg_OpenCVOpenCLDilation_Obj   *pAlgHandle,
                           Alg_OpenCVOpenCLDilationControlParams *pControlParams);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for OpenCV OpenCL Dilation algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCVOpenCLDilationDelete(Alg_OpenCVOpenCLDilation_Obj *pAlgHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
