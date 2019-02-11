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
 * \file opencvCannyAlgo.c
 *
 * \brief Algorithm for Alg_OpenCVCanny on A15
 *
 *        This Alg_OpenCVCanny algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *        This algorithm does a opencv canny edge detection.
 *        Height and width gets decided during
 *        Create. If height / width needs to be altered, then control call
 *        needs to be done.
 *
 * \version 0.0 (March 2016) : [SN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "iOpenCVCannyAlgo.h"
#include "iCanny.h"

/**
 *******************************************************************************
 *
 * \brief Implementation of function to be executed by pthread task which will
 *        be running OpenCV Canny function
 *
 * \param  pCreateParams    [IN] algorithm handle structure that contains the
 *                            input / output pointers is passed
 *
 * \return  nothing
 *
 *******************************************************************************
 */

void cannyThreadCreate(Alg_OpenCVCanny_Obj *pAlgHandle)
{
    if(pthread_create(&pAlgHandle->cannyThread, &pAlgHandle->pAttrs,
	                  &cannyThreadFunc, (void *)NULL))
    {
        generic_printf("Error creating pthread \n");
        return;
    }
}

/**
 *******************************************************************************
 *
 * \brief Implementation of create for OpenCVCanny algo
 *
 * \param  pCreateParams    [IN] Creation parameters for OpenCVCanny Algorithm
 *
 * \return  Handle to algorithm
 *
 *******************************************************************************
 */
Alg_OpenCVCanny_Obj * Alg_OpenCVCannyCreate(
                        Alg_OpenCVCannyCreateParams *pCreateParams)
{
    CvSize imageSize;
    Alg_OpenCVCanny_Obj * pAlgHandle;
    Int32 retc;

    pAlgHandle = (Alg_OpenCVCanny_Obj *) malloc(sizeof(Alg_OpenCVCanny_Obj));

    UTILS_assert(pAlgHandle != NULL);

    pAlgHandle->maxHeight           = pCreateParams->maxHeight;
    pAlgHandle->maxWidth            = pCreateParams->maxWidth;

    imageSize.height                = pCreateParams->maxHeight;
    imageSize.width                 = pCreateParams->maxWidth;

    pAlgHandle->inputImage       = cvCreateImageHeader(imageSize, IPL_DEPTH_8U, 1);
    pAlgHandle->outputImage      = cvCreateImageHeader(imageSize, IPL_DEPTH_8U, 1);

    retc = pthread_attr_init(&pAlgHandle->pAttrs);
    myAssert(retc);

    retc = pthread_attr_setdetachstate(&pAlgHandle->pAttrs, PTHREAD_CREATE_JOINABLE);
    myAssert(retc);

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&pAlgHandle->mtx, &attr);
    pthread_mutexattr_destroy(&attr);

    pAlgHandle->cannyStartPthd = 0;

    return pAlgHandle;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for OpenCVCanny algo
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
Int32 Alg_OpenCVCannyProcess(Alg_OpenCVCanny_Obj *algHandle,
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
    Int32 rowIdx;
    Int32 colIdx;

    UInt32 wordWidth;
    UInt32 numPlanes;

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

    /*
     * For Luma plane of 420SP OR RGB OR 422IL
     */
    inputPtr  = inPtr[0];
    outputPtr = outPtr[0];

    cvSetData(algHandle->inputImage, (uchar *)inputPtr, inPitch[0]);
    cvSetData(algHandle->outputImage, (uchar *)outputPtr, outPitch[0]);

    iCanny(algHandle);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for OpenCVCanny algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCVCannyControl(Alg_OpenCVCanny_Obj          *pAlgHandle,
                           Alg_OpenCVCannyControlParams *pControlParams)
{
    /*
     * Any alteration of algorithm behavior
     */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop for OpenCVCanny algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCVCannyStop(Alg_OpenCVCanny_Obj *algHandle)
{
      return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for OpenCVCanny algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_OpenCVCannyDelete(Alg_OpenCVCanny_Obj *algHandle)
{
    pthread_detach(algHandle->cannyThread);
    pthread_cancel(algHandle->cannyThread);
    iCannyDelete();
    pthread_mutex_destroy(&algHandle->mtx);
    pthread_attr_destroy(&algHandle->pAttrs);

    cvReleaseImageHeader(&algHandle->inputImage);
    cvReleaseImageHeader(&algHandle->outputImage);

    free(algHandle);

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
