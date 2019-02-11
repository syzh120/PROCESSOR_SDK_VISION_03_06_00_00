/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/* -------------------------------------------------------------------- */
/* NAME : evelib_harris_corner_detection_test.c                         */
/*                                                                      */
/* DESCRIPTION:                                                         */
/*                                                                      */
/* This file contains an Harris Corner Detection test                   */
/*                                                                      */
/* Author: Venkat Peddigari <venkatrpeddigari@ti.com>                   */
/* -------------------------------------------------------------------- */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "evestarterware.h"
#include "algframework.h"
#include "eve_profile.h"


#include "evelib_harris_corner_detection.h"
#include "../vlib/vcop_vec_gradients_xy_and_magnitude/inc/vcop_vec_gradients_xy_and_magnitude_c.h"
#include "../vlib/vcop_harrisScore_7x7/inc/vcop_harrisScore_7x7_cn.h"
#include "../vlib/vcop_nonMaxSuppress_mxn_S16/inc/vcop_nonMaxSuppress_mxn_16s_c.h"

#define COMPARE_REFERENCE

#define BLK_PAD_X        16
#define BLK_PAD_Y        16

#define BLK_WIDTH        32
#define BLK_HEIGHT       32

#define BLK_WIDTH_OUT    (BLK_WIDTH)
#define BLK_HEIGHT_OUT   (BLK_HEIGHT)

//#define IMG_WIDTH        (64) //64//624
//#define IMG_HEIGHT       (64) //64//336

#define IMG_WIDTH        (624) //64//624
#define IMG_HEIGHT       (464) //64//336

#define IMG_LINE_PITCH   (IMG_WIDTH + BLK_PAD_X)

#define IMG_WIDTH_OUT    (IMG_WIDTH + BLK_PAD_X)
#define IMG_HEIGHT_OUT   (IMG_HEIGHT + BLK_PAD_Y) // + 8)

uint8_t input[IMG_LINE_PITCH*IMG_HEIGHT_OUT];
uint8_t output[IMG_WIDTH_OUT*IMG_HEIGHT_OUT];

int16_t X[IMG_WIDTH_OUT*IMG_HEIGHT_OUT] = {0};
int16_t Y[IMG_WIDTH_OUT*IMG_HEIGHT_OUT] = {0};

int16_t refX[IMG_WIDTH_OUT*IMG_HEIGHT_OUT] = {0};
int16_t refY[IMG_WIDTH_OUT*IMG_HEIGHT_OUT] = {0};

int16_t refGradX[IMG_WIDTH_OUT*IMG_HEIGHT_OUT];
int16_t refGradY[IMG_WIDTH_OUT*IMG_HEIGHT_OUT];
int16_t refMag[IMG_WIDTH_OUT*IMG_HEIGHT_OUT];
int16_t refHarrisScore[IMG_WIDTH_OUT*IMG_HEIGHT_OUT];
uint8_t refOutput[IMG_WIDTH_OUT*IMG_HEIGHT_OUT];

static void CreatePattern2(unsigned char *p, unsigned short w, unsigned short h)
{
    int i;
    //srand(1);
    for (i = 0; i < w*h; i++)
    {
        p[i] =  rand()&0xFF; //(x | y) / 2 + 127; //rand()&0xFF;
    }
}

