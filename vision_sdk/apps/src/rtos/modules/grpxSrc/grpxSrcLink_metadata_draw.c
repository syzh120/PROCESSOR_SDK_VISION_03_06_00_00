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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "grpxSrcLink_priv.h"

#define ULTRASONIC_LAYOUT_CLIP_TOP       (100)
#define ULTRASONIC_LAYOUT_CLIP_BOTTOM    ( 75)
/* below co-ordinates are relative to surround view window*/
#define ULTRASONIC_LAYOUT_CLIP_CENTER_X  (326)
#define ULTRASONIC_LAYOUT_CLIP_CENTER_Y  (329)
#define ULTRASONIC_LAYOUT_CLIP_CENTER_W  (228) /* this MUST match the jeep width */
#define ULTRASONIC_LAYOUT_CLIP_CENTER_H  (432) /* this MUST match the jeep height */

Int32 GrpxSrcLink_drawUltrasonicResults(GrpxSrcLink_Obj *pObj, System_MetaDataBuffer *pMetaBuffer)
{
    GrpxSrcLink_MetaDataDrawObj *pMetaDataDrawObj;
    Utils_DmaCopyFill2D dmaPrm;
    Int32 status;
    UInt16 startX, startY, winWidth, winHeight, displayWidth, displayHeight;

    pMetaDataDrawObj = &pObj->metaDataDrawObj;

    if(pMetaBuffer && pMetaBuffer->numMetaDataPlanes==1)
    {
        /* there can be only one plane  for overlay data */

        /* check if drawing area is within display are, else dont draw */

        startX    = pObj->createArgs.ultrasonicParams.windowStartX;
        startY    = pObj->createArgs.ultrasonicParams.windowStartY;
        winWidth  = pObj->createArgs.ultrasonicParams.windowWidth;
        winHeight = pObj->createArgs.ultrasonicParams.windowHeight;
        displayWidth  = pObj->info.queInfo[0].chInfo[0].width;
        displayHeight = pObj->info.queInfo[0].chInfo[0].height;

        if(startX + winWidth <= displayWidth
               &&
            startY + winHeight <= displayHeight
               &&
            pObj->createArgs.grpxBufInfo.dataFormat ==
                SYSTEM_DF_BGRA16_4444
               &&
            ULTRASONIC_LAYOUT_CLIP_CENTER_X + ULTRASONIC_LAYOUT_CLIP_CENTER_W <= winWidth
               &&
            ULTRASONIC_LAYOUT_CLIP_CENTER_Y + ULTRASONIC_LAYOUT_CLIP_CENTER_H <= winHeight
               &&
            ULTRASONIC_LAYOUT_CLIP_TOP <= ULTRASONIC_LAYOUT_CLIP_CENTER_Y
               &&
            (Int32)(displayHeight - ULTRASONIC_LAYOUT_CLIP_BOTTOM) >= (ULTRASONIC_LAYOUT_CLIP_CENTER_Y+ULTRASONIC_LAYOUT_CLIP_CENTER_H)
            )
        {
            /* Now DMA from this buffer to Grpx Buffer */

            /* DMA in 4 blocks such that it does not overlap
             * the surround view logo, jeep image and text
             */

            /* Block 0 - top */
            dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
            dmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
            dmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
            dmaPrm.destAddr[1]  = NULL;
            dmaPrm.destPitch[1] = 0;
            dmaPrm.srcStartX    = 0;
            dmaPrm.srcStartY    = ULTRASONIC_LAYOUT_CLIP_TOP;
            dmaPrm.destStartX   = startX + dmaPrm.srcStartX;
            dmaPrm.destStartY   = startY + dmaPrm.srcStartY;
            dmaPrm.width        = winWidth;
            dmaPrm.height       = ULTRASONIC_LAYOUT_CLIP_CENTER_Y - dmaPrm.srcStartY;
            dmaPrm.srcAddr[0]   = (Ptr) pMetaBuffer->bufAddr[0];
            dmaPrm.srcPitch[0]  = dmaPrm.width*2; /* assuming 2 bytes per pixel */
            dmaPrm.srcAddr[1]   = NULL;
            dmaPrm.srcPitch[1]  = 0;

            status = Utils_dmaCopy2D(&pMetaDataDrawObj->dmaObj,
                                     &dmaPrm,
                                     1);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            /* Block 1 - left */
            dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
            dmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
            dmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
            dmaPrm.destAddr[1]  = NULL;
            dmaPrm.destPitch[1] = 0;
            dmaPrm.srcStartX    = 0;
            dmaPrm.srcStartY    = ULTRASONIC_LAYOUT_CLIP_CENTER_Y;
            dmaPrm.destStartX   = startX + dmaPrm.srcStartX;
            dmaPrm.destStartY   = startY + dmaPrm.srcStartY;
            dmaPrm.width        = ULTRASONIC_LAYOUT_CLIP_CENTER_X;
            dmaPrm.height       = ULTRASONIC_LAYOUT_CLIP_CENTER_H;
            dmaPrm.srcAddr[0]   = (Ptr) pMetaBuffer->bufAddr[0];
            dmaPrm.srcPitch[0]  = dmaPrm.width*2; /* assuming 2 bytes per pixel */
            dmaPrm.srcAddr[1]   = NULL;
            dmaPrm.srcPitch[1]  = 0;

            status = Utils_dmaCopy2D(&pMetaDataDrawObj->dmaObj,
                                     &dmaPrm,
                                     1);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

            /* Block 2 - right */
            dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
            dmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
            dmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
            dmaPrm.destAddr[1]  = NULL;
            dmaPrm.destPitch[1] = 0;
            dmaPrm.srcStartX    = ULTRASONIC_LAYOUT_CLIP_CENTER_X + ULTRASONIC_LAYOUT_CLIP_CENTER_W;
            dmaPrm.srcStartY    = ULTRASONIC_LAYOUT_CLIP_CENTER_Y;
            dmaPrm.destStartX   = startX + dmaPrm.srcStartX;
            dmaPrm.destStartY   = startY + dmaPrm.srcStartY;
            dmaPrm.width        = winWidth - dmaPrm.srcStartX;
            dmaPrm.height       = ULTRASONIC_LAYOUT_CLIP_CENTER_H;
            dmaPrm.srcAddr[0]   = (Ptr) pMetaBuffer->bufAddr[0];
            dmaPrm.srcPitch[0]  = dmaPrm.width*2; /* assuming 2 bytes per pixel */
            dmaPrm.srcAddr[1]   = NULL;
            dmaPrm.srcPitch[1]  = 0;

            status = Utils_dmaCopy2D(&pMetaDataDrawObj->dmaObj,
                                     &dmaPrm,
                                     1);

            /* Block 3 - bottom */
            dmaPrm.dataFormat   = SYSTEM_DF_RAW16;
            dmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
            dmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
            dmaPrm.destAddr[1]  = NULL;
            dmaPrm.destPitch[1] = 0;
            dmaPrm.srcStartX    = 0;
            dmaPrm.srcStartY    = ULTRASONIC_LAYOUT_CLIP_CENTER_Y + ULTRASONIC_LAYOUT_CLIP_CENTER_H;
            dmaPrm.destStartX   = startX + dmaPrm.srcStartX;
            dmaPrm.destStartY   = startY + dmaPrm.srcStartY;
            dmaPrm.width        = winWidth;
            dmaPrm.height       = winHeight - dmaPrm.srcStartY - ULTRASONIC_LAYOUT_CLIP_BOTTOM;
            dmaPrm.srcAddr[0]   = (Ptr) pMetaBuffer->bufAddr[0];
            dmaPrm.srcPitch[0]  = dmaPrm.width*2; /* assuming 2 bytes per pixel */
            dmaPrm.srcAddr[1]   = NULL;
            dmaPrm.srcPitch[1]  = 0;

            status = Utils_dmaCopy2D(&pMetaDataDrawObj->dmaObj,
                                     &dmaPrm,
                                     1);

            UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        }
    }

    return 0;
}

