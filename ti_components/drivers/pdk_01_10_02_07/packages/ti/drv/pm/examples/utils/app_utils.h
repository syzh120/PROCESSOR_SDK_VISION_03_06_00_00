/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file     app_utils.h
 *
 *  \brief    This file contains common utility functions used by the apps
 *
 */

#ifndef APP_UTILS_H_
#define APP_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the Silicon Package Type of SoC.
 */
typedef enum platformSiliconPackageType
{
    PLATFORM_SILICON_PACKAGE_TYPE_UNKNOWN = 0,
    /**< Silicon Package type is Invalid */
    PLATFORM_SILICON_PACKAGE_TYPE_12X12 = 1,
    /**< Silicon Package type is 12x12 */
    PLATFORM_SILICON_PACKAGE_TYPE_15X15 = 2,
    /**< Silicon Package type is 15x15 */
    PLATFORM_SILICON_PACKAGE_TYPE_17X17 = 3,
    /**< Silicon Package type is 17x17 */
    PLATFORM_SILICON_PACKAGE_TYPE_23X23 = 4
                                          /**< Silicon Package type is 23x23 */
} platformSiliconPackageType_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void AppUtils_defaultInit(void);

void AppUtils_printf(const char *pStr, ...);

char AppUtils_getChar(void);
int32_t AppUtils_getCharTimeout(char *ch, uint32_t msec);
int32_t AppUtils_getNum(void);

void AppUtils_delay(uint32_t msec);
uint32_t AppUtils_getCurTimeInMsec(void);

uint32_t AppUtils_GetSiliconPackageType(void);
#ifdef __cplusplus
}
#endif

#endif  /* #ifndef APP_UTILS_H_ */
