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

/**
 *******************************************************************************
 *
 * \file app_init_dsp.c
 *
 * \brief  This file implements application init functions for the DSP core
 *
 *         This file has the DSP1 main(), the entry point to the core.
 *         Set the DSP1 clock and call System_start() & BIOS_start()
 *
 * \version 0.0 (Jul 2013) : [SS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include <src/rtos/utils_common/include/utils.h>
#include <include/link_api/system_common.h>


/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */
#ifdef ALG_sceneobstruction
    Int32 AlgorithmLink_sceneObstructionDetect_initPlugin(void);
#endif
#ifdef ALG_framecopy
    Int32 AlgorithmLink_FrameCopy_initPlugin(void);
#endif
#ifdef ALG_safe_framecopy
    Int32 AlgorithmLink_SafeFrameCopy_initPlugin(void);
#endif
#ifdef ALG_colortogray
    Int32 AlgorithmLink_ColorToGray_initPlugin(void);
#endif
#ifdef ALG_dmaSwMs
    Int32 AlgorithmLink_DmaSwMs_initPlugin(void);
#endif
#ifdef ALG_objectdetection
    Int32 AlgorithmLink_ObjectDetection_initPlugin(void);
#endif
#ifdef ALG_objectdetection
    Int32 AlgorithmLink_ObjectClassification_initPlugin(void);
#endif
#ifdef ALG_denseopticalflow
    Int32 AlgorithmLink_vectorToImage_initPlugin(void);
#endif
#ifdef ALG_structurefrommotion
    Int32 AlgorithmLink_sfmLinearTwoView_initPlugin(void);
    Int32 AlgorithmLink_sfmMain_initPlugin(void);
    Int32 AlgorithmLink_sfmMap_initPlugin(void);
#endif
#ifdef ALG_lanedetection
    Int32 AlgorithmLink_laneDetect_initPlugin(void);
#endif
#ifdef ALG_objectdetection
    Int32 AlgorithmLink_objectDraw_initPlugin(void);
#endif
#ifdef ALG_sfm
    Int32 AlgorithmLink_sfm_initPlugin(void);
    Int32 AlgorithmLink_fcw_initPlugin(void);
#endif
#ifdef ALG_clr
    Int32 AlgorithmLink_clr_initPlugin(void);
#endif
#ifdef ALG_radarprocess
    Int32 AlgorithmLink_RadarProcess_initPlugin(void);
#endif
#ifdef ALG_surroundview
    Int32 AlgorithmLink_Synthesis_initPlugin(void);
    Int32 AlgorithmLink_pAlign_initPlugin(void);
    Int32 AlgorithmLink_gAlign_initPlugin(void);
    Int32 AlgorithmLink_gAlign3D_initPlugin(void);
    Int32 AlgorithmLink_adaptiveBowl_initPlugin(void);
    Int32 AlgorithmLink_UltrasonicFusion_initPlugin(void);
#endif
#ifdef ALG_drawRearview
    Int32 AlgorithmLink_DrawRearview_initPlugin(void);
#endif
#ifdef ALG_autocalibration
    Int32 AlgorithmLink_acDetect_initPlugin(void);
    Int32 AlgorithmLink_pEstimate_initPlugin(void);
#endif
#if defined(ALG_surroundview) || defined(ALG_autocalibration)
    Int32 lz4CompDecomp_init(void);
#endif

#ifdef ALG_autoremap
    Int32 AlgorithmLink_AutoRemap_initPlugin(void);
#endif
#ifdef ALG_stereo_postprocessing
    Int32 AlgorithmLink_StereoPostProcess_initPlugin(void);
#endif
#ifdef ALG_swcrc
    Int32 AlgorithmLink_SwCrc_initPlugin(void);
#endif
#ifdef ALG_rear_view_panorama
    Int32 AlgorithmLink_Stitching_initPlugin(void);
    Int32 AlgorithmLink_ImageTransform_initPlugin(void);
    Int32 AlgorithmLink_SeamDetection_initPlugin(void);
