/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 *  \file bsp_platform.c
 *
 *  \brief Interface file to the platform specific functions abstraction APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/platforms/bsp_platform.h>
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
#include <bsp_platformTda2xx.h>
#endif
#if defined (SOC_TDA3XX)
#include <bsp_platformTda3xx.h>
#endif
#if defined (OMAP5430_BUILD)
#include <bsp_platformOmap5x.h>
#endif
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
#include <bsp_platformTI814x.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Bsp_PlatformId          platformId;
    /**< Platform ID. For valid values see #Bsp_PlatformId. */
    Bsp_PlatformSocId       socId;
    /**< SOC ID. For valid values see #Bsp_PlatformSocId. */
    Bsp_PlatformCoreId      coreId;
    /**< Core ID. For valid values see #Bsp_PlatformCoreId. */
    Bsp_PlatformCpuRev      cpuRev;
    /**< CPU revision. */
    Bsp_PlatformPackageType packageType;
    /**< Package Type. */
} Bsp_platformCommonObj;

/**
 *  struct Bsp_SocIdString
 *  \brief Structure to store SOC ID and string pair.
 */
typedef struct
{
    Bsp_PlatformSocId socId;
    /**< SOC ID. */
    const Char       *socIdStr;
    /**< Pointer to SOC ID string. */
} Bsp_SocIdString;

/**
 *  struct Bsp_CoreIdString
 *  \brief Structure to store core ID and string pair.
 */
typedef struct
{
    Bsp_PlatformCoreId coreId;
    /**< Core ID. */
    const Char        *coreIdStr;
    /**< Pointer to core ID string. */
} Bsp_CoreIdString;

/**
 *  struct Bsp_PlatformIdString
 *  \brief Structure to store board ID and string pair.
 */
typedef struct
{
    Bsp_PlatformId platformId;
    /**< Platform ID. */
    const Char    *platformIdStr;
    /**< Pointer to Platform ID string. */
} Bsp_PlatformIdString;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static Bsp_platformCommonObj gPlatformCommonObj;

static Bsp_SocIdString       gSocIdStrTable[] =
{
    {BSP_PLATFORM_SOC_ID_UNKNOWN, "UNKNOWN"},
    {BSP_PLATFORM_SOC_ID_TDA2XX,  "TDA2XX" },
    {BSP_PLATFORM_SOC_ID_TDA3XX,  "TDA3XX" },
    {BSP_PLATFORM_SOC_ID_TI814X,  "TI814x" },
    {BSP_PLATFORM_SOC_ID_TI8149,  "TI8149" },
    {BSP_PLATFORM_SOC_ID_OMAP5X,  "Omap5x" },
    {BSP_PLATFORM_SOC_ID_TI811X,  "TI811x" },
    {BSP_PLATFORM_SOC_ID_DRA75X,  "DRA75x" },
    {BSP_PLATFORM_SOC_ID_TDA2EX,  "TDA2EX" },
    {BSP_PLATFORM_SOC_ID_AM574X,  "AM574X" },
    {BSP_PLATFORM_SOC_ID_AM572X,  "AM572X" },
    {BSP_PLATFORM_SOC_ID_AM571X,  "AM571X" },
    {BSP_PLATFORM_SOC_ID_TDA2PX,  "TDA2PX" }
};

static Bsp_CoreIdString      gCoreIdStrTable[] =
{
    {BSP_PLATFORM_CORE_ID_UNKNOWN, "UNKNOWN"},
    {BSP_PLATFORM_CORE_ID_A15,     "A15"    },
    {BSP_PLATFORM_CORE_ID_M4,      "M4"     },
    {BSP_PLATFORM_CORE_ID_DSP,     "DSP"    },
    {BSP_PLATFORM_CORE_ID_A8,      "A8"     },
    {BSP_PLATFORM_CORE_ID_M3,      "M3"     }
};

static Bsp_PlatformIdString  gPlatformIdStrTable[] =
{
    {BSP_PLATFORM_ID_UNKNOWN, "UNKNOWN"},
    {BSP_PLATFORM_ID_EVM,     "EVM"    },
    {BSP_PLATFORM_ID_SIM,     "SIM"    },
    {BSP_PLATFORM_ID_ZEBU,    "ZEBU"   },
    {BSP_PLATFORM_ID_VIRTIO,  "VIRTIO" }
};

/** \brief Number of entries in Platform ID string table. */
#define BSP_PLATFORM_NUM_ID_STR_ENTRIES     (sizeof (gPlatformIdStrTable) / \
                                             sizeof (Bsp_PlatformIdString))

