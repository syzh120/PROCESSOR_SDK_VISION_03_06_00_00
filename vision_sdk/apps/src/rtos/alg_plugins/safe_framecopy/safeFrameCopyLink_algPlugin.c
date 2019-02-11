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
 * \file safeFrameCopyLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for frame copy Link
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 * \version 0.1 (Aug 2013) : [PS] Changes to make plug in functions not rely
 *                                on the elements of Algorithm link object.
 *                                Necessary functionality is accomplished via
 *                                API call backs to link skeletal implementation
 * \version 0.2 (Sept 2013) : [PS] Added code for multi channel support
 * \version 0.3 (Sept 2013) : [PS] Added code for stats collector
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "safeFrameCopyLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <ti/drv/vps/include/osal/bsp_safety_osal.h>

/*
 * Memory violations are disabled by default.
 * Change this to (0 == (frameCount % 5U))
 * to generate a violation every 5th frame
 * Violation will be blocked by XMC/firewall.
 * IPU/DSP will print out error violations in UART log
 */
#define VIOLATE_CONDITION (0)

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
Int32 AlgorithmLink_SafeFrameCopy_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_safeFrameCopyCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_safeFrameCopyProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_safeFrameCopyControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_safeFrameCopyStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_safeFrameCopyDelete;

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_SAFEFRAMECOPY;
#endif

#ifdef BUILD_ARP32
    algId = ALGORITHM_LINK_EVE_ALG_SAFEFRAMECOPY;
#endif

#ifdef BUILD_A15
    algId = ALGORITHM_LINK_A15_ALG_SAFEFRAMECOPY;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);
    AlgorithmLink_setPluginFFIMode(algId, BSP_SAFETY_OSAL_MODE_QM);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for frame copy algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
#ifdef BUILD_ARP32
static void Alg_sfcMemCpy(UInt32 *dst, UInt32 *src, UInt32 size)
{
    UInt32 cnt;

    for (cnt = 0; cnt < size; cnt ++)
    {
        *dst = *src;
        dst ++;
        src ++;
    }
}
#endif

Int32 AlgorithmLink_safeFrameCopyCreate(void * pObj, void * pCreateParams)
{
    Alg_SafeFrameCopy_Obj          * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       maxHeight;
    UInt32                       maxWidth;
    System_Buffer              * pSystemBuffer;
    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;
    System_LinkInfo              prevLinkInfo;
    Int32                        outputQId;
    Int32                        channelId;
    Int32                        numChannelsUsed;
    Int32                        numInputQUsed;
    Int32                        numOutputQUsed;
    UInt32                       prevLinkQueId;
    UInt32                       dataFormat;
    System_LinkChInfo          * pOutChInfo;
    System_LinkChInfo          * pPrevChInfo;
    UInt32                       prevChInfoFlags;

    AlgorithmLink_SafeFrameCopyObj          * pSafeFrameCopyObj;
    AlgorithmLink_SafeFrameCopyCreateParams * pSafeFrameCopyCreateParams;
    AlgorithmLink_OutputQueueInfo       * pOutputQInfo;
    AlgorithmLink_InputQueueInfo        * pInputQInfo;

    pSafeFrameCopyCreateParams =
        (AlgorithmLink_SafeFrameCopyCreateParams *)pCreateParams;

    /*
     * Space for Algorithm specific object gets allocated here.
     * Pointer gets recorded in algorithmParams
     */
    pSafeFrameCopyObj = (AlgorithmLink_SafeFrameCopyObj *)
                        Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
                                       sizeof(AlgorithmLink_SafeFrameCopyObj), 32);

    UTILS_assert(pSafeFrameCopyObj!=NULL);

    pOutputQInfo = &pSafeFrameCopyObj->outputQInfo;
    pInputQInfo  = &pSafeFrameCopyObj->inputQInfo;

    AlgorithmLink_setAlgorithmParamsObj(pObj, pSafeFrameCopyObj);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    pSafeFrameCopyObj->algLinkCreateParams.maxHeight =
        pSafeFrameCopyCreateParams->maxHeight;
    pSafeFrameCopyObj->algLinkCreateParams.maxWidth  =
        pSafeFrameCopyCreateParams->maxWidth;
    pSafeFrameCopyObj->algLinkCreateParams.numOutputFrames =
        pSafeFrameCopyCreateParams->numOutputFrames;

    /* TODO: Make sure that the size of data structures
             System_LinkOutQueParams and System_LinkInQueParams are multiple
             of 4 byte */
