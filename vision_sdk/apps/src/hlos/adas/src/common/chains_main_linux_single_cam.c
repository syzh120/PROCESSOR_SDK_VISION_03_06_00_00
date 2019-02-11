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
 * \brief Single Camera UC Menu
 *******************************************************************************
 */

char gChains_menuSingleCameraUsecases[] = {
    "\r\n "
    "\r\n Single Camera Usecases"
    "\r\n ------------------------"
#ifdef UC_vip_single_cam_sgx_display
    "\r\n 1: 1CH VIP capture + SGX Copy + DISPLAY"
#endif
#ifndef IPUMM_INCLUDE
#ifdef UC_vip_single_cam_enc_dec_sgx_display
    "\r\n 2: 1CH VIP capture + Encode + Decode + SGX Copy + DISPLAY"
#endif
#endif
#ifdef UC_vip_single_cam_framecopyEve_sgx_display
    "\r\n 3: 1CH VIP capture + Alg FrameCopy (EVE1) + SGX Copy + DISPLAY - (TDA2xx ONLY)"
#endif
#ifdef FPD_DISPLAY
#ifdef UC_vip_single_cam_dualSgxDisplay
    "\r\n 4: 1CH VIP capture + SGX Copy + DUAL Display(HDMI & FPD-Out)"
#endif
#endif
#ifndef IPUMM_INCLUDE
#ifdef UC_null_src_decode_display
    "\r\n 5: NullSrc + Decode + Display (Only 1920x1080 H264/MJPEG Video Input Bit-Stream Supported)"
#endif
#endif
#ifdef UC_vip_single_cam_framecopy_sgx_display
    "\r\n 6: 1CH VIP capture + Alg Frame Copy (A15) + SGX Copy + DISPLAY"
#endif
#ifdef UC_vip_single_cam_connectorLinksA15_sgx_display
    "\r\n 7: 1CH VIP + Alg Frame Copy (A15) + Connetor Links (Dup, Merge, Select, Gate on A15) + SGX Copy + DISPLAY"
#endif
#ifdef UC_disp_dist_src_display
    "\r\n 8: DispDistSrc (weston) + Display (1920x1080 HDMI)"
#endif
#ifdef UC_vip_single_cam_sgx_display_autosar_app
    "\r\n 9: 1CH VIP capture + SGX Copy + DISPLAY + Autosar"
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
Void Chains_menuSingleCameraRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuSingleCameraUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_vip_single_cam_sgx_display
            case '1':
                chains_vipSingleCam_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifndef IPUMM_INCLUDE
            #ifdef UC_vip_single_cam_enc_dec_sgx_display
            case '2':
                chains_vipSingleCam_Enc_Dec_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifdef UC_vip_single_cam_framecopyEve_sgx_display
            case '3':
                gChains_usecaseCfg.algProcId = SYSTEM_PROC_EVE1;
                chains_vipSingleCamFrmcpyEve_SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef FPD_DISPLAY
            #ifdef UC_vip_single_cam_dualSgxDisplay
            case '4':
                chains_vipSingleCam_SGX_IpuDualDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifndef IPUMM_INCLUDE
            #ifdef UC_null_src_decode_display
            case '5':
                gChains_usecaseCfg.numLvdsCh = 1;
                Chains_nullSrc_DecodeDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #endif
            #ifdef UC_vip_single_cam_framecopy_sgx_display
            case '6':
                chains_vipSingleCamFrameCopySgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_connectorLinksA15_sgx_display
            case '7':
                chains_vipSingleCamConnectorLinksA15SgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_disp_dist_src_display
            case '8':
                Chains_dispDistSrc_Display(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_sgx_display_autosar_app
            case '9':
                chains_vipSingleCam_SgxDisplay_Autosar(&gChains_usecaseCfg);
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

