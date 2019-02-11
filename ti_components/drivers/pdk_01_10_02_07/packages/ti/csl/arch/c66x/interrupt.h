/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup CSL_ARCH_C66X
 *  \defgroup CSL_ARCH_C66X_INTERRUPT Interrupt
 *
 *  @{
 */
/**
 *  \file  c66x/interrupt.h
 *
 *  \brief This file contains the API prototypes for configuring INTC for
 *         DSP
 */
#ifndef INTERRUPT_H
#define INTERRUPT_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define C64

#define INTH_INT_ID_EVT0                (0U)
#define INTH_INT_ID_EVT1                (1U)
#define INTH_INT_ID_EVT2                (2U)
#define INTH_INT_ID_EVT3                (3U)

#define INTH_INT_ID_EMU_DTDMA           9

#define INTH_INT_ID_EMU_RDTXRX          11
#define INTH_INT_ID_EMU_RDTXTX          12
#define INTH_INT_ID_IDMAINT0            13
#define INTH_INT_ID_IDMAINT1            14
#define INTH_INT_ID_SDINT0              15          /* IRQOQN */
#define INTH_INT_ID_SPIINT0             16          /* SINTERRUPTN */
#define INTH_INT_ID_VCPINT              17          /* vcp_int */
#define INTH_INT_ID_ELM_IRQ             18          /* ELM_IRQ */
#define INTH_INT_ID_ELM                 18          /* ELM_IRQ */
#define INTH_INT_ID_IDEINTR             19          /* PATA ide_int */
#define INTH_INT_ID_EDMACOMPINT         20          /* tpcc_int_pend_n[0] */
#define INTH_INT_ID_EDMAERRINT          21          /* tpcc_errint_pend_n */
#define INTH_INT_ID_TCERRINT0           22          /* tptc_errint_pend_n */
#define INTH_INT_ID_ISS_IRQ4            23          /* iss_irq[4] */
#define INTH_INT_ID_TPPMBOXINT          24          /*
                                                     *
                                                     * TPPSS_MAIL_U0_INTR_PEND_N
                                                     */
#define INTH_INT_ID_TPPDMAPKT           25          /*
                                                     *
                                                     * TPPSS_DMAPC0_INTR_PEND_N
                                                     */
#define INTH_INT_ID_TPPDMABS            26          /*
                                                     *
                                                     * TPPSS_DMABS0_INTR_PEND_N
                                                     */
#define HOST_TPPSS_DMABS0_INTRNUM       26          /*
                                                     *
                                                     * TPPSS_DMABS0_INTR_PEND_N
                                                     */
#define INTH_INT_ID_TCERRINT1           27          /* tptc_lerrint_po */
#define INTH_INT_ID_TCERRINT2           28          /* tptc_lerrint_po */
#define INTH_INT_ID_TCERRINT3           29          /* tptc_lerrint_po */
#define INTH_INT_ID_SDINT1              30          /* IRQOQN */
#define INTH_INT_ID_SDINT2              31          /* IRQOQN */
#define INTH_INT_ID_3PGSWRXTHR0         32          /*
                                                     *
                                                     * c0_rx_thresh_intr_pend
                                                     */
#define INTH_INT_ID_3PGSWRXINT0         33          /* c0_rx_intr_pend */
#define INTH_INT_ID_3PGSWTXINT0         34          /* c0_tx_intr_pend */
#define INTH_INT_ID_3PGSWMISC0          35          /* c0_misc_intr_pend */
#define INTH_INT_ID_PCIINTA             36          /*
                                                     *
                                                     * pcie_int_i_intr_pend_n0
                                                     */
#define INTH_INT_ID_PCIINTB             37          /*
                                                     *
                                                     * pcie_int_i_intr_pend_n1
                                                     */
#define INTH_INT_ID_PCIINTC             38          /*
                                                     *
                                                     * pcie_int_i_intr_pend_n2
                                                     */
#define INTH_INT_ID_PCIINTD             39          /*
                                                     *
                                                     * pcie_int_i_intr_pend_n3
                                                     */
#define INTH_INT_ID_HDDSS               40          /* intr0_intr_pend_n */
#define INTH_INT_ID_HDMIINT             41          /* intro_intr_pend_n */
#define INTH_INT_ID_SATAINT             42          /* intrq_pend_n */
#define INTH_INT_ID_GFXINT              43          /* THALIAIRQ */
#define INTH_INT_ID_SECURESS_PUBLIC_INT 44          /*
                                                     *
                                                     * nss_pub_top_intr_pending
                                                     */
#define INTH_INT_ID_SECURESS_MBINT      45          /* nss_swi_pub_top_intr-
                                                     * _pending
                                                     */
#define INTH_INT_ID_FDIFINT             46          /* FDIF_IRQ3 */
#define INTH_INT_ID_WDINT               47          /* PO_INT_REQ */
#define INTH_INT_ID_TINT0               48          /* POINTR_PEND */
#define INTH_INT_ID_TINT1               49          /* POINTR_PEND */
#define INTH_INT_ID_TINT2               50          /* POINTR_PEND */
#define INTH_INT_ID_TINT3               51          /* POINTR_PEND */
#define INTH_INT_ID_TINT4               52          /* POINTR_PEND */
#define INTH_INT_ID_TINT5               53          /* POINTR_PEND */
#define INTH_INT_ID_TINT6               54          /* POINTR_PEND */
#define INTH_INT_ID_TINT7               55          /* POINTR_PEND */
#define INTH_INT_ID_MBINT               56          /* mail_u0_irq */
#define INTH_INT_ID_GPIOINT3A           57          /* POINTRPEND1 */
#define INTH_INT_ID_I2CINT0             58          /* POINTRPEND */
#define INTH_INT_ID_I2CINT1             59          /* POINTRPEND */
#define INTH_INT_ID_UARTINT0            60          /* uart0_nirq */
#define INTH_INT_ID_UARTINT1            61          /* uart1_nirq */
#define INTH_INT_ID_UARTINT2            62          /* uart2_nirq */
#define INTH_INT_ID_GPIOINT3B           63          /* POINTRPEND2 */
#define INTH_INT_ID_GPIOINT0A           64          /* POINTRPEND0 */
#define INTH_INT_ID_GPIOINT0B           65          /* POINTRPEND0 */
#define INTH_INT_ID_GPIOINT1A           66          /* POINTRPEND1 */
#define INTH_INT_ID_GPIOINT1B           67          /* POINTRPEND1 */
#define INTH_INT_ID_GPIOINT2A           68          /* POINTRPEND1 */
#define INTH_INT_ID_GPIOINT2B           69          /* POINTRPEND2 */
#define INTH_INT_ID_MCATXINT0           70          /* mcasp_t_intr_pend */
#define INTH_INT_ID_MCARXINT0           71          /* mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT1           72          /* mcasp_t_intr_pend */
#define INTH_INT_ID_MCARXINT1           73          /* mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT2           74          /* mcasp_t_intr_pend */
#define INTH_INT_ID_MCARXINT2           75          /* mcasp_r_intr_pend */
#define INTH_INT_ID_MCBSPINT            76          /* PORCOMMONIRQ */
#define INTH_INT_ID_UARTINT3            77          /* uart3_nirq */
#define INTH_INT_ID_UARTINT4            78          /* uart4_nirq */
#define INTH_INT_ID_UARTINT5            79          /* uart5_nirq */
#define INTH_INT_ID_MCATXINT3           80          /* mcasp_x_intr_pend */
#define INTH_INT_ID_MCARXINT3           81          /* mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT4           82          /* mcasp_x_intr_pend */
#define INTH_INT_ID_MCARXINT4           83          /* mcasp_r_intr_pend */
#define INTH_INT_ID_MCATXINT5           84          /* mcasp_x_intr_pend */
#define INTH_INT_ID_MCARXINT5           85          /* mcasp_r_intr_pend */
#define INTH_INT_ID_SPIINT1             86          /* SINTERRUPTN */
#define INTH_INT_ID_SPIINT2             87          /* SINTERRUPTN */
#define INTH_INT_ID_SPIINT3             88          /* SINTERRUPTN */
#define INTH_INT_ID_I2CINT2             89          /* POINTRPEND */
#define INTH_INT_ID_IVA0CONT1SYNC       90          /*
                                                     *
                                                     * IVA_HD0_POSYNCINTRPEDN1
                                                     */
#define INTH_INT_ID_IVA0CONT2SYNC       91          /*
                                                     *
                                                     * IVA_HD0_POSYNCINTRPEDN2
                                                     */
#define INTH_INT_ID_I2CINT3             92          /* POINTRPEND */
#define INTH_INT_ID_MCMMUINT            93          /* POMMUHOSTINTTR */
#define INTH_INT_ID_IVA0MBOXINT         94          /* IVA_HD0_POMBINTRPEND0 */
#define INTH_INT_ID_GPMCINT             95          /* gpmc_sinterrupt */
#define INTH_INT_ID_INTERR              96          /* Dropped DSP interrupt */
#define INTH_INT_ID_EMC_IDMAERR         97          /* Invalid IDMA params */
#define INTH_INT_ID_PBISTINTERR         98          /* PBIST interrupt
                                                     * May not be available on
                                                     * all SoCs
                                                     */
#define INTH_INT_ID_MDMAERR             110         /* MDMA/XMC error intr */
#define INTH_INT_ID_PMC_ED              113         /* 1-bit error: L1P */

#define INTH_INT_ID_UMCED1              116         /* 1-bit error: L2 */
#define INTH_INT_ID_UMCED2              117         /* 2-bit error: L2 */
#define INTH_INT_ID_PDC_INT             118         /* Powerdomain intr */
#define INTH_INT_ID_SYS_CMPA            119         /* CFG space violations */
#define INTH_INT_ID_PMC_CMPA            120         /* CPU violation: L1PMPU */
#define INTH_INT_ID_PMC_DMPA            121         /* DMA violation: L1PMPU */
#define INTH_INT_ID_DMC_CMPA            122         /* CPU violation: L1DMPU */
#define INTH_INT_ID_DMC_DMPA            123         /* DMA violation: L1DMPU */
#define INTH_INT_ID_UMCCMPA             124         /* CPU violation: L2MPU */
#define INTH_INT_ID_UMCDMPA             125         /* DMA violation: L2MPU */
#define INTH_INT_ID_EMC_CMPA            126         /* CFG space violations
                                                     * from external access
                                                     */
#define INTH_INT_ID_EMC_BUSERR          127         /* Abort returned from
                                                     * external peripherals
                                                     */

/* GEM Crossbar Mapping */

#define INTH_INT_ID_DCAN0_INT0          15              /* dcan_int0 */
#define INTH_INT_ID_DCAN0_INT1          16              /* dcan_int1 */
#define INTH_INT_ID_DCAN0_PARIT         17              /* dcan_parity_int */
#define INTH_INT_ID_DCAN1_INT0          18              /* dcan_int0 */
#define INTH_INT_ID_DCAN1_INT1          19              /* dcan_int1 */
#define INTH_INT_ID_DCAN1_PARIT         20              /* dcan_parity_int */
#define INTH_INT_ID_MLB_SYS_INT0        21              /* MLB_SYS_INT0  */
#define INTH_INT_ID_MLB_SYS_INT1        22              /* MLB_SYS_INT1  */
#define INTH_INT_ID_MLB_INT             23              /* MLB_INT */
#define INTH_INT_ID_SEC_EVNT            24              /* security_events_irq
                                                         */
#define INTH_INT_ID_L3DEBUG             25              /* l3_dbg_irq */
#define INTH_INT_ID_L3APPINT            26              /* l3_app_irq */
#define INTH_INT_ID_EDMAMPERR           27              /* tpcc_mpint_pend_n */
#define INTH_INT_ID_TINT8               28              /* POINTR_PEND */
#define INTH_INT_ID_WDINT0              29              /* PO_INT_REQ */
#define INTH_INT_ID_USBSSINT            30              /* usbss_intr_pend */
#define INTH_INT_ID_USBINT0             31              /* usb0_intr_pend */
#define INTH_INT_ID_USBINT1             32              /* usb1_intr_pend */
#define INTH_INT_ID_RTCINT              33              /* timer_intr_pend */
#define INTH_INT_ID_RTC_ALARM           34              /* alarm_intr_pend */
#define INTH_INT_ID_SMCDINT0            35              /* icc_irq0 */
#define INTH_INT_ID_SMCDINT1            36              /* icc_irq1 */
#define INTH_INT_ID_DDRERR0             37              /* mem_err_intr_pend_n
                                                         */
#define INTH_INT_ID_DDRERR1             38              /* mem_err_intr_pend_n
                                                         */
#define INTH_DEFAULT_INTERRUPT_KIND     (INTH_TYPE_IRQ)
#define INTH_DEFAULT_PRIORITY           0

/* Renaming few interrupt names to make it easier to map */
#define INTH_INT_ID_L1D_PROT_CPU        (INTH_INT_ID_DMC_CMPA)
#define INTH_INT_ID_L1D_PROT_DMA        (INTH_INT_ID_DMC_DMPA)
#define INTH_INT_ID_L1P_PROT_CPU        (INTH_INT_ID_PMC_CMPA)
#define INTH_INT_ID_L1P_PROT_DMA        (INTH_INT_ID_PMC_DMPA)
#define INTH_INT_ID_L2_PROT_CPU         (INTH_INT_ID_UMCCMPA)
#define INTH_INT_ID_L2_PROT_DMA         (INTH_INT_ID_UMCDMPA)
#define INTH_INT_ID_L3_BUS_ERR          (INTH_INT_ID_EMC_BUSERR)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*
 * \brief        function pointer to interrupt handlers
 *               A function pointer to interrupt handlers. The functions should
 *               be defined in the following format:
 *
 * \param   None
 *
 * \return  None.
 *
 **/
typedef void (*IntrFuncPtr)(void *handle);

/**
 * \brief   This API is used to initialize the interrupt controller. This API
 *          shall be called before using the interrupt controller.
 *
 * \return  None.
 *
 **/
void Intc_Init(void);

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts.
 *
 * \param    intrNum - Interrupt Number
 * \param    fptr    - Function pointer to the ISR
 * \param    fun_arg - Argument to the ISR
 *
 * Note: When the interrupt occurs for the sytem interrupt number indicated,
 * the control goes to the ISR given as the parameter.
 *
 * \return      None.
 **/
void Intc_IntRegister(uint16_t intrNum, IntrFuncPtr fptr, void *fun_arg);

/**
 * \brief   Unregisters an interrupt
 *
 * \param   intrNum - Interrupt Number
 *
 * Note: Once an interrupt is unregistered it will enter infinite loop once
 * an interrupt occurs
 *
 * \return      None.
 **/
void Intc_IntUnregister(uint16_t intrNum);

/**
 * \brief   This API enables the system interrupt in INTC. However, for
 *          the interrupt generation, make sure that the interrupt is
 *          enabled at the peripheral level also.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemEnable(uint16_t intrNum);

/**
 * \brief   This API disables the system interrupt in INTC.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void Intc_SystemDisable(uint16_t intrNum);

/**
 * \brief  Restore the processor IER status if status is not equal to 0.
 *         else enables all the bits in IER.
 *         This does not affect the set of interrupts enabled/disabled
 *         in the INTC.
 *
 * \param   status  The status returned by the Intc_IntDisable function.
 *
 * \return  None
 *
 **/
void Intc_IntEnable(uint32_t status);
/**
 * \brief  Read and save the status and Disables the bits in IER .
 *         Prevents the processor to respond to interrupts.
 *
 * \return   Current status of IER
 *
 **/
uint32_t Intc_IntDisable(void);

/**
 * \brief   This API assigns a priority to an interrupt
 *
 * \param   intrNum  - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   hostIntRoute - The host interrupt IRQ/FIQ to which the interrupt
 *                         is to be routed.
 *     'priority' can take any value from 0 to 127, 0 being the highest and
 *     127 being the lowest priority.
 *
 * \return  None.
 *
 **/
void Intc_IntPrioritySet(uint16_t intrNum, uint16_t priority,
                         uint8_t hostIntRoute);

#ifdef __cplusplus
}
#endif

#endif    /* __INTH_H */
/** @} */
/**
 *  \ingroup CSL_ARCH
 *  \defgroup CSL_ARCH_C66X C66x
 */
/********************************* End of file ******************************/
