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
 *  \file vps_cfgrsz.h
 *
 *  \brief
 *
 */

/**
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_IPIPEIF ISS - IPIPEIF Config API
 *
 *  @{
 */

#ifndef VPS_CFG_IPIPEIF_H_
#define VPS_CFG_IPIPEIF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Ioctl for getting IPIPEIF parameters
 */
#define VPS_ISS_IPIPEIF_IOCTL_GET_CONFIG (VPS_ISS_IOCTL_IPIPEIF_IOCTL_BASE + 0U)

/**
 *  \brief Ioctl for setting IPIPEIF parameters
 */
#define VPS_ISS_IPIPIEF_IOCTL_SET_CONFIG (VPS_ISS_IPIPEIF_IOCTL_GET_CONFIG + 1U)

/**
 *  \brief IPIPEIF Companding and Decompanding LUT size
 */
#define VPS_ISS_IPIPEIF_COMP_DECOMP_LUT_SIZE     (513U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Sub Blocks with in IPIPE IF that could be controlled/configured.
 */
typedef enum vpsissIpipeifModule
{
    VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT = 0x0,
    /**< Control Command to update the Companding and Decompanding LUT */
    VPS_ISS_IPIPEIF_MODULE_COMPA_DECOMPA_CFG = 0x1,
    /**< Control Command to set Companding and Decompanding
         Configuration on Vport Input, Memory input and WDR Merge output */
    VPS_ISS_IPIPEIF_MODULE_SATURATION_CFG = 0x2,
    /**< Control command to set Saturation Configuration for VPort input
         memory input and isif input */
    VPS_ISS_IPIPEIF_MODULE_WDR_MERGE_CFG = 0x3,
    /**< Control command for setting parameters/configuration for WDR Merge */
    VPS_ISS_IPIPEIF_MODULE_DPC_CFG = 0x4,
    /**< Control command for enabling / configuring DPC on memory / vport
        input & isif input */
    VPS_ISS_IPIEIF_MODULE_ID_MAX = 0x7FFFFFFF
                                   /**< Ensures enum is 32 bit wide */
} vpsissIpipeifModule_t;    /**< vpsissIpipeifModule_t */

/**
 *  \brief Instance Id of the Comp/Decomp Module.
 */
typedef enum vpsissIpipeifCompDecompInst
{
    VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_VCOMP_DECOMP = 0x1,
    /**< Vcomp Decompanding Instance */
    VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_MEMIF_DECOMP = 0x2,
    /**< Vcomp Decompanding Instance */
    VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_WDR_COMP = 0x4,
    /**< Vcomp Decompanding Instance */
    VPS_ISS_IPIPEIF_MODULE_COMP_DECOMP_INST_ALL = 0x7
    /**< Control command for setting parameters /
            configuration for WDR Merge */
} vpsissIpipeifCompDecompInst_t;    /**< vpsissIpipeifCompDecompInst_t */

/**
 *  \brief Instance Id of the Saturation Module.
 */
typedef enum vpsissIpipeifSaturationInst
{
    VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_VCOMP = 0x0,
    /**< Vcomp Decompanding Instance */
    VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_MEMIF = 0x1,
    /**< Vcomp Decompanding Instance */
    VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ISIF = 0x2,
    /**< Vcomp Decompanding Instance */
    VPS_ISS_IPIPEIF_MODULE_SATURATION_INST_ALL = 0x3
    /**< Control command for setting parameters /
            configuration for WDR Merge */
} vpsissIpipeifSaturationInst_t;    /**< vpsissIpipeifSaturationInst_t */

/**
 *  \brief Configuration parameters of defect pixel correction
 */
typedef struct vpsissIpipeifDpcCfg
{
    uint32_t enable;
    /**< Enable defect pixel correction */
    uint32_t th;
    /**< DPC threshold value */
} vpsissIpipeifDpcCfg_t;

/**
 *  \brief Updated de companding & companding look up tables. A non null pointer
 *      configures the driver to update the LUT, with values specified by the
 *      pointers.
 */
typedef struct vpsissIpipeifLutConfig
{
    uint32_t *vportDecompandLut;
    /**< Pointer to De Companding lut */
    uint32_t  vportLutSize;
    /**< Specify the size of the lut */

    uint32_t *memifDecompandLut;
    /**< Pointer to De Companding lut */
    uint32_t  memifLutSize;
    /**< Specify the size of the lut */

    uint32_t *wdrCompandLut;
    /**< Pointer to Companding lut */
    uint32_t  wdrLutSize;
    /**< Specify the size of the lut */
} vpsissIpipeifLutConfig_t;

