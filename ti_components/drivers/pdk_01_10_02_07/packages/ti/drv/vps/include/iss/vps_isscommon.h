/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_DATATYPES VPS - Common Data Types and macros
 *
 *  @{
 */

/**
 *  \file vps_isscommon.h
 *
 *  \brief ISS - Common API datatypes
 */

#ifndef VPS_ISSCOMMON_H_
#define VPS_ISSCOMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

/* ========================================================================== */
/*          Include HW specific config constants, structures                  */
/* ========================================================================== */

#include <ti/drv/vps/include/iss/vps_cfgldc.h>
#include <ti/drv/vps/include/iss/vps_cfgvtnf.h>
#include <ti/drv/vps/include/iss/vps_cfgipipe.h>
#include <ti/drv/vps/include/iss/vps_cfgisif.h>
#include <ti/drv/vps/include/iss/vps_cfgrsz.h>
#include <ti/drv/vps/include/iss/vps_cfgh3a.h>
#include <ti/drv/vps/include/iss/vps_cfgipipeif.h>
#include <ti/drv/vps/include/iss/vps_cfgcnf.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define VPS_ISS_IOCTL_IPIPE_IOCTL_BASE      (uint32_t) (0x00000000U)
/**< IPIPE Ioctl base */
#define VPS_ISS_IOCTL_IPIPE_IOCTL_NUM       (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_IPIPE_IOCTL_END       (VPS_ISS_IOCTL_IPIPE_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_IPIPE_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_ISIF_IOCTL_BASE       (VPS_ISS_IOCTL_IPIPE_IOCTL_END)
/**< ISIF Ioctl base */
#define VPS_ISS_IOCTL_ISIF_IOCTL_NUM        (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_ISIF_IOCTL_END        (VPS_ISS_IOCTL_ISIF_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_ISIF_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_RSZ_IOCTL_BASE        (VPS_ISS_IOCTL_ISIF_IOCTL_END)
/**< RSZ Ioctl base */
#define VPS_ISS_IOCTL_RSZ_IOCTL_NUM         (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_RSZ_IOCTL_END         (VPS_ISS_IOCTL_RSZ_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_RSZ_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_H3A_IOCTL_BASE        (uint32_t) ( \
        VPS_ISS_IOCTL_RSZ_IOCTL_END)
/**< H3A Ioctl base */
#define VPS_ISS_IOCTL_H3A_IOCTL_NUM         (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_H3A_IOCTL_END         (VPS_ISS_IOCTL_H3A_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_H3A_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_IPIPEIF_IOCTL_BASE  (VPS_ISS_IOCTL_H3A_IOCTL_END)
/**< IPIPEIF Ioctl base */
#define VPS_ISS_IOCTL_IPIPEIF_IOCTL_NUM   (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_IPIPEIF_IOCTL_END   (VPS_ISS_IOCTL_IPIPEIF_IOCTL_BASE + \
                                           VPS_ISS_IOCTL_IPIPEIF_IOCTL_NUM -  \
                                           1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_NSF3_IOCTL_BASE       (VPS_ISS_IOCTL_IPIPEIF_IOCTL_END)
/**< NSF3 Ioctl base */
#define VPS_ISS_IOCTL_NSF3_IOCTL_NUM        (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_NSF3_IOCTL_END        (VPS_ISS_IOCTL_NSF3_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_NSF3_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_GLBCE_IOCTL_BASE      (VPS_ISS_IOCTL_NSF3_IOCTL_END)
/**< GLBCE Ioctl base */
#define VPS_ISS_IOCTL_GLBCE_IOCTL_NUM       (uint32_t) (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_GLBCE_IOCTL_END       (VPS_ISS_IOCTL_GLBCE_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_GLBCE_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_CNF_IOCTL_BASE        (VPS_ISS_IOCTL_GLBCE_IOCTL_END)
/**< CNF Ioctl base */
#define VPS_ISS_IOCTL_CNF_IOCTL_NUM         (uint32_t) (0x5U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CNF_IOCTL_END         (VPS_ISS_IOCTL_CNF_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CNF_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

