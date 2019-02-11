/*
 *  Copyright (c) Texas Instruments Incorporated 2014-2016
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
 *  \file  stw_platform.h
 *
 *  \brief This file contains platform specific defines.
 *
 *  The SoC can be integrated into different platform types such as EVM, Zebu,
 *  simulator etc. This file defines such platform specific aspects.
 */

#ifndef STW_PLATFORM_H_
#define STW_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif /* ifdef __cplusplus */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Platform ID.
 */
typedef enum platformId
{
    PLATFORM_ID_UNKNOWN = 0x0001U,
    /**< Unknown platform. */
    PLATFORM_ID_EVM = 0x0002U,
    /**< EVMs. */
    PLATFORM_ID_SIM = 0x0004U,
    /**< Simulator. */
    PLATFORM_ID_ZEBU = 0x0008U,
    /**< Zebu presilicon platform. */
    PLATFORM_ID_VIRTIO = 0x0010U,
    /**< Virtio presilicon platform. */
    PLATFORM_ID_MAX = 0xFFFFU
                      /**< Max Platform ID. */
} platformId_t;

/**
 *  \brief SOC ID.
 */
typedef enum platformSocId
{
    PLATFORM_SOC_ID_UNKNOWN = 0x0001U,
    /**< Unknown SOC. */
    PLATFORM_SOC_ID_TDA2XX = 0x0002U,
    /**< TDA2XX SOC. */
    PLATFORM_SOC_ID_TI814X = 0x0004U,
    /**< TI814x SOC. */
    PLATFORM_SOC_ID_TI8149 = 0x0008U,
    /**< TI8149 SOC. */
    PLATFORM_SOC_ID_TI811X = 0x0010U,
    /**< TI811x SOC. */
    PLATFORM_SOC_ID_OMAP5X = 0x0020U,
    /**< OMAP5430 SOC. */
    PLATFORM_SOC_ID_TDA3XX = 0x0040U,
    /**< TDA3XX SOC. */
    PLATFORM_SOC_ID_TDA2EX = 0x0100U,
    /**< TDA2EX SOC. */
    PLATFORM_SOC_ID_TDA2PX = 0x0200U,
    /**< TDA2PX SOC. */
    PLATFORM_SOC_ID_MAX = 0xFFFFU
                          /**< Max SOC ID. */
} platformSocId_t;

/**
 *  \brief Core ID.
 */
typedef enum platformCoreId
{
    PLATFORM_CORE_ID_UNKNOWN = 0x0001U,
    /**< Unknown Core. */
    PLATFORM_CORE_ID_A15 = 0x0002U,
    /**< A15 Core. */
    PLATFORM_CORE_ID_M4 = 0x0004U,
    /**< M4 Core. */
    PLATFORM_CORE_ID_DSP = 0x0008U,
    /**< DSP Core. */
    PLATFORM_CORE_ID_A8 = 0x0010U,
    /**< A8 Core - Applicable only to TI81xx family. */
    PLATFORM_CORE_ID_M3 = 0x0020U,
    /**< M3 Core - Applicable only to TI81xx family. */
    PLATFORM_CORE_ID_MAX = 0xFFFFU
                           /**< Max CORE ID. */
} platformCoreId_t;

/**
 *  \brief CPU revision ID.
 */
typedef enum platformCpuRev
{
    PLATFORM_CPU_REV_UNKNOWN,
    /**< Unknown/unsupported CPU revision. */
    PLATFORM_CPU_REV_1_0,
    /**< CPU revision 1.0. */
    PLATFORM_CPU_REV_1_1,
    /**< CPU revision 1.1. */
    PLATFORM_CPU_REV_2_0,
    /**< CPU revision 2.0. */
    PLATFORM_CPU_REV_2_1,
    /**< CPU revision 2.1. */
    PLATFORM_CPU_REV_3_0,
    /**< CPU revision 3.0. */
    PLATFORM_CPU_REV_MAX
    /**< Max CPU revision. */
} platformCpuRev_t;

/**
 *  \brief Enum for the Memory mapped Region- MMR
 */
