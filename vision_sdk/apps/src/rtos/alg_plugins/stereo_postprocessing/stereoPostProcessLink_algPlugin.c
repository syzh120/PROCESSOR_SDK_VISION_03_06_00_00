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
 * \file stereoPostProcessLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Disparity Haming Distance
 *         algorithm Link
 *
 * \version 0.1 (Oct 2014) : [VT] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "stereoPostProcessLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/* Uncomment below line to feed a static left image input corresponding to this post processing link
    The static input is assumed to be contained in a global array gCensusTestLeftInput[]
    of dimensions 896*416= CENSUS_INPUT_IMAGE_WIDTH*CENSUS_INPUT_IMAGE_HEIGHT bytes
    It must be same left image that is fed to the census transform link.

    Purpose of feeding a static image is for testing the stereo-vision algorithm independently only,
    isolated from any pre-processing step such as remap, ISP.
*/
/*#define _TEST_STATIC_INPUT */

#ifdef _TEST_STATIC_INPUT
extern unsigned short gCensusTestLeftInput[896*416/2];
#endif


#define DISPARITY_16BITS 1

uint8_t falseColorLUT_YUV[2][3][257]= {

/* Multi-color color map
const uint8_t falseMultiColorLUT_YUV[3][257]
*/
    {
        {16,34,33,32,32,31,30,30,29,29,29,30,31,31,32,32,33,34,34,35,35,36,37,38,38,39,39,40,41,41,44,47,51,54,57,60,63,67,70,73,76,79,83,86,89,92,96,99,102,105,108,112,115,118,121,124,128,131,134,137,140,144,147,150,153,157,160,162,166,169,169,168,168,167,166,166,165,164,164,163,163,162,161,161,160,159,159,158,158,157,156,156,155,154,154,153,153,152,151,151,150,149,149,148,148,147,146,146,145,144,146,147,149,150,152,154,155,157,158,160,161,163,165,166,168,169,171,171,174,176,177,179,180,182,184,185,187,188,190,191,193,195,196,198,199,201,202,204,206,207,208,210,208,207,206,205,203,202,201,199,198,197,196,195,193,192,191,190,188,187,186,185,183,182,181,180,178,177,176,174,173,171,171,169,168,167,166,164,163,162,161,159,158,157,156,154,153,151,151,149,148,147,145,144,143,142,140,139,138,136,135,134,132,130,129,127,125,123,122,120,118,117,115,113,111,110,108,106,104,103,101,99,97,96,94,92,90,89,87,85,83,82,82,83,84,84,85,85,86,87,87,88,89,89,90,90,91},
        {128,164,167,170,172,174,176,179,181,184,187,190,192,194,197,200,203,205,208,211,214,217,220,222,226,228,230,233,236,239,237,236,233,232,229,228,226,224,222,221,218,216,215,213,212,209,207,206,204,202,200,198,197,194,193,191,189,187,186,183,182,180,178,176,175,172,170,169,167,165,162,160,156,155,151,148,145,143,140,138,135,132,129,127,124,121,119,117,114,110,108,104,103,100,97,93,91,88,85,83,80,77,74,71,69,65,64,61,57,54,55,54,52,51,50,50,49,48,46,46,46,44,43,43,42,41,40,38,38,36,35,36,35,34,32,31,30,29,28,27,27,26,25,24,24,23,22,20,20,19,18,16,17,19,20,21,21,22,23,24,23,24,25,26,27,28,28,29,30,31,31,31,33,33,33,35,35,37,37,38,39,39,40,40,42,42,43,44,43,45,46,46,46,47,49,50,50,51,51,52,53,54,55,55,56,57,57,57,58,60,60,61,62,63,64,65,65,67,68,69,69,71,72,72,73,74,76,76,78,79,80,80,82,83,83,85,86,87,87,89,90,91,94,97,100,102,104,107,111,113,116,118,122,123,127,129,132},
        {128,135,132,131,129,127,125,123,121,120,118,118,118,118,117,117,116,115,115,115,114,114,114,113,112,112,112,112,111,110,109,105,104,102,99,97,95,92,90,88,85,82,81,78,75,74,71,68,67,64,61,60,57,55,53,50,47,45,43,40,39,36,34,31,29,26,23,22,20,16,18,18,18,19,19,20,20,20,20,21,21,23,23,23,23,25,25,25,26,26,27,26,28,28,28,28,30,29,29,31,31,31,31,33,33,33,34,34,34,34,37,40,43,46,47,50,53,56,58,61,64,66,69,71,75,78,79,83,85,87,91,93,95,98,102,104,106,109,111,114,118,119,122,125,128,130,133,135,138,141,143,145,146,148,148,149,151,151,152,153,154,154,156,156,157,159,159,160,162,162,163,164,165,165,166,167,169,170,170,172,173,173,174,175,176,177,177,178,180,180,181,183,183,184,185,186,187,188,188,189,191,191,192,194,194,195,197,197,198,199,199,200,203,203,205,206,207,208,209,211,212,213,215,216,218,218,220,221,223,223,225,226,227,229,230,232,232,234,235,237,237,239,238,238,237,238,237,237,235,235,235,234,234,234,233,232,232}
    },

/* Blue-only color map
const uint8_t falseBlueColorLUT_YUV[3][257]
*/
    {
        {16,26,38,44,47,50,52,55,57,59,61,62,64,65,67,68,69,71,72,73,74,75,77,78,78,80,81,81,83,84,85,85,86,87,88,89,90,91,92,92,93,94,95,95,96,97,98,98,99,100,100,101,102,102,103,104,104,105,105,106,107,107,108,108,109,110,111,111,111,112,113,113,114,114,115,115,116,117,117,118,118,118,119,120,120,121,122,122,122,123,123,124,125,125,125,126,126,127,127,128,128,129,129,130,130,131,131,132,132,132,133,133,134,134,135,135,135,136,136,137,137,138,138,138,139,139,140,140,140,141,141,142,142,142,143,143,144,144,144,145,145,146,146,146,147,147,148,148,148,148,149,149,150,150,151,151,151,151,152,152,153,153,154,154,155,155,155,155,155,156,156,157,157,157,158,158,158,158,159,159,160,160,160,161,161,162,162,162,162,163,163,163,164,164,165,165,166,166,166,166,166,167,167,167,168,168,168,169,169,169,169,170,170,171,171,171,172,172,172,173,173,173,173,174,174,174,174,175,175,175,176,176,176,176,177,177,177,178,178,178,179,179,179,179,180,180,180,181,181,181,181,182,182,182,182,183,183,},
        {128,173,172,171,171,170,170,170,170,170,170,169,169,169,169,169,169,169,168,168,168,168,168,168,168,168,168,168,167,167,167,167,167,167,167,167,167,167,167,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,166,165,166,165,165,165,165,165,165,165,165,165,165,165,165,165,165,165,164,165,164,164,164,164,164,164,164,164,164,164,164,164,164,164,163,164,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,163,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,162,161,162,161,162,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,161,160,161,161,160,161,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,160,159,160,159,159,160,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,159,158,159,159,158,159,159,158,158,158,158,158,158,158,158,158,158,158,158,158,158,158,},
        {128,121,119,119,118,118,118,117,117,117,117,116,116,116,116,116,116,116,115,115,115,115,115,115,115,114,114,114,114,114,114,114,114,114,113,113,113,113,113,113,113,113,113,112,112,112,112,112,112,112,112,112,112,112,112,112,111,112,111,111,111,111,111,111,111,111,110,111,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,109,110,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,108,109,109,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,107,108,107,107,107,107,107,107,107,107,107,107,107,107,107,106,107,106,107,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,105,106,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,104,105,105,104,104,104,104,104,104,104,104,104,104,104,104,104,104,103,104,104,104,104,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,102,103,103,102,103,103,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,}
    }

};

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plug-ins of stereoPostProcess algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcess_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
            AlgorithmLink_StereoPostProcessCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
            AlgorithmLink_StereoPostProcessProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
            AlgorithmLink_StereoPostProcessControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
            AlgorithmLink_StereoPostProcessStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
            AlgorithmLink_StereoPostProcessDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_STEREO_POST_PROCESS;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Feature Plane Alg uses the IVISION standard to interact with the
 *        framework. All process/control calls to the algorithm should adhere
 *        to the IVISION standard. This function initializes input and output
 *        buffers
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
UInt32 AlgorithmLink_StereoPostProcessInitIOBuffers(
        AlgorithmLink_StereoPostProcessObj *pObj,
        AlgorithmLink_StereoPostProcessCreateParams * pLinkCreateParams)
{
    IVISION_InBufs      * pInBufs;
    IVISION_OutBufs     * pOutBufs;
    UInt32              idx;

    pInBufs         = &pObj->inBufs;
    pInBufs->size   = sizeof(IVISION_InBufs);
    pInBufs->numBufs    = STEREOVISION_TI_BUFDESC_IN_TOTAL;
    pInBufs->bufDesc = pObj->inBufDescList;
    for(idx = 0 ; idx < STEREOVISION_TI_BUFDESC_IN_TOTAL ;idx++)
    {
        pObj->inBufDescList[idx] = &pObj->inBufDesc[idx];
        pObj->inBufDesc[idx].numPlanes  = 1;
    }

    pOutBufs        = &pObj->outBufs;
    pOutBufs->size  = sizeof(IVISION_OutBufs);
    pOutBufs->numBufs   = STEREOVISION_TI_BUFDESC_OUT_TOTAL;
    pOutBufs->bufDesc= pObj->outBufDescList;
    for(idx = 0 ; idx < STEREOVISION_TI_BUFDESC_OUT_TOTAL ;idx++)
    {
        pObj->outBufDescList[idx] = &pObj->outBufDesc[idx];
        pObj->outBufDesc[idx].numPlanes  = 1;
    }

    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->numPlanes = 1;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.topLeft.x
    = pLinkCreateParams->imageStartX;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.topLeft.y
    = pLinkCreateParams->imageStartY;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].width              = pLinkCreateParams->censusSrcImageWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].height             = pLinkCreateParams->censusSrcImageHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.width     = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].frameROI.height    = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].planeType          = 0; // Luma Y
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_IMAGE]->bufPlanes[0].buf = NULL;


    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->numPlanes                       = 1;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.topLeft.x = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.topLeft.y = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].width              = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].height             = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.width     = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].frameROI.height    = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].planeType          = 0; // Luma Y
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_DISPARITY]->bufPlanes[0].buf = NULL;

    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->numPlanes                       = 1;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.topLeft.x = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.topLeft.y = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].width              = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].height             = pLinkCreateParams->maxImageRoiHeight/2;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.width     = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].frameROI.height    = pLinkCreateParams->maxImageRoiHeight/2;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].planeType          = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY]->bufPlanes[0].buf = NULL;

    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->numPlanes                       = 1;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.topLeft.x = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.topLeft.y = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].width              = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].height             = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.width     = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].frameROI.height    = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].planeType          = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_PREV_COST]->bufPlanes[0].buf= NULL;

    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->numPlanes                       = 1;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.topLeft.x = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.topLeft.y = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].width              = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].height             = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.width     = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].frameROI.height    = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].planeType          = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_COST]->bufPlanes[0].buf= NULL;

    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->numPlanes                       = 1;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.topLeft.x = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.topLeft.y = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].width              = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].height             = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.width     = pLinkCreateParams->maxImageRoiWidth;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].frameROI.height    = pLinkCreateParams->maxImageRoiHeight;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].planeType          = 0;
    pInBufs->bufDesc[STEREOVISION_TI_BUFDESC_IN_NEXT_COST]->bufPlanes[0].buf= NULL;

    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->numPlanes                        = 1;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.topLeft.x  = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.topLeft.y  = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].width               = pLinkCreateParams->maxImageRoiWidth;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].height              = pLinkCreateParams->maxImageRoiHeight;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.width      = pLinkCreateParams->maxImageRoiWidth;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].frameROI.height     = pLinkCreateParams->maxImageRoiHeight;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].planeType           = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_DISPARITY]->bufPlanes[0].buf = NULL;

    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->numPlanes                        = 1;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.topLeft.x  = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.topLeft.y  = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].width               = pLinkCreateParams->maxImageRoiWidth;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].height              = pLinkCreateParams->maxImageRoiHeight;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.width      = pLinkCreateParams->maxImageRoiWidth;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].frameROI.height     = pLinkCreateParams->maxImageRoiHeight;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].planeType           = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE]->bufPlanes[0].buf = NULL;

    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->numPlanes                        = 1;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.topLeft.x  = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.topLeft.y  = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].width               = pLinkCreateParams->maxImageRoiWidth;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].height              = pLinkCreateParams->maxImageRoiHeight;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.width      = pLinkCreateParams->maxImageRoiWidth;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].frameROI.height     = pLinkCreateParams->maxImageRoiHeight;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].planeType           = 0;
    pOutBufs->bufDesc[STEREOVISION_TI_BUFDESC_OUT_TEXTURE]->bufPlanes[0].buf = NULL;

    /*
     * Texture is buf size
     * Disparity and Confidence is 2*bufsize
     */
    pObj->outBufferSize = pLinkCreateParams->maxImageRoiWidth*pLinkCreateParams->maxImageRoiHeight;

    return SYSTEM_LINK_STATUS_SOK;

}