#endif
#ifdef ALG_stereo_app
    Int32 AlgorithmLink_StereoApp_initPlugin(void);
#endif

#ifdef ALG_tidl
    Int32 AlgorithmLink_tidl_initPluginDsp(void);
#endif
#ifdef ALG_tiop
    Int32 AlgorithmLink_tiop_initPlugin(void);
#endif

/**
 *******************************************************************************
 *
 * \brief Application init
 *
 *******************************************************************************
 */
void App_init(void)
{
    /* Algorithms plug in init */
#ifdef ALG_sceneobstruction
    AlgorithmLink_sceneObstructionDetect_initPlugin();
#endif
#ifdef ALG_framecopy
    AlgorithmLink_FrameCopy_initPlugin();
#endif
#ifdef ALG_safe_framecopy
    AlgorithmLink_SafeFrameCopy_initPlugin();
#endif
#ifdef ALG_colortogray
    AlgorithmLink_ColorToGray_initPlugin();
#endif
#ifdef ALG_dmaSwMs
    AlgorithmLink_DmaSwMs_initPlugin();
#endif
#ifdef ALG_objectdetection
    AlgorithmLink_ObjectDetection_initPlugin();
#endif
#ifdef ALG_objectdetection
    AlgorithmLink_ObjectClassification_initPlugin();
#endif
#ifdef ALG_denseopticalflow
    AlgorithmLink_vectorToImage_initPlugin();
#endif
#ifdef ALG_structurefrommotion
    AlgorithmLink_sfmLinearTwoView_initPlugin();
    AlgorithmLink_sfmMain_initPlugin();
    AlgorithmLink_sfmMap_initPlugin();
#endif
#ifdef ALG_lanedetection
    AlgorithmLink_laneDetect_initPlugin();
#endif
#ifdef ALG_objectdetection
    AlgorithmLink_objectDraw_initPlugin();
#endif
#ifdef ALG_sfm
    AlgorithmLink_sfm_initPlugin();
    AlgorithmLink_fcw_initPlugin();
#endif
#ifdef ALG_clr
    AlgorithmLink_clr_initPlugin();
#endif
#ifdef ALG_radarprocess
    AlgorithmLink_RadarProcess_initPlugin();
#endif
#ifdef ALG_surroundview
    AlgorithmLink_Synthesis_initPlugin();
    AlgorithmLink_pAlign_initPlugin();
    AlgorithmLink_gAlign_initPlugin();
    AlgorithmLink_gAlign3D_initPlugin();
    AlgorithmLink_adaptiveBowl_initPlugin();
    AlgorithmLink_UltrasonicFusion_initPlugin();
#endif
#ifdef ALG_drawRearview
    AlgorithmLink_DrawRearview_initPlugin();
#endif
#ifdef ALG_autocalibration
    AlgorithmLink_acDetect_initPlugin();
    AlgorithmLink_pEstimate_initPlugin();
#endif
#if defined(ALG_surroundview) || defined(ALG_autocalibration)
    lz4CompDecomp_init();
#endif
#ifdef ALG_autoremap
    AlgorithmLink_AutoRemap_initPlugin();
#endif
#ifdef ALG_stereo_postprocessing
    AlgorithmLink_StereoPostProcess_initPlugin();
#endif
#ifdef ALG_swcrc
    AlgorithmLink_SwCrc_initPlugin();
#endif
#ifdef ALG_rear_view_panorama
    AlgorithmLink_Stitching_initPlugin();
    AlgorithmLink_ImageTransform_initPlugin();
    AlgorithmLink_SeamDetection_initPlugin();
#endif
#ifdef ALG_stereo_app
    AlgorithmLink_StereoApp_initPlugin();
#endif
#ifdef ALG_tidl
    AlgorithmLink_tidl_initPluginDsp();
#endif
#ifdef ALG_tiop
    AlgorithmLink_tiop_initPlugin();
#endif
}

/**
 *******************************************************************************
 *
 * \brief Application deinit
 *
 *******************************************************************************
 */
void App_deInit(void)
{

}

/* Nothing beyond this point */

