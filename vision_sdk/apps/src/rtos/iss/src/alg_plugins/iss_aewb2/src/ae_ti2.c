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
/*
 *  ======== ae_ti.c ========
 *  TI's implementation of the AE algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by xDAIS.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/iae.h"
#include <src/rtos/utils_common/include/utils_mem.h>

#include "./ae_ti.h"
#include "./ae_ti_priv.h"

/* #define __DEBUG */
#ifdef __DEBUG
#define AE_DEBUG_PRINTS
#endif

/* #define AE_DEBUG */

static XDAS_UInt32 numAEChannels;


/*
 *  ======== AE_TI_alloc ========
 */
static Int AE_TI_alloc(const IALG_Params * algParams,
        IALG_Fxns ** pf, IALG_MemRec memTab[])
{
    IAE_Params *params = (IAE_Params *) algParams;
    int numTabs = 1;

    /* Request memory for my object */
    memTab[0].size = sizeof(AE_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    memTab[1].size = sizeof(XDAS_UInt32) * (params->numHistory + 1) * NCAM;
    memTab[1].alignment = 0;
    memTab[1].space = IALG_EXTERNAL;
    memTab[1].attrs = IALG_PERSIST;
    numTabs++;
    return (numTabs);
}

/*
 *  ======== AE_TI_free ========
 */
static Int AE_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    AE_TI_Obj *h = (AE_TI_Obj *) handle;
    int numTabs = 0;
    /* Request memory for my object */
    memTab[0].size = sizeof(AE_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    memTab[1].size = sizeof(XDAS_UInt32) * h->numHistory + 1;
    memTab[1].alignment = 0;
    memTab[1].space = IALG_EXTERNAL;
    memTab[1].attrs = IALG_PERSIST;
    numTabs++;
    return (numTabs);
}

/*
 *  ======== AE_TI_initObj ========
 */
static Int AE_TI_init(IALG_Handle handle,
        const IALG_MemRec memTab[], IALG_Handle p,
        const IALG_Params * algParams)
{
    AE_TI_Obj *h = (AE_TI_Obj *) handle;
    IAE_Params *params = (IAE_Params *) algParams;
    int i;

    if (handle == NULL)
        return (IAE_EFAIL);
    if (params == NULL)
    {
        /* no static parameters passed in, use default */
        h->numHistory = 1;
        h->numSmoothSteps = 1;
        h->cam_histY[0] = NULL;
        h->cam_histY[1] = NULL;
        h->cam_histY[2] = NULL;
        h->cam_histY[3] = NULL;
    }
    else if (params->size != sizeof(IAE_Params))
    {
        return (IAE_EUNSUPPORTED);
    } else if ( (params->numChannels > IAE_MAX_CHANNELS) || (params->numChannels < IAE_MIN_CHANNELS)) {
        return (IAE_EUNSUPPORTED);
    } else
    {
        h->numHistory = params->numHistory + 1;
        h->numSmoothSteps = params->numSmoothSteps;
        if (h->numSmoothSteps < 0) h->numSmoothSteps = 1;
        if (h->numSmoothSteps > 10) h->numSmoothSteps = 10;
        h->cam_histY[0] = memTab[1].base;
        h->cam_histY[1] = &h->cam_histY[0][h->numHistory];
        h->cam_histY[2] = &h->cam_histY[1][h->numHistory];
        h->cam_histY[3] = &h->cam_histY[2][h->numHistory];
        for (i = 0; i < h->numHistory; i++)
        {
            h->cam_histY[0][i] = -1;
            h->cam_histY[1][i] = -1;
            h->cam_histY[2][i] = -1;
            h->cam_histY[3][i] = -1;
        }
    }
    h->numRanges = 0;
    h->exposureTimeStepSize = 1;
    h->targetBrightness = 40;
    h->targetBrightnessRange.min = h->targetBrightness - 5;
    h->targetBrightnessRange.max = h->targetBrightness + 5;
    h->thrld = 10;

    numAEChannels = params->numChannels;
    for(i=0;i<numAEChannels;i++)
    {
        h->prevAE.exposureTime = (XDAS_Int32)1000;
        h->prevAE.apertureLevel = (XDAS_Int32)0;
        h->prevAE.sensorGain = (XDAS_Int32)1000;
        h->prevAE.ipipeGain = (XDAS_Int32)128;
    }

    for (i = 0; i < NCAM; i++)
    {
        h->cam_group[i] = 0;
        h->cam_sumY[i] = -1;
    }

    return (IAE_EOK);
}
static Int32 clip_int(Int32 v, Int32 vmin, Int32 vmax)
{
    if (v < vmin) return vmin;
    if (v > vmax) return vmax;
    return v;
}


static void search_in_range(float ex,
        Int32 Amin, Int32 Amax, Int32* pA,
        Int32 Tmin, Int32 Tmax, Int32 Tstep, int* pT,
        Int32 AGmin, Int32 AGmax, Int32* pAG,
        Int32 DGmin, Int32 DGmax, Int32* pDG)
{
    ex *= Amin;
    *pA = clip_int(ex, Amin, Amax);
    ex /= (*pA);

    ex *= Tmin;
    *pT = clip_int((int)(ex/Tstep)*Tstep, Tmin, Tmax);
    ex /= (*pT);

    ex *= AGmin;
    *pAG = clip_int(ex, AGmin, AGmax);
    ex /= *pAG;

    ex *= DGmin;
    *pDG = clip_int(ex, DGmin, DGmax);
    ex /= (*pDG);

}

static Int32 search_range_ATG_dec_gain(Int32 adjRatio,
        Int32 cA, Int32 cT, Int32 cAG, Int32 cDG,
        IAE_Range rA, IAE_Range rT, IAE_Range rAG,
        IAE_Range rDG, Int32 Tstep, Int32 *pA, Int32 *pT,
        Int32 *pAG, Int32 *pDG)
{
    Int32 Tmin = (rT.min+Tstep-1) / Tstep * Tstep;
    Int32 Tmax = rT.max / Tstep * Tstep;
    if (Tmin > Tmax || Tmin <= 0)
    {
        Tmin = Tmax;
    }
#ifdef AE_DEBUG
    Vps_printf("\nAE debug: dec Tmin=%d, Tmax=%d, Tstep=%d\n", Tmin, Tmax, Tstep);
#endif
    float tm = (float)rA.min * Tmin * rAG.min * rDG.min;
    float tc = (float)cA * cT * cAG * cDG;

    if (tm*1024 <= adjRatio*tc)
    {
        float ex = tc * adjRatio / 1024 / tm;
        search_in_range(ex,
                rA.min, rA.max, pA,
                Tmin, Tmax, Tstep, pT,
                rAG.min, rAG.max, pAG,
                rDG.min, rDG.max, pDG);
        return 1;
    }
    *pA = rA.min;
    *pT = Tmin;
    *pAG = rAG.min;
    *pDG = rDG.min;

    return 0;
}

static Int32 search_range_ATG_inc_gain(int adjRatio,
        Int32 cA, Int32 cT, Int32 cAG, Int32 cDG,
        IAE_Range rA, IAE_Range rT, IAE_Range rAG,
        IAE_Range rDG, Int32 Tstep, Int32 *pA, Int32 *pT,
        Int32 *pAG, Int32 *pDG)
{
    Int32 Tmin = (rT.min+Tstep-1) / Tstep * Tstep;
    Int32 Tmax = rT.max / Tstep * Tstep;
    if (Tmin > Tmax || Tmin <= 0)
    {
        Tmin = Tmax;
    }
#ifdef AE_DEBUG
    Vps_printf("\nAE debug: inc Tmin=%d, Tmax=%d, Tstep=%d\n", Tmin, Tmax, Tstep);
#endif
    float tm = (float)rA.max * Tmax * rAG.max * rDG.max;
    float tc = (float)cA * cT * cAG * cDG;

    if (tm*1024 >= adjRatio*tc)
    {
        float ex = tc * adjRatio / 1024 / rA.min / Tmin / rAG.min / rDG.min;
        search_in_range(ex,
                rA.min, rA.max, pA,
                Tmin, Tmax, Tstep, pT,
                rAG.min, rAG.max, pAG,
                rDG.min, rDG.max, pDG);
        return 1;
    }
    *pA = rA.max;
    *pT = Tmax;
    *pAG = rAG.max;
    *pDG = rDG.max;

    return 0;
}

static UInt32 calc_curY(IAEWB_Rgb rgbData[], XDAS_UInt8 weight[], Int32 width, Int32 height, Int32 nPix, UInt32 rY, UInt32 gY, UInt32 bY)
{
    int i, j;
    UInt32 rSum = 0, bSum = 0, gSum = 0, wSum = 0;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            rSum += (UInt32) rgbData[i * width + j].r * weight[i * width + j];
            gSum += (UInt32) rgbData[i * width + j].g * weight[i * width + j];
            bSum += (UInt32) rgbData[i * width + j].b * weight[i * width + j];
            wSum += weight[i * width + j];
        }
    }

    rSum >>= 8;
    gSum >>= 8;
    bSum >>= 8;
    wSum *= nPix;
    if (wSum < 1) wSum = 1;

    UInt32 curY = (rSum * rY + gSum * gY + bSum * bY + (wSum >> 1)) / wSum;

    if (curY == 0) return 1;
    return curY;
}

