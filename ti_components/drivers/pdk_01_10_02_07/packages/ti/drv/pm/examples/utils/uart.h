/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file  uart.h
 *
 *  \brief This file contains the prototyes of the low level UART functions
 */

#ifndef UART_H_
#define UART_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/cslr_uart.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* The size of the Transmitter FIFO. */
#define TX_FIFO_SIZE                        (64)

/* The size of the Receiver FIFO. */
#define RX_FIFO_SIZE                        (64)

/*
** Values to configure the Operating modes of UART.
*/
#define UART16x_OPER_MODE                   (UART_MDR1_MODE_SELECT_UART16X)
#define UART_SIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_SIR)
#define UART16x_AUTO_BAUD_OPER_MODE         (UART_MDR1_MODE_SELECT_UART16XAUTO)
#define UART13x_OPER_MODE                   (UART_MDR1_MODE_SELECT_UART13X)
#define UART_MIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_MIR)
#define UART_FIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_FIR)
#define UART_CIR_OPER_MODE                  (UART_MDR1_MODE_SELECT_CIR)
#define UART_DISABLED_MODE                  (UART_MDR1_MODE_SELECT_MASK)

/*
** Values to control the Line characteristics.
*/

/* Break condition generation controls. */
#define UART_BREAK_COND_DISABLE             (UART_LCR_BREAK_EN_BREAK_EN_VALUE_0 \
                                             <<                                 \
                                             UART_LCR_BREAK_EN_SHIFT)
#define UART_BREAK_COND_ENABLE              (UART_LCR_BREAK_EN_BREAK_EN_VALUE_1 \
                                             <<                                 \
                                             UART_LCR_BREAK_EN_SHIFT)

/* Values to control parity feature. */

#define UART_PARITY_REPR_1                  (UART_LCR_PARITY_TYPE2_MASK |                   \
                                             (                                              \
                                                 UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_0 \
                                                 <<                                         \
                                                 UART_LCR_PARITY_TYPE1_SHIFT) |             \
                                             UART_LCR_PARITY_EN_MASK)

#define UART_PARITY_REPR_0                  (UART_LCR_PARITY_TYPE2_MASK |                   \
                                             (                                              \
                                                 UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_1 \
                                                 <<                                         \
                                                 UART_LCR_PARITY_TYPE1_SHIFT) |             \
                                             UART_LCR_PARITY_EN_MASK)

#define UART_ODD_PARITY                     ((                                              \
                                                 UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_0 \
                                                 <<                                         \
                                                 UART_LCR_PARITY_TYPE1_SHIFT) |             \
                                             UART_LCR_PARITY_EN_MASK)

#define UART_EVEN_PARITY                    ((                                              \
                                                 UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_1 \
                                                 <<                                         \
                                                 UART_LCR_PARITY_TYPE1_SHIFT) |             \
                                             UART_LCR_PARITY_EN_MASK)

#define UART_PARITY_NONE                    (   \
        UART_LCR_PARITY_EN_PARITY_EN_VALUE_0 << \
        UART_LCR_PARITY_EN_SHIFT)

/* Number of Stop Bits per frame. */

#define UART_FRAME_NUM_STB_1                (UART_LCR_NB_STOP_NB_STOP_VALUE_0 \
                                             <<                               \
                                             UART_LCR_NB_STOP_SHIFT)
#define UART_FRAME_NUM_STB_1_5_2            (UART_LCR_NB_STOP_NB_STOP_VALUE_1 \
                                             <<                               \
                                             UART_LCR_NB_STOP_SHIFT)

/* Word Length per frame. */

#define UART_FRAME_WORD_LENGTH_5            ( \
        UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_0)
#define UART_FRAME_WORD_LENGTH_6            ( \
        UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_1)
#define UART_FRAME_WORD_LENGTH_7            ( \
        UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_2)
#define UART_FRAME_WORD_LENGTH_8            ( \
        UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_3)

/*
** Values associated with setting the Trigger Levels and DMA mode selection.
*/

/* Values for trigger level for the Receiver FIFO. */

