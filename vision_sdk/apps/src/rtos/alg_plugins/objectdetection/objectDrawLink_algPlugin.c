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
 * \file objectDrawLink_algPlugin.c
 *
 * \brief  This file contains plug in functions for rectangle drawing over
 *         a object. This plugin does the following
 *          - Takes the composite buffer from the previous link. The composite
 *            buffer has two channels, one containing the original video
 *            and the other containing metadata (rectangles to be drawn)
 *          - Scales co-ordinates as per the requirement
 *          - Optionally copies the input video into an output buffer
 *            using EDMA
 *          - Draws rectangles on the video and sends to the next link
 *
 * \version 0.0 (Mar 2014) : [NN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "objectDrawLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

#define COLOR_INDEX_MAX (64)
#define SOF_PAD_PIXELS  (16)

#define MAX_SFM_DISTANCE    (30.0)

static UInt32 YUV_COLOR_MAP[COLOR_INDEX_MAX];

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
Int32 AlgorithmLink_objectDraw_initPlugin()
{
    AlgorithmLink_FuncTable pluginFunctions;
    UInt32 algId = (UInt32)-1;

    pluginFunctions.AlgorithmLink_AlgPluginCreate =
        AlgorithmLink_objectDrawCreate;
    pluginFunctions.AlgorithmLink_AlgPluginProcess =
        AlgorithmLink_objectDrawProcess;
    pluginFunctions.AlgorithmLink_AlgPluginControl =
        AlgorithmLink_objectDrawControl;
    pluginFunctions.AlgorithmLink_AlgPluginStop =
        AlgorithmLink_objectDrawStop;
    pluginFunctions.AlgorithmLink_AlgPluginDelete =
        AlgorithmLink_objectDrawDelete;

#ifdef BUILD_M4
    algId = ALGORITHM_LINK_IPU_ALG_OBJECT_DRAW;
#endif

#ifdef BUILD_A15
    algId = ALGORITHM_LINK_A15_ALG_OBJECT_DRAW;
#endif

#ifdef BUILD_DSP
    algId = ALGORITHM_LINK_DSP_ALG_OBJECT_DRAW;
#endif

    AlgorithmLink_registerPlugin(algId, &pluginFunctions);

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for object draw alg link
 *
 *
 * \param  pObj              [IN] Algorithm link object handle
 * \param  pCreateParams     [IN] Pointer to create time parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_objectDrawCreate(void * pObj,void * pCreateParams)
{
    UInt32 numInputQUsed;
    UInt32 numOutputQUsed;
    UInt32 numChannelsUsed;
    UInt32 channelId;
    UInt32 status;
    UInt32 bufId;
    UInt32 prevLinkQId;
    Utils_DmaChCreateParams dmaParams;
    AlgorithmLink_ObjectDrawObj                         * pObjectDrawObj;
    AlgorithmLink_ObjectDrawCreateParams                * pLinkCreateParams;
    AlgorithmLink_OutputQueueInfo                           * pOutputQInfo;
    AlgorithmLink_InputQueueInfo                            * pInputQInfo;
    System_LinkInfo                                           prevLinkInfo;
    System_LinkChInfo                                       * pOutChInfo;
    System_LinkChInfo                                       * pPrevLinkChInfo;
    System_Buffer                                           * pSystemBuffer;
    System_VideoFrameBuffer                                 * pVideoBuffer;


    pObjectDrawObj = (AlgorithmLink_ObjectDrawObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmLink_ObjectDrawObj), 32);
    UTILS_assert(pObjectDrawObj != NULL);

    AlgorithmLink_setAlgorithmParamsObj(pObj, pObjectDrawObj);

    pLinkCreateParams = (AlgorithmLink_ObjectDrawCreateParams *)
                         pCreateParams;
    pInputQInfo       = &pObjectDrawObj->inputQInfo;
    pOutputQInfo      = &pObjectDrawObj->outputQInfo;
    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pObjectDrawObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmLink_ObjectDrawCreateParams)
           );
    /*
     * Populating parameters corresponding to Q usage of geometric alignment
     * algorithm link
     */
    numInputQUsed               = 1;
    numOutputQUsed              = 1;
    numChannelsUsed             = 1;
    channelId                   = 0;

    AlgorithmLink_objectDrawConvertHsvToYuv();

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
    prevLinkQId         = pLinkCreateParams->inQueParams.prevLinkQueId;
    pPrevLinkChInfo     = &prevLinkInfo.queInfo[prevLinkQId].chInfo[channelId];

    /*
     * Copy previous link channel information as current link's out
     * channel information
     */
    memcpy(pOutChInfo, pPrevLinkChInfo, sizeof(System_LinkChInfo));

    /* override to take ROI into effect */
    pOutChInfo->width = pLinkCreateParams->imgFrameWidth;
    pOutChInfo->height = pLinkCreateParams->imgFrameHeight;
    pOutChInfo->startX = 0;
    pOutChInfo->startY = 0;

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

    status = Draw2D_create(&pObjectDrawObj->draw2DHndl);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Dummy address value, that is overridden later */
    pObjectDrawObj->draw2DBufInfo.bufAddr[0]  = 0xFFFF;
    pObjectDrawObj->draw2DBufInfo.bufAddr[1]  = 0xFFFF;

    pObjectDrawObj->draw2DBufInfo.bufWidth    = pOutChInfo->width;
    pObjectDrawObj->draw2DBufInfo.bufHeight   = pOutChInfo->height;
    pObjectDrawObj->draw2DBufInfo.bufPitch[0] = pOutChInfo->pitch[0];
    pObjectDrawObj->draw2DBufInfo.bufPitch[1] = pOutChInfo->pitch[1];
    pObjectDrawObj->draw2DBufInfo.dataFormat  = SYSTEM_DF_YUV420SP_UV;
    pObjectDrawObj->draw2DBufInfo.transperentColor = DRAW2D_TRANSPARENT_COLOR;
    pObjectDrawObj->draw2DBufInfo.transperentColorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;

    status = Draw2D_setBufInfo(pObjectDrawObj->draw2DHndl,
                                &pObjectDrawObj->draw2DBufInfo);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);


    /*
     * Create DMA channel
     */
    Utils_DmaChCreateParams_Init(&dmaParams);

    status = Utils_dmaCreateCh(
                                &pObjectDrawObj->copyFramesDmaObj,
                                &dmaParams
                               );
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);



    /* if thickness value is outside a range, set it to default */
    if(    pObjectDrawObj->algLinkCreateParams.objectRectThickness >  8
        || pObjectDrawObj->algLinkCreateParams.objectRectThickness == 0
        )
    {
        pObjectDrawObj->algLinkCreateParams.objectRectThickness
            = OBJECT_RECTANGLE_THICKNESS;
    }

    pObjectDrawObj->linePrm.lineSize
        = pObjectDrawObj->algLinkCreateParams.objectRectThickness;

    pObjectDrawObj->laneMinWidth = 0;
    pObjectDrawObj->laneMaxWidth = 0;

    /*
     * Algorithm creation happens here
     * - Population of create time parameters
     * - Query for number of memory records needed
     * - Query for the size of each algorithm internal objects
     * - Actual memory allocation for internal alg objects
     */

    /*
     * Allocate memory for the output buffers and link metadata buffer with
     * system Buffer
     */
    pObjectDrawObj->outBufferSize_y = pOutChInfo->pitch[0]
                      *
                      pOutChInfo->height;

    pObjectDrawObj->outBufferSize_uv = (pOutChInfo->pitch[1]
                      *
                      pOutChInfo->height)/2;

    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pSystemBuffer       =  &pObjectDrawObj->buffers[bufId];
        pVideoBuffer        =  &pObjectDrawObj->videoBuffers[bufId];

        pSystemBuffer->bufType      = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
        pSystemBuffer->chNum        = 0;
        pSystemBuffer->payload      = pVideoBuffer;
        pSystemBuffer->payloadSize  = sizeof(System_VideoFrameBuffer);
        pVideoBuffer->bufAddr[0]    = Utils_memAlloc
                                      (
                                        UTILS_HEAPID_DDR_CACHED_SR,
                                        pObjectDrawObj->outBufferSize_y +
                                         pObjectDrawObj->outBufferSize_uv,
                                        ALGORITHMLINK_FRAME_ALIGN
                                      );
        pVideoBuffer->bufAddr[1]    = (UInt8 *)pVideoBuffer->bufAddr[0] +
            pObjectDrawObj->outBufferSize_y;

        memcpy(
                &pVideoBuffer->chInfo,
                pPrevLinkChInfo,
                sizeof(System_LinkChInfo)
              );
       pVideoBuffer->flags = pPrevLinkChInfo->flags;
       AlgorithmLink_putEmptyOutputBuffer(pObj, 0, pSystemBuffer);
    }

    pObjectDrawObj->linkStatsInfo = Utils_linkStatsCollectorAllocInst(
       AlgorithmLink_getLinkId(pObj), " ALG_OBJECT_DRAW");
    UTILS_assert(NULL != pObjectDrawObj->linkStatsInfo);

    pObjectDrawObj->isFirstFrameRecv    = FALSE;

    return SYSTEM_LINK_STATUS_SOK;
}

