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
 *  \file vpshal_ipipeif.h
 *
 *  \brief This file defines all abstractions for IPIPEIF module of ISS.
 *  This abstraction support multiple opens (handles) even though we have single
 *  instance of the module. This enables simpler implementation of drivers/
 *  applications.
 *  The caller will have to ensure mutual exclusiveness
 *
 *  \warning The following steps lists sequence of API for a WDR merge.
 *  1. Determine the order for the merge. i.e. determine if VPORT would receive
 *      short exposure frame / long exposure frame. Similarly determine ISIF
 *      would receive short / long exposure frame.
 *  2. Initialize / Open the hal
 *  3. Set the complete config required for PASS 2 i.e. WDR merge
 *  4. PASS 1
 *  5. Setup for pass one using control command
 *          VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG, with following config
 *          isshalIpipeifRtCfg_t.enableWdr = FALSE
 *          isshalIpipeifRtCfg_t.inpSrc1 = as required
 *          isshalIpipeifRtCfg_t.inpSrc2 = as required
 *  6. Start other modules that feed into IPIPE IF, on completion.
 *  7. PASS 2
 *  8. Specify the address of PASS 1 frame buffer using command
 *      VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS
 *  9. Setup for WDR merge using VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG
 *          VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG, with following config
 *          isshalIpipeifRtCfg_t.enableWdr = TRUE
 *          isshalIpipeifRtCfg_t.inpSrc1 = as required
 *          isshalIpipeifRtCfg_t.inpSrc2 = as required
 *  10. Start using VPS_HAL_ISS_IOCTL_START
 *  11. Start other modules that feed into IPIPE IF. On completion, stop using
 *      VPS_HAL_ISS_IOCTL_STOP.
 *
 */

#ifndef VPSHAL_ISSIPIPEIF_H_
#define VPSHAL_ISSIPIPEIF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/include/iss/vps_cfgipipeif.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Defines the total number of opens supported. */
#define VPS_HAL_ISS_IPIPEIF_OPEN_NUM        (8U)

/** \brief Defines the total number of IPIPE IF available */
#define VPS_HAL_ISS_IPIPEIF_MAX_INST        (1U)

/* Control Commands supported by IPIPE IF */

/* CONTROL Command Supported */
/**
 *  VPS_HAL_ISS_IOCTL_START
 *  \brief START generic command is supported. This requires to be used when
 *          MEM IF is used to read a frame
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_START
 *  \param cmdArgs  None.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */

