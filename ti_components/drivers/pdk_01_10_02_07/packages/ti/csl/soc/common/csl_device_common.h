/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup CSL_SOC
 *  \defgroup CSL_DEVICE_COMMON Device Common API
 *
 *  @{
 */
/**
 *  \file     csl_device_common.h
 *
 *  \brief    This file contains the prototypes of common device API
 *            This also contains some related macros.
 *
 */

#ifndef CSL_DEVICE_COMMON_H
#define CSL_DEVICE_COMMON_H

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Enumeration to select the Silicon Package Type of SoC.
 */
typedef enum
{
    CSL_SOC_SILICON_PACKAGE_TYPE_UNKNOWN = 0,
    /**< Silicon Package type is Invalid */
    CSL_SOC_SILICON_PACKAGE_TYPE_12X12 = 1,
    /**< Silicon Package type is 12x12 */
    CSL_SOC_SILICON_PACKAGE_TYPE_15X15 = 2,
    /**< Silicon Package type is 15x15 */
    CSL_SOC_SILICON_PACKAGE_TYPE_17X17 = 3,
    /**< Silicon Package type is 17x17 */
    CSL_SOC_SILICON_PACKAGE_TYPE_23X23 = 4
                                          /**< Silicon Package type is 23x23 */
} CSL_SocSiliconPackageType;

#if defined (SOC_TDA2XX) || defined (SOC_DRA75x) || defined (SOC_AM572x)
#define CSL_SOC_SILICON_REV_1_0     (0U)
#define CSL_SOC_SILICON_REV_1_1     (1U)
#define CSL_SOC_SILICON_REV_2_0     (2U)
#endif

#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#define CSL_SOC_SILICON_REV_1_0     (0U)
#endif

#if defined (SOC_AM574x) || defined (SOC_TDA2PX) 
#define CSL_SOC_SILICON_REV_1_0     (0U)
#endif

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#define CSL_SOC_SILICON_REV_1_0     (0U)
#define CSL_SOC_SILICON_REV_1_0_A   (1U)
#define CSL_SOC_SILICON_REV_2_0     (2U)
#endif
#define CSL_SOC_SILICON_REV_UNKNOWN (0xFFFFFFFFU)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief     API to return the silicon package type of SoC.\n
 *
 * \return  enum value of CSL_SocSiliconPackageType.
 *
**/
uint32_t CSL_getSocSiliconPackageType(void);

/**
 * \brief     API to return the silicon revision type of SoC.\n
 *
 * \return    silicon revision value
 *
**/
uint32_t CSL_getSocSiliconRev(void);

#ifdef __cplusplus
}
#endif

#endif /* CSL_DEVICE_COMMON_H */
/** @} */

/**
 *  \defgroup CSL_SOC CSL SOC Module
 */