#define UART_FCR_RX_TRIG_LVL_8              (UART_FCR_RX_FIFO_TRIG_8CHAR << \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)
#define UART_FCR_RX_TRIG_LVL_16             (UART_FCR_RX_FIFO_TRIG_16CHAR << \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)
#define UART_FCR_RX_TRIG_LVL_56             (UART_FCR_RX_FIFO_TRIG_56CHAR << \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)
#define UART_FCR_RX_TRIG_LVL_60             (UART_FCR_RX_FIFO_TRIG_60CHAR << \
                                             UART_FCR_RX_FIFO_TRIG_SHIFT)

/* Values for the trigger level for the Transmitter FIFO. */

#define UART_FCR_TX_TRIG_LVL_8              (UART_FCR_TX_FIFO_TRIG_8SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)
#define UART_FCR_TX_TRIG_LVL_16             (UART_FCR_TX_FIFO_TRIG_16SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)
#define UART_FCR_TX_TRIG_LVL_32             (UART_FCR_TX_FIFO_TRIG_32SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)
#define UART_FCR_TX_TRIG_LVL_56             (UART_FCR_TX_FIFO_TRIG_56SPACES << \
                                             UART_FCR_TX_FIFO_TRIG_SHIFT)

/* Values corresponding to DMA mode selection. */

#define UART_DMA_MODE_0_ENABLE              ( \
        UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_0)
#define UART_DMA_MODE_1_ENABLE              ( \
        UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_1)
#define UART_DMA_MODE_2_ENABLE              ( \
        UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_2)
#define UART_DMA_MODE_3_ENABLE              ( \
        UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_3)

/*
** Values used to choose the path for configuring the DMA Mode.
** DMA Mode could be configured either through FCR or SCR.
*/
#define UART_DMA_EN_PATH_FCR                ( \
        UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_0)
#define UART_DMA_EN_PATH_SCR                ( \
        UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_1)

/*
** Values related to enabling/disabling of Interrupts.
*/

/* Values for enabling/disabling the interrupts of UART. */

#define UART_INT_CTS                        (UART_IER_CTS_IT_MASK)
#define UART_INT_RTS                        (UART_IER_RTS_IT_MASK)
#define UART_INT_XOFF                       (UART_IER_XOFF_IT_MASK)
#define UART_INT_SLEEPMODE                  (UART_IER_SLEEP_MODE_MASK)
#define UART_INT_MODEM_STAT                 (UART_IER_MODEM_STS_IT_MASK)
#define UART_INT_LINE_STAT                  (UART_IER_LINE_STS_IT_MASK)
#define UART_INT_THR                        (UART_IER_THR_IT_MASK)
#define UART_INT_RHR_CTI                    (UART_IER_RHR_IT_MASK)

/*
** Values related to Line Status information.
*/

/* Values pertaining to UART Line Status information. */

#define UART_FIFO_PE_FE_BI_DETECTED         (UART_LSR_RX_FIFO_STS_MASK)
#define UART_BREAK_DETECTED_ERROR           (UART_LSR_RX_BI_MASK)
#define UART_FRAMING_ERROR                  (UART_LSR_RX_FE_MASK)
#define UART_PARITY_ERROR                   (UART_LSR_RX_PE_MASK)
#define UART_OVERRUN_ERROR                  (UART_LSR_RX_OE_MASK)

/*
** Values related to status of Interrupt souces.
*/

/* Values pertaining to status of UART Interrupt sources. */

#define UART_INTID_MODEM_STAT               (UART_IIR_IT_TYPE_IT_TYPE_VALUE_0 \
                                             <<                               \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_TX_THRES_REACH           (UART_IIR_IT_TYPE_IT_TYPE_VALUE_1 \
                                             <<                               \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_RX_THRES_REACH           (UART_IIR_IT_TYPE_IT_TYPE_VALUE_2 \
                                             <<                               \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_RX_LINE_STAT_ERROR       (UART_IIR_IT_TYPE_IT_TYPE_VALUE_3 \
                                             <<                               \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_CHAR_TIMEOUT             (UART_IIR_IT_TYPE_IT_TYPE_VALUE_6 \
                                             <<                               \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_XOFF_SPEC_CHAR_DETECT    (UART_IIR_IT_TYPE_IT_TYPE_VALUE_8 \
                                             <<                               \
                                             UART_IIR_IT_TYPE_SHIFT)
#define UART_INTID_MODEM_SIG_STATE_CHANGE   (UART_IIR_IT_TYPE_IT_TYPE_VALUE_10 \
                                             <<                                \
                                             UART_IIR_IT_TYPE_SHIFT)

/* Values indicating the UART Interrupt pending status. */
#define UART_INT_PENDING                    (0U)
#define UART_N0_INT_PENDING                 (1U)

/*
** Values pertaining to control of Enhanced Features.
*/

/* Values for controlling Auto-CTS and Auto-RTS features. */

#define UART_AUTO_CTS_ENABLE                ((uint32_t) (                                    \
                                                 UART_EFR_AUTO_CTS_EN_AUTO_CTS_EN_U_VALUE_1) \
                                             <<                                              \
                                             (UART_EFR_AUTO_CTS_EN_SHIFT))
#define UART_AUTO_CTS_DISABLE               ((uint32_t) (                                    \
                                                 UART_EFR_AUTO_CTS_EN_AUTO_CTS_EN_U_VALUE_0) \
                                             <<                                              \
                                             (UART_EFR_AUTO_CTS_EN_SHIFT))