typedef enum
{
    PLATFORM_MMR_REG_1 = 0,
    /**<  MMR Region 1*/
    PLATFORM_MMR_REG_2,
    /**<  MMR Region 2*/
    PLATFORM_MMR_REG_3,
    /**<  MMR Region 3*/
    PLATFORM_MMR_REG_4,
    /**<  MMR Region 4*/
    PLATFORM_MMR_REG_5
    /**<  MMR Region 5*/
} platformMmrRegion_t;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Board initialization parameters.
 */
typedef struct platformInitParams
{
    uint32_t isPinMuxSettingReq;
    /**< Pinumx setting is requried or not. Sometimes pin mux setting
     *   is required to be done from host processor. */
    uint32_t isIrqXBarSettingReq;
    /**< IRQ Cross-bar setting is requried or not. If this is enabled, then
     *   following configuration will be done. If the application wish to
     *   change to a different crossbar setup for VIP, DSS, VPE etc.,this flag
     *   should be set to FALSE and application has to take care of IRQ
     *   Cross-bar setting for the IP modules used.
     *
     *      DISPC_IRQ -> IPU1_23
     *      HDMI_IRQ  -> IPU1_26
     *      VIP1_IRQ1 -> IPU1_27
     *      VIP2_IRQ1 -> IPU1_28
     *      VIP3_IRQ1 -> IPU1_29
     *      VPE1_IRQ1 -> IPU1_30
     *      I2C1_IRQ -> IPU1_41
     *      I2C2_IRQ  -> IPU1_42
     */
} platformInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief Init the underlying platform.
 *
 *  \param initPrms     [IN] Platform Initialization parameters. If
 *                           NULL is passed, pin mux setting will be done by
 *                           default.
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t PLATFORMInit(const platformInitParams_t *initPrms);

/**
 *  \brief De-init the underlying platform.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return STW_SOK      On success
 *  \return STW_EFAIL    General failure
 */
int32_t PLATFORMDeInit(void *args);

/**
 *  \brief Returns the platform ID.
 *
 *  \return Platform_ID             On success.
 *  \return PLATFORM_ID_UNKNOWN     Otherwise.
 */
platformId_t PLATFORMGetId(void);

/**
 *  \brief Function to get the name of the platform in printable string.
 *
 *  \return Platform_name   Returns a const pointer to the string. If the
 *                          platform is not known, then it returns the string as
 *                          "UNKNOWN".
 */
const char *PLATFORMGetString(void);

/**
 *  \brief Funtion to print the platform information
 *
 */
void PLATFORMPrintInfo(void);

/**
 *  \brief Returns the SOC ID.
 *
 *  \return PLATFORM_SOC_ID             On success.
 *  \return PLATFORM_SOC_ID_UNKNOWN     Otherwise.
 */
platformSocId_t PLATFORMGetSocId(void);

/**
 *  \brief Returns the Core ID.
 *
 *  \return PLATFORM_CORE_ID            On success.
 *  \return PLATFORM_CORE_ID_UNKNOWN    Otherwise.
 */
platformCoreId_t PLATFORMGetCoreId(void);

/**
 *  \brief Function to get the name of the core in printable string.
 *
 *  \return Core_name   Returns a const pointer to the string. If the
 *                      core is not known, then it returns the string as
 *                      "UNKNOWN".
 */
const char *PLATFORMGetCoreString(void);

/**
 *  \brief Returns the CPU revision.
 *
 *  \return PLATFORM_CPU_REV            On success.
 *  \return PLATFORM_CPU_REV_UNKNOWN    Otherwise.
 */
platformCpuRev_t PLATFORMGetCpuRev(void);

/**
 *  \brief Function to get the name of the CPU REV in printable string.
 *
 *  \return Cpu_rev_name    Returns a const pointer to the string. If the
 *                          cpu_rev is not known, then it returns the string as
 *                          "UNKNOWN".
 */
const char *PLATFORMGetCpuRevString(void);

