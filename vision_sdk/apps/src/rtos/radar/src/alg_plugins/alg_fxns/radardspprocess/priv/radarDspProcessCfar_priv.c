/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
 *******************************************************************************
 * \file radarDspProcessCfar_priv.c
 *
 * \brief  This file contains plug in functions for radar DSP based peak
 *         detection CFAR Processing.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <ti/alg/mmwavelib/mmwavelib.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/radarDspProcess_Priv.h>
#include <math.h>
#include <stdio.h>
#include "c6x.h"

/*******************************************************************************
 *  Global Variables
 *******************************************************************************
 */

/** \brief Log table */
double ti_math_logtable[8] = {
   0.0000000000,
  -0.1177830356,
  -0.2231435513,
  -0.3184537311,
  -0.4054651081,
  -0.4855078157,
  -0.5596157879,
  -0.6286086594
};

 /*******************************************************************************
 *  Algorithm Link Private Function Declaration
 *******************************************************************************
 */
static inline float log2sp_i(float a);
UInt32 AlgorithmFxn_RadarDspCfar_caall (AlgorithmFxn_RadarDspProcessObj *pObj);

/*******************************************************************************
 *  Algorithm Link Function Definition
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP CFAR Processing.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspCfarCreate(AlgorithmFxn_RadarDspProcessObj *pObj)
{
    Int32 retVal = SYSTEM_LINK_STATUS_SOK;

    /* incorrect CFAR-CASO window setting */
    if ((pObj->algLinkCreateParams.cfarCreateParams.cfarType ==
        ALG_FXN_RADAR_DSP_PROCESS_CFAR_CASO)
        && (pObj->algLinkCreateParams.cfarCreateParams.searchWinSizeDoppler == 0))
        retVal = SYSTEM_LINK_STATUS_EFAIL;

    UTILS_assert(retVal == SYSTEM_LINK_STATUS_SOK);
    pObj->cfarScratch  = (UInt32 *) Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
        pObj->maxRangeBins*(sizeof(float) + sizeof(Int16)) +
        100*sizeof(float),  1);

    UTILS_assert (pObj->cfarScratch != NULL);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Process function for the DSP CFAR Processing.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarDspCfarProcess(AlgorithmFxn_RadarDspProcessObj *pObj)
{
    /* Call CFAR process */
    pObj->opBufCFAR->numObjDetected = AlgorithmFxn_RadarDspCfar_caall(pObj);

    return SYSTEM_LINK_STATUS_SOK;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Delete function for the DSP CFAR Processing.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspCfarDelete(AlgorithmFxn_RadarDspProcessObj *pObj)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    /* Free Buffer for the CFAR Scratch Buffer */
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           pObj->cfarScratch,
                           pObj->maxRangeBins*(sizeof(float) + sizeof(Int16))
                           + 100 * sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}

/******************************************************************************
 *  Algorithm Specific Functions
******************************************************************************/