/**
 *  VPS_HAL_ISS_IOCTL_STOP
 *  \brief STOP generic command is supported. This requires to be used when
 *          MEM IF is used to read a frame
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_STOP
 *  \param cmdArgs  None.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SETCFG
 *  \brief This control is to be used to update the configuration.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SETCFG
 *  \param cmdArgs  A pointer of type isshalIpipeifCfg_t. All the enabled
 *                      modules should have a valid config.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SETCFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_BEGIN + 1U)
/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG
 *  \brief This control is to be used to update the configuration.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG
 *  \param cmdArgs  A non NULL pointer of type isshalIpipeifRtCfg_t
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SETCFG + 1U)
/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS
 *  \brief This control is to be used to update address of the frame to be read.
 *
 *  \warning Please enusre IPIPE IF has been configured read in a frame from
 *              memory.
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS
 *  \param cmdArgs  A pointer of type, uint32_t. which should define a 32 bit
 *                      valid address aligned on 32 bytes boundary.
 *                      i.e. bits 0 - 4 should be ZERO / Ignored
 *  \param arg      A pointer of type, uint32_t. which should define a 11 bit
 *                      valid line stride
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SETRTCFG + 1U)
/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT
 *  \brief This control is to be used to update the various LUT used in IPIPE IF
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT
 *  \param cmdArgs  A pointer of type, vpsissIpipeifLutCfg_t. With at least
 *                      1 non-null pointer for a lut.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_BUFFERS + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SET_CLK_POL_FIFO
 *  \brief This control is to be used to configure clock, FIFO watermark,
 *          polarity of video sync signals. Refer isshalIpipeifClkCfg_t
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SET_CLK_POL_FIFO
 *  \param cmdArgs  A pointer of type, isshalIpipeifLutCfg_t.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SET_CLK_POL_FIFO \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_UPDATE_LUT + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_GET_CLK_POL_FIFO
 *  \brief This control is to be used to retrive current clock, FIFO watermark,
 *          polarity of video sync signals. Refer isshalIpipeifClkCfg_t
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_GET_CLK_POL_FIFO
 *  \param cmdArgs  A pointer of type, isshalIpipeifLutCfg_t.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_GET_CLK_POL_FIFO \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SET_CLK_POL_FIFO + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG
 *  \brief This control is to be used to set the companding and decompanding
 *         modules configuration
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG
 *  \param cmdArgs  A pointer of type, vpsissIpipeifDeCompandInsts_t.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_GET_CLK_POL_FIFO + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG
 *  \brief This control is to be used to set WDR Configuration
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG
 *  \param cmdArgs  A pointer of type, vpsissIpipeifWdrCfg_t.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SET_COMPDECOMP_CFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG
 *  \brief This control is to be used to set WDR Configuration
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG
 *  \param cmdArgs  A pointer of type, vpsissIpipeifSaturaInsts_t.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SET_WDR_CFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG
 *  \brief This control is to be used to get default/expert configuration
 *         for IPIPEIF.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG
 *  \param cmdArgs  A pointer of type, isshalIpipeifCfg_t.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SET_SATURATION_CFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG
 *  \brief This control is to be used to configure DPC sub-block on ISIF input
 *          path.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG
 *  \param cmdArgs  A pointer to an array of vpsissIpipeifDpcCfg_t with 2
 *                      instances.
 *                      Location 0x0 holds DPC config for vport or isif input
 *                      Location 0x1 holds DPC config for memory input.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_GET_DEFAULTCFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_SET_FRAME_CFG
 *  \brief This control is to be used to configure Frame size.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG
 *  \param cmdArgs  A pointer to an array of isshalIpipeifFrameCfg_t
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_SET_FRAME_CFG \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SET_DPC_CFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT
 *  \brief Control command used to enable / disable. Supports
 *          DeCompanding on Vport & saturation on Vport / ISIF inputs
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT
 *  \param cmdArgs  A pointer to an array of vpsissIpipeifCtrl_t
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_SET_FRAME_CFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_IPIPEIF_ENABLE_INPUT_IF
 *  \brief Control command to enable Input Sd Ram interface
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT
 *  \param cmdArgs  not used
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_IPIPEIF_ENABLE_INPUT_IF \
    (VPS_HAL_ISS_IOCTL_IPIPEIF_EN_DIS_COMP_DECOMP_SAT + 1U)

/** \brief IOCTL Gaurd macro */
#if (VPS_HAL_ISS_IOCTL_IPIPEIF_ENABLE_INPUT_IF > \
     VPS_HAL_ISS_IOCTL_IPIPEIF_END)
    #error "Increase VPS_HAL_ISS_IOCTL_IPIPEIF_NUM in file vpshal_iss.h file"
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  enum isshalIpipeifInstId
 *  \brief Enum to define the various H3A instance.
 */
typedef enum isshalIpipeifInstId
{
    ISSHAL_IPIPEIF_INST_0 = 0,
    /**< Ipipeif Instance Id 0. */
    ISSHAL_IPIPEIF_INST_MAX_ID = 1,
    /**< Max - used for error check. */
    ISSHAL_IPIPEIF_INST_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed, will always be contained in int */
} isshalIpipeifInstId_t;

/**
 *  enum isshalIpipeifIsifOutSrc
 *  \brief Enum for selecting output configuration for ISIF out port
 */
