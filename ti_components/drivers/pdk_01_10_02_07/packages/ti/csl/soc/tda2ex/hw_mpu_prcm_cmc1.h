/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_mpu_prcm_cmc1.h
 *
 *  \brief  Register-level header file for MPU
 *
**/

#ifndef HW_MPU_PRCM_CMC1_H_
#define HW_MPU_PRCM_CMC1_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MPU_CM_CPU1_CLKSTCTRL                                                                               (0x0U)
#define MPU_CM_CPU1_CPU1_CLKCTRL                                                                            (0x20U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL_SHIFT                                                               (0U)
#define MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL_MASK                                                                (0x00000003U)
#define MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                             (0U)
#define MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL_RESERVED                                                             (1U)
#define MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                              (2U)
#define MPU_CM_CPU1_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                              (3U)

#define MPU_CM_CPU1_CLKSTCTRL_RESERVED_SHIFT                                                                (2U)
#define MPU_CM_CPU1_CLKSTCTRL_RESERVED_MASK                                                                 (0xfffffffcU)

#define MPU_CM_CPU1_CPU1_CLKCTRL_STBYST_SHIFT                                                               (0U)
#define MPU_CM_CPU1_CPU1_CLKCTRL_STBYST_MASK                                                                (0x00000001U)
#define MPU_CM_CPU1_CPU1_CLKCTRL_STBYST_FUNC                                                                 (0U)
#define MPU_CM_CPU1_CPU1_CLKCTRL_STBYST_STANDBY                                                              (1U)

#define MPU_CM_CPU1_CPU1_CLKCTRL_RESERVED_SHIFT                                                             (1U)
#define MPU_CM_CPU1_CPU1_CLKCTRL_RESERVED_MASK                                                              (0xfffffffeU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_CMC1_H_ */
