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

#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include "data_vis_priv.h"

DataVis_Obj gDataVis_Obj = { 0 };

static inline UInt32 offsetFromTop(DataVis_DataBwPrm *pPrm, UInt32 percentage)
{
    return pPrm->winPosY + (pPrm->winHeight*percentage)/100;
}

static inline UInt32 offsetFromLeft(DataVis_DataBwPrm *pPrm, UInt32 percentage)
{
    return pPrm->winPosX + (pPrm->winWidth*percentage)/100;
}

static inline UInt32 offsetFromRight(DataVis_DataBwPrm *pPrm, UInt32 percentage)
{
    return pPrm->winPosX + pPrm->winWidth - (pPrm->winWidth*percentage)/100;
}

static inline UInt32 offsetFromBottom(DataVis_DataBwPrm *pPrm, UInt32 percentage)
{
    return pPrm->winPosY + pPrm->winHeight - (pPrm->winHeight*percentage)/100;
}

Void DataVis_getSampleDuration(Bool *pIsUpdate, UInt32 *pSampleDuration)
{
    *pIsUpdate = FALSE;

    if(gDataVis_Obj.isSetPrmDone == TRUE)
    {
        DataVis_lock();

        if(gDataVis_Obj.resetDataCollector)
        {
            gDataVis_Obj.resetDataCollector = FALSE;
            *pSampleDuration = gDataVis_Obj.userSetPrm.sampleDuration;
            *pIsUpdate = TRUE;
        }

        DataVis_unlock();
    }
}

Void DataVis_getLogForVis(void)
{
    Int32 uc_idx = 0;
    Int32 num_counters = 0;
    UInt32 cfg_idx;
    DataVis_DataBwElement bwElem;

    bwElem.timestamp = Utils_getCurGlobalTimeInUsec();

    for(cfg_idx=0U; cfg_idx<MAX_SDRAM_CFGS; cfg_idx++)
    {
        Utils_StatCollSdramCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.sdramCfg[cfg_idx];

        for(uc_idx = 0; uc_idx < pCfg->num_uc; uc_idx++)
        {
            num_counters = pCfg->data[uc_idx].numCounters;

            switch(num_counters)
            {
                /*
                * MISRA.PTR.ARITH
                * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
                * Pointer is used in arithmetic or array index expression
                * KW State: Defer -> Waiver -> Case by case
                */
                case 1  :
                    bwElem.dataBw[pCfg->cfg[uc_idx].idx] =
                                                (UInt32)pCfg->data[uc_idx].avg[0];
                    break;

                case 2  :
                    ; /* TODO Not Implemented */
                    break;
                default:
                    break;
            }
        }
    }
    for(cfg_idx=0U; cfg_idx<MAX_MSTR_CFGS; cfg_idx++)
    {
        Utils_StatCollMstrCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.mstrCfg[cfg_idx];

        for(uc_idx = 0; uc_idx < pCfg->num_uc; uc_idx++)
        {
            num_counters = pCfg->data[uc_idx].numCounters;

            switch(num_counters)
            {
                case 1  :
                    if(pCfg->cfg[uc_idx].cfg.usecase==SCI_MSTR_THROUGHPUT)
                    {
                        bwElem.dataBw[pCfg->cfg[uc_idx].idx] =
                                                (UInt32)pCfg->data[uc_idx].avg[0];
                    }
                    else
                    {
                        ; /* TODO Not Implemented */

                    }
                    break;

                case 2  :
                    if(pCfg->cfg[uc_idx].cfg.usecase==SCI_MSTR_THROUGHPUT)
                    {
                        bwElem.dataBw[pCfg->cfg[uc_idx].idx] =
                                                (UInt32)pCfg->data[uc_idx].avg[0];
                        /* TODO for second counter */

                    }
                    else
                    {
                        ; /* TODO Not Implemented */
                    }
                    break;
                default:
                    break;

            }
        }
    }

    DataVis_writeDataBwData(&bwElem);
}

