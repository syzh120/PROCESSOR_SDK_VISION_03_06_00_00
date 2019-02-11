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
 * \file remapMergeLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for remapMerge algorithm
 *
 * \version 0.0 (Oct 2014) : [YM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "remapMergeLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <evelib_memcopy_dma_2d.h>
#include <string.h>


void stereovision_getLeftBlockMap(unsigned char **pSrcBlkMapLeft, unsigned int *blockMap_LEN, sConvertMap *mapStruct);
void stereovision_getRightBlockMap(unsigned char **pSrcBlkMapRight, unsigned int *blockMap_LEN, sConvertMap *mapStruct);

void stereovision_getBlockMap(uint8_t **srcBlkMap, uint32_t *blockMap_LEN, sConvertMap *maps, uint8_t *convertedMap) {

    uint32_t i;
    uint8_t *p;
    p= (uint8_t*)maps;

    for (i=0; i< sizeof(sConvertMap);i++)
        *p++= *convertedMap++;

    p= (uint8_t*)blockMap_LEN;
    for (i=0; i< sizeof(*blockMap_LEN);i++)
        *p++= *convertedMap++;

    *srcBlkMap= convertedMap;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMerge_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_RemapMergeCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_RemapMergeProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_RemapMergeControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_RemapMergeStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_RemapMergeDelete;

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_REMAPMERGE;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);
    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Remap merge Alg uses the IVISION standard to interact with the
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
UInt32 AlgorithmLink_RemapMergeInitIOBuffers
                                (
                                  AlgorithmLink_RemapMergeObj *pObj
                                )
{
    IVISION_InBufs  *pInBufs;
    IVISION_OutBufs *pOutBufs;
    AlgorithmLink_RemapMergeCreateParams *pLinkPrms = &pObj->algLinkCreateParams;

    pInBufs = &pObj->inBufs;
    pInBufs->size       = sizeof(IVISION_InBufs);
    pInBufs->numBufs    = REMAP_MERGE_TI_BUFDESC_IN_REMAP_TOTAL;
    pInBufs->bufDesc    = pObj->inBufDescList;
    pObj->inBufDescList[0]  = &pObj->inBufDesc;
    pObj->inBufDescList[1]  = &pObj->lutBufDesc;



    pOutBufs = &pObj->outBufs;
    pOutBufs->size      = sizeof(IVISION_OutBufs);
    pOutBufs->numBufs   = REMAP_MERGE_TI_BUFDESC_OUT_TOTAL;
    pOutBufs->bufDesc   = pObj->outBufDescList;
    pObj->outBufDescList[0]= &pObj->outBufDesc;

    pInBufs->bufDesc[0]->numPlanes                          = 1;
    pInBufs->bufDesc[0]->bufPlanes[0].buf                   = NULL;
    pInBufs->bufDesc[0]->bufPlanes[0].width                 = pLinkPrms->srcStride;
    pInBufs->bufDesc[0]->bufPlanes[0].height                = pLinkPrms->srcHeight;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = pLinkPrms->srcStride;
    pInBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = pLinkPrms->srcHeight;
    pInBufs->bufDesc[0]->bufPlanes[0].planeType = 0;

    pInBufs->bufDesc[1]->numPlanes                          = 1;
    pInBufs->bufDesc[1]->bufPlanes[0].buf                   = NULL;
    pInBufs->bufDesc[1]->bufPlanes[0].width                 = 0;
    pInBufs->bufDesc[1]->bufPlanes[0].height                = 1;
    pInBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pInBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pInBufs->bufDesc[1]->bufPlanes[0].frameROI.width        = 0;
    pInBufs->bufDesc[1]->bufPlanes[0].frameROI.height       = 1;


    pOutBufs->bufDesc[0]->numPlanes                          = 1;
    pOutBufs->bufDesc[0]->bufPlanes[0].buf                   = NULL;
    pOutBufs->bufDesc[0]->bufPlanes[0].width                 = pLinkPrms->dstStride;
    pOutBufs->bufDesc[0]->bufPlanes[0].height                = pLinkPrms->roiHeight;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = pLinkPrms->roiWidth;
    pOutBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = pLinkPrms->roiHeight;

    pObj->output_pitch = pLinkPrms->roiWidth;
    pObj->output_height = pLinkPrms->roiHeight;

    return SYSTEM_LINK_STATUS_SOK;

}


/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for algorithm draw alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergeCreate(void * pObj,void * pCreateParams)
{
    UInt32                                 status = SYSTEM_LINK_STATUS_SOK;
    UInt32                                 numInputQUsed;
    UInt32                                 numOutputQUsed;
    UInt32                                 channelId;
    UInt32                                 outputQId;
    UInt32                                 prevLinkQueId;
    UInt32                                 bufId;
    UInt32                                 outBufferSize;
    System_LinkInfo                        prevLinkInfo;
    System_LinkChInfo                    * pOutChInfo;
    System_LinkChInfo                    * pPrevChInfo;
    System_VideoFrameBuffer              * pSysVideoFrameBufferOutput;
    System_Buffer                        * pSystemBuffer;

    AlgorithmLink_RemapMergeObj          * pRemapMergeObj;
    AlgorithmLink_RemapMergeCreateParams * pLinkCreateParams;
    REMAP_MERGE_TI_CreateParams          * pAlgCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;

    IVISION_InArgs                       *pInArgs;
    IVISION_OutArgs                      *pOutArgs;

    char pgmHeader[32];
    UInt8                                *pRectMapLeftLUT, *pRectMapRightLUT;
    pLinkCreateParams = (AlgorithmLink_RemapMergeCreateParams *)
                         pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pRemapMergeObj = (AlgorithmLink_RemapMergeObj *)
                    Utils_memAlloc(
                        UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_RemapMergeObj),
                        32);
    UTILS_assert(pRemapMergeObj != NULL);
    AlgorithmLink_setAlgorithmParamsObj(pObj, pRemapMergeObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pRemapMergeObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_RemapMergeCreateParams)
           );


    pAlgCreateParams  = &pRemapMergeObj->algCreateParams;

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */
    pAlgCreateParams->visionParams.algParams.size = sizeof(*pAlgCreateParams);
    pAlgCreateParams->visionParams.cacheWriteBack = NULL;

    pAlgCreateParams->remapParams.maps.isSrcMapFloat  = pLinkCreateParams->isSrcMapFloat;
    pAlgCreateParams->remapParams.maps.srcFormat      = pLinkCreateParams->srcFormat;
    pAlgCreateParams->remapParams.maps.qShift         = pLinkCreateParams->mapQshift;

    pAlgCreateParams->remapParams.interpolationLuma   = pLinkCreateParams->interpolationLuma;
    pAlgCreateParams->remapParams.interpolationChroma = pLinkCreateParams->interpolationChroma;
    pAlgCreateParams->remapParams.rightShift          = pLinkCreateParams->rightShift;
    pAlgCreateParams->remapParams.sat_high            = pLinkCreateParams->sat_high;
    pAlgCreateParams->remapParams.sat_high_set        = pLinkCreateParams->sat_high_set;
    pAlgCreateParams->remapParams.sat_low             = pLinkCreateParams->sat_low;
    pAlgCreateParams->remapParams.sat_low_set         = pLinkCreateParams->sat_low_set;

    /* check for params->maps.srcMap in tb */

    pAlgCreateParams->remapParams.maps.srcImageDim.width      = pLinkCreateParams->srcStride;
    pAlgCreateParams->remapParams.maps.srcImageDim.height     = pLinkCreateParams->srcHeight;
    pAlgCreateParams->remapParams.maps.mapDim.width           = pLinkCreateParams->roiWidth;
    pAlgCreateParams->remapParams.maps.mapDim.height          = pLinkCreateParams->roiHeight;
    pAlgCreateParams->remapParams.maps.outputBlockDim.width   = pLinkCreateParams->blockWidthBB;
    pAlgCreateParams->remapParams.maps.outputBlockDim.height  = pLinkCreateParams->blockHeightBB;

    pAlgCreateParams->enableMerge                     = pLinkCreateParams->enableMerge;
    pAlgCreateParams->dstFormat                       = pLinkCreateParams->dstFormat;

    /*
     * Populating parameters corresponding to Q usage of soft isp
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = 1;
    pInputQInfo                 = &pRemapMergeObj->inputQInfo;
    pOutputQInfo                = &pRemapMergeObj->outputQInfo;
    pInputQInfo->qMode          = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode         = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    outputQId                   = 0;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In soft isp Link, only data format changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(
                                  pLinkCreateParams->inQueParams.prevLinkId,
                                  &prevLinkInfo
                                );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    UTILS_assert(prevLinkInfo.numQue >= numInputQUsed);

    prevLinkQueId = pLinkCreateParams->inQueParams.prevLinkQueId;
    pRemapMergeObj->numInputChannels = prevLinkInfo.queInfo[prevLinkQueId].numCh;
    pOutputQInfo->queInfo.numCh = pRemapMergeObj->numInputChannels;

    for(channelId =0 ; channelId < pRemapMergeObj->numInputChannels; channelId++)    {

        if(!pLinkCreateParams->calibLUTBufPrms.isValid)
        {

            if (channelId== 0) {
                Vps_printf("ALGORITHM: RemapMerge is using right LUT found in rectMapRight_int_converted.c as there is no table in QSPI.\n");
                stereovision_getRightBlockMap(&(pRemapMergeObj->srcBlkMap[0]),
                        &(pRemapMergeObj->blockMapLen[0]),
                        &(pAlgCreateParams->remapParams.maps));
            }
            else {
                Vps_printf("ALGORITHM: RemapMerge is using left LUT found in rectMapLeft_int_converted.c as there is no table in QSPI.\n");
                /* Store left and right channel LUTs, blockMap_len remains same across channels */
                stereovision_getLeftBlockMap(&(pRemapMergeObj->srcBlkMap[1]),
                        &(pRemapMergeObj->blockMapLen[1]),
                        &(pAlgCreateParams->remapParams.maps));
            }
        }
        else
        {
            pRectMapRightLUT = pLinkCreateParams->calibLUTBufPrms.pCalibLUTBuf + 4;
            pRectMapLeftLUT = pLinkCreateParams->calibLUTBufPrms.pCalibLUTBuf + 4
                    +(pLinkCreateParams->calibLUTBufPrms.calibLUTBufSize/2);
            if (channelId== 0) {
                Vps_printf("ALGORITHM: RemapMerge is using right LUT stored in QSPI, table in rectMapRight_int_converted.c is ignored.\n");
                stereovision_getBlockMap(&(pRemapMergeObj->srcBlkMap[0]),
                        &(pRemapMergeObj->blockMapLen[0]),
                        &(pAlgCreateParams->remapParams.maps), pRectMapRightLUT);
            } else {
                Vps_printf("ALGORITHM: RemapMerge is using left LUT stored in QSPI, table in rectMapLeft_int_converted.c is ignored.\n");
                /* Store left and right channel LUTs, blockMap_len remains same across channels */
                stereovision_getBlockMap(&(pRemapMergeObj->srcBlkMap[1]),
                        &(pRemapMergeObj->blockMapLen[1]),
                        &(pAlgCreateParams->remapParams.maps), pRectMapLeftLUT);
            }
        }

        pRemapMergeObj->handle[channelId] = AlgIvision_create(&REMAP_MERGE_TI_VISION_FXNS, (IALG_Params *)pAlgCreateParams);
        UTILS_assert(pRemapMergeObj->handle!=NULL);
    }
    /*
     * Initialize input output buffers
     */
    status = AlgorithmLink_RemapMergeInitIOBuffers(pRemapMergeObj);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Channel Info Population
     */
    for(channelId =0 ; channelId < pRemapMergeObj->numInputChannels; channelId++)
    {
        pOutChInfo      = &(pOutputQInfo->queInfo.chInfo[channelId]);
        pPrevChInfo     = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

        pOutChInfo->startX = 0;
        pOutChInfo->startY = 0;
        pOutChInfo->width  = pAlgCreateParams->remapParams.maps.mapDim.width;
        pOutChInfo->height = pAlgCreateParams->remapParams.maps.mapDim.height; // TBD : Changed
        pOutChInfo->flags = pPrevChInfo->flags;
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pOutChInfo->flags,
                                                    SYSTEM_DF_YUV420SP_UV);
        pOutChInfo->pitch[0] = pRemapMergeObj->output_pitch;
        pOutChInfo->pitch[1] = pRemapMergeObj->output_pitch;
        pOutChInfo->pitch[2] = 0;

        /*
         * Taking a copy of input channel info in the link object for any future
         * use
         */
        memcpy((void *)&(pRemapMergeObj->inputChInfo[channelId]),
            (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
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
    for(channelId =0 ; channelId < pRemapMergeObj->numInputChannels; channelId++)
    {
        for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
        {
            pSystemBuffer           =  &pRemapMergeObj->buffers[channelId][bufId];
            pSysVideoFrameBufferOutput
                                    =  &pRemapMergeObj->videoFrames[channelId][bufId];

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSystemBuffer->bufType      =   SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
            pSystemBuffer->payload      =   pSysVideoFrameBufferOutput;
            pSystemBuffer->payloadSize  =   sizeof(System_VideoFrameBuffer);
            pSystemBuffer->chNum        =   channelId;

            memcpy((void *)&pSysVideoFrameBufferOutput->chInfo,
               (void *)&pOutputQInfo->queInfo.chInfo[channelId],
               sizeof(System_LinkChInfo));

            outBufferSize = pRemapMergeObj->output_pitch*pRemapMergeObj->output_height;
            pSysVideoFrameBufferOutput->bufAddr[0] = Utils_memAlloc(
                                                     UTILS_HEAPID_DDR_CACHED_SR,
                                                     outBufferSize,
                                                     ALGORITHMLINK_FRAME_ALIGN
                                                     );
            UTILS_assert(pSysVideoFrameBufferOutput->bufAddr[0] != NULL);

            pSysVideoFrameBufferOutput->bufAddr[1] = Utils_memAlloc(
                                                     UTILS_HEAPID_DDR_CACHED_SR,
                                                     outBufferSize/2,
                                                     ALGORITHMLINK_FRAME_ALIGN
                                                     );
            UTILS_assert(pSysVideoFrameBufferOutput->bufAddr[1] != NULL);
            /*
            * Initialising the chroma data with 0x80 as SOftISP works only on
            * Luma data
            */
            memset(pSysVideoFrameBufferOutput->bufAddr[1],0x80,outBufferSize/2);

            status = AlgorithmLink_putEmptyOutputBuffer
                                            (pObj, outputQId, pSystemBuffer);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    pInArgs               = &pRemapMergeObj->inArgs;
    pInArgs->subFrameInfo = 0;
    pInArgs->size         = sizeof(IVISION_InArgs);

    pOutArgs              = &pRemapMergeObj->outArgs;
    pOutArgs->size        = sizeof(IVISION_OutArgs);


    pRemapMergeObj->isFirstFrameRecv    = FALSE;

    pRemapMergeObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_REMAP_REMERGE");
    UTILS_assert(NULL != pRemapMergeObj->linkStatsInfo);

    /* Allocate Extra frame for saving captured frame */
    if (pRemapMergeObj->algLinkCreateParams.allocBufferForRawDump)
    {
        /* Define pgm header */
        sprintf(pgmHeader, "P5%c%d %d%c255%c", 10, pLinkCreateParams->srcStride, pLinkCreateParams->srcHeight, 10, 10);
        pRemapMergeObj->pgmHeaderSize= strlen(pgmHeader);

        pRemapMergeObj->saveFrameBufSize
            = (pLinkCreateParams->srcStride * pLinkCreateParams->srcHeight + pRemapMergeObj->pgmHeaderSize)*2;
        pRemapMergeObj->saveFrameBufAddr =
            Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pRemapMergeObj->saveFrameBufSize,
                ALGORITHMLINK_FRAME_ALIGN);
        UTILS_assert(pRemapMergeObj->saveFrameBufAddr != NULL);

/* Copy PGM header to the beginning of left and right raw dump */
        memcpy(pRemapMergeObj->saveFrameBufAddr, pgmHeader, pRemapMergeObj->pgmHeaderSize);
        memcpy(pRemapMergeObj->saveFrameBufAddr + pRemapMergeObj->saveFrameBufSize/2, pgmHeader, pRemapMergeObj->pgmHeaderSize);
        pRemapMergeObj->saveFrame[0] = FALSE;
        pRemapMergeObj->saveFrame[1] = FALSE;
    }

    return status;


}


/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for Remap Merge algorithm link
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
Int32 AlgorithmLink_RemapMergeProcess(void * pObj)
{
    UInt32                                  bufId;
    UInt32                                  inputQId;
    UInt32                                  channelId;
    UInt32                                  outputQId;
    UInt32                                  status = SYSTEM_LINK_STATUS_SOK;
    Bool                                    bufDropFlag;
    AlgorithmLink_RemapMergeObj             * pRemapMergeObj;
    AlgorithmLink_RemapMergeCreateParams    * pLinkCreateParams;
    System_Buffer                           * pSysOutBuffer;
    System_Buffer                           * pSysInBuffer;
    System_VideoFrameBuffer                 * pSysVideoFrameBufferInput;
    System_VideoFrameBuffer                 * pSysVideoFrameBufferOutput;
    IVISION_InBufs                          * pInBufs;
    IVISION_OutBufs                         * pOutBufs;
    IVISION_InArgs                          * pInArgs;
    IVISION_OutArgs                         * pOutArgs;
    System_BufferList                       inputBufList;
    System_BufferList                       outputBufListReturn;
    System_BufferList                       inputBufListReturn;
    UInt8                                   * saveFrameAddress;
    System_LinkStatistics                   * linkStatsInfo;

    pRemapMergeObj = (AlgorithmLink_RemapMergeObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);



    linkStatsInfo = pRemapMergeObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    pLinkCreateParams = &pRemapMergeObj->algLinkCreateParams;

    pInBufs  = &pRemapMergeObj->inBufs;
    pOutBufs = &pRemapMergeObj->outBufs;
    pInArgs  = &pRemapMergeObj->inArgs;
    pOutArgs = &pRemapMergeObj->outArgs;

    System_getLinksFullBuffers(
                        pLinkCreateParams->inQueParams.prevLinkId,
                        pLinkCreateParams->inQueParams.prevLinkQueId,
                        &inputBufList);

    linkStatsInfo->linkStats.newDataCmdCount++;

    if (inputBufList.numBuf)
    {
        if (pRemapMergeObj->isFirstFrameRecv == FALSE)
        {
            pRemapMergeObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics
                        (&linkStatsInfo->linkStats, pRemapMergeObj->numInputChannels, 1);
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
            if(channelId < pRemapMergeObj->numInputChannels)
            {
                linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;
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
                 linkStatsInfo->linkStats.chStats[channelId].inBufDropCount++;
                 linkStatsInfo->linkStats.chStats[channelId].outBufDropCount[0]++;
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

                pSysVideoFrameBufferOutput
                    = (System_VideoFrameBuffer *)pSysOutBuffer->payload;
                pSysVideoFrameBufferInput
                    = (System_VideoFrameBuffer *)pSysInBuffer->payload;

                /*
                 * Index 0: RCCC data format
                */
                pInBufs->bufDesc[0]->bufPlanes[0].buf
                                = pSysVideoFrameBufferInput->bufAddr[0];
                pInBufs->bufDesc[0]->bufferId   = (UInt32)pSysInBuffer;

                // populate convert map and block len here based on channels


                /*
                 * Index 0: Y data YUV420 format
                */
                pOutBufs->bufDesc[0]->bufPlanes[0].buf
                                = pSysVideoFrameBufferOutput->bufAddr[0];

                /* Right channel so plugin right source map*/
                pInBufs->bufDesc[1]->bufPlanes[0].buf = (UInt8 *)pRemapMergeObj->srcBlkMap[channelId];
                pInBufs->bufDesc[1]->bufPlanes[0].width          = pRemapMergeObj->blockMapLen[channelId];
                pInBufs->bufDesc[1]->bufPlanes[0].frameROI.width = pRemapMergeObj->blockMapLen[channelId];


                if ((TRUE == pRemapMergeObj->algLinkCreateParams.allocBufferForRawDump) &&
                    (TRUE == pRemapMergeObj->saveFrame[channelId]))
                {
                    if(channelId)
                        saveFrameAddress = pRemapMergeObj->saveFrameBufAddr +
                                        (pRemapMergeObj->saveFrameBufSize/2) + pRemapMergeObj->pgmHeaderSize;
                    else
                        saveFrameAddress = pRemapMergeObj->saveFrameBufAddr + pRemapMergeObj->pgmHeaderSize;
                    EVELIB_memcopyDMA2D(
                                (UInt8 *)pInBufs->bufDesc[0]->bufPlanes[0].buf,
                                (UInt8 *)saveFrameAddress,
                                pInBufs->bufDesc[0]->bufPlanes[0].width,
                                pInBufs->bufDesc[0]->bufPlanes[0].height,
                                pInBufs->bufDesc[0]->bufPlanes[0].width,
                                pInBufs->bufDesc[0]->bufPlanes[0].width);

                    /* Reset the flag */
                    pRemapMergeObj->saveFrame[channelId] = FALSE;

                    Vps_printf(" ******************************************\n");
                    Vps_printf(" saveRaw(0, 0x%x, %d, 32, false); ",
                        saveFrameAddress,
                        pInBufs->bufDesc[0]->bufPlanes[0].width *
                        pInBufs->bufDesc[0]->bufPlanes[0].height / 4);
                    Vps_printf(" ******************************************\n");
                }

                if (TRUE == pRemapMergeObj->algLinkCreateParams.allocBufferForRawDump) {
                            EVELIB_memcopyDMA2D(
                                                            (UInt8 *)pInBufs->bufDesc[0]->bufPlanes[0].buf,
                                                            (UInt8 *)pOutBufs->bufDesc[0]->bufPlanes[0].buf,
                                                            pInBufs->bufDesc[0]->bufPlanes[0].width,
                                                            pInBufs->bufDesc[0]->bufPlanes[0].height,
                                                            pInBufs->bufDesc[0]->bufPlanes[0].width,
                                                            pInBufs->bufDesc[0]->bufPlanes[0].width);
                }
                else {
                            status = AlgIvision_process(pRemapMergeObj->handle[channelId],
                                                     pInBufs,
                                                     pOutBufs,
                                                     (IVISION_InArgs *)pInArgs,
                                                     (IVISION_OutArgs *)pOutArgs
                                                    );
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
 * \brief This function save a raw frame into a fixed location
 *
 * \param   pObj
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergeSaveFrame
                                            (AlgorithmLink_RemapMergeObj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    if (pObj->algLinkCreateParams.allocBufferForRawDump)
    {
        pObj->saveFrame[0] = TRUE;
        pObj->saveFrame[1] = TRUE;

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function returns information about the saved raw frame
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergeGetSaveFrameStatus
                                (AlgorithmLink_RemapMergeObj *pObj,
                                AlgorithmLink_RemapMergeSaveFrameStatus *pPrm)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;

    pPrm->isSaveFrameComplete = FALSE;
    pPrm->bufAddr = NULL;
    pPrm->bufSize = 0;

    if (pObj->algLinkCreateParams.allocBufferForRawDump)
    {
        if(pObj->saveFrame[0]==FALSE && pObj->saveFrame[1]==FALSE)
        {
            pPrm->isSaveFrameComplete = TRUE;
            pPrm->bufAddr = (UInt32)pObj->saveFrameBufAddr;
            pPrm->bufSize = pObj->saveFrameBufSize;
        }

        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for color to gray algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_RemapMergeControl(void * pObj, void *pControlParams)
{
    AlgorithmLink_RemapMergeObj  * pRemapMergeObj;
    AlgorithmLink_ControlParams  * pAlgLinkControlPrm;
    AlgorithmLink_RemapMergeSaveFrameStatus *pSaveFrameStatus;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pRemapMergeObj = (AlgorithmLink_RemapMergeObj *)
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
            AlgorithmLink_RemapMergePrintStatistics(pObj, pRemapMergeObj);
            break;

        case REMAP_LINK_CMD_SAVE_FRAME:
            AlgorithmLink_RemapMergeSaveFrame(pRemapMergeObj);
            break;

        case REMAP_LINK_CMD_GET_SAVE_FRAME_STATUS:
            pSaveFrameStatus = (AlgorithmLink_RemapMergeSaveFrameStatus *)
                                    pControlParams;
            AlgorithmLink_RemapMergeGetSaveFrameStatus
                                            (pRemapMergeObj, pSaveFrameStatus);
            break;

        default:
            status = SYSTEM_LINK_STATUS_SOK;
            break;
    }


    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for color to gray algorithm link
 *
 *        For this algorithm there is no locking of frames and hence no
 *        flushing of frames. Also there are no any other functionality to be
 *        done at the end of execution of this algorithm. Hence this function
 *        is an empty function for this algorithm.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergeStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for Remap Merge algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergeDelete(void * pObj)
{
    UInt32 bufId, outBufferSize;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmLink_RemapMergeObj                * pRemapMergeObj;
    AlgorithmLink_RemapMergeCreateParams       * pLinkCreateParams;
    System_VideoFrameBuffer                 * pSystemVideoFrameBuffer;
    UInt32                                  channelId;

    pRemapMergeObj = (AlgorithmLink_RemapMergeObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pRemapMergeObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pLinkCreateParams = &pRemapMergeObj->algLinkCreateParams;

    /*
     * Free link buffers
     */
    for(channelId =0 ; channelId < pRemapMergeObj->numInputChannels; channelId++)
    {
        status = AlgIvision_delete(pRemapMergeObj->handle[channelId]);
        UTILS_assert(status == 0);

        for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
        {
            UTILS_assert(channelId < REMAPMERGE_MAX_CH_PER_OUT_QUE);
            pSystemVideoFrameBuffer     =   &pRemapMergeObj->videoFrames[channelId][bufId];
            outBufferSize = pRemapMergeObj->output_pitch*pRemapMergeObj->output_height;

            /*
             * Free'ing up of allocated buffers
             */
            status = Utils_memFree(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemVideoFrameBuffer->bufAddr[0],
                                    outBufferSize
                                   );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            status = Utils_memFree(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemVideoFrameBuffer->bufAddr[1],
                                    outBufferSize/2
                                   );
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        }
    }

   Utils_memFree(
                   UTILS_HEAPID_DDR_CACHED_LOCAL,
                   pRemapMergeObj,
                   sizeof(AlgorithmLink_RemapMergeObj)
                );


    /* Free up Extra frame for saving captured frame */
    if (pRemapMergeObj->algLinkCreateParams.allocBufferForRawDump)
    {
        /* Initialize this flag to 0 so that it can't be used */
        pRemapMergeObj->saveFrame[0] = FALSE;
        pRemapMergeObj->saveFrame[1] = FALSE;

        /* Free up the extra buffer memory space */
        status = Utils_memFree(
                    UTILS_HEAPID_DDR_CACHED_SR,
                    pRemapMergeObj->saveFrameBufAddr,
                    pRemapMergeObj->saveFrameBufSize
                    );
        UTILS_assert(status==0);
        pRemapMergeObj->saveFrameBufAddr = NULL;
    }
    return status;
}



/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pRemapMergeObj       [IN] Color to gray Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_RemapMergePrintStatistics(void *pObj,
                     AlgorithmLink_RemapMergeObj *pRemapMergeObj)
{

    UTILS_assert(NULL != pRemapMergeObj->linkStatsInfo);

    Utils_printLinkStatistics(&pRemapMergeObj->linkStatsInfo->linkStats, "ALG_REMAP_REMERGE", TRUE);

    Utils_printLatency("ALG_REMAP_REMERGE",
                       &pRemapMergeObj->linkStatsInfo->linkLatency,
                       &pRemapMergeObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}


/* Nothing beyond this point */
