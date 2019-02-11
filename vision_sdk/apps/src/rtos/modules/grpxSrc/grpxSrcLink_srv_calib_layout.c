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
  ******************************************************************************
 * \file grpxSrcLink_sv_sof_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for
 *         2D Surround view + SOF demo on TDA3xx
 *
 * \version 0.0 (Oct 2013) : [NN] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "grpxSrcLink_priv.h"
#include <src/rtos/alg_plugins/autocalibration/include/svACDCommonDefs.h>

#define SRV_NUM_CORNER_PTS  (8U)
#define SRV_CORNERPT_SIZE   ((SRV_NUM_CORNER_PTS * 2U * 4U) + 1)
#define SRV_RECT_WIDTH      (10U)
#define SRV_RECT_HEIGHT     (10U)

/* The ROI parameters are defined based on the following resolution */
/*#if INPUT_480P
#define SRV_ROI_WIDTH       (1280U)
#define SRV_ROI_HEIGHT      (720U)
#elif INPUT_720P
#define SRV_ROI_WIDTH       (1280U)
#define SRV_ROI_HEIGHT      (720U)
#else
#define SRV_ROI_WIDTH       (1920U)
#define SRV_ROI_HEIGHT      (1080U)
#endif*/

static UInt32 gCapWidth;
static UInt32 gCapHeight;
static UInt32 gDisWidth;
static UInt32 gDisHeight;
static UInt32 gWinWidth;
static UInt32 gWinHeight;
static Int32 gPrevCornerPts[SRV_CORNERPT_SIZE] = {0};

Void getStringPosn(
            UInt32 winStartX,
            UInt32 winStartY,
            UInt32 winWidth,
            UInt32 winHeight,
            UInt32 stringLen,
            Draw2D_FontProperty *pFontProp,
            UInt32 *pStrX,
            UInt32 *pStrY)
{
    UInt32 winOfstX;
    UInt32 winOfstY;

    winOfstX = (winWidth/2) - (stringLen * pFontProp->width/2);
    winOfstY = winHeight - (2 * pFontProp->height);

    *pStrX = winOfstX + winStartX;
    *pStrY = winOfstY + winStartY;
}

