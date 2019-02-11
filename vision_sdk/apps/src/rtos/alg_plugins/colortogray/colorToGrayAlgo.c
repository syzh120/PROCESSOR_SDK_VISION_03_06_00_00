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
 * \file colorToGrayAlgo.c
 *
 * \brief Algorithm for Alg_ColorToGray on DSP
 *
 *        This Alg_ColorToGray algorithm is only for demonstrative purpose. 
 *        It is NOT product quality.
 *        Color to gray is a sample algorithm, which just takes a colored video
 *        frame and zeros out chroma component to make it look gray. The 
 *        purpose of this sample algorithm is to demonstrate inplace 
 *        computation in Links and Chains framework.
 *
 * \version 0.0 (Sept 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "iColorToGrayAlgo.h"

/**
 *******************************************************************************
 *
 * \brief Implementation of create for color to gray algo
 *
 * \param  pCreateParams    [IN] Creation parameters for color to gray Algorithm
 *
 * \return  Handle to algorithm
 *
 *******************************************************************************
 */
Alg_ColorToGray_Obj * Alg_ColorToGrayCreate(
                        Alg_ColorToGrayCreateParams *pCreateParams)
{

    Alg_ColorToGray_Obj * pAlgHandle;
    
    pAlgHandle = (Alg_ColorToGray_Obj *) malloc(sizeof(Alg_ColorToGray_Obj));

    UTILS_assert(pAlgHandle != NULL);

    return pAlgHandle;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for color to gray algo
 *        
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV, 
 *        SYSTEM_DF_RGB24_888. It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned. 
 *        
 * \param  algHandle    [IN] Algorithm object handle
 * \param  inPtr[]      [IN] Array of input pointers
 *                           Index 0 - Pointer to Y data in case of YUV420SP, 
 *                                   - Single pointer for YUV422IL or RGB
 *                           Index 1 - Pointer to UV data in case of YUV420SP
 * \param  width        [IN] width of image
 * \param  height       [IN] height of image
 * \param  inPitch[]    [IN] Array of pitch of input image (Address offset 
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 * \param  dataFormat   [IN] Different image data formats. Refer 
 *                           System_VideoDataFormat
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_ColorToGrayProcess(Alg_ColorToGray_Obj *algHandle,
                           UInt32            *inPtr[],
                           UInt32             width,
                           UInt32             height,
                           UInt32             inPitch[],
                           UInt32             dataFormat 
                          )
{
    Int32 rowIdx; 
    Int32 colIdx;

    UInt32 wordWidth;
    
    UInt32 *inputPtr;
    UInt32 mask = 0x00FF00FF;
    UInt32 mask1 = 0x80008000;
             
    if(dataFormat == SYSTEM_DF_YUV422I_YUYV) 
    {
        wordWidth = (width*2)>>2;
    } 
    else
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }
        
    inputPtr  = inPtr[0];
    
    for(rowIdx = 0; rowIdx < height ; rowIdx++)
    {
        for(colIdx = 0; colIdx < wordWidth ; colIdx++)
        {
             /* Masking chroma component */
             
            *(inputPtr+colIdx) &= mask;
            *(inputPtr+colIdx) |= mask1;
            
        }
        inputPtr += (inPitch[0] >> 2);
    }
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for color to gray algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_ColorToGrayControl(Alg_ColorToGray_Obj          *pAlgHandle,
                           Alg_ColorToGrayControlParams *pControlParams)
{
    /* 
     * Any alteration of algorithm behavior
     */
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop for color to gray algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_ColorToGrayStop(Alg_ColorToGray_Obj *algHandle)
{
      return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for color to gray algo
 *
 * \param  algHandle    [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_ColorToGrayDelete(Alg_ColorToGray_Obj *algHandle)
{
    free(algHandle);
    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
