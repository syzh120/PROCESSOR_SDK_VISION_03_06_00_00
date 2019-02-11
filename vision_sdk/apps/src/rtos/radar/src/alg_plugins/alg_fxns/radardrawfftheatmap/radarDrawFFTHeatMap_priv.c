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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
  ******************************************************************************
 * \file radarDrawFFTHeatMap_priv.c
 *
 * \brief  This file contains algorithm functions for drawing the radar related
 *         metadata output on the display.
 *
 * \version 0.0 (Oct 2016) : [CM] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/alg_fxns/radarDrawFFTHeatMap_if.h>
#include "radarDrawFFTHeatMap_priv.h"

/** Axis Pad for Radar Display  */
#define RADAR_DRAW_AXIS_PAD (2U)

/** Number of Range axis points  */
#define RADAR_DRAW_RANGE_AXIS_COUNT (8U)

/** Number of Velocity axis points  */
#define RADAR_DRAW_VELOCITY_AXIS_COUNT (4U)

/** Display char size  */
#define RADAR_DRAW_DATA_SIZE (25U)

/** Display Layout Length  */
#define RADAR_LAYOUT_LENGTH (1536U)

/** Display Layout Height */
#define RADAR_LAYOUT_HEIGHT (384U)

static UInt32 radarDrawLinkCalcEnergy(UInt32 number);
static inline UInt32 radarDrawAdd(UInt32 a, UInt32 b);
static inline Int32 radarDrawMultiply(Int16 a, Int16 b);
static UInt16 radarDrawGetColor(
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pCreateArgs, UInt32 energy);

/**
 *******************************************************************************
 *
 * \brief Api to plot the fft heat map
 *
 *  \param  pObj        Algorithm Handle which was created during the create
 *                      algorithm function call.
 *  \param  pInBuf      Input video buffer pointer.
 *  \param  pOutBuf     Output video buffer pointer.
 *
 *  \return status      Status of the success or failure of the process
 *                      operations.
 *
 *******************************************************************************
 */
