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
 * \file app_init_ipu_secondary.c
 *
 * \brief  This file implements application init functions for the IPU primary core
 *
 *         This file has the DSP1 main(), the entry point to the core.
 *         Set the DSP1 clock and call System_start() & BIOS_start()
 *
 * \version 0.0 (Aug 2018) : [AKG] First version
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
#include <include/link_api/autosar_ipcLink.h>

/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */
#if ((defined (BUILD_M4_0) && defined(NDK_PROC_TO_USE_IPU1_0)) || \
     (defined (BUILD_M4_2) && defined(NDK_PROC_TO_USE_IPU2)))
    void ConsoleClose();
    Int32 NetworkCtrl_init();
    Int32 NetworkCtrl_deInit();
#endif

#if (defined (FATFS_PROC_TO_USE_IPU1_0))
   void  NetworkCtrl_fileIOCmdHandler_Init();
   void  NetworkCtrl_fileIOCmdHandler_DeInit();
#endif

#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || \
     (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
    Void DevCtrl_init();
    Void DevCtrl_deInit();
#endif

#ifdef ALG_sceneobstruction
    Int32 AlgorithmLink_sceneObstructionDetect_initPlugin(void);
#endif
#ifdef ALG_iss_aewb
    Int32 AlgorithmLink_issAewb1_initPlugin(void);
#endif
#ifdef ALG_iss_aewb2
Int32 AlgorithmLink_issAewb2_initPlugin(void);
#endif
#ifdef ALG_deWarp
    Int32 AlgLink_DeWarpPlugin_init(void);
#endif
#ifdef ALG_crc
    Int32 AlgorithmLink_Crc_initPlugin(void);
#endif
#ifdef ALG_objectdetection
    /* Image Pyramid plugin is supported only one M4 */
    Int32 AlgorithmLink_imgPyramidComputation_initPlugin(void);
#endif
#ifdef ALG_dmaSwMs
    Int32 AlgorithmLink_DmaSwMs_initPlugin(void);
#endif
#ifdef ALG_vpeSwMs
    Int32 AlgorithmLink_VpeSwMs_initPlugin(void);
#endif
#ifdef ALG_objectdetection
    Int32 AlgorithmLink_objectDraw_initPlugin(void);
#endif
#ifdef ALG_radarprocess
    Int32 AlgorithmLink_RadarProcess_initPlugin(void);
#endif
#ifdef ALG_rvcDiags
    Int32 AlgorithmLink_RvcDiagnostic_initPlugin(void);
#endif
#ifdef ALG_openvx
    Int32 AlgorithmLink_OpenVx_initPlugin(void);
#endif
#ifdef ALG_tidl
    #ifdef TDA3XX_BUILD
        Int32 AlgorithmLink_tidlpreproc_initPluginIpu(void);
    #endif
#endif
#ifdef AUTOSAR_APP 
    Void McalRx_init(Void);
    Void McalRx_deInit(Void);
    Void McalTx_init(Void);
    Void McalTx_deInit(Void);
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
#if ((defined (BUILD_M4_0) && defined(NDK_PROC_TO_USE_IPU1_0)) || \
     (defined (BUILD_M4_2) && defined(NDK_PROC_TO_USE_IPU2)))
    NetworkCtrl_init();
#endif
#if (defined (FATFS_PROC_TO_USE_IPU1_0))
    NetworkCtrl_fileIOCmdHandler_Init();
#endif
#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || \
     (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
    DevCtrl_init();
#endif
    /* Algorithms plug in init */
#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || \
     (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
    #ifdef ALG_sceneobstruction
        AlgorithmLink_sceneObstructionDetect_initPlugin();
    #endif
    #ifdef ALG_iss_aewb
        AlgorithmLink_issAewb1_initPlugin();
    #ifdef ALG_iss_aewb2
    AlgorithmLink_issAewb2_initPlugin();
    #endif
    #endif
    #ifdef ALG_deWarp
        AlgLink_DeWarpPlugin_init();
    #endif
    #ifdef ALG_crc
        AlgorithmLink_Crc_initPlugin();
    #endif
    #ifdef ALG_objectdetection
        /* Image Pyramid plugin is supported only one M4 */
        AlgorithmLink_imgPyramidComputation_initPlugin();
    #endif
    #ifdef ALG_dmaSwMs
        AlgorithmLink_DmaSwMs_initPlugin();
    #endif
    #ifdef ALG_vpeSwMs
        AlgorithmLink_VpeSwMs_initPlugin();
    #endif
    #ifdef ALG_objectdetection
        AlgorithmLink_objectDraw_initPlugin();
    #endif
    #ifdef ALG_radarprocess
        AlgorithmLink_RadarProcess_initPlugin();
    #endif
    #ifdef ALG_rvcDiags
        AlgorithmLink_RvcDiagnostic_initPlugin();
    #endif
    #ifdef ALG_openvx
        AlgorithmLink_OpenVx_initPlugin();
    #endif
    #ifdef ALG_tidl
        #ifdef TDA3XX_BUILD
            AlgorithmLink_tidlpreproc_initPluginIpu();
        #endif
    #endif
#endif
#ifdef AUTOSAR_APP
    McalTx_init();
    McalRx_init();
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
#if ((defined (BUILD_M4_0) && defined(NDK_PROC_TO_USE_IPU1_0)) || \
     (defined (BUILD_M4_2) && defined(NDK_PROC_TO_USE_IPU2)))
    ConsoleClose();
    NetworkCtrl_deInit();
    DevCtrl_deInit();
#endif
#if (defined (FATFS_PROC_TO_USE_IPU1_0))
    NetworkCtrl_fileIOCmdHandler_DeInit();
#endif
#ifdef AUTOSAR_APP
    McalTx_deInit();
    McalRx_deInit();
#endif
}

/* Nothing beyond this point */