Void AlgorithmLink_objectDrawDistanceFromCamera(AlgorithmLink_ObjectDrawObj *pObj,
                    TI_OD_objectDescriptor *pObjectDataDesc)
{
    char distFromObject[32];
    Draw2D_FontPrm fontPrm;
    float distance;

    if(pObj->algLinkCreateParams.objectDrawDistance)
    {
        if(pObjectDataDesc->objType==TI_OD_PEDESTRIAN
                ||
           pObjectDataDesc->objType==TI_OD_VEHICLE
            )
        {
            distance = pObjectDataDesc->reserved0;

            if(distance > MAX_SFM_DISTANCE)
            {
                distance = MAX_SFM_DISTANCE;
            }

            if(distance >= 0)
            {
                sprintf(distFromObject, "%dm", (Int32)distance);

                fontPrm.fontIdx = 13;

                Draw2D_drawString(pObj->draw2DHndl,
                    pObjectDataDesc->xPos,
                    pObjectDataDesc->yPos
                            + pObjectDataDesc->objHeight
                            + pObj->linePrm.lineSize
                            + 2,
                    distFromObject,
                    &fontPrm
                    );
            }
        }
    }
}

Void AlgorithmLink_objectDrawTrafficSigns(AlgorithmLink_ObjectDrawObj *pObj,
                    TI_OD_objectDescriptor *pObjectDataDesc,
                    UInt32 bufAddr[SYSTEM_MAX_PLANES])
{
    if( pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR )
    {
        if(pObjectDataDesc->objType==TI_OD_TRAFFIC_SIGN)
        {
            if(pObj->algLinkCreateParams.objectTsrDrawTrafficSigns)
            {
                if((pObjectDataDesc->objSubType) > 0 && (pObjectDataDesc->objSubType < OBJECTDRAW_TRAFFIC_SIGN_MAX))
                {
                    AlgorithmLink_objectDrawCopyTrafficSign(
                       (UInt8*)bufAddr[0],
                        (UInt8*)bufAddr[1],
                        pObj->draw2DBufInfo.bufPitch[0],
                        pObj->draw2DBufInfo.bufPitch[1],
                        pObj->draw2DBufInfo.bufWidth,
                        pObj->draw2DBufInfo.bufHeight,
                        pObjectDataDesc->xPos - 16,
                        pObjectDataDesc->yPos - 16,
                        pObjectDataDesc->objSubType,
                        OBJECTDRAW_TRAFFIC_SIGN_32x32
                    );
                }
            }
        }
    }
}

Void AlgorithmLink_objectDrawRectangles(AlgorithmLink_ObjectDrawObj *pObj,
                    TI_OD_objectDescriptor *pObjectDataDesc
                    )
{
    Bool isValidObj;

    isValidObj = FALSE;

    if(    (pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR)
        || (pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD)
        || (pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_VD)
       )
    {
        if(pObjectDataDesc->objType==TI_OD_PEDESTRIAN)
        {
            pObj->linePrm.lineColor = COLOR_PURPLE; /* in YUV */
        }
        else
        if(pObjectDataDesc->objType==TI_OD_VEHICLE)
        {
            pObj->linePrm.lineColor = COLOR_GREEN; /* in YUV */
        }
        else
        if(pObjectDataDesc->objType==TI_OD_TRAFFIC_SIGN)
        {
           pObj->linePrm.lineColor = COLOR_BLUE; /* in YUV */
        }

        if(pObjectDataDesc->objType==TI_OD_TRAFFIC_SIGN)
        {
            if(pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR)
            {
                if((pObjectDataDesc->objSubType) > 0 && (pObjectDataDesc->objSubType < OBJECTDRAW_TRAFFIC_SIGN_MAX))
                {
                    isValidObj = TRUE;
                }
            }
        }
        else
        if(pObjectDataDesc->objType==TI_OD_PEDESTRIAN)
        {
            if(pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD)
            {
                isValidObj = TRUE;
            }
        }
        else
        if(pObjectDataDesc->objType==TI_OD_VEHICLE)
        {
            if(pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_VD)
            {
                isValidObj = TRUE;
            }
        }

    }
    if(pObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR)
    {
        if(pObjectDataDesc->objType == TI_CLR_OBJ_RED_TRAFFIC_LIGHT)
        {
            pObj->linePrm.lineColor = COLOR_RED; /* in YUV */
            pObj->linePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;
            isValidObj = TRUE;
        }
        else
        if(pObjectDataDesc->objType == TI_CLR_OBJ_GREEN_TRAFFIC_LIGHT)
        {
            pObj->linePrm.lineColor = COLOR_GREEN; /* in YUV */
            pObj->linePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;
            isValidObj = TRUE;
        }
        else
        if(pObjectDataDesc->objType == TI_CLR_OBJ_VEHICLE)
        {
            pObj->linePrm.lineColor = COLOR_GREEN; /* in YUV */
            pObj->linePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;
            isValidObj = TRUE;
        }
    }

    if(isValidObj)
    {
        Draw2D_drawRect(
                                pObj->draw2DHndl,
                                pObjectDataDesc->xPos,
                                pObjectDataDesc->yPos,
                                pObjectDataDesc->objWidth,
                                pObjectDataDesc->objHeight,
                                &pObj->linePrm
                            );

        #if 0
        Vps_printf(" ALG_OBJECT_DRAW: Tag=%d, Type=%d, SubType=%d, Score=%f, Scale=%f, (%d, %d : %d x %d)\n",
            pObjectDataDesc->objTag,
            pObjectDataDesc->objType,
            pObjectDataDesc->objSubType,
            pObjectDataDesc->objScore,
            pObjectDataDesc->objScale,
            pObjectDataDesc->xPos,
            pObjectDataDesc->yPos,
            pObjectDataDesc->objWidth,
            pObjectDataDesc->objHeight
            );
        #endif
    }
}

