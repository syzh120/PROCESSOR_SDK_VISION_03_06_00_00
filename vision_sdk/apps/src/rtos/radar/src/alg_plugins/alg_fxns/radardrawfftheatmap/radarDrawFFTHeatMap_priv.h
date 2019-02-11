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
 * \file RadarDrawFFTHeatMap_priv.h Radar draw private API/Data structures
 *
 * \brief  This file is a private header file for Radar draw link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of Radar draw link.
 *
 * \version 0.0 (Sept 2016) : [CM] First version
 *
 *******************************************************************************
 */

#ifndef _RADAR_DRAW_FFT_HEATMAP_PRIV_H_
#define _RADAR_DRAW_FFT_HEATMAP_PRIV_H_

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
#include <include/alg_fxns/radarDrawFFTHeatMap_if.h>
#include <include/alg_fxns/radarFFT_if.h>
#include "src/include/draw2d.h"
#include <src/rtos/utils_common/include/utils_dma.h>

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
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams algLinkCreateParams;
    /**< Create params of object draw algorithm link */

    UInt32 outBufferSize;
    /**< output buffer size */

    UInt32 firstTime;
    /**< Flag to indicated whether first frame is received or not */

    Draw2D_BufInfo draw2DBufInfo;
    /**< Buffer info used for drawing */

    Draw2D_Handle draw2DHndl;
    /**< Handle to the draw object */

    Utils_DmaChObj  copyFramesDmaObj;
    /**< DMA object to use when copying input frame to output frame */

    UInt32 backgroundBufAddr;
    /**< Holds the address of the background image that will be copied every
     *   time a new data is recieved and then the objects are copied over this.
     */
    
    UInt32 prevDrawnBufAddr;
    /**< Holds the address of the previously drawn heat map for a given profile
     */
    
    UInt32 currProfileId;
    /**< Current ProfileId being drawn */
} AlgorithmFxn_RadarDrawFFTHeatMap_Obj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

void * AlgorithmFxn_RadarDrawFFTHeatMapCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams);
Int32 AlgorithmFxn_RadarDrawFFTHeatMapProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf);
Int32 AlgorithmFxn_RadarDrawFFTHeatMapControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams);
Int32 AlgorithmFxn_RadarDrawFFTHeatMapDelete(void *alg_handle);

Int32 RadarDrawFFTHeatMap_processData(
    AlgorithmFxn_RadarDrawFFTHeatMap_Obj *pObj,
    System_VideoFrameBuffer *pInBuf,
    System_VideoFrameBuffer *pOutBuf,
    AlgorithmFxn_RadarFftBuffDescriptor *pBufDesc);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
