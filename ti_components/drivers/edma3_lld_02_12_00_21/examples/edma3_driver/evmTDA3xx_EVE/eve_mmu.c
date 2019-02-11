/*
 * eve_mmu.c
 *
 * This file contains the test / demo code to demonstrate the EDMA3 driver
 * functionality on DSP/BIOS 6.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
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

/******************************************************************************
*                             Macro Declarations                              *
******************************************************************************/
#define WR_MEM_32(addr, data)    *(unsigned int*)(addr) =(unsigned int)(data)
#define RD_MEM_32(addr)          *(unsigned int*)(addr)

#define MMU_BASE 0x40081000 /* EVE's view */
/* #define MMU_BASE 0x42081000 */   /* MPU's view */
#define TESLASS_MMU__MMU_CNTL    ( MMU_BASE + 0x44 )
#define TESLASS_MMU__MMU_CAM     ( MMU_BASE + 0x58 )
#define TESLASS_MMU__MMU_RAM     ( MMU_BASE + 0x5c )
#define TESLASS_MMU__MMU_LOCK    ( MMU_BASE + 0x50 )
#define TESLASS_MMU__MMU_LD_TLB  ( MMU_BASE + 0x54 )

#define PHY_ADDR1   0x4A000000
#define VIRT_ADDR1  0x4A000000

/*
 * eve1MmuConfig() This function does EVE MMU settings. This function is
 * called from Reset Module which is defined in configuration file.
 */
void eveMmuConfig(void)
{
    /* ------------------------------------------------------------------------------------------------------- */
    WR_MEM_32(TESLASS_MMU__MMU_CAM, 0x0000000c | (VIRT_ADDR1 & 0xFFFFE000));
    WR_MEM_32(TESLASS_MMU__MMU_RAM, 0x000001c0 | (PHY_ADDR1  & 0xFFFFE000));

    /* tlbEntry is bits 8:4
    #define TESLASS_MMU__MMU_LOCK__CURRENTVICTIM          BITFIELD(8, 4) */
    WR_MEM_32(TESLASS_MMU__MMU_LOCK, ((RD_MEM_32(TESLASS_MMU__MMU_LOCK)) & 0xFFFFFE0F) | ( 11 << 4 ));
    WR_MEM_32(TESLASS_MMU__MMU_LD_TLB, 1 );
    /* ------------------------------------------------------------------------------------------------------- */

    /*Enable MMU*/
    WR_MEM_32(TESLASS_MMU__MMU_CNTL, ((RD_MEM_32(TESLASS_MMU__MMU_CNTL)) & 0xFFFFFFFD) | 0x2);
}