static Int32 abs_int(Int32 x)
{
    if (x < 0) return -x;
    return x;
}
/*
 *  ======== AE_TI_process ========
 */
#define SAT_Y              180
#define UND_Y              25    //10
#define THR_Y              5

static void update_hist(int reset, Int32 curY, Int32 *p_sumY, Int32 histY[], Int32 numHist)
{
    int i;
    if (reset)
    {
        *p_sumY = curY * numHist;
        for (i = 0; i < numHist; i++)
        {
            histY[i] = curY;
        }
    }
    else
    {
        /* update sumY */
        *p_sumY = *p_sumY + curY - histY[numHist - 1];

        /* update history */
        for (i = numHist - 1; i > 0; i--)
        {
            histY[i] = histY[i - 1];
        }
        histY[0] = curY;
    }
    if (*p_sumY < 1) *p_sumY = 1;
}

static int update_lock(int reset, Int32 curY, Int32 sumY,
        Int32 tgtY, Int32 tgtMin, Int32 tgtMax,
        Int32 thrld, Int32 nHist, Int32 *p_locked, Int32 *p_lockCnt)
{
    if (reset)
    {
        *p_locked = 0;
        *p_lockCnt = 0;
        return 0;
    }

    if( curY > (tgtY*5) )
    {
        *p_locked = 0;
        *p_lockCnt = 0;
        return 0;        
    }   
     
    if (abs_int(sumY - tgtY * nHist) < thrld * nHist && *p_locked)
    {
        return 1;
    }
    if ((curY > tgtMin && curY < tgtMax) || (sumY > tgtMin * nHist && sumY < tgtMax * nHist))
    {
        *p_lockCnt = *p_lockCnt + 1;
    }
    else if (*p_lockCnt > 0)
    {
        *p_lockCnt = *p_lockCnt - 1;
    }

    if (*p_lockCnt >= 3)
    {
        *p_lockCnt = 3;
        *p_locked = 1;
        return 1;
    }
    else if (*p_lockCnt > 0 && *p_locked)
    {
        return 1;
    }
    return 0;
}

