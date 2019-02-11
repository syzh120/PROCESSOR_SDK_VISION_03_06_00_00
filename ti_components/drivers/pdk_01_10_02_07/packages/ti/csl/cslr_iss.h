/********************************************************************
 * Copyright (C) 2013-2017 Texas Instruments Incorporated.
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

#ifndef CSLR_ISS_TOP_H_
#define CSLR_ISS_TOP_H_

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x) || defined (SOC_TDA2PX) || defined (SOC_AM574x)
#include <ti/csl/cslr_cal.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_regs.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_h3a.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_ipipe.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_ipipeif.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_isif.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_lvdsrx.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_nsf3.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_regs.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_rsz.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_simcop_dma.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_simcop_regs.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_sys1.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_sys2.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_sys3.h>
#include <ti/csl/src/ip/iss/V0/hw_iss_vtnf.h>
#endif

#endif
