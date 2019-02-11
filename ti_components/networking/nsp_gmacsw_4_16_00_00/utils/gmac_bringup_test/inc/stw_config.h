/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *
*/


/**
 *  \file stw_config.h
 *
 *  \brief Starterware header file containing globally used configuration.
 *
 */

#ifndef STW_CONFIG_H_
#define STW_CONFIG_H_

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

/* ========================================================================== */
/* The define below could be used to enable logging for each modules          */
/* Set the value to                                                           */
/* (GT_DEBUG | GT_TraceState_Enable) - Enables all log messages               */
/* (GT_INFO | GT_TraceState_Enable) - Enables log messages except debug level */
/* (GT_ERR | GT_TraceState_Enable) - Enables only error log messages          */
/* 0 - Disables all log messages                                              */
/* ========================================================================== */

/** \brief Log enable for STW Utils. */
#define StwUtilsTrace                   (GT_DEFAULT_MASK)

/** \brief Log enable for VPE core. */
#define VpsVpeCoreTrace                 (GT_DEFAULT_MASK)
/** \brief Log enable for VPE writeback path core. */
#define VpsVwbCoreTrace                 (GT_DEFAULT_MASK)
/** \brief Log enable for VIP core. */
#define VpsVipCoreTrace                 (GT_DEFAULT_MASK)
/** \brief Log enable for VIP core. */
#define VpsIssCoreTrace                 (GT_DEFAULT_MASK)
/** \brief Log enable for CAL core. */
#define VpsIssCalCoreTrace              (GT_DEFAULT_MASK)
/** \brief Log enable for DSS core. */
#define VpsDssCoreTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for DCTRL core. */
#define VpsDctrlCoreTrace                 (GT_DEFAULT_MASK)

/** \brief Log enable for VPS event manager. */
#define VpsVemTrace                     (GT_DEFAULT_MASK)
/** \brief Log enable for VPS resource manager. */
#define VpsVrmTrace                     (GT_DEFAULT_MASK)

/** \brief Log enable for VPS common modules. */
#define VpsTrace                        (GT_INFO | GT_TraceState_Enable)
/** \brief Log enable for all HAL modules. */
#define VpsHalTrace                     (GT_INFO | GT_TraceState_Enable)
/** \brief Log enable for VPDMA HAL debug modules. */
#define VpsHalVpdmaDebugTrace           (GT_DEBUG | GT_TraceState_Enable)

/** \brief Define this macro to load custome VPDMA firmware. */
/* #define VPS_CFG_ENABLE_CUSTOM_FW_LOAD */

/** \brief Define this macro to enable descriptor placement in OCMC. */
/* #define VPS_CFG_DESC_IN_OCMC */

/* ========================================================================== *
 *  VPDMA priority is 3bit field having values from 0 to 7.
 *  VPDMA priority is passed to DMM/DDR as master priority.
 *  However bit1 in VPDMA priority is not used by DMM/DDR.
 *  Hence effective priorities map as shown below
 *
 *  VPDMA Desc Prioirty Value       Actual DMM/DDR Master priority
 *  0   (000b)                      0   (00b)
 *  1   (001b)                      1   (01b)
 *  2   (010b)                      0   (00b)
 *  3   (011b)                      1   (01b)
 *  4   (100b)                      2   (10b)
 *  5   (101b)                      3   (11b)
 *  6   (110b)                      2   (10b)
 *  7   (111b)                      3   (11b)
 *
 *  Thus for example, VPDMA Desc priority 0 and 2 map to priority 0 at DMM/DDR
 *
 *  Hence in the below priroties for different drivers we will only use the
 *  below priority values
 *
 *  VPSHAL_VPDMA_DATADESCPRIO_0 (effective DDR/DMM priority 0)
 *  VPSHAL_VPDMA_DATADESCPRIO_1 (effective DDR/DMM priority 1)
 *  VPSHAL_VPDMA_DATADESCPRIO_4 (effective DDR/DMM priority 2)
 *  VPSHAL_VPDMA_DATADESCPRIO_7 (effective DDR/DMM priority 3)
 *
 *  Also
 *  - Capture should be the HIGHEST priority ALWAYS to avoid overflow conditions
 *  - Display should be the 2nd-HIGHEST priority ALWAYS to avoid underflow
 *    conditions
 *  - M2M driver should be of lower priority
 *  - NSF is kept higher than other M2M drivers for performance reasons
 * ========================================================================== */

/** \brief VPDMA priority for different capture, display, M2M clients */

