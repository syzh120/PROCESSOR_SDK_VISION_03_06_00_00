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

/**
 *******************************************************************************
 * \file chains_vipSingleCameraView.c
 *
 * \brief  Usecase file implementation of capture display usecase.
 *
 *         Usecase file for single camere view usecase.
 *
 *         EpSource --> EpSink Link(A15)
 *
 *         The data flow daigram is shown below
 *
 *              EpSource (A15)
 *                   |
 *               EpSink (A15)
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "chains_bufLoop_priv.h"
#include <src/hlos/common/chains_common.h>
#include <vivi_preview.h>
#include "../../ti-plugins/include/preview_chain.h"

/**
 *******************************************************************************
 *
 *  \brief  SingleCameraViewObject
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {
    chains_bufLoopObj ucObj;

    struct vivi_source source;
    struct vivi_source sink;

}chains_bufLoopAppObj;

chains_bufLoopAppObj gBufLoopObj;

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
Void chains_bufLoop_SetAppPrms(chains_bufLoopObj *pUcObj,Void *appObj)
{
}

Void chains_bufLoop_InitSourceEpApp(struct vivi_sink *sink, struct vivi_source *source)
{
    chains_bufLoopAppObj *pObj
        = (chains_bufLoopAppObj *)&gBufLoopObj;

    Vps_printf(" CHAIN: chains_bufLoop_InitSourceEpApp !!!\n");
    chains_bufLoop_SetLinkId(&pObj->ucObj);

    /* Let's set the epLink ids now */
    sink->eplink_id[0] = pObj->ucObj.EpSinkLinkID;
    source->eplink_id[0] = pObj->ucObj.EpSourceLinkID;
    /* saving into the chain instance for future */
    pObj->sink.eplink_id[0] = sink->eplink_id[0];
    pObj->source.eplink_id[0] = source->eplink_id[0];
    Vps_printf(" CHAIN: chains_bufLoop_InitSourceEpApp  done!!!\n");
}

Int32 chains_bufLoop_CreateSourceEpApp(struct vivi_sink *sink, struct vivi_source *source,
                struct vivi_source_config *sourceCfg[])
{
    Int32 status;
    Int32 i;
    EpLink_CreateParams  *pEndp;
    chains_bufLoopObj *pUcObj;
    chains_bufLoopAppObj *pObj
        = (chains_bufLoopAppObj *)&gBufLoopObj;

    Vps_printf(" CHAIN: chains_bufLoop_CreateSourceEpApp !!!\n");
    pUcObj = &pObj->ucObj;
    /* sink configuration */
    pEndp = &pUcObj->EpSinkPrm;
    pEndp->epType = EP_SINK;
    pEndp->chainId = PREVIEW_BUF_LOOP;
    strcpy(pEndp->plugName, PREVIEW_PLUGIN_NAME);
    /* source configuration */
    pEndp = &pUcObj->EpSourcePrm;
    pEndp->epType = EP_SOURCE;
    pEndp->chainId = PREVIEW_BUF_LOOP;
    strcpy(pEndp->plugName, PREVIEW_PLUGIN_NAME);

    for (i=0; i<PREVIEW_BUF_LOOP_NUM_EP_SOURCE; i++) {
        if (sourceCfg[i]->eplink_id == pObj->source.eplink_id[i]) {
            memcpy(&pEndp->srcConfig.queInfo, &sourceCfg[i]->config,
                            sizeof(System_LinkQueInfo));
        }
    }

    /* need to return it back to the application */
    sink->eplink_id[0] = pObj->sink.eplink_id[0];
    source->eplink_id[0] = pObj->source.eplink_id[0];

    status = chains_bufLoop_Create(&pObj->ucObj, pObj);
    Vps_printf(" CHAIN: chains_bufLoop_CreateSourceEpApp done!!! status - 0x%x\n", status);

    return status;
}

Int32 chains_bufLoop_StartApp(Void)
{
    Int32 status;
    chains_bufLoopAppObj *pObj
        = (chains_bufLoopAppObj *)&gBufLoopObj;

    Vps_printf(" CHAIN: chains_bufLoop_StartApp !!!\n");
    status = chains_bufLoop_Start(&pObj->ucObj);
    Vps_printf(" CHAIN: chains_bufLoop_StartApp done!!! status - 0x%x\n", status);

    return status;
}

Int32 chains_bufLoop_StopApp(Void)
{
    Int32 status;
    chains_bufLoopAppObj *pObj
        = (chains_bufLoopAppObj *)&gBufLoopObj;

    Vps_printf(" CHAIN: chains_bufLoop_StopApp !!!\n");
    status = chains_bufLoop_Stop(&pObj->ucObj);
    Vps_printf(" CHAIN: chains_bufLoop_StopApp done!!! status - 0x%x\n", status);

    return status;
}

Int32 chains_bufLoop_DeleteApp(Void)
{
    Int32 status;
    chains_bufLoopAppObj *pObj
        = (chains_bufLoopAppObj *)&gBufLoopObj;

    Vps_printf(" CHAIN: chains_bufLoop_Delete !!!\n");
    status = chains_bufLoop_Delete(&pObj->ucObj);
    Vps_printf(" CHAIN: chains_bufLoop_Delete done!!! status - 0x%x\n", status);

    return status;
}
