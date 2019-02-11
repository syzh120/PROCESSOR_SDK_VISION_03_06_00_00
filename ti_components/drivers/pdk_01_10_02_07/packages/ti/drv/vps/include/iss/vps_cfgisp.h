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
 *  \file vps_cfgisp.h
 *
 *  \brief  Provides interfaces to control / configure ISP parameters.
 *          These parameters are either used in the capture driver or in the
 *          M2M driver.
 *
 */

#ifndef VPS_CFG_ISP_H_
#define VPS_CFG_ISP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Ioctl for getting VP1 Configuration
 */
#define VPS_ISS_ISIF_IOCTL_GET_VP1_CONFIG   (VPS_ISS_IOCTL_ISP_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for setting VP1 parameters
 */
#define VPS_ISS_ISIF_IOCTL_SET_VP1_CONFIG   (VPS_ISS_IOCTL_ISP_IOCTL_BASE + 1U)

/**
 *  \brief Ioctl for getting VP2 Configuration
 */
#define VPS_ISS_IPIPE_IOCTL_GET_VP2_CONFIG   (VPS_ISS_IOCTL_ISP_IOCTL_BASE + 2U)

/**
 *  \brief Ioctl for setting VP2 parameters
 */
#define VPS_ISS_IPIPE_IOCTL_SET_VP2_CONFIG   (VPS_ISS_IOCTL_ISP_IOCTL_BASE + 3U)

/**
 *  \brief Ioctl to configuring ISS traffic priority.
 *
 *          When ISS streams that are sourced from / destined out side ISS
 *          boundary, there are 3 possible routes. Each of these routes have
 *          priorities. This is done to ensure real time stream has higher
 *          priority over the non-real streams.
 *
 *          Use this control to configure the priority of streams to achieve
 *          required system requirements.
 *
 *          Takes argument of type #vpsissRoutingConfig_t
 */
#define VPS_ISS_SET_ISS_STREAM_PRI_CONFIG  (VPS_ISS_IOCTL_ISP_IOCTL_BASE + 4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum to select the MSB bit of the NSF2/GLBCE input with which
 *         MSB bit of the input is connected.
 */
typedef enum vpsissIspInDataMsbPos
{
    VPS_ISS_INPUT_MSB_POS_BIT15 = 0x0,
    /**< MSB Bit is Bit 15 */
    VPS_ISS_INPUT_MSB_POS_BIT14 = 0x1,
    /**< MSB Bit is Bit 14 */
    VPS_ISS_INPUT_MSB_POS_BIT13 = 0x2,
    /**< MSB Bit is Bit 13 */
    VPS_ISS_INPUT_MSB_POS_BIT12 = 0x3,
    /**< MSB Bit is Bit 12 */
    VPS_ISS_INPUT_MSB_POS_BIT11 = 0x4,
    /**< MSB Bit is Bit 11 */
    VPS_ISS_INPUT_MSB_POS_BIT10 = 0x5,
    /**< MSB Bit is Bit 10 */
    VPS_ISS_INPUT_MSB_POS_BIT9 = 0x6,
    /**< MSB Bit is Bit 9 */
    VPS_ISS_INPUT_MSB_POS_BIT8 = 0x7,
    /**< MSB Bit is Bit 8 */
    VPS_ISS_INPUT_MSB_POS_BIT7 = 0x8,
    /**< MSB Bit is Bit 7 */
    VPS_ISS_INPUT_MSB_POS_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed, will
                             *always be contained in int */
} vpsissIspInDataMsbPos_t;  /**< vpsissIspInDataMsbPos_t */

/**
 *  \brief Enum to select the MSB bit of the NSF2/GLBCE output
 */
typedef enum vpsissIspOutDataMsbPos
{
    VPS_ISS_OUTPUT_MSB_POS_BIT16 = 0x0,
    /**< Output Bits are on [15:0] */
    VPS_ISS_OUTPUT_MSB_POS_BIT15 = 0x1,
    /**< Output Bits are on [15:1] */
    VPS_ISS_OUTPUT_MSB_POS_BIT14 = 0x2,
    /**< Output Bits are on [15:2] */
    VPS_ISS_OUTPUT_MSB_POS_BIT13 = 0x3,
    /**< Output Bits are on [15:3] */
    VPS_ISS_OUTPUT_MSB_POS_BIT12 = 0x4,
    /**< Output Bits are on [15:4] */
    VPS_ISS_OUTPUT_MSB_POS_BIT11 = 0x5,
    /**< Output Bits are on [15:5] */
    VPS_ISS_OUTPUT_MSB_POS_BIT10 = 0x6,
    /**< Output Bits are on [15:6] */
    VPS_ISS_OUTPUT_MSB_POS_BIT9 = 0x7,
    /**< Output Bits are on [15:7] */
    VPS_ISS_OUTPUT_MSB_POS_BIT8 = 0x8,
    /**< Output Bits are on [15:8] */
    VPS_ISS_OUTPUT_MSB_POS_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed, will
                             *always be contained in int */
} vpsissIspOutDataMsbPos_t; /**< vpsissIspOutDataMsbPos_t */

