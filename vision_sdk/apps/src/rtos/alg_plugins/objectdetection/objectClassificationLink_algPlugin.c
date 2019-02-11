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
 * \file objectClassificationLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for Object Classification
 *         Link
 *
 * \version 0.0 (Nov 2015) : [YM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "objectClassificationLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */
#define INPUT_OBJ_WIDTH  (36)
#define INPUT_OBJ_HEIGHT (36)

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
Int32 AlgorithmLink_ObjectClassification_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_objectClassificationCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_objectClassificationProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_objectClassificationControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_objectClassificationStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_objectClassificationDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_OBJECTCLASSIFICATION;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief AlgorithmLink_objectClassificationInitIOBuffers is a helper function
 *        used at create time which initializes buffer descriptor prameters
 *
 * \param  pObj              [IN] pointer to AlgorithmLink_ObjectClassificationObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
UInt32 AlgorithmLink_objectClassificationInitIOBuffers(
                                  AlgorithmLink_ObjectClassificationObj *pObj
                                )
{
    IVISION_InBufs  *pInBufs    = &pObj->inBufs;
    IVISION_OutBufs *pOutBufs   = &pObj->outBufs;

    pInBufs->bufDesc  = pObj->inBufDescList;
    pOutBufs->bufDesc = pObj->outBufDescList;

    pObj->inBufDescList[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]  = &pObj->inBufDesc[0];
    pObj->inBufDescList[TI_OC_IN_BUFDESC_DETECTION_LIST] = &pObj->inBufDesc[1];
    pObj->outBufDescList[TI_OC_OUT_BUFDESC_OBJECT_LIST]  = &pObj->outBufDesc[0];
    pObj->outBufDescList[TI_OC_OUT_BUFDESC_IMAGE_LIST]   = &pObj->outBufDesc[1];

    pInBufs->size       = sizeof(IVISION_InBufs);
    pOutBufs->size      = sizeof(IVISION_OutBufs);
    pInBufs->numBufs    = TI_OC_IN_BUFDESC_TOTAL;
    pOutBufs->numBufs   = TI_OC_OUT_BUFDESC_TOTAL;

    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->numPlanes                           = 1;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].frameROI.topLeft.x     = 0;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].frameROI.topLeft.y     = 0;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].width                  = sizeof(IVISION_BufDesc) *
                                                                                            TI_OC_MAX_TOTAL_SCALES;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].height                 = 1;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].frameROI.width         = pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].width;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].frameROI.height        = pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].height;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].planeType              = 0;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].buf                    = NULL;

    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->numPlanes                          = 1;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].width                 = TI_OC_INPUT_LIST_SIZE;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].height                = 1;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.width        = pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].width;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].frameROI.height       = pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].height;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].planeType             = 0;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].buf                   = NULL;


    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->numPlanes                          = 1;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].width                 = TI_OC_OUTPUT_LIST_SIZE;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].height                = 1;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.width        = TI_OC_OUTPUT_LIST_SIZE;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].frameROI.height       = 1;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].planeType             = 0;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].buf                   = NULL;


    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->numPlanes                          = 1;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].width                 = INPUT_OBJ_WIDTH;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].height                = INPUT_OBJ_HEIGHT;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].frameROI.width        = INPUT_OBJ_WIDTH;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].frameROI.height       = INPUT_OBJ_HEIGHT;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].planeType             = 0;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].buf                   = NULL;

    return SYSTEM_LINK_STATUS_SOK;

}

/**
 *******************************************************************************
 *
 * \brief AlgorithmLink_objectClassificationSetIOArgs is a helper function
 *        used at create time which initializes buffer descriptor prameters
 *
 * \param  pObj              [IN] pointer to AlgorithmLink_ObjectClassificationObj
 *
 * \return
 *
 *******************************************************************************
 */
