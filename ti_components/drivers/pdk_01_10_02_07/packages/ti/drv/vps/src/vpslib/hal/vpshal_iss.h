/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpshal_iss.h
 *
 *  \brief Common Header file for all ISS HALs. The ISS block is sub-divded into
 *  3 distinct functional blocks, namely, CAL - Capture, ISP - Image Processing,
 *  SIMCOP - Simple Image Co-Processor.
 *  This file defines common data-structures, enums, control functions, etc for
 *  all ISS HALs
 *
 */

#ifndef VPSHAL_ISS_H_
#define VPSHAL_ISS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/iss/vps_cfgisp.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */


/** \brief Common ioctl for getting blanking requirement,
           all modules of ISS requires minimum horizontal and
           vertical blanking depending on the configuration. This ioctl
           can be used by the upper layer to get blanking requirement */
#define VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO (VPS_HAL_ISS_IOCTL_CAL_END + 1U)

/** \brief IOCTL range for each of the sub-modules under ISS */
#define VPS_HAL_ISS_IOCTL_VIDEO_MUX_BEGIN   (VPS_HAL_ISS_IOCTL_END + 1U)
#define VPS_HAL_ISS_IOCTL_VIDEO_MUX_NUM     (5U)
#define VPS_HAL_ISS_IOCTL_VIDEO_MUX_END     (VPS_HAL_ISS_IOCTL_VIDEO_MUX_BEGIN \
                                             + VPS_HAL_ISS_IOCTL_VIDEO_MUX_NUM \
                                             - 1U)

#define VPS_HAL_ISS_IOCTL_VTNF3_BEGIN       (VPS_HAL_ISS_IOCTL_VIDEO_MUX_END)
#define VPS_HAL_ISS_IOCTL_VTNF3_NUM         (5U)
#define VPS_HAL_ISS_IOCTL_VTNF3_END         (VPS_HAL_ISS_IOCTL_VTNF3_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_VTNF3_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_IPIPEIF_BEGIN     (VPS_HAL_ISS_IOCTL_VTNF3_END)
#define VPS_HAL_ISS_IOCTL_IPIPEIF_NUM       (15U)
#define VPS_HAL_ISS_IOCTL_IPIPEIF_END       (VPS_HAL_ISS_IOCTL_IPIPEIF_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_IPIPEIF_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_IPIPE_BEGIN       (VPS_HAL_ISS_IOCTL_IPIPEIF_END)
#define VPS_HAL_ISS_IOCTL_IPIPE_NUM         (20U)
#define VPS_HAL_ISS_IOCTL_IPIPE_END         (VPS_HAL_ISS_IOCTL_IPIPE_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_IPIPE_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_ISIF_BEGIN        (VPS_HAL_ISS_IOCTL_IPIPE_END)
#define VPS_HAL_ISS_IOCTL_ISIF_NUM          (10U)
#define VPS_HAL_ISS_IOCTL_ISIF_END          (VPS_HAL_ISS_IOCTL_ISIF_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_ISIF_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_RSZ_BEGIN         (VPS_HAL_ISS_IOCTL_ISIF_END)
#define VPS_HAL_ISS_IOCTL_RSZ_NUM           (5U)
#define VPS_HAL_ISS_IOCTL_RSZ_END           (VPS_HAL_ISS_IOCTL_RSZ_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_RSZ_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_H3A_BEGIN         (VPS_HAL_ISS_IOCTL_RSZ_END)
#define VPS_HAL_ISS_IOCTL_H3A_NUM           (5U)
#define VPS_HAL_ISS_IOCTL_H3A_END           (VPS_HAL_ISS_IOCTL_H3A_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_H3A_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_NSF3_BEGIN        (VPS_HAL_ISS_IOCTL_H3A_END)
#define VPS_HAL_ISS_IOCTL_NSF3_NUM          (5U)
#define VPS_HAL_ISS_IOCTL_NSF3_END          (VPS_HAL_ISS_IOCTL_NSF3_BEGIN + \
                                             VPS_HAL_ISS_IOCTL_NSF3_NUM -   \
                                             1U)

#define VPS_HAL_ISS_IOCTL_GLBCE_BEGIN        (VPS_HAL_ISS_IOCTL_NSF3_END)
#define VPS_HAL_ISS_IOCTL_GLBCE_NUM          (10U)
#define VPS_HAL_ISS_IOCTL_GLBCE_END          (VPS_HAL_ISS_IOCTL_GLBCE_BEGIN + \
                                              VPS_HAL_ISS_IOCTL_GLBCE_NUM -   \
                                              1U)