Void AlgorithmLink_StereoPostProcessSetIOArgs
( AlgorithmLink_StereoPostProcessObj *pObj)
{
    pObj->outArgs.iVisionOutArgs.size = sizeof(STEREOVISION_TI_OutArgs);
    pObj->inArgs.iVisionInArgs.size = sizeof(STEREOVISION_TI_InArgs);
    pObj->inArgs.iVisionInArgs.subFrameInfo = 0;
    pObj->inArgs.iVisionInArgs.size = sizeof(STEREOVISION_TI_InArgs);
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for disparity alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcessCreate(void *pObj,void *pCreateParams)
{
    UInt32                                      status = SYSTEM_LINK_STATUS_SOK;
    UInt32                                      bufferSize;
    UInt32                                      prevLinkQueId;
    UInt32                                      bufId;
    UInt32                                      numInputQUsed;
    UInt32                                      numOutputQUsed;
    UInt32                                      outputQId;
    UInt32                                      idx, numPlanes, channelId;
    UInt32                                      outputChId;
    System_LinkInfo                             prevLinkInfo;
    System_LinkChInfo                           * pOutChInfo, * pPrevChInfo;
    AlgorithmLink_InputQueueInfo                * pInputQInfo;
    AlgorithmLink_OutputQueueInfo               * pOutputQInfo;
    AlgorithmLink_StereoPostProcessCreateParams  * pLinkCreateParams;
    AlgorithmLink_StereoPostProcessObj           * pStereoPostProcessObj;
    System_VideoFrameBuffer                     * pSysVideoFrameOutput;
    System_MetaDataBuffer                       * pSystemMetaDataBuffer;
    System_Buffer                               * pSystemBuffer;
    System_Buffer                               * pSysOutBuffer16BitDisparity;
    STEREOVISION_TI_CreateParams           * pAlgCreateParams;
    STEREOVISION_TI_InArgs              *pInArgs;

    pLinkCreateParams = (AlgorithmLink_StereoPostProcessCreateParams *)
                                 pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pStereoPostProcessObj = (AlgorithmLink_StereoPostProcessObj *)
                            Utils_memAlloc(
                                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                                    sizeof(AlgorithmLink_StereoPostProcessObj),
                                    32);
    UTILS_assert(pStereoPostProcessObj != NULL);
    AlgorithmLink_setAlgorithmParamsObj(pObj, pStereoPostProcessObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pStereoPostProcessObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_StereoPostProcessCreateParams)
    );

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */
    pAlgCreateParams  = &pStereoPostProcessObj->algCreateParams;
    pAlgCreateParams->visionParams.algParams.size = sizeof(*pAlgCreateParams);
    pAlgCreateParams->visionParams.cacheWriteBack = NULL;
    pAlgCreateParams->maxImageRoiWidth = pLinkCreateParams->maxImageRoiWidth;
    pAlgCreateParams->maxImageRoiHeight = pLinkCreateParams->maxImageRoiHeight;
    pAlgCreateParams->inputBitDepth = pLinkCreateParams->inputBitDepth;

    pAlgCreateParams->processingMode = STEREOVISION_TI_POSTPROCESS_ONLY;

    pAlgCreateParams->disparityOptions.censusWinHeight = pLinkCreateParams->censusWinHeight;
    pAlgCreateParams->disparityOptions.censusWinWidth= pLinkCreateParams->censusWinWidth;
    pAlgCreateParams->disparityOptions.costMethod= STEREOVISION_TI_HAM_DIST;
    pAlgCreateParams->disparityOptions.disparityStep= pLinkCreateParams->disparityStep;
    pAlgCreateParams->disparityOptions.costSupportWinHeight= pLinkCreateParams->disparityWinHeight;
    pAlgCreateParams->disparityOptions.costSupportWinWidth= pLinkCreateParams->disparityWinWidth;
    pAlgCreateParams->disparityOptions.maxDisparity= pLinkCreateParams->numDisparities - 1;
    pAlgCreateParams->disparityOptions.minDisparity= 0;
    pAlgCreateParams->disparityOptions.searchDir= pLinkCreateParams->disparitySearchDir;

    pInArgs=&pStereoPostProcessObj->inArgs;
    pInArgs->postProcOptions.costMaxThreshold=pLinkCreateParams->costMaxThreshold;
    pInArgs->postProcOptions.disparityMaxThreshold= pLinkCreateParams->numDisparities;
    pInArgs->postProcOptions.disparityMinThreshold= 0;
    pInArgs->postProcOptions.disparityNumFracBits= pLinkCreateParams->numFracBits;
    pInArgs->postProcOptions.holeFillingStrength= pLinkCreateParams->holeFillingStrength;
    pInArgs->postProcOptions.minConfidenceThreshold= pLinkCreateParams->minConfidenceThreshold;
    pInArgs->postProcOptions.smoothingStrength=STEREOVISION_TI_SMOOTHING_STRENGTH_NONE;
    pInArgs->postProcOptions.textureLumaHiThresh= pLinkCreateParams->textureLumaHiThresh;
    pInArgs->postProcOptions.textureLumaLoThresh= pLinkCreateParams->textureLumaLoThresh;
    pInArgs->postProcOptions.textureThreshold= pLinkCreateParams->textureThreshold;
    pInArgs->postProcOptions.lrMaxDiffThreshold= pLinkCreateParams->lrMaxDiffThreshold;
    pInArgs->postProcOptions.maxDispDissimilarity= pLinkCreateParams->maxDispDissimilarity;
    pInArgs->postProcOptions.minConfidentNSegment= pLinkCreateParams->minConfidentNSegment;
    pInArgs->postProcOptions.auxDisparityHorzDsFactor= 1;
    pInArgs->postProcOptions.auxDisparityVertDsFactor= 2;

    pInArgs->postProcOptions.enable16BitsDispOut = pLinkCreateParams->enable16BitsDispOut;
    pAlgCreateParams->edma3RmLldHandle  = NULL;

    pStereoPostProcessObj->handle = AlgIvision_create(&STEREOVISION_TI_VISION_FXNS, (IALG_Params *)(pAlgCreateParams));
    UTILS_assert(pStereoPostProcessObj->handle!=NULL);

    /*
     * Populating parameters corresponding to Q usage of stereoPostProcess
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = ALGLINK_STEREOPP_OPQID_MAXOPQ;
    pInputQInfo                 = &pStereoPostProcessObj->inputQInfo;
    pOutputQInfo                = &pStereoPostProcessObj->outputQInfo[0];

    pInputQInfo->qMode                                         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[ALGLINK_STEREOPP_OPQID_DISPARITY].qMode       = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY].qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    //outputQId                   = 0;
    //outputChId                  = 0;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In stereoPostProcess Link, only data format changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(
            pLinkCreateParams->inQueParams.prevLinkId,
            &prevLinkInfo
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= numInputQUsed);

    prevLinkQueId = pLinkCreateParams->inQueParams.prevLinkQueId;
    pStereoPostProcessObj->numInputChannels
    = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    /* Disparity Alg link will only output 1 channel for the disparity output */
    pOutputQInfo[ALGLINK_STEREOPP_OPQID_DISPARITY].queInfo.numCh = 1;
    pOutputQInfo[ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY].queInfo.numCh = 1;

    /*
     * Initialize input output buffers TBD
     */
    AlgorithmLink_StereoPostProcessInitIOBuffers(pStereoPostProcessObj,
            pLinkCreateParams);
    AlgorithmLink_StereoPostProcessSetIOArgs(pStereoPostProcessObj);

    /*
     * Channel Info Population
     */
    outputQId  = ALGLINK_STEREOPP_OPQID_DISPARITY;
    outputChId = 0;

    pOutChInfo      = &(pOutputQInfo[outputQId].queInfo.chInfo[outputChId]);
    pPrevChInfo = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[outputChId]);
    pOutChInfo->startX = pPrevChInfo->startX;
    pOutChInfo->startY = pPrevChInfo->startY;
    pOutChInfo->width  = pPrevChInfo->width;
    pOutChInfo->height = pPrevChInfo->height;
    pOutChInfo->flags = pPrevChInfo->flags;
    pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pOutChInfo->flags,
            SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
    pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pOutChInfo->flags,
            SYSTEM_DF_YUV420SP_UV);
    pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pOutChInfo->flags, SYSTEM_SF_PROGRESSIVE);

    //TBD
    pOutChInfo->pitch[0] = pOutChInfo->width;
    pOutChInfo->pitch[1] = pOutChInfo->width;
    pOutChInfo->pitch[2] = 0;

    /* For temporal filter */
    pStereoPostProcessObj->temporalFilterNumFrames= pLinkCreateParams->temporalFilterNumFrames; /* It is the number of frames during which a pixel must have non zero value before being displayed*/

    pStereoPostProcessObj->imagePitch[0]= pOutChInfo->width;
    pStereoPostProcessObj->imagePitch[1] = pOutChInfo->width;
    pStereoPostProcessObj->imagePitch[2] = 0;

    pStereoPostProcessObj->imageHeight[0] = pOutChInfo->height;
    pStereoPostProcessObj->imageHeight[1] = pOutChInfo->height;
    pStereoPostProcessObj->imageHeight[2] = 0;

    /*
     * Channel info population for output Q Id - ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY
     */
    if (pLinkCreateParams->enable16BitsDispOut)
    {
        outputQId  = ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY;
        outputChId = 0;
        pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[outputChId]);
        pOutChInfo->flags = 0;
    }

    /*
     * Taking a copy of input channel info in the link object for any future
     * use
     */
    for(idx =0 ; idx < pStereoPostProcessObj->numInputChannels; idx++)
    {

        memcpy((void *)&(pStereoPostProcessObj->inputChInfo[idx]),
                (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[idx]),
                sizeof(System_LinkChInfo)
        );
    }

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    status = AlgorithmLink_queueInfoInit(
            pObj,
            numInputQUsed,
            pInputQInfo,
            numOutputQUsed,
            pOutputQInfo
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */
    outputQId = ALGLINK_STEREOPP_OPQID_DISPARITY;
    channelId = 0;

    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer =   &pStereoPostProcessObj->buffers[outputQId][bufId];
        pSysVideoFrameOutput
        = &pStereoPostProcessObj->videoFrames[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->payload      =   pSysVideoFrameOutput;
        pSystemBuffer->payloadSize  =   sizeof(System_VideoFrameBuffer);
        pSystemBuffer->chNum        =   0;

        memcpy((void *)&pSysVideoFrameOutput->chInfo,
                (void *)&pOutputQInfo[outputQId].queInfo.chInfo[channelId],
                sizeof(System_LinkChInfo));

        /* 0 indicates progrssive*/
        pSysVideoFrameOutput->flags = System_Video_Frame_Set_Flag_Fid(pSysVideoFrameOutput->flags, 0);

        //Two Planes
        numPlanes = 2;
        for(idx = 0; idx <numPlanes; idx++)
        {
            bufferSize = pStereoPostProcessObj->imageHeight[idx] *
                    pStereoPostProcessObj->imagePitch[idx];

            pSysVideoFrameOutput->bufAddr[idx] = Utils_memAlloc(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    bufferSize,
                    ALGORITHMLINK_FRAME_ALIGN
            );
            UTILS_assert(pSysVideoFrameOutput->bufAddr[idx] != NULL);
        }

        status = AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /*
     * Allocate buffer for 16-bit disparity output
     */
    if (pLinkCreateParams->enable16BitsDispOut)
    {
        outputQId = ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY;
        channelId = 0;
        for (bufId = 0; bufId < pLinkCreateParams->num16BitDispOutBuffers; bufId++)
        {
            pSysOutBuffer16BitDisparity =  &pStereoPostProcessObj->buffers[outputQId][bufId];
            pSystemMetaDataBuffer = &pStereoPostProcessObj->disparity16bit[bufId];

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSysOutBuffer16BitDisparity->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
            pSysOutBuffer16BitDisparity->payload      =   pSystemMetaDataBuffer;
            pSysOutBuffer16BitDisparity->payloadSize  =   sizeof(System_MetaDataBuffer);
            pSysOutBuffer16BitDisparity->chNum        =   channelId;

            // set buffer size
            bufferSize = pStereoPostProcessObj->imageHeight[0] *
                    pStereoPostProcessObj->imagePitch[0] * 2; // 2 bytes

            pSystemMetaDataBuffer->numMetaDataPlanes = 1;
            pSystemMetaDataBuffer->bufAddr[0] =  Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    bufferSize,
                                                    ALGORITHMLINK_FRAME_ALIGN);

            pSystemMetaDataBuffer->metaBufSize[0]    = bufferSize;
            pSystemMetaDataBuffer->metaFillLength[0] = bufferSize;
            pSystemMetaDataBuffer->flags             = 0;

            UTILS_assert(pSystemMetaDataBuffer->bufAddr[0] != NULL);

            status = AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSysOutBuffer16BitDisparity);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    //Allocating buffers for the Post Proc output - disparity, texture and confidence
    pStereoPostProcessObj->circIdx= 0;
    pStereoPostProcessObj->postProcOutput[0].numMetaDataPlanes = 3;
    pStereoPostProcessObj->postProcOutput[1].numMetaDataPlanes = 3;
    pStereoPostProcessObj->postProcOutput[2].numMetaDataPlanes = 3;
    for(idx = 0; idx <pStereoPostProcessObj->postProcOutput[0].numMetaDataPlanes; idx++)
    {
        pStereoPostProcessObj->postProcOutput[0].metaBufSize[idx] = pStereoPostProcessObj->outBufferSize*2;
        pStereoPostProcessObj->postProcOutput[0].metaFillLength[idx] = pStereoPostProcessObj->outBufferSize*2;
        pStereoPostProcessObj->postProcOutput[0].bufAddr[idx] =  Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pStereoPostProcessObj->outBufferSize*2,
                ALGORITHMLINK_FRAME_ALIGN
        );

        pStereoPostProcessObj->postProcOutput[1].metaBufSize[idx]= pStereoPostProcessObj->postProcOutput[0].metaBufSize[idx];
        pStereoPostProcessObj->postProcOutput[2].metaBufSize[idx]= pStereoPostProcessObj->postProcOutput[0].metaBufSize[idx];
        pStereoPostProcessObj->postProcOutput[3].metaBufSize[idx]= pStereoPostProcessObj->postProcOutput[0].metaBufSize[idx];
        pStereoPostProcessObj->postProcOutput[1].metaFillLength[idx] = pStereoPostProcessObj->postProcOutput[0].metaFillLength[idx];
        pStereoPostProcessObj->postProcOutput[2].metaFillLength[idx] = pStereoPostProcessObj->postProcOutput[0].metaFillLength[idx];
        pStereoPostProcessObj->postProcOutput[3].metaFillLength[idx] = pStereoPostProcessObj->postProcOutput[0].metaFillLength[idx];
        pStereoPostProcessObj->postProcOutput[1].bufAddr[idx] =  pStereoPostProcessObj->postProcOutput[0].bufAddr[idx];
        pStereoPostProcessObj->postProcOutput[2].bufAddr[idx] =  pStereoPostProcessObj->postProcOutput[0].bufAddr[idx];
        pStereoPostProcessObj->postProcOutput[3].bufAddr[idx] =  pStereoPostProcessObj->postProcOutput[0].bufAddr[idx];
    }

    /* For median filter, we must allocate two extra memory buffers for the disparity plane idx= 0
           We also allocated an extra memory buffer to store the final output */
    pStereoPostProcessObj->postProcOutput[1].bufAddr[0]=  Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pStereoPostProcessObj->outBufferSize*2,
            ALGORITHMLINK_FRAME_ALIGN
    );

    pStereoPostProcessObj->postProcOutput[2].bufAddr[0]=  Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pStereoPostProcessObj->outBufferSize*2,
            ALGORITHMLINK_FRAME_ALIGN
    );
    pStereoPostProcessObj->postProcOutput[3].bufAddr[0]=  Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pStereoPostProcessObj->outBufferSize*2,
            ALGORITHMLINK_FRAME_ALIGN
    );

    memset(pStereoPostProcessObj->postProcOutput[3].bufAddr[0], 0, pStereoPostProcessObj->outBufferSize);

    /*
     * Creation of local input Qs for disparity, Left and Right streams.
     */
     for(idx = 0; idx < PPROC_LINK_MAX_NUM_INPUT_CHANNELS; idx++)
     {
         status  = Utils_queCreate(&(pStereoPostProcessObj->localInputQ[idx].queHandle),
                 PPROC_LINK_MAX_LOCALQUEUELENGTH,
                 (pStereoPostProcessObj->localInputQ[idx].queMem),
                 UTILS_QUE_FLAG_NO_BLOCK_QUE);
         UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
     }

     pStereoPostProcessObj->isFirstFrameRecv    = FALSE;

    /* Assign pointer to link stats object */
    pStereoPostProcessObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_STEREO_POSTPROCESS");
    UTILS_assert(NULL != pStereoPostProcessObj->linkStatsInfo);

     return status;
}