Void DataVis_CreatePrm_Init(DataVis_CreatePrm *pCreatePrm)
{
    memset(pCreatePrm, 0, sizeof(DataVis_CreatePrm));

    pCreatePrm->maxWinWidth  = 640;
    pCreatePrm->maxWinHeight = 360;
    pCreatePrm->maxNumberOfSamples = 1000;
}

Void DataVis_DataBwPrm_Init(DataVis_DataBwPrm *pPrm)
{
    UInt16 idx, group_idx;

    memset(pPrm, 0, sizeof(DataVis_DataBwPrm));

    /* set default param's */
    pPrm->sampleDuration = 500;
    pPrm->numOfSamples = 120;
    pPrm->drawRefreshRate = 5000;
    pPrm->yScaleMin = 0.0;
    pPrm->yScaleMax = 2.0;
    pPrm->yScaleMajorInc = 0.2;
    pPrm->yScaleMinorInc = 0.2;
    pPrm->xScaleMin = 0.0;
    pPrm->xScaleMax = 60;
    pPrm->xScaleMajorInc = 15;
    pPrm->xScaleMinorInc =  5;
    strcpy(pPrm->xScaleText, "sec");
    strcpy(pPrm->yScaleText, "GB/s");

    idx = 0;
    group_idx = 0;
    #ifdef TDA3XX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR;
    group_idx++;
    #endif
    #ifdef TDA2EX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR;
    group_idx++;
    #endif
    #if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EMIF2_RD_WR;
    group_idx++;
    #endif
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "EMIF");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(0, 0, 240);
    idx++;

    group_idx=0;
    #ifdef TDA3XX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_ISS_RT;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT2;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT1;
    group_idx++;
    #endif
    #ifdef TDA2EX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2;
    group_idx++;
    #endif
    #ifdef TDA2XX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP2_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP2_P2;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP3_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP3_P2;
    group_idx++;
    #endif
    #ifdef TDA2PX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP2_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VIP2_P2;
    group_idx++;
    #endif
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "CAPTURE");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(0, 240, 0);
    idx++;

    group_idx=0;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSS;
    group_idx++;
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "DISPLAY");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(240, 0, 0);
    idx++;

    group_idx=0;
    #ifdef TDA3XX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP2_MDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP2_EDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA;
    group_idx++;
    #endif
    #ifdef TDA2EX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA;
    group_idx++;
    #endif
    #if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP2_MDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP2_EDMA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA;
    group_idx++;
    #endif
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "DSP");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(240, 240, 0);
    idx++;

    group_idx=0;
    #ifdef TDA3XX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE1_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE1_P2;
    group_idx++;
    #endif
    #ifdef TDA2EX_BUILD
    #endif
    #ifdef TDA2XX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC0;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC0;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE3_TC0;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE3_TC1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE4_TC0;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE4_TC1;
    group_idx++;
    #endif
    #ifdef TDA2PX_BUILD
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC0;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC0;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC1;
    group_idx++;
    #endif
    #ifndef TDA2EX_BUILD
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "EVE");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(240, 240, 240);
    idx++;
    #endif

#ifndef TDA3XX_BUILD
    group_idx = 0;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_IVA;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VPE_P1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_VPE_P2;
    group_idx++;
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "HWA");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(0, 240, 240);
    idx++;
#endif

    group_idx=0;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_IPU1;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_RD;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_WR;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_RD;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_WR;
    group_idx++;
    pPrm->dataBwModProp[idx].moduleId[group_idx] = UTILS_STATCOLL_DATA_BW_MOD_GMAC_SW;
    group_idx++;
    pPrm->dataBwModProp[idx].numModules = group_idx;
    strcpy(pPrm->dataBwModProp[idx].dataBwModText, "OTHER");
    pPrm->dataBwModProp[idx].color = RGB888_TO_RGB565(240, 240, 240);
    idx++;

    pPrm->numDataBwMod = idx;

    pPrm->winWidth = 640;
    pPrm->winHeight = 360;
    pPrm->winPosX = 10;
    pPrm->winPosY = 10;

    pPrm->pDraw2DHandle = NULL;
}