Int32 GrpxSrcLink_drawSrvCalibLayout(
                    GrpxSrcLink_Obj *pObj,
                    System_LinkChInfo *pChInfo,
                    UInt32 capWidth,
                    UInt32 capHeight)
{
    GrpxSrcLink_CreateParams *pCreatePrms = &pObj->createArgs;
    UInt32 strStartX, strStartY;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    char string[128U];
    Draw2D_LinePrm linePrm;
    UInt32 firstStartX;
    UInt32 firstStartY;
    UInt32 firstWidth;
    UInt32 firstHeight;

    UInt32 secondStartX;
    UInt32 secondStartY;
    UInt32 secondWidth;
    UInt32 secondHeight;

    gCapWidth = capWidth;
    gCapHeight = capHeight;
    gDisWidth = pChInfo->width;
    gDisHeight = pChInfo->height;
    gWinWidth = gDisWidth/2;
    gWinHeight = gDisHeight/2;
    UInt32 firstROITop, firstROILeft, firstROIRight, firstROIBottom;
    UInt32 secondROITop, secondROILeft, secondROIRight, secondROIBottom;
    UInt32 srvROIWidth, srvROIHeight;

    fontPrm.fontIdx = 1U;
    Draw2D_getFontProperty(
            &fontPrm,
            &fontProp);

    strcpy(string,"CH 0:FRONT");
    getStringPosn(
            0U,
            0U,
            gWinWidth,
            gWinHeight,
            strlen(string),
            &fontProp,
            &strStartX,
            &strStartY);

    Draw2D_drawString(
            pObj->draw2DHndl,
            strStartX,
            strStartY,
            string,
            &fontPrm);

    strcpy(string,"CH 1:RIGHT");
    getStringPosn(
            gWinWidth,
            0U,
            gWinWidth,
            gWinHeight,
            strlen(string),
            &fontProp,
            &strStartX,
            &strStartY);

    Draw2D_drawString(
            pObj->draw2DHndl,
            strStartX,
            strStartY,
            string,
            &fontPrm);

    strcpy(string,"CH 2:BACK");
    getStringPosn(
            0U,
            gWinHeight,
            gWinWidth,
            gWinHeight,
            strlen(string),
            &fontProp,
            &strStartX,
            &strStartY);

    Draw2D_drawString(
            pObj->draw2DHndl,
            strStartX,
            strStartY,
            string,
            &fontPrm);

    strcpy(string,"CH 3:LEFT");
    getStringPosn(
            gWinWidth,
            gWinHeight,
            gWinWidth,
            gWinHeight,
            strlen(string),
            &fontProp,
            &strStartX,
            &strStartY);

    Draw2D_drawString(
            pObj->draw2DHndl,
            strStartX,
            strStartY,
            string,
            &fontPrm);

    /*  Calibration ROI */
    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineColor = 0xF800;
    linePrm.lineSize = 1;

    if (pCreatePrms->is2mp == TRUE)
    {
        srvROIWidth = 1920;
        srvROIHeight = 1080;
        firstROITop = 300;
        firstROIBottom = 1050;
        firstROILeft = 50;
        firstROIRight = 900;
        secondROITop = 300;
        secondROIBottom = 1050;
        secondROILeft = 950;
        secondROIRight = 1870;
    }
    else
    {
        srvROIWidth = 1280;
        srvROIHeight = 720;
        firstROITop = 150;
        firstROIBottom = 670;
        firstROILeft = 100;
        firstROIRight = 600;
        secondROITop = 150;
        secondROIBottom = 670;
        secondROILeft = 700;
        secondROIRight = 1200;
    }

    firstStartX = (firstROILeft * gWinWidth)/srvROIWidth;
    firstStartY = (firstROITop * gWinHeight)/srvROIHeight;
    firstWidth = ((firstROIRight - firstROILeft) * gWinWidth)/srvROIWidth;
    firstHeight = ((firstROIBottom - firstROITop) * gWinHeight)/srvROIHeight;

    secondStartX = (secondROILeft * gWinWidth)/srvROIWidth;
    secondStartY = (secondROITop * gWinHeight)/srvROIHeight;
    secondWidth = ((secondROIRight - secondROILeft) * gWinWidth)/srvROIWidth;
    secondHeight = ((secondROIBottom - secondROITop) * gWinHeight)/srvROIHeight;

    /* FRONT */
    /* Left ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            firstStartX,
            firstStartY,
            firstWidth,
            firstHeight,
            &linePrm);

    /* Right ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            secondStartX,
            secondStartY,
            secondWidth,
            secondHeight,
            &linePrm);

    /* RIGHT */
    /* Left ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            gWinWidth + firstStartX,
            firstStartY,
            firstWidth,
            firstHeight,
            &linePrm);

    /* Right ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            gWinWidth + secondStartX,
            secondStartY,
            secondWidth,
            secondHeight,
            &linePrm);

    /* BACK */
    /* Left ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            firstStartX,
            gWinHeight + firstStartY,
            firstWidth,
            firstHeight,
            &linePrm);

    /* Right ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            secondStartX,
            gWinHeight + secondStartY,
            secondWidth,
            secondHeight,
            &linePrm);

    /* LEFT */
    /* Left ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            gWinWidth + firstStartX,
            gWinHeight + firstStartY,
            firstWidth,
            firstHeight,
            &linePrm);

    /* Right ROI */
    Draw2D_drawRect(
            pObj->draw2DHndl,
            gWinWidth + secondStartX,
            gWinHeight + secondStartY,
            secondWidth,
            secondHeight,
            &linePrm);

    return 0;
}

Void scaleCornerPoints(
            Int32 origX,
            Int32 origY,
            UInt32 *pScaledX,
            UInt32 *pScaledY)
{
    *pScaledX = ((origX >> 4) * gWinWidth)/gCapWidth;
    *pScaledY = ((origY >> 4) * gWinHeight)/gCapHeight;
}

