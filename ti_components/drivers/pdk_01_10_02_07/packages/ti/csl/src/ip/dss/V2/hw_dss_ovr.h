/*
* hw_dss_ovr.h
*
* Register-level header file for DSS_OVR
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

#ifndef HW_DSS_OVR_H_
#define HW_DSS_OVR_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DSS_OVR_CONFIG                                              (0x0U)
#define DSS_OVR_CONTROL                                             (0x4U)
#define DSS_OVR_DEFAULT_COLOR                                       (0x8U)
#define DSS_OVR_DEFAULT_COLOR2                                      (0xcU)
#define DSS_OVR_TRANS_COLOR_MAX                                     (0x10U)
#define DSS_OVR_TRANS_COLOR_MAX2                                    (0x14U)
#define DSS_OVR_TRANS_COLOR_MIN                                     (0x18U)
#define DSS_OVR_TRANS_COLOR_MIN2                                    (0x1cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_OVR_CONFIG_TCKLCDENABLE_SHIFT                                               (10U)
#define DSS_OVR_CONFIG_TCKLCDENABLE_MASK                                                (0x00000400U)
#define DSS_OVR_CONFIG_TCKLCDENABLE_DISTCK                                               (0U)
#define DSS_OVR_CONFIG_TCKLCDENABLE_ENBTCK                                               (1U)

#define DSS_OVR_CONFIG_TCKLCDSELECTION_SHIFT                                            (11U)
#define DSS_OVR_CONFIG_TCKLCDSELECTION_MASK                                             (0x00000800U)
#define DSS_OVR_CONFIG_TCKLCDSELECTION_GDTK                                              (0U)
#define DSS_OVR_CONFIG_TCKLCDSELECTION_VSTK                                              (1U)

#define DSS_OVR_CONFIG_INTERLEAVED3DMODE_SHIFT                                          (8U)
#define DSS_OVR_CONFIG_INTERLEAVED3DMODE_MASK                                           (0x00000300U)
#define DSS_OVR_CONFIG_INTERLEAVED3DMODE_NOINTERLEAVING                                  (0U)
#define DSS_OVR_CONFIG_INTERLEAVED3DMODE_LINEINTERLEAVING                                (2U)
#define DSS_OVR_CONFIG_INTERLEAVED3DMODE_PIXELINTERLEAVING                               (3U)
#define DSS_OVR_CONFIG_INTERLEAVED3DMODE_RESERVED                                        (1U)

#define DSS_OVR_CONFIG_GLBCEEN_SHIFT                                                    (12U)
#define DSS_OVR_CONFIG_GLBCEEN_MASK                                                     (0x00001000U)
#define DSS_OVR_CONFIG_GLBCEEN_GLBCEDIS                                                  (0U)
#define DSS_OVR_CONFIG_GLBCEEN                                                           (1U)

#define DSS_OVR_CONFIG_GLBCESEL_SHIFT                                                   (13U)
#define DSS_OVR_CONFIG_GLBCESEL_MASK                                                    (0x00002000U)
#define DSS_OVR_CONFIG_GLBCESEL_GLBCE_0                                                  (0U)
#define DSS_OVR_CONFIG_GLBCESEL_GLBCE_1                                                  (1U)

#define DSS_OVR_CONTROL_OVERLAYOPTIMIZATION_SHIFT                                       (12U)
#define DSS_OVR_CONTROL_OVERLAYOPTIMIZATION_MASK                                        (0x00001000U)
#define DSS_OVR_CONTROL_OVERLAYOPTIMIZATION_GDBVWFM                                      (0U)
#define DSS_OVR_CONTROL_OVERLAYOPTIMIZATION_GDBVWNFM                                     (1U)

#define DSS_OVR_DEFAULT_COLOR_DEFAULTCOLOR_SHIFT                                        (0U)
#define DSS_OVR_DEFAULT_COLOR_DEFAULTCOLOR_MASK                                         (0xffffffffU)

#define DSS_OVR_DEFAULT_COLOR2_DEFAULTCOLOR_SHIFT                                       (0U)
#define DSS_OVR_DEFAULT_COLOR2_DEFAULTCOLOR_MASK                                        (0x0000ffffU)

#define DSS_OVR_TRANS_COLOR_MAX_TRANSCOLORKEY_SHIFT                                     (0U)
#define DSS_OVR_TRANS_COLOR_MAX_TRANSCOLORKEY_MASK                                      (0xffffffffU)

#define DSS_OVR_TRANS_COLOR_MAX2_TRANSCOLORKEY_SHIFT                                    (0U)
#define DSS_OVR_TRANS_COLOR_MAX2_TRANSCOLORKEY_MASK                                     (0x0000000fU)

#define DSS_OVR_TRANS_COLOR_MIN_TRANSCOLORKEY_SHIFT                                     (0U)
#define DSS_OVR_TRANS_COLOR_MIN_TRANSCOLORKEY_MASK                                      (0xffffffffU)

#define DSS_OVR_TRANS_COLOR_MIN2_TRANSCOLORKEY_SHIFT                                    (0U)
#define DSS_OVR_TRANS_COLOR_MIN2_TRANSCOLORKEY_MASK                                     (0x0000000fU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_OVR_H_ */