#define UART_AUTO_RTS_ENABLE                ((uint32_t) (                                    \
                                                 UART_EFR_AUTO_RTS_EN_AUTO_RTS_EN_U_VALUE_1) \
                                             <<                                              \
                                             (UART_EFR_AUTO_RTS_EN_SHIFT))
#define UART_AUTO_RTS_DISABLE               ((uint32_t) (                                    \
                                                 UART_EFR_AUTO_RTS_EN_AUTO_RTS_EN_U_VALUE_0) \
                                             <<                                              \
                                             (UART_EFR_AUTO_RTS_EN_SHIFT))

/* Values to enable/disable detection of Special Character. */

#define UART_SPECIAL_CHAR_DETECT_ENABLE     (UART_EFR_SPECIAL_CHAR_DETECT_MASK)
#define UART_SPECIAL_CHAR_DETECT_DISABLE    ( \
        UART_EFR_SPECIAL_CHAR_DETECT_SPECIAL_CHAR_DETECT_U_VALUE_0)

/* Values to configure the options for Software Flow Control. */

#define UART_NO_SOFTWARE_FLOW_CONTROL       ((                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_0 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_TX_SHIFT)                 \
                                             |                                                      \
                                             (                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_0 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

#define UART_TX_RX_XON1_XOFF1               ((                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_2 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_TX_SHIFT)                 \
                                             |                                                      \
                                             (                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_2 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

#define UART_TX_RX_XON2_XOFF2               ((                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_1 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_TX_SHIFT)                 \
                                             |                                                      \
                                             (                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_1 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

#define UART_TX_RX_XON1_XOFF1_XON2_XOFF2    ((                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_3 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_TX_SHIFT)                 \
                                             |                                                      \
                                             (                                                      \
                                                 UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_3 \
                                                 <<                                                 \
                                                 UART_EFR_SW_FLOW_CONTROL_RX_SHIFT))

/*
** Values corresponding to Mode Definition Register 2(MDR2).
*/

/* Values to enable/disable Pulse shaping for UART. */
#define UART_PULSE_NORMAL                   (      \
        UART_MDR2_UART_PULSE_UART_PULSE_VALUE_0 << \
        UART_MDR2_UART_PULSE_SHIFT)
#define UART_PULSE_SHAPING                  (      \
        UART_MDR2_UART_PULSE_UART_PULSE_VALUE_1 << \
        UART_MDR2_UART_PULSE_SHIFT)
/*
** Values corresponding to Mode Definition Register 3(MDR3).
*/

/* Values used to control the method of setting the TX DMA Threshold value. */
#define UART_TX_DMA_THRESHOLD_64            (UART_MDR3_SET_DMA_TX_THRESHOLD_64 \
                                             <<                                \
                                             UART_MDR3_SET_DMA_TX_THRESHOLD_SHIFT)
#define UART_TX_DMA_THRESHOLD_REG           (UART_MDR3_SET_DMA_TX_THRESHOLD_REG \
                                             <<                                 \
                                             UART_MDR3_SET_DMA_TX_THRESHOLD_SHIFT)

/*
** Macros related to control and status of Modem Signals.
*/

/* Values to enable/disable XON any feature. */

