/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2015
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
 *  \file bsp_config.h
 *
 *  \brief BSP header file containing globally used configuration.
 *
 */

#ifndef BSP_CONFIG_H_
#define BSP_CONFIG_H_

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
 *  \brief BSP package version string.
 *  Version is of the form mm_nn_xx_yy where,
 *      mm - Product version. This increments for any new BSP versions or
 *           platform.
 *      nn - Major number - Increments if any backward compatibility is broken
 *           or major change within a product version.
 *      xx - Minor number - Increments for any minor change or any additions
 *           done without breaking backward compatibility.
 *      yy - Build number - Increments for every release.
 */
#define BSP_VERSION_STRING              "PDK_01_10_02_xx"

/** \brief BSP package version number. */
#define BSP_VERSION_NUMBER              ((UInt32) 0x01100200U)

/* ========================================================================== */
/* The define below could be used to enable logging for each modules          */
/* Set the value to                                                           */
/* (GT_DEBUG | GT_TraceState_Enable) - Enables all log messages               */
/* (GT_INFO | GT_TraceState_Enable) - Enables log messages except debug level */
/* (GT_ERR | GT_TraceState_Enable) - Enables only error log messages          */
/* 0 - Disables all log messages                                              */
/* ========================================================================== */

/** \brief Log enable for BSP Utils. */
#define BspUtilsTrace                   (GT_DEFAULT_MASK)

/** \brief Log enable for platform module. */
#define BspPlatTrace                    (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for board module. */
#define BspBoardTrace                   (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for I2C driver. */
#define BspI2cTrace                     (GT_DEFAULT_MASK)

/** \brief Log enable for external decoder/encoder drivers. */
#define BspDeviceTrace                  (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for VPS driver common modules. */
#define VpsDrvTrace                     (GT_INFO | GT_TraceState_Enable)

/** \brief Log enable for capture driver. */
#define VpsDrvCaptTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for display driver. */
#define VpsDrvDispTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for display controller driver. */
#define VpsDrvDctrlTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for memory to memory driver. */
#define VpsMDrvTrace                    (GT_DEFAULT_MASK)

/** \brief Log enable for DSS memory to memory driver. */
#define VpsMDrvDssTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for M2M list manager. */
#define VpsMlmTrace                     (GT_DEFAULT_MASK)
/** \brief Log enable for M2M VPE driver. */
#define VpsMdrvVpeTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for M2M ISS driver. */
#define VpsMdrvIssTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for control driver. */
#define VpsDrvCtrlTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for example application. */
#define BspAppTrace                     (GT_INFO | GT_TraceState_Enable)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Get the version string for the BSP package.
 *
 *  This is the version number for all the drivers on BSP. This
 *  function can be called prior to #Bsp_commonInit() to get the version number.
 *
 *  \return pointer to BSP version string.
 */
const Char *Bsp_getVersionString(void);

/**
 *  \brief Same as #Bsp_getVersionString() except it returns the version in
 *  UInt32 form.
 *
 *  Example, v1.0.1.17 will be 0x01000117
 *
 *  \return BSP version number.
 */
UInt32 Bsp_getVersionNumber(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_CONFIG_H_ */
