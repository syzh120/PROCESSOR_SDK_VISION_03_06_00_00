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
 *  @file   ipclib_interruptTda2exMailboxCfg.c
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
#include <ti/drv/ipc_lite/ipclib_interruptTda2ex.h>

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
    {26U,  249U}, /* DSP1 <- IPU1_0, HOST, IPU1_1 */
    {29U,  257U}, /* DSP1 <- DSP2, IPU2_0 */
    {30U,  261U}, /* DSP1 <- IPU2_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (SMP_BIOS) || defined (BUILD_IPU1_0)
    /* IPU1_0 as dst */
    {44U,  250U}, /* IPU1_0 / IPU1 <- DSP1, HOST */
    {47U,  259U}, /* IPU1_0 / IPU1 <- DSP2, IPU2_0 */
    {48U,  263U}, /* IPU1_0 / IPU1 <- IPU2_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained
                   *always */
#endif
#if defined (SMP_BIOS) || defined (BUILD_IPU1_1)
    /* IPU1_1 as dst */
    {51U,  252U}, /* IPU1_1 <- DSP1, HOST */
    {54U,  263U}, /* IPU1_1 <- DSP2, IPU2_0 */
    {LE,   LE  }, /* Last Entry - need to be maintained always */
#endif

#if defined (SMP_BIOS) || defined (BUILD_IPU2_0)
    /* IPU2_0 as dst */
    {44U,  254U}, /* IPU2_0 / IPU2 <- HOST */
    {47U,  260U}, /* IPU2_0 / IPU2 <- DSP1, IPU1_0 */
    {48U,  264U}, /* IPU2_0 / IPU2 <- IPU1_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (SMP_BIOS) || defined (BUILD_IPU2_1)
    /* IPU2_1 as dst */
    {51U,  256U}, /* IPU2_1 <- HOST */
    {54U,  264U}, /* IPU2_1 <- DSP1, IPU1_0 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (BUILD_A15_0)
    /* A15 as dst */
    {129U, 251U},  /* A15 <- DSP1, IPU1_0, IPU1_1 */
    {134U, 255U},  /* A15 <- DSP2, IPU2_0, IPU2_1 */
    {LE,   LE  }   /* Last Entry - need to be maintained always */
#endif
};

/* interrrupt numbers for cores in TDA2xx */
uint32_t IpcLib_gIntNumConfig[IPCLIB_MAX_PROC] = {

#if defined (BUILD_DSP_1)
    60U,  /* DSP1 */
    57U,  /* IPU1_0 */
    60U,  /* IPU2_0 */
    57U,  /* A15 */
    57U,  /* IPU1_1 */
    61U   /* IPU2_1 */
#endif

#if defined (__TI_ARM_V7M4__)
    #if defined (BUILD_IPU1_0) || defined (BUILD_IPU2_0)
        #if defined (BUILD_IPU1_0)
    66U,       /* DSP1 */
    IE,        /* IPU1_0 */
    69U,       /* IPU2_0 */
    66U,       /* A15 */
    69U,       /* IPU1_1 */
    70U        /* IPU2_1 */
        #endif
        #if defined (BUILD_IPU2_0)
    69U,       /* DSP1 */
    69U,       /* IPU1_0 */
    IE,        /* IPU2_0 */
    66U,       /* A15 */
    70U,       /* IPU1_1 */
    19U        /* IPU2_1 */
        #endif
    #endif

    #if defined (BUILD_IPU1_1) || defined (BUILD_IPU2_1)
        #if defined (BUILD_IPU1_1)
    73U,       /* DSP1 */
    76U,       /* IPU1_0 */
    76U,       /* IPU2_0 */
    73U,       /* A15 */
    IE,        /* IPU1_1 */ /* new */
    IE         /* IPU2_1 */
        #endif
        #if defined (BUILD_IPU2_1)
    76U,       /* DSP1 */
    76U,       /* IPU1_0 */
    19U,       /* IPU2_0 */
    73U,       /* A15 */
    IE,        /* IPU1_1 */ /* new */
    IE         /* IPU2_1 */
        #endif
    #endif
#endif

#if defined (BUILD_A15_0)
#ifdef SYSBIOS
    /* obtained by looking at MPU IRQ + 32 */
    136U + 32U, /* DSP1 */
    136U + 32U, /* IPU1-0 */
    141U + 32U, /* IPU2-0 */
    IE,         /* HOST */
    136U + 32U, /* IPU1_1 */
    141U + 32U  /* IPU2_1 */
#else
    136U,       /* DSP1 */
    136U,       /* IPU1_0 */
    141U,       /* IPU2_0 */
    IE,         /* HOST */
    136U,       /* IPU1_1 */
    141U        /* IPU2_1 */
#endif
#endif
};