Void AlgorithmLink_objectDrawClr(AlgorithmLink_ObjectDrawObj *pObj)
{
    UInt32 numObjs, i, trafficLightId;
    TI_OD_outputList *pObjectDataOutput;
    TI_OD_objectDescriptor *pObjectDataDesc;

    if(pObj->pClrOutput==NULL)
        return;

    pObjectDataOutput = (TI_OD_outputList*)pObj->pClrOutput;

    /* these need to match since same draw rectangles is used for both OD and CLR */
    UTILS_assert(sizeof(TI_CLR_output)==sizeof(TI_OD_outputList));
    UTILS_assert(sizeof(TI_CLR_objectDescriptor)==sizeof(TI_OD_objectDescriptor));

    /*
     * Invalidate part of the buffer to read size of valid
     * metadata buffer
     */
    Cache_inv(pObjectDataOutput,
              sizeof(TI_OD_outputList),
              Cache_Type_ALLD,
              TRUE
            );


    numObjs = pObjectDataOutput->numObjects;

    if(numObjs <= TI_CLR_MAX_DETECTIONS_PER_FRAME)
    {
        for (i = 0; i < numObjs; i++)
        {
            pObjectDataDesc = &pObjectDataOutput->objDesc[i];

            /* Is it valid circular light ? */
            if(    pObjectDataDesc->objType != TI_CLR_OBJ_RED_TRAFFIC_LIGHT
                && pObjectDataDesc->objType != TI_CLR_OBJ_GREEN_TRAFFIC_LIGHT
                && pObjectDataDesc->objType != TI_CLR_OBJ_VEHICLE
              )
            {
                continue;
            }

            /* OK to draw !! */
            AlgorithmLink_objectDrawRectangles(
                        pObj,
                        pObjectDataDesc
                );

            trafficLightId = 0xFF; /* invalid */

            if(pObjectDataDesc->objType==TI_CLR_OBJ_RED_TRAFFIC_LIGHT)
                trafficLightId = 0;
            else
            if(pObjectDataDesc->objType==TI_CLR_OBJ_GREEN_TRAFFIC_LIGHT)
                trafficLightId = 1;

            AlgorithmLink_objectDrawCopyTrafficLight(
                (UInt8*)pObj->drawBufAddr[0],
                (UInt8*)pObj->drawBufAddr[1],
                pObj->draw2DBufInfo.bufPitch[0],
                pObj->draw2DBufInfo.bufPitch[1],
                pObj->draw2DBufInfo.bufWidth,
                pObj->draw2DBufInfo.bufHeight,
                (pObjectDataDesc->xPos + pObjectDataDesc->objWidth/4) - 32,
                (pObjectDataDesc->yPos + pObjectDataDesc->objHeight/4) - 32,
                trafficLightId,
                0
                );
        }
    }
}

static Bool isInRange(UInt32 value, UInt32 min, UInt32 max)
{
    UInt32 offset = 20;

    if(min > offset)
        min -= offset;
    else
        min = 0;

    max += offset;

    if(value >= min && value <= max)
        return TRUE;

    return FALSE;
}

Void AlgorithmLink_objectDrawObjectsNight(AlgorithmLink_ObjectDrawObj *pObj)
{
    UInt32 numObjs, numClr, i, j, x, y, w, h;
    TI_OD_outputList *pObjectDataOutput;
    TI_OD_objectDescriptor *pObjectDataDesc;
    TI_OD_outputList *pClrDataOutput;
    TI_OD_objectDescriptor *pClrDataDesc;

    if(pObj->pOdOutput==NULL)
        return;

    if(pObj->pClrOutput==NULL)
        return;

    pClrDataOutput = (TI_OD_outputList*)pObj->pClrOutput;
    pObjectDataOutput = (TI_OD_outputList*)pObj->pOdOutput;


    /*
     * Invalidate part of the buffer to read size of valid
     * metadata buffer
     */
    Cache_inv(pObjectDataOutput,
              sizeof(TI_OD_outputList),
              Cache_Type_ALLD,
              TRUE
            );
    Cache_inv(pClrDataOutput,
              sizeof(TI_OD_outputList),
              Cache_Type_ALLD,
              TRUE
            );

    numClr = pClrDataOutput->numObjects;
    numObjs = pObjectDataOutput->numObjects;

    pObj->linePrm.lineColor = COLOR_GREEN; /* in YUV */
    pObj->linePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;

    if (numClr <= TI_OD_MAX_NUM_OBJECTS)
    {
        for (i = 0; i < numClr; i++)
        {
            pClrDataDesc = &pClrDataOutput->objDesc[i];

            x = pClrDataDesc->xPos;
            y = pClrDataDesc->yPos;
            w = pClrDataDesc->objWidth;
            h = pClrDataDesc->objHeight;

            /* check for overlap between CLR and VD */
            for(j=0; j<numObjs; j++)
            {
                pObjectDataDesc = &pObjectDataOutput->objDesc[j];

                if( isInRange(pClrDataDesc->xPos, pObjectDataDesc->xPos, pObjectDataDesc->xPos+pObjectDataDesc->objWidth)
                    &&
                    isInRange(pClrDataDesc->yPos, pObjectDataDesc->yPos, pObjectDataDesc->yPos+pObjectDataDesc->objHeight)
                  )
                {
                    x = pObjectDataDesc->xPos;
                    y = pObjectDataDesc->yPos;
                    w = pObjectDataDesc->objWidth;
                    h = pObjectDataDesc->objHeight;
                }
                if( isInRange(pClrDataDesc->xPos+pClrDataDesc->objWidth, pObjectDataDesc->xPos, pObjectDataDesc->xPos+pObjectDataDesc->objWidth)
                    &&
                    isInRange(pClrDataDesc->yPos+pClrDataDesc->objHeight, pObjectDataDesc->yPos, pObjectDataDesc->yPos+pObjectDataDesc->objHeight)
                  )
                {
                    x = pObjectDataDesc->xPos;
                    y = pObjectDataDesc->yPos;
                    w = pObjectDataDesc->objWidth;
                    h = pObjectDataDesc->objHeight;
                }
                if( isInRange(pClrDataDesc->xPos, pObjectDataDesc->xPos, pObjectDataDesc->xPos+pObjectDataDesc->objWidth)
                    &&
                    isInRange(pClrDataDesc->yPos+pClrDataDesc->objHeight, pObjectDataDesc->yPos, pObjectDataDesc->yPos+pObjectDataDesc->objHeight)
                  )
                {
                    x = pObjectDataDesc->xPos;
                    y = pObjectDataDesc->yPos;
                    w = pObjectDataDesc->objWidth;
                    h = pObjectDataDesc->objHeight;
                }
                if( isInRange(pClrDataDesc->xPos+pClrDataDesc->objWidth, pObjectDataDesc->xPos, pObjectDataDesc->xPos+pObjectDataDesc->objWidth)
                    &&
                    isInRange(pClrDataDesc->yPos, pObjectDataDesc->yPos, pObjectDataDesc->yPos+pObjectDataDesc->objHeight)
                  )
                {
                    x = pObjectDataDesc->xPos;
                    y = pObjectDataDesc->yPos;
                    w = pObjectDataDesc->objWidth;
                    h = pObjectDataDesc->objHeight;
                }
            }

            Draw2D_drawRect(
                            pObj->draw2DHndl,
                            x,
                            y,
                            w,
                            h,
                            &pObj->linePrm
                            );

        }
    }
}

Void AlgorithmLink_objectDrawObjects(AlgorithmLink_ObjectDrawObj *pObj)
{
    UInt32 numObjs, i;
    TI_OD_outputList *pObjectDataOutput;
    TI_OD_objectDescriptor *pObjectDataDesc;

    if(pObj->pOdOutput==NULL)
        return;

    pObjectDataOutput = (TI_OD_outputList*)pObj->pOdOutput;

    /*
     * Invalidate part of the buffer to read size of valid
     * metadata buffer
     */
    if(ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_TIDL_OD !=
        pObj->algLinkCreateParams.drawAlgId[0])
    {
        Cache_inv(pObjectDataOutput,
              sizeof(TI_OD_outputList),
              Cache_Type_ALLD,
              TRUE
            );
    }
    numObjs = pObjectDataOutput->numObjects;

    if (numObjs <= TI_OD_MAX_NUM_OBJECTS)
    {
        for (i = 0; i < numObjs; i++)
        {
            pObjectDataDesc = &pObjectDataOutput->objDesc[i];

            AlgorithmLink_objectDrawRectangles(
                        pObj,
                        pObjectDataDesc
                );

            AlgorithmLink_objectDrawTrafficSigns(
                        pObj,
                        pObjectDataDesc,
                        pObj->drawBufAddr
                    );

            AlgorithmLink_objectDrawDistanceFromCamera(
                        pObj,
                        pObjectDataDesc
                );
        }
    }
}