/**< Value of last control command */

#define VPS_ISS_IOCTL_CAL_IOCTL_BASE        (VPS_ISS_IOCTL_CNF_IOCTL_END)
/**< CAL Ioctl base */
#define VPS_ISS_IOCTL_CAL_IOCTL_NUM         (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CAL_IOCTL_END         (VPS_ISS_IOCTL_CAL_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CAL_IOCTL_NUM -  \
                                             1U)
 /**< Value of last control command */

#define VPS_ISS_IOCTL_LVDS_IOCTL_BASE       (VPS_ISS_IOCTL_CAL_IOCTL_END)
/**< LVDS Ioctl base */
#define VPS_ISS_IOCTL_LVDS_IOCTL_NUM        (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_LVDS_IOCTL_END        (VPS_ISS_IOCTL_LVDS_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_LVDS_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_CPI_IOCTL_BASE        (VPS_ISS_IOCTL_LVDS_IOCTL_END)
/**< CPI Ioctl base */
#define VPS_ISS_IOCTL_CPI_IOCTL_NUM         (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CPI_IOCTL_END         (VPS_ISS_IOCTL_CPI_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CPI_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_ISP_IOCTL_BASE        (VPS_ISS_IOCTL_CPI_IOCTL_END)
/**< ISP Ioctl base */
#define VPS_ISS_IOCTL_ISP_IOCTL_NUM         (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_ISP_IOCTL_END         (VPS_ISS_IOCTL_ISP_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_ISP_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_SIMCOP_IOCTL_BASE     (VPS_ISS_IOCTL_ISP_IOCTL_END)
/**< SIMCOP Ioctl base */
#define VPS_ISS_IOCTL_SIMCOP_IOCTL_NUM      (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_SIMCOP_IOCTL_END      (VPS_ISS_IOCTL_SIMCOP_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_SIMCOP_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

#define VPS_ISS_IOCTL_CALM2M_IOCTL_BASE     (VPS_ISS_IOCTL_SIMCOP_IOCTL_END)
/**< CALM2M Ioctl base */
#define VPS_ISS_IOCTL_CALM2M_IOCTL_NUM      (0x10U)
/**< Number of control commands */
#define VPS_ISS_IOCTL_CALM2M_IOCTL_END      (VPS_ISS_IOCTL_CALM2M_IOCTL_BASE + \
                                             VPS_ISS_IOCTL_CALM2M_IOCTL_NUM -  \
                                             1U)
/**< Value of last control command */

/**
 *  \brief Set ISS CAL M2M parameters.
 *
 *  This IOCTL can be used to set the ISS CAL M2M dma parameters.
 *  This IOCTL should be called after creating ISS CAL M2M M2M driver instance
 *
 *  \param cmdArgs       [IN]  const vpsissCalm2mDmaCtrlParams_t *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define VPS_ISS_CALM2M_IOCTL_SET_DMA_PARAMS   (VPS_ISS_IOCTL_CALM2M_IOCTL_BASE + 0x0001U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */


/**
 *  \brief ISS output Stream ID
 */
typedef enum vpsissStreamId
{
    VPS_ISS_STREAM_CAL_RD_INPUT_0 = 0x0,
    /**< CAL Read Input */
    VPS_ISS_STREAM_ID_RSZ_A = 0x1,
    /**< Id for output from RSZ_A */
    VPS_ISS_STREAM_ID_INPUT_N1 = 0x2,
    /**< Id for the Previous input */
    VPS_ISS_STREAM_ID_RSZ_B = 0x3,
    /** Id for output from RSZ_B */
    VPS_ISS_STREAM_ID_BSC = 0x4,
    /** Id for output BSC data */
    VPS_ISS_STREAM_ID_BOXCAR = 0x5,
    /** Id for output Boxcar data */
    VPS_ISS_STREAM_ID_HIST = 0x6,
    /** Id for output Histogram data */
    VPS_ISS_STREAM_ID_AF = 0x7,
    /** Id for output AutoFocus Data */
    VPS_ISS_STREAM_ID_AEWB = 0x8,
    /** Id for output AutoWhiteBalance Data */
    VPS_ISS_STREAM_ID_MAX = 0x9
                    /**< Should be the last enum */
} vpsissStreamId_t; /**< vpsissStreamId_t */