void AlgorithmLink_StereoPostProcess_medianTemporalFilter(
        uint32_t * restrict dispOutput2,
        uint32_t * restrict dispOutput1,
        uint32_t * restrict dispOutput0,
        uint32_t * restrict dispOutput,
        uint16_t width,
        uint16_t height) {

    uint32_t x, d2, d1, d0, a00, a01, a11, median;

    _nassert((int)dispOutput2 % 4 == 0);
    _nassert((int)dispOutput1 % 4 == 0);
    _nassert((int)dispOutput0 % 4 == 0);

    for (x = 0; x < ((width*height)/4); x++)
    {
        d2 = _amem4(dispOutput2++);
        d1 = _amem4(dispOutput1++);
        d0 = _amem4(dispOutput0++);

        a00= _minu4(d0,d1);
        a01= _maxu4(d0,d1);

        a11= _minu4(a01,d2);

        median= _maxu4(a00, a11);

        _amem4(dispOutput++)= median;
    }

}

void AlgorithmLink_StereoPostProcess_temporalFilter(
        uint32_t * restrict dispOutput,
        uint32_t * restrict lifeTime,
        uint32_t * restrict lastValidValue,
        uint16_t width,
        uint16_t height,
        int8_t maxLifeTime) {

    uint32_t x, d, life, zeroFlag, nonZeroFlag, zeroMask, nonZeroMask, packedMaxLifeTime;
    uint32_t upperBound, temp, decVal, incVal, displayFlag, displayMask, lifeNonZeroFlag;
    uint32_t lastValid;

    uint32_t v01010101= 0x01010101;
    uint32_t vffffffff= 0xFFFFFFFF;

    temp= (maxLifeTime << 16) | maxLifeTime;
    packedMaxLifeTime= _packl4(temp,temp);

    temp= (maxLifeTime << 17) | (maxLifeTime<<1);
    upperBound= _packl4(temp,temp);

    _nassert((int)dispOutput % 4 == 0);
    _nassert((int)lifeTime % 4 == 0);

#pragma MUST_ITERATE(64, ,2)
    for (x = 0; x < ((width*height)/4); x++)
    {
        d = _amem4(dispOutput);
        life = _amem4(lifeTime);
        lastValid= _amem4(lastValidValue++);

        zeroFlag= _cmpeq4(d, 0);
        lifeNonZeroFlag= _cmpgtu4(life, 0);

        nonZeroFlag= ~zeroFlag;
        zeroFlag= zeroFlag & lifeNonZeroFlag;

        nonZeroMask= _xpnd4(nonZeroFlag);
        zeroMask= _xpnd4(zeroFlag);

        incVal= v01010101 & nonZeroMask;
        decVal= vffffffff & zeroMask;

        life= _add4(life, incVal);
        life= _add4(life, decVal);

        life= _minu4(life, upperBound);

        displayFlag= _cmpgtu4(life, packedMaxLifeTime);
        displayMask= _xpnd4(displayFlag);

        /* if life is greater than maskLifeTime we will display the disparity
            we either display the disparity value 'd' if not zero or if it is zero, we display the lastValid disparity
        */
        lastValid= lastValid & zeroMask;
        d= d & displayMask;
        lastValid= lastValid & displayMask;
        d= d & nonZeroMask;
        d= d | lastValid;

        _amem4(dispOutput++)= d;
        _amem4(lifeTime++)= life;

    }

}