/** \brief Number of entries in SOC ID string table. */
#define BSP_PLATFORM_SOC_NUM_ID_STR_ENTRIES     (sizeof (gSocIdStrTable) / \
                                                 sizeof (Bsp_SocIdString))

/** \brief Number of entries in Core ID string table. */
#define BSP_PLATFORM_CORE_NUM_ID_STR_ENTRIES    (sizeof (gCoreIdStrTable) / \
                                                 sizeof (Bsp_CoreIdString))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_platformInit(const Bsp_PlatformInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;
    Bsp_PlatformInitParams localInitPrms;

    BspUtils_memset(&gPlatformCommonObj, 0, sizeof (gPlatformCommonObj));

    gPlatformCommonObj.platformId = BSP_PLATFORM_ID_UNKNOWN;
    gPlatformCommonObj.socId      = BSP_PLATFORM_SOC_ID_UNKNOWN;
    gPlatformCommonObj.coreId     = BSP_PLATFORM_CORE_ID_UNKNOWN;

    /* If NULL is passed pinMux will be initialized by default */
    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        BspPlatformInitParams_init(&localInitPrms);
    }

    /* Platform is EVM */
    gPlatformCommonObj.platformId = BSP_PLATFORM_ID_EVM;

#ifdef PLATFORM_SIM
    /* Platform is Simulator */
    gPlatformCommonObj.platformId = BSP_PLATFORM_ID_SIM;
#endif

#ifdef PLATFORM_ZEBU
    /* Platform is Zebu */
    gPlatformCommonObj.platformId = BSP_PLATFORM_ID_ZEBU;
#endif

#ifdef PLATFORM_VIRTIO
    /* Platform is Virtio */
    gPlatformCommonObj.platformId = BSP_PLATFORM_ID_VIRTIO;
#endif

#ifdef __ARM_ARCH_7A__
    gPlatformCommonObj.coreId = BSP_PLATFORM_CORE_ID_A15;
#endif
#ifdef __TI_ARM_V7M4__
    gPlatformCommonObj.coreId = BSP_PLATFORM_CORE_ID_M4;
#endif
#ifdef _TMS320C6X
    gPlatformCommonObj.coreId = BSP_PLATFORM_CORE_ID_DSP;
#endif
#ifdef BUILD_A8
    gPlatformCommonObj.coreId = BSP_PLATFORM_CORE_ID_A8;
#endif
#ifdef BUILD_M3
    gPlatformCommonObj.coreId = BSP_PLATFORM_CORE_ID_M3;
#endif

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
#if defined (SOC_TDA2XX)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TDA2XX;
#endif
#if defined (SOC_TDA2PX)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TDA2PX;
#endif
#if defined (SOC_AM572x)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_AM572X;
#endif

#if defined (SOC_AM574x)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_AM574X;
#endif

#if defined (SOC_AM571x)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_AM571X;
#endif

#if defined (SOC_DRA75x)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_DRA75X;
#endif
#if defined (SOC_TDA2EX)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TDA2EX;
#endif
    retVal = Bsp_platformTda2xxInit(initPrms);

    /* Get the CPU, Package Type and board revisions */
    gPlatformCommonObj.cpuRev      = Bsp_platformTda2xxGetCpuRev();
    gPlatformCommonObj.packageType = Bsp_platformTda2xxGetPackageType();
#endif

#if defined (SOC_TDA3XX)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TDA3XX;
    retVal = Bsp_platformTda3xxInit(initPrms);

    /* Get the CPU, Package Type and board revisions */
    gPlatformCommonObj.cpuRev      = Bsp_platformTda3xxGetCpuRev();
    gPlatformCommonObj.packageType = Bsp_platformTda3xxGetPackageType();
#endif

#if defined (OMAP5430_BUILD)
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_OMAP5X;
    retVal = Bsp_platformOmap5xInit(initPrms);

    /* Get the CPU, Package Type and board revisions */
    gPlatformCommonObj.cpuRev      = Bsp_platformOmap5xGetCpuRev();
    gPlatformCommonObj.packageType = Bsp_platformOmap5xGetPackageType();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)

#ifdef TI814X_BUILD
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TI814X;
#endif
#ifdef TI8149_BUILD
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TI8149;
#endif
#ifdef TI811X_BUILD
    gPlatformCommonObj.socId = BSP_PLATFORM_SOC_ID_TI811X;
#endif
    retVal = Bsp_platformTI814xInit(initPrms);

    /* Get the CPU, Package Type and board revisions */
    gPlatformCommonObj.cpuRev      = Bsp_platformTI814xGetCpuRev();
    gPlatformCommonObj.packageType = Bsp_platformTI814xGetPackageType();
#endif

    return (retVal);
}

