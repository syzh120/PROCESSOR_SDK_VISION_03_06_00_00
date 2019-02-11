/*
 *  @file  MMUAccInt.h
 *
 *  @brief  MMU Register access Macros
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

#ifndef _MMU_REG_ACM_H
#define _MMU_REG_ACM_H



#include <GlobalTypes.h>
#include <MMUAccInt.h>


/*
* EXPORTED DEFINITIONS
*
*/

#define MMUMMU_SYSCONFIGReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_SYSCONFIG_OFFSET))


#define MMUMMU_SYSCONFIGWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_SYSCONFIG_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}

#define MMUMMU_SYSCONFIGClockActivityGet32(var)\
    ((UInt32)(((var) & MMU_MMU_SYSCONFIG_ClockActivity_MASK)\
    >> MMU_MMU_SYSCONFIG_ClockActivity_OFFSET))

#define mmu_sisconf_auto_idle_set32(var, value)\
    ((((var) & ~(MMU_MMU_SYSCONFIG_AutoIdle_MASK)) |\
    (((value) << MMU_MMU_SYSCONFIG_AutoIdle_OFFSET) &\
    MMU_MMU_SYSCONFIG_AutoIdle_MASK)))

#define MMUMMU_IRQSTATUSReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_IRQSTATUS_OFFSET))


#define MMUMMU_IRQSTATUSWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_IRQSTATUS_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}


#define MMUMMU_IRQENABLEReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_IRQENABLE_OFFSET))


#define MMUMMU_IRQENABLEWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_IRQENABLE_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}

#define MMUMMU_IRQENABLETableWalkFaultSet32(var, value)\
    ((((var) & ~(MMU_MMU_IRQENABLE_TableWalkFault_MASK)) |\
    (((value) << MMU_MMU_IRQENABLE_TableWalkFault_OFFSET) &\
    MMU_MMU_IRQENABLE_TableWalkFault_MASK)))

#define MMUMMU_IRQENABLETranslationFaultRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_IRQENABLE_OFFSET)))) &\
    MMU_MMU_IRQENABLE_TranslationFault_MASK) >>\
    MMU_MMU_IRQENABLE_TranslationFault_OFFSET))



#define MMUMMU_IRQENABLETranslationFaultSet32(var, value)\
    ((((var) & ~(MMU_MMU_IRQENABLE_TranslationFault_MASK)) |\
    (((value) << MMU_MMU_IRQENABLE_TranslationFault_OFFSET) &\
    MMU_MMU_IRQENABLE_TranslationFault_MASK)))


#define MMUMMU_IRQENABLETLBMissRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_IRQENABLE_OFFSET)))) &\
    MMU_MMU_IRQENABLE_TLBMiss_MASK) >>\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET))


#define MMUMMU_IRQENABLETLBMissReadIsTrMissIntM32(base_address)\
    ((MMUMMU_IRQENABLETLBMissTrMissIntM == (MMUMMU_IRQENABLETLBMissE)\
    (((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_IRQENABLE_OFFSET)))) &\
    MMU_MMU_IRQENABLE_TLBMiss_MASK) >>\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET)))


#define MMUMMU_IRQENABLETLBMissReadIsTrMissGInt32(base_address)\
    ((MMUMMU_IRQENABLETLBMissTrMissGInt == (MMUMMU_IRQENABLETLBMissE)\
    (((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_IRQENABLE_OFFSET)))) &\
    MMU_MMU_IRQENABLE_TLBMiss_MASK) >>\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET)))


#define MMUMMU_IRQENABLETLBMissGet32(var)\
    ((UInt32)(((var) & MMU_MMU_IRQENABLE_TLBMiss_MASK)\
    >> MMU_MMU_IRQENABLE_TLBMiss_OFFSET))


#define MMUMMU_IRQENABLETLBMissIsTrMissIntM32(var)\
    ((MMUMMU_IRQENABLETLBMissTrMissIntM == \
    (MMUMMU_IRQENABLETLBMissE)(((var) & MMU_MMU_IRQENABLE_TLBMiss_MASK) >>\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET)))

#define MMUMMU_IRQENABLETLBMissIsTrMissGInt32(var)\
    ((MMUMMU_IRQENABLETLBMissTrMissGInt ==\
    (MMUMMU_IRQENABLETLBMissE)(((var) & MMU_MMU_IRQENABLE_TLBMiss_MASK) >>\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET)))

#define MMUMMU_IRQENABLETLBMissWrite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_IRQENABLE_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_IRQENABLE_TLBMiss_MASK);\
    newValue <<= MMU_MMU_IRQENABLE_TLBMiss_OFFSET;\
    newValue &= MMU_MMU_IRQENABLE_TLBMiss_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}