#if 0
void AlgorithmLink_StereoPostProcess_medianTemporalFilter(
        uint32_t * restrict dispOutput2,
        uint32_t * restrict dispOutput1,
        uint32_t * restrict dispOutput0,
        uint32_t * restrict dispOutput,
        uint16_t width,
        uint16_t height) {

    uint32_t x, d2, d1, d0, a00, a01, a11, median;

    _nassert((int)dispOutput2 % 4 == 0);
    _nassert((int)dispOutput1 % 4 == 0);
    _nassert((int)dispOutput0 % 4 == 0);

    for (x = 0; x < ((width*height)/8); x++)
    {
        d2_a = _amem4(dispOutput2++);
        d2_b = _amem4(dispOutput2++);
        d1_a = _amem4(dispOutput1++);
        d1_b = _amem4(dispOutput1++);
        d0_a = _amem4(dispOutput0++);
        d0_b = _amem4(dispOutput0++);

        a00_a= _minu4(d0_a,d1_a);
        a00_b= _minu4(d0_b,d1_b);

        a01_a= _maxu4(d0_a,d1_a);
        a01_b= _maxu4(d0_b,d1_b);

        a11_a= _minu4(a01_a,d2_a);
        a11_b= _minu4(a01_b,d2_b);

        median_a= _maxu4(a00_a, a11_a);
        median_b= _maxu4(a00_b, a11_b);

        _amem4(dispOutput++)= median_a;
        _amem4(dispOutput++)= median_b;
    }

}
#endif

