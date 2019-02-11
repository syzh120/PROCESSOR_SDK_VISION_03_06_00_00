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
 * \file grpxSrcLink_stereo_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for Surround view
 *         + Edge detect demo
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
#include <src/rtos/alg_plugins/autoremap/include/autoRemapCommonDefs.h>


#define REMAP_NUM_FEATURE_PTS  (SMALC_MAX_HARRIS_FEATURES)
#define NUM_ELEMENT_PER_PT     (4U)
#define REMAP_FEATUREPT_SIZE   ((REMAP_NUM_FEATURE_PTS * NUM_ELEMENT_PER_PT) + 1)
#define REMAP_RECT_WIDTH       (4U)
#define REMAP_RECT_HEIGHT      (4U)

static UInt32 gCapWidth;
static UInt32 gCapHeight;
static UInt32 gWinWidth;
static UInt32 gWinHeight;
static UInt32 gWinStartX;
static UInt32 gWinStartY;
static Int16 gPrevFeaturePts[REMAP_FEATUREPT_SIZE] = {0};


/**
 *******************************************************************************
 *
 * \brief Background Color of the Graphics Buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPARITY_BACKGROUND_COLOR ((UInt16)(RGB888_TO_RGB565(16,16,16)))

#define DISPARITY_FRAME_THICKNESS  (10)


Int32 GrpxSrcLink_drawStereoDisparityLayout(GrpxSrcLink_Obj *pObj)
{
    Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    Draw2D_FontPrm fontPrm;

    /* fill full buffer with background color */
    region.color  = DISPARITY_BACKGROUND_COLOR;
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = 0;
    region.startY = 0;
    region.height = pObj->info.queInfo[0].chInfo[0].height;
    region.width  = pObj->info.queInfo[0].chInfo[0].width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* fill transprenecy color in portions where video should be visible */

    /* Live camera Left */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.colorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;
    region.startX = 0;
    region.startY = 720;
    region.height = 360;
    region.width  = 640;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* Live camera Right */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.colorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;
    region.startX = 640;
    region.startY = 720;
    region.height = 360;
    region.width  = 640;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* Disparity Window */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.colorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;
    region.startX = 0;
    region.startY = 0;
    region.height = 720;
    region.width  = 1280;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* draw bitmap's */

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO_1;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   1600 +80,
                   DISPARITY_FRAME_THICKNESS,
                   &bmpPrm
                   );
    /* Color Bar */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_STEREO_COLORBAR_20x720;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   1300,
                   DISPARITY_FRAME_THICKNESS,
                   &bmpPrm
                   );

    /* String for Left Camera */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          100,
          720+DISPARITY_FRAME_THICKNESS,
          "  LEFT CAMERA  ",
          &fontPrm
          );

    /* String for Right Camera */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          640+100,
          720+DISPARITY_FRAME_THICKNESS,
          "  RIGHT CAMERA  ",
          &fontPrm
          );

    /* String for Disparity Map */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          500,
          DISPARITY_FRAME_THICKNESS,
          "  STEREO DISPARITY MAP ",
          &fontPrm
          );

    /* String for Far */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          1320,
          DISPARITY_FRAME_THICKNESS,
          "  FAR  ",
          &fontPrm
          );

    /* String for Near*/
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          1320,
          720-DISPARITY_FRAME_THICKNESS,
          "  NEAR  ",
          &fontPrm
          );

    return SYSTEM_LINK_STATUS_SOK;
}

Void GrpxSrcLink_displayStereoDisparityDrawCpuLoadBar(
                    GrpxSrcLink_Obj *pObj,
                    UInt32 cpuLoadInt,
                    UInt32 cpuLoadFract,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height
                )
{
    Draw2D_RegionPrm region;
    UInt32 color[2];
    UInt32 barHeight[2];

    color[0] = RGB888_TO_RGB565(40, 40, 40);
    color[1] = RGB888_TO_RGB565(0, 160, 0);

    if(cpuLoadFract>=5)
        cpuLoadInt++;

    barHeight[0] = (height * (100 - cpuLoadInt))/100;

    if(barHeight[0] > height)
        barHeight[0] = height;

    barHeight[1] = height - barHeight[0];

    /* fill in in active load color */
    region.color  = color[0];
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = startX;
    region.startY = startY;
    region.height = barHeight[0];
    region.width  = width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* fill active load color */
    region.color  = color[1];
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = startX;
    region.startY = startY + barHeight[0];
    region.height = barHeight[1];
    region.width  = width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

}

