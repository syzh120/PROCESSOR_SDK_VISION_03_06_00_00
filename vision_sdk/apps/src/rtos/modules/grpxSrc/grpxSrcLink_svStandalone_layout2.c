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
 * \file grpxSrcLink_sved_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for
 *         3D Surround view demo
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


/**
 *******************************************************************************
 *
 * \brief Background Color of the Graphics Buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SVED_BACKGROUND_COLOR ((UInt16)(RGB888_TO_RGB565(8,8,8)))

#define SVED_FRAME_THICKNESS  (10)


Int32 GrpxSrcLink_drawSurroundViewStandaloneLayout2(GrpxSrcLink_Obj *pObj,
                                                    UInt32 disablePreview)
{
    Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    Draw2D_FontPrm fontPrm;

    /* fill full buffer with background color */
    region.color  = SVED_BACKGROUND_COLOR;
    region.startX = 0;
    region.startY = 0;
    region.height = pObj->info.queInfo[0].chInfo[0].height;
    region.width  = pObj->info.queInfo[0].chInfo[0].width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* Surround view video */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.startX = 0;
    region.startY = 0;
    region.height = 1080;
    region.width  = 1920;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* draw bitmap's */

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO_1;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   25,
                   SVED_FRAME_THICKNESS,
                   &bmpPrm
                   );

    /* Surround view logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_SURROUND_VIEW;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   520+SVED_FRAME_THICKNESS+80,
                   0,
                   &bmpPrm
                   );

    if (BSP_PLATFORM_SOC_ID_TDA2XX == Bsp_platformGetSocId())
    {
        /* TDA2x logo */
        bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TDA2X;
        Draw2D_drawBmp(pObj->draw2DHndl,
                    520+SVED_FRAME_THICKNESS+80  -75 + 880 - 240,
                    0+95,
                    &bmpPrm
                    );
    }

    /* String for input resolution / frame-rate etc */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          200 - 120 + 15,
          "INPUT RESOLUTION: 1920x1080",
          &fontPrm
          );

    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          200 - 120 + 15 + 30,
          "FRAME-RATE: 30fps   ",
          &fontPrm
          );

    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          200 - 120 + 15 + 30*2,
          "   NETWORK: FPDLink ",
          &fontPrm
          );

    /* String for output resolution */
    fontPrm.fontIdx = 4;
    Draw2D_drawString(pObj->draw2DHndl,
          120+SVED_FRAME_THICKNESS+80,
          pObj->info.queInfo[0].chInfo[0].height - 120 + 15 + 30,
          "BOWL VIEW: 960x1080",
          &fontPrm
          );

    /* String for output resolution */
    fontPrm.fontIdx = 4;
    Draw2D_drawString(pObj->draw2DHndl,
          100+1020+SVED_FRAME_THICKNESS+80,
          pObj->info.queInfo[0].chInfo[0].height - 120 + 15 + 30,
          "FRONT VIEW: 960x1080",
          &fontPrm
          );

    return 0;
}
