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


/** @file    DeviceInit.c
 *
 *  @brief     Implements the SoC Init for EDMA & TIMER in the Master framework
 *
 *  @author     Sandeep R
 *
 *  @date         07-03-2012
 *
 * <B> History: </B>
 *
 *      -# 03-07-2012   Sandeep R   Initial Version
 */
/** \include deviceInit.h
    \brief header file for DeviceInit.x
*/
#include "stdint.h"
#include "deviceInit.h"
/** \include GlobalTypes.h
    \brief header file for data type definitions
*/

/******************************************************************************\
 *       Functions Definitions
\******************************************************************************/
/* ------------------------------------------------------------------------*//**
 * @fn       deviceInit(
        void
)
 * @brief         SoC PRCM Init for EDMA & DMTIMER
 *
 * @param[in]     None
 *
 * @returns       None
 *
 * @details   This function is responsible for SoC PRCM Init for EDMA TPCC & all three TPTCs & DMTIMER3
 *
 *//*------------------------------------------------------------------------ */

void deviceInit(void) {

    /*! Enable Clocks for TPCC & TPTC*/
   EdmaPrcm();

   /*! Enable CPU Timer */
   CPU_timerInit();

   /*! Enable Clocks for DMTIMER */
   TIMER_PrcmEnable(3);
   TIMER_Init(3);
    /*! Enable DMTIMER */
   TIMER_Start(3);

}

/* ------------------------------------------------------------------------*//**
 * @fn       EdmaPrcm(
        void
)
 * @brief         SoC PRCM Init for EDMA
 *
 * @param[in]     None
 *
 * @returns       None
 *
 * @details   This function is responsible for SoC PRCM Init for EDMA TPCC & all three TPTCs
 *
 *//*------------------------------------------------------------------------ */

void EdmaPrcm(void) {
    HW_WR_REG32(0x4A008778,0x00000001);
    while((HW_RD_REG32(0x4A008778)&0x30000) !=0x0 ){}

    HW_WR_REG32(0x4A008780,0x00000001);
    while((HW_RD_REG32(0x4A008780)&0x30000) !=0x0 ){}
}
/* ------------------------------------------------------------------------*//**
 * @fn       EdmaPrcmDisable(
        void
)
 * @brief         SoC PRCM disable for EDMA
 *
 * @param[in]     None
 *
 * @returns       None
 *
 * @details   This function is responsible for SoC PRCM disable for EDMA TPCC & all three TPTCs
 *
 *//*------------------------------------------------------------------------ */
void EdmaPrcmDisable() {
    /*! Disable PRCM for TPCC */
  HW_WR_REG32(CM_ALWON_TPCC_CLKCTRL,0x00000000);
  while((HW_RD_REG32(CM_ALWON_TPCC_CLKCTRL)&0x00030000) != 0x00030000 ){}

    /*! Disable PRCM for TPTC0 */
  HW_WR_REG32(CM_ALWON_TPTC0_CLKCTRL,0x00000000);
  while((HW_RD_REG32(CM_ALWON_TPTC0_CLKCTRL)&0x00030000) != 0x00030000 ){}

    /*! Disable PRCM for TPCT1 */
  HW_WR_REG32(CM_ALWON_TPTC1_CLKCTRL,0x00000000);
  while((HW_RD_REG32(CM_ALWON_TPTC1_CLKCTRL)&0x00030000) != 0x00030000 ){}

    /*! Disable PRCM for TPTC2 */
  HW_WR_REG32(CM_ALWON_TPTC2_CLKCTRL,0x00000000);
  while((HW_RD_REG32(CM_ALWON_TPTC2_CLKCTRL)&0x00030000) != 0x00030000 ){}

}


/*********************************************************************************
 *  Timer Functions
*********************************************************************************/

void TIMER_PrcmEnable(uint32_t timerInst)
{
  switch(timerInst)
  {
    case 3:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER3_CLKCTRL_OFFSET, 0x2);
      break;
    case 4:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL_OFFSET, 0x2);
      break;
    case 9:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER9_CLKCTRL_OFFSET, 0x2);
      break;
    case 11:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER11_CLKCTRL_OFFSET, 0x2);
      break;
    case 13:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER3_TIMER13_CLKCTRL_OFFSET, 0x2);
      break;
    case 14:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER3_TIMER14_CLKCTRL_OFFSET, 0x2);
      break;
    case 15:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER3_TIMER15_CLKCTRL_OFFSET, 0x2);
      break;
    case 16:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER3_TIMER16_CLKCTRL_OFFSET, 0x2);
      break;
    default:
      HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER3_CLKCTRL_OFFSET, 0x2);
      break;
  }
}

