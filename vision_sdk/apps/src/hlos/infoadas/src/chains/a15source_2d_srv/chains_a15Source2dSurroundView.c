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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_a15Source2dSurroundView_priv.h"
#include <src/hlos/common/chains_common.h>
#include <vivi_srv.h>
#include "../../ti-plugins/include/srv_chain.h"
#include "osa_file.h"
#include <osa_mem.h>
#include <src/hlos/system/system_priv_ipc.h>

#ifndef QNX_BUILD
#ifdef ANDROID
#define SYNTH_ALG_2D_SRV_LUT_FILENAME "/data/infoadas/synthtable.bin"
#else
#define SYNTH_ALG_2D_SRV_LUT_FILENAME "/home/root/synthtable.bin"
#endif
#else
#define SYNTH_ALG_2D_SRV_LUT_FILENAME "/tmp/synthtable.bin"
#endif

/**
 *******************************************************************************
 *
 *  \brief  Use-case object
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/

typedef struct {
    chains_a15Source2dSurroundViewObj ucObj;

    struct vivi_source source;
    struct vivi_sink sink;
    struct vivi_source_config source_config[A15SOURCE_SRV_2D_880x1080_NUM_EP_SOURCE];

    UInt32 svInWidth;
    UInt32 svInHeight;
    UInt32 svOutWidth;
    UInt32 svOutHeight;
    UInt32 svCarImageWidth;
    UInt32 svCarImageHeight;
    UInt32 svNumViews;
    UInt32 svOutputMode;
    UInt32 enableCarOverlayInAlg;
    UInt32 synthLUTSize;
    UInt8 *synthLUTPtr;
    /**< Set to 1, if DSP need to create the car image, apply only for 2D SRV */
} Chains_A15Source2dSurroundViewAppObj;

