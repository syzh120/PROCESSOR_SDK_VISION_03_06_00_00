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

#define RGB888_TO_RGB565(r,g,b)     ((((UInt32)(r>>3) & 0x1F) << 11) | (((UInt32)(g>>2) & 0x3F) << 5) | (((UInt32)(b>>3) & 0x1F)))

/**
 *******************************************************************************
 *
 * \brief Background Color of the Graphics Buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OF_BACKGROUND_COLOR (DRAW2D_TRANSPARENT_COLOR)

#define OF_FRAME_THICKNESS  (25)
#define OF_LUT_HEIGHT       (129)

Int32 GrpxSrcLink_drawOpticalFlowLayout(GrpxSrcLink_Obj *pObj)
{
    Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    GrpxSrcLink_CreateParams *createPrms = &pObj->createArgs;
    GrpxSrcLink_OpticalFlowParameters *ofPrms;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    System_LinkInfo captLinkInfo;
    UInt32 width = 0,height = 0;
    char loadString[GRPX_SRC_LINK_STR_SZ];

    /* fill full buffer with background color */
    region.color  = OF_BACKGROUND_COLOR;
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = 0;
    region.startY = 0;
    region.height = pObj->info.queInfo[0].chInfo[0].height;
    region.width  = pObj->info.queInfo[0].chInfo[0].width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    ofPrms = &createPrms->opticalFlowParams;

    switch(ofPrms->lutId)
    {
        default:
        case 0:
            bmpPrm.bmpIdx = DRAW2D_BMP_IDX_OPTFLOW_LUT_0;
            break;
        case 1:
            bmpPrm.bmpIdx = DRAW2D_BMP_IDX_OPTFLOW_LUT_1;
            break;
        case 2:
            bmpPrm.bmpIdx = DRAW2D_BMP_IDX_OPTFLOW_LUT_2;
            break;
    }
    Draw2D_drawBmp(pObj->draw2DHndl,
                   OF_FRAME_THICKNESS,
                   pObj->info.queInfo[0].chInfo[0].height - (OF_LUT_HEIGHT + OF_FRAME_THICKNESS),
                   &bmpPrm
                   );

    /* draw bitmap's */

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   OF_FRAME_THICKNESS,
                   OF_FRAME_THICKNESS,
                   &bmpPrm
                   );

    fontPrm.fontIdx = 2;

    /* draw resolution String */

    Draw2D_getFontProperty(&fontPrm, &fontProp);


    System_linkGetInfo(SYSTEM_LINK_ID_CAPTURE,&captLinkInfo);

    if(captLinkInfo.queInfo[0].chInfo[0].width == 1280)
    {
        width = 1280;
        height = 720;
    }
    else if(captLinkInfo.queInfo[0].chInfo[0].width == 1920)
    {
        width = 1920;
        height = 1080;
    }
    snprintf(loadString, GRPX_SRC_LINK_STR_SZ, "RESOLUTION : %d x %d", width, height);

    /* TODO : Get Resolution and FPS from OF Alg Plugin, instead of Hardcoding*/
    Draw2D_drawString(pObj->draw2DHndl,
                      (OF_FRAME_THICKNESS * 2 + OF_LUT_HEIGHT),
                      pObj->info.queInfo[0].chInfo[0].height - (OF_LUT_HEIGHT + OF_FRAME_THICKNESS),
                      loadString,
                      &fontPrm);
    return 0;
}

Int32 GrpxSrcLink_displayOpticalFlowDetectStats(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY;

    fontPrm.fontIdx = 7;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    startX = OF_FRAME_THICKNESS*2 + OF_LUT_HEIGHT ;
    startY = pObj->info.queInfo[0].chInfo[0].height - (OF_FRAME_THICKNESS + OF_LUT_HEIGHT / 2 + fontProp.height*2 + 8);

    GrpxSrcLink_drawCpuLoad(pObj,
            startX,
            startY,
            30,
            OF_LUT_HEIGHT/2,
            4,
            4,
            7
            );

    return 0;
}
