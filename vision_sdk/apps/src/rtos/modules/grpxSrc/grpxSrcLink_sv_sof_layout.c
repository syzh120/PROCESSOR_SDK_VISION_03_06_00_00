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


/**
 *******************************************************************************
 *
 * \brief Background Color of the Graphics Buffer
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SV_SOF_BACKGROUND_COLOR ((UInt16)(RGB888_TO_RGB565(16,16,16)))

/* TDA3xx defaults for 1024 X 768 resolution */
UInt32  gSvDispWidth = 1024U;
UInt32  gSvDispHeight = 768U;
UInt32  gSvOutWidth = 640U;
UInt32  gSvOutHeight = 760U;
UInt32  gSvStartX = 0U;
UInt32  gSvSofBorder = 5U;
UInt32  gSvSofJeepWidth = 208U;
UInt32  gSvSofJeepHeight = 424U;
UInt32  gSvLogoWidth = 480U;
UInt32  gSvMode2OutWidth = 1000U;
UInt32  gSvMode2OutHeight = 760U;
UInt32  gSvSofStatsHeight = 180U;

Int32 GrpxSrcLink_drawSurroundViewSOFLayout(GrpxSrcLink_Obj *pObj,
                                            System_LinkChInfo *pChInfo)
{
    UInt32 disStartX, disStartY, disWidth, disHeight, rot;
    Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    Draw2D_BmpProperty bmpProp;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;
    char string[128U];
    GrpxSrcLink_CreateParams *pCreatePrms = &pObj->createArgs;

    disStartX = pCreatePrms->displaySrv2D.startX;
    disStartY = pCreatePrms->displaySrv2D.startY;
    disWidth = pCreatePrms->displaySrv2D.width;
    disHeight = pCreatePrms->displaySrv2D.height;

    /* fill full buffer with background color */
    region.color  = SV_SOF_BACKGROUND_COLOR;
    region.colorFormat = SYSTEM_DF_BGR16_565;
    region.startX = 0;
    region.startY = 0;
    region.height = pObj->info.queInfo[0].chInfo[0].height;
    region.width  = pObj->info.queInfo[0].chInfo[0].width;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* 2D Surround view video */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.startX = disStartX;
    region.startY = disStartY;
    region.height = disHeight;
    region.width  = disWidth;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO_1;
    Draw2D_getBmpProperty(&bmpPrm, &bmpProp);
    Draw2D_drawBmp(pObj->draw2DHndl,
                   (pObj->info.queInfo[0].chInfo[0].width - bmpProp.width),
                   (pObj->info.queInfo[0].chInfo[0].height - bmpProp.height),
                   &bmpPrm);

    /* Surround view logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_SURROUND_VIEW;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   (pObj->info.queInfo[0].chInfo[0].width - 720)/2,
                   0,
                   &bmpPrm);

    if (pObj->createArgs.enableJeepOverlay == TRUE)
    {
        /* Jeep Image */
        bmpPrm.bmpIdx = DRAW2D_BMP_IDX_JEEP_220_X_330;
        rot = 0;
        Draw2D_getBmpProperty(&bmpPrm, &bmpProp);
        Draw2D_drawBmp_rot(
                pObj->draw2DHndl,
                disStartX + (disWidth - bmpProp.width)/2,
                disStartY + (disHeight - bmpProp.height)/2,
                &bmpPrm,
                rot);
    }

    /* String for output resolution */
    fontPrm.fontIdx = 4;
    Draw2D_getFontProperty(&fontPrm, &fontProp);

    sprintf(string,"TOP VIEW (%3dx%3d)",\
                pCreatePrms->displaySrv2D.srvOutWidth,
                pCreatePrms->displaySrv2D.srvOutHeight);
    Draw2D_drawString(pObj->draw2DHndl,
                disStartX + (disWidth - (fontProp.width * strlen(string)))/2,
                disStartY + pObj->info.queInfo[0].chInfo[0].height - 120 + 15 + 30 - 40,
                string,
                &fontPrm);

    return SYSTEM_LINK_STATUS_SOK;
}

