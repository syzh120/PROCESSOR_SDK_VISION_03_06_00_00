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
#include <vivi_srv.h>
#include <srv_priv.h>
#include "include/srv_chain.h"

#include <system_linkId.h>
#include <sgx3DsrvLink.h>

/* 2d-srv-info */
#define LVDS_SRV_2D_880x1080_NUM_EP_SINK   (2)
#define LVDS_SRV_2D_880x1080_NUM_EP_SOURCE (0)
/* 3d-srv-info */
#define LVDS_SRV_3D_880x1080_NUM_EP_SINK   (2)
#define LVDS_SRV_3D_880x1080_NUM_EP_SOURCE (0)
/* 3d-srv-info */
#define CAL_ISS_SRV_3D_880x1080_NUM_EP_SINK   (2)
#define CAL_ISS_SRV_3D_880x1080_NUM_EP_SOURCE (0)

struct srv_chain {
    struct vivi_chain_info info;
    struct srv_chain_func func;
};

static const struct srv_chain srv_ctab[SRV_NUM_CHAINS] =
{
    {
        .info = {
            "lvds-srv-2d-880x1080",
            LVDS_SRV_2D_880x1080,
            LVDS_SRV_2D_880x1080_NUM_EP_SINK,
            LVDS_SRV_2D_880x1080_NUM_EP_SOURCE
        },
        .func = {
            {
                &chains_lvdsVip2dSurroundView_CreateApp,
                &chains_lvdsVip2dSurroundView_StartApp,
                &chains_lvdsVip2dSurroundView_StopApp,
                &chains_lvdsVip2dSurroundView_DeleteApp,
                NULL,
                NULL
            },
            &chains_lvdsVip2dSurroundView_PauseApp,
            &chains_lvdsVip2dSurroundView_ResumeApp
        }
    },
    {
        .info = {
            "lvds-srv-3d-880x1080",
            LVDS_SRV_3D_880x1080,
            LVDS_SRV_3D_880x1080_NUM_EP_SINK,
            LVDS_SRV_3D_880x1080_NUM_EP_SOURCE
        },
        .func = {
            {
                &chains_lvdsVip3dSurroundView_CreateApp,
                &chains_lvdsVip3dSurroundView_StartApp,
                &chains_lvdsVip3dSurroundView_StopApp,
                &chains_lvdsVip3dSurroundView_DeleteApp,
                NULL,
                NULL
            },
            &chains_lvdsVip3dSurroundView_PauseApp,
            &chains_lvdsVip3dSurroundView_ResumeApp
        }
    },
    {
        .info = {
            "a15source-srv-2d-880x1080",
            A15SOURCE_SRV_2D_880x1080,
            A15SOURCE_SRV_2D_880x1080_NUM_EP_SINK,
            A15SOURCE_SRV_2D_880x1080_NUM_EP_SOURCE
        },
        .func = {
            {
                NULL,
                &chains_a15Source2dSurroundView_StartApp,
                &chains_a15Source2dSurroundView_StopApp,
                &chains_a15Source2dSurroundView_DeleteApp,
                &chains_a15Source2dSurroundView_InitApp,
                &chains_a15Source2dSurroundView_CreateSrcEpApp
            },
                &chains_a15Source2dSurroundView_PauseApp,
                &chains_a15Source2dSurroundView_ResumeApp,
        }
    },
    {
        .info = {
            "a15source-srv-3d-880x1080",
            A15SOURCE_SRV_3D_880x1080,
            A15SOURCE_SRV_3D_880x1080_NUM_EP_SINK,
            A15SOURCE_SRV_3D_880x1080_NUM_EP_SOURCE
        },
        .func = {
            {
                NULL,
                &chains_a15Source3dSurroundView_StartApp,
                &chains_a15Source3dSurroundView_StopApp,
                &chains_a15Source3dSurroundView_DeleteApp,
                &chains_a15Source3dSurroundView_InitApp,
                &chains_a15Source3dSurroundView_CreateSrcEpApp
            },
                &chains_a15Source3dSurroundView_PauseApp,
                &chains_a15Source3dSurroundView_ResumeApp,
        }
    },
#ifdef ISS_INCLUDE
    {
        .info = {
            "cal-iss-srv-3d-880x1080",
            CAL_ISS_SRV_3D_880x1080,
            CAL_ISS_SRV_3D_880x1080_NUM_EP_SINK,
            CAL_ISS_SRV_3D_880x1080_NUM_EP_SOURCE
        },
        .func = {
            {
		&chains_issMultiCaptIsp_Sgx3Dsrv_CreateApp,
		&chains_issMultiCaptIsp_Sgx3Dsrv_StartApp,
		&chains_issMultiCaptIsp_Sgx3Dsrv_StopApp,
		&chains_issMultiCaptIsp_Sgx3Dsrv_DeleteApp,
                NULL,
                NULL
            },
	    &chains_issMultiCaptIsp_Sgx3Dsrv_PauseApp,
	    &chains_issMultiCaptIsp_Sgx3Dsrv_ResumeApp,
        }
    },
#endif
};

DEFINE_PLUGIN_NUM_CHAINS_FUNC(SRV_PNAME_TOKEN)
{
    return (SRV_NUM_CHAINS);
}

DEFINE_PLUGIN_CHAIN_INFO_FUNC(SRV_PNAME_TOKEN, chain_info, idx)
{
    if (idx < SRV_NUM_CHAINS) {
        strcpy(chain_info->cname, srv_ctab[idx].info.cname);
        chain_info->id = srv_ctab[idx].info.id;
        chain_info->num_sink_eplink = srv_ctab[idx].info.num_sink_eplink;
        chain_info->num_source_eplink = srv_ctab[idx].info.num_source_eplink;
    }
}

DEFINE_PLUGIN_CHAIN_CONTROL_FUNC(SRV_PNAME_TOKEN, chain_func, chain_id)
{
    struct srv_chain_func *srv_cfunc = (struct srv_chain_func*) chain_func;

    if (chain_id < SRV_NUM_CHAINS) {
        chain_func->create = srv_ctab[chain_id].func.create;
        chain_func->start = srv_ctab[chain_id].func.start;
        chain_func->stop = srv_ctab[chain_id].func.stop;
        chain_func->delete = srv_ctab[chain_id].func.delete;
        /* source ep specific */
        chain_func->init = srv_ctab[chain_id].func.init;
        chain_func->create_with_source_ep = srv_ctab[chain_id].func.create_with_source_ep;
        /* srv specific */
        srv_cfunc->pause = srv_ctab[chain_id].func.pause;
        srv_cfunc->resume = srv_ctab[chain_id].func.resume;
    }
}

void srv_get_egl_link(uint32_t *link_id, uint32_t *chain_id, uint32_t *num_egl_chain, uint32_t *command)
{
    *link_id = SYSTEM_LINK_ID_SGX3DSRV_0;
    *num_egl_chain = 2; /* Return chains involving EGL links */
    chain_id[0] = LVDS_SRV_3D_880x1080;
    chain_id[1] = A15SOURCE_SRV_3D_880x1080;
#ifdef ISS_INCLUDE
    *num_egl_chain = 3; /* Return chains involving EGL links */
    chain_id[2] = CAL_ISS_SRV_3D_880x1080;
#endif
    *command = SGXLINK_CMD_ACQUIRE_EGL_INFO;
}