/**
 *  \brief An utility memcopy function, implemented by HAL consumer. This
 *          function would be invoked to load various look up table (LUT).
 *
 *  \warning            This function implementation will ensure thread / task
 *                      context safe. i.e. this function could be called by
 *                      multiple contexts. This function will NOT be called
 *                      in a ISR context.
 *
 *  \param dest         Pointer to an array that of type uint32_t that holds
 *                      set of destination address. The number of valid entries
 *                      is defined by numCpy.
 *  \param src          Pointer to an array that of type uint32_t that holds
 *                      set of source address. The number of valid entries
 *                      is defined by numCpy.
 *  \param byteCount    Pointer to an array that of type uint32_t that holds
 *                      the number of bytes to be transferred. The number of
 *                      valid entries is defined by numCpy.
 *  \param numCpy       An uint32_t that holds of number of copies requested.
 *                      Caller of this function will ensure that all function
 *                      arguments will be big enough to hold "numCpy" of
 *                      uint32_t values
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */

typedef int32_t (*VpsHal_issUtilMemCpy_t)(uint32_t       *dest[],
                                          const uint32_t *src[],
                                          uint32_t        byteCount[],
                                          uint32_t        numCpy);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalIssCtrlInitParams
 *  \brief ISS common / control HAL module initialization parameters.
 */
typedef struct isshalIssCtrlInitParams
{
    uint32_t               issBaseAddress;
    /**< ISS common register base address */
    uint32_t               ispSys1BaseAddress;
    /**< ISP SYS1 baseaddress */
    uint32_t               ispSys2BaseAddress;
    /**< ISP SYS2 baseaddress */
    uint32_t               ispSys3BaseAddress;
    /**< ISP SYS3 baseaddress */
    uint32_t               vmuxMod;
    /**< VMUX operation mode, FALSE (0x0) for legacy/fixed connection.
     *   TRUE for explicit control. Refer manual for details.
     *   LEGACY mode is not supported for now. */
    VpsHal_issUtilMemCpy_t utilsMemCpy;
    /**< HAL consumer could provide an optimized memory copy function. */
    uint32_t               prms;
    /**< Not used */
} isshalIssCtrlInitParams_t;

/**
 *  struct isshalIspInitParams
 *  \brief ISP HAL module initialization parameters.
 */
typedef struct isshalIspInitParams
{
    uint32_t prms;
    /**< Init Params, not used */
} isshalIspInitParams_t;

/**
 *  struct isshalSimcopInitParams
 *  \brief SIMCOP HAL module initialization parameters.
 */
typedef struct isshalSimcopInitParams
{
    uint32_t prms;
    /**< Init Params, not used */
} isshalSimcopInitParams_t;

/**
 *  struct isshalVMuxSrcPorts
 *  \brief VMUX Source port identifiers.
 */
typedef enum isshalVMuxSrcPorts
{
    SRC_PORT_CAL_A_BYS_OUT = 0x1,
    /**< Input is from CAL A BYS out port */
    SRC_PORT_CAL_A_VP = 0x2,
    /**< Input is from CAL A Video Port port */
    SRC_PORT_CAL_B_BYS_OUT = 0x3,
    /**< Input is from CAL A BYS out port */
    SRC_PORT_CAL_B_VP = 0x4,
    /**< Input is from CAL A Video Port port */
    SRC_PORT_PARALLEL_A = 0x5,
    /**< Input is from Parallel input port */
    SRC_PORT_NSF3V_OUT = 0x6,
    /**< Input is from NSF out port */
    SRC_PORT_GLBCE_OUT = 0x7,
    /**< Input is from GLBCE out port */
    SRC_PORT_LVDSRX_OUT_0 = 0x8,
    /**< Input is from LVDS RX 0 port */
    SRC_PORT_LVDSRX_OUT_3 = 0x9,
    /**< Input is from LVDS RX 3 port */
    SRC_PORT_MAX = 0xA,
    /**< End of enumeration marker */
    SRC_PORT_MAX_FORCE_INT = 0x7FFFFFFF
                             /**< This will ensure enum is not packed, will always be contained in int */
} isshalVMuxSrcPorts_t;

/**
 *  struct isshalVMuxSinkPorts
 *  \brief VMUX Destination / Sink / Drain port identifiers
 */
