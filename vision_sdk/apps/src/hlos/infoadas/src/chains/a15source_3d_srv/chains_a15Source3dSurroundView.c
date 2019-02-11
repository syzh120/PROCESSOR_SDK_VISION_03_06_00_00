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
#include "chains_a15Source3dSurroundView_priv.h"
#include <src/hlos/common/chains_common.h>
#include <vivi_srv.h>
#include "../../ti-plugins/include/srv_chain.h"

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
#define CAPTURE_SENSOR_WIDTH                 (1280)
#define CAPTURE_SENSOR_HEIGHT                (720)
#define SGX3DSRV_OUTPUT_FRAME_WIDTH          (880)
#define SGX3DSRV_OUTPUT_FRAME_HEIGHT         (1080)

typedef struct {
    chains_a15Source3dSurroundViewObj ucObj;

    struct vivi_source source;
    struct vivi_sink sink;
    struct vivi_source_config source_config[A15SOURCE_SRV_3D_880x1080_NUM_EP_SOURCE];
    UInt32 numLvdsCh;
    AlgorithmLink_SrvOutputModes svOutputMode;
    Bool enableCarOverlayInAlg;
} Chains_A15Source3dSurroundViewAppObj;

Chains_A15Source3dSurroundViewAppObj gA15Source3dSurroundViewAppObj;

static Void chains_a15Source3dSurroundView_SetSgx3DsrvLinkPrms (
                                  Sgx3DsrvLink_CreateParams *prms)
{
    prms->maxOutputHeight = SGX3DSRV_OUTPUT_FRAME_HEIGHT;
    prms->maxOutputWidth = SGX3DSRV_OUTPUT_FRAME_WIDTH;
    prms->maxInputHeight = CAPTURE_SENSOR_HEIGHT;
    prms->maxInputWidth = CAPTURE_SENSOR_WIDTH;
    prms->numViews = 1;
    prms->bAnimate = 1;
    prms->numInQue = 4;
    prms->inBufType[0] = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    prms->inBufType[1] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[2] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->inBufType[3] = SYSTEM_BUFFER_TYPE_METADATA;
    prms->bEglInfoInCreate = FALSE;
    prms->EglInfo = NULL;
}

Void chains_a15Source3dSurroundView_SetAppPrms(
            chains_a15Source3dSurroundViewObj *pUcObj, Void *appObj)
{
    EpLink_CreateParams  *pEndp;

    Chains_A15Source3dSurroundViewAppObj *pObj
        = (Chains_A15Source3dSurroundViewAppObj*)appObj;

    UInt32 svOutWidth, svOutHeight;

    ChainsCommon_SurroundView_GetSrvOutputResolution(
                                    pObj->svOutputMode,
                                    &svOutWidth,
                                    &svOutHeight);

    /* Synthesis */
    ChainsCommon_SurroundView_SetSynthParams(
                                    &pUcObj->Alg_SynthesisPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->svOutputMode,
                                    pObj->enableCarOverlayInAlg);

    /* Geo Align */
    ChainsCommon_SurroundView_SetGAlign3DParams(
                                    &pUcObj->Alg_GeoAlign3DPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->svOutputMode);

    /* Photo Align */
    ChainsCommon_SurroundView_SetPAlignParams(
                                    &pUcObj->Alg_PhotoAlignPrm,
                                    SRV_LVDS_CAPTURE_WIDTH,
                                    SRV_LVDS_CAPTURE_HEIGHT,
                                    svOutWidth,
                                    svOutHeight,
                                    SRV_NUM_VIEWS,
                                    SRV_CARBOX_WIDTH,
                                    SRV_CARBOX_HEIGHT,
                                    pObj->svOutputMode);

    chains_a15Source3dSurroundView_SetSgx3DsrvLinkPrms
                        (&pUcObj->Sgx3DsrvPrm);

    /* We have three epLinks (1 src + 2 sink) in the chain; we will configure them now */
    /* sink2 */
    pEndp = &pUcObj->EpSink_2Prm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = A15SOURCE_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);

    /* sink1 */
    pEndp = &pUcObj->EpSink_1Prm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = A15SOURCE_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);

    /* source configuration */
    pEndp = &pUcObj->EpSourcePrm;
    pEndp->epType = EP_SOURCE;
    pEndp->chainId = A15SOURCE_SRV_3D_880x1080;
    strcpy(pEndp->plugName, SRV_PLUGIN_NAME);
    /* copy the source config data to the epSource link's config structure */
    if (pObj->source_config[0].eplink_id == pObj->source.eplink_id[0]) {
        memcpy(&pEndp->srcConfig.queInfo, &pObj->source_config[0].config,
            sizeof(System_LinkQueInfo));
    }
}

