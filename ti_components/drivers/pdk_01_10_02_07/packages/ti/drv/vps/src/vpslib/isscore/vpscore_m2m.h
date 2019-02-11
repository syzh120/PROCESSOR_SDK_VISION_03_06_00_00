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
 *  \file vpscore_m2m.h
 *
 *  \brief  Provides interfaces to control / configure ISP based M2M capture.
 *
 *          Only one instance is supported as of now, This instance can
 *          be opened multiple times. The maximum open supported is defined
 *          by VPSCORE_ISS_M2M_ISP_MAX_HANDLES.
 */

#ifndef VPSCORE_ISS_ISP_M2M_H_
#define VPSCORE_ISS_ISP_M2M_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_isp.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief IOCTL base address for the common IOCTLs listed below. */
#define VCORE_ISS_M2M_COMMON_IOCTL_BASE     (0x00000000U)

/** \brief IOCTL base address for the custom IOCTLs of each cores. */
#define VCORE_ISS_M2M_CUSTOM_IOCTL_BASE     (0x00000100U)

/* Maximum number of handles supported by this m2m driver
    WDR requires 2
    YUV ReSizer 1
    In case of multi-channel surround view use case, we would require 4
        separate handles */
#define VPSCORE_ISS_M2M_ISP_MAX_HANDLES         (8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Enum for ISS M2m driver instance id
 */
typedef enum vcoreissM2mDrvInstId
{
    VPSCORE_ISS_M2M_ISP_INST_0 = 0x0,
    /**< M2M Instance for the Below ISP Path
         CAL (RD_DMA) -> VideoMux -> VideoPath -> IPIPEIF -> NSF3 ->
         ISIF -> IPIPEIF -> GLBCE -> IPIPE -> Resizer -> CNF (WR_DMA)
         Many of the modules can be enabled/bypassed in
         this path using either flags in create params or in set params
         Even WDR Pass1 and Pass2 data flow can be enabled/disabled using
         these flags
     */
    VPSCORE_ISS_M2M_MAX_INST = 0x1,
    /**< Max Instance */
    VPSCORE_ISS_M2M_INST_FORCE_INT = 0x7FFFFFFF
                                     /**< This will ensure enum is not packed, will always be contained in int */
} vcoreissM2mDrvInstId_t;

/**
 *  \brief M2M ISS Core init time parameters, passed to the #VpsCore_issIspInit
 *         core is initialized based on these parameters.
 */
typedef struct vcoreIspInitParams
{
    vcoreissM2mDrvInstId_t instId;
    /**< M2M Core Instance ID */
    Ptr                    halPlatformData;
    /**< HAL information */
    uint32_t               subModules;
    /**< Bitmask of the submodules to be enabled for this
     *   instance of the M2M driver */

    /* Event Manager Parameters */
    issemInstId_t          irqNum;
    /**< IRQ Number for the fraem completion callback */
    uint32_t               calInstId;
    /**< Cal Instance Id */
    uint32_t               calIrmId;
    /**< CAL Resource Manager Id */
    Ptr                    arg;
} vcoreIspInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to initialize ISP M2m instance, also calls hal
 *         init to initialize the hals.
 *
 *  \param numInst          number of instances to be initialized
 *  \param initParams       Init parameters, containing HAL
 *                          init parameters and m2m instance id
 *  \param arg              not used as of now
 *
 *  \return                 success: Valid #VpsCore_Inst
 *                          failure: NULL
 */
int32_t VpsCore_issM2mInit(
    uint32_t                    numInst,
    const vcoreIspInitParams_t *initPrms,
    Ptr                         arg);

/**
 *  \brief DeInitializes ISP M2M instances
 *
 *  \param arg            Not used as of now.
 *
 *  \return               success: TRUE
 *                        failure: NULL
 */
int32_t VpsCore_issM2mDeInit(Ptr arg);

/**
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_issM2mGetCoreOps(void);

/**
 *  \brief Returns the pointer to the core instance object
 *
 *  \return  A Valid pointer on success else a NULL pointer.
 */
VpsCore_Inst VpsCore_issM2mGetCoreInstObj(vcoreissM2mDrvInstId_t instId);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSCORE_ISS_ISP_M2M_H_ */