typedef enum isshalVMuxSinkPorts
{
    SINK_PORT_ISP_IN = 0x1,
    /**< ISP IN port */
    SINK_PORT_NSFV3_IN = 0x2,
    /**< Input into NSF V3 */
    SINK_PORT_GLBCE_IN = 0x4,
    /**< Input into GLBCE */
    SINK_PORT_CAL_A_BYS_IN = 0x8,
    /**< Input into CAL A Via BSY In port */
    SINK_PORT_CAL_B_BYS_IN = 0x10,
    /**< Input into CAL B Via BSY In port */
    SINK_PORT_MAX = 0x20,
    /**< End of enumeration marker */
    SINK_PORT_MAX_FORCE_INT = 0x7FFFFFFF
                              /**< This will ensure enum is not packed, will always be contained in int */
} isshalVMuxSinkPorts_t;

/**
 *  \brief Enum for defining the ISS module Ids
 */
typedef enum isshalIssModuleId
{
    ISSHAL_ISS_MODULE_IPIPEIF = 0x0,
    /**< IPIPEIF Module */
    ISSHAL_ISS_MODULE_IPIPE = 0x1,
    /**< IPIPE Module */
    ISSHAL_ISS_MODULE_RSZ = 0x2,
    /**< Resizer Module */
    ISSHAL_ISS_MODULE_H3A = 0x3,
    /**< H3A Module */
    ISSHAL_ISS_MODULE_ISIF = 0x4,
    /**< ISIF Module */
    ISSHAL_ISS_MODULE_BL = 0x5,
    /**< BL Module */
    ISSHAL_ISS_MODULE_CNFA = 0x6,
    /**< CNFA Module */
    ISSHAL_ISS_MODULE_CNFB = 0x7,
    /**< CNFB Module */
    ISSHAL_ISS_MODULE_NSF3 = 0x8,
    /**< NSF3 Module */
    ISSHAL_ISS_MODULE_GLBCE = 0x9,
    /**< GLBCE Module */
    ISSHAL_ISS_MODULE_SYNC = 0xA,
    /**< Sync module,
     *   Shall be enabled when Video port is receiving data
     *   Shall be disabled when Video port is not receiving data eg
     *   data is read from IPIPEIF */
    ISSHAL_ISS_MODULE_PSYNC = 0xB,
    /**< PCLK Sync clock Select,
    *   Used to select the clock which is used to
    * resynchronize
    *   the input pixel clock.
    *   Enable when Pixelclock is higher than 213MHz
    * or
    *   DPC is used with the CAL
    * (CAL->DPC->NSF3->CAL) */
    ISSHAL_ISS_MODULE_FORCE_INT = 0x7FFFFFFF
                                  /**< This will ensure enum is not packed,
                                          will always be contained in int */
} isshalIssModuleId_t;

/**
 *  \brief  Enum for selecting the module for bandwidth control,
 *          used in setting minimum interval between two consecutive
 *          DMA read or write.
 */
typedef enum isshalIssBwCtrlModule
{
    ISSHAL_ISS_BW_CTRL_MODULE_ISIF_READ = 0x0,
    /**< ISIF Read */
    ISSHAL_ISS_BW_CTRL_MODULE_IPIPEIF_READ = 0x1,
    /**< IPIPEIF Read */
    ISSHAL_ISS_BW_CTRL_MODULE_H3A_WRITE = 0x2,
    /**< H3A Write */
    ISSHAL_ISS_BW_CTRL_MODULE_FORCE_INT = 0x7FFFFFFF
                                          /**< This will ensure enum is not packed,
                                                  will always be contained in int */
} isshalIssBwCtrlModule_t;

/**
 *  \brief Enum for setting up the VBUSM Priority
 */
typedef enum isshalIssVBusMPriority
{
    ISSHAL_ISS_VBUSM_PRIORITY_HIGH0 = 0x0,
    /**< VBUSM Cpriority High */
    ISSHAL_ISS_VBUSM_PRIORITY_HIGH1 = 0x1,
    /**< VBUSM Cpriority High */
    ISSHAL_ISS_VBUSM_PRIORITY_MEDIUM0 = 0x2,
    /**< VBUSM Cpriority Medium */
    ISSHAL_ISS_VBUSM_PRIORITY_MEDIUM1 = 0x3,
    /**< VBUSM Cpriority Medium */
    ISSHAL_ISS_VBUSM_PRIORITY_NORMAL0 = 0x4,
    /**< VBUSM Cpriority Normal */
    ISSHAL_ISS_VBUSM_PRIORITY_NORMAL1 = 0x5,
    /**< VBUSM Cpriority Normal */
    ISSHAL_ISS_VBUSM_PRIORITY_NORMAL2 = 0x6,
    /**< VBUSM Cpriority Normal */
    ISSHAL_ISS_VBUSM_PRIORITY_NORMAL3 = 0x7,
    /**< VBUSM Cpriority Normal */
    ISSHAL_ISS_VBUSM_PRIORITY_FORCE_INT = 0x7FFFFFFF
                                          /**< This will ensure enum is not packed,
                                                  will always be contained in int */
} isshalIssVBusMPriority_t;

