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
 * \file fcwLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for algorithm plugin
 *         Link
 *
 * \version 0.0 (Feb 2014) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "fcwLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <math.h>

/* uncomment below to disable calling of alg process API - used for debug ONLY */
//#define ALG_DISABLE

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of gAlign algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_fcw_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_fcwCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_fcwProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_fcwControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_fcwStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_fcwDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_FCW;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Alg uses the IVISION standard to interact with the
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
Int32 AlgorithmLink_gpeAlgParamsInit (
                                  AlgorithmLink_FcwObj *pObj,
                                  System_LinkChInfo *inChInfo
                                )
{
    pObj->algGpeInBufs.size    = sizeof(pObj->algGpeInBufs);
    pObj->algGpeInBufs.numBufs = GPE_TI_IN_BUFDESC_TOTAL;
    pObj->algGpeInBufs.bufDesc = pObj->algGpeInBufDesc;

    pObj->algGpeInBufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]     = &pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE];
    pObj->algGpeInBufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE] = &pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE];

    pObj->algGpeOutBufs.size    = sizeof(pObj->algGpeOutBufs);
    pObj->algGpeOutBufs.numBufs = 1;
    pObj->algGpeOutBufs.bufDesc = pObj->algGpeOutBufDesc;

    pObj->algGpeOutBufDesc[0]   = &pObj->algGpeOutBufDescGpeObjs;

    memset(&pObj->algGpeInArgs, 0, sizeof(pObj->algGpeInArgs));
    pObj->algGpeInArgs.iVisionInArgs.size         = sizeof(pObj->algGpeInArgs);
    pObj->algGpeInArgs.iVisionInArgs.subFrameInfo = 0;

    pObj->algGpeCreateParams.visionParams.algParams.size = sizeof(pObj->algGpeCreateParams);
    pObj->algGpeCreateParams.visionParams.cacheWriteBack = NULL;


    pObj->algGpeCreateParams.maxNumPointCloud   = SFM_LINK_MAX_TRACK_POINTS;
    pObj->algGpeCreateParams.maxNumObjects      = GPE_TI_MAX_INPUT_OBJECTS;
    pObj->algGpeCreateParams.rsvd1              = 0;
    pObj->algGpeCreateParams.rsvd2              = 0;

    pObj->algGpeInArgs.fps                             = pObj->algLinkCreateParams.frameRate;
    pObj->algGpeInArgs.imgWidth                        = pObj->algLinkCreateParams.imageWidth;
    pObj->algGpeInArgs.imgHeight                       = pObj->algLinkCreateParams.imageHeight;
    pObj->algGpeInArgs.gpeParams.cameraHeight          = pObj->algLinkCreateParams.camHeightInMeter;
    pObj->algGpeInArgs.gpeParams.fracWidthTrpzd        = 0.33;
    pObj->algGpeInArgs.gpeParams.fracHeightTrpzd       = 0.33;


    pObj->algGpeInArgs.reserved1                       = 0    ;
    pObj->algGpeInArgs.reserved2                       = 0    ;
    pObj->algGpeInArgs.gpeParams.cameraHeight          = 1.4  ;
    pObj->algGpeInArgs.gpeParams.ptOnPlaneDistTh       = 50.0 ;
    pObj->algGpeInArgs.gpeParams.maxCostTh             = 100 ;
    pObj->algGpeInArgs.gpeParams.trpzdImpFac           = 2.0  ;
    pObj->algGpeInArgs.gpeParams.baseRoll              = 0    ;
    pObj->algGpeInArgs.gpeParams.deltaRoll             = 0.5  ;
    pObj->algGpeInArgs.gpeParams.basePitch             = 0    ;
    pObj->algGpeInArgs.gpeParams.deltaPitch            = 0.5  ;
    pObj->algGpeInArgs.gpeParams.pointsOnlyInTrpzd     = 0    ;
    pObj->algGpeInArgs.gpeParams.noMovingObjectPtCloud = 1    ;
    pObj->algGpeInArgs.gpeParams.startY                = 0    ;
    pObj->algGpeInArgs.gpeParams.minPtsForRansac       = 16   ;
    pObj->algGpeInArgs.gpeParams.numRansacIteration    = 3001 ;

    memset(&pObj->algGpeOutArgs, 0, sizeof(pObj->algGpeOutArgs));
    pObj->algGpeOutArgs.iVisionOutArgs.size         = sizeof(pObj->algGpeOutArgs);

    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].buf                 = NULL;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].width               = sizeof(GPE_TI_OD_input);
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].height              = 1;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].frameROI.width      = sizeof(GPE_TI_OD_input);
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].frameROI.height     = 1;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].planeType           = 0;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].formatType                       = 0; /* NOT USED */
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufferId                         = 0xFF; /* NOT USED */

    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].buf                 = NULL;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].width               = pObj->algGpeCreateParams.maxNumPointCloud * sizeof(GPE_TI_pCloudDesc);
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].height              = 1;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].frameROI.width      = pObj->algGpeCreateParams.maxNumPointCloud * sizeof(GPE_TI_pCloudDesc);
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].frameROI.height     = 1;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].planeType           = 0;
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].formatType                       = 0; /* NOT USED */
    pObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufferId                         = 0xFF; /* NOT USED */

    pObj->algGpeOutBufDescGpeObjs.numPlanes                        = 1;
    /* Will be filled with output pointer later
     */
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].buf                 = NULL;
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].width               = sizeof(FCW_TI_output);
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].height              = 1;
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].frameROI.width      = pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].width;
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].frameROI.height     = 1;
    pObj->algGpeOutBufDescGpeObjs.bufPlanes[0].planeType           = 0;
    pObj->algGpeOutBufDescGpeObjs.formatType                       = 0; /* NOT USED */
    pObj->algGpeOutBufDescGpeObjs.bufferId                         = 0xFF; /* NOT USED */

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Alg uses the IVISION standard to interact with the
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
Int32 AlgorithmLink_fcwAlgParamsInit (
                                  AlgorithmLink_FcwObj *pObj,
                                  System_LinkChInfo *inChInfo
                                )
{
    UInt32 i;

    pObj->algFcwInBufs.size    = sizeof(pObj->algFcwInBufs);
    pObj->algFcwInBufs.numBufs = 1;
    pObj->algFcwInBufs.bufDesc = pObj->algFcwInBufDesc;

    pObj->algFcwInBufDesc[0]   = &pObj->algFcwInBufDescObjDesc;

    pObj->algFcwOutBufs.size    = sizeof(pObj->algFcwOutBufs);
    pObj->algFcwOutBufs.numBufs = 1;
    pObj->algFcwOutBufs.bufDesc = pObj->algFcwOutBufDesc;

    pObj->algFcwOutBufDesc[0]   = &pObj->algFcwOutBufDescFcwObjs;

    memset(&pObj->algFcwInArgs, 0, sizeof(pObj->algFcwInArgs));
    pObj->algFcwInArgs.iVisionInArgs.size         = sizeof(pObj->algFcwInArgs);
    pObj->algFcwInArgs.iVisionInArgs.subFrameInfo = 0;

    pObj->algFcwCreateParams.visionParams.algParams.size = sizeof(pObj->algFcwCreateParams);
    pObj->algFcwCreateParams.visionParams.cacheWriteBack = NULL;

    for(i=0; i<ALG_SFM_CAMERA_INTRENSIC_PARAM_SIZE; i++)
    {
        pObj->algFcwCreateParams.camIntPrm[i/3][i%3]
            =
            pObj->algLinkCreateParams.cameraIntrinsicParams[i];
    }
    pObj->algFcwCreateParams.maxNumObjects = FCW_TI_MAX_INPUT_OBJECTS;
    pObj->algFcwCreateParams.minObjDist    = pObj->algLinkCreateParams.minObjDist;
    pObj->algFcwCreateParams.maxObjDist    = pObj->algLinkCreateParams.maxObjDist;
    pObj->algFcwCreateParams.minObjHeight  = pObj->algLinkCreateParams.minObjHeight;
    pObj->algFcwCreateParams.maxObjHeight  = pObj->algLinkCreateParams.maxObjHeight;
    pObj->algFcwCreateParams.rsvd1         = 0;
    pObj->algFcwCreateParams.rsvd2         = 0;

    /* pObj->algFcwInArgs.camExtPrm[x] is set later on a per frame basis */
    /* pObj->algFcwInArgs.grndPlaneEq[x] is set later on a per frame basis */
    pObj->algFcwInArgs.fps               = pObj->algLinkCreateParams.frameRate;
    pObj->algFcwInArgs.camHeightInMeter  = pObj->algLinkCreateParams.camHeightInMeter;
    pObj->algFcwInArgs.camOffsetInMeter  = pObj->algLinkCreateParams.camOffsetInMeter;
    pObj->algFcwInArgs.imgHeight         = pObj->algLinkCreateParams.imageHeight;
    pObj->algFcwInArgs.reserved1         = 0;
    pObj->algFcwInArgs.reserved2         = 0;

    memset(&pObj->algFcwOutArgs, 0, sizeof(pObj->algFcwOutArgs));
    pObj->algFcwOutArgs.iVisionOutArgs.size         = sizeof(pObj->algFcwOutArgs);

    memset(&pObj->algFcwInBufDescObjDesc, 0, sizeof(pObj->algFcwInBufDescObjDesc));
    pObj->algFcwInBufDescObjDesc.numPlanes                        = 1;
    /* Will be filled with input pointer later
     */
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].buf                 = NULL;
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].width               = sizeof(FCW_TI_OD_input);
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].height              = 1;
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].frameROI.width      = pObj->algFcwInBufDescObjDesc.bufPlanes[0].width;
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].frameROI.height     = 1;
    pObj->algFcwInBufDescObjDesc.bufPlanes[0].planeType           = 0;
    pObj->algFcwInBufDescObjDesc.formatType                       = 0; /* NOT USED */
    pObj->algFcwInBufDescObjDesc.bufferId                         = 0xFF; /* NOT USED */

    memset(&pObj->algFcwOutBufDescFcwObjs, 0, sizeof(pObj->algFcwOutBufDescFcwObjs));
    pObj->algFcwOutBufDescFcwObjs.numPlanes                        = 1;
    /* Will be filled with output pointer later
     */
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].buf                 = NULL;
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].width               = sizeof(FCW_TI_output);
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].height              = 1;
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].frameROI.topLeft.x  = 0;
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].frameROI.topLeft.y  = 0;
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].frameROI.width      = pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].width;
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].frameROI.height     = 1;
    pObj->algFcwOutBufDescFcwObjs.bufPlanes[0].planeType           = 0;
    pObj->algFcwOutBufDescFcwObjs.formatType                       = 0; /* NOT USED */
    pObj->algFcwOutBufDescFcwObjs.bufferId                         = 0xFF; /* NOT USED */

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_fcwCreate(void * pObj,void * pCreateParams)
{
    UInt32 status;
    UInt32 prevLinkQId;
    UInt32 bufId;
    System_LinkInfo                                     prevLinkInfo;
    AlgorithmLink_FcwObj                  * pAlgObj;
    AlgorithmLink_OutputQueueInfo                       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                        * pInputQInfo;
    System_LinkChInfo                                   * pOutChInfo;
    System_Buffer                                       * pSystemBuffer;
    System_MetaDataBuffer                               * pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_FcwObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_FcwObj),
                        128);
    UTILS_assert(pAlgObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pAlgObj);

    pInputQInfo       = &pAlgObj->inputQInfo;
    pOutputQInfo      = &pAlgObj->outputQInfo;

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            &pAlgObj->algLinkCreateParams,
            pCreateParams,
            sizeof(pAlgObj->algLinkCreateParams)
           );

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    status = System_linkGetInfo(
                    pAlgObj->algLinkCreateParams.inQueParams.prevLinkId,
                    &prevLinkInfo
                    );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= 1);

    prevLinkQId = pAlgObj->algLinkCreateParams.inQueParams.prevLinkQueId;
    pAlgObj->inChInfo = prevLinkInfo.queInfo[prevLinkQId].chInfo[0];

    pOutputQInfo->queInfo.numCh = 1;

    pOutChInfo          = &pOutputQInfo->queInfo.chInfo[0];
    pOutChInfo->flags   = 0;
    pOutChInfo->height  = 0;
    pOutChInfo->width   = 0;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(
                                    pObj,
                                    1,
                                    pInputQInfo,
                                    1,
                                    pOutputQInfo
                               );

    AlgorithmLink_gpeAlgParamsInit(pAlgObj, &pAlgObj->inChInfo);

    pAlgObj->algGpeHandle = AlgIvision_create(
                        &GPE_TI_VISION_FXNS,
                        (IALG_Params *)&pAlgObj->algGpeCreateParams
                        );
    UTILS_assert(pAlgObj->algGpeHandle!=NULL);


    AlgorithmLink_fcwAlgParamsInit(pAlgObj, &pAlgObj->inChInfo);

    pAlgObj->algFcwHandle = AlgIvision_create(
                        &FCW_TI_VISION_FXNS,
                        (IALG_Params *)&pAlgObj->algFcwCreateParams
                        );
    UTILS_assert(pAlgObj->algFcwHandle!=NULL);

    if(pAlgObj->algLinkCreateParams.numOutBuffers
        > FCW_LINK_MAX_NUM_OUTPUT)
    {
        pAlgObj->algLinkCreateParams.numOutBuffers
            = FCW_LINK_MAX_NUM_OUTPUT;
    }

    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */

    for (bufId = 0; bufId < pAlgObj->algLinkCreateParams.numOutBuffers; bufId++)
    {
        pSystemBuffer       =   &pAlgObj->buffers[bufId];
        pMetaDataBuffer     =   &pAlgObj->metaDataBuffers[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pMetaDataBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =   0;

        pMetaDataBuffer->numMetaDataPlanes  =  1;
        pMetaDataBuffer->metaBufSize[0]
            =  FCW_LINK_FCW_OUT_BUF_SIZE;

        pMetaDataBuffer->bufAddr[0]         =  Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pMetaDataBuffer->metaBufSize[0],
                                                    128
                                                    );

        pMetaDataBuffer->metaFillLength[0] = pMetaDataBuffer->metaBufSize[0];

        UTILS_assert(pMetaDataBuffer->bufAddr[0] != NULL);

        pMetaDataBuffer->flags = 0;

        status = AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    pAlgObj->isFirstFrameRecv    = FALSE;

    /* Assign pointer to link stats object */
    pAlgObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_FCW");
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    return SYSTEM_LINK_STATUS_SOK;
}

