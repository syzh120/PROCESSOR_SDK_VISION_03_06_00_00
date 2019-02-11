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
#include <src/include/chains.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <src/rtos/iss/include/iss_sensors.h>

/*******************************************************************************
 *  Global's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Menu for system settings.
 *******************************************************************************
 */
 char gChains_menuSystemSettings[] = {
    "\r\n "
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
    "\r\n 1: Display Settings"
    "\r\n 2: Capture Settings"
    "\r\n 3: ISS Settings (TDA3x ONLY)"
    "\r\n 4: Enable Charging via USB2 Port (TDA2x EVM ONLY)"
    "\r\n 5: Print PRCM Statistics"
    "\r\n 6: Show Memory/CPU/DDR BW usage"
    "\r\n 7: Calibration Settings"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Menu for capture settings.
 *******************************************************************************
 */
char gChains_menuCaptureSrc[] = {
    "\r\n "
    "\r\n =============="
    "\r\n Capture Source"
    "\r\n =============="
    "\r\n "
    "\r\n 1: OV10635 Sensor 720P30"
    "\r\n 2: HDMI Capture 1080P60 (Not Supported in TDA2x/TDA2Ex Multi-serdes board)"
    "\r\n 3: OV10640 Sensor 720P30 - CSI2 (TDA3x ONLY)"
    "\r\n 4: OV10640 Sensor 720P30 - Parallel (TDA3x ONLY)"
    "\r\n 5: AR0132  Sensor 720P60 - Parallel (TDA3x ONLY)"
    "\r\n 6: AR0140  Sensor 720P60 - Parallel (TDA3x ONLY)"
    "\r\n 7: IMX224  Sensor 1280x960 - CSI2 (TDA3x ONLY)"
    "\r\n 8: AR0140  Sensor for SV - TIDA00262 (TDA3x ONLY)"
    "\r\n 9: OV10640 Sensor for SV - IMI (TDA3x ONLY)"
    "\r\n a: OV10635 Sensor for Mosaic Display - SAT0088/OV10635 (TDA2PX, TDA2EX & TDA3x)"
    "\r\n b: OV2775 Sensor 1080p30 (TDA3x ONLY)"
    "\r\n c: AR143 MARS Camera (TDA3x ONLY)"
    "\r\n d: Skip Sensor configuration "
    "\r\n e: OV2775 Sensor 1080p30 - TIDA001130"
    "\r\n f: IMX390 Sensor 1080p30 - D3"
    "\r\n g: OV10640 Sensor + OV490 ISP - IMI"
    "\r\n h: AR0233 RCCB UB953 - MARS"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char *gChain_captureSrcName[CHAINS_CAPTURE_SRC_MAX] =
{
    "Sensor OV10635 1280x720  @ 30fps - VIP, YUV422",
    "HDMI   RX      1280x720  @ 60fps - VIP, YUV422",
    "HDMI   RX      1920x1080 @ 60fps - VIP, YUV422",
    "Sensor AR0132  1280x720  @ 30fps - VIP, RCCC (TDA2x MonsterCam ONLY)",
    "Sensor AR0132  1280x720  @ 60fps - VIP, Bayer, Ext. ISP (TDA2x MonsterCam ONLY)",
    "Sensor OV10640 1280x720  @ 30fps - ISS CSI2, Bayer (TDA3x EVM ONLY)",
    "Sensor OV10640 1280x720  @ 30fps - ISS CPI , Bayer (TDA3x EVM ONLY)",
    "Sensor AR0132  1280x720  @ 60fps - ISS CPI , Bayer (TDA3x EVM ONLY)",
    "Sensor AR0132  1280x720  @ 60fps - ISS CPI , Monochrome (TDA3x EVM ONLY)",
    "Sensor AR0140  1280x800  @ 30fps - ISS CPI , Bayer (TDA3x EVM ONLY)",
    "Sensor IMX224  1280x960  @ 30fps - ISS CSI2, Bayer (TDA3x EVM ONLY)",
    "Sensor AR0132 DM388 1280x720 @ 60fps - VIP, YUV422 (TDA2x MonsterCam ONLY)",
    "Sensor AR0140 TIDA00262 1280x720 @ 30fps - ISS CSI2, Bayer (TDA3x EVM ONLY)",
    "Sensor OV10635 1280x720 @ 60fps - LVDS (TDA3x EVM ONLY)",
    "Sensor OV10640 IMI 1280x720 @ 30fps - ISS CSI2, Bayer (TDA3x EVM ONLY)",
    "Sensor SAT0088 (OV10635) @ 30fps - CAL CSI2, YUV422 (TDA2Ex EVM ONLY)",
    "CHAINS_CAPTURE_SRC_VIDDEC_TVP5158 , THIS ENTRY WAS MISSING BECAUSE OF A BUG)",
    "Sensor OV2775 1920x1080  @ 30fps - ISS CSI2, Bayer (TDA3x EVM ONLY)",
    "Sensor AR0143 MARS 1280x800 @ 30fps - ISS CSI2, Bayer (TDA3x EVM ONLY)",
    "Sensor IMX290",
    "Ethernet AVB Cam 1280x720 @ 30fps - (TDA2Ex ETH SRV BOARD ONLY)",
    "Sensor OV10640+OV490 IMI  1280x720  @ 30fps - VIP, Bayer"
    "Sensor AR0233 MARS 1920x1080 @ 30fps - ISS CSI2, RCCB (TDA3x RVP and TDA2Px EVM ONLY)",
};

extern char *gChain_displayTypeName[];
extern char gChains_menuIssSettings_0[];
Void Chains_showDisplaySettingsMenu();
Void Chains_showPMStatistics();

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */

char gChains_menuIssSettings_1[] = {
    "\r\n"
    "\r\n"
    "\r\n 1: Disable LDC and VTNF Mode"
    "\r\n 2: Enable LDC Only Mode"
    "\r\n 3: Enable VTNF Only Mode"
    "\r\n 4: Enable LDC and VTNF Mode"
    "\r\n 5: Enable Two Pass WDR"
    "\r\n 6: Enable Two Pass WDR Line Interleaved"
    "\r\n 7: Disable WDR"
    "\r\n 8: Enable One Pass WDR"
    "\r\n "
    "\r\n x: Exit"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuCalibrationSettings[] = {
    "\r\n "
    "\r\n ====================="
    "\r\n Calibration Settings"
    "\r\n ====================="
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: Binarization Settings "
    "\r\n 2: Corner Detection Settings "
    "\r\n 3: Pose Estimation Settings "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuBinarizationSettings[] = {
    "\r\n "
    "\r\n ======================"
    "\r\n Binarization Settings"
    "\r\n ======================"
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: White Bias (0.9) "
    "\r\n 2: No Bias (1.0) "
    "\r\n 3: Default Bias (1.1) "
    "\r\n 4: Black Bias 1 (1.15) "
    "\r\n 5: Black Bias 2 (1.25) "
    "\r\n "
    "\r\n 6: Small Window (50x50)"
    "\r\n 7: Large Window (75x75 Default) "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuCornerSettings[] = {
    "\r\n "
    "\r\n =========================="
    "\r\n Corner Detection Settings"
    "\r\n =========================="
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: Line Estimation RANSAC Off (Default) "
    "\r\n 2: Line Estimation RANSAC On "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuPoseSettings[] = {
    "\r\n "
    "\r\n =========================="
    "\r\n Pose Estimation Settings"
    "\r\n =========================="
    "\r\n "
    "\r\n 0: Exit "
    "\r\n "
    "\r\n 1: Pose Estimation RANSAC Off (Default) "
    "\r\n 2: Pose Estimation RANSAC On "
    "\r\n 3: Single Chart Pose Estimation Off (Default) "
    "\r\n 4: Single Chart Pose Estimation On "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

void Chains_showIssSettings()
{
    char *onOff[] = { "OFF", "ON" };
    char *wdr[] = {"OFF", "OnePass", "TwoPass", "TwoPass-LineInterleaved", "OFF"};

    Vps_printf(" ISS Settings   : LDC=[%s] VTNF=[%s] WDR=[%s] \n",
        onOff[gChains_usecaseCfg.issLdcEnable],
        onOff[gChains_usecaseCfg.issVtnfEnable],
        wdr[gChains_usecaseCfg.ispOpMode]
        );
}

/**
 *******************************************************************************
 *
 * \brief   Function to display select options using uart print message
 *
 *******************************************************************************
*/
Void Chains_showMainMenu(char *main_menu)
{
    char ipAddr1[20];
    char ipAddr2[20];

    /*Obtain the IP Addresses for both the interfaces*/
    Utils_netGetIpAddrStr(ipAddr1, 1);
    Utils_netGetIpAddrStr(ipAddr2, 2);

    Vps_printf(" \n");
    Vps_printf(" Current System Settings,\n");
    Vps_printf(" ========================\n");
    Vps_printf(" Display Type   : %s \n",
            gChain_displayTypeName[gChains_usecaseCfg.displayType]);

    UTILS_assert(gChains_usecaseCfg.captureSrc < CHAINS_CAPTURE_SRC_MAX);
    Vps_printf(" Capture Source : %s \n",
            gChain_captureSrcName[gChains_usecaseCfg.captureSrc]);
    Vps_printf(" My IP address for interface 1 : %s \n",
            ipAddr1 );
    Vps_printf(" My IP address for interface 2 : %s \n",
            ipAddr2 );
    Chains_showIssSettings();

    Vps_printf(" \n");
    Vps_printf(" ============\r\n");
    Vps_printf(" Usecase Menu\r\n");
    Vps_printf(" ============\r\n");

    Vps_printf(main_menu);
}

void Chains_showIssSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuIssSettings_0);
        Chains_showIssSettings();
        Vps_printf(gChains_menuIssSettings_1);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                gChains_usecaseCfg.issLdcEnable = 0;
                gChains_usecaseCfg.issVtnfEnable = 0;
                break;
            case '2':
                gChains_usecaseCfg.issLdcEnable = 1;
                gChains_usecaseCfg.issVtnfEnable = 0;
                break;
            case '3':
                gChains_usecaseCfg.issVtnfEnable = 1;
                gChains_usecaseCfg.issLdcEnable = 0;
                break;
            case '4':
                gChains_usecaseCfg.issVtnfEnable = 1;
                gChains_usecaseCfg.issLdcEnable = 1;
                break;
            case '5':
                gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_2PASS_WDR;
                break;
            case '6':
                gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED;
                break;
            case '7':
                gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
                break;
            case '8':
                gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_1PASS_WDR;
                break;
            case 'x':
            case 'X':
                done = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }

    }while(done == FALSE);

}

void Chains_showBinarizationSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuBinarizationSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 1;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 2;
            done = TRUE;
            break;
        case '3':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 0;
            done = TRUE;
            break;
        case '4':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 3;
            done = TRUE;
            break;
        case '5':
            gChains_usecaseCfg.calibrationParams.thresholdMode = 4;
            done = TRUE;
            break;
        case '6':
            gChains_usecaseCfg.calibrationParams.windowMode = 1;
            done = TRUE;
            break;
        case '7':
            gChains_usecaseCfg.calibrationParams.windowMode = 0;
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}

void Chains_showCornerDetectionSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuCornerSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            gChains_usecaseCfg.calibrationParams.Ransac = 0;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.calibrationParams.Ransac = 1;
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}

void Chains_showPoseDetectionSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuPoseSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            gChains_usecaseCfg.calibrationParams.PoseRansac = 0;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.calibrationParams.PoseRansac = 1;
            done = TRUE;
            break;
        case '3':
            gChains_usecaseCfg.calibrationParams.SingleChartPose = 0;
            done = TRUE;
            break;
        case '4':
            gChains_usecaseCfg.calibrationParams.SingleChartPose = 1;
            done = TRUE;
            break;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}

