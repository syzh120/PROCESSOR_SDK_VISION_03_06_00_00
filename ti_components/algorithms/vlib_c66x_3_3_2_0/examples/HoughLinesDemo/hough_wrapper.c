/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ('TI Devices').  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ti/vlib/src/common/VLIB_test.h>
#include <ti/vlib/src/common/vlib_memory.h>
#include <ti/vlib/src/common/vlib_profile.h>
#include <ti/vlib/vlib.h>
#include "prototype.h"

#define W 360
#define H 120

#define NUMTHETA (267)
#define RHOMAX   (600)

extern short             TableSineBK_Minus80toPlus80resZeroPointSix_Q8[NUMTHETA];
extern short             TableCosineBK_Minus80toPlus80resZeroPointSix_Q8[NUMTHETA];
extern unsigned short    pEdgeMapList[2 * 30];


unsigned short    calculatedOutHoughSpace[NUMTHETA * RHOMAX];
unsigned short    ping[RHOMAX];
unsigned short    pong[RHOMAX];
unsigned short    pang[RHOMAX];
unsigned short    peng[RHOMAX];

int
VLIB_InitializeTrigLUTs(short *restrict pSin,
                        short *restrict pCos,
                        float ThetaMin,
                        float ThetaMax,
                        float NumThetaPoints)
{

    unsigned int    i;
    float           Theta;

    for( i = 0; i < NumThetaPoints; i++ ) {
        Theta = ThetaMin + i * (ThetaMax - ThetaMin) / (NumThetaPoints - 1);

        *(pSin + i) = (short)(floor(256 * sin(Theta * 0.017453) + 0.5));
        *(pCos + i) = (short)(floor(256 * cos(Theta * 0.017453) + 0.5));

    }

    return (0);
}

void main()
{
    /* Creating input image */
    int               i;
    unsigned short    x, y;
    unsigned char     Im[W * H];
    unsigned int      listsize[1];
    int               maxRho, maxTheta, maxVal, maxIndex;
    /* int result1,result2,errorCount; */

    short    sinLUT[NUMTHETA];
    short    cosLUT[NUMTHETA];

    VLIB_cache_init();
    VLIB_InitializeTrigLUTs(&sinLUT[0], &cosLUT[0], -80, 79.6, NUMTHETA);

    /* generating input image */
    memset(Im, 0, W * H);

    for( i=0; i < 30; i++ ) {
        x=i + 3;
        y=x * 2 + 10;
        Im[x + y * W]=1;
    }

    pgmwrite("hough_in211.pgm", W, H, Im, "test", (unsigned int)sizeof(char));

    /* Convert the binary image to Edge list */
    wrap_binarymatrix2index(Im, W, H, pEdgeMapList, listsize);

    /* Hough space voting */
    memset(calculatedOutHoughSpace, 0, 2 * NUMTHETA * RHOMAX);

    VLIB_houghLineFromList(
        pEdgeMapList,
        calculatedOutHoughSpace,
        W,         /* outBlkWidth */
        H,         /* outBlkHeight */
        30,           /* listSize */
        NUMTHETA,         /* thetaRange, */
        RHOMAX,         /* rhoMaxLength */
        sinLUT,
        cosLUT,
        ping,
        pong,
        pang,
        peng);

    /* Finding max */
    maxVal=0;

    for( i=0; i < NUMTHETA * RHOMAX; i++ ) {
        if( calculatedOutHoughSpace[i] > maxVal ) {
            maxVal= calculatedOutHoughSpace[i];
            maxIndex = i;
        }
    }

    /* maxIndex = maxRho + maxTheta*RHOMAX */
    maxRho   = maxIndex % RHOMAX;
    maxTheta = (maxIndex) / RHOMAX;

    /* printf("\n maxRho=%d",maxRho); */
    /* printf("\n maxTheta=%d",maxTheta); */

    for( i=0; i < NUMTHETA * RHOMAX; i++ ) {
        calculatedOutHoughSpace[i] = 30 * calculatedOutHoughSpace[i];
    }

    /*
        for(i=0;i<0*W*H;i++)
        {
            Im[i] = 0;
        }
    */
    pgmwrite("hough_space121.pgm", RHOMAX, NUMTHETA, (unsigned char *) calculatedOutHoughSpace, "test", (unsigned int)sizeof(char));
    draw_line(Im, W, H, maxRho, maxTheta, RHOMAX, sinLUT, cosLUT);
    pgmwrite("hough_out211.pgm", W, H, Im, "test", sizeof(char));

    printf("\n HOUGH TRANSFORM EXECUTION IS DONE - PLEASE SEE THE OUTPUT IMAGES\n");

}

