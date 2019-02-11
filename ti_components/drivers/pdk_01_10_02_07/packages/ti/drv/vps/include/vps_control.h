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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_CTRL_API VPS Control driver API
 *
 *  @{
 */

/**
 *  \file vps_control.h
 *
 *  \brief VPS Control Driver.
 *  VPS Control Driver Interface file.
 */

#ifndef VPS_CONTROL_H_
#define VPS_CONTROL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \name VPS control instance ID's
 *
 *  @{
 */

/** \brief VPS control driver instance 0 - only one instance is supported. */
#define VPS_CTRL_INST_0                 ((UInt32) 0U)

/* @} */

/*
 *  VPS control driver IOCTLs.
 */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_CTRL
 *  @{
 */

/**
 *  \brief Enable/disable Lazy Loading for a scaler.
 *
 *  This IOCTL should be called only when the VPE instance corresponding to
 *  vpeInstId is not opened. Otherwise this IOCTL will return error.
 *
 *  \param cmdArgs       [IN]  const Vps_ScLazyLoadingParams *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID_SOK on success, else failure
 *
 */
#define IOCTL_VPS_CTRL_SET_VPE_LAZY_LOADING (VPS_CTRL_IOCTL_BASE + 0x0000U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_ScLazyLoadingParams
 *  \brief Application interface structure for setting Lazy Loading
 *  configuration for scaler.
 */
typedef struct
{
    UInt32 vpeInstId;
    /**< VPE driver instance ID. Applicable if multiple VPE instances are
     *   present. Refer VPE header file for specific values. */
    UInt32 scalerId;
    /**< Scaler ID - Used in case multiple scalers are present in a driver.
     *   Refer VPE header file for specific values. */
    UInt32 lazyLoadingEnable;
    /**< Indicates whether lazy loading is to be enabled.
     *   If TRUE, lazy loading is to be enabled.
     *   If FALSE, lazy loading is to be disabled. */
} Vps_ScLazyLoadingParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_ScLazyLoadingParams structure init function.
 *
 *  \param prms         [IN] Pointer to #Vps_ScLazyLoadingParams structure.
 *
 */
static inline void VpsScLazyLoadingParams_init(Vps_ScLazyLoadingParams *prms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsScLazyLoadingParams_init(Vps_ScLazyLoadingParams *prms)
{
    if (NULL != prms)
    {
        prms->scalerId          = 0U;
        prms->lazyLoadingEnable = (UInt32) TRUE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_CONTROL_H_ */

/* @} */
