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

char gChains_menuSingleCameraUsecases[] = {
    "\r\n "
    "\r\n Single Camera Usecases"
    "\r\n ------------------------"
#ifdef UC_vip_single_cam_view
    "\r\n 1: 1CH VIP capture + Display "
#endif
#ifdef UC_vip_single_cam_frame_copy
    "\r\n 2: 1CH VIP capture + Alg Frame Copy (DSP1) + Display "
#endif
#ifdef UC_vip_single_cam_frame_copy
    "\r\n 3: 1CH VIP capture + Alg Frame Copy (EVE1) + Display "
#endif
#ifdef UC_vip_single_cam_frame_copy
    "\r\n 4: 1CH VIP capture + Alg Frame Copy (A15) + Display "
#endif
#ifdef UC_vip_single_cam_edge_detection
    "\r\n 5: 1CH VIP capture + Edge Detect (EVE1) + Display "
#endif
#ifdef UC_vip_single_cam_dense_optical_flow
    "\r\n 6: 1CH VIP capture + Dense Optical Flow (EVEx) + Display (HDMI)"
#endif
#ifdef UC_vip_single_cam_sparse_optical_flow
    "\r\n 7: 1CH VIP capture (HDMI) + Sparse Optical Flow (EVE1) + Display"
#endif
#ifdef UC_vip_single_cam_subframe_copy
    "\r\n 8: 1CH VIP capture + Alg Subframe Copy (EVE1) + Display "
#endif
#ifdef UC_vip_single_cam_view_dsswb
    "\r\n 9: 1CH VIP capture + DSSWB + CRC + Display (Supported only on TDA3x)"
#endif
#ifdef UC_vip_single_cam_view_encdec
    "\r\n a: 1CH VIP capture + ENC + DEC + VPE + Display"
#endif
#ifdef UC_vip_single_cam_lane_detection
    "\r\n b: 1CH VIP capture (HDMI) + Lane Detect (DSP1 + EVE1) + Display"
#endif
#ifdef UC_vip_single_cam_sfm
    "\r\n c: 1CH VIP capture (HDMI) + SOF (EVE1) + SFM (DSP1) + Display"
#endif
#ifdef UC_vip_single_cam_tlr
    "\r\n d: 1CH VIP capture (HDMI) + Traffic Light Recognition (TLR) (DSP1) + Display"
#endif
#ifdef UC_vip_single_cam_object_detection2
    "\r\n e: 1CH VIP capture (HDMI) + Pedestrian, Traffic Sign, Vehicle Detect 2 (EVE1 + DSP1) + Display"
#endif
#ifdef UC_vip_single_cam_analytics2
    "\r\n f: 1CH VIP capture (HDMI) + FrontCam Analytics 2 (PD+TSR+VD+LD+TLR+SFM) (DSPx, EVEx) + Display (HDMI)"
#endif
#ifdef UC_vip_single_cam_frame_copy_safety
    "\r\n g: 1CH VIP capture + QM Alg Frame Copy with FFI (DSP1) + Display "
#endif
#ifdef UC_vip_single_cam_frame_copy_safety
    "\r\n h: 1CH VIP capture + QM Alg Frame Copy with FFI (EVE1) + Display (TDA3x only)"
#endif
#ifdef UC_vip_single_cam_frame_copy_safety
    "\r\n i: 1CH VIP capture + Safe Frame Copy (A15) + Display "
#endif
#ifdef UC_vip_single_cam_opencvcanny
    "\r\n j: 1CH VIP capture + OpenCV Canny (A15) + Display "
#endif
#ifdef UC_vip_single_cam_opencvopencldilation
    "\r\n k: 1CH VIP capture + OpenCV OpenCL Dilation (A15 + DSP) + Display "
#endif
#ifdef UC_vip_single_cam_display_metadata
    "\r\n l: 1CH VIP capture + DisplayMultiPipe + DSSWb + Metadata "
#endif
#ifdef UC_vip_single_cam_opencvtests
    "\r\n m: 1CH VIP capture + OpenCV tests (A15) + Display "
#endif
#ifdef UC_null_src_dec_display
    "\r\n n: NullSrc (File IO) + Decode + Display"
#endif
#ifdef UC_vip_single_cam_view_autosar_app
    "\r\n o: 1CH VIP capture + Display + Autosar"
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
    Chains_Ctrl usecaseCfg;
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuSingleCameraUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_vip_single_cam_view
            case '1':
                Chains_vipSingleCam_Display(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_frame_copy
            case '2':
                gChains_usecaseCfg.algProcId = SYSTEM_PROC_DSP1;
                Chains_vipSingleCameraFrameCopy(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_frame_copy
            case '3':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_EVE1;
                    Chains_vipSingleCameraFrameCopy(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_frame_copy
            case '4':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_A15_0;
                    Chains_vipSingleCameraFrameCopy(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_edge_detection
            case '5':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_EVE1;
                    Chains_vipSingleCameraEdgeDetection(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_dense_optical_flow
            case '6':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    gChains_usecaseCfg.numLvdsCh = 1;
                    usecaseCfg = gChains_usecaseCfg;
                    Chains_vipSingleCameraDenseOpticalFlow(&usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_sparse_optical_flow
            case '7':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    Chains_vipSingleCameraSparseOpticalFlow(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_subframe_copy
            case '8':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    Chains_vipSingleCameraSubFrameCopy(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_view_dsswb
            case '9':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    Chains_vipSingleCam_DisplayWbCrc(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_view_encdec
            case 'a':
            case 'A':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    Chains_vipSingleCam_EncDec_Display(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_lane_detection
            case 'b':
            case 'B':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    usecaseCfg = gChains_usecaseCfg;
                    if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_HDMI_1080P )
                    {
                        Vps_printf(" ### ONLY HDMI 1080p60 input supported for this usecase ");
                        Vps_printf(" ### Please choose HDMI 1080p60 Capture Source using option 's'\n");
                        break;
                    }
                    Chains_vipSingleCameraLaneDetect(&gChains_usecaseCfg);
                    /* No HDMI input for monstercam */
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_sfm
            case 'c':
            case 'C':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    usecaseCfg = gChains_usecaseCfg;
                    if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_HDMI_1080P )
                    {
                        Vps_printf(" ### ONLY HDMI 1080p60 input supported for this usecase ");
                        Vps_printf(" ### Please choose HDMI 1080p60 Capture Source using option 's'\n");
                        break;
                    }
                    Chains_vipSingleCameraSfm(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_tlr
            case 'd':
            case 'D':
                usecaseCfg = gChains_usecaseCfg;
                if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_HDMI_1080P )
                {
                    Vps_printf(" ### ONLY HDMI 1080p60 input supported for this usecase ");
                    Vps_printf(" ### Please choose HDMI 1080p60 Capture Source using option 's'\n");
                    break;
                }
                Chains_vipSingleCameraTlr(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_object_detection2
            case 'e':
            case 'E':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    usecaseCfg = gChains_usecaseCfg;
                    #if 0
                    if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_HDMI_1080P )
                    {
                        Vps_printf(" ### ONLY HDMI 1080p60 input supported for this usecase ");
                        Vps_printf(" ### Please choose HDMI 1080p60 Capture Source using option 's'\n");
                        break;
                    }
                    #endif

                    Chains_vipSingleCameraObjectDetect2Tda3xx(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_analytics2
            case 'f':
            case 'F':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                    usecaseCfg = gChains_usecaseCfg;
                    if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_HDMI_1080P )
                    {
                        Vps_printf(" ### ONLY HDMI 1080p60 input supported for this usecase ");
                        Vps_printf(" ### Please choose HDMI 1080p60 Capture Source using option 's'\n");
                        break;
                    }
                    Chains_vipSingleCameraAnalytics2(&gChains_usecaseCfg);
                }
                else
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_frame_copy_safety
            case 'G':
            case 'g':
                #ifdef ECC_FFI_INCLUDE
                gChains_usecaseCfg.algProcId = SYSTEM_PROC_DSP1;
                Chains_vipSingleCameraSafeFrameCopy(&gChains_usecaseCfg);
                #else
                Vps_printf(" ### ECC_FFI_INCLUDE is not enabled!!!! \n");
                #endif
                break;
            #endif
            #ifdef UC_vip_single_cam_frame_copy_safety
            case 'h':
            case 'H':
                #ifdef ECC_FFI_INCLUDE
                if(BSP_PLATFORM_SOC_ID_TDA3XX == Bsp_platformGetSocId())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_EVE1;
                    Chains_vipSingleCameraSafeFrameCopy(&gChains_usecaseCfg);
                }
                else if(BSP_PLATFORM_SOC_ID_TDA2EX == Bsp_platformGetSocId())
                {
                    Vps_printf(" ### TDA2Ex do not have EVE core, usecase with EVE is not supported \n");
                }
                else
                {
                    Vps_printf(" ### FFI on EVE is supported in VisionSDK only on TDA3x\n");
                }
                #else
                Vps_printf(" ### ECC_FFI_INCLUDE is not enabled!!!! \n");
                #endif
                break;
            #endif
            #ifdef UC_vip_single_cam_frame_copy_safety
            case 'i':
            case 'I':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_A15_0;
                    Chains_vipSingleCameraSafeFrameCopy(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_opencvcanny
            case 'j':
            case 'J':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_A15_0;
                    Chains_vipSingleCamOpenCVCanny(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_opencvopencldilation
            case 'k':
            case 'K':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_A15_0;
                    Chains_vipSingleCamOpenCVOpenCLDilation(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_display_metadata
            case 'l':
            case 'L':
                {
                    Chains_vipSingleCam_Display_Metadata(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_opencvtests
            case 'm':
            case 'M':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    gChains_usecaseCfg.algProcId = SYSTEM_PROC_A15_0;
                    Chains_vipSingleCamOpenCVTests(&gChains_usecaseCfg);
                }
            #endif
            #ifdef UC_null_src_dec_display
            case 'n':
            case 'N':
                {
                    gChains_usecaseCfg.numLvdsCh = 1;
                    Chains_nullSrc_DecodeDisplay(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_vip_single_cam_view_autosar_app
            case 'o':
            case 'O':
                Chains_vipSingleCam_Display_Autosar(&gChains_usecaseCfg);
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