Chains_A15Source2dSurroundViewAppObj gA15Source2dSurroundViewAppObj;

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_a15Source2dSurroundView_SetAppPrms(
            chains_a15Source2dSurroundViewObj *pUcObj, Void *appObj)
{
    EpLink_CreateParams  *pEpLinkParams;
    Chains_A15Source2dSurroundViewAppObj *pObj;
#ifndef EARLY_SRV_ENABLE
    UInt32 tmpReadSize=0;
    UInt8 *virt_addr;
    int osa_ret=OSA_SOK;
#endif
    pObj   = (Chains_A15Source2dSurroundViewAppObj*)appObj;


    ChainsCommon_SurroundView_SetSynthParams(&pUcObj->Alg_SynthesisPrm,
                                              pObj->svInWidth, pObj->svInHeight,
                                              pObj->svOutWidth, pObj->svOutHeight,
                                              pObj->svNumViews,
                                              pObj->svCarImageWidth,
                                              pObj->svCarImageHeight,
                                              pObj->svOutputMode,
                                              pObj->enableCarOverlayInAlg);
    UTILS_assert(pUcObj->Alg_SynthesisPrm.synthLUTPtr != NULL);
    pObj->synthLUTPtr = pUcObj->Alg_SynthesisPrm.synthLUTPtr;
    pObj->synthLUTSize = pUcObj->Alg_SynthesisPrm.synthLUTSize;

#ifndef EARLY_SRV_ENABLE
    virt_addr = (UInt8 *)OSA_memPhys2Virt((unsigned int)pObj->synthLUTPtr,
                      OSA_MEM_REGION_TYPE_AUTO);
    osa_ret = OSA_fileReadFile(SYNTH_ALG_2D_SRV_LUT_FILENAME,
                   virt_addr,
                   pObj->synthLUTSize,&tmpReadSize);
    pUcObj->Alg_SynthesisPrm.useSuppliedLUT = 0;
    pUcObj->Alg_SynthesisPrm.saveCalculatedLUT = 1;
    if (OSA_SOK == osa_ret) {
        if(tmpReadSize == pObj->synthLUTSize) {
            OSA_memCacheWb((unsigned int)virt_addr,
                ((unsigned int)virt_addr)+pObj->synthLUTSize);
            OSA_memCacheInv((unsigned int)virt_addr, pObj->synthLUTSize);

            pUcObj->Alg_SynthesisPrm.useSuppliedLUT = 1;
            pUcObj->Alg_SynthesisPrm.saveCalculatedLUT = 0;
        }
    } else {
        OSA_memCacheInv((unsigned int)virt_addr, pObj->synthLUTSize);
    }
#endif
    ChainsCommon_SurroundView_SetGAlignParams(&pUcObj->Alg_GeoAlignPrm,
                                              pObj->svInWidth, pObj->svInHeight,
                                              pObj->svOutWidth, pObj->svOutHeight,
                                              pObj->svNumViews,
                                              pObj->svCarImageWidth,
                                              pObj->svCarImageHeight,
                                              pObj->svOutputMode);

    ChainsCommon_SurroundView_SetPAlignParams(&pUcObj->Alg_PhotoAlignPrm,
                                              pObj->svInWidth, pObj->svInHeight,
                                              pObj->svOutWidth, pObj->svOutHeight,
                                              pObj->svNumViews,
                                              pObj->svCarImageWidth,
                                              pObj->svCarImageHeight,
                                              pObj->svOutputMode);

    /* We have three epLinks (1 src + 2 sink) in the chain; we will configure them now */
    /* sink2 configuration*/
    pEpLinkParams = &pUcObj->EpSink_2Prm;
    pEpLinkParams->epType = EP_SINK;
    pEpLinkParams->chainId = A15SOURCE_SRV_2D_880x1080;
    strcpy(pEpLinkParams->plugName, SRV_PLUGIN_NAME);

    /* sink1 configuration*/
    pEpLinkParams = &pUcObj->EpSink_1Prm;
    pEpLinkParams->epType = EP_SINK;
    pEpLinkParams->chainId = A15SOURCE_SRV_2D_880x1080;
    strcpy(pEpLinkParams->plugName, SRV_PLUGIN_NAME);

    /* source configuration */
    pEpLinkParams = &pUcObj->EpSourcePrm;
    pEpLinkParams->epType = EP_SOURCE;
    pEpLinkParams->chainId = A15SOURCE_SRV_2D_880x1080;
    strcpy(pEpLinkParams->plugName, SRV_PLUGIN_NAME);

    /* copy the source config data to the epSource link's config structure */
    if (pObj->source_config[0].eplink_id == pObj->source.eplink_id[0]) {
        memcpy(&pEpLinkParams->srcConfig.queInfo, &pObj->source_config[0].config,
            sizeof(System_LinkQueInfo));
    }

}
Void chains_a15Source2dSurroundView_saveLUT()
{
    Chains_A15Source2dSurroundViewAppObj *pObj;
    chains_a15Source2dSurroundViewObj *pUcObj;
    UInt8 *virt_addr = NULL;

    pObj = (Chains_A15Source2dSurroundViewAppObj*)&gA15Source2dSurroundViewAppObj;
    pUcObj = &pObj->ucObj;

    UTILS_assert(pObj->synthLUTPtr != NULL);
    virt_addr = (UInt8 *)OSA_memPhys2Virt((unsigned int)pObj->synthLUTPtr,
                          OSA_MEM_REGION_TYPE_AUTO);
    OSA_printf("Virtual address for LUT is 0x%08x\n",(unsigned int)virt_addr);
    if(pUcObj->Alg_SynthesisPrm.saveCalculatedLUT==1) {
        OSA_fileWriteFile(SYNTH_ALG_2D_SRV_LUT_FILENAME,
                  virt_addr,
                  pObj->synthLUTSize);
    }
}
#define SV2D_CARBOX_WIDTH 190
#define SV2D_CARBOX_HEIGHT 360

Void  chains_a15Source2dSurroundView_InitApp(struct vivi_sink *sink,
    struct vivi_source *source)
{
    Bool startWithCalibration;
    Chains_A15Source2dSurroundViewAppObj *pObj
        = (Chains_A15Source2dSurroundViewAppObj*)&gA15Source2dSurroundViewAppObj;

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_InitApp !!!\n");

    /* SRV Algo related initialization */
    pObj->svInWidth = SV_INPUT_WIDTH;
    pObj->svInHeight = SV_INPUT_HEIGHT;
    pObj->svOutWidth = 880;
    pObj->svOutHeight = 1080;
    pObj->svCarImageWidth = SV2D_CARBOX_WIDTH;
    pObj->svCarImageHeight = SV2D_CARBOX_HEIGHT;
    pObj->svNumViews = SV_NUM_VIEWS;
    pObj->svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_2D;
    pObj->enableCarOverlayInAlg = 1;

    /* Set startWithCalibration = TRUE to start the demo with calibration.
       Else it will use the previously calibrated LUTs */
    startWithCalibration = TRUE;
    ChainsCommon_SurroundView_CalibInit(
                                startWithCalibration,
                                pObj->svOutputMode);

    /* Set the link ids */
    chains_a15Source2dSurroundView_SetLinkId(&pObj->ucObj);

