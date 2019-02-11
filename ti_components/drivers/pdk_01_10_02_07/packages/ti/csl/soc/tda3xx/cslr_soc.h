/*
 *  Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef CSLR_SOC_IN_H_
#define CSLR_SOC_IN_H_

#if defined (__TI_ARM_V7M4__)
#include <ti/csl/soc/tda3xx/armv7m/soc.h>
#elif defined (_TMS320C6X)
#include <ti/csl/soc/tda3xx/c66x/soc.h>
#elif defined (BUILD_ARP32)
#include <ti/csl/soc/tda3xx/arp32/soc.h>
#endif
#include <ti/csl/soc/tda3xx/cslr_soc_defines.h>
#include <ti/csl/soc/tda3xx/csl_device_xbar.h>
#include <ti/csl/soc/common/csl_device_common.h>
#include <ti/csl/soc/tda3xx/soc_defines_xbar_map.h>

#include <ti/csl/soc/tda3xx/hw_cam_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_cam_prm.h>
#include <ti/csl/soc/tda3xx/hw_ckgen_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_ckgen_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_ckgen_prm.h>
#include <ti/csl/soc/tda3xx/hw_cmi.h>
#include <ti/csl/soc/tda3xx/hw_core_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_core_prm.h>
#include <ti/csl/soc/tda3xx/hw_coreaon_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_core.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_core_irq_dma.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_core_pad.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_core_pad_io.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_core_sec.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_wkup.h>
#include <ti/csl/soc/tda3xx/hw_ctrl_wkup_pad.h>
#include <ti/csl/soc/tda3xx/hw_custefuse_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_custefuse_prm.h>
#include <ti/csl/soc/tda3xx/hw_device_prm.h>
#include <ti/csl/soc/tda3xx/hw_dsp1_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_dsp1_prm.h>
#include <ti/csl/soc/tda3xx/hw_dsp2_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_dsp2_prm.h>
#include <ti/csl/soc/tda3xx/hw_dss_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_dss_prm.h>
#include <ti/csl/soc/tda3xx/hw_emu_cm.h>
#include <ti/csl/soc/tda3xx/hw_emu_prm.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/soc/tda3xx/hw_eve1_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_eve1_prm.h>
#include <ti/csl/soc/tda3xx/hw_ipu_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_ipu_prm.h>
#include <ti/csl/soc/tda3xx/hw_iss_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_iss_ctset_core.h>
#include <ti/csl/soc/tda3xx/hw_iss_prm.h>
#include <ti/csl/soc/tda3xx/hw_l3init_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_l3init_prm.h>
#include <ti/csl/soc/tda3xx/hw_l4_cfg_ap.h>
#include <ti/csl/soc/tda3xx/hw_l4_cfg_ia_ip0.h>
#include <ti/csl/soc/tda3xx/hw_l4_cfg_la.h>
#include <ti/csl/soc/tda3xx/hw_l4per_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_l4per_prm.h>
#include <ti/csl/soc/tda3xx/hw_ocp_socket_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_ocp_socket_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_ocp_socket_prm.h>
#include <ti/csl/soc/tda3xx/hw_pmi.h>
#include <ti/csl/soc/tda3xx/hw_restore_cm_core.h>
#include <ti/csl/soc/tda3xx/hw_restore_cm_core_aon.h>
#include <ti/csl/soc/tda3xx/hw_sysconfig.h>
#include <ti/csl/soc/tda3xx/hw_wkupaon_cm.h>
#include <ti/csl/soc/tda3xx/hw_wkupaon_prm.h>
#include <ti/csl/soc/tda3xx/hw_ipu_wugen_local_prcm.h>
#include <ti/csl/soc/tda3xx/hw_ipu_m4_nvic.h>

#ifdef __cplusplus
extern "C" {
#endif

/** I2C      */
#define CSL_I2C_0_MODULE_FREQ               (96000000)
#define CSL_I2C_1_MODULE_FREQ               (96000000)
/** UART     */
#define CSL_UART_0_MODULE_FREQ              (48000000)
#define CSL_UART_1_MODULE_FREQ              (48000000)
#define CSL_UART_2_MODULE_FREQ              (48000000)

/** @brief Number of UART instances                                           */
#define CSL_UART_PER_CNT                    (3U)

/** @brief Number of McASP instances                                         */
#define CSL_MCASP_PER_CNT                   (3U)
#define CSL_MCASP_0_NUMSERIALIZERS          (16U)
#define CSL_MCASP_1_NUMSERIALIZERS          (6U)
#define CSL_MCASP_2_NUMSERIALIZERS          (6U)

/** MCSPI      */
#define CSL_MCSPI_0_MODULE_FREQ             (48000000)
#define CSL_MCSPI_1_MODULE_FREQ             (48000000)
#define CSL_MCSPI_2_MODULE_FREQ             (48000000)
#define CSL_MCSPI_3_MODULE_FREQ             (48000000)


#ifdef __cplusplus
}
#endif

#endif /* CSLR_SOC_IN_H_ */
