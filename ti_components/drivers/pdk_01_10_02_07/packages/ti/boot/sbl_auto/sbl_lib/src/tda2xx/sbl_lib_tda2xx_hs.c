/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     sbl_lib_tda2xx_hs.c
 *
 *  \brief    This file contains the SBL Library layer for HS devices of
 *            TDA2xx SOC family.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <sbl_lib_tda2xx_priv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Flags supported by ROM/PPA APIs for controlling pre-emption of ROM/PPA
 * service routines
 */
#define PPA_CRITICAL                    (0x4U)
#define PPA_ALLOW_IRQ_FIQ               (0x3U)
#define PPA_ALLOW_IRQ                   (0x2U)
#define PPA_ALLOW_FIQ                   (0x1U)
#define PPA_BLOCK_IRQ_FIQ               (0x0U)

/* Length of signatures used for authentication TDA2xx HS devices */
#define AUTH_SIGNATURE_LENGTH           (uint32_t) (0x118U)

/* TDA2XX ROM Services */
/* Index for API used for authenticating custom binary images */
#define API_HAL_KM_VERIFYCERTIFICATESIGNATURE_INDEX (0x0000000EU)

/* TDA2XX PPA Services */
#define PPA_HAL_SERVICES_START_INDEX    (0x200U)

/* Index for API used for opening up firewalls required for FFI.
 * Reference PPA service implementation opens up only following firewalls:
 *  EMIF (EMIF accesses from L3)
 *  MA_MPU (EMIF accesses from A15)
 *  OCMC2 (ALl OCMC2 accesses)
 *  OCMC3 (ALl OCMC3 accesses)
 */
#define PPA_SERV_HAL_OPEN_FFI_FW       (uint32_t) (PPA_HAL_SERVICES_START_INDEX \
                                                   + 28U)

/* Index for API used for configuring OCMC1 firewall.
 * In case of TDA2x HS devices, 1st 4kB of OCMC1 should always be blocked as
 * to account for a silicon erratum. This PPA service enforces this restriction
 * by blocking access to region 0/1 of firewall and ignoring requests for
 * enabling access to first 4kB.
 *
 * However, to allow use of rest of OCMC1 with FFI. This API can be used.
 */
#define PPA_SERV_HAL_SETUP_OCMC1_FW    (uint32_t) (PPA_HAL_SERVICES_START_INDEX \
                                                   + 29U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLLibHSOpenL3Firewalls(void)
{
    uint32_t args[16U];
    uint32_t secTaskId = 0xFFU; /* 0xFF for new service */

    if ((uint32_t) TRUE == SblLibIsExecutingOnA15HS())
    {
        /* Number of arguments is zero for PPA_SERV_HAL_OPEN_FFI_FW */
        args[0] = 0U;
        SBLLibHSSecureEntryAsm(
            PPA_SERV_HAL_OPEN_FFI_FW, PPA_BLOCK_IRQ_FIQ, &args[0], &secTaskId);
    }
}

