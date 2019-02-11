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
#include <system_cfg.h>
#include <src/hlos/adas/include/chains.h>

/**
 *******************************************************************************
 * \brief Multi camera UC Menu
 *******************************************************************************
 */

char gChains_menuMultiCameraLvdsUsecases[] = {
    "\r\n "
    "\r\n Multi-Camera LVDS Usecases"
    "\r\n ----------------------------"
#ifdef UC_lvds_vip_multi_cam_view_sgx_display
    "\r\n 1: 4CH VIP LVDS capture + SGX MOSAIC + DISPLAY"
#endif
#ifdef UC_lvds_vip_multi_cam_vpe_enc_null
    "\r\n 2: 4CH VIP LVDS capture + Scale + Encode + Null (file dump)"
#endif
#ifdef UC_lvds_vip_multi_cam_3d_srv
    "\r\n 3: 4CH VIP LVDS capture + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_lvds_vip_multi_cam_2mp_3d_srv
    "\r\n 4: 4CH VIP LVDS 2MP capture + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_lvds_vip_multi_cam_3d_perception
    "\r\n 5: 4CH VIP LVDS capture + 3D SRV + 4CH SfM (3D perception demo - EVE1-4/DSP1&2) + DISPLAY - Only on TDA2xx with HDMI 1080p display"
#endif
#ifdef UC_ov490_vip_multi_cam_3d_srv
    "\r\n 6: 2CH OV490 2560x720 capture + Split + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_srv_calibration
    "\r\n 7: Surround View Calibration"
    "\r\n 8: CSI2 CAL Surround View Calibration"
#endif
#ifdef UC_lvds_vip_multi_cam_3d_adaptive_srv
    "\r\n 9: 4CH VIP LVDS capture + Adaptive 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_csi2Cal_multi_cam_view
    "\r\n a: 4CH CSI2 CAL capture + SgxFrmCpy + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_csi2Cal_multi_cam_3d_srv
    "\r\n b: 4CH CSI2 CAL capture + 3D SRV (SGX/A15) + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_csi2Cal_multi_cam_3d_srv_cbb
    "\r\n c: 4CH CSI2 CAL capture + 3D SRV (SGX/A15) + Car Black Box + DISPLAY - Only HDMI 1080p display supported"
#endif
#ifdef UC_lvds_vip_single_cam_view_sgx_display
    "\r\n d: 1CH VIP LVDS capture + SGX MOSAIC + DISPLAY"
#endif
#ifdef UC_lvds_vip_multi_cam_8ch_sgx_display
    "\r\n e: 8CH VIP LVDS capture + SGX/DRM MOSAIC DISPLAY(A15)"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/
Void Chains_menuMultiCameraLvdsRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuMultiCameraLvdsUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_lvds_vip_multi_cam_view_sgx_display
            case '1':
                gChains_usecaseCfg.numLvdsCh = 4;
                chains_lvdsVipMultiCam_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_vpe_enc_null
            case '2':
                gChains_usecaseCfg.numLvdsCh = 4;
                chains_lvdsVipMultiCam_vpeEncNull(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_3d_srv
            case '3':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_lvdsVipMultiCam_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_2mp_3d_srv
            case '4':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_IMX290ISP;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_lvdsVipMultiCam2mp_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_3d_perception
            case '5':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                chains_lvdsVipMultiCam_3d_perception(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_ov490_vip_multi_cam_3d_srv
            case '6':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_ov490VipMultiCam_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_srv_calibration
            case '7':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_VIP);
                break;
            case '8':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_CSI2CAL);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_3d_adaptive_srv
            case '9':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_lvdsVipMultiCam_Sgx3D_adaptive_srv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_csi2Cal_multi_cam_view
            case 'a':
            case 'A':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                chains_csi2CalMultiCam_View(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_csi2Cal_multi_cam_3d_srv
            case 'b':
            case 'B':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_csi2CalMultiCam_Sgx3Dsrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_csi2Cal_multi_cam_3d_srv_cbb
            case 'c':
            case 'C':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_csi2CalMultiCam_Sgx3Dsrv_carBlackBox(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_single_cam_view_sgx_display
            case 'd':
            case 'D':
                gChains_usecaseCfg.numLvdsCh = 1;
                chains_lvdsVipSingleCam_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_lvds_vip_multi_cam_8ch_sgx_display
            case 'e':
            case 'E':
                gChains_usecaseCfg.numLvdsCh = 8;
                chains_lvdsVipMultiCam_8ch_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            case 'x':
            case 'X':
                done = TRUE;
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