/**
 *  \brief Enum defining CNF instance Id
 */
typedef enum isshalIssCnfInstId
{
    ISSHAL_ISS_CNF_A = 0x0,
    /**< CNF Instance A, connected to RSZA output */
    ISSHAL_ISS_CNF_B = 0x1,
    /**< CNF Instance B, connected to RSZB output */
    ISSHAL_ISS_MAX_INST = 0x2,
    /**< Should be the last enum */
    ISSHAL_ISS_MAX_INST_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed,
                                            will always be contained in int */
} isshalIssCnfInstId_t;

typedef enum isshalGlbceSwitchModule
{
    ISSHAL_GLBCE_SWITCH_NSF3 = 0x0,
    /**< Nsf3 Module for the Glbce Switch */
    ISSHAL_GLBCE_SWITCH_GLBCE = 0x1,
    /**< GLBCE Module for the Glbce Switch */
    ISSHAL_GLBCE_SWITCH_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed,
                                            will always be contained in int */
} isshalGlbceSwitchModule_t;

typedef enum isshalGlbceSwitchCtrl
{
    ISSHAL_GLBCE_SWITCH_DISABLED = 0x0,
    /**< Disable data passing to GLBCE/NSF3
     *   In this case, ISP works same way as ISP without GLBCE function */
    ISSHAL_GLBCE_SWITCH_CAL = 0x1,
    /**< Enable GLBCE/NSF3 with CAL */
    ISSHAL_GLBCE_SWITCH_ISP = 0x2,
    /**< Enable GLBCE/NSF3 After IPIPEIF */
    ISSHAL_GLBCE_SWITCH_CTRL_FORCE_INT = 0x7FFFFFFF
                                         /**< This will ensure enum is not packed,
                                                 will always be contained in int */
} isshalGlbceSwitchCtrl_t;


/**
 *  \brief NSF3 Input Format and Interface
 */
typedef enum isshalissNsf3InpData
{
    ISSHAL_NSF3_INP_DATA_RAW = 0x0,
    /**< RAW Data Input */
    ISSHAL_NSF3_INP_DATA_YUV_16BIT = 0x1,
    /**< From VP1, YUV422 16 bit data or YUV420 Luma 8bit data
     *   Not Valid for CAL input */
    ISSHAL_NSF3_INP_DATA_YUV_8BIT = 0x2,
    /**< For Cal,
     *      YUV422 8bit
     *      YUV420 luma 8bit
     *      YUV420 chroma 8bit
     *   For VP1
     *      YUV422 8bit
     *      YUV420 chroma 8bit */
    ISSHAL_NSF3_INP_DATA_FORCE_INT = 0x7FFFFFFF
                                     /**< This will ensure enum is not packed,
                                             will always be contained in int */
} isshalissNsf3InpData_t;

/**
 *  \brief Enum for selecting chroma position in chroma up or down sampler
 */
typedef enum issCtrlChromaPos
{
    ISSHAL_ISS_CHROMA_POS_COSITED = 0x0,
    /**< Chroma is cosited */
    ISSHAL_ISS_CHROMA_POS_CENTERED = 0x1,
    /**< Chroma is Centred */
    ISSHAL_ISS_CHROMA_POS_FORCE_INT = 0x7FFFFFFF
                                      /**< This will ensure enum is not packed,
                                              will always be contained in int */
} issCtrlChromaPos_t;

/**
 *  \brief Enum for selecting bayer color components for odd/even pixel
 *         position on odd/even lines, Also used for specifying gain and offset
 *         in White balance config for each color component
 */
typedef enum isshalBayerColorComp
{
    ISSHAL_ISS_BAYER_COLOR_COMP_R = 0x0,
    /**< Red Color Component in Bayer image */
    ISSHAL_ISS_BAYER_COLOR_COMP_GR = 0x1,
    /**< GreenR Color Component in Bayer image */
    ISSHAL_ISS_BAYER_COLOR_COMP_GB = 0x2,
    /**< GreenB Color Component in Bayer image */
    ISSHAL_ISS_BAYER_COLOR_COMP_B = 0x3,
    /**< Blue Color Component in Bayer image */
    ISSHAL_ISS_BAYER_COLOR_COMP_MAX = 0x4,
    /**< This should be the last number,
     *   used in specifying array size */
    ISSHAL_ISS_BAYER_COLOR_COMP_FORCE_INT = 0x7FFFFFFF
                                            /**< This will ensure enum is not packed,
                                                    will always be contained in int */
} isshalBayerColorComp_t;