void TIMER_Init(uint32_t timerInst)
{
  uint32_t timer_baseaddr = SOC_TIMER3_BASE;

  switch(timerInst)
  {
    case 3:
      timer_baseaddr = SOC_TIMER3_BASE;
      break;
    case 4:
      timer_baseaddr = SOC_TIMER4_BASE;
      break;
    case 9:
      timer_baseaddr = SOC_TIMER9_BASE;
      break;
    case 11:
      timer_baseaddr = SOC_TIMER11_BASE;
      break;
    case 13:
      timer_baseaddr = SOC_TIMER13_BASE;
      break;
    case 14:
      timer_baseaddr = SOC_TIMER14_BASE;
      break;
    case 15:
      timer_baseaddr = SOC_TIMER15_BASE;
      break;
    case 16:
      timer_baseaddr = SOC_TIMER16_BASE;
      break;
    default:
      break;
  }

  /*Reset the timer module */
  TIMERReset(timer_baseaddr);

  /* Enable free run in emulation mode */
  TIMEREmuModeConfigure(timer_baseaddr, TIMER_FREE);

  //TODO: need to remove Remove prescaling
  //TIMERPreScalerClkEnable(timer_baseaddr, TIMER_PRESCALER_CLK_DIV_BY_4);


  /* Load the counter with the initial count value */
  TIMERCounterSet(timer_baseaddr, TIMER_INITIAL_COUNT);

  /* Load the load register with the reload count value */
  TIMERReloadSet(timer_baseaddr, TIMER_RLD_COUNT);

  /* Configure the Timer for Auto-reload and compare mode */
  TIMERModeConfigure(timer_baseaddr, TIMER_AUTORLD_NOCMP_ENABLE);
#ifdef L3STATCOLL_TIMER_PERIODIC_DUMP
  /*Configure timer for compare match value(1ms)*/
  TIMERCompareSet(timer_baseaddr, 0x4E20);

  TIMERIntEnable(timer_baseaddr,TIMER_INT_MAT_EN_FLAG);

  Intc_Init();
  Intc_IntRegister(67,
                   (IntrFuncPtr)TESOC_IRQ_DONE_IntHandler,
                    (void *)0);
#endif
}

void TIMER_DeInit(uint32_t timerInst)
{

}

void TIMER_Start(uint32_t timerInst)
{
  uint32_t timer_baseaddr = SOC_TIMER3_BASE;

  switch(timerInst)
  {
    case 3:
      timer_baseaddr = SOC_TIMER3_BASE;
      break;
    case 4:
      timer_baseaddr = SOC_TIMER4_BASE;
      break;
    case 9:
      timer_baseaddr = SOC_TIMER9_BASE;
      break;
    case 11:
      timer_baseaddr = SOC_TIMER11_BASE;
      break;
    case 13:
      timer_baseaddr = SOC_TIMER13_BASE;
      break;
    case 14:
      timer_baseaddr = SOC_TIMER14_BASE;
      break;
    case 15:
      timer_baseaddr = SOC_TIMER15_BASE;
      break;
    case 16:
      timer_baseaddr = SOC_TIMER16_BASE;
      break;
    default:
      break;
  }

  /* Start the Timer */
  TIMEREnable(timer_baseaddr);
}

void TIMER_Stop(uint32_t timerInst)
{
  uint32_t timer_baseaddr = SOC_TIMER3_BASE;

  switch(timerInst)
  {
    case 3:
      timer_baseaddr = SOC_TIMER3_BASE;
      break;
    case 4:
      timer_baseaddr = SOC_TIMER4_BASE;
      break;
    case 9:
      timer_baseaddr = SOC_TIMER9_BASE;
      break;
    case 11:
      timer_baseaddr = SOC_TIMER11_BASE;
      break;
    case 13:
      timer_baseaddr = SOC_TIMER13_BASE;
      break;
    case 14:
      timer_baseaddr = SOC_TIMER14_BASE;
      break;
    case 15:
      timer_baseaddr = SOC_TIMER15_BASE;
      break;
    case 16:
      timer_baseaddr = SOC_TIMER16_BASE;
      break;
    default:
      break;
  }

  /* Stop the Timer */
  TIMERDisable(timer_baseaddr);
}

uint32_t TIMER_Read(uint32_t timerInst)
{
  uint32_t timer_baseaddr = SOC_TIMER3_BASE;
  uint32_t retVal;

  switch(timerInst)
  {
    case 3:
      timer_baseaddr = SOC_TIMER3_BASE;
      break;
    case 4:
      timer_baseaddr = SOC_TIMER4_BASE;
      break;
    case 9:
      timer_baseaddr = SOC_TIMER9_BASE;
      break;
    case 11:
      timer_baseaddr = SOC_TIMER11_BASE;
      break;
    case 13:
      timer_baseaddr = SOC_TIMER13_BASE;
      break;
    case 14:
      timer_baseaddr = SOC_TIMER14_BASE;
      break;
    case 15:
      timer_baseaddr = SOC_TIMER15_BASE;
      break;
    case 16:
      timer_baseaddr = SOC_TIMER16_BASE;
      break;
    default:
      break;
  }

  /* Read Timer value */
  retVal = TIMERCounterGet(timer_baseaddr);
  return retVal;
}

