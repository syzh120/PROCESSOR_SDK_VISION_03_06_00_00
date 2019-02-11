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
#ifndef __SRV_CHAIN_H__
#define __SRV_CHAIN_H__

enum srv_chain_id {
    LVDS_SRV_2D_880x1080,
    LVDS_SRV_3D_880x1080,
    A15SOURCE_SRV_2D_880x1080,
    A15SOURCE_SRV_3D_880x1080,
#ifdef ISS_INCLUDE
    CAL_ISS_SRV_3D_880x1080,
#endif
    SRV_NUM_CHAINS,
};

/* a15source-2d-srv-info */
#define A15SOURCE_SRV_2D_880x1080_NUM_EP_SINK   (2)
#define A15SOURCE_SRV_2D_880x1080_NUM_EP_SOURCE (1)
/* a15source-3d-srv-info */
#define A15SOURCE_SRV_3D_880x1080_NUM_EP_SINK   (2)
#define A15SOURCE_SRV_3D_880x1080_NUM_EP_SOURCE (1)

Int32 chains_lvdsVip2dSurroundView_CreateApp(struct vivi_sink *sink, struct vivi_source *source);
Int32 chains_lvdsVip2dSurroundView_StartApp();
Int32 chains_lvdsVip2dSurroundView_StopApp();
Int32 chains_lvdsVip2dSurroundView_DeleteApp();
Int32 chains_lvdsVip2dSurroundView_PauseApp();
Int32 chains_lvdsVip2dSurroundView_ResumeApp();

Int32 chains_lvdsVip3dSurroundView_CreateApp(struct vivi_sink *sink, struct vivi_source *source);
Int32 chains_lvdsVip3dSurroundView_StartApp();
Int32 chains_lvdsVip3dSurroundView_StopApp();
Int32 chains_lvdsVip3dSurroundView_DeleteApp();
Int32 chains_lvdsVip3dSurroundView_PauseApp();
Int32 chains_lvdsVip3dSurroundView_ResumeApp();

Int32 chains_issMultiCaptIsp_Sgx3Dsrv_CreateApp(struct vivi_sink *sink, struct vivi_source *source);
Int32 chains_issMultiCaptIsp_Sgx3Dsrv_StartApp();
Int32 chains_issMultiCaptIsp_Sgx3Dsrv_StopApp();
Int32 chains_issMultiCaptIsp_Sgx3Dsrv_DeleteApp();
Int32 chains_issMultiCaptIsp_Sgx3Dsrv_PauseApp();
Int32 chains_issMultiCaptIsp_Sgx3Dsrv_ResumeApp();

Int32 chains_a15Source2dSurroundView_StartApp();
Int32 chains_a15Source2dSurroundView_StopApp();
Int32 chains_a15Source2dSurroundView_DeleteApp();
Int32 chains_a15Source2dSurroundView_PauseApp();
Int32 chains_a15Source2dSurroundView_ResumeApp();
Void  chains_a15Source2dSurroundView_InitApp(struct vivi_sink *sink,
    struct vivi_source *source);
Int32 chains_a15Source2dSurroundView_CreateSrcEpApp(struct vivi_sink *sink,
    struct vivi_source *source, struct vivi_source_config *sourceCfg[]);
Void chains_a15Source2dSurroundView_StatApp();


Int32 chains_a15Source3dSurroundView_StartApp();
Int32 chains_a15Source3dSurroundView_StopApp();
Int32 chains_a15Source3dSurroundView_DeleteApp();
Int32 chains_a15Source3dSurroundView_PauseApp();
Int32 chains_a15Source3dSurroundView_ResumeApp();
Void  chains_a15Source3dSurroundView_InitApp(struct vivi_sink *sink,
    struct vivi_source *source);
Int32 chains_a15Source3dSurroundView_CreateSrcEpApp(struct vivi_sink *sink,
    struct vivi_source *source, struct vivi_source_config *sourceCfg[]);
Void chains_a15Source3dSurroundView_StatApp();

#endif /* __SRV_CHAIN_H__ */