typedef struct isshalOpenParams
{
    uint32_t instId;
    /**< Instance Id of the module */
} isshalOpenParams_t;

/**
 *  \brief structure for setting the clip value ie minimum and maximum value
 */
typedef struct isshalCtrlClipValue
{
    uint32_t min;
    /**< Minimum Value */
    uint32_t max;
    /**< Maximum Value */
} isshalCtrlClipValue_t;

/**
 *  \brief structure containing CNF (Chroma Noise Filter) configuration
 */
typedef struct isshalissCnfConfig
{
    isshalIssCnfInstId_t instId;
    /**< CNF Instance ID, only one instance CNFA supported on TDA3XX */
    uint32_t             enable;
    /**< Enable/Disable CNF (Chroma Noise Filter)
     *   Should be enabled only if the output is YUV420 and UV pass is active.
     *   In other case, this bit must be disabled */
    uint32_t             enableCds;
    /**< Enable/Disable Chroma Down Sampler
     *   Valid only if CNF is enabled
     *   TRUE: Chroma Down Sampler is enabled in CNF process on RSZ output
     *   FALSE: Chroma Down Sampler is disabled in CNF process on RZS output */
    uint32_t             frameWidth;
    /**< Width of the CNF output
     *   must be even number
     *   must be same as resizer output width if CDS is off
     *   half of resizer output width if CDS is on
     *   must be multiple of 4 if CDS is on */
    uint32_t             frameHeight;
    /**< Height of the CNF output
     *   must be same Resizer chroma height if CDS is off
     *   half of resizer output height if CDS is on
     *   must be multiple of 2 if CDS is on */
} isshalissCnfConfig_t;

/**
 *  \brief structure containing VP1 (Video Port1) configuration,
 *         This video port connects NSF3 to IPIPEIF and ISIF.
 */
typedef struct isshalissVp1Config
{
    Fvid2_DataFormat        bayerDataFormat;
    /**< Bayer input DataFormat for VP1
     *   Valid values are
     *      FVID2_DF_BAYER_GRBG,
     *      FVID2_DF_BAYER_RGGB,
     *      FVID2_DF_BAYER_BGGR,
     *      FVID2_DF_BAYER_GBRG*/
    uint32_t                enableDelay;
    /**< Enables/Disables delay between NSF3V input VD/HD and output VD/HD,
     *   Used typically when NSF3 is in ISP path and DFS/WDR is enabled
     *   In this case, VD must be at least one line earlier than first line */
    uint32_t                horzDelay;
    /**< Horizontal delay from HD_IN to HD_OUT in terms of cycles
     *   Depends on the NSF3 format
     *   for 16 bit input, max clock delay is 16
     *   for 8 bit input, max clock delay is 8
     *   When max value is used, there is no delay between input to output
     *   When less than max value is used, actual delay is (max - value) */
    uint32_t                vertDelay;
    /**< Vertical Delay of VP1 port from VD_IN to VD_OUT
     *   This value should be equal to or smaller than NSF3V
     *   line latency for meaningfull operation
     *   The value of 0 to 3 can be used when only top border is replicated
     *   The value of 0 to 17 can be used when only bottom or both top
     *   and bottom borders are replicated in NSF3 */
    Fvid2_CropConfig        cropWin;
    /**< Horizontal/Vertical start position and frame size
     *   Horizontal size is in terms of cycles, so YUV422 8 bit input,
     *   horizontal size = width * 2 */
    uint32_t                enableYcSwap;
    /**< The ISIF module has a 16-bit interface. When 16-bit YUV data
     *   are input, the luma data (YIN7-0) are expected to be on
     *   the 8 MS bits and the chroma (CIN7-0) data are expected
     *   to be on the LS bits. This enables to swap the 8 MS bits
     *   with the 8 LS bits of the interface in case the luma and
     *   chroma do not come in the correct order. */
    uint32_t                enableLumaOddPos;
    /**< Selects the Luma at the odd position in YUV422 data */

    /* Configurations required for the NSF3 operation */
    isshalissNsf3InpData_t  inpDataFormat;
    /**< Input Data Format and interface */
    Fvid2_Polarity          hdPol;
    /**< polarity of the HD Signal */
    Fvid2_Polarity          vdPol;
    /**< polarity of the VD Signal */
    uint32_t                isInvertData;
    /**< Flag to indicate input data is inverted, one's complement */
    vpsissIspInDataMsbPos_t inMsbPos;
    /**< Selects MSB position of Input Data for NSF3V (VP-1 and CAL)
     *   For input of IN[15..0],
     *      corresponding output is given to DPC and/or NSF3V
     *   Only Valid for RAW Input
     *   For the output, 12bits are always mapped to LSB */
} isshalissVp1Config_t;

