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
 *  \file stw_platform.c
 *
 *  \brief Interface file to the platform specific functions abstraction APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/stw_platform.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#include <stw_platformTda2xx.h>
#endif
#if defined (SOC_TDA3XX)
#include <stw_platformTda3xx.h>
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct platformCommonObj
{
    platformId_t     platfrmId;
    /**< Platform ID. For valid values see #platformId_t. */
    platformSocId_t  socId;
    /**< SOC ID. For valid values see #platformSocId_t. */
    platformCoreId_t coreId;
    /**< Core ID. For valid values see #platformCoreId_t. */
    platformCpuRev_t cpuRev;
    /**< CPU revision. */
} platformCommonObj_t;

/**
 *  struct platformSocIdString_t
 *  \brief Structure to store SOC ID and string pair.
 */
typedef struct platformSocIdString
{
    platformSocId_t socId;
    /**< SOC ID. */
    const char     *socIdStr;
    /**< Pointer to SOC ID string. */
} platformSocIdString_t;

/**
 *  struct platformCoreIdString_t
 *  \brief Structure to store core ID and string pair.
 */
typedef struct platformCoreIdString
{
    platformCoreId_t coreId;
    /**< Core ID. */
    const char      *coreIdStr;
    /**< Pointer to core ID string. */
} platformCoreIdString_t;

/**
 *  struct platformIdString_t
 *  \brief Structure to store board ID and string pair.
 */
typedef struct platformIdString
{
    platformId_t platfrmId;
    /**< Platform ID. */
    const char  *platformIdStr;
    /**< Pointer to Platform ID string. */
} platformIdString_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static platformCommonObj_t          gPlatformCommonObj;

static const platformSocIdString_t  gSocIdStrTable[] =
{
    {PLATFORM_SOC_ID_UNKNOWN, "UNKNOWN"},
    {PLATFORM_SOC_ID_TDA2XX,  "TDA2XX" },
    {PLATFORM_SOC_ID_TDA3XX,  "TDA3XX" },
    {PLATFORM_SOC_ID_TI814X,  "TI814x" },
    {PLATFORM_SOC_ID_TI8149,  "TI8149" },
    {PLATFORM_SOC_ID_OMAP5X,  "Omap5x" },
    {PLATFORM_SOC_ID_TI811X,  "TI811x" },
    {PLATFORM_SOC_ID_TDA2EX,  "TDA2EX" },
    {PLATFORM_SOC_ID_TDA2PX,  "TDA2PX" }
};

static const platformCoreIdString_t gCoreIdStrTable[] =
{
    {PLATFORM_CORE_ID_UNKNOWN, "UNKNOWN"},
    {PLATFORM_CORE_ID_A15,     "A15"    },
    {PLATFORM_CORE_ID_M4,      "M4"     },
    {PLATFORM_CORE_ID_DSP,     "DSP"    },
    {PLATFORM_CORE_ID_A8,      "A8"     },
    {PLATFORM_CORE_ID_M3,      "M3"     }
};

static const platformIdString_t     gPlatformIdStrTable[] =
{
    {PLATFORM_ID_UNKNOWN, "UNKNOWN"},
    {PLATFORM_ID_EVM,     "EVM"    },
    {PLATFORM_ID_SIM,     "SIM"    },
    {PLATFORM_ID_ZEBU,    "ZEBU"   },
    {PLATFORM_ID_VIRTIO,  "VIRTIO" }
};

/** \brief Number of entries in Platform ID string table. */
#define PLATFORM_NUM_ID_STR_ENTRIES     (sizeof (gPlatformIdStrTable) / \
                                         sizeof (platformIdString_t))

/** \brief Number of entries in SOC ID string table. */
#define PLATFORM_SOC_NUM_ID_STR_ENTRIES     (sizeof (gSocIdStrTable) / \
                                             sizeof (platformSocIdString_t))

/** \brief Number of entries in Core ID string table. */
#define PLATFORM_CORE_NUM_ID_STR_ENTRIES    (sizeof (gCoreIdStrTable) / \
                                             sizeof (platformCoreIdString_t))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t PLATFORMInit(const platformInitParams_t *initPrms)
{
    int32_t retVal = STW_SOK;
    platformInitParams_t localInitPrms;

    memset(&gPlatformCommonObj, 0, sizeof (gPlatformCommonObj));

    gPlatformCommonObj.platfrmId = PLATFORM_ID_UNKNOWN;
    gPlatformCommonObj.socId     = PLATFORM_SOC_ID_UNKNOWN;
    gPlatformCommonObj.coreId    = PLATFORM_CORE_ID_UNKNOWN;

    /* If NULL is passed pinMux will be initialized by default */
    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        PLATFORMInitParams_init(&localInitPrms);
    }

    /* Platform is EVM */
    gPlatformCommonObj.platfrmId = PLATFORM_ID_EVM;