typedef enum isshalIpipeifIsifOutSrc
{
    ISSHAL_IPIPEIF_ISIF_OUT_MIN = 0x0,
    /**< enum min marker */
    ISSHAL_IPIPEIF_ISIF_OUT_RAW_VPORT = 0x1,
    /**< Raw data from VPORT is sent to ISIF out */
    ISSHAL_IPIPEIF_ISIF_OUT_MEMIF = 0x2,
    /**< Data from DPM, read via MEM IF is sent to ISIF out */
    ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS = 0x3,
    /**< Data from DFS/WDR (companded), is sent to ISIF out */
    ISSHAL_IPIPEIF_ISIF_OUT_MEMIF_YUV = 0x4,
    /**< YUV data from DPM, read via MEM IF is sent to ISIF out */
    ISSHAL_IPIPEIF_ISIF_OUT_IP_MAX = 0x5,
    /**< enum max marker */
    ISSHAL_IPIPEIF_ISIF_OUT_FORCE_INT = 0x7FFFFFFF
                                        /**< This will ensure enum is not packed, will always be contained in int */
} isshalIpipeifIsifOutSrc_t;

/**
 *  enum isshalIpipeifIpipeOutSrc
 *  \brief Enum for selecting output configuration for IPIPE out port
 */
typedef enum isshalIpipeifIpipeOutSrc
{
    ISSHAL_IPIPEIF_IPIPE_OUT_MIN = 0x0,
    /**< enum min marker */
    ISSHAL_IPIPEIF_IPIPE_OUT_ISIF = 0x1,
    /**< Data from ISIF is sent to IPIPE out */
    ISSHAL_IPIPEIF_IPIPE_OUT_MEMIF = 0x2,
    /**< Data from DPM, read via MEM IF is sent to IPIPE out */
    ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS = 0x3,
    /**< Data from DFS/WDR (companded), is sent to IPIPE out */
    ISSHAL_IPIPEIF_IPIPE_OUT_MEMIF_YUV = 0x4,
    /**< YUV data from DPM, read via MEM IF is sent to IPIPE out */
    ISSHAL_IPIPEIF_IPIPE_OUT_IP_MAX = 0x5,
    /**< enum max marker */
    ISSHAL_IPIPEIF_IPIPE_OUT_FORCE_INT = 0x7FFFFFFF
                                         /**< This will ensure enum is not packed, will always be contained in int */
} isshalIpipeifIpipeOutSrc_t;

/**
 *  struct isshalIpipeifFrameCfg
 *  \brief Define the frame configuration, when reading frame via m2mif.
 */
typedef struct isshalIpipeifFrameCfg
{
    uint32_t ppln;
    /**< Interval of HD in pixels OR start pixel in HD */
    uint32_t lpfr;
    /**< Interval of VD in lines OR start line in VD */
    uint32_t hnum;
    /**< Number of valid pixels in a line */
    uint32_t vnum;
    /**< Number of valid lines in a frame */
} isshalIpipeifFrameCfg_t;

/**
 *  struct isshalIpipeifDpcmCfg
 *  \brief Configuration parameters of de-compression module
 */
typedef struct isshalIpipeifDpcmCfg
{
    uint32_t enable;
    /**< Enable de-compression. TRUE enables it, FALSE disables */
    uint32_t pred;
    /**< TRUE configures for advanced prediction mode, FALSE for normal mode */
    uint32_t bits;
    /**< TRUE configures for 8 bit to 12 bit de-compression, FALSE configures
     *  for 8 bit to 10 bit de-compression */
} isshalIpipeifDpcmCfg_t;

/**
 *  struct isshalIpipeifDecimation
 *  \brief Configuration parameters of decimation filer
 */