Void AlgorithmLink_objectDrawLaneFindMinMax(
                                  AlgorithmLink_ObjectDrawObj *pObj,
                                  UInt32 numLanePoints,
                                  LD_TI_output * pLanePoints,
                                  Int32 *minX,
                                  Int32 *minY,
                                  Int32 *maxX,
                                  Int32 *maxY
                               )
{
    UInt32 i;
    LD_TI_output *pPoint;

    *maxX = *maxY = 0;
    *minX = *minY = 0xFFFF;

    for(i=0; i<numLanePoints; i++)
    {
        pPoint = &pLanePoints[i];

        if(pPoint->x < *minX)
            *minX = pPoint->x;

        if(pPoint->x > *maxX)
            *maxX = pPoint->x;

        if(pPoint->y < *minY)
            *minY = pPoint->y;

        if(pPoint->y > *maxY)
            *maxY = pPoint->y;
    }
}

/*
  y - y1 = m (x - x1)

  x = (y-y1)/( (y2-y1)/(x2-x1) ) + x1

  x = (y-y1)*(x2-x1)/(y2-y1) + x1
*/

Int32 AlgorithmLink_objectDrawSolveLineEqForX(Int32 x1, Int32 y1, Int32 x2, Int32 y2, Int32 y)
{
    float inv_slope = (float)(x2-x1)/(y2-y1);

    return (Int32)( (float)(y-y1)*inv_slope + x1);
}

Bool AlgorithmLink_objectDrawIsHorVertLineIntersect(AlgorithmLink_ObjectDrawObj *pObj,
            UInt32 hor_x1,
            UInt32 hor_y1,
            UInt32 hor_x2,
            UInt32 vert_x1,
            UInt32 vert_y1,
            UInt32 vert_y2
            )
{
    Bool status = FALSE;

    if(hor_x1 <= vert_x1 && hor_x2 >= vert_x1)
    {
        if(vert_y1 <= hor_y1 && vert_y2 >= hor_y1)
        {
            status = TRUE;
        }
    }

    return status;
}

Bool AlgorithmLink_objectDrawIsLaneIntersectWithObject(AlgorithmLink_ObjectDrawObj *pObj,
            UInt32 hor_x1,
            UInt32 hor_y1,
            UInt32 hor_x2
            )
{
    Bool status = FALSE;
    UInt32 numObjs, i;
    TI_OD_outputList *pObjectDataOutput;
    TI_OD_objectDescriptor *pObjectDataDesc;

    if(pObj->pOdOutput==NULL)
        return status;

    pObjectDataOutput = (TI_OD_outputList*)pObj->pOdOutput;

    /*
     * Invalidate part of the buffer to read size of valid
     * metadata buffer
     */
    Cache_inv(pObjectDataOutput,
              sizeof(TI_OD_outputList),
              Cache_Type_ALLD,
              TRUE
            );

    numObjs = pObjectDataOutput->numObjects;

    if (numObjs <= TI_OD_MAX_NUM_OBJECTS)
    {
        for (i = 0; i < numObjs; i++)
        {
            pObjectDataDesc = &pObjectDataOutput->objDesc[i];


            status = AlgorithmLink_objectDrawIsHorVertLineIntersect(
                            pObj,
                            hor_x1,
                            hor_y1,
                            hor_x2,
                            pObjectDataDesc->xPos,
                            pObjectDataDesc->yPos,
                            pObjectDataDesc->yPos + pObjectDataDesc->objHeight
                    );
            if(status == FALSE)
            {
                status = AlgorithmLink_objectDrawIsHorVertLineIntersect(
                            pObj,
                            hor_x1,
                            hor_y1,
                            hor_x2,
                            pObjectDataDesc->xPos+pObjectDataDesc->objWidth,
                            pObjectDataDesc->yPos,
                            pObjectDataDesc->yPos + pObjectDataDesc->objHeight
                    );
            }
            if(status==TRUE)
            {
                break;
            }
        }
    }

    return status;
}



