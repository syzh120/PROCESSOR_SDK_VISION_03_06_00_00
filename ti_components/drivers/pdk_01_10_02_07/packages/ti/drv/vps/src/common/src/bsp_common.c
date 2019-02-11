/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bsp_common.c
 *
 *  \brief Interface file to the common utility function.
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
#include <ti/drv/vps/include/common/bsp_common.h>
#include <bsp_commonPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_commonInit(const Bsp_CommonInitParams *initPrms)
{
    Int32 retVal = BSP_SOK;

    if (NULL == initPrms)
    {
        GT_0trace(BspUtilsTrace, GT_ERR, "NULL init params!!\r\n");
        retVal = BSP_EBADARGS;
    }
    else
    {
        retVal = BspUtils_init();
    }

    return (retVal);
}

Int32 Bsp_commonDeInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

    retVal = BspUtils_deInit(NULL);

    return (retVal);
}

/**
 *  Bsp_getVersionString
 *  \brief Get the BSP package version in string form. This API can be
 *  called before calling #Bsp_commonInit().
 *
 *  \return             Returns pointer to BSP version string.
 */
const Char *Bsp_getVersionString(void)
{
    return (BSP_VERSION_STRING);
}

/**
 *  Bsp_getVersionNumber
 *  \brief Get the BSP package version in number form. This API can be
 *  called before calling #Bsp_commonInit().
 *
 *  \return             BSP version number.
 */
UInt32 Bsp_getVersionNumber(void)
{
    return (BSP_VERSION_NUMBER);
}

