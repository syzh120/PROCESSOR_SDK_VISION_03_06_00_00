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
 * \file disparityHamDistLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Disparity Haming Distance
 *         algorithm Link
 *
 * \version 0.1 (Sept 2014) : [SR] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "disparityHamDistLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/* Remove for subsequent version of EVE SW */
#define _EVE_SW_1_08

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plug-ins of disparityHamDist algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_disparityHamDist_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
            AlgorithmLink_disparityHamDistCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
            AlgorithmLink_disparityHamDistProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
            AlgorithmLink_disparityHamDistControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
            AlgorithmLink_disparityHamDistStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
            AlgorithmLink_disparityHamDistDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_DISPARITY_HAMDIST;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}
/**
 *******************************************************************************
 *
 * \brief disparityHamDist Alg uses the IVISION standard to interact with the
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
UInt32 AlgorithmLink_disparityHamDistInitIOBuffers
( AlgorithmLink_DisparityHamDistObj *pObj,
        AlgorithmLink_DisparityHamDistCreateParams * pLinkCreateParams)
{
    UInt32              idx;
    UInt32              numBytesPerDisparityHamDist;

    IVISION_InBufs      * pInBufs;
    IVISION_OutBufs     * pOutBufs;

    pInBufs         = &pObj->inBufs;
    pInBufs->size   = sizeof(IVISION_InBufs);
    pInBufs->numBufs    = DISPARITY_TI_BUFDESC_IN_TOTAL;
    pInBufs->bufDesc = pObj->inBufDescList;
    for(idx = 0 ; idx < DISPARITY_TI_BUFDESC_IN_TOTAL ;idx++)
    {
        pObj->inBufDescList[idx] = &pObj->inBufDesc[idx];
    }

    pOutBufs        = &pObj->outBufs;
    pOutBufs->size  = sizeof(IVISION_OutBufs);
    pOutBufs->numBufs   = DISPARITY_TI_BUFDESC_OUT_TOTAL;
    pOutBufs->bufDesc= pObj->outBufDescList;
    for(idx = 0 ; idx < DISPARITY_TI_BUFDESC_OUT_TOTAL ;idx++)
    {
        pObj->outBufDescList[idx] = &pObj->outBufDesc[idx];
    }

    idx = DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE;
    pInBufs->bufDesc[idx]->numPlanes = 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x
    = pLinkCreateParams->inputRightImageStartX;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y
    = pLinkCreateParams->inputRightImageStartY;
    pInBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->srcImageWidth); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->srcImageHeight); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE;
    pInBufs->bufDesc[idx]->numPlanes = 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x
    = pLinkCreateParams->inputLeftImageStartX;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y
    = pLinkCreateParams->inputLeftImageStartY;
    pInBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->srcImageWidth);//VC
    pInBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->srcImageHeight); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pInBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_DISPARITY_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth);  // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_COST_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_PREV_ADJ_COST_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_NEXT_ADJ_COST_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    numBytesPerDisparityHamDist= 1;

    pObj->outBufferSize = (numBytesPerDisparityHamDist
            *pLinkCreateParams->imageRoiWidth*pLinkCreateParams->imageRoiHeight);

    return SYSTEM_LINK_STATUS_SOK;

}

UInt32 AlgorithmLink_rlDisparityHamDistInitIOBuffers
( AlgorithmLink_DisparityHamDistObj *pObj,
        AlgorithmLink_DisparityHamDistCreateParams * pLinkCreateParams)
{
    UInt32              idx;
    UInt32              numBytesPerDisparityHamDist;

    IVISION_InBufs      * pInBufs;
    IVISION_OutBufs     * pOutBufs;

    pInBufs         = &pObj->rlInBufs;
    pInBufs->size   = sizeof(IVISION_InBufs);
    pInBufs->numBufs    = DISPARITY_TI_BUFDESC_IN_TOTAL;
    pInBufs->bufDesc = pObj->rlInBufDescList;
    for(idx = 0 ; idx < DISPARITY_TI_BUFDESC_IN_TOTAL ;idx++)
    {
        pObj->rlInBufDescList[idx] = &pObj->rlInBufDesc[idx];
    }

    pOutBufs        = &pObj->rlOutBufs;
    pOutBufs->size  = sizeof(IVISION_OutBufs);
    pOutBufs->numBufs   = DISPARITY_TI_BUFDESC_OUT_TOTAL;
    pOutBufs->bufDesc= pObj->rlOutBufDescList;
    for(idx = 0 ; idx < DISPARITY_TI_BUFDESC_OUT_TOTAL ;idx++)
    {
        pObj->rlOutBufDescList[idx] = &pObj->rlOutBufDesc[idx];
    }

    idx = DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE;
    pInBufs->bufDesc[idx]->numPlanes = 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x
    = (pLinkCreateParams->winWidth - 1)/2;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y
    = pLinkCreateParams->winHeight/4; /* RL disparity will use a cost window of winWidth x (winHeight/2) */
    pInBufs->bufDesc[idx]->bufPlanes[0].width
    = (2*pLinkCreateParams->srcImageWidth); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->srcImageHeight/2); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight/2); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE;
    pInBufs->bufDesc[idx]->numPlanes = 1;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x
    = (pLinkCreateParams->winWidth - 1)/2;
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y
    = pLinkCreateParams->winHeight/4;
    pInBufs->bufDesc[idx]->bufPlanes[0].width
    = (2*pLinkCreateParams->srcImageWidth);//VC
    pInBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->srcImageHeight/2); //VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pInBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight/2); // VC
    pInBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pInBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_DISPARITY_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->imageRoiHeight/2); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth);  // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight/2); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    idx = DISPARITY_TI_BUFDESC_COST_OUT;
    pOutBufs->bufDesc[idx]->numPlanes = 1;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].height
    = (pLinkCreateParams->imageRoiHeight/2); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.width
    = (pLinkCreateParams->imageRoiWidth); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].frameROI.height
    = (pLinkCreateParams->imageRoiHeight/2); // VC
    pOutBufs->bufDesc[idx]->bufPlanes[0].planeType = 0;
    pOutBufs->bufDesc[idx]->bufPlanes[0].buf = NULL;

    numBytesPerDisparityHamDist= 1;

    pObj->rlOutBufferSize = (numBytesPerDisparityHamDist
            *pLinkCreateParams->imageRoiWidth*(pLinkCreateParams->imageRoiHeight/2));

    return SYSTEM_LINK_STATUS_SOK;

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
Int32 AlgorithmLink_disparityHamDistCreate(void *pObj,void *pCreateParams)
{
    UInt32                                      status = SYSTEM_LINK_STATUS_SOK;
    UInt32                                      bufferSize;
    UInt32                                      prevLinkQueId;
    UInt32                                      bufId;
    UInt32                                      numInputQUsed;
    UInt32                                      numOutputQUsed;
    UInt32                                      outputQId;
    UInt32                                      idx;
    UInt32                                      outputChId;
    System_LinkInfo                             prevLinkInfo;
    System_LinkChInfo                           * pOutChInfo, * pPrevChInfo;
    AlgorithmLink_InputQueueInfo                * pInputQInfo;
    AlgorithmLink_OutputQueueInfo               * pOutputQInfo;
    DISPARITY_TI_CreateParams           * pAlgCreateParams;
    AlgorithmLink_DisparityHamDistCreateParams  * pLinkCreateParams;
    AlgorithmLink_DisparityHamDistObj           * pDisparityHamDistObj;
    System_MetaDataBuffer                       * pSysMetaDataBufferOutput;
    System_Buffer                               * pSystemBuffer;
    IVISION_InArgs                              * inArgs;
    DISPARITY_TI_outArgs                * outArgs;


    pLinkCreateParams = (AlgorithmLink_DisparityHamDistCreateParams *)
                                 pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pDisparityHamDistObj = (AlgorithmLink_DisparityHamDistObj *)
                            Utils_memAlloc(
                                    UTILS_HEAPID_DDR_CACHED_LOCAL,
                                    sizeof(AlgorithmLink_DisparityHamDistObj),
                                    32);
    UTILS_assert(pDisparityHamDistObj != NULL);
    AlgorithmLink_setAlgorithmParamsObj(pObj, pDisparityHamDistObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pDisparityHamDistObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_DisparityHamDistCreateParams)
    );

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */
    pAlgCreateParams  = &pDisparityHamDistObj->algCreateParams;
    pAlgCreateParams->visionParams.algParams.size = sizeof(*pAlgCreateParams);
    pAlgCreateParams->visionParams.cacheWriteBack = NULL;
    pAlgCreateParams->imgFrameWidth     = pLinkCreateParams->imageRoiWidth; // VC`
    pAlgCreateParams->imgFrameHeight    = pLinkCreateParams->imageRoiHeight; //VC
    pAlgCreateParams->inputBitDepth     = pLinkCreateParams->inputBitDepth;
    pAlgCreateParams->winWidth          = pLinkCreateParams->winWidth;
    pAlgCreateParams->winHeight         = pLinkCreateParams->winHeight;
    pAlgCreateParams->numDisparities    = pLinkCreateParams->numDisparities;
    pAlgCreateParams->disparityStep     = pLinkCreateParams->disparityStep;
    pAlgCreateParams->costMethod        = DISPARITY_TI_HAM_DIST;
    pAlgCreateParams->searchDir         = pLinkCreateParams->searchDir;
    pAlgCreateParams->outputCostType    = DISPARITY_TI_MIN_ADJACENT_COSTS;

    pDisparityHamDistObj->handle = AlgIvision_create(&DISPARITY_TI_VISION_FXNS, (IALG_Params *)(pAlgCreateParams));
    UTILS_assert(pDisparityHamDistObj->handle!=NULL);

    /* Create second instance of disparity applet, to produce Right to left disparity map from a vertically downsampled version
    of the original input frame and also with a higher disparity step, twice from the one used for Left to Right disparity map*/
    pAlgCreateParams  = &pDisparityHamDistObj->rlAlgCreateParams;
    pAlgCreateParams->visionParams.algParams.size = sizeof(*pAlgCreateParams);
    pAlgCreateParams->visionParams.cacheWriteBack = NULL;
    pAlgCreateParams->imgFrameWidth     = pLinkCreateParams->imageRoiWidth;
    pAlgCreateParams->imgFrameHeight    = pLinkCreateParams->imageRoiHeight/2;
    pAlgCreateParams->inputBitDepth     = pLinkCreateParams->inputBitDepth;
    pAlgCreateParams->winWidth          = pLinkCreateParams->winWidth;
    pAlgCreateParams->winHeight         = pLinkCreateParams->winHeight/2 + 1;
    pAlgCreateParams->numDisparities    = pLinkCreateParams->numDisparities;
    pAlgCreateParams->disparityStep     = pLinkCreateParams->disparityStep*2;
    pAlgCreateParams->costMethod        = DISPARITY_TI_HAM_DIST;
    pAlgCreateParams->searchDir         = ((pLinkCreateParams->searchDir== DISPARITY_TI_LEFT_TO_RIGHT) ?  DISPARITY_TI_RIGHT_TO_LEFT : DISPARITY_TI_LEFT_TO_RIGHT);