#define UART_XON_ANY_ENABLE                 (UART_MCR_XON_EN_XON_EN_VALUE_1 << \
                                             UART_MCR_XON_EN_SHIFT)
#define UART_XON_ANY_DISABLE                (UART_MCR_XON_EN_XON_EN_VALUE_0 << \
                                             UART_MCR_XON_EN_SHIFT)

/* Values to enable/disable Loopback mode of operation. */

#define UART_LOOPBACK_MODE_ENABLE           (       \
        UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_1 << \
        UART_MCR_LOOPBACK_EN_SHIFT)
#define UART_LOOPBACK_MODE_DISABLE          (       \
        UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_0 << \
        UART_MCR_LOOPBACK_EN_SHIFT)

/* Macros used to force the Modem Control lines to active/inactive states. */

#define UART_DCD_CONTROL                    (UART_MCR_CD_STS_CH_MASK)
#define UART_RI_CONTROL                     (UART_MCR_RI_STS_CH_MASK)
#define UART_RTS_CONTROL                    (UART_MCR_RTS_MASK)
#define UART_DTR_CONTROL                    (UART_MCR_DTR_MASK)

/* Values that indicate the values on Modem Control lines. */

#define UART_DCD_VALUE                      (UART_MSR_NCD_STS_MASK)
#define UART_RI_VALUE                       (UART_MSR_NRI_STS_MASK)
#define UART_DSR_VALUE                      (UART_MSR_NDSR_STS_MASK)
#define UART_CTS_VALUE                      (UART_MSR_NCTS_STS_MASK)

/* Values used to detect the changes in Modem Control lines. */

#define UART_DCD_STS_CHANGED                (UART_MSR_DCD_STS_MASK)
#define UART_RI_STS_CHANGED                 (UART_MSR_RI_STS_MASK)
#define UART_DSR_STS_CHANGED                (UART_MSR_DSR_STS_MASK)
#define UART_CTS_STS_CHANGED                (UART_MSR_CTS_STS_MASK)

/*
** Values related to the control and status of Supplementary registers.
*/

/*
** Values used to enable/disable a granularity of 1 for TX and RX FIFO trigger
** levels.
*/
#define UART_RX_TRIG_LVL_GRAN_1_DISABLE     (             \
        UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_0 << \
        UART_SCR_RX_TRIG_GRANU1_SHIFT)
#define UART_RX_TRIG_LVL_GRAN_1_ENABLE      (             \
        UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_1 << \
        UART_SCR_RX_TRIG_GRANU1_SHIFT)

#define UART_TX_TRIG_LVL_GRAN_1_DISABLE     (             \
        UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_0 << \
        UART_SCR_TX_TRIG_GRANU1_SHIFT)
#define UART_TX_FIFO_LVL_GRAN_1_ENABLE      (             \
        UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_1 << \
        UART_SCR_TX_TRIG_GRANU1_SHIFT)

/* Value used to enable/disable DSRn interrupt. */

#define UART_DSRn_INT_DISABLE               (UART_SCR_DSR_IT_DSR_IT_VALUE_0 << \
                                             UART_SCR_DSR_IT_SHIFT)
#define UART_DSRn_INT_ENABLE                (UART_SCR_DSR_IT_DSR_IT_VALUE_1 << \
                                             UART_SCR_DSR_IT_SHIFT)

/* Values to control the module Wake-Up rights for RX, CTSn and DSRn pins. */

#define UART_RX_CTS_DSR_WAKEUP_DISABLE      (                                   \
        UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_RX_CTS_DSR_WAKE_UP_ENABLE_VALUE_0 << \
        UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_SHIFT)
#define UART_RX_CTS_DSR_WAKEUP_ENABLE       (                                   \
        UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_RX_CTS_DSR_WAKE_UP_ENABLE_VALUE_1 << \
        UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_SHIFT)

/* Values to control the THR interrupt modes. */

#define UART_THR_INT_NORMAL                 (               \
        UART_SCR_TX_EMPTY_CTL_IT_TX_EMPTY_CTL_IT_VALUE_0 << \
        UART_SCR_TX_EMPTY_CTL_IT_SHIFT)
#define UART_THR_INT_FIFO_TSR_EMPTY         (               \
        UART_SCR_TX_EMPTY_CTL_IT_TX_EMPTY_CTL_IT_VALUE_1 << \
        UART_SCR_TX_EMPTY_CTL_IT_SHIFT)