/**
 *******************************************************************************
 *
 * \brief Coverts disparity output into YUV
 *
 *
 * \param
 *
 * \return  void
 *
 *******************************************************************************
 */
#if DISPARITY_16BITS
void AlgorithmLink_StereoPostProcess_convertDisparityFalseColorYUV420SP_opt(
        uint8_t *image_y,
        uint8_t *image_uv,
        uint16_t *dispOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        uint8_t minDisparity,
        uint8_t falseColorLUT_YUV[][257],
        uint8_t numFracBits,
        Bool    useGrayScale)
#else
void AlgorithmLink_StereoPostProcess_convertDisparityFalseColorYUV420SP_opt(
        uint8_t *image_y,
        uint8_t *image_uv,
        uint8_t *dispOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        uint8_t minDisparity,
        uint8_t falseColorLUT_YUV[][257],
        Bool    useGrayScale)
#endif
{


    int32_t x, y, idx, shiftFactor=0;

    /* The code assumes that numDisparity is multiple of 2, else the o/p will not be scaled properly*/

    while (numDisparities != 0)
    {
        numDisparities = numDisparities>>1;
        shiftFactor++;
    }
    shiftFactor --; /* Decrement 1 mak the count correct  */
    shiftFactor = 8 - shiftFactor; /* this results in -> 256 / numDisparity */

    minDisparity= minDisparity << shiftFactor;

    if (useGrayScale)
    {
        idx= 0;
        for (y = 0; y < height; y++)
        {
            for (x = 0; x < (width); x++)
            {
#if DISPARITY_16BITS
                    *image_y++ = (dispOutput[idx++] >> numFracBits)  << shiftFactor;
#else
                    *image_y++ = dispOutput[idx++]  << shiftFactor;
#endif
                    *image_uv++ = 128;
            }
        }
    }
    else
    {
        uint8_t *falseColorY, *falseColorU, *falseColorV;
        int32_t value1, value2, value3, value4;
        falseColorY = (uint8_t *)falseColorLUT_YUV[0];
        falseColorU = (uint8_t *)falseColorLUT_YUV[1];
        falseColorV = (uint8_t *)falseColorLUT_YUV[2];

        idx= 0;
        for (y = 0; y < height; y++)
        {
            if((y & 0x1) == 0) // Even lines
            {
                for (x = 0; x < (width/4); x++) // loop unrolled 4 time
                {
#if DISPARITY_16BITS
                    value1 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
                    value2 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
                    value3 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
                    value4 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
#else
                    value1 = dispOutput[idx++] << shiftFactor;
                    value2 = dispOutput[idx++] << shiftFactor;
                    value3 = dispOutput[idx++] << shiftFactor;
                    value4 = dispOutput[idx++] << shiftFactor;
#endif

                    value1-= minDisparity;
                    value2-= minDisparity;
                    value3-= minDisparity;
                    value4-= minDisparity;

                    value1= (value1 < 0) ? 0 : value1;
                    value2= (value2 < 0) ? 0 : value2;
                    value3= (value3 < 0) ? 0 : value3;
                    value4= (value4 < 0) ? 0 : value4;

                    *image_y++ = (uint8_t) (falseColorY[value1]);
                    *image_y++ = (uint8_t) (falseColorY[value2]);
                    *image_y++ = (uint8_t) (falseColorY[value3]);
                    *image_y++ = (uint8_t) (falseColorY[value4]);

                    *image_uv++ = (uint8_t)(falseColorU[value1]);
                    *image_uv++ = (uint8_t)(falseColorV[value2]);
                    *image_uv++ = (uint8_t)(falseColorU[value3]);
                    *image_uv++ = (uint8_t)(falseColorV[value4]);

                }
            }
            else // Odd lines
            {
                for (x = 0; x < (width/4); x++) // loop unrolled 4 time
                {

#if DISPARITY_16BITS
                    value1 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
                    value2 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
                    value3 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
                    value4 = (dispOutput[idx++] >> numFracBits) << shiftFactor;
#else
                    value1 = dispOutput[idx++] << shiftFactor;
                    value2 = dispOutput[idx++] << shiftFactor;
                    value3 = dispOutput[idx++] << shiftFactor;
                    value4 = dispOutput[idx++] << shiftFactor;
#endif

                    *image_y++ = (uint8_t) (falseColorY[value1]);
                    *image_y++ = (uint8_t) (falseColorY[value2]);
                    *image_y++ = (uint8_t) (falseColorY[value3]);
                    *image_y++ = (uint8_t) (falseColorY[value4]);

                }
            }

        }
    }
}