Int32 drawCornerPoints(
            GrpxSrcLink_Obj *pObj,
            UInt32 winStartX,
            UInt32 winStartY,
            UInt32 numPoints,
            Int32 *pPoint,
            Bool clear)
{
    UInt32 cnt;
    UInt32 color;
    Draw2D_RegionPrm region;
    UInt32 scaledX, scaledY;

    color = RGB888_TO_RGB565(160, 0, 0);

    for (cnt = 0;cnt < numPoints;cnt ++)
    {
        scaleCornerPoints(
                pPoint[cnt * 2],
                pPoint[cnt * 2 + 1],
                &scaledX,
                &scaledY);

        region.color  = color;
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = winStartX + scaledX - (SRV_RECT_WIDTH >> 1);
        region.startY = winStartY + scaledY - (SRV_RECT_HEIGHT >> 1);
        region.width = SRV_RECT_WIDTH;
        region.height  = SRV_RECT_HEIGHT;

        if (clear == TRUE)
        {
            Draw2D_clearRegion(
                    pObj->draw2DHndl,
                    region.startX,
                    region.startY,
                    region.width,
                    region.height);
        }
        else
        {
            Draw2D_fillRegion(
                    pObj->draw2DHndl,
                    &region);
        }
    }

    return 0;
}

Int32 GrpxSrcLink_displaySrvCalibStats(
                        GrpxSrcLink_Obj *pObj,
                        GrpxSrcLink_SrvCalibPrm *pSrvCalibPrm)
{
    Int32 *pCornerPoints;

#ifdef LINUX_BUILD
    /*
     *  Cache Invalidation is required only when the message is sent from
     *  A15 under Linux Build.
     */
    Cache_inv(
        (Ptr)pSrvCalibPrm,
        sizeof(GrpxSrcLink_SrvCalibPrm),
        Cache_Type_ALLD,
        TRUE);

    Cache_inv(
        (Ptr)pSrvCalibPrm->cornerPointsBuf,
        pSrvCalibPrm->cornerPointBufSize,
        Cache_Type_ALLD,
        TRUE);
#endif

    /*
     *  Erase the previous corner points
     */
    pCornerPoints = gPrevCornerPts;

    if (*pCornerPoints == 1)
    {
        pCornerPoints ++;

        // Front Cam
        drawCornerPoints(
                    pObj,
                    0U,
                    0U,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    TRUE);

        pCornerPoints += SRV_NUM_CORNER_PTS << 1;

        // Right Cam
        drawCornerPoints(
                    pObj,
                    gWinWidth,
                    0U,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    TRUE);

        pCornerPoints += SRV_NUM_CORNER_PTS << 1;

        // Back Cam
        drawCornerPoints(
                    pObj,
                    0U,
                    gWinHeight,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    TRUE);

        pCornerPoints += SRV_NUM_CORNER_PTS << 1;

        // Left Cam
        drawCornerPoints(
                    pObj,
                    gWinWidth,
                    gWinHeight,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    TRUE);
    }

    /*
     *  Draw new corner points
     */
    pCornerPoints = pSrvCalibPrm->cornerPointsBuf;

    if (*pCornerPoints == 1)
    {
        pCornerPoints ++;

        // Front Cam
        drawCornerPoints(
                    pObj,
                    0U,
                    0U,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    FALSE);

        pCornerPoints += SRV_NUM_CORNER_PTS << 1;

        // Right Cam
        drawCornerPoints(
                    pObj,
                    gWinWidth,
                    0U,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    FALSE);

        pCornerPoints += SRV_NUM_CORNER_PTS << 1;

        // Back Cam
        drawCornerPoints(
                    pObj,
                    0U,
                    gWinHeight,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    FALSE);

        pCornerPoints += SRV_NUM_CORNER_PTS << 1;

        // Left Cam
        drawCornerPoints(
                    pObj,
                    gWinWidth,
                    gWinHeight,
                    SRV_NUM_CORNER_PTS,
                    pCornerPoints,
                    FALSE);

        memcpy(
            gPrevCornerPts,
            pSrvCalibPrm->cornerPointsBuf,
            SRV_CORNERPT_SIZE << 2);
    }

    return 0;
}