Int32 GrpxSrcLink_drawMetaDataResultsCreate(GrpxSrcLink_Obj *pObj)
{
    Int32 status;

    Utils_DmaChCreateParams dmaPrm;

    memset(&pObj->metaDataDrawObj, 0, sizeof(pObj->metaDataDrawObj));
    pObj->metaDataDrawObj.isFirstTime = TRUE;
    pObj->metaDataDrawObj.startTime = 0;
    pObj->metaDataDrawObj.refreshInterval = 34; /* in msecs */

    Utils_DmaChCreateParams_Init(&dmaPrm);

    status = Utils_dmaCreateCh(&pObj->metaDataDrawObj.dmaObj, &dmaPrm);
    UTILS_assert(status==0);

    return status;
}

Int32 GrpxSrcLink_drawMetaDataResultsDelete(GrpxSrcLink_Obj *pObj)
{
    Int32 status;

    status = Utils_dmaDeleteCh(&pObj->metaDataDrawObj.dmaObj);

    UTILS_assert(status==0);

    return status;
}

Int32 GrpxSrcLink_drawMetaDataResultsRun(GrpxSrcLink_Obj *pObj)
{
    GrpxSrcLink_MetaDataDrawObj *pMetaDataDrawObj;
    UInt32 elaspedTime;
    System_BufferList bufferList;
    System_Buffer *pBuffer;
    System_MetaDataBuffer *pMetaBuffer;

    pMetaDataDrawObj = &pObj->metaDataDrawObj;

    if(pMetaDataDrawObj->isFirstTime)
    {
        pMetaDataDrawObj->isFirstTime = FALSE;
        pMetaDataDrawObj->startTime = Utils_getCurTimeInMsec();

        return 0;
    }

    elaspedTime = Utils_getCurTimeInMsec() - pMetaDataDrawObj->startTime;

    if(elaspedTime < pMetaDataDrawObj->refreshInterval)
    {
        /* Not yet time to draw */
        return 0;
    }

    /* now draw */
    pMetaDataDrawObj->startTime = Utils_getCurTimeInMsec();

    System_getLinksFullBuffers(
        pObj->createArgs.inQueParams.prevLinkId,
        pObj->createArgs.inQueParams.prevLinkQueId,
        &bufferList
        );

    if(bufferList.numBuf)
    {
        /* pick last buffer or latest buffer to draw */
        pBuffer = bufferList.buffers[bufferList.numBuf-1];

        if(pBuffer
            && pBuffer->bufType == SYSTEM_BUFFER_TYPE_METADATA
            )
        {
            pMetaBuffer = (System_MetaDataBuffer*)pBuffer->payload;

            if (pObj->createArgs.ultrasonicParams.enable)
            {
                GrpxSrcLink_drawUltrasonicResults(pObj, pMetaBuffer);
            }
        }

        System_putLinksEmptyBuffers(
            pObj->createArgs.inQueParams.prevLinkId,
            pObj->createArgs.inQueParams.prevLinkQueId,
            &bufferList
            );
    }

    return 0;
}