Int32 RadarDrawFFTHeatMap_processData(
    AlgorithmFxn_RadarDrawFFTHeatMap_Obj *pObj,
    System_VideoFrameBuffer *pInBuf,
    System_VideoFrameBuffer *pOutBuf,
    AlgorithmFxn_RadarFftBuffDescriptor *pBufDesc)
{
    UInt32 horzSamples = 0, hCnt, vCnt, numAnt, antOffset, pitch, numHorzPoints;
    UInt8 *pInTempBufPtr;
    UInt16 pixelColor;
    UInt32 *pInBufPtr;
    UInt16 *pOutBufPtr;
    UInt32 energy, outPitch, w, h;
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pCreateArgs;
    UInt32 row, col,i;
    Draw2D_LinePrm linePrm;
    Draw2D_FontProperty fontProp;
    Draw2D_FontPrm fontPrm;
    UInt32 color;
    char loadString[10];
    Utils_DmaCopyFill2D dmaPrm;
    Int32 status;

    UTILS_assert(NULL != pInBuf);
    UTILS_assert(NULL != pOutBuf);
    UTILS_assert(NULL != pBufDesc);

    pCreateArgs = &pObj->algLinkCreateParams;

    /* h and w correspond to radar captured buffer height and width */
    w = pInBuf->chInfo.width/pCreateArgs->numRxAntenna[pObj->currProfileId];
    h = pInBuf->chInfo.height/pCreateArgs->numTxAntenna[pObj->currProfileId];
    /* outpitch is output draw buffer pitch */
    outPitch = pOutBuf->chInfo.pitch[0];

    /* Draw the background once  */
    if ((pObj->firstTime == 0U)
        && (pObj->currProfileId == pBufDesc->profileId))
    {
        pOutBufPtr = (UInt16 *)((UInt32)pObj->backgroundBufAddr +
        (pCreateArgs->outBufStartY * outPitch) +
        (pCreateArgs->outBufStartX * 2));

        color = RGB888_TO_RGB565(255, 255, 255);

        linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
        linePrm.lineColor = color;
        linePrm.lineSize = 2;

        /* Draw the vertical line */
        Draw2D_drawLine(pObj->draw2DHndl,
                pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD,
                pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD,
                pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD,
                pCreateArgs->outBufStartY + RADAR_LAYOUT_HEIGHT + RADAR_DRAW_AXIS_PAD,
                &linePrm);
        /* Draw the horizontal line */
        Draw2D_drawLine(pObj->draw2DHndl,
                pCreateArgs->outBufStartX  - RADAR_DRAW_AXIS_PAD,
                (pCreateArgs->outBufStartY + RADAR_LAYOUT_HEIGHT/2) ,
                pCreateArgs->outBufStartX  + RADAR_LAYOUT_LENGTH
                                           + RADAR_DRAW_AXIS_PAD + 2,
                (pCreateArgs->outBufStartY + RADAR_LAYOUT_HEIGHT/2) ,
                &linePrm);

        /* FontIdx 0 is larger and used for layout title*/
        fontPrm.fontIdx = 0;
        Draw2D_getFontProperty(&fontPrm, &fontProp);

        snprintf(loadString, 50, "RADAR 2D FFT HEAT MAP (PROFILE %d)", pObj->currProfileId);

        Draw2D_clearString(pObj->draw2DHndl,
              (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) + (RADAR_LAYOUT_LENGTH/4),
              (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 4) ,
                strlen(loadString),
                &fontPrm
              );

        Draw2D_drawString(pObj->draw2DHndl,
              (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) + (RADAR_LAYOUT_LENGTH/4),
              (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 4),
                loadString,
                &fontPrm
              );

        fontPrm.fontIdx = 02;
        Draw2D_getFontProperty(&fontPrm, &fontProp);

        /* Print axis label */
        snprintf(loadString, 10, "RANGE (m)");
        Draw2D_clearString(pObj->draw2DHndl,
              (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) +
              (RADAR_LAYOUT_LENGTH/2),
              (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 2),
                strlen(loadString),
                &fontPrm
              );

        Draw2D_drawString(pObj->draw2DHndl,
              (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) +
              (RADAR_LAYOUT_LENGTH/2),
              (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 2),
                loadString,
                &fontPrm
              );

        snprintf(loadString, 15, "VELOCITY (m/s)");
        Draw2D_clearString(pObj->draw2DHndl,
                (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - 220,
                ((pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) +
                (RADAR_LAYOUT_HEIGHT/4) + RADAR_DRAW_DATA_SIZE),
                strlen(loadString),
                &fontPrm
                );

        Draw2D_drawString(pObj->draw2DHndl,
                (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - 220,
                ((pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) +
                (RADAR_LAYOUT_HEIGHT/4) + RADAR_DRAW_DATA_SIZE),
                loadString,
                &fontPrm
                );

        for(i = 0; i <= RADAR_LAYOUT_LENGTH;)
        {
            UInt32 value;
            value = (UInt32)(i * w * 100.0 *
                             pCreateArgs->rangeRes[pObj->currProfileId])/
                             RADAR_LAYOUT_LENGTH;
            Draw2D_drawLine(pObj->draw2DHndl,
                (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) + i,
                (pCreateArgs->outBufStartY + RADAR_LAYOUT_HEIGHT/2),
                (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) + i,
                (pCreateArgs->outBufStartY + RADAR_LAYOUT_HEIGHT/2) - 8,
                &linePrm);
            snprintf(loadString, 10, "%d.%d",value/100, value%100);
            /* Keeping the labels to be at the center of the tick position except the
             * first one.
             */
            if (i == 0)
            {
                value = (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) + i + 5;
            }
            else
            {
                value = (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) + i - 10;
            }
            Draw2D_clearString(pObj->draw2DHndl,
                      value,
                      (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - RADAR_DRAW_DATA_SIZE,
                        strlen(loadString),
                        &fontPrm
                      );

            Draw2D_drawString(pObj->draw2DHndl,
                      value,
                      (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - RADAR_DRAW_DATA_SIZE,
                        loadString,
                        &fontPrm
                      );
            i = i + (RADAR_LAYOUT_LENGTH/RADAR_DRAW_RANGE_AXIS_COUNT);
        }

        for(i = 0; i <= RADAR_LAYOUT_HEIGHT;)
        {
            Int32 value;
            float factor = ((float)i)/(float)RADAR_LAYOUT_HEIGHT;
            value = (Int32)(h * 100.0 * pCreateArgs->velocityRes[pObj->currProfileId] * ((float)0.5 - factor));
            Draw2D_drawLine(pObj->draw2DHndl,
                (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD),
                (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) + i,
                (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - 8,
                (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) + i,
                &linePrm);
            snprintf(loadString, 10, "%d.%d",value/100, abs(value%100));
            Draw2D_clearString(pObj->draw2DHndl,
                      (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE*4),
                      (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) + i,
                        strlen(loadString),
                        &fontPrm
                      );

            Draw2D_drawString(pObj->draw2DHndl,
                      (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE*4),
                      (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) + i,
                        loadString,
                        &fontPrm
                      );
            i = i + (RADAR_LAYOUT_HEIGHT/RADAR_DRAW_VELOCITY_AXIS_COUNT);
        }

        pObj->firstTime = 1;
    }
    else
    {
        dmaPrm.dataFormat   = SYSTEM_DF_RGB16_565;
        dmaPrm.destAddr[0]  = (Ptr) pOutBuf->bufAddr[0U];
        dmaPrm.destAddr[1]  = NULL;
        dmaPrm.destPitch[0] = outPitch;
        dmaPrm.destPitch[1] = 0;
        dmaPrm.destStartX   = (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - 220;
        dmaPrm.destStartY   = (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 4);
        dmaPrm.width        = (RADAR_LAYOUT_LENGTH + (RADAR_DRAW_AXIS_PAD * 2 ) + 320) *2;
        dmaPrm.height       = RADAR_LAYOUT_HEIGHT + (RADAR_DRAW_AXIS_PAD * 2) + (RADAR_DRAW_DATA_SIZE * 5);
        dmaPrm.srcAddr[0]   = (Ptr) pObj->backgroundBufAddr;
        dmaPrm.srcAddr[1]   = NULL;
        dmaPrm.srcPitch[0]  = outPitch;
        dmaPrm.srcPitch[1]  = 0;
        dmaPrm.srcStartX    = dmaPrm.destStartX;
        dmaPrm.srcStartY    = dmaPrm.destStartY;

        status = Utils_dmaCopy2D(&pObj->copyFramesDmaObj,
                                 &dmaPrm,
                                 1);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    if (pObj->currProfileId == pBufDesc->profileId)
    {
        pOutBufPtr = (UInt16 *)((UInt32)pOutBuf->bufAddr[0U] +
            ((pCreateArgs->outBufStartY +
            RADAR_LAYOUT_HEIGHT/2 - RADAR_LAYOUT_HEIGHT/h) * outPitch) +
            (pCreateArgs->outBufStartX * 2));

        pInBufPtr = (UInt32 *)pInBuf->bufAddr[0U];

        numAnt = pBufDesc->bufDesc.numAntennas;
        antOffset = pBufDesc->bufDesc.offsetBwAntennas[0];
        pitch = pBufDesc->bufDesc.pitch[0];
        numHorzPoints = pBufDesc->bufDesc.numHorzPoints[0];

        /*output data buff   */

        /* Input Buff pattern to draw */

        /*
        *    <-numHorzPoints->
        *  / |----------------|----------------|----------------|----------------|---
        *  | | Antenna 0      | Antenna 1      |  Antenna 2     |  Antenna 3     | -
        *  | |                |                |                |                | |
        *  | |                |                |                |                | h
        *  | |<--antOffset--->|                |                |                | |
        *  | |                |                |                |                | -
        *  | |----------------|----------------|----------------|----------------|---
        *  | | Antenna 0      | Antenna 1      |  Antenna 2     |  Antenna 3     | -
        *  | |                |                |                |                | |
        *  | |                |                |                |                | h
        *  | |<--antOffset--->|                |                |                | |
        *  | |                |                |                |                | -
        *  | |----------------|----------------|----------------|----------------|---
        *  | |------------------------pitch--------------------------------------|
        *  |  ....
        *  |  Repeated Chirp Length (w)/ numHorzPoints times
        *  \
        *
        */

        /* The output from radarfft algo buffer contains data in above format
        * Antenna 0, Antenna 1 ... number of antenna configured
        * antOffset is the offset between antenna data
        * numHorzPoints is the horizontal data present.(This can be less than antOffset)
        * width is the total buffer width
        * height is the total buffer height
        */

        for (vCnt = 0U; vCnt < h; vCnt ++)
        {
            /* Assign buff ptr to tempbuffptr to seek different points  */
            pInTempBufPtr = (UInt8 *)pInBufPtr;
            for (hCnt = 0U; hCnt < w; hCnt ++)
            {
                /* Perform energy calculation only for non zero entries */
                if (*(UInt32 *)pInTempBufPtr != 0U)
                {
                    energy = radarDrawLinkCalcEnergy(
                        *(UInt32 *)pInTempBufPtr);
                    /* Ignore data less than threashold */
                    if (energy > pCreateArgs->binRange[0])
                    {
                        pixelColor = radarDrawGetColor(pCreateArgs, energy);
                        /* Pick the color and plot by scale it */
                        for (row = 0; row < RADAR_LAYOUT_HEIGHT/h; row++)
                        {
                        for (col = 0; col < RADAR_LAYOUT_LENGTH/w; col++)
                            {
                                UInt16* tmpPtr = (UInt16*) ((UInt32)pOutBufPtr + (row*outPitch));
                                *(tmpPtr + ((hCnt * RADAR_LAYOUT_LENGTH)/w) + col) = pixelColor;
                            }
                        }
                    }
                }
                /* Seek to next data of same antenna */
                pInTempBufPtr = pInTempBufPtr + (numAnt * antOffset);
                horzSamples ++;

                if (horzSamples == numHorzPoints)
                {
                    horzSamples = 0;
                    pInTempBufPtr = (UInt8 *)((UInt32)pInTempBufPtr + (pitch * (h-1))+4 - antOffset);
                }
                else
                {
                    pInTempBufPtr = (UInt8 *)((UInt32)pInTempBufPtr - pitch + 4); /* Temp buff is uint8 */
                }
            }
            pInBufPtr = (UInt32 *)((UInt32)pInBufPtr + pitch);

            /* Output of draw  */

            /*  <----         RADAR_LAYOUT_LENGTH        --------->
            * |------------------------------------------------- \
            * |     63                                           |
            * |     ...        Moving away from sensor           |
            * |     ...                                          |
            * |     1                                             > RADAR_LAYOUT_HEIGHT
            * |-----0------------------------------------------- |
            * |     128                                          |
            * |     ...        Moving towards the sensor         |
            * |     ...                                          |
            * |     64                                           |
            * |------------------------------------------------- /
            * Output Pitch (outPitch) is the total output buffer pitch.
            */

            if(vCnt == ((h/2) -1))
            {
                pOutBufPtr = (UInt16 *)((UInt32)pOutBuf->bufAddr[0U] +
                ((pCreateArgs->outBufStartY + RADAR_LAYOUT_HEIGHT) * outPitch) +
                (pCreateArgs->outBufStartX * 2));
            }
            else
            {
                pOutBufPtr = (UInt16*)((UInt32)pOutBufPtr - (outPitch * RADAR_LAYOUT_HEIGHT)/h);
            }
        }

        dmaPrm.dataFormat   = SYSTEM_DF_RGB16_565;
        dmaPrm.destAddr[0]  = (Ptr) pObj->prevDrawnBufAddr;
        dmaPrm.destAddr[1]  = NULL;
        dmaPrm.destPitch[0] = outPitch;
        dmaPrm.destPitch[1] = 0;
        dmaPrm.destStartX   = (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - 220;
        dmaPrm.destStartY   = (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 4);
        dmaPrm.width        = (RADAR_LAYOUT_LENGTH + (RADAR_DRAW_AXIS_PAD * 2 ) + 320) *2;
        dmaPrm.height       = RADAR_LAYOUT_HEIGHT + (RADAR_DRAW_AXIS_PAD * 2) + (RADAR_DRAW_DATA_SIZE * 5);
        dmaPrm.srcAddr[0]   = (Ptr)  pOutBuf->bufAddr[0U];
        dmaPrm.srcAddr[1]   = NULL;
        dmaPrm.srcPitch[0]  = outPitch;
        dmaPrm.srcPitch[1]  = 0;
        dmaPrm.srcStartX    = dmaPrm.destStartX;
        dmaPrm.srcStartY    = dmaPrm.destStartY;

        status = Utils_dmaCopy2D(&pObj->copyFramesDmaObj,
                                 &dmaPrm,
                                 1);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    else
    {
        dmaPrm.dataFormat   = SYSTEM_DF_RGB16_565;
        dmaPrm.destAddr[0]  = (Ptr)  pOutBuf->bufAddr[0U];
        dmaPrm.destAddr[1]  = NULL;
        dmaPrm.destPitch[0] = outPitch;
        dmaPrm.destPitch[1] = 0;
        dmaPrm.destStartX   = (pCreateArgs->outBufStartX - RADAR_DRAW_AXIS_PAD) - 220;
        dmaPrm.destStartY   = (pCreateArgs->outBufStartY - RADAR_DRAW_AXIS_PAD) - (RADAR_DRAW_DATA_SIZE * 4);
        dmaPrm.width        = (RADAR_LAYOUT_LENGTH + (RADAR_DRAW_AXIS_PAD * 2 ) + 320) *2;
        dmaPrm.height       = RADAR_LAYOUT_HEIGHT + (RADAR_DRAW_AXIS_PAD * 2) + (RADAR_DRAW_DATA_SIZE * 5);
        dmaPrm.srcAddr[0]   = (Ptr) pObj->prevDrawnBufAddr;
        dmaPrm.srcAddr[1]   = NULL;
        dmaPrm.srcPitch[0]  = outPitch;
        dmaPrm.srcPitch[1]  = 0;
        dmaPrm.srcStartX    = dmaPrm.destStartX;
        dmaPrm.srcStartY    = dmaPrm.destStartY;

        status = Utils_dmaCopy2D(&pObj->copyFramesDmaObj,
                                 &dmaPrm,
                                 1);

        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

static UInt32 radarDrawLinkCalcEnergy(UInt32 number)
{
    Int16 a, b;
    UInt32  res1, res2;

    a = (Int16)(number & 0xFFFF);
    b = (Int16)((number & 0xFFFF0000)>>16U);

    res1 = (UInt32)radarDrawMultiply(a, a);
    res2 = (UInt32)radarDrawMultiply(b, b);

    return radarDrawAdd(res1, res2);
}

static inline Int32 radarDrawMultiply(Int16 a, Int16 b)
{
    Int32 c;

    c = a * b;

    return c;
}

static inline UInt32 radarDrawAdd(UInt32 a, UInt32 b)
{
    UInt32 result;
    UInt64 c;

    c = (UInt64)a + (UInt64)b;
    if (c > 0xFFFFFFFF)
    {
        result = 0xFFFFFFFFU;
    }
    else
    {
        result = c & 0xFFFFFFFF;
    }

    return (result);
}

static UInt16 radarDrawGetColor(
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pCreateArgs, UInt32 energy)
{
    UInt16 color = 0x0;
    UInt32 cnt, numBins = pCreateArgs->numBins;
    UInt32 *range = &pCreateArgs->binRange[0];
    UInt32 *pColor = &pCreateArgs->rgb565Color[0];

    for (cnt = 0; cnt < numBins; cnt ++)
    {
        if (energy <= range[cnt])
        {
            color = pColor[cnt];
            break;
        }
    }

    return (color);
}