Void AlgorithmLink_objectClassificationSetIOArgs(
                AlgorithmLink_ObjectClassificationObj *pObj
                )
{
    pObj->inArgs.iVisionInArgs.size = sizeof(IVISION_InArgs);

    pObj->inArgs.inputMode = 0;
    pObj->inArgs.classifierType = 0;
    pObj->inArgs.reserved0 = 0;
    pObj->inArgs.reserved1 = 0;
    pObj->inArgs.reserved2 = 0;
    pObj->inArgs.reserved3 = 0;

    pObj->outArgs.iVisionOutArgs.size   = sizeof(IVISION_OutArgs);
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for Object Classification alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationCreate(void * pObj,void * pCreateParams)
{
    UInt32 numInputQUsed;
    UInt32 numOutputQUsed;
    UInt32 numChannelsUsed;
    UInt32 channelId;
    UInt32 status;
    UInt32 bufId;
    AlgorithmLink_ObjectClassificationObj          * pObjectClassifyObj;
    TI_OC_CreateParams                             * pAlgCreateParams;
    AlgorithmLink_ObjectClassificationCreateParams * pLinkCreateParams;
    AlgorithmLink_OutputQueueInfo                  * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                   * pInputQInfo;
    System_LinkInfo                                  prevLinkInfo;
    System_LinkChInfo                              * pOutChInfo;
    System_Buffer                                  * pSystemBuffer;
    System_MetaDataBuffer                          * pMetaDataBuffer;


    pObjectClassifyObj = (AlgorithmLink_ObjectClassificationObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_ObjectClassificationObj), 32);
    UTILS_assert(pObjectClassifyObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pObjectClassifyObj);

    pAlgCreateParams  = &pObjectClassifyObj->algCreateParams;
    pLinkCreateParams = (AlgorithmLink_ObjectClassificationCreateParams *)
                         pCreateParams;
    pInputQInfo       = &pObjectClassifyObj->inputQInfo;
    pOutputQInfo      = &pObjectClassifyObj->outputQInfo;
    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pObjectClassifyObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_ObjectClassificationCreateParams)
           );
    /*
     * Populating parameters corresponding to Q usage of geometric alignment
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = 1;
    numChannelsUsed             = 1;
    channelId                   = 0;

    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->queInfo.numCh = numChannelsUsed;

    status = System_linkGetInfo(
                                  pLinkCreateParams->inQueParams.prevLinkId,
                                  &prevLinkInfo
                                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= numInputQUsed);

    channelId           = 0;
    pOutChInfo          = &pOutputQInfo->queInfo.chInfo[channelId];
    pOutChInfo->flags   = 0;

    pOutChInfo->width   = pLinkCreateParams->imgFrameWidth;
    pOutChInfo->height  = pLinkCreateParams->imgFrameHeight;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(
                                    pObj,
                                    numInputQUsed,
                                    pInputQInfo,
                                    numOutputQUsed,
                                    pOutputQInfo
                               );

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */


    pAlgCreateParams->visionParams.algParams.size = sizeof(IVISION_Params);

    pAlgCreateParams->edma3RmLldHandle  = NULL;
    pAlgCreateParams->maxImageWidth     = pOutChInfo->width;
    pAlgCreateParams->maxImageHeight    = pOutChInfo->height;
    pAlgCreateParams->maxScales         = pLinkCreateParams->numScales;

    pObjectClassifyObj->handle = AlgIvision_create(
                                &TI_OC_VISION_FXNS,
                                (IALG_Params*)pAlgCreateParams
                                );
    UTILS_assert(pObjectClassifyObj->handle!=NULL);

    /*
     * Initialize input output buffers
     */
    AlgorithmLink_objectClassificationInitIOBuffers(pObjectClassifyObj);


    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer, output will still be an updated OD list.
     */

    pObjectClassifyObj->outBufferSize = TI_OC_OUTPUT_LIST_SIZE;

    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer       =   &pObjectClassifyObj->buffers[bufId];
        pMetaDataBuffer     =   &pObjectClassifyObj->ocOutput[bufId];

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->payload      =   pMetaDataBuffer;
        pSystemBuffer->payloadSize  =   sizeof(System_MetaDataBuffer);
        pSystemBuffer->chNum        =   0;

        pMetaDataBuffer->numMetaDataPlanes  =   1;
        pMetaDataBuffer->metaBufSize[0]     =   pObjectClassifyObj->outBufferSize;
        pMetaDataBuffer->metaFillLength[0]  =   pObjectClassifyObj->outBufferSize;
        pMetaDataBuffer->bufAddr[0]         =   Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    pObjectClassifyObj->outBufferSize,
                                                    ALGORITHMLINK_FRAME_ALIGN
                                                    );
        UTILS_assert(pMetaDataBuffer->bufAddr[0] != NULL);
        pMetaDataBuffer->flags = 0;

        AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }

    pObjectClassifyObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_OBJECT_CLASSIFICATION");
    UTILS_assert(NULL != pObjectClassifyObj->linkStatsInfo);

    pObjectClassifyObj->isFirstFrameRecv    = FALSE;

    AlgorithmLink_objectClassificationSetIOArgs(pObjectClassifyObj);


    pObjectClassifyObj->pTmpOutput = Utils_memAlloc( UTILS_HEAPID_DDR_CACHED_SR,
                ALGORITHM_LINK_OBJECTCLASSIFICATION_TMP_OUTPUT_SIZE,
                ALGORITHMLINK_FRAME_ALIGN
                );
    UTILS_assert(pObjectClassifyObj->pTmpOutput!=NULL);


    return status;
}

