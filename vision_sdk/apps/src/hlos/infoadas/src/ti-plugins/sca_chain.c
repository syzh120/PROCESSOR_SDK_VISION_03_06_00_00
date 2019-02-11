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
#include <vivi_sca.h>
#include <sca_priv.h>
#include "include/sca_chain.h"

struct sca_chain {
    struct vivi_chain_info info;
    struct sca_chain_func func;
};

static const struct sca_chain sca_ctab[SCA_NUM_CHAINS] =
{
#ifndef TDA2EX_BUILD
    {
        .info = {
            "lvds-vip-single-cam-analytics",
            SCA_LVDS_SINGLE_CAM,
            SCA_LVDS_SINGLE_CAM_NUM_EP_SINK,
            SCA_LVDS_SINGLE_CAM_NUM_EP_SOURCE
        },
        .func = {
           {
                &chains_lvdsVipSingleCamAnalytics_CreateApp,
                &chains_lvdsVipSingleCamAnalytics_StartApp,
                &chains_lvdsVipSingleCamAnalytics_StopApp,
                &chains_lvdsVipSingleCamAnalytics_DeleteApp
            }
        }
    },
#endif
#if 0 /* Not tested */
    {
        .info = {
            "lvds-vip-single-cam-analytics2",
            SCA_LVDS_SINGLE_CAM_ANALYTICS2,
            SCA_LVDS_SINGLE_CAM_ANALYTICS2_NUM_EP_SINK,
            SCA_LVDS_SINGLE_CAM_ANALYTICS2_NUM_EP_SOURCE
        },
        .func = {
           {
                &chains_vipSingleCameraAnalytics2_CreateApp,
                &chains_vipSingleCameraAnalytics2_StartApp,
                &chains_vipSingleCameraAnalytics2_StopApp,
                &chains_vipSingleCameraAnalytics2_DeleteApp
            }
        }
    },
#endif
};

DEFINE_PLUGIN_NUM_CHAINS_FUNC(SCA_PNAME_TOKEN)
{
    return (SCA_NUM_CHAINS);
}

DEFINE_PLUGIN_CHAIN_INFO_FUNC(SCA_PNAME_TOKEN, chain_info, idx)
{
    if (idx < SCA_NUM_CHAINS) {
        strcpy(chain_info->cname, sca_ctab[idx].info.cname);
        chain_info->id = sca_ctab[idx].info.id;
        chain_info->num_sink_eplink = sca_ctab[idx].info.num_sink_eplink;
        chain_info->num_source_eplink = sca_ctab[idx].info.num_source_eplink;
    }
}

DEFINE_PLUGIN_CHAIN_CONTROL_FUNC(SCA_PNAME_TOKEN, chain_func, chain_id)
{
    if (chain_id < SCA_NUM_CHAINS) {
        chain_func->create = sca_ctab[chain_id].func.create;
        chain_func->start = sca_ctab[chain_id].func.start;
        chain_func->stop = sca_ctab[chain_id].func.stop;
        chain_func->delete = sca_ctab[chain_id].func.delete;
        chain_func->init = sca_ctab[chain_id].func.init;
        chain_func->create_with_source_ep = sca_ctab[chain_id].func.create_with_source_ep;
    }
}
