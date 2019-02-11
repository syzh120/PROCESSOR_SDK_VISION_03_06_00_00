/*
 *   Copyright (c) Texas Instruments Incorporated 2012-2016
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
 */

/**
 *  \defgroup BSP_SAFETY_OSAL_API Safety OSAL API
 *
 *  @{
 */

/**
 *  \file bsp_safety_osal.h
 *
 *  \brief Safety OSAL Interface.
 */

#ifndef BSP_SAFETY_OSAL_H_
#define BSP_SAFETY_OSAL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Safety Mode is ASIL */
#define BSP_SAFETY_OSAL_MODE_ASIL   (0x0U)

/** \brief Safety Mode is QM */
#define BSP_SAFETY_OSAL_MODE_QM     (0x1U)

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/**
 *  \brief Switch Safety Mode
 *
 *  This function switches the safety mode. User should pass the desired safety
 *  mode.
 *
 *  \param  safetyMode     [IN] Safety Mode to be set
 *
 *  \return curSafetyMode  Safety Mode before switch.
 */
UInt32 BspSafetyOsal_setSafetyMode(UInt32 safetyMode);

/**
 *  \brief Get Safety Mode
 *
 *  This function returns the current safety mode.
 *
 *  \return curSafetyMode Current safety Mode.
 *
 */
UInt32 BspSafetyOsal_getSafetyMode(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_SAFETY_OSAL_H_ */

/* @} */