Int32 Bsp_platformDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxDeInit();
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxDeInit();
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    retVal = Bsp_platformTI814xDeInit();
#endif

    return (retVal);
}

Bsp_PlatformId Bsp_platformGetId(void)
{
    return (gPlatformCommonObj.platformId);
}

Bsp_PlatformSocId Bsp_platformGetSocId(void)
{
    return (gPlatformCommonObj.socId);
}

Bsp_PlatformCoreId Bsp_platformGetCoreId(void)
{
    return (gPlatformCommonObj.coreId);
}

Bsp_PlatformCpuRev Bsp_platformGetCpuRev(void)
{
    return (gPlatformCommonObj.cpuRev);
}

Bsp_PlatformPackageType Bsp_platformGetPackageType(void)
{
    return (gPlatformCommonObj.packageType);
}

Int32 Bsp_platformSimVideoInputSelect(UInt32 vipInstId,
                                      UInt32 fileId,
                                      UInt32 pixelClk)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal =
        Bsp_platformTda2xxSimVideoInputSelect(vipInstId, fileId, pixelClk);
#endif

#if defined (SOC_TDA3XX)
    retVal =
        Bsp_platformTda3xxSimVideoInputSelect(vipInstId, fileId, pixelClk);
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    retVal = Bsp_platformTI814xSimVideoInputSelect(vipInstId, fileId, pixelClk);
#endif

    return (retVal);
}

Int32 Bsp_platformSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxSetVencClkSrc(vencPrms);
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxSetVencClkSrc(vencPrms);
#endif

    return (retVal);
}

Int32 Bsp_platformSetDispcFuncClkSrc(UInt32 fClkSrc)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxSetDispcFuncClkSrc(fClkSrc);
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxSetDispcFuncClkSrc(fClkSrc);
#endif

    return (retVal);
}

Int32 Bsp_platformSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxSetPllFreq(pllFreq);
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxSetPllFreq(pllFreq);
#endif

    return (retVal);
}

Int32 Bsp_platformEnableHdmiPll(UInt32 enable)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxEnableHdmiPll(enable);
#endif

    return (retVal);
}

UInt32 Bsp_platformGetFtRev(void)
{
    UInt32 ftRev = 0;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    ftRev = Bsp_platformTda2xxGetFtRev();
#endif

    return (ftRev);
}

const Char *Bsp_platformGetString(void)
{
    Bsp_PlatformId platformId;
    const Char    *platformIdStr = NULL;
    UInt32         entryCnt;

    platformId = Bsp_platformGetId();
    if (platformId >= BSP_PLATFORM_ID_MAX)
    {
        platformId = BSP_PLATFORM_ID_UNKNOWN;
    }

    for (entryCnt = 0U; entryCnt < BSP_PLATFORM_NUM_ID_STR_ENTRIES; entryCnt++)
    {
        if (gPlatformIdStrTable[entryCnt].platformId == platformId)
        {
            platformIdStr = gPlatformIdStrTable[entryCnt].platformIdStr;
            break;
        }
    }
    GT_assert(BspPlatTrace, (platformIdStr != NULL));

    return (platformIdStr);
}

const Char *Bsp_platformGetSocString(void)
{
    Bsp_PlatformSocId socId;
    const Char       *socIdStr = NULL;
    UInt32 entryCnt;

    socId = Bsp_platformGetSocId();
    if (socId >= BSP_PLATFORM_SOC_ID_MAX)
    {
        socId = BSP_PLATFORM_SOC_ID_UNKNOWN;
    }

    for (entryCnt = 0U;
         entryCnt < BSP_PLATFORM_SOC_NUM_ID_STR_ENTRIES; entryCnt++)
    {
        if (gSocIdStrTable[entryCnt].socId == socId)
        {
            socIdStr = gSocIdStrTable[entryCnt].socIdStr;
            break;
        }
    }
    GT_assert(BspPlatTrace, (socIdStr != NULL));

    return (socIdStr);
}

const Char *Bsp_platformGetCoreString(void)
{
    Bsp_PlatformCoreId coreId;
    const Char        *coreIdStr = NULL;
    UInt32 entryCnt;

    coreId = Bsp_platformGetCoreId();
    if (coreId >= BSP_PLATFORM_CORE_ID_MAX)
    {
        coreId = BSP_PLATFORM_CORE_ID_UNKNOWN;
    }

    for (entryCnt = 0U;
         entryCnt < BSP_PLATFORM_CORE_NUM_ID_STR_ENTRIES; entryCnt++)
    {
        if (gCoreIdStrTable[entryCnt].coreId == coreId)
        {
            coreIdStr = gCoreIdStrTable[entryCnt].coreIdStr;
            break;
        }
    }
    GT_assert(BspPlatTrace, (coreIdStr != NULL));

    return (coreIdStr);
}

