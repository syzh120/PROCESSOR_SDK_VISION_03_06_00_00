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
#ifndef CSLR_VPDMA_H_
#define CSLR_VPDMA_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for mmr_generated_address_block
**************************************************************************/
typedef struct {
    volatile Uint32 PID;
    volatile Uint32 LIST_ADDR;
    volatile Uint32 LIST_ATTR;
    volatile Uint32 LIST_STAT_SYNC;
    volatile Uint8  RSVD0[8];
    volatile Uint32 BG_RGB;
    volatile Uint32 BG_YUV;
    volatile Uint8  RSVD1[16];
    volatile Uint32 SETUP;
    volatile Uint32 MAX_SIZE1;
    volatile Uint32 MAX_SIZE2;
    volatile Uint32 MAX_SIZE3;
    volatile Uint32 INT0_CHANNEL0_INT_STAT;
    volatile Uint32 INT0_CHANNEL0_INT_MASK;
    volatile Uint32 INT0_CHANNEL1_INT_STAT;
    volatile Uint32 INT0_CHANNEL1_INT_MASK;
    volatile Uint32 INT0_CHANNEL2_INT_STAT;
    volatile Uint32 INT0_CHANNEL2_INT_MASK;
    volatile Uint32 INT0_CHANNEL3_INT_STAT;
    volatile Uint32 INT0_CHANNEL3_INT_MASK;
    volatile Uint32 INT0_CHANNEL4_INT_STAT;
    volatile Uint32 INT0_CHANNEL4_INT_MASK;
    volatile Uint32 INT0_CHANNEL5_INT_STAT;
    volatile Uint32 INT0_CHANNEL5_INT_MASK;
    volatile Uint8  RSVD2[8];
    volatile Uint32 INT0_CLIENT0_INT_STAT;
    volatile Uint32 INT0_CLIENT0_INT_MASK;
    volatile Uint8  RSVD3[8];
    volatile Uint32 INT0_LIST0_INT_STAT;
    volatile Uint32 INT0_LIST0_INT_MASK;
    volatile Uint32 INT1_CHANNEL0_INT_STAT;
    volatile Uint32 INT1_CHANNEL0_INT_MASK;
    volatile Uint32 INT1_CHANNEL1_INT_STAT;
    volatile Uint32 INT1_CHANNEL1_INT_MASK;
    volatile Uint32 INT1_CHANNEL2_INT_STAT;
    volatile Uint32 INT1_CHANNEL2_INT_MASK;
    volatile Uint32 INT1_CHANNEL3_INT_STAT;
    volatile Uint32 INT1_CHANNEL3_INT_MASK;
    volatile Uint32 INT1_CHANNEL4_INT_STAT;
    volatile Uint32 INT1_CHANNEL4_INT_MASK;
    volatile Uint32 INT1_CHANNEL5_INT_STAT;
    volatile Uint32 INT1_CHANNEL5_INT_MASK;
    volatile Uint8  RSVD4[8];
    volatile Uint32 INT1_CLIENT0_INT_STAT;
    volatile Uint32 INT1_CLIENT0_INT_MASK;
    volatile Uint8  RSVD5[8];
    volatile Uint32 INT1_LIST0_INT_STAT;
    volatile Uint32 INT1_LIST0_INT_MASK;
    volatile Uint32 INT2_CHANNEL0_INT_STAT;
    volatile Uint32 INT2_CHANNEL0_INT_MASK;
    volatile Uint32 INT2_CHANNEL1_INT_STAT;
    volatile Uint32 INT2_CHANNEL1_INT_MASK;
    volatile Uint32 INT2_CHANNEL2_INT_STAT;
    volatile Uint32 INT2_CHANNEL2_INT_MASK;
    volatile Uint32 INT2_CHANNEL3_INT_STAT;
    volatile Uint32 INT2_CHANNEL3_INT_MASK;
    volatile Uint32 INT2_CHANNEL4_INT_STAT;
    volatile Uint32 INT2_CHANNEL4_INT_MASK;
    volatile Uint32 INT2_CHANNEL5_INT_STAT;
    volatile Uint32 INT2_CHANNEL5_INT_MASK;
    volatile Uint8  RSVD6[8];
    volatile Uint32 INT2_CLIENT0_INT_STAT;
    volatile Uint32 INT2_CLIENT0_INT_MASK;
    volatile Uint8  RSVD7[8];
    volatile Uint32 INT2_LIST0_INT_STAT;
    volatile Uint32 INT2_LIST0_INT_MASK;
    volatile Uint32 INT3_CHANNEL0_INT_STAT;
    volatile Uint32 INT3_CHANNEL0_INT_MASK;
    volatile Uint32 INT3_CHANNEL1_INT_STAT;
    volatile Uint32 INT3_CHANNEL1_INT_MASK;
    volatile Uint32 INT3_CHANNEL2_INT_STAT;
    volatile Uint32 INT3_CHANNEL2_INT_MASK;
    volatile Uint32 INT3_CHANNEL3_INT_STAT;
    volatile Uint32 INT3_CHANNEL3_INT_MASK;
    volatile Uint32 INT3_CHANNEL4_INT_STAT;
    volatile Uint32 INT3_CHANNEL4_INT_MASK;
    volatile Uint32 INT3_CHANNEL5_INT_STAT;
    volatile Uint32 INT3_CHANNEL5_INT_MASK;
    volatile Uint8  RSVD8[8];
    volatile Uint32 INT3_CLIENT0_INT_STAT;
    volatile Uint32 INT3_CLIENT0_INT_MASK;
    volatile Uint8  RSVD9[8];
    volatile Uint32 INT3_LIST0_INT_STAT;
    volatile Uint32 INT3_LIST0_INT_MASK;
    volatile Uint8  RSVD10[128];
    volatile Uint32 PERF_MON0;
    volatile Uint32 PERF_MON1;
    volatile Uint32 PERF_MON2;
    volatile Uint32 PERF_MON3;
    volatile Uint32 PERF_MON4;
    volatile Uint32 PERF_MON5;
    volatile Uint32 PERF_MON6;
    volatile Uint32 PERF_MON7;
    volatile Uint32 PERF_MON8;
    volatile Uint32 PERF_MON9;
    volatile Uint32 PERF_MON10;
    volatile Uint32 PERF_MON11;
    volatile Uint32 PERF_MON12;
    volatile Uint32 PERF_MON13;
    volatile Uint32 PERF_MON14;
    volatile Uint32 PERF_MON15;
    volatile Uint32 PERF_MON16;
    volatile Uint32 PERF_MON17;
    volatile Uint32 PERF_MON18;
    volatile Uint32 PERF_MON19;
    volatile Uint32 PERF_MON20;
    volatile Uint32 PERF_MON21;
    volatile Uint32 PERF_MON22;
    volatile Uint32 PERF_MON23;
    volatile Uint32 PERF_MON24;
    volatile Uint32 PERF_MON25;
    volatile Uint32 PERF_MON26;
    volatile Uint32 PERF_MON27;
    volatile Uint32 PERF_MON28;
    volatile Uint32 PERF_MON29;
    volatile Uint32 PERF_MON30;
    volatile Uint32 PERF_MON31;
    volatile Uint32 PERF_MON32;
    volatile Uint32 PERF_MON33;
    volatile Uint32 PERF_MON34;
    volatile Uint32 PERF_MON35;
    volatile Uint32 PERF_MON36;
    volatile Uint32 PERF_MON37;
    volatile Uint32 PERF_MON38;
    volatile Uint32 PERF_MON39;
    volatile Uint32 PERF_MON40;
    volatile Uint32 PERF_MON41;
    volatile Uint32 PERF_MON42;
    volatile Uint32 PERF_MON43;
    volatile Uint32 PERF_MON44;
    volatile Uint32 PERF_MON45;
    volatile Uint32 PERF_MON46;
    volatile Uint32 PERF_MON47;
    volatile Uint32 PERF_MON48;
    volatile Uint32 PERF_MON49;
    volatile Uint32 PERF_MON50;
    volatile Uint32 PERF_MON51;
    volatile Uint32 PERF_MON52;
    volatile Uint32 PERF_MON53;
    volatile Uint32 PERF_MON54;
    volatile Uint32 PERF_MON55;
    volatile Uint32 PERF_MON56;
    volatile Uint32 PERF_MON57;
    volatile Uint32 PERF_MON58;
    volatile Uint32 PERF_MON59;
    volatile Uint32 PERF_MON60;
    volatile Uint32 PERF_MON61;
    volatile Uint8  RSVD11[8];
    volatile Uint32 DEI_HQ_1_CHROMA_CSTAT;
    volatile Uint32 DEI_HQ_1_LUMA_CSTAT;
    volatile Uint32 DEI_HQ_2_LUMA_CSTAT;
    volatile Uint32 DEI_HQ_2_CHROMA_CSTAT;
    volatile Uint32 DEI_HQ_3_LUMA_CSTAT;
    volatile Uint32 DEI_HQ_3_CHROMA_CSTAT;
    volatile Uint8  RSVD12[24];
    volatile Uint32 DEI_HQ_MV_IN_CSTAT;
    volatile Uint8  RSVD13[8];
    volatile Uint32 DEI_HQ_MV_OUT_CSTAT;
    volatile Uint8  RSVD14[72];
    volatile Uint32 VIP1_LO_Y_CSTAT;
    volatile Uint32 VIP1_LO_UV_CSTAT;
    volatile Uint32 VIP1_UP_Y_CSTAT;
    volatile Uint32 VIP1_UP_UV_CSTAT;
    volatile Uint32 VIP2_LO_Y_CSTAT;
    volatile Uint32 VIP2_LO_UV_CSTAT;
    volatile Uint32 VIP2_UP_Y_CSTAT;
    volatile Uint32 VIP2_UP_UV_CSTAT;
    volatile Uint8  RSVD15[40];
    volatile Uint32 VPI_CTL_CSTAT;
    volatile Uint8  RSVD16[20];
    volatile Uint32 VIP1_ANC_A_CSTAT;
    volatile Uint32 VIP1_ANC_B_CSTAT;
    volatile Uint32 VIP2_ANC_A_CSTAT;
    volatile Uint32 VIP2_ANC_B_CSTAT;
} CSL_VpdmaRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_VPDMA_PID                                           (0x0U)
#define CSL_VPDMA_LIST_ADDR                                     (0x4U)
#define CSL_VPDMA_LIST_ATTR                                     (0x8U)
#define CSL_VPDMA_LIST_STAT_SYNC                                (0xCU)
#define CSL_VPDMA_BG_RGB                                        (0x18U)
#define CSL_VPDMA_BG_YUV                                        (0x1CU)
#define CSL_VPDMA_SETUP                                         (0x30U)
#define CSL_VPDMA_MAX_SIZE1                                     (0x34U)
#define CSL_VPDMA_MAX_SIZE2                                     (0x38U)
#define CSL_VPDMA_MAX_SIZE3                                     (0x3CU)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT                        (0x40U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK                        (0x44U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT                        (0x48U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK                        (0x4CU)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT                        (0x50U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK                        (0x54U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT                        (0x58U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK                        (0x5CU)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT                        (0x60U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK                        (0x64U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT                        (0x68U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK                        (0x6CU)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT                         (0x78U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK                         (0x7CU)
#define CSL_VPDMA_INT0_LIST0_INT_STAT                           (0x88U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK                           (0x8CU)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT                        (0x90U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK                        (0x94U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT                        (0x98U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK                        (0x9CU)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT                        (0xA0U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK                        (0xA4U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT                        (0xA8U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK                        (0xACU)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT                        (0xB0U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK                        (0xB4U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT                        (0xB8U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK                        (0xBCU)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT                         (0xC8U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK                         (0xCCU)
#define CSL_VPDMA_INT1_LIST0_INT_STAT                           (0xD8U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK                           (0xDCU)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT                        (0xE0U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK                        (0xE4U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT                        (0xE8U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK                        (0xECU)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT                        (0xF0U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK                        (0xF4U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT                        (0xF8U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK                        (0xFCU)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT                        (0x100U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK                        (0x104U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT                        (0x108U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK                        (0x10CU)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT                         (0x118U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK                         (0x11CU)
#define CSL_VPDMA_INT2_LIST0_INT_STAT                           (0x128U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK                           (0x12CU)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT                        (0x130U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK                        (0x134U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT                        (0x138U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK                        (0x13CU)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT                        (0x140U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK                        (0x144U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT                        (0x148U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK                        (0x14CU)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT                        (0x150U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK                        (0x154U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT                        (0x158U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK                        (0x15CU)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT                         (0x168U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK                         (0x16CU)
#define CSL_VPDMA_INT3_LIST0_INT_STAT                           (0x178U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK                           (0x17CU)
#define CSL_VPDMA_PERF_MON0                                     (0x200U)
#define CSL_VPDMA_PERF_MON1                                     (0x204U)
#define CSL_VPDMA_PERF_MON2                                     (0x208U)
#define CSL_VPDMA_PERF_MON3                                     (0x20CU)
#define CSL_VPDMA_PERF_MON4                                     (0x210U)
#define CSL_VPDMA_PERF_MON5                                     (0x214U)
#define CSL_VPDMA_PERF_MON6                                     (0x218U)
#define CSL_VPDMA_PERF_MON7                                     (0x21CU)
#define CSL_VPDMA_PERF_MON8                                     (0x220U)
#define CSL_VPDMA_PERF_MON9                                     (0x224U)
#define CSL_VPDMA_PERF_MON10                                    (0x228U)
#define CSL_VPDMA_PERF_MON11                                    (0x22CU)
#define CSL_VPDMA_PERF_MON12                                    (0x230U)
#define CSL_VPDMA_PERF_MON13                                    (0x234U)
#define CSL_VPDMA_PERF_MON14                                    (0x238U)
#define CSL_VPDMA_PERF_MON15                                    (0x23CU)
#define CSL_VPDMA_PERF_MON16                                    (0x240U)
#define CSL_VPDMA_PERF_MON17                                    (0x244U)
#define CSL_VPDMA_PERF_MON18                                    (0x248U)
#define CSL_VPDMA_PERF_MON19                                    (0x24CU)
#define CSL_VPDMA_PERF_MON20                                    (0x250U)
#define CSL_VPDMA_PERF_MON21                                    (0x254U)
#define CSL_VPDMA_PERF_MON22                                    (0x258U)
#define CSL_VPDMA_PERF_MON23                                    (0x25CU)
#define CSL_VPDMA_PERF_MON24                                    (0x260U)
#define CSL_VPDMA_PERF_MON25                                    (0x264U)
#define CSL_VPDMA_PERF_MON26                                    (0x268U)
#define CSL_VPDMA_PERF_MON27                                    (0x26CU)
#define CSL_VPDMA_PERF_MON28                                    (0x270U)
#define CSL_VPDMA_PERF_MON29                                    (0x274U)
#define CSL_VPDMA_PERF_MON30                                    (0x278U)
#define CSL_VPDMA_PERF_MON31                                    (0x27CU)
#define CSL_VPDMA_PERF_MON32                                    (0x280U)
#define CSL_VPDMA_PERF_MON33                                    (0x284U)
#define CSL_VPDMA_PERF_MON34                                    (0x288U)
#define CSL_VPDMA_PERF_MON35                                    (0x28CU)
#define CSL_VPDMA_PERF_MON36                                    (0x290U)
#define CSL_VPDMA_PERF_MON37                                    (0x294U)
#define CSL_VPDMA_PERF_MON38                                    (0x298U)
#define CSL_VPDMA_PERF_MON39                                    (0x29CU)
#define CSL_VPDMA_PERF_MON40                                    (0x2A0U)
#define CSL_VPDMA_PERF_MON41                                    (0x2A4U)
#define CSL_VPDMA_PERF_MON42                                    (0x2A8U)
#define CSL_VPDMA_PERF_MON43                                    (0x2ACU)
#define CSL_VPDMA_PERF_MON44                                    (0x2B0U)
#define CSL_VPDMA_PERF_MON45                                    (0x2B4U)
#define CSL_VPDMA_PERF_MON46                                    (0x2B8U)
#define CSL_VPDMA_PERF_MON47                                    (0x2BCU)
#define CSL_VPDMA_PERF_MON48                                    (0x2C0U)
#define CSL_VPDMA_PERF_MON49                                    (0x2C4U)
#define CSL_VPDMA_PERF_MON50                                    (0x2C8U)
#define CSL_VPDMA_PERF_MON51                                    (0x2CCU)
#define CSL_VPDMA_PERF_MON52                                    (0x2D0U)
#define CSL_VPDMA_PERF_MON53                                    (0x2D4U)
#define CSL_VPDMA_PERF_MON54                                    (0x2D8U)
#define CSL_VPDMA_PERF_MON55                                    (0x2DCU)
#define CSL_VPDMA_PERF_MON56                                    (0x2E0U)
#define CSL_VPDMA_PERF_MON57                                    (0x2E4U)
#define CSL_VPDMA_PERF_MON58                                    (0x2E8U)
#define CSL_VPDMA_PERF_MON59                                    (0x2ECU)
#define CSL_VPDMA_PERF_MON60                                    (0x2F0U)
#define CSL_VPDMA_PERF_MON61                                    (0x2F4U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT                         (0x300U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT                           (0x304U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT                           (0x308U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT                         (0x30CU)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT                           (0x310U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT                         (0x314U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT                            (0x330U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT                           (0x33CU)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT                               (0x388U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT                              (0x38CU)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT                               (0x390U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT                              (0x394U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT                               (0x398U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT                              (0x39CU)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT                               (0x3A0U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT                              (0x3A4U)
#define CSL_VPDMA_VPI_CTL_CSTAT                                 (0x3D0U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT                              (0x3E8U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT                              (0x3ECU)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT                              (0x3F0U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT                              (0x3F4U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* PID */