/**
 *  \brief structure containing VP2 (Video Port2) configuration,
 *         This video port connects GLBCE to IPIPEIF and IPIPE.
 */
typedef struct isshalissVp2Config
{
    Fvid2_PosConfig          pos;
    /**< Starting location of the first active pixel */
    uint32_t                 horzDelay;
    /**< Horizontal delay from HS_IN (derived from HD_IN) to HD_OUT.
     *   The latency of NSF3V should be set in this field.
     *   Usually, this value should be left as default (67) */
    uint32_t                 vertDelay;
    /**< Vertical Delay of VP2 port from VD_IN to VD_OUT.
     *   After number of lines specified here following VD_IN,
     *   VD_OUT is output.
     *   This value should be equal to or smaller than GLBCE line
     *   latency for meaningful operation.
     *  Usually, this value should be left as default (1) */
    vpsissIspInDataMsbPos_t  inMsbPos;
    /**< Selects MSB position of Input Data for GLBCE */
    vpsissIspOutDataMsbPos_t outMsbPos;
    /**< Selects MSB position of output data from GLBCE */
} isshalissVp2Config_t;

/**
 *  \brief Structure containing blanking information
 *         Used with the the ioctl #VPS_HAL_ISS_IOCTL_GET_BLANKING_INFO to get
 *         the modules blanking requirement
 */
typedef struct isshalissBlankingInfo
{
    issCtrlProcMode_t procMode;
    /**< Processing mode, this is input parameter.
         Depending on the processing mode, blanking requirement may
         change in the module */
    uint32_t          hBlank;
    /**< Number of pixels required in horizontal blanking period in each line */
    uint32_t          vBlank;
    /**< Number of lines required in vertical blanking period */
} isshalissBlankingInfo_t;

/**
 *  \brief Function pointer for starting the modules
 */
typedef int32_t (*isshalissStartModuleFxn)(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);
typedef int32_t (*isshalissStopModuleFxn)(
    VpsHal_Handle handle,
    Ptr           arg);
typedef int32_t (*isshalissControlModuleFxn)(
    VpsHal_Handle handle,
    uint32_t      cmd,
    Ptr           cmdArgs,
    Ptr           arg);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initializes ISS common control abstractions.
 *
 *  Caller of this function ensures the following,
 *  1. This function is called before any other abstractions are called.
 *  2. Called only ONCE during the initialization sequence.
 *  4. TODO
 *
 *  \param initPrms     Pointer to #isshalIssCtrlInitParams_t.
 *  \param arg          Not used
 */
int32_t VpsHal_issctrlInit(const isshalIssCtrlInitParams_t *initPrms, Ptr arg);

/**
 *  \brief DeInitializes ISS common control abstractions.
 *
 *  Caller of this function ensures the following.
 *  1. This function should be last in de-init / tear down sequence.
 *  3. TODO.
 *
 *  \param arg          Not used
 */
int32_t VpsHal_issctrlDeInit(Ptr arg);

/**
 *  \brief ISP initialization function.
 */
int32_t VpsHal_issispInit(const isshalIspInitParams_t *initPrms);

/**
 *  \brief ISP de-initialization function.
 */
int32_t VpsHal_issispDeInit(void);

/**
 *  \brief API to control state of sub modules
 *
 *  This function is expected to be used to power up / down a sub-module
 *
 *  \param module   Module identifier. Multiple modules could be specified.
 *                  e.g. module = SUB_MODULE_LVDSRX | SUB_MODULE_CAL_A
 *  \param flags    TRUE turn ON, FALSE turns OFF.
 *
 *  \return BSP_SOK on successful completion, BSP_EFAIL otherwise.
 */
int32_t VpsHal_issPowerCtrl(isshalSubModules_t module, uint32_t flags);

