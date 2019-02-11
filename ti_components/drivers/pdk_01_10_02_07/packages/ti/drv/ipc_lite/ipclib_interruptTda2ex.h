/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \defgroup IPC_LIB_TDA2EX TDA2ex IPC Interrupt Connection
 *
 *  @{
 */
/**
 * @file ipclib_interruptTda2ex.h
 *
 * This file contains platform specific data structure to define
 *      interrupt connections.
 *
 *
 */

#ifndef IPCLIB_INTERRUPT_TDA2EX_H_
#define IPCLIB_INTERRUPT_TDA2EX_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                             INCLUDE FILES
 *******************************************************************************/
#include <stdint.h>
#include <string.h>

/******************************************************************************
 *                        MACRO DEFINITIONS
 ******************************************************************************/
/**
 *  \brief Max processors available for ipc.
 */
#define IPCLIB_MAX_PROC                (6U)

/**
 * \name Virtual proc ids for TDA2EX
 *  @{
 */
/**
 * \brief IPCLIB_DSP1_ID  DSP1 ID
 */
#define IPCLIB_DSP1_ID                 (0U)
/**
 * \brief IPCLIB_IPU1_0_ID  IPU1_0 ID
 */
#define IPCLIB_IPU1_0_ID               (1U)
/**
 * \brief IPCLIB_IPU2_0_ID  IPU2_0 ID
 */
#define IPCLIB_IPU2_0_ID               (2U)
/**
 * \brief IPCLIB_A15_0_ID  A15_0 ID
 */
#define IPCLIB_A15_0_ID                (3U)
/**
 * \brief IPCLIB_IPU1_1_ID  IPU1_1 ID
 */
#define IPCLIB_IPU1_1_ID               (4U)
/**
 * \brief IPCLIB_IPU2_1_ID  IPU2_1 ID
 */
#define IPCLIB_IPU2_1_ID               (5U)
/** @} */

#ifdef __cplusplus
}
#endif

#endif
/** @} */
