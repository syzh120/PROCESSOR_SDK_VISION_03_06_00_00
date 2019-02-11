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
 * \file app_init_a15.c
 *
 * \brief  This file implements application init functions for the A15 core
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

#ifdef NDK_PROC_TO_USE_A15_0
    void ConsoleClose();
    Int32 NetworkCtrl_init();
    Int32 NetworkCtrl_deInit();
#endif

#ifdef ALG_opencvcanny
    Int32 AlgorithmLink_OpenCVCanny_initPlugin(void);
#endif
#ifdef ALG_opencvopencldilation
    Int32 AlgorithmLink_OpenCVOpenCLDilation_initPlugin(void);
#endif
#ifdef ALG_opencvtests
    Int32 AlgorithmLink_OpenCVTests_initPlugin(void);
#endif
#ifdef ALG_framecopy
    Int32 AlgorithmLink_FrameCopy_initPlugin(void);
#endif
#ifdef ALG_safe_framecopy
    Int32 AlgorithmLink_SafeFrameCopy_initPlugin(void);
#endif
#ifdef ALG_openclframecopy
    Int32 AlgorithmLink_OpenCLFrameCopy_initPlugin(void);
#endif
#ifdef ALG_openclcannyedge
    Int32 AlgorithmLink_OpenCLCannyEdge_initPlugin(void);
#endif
#ifdef ALG_dmaSwMs
    Int32 AlgorithmLink_DmaSwMs_initPlugin(void);
#endif
#ifdef ALG_objectdetection
    Int32 AlgorithmLink_objectDraw_initPlugin(void);
#endif
#ifdef ALG_radarprocess
    Int32 AlgorithmLink_RadarProcess_initPlugin(void);
#endif
#ifdef ALG_tidl
    Int32 AlgorithmLink_tidlpreproc_initPlugin(void);
    Int32 AlgorithmLink_tidlpostproc_initPlugin(Void);
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
#ifdef NDK_PROC_TO_USE_A15_0
    NetworkCtrl_init();
#endif

    /* Algorithms plug in init */
#ifdef ALG_opencvcanny
    AlgorithmLink_OpenCVCanny_initPlugin();
#endif
#ifdef ALG_opencvopencldilation
    AlgorithmLink_OpenCVOpenCLDilation_initPlugin();
#endif
#ifdef ALG_opencvtests
    AlgorithmLink_OpenCVTests_initPlugin();
#endif
#ifdef ALG_framecopy
    AlgorithmLink_FrameCopy_initPlugin();
#endif
#ifdef ALG_safe_framecopy
    AlgorithmLink_SafeFrameCopy_initPlugin();
#endif
#ifdef ALG_openclframecopy
    AlgorithmLink_OpenCLFrameCopy_initPlugin();
#endif
#ifdef ALG_openclcannyedge
    AlgorithmLink_OpenCLCannyEdge_initPlugin();
#endif
#ifdef ALG_dmaSwMs
    AlgorithmLink_DmaSwMs_initPlugin();
#endif
#ifdef ALG_objectdetection
    AlgorithmLink_objectDraw_initPlugin();
#endif
#ifdef ALG_radarprocess
    AlgorithmLink_RadarProcess_initPlugin();
#endif
#ifdef ALG_tidl
    AlgorithmLink_tidlpreproc_initPlugin();
    AlgorithmLink_tidlpostproc_initPlugin();
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
#ifdef NDK_PROC_TO_USE_A15_0
    ConsoleClose();
    NetworkCtrl_deInit();
#endif
}

/* Nothing beyond this point */