/**
 *  \brief API to control gating of clock at video mux level.
 *
 *  This function will check if the given source / sink could be connected.
 *  Stop/Start the pixel clock flow at the given ports.
 *
 *  \param srcPort      Source port identifier - Only 1 source to be given
 *  \param sinkPort     Sink port identifier - Only 1 sink to be given
 *  \param flags        TRUE turn ON clock at Video Mux, FALSE turns OFF.
 *
 *  \return  BSP_SOK on successful completion, BSP_EBADARGS, for un-supported
 *              maps.
 */
int32_t VpsHal_issvmuxClkCtrl(isshalVMuxSrcPorts_t  srcPort,
                              isshalVMuxSinkPorts_t sinkPort,
                              uint32_t              flags);

/**
 *  \brief Connect a given source to a sink in the video mux.
 *
 *  This function will check if the modules clocks are gated at VMUX, check if
 *  the supplied map is supported and perform the connection.
 *  Its the callers responsibility to ensure the modules clocks are gated and
 *  modules are in required state, before this function is called.
 *
 *  \param srcPort      Source port identifier - Only 1 source to be given
 *  \param sinkPort     Sink port identifier - Only 1 sink to be given
 *  \param isEnable     Not used
 *
 *  \return  BSP_SOK on successful completion, BSP_EBADARGS, for un-supported
 *              maps.
 */
int32_t VpsHal_issvmuxSetPath(isshalVMuxSrcPorts_t  srcPort,
                              isshalVMuxSinkPorts_t sinkPort,
                              uint32_t              isEnable);

/**
 *  \brief Enable/Disable clock for a given module
 *
 *  This function will enable/disable the clock for the given module.
 *  If the clock is not enabled, it returns error when MMR or memory
 *  is accessed.
 *
 *  \param moduleId     Id of the module to be enabled/disabled
 *  \param flag         TRUE: enable the module, FALSE: Disable the module
 *
 *  \return  FVID2_SOK on successful completion, BSP_EBADARGS, for
 *           wrong moduleId.
 */
int32_t VpsHal_issEnableModule(
    isshalIssModuleId_t moduleId,
    uint32_t            enableFlag);

/**
 *  \brief Function to enable VD Pulse Extension
 *
 *  This enables or disables the VD extension bridge.
 *  By default, the bridge is enabled.
 *  At ISS level, it is expected that this brigde is enabled when
 *  the VPORT gets data from the CSI2 RX module and
 *  this bridge is disabled when the VPORT gets data from the
 *  parallel interface.
 *
 *  \param flag         TRUE: enable the module, FALSE: Disable the module
 *
 *  \return  None.
 */
void VpsHal_issEnableVdPulseExt(uint32_t enableFlag);

/**
 *  \brief Function to Invert the pixel clock
 *
 * This function enables or disables pixel clock inversion.
 * The ISP always samples the data on the rising edge of the
 * pixel clock. Enabling the inversion shifts the re-sampling
 * period by 1/2 a pixel clock period.
 *
 * PCLK needs to be disabled at ISS level before setting calling this api.
 *
 *  \param flag         TRUE: enable the module, FALSE: Disable the module
 *
 *  \return  None.
 */
void VpsHal_issEnablePixClkInvert(uint32_t enableFlag);

/**
 *  \brief Function to enable/disable OCP Posted Write
 *
 *  \param flag         TRUE: enable the module, FALSE: Disable the module
 *
 *  \return  None.
 */
void VpsHal_issEnablePostedWrite(uint32_t enableFlag);

/**
 *  \brief Function to Buffer Logic VBUSM Priority
 *
 *  \param prio         Priority
 *
 *  \return  None.
 */
void VpsHal_issSetVbusMPriority(isshalIssVBusMPriority_t prio);

/**
 *  \brief Function to reset the ISP
 *         Before issuing a soft reset, must ensure that no more
 *         traffic is being generated by the ISP. Basically, it means
 *         that either the camera module shall be stopped from
 *         sending data and/or that the ISP5 modules are disabled.
 *         Furthermore, must set the ISP in standbymode before
 *         issuing the soft reset:
 *         Set ISP5_SYSCONFIG.STANDBYMODE = 2 (smart standby)
 *         Set ISP5_CTRL.MSTANDBY to "1"
 *         Poll for ISP5_CTRL.MSTANDBY_WAIT = 1.
 *         then call this api
 *
 */
void VpsHal_issIspReset(void);

/**
 *  \brief Function to returns the reset status
 *
 *  \return Flag indicating reset is done or not
 */
uint32_t VpsHal_issIspIsResetdone(void);

