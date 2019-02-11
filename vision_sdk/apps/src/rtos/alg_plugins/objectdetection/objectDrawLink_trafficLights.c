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

#include "objectDrawLink_priv.h"


#define OBJECTDRAW_TRAFFIC_LIGHT_WIDTH_1  (32)
#define OBJECTDRAW_TRAFFIC_LIGHT_HEIGHT_1 (32)

#define OBJECTDRAW_TRAFFIC_LIGHT_MAX    (2)

UInt8 gObjectDraw_trafficLights_1[] = {
    #include "traffic_lights/Red_TL_32x32.h"
    #include "traffic_lights/Green_TL_32x32.h"
};

Int32 AlgorithmLink_objectDrawCopyTrafficLight(
    UInt8 *bufAddrY,
    UInt8 *bufAddrC,
    UInt32 pitchY,
    UInt32 pitchC,
    UInt32 bufWidth,
    UInt32 bufHeight,
    UInt32 startX,
    UInt32 startY,
    UInt32 trafficLightId,
    UInt32 trafficLightType
    )
{
    UInt8 *pTrafficLight;
    UInt8 *pTrafficLightList;
    UInt32 copyWidth, copyHeight, i;
    UInt32 trafficLightSize;
    UInt32 trafficLightWidth, trafficLightHeight;

    if(trafficLightId>=OBJECTDRAW_TRAFFIC_LIGHT_MAX)
        return -1;

    trafficLightWidth = OBJECTDRAW_TRAFFIC_LIGHT_WIDTH_1;
    trafficLightHeight = OBJECTDRAW_TRAFFIC_LIGHT_HEIGHT_1;
    pTrafficLightList = gObjectDraw_trafficLights_1;

    trafficLightSize = trafficLightWidth*trafficLightHeight*3/2;

    /* align to multiple of 2, since data format is YUV420 */
    startX = SystemUtils_floor(startX, 2);
    startY = SystemUtils_floor(startY, 2);

    /* clip the copy area to limit within buffer area */
    copyWidth = trafficLightWidth;
    copyHeight = trafficLightHeight;

    if(startX > bufWidth
        ||
       startY > bufHeight
        )
    {
        /* Nothing to copy in this case */
        return 0;
    }

    if(startX+copyWidth > bufWidth)
    {
        copyWidth = bufWidth - startX;
    }

    if(startY+copyHeight > bufHeight)
    {
        copyHeight = bufHeight - startY;
    }

    /* adjust input buffer pointer to start location */
    bufAddrY = bufAddrY + pitchY*startY + startX;
    bufAddrC = bufAddrC + pitchC*startY/2 + startX;

    /* Copy Y */
    pTrafficLight = pTrafficLightList
                + trafficLightId*trafficLightSize;

    for(i=0; i<copyHeight; i++)
    {
        memcpy(bufAddrY, pTrafficLight, copyWidth);

        bufAddrY+=pitchY;
        pTrafficLight+=trafficLightWidth;
    }

    /* Copy C */
    pTrafficLight = pTrafficLightList
                + trafficLightId*trafficLightSize;

    pTrafficLight += trafficLightWidth*trafficLightHeight;

    for(i=0; i<copyHeight/2; i++)
    {
        memcpy(bufAddrC, pTrafficLight, copyWidth);

        bufAddrC+=pitchC;
        pTrafficLight+=trafficLightWidth;
    }

    return 0;
}