UInt32 AlgorithmFxn_RadarDspCfar_caall (AlgorithmFxn_RadarDspProcessObj *pObj)
{
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;
    AlgorithmFxn_RadarDspProcCfarCreateParams *pCfarCreateParams;
    AlgorithmFxn_RadarDspProcessCFAROut *cfarOut = pObj->opBufCFAR;
    float *opBufEnergySum = pObj->opBufEnergySum;
    UInt32 chId = pObj->currCh;
    UInt32 currProfile = pObj->currProfile;
    UInt32 numDopplerBins = pObj->chObj[chId].numDopplerBins[currProfile];
    UInt32 numRangeBins = pObj->chObj[chId].numRangeBins[currProfile];
    Int32  i, j, k, i_doppler;
    float  totalPower;
    float  threshold, dopplerScale;
    UInt32 detected, tempDetected;
    Int16  *tempRangeIndex;
    float  *tempNoise;

    pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    pCfarCreateParams = &pLinkCreateParams->cfarCreateParams;
    tempRangeIndex  = (Int16 *) pObj->cfarScratch;
    tempNoise       = (float *) &pObj->cfarScratch[numRangeBins/2];
    detected        = 0;

    if(pCfarCreateParams->log2MagFlag)
    {
        for (i = 0; i < numDopplerBins; i++)
        {
            for(j = 0; j < numRangeBins; j++)
            {
                opBufEnergySum[i * numRangeBins + j] =
                    0.5f*log2sp_i(1.f + opBufEnergySum[i * numRangeBins + j]);
            }
        }
    }
    dopplerScale = pCfarCreateParams->dopplerSearchRelThr *
                   0.5f/((float)pCfarCreateParams->searchWinSizeDoppler);

    for (i = 0; i < (Int32) numDopplerBins; i++)
    {
        /* search from low doppler to high doppler, both direction*/
        if (i & 1)
        {
            i_doppler = numDopplerBins - 1 - (i >> 1);
        }
        else
        {
            i_doppler = i >> 1;
        }
        tempDetected = mmwavelib_cfarfloat_caall(
                                   &opBufEnergySum[i * numRangeBins],
                                   numRangeBins,
                                   pCfarCreateParams->cfarType,
                                   pCfarCreateParams->guardSizeRange,
                                   pCfarCreateParams->searchWinSizeRange,
                                   pCfarCreateParams->leftSkipSize,
                                   pCfarCreateParams->rightSkipSize,
                                   pCfarCreateParams->K0,
                                   (UInt32 *)tempRangeIndex,
                                   (float *)tempNoise);
        if (pCfarCreateParams->enableSecondPassSearch)
        {
            Int32 leftrepeat, rightrepeat, localRangeInd;

            leftrepeat =
                (Int32)pCfarCreateParams->searchWinSizeDoppler - i_doppler;
            if (leftrepeat < 0)
                leftrepeat = 0;
            rightrepeat =
                (Int32)pCfarCreateParams->searchWinSizeDoppler -
                ((Int32)numDopplerBins - 1 - i_doppler);
            if (rightrepeat < 0)
                rightrepeat = 0;

            /* Left Edge */
            if (i_doppler <  (Int32)pCfarCreateParams->searchWinSizeDoppler)
            {
                for (j = 0; j < (Int32)tempDetected; j++)
                {
                    localRangeInd    =    tempRangeIndex[j];
                    totalPower        =    0.f;
                    for (k = (Int32)numDopplerBins - leftrepeat;
                         k < (Int32)numDopplerBins; k++)
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    for (k = 0;
                         k < ((Int32)pCfarCreateParams->searchWinSizeDoppler -
                                      leftrepeat); k++)
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }

                    for (k = i_doppler + 1;
                         k <= i_doppler + (Int32)pCfarCreateParams->searchWinSizeDoppler;
                         k++)
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    threshold    =    totalPower * dopplerScale;
                    if ((opBufEnergySum[i_doppler * numRangeBins +
                                        localRangeInd] > threshold) &&
                        (detected < pCfarCreateParams->maxNumDetObj))
                    {
                        cfarOut->noise[detected]           =    tempNoise[j];
                        cfarOut->rangeInd[detected]        =    localRangeInd;
                        cfarOut->dopplerInd[detected++]    =    i_doppler;
                    }
                }
            }
            /* right edge */
            else if (i_doppler >= (Int32)numDopplerBins -
                                  (Int32)pCfarCreateParams->searchWinSizeDoppler)
            {
                for (j = 0; j < (Int32)tempDetected; j++)
                {
                    localRangeInd    =    tempRangeIndex[j];
                    totalPower        =    0.f;
                    for (k = i_doppler -
                            (Int32)pCfarCreateParams->searchWinSizeDoppler;
                            k < i_doppler ; k++ )
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    for (k = 0; k < rightrepeat; k++ )
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    for (k = i_doppler + 1; k < (Int32)numDopplerBins ; k++ )
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    threshold    =    totalPower * dopplerScale;
                    if ((opBufEnergySum[i_doppler * numRangeBins + localRangeInd] >
                            threshold) &&
                            (detected < pCfarCreateParams->maxNumDetObj))
                    {
                        cfarOut->noise[detected]           =    tempNoise[j];
                        cfarOut->rangeInd[detected]        =    localRangeInd;
                        cfarOut->dopplerInd[detected++]    =    i_doppler;
                    }
                }
            }
            else  /* None Edge */
            {
                for (j = 0; j < (Int32)tempDetected; j++)
                {
                    localRangeInd    =    tempRangeIndex[j];
                    totalPower        =    0.f;
                    for (k = i_doppler -
                            (Int32)pCfarCreateParams->searchWinSizeDoppler;
                            k < i_doppler ; k++)
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    for (k = i_doppler + 1;
                         k <= i_doppler + (Int32)pCfarCreateParams->searchWinSizeDoppler;
                         k++ )
                    {
                        totalPower += opBufEnergySum[
                            k * numRangeBins + localRangeInd];
                    }
                    threshold    =    totalPower * dopplerScale;
                    if ((opBufEnergySum[i_doppler * numRangeBins + localRangeInd]
                        > threshold) &&
                        (detected < pCfarCreateParams->maxNumDetObj))
                    {
                        cfarOut->noise[detected]            =    tempNoise[j];
                        cfarOut->rangeInd[detected]        =    localRangeInd;
                        cfarOut->dopplerInd[detected++]    =    i_doppler;
                    }
                }
            }
        }
        else
        {
            if (tempDetected < pCfarCreateParams->maxNumDetObj)
            {
                for (j = 0; j < (Int32)tempDetected; j++)
                {
                    cfarOut->noise[detected]        = tempNoise[j];
                    cfarOut->rangeInd[detected]     = tempRangeIndex[j];
                    cfarOut->dopplerInd[detected++] = i_doppler;
                }
            }
            else
            {
                for (j = 0; j < pCfarCreateParams->maxNumDetObj; j++)
                {
                    cfarOut->noise[detected]        = tempNoise[j];
                    cfarOut->rangeInd[detected]     = tempRangeIndex[j];
                    cfarOut->dopplerInd[detected++] = i_doppler;
                }
                break;
            }
        }
    }
    /* Calculate range, speed, noise and SNR of the detected objects. */
    for (i = 0; i < (Int32) detected; i++ )
    {
        cfarOut->rangeEst[i] = (float)cfarOut->rangeInd[i] *
                                pLinkCreateParams->chCreateParams[chId].
                                rangeRes[currProfile];
        cfarOut->snrEst[i] = opBufEnergySum[cfarOut->dopplerInd[i] *
                             numRangeBins + cfarOut->rangeInd[i]]
                             /cfarOut->noise[i];
        /*this is an approximation since noise is not log2(sum(noise)) */
        if(pCfarCreateParams->log2MagFlag)
        {
            cfarOut->snrEst[i] = 6.f*(opBufEnergySum[cfarOut->dopplerInd[i]
                                      * numRangeBins + cfarOut->rangeInd[i]] -
                                      cfarOut->noise[i]);
        }
        if ((UInt32)cfarOut->dopplerInd[i] >= (numDopplerBins >> 1))
            k = (Int32)cfarOut->dopplerInd[i] - (Int32)numDopplerBins;
        else
            k = (Int32)cfarOut->dopplerInd[i];
        cfarOut->dopplerEst[i] = (float)k * pLinkCreateParams->
                                 chCreateParams[chId].dopplerRes[currProfile];
    }
    return detected;
}

