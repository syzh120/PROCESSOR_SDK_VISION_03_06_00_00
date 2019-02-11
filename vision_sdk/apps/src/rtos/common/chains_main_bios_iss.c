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
#include <src/rtos/iss/include/iss_sensors.h>

char gChains_menuIssUsecases[] = {
    "\r\n "
    "\r\n ISS Usecases (TDA3x ONLY)"
    "\r\n ---------------------------"
#ifdef UC_iss_capture_isp_simcop_display
    "\r\n 1: 1CH ISS capture + ISS ISP + ISS LDC+VTNF + Display"
#endif
#ifdef UC_iss_mult_capture_isp_simcop_sv_tda3xx
    "\r\n 2: 4CH ISS capture + ISS ISP + Simcop + Surround View (DSP1) +  Display"
#endif
#ifdef UC_iss_monochrome_capt_isp_display
    "\r\n 3: 1CH ISS capture (AR0132) + ISS ISP Monochrome +  Display"
#endif
#ifdef UC_iss_mult_capture_isp_dewarp_3dsv_tda3xx
    "\r\n 4: 3D SRV 4CH ISS capture + ISS ISP + DeWarp + Synthesis (DSP1) + Display"
#endif
#ifdef UC_srv_calibration
    "\r\n 5: Surround View Calibration"
#endif
#ifdef UC_iss_mult_capture_isp_2d_3d_sv_tda3x
    "\r\n 6: 3D + 2D SRV 4CH ISS capture + ISS ISP + DeWarp + Synthesis (DSP1) + Display"
#endif
#ifdef UC_iss_mult_capture_isp_dewarp_3dsv_rearview_tda3xx
    "\r\n 7: 3D SRV 4CH ISS capture + ISS ISP + DeWarp + Synthesis (DSP1) + RearView + Display"
#endif
#ifdef UC_iss_mult_capture_isp_simcop_stereo_tda3xx
    "\r\n 8: Stereo capture + ISS ISP + Simcop + Display"
#endif
#ifdef UC_iss_mult_capture_isp_dewarp_stereo_tda3xx
    "\r\n 9: Stereo capture + ISS ISP + Dewarp + Display"
#endif
#ifdef UC_iss_mult_capture_isp_stereo_autocalib_tda3xx
    "\r\n a: Stereo catpure + ISS ISP + Auto Calibration"
#endif
#ifdef UC_iss_mult_capture_isp_dewarp_stereoplus_tda3xx
    "\r\n b: Stereo capture + ISS ISP + Dewarp + Streaming + Display"
#endif
#ifdef UC_iss_multi_inst_capture_display
    "\r\n c: 4 Channel (2 ch per CSI2 Inst) ISS Capture (OV2775 Sensor) Display"
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
Void Chains_menuIssRun()
{
    char ch;
    Bool done = FALSE;
    Bsp_PlatformSocId socId;

    socId = Bsp_platformGetSocId();
    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuIssUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        if ((BSP_PLATFORM_SOC_ID_TDA2PX != socId) &&
            (BSP_PLATFORM_SOC_ID_TDA3XX != socId))
        {
            Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform \n");

            if ((ch == 'x') || (ch == 'X'))
            {
                done = TRUE;
            }
        }
        else
        {
            switch(ch)
            {
                #ifdef UC_iss_capture_isp_simcop_display
                case '1':
                    Chains_issIspSimcop_Display(&gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_simcop_sv_tda3xx
                case '2':
                    Chains_issMultCaptIspDewarp3dSv_Display(
                                            &gChains_usecaseCfg,
                                            ALGORITHM_LINK_SRV_OUTPUT_2D_LDC);
                    break;
                #endif
                #ifdef UC_iss_monochrome_capt_isp_display
                case '3':
                    strncpy(gChains_usecaseCfg.sensorName,
                        SENSOR_APTINA_AR0132, ISS_SENSORS_MAX_NAME);
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL;
                    Chains_monochrome_issIsp_Display(&gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_dewarp_3dsv_tda3xx
                case '4':
                    Chains_issMultCaptIspDewarp3dSv_Display(
                                            &gChains_usecaseCfg,
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC);
                    break;
                #endif
                #ifdef UC_srv_calibration
                case '5':
                    chains_srvCalibration_Display(
                                            &gChains_usecaseCfg,
                                            CHAINS_CAPTURE_INTF_ISS);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_2d_3d_sv_tda3x
                case '6':
                    Chains_issMultCaptIsp2d3d3dSv_Display(
                                                        &gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_dewarp_3dsv_rearview_tda3xx
                case '7':
                    Chains_issMultCaptIspDeWarpRearView3dSv_Display(
                                                        &gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_simcop_stereo_tda3xx
                case '8':
                    gChains_usecaseCfg.issLdcEnable = TRUE;
                    gChains_usecaseCfg.issVtnfEnable = FALSE;

                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_IMI,
                        ISS_SENSORS_MAX_NAME);

                    Chains_issMultCaptIspSimcop_Stereo(&gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_dewarp_stereo_tda3xx
                case '9':
                    gChains_usecaseCfg.issLdcEnable = TRUE;
                    gChains_usecaseCfg.issVtnfEnable = FALSE;

                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_IMI,
                        ISS_SENSORS_MAX_NAME);

                    Chains_issMultCaptIspDeWarp_Stereo(&gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_stereo_autocalib_tda3xx
                case 'a':
                case 'A':
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_IMI,
                        ISS_SENSORS_MAX_NAME);
                    Chains_issMultCaptSteroAutoCalib(&gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_mult_capture_isp_dewarp_stereoplus_tda3xx
                case 'b':
                case 'B':
                    gChains_usecaseCfg.issLdcEnable = TRUE;
                    gChains_usecaseCfg.issVtnfEnable = FALSE;

                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_IMI,
                        ISS_SENSORS_MAX_NAME);

                    Chains_issMultCaptIspDeWarp_StereoPlus(&gChains_usecaseCfg);
                    break;
                #endif
                #ifdef UC_iss_multi_inst_capture_display
                case 'C':
                case 'c':
                    Chains_iss_multi_inst_capture_display(&gChains_usecaseCfg);
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

}