Void AlgorithmLink_objectDrawLanes2(AlgorithmLink_ObjectDrawObj *pObj)
{
    AlgorithmLink_LaneDetectOutput *pLaneOutput;
    Int32 leftTopX, leftTopY, leftBottomX, leftBottomY;
    Int32 rightTopX, rightTopY, rightBottomX, rightBottomY;
    Int32 y, x_l, x_r;
    Int32 trapX[4], trapY[4];
    Int32 roiHeight, roiStartY;
    Draw2D_LinePrm linePrm;
    Int32 height, roiWidth;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    char str[32];


    linePrm.lineSize = pObj->algLinkCreateParams.laneThickness;
    linePrm.lineColor = COLOR_YELLOW;
    linePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;

    roiStartY = pObj->algLinkCreateParams.laneRoiStartY;
    roiHeight = pObj->algLinkCreateParams.laneRoiHeight;
    height    = pObj->algLinkCreateParams.imgFrameHeight;
    roiWidth  = pObj->algLinkCreateParams.laneRoiWidth;

    if(pObj->pLdOutput==NULL)
        return;

    pLaneOutput = pObj->pLdOutput;

    Cache_inv(pLaneOutput,
              LANEDETECT_LINK_LANE_POINTS_BUF_SIZE,
              Cache_Type_ALLD,
              TRUE
            );

    if (pLaneOutput->laneCrossInfo == LD_TI_NO_LANE_CROSS)
    {
        if((pLaneOutput->numLeftLanePoints + pLaneOutput->numRightLanePoints) > 1)
        {
            AlgorithmLink_objectDrawLaneFindMinMax(
                pObj,
                pLaneOutput->numLeftLanePoints,
                &pLaneOutput->laneInfo[0],
                &leftBottomX,
                &leftTopY,
                &leftTopX,
                &leftBottomY
                );

            AlgorithmLink_objectDrawLaneFindMinMax(
                pObj,
                pLaneOutput->numRightLanePoints,
                &pLaneOutput->laneInfo[pLaneOutput->numLeftLanePoints],
                &rightTopX,
                &rightTopY,
                &rightBottomX,
                &rightBottomY
                );

            trapY[1] = trapY[0] = (roiStartY);

            if((roiStartY + roiHeight) >= height)
            {
                trapY[2] = trapY[3] = height - 10;
            }
            else
            {
                trapY[2] = trapY[3] = roiStartY + roiHeight - 10;
            }

            trapX[0] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[0]);
            trapX[1] = AlgorithmLink_objectDrawSolveLineEqForX(rightTopX, rightTopY, rightBottomX, rightBottomY, trapY[1]);
            trapX[2] = AlgorithmLink_objectDrawSolveLineEqForX(rightTopX, rightTopY, rightBottomX, rightBottomY, trapY[2]);
            trapX[3] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[3]);

            if(pLaneOutput->numRightLanePoints > 1)
            {
                /* If there are no left lane points, find topXL and botXL = roiWidth, and topYL = topYR, botYL = botYR */
                if(((leftTopX == leftBottomX) && (leftTopY == leftBottomY)) || (pLaneOutput->numLeftLanePoints == 0))
                {
                    if ((pObj->laneMaxWidth != 0) && (pObj->laneMinWidth != 0)){
                      leftTopX = trapX[1] - pObj->laneMinWidth;
                      leftTopY = trapY[1];
                      leftBottomX = trapX[2] - pObj->laneMaxWidth;
                      leftBottomY = trapY[2];
                      trapX[0] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[0]);
                      trapX[3] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[3]);
                    } else {
                      leftTopX = trapX[2] - roiWidth/2; /* used BottomX because need to be trapezoid */
                      leftBottomX = trapX[1] - roiWidth/2; /* used TopX because need to be trapezoid */
                      leftTopY = trapY[1];
                      leftBottomY = trapY[2];
                      trapX[0] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[0]);
                      trapX[3] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[3]);
                    }
                }
            }
            else
            {
                rightTopX = rightBottomX;
                rightTopY = rightBottomY;
            }

            if(pLaneOutput->numLeftLanePoints > 1 )
            {
                /* If there are no right lane points, find topXR and botXR from roiWidth, and topYR = topYL, botYR = botYL */
                if(((rightTopX == rightBottomX) && (rightTopY == rightBottomY)) || (pLaneOutput->numRightLanePoints == 0))
                {
                    if ((pObj->laneMaxWidth != 0) && (pObj->laneMinWidth != 0)){
                      rightTopX = trapX[0] + pObj->laneMinWidth;
                      rightTopY = trapY[0];
                      rightBottomX = trapX[3] + pObj->laneMaxWidth;
                      rightBottomY = trapY[3];
                      trapX[1] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[1]);
                      trapX[2] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[2]);
                    } else {
                      rightTopX = trapX[3] + roiWidth/2; /* used BottomX because need to be trapezoid */
                      rightBottomX = trapX[0] + roiWidth/2; /* used TopX because need to be trapezoid */
                      rightTopY = trapY[0];
                      rightBottomY = trapY[3];
                      trapX[1] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[1]);
                      trapX[2] = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, trapY[2]);
                    }
                }
            }
            else
            {
                return;
            }


            y = trapY[0];
            x_l = trapX[0];
            x_r = trapX[1];

            /* Update the laneMaxWidth the first time */
            if (pObj->laneMinWidth == 0)
            {
                pObj->laneMinWidth = trapX[1] - trapX[0];
            }

            if (pObj->laneMaxWidth == 0)
            {
                pObj->laneMaxWidth = trapX[2] - trapX[3];
            }

            if(pObj->laneMinWidth >= pObj->laneMaxWidth)
            {
                pObj->laneMinWidth = 0;
                pObj->laneMaxWidth = 0;
            }

            while(1)
            {
                if((x_l < 0) || (x_l > pObj->algLinkCreateParams.imgFrameWidth))
                    break;

                if((x_r < 0) || (x_r > pObj->algLinkCreateParams.imgFrameWidth))
                    break;

                x_l = SystemUtils_floor(x_l, 4);
                x_r = SystemUtils_align(x_r, 4);
                y = SystemUtils_floor(y, 2);

                if( AlgorithmLink_objectDrawIsLaneIntersectWithObject(
                            pObj,
                            x_l*pObj->algLinkCreateParams.laneScaleX,
                            y*pObj->algLinkCreateParams.laneScaleY,
                            x_r*pObj->algLinkCreateParams.laneScaleX
                        )
                    == FALSE
                    )
                {
                    Draw2D_drawLine(pObj->draw2DHndl,
                        x_l*pObj->algLinkCreateParams.laneScaleX,
                        y*pObj->algLinkCreateParams.laneScaleY,
                        x_r*pObj->algLinkCreateParams.laneScaleX,
                        y*pObj->algLinkCreateParams.laneScaleY,
                        &linePrm
                        );
                }

                y   += 10;
                x_l = AlgorithmLink_objectDrawSolveLineEqForX(leftTopX, leftTopY, leftBottomX, leftBottomY, y);
                x_r = AlgorithmLink_objectDrawSolveLineEqForX(rightTopX, rightTopY, rightBottomX, rightBottomY, y);

                if(y > trapY[3])
                {
                    break;
                }
            }
        }
    }
    else
    {
        fontPrm.fontIdx = 12;
        Draw2D_getFontProperty(&fontPrm, &fontProp);

        sprintf(str, "!!! DEPARTING LANE !!!");
        Draw2D_drawString(pObj->draw2DHndl,
                (pObj->algLinkCreateParams.imgFrameWidth - (fontProp.width * strlen(str))) /2 ,
                pObj->algLinkCreateParams.imgFrameHeight/4,
                str,
                &fontPrm
                );
    }
}

Void AlgorithmLink_objectDrawSfmDistanceBar(AlgorithmLink_ObjectDrawObj *pObj,
            UInt32 startX, UInt32 startY, float min, float max)
{
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    Draw2D_LinePrm rectPrm;
    UInt32 i;
    UInt16 xmin, xmax, ymin, ymax, barSizeW, barSizeH, gap;
    char str[32];

    barSizeH = 4;
    barSizeW = 24;

    gap = 4;

    rectPrm.lineSize = barSizeH;
    rectPrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;

    fontPrm.fontIdx = 13;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    sprintf(str, "%3.1fm", max);

    Draw2D_drawString(pObj->draw2DHndl,
            startX,
            startY,
            str,
            &fontPrm
            );

    for(i=0; i<COLOR_INDEX_MAX; i++)
    {
        xmin = startX;
        ymin = startY + fontProp.height  + gap + (i*barSizeH);
        xmax = xmin + barSizeW;
        ymax = ymin + barSizeH;

        rectPrm.lineColor = YUV_COLOR_MAP[COLOR_INDEX_MAX-1-i];

        Draw2D_drawRect(pObj->draw2DHndl,
            xmin,
            ymin,
            xmax-xmin,
            ymax-ymin,
            &rectPrm
            );
    }

    sprintf(str, "%3.1fm", min);

    fontPrm.fontIdx = 13;

    Draw2D_drawString(pObj->draw2DHndl,
            startX,
            startY + fontProp.height + gap + gap + (COLOR_INDEX_MAX+1)*barSizeH,
            str,
            &fontPrm
            );
}

Void AlgorithmLink_objectDrawSfmPoints(AlgorithmLink_ObjectDrawObj *pObj)
{
    UInt32 i, colorIndex, color;
    UInt16 xmin, xmax, ymin, ymax, vx, vy;
    SFM_TI_output *pCurOut;
    float distance;
    float  maxZ4Visulization = 100.0;
    Draw2D_LinePrm rectPrm;
    AlgorithmLink_SfmOutput *pSfmOutput;

    if(pObj->pSfmOutput==NULL)
        return;

    pSfmOutput = pObj->pSfmOutput;

    Cache_inv(
               pSfmOutput,
               SFM_LINK_SFM_POINTS_BUF_SIZE,
               Cache_Type_ALLD,
               TRUE
             );

    rectPrm.lineSize = 2;
    rectPrm.lineColor = COLOR_RED;
    rectPrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;

    for(i=0; i<pSfmOutput->outNumPoints; i++)
    {
        pCurOut = &pSfmOutput->sfmOut[i];

        distance =
                pCurOut->point3dX*pCurOut->point3dX
            +   pCurOut->point3dY*pCurOut->point3dY
            +   pCurOut->point3dZ*pCurOut->point3dZ
                ;

        distance = sqrt(distance);

        if(distance > maxZ4Visulization)
            distance = maxZ4Visulization;

        if(distance < 0)
            distance = 0;

        colorIndex = ((distance / maxZ4Visulization) * COLOR_INDEX_MAX);

        if(colorIndex>=COLOR_INDEX_MAX)
            colorIndex = COLOR_INDEX_MAX-1;

        color = YUV_COLOR_MAP[colorIndex];

        vx = pCurOut->point2dX + SOF_PAD_PIXELS;
        vy = pCurOut->point2dY + SOF_PAD_PIXELS;

        rectPrm.lineColor = color;
        rectPrm.lineSize = 2;

        xmin = vx-2;
        ymin = vy-2;
        xmax = vx+2;
        ymax = vy+2;

        {
            Draw2D_drawRect(pObj->draw2DHndl,
                xmin,
                ymin,
                xmax-xmin,
                ymax-ymin,
                &rectPrm
                );
        }
    }

    #if 1
    AlgorithmLink_objectDrawSfmDistanceBar(pObj, 16, 232, 0, maxZ4Visulization);
    #endif

}