#if 0
Int32  AlgorithmLink_StereoPostProcess_convertDisparityFalseColorYUV420SP(
        uint8_t * restrict image_y,
        uint8_t * restrict image_uv,
        uint8_t * restrict dispOutput,
        uint16_t * restrict costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio) {

    int32_t x, y, value, idx=0;
    uint16_t maxCost= 0;

    /* First, search for the maxCost */

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (costOutput[idx] > maxCost) {
                maxCost = costOutput[idx];
            }
            idx++;
        }
    }

    maxCost= (uint16_t)(maxMinCostRatio*(float)maxCost);

    idx= 0;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (costOutput[idx] <= maxCost)
                value = (dispOutput[idx] * (int32_t)255)/numDisparities;
            else
                value= 0;

            image_y[y*width + x] = (uint8_t) (falseColorLUT_YUV[0][value]);
            image_uv[(y>>1)*width + ((x>>1)<<1)] = (uint8_t)(falseColorLUT_YUV[1][value]);
            image_uv[(y>>1)*width + ((x>>1)<<1) + 1] = (uint8_t)(falseColorLUT_YUV[2][value]);
            idx++;
        }
    }
    return SYSTEM_LINK_STATUS_SOK;
}
#endif
/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for disparity algorithm link
 *
 *        This function executes on the EVE The processor gets locked with
 *        execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcessProcess(void * pObj)
{
    UInt32                                  idx, status = SYSTEM_LINK_STATUS_SOK;

    UInt32                                  bufId;
    UInt32                                  inputQId;
    UInt32                                  outputQId, channelId;
    Bool                                    bufDropFlag[2] = {FALSE};
    Bool                                    isProcessCallDoneFlag;
    AlgorithmLink_StereoPostProcessObj                 * pStereoPostProcessObj;
    AlgorithmLink_StereoPostProcessCreateParams        * pLinkCreateParams;
    System_Buffer                                     * pSysOutBuffer;
    System_Buffer                               * pSysOutBuffer16BitDisparity;
    System_Buffer                                     * pSysInBuffer;
    System_Buffer                                * pSysBufferMetadata;
    System_Buffer                                * pSysBufferLRVideo;
    System_BufferList                                 inputBufList;
    System_BufferList                                 outputBufListReturn;
    System_BufferList                                 inputBufListReturn;
    System_VideoFrameBuffer                       * pSysVideoFrameOutput;
    System_MetaDataBuffer *pSysMetaDataBufInput, *pSysMetaDataBufOutput;
    System_MetaDataBuffer *pSysMetaDataBuf16BitOutput;
#ifdef _INCLUDE_TEMPORAL_NOISE_FILTER
    System_MetaDataBuffer *pSysMetaDataBufOutput1;
    System_MetaDataBuffer *pSysMetaDataBufMedianOutput;
#endif
    System_VideoFrameCompositeBuffer              * pSysCompositeBufferInput;

    IVISION_InBufs                      *pInBufs;
    IVISION_OutBufs                     *pOutBufs;
    STEREOVISION_TI_InArgs              *pInArgs;
    STEREOVISION_TI_OutArgs             *pOutArgs;
    System_LinkStatistics               *linkStatsInfo;

    pStereoPostProcessObj = (AlgorithmLink_StereoPostProcessObj *)
                                        AlgorithmLink_getAlgorithmParamsObj(pObj);
#ifdef _INCLUDE_TEMPORAL_NOISE_FILTER
    pSysMetaDataBufMedianOutput= &pStereoPostProcessObj->postProcOutput[3];
#endif
    pLinkCreateParams = &pStereoPostProcessObj->algLinkCreateParams;

    pInBufs  = &pStereoPostProcessObj->inBufs;
    pOutBufs = &pStereoPostProcessObj->outBufs;

    linkStatsInfo = pStereoPostProcessObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(
        linkStatsInfo);

    System_getLinksFullBuffers(
            pLinkCreateParams->inQueParams.prevLinkId,
            pLinkCreateParams->inQueParams.prevLinkQueId,
            &inputBufList);

    if(inputBufList.numBuf)
    {
        linkStatsInfo->linkStats.newDataCmdCount++;

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];

            if (pSysInBuffer != NULL)
            {
                channelId = pSysInBuffer->chNum;
                UTILS_assert (channelId < PPROC_LINK_MAX_NUM_INPUT_CHANNELS);

                status = Utils_quePut(
                        &(pStereoPostProcessObj->localInputQ[channelId].queHandle),
                        pSysInBuffer,
                        BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }

    while(1)
    {
        isProcessCallDoneFlag = FALSE;

        if (pStereoPostProcessObj->isFirstFrameRecv == FALSE)
        {
            pStereoPostProcessObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                    pStereoPostProcessObj->numInputChannels, 1);
            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        if(Utils_queGetQueuedCount(
                &(pStereoPostProcessObj->localInputQ[0].queHandle))>0
                &&
                Utils_queGetQueuedCount(
                        &(pStereoPostProcessObj->localInputQ[1].queHandle))>0
        )
        {
            inputBufListReturn.numBuf       = 0;

            status = Utils_queGet(
                    &(pStereoPostProcessObj->localInputQ[0].
                            queHandle),
                            (Ptr *)&pSysBufferMetadata,
                            1,
                            BSP_OSAL_NO_WAIT);
            UTILS_assert(pSysBufferMetadata != NULL);
            inputBufListReturn.buffers[inputBufListReturn.numBuf] = pSysBufferMetadata;
            inputBufListReturn.numBuf++;

            status = Utils_queGet(
                    &(pStereoPostProcessObj->localInputQ[1].
                            queHandle),
                            (Ptr *)&pSysBufferLRVideo,
                            1,
                            BSP_OSAL_NO_WAIT);
            UTILS_assert(pSysBufferLRVideo != NULL);
            inputBufListReturn.buffers[inputBufListReturn.numBuf] = pSysBufferLRVideo;
            inputBufListReturn.numBuf++;

            UTILS_assert (pSysBufferMetadata->srcTimestamp == pSysBufferLRVideo->srcTimestamp);

            channelId = pSysBufferMetadata->chNum;
            if(channelId < pStereoPostProcessObj->numInputChannels)
            {
                linkStatsInfo->linkStats.chStats[channelId]
                                                         .inBufRecvCount++;
            }

            /*
             * Getting free (empty) buffers from pool of output buffers
             */
            outputQId        = ALGLINK_STEREOPP_OPQID_DISPARITY;
            status = AlgorithmLink_getEmptyOutputBuffer(
                    pObj,
                    outputQId,
                    channelId,
                    &pSysOutBuffer
            );
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                linkStatsInfo->linkStats.chStats[channelId]
                                                         .inBufDropCount++;
                linkStatsInfo->linkStats.chStats[channelId]
                                                         .outBufDropCount[0]++;
            }
            else
            {
                // for 16-bit disparity output
                if (pLinkCreateParams->enable16BitsDispOut)
                {
                    outputQId = ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY;
                    status = AlgorithmLink_getEmptyOutputBuffer(
                            pObj,
                            outputQId,
                            channelId,
                            &pSysOutBuffer16BitDisparity);

                    if (status != SYSTEM_LINK_STATUS_SOK)
                    {

                        // free-up the previously allocated output buffer
                        AlgorithmLink_putEmptyOutputBuffer(pObj,
                                                        ALGLINK_STEREOPP_OPQID_DISPARITY,
                                                        pSysOutBuffer);
                        linkStatsInfo->linkStats.outBufErrorCount++;
                        break;
                    }

                    UTILS_assert(pSysOutBuffer16BitDisparity != NULL);

                    pSysOutBuffer16BitDisparity->srcTimestamp = pSysBufferMetadata->srcTimestamp;
                    pSysOutBuffer16BitDisparity->linkLocalTimestamp
                                    = Utils_getCurGlobalTimeInUsec();

                    pSysMetaDataBuf16BitOutput = (System_MetaDataBuffer *) pSysOutBuffer16BitDisparity->payload;
                }


                /*
                 * Get video frame buffer out of the system Buffer for both
                 * input and output buffers.
                 * Associate the input/output buffer pointers with inBufs
                 * and outBufs
                 * Record the bufferId with the address of the System Buffer
                 */

                isProcessCallDoneFlag = TRUE;

                pSysOutBuffer->srcTimestamp = pSysBufferMetadata->srcTimestamp;
                pSysOutBuffer->frameId = pSysBufferMetadata->frameId;
                pSysOutBuffer->linkLocalTimestamp
                = Utils_getCurGlobalTimeInUsec();

                pSysVideoFrameOutput
                = (System_VideoFrameBuffer*)pSysOutBuffer->payload;

                pSysMetaDataBufInput = (System_MetaDataBuffer *)
                                        pSysBufferMetadata->payload;

                pSysCompositeBufferInput
                = (System_VideoFrameCompositeBuffer *)pSysBufferLRVideo->payload;

                pSysMetaDataBufOutput = &pStereoPostProcessObj->postProcOutput[pStereoPostProcessObj->circIdx];
#ifdef _INCLUDE_TEMPORAL_NOISE_FILTER
                if (pStereoPostProcessObj->circIdx== 2) {
                    pSysMetaDataBufOutput1= &pStereoPostProcessObj->postProcOutput[1];
                    //pSysMetaDataBufOutput0= &pStereoPostProcessObj->postProcOutput[0];
                    pStereoPostProcessObj->circIdx= 0;
                }
                else if (pStereoPostProcessObj->circIdx== 1) {
                    pSysMetaDataBufOutput1= &pStereoPostProcessObj->postProcOutput[0];
                    //pSysMetaDataBufOutput0= &pStereoPostProcessObj->postProcOutput[2];
                    pStereoPostProcessObj->circIdx++;
                }
                else {
                    pSysMetaDataBufOutput1= &pStereoPostProcessObj->postProcOutput[2];
                    //pSysMetaDataBufOutput0= &pStereoPostProcessObj->postProcOutput[1];
                    pStereoPostProcessObj->circIdx++;
                }
#endif
                Cache_inv(
                        pSysMetaDataBufInput->bufAddr[0],
                        pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0],
                        Cache_Type_ALLD,
                        TRUE
                );

                Cache_inv(
                        pSysMetaDataBufInput->bufAddr[1],
                        pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0]*2,
                        Cache_Type_ALLD,
                        TRUE
                );

                Cache_inv(
                        pSysMetaDataBufInput->bufAddr[2],
                        pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0]*2,
                        Cache_Type_ALLD,
                        TRUE
                );

                Cache_inv(
                        pSysMetaDataBufInput->bufAddr[3],
                        pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0]*2,
                        Cache_Type_ALLD,
                        TRUE
                );


                Cache_inv(
                        pSysCompositeBufferInput->bufAddr[0][1],
                        pStereoPostProcessObj->algLinkCreateParams.censusSrcImageWidth* pStereoPostProcessObj->algLinkCreateParams.censusSrcImageHeight,
                        Cache_Type_ALLD,
                        TRUE
                );

                idx = STEREOVISION_TI_BUFDESC_IN_IMAGE;
