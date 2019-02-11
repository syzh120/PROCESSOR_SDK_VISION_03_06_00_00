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
 * \file chains_common_srv_calib.h
 *
 * \brief This file contains common utility functions used by SV use cases
 *
 *******************************************************************************
 */

#ifndef _CHAINS_COMMON_SRV_CALIB_H_
#define _CHAINS_COMMON_SRV_CALIB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <include/alglink_api/algorithmLink_srvCommon.h>
#include <include/alglink_api/algorithmLink_geometricAlignment.h>
#include <include/alglink_api/algorithmLink_geometricAlignment3D.h>
#include <include/alglink_api/algorithmLink_synthesis.h>
#include <include/link_api/lz4CompDecomp.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#ifdef TDA3XX_128MB_DDR
#define SYSTEM_LINK_ID_LZ4_DSP                  (SYSTEM_LINK_ID_DSP1)
#else
#define SYSTEM_LINK_ID_LZ4_DSP                  (SYSTEM_LINK_ID_DSP2)
#endif
#define SRV_NUM_CAMERAS                         (SRV_NUM_VIEWS)

#define SRV_LDC_OUTPUT_WIDTH_MAX                (1280U)
#define SRV_LDC_OUTPUT_HEIGHT_MAX               (1080U)

#define SRV_LDC_LUT_FRM_WIDTH                   (SRV_LDC_OUTPUT_WIDTH_MAX)
#define SRV_LDC_LUT_FRM_HEIGHT                  (SRV_LDC_OUTPUT_HEIGHT_MAX)

#define SRV_TDA2X_CAPTURE_WIDTH                 (1280U)
#define SRV_TDA2X_CAPTURE_HEIGHT                (720U)

#define SRV_TDA2X_CAPTURE_WIDTH_2MP             (1920U)
#define SRV_TDA2X_CAPTURE_HEIGHT_2MP            (1080U)

#define SRV_FILENAME_MAX_SIZE                   (1024U)

#define SRV_DIR_3X                              "TDA3X"
#define SRV_DIR_2X                              "TDA2X"
#define SRV_DIR_2PX                             "TDA2PX"
#define SRV_FILENAME_LUT                        "LUT.BIN"
#define SRV_FILENAME_LUTIDX                     "LUT_IDX.BIN"
#define SRV_FILENAME_SET_LUT                    "LUT_SET.BIN"
#define SRV_FILENAME_SET_LUTIDX                 "LUT_SET_IDX.BIN"
#define SRV_FILENAME_V2W                        "V2W.LZ4"
#define SRV_FILENAME_V2WIDX                     "V2W_IDX.BIN"
#define SRV_FILENAME_CARIMG                     "CARIMG.BIN"
#define SRV_FILENAME_CARIMGIDX                  "CARIMG_IDX.BIN"
#define SRV_IMG_FILE_FRONT                      "FRONT"
#define SRV_IMG_FILE_RIGHT                      "RIGHT"
#define SRV_IMG_FILE_BACK                       "BACK"
#define SRV_IMG_FILE_LEFT                       "LEFT"
#define SRV_CALMAT_FILE                         "CALMAT.BIN"
#define SRV_PERSMAT_FILE                        "PERSMAT.BIN"
#define SRV_CHARTPOS_FILE                       "CHARTPOS.BIN"
#define SRV_DISPLAYFRAME_FILE                   "DIS_FR.YUV"
#define SRV_FILENAME_GPULUT                     "GPULUT.BIN"

#define SRV_MEDIA_SIZE_HEADER                   (1024U)
#define SRV_MEDIA_SIZE_MAXIDX                   (10U * 1024U)
#define SRV_MEDIA_SIZE_METADATA                 (128U)
#define SRV_LDC_VIEW2WORLDMESH_MAX_SIZE         (150U * 1024U)
#define SRV_LDC_CARIMAGE_MAX_SIZE               (1U * MB)
#define SRV_CALMAT_SIZE                         (12U * 4U)
#define SRV_PERSMAT_SIZE                        (9U * 4U)
#define SRV_FILEWRITE_CHUNKSIZE                 (96U * 1024U)   /* Bytes */
#define SRV_FILEREAD_CHUNKSIZE                  (100U * 1024U)  /* Bytes */
#define SRV_CHARTPOS_SIZE                       (256U)
#define SRV_CORNERPOINT_SIZE                    (1024U)
#define SRV_MEDIA_IDX_SET_SIZE_OFFSET           (3U)
/*
 *  For 128 MB DDR build the persistent memory size is
 *  reduced to 8 MB.
 */