#ifdef _EVE_SW_1_08 // The below line is to ensure compatibility with EVE sw 1.08. Will disable it once EVE sw 1.09 is available
    pAlgCreateParams->outputCostType    = DISPARITY_TI_MINCOST;
#else
    pAlgCreateParams->outputCostType    = DISPARITY_TI_NOCOST;
#endif
    pDisparityHamDistObj->rlHandle = AlgIvision_create(&DISPARITY_TI_VISION_FXNS, (IALG_Params *)(pAlgCreateParams));
    UTILS_assert(pDisparityHamDistObj->rlHandle!=NULL);

    /*
     * Populating parameters corresponding to Q usage of disparityHamDist
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = 1;
    pInputQInfo       = &pDisparityHamDistObj->inputQInfo;
    pOutputQInfo      = &pDisparityHamDistObj->outputQInfo;
    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    outputQId                   = 0;
    outputChId                  = 0;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In disparityHamDist Link, only data format changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(
            pLinkCreateParams->inQueParams.prevLinkId,
            &prevLinkInfo
    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= numInputQUsed);

    prevLinkQueId = pLinkCreateParams->inQueParams.prevLinkQueId;
    pDisparityHamDistObj->numInputChannels
    = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    /* Disparity Alg link will only output 1 channel for the disparity output */
    pOutputQInfo->queInfo.numCh = 1;

    /*
     * Initialize input output buffers
     */
    AlgorithmLink_disparityHamDistInitIOBuffers(pDisparityHamDistObj,
            pLinkCreateParams);

    AlgorithmLink_rlDisparityHamDistInitIOBuffers(pDisparityHamDistObj,
            pLinkCreateParams);

    /*
     * Channel Info Population
     */
    pOutChInfo      = &(pOutputQInfo->queInfo.chInfo[outputChId]);
    pPrevChInfo = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[outputChId]);
    pOutChInfo->startX = 0;
    pOutChInfo->startY = 0;
    pOutChInfo->width  = pLinkCreateParams->imageRoiWidth;
    pOutChInfo->height = pLinkCreateParams->imageRoiHeight;
    pOutChInfo->flags = pPrevChInfo->flags;
    pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pOutChInfo->flags,
            SYSTEM_BUFFER_TYPE_METADATA);

    pOutChInfo->pitch[0] = pLinkCreateParams->imageRoiWidth;
    pOutChInfo->pitch[1] = pLinkCreateParams->imageRoiWidth;
    pOutChInfo->pitch[2] = 0;

    /*
     * Taking a copy of input channel info in the link object for any future
     * use
     */
    for(idx =0 ; idx < pDisparityHamDistObj->numInputChannels; idx++)
    {

        memcpy((void *)&(pDisparityHamDistObj->inputChInfo[idx]),
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
    //<TODO : Yet to be given from the alg team >

    bufferSize = pDisparityHamDistObj->outBufferSize;
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer =   &pDisparityHamDistObj->buffers[bufId];
        pSysMetaDataBufferOutput
        = &pDisparityHamDistObj->disparityHamDistOpBuffers[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pSysMetaDataBufferOutput;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =   0;

        pSysMetaDataBufferOutput->numMetaDataPlanes = 4;
        pSysMetaDataBufferOutput->metaBufSize[0] = bufferSize;
        pSysMetaDataBufferOutput->metaFillLength[0] = bufferSize;
        pSysMetaDataBufferOutput->bufAddr[0]    =   Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                bufferSize + bufferSize/2,
                ALGORITHMLINK_FRAME_ALIGN
        );
        UTILS_assert(pSysMetaDataBufferOutput->bufAddr[0] != NULL);

        pSysMetaDataBufferOutput->metaBufSize[1] = bufferSize*2;
        pSysMetaDataBufferOutput->metaFillLength[1] = bufferSize*2;
        pSysMetaDataBufferOutput->bufAddr[1]    =   Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
#ifdef _EVE_SW_1_08
bufferSize*4,
#else
    bufferSize*2,
#endif
ALGORITHMLINK_FRAME_ALIGN
        );
        UTILS_assert(pSysMetaDataBufferOutput->bufAddr[1] != NULL);

        pSysMetaDataBufferOutput->metaBufSize[2] = bufferSize*2;
        pSysMetaDataBufferOutput->metaFillLength[2] = bufferSize*2;
        pSysMetaDataBufferOutput->bufAddr[2]    =   Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                bufferSize*2,
                ALGORITHMLINK_FRAME_ALIGN
        );
        UTILS_assert(pSysMetaDataBufferOutput->bufAddr[2] != NULL);

        pSysMetaDataBufferOutput->metaBufSize[3] = bufferSize*2;
        pSysMetaDataBufferOutput->metaFillLength[3] = bufferSize*2;
        pSysMetaDataBufferOutput->bufAddr[3]    =   Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                bufferSize*2,
                ALGORITHMLINK_FRAME_ALIGN
        );
        UTILS_assert(pSysMetaDataBufferOutput->bufAddr[3] != NULL);


        /* Set to 0 when used as meta data buffer */
        pSysMetaDataBufferOutput->flags = 0;

        status = AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    inArgs  = &pDisparityHamDistObj->inArgs;
    outArgs = &pDisparityHamDistObj->outArgs;

    inArgs->subFrameInfo = 0;
    inArgs->size = sizeof(IVISION_InArgs);

    outArgs->iVisionOutArgs.size = sizeof(DISPARITY_TI_outArgs);

    pDisparityHamDistObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_DISPARITY");
    UTILS_assert(NULL != pDisparityHamDistObj->linkStatsInfo);

    pDisparityHamDistObj->isFirstFrameRecv    = FALSE;

    return status;
}
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
Int32 AlgorithmLink_disparityHamDistProcess(void * pObj)
{
    UInt32              idx;
    UInt32                                  status = SYSTEM_LINK_STATUS_SOK;
    UInt32                                  bufId;
    UInt32                                  inputQId;
    UInt32                                  outputQId, channelId;
    Bool                                    bufDropFlag;
    AlgorithmLink_DisparityHamDistObj                 * pDisparityHamDistObj;
    AlgorithmLink_DisparityHamDistCreateParams        * pLinkCreateParams;
    System_Buffer                                     * pSysOutBuffer;
    System_Buffer                                     * pSysInBuffer;
    System_BufferList                                 inputBufList;
    System_BufferList                                 outputBufListReturn;
    System_BufferList                                 inputBufListReturn;
    System_VideoFrameCompositeBuffer *pCompositeBuffer;
    IVISION_InBufs                      *pInBufs;
    IVISION_OutBufs                     *pOutBufs;
    IVISION_InBufs                      *pRlInBufs;
    IVISION_OutBufs                     *pRlOutBufs;
    System_MetaDataBuffer *pSysMetaDataBufferOutput;
    IVISION_InArgs                          * pInArgs;
    DISPARITY_TI_outArgs            * pOutArgs;
    System_LinkStatistics      * linkStatsInfo;

    pDisparityHamDistObj = (AlgorithmLink_DisparityHamDistObj *)
                                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    linkStatsInfo = pDisparityHamDistObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);


    pLinkCreateParams = &pDisparityHamDistObj->algLinkCreateParams;

    pInBufs  = &pDisparityHamDistObj->inBufs;
    pOutBufs = &pDisparityHamDistObj->outBufs;

    pRlInBufs  = &pDisparityHamDistObj->rlInBufs;
    pRlOutBufs = &pDisparityHamDistObj->rlOutBufs;

    System_getLinksFullBuffers(
            pLinkCreateParams->inQueParams.prevLinkId,
            pLinkCreateParams->inQueParams.prevLinkQueId,
            &inputBufList);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    if (inputBufList.numBuf)
    {
        if (pDisparityHamDistObj->isFirstFrameRecv == FALSE)
        {
            pDisparityHamDistObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(&linkStatsInfo->linkStats,
                        pDisparityHamDistObj->numInputChannels, 1);
            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];
            if(pSysInBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            channelId = pSysInBuffer->chNum;
            if(channelId < pDisparityHamDistObj->numInputChannels)
            {
                linkStatsInfo->linkStats.chStats[channelId]
                                                        .inBufRecvCount++;
            }

            /*
             * Getting free (empty) buffers from pool of output buffers
             */
            outputQId        = 0;
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
                /*
                 * Get video frame buffer out of the system Buffer for both
                 * input and output buffers.
                 * Associate the input/output buffer pointers with inBufs
                 * and outBufs
                 * Record the bufferId with the address of the System Buffer
                 */
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp
                = Utils_getCurGlobalTimeInUsec();

                pSysMetaDataBufferOutput
                = (System_MetaDataBuffer *)pSysOutBuffer->payload;

                pCompositeBuffer = (System_VideoFrameCompositeBuffer *)
                                        pSysInBuffer->payload;

                idx = DISPARITY_TI_BUFDESC_IN_RIGHT_IMAGE;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pCompositeBuffer->bufAddr[0][0];
                pRlInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pCompositeBuffer->bufAddr[0][0];
                idx = DISPARITY_TI_BUFDESC_IN_LEFT_IMAGE;
                pInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pCompositeBuffer->bufAddr[0][1];
                pRlInBufs->bufDesc[idx]->bufPlanes[0].buf
                = pCompositeBuffer->bufAddr[0][1];

                idx = DISPARITY_TI_BUFDESC_DISPARITY_OUT;
                pOutBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufferOutput->bufAddr[0];
                pRlOutBufs->bufDesc[idx]->bufPlanes[0].buf
                = (uint8_t*)pSysMetaDataBufferOutput->bufAddr[0] + pDisparityHamDistObj->outBufferSize;

                idx = DISPARITY_TI_BUFDESC_COST_OUT;
                pOutBufs->bufDesc[idx]->bufPlanes[0].buf
                = pSysMetaDataBufferOutput->bufAddr[1];
#ifdef _EVE_SW_1_08 // The below line is to ensure compatibility with EVE sw 1.08. Will disable it once EVE sw 1.09 is available

pRlOutBufs->bufDesc[idx]->bufPlanes[0].buf
= (uint8_t*)pSysMetaDataBufferOutput->bufAddr[0] + 2*pDisparityHamDistObj->outBufferSize;

#endif

idx = DISPARITY_TI_BUFDESC_PREV_ADJ_COST_OUT;
pOutBufs->bufDesc[idx]->bufPlanes[0].buf
= pSysMetaDataBufferOutput->bufAddr[2];

idx = DISPARITY_TI_BUFDESC_NEXT_ADJ_COST_OUT;
pOutBufs->bufDesc[idx]->bufPlanes[0].buf
= pSysMetaDataBufferOutput->bufAddr[3];

pInArgs  = &pDisparityHamDistObj->inArgs;
pOutArgs = &pDisparityHamDistObj->outArgs;
status = AlgIvision_process(
        pDisparityHamDistObj->handle,
        pInBufs,
        pOutBufs,
        (IVISION_InArgs *)pInArgs,
        (IVISION_OutArgs *)pOutArgs);
UTILS_assert(status == IALG_EOK);

if (pLinkCreateParams->extraRightLeftMap) {
    status = AlgIvision_process(
            pDisparityHamDistObj->rlHandle,
            pRlInBufs,
            pRlOutBufs,
            (IVISION_InArgs *)pInArgs,
            (IVISION_OutArgs *)pOutArgs);
    UTILS_assert(status == IALG_EOK);
}

Utils_updateLatency(&linkStatsInfo->linkLatency,
        pSysOutBuffer->linkLocalTimestamp);
Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
        pSysOutBuffer->srcTimestamp);

linkStatsInfo->linkStats.chStats
[channelId].inBufProcessCount++;
linkStatsInfo->linkStats.chStats
[channelId].outBufCount[0]++;

/*
 * <TODO For Now not handling locking of output buffers
 *  case >
 */
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
         pLinkCreateParams->outQueParams.nextLink,
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
            }

            inputQId                        = 0;
            inputBufListReturn.numBuf       = 1;
            inputBufListReturn.buffers[0]   = pSysInBuffer;
            bufDropFlag = FALSE;
            status = AlgorithmLink_releaseInputBuffer(
                    pObj,
                    inputQId,
                    pLinkCreateParams->inQueParams.prevLinkId,
                    pLinkCreateParams->inQueParams.prevLinkQueId,
                    &inputBufListReturn,
                    &bufDropFlag);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
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
Int32 AlgorithmLink_disparityHamDistControl(void * pObj,
        void * pControlParams)
{
    Int32                               status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_DisparityHamDistObj             * pDisparityHamDistObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    pDisparityHamDistObj = (AlgorithmLink_DisparityHamDistObj *)
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
        AlgorithmLink_disparityHamDistPrintStatistics(pObj,
                pDisparityHamDistObj
        );
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

Int32 AlgorithmLink_disparityHamDistStop(void * pObj)
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
Int32 AlgorithmLink_disparityHamDistDelete(void * pObj)
{
    UInt32                                  status;
    UInt32                                  bufId;
    UInt32                                  bufferSize;

    AlgorithmLink_DisparityHamDistObj                 * pDisparityHamDistObj;
    AlgorithmLink_DisparityHamDistCreateParams        * pLinkCreateParams;
    System_MetaDataBuffer                           * pSysMetaDataBuffer;

    pDisparityHamDistObj = (AlgorithmLink_DisparityHamDistObj *)
                                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pDisparityHamDistObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pDisparityHamDistObj->linkStatsInfo);
    UTILS_assert(status == 0);


    status = AlgIvision_delete(pDisparityHamDistObj->handle);
    UTILS_assert(status == 0);

    status = AlgIvision_delete(pDisparityHamDistObj->rlHandle);
    UTILS_assert(status == 0);

    /*
     * Free link buffers
     */
    bufferSize = pDisparityHamDistObj->outBufferSize;
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSysMetaDataBuffer
        = &pDisparityHamDistObj->disparityHamDistOpBuffers[bufId];

        /*
         * Free'ing up of allocated buffers
         */
        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pSysMetaDataBuffer->bufAddr[0],
                bufferSize
        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pSysMetaDataBuffer->bufAddr[1],
                bufferSize*2
        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pSysMetaDataBuffer->bufAddr[2],
                bufferSize*2
        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pSysMetaDataBuffer->bufAddr[3],
                bufferSize*2
        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_LOCAL,
            pDisparityHamDistObj,
            sizeof(AlgorithmLink_DisparityHamDistObj)
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
Int32 AlgorithmLink_disparityHamDistPrintStatistics(void *pObj,
        AlgorithmLink_DisparityHamDistObj *pDisparityHamDistObj)
{
    UTILS_assert(NULL != pDisparityHamDistObj->linkStatsInfo);

    Utils_printLinkStatistics(&pDisparityHamDistObj->linkStatsInfo->linkStats,
                            "ALG_DISPARITY_HAMDIST",
                            TRUE);

    Utils_printLatency("ALG_DISPARITY_HAMDIST",
            &pDisparityHamDistObj->linkStatsInfo->linkLatency,
            &pDisparityHamDistObj->linkStatsInfo->srcToLinkLatency,
            TRUE
    );

    return SYSTEM_LINK_STATUS_SOK;
}

