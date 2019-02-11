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
 * \file drawRearviewLink_priv.h Frame Copy Algorithm Link private
 *                            API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef _DRAWREARVIEW_LINK_PRIV_H_
#define _DRAWREARVIEW_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_drawRearview.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include "iDrawRearviewAlgo.h"
#include "src/include/draw2d.h"
#include <src/rtos/utils_common/include/utils_link_stats_if.h>
#include <math.h>
#include <float.h>
#include "src/rtos/utils_common/include/utils_dma.h"


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max number of video frames needed for frame copy algorithm
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DRAWREARVIEW_LINK_MAX_FRAMES (10)
#define COLOR_RED       (0x4C34FF)
#define COLOR_GREEN     (0x960000)
#define COLOR_BLUE      (0xB3CC00)
#define COLOR_YELLOW    (0xE2009D)
#define COLOR_PURPLE    (0x5EA1F3)


#define REDLINE_YMAX 150
#define YELLINE_YMAX 300
#define REDLINE_YMAX_Proj -1*(REDLINE_YMAX/((0.003378*(REDLINE_YMAX))+1)) + 488
#define YELLINE_YMAX_Proj -1*(YELLINE_YMAX/((0.003378*(YELLINE_YMAX))+1)) + 488
#define PROJXPASS	642
#define PROJYPASS	276
#define PROJXDRIVER 308
#define PROJYDRIVER 276
#define Y0 488

//#define ELLIPSISSTEERTINGMODEL  (1)
#define ACKERMANNSTEERTINGMODEL (1)
#define DISCRETE_RES		   500


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct {

    Bool isFirstTime; /* Are we invoking the Ultrasonic draw API for this first time */
    Bool displayTopView;
    UInt32 state;
    UInt32 prevState;
    UInt32 delay;

    Int32 aLong;            // Variable for ellipse steering model

    Int32 steeringAngle;
    Bool turningDir;		// TRUE = Right Turn; FALSE = Left Turn
    Bool drawBuf;
    /* If TRUE will draw from Buffer arrays below, else generate points, fill buffer, then draw*/
    short iDriver;
    short iPass;
    Int32 xDriverBuf[DISCRETE_RES];
    Int32 yDriverBuf[DISCRETE_RES];
    Int32 xPassBuf[DISCRETE_RES];
    Int32 yPassBuf[DISCRETE_RES];

} AlgorithmLink_RearviewOverlayDrawObj;

/**
 *******************************************************************************
 *
 *   \brief Structure containing frame copy algorithm link specific parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    Alg_drawRearview_Obj         * algHandle;
    /**< Handle of the algorithm */
    UInt32                      pitch;
    /**< Pitch of output video frames. This is kept same for all channels*/
    System_LinkOutQueParams     outQueParams;
    /**< Output queue information */
    System_LinkInQueParams      inQueParams;
    /**< Input queue information */
    UInt32                      numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo           inputChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */
    AlgorithmLink_drawRearviewCreateParams algLinkCreateParams;
    /**< Create params of the frame copy algorithm Link*/
    Alg_drawRearviewCreateParams   createParams;
    /**< Create params of the frame copy algorithm */
    Alg_drawRearviewControlParams  controlParams;
    /**< Control params of the frame copy algorithm */

    AlgorithmLink_RearviewOverlayDrawObj rearViewOverlayDrawObj;

    Draw2D_BufInfo draw2DBufInfo;
    /**< Buffer info used for drawing */

    Draw2D_Handle draw2DHndl;
    /**< Handle to the draw object */

    Draw2D_LinePrm linePrm;
    /**< Line params for drawing rectangles */

    UInt32 drawBufAddr[SYSTEM_MAX_PLANES];

    System_Buffer buffers[SYSTEM_MAX_CH_PER_OUT_QUE]
                         [DRAWREARVIEW_LINK_MAX_FRAMES];
    /**< System buffer data structure to exchange buffers between links */
    System_VideoFrameBuffer videoFrames[SYSTEM_MAX_CH_PER_OUT_QUE]
                                       [DRAWREARVIEW_LINK_MAX_FRAMES];
    /**< Payload for System buffers */
    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Q */
    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Q */
    UInt32                      frameDropCounter;
    /**< Counter to keep track of number of frame drops */

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


} AlgorithmLink_drawRearviewObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_drawRearviewCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_drawRearviewProcess(void * pObj);
Int32 AlgorithmLink_drawRearviewControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_drawRearviewStop(void * pObj);
Int32 AlgorithmLink_drawRearviewDelete(void * pObj);
Int32 AlgorithmLink_drawRearviewPrintStatistics(void *pObj,
                       AlgorithmLink_drawRearviewObj *pdrawRearviewObj);

Int32 AlgorithmLink_drawOverlaysRun(AlgorithmLink_drawRearviewObj *pObj);
void  AlgorithmLink_drawEllipsis(AlgorithmLink_drawRearviewObj *pObj, double aPass, double bPass, double aDriver, double bDriver);
void  AlgorithmLink_drawAckermannSteering(AlgorithmLink_drawRearviewObj *pObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
