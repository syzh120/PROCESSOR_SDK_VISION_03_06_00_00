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
 * \file grpxSrcLink_sem_seg_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for
 *         TDA3x 2D 3D Surround view demo
 *
 * \version 0.0 (Feb 2016) : [Suj] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include "grpxSrcLink_priv.h"
#include <src/rtos/usecases/semSeg/chains_semSeg.h>

/*******************************************************************************
 *  FUNCTION PROTOTYPES
 *******************************************************************************
 */
#define GAP1        (10)
#define GAP2        (32)

/**
 *******************************************************************************
 *
 * \brief Background Color of the Graphics Buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
Int32 GrpxSrcLink_drawSemSegLayout(
                    GrpxSrcLink_Obj *pObj,
                    UInt32 capWidth,
                    UInt32 capHeight)
{
    Draw2D_BmpPrm bmpPrm;
    Draw2D_BmpProperty bmpProp;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    Draw2D_RegionPrm region;
    char string[128U];
    char segStrings[4][128] = {"ROAD","PEDESTRIAN","ROAD SIGN","VEHICLE"};
    UInt32 segLegendWidth, segLegendStartX, segLegendStartY;

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO_1;
    Draw2D_getBmpProperty(&bmpPrm, &bmpProp);
    Draw2D_drawBmp(pObj->draw2DHndl,
                   GAP2,
                   (pObj->info.queInfo[0].chInfo[0].height - \
                                                    (bmpProp.height + GAP2)),
                   &bmpPrm);

    /* Semantic Segmentation String */
    fontPrm.fontIdx = 4;
    Draw2D_getFontProperty(&fontPrm, &fontProp);
    sprintf(string,"SEMANTIC SEGMENTATION");
    Draw2D_drawString(
                pObj->draw2DHndl,
                (pObj->info.queInfo[0].chInfo[0].width - \
                                        (fontProp.width * strlen(string)))/2,
                GAP2,
                string,
                &fontPrm);

    /* Segments Legend */
    fontPrm.fontIdx = 2;
    Draw2D_getFontProperty(&fontPrm, &fontProp);

    segLegendWidth = \
    fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[0])) + GAP2 + \
    fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[1])) + GAP2 + \
    fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[2])) + GAP2 + \
    fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[3])) + GAP2;

    segLegendStartX = \
        (pObj->info.queInfo[0].chInfo[0].width - segLegendWidth)/2;
    segLegendStartY = \
        (pObj->info.queInfo[0].chInfo[0].height - (fontProp.height + GAP2));

    /* Segment 1 */
    region.color = \
    RGB888_TO_RGB565(PALETTE_ROAD_RED, PALETTE_ROAD_GREEN, PALETTE_ROAD_BLUE);
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = segLegendStartX;
    region.startY = segLegendStartY;
    region.width = fontProp.height;
    region.height = fontProp.height;

    Draw2D_fillRegion(pObj->draw2DHndl, &region);

    Draw2D_drawString(
                pObj->draw2DHndl,
                segLegendStartX + fontProp.height + GAP1,
                segLegendStartY,
                segStrings[0],
                &fontPrm);

    segLegendStartX += \
        fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[0])) + GAP2;

    /* Segment 2 */
    region.color = \
    RGB888_TO_RGB565(PALETTE_PED_RED, PALETTE_PED_GREEN, PALETTE_PED_BLUE);
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = segLegendStartX;
    region.startY = segLegendStartY;
    region.width = fontProp.height;
    region.height = fontProp.height;

    Draw2D_fillRegion(pObj->draw2DHndl, &region);

    Draw2D_drawString(
                pObj->draw2DHndl,
                segLegendStartX + fontProp.height + GAP1,
                segLegendStartY,
                segStrings[1],
                &fontPrm);

    segLegendStartX += \
        fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[1])) + GAP2;

    /* Segment 3 */
    region.color = \
    RGB888_TO_RGB565(PALETTE_SIGN_RED, PALETTE_SIGN_GREEN, PALETTE_SIGN_BLUE);
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = segLegendStartX;
    region.startY = segLegendStartY;
    region.width = fontProp.height;
    region.height = fontProp.height;

    Draw2D_fillRegion(pObj->draw2DHndl, &region);

    Draw2D_drawString(
                pObj->draw2DHndl,
                segLegendStartX + fontProp.height + GAP1,
                segLegendStartY,
                segStrings[2],
                &fontPrm);

    segLegendStartX += \
        fontProp.height + GAP1 + (fontProp.width * strlen(segStrings[2])) + GAP2;

    /* Segment 4 */
    region.color = \
    RGB888_TO_RGB565(PALETTE_VEH_RED, PALETTE_VEH_GREEN, PALETTE_VEH_BLUE);
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = segLegendStartX;
    region.startY = segLegendStartY;
    region.width = fontProp.height;
    region.height = fontProp.height;

    Draw2D_fillRegion(pObj->draw2DHndl, &region);

    Draw2D_drawString(
                pObj->draw2DHndl,
                segLegendStartX + fontProp.height + GAP1,
                segLegendStartY,
                segStrings[3],
                &fontPrm);

    return SYSTEM_LINK_STATUS_SOK;
}