#define CSL_VPDMA_PID_FUNC_MASK                                 (0x3FFF0000U)
#define CSL_VPDMA_PID_FUNC_SHIFT                                (16U)
#define CSL_VPDMA_PID_FUNC_RESETVAL                             (0x00000d00U)
#define CSL_VPDMA_PID_FUNC_MAX                                  (0x00003fffU)

#define CSL_VPDMA_PID_MAJOR_MASK                                (0x00000700U)
#define CSL_VPDMA_PID_MAJOR_SHIFT                               (8U)
#define CSL_VPDMA_PID_MAJOR_RESETVAL                            (0x00000001U)
#define CSL_VPDMA_PID_MAJOR_MAX                                 (0x00000007U)

#define CSL_VPDMA_PID_MINOR_MASK                                (0x0000003FU)
#define CSL_VPDMA_PID_MINOR_SHIFT                               (0U)
#define CSL_VPDMA_PID_MINOR_RESETVAL                            (0x00000000U)
#define CSL_VPDMA_PID_MINOR_MAX                                 (0x0000003fU)

#define CSL_VPDMA_PID_RTL_MASK                                  (0x0000F800U)
#define CSL_VPDMA_PID_RTL_SHIFT                                 (11U)
#define CSL_VPDMA_PID_RTL_RESETVAL                              (0x00000001U)
#define CSL_VPDMA_PID_RTL_MAX                                   (0x0000001fU)

#define CSL_VPDMA_PID_SCHEME_MASK                               (0xC0000000U)
#define CSL_VPDMA_PID_SCHEME_SHIFT                              (30U)
#define CSL_VPDMA_PID_SCHEME_RESETVAL                           (0x00000001U)
#define CSL_VPDMA_PID_SCHEME_MAX                                (0x00000003U)

#define CSL_VPDMA_PID_VPDMA_ACCESS_TYPE_MASK                    (0x00000040U)
#define CSL_VPDMA_PID_VPDMA_ACCESS_TYPE_SHIFT                   (6U)
#define CSL_VPDMA_PID_VPDMA_ACCESS_TYPE_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PID_VPDMA_ACCESS_TYPE_MAX                     (0x00000001U)

#define CSL_VPDMA_PID_VPDMA_LOAD_COMPLETE_MASK                  (0x00000080U)
#define CSL_VPDMA_PID_VPDMA_LOAD_COMPLETE_SHIFT                 (7U)
#define CSL_VPDMA_PID_VPDMA_LOAD_COMPLETE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PID_VPDMA_LOAD_COMPLETE_MAX                   (0x00000001U)

#define CSL_VPDMA_PID_RESETVAL                                  (0x4d000900U)

/* LIST_ADDR */

#define CSL_VPDMA_LIST_ADDR_LIST_ADDR_MASK                      (0xFFFFFFFFU)
#define CSL_VPDMA_LIST_ADDR_LIST_ADDR_SHIFT                     (0U)
#define CSL_VPDMA_LIST_ADDR_LIST_ADDR_RESETVAL                  (0x00000000U)
#define CSL_VPDMA_LIST_ADDR_LIST_ADDR_MAX                       (0xffffffffU)

#define CSL_VPDMA_LIST_ADDR_RESETVAL                            (0x00000000U)

/* LIST_ATTR */

#define CSL_VPDMA_LIST_ATTR_LIST_NUM_MASK                       (0x07000000U)
#define CSL_VPDMA_LIST_ATTR_LIST_NUM_SHIFT                      (24U)
#define CSL_VPDMA_LIST_ATTR_LIST_NUM_RESETVAL                   (0x00000000U)
#define CSL_VPDMA_LIST_ATTR_LIST_NUM_MAX                        (0x00000007U)

#define CSL_VPDMA_LIST_ATTR_LIST_SIZE_MASK                      (0x0000FFFFU)
#define CSL_VPDMA_LIST_ATTR_LIST_SIZE_SHIFT                     (0U)
#define CSL_VPDMA_LIST_ATTR_LIST_SIZE_RESETVAL                  (0x00000000U)
#define CSL_VPDMA_LIST_ATTR_LIST_SIZE_MAX                       (0x0000ffffU)

#define CSL_VPDMA_LIST_ATTR_LIST_TYPE_MASK                      (0x00070000U)
#define CSL_VPDMA_LIST_ATTR_LIST_TYPE_SHIFT                     (16U)
#define CSL_VPDMA_LIST_ATTR_LIST_TYPE_RESETVAL                  (0x00000000U)
#define CSL_VPDMA_LIST_ATTR_LIST_TYPE_MAX                       (0x00000007U)