Int32 DataVis_create(DataVis_CreatePrm *pCreatePrm)
{
    gDataVis_Obj.createPrm = *pCreatePrm;

    gDataVis_Obj.lock = BspOsal_semCreate((Int32)0, (Bool)TRUE);
    UTILS_assert(gDataVis_Obj.lock != NULL);

    DataVis_unlock();

    gDataVis_Obj.pDrawDataBwElements =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            sizeof(DataVis_DataBwElement)*pCreatePrm->maxNumberOfSamples, 32);
    UTILS_assert(gDataVis_Obj.pDrawDataBwElements != NULL);

    DataVis_queueDataBwCreate();

    /* Register call back functions called from Utils stat collector */
    Utils_statCollectorRegistergetSampleDurationCb(DataVis_getSampleDuration);
    Utils_statCollectorRegistergetLogForVisCb(DataVis_getLogForVis);

    return 0;
}

Int32 DataVis_delete()
{
    DataVis_CreatePrm *pCreatePrm;

    pCreatePrm = &gDataVis_Obj.createPrm;

    DataVis_queueDataBwDelete();

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
        gDataVis_Obj.pDrawDataBwElements,
        sizeof(DataVis_DataBwElement)*pCreatePrm->maxNumberOfSamples
        );

    BspOsal_semDelete(&gDataVis_Obj.lock);

    return 0;
}



Int32 DataVis_setDataBwPrm(DataVis_DataBwPrm *pPrm, Bool resetDataCollector, Bool resetDraw)
{
    DataVis_lock();

    gDataVis_Obj.userSetPrm = *pPrm;
    gDataVis_Obj.resetDataCollector = resetDataCollector;
    gDataVis_Obj.resetDraw = resetDraw;

    gDataVis_Obj.isSetPrmDone = TRUE;

    DataVis_unlock();

    return 0;
}

Bool DataVis_isPrmUpdatedForDataBwDraw(DataVis_DataBwPrm *pPrm)
{
    Bool isUpdate = FALSE;

    if(gDataVis_Obj.isSetPrmDone == FALSE)
        return FALSE;

    DataVis_lock();

    if(gDataVis_Obj.resetDraw)
    {
        gDataVis_Obj.resetDraw = FALSE;
        *pPrm = gDataVis_Obj.userSetPrm;
        isUpdate = TRUE;
    }

    DataVis_unlock();

    return isUpdate;
}

Bool DataVis_isPrmUpdatedForDataBWCollector(DataVis_DataBwPrm *pPrm)
{
    Bool isUpdate = FALSE;

    if(gDataVis_Obj.isSetPrmDone == FALSE)
        return FALSE;

    DataVis_lock();

    if(gDataVis_Obj.resetDataCollector)
    {
        gDataVis_Obj.resetDataCollector = FALSE;
        *pPrm = gDataVis_Obj.userSetPrm;
        isUpdate = TRUE;
    }

    DataVis_unlock();

    return isUpdate;
}