uint32_t timerRead(uint32_t timerInst)
{
   return TIMER_Read(timerInst);
}
#ifdef ALO_SYSTEM_EDMA_
/*************************************************/
/*          System MMU Config                */
/*************************************************/
#define PHY_ADDR1  0x80000000
#define VIRT_ADDR1 0x80000000
#define PHY_ADDR2  0x81000000
#define VIRT_ADDR2 0x81000000
#define PHY_ADDR3  0x82000000
#define VIRT_ADDR3 0x82000000
#define PHY_ADDR4  0x83000000
#define VIRT_ADDR4 0x83000000
#define PHY_ADDR5  0x84000000
#define VIRT_ADDR5 0x84000000
#define PHY_ADDR6  0x85000000
#define VIRT_ADDR6 0x85000000
#define PHY_ADDR7  0x86000000
#define VIRT_ADDR7 0x86000000
#define PHY_ADDR8  0x40300000
#define VIRT_ADDR8 0x40300000

void SYSTEM_MMU0_config()
{
   MMU_TlbEntry_t  mmu_entry;
   volatile unsigned int rVal, bits ;
   uint32_t val=0;

      /* Configure MMU Tlb Entry for DDR code section  */
      mmu_entry.phyAddr         = PHY_ADDR1;
      mmu_entry.virtAddr        = VIRT_ADDR1;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size; /* 64 KB */
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 1,
            &mmu_entry );


           /* Configure MMU Tlb Entry for DDR Data  */
      mmu_entry.phyAddr         = PHY_ADDR2;
      mmu_entry.virtAddr        = VIRT_ADDR2;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size; /* 16 MB */
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 2,
            &mmu_entry );

      /* Configure MMU Tlb Entry for test_done  */
      mmu_entry.phyAddr         = PHY_ADDR3;
      mmu_entry.virtAddr        = VIRT_ADDR3;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size;
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 3,
            &mmu_entry );

      /* Configure MMU Tlb Entry for ocmc ram  */
      mmu_entry.phyAddr         = PHY_ADDR4;
      mmu_entry.virtAddr        = VIRT_ADDR4;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size;
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 4,
            &mmu_entry );

      /* Configure MMU Tlb Entry for gem1 l2  */
      mmu_entry.phyAddr         = PHY_ADDR5;
      mmu_entry.virtAddr        = VIRT_ADDR5;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size;
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 5,
            &mmu_entry );

      /* Configure MMU Tlb Entry for ocmc ram  */
      mmu_entry.phyAddr         = PHY_ADDR6;
      mmu_entry.virtAddr        = VIRT_ADDR6;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size;
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 6,
            &mmu_entry );

      /* Configure MMU Tlb Entry for ocmc ram  */
      mmu_entry.phyAddr         = PHY_ADDR7;
      mmu_entry.virtAddr        = VIRT_ADDR7;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size;
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 7,
            &mmu_entry );

      /* Configure MMU Tlb Entry for ocmc ram  */
      /* Configure MMU Tlb Entry for DDR Data  */
      mmu_entry.phyAddr         = PHY_ADDR8;
      mmu_entry.virtAddr        = VIRT_ADDR8;
      mmu_entry.valid           = TRUE;
      mmu_entry.pageSize        = MMU_SuperSection_Size;
      mmu_entry.endianness      = MMU_Little_Endian;
      mmu_entry.elementSize     = MMU_NoTranslation_ElementSize;
      mmu_entry.tlbElementSize  = MMU_CPU_ElementSize;
      mmu_entry.preserve        = TRUE;

      MMU_SetTlbEntry( 8,
            &mmu_entry );

      /* Enable MMU */
      HW_WR_REG32(SYSTEM_MMU_CNTL, ((HW_RD_REG32(SYSTEM_MMU_CNTL)) & 0xFFFFFFFD) | 0x2);


      // Enable path through MMU
      val = HW_RD_REG32(0x4A003C18);
      val|= 0x00F00;
      HW_WR_REG32(0x4A003C18, val);
}
#endif
void CPU_timerInit()
{
   /* Set Reload Value */
   HW_WR_REG32(0xE000E014, 0x00FFFFFE);

   /* Clear Current Value */
   HW_WR_REG32(0xE000E018, 0x00FFFFFE);

   /* Program Control and Status Register */
   HW_WR_REG32(0xE000E010, 0x00000005);


}

uint32_t CPU_timerRead()
{
   return HW_RD_REG32(0xE000E018);
}

/*! EOF */