int main()
{
    int i=0, j=0, fail = 0;
    int t0=0, t1=0, tdiff=0, tmcpfX16=0, tmcpsX16=0, tpixX16 = 0;
    int nFeatures = 0, nRefFeatures = 0;
    int numSlices = 1;
    short harrisScoreScalingFactor = 1310;
    short nmsThresh = 14000;
    char *status = "UNKNOWN";
    unsigned int tcntr0, tcntr1, overflow, profile_sctm;

    /*------------------------------------------------------------*/
    /* This function actually sets Enable bit in the CT CNTL      */
    /* register of SCTM. Parameter CTM is defined in              */
    /* baseaddress.h, and is used by cred macros to compute       */
    /* baseaddress of CTM.                                        */
    /*------------------------------------------------------------*/
    EVE_SCTM_Enable(CTM);

    /*------------------------------------------------------------*/
    /* Configure Counter 0, to measure "vcop_busy" which is a     */
    /* duration signal, and enable the counter.                   */
    /*------------------------------------------------------------*/
    EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
    EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
#if 0
    srand(1);
    for(i=0; i<IMG_LINE_PITCH*IMG_HEIGHT_OUT; i++)
    {
       input[i] = rand() % FF;
    }
#else
  srand(4);
  CreatePattern2(input, IMG_WIDTH+BLK_PAD_X, IMG_HEIGHT+BLK_PAD_Y);
#endif
    memset(output, 0, sizeof(output));
    memset(refOutput, 0, sizeof(refOutput));

    memset(refGradX,0,sizeof(refGradX));
    memset(refGradY,0,sizeof(refGradY));
    memset(refMag  ,0,sizeof(refMag)  );
    memset(refHarrisScore, 0, sizeof(refHarrisScore));

#ifdef COMPARE_REFERENCE
    int m = 7, n = 7;
    vcop_vec_gradients_xy_and_magnitude_cn(input,
                                          (refGradX+IMG_LINE_PITCH+1),
                                          (refGradY+IMG_LINE_PITCH+1),
                                          (refMag+IMG_LINE_PITCH+1),
                                          IMG_WIDTH_OUT,
                                          IMG_HEIGHT_OUT-2,
                                          IMG_LINE_PITCH);

    vcop_harrisScore_7x7_cn((refGradX+IMG_LINE_PITCH+1),
                            (refGradY+IMG_LINE_PITCH+1),
                            IMG_LINE_PITCH,
                            IMG_HEIGHT_OUT,
                            refHarrisScore + (((m/2 + 1) * IMG_LINE_PITCH) + (n/2 + 1)),
                            harrisScoreScalingFactor);

    vcop_nonMaxSuppress_mxn_16s_cn((uint16_t *)refHarrisScore,
                                   refOutput,
                                   IMG_HEIGHT_OUT,
                                   IMG_LINE_PITCH,
                                   m,
                                   n,
                                   nmsThresh);

    /* populate the index positions of all corners found and number of features or corners */
    for (i = ((BLK_PAD_Y/2)-1); i < (IMG_HEIGHT + ((BLK_PAD_Y/2) - 1)) ; i++)
    {
        for (j = ((BLK_PAD_X/2) - 1); j < (IMG_WIDTH + ((BLK_PAD_X/2) - 1)); j++)
        {
            if (refOutput[(i-m/2)*IMG_WIDTH_OUT+(j-n/2)])
            {
                refY[nRefFeatures] = (i)<<4;
                refX[nRefFeatures] = (j)<<4;
                nRefFeatures++;
            }
        }
    }

    fail = 0;
#endif

    _tsc_start();

    tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    t0 = _tsc_gettime();

    EVELIB_harrisCornerDetection(input, IMG_WIDTH, IMG_HEIGHT, IMG_LINE_PITCH, IMG_HEIGHT_OUT, 1, output, IMG_WIDTH_OUT, IMG_HEIGHT_OUT,
                                 IMG_WIDTH_OUT, IMG_HEIGHT_OUT, BLK_WIDTH, BLK_HEIGHT, 1, harrisScoreScalingFactor, nmsThresh);

    t1 = _tsc_gettime();

    tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
    if(overflow) {
        TEST_PRINTF("Counter overflow!!!\n");
    }
    profile_sctm = ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0)) << 1;

    /* populate the index positions of all corners found and number of features or corners */
    for (i = ((BLK_PAD_Y/2)-1); i < (IMG_HEIGHT + ((BLK_PAD_Y/2) - 1)) ; i++)
    {
        for (j = ((BLK_PAD_X/2) - 1); j < (IMG_WIDTH + ((BLK_PAD_X/2) - 1)); j++)
        {
            if (output[i*IMG_WIDTH_OUT+j])
            {
                Y[nFeatures] = ((i-0)<<4);
                X[nFeatures] = ((j-0)<<4);
                nFeatures++;
            }
        }
    }