#ifdef _TEST_STATIC_INPUT
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = gCensusTestLeftInput;
#else
                if (pStereoPostProcessObj->algLinkCreateParams.disparitySearchDir== STEREOVISION_TI_LEFT_TO_RIGHT) {
                    pInBufs->bufDesc[idx]->bufPlanes[0].buf= pSysCompositeBufferInput->bufAddr[0][1];
                    }
                else {
                    pInBufs->bufDesc[idx]->bufPlanes[0].buf= pSysCompositeBufferInput->bufAddr[0][0];
                    }
#endif
                idx = STEREOVISION_TI_BUFDESC_IN_DISPARITY;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufInput->bufAddr[0];
                idx = STEREOVISION_TI_BUFDESC_IN_PREV_COST;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufInput->bufAddr[2];
                idx = STEREOVISION_TI_BUFDESC_IN_COST;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufInput->bufAddr[1];
                idx = STEREOVISION_TI_BUFDESC_IN_NEXT_COST;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufInput->bufAddr[3];
                idx = STEREOVISION_TI_BUFDESC_IN_AUX_DISPARITY;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = (uint8_t*)pSysMetaDataBufInput->bufAddr[0] + pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0];

                idx = STEREOVISION_TI_BUFDESC_OUT_DISPARITY;
                pOutBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufOutput->bufAddr[0];
                idx = STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE;
                pOutBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufOutput->bufAddr[1];
                idx = STEREOVISION_TI_BUFDESC_OUT_TEXTURE;
                pOutBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufOutput->bufAddr[2];

                /* for 16-bit disparity output */
                if (pLinkCreateParams->enable16BitsDispOut)
                {
                    idx = STEREOVISION_TI_BUFDESC_OUT_CONFIDENCE;
                    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = pSysMetaDataBuf16BitOutput->bufAddr[0];
                }

                pInArgs  = &pStereoPostProcessObj->inArgs;
                pOutArgs = &pStereoPostProcessObj->outArgs;

                /* If generation of extra right to left disparity map was disabled then set the lrMaxDiffThreshold to 255
                                in order to avoid doing left right check
                                */
                if (pLinkCreateParams->disparityExtraRightLeft== 0) {
                    pInArgs->postProcOptions.lrMaxDiffThreshold= 255;
                }

                status = AlgIvision_process(
                        pStereoPostProcessObj->handle,
                        pInBufs,
                        pOutBufs,
                        (IVISION_InArgs *)pInArgs,
                        (IVISION_OutArgs *)pOutArgs);
                UTILS_assert(status == IALG_EOK);

                Cache_wbInv(
                        pSysMetaDataBufOutput->bufAddr[0],
                        pStereoPostProcessObj->outBufferSize*2,
                        Cache_Type_ALLD,
                        TRUE
                );

                Cache_wbInv(
                        pSysMetaDataBufOutput->bufAddr[1],
                        pStereoPostProcessObj->outBufferSize*2,
                        Cache_Type_ALLD,
                        TRUE
                );

                Cache_wbInv(
                        pSysMetaDataBufOutput->bufAddr[2],
                        pStereoPostProcessObj->outBufferSize*2,
                        Cache_Type_ALLD,
                        TRUE
                );

                // 16-bit disparity output
                if (pLinkCreateParams->enable16BitsDispOut)
                {
                    Cache_wbInv(
                            pSysMetaDataBuf16BitOutput->bufAddr[0],
                            pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0] * 2,
                            Cache_Type_ALLD,
                            TRUE
                	);
            	}

                /*
                AlgorithmLink_StereoPostProcess_medianTemporalFilter(
                        (uint32_t*)pSysMetaDataBufOutput->bufAddr[0],
                        (uint32_t*)pSysMetaDataBufOutput1->bufAddr[0],
                        (uint32_t*)pSysMetaDataBufOutput0->bufAddr[0],
                        (uint32_t*)pSysMetaDataBufMedianOutput->bufAddr[0],
                        pStereoPostProcessObj->imagePitch[0],
                        pStereoPostProcessObj->imageHeight[0]);
                 */
#ifdef _INCLUDE_TEMPORAL_NOISE_FILTER
                AlgorithmLink_StereoPostProcess_temporalFilter(
                        (uint32_t*)pSysMetaDataBufOutput->bufAddr[0],
                        (uint32_t*)pSysMetaDataBufMedianOutput->bufAddr[0],
                        (uint32_t*)pSysMetaDataBufOutput1->bufAddr[0],
                        pStereoPostProcessObj->imagePitch[0],
                        pStereoPostProcessObj->imageHeight[0],
                        pStereoPostProcessObj->temporalFilterNumFrames);
#endif

#if DISPARITY_16BITS
                AlgorithmLink_StereoPostProcess_convertDisparityFalseColorYUV420SP_opt(
                        pSysVideoFrameOutput->bufAddr[0],
                        pSysVideoFrameOutput->bufAddr[1],
                        (uint16_t *)pSysMetaDataBufOutput->bufAddr[0],
                        pStereoPostProcessObj->imagePitch[0],
                        pStereoPostProcessObj->imageHeight[0],
                        pStereoPostProcessObj->algLinkCreateParams.numDisparities,
                        pStereoPostProcessObj->algLinkCreateParams.minDisparityToDisplay,
                        &falseColorLUT_YUV[pStereoPostProcessObj->algLinkCreateParams.colorMapIndex][0],
                        pStereoPostProcessObj->inArgs.postProcOptions.disparityNumFracBits,
                        pStereoPostProcessObj->algLinkCreateParams.useGrayScale);
#else

                AlgorithmLink_StereoPostProcess_convertDisparityFalseColorYUV420SP_opt(
                        pSysVideoFrameOutput->bufAddr[0],
                        pSysVideoFrameOutput->bufAddr[1],
                        pSysMetaDataBufOutput->bufAddr[0],
                        pStereoPostProcessObj->imagePitch[0],
                        pStereoPostProcessObj->imageHeight[0],
                        pStereoPostProcessObj->algLinkCreateParams.numDisparities,
                        pStereoPostProcessObj->algLinkCreateParams.minDisparityToDisplay,
                        &falseColorLUT_YUV[pStereoPostProcessObj->algLinkCreateParams.colorMapIndex][0],
                        pStereoPostProcessObj->algLinkCreateParams.useGrayScale);