Void AlgorithmLink_objectDrawSofFlows(AlgorithmLink_ObjectDrawObj *pObj)
{
    Draw2D_LinePrm rectLinePrm, linePrm;
    strackInfo * trackInfo;

    UInt16 vx, vy, xmin, xmax, ymin, ymax;
    UInt16 numLines, i, j, minPt, maxPt, idx, startX, startY;

    if(pObj->pSofOutput==NULL)
        return;

    trackInfo = pObj->pSofOutput;

    startX  = startY = SOF_ALGLINK_PAD_PIXELS;

    rectLinePrm.lineSize = 2;
    rectLinePrm.lineColor = COLOR_RED;
    rectLinePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;

    linePrm.lineSize = 1;
    linePrm.lineColor = COLOR_GREEN;
    linePrm.lineColorFormat = SYSTEM_DF_YUV420SP_UV;

    Cache_inv(
               trackInfo,
               SOF_ALGLINK_FLOW_TRACK_POINTS_BUF_SIZE,
               Cache_Type_ALLD,
               TRUE
             );


    for(i = 0; i < pObj->algLinkCreateParams.sofMaxTrackPoints; i ++)
    {
        if(trackInfo[i].age > 0)
        {
            idx = trackInfo[i].age % MAX_NUM_FRAMES_TO_TRACK;
            vx = trackInfo[i].x[idx]/16 + startX;
            vy = trackInfo[i].y[idx]/16 + startY;

            vx = vx & (~1);
            vy = vy & (~1);

            xmin = vx-4;
            ymin = vy-4;
            xmax = vx+4;
            ymax = vy+4;

            Draw2D_drawRect(pObj->draw2DHndl,
                xmin,
                ymin,
                xmax-xmin,
                ymax-ymin,
                &rectLinePrm
                );

            numLines = (trackInfo[i].age + 1) > MAX_NUM_FRAMES_TO_TRACK ? MAX_NUM_FRAMES_TO_TRACK : (trackInfo[i].age+1);
            numLines = numLines-1;

            for(j = 0; j < numLines; j++)
            {
                minPt = (idx-j    + MAX_NUM_FRAMES_TO_TRACK) % MAX_NUM_FRAMES_TO_TRACK;
                maxPt = (idx-j - 1 + MAX_NUM_FRAMES_TO_TRACK) % MAX_NUM_FRAMES_TO_TRACK;
                xmin = trackInfo[i].x[minPt]/16 + startX;
                ymin = trackInfo[i].y[minPt]/16 + startY;

                xmin = xmin & (~1);
                ymin = ymin & (~1);

                xmax = trackInfo[i].x[maxPt]/16 + startX;
                ymax = trackInfo[i].y[maxPt]/16 + startY;

                xmax = xmax & (~1);
                ymax = ymax & (~1);

                Draw2D_drawLine(pObj->draw2DHndl,
                    xmin,
                    ymin,
                    xmax,
                    ymax,
                    &linePrm
                    );
            }
        }
    }
}

