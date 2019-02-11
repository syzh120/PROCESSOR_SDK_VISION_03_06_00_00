/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014 - 2018
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
 *  \file      V1\pmhal_prcm_includes.h
 *
 *  \brief     This file contains header files to be used by StarterWare PRCM
 *             (internal) implementation.
 */

#ifndef PMHAL_PRCM_INCLUDES_H_
#define PMHAL_PRCM_INCLUDES_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

/* All SOC files */
#include <ti/csl/soc.h>

/* IP files */
#include <ti/csl/cslr_pcie.h>
#include <ti/csl/cslr_mcasp.h>
#include <ti/csl/cslr_dss.h>
#include <ti/csl/cslr_i2c.h>
#include <ti/csl/cslr_gpmc.h>
#include <ti/csl/cslr_mmu.h>
#include <ti/csl/cslr_ocmc_ecc.h>
#include <ti/csl/cslr_spinlock.h>
#include <ti/csl/cslr_mailbox.h>
#include <ti/csl/cslr_mcspi.h>
#include <ti/csl/cslr_uart.h>
#include <ti/csl/cslr_gpio.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/cslr_vip.h>
#include <ti/csl/cslr_vpe.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/cslr_mmc.h>
#include <ti/csl/cslr_edma.h>
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
#include <ti/csl/cslr_cal.h>
#endif
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/cslr_eve.h>

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

#endif /* PMHAL_PRCM_INCLUDES_H_ */
