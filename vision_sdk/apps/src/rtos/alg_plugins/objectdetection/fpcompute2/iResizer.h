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
 * \file iResizer.h
 *
 * \brief Interface for resizer driver,
 *        Defines function pointers and interface for resizer drier,
 *        These functions must be implemented by the resizer driver
 *
 * \version 0.0
 *
 *******************************************************************************
 */

#ifndef IRESIZER_H_
#define IRESIZER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

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
 *   \brief Function pointer for creating driver
 *
 *******************************************************************************
*/
typedef Void * (*Alg_imgPyramidCreateDrv) (
            AlgorithmLink_ImgPmdObj *pImgPmdObj,
            Void *data);

/**
 *******************************************************************************
 *
 *   \brief Function pointer for deleting driver
 *
 *******************************************************************************
*/
typedef Void (*Alg_imgPyramidDeleteDrv) (
            Void *pHndl,
            Void *data);

/**
 *******************************************************************************
 *
 *   \brief Function pointer for processing frame
 *
 *******************************************************************************
*/
typedef Void (*Alg_imgPyramidDrvProcessFrame) (
            Void *pHndl,
            AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc1,
            AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc1,
            AlgorithmLink_ImgPyramidFrameDesc *inFrmDesc2,
            AlgorithmLink_ImgPyramidFrameDesc *outFrmDesc2,
            Void *data);

/**
 *******************************************************************************
 *
 *   \brief Structure containing function pointer for the resizer driver.
 *          the driver implementing resizer functionality can add
 *          their function so that they can be used for generating image
 *          pyramid.
 *
 *******************************************************************************
*/
struct Alg_ImgPyramidRszDrvFxns_t
{
    AlgorithmLink_ImgPyramidRszModules  rszModule;
    /**< ID of the resizer driver */
    Alg_imgPyramidCreateDrv             createDrv;
    /**< Function to create driver */
    Alg_imgPyramidDeleteDrv             deleteDrv;
    /**< Function to delete driver */
    Alg_imgPyramidDrvProcessFrame       processFrame;
    /**< Function to process frame,
         this pointer supports single input and two outputs */
} ;


/*******************************************************************************
 *  Global Variable
 *******************************************************************************
 */

/* Structure containing pointer to the function to the resizer module */
Alg_ImgPyramidRszDrvFxns gImgPyramidRszModule
    [ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_MAX] =
{
    #ifdef ISS_INCLUDE
    {
        ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_ISS,
        Alg_imgPyramidIssRszCreateDrv,
        Alg_imgPyramidIssRszDeleteDrv,
        Alg_imgPyramidIssRszProcessFrame
    },
    #endif
    #ifdef VPE_INCLUDE
    {
        ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_VPE,
        Alg_imgPyramidVpeRszCreateDrv,
        Alg_imgPyramidVpeRszDeleteDrv,
        Alg_imgPyramidVpeRszProcessFrame
    },
    #endif
    {
        ALGORITHM_LINK_IMG_PYRAMID_FORCE32BIT, NULL, NULL, NULL
    }
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
