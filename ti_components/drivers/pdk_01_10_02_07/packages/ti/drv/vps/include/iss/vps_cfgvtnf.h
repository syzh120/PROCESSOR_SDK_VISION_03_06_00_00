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
 *  \file vps_cfgvtnf.h
 *
 *  \brief  Defines the structures / control operations that could be used to
 *              configure / control LDC module
 */

/**
 *  \addtogroup BSP_DRV_VPS_COMMON_CAPTURE_SIMCOP_LDC_ISS
 *
 *  @{
 */

#ifndef VPS_CFG_VTNF_H_
#define VPS_CFG_VTNF_H_

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
 *  \brief VTNF Lut Size
 */
#define VPS_ISS_VTNF_LUT_SIZE            (32U)

/**
 *  enum isshalvtnfTriggerSrc
 *  \brief Enum for selecting Trigger Source
 */
typedef enum isshalvtnfTriggerSrc
{
    ISSHAL_VTNF_TRG_SRC_REG = 0,
    /**< Trigger Source is register write */
    ISSHAL_VTNF_TRG_SRC_HWSEQ = 1,
    /**< Trigger Source is Hardware sequencer */
    ISSHAL_VTNF_TRG_SRC_FORCE_INT = 0x7FFFFFFF
                            /**< This will ensure enum is not packed,
                             *      will always be contained in int */
} vpsissvtnfTriggerSrc_t;   /**< vpsissvtnfTriggerSrc_t */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct vpsissvtnfAdvConfig
 *  \brief Advanced configuration parameters of VTNF.
 */
typedef struct vpsissvtnfAdvConfig
{
    uint32_t               blockWidth;
    /**< Block width, must be multiple of 16 for YUV420 and
     *   multiple of 32 for YV12 formats and upto 512 */
    uint32_t               blockHeight;
    /**< Block Height, must be multiple of 4 and up to 128 */

    uint32_t               roundBitCount;
    /**< Bit count by which combined SAD value is rounded down to get
     *   the LUT index */
    uint32_t               colorWeight1;
    /**< Weight used for adjusting contribution of luma and chroma difference */
    uint32_t               colorWeight2;
    /**< Weight used for adjusting contribution of luma and chroma difference */
    uint32_t               lut1[VPS_ISS_VTNF_LUT_SIZE];
    /**< Lookup table contining alpha blending values to blend
     *   the previous frame output and current frame input for Luma */
    uint32_t               lut2[VPS_ISS_VTNF_LUT_SIZE];
    /**< Lookup table contining alpha blending values to blend
     *   the previous frame output and current frame input for Chroma */

    vpsissvtnfTriggerSrc_t triggerSource;
    /**< VTNF Trigger Source
     *   Supported in HAL
     *   Unsupported in driver - will be forced to ISSHAL_VTNF_TRG_SRC_HWSEQ */
    uint32_t               intrEnable;
    /**< Flag to enable/disable Interrupt,
     *   0: disables interrupt
     *   1: Enable interrupt
     *   Supported in HAL
     *   Unsupported in driver - will be forced to 1 */
} vpsissvtnfAdvConfig_t;

/**
 *  struct vpsissvtnfConfig
 *  \brief Configuration parameters of VTNF.
 */
typedef struct vpsissvtnfConfig
{
    uint32_t outDataFormat;
    /**< Output Data format: VTNF supports YUV420-NV12/21 and YV12 data formats,
     *   Input data format should be NV12 or NV21.
     *   Supported combinations:
     \ INPUT            ||  NV12  | NV21
     \ OUTPUT \         ||        |
     \  ===================================
     \  NV12            ||  YES   | NO
     \  NV21            ||  NO    | YES
     \  YV12            ||  YES   | NO
     \  YV21            ||  NO    | YES
     \   For valid values see #Fvid2_DataFormat */

    uint32_t              isAdvCfgValid;
    /**< Are the advCfg contents valid, if FALSE driver will compute advCfg
     *   internally */
    vpsissvtnfAdvConfig_t advCfg;
    /**< LDC advanced configuration - if isAdvCfgValid == FALSE, driver will
     *   compute the advCfg internally */
} vpsissvtnfConfig_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  vpsissVtnfCfg_init
 *  \brief This function should be used to initialize variable of type
 *          #vpsissvtnfConfig_t.
 *
 *  \param vtnfCfg   A pointer of type vpsissvtnfConfig_t
 *  \return          None
 */
