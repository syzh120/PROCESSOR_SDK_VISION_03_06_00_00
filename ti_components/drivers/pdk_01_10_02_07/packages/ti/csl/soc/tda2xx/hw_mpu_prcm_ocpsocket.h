/*
 *  Copyright (C) 2008-2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_mpu_prcm_ocpsocket.h
 *
 *  \brief  Register-level header file for MPU
 *
**/
#ifndef HW_MPU_PRCM_OCPSOCKET_H_
#define HW_MPU_PRCM_OCPSOCKET_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MPU_REVISION                                                                                       (0x0U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MPU_REVISION_X_MAJOR_SHIFT                                                                        (8U)
#define MPU_REVISION_X_MAJOR_MASK                                                                         (0x00000700U)
#define MPU_REVISION_X_MAJOR_READ0X0                                                                      (0U)

#define MPU_REVISION_Y_MINOR_SHIFT                                                                        (0U)
#define MPU_REVISION_Y_MINOR_MASK                                                                         (0x0000003fU)
#define MPU_REVISION_Y_MINOR_READ0X0                                                                      (0U)
#define MPU_REVISION_Y_MINOR_READ0X1                                                                      (1U)

#define MPU_REVISION_CUSTOM_SHIFT                                                                         (6U)
#define MPU_REVISION_CUSTOM_MASK                                                                          (0x000000c0U)

#define MPU_REVISION_R_RTL_SHIFT                                                                          (11U)
#define MPU_REVISION_R_RTL_MASK                                                                           (0x0000f800U)

#define MPU_REVISION_FUNC_SHIFT                                                                           (16U)
#define MPU_REVISION_FUNC_MASK                                                                            (0x0fff0000U)

#define MPU_REVISION_RESERVED_SHIFT                                                                       (28U)
#define MPU_REVISION_RESERVED_MASK                                                                        (0x30000000U)

#define MPU_REVISION_SCHEME_SHIFT                                                                         (30U)
#define MPU_REVISION_SCHEME_MASK                                                                          (0xc0000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_OCPSOCKET_H_ */