static Int32 update_adjRatio(Int32 curY, Int32 tgtY, int nSteps)
{
    Int32 adjRatio = tgtY * 1024 / curY;
    // adjust the ratio
    int delta = 100 * (11-nSteps) / 10;
    if (adjRatio > 16384)
    {
        adjRatio = 16384;
    }
    else if (adjRatio < 64)
    {
        adjRatio = 64;
    }                      
    else if (adjRatio > 8192)
    {
        adjRatio = 8192;
    }
    else if (adjRatio < 128)
    {
        adjRatio = 128;
    }
    /* x7 */
    else if (adjRatio > 7168)
    {
        adjRatio = 7168;
    }
    else if (adjRatio < 146)
    {
        adjRatio = 146;
    }
    /* x6 */
    else if (adjRatio > 6144)
    {
        adjRatio = 6144;
    }
    else if (adjRatio < 171)
    {
        adjRatio = 171;
    }
    /* x5 */
    else if (adjRatio > 5120)
    {
        adjRatio = 5120;
    }
    else if (adjRatio < 205)
    {
        adjRatio = 205;
    }
    
    else if (adjRatio > 4096)
    {
        adjRatio = 4096;
    }
    else if (adjRatio < 256)
    {
        adjRatio = 256;
    }
    else if (adjRatio > 2048)
    {
        adjRatio = 2048;
    }
    else if (adjRatio < 512)
    {
        adjRatio = 512;
    }
    else if (adjRatio > 1536)
    {
        adjRatio = 1331;
    }
    else if (adjRatio < 682)
    {
        adjRatio = 788;
    }
    else if (adjRatio > 1331)
    {
        adjRatio = 1228;
    }
    else if (adjRatio < 788)
    {
        adjRatio = 853;
    }
    else if (adjRatio > 1024 + delta)
    {
        adjRatio = 1024 + delta;
    }
    else if (adjRatio < 1024 - delta)
    {
        adjRatio = 1024 - delta;
    }
    return adjRatio;
}