/**
 *  \brief Function to control the read/write bandwidth for ISIF/IPIPE/H3A.
 *         It is used to set the minimum delay in terms of clock cycles
 *         between two consecutive read or write.
 *
 *  \param module       Module Id for which bwCtrl is to be set
 *  \param bwCtrl       read/write delay in terms of clock cycles
 */
void VpsHal_issSetModuleBwCtrl(isshalIssBwCtrlModule_t module, uint32_t bwCtrl);

/**
 *  \brief Function to set the CNF configuration
 *
 *  \param  cnfCfg      Pointer to the CNF configuration
 *
 *  \return FVID2_SOK on successful completion,
 *          error in case of parameters are wrong
 */
int32_t VpsHal_issSetCnfConfig(const isshalissCnfConfig_t *cnfCfg);

/**
 *  \brief Function to set the GLBCE switch,
 *         it is a mux to connect NSF3/GLBCE with IPIPEIF and ISIF/IPIPE
 *         The path can be from CAL or ISP module
 *
 *  \param  module      NSF3/GLBCE module ID
 *  \param  ctrl        path to be selected
 *
 *  \return None
 */
void VpsHal_issSetGlbceSwitch(
    isshalGlbceSwitchModule_t module,
    isshalGlbceSwitchCtrl_t   ctrl);

/**
 *  \brief Function for enabling DPC before NSF3,
 *         Valid only if NSF3 is enabled
 *         DPC configuration should be set using IPIPE module
 *         also DPC submodule clock should be enabled using IPIPE module
 *         NSF3 alone should not be reset when DPC is used before NSF3 instead,
 *         whole ISS should be reset
 *
 *  \param TRUE: Enables DPC before NSF3
 *         FALSE: No DPC before NSF3
 *
 *  \return None
 */
void VpsHal_issDpcBeforeNsf3(uint32_t enable);

/**
 *  \brief Function for setting VP1 configuration,
 *         VP1 connects NSF3 with IPIPEIF and ISIF
 *
 *  \param cfg VP1 configuration
 *
 *  \return None
 */
int32_t VpsHal_issSetVp1Config(const isshalissVp1Config_t *cfg);

/**
 *  \brief Function for setting VP2 configuration,
 *         VP2 connects GLBCE with IPIPEIF and IPIPE
 *
 *  \param cfg VP2 configuration
 *
 *  \return None
 */
int32_t VpsHal_issSetVp2Config(const isshalissVp2Config_t *cfg);

/**
 *  \brief An utility memcopy function, an attempt to let HAL consumer optimize
 *          memcopy operation.
 *
 *  \warning            This function should NOT be called in a ISR context.
 *
 *  \param dest         Pointer to an array that of type uint32_t that holds
 *                      set of destination address. The number of valid entries
 *                      is defined by numCpy.
 *  \param src          Pointer to an array that of type uint32_t that holds
 *                      set of source address. The number of valid entries
 *                      is defined by numCpy.
 *  \param byteCount    Pointer to an array that of type uint32_t that holds
 *                      the number of bytes to be transferred. The number of
 *                      valid entries is defined by numCpy.
 *  \param numCpy       An uint32_t that holds of number of copies requested.
 *                      Caller of this function will ensure that all function
 *                      arguments will be big enough to hold "numCpy" of
 *                      uint32_t values
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
int32_t VpsHal_issUtilMemCpy(uint32_t *dest[],
                             const uint32_t *src[], uint32_t byteCount[],
                             uint32_t numCpy);

/**
 *  \brief The ISS local interconnect, provide a mechanism to prioritize
 *          all requests originating from ISS to external interface. This
 *          function is used to configure the priority of requests.
 *
 *  \param initiator    A valid initiator, for which priority should be set
 *  \param priority     A valid priority level.
 *  \param cportId      Applicable when initiator is either CAL A or CAL B.
 *
 *  \warning    Following priority and initiator combination is in-valid
 *              . SIMCOP DMA / LDC, Should not be on OCPM1.
 *                  An error code would be returned and not configured.
 *              . CAL A / CAL B, cport ID 0, preferably should not be on OCPM1
 *                  An warning error code would be returned but configured.
 *                  Other operations can proceed.
 *
 *  \return FVID2_SOK, or appropriate error code.
 */
int32_t VpsHal_issSetInitiatorPriority(vpsissL3Initiator_t  initiator,
                                       vpsissL3RoutingPri_t priority,
                                       uint32_t             cportId);

/**
 *  \brief Function to check if GLBCE Filter done flag is set or not in SYS2
 *
 *  \return Status of the filter done flag
 */
uint32_t VpsHal_issGlbceIsFilterDoneInSys2(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSHAL_ISS_H_ */