Void  chains_a15Source3dSurroundView_InitApp(struct vivi_sink *sink,
    struct vivi_source *source)
{
    Bool startWithCalibration;
    Chains_A15Source3dSurroundViewAppObj *pObj
        = (Chains_A15Source3dSurroundViewAppObj*)&gA15Source3dSurroundViewAppObj;

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_InitApp !!!\n");

    /* SRV Algo related initialization */
    pObj->numLvdsCh = 4;
    pObj->svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
    pObj->enableCarOverlayInAlg = 0;

    /* Set startWithCalibration = TRUE to start the demo with calibration.
       Else it will use the previously calibrated LUTs */
    startWithCalibration = TRUE;
    ChainsCommon_SurroundView_CalibInit(
                                startWithCalibration,
                                pObj->svOutputMode);

    /* Set the link ids */
    chains_a15Source3dSurroundView_SetLinkId(&pObj->ucObj);

    /* Let's read the epLink ids to the back to caller */
    sink->eplink_id[0] = pObj->ucObj.EpSink_1LinkID;
    sink->eplink_id[1] = pObj->ucObj.EpSink_2LinkID;
    source->eplink_id[0] = pObj->ucObj.EpSourceLinkID;
    /* saving into the chain instance for future */
    pObj->sink.eplink_id[0] = sink->eplink_id[0];
    pObj->sink.eplink_id[1] = sink->eplink_id[1];
    pObj->source.eplink_id[0] = source->eplink_id[0];

    ChainsCommon_statCollectorReset();

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_InitApp DONE !!!\n");
}

Int32 chains_a15Source3dSurroundView_CreateSrcEpApp(struct vivi_sink *sink,
    struct vivi_source *source, struct vivi_source_config *sourceCfg[])
{
    Int32 status;
    Chains_A15Source3dSurroundViewAppObj *pObj
        = (Chains_A15Source3dSurroundViewAppObj*)&gA15Source3dSurroundViewAppObj;

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_CreateSrcEpApp !!!\n");

    /* reading the source configuration and storing to the chain instance */
    memcpy(pObj->source_config,
           *sourceCfg,
           sizeof(struct vivi_source_config) * A15SOURCE_SRV_3D_880x1080_NUM_EP_SOURCE);

    status = chains_a15Source3dSurroundView_Create(&pObj->ucObj, pObj);

    /* Make sure the id's are still the same as set in init function */
    OSA_assert(sink->eplink_id[0] == pObj->ucObj.EpSink_1LinkID);
    OSA_assert(sink->eplink_id[1] == pObj->ucObj.EpSink_2LinkID);
    OSA_assert(source->eplink_id[0] == pObj->ucObj.EpSourceLinkID);

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_CreateSrcEpApp DONE !!!\n");
    return status;
}

Int32 chains_a15Source3dSurroundView_StartApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_StartApp !!!\n");
    ChainsCommon_memPrintHeapStatus();

    status = chains_a15Source3dSurroundView_Start(&gA15Source3dSurroundViewAppObj.ucObj);

    ChainsCommon_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_StartApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source3dSurroundView_StopApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_StopApp !!!\n");
    status = chains_a15Source3dSurroundView_Stop(&gA15Source3dSurroundViewAppObj.ucObj);

    ChainsCommon_prfLoadCalcEnable(FALSE, TRUE, TRUE);

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_StopApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source3dSurroundView_DeleteApp()
{
    Int32 status;

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_DeleteApp !!!\n");
    status = chains_a15Source3dSurroundView_Delete(&gA15Source3dSurroundViewAppObj.ucObj);

    ChainsCommon_SurroundView_CalibDeInit();

    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_DeleteApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source3dSurroundView_PauseApp()
{
    Int32 status;
    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_PauseApp !!!\n");
    chains_a15Source3dSurroundViewObj *pObj = &gA15Source3dSurroundViewAppObj.ucObj;
    status = System_linkStop(pObj->EpSourceLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_PauseApp DONE!!!\n");
    return status;
}

Int32 chains_a15Source3dSurroundView_ResumeApp()
{
    Int32 status;
    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_ResumeApp !!!\n");
    chains_a15Source3dSurroundViewObj *pObj = &gA15Source3dSurroundViewAppObj.ucObj;
    status = System_linkStart(pObj->EpSourceLinkID);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    Vps_printf(" CHAIN: chains_a15Source3dSurroundView_PauseApp DONE!!!\n");
    return status;
}

Void chains_a15Source3dSurroundView_CalibApp()
{
    ChainsCommon_SurroundView_MenuCalibration();
}

Void chains_a15Source3dSurroundView_StatApp()
{
    chains_a15Source3dSurroundView_printStatistics(&gA15Source3dSurroundViewAppObj.ucObj);
    ChainsCommon_memPrintHeapStatus();
}
