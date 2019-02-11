/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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

-c                                   /* LINK USING C CONVENTIONS         */
-stack  0x800                       /* SOFTWARE STACK SIZE              */
-heap   0x800                      /* HEAP AREA SIZE                   */
//-l rtsv7M3_T_le_eabi.lib             /* GET RUN-TIME SUPPORT             */
//-e Reset_Handler
-e _c_int00

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    IRAM_MEM_BOOT:     org = 0x00020000 len = 0x400        /* RAM 0x1FBFF*/
    IRAM_MEM:     org = 0x00020400 len = 0xFC00        /* RAM 0x1FBFF*/
    DDR3_A8:      org = 0x80000000 len = 0x02000000  /* 32 MB */
    DDR3_DSP:     org = 0x82000000 len = 0x02000000  /* 32 MB */
    DDR3_M4:      org = 0x84000000 len = 0x02000000  /* 32 MB */
    DDR3_SR0:     org = 0x86000000 len = 0x01000000  /* 16 MB */
    DDR3_M3VPSS:  org = 0x87000000 len = 0x01000000  /* 16 MB */

   OCMC_GMAC_RX:        org = 0x40300000 len = 0x33EFF  /* 16 MB */
   OCMC_RESULT:       org = 0x33FC00 len = 0x100  /* 16 MB */
   OCMC_IPU_BOOT:     org = 0x340000 len = 0x400  /* 16 MB */
   OCMC_SYNC:         org = 0x340400 len = 0x20
   OCMC_TESTRESULT:    org = 0x340420 len = 0x40
   OCMC_IPU:            org = 0x340460 len = 0x1FBA0
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs                : load > OCMC_IPU_BOOT
    .intc_text                 : load > OCMC_IPU
    .init                    : load > OCMC_IPU

    .text                     : load > OCMC_IPU       /*       CODE        */
    .data                   : load > OCMC_IPU       /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss                      : load > OCMC_IPU       /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
    RUN_START(bss_start)
    RUN_END(bss_end)
    .const                  : load > OCMC_IPU       /*  GLOBAL CONSTANTS             */
    .cinit                  : load > OCMC_IPU
    .stack                  : load > OCMC_IPU       /*  SOFTWARE SYSTEM STACK        */
    .plt                    : load > OCMC_IPU
    .sysmem                 : load > OCMC_IPU
   .my_sect_ddr             : load > OCMC_IPU
   .OCMC_RESULT             : load > OCMC_RESULT
   .OCMC_TESTRESULT         : load >OCMC_TESTRESULT
   .OCMC_SYNC                : load > OCMC_SYNC
   .user_ocmc_data            : load > OCMC_GMAC_RX
}

