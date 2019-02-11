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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "radarDraw_priv.h"

/**< \brief Macro to convert RGB888 to RGB565 */
#define RADAR_DRAW_RGB888_TO_RGB565(r,g,b)     \
    ((((UInt32)(r>>3) & 0x1F) << 11) | \
    (((UInt32)(g>>2) & 0x3F) << 5) | \
    (((UInt32)(b>>3) & 0x1F)))

/**< \brief Macro to convert from degree to Radians */
#define RADAR_DRAW_M_RAD        0.0174532925

/**< \brief Macro definition for minimum length to draw in the cone */
#define RADAR_DRAW_MINIMUM_LENGTH 4U

/**< \brief Radar Draw Cluster macro definition. This is currently not supported
 *          as the algorithm needs to be put in place.
 */
/* #define RADAR_DRAW_CLUSTER */

Int32 RadarDraw_drawRadarObjects(AlgorithmFxn_RadarDrawObj *pObj)
{
    UInt32 idx;
    AlgorithmFxn_RadarBeamFormBuffDescriptor *pRadarOutput;
    RadarDraw_targetInformation target;
    Int32 angle;
    double currAzimAngle, currRange;
    Int32 maxVelocityBinNum, midPoint;

    pRadarOutput = pObj->detectedObjs;
    maxVelocityBinNum =
        pObj->algLinkCreateParams.maxVelocityBinNum[pRadarOutput->profileId];
    midPoint = maxVelocityBinNum/2;
    for (idx = 0; idx < pRadarOutput->numDetections; idx++)
    {
        angle = (pObj->algLinkCreateParams.numHorzAngles - 1)/2;
        /* Create mirror image of angle */
        currAzimAngle = -(((Int32)(pRadarOutput->objBuf[idx].angleBin % pObj->algLinkCreateParams.numHorzAngles) - angle)*
                     pObj->algLinkCreateParams.azimAngleRes[pRadarOutput->profileId]);
        /* Current Range is in cm */
        currRange = 100 * pRadarOutput->objBuf[idx].range
                    * pObj->algLinkCreateParams.rangeRes[pRadarOutput->profileId];
        if (((currAzimAngle < angle) && (currAzimAngle > -angle)) &&
                (((currRange * 2)/pObj->scale) < pObj->radius) && (pRadarOutput->objBuf[idx].energy > 0))
        {
            target.angle = (Int32) currAzimAngle * 2;
            target.distance = (Int32) ((currRange * 2)/ pObj->scale);
            if (pRadarOutput->objBuf[idx].velocity >= midPoint)
            {
                target.relSpeed = ((Int32)pRadarOutput->objBuf[idx].velocity -
                                   maxVelocityBinNum)*
                                  pObj->algLinkCreateParams.velocityRes[
                                  pRadarOutput->profileId];
            }
            else
            {
                target.relSpeed = pRadarOutput->objBuf[idx].velocity *
                                  pObj->algLinkCreateParams.velocityRes[
                                  pRadarOutput->profileId];
            }

            RadarDraw_plotTarget(pObj,
                                     pObj->centerX,
                                     pObj->centerY,
                                     pObj->radius,
                                     &target);
        }
        else
        {
            //Vps_printf("RadarDrawLink: obj [%d] is out of range for display!! ", idx);
        }
    }
#ifdef RADAR_DRAW_CLUSTER
    if (pRadarOutput->numCluster > 1)
    {
        UInt32 startX, startY, width, height, color;
        Int32 offsetX, offsetY, sizeX, sizeY;
        for (idx = 0; idx < pRadarOutput->numCluster; idx++)
        {
            offsetX = pRadarOutput->report[idx].xCenter;
            offsetX = (offsetX*100) >> 8;
            offsetY = pRadarOutput->report[idx].yCenter;
            offsetY = (offsetY*100) >> 8;
            sizeX = pRadarOutput->report[idx].xSize;
            sizeX = (sizeX*100) >> 8;
            sizeY = pRadarOutput->report[idx].ySize;
            sizeY = (sizeY*100) >> 8;

            startX = pObj->centerX + offsetX/pObj->scale;
            startY = pObj->centerY - offsetY/pObj->scale;
            width = sizeX/pObj->scale;
            height = sizeY/pObj->scale;
            if(pRadarOutput->report[idx].minVel < (0 - pRadarOutput->vel_threshold))
            {
                color = 2;
            }
            else if(pRadarOutput->report[idx].minVel > pRadarOutput->vel_threshold)
            {
                color = 1;
            }
            else
            {
                color = 0;
            }
            RadarDraw_drawClusterBox(pObj,
                                        startX,
                                        startY,
                                        width,
                                        height,
                                        color);
        }
    }
#endif
    return 0;
}