Void GrpxSrcLink_displaySurroundViewSOFDrawCpuLoadBar_rot(
                    GrpxSrcLink_Obj *pObj,
                    UInt32 cpuLoadInt,
                    UInt32 cpuLoadFract,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height,
                    UInt32 rotate
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

    if(0 == rotate)
    {
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
    else if(1 == rotate)
    {
        /* fill in in active load color */
        region.color  = color[0];
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = startX;
        region.startY = startY - width;
        region.height = width;
        region.width  = barHeight[0];

        Draw2D_fillRegion(pObj->draw2DHndl,&region);

        /* fill active load color */
        region.color  = color[1];
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = startX + barHeight[0];
        region.startY = startY - width;
        region.height = width;
        region.width  = barHeight[1];

        Draw2D_fillRegion(pObj->draw2DHndl,&region);
    }
    else if(2 == rotate)
    {
        /* fill in in active load color */
        region.color  = color[0];
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = startX - barHeight[0];
        region.startY = startY;
        region.height = width;
        region.width  = barHeight[0];

        Draw2D_fillRegion(pObj->draw2DHndl,&region);

        /* fill active load color */
        region.color  = color[1];
        region.colorFormat = SYSTEM_DF_BGR16_565;
        region.startX = startX - barHeight[0] - barHeight[1];
        region.startY = startY;
        region.height = width;
        region.width  = barHeight[1];

        Draw2D_fillRegion(pObj->draw2DHndl,&region);
    }
}

Int32 GrpxSrcLink_displaySurroundViewSOFStats(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;
    UInt32 procId;
    Utils_SystemLoadStats *loadStats;
    char loadString[GRPX_SRC_LINK_STR_SZ];
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY, startX1, startY1, rot = 0;
    UInt32 statsHeight;
    UInt32 barWidth, barHeight, barOffset;

    fontPrm.fontIdx = 7;
    Draw2D_getFontProperty(&fontPrm, &fontProp);

    if ((1280U == gSvDispWidth) && (720U == gSvDispHeight))
    {
        startX =  ((gSvDispWidth - gSvMode2OutWidth)/2) +
                    fontProp.height - gSvSofStatsHeight;
    }
    else
    {
        startX =  ((gSvDispWidth - gSvMode2OutWidth)/2) + fontProp.height;
    }
    startY =  (pObj->info.queInfo[0].chInfo[0].height - gSvSofStatsHeight);
    statsHeight = gSvSofStatsHeight;
    barHeight = (statsHeight - fontProp.height*2 - gSvSofBorder*4);
    barWidth = fontProp.width*2;
    barOffset = fontProp.width; /* Offset from startX */
    startY1 = startY;
    startX1 = startX + gSvSofBorder*2 + barHeight + fontProp.height;
    rot = 0;

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
                          "%-4s",
                          System_getProcName(procId)
                          );

            if (SYSTEM_PROC_IPU1_0 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s",
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
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s",
                          "M4-1"
                          );
            }
            else if (SYSTEM_PROC_A15_0 == procId)
            {
               snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%-4s",
                          "A15"
                          );
               /* HACK for Demo, needs to fix properly */
#ifdef A15_TARGET_OS_LINUX
               loadStats->totalLoadParams.integerValue = 9;
               loadStats->totalLoadParams.fractionalValue = 5;
#endif
            }
            else
            {
                /*
                 * Avoid MISRA C Warnings
                 */
            }

            /* draw CPU name */
            if(rot == 0)
            {
                Draw2D_drawString_rot(pObj->draw2DHndl,
                          startX,
                          startY + (statsHeight - gSvSofBorder*4),
                          loadString,
                          &fontPrm,
                          rot
                          );
            }
            else
            {
                Draw2D_drawString_rot(pObj->draw2DHndl,
                          startX,
                          startY,
                          loadString,
                          &fontPrm,
                          rot
                          );
            }

            if (0 == rot)
            {
                GrpxSrcLink_displaySurroundViewSOFDrawCpuLoadBar_rot
                    (
                        pObj,
                        loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                        loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                        startX + barOffset,
                        startY1 + gSvSofBorder + fontProp.height,
                        barWidth,
                        barHeight,
                        rot
                    );
            }
            else if (1 == rot)
            {
                GrpxSrcLink_displaySurroundViewSOFDrawCpuLoadBar_rot
                    (
                        pObj,
                        loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                        loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                        startX1 + fontProp.height + gSvSofBorder,
                        startY - barOffset,
                        barWidth,
                        barHeight,
                        rot
                    );
            }
            else if (2 == rot)
            {
                GrpxSrcLink_displaySurroundViewSOFDrawCpuLoadBar_rot
                    (
                        pObj,
                        loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                        loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                        startX1 - fontProp.height - gSvSofBorder,
                        startY + barOffset,
                        barWidth,
                        barHeight,
                        rot
                    );
            }

            snprintf(loadString, GRPX_SRC_LINK_STR_SZ,
                          "%02d.%d%%",
                          loadStats->totalLoadParams.integerValue,
                          loadStats->totalLoadParams.fractionalValue
                          );

            /* draw CPU load as text */
            if(rot == 0)
            {
                Draw2D_drawString_rot(pObj->draw2DHndl,
                          startX,
                          startY1,
                          loadString,
                          &fontPrm,
                          rot
                          );
            }
            else
            {
                Draw2D_drawString_rot(pObj->draw2DHndl,
                          startX1,
                          startY1,
                          loadString,
                          &fontPrm,
                          rot
                          );
            }

            if(0 == rot)
            {
                startX1 = startX1 + fontProp.width*6 + 0;
                startX  = startX  + fontProp.width*6 + 0;
            }
            else if(1 == rot)
            {
                startY1 = startY1 - fontProp.width*6 + 0;
                startY  = startY  - fontProp.width*6 + 0;
            }
            else if(2 == rot)
            {
                startY1 = startY1 + fontProp.width*6 + 0;
                startY  = startY  + fontProp.width*6 + 0;
            }
    }
    return 0;
}

