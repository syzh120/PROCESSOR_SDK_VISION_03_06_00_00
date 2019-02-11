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

/*
 *******************************************************************************
 *
 * \file chains_common_surround_view.h
 *
 * \brief This file contains common utility functions used by SV use cases
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_SRV_H_
#define _CHAINS_COMMON_SRV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <src/include/chains_common_osal.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define SRV_NUM_VIEWS                           (4U)

#define SRV_SET_SIZE                            (30U)

#define SRV_OUTPUT_WIDTH_TDA2X_3D               (1080U)
#define SRV_OUTPUT_HEIGHT_TDA2X_3D              (1080U)

#define SRV_OUTPUT_WIDTH_TDA2X_2D               (880U)
#define SRV_OUTPUT_HEIGHT_TDA2X_2D              (1080U)

#define SRV_OUTPUT_WIDTH_TDA3X_3D_LDC           (1280U)
#define SRV_OUTPUT_HEIGHT_TDA3X_3D_LDC          (1080U)

#define SRV_OUTPUT_WIDTH_TDA3X_2D               (720U)
#define SRV_OUTPUT_HEIGHT_TDA3X_2D              (960U)

#define SRV_OUTPUT_WIDTH_TDA3X_2D_LDC           (SRV_OUTPUT_WIDTH_TDA3X_3D_LDC)
#define SRV_OUTPUT_HEIGHT_TDA3X_2D_LDC          (SRV_OUTPUT_HEIGHT_TDA3X_3D_LDC)

#define SRV_LVDS_CAPTURE_WIDTH                  (1280U)
#define SRV_LVDS_CAPTURE_HEIGHT                 (720U)

#define SRV_OV490_SENSOR_WIDTH                  (1280U)
#define SRV_OV490_SENSOR_HEIGHT                 (1080U)

#if defined(LINUX_BUILD) || defined(QNX_BUILD)
    #define SRV_CARBOX_WIDTH                    (80U)
    #define SRV_CARBOX_HEIGHT                   (160U)
#else
    #define SRV_CARBOX_WIDTH                    (160U)
    #define SRV_CARBOX_HEIGHT                   (240U)
#endif

#define SVORG_SCALED_WIDTH                      (SRV_LVDS_CAPTURE_WIDTH/4)
#define SVORG_SCALED_HEIGHT                     (SRV_LVDS_CAPTURE_HEIGHT/4)
#define SVORG_MOSAIC_SPACING_HOR                (0U)
#define SVORG_MOSAIC_SPACING_VER                (35U)
#define SVORG_MOSAIC_WIDTH                      (SVORG_SCALED_WIDTH)
#define SVORG_MOSAIC_HEIGHT                     ((SVORG_SCALED_HEIGHT) * SRV_NUM_VIEWS + SVORG_MOSAIC_SPACING_VER * (SRV_NUM_VIEWS - 1))
#define SVORG_MOSAIC_POSX                       (25U)
#define SVORG_MOSAIC_POSY                       (100 + 35)

#define FRONTCAM_SCALED_WIDTH                   (SRV_LVDS_CAPTURE_WIDTH/2)
#define FRONTCAM_SCALED_HEIGHT                  (SRV_LVDS_CAPTURE_HEIGHT/2)
#define FRONTCAM_MOSAIC_SPACING_HOR             (0U)
#define FRONTCAM_MOSAIC_SPACING_VER             (50U)
#define FRONTCAM_MOSAIC_WIDTH                   (FRONTCAM_SCALED_WIDTH)
#define FRONTCAM_MOSAIC_HEIGHT                  ((FRONTCAM_SCALED_HEIGHT * 2) + FRONTCAM_MOSAIC_SPACING_VER)
#define FRONTCAM_MOSAIC_POSX                    (1920 - 25 - 640)
#define FRONTCAM_MOSAIC_POSY                    (100 + 50)

#define DOF_WIDTH_ALIGN                         (64U)
#define DOF_HEIGHT_ALIGN                        (32U)

#define SRV_FEATUREPLANE_NUM_OUT_BUF            (8U)
#define SRV_FEATUREPLANE_ALG_WIDTH              (640U)
#define SRV_FEATUREPLANE_ALG_HEIGHT             (360U)

#define SRV_TIGHT_SYNC_DELTA_IN_MSEC            (16U)
#define SRV_LOOSE_SYNC_DELTA_IN_MSEC            (0x7FFFFFFF)

#define SRV_TIGHT_SYNC_DROP_THRESHOLD_IN_MSEC   (33U)
#define SRV_LOOSE_SYNC_DROP_THRESHOLD_IN_MSEC   (0x7FFFFFFF)

#define SRV_LDC_PIXEL_PAD                       (2U)
#define SRV_LDC_MESH_TABLE_PITCH(w, r)          ((((((w)/(r))+1) + 15U) & ~15U) * (4U))

/*******************************************************************************
 *  Enums and Structures
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enum for various GA calibration modes (Calibration ON/OFF)
 *
 *******************************************************************************
*/
typedef enum
{
    CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO = 0,
    CHAINS_SURROUND_VIEW_GA_CALIBRATION_FORCE,
    CHAINS_SURROUND_VIEW_GA_CALIBRATION_NO_USERSGXLUT,
    CHAINS_SURROUND_VIEW_GA_CALIBRATION_MAXNUM,
    CHAINS_SURROUND_VIEW_GA_CALIBRATION_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */
}Chains_SurroundView_GACalibrationType;


/**
 *******************************************************************************
 *
 *  \brief  Data structure for the GA calibration
 *          The GA output LUT and perspestive matrix are generated while
 *          calibration ON and these tables are stored in QSPI flash.
 *          Successive run read these tables and input the same to SV GA
 *          Algorithm.
 *
 *******************************************************************************
 */
typedef struct
{
    Chains_SurroundView_GACalibrationType GACalibrationType;
    Chains_SurroundView_GACalibrationType GACalibrationTypePrev;
    UInt8 *gaLUTDDRPtr;
    UInt8 *persMatDDRPtr;
    UInt8 *featurePtDDRPtr;
    UInt8 *autoPersMatDDRPtr;
    UInt8 *synthLUTPtr;
    UInt32 synthLUTSize;
    AlgorithmLink_GAlignCalibrationMode calMode;
    AlgorithmLink_SrvOutputModes svOutputMode;

} ChainsCommon_SurroundView_GACalibrationInfo;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
Void ChainsCommon_Osal_readSrvCalibTable(
                                UInt32 readAddr,
                                UInt32 readOffset,
                                UInt32 readSize);
Void ChainsCommon_Osal_writeSrvCalibTable(
                                UInt32 writeAddr,
                                UInt32 writeOffset,
                                UInt32 writeSize);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */
