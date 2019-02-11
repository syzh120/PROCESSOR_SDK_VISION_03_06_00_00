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
 *  \file   hw_counter_32k.h
 *
 *  \brief  Register-level header file for COUNTER_32K
 *
**/

#ifndef HW_COUNTER_32K_H_
#define HW_COUNTER_32K_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define COUNTER_32K_REVISION                                                                                (0x0U)
#define COUNTER_32K_SYSCONFIG                                                                               (0x10U)
#define COUNTER_32K_CR                                                                                      (0x30U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define COUNTER_32K_REVISION_REVISION_SHIFT                                                                 (0U)
#define COUNTER_32K_REVISION_REVISION_MASK                                                                  (0xffffffffU)

#define COUNTER_32K_SYSCONFIG_RESERVED_1_SHIFT                                                              (1U)
#define COUNTER_32K_SYSCONFIG_RESERVED_1_MASK                                                               (0x00000006U)

#define COUNTER_32K_SYSCONFIG_IDLEMODE_SHIFT                                                                (3U)
#define COUNTER_32K_SYSCONFIG_IDLEMODE_MASK                                                                 (0x00000018U)
#define COUNTER_32K_SYSCONFIG_IDLEMODE_FORCEIDLE                                                             (0U)
#define COUNTER_32K_SYSCONFIG_IDLEMODE_NOIDLE                                                                (1U)
#define COUNTER_32K_SYSCONFIG_IDLEMODE_SMARTIDLE                                                             (2U)
#define COUNTER_32K_SYSCONFIG_IDLEMODE_RESERVED1                                                             (3U)

#define COUNTER_32K_SYSCONFIG_RESERVED_2_SHIFT                                                              (5U)
#define COUNTER_32K_SYSCONFIG_RESERVED_2_MASK                                                               (0xffffffe0U)

#define COUNTER_32K_SYSCONFIG_SYNCMODE_SHIFT                                                                (0U)
#define COUNTER_32K_SYSCONFIG_SYNCMODE_MASK                                                                 (0x00000001U)

#define COUNTER_32K_CR_COUNTER_VALUE_SHIFT                                                                  (0U)
#define COUNTER_32K_CR_COUNTER_VALUE_MASK                                                                   (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_COUNTER_32K_H_ */