static void update_exposure(AE_TI_Obj *h, Int32 adjRatio,
        Int32 cA, Int32 cT, Int32 cAG, Int32 cDG,
        Int32 *p_nA, Int32 *p_nT, Int32 *p_nAG, Int32 *p_nDG)
{
    int i, r = 0;
    if (adjRatio >= 1024)  //increase gain
    {
        for (i = 0; i < h->numRanges; i++)
        {
            r = search_range_ATG_inc_gain(adjRatio,
                    cA, cT, cAG, cDG,
                    h->apertureLevelRange[i],
                    h->exposureTimeRange[i],
                    h->sensorGainRange[i],
                    h->ipipeGainRange[i],
                    h->exposureTimeStepSize,
                    p_nA, p_nT, p_nAG, p_nDG);
            if (r == 1)
            {
                break;
            }
        }
    }
    else if (adjRatio < 1024) //decrease gain
    {
        for (i = h->numRanges-1; i>=0; i--)
        {
            r = search_range_ATG_dec_gain(adjRatio,
                    cA, cT, cAG, cDG,
                    h->apertureLevelRange[i],
                    h->exposureTimeRange[i],
                    h->sensorGainRange[i],
                    h->ipipeGainRange[i],
                    h->exposureTimeStepSize,
                    p_nA, p_nT, p_nAG, p_nDG);
            if (r == 1)
            {
                break;
            }
        }
    }
}
static void calc_exposure(AE_TI_Obj *h, Int32 curY, Int32 *p_locked, IAEWB_Ae *p_prevAE, IAEWB_Ae *p_nextAE)
{
    *p_locked = 0;
    Int32 adjRatio = update_adjRatio(curY, h->targetBrightness, h->numSmoothSteps);

    Int32 cT  = p_prevAE->exposureTime;
    Int32 cAG = p_prevAE->sensorGain;
    Int32 cA  = p_prevAE->apertureLevel;
    Int32 cDG = p_prevAE->ipipeGain;
    Int32 nA = cA;
    Int32 nT = cT;
    Int32 nAG = cAG;
    Int32 nDG = cDG;

    update_exposure(h, adjRatio, cA, cT, cAG, cDG, &nA, &nT, &nAG, &nDG);

    /* now output the AE settings for next frame(s) */
    p_prevAE->exposureTime  = p_nextAE->exposureTime  = nT;
    p_prevAE->apertureLevel = p_nextAE->apertureLevel = nA;
    p_prevAE->sensorGain    = p_nextAE->sensorGain    = nAG;
    p_prevAE->ipipeGain     = p_nextAE->ipipeGain     = nDG;
}

