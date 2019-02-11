/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_CAL_H_
#define CSLR_CAL_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for IRQ
**************************************************************************/
typedef struct {
    volatile Uint32 HL_IRQSTATUS_RAW;
    volatile Uint32 HL_IRQSTATUS;
    volatile Uint32 HL_IRQENABLE_SET;
    volatile Uint32 HL_IRQENABLE_CLR;
} CSL_CalIrqRegs;


/**************************************************************************
* Register Overlay Structure for PIX_PROC
**************************************************************************/
typedef struct {
    volatile Uint32 PIX_PROC;
} CSL_CalPix_procRegs;


/**************************************************************************
* Register Overlay Structure for CTRL_BLOCK
**************************************************************************/
typedef struct {
    volatile Uint32 CTRL;
    volatile Uint8  RSVD0[28];
    volatile Uint32 VPORT_CTRL1;
    volatile Uint32 VPORT_CTRL2;
    volatile Uint8  RSVD1[8];
    volatile Uint32 BYS_CTRL1;
    volatile Uint32 BYS_CTRL2;
    volatile Uint8  RSVD2[8];
    volatile Uint32 RD_DMA_CTRL;
    volatile Uint32 RD_DMA_PIX_ADDR;
    volatile Uint32 RD_DMA_PIX_OFST;
    volatile Uint32 RD_DMA_XSIZE;
    volatile Uint32 RD_DMA_YSIZE;
    volatile Uint32 RD_DMA_INIT_ADDR;
    volatile Uint8  RSVD3[16];
    volatile Uint32 RD_DMA_INIT_OFST;
} CSL_CalCtrl_blockRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint32 HL_REVISION;
    volatile Uint32 HL_HWINFO;
    volatile Uint8  RSVD4[8];
    volatile Uint32 HL_SYSCONFIG;
    volatile Uint8  RSVD5[8];
    volatile Uint32 HL_IRQ_EOI;
    CSL_CalIrqRegs	IRQ[5];
    volatile Uint8  RSVD6[80];
    CSL_CalPix_procRegs	PIX_PROC[4];
    volatile Uint8  RSVD7[48];
    CSL_CalCtrl_blockRegs	CTRL_BLOCK;
} CSL_CalRegs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* IP Revision Identifier (X.Y.R) Used by software to track features, bugs,
 * and compatibility */
#define CSL_CAL_HL_REVISION                                     (0x0U)

/* Information about the IP module's hardware configuration, i.e. typically
 * the module's HDL generics (if any). Actual field format and encoding is up
 * to the module's designer to decide. */
#define CSL_CAL_HL_HWINFO                                       (0x4U)

/* Clock management configuration */
#define CSL_CAL_HL_SYSCONFIG                                    (0x10U)

/* End Of Interrupt number specification */
#define CSL_CAL_HL_IRQ_EOI                                      (0x1CU)

/* Per-event raw interrupt status vector, line #0. Raw status is set even if
 * event is not enabled. */
#define CSL_CAL_HL_IRQSTATUS_RAW(n)                             (0x20U + ((n) * (0x10U)))

/* Per-event "enabled" interrupt status vector, line #0. Enabled status isn't
 * set unless event is enabled. */
#define CSL_CAL_HL_IRQSTATUS(n)                                 (0x24U + ((n) * (0x10U)))

/* Per-event interrupt enable bit vector Write 1 to set (enable interrupt).
 * Readout equal to corresponding _CLR register. */
#define CSL_CAL_HL_IRQENABLE_SET(n)                             (0x28U + ((n) * (0x10U)))

/* Per-event interrupt enable bit vector Write 1 to clear (disable interrupt).
 * Readout equal to corresponding _SET register. */
#define CSL_CAL_HL_IRQENABLE_CLR(n)                             (0x2CU + ((n) * (0x10U)))

/* Pixel processing control */
#define CSL_CAL_PIX_PROC(n)                                     (0xC0U + ((n) * (0x4U)))

/* Global control register */
#define CSL_CAL_CTRL                                            (0x100U)

/* Video port control register */
#define CSL_CAL_VPORT_CTRL1                                     (0x120U)

/* Video port control register */
#define CSL_CAL_VPORT_CTRL2                                     (0x124U)

/* BYS port control register */
#define CSL_CAL_BYS_CTRL1                                       (0x130U)

/* BYS port control register */
#define CSL_CAL_BYS_CTRL2                                       (0x134U)

/* Read DMA control register */
#define CSL_CAL_RD_DMA_CTRL                                     (0x140U)

/* Byte address of the top left corner of the buffer to read in system memory */
#define CSL_CAL_RD_DMA_PIX_ADDR                                 (0x144U)

/* Byte offset between two consecutive line starts */
#define CSL_CAL_RD_DMA_PIX_OFST                                 (0x148U)

/* RD_DMA_XSIZE */
#define CSL_CAL_RD_DMA_XSIZE                                    (0x14CU)

/* RD_DMA_YSIZE */
#define CSL_CAL_RD_DMA_YSIZE                                    (0x150U)

/* RD_DMA_INIT_ADDR */
#define CSL_CAL_RD_DMA_INIT_ADDR                                (0x154U)