#ifdef PLATFORM_SIM
    /* Platform is Simulator */
    gPlatformCommonObj.platfrmId = PLATFORM_ID_SIM;
#endif
#ifdef PLATFORM_ZEBU
    /* Platform is Zebu */
    gPlatformCommonObj.platfrmId = PLATFORM_ID_ZEBU;
#endif
#ifdef PLATFORM_VIRTIO
    /* Platform is Virtio */
    gPlatformCommonObj.platfrmId = PLATFORM_ID_VIRTIO;
#endif

#if defined (__ARM_ARCH_7A__)
    gPlatformCommonObj.coreId = PLATFORM_CORE_ID_A15;
#endif
#if defined (__TI_ARM_V7M4__)
    gPlatformCommonObj.coreId = PLATFORM_CORE_ID_M4;
#endif
#if defined (_TMS320C6X)
    gPlatformCommonObj.coreId = PLATFORM_CORE_ID_DSP;
#endif
#if defined (BUILD_A8)
    gPlatformCommonObj.coreId = PLATFORM_CORE_ID_A8;
#endif
#if defined (BUILD_M3)
    gPlatformCommonObj.coreId = PLATFORM_CORE_ID_M3;
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#if defined (SOC_TDA2XX)
    gPlatformCommonObj.socId = PLATFORM_SOC_ID_TDA2XX;
#endif
#if defined (SOC_TDA2PX)
    gPlatformCommonObj.socId = PLATFORM_SOC_ID_TDA2PX;
#endif
#if defined (SOC_TDA2EX)
    gPlatformCommonObj.socId = PLATFORM_SOC_ID_TDA2EX;
#endif

    retVal = PLATFORMTda2xxInit(initPrms);

    /* Get the CPU and board revisions */
    gPlatformCommonObj.cpuRev = PLATFORMTda2xxGetCpuRev();
#endif

#if defined (SOC_TDA3XX)
    gPlatformCommonObj.socId = PLATFORM_SOC_ID_TDA3XX;

    retVal = PLATFORMTda3xxInit(initPrms);

    /* Get the CPU and board revisions */
    gPlatformCommonObj.cpuRev = PLATFORMTda3xxGetCpuRev();
#endif

    return (retVal);
}

int32_t PLATFORMDeInit(void *args)
{
    int32_t retVal = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    retVal = PLATFORMTda2xxDeInit();
#endif

#if defined (SOC_TDA3XX)
    retVal = PLATFORMTda3xxDeInit();
#endif

    return (retVal);
}

platformId_t PLATFORMGetId(void)
{
    return (gPlatformCommonObj.platfrmId);
}

platformSocId_t PLATFORMGetSocId(void)
{
    return (gPlatformCommonObj.socId);
}

platformCoreId_t PLATFORMGetCoreId(void)
{
    return (gPlatformCommonObj.coreId);
}

platformCpuRev_t PLATFORMGetCpuRev(void)
{
    return (gPlatformCommonObj.cpuRev);
}

uint32_t PLATFORMGetFtRev(void)
{
    uint32_t ftRev = 0;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    ftRev = PLATFORMTda2xxGetFtRev();
#endif

    return (ftRev);
}

const char *PLATFORMGetString(void)
{
    platformId_t platfrmId;
    const char  *platformIdStr = NULL;
    uint32_t     entryCnt;

    platfrmId = PLATFORMGetId();
    if (platfrmId >= PLATFORM_ID_MAX)
    {
        platfrmId = PLATFORM_ID_UNKNOWN;
    }

    for (entryCnt = 0U; entryCnt < PLATFORM_NUM_ID_STR_ENTRIES; entryCnt++)
    {
        if (gPlatformIdStrTable[entryCnt].platfrmId == platfrmId)
        {
            platformIdStr = gPlatformIdStrTable[entryCnt].platformIdStr;
            break;
        }
    }

    return (platformIdStr);
}

const char *PLATFORMGetSocString(void)
{
    platformSocId_t socId;
    const char     *socIdStr = NULL;
    uint32_t        entryCnt;

    socId = PLATFORMGetSocId();
    if (socId >= PLATFORM_SOC_ID_MAX)
    {
        socId = PLATFORM_SOC_ID_UNKNOWN;
    }

    for (entryCnt = 0U;
         entryCnt < PLATFORM_SOC_NUM_ID_STR_ENTRIES; entryCnt++)
    {
        if (gSocIdStrTable[entryCnt].socId == socId)
        {
            socIdStr = gSocIdStrTable[entryCnt].socIdStr;
            break;
        }
    }

    return (socIdStr);
}