Int32 GrpxSrcLink_displayStereoDisparityStats(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;
    UInt32 procId;
    Utils_SystemLoadStats *loadStats;
    char loadString[GRPX_SRC_LINK_STR_SZ];
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY, startX1, startY1;
    UInt32 statsHeight;

    fontPrm.fontIdx = 3;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    statsHeight = pObj->info.queInfo[0].chInfo[0].height - 900;
    startY =  pObj->info.queInfo[0].chInfo[0].height - fontProp.height;
    startX =  pObj->info.queInfo[0].chInfo[0].width - 640 + 10;
    startX1 = pObj->info.queInfo[0].chInfo[0].width - 640 + 10;
    startY1 = 900 + DISPARITY_FRAME_THICKNESS;


    for (procId = 0; procId < SYSTEM_PROC_MAX; procId++)
    {
            loadStats = &pObj->statsDisplayObj.systemLoadStats[procId];

            if(Bsp_platformIsTda3xxFamilyBuild()
                &&
                (procId == SYSTEM_PROC_A15_0
                    ||
                 procId == SYSTEM_PROC_EVE2
                    ||
                 procId == SYSTEM_PROC_EVE3
                    ||
                 procId == SYSTEM_PROC_EVE4
                    ||
                 procId == SYSTEM_PROC_IPU2
                )
              )
            {
                /* These CPUs dont exist in TDA3xx */
                continue;
            }

            snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          System_getProcName(procId)
                          );

            if (SYSTEM_PROC_IPU1_0 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-0"
                          );
            }
            else if (SYSTEM_PROC_IPU2 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-2"
                          );
            }
            else if (SYSTEM_PROC_IPU1_1 == procId)
            {
#ifdef A15_TARGET_OS_LINUX
               /* In case of Linux build, VSDK do not use IPU1-1 and use the
                * same space in the GRPX for SGX load */
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "SGX "
                          );
               System_linkControl(
                   SYSTEM_LINK_ID_SGXFRMCPY_0,
                   SYSTEM_COMMON_CMD_GET_SGX_LOAD,
                   loadStats,
                   sizeof(Utils_SystemLoadStats),
                   TRUE);
#else
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-1"
                          );
#endif
            }
            else if (SYSTEM_PROC_A15_0 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "A15"
                          );
            }
            else
            {
                /*
                 * Avoid MISRA C Warnings
                 */
            }

            /* draw CPU name */
            Draw2D_clearString(pObj->draw2DHndl,
                      startX,
                      startY,
                      strlen(loadString),
                      &fontPrm
                      );

            Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      startY,
                      loadString,
                      &fontPrm
                      );

            GrpxSrcLink_displayStereoDisparityDrawCpuLoadBar
                (
                    pObj,
                    loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                    loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                    startX,
                    pObj->info.queInfo[0].chInfo[0].height - statsHeight + fontProp.height + DISPARITY_FRAME_THICKNESS*2,
                    30,
                    (statsHeight - DISPARITY_FRAME_THICKNESS) - (fontProp.height + DISPARITY_FRAME_THICKNESS)*2
                );

            /* draw CPU load as text */
            snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%02d.%d%%\n",
                          loadStats->totalLoadParams.integerValue,
                          loadStats->totalLoadParams.fractionalValue
                          );
            Draw2D_clearString(pObj->draw2DHndl,
                      startX1,
                      startY1,
                      strlen(loadString),
                      &fontPrm
                      );

            Draw2D_drawString(pObj->draw2DHndl,
                      startX1,
                      startY1,
                      loadString,
                      &fontPrm
                      );
           startX1 = startX1 + fontProp.width*5 + 10;
           startX = startX+fontProp.width*5 + 10;
    }
    return 0;
}

#if 0
Void getStringPosnStereo(
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

    //winOfstY = winHeight - (2 * pFontProp->height);
    winOfstY = winHeight + (2 * pFontProp->height); // write string below image

    *pStrX = winOfstX + winStartX;
    *pStrY = winOfstY + winStartY;
}
#endif

Int32 GrpxSrcLink_drawStereoCalibLayout(
        GrpxSrcLink_Obj *pObj,
        GrpxSrcLink_StereoCalibDisplayPrm pStereoCalibDisplayPrm)
{
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;

    gCapWidth = pStereoCalibDisplayPrm.stereoCalibCaptureWidth;
    gCapHeight = pStereoCalibDisplayPrm.stereoCalibCaptureHeight;
    gWinWidth = pStereoCalibDisplayPrm.stereoCalibDisplayWidth;
    gWinHeight = pStereoCalibDisplayPrm.stereoCalibDisplayHeight;
    gWinStartX = pStereoCalibDisplayPrm.stereoCalibDisplayStartX;
    gWinStartY = pStereoCalibDisplayPrm.stereoCalibDisplayStartY;

    fontPrm.fontIdx = 5;
    Draw2D_getFontProperty(
            &fontPrm,
            &fontProp);

    Draw2D_drawString(
            pObj->draw2DHndl,
            430, //strStartX,
            850, //strStartY,
            " LEFT ", //string,
            &fontPrm);

    Draw2D_drawString(
            pObj->draw2DHndl,
            1410, //strStartX,
            850,  //strStartY,
            " RIGHT ", //string,
            &fontPrm);

    return 0;
}

