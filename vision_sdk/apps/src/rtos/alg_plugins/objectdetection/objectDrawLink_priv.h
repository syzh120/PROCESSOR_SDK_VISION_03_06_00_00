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
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file objectDrawLink_priv.h Object Draw Link
 *       private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef _OBJECTDRAW_LINK_PRIV_H_
#define _OBJECTDRAW_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_objectDraw.h>
#include "src/include/draw2d.h"
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <include/alglink_api/algorithmLink_objectDetection.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include "iobjdet_ti.h"
#include "iclr_ti.h"
#include <src/rtos/utils_common/include/utils_link_stats_if.h>
#include <src/rtos/alg_plugins/lanedetection/laneDetectLink_priv.h>
#include <src/rtos/alg_plugins/sparseopticalflow/sparseOpticalFlowLink_priv.h>
#include <src/rtos/alg_plugins/sfm/sfmLink_priv.h>
#include "math.h"

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* Size of different traffic sign icons */
#define OBJECTDRAW_TRAFFIC_SIGN_32x32   0

#define COLOR_RED       (0x4C34FF)
#define COLOR_GREEN     (0x960000)
#define COLOR_BLUE      (0xB3CC00)
#define COLOR_YELLOW    (0xE2009D)
#define COLOR_PURPLE    (0x5EA1F3)

/**
 *******************************************************************************
 *
 *   \brief traffic signs width
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OBJECTDRAW_TRAFFIC_SIGN_WIDTH_1  (32)
/**
 *******************************************************************************
 *
 *   \brief traffic signs height
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OBJECTDRAW_TRAFFIC_SIGN_HEIGHT_1 (32)
/**
 *******************************************************************************
 *
 *   \brief Max number of valid traffic signs
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OBJECTDRAW_TRAFFIC_SIGN_MAX    (27)

/**
 *******************************************************************************
 *
 *   \brief Max number of buffers
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OBJECTDRAW_LINK_MAX_NUM_OUTPUT    (8)

/**
 *******************************************************************************
 *
 *   \brief Thickness of the rectangles drawn around objects
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define OBJECT_RECTANGLE_THICKNESS         (1)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing feature plane computation algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ObjectDrawCreateParams algLinkCreateParams;
    /**< Create params of object draw algorithm link */

    System_Buffer buffers[OBJECTDRAW_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */

    System_VideoFrameBuffer videoBuffers[OBJECTDRAW_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers */

    UInt32 outBufferSize_y;
    /**< output buffer size for Y-plane */

    UInt32 outBufferSize_uv;
    /**< output buffer size for C-plane */

    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Queue*/

    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Queue*/

    Draw2D_BufInfo draw2DBufInfo;
    /**< Buffer info used for drawing */

    Draw2D_Handle draw2DHndl;
    /**< Handle to the draw object */

    Draw2D_LinePrm linePrm;
    /**< Line params for drawing rectangles */

    UInt32                        frameDropCounter;
    /**< Counter to keep track of number of frame drops */

    Utils_DmaChObj  copyFramesDmaObj;
    /**< DMA object to use when copying input frame to output frame */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

    TI_OD_outputList *pOdOutput;

    TI_OD_outputList *pClrOutput;

    AlgorithmLink_LaneDetectOutput *pLdOutput;

    AlgorithmLink_SfmOutput *pSfmOutput;

    strackInfo *pSofOutput;

    UInt32 drawBufAddr[SYSTEM_MAX_PLANES];

    UInt32 laneMinWidth;

    UInt32 laneMaxWidth;

    TI_OD_outputList TIDLOdOutput;

} AlgorithmLink_ObjectDrawObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_objectDrawCreate(void * pObj,
                                              void * pCreateParams);
Int32 AlgorithmLink_objectDrawProcess(void * pObj);
Int32 AlgorithmLink_objectDrawControl(void * pObj,
                                               void * pControlParams);
Int32 AlgorithmLink_objectDrawStop(void * pObj);
Int32 AlgorithmLink_objectDrawDelete(void * pObj);
Int32 AlgorithmLink_objectDrawPrintStatistics(void *pObj,
                AlgorithmLink_ObjectDrawObj *pObjectDrawObj);

Int32 AlgorithmLink_objectDrawCopyTrafficSign(
    UInt8 *bufAddrY,
    UInt8 *bufAddrC,
    UInt32 pitchY,
    UInt32 pitchC,
    UInt32 bufWidth,
    UInt32 bufHeight,
    UInt32 startX,
    UInt32 startY,
    UInt32 trafficSignId,
    UInt32 trafficSignType
    );

Int32 AlgorithmLink_objectDrawCopyTrafficLight(
    UInt8 *bufAddrY,
    UInt8 *bufAddrC,
    UInt32 pitchY,
    UInt32 pitchC,
    UInt32 bufWidth,
    UInt32 bufHeight,
    UInt32 startX,
    UInt32 startY,
    UInt32 trafficLightId,
    UInt32 trafficLightType
    );

void AlgorithmLink_objectDrawConvertHsvToYuv();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