Void AlgorithmLink_fcwPostProcess(AlgorithmLink_FcwObj *pObj,
        AlgorithmLink_FcwOutput *pOutput)
{
    FCW_TI_OD_input *pOdOut = &pOutput->objectDetectOut;
    FCW_TI_output *pFcwOut = &pOutput->fcwOut;
    FCW_TI_objectWorldInfo *pFcwObj;
    FCW_TI_objectDescriptor *pOdObj;
    UInt32 fcwIdx, odIdx;

    /* mark 'distFrmCamera' in Object list as invalid */
    for(odIdx=0; odIdx<pOdOut->numObjects; odIdx++)
    {
        pOdObj = &pOdOut->objDesc[odIdx];
        pOdObj->reserved0 = -100;
    }

    /* fill 'distFrmCamera' computed for objects by FCW */

    /* for all FCW computed results */
    #if 0
    {
        UInt32 tmpOdIdx;

        for(fcwIdx=0; fcwIdx<pFcwOut->numObjects; fcwIdx++)
        {
            pFcwObj = &pFcwOut->objWorldInfo[fcwIdx];

            /* find pFcwObj->objTag in pOdOut
             * start from index 'fcwIdx'
             */
            odIdx = fcwIdx;

            for(tmpOdIdx=0; tmpOdIdx<pOdOut->numObjects; tmpOdIdx++)
            {
                pOdObj = &pOdOut->objDesc[odIdx];

                if(pOdObj->objTag == pFcwObj->objTag)
                {
                    /* found match between FCW results and Obkect list */
                    pOdObj->reserved0 = pFcwObj->distFrmCamera;
                    #if 0
                    Vps_printf(" ALG_FWC: Obj #%d: Tag %d: %3.1f m",
                        odIdx,
                        pOdObj->objTag,
                        pOdObj->reserved0);
                    #endif
                    break;
                }

                odIdx++;
                /* wrap around to start */
                if(odIdx>=pOdOut->numObjects)
                {
                    odIdx = 0;
                }
            }
        }
    }
    #else
    for(fcwIdx=0; fcwIdx<pFcwOut->numObjects; fcwIdx++)
    {
        pFcwObj = &pFcwOut->objWorldInfo[fcwIdx];

        if(fcwIdx < pOdOut->numObjects)
        {
            pOdObj = &pOdOut->objDesc[fcwIdx];

            /* found match between FCW results and Obkect list */
            pOdObj->reserved0 = pFcwObj->distFrmCamera;
            #if 0
            Vps_printf(" ALG_FWC: Obj #%d: Tag %d: %3.1f m",
                odIdx,
                pOdObj->objTag,
                pOdObj->reserved0);
            #endif
        }
    }
    #endif
}

