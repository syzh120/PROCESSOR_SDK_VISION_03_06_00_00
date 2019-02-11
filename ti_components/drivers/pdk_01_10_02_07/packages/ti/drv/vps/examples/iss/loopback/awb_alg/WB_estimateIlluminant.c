/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/************************************************************************************//**
* TI ISP Library Reference Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

#include <stdio.h>
#include <math.h>
//#include <memory.h>
#include <stdlib.h>

#include <inc/Image_Data_Handling.h>
#include <inc/spatial_domain.h>
#include <inc/white_balance.h>

Histogram h[3];

static int SATURATION_THRESHOLD = 250;  /*Gray pixel value above which it is considered to be saturated.  Value of 200 is set keeping in mind that the image data is not gamma corrcted*/

int WB_estimateIlluminant(Image *imgPtr, float percPix, Illuminant *Illum)
{
    int       i, j, cutoff[3] = {0}, test;
    long int  temp1, temp2;

    float     rgb2xyz[] =
    {0.4124564, 0.3575761, 0.1804375, 0.2126729, 0.7151522, 0.072175,
     0.0193339,
     0.119192,  0.9503041};
    float     A0     = -949.86315, A1 = 6253.80338, t1 = 0.92159, A2 =
        28.70599, t2 = 0.20039;
    float     A3     = 0.00004, t3 = 0.07125, xe = 0.3320, ye = 0.1858, n;
    float     XYZ[3] = {0.0, 0.0, 0.0};
    float     ftemp;

    temp2 = (int)(((float)imgPtr->rows * (float)imgPtr->cols * percPix) / 100.0);

    test = SDF_computeHistogram(imgPtr, &h[0], 'r');
    if(test != 1)
    {
        return test;
    }

    test = SDF_computeHistogram(imgPtr, &h[1], 'g');
    if(test != 1)
    {
        return test;
    }

    test = SDF_computeHistogram(imgPtr, &h[2], 'b');
    if(test != 1)
    {
        return test;
    }

    for(j = 0; j <= 2; j++) {
        temp1 = 0;
        for(i = SATURATION_THRESHOLD; i >= 0; i--) {
            if(temp1 >= temp2)
            {
                cutoff[j] = i;
                break;
            }
            else
            {
                temp1 = temp1 + h[j].hist[i];
            }
        }
    }

    for(j = 0; j <= 2; j++) {
        temp1 = 0;
        temp2 = 0;
        for(i = cutoff[j]; i <= SATURATION_THRESHOLD; i++) {
            temp1 = temp1 + (h[j].hist[i]);
            temp2 = temp2 + (i * h[j].hist[i]);
        }
        if(temp1 != 0)
        {
            Illum->RGB[j] = (int)((float)temp2 / (float)temp1);
        }
        else
        {
            Illum->RGB[j] = 255;
        }
    }

    /*
    If under some conditions, which have not yet been encounterd, any of the above division
    operations encunter divide by zero exception Illum->RGB[0,1,2] should be set to 255

    If divide by zero exception happens anywhere further in the code Illum->temperature
    should be set to 6500
    */

    for(i = 0; i <= 2; i++) {
        for(j = 0; j <= 2; j++) {
            XYZ[i] = XYZ[i] + rgb2xyz[i * 3 + j] * (float)Illum->RGB[j];
        }
    }

    ftemp  = XYZ[0] + XYZ[1] + XYZ[2];
    XYZ[0] = XYZ[0] / ftemp;
    XYZ[1] = XYZ[1] / ftemp;

    n = (XYZ[0] - xe) / (XYZ[1] - ye);

    Illum->temperature = A0 + A1 *exp(-n / t1) + A2 *exp(-n / t2) + A3 *exp(
        -n / t3);

    return 1;
}