Int32 AlgorithmLink_objectDrawCopyInput(
                                        AlgorithmLink_ObjectDrawObj *pObj,
                                        System_VideoFrameCompositeBuffer *pCompBuffer,
                                        System_Buffer *pOutBuffer
                                                      )
{
    System_VideoFrameBuffer *pVidFrame = (System_VideoFrameBuffer *)pOutBuffer->payload;
    Utils_DmaCopyFill2D dmaPrm;
    Int32 status;


    dmaPrm.dataFormat   = SYSTEM_DF_YUV420SP_UV;
    dmaPrm.destAddr[0]  = (Ptr) pVidFrame->bufAddr[0];
    dmaPrm.destAddr[1]  = (Ptr) pVidFrame->bufAddr[1];
    dmaPrm.destPitch[0] = pObj->outputQInfo.queInfo.chInfo[0].pitch[0];
    dmaPrm.destPitch[1] = pObj->outputQInfo.queInfo.chInfo[0].pitch[1];
    dmaPrm.destStartX   = pObj->outputQInfo.queInfo.chInfo[0].startX;
    dmaPrm.destStartY   = pObj->outputQInfo.queInfo.chInfo[0].startY;
    dmaPrm.width        = pObj->outputQInfo.queInfo.chInfo[0].width;
    dmaPrm.height       = pObj->outputQInfo.queInfo.chInfo[0].height;
    dmaPrm.srcAddr[0]   = (Ptr) pCompBuffer->bufAddr[0][0];
    dmaPrm.srcAddr[1]   = (Ptr) pCompBuffer->bufAddr[1][0];
    dmaPrm.srcPitch[0]  = pObj->outputQInfo.queInfo.chInfo[0].pitch[0];
    dmaPrm.srcPitch[1]  = pObj->outputQInfo.queInfo.chInfo[0].pitch[1];
    dmaPrm.srcStartX    = pObj->algLinkCreateParams.imgFrameStartX;
    dmaPrm.srcStartY    = pObj->algLinkCreateParams.imgFrameStartY;

    status = Utils_dmaCopy2D(&pObj->copyFramesDmaObj,
                             &dmaPrm,
                             1);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Int32 clip_offst(int32_t input, int32_t max)
{
  Int32 output;
  output = (input >= (max-4)) ? (max - 4) : input;
  output = output < 4 ? 4 : output;
  return output;
}
/***************************************************************************/
/*  caffee output for detection of object follows the following format */
/*     ---------------     */
/*     |idx| contains|     */
/*     ---------------     */
/*     | 0 |  label  |     */
/*     | 1 |  scores |     */
/*     | 2 |  na     |     */
/*     | 3 |  xmin   |     */
/*     | 4 |  ymin   |     */
/*     | 5 |  xmax   |     */
/*     | 6 |  ymax   |     */
/*     ---------------     */
/************************************************************************/

Void AlgorithmLink_objectDrawSetMetaDataBuf(AlgorithmLink_ObjectDrawObj *pObj,
    System_VideoFrameCompositeBuffer *pCompositeBuffer)
{
    UInt32 chId, i;
    AlgorithmLink_ObjectDrawAlgId algId;
    Void *metaDataAddr;
    float *bboxPtr;
    UInt32  bidx,width,height,bufferOffset;
    pObj->pOdOutput = NULL;
    pObj->pClrOutput = NULL;
    pObj->pLdOutput = NULL;
    pObj->pSfmOutput = NULL;
    pObj->pSofOutput = NULL;

    for(i=0; i<pObj->algLinkCreateParams.numDrawAlg; i++)
    {
        algId = pObj->algLinkCreateParams.drawAlgId[i];

        chId = i+1;  /* +1, since CH0 is original input frame */

        metaDataAddr = NULL;

        if(chId<pCompositeBuffer->numFrames)
        {
            metaDataAddr = pCompositeBuffer->bufAddr[0][chId];
        }

        if(algId==ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_OD)
        {
            pObj->pOdOutput =
                    (TI_OD_outputList*)metaDataAddr;
        }
        else
        if(algId==ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_CLR)
        {
            pObj->pClrOutput =
                    (TI_OD_outputList*)metaDataAddr;
        }
        else
        if(algId==ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_LD)
        {
            pObj->pLdOutput =
                    (AlgorithmLink_LaneDetectOutput*)metaDataAddr;
        }
        else
        if(algId==ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SFM)
        {
            pObj->pSfmOutput =
                    (AlgorithmLink_SfmOutput*)metaDataAddr;
        }
        else
        if(algId==ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_SOF)
        {
            pObj->pSofOutput =
                    (strackInfo*)metaDataAddr;
        }
        else
        if(algId == ALGORITHM_LINK_OBJECT_DETECT_DRAW_ALG_TIDL_OD)
        {
            TI_OD_outputList *tempoutPutList;
            tempoutPutList = &pObj->TIDLOdOutput;

            /* Convert the tidl output to TI_OD_outputList format */
            tempoutPutList->numObjects = 0;
            /* Metadata is passed from algo in buffer */
            bufferOffset = *(UInt32*)(metaDataAddr);

            bboxPtr = (float *)((char *)metaDataAddr + (bufferOffset*4)+4);
            width = pCompositeBuffer->chInfo.width;
            height = pCompositeBuffer->chInfo.height;
            for(bidx = 0; bidx < 20; bidx++)
            {
              if ((bboxPtr[7 * bidx] != -1) &&
                    (bboxPtr[7 * bidx + 2] > pObj->algLinkCreateParams.scoreThreshold))
              {
                 Int32   label = bboxPtr[7 * bidx + 1];
                 Int32   xmin  = clip_offst((bboxPtr[7 * bidx + 3] * width), width);
                 Int32   ymin  = clip_offst((bboxPtr[7 * bidx + 4] * height), height);
                 Int32   xmax  = clip_offst((bboxPtr[7 * bidx + 5] * width), width);
                 Int32   ymax  = clip_offst((bboxPtr[7 * bidx + 6] * height), height);

                 tempoutPutList->objDesc[tempoutPutList->numObjects].objTag = 0;
                 tempoutPutList->objDesc[tempoutPutList->numObjects].objType = ((label - 1)%3);
                 tempoutPutList->objDesc[tempoutPutList->numObjects].objSubType = 1;
                 tempoutPutList->objDesc[tempoutPutList->numObjects].xPos = xmin;
                 tempoutPutList->objDesc[tempoutPutList->numObjects].yPos = ymin;
                 tempoutPutList->objDesc[tempoutPutList->numObjects].objWidth = xmax - xmin;
                 tempoutPutList->objDesc[tempoutPutList->numObjects].objHeight = ymax - ymin;
                 tempoutPutList->objDesc[tempoutPutList->numObjects].objScore = bboxPtr[7 * bidx + 2];
                 tempoutPutList->objDesc[tempoutPutList->numObjects].objScale =  1;
                 tempoutPutList->numObjects++;
              }
            }
            pObj->pOdOutput = tempoutPutList;
        }
    }
}

Int32 AlgorithmLink_objectDrawProcess(void * pObj)
{
    UInt32 bufId;
    Int32  status = SYSTEM_LINK_STATUS_SOK;
    Bool   bufDropFlag;
    AlgorithmLink_ObjectDrawObj           * pObjectDrawObj;
    AlgorithmLink_ObjectDrawCreateParams  * pLinkCreateParams;
    System_Buffer                         * pSysOutBuffer;
    System_Buffer                         * pSysInBuffer;
    System_VideoFrameBuffer               * pVideoBuffer;
    System_VideoFrameCompositeBuffer      * pCompositeBuffer;
    System_BufferList                       inputBufList;
    System_BufferList                       outputBufListReturn;
    System_BufferList                       inputBufListReturn;
    System_LinkStatistics                 * linkStatsInfo;
    System_LinkChInfo                     * outChInfo;

    pObjectDrawObj = (AlgorithmLink_ObjectDrawObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    linkStatsInfo = pObjectDrawObj->linkStatsInfo;
    UTILS_assert(NULL != linkStatsInfo);


    pLinkCreateParams = &pObjectDrawObj->algLinkCreateParams;

    if (pObjectDrawObj->isFirstFrameRecv == FALSE)
    {
        pObjectDrawObj->isFirstFrameRecv = TRUE;

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

            UTILS_assert(pSysInBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER);
            /*
             * The input buffer is a composite buffer consisting of two
             * channels. Channel 0 consists of video frame buffer while
             * channel1 consists of meta data.
             */
            pCompositeBuffer =
                   (System_VideoFrameCompositeBuffer *) pSysInBuffer->payload;

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
                pSysOutBuffer->srcTimestamp = pSysInBuffer->srcTimestamp;
                pSysOutBuffer->frameId = pSysInBuffer->frameId;
                pSysOutBuffer->linkLocalTimestamp = Utils_getCurGlobalTimeInUsec();

                outChInfo = &pObjectDrawObj->outputQInfo.queInfo.chInfo[0];

                pVideoBuffer    = (System_VideoFrameBuffer *)pSysOutBuffer->payload;

                Cache_inv(
                          pVideoBuffer->bufAddr[0],
                          outChInfo->pitch[0]*outChInfo->height,
                          Cache_Type_ALLD,
                          TRUE
                        );
                Cache_inv(
                          pVideoBuffer->bufAddr[1],
                          outChInfo->pitch[1]*outChInfo->height/2,
                          Cache_Type_ALLD,
                          TRUE
                        );

                status = AlgorithmLink_objectDrawCopyInput(
                                                        pObjectDrawObj,
                                                        pCompositeBuffer,
                                                        pSysOutBuffer
                                                      );
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                pObjectDrawObj->drawBufAddr[0] = (UInt32)pVideoBuffer->bufAddr[0];
                pObjectDrawObj->drawBufAddr[1] = (UInt32)pVideoBuffer->bufAddr[1];

                Draw2D_updateBufAddr(pObjectDrawObj->draw2DHndl, pObjectDrawObj->drawBufAddr);

                AlgorithmLink_objectDrawSetMetaDataBuf(pObjectDrawObj, pCompositeBuffer);
                if( pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_SOF )
                {
                    AlgorithmLink_objectDrawSofFlows(pObjectDrawObj);
                }
                if( pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_SFM )
                {
                    AlgorithmLink_objectDrawSfmPoints(pObjectDrawObj);
                }
                if( pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_LD )
                {
                    AlgorithmLink_objectDrawLanes2(pObjectDrawObj);
                }
                if( pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_CLR )
                {
                    AlgorithmLink_objectDrawClr(pObjectDrawObj);
                }
                if( (pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_PD)
                    ||
                    (pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_VD)
                    ||
                    (pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_TSR)
                    )
                {
                    AlgorithmLink_objectDrawObjects(pObjectDrawObj);
                }
                if( (pObjectDrawObj->algLinkCreateParams.drawOption & ALGORITHM_LINK_OBJECT_DETECT_DRAW_VD_NIGHT) )
                {
                    AlgorithmLink_objectDrawObjectsNight(pObjectDrawObj);
                }

                Utils_updateLatency(&linkStatsInfo->linkLatency,
                                    pSysOutBuffer->linkLocalTimestamp);
                Utils_updateLatency(&linkStatsInfo->srcToLinkLatency,
                                    pSysOutBuffer->srcTimestamp);

                linkStatsInfo->linkStats.chStats[0].inBufProcessCount++;
                linkStatsInfo->linkStats.chStats[0].outBufCount[0]++;

                /* Frame to be displayed will not have x y offset even in
                 * case of decoder output
                 */
                pVideoBuffer->chInfo.startX = 0;
                pVideoBuffer->chInfo.startY = 0;

                Cache_wb(
                          pVideoBuffer->bufAddr[0],
                          outChInfo->pitch[0]*outChInfo->height,
                          Cache_Type_ALLD,
                          TRUE
                        );

                Cache_wb(
                          pVideoBuffer->bufAddr[1],
                          outChInfo->pitch[1]*outChInfo->height/2,
                          Cache_Type_ALLD,
                          TRUE
                        );

                AlgorithmLink_putFullOutputBuffer(
                                                    pObj,
                                                    0,
                                                    pSysOutBuffer
                                                 );
                UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

                /*
                 * Informing next link that a new data has peen put for its
                 * processing
                 */
                System_sendLinkCmd(
                                    pLinkCreateParams->outQueParams.nextLink,
                                    SYSTEM_CMD_NEW_DATA,
                                    NULL

                                  );
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
                                  &bufDropFlag
                                 );
        }
    }
    return status;
}

