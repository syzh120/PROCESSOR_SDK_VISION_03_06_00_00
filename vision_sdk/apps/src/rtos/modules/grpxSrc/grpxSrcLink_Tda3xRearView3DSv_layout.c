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
 * \file grpxSrcLink_Tda3xRearView3DSv_layout.c
 *
 * \brief  This file has the implementation of GRPX layout for
 *         TDA3x RearView + 3D Surround view demo
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
#include <math.h>

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

#define REARVIEW_WIDTH                      (1920U-896U-50U)
#define REARVIEW_HEIGHT                     (488U)
#define REARVIEW_STARTX                     (50U)
#define REARVIEW_STARTY                     ((1080U - REARVIEW_HEIGHT)/2U)

#define REARVIEW_OVERLAY_WIDTH (560U)
#define REARVIEW_OVERLAY_HEIGHT (291U)
#define REARVIEW_OVERLAY_WIDTH_RIGHT (199U)
#define REARVIEW_OVERLAY_HEIGHT_RIGHT (291U)
#define REARVIEW_OVERLAY_WIDTH_LEFT (200U)
#define REARVIEW_OVERLAY_HEIGHT_LEFT (293U)
#define REARVIEW_OVERLAY_STARTX ((REARVIEW_WIDTH/2U)-(REARVIEW_OVERLAY_WIDTH/2U) + REARVIEW_STARTX+5U)
#define REARVIEW_OVERLAY_STARTY (REARVIEW_HEIGHT+REARVIEW_STARTY-REARVIEW_OVERLAY_HEIGHT)
#define REARVIEW_OVERLAY_ENDX (REARVIEW_OVERLAY_STARTX + REARVIEW_OVERLAY_WIDTH)
#define REARVIEW_OVERLAY_ENDY (REARVIEW_OVERLAY_STARTY + REARVIEW_OVERLAY_WIDTH)
#define TOPDOWN_REARVIEW_OVERLAY_WIDTH (580U)
#define TOPDOWN_REARVIEW_OVERLAY_HEIGHT (438U)
#define TOPDOWN_REARVIEW_OVERLAY_WIDTH_RIGHT (95U)
#define TOPDOWN_REARVIEW_OVERLAY_HEIGHT_RIGHT (438U)
#define TOPDOWN_REARVIEW_OVERLAY_WIDTH_LEFT (94U)
#define TOPDOWN_REARVIEW_OVERLAY_HEIGHT_LEFT (438U)
#define TOPDOWN_REARVIEW_OVERLAY_STARTX ((REARVIEW_WIDTH/2U)-(TOPDOWN_REARVIEW_OVERLAY_WIDTH/2U) + REARVIEW_STARTX)
#define TOPDOWN_REARVIEW_OVERLAY_STARTY (REARVIEW_STARTY)
#define TOPDOWN_REARVIEW_OVERLAY_ENDX (TOPDOWN_REARVIEW_OVERLAY_STARTX + TOPDOWN_REARVIEW_OVERLAY_WIDTH)
#define TOPDOWN_REARVIEW_OVERLAY_ENDY (TOPDOWN_REARVIEW_OVERLAY_STARTY + TOPDOWN_REARVIEW_OVERLAY_WIDTH)
#define REAR_VIEW_OVERLAY_BUF_SIZE (1920U*1080U*2U)

#define XDRIVERSTATICMIN 200+50
#define YDRIVERSTATICMIN Y0
#define XDRIVERSTATICMAX 397+50
#define YDRIVERSTATICMAX 572
#define XPASSSTATICMIN 749+50
#define YPASSSTATICMIN Y0
#define XPASSSTATICMAX 552+50
#define YPASSSTATICMAX 572
#define Y0 1080-REARVIEW_STARTY