#define VPS_CFG_CAPT_VPDMA_PRIORITY     (VPSHAL_VPDMA_DATADESCPRIO_0)
#define VPS_CFG_DISP_VPDMA_PRIORITY     (VPSHAL_VPDMA_DATADESCPRIO_1)
#define VPS_CFG_M2M_VPDMA_PRIORITY_RD   (VPSHAL_VPDMA_DATADESCPRIO_7)
#define VPS_CFG_M2M_VPDMA_PRIORITY_WR   (VPS_CFG_M2M_VPDMA_PRIORITY_RD)

/**
 *  \brief Maximum number of windows per row supported in multiple window mode.
 *  This is used to allocate memory and array size statically.
 *  Note: This macro could be changed as and when the requirement changes.
 */
#define VPS_CFG_MAX_MULTI_WIN_COL       (8U)

/**
 *  \brief Maximum number of rows per frame supported in multiple window mode.
 *  This is used to allocate memory and array size statically.
 *  Note: This macro could be changed as and when the requirement changes.
 */
#define VPS_CFG_MAX_MULTI_WIN_ROW       (8U)

/**
 *  \brief Maximum number of frames supported in multiple window mode.
 *  This is used to allocate memory and array size statically.
 *  Note: This macro could be changed as and when the requirement changes.
 */
#define VPS_CFG_MAX_MULTI_WIN           (VPS_CFG_MAX_MULTI_WIN_COL * \
                                         VPS_CFG_MAX_MULTI_WIN_ROW)

/**
 *  \brief Maximum number of in data descriptors.
 *  First row multi window descriptor * 2U for Y/C separate clients +
 *  considering worst case client - 9 IN channels of DEI HQ path without
 *  SC writback path. (Current field covered in multi window descriptor,
 *  3x2 previous fields, 2 MV in, 1 MVSTM in).
 *  Note: This macro can be changed as and when requirement changes.
 */
#define VPS_CFG_MAX_IN_DESC             (VPS_CFG_MAX_MULTI_WIN_COL * 2U + 9U)

/**
 *  \brief Maximum number of out data descriptors.
 *  Considering worst case client - 6 OUT channels of DEI HQ path without
 *  SC writback path. (4 Current field out, 1 MV out, 1 MVSTM out).
 *  Note: This macro can be changed as and when requirement changes.
 */
#define VPS_CFG_MAX_OUT_DESC            (6U)

/**
 *  \brief Maximum number of multi window data descriptor to allocate per
 *  client to program from 2nd row descriptors.
 *  Max multi window descriptor (- first row) * 2U for Y/C separate clients
 *  1 for "Zero transfer descriptor" * 2U for Y/C separate clients
 *  1 for a SOCH on last window channel (either actual or free channel) and
 *  abort descriptor on actual channel * 2U for Y/C separate clients
 *  Abort descriptor on free channel of last window in all rows * 2U for Y/C
 *  separate clients (/2U since abort desc is 1/2 the size of data desc).
 *  Note: This macro can be changed as and when requirement changes.
 */
#define VPS_CFG_MAX_MULTI_WIN_DESC    ((VPS_CFG_MAX_MULTI_WIN_COL *            \
                                        (VPS_CFG_MAX_MULTI_WIN_ROW - 1U) * 2U) \
                                       + (1U * 2U)                             \
                                       + (1U * 2U)                             \
                                       + ((VPS_CFG_MAX_MULTI_WIN_ROW * 2U) / 2U))

/**
 *  \brief Define this macro to use Sync on Channel instead of Sync on Client
 *  in all M2M drivers while chaining different channels in a single VPDMA
 *  submission. Uncomment this to use Sync on Client.
 */
#define VPS_CFG_USE_SYNC_ON_CH

/** \brief Blender/Comp BackGround Color in RGB Format is 30-bit packed. */
#define VPS_CFG_COMP_BKCOLOR            (0x04010040U)
/** \brief VCOMP BackGround Color in YUV. Format is 0x0CRCBYY (each 10 bits). */
#define VPS_CFG_VCOMP_BKCOLOR           (0x20080000U)
/** \brief VPDMA BackGround Color in ARGB. Format is 0xAARRGGBB. */
#define VPS_CFG_VPDMA_ARGB_BKCOLOR      (0x00000000U)
/** \brief VPDMA BackGround Color in YUV. Format is 0x00YYCBCR. */
#define VPS_CFG_VPDMA_YUV_BKCOLOR       (0x00008080U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_CONFIG_H_ */