    /* Let's read the epLink ids to the back to caller */
    sink->eplink_id[0] = pObj->ucObj.EpSink_2LinkID;
    sink->eplink_id[1] = pObj->ucObj.EpSink_1LinkID;
    source->eplink_id[0] = pObj->ucObj.EpSourceLinkID;
    /* saving into the chain instance for future */
    pObj->sink.eplink_id[0] = sink->eplink_id[0];
    pObj->sink.eplink_id[1] = sink->eplink_id[1];
    pObj->source.eplink_id[0] = source->eplink_id[0];

    ChainsCommon_statCollectorReset();

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_InitApp DONE !!!\n");
}

Int32 chains_a15Source2dSurroundView_CreateSrcEpApp(struct vivi_sink *sink,
    struct vivi_source *source, struct vivi_source_config *sourceCfg[])
{
    Int32 status, i, dataFmt[4], scanFmt[4], bufType[4];
    Chains_A15Source2dSurroundViewAppObj *pObj
        = (Chains_A15Source2dSurroundViewAppObj*)&gA15Source2dSurroundViewAppObj;

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_CreateSrcEpApp !!!\n");

    for (i=0; i<sourceCfg[0]->config.numCh; i++) {
        dataFmt[i] = System_Link_Ch_Info_Get_Flag_Data_Format(sourceCfg[0]->config.chInfo[i].flags);
        scanFmt[i] = System_Link_Ch_Info_Get_Flag_Scan_Format(sourceCfg[0]->config.chInfo[i].flags);
        bufType[i] = System_Link_Ch_Info_Get_Flag_Buf_Type(sourceCfg[0]->config.chInfo[i].flags);
        Vps_printf("dataFmt[%d] = %u \n",i, dataFmt[i]);
        Vps_printf("scanFmt[%d] = %u \n",i, scanFmt[i]);
        Vps_printf("bufType[%d] = %u \n",i, bufType[i]);
        Vps_printf("width[%d] = %u \n",i, sourceCfg[0]->config.chInfo[i].width);
        Vps_printf("height[%d] = %u \n",i, sourceCfg[0]->config.chInfo[i].height);
    }

    /* reading the source configuration and storing to the chain instance */
    memcpy(pObj->source_config,
           *sourceCfg,
           sizeof(struct vivi_source_config) * A15SOURCE_SRV_2D_880x1080_NUM_EP_SOURCE);

    status = chains_a15Source2dSurroundView_Create(&pObj->ucObj, pObj);
    chains_a15Source2dSurroundView_saveLUT();

    /* Make sure the id's are still the same as set in init function */
    OSA_assert(sink->eplink_id[0] == pObj->ucObj.EpSink_2LinkID);
    OSA_assert(sink->eplink_id[1] == pObj->ucObj.EpSink_1LinkID);
    OSA_assert(source->eplink_id[0] == pObj->ucObj.EpSourceLinkID);

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_CreateSrcEpApp DONE !!!\n");
    return status;
}

Int32 chains_a15Source2dSurroundView_StartApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_StartApp !!!\n");
    ChainsCommon_memPrintHeapStatus();

    status = chains_a15Source2dSurroundView_Start(&gA15Source2dSurroundViewAppObj.ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_StartApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source2dSurroundView_StopApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_StopApp !!!\n");
    status = chains_a15Source2dSurroundView_Stop(&gA15Source2dSurroundViewAppObj.ucObj);

    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_StopApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source2dSurroundView_DeleteApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_DeleteApp !!!\n");
    status = chains_a15Source2dSurroundView_Delete(&gA15Source2dSurroundViewAppObj.ucObj);

    ChainsCommon_SurroundView_CalibDeInit();

    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_DeleteApp DONE!!!\n");
    return status;
}
Int32 chains_a15Source2dSurroundView_PauseApp()
{
    Int32 status;
    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_PauseApp !!!\n");
    chains_a15Source2dSurroundViewObj *pObj = &gA15Source2dSurroundViewAppObj.ucObj;
    status = System_linkStop(pObj->EpSourceLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_PauseApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source2dSurroundView_ResumeApp()
{
    Int32 status;
    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_ResumeApp !!!\n");
    chains_a15Source2dSurroundViewObj *pObj = &gA15Source2dSurroundViewAppObj.ucObj;
    status = System_linkStart(pObj->EpSourceLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Vps_printf(" CHAIN: chains_a15Source2dSurroundView_ResumeApp DONE!!!\n");
    return status;
}


Void chains_a15Source2dSurroundView_CalibApp()
{
    ChainsCommon_SurroundView_MenuCalibration();
}

Void chains_a15Source2dSurroundView_StatApp()
{
    chains_a15Source2dSurroundView_printStatistics(&gA15Source2dSurroundViewAppObj.ucObj);
    ChainsCommon_memPrintHeapStatus();
}
