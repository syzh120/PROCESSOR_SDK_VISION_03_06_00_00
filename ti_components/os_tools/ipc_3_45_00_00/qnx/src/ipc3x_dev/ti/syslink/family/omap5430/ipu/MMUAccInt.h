/*
 *  @file  MMUAccInt.h
 *
 *  @brief  MMU Register offset definitions
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2011, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */


#ifndef _MMU_ACC_INT_H
#define _MMU_ACC_INT_H


/* Register offset address definitions */

#define MMU_MMU_REVISION_OFFSET 0x0
#define MMU_MMU_SYSCONFIG_OFFSET 0x10
#define MMU_MMU_SYSSTATUS_OFFSET 014
#define MMU_MMU_IRQSTATUS_OFFSET 0x18
#define MMU_MMU_IRQENABLE_OFFSET 0x1c
#define MMU_MMU_WALKING_ST_OFFSET 0x40
#define MMU_MMU_CNTL_OFFSET     0x44
#define MMU_MMU_FAULT_AD_OFFSET 0x48
#define MMU_MMU_TTB_OFFSET      0x4c
#define MMU_MMU_LOCK_OFFSET     0x50
#define MMU_MMU_LD_TLB_OFFSET   0x54
#define MMU_MMU_CAM_OFFSET      0x58
#define MMU_MMU_RAM_OFFSET      0x5c
#define MMU_MMU_GFLUSH_OFFSET   0x60
#define MMU_MMU_FLUSH_ENTRY_OFFSET 0x64
#define MMU_MMU_READ_CAM_OFFSET    0x68
#define MMU_MMU_READ_RAM_OFFSET    0x6c
#define MMU_MMU_EMU_FAULT_AD_OFFSET    0x70


/* Bitfield mask and offset declarations */

#define MMU_MMU_REVISION_Rev_MASK    0xff
#define MMU_MMU_REVISION_Rev_OFFSET    0

#define MMU_MMU_SYSCONFIG_ClockActivity_MASK    0x300
#define MMU_MMU_SYSCONFIG_ClockActivity_OFFSET    8

#define MMU_MMU_SYSCONFIG_IdleMode_MASK    0x18
#define MMU_MMU_SYSCONFIG_IdleMode_OFFSET    3

#define MMU_MMU_SYSCONFIG_SoftReset_MASK    0x2
#define MMU_MMU_SYSCONFIG_SoftReset_OFFSET    1

#define MMU_MMU_SYSCONFIG_AutoIdle_MASK    0x1
#define MMU_MMU_SYSCONFIG_AutoIdle_OFFSET    0

#define MMU_MMU_SYSSTATUS_ResetDone_MASK    0x1
#define MMU_MMU_SYSSTATUS_ResetDone_OFFSET    0

#define MMU_MMU_IRQSTATUS_MultiHitFault_MASK    0x10
#define MMU_MMU_IRQSTATUS_MultiHitFault_OFFSET    4

#define MMU_MMU_IRQSTATUS_TableWalkFault_MASK    0x8
#define MMU_MMU_IRQSTATUS_TableWalkFault_OFFSET    3

#define MMU_MMU_IRQSTATUS_EMUMiss_MASK    0x4
#define MMU_MMU_IRQSTATUS_EMUMiss_OFFSET    2

#define MMU_MMU_IRQSTATUS_TranslationFault_MASK    0x2
#define MMU_MMU_IRQSTATUS_TranslationFault_OFFSET    1

#define MMU_MMU_IRQSTATUS_TLBMiss_MASK    0x1
#define MMU_MMU_IRQSTATUS_TLBMiss_OFFSET    0

#define MMU_MMU_IRQENABLE_MultiHitFault_MASK    0x10
#define MMU_MMU_IRQENABLE_MultiHitFault_OFFSET    4

#define MMU_MMU_IRQENABLE_TableWalkFault_MASK    0x8
#define MMU_MMU_IRQENABLE_TableWalkFault_OFFSET    3

#define MMU_MMU_IRQENABLE_EMUMiss_MASK    0x4
#define MMU_MMU_IRQENABLE_EMUMiss_OFFSET    2

#define MMU_MMU_IRQENABLE_TranslationFault_MASK    0x2
#define MMU_MMU_IRQENABLE_TranslationFault_OFFSET    1

#define MMU_MMU_IRQENABLE_TLBMiss_MASK    0x1
#define MMU_MMU_IRQENABLE_TLBMiss_OFFSET    0

