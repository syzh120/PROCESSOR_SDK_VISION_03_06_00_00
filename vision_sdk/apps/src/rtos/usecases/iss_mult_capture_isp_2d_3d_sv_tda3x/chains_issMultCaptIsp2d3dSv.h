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


#ifndef CHAINS_ISSMULTICAPTISPSIMCOPSRV_H_
#define CHAINS_ISSMULTICAPTISPSIMCOPSRV_H_

#include "chains_issMultCaptIsp2d3dSv_priv.h"
#include <src/rtos/alg_plugins/surroundview/include/svCommonDefs.h>
#include <src/include/chains_common.h>
#include <src/rtos/iss/include/app_util_iss.h>

/* Maximum No of view points */
#define SRV_UC_3D_MAX_NUM_VIEW_POINTS           (200U)

/* SRV Num Views/Channels */
#define SRV_UC_3D_NUM_CAMERAS                   (4U)

/* Parameters of these is used while creating */
#define SRV_UC_3D_DEFAULT_VIEW_TO_USE           (0U)

#define SRV_UC_3D_DEWARP_NUM_OUTPUT_BUFS        (3U)
/**< Number of output buffer that would be allocated at DeWarp */
#define SRV_UC_3D_ISP_NUM_OUTPUT_BUFS           (3U)
/**< Number of output buffer that would be allocated at ISP */

/* Capture Resolution of AR0140 sensor */
#define SRV_UC_3D_CAPT_SENSOR_AR140_WIDTH       (1280U)
#define SRV_UC_3D_CAPT_SENSOR_AR140_HEIGHT      (800U)

/* Capture Resolution of OV10640 sensor */
#define SRV_UC_3D_CAPT_SENSOR_OV10640_WIDTH     (1280U)
#define SRV_UC_3D_CAPT_SENSOR_OV10640_HEIGHT    (720U)

#define SRV_UC_3D_ISP_OUTPUT_WIDTH_W_PAD    (SRV_UC_3D_CAPT_SENSOR_AR140_WIDTH)
#define SRV_UC_3D_ISP_OUTPUT_HEIGHT_W_PAD   (1080U)


/*
 *  2D SRV parameters
 */
/* SRV Car Box Size */
#define SRV_UC_2D_CARBOX_WIDTH              (160U)
#define SRV_UC_2D_CARBOX_HEIGHT             (240U)

/* Output size from SYNTH */
#define SRV_UC_2D_SYNTH_OUTPUT_WIDTH        (720U)
#define SRV_UC_2D_SYNTH_OUTPUT_HEIGHT       (960U)

/* Display parameters */
#define SRV_UC_2D_DISPLAY_STARTX            (16U)
#define SRV_UC_2D_DISPLAY_STARTY            (72U)
#define SRV_UC_2D_DISPLAY_WIDTH             (SRV_UC_2D_SYNTH_OUTPUT_WIDTH)
#define SRV_UC_2D_DISPLAY_HEIGHT            (SRV_UC_2D_SYNTH_OUTPUT_HEIGHT)

/*
 *  3D SRV parameters
 */
/* SRV Car Box Size */
#define SRV_UC_3D_CARBOX_WIDTH              (0U)
#define SRV_UC_3D_CARBOX_HEIGHT             (0U)

/* Maximum output size from LDC / SIMCOP */
#define SRV_UC_3D_LDC_OUTPUT_WIDTH_MAX      (1280U)
#define SRV_UC_3D_LDC_OUTPUT_HEIGHT_MAX     (1080U)

/* Maximum output size from SYNTH */
#define SRV_UC_3D_SYNTH_OUTPUT_WIDTH_MAX    (752U)
#define SRV_UC_3D_SYNTH_OUTPUT_HEIGHT_MAX   (1008U)

/* LDC Frm size and other parameters */
#define SRV_UC_3D_LDC_BLOCK_WIDTH           (16U)
#define SRV_UC_3D_LDC_BLOCK_HEIGHT          (16U)