static void calc_groupYs(int cam_group[], UInt32 cam_Ys[], int ref_in_group[], IAEWB_Ae cam_prevAE[], UInt32 grp_Ys[])
{
    UInt32 sY[NCAM] = {0, 0, 0, 0};
    UInt32 sC[NCAM] = {0, 0, 0, 0};
    int i;
    for (i = 0; i < NCAM; i++)
    {
        int gid = cam_group[i];
        sC[gid]++;
        if (i == ref_in_group[i] || cam_prevAE[i].sensorGain == 0 || cam_prevAE[i].exposureTime == 0)
        {
            sY[gid] += cam_Ys[i];
        }
        else
        {
            int w = cam_prevAE[ref_in_group[i]].sensorGain * 512 /  cam_prevAE[i].sensorGain;
            w = w * cam_prevAE[ref_in_group[i]].exposureTime / cam_prevAE[i].exposureTime;
            sY[gid] += (w * cam_Ys[i]) >> 9;
        }
    }


    for (i = 0; i < NCAM; i++)
    {
        int gid = cam_group[i];
        if (sC[gid] == 0)
        {
            grp_Ys[i] = sY[gid];
        }
        else
        {
            grp_Ys[i] = sY[gid] / sC[gid];
        }
        if (grp_Ys[i] < 1)
        {
            grp_Ys[i] = 1;
        }
    }
}

static void swap2(UInt32 *p)
{
    UInt32 t = p[0];
    p[0] = p[1];
    p[1] = t;
}

static void sort(UInt32 a[], UInt32 s[], UInt32 idx[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        s[i] = a[i];
        idx[i] = i;
        for (j = i; j > 0; j--)
        {
            if (s[j] >= s[j-1])
            {
                break;
            }
            swap2(&s[j-1]);
            swap2(&idx[j-1]);
        }
    }
}

static int find_group(UInt32 curYs[], IAEWB_Ae cam_prevAE[], Int32 cam_group[], Int32 is_wdr)
{
    UInt32 y[NCAM], ys[NCAM], yi[NCAM], group[NCAM];
    int i;
    int ratio1 = 7, ratio2 = 6;
    if (is_wdr) 
    {
        ratio1 = 16;
        ratio2 = 14;
    }

    for (i = 0; i < NCAM; i++)
    {
        y[i] = cam_prevAE[i].exposureTime * cam_prevAE[i].sensorGain >> 10; 
        if (y[i] < 1) y[i] = 1;
        y[i] = curYs[i] * 33333*4 / y[i];
        if (y[i] < 1) y[i] = 1;
    }

    sort(y, ys, yi, NCAM);

    if (cam_group[0] == 0 && cam_group[1] == 0 && cam_group[2] == 0 && cam_group[3] == 0)
    {
        if (ys[3] < ratio1 * ys[0])
        {
            return 0;
        }
    }

    if ( ys[3] < ratio2 * ys[0] )
    {
        group[0] = group[1] = group[2] = group[3] = 0;
    }
    else
    {
        int r1 = ys[1] * 100 / ys[0];
        int r2 = ys[2] * 100 / ys[1]; 
        int r3 = ys[3] * 100 / ys[2];
        if (r1 >= r2 && r1 >= r3)      // 1 + 3
        {
            group[yi[0]] = 0;
            group[yi[1]] = 1;
            group[yi[2]] = 1;
            group[yi[3]] = 1;
        }
        else if (r3 >= r1 && r3 >= r2) // 3 + 1
        {
            group[yi[0]] = 0;
            group[yi[1]] = 0;
            group[yi[2]] = 0;
            group[yi[3]] = 1;
        }
        else                          // 2 + 2
        {
            group[yi[0]] = 0;
            group[yi[1]] = 0;
            group[yi[2]] = 1;
            group[yi[3]] = 1;
        }
    }

    int regroup = 0;
    for (i = 0; i < NCAM; i++)
    {
        if (cam_group[i] != group[i]) regroup = 1;
    }

    if (regroup)
    {
        for (i = 0; i < NCAM; i++)
        {
            cam_group[i] = group[i];
        }
    }
    return regroup;
}

