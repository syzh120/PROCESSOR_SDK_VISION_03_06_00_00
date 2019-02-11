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
#include "chains_lvdsVip2dSurroundView_priv.h"
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
enum synctype {
    LOOSE_SYNC,
    TIGHT_SYNC
};


typedef struct {
    chains_lvdsVip2dSurroundViewObj ucObj;
    VideoSensorCreateAndStartAppPrm vidSensorPrm;

    UInt32 num_captures;
    UInt32 num_buffers_per_capture;
    UInt32 portId[VIDEO_SENSOR_MAX_LVDS_CAMERAS];
    UInt32 capture_width;
    UInt32 capture_height;

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
} Chains_LvdsVip2dSurroundViewAppObj;

Chains_LvdsVip2dSurroundViewAppObj gLvdsVip2dSurroundViewObj;

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
Void chains_lvdsVip2dSurroundView_SetAppPrms(
            chains_lvdsVip2dSurroundViewObj *pUcObj, Void *appObj)
{
    Vps_printf("Inside setting app Prms for 2D-SRV\n");
    UInt32 i;
    CaptureLink_CreateParams  *pVipCapture;
    EpLink_CreateParams  *pEndp;
    Chains_LvdsVip2dSurroundViewAppObj *pObj;

#ifndef EARLY_SRV_ENABLE
    UInt32 tmpReadSize=0;
    UInt8 *virt_addr;
    int osa_ret=OSA_SOK;
#endif
    pObj = (Chains_LvdsVip2dSurroundViewAppObj*)appObj;
    pObj->vidSensorPrm.captureSrcId = CHAINS_CAPTURE_SRC_OV10635;
    pObj->vidSensorPrm.isLVDSCaptMode = TRUE;
    pObj->vidSensorPrm.numLvdsCh = 4;

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
            APP_CTRL_LINK_CMD_VIDEO_SENSOR_CREATE_AND_START,
            &pObj->vidSensorPrm,
            sizeof(VideoSensorCreateAndStartAppPrm),
            TRUE);

    pVipCapture = &pUcObj->CapturePrm;
    ChainsCommon_MultiCam_SetCapturePrms(&pUcObj->CapturePrm,
                             pObj->num_captures);

    for (i=0; i<SYSTEM_CAPTURE_VIP_INST_MAX; i++) {
        pVipCapture->vipInst[i].numBufs = pObj->num_buffers_per_capture;
    }

    ChainsCommon_SurroundView_SetSyncPrm(&pUcObj->Sync_svPrm, pObj->num_captures,
                                              TIGHT_SYNC);

    ChainsCommon_SurroundView_SetSynthParams(&pUcObj->Alg_SynthesisPrm,
                                              pObj->svInWidth, pObj->svInHeight,
                                              pObj->svOutWidth, pObj->svOutHeight,
                                              pObj->svNumViews,
                                              pObj->svCarImageWidth,
                                              pObj->svCarImageHeight,
                                              pObj->svOutputMode,
                                              pObj->enableCarOverlayInAlg);
    
    pUcObj->Alg_SynthesisPrm.useStaticGALut = TRUE;

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
    
    pUcObj->Alg_GeoAlignPrm.bypass_GA = TRUE;

    ChainsCommon_SurroundView_SetPAlignParams(&pUcObj->Alg_PhotoAlignPrm,
                                              pObj->svInWidth, pObj->svInHeight,
                                              pObj->svOutWidth, pObj->svOutHeight,
                                              pObj->svNumViews,
                                              pObj->svCarImageWidth,
                                              pObj->svCarImageHeight,
                                              pObj->svOutputMode);

    /* We have two epLinks in the chain; we will configure them now */
    /* sink2 */
    pEndp = &pUcObj->EpSink_2Prm;;
    pEndp->epType = EP_SINK;
    pEndp->chainId = LVDS_SRV_2D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);

    /* sink1 */
    pEndp = &pUcObj->EpSink_1Prm;;
    pEndp->epType = EP_SINK;
    pEndp->chainId = LVDS_SRV_2D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);
    Vps_printf("Set-App Prms done\n");
}