/* Values to control the DMA counter reset features. */

#define UART_DMA_CNTR_NO_RESET_FIFO_RESET   (               \
        UART_SSR_DMA_COUNTER_RST_DMA_COUNTER_RST_VALUE_0 << \
        UART_SSR_DMA_COUNTER_RST_SHIFT)
#define UART_DMA_CNTR_RESET_FIFO_RESET      (               \
        UART_SSR_DMA_COUNTER_RST_DMA_COUNTER_RST_VALUE_1 << \
        UART_SSR_DMA_COUNTER_RST_SHIFT)

/* Values indicating the Falling edge status on RX, CTSn and DSRn pins. */

#define UART_RX_CTS_DSR_NO_FALL_EDGE        (                             \
        UART_SSR_RX_CTS_DSR_WAKE_UP_STS_RX_CTS_DSR_WAKE_UP_STS_VALUE_0 << \
        UART_SSR_RX_CTS_DSR_WAKE_UP_STS_SHIFT)
#define UART_RX_CTS_DSR_FALL_EDGE           (                             \
        UART_SSR_RX_CTS_DSR_WAKE_UP_STS_RX_CTS_DSR_WAKE_UP_STS_VALUE_1 << \
        UART_SSR_RX_CTS_DSR_WAKE_UP_STS_SHIFT)

/* Values indicating the filled status of TX FIFO. */

#define UART_TX_FIFO_NOT_FULL               ( \
        UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_0)
#define UART_TX_FIFO_FULL                   ( \
        UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_1)

/*
** Values related to Auxilliary Control Register(ACREG).
*/

/* Values to set/clear the SD pin. */

#define UART_SD_PIN_LOW                     (UART_ACREG_SD_MOD_SD_MOD_VALUE_1 \
                                             <<                               \
                                             UART_ACREG_SD_MOD_SHIFT)
#define UART_SD_PIN_HIGH                    (UART_ACREG_SD_MOD_SD_MOD_VALUE_0 \
                                             <<                               \
                                             UART_ACREG_SD_MOD_SHIFT)

/*
** Values controlling System Configuration functions.
*/

/* Values controlling Power Management Request/Acknowledgement modes. */

#define UART_IDLEMODE_FORCE_IDLE            (  \
        UART_SYSC_IDLEMODE_IDLEMODE_VALUE_0 << \
        UART_SYSC_IDLEMODE_SHIFT)
#define UART_IDLEMODE_NO_IDLE               (  \
        UART_SYSC_IDLEMODE_IDLEMODE_VALUE_1 << \
        UART_SYSC_IDLEMODE_SHIFT)
#define UART_IDLEMODE_SMART_IDLE            (  \
        UART_SYSC_IDLEMODE_IDLEMODE_VALUE_2 << \
        UART_SYSC_IDLEMODE_SHIFT)
#define UART_IDLEMODE_SMART_IDLE_WAKEUP     (  \
        UART_SYSC_IDLEMODE_IDLEMODE_VALUE_3 << \
        UART_SYSC_IDLEMODE_SHIFT)

/* Values enabling/disabling WakeUp capability. */

#define UART_WAKEUP_ENABLE                  (    \
        UART_SYSC_ENAWAKEUP_ENAWAKEUP_VALUE_1 << \
        UART_SYSC_ENAWAKEUP_SHIFT)
#define UART_WAKEUP_DISABLE                 (    \
        UART_SYSC_ENAWAKEUP_ENAWAKEUP_VALUE_0 << \
        UART_SYSC_ENAWAKEUP_SHIFT)

/* Values to enable /disable Autoidle mode. */
#define UART_AUTO_IDLE_MODE_ENABLE          ( \
        UART_SYSC_AUTOIDLE_AUTOIDLE_VALUE_1)
#define UART_AUTO_IDLE_MODE_DISABLE         ( \
        UART_SYSC_AUTOIDLE_AUTOIDLE_VALUE_0)

/*
** Values configuring Wake-up modes for the UART in Wake-Up Enable Register.
*/

/* Values that enable/disable Wake-Up generation ability for various signals. */
#define UART_WAKEUP_TX_INTERRUPT            (UART_WER_EVENT_7_TX_WAKEUP_EN_MASK)
#define UART_WAKEUP_RLS_INTERRUPT           ( \
        UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_MASK)