Void scaleRemapFeaturePoints(
            Int16 origX,
            Int16 origY,
            UInt32 *pScaledX,
            UInt32 *pScaledY)
{
    *pScaledX = (UInt32)(origX * gWinWidth/gCapWidth);
    *pScaledY = (UInt32)(origY * gWinHeight/gCapHeight);
}

Int32 drawRemapFeaturePoints(
            GrpxSrcLink_Obj *pObj,
            UInt32 lWinStartX,
            UInt32 lWinStartY,
            UInt32 rWinStartX,
            UInt32 rWinStartY,
            UInt32 numPoints,
            Int16 *pPoint,
            Bool clear)
{

    UInt32 cnt;
    UInt32 color;
    Draw2D_RegionPrm region;
    UInt32 scaledX, scaledY;

    color = RGB888_TO_RGB565(160, 0, 0);

    for (cnt = 0;cnt < numPoints;cnt ++)
    {

    	// left
    	scaleRemapFeaturePoints(
                pPoint[cnt * 4],
                pPoint[cnt * 4 + 1],
                &scaledX,
                &scaledY);

        region.color  = color;
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = lWinStartX + scaledX - (REMAP_RECT_WIDTH >> 1);
        region.startY = lWinStartY + scaledY - (REMAP_RECT_HEIGHT >> 1);
        region.width = REMAP_RECT_WIDTH;
        region.height  = REMAP_RECT_HEIGHT;


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

        // right
    	scaleRemapFeaturePoints(
                pPoint[cnt * 4 + 2],
                pPoint[cnt * 4 + 3],
                &scaledX,
                &scaledY);

        region.color  = color;
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = rWinStartX + scaledX - (REMAP_RECT_WIDTH >> 1);
        region.startY = rWinStartY + scaledY - (REMAP_RECT_HEIGHT >> 1);
        region.width = REMAP_RECT_WIDTH;
        region.height  = REMAP_RECT_HEIGHT;

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

Int32 GrpxSrcLink_displayStereoCalibStats(
                        GrpxSrcLink_Obj *pObj,
                        GrpxSrcLink_StereoCalibPrm *pStereoCalibPrm)
{

    Int16 *pFeaturePoints;
    Int32 numFeaturePts;

    Cache_inv(
        (Ptr)pStereoCalibPrm,
        sizeof(GrpxSrcLink_StereoCalibPrm),
        Cache_Type_ALLD,
        TRUE);

    Cache_inv(
        (Ptr)pStereoCalibPrm->featurePointBuf,
        pStereoCalibPrm->featurePointBufSize,
        Cache_Type_ALLD,
        TRUE);

    /*
     *  Erase the previous corner points
     */
    pFeaturePoints = gPrevFeaturePts;
    numFeaturePts = pFeaturePoints[0];

    Vps_printf("----- PREV numFeature:%d\n", numFeaturePts);
    /*
    Vps_printf("------gWinStartX:%d, gWinStartY:%d, gWinWidth:%d, Height:%d, gCapWidth:%d, gCapHeight:%d\n",
    	gWinStartX, gWinStartY,  gWinWidth, gWinHeight, gCapWidth, gCapHeight);
    */

    if (numFeaturePts > 0)
    {
    	pFeaturePoints ++;

    	// Draw left * right feature pts
        drawRemapFeaturePoints(
                    pObj,
                    gWinStartX,
                    gWinStartY,
                    gWinStartX + gWinWidth,
                    gWinStartY,
                    numFeaturePts,
                    pFeaturePoints,
                    TRUE);

    }

    /*
     *  Draw new corner points
     */
    pFeaturePoints = pStereoCalibPrm->featurePointBuf;
    numFeaturePts = pStereoCalibPrm->endIdx - pStereoCalibPrm->startIdx + 1;


    if (numFeaturePts > 0)
    {
    	pFeaturePoints += (pStereoCalibPrm->startIdx * NUM_ELEMENT_PER_PT);


        // Draw left * right feature pts
        drawRemapFeaturePoints(
                    pObj,
                    gWinStartX,
                    gWinStartY,
                    gWinStartX + gWinWidth,
                    gWinStartY,
                    numFeaturePts,
                    pFeaturePoints,
                    FALSE);

        gPrevFeaturePts[0] = numFeaturePts;

        memcpy(
            &gPrevFeaturePts[1],
            pFeaturePoints, //pStereoCalibPrm->featurePointBuf,
            numFeaturePts * NUM_ELEMENT_PER_PT * sizeof(Int16));
    }



    return 0;

}