Int32 AlgorithmLink_objectDrawControl(void * pObj,
                                               void * pControlParams)
{
    AlgorithmLink_ObjectDrawObj* pObjectDrawObj;
    AlgorithmLink_ControlParams         * pAlgLinkControlPrm;
    AlgorithmLink_ObjectDrawSetROIParams *pROIPrm;
    AlgorithmLink_ObjectDrawSetDrawParams *pDrawPrm;

    Int32                        status    = SYSTEM_LINK_STATUS_SOK;

    pObjectDrawObj = (AlgorithmLink_ObjectDrawObj *)
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
        case ALGORITHM_LINK_OBJECT_DRAW_CMD_SET_ROI:

            if(pAlgLinkControlPrm->size != sizeof(*pROIPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pROIPrm = (AlgorithmLink_ObjectDrawSetROIParams *)
                                    pControlParams;

                pObjectDrawObj->algLinkCreateParams.imgFrameStartX
                    = pROIPrm->imgFrameStartX;

                pObjectDrawObj->algLinkCreateParams.imgFrameStartY
                    = pROIPrm->imgFrameStartY;

                pObjectDrawObj->algLinkCreateParams.imgFrameWidth
                    = pROIPrm->imgFrameWidth;

                pObjectDrawObj->algLinkCreateParams.imgFrameHeight
                    = pROIPrm->imgFrameHeight;
            }
            break;

        case ALGORITHM_LINK_OBJECT_DRAW_CMD_SET_DRAW_PRMS:

            if(pAlgLinkControlPrm->size != sizeof(*pDrawPrm))
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pDrawPrm = (AlgorithmLink_ObjectDrawSetDrawParams *)
                                    pControlParams;

                pObjectDrawObj->algLinkCreateParams.drawOption
                    = pDrawPrm->drawOption;
            }
            break;

        case SYSTEM_CMD_PRINT_STATISTICS:
            AlgorithmLink_objectDrawPrintStatistics(
                                                             pObj,
                                                             pObjectDrawObj
                                                            );
            break;

        default:
            break;
    }

    return status;
}
Int32 AlgorithmLink_objectDrawStop(void * pObj)
{
    return 0;
}
Int32 AlgorithmLink_objectDrawDelete(void * pObj)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 bufId;
    AlgorithmLink_ObjectDrawObj                   * pObjectDrawObj;
    AlgorithmLink_ObjectDrawCreateParams    * pLinkCreateParams;
    System_VideoFrameBuffer                     * pVideoBuffer;

    pObjectDrawObj = (AlgorithmLink_ObjectDrawObj *)
                                AlgorithmLink_getAlgorithmParamsObj(pObj);

    status = Utils_linkStatsCollectorDeAllocInst(pObjectDrawObj->linkStatsInfo);
    UTILS_assert(status==0);

    pLinkCreateParams = &pObjectDrawObj->algLinkCreateParams;

    /*
     * Free link buffers
     */
    for (bufId = 0; bufId < pLinkCreateParams->numOutBuffers; bufId++)
    {
        pVideoBuffer  =   &pObjectDrawObj->videoBuffers[bufId];

        status = Utils_memFree(
                                UTILS_HEAPID_DDR_CACHED_SR,
                                pVideoBuffer->bufAddr[0],
                                pObjectDrawObj->outBufferSize_y +
                                 pObjectDrawObj->outBufferSize_uv
                               );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    }

    Utils_dmaDeleteCh(&pObjectDrawObj->copyFramesDmaObj);

    status = Draw2D_delete(pObjectDrawObj->draw2DHndl);

    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    Utils_memFree(
                       UTILS_HEAPID_DDR_CACHED_LOCAL,
                       pObjectDrawObj,
                       sizeof(AlgorithmLink_ObjectDrawObj)
                    );

    return status;
}

Int32 AlgorithmLink_objectDrawPrintStatistics(void *pObj,
                AlgorithmLink_ObjectDrawObj *pObjectDrawObj)
{
    UTILS_assert(NULL != pObjectDrawObj->linkStatsInfo);

    Utils_printLinkStatistics(&pObjectDrawObj->linkStatsInfo->linkStats,
                            "ALG_OBJECT_DRAW",
                            TRUE);

    Utils_printLatency("ALG_OBJECT_DRAW",
                       &pObjectDrawObj->linkStatsInfo->linkLatency,
                       &pObjectDrawObj->linkStatsInfo->srcToLinkLatency,
                        TRUE
                       );

    return SYSTEM_LINK_STATUS_SOK;
}

static double HSV_COLOR_MAP[COLOR_INDEX_MAX][3] = {
  1.0000,         0,         0,
  1.0000,    0.0938,         0,
  1.0000,    0.1875,         0,
  1.0000,    0.2813,         0,
  1.0000,    0.3750,         0,
  1.0000,    0.4688,         0,
  1.0000,    0.5625,         0,
  1.0000,    0.6563,         0,
  1.0000,    0.7500,         0,
  1.0000,    0.8438,         0,
  1.0000,    0.9375,         0,
  0.9688,    1.0000,         0,
  0.8750,    1.0000,         0,
  0.7813,    1.0000,         0,
  0.6875,    1.0000,         0,
  0.5938,    1.0000,         0,
  0.5000,    1.0000,         0,
  0.4063,    1.0000,         0,
  0.3125,    1.0000,         0,
  0.2188,    1.0000,         0,
  0.1250,    1.0000,         0,
  0.0313,    1.0000,         0,
  0,    1.0000,    0.0625,
  0,    1.0000,    0.1563,
  0,    1.0000,    0.2500,
  0,    1.0000,    0.3438,
  0,    1.0000,    0.4375,
  0,    1.0000,    0.5313,
  0,    1.0000,    0.6250,
  0,    1.0000,    0.7188,
  0,    1.0000,    0.8125,
  0,    1.0000,    0.9063,
  0,    1.0000,    1.0000,
  0,    0.9063,    1.0000,
  0,    0.8125,    1.0000,
  0,    0.7188,    1.0000,
  0,    0.6250,    1.0000,
  0,    0.5313,    1.0000,
  0,    0.4375,    1.0000,
  0,    0.3438,    1.0000,
  0,    0.2500,    1.0000,
  0,    0.1563,    1.0000,
  0,    0.0625,    1.0000,
  0.0313,         0,    1.0000,
  0.1250,         0,    1.0000,
  0.2188,         0,    1.0000,
  0.3125,         0,    1.0000,
  0.4063,         0,    1.0000,
  0.5000,         0,    1.0000,
  0.5938,         0,    1.0000,
  0.6875,         0,    1.0000,
  0.7813,         0,    1.0000,
  0.8750,         0,    1.0000,
  0.9688,         0,    1.0000,
  1.0000,         0,    0.9375,
  1.0000,         0,    0.8438,
  1.0000,         0,    0.7500,
  1.0000,         0,    0.6563,
  1.0000,         0,    0.5625,
  1.0000,         0,    0.4688,
  1.0000,         0,    0.3750,
  1.0000,         0,    0.2813,
  1.0000,         0,    0.1875,
  1.0000,         0,    0.0938,
};

void AlgorithmLink_objectDrawConvertHsvToYuv()
{
#define UCHAR_MAX   (0xFF)

    uint32_t  colorIndex,r,g,b,y,cb,cr;

    for(colorIndex=0; colorIndex<COLOR_INDEX_MAX; colorIndex++)
    {
        r = HSV_COLOR_MAP[colorIndex][0]*UCHAR_MAX;
        g = HSV_COLOR_MAP[colorIndex][1]*UCHAR_MAX;
        b = HSV_COLOR_MAP[colorIndex][2]*UCHAR_MAX;

        y  = (( (66 * r)  + (129 * g) + (25 * b)  + 128) >> 8) + 16;
        cb = ((-(38 * r)  - (74 * g)  + (112 * b) + 128) >> 8) + 128;
        cr = (( (112 * r) - (94 * g)  - (18 * b)  + 128) >> 8) + 128;

        y  =  y & UCHAR_MAX;
        cb = cb & UCHAR_MAX;
        cr = cr & UCHAR_MAX;

        YUV_COLOR_MAP[colorIndex] = ((y<<16) | (cb<<8) | (cr<<0));
    }
}