/**
 *  \brief Lists the valid ISS L3 initiators
 */
typedef enum vpsissL3Initiator
{
    VPS_ISS_INIT_CAL_A_CPORT_X = 0x0U,
    /**< CAL A for all cports. */
    VPS_ISS_INIT_CAL_B_CPORT_X,
    /**< CAL B for all cports */
    VPS_ISS_INIT_IPIPEIF_RD,
    /**< IPIPE IF memory read */
    VPS_ISS_INIT_ISIF_LSC_RD,
    /**< LSC Lut Read */
    VPS_ISS_INIT_ISIF_WR,
    /**< RAW write to memory */
    VPS_ISS_INIT_IPIPE_BOXCAR,
    /**< BOXCAR Output */
    VPS_ISS_INIT_ISIF_H3A,
    /**< H3A stats output */
    VPS_ISS_INIT_RSZ_A,
    /**< Re Seizer A output */
    VPS_ISS_INIT_RSZ_B,
    /**< Re Seizer B output */
    VPS_ISS_INIT_SIMCOP_DMA,
    /**< SIMCOP DMA */
    VPS_ISS_INIT_SIMCOP_LDC,
    /**< SIMCOP LDC Lut read */
    VPS_ISS_INIT_MAX
    /**< Max value marker */
} vpsissL3Initiator_t; /**< vpsissL3Initiator_t */

/**
 *  \brief Different level of routing priority from ISS to L3.
 *
 *      OCPM1 - Has the highest and should be used for real time traffic
 *                  Such as capturing from external interface
 *      OCPM2 - Has the second highest priority. Recommended for non-real time
 *                  traffic
 *      OCPM3 - Has the least priority. Recommended for non-real time traffic.
 *
 *      \warning All combinations of streams/priority may not be supported.
 *          e.g. SIMCOP LDC & DMA priority is fixed. It will always be on OCPM3
 *          Refer the TRM for more possible combinations.
 */
typedef enum vpsissL3RoutingPri
{
    VPS_ISS_L3_ROUTING_OCPM2 = 0x0U,
    /**<  Second highest priority */
    VPS_ISS_L3_ROUTING_OCPM1 = 0x1U,
    /**<  Highest priority */
    VPS_ISS_L3_ROUTING_OCPM3 = 0x2U,
    /**<  Least priority */
    VPS_ISS_L3_ROUTING_FORCE_INT = 0x7FFFFFFF
                                   /**< This will ensure enum is not packed,will
                                    *always be contained in int */
} vpsissL3RoutingPri_t; /**< vpsissL3RoutingPri_t */

/*  \brief Generic ISP Parameters
 *  Structure containing Generic ISP parameters, used in the capture and
 *  ISS m2m drivers for initial path and format settings. Individual modules
 *  settings can be done using module specific ioctls.
 */

typedef struct vpsissIspParams
{
    Fvid2_Format      inFmt;
    /**< input Frame Format,
     *   Used for specifying input active frame size and frame data formt
     *   For the instances 2 and 3, only Bayer DataFormat is supported,
     *   Only Frame size, dataFormat and bpp variables are used from this
     *   structure */
    uint32_t          enableStreams[VPS_ISS_STREAM_ID_MAX];
    /**< List of flag to enable perticular output
     *   Driver checks only for output streams,
     *   does not use flag for the input stream
     *   Available streams depends on the path selected
     *      for example, H3A outputs can be enabled only if ISIF
     *      module is in the path */
    uint32_t          enableWdrMerge;
    /**< Flag to enable WDR merge, when enabled, it expects
     *   the frame format of the previous frame to be speciefied in inFmtN_1
     *   also it expects the pointer to the buffer in the
     *   stream id VPS_ISS_STREAM_ID_INPUT_N1
     *   Not valid for on the fly capture */
    uint32_t          enableVportCompInput;
    /**< Flag to select the input source to the IPIPEIF
     *   It could be either Vport or companding output.
     *   0: Vport input, any other value: Companding input
     *
     *   Note that enableWdrMerge and enableVportCompInput can
     *   not be enabled at the same time as same companding input
     *   cannot be used for both the muxes */
    uint32_t          enableDfs;
    /**< Not used as of now */
    Fvid2_Format      inFmtN_1;
    /**< Format format for the input N-1 Frame,
     *   Used to sepcify the frame format of the previous
     *   frame for WDR merge. This frame is read from the memory in IPIPEIF
     *   and merged with the frame coming frame vport
     *   Not used in on-the-fly capture,
     *   Used only if enableWdrMerge/enableDfs flag is set */
    vpsissGlbcePath_t glbcePath;
    /**< GLBCE path Selection */
    vpsissNsf3Path_t  nsf3Path;
    /**< Nsf3 path Selection */
    uint32_t          enableDpcPreNsf3;
    /**< Flag to enable DPC before the NSF3,
     *   only valid if NSF3 is enabled in nsf3Path,
     *   DPC parameters are set using IPIPE configuration */
    uint32_t          enableCnf;
    /**< Flag to enable CNF at the RSZA output,
     *   Used only when RSZ is in the path and
     *   output format is set to YUV420 */
    uint32_t          enableRszInputFromIpipeif;
    /**< Flag to enable Resizer input from Ipipeif,
     *   Resizer gets its input from IPIPE, this flag is used to
     *   enable resizer input from IPIPEIF.
     *   When this is enabled, IPIPE is not used in the path and will
     *   not be enabled */
    uint32_t          useWen;
    /**< Flag to make use of Write Enable Signal */
    Fvid2_Polarity    hdPol;
    /**< Polarity of the HD Signal */
    Fvid2_Polarity    vdPol;
    /**< Polarity of the VD Signal */
} vpsissIspParams_t; /**< vpsissIspParams_t */

/*  \brief VP1 Configuration
 *  Structure containing VP1 Configuration, Video Port1 is a port
 *  between IPIPEIF and ISIF. This port also connects NSF3 to the ISP.
 *  This structure is used to introduce the delay in hsync/vsync and setting up
 *  the crop window.
 */
typedef struct vpsissIspVp1Config
{
    uint32_t         enableDelay;
    /**< Enables/Disables delay between NSF3V input VD/HD and output VD/HD,
     *   Used typically when NSF3 is in ISP path and DFS/WDR is enabled
     *   In this case, VD must be at least one line earlier than first line */
    uint32_t         horzDelay;
    /**< Horizontal delay from HD_IN to HD_OUT in terms of cycles
     *   Depends on the NSF3 format
     *   for 16 bit input, max clock delay is 16
     *   for 8 bit input, max clock delay is 8
     *   When max value is used, there is no delay between input to output
     *   When less than max value is used, actual delay is (max - value) */
    uint32_t         vertDelay;
    /**< Vertical Delay of VP1 port from VD_IN to VD_OUT
     *   This value should be equal to or smaller than NSF3V
     *   line latency for meaningfull operation
     *   The value of 0 to 3 can be used when only top border is replicated
     *   The value of 0 to 17 can be used when only bottom or both top
     *   and bottom borders are replicated in NSF3 */
    Fvid2_CropConfig cropWin;
    /**< Horizontal/Vertical start position and frame size
     *   Horizontal size is in terms of cycles, so YUV422 8 bit input,
     *   horizontal size = width * 2 */
    uint32_t         enableYcSwap;
    /**< The ISIF module has a 16-bit interface. When 16-bit YUV data
     *   are input, the luma data (YIN7-0) are expected to be on
     *   the 8 MS bits and the chroma (CIN7-0) data are expected
     *   to be on the LS bits. This enables to swap the 8 MS bits
     *   with the 8 LS bits of the interface in case the luma and
     *   chroma do not come in the correct order. */
    uint32_t         enableLumaOddPos;
    /**< Selects the Luma at the odd position in YUV422 data */
} vpsissIspVp1Config_t; /**< vpsissIspVp1Config_t */

/*  \brief VP2 Configuration
 *  Structure containing VP2 Configuration, Video Port2 is a port
 *  between IPIPEIF and IPIPE. This port also connects GLBCE to the ISP.
 *  This structure is used to configure in hsync/vsync and setting up
 *  starting position.
 */
typedef struct vpsissIspVp2Config
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
} vpsissIspVp2Config_t; /**< vpsissIspVp2Config_t */

/**
 *  \brief Configure priority of ISS data sources. Refer IOCTL
 *          #VPS_ISS_SET_ISS_STREAM_PRI_CONFIG
 *
 *  \warning All combinations of streams/priority may not be supported.
 *              Please refer TRM for valid combinations.
 */
typedef struct vpsissRoutingConfig
{
    uint32_t             numStreams;
    /**< Number of streams that you want to configure */
    vpsissL3Initiator_t  source[VPS_ISS_INIT_MAX];
    /**< Specify the data traffic source */
    vpsissL3RoutingPri_t priority[VPS_ISS_INIT_MAX];
    /**< Specify its associated priority */
    uint32_t             cportId[VPS_ISS_INIT_MAX];
    /**< Applicable only for CAL. Ignored for others.
     *      Currently ignored, capture core configure each of the streams as
     *      highest priority. */
}vpsissRoutingConfig_t; /**< vpsissRoutingConfig_t */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_ISP_H_ */