/**
 *  \brief Configuration parameters of de-companding block.
 */
typedef struct vpsissIpipeifDeCompandConfig
{
    uint32_t enable;
    /**< TRUE enables de-companding block. FALSE disables de-companding */
    uint32_t size;
    /**< Configure the width of the companded data stream. Refer bit field
        LUTBITSEL of register IPIPEIF_VPDCMPCFG & IPIPEIF_SDDCMPCFG */
    uint32_t useLut;
    /**< The coefficients required by de-companding is provided via an LUT
         or via registers.
         Before setting it true, set the luts using
         VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT command  */
    /* Coefficients in case LUT is not used */
    uint32_t xthr1;
    /**< Threshold value, 16bit is used */
    uint32_t xthr2;
    /**< Threshold value, 16bit is used */
    uint32_t xthr3;
    /**< Threshold value, 16bit is used */
    uint32_t ythr1;
    /**< Threshold value, 20bit is used */
    uint32_t ythr2;
    /**< Threshold value, 20bit is used */
    uint32_t ythr3;
    /**< Threshold value, 20bit is used */
    uint32_t slope1;
    /**< Slope value, 16bit is used */
    uint32_t slope2;
    /**< Slope value, 16bit is used */
    uint32_t slope3;
    /**< Slope value, 16bit is used */
    uint32_t slope4;
    /**< Slope value, 16bit is used */
    uint32_t shift;
    /**< Shift value for PWL, 5 bits are used */
} vpsissIpipeifDeCompandConfig_t;

/**
 *  \brief Configuration parameters of dark frame subtraction / wide dynamic
 *  range block.
 */
typedef struct vpsissIpipeifWdrCfg
{
    uint32_t enable;
    /**< TRUE configure for WDR merge operation.
        In Addition to configuring this as TRUE
        isifOutCfg.inpSrc1 should be equals to ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS.
        OR
        ipipeOutCfg.inpSrc2 should be equalsto ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS.

        FALSE Configures for Dark frame subtraction. Currently not supported.
        In addition to configuring this as FALSE,
        isifOutCfg.inpSrc1 should NOT be ISSHAL_IPIPEIF_ISIF_OUT_WDR_DFS.
        OR
        ipipeOutCfg.inpSrc2 should NOT be ISSHAL_IPIPEIF_IPIPE_OUT_WDR_DFS.
        */
    uint32_t wdrDir;
    /**< TRUE configures WDR block to expect long exposure frame from MEMIF
            and short exposure from VPORT.
        FALSE configures WDR block to expect long exposure frame from VPORT
            and short exposure from MEMIF.
        DFSDIR */
    uint32_t dst;
    /**< Down shift value, after WDR merge. Range 0x0 to 0xF */
    uint32_t sbit;
    /**< Shift up value for short exposure frame. Range 0x0 to 0x7 */
    uint32_t lbit;
    /**< Shift up value for long exposure frame. Range 0x0 to 0x7 */
    uint32_t wgt_sel;
    /**< Select long / short frame for weight calculation. TRUE uses short frame
        FALSE uses long frame. Breaking coding guide lines, in order to maintain
        name similar to spec. */
    uint32_t afe;
    /**< WDR Merge parameter. Exponential part of value in weight calculation
        5 bits unsigned value */
    uint32_t afm;
    /**< WDR Merge parameter. Mantissa part of value in weight calculation
        16 bits signed value */
    uint32_t bf;
    /**< WDR Merge parameter. Q0.15 BF * 2 ^ -16 * 2 ^ -5
            0 - 15 (16)bits are used */
    uint32_t gshort;
    /**< WDR Merge parameter. Gain parameter to be applied for short frame.
            0 - 15 (16) bits are used. */
    uint32_t glong;
    /**< WDR Merge parameter. Gain parameter to be applied for long frame.
            0 - 15 (16) bits are used. */
    uint32_t thr;
    /**< Threshold value. 0 - 15 (16) bits are used */
    uint32_t lbk00;
    /**< Black level for long exposure. Applied to even pixel on even line.
        13 bits used. */
    uint32_t lbk01;
    /**< Black level for long exposure. Applied to odd pixel on even line.
        13 bits used. */
    uint32_t lbk10;
    /**< Black level for long exposure. Applied to event pixel on odd line.
        13 bits used. */
    uint32_t lbk11;
    /**< Black level for long exposure. Applied to odd pixel on odd line.
        13 bits used. */
    uint32_t sbk00;
    /**< Black level for short exposure. Applied to even pixel on even line.
        13 bits used. */
    uint32_t sbk01;
    /**< Black level for short exposure. Applied to odd pixel on even line.
        13 bits used. */
    uint32_t sbk10;
    /**< Black level for short exposure. Applied to event pixel on odd line.
        13 bits used. */
    uint32_t sbk11;
    /**< Black level for short exposure. Applied to odd pixel on odd line.
        13 bits used. */
    uint32_t mas;
    /**< Adaptive filter, slope config 16 bits are used. */
    uint32_t mad;
    /**< Adaptive filter, threshold config 16 bits are used. */
    uint32_t lwb[FVID2_BAYER_COLOR_COMP_MAX];
    /**< Long Exposure White balance for pixels. 13 bits used */
    uint32_t swb[FVID2_BAYER_COLOR_COMP_MAX];
    /**< Short Exposure White balance for pixels. 13 bits used */
    uint32_t mergeShift;
    /**< Post merger divide factor*/
    uint32_t mergeClip;
    /**< Post merger clip threshold*/

} vpsissIpipeifWdrCfg_t;

