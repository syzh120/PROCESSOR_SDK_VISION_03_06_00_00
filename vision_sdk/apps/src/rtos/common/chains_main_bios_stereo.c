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

char gChains_menuStereoUsecases[] = {
    "\r\n "
    "\r\n TDA2x Usecases"
    "\r\n -----------------------------------------"
    "\r\n "
#ifdef UC_network_stereo_display
    "\r\n 1: Network + Stereo + Display (HDMI)"
#endif
#ifdef UC_lvds_vip_single_stereo
    "\r\n 2: 2CH LVDS capture + VPE + Stereo (DSPx, EVEx) + Display (HDMI)"
#endif
#ifdef UC_lvds_vip_single_stereo_auto_calib
    "\r\n 3: 2CH LVDS capture + VPE + Stereo Rectification + Display (HDMI) - USED for on-line Stereo Calibration"
#endif
#ifdef UC_lvds_vip_single_stereo_calibration
    "\r\n 4: 2CH LVDS capture + VPE + Remap + Display (HDMI) - USED for off-line Stereo Calibration"
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
Void Chains_menuStereoRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuStereoUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_network_stereo_display
            case '1':
                if(Bsp_platformIsTda2xxFamilyBuild() && (BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId()))
                {
                    chains_networkStereoDisplay(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform \n");
                }
                break;
            #endif
            #ifdef UC_lvds_vip_single_stereo
            case '2':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.numLvdsCh = 2;

                        if( gChains_usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_OV10635)
                        {
                            Vps_printf(" ### ONLY OV10635 Sensor supported for this usecase");
                            Vps_printf(" ### Please choose OV10635 as Capture Source using option 's'\n");
                            break;
                        }

                        Chains_lvdsVipSingleStereo(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase.  MulitDes Board Not Connected \n");
                    }
                }
                break;
            #endif
            #ifdef UC_lvds_vip_single_stereo_auto_calib
            case '3':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.numLvdsCh = 2;

                        if( gChains_usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_OV10635)
                        {
                            Vps_printf(" ### ONLY OV10635 Sensor supported for this usecase");
                            Vps_printf(" ### Please choose OV10635 as Capture Source using option 's'\n");
                            break;
                        }

                        Chains_lvdsVipSingleStereoAutoCalib(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase.  MulitDes Board Not Connected \n");
                    }
                }
                break;
            #endif
            #ifdef UC_lvds_vip_single_stereo_calibration
            case '4':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.numLvdsCh = 2;

                        if( gChains_usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_OV10635)
                        {
                            Vps_printf(" ### ONLY OV10635 Sensor supported for this usecase");
                            Vps_printf(" ### Please choose OV10635 as Capture Source using option 's'\n");
                            break;
                        }

                        Chains_lvdsVipSingleStereoCalibration(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase.  MulitDes Board Not Connected \n");
                    }
                }
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

