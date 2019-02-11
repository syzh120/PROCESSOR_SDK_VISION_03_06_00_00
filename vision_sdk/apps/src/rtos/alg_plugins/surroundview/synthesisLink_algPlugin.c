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
 * \file synthesisLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for synthesis Link
 *
 * \version 0.0 (Oct 2013) : [PS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "synthesisLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/*******************************************************************************
 *  FUNCTION DECLARATION
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisLateCreate(void * pObj,
                        AlgorithmLink_SynthesisObj *pSynthesisObj);

extern  uWord16 GAlignLUT[];
extern unsigned char GSynthLUT_Default[];
extern const uWord32 g_synthlut_inbuilt_len;

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of synthesis algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_Synthesis_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_synthesisCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_synthesisProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_synthesisControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_synthesisStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_synthesisDelete;

#ifdef BUILD_DSP
    {
        void Utils_genSrvLutInit(void);

        Utils_genSrvLutInit();

        algId = ALGORITHM_LINK_DSP_ALG_SYNTHESIS;
    }
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for synthesis algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisCreate(void * pObj, void * pCreateParams)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       maxHeight;
    UInt32                       maxWidth;
    System_LinkInfo              prevLinkInfo;
    AlgorithmLink_SynthesisOutputQueId   outputQId;
    AlgorithmLink_SynthesisInputQueId    inputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       dataFormat;
    System_LinkChInfo          * pOutChInfo;
    System_LinkChInfo          * pPrevChInfo;
    UInt32                       prevChInfoFlags;

    AlgorithmLink_SynthesisObj           * pSynthesisObj;
    AlgorithmLink_SynthesisCreateParams  * pSynthesisLinkCreateParams;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    AlgorithmLink_InputQueueInfo         * pInputQInfo;

    pSynthesisLinkCreateParams =
        (AlgorithmLink_SynthesisCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pSynthesisObj = (AlgorithmLink_SynthesisObj *)
                                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    sizeof(AlgorithmLink_SynthesisObj), 64);
    UTILS_assert(pSynthesisObj!=NULL);
    UTILS_assert(ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS <=
        pSynthesisLinkCreateParams->numViews);

    pOutputQInfo = &pSynthesisObj->outputQInfo[0];
    pInputQInfo  = &pSynthesisObj->inputQInfo[0];

    AlgorithmLink_setAlgorithmParamsObj(pObj, pSynthesisObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pSynthesisObj->algLinkCreateParams),
           (void*)(pSynthesisLinkCreateParams),
           sizeof(AlgorithmLink_SynthesisCreateParams)
          );

    /*
     * Populating parameters corresponding to Q usage of synthesis
     * algorithm link
     */
    numInputQUsed     = ALGLINK_SYNTHESIS_IPQID_MAXIPQ;
    numOutputQUsed    = ALGLINK_SYNTHESIS_OPQID_MAXOPQ;
    numChannelsUsed   = 1;
    channelId         = 0;

    pInputQInfo[ALGLINK_SYNTHESIS_IPQID_MULTIVIEW].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pInputQInfo[ALGLINK_SYNTHESIS_IPQID_GALUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pInputQInfo[ALGLINK_SYNTHESIS_IPQID_PALUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_SYNTHESIS_OPQID_OPFRAME].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[ALGLINK_SYNTHESIS_OPQID_PASTATS].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo[ALGLINK_SYNTHESIS_OPQID_SGXLUT].qMode =
        ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    pOutputQInfo[ALGLINK_SYNTHESIS_OPQID_OPFRAME].queInfo.numCh = numChannelsUsed;
    pOutputQInfo[ALGLINK_SYNTHESIS_OPQID_PASTATS].queInfo.numCh = numChannelsUsed;
    pOutputQInfo[ALGLINK_SYNTHESIS_OPQID_SGXLUT].queInfo.numCh = numChannelsUsed;
    /*
     * Channel info population for output Q Id - ALGLINK_SYNTHESIS_OPQID_OPFRAME
     */
    outputQId = ALGLINK_SYNTHESIS_OPQID_OPFRAME;
    inputQId  = ALGLINK_SYNTHESIS_IPQID_MULTIVIEW;

    status = System_linkGetInfo(
                pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
                &prevLinkInfo);

    prevLinkQueId =
        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId;
    pPrevChInfo   =
        &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);

    maxHeight = pSynthesisObj->algLinkCreateParams.maxOutputHeight;
    maxWidth  = pSynthesisObj->algLinkCreateParams.maxOutputWidth;

    if(ALGLINK_SYNTHESIS_OUTPUTRES_2MP == pSynthesisObj->algLinkCreateParams.outputRes)
    {
        UTILS_assert(maxWidth  <= SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP);
    }
    else
    {
        UTILS_assert(maxWidth  <= SV_ALGLINK_OUTPUT_FRAME_WIDTH);
    }

    UTILS_assert(maxHeight <= SV_ALGLINK_OUTPUT_FRAME_HEIGHT);

    /*
     * Make pitch a multiple of ALGORITHMLINK_FRAME_ALIGN, so that if the frame
     * origin is aligned, then individual lines are also aligned
     * Also note that the pitch is kept same independent of width of
     * individual channels
     */
    pSynthesisObj->outPitch[0] = maxWidth; //SystemUtils_align(SV_ALGLINK_OUTPUT_FRAME_WIDTH,
                                           //ALGORITHMLINK_FRAME_ALIGN);
    pSynthesisObj->outPitch[1] = pSynthesisObj->outPitch[0];
    pSynthesisObj->outPitch[2] = pSynthesisObj->outPitch[0];

    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->startX = 0;
    pOutChInfo->startY = 0;
    pOutChInfo->width  = maxWidth;
    pOutChInfo->height = maxHeight;
    prevChInfoFlags    = pPrevChInfo->flags;
    pOutChInfo->flags  = prevChInfoFlags;

    dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

    if(dataFormat != SYSTEM_DF_YUV420SP_UV)
    {
      UTILS_assert(NULL);
    }

    pSynthesisObj->dataFormat = dataFormat;
    pSynthesisObj->inPitch[0] = pPrevChInfo->pitch[0];
    pSynthesisObj->inPitch[1] = pPrevChInfo->pitch[1];

    if(pSynthesisLinkCreateParams->svOutputMode != \
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC)
    {
        if((pPrevChInfo->width > pSynthesisObj->algLinkCreateParams.maxInputWidth)
           ||
           (pPrevChInfo->height > pSynthesisObj->algLinkCreateParams.maxInputHeight)
          )
        {
          UTILS_assert(NULL);
        }
    }
    else
    {
        /*
         *  For 3D LDC the synthesis input buffer size is the max size:
         */
        pSynthesisObj->algLinkCreateParams.maxInputWidth = pPrevChInfo->width;
        pSynthesisObj->algLinkCreateParams.maxInputHeight = pPrevChInfo->height;
    }

    pOutChInfo->pitch[0] = pSynthesisObj->outPitch[0];
    pOutChInfo->pitch[1] = pSynthesisObj->outPitch[1];
    pOutChInfo->pitch[2] = pSynthesisObj->outPitch[2];

    /*
     * Channel info population for output Q Id - ALGLINK_SYNTHESIS_OPQID_PASTATS
     */
    outputQId = ALGLINK_SYNTHESIS_OPQID_PASTATS;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;

    /*
     * Channel info population for output Q Id - ALGLINK_SYNTHESIS_OPQID_PASTATS
     */
    outputQId = ALGLINK_SYNTHESIS_OPQID_SGXLUT;
    channelId = 0;
    pOutChInfo = &(pOutputQInfo[outputQId].queInfo.chInfo[channelId]);
    pOutChInfo->flags = 0;

    /*
     * Initializations needed for book keeping of buffer handling.
     * Note that this needs to be called only after setting inputQMode and
     * outputQMode.
     */
    AlgorithmLink_queueInfoInit(pObj,
                                numInputQUsed,
                                pInputQInfo,
                                numOutputQUsed,
                                pOutputQInfo
                                );

    if (TRUE != pSynthesisLinkCreateParams->earlyCreate)
    {
        AlgorithmLink_synthesisLateCreate (pObj, pSynthesisObj);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Late Create Plugin for synthesis algorithm link
 *
 *        This function and the algorithm process function execute
 *        on same processor core. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisLateCreate(void * pObj,
                        AlgorithmLink_SynthesisObj *pSynthesisObj)
{
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    void                       * algHandle;
    Int32                        frameIdx, idx;
    AlgorithmLink_SynthesisCreateParams  * pSynthesisLinkCreateParams;
    SV_Synthesis_CreationParamsStruct    * pAlgCreateParams;
    AlgLink_MemRequests          memRequests;
    UInt32                                 memTabId;
    AlgorithmLink_SynthesisOutputQueId   outputQId;
    Int32                        channelId;
    System_Buffer              * pSystemBuffer;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;
    AlgorithmLink_OutputQueueInfo        * pOutputQInfo;
    UInt32                       maxHeight;
    UInt32                       metaBufSize;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    System_MetaDataBuffer      * pBlendLUTBuffer = NULL;
    AlgorithmLink_SynthesisInputQueId    inputQId;

    pSynthesisLinkCreateParams = (AlgorithmLink_SynthesisCreateParams *)
                                    &pSynthesisObj->algLinkCreateParams;
    pAlgCreateParams = &pSynthesisObj->algCreateParams;
    pOutputQInfo = &pSynthesisObj->outputQInfo[0];
    maxHeight = pSynthesisObj->algLinkCreateParams.maxOutputHeight;


    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */

    pAlgCreateParams->SVInCamFrmHeight =
        pSynthesisLinkCreateParams->maxInputHeight;
    pAlgCreateParams->SVInCamFrmWidth =
        pSynthesisLinkCreateParams->maxInputWidth;
    pAlgCreateParams->SVOutDisplayHeight =
        pSynthesisLinkCreateParams->maxOutputHeight;
    pAlgCreateParams->SVOutDisplayWidth =
        pSynthesisLinkCreateParams->maxOutputWidth;
    pAlgCreateParams->numCameras =
        pSynthesisLinkCreateParams->numViews;

    for (idx = 0; idx < pAlgCreateParams->numCameras; idx ++)
    {
        pAlgCreateParams->ldcFrmWidth[idx] =
            pSynthesisLinkCreateParams->ldcFrmWidth[idx];
        pAlgCreateParams->ldcFrmHeight[idx] =
            pSynthesisLinkCreateParams->ldcFrmHeight[idx];
    }

    /*
     * Block sizes need to be powers of 2
     */
    pAlgCreateParams->blockSizeV       = 40;
    pAlgCreateParams->blockSizeH       = 40;
    pAlgCreateParams->outputMode = pSynthesisLinkCreateParams->svOutputMode;
    pAlgCreateParams->enableCarOverlayInAlg =
                            pSynthesisLinkCreateParams->enableCarOverlayInAlg;

    pAlgCreateParams->subsampleratio   = 4;
    pAlgCreateParams->numColorChannels = 3;
    pAlgCreateParams->blendlen         = 10;
    pAlgCreateParams->seam_offset      = 0;//-100;
    //positive value to shift the seam horizontally and negative to shift it vertically

    if (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
    {
       pAlgCreateParams->subsampleratio   = 2;
    }
    else if (ALGORITHM_LINK_SRV_OUTPUT_3D_LDC ==
                                    pSynthesisLinkCreateParams->svOutputMode)
    {
        pAlgCreateParams->subsampleratio    = pSynthesisLinkCreateParams->subsampleratio;
        pAlgCreateParams->useUserBlendTable3DLDC = pSynthesisLinkCreateParams->useUserBlendTable3DLDC;
        pAlgCreateParams->numColorChannels  = 3;
        pAlgCreateParams->blendlen          = 12;
        pAlgCreateParams->seam_offset       = 20;
    }
    else
    {
       pAlgCreateParams->subsampleratio   = 4;
    }

    pAlgCreateParams->svCarBoxParams.CarBoxCenter_x =
        (pAlgCreateParams->SVOutDisplayWidth / 2);
    pAlgCreateParams->svCarBoxParams.CarBoxCenter_y =
        (pAlgCreateParams->SVOutDisplayHeight / 2);
    pAlgCreateParams->svCarBoxParams.CarBox_height =
            pSynthesisLinkCreateParams->carBoxHeight;
    pAlgCreateParams->svCarBoxParams.CarBox_width =
            pSynthesisLinkCreateParams->carBoxWidth;

    /*
     * First time call is just to get size for algorithm handle.
     *
     * TBD - Currently since memquery function is dependent on alg handle
     * space, there are two calls - first for alg handle and then for other
     * requests. In future, once this dependency is removed, there will be
     * only call of MemQuery
     */
    Alg_SynthesisMemQuery(pAlgCreateParams, &memRequests, 1);
    memTabId = 0;
    memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        memRequests.memTab[memTabId].size,
                                        memRequests.memTab[memTabId].alignment
                                        );
    UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

    /*
     * Memory allocations for the requests done by algorithm
     * For now treating all requests as persistent and allocating in DDR
     */
    Alg_SynthesisMemQuery(pAlgCreateParams, &memRequests, 0);
    for(memTabId = 1 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {
        /*
         * TBD: Temporary allocation of L2 memory directly.
         */
        if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
        {
           memRequests.memTab[memTabId].basePtr = (void *)
                Utils_memAlloc(
                        UTILS_HEAPID_L2_LOCAL,
                        memRequests.memTab[memTabId].size,
                        memRequests.memTab[memTabId].alignment
                        );
        }
        else
        {
        if(memRequests.memTab[memTabId].size > 0)
        {

        memRequests.memTab[memTabId].basePtr = Utils_memAlloc(
                                    UTILS_HEAPID_DDR_CACHED_SR,
                                    memRequests.memTab[memTabId].size,
                                    memRequests.memTab[memTabId].alignment);
        UTILS_assert(memRequests.memTab[memTabId].basePtr != NULL);

        }
    }

    }

    /*
     * Creation of output buffers for output Q of ALGLINK_SYNTHESIS_OPQID_OPFRAME
     *  - Connecting video frame buffer to system buffer payload
     *  - Memory allocation for Luma and Chroma buffers (Assume 420 SP format)
     *  - Put the buffer into empty queue
     */
    /* Set the second output Q only incase of 2D SRV mode */
    if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
         (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
        (ALGORITHM_LINK_SRV_OUTPUT_3D_LDC == pSynthesisLinkCreateParams->svOutputMode))
    {
        outputQId = ALGLINK_SYNTHESIS_OPQID_OPFRAME;
        channelId = 0;

        for(frameIdx = 0;
            frameIdx < pSynthesisObj->algLinkCreateParams.numOutputFrames;
            frameIdx++)
        {
            pSystemBuffer           =
                                 &(pSynthesisObj->buffers[outputQId][frameIdx]);
            pSystemVideoFrameBuffer =
                                 &(pSynthesisObj->videoFrames[frameIdx]);

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSystemBuffer->payload     = pSystemVideoFrameBuffer;
            pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
            pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
            pSystemBuffer->chNum       = channelId;

            memcpy((void *)&pSystemVideoFrameBuffer->chInfo,
                   (void *)&pOutputQInfo[outputQId].queInfo.chInfo[channelId],
                   sizeof(System_LinkChInfo));

            /*
             * Buffer allocation done for maxHeight, maxWidth and for 420SP format
             */
            pSystemVideoFrameBuffer->bufAddr[0] = Utils_memAlloc(
                                           UTILS_HEAPID_DDR_CACHED_SR,
                                           (SV_ALGLINK_OUTPUT_FRAME_HEIGHT*
                                           (pSynthesisObj->outPitch[0])*
                                           (1.5)),
                                           ALGORITHMLINK_FRAME_ALIGN);

            /*
             * Carving out memory pointer for chroma which will get used in case of
             * SYSTEM_DF_YUV420SP_UV
             */
            pSystemVideoFrameBuffer->bufAddr[1] = (void*)(
                (UInt32) pSystemVideoFrameBuffer->bufAddr[0] +
                (UInt32)(maxHeight*(pSynthesisObj->outPitch[0]))
                );

            UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);

            AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
        }
    }

    /*
     * For first frame synthesis PALUT will not be available from PA Link.
     * So a temporary buffer space is allocated just for first frame synthesis
     */
    //metaBufSize = SV_ALGLINK_PALUT_SIZE;
    metaBufSize = sizeof(PAlignOutStruct);

    pSynthesisObj->pLinkStaticPALUT = (UInt8 *) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    metaBufSize,
                                                    ALGORITHMLINK_FRAME_ALIGN);

    UTILS_assert(pSynthesisObj->pLinkStaticPALUT != NULL);

    /*
     * Creation of output buffers for output Q of ALGLINK_SYNTHESIS_OPQID_PASTATS
     *  - Connecting metadata buffer to system buffer payload
     *  - Memory allocation for buffers
     *  - Put the buffer into empty queue
     */
    outputQId = ALGLINK_SYNTHESIS_OPQID_PASTATS;
    channelId = 0;

    for(frameIdx = 0;
        frameIdx < pSynthesisObj->algLinkCreateParams
                    .numPhotometricStatisticsTables;
        frameIdx++)
    {
        pSystemBuffer         =
                             &(pSynthesisObj->buffers[outputQId][frameIdx]);
        pSystemMetaDataBuffer =
                             &(pSynthesisObj->photoAlignStats[frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemMetaDataBuffer;
        pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
        pSystemBuffer->chNum       = channelId;

        /*
         * Buffer allocation done considering following factors -
         *  - Sub sampled height
         *  - Sub sampled width
         *  - Number of planes (3)
         *  - Number of non-overlapping view pairs
         *    (Ex: For 4 views case, 1-3 and 2-4 are non overlapping view pairs)
         * An additional 256 bytes for any round off etc during division etc..
         */
        if(ALGLINK_SYNTHESIS_OUTPUTRES_2MP == pSynthesisObj->algLinkCreateParams.outputRes)
        {
            metaBufSize =
                (SV_ALGLINK_OUTPUT_FRAME_HEIGHT / pAlgCreateParams->blockSizeV) *
                (SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP / pAlgCreateParams->blockSizeH) *
                pAlgCreateParams->numColorChannels *
                PAlignStat_BitPerEntry *
                2
                + 256  + 64U
                ;
        }
        else
        {
            metaBufSize =
                (SV_ALGLINK_OUTPUT_FRAME_HEIGHT / pAlgCreateParams->blockSizeV) *
                (SV_ALGLINK_OUTPUT_FRAME_WIDTH / pAlgCreateParams->blockSizeH) *
                pAlgCreateParams->numColorChannels *
                PAlignStat_BitPerEntry *
                2
                + 256  + 64U
                ;
        }

        //metaBufSize =
        //            (SV_ALGLINK_OUTPUT_FRAME_HEIGHT / pAlgCreateParams->blockSizeV) *
        //            (SV_ALGLINK_OUTPUT_FRAME_WIDTH / pAlgCreateParams->blockSizeH) *
        //            3 *
        //            (SV_ALGLINK_MAX_NUM_VIEWS/2)
        //            + 256
        //            ;

        pSystemMetaDataBuffer->numMetaDataPlanes = 1;
        pSystemMetaDataBuffer->bufAddr[0] =  Utils_memAlloc(
                                                UTILS_HEAPID_DDR_CACHED_SR,
                                                metaBufSize,
                                                ALGORITHMLINK_FRAME_ALIGN);
        pSystemMetaDataBuffer->metaBufSize[0]    = metaBufSize;
        pSystemMetaDataBuffer->metaFillLength[0] = metaBufSize;
        pSystemMetaDataBuffer->flags             = 0;

        UTILS_assert(pSystemMetaDataBuffer->bufAddr[0] != NULL);

        AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
    }

    /*
     *  Don't allocate SGX LUT for 3D LDC SRV:
     */
    if(pSynthesisLinkCreateParams->svOutputMode != \
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC)
    {
        /*
         * Creation of output buffers for output Q of ALGLINK_SYNTHESIS_OPQID_SGXLUT
         *  - Connecting metadata buffer to system buffer payload
         *  - Memory allocation for buffers
         *  - Put the buffer into empty queue
         */

        outputQId = ALGLINK_SYNTHESIS_OPQID_SGXLUT;
        channelId = 0;

        for(frameIdx = 0;
            frameIdx < pSynthesisObj->algLinkCreateParams
                        .numSgxBlendLUTables;
            frameIdx++)
        {
            pSystemBuffer         =
                                 &(pSynthesisObj->buffers[outputQId][frameIdx]);
            pSystemMetaDataBuffer =
                                 &(pSynthesisObj->opSgxBlendLUT[frameIdx]);

            /*
             * Properties of pSystemBuffer, which do not get altered during
             * run time (frame exchanges) are initialized here
             */
            pSystemBuffer->payload     = pSystemMetaDataBuffer;
            pSystemBuffer->payloadSize = sizeof(System_MetaDataBuffer);
            pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_METADATA;
            pSystemBuffer->chNum       = channelId;

            /*
             * Buffer allocation done considering following factors -
             *  - Sub sampled height
             *  - Sub sampled width
             *  - Number of planes (3)
             *  - Number of non-overlapping view pairs
             *    (Ex: For 4 views case, 1-3 and 2-4 are non overlapping view pairs)
             * An additional 256 bytes for any round off etc during division etc..
             */
            if(ALGLINK_SYNTHESIS_OUTPUTRES_2MP == pSynthesisObj->algLinkCreateParams.outputRes)
            {
                metaBufSize = (SV_ALGLINK_OUTPUT_FRAME_HEIGHT * \
                           SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP * 4 );
            }
            else
            {
                metaBufSize = (SV_ALGLINK_OUTPUT_FRAME_HEIGHT * \
                           SV_ALGLINK_OUTPUT_FRAME_WIDTH * 4 );
            }

            pSystemMetaDataBuffer->numMetaDataPlanes = 1;
            pSystemMetaDataBuffer->bufAddr[0] =  Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    metaBufSize,
                                                    ALGORITHMLINK_FRAME_ALIGN);
            pSystemMetaDataBuffer->metaBufSize[0]    = metaBufSize;
            pSystemMetaDataBuffer->metaFillLength[0] = metaBufSize;
            pSystemMetaDataBuffer->flags             = 0;

            UTILS_assert(pSystemMetaDataBuffer->bufAddr[0] != NULL);

            if (frameIdx == 0)
            {
                pSynthesisObj->sysBufferBlendLUT = pSystemBuffer;
                pBlendLUTBuffer = (System_MetaDataBuffer*) pSystemBuffer->payload;
            }

            /* Put in the Empty output Q only incase of 3D SRV mode */
            if (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
            {
                AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
            }
        }

        UTILS_assert(pBlendLUTBuffer != NULL);
    }

    pAlgCreateParams->useSuppliedLUT = pSynthesisLinkCreateParams->useSuppliedLUT;
    pAlgCreateParams->synthLUTPtr = pSynthesisLinkCreateParams->synthLUTPtr;
    pAlgCreateParams->synthLUTSize = pSynthesisLinkCreateParams->synthLUTSize;

    /* Do Cache Invalidate on the user supplied LUT buffer before use */
    if((pAlgCreateParams->useSuppliedLUT==TRUE) &&
       (pAlgCreateParams->synthLUTPtr!=NULL)){
        Cache_inv(pAlgCreateParams->synthLUTPtr,
             pAlgCreateParams->synthLUTSize,
             Cache_Type_ALLD,
             TRUE);
    }

    pAlgCreateParams->saveCalculatedLUT = pSynthesisLinkCreateParams->saveCalculatedLUT;

    /* Do Cache Invalidate on the user supplied LUT buffer before use */
    if((pAlgCreateParams->useSuppliedLUT==TRUE) &&
       (pAlgCreateParams->synthLUTPtr!=NULL)){
        Cache_inv(pAlgCreateParams->synthLUTPtr,
             pAlgCreateParams->synthLUTSize,
             Cache_Type_ALLD,
             TRUE);
    }

    /* In case of LDC 3D SRV, the memory for the blend table is allocated above
        use that, instead of the memory allocated to SGXLUT.
        This is bug in case of LDC SRV : fix it */
    if (ALGORITHM_LINK_SRV_OUTPUT_3D_LDC ==
                                    pSynthesisLinkCreateParams->svOutputMode)
    {
        memTabId = 1U;
        algHandle = Alg_SynthesisCreate(pAlgCreateParams, &memRequests,
                                    memRequests.memTab[memTabId].basePtr);
    }
    else
    {
        algHandle = Alg_SynthesisCreate(pAlgCreateParams, &memRequests,
                                    pBlendLUTBuffer->bufAddr[0]);
    }

    UTILS_assert(algHandle != NULL);

    pSynthesisObj->algHandle = algHandle;

    if(pSynthesisLinkCreateParams->svOutputMode != \
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC)
    {
        /*
         *  Blend Buffer is not allocated for 3D LDC SRV
         */
        Cache_wb(pBlendLUTBuffer->bufAddr[0],
                 pBlendLUTBuffer->metaBufSize[0],
                 Cache_Type_ALLD,
                 TRUE);
    }

    if((pAlgCreateParams->saveCalculatedLUT==TRUE) &&
       (pAlgCreateParams->synthLUTPtr!=NULL)){
        Cache_wb(pAlgCreateParams->synthLUTPtr,
             pAlgCreateParams->synthLUTSize,
             Cache_Type_ALLD,
                 TRUE);
    }

    /*
     * Creation of local input Qs for ALGLINK_SYNTHESIS_IPQID_MULTIVIEW and
     * ALGLINK_SYNTHESIS_IPQID_PALUT.
     * For ALGLINK_SYNTHESIS_IPQID_GALUT, always just one entry is kept.
     */
    inputQId = ALGLINK_SYNTHESIS_IPQID_MULTIVIEW;
    status  = Utils_queCreate(&(pSynthesisObj->localInputQ[inputQId].queHandle),
                               SYNTHESIS_LINK_MAX_LOCALQUEUELENGTH,
                              (pSynthesisObj->localInputQ[inputQId].queMem),
                               UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    inputQId = ALGLINK_SYNTHESIS_IPQID_PALUT;
    status  = Utils_queCreate(&(pSynthesisObj->localInputQ[inputQId].queHandle),
                               SYNTHESIS_LINK_MAX_LOCALQUEUELENGTH,
                              (pSynthesisObj->localInputQ[inputQId].queMem),
                               UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pSynthesisObj->frameDropCounter          = 0;

    pSynthesisObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj),"ALG_SYNTHESIS");
    UTILS_assert(NULL != pSynthesisObj->linkStatsInfo);

    pSynthesisObj->numInputChannels = 1;

    pSynthesisObj->isFirstFrameRecv   = FALSE;
    pSynthesisObj->receivedGALUTFlag  = FALSE;
    pSynthesisObj->isFirstOPGenerated = FALSE;
    pSynthesisObj->isSGXBlendLUTOPGenerated = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for synthesis algorithm link
 *
 *        This function and the algorithm process function execute
 *        on same processor core. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisProcess(void * pObj)
{
    AlgorithmLink_SynthesisObj * pSynthesisObj;
    void                       * algHandle;
    AlgorithmLink_SynthesisInputQueId    inputQId;
    AlgorithmLink_SynthesisOutputQueId   outputQId;
    UInt32                       channelId = 0;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    UInt32                       viewId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferInput;
    System_Buffer              * pSystemBufferMultiview;
    System_Buffer              * pSystemBufferPALUT;
    System_Buffer              * pSysBufferPAStats;
    System_Buffer              * pSysBufferOutput;
    System_Buffer              * pSysBufferBlendLUT;
    Bool                         bufDropFlag;
    Bool                         isProcessCallDoneFlag;
    System_MetaDataBuffer      * pPAStatsBuffer;
    System_MetaDataBuffer      * pPALUTBuffer;
    System_MetaDataBuffer      * pGALUTBuffer;
    System_MetaDataBuffer      * pBlendLUTBuffer;
    System_VideoFrameBuffer    * pVideoOutputBuffer;
    void                       * inPAlignLUTPtr;
    PAlignOutStruct            * PAlignOutStruct_ptr;
    Uint32                       i,j;
    Bool                         processFrm;
    Ptr                          gaLutAddr;

    System_VideoFrameCompositeBuffer     * pCompositeBuffer;
    AlgorithmLink_SynthesisCreateParams  * pSynthesisLinkCreateParams;
    System_LinkStatistics      * linkStatsInfo;
    System_VideoFrameCompositeBuffer compositeBufferTmp;
    UInt32 offsetY, offsetUV;

    pSynthesisObj = (AlgorithmLink_SynthesisObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pSynthesisObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle                  = pSynthesisObj->algHandle;
    pSynthesisLinkCreateParams = (AlgorithmLink_SynthesisCreateParams *)
                                    &pSynthesisObj->algLinkCreateParams;

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_SYNTHESIS_IPQID_MULTIVIEW and queue them up locally.
     */
    inputQId = ALGLINK_SYNTHESIS_IPQID_MULTIVIEW;

    System_getLinksFullBuffers(
        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufList);

    if(inputBufList.numBuf)
    {
        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {
            pSysBufferInput = inputBufList.buffers[bufId];

            /*TBD: Check for parameter correctness. If in error, return input*/

            if (pSysBufferInput != NULL)
            {
                status = Utils_quePut(
                            &(pSynthesisObj->localInputQ[inputQId].queHandle),
                            pSysBufferInput,
                            BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }

    /*
     * Get Input buffers from previous link for
     * Qid = ALGLINK_SYNTHESIS_IPQID_PALUT and queue them up locally.
     */
    /* Set the second output Q only incase of 2D SRV mode */
    if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
         (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
        (ALGORITHM_LINK_SRV_OUTPUT_3D_LDC == pSynthesisLinkCreateParams->svOutputMode))
    {
        inputQId = ALGLINK_SYNTHESIS_IPQID_PALUT;

        System_getLinksFullBuffers(
            pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
            pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
            &inputBufList);

        if(inputBufList.numBuf)
        {
            for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
            {
                pSysBufferInput = inputBufList.buffers[bufId];
                /*TBD: Check for parameter correctness. If in error, return input*/
                status = Utils_quePut(
                            &(pSynthesisObj->localInputQ[inputQId].queHandle),
                            pSysBufferInput,
                            BSP_OSAL_NO_WAIT);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }
    }

    if ((pSynthesisLinkCreateParams->svOutputMode !=
                                            ALGORITHM_LINK_SRV_OUTPUT_2D_LDC) &&
        (pSynthesisLinkCreateParams->svOutputMode !=
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
    {
        /*
         * Get Input buffers from previous link for
         * Qid = ALGLINK_SYNTHESIS_IPQID_GALUT and store latest copy locally.
         */
        inputQId = ALGLINK_SYNTHESIS_IPQID_GALUT;

        System_getLinksFullBuffers(
            pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
            pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
            &inputBufList);

        if(inputBufList.numBuf)
        {
            for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
            {
                /*
                 * At any point in time, Synthesis link will hold only one GA LUT.
                 * So whenever GA LUT is received, the previously received one
                 * will be released and the newly received one will be archived.
                 */
                if(pSynthesisObj->receivedGALUTFlag == TRUE)
                {
                    inputBufListReturn.numBuf     = 1;
                    inputBufListReturn.buffers[0] = pSynthesisObj->sysBufferGALUT;
                    bufDropFlag = FALSE;

                    AlgorithmLink_releaseInputBuffer(
                        pObj,
                        inputQId,
                        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
                        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                        &inputBufListReturn,
                        &bufDropFlag);
                    pSynthesisObj->receivedGALUTFlag = FALSE;
                }

                pSynthesisObj->sysBufferGALUT = inputBufList.buffers[bufId];
                /*TBD: Check for parameter correctness. If in error, return input*/
                pSynthesisObj->receivedGALUTFlag = TRUE;
            }
        }
    }


    if(pSynthesisObj->isFirstFrameRecv==FALSE)
    {
        pSynthesisObj->isFirstFrameRecv = TRUE;

        Utils_resetLinkStatistics(
            &linkStatsInfo->linkStats,
            pSynthesisObj->numInputChannels,
            1);

        Utils_resetLatency(&linkStatsInfo->linkLatency);
        Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        //Task_sleep(100);
    }

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;

    processFrm = (Bool)FALSE;
    if ((pSynthesisLinkCreateParams->svOutputMode != ALGORITHM_LINK_SRV_OUTPUT_2D_LDC) &&
        (pSynthesisLinkCreateParams->svOutputMode != ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
    {
        processFrm = pSynthesisObj->receivedGALUTFlag;
    }
    else
    {
        processFrm = (Bool)TRUE;
    }

    if(pSynthesisLinkCreateParams->useStaticGALut == TRUE)
    {
        processFrm = (Bool) TRUE;
    }

    /*
     * Continuous loop to perform synthesis as long as input and output
     * buffers are available. Exit this loop, when, if for some reason
     * the alg process call is not done (tracked via isProcessCallDoneFlag).
     */
    while(1)
    {

    isProcessCallDoneFlag = FALSE;
    /*
     * Checking if all the inputs are available. For first frame, PALUT is
     * not expected to come. This is tracked via isFirstOPGenerated.
     */
    if(processFrm == TRUE
            &&
      Utils_queGetQueuedCount(
      &(pSynthesisObj->localInputQ[ALGLINK_SYNTHESIS_IPQID_MULTIVIEW].queHandle))>0
            &&
      ((Utils_queGetQueuedCount(
      &(pSynthesisObj->localInputQ[ALGLINK_SYNTHESIS_IPQID_PALUT].queHandle))>0
       ||
       (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D))
       ||
       pSynthesisObj->isFirstOPGenerated == FALSE)
     )
     {

      pVideoOutputBuffer = NULL;
      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
          (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
        outputQId = ALGLINK_SYNTHESIS_OPQID_OPFRAME;
        channelId = 0;
        status = AlgorithmLink_getEmptyOutputBuffer(pObj,
                                                    outputQId,
                                                    channelId,
                                                    &pSysBufferOutput);

        if(status != SYSTEM_LINK_STATUS_SOK)
        {
          linkStatsInfo->linkStats.outBufErrorCount++;
          break;
        }
        UTILS_assert(pSysBufferOutput != NULL);
        pVideoOutputBuffer = (System_VideoFrameBuffer*)pSysBufferOutput->payload;
      }

      outputQId = ALGLINK_SYNTHESIS_OPQID_PASTATS;
      channelId = 0;
      status = AlgorithmLink_getEmptyOutputBuffer(pObj,
                                                  outputQId,
                                                  channelId,
                                                  &pSysBufferPAStats);

      if(status != SYSTEM_LINK_STATUS_SOK)
      {
        if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
            (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
        {
            AlgorithmLink_putEmptyOutputBuffer(pObj,
                                           ALGLINK_SYNTHESIS_OPQID_OPFRAME,
                                           pSysBufferOutput);
        }
        linkStatsInfo->linkStats.outBufErrorCount++;
        break;
      }

      UTILS_assert(pSysBufferPAStats != NULL);
      pPAStatsBuffer = (System_MetaDataBuffer*)pSysBufferPAStats->payload;

      /*
       * Reaching here means output buffers are available.
       * Hence getting inputs from local Queus
       */
      status = Utils_queGet(
                &(pSynthesisObj->localInputQ[ALGLINK_SYNTHESIS_IPQID_MULTIVIEW].
                    queHandle),
                (Ptr *)&pSystemBufferMultiview,
                1,
                BSP_OSAL_NO_WAIT);

      UTILS_assert(pSystemBufferMultiview != NULL);

      pCompositeBuffer = (System_VideoFrameCompositeBuffer *)
                            (pSystemBufferMultiview->payload);

      inPAlignLUTPtr = NULL;
      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
          (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
        if(pSynthesisObj->isFirstOPGenerated == TRUE)
        {
          status = Utils_queGet(
                      &(pSynthesisObj->localInputQ[ALGLINK_SYNTHESIS_IPQID_PALUT].
                          queHandle),
                      (Ptr *)&pSystemBufferPALUT,
                      1,
                      BSP_OSAL_NO_WAIT);
          pPALUTBuffer = (System_MetaDataBuffer *)(pSystemBufferPALUT->payload);
          inPAlignLUTPtr = pPALUTBuffer->bufAddr[0];
        }
        else
        {
           /*
            * For first frame case temporary memory buffer is provided.
            * TBD - PA LUT buffer is uninitialized.
            * Currently nothing is initialized since only first frame looks
            * corrupted.
            */
           PAlignOutStruct_ptr = (PAlignOutStruct *) pSynthesisObj->pLinkStaticPALUT;

           //Initialization
           for(i=0;i<(MAX_NUM_VIEWS*NUM_MAX_COLORPLANES);i++){
               PAlignOutStruct_ptr->PAlignOut_Gain[i]=256;
           }
           for(i=0;i<(MAX_NUM_VIEWS*NUM_MAX_COLORPLANES);i++){
               for(j=0;j<256;j++){
                   PAlignOutStruct_ptr->PAlignOut_LUT[(i*256)+j]=j;
               }
           }
           inPAlignLUTPtr = (UInt32 *) PAlignOutStruct_ptr;
        }
      }

      if ((pSynthesisLinkCreateParams->svOutputMode != ALGORITHM_LINK_SRV_OUTPUT_2D_LDC) &&
          (pSynthesisLinkCreateParams->svOutputMode != ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
            if(pSynthesisLinkCreateParams->useStaticGALut == TRUE)
            {
                gaLutAddr = GAlignLUT;
            }

            else
            {
                pGALUTBuffer = (System_MetaDataBuffer *)pSynthesisObj->
                    sysBufferGALUT->payload;
                gaLutAddr = pGALUTBuffer->bufAddr[0U];
            }
      }
      else
      {
          gaLutAddr = NULL;
      }

      for(viewId = 0; viewId < SV_ALGLINK_MAX_NUM_VIEWS ;viewId++)
      {
        Cache_inv(pCompositeBuffer->bufAddr[0][viewId],
         (pSynthesisLinkCreateParams->maxInputWidth*
            pSynthesisLinkCreateParams->maxInputHeight),
         Cache_Type_ALLD, TRUE);
        Cache_inv(pCompositeBuffer->bufAddr[1][viewId],
         ((pSynthesisLinkCreateParams->maxInputWidth*
            pSynthesisLinkCreateParams->maxInputHeight)/2),
         Cache_Type_ALLD, TRUE);
      }

      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
          (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
          pSysBufferOutput->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
          pSysBufferOutput->frameId = pSystemBufferMultiview->frameId;
          pSysBufferOutput->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
      }

      pSysBufferPAStats->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
      pSysBufferPAStats->frameId = pSystemBufferMultiview->frameId;
      pSysBufferPAStats->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

      if (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
      {
          pSynthesisObj->isSGXBlendLUTOPGenerated = FALSE;
          outputQId = ALGLINK_SYNTHESIS_OPQID_SGXLUT;
          channelId = 0;
          status = AlgorithmLink_getEmptyOutputBuffer(pObj,
                                                      outputQId,
                                                      channelId,
                                                      &pSysBufferBlendLUT);

          if ((status == SYSTEM_LINK_STATUS_SOK) && (pSysBufferBlendLUT != NULL))
          {
              pSynthesisObj->sysBufferBlendLUT = pSysBufferBlendLUT;
              pSynthesisObj->isSGXBlendLUTOPGenerated = TRUE;

              pSysBufferBlendLUT->srcTimestamp = pSystemBufferMultiview->srcTimestamp;
              pSysBufferBlendLUT->frameId = pSystemBufferMultiview->frameId;
              pSysBufferBlendLUT->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();
          }
      }

      if(pSynthesisLinkCreateParams->svOutputMode != \
                                        ALGORITHM_LINK_SRV_OUTPUT_3D_LDC)
      {
          /*
           *    For 3D LDC don't validate the blend buffer address since it
           *    is not allocated:
           */
          pSysBufferBlendLUT = pSynthesisObj->sysBufferBlendLUT;
          pBlendLUTBuffer = (System_MetaDataBuffer*) pSysBufferBlendLUT->payload;
          UTILS_assert(pBlendLUTBuffer != NULL);
      }

        /* In case SRV 3D based on LDC is used, check if we require to update
            the view point params */
        if (ALGORITHM_LINK_SRV_OUTPUT_3D_LDC ==
                                    pSynthesisLinkCreateParams->svOutputMode)
        {
            UInt32                       idx;
            SV_Synthesis_ControlParams   ctrlPrm;
            SV_Synthesis_InputFrameCfg   synthInFrmSize;
            AlgorithmLink_SrvCommonViewPointParams *pViewPrm;

            pViewPrm = (AlgorithmLink_SrvCommonViewPointParams *)
                            pCompositeBuffer->metaBufAddr[0U];

            if (NULL != pViewPrm)
            {
                Cache_inv(pViewPrm,
                            sizeof (AlgorithmLink_SrvCommonViewPointParams),
                            Cache_Type_ALLD, TRUE);

                Cache_inv(pViewPrm->carImgPtr, pViewPrm->sizeOfcarImg,
                            Cache_Type_ALLD, TRUE);

                viewId = pViewPrm->viewPointId;

                ctrlPrm.cmd = SV_SYNTHESIS_CMD_UPDATE_LDC_WIDTH_HEIGHT;
                ctrlPrm.cmdArgs = &synthInFrmSize;

                for (idx = 0U; idx < ALGLINK_SRV_COMMON_MAX_CAMERAS;
                                idx++)
                {
                    synthInFrmSize.width[idx] = pViewPrm->ldcOutFrameWidth[idx];
                    synthInFrmSize.height[idx] =
                                               pViewPrm->ldcOutFrameHeight[idx];

                    synthInFrmSize.padX[idx] = (UInt16)
                                                pViewPrm->ldcOutPadX[idx];
                    synthInFrmSize.padY[idx] = (UInt16)
                                                pViewPrm->ldcOutPadY[idx];

                    synthInFrmSize.chMap[idx] = pViewPrm->remappedCh[idx];

                    synthInFrmSize.quadrantStartX[idx] = pViewPrm->quadrantStartX[idx];
                    synthInFrmSize.quadrantEndX[idx] = pViewPrm->quadrantEndX[idx];
                    synthInFrmSize.quadrantStartY[idx] = pViewPrm->quadrantStartY[idx];
                    synthInFrmSize.quadrantEndY[idx] = pViewPrm->quadrantEndY[idx];
                }
                synthInFrmSize.carPosX = pViewPrm->carPosX;
                synthInFrmSize.carPosY = pViewPrm->carPosY;
                synthInFrmSize.carSizeX = pViewPrm->carBoxWidth;
                synthInFrmSize.carSizeY = pViewPrm->carBoxHeight;
                synthInFrmSize.carImgPtr = pViewPrm->carImgPtr;
                UTILS_assert(NULL != synthInFrmSize.carImgPtr);
                synthInFrmSize.sizeOfcarImg = pViewPrm->sizeOfcarImg;

                synthInFrmSize.userBlendTableAddr = pViewPrm->blendTableAddr;

                status = Alg_SynthesisControl(algHandle, &ctrlPrm);
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
            }
        }

        compositeBufferTmp = *pCompositeBuffer;
        if ((compositeBufferTmp.chInfo.startX!=0) || (compositeBufferTmp.chInfo.startY!=0))
        {
            offsetY  = compositeBufferTmp.chInfo.pitch[0]*compositeBufferTmp.chInfo.startY
                     + compositeBufferTmp.chInfo.startX;
            offsetUV = compositeBufferTmp.chInfo.pitch[1]*compositeBufferTmp.chInfo.startY/2
                     + compositeBufferTmp.chInfo.startX;
            compositeBufferTmp.bufAddr[0][0] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][0] + offsetY);
            compositeBufferTmp.bufAddr[0][1] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][1] + offsetY);
            compositeBufferTmp.bufAddr[0][2] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][2] + offsetY);
            compositeBufferTmp.bufAddr[0][3] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[0][3] + offsetY);
            compositeBufferTmp.bufAddr[1][0] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][0] + offsetUV);
            compositeBufferTmp.bufAddr[1][1] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][1] + offsetUV);
            compositeBufferTmp.bufAddr[1][2] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][2] + offsetUV);
            compositeBufferTmp.bufAddr[1][3] =
                (UInt8 *) ((UInt32)compositeBufferTmp.bufAddr[1][3] + offsetUV);
        }

        /* The synthesis parameters are collected together in a single structure */
        /* This is workaround for the DSP MDMA error */
        /* TBD: Root cause the MDMD error */
        {
            SV_Synthesis_ProcessPrm synthProcPrm;

            synthProcPrm.svHandle = algHandle;
            synthProcPrm.pCompositeBuffer = &compositeBufferTmp;
            synthProcPrm.pVideoOutputBuffer = pVideoOutputBuffer;
            synthProcPrm.inPitch = &pSynthesisObj->inPitch[0];
            synthProcPrm.outPitch = &pSynthesisObj->outPitch[0];
            synthProcPrm.inGALUTPtr = gaLutAddr;
            synthProcPrm.inPAlignLUTPtr = inPAlignLUTPtr;
            synthProcPrm.outStatLUTPtr = pPAStatsBuffer->bufAddr[0];
            synthProcPrm.outBlendLUTPtr = pBlendLUTBuffer->bufAddr[0];
            synthProcPrm.dataFormat = pSynthesisObj->dataFormat;
            synthProcPrm.synthesisMode = pSynthesisLinkCreateParams->synthesisMode;

            status = Alg_SynthesisProcess(&synthProcPrm);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }

      /*
       * Putting filled buffer into output full buffer for
       * outputQId = ALGLINK_SYNTHESIS_OPQID_SGXLUT
       */
      if ((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D)
          && (pSynthesisObj->isSGXBlendLUTOPGenerated == TRUE))
      {
          Cache_wb(pBlendLUTBuffer->bufAddr[0],
                   pBlendLUTBuffer->metaBufSize[0],
                   Cache_Type_ALLD,
                   TRUE);

          Utils_updateLatency(&linkStatsInfo->linkLatency,
                              pSysBufferBlendLUT->linkLocalTimestamp);
          Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                              pSysBufferBlendLUT->srcTimestamp);

          outputQId = ALGLINK_SYNTHESIS_OPQID_SGXLUT;
          status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                        outputQId,
                                                        pSysBufferBlendLUT);

          UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

          /*
           * Informing next link that a new data has peen put for its
           * processing
           */
          System_sendLinkCmd(
            pSynthesisLinkCreateParams->outQueParams[outputQId].nextLink,
            SYSTEM_CMD_NEW_DATA,
            NULL);

          outputQId                      = ALGLINK_SYNTHESIS_OPQID_SGXLUT;
          outputBufListReturn.numBuf     = 1;
          outputBufListReturn.buffers[0] = pSysBufferBlendLUT;
          AlgorithmLink_releaseOutputBuffer(pObj,
                                            outputQId,
                                            &outputBufListReturn);
      }

      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
          Cache_wb(pVideoOutputBuffer->bufAddr[0],
                   (pSynthesisObj->algLinkCreateParams.maxOutputWidth *
                    pSynthesisObj->algLinkCreateParams.maxOutputHeight),
                   Cache_Type_ALLD,
                   TRUE);
          Cache_wb(pVideoOutputBuffer->bufAddr[1],
                   (pSynthesisObj->algLinkCreateParams.maxOutputWidth *
                    pSynthesisObj->algLinkCreateParams.maxOutputHeight)/2,
                   Cache_Type_ALLD,
                   TRUE);

          Utils_updateLatency(&linkStatsInfo->linkLatency,
                              pSysBufferOutput->linkLocalTimestamp);
          Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                pSysBufferOutput->srcTimestamp);
      }

      Cache_wb(pPAStatsBuffer->bufAddr[0],
               pPAStatsBuffer->metaBufSize[0],
               Cache_Type_ALLD,
               TRUE);

      Utils_updateLatency(&linkStatsInfo->linkLatency,
                          pSysBufferPAStats->linkLocalTimestamp);
      Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                          pSysBufferPAStats->srcTimestamp);

      isProcessCallDoneFlag = TRUE;

      if (pSystemBufferMultiview != NULL)
      {
        linkStatsInfo->linkStats.chStats
                    [pSystemBufferMultiview->chNum].inBufProcessCount++;
        linkStatsInfo->linkStats.chStats
                    [pSystemBufferMultiview->chNum].outBufCount[0]++;
      }

      /*
       * Putting filled buffer into output full buffer for
       * outputQId = ALGLINK_SYNTHESIS_OPQID_OPFRAME
       */
      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
          outputQId = ALGLINK_SYNTHESIS_OPQID_OPFRAME;
          status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                        outputQId,
                                                        pSysBufferOutput);

          UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

          /*
           * Informing next link that a new data has peen put for its
           * processing
           */
          System_sendLinkCmd(
            pSynthesisLinkCreateParams->outQueParams[outputQId].nextLink,
            SYSTEM_CMD_NEW_DATA,
            NULL);

      }
      /*
       * Putting filled buffer into output full buffer for
       * outputQId = ALGLINK_SYNTHESIS_OPQID_PASTATS
       */
      outputQId = ALGLINK_SYNTHESIS_OPQID_PASTATS;
      status    = AlgorithmLink_putFullOutputBuffer(pObj,
                                                    outputQId,
                                                    pSysBufferPAStats);

      UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

      /*
       * Informing next link that a new data has peen put for its
       * processing
       */
      System_sendLinkCmd(
        pSynthesisLinkCreateParams->outQueParams[outputQId].nextLink,
        SYSTEM_CMD_NEW_DATA,
        NULL);

      /*
       * Releasing (Free'ing) output buffers, since algorithm does not need
       * it for any future usage.
       */
      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D)||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
          outputQId                      = ALGLINK_SYNTHESIS_OPQID_OPFRAME;
          outputBufListReturn.numBuf     = 1;
          outputBufListReturn.buffers[0] = pSysBufferOutput;
          AlgorithmLink_releaseOutputBuffer(pObj,
                                            outputQId,
                                            &outputBufListReturn);
      }

      outputQId                      = ALGLINK_SYNTHESIS_OPQID_PASTATS;
      outputBufListReturn.numBuf     = 1;
      outputBufListReturn.buffers[0] = pSysBufferPAStats;
      AlgorithmLink_releaseOutputBuffer(pObj,
                                        outputQId,
                                        &outputBufListReturn);

      /*
       * Releasing (Free'ing) Input buffers, since algorithm does not need
       * it for any future usage.
       */
      bufDropFlag = FALSE;

      inputQId                      = ALGLINK_SYNTHESIS_IPQID_MULTIVIEW;
      inputBufListReturn.numBuf     = 1;
      inputBufListReturn.buffers[0] = pSystemBufferMultiview;
      AlgorithmLink_releaseInputBuffer(
        pObj,
        inputQId,
        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
        pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
        &inputBufListReturn,
        &bufDropFlag);

      if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
           (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
      {
          if(pSynthesisObj->isFirstOPGenerated == TRUE)
          {
            inputQId                      = ALGLINK_SYNTHESIS_IPQID_PALUT;
            inputBufListReturn.numBuf     = 1;
            inputBufListReturn.buffers[0] = pSystemBufferPALUT;
            AlgorithmLink_releaseInputBuffer(
                pObj,
                inputQId,
                pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkId,
                pSynthesisLinkCreateParams->inQueParams[inputQId].prevLinkQueId,
                &inputBufListReturn,
                &bufDropFlag);
          }

          pSynthesisObj->isFirstOPGenerated = TRUE;
      }
    }

    if(isProcessCallDoneFlag == FALSE)
        break;
            /* TBD - Take care of error stats

            pSynthesisObj->linkStats.inBufErrorCount++;
            pSynthesisObj->linkStats.chStats
                            [pSysBufferInput->chNum].inBufDropCount++;
            pSynthesisObj->linkStats.chStats
                            [pSysBufferInput->chNum].outBufDropCount[0]++;
            */

    } /* End of while(1) */

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for synthesis algorithm link
 *
 *
 * \param  pObj               [IN] Algorithm link object handle
 * \param  pControlParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_synthesisControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_SynthesisObj     * pSynthesisObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    void                           * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pSynthesisObj = (AlgorithmLink_SynthesisObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pSynthesisObj->algHandle;

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
            AlgorithmLink_synthesisPrintStatistics(pObj, pSynthesisObj);
            break;

        case ALGORITHM_LINK_SRV_SYNTHESIS_LATE_CREATE:
            AlgorithmLink_synthesisLateCreate(pObj, pSynthesisObj);
            break;

        default:
            status = Alg_SynthesisControl(algHandle,
                                          &(pSynthesisObj->controlParams)
                                          );
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for synthesis algorithm link
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
Int32 AlgorithmLink_synthesisStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for synthesis algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisDelete(void * pObj)
{
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       metaBufSize;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;
    System_MetaDataBuffer      * pSystemMetaDataBuffer;
    AlgorithmLink_SynthesisInputQueId    inputQId;
    AlgLink_MemRequests          memRequests;

    AlgorithmLink_SynthesisObj           * pSynthesisObj;
    AlgorithmLink_SynthesisCreateParams  * pSynthesisLinkCreateParams;
    SV_Synthesis_CreationParamsStruct    * pAlgCreateParams;
    UInt32                                 memTabId;

    pSynthesisObj = (AlgorithmLink_SynthesisObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pSynthesisObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pSynthesisLinkCreateParams = &pSynthesisObj->algLinkCreateParams;
    pAlgCreateParams = (&pSynthesisObj->algCreateParams);

    Alg_SynthesisDelete(pSynthesisObj->algHandle, &memRequests);

    /*
     * Memory allocations for the requests done by algorithm
     */
    for(memTabId = 0 ; memTabId < memRequests.numMemTabs ; memTabId++)
    {

        if(memRequests.memTab[memTabId].memLocation == ALGORITHM_LINK_MEM_DSPL2)
        {
            Utils_memFree(
                    UTILS_HEAPID_L2_LOCAL,
                    memRequests.memTab[memTabId].basePtr,
                    memRequests.memTab[memTabId].size
                    );
        }
        if(memRequests.memTab[memTabId].memLocation != ALGORITHM_LINK_MEM_DSPL2)
        {

            if(memRequests.memTab[memTabId].size > 0)
            {

            status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                   memRequests.memTab[memTabId].basePtr,
                                   memRequests.memTab[memTabId].size);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            }

        }

    }

    /*
     * Deletion of output buffers for output Q of ALGLINK_SYNTHESIS_OPQID_OPFRAME
     */
    /* Set the second output Q only incase of 2D SRV mode */
    if (((pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D) ||
         (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_2D_LDC)) ||
        (pSynthesisLinkCreateParams->svOutputMode == ALGORITHM_LINK_SRV_OUTPUT_3D_LDC))
    {
        for(frameIdx = 0;
            frameIdx < pSynthesisObj->algLinkCreateParams.numOutputFrames;
            frameIdx++)
        {
            pSystemVideoFrameBuffer =
                                 &(pSynthesisObj->videoFrames[frameIdx]);

            /*
             * Buffer allocation done for maxHeight, outPitch and for 420SP format
             */
            status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                   pSystemVideoFrameBuffer->bufAddr[0],
                                  (SV_ALGLINK_OUTPUT_FRAME_HEIGHT*(pSynthesisObj->outPitch[0])*(1.5)));

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        }
    }

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           pSynthesisObj->pLinkStaticPALUT,
                           sizeof(PAlignOutStruct));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Deletion of output buffers for output Q of ALGLINK_SYNTHESIS_OPQID_PASTATS
     */
    for(frameIdx = 0;
        frameIdx < pSynthesisObj->algLinkCreateParams
                    .numPhotometricStatisticsTables;
        frameIdx++)
    {
        pSystemMetaDataBuffer =
                             &(pSynthesisObj->photoAlignStats[frameIdx]);

        /*
         * Buffer allocation done considering following factors -
         *  - Sub sampled height
         *  - Sub sampled width
         *  - Number of planes (3)
         *  - Number of non-overlapping view pairs
         *    (Ex: For 4 views case, 1-3 and 2-4 are non overlapping view pairs)
         * An additional 256 bytes for any round off etc during division etc..
         */
        if(ALGLINK_SYNTHESIS_OUTPUTRES_2MP == pSynthesisObj->algLinkCreateParams.outputRes)
        {
            metaBufSize =
                (SV_ALGLINK_OUTPUT_FRAME_HEIGHT / pAlgCreateParams->blockSizeV) *
                (SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP / pAlgCreateParams->blockSizeH) *
                pAlgCreateParams->numColorChannels *
                PAlignStat_BitPerEntry *
                2
                + 256 + 64U
                ;
        }
        else
        {
            metaBufSize =
                (SV_ALGLINK_OUTPUT_FRAME_HEIGHT / pAlgCreateParams->blockSizeV) *
                (SV_ALGLINK_OUTPUT_FRAME_WIDTH / pAlgCreateParams->blockSizeH) *
                pAlgCreateParams->numColorChannels *
                PAlignStat_BitPerEntry *
                2
                + 256 + 64U
                ;
        }

        status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                pSystemMetaDataBuffer->bufAddr[0],
                                metaBufSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    if(pSynthesisLinkCreateParams->svOutputMode != \
                                        ALGORITHM_LINK_SRV_OUTPUT_3D_LDC)
    {
        /*
         * Deletion of output buffers for output Q of ALGLINK_SYNTHESIS_OPQID_PASTATS
         */
        for(frameIdx = 0;
            frameIdx < pSynthesisObj->algLinkCreateParams
                        .numSgxBlendLUTables;
            frameIdx++)
        {
            pSystemMetaDataBuffer = &(pSynthesisObj->opSgxBlendLUT[frameIdx]);

            /*
             * Buffer allocation done considering following factors -
             *  - Sub sampled height
             *  - Sub sampled width
             *  - Number of planes (3)
             *  - Number of non-overlapping view pairs
             *    (Ex: For 4 views case, 1-3 and 2-4 are non overlapping view pairs)
             * An additional 256 bytes for any round off etc during division etc..
             */
            if(ALGLINK_SYNTHESIS_OUTPUTRES_2MP == pSynthesisObj->algLinkCreateParams.outputRes)
            {
                metaBufSize = (SV_ALGLINK_OUTPUT_FRAME_HEIGHT * \
                               SV_ALGLINK_OUTPUT_FRAME_WIDTH_2MP * 4 );
            }
            else
            {
                metaBufSize = (SV_ALGLINK_OUTPUT_FRAME_HEIGHT * \
                               SV_ALGLINK_OUTPUT_FRAME_WIDTH * 4 );
            }


            status =  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                                    pSystemMetaDataBuffer->bufAddr[0],
                                    metaBufSize);
            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
        }
    }

    /*
     * Deletion of local input Qs for ALGLINK_SYNTHESIS_IPQID_MULTIVIEW and
     * ALGLINK_SYNTHESIS_IPQID_PALUT.
     * For ALGLINK_SYNTHESIS_IPQID_GALUT, always just one entry is kept.
     */
    inputQId = ALGLINK_SYNTHESIS_IPQID_MULTIVIEW;
    status = Utils_queDelete(&(pSynthesisObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    inputQId = ALGLINK_SYNTHESIS_IPQID_PALUT;
    status = Utils_queDelete(&(pSynthesisObj->localInputQ[inputQId].queHandle));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /*
     * Space for Algorithm specific object gets freed here.
     */
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           pSynthesisObj,
                           sizeof(AlgorithmLink_SynthesisObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pSynthesisObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_synthesisPrintStatistics(void *pObj,
                       AlgorithmLink_SynthesisObj *pSynthesisObj)
{
    UTILS_assert(NULL != pSynthesisObj->linkStatsInfo);

    Utils_printLinkStatistics(&pSynthesisObj->linkStatsInfo->linkStats, "ALG_SYNTHESIS", TRUE);

    Utils_printLatency("ALG_SYNTHESIS",
                       &pSynthesisObj->linkStatsInfo->linkLatency,
                       &pSynthesisObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
