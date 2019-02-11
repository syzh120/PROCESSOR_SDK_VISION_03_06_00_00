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
 *  @file   ipclib_interruptTda2xxMailboxCfg.c
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
#include <ti/drv/ipc_lite/ipclib_interruptTda2xx.h>

/**
 * DES_ID : DOX_DES_TAG(DES_IPC_LITE_005)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1407) DOX_REQ_TAG(PDK-1409) DOX_REQ_TAG(PDK-1429)
 *                DOX_REQ_TAG(PDK-1432)
 */
/* Cross bar to interrrupt controller mapping for cores in TDA2xx */
IpcLib_InterruptXbar IpcLib_gXbarConfig[] = {
    /* Nothing to be done in crossbar for EVE to EVE communication
     * Since they use internal mailboxes
     */
#if defined (BUILD_ARP32)
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (BUILD_DSP_1)
    /* DSP1 as dst */
    {24U,  284U}, /* DSP1 <- EVE1   */
    {25U,  293U}, /* DSP1 <- EVE2   */
    {26U,  249U}, /* DSP1 <- IPU1_0, HOST, IPU1_1 */
    {27U,  302U}, /* DSP1 <- EVE3 */
    {28U,  311U}, /* DSP1 <- EVE4 */
    {29U,  257U}, /* DSP1 <- DSP2, IPU2_0 */
    {30U,  261U}, /* DSP1 <- IPU2_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (BUILD_DSP_2)
    /* DSP2 as dst */
    {24U,  287U}, /* DSP2 <- EVE1   */
    {25U,  296U}, /* DSP2 <- EVE2   */
    {26U,  253U}, /* DSP2 <- IPU1_0, HOST, IPU1_1 */
    {27U,  305U}, /* DSP2 <- EVE3 */
    {28U,  314U}, /* DSP2 <- EVE4 */
    {29U,  258U}, /* DSP2 <- DSP1, IPU2_0 */
    {30U,  262U}, /* DSP2 <- IPU2_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (SMP_BIOS) || defined (BUILD_IPU1_0)
    /* IPU1_0 as dst */
    {42U,  285U}, /* IPU1_0 / IPU1 <- EVE1   */
    {43U,  294U}, /* IPU1_0 / IPU1 <- EVE2   */
    {44U,  250U}, /* IPU1_0 / IPU1 <- DSP1, HOST */
    {45U,  303U}, /* IPU1_0 / IPU1 <- EVE3 */
    {46U,  312U}, /* IPU1_0 / IPU1 <- EVE4 */
    {47U,  259U}, /* IPU1_0 / IPU1 <- DSP2, IPU2_0 */
    {48U,  263U}, /* IPU1_0 / IPU1 <- IPU2_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained
                   *always */
#endif
#if defined (SMP_BIOS) || defined (BUILD_IPU1_1)
    /* IPU1_1 as dst */
    {49U,  289U}, /* IPU1_1 <- EVE1   */
    {50U,  298U}, /* IPU1_1 <- EVE2   */
    {51U,  252U}, /* IPU1_1 <- DSP1,  */
    {52U,  307U}, /* IPU1_1 <- EVE3 */
    {53U,  316U}, /* IPU1_1 <- EVE4 */
    {54U,  263U}, /* IPU1_1 <- DSP2, IPU2_0 */
    {LE,   LE  }, /* Last Entry - need to be maintained always */
#endif

#if defined (SMP_BIOS) || defined (BUILD_IPU2_0)
    /* IPU2_0 as dst */
    {42U,  288U}, /* IPU2_0 / IPU2 <- EVE1   */
    {43U,  297U}, /* IPU2_0 / IPU2 <- EVE2   */
    {44U,  254U}, /* IPU2_0 / IPU2 <- DSP2, HOST */
    {45U,  306U}, /* IPU2_0 / IPU2 <- EVE3 */
    {46U,  315U}, /* IPU2_0 / IPU2 <- EVE4 */
    {47U,  260U}, /* IPU2_0 / IPU2 <- DSP1, IPU1_0 */
    {48U,  264U}, /* IPU2_0 / IPU2 <- IPU1_1 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif
#if defined (SMP_BIOS) || defined (BUILD_IPU2_1)
    /* IPU2_1 as dst */
    {49U,  289U}, /* IPU2_1 <- EVE1   */
    {50U,  298U}, /* IPU2_1 <- EVE2   */
    {51U,  256U}, /* IPU2_1 <- DSP2, HOST */
    {52U,  307U}, /* IPU2_1 <- EVE3 */
    {53U,  316U}, /* IPU2_1 <- EVE4 */
    {54U,  264U}, /* IPU2_1 <- DSP1, IPU1_0 */
    {LE,   LE  }  /* Last Entry - need to be maintained always */
#endif

#if defined (BUILD_A15_0)
    /* A15 as dst */
    {127U, 286U},  /* A15 <- EVE1   */
    {128U, 295U},  /* A15 <- EVE2   */
    {129U, 251U},  /* A15 <- DSP1, IPU1_0, IPU1_1 */
    {130U, 304U},  /* A15 <- EVE3 */
    {131U, 313U},  /* A15 <- EVE4 */
    {134U, 255U},  /* A15 <- DSP2, IPU2_0, IPU2_1 */
    {LE,   LE  }   /* Last Entry - need to be maintained always */
#endif
};

