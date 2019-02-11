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
 *  \file vpsdrv_m2mVpe.h
 *
 *  \brief This file implements the memory to memory driver for the
 *  VPE with outputs through DEI Write back paths.
 *
 */

#ifndef VPSDRV_M2MVPE_H_
#define VPSDRV_M2MVPE_H_

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

/** \brief Core index for VPE core. */
#define VPSMDRV_VPE_VPE_CORE_IDX        (0U)
/** \brief Core index for VPE writeback core. */
#define VPSMDRV_VPE_VWB_CORE_IDX        (1U)
/* Note: If a new core is to be added into this that has a scaler in it, refer
 * to vps_m2mVpe.h:
 * VPS_M2M_VPE_SCALER_ID_SC0.
 * The new scalerId corresponding to this core needs to be added at the end
 * and the new core with that scaler ID must be added at the end here. This
 * same ordering is assumed within the code.
 */
/** \brief Maximum number of core required by driver. */
#define VPSMDRV_VPE_MAX_CORE            (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsMdrv_VpeInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32              drvInstId;
    /**< Driver instance ID. */
    UInt32              coreInstId[VPSMDRV_VPE_MAX_CORE];
    /**< VPE, VWB core instance number/ID. */
    const Vcore_M2mOps *coreOps[VPSMDRV_VPE_MAX_CORE];
    /**< VPE, VWB core function pointers. */
} VpsMdrv_VpeInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsMdrv_vpeInit
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
Int32 VpsMdrv_vpeInit(UInt32                       numInst,
                      const VpsMdrv_VpeInitParams *initPrms);

/**
 *  VpsMdrv_vpeDeInit
 *  \brief VPE driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_vpeDeInit(void);

/**
 *  VpsMdrv_vpeSetLazyLoadParams
 *  \brief VPE driver set lazy load parameter for a given instance and scaler.
 *
 *  \param lazyPrms     Pointer to lazy loading parameter. This can't be NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_vpeSetLazyLoadParams(const Vps_ScLazyLoadingParams *lazyPrms);

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MVPE_H_ */