#define CSL_VPDMA_LIST_ATTR_RDY_MASK                            (0x00080000U)
#define CSL_VPDMA_LIST_ATTR_RDY_SHIFT                           (19U)
#define CSL_VPDMA_LIST_ATTR_RDY_RESETVAL                        (0x00000000U)
#define CSL_VPDMA_LIST_ATTR_RDY_MAX                             (0x00000001U)

#define CSL_VPDMA_LIST_ATTR_STOP_MASK                           (0x00100000U)
#define CSL_VPDMA_LIST_ATTR_STOP_SHIFT                          (20U)
#define CSL_VPDMA_LIST_ATTR_STOP_RESETVAL                       (0x00000000U)
#define CSL_VPDMA_LIST_ATTR_STOP_MAX                            (0x00000001U)

#define CSL_VPDMA_LIST_ATTR_RESETVAL                            (0x00000000U)

/* LIST_STAT_SYNC */

#define CSL_VPDMA_LIST_STAT_SYNC_LIST0_BUSY_MASK                (0x00010000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST0_BUSY_SHIFT               (16U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST0_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST0_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST1_BUSY_MASK                (0x00020000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST1_BUSY_SHIFT               (17U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST1_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST1_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST2_BUSY_MASK                (0x00040000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST2_BUSY_SHIFT               (18U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST2_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST2_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST3_BUSY_MASK                (0x00080000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST3_BUSY_SHIFT               (19U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST3_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST3_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST4_BUSY_MASK                (0x00100000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST4_BUSY_SHIFT               (20U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST4_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST4_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST5_BUSY_MASK                (0x00200000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST5_BUSY_SHIFT               (21U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST5_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST5_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST6_BUSY_MASK                (0x00400000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST6_BUSY_SHIFT               (22U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST6_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST6_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_LIST7_BUSY_MASK                (0x00800000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST7_BUSY_SHIFT               (23U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST7_BUSY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_LIST7_BUSY_MAX                 (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS0_MASK               (0x00000001U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS0_SHIFT              (0U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS0_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS0_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS1_MASK               (0x00000002U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS1_SHIFT              (1U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS1_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS1_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS2_MASK               (0x00000004U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS2_SHIFT              (2U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS2_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS2_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS3_MASK               (0x00000008U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS3_SHIFT              (3U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS3_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS3_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS4_MASK               (0x00000010U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS4_SHIFT              (4U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS4_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS4_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS5_MASK               (0x00000020U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS5_SHIFT              (5U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS5_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS5_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS6_MASK               (0x00000040U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS6_SHIFT              (6U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS6_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS6_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS7_MASK               (0x00000080U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS7_SHIFT              (7U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS7_RESETVAL           (0x00000000U)
#define CSL_VPDMA_LIST_STAT_SYNC_SYNC_LISTS7_MAX                (0x00000001U)

#define CSL_VPDMA_LIST_STAT_SYNC_RESETVAL                       (0x00000000U)

/* BG_RGB */

#define CSL_VPDMA_BG_RGB_BLEND_MASK                             (0x000000FFU)
#define CSL_VPDMA_BG_RGB_BLEND_SHIFT                            (0U)
#define CSL_VPDMA_BG_RGB_BLEND_RESETVAL                         (0x00000000U)
#define CSL_VPDMA_BG_RGB_BLEND_MAX                              (0x000000ffU)

#define CSL_VPDMA_BG_RGB_BLUE_MASK                              (0x0000FF00U)
#define CSL_VPDMA_BG_RGB_BLUE_SHIFT                             (8U)
#define CSL_VPDMA_BG_RGB_BLUE_RESETVAL                          (0x00000000U)
#define CSL_VPDMA_BG_RGB_BLUE_MAX                               (0x000000ffU)

#define CSL_VPDMA_BG_RGB_GREEN_MASK                             (0x00FF0000U)
#define CSL_VPDMA_BG_RGB_GREEN_SHIFT                            (16U)
#define CSL_VPDMA_BG_RGB_GREEN_RESETVAL                         (0x00000000U)
#define CSL_VPDMA_BG_RGB_GREEN_MAX                              (0x000000ffU)

#define CSL_VPDMA_BG_RGB_RED_MASK                               (0xFF000000U)
#define CSL_VPDMA_BG_RGB_RED_SHIFT                              (24U)
#define CSL_VPDMA_BG_RGB_RED_RESETVAL                           (0x00000000U)
#define CSL_VPDMA_BG_RGB_RED_MAX                                (0x000000ffU)

#define CSL_VPDMA_BG_RGB_RESETVAL                               (0x00000000U)

/* BG_YUV */

#define CSL_VPDMA_BG_YUV_CB_MASK                                (0x000000FFU)
#define CSL_VPDMA_BG_YUV_CB_SHIFT                               (0U)
#define CSL_VPDMA_BG_YUV_CB_RESETVAL                            (0x00000000U)
#define CSL_VPDMA_BG_YUV_CB_MAX                                 (0x000000ffU)

#define CSL_VPDMA_BG_YUV_CR_MASK                                (0x0000FF00U)
#define CSL_VPDMA_BG_YUV_CR_SHIFT                               (8U)
#define CSL_VPDMA_BG_YUV_CR_RESETVAL                            (0x00000000U)
#define CSL_VPDMA_BG_YUV_CR_MAX                                 (0x000000ffU)

#define CSL_VPDMA_BG_YUV_Y_MASK                                 (0x00FF0000U)
#define CSL_VPDMA_BG_YUV_Y_SHIFT                                (16U)
#define CSL_VPDMA_BG_YUV_Y_RESETVAL                             (0x00000000U)
#define CSL_VPDMA_BG_YUV_Y_MAX                                  (0x000000ffU)

#define CSL_VPDMA_BG_YUV_RESETVAL                               (0x00000000U)

/* SETUP */

#define CSL_VPDMA_SETUP_SEC_BASE_CH_MASK                        (0x00000001U)
#define CSL_VPDMA_SETUP_SEC_BASE_CH_SHIFT                       (0U)
#define CSL_VPDMA_SETUP_SEC_BASE_CH_RESETVAL                    (0x00000000U)
#define CSL_VPDMA_SETUP_SEC_BASE_CH_MAX                         (0x00000001U)

#define CSL_VPDMA_SETUP_RESETVAL                                (0x00000000U)

/* MAX_SIZE1 */

#define CSL_VPDMA_MAX_SIZE1_MAX_HEIGHT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_MAX_SIZE1_MAX_HEIGHT_SHIFT                    (0U)
#define CSL_VPDMA_MAX_SIZE1_MAX_HEIGHT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_MAX_SIZE1_MAX_HEIGHT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_MAX_SIZE1_MAX_WIDTH_MASK                      (0xFFFF0000U)
#define CSL_VPDMA_MAX_SIZE1_MAX_WIDTH_SHIFT                     (16U)
#define CSL_VPDMA_MAX_SIZE1_MAX_WIDTH_RESETVAL                  (0x00000000U)
#define CSL_VPDMA_MAX_SIZE1_MAX_WIDTH_MAX                       (0x0000ffffU)

#define CSL_VPDMA_MAX_SIZE1_RESETVAL                            (0x00000000U)

/* MAX_SIZE2 */

#define CSL_VPDMA_MAX_SIZE2_MAX_HEIGHT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_MAX_SIZE2_MAX_HEIGHT_SHIFT                    (0U)
#define CSL_VPDMA_MAX_SIZE2_MAX_HEIGHT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_MAX_SIZE2_MAX_HEIGHT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_MAX_SIZE2_MAX_WIDTH_MASK                      (0xFFFF0000U)
#define CSL_VPDMA_MAX_SIZE2_MAX_WIDTH_SHIFT                     (16U)
#define CSL_VPDMA_MAX_SIZE2_MAX_WIDTH_RESETVAL                  (0x00000000U)
#define CSL_VPDMA_MAX_SIZE2_MAX_WIDTH_MAX                       (0x0000ffffU)

#define CSL_VPDMA_MAX_SIZE2_RESETVAL                            (0x00000000U)

/* MAX_SIZE3 */

#define CSL_VPDMA_MAX_SIZE3_MAX_HEIGHT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_MAX_SIZE3_MAX_HEIGHT_SHIFT                    (0U)
#define CSL_VPDMA_MAX_SIZE3_MAX_HEIGHT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_MAX_SIZE3_MAX_HEIGHT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_MAX_SIZE3_MAX_WIDTH_MASK                      (0xFFFF0000U)
#define CSL_VPDMA_MAX_SIZE3_MAX_WIDTH_SHIFT                     (16U)
#define CSL_VPDMA_MAX_SIZE3_MAX_WIDTH_RESETVAL                  (0x00000000U)
#define CSL_VPDMA_MAX_SIZE3_MAX_WIDTH_MAX                       (0x0000ffffU)

#define CSL_VPDMA_MAX_SIZE3_RESETVAL                            (0x00000000U)

/* INT0_CHANNEL0_INT_STAT */

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_STAT_RESETVAL               (0x00000000U)

/* INT0_CHANNEL0_INT_MASK */

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL0_INT_MASK_RESETVAL               (0x00000000U)

/* INT0_CHANNEL1_INT_STAT */

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_STAT_RESETVAL               (0x00000000U)

/* INT0_CHANNEL1_INT_MASK */

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL1_INT_MASK_RESETVAL               (0x00000000U)

/* INT0_CHANNEL2_INT_STAT */

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_STAT_RESETVAL               (0x00000000U)

/* INT0_CHANNEL2_INT_MASK */

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL2_INT_MASK_RESETVAL               (0x00000000U)

/* INT0_CHANNEL3_INT_STAT */

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_STAT_RESETVAL               (0x00000000U)

/* INT0_CHANNEL3_INT_MASK */

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL3_INT_MASK_RESETVAL               (0x00000000U)

/* INT0_CHANNEL4_INT_STAT */

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_STAT_RESETVAL               (0x00000000U)

/* INT0_CHANNEL4_INT_MASK */

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL4_INT_MASK_RESETVAL               (0x00000000U)

/* INT0_CHANNEL5_INT_STAT */

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_STAT_RESETVAL               (0x00000000U)

/* INT0_CHANNEL5_INT_MASK */

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CHANNEL5_INT_MASK_RESETVAL               (0x00000000U)

/* INT0_CLIENT0_INT_STAT */

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_STAT_RESETVAL                (0x00000000U)

/* INT0_CLIENT0_INT_MASK */

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_CLIENT0_INT_MASK_RESETVAL                (0x00000000U)

/* INT0_LIST0_INT_STAT */

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_STAT_RESETVAL                  (0x00000000U)

/* INT0_LIST0_INT_MASK */

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT0_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT0_LIST0_INT_MASK_RESETVAL                  (0x00000000U)

/* INT1_CHANNEL0_INT_STAT */

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_STAT_RESETVAL               (0x00000000U)

/* INT1_CHANNEL0_INT_MASK */

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL0_INT_MASK_RESETVAL               (0x00000000U)

/* INT1_CHANNEL1_INT_STAT */

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_STAT_RESETVAL               (0x00000000U)

/* INT1_CHANNEL1_INT_MASK */

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL1_INT_MASK_RESETVAL               (0x00000000U)