typedef struct isshalIpipeifDecimation
{
    uint32_t enable;
    /**< TRUE enables horizontal decimation and FALSE disables. When disabled
     *  below config values are ignored */
    uint32_t rsz;
    /**< Configure the decimation ratio. Valid values are between 16 & 112,
     *  including 16 & 112.
     *  Ratio = 16 / rsz i.e. ratio between 1/1 to 1/7 is supported */
    uint32_t crop;
    /**< A non zero value could be used to drop pixel data.
     * i.e. active line length was 1280 and we require to drop 1 - 10 active
     * pixels
     * after resize operation, crop should be set to 10.
     * Valid values are 1 to 8191, provided active line length (post scale) is
     * not
     * exceeded.
     * Maps to register IPIPEIF_INIRSZ.INIRSZ
     */
} isshalIpipeifDecimation_t;

/**
 *  struct isshalIpipeifIsifOutCfg
 *  \brief Specifies the configurations for output port ISIF. This includes the
 *  input ports / modules used and there config.
 */
typedef struct isshalIpipeifIsifOutCfg
{
    isshalIpipeifIsifOutSrc_t inpSrc1;
    /**< Configure source of ISIF output port. When configured with
     *      ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS DFS/WDR is chosen */
    uint32_t                  oneShot;
    /**< When data is read from memory, two way of operations is possible
     *  TRUE configures for one short mode
     *  FALSE for continuous mode */
} isshalIpipeifIsifOutCfg_t;

/**
 *  struct isshalIpipeifIpipeOutCfg
 *  \brief Specifies the configurations for output port IPIPE. This includes the
 *  input ports / modules used and there config.
 */
typedef struct isshalIpipeifIpipeOutCfg
{
    isshalIpipeifIpipeOutSrc_t inpSrc2;
    /**< Configure source of IPIPE output port. When configured for
     *      ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS DFS/WDR is chosen */
    uint32_t                   enable121Avg;
    /**< TRUE enables 121 average filter, FALSE disables it */
    isshalIpipeifDecimation_t  deciCfg;
    /**< Configure decimation block */
    uint32_t                   gainCfg;
    /**< Control the gain, it applicable only for RAW data. Value is expressed
     *  as U10Q9. */
    uint32_t                   oclip;
    /**< Output clipping after gain, this value is expressed in U16Q0.
     *  For non WDR modes value should be 0 < oclip < 4096
     *  For WDR mode value should be 0 < oclip < 65536 */
} isshalIpipeifIpipeOutCfg_t;

/**
 *  struct isshalIpipeifH3aOutCfg
 *  \brief Specifies the configurations for output port H3A. This includes the
 *  input ports / modules used and there config.
 */
typedef struct isshalIpipeifH3aOutCfg
{
    uint32_t                  enable121Avg;
    /**< TRUE enables 121 average filter, FALSE disables it */
    isshalIpipeifDecimation_t deciCfg;
    /**< Configure decimation block */
} isshalIpipeifH3aOutCfg_t;

/**
 *  struct isshalIpipeifPackCfg
 *  \brief Configure the packed / unpacked incoming data into packed / un
 *      packed streams.
 */
typedef struct isshalIpipeifPackCfg
{
    uint32_t unpack;
    /**< Refer spec for details. Valid range is 0 to 3 */
    uint32_t datasft;
    /**< Refer spec for details. Valid range is 0 to 7 */
    uint32_t raw16_memif;
    /**< Refer spec for details. Valid range is 0 to 1 */
} isshalIpipeifPackCfg_t;

/**
 *  struct isshalIpipeifClkCfg
 *  \brief Configure the module clock dividers, FIFO watermark, polarity of
 *      video sync signals.
 */
