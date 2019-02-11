/*
* hw_dss_dssreg.h
*
* Register-level header file for DSS_DSSREG
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
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

#ifndef HW_DSS_DSSREG_H_
#define HW_DSS_DSSREG_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DSS_DSSREG_REVISION                                         (0x0U)
#define DSS_DSSREG_SYSCONFIG                                        (0x10U)
#define DSS_DSSREG_SYSSTATUS                                        (0x14U)
#define DSS_DSSREG_VENC_CTRL                                        (0x18U)
#define DSS_DSSREG_DPI_CTRL                                         (0x1cU)
#define DSS_DSSREG_DEBUG_CFG                                        (0x40U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_DSSREG_REVISION_REV_SHIFT                                                   (0U)
#define DSS_DSSREG_REVISION_REV_MASK                                                    (0x000000ffU)

#define DSS_DSSREG_REVISION_RESERVED_2_SHIFT                                            (8U)
#define DSS_DSSREG_REVISION_RESERVED_2_MASK                                             (0xffffff00U)

#define DSS_DSSREG_SYSCONFIG_SIDLEMODE_SHIFT                                            (0U)
#define DSS_DSSREG_SYSCONFIG_SIDLEMODE_MASK                                             (0x00000003U)
#define DSS_DSSREG_SYSCONFIG_SIDLEMODE_FIDLE                                             (0U)
#define DSS_DSSREG_SYSCONFIG_SIDLEMODE_NIDLE                                             (1U)
#define DSS_DSSREG_SYSCONFIG_SIDLEMODE_SIDLE                                             (2U)
#define DSS_DSSREG_SYSCONFIG_SIDLEMODE_RES                                               (3U)

#define DSS_DSSREG_SYSCONFIG_RESERVED2_SHIFT                                            (2U)
#define DSS_DSSREG_SYSCONFIG_RESERVED2_MASK                                             (0x0000000cU)

#define DSS_DSSREG_SYSCONFIG_RESERVED3_SHIFT                                            (4U)
#define DSS_DSSREG_SYSCONFIG_RESERVED3_MASK                                             (0x00000010U)

#define DSS_DSSREG_SYSCONFIG_SCPMUXING_SHIFT                                            (16U)
#define DSS_DSSREG_SYSCONFIG_SCPMUXING_MASK                                             (0x00010000U)
#define DSS_DSSREG_SYSCONFIG_SCPMUXING_HDMISCP                                           (0U)
#define DSS_DSSREG_SYSCONFIG_SCPMUXING_DPSCP                                             (1U)

#define DSS_DSSREG_SYSCONFIG_RESERVED4_SHIFT                                            (5U)
#define DSS_DSSREG_SYSCONFIG_RESERVED4_MASK                                             (0x0000ffe0U)

#define DSS_DSSREG_SYSCONFIG_RESERVED5_SHIFT                                            (17U)
#define DSS_DSSREG_SYSCONFIG_RESERVED5_MASK                                             (0xfffe0000U)

#define DSS_DSSREG_SYSCONFIG_RESERVED_SCP_SHIFT                                         (16U)
#define DSS_DSSREG_SYSCONFIG_RESERVED_SCP_MASK                                          (0x00010000U)

#define DSS_DSSREG_SYSSTATUS_RESETDONE_SHIFT                                            (0U)
#define DSS_DSSREG_SYSSTATUS_RESETDONE_MASK                                             (0x00000001U)
#define DSS_DSSREG_SYSSTATUS_RESETDONE_RSTCOMP                                           (1U)
#define DSS_DSSREG_SYSSTATUS_RESETDONE_RSTACT                                            (0U)

#define DSS_DSSREG_SYSSTATUS_DSI_A_RESETDONE_SHIFT                                      (1U)
#define DSS_DSSREG_SYSSTATUS_DSI_A_RESETDONE_MASK                                       (0x00000002U)

#define DSS_DSSREG_SYSSTATUS_DSI_B_RESETDONE_SHIFT                                      (2U)
#define DSS_DSSREG_SYSSTATUS_DSI_B_RESETDONE_MASK                                       (0x00000004U)

#define DSS_DSSREG_SYSSTATUS_HDMI_RESETDONE_SHIFT                                       (3U)
#define DSS_DSSREG_SYSSTATUS_HDMI_RESETDONE_MASK                                        (0x00000008U)

#define DSS_DSSREG_SYSSTATUS_DP_A_RESETDONE_SHIFT                                       (4U)
#define DSS_DSSREG_SYSSTATUS_DP_A_RESETDONE_MASK                                        (0x00000010U)

#define DSS_DSSREG_SYSSTATUS_DP_B_RESETDONE_SHIFT                                       (5U)
#define DSS_DSSREG_SYSSTATUS_DP_B_RESETDONE_MASK                                        (0x00000020U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_SHIFT                                             (7U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_MASK                                              (0xffffff80U)

#define DSS_DSSREG_SYSSTATUS_VENC_RESETDONE_SHIFT                                       (6U)
#define DSS_DSSREG_SYSSTATUS_VENC_RESETDONE_MASK                                        (0x00000040U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_DSIA_SHIFT                                        (1U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_DSIA_MASK                                         (0x00000002U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_DSIB_SHIFT                                        (2U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_DSIB_MASK                                         (0x00000004U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_HDMI_SHIFT                                        (3U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_HDMI_MASK                                         (0x00000008U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_DPA_SHIFT                                         (4U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_DPA_MASK                                          (0x00000010U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_DPB_SHIFT                                         (5U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_DPB_MASK                                          (0x00000020U)

#define DSS_DSSREG_SYSSTATUS_RESERVED_VENC_SHIFT                                        (6U)
#define DSS_DSSREG_SYSSTATUS_RESERVED_VENC_MASK                                         (0x00000040U)

#define DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE_SHIFT                                      (0U)
#define DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE_MASK                                       (0x00000001U)
#define DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE_DISABLE                                     (0U)
#define DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE                                             (1U)

#define DSS_DSSREG_VENC_CTRL_DAC_DEMEN_SHIFT                                            (1U)
#define DSS_DSSREG_VENC_CTRL_DAC_DEMEN_MASK                                             (0x00000002U)
#define DSS_DSSREG_VENC_CTRL_DAC_DEMEN_DISABLE                                           (0U)
#define DSS_DSSREG_VENC_CTRL_DAC_DEMEN_ENABLE                                            (1U)

#define DSS_DSSREG_VENC_CTRL_DAC_POWERDN_BGZ_SHIFT                                      (2U)
#define DSS_DSSREG_VENC_CTRL_DAC_POWERDN_BGZ_MASK                                       (0x00000004U)
#define DSS_DSSREG_VENC_CTRL_DAC_POWERDN_BGZ_DISABLE                                     (0U)
#define DSS_DSSREG_VENC_CTRL_DAC_POWERDN_BGZ_ENABLE                                      (1U)

#define DSS_DSSREG_VENC_CTRL_RESERVED_SHIFT                                             (3U)
#define DSS_DSSREG_VENC_CTRL_RESERVED_MASK                                              (0xfffffff8U)

#define DSS_DSSREG_DPI_CTRL_ENABLE_SHIFT                                                (0U)
#define DSS_DSSREG_DPI_CTRL_ENABLE_MASK                                                 (0x00000001U)
#define DSS_DSSREG_DPI_CTRL_ENABLE_DISABLE                                               (0U)
#define DSS_DSSREG_DPI_CTRL_ENABLE                                                       (1U)

#define DSS_DSSREG_DPI_CTRL_RESERVED_SHIFT                                              (1U)
#define DSS_DSSREG_DPI_CTRL_RESERVED_MASK                                               (0xfffffffeU)

#define DSS_DSSREG_DEBUG_CFG_SHIFT                                                      (0U)
#define DSS_DSSREG_DEBUG_CFG_MASK                                                       (0x00000007U)
#define DSS_DSSREG_DEBUG_CFG_DISPC                                                       (0U)
#define DSS_DSSREG_DEBUG_CFG_DSI1_A                                                      (1U)
#define DSS_DSSREG_DEBUG_CFG_DSI1_B                                                      (2U)
#define DSS_DSSREG_DEBUG_CFG_DP_A                                                        (3U)
#define DSS_DSSREG_DEBUG_CFG_DP_B                                                        (4U)
#define DSS_DSSREG_DEBUG_CFG_HDMI                                                        (5U)

#define DSS_DSSREG_DEBUG_CFG_RESERVED_SHIFT                                             (3U)
#define DSS_DSSREG_DEBUG_CFG_RESERVED_MASK                                              (0xfffffff8U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_DSSREG_H_ */

