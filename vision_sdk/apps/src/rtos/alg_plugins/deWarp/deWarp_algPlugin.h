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
 * \ingroup ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_DEWARP : Algorithm implementation private include
 *
 * @{
 */


#ifndef DEWARP_ALG_PLUGIN_PRIV_H_
#define DEWARP_ALG_PLUGIN_PRIV_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/alglink_api/algorithmLink_deWarp.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>
#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <src/rtos/utils_common/include/utils_cbuf_ocmc.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Indicates the default number of output buffers to be used
 *******************************************************************************
*/
#define ALG_LINK_DEWARP_NUM_BUFS_PER_CH_DEFAULT (3U)

/**
 ******************************************************************************
 * \brief Maximum number of output frames allocated per channel
 ******************************************************************************
 */
#define ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH     (SYSTEM_LINK_MAX_FRAMES_PER_CH)


/**
 ******************************************************************************
 *
 * \brief Maximum number of output frames that could be allocated
 *
 ******************************************************************************
 */
#define ALG_PLUGIN_DEWARP_MAX_FRAMES (ALG_LINK_DEWARP_MAX_CH * \
                                      ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH)

/**
 *******************************************************************************
 * \brief In Valid View ID marker.
 *******************************************************************************
 */
#define ALG_PLUGIN_DEWARP_INVALID_VIEW_ID (0x7FFFFFFFU)

/**
 *******************************************************************************
 * \brief Maximum Output Width.
 *******************************************************************************
 */
#define ALG_PLUGIN_DEWARP_MAX_OUT_WIDTH (1280U)

/**
 *******************************************************************************
 * \brief Pitch alignment
 *******************************************************************************
 */
#define ALG_PLUGIN_DEWARP_PITCH_ALIGNMENT (16U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure containing attributes of each channel
 *
 *******************************************************************************
*/
typedef struct {

    vpsissSimcopCfgPrms_t   drvSimcopCfg;
    /**< SIMCOP configuration parameters */
    Fvid2_Handle            drvHandle;
    /**< FVID2 driver handle. */

    UInt32                  outBufSize;
    /**< Size of output buffer, used to track the allocated size per channel */
    /* Used, when applications require to DUMP a output frame into local memory,
        Apps, later could fetch it */
    UInt8                   *saveFrameBufAddr;
    /**< Frame buffer used for saving captured frame */
    volatile UInt32         saveFrame;
    /**< Flag to indicate dumping of frame is in progress */

    /* Input Frame parameters */
    UInt32          inputFrameWidth;
    /** < Width */
    UInt32          inputFrameHeight;
    /** < Height */
    UInt32          inputFramePitch[SYSTEM_MAX_PLANES];
    /** < Pitch */
    /* Output Frame parameters */
    UInt32          outputFrameWidth;
    /** < Width */
    UInt32          outputFrameHeight;
    /** < Height */
    UInt32          outputFramePitch[SYSTEM_MAX_PLANES];
    /** < Pitch */

    UInt32          xPad;
    /** < x pad */

    UInt32          yPad;
    /** < y pad */

    UInt32 ocmcLdcLutAddr;
    /** < This is the OCMC RAM address where LDC LUTs are copied into */

} AlgPluginDeWarpChObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing information for each instance of DeWarp Plugin
 *
 *******************************************************************************
*/
typedef struct {

    BspOsal_SemHandle           drvFrameProcessed;
    /**< Semaphore for tracking process call of the driver */

    AlgLink_DeWarpCreateParams  createArgs;
    /**< Create params link */


    AlgorithmLink_InputQueueInfo    inputQInfo;
    /**< All the information about input Queue*/
    AlgorithmLink_OutputQueueInfo   outputQInfo;
    /**< All the information about output Queue*/


    AlgPluginDeWarpChObj            chObj[ALG_LINK_DEWARP_MAX_CH];
    /**< Attributes for operating each channel */
    UInt32                          numInputCh;
    /**< Number of input channels */
    Void *pPrevOutBuffer;
    /**< Previous frame's output to be given as reference input frame,
            to process next frame. This will hold a composite buffers describing
            previous output */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool    isFirstFrameRecv;
    /**< Flag to activate stats collection*/
    UInt32  activeViewPointId;
    /**< Used to track the current selected view point */

    System_Buffer sysBuffers[ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH];
    /**< System buffer that would hold composite output buffers. */
    System_VideoFrameCompositeBuffer
                            compBuffers[ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH];
    /**< Composite Buffer that would hold output of each channel */
    System_VideoFrameBuffer frameBuffers[ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH];
    /**< Composite Buffer that would hold output of each channel */
    UInt32 outBufSize[ALG_PLUGIN_DEWARP_MAX_FRAMES_PER_CH];
    /**< Keep track of size of allocated memory */

    UInt32 processedFrameCount;
    /**< Number of frames processed by this plugin */

    UInt32 fillBuf;
    /**< Fill Buffer address */

    UInt32 fillBufUV;
    /**< Fill Buffer UV address */

    AlgorithmLink_SrvCommonViewPointParams *curViewParams;
    /**< Pointer to the current view point parameter structure */

    Utils_DmaChObj          dumpFramesDmaObj;
    /**< DMA parameters used to dump a frame. Essentially a output frame is
            copied (DMA) into spare buffer */

} AlgLink_DeWarpObj;


#endif /* DEWARP_ALG_PLUGIN_PRIV_H_ */

/* @} */
