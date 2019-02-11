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
 * \ingroup  ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_IMAGEPYRAMID Image Pyramid API
 *
 * \brief  This module has the interface for using Image Pyramid algorithm
 *
 *         Image Pyramid algorithm link -
 *             1. This alg takes input from previous link and generated image
 *                pyramid
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_imgPyramid.h
 *
 * \brief Algorithm Link API specific to image pyramid algorithm
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_IMAGEPYRAMID_H_
#define ALGORITHM_LINK_IMAGEPYRAMID_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ALGORITHLINK_IMGPYRAMID_MAX_SCALES                  (24U)

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ALGORITHM_LINK_IMAGE_PYRAMID_CMD \
 *                   Image Pyramid Control Commands
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Link CMD: Command to get the pyramid information. It returns
 *        number of output scales and output resolution for each scales.
 *        It also returns the pitch/buffer lines offset information for each
 *        scale.
 *        Note: It does not update/touch the bufAddr field
 *
 *   \param AlgorithmLink_ImgPyramidInfo *pPrm [OUT] Image Pyramid Information.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_LINK_IMAGE_PYRAMID_CMD_GET_PYRAMID_INFO   (0x1000)


/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Enum to select resizer modules.
 *          Image Pyramid uses resizer module for generating different scales,
 *          This enum selects underlying resizer module to be used
 *          for generating image pyramid
 *
 *******************************************************************************
*/
typedef enum
{
    ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_ISS = 0,
    /**< Use ISS Resizer for Generating Image pyramid */
    ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_EVE = 1,
    /**< Use EVE Resizer for Generating Image pyramid */
    ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_VPE = 2,
    /**< Use VPE for Generating Image pyramid */
    ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_MAX = 3,
    /**< Max modules */
    ALGORITHM_LINK_IMG_PYRAMID_FORCE32BIT = 0x7FFFFFFF
    /**< Last enum to make enum value 32 bit */
} AlgorithmLink_ImgPyramidRszModules;



/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Image Pyramid Frame Descriptor.
 *          It contains output frame size and other information for each scale.
 *
 *          Pointer to array of AlgorithmLink_ImgPyramidFrameDesc is
 *          also output as metadata buffer in system_buffer.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32      orgWidth;
    /**< Original Frame Information */
    UInt32      orgHeight;
    /**< Original Frame Information */
    UInt32      startX;
    /**< Horizontal Position of the output image in the given buffer */
    UInt32      startY;
    /**< vertical Position of the output image in the given buffer */
    UInt32      width;
    /**< Output Image width */
    UInt32      height;
    /**< Output Image height */
    Ptr         bufAddr[SYSTEM_MAX_PLANES];
    /**< Buffer Addresses for the Luma and chroma */
    UInt32      pitch[SYSTEM_MAX_PLANES];
    /**< pitch/lineoffset for the luma and chroma */
} AlgorithmLink_ImgPyramidFrameDesc;


/**
 *******************************************************************************
 *
 *   \brief Image Pyramid Information structure.
 *          This structure contains output frame size information
 *          and other information used in calculating output frame size
 *          for each scale.
 *
 *          This structure is used as an argument with the
 *          ALGORITHM_LINK_IMAGE_PYRAMID_CMD_GET_PYRAMID_INFO ioctl.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                            sreachStep;
    /**< Sread Step */
    UInt32                            numScales;
    /**< Number of scales to use for image pyramid,
         Copied from Create Parameters  */
    UInt32                            scaleSteps;
    /**< Number of steps to use for image pyramid,
         Copied from Create Parameters */
    AlgorithmLink_ImgPyramidFrameDesc frmDesc
        [ALGORITHLINK_IMGPYRAMID_MAX_SCALES];
    /* Image Pyramid Output Frame information */
} AlgorithmLink_ImgPyramidInfo;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for image pyramid
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams              baseClassCreate;
    /**< Base class create params. This structure should be first element */
    AlgorithmLink_ImgPyramidRszModules      rszModule;
    /**< Underlying Resizer to be used for resizing operation */
    UInt32                                  numOutBuffers;
    /**< Number of output buffers */
    UInt32                                  enableRoi;
    /**< Flag to enable/disable ROI */
    UInt32                                  roiStartX;
    /**< Roi horizontal start position */
    UInt32                                  roiStartY;
    /**< Roi vertical start position */
    UInt32                                  roiWidth;
    /**< Width of ROI relative to frameWidth */
    UInt32                                  roiHeight;
    /**< Height of ROI relative to frameHeight */
    UInt32                                  numScales;
    /**< Number of scales to use for image pyramid,
         Must be less than ALGORITHLINK_IMGPYRAMID_MAX_SCALES */
    UInt32                                  scaleSteps;
    /**< Number of steps to use for image pyramid,
         Must be less than #numScales */
    System_LinkOutQueParams                 outQueParams;
    /**< Output queue information */
    System_LinkInQueParams                  inQueParams;
    /**< Input queue information */
    System_LinkMemAllocInfo                 memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */
} AlgorithmLink_ImgPyramidCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure used for getting image pyramid information.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
    AlgorithmLink_ImgPyramidInfo    imgPyramidInfo;
    /**< Pointer to image pyramid information structure */
} AlgorithmLink_ImgPyramidImgPyramidInfoControlParams;


/*******************************************************************************
 *  Function Prototype
 *******************************************************************************
 */
static inline void AlgorithmLink_ImgPyramid_Init(
                    AlgorithmLink_ImgPyramidCreateParams *pPrm);
static inline void AlgorithmLink_ImgPyramidImgPyramidInfoControlParams_Init(
        AlgorithmLink_ImgPyramidImgPyramidInfoControlParams *pPrm);


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_ImgPyramid_Init(
    AlgorithmLink_ImgPyramidCreateParams *pPrm)
{
    memset(pPrm, 0, sizeof(AlgorithmLink_ImgPyramidCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                    sizeof(AlgorithmLink_ImgPyramidCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_IPU_ALG_IMG_PYRAMID;

    pPrm->inQueParams.prevLinkId    = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->outQueParams.nextLink     = SYSTEM_LINK_ID_INVALID;
    pPrm->rszModule                 = ALGORITHM_LINK_IMG_PYRAMID_RSZ_MODULE_EVE;
    pPrm->numOutBuffers             = 2U;
    pPrm->roiStartX                 = 0U;
    pPrm->roiStartY                 = 0U;
    pPrm->roiWidth                  = 720U;
    pPrm->roiHeight                 = 480U;
    pPrm->numScales                 = 17U;
    pPrm->scaleSteps                = 6U;
}

/**
 *******************************************************************************
 *
 * \brief Set defaults for Control parameters
 *
 * \param pPrm  [OUT] control parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_ImgPyramidImgPyramidInfoControlParams_Init(
        AlgorithmLink_ImgPyramidImgPyramidInfoControlParams *pPrm)
{
    memset(pPrm, 0,
        sizeof(AlgorithmLink_ImgPyramidImgPyramidInfoControlParams));
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of image pyramid algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_imgPyramidComputation_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