#define MMU_MMU_WALKING_ST_TWLRunning_MASK    0x1
#define MMU_MMU_WALKING_ST_TWLRunning_OFFSET    0

#define MMU_MMU_CNTL_EmuTLBUpdate_MASK    0x8
#define MMU_MMU_CNTL_EmuTLBUpdate_OFFSET    3

#define MMU_MMU_CNTL_TWLEnable_MASK    0x4
#define MMU_MMU_CNTL_TWLEnable_OFFSET    2

#define MMU_MMU_CNTL_MMUEnable_MASK    0x2
#define MMU_MMU_CNTL_MMUEnable_OFFSET    1

#define MMU_MMU_FAULT_AD_FaultAddress_MASK    0xffffffff
#define MMU_MMU_FAULT_AD_FaultAddress_OFFSET    0

#define MMU_MMU_TTB_TTBAddress_MASK    0xffffff00
#define MMU_MMU_TTB_TTBAddress_OFFSET    8

#define MMU_MMU_LOCK_BaseValue_MASK    0xfc00
#define MMU_MMU_LOCK_BaseValue_OFFSET    10

#define MMU_MMU_LOCK_CurrentVictim_MASK    0x3f0
#define MMU_MMU_LOCK_CurrentVictim_OFFSET    4

#define MMU_MMU_LD_TLB_LdTLBItem_MASK    0x1
#define MMU_MMU_LD_TLB_LdTLBItem_OFFSET    0

#define MMU_MMU_CAM_VATag_MASK    0xfffff000
#define MMU_MMU_CAM_VATag_OFFSET    12

#define MMU_MMU_CAM_P_MASK    0x8
#define MMU_MMU_CAM_P_OFFSET    3

#define MMU_MMU_CAM_V_MASK    0x4
#define MMU_MMU_CAM_V_OFFSET    2

#define MMU_MMU_CAM_PageSize_MASK    0x3
#define MMU_MMU_CAM_PageSize_OFFSET    0

#define MMU_MMU_RAM_PhysicalAddress_MASK    0xfffff000
#define MMU_MMU_RAM_PhysicalAddress_OFFSET    12

#define MMU_MMU_RAM_Endianness_MASK    0x200
#define MMU_MMU_RAM_Endianness_OFFSET    9

#define MMU_MMU_RAM_ElementSize_MASK    0x180
#define MMU_MMU_RAM_ElementSize_OFFSET    7

#define MMU_MMU_RAM_Mixed_MASK    0x40
#define MMU_MMU_RAM_Mixed_OFFSET    6

#define MMU_MMU_GFLUSH_GlobalFlush_MASK    0x1
#define MMU_MMU_GFLUSH_GlobalFlush_OFFSET    0

#define MMU_MMU_FLUSH_ENTRY_FlushEntry_MASK    0x1
#define MMU_MMU_FLUSH_ENTRY_FlushEntry_OFFSET    0

#define MMU_MMU_READ_CAM_VATag_MASK    0xfffff000
#define MMU_MMU_READ_CAM_VATag_OFFSET    12

#define MMU_MMU_READ_CAM_P_MASK    0x8
#define MMU_MMU_READ_CAM_P_OFFSET    3

#define MMU_MMU_READ_CAM_V_MASK    0x4
#define MMU_MMU_READ_CAM_V_OFFSET    2

#define MMU_MMU_READ_CAM_PageSize_MASK    0x3
#define MMU_MMU_READ_CAM_PageSize_OFFSET    0

#define MMU_MMU_READ_RAM_PhysicalAddress_MASK    0xfffff000
#define MMU_MMU_READ_RAM_PhysicalAddress_OFFSET    12

#define MMU_MMU_READ_RAM_Endianness_MASK    0x200
#define MMU_MMU_READ_RAM_Endianness_OFFSET    9

#define MMU_MMU_READ_RAM_ElementSize_MASK    0x180
#define MMU_MMU_READ_RAM_ElementSize_OFFSET    7

#define MMU_MMU_READ_RAM_Mixed_MASK    0x40
#define MMU_MMU_READ_RAM_Mixed_OFFSET    6

#define MMU_MMU_EMU_FAULT_AD_EmuFaultAddress_MASK    0xffffffff
#define MMU_MMU_EMU_FAULT_AD_EmuFaultAddress_OFFSET    0

#endif /* _MMU_ACC_INT_H */
/* EOF */