const Char *Bsp_platformGetCpuRevString(void)
{
    Bsp_PlatformCpuRev cpuRev;
    static Char       *gPlatformCpuNameStr[] =
    {
        "UNKNOWN",
        "ES1.0",
        "ES1.1",
        "ES2.0",
        "ES2.1",
        "ES3.0",
    };

    /* Check for out of bound access */
    GT_assert(BspPlatTrace,
              ((Int32) BSP_PLATFORM_CPU_REV_MAX ==
               (Int32) (sizeof (gPlatformCpuNameStr) / sizeof (Char *))));

    cpuRev = Bsp_platformGetCpuRev();
    if (cpuRev >= BSP_PLATFORM_CPU_REV_MAX)
    {
        cpuRev = BSP_PLATFORM_CPU_REV_UNKNOWN;
    }

    return (gPlatformCpuNameStr[cpuRev]);
}

const Char *Bsp_platformGetPackageTypeString(void)
{
    Bsp_PlatformPackageType packageType;
    static Char            *gPlatformPackageTypeStr[] =
    {
        "UNKNOWN",
        "15x15",
        "12x12",
        "17x17",
        "23x23",
    };

    /* Check for out of bound access */
    GT_assert(BspPlatTrace,
              ((Int32) BSP_PLATFORM_PACKAGE_TYPE_MAX ==
               ((Int32) (sizeof (gPlatformPackageTypeStr) / sizeof (Char *)))));

    packageType = Bsp_platformGetPackageType();
    if (packageType >= BSP_PLATFORM_PACKAGE_TYPE_MAX)
    {
        packageType = BSP_PLATFORM_PACKAGE_TYPE_UNKNOWN;
    }

    return (gPlatformPackageTypeStr[packageType]);
}

/* MISRA CAST.PTR.INT*/
void Bsp_platformPrintInfo(void)
{
    GT_1trace(BspPlatTrace, GT_INFO,
              " Platform              : [%s]\r\n", Bsp_platformGetString());
    GT_1trace(BspPlatTrace, GT_INFO,
              " SOC                   : [%s]\r\n", Bsp_platformGetSocString());
    GT_1trace(BspPlatTrace, GT_INFO,
              " SOC Revision          : [%s]\r\n", Bsp_platformGetCpuRevString());
    GT_1trace(BspPlatTrace, GT_INFO,
              " FT Revision           : [%d]\r\n", Bsp_platformGetFtRev());
    GT_1trace(BspPlatTrace, GT_INFO,
              " Package               : [%s]\r\n",
              Bsp_platformGetPackageTypeString());
    GT_1trace(BspPlatTrace, GT_INFO,
              " Core                  : [%s]\r\n", Bsp_platformGetCoreString());

    return;
}

Int32 Bsp_platformSetLcdClkPolarity(UInt32 vencId, UInt32 polarity)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxSetLCDinputPolarity(vencId, polarity);
#endif
#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxSetLCDinputPolarity(vencId, polarity);
#endif

    return (retVal);
}

Int32 Bsp_platformSetLcdSyncPolarity(UInt32 vencId,
                                     UInt32 ctrlEnable,
                                     UInt32 edgePolarity)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal =
        Bsp_platformTda2xxSetLcdSyncPolarity(vencId, ctrlEnable, edgePolarity);
#endif

#if defined (SOC_TDA3XX)
    retVal =
        Bsp_platformTda3xxSetLcdSyncPolarity(vencId, ctrlEnable, edgePolarity);
#endif

    return (retVal);
}

Int32 Bsp_platformSetVipClkInversion(UInt32 instId, UInt32 invEnable)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxSetVipClkInversion(instId, invEnable);
#endif
#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxSetVipClkInversion(instId, invEnable);
#endif

    return (retVal);
}

Int32 Bsp_platformSetPinmuxRegs(UInt32 mode_index,
                                UInt32 offset,
                                UInt32 pupd_info)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxSetPinmuxRegs(mode_index, offset, pupd_info);
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxSetPinmuxRegs(mode_index, offset, pupd_info);
#endif

    return (retVal);
}

Int32 Bsp_platformLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxLockRegion(region);
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxLockRegion(region);
#endif

    return (retVal);
}

Int32 Bsp_platformUnLockRegion(Bsp_PlatformMmrRegion region)
{
    Int32 retVal = BSP_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_TDA2PX) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_AM571x)
    retVal = Bsp_platformTda2xxUnLockRegion(region);
#endif

#if defined (SOC_TDA3XX)
    retVal = Bsp_platformTda3xxUnLockRegion(region);
#endif

    return (retVal);
}
