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


/** @file    DeviceInit.h
 *
 *  @brief     header file for DeviceInit.c
 *
 *  @author     Sandeep R
 *
 *  @date         07-03-2012
 *
 * <B> History: </B>
 *
 *      -# 03-07-2012   Sandeep R   Initial Version
 */
#include "timer.h"
#include "hw_timer.h"

/*! \def NUM_OF_TIMER
    \brief macro to Specify the Peripheral Timer Instances available in Vayu
*/
#define NUM_OF_TIMER 16
/*! \def AEGIS
    \brief macro to enable AEGIS; always enabled
*/
#define VAYU

#ifdef VAYU
#define PRCM_BASE_ADDR         0x48243000
#define SOC_EDMA_TPCC_BASE              0x43300000
#define SOC_EDMA_TC0_BASE               0x43400000
#define SOC_EDMA_TC1_BASE               0x43500000
#define CM_ALWON_TPCC_CLKCTRL   (PRCM_BASE_ADDR+0x8878)
#define CM_ALWON_TPTC0_CLKCTRL   (PRCM_BASE_ADDR+0x8880)
#define CM_ALWON_TPTC1_CLKCTRL   (PRCM_BASE_ADDR+0x8888)
#define CM_ALWON_TPTC2_CLKCTRL   (PRCM_BASE_ADDR+0x8890)
#endif


/* TIMER Register addresses  */
#define SOC_L4PER_CM_CORE_BASE                  0x4a009700

#define CM_L4PER_TIMER3_CLKCTRL_OFFSET            (0x40U)
#define CM_L4PER_TIMER4_CLKCTRL_OFFSET            (0x48U)
#define CM_L4PER_TIMER9_CLKCTRL_OFFSET            (0x50U)
#define CM_L4PER_TIMER11_CLKCTRL_OFFSET            (0x30U)
#define CM_L4PER3_TIMER13_CLKCTRL_OFFSET         (0xc8U)
#define CM_L4PER3_TIMER14_CLKCTRL_OFFSET         (0xd0U)
#define CM_L4PER3_TIMER15_CLKCTRL_OFFSET         (0xd8U)
#define CM_L4PER3_TIMER16_CLKCTRL_OFFSET         (0x130U)

#define SOC_TIMER3_BASE                        0x48034000
#define SOC_TIMER4_BASE                        0x48036000
#define SOC_TIMER9_BASE                        0x4803e000
#define SOC_TIMER11_BASE                     0x48088000
#define SOC_TIMER13_BASE                     0x48828000
#define SOC_TIMER14_BASE                     0x4882a000
#define SOC_TIMER15_BASE                     0x4882c000
#define SOC_TIMER16_BASE                     0x4882e000

#define TIMER_INITIAL_COUNT                      (0x00000000u)      // Initial value of Timer
#define TIMER_RLD_COUNT                            (0x00000000u)      // Reload value of Timer

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

void deviceInit(void) ;

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

void EdmaPrcm(void);

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
void EdmaPrcmDisable() ;



/*TIMER Functions */
void TIMER_PrcmEnable(uint32_t timerInst);
void TIMER_Init(uint32_t timerInst);
void TIMER_DeInit(uint32_t timerInst);
void TIMER_Start(uint32_t timerInst);
void TIMER_Stop(uint32_t timerInst);
uint32_t TIMER_Read(uint32_t timerInst);

void CPU_timerInit();
uint32_t CPU_timerRead();

#ifdef ALO_SYSTEM_EDMA
void   SYSTEM_MMU0_config();
#endif

/*! EOF */
