/********************************************************************
 * Copyright (C) 2015-2017 Texas Instruments Incorporated.
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
#ifndef CSLR_PCIE_TOP_H
#define CSLR_PCIE_TOP_H

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


#if defined(SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined(SOC_AM571x) || defined(SOC_TDA2EX) || defined(SOC_DRA72x)
#include <ti/csl/src/ip/pcie/V1/cslr_pcie.h>
#include <ti/csl/src/ip/pcie/V1/cslr_ep_cfg_dbics2.h>
#include <ti/csl/src/ip/pcie/V1/cslr_ep_cfg_dbics.h>
#include <ti/csl/src/ip/pcie/V1/cslr_ep_cfg.h>
#include <ti/csl/src/ip/pcie/V1/cslr_pl_conf.h>
#include <ti/csl/src/ip/pcie/V1/cslr_rc_cfg_dbics2.h>
#include <ti/csl/src/ip/pcie/V1/cslr_rc_cfg_dbics.h>
#include <ti/csl/src/ip/pcie/V1/cslr_rc_cfg.h>
#include <ti/csl/src/ip/pcie/V1/cslr_pcie.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_ep_cfg_dbics2.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_ep_cfg_dbics.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_ep_cfg_pcie.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_pl_conf.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_rc_cfg_dbics2.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_rc_cfg_dbics.h>
#include <ti/csl/src/ip/pcie/V1/hw_pciectrl_ti_conf.h>
#elif defined(SOC_C6678)||defined(SOC_C6657)
#include <ti/csl/src/ip/pcie/V0/cslr_pcie_cfg_space_endpoint.h>
#include <ti/csl/src/ip/pcie/V0/cslr_pcie_cfg_space_rootcomplex.h>
#include <ti/csl/src/ip/pcie/V0/cslr_pciess_app.h>
#include <ti/csl/src/ip/pcie/V0/cslr_pciess_cfgtype0.h>
#include <ti/csl/src/ip/pcie/V0/cslr_pciess_cfgtype1.h>
#else
#include <ti/csl/src/ip/pcie/V0/cslr_pcie_cfg_space_endpoint.h>
#include <ti/csl/src/ip/pcie/V0/cslr_pcie_cfg_space_rootcomplex.h>
#include <ti/csl/src/ip/pcie/V0/cslr_pciess_app.h>
/* Two files aren't used by LLD */
/* #include <ti/csl/src/ip/pcie/V0/cslr_pciess_cfgtype0.h> */
/* #include <ti/csl/src/ip/pcie/V0/cslr_pciess_cfgtype1.h> */
#endif

#endif