void Chains_showCalibrationSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuCalibrationSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '0':
            done = TRUE;
            break;
        case '1':
            Chains_showBinarizationSettingsMenu();
            done = TRUE;
            break;
        case '2':
            Chains_showCornerDetectionSettingsMenu();
            done = TRUE;
            break;
        case '3':
            Chains_showPoseDetectionSettingsMenu();
            done = TRUE;
        default:
            Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }

    } while (done == FALSE);

}


/**
 *******************************************************************************
 *
 * \brief   Function to set capture settings.
 *
 *******************************************************************************
*/
Void Chains_showCaptureSettingsMenu()
{
    char ch;
    Bool captSrcSelectDone;
    captSrcSelectDone = FALSE;
    Bsp_PlatformSocId socId;

    socId = Bsp_platformGetSocId();

    /* By Default sensor requires to be programmed */
    gChains_usecaseCfg.byPassSensorCfg = FALSE;
    do
    {
        Vps_printf(gChains_menuCaptureSrc);
        Vps_printf(" \r\n");
        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                captSrcSelectDone = TRUE;
                break;
            case '2':
                if(Bsp_platformIsTda2xxFamilyBuild() &&
                  (BSP_BOARD_MULTIDES == Bsp_boardGetId()))
                {
                    Vps_printf(" HDMI IN from SIL9127/ADV7611 NOT supported on TDA2xx/2Ex "
                    "when Multi-deserializer board is connected to VISION card\r\n");
                }
                else
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_HDMI_1080P;
                    captSrcSelectDone = TRUE;
                }
                break;
            case '3':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10640_CSI2;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_CSI2,
                        ISS_SENSORS_MAX_NAME);

                    captSrcSelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }
                break;
            case '4':
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }
                break;
            case '5':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_APTINA_AR0132,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }

                break;

            case '6':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc =
                        CHAINS_CAPTURE_SRC_AR0140BAYER_PARALLEL;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_APTINA_AR0140,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }
                break;
            case '7':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc =
                        CHAINS_CAPTURE_SRC_IMX224_CSI2;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_SONY_IMX224_CSI2,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }
                break;
            case '8':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_TIDA00262;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_APTINA_AR0140_TIDA262,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }
                break;
            case '9':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_IMI;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_IMI,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }
                break;

            case 'a':
            case 'A':
                if ((BSP_PLATFORM_SOC_ID_TDA2EX != socId) &&
                    (BSP_PLATFORM_SOC_ID_TDA3XX != socId) &&
                    (BSP_PLATFORM_SOC_ID_TDA2PX != socId))
                {
                    Vps_printf(" Supported only on TDA2Px, TDA2Ex & TDA3x EVM's \r\n");
                }
                else if (BSPUTILS_UB964_VERSION_ID !=
                                            BspUtils_appGetUb96xVersion(0U))
                {
                    Vps_printf(" Supported only on UB964 EVM's \r\n");
                    Vps_printf(" Please Refer User Guide (TDA2Ex, TDA3x, UB964) \r\n");
                }
                else
                {
                    gChains_usecaseCfg.captureSrc =
                                            CHAINS_CAPTURE_SRC_UB964_OV1063X;
                    captSrcSelectDone = TRUE;
                }
                break;
            case 'b':
            case 'B':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV2775_CSI2;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV2775_CSI2,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                    Vps_printf(" OV2775 Selected \r\n");
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }

                break;
            case 'c':
            case 'C':

                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_MARS_AR0143;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_APTINA_AR0143_MARS,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                    Vps_printf(" MARS AR0143 Selected \r\n");
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }

                break;
            case 'd':
            case 'D':
                /* Not mandated to set the capture source, setting it up to
                    default value */
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV10635;
                captSrcSelectDone = TRUE;
                gChains_usecaseCfg.byPassSensorCfg = TRUE;
                break;

            case 'e':
            case 'E':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV2775_TIDA1130,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                    Vps_printf(" TIDA1130 Sensor is Selected \r\n");
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }

                break;
            case 'f':
            case 'F':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_SONY_IMX390_UB953_D3,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                    Vps_printf(" D3-IMX390 Sensor is Selected \r\n");
                }
                else
                {
                    Vps_printf(" This sensor NOT supported on current platform\n");
                }

                break;
            case 'g':
            case 'G':
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV490;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_OMNIVISION_OV10640_OV490_IMI,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                    Vps_printf(" %s is Selected \r\n", SENSOR_OMNIVISION_OV10640_OV490_IMI);

                break;            
            case 'h':
            case 'H':
                if ((BSP_PLATFORM_SOC_ID_TDA2PX == socId) ||
                    (BSP_PLATFORM_SOC_ID_TDA3XX == socId))
                {
                    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_UB960_MARS_AR0233;
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_APTINA_AR0233_MARS,
                        ISS_SENSORS_MAX_NAME);
                    captSrcSelectDone = TRUE;
                    Vps_printf(" MARS AR0233 Selected \r\n");
                }
                else
                {
                    Vps_printf(" This sensor is NOT supported on current platform\n");
                }
                break;            

            case 'x':
            case 'X':
                captSrcSelectDone = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }

    }while(captSrcSelectDone == FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Function to select systems settings option.
 *
 *******************************************************************************
*/
Void Chains_showSystemSettingsMenu()
{
    char ch;
    Bool done;
    done = FALSE;

    do
    {
        Vps_printf(gChains_menuSystemSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                Chains_showDisplaySettingsMenu();
                done = TRUE;
                break;
            case '2':
                Chains_showCaptureSettingsMenu();
                done = TRUE;
                break;
            case '3':
                Chains_showIssSettingsMenu();
                done = TRUE;
            case '4':
                Board_enableUsbCharging();
                done = TRUE;
                break;
            case '5':
                Chains_showPMStatistics();
                done = TRUE;
                break;
            case '6':
                Utils_prcmPrintAllVDTempValues();
                Chains_memPrintHeapStatus();
                Chains_statCollectorPrint();
                Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
                Vps_printf(" CHAINS: Waiting for CPU load calculation to Complete !!!!\n");
                Task_sleep(2000);
                Vps_printf(" CHAINS: CPU load calculation to Complete !!!!\n");
                Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
                done = TRUE;
                break;
            case '7':
                Chains_showCalibrationSettingsMenu();
                done = TRUE;
                break;
            case 'x':
            case 'X':
                done = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }while(!done);
}

