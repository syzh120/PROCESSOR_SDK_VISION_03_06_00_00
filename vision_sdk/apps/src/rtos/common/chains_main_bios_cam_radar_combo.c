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

char gChains_menuCamRadarComboUsecases[] = {
    "\r\n "
    "\r\n Camera and Radar Combo Use Cases"
    "\r\n --------------------------------"
    #ifdef UC_camera_radar_capture_display
    "\r\n 1: Camera and Radar Capture +  Radar Processing (DSP1) + Display (HDMI)"
    #endif
    #ifdef UC_tidl_OD_radar_process_display
    "\r\n 2: TIDL OD + Radar Processing + Display (HDMI)"
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
 * \param   ch        [IN]  Input choice for user
 *
 *******************************************************************************
*/
Void Chains_menuCamRadarComboRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuCamRadarComboUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_camera_radar_capture_display
            case '1':
                if (Bsp_platformIsTda2xxFamilyBuild())
                {
                    strncpy(
                        gChains_usecaseCfg.sensorName,
                        SENSOR_SONY_IMX390_AWR1243_UB953_D3,
                        ISS_SENSORS_MAX_NAME);
                    Vps_printf(" D3-IMX390 AND AWR1243 Radar Sensors are Selected \r\n");
                    Chains_cameraRadarCapture_display(&gChains_usecaseCfg);
                }
                break;
            #endif
			#ifdef UC_tidl_OD_radar_process_display
            case '2':
                if (Bsp_platformIsTda2xxFamilyBuild())
                {
                    Chains_tidlOD_radarProcess_display(&gChains_usecaseCfg);                }
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