Void DataVis_drawDataBwScaleH()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;
    UInt32 startX, textStartY, endX, i, length, numMajor;
    float value;
    float curX, majorInc;
    char tmpStr[16];
    Draw2D_LinePrm linePrm;
    Draw2D_FontPrm fontPrm;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    textStartY = offsetFromBottom(pPrm, 8);
    startX = offsetFromLeft(pPrm, 8);
    endX = offsetFromRight(pPrm, 15);

    length   = endX - startX;
    numMajor = ((pPrm->xScaleMax - pPrm->xScaleMin)/pPrm->xScaleMajorInc);
    majorInc = length / numMajor;

    /* draw Horizontal scale line */

    linePrm.lineColor = RGB888_TO_RGB565(255, 255, 255);
    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineSize = 3;

    Draw2D_drawLine(pDraw2D,
        startX,
        offsetFromBottom(pPrm, 10),
        endX,
        offsetFromBottom(pPrm, 10),
        &linePrm
       );

    /* draw H scale - text */
    fontPrm.fontIdx = 3;

    Draw2D_drawString(pDraw2D,
        endX,
        offsetFromBottom(pPrm, 15),
        pPrm->xScaleText,
        &fontPrm
        );

    value = pPrm->xScaleMin;

    /* draw major text */
    for(i=0; i<=numMajor; i++)
    {
        sprintf(tmpStr, "%3.1f", value);
        fontPrm.fontIdx = 3;

        curX = startX + i*majorInc;

        Draw2D_drawString(pDraw2D,
            curX,
            textStartY,
            tmpStr,
            &fontPrm
            );

        value += pPrm->xScaleMajorInc;
    }
}

Void DataVis_drawDataBwScaleV()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;
    UInt32 startY, textStartX, endY, i, length, numMajor;
    float value;
    float curY, majorInc;
    char tmpStr[16];

    Draw2D_LinePrm linePrm;
    Draw2D_FontPrm fontPrm;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    textStartX = offsetFromLeft(pPrm, 2);
    startY = offsetFromBottom(pPrm, 10);
    endY = offsetFromTop(pPrm, 10);

    length   = startY - endY;
    numMajor = ((pPrm->yScaleMax - pPrm->yScaleMin)/pPrm->yScaleMajorInc);
    majorInc = length / numMajor;

    /* draw Vertical scale line */

    linePrm.lineColor = RGB888_TO_RGB565(255, 255, 255);
    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineSize = 3;

    Draw2D_drawLine(pDraw2D,
        offsetFromLeft(pPrm, 8) - linePrm.lineSize,
        startY,
        offsetFromLeft(pPrm, 8) - linePrm.lineSize,
        endY,
        &linePrm
       );

    /* draw V scale - text */
    fontPrm.fontIdx = 3;

    Draw2D_drawString(pDraw2D,
        textStartX,
        offsetFromTop(pPrm, 2),
        pPrm->yScaleText,
        &fontPrm
        );

    value = pPrm->yScaleMin;

    /* draw major text */
    for(i=0; i<=numMajor; i++)
    {
        sprintf(tmpStr, "%3.1f", value);
        fontPrm.fontIdx = 3;

        curY = startY - i*majorInc;

        Draw2D_drawString(pDraw2D,
            textStartX,
            curY,
            tmpStr,
            &fontPrm
            );

        value += pPrm->yScaleMajorInc;
    }
}

Void DataVis_drawDataBwScaleLinesV()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;
    float curY, minorInc, majorInc;
    UInt32 lineStartX, lineEndX, startY, endY, length, numMinor, i, numMajor;

    Draw2D_LinePrm linePrm;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    startY = offsetFromBottom(pPrm, 10);
    endY = offsetFromTop(pPrm, 10);

    length   = startY - endY;

    numMinor = ((pPrm->yScaleMax - pPrm->yScaleMin)/pPrm->yScaleMinorInc);
    minorInc = (float)length / numMinor;

    numMajor = ((pPrm->yScaleMax - pPrm->yScaleMin)/pPrm->yScaleMajorInc);
    majorInc = (float)length / numMajor;

    lineStartX = offsetFromLeft(pPrm, 8);
    lineEndX = offsetFromRight(pPrm, 15);

    for(i=1; i<=numMinor; i++)
    {
        curY = ((float)startY - (float)i*minorInc);

        linePrm.lineColor = RGB888_TO_RGB565(64, 64, 64);
        linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
        linePrm.lineSize = 1;

        Draw2D_drawLine(pDraw2D,
            lineStartX,
            curY,
            lineEndX,
            curY,
            &linePrm
           );
    }

    for(i=1; i<=numMajor; i++)
    {
        curY = ((float)startY - (float)i*majorInc);

        linePrm.lineColor = RGB888_TO_RGB565(128, 128, 128);
        linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
        linePrm.lineSize = 1;

        Draw2D_drawLine(pDraw2D,
            lineStartX,
            curY,
            lineEndX,
            curY,
            &linePrm
           );
    }

}