Int32 GrpxSrcLink_drawTDA3xRearView3DSVLayout(GrpxSrcLink_Obj *pObj)
{
	Draw2D_RegionPrm region;
    Draw2D_BmpPrm bmpPrm;
    Draw2D_FontPrm fontPrm;
    GrpxSrcLink_CreateParams *pCreatePrms = &pObj->createArgs;

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


    /* TI logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_TI_LOGO_1;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   50,
                   3*SVED_FRAME_THICKNESS,
                   &bmpPrm
                   );

    /* Surround view logo */
    bmpPrm.bmpIdx = DRAW2D_BMP_IDX_SURROUND_VIEW;
    Draw2D_drawBmp(pObj->draw2DHndl,
                   1108,
                   SVED_FRAME_THICKNESS,
                   &bmpPrm
                   );

    if (pObj->createArgs.enableJeepOverlay == TRUE)
    {
        /* Jeep Image */
        /* TODO : Change Co-ordinates as per the requirement */
        bmpPrm.bmpIdx = DRAW2D_BMP_IDX_JEEP_IMAGE_TRUESCALE;
        Draw2D_drawBmp(pObj->draw2DHndl,
                    (326+520),
                    (324+5),
                    &bmpPrm
                    );
    }

    /* String for input resolution / frame-rate etc */
    fontPrm.fontIdx = 5;
    if (SYSTEM_STD_WXGA_30 == pCreatePrms->tda3x3DSvSrcResolution)
    {
        Draw2D_drawString(pObj->draw2DHndl,
              50,
              200 - 120 + 15 + 2*SVED_FRAME_THICKNESS,
              "RESOLUTION: 1280x800",
              &fontPrm
              );
    }
    else
    {
        Draw2D_drawString(pObj->draw2DHndl,
              50,
              200 - 120 + 15 + 2*SVED_FRAME_THICKNESS,
              "RESOLUTION: 1280x720",
              &fontPrm
              );
    }

    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          50,
          200 - 120 + 15 + 30 + 2*SVED_FRAME_THICKNESS,
          "FRAME-RATE: 30fps   ",
          &fontPrm
          );

    fontPrm.fontIdx = 5;
    Draw2D_drawString(pObj->draw2DHndl,
          50,
          200 - 120 + 15 + 30*2 + 2*SVED_FRAME_THICKNESS,
          "   NETWORK: FPDLink ",
          &fontPrm
          );

    /* String for output resolution */
    fontPrm.fontIdx = 4;
    Draw2D_drawString(pObj->draw2DHndl,
          1284,
          pObj->info.queInfo[0].chInfo[0].height - 120 + 15 + 30,
          "RESOLUTION: 752x1008",
          &fontPrm
          );

    /* Draw Static Backup Lines */

    Draw2D_LinePrm linePrm2;
    linePrm2.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm2.lineSize = 14;
    linePrm2.lineColor = RGB888_TO_RGB565(0, 159, 255);

    /* Draw the Static Lines */
    Draw2D_drawLine(pObj->draw2DHndl,
        XDRIVERSTATICMIN,
        YDRIVERSTATICMIN,
        XDRIVERSTATICMAX,
        YDRIVERSTATICMAX,
        &linePrm2);
    Draw2D_drawLine(pObj->draw2DHndl,
        XPASSSTATICMIN,
        YPASSSTATICMIN,
        XPASSSTATICMAX,
        YPASSSTATICMAX,
        &linePrm2);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 GrpxSrcLink_drawOverlaysCreate(GrpxSrcLink_Obj *pObj)
{
    Int32 status;

    Utils_DmaChCreateParams dmaPrm;

    memset(&pObj->rearViewOverlayDrawObj, 0, sizeof(pObj->rearViewOverlayDrawObj));
    pObj->rearViewOverlayDrawObj.isFirstTime = TRUE;
    pObj->rearViewOverlayDrawObj.displayTopView = FALSE;

    Utils_DmaChCreateParams_Init(&dmaPrm);

    status = Utils_dmaCreateCh(&pObj->rearViewOverlayDrawObj.dmaObj, &dmaPrm);
    UTILS_assert(status==0);

    pObj->rearViewOverlayDrawObj.rearViewLeftBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);
    pObj->rearViewOverlayDrawObj.rearViewRightBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);
    pObj->rearViewOverlayDrawObj.rearViewLeftBlankBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);
    pObj->rearViewOverlayDrawObj.rearViewRightBlankBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);

    pObj->rearViewOverlayDrawObj.topViewLeftBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);
    pObj->rearViewOverlayDrawObj.topViewRightBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);
    pObj->rearViewOverlayDrawObj.topViewLeftBlankBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);
    pObj->rearViewOverlayDrawObj.topViewRightBlankBufAddr = (UInt32) Utils_memAlloc(
                                                    UTILS_HEAPID_DDR_CACHED_SR,
                                                    REAR_VIEW_OVERLAY_BUF_SIZE, 128);

    return status;
}

