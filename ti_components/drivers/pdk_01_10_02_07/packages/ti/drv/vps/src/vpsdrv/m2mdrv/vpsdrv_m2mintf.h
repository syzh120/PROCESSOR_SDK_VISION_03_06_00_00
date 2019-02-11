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
 *  \file vps_m2mIntf.h
 *
 *  \brief This file implements the memory to memory driver.
 *
 */

#ifndef VPS_DRV_M2M_INTF_H_
#define VPS_DRV_M2M_INTF_H_

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

/** \brief Maxium number of cores supported */
#define VPSMDRV_INTF_MAX_CORE           (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsMdrv_M2mInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32             drvInstId;
    /**< Driver instance ID. */
    UInt32             isMultiChSupported;
    /**< Flag to indicate if this instance supports multiple channels or not */
    UInt32             numCores;
    /**< Number of valid entries in coreInstId and coreOps */
    VpsCore_Inst       coreInstId[VPSMDRV_INTF_MAX_CORE];
    /**< Core instance number/ID. */
    const VpsCore_Ops *coreOps[VPSMDRV_INTF_MAX_CORE];
    /**< VPE, VWB core function pointers. */
} VpsMdrv_M2mIntfInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsMdrv_intfInit
 *  \brief VPE M2M driver init function.
 *  Initializes driver objects, allocates memory etc.
 *  This function should be called before calling any of FVID2 APIs for this
 *  driver.
 *
 *  \param numInst      Number of instance objects to be initialized.
 *  \param initPrms     Pointer to the init parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInst.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_intfInit(UInt32                           numInst,
                       const VpsMdrv_M2mIntfInitParams *initPrms);

/**
 *  VpsMdrv_deInit
 *  \brief VPE driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_intfDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* VPS_DRV_M2M_INTF_H_ */