Void DataVis_drawDataBwScaleLinesH()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;
    float curX, minorInc, majorInc;
    UInt32 lineStartY, lineEndY, startX, endX, length, numMinor, i, numMajor;

    Draw2D_LinePrm linePrm;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    startX = offsetFromLeft(pPrm, 8);
    endX = offsetFromRight(pPrm, 15);

    length   = endX - startX;

    numMinor = ((pPrm->xScaleMax - pPrm->xScaleMin)/pPrm->xScaleMinorInc);
    minorInc = (float)length / numMinor;

    numMajor = ((pPrm->xScaleMax - pPrm->xScaleMin)/pPrm->xScaleMajorInc);
    majorInc = (float)length / numMajor;

    lineStartY = offsetFromBottom(pPrm, 10);
    lineEndY = offsetFromTop(pPrm, 10);

    for(i=1; i<=numMinor; i++)
    {
        curX = ((float)startX + (float)i*minorInc);

        linePrm.lineColor = RGB888_TO_RGB565(32, 32, 32);
        linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
        linePrm.lineSize = 1;

        Draw2D_drawLine(pDraw2D,
            curX,
            lineStartY,
            curX,
            lineEndY,
            &linePrm
           );
    }

    for(i=1; i<=numMajor; i++)
    {
        curX = ((float)startX + (float)i*majorInc);

        linePrm.lineColor = RGB888_TO_RGB565(128, 128, 128);
        linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
        linePrm.lineSize = 1;

        Draw2D_drawLine(pDraw2D,
            curX,
            lineStartY,
            curX,
            lineEndY,
            &linePrm
           );
    }

}

static Void DataVis_drawDataBwLegend()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;
    UInt32 startX, startY, i;
    Draw2D_RegionPrm regPrm;
    Draw2D_FontPrm fontPrm;
    Draw2D_FontProperty fontProp;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    fontPrm.fontIdx = 3;

    Draw2D_getFontProperty(&fontPrm, &fontProp);

    startX = offsetFromRight(pPrm, 14);
    startY = offsetFromTop(pPrm, 10);

    for(i=0; i<pPrm->numDataBwMod; i++)
    {
        regPrm.startX = startX;
        regPrm.startY = startY;
        regPrm.height = fontProp.height;
        regPrm.width  = regPrm.height;
        regPrm.color  = pPrm->dataBwModProp[i].color;
        regPrm.colorFormat = SYSTEM_DF_BGR16_565;
        Draw2D_fillRegion(pDraw2D, &regPrm);

        Draw2D_drawString(pDraw2D,
            startX + regPrm.width + (pPrm->winWidth*1/100),
            startY,
            pPrm->dataBwModProp[i].dataBwModText,
            &fontPrm
        );

        startY += regPrm.height + (pPrm->winHeight*2/100);
    }
}

static Void DataVis_clearDataBwWin()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;

    Draw2D_RegionPrm regPrm;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    regPrm.startX = pPrm->winPosX;
    regPrm.startY = pPrm->winPosY;
    regPrm.height = pPrm->winHeight;
    regPrm.width  = pPrm->winWidth;
    regPrm.color  = RGB888_TO_RGB565(30, 30, 30);
    regPrm.colorFormat = SYSTEM_DF_BGR16_565;

    Draw2D_fillRegion(pDraw2D, &regPrm);
}