/* Byte offset between two consecutive line starts */
#define CSL_CAL_RD_DMA_INIT_OFST                                (0x168U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* HL_REVISION */

#define CSL_CAL_HL_REVISION_Y_MINOR_MASK                        (0x0000003FU)
#define CSL_CAL_HL_REVISION_Y_MINOR_SHIFT                       (0U)
#define CSL_CAL_HL_REVISION_Y_MINOR_RESETVAL                    (0x00000000U)
#define CSL_CAL_HL_REVISION_Y_MINOR_MAX                         (0x0000003fU)

#define CSL_CAL_HL_REVISION_CUSTOM_MASK                         (0x000000C0U)
#define CSL_CAL_HL_REVISION_CUSTOM_SHIFT                        (6U)
#define CSL_CAL_HL_REVISION_CUSTOM_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_REVISION_CUSTOM_STANDARD                     (0x00000000U)

#define CSL_CAL_HL_REVISION_X_MAJOR_MASK                        (0x00000700U)
#define CSL_CAL_HL_REVISION_X_MAJOR_SHIFT                       (8U)
#define CSL_CAL_HL_REVISION_X_MAJOR_RESETVAL                    (0x00000001U)
#define CSL_CAL_HL_REVISION_X_MAJOR_MAX                         (0x00000007U)

#define CSL_CAL_HL_REVISION_R_RTL_MASK                          (0x0000F800U)
#define CSL_CAL_HL_REVISION_R_RTL_SHIFT                         (11U)
#define CSL_CAL_HL_REVISION_R_RTL_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_REVISION_R_RTL_MAX                           (0x0000001fU)

#define CSL_CAL_HL_REVISION_FUNC_MASK                           (0x0FFF0000U)
#define CSL_CAL_HL_REVISION_FUNC_SHIFT                          (16U)
#define CSL_CAL_HL_REVISION_FUNC_RESETVAL                       (0x00000000U)
#define CSL_CAL_HL_REVISION_FUNC_MAX                            (0x00000fffU)

#define CSL_CAL_HL_REVISION_SCHEME_MASK                         (0xC0000000U)
#define CSL_CAL_HL_REVISION_SCHEME_SHIFT                        (30U)
#define CSL_CAL_HL_REVISION_SCHEME_RESETVAL                     (0x00000001U)
#define CSL_CAL_HL_REVISION_SCHEME_H08                          (0x00000001U)
#define CSL_CAL_HL_REVISION_SCHEME_LEGACY                       (0x00000000U)

#define CSL_CAL_HL_REVISION_RESETVAL                            (0x40000100U)

/* HL_HWINFO */

#define CSL_CAL_HL_HWINFO_WFIFO_MASK                            (0x0000000FU)
#define CSL_CAL_HL_HWINFO_WFIFO_SHIFT                           (0U)
#define CSL_CAL_HL_HWINFO_WFIFO_RESETVAL                        (0x00000007U)
#define CSL_CAL_HL_HWINFO_WFIFO_MAX                             (0x0000000fU)

#define CSL_CAL_HL_HWINFO_RFIFO_MASK                            (0x000000F0U)
#define CSL_CAL_HL_HWINFO_RFIFO_SHIFT                           (4U)
#define CSL_CAL_HL_HWINFO_RFIFO_RESETVAL                        (0x00000006U)
#define CSL_CAL_HL_HWINFO_RFIFO_MAX                             (0x0000000fU)

#define CSL_CAL_HL_HWINFO_PCTX_MASK                             (0x00001F00U)
#define CSL_CAL_HL_HWINFO_PCTX_SHIFT                            (8U)
#define CSL_CAL_HL_HWINFO_PCTX_RESETVAL                         (0x00000004U)
#define CSL_CAL_HL_HWINFO_PCTX_MAX                              (0x0000001fU)

#define CSL_CAL_HL_HWINFO_WCTX_MASK                             (0x0007E000U)
#define CSL_CAL_HL_HWINFO_WCTX_SHIFT                            (13U)
#define CSL_CAL_HL_HWINFO_WCTX_RESETVAL                         (0x00000008U)
#define CSL_CAL_HL_HWINFO_WCTX_MAX                              (0x0000003fU)

#define CSL_CAL_HL_HWINFO_VFIFO_MASK                            (0x00780000U)
#define CSL_CAL_HL_HWINFO_VFIFO_SHIFT                           (19U)
#define CSL_CAL_HL_HWINFO_VFIFO_RESETVAL                        (0x00000009U)
#define CSL_CAL_HL_HWINFO_VFIFO_MAX                             (0x0000000fU)

#define CSL_CAL_HL_HWINFO_NCPORT_MASK                           (0x0F800000U)
#define CSL_CAL_HL_HWINFO_NCPORT_SHIFT                          (23U)
#define CSL_CAL_HL_HWINFO_NCPORT_RESETVAL                       (0x00000007U)
#define CSL_CAL_HL_HWINFO_NCPORT_MAX                            (0x0000001fU)

#define CSL_CAL_HL_HWINFO_RESETVAL                              (0x03c90467U)

/* HL_SYSCONFIG */

#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_MASK                     (0x00000001U)
#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_SHIFT                    (0U)
#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_DONE                     (0x00000000U)
#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_PENDING                  (0x00000001U)
#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_SYSCONFIG_SOFTRESET_RESET                    (0x00000001U)