const char *PLATFORMGetCoreString(void)
{
    platformCoreId_t coreId;
    const char      *coreIdStr = NULL;
    uint32_t         entryCnt;

    coreId = PLATFORMGetCoreId();
    if (coreId >= PLATFORM_CORE_ID_MAX)
    {
        coreId = PLATFORM_CORE_ID_UNKNOWN;
    }

    for (entryCnt = 0U;
         entryCnt < PLATFORM_CORE_NUM_ID_STR_ENTRIES; entryCnt++)
    {
        if (gCoreIdStrTable[entryCnt].coreId == coreId)
        {
            coreIdStr = gCoreIdStrTable[entryCnt].coreIdStr;
            break;
        }
    }

    return (coreIdStr);
}

const char *PLATFORMGetCpuRevString(void)
{
    platformCpuRev_t   cpuRev = PLATFORM_CPU_REV_UNKNOWN;
    const char        *retPtr = NULL;
    static const char *gPlatformCpuNameStr[] =
    {
        "UNKNOWN",
        "ES1.0",
        "ES1.1",
        "ES2.0",
        "ES2.1",
        "ES3.0",
    };

    /* Check for out of bound access */
    if ((size_t) PLATFORM_CPU_REV_MAX ==
        (sizeof (gPlatformCpuNameStr) / sizeof (char *)))
    {
        cpuRev = PLATFORMGetCpuRev();
        if (cpuRev >= PLATFORM_CPU_REV_MAX)
        {
            cpuRev = PLATFORM_CPU_REV_UNKNOWN;
        }
        retPtr = gPlatformCpuNameStr[cpuRev];
    }

    return (retPtr);
}

void PLATFORMPrintInfo(void)
{
    const char *platformIdStr  = NULL;
    const char *socIdStr       = NULL;
    const char *platformRevStr = NULL;
    const char *coreIdStr      = NULL;

    platformIdStr = PLATFORMGetString();
    if (platformIdStr != NULL)
    {
        UARTprintf(" \r\nPlatform                     : ");
        UARTprintf(platformIdStr);
    }
    else
    {
        UARTprintf("\r\n NULL Pointer Detected platformIdStr ");
    }

    socIdStr = PLATFORMGetSocString();
    if (socIdStr != NULL)
    {
        UARTprintf(" \r\nSOC                          : ");
        UARTprintf(socIdStr);
    }
    else
    {
        UARTprintf("\r\n NULL Pointer Detected socIdStr ");
    }

    platformRevStr = PLATFORMGetCpuRevString();
    if (platformRevStr != NULL)
    {
        UARTprintf(" \r\nSOC Revision                 : ");
        UARTprintf(platformRevStr);
    }
    else
    {
        UARTprintf("\r\n platformRevStr out of bound error ");
    }

    UARTprintf(" \r\nFT Revision                  : ");
    UARTPutNum((int32_t) PLATFORMGetFtRev());

    coreIdStr = PLATFORMGetCoreString();
    if (coreIdStr != NULL)
    {
        UARTprintf(" \r\nCore                         : ");
        UARTprintf(coreIdStr);
    }
    else
    {
        UARTprintf("\r\n NULL Pointer Detected coreIdStr ");
    }

    return;
}

int32_t PLATFORMSetPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg)
{
    int32_t retVal = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    retVal = PLATFORMTda2xxSetPinmuxRegs(baseAddrOffset, ioPinCfg);
#endif

#if defined (SOC_TDA3XX)
    retVal = PLATFORMTda3xxSetPinmuxRegs(baseAddrOffset, ioPinCfg);
#endif

    return (retVal);
}

int32_t PLATFORMLockRegion(platformMmrRegion_t region)
{
    int32_t retVal = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    retVal = PLATFORMTda2xxLockRegion(region);
#endif

#if defined (SOC_TDA3XX)
    retVal = PLATFORMTda3xxLockRegion(region);
#endif

    return (retVal);
}

int32_t PLATFORMUnLockRegion(platformMmrRegion_t region)
{
    int32_t retVal = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    retVal = PLATFORMTda2xxUnLockRegion(region);
#endif

#if defined (SOC_TDA3XX)
    retVal = PLATFORMTda3xxUnLockRegion(region);
#endif

    return (retVal);
}