#ifndef TDA3XX_128MB_DDR
    #define SRV_PERSISTENT_BUF_SIZE             (25U * MB)
#else
    #define SRV_PERSISTENT_BUF_SIZE             (8U * MB)
#endif

#define SRV_SRCATCH_BUF_SIZE                    (1U * MB)
#define SRV_3D_LDC_SUB_SAMPLE_RATIO             (8U)
#define SRV_3D_GPU_SUB_SAMPLE_RATIO             (4U)

#ifdef LINUX_BUILD
    #define GA_OUTPUT_LUT_FLASHMEM_OFFSET           (01 * 1024 * 1024)

#ifdef ANDROID
    #define CALIBDATA_FILENAME                      "/data/infoadas/.calibtable"
#else
    /* Is this path valid for both NFS and SD as storage media? */
    #define CALIBDATA_FILENAME                      "/home/root/.calibtable"
#endif
#elif defined(QNX_BUILD)
    #define GA_OUTPUT_LUT_FLASHMEM_OFFSET           (0)
    #define CALIBDATA_FILENAME                      "/tmp/.calibtable"
#else
    #define GA_OUTPUT_LUT_FLASHMEM_OFFSET           (20 * 1024 * 1024)
#endif
#define GA_OUTPUT_LUT_SIZE                          (10 * 1024 * 1024)

#define GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET       (GA_OUTPUT_LUT_FLASHMEM_OFFSET + GA_OUTPUT_LUT_SIZE)
#define GA_PERSPECTIVE_MATRIX_SIZE                  (64 * 1024)

#if defined(LINUX_BUILD) || defined(QNX_BUILD)
    #define GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D    (GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET + GA_PERSPECTIVE_MATRIX_SIZE)
    #define GA_PERSPECTIVE_MATRIX_SIZE_2D               (64 * 1024)
#else
    #define GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET_2D    (GA_PERSPECTIVE_MATRIX_FLASHMEM_OFFSET)
    #define GA_PERSPECTIVE_MATRIX_SIZE_2D               (GA_PERSPECTIVE_MATRIX_SIZE)
#endif

#define GA_OUTPUT_LUT_SIZE_MEM_ALLOC                (20 * 1024 * 1024)
#define GA_FEATURE_PT_SIZE                          (1 * 1024)

#define GA_MAGIC_PATTERN_SIZE_IN_BYTES              (4)
#define GA_OUTPUT_LUT_MAGIC_SEQUENCE                (0x1234ABCD)
#define GA_PERSPECTIVE_MATRIX_MAGIC_SEQUENCE        (0xABCD1234)

/* LDC Slice Calculation parameters */
#define SRV_LDC_TDA3X_MAX_INBLK_SIZE                (5120)
#define SRV_LDC_MAX_NUM_SLICES                      (3)

/* For YUV420SP format the min block width is 16 */
#define SRV_LDC_BLK_WIDTH_0                         (16)
#define SRV_LDC_BLK_WIDTH_1                         (16)
#define SRV_LDC_BLK_WIDTH_2                         (16)

/* Block Height can be any even number */
#define SRV_LDC_BLK_HEIGHT_0                        (16)
#define SRV_LDC_BLK_HEIGHT_1                        (8)
#define SRV_LDC_BLK_HEIGHT_2                        (2)

/*******************************************************************************
 *  Structures and enums
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enum for Calibration Type
 *
 *******************************************************************************
*/
typedef enum
{
    SRV_CALIB_TYPE_AUTO,
    SRV_CALIB_TYPE_MANUAL

} SRV_CALIB_TYPE;