Int32 GrpxSrcLink_drawOverlaysDelete(GrpxSrcLink_Obj *pObj)
{
    Int32 status;

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.rearViewLeftBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.rearViewRightBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.rearViewLeftBlankBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.rearViewRightBlankBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.topViewLeftBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.topViewRightBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.topViewLeftBlankBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) pObj->rearViewOverlayDrawObj.topViewRightBlankBufAddr, REAR_VIEW_OVERLAY_BUF_SIZE);
    UTILS_assert(status==0);

    status = Utils_dmaDeleteCh(&pObj->rearViewOverlayDrawObj.dmaObj);

    UTILS_assert(status==0);

    return status;
}


Int32 GrpxSrcLink_drawOverlaysRun(GrpxSrcLink_Obj *pObj)
{
#ifdef GPRX_SRC_REARVIEW_DYNAMIC_LINES
    GrpxSrcLink_RearviewOverlayDrawObj *pRearViewOverlayDrawObj;
	pRearViewOverlayDrawObj = &pObj->rearViewOverlayDrawObj;

    if(pRearViewOverlayDrawObj->isFirstTime)
    {
        pRearViewOverlayDrawObj->isFirstTime = FALSE;

        /* Save the background to a buffer */
        Draw2D_updateBufAddr(pObj->draw2DHndl, &pObj->rearViewOverlayDrawObj.rearViewLeftBufAddr);

        Draw2D_BmpPrm bmpPrm;
        bmpPrm.bmpIdx = DRAW2D_BMP_FORD_REARVIEW_CAMERA_LEFT;
        Draw2D_drawBmp(pObj->draw2DHndl,
                       REARVIEW_OVERLAY_STARTX,
                       REARVIEW_OVERLAY_STARTY,
                       &bmpPrm
                       );

        /* Display the background */

        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.dataFormat   = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.dataFormat = SYSTEM_DF_RAW16;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.destAddr[0]  = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.destPitch[0] = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.destAddr[1]  = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.destAddr[1]  = NULL;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.destPitch[1] = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.destPitch[1] = 0;

        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.srcStartX    = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.srcStartX    = REARVIEW_OVERLAY_STARTX;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.srcStartY    = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.srcStartY    = REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.destStartX   = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.destStartX   = REARVIEW_OVERLAY_STARTX;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.destStartY   = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.destStartY   = REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.width        = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.width        = REARVIEW_OVERLAY_WIDTH_LEFT;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.height       = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.height       = REARVIEW_OVERLAY_HEIGHT_LEFT;

        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.rearViewLeftBufAddr;
        pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.rearViewLeftBlankBufAddr;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.srcPitch[0]  = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.srcPitch[0]  = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.srcAddr[1]   = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.srcAddr[1]   = NULL;
        pRearViewOverlayDrawObj->rearViewLeftDmaPrm.srcPitch[1]  = pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm.srcPitch[1]  = 0;

        Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                        &pRearViewOverlayDrawObj->rearViewLeftDmaPrm,
                        1);

        /* Save the background to a buffer */
        Draw2D_updateBufAddr(pObj->draw2DHndl, &pObj->rearViewOverlayDrawObj.rearViewRightBufAddr);

        bmpPrm.bmpIdx = DRAW2D_BMP_FORD_REARVIEW_CAMERA_RIGHT;
        Draw2D_drawBmp(pObj->draw2DHndl,
                       REARVIEW_OVERLAY_STARTX+REARVIEW_OVERLAY_WIDTH-REARVIEW_OVERLAY_WIDTH_RIGHT,
                       REARVIEW_OVERLAY_STARTY,
                       &bmpPrm
                       );

        /* Display the background */

        pRearViewOverlayDrawObj->rearViewRightDmaPrm.dataFormat   = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.dataFormat   = SYSTEM_DF_RAW16;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.destAddr[0]  = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.destPitch[0] = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.destAddr[1]  = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.destAddr[1]  = NULL;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.destPitch[1] = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.destPitch[1] = 0;

        pRearViewOverlayDrawObj->rearViewRightDmaPrm.srcStartX    = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.srcStartX
                                                                  = REARVIEW_OVERLAY_STARTX+REARVIEW_OVERLAY_WIDTH-REARVIEW_OVERLAY_WIDTH_RIGHT;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.srcStartY    = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.srcStartY
                                                                  = REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.destStartX   = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.destStartX
                                                                  = REARVIEW_OVERLAY_STARTX+REARVIEW_OVERLAY_WIDTH-REARVIEW_OVERLAY_WIDTH_RIGHT;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.destStartY   = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.destStartY
                                                                  = REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.width        = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.width
                                                                  = REARVIEW_OVERLAY_WIDTH_RIGHT;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.height       = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.height
                                                                  = REARVIEW_OVERLAY_HEIGHT_RIGHT;

        pRearViewOverlayDrawObj->rearViewRightDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.rearViewRightBufAddr;
        pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.rearViewRightBlankBufAddr;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.srcPitch[0]  = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.srcPitch[0]
                                                                  = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.srcAddr[1]   = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.srcAddr[1]   = NULL;
        pRearViewOverlayDrawObj->rearViewRightDmaPrm.srcPitch[1]  = pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm.srcPitch[1]  = 0;

        Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                        &pRearViewOverlayDrawObj->rearViewRightDmaPrm,
                        1);


        /* Save the background to a buffer */

        Draw2D_updateBufAddr(pObj->draw2DHndl, &pObj->rearViewOverlayDrawObj.topViewLeftBufAddr);


        bmpPrm.bmpIdx = DRAW2D_BMP_FORD_TOPDOWN_REARVIEW_CAMERA_LEFT;
        Draw2D_drawBmp(pObj->draw2DHndl,
                       TOPDOWN_REARVIEW_OVERLAY_STARTX,
                       TOPDOWN_REARVIEW_OVERLAY_STARTY,
                       &bmpPrm
                       );

        pRearViewOverlayDrawObj->topViewLeftDmaPrm.dataFormat   = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.dataFormat   = SYSTEM_DF_RAW16;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.destAddr[0]  = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.destPitch[0] = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.destAddr[1]  = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.destAddr[1]  = NULL;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.destPitch[1] = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.destPitch[1] = 0;

        pRearViewOverlayDrawObj->topViewLeftDmaPrm.srcStartX    = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.srcStartX    = TOPDOWN_REARVIEW_OVERLAY_STARTX;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.srcStartY    = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.srcStartY    = TOPDOWN_REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.destStartX   = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.destStartX   = TOPDOWN_REARVIEW_OVERLAY_STARTX;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.destStartY   = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.destStartY   = TOPDOWN_REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.width        = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.width        = TOPDOWN_REARVIEW_OVERLAY_WIDTH_LEFT;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.height       = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.height       = TOPDOWN_REARVIEW_OVERLAY_HEIGHT_LEFT;

        pRearViewOverlayDrawObj->topViewLeftDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.topViewLeftBufAddr;
        pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.topViewLeftBlankBufAddr;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.srcPitch[0]  = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.srcPitch[0]  = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.srcAddr[1]   = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.srcAddr[1]   = NULL;
        pRearViewOverlayDrawObj->topViewLeftDmaPrm.srcPitch[1]  = pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm.srcPitch[1]  = 0;

        Draw2D_updateBufAddr(pObj->draw2DHndl,
                       (UInt32 *) &pObj->outObj.videoFrames[0].bufAddr[0]);


        /* Save the background to a buffer */

        Draw2D_updateBufAddr(pObj->draw2DHndl, &pObj->rearViewOverlayDrawObj.topViewRightBufAddr);


        bmpPrm.bmpIdx = DRAW2D_BMP_FORD_TOPDOWN_REARVIEW_CAMERA_RIGHT;
        Draw2D_drawBmp(pObj->draw2DHndl,
                       TOPDOWN_REARVIEW_OVERLAY_STARTX+TOPDOWN_REARVIEW_OVERLAY_WIDTH-TOPDOWN_REARVIEW_OVERLAY_WIDTH_RIGHT,
                       TOPDOWN_REARVIEW_OVERLAY_STARTY,
                       &bmpPrm
                       );

        pRearViewOverlayDrawObj->topViewRightDmaPrm.dataFormat   = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.dataFormat   = SYSTEM_DF_RAW16;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.destAddr[0]  = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.destAddr[0]  = (Ptr) pObj->outObj.videoFrames[0].bufAddr[0];
        pRearViewOverlayDrawObj->topViewRightDmaPrm.destPitch[0] = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.destPitch[0] = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->topViewRightDmaPrm.destAddr[1]  = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.destAddr[1]  = NULL;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.destPitch[1] = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.destPitch[1] = 0;

        pRearViewOverlayDrawObj->topViewRightDmaPrm.srcStartX    = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.srcStartX
                                                                 = TOPDOWN_REARVIEW_OVERLAY_STARTX+TOPDOWN_REARVIEW_OVERLAY_WIDTH-TOPDOWN_REARVIEW_OVERLAY_WIDTH_RIGHT;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.srcStartY    = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.srcStartY    = TOPDOWN_REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.destStartX   = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.destStartX
                                                                 = TOPDOWN_REARVIEW_OVERLAY_STARTX+TOPDOWN_REARVIEW_OVERLAY_WIDTH-TOPDOWN_REARVIEW_OVERLAY_WIDTH_RIGHT;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.destStartY   = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.destStartY   = TOPDOWN_REARVIEW_OVERLAY_STARTY;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.width        = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.width        = TOPDOWN_REARVIEW_OVERLAY_WIDTH_RIGHT;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.height       = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.height       = TOPDOWN_REARVIEW_OVERLAY_HEIGHT_RIGHT;

        pRearViewOverlayDrawObj->topViewRightDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.topViewRightBufAddr;
        pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.srcAddr[0]   = (Ptr) pObj->rearViewOverlayDrawObj.topViewRightBlankBufAddr;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.srcPitch[0]  = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.srcPitch[0]  = pObj->info.queInfo[0].chInfo[0].pitch[0];
        pRearViewOverlayDrawObj->topViewRightDmaPrm.srcAddr[1]   = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.srcAddr[1]   = NULL;
        pRearViewOverlayDrawObj->topViewRightDmaPrm.srcPitch[1]  = pRearViewOverlayDrawObj->topViewRightBlankDmaPrm.srcPitch[1]  = 0;

        Draw2D_updateBufAddr(pObj->draw2DHndl,
                            (UInt32 *) &pObj->outObj.videoFrames[0].bufAddr[0]);

        pObj->rearViewOverlayDrawObj.displayTopView = TRUE;
    }
    else
    {
        /* Displaying top view by first erasing rear view overlays then drawing top view overlays */
        if (pRearViewOverlayDrawObj->displayTopView)
        {
            /* Erasing left rear view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->rearViewLeftBlankDmaPrm,
                           1);

            /* Erasing right rear view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->rearViewRightBlankDmaPrm,
                            1);

            /* Drawing left top view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->topViewLeftDmaPrm,
                            1);

            /* Drawing right top view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->topViewRightDmaPrm,
                            1);
         	pRearViewOverlayDrawObj->displayTopView = FALSE;

      }
        /* Displaying rear view by first erasing top view overlays then drawing rear view overlays */
        else
        {
            /* Erasing left top view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->topViewLeftBlankDmaPrm,
                            1);

            /* Erasing right top view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->topViewRightBlankDmaPrm,
                            1);

            /* Drawing left rear view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->rearViewLeftDmaPrm,
                            1);

            /* Drawing right rear view overlay */
            Utils_dmaCopy2D(&pRearViewOverlayDrawObj->dmaObj,
                            &pRearViewOverlayDrawObj->rearViewRightDmaPrm,
                            1);
            pRearViewOverlayDrawObj->displayTopView = TRUE;

        }
    }
#endif

    return 0;
}

Void GrpxSrcLink_displayTDA3xRearView3DSVDrawCpuLoadBar(
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

Int32 GrpxSrcLink_displayTDA3xRearView3DSVStats(GrpxSrcLink_Obj *pObj)
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
    startX =  pObj->info.queInfo[0].chInfo[0].width/2 - 520;
    startX1 = pObj->info.queInfo[0].chInfo[0].width/2 - 520;
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

            GrpxSrcLink_displayTDA3xRearView3DSVDrawCpuLoadBar
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