/**  \brief Enum for selecting the ISP modules, Selecting a module enables
 *         the clock for that module at the open time. All the modules
 *         required for the m2m instance must be enabled.
 */
typedef enum vpsissIspModuleId
{
    VPS_ISS_ISP_MODULE_IPIPEIF = 0x0,
    /**< IPIPEIF Module */
    VPS_ISS_ISP_MODULE_NSF3 = 0x1,
    /**< NSF3 Module */
    VPS_ISS_ISP_MODULE_GLBCE = 0x2,
    /**< GLBCE Module */
    VPS_ISS_ISP_MODULE_ISIF = 0x3,
    /**< ISIF Module */
    VPS_ISS_ISP_MODULE_IPIPE = 0x4,
    /**< IPIPE Module */
    VPS_ISS_ISP_MODULE_RSZ = 0x5,
    /**< Resizer Module */
    VPS_ISS_ISP_MODULE_H3A = 0x6,
    /**< H3A module */
    VPS_ISS_ISP_MODULE_CNF = 0x7,
    /**< H3A module */
    VPS_ISS_ISP_MAX_MODULE = 0x8,
    /**< Last Enum, user for error checking and array size */
    VPS_ISS_ISP_MODULE_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                         *      will always be contained in int */
} vpsissIspModuleId_t;  /**< vpsissIspModuleId_t */

/**  \brief Enum for selecting GLBCE Path, It could be either present
 *         in ISP or in CAL path
 */
typedef enum vpsissGlbcePath
{
    VPS_ISS_GLBCE_PATH_DISABLED = 0x0,
    /**< GLBCE is Disabled and is not enabled in any path */
    VPS_ISS_GLBCE_PATH_CAL = 0x1,
    /**< GLBCE is enabled on CAL Bys path */
    VPS_ISS_GLBCE_PATH_ISP = 0x2,
    /**< GLBCE is enabled on ISP IPIPEIF->IPIPE path */
    VPS_ISS_GLBCE_PATH_MAX = 0x3,
    /**< Last enum, used for error checking */
    VPS_ISS_GLBCE_PATH_FORCE_INT = 0x7FFFFFFF
                        /**< This will ensure enum is not packed,
                         *      will always be contained in int */
} vpsissGlbcePath_t;    /**< vpsissGlbcePath_t */

/**  \brief Enum for selecting NSF3 Path, It could be either present
 *         in ISP or in CAL path
 */
typedef enum vpsissNsf3Path
{
    VPS_ISS_NSF3_PATH_DISABLED = 0x0,
    /**< NSF3 is Disabled and is not enabled in any path */
    VPS_ISS_NSF3_PATH_CAL = 0x1,
    /**< NSF3 is enabled on CAL Bys path */
    VPS_ISS_NSF3_PATH_ISP = 0x2,
    /**< NSF3 is enabled on ISP IPIPEIF->IPIPE path */
    VPS_ISS_NSF3_PATH_MAX = 0x3,
    /**< Last enum, used for error checking */
    VPS_ISS_NSF3_PATH_FORCE_INT = 0x7FFFFFFF
                    /**< This will ensure enum is not packed,
                     *      will always be contained in int */
} vpsissNsf3Path_t; /**< vpsissNsf3Path_t */

/**
 *  \brief SIMCOP output Stream ID
 */
