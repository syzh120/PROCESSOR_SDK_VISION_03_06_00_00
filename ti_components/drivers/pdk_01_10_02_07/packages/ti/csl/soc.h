/**
 *   @file  soc.h
 *
 *   @brief
 *      This file contains SOC specific defintions.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2009-2017, Texas Instruments, Inc.
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

#ifndef CSL_SOC_H
#define CSL_SOC_H

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>

/*****************************************************************************\
* Static inline definition
\*****************************************************************************/
#ifndef CSL_IDEF_INLINE
#define CSL_IDEF_INLINE static inline
#endif

#if defined(SOC_K2K)

#include <ti/csl/soc/k2k/src/cslr_device.h>

#elif defined(SOC_K2H)

#include <ti/csl/soc/k2h/src/cslr_device.h>

#elif defined(SOC_K2E)

#include <ti/csl/soc/k2e/src/cslr_device.h>

#elif defined(SOC_K2L)

#include <ti/csl/soc/k2l/src/cslr_device.h>

#elif defined(SOC_AM574x)

#include <ti/csl/soc/am574x/src/cslr_soc.h>

#elif defined(SOC_AM572x)

#include <ti/csl/soc/am572x/src/cslr_soc.h>

#elif defined(SOC_AM571x)

#include <ti/csl/soc/am571x/src/cslr_soc.h>

#elif defined(SOC_K2G)

#include <ti/csl/soc/k2g/src/cslr_soc.h>

#elif defined (SOC_TDA2XX)

#include <ti/csl/soc/tda2xx/cslr_soc.h>

#elif defined(SOC_TDA2PX)

#include <ti/csl/soc/tda2px/cslr_soc.h>

#elif defined(SOC_TDA2EX)

#include <ti/csl/soc/tda2ex/cslr_soc.h>

#elif defined(SOC_TDA3XX)

#include <ti/csl/soc/tda3xx/cslr_soc.h>

#elif defined(SOC_DRA72x)

#include <ti/csl/soc/dra72x/cslr_soc.h>

#elif defined(SOC_DRA75x)

#include <ti/csl/soc/dra75x/cslr_soc.h>

#elif defined(SOC_DRA78x)

#include <ti/csl/soc/dra78x/cslr_soc.h>

#elif defined(SOC_C6678)

#include <ti/csl/soc/c6678/src/cslr_device.h>

#elif defined(SOC_C6657)

#include <ti/csl/soc/c6657/src/cslr_device.h>

#elif defined(SOC_OMAPL137)

#include <ti/csl/soc/omapl137/src/cslr_soc.h>

#elif defined(SOC_OMAPL138)

#include <ti/csl/soc/omapl138/src/cslr_soc.h>

#endif /* SOC_XXXXX */

#endif  /* CSL_SOC_H*/