/* fast sin and cos calculation */
double sin_table[360];

/* in degrees */
static inline double RadarDraw_sinvLookup(int angle)
{
    /* prepare input angle to be [0, 359] */
    while (angle < 0)
        angle += 360;

    while (angle > 359)
        angle -=360;
    /*  array boundary protection */
    UTILS_assert((angle >= 0) && (angle <= 359));

    return sin_table[angle];
}
static inline double RadarDraw_cosvLookup(int angle)
{
    /* cos(x) =  sin(x + 90) */
    return RadarDraw_sinvLookup(angle + 90);
}
static inline UInt32 RadarDraw_calcX(UInt32 radius, double degree)
{
    return (UInt32)(RadarDraw_sinvLookup((int)degree) * radius);
}
static inline UInt32 RadarDraw_calcY(UInt32 radius, double degree)
{
    return (UInt32)(RadarDraw_cosvLookup((int)degree) * radius);

}

void RadarDraw_sinFillTable(void)
{
    int degree;

    for (degree = 0; degree < 180; degree++)
    {
        sin_table[degree]       =  sin(degree * RADAR_DRAW_M_RAD );
        sin_table[degree + 180] = -sin_table[degree];
    }
}

Void RadarDraw_drawLabel(
        AlgorithmFxn_RadarDrawObj *pObj,
        UInt32 x,
        UInt32 y,
        char *text,
        UInt32 fontId)
{
    char loadString[RADAR_DRAW_STR_SZ];
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;

    fontPrm.fontIdx = fontId;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    snprintf(loadString, RADAR_DRAW_STR_SZ,
                          "%s\n",
                          text
                          );

    /* shift the letters in both directions due to presence of the
     * radar scope
     */
    Draw2D_drawString(pObj->draw2DHndl,
                      x,
                      y,
                      loadString,
                      &fontPrm
                      );
}

/**
 *******************************************************************************
 *
 * \brief This function draws a circle and a cross
 * \param  pObj [IN] AlgorithmFxn_RadarDrawObj
 * \param  UInt32 [IN] centerX
 * \param  UInt32 [IN] centerY
 * \param  UInt32 [IN] radius
 * \param  UInt32 [IN] color
                        0: white
                        1: red
                        2: green
 *
 *******************************************************************************
 */
Void RadarDraw_drawTargetCircleCross(
                    AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 centerX,
                    UInt32 centerY,
                    UInt32 radius,
                    UInt32 colorSelection)
{
    Draw2D_LinePrm linePrm;
    UInt32 color[3];

    color[0] = RADAR_DRAW_RGB888_TO_RGB565(255, 255, 255);    /* white */
    color[1] = RADAR_DRAW_RGB888_TO_RGB565(255, 0, 0);        /* red */
    color[2] = RADAR_DRAW_RGB888_TO_RGB565(0, 255, 255);      /* blue */

    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineColor = color[colorSelection];
    linePrm.lineSize = 2;

    double i;
    UInt32 x;
    UInt32 y;
    int xDelta = RadarDraw_calcX(radius, 45);
    int yDelta = RadarDraw_calcY(radius, 45);

    if (radius < RADAR_DRAW_MINIMUM_LENGTH)
    {
        radius = RADAR_DRAW_MINIMUM_LENGTH;
    }

    /* draw the coloured circle */
    for (i = 0; i < 90; i++){
        x = RadarDraw_calcX(radius, i);
        y = RadarDraw_calcY(radius, i);

        Draw2D_drawPixel(
            pObj->draw2DHndl,
            centerX + x,
            centerY + y,
            linePrm.lineColor,
            linePrm.lineColorFormat
        );

        Draw2D_drawPixel(
            pObj->draw2DHndl,
            centerX + x,
            centerY - y,
            linePrm.lineColor,
            linePrm.lineColorFormat
        );

        Draw2D_drawPixel(
            pObj->draw2DHndl,
            centerX - x,
            centerY + y,
            linePrm.lineColor,
            linePrm.lineColorFormat
        );

        Draw2D_drawPixel(
            pObj->draw2DHndl,
            centerX - x,
            centerY - y,
            linePrm.lineColor,
            linePrm.lineColorFormat
        );
    }

    if (pObj->scale == 1)
    {
        /* draw the cross in the middle */
        Draw2D_drawLine(pObj->draw2DHndl,
                centerX - xDelta,
                centerY - yDelta,
                centerX + xDelta,
                centerY + yDelta,
                &linePrm);

        Draw2D_drawLine(pObj->draw2DHndl,
                centerX - xDelta,
                centerY + yDelta,
                centerX + xDelta,
                centerY - yDelta,
                &linePrm);
    }
}

