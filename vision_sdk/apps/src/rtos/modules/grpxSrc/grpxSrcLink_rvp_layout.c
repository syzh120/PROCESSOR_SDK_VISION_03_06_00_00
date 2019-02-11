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
#define GRPX_BACKGROUND_COLOR ((UInt16)(RGB888_TO_RGB565(15,15,15)))

#define GRPX_FRAME_THICKNESS  		(10)

////////////////////////////////////////////////////////////////////////
// All hardcoded values are for an assume screen width/height
#define PANORAMA_OUTPUT_WIDTH		(1920)
#define PANORAMA_OUTPUT_HEIGHT		(480)

#define PANORAMA_OUTPUT_POSX        (0)
#define PANORAMA_OUTPUT_POSY        (120)

#define DISPARITY_OUTPUT_WIDTH		(800)
#define DISPARITY_OUTPUT_HEIGHT		(384)

#define DISPARITY_OUTPUT_POSX 		(PANORAMA_OUTPUT_WIDTH/2-DISPARITY_OUTPUT_WIDTH/2)
#define DISPARITY_OUTPUT_POSY		(3*PANORAMA_OUTPUT_HEIGHT/2-DISPARITY_OUTPUT_HEIGHT/2)

#define PANORAMA_LOGO_WIDTH			(950)
#define PANORAMA_LOGO_HEIGHT		(100)

#define CAR_IMAGE_WIDTH				(599)
#define CAR_IMAGE_HEIGHT			(314)
#define CAR2_IMAGE_WIDTH			(487)
#define CAR2_IMAGE_HEIGHT			(259)

#define TDALOGOWIDTH                (219U)
#define TDALOGOHEIGHT               (60U)

Int32 GrpxSrcLink_drawRearViewPanoramaLayout(GrpxSrcLink_Obj *pObj)
{
    // To remove car overlay image
	Draw2D_BmpPrm bmpPrm;

    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_RSVP_CAR_IMAGE;
    Draw2D_drawBmp(pObj->draw2DHndl,
                PANORAMA_OUTPUT_WIDTH/2-CAR_IMAGE_WIDTH/2,
                (PANORAMA_OUTPUT_POSY+PANORAMA_OUTPUT_HEIGHT)-CAR_IMAGE_HEIGHT,
                &bmpPrm
                );
#if 0
    Draw2D_BmpPrm bmpPrm;
    Draw2D_FontPrm fontPrm;

	{
	/* Fill full buffer with background color */
    region.color  = GRPX_BACKGROUND_COLOR;
    region.startX = 0;
    region.startY = 0;
    region.height = pObj->info.queInfo[0].chInfo[0].height;
    region.width  = pObj->info.queInfo[0].chInfo[0].width;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);
    	
	/* Panorama View Visibility Cutout */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.startX = PANORAMA_OUTPUT_POSX;
    region.startY = PANORAMA_OUTPUT_POSY;
    region.height = PANORAMA_OUTPUT_HEIGHT;
    region.width  = PANORAMA_OUTPUT_WIDTH;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);	

    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO_1;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   25,
                   0,
                   &bmpPrm
                   );
    /* RVP logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_REAR_VIEW_PANORAMA;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   25+PANORAMA_LOGO_WIDTH/2,
                   0, // Lucas--may tweak this #
                   &bmpPrm
                   ); 
                                 
    /* TDA3x logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TDA3X;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   1920 - (TDALOGOWIDTH+25),
                   0,
                   &bmpPrm
                   ); 
                           	
	/* String for output resolution */
	fontPrm.fontIdx = 5; // 15x25 for size 5
    Draw2D_drawString(pObj->draw2DHndl,
          PANORAMA_OUTPUT_WIDTH-405, // 27x15
          PANORAMA_OUTPUT_HEIGHT,
          "OUTPUT RESOLUTION: 1920x480", // 27 chars
          &fontPrm
          );
          
    /* String for input resolution / frame-rate etc */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          PANORAMA_OUTPUT_HEIGHT+80+65+30*0,
          "INPUT RESOLUTION: 1280x720",
          &fontPrm
          );

    /* String for stitching frame-rate etc */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          PANORAMA_OUTPUT_HEIGHT+80+65+30*1,
          "STITCHING FRAME RATE: N/A",
          &fontPrm
          );

    /* String for seam detection frame-rate etc */
    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          PANORAMA_OUTPUT_HEIGHT+80+65+30*2,
          "SEAM DETECTION FRAME RATE: N/A",
          &fontPrm
          );

    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          PANORAMA_OUTPUT_HEIGHT+80+65+30*3,
          "FRAME-RATE: N/A fps   ",
          &fontPrm
          );

    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          25,
          PANORAMA_OUTPUT_HEIGHT+80+65+30*3,
          "NUMBER OF CAMERAS: 4",
          &fontPrm
          );  
	}
                
    if (pObj->createArgs.enableCarOverlay == TRUE)
    {
        /* Car Image */
        bmpPrm.bmpIdx = DRAW2D_BMP_IDX_CAR_IMAGE;
        Draw2D_drawBmp(pObj->draw2DHndl,
                    PANORAMA_OUTPUT_WIDTH/2-CAR_IMAGE_WIDTH/2,
                    PANORAMA_OUTPUT_HEIGHT-CAR_IMAGE_HEIGHT,
                    &bmpPrm
                    );
    }
	
	if (pObj->createArgs.enableRVPDisparityLayout == TRUE)
    {
	/* Disparity View Visibility Cutout */
    region.color  = DRAW2D_TRANSPARENT_COLOR;
    region.startX = DISPARITY_OUTPUT_POSX;
    region.startY = DISPARITY_OUTPUT_POSY;
    region.height = DISPARITY_OUTPUT_HEIGHT;
    region.width  = DISPARITY_OUTPUT_WIDTH;
    Draw2D_fillRegion(pObj->draw2DHndl,&region);	
	/* String for Disparity View */      
	fontPrm.fontIdx = 4; // 20x33 for size 4
    Draw2D_drawString(pObj->draw2DHndl,
          DISPARITY_OUTPUT_POSX+DISPARITY_OUTPUT_WIDTH/2-200, // 20x20/2 
          DISPARITY_OUTPUT_POSY+DISPARITY_OUTPUT_HEIGHT,
          "  STEREO DISPARITY  ", // 20 chars
          &fontPrm
          );
     /* String for output resolution */
    fontPrm.fontIdx = 5; // 15x25 for size 5
    Draw2D_drawString(pObj->draw2DHndl,
          DISPARITY_OUTPUT_POSX+DISPARITY_OUTPUT_WIDTH,
          DISPARITY_OUTPUT_POSY+DISPARITY_OUTPUT_HEIGHT-25, //height of size 5
          "OUTPUT RESOLUTION: 800x384", // 26 chars
          &fontPrm
          );      
	}