#ifdef COMPARE_REFERENCE

#if 1
    for (i = ((BLK_PAD_Y/2)-1); i < (IMG_HEIGHT + ((BLK_PAD_Y/2) - 1)) ; i++)
    {
        for (j = ((BLK_PAD_X/2) - 1); j < (IMG_WIDTH + ((BLK_PAD_X/2) - 1)); j++)
        {
           if(output[i*IMG_WIDTH_OUT+j] != refOutput[(i-m/2)*IMG_WIDTH_OUT+(j-n/2)])
           {
             fail = 1;
           }
        }
    }
#endif
    printf("\n CURR Num Features = %2d, || REF Num Features = %2d \n", nFeatures, nRefFeatures);

#if 1
    if(nFeatures == nRefFeatures)
    {
        for (i = 0; i < nFeatures; i++)
        {
            if(refY[i] != Y[i])
            {
                fail = 1;
                break;
            }

            if(refX[i] != X[i])
            {
                fail = 1;
                break;
            }
        }
    }
    else
    {
        fail = 1;
    }
    if(fail ==1 )
    {
      printf("\n CURR Num Features = %2d, || REF Num Features = %2d \n", nFeatures, nRefFeatures);
      for (i = 0; i < nFeatures; i++)
      {
          printf("CURR: %2d, %2d, || REF :%2d, %2d", X[i]>>4, Y[i]>>4,refX[i]>>4,refY[i]>>4);
          //printf("CURR: %2d, %2d, || REF :%2d, %2d", X[i], Y[i],refX[i],refY[i]);
          if((refY[i] != Y[i]) || (refX[i] != X[i]))
          {
            printf("******************\n");
           }
          else
          {
            printf("\n");
          }
      }
    }
#endif
    status = fail? "FAILED" : "PASSED";

#endif
    printf("SCTM Cycles %d\n",profile_sctm);
    tdiff = (t1-t0)*2;
    tmcpfX16 = tdiff*16 / 1000000;
    tmcpsX16 = tmcpfX16*30;
    tpixX16  = tdiff * 16 / (IMG_WIDTH*IMG_HEIGHT);

#ifdef EN_ZEBU_TEST
    TEST_PRINTF("\n%s %s %s %s %s %s %s %s %s %s %s\n", \
            "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
    TEST_PRINTF("\n%s %s %s\n", "EVELIB HarrisCornerDetection", status, "");
#else
    TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %15s %20s %10s %16s    %s", \
            "Algorithm", "Status", "Width", "Height", "NumSlices", "VCOPCycPerFr", "MegaCycPerFr", \
            "MegaCycPerSec(30Fr)", "CycPerPix", "TimePerFr(MSec)", "Comments");
    TEST_PRINTF("\n%-20s %10s %10d %10d %10d %15d %15.2f %20.2f %10.2f %16.2f    %s\n", "EVELIB HarrisCornerDetection", status, IMG_WIDTH, IMG_HEIGHT,
        numSlices, tdiff, (tmcpfX16/16.0), (tmcpsX16/16.0), (tpixX16/16.0), (tmcpfX16*1000/16.0/500.0), "");

    TEST_PRINTF("\n%-20s %25s %20s %20s %20s %20s %20s    %s", \
            "Algorithm", "Scratch(.far/.fardata)", "Const(.const)", "Program(.text)", "DDRTrfrIn", "DDRTrfrOut", "DDRTrfrTot", "Comments");
    TEST_PRINTF("\n%-20s %25d %20d %20d %20.1f %20.1f %20.1f    %s\n","EVELIB HarrisCornerDetection", 0, 1, 27, 1.0, 1.0, 2.0, "");
#endif

    return fail;
}