int32_t SBLLibHSConfigureOcmc1Firewall(uint32_t regionId,
                                       uint32_t startAddress,
                                       uint32_t size,
                                       uint32_t domainAndAccessPerm,
                                       uint32_t initiatorPerm)
{
    int32_t  retVal = STW_SOK;
    uint32_t args[16U];
    uint32_t secTaskId = 0xFFU; /* 0xFF for new service */

    /* Number of arguments is 4 for PPA_SERV_HAL_SETUP_OCMC1_FW
     *
     * TDA2x HS devices should not open access to first 4*kB of OCMC to account
     * for a silicon errata. To ensure this, OCMC1 firewall configuration is
     * restricted to be done only via PPA service.
     *
     * Description for PPA_SERV_HAL_SETUP_OCMC1_FW
     * - PPA HAL service to configure OCMC Firewall region 2-7
     *   Any arguments which maps into first 4kB of OCMC or
     *   uses region 0 or 1 will return error.
     *
     * - startAddressAndRegionNumber :
     *     Start address for firewall region, must be aligned to 4k
     *     or'd with region number in the lower 8 bits.
     * - size :
     *     Size of the region in bytes
     * - domainAndAccessPerm :
     *     Domain and access permission bits as defined in
     *     MRM_PERMISSION_REGION_LOW_j
     * - initiatorPerm :
     *     Initiator permission bits as defined in
     *     MRM_PERMISSION_REGION_HIGH_j
     *
     */

    /* Return STW_SOK without errors on GP devices */
    if ((uint32_t) TRUE == SblLibIsExecutingOnA15HS())
    {
        /* Number of arguments */
        args[0] = 4U;
        /* Start address - aligned to 4*kB */
        args[1] = startAddress & 0xFFFFF000U;
        /* "OR" first argument with region number = 2 */
        args[1] |= regionId;
        /* Size of OCMC is 512*kB. Setting size to 4*kB less than this value */
        args[2] = size;
        /* Setting full permissions for all */
        args[3] = domainAndAccessPerm;
        args[4] = initiatorPerm;
        retVal  =
            SBLLibHSSecureEntryAsm(PPA_SERV_HAL_SETUP_OCMC1_FW,
                                   PPA_BLOCK_IRQ_FIQ,
                                   &args[0],
                                   &secTaskId);
        if (0 != retVal)
        {
            retVal = STW_EFAIL;
        }
    }
    return retVal;
}

int32_t SBLLibHSAuthenticateBinary(uint32_t address, uint32_t size)
{
    int32_t  retVal = STW_SOK;
    uint32_t args[16U];
    uint32_t secTaskId = 0xFFU; /* 0xFF for new service */

    /* Return STW_SOK without authenticating on GP devices */
    if ((uint32_t) TRUE == SblLibIsExecutingOnA15HS())
    {
        /* 4 arguments for API_HAL_KM_VERIFYCERTIFICATESIGNATURE_INDEX */
        args[0] = 4U;
        /* Start of Image to Verify */
        args[1] = address;
        /* Size of Image to Verify */
        args[2] = size - AUTH_SIGNATURE_LENGTH;
        /* Start of Auth Signature */
        args[3] = args[1] + args[2];
        /* Reserved - keep 0xFFFFFFFFU */
        args[4] = 0xFFFFFFFFU;

        if (size & 0x3U)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Invalid size \n");
        }
        else
        {
            retVal = SBLLibHSSecureEntryAsm(
                API_HAL_KM_VERIFYCERTIFICATESIGNATURE_INDEX,
                PPA_BLOCK_IRQ_FIQ, &args[0], &secTaskId);
            if (0 != retVal)
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                             "\n Authentication failed! \n");
            }
            else
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                             "\n Image authenticated!\n");
            }
        }
    }
#if defined (__ARM_ARCH_7A__)
    /* Do nothing */
#else
    /* Force error on HS devices if SBLLIB is used for code loading from
     * cores other than A15
     */
    retVal = STW_EFAIL;
#endif
    return retVal;
}

#if defined (__ARM_ARCH_7A__)
/* No need to define dummy API */
#else

int32_t SBLLibHSSecureEntryAsm(uint32_t  id,
                               uint32_t  flag,
                               uint32_t *pArgs,
                               uint32_t *secTaskId)
{
    /* This function is only available on A15.
     * Defining a dummy function for sbl-lib built on other cores
     */
    return STW_EFAIL;
}

#endif

/*
 * Checks whether code is executing on A15 on an HS device
 */
uint32_t SblLibIsExecutingOnA15HS(void)
{
#if defined (__ARM_ARCH_7A__)
    uint32_t retVal = TRUE;
    uint32_t deviceType;
    deviceType =
        HW_RD_FIELD32((SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                       CTRL_CORE_STATUS), CTRL_CORE_STATUS_DEVICE_TYPE);
    if (CTRL_CORE_STATUS_DEVICE_TYPE_DEV_HS != deviceType)
    {
        retVal = (uint32_t) FALSE;
    }
    return retVal;
#else
    return (uint32_t) FALSE;
#endif
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