#define UART_WAKEUP_RHR_INTERRUPT           ( \
        UART_WER_EVENT_5_RHR_INTERRUPT_MASK)
#define UART_WAKEUP_RX_ACTIVITY             (UART_WER_EVENT_4_RX_ACTIVITY_MASK)
#define UART_WAKEUP_DCD_ACTIVITY            ( \
        UART_WER_EVENT_3_DCD_CD_ACTIVITY_MASK)
#define UART_WAKEUP_RI_ACTIVITY             (UART_WER_EVENT_2_RI_ACTIVITY_MASK)
#define UART_WAKEUP_DSR_ACTIVITY            (UART_WER_EVENT_1_DSR_ACTIVITY_MASK)
#define UART_WAKEUP_CTS_ACTIVITY            (UART_WER_EVENT_0_CTS_ACTIVITY_MASK)

/*
** Values indicating the line characteristics of UART Autobauding mode
** communication.
*/

/* Values indicating the parity in UART Autobauding mode. */

#define UART_AUTOBAUD_NO_PARITY             (          \
        UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_0 << \
        UART_UASR_PARITY_TYPE_SHIFT)
#define UART_AUTOBAUD_PARITY_SPACE          (          \
        UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_1 << \
        UART_UASR_PARITY_TYPE_SHIFT)
#define UART_AUTOBAUD_EVEN_PARITY           (          \
        UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_2 << \
        UART_UASR_PARITY_TYPE_SHIFT)
#define UART_AUTOBAUD_ODD_PARITY            (          \
        UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_3 << \
        UART_UASR_PARITY_TYPE_SHIFT)

/* Values indicating the word length in UART Autobaud mode. */

#define UART_AUTOBAUD_CHAR_LENGTH_7         (          \
        UART_UASR_BIT_BY_CHAR_BIT_BY_CHAR_U_VALUE_0 << \
        UART_UASR_BIT_BY_CHAR_SHIFT)
#define UART_AUTOBAUD_CHAR_LENGTH_8         (          \
        UART_UASR_BIT_BY_CHAR_BIT_BY_CHAR_U_VALUE_1 << \
        UART_UASR_BIT_BY_CHAR_SHIFT)

/* Values indicating the baud rate in UART Autobaud mode. */

#define UART_AUTOBAUD_NO_SPEED_IDEN         (UART_UASR_SPEED_SPEED_VALUE_0)
#define UART_AUTOBAUD_SPEED_115200          (UART_UASR_SPEED_SPEED_VALUE_1)
#define UART_AUTOBAUD_SPEED_57600           (UART_UASR_SPEED_SPEED_VALUE_2)
#define UART_AUTOBAUD_SPEED_38400           (UART_UASR_SPEED_SPEED_VALUE_3)
#define UART_AUTOBAUD_SPEED_28800           (UART_UASR_SPEED_SPEED_VALUE_4)
#define UART_AUTOBAUD_SPEED_19200           (UART_UASR_SPEED_SPEED_VALUE_5)
#define UART_AUTOBAUD_SPEED_14400           (UART_UASR_SPEED_SPEED_VALUE_6)
#define UART_AUTOBAUD_SPEED_9600            (UART_UASR_SPEED_SPEED_VALUE_7)
#define UART_AUTOBAUD_SPEED_4800            (UART_UASR_SPEED_SPEED_VALUE_8)
#define UART_AUTOBAUD_SPEED_2400            (UART_UASR_SPEED_SPEED_VALUE_9)
#define UART_AUTOBAUD_SPEED_1200            (UART_UASR_SPEED_SPEED_VALUE_10)

/*
** Miscellaneous macros.
*/
/*
** Values used to choose the trigger level granularity.
*/
#define UART_TRIG_LVL_GRANULARITY_4         ((uint32_t) 0x0000U)
#define UART_TRIG_LVL_GRANULARITY_1         ((uint32_t) 0x0001U)

/* Values to be used while switching between register configuration modes. */

#define UART_REG_CONFIG_MODE_A              (uint32_t) (0x0080)
#define UART_REG_CONFIG_MODE_B              (uint32_t) (0x00BF)
#define UART_REG_OPERATIONAL_MODE           (uint32_t) (0x007F)