Int32 AlgorithmLink_fcwProcess(void * pObj)
{
    UInt32 bufId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_FcwObj                  * pAlgObj;
    System_BufferList                       inputBufList;
    AlgorithmLink_FcwCreateParams         * pLinkCreatePrms;
    System_Buffer                         * pSysOutBuffer;
    System_Buffer                         * pSysInBuffer;
    System_VideoFrameCompositeBuffer      * pInMetaBuf;
    System_MetaDataBuffer                 * pOutMetaBuf;
    System_BufferList                     bufListReturn;
    System_LinkStatistics *linkStatsInfo;

    pAlgObj = (AlgorithmLink_FcwObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);


    pLinkCreatePrms = &pAlgObj->algLinkCreateParams;

    linkStatsInfo = pAlgObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    if (pAlgObj->isFirstFrameRecv == FALSE)
    {
        pAlgObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                        pLinkCreatePrms->inQueParams.prevLinkId,
                        pLinkCreatePrms->inQueParams.prevLinkQueId,
                        &inputBufList);


    if (inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysInBuffer = inputBufList.buffers[bufId];
            if(pSysInBuffer == NULL)
            {
                linkStatsInfo->linkStats.inBufErrorCount++;
                continue;
            }

            linkStatsInfo->linkStats.chStats[0].inBufRecvCount++;

            UTILS_assert(
                pSysInBuffer->bufType ==
                    SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER);

            status = AlgorithmLink_getEmptyOutputBuffer(
                                                    pObj,
                                                    0,
                                                    0,
                                                    &pSysOutBuffer
                                                    );
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                linkStatsInfo->linkStats.chStats
                            [0].inBufDropCount++;
                linkStatsInfo->linkStats.chStats
                            [0].outBufDropCount[0]++;
            }
            else
            {
                AlgorithmLink_FcwOutput *pFcwOutput;
                AlgorithmLink_SfmOutput *pSfmOutput;
                FCW_TI_OD_input         *pOdOutput;

                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                pOutMetaBuf  = (System_MetaDataBuffer *)pSysOutBuffer->payload;
                pInMetaBuf  = (System_VideoFrameCompositeBuffer *) pSysInBuffer->payload;

                pFcwOutput = (AlgorithmLink_FcwOutput*)pOutMetaBuf->bufAddr[0];

                /* CH0 is OD output */
                pOdOutput  = (FCW_TI_OD_input*)pInMetaBuf->bufAddr[0][0];
                /* CH1 is SFM output */
                pSfmOutput = (AlgorithmLink_SfmOutput*)pInMetaBuf->bufAddr[0][1];

                pAlgObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE].bufPlanes[0].buf = (Void*)pOdOutput;
                pAlgObj->algFcwInBufDescObjDesc.bufPlanes[0].buf = (Void*)pOdOutput;

                pAlgObj->algGpeInBufDescObjDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE].bufPlanes[0].buf =
                                                                 (Void*)(pSfmOutput->sfmOut);



                pAlgObj->algFcwOutBufDescFcwObjs.bufPlanes[0].buf = (Void*)
                    &pFcwOutput->fcwOut;

                Cache_inv(
                          pOdOutput,
                          sizeof(FCW_TI_OD_input),
                          Cache_Type_ALLD,
                          TRUE
                        );

                Cache_inv(
                          pSfmOutput,
                          sizeof(AlgorithmLink_SfmOutput),
                          Cache_Type_ALLD,
                          TRUE
                        );

                memcpy(pAlgObj->algFcwInArgs.camExtPrm,
                        pSfmOutput->camExtPrm,
                        sizeof(pAlgObj->algFcwInArgs.camExtPrm)
                       );

                pAlgObj->algGpeInArgs.numPointCloud = pSfmOutput->outNumPoints;

                status = AlgIvision_process(
                                pAlgObj->algGpeHandle,
                                &pAlgObj->algGpeInBufs,
                                &pAlgObj->algGpeOutBufs,
                                (IVISION_InArgs*)&pAlgObj->algGpeInArgs,
                                (IVISION_OutArgs *)&pAlgObj->algGpeOutArgs
                    );

                if(status!=IALG_EOK)
                {
                    #if 0
                    Vps_printf(" ALG_FCW: ERROR: GPE process  AlgObj->algGpeInArgs.numPointCloud = %d !!!\n", pAlgObj->algGpeInArgs.numPointCloud);
                    #endif
                }


                pAlgObj->algFcwInArgs.grndPlaneEq[0] =  pAlgObj->algGpeOutArgs.grndPlaneEq[0];
                pAlgObj->algFcwInArgs.grndPlaneEq[1] =  pAlgObj->algGpeOutArgs.grndPlaneEq[1];
                pAlgObj->algFcwInArgs.grndPlaneEq[2] =  pAlgObj->algGpeOutArgs.grndPlaneEq[2];


                #ifndef ALG_DISABLE

                #if 0
                Vps_printf(" ALG_FCW: Running .... !!!\n"
                    );
                #endif

                status = AlgIvision_process(
                                pAlgObj->algFcwHandle,
                                &pAlgObj->algFcwInBufs,
                                &pAlgObj->algFcwOutBufs,
                                (IVISION_InArgs*)&pAlgObj->algFcwInArgs,
                                (IVISION_OutArgs *)&pAlgObj->algFcwOutArgs
                    );

                #if 1
                if(status!=IALG_EOK)
                {
                    Vps_printf(" ALG_FCW: ERROR: Alg process!!!\n");
                }
                #endif
                #else
                pFcwOutput->fcwOut.numObjects = 0;
                #endif

                /* copy object descriptors from input to output */
                memcpy(
                    &pFcwOutput->objectDetectOut,
                    pOdOutput,
                    sizeof(pFcwOutput->objectDetectOut)
                    );

                #if 0
                if(pFcwOutput->fcwOut.numObjects > 0
                    ||
                    pFcwOutput->objectDetectOut.numObjects > 0)
                {
                    Vps_printf(" ALG_FCW: %d OD objects, %d  FCW objects !!!\n",
                        pFcwOutput->objectDetectOut.numObjects,
                        pFcwOutput->fcwOut.numObjects
                        );
                }
                #endif

                AlgorithmLink_fcwPostProcess(pAlgObj, pFcwOutput);

                Cache_wb(
                          pOutMetaBuf->bufAddr[0],
                          pOutMetaBuf->metaBufSize[0],
                          Cache_Type_ALLD,
                          TRUE
                        );

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats
                            [0].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats
                            [0].outBufCount[0]++;

                status = AlgorithmLink_putFullOutputBuffer(
                                            pObj,
                                            0,
                                            pSysOutBuffer);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                System_sendLinkCmd(
                        pLinkCreatePrms->outQueParams.nextLink,
                        SYSTEM_CMD_NEW_DATA,
                        NULL);

                bufListReturn.numBuf = 1;
                bufListReturn.buffers[0] = pSysOutBuffer;
                status = AlgorithmLink_releaseOutputBuffer(
                                                   pObj,
                                                   0,
                                                   &bufListReturn
                                                  );
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }

            bufListReturn.numBuf = 1;
            bufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                          pObj,
                          0,
                          pLinkCreatePrms->inQueParams.prevLinkId,
                          pLinkCreatePrms->inQueParams.prevLinkQueId,
                          &bufListReturn,
                          &bufDropFlag);
        }
    }
    return status;
}