#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_MASK                      (0x0000000CU)
#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_SHIFT                     (2U)
#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_RESETVAL                  (0x00000002U)
#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_FORCE                     (0x00000000U)
#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_NO                        (0x00000001U)
#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_SMART1                    (0x00000002U)
#define CSL_CAL_HL_SYSCONFIG_IDLEMODE_SMART2                    (0x00000003U)

#define CSL_CAL_HL_SYSCONFIG_RESETVAL                           (0x00000008U)

/* HL_IRQ_EOI */

#define CSL_CAL_HL_IRQ_EOI_LINE_NUMBER_MASK                     (0x00000001U)
#define CSL_CAL_HL_IRQ_EOI_LINE_NUMBER_SHIFT                    (0U)
#define CSL_CAL_HL_IRQ_EOI_LINE_NUMBER_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQ_EOI_LINE_NUMBER_READ0                    (0x00000000U)
#define CSL_CAL_HL_IRQ_EOI_LINE_NUMBER_EOI0                     (0x00000000U)

#define CSL_CAL_HL_IRQ_EOI_RESETVAL                             (0x00000000U)

/* HL_IRQSTATUS_RAW */

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_MASK                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_SHIFT                     (0U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ0_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_MASK                      (0x00000002U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_SHIFT                     (1U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ1_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_MASK                      (0x00000004U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_SHIFT                     (2U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ2_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_MASK                      (0x00000008U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_SHIFT                     (3U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ3_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_MASK                      (0x00000010U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_SHIFT                     (4U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ4_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_MASK                      (0x00000020U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_SHIFT                     (5U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ5_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_MASK                      (0x00000040U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_SHIFT                     (6U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ6_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_MASK                      (0x00000080U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_SHIFT                     (7U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ7_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_MASK                      (0x00000100U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_SHIFT                     (8U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ8_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_MASK                      (0x00000200U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_SHIFT                     (9U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_NOEVENT                   (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_PENDING                   (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_NACT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ9_SET                       (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_MASK                     (0x00000400U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_SHIFT                    (10U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ10_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_MASK                     (0x00000800U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_SHIFT                    (11U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ11_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_MASK                     (0x00001000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_SHIFT                    (12U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ12_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_MASK                     (0x00002000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_SHIFT                    (13U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ13_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_MASK                     (0x00004000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_SHIFT                    (14U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ14_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_MASK                     (0x00008000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_SHIFT                    (15U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ15_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_MASK                     (0x00010000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_SHIFT                    (16U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ16_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_MASK                     (0x00020000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_SHIFT                    (17U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ17_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_MASK                     (0x00040000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_SHIFT                    (18U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ18_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_MASK                     (0x00080000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_SHIFT                    (19U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ19_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_MASK                     (0x00100000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_SHIFT                    (20U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ20_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_MASK                     (0x00200000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_SHIFT                    (21U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ21_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_MASK                     (0x00400000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_SHIFT                    (22U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ22_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_MASK                     (0x00800000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_SHIFT                    (23U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_NOEVENT                  (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_PENDING                  (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_NACT                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_RAW_IRQ23_SET                      (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RAW_RESETVAL                       (0x00000000U)

/* HL_IRQSTATUS */

#define CSL_CAL_HL_IRQSTATUS_IRQ0_MASK                          (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ0_SHIFT                         (0U)
#define CSL_CAL_HL_IRQSTATUS_IRQ0_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ0_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ0_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ0_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ0_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ1_MASK                          (0x00000002U)
#define CSL_CAL_HL_IRQSTATUS_IRQ1_SHIFT                         (1U)
#define CSL_CAL_HL_IRQSTATUS_IRQ1_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ1_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ1_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ1_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ1_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ2_MASK                          (0x00000004U)
#define CSL_CAL_HL_IRQSTATUS_IRQ2_SHIFT                         (2U)
#define CSL_CAL_HL_IRQSTATUS_IRQ2_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ2_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ2_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ2_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ2_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ3_MASK                          (0x00000008U)
#define CSL_CAL_HL_IRQSTATUS_IRQ3_SHIFT                         (3U)
#define CSL_CAL_HL_IRQSTATUS_IRQ3_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ3_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ3_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ3_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ3_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ4_MASK                          (0x00000010U)
#define CSL_CAL_HL_IRQSTATUS_IRQ4_SHIFT                         (4U)
#define CSL_CAL_HL_IRQSTATUS_IRQ4_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ4_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ4_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ4_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ4_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ5_MASK                          (0x00000020U)
#define CSL_CAL_HL_IRQSTATUS_IRQ5_SHIFT                         (5U)
#define CSL_CAL_HL_IRQSTATUS_IRQ5_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ5_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ5_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ5_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ5_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ6_MASK                          (0x00000040U)
#define CSL_CAL_HL_IRQSTATUS_IRQ6_SHIFT                         (6U)
#define CSL_CAL_HL_IRQSTATUS_IRQ6_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ6_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ6_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ6_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ6_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ7_MASK                          (0x00000080U)
#define CSL_CAL_HL_IRQSTATUS_IRQ7_SHIFT                         (7U)
#define CSL_CAL_HL_IRQSTATUS_IRQ7_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ7_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ7_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ7_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ7_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ8_MASK                          (0x00000100U)
#define CSL_CAL_HL_IRQSTATUS_IRQ8_SHIFT                         (8U)
#define CSL_CAL_HL_IRQSTATUS_IRQ8_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ8_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ8_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ8_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ8_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ9_MASK                          (0x00000200U)
#define CSL_CAL_HL_IRQSTATUS_IRQ9_SHIFT                         (9U)
#define CSL_CAL_HL_IRQSTATUS_IRQ9_RESETVAL                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ9_NOEVENT                       (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ9_PENDING                       (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ9_NACT                          (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ9_CLEAR                         (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ10_MASK                         (0x00000400U)
#define CSL_CAL_HL_IRQSTATUS_IRQ10_SHIFT                        (10U)
#define CSL_CAL_HL_IRQSTATUS_IRQ10_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ10_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ10_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ10_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ10_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ11_MASK                         (0x00000800U)
#define CSL_CAL_HL_IRQSTATUS_IRQ11_SHIFT                        (11U)
#define CSL_CAL_HL_IRQSTATUS_IRQ11_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ11_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ11_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ11_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ11_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ12_MASK                         (0x00001000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ12_SHIFT                        (12U)
#define CSL_CAL_HL_IRQSTATUS_IRQ12_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ12_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ12_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ12_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ12_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ13_MASK                         (0x00002000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ13_SHIFT                        (13U)
#define CSL_CAL_HL_IRQSTATUS_IRQ13_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ13_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ13_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ13_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ13_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ14_MASK                         (0x00004000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ14_SHIFT                        (14U)
#define CSL_CAL_HL_IRQSTATUS_IRQ14_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ14_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ14_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ14_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ14_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ15_MASK                         (0x00008000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ15_SHIFT                        (15U)
#define CSL_CAL_HL_IRQSTATUS_IRQ15_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ15_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ15_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ15_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ15_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ16_MASK                         (0x00010000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ16_SHIFT                        (16U)
#define CSL_CAL_HL_IRQSTATUS_IRQ16_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ16_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ16_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ16_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ16_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ17_MASK                         (0x00020000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ17_SHIFT                        (17U)
#define CSL_CAL_HL_IRQSTATUS_IRQ17_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ17_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ17_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ17_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ17_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ18_MASK                         (0x00040000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ18_SHIFT                        (18U)
#define CSL_CAL_HL_IRQSTATUS_IRQ18_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ18_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ18_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ18_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ18_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ19_MASK                         (0x00080000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ19_SHIFT                        (19U)
#define CSL_CAL_HL_IRQSTATUS_IRQ19_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ19_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ19_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ19_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ19_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ20_MASK                         (0x00100000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ20_SHIFT                        (20U)
#define CSL_CAL_HL_IRQSTATUS_IRQ20_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ20_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ20_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ20_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ20_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ21_MASK                         (0x00200000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ21_SHIFT                        (21U)
#define CSL_CAL_HL_IRQSTATUS_IRQ21_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ21_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ21_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ21_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ21_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ22_MASK                         (0x00400000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ22_SHIFT                        (22U)
#define CSL_CAL_HL_IRQSTATUS_IRQ22_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ22_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ22_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ22_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ22_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_IRQ23_MASK                         (0x00800000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ23_SHIFT                        (23U)
#define CSL_CAL_HL_IRQSTATUS_IRQ23_RESETVAL                     (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ23_NOEVENT                      (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ23_PENDING                      (0x00000001U)
#define CSL_CAL_HL_IRQSTATUS_IRQ23_NACT                         (0x00000000U)
#define CSL_CAL_HL_IRQSTATUS_IRQ23_CLEAR                        (0x00000001U)

#define CSL_CAL_HL_IRQSTATUS_RESETVAL                           (0x00000000U)

/* HL_IRQENABLE_SET */

#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_MASK                      (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_SHIFT                     (0U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ0_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_MASK                      (0x00000002U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_SHIFT                     (1U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ1_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_MASK                      (0x00000004U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_SHIFT                     (2U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ2_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_MASK                      (0x00000008U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_SHIFT                     (3U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ3_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_MASK                      (0x00000010U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_SHIFT                     (4U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ4_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_MASK                      (0x00000020U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_SHIFT                     (5U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ5_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_MASK                      (0x00000040U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_SHIFT                     (6U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ6_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_MASK                      (0x00000080U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_SHIFT                     (7U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ7_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_MASK                      (0x00000100U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_SHIFT                     (8U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ8_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_MASK                      (0x00000200U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_SHIFT                     (9U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_ENABLE                    (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ9_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_MASK                     (0x00000400U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_SHIFT                    (10U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ10_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_MASK                     (0x00000800U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_SHIFT                    (11U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ11_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_MASK                     (0x00001000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_SHIFT                    (12U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ12_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_MASK                     (0x00002000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_SHIFT                    (13U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ13_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_MASK                     (0x00004000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_SHIFT                    (14U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ14_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_MASK                     (0x00008000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_SHIFT                    (15U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ15_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_MASK                     (0x00010000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_SHIFT                    (16U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ16_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_MASK                     (0x00020000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_SHIFT                    (17U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ17_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_MASK                     (0x00040000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_SHIFT                    (18U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ18_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_MASK                     (0x00080000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_SHIFT                    (19U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ19_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_MASK                     (0x00100000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_SHIFT                    (20U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ20_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_MASK                     (0x00200000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_SHIFT                    (21U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ21_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_MASK                     (0x00400000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_SHIFT                    (22U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ22_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_MASK                     (0x00800000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_SHIFT                    (23U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_ENABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_SET_IRQ23_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_SET_RESETVAL                       (0x00000000U)

/* HL_IRQENABLE_CLR */

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_MASK                      (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_SHIFT                     (0U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ0_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_MASK                      (0x00000002U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_SHIFT                     (1U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ1_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_MASK                      (0x00000004U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_SHIFT                     (2U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ2_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_MASK                      (0x00000008U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_SHIFT                     (3U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ3_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_MASK                      (0x00000010U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_SHIFT                     (4U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ4_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_MASK                      (0x00000020U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_SHIFT                     (5U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ5_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_MASK                      (0x00000040U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_SHIFT                     (6U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ6_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_MASK                      (0x00000080U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_SHIFT                     (7U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ7_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_MASK                      (0x00000100U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_SHIFT                     (8U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ8_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_MASK                      (0x00000200U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_SHIFT                     (9U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_RESETVAL                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_NOACTION                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_DISABLE                   (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_DISABLED                  (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ9_ENABLED                   (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_MASK                     (0x00000400U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_SHIFT                    (10U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ10_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_MASK                     (0x00000800U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_SHIFT                    (11U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ11_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_MASK                     (0x00001000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_SHIFT                    (12U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ12_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_MASK                     (0x00002000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_SHIFT                    (13U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ13_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_MASK                     (0x00004000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_SHIFT                    (14U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ14_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_MASK                     (0x00008000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_SHIFT                    (15U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ15_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_MASK                     (0x00010000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_SHIFT                    (16U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ16_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_MASK                     (0x00020000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_SHIFT                    (17U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ17_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_MASK                     (0x00040000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_SHIFT                    (18U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ18_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_MASK                     (0x00080000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_SHIFT                    (19U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ19_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_MASK                     (0x00100000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_SHIFT                    (20U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ20_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_MASK                     (0x00200000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_SHIFT                    (21U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ21_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_MASK                     (0x00400000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_SHIFT                    (22U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ22_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_MASK                     (0x00800000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_SHIFT                    (23U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_RESETVAL                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_NOACTION                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_DISABLE                  (0x00000001U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_DISABLED                 (0x00000000U)
#define CSL_CAL_HL_IRQENABLE_CLR_IRQ23_ENABLED                  (0x00000001U)

#define CSL_CAL_HL_IRQENABLE_CLR_RESETVAL                       (0x00000000U)

/* PIX_PROC */

#define CSL_CAL_PIX_PROC_EXTRACT_MASK                           (0x0000001EU)
#define CSL_CAL_PIX_PROC_EXTRACT_SHIFT                          (1U)
#define CSL_CAL_PIX_PROC_EXTRACT_RESETVAL                       (0x0000000aU)
#define CSL_CAL_PIX_PROC_EXTRACT_MAX                            (0x0000000fU)

#define CSL_CAL_PIX_PROC_DPCMD_MASK                             (0x000003E0U)
#define CSL_CAL_PIX_PROC_DPCMD_SHIFT                            (5U)
#define CSL_CAL_PIX_PROC_DPCMD_RESETVAL                         (0x00000000U)
#define CSL_CAL_PIX_PROC_DPCMD_MAX                              (0x0000001fU)

#define CSL_CAL_PIX_PROC_DPCME_MASK                             (0x0000F800U)
#define CSL_CAL_PIX_PROC_DPCME_SHIFT                            (11U)
#define CSL_CAL_PIX_PROC_DPCME_RESETVAL                         (0x00000000U)
#define CSL_CAL_PIX_PROC_DPCME_MAX                              (0x0000001fU)

#define CSL_CAL_PIX_PROC_PACK_MASK                              (0x00070000U)
#define CSL_CAL_PIX_PROC_PACK_SHIFT                             (16U)
#define CSL_CAL_PIX_PROC_PACK_RESETVAL                          (0x00000005U)
#define CSL_CAL_PIX_PROC_PACK_B8                                (0x00000000U)
#define CSL_CAL_PIX_PROC_PACK_B10_MIPI                          (0x00000002U)
#define CSL_CAL_PIX_PROC_PACK_B12                               (0x00000003U)
#define CSL_CAL_PIX_PROC_PACK_B12_MIPI                          (0x00000004U)
#define CSL_CAL_PIX_PROC_PACK_B16                               (0x00000005U)
#define CSL_CAL_PIX_PROC_PACK_ARGB                              (0x00000006U)

#define CSL_CAL_PIX_PROC_CPORT_MASK                             (0x00F80000U)
#define CSL_CAL_PIX_PROC_CPORT_SHIFT                            (19U)
#define CSL_CAL_PIX_PROC_CPORT_RESETVAL                         (0x00000000U)
#define CSL_CAL_PIX_PROC_CPORT_MAX                              (0x0000001fU)

#define CSL_CAL_PIX_PROC_EN_MASK                                (0x00000001U)
#define CSL_CAL_PIX_PROC_EN_SHIFT                               (0U)
#define CSL_CAL_PIX_PROC_EN_RESETVAL                            (0x00000000U)
#define CSL_CAL_PIX_PROC_EN_DIS                                 (0x00000000U)
#define CSL_CAL_PIX_PROC_EN_EN                                  (0x00000001U)

#define CSL_CAL_PIX_PROC_RESETVAL                               (0x00050014U)

/* CTRL */

#define CSL_CAL_CTRL_TAGCNT_MASK                                (0x0000001EU)
#define CSL_CAL_CTRL_TAGCNT_SHIFT                               (1U)
#define CSL_CAL_CTRL_TAGCNT_RESETVAL                            (0x0000000fU)
#define CSL_CAL_CTRL_TAGCNT_MAX                                 (0x0000000fU)

#define CSL_CAL_CTRL_BURSTSIZE_MASK                             (0x00000060U)
#define CSL_CAL_CTRL_BURSTSIZE_SHIFT                            (5U)
#define CSL_CAL_CTRL_BURSTSIZE_RESETVAL                         (0x00000003U)
#define CSL_CAL_CTRL_BURSTSIZE_BURST16                          (0x00000000U)
#define CSL_CAL_CTRL_BURSTSIZE_BURST32                          (0x00000001U)
#define CSL_CAL_CTRL_BURSTSIZE_BURST64                          (0x00000002U)
#define CSL_CAL_CTRL_BURSTSIZE_BURST128                         (0x00000003U)

#define CSL_CAL_CTRL_LL_FORCE_STATE_MASK                        (0x00001F80U)
#define CSL_CAL_CTRL_LL_FORCE_STATE_SHIFT                       (7U)
#define CSL_CAL_CTRL_LL_FORCE_STATE_RESETVAL                    (0x00000000U)
#define CSL_CAL_CTRL_LL_FORCE_STATE_MAX                         (0x0000003fU)

#define CSL_CAL_CTRL_POSTED_WRITES_MASK                         (0x00000001U)
#define CSL_CAL_CTRL_POSTED_WRITES_SHIFT                        (0U)
#define CSL_CAL_CTRL_POSTED_WRITES_RESETVAL                     (0x00000000U)
#define CSL_CAL_CTRL_POSTED_WRITES_NONPOSTED                    (0x00000000U)
#define CSL_CAL_CTRL_POSTED_WRITES_POSTED                       (0x00000001U)

#define CSL_CAL_CTRL_MFLAG_MASK                                 (0x001FE000U)
#define CSL_CAL_CTRL_MFLAG_SHIFT                                (13U)
#define CSL_CAL_CTRL_MFLAG_RESETVAL                             (0x000000ffU)
#define CSL_CAL_CTRL_MFLAG_MAX                                  (0x000000ffU)

#define CSL_CAL_CTRL_RESETVAL                                   (0x001fe07eU)

/* VPORT_CTRL1 */

#define CSL_CAL_VPORT_CTRL1_PCLK_MASK                           (0x0001FFFFU)
#define CSL_CAL_VPORT_CTRL1_PCLK_SHIFT                          (0U)
#define CSL_CAL_VPORT_CTRL1_PCLK_RESETVAL                       (0x00000000U)
#define CSL_CAL_VPORT_CTRL1_PCLK_MAX                            (0x0001ffffU)

#define CSL_CAL_VPORT_CTRL1_XBLK_MASK                           (0x01FE0000U)
#define CSL_CAL_VPORT_CTRL1_XBLK_SHIFT                          (17U)
#define CSL_CAL_VPORT_CTRL1_XBLK_RESETVAL                       (0x00000000U)
#define CSL_CAL_VPORT_CTRL1_XBLK_MAX                            (0x000000ffU)

#define CSL_CAL_VPORT_CTRL1_YBLK_MASK                           (0x7E000000U)
#define CSL_CAL_VPORT_CTRL1_YBLK_SHIFT                          (25U)
#define CSL_CAL_VPORT_CTRL1_YBLK_RESETVAL                       (0x00000000U)
#define CSL_CAL_VPORT_CTRL1_YBLK_MAX                            (0x0000003fU)

#define CSL_CAL_VPORT_CTRL1_WIDTH_MASK                          (0x80000000U)
#define CSL_CAL_VPORT_CTRL1_WIDTH_SHIFT                         (31U)
#define CSL_CAL_VPORT_CTRL1_WIDTH_RESETVAL                      (0x00000000U)
#define CSL_CAL_VPORT_CTRL1_WIDTH_ONE                           (0x00000000U)
#define CSL_CAL_VPORT_CTRL1_WIDTH_TWO                           (0x00000001U)

#define CSL_CAL_VPORT_CTRL1_RESETVAL                            (0x00000000U)

/* VPORT_CTRL2 */

#define CSL_CAL_VPORT_CTRL2_CPORT_MASK                          (0x0000001FU)
#define CSL_CAL_VPORT_CTRL2_CPORT_SHIFT                         (0U)
#define CSL_CAL_VPORT_CTRL2_CPORT_RESETVAL                      (0x00000000U)
#define CSL_CAL_VPORT_CTRL2_CPORT_MAX                           (0x0000001fU)

#define CSL_CAL_VPORT_CTRL2_RDY_THR_MASK                        (0xFFFC0000U)
#define CSL_CAL_VPORT_CTRL2_RDY_THR_SHIFT                       (18U)
#define CSL_CAL_VPORT_CTRL2_RDY_THR_RESETVAL                    (0x00000000U)
#define CSL_CAL_VPORT_CTRL2_RDY_THR_MAX                         (0x00003fffU)

#define CSL_CAL_VPORT_CTRL2_FSM_RESET_MASK                      (0x00020000U)
#define CSL_CAL_VPORT_CTRL2_FSM_RESET_SHIFT                     (17U)
#define CSL_CAL_VPORT_CTRL2_FSM_RESET_RESETVAL                  (0x00000000U)
#define CSL_CAL_VPORT_CTRL2_FSM_RESET_NOEFFECT                  (0x00000000U)
#define CSL_CAL_VPORT_CTRL2_FSM_RESET_RESET                     (0x00000001U)

#define CSL_CAL_VPORT_CTRL2_FS_RESETS_MASK                      (0x00010000U)
#define CSL_CAL_VPORT_CTRL2_FS_RESETS_SHIFT                     (16U)
#define CSL_CAL_VPORT_CTRL2_FS_RESETS_RESETVAL                  (0x00000001U)
#define CSL_CAL_VPORT_CTRL2_FS_RESETS_NO                        (0x00000000U)
#define CSL_CAL_VPORT_CTRL2_FS_RESETS_YES                       (0x00000001U)

#define CSL_CAL_VPORT_CTRL2_RESETVAL                            (0x00010000U)

/* BYS_CTRL1 */

#define CSL_CAL_BYS_CTRL1_XBLK_MASK                             (0x01FE0000U)
#define CSL_CAL_BYS_CTRL1_XBLK_SHIFT                            (17U)
#define CSL_CAL_BYS_CTRL1_XBLK_RESETVAL                         (0x00000004U)
#define CSL_CAL_BYS_CTRL1_XBLK_MAX                              (0x000000ffU)

#define CSL_CAL_BYS_CTRL1_YBLK_MASK                             (0x7E000000U)
#define CSL_CAL_BYS_CTRL1_YBLK_SHIFT                            (25U)
#define CSL_CAL_BYS_CTRL1_YBLK_RESETVAL                         (0x00000004U)
#define CSL_CAL_BYS_CTRL1_YBLK_MAX                              (0x0000003fU)

#define CSL_CAL_BYS_CTRL1_PCLK_MASK                             (0x0001FFFFU)
#define CSL_CAL_BYS_CTRL1_PCLK_SHIFT                            (0U)
#define CSL_CAL_BYS_CTRL1_PCLK_RESETVAL                         (0x00000000U)
#define CSL_CAL_BYS_CTRL1_PCLK_MAX                              (0x0001ffffU)

#define CSL_CAL_BYS_CTRL1_BYSINEN_MASK                          (0x80000000U)
#define CSL_CAL_BYS_CTRL1_BYSINEN_SHIFT                         (31U)
#define CSL_CAL_BYS_CTRL1_BYSINEN_RESETVAL                      (0x00000000U)
#define CSL_CAL_BYS_CTRL1_BYSINEN_DIS                           (0x00000000U)
#define CSL_CAL_BYS_CTRL1_BYSINEN_EN                            (0x00000001U)

#define CSL_CAL_BYS_CTRL1_RESETVAL                              (0x08080000U)

/* BYS_CTRL2 */

#define CSL_CAL_BYS_CTRL2_CPORTIN_MASK                          (0x0000001FU)
#define CSL_CAL_BYS_CTRL2_CPORTIN_SHIFT                         (0U)
#define CSL_CAL_BYS_CTRL2_CPORTIN_RESETVAL                      (0x00000000U)
#define CSL_CAL_BYS_CTRL2_CPORTIN_MAX                           (0x0000001fU)

#define CSL_CAL_BYS_CTRL2_CPORTOUT_MASK                         (0x000003E0U)
#define CSL_CAL_BYS_CTRL2_CPORTOUT_SHIFT                        (5U)
#define CSL_CAL_BYS_CTRL2_CPORTOUT_RESETVAL                     (0x00000000U)
#define CSL_CAL_BYS_CTRL2_CPORTOUT_MAX                          (0x0000001fU)

#define CSL_CAL_BYS_CTRL2_DUPLICATEDDATA_MASK                   (0x00000400U)
#define CSL_CAL_BYS_CTRL2_DUPLICATEDDATA_SHIFT                  (10U)
#define CSL_CAL_BYS_CTRL2_DUPLICATEDDATA_RESETVAL               (0x00000000U)
#define CSL_CAL_BYS_CTRL2_DUPLICATEDDATA_NO                     (0x00000000U)
#define CSL_CAL_BYS_CTRL2_DUPLICATEDDATA_YES                    (0x00000001U)

#define CSL_CAL_BYS_CTRL2_RESETVAL                              (0x00000000U)

/* RD_DMA_CTRL */

#define CSL_CAL_RD_DMA_CTRL_GO_MASK                             (0x00000001U)
#define CSL_CAL_RD_DMA_CTRL_GO_SHIFT                            (0U)
#define CSL_CAL_RD_DMA_CTRL_GO_RESETVAL                         (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_GO_DIS                              (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_GO_EN                               (0x00000001U)
#define CSL_CAL_RD_DMA_CTRL_GO_IDLE                             (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_GO_BUSY                             (0x00000001U)

#define CSL_CAL_RD_DMA_CTRL_BW_LIMITER_MASK                     (0x000007FCU)
#define CSL_CAL_RD_DMA_CTRL_BW_LIMITER_SHIFT                    (2U)
#define CSL_CAL_RD_DMA_CTRL_BW_LIMITER_RESETVAL                 (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_BW_LIMITER_MAX                      (0x000001ffU)

#define CSL_CAL_RD_DMA_CTRL_INIT_MASK                           (0x00000002U)
#define CSL_CAL_RD_DMA_CTRL_INIT_SHIFT                          (1U)
#define CSL_CAL_RD_DMA_CTRL_INIT_RESETVAL                       (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_INIT_DIS                            (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_INIT_EN                             (0x00000001U)

#define CSL_CAL_RD_DMA_CTRL_OCP_TAG_CNT_MASK                    (0x00007800U)
#define CSL_CAL_RD_DMA_CTRL_OCP_TAG_CNT_SHIFT                   (11U)
#define CSL_CAL_RD_DMA_CTRL_OCP_TAG_CNT_RESETVAL                (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_OCP_TAG_CNT_MAX                     (0x0000000fU)

#define CSL_CAL_RD_DMA_CTRL_PCLK_MASK                           (0xFFFF8000U)
#define CSL_CAL_RD_DMA_CTRL_PCLK_SHIFT                          (15U)
#define CSL_CAL_RD_DMA_CTRL_PCLK_RESETVAL                       (0x00000000U)
#define CSL_CAL_RD_DMA_CTRL_PCLK_MAX                            (0x0001ffffU)

#define CSL_CAL_RD_DMA_CTRL_RESETVAL                            (0x00000000U)

/* RD_DMA_PIX_ADDR */

#define CSL_CAL_RD_DMA_PIX_ADDR_ADDR_MASK                       (0xFFFFFFF8U)
#define CSL_CAL_RD_DMA_PIX_ADDR_ADDR_SHIFT                      (3U)
#define CSL_CAL_RD_DMA_PIX_ADDR_ADDR_RESETVAL                   (0x00000000U)
#define CSL_CAL_RD_DMA_PIX_ADDR_ADDR_MAX                        (0x1fffffffU)

#define CSL_CAL_RD_DMA_PIX_ADDR_RESETVAL                        (0x00000000U)

/* RD_DMA_PIX_OFST */

#define CSL_CAL_RD_DMA_PIX_OFST_OFST_MASK                       (0xFFFFFFF0U)
#define CSL_CAL_RD_DMA_PIX_OFST_OFST_SHIFT                      (4U)
#define CSL_CAL_RD_DMA_PIX_OFST_OFST_RESETVAL                   (0x00000000U)
#define CSL_CAL_RD_DMA_PIX_OFST_OFST_MAX                        (0x0fffffffU)

#define CSL_CAL_RD_DMA_PIX_OFST_RESETVAL                        (0x00000000U)

/* RD_DMA_XSIZE */

#define CSL_CAL_RD_DMA_XSIZE_XSIZE_MASK                         (0xFFF80000U)
#define CSL_CAL_RD_DMA_XSIZE_XSIZE_SHIFT                        (19U)
#define CSL_CAL_RD_DMA_XSIZE_XSIZE_RESETVAL                     (0x00000000U)
#define CSL_CAL_RD_DMA_XSIZE_XSIZE_MAX                          (0x00001fffU)

#define CSL_CAL_RD_DMA_XSIZE_RESETVAL                           (0x00000000U)

/* RD_DMA_YSIZE */

#define CSL_CAL_RD_DMA_YSIZE_YSIZE_MASK                         (0x3FFF0000U)
#define CSL_CAL_RD_DMA_YSIZE_YSIZE_SHIFT                        (16U)
#define CSL_CAL_RD_DMA_YSIZE_YSIZE_RESETVAL                     (0x00000000U)
#define CSL_CAL_RD_DMA_YSIZE_YSIZE_MAX                          (0x00003fffU)

#define CSL_CAL_RD_DMA_YSIZE_RESETVAL                           (0x00000000U)

/* RD_DMA_INIT_ADDR */

#define CSL_CAL_RD_DMA_INIT_ADDR_ADDR_MASK                      (0xFFFFFFF8U)
#define CSL_CAL_RD_DMA_INIT_ADDR_ADDR_SHIFT                     (3U)
#define CSL_CAL_RD_DMA_INIT_ADDR_ADDR_RESETVAL                  (0x00000000U)
#define CSL_CAL_RD_DMA_INIT_ADDR_ADDR_MAX                       (0x1fffffffU)

#define CSL_CAL_RD_DMA_INIT_ADDR_RESETVAL                       (0x00000000U)

/* RD_DMA_INIT_OFST */

#define CSL_CAL_RD_DMA_INIT_OFST_OFST_MASK                      (0xFFFFFFF8U)
#define CSL_CAL_RD_DMA_INIT_OFST_OFST_SHIFT                     (3U)
#define CSL_CAL_RD_DMA_INIT_OFST_OFST_RESETVAL                  (0x00000000U)
#define CSL_CAL_RD_DMA_INIT_OFST_OFST_MAX                       (0x1fffffffU)

#define CSL_CAL_RD_DMA_INIT_OFST_RESETVAL                       (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