/* interrrupt numbers for cores in TDA2xx */
uint32_t IpcLib_gIntNumConfig[IPCLIB_MAX_PROC] = {
    /* Nothing to be done in crossbar for EVE to EVE communication
     * Since they use internal mailboxes
     */
#if defined (BUILD_DSP_1)
    55U,  /* EVE1 */
    56U,  /* EVE2 */
    58U,  /* EVE3 */
    59U,  /* EVE4 */
    60U,  /* DSP1 */
    60U,  /* DSP2 */
    57U,  /* IPU1_0 */
    60U,  /* IPU2_0 */
    57U,  /* A15 */
    57U,  /* IPU1_1 */
    61U   /* IPU2_1 */
#endif

#if defined (BUILD_DSP_2)
    55U,  /* EVE1 */
    56U,  /* EVE2 */
    58U,  /* EVE3 */
    59U,  /* EVE4 */
    60U,  /* DSP1 */
    60U,  /* DSP2 */
    60U,  /* IPU1_0 */
    57U,  /* IPU2_0 */
    57U,  /* A15 */
    61U,  /* IPU1_1 */
    57U   /* IPU2_1 */
#endif

#if defined (BUILD_ARP32)
    60U,   /* EVE1 */
    60U,   /* EVE2 */
    60U,   /* EVE3 */
    60U,   /* EVE4 */
    29U,   /* DSP1 */
    30U,   /* DSP2 */
    29U,   /* IPU1_0 */
    30U,   /* IPU2_0 */
    29U,   /* A15 */
    30U,   /* IPU1_1 */
    30U    /* IPU2_1 */
#endif

#if defined (__TI_ARM_V7M4__)
    #if defined (BUILD_IPU1_0) || defined (BUILD_IPU2_0)
    64U,       /* EVE1 */
    65U,       /* EVE2 */
    67U,       /* EVE3 */
    68U,       /* EVE4 */
        #if defined (BUILD_IPU1_0)
    66U,       /* DSP1 */
    69U,       /* DSP2 */
    IE,        /* IPU1_0 */
    69U,       /* IPU2_0 */
    66U,       /* A15 */
    69U,       /* IPU1_1 */
    70U        /* IPU2_1 */
        #endif
        #if defined (BUILD_IPU2_0)
    69U,       /* DSP1 */
    66U,       /* DSP2 */
    69U,       /* IPU1_0 */
    IE,        /* IPU2_0 */
    66U,       /* A15 */
    70U,       /* IPU1_1 */
    19U        /* IPU2_1 */
        #endif
    #endif

    #if defined (BUILD_IPU1_1) || defined (BUILD_IPU2_1)
    71U,       /* EVE1 */
    72U,       /* EVE2 */
    74U,       /* EVE3 */
    75U,       /* EVE4 */
        #if defined (BUILD_IPU1_1)
    73U,       /* DSP1 */
    76U,       /* DSP2 */
    76U,       /* IPU1_0 */
    76U,       /* IPU2_0 */
    73U,       /* A15 */
    IE,        /* IPU1_1 */ /* new */
    IE         /* IPU2_1 */
        #endif
        #if defined (BUILD_IPU2_1)
    76U,       /* DSP1 */
    73U,       /* DSP2 */
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
    134U + 32U, /* EVE1 */
    135U + 32U, /* EVE2 */
    137U + 32U, /* EVE3 */
    138U + 32U, /* EVE4 */
    136U + 32U, /* DSP1 */
    141U + 32U, /* DSP2 */
    136U + 32U, /* IPU1-0 */
    141U + 32U, /* IPU2-0 */
    IE,         /* HOST */
    136U + 32U, /* IPU1_1 */
    141U + 32U  /* IPU2_1 */
#else
    134U,       /* EVE1 */
    135U,       /* EVE2 */
    137U,       /* EVE3 */
    138U,       /* EVE4 */
    136U,       /* DSP1 */
    141U,       /* DSP2 */
    136U,       /* IPU1_0 */
    141U,       /* IPU2_0 */
    IE,         /* HOST */
    136U,       /* IPU1_1 */
    141U        /* IPU2_1 */
#endif
#endif
};