Void chains_lvdsVip2dSurroundView_saveLUT()
{
    Chains_LvdsVip2dSurroundViewAppObj *pObj;
    chains_lvdsVip2dSurroundViewObj *pUcObj;
    UInt8 *virt_addr = NULL;

    pObj = (Chains_LvdsVip2dSurroundViewAppObj*)&gLvdsVip2dSurroundViewObj;
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

Void chains_lvdsVip2dSurroundView_InitApp()
{
    Bool startWithCalibration;
    Chains_LvdsVip2dSurroundViewAppObj *pObj
        = (Chains_LvdsVip2dSurroundViewAppObj*)&gLvdsVip2dSurroundViewObj;

    /* Capture related initialization */
    pObj->num_captures = 4;
    pObj->num_buffers_per_capture = 6;
    pObj->capture_width = LVDS_CAPTURE_WIDTH;
    pObj->capture_height = LVDS_CAPTURE_HEIGHT;

#ifdef TDA2EX_BUILD
    //This change is done for supporting tda2ex
    pObj->portId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pObj->portId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pObj->portId[2] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTB;
    pObj->portId[3] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTB;
#else
    pObj->portId[0] = SYSTEM_CAPTURE_INST_VIP1_SLICE1_PORTA;
    pObj->portId[1] = SYSTEM_CAPTURE_INST_VIP1_SLICE2_PORTA;
    pObj->portId[2] = SYSTEM_CAPTURE_INST_VIP2_SLICE1_PORTA;
    pObj->portId[3] = SYSTEM_CAPTURE_INST_VIP3_SLICE1_PORTA;
    pObj->portId[4] = SYSTEM_CAPTURE_INST_VIP3_SLICE2_PORTA;
    pObj->portId[5] = SYSTEM_CAPTURE_INST_VIP2_SLICE2_PORTB;
#endif

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
}

Int32 chains_lvdsVip2dSurroundView_CreateApp(struct vivi_sink *sink, struct vivi_source *source)
{
    Int32 status;
    chains_lvdsVip2dSurroundViewObj *pUcObj;

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_CreateApp !!!\n");
    chains_lvdsVip2dSurroundView_InitApp();
    status = chains_lvdsVip2dSurroundView_Create(&gLvdsVip2dSurroundViewObj.ucObj, &gLvdsVip2dSurroundViewObj);

    chains_lvdsVip2dSurroundView_saveLUT();
    /* Let's set the epLink ids now */
    pUcObj = &gLvdsVip2dSurroundViewObj.ucObj;
    sink->eplink_id[0] = pUcObj->EpSink_2LinkID;
    sink->eplink_id[1] = pUcObj->EpSink_1LinkID;

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_CreateApp DONE !!!\n");
    return status;
}

Int32 chains_lvdsVip2dSurroundView_StartApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_StartApp !!!\n");
    ChainsCommon_memPrintHeapStatus();

    status = chains_lvdsVip2dSurroundView_Start(&gLvdsVip2dSurroundViewObj.ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_StartApp DONE!!!\n");
    return status;
}

Int32 chains_lvdsVip2dSurroundView_StopApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_StopApp !!!\n");
    status = chains_lvdsVip2dSurroundView_Stop(&gLvdsVip2dSurroundViewObj.ucObj);

    System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
            APP_CTRL_LINK_CMD_VIDEO_SENSOR_STOP_AND_DELETE,
            &gLvdsVip2dSurroundViewObj.vidSensorPrm,
            sizeof(VideoSensorCreateAndStartAppPrm),
            TRUE);
    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_StopApp DONE!!!\n");
    return status;
}

Int32 chains_lvdsVip2dSurroundView_DeleteApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_DeleteApp !!!\n");
    status = chains_lvdsVip2dSurroundView_Delete(&gLvdsVip2dSurroundViewObj.ucObj);

    ChainsCommon_SurroundView_CalibDeInit();

    Vps_printf(" CHAIN: chains_lvdsVip2dSurroundView_DeleteApp DONE!!!\n");
    return status;
}

Int32 chains_lvdsVip2dSurroundView_PauseApp()
{
    Int32 status;
    chains_lvdsVip2dSurroundViewObj *pObj = &gLvdsVip2dSurroundViewObj.ucObj;

    status = System_linkStop(pObj->CaptureLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Int32 chains_lvdsVip2dSurroundView_ResumeApp()
{
    Int32 status;
    chains_lvdsVip2dSurroundViewObj *pObj = &gLvdsVip2dSurroundViewObj.ucObj;

    status = System_linkStart(pObj->CaptureLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Void chains_lvdsVip2dSurroundView_CalibApp()
{
    ChainsCommon_SurroundView_MenuCalibration();
}

Void chains_lvdsVip2dSurroundView_StatApp()
{
    chains_lvdsVip2dSurroundView_printStatistics(&gLvdsVip2dSurroundViewObj.ucObj);
    ChainsCommon_memPrintHeapStatus();
}