static Void DataVis_clearDataBwPlotArea()
{
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwPrm *pPrm;

    Draw2D_RegionPrm regPrm;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    regPrm.startX = offsetFromLeft(pPrm, 8);
    regPrm.startY = offsetFromTop(pPrm, 10);
    regPrm.height = offsetFromBottom(pPrm, 10) - regPrm.startY + 3;
    regPrm.width  = offsetFromRight(pPrm, 15) - regPrm.startX;
    regPrm.color  = RGB888_TO_RGB565(30, 30, 30);
    regPrm.colorFormat = SYSTEM_DF_BGR16_565;

    Draw2D_fillRegion(pDraw2D, &regPrm);
}

static Void DataVis_drawDataBwReadSamples()
{
    DataVis_DataBwPrm *pPrm;
    UInt32 elemWr, numWr;

    pPrm = &gDataVis_Obj.drawPrm;

    numWr = 0;
    elemWr = pPrm->numOfSamples-gDataVis_Obj.curDrawWrIdx;
    DataVis_readDataBwData(
        &gDataVis_Obj.pDrawDataBwElements[gDataVis_Obj.curDrawWrIdx],
        &numWr,
        elemWr
        );

    gDataVis_Obj.curDrawWrIdx = (gDataVis_Obj.curDrawWrIdx+numWr)%pPrm->numOfSamples;
    gDataVis_Obj.curDrawNumElements += numWr;
    if(gDataVis_Obj.curDrawNumElements>pPrm->numOfSamples)
        gDataVis_Obj.curDrawNumElements = pPrm->numOfSamples;

    /* there may be more samples */
    numWr = 0;
    elemWr = gDataVis_Obj.curDrawWrIdx;
    DataVis_readDataBwData(
        &gDataVis_Obj.pDrawDataBwElements[gDataVis_Obj.curDrawWrIdx],
        &numWr,
        elemWr
        );

    gDataVis_Obj.curDrawWrIdx = (gDataVis_Obj.curDrawWrIdx+numWr)%pPrm->numOfSamples;
    gDataVis_Obj.curDrawNumElements += numWr;
    if(gDataVis_Obj.curDrawNumElements>pPrm->numOfSamples)
        gDataVis_Obj.curDrawNumElements = pPrm->numOfSamples;
}

static UInt32 DataVis_drawDataBwConvertValueToScaleY(UInt32 value)
{
    DataVis_DataBwPrm *pPrm;
    float valueF;
    UInt32 startY, endY, length;

    pPrm = &gDataVis_Obj.drawPrm;

    startY = offsetFromBottom(pPrm, 10);
    endY = offsetFromTop(pPrm, 10);

    length   = startY - endY;

    /* convert to GB/s */
    valueF = value/1000000000.0;

    if(valueF < pPrm->yScaleMin)
        valueF = pPrm->yScaleMin;
    if(valueF > pPrm->yScaleMax)
        valueF = pPrm->yScaleMax;

    /* scale it */
    return startY - (UInt32)( (valueF*length)/(pPrm->yScaleMax-pPrm->yScaleMin));
}

static UInt32 DataVis_drawDataBwConvertValueToScaleX(UInt32 value)
{
    DataVis_DataBwPrm *pPrm;
    UInt32 startX, endX, length;

    pPrm = &gDataVis_Obj.drawPrm;

    startX = offsetFromLeft(pPrm, 8);
    endX = offsetFromRight(pPrm, 15);

    length   = endX - startX;

    /* scale it */
    return startX + (UInt32)(((float)value*length)/pPrm->numOfSamples);
}


