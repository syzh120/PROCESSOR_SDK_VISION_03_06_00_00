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

/*******************************************************************************
 *  Global's
 *******************************************************************************
 */

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
    "\r\n 1: LCD  7-inch 800x480@60fps"
    "\r\n 2: LCD  10-inch 1280x720@60fps"
    "\r\n 3: HDMI 1080P60 "
    "\r\n 4: HDMI 720P60 "
    "\r\n 5: SDTV NTSC "
    "\r\n 6: SDTV PAL "
    "\r\n 7: HDMI XGA TDM mode (TDA3x ONLY) "
    "\r\n 8: LCD  10-inch 1920x1200@60fps"
    "\r\n 9: HDMI WXGA mode (TDA3x ONLY) "
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


char *gChain_displayTypeName[] =
{
    "LCD   800x480  @ 60fps (7-inch)",
    "LCD  1280x720  @ 60fps (10-inch)",
    "HDMI 1280x720  @ 60fps",
    "HDMI 1920x1080 @ 60fps",
    "SDTV NTSC 720x480i @ 60fps",
    "SDTV PAL  720x576i @ 60fps",
    "XGA 1024x768 @ 60fps - (TDA3x ONLY - using TDM Mode)",
    "LCD 10-inch 1920x1200@60fps",
    "WXGA 1280x800 @ 60fps - (TDA3x ONLY)",
};

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_runTimePMMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains PRCM Stats Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 1: Show  Dpll Status "
    "\r\n 2: Show  Temperature "
    "\r\n 3: Show  Voltages "
    "\r\n 4: Show  Module Power State "
    "\r\n 5: Show  CPU Frequency "
    "\r\n 6: Show  Peripherals Frequency "
    "\r\n 7: Dump  Prcm Register Data "
    "\r\n 8: Show  Power Consumption (valid only for TDA2xx)"
    "\r\n 9: Print All PRCM Stats"
    "\r\n "
    "\r\n x: To Exit out of menu "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuIssSettings_0[] = {
    "\r\n "
    "\r\n ============"
    "\r\n ISS Settings"
    "\r\n ============"
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Print PM Statistics
 *
 *******************************************************************************
*/
Void Chains_showPMStatistics()
{
    char ch;
    UInt32 done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_runTimePMMenu);
        ch = Chains_readChar();

        switch(ch)
        {
            case '1':
                Utils_prcmPrintAllDpllValues();
                break;
            case '2':
                Utils_prcmPrintAllVDTempValues();
                break;
            case '3':
                Utils_prcmPrintAllVoltageValues();
                break;
            case '4':
                Utils_prcmPrintAllModuleState();
                break;
            case '5':
                Utils_prcmPrintAllCPUFrequency();
                break;
            case '6':
                Utils_prcmPrintAllPeripheralsFrequency();
                break;
            case '7':
                Utils_prcmDumpRegisterData();
                break;
            case '8':
                Utils_prcmPrintPowerConsumption();
                break;
            case '9':
                Utils_prcmPrintAllDpllValues();
                Task_sleep(100);
                Utils_prcmPrintAllVDTempValues();
                Utils_prcmPrintAllVoltageValues();
                Task_sleep(100);
                Utils_prcmPrintAllModuleState();
                Task_sleep(100);
                Utils_prcmPrintAllCPUFrequency();
                Task_sleep(100);
                Utils_prcmPrintAllPeripheralsFrequency();
                Utils_prcmDumpRegisterData();
                Task_sleep(100);
                done = TRUE;
                break;
            case 'x':
                done = TRUE;
                break;
            default:
                    Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
            break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to set display settings.
 *
 *******************************************************************************
*/
Void Chains_showDisplaySettingsMenu()
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
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_LCD_7_INCH;
                displaySelectDone = TRUE;
                break;
            case '2':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_LCD_10_INCH;
                displaySelectDone = TRUE;
                break;
            case '3':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                displaySelectDone = TRUE;
                break;
            case '4':
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_720P;
                displaySelectDone = TRUE;
                break;
            case '5':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_SDTV_NTSC;
                    displaySelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This display NOT supported on current platform\n");
                }
                break;
            case '6':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_SDTV_PAL;
                    displaySelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This display NOT supported on current platform\n");
                }
                break;
            case '7':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_XGA_TDM;
                    displaySelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This display NOT supported on current platform\n");
                }
                break;
            case '8':
                gChains_usecaseCfg.displayType =
                    CHAINS_DISPLAY_TYPE_LDC_10_INCH_LCDCTRL_TC358778_MIPI_DSI_1920_1200;
                displaySelectDone = TRUE;
                break;
            case '9':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_WXGA;
                    displaySelectDone = TRUE;
                }
                else
                {
                    Vps_printf(" This display NOT supported on current platform\n");
                }
                break;
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

