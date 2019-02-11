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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
 * \ingroup RADAR_DRAW_API
 * \defgroup RADAR_DRAW_IMPL Radar draw Implementation
 *
 * @{
 *
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \file RadarDraw_priv.h Radar draw private API/Data structures
 *
 * \brief  This file is a private header file for Radar draw link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of Radar draw link.
 *
 * \version 0.0 (Sept 2016) : [PG] First version copied from grpx link radar
 *
 *******************************************************************************
 */

#ifndef _RADAR_DRAW_PRIV_H_
#define _RADAR_DRAW_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <include/link_api/system_common.h>
#include <src/include/draw2d.h>
#include <include/alg_fxns/radarDraw_if.h>
#include <include/alg_fxns/radarBeamForm_if.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include "math.h"


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Draw link size of string
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define RADAR_DRAW_STR_SZ (128)

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
    AlgorithmFxn_RadarDrawCreateParams algLinkCreateParams;
    /**< Create params of object draw algorithm link */

    UInt32 outBufferSize_y;
    /**< output buffer size for Y-plane */

    Draw2D_BufInfo draw2DBufInfo;
    /**< Buffer info used for drawing */

    Draw2D_Handle draw2DHndl;
    /**< Handle to the draw object */

    Utils_DmaChObj  copyFramesDmaObj;
    /**< DMA object to use when copying input frame to output frame */

    UInt32 drawBufAddr[SYSTEM_MAX_PLANES];

    UInt32 backgroundBufAddr;
    /**< Holds the address of the background image that will be copied every
     *   time a new data is recieved and then the objects are copied over this.
     */
    UInt32 prevDrawnBuffer;
    /**< Holds the address of the background image that will be copied every
     *   time a new data is recieved and then the objects are copied over this.
     */
    UInt32 currProfileId;
    /**< Current Profile Id being displayed */
    UInt32 pitch;
    /**< Pitch of the output buffer */
    UInt32 centerX;
    /**< Center of the sector for the radar object detection output */
    UInt32 centerY;
    /**< Center of the sector for the radar object detection output */
    UInt32 radius;
    /**< Radius of the sector for the radar object detection output */
    UInt32 angle;
    /**< Angle of the sector for the radar object detection output */
    UInt32 scale;
    /**< Scale of the sector for the radar object detection output */

    AlgorithmFxn_RadarBeamFormBuffDescriptor* detectedObjs;
    /**< Radar object detection output parameters */

} AlgorithmFxn_RadarDrawObj;

typedef struct
{
    UInt32    distance;
    /**< Distance to radar sensor , in cm */
    Int32    angle;
    /**< Azimuth angle to the radar sensor  */
    Int32    relSpeed;
    /**< Relative speed of the target  */
} RadarDraw_targetInformation;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

void * AlgorithmFxn_RadarDrawCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams);
Int32 AlgorithmFxn_RadarDrawProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf);
Int32 AlgorithmFxn_RadarDrawControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams);
Int32 AlgorithmFxn_RadarDrawDelete(void *alg_handle);

Int32 RadarDraw_drawRadarObjects(AlgorithmFxn_RadarDrawObj *pObj);

Void RadarDraw_setBRadarScopePrinted(Bool value);

Void RadarDraw_setBRadarTargetUpdated(Bool value);

Int32 RadarDraw_drawSectorLines(AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 length,
                    UInt32 degree
                    );


Void RadarDraw_drawPartCircle(AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 x,
                    UInt32 y,
                    UInt32 radius,
                    UInt32 degrees
                    );

Void RadarDraw_drawLabels(AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 x,
                    UInt32 y,
                    UInt32 radius,
                    UInt32 degrees);

Int32 RadarDraw_drawCpuLoad(AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 x, UInt32 y,
                    UInt32 barWidth,
                    UInt32 barHeight,
                    UInt32 padX,
                    UInt32 padY,
                    UInt32 fontIdx
                    );

Void RadarDraw_plotTarget(AlgorithmFxn_RadarDrawObj *pObj,
        Int32 x,
        Int32 y,
        Int32 radius,
        RadarDraw_targetInformation *pTarget );

Void RadarDraw_drawLabel(
        AlgorithmFxn_RadarDrawObj *pObj,
        UInt32 x,
        UInt32 y,
        char *text, UInt32 fontId);


Void RadarDraw_drawClusterBox(
                    AlgorithmFxn_RadarDrawObj *pObj,
                    UInt32 startX,
                    UInt32 startY,
                    UInt32 width,
                    UInt32 height,
                    UInt32 colorSelection);

void RadarDraw_sinFillTable(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
