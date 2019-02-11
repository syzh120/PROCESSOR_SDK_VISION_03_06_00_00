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
 * \file grpxSrcLink_OF_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for Optical Flow
 *         demo
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

#define TI_LOGO_START_X     (10)
#define TI_LOGO_START_Y     (10)

#define CPU_BAR_WIDTH       (30)
#define CPU_BAR_HEIGHT      (80)

Int32 GrpxSrcLink_drawPdTsrLdSofStereoLayout(GrpxSrcLink_Obj *pObj)
{
    Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    char loadString[GRPX_SRC_LINK_STR_SZ];
    Int32 startX;

    /* fill full buffer with black color */
    region.color  = RGB888_TO_RGB565(8,8,8);
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = 0;
    region.startY = 0;
    region.height = pObj->info.queInfo[0].chInfo[0].height;
    region.width  = pObj->info.queInfo[0].chInfo[0].width;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* fill windows in buffer with transperency color */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.colorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;
    region.startX = 160;
    region.startY = 0;
    region.height = 900;
    region.width  = 1600;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* fill windows in buffer with transperency color */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.colorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;
    region.startX = 160+800+60;
    region.startY = 900;
    region.height = 180;
    region.width  = 320;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.colorFormat = DRAW2D_TRANSPARENT_COLOR_FORMAT;
    region.startX = 160+800+60+320+40;
    region.startY = 900;
    region.height = 180;
    region.width  = 320;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);


    /* draw bitmap's */

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   TI_LOGO_START_X,
                   TI_LOGO_START_Y,
                   &bmpPrm
                   );

    fontPrm.fontIdx = 5;

    /* draw algorithm name String */

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ," PEDESTRIAN DETECT + TRAFFIC SIGN RECOGNITION ");

    startX = 160 + (800 - strlen(loadString)*fontProp.width)/2;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      5,
                      loadString,
                      &fontPrm);

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ," LANE DETECT ");

    startX = 160 + 800 + (800 - strlen(loadString)*fontProp.width)/2;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      5,
                      loadString,
                      &fontPrm);

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ," SPARSE OPTICAL FLOW ( MOTION ) ");

    startX = 160 + (800 - strlen(loadString)*fontProp.width)/2;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      450+5,
                      loadString,
                      &fontPrm);

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ," STEREO DISPARITY MAP ( DEPTH ) ");

    startX = 160 + 800 + (800 - strlen(loadString)*fontProp.width)/2;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      450+5,
                      loadString,
                      &fontPrm);

    fontPrm.fontIdx = 5;

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ," LEFT CAMERA ");

    startX = 160 + 800 + 60 + (320 - strlen(loadString)*fontProp.width)/2;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      900+5,
                      loadString,
                      &fontPrm);

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ," RIGHT CAMERA ");

    startX = 160 + 800 + 60 + 320 + 40 + (320 - strlen(loadString)*fontProp.width)/2;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      900+5,
                      loadString,
                      &fontPrm);

    /* Color Bar */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_STEREO_COLORBAR_35x450;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   160 + 800*2 + 20,
                   450,
                   &bmpPrm
                   );

    fontPrm.fontIdx = 7;

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ,"FAR");

    startX = 160 + 1600 + 20 + 20 + 10;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      450,
                      loadString,
                      &fontPrm);

    snprintf(loadString, GRPX_SRC_LINK_STR_SZ,"NEAR");

    startX = 160 + 1600 + 20 + 20 + 10;
    if(startX<0)
        startX = 0;

    Draw2D_drawString(pObj->draw2DHndl,
                      startX,
                      880,
                      loadString,
                      &fontPrm);

    return 0;
}

Int32 GrpxSrcLink_displayPdTsrLdSofStereoStats(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY;

    fontPrm.fontIdx = 5;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    startX = 160;
    startY = pObj->info.queInfo[0].chInfo[0].height - (TI_LOGO_START_Y + CPU_BAR_HEIGHT + fontProp.height*2 + 8);

    GrpxSrcLink_drawCpuLoad(pObj,
            startX,
            startY,
            CPU_BAR_WIDTH,
            CPU_BAR_HEIGHT,
            4,
            4,
            fontPrm.fontIdx
            );

    return 0;
}