/**
 *******************************************************************************
 *
 * \brief This function draws a box for clustering
 * \param  pObj [IN] AlgorithmFxn_RadarDrawObj
 * \param  UInt32 [IN] startX
 * \param  UInt32 [IN] startY
 * \param  UInt32 [IN] width
 * \param  UInt32 [IN] height
 * \param  UInt32 [IN] color
                        0: white
                        1: red
                        2: green
 *
 *******************************************************************************
 */
Void RadarDraw_drawClusterBox(
                    AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height,
                    UInt32 colorSelection)
{
    Draw2D_LinePrm linePrm;
    UInt32 color[3];

    color[0] = RADAR_DRAW_RGB888_TO_RGB565(255, 255, 255);    /* white */
    color[1] = RADAR_DRAW_RGB888_TO_RGB565(255, 0, 0);        /* red */
    color[2] = RADAR_DRAW_RGB888_TO_RGB565(255, 255, 0);      /* yellow */

    if (width < RADAR_DRAW_MINIMUM_LENGTH)
    {
        width = RADAR_DRAW_MINIMUM_LENGTH;
    }
    if (height < RADAR_DRAW_MINIMUM_LENGTH)
    {
        height = RADAR_DRAW_MINIMUM_LENGTH;
    }

    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineColor = color[colorSelection];
    linePrm.lineSize = 2;

    Draw2D_drawRect(pObj->draw2DHndl,
                    startX,
                    startY,
                    width,
                    height,
                    &linePrm);
}

/**
 *******************************************************************************
 *
 * \brief This function plots one single radar target
 * \param  pObj [IN] AlgorithmFxn_RadarDrawObj
 * \param  UInt32 [IN] x
 * \param  UInt32 [IN] y
 * \param  UInt32 [IN] radius
 * \param  RadarDraw_targetInformation [IN] target
 *
 *******************************************************************************
 */
Void RadarDraw_plotTarget(AlgorithmFxn_RadarDrawObj *pObj,
        Int32 x,
        Int32 y,
        Int32 radius,
        RadarDraw_targetInformation *pTarget )
{

    /* check the relative speed */
    int colorSel;
    int posY;
    int posX;

    if(pTarget->relSpeed < 0)
        colorSel = 2;
    else if(pTarget->relSpeed > 0)
        colorSel = 1;
    else
        colorSel = 0;

    /* calculate the position */
    posY = y - RadarDraw_calcY(pTarget->distance, pTarget->angle);

    if (pTarget->angle < 0)
        posX = x - RadarDraw_calcX(pTarget->distance, (pTarget->angle * (-1)));
    else
        posX = x + RadarDraw_calcX(pTarget->distance, pTarget->angle);

    /* plot the target to the scope */
    RadarDraw_drawTargetCircleCross(
                                pObj,
                                posX,
                                posY,
                                6/pObj->scale,
                                colorSel);
}

/**
 *******************************************************************************
 *
 * \brief This function draws the labels next to the radar scope
 * \param  pObj [IN] AlgorithmFxn_RadarDrawObj
 * \param  UInt32 [IN] centerX
 * \param  UInt32 [IN] centerY
 * \param  UInt32 [IN] radius
 * \param  UInt32 [IN] degrees
 *
 *******************************************************************************
 */