int ae_count = 0;
static XDAS_Int32 AE_TI_process(IAE_Handle handle, IAE_InArgs * inArgs,
        IAE_OutArgs * outArgs, IAEWB_Rgb * rgbData,
        XDAS_UInt8 * weight, void *customData)
{

    AE_TI_Obj *h = (AE_TI_Obj *) handle;
    int i;

    UInt32 h_cnt = inArgs->statMat.winCtHorz;
    UInt32 v_cnt = inArgs->statMat.winCtVert / NCAM;
    ae_count++;
    if( ae_count % 1 != 0 )
    {
        return IAE_EOK;
    }
    if( ae_count % 20 == 0  )
    {
        //Vps_printf("numSmoothSteps = %d",h->numSmoothSteps);
    }

    UInt32 curYs[NCAM];
    for (i = 0; i < NCAM; i++)
    {
        curYs[i] = calc_curY(
                &rgbData[h_cnt * v_cnt * i], 
                &weight[h_cnt * v_cnt * i], 
                h_cnt,
                v_cnt,
                inArgs->statMat.pixCtWin,
                (0x4d * inArgs->curWb.rGain + 512) >> 10,
                (0x96 * inArgs->curWb.gGain + 512) >> 10,
                (0x1d * inArgs->curWb.bGain + 512) >> 10);
    }

    // group cameras
    UInt32 wdr_mode = * ((UInt32*)customData);
    int regroup = find_group(curYs, h->cam_prevAE, h->cam_group, wdr_mode);

    // find the first camera in a group; check reset conditions
    int reset = inArgs->curAe.exposureTime % h->exposureTimeStepSize != 0;
    int cam_reset[NCAM] = {0,0,0,0};
    int ref_in_group[NCAM] = {0, 0, 0, 0};

    //    start of new method to find ref in the group
#define FIRST_IN_GRP_INIT  (16384)
    int gid, diff, min, minIdx;
    for( gid = 0; gid < 2; gid++ )
    {
        min    = FIRST_IN_GRP_INIT;
        minIdx = 0;
        for( i = 0; i < NCAM; i++ )
        {
            if( h->cam_group[i] == gid )
            {
                diff = curYs[i] - h->targetBrightness;
                diff = diff < 0 ? (-diff) : diff;

                if( min == FIRST_IN_GRP_INIT )
                {
                    min    = diff;
                    minIdx = i;
                }
                else
                {    
                    if( min > diff )
                    {
                        min = diff;
                        minIdx = i;                            
                    }    
                }
            }
        }
        for( i = 0; i < NCAM; i++ )
        {
            if( h->cam_group[i] == gid )
            {
                ref_in_group[i] = minIdx;
            }
        }
    }
    for (i = 0; i < NCAM; i++)
    {
        cam_reset[i] = regroup || (h->cam_sumY[i] < 0);
        if (reset)
        {
            h->cam_group[i] = 0;
            cam_reset[i] = 1;
            ref_in_group[i] = 0;
        }
    }    
    // end of new method to find ref in the group

    // group average
    UInt32 groupYs[NCAM] = {0, 0, 0, 0};
    calc_groupYs(h->cam_group, curYs, ref_in_group, h->cam_prevAE, groupYs);

    // now update the history brightnesss data
    for (i = 0; i < NCAM; i++)
    {
        if (i == ref_in_group[i])
        {
            update_hist(cam_reset[i], groupYs[i], &h->cam_sumY[i], &h->cam_histY[i][0], h->numHistory);
        }
    }

    Int32 tgtY = h->targetBrightness;
    Int32 nhist = h->numHistory;
    Int32 minY = h->targetBrightnessRange.min;
    Int32 maxY = h->targetBrightnessRange.max;
    Int32 thr = h->thrld;

    for (i = 0; i < NCAM; i++)
    {
        int first = ref_in_group[i];
        if (first == i)
        {
            int lockst = update_lock(cam_reset[i], groupYs[i], h->cam_sumY[i], tgtY, minY, maxY, thr, nhist, &h->cam_locked[i], &h->cam_lockCnt[i]);
            if (lockst)
            {
                outArgs->cam_nextAe[i] = h->cam_prevAE[i];
            }
            else
            {
                calc_exposure(h, groupYs[i], &h->cam_locked[i], &h->cam_prevAE[i], &outArgs->cam_nextAe[i]);
            }
        }
        else
        {
            h->cam_prevAE[i] = outArgs->cam_nextAe[i] = outArgs->cam_nextAe[first];
        }
    }

    return (IAE_EOK);
}

    /*
     *  ======== AE_TI_control ========
     */
