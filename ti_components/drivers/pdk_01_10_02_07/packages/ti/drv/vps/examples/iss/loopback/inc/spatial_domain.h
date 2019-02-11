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
* TI ISP Library Refernce Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

#ifndef SPATIAL_DOMAIN_H
#define SPATIAL_DOMAIN_H
#include <Image_Data_Handling.h>
//typedef unsigned char kz_pixel_t;  /* for 8 bit-per-pixel images */
#define uiNR_OF_GREY (256)

#define false 0
#define true 1

typedef struct
{
    int hist[256];
}Histogram;

/******************************************************************************//**
* FUNCTION: int SDF_computeHistogram(Image *ptr, int *h, char channel);
* perfoms
*         For a given image computes histogram of a color channel specified
* Returns
*         -1 for non 8/24/32 bit image, empty image or NULL value in histogram
*         pointer
*
*         0 if specified channel not available in the image
*
*         1 on success
*******************************************************************************/
int SDF_computeHistogram(Image *ptr, Histogram *h, char channel);

#endif