/* INT1_CHANNEL2_INT_STAT */

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_STAT_RESETVAL               (0x00000000U)

/* INT1_CHANNEL2_INT_MASK */

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL2_INT_MASK_RESETVAL               (0x00000000U)

/* INT1_CHANNEL3_INT_STAT */

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_STAT_RESETVAL               (0x00000000U)

/* INT1_CHANNEL3_INT_MASK */

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL3_INT_MASK_RESETVAL               (0x00000000U)

/* INT1_CHANNEL4_INT_STAT */

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_STAT_RESETVAL               (0x00000000U)

/* INT1_CHANNEL4_INT_MASK */

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL4_INT_MASK_RESETVAL               (0x00000000U)

/* INT1_CHANNEL5_INT_STAT */

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_STAT_RESETVAL               (0x00000000U)

/* INT1_CHANNEL5_INT_MASK */

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CHANNEL5_INT_MASK_RESETVAL               (0x00000000U)

/* INT1_CLIENT0_INT_STAT */

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_STAT_RESETVAL                (0x00000000U)

/* INT1_CLIENT0_INT_MASK */

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_CLIENT0_INT_MASK_RESETVAL                (0x00000000U)

/* INT1_LIST0_INT_STAT */

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_STAT_RESETVAL                  (0x00000000U)

/* INT1_LIST0_INT_MASK */

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT1_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT1_LIST0_INT_MASK_RESETVAL                  (0x00000000U)

/* INT2_CHANNEL0_INT_STAT */

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_STAT_RESETVAL               (0x00000000U)

/* INT2_CHANNEL0_INT_MASK */

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL0_INT_MASK_RESETVAL               (0x00000000U)

/* INT2_CHANNEL1_INT_STAT */

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_STAT_RESETVAL               (0x00000000U)

/* INT2_CHANNEL1_INT_MASK */

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL1_INT_MASK_RESETVAL               (0x00000000U)

/* INT2_CHANNEL2_INT_STAT */

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_STAT_RESETVAL               (0x00000000U)

/* INT2_CHANNEL2_INT_MASK */

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL2_INT_MASK_RESETVAL               (0x00000000U)

/* INT2_CHANNEL3_INT_STAT */

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_STAT_RESETVAL               (0x00000000U)

/* INT2_CHANNEL3_INT_MASK */

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL3_INT_MASK_RESETVAL               (0x00000000U)

/* INT2_CHANNEL4_INT_STAT */

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_STAT_RESETVAL               (0x00000000U)

/* INT2_CHANNEL4_INT_MASK */

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL4_INT_MASK_RESETVAL               (0x00000000U)

/* INT2_CHANNEL5_INT_STAT */

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_STAT_RESETVAL               (0x00000000U)

/* INT2_CHANNEL5_INT_MASK */

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CHANNEL5_INT_MASK_RESETVAL               (0x00000000U)

/* INT2_CLIENT0_INT_STAT */

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_STAT_RESETVAL                (0x00000000U)

/* INT2_CLIENT0_INT_MASK */

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_CLIENT0_INT_MASK_RESETVAL                (0x00000000U)

/* INT2_LIST0_INT_STAT */

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_STAT_RESETVAL                  (0x00000000U)

/* INT2_LIST0_INT_MASK */

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT2_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT2_LIST0_INT_MASK_RESETVAL                  (0x00000000U)

/* INT3_CHANNEL0_INT_STAT */

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_INT_STAT_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_STAT_RESETVAL               (0x00000000U)