/* Display parameters */
#define SRV_UC_3D_DISPLAY_STARTX            (SRV_UC_2D_DISPLAY_STARTX + SRV_UC_2D_DISPLAY_WIDTH + 16U)
#define SRV_UC_3D_DISPLAY_STARTY            (72U)
#define SRV_UC_3D_DISPLAY_WIDTH             (752U)
#define SRV_UC_3D_DISPLAY_HEIGHT            (1008U)

/**
 *******************************************************************************
 *
 *  \brief  SRV_UC_3D_LDC_SLICE_PRM
 *
 *        This enum contains the index to the slice parameter set structure
 *        'gLdcSlicePrm'.
 *
 *******************************************************************************
*/
typedef enum
{
    SRV_UC_3D_LDC_SLICE_PRM_1_16x16,
    /* 1 slice with 16x16 block size */
    SRV_UC_3D_LDC_SLICE_PRM_1_16x8,
    /* 1 slice with 16x8 block size */
    SRV_UC_3D_LDC_SLICE_PRM_2_16x16_16x8,
    /* 2 slices with 16x16 and 16x8 block size */
    SRV_UC_3D_LDC_SLICE_PRM_2_16x16_16x4,
    /* 2 slices with 16x16 and 16x4 block size */
    SRV_UC_3D_LDC_SLICE_PRM_1_16x4,
    /* 1 slice with 16x4 block size */
    SRV_UC_3D_LDC_SLICE_PRM_2_16x8_16x4,
    /* 2 slices with 16x8 and 16x4 block size */
    SRV_UC_3D_LDC_SLICE_PRM_3_16x16_16x8_16x4,
    /* 3 slices with 16x16, 16x8 and 16x4 block size */
    SRV_UC_3D_LDC_SLICE_PRM_MAX,
    /* Maximum No of Slice Parameters */
}SRV_UC_3D_LDC_SLICE_PRM;

/**
 *******************************************************************************
 *
 *  \brief  chains_issMultCaptIsp2d3dSv_DisplayAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_issMultCaptIsp2d3dSvObj ucObj;

    AppUtils_Obj                    appObjPrms;

    IssM2mSimcopLink_ConfigParams simcopConfig;
    vpsissldcConfig_t             ldcCfg;
    vpsissvtnfConfig_t            vtnfCfg;
    AlgLink_DeWarpConfigParams    deWarpSimcopCfg;

    UInt32 numCh;
    UInt32  captureOutWidth;
    UInt32  captureOutHeight;
    UInt32  displayWidth;
    UInt32  displayHeight;

    Chains_Ctrl *chainsCfg;


    Bool bypassVtnf;
    Bool bypassLdc;

    AlgorithmLink_SrvCommonViewPointParams \
        algViewParams[SRV_UC_3D_MAX_NUM_VIEW_POINTS];
    System_VideoFrameCompositeBuffer \
        ldcMeshTableContainer[SRV_UC_3D_MAX_NUM_VIEW_POINTS];

    UInt32  freeToSwitch;
    UInt32  numViewPoints;

    BspOsal_SemHandle startSrvDemo;
    /**< Synchronization sempahore used to signal start computing LDC LUTs */
    BspOsal_TaskHandle mediaTaskHndl;
    /**< Media task handle */

    AlgLink_DeWarpSaveFrame deWarpSaveFrame;

    UInt32 lutIdxFilePresent;
    /**< Flag to indicate if LUT Index file is present on MMCSD card */
    UInt32 v2WIdxFilePresent;
    /**< Flag to indicate if View to World Index file is present on
        MMCSD card */
    Bool useUserBlendTable3DLDC;
    /**< Flag for using the user Blend Table */

} chains_issMultCaptIsp2d3dSv_DisplayAppObj;

Void chains_issMultCaptIsp2d3dSv_MediaTask(UArg arg1, UArg arg2);
/**< Task to interface to media */
Int32 chains_issMultCaptIsp2d3dSv_FreeBufs(void);

#endif /* CHAINS_ISSMULTICAPTISPSIMCOPSRV_H_ */
