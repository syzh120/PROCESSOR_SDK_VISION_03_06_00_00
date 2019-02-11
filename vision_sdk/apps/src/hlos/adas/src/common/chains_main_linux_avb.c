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
 * \brief AVB UC Menu
 *******************************************************************************
 */

char gChains_menuAvbRxUsecases[] = {
    "\r\n "
    "\r\n AVB RX Usecases"
    "\r\n -----------------"
#ifdef UC_avb_rx_multi_cam_decode_sgx_display
    "\r\n 1: 4CH AVB Capture + Decode + SGX MOSAIC + DISPLAY"
#endif
#ifdef UC_avb_rx_multi_cam_3d_srv
    "\r\n 2: 4CH AVB Capture + Decode + SGX 3D-SRV + DISPLAY"
#endif
#ifdef UC_avbrx_sv_display_avbtx
    "\r\n 3: 4CH AVB Capture + Decode + SGX 3D-SRV + DISPLAY + ENCODE + AVBTX"
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
Void Chains_menuAvbRxRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuAvbRxUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_avb_rx_multi_cam_decode_sgx_display
            case '1':
                gChains_usecaseCfg.numLvdsCh = 4;
                Chains_AvbRxDecodeSgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_avb_rx_multi_cam_3d_srv
            case '2':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                Chains_AvbRxSgx3DSrv(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_avbrx_sv_display_avbtx
            case '3':
                gChains_usecaseCfg.numLvdsCh = 4;
                gChains_usecaseCfg.svOutputMode = ALGORITHM_LINK_SRV_OUTPUT_3D;
                gChains_usecaseCfg.enableCarOverlayInAlg = 0;
                gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;
                gChains_usecaseCfg.enableAutoCalib = 1;
                gChains_usecaseCfg.enablePersmatUpdate = 0;
                chains_avbrxSrvDisplayAvbtx(&gChains_usecaseCfg);
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