typedef enum vpsissSimcopStreamId
{
    VPS_SIMCOP_STREAM_ID_CUR_FRAME = 0x0,
    /**< Identifier for current frame */
    VPS_SIMCOP_STREAM_ID_PREV_FRAME = 0x1,
    /**< Identifier for previous frame */
    VPS_SIMCOP_STREAM_ID_OUT_FRAME = 0x2,
    /**< Identifier for output frame */
    VPS_SIMCOP_STREAM_ID_MESH_TABLE = 0x3,
    /**< Identifier for LDC mesh table frame */
    VPS_SIMCOP_STREAM_ID_MAX = VPS_SIMCOP_STREAM_ID_MESH_TABLE,
    /**< Last enum. Used for error checks or specifying stream count */
    VPS_SIMCOP_STREAM_ID_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed,
                             *      will always be contained in int */
} vpsissSimcopStreamId_t;   /**< vpsissSimcopStreamId_t */

/**
 *  \brief ISS CAL M2M Stream ID
 */
typedef enum vpsissCalm2mStreamId
{
    VPS_CALM2M_STREAM_ID_INPUT_FRAME = 0x0,
    /**< Identifier for input frame */
    VPS_CALM2M_STREAM_ID_OUT_FRAME = 0x1,
    /**< Identifier for output frame */
    VPS_CALM2M_STREAM_ID_MAX = VPS_CALM2M_STREAM_ID_OUT_FRAME,
    /**< Last enum. Used for error checks or specifying stream count */
    VPS_CALM2M_STREAM_ID_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed,
                             *      will always be contained in int */
} vpsissCalm2mStreamId_t;   /**< vpsissCalm2mStreamId_t */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Open Parameters
 */
typedef struct vpsissIspOpenParams
{
    uint32_t isModuleReq[VPS_ISS_ISP_MAX_MODULE];
    /**< Flag to indicate whether the given module is required or not
     *   vpsIssIspModuleId_t is used as an index into this array.
     *   Module Hal will be opened only if the module is enabled here.
     *   If the module is not openend, its functional clock will not
     *   be enabled, which saves the power.
     *   If the modules is set to not required here, it can not be
     *   enabled later on any time, setConfig for the module will
     *   return error. */
    Ptr      arg;
    /**< Not Used as of now */
} vpsissIspOpenParams_t;

/**
 *  \brief Open Return Parameters, contain return status and module
 *         caused failure
 */
typedef struct vpsissIspOpenRetParams
{
    int32_t             status;
    /**< Status of the open, return value of the open */
    vpsissIspModuleId_t module;
    /**< the first module, which failed to open */
    Ptr                 arg;
    /**< Not used as of now */
} vpsissIspOpenRetParams_t;

/**
 *  \brief Open Parameters, currently not used
 */
typedef struct vpsissSimcopOpenParams
{
    uint32_t mode;
    /**< Mode in which SIMCOP needs to be configured
     #vpsissSimcopM2MMode_t */
    Ptr      arg;
    /**< Not Used as of now */

    uint32_t ldcRdMaxTagCnt;
    /**< LDC read Max Tag Count */
} vpsissSimcopOpenParams_t;

/**
 *  \brief Open Parameters, currently not used
 */
typedef struct vpsissCalm2mOpenParams
{
    Ptr      arg;
    /**< Not Used as of now */
} vpsissCalm2mOpenParams_t;

/**
 *  \brief Open Parameters, currently not used
 */