/**
 *******************************************************************************
 *
 * \brief AlgorithmLink_objectClassificationSetIOArgs is a helper function
 *        used at process time which ensures
 *        - Cache coherency of input & output buffers
 *        - Interpreting input from composite buffer and submitting to process
 *        - Merging object list with OC ouput
 *
 * \param  pObj  [IN] pointer to AlgorithmLink_ObjectClassificationObj
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationAlgProcess(Void *         pObj,
                                                   System_Buffer* pSysInBuffer,
                                                   System_Buffer* pSysOutBuffer)
{

    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Int32 i,j;
    AlgorithmLink_ObjectDetectionOutput            * pOCInputODLists;
    AlgorithmLink_ImgPyramidFrameDesc              * pOcInputImgPyramid;
    AlgorithmLink_ObjectClassificationObj          * pObjectClassifyObj;
    System_VideoFrameCompositeBuffer               * pCompDataInBuffer;
    System_MetaDataBuffer                          * pMetaDataOutBuffer;
    IVISION_InBufs                                 * pInBufs;
    IVISION_OutBufs                                * pOutBufs;
    TI_OC_InArgs                                   * pInArgs;
    TI_OC_OutArgs                                  * pOutArgs;

    TI_OD_outputList                               * pInputObjectList;
    TI_OC_outputList                               * pLocalObjectList;
    TI_OC_outputList                               * pOutputObjectList;


    pObjectClassifyObj = (AlgorithmLink_ObjectClassificationObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pInBufs  = &pObjectClassifyObj->inBufs;
    pOutBufs = &pObjectClassifyObj->outBufs;
    pInArgs  = &pObjectClassifyObj->inArgs;
    pOutArgs = &pObjectClassifyObj->outArgs;

    /*
     * Input buffer is a composite buffer with details of img pyramid, detect list and
     * object list. OC is intereseted in img pyramid and detection list.
     * object list is used to prepare final out put based on OC algorith output by merging
     * detect list from OC output with object list .
     */
    pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
    pSysOutBuffer->frameId = pSysInBuffer->frameId;
    pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

    pCompDataInBuffer    = (System_VideoFrameCompositeBuffer *)pSysInBuffer->payload;
    pMetaDataOutBuffer   = (System_MetaDataBuffer *)pSysOutBuffer->payload;

    pOCInputODLists      = (AlgorithmLink_ObjectDetectionOutput *) pCompDataInBuffer->bufAddr[0][0];
    pOcInputImgPyramid   = (AlgorithmLink_ImgPyramidFrameDesc *) pCompDataInBuffer->bufAddr[0][1];

    Cache_inv(pOCInputODLists,
              sizeof(AlgorithmLink_ObjectDetectionOutput),
              Cache_Type_ALLD,
              TRUE
             );

    Cache_inv(pOcInputImgPyramid,
              sizeof(AlgorithmLink_ImgPyramidFrameDesc) * pObjectClassifyObj->numScales,
              Cache_Type_ALLD,
              TRUE
             );


    for(i = 0; i < pObjectClassifyObj->numScales; i++)
    {
        Cache_inv((Void *)pOcInputImgPyramid[i].bufAddr[0],
                  pOcInputImgPyramid[i].pitch[0] * pOcInputImgPyramid[i].height,
                  Cache_Type_ALLD,
                  TRUE
                 );
        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].buf = (Void *)pOcInputImgPyramid[i].bufAddr[0];

        Cache_inv((Void *)pOcInputImgPyramid[i].bufAddr[1],
               (pOcInputImgPyramid[i].pitch[1] * pOcInputImgPyramid[i].height)/2,
               Cache_Type_ALLD,
               TRUE
              );
        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].buf = (Void *)pOcInputImgPyramid[i].bufAddr[1];

    }

    pInBufs->bufDesc[0]->bufferId   = (UInt32)pSysInBuffer;

    /* prepare input and output buffs for algorithm */

    pInBufs->bufDesc[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]->bufPlanes[0].buf  = pObjectClassifyObj->inBufImgPyramid;
    pInBufs->bufDesc[TI_OC_IN_BUFDESC_DETECTION_LIST]->bufPlanes[0].buf = (Void *) &pOCInputODLists->detectionList;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_OBJECT_LIST]->bufPlanes[0].buf  = &pObjectClassifyObj->detectionListLocal;
    pOutBufs->bufDesc[TI_OC_OUT_BUFDESC_IMAGE_LIST]->bufPlanes[0].buf   = pObjectClassifyObj->pTmpOutput;

    pObjectClassifyObj->detectionListLocal.numObjects = 0;

    status = IALG_EOK;
    if(pOCInputODLists->detectionList.numObjects > 0)
    {

        status = AlgIvision_process(
                                 (IVISION_Handle)pObjectClassifyObj->handle,
                                 pInBufs,
                                 pOutBufs,
                                 (IVISION_InArgs *)pInArgs,
                                 (IVISION_OutArgs *)pOutArgs
                                );
    }

    if (status != IALG_EOK)
    {
        UTILS_assert(NULL);
    }
    else
    {
        /* Merge output of object classification (final detection list) with input object list
         * Object list is the superset of detection list and object list at input */

        pInputObjectList   = (TI_OD_outputList *) &pOCInputODLists->objectList;
        pLocalObjectList   = (TI_OC_outputList *) &pObjectClassifyObj->detectionListLocal;
        pOutputObjectList  = (TI_OC_outputList *) pMetaDataOutBuffer->bufAddr[0];

        UTILS_assert(pInputObjectList->numObjects  < TI_OD_MAX_NUM_OBJECTS);
        UTILS_assert(pLocalObjectList->numObjects  < TI_OD_MAX_NUM_OBJECTS);

        memcpy(pOutputObjectList, (Void *) pInputObjectList, sizeof(TI_OD_outputList));

        for(i = 0; i < pLocalObjectList->numObjects; i++)
        {
            for(j = 0; j < pOutputObjectList->numObjects; j++)
            {
                if(pOutputObjectList->objDesc[j].objTag == pLocalObjectList->objDesc[i].objTag)
                {
                    pOutputObjectList->objDesc[j].objSubType = pLocalObjectList->objDesc[i].objSubType;
                    break;
                }
            }
        }

        Cache_wb(pMetaDataOutBuffer->bufAddr[0],
               pMetaDataOutBuffer->metaBufSize[0],
               Cache_Type_ALLD,
               TRUE
                );
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for Object Classification alg link
 *
 * \param  pObj  [IN] pointer to AlgorithmLink_ObjectClassificationObj
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationProcess(void * pObj)
{
    UInt32 bufId;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_ObjectClassificationObj          * pObjectClassifyObj;
    System_BufferList                                inputBufList;
    AlgorithmLink_ObjectClassificationCreateParams * pLinkCreateParams;
    System_Buffer                                  * pSysOutBuffer;
    System_Buffer                                  * pSysInBuffer;
    System_BufferList                                outputBufListReturn;
    System_BufferList                                inputBufListReturn;
    System_LinkStatistics                          * linkStatsInfo;


    pObjectClassifyObj = (AlgorithmLink_ObjectClassificationObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pObjectClassifyObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    pLinkCreateParams = &pObjectClassifyObj->algLinkCreateParams;

    if (pObjectClassifyObj->isFirstFrameRecv == FALSE)
    {
        pObjectClassifyObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(&linkStatsInfo->linkStats, 1, 1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    System_getLinksFullBuffers(
                        pLinkCreateParams->inQueParams.prevLinkId,
                        pLinkCreateParams->inQueParams.prevLinkQueId,
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

               status = AlgorithmLink_objectClassificationAlgProcess(pObj,
                                                                     pSysInBuffer,
                                                                     pSysOutBuffer);

               Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysOutBuffer->linkLocalTimestamp);
               Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysOutBuffer->srcTimestamp);

               linkStatsInfo->linkStats.chStats
                                [0].inBufProcessCount++;
               linkStatsInfo->linkStats.chStats
                                [0].outBufCount[0]++;

               /*
                * <TODO For Now not handling locking of output buffers
                *  case >
                */
               status = AlgorithmLink_putFullOutputBuffer(
                                                pObj,
                                                0,
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

               AlgorithmLink_releaseOutputBuffer(
                                                  pObj,
                                                  0,
                                                  &outputBufListReturn
                                                  );
            }

            inputBufListReturn.numBuf = 1;
            inputBufListReturn.buffers[0] = pSysInBuffer;
            bufDropFlag = FALSE;
            AlgorithmLink_releaseInputBuffer(
                              pObj,
                              0,
                              pLinkCreateParams->inQueParams.prevLinkId,
                              pLinkCreateParams->inQueParams.prevLinkQueId,
                              &inputBufListReturn,
                              &bufDropFlag);
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for Object Classification alg link
 *
 * \param  pObj  [IN] pointer to AlgorithmLink_ObjectClassificationObj
 * \param  pObj  [IN] pointer to pControlParams
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_ObjectClassificationObj* pObjectClassifyObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;
    AlgorithmLink_ImgPyramidInfo        * pImgPmdInfo;
    AlgorithmLink_ImgPyramidImgPyramidInfoControlParams *imgPyramidInfoControlParams;
    Int32 i = 0;


    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pObjectClassifyObj = (AlgorithmLink_ObjectClassificationObj *)
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
        case ALGORITHM_LINK_OBJECTCLASSIFICATION_CMD_CREATE_ALG:
                imgPyramidInfoControlParams = (AlgorithmLink_ImgPyramidImgPyramidInfoControlParams *)
                                        pControlParams;

                if (NULL != imgPyramidInfoControlParams)
                {
                    pImgPmdInfo = &(imgPyramidInfoControlParams->imgPyramidInfo);

                    pObjectClassifyObj->numScales = pImgPmdInfo->numScales;

                    for(i = 0; i < pImgPmdInfo->numScales; i++)
                    {

                        pObjectClassifyObj->inBufImgPyramid[i].numPlanes                          = 2;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].width                 = pImgPmdInfo->frmDesc[i].pitch[0];
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].height                = pImgPmdInfo->frmDesc[i].height;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].frameROI.width        = pImgPmdInfo->frmDesc[i].width;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].frameROI.height       = pImgPmdInfo->frmDesc[i].height;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].planeType             = 0;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].buf                   = NULL;

                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].width                 = pImgPmdInfo->frmDesc[i].pitch[1];
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].height                = pImgPmdInfo->frmDesc[i].height/2;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].frameROI.width        = pImgPmdInfo->frmDesc[i].width;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].frameROI.height       = pImgPmdInfo->frmDesc[i].height/2;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].planeType             = 1;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].buf                   = NULL;

                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].frameROI.topLeft.x    = 0;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[0].frameROI.topLeft.y    = 0;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].frameROI.topLeft.x    = 0;
                        pObjectClassifyObj->inBufImgPyramid[i].bufPlanes[1].frameROI.topLeft.y    = 0;
                    }
                }
                else
                {
                    status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                }

            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_objectClassificationPrintStatistics(
                                                             pObj,
                                                             pObjectClassifyObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for Object Classification alg link
 *
 * \param  pObj  [IN] pointer to AlgorithmLink_ObjectClassificationObj
 * \param  pObj  [IN] pointer to pControlParams
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationStop(void * pObj)
{
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for Object Classification alg link
 *
 * \param  pObj  [IN] pointer to AlgorithmLink_ObjectClassificationObj
 * \param  pObj  [IN] pointer to pControlParams
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationDelete(void * pObj)
{
    UInt32 status;
    UInt32 bufId;
    AlgorithmLink_ObjectClassificationObj                   * pObjectClassifyObj;
    AlgorithmLink_ObjectClassificationCreateParams          * pLinkCreateParams;
    System_MetaDataBuffer                                   * pMetaDataBuffer;

    pObjectClassifyObj = (AlgorithmLink_ObjectClassificationObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    pLinkCreateParams = &pObjectClassifyObj->algLinkCreateParams;

    status = Utils_linkStatsCollectorDeAllocInst(pObjectClassifyObj->linkStatsInfo);
    UTILS_assert(status==0);

    status = AlgIvision_delete(pObjectClassifyObj->handle);
    UTILS_assert(status==0);

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pMetaDataBuffer     =   &pObjectClassifyObj->ocOutput[bufId];


        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pMetaDataBuffer->bufAddr[0],
                                pMetaDataBuffer->metaBufSize[0]
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    Utils_memFree( UTILS_HEAPID_DDR_CACHED_SR,
                pObjectClassifyObj->pTmpOutput,
                ALGORITHM_LINK_OBJECTCLASSIFICATION_TMP_OUTPUT_SIZE
                );

    Utils_memFree(
                   UTILS_HEAPID_DDR_CACHED_LOCAL,
                   pObjectClassifyObj,
                   sizeof(AlgorithmLink_ObjectClassificationObj)
                );

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Helper function to print stats for Object Classification alg link
 *
 * \param  pObj  [IN] pointer to AlgorithmLink_ObjectClassificationObj
 * \param  pObj  [IN] pointer to OC object
 *
 * \return SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectClassificationPrintStatistics(void *pObj,
                AlgorithmLink_ObjectClassificationObj *pObjectClassificationObj)
{
    UTILS_assert(NULL != pObjectClassificationObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObjectClassificationObj->linkStatsInfo->linkStats,
                            "ALG_OBJECT_CLASSIFICATION",
                            TRUE);

    Utils_printLatency("ALG_OBJECT_CLASSIFICATION",
                       &pObjectClassificationObj->linkStatsInfo->linkLatency,
                       &pObjectClassificationObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}
