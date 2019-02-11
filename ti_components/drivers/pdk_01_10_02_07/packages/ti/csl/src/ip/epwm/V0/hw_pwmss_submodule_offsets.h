/*
* hw_pwmss_submodule_offsets.h
*
* Header file for PWMSS containing the register offset values of all its
* sub modules.
*
* Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef HW_PWMSS_SUBMODULE_OFFSETS_V0_H_
#define HW_PWMSS_SUBMODULE_OFFSETS_V0_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Sub module offset Definitions
****************************************************************************************************/

#define PWMSS_PWMSS_OFFSET                                                    (0x0U)
#define PWMSS_ECAP_OFFSET                                                     (0x100U)
#define PWMSS_EQEP_OFFSET                                                     (0x180U)
#define PWMSS_EPWM_OFFSET                                                     (0x200U)
#define PWMSS_EPWM_HRCTL_OFFSET                                               (0xC0U)
#define PWMSS_EPWM_PCCTL_TO_HRCTL_RSVD                                        (PWMSS_EPWM_HRCTL_OFFSET - 0x3EU)

#ifdef __cplusplus
}
#endif
#endif /* HW_PWMSS_SUBMODULE_OFFSETS_V0_H_ */
