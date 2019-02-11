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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/iss_sensors.h>

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */
Void Chains_showMainMenu(char *main_menu);
Void Chains_showSystemSettingsMenu();
Void Chains_menuSingleCameraRun();
Void Chains_menuMultiCameraLvdsRun();
Void Chains_menuAvbRxRun();
Void Chains_menuDualDisplayRun();
Void Chains_menuIssRun();
Void Chains_menuStereoRun();
Void Chains_menuNetworkRxTxRun();
Void Chains_menuMiscTestRun();
Void Chains_menuOpenCLRun();
Void Chains_menuOpenVXRun();
Void Chains_menuRearViewPanoramaRun();
Void Chains_menuTIDLRun();
Void Chains_menuCamRadarComboRun();

Chains_Ctrl gChains_usecaseCfg;

/**
 *******************************************************************************
 * \brief Menu setting display string.
 *******************************************************************************
 */
char gChains_menuUseCases[] = {
    "\r\n "
    "\r\n Vision SDK Usecases,"
    "\r\n -------------------- "
    "\r\n 1: Single Camera Usecases"
    "\r\n 2: Multi-Camera LVDS Usecases"
    "\r\n 3: AVB RX Usecases, (TDA2x & TDA2Ex ONLY)"
    "\r\n 4: Dual Display Usecases, (TDA2x EVM ONLY)"
    "\r\n 5: ISS Usecases, (TDA3x ONLY)"
    "\r\n 6: TDA2x Stereo Usecases "
    #ifdef UC_network_rx_tx
    "\r\n 7: Network RX/TX Usecases"
    #endif
    "\r\n 9: RADAR Usecases"
    "\r\n a: Miscellaneous test's"
    #ifdef OPENCL_INCLUDE
    "\r\n b: OPENCL Usecases (TDA2x EVM ONLY)"
    #endif
    #ifdef OPENVX_INCLUDE
    "\r\n c: OPENVX Usecases"
    #endif
    #if defined(UC_rear_view_panorama_tda3xx)
    "\r\n d: Rear View Panorama Use-cases"
    #endif
    #ifdef BUILD_ADAM_CAR
    "\r\n e: ADAM Car Use-cases"
    #endif
    "\r\n f: TIDL Usecase"
    "\r\n g: Camera Radar Combo Usecases"
    "\r\n "
    "\r\n s: System Settings "
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n 1: Change Display Channel (Support 4CH LVDS + Mosaic use-case only)"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Main call for usecase selection and configuration
 *
 *          Chains_main is called form the main of main_ipu1_0.c .
 *          This is the entry point for usecase selection.
 *          Board, UART LCD initializations and demo selections are performed.
 *          It waits in a while loop till the end of demo/usecase is triggred
 *
 * \param   arg0    [IN]  default args
 *
 * \param   arg1    [IN]  default args
 *
 *******************************************************************************
*/
Void Chains_main(UArg arg0, UArg arg1)
{

    ChainsCommon_Init();
    Chains_Ctrl_Init(&gChains_usecaseCfg);

#if defined(TDA2EX_ETHSRV_BOARD)
    /*
     * For ETH SRV Board camera power is on by default, so turn it off.
     * Use-cases enable camera power in start function.
     */
    ChainsCommon_StopCaptureDevice( CHAINS_CAPTURE_SRC_TRULY_AVB_CAM );
#endif

    #ifdef TDA3XX_FAMILY_BUILD
    #ifdef UC_fast_boot_iss_capture_isp_simcop_pd_display
    if(System_isFastBootEnabled())
    {
        gChains_usecaseCfg.displayType   = CHAINS_DISPLAY_TYPE_LCD_10_INCH;
        gChains_usecaseCfg.captureSrc    = CHAINS_CAPTURE_SRC_AR0140BAYER_PARALLEL;
        gChains_usecaseCfg.ispOpMode     = ISSM2MISP_LINK_OPMODE_2PASS_WDR;
        gChains_usecaseCfg.issLdcEnable  = 0;
        gChains_usecaseCfg.issVtnfEnable = 0;

        if(Bsp_platformIsTda3xxFamilyBuild())
        {
            Chains_fastBootIssIspSimcop_pd_Display(&gChains_usecaseCfg);
        }
        else
        {
            Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform or "
                       "     Check FAST_BOOT_INCLUDE in Rules.make \n");
        }
    }
    else if (System_isSrvFastBootEnabled())
    {
        gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
        strncpy(
            gChains_usecaseCfg.sensorName,
            SENSOR_OMNIVISION_OV10640_IMI,
            ISS_SENSORS_MAX_NAME);
        Chains_issMultCaptIspDewarp3dSv_Display(
                                            &gChains_usecaseCfg,
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC);
    }
    else
    #elif defined(UC_iss_mult_capture_isp_dewarp_3dsv_tda3xx)
    if (System_isSrvFastBootEnabled())
    {
        gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
        strncpy(
            gChains_usecaseCfg.sensorName,
            SENSOR_OMNIVISION_OV10640_IMI,
            ISS_SENSORS_MAX_NAME);
        Chains_issMultCaptIspDewarp3dSv_Display(
                                            &gChains_usecaseCfg,
                                            ALGORITHM_LINK_SRV_OUTPUT_3D_LDC);
    }
    else
    #endif
    #endif
    {
        #ifdef CHAINS_DISABLE_GET_CHAR
        Chains_menuMainRun('n');
        #endif
        {
            char ch;
            Bool done;

            done = FALSE;

            while(!done)
            {
                Chains_showMainMenu(gChains_menuUseCases);

                ch = Chains_readChar();

                Vps_printf(" \r\n");

                switch(ch)
                {
                    case '1':
                        Chains_menuSingleCameraRun();
                        break;
                    case '2':
                        Chains_menuMultiCameraLvdsRun();
                        break;
                    #ifdef AVB_INCLUDE
                    case '3':
                    if(Utils_netIsNetworkEnabled())
                    {
                        Chains_menuAvbRxRun();
                    }
                    else
                    {
                        Vps_printf(" ### Networking NOT enabled in build, Rebuild \
                               binaries  with NDK_PROC_TO_USE=<proc name> in Rules.make \n");
                    }
                    break;
                    #endif
                    case '4':
                        Chains_menuDualDisplayRun();
                        break;
                    case '5':
                        Chains_menuIssRun();
                        break;
                    case '6':
                        Chains_menuStereoRun();
                        break;
                    #ifdef UC_network_rx_tx
                    case '7':
                        Chains_menuNetworkRxTxRun();
                        break;
                    #endif
                    case '9':
                        {
                            Void Chains_radarMain(Chains_Ctrl *chainsCfg);

                            Chains_radarMain(&gChains_usecaseCfg);
                        }
                        break;

                    case 'a':
                        Chains_menuMiscTestRun();
                        break;
                    #ifdef OPENCL_INCLUDE
                    case 'b':
                        Chains_menuOpenCLRun();
                        break;
                    #endif
                    #ifdef OPENVX_INCLUDE
                    case 'c':
                    case 'C':
                        Chains_menuOpenVXRun();
                        break;
                    #endif
                    #if defined(UC_rear_view_panorama_tda3xx)
                    case 'd':
                        Chains_menuRearViewPanoramaRun();
                        break;
                    #endif
                    #ifdef BUILD_ADAM_CAR
                    case 'e':
                        {
                            Void Chains_adamCarDemoMain(Chains_Ctrl *chainsCfg);
                            Chains_adamCarDemoMain(&gChains_usecaseCfg);
                        }
                        break;
                    #endif
                    case 'f':
                    case 'F':
                        Chains_menuTIDLRun();
                        break;
                    case 'g':
                    case 'G':
                        Chains_menuCamRadarComboRun();
                        break;
                    case 's':
                    case 'S':
                        Chains_showSystemSettingsMenu();
                        break;

                    case 'x':
                    case 'X':
                        done = TRUE;
                        break;
                }
            }
        }
    }

    ChainsCommon_DeInit();
}

