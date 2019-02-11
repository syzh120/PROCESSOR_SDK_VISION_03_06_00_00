/*  ============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015-2017
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

/* ========================================================================== */
/*                         Include Files                                      */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t CSL_getSocSiliconPackageType(void)
{
    uint32_t packageType = CSL_SOC_SILICON_PACKAGE_TYPE_UNKNOWN;
    uint32_t regVal;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                           CTRL_WKUP_STD_FUSE_DIE_ID_2,
                           CTRL_WKUP_STD_FUSE_DIE_ID_2_PACKAGE_TYPE);
    if (0x1U == regVal)
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_17X17;
    }
    else if (0x2U == regVal)
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_23X23;
    }
    else
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_UNKNOWN;
    }
#elif defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    regVal = HW_RD_FIELD32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                           CTRL_CORE_BOOTSTRAP,
                           CTRL_CORE_BOOTSTRAP_SYSBOOT_7);
    if (0x1U == regVal)
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_12X12;
    }
    else
    {
        packageType = CSL_SOC_SILICON_PACKAGE_TYPE_15X15;
    }
#endif

    return packageType;
}

uint32_t CSL_getSocSiliconRev(void)
{
    uint32_t siliconRev = CSL_SOC_SILICON_REV_UNKNOWN;

#if defined (SOC_AM574x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
    siliconRev = HW_RD_REG32(SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
                             CTRL_WKUP_ID_CODE);

    siliconRev = (siliconRev & 0xF0000000U) >> 28U;
#endif

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    siliconRev = HW_RD_REG32(
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE + CTRL_WKUP_STD_FUSE_DIE_ID_3);

    siliconRev = siliconRev & 0x0000001FU;
#endif

    return (siliconRev);
}