static inline void vpsissVtnfCfg_init(vpsissvtnfConfig_t *vtnfCfg);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 *
 */
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Pointer is accessed as an array
 * Static inline function for initializing vtnf config structure
 */
static inline void vpsissVtnfCfg_init(vpsissvtnfConfig_t *vtnfCfg)
{
    uint32_t lutCnt = 0U;

    if(NULL != vtnfCfg)
    {
        vtnfCfg->outDataFormat        = FVID2_DF_YUV420SP_UV;
        vtnfCfg->isAdvCfgValid        = (uint32_t) TRUE;
        vtnfCfg->advCfg.blockWidth    = 32;   /* NEED NOT be set by USER */
        vtnfCfg->advCfg.blockHeight   = 36;   /* NEED NOT be set by USER */
        vtnfCfg->advCfg.roundBitCount = 3;
        vtnfCfg->advCfg.colorWeight1  = 0;
        vtnfCfg->advCfg.colorWeight2  = 0;

        lutCnt = 0U;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 176U;
        vtnfCfg->advCfg.lut1[lutCnt] = 160U;
        vtnfCfg->advCfg.lut1[lutCnt] = 144U;
        vtnfCfg->advCfg.lut1[lutCnt] = 128U;
        vtnfCfg->advCfg.lut1[lutCnt] = 112U;
        vtnfCfg->advCfg.lut1[lutCnt] = 96U;
        vtnfCfg->advCfg.lut1[lutCnt] = 80U;

        vtnfCfg->advCfg.lut1[lutCnt] = 72U;
        vtnfCfg->advCfg.lut1[lutCnt] = 64U;
        vtnfCfg->advCfg.lut1[lutCnt] = 56U;
        vtnfCfg->advCfg.lut1[lutCnt] = 48U;
        vtnfCfg->advCfg.lut1[lutCnt] = 32U;
        vtnfCfg->advCfg.lut1[lutCnt] = 24U;
        vtnfCfg->advCfg.lut1[lutCnt] = 16U;
        vtnfCfg->advCfg.lut1[lutCnt] = 8U;

        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;

        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;
        vtnfCfg->advCfg.lut1[lutCnt] = 0;

        lutCnt = 0U;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 176U;
        vtnfCfg->advCfg.lut2[lutCnt] = 160U;
        vtnfCfg->advCfg.lut2[lutCnt] = 144U;
        vtnfCfg->advCfg.lut2[lutCnt] = 128U;
        vtnfCfg->advCfg.lut2[lutCnt] = 112U;
        vtnfCfg->advCfg.lut2[lutCnt] = 96U;
        vtnfCfg->advCfg.lut2[lutCnt] = 80U;

        vtnfCfg->advCfg.lut2[lutCnt] = 72U;
        vtnfCfg->advCfg.lut2[lutCnt] = 64U;
        vtnfCfg->advCfg.lut2[lutCnt] = 56U;
        vtnfCfg->advCfg.lut2[lutCnt] = 48U;
        vtnfCfg->advCfg.lut2[lutCnt] = 32U;
        vtnfCfg->advCfg.lut2[lutCnt] = 24U;
        vtnfCfg->advCfg.lut2[lutCnt] = 16U;
        vtnfCfg->advCfg.lut2[lutCnt] = 8U;

        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;

        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;
        vtnfCfg->advCfg.lut2[lutCnt] = 0;

        /* Need not set by USER */
        vtnfCfg->advCfg.triggerSource = ISSHAL_VTNF_TRG_SRC_HWSEQ;
        /* Need not set by USER */
        vtnfCfg->advCfg.intrEnable = (uint32_t) TRUE;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* _VPS_CFG_VTNF_H_ */

/* @} */