typedef struct vpsissSimcopCfgPrms
{
    vpsissldcConfig_t  ldcCfg;
    /**< Configuration for LDC - Ignored if mode = VPSCORE_ISS_VTNF_ONLY */
    vpsissvtnfConfig_t vtnfCfg;
    /**< Configuration for VTNF - Ignored if mode = VPSCORE_ISS_LDC_ONLY */
    uint32_t           inpFrmPitch;
    /**< Input frames line stride */
    uint32_t           prevFrmPitch;
    /**< Previous / reference frames line stride */
    uint32_t           outFrmPitch;
    /**< Output frames line stride */
    uint32_t           inFrameWidth;
    /**< Input frames width */
    uint32_t           inFrameHeight;
    /**< Input frames height */
    Fvid2_CropConfig   cropCfg;
    /**< Selection section of input frame to be processed */
    uint32_t           blkWidth;
    /**< Sub Block Width */
    uint32_t           blkHeight;
    /**< Sub Block Height */
    Ptr                arg;
    /**< Not Used as of now */
}vpsissSimcopCfgPrms_t;

/**
 *  struct vpsissCalOtfStreamMapCfg
 *  \brief Associate capture stream ID with the ISP stream ID
 *
 *  \attention This IOCTL is mandatory for on-the-fly capture
 *
 *  \warning Deviation from naming convention: To enable backward compatibility
 *
 */
typedef struct vpsissCalOtfStreamMapCfg
{
    uint32_t numStream;
    /**< Specify the number of ISP streams that are enabled in ISP.
            Please note that only the stream that ISP could write is valid.
            Please refer vpsissStreamId_t for valid write streams. */
    uint32_t captStreamId[VPS_ISS_STREAM_ID_MAX];
    /**< Capture Stream Identifier */
    vpsissStreamId_t ispStreamId[VPS_ISS_STREAM_ID_MAX];
    /**< Associated ISP stream Identifier.
        e.g. consider use case where in an CSI2 stream is received and
                processed on the fly (via ISP) to generate 2 different streams
                Stream 1 - YUV422 video stream of resolution 1280x960
                    via ReSizer A of ISP
                    Associated Capture Stream Identifier is 1
                Stream 3 - Auto White Balance data for this stream
                    Associated Capture Stream Identifier is 2
        \code
            numStream = 2;

            captStreamId[0] = 1U;
            ispStreamId[0] = VPS_ISS_STREAM_ID_RSZ_A;

            captStreamId[1U] = 2U;
            ispStreamId[1U] = VPS_ISS_STREAM_ID_AEWB; \endcode */

    Ptr     pAdditionalArgs;
    /**< Not used for now - should be set to NULL */
} vpsissCalOtfStreamMapCfg_t;

/**
 *  \brief Configuration Parameters for CAL M2M driver.
 */
typedef struct vpsissCalm2mParams
{
    uint32_t                inWidth;
    /**< Input frames width */
    uint32_t                inHeight;
    /**< Input frames height */
    uint32_t                inPitch;
    /**< Input frames line stride */
    Fvid2_BitsPerPixel      inBpp;
    /**< Input frame bits per pixel */
    vpsissCalPixExtract_t   inPixExtract;
    /**< Input pixel extract format */
    uint32_t                outWidth;
    /**< Output frames width */
    uint32_t                outHeight;
    /**< Output frames height */
    uint32_t                outPitch;
    /**< Output frames line stride */
    Fvid2_BitsPerPixel      outBpp;
    /**< Output frame bits per pixel */
    vpsissCalPixPack_t      outPixPack;
    /**< Output pixel pack format */
    Ptr                arg;
    /**< Not Used as of now */
}vpsissCalm2mParams_t;

/**
 *  \brief Dma Parameters for CAL M2M driver.
 */
typedef struct vpsissCalm2mDmaCtrlParams
{
    uint32_t    bwLimit;
    /**<  Defines a minimum cycle count between to consecutive
          read requests issued by the RD DMA. */
    uint32_t    ocpTagCnt;
    /**<  Maximum allowed number of outstanding OCP read requests.
          Max value is 0xF */
    uint32_t    pixClock;
    /**<  Controls the data rate at which data is read from the read
          DMA FIFO and sent to the internal processing pipeline. */
}vpsissCalm2mDmaCtrlParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_ISSCOMMON_H_ */

/* @} */

