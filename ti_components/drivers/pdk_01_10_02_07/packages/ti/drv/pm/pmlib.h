/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 *  \defgroup PM_LIB PMLIB
 *
 *  PMLIB provides application interface to
 *     - Configure system level clock frequencies
 *     - Configure the system power states
 *     - Perform dynamic CPU power optimization
 *
 */
 
/**
 *  \file      pmlib.h
 *
 *  \brief     This file contains all includes related to PM Library.
 *
 */

#ifndef PMLIB_TOP_H_
#define PMLIB_TOP_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_AM574x) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#include <ti/drv/pm/include/pm_types.h>
#include <ti/drv/pm/include/pm_utils.h>
#include <ti/drv/pm/include/pmlib_boardconfig.h>
#include <ti/drv/pm/include/pmlib_clkrate.h>
#include <ti/drv/pm/include/pmlib_cpuidle.h>
#include <ti/drv/pm/include/pmlib_sysconfig.h>
#include <ti/drv/pm/include/pmlib_videopll.h>
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

#endif /* PMLIB_TOP_H_ */