/* INT3_CHANNEL0_INT_MASK */

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MASK    (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_SHIFT   (12U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_MAX     (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_INT_MASK_HQ_VID3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL0_INT_MASK_RESETVAL               (0x00000000U)

/* INT3_CHANNEL1_INT_STAT */

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_STAT_RESETVAL               (0x00000000U)

/* INT3_CHANNEL1_INT_MASK */

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL1_INT_MASK_RESETVAL               (0x00000000U)

/* INT3_CHANNEL2_INT_STAT */

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_INT_STAT_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_STAT_RESETVAL               (0x00000000U)

/* INT3_CHANNEL2_INT_MASK */

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_INT_MASK_VIP1_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL2_INT_MASK_RESETVAL               (0x00000000U)

/* INT3_CHANNEL3_INT_STAT */

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_STAT_RESETVAL               (0x00000000U)

/* INT3_CHANNEL3_INT_MASK */

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP1_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL3_INT_MASK_RESETVAL               (0x00000000U)

/* INT3_CHANNEL4_INT_STAT */

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_INT_STAT_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_STAT_RESETVAL               (0x00000000U)

/* INT3_CHANNEL4_INT_MASK */

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_SHIFT  (22U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_SHIFT  (23U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_SHIFT  (24U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_SHIFT  (25U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_SHIFT  (26U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_SHIFT  (27U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_SHIFT  (18U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_SHIFT  (19U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_SHIFT  (20U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_SHIFT  (21U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCA_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_SHIFT  (28U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_SHIFT  (29U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_SHIFT  (30U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_SHIFT  (31U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_INT_MASK_VIP2_MULT_PORTB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL4_INT_MASK_RESETVAL               (0x00000000U)

/* INT3_CHANNEL5_INT_STAT */

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_INT_STAT_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_STAT_RESETVAL               (0x00000000U)

/* INT3_CHANNEL5_INT_MASK */

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_SHIFT  (6U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_SHIFT  (7U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_SHIFT  (8U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_SHIFT  (9U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_SHIFT  (10U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_SHIFT  (11U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_SHIFT  (0U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_SHIFT  (1U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_SHIFT  (2U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_SHIFT  (3U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_SHIFT  (4U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_SHIFT  (5U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_MULT_ANCB_SRC9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_SHIFT  (13U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_SHIFT  (12U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_SHIFT  (16U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTA_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_SHIFT  (15U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_SHIFT  (14U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_SHIFT  (17U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_INT_MASK_VIP2_PORTB_RGB_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CHANNEL5_INT_MASK_RESETVAL               (0x00000000U)

/* INT3_CLIENT0_INT_STAT */

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_INT_STAT_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_STAT_RESETVAL                (0x00000000U)

/* INT3_CLIENT0_INT_MASK */

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_SHIFT  (0U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_SHIFT  (1U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_1_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_SHIFT  (3U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_SHIFT  (2U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_2_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_SHIFT  (5U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_CHROMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_SHIFT  (4U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_3_LUMA_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_SHIFT  (12U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_IN_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_SHIFT  (15U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_INT_MASK_DEI_HQ_MV_OUT_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_CLIENT0_INT_MASK_RESETVAL                (0x00000000U)

/* INT3_LIST0_INT_STAT */

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_STAT_INT_STAT_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_STAT_RESETVAL                  (0x00000000U)

/* INT3_LIST0_INT_MASK */

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MASK  (0x00010000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_SHIFT  (16U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT0_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MASK  (0x00020000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_SHIFT  (17U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT1_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MASK  (0x04000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_SHIFT  (26U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT10_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MASK  (0x08000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_SHIFT  (27U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT11_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MASK  (0x10000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_SHIFT  (28U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT12_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MASK  (0x20000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_SHIFT  (29U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT13_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MASK  (0x40000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_SHIFT  (30U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT14_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MASK  (0x80000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_SHIFT  (31U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT15_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MASK  (0x00040000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_SHIFT  (18U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT2_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MASK  (0x00080000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_SHIFT  (19U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT3_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MASK  (0x00100000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_SHIFT  (20U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT4_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MASK  (0x00200000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_SHIFT  (21U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT5_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MASK  (0x00400000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_SHIFT  (22U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT6_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MASK  (0x00800000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_SHIFT  (23U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT7_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MASK  (0x01000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_SHIFT  (24U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT8_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MASK  (0x02000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_SHIFT  (25U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_CONTROL_DESCRIPTOR_INT9_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MASK  (0x00000001U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_SHIFT  (0U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MASK  (0x00000002U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_SHIFT  (1U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST0_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MASK  (0x00000004U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_SHIFT  (2U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MASK  (0x00000008U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_SHIFT  (3U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST1_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MASK  (0x00000010U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_SHIFT  (4U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MASK  (0x00000020U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_SHIFT  (5U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST2_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MASK  (0x00000040U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_SHIFT  (6U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MASK  (0x00000080U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_SHIFT  (7U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST3_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MASK  (0x00000100U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_SHIFT  (8U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MASK  (0x00000200U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_SHIFT  (9U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST4_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MASK  (0x00000400U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_SHIFT  (10U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MASK  (0x00000800U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_SHIFT  (11U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST5_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MASK  (0x00001000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_SHIFT  (12U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MASK  (0x00002000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_SHIFT  (13U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST6_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MASK  (0x00004000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_SHIFT  (14U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_COMPLETE_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MASK  (0x00008000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_SHIFT  (15U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_RESETVAL  (0x00000000U)
#define CSL_VPDMA_INT3_LIST0_INT_MASK_INT_MASK_LIST7_NOTIFY_MAX  (0x00000001U)

#define CSL_VPDMA_INT3_LIST0_INT_MASK_RESETVAL                  (0x00000000U)

/* PERF_MON0 */

#define CSL_VPDMA_PERF_MON0_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON0_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON0_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON0_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON0_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON0_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON0_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON0_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON0_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON0_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON0_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON0_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON0_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON0_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON0_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON0_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON0_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON0_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON0_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON0_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON0_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON0_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON0_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON0_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON0_RESETVAL                            (0x00000000U)

/* PERF_MON1 */

#define CSL_VPDMA_PERF_MON1_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON1_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON1_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON1_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON1_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON1_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON1_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON1_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON1_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON1_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON1_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON1_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON1_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON1_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON1_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON1_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON1_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON1_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON1_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON1_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON1_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON1_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON1_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON1_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON1_RESETVAL                            (0x00000000U)

/* PERF_MON2 */

#define CSL_VPDMA_PERF_MON2_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON2_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON2_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON2_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON2_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON2_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON2_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON2_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON2_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON2_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON2_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON2_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON2_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON2_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON2_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON2_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON2_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON2_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON2_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON2_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON2_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON2_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON2_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON2_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON2_RESETVAL                            (0x00000000U)

/* PERF_MON3 */

#define CSL_VPDMA_PERF_MON3_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON3_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON3_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON3_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON3_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON3_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON3_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON3_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON3_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON3_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON3_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON3_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON3_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON3_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON3_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON3_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON3_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON3_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON3_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON3_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON3_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON3_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON3_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON3_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON3_RESETVAL                            (0x00000000U)

/* PERF_MON4 */

#define CSL_VPDMA_PERF_MON4_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON4_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON4_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON4_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON4_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON4_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON4_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON4_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON4_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON4_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON4_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON4_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON4_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON4_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON4_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON4_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON4_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON4_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON4_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON4_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON4_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON4_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON4_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON4_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON4_RESETVAL                            (0x00000000U)

/* PERF_MON5 */

#define CSL_VPDMA_PERF_MON5_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON5_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON5_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON5_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON5_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON5_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON5_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON5_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON5_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON5_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON5_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON5_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON5_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON5_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON5_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON5_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON5_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON5_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON5_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON5_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON5_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON5_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON5_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON5_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON5_RESETVAL                            (0x00000000U)

/* PERF_MON6 */

#define CSL_VPDMA_PERF_MON6_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON6_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON6_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON6_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON6_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON6_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON6_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON6_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON6_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON6_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON6_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON6_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON6_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON6_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON6_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON6_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON6_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON6_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON6_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON6_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON6_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON6_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON6_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON6_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON6_RESETVAL                            (0x00000000U)

/* PERF_MON7 */

#define CSL_VPDMA_PERF_MON7_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON7_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON7_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON7_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON7_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON7_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON7_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON7_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON7_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON7_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON7_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON7_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON7_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON7_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON7_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON7_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON7_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON7_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON7_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON7_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON7_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON7_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON7_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON7_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON7_RESETVAL                            (0x00000000U)

/* PERF_MON8 */

#define CSL_VPDMA_PERF_MON8_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON8_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON8_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON8_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON8_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON8_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON8_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON8_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON8_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON8_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON8_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON8_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON8_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON8_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON8_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON8_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON8_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON8_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON8_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON8_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON8_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON8_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON8_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON8_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON8_RESETVAL                            (0x00000000U)

/* PERF_MON9 */

#define CSL_VPDMA_PERF_MON9_CAPTURE_MODE_MASK                   (0xC0000000U)
#define CSL_VPDMA_PERF_MON9_CAPTURE_MODE_SHIFT                  (30U)
#define CSL_VPDMA_PERF_MON9_CAPTURE_MODE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON9_CAPTURE_MODE_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON9_CURR_COUNT_MASK                     (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON9_CURR_COUNT_SHIFT                    (0U)
#define CSL_VPDMA_PERF_MON9_CURR_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON9_CURR_COUNT_MAX                      (0x0000ffffU)

#define CSL_VPDMA_PERF_MON9_START_CLIENT_MASK                   (0x00300000U)
#define CSL_VPDMA_PERF_MON9_START_CLIENT_SHIFT                  (20U)
#define CSL_VPDMA_PERF_MON9_START_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON9_START_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON9_START_COUNT_MASK                    (0x00070000U)
#define CSL_VPDMA_PERF_MON9_START_COUNT_SHIFT                   (16U)
#define CSL_VPDMA_PERF_MON9_START_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON9_START_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON9_STOP_CLIENT_MASK                    (0x30000000U)
#define CSL_VPDMA_PERF_MON9_STOP_CLIENT_SHIFT                   (28U)
#define CSL_VPDMA_PERF_MON9_STOP_CLIENT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON9_STOP_CLIENT_MAX                     (0x00000003U)

#define CSL_VPDMA_PERF_MON9_STOP_COUNT_MASK                     (0x07000000U)
#define CSL_VPDMA_PERF_MON9_STOP_COUNT_SHIFT                    (24U)
#define CSL_VPDMA_PERF_MON9_STOP_COUNT_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_PERF_MON9_STOP_COUNT_MAX                      (0x00000007U)

#define CSL_VPDMA_PERF_MON9_RESETVAL                            (0x00000000U)

/* PERF_MON10 */

#define CSL_VPDMA_PERF_MON10_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON10_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON10_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON10_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON10_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON10_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON10_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON10_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON10_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON10_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON10_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON10_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON10_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON10_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON10_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON10_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON10_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON10_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON10_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON10_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON10_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON10_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON10_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON10_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON10_RESETVAL                           (0x00000000U)

/* PERF_MON11 */

#define CSL_VPDMA_PERF_MON11_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON11_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON11_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON11_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON11_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON11_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON11_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON11_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON11_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON11_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON11_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON11_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON11_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON11_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON11_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON11_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON11_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON11_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON11_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON11_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON11_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON11_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON11_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON11_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON11_RESETVAL                           (0x00000000U)

/* PERF_MON12 */

#define CSL_VPDMA_PERF_MON12_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON12_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON12_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON12_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON12_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON12_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON12_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON12_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON12_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON12_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON12_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON12_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON12_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON12_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON12_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON12_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON12_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON12_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON12_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON12_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON12_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON12_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON12_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON12_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON12_RESETVAL                           (0x00000000U)

/* PERF_MON13 */

#define CSL_VPDMA_PERF_MON13_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON13_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON13_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON13_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON13_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON13_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON13_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON13_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON13_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON13_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON13_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON13_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON13_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON13_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON13_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON13_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON13_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON13_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON13_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON13_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON13_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON13_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON13_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON13_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON13_RESETVAL                           (0x00000000U)

/* PERF_MON14 */

#define CSL_VPDMA_PERF_MON14_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON14_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON14_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON14_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON14_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON14_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON14_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON14_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON14_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON14_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON14_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON14_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON14_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON14_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON14_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON14_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON14_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON14_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON14_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON14_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON14_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON14_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON14_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON14_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON14_RESETVAL                           (0x00000000U)

/* PERF_MON15 */

#define CSL_VPDMA_PERF_MON15_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON15_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON15_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON15_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON15_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON15_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON15_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON15_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON15_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON15_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON15_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON15_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON15_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON15_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON15_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON15_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON15_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON15_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON15_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON15_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON15_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON15_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON15_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON15_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON15_RESETVAL                           (0x00000000U)

/* PERF_MON16 */

#define CSL_VPDMA_PERF_MON16_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON16_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON16_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON16_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON16_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON16_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON16_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON16_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON16_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON16_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON16_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON16_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON16_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON16_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON16_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON16_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON16_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON16_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON16_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON16_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON16_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON16_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON16_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON16_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON16_RESETVAL                           (0x00000000U)

/* PERF_MON17 */

#define CSL_VPDMA_PERF_MON17_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON17_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON17_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON17_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON17_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON17_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON17_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON17_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON17_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON17_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON17_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON17_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON17_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON17_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON17_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON17_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON17_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON17_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON17_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON17_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON17_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON17_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON17_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON17_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON17_RESETVAL                           (0x00000000U)

/* PERF_MON18 */

#define CSL_VPDMA_PERF_MON18_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON18_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON18_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON18_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON18_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON18_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON18_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON18_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON18_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON18_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON18_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON18_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON18_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON18_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON18_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON18_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON18_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON18_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON18_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON18_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON18_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON18_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON18_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON18_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON18_RESETVAL                           (0x00000000U)

/* PERF_MON19 */

#define CSL_VPDMA_PERF_MON19_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON19_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON19_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON19_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON19_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON19_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON19_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON19_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON19_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON19_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON19_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON19_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON19_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON19_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON19_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON19_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON19_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON19_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON19_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON19_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON19_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON19_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON19_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON19_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON19_RESETVAL                           (0x00000000U)

/* PERF_MON20 */

#define CSL_VPDMA_PERF_MON20_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON20_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON20_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON20_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON20_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON20_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON20_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON20_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON20_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON20_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON20_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON20_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON20_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON20_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON20_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON20_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON20_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON20_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON20_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON20_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON20_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON20_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON20_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON20_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON20_RESETVAL                           (0x00000000U)

/* PERF_MON21 */

#define CSL_VPDMA_PERF_MON21_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON21_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON21_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON21_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON21_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON21_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON21_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON21_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON21_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON21_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON21_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON21_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON21_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON21_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON21_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON21_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON21_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON21_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON21_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON21_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON21_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON21_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON21_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON21_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON21_RESETVAL                           (0x00000000U)

/* PERF_MON22 */

#define CSL_VPDMA_PERF_MON22_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON22_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON22_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON22_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON22_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON22_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON22_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON22_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON22_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON22_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON22_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON22_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON22_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON22_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON22_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON22_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON22_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON22_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON22_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON22_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON22_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON22_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON22_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON22_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON22_RESETVAL                           (0x00000000U)

/* PERF_MON23 */

#define CSL_VPDMA_PERF_MON23_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON23_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON23_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON23_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON23_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON23_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON23_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON23_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON23_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON23_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON23_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON23_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON23_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON23_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON23_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON23_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON23_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON23_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON23_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON23_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON23_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON23_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON23_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON23_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON23_RESETVAL                           (0x00000000U)

/* PERF_MON24 */

#define CSL_VPDMA_PERF_MON24_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON24_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON24_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON24_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON24_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON24_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON24_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON24_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON24_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON24_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON24_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON24_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON24_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON24_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON24_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON24_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON24_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON24_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON24_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON24_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON24_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON24_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON24_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON24_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON24_RESETVAL                           (0x00000000U)

/* PERF_MON25 */

#define CSL_VPDMA_PERF_MON25_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON25_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON25_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON25_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON25_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON25_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON25_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON25_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON25_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON25_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON25_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON25_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON25_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON25_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON25_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON25_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON25_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON25_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON25_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON25_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON25_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON25_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON25_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON25_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON25_RESETVAL                           (0x00000000U)

/* PERF_MON26 */

#define CSL_VPDMA_PERF_MON26_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON26_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON26_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON26_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON26_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON26_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON26_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON26_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON26_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON26_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON26_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON26_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON26_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON26_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON26_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON26_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON26_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON26_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON26_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON26_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON26_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON26_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON26_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON26_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON26_RESETVAL                           (0x00000000U)

/* PERF_MON27 */

#define CSL_VPDMA_PERF_MON27_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON27_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON27_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON27_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON27_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON27_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON27_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON27_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON27_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON27_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON27_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON27_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON27_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON27_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON27_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON27_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON27_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON27_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON27_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON27_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON27_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON27_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON27_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON27_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON27_RESETVAL                           (0x00000000U)

/* PERF_MON28 */

#define CSL_VPDMA_PERF_MON28_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON28_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON28_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON28_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON28_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON28_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON28_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON28_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON28_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON28_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON28_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON28_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON28_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON28_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON28_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON28_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON28_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON28_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON28_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON28_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON28_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON28_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON28_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON28_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON28_RESETVAL                           (0x00000000U)

/* PERF_MON29 */

#define CSL_VPDMA_PERF_MON29_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON29_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON29_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON29_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON29_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON29_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON29_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON29_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON29_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON29_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON29_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON29_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON29_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON29_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON29_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON29_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON29_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON29_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON29_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON29_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON29_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON29_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON29_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON29_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON29_RESETVAL                           (0x00000000U)

/* PERF_MON30 */

#define CSL_VPDMA_PERF_MON30_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON30_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON30_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON30_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON30_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON30_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON30_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON30_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON30_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON30_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON30_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON30_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON30_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON30_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON30_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON30_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON30_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON30_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON30_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON30_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON30_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON30_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON30_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON30_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON30_RESETVAL                           (0x00000000U)

/* PERF_MON31 */

#define CSL_VPDMA_PERF_MON31_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON31_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON31_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON31_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON31_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON31_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON31_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON31_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON31_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON31_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON31_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON31_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON31_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON31_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON31_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON31_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON31_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON31_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON31_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON31_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON31_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON31_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON31_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON31_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON31_RESETVAL                           (0x00000000U)

/* PERF_MON32 */

#define CSL_VPDMA_PERF_MON32_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON32_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON32_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON32_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON32_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON32_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON32_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON32_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON32_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON32_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON32_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON32_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON32_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON32_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON32_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON32_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON32_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON32_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON32_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON32_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON32_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON32_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON32_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON32_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON32_RESETVAL                           (0x00000000U)

/* PERF_MON33 */

#define CSL_VPDMA_PERF_MON33_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON33_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON33_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON33_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON33_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON33_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON33_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON33_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON33_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON33_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON33_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON33_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON33_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON33_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON33_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON33_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON33_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON33_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON33_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON33_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON33_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON33_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON33_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON33_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON33_RESETVAL                           (0x00000000U)

/* PERF_MON34 */

#define CSL_VPDMA_PERF_MON34_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON34_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON34_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON34_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON34_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON34_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON34_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON34_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON34_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON34_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON34_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON34_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON34_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON34_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON34_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON34_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON34_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON34_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON34_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON34_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON34_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON34_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON34_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON34_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON34_RESETVAL                           (0x00000000U)

/* PERF_MON35 */

#define CSL_VPDMA_PERF_MON35_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON35_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON35_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON35_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON35_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON35_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON35_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON35_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON35_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON35_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON35_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON35_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON35_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON35_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON35_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON35_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON35_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON35_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON35_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON35_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON35_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON35_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON35_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON35_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON35_RESETVAL                           (0x00000000U)

/* PERF_MON36 */

#define CSL_VPDMA_PERF_MON36_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON36_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON36_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON36_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON36_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON36_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON36_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON36_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON36_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON36_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON36_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON36_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON36_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON36_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON36_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON36_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON36_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON36_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON36_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON36_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON36_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON36_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON36_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON36_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON36_RESETVAL                           (0x00000000U)

/* PERF_MON37 */

#define CSL_VPDMA_PERF_MON37_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON37_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON37_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON37_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON37_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON37_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON37_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON37_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON37_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON37_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON37_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON37_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON37_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON37_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON37_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON37_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON37_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON37_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON37_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON37_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON37_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON37_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON37_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON37_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON37_RESETVAL                           (0x00000000U)

/* PERF_MON38 */

#define CSL_VPDMA_PERF_MON38_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON38_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON38_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON38_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON38_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON38_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON38_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON38_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON38_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON38_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON38_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON38_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON38_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON38_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON38_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON38_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON38_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON38_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON38_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON38_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON38_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON38_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON38_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON38_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON38_RESETVAL                           (0x00000000U)

/* PERF_MON39 */

#define CSL_VPDMA_PERF_MON39_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON39_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON39_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON39_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON39_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON39_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON39_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON39_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON39_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON39_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON39_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON39_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON39_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON39_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON39_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON39_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON39_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON39_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON39_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON39_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON39_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON39_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON39_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON39_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON39_RESETVAL                           (0x00000000U)

/* PERF_MON40 */

#define CSL_VPDMA_PERF_MON40_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON40_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON40_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON40_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON40_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON40_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON40_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON40_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON40_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON40_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON40_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON40_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON40_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON40_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON40_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON40_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON40_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON40_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON40_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON40_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON40_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON40_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON40_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON40_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON40_RESETVAL                           (0x00000000U)

/* PERF_MON41 */

#define CSL_VPDMA_PERF_MON41_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON41_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON41_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON41_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON41_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON41_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON41_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON41_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON41_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON41_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON41_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON41_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON41_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON41_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON41_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON41_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON41_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON41_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON41_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON41_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON41_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON41_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON41_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON41_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON41_RESETVAL                           (0x00000000U)

/* PERF_MON42 */

#define CSL_VPDMA_PERF_MON42_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON42_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON42_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON42_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON42_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON42_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON42_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON42_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON42_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON42_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON42_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON42_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON42_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON42_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON42_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON42_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON42_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON42_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON42_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON42_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON42_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON42_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON42_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON42_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON42_RESETVAL                           (0x00000000U)

/* PERF_MON43 */

#define CSL_VPDMA_PERF_MON43_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON43_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON43_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON43_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON43_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON43_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON43_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON43_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON43_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON43_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON43_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON43_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON43_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON43_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON43_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON43_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON43_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON43_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON43_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON43_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON43_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON43_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON43_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON43_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON43_RESETVAL                           (0x00000000U)

/* PERF_MON44 */

#define CSL_VPDMA_PERF_MON44_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON44_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON44_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON44_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON44_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON44_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON44_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON44_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON44_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON44_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON44_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON44_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON44_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON44_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON44_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON44_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON44_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON44_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON44_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON44_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON44_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON44_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON44_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON44_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON44_RESETVAL                           (0x00000000U)

/* PERF_MON45 */

#define CSL_VPDMA_PERF_MON45_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON45_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON45_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON45_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON45_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON45_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON45_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON45_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON45_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON45_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON45_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON45_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON45_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON45_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON45_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON45_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON45_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON45_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON45_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON45_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON45_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON45_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON45_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON45_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON45_RESETVAL                           (0x00000000U)

/* PERF_MON46 */

#define CSL_VPDMA_PERF_MON46_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON46_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON46_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON46_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON46_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON46_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON46_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON46_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON46_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON46_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON46_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON46_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON46_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON46_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON46_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON46_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON46_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON46_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON46_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON46_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON46_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON46_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON46_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON46_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON46_RESETVAL                           (0x00000000U)

/* PERF_MON47 */

#define CSL_VPDMA_PERF_MON47_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON47_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON47_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON47_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON47_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON47_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON47_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON47_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON47_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON47_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON47_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON47_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON47_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON47_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON47_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON47_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON47_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON47_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON47_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON47_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON47_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON47_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON47_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON47_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON47_RESETVAL                           (0x00000000U)

/* PERF_MON48 */

#define CSL_VPDMA_PERF_MON48_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON48_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON48_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON48_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON48_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON48_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON48_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON48_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON48_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON48_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON48_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON48_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON48_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON48_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON48_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON48_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON48_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON48_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON48_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON48_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON48_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON48_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON48_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON48_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON48_RESETVAL                           (0x00000000U)

/* PERF_MON49 */

#define CSL_VPDMA_PERF_MON49_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON49_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON49_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON49_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON49_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON49_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON49_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON49_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON49_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON49_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON49_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON49_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON49_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON49_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON49_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON49_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON49_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON49_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON49_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON49_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON49_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON49_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON49_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON49_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON49_RESETVAL                           (0x00000000U)

/* PERF_MON50 */

#define CSL_VPDMA_PERF_MON50_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON50_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON50_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON50_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON50_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON50_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON50_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON50_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON50_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON50_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON50_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON50_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON50_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON50_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON50_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON50_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON50_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON50_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON50_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON50_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON50_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON50_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON50_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON50_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON50_RESETVAL                           (0x00000000U)

/* PERF_MON51 */

#define CSL_VPDMA_PERF_MON51_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON51_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON51_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON51_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON51_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON51_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON51_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON51_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON51_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON51_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON51_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON51_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON51_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON51_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON51_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON51_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON51_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON51_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON51_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON51_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON51_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON51_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON51_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON51_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON51_RESETVAL                           (0x00000000U)

/* PERF_MON52 */

#define CSL_VPDMA_PERF_MON52_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON52_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON52_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON52_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON52_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON52_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON52_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON52_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON52_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON52_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON52_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON52_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON52_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON52_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON52_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON52_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON52_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON52_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON52_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON52_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON52_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON52_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON52_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON52_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON52_RESETVAL                           (0x00000000U)

/* PERF_MON53 */

#define CSL_VPDMA_PERF_MON53_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON53_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON53_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON53_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON53_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON53_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON53_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON53_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON53_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON53_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON53_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON53_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON53_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON53_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON53_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON53_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON53_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON53_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON53_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON53_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON53_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON53_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON53_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON53_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON53_RESETVAL                           (0x00000000U)

/* PERF_MON54 */

#define CSL_VPDMA_PERF_MON54_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON54_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON54_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON54_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON54_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON54_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON54_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON54_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON54_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON54_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON54_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON54_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON54_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON54_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON54_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON54_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON54_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON54_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON54_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON54_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON54_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON54_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON54_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON54_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON54_RESETVAL                           (0x00000000U)

/* PERF_MON55 */

#define CSL_VPDMA_PERF_MON55_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON55_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON55_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON55_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON55_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON55_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON55_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON55_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON55_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON55_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON55_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON55_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON55_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON55_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON55_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON55_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON55_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON55_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON55_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON55_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON55_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON55_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON55_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON55_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON55_RESETVAL                           (0x00000000U)

/* PERF_MON56 */

#define CSL_VPDMA_PERF_MON56_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON56_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON56_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON56_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON56_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON56_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON56_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON56_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON56_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON56_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON56_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON56_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON56_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON56_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON56_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON56_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON56_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON56_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON56_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON56_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON56_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON56_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON56_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON56_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON56_RESETVAL                           (0x00000000U)

/* PERF_MON57 */

#define CSL_VPDMA_PERF_MON57_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON57_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON57_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON57_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON57_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON57_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON57_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON57_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON57_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON57_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON57_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON57_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON57_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON57_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON57_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON57_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON57_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON57_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON57_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON57_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON57_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON57_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON57_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON57_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON57_RESETVAL                           (0x00000000U)

/* PERF_MON58 */

#define CSL_VPDMA_PERF_MON58_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON58_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON58_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON58_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON58_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON58_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON58_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON58_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON58_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON58_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON58_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON58_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON58_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON58_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON58_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON58_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON58_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON58_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON58_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON58_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON58_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON58_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON58_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON58_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON58_RESETVAL                           (0x00000000U)

/* PERF_MON59 */

#define CSL_VPDMA_PERF_MON59_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON59_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON59_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON59_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON59_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON59_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON59_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON59_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON59_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON59_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON59_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON59_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON59_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON59_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON59_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON59_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON59_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON59_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON59_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON59_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON59_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON59_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON59_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON59_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON59_RESETVAL                           (0x00000000U)

/* PERF_MON60 */

#define CSL_VPDMA_PERF_MON60_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON60_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON60_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON60_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON60_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON60_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON60_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON60_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON60_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON60_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON60_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON60_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON60_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON60_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON60_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON60_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON60_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON60_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON60_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON60_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON60_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON60_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON60_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON60_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON60_RESETVAL                           (0x00000000U)

/* PERF_MON61 */

#define CSL_VPDMA_PERF_MON61_CAPTURE_MODE_MASK                  (0xC0000000U)
#define CSL_VPDMA_PERF_MON61_CAPTURE_MODE_SHIFT                 (30U)
#define CSL_VPDMA_PERF_MON61_CAPTURE_MODE_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON61_CAPTURE_MODE_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON61_CURR_COUNT_MASK                    (0x0000FFFFU)
#define CSL_VPDMA_PERF_MON61_CURR_COUNT_SHIFT                   (0U)
#define CSL_VPDMA_PERF_MON61_CURR_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON61_CURR_COUNT_MAX                     (0x0000ffffU)

#define CSL_VPDMA_PERF_MON61_START_CLIENT_MASK                  (0x00300000U)
#define CSL_VPDMA_PERF_MON61_START_CLIENT_SHIFT                 (20U)
#define CSL_VPDMA_PERF_MON61_START_CLIENT_RESETVAL              (0x00000000U)
#define CSL_VPDMA_PERF_MON61_START_CLIENT_MAX                   (0x00000003U)

#define CSL_VPDMA_PERF_MON61_START_COUNT_MASK                   (0x00070000U)
#define CSL_VPDMA_PERF_MON61_START_COUNT_SHIFT                  (16U)
#define CSL_VPDMA_PERF_MON61_START_COUNT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON61_START_COUNT_MAX                    (0x00000007U)

#define CSL_VPDMA_PERF_MON61_STOP_CLIENT_MASK                   (0x30000000U)
#define CSL_VPDMA_PERF_MON61_STOP_CLIENT_SHIFT                  (28U)
#define CSL_VPDMA_PERF_MON61_STOP_CLIENT_RESETVAL               (0x00000000U)
#define CSL_VPDMA_PERF_MON61_STOP_CLIENT_MAX                    (0x00000003U)

#define CSL_VPDMA_PERF_MON61_STOP_COUNT_MASK                    (0x07000000U)
#define CSL_VPDMA_PERF_MON61_STOP_COUNT_SHIFT                   (24U)
#define CSL_VPDMA_PERF_MON61_STOP_COUNT_RESETVAL                (0x00000000U)
#define CSL_VPDMA_PERF_MON61_STOP_COUNT_MAX                     (0x00000007U)

#define CSL_VPDMA_PERF_MON61_RESETVAL                           (0x00000000U)

/* DEI_HQ_1_CHROMA_CSTAT */

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_BUSY_MASK               (0x00008000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_BUSY_SHIFT              (15U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_BUSY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_BUSY_MAX                (0x00000001U)

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_DMA_ACTIVE_MASK         (0x00004000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_DMA_ACTIVE_SHIFT        (14U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_DMA_ACTIVE_RESETVAL     (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_DMA_ACTIVE_MAX          (0x00000001U)

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_FRM_START_MASK          (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_FRM_START_SHIFT         (10U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_FRM_START_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_FRM_START_MAX           (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_LINE_MODE_MASK          (0x00000300U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_LINE_MODE_SHIFT         (8U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_LINE_MODE_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_LINE_MODE_MAX           (0x00000003U)

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_DELAY_MASK          (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_DELAY_SHIFT         (24U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_DELAY_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_DELAY_MAX           (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_RATE_MASK           (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_RATE_SHIFT          (16U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_RATE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_REQ_RATE_MAX            (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_1_CHROMA_CSTAT_RESETVAL                (0x00000000U)

/* DEI_HQ_1_LUMA_CSTAT */

#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_BUSY_MASK                 (0x00008000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_BUSY_SHIFT                (15U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_BUSY_RESETVAL             (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_BUSY_MAX                  (0x00000001U)

#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_DMA_ACTIVE_MASK           (0x00004000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_DMA_ACTIVE_SHIFT          (14U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_DMA_ACTIVE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_DMA_ACTIVE_MAX            (0x00000001U)

#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_FRM_START_MASK            (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_FRM_START_SHIFT           (10U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_FRM_START_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_FRM_START_MAX             (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_DELAY_MASK            (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_DELAY_SHIFT           (24U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_DELAY_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_DELAY_MAX             (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_RATE_MASK             (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_RATE_SHIFT            (16U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_RATE_RESETVAL         (0x00000000U)
#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_REQ_RATE_MAX              (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_1_LUMA_CSTAT_RESETVAL                  (0x00000000U)

/* DEI_HQ_2_LUMA_CSTAT */

#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_BUSY_MASK                 (0x00008000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_BUSY_SHIFT                (15U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_BUSY_RESETVAL             (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_BUSY_MAX                  (0x00000001U)

#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_DMA_ACTIVE_MASK           (0x00004000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_DMA_ACTIVE_SHIFT          (14U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_DMA_ACTIVE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_DMA_ACTIVE_MAX            (0x00000001U)

#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_FRM_START_MASK            (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_FRM_START_SHIFT           (10U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_FRM_START_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_FRM_START_MAX             (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_DELAY_MASK            (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_DELAY_SHIFT           (24U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_DELAY_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_DELAY_MAX             (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_RATE_MASK             (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_RATE_SHIFT            (16U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_RATE_RESETVAL         (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_REQ_RATE_MAX              (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_2_LUMA_CSTAT_RESETVAL                  (0x00000000U)

/* DEI_HQ_2_CHROMA_CSTAT */

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_BUSY_MASK               (0x00008000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_BUSY_SHIFT              (15U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_BUSY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_BUSY_MAX                (0x00000001U)

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_DMA_ACTIVE_MASK         (0x00004000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_DMA_ACTIVE_SHIFT        (14U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_DMA_ACTIVE_RESETVAL     (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_DMA_ACTIVE_MAX          (0x00000001U)

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_FRM_START_MASK          (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_FRM_START_SHIFT         (10U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_FRM_START_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_FRM_START_MAX           (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_LINE_MODE_MASK          (0x00000300U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_LINE_MODE_SHIFT         (8U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_LINE_MODE_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_LINE_MODE_MAX           (0x00000003U)

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_DELAY_MASK          (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_DELAY_SHIFT         (24U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_DELAY_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_DELAY_MAX           (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_RATE_MASK           (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_RATE_SHIFT          (16U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_RATE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_REQ_RATE_MAX            (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_2_CHROMA_CSTAT_RESETVAL                (0x00000000U)

/* DEI_HQ_3_LUMA_CSTAT */

#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_BUSY_MASK                 (0x00008000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_BUSY_SHIFT                (15U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_BUSY_RESETVAL             (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_BUSY_MAX                  (0x00000001U)

#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_DMA_ACTIVE_MASK           (0x00004000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_DMA_ACTIVE_SHIFT          (14U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_DMA_ACTIVE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_DMA_ACTIVE_MAX            (0x00000001U)

#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_FRM_START_MASK            (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_FRM_START_SHIFT           (10U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_FRM_START_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_FRM_START_MAX             (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_DELAY_MASK            (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_DELAY_SHIFT           (24U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_DELAY_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_DELAY_MAX             (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_RATE_MASK             (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_RATE_SHIFT            (16U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_RATE_RESETVAL         (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_REQ_RATE_MAX              (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_3_LUMA_CSTAT_RESETVAL                  (0x00000000U)

/* DEI_HQ_3_CHROMA_CSTAT */

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_BUSY_MASK               (0x00008000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_BUSY_SHIFT              (15U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_BUSY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_BUSY_MAX                (0x00000001U)

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_DMA_ACTIVE_MASK         (0x00004000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_DMA_ACTIVE_SHIFT        (14U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_DMA_ACTIVE_RESETVAL     (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_DMA_ACTIVE_MAX          (0x00000001U)

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_FRM_START_MASK          (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_FRM_START_SHIFT         (10U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_FRM_START_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_FRM_START_MAX           (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_LINE_MODE_MASK          (0x00000300U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_LINE_MODE_SHIFT         (8U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_LINE_MODE_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_LINE_MODE_MAX           (0x00000003U)

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_DELAY_MASK          (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_DELAY_SHIFT         (24U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_DELAY_RESETVAL      (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_DELAY_MAX           (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_RATE_MASK           (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_RATE_SHIFT          (16U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_RATE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_REQ_RATE_MAX            (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_3_CHROMA_CSTAT_RESETVAL                (0x00000000U)

/* DEI_HQ_MV_IN_CSTAT */

#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_BUSY_MASK                  (0x00008000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_BUSY_SHIFT                 (15U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_BUSY_RESETVAL              (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_BUSY_MAX                   (0x00000001U)

#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_DMA_ACTIVE_MASK            (0x00004000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_DMA_ACTIVE_SHIFT           (14U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_DMA_ACTIVE_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_DMA_ACTIVE_MAX             (0x00000001U)

#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_FRM_START_MASK             (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_FRM_START_SHIFT            (10U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_FRM_START_RESETVAL         (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_FRM_START_MAX              (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_DELAY_MASK             (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_DELAY_SHIFT            (24U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_DELAY_RESETVAL         (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_DELAY_MAX              (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_RATE_MASK              (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_RATE_SHIFT             (16U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_RATE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_REQ_RATE_MAX               (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_MV_IN_CSTAT_RESETVAL                   (0x00000000U)

/* DEI_HQ_MV_OUT_CSTAT */

#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_BUSY_MASK                 (0x00008000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_BUSY_SHIFT                (15U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_BUSY_RESETVAL             (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_BUSY_MAX                  (0x00000001U)

#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_DMA_ACTIVE_MASK           (0x00004000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_DMA_ACTIVE_SHIFT          (14U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_DMA_ACTIVE_RESETVAL       (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_DMA_ACTIVE_MAX            (0x00000001U)

#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_FRM_START_MASK            (0x00003C00U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_FRM_START_SHIFT           (10U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_FRM_START_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_FRM_START_MAX             (0x0000000fU)

#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_DELAY_MASK            (0xFF000000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_DELAY_SHIFT           (24U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_DELAY_RESETVAL        (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_DELAY_MAX             (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_RATE_MASK             (0x00FF0000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_RATE_SHIFT            (16U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_RATE_RESETVAL         (0x00000000U)
#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_REQ_RATE_MAX              (0x000000ffU)

#define CSL_VPDMA_DEI_HQ_MV_OUT_CSTAT_RESETVAL                  (0x00000000U)

/* VIP1_LO_Y_CSTAT */

#define CSL_VPDMA_VIP1_LO_Y_CSTAT_BUSY_MASK                     (0x00008000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_BUSY_SHIFT                    (15U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_BUSY_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_BUSY_MAX                      (0x00000001U)

#define CSL_VPDMA_VIP1_LO_Y_CSTAT_DMA_ACTIVE_MASK               (0x00004000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_DMA_ACTIVE_SHIFT              (14U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_DMA_ACTIVE_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_DMA_ACTIVE_MAX                (0x00000001U)

#define CSL_VPDMA_VIP1_LO_Y_CSTAT_FRM_START_MASK                (0x00003C00U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_FRM_START_SHIFT               (10U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_FRM_START_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_FRM_START_MAX                 (0x0000000fU)

#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_DELAY_MASK                (0xFF000000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_DELAY_SHIFT               (24U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_DELAY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_DELAY_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_RATE_MASK                 (0x00FF0000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_RATE_SHIFT                (16U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_RATE_RESETVAL             (0x00000000U)
#define CSL_VPDMA_VIP1_LO_Y_CSTAT_REQ_RATE_MAX                  (0x000000ffU)

#define CSL_VPDMA_VIP1_LO_Y_CSTAT_RESETVAL                      (0x00000000U)

/* VIP1_LO_UV_CSTAT */

#define CSL_VPDMA_VIP1_LO_UV_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP1_LO_UV_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP1_LO_UV_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_LO_UV_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP1_LO_UV_CSTAT_RESETVAL                     (0x00000000U)

/* VIP1_UP_Y_CSTAT */

#define CSL_VPDMA_VIP1_UP_Y_CSTAT_BUSY_MASK                     (0x00008000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_BUSY_SHIFT                    (15U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_BUSY_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_BUSY_MAX                      (0x00000001U)

#define CSL_VPDMA_VIP1_UP_Y_CSTAT_DMA_ACTIVE_MASK               (0x00004000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_DMA_ACTIVE_SHIFT              (14U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_DMA_ACTIVE_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_DMA_ACTIVE_MAX                (0x00000001U)

#define CSL_VPDMA_VIP1_UP_Y_CSTAT_FRM_START_MASK                (0x00003C00U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_FRM_START_SHIFT               (10U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_FRM_START_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_FRM_START_MAX                 (0x0000000fU)

#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_DELAY_MASK                (0xFF000000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_DELAY_SHIFT               (24U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_DELAY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_DELAY_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_RATE_MASK                 (0x00FF0000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_RATE_SHIFT                (16U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_RATE_RESETVAL             (0x00000000U)
#define CSL_VPDMA_VIP1_UP_Y_CSTAT_REQ_RATE_MAX                  (0x000000ffU)

#define CSL_VPDMA_VIP1_UP_Y_CSTAT_RESETVAL                      (0x00000000U)

/* VIP1_UP_UV_CSTAT */

#define CSL_VPDMA_VIP1_UP_UV_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP1_UP_UV_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP1_UP_UV_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_UP_UV_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP1_UP_UV_CSTAT_RESETVAL                     (0x00000000U)

/* VIP2_LO_Y_CSTAT */

#define CSL_VPDMA_VIP2_LO_Y_CSTAT_BUSY_MASK                     (0x00008000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_BUSY_SHIFT                    (15U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_BUSY_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_BUSY_MAX                      (0x00000001U)

#define CSL_VPDMA_VIP2_LO_Y_CSTAT_DMA_ACTIVE_MASK               (0x00004000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_DMA_ACTIVE_SHIFT              (14U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_DMA_ACTIVE_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_DMA_ACTIVE_MAX                (0x00000001U)

#define CSL_VPDMA_VIP2_LO_Y_CSTAT_FRM_START_MASK                (0x00003C00U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_FRM_START_SHIFT               (10U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_FRM_START_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_FRM_START_MAX                 (0x0000000fU)

#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_DELAY_MASK                (0xFF000000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_DELAY_SHIFT               (24U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_DELAY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_DELAY_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_RATE_MASK                 (0x00FF0000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_RATE_SHIFT                (16U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_RATE_RESETVAL             (0x00000000U)
#define CSL_VPDMA_VIP2_LO_Y_CSTAT_REQ_RATE_MAX                  (0x000000ffU)

#define CSL_VPDMA_VIP2_LO_Y_CSTAT_RESETVAL                      (0x00000000U)

/* VIP2_LO_UV_CSTAT */

#define CSL_VPDMA_VIP2_LO_UV_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP2_LO_UV_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP2_LO_UV_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_LO_UV_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP2_LO_UV_CSTAT_RESETVAL                     (0x00000000U)

/* VIP2_UP_Y_CSTAT */

#define CSL_VPDMA_VIP2_UP_Y_CSTAT_BUSY_MASK                     (0x00008000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_BUSY_SHIFT                    (15U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_BUSY_RESETVAL                 (0x00000000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_BUSY_MAX                      (0x00000001U)

#define CSL_VPDMA_VIP2_UP_Y_CSTAT_DMA_ACTIVE_MASK               (0x00004000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_DMA_ACTIVE_SHIFT              (14U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_DMA_ACTIVE_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_DMA_ACTIVE_MAX                (0x00000001U)

#define CSL_VPDMA_VIP2_UP_Y_CSTAT_FRM_START_MASK                (0x00003C00U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_FRM_START_SHIFT               (10U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_FRM_START_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_FRM_START_MAX                 (0x0000000fU)

#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_DELAY_MASK                (0xFF000000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_DELAY_SHIFT               (24U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_DELAY_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_DELAY_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_RATE_MASK                 (0x00FF0000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_RATE_SHIFT                (16U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_RATE_RESETVAL             (0x00000000U)
#define CSL_VPDMA_VIP2_UP_Y_CSTAT_REQ_RATE_MAX                  (0x000000ffU)

#define CSL_VPDMA_VIP2_UP_Y_CSTAT_RESETVAL                      (0x00000000U)

/* VIP2_UP_UV_CSTAT */

#define CSL_VPDMA_VIP2_UP_UV_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP2_UP_UV_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP2_UP_UV_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_UP_UV_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP2_UP_UV_CSTAT_RESETVAL                     (0x00000000U)

/* VPI_CTL_CSTAT */

#define CSL_VPDMA_VPI_CTL_CSTAT_BUSY_MASK                       (0x00008000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_BUSY_SHIFT                      (15U)
#define CSL_VPDMA_VPI_CTL_CSTAT_BUSY_RESETVAL                   (0x00000000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_BUSY_MAX                        (0x00000001U)

#define CSL_VPDMA_VPI_CTL_CSTAT_DMA_ACTIVE_MASK                 (0x00004000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_DMA_ACTIVE_SHIFT                (14U)
#define CSL_VPDMA_VPI_CTL_CSTAT_DMA_ACTIVE_RESETVAL             (0x00000000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_DMA_ACTIVE_MAX                  (0x00000001U)

#define CSL_VPDMA_VPI_CTL_CSTAT_FRM_START_MASK                  (0x00003C00U)
#define CSL_VPDMA_VPI_CTL_CSTAT_FRM_START_SHIFT                 (10U)
#define CSL_VPDMA_VPI_CTL_CSTAT_FRM_START_RESETVAL              (0x00000000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_FRM_START_MAX                   (0x0000000fU)

#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_DELAY_MASK                  (0xFF000000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_DELAY_SHIFT                 (24U)
#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_DELAY_RESETVAL              (0x00000000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_DELAY_MAX                   (0x000000ffU)

#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_RATE_MASK                   (0x00FF0000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_RATE_SHIFT                  (16U)
#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_RATE_RESETVAL               (0x00000000U)
#define CSL_VPDMA_VPI_CTL_CSTAT_REQ_RATE_MAX                    (0x000000ffU)

#define CSL_VPDMA_VPI_CTL_CSTAT_RESETVAL                        (0x00000000U)

/* VIP1_ANC_A_CSTAT */

#define CSL_VPDMA_VIP1_ANC_A_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP1_ANC_A_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP1_ANC_A_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_A_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP1_ANC_A_CSTAT_RESETVAL                     (0x00000000U)

/* VIP1_ANC_B_CSTAT */

#define CSL_VPDMA_VIP1_ANC_B_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP1_ANC_B_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP1_ANC_B_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP1_ANC_B_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP1_ANC_B_CSTAT_RESETVAL                     (0x00000000U)

/* VIP2_ANC_A_CSTAT */

#define CSL_VPDMA_VIP2_ANC_A_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP2_ANC_A_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP2_ANC_A_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_A_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP2_ANC_A_CSTAT_RESETVAL                     (0x00000000U)

/* VIP2_ANC_B_CSTAT */

#define CSL_VPDMA_VIP2_ANC_B_CSTAT_BUSY_MASK                    (0x00008000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_BUSY_SHIFT                   (15U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_BUSY_RESETVAL                (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_BUSY_MAX                     (0x00000001U)

#define CSL_VPDMA_VIP2_ANC_B_CSTAT_DMA_ACTIVE_MASK              (0x00004000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_DMA_ACTIVE_SHIFT             (14U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_DMA_ACTIVE_RESETVAL          (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_DMA_ACTIVE_MAX               (0x00000001U)

#define CSL_VPDMA_VIP2_ANC_B_CSTAT_FRM_START_MASK               (0x00003C00U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_FRM_START_SHIFT              (10U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_FRM_START_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_FRM_START_MAX                (0x0000000fU)

#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_DELAY_MASK               (0xFF000000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_DELAY_SHIFT              (24U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_DELAY_RESETVAL           (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_DELAY_MAX                (0x000000ffU)

#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_RATE_MASK                (0x00FF0000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_RATE_SHIFT               (16U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_RATE_RESETVAL            (0x00000000U)
#define CSL_VPDMA_VIP2_ANC_B_CSTAT_REQ_RATE_MAX                 (0x000000ffU)

#define CSL_VPDMA_VIP2_ANC_B_CSTAT_RESETVAL                     (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