static Void DataVis_drawDataBwDrawSamples()
{
    DataVis_DataBwPrm *pPrm;
    DataVis_DataBwModDrawProp *pProp;
    Draw2D_Handle *pDraw2D;
    DataVis_DataBwElement *pElem;
    Draw2D_LinePrm linePrm;
    UInt32 i, j, k, startIdx;
    UInt32 value;

    pPrm = &gDataVis_Obj.drawPrm;
    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    if(gDataVis_Obj.curDrawNumElements<pPrm->numOfSamples)
    {
        startIdx = 0;
    }
    else
    {
        startIdx = (gDataVis_Obj.curDrawWrIdx+1)%pPrm->numOfSamples;
    }

    linePrm.lineColorFormat = SYSTEM_DF_BGR16_565;
    linePrm.lineSize = 3;

    for(j=0; j<pPrm->numDataBwMod; j++)
    {
        gDataVis_Obj.x_prev[j] = 0xFFFF;
        gDataVis_Obj.y_prev[j] = 0xFFFF;
    }

    for(i=0; i<gDataVis_Obj.curDrawNumElements-1; i++)
    {
        pElem = &gDataVis_Obj.pDrawDataBwElements[startIdx];

        for(j=0; j<pPrm->numDataBwMod; j++)
        {
            pProp = &pPrm->dataBwModProp[j];

            value = 0;
            for(k=0; k<pProp->numModules; k++)
            {
                value += pElem->dataBw[pProp->moduleId[k]];
            }

            gDataVis_Obj.y_cur[j] = DataVis_drawDataBwConvertValueToScaleY(value);
            gDataVis_Obj.x_cur[j] = DataVis_drawDataBwConvertValueToScaleX(i);

            linePrm.lineColor = pProp->color;

            if(gDataVis_Obj.x_prev[j]!=0xFFFF && gDataVis_Obj.y_prev[j]!=0xFFFF)
            {
                Draw2D_drawLine(
                    pDraw2D,
                    gDataVis_Obj.x_prev[j],
                    gDataVis_Obj.y_prev[j],
                    gDataVis_Obj.x_cur[j],
                    gDataVis_Obj.y_cur[j],
                    &linePrm
                    );
            }
            gDataVis_Obj.x_prev[j] = gDataVis_Obj.x_cur[j];
            gDataVis_Obj.y_prev[j] = gDataVis_Obj.y_cur[j];
        }

        startIdx = (startIdx+1)%pPrm->numOfSamples;
    }
}


Int32 DataVis_drawDataBw()
{
    DataVis_DataBwPrm *pPrm;
    Draw2D_Handle *pDraw2D;
    UInt64 elaspedTime;

    if(gDataVis_Obj.isSetPrmDone==FALSE)
    {
        return 0;
    }

    pPrm = &gDataVis_Obj.drawPrm;

    if(DataVis_isPrmUpdatedForDataBwDraw(pPrm)==TRUE)
    {
        gDataVis_Obj.curDrawWrIdx = 0;
        gDataVis_Obj.curDrawNumElements = 0;

        DataVis_clearDataBwWin();
        DataVis_drawDataBwScaleH();
        DataVis_drawDataBwScaleV();
        DataVis_drawDataBwLegend();


        gDataVis_Obj.startTimeInMsec = Utils_getCurGlobalTimeInMsec();
    }

    pDraw2D = pPrm->pDraw2DHandle;
    UTILS_assert(pDraw2D!=NULL);

    elaspedTime = Utils_getCurGlobalTimeInMsec() - gDataVis_Obj.startTimeInMsec;

    if(elaspedTime >= pPrm->drawRefreshRate)
    {
        DataVis_drawDataBwReadSamples();
        DataVis_clearDataBwPlotArea();
        /*
        DataVis_drawDataBwScaleLinesV();
        DataVis_drawDataBwScaleLinesH();
         */
        DataVis_drawDataBwDrawSamples();

        gDataVis_Obj.startTimeInMsec = Utils_getCurGlobalTimeInMsec();
    }

    return 0;
}

Void DataVis_lock()
{
    UTILS_assert(gDataVis_Obj.lock != NULL);
    BspOsal_semWait(gDataVis_Obj.lock, BSP_OSAL_WAIT_FOREVER);
}

Void DataVis_unlock()
{
    UTILS_assert(gDataVis_Obj.lock != NULL);
    BspOsal_semPost(gDataVis_Obj.lock);
}