static inline float log2sp_i(float a)
{
    double  ln2  =  0.693147180559945;
    double  base =  1.4426950408890;
    float   c1   = -0.2302894f;
    float   c2   =  0.1908169f;
    float   c3   = -0.2505905f;
    float   c4   =  0.3333164f;
    float   c5   = -0.5000002f;
    float   MAXe =  3.402823466E+38;
    float   pol, r1, r2, r3, r4, res;
    double  dr, frcpax, rcp, T;
    int     N, T_index;

    /* r = x * frcpa(x) -1 */
    rcp = _rcpdp((double) a);
    frcpax = _itod(_clr(_hi(rcp),0,16), 0);
    dr = frcpax * (double) a  - 1.0;

    /* Polynomial p(r) that approximates ln(1+r) - r */
    r1 = (float) dr;
    r2 = r1*r1;
    r3 = r1*r2;
    r4 = r2*r2;

    pol  = c5*r2 + ((c4*r3) + ((c2*r1 + c3) + c1*r2)*r4);
    pol *= (float) base;

    /* Reconstruction: result = T + r + p(r) */
    N       = _extu(_hi(frcpax),  1, 21) - 1023;
    T_index = _extu(_hi(frcpax), 12, 29);
    T       = (ti_math_logtable[T_index] - ln2 * (double) N) * base;
    res     = (dr * base  + T) + (pol);

    if (a <= 0.0f) {
        res = _itof(0xFF800000);
    }
    if (a > MAXe) {
        res = 1024.0;
    }

    return (res);
}