/**
 *  \brief Configuration parameters of saturation block
 */
typedef struct vpsissIpipeifSaturaConfig
{
    uint32_t enable;
    /**< TRUE enables saturation filter and FALSE disables. When disabled all
        below config values are ignored */
    uint32_t sat;
    /**< Value used in WDR split function for pseudo-long exposure frame.
        min is 0x0 and maximum if 0xFFFF. 0xFFFF disables sat */
    uint32_t dcClmp;
    /**< DC Clamp addition value, used in WDR split function for pseudo short
        frame. 8 LS bits would be used */
    uint32_t dsf;
    /**< Down shift value used in WDR split function, used for pseudo short
        frame */
} vpsissIpipeifSaturaConfig_t;

/**
 *  \brief Saturation control / config
 */
typedef struct vpsissIpipeifSaturaInsts
{
    vpsissIpipeifSaturationInst_t modInstId;
    /**< Instance Id of the Module */
    vpsissIpipeifSaturaConfig_t   vportSatCfg;
    /**< Configure saturation configuration on vport path */
    vpsissIpipeifSaturaConfig_t   memifSatCfg;
    /**< Configure saturation configuration on memory input */
    vpsissIpipeifSaturaConfig_t   isifSatCfg;
    /**< Configure saturation configuration on isif path */
} vpsissIpipeifSaturaInsts_t;

/**
 *  \brief De Companding control / config
 */
typedef struct vpsissIpipeifDeCompandInsts
{
    vpsissIpipeifCompDecompInst_t  modInstId;
    /**< Instand Id of the Module */
    vpsissIpipeifDeCompandConfig_t vportDeCompandCfg;
    /**< Configure de companding block on vport path */
    vpsissIpipeifDeCompandConfig_t memifDeCompandCfg;
    /**< Configure de companding block on memory path */
    vpsissIpipeifDeCompandConfig_t compandCfg;
    /**< Companding configuration */
} vpsissIpipeifDeCompandInsts_t;

/**
 *  \brief Control / Config parameters that tend change often
 */
typedef struct vpsissIpipeifCtrl
{
    vpsissIpipeifModule_t          module;
    /**< ID of the module to be configured. */
    vpsissIpipeifLutConfig_t      *pLutCfg;
    /**< Pointer to structure containing Companding and
         Decompanding Look up Tables,
         Used for updating these tables
         only used when module is set to #VPS_ISS_IPIPEIF_MODULE_UPDATE_LUT */
    vpsissIpipeifWdrCfg_t         *pWdrCfg;
    /**< Pointer to WDR configuration, also used for enabling/disabling WDR */
    vpsissIpipeifSaturaInsts_t    *pSatCfg;
    /**< Saturation configuration for the VPort, Memory and ISIF input paths */
    vpsissIpipeifDeCompandInsts_t *pCompDecompCfg;
    /**< Pointer to Companding and Decompanding Configuration */
    vpsissIpipeifDpcCfg_t         *pDpcCfg;
    /**< DPC configuration, pointer to array of size 2.
        Location 0 holds config for vport/isif input
        Location 1 holds config for memory input.
        CAUTION DPC on vport & isif is same. Depending on the WDR input
            DPC is either active on vport or isif lane. */
} vpsissIpipeifCtrl_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_CFG_IPIPEIF_H_ */

/* @} */

