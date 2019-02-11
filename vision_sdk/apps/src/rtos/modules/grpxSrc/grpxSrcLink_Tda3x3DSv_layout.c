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

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
  ******************************************************************************
 * \file grpxSrcLink_Tda3x3DSv_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for
 *         TDA3x 3D Surround view demo
 *
 * \version 0.0 (Feb 2016) : [Suj] First version
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


Int32 GrpxSrcLink_drawTDA3x3DSVLayout(GrpxSrcLink_Obj *pObj)
{
    Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    Draw2D_FontPrm fontPrm;
    GrpxSrcLink_CreateParams *pCreatePrms = &pObj->createArgs;
    char string[128U];

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

    if (pObj->createArgs.enableJeepOverlay == TRUE)
    {
        /* Jeep Image */
        /* TODO : Change Co-ordinates as per the requirement */
        bmpPrm.bmpIdx = DRAW2D_BMP_IDX_JEEP_IMAGE_TRUESCALE;
        Draw2D_drawBmp(pObj->draw2DHndl,
                    (326+520), //520 comes from layout
                    (324+5), //5 comes from layout
                    &bmpPrm
                    );
    }

    /* String for input resolution / frame-rate etc */
    fontPrm.fontIdx = 5;
    if (SYSTEM_STD_WXGA_30 == pCreatePrms->tda3x3DSvSrcResolution)
    {
        Draw2D_drawString(pObj->draw2DHndl,
              25,
              200 - 120 + 15,
              "RESOLUTION: 1280x800",
              &fontPrm
              );
    }
    else
    {
        Draw2D_drawString(pObj->draw2DHndl,
              25,
              200 - 120 + 15,
              "RESOLUTION: 1280x720",
              &fontPrm
              );
    }

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
    sprintf(string,"RESOLUTION: %3dx%3d",\
                pCreatePrms->displaySrv3D.srvOutWidth,
                pCreatePrms->displaySrv3D.srvOutHeight);
    Draw2D_drawString(pObj->draw2DHndl,
          100+520+SVED_FRAME_THICKNESS+80,
          pObj->info.queInfo[0].chInfo[0].height - 120 + 15 + 30,
          string,
          &fontPrm
          );

    return SYSTEM_LINK_STATUS_SOK;
}

Void GrpxSrcLink_displayTDA3x3DSVDrawCpuLoadBar(
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
    region.startX = startX;
    region.startY = startY;
    region.height = barHeight[0];
    region.width  = width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* fill active load color */
    region.color  = color[1];
    region.startX = startX;
    region.startY = startY + barHeight[0];
    region.height = barHeight[1];
    region.width  = width;

    Draw2D_fillRegion(pObj->draw2DHndl,&region);

}

Int32 GrpxSrcLink_displayTDA3x3DSVStats(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;
    UInt32 procId;
    Utils_SystemLoadStats *loadStats;
    char loadString[GRPX_SRC_LINK_STR_SZ];
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY, startX1, startY1;
    UInt32 statsHeight;
    Bsp_PlatformSocId socId;

    socId = Bsp_platformGetSocId();

    fontPrm.fontIdx = 3;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    statsHeight = 180;
    startY =  200 - fontProp.height;
    startX =  pObj->info.queInfo[0].chInfo[0].width - 520;
    startX1 = pObj->info.queInfo[0].chInfo[0].width - 520;
    startY1 = 20 + SVED_FRAME_THICKNESS;


    for (procId = 0; ((procId < SYSTEM_PROC_MAX) &&
                      (BSP_PLATFORM_SOC_ID_TDA3XX == socId)); procId++)
    {
        if (((SYSTEM_PROC_A15_0 != procId) &&
             ((SYSTEM_PROC_EVE2 != procId) && (SYSTEM_PROC_EVE3 != procId))) &&
            (SYSTEM_PROC_IPU2 != procId))
        {
            loadStats = &pObj->statsDisplayObj.systemLoadStats[procId];

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
            else if (SYSTEM_PROC_IPU1_1 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "M4-1"
                          );
            }
            /*
            * Instead of EVE4, the loading of ISP is being displayed for TDA2px & TDA3x
            */
            else if ((SYSTEM_PROC_EVE4 == procId) &&
                     ((BSP_PLATFORM_SOC_ID_TDA2PX == Bsp_platformGetSocId()) ||
                      Bsp_platformIsTda3xxFamilyBuild()))
            {
#ifdef ISS_INCLUDE
               GrpxSrcLink_drawISPLoad(loadStats);
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s\n",
                          "ISP"
                          );
#else
               continue;
#endif
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

            GrpxSrcLink_displayTDA3x3DSVDrawCpuLoadBar
                (
                    pObj,
                    loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                    loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                    startX,
                    fontProp.height + SVED_FRAME_THICKNESS*2,
                    30,
                    (statsHeight - SVED_FRAME_THICKNESS) - (fontProp.height + SVED_FRAME_THICKNESS)*2
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
           startX1 = startX1 + fontProp.width*6 + 0;
           startX = startX+fontProp.width*6 + 0;
        }
    }
    return 0;
}
