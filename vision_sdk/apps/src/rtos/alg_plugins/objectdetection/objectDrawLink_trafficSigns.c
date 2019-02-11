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

UInt8 gObjectDraw_trafficSigns_1[] = {
    #include "traffic_signs/000_1.h"
    #include "traffic_signs/001_1.h"
    #include "traffic_signs/002_1.h"
    #include "traffic_signs/003_1.h"
    #include "traffic_signs/004_1.h"
    #include "traffic_signs/005_1.h"
    #include "traffic_signs/006_1.h"
    #include "traffic_signs/007_1.h"
    #include "traffic_signs/008_1.h"
    #include "traffic_signs/009_1.h"
    #include "traffic_signs/010_1.h"
    #include "traffic_signs/011_1.h"
    #include "traffic_signs/012_1.h"
    #include "traffic_signs/013_1.h"
    #include "traffic_signs/014_1.h"
    #include "traffic_signs/015_1.h"
    #include "traffic_signs/016_1.h"
    #include "traffic_signs/017_1.h"
    #include "traffic_signs/018_1.h"
    #include "traffic_signs/019_1.h"
    #include "traffic_signs/020_1.h"
    #include "traffic_signs/021_1.h"
    #include "traffic_signs/022_1.h"
    #include "traffic_signs/023_1.h"
    #include "traffic_signs/024_1.h"
    #include "traffic_signs/025_1.h"
    #include "traffic_signs/026_1.h"
    #include "traffic_signs/027_1.h"
    #include "traffic_signs/028_1.h"
    #include "traffic_signs/029_1.h"
    #include "traffic_signs/030_1.h"
    #include "traffic_signs/031_1.h"

};

Int32 AlgorithmLink_objectDrawCopyTrafficSign(
    UInt8 *bufAddrY,
    UInt8 *bufAddrC,
    UInt32 pitchY,
    UInt32 pitchC,
    UInt32 bufWidth,
    UInt32 bufHeight,
    UInt32 startX,
    UInt32 startY,
    UInt32 trafficSignId,
    UInt32 trafficSignType
    )
{
    UInt8 *pTrafficSign;
    UInt8 *pTrafficSignList;
    UInt32 copyWidth, copyHeight, i;
    UInt32 trafficSignSize;
    UInt32 trafficSignWidth, trafficSignHeight;

    if(trafficSignId>=OBJECTDRAW_TRAFFIC_SIGN_MAX)
        return -1;

    trafficSignWidth = OBJECTDRAW_TRAFFIC_SIGN_WIDTH_1;
    trafficSignHeight = OBJECTDRAW_TRAFFIC_SIGN_HEIGHT_1;
    pTrafficSignList = gObjectDraw_trafficSigns_1;

    trafficSignSize = trafficSignWidth*trafficSignHeight*3/2;

    /* align to multiple of 2, since data format is YUV420 */
    startX = SystemUtils_floor(startX, 2);
    startY = SystemUtils_floor(startY, 2);

    /* clip the copy area to limit within buffer area */
    copyWidth = trafficSignWidth;
    copyHeight = trafficSignHeight;

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
    pTrafficSign = pTrafficSignList
                + trafficSignId*trafficSignSize;

    for(i=0; i<copyHeight; i++)
    {
        memcpy(bufAddrY, pTrafficSign, copyWidth);

        bufAddrY+=pitchY;
        pTrafficSign+=trafficSignWidth;
    }

    /* Copy C */
    pTrafficSign = pTrafficSignList
                + trafficSignId*trafficSignSize;

    pTrafficSign += trafficSignWidth*trafficSignHeight;

    for(i=0; i<copyHeight/2; i++)
    {
        memcpy(bufAddrC, pTrafficSign, copyWidth);

        bufAddrC+=pitchC;
        pTrafficSign+=trafficSignWidth;
    }

    return 0;
}












































