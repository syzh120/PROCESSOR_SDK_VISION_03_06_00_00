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
 * \ingroup GRPX_SRC_LINK_API
 * \defgroup GRPX_SRC_LINK_IMPL Grpx Src Link Implementation
 *
 * @{
 *
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \file GrpxSrcLink_priv.h Grpx Src Link private API/Data structures
 *
 * \brief  This file is a private header file for grpx src link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of grpx src link.
 *
 * \version 0.0 (Oct 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef _GRPX_SRC_LINK_PRIV_H_
#define _GRPX_SRC_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/rtiLink.h>
#ifndef RADAR_ONLY
#include <include/alglink_api/algorithmLink_ultrasonicFusion.h>
#endif

#include <src/include/draw2d.h>
#include <src/include/link_stats_monitor.h>
#include <src/rtos/utils_common/include/utils_prf.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Maximum number of grpx src link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_OBJ_MAX    (2)

/**
 *******************************************************************************
 *
 * \brief Max Number of buffers this link uses
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_MAX_OUT_FRAMES   (SYSTEM_LINK_FRAMES_PER_CH)

/**
 *******************************************************************************
 *
 * \brief Number of buffers this link uses
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_OUT_FRAMES       (1)

/**
 *******************************************************************************
 *
 * \brief Interval at which stats have to be calculated in Msec
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_LOAD_REFRESH_INTERVAL_MSEC (2000)

/**
 *******************************************************************************
 *
 * \brief Interval at which GrpxSrcLink processing happens
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define GRPX_SRC_LINK_PROCESS_INTERVAL_MSEC (10)

/* String size for prints */
#define GRPX_SRC_LINK_STR_SZ (128)


typedef enum {

    GRAPHICS_SRC_LINK_PROFILER_NOT_RUNNING,
    /**< Profiler not Running */

    GRAPHICS_SRC_LINK_PROFILER_RUNNING
    /**< Profiler Running */

}GraphicsLink_ProfilerState;

typedef enum {

    GRAPHICS_SRC_LINK_START_PROFILER,
    /**< Command to start profiler */

    GRAPHICS_SRC_LINK_STOP_PROFILER,
    /**< Command to stop profiler */

    GRAPHICS_SRC_LINK_RESET_PROFILER
    /**< Command to reset profiler */

}GraphicsLink_ProfilerCommands;

typedef enum {

    GRAPHICS_SRC_LINK_STRPRINT_INACTIVE,
    GRAPHICS_SRC_LINK_STRPRINT_PRINTSTR,
    GRAPHICS_SRC_LINK_STRPRINT_ACTIVE,
    GRAPHICS_SRC_LINK_STRPRINT_CLEARSTR
} GraphicsLink_StringPrintState;
/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
typedef struct {

    Bool isFirstTime; /* Are we invoking the Ultrasonic draw API for this first time */
    UInt32 startTime;
    UInt32 refreshInterval;
    Utils_DmaChObj dmaObj;
    UInt32 backgroundBufAddr;
    Utils_DmaCopyFill2D backgroundDmaPrm;
} GrpxSrcLink_MetaDataDrawObj;

typedef struct {

    Bool isFirstTime; /* Are we invoking the Ultrasonic draw API for this first time */
    Bool displayTopView;
    Utils_DmaChObj dmaObj;
    UInt32 topViewLeftBufAddr;
    UInt32 topViewRightBufAddr;
    UInt32 rearViewLeftBufAddr;
    UInt32 rearViewRightBufAddr;
    UInt32 topViewLeftBlankBufAddr;
    UInt32 topViewRightBlankBufAddr;
    UInt32 rearViewLeftBlankBufAddr;
    UInt32 rearViewRightBlankBufAddr;
    Utils_DmaCopyFill2D topViewLeftDmaPrm;
    Utils_DmaCopyFill2D topViewRightDmaPrm;
    Utils_DmaCopyFill2D rearViewLeftDmaPrm;
    Utils_DmaCopyFill2D rearViewRightDmaPrm;
    Utils_DmaCopyFill2D topViewLeftBlankDmaPrm;
    Utils_DmaCopyFill2D topViewRightBlankDmaPrm;
    Utils_DmaCopyFill2D rearViewLeftBlankDmaPrm;
    Utils_DmaCopyFill2D rearViewRightBlankDmaPrm;
} GrpxSrcLink_RearviewOverlayDrawObj;

typedef struct {
    Utils_BufHndl bufOutQue;
    /**< Output buffer queue */

    System_Buffer buffers[GRPX_SRC_LINK_MAX_OUT_FRAMES];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[GRPX_SRC_LINK_MAX_OUT_FRAMES];
    /**< Payload for System buffers */

    Fvid2_Frame frames[GRPX_SRC_LINK_MAX_OUT_FRAMES];
    /**< Fvid2_frames to hold buffers */

    UInt32 numFrames;
    /**< Number of output buffers, must be <= GRPX_SRC_LINK_MAX_OUT_FRAMES */

    Fvid2_Format format;
    /**< Format object used for buffer creation */

}GrpxSrcLink_OutObj;

typedef struct {

    Utils_SystemLoadStats systemLoadStats[SYSTEM_PROC_MAX];
    /**< Load object for each processor in the system */

    UInt32                profilerState;
    /**< Variable to keep track of profiler state */

    UInt32                refreshInterval;
    /**< Variable to control load calculation period in Msec */

    UInt32                startTime;
    /**< Varaile to hold stats start time */


}GrpxSrc_StatsDisplayObj;


typedef struct
{
    GraphicsLink_StringPrintState    stringPrintState;
    /**< State of stirng print  */
    Int32  remainingDuration;
    /**< Time in ms that specified string needs to be dispalyed */
    GrpxSrcLink_StringInfo stringInfo;
    /**< String to be displayed */
} GrpxSrcLink_StringRunTimePrintObj;
/**
 *******************************************************************************
 *
 * \brief Structure to hold all grpx Src link related information
 *
 *******************************************************************************
 */

typedef struct {
    UInt32 tskId;
    /**< Placeholder to store grpx src link task id */

    char name[32];
    /**< Link name */

    Utils_TskHndl tsk;
    /**< Handle to grpx src link task */

    GrpxSrcLink_CreateParams createArgs;
    /**< Create params for grpx src link */

    System_LinkInfo prevLinkInfo;
    /**< previous link information */
    System_LinkInfo info;
    /**< Output queue information of this link */

    GrpxSrcLink_OutObj outObj;
    /**< Data structure to hold output information */

    Bool isFirstProcessCall;

    GrpxSrc_StatsDisplayObj statsDisplayObj;
    GrpxSrcLink_MetaDataDrawObj metaDataDrawObj;
    GrpxSrcLink_RearviewOverlayDrawObj rearViewOverlayDrawObj;
    Draw2D_Handle draw2DHndl;

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by capture link */

    Bool isLinkStarted;

    Bool isNewDataCmdSendOut;

    GrpxSrcLink_StringRunTimePrintObj stringPrintInfo;
    /**< String info to be printed */


}GrpxSrcLink_Obj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

Int32 GrpxSrcLink_drawSurroundViewEdgeDetectLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displaySurroundViewEdgeDetectStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawOpticalFlowLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displayOpticalFlowDetectStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawStereoDisparityLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displayStereoDisparityStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawStereoDisparityMultiFCAlgLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displayStereoDisparityMultiFCAlgStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawCpuLoad(GrpxSrcLink_Obj *pObj,
                    UInt32 x, UInt32 y,
                    UInt32 barWidth,
                    UInt32 barHeight,
                    UInt32 padX,
                    UInt32 padY,
                    UInt32 fontIdx
                    );

Int32 GrpxSrcLink_drawPdTsrLdLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displayPdTsrLdStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawPdTsrLdSofLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displayPdTsrLdSofStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawPdTsrLdSofStereoLayout(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displayPdTsrLdSofStereoStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawSurroundViewSOFLayout(GrpxSrcLink_Obj *pObj,
                                            System_LinkChInfo *pChInfo);

Int32 GrpxSrcLink_display3DSurroundViewStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displaySurroundViewSOFStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawSurroundViewStandaloneLayout(GrpxSrcLink_Obj *pObj,
                                                    UInt32 disablePreview);

Int32 GrpxSrcLink_drawSurroundViewStandaloneLayout2(GrpxSrcLink_Obj *pObj,
                                                    UInt32 disablePreview);

Int32 GrpxSrcLink_drawFcAnalytics2Layout(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawFcAnalytics2DrawLegend(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_displaySurroundViewStandaloneStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawSfMLayout(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_displaySfMStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawStereoCalibLayout(
        GrpxSrcLink_Obj *pObj,
        GrpxSrcLink_StereoCalibDisplayPrm pStereoCalibDisplayPrm);

Int32 GrpxSrcLink_displayStereoCalibStats(
        GrpxSrcLink_Obj *pObj,
        GrpxSrcLink_StereoCalibPrm *pStereoCalibPrm);

Int32 GrpxSrcLink_drawMetaDataResultsCreate(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawMetaDataResultsRun(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawMetaDataResultsDelete(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawTDA3x3DSVLayout(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawTDA3xRearView3DSVLayout(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawTDA3x2D3DSVLayout(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_displayTDA3x3DSVStats(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_displayTDA3xRearView3DSVStats(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_displayTDA3x2D3DSVStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawOverlaysCreate(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawOverlaysRun(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_drawOverlaysDelete(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawSrvCalibLayout(
                    GrpxSrcLink_Obj *pObj,
                    System_LinkChInfo *pChInfo,
                    UInt32 capWidth,
                    UInt32 capHeight);
Int32 GrpxSrcLink_displaySrvCalibStats(
                        GrpxSrcLink_Obj *pObj,
                        GrpxSrcLink_SrvCalibPrm *pSrvCalibPrm);

Int32 GrpxSrcLink_drawRearViewPanoramaLayout(GrpxSrcLink_Obj *pObj);
Int32 GrpxSrcLink_displayRearViewPanoramaStats(GrpxSrcLink_Obj *pObj);

Int32 GrpxSrcLink_drawSemSegLayout(
                    GrpxSrcLink_Obj *pObj,
                    UInt32 capWidth,
                    UInt32 capHeight);

Int32 GrpxSrcLink_drawtidlOdLayout(
                    GrpxSrcLink_Obj *pObj,
                    UInt32 capWidth,
                    UInt32 capHeight);

void GrpxSrcLink_drawISPLoad(Utils_SystemLoadStats *loadStats);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