/**
 *******************************************************************************
 *
 *  \brief  SV_MEDIA_FILE
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef enum
{
    SRV_MEDIA_FILE_LUT,
    SRV_MEDIA_FILE_V2W,
    SRV_MEDIA_FILE_VIEWPOINT_ZERO

}SRV_MEDIA_FILE;



/**
 *******************************************************************************
 *
 *  \brief  Chain_Common_SRV_CalibrationPrm
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32  numCh;
    UInt32 captureOutWidth;
    UInt32 captureOutHeight;
    AlgorithmLink_SrvCommonViewPointParams algViewParams;
    System_VideoFrameCompositeBuffer ldcMeshTableContainer;
    AlgorithmLink_lutGenPrm_3DSRV gAlignGenLutPrm3DSrv;
    AlgorithmLink_calMatGenPrm_3DSRV calMatGenPrm3DSrv;
    AlgorithmLink_update2DPersMatPrm update2DPersMat;
    AlgorithmLink_blenTableGenPrm blendTableGenPrm;
    Bool isCalMatGenerated;
    Int8 *inChartPosBuf;
    Ptr saveFrameSync;
    Bool saveFrame;
    UInt32 saveFrameChId;
    UInt16 *gpuLut3DBuf;
    UInt32 gpuLutSize;
    float *gpuLut3D_XYZBuf;
    UInt32 gpuLutXYZSize;
    float *gpuLut3D_undistBuf;
    UInt32 gpuLutundistSize;
    UInt8 binarizationMode;
    UInt8 thresholdMode;
    UInt8 windowMode;
    UInt8 Ransac;
    UInt8 PoseRansac;
    UInt8 SingleChartPose;
    lz4CompDecomp_inp toBeCompressed;
    Bool is2mp;
} Chain_Common_SRV_CalibrationPrm;

/**
 *******************************************************************************
 *
 *  \brief  Chain_Common_SRV_mediaObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 *v2wIdxBuf;
    /*V2W Index buffer*/

    UInt8 *v2wBuf;
    /*uncompressed v2w Table buffer*/

    UInt32 v2wBufSize;
    /*uncompressed v2w Table buffer size*/

    UInt32 *carImgIdxBuf;
    /*CarImage IDX buffer*/

    UInt8 *carImgBuf;
    /* uncompresssed carImage Buffer*/

    UInt32 carImgBufSize;
    /* uncompresssed carImage Buffer Size*/

    UInt32 *ldcIdxBuf;
    /* LDC LUT IDX buffer */

    UInt8 *ldcBuf;
    /*LDC LUT + Blend Table Buffer*/

    UInt32 ldcBufSize;
    /*LDC LUT + Blend Table Buffer Size*/

    Int32 fplutSet[100];
    /*Collection of file pointers for the LDC LUT SETS*/

    Int32 fpLutIdxFile;
    /* New LDC IDX file pointer*/

    UInt8 *currentldcBuf;
    /* Current LDC LUT buffer where the next set has to be uncompressed*/

    UInt8 *currentImgBuf;
    /*Current CAR Image Buffer where the next set of car images has to be decompressed*/


} Chain_Common_SRV_mediaObj;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
Void Chain_Common_SRV_generateLdcLut4ViewPoints(
                    Chain_Common_SRV_CalibrationPrm *pObj);
Int32 Chain_Common_SRV_generateGpuLut(
                    Chain_Common_SRV_CalibrationPrm *pObj);
Int32 Chain_Common_SRV_update2DPersMat(
                    Chain_Common_SRV_CalibrationPrm *pObj);
Void Chain_Common_SRV_generateCalMat(
                    Chain_Common_SRV_CalibrationPrm *pObj,
                    SRV_CALIB_TYPE calibType);
Int32 Chain_Common_SRV_Comp_mediaInit(
            Chain_Common_SRV_mediaObj *pMediaObj,
            SRV_MEDIA_FILE fileType);
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