static XDAS_Int32 AE_TI_control(IAE_Handle handle, IAE_Cmd id,
            IAE_DynamicParams * params, IAE_Status * status)
{
    XDAS_Int32 retVal;
    AE_TI_Obj *h = (AE_TI_Obj *) handle;
    int i;
    /* validate arguments - this codec only supports "base" xDM. */
    if (params->size != sizeof(*params))
    {

        return (IAE_EUNSUPPORTED);
    }

    switch (id)
    {
        case IAE_CMD_SET_CONFIG:
            if (params->numRanges > IAE_MAX_RANGES)
            {
                retVal = IAE_EFAIL;
            }
            else
            {
                h->numRanges = params->numRanges;
                for (i = 0; i < h->numRanges; i++)
                {
                    h->exposureTimeRange[i] = params->exposureTimeRange[i];
                    h->apertureLevelRange[i] = params->apertureLevelRange[i];
                    h->sensorGainRange[i] = params->sensorGainRange[i];
                    h->ipipeGainRange[i] = params->ipipeGainRange[i];
                }
                h->targetBrightnessRange = params->targetBrightnessRange;
                h->thrld = params->thrld;
                h->targetBrightness = params->targetBrightness;
                h->exposureTimeStepSize = params->exposureTimeStepSize;
                for (i = 0; i < h->numHistory; i++)
                {
                    h->cam_histY[0][i] = -1;
                    h->cam_histY[1][i] = -1;
                    h->cam_histY[2][i] = -1;
                    h->cam_histY[3][i] = -1;
                }
#ifdef AE_DEBUG_PRINTS
                Vps_printf("exposureTime Range = %d, %d, %d\n",
                        h->exposureTimeRange[0].min, h->exposureTimeRange[0].max,
                        h->exposureTimeStepSize);
                Vps_printf("setup dynamic parameters \n");
#endif
                retVal = IAE_EOK;
            }
            break;
        case IAE_CMD_GET_CONFIG:
            params->numRanges = h->numRanges;
            for (i = 0; i < h->numRanges; i++)
            {
                params->exposureTimeRange[i] = h->exposureTimeRange[i];
                params->apertureLevelRange[i] = h->apertureLevelRange[i];
                params->sensorGainRange[i] = h->sensorGainRange[i];
                params->ipipeGainRange[i] = h->ipipeGainRange[i];
            }
            params->targetBrightnessRange = h->targetBrightnessRange;
            params->thrld = h->thrld;
            params->targetBrightness = h->targetBrightness;
            params->exposureTimeStepSize = h->exposureTimeStepSize;

            retVal = IAE_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IAE_EUNSUPPORTED;
            break;
    }
    return (retVal);
}

extern IALG_Fxns AE_TI_IALG2;
#define IALGFXNS  \
    &AE_TI_IALG2,   /* module ID */                         \
NULL,               /* activate */                          \
AE_TI_alloc,        /* alloc */                             \
NULL,               /* control (NULL => no control ops) */  \
NULL,               /* deactivate */                        \
AE_TI_free,         /* free */                              \
AE_TI_init,         /* init */                              \
NULL,               /* moved */                             \
NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== AE_TI_IAE ========
 *  This structure defines TI's implementation of the IAE interface
 *  for the AE_TI module.
 */
IAE_Fxns AE_TI_AE2 = {           /* module_vendor_interface */
    {IALGFXNS},
    AE_TI_process,
    AE_TI_control,
};

/*
 *  ======== AE_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the AE_TI module.
 */
IALG_Fxns AE_TI_IALG2 = {        /* module_vendor_interface */
    IALGFXNS
};