#endif

   return SYSTEM_LINK_STATUS_SOK;
}

Void GrpxSrcLink_displayRearViewPanoramaDrawCpuLoadBar(
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

Int32 GrpxSrcLink_displayRearViewPanoramaStats(GrpxSrcLink_Obj *pObj)
{
    Draw2D_FontPrm fontPrm;
    UInt32 procId;
    Utils_SystemLoadStats *loadStats;
    char loadString[GRPX_SRC_LINK_STR_SZ];
    Draw2D_FontProperty fontProp;
    UInt32 startX, startY, startX1, startY1;
    //UInt32 statsHeight;

    fontPrm.fontIdx = 3;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    //statsHeight = 180;
    startY =  PANORAMA_OUTPUT_HEIGHT+80+95+60+30*2+180 - fontProp.height;
    startX =  GRPX_FRAME_THICKNESS;
    startX1 = GRPX_FRAME_THICKNESS;
    startY1 = PANORAMA_OUTPUT_HEIGHT+80+95+60+30*2;


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

            if(BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId()
                &&
                (procId == SYSTEM_PROC_DSP2
                    ||
                 procId == SYSTEM_PROC_EVE1
                    ||
                 procId == SYSTEM_PROC_EVE2
                    ||
                 procId == SYSTEM_PROC_EVE3
                    ||
                 procId == SYSTEM_PROC_EVE4
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
                   SYSTEM_LINK_ID_SGX3DSRV_0,
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

#if 0
            GrpxSrcLink_displayRearViewPanoramaDrawCpuLoadBar
                (
                    pObj,
                    loadStats->totalLoadParams.integerValue, /* CPU load integer value */
                    loadStats->totalLoadParams.fractionalValue, /* CPU load integer value */
                    startX,
                    fontProp.height + PANORAMA_OUTPUT_HEIGHT+80+95+60+30*2,
                    30,
                    (statsHeight - GRPX_FRAME_THICKNESS) - (fontProp.height + GRPX_FRAME_THICKNESS)*2
                );
#endif

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
    return 0;
}