#define MMUMMU_IRQENABLETLBMissWriteTrMissIntM32(base_address)\
{\
    const UInt32 offset = MMU_MMU_IRQENABLE_OFFSET;\
    const UInt32 newValue = (UInt32)MMUMMU_IRQENABLETLBMissTrMissIntM <<\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE(base_address+offset);\
    data &= ~(MMU_MMU_IRQENABLE_TLBMiss_MASK);\
        data |= newValue;\
    WR_MEM_32_VOLATILE(base_address+offset, data);\
}


#define MMUMMU_IRQENABLETLBMissWriteTrMissGInt32(base_address)\
{\
    const UInt32 offset = MMU_MMU_IRQENABLE_OFFSET;\
    const UInt32 newValue = (UInt32)MMUMMU_IRQENABLETLBMissTrMissGInt <<\
    MMU_MMU_IRQENABLE_TLBMiss_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE(base_address+offset);\
    data &= ~(MMU_MMU_IRQENABLE_TLBMiss_MASK);\
    data |= newValue;\
    WR_MEM_32_VOLATILE(base_address+offset, data);\
}


#define MMUMMU_IRQENABLETLBMissSet32(var, value)\
    ((((var) & ~(MMU_MMU_IRQENABLE_TLBMiss_MASK)) |\
    (((value) << MMU_MMU_IRQENABLE_TLBMiss_OFFSET) &\
    MMU_MMU_IRQENABLE_TLBMiss_MASK)))


#define MMUMMU_WALKING_STTWLRunningRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_WALKING_ST_OFFSET)))) &\
    MMU_MMU_WALKING_ST_TWLRunning_MASK) >>\
    MMU_MMU_WALKING_ST_TWLRunning_OFFSET))



#define MMUMMU_CNTLTWLEnableRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_CNTL_OFFSET)))) &\
    MMU_MMU_CNTL_TWLEnable_MASK) >>\
    MMU_MMU_CNTL_TWLEnable_OFFSET))


#define MMUMMU_CNTLTWLEnableWrite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_CNTL_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_CNTL_TWLEnable_MASK);\
    newValue <<= MMU_MMU_CNTL_TWLEnable_OFFSET;\
    newValue &= MMU_MMU_CNTL_TWLEnable_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}


#define MMUMMU_CNTLMMUEnableWrite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_CNTL_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_CNTL_MMUEnable_MASK);\
    newValue <<= MMU_MMU_CNTL_MMUEnable_OFFSET;\
    newValue &= MMU_MMU_CNTL_MMUEnable_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}


#define MMUMMU_FAULT_ADReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_FAULT_AD_OFFSET))


#define MMUMMU_FAULT_ADFaultAddressRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_FAULT_AD_OFFSET)))) &\
    MMU_MMU_FAULT_AD_FaultAddress_MASK) >>\
    MMU_MMU_FAULT_AD_FaultAddress_OFFSET))

#define MMUMMU_FAULT_ADFaultAddressGet32(var)\
    ((UInt32)(((var) & MMU_MMU_FAULT_AD_FaultAddress_MASK)\
    >> MMU_MMU_FAULT_AD_FaultAddress_OFFSET))


#define MMUMMU_TTBReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_TTB_OFFSET))

#define MMUMMU_TTBWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_TTB_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}

#define MMUMMU_TTBTTBAddressRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_TTB_OFFSET)))) &\
    MMU_MMU_TTB_TTBAddress_MASK) >>\
    MMU_MMU_TTB_TTBAddress_OFFSET))

#define MMUMMU_TTBTTBAddressGet32(var)\
    ((UInt32)(((var) & MMU_MMU_TTB_TTBAddress_MASK)\
    >> MMU_MMU_TTB_TTBAddress_OFFSET))


#define MMUMMU_TTBTTBAddressWrite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_TTB_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_TTB_TTBAddress_MASK);\
    newValue <<= MMU_MMU_TTB_TTBAddress_OFFSET;\
    newValue &= MMU_MMU_TTB_TTBAddress_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}

#define MMUMMU_TTBTTBAddressSet32(var, value)\
    ((((var) & ~(MMU_MMU_TTB_TTBAddress_MASK)) |\
    (((value) << MMU_MMU_TTB_TTBAddress_OFFSET) &\
    MMU_MMU_TTB_TTBAddress_MASK)))


#define mmu_lckread_reg_32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_LOCK_OFFSET))

#define mmu_lck_write_reg32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_LOCK_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}


#define MMUMMU_LOCKBaseValueRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_LOCK_OFFSET)))) &\
    MMU_MMU_LOCK_BaseValue_MASK) >>\
    MMU_MMU_LOCK_BaseValue_OFFSET))
#define MMUMMU_LOCKBaseValueGet32(var)\
    ((UInt32)(((var) & MMU_MMU_LOCK_BaseValue_MASK)\
    >> MMU_MMU_LOCK_BaseValue_OFFSET))


#define MMUMMU_LOCKBaseValueWrite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_LOCK_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_LOCK_BaseValue_MASK);\
    newValue <<= MMU_MMU_LOCK_BaseValue_OFFSET;\
    newValue &= MMU_MMU_LOCK_BaseValue_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}


