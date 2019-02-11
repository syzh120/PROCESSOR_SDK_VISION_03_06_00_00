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
#include <src/include/chains.h>

char gChains_menuMultiCameraLvdsUsecases[] = {
    "\r\n "
    "\r\n Multi-Camera LVDS Usecases"
    "\r\n ----------------------------"
#if defined(UC_lvds_vip_multi_cam_view) || defined(UC_lvds_vip_multi_cam_view_tda3xx)
    "\r\n 1: 4CH VIP Capture + Mosaic Display "
#endif
#ifdef UC_lvds_vip_sv_standalone
    "\r\n 2: 4CH VIP Capture + Surround View (DSP) + Display (HDMI)"
#endif
#ifdef UC_lvds_vip_sv_analytics_us
    "\r\n 3: 5CH VIP Capture + Surround View (DSPx) + Analytics (DSP/EVE) + Ultrasound (DSPx) + HDMI Display (HDMI) (TDA2x ONLY)"
#endif
#ifdef UC_lvds_vip_sv_tda3xx
    "\r\n 4: 4CH VIP Capture + Surround View (DSP) + Display (HDMI) (TDA3x only)"
#endif
#ifdef UC_ov490_vip_sv_standalone
    "\r\n 5: 2CH VIP Capture (2560x720) + Surround View (DSPx) + Display (TDA2x + TIDA0455 only)"
#endif
#ifdef UC_srv_calibration
    "\r\n 6: Surround View Calibration"
#endif
#ifdef UC_csi2_cal_multi_cam_view
    "\r\n 7: OV10635 & UB964 4CH CSI2 Capture + Display "
#endif
#ifdef UC_csi2_cal_sv_standalone
    "\r\n 8: OV10635 & UB964 4CH CSI2 Surround View (DSP) + Display (HDMI)"
#endif
#ifdef UC_lvds_vip_single_cam_view
    "\r\n 9: 1CH LVDS capture +  Display + NetworkRx"
#endif
#ifdef UC_lvds_vip_8_cam_view
    "\r\n a: 8CH VIP Capture + Mosaic Display (HDMI)"
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
    Chains_Ctrl usecaseCfg;
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuMultiCameraLvdsUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #if defined(UC_lvds_vip_multi_cam_view) || defined(UC_lvds_vip_multi_cam_view_tda3xx)
            case '1':
                if ((Bsp_platformIsTda2xxFamilyBuild()) ||
                    (Bsp_platformIsTda3xxFamilyBuild()))
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.algProcId = System_getSelfProcId();
                        gChains_usecaseCfg.numLvdsCh = VIDEO_SENSOR_NUM_LVDS_CAMERAS;
                        usecaseCfg = gChains_usecaseCfg;
                        if( usecaseCfg.captureSrc != CHAINS_CAPTURE_SRC_OV10635 && 
                            usecaseCfg.captureSrc != CHAINS_CAPTURE_SRC_OV490)
                        {
                            Vps_printf(" ### ONLY OV10635 and OV10640+OV490 Sensors supported for this usecase ");
                            Vps_printf(" ### Please choose OV10635 or OV10640+OV490 as Capture Source using option 's'\n");
                            break;
                        }
                        #ifdef UC_lvds_vip_multi_cam_view
                        if (Bsp_platformIsTda2xxFamilyBuild())
                        {
                            Chains_lvdsVipMultiCam_Display(&gChains_usecaseCfg);
                        }
                        #endif
                        #ifdef UC_lvds_vip_multi_cam_view_tda3xx
                        if(Bsp_platformIsTda3xxFamilyBuild())
                        {
                            Chains_lvdsVipMultiCam_Display_tda3xx(&gChains_usecaseCfg);
                        }
                        #endif
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase. MulitDes Board Not Connected \n");
                    }
                }
                break;
            #endif
            #ifdef UC_lvds_vip_sv_standalone
            case '2':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.numLvdsCh = 4;
                        gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_2D;
                        gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                        usecaseCfg = gChains_usecaseCfg;
                        if( usecaseCfg.displayType != CHAINS_DISPLAY_TYPE_HDMI_1080P )
                        {
                            Vps_printf("  ### ONLY HDMI 1080p Display supported for this usecase ");
                            Vps_printf("Please choose HDMI Display Type using option 's'\n");
                            break;
                        }
                        if( usecaseCfg.captureSrc != CHAINS_CAPTURE_SRC_OV10635 &&
                            usecaseCfg.captureSrc != CHAINS_CAPTURE_SRC_OV490)
                        {
                            Vps_printf(" ### ONLY OV10635 and OV10640+OV490 Sensors supported for this usecase ");
                            Vps_printf(" ### Please choose OV10635 or OV10640+OV490 as Capture Source using option 's'\n");
                            break;
                        }

                        Chains_lvdsVipSurroundViewStandalone(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase.  MulitDes Board Not Connected \n");
                    }
                }
                break;
            #endif
            #ifdef UC_lvds_vip_sv_analytics_us
            case '3':
                #ifdef ULTRASONIC_INCLUDE
                if(Bsp_platformIsTda2xxFamilyBuild() && (BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId()))
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.numLvdsCh = 5;
                        gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_2D;
                        gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                        usecaseCfg = gChains_usecaseCfg;
                        if( usecaseCfg.displayType != CHAINS_DISPLAY_TYPE_HDMI_1080P )
                        {
                            Vps_printf("  ### ONLY HDMI 1080p Display supported for this usecase ");
                            Vps_printf("Please choose HDMI Display Type using option 's'\n");
                            break;
                        }
                        if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_OV10635 )
                        {
                            Vps_printf(" ### ONLY OV10635 Sensor supported for this usecase ");
                            Vps_printf(" ### Please choose OV10635 as Capture Source using option 's'\n");
                            break;
                        }

                        Chains_lvdsVipSurroundViewAnalyticsUltrasound(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase. MulitDes Board Not Connected \n");
                    }
                }
                #else
                        Vps_printf(" ### Cannot run usecase. ULTRASONIC_INCLUDE not enabled in cfg.mk \n");
                #endif
                break;
            #endif
            #ifdef UC_lvds_vip_sv_tda3xx
            case '4' :
                if (Bsp_platformIsTda3xxFamilyBuild())
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.algProcId = System_getSelfProcId();
                        gChains_usecaseCfg.numLvdsCh = VIDEO_SENSOR_NUM_LVDS_CAMERAS;
                        usecaseCfg = gChains_usecaseCfg;
                        Chains_lvdsVipSurroundView(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase. MulitDes Board Not Connected \n");
                    }
                }
                break;
            #endif
            #ifdef UC_ov490_vip_sv_standalone
            case '5':
                {
                    Chains_CaptureSrc srcBkp = gChains_usecaseCfg.captureSrc;
                    /* Set capture src to MAX to bypass sensor driver */
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_MAX;
                    Chains_ov490VipSurroundViewStandalone(&gChains_usecaseCfg);
                    /* Revert capture src to original value */
                    gChains_usecaseCfg.captureSrc = srcBkp;
                }
                break;
            #endif
            #ifdef UC_srv_calibration
            case '6':
                if(CHAINS_CAPTURE_SRC_UB964_OV1063X == gChains_usecaseCfg.captureSrc)
                {
                    chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_CSI2CAL);
                }
                else
                {
                    chains_srvCalibration_Display(
                                    &gChains_usecaseCfg,
                                    CHAINS_CAPTURE_INTF_VIP);
                }
                break;
            #endif
            #ifdef UC_csi2_cal_multi_cam_view
            case '7':
                Chains_csi2CalMultiCam(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_csi2_cal_sv_standalone
            case '8':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_2D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                Chains_csi2CalSVStandalone(&gChains_usecaseCfg);
                break;
            #endif
        
            #ifdef UC_lvds_vip_single_cam_view
            case '9':
                gChains_usecaseCfg.numLvdsCh = 1;
                Chains_lvdsVipSingleCam_Display(&gChains_usecaseCfg);
                break;
            #endif

            #ifdef UC_lvds_vip_8_cam_view
            case 'a':
            case 'A':
                gChains_usecaseCfg.numLvdsCh = 8;
                Chains_lvdsVip8Cam_Display(&gChains_usecaseCfg);
                break;
            #endif

            case 'x':
            case 'X':
                done = TRUE;
                usecaseCfg = usecaseCfg; /* to avoid unused variable warning */
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