typedef struct isshalIpipeifClkCfg
{
    /* Following parameters are applicable only when data is READ from memory.
     *  i.e. through memif */
    uint32_t vdPol;
    /**< Specifies polarity of the vSync.
     *  FALSE (0) indicates active high
     *  TRUE (1) indicates indicates active low */
    uint32_t hdPol;
    /**< Specifies polarity of the hSync.
     *  FALSE (0) indicates active high
     *  TRUE (1) indicates indicates active low */
    uint32_t fifoWmrkLvl;
    /**< Configure the FIFO water mark level, Valid values are 0 - 16.
     *  A internal FIFO for 16 entries is maintained by IP.
     *  A value of 5 indicates that no more than 5 valid entries are present
     *      in FIFO, provided that there is more data to read. */
    uint32_t enableM2MStall;
    /**< Enable stall mechanism when operated in m2m mode. TRUE enables it
     *      FALSE disables the stall */
    uint32_t moduleClockSel;
    /**< In M2M mode,
     *      TRUE indicates that pixel clock for IPIPEIF and IPIPE is derived
     *      from ISS functional clock (post divider value below)
     *      FALSE indicates that pixel clock is sourced from vport. Divider
     *      below has no effect */
    /* pixel clock = functional clock * (clkDivM / clkDivN) */
    uint32_t clkDivM;
    /**< In M2M mode, When pixel clock is not sourced from vport, the clock is
     *  divider value could be specified. Valid range is 0 to 0xFF */
    uint32_t clkDivN;
    /**< In M2M mode, When pixel clock is not sourced from vport, the clock is
     *  divider value could be specified. Valid range is 0 to 0xFF */
} isshalIpipeifClkCfg_t;

/**
 *  struct isshalIpipeifCfg
 *  \brief Once created, the configuration could updated with appropriate IOCTL,
 *          with this structure specifying the required configuration.
 */
typedef struct isshalIpipeifCfg
{
    isshalIpipeifFrameCfg_t       ipFrameCfg;
    /**< Configure input frame config */

    isshalIpipeifPackCfg_t        unpack;
    /**< Configure packing modes */

    vpsissIpipeifDeCompandInsts_t compDecompCfg;
    /**< Companding and Decompanding configuration configuration */

    vpsissIpipeifSaturaInsts_t    satCfg;

    vpsissIpipeifDpcCfg_t         memIfDpcCfg;
    /**< Configure defect pixel correction on memory input path */
    vpsissIpipeifDpcCfg_t         vportOrIsififDpcCfg;
    /**< Configure defect pixel correction on vport or isif input path */

    isshalIpipeifDpcmCfg_t        memifDpcmCfg;
    /**< Configure de-compression module */

    vpsissIpipeifWdrCfg_t         wdrCfg;
    /**< Configure WDR parameters */

    isshalIpipeifIsifOutCfg_t     isifOutCfg;
    /**< Configures source, path and module parameters that govern isif out
     *  path */
    isshalIpipeifIpipeOutCfg_t    ipipeOutCfg;
    /**< Configures source, path and module parameters that govern ipipe out
     *  path */
    isshalIpipeifH3aOutCfg_t      h3aOutCfg;
    /**< Configures source, path and module parameters that govern h3a out
     *  path */
} isshalIpipeifCfg_t;

/**
 *  struct isshalIpipeifRtCfg
 *  \brief Used to update few configurations, that are expected to be changed
 *          with every frame.
 *  \warning All parameters of this structure is expected to hold a valid
 *              configuration. No checks are performed while applying.
 */
typedef struct isshalIpipeifRtCfg
{
    isshalIpipeifIsifOutSrc_t  inpSrc1;
    /**< Configure source of ISIF output port. When configured with
     *      ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS DFS/WDR is choosen */
    isshalIpipeifIpipeOutSrc_t inpSrc2;
    /**< Configure source of IPIPE output port. When configured for
     *      ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS DFS/WDR is choosen */
    uint32_t                   enableWdr;
    /**< TRUE configure for WDR merge operation.
     *  In Addition to configuring this as TRUE
     *  isifOutCfg.inpSrc1 should be equals to ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS.
     *  OR
     *  ipipeOutCfg.inpSrc2 should be equalsto ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS.
     *
     *  FALSE Configures for Dark frame subtraction. Currently not supported.
     *  In addition to configuring this as FALSE,
     *  isifOutCfg.inpSrc1 should NOT be ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS.
     *  OR
     *  ipipeOutCfg.inpSrc2 should NOT be ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS.
     */
} isshalIpipeifRtCfg_t;

