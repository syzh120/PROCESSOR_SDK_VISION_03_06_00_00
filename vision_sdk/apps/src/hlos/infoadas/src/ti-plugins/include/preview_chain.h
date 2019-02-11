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
#ifndef __PREVIEW_CHAIN_H__
#define __PREVIEW_CHAIN_H__

enum preview_chain_id {
    PREVIEW_LVDS_SINGLE_CAM,
    PREVIEW_LVDS_MULTI_CAM,
#ifdef ISS_INCLUDE
    PREVIEW_CSI2CAL_MULTI_CAM,
#endif
#ifdef QNX_BUILD
    PREVIEW_BUF_LOOP,
#endif
    PREVIEW_NUM_CHAINS,
};

/* preview-chain1-info */
#define PREVIEW_LVDS_SINGLE_CAM_NUM_EP_SINK   (1)
#define PREVIEW_LVDS_SINGLE_CAM_NUM_EP_SOURCE (0)
/* preview-chain2-info */
#define PREVIEW_LVDS_MULTI_CAM_NUM_EP_SINK   (1)
#define PREVIEW_LVDS_MULTI_CAM_NUM_EP_SOURCE (0)
/* preview-chain3-info */
#define PREVIEW_BUF_LOOP_NUM_EP_SINK   (1)
#define PREVIEW_BUF_LOOP_NUM_EP_SOURCE   (1)
/* preview-chain4-info */
#define PREVIEW_CSI2CAL_MULTI_CAM_NUM_EP_SINK   (1)
#define PREVIEW_CSI2CAL_MULTI_CAM_NUM_EP_SOURCE (0)

Int32 chains_lvdsVipSingleCamCapture_CreateApp(struct vivi_sink *sink,
		struct vivi_source *source);
Int32 chains_lvdsVipSingleCamCapture_StartApp();
Int32 chains_lvdsVipSingleCamCapture_StopApp();
Int32 chains_lvdsVipSingleCamCapture_DeleteApp();

Int32 chains_lvdsVipMultiCamCapture_CreateApp(struct vivi_sink *sink,
		struct vivi_source *source);
Int32 chains_lvdsVipMultiCamCapture_StartApp();
Int32 chains_lvdsVipMultiCamCapture_StopApp();
Int32 chains_lvdsVipMultiCamCapture_DeleteApp();

Int32 chains_bufLoop_StartApp(Void);
Int32 chains_bufLoop_StopApp(Void);
Int32 chains_bufLoop_DeleteApp(Void);
Void chains_bufLoop_InitSourceEpApp(struct vivi_sink *sink,
		struct vivi_source *source);
Int32 chains_bufLoop_CreateSourceEpApp(struct vivi_sink *sink,
		struct vivi_source *source, struct vivi_source_config *sourceCfg[]);

#ifdef ISS_INCLUDE
Int32 chains_csi2CalMultiCam_View_CreateApp(struct vivi_sink *sink,
		struct vivi_source *source);
Int32 chains_csi2CalMultiCam_View_StartApp();
Int32 chains_csi2CalMultiCam_View_StopApp();
Int32 chains_csi2CalMultiCam_View_DeleteApp();
#endif

#endif /* __PREVIEW_CHAIN_H__ */
