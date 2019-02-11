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
 * \file irm_resrcMgr.h
 *
 * \brief ISS Resource Manager header file
 *      This file provides functions that could be used to allocate /
 *      resources of ISS sub block.
 *
 *      Also defines the resources and allocation policies if any.
 *
 */

#ifndef IRM_RESRCMGR_H_
#define IRM_RESRCMGR_H_

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

/** \brief Maximum number of CAL blocks, for which resource management is
 *          desired */
#ifdef VPS_ISS_CALM2M_BUILD
/* In Case of TDA2Px there are total 3 instances of CAL.
   2 as part of ISS for M2M, 1 seperate instance of CAL. */
#define IRM_MAX_CAL_BLOCKS          (0x3U)
#else
#define IRM_MAX_CAL_BLOCKS          (0x2U)
#endif

/** \brief Identifier for CAL A */
#define IRM_RES_CAL_INST_A          (0x0U)

/** \brief Identifier for CAL A */
#define IRM_RES_CAL_INST_B          (0x1U)

/** \brief Value to indicate invalid instance */
#define IRM_RES_CAL_INVALID         (0xFFFFFFFFU)
/**
 *  \brief Modules maintained by resource manager
 */
typedef enum Irm_Modules
{
    IRM_MODULE_CAL_A = 0x0,
    /**< Module CAL */
    IRM_MODULE_CAL_B,
    /**< Module CAL */
    IRM_MODULE_MAX
    /**< This will ensure enum is not packed, will always be contained in int*/
} Irm_Modules_t;

/**
 *  \brief Supported options for allocation. For each option, a bit is reserved.
 *          While adding new policies ensure the value is power of 2
 */
typedef enum Irm_AllocPolicies
{
    IRM_CAL_ALLOC_POLICY_NONE = 0x0,
    /**< None */
    IRM_CAL_ALLOC_POLICY_CPORTID_0_LEAST_PREFFERED,
    /**< Cport ID 0x0, is reserved for read from memory. Should not be used
     *      for receiving stream from external interface */
    IRM_CAL_ALLOC_POLICY_WRDMA_0_LEAST_PREFFERED,
    /**< Write DMA context 0x0, is not preferred for writes. */
    IRM_ALLOC_POLICIES_MAX
    /**< This will ensure enum is not packed, will always be contained in int*/
} Irm_AllocPolicies_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief Initilization parameters
 */
typedef struct Irm_InitParams
{
    UInt32 numCalBlocks;
    /**< Define number of CAL blocks */
    Ptr    arg;
    /**< Not Used as of now */
} Irm_InitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Irm_init
 *  \brief Function to initialize ISS resource manager. It initializes
 *  all global variables and keeps it ready.
 *
 *  \param numInst      Should be 0x0. Multi-instance is not supported.
 *  \param instPrms     NULL, not used as of now.
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Irm_init(UInt32 numInst, const Irm_InitParams_t *instPrms);

/**
 *  Irm_deInit
 *  \brief Function to de-initialize VPS resource manager.
 *
 *  \return              Returns 0 on success else returns error value.
 */
Int32 Irm_deInit(void);

/**
 *  Vrm_allocResource
 *  \brief Function to allocate given resource.
 *
 *  Vrm_init function should be called before calling this function.
 *
 *  \param instId       Not Used
 *  \param resource     Module identifier, it should be IRM_MODULE_CAL_A or
 *                          IRM_MODULE_CAL_B.
 *  \param reqRes       An or values of enum vpsissCaptureSubModuleId_t.
 *  \param allocRes     Valid pointer to structure vpsissCaptureSubModuleId_t
 *  \param flags        Additional policies that should be honoured. Multiple
 *                          policies can be specified as ORed values. For valid
 *                          policies refer #Irm_AllocPolicies_t
 *
 *  \return             Returns 0 if resource is allocated to the caller or -1.
 */
Int32 Irm_allocResource(UInt32 instId, Irm_Modules_t module, UInt32 reqRes,
                        Ptr allocRes, UInt32 flags);

/**
 *  Vrm_releaseResource
 *  \brief Function to release given resource.
 *
 *  Vrm_init and allocResource API should be called before calling this API
 *
 *  \param instId       Not Used
 *  \param resource     Module identifier, it should be IRM_MODULE_CAL_A or
 *                          IRM_MODULE_CAL_B.
 *  \param relRes       Valid pointer to structure vpsissCaptureBlocks_t
 *
 *  \return             Returns 0 on success else returns error value.
 */
Int32 Irm_releaseResource(UInt32 instId, Irm_Modules_t module,
                          Ptr relRes);

#ifdef __cplusplus
}
#endif

#endif /* End of #ifndef _IRM_RESRCMGR_H_ */