Void RadarDraw_drawLabels(AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 centerX,
                    UInt32 centerY,
                    UInt32 radius,
                    UInt32 degrees)
{
    UInt32 offset;
    Int32 range;
    char label[16];
    Int32 angle;
    UInt32 deltaX, deltaY;

    sprintf(label, "Radar Object");
    RadarDraw_drawLabel(pObj,1440, 810, label, 0);
    sprintf(label, "Detection");
    RadarDraw_drawLabel(pObj,1440, 900, label, 0);

    /* By default, 1 pixel = 1 centermeter with scale = 1. */
    offset = 200U;
    for (radius=offset, range=1; radius < pObj->radius; radius+=offset, range++)
    {
        sprintf(label, "%dm", (range * pObj->scale));
        RadarDraw_drawLabel(pObj,
                centerX + RadarDraw_calcX(radius, 2*pObj->angle+2),
                centerY - RadarDraw_calcY(radius, 2*pObj->angle+2),
                label, 2);
    }
    angle = (Int32) pObj->angle;
    while(angle > 0)
    {
        deltaX = RadarDraw_calcX(radius + 1, angle * 2);
        deltaY = RadarDraw_calcY(radius + 1, angle * 2);
        sprintf(label, "%ddeg", angle);
        RadarDraw_drawLabel(pObj,
                centerX + deltaX,
                centerY - deltaY,
                label, 2);
        sprintf(label, "-%ddeg", angle);
        RadarDraw_drawLabel(pObj,
                centerX - deltaX,
                centerY - deltaY,
                label, 2);
        angle -= 10;
    }
    deltaX = RadarDraw_calcX(radius + 1, 0);
    deltaY = RadarDraw_calcY(radius + 1, 0);
    sprintf(label, "0deg");
    RadarDraw_drawLabel(pObj,
                centerX + deltaX,
                centerY - deltaY,
                label, 2);
}

 /**
 *******************************************************************************
 *
 * \brief This function draws a part of a circle
 * \param  pObj [IN] AlgorithmFxn_RadarDrawObj
 * \param  UInt32 [IN] centerX
 * \param  UInt32 [IN] centerY
 * \param  UInt32 [IN] radius
 * \param  UInt32 [IN] degrees
 *
 *******************************************************************************
 */
Void RadarDraw_drawPartCircle(
                    AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 centerX,
                    UInt32 centerY,
                    UInt32 radius,
                    UInt32 degrees
                    )
{
    Draw2D_LinePrm linePrm;
    UInt32 color[2];
    double i;
    UInt32 x;
    UInt32 y;

    color[1] = RADAR_DRAW_RGB888_TO_RGB565(0, 128, 0);
    color[0] = RADAR_DRAW_RGB888_TO_RGB565(198, 198, 198);

    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineColor = color[1];
    linePrm.lineSize = 2;

    for (i = 0; i < degrees; i++){
            x = RadarDraw_calcX(radius, i);
            y = RadarDraw_calcY(radius, i);

            Draw2D_drawPixel(
                pObj->draw2DHndl,
                centerX + x,
                centerY - y,
                linePrm.lineColor,
                linePrm.lineColorFormat
                );

            Draw2D_drawPixel(
                pObj->draw2DHndl,
                centerX - x,
                centerY - y,
                linePrm.lineColor,
                linePrm.lineColorFormat
                );
    }
}

/**
 *******************************************************************************
 *
 * \brief This function draws the sector lines to be able to display several angles
 * \param  pObj [IN] AlgorithmFxn_RadarDrawObj
 * \param  UInt32 [IN] startX
 * \param  UInt32 [IN] startY
 * \param  UInt32 [IN] length
 *
 *******************************************************************************
 */
Int32 RadarDraw_drawSectorLines(
                        AlgorithmFxn_RadarDrawObj *pObj,
                        UInt32 startX,
                        UInt32 startY,
                        UInt32 length,
                        UInt32 degree
                        )
{
    Draw2D_LinePrm linePrm;
    UInt32 color[2];
    UInt32 deltaX, deltaY;
    UInt32 i;

    color[1] = RADAR_DRAW_RGB888_TO_RGB565(0, 128, 0);
    color[0] = RADAR_DRAW_RGB888_TO_RGB565(255, 255, 255);

    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineColor = color[1];
    linePrm.lineSize = 2;

    Draw2D_drawLine(pObj->draw2DHndl,
            startX,
            startY,
            startX,
            startY - length,
            &linePrm);

    deltaX = RadarDraw_calcX(length, degree);
    deltaY = RadarDraw_calcY(length, degree);

    Draw2D_drawLine(pObj->draw2DHndl,
            startX,
            startY,
            startX - deltaX,
            startY - deltaY,
            &linePrm);

    Draw2D_drawLine(pObj->draw2DHndl,
            startX,
            startY,
            startX + deltaX,
            startY - deltaY,
            &linePrm);

    for(i=1; degree > 15; i++)
    {
        deltaX = RadarDraw_calcX(length, 10*i*2);
        deltaY = RadarDraw_calcY(length, 10*i*2);

        Draw2D_drawLine(pObj->draw2DHndl,
                startX,
                startY,
                startX - deltaX,
                startY - deltaY,
                &linePrm);

        Draw2D_drawLine(pObj->draw2DHndl,
                startX,
                startY,
                startX + deltaX,
                startY - deltaY,
                &linePrm);

        degree -= 20;
    }

    return 0;
}