#endif

                Cache_wb(
                        pSysVideoFrameOutput->bufAddr[0],
                        pStereoPostProcessObj->imagePitch[0]* pStereoPostProcessObj->imageHeight[0],
                        Cache_Type_ALLD,
                        TRUE
                );

                Cache_wb(
                        pSysVideoFrameOutput->bufAddr[1],
                        pStereoPostProcessObj->imagePitch[1]* pStereoPostProcessObj->imageHeight[1],
                        Cache_Type_ALLD,
                        TRUE
                );

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                        pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                        pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                [channelId].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                [channelId].outBufCount[0]++;

                ////////////////////////////////////////////////////////
                // put Disparity output in the queue, and release it  //
                ////////////////////////////////////////////////////////
                outputQId = ALGLINK_STEREOPP_OPQID_DISPARITY;
                status = AlgorithmLink_putFullOutputBuffer(
                        pObj,
                        outputQId,
                        pSysOutBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(
                        pLinkCreateParams->outQueParams[outputQId].nextLink,
                        SYSTEM_CMD_NEW_DATA,
                        NULL);
                /*
                 * Releasing (Free'ing) output buffers, since algorithm
                 * does not need it for any future usage.
                 */
                outputBufListReturn.numBuf = 1;
                outputBufListReturn.buffers[0] = pSysOutBuffer;

                status = AlgorithmLink_releaseOutputBuffer(
                        pObj,
                        outputQId,
                        &outputBufListReturn
                );
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


                ////////////////////////////////////////////////////////////
                // put 16 bit disparity output in the queue, and release it //
                ////////////////////////////////////////////////////////////
                if (pLinkCreateParams->enable16BitsDispOut)
                {
                    outputQId = ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY;
                    status = AlgorithmLink_putFullOutputBuffer(
                            pObj,
                            outputQId,
                            pSysOutBuffer16BitDisparity);
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                    /*
                     * Informing next link that a new data has peen put for its
                     * processing
                     */
                    System_sendLinkCmd(
                            pLinkCreateParams->outQueParams[outputQId].nextLink,
                            SYSTEM_CMD_NEW_DATA,
                            NULL);
                    /*
                     * Releasing (Free'ing) output buffers, since algorithm
                     * does not need it for any future usage.
                     */
                    outputBufListReturn.numBuf = 1;
                    outputBufListReturn.buffers[0] = pSysOutBuffer16BitDisparity;

                    status = AlgorithmLink_releaseOutputBuffer(
                            pObj,
                            outputQId,
                            &outputBufListReturn
                    );
                    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
                }

            }

            inputQId                        = 0;
            status = AlgorithmLink_releaseInputBuffer(
                    pObj,
                    inputQId,
                    pLinkCreateParams->inQueParams.prevLinkId,
                    pLinkCreateParams->inQueParams.prevLinkQueId,
                    &inputBufListReturn,
                    bufDropFlag);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

        if(isProcessCallDoneFlag == FALSE)
            break;
        else
        	break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for disparity algo
 *
 * \param  pObj                  [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcessControl(void * pObj,
        void * pControlParams)
{
    AlgorithmLink_StereoPostProcessControlParams *pStereoCtlParams;
    Int32                               status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_StereoPostProcessObj             * pStereoPostProcessObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    pStereoPostProcessObj = (AlgorithmLink_StereoPostProcessObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)pControlParams;

    /*
     * There can be other commands to alter the properties of the alg link
     * or properties of the core algorithm.
     * In this simple example, there is just a control command to print
     * statistics and a default call to algorithm control.
     */

    switch(pAlgLinkControlPrm->controlCmd)
    {

    case SYSTEM_CMD_PRINT_STATISTICS:
        AlgorithmLink_StereoPostProcessPrintStatistics(pObj,
                pStereoPostProcessObj
        );
        break;

    case STEREO_POSTPROCESS_LINK_CMD_SET_DYNAMIC_PARAMS:
        pStereoCtlParams = (AlgorithmLink_StereoPostProcessControlParams *)
                                    pControlParams;
        status= AlgorithmLink_StereoPostProcessUpdateParams(pStereoPostProcessObj, pStereoCtlParams);
        break;

    default:
        //No other control call implemented in this link
        UTILS_assert(NULL);
        break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for disparity algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_StereoPostProcessStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for disparity algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcessDelete(void * pObj)
{
    UInt32                                  status;
    UInt32                                  bufId, idx;
    UInt32                                  bufferSize, numPlanes;

    AlgorithmLink_StereoPostProcessObj                 * pStereoPostProcessObj;
    AlgorithmLink_StereoPostProcessCreateParams        * pLinkCreateParams;
    System_VideoFrameBuffer                            * pSysVideoFrameOutput;
    System_MetaDataBuffer                              * pSystemMetaDataBuffer;

    pStereoPostProcessObj = (AlgorithmLink_StereoPostProcessObj *)
                                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pStereoPostProcessObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pStereoPostProcessObj->linkStatsInfo);
    UTILS_assert(status == 0);

    status = AlgIvision_delete(pStereoPostProcessObj->handle);
    UTILS_assert(status == 0);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSysVideoFrameOutput = &pStereoPostProcessObj->videoFrames[bufId];

        numPlanes=2;
        for(idx = 0; idx <numPlanes; idx++)
        {
            bufferSize = pStereoPostProcessObj->imageHeight[idx] *
                    pStereoPostProcessObj->imagePitch[idx];

            status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pSysVideoFrameOutput->bufAddr[idx],
                    bufferSize
            );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

    }

    // for 16-bit disparity output
    if (pLinkCreateParams->enable16BitsDispOut)
    {
        for (bufId = 0; bufId < pLinkCreateParams->num16BitDispOutBuffers; bufId++)
        {
            pSystemMetaDataBuffer = &pStereoPostProcessObj->disparity16bit[bufId];

            bufferSize = pStereoPostProcessObj->imageHeight[0] *
                    pStereoPostProcessObj->imagePitch[0] * 2;  // 2 bytes
            status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pSystemMetaDataBuffer->bufAddr[0],
                    bufferSize
            );

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    numPlanes = 3;
    for(idx = 0; idx <numPlanes; idx++)
    {
        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pStereoPostProcessObj->postProcOutput[0].bufAddr[idx],
                pStereoPostProcessObj->outBufferSize*2
        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pStereoPostProcessObj->postProcOutput[1].bufAddr[0],
            pStereoPostProcessObj->outBufferSize*2
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pStereoPostProcessObj->postProcOutput[2].bufAddr[0],
            pStereoPostProcessObj->outBufferSize*2
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pStereoPostProcessObj->postProcOutput[3].bufAddr[0],
            pStereoPostProcessObj->outBufferSize*2
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for(idx = 0; idx < PPROC_LINK_MAX_NUM_INPUT_CHANNELS; idx++)
    {
        status = Utils_queDelete(&(pStereoPostProcessObj->localInputQ[idx].queHandle));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_LOCAL,
            pStereoPostProcessObj,
            sizeof(AlgorithmLink_StereoPostProcessObj)
    );
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pEdgeDetectionObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcessPrintStatistics(void *pObj,
        AlgorithmLink_StereoPostProcessObj *pStereoPostProcessObj)
{
    UTILS_assert(NULL != pStereoPostProcessObj->linkStatsInfo);

    Utils_printLinkStatistics(&pStereoPostProcessObj->linkStatsInfo->linkStats,
            "ALG_STEREO_POST_PROCESS",
            TRUE);

    Utils_printLatency("ALG_STEREO_POST_PROCESS",
            &pStereoPostProcessObj->linkStatsInfo->linkLatency,
            &pStereoPostProcessObj->linkStatsInfo->srcToLinkLatency,
            TRUE
    );

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Update parmeters dynamically
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pEdgeDetectionObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_StereoPostProcessUpdateParams(AlgorithmLink_StereoPostProcessObj *pObj, AlgorithmLink_StereoPostProcessControlParams *pStereoCtlParams) {
    STEREOVISION_TI_InArgs              *pInArgs;

    pInArgs=&pObj->inArgs;
    pInArgs->postProcOptions.textureLumaHiThresh= pStereoCtlParams->stereoParams.postproc_texture_lumahithresh;
    pInArgs->postProcOptions.textureLumaLoThresh= pStereoCtlParams->stereoParams.postproc_texture_lumalothresh;
    pInArgs->postProcOptions.costMaxThreshold= pStereoCtlParams->stereoParams.postproc_cost_max_threshold;
    pInArgs->postProcOptions.minConfidenceThreshold= pStereoCtlParams->stereoParams.postproc_conf_min_thrseshold;
    pInArgs->postProcOptions.textureThreshold= pStereoCtlParams->stereoParams.postproc_texture_threshold;
    pInArgs->postProcOptions.lrMaxDiffThreshold= pStereoCtlParams->stereoParams.postproc_lrmaxdiff_threshold;
    pInArgs->postProcOptions.maxDispDissimilarity= pStereoCtlParams->stereoParams.postproc_maxdisp_dissimilarity;
    pInArgs->postProcOptions.minConfidentNSegment= pStereoCtlParams->stereoParams.postproc_minconf_nseg_threshold;
    return SYSTEM_LINK_STATUS_SOK;
}


