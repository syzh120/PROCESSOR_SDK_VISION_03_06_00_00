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
 *  @file   ipclib_interruptTda3xxProcCfg.c
 *
 *  @brief  This file contains platform specific configuration
 *          for processor in the SOC.
 *
 *
 */

/*_______________________________ Include Files _____________________________*/
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ipclib_interrupt_priv.h>
#include <ti/drv/ipc_lite/ipclib_interruptTda3xx.h>

#ifdef BUILD_DSP_1
#define IPCLIB_SELF_PROC_ID  (IPCLIB_DSP1_ID)
#endif

#ifdef BUILD_DSP_2
#define IPCLIB_SELF_PROC_ID  (IPCLIB_DSP2_ID)
#endif

#ifdef BUILD_IPU1_0
#define IPCLIB_SELF_PROC_ID  (IPCLIB_IPU1_0_ID)
#endif

#ifdef BUILD_IPU1_1
#define IPCLIB_SELF_PROC_ID  (IPCLIB_IPU1_1_ID)
#endif

#ifdef BUILD_ARP32_1
#define IPCLIB_SELF_PROC_ID  (IPCLIB_EVE1_ID)
#endif

/**
 * DES_ID : DOX_DES_TAG(DES_IPC_LITE_003)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1415)
 */
/** Virtual processor IDs to name mapping and their default status
 * for cores in TDA3xx
 */
IpcLib_InterruptProcCfg IpcLib_gProcConfig = {
    (uint32_t) IPCLIB_SELF_PROC_ID,              /* selfProcId
                                                 **/
    {
        {(uint32_t) IPCLIB_DSP1_ID,   "DSP1"  }, /* DSP1 */
        {(uint32_t) IPCLIB_DSP2_ID,   "DSP2"  }, /* DSP2 */
        {(uint32_t) IPCLIB_IPU1_0_ID, "IPU1-0"}, /* IPU1_0 */
        {(uint32_t) IPCLIB_IPU1_1_ID, "IPU1-1"}, /* IPU1_1 */
        {(uint32_t) IPCLIB_EVE1_ID,   "EVE1"  }  /* EVE1 */
    }
};
