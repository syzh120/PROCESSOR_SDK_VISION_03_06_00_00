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
 *  @file   ipclib_interruptTda3xxMailboxCfg.c
 *
 *  @brief  This file contains platform specific configuration
 *          for ipclib interrupt module.
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

/**
 * DES_ID : DOX_DES_TAG(DES_IPC_LITE_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1407) DOX_REQ_TAG(PDK-1409) DOX_REQ_TAG(PDK-1429)
 *                DOX_REQ_TAG(PDK-1432)
 */
/* Cross bar to interrrupt controller mapping for cores in TDA2xx */
IpcLib_InterruptXbar IpcLib_gXbarConfig[] = {
#if defined (BUILD_DSP_1)
    /* DSP1 as dst */
    {40U, 237U},  /* DSP1 <- IPU1/DSP2   */
    {41U, 284U},  /* DSP1 <- EVE1        */
    {LE,  LE  }   /* Last Entry - need to be maintained always */
#endif

#if defined (BUILD_DSP_2)
    /* DSP2 as dst */
    {40U, 238U},  /* DSP2 <- IPU1/DSP1   */
    {41U, 285U},  /* DSP2 <- EVE1   */
    {LE,  LE  }   /* Last Entry - need to be maintained always */
#endif

#if defined (BUILD_IPU1_0) /* this configures for ipu1_0 always
                           **/
    /* IPU1_0 as dst */
    {33U, 239U},           /* IPU1_0 / IPU1 <- DSP1/DSP2   */
    {40U, 286U},           /* IPU1_0 / IPU1 <- EVE1   */
    {LE,  LE  }            /* Last Entry - need to be maintained
                            *always */
#endif
#if defined (BUILD_IPU1_1)
    /* IPU1_1 as dst */
    {34U, 240U},  /* IPU1_1 <- DSP1/DSP2    */
    {41U, 287U},  /* IPU1_1 <- EVE1   */
    {LE,  LE  }   /* Last Entry - need to be maintained always */
#endif

    /* Nothing to be done in crossbar for EVE to EVE communication
     * Since they use internal mailboxes
     */
#if defined (BUILD_ARP32)
    {LE,  LE  }   /* Last Entry - need to be maintained always */
#endif
};

/* interrrupt numbers for cores in TDA3xx */
uint32_t IpcLib_gIntNumConfig[IPCLIB_MAX_PROC] = {
    /* Nothing to be done in crossbar for EVE to EVE communication
     * Since they use internal mailboxes
     */

#if defined (BUILD_DSP_1) || defined (BUILD_DSP_2)
    71U,  /* DSP1   */
    71U,  /* DSP2   */
    71U,  /* IPU1_0 */
    71U,  /* IPU1_1 */
    72U,  /* EVE1   */
#endif

#if defined (__TI_ARM_V7M4__)

    #if defined (BUILD_IPU1_0)
    55U,      /* DSP1   */
    55U,      /* DSP2   */
    IE,       /* IPU1_0 */
    #if !defined (SMP_BIOS)
    55U,      /* IPU1_1 */
    #else
    19U,      /* IPU1_1 */
    #endif
    62U       /* EVE1   */
    #endif

    #if defined (BUILD_IPU1_1)
    56U,      /* DSP1   */
    56U,      /* DSP2   */
    #if !defined (SMP_BIOS)
    56U,      /* IPU1_0 */
    #else
    19U,      /* IPU1_0 */
    #endif
    IE,       /* IPU1_1 */
    63U       /* EVE1   */
    #endif

#endif

#if defined (BUILD_ARP32)
    29U,  /* DSP1   */
    29U,  /* DSP2   */
    29U,  /* IPU1_0 */
    30U,  /* IPU1_1 */
    IE    /* EVE1   */
#endif
};

