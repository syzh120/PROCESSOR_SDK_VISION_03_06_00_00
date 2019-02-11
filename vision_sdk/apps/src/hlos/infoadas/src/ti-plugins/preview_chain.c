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

#include <vivi_plugin.h>
#include <vivi_preview.h>
#include <preview_priv.h>
#include "include/preview_chain.h"

struct preview_chain {
    struct vivi_chain_info info;
    struct preview_chain_func func;
};

static const struct preview_chain preview_ctab[PREVIEW_NUM_CHAINS] =
{
    {
        .info = {
            "lvds-vip-single-cam",
            PREVIEW_LVDS_SINGLE_CAM,
            PREVIEW_LVDS_SINGLE_CAM_NUM_EP_SINK,
            PREVIEW_LVDS_SINGLE_CAM_NUM_EP_SOURCE
        },
        .func = {
           {
                &chains_lvdsVipSingleCamCapture_CreateApp,
                &chains_lvdsVipSingleCamCapture_StartApp,
                &chains_lvdsVipSingleCamCapture_StopApp,
                &chains_lvdsVipSingleCamCapture_DeleteApp
            }
        }
    },
    {
        .info = {
            "lvds-vip-multi-cam",
            PREVIEW_LVDS_MULTI_CAM,
            PREVIEW_LVDS_MULTI_CAM_NUM_EP_SINK,
            PREVIEW_LVDS_MULTI_CAM_NUM_EP_SOURCE
        },
        .func = {
           {
                &chains_lvdsVipMultiCamCapture_CreateApp,
                &chains_lvdsVipMultiCamCapture_StartApp,
                &chains_lvdsVipMultiCamCapture_StopApp,
                &chains_lvdsVipMultiCamCapture_DeleteApp
            }
        }
    },

#ifdef ISS_INCLUDE
    {
        .info = {
            "csi2-cal-multi-cam",
            PREVIEW_CSI2CAL_MULTI_CAM,
            PREVIEW_CSI2CAL_MULTI_CAM_NUM_EP_SINK,
            PREVIEW_CSI2CAL_MULTI_CAM_NUM_EP_SOURCE
        },
        .func = {
           {
                &chains_csi2CalMultiCam_View_CreateApp,
                &chains_csi2CalMultiCam_View_StartApp,
                &chains_csi2CalMultiCam_View_StopApp,
                &chains_csi2CalMultiCam_View_DeleteApp
            }
        }
    },
#endif

#ifdef QNX_BUILD
    {
        .info = {
            "buf-loop",
            PREVIEW_BUF_LOOP,
            PREVIEW_BUF_LOOP_NUM_EP_SINK,
            PREVIEW_BUF_LOOP_NUM_EP_SOURCE
        },
        .func = {
            {
                NULL,
                &chains_bufLoop_StartApp,
                &chains_bufLoop_StopApp,
                &chains_bufLoop_DeleteApp,
                &chains_bufLoop_InitSourceEpApp,
                &chains_bufLoop_CreateSourceEpApp,
            }
        }
    },
#endif
};

DEFINE_PLUGIN_NUM_CHAINS_FUNC(PREVIEW_PNAME_TOKEN)
{
    return (PREVIEW_NUM_CHAINS);
}

DEFINE_PLUGIN_CHAIN_INFO_FUNC(PREVIEW_PNAME_TOKEN, chain_info, idx)
{
    if (idx < PREVIEW_NUM_CHAINS) {
        strcpy(chain_info->cname, preview_ctab[idx].info.cname);
        chain_info->id = preview_ctab[idx].info.id;
        chain_info->num_sink_eplink = preview_ctab[idx].info.num_sink_eplink;
        chain_info->num_source_eplink = preview_ctab[idx].info.num_source_eplink;
    }
}

DEFINE_PLUGIN_CHAIN_CONTROL_FUNC(PREVIEW_PNAME_TOKEN, chain_func, chain_id)
{
    if (chain_id < PREVIEW_NUM_CHAINS) {
        chain_func->create = preview_ctab[chain_id].func.create;
        chain_func->start = preview_ctab[chain_id].func.start;
        chain_func->stop = preview_ctab[chain_id].func.stop;
        chain_func->delete = preview_ctab[chain_id].func.delete;
        chain_func->init = preview_ctab[chain_id].func.init;
        chain_func->create_with_source_ep = preview_ctab[chain_id].func.create_with_source_ep;
    }
}
