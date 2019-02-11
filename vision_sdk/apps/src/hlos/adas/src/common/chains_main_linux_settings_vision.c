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
    "\r\n 3: Calibration Settings"
    "\r\n 4: ISS Settings"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Menu for display settings.
 *******************************************************************************
 */
char gChains_menuDisplaySettings[] = {
    "\r\n "
    "\r\n ================"
    "\r\n Display Settings"
    "\r\n ================"
    "\r\n "
#if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD)
    "\r\n 1: LCD  10-inch 1280x720@60fps"
#endif
    "\r\n 2: HDMI 1080P60 "
#ifdef FPD_DISPLAY
    "\r\n 3: FPD Out "
#endif
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
    "\r\n 2: HDMI Capture 1080P60 "
    "\r\n 3: OV10640 CSI2 Sensor 1280x720 (Only on TDA3xx/TDA2px)"
    "\r\n 4: OV10640 IMI Sennsor 1280x720 (Only on TDA3xx/TDA2px)"
    "\r\n 5: OV2775 CSI2 Sensor (Only on TDA3xx/TDA2px)"
    "\r\n 6: D3 IMX390 CSI2 Sensor on Fusion Platform (Only on TDA2px)"
    "\r\n 7: OV2775 TIDA1130 Sensor on Fusion Platform (Only on TDA2px)"
    "\r\n 8: AR143 MARS Camera (Only on TDA3xx/TDA2px)"
    "\n\n 9: OV490 Capture"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
*******************************************************************************
* \brief Menu for automatic calibration settings.
*******************************************************************************
*/

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

/**
 *******************************************************************************
 * \brief Menu for ISS settings.
 *******************************************************************************
 */
char gChains_menuISSSettings[] = {
    "\r\n "
    "\r\n ================"
    "\r\n ISS Settings"
    "\r\n ================"
    "\r\n "
    "\r\n 1: Enable Linear Mode"
    "\r\n 2: Enable Two Pass WDR Mode"
    "\r\n 3: Enable Single Pass WDR Mode"
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
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Run Time Menu string for 3D SRV.
 *******************************************************************************
 */
char gChains_3DSrvRunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n c: Change Camera "
    "\r\n a: Change Angle "
    "\r\n t: Change Target "
    "\r\n i: Increase in c, a or t"
    "\r\n d: Decrease in c, a or t"
    "\r\n x: Modify X position by delta "
    "\r\n y: Modify Y position by delta "
    "\r\n z: Modify Z position by delta "
    "\r\n m: increase delta, or more change "
    "\r\n l: decrease delta or less change "
    "\r\n 1: Preset view 0 "
    "\r\n 2: Preset view 1 "
    "\r\n 3: Preset view 2 "
    "\r\n b: Turn bowl view on/off "
    "\r\n v: Turn car view on/off "
    "\r\n j: Turn Animation On "
    "\r\n k: Turn Animation Off "
    "\r\n n: Change Render mode "
    "\r\n w: Change car "
    "\r\n "
    "\r\n 4: Control bowl depth"
    "\r\n o: Stop bowl change"
    "\r\n s: Re-start bowl change (running by default)"
    "\r\n "
    "\r\n To make changes follow the below sequence:"
    "\r\n First select c , a or t. Then select i or d. Then select x, y or z."
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Function to set display settings.
 *
 *******************************************************************************
*/

void Chains_showDisplaySettingsMenu()
{
    char ch;
    Bool displaySelectDone;
    displaySelectDone = FALSE;

    do
    {
        Vps_printf(gChains_menuDisplaySettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_LCD_10_INCH;
                displaySelectDone = TRUE;
                break;
            case '2':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                displaySelectDone = TRUE;
                break;
            #ifdef FPD_DISPLAY
            case '3':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_FPD;
                displaySelectDone = TRUE;
                break;
            #endif
            case 'x':
            case 'X':
                displaySelectDone = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }

    }while(displaySelectDone == FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Function to set capture settings.
 *
 *******************************************************************************
*/

void Chains_showCaptureSettingsMenu()
{
    char ch;
    Bool captSrcSelectDone;
    captSrcSelectDone = FALSE;

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
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_HDMI_1080P;
                captSrcSelectDone = TRUE;
                break;
            case '3':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_OMNIVISION_OV10640_CSI2,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '4':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_OMNIVISION_OV10640_IMI,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '5':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_OMNIVISION_OV2775_CSI2,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '6':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_SONY_IMX390_UB953_D3,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '7':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_OMNIVISION_OV2775_TIDA1130,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '8':
                strncpy(gChains_usecaseCfg.sensorName,
                    SENSOR_APTINA_AR0143_MARS,
                    ISS_SENSORS_MAX_NAME);
                captSrcSelectDone = TRUE;
                break;
            case '9':
                gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_OV490;
                captSrcSelectDone = TRUE;
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
* \brief Menu for autocalibration settings.
*******************************************************************************
*/
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
* \brief Menu for ISS settings.
*******************************************************************************
*/
void Chains_showISSSettingsMenu()
{
    char ch;
    int done = FALSE;

    do
    {
        Vps_printf(gChains_menuISSSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch (ch)
        {
        case '1':
            gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
            done = TRUE;
            break;
        case '2':
            gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_2PASS_WDR;
            done = TRUE;
            break;
        case '3':
            gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_1PASS_WDR;
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

    } while (done == FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection
 *
 *          This functions displays the run time options available
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char Chains_menuRunTime()
{
    Vps_printf(gChains_runTimeMenu);

    return Chains_readChar();
}

/**
 *******************************************************************************
 *
 * \brief   Run time Menu selection for 3D SRV
 *
 *          This functions displays the run time options available for 3D SRV
 *          And receives user input and calls corrosponding functions run time
 *          Instrumentation logs are printing routine is called in same function
 *
 *******************************************************************************
*/
char Chains_menu3DSrvRunTime()
{
    Vps_printf(gChains_3DSrvRunTimeMenu);

    return Chains_readChar();
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
                Chains_showCalibrationSettingsMenu();
                done = TRUE;
                break;
            case '4':
                Chains_showISSSettingsMenu();
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

#ifdef OPENVX_INCLUDE
char vx_tutorial_get_char()
{
    return getchar();
}
#endif

