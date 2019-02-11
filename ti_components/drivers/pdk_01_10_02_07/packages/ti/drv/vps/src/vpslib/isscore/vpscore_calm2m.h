/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2018
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
 *  \file vpscore_calm2m.h
 *
 *  \brief Common Header file for the cal B lib
 *
 */

#ifndef VPSCORE_CALM2M_H_
#define VPSCORE_CALM2M_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief Instance identifier
 */
typedef enum vcoreCalm2mInst
{
    VPSCORE_ISS_CALM2M_INST_0           = 0,
    VPSCORE_ISS_CALM2M_INST_MAX         = 1,
    VPSCORE_ISS_CALM2M_INST_FORCE_INT   = 0x7FFFFFFF
                                        /**< This will ensure enum is not
                                         * *packed, will always be contained in
                                         *int */
} vcoreCalm2mInst_t;

/**
 *  \brief Initialization parameters.
 */
typedef struct vcoreCalm2mInitParams
{
    Ptr                         halPlatformData;
    /**< HAL information */
    uint32_t                    instId;
    /**< CALM2M CORE Instance ID # */
    issemInstId_t               irqNum;
    /**< IRQ Number for the fraem completion callback */
    issemEventGroup_t           eventGroup;
    /**< Event type */
    uint32_t                    eventNum;
    /**< Event Number */
    Ptr                         arg;
    /**< UnUsed reserved for future */
}vcoreCalm2mInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsCore_calm2mGetCoreOps
 *  \brief Returns the core ops supported
 *
 *  \param none      None
 *
 *  \return          Returns pointer to a #VpsCore_Ops instance
 *
 */
const VpsCore_Ops *VpsCore_calm2mGetCoreOps(void);

/**
 *  VpsCore_calm2mInit
 *  \brief CALM2M core init function.
 *  Initializes core objects for all instances of CALM2M.
 *  This function should be called before calling any of CALBM2M core API's.
 *  TBD: Fix Prototype
 *
 *  \param numInst      [IN] Number of CALBM2M instances to initialize
 *  \param initPrms     [IN] Array of type #vcoreCalm2mInitParams_t and size
 *                      numInst containing init parameters with instance
 *                      numInst containing init parameters
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_calm2mInit(uint32_t                       numInst,
                           const vcoreCalm2mInitParams_t *initPrms,
                           Ptr                            arg);

/**
 *  VpsCore_calm2mDeInit
 *  \brief This function closes all HAL handles & power down CALBM2M
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_calm2mDeInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSCORE_CALBM2M_H_ */