/**
 *  \brief Configures IO pins needed for module.
 *
 *  \param baseAddrOffset   offset of the IO pin
 *  \param ioPinCfg         IO pin configuration settings such as Mux mode, To
 *                          enable Pull Up/Down, PullType Select, Receivemode
 *                          is enabled / not, Slew control etc.,
 *
 *  \return             STW_SOK
 */
int32_t PLATFORMSetPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg);

/**
 *  \brief This API will lock the five memory regions of CTRL_MODULE_CORE
 *         memory mapped space
 *
 *  \param region   Memory Mapped region
 *                  Refer #platformMmrRegion_t for valid set of values
 *
 *  \return             STW_SOK
 */
int32_t PLATFORMLockRegion(platformMmrRegion_t region);

/**
 *  \brief This API will unlock the five memory regions of CTRL_MODULE_CORE
 *         memory mapped space
 *
 *  \param region   Memory Mapped region
 *                  Refer #platformMmrRegion_t for valid set of values
 *
 *  \return             STW_SOK
 */
int32_t PLATFORMUnLockRegion(platformMmrRegion_t region);

uint32_t PLATFORMGetFtRev(void);
const char *PLATFORMGetSocString(void);

/**
 *  \brief Check if the SOC is Tda2xx derivatives.
 *
 *  \return TRUE if the SOC is Tda2xx derivatives else returns FALSE.
 */
static inline Bool PLATFORMIsTda2xxFamilyBuild(void);

/**
 *  \brief Check if the SOC is Tda3xx derivatives.
 *
 *  \return TRUE if the SOC is Tda3xx derivatives else returns FALSE.
 */
static inline Bool PLATFORMIsTda3xxFamilyBuild(void);

/**
 *  \brief Check if the SOC is TI814x derivatives.
 *
 *  \return TRUE if the SOC is TI814x derivatives else returns FALSE.
 */
static inline Bool PLATFORMIsTI814xFamilyBuild(void);

/**
 *  \brief Check if the SOC is Omap5x derivatives.
 *
 *  \return TRUE if the SOC is Omap5x derivatives else returns FALSE.
 */
static inline Bool PLATFORMIsOmap5xFamilyBuild(void);

/**
 *  \brief Initializes Pin mux and Cross bar setting Required or not.
 *
 *  \return None.
 */

static inline void PLATFORMInitParams_init(platformInitParams_t *initPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline Bool PLATFORMIsTda2xxFamilyBuild(void)
{
    platformSocId_t socId;
    Bool retStatus = FALSE;

    socId = PLATFORMGetSocId();
    if ((PLATFORM_SOC_ID_TDA2XX == socId) ||
        (PLATFORM_SOC_ID_TDA2PX == socId) ||
        (PLATFORM_SOC_ID_TDA2EX == socId))
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline Bool PLATFORMIsTda3xxFamilyBuild(void)
{
    platformSocId_t socId;
    Bool retStatus = FALSE;

    socId = PLATFORMGetSocId();
    if (PLATFORM_SOC_ID_TDA3XX == socId)
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline Bool PLATFORMIsOmap5xFamilyBuild(void)
{
    platformSocId_t socId;
    Bool retStatus = FALSE;

    socId = PLATFORMGetSocId();
    if (PLATFORM_SOC_ID_OMAP5X == socId)
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline Bool PLATFORMIsTI814xFamilyBuild(void)
{
    platformSocId_t socId;
    Bool retStatus = FALSE;

    socId = PLATFORMGetSocId();
    if ((PLATFORM_SOC_ID_TI814X == socId) ||
        (PLATFORM_SOC_ID_TI8149 == socId) ||
        (PLATFORM_SOC_ID_TI811X == socId))
    {
        retStatus = (Bool) TRUE;
    }

    return (retStatus);
}

static inline void PLATFORMInitParams_init(platformInitParams_t *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isPinMuxSettingReq  = (uint32_t) TRUE;
        initPrms->isIrqXBarSettingReq = (uint32_t) TRUE;
    }
    return;
}

#ifdef __cplusplus
}
#endif /* ifdef __cplusplus */

#endif /* #ifndef STW_PLATFORM_H_ */