/* Parameterized macro used to determine a value to be written to FCR. */
#define UART_FCR_PROGRAM(rxFIFOTrig, txFIFOTrig, dmaMode, txClr, rxClr, fifoEn) \
    ((uint32_t)                                                                 \
     ((((rxFIFOTrig) & 0x3) << 6) |                                             \
      (((txFIFOTrig) & 0x3) << 4) |                                             \
      (((dmaMode) & 0x1) << 3) |                                                \
      (((txClr) & 0x1) << 2) |                                                  \
      (((rxClr) & 0x1) << 1) |                                                  \
      ((fifoEn) & 0x1)))
#define UART_FIFO_CONFIG_TXGRA     ((uint32_t) 0xFU << 26)
#define UART_FIFO_CONFIG_RXGRA     ((uint32_t) 0xFU << 22)
#define UART_FIFO_CONFIG_TXTRIG    ((uint32_t) 0xFFU << 14)
#define UART_FIFO_CONFIG_RXTRIG    ((uint32_t) 0xFFU << 6)
#define UART_FIFO_CONFIG_TXCLR     ((uint32_t) 0x1U << 5)
#define UART_FIFO_CONFIG_RXCLR     ((uint32_t) 0x1U << 4)
#define UART_FIFO_CONFIG_DMAENPATH ((uint32_t) 0x1U << 3)
#define UART_FIFO_CONFIG_DMAMODE   ((uint32_t) 0x7U << 0)

/* Over-sampling rate for MIR mode used to obtain the Divisor Values. */
#define UART_MIR_OVERSAMPLING_RATE_41          ((uint32_t) 41U)
#define UART_MIR_OVERSAMPLING_RATE_42          ((uint32_t) 42U)

#define UART_FCR_TX_FIFO_TRIG_8SPACES    ((uint32_t) 0x0U)
#define UART_FCR_TX_FIFO_TRIG_16SPACES   ((uint32_t) 0x1U)
#define UART_FCR_TX_FIFO_TRIG_32SPACES   ((uint32_t) 0x2U)
#define UART_FCR_TX_FIFO_TRIG_56SPACES   ((uint32_t) 0x3U)

/*used in uart console init function*/
#define UART_LCR_STB_SHIFT           ((uint32_t) 0x00000002U)
#define UART_LCR_PEN_SHIFT           ((uint32_t) 0x00000003U)
#define UART_LCR_BC_SHIFT            ((uint32_t) 0x00000006U)

#define UART_LCR_PARITY_EN_DISABLE      ((uint32_t) 0x0U)

#define UART_MDR1_MODE_SELECT_CIR           ((uint32_t) 0x6U)
#define UART_MDR1_MODE_SELECT_DISABLED      ((uint32_t) 0x7U)
#define UART_MDR1_MODE_SELECT_FIR           ((uint32_t) 0x5U)
#define UART_MDR1_MODE_SELECT_MIR           ((uint32_t) 0x4U)
#define UART_MDR1_MODE_SELECT_SIR           ((uint32_t) 0x1U)
#define UART_MDR1_MODE_SELECT_UART13X       ((uint32_t) 0x3U)
#define UART_MDR1_MODE_SELECT_UART16X       ((uint32_t) 0x0U)
#define UART_MDR1_MODE_SELECT_UART16XAUTO   ((uint32_t) 0x2U)

#define UART_FCR_RX_FIFO_TRIG_16CHAR   ((uint32_t) 0x1U)
#define UART_FCR_RX_FIFO_TRIG_56CHAR   ((uint32_t) 0x2U)
#define UART_FCR_RX_FIFO_TRIG_60CHAR   ((uint32_t) 0x3U)
#define UART_FCR_RX_FIFO_TRIG_8CHAR    ((uint32_t) 0x0U)

#define UART_EFR_SW_FLOW_CONTROL_RX_SHIFT   ((uint32_t) 0x0U)
#define UART_EFR_SW_FLOW_CONTROL_TX_SHIFT   ((uint32_t) 0x2U)

#define UART_MDR3_SET_DMA_TX_THRESHOLD_64    ((uint32_t) 0x0U)
#define UART_MDR3_SET_DMA_TX_THRESHOLD_REG   ((uint32_t) 0x1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef UART_H_ */