Int32 AlgorithmLink_fcwControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_FcwObj* pAlgObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pAlgObj = (AlgorithmLink_FcwObj *)
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
            AlgorithmLink_fcwPrintStatistics(
                                                                pObj,
                                                                pAlgObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

Int32 AlgorithmLink_fcwStop(void * pObj)
{
    return 0;
}

Int32 AlgorithmLink_fcwDelete(void * pObj)
{
    Int32 status;
    UInt32 bufId;
    AlgorithmLink_FcwObj *pAlgObj;
    System_MetaDataBuffer              *pMetaDataBuffer;

    pAlgObj = (AlgorithmLink_FcwObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pAlgObj->linkStatsInfo);
    UTILS_assert(status==0);

    /*
     * Free allocated memory for alg internal objects
     */
    status = AlgIvision_delete(pAlgObj->algGpeHandle);
    UTILS_assert(status==0);
    /*
     * Free allocated memory for alg internal objects
     */
    status = AlgIvision_delete(pAlgObj->algFcwHandle);
    UTILS_assert(status==0);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pAlgObj->algLinkCreateParams.numOutBuffers; bufId++)
    {
        pMetaDataBuffer     =   &pAlgObj->metaDataBuffers[bufId];

        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pMetaDataBuffer->bufAddr[0],
                                pMetaDataBuffer->metaBufSize[0]
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    Utils_memFree(
                       UTILS_HEAPID_DDR_CACHED_LOCAL,
                       pAlgObj,
                       sizeof(AlgorithmLink_FcwObj)
                    );
    return status;

}

Int32 AlgorithmLink_fcwPrintStatistics(void *pObj,
                AlgorithmLink_FcwObj *pAlgObj)
{
    UTILS_assert(NULL != pAlgObj->linkStatsInfo);

    Utils_printLinkStatistics(&pAlgObj->linkStatsInfo->linkStats,
                            "ALG_FCW",
                            TRUE);

    Utils_printLatency("ALG_FCW",
                       &pAlgObj->linkStatsInfo->linkLatency,
                       &pAlgObj->linkStatsInfo->srcToLinkLatency,
                       TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

