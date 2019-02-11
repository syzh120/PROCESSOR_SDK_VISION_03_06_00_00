/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2017
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
 *  \file      prcm/pmhal_prcm.h
 *
 *  \brief     This file contains enumeration declarations for different
 *             elements of PRCM like clock, module, power domain, etc.
 *             which uniquely identifies each element of PRCM.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *             If manual changes are required the implications of the
 *             change in this and other auto generated files has to be
 *             completely understood.
 */

#ifndef PMHAL_PRCM_TOP_H_
#define PMHAL_PRCM_TOP_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined(SOC_AM572x) || defined(SOC_DRA75x)
#include <ti/drv/pm/include/prcm/V0/pmhal_prcm.h>
#endif

#if defined (SOC_TDA2PX) || defined (SOC_AM574x)
#include <ti/drv/pm/include/prcm/V5/pmhal_prcm.h>
#endif

#if defined(SOC_TDA2EX) || defined(SOC_DRA72x) || defined(SOC_AM571x)
#include <ti/drv/pm/include/prcm/V1/pmhal_prcm.h>
#endif

#if defined(SOC_TDA3XX) || defined (SOC_DRA78x)
#include <ti/drv/pm/include/prcm/V2/pmhal_prcm.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* PMHAL_PRCM_TOP_H_ */

