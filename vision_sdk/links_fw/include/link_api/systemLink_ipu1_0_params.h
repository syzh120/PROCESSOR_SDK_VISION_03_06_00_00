/*
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
*/

/**
 *******************************************************************************
 *
 *  \ingroup PROCESSOR_LINK_API
 *  \defgroup SYSTEM_IPU1_0_LINK_API Processor Link API: IPU1 Core0
 *
 *  This module defines the control commands that are applicable to
 *  IPU1 Core0 processor.
 *
 *   @{
*/

/**
 *******************************************************************************
 *
 *  \file systemLink_ipu1_0_params.h
 *  \brief Processor Link API: IPU1 Core0
 *
 *******************************************************************************
*/

#ifndef SYSTEM_LINK_IPU1_0_PARAMS_H_
#define SYSTEM_LINK_IPU1_0_PARAMS_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_common.h>

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Configuration for sub-frame level processing at create time.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 subFrameEnable;
    /**< TRUE : SubFrame level capture/processing is enabled.
     *   FALSE: SubFrame level capture/processing is disabled.
     *   Must be FALSE for multi-channel capture mode. */
    UInt32 numLinesPerSubFrame;
    /**< Number of lines per subframes.
     *
     *   MUST be multiple of the output size.
     *   Not valid, ignored for ancillary data capture.
     *
     *   In case of capture,
     *   SubFrame callback gets called after every numLinesPerSubFrame
     *   for every output stream, except ancillary data stream.
     *
     *   Ignored when subFrameEnable = FALSE */
} System_SubFrameParams;

/**
 *  enum System_WbInNode
 *  \brief Enumerations for WB connection to Pipeline/Overlay.
 */
typedef enum
{
    SYSTEM_WB_IN_NODE_VID1 = 1,
    /**< VID1 pipeline is connected to Writeback. */
    SYSTEM_WB_IN_NODE_VID2 = 2,
    /**< VID2 pipeline is connected to Writeback. */
    SYSTEM_WB_IN_NODE_VID3 = 3,
    /**< VID3 pipeline is connected to Writeback
     *    Not applicable for tda3xx platform. */
    SYSTEM_WB_IN_NODE_GFX = 4,
    /**< GFX pipeline is connected to Writeback*/
    SYSTEM_WB_IN_NODE_LCD1 = 6,
    /**< LCD1 Overlay is connected to Writeback*/
    SYSTEM_WB_IN_NODE_LCD2 = 7,
    /**< LCD2 Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    SYSTEM_WB_IN_NODE_LCD3 = 8,
    /**< LCD3 Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    SYSTEM_WB_IN_NODE_TV = 9,
    /**< TV Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    SYSTEM_WB_IN_NODE_MAX = 10
    /**< Should be the last value of this
     * enumeration. Will be used by driver for
     * validating the input parameters. */
} System_WbInNode;

/**
 *******************************************************************************
 *
 *  \brief Input frame Configuration parameters for DSS WB capture &
 *         processing at create time.
 *
 *******************************************************************************
 */
typedef struct
{
    System_WbInNode        inNode;
    /**< node from where write back should be captured */
    UInt32                 wbInSourceWidth;
    /**< Input width of overlay feeding Writeback pipeline */
    UInt32                 wbInSourceHeight;
    /**< Input height of overlay feeding Writeback pipeline */
    UInt32                 wbInWidth;
    /**< input width for wb pipeline. Same as wbInSourceWidth if crop not
     *required */
    UInt32                 wbInHeight;
    /**< input height for wb pipeline. Same as wbInSourceHeight if crop not
     *required */
    UInt32                 wbPosx;
    /**< Input position x for WB pipeline */
    UInt32                 wbPosy;
    /**< Input position y  for WB pipeline */
    System_VideoDataFormat wbInSourceDataFmt;
    /**< output data format of Overlay which feeds wb pipeline */
    System_VideoScanFormat wbScanFormat;
    /**< output Scan format of Overlay which feeds wb pipeline */
    UInt32                 wbFieldMerge;
    /**< Field merge or field separated */
} System_DssWbInputParams;

/**
 *******************************************************************************
 *
 *  \brief Output frame Configuration parameters for DSS WB capture &
 *         processing at create time.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32                 wbWidth;
    /**< Output width in pixels for WB Pipeline.
         For TDA3xx, Must be output 32 pixels aligned */
    UInt32                 wbHeight;
    /**< Output height in pixels for WB Pipeline. */
    System_VideoDataFormat wbDataFmt;
    /**< YUV or RGB data format of wb pipeline output. */
    System_VideoScanFormat wbScanFormat;
    /**< Output Scan Format. For valid values see Fvid2_ScanFormat in
     *   starterware. */
    UInt32                 wbFieldMerge;
    /**< Field merge or field separated */
} System_DssWbOutputParams;

/**
 *******************************************************************************
 *
 *  \brief Structure containing crop configuration - used in Scaler and VCOMP.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 cropStartX;
    /**< Horizontal offset from which picture needs to be cropped. */
    UInt32 cropStartY;
    /**< Vertical offset from which picture needs to be cropped. */
    UInt32 cropWidth;
    /**< Width of the picture to be cropped. */
    UInt32 cropHeight;
    /**< Height of the picture to be cropped. */
} System_CropConfig;

/**
 *******************************************************************************
 *
 *  \brief These are all scaler parameters exposed to the application.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32           bypass;
    /**< Scaler should be bypassed or not. */

    UInt32           nonLinear;
    /**< Flag to indicate whether linear or non-linear scaling is used for
     *   horizontal scaler. Non-linear scaling is available for polyphase
     *   filter only
     *   Example: Scaling from 16/9 aspect ratio to 4/3 aspect ratio.*/

    UInt32           stripSize;
    /**< Size of left and right strip for nonlinear horizontal scaling in terms
     *   of pixel. It must be set to zero for linear horz scaling. */
} System_ScConfig;

/**
 *******************************************************************************
 *
 *  \brief Application interface structure for programming the coefficients.
 *  Structure will be used for all drivers involving scalers.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 hScalingSet;
    /**< Horizontal scaling coefficient set.
     *   For valid values see #System_ScCoeffSet. */
    UInt32 vScalingSet;
    /**< Vertical scaling coefficient set.
     *   For valid values see #System_ScCoeffSet. */
} System_ScCoeffParams;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