/**
 *  struct isshalIpipieifInstParams
 *  \brief Initialization parameters, These parameters cannot be changed once
 *          initialized
 */
typedef struct isshalIpipieifInstParams
{
    uint32_t instId;
    /**< Instand Id. For valid values see #isshalIpipeifInstId. */
    uint32_t baseAddress;
    /**< IPIPE IF registers base address */
    uint32_t lut0Addr[1U];
    /**< VP DeCompanding LUT Address */
    uint32_t lut0Size;
    /**< Number of bytes that represent this LUT */
    uint32_t lut1Addr[1U];
    /**< MEM IF DeCompanding LUT Address */
    uint32_t lut1Size;
    /**< Number of bytes that represent this LUT */
    uint32_t lut2Addr[1U];
    /**< WDR Companding LUT Address */
    uint32_t lut2Size;
    /**< Number of bytes that represent this LUT */
    uint32_t prms;
    /**< Not used */
} isshalIpipieifInstParams_t;

/**
 *  struct isshalIssIpipieifOpenParams
 *  \brief No control as of now.
 *
 */
typedef struct isshalIssIpipieifOpenParams
{
    uint32_t instId;
    /**< Identifies the instance of IPIPE IF. Currently should be 0 */
}isshalIssIpipieifOpenParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initializes IPIPE IF modules, performs following operations
 *
 *  \param numInst  Number of instances of IPIPE IF that requires to be init.
 *  \param initPrms Pointer to array of #isshalIpipieifInstParams_t. This array
 *                      should contain numInst valid entries.
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
int32_t VpsHal_issipipeifInit(uint32_t                          numInst,
                              const isshalIpipieifInstParams_t *initPrms,
                              Ptr                               arg);

/**
 *  \brief De-initializes the IPIPE IF modules and performs following actions
 *
 *  \param arg  Not used for now. Should be NULL
 *
 *  \return     Returns FVID2_SOK on success else returns error value
 */
int32_t VpsHal_issipipeifDeInit(Ptr arg);

/**
 *  VpsHal_issipipeifOpen
 *  \brief This function should be called prior to calling any of the IPIPEI
 *  abstraction APIs are used. This should be called post initialization of
 *  ipipeif module.
 *
 *  \param openPrms Open Parameters
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         A non NULL pointers, NULL on errors.
 */
VpsHal_Handle VpsHal_issipipeifOpen(const isshalOpenParams_t
                                    *openPrms, Ptr arg);

/**
 *  VpsHal_issipipeifClose
 *  \brief This function should be called to close previously opened abstraction
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeifClose(VpsHal_Handle handle, Ptr arg);

/**
 *  VpsHal_issipipeifControl
 *  \brief VTNF specific control commands.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_issipipeifOpen
 *  \param cmd      A valid control command, refer above for valid commands
 *  \param cmdArgs  Arguments for the control command, depends on the control
 *                  command used.
 *  \param arg      Arguments for the control command, depends on the control
 *                  command used.
 *
 *  \return         Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeifControl(VpsHal_Handle handle,
                                 UInt32        cmd,
                                 Ptr           cmdArgs,
                                 Ptr           arg);

/**
 *  VpsHal_issipipeifAfStart
 *  \brief IPIPEIF Api for enabling the module. Used to start the IPIEIF block
 *         in either free running or in One-Shot mode. In one-short mode,
 *         it will be disabled at the end of frame processing. In free running
 *         mode, it should be disabled by calling stop API.
 *
 *  \param handle           Instance handle
 *  \param procMode         Processing Mode either one shot or free running
 *  \param arg              Not Used
 *
 *  \return                 Returns 0 on success else returns error value
 */
int32_t VpsHal_issipipeifStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);
int32_t VpsHal_issipipeifStop(
    VpsHal_Handle handle,
    Ptr           arg);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSHAL_ISSIPIPEIF_H_ */