#ifdef BUILD_ARP32
    Alg_sfcMemCpy((UInt32*)(&pSafeFrameCopyObj->outQueParams),
               (UInt32*)(&pSafeFrameCopyCreateParams->outQueParams),
                sizeof(System_LinkOutQueParams)/4);
    Alg_sfcMemCpy((UInt32 *)(&pSafeFrameCopyObj->inQueParams),
           (UInt32 *)(&pSafeFrameCopyCreateParams->inQueParams),
           sizeof(System_LinkInQueParams) / 4);
#else
    memcpy((void*)(&pSafeFrameCopyObj->outQueParams),
           (void *)(&pSafeFrameCopyCreateParams->outQueParams),
                sizeof(System_LinkOutQueParams));
    memcpy((void *)(&pSafeFrameCopyObj->inQueParams),
           (void *)(&pSafeFrameCopyCreateParams->inQueParams),
           sizeof(System_LinkInQueParams));
#endif
    /*
     * Populating parameters corresponding to Q usage of frame copy
     * algorithm link
     */
    numInputQUsed     = 1;
    numOutputQUsed    = 1;
    numChannelsUsed   = 1;
    pInputQInfo->qMode  = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;
    pOutputQInfo->qMode = ALGORITHM_LINK_QUEUEMODE_NOTINPLACE;

    outputQId                 = 0;
    pOutputQInfo->queInfo.numCh = numChannelsUsed;

    /*
     * Channel info of current link will be obtained from previous link.
     * If any of the properties get changed in the current link, then those
     * values need to be updated accordingly in
     * pOutputQInfo->queInfo.chInfo[channelId]
     * In frame copy example, only pitch changes. Hence only it is
     * updated. Other parameters are copied from prev link.
     */
    status = System_linkGetInfo(pSafeFrameCopyCreateParams->inQueParams.prevLinkId,
                                &prevLinkInfo);

    prevLinkQueId = pSafeFrameCopyCreateParams->inQueParams.prevLinkQueId;

    pSafeFrameCopyObj->numInputChannels = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    maxHeight = pSafeFrameCopyObj->algLinkCreateParams.maxHeight;
    maxWidth  = pSafeFrameCopyObj->algLinkCreateParams.maxWidth;

    /*
     * Make pitch a multiple of ALGORITHMLINK_FRAME_ALIGN, so that if the frame
     * origin is aligned, then individual lines are also aligned
     * Also note that the pitch is kept same independent of width of
     * individual channels
     */
    pSafeFrameCopyObj->pitch = maxWidth;
    if(maxWidth % ALGORITHMLINK_FRAME_ALIGN)
    {
        pSafeFrameCopyObj->pitch += (ALGORITHMLINK_FRAME_ALIGN -
                                (maxWidth % ALGORITHMLINK_FRAME_ALIGN));
    }

    /*
     * Channel Info Population
     */
    for(channelId =0 ; channelId < pSafeFrameCopyObj->numInputChannels; channelId++)
    {

      pOutChInfo      = &(pOutputQInfo->queInfo.chInfo[channelId]);
      pPrevChInfo     = &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]);
      prevChInfoFlags = pPrevChInfo->flags;

      /*
       * Certain channel info parameters simply get defined by previous link
       * channel info. Hence copying them to output channel info
       */
      pOutChInfo->startX = pPrevChInfo->startX;
      pOutChInfo->startY = pPrevChInfo->startY;
      pOutChInfo->width  = pPrevChInfo->width;
      pOutChInfo->height = pPrevChInfo->height;
      pOutChInfo->flags  = prevChInfoFlags;

      dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(prevChInfoFlags);

      if((dataFormat != SYSTEM_DF_YUV422I_YUYV)
         &&
         (dataFormat != SYSTEM_DF_YUV420SP_UV)
        )
      {
        return SYSTEM_LINK_STATUS_EFAIL;
      }

      if(pPrevChInfo->width > maxWidth || pPrevChInfo->height > maxHeight)
      {
        return SYSTEM_LINK_STATUS_EFAIL;
      }

      /*
       * Certain channel info parameters are properties of the current link,
       * They are set here.
       */
      pOutChInfo->pitch[0] = pSafeFrameCopyObj->pitch;
      pOutChInfo->pitch[1] = pSafeFrameCopyObj->pitch;
      pOutChInfo->pitch[2] = pSafeFrameCopyObj->pitch;

      if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
      {
        pOutChInfo->pitch[0] = pSafeFrameCopyObj->pitch * 2;
      }

      /*
       * Taking a copy of input channel info in the link object for any future
       * use
       */
      memcpy((void *)&(pSafeFrameCopyObj->inputChInfo[channelId]),
             (void *)&(prevLinkInfo.queInfo[prevLinkQueId].chInfo[channelId]),
             sizeof(System_LinkChInfo)
            );
    }

    /*
     * If any output buffer Q gets used in INPLACE manner, then
     * pOutputQInfo->inQueParams and
     * pOutputQInfo->inputQId need to be populated appropriately.
     */

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

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Create call for algorithm
     * - Algorithm handle gets recorded inside link object
     */

    pSafeFrameCopyObj->createParams.maxHeight    = maxHeight;
    pSafeFrameCopyObj->createParams.maxWidth     = maxWidth;
    pSafeFrameCopyObj->frameDropCounter          = 0;

    algHandle = Alg_SafeFrameCopyCreate(&pSafeFrameCopyObj->createParams);
    UTILS_assert(algHandle != NULL);

    pSafeFrameCopyObj->algHandle = algHandle;

    /*
     * Creation of output buffers for output buffer Q = 0 (Used)
     *  - Connecting video frame buffer to system buffer payload
     *  - Memory allocation for Luma and Chroma buffers (Assume 420 format)
     *  - Put the buffer into empty queue
     */
    outputQId = 0;

    for(channelId =0 ; channelId < pSafeFrameCopyObj->numInputChannels; channelId++)
    {
      for(frameIdx = 0;
          frameIdx < pSafeFrameCopyObj->algLinkCreateParams.numOutputFrames;
          frameIdx++)
      {
        pSystemBuffer           =
                             &(pSafeFrameCopyObj->buffers[channelId][frameIdx]);
        pSystemVideoFrameBuffer =
                             &(pSafeFrameCopyObj->videoFrames[channelId][frameIdx]);

        /*
         * Properties of pSystemBuffer, which do not get altered during
         * run time (frame exchanges) are initialized here
         */
        pSystemBuffer->payload     = pSystemVideoFrameBuffer;
        pSystemBuffer->payloadSize = sizeof(System_VideoFrameBuffer);
        pSystemBuffer->bufType     = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->chNum       = channelId;

        memcpy((void *)&pSystemVideoFrameBuffer->chInfo,
               (void *)&pOutputQInfo->queInfo.chInfo[channelId],
               sizeof(System_LinkChInfo));

        /*
         * Buffer allocation done for maxHeight, maxWidth and also assuming
         * worst case num planes = 2, for data Format SYSTEM_DF_YUV422I_YUYV
         * run time (frame exchanges) are initialized here
         */
        pSystemVideoFrameBuffer->bufAddr[0] =
            Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
                           (maxHeight*(pSafeFrameCopyObj->pitch)*2),
                           ALGORITHMLINK_FRAME_ALIGN);

        /*
         * Carving out memory pointer for chroma which will get used in case of
         * SYSTEM_DF_YUV422SP_UV
         */
        pSystemVideoFrameBuffer->bufAddr[1] = (void*)(
            (UInt32) pSystemVideoFrameBuffer->bufAddr[0] +
            (UInt32)(maxHeight*(pSafeFrameCopyObj->pitch))
            );

        UTILS_assert(pSystemVideoFrameBuffer->bufAddr[0] != NULL);

        AlgorithmLink_putEmptyOutputBuffer(pObj, outputQId, pSystemBuffer);
      }
    }

    pSafeFrameCopyObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
        AlgorithmLink_getLinkId(pObj), "ALG_FRAME_COPY");
    UTILS_assert(NULL != pSafeFrameCopyObj->linkStatsInfo);

    pSafeFrameCopyObj->isFirstFrameRecv = FALSE;

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin for frame copy algorithm link
 *
 *        This function executes on the DSP or EVE or A15 processor.
 *        Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can pre-empt this function execution.
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_safeFrameCopyProcess(void * pObj)
{
    AlgorithmLink_SafeFrameCopyObj * pSafeFrameCopyObj;
    Alg_SafeFrameCopy_Obj          * algHandle;
    Int32                        inputQId;
    Int32                        outputQId;
    UInt32                       channelId;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       bufId;
    System_BufferList            inputBufList;
    System_BufferList            inputBufListReturn;
    System_BufferList            outputBufListReturn;
    System_Buffer              * pSysBufferInput;
    System_VideoFrameBuffer    * pSysVideoFrameBufferInput;
    System_Buffer              * pSysBufferOutput;
    System_VideoFrameBuffer    * pSysVideoFrameBufferOutput;
    UInt32                       dataFormat;
    UInt32                       outPitch[SYSTEM_MAX_PLANES];
    UInt32                       bufSize[SYSTEM_MAX_PLANES];
    UInt32                       bufCntr;
    UInt32                       numBuffs;
    System_LinkChInfo          * pInputChInfo;
    System_LinkChInfo          * pOutputChInfo;
    Bool                         bufDropFlag;
    AlgorithmLink_SafeCopyMode   copyMode;
    System_LinkStatistics      * linkStatsInfo;
    /* Using this variable, mode will be switched between DMA and CPU for
     * every alternate frame for DSP and EVE
     */
    UInt32                       frameCount = 0;
    UInt32                       tempAddress[2U];

    pSafeFrameCopyObj = (AlgorithmLink_SafeFrameCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pSafeFrameCopyObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);

    algHandle     = pSafeFrameCopyObj->algHandle;

    Utils_linkStatsCollectorProcessCmd(linkStatsInfo);

    linkStatsInfo->linkStats.newDataCmdCount++;
    frameCount = linkStatsInfo->linkStats.newDataCmdCount;

    /*
     * Getting input buffers from previous link
     */
    System_getLinksFullBuffers(pSafeFrameCopyObj->inQueParams.prevLinkId,
                               pSafeFrameCopyObj->inQueParams.prevLinkQueId,
                               &inputBufList);

    if(inputBufList.numBuf)
    {
        if(pSafeFrameCopyObj->isFirstFrameRecv==FALSE)
        {
            pSafeFrameCopyObj->isFirstFrameRecv = TRUE;

            Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    pSafeFrameCopyObj->numInputChannels,
                    1);

            Utils_resetLatency(&linkStatsInfo->linkLatency);
            Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);
        }

        for (bufId = 0; bufId < inputBufList.numBuf; bufId++)
        {

          pSysBufferInput           = inputBufList.buffers[bufId];
          pSysVideoFrameBufferInput = pSysBufferInput->payload;

          channelId = pSysBufferInput->chNum;

          if(channelId < pSafeFrameCopyObj->numInputChannels)
          {
            linkStatsInfo->linkStats.chStats[channelId].inBufRecvCount++;
          }

          /*
           * Error checks can be done on the input buffer and only later,
           * it can be picked for processing
           */
          if((pSysBufferInput->bufType != SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
             ||
             (channelId >= pSafeFrameCopyObj->numInputChannels)
            )
          {
            bufDropFlag = TRUE;
            linkStatsInfo->linkStats.inBufErrorCount++;
          }
          else
          {

          /*
           * Getting free (empty) buffers from pool of output buffers
           */
          outputQId = 0;


          status = AlgorithmLink_getEmptyOutputBuffer(pObj,
                                                      outputQId,
                                                      channelId,
                                                      &pSysBufferOutput);

          /*
           * Get into algorithm processing only if an output frame is available.
           * Else input buffer will be returned back to sender and its a case
           * of frame drop.
           */
          if(status == SYSTEM_LINK_STATUS_SOK)
          {

          pSysVideoFrameBufferOutput = pSysBufferOutput->payload;
          pOutputChInfo = &(pSafeFrameCopyObj->outputQInfo.queInfo.chInfo[channelId]);
          pInputChInfo  = &(pSafeFrameCopyObj->inputChInfo[channelId]);

          /*
           * If there is any parameter change on the input channel,
           * then, channel info needs to be read from pSysVideoFrameBufferInput.
           * And then,
           *  - Update the local copies present in OutputQInfo and inputChInfo
           *  - Also update channel info in pSysVideoFrameBufferOutput to
           *    pass on new parameters to next link
           */

          if(System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update(
                        pSysVideoFrameBufferInput->chInfo.flags))
          {
            pInputChInfo = &(pSysVideoFrameBufferInput->chInfo);

            memcpy(&(pSafeFrameCopyObj->inputChInfo[channelId]),
                   pInputChInfo,
                   sizeof(System_LinkChInfo));

            memcpy(pOutputChInfo,
                   pInputChInfo,
                   sizeof(System_LinkChInfo));

            dataFormat =
                  System_Link_Ch_Info_Get_Flag_Data_Format(pInputChInfo->flags);

            /*
             * Upon dataFormat change pitch for plane 0 needs to be updated
             * Plane 1 is used only for 420 SP case and it need not be altered
             */
            pOutputChInfo->pitch[0] = pSafeFrameCopyObj->pitch;
            if(dataFormat == SYSTEM_DF_YUV422I_YUYV)
            {
                pOutputChInfo->pitch[0] = pSafeFrameCopyObj->pitch * 2;
            }

            /*
             * Also update the Channel info in Output System Buffer to pass it
             * on to next link
             */
            memcpy(&(pSysVideoFrameBufferOutput->chInfo),
                  pOutputChInfo,
                  sizeof(System_LinkChInfo));
          }
          else
          {
            /*
             * Indicating to next link that there has been no parameter update
             */
            System_Link_Ch_Info_Set_Flag_Data_Format(
                        pSysVideoFrameBufferOutput->chInfo.flags,
                        0);
          }

          /*
           * Call to the algorithm
           */
          outPitch[0] = pOutputChInfo->pitch[0];
          outPitch[1] = pOutputChInfo->pitch[1];

          dataFormat = System_Link_Ch_Info_Get_Flag_Data_Format(
                        pOutputChInfo->flags);

          /*
           * Default
           */
          copyMode = ALGORITHM_LINK_ALG_CPUSAFEFRAMECOPY;

          switch(System_getSelfProcId())
          {
            case SYSTEM_PROC_A15_0:
                copyMode = ALGORITHM_LINK_ALG_CPUSAFEFRAMECOPY;
                break;
            case SYSTEM_PROC_DSP1:
            case SYSTEM_PROC_DSP2:
            case SYSTEM_PROC_EVE1:
            case SYSTEM_PROC_EVE2:
            case SYSTEM_PROC_EVE3:
            case SYSTEM_PROC_EVE4:
                /* Alternate between CPU copy and DMA copy to demonstrate
                 * protection from both CPU and DMA transfers
                 * For TDA3XX, if RTI is enabled, CPU copy is not used.
                 *   - Since RTI-LINK depends on BspOsal_sleep()
                 *   - and ECC_FFI_INCLUDE disables interrupt on EVE during
                 *   - frameCopy, always use DMA COPY for EVE when RTI is used.
                 *   - Otherwise, RTI WWDT will not be serviced at correct time
                 *   - and RTI-LINK will generate error
                 */
                if( 0U == (frameCount & 0x1U) )
                {
                    copyMode = ALGORITHM_LINK_ALG_DMASAFEFRAMECOPY;
                }
                else
                {
                    #if defined(RTI_INCLUDE) && \
                        defined(BUILD_ARP32)
                    copyMode = ALGORITHM_LINK_ALG_DMASAFEFRAMECOPY;
                    #else
                    copyMode = ALGORITHM_LINK_ALG_CPUSAFEFRAMECOPY;
                    #endif
                }
                break;
          }

          switch (dataFormat)
          {
              case SYSTEM_DF_YUV422I_YUYV:
                  numBuffs = 1;
                  break;
              case SYSTEM_DF_YUV420SP_UV:
                  numBuffs = 2;
                  break;
              default:
                  numBuffs = 1;
                  UTILS_assert (0);
                  break;
          }

          pSysBufferOutput->srcTimestamp = pSysBufferInput->srcTimestamp;
          pSysBufferOutput->frameId = pSysBufferInput->frameId;
          pSysBufferOutput->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

          /*
           * Cache Invalidate of input buffer
           */
          if(copyMode == ALGORITHM_LINK_ALG_CPUSAFEFRAMECOPY)
          {
            bufSize[0]  = ((pInputChInfo->height)*(pInputChInfo->pitch[0]));
            bufSize[1]  = ((pInputChInfo->height)*(pInputChInfo->pitch[1]));

            for(bufCntr = 0; bufCntr < numBuffs; bufCntr++)
            {
                Cache_inv(pSysVideoFrameBufferInput->bufAddr[bufCntr],
                          bufSize[bufCntr],
                          Cache_Type_ALLD,
                          TRUE
                         );
            }
          }

          tempAddress[0U] = (UInt32) pSysVideoFrameBufferOutput->bufAddr[0U];
          tempAddress[1U] = (UInt32) pSysVideoFrameBufferOutput->bufAddr[1U];
#if defined(BUILD_ARP32) || defined(BUILD_DSP)
          if(VIOLATE_CONDITION)
          {
            /* Allocating arbitrary buffer in ASIL region to demonstrate
             * XMC/Firewall based protection
             */
            tempAddress[0U] = (UInt32)
                Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL,
                               (pSafeFrameCopyObj->pitch*2),
                               ALGORITHMLINK_FRAME_ALIGN);
            tempAddress[1U] = tempAddress[0U];
          }
#endif

          Alg_SafeFrameCopyProcess(algHandle,
                               (UInt32 **)pSysVideoFrameBufferInput->bufAddr,
                               (UInt32 **)tempAddress,
                               pInputChInfo->width,
                               pInputChInfo->height,
                               pInputChInfo->pitch,
                               outPitch,
                               dataFormat,
                               copyMode
                              );

#if defined(BUILD_ARP32) || defined(BUILD_DSP)
          if(VIOLATE_CONDITION)
          {
            /* Free arbitrary buffer allocated in ASIL region to demonstrate
             * XMC/Firewall based protection
             */
            status =
                  Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL,
                                (Ptr)tempAddress[0],
                                (pSafeFrameCopyObj->pitch*2)
                               );
              UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
          }
#endif

          /*
           * Cache Write back of output buffer to DDR
           */
          if(copyMode == ALGORITHM_LINK_ALG_CPUSAFEFRAMECOPY)
          {
            bufSize[0]  = ((pOutputChInfo->height)*(outPitch[0]));
            bufSize[1]  = ((pOutputChInfo->height)*(outPitch[1]));
            for(bufCntr = 0; bufCntr < numBuffs; bufCntr++)
            {
              Cache_wb(pSysVideoFrameBufferOutput->bufAddr[bufCntr],
                       bufSize[bufCntr],
                       Cache_Type_ALLD,
                       TRUE
                      );
            }
          }

          Utils_updateLatency(&linkStatsInfo->linkLatency,
                              pSysBufferOutput->linkLocalTimestamp);
          Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                              pSysBufferOutput->srcTimestamp);

          linkStatsInfo->linkStats.chStats
                    [pSysBufferInput->chNum].inBufProcessCount++;
          linkStatsInfo->linkStats.chStats
                    [pSysBufferInput->chNum].outBufCount[0]++;

          /*
           * Putting filled buffer into output full buffer Q
           * Note that this does not mean algorithm has freed the output buffer
           */
          status = AlgorithmLink_putFullOutputBuffer(pObj,
                                                     outputQId,
                                                     pSysBufferOutput);

          UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

          /*
           * Informing next link that a new data has peen put for its
           * processing
           */
          System_sendLinkCmd(pSafeFrameCopyObj->outQueParams.nextLink,
                             SYSTEM_CMD_NEW_DATA,
                             NULL);

          /*
           * Releasing (Free'ing) output buffer, since algorithm does not need
           * it for any future usage.
           * In case of INPLACE computation, there is no need to free output
           * buffer, since it will be freed as input buffer.
           */
          outputQId                      = 0;
          outputBufListReturn.numBuf     = 1;
          outputBufListReturn.buffers[0] = pSysBufferOutput;

          AlgorithmLink_releaseOutputBuffer(pObj,
                                            outputQId,
                                            &outputBufListReturn);

          bufDropFlag = FALSE;

          }
          else
          {
            bufDropFlag = TRUE;

            linkStatsInfo->linkStats.outBufErrorCount++;
            linkStatsInfo->linkStats.chStats
                            [pSysBufferInput->chNum].inBufDropCount++;
            linkStatsInfo->linkStats.chStats
                            [pSysBufferInput->chNum].outBufDropCount[0]++;

          } /* Output Buffer availability */

          } /* Input Buffer validity */

          /*
           * Releasing (Free'ing) input buffer, since algorithm does not need
           * it for any future usage.
           */
          inputQId                      = 0;
          inputBufListReturn.numBuf     = 1;
          inputBufListReturn.buffers[0] = pSysBufferInput;
          AlgorithmLink_releaseInputBuffer(
                                      pObj,
                                      inputQId,
                                      pSafeFrameCopyObj->inQueParams.prevLinkId,
                                      pSafeFrameCopyObj->inQueParams.prevLinkQueId,
                                      &inputBufListReturn,
                                      &bufDropFlag);

        }

    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control Plugin for frame copy algorithm link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */

Int32 AlgorithmLink_safeFrameCopyControl(void * pObj, void * pControlParams)
{
    AlgorithmLink_SafeFrameCopyObj     * pSafeFrameCopyObj;
    AlgorithmLink_ControlParams    * pAlgLinkControlPrm;
    Alg_SafeFrameCopy_Obj              * algHandle;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pSafeFrameCopyObj = (AlgorithmLink_SafeFrameCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pSafeFrameCopyObj->algHandle;

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
            AlgorithmLink_safeFrameCopyPrintStatistics(pObj, pSafeFrameCopyObj);
            break;

        default:
            status = Alg_SafeFrameCopyControl(algHandle,
                                          &(pSafeFrameCopyObj->controlParams)
                                          );
            break;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Stop Plugin for frame copy algorithm link
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
Int32 AlgorithmLink_safeFrameCopyStop(void * pObj)
{
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Plugin for frame copy algorithm link
 *
 * \param  pObj              [IN] Algorithm link object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_safeFrameCopyDelete(void * pObj)
{
    Alg_SafeFrameCopy_Obj          * algHandle;
    Int32                        frameIdx;
    Int32                        status    = SYSTEM_LINK_STATUS_SOK;
    UInt32                       maxHeight;
    UInt32                       channelId;

    System_VideoFrameBuffer    * pSystemVideoFrameBuffer;
    AlgorithmLink_SafeFrameCopyObj * pSafeFrameCopyObj;

    pSafeFrameCopyObj = (AlgorithmLink_SafeFrameCopyObj *)
                        AlgorithmLink_getAlgorithmParamsObj(pObj);
    algHandle     = pSafeFrameCopyObj->algHandle;

    status = Utils_linkStatsCollectorDeAllocInst(pSafeFrameCopyObj->linkStatsInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Alg_SafeFrameCopyDelete(algHandle);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    maxHeight = pSafeFrameCopyObj->algLinkCreateParams.maxHeight;

    for(channelId =0 ; channelId < pSafeFrameCopyObj->numInputChannels; channelId++)
    {
      for(frameIdx = 0;
          frameIdx < (pSafeFrameCopyObj->algLinkCreateParams.numOutputFrames);
          frameIdx++)
      {
        pSystemVideoFrameBuffer =
                             &(pSafeFrameCopyObj->videoFrames[channelId][frameIdx]);

        /*
         * Free'ing up of allocated buffers
         */
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
                               pSystemVideoFrameBuffer->bufAddr[0],
                               (maxHeight*pSafeFrameCopyObj->pitch*2)
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
      }
    }

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
                           pSafeFrameCopyObj, sizeof(AlgorithmLink_SafeFrameCopyObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param  pObj                [IN] Algorithm link object handle
 * \param  pSafeFrameCopyObj       [IN] Frame copy link Object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_safeFrameCopyPrintStatistics(void *pObj,
                       AlgorithmLink_SafeFrameCopyObj *pSafeFrameCopyObj)
{

    UTILS_assert(NULL != pSafeFrameCopyObj->linkStatsInfo);

    Utils_printLinkStatistics(&pSafeFrameCopyObj->linkStatsInfo->linkStats, "ALG_SAFEFRAMECOPY", TRUE);

    Utils_printLatency("ALG_SAFEFRAMECOPY",
                       &pSafeFrameCopyObj->linkStatsInfo->linkLatency,
                       &pSafeFrameCopyObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