#define MMUMMU_LOCKBaseValueSet32(var, value)\
    ((((var) & ~(MMU_MMU_LOCK_BaseValue_MASK)) |\
    (((value) << MMU_MMU_LOCK_BaseValue_OFFSET) &\
    MMU_MMU_LOCK_BaseValue_MASK)))

#define MMUMMU_LOCKCurrentVictimRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_LOCK_OFFSET)))) &\
    MMU_MMU_LOCK_CurrentVictim_MASK) >>\
    MMU_MMU_LOCK_CurrentVictim_OFFSET))


#define MMUMMU_LOCKCurrentVictimGet32(var)\
    ((UInt32)(((var) & MMU_MMU_LOCK_CurrentVictim_MASK)\
    >> MMU_MMU_LOCK_CurrentVictim_OFFSET))


#define mmu_lck_crnt_vctmwite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_LOCK_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_LOCK_CurrentVictim_MASK);\
    newValue <<= MMU_MMU_LOCK_CurrentVictim_OFFSET;\
    newValue &= MMU_MMU_LOCK_CurrentVictim_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}


#define MMUMMU_LOCKCurrentVictimSet32(var, value)\
    ((((var) & ~(MMU_MMU_LOCK_CurrentVictim_MASK)) |\
    (((value) << MMU_MMU_LOCK_CurrentVictim_OFFSET) &\
    MMU_MMU_LOCK_CurrentVictim_MASK)))


#define MMUMMU_LD_TLBReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_LD_TLB_OFFSET))

#define mmu_ld_tlbwrt_reg32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_LD_TLB_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}

#define MMUMMU_LD_TLBLdTLBItemRead32(base_address)\
    ((((RD_MEM_32_VOLATILE(((base_address)+(MMU_MMU_LD_TLB_OFFSET)))) &\
    MMU_MMU_LD_TLB_LdTLBItem_MASK) >>\
    MMU_MMU_LD_TLB_LdTLBItem_OFFSET))


#define MMUMMU_CAMReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_READ_CAM_OFFSET))


#define MMUMMU_CAMWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_CAM_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}

#define MMUMMU_RAMReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_READ_RAM_OFFSET))


#define MMUMMU_RAMWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_RAM_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}

#define MMUMMU_GFLUSHGlobalFlushWrite32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_GFLUSH_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE((base_address)+offset);\
    register UInt32 newValue = (value);\
    data &= ~(MMU_MMU_GFLUSH_GlobalFlush_MASK);\
    newValue <<= MMU_MMU_GFLUSH_GlobalFlush_OFFSET;\
    newValue &= MMU_MMU_GFLUSH_GlobalFlush_MASK;\
    newValue |= data;\
    WR_MEM_32_VOLATILE(base_address+offset, newValue);\
}

#define MMUMMU_GFLUSHGlobalFlushWritenft_w32(base_address)\
{\
        const UInt32 offset = MMU_MMU_GFLUSH_OFFSET;\
    const UInt32 newValue = (UInt32)MMUMMU_GFLUSHGlobalFlushnft_w <<\
    MMU_MMU_GFLUSH_GlobalFlush_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE(base_address+offset);\
    data &= ~(MMU_MMU_GFLUSH_GlobalFlush_MASK);\
    data |= newValue;\
    WR_MEM_32_VOLATILE(base_address+offset, data);\
}

#define MMUMMU_GFLUSHGlobalFlushWriteflush_w32(base_address)\
{\
    const UInt32 offset = MMU_MMU_GFLUSH_OFFSET;\
    const UInt32 newValue = (UInt32)MMUMMU_GFLUSHGlobalFlushflush_w <<\
    MMU_MMU_GFLUSH_GlobalFlush_OFFSET;\
    register UInt32 data = RD_MEM_32_VOLATILE(base_address+offset);\
    data &= ~(MMU_MMU_GFLUSH_GlobalFlush_MASK);\
    data |= newValue;\
    WR_MEM_32_VOLATILE(base_address+offset, data);\
}


#define MMUMMU_GFLUSHGlobalFlushSet32(var, value)\
    ((((var) & ~(MMU_MMU_GFLUSH_GlobalFlush_MASK)) |\
    (((value) << MMU_MMU_GFLUSH_GlobalFlush_OFFSET) &\
    MMU_MMU_GFLUSH_GlobalFlush_MASK)))

#define MMUMMU_FLUSH_ENTRYReadRegister32(base_address)\
    (RD_MEM_32_VOLATILE((base_address)+MMU_MMU_FLUSH_ENTRY_OFFSET))


#define MMUMMU_FLUSH_ENTRYWriteRegister32(base_address, value)\
{\
    const UInt32 offset = MMU_MMU_FLUSH_ENTRY_OFFSET;\
    register UInt32 newValue = (value);\
    WR_MEM_32_VOLATILE((base_address)+offset, newValue);\
}




#endif /* _MMU_REG_ACM_H */
/* EOF */

