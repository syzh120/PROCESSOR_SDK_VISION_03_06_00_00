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
#ifndef CSLR_DSS_DISPC_H_
#define CSLR_DSS_DISPC_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for VID1_FIR_COEF_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID1_FIR_COEF_H;
    volatile Uint32 VID1_FIR_COEF_HV;
} CSL_Dss_dispcVid1_fir_coef_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK1
**************************************************************************/
typedef struct {
    volatile Uint32 VID1_CONV_COEF0;
    volatile Uint32 VID1_CONV_COEF1;
    volatile Uint32 VID1_CONV_COEF2;
    volatile Uint32 VID1_CONV_COEF3;
    volatile Uint32 VID1_CONV_COEF4;
    volatile Uint8  RSVD0[8];
    volatile Uint32 VID2_BA[2];
    volatile Uint32 VID2_POSITION;
    volatile Uint32 VID2_SIZE;
    volatile Uint32 VID2_ATTRS;
    volatile Uint32 VID2_BUF_THR;
    volatile Uint32 VID2_BUF_SIZE_STS;
    volatile Uint32 VID2_ROW_INC;
    volatile Uint32 VID2_PIXEL_INC;
    volatile Uint32 VID2_FIR;
    volatile Uint32 VID2_PICTURE_SIZE;
    volatile Uint32 VID2_ACCU[2];
} CSL_Dss_dispcBlock1Regs;


/**************************************************************************
* Register Overlay Structure for VID2_FIR_COEF_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID2_FIR_COEF_H;
    volatile Uint32 VID2_FIR_COEF_HV;
} CSL_Dss_dispcVid2_fir_coef_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK2
**************************************************************************/
typedef struct {
    volatile Uint32 VID2_CONV_COEF0;
    volatile Uint32 VID2_CONV_COEF1;
    volatile Uint32 VID2_CONV_COEF2;
    volatile Uint32 VID2_CONV_COEF3;
    volatile Uint32 VID2_CONV_COEF4;
    volatile Uint32 DATA1_CYCLE1;
    volatile Uint32 DATA1_CYCLE2;
    volatile Uint32 DATA1_CYCLE3;
} CSL_Dss_dispcBlock2Regs;


/**************************************************************************
* Register Overlay Structure for VID1_FIR_COEF_V_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID1_FIR_COEF_V;
} CSL_Dss_dispcVid1_fir_coef_v_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for VID2_FIR_COEF_V_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID2_FIR_COEF_V;
} CSL_Dss_dispcVid2_fir_coef_v_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK3
**************************************************************************/
typedef struct {
    volatile Uint32 CPR1_COEF_R;
    volatile Uint32 CPR1_COEF_G;
    volatile Uint32 CPR1_COEF_B;
    volatile Uint32 GFX_PRELOAD;
    volatile Uint32 VID1_PRELOAD;
    volatile Uint32 VID2_PRELOAD;
    volatile Uint32 CTRL2;
    volatile Uint8  RSVD0[4];
    volatile Uint32 GFX_POSITION2;
    volatile Uint32 VID1_POSITION2;
    volatile Uint32 VID2_POSITION2;
    volatile Uint32 VID3_POSITION2;
    volatile Uint8  RSVD1[176];
    volatile Uint32 VID3_ACCU[2];
    volatile Uint32 VID3_BA[2];
} CSL_Dss_dispcBlock3Regs;


/**************************************************************************
* Register Overlay Structure for VID3_FIR_COEF_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID3_FIR_COEF_H;
    volatile Uint32 VID3_FIR_COEF_HV;
} CSL_Dss_dispcVid3_fir_coef_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for VID3_FIR_COEF_V_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID3_FIR_COEF_V;
} CSL_Dss_dispcVid3_fir_coef_v_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK4
**************************************************************************/
typedef struct {
    volatile Uint32 VID3_ATTRS;
    volatile Uint32 VID3_CONV_COEF0;
    volatile Uint32 VID3_CONV_COEF1;
    volatile Uint32 VID3_CONV_COEF2;
    volatile Uint32 VID3_CONV_COEF3;
    volatile Uint32 VID3_CONV_COEF4;
    volatile Uint32 VID3_BUF_SIZE_STS;
    volatile Uint32 VID3_BUF_THR;
    volatile Uint32 VID3_FIR;
    volatile Uint32 VID3_PICTURE_SIZE;
    volatile Uint32 VID3_PIXEL_INC;
    volatile Uint32 VID3_POSITION;
    volatile Uint32 VID3_PRELOAD;
    volatile Uint32 VID3_ROW_INC;
    volatile Uint32 VID3_SIZE;
    volatile Uint32 DEFAULT_COLOR2;
    volatile Uint32 TRANS_COLOR2;
    volatile Uint32 CPR2_COEF_B;
    volatile Uint32 CPR2_COEF_G;
    volatile Uint32 CPR2_COEF_R;
    volatile Uint32 DATA2_CYCLE1;
    volatile Uint32 DATA2_CYCLE2;
    volatile Uint32 DATA2_CYCLE3;
    volatile Uint32 SIZE_LCD2;
    volatile Uint8  RSVD0[48];
    volatile Uint32 TIMING_H2;
    volatile Uint32 TIMING_V2;
    volatile Uint32 POL_FREQ2;
    volatile Uint32 DIVISOR2;
    volatile Uint8  RSVD1[240];
    volatile Uint32 WB_ACCU[2];
    volatile Uint32 WB_BA[2];
} CSL_Dss_dispcBlock4Regs;


/**************************************************************************
* Register Overlay Structure for WB_FIR_COEF_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 WB_FIR_COEF_H;
    volatile Uint32 WB_FIR_COEF_HV;
} CSL_Dss_dispcWb_fir_coef_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for WB_FIR_COEF_V_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 WB_FIR_COEF_V;
} CSL_Dss_dispcWb_fir_coef_v_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK5
**************************************************************************/
typedef struct {
    volatile Uint32 WB_ATTRS;
    volatile Uint32 WB_CONV_COEF0;
    volatile Uint32 WB_CONV_COEF1;
    volatile Uint32 WB_CONV_COEF2;
    volatile Uint32 WB_CONV_COEF3;
    volatile Uint32 WB_CONV_COEF4;
    volatile Uint32 WB_BUF_SIZE_STS;
    volatile Uint32 WB_BUF_THR;
    volatile Uint32 WB_FIR;
    volatile Uint32 WB_PICTURE_SIZE;
    volatile Uint32 WB_PIXEL_INC;
    volatile Uint8  RSVD0[8];
    volatile Uint32 WB_ROW_INC;
    volatile Uint32 WB_SIZE;
    volatile Uint8  RSVD1[84];
    volatile Uint32 VID1_BA_UV[2];
    volatile Uint32 VID2_BA_UV[2];
    volatile Uint32 VID3_BA_UV[2];
    volatile Uint32 WB_BA_UV[2];
    volatile Uint32 CONFIG2;
    volatile Uint32 VID1_ATTRS2;
    volatile Uint32 VID2_ATTRS2;
    volatile Uint32 VID3_ATTRS2;
    volatile Uint32 GAMMA_TBL0;
    volatile Uint32 GAMMA_TBL1;
    volatile Uint32 GAMMA_TBL2;
    volatile Uint32 VID1_FIR2;
    volatile Uint32 VID1_ACCU2[2];
} CSL_Dss_dispcBlock5Regs;


/**************************************************************************
* Register Overlay Structure for VID1_FIR_COEF2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID1_FIR_COEF_H2;
    volatile Uint32 VID1_FIR_COEF_HV2;
} CSL_Dss_dispcVid1_fir_coef2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for VID1_FIR_COEF_V2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID1_FIR_COEF_V2;
} CSL_Dss_dispcVid1_fir_coef_v2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK6
**************************************************************************/
typedef struct {
    volatile Uint32 VID2_FIR2;
    volatile Uint32 VID2_ACCU2[2];
} CSL_Dss_dispcBlock6Regs;


/**************************************************************************
* Register Overlay Structure for VID2_FIR_COEF2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID2_FIR_COEF_H2;
    volatile Uint32 VID2_FIR_COEF_HV2;
} CSL_Dss_dispcVid2_fir_coef2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for VID2_FIR_COEF_V2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID2_FIR_COEF_V2;
} CSL_Dss_dispcVid2_fir_coef_v2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK7
**************************************************************************/
typedef struct {
    volatile Uint32 VID3_FIR2;
    volatile Uint32 VID3_ACCU2[2];
} CSL_Dss_dispcBlock7Regs;


/**************************************************************************
* Register Overlay Structure for VID3_FIR_COEF2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID3_FIR_COEF_H2;
    volatile Uint32 VID3_FIR_COEF_HV2;
} CSL_Dss_dispcVid3_fir_coef2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for VID3_FIR_COEF_V2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 VID3_FIR_COEF_V2;
} CSL_Dss_dispcVid3_fir_coef_v2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK8
**************************************************************************/
typedef struct {
    volatile Uint32 WB_FIR2;
    volatile Uint32 WB_ACCU2[2];
} CSL_Dss_dispcBlock8Regs;


/**************************************************************************
* Register Overlay Structure for WB_FIR_COEF2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 WB_FIR_COEF_H2;
    volatile Uint32 WB_FIR_COEF_HV2;
} CSL_Dss_dispcWb_fir_coef2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for WB_FIR_COEF_V2_REGSET_0_7
**************************************************************************/
typedef struct {
    volatile Uint32 WB_FIR_COEF_V2;
} CSL_Dss_dispcWb_fir_coef_v2_regset_0_7Regs;


/**************************************************************************
* Register Overlay Structure for BLOCK9
**************************************************************************/
typedef struct {
    volatile Uint32 GLOBAL_BUFFER;
    volatile Uint32 DIVISOR;
    volatile Uint8  RSVD0[8];
    volatile Uint32 WB_ATTRS2;
    volatile Uint32 DEFAULT_COLOR3;
    volatile Uint32 TRANS_COLOR3;
    volatile Uint32 CPR3_COEF_B;
    volatile Uint32 CPR3_COEF_G;
    volatile Uint32 CPR3_COEF_R;
    volatile Uint32 DATA3_CYCLE1;
    volatile Uint32 DATA3_CYCLE2;
    volatile Uint32 DATA3_CYCLE3;
    volatile Uint32 SIZE_LCD3;
    volatile Uint32 DIVISOR3;
    volatile Uint32 POL_FREQ3;
    volatile Uint32 TIMING_H3;
    volatile Uint32 TIMING_V3;
    volatile Uint32 CTRL3;
    volatile Uint32 CONFIG3;
    volatile Uint32 GAMMA_TBL3;
    volatile Uint32 BA0_FLIPIMMEDIATE_EN;
    volatile Uint8  RSVD1[4];
    volatile Uint32 GLOBAL_MFLAG_ATTR;
    volatile Uint32 GFX_MFLAG_THR;
    volatile Uint32 VID1_MFLAG_THR;
    volatile Uint32 VID2_MFLAG_THR;
    volatile Uint32 VID3_MFLAG_THR;
    volatile Uint32 WB_MFLAG_THR;
} CSL_Dss_dispcBlock9Regs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint32 REVISION;
    volatile Uint8  RSVD2[12];
    volatile Uint32 SYSCONFIG;
    volatile Uint32 SYSSTS;
    volatile Uint32 IRQSTS;
    volatile Uint32 IRQEN;
    volatile Uint8  RSVD3[32];
    volatile Uint32 CTRL1;
    volatile Uint32 CONFIG1;
    volatile Uint32 CAPABLE;
    volatile Uint32 DEFAULT_COLOR0;
    volatile Uint32 DEFAULT_COLOR1;
    volatile Uint32 TRANS_COLOR0;
    volatile Uint32 TRANS_COLOR1;
    volatile Uint32 LINE_STS;
    volatile Uint32 LINE_NUMBER;
    volatile Uint32 TIMING_H1;
    volatile Uint32 TIMING_V1;
    volatile Uint32 POL_FREQ1;
    volatile Uint32 DIVISOR1;
    volatile Uint32 GLOBAL_ALPHA;
    volatile Uint32 SIZE_TV;
    volatile Uint32 SIZE_LCD1;
    volatile Uint32 GFX_BA[2];
    volatile Uint32 GFX_POSITION;
    volatile Uint32 GFX_SIZE;
    volatile Uint8  RSVD4[16];
    volatile Uint32 GFX_ATTRS;
    volatile Uint32 GFX_BUF_THR;
    volatile Uint32 GFX_BUF_SIZE_STS;
    volatile Uint32 GFX_ROW_INC;
    volatile Uint32 GFX_PIXEL_INC;
    volatile Uint32 GFX_WINDOW_SKIP;
    volatile Uint32 GFX_TBL_BA;
    volatile Uint32 VID1_BA[2];
    volatile Uint32 VID1_POSITION;
    volatile Uint32 VID1_SIZE;
    volatile Uint32 VID1_ATTRS;
    volatile Uint32 VID1_BUF_THR;
    volatile Uint32 VID1_BUF_SIZE_STS;
    volatile Uint32 VID1_ROW_INC;
    volatile Uint32 VID1_PIXEL_INC;
    volatile Uint32 VID1_FIR;
    volatile Uint32 VID1_PICTURE_SIZE;
    volatile Uint32 VID1_ACCU[2];
    CSL_Dss_dispcVid1_fir_coef_regset_0_7Regs	VID1_FIR_COEF_REGSET_0_7[8];
    CSL_Dss_dispcBlock1Regs	BLOCK1;
    CSL_Dss_dispcVid2_fir_coef_regset_0_7Regs	VID2_FIR_COEF_REGSET_0_7[8];
    CSL_Dss_dispcBlock2Regs	BLOCK2;
    CSL_Dss_dispcVid1_fir_coef_v_regset_0_7Regs	VID1_FIR_COEF_V_REGSET_0_7[8];
    CSL_Dss_dispcVid2_fir_coef_v_regset_0_7Regs	VID2_FIR_COEF_V_REGSET_0_7[8];
    CSL_Dss_dispcBlock3Regs	BLOCK3;
    CSL_Dss_dispcVid3_fir_coef_regset_0_7Regs	VID3_FIR_COEF_REGSET_0_7[8];
    CSL_Dss_dispcVid3_fir_coef_v_regset_0_7Regs	VID3_FIR_COEF_V_REGSET_0_7[8];
    CSL_Dss_dispcBlock4Regs	BLOCK4;
    CSL_Dss_dispcWb_fir_coef_regset_0_7Regs	WB_FIR_COEF_REGSET_0_7[8];
    CSL_Dss_dispcWb_fir_coef_v_regset_0_7Regs	WB_FIR_COEF_V_REGSET_0_7[8];
    CSL_Dss_dispcBlock5Regs	BLOCK5;
    CSL_Dss_dispcVid1_fir_coef2_regset_0_7Regs	VID1_FIR_COEF2_REGSET_0_7[8];
    CSL_Dss_dispcVid1_fir_coef_v2_regset_0_7Regs	VID1_FIR_COEF_V2_REGSET_0_7[8];
    CSL_Dss_dispcBlock6Regs	BLOCK6;
    CSL_Dss_dispcVid2_fir_coef2_regset_0_7Regs	VID2_FIR_COEF2_REGSET_0_7[8];
    CSL_Dss_dispcVid2_fir_coef_v2_regset_0_7Regs	VID2_FIR_COEF_V2_REGSET_0_7[8];
    volatile Uint8  RSVD5[16];
    CSL_Dss_dispcBlock7Regs	BLOCK7;
    CSL_Dss_dispcVid3_fir_coef2_regset_0_7Regs	VID3_FIR_COEF2_REGSET_0_7[8];
    CSL_Dss_dispcVid3_fir_coef_v2_regset_0_7Regs	VID3_FIR_COEF_V2_REGSET_0_7[8];
    CSL_Dss_dispcBlock8Regs	BLOCK8;
    volatile Uint8  RSVD6[4];
    CSL_Dss_dispcWb_fir_coef2_regset_0_7Regs	WB_FIR_COEF2_REGSET_0_7[8];
    CSL_Dss_dispcWb_fir_coef_v2_regset_0_7Regs	WB_FIR_COEF_V2_REGSET_0_7[8];
    CSL_Dss_dispcBlock9Regs	BLOCK9;
} CSL_dss_dispcRegs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* This register contains the IP revision code */
#define CSL_DSS_DISPC_REVISION                                  (0x0U)

/* This register allows to control various parameters of the OCP interface. */
#define CSL_DSS_DISPC_SYSCONFIG                                 (0x10U)

/* This register provides status information about the module, excluding the 
 * interrupt status information. */
#define CSL_DSS_DISPC_SYSSTS                                    (0x14U)

/* This register regroups all the status of the module internal events that 
 * generate an interrupt. Write 1 to a given bit resets this bit */
#define CSL_DSS_DISPC_IRQSTS                                    (0x18U)

/* This register allows to mask/unmask the module internal sources of 
 * interrupt, on an event-by-event basis */
#define CSL_DSS_DISPC_IRQEN                                     (0x1CU)

/* The control register configures the Display Controller module for the 
 * primary LCD and TV outputs. */
#define CSL_DSS_DISPC_CTRL1                                     (0x40U)

/* The control register configures the Display Controller module for the 
 * primary LCD output and TV output. Shadow register, updated on VFP start 
 * period of primary LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by 
 * SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_CONFIG1                                   (0x44U)

/* Deprecated register. */
#define CSL_DSS_DISPC_CAPABLE                                   (0x48U)

/* The control register allows to configure the default solid background color 
 * for the primary LCD. Shadow register, updated on VFP start period of the 
 * primary LCD */
#define CSL_DSS_DISPC_DEFAULT_COLOR0                            (0x4CU)

/* The control register allows to configure the default solid background color 
 * for the TV output. Shadow register, updated on EVSYNC */
#define CSL_DSS_DISPC_DEFAULT_COLOR1                            (0x50U)

/* The register sets the transparency color value for the video/graphics 
 * overlays for the pirmary LCD output. Shadow register, updated on VFP start 
 * period of the primary LCD */
#define CSL_DSS_DISPC_TRANS_COLOR0                              (0x54U)

/* The register sets the transparency color value for the video/graphics 
 * overlays for the TV output. Shadow register, updated on EVSYNC */
#define CSL_DSS_DISPC_TRANS_COLOR1                              (0x58U)

/* The control register indicates the current primary LCD panel display line 
 * number. */
#define CSL_DSS_DISPC_LINE_STS                                  (0x5CU)

/* The control register indicates the primary LCD panel display line number 
 * for the interrupt and the DMA request. Shadow register, updated on VFP 
 * start period of primary LCD. */
#define CSL_DSS_DISPC_LINE_NUMBER                               (0x60U)

/* The register configures the timing logic for the HSYNC signal. It is used 
 * for the primary LCD output. Shadow register, updated on VFP start period of 
 * primary LCD */
#define CSL_DSS_DISPC_TIMING_H1                                 (0x64U)

/* The register configures the timing logic for the VSYNC signal. It is used 
 * for the primary LCD output. Shadow register, updated on VFP start period of 
 * primary LCD */
#define CSL_DSS_DISPC_TIMING_V1                                 (0x68U)

/* The register configures the signal configuration. It is used for the 
 * primary LCD output. Shadow register, updated on VFP start period of primary 
 * LCD. */
#define CSL_DSS_DISPC_POL_FREQ1                                 (0x6CU)

/* The register configures the divisors. It is used for the primary LCD output 
 * Shadow register, updated on VFP start period of primary LCD. This register 
 * corresponds to OMAP3430 DISPC_DIVISOR (renamed) */
#define CSL_DSS_DISPC_DIVISOR1                                  (0x70U)

/* The register defines the global alpha value for the graphics and three 
 * video pipelines. Shadow register, updated on VFP start period of primary 
 * LCD or VFP start period of the secondary LCD or VFP start period of the 
 * third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory for each bit-field depending on the association of the each pipeline 
 * with the primary LCD, secondary LCD or TV output. */
#define CSL_DSS_DISPC_GLOBAL_ALPHA                              (0x74U)

/* The register configures the size of the TV output field (interlace), frame 
 * (progressive) (horizontal and vertical). Shadow register, updated on 
 * EVSYNC. A delta value is used to indicate if the odd field has same 
 * vertical size as the even field or +/- one line. */
#define CSL_DSS_DISPC_SIZE_TV                                   (0x78U)

/* The register configures the panel size (horizontal and vertical). Shadow 
 * register, updated on VFP start period of primary LCD. A delta value is used 
 * to indicate if the odd field has same vertical size as the even field or 
 * +/- one line. */
#define CSL_DSS_DISPC_SIZE_LCD1                                 (0x7CU)

/* The register configures the base address of the graphics buffer displayed 
 * in the graphics window (0 & 1 :for ping-pong mechanism with external 
 * trigger, based on the field polarity, 0 only used when graphics pipeline on 
 * the LCD output and 0 & 1 when on the TV output). Shadow register, updated 
 * on VFP start period of primary LCD or VFP start period of the secondary LCD 
 * or VFP start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB 
 * is set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline). The synchronization event is defined based on the 
 * output using the pipeline: primary LCD, secondary LCD, third LCD, TV output 
 * or write-back to the memory */
#define CSL_DSS_DISPC_GFX_BA(i)                                 (0x80U + ((i) * (0x4U)))

/* The register configures the position of the graphics window. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_GFX_POSITION                              (0x88U)

/* The register configures the size of the graphics window. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_GFX_SIZE                                  (0x8CU)

/* The register configures the graphics attributes. Shadow register, updated 
 * on VFP start period of primary LCD or VFP start period of the secondary LCD 
 * or VFP start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB 
 * is set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline). The synchronization event is defined based on the 
 * output using the pipeline: primary LCD, secondary LCD, third LCD, TV output 
 * or write-back to the memory */
#define CSL_DSS_DISPC_GFX_ATTRS                                 (0xA0U)

/* The register configures the graphics buffer. Shadow register, updated on 
 * VFP start period of primary LCD or VFP start period of the secondary LCD or 
 * VFP start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is 
 * set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline). The synchronization event is defined based on the 
 * output using the pipeline: primary LCD, secondary LCD, third LCD, TV output 
 * or write-back to the memory */
#define CSL_DSS_DISPC_GFX_BUF_THR                               (0xA4U)

/* The register defines the Graphics buffer size */
#define CSL_DSS_DISPC_GFX_BUF_SIZE_STS                          (0xA8U)

/* The register configures the number of bytes to increment at the end of the 
 * row. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_GFX_ROW_INC                               (0xACU)

/* The register configures the number of bytes to increment between two 
 * pixels. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_GFX_PIXEL_INC                             (0xB0U)

/* Write 0's for future compatibility. Reads return 0 */
#define CSL_DSS_DISPC_GFX_WINDOW_SKIP                           (0xB4U)

/* The register configures the base address of the palette buffer or the gamma 
 * table buffer. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_GFX_TBL_BA                                (0xB8U)

/* The register configures the base address of the video buffer for the video 
 * window #1 (DISPC_VID1_BA__0 & DISPC_VID1_BA__1 for ping-pong mechanism with 
 * external trigger, based on the field polarity otherwise only 
 * DISPC_VID1_BA__0 is used). Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_BA(i)                                (0xBCU + ((i) * (0x4U)))

/* The register configures the position of the video window #1. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_POSITION                             (0xC4U)

/* The register configures the size of the video window #1. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_SIZE                                 (0xC8U)

/* The register configures the attributes of the video window #1. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_ATTRS                                (0xCCU)

/* The register configures the video buffer associated with the video pipeline 
 * #1. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_BUF_THR                              (0xD0U)

/* The register defines the Video buffer size for the video pipeline #1. */
#define CSL_DSS_DISPC_VID1_BUF_SIZE_STS                         (0xD4U)

/* The register configures the number of bytes to increment at the end of the 
 * row for the buffer associated with the video window #1. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_ROW_INC                              (0xD8U)

/* The register configures the number of bytes to increment between two pixels 
 * for the buffer associated with the video window #2. The register is used 
 * only when the TILER is not present in the system in order to perform low 
 * performance rotation. When the TILER IP is present it is highly recommanded 
 * to use it for performing the rotation. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of the secondary LCD or VFP 
 * start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set 
 * to 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID1_PIXEL_INC                            (0xDCU)

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the video window #1. It is used for ARGB and Y setting. 
 * Shadow register, updated on VFP start period of primary LCD or VFP start 
 * period of the secondary LCD or VFP start period of the third LCD or EVSYNC 
 * or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is 
 * finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_FIR                                  (0xE0U)

/* The register configures the size of the video picture associated with the 
 * video layer #1 before up/down-scaling. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of the secondary LCD or VFP 
 * start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set 
 * to 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE                         (0xE4U)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the video window #1 (DISPC_VID1_ACCU__0 & 
 * DISPC_VID1_ACCU__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity) It is used for ARGB and Y setting. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_ACCU(i)                              (0xE8U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the video window #1 
 * for the phases from 0 to 7. It is used for ARGB and Y setting. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_FIR_COEF_H(n)                        (0xF0U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * video window #1 for the phases from 0 to 7. It is used for ARGB and Y 
 * setting. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV(n)                       (0xF4U + ((n) * (0x8U)))

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #1. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_CONV_COEF0                           (0x130U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #1. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_CONV_COEF1                           (0x134U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #1. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_CONV_COEF2                           (0x138U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #1. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_CONV_COEF3                           (0x13CU)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #1. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_CONV_COEF4                           (0x140U)

/* The register configures the base address of the video buffer for the video 
 * window #2 (DISPC_VID2_BA__0 & DISPC_VID2_BA__1 for ping-pong mechanism with 
 * external trigger, based on the field polarity otherwise only 
 * DISPC_VID2_BA__0 is used)). Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_BA(i)                                (0x14CU + ((i) * (0x4U)))

/* The register configures the position of the video window #2. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_POSITION                             (0x154U)

/* The register configures the size of the video window #2. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_SIZE                                 (0x158U)

/* The register configures the attributes of the video window #2. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_ATTRS                                (0x15CU)

/* The register configures the DMA buffer associated with the video pipeline 
 * #2. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_BUF_THR                              (0x160U)

/* The register defines the DMA buffer size for the video pipeline #2. */
#define CSL_DSS_DISPC_VID2_BUF_SIZE_STS                         (0x164U)

/* The register configures the number of bytes to increment at the end of the 
 * row for the buffer associated with the video window #2. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_ROW_INC                              (0x168U)

/* The register configures the number of bytes to increment between two pixels 
 * for the buffer associated with the video window #2. The register is used 
 * only when the TILER is not present in the system in order to perform low 
 * performance rotation. When the TILER IP is present it is highly recommanded 
 * to use it for performing the rotation. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of the secondary LCD or VFP 
 * start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set 
 * to 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID2_PIXEL_INC                            (0x16CU)

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the video window #2. It is used for ARGB and Y setting. 
 * Shadow register, updated on VFP start period of primary LCD or VFP start 
 * period of the secondary LCD or VFP start period of the third LCD or EVSYNC 
 * or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is 
 * finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_FIR                                  (0x170U)

/* The register configures the size of the video picture associated with the 
 * video layer #2 before up/down-scaling. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of the secondary LCD or VFP 
 * start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set 
 * to 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE                         (0x174U)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the video window #2 (DISPC_VID2_ACCU__0 & 
 * DISPC_VID2_ACCU__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity). It is used for ARGB and Y setting. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_ACCU(i)                              (0x178U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the video window #2 
 * for the phases from 0 to 7. It is used for ARGB and Y setting. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_FIR_COEF_H(n)                        (0x180U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * video window #2 for the phases from 0 to 7. It is used for ARGB and Y 
 * setting. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV(n)                       (0x184U + ((n) * (0x8U)))

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #2. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_CONV_COEF0                           (0x1C0U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #2. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_CONV_COEF1                           (0x1C4U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #2. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_CONV_COEF2                           (0x1C8U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #2. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_CONV_COEF3                           (0x1CCU)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #2. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_CONV_COEF4                           (0x1D0U)

/* The control register configures the output data format for 1st cycle. 
 * Shadow register, updated on VFP start period of primary LCD */
#define CSL_DSS_DISPC_DATA1_CYCLE1                              (0x1D4U)

/* The control register configures the output data format for 2nd cycle. 
 * Shadow register, updated on VFP start period of primary LCD */
#define CSL_DSS_DISPC_DATA1_CYCLE2                              (0x1D8U)

/* The control register configures the output data format for 3rd cycle. 
 * Shadow register, updated on VFP start period of primary LCD */
#define CSL_DSS_DISPC_DATA1_CYCLE3                              (0x1DCU)

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the video window 
 * #1 for the phases from 0 to 7. It is used for ARGB and Y setting. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_FIR_COEF_V(n)                        (0x1E0U + ((n) * (0x4U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the video window 
 * #2 for the phases from 0 to 7. It is used for ARGB and Y setting. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_FIR_COEF_V(n)                        (0x200U + ((n) * (0x4U)))

/* The register configures the color phase rotation matrix coefficients for 
 * the Red component. It is used for the primary LCD output. Shadow register, 
 * updated on VFP start period of primary LCD */
#define CSL_DSS_DISPC_CPR1_COEF_R                               (0x220U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Green component. It is used for the primary LCD output. Shadow 
 * register, updated on VFP start period of primary LCD */
#define CSL_DSS_DISPC_CPR1_COEF_G                               (0x224U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Blue component. It is used for the primary LCD output. Shadow register, 
 * updated on VFP start period of primary LCD */
#define CSL_DSS_DISPC_CPR1_COEF_B                               (0x228U)

/* The register configures the graphics DMA buffer Shadow register, updated on 
 * VFP start period of primary LCD or VFP start period of the secondary LCD or 
 * VFP start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is 
 * set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline). The synchronization event is defined based on the 
 * output using the pipeline: primary LCD, secondary LCD, third LCD, TV output 
 * or write-back to the memory */
#define CSL_DSS_DISPC_GFX_PRELOAD                               (0x22CU)

/* The register configures the DMA buffer of the video #1 pipeline. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_PRELOAD                              (0x230U)

/* The register configures the DMA buffer of the video #2 pipeline. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_PRELOAD                              (0x234U)

/* The control register configures the Display Controller module for the 
 * secondary LCD output. */
#define CSL_DSS_DISPC_CTRL2                                     (0x238U)

/* The register configures the position of the 2nd graphics window in 
 * FramePacking mode. Shadow register, updated on VFP start period of primary 
 * LCD or VFP start period of the secondary LCD or VFP start period of the 
 * third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_GFX_POSITION2                             (0x240U)

/* The register configures the position of the 2nd video window #1 in 
 * FramePacking mode. Shadow register, updated on VFP start period of primary 
 * LCD or VFP start period of the secondary LCD or VFP start period of the 
 * third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_POSITION2                            (0x244U)

/* The register configures the position of the 2nd video window #2. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_POSITION2                            (0x248U)

/* The register configures the position of the 2nd video window #3. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_POSITION2                            (0x24CU)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the video window #3 (DISPC_VID3_ACCU__0 & 
 * DISPC_VID3_ACCU__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity). It is used for ARGB and Y setting. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_ACCU(i)                              (0x300U + ((i) * (0x4U)))

/* The register configures the base address of the video buffer for the video 
 * window #3 (DISPC_VID3_BA__0 & DISPC_VID3_BA__1 for ping-pong mechanism with 
 * external trigger, based on the field polarity otherwise only 
 * DISPC_VID3_BA__0 is used)). Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_BA(i)                                (0x308U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the video window #3 
 * for the phases from 0 to 7. It is used for ARGB and Y setting. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_FIR_COEF_H(n)                        (0x310U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * video window #3 for the phases from 0 to 7. It is used for ARGB and Y 
 * setting. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV(n)                       (0x314U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the video window 
 * #3 for the phases from 0 to 7. It is used for ARGB and Y setting. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_FIR_COEF_V(n)                        (0x350U + ((n) * (0x4U)))

/* The register configures the attributes of the video window #3. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_ATTRS                                (0x370U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #3. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_CONV_COEF0                           (0x374U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #3. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_CONV_COEF1                           (0x378U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #3. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_CONV_COEF2                           (0x37CU)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #3. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_CONV_COEF3                           (0x380U)

/* The register configures the color space conversion matrix coefficients for 
 * the video pipeline #3. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_CONV_COEF4                           (0x384U)

/* The register defines the DMA buffer size for the video pipeline #3. */
#define CSL_DSS_DISPC_VID3_BUF_SIZE_STS                         (0x388U)

/* The register configures the DMA buffer associated with the video pipeline 
 * #3. Shadow register, updated on VFP start period of primary LCD or VFP 
 * start period of the secondary LCD or VFP start period of the third LCD or 
 * EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame 
 * is finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_BUF_THR                              (0x38CU)

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the video window #3. It is used for ARGB and Y setting. 
 * Shadow register, updated on VFP start period of primary LCD or VFP start 
 * period of the secondary LCD or VFP start period of the third LCD or EVSYNC 
 * or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is 
 * finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_FIR                                  (0x390U)

/* The register configures the size of the video picture associated with the 
 * video layer #3 before up/down-scaling. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of the secondary LCD or VFP 
 * start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set 
 * to 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE                         (0x394U)

/* The register configures the number of bytes to increment between two pixels 
 * for the buffer associated with the video window #3. The register is used 
 * only when the TILER is not present in the system in order to perform low 
 * performance rotation. When the TILER IP is present it is highly recommanded 
 * to use it for performing the rotation. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of the secondary LCD or VFP 
 * start period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set 
 * to 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID3_PIXEL_INC                            (0x398U)

/* The register configures the position of the video window #3. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_POSITION                             (0x39CU)

/* The register configures the DMA buffer of the video #3 pipeline. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_PRELOAD                              (0x3A0U)

/* The register configures the number of bytes to increment at the end of the 
 * row for the buffer associated with the video window #3. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_ROW_INC                              (0x3A4U)

/* The register configures the size of the video window #3. Shadow register, 
 * updated on VFP start period of primary LCD or VFP start period of the 
 * secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_SIZE                                 (0x3A8U)

/* The control register allows to configure the default solid background color 
 * for the secondary LCD Shadow register, updated on VFP start period of 
 * secondary LCD */
#define CSL_DSS_DISPC_DEFAULT_COLOR2                            (0x3ACU)

/* The register sets the transparency color value for the video/graphics 
 * overlays for the secondary LCD output. Shadow register, updated on VFP 
 * start period of the secondary LCD */
#define CSL_DSS_DISPC_TRANS_COLOR2                              (0x3B0U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Blue component. It is used for the secondary LCD output. Shadow 
 * register, updated on VFP start period of secondary LCD */
#define CSL_DSS_DISPC_CPR2_COEF_B                               (0x3B4U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Green component. It is used for the secondary LCD output. Shadow 
 * register, updated on VFP start period of secondary LCD */
#define CSL_DSS_DISPC_CPR2_COEF_G                               (0x3B8U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Red component. Shadow register, updated on VFP start period of 
 * secondary LCD */
#define CSL_DSS_DISPC_CPR2_COEF_R                               (0x3BCU)

/* The control register configures the output data format for 1st cycle. 
 * Shadow register, updated on VFP start period of secondary LCD */
#define CSL_DSS_DISPC_DATA2_CYCLE1                              (0x3C0U)

/* The control register configures the output data format for 2nd cycle. 
 * Shadow register, updated on VFP start period of secondary LCD */
#define CSL_DSS_DISPC_DATA2_CYCLE2                              (0x3C4U)

/* The control register configures the output data format for 3rd cycle. 
 * Shadow register, updated on VFP start period of secondary LCD */
#define CSL_DSS_DISPC_DATA2_CYCLE3                              (0x3C8U)

/* The register configures the panel size (horizontal and vertical). It is 
 * used for the secondary LCD output. Shadow register, updated on VFP start 
 * period of secondary LCD. A delta value is used to indicate if the odd field 
 * has same vertical size as the even field or +/- one line. */
#define CSL_DSS_DISPC_SIZE_LCD2                                 (0x3CCU)

/* The register configures the timing logic for the HSYNC signal. It is used 
 * for the secondary LCD output. Shadow register, updated on VFP start period 
 * of secondary LCD */
#define CSL_DSS_DISPC_TIMING_H2                                 (0x400U)

/* The register configures the timing logic for the VSYNC signal. It is used 
 * for the secondary LCD output. Shadow register, updated on VFP start period 
 * of secondary LCD */
#define CSL_DSS_DISPC_TIMING_V2                                 (0x404U)

/* The register configures the signal configuration. It is used for the 
 * secondary LCD output. Shadow register, updated on VFP start period of 
 * secondary LCD */
#define CSL_DSS_DISPC_POL_FREQ2                                 (0x408U)

/* The register configures the divisors. It is used for the secondary LCD 
 * output. Shadow register, updated on VFP start period of secondary LCD */
#define CSL_DSS_DISPC_DIVISOR2                                  (0x40CU)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the write back pipeline (DISPC_WB_ACCU__0 
 * & DISPC_WB_ACCU__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity). It is used for ARGB and Y setting. Shadow register, 
 * updated when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is 
 * finished (no more data in the write-back pipeline) when the WB pipeline is 
 * directly connected to one of the pipelines (graphics or video), otherwise 
 * updated on VFP start period of primary LCD or VFP start period of secondary 
 * LCD or VFP start period of the third LCD or EVSYNC depending on which 
 * overlay output is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_ACCU(i)                                (0x500U + ((i) * (0x4U)))

/* The register configures the base address of the WB buffer (DISPC_WB_BA__0 & 
 * DISPC_WB_BA__1 for ping-pong mechanism with external trigger, based on the 
 * field polarity otherwise only DISPC_WB_BA__0 is used). Shadow register, 
 * updated when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is 
 * finished (no more data in the write-back pipeline) when the WB pipeline is 
 * directly connected to one of the pipelines (graphics or video), otherwise 
 * updated on VFP start period of primary LCD or VFP start period of secondary 
 * LCD or VFP start period of the third LCD or EVSYNC depending on which 
 * overlay output is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_BA(i)                                  (0x508U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the write back 
 * pipeline for the phases from 0 to 7. It is used for ARGB and Y setting. 
 * Shadow register, updated when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline) when 
 * the WB pipeline is directly connected to one of the pipelines (graphics or 
 * video), otherwise updated on VFP start period of primary LCD or VFP start 
 * period of secondary LCD or VFP start period of the third LCD or EVSYNC 
 * depending on which overlay output is selected as an input to the WB 
 * pipeline */
#define CSL_DSS_DISPC_WB_FIR_COEF_H(n)                          (0x510U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * write back pipeline for the phases from 0 to 7. It is used for ARGB and Y 
 * setting. Shadow register, updated when DISPC_CONTROL2.GOWB is set to 1 by 
 * SW and current WB frame is finished (no more data in the write-back 
 * pipeline) when the WB pipeline is directly connected to one of the 
 * pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_FIR_COEF_HV(n)                         (0x514U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the write back 
 * pipeline for the phases from 0 to 7. It is used for ARGB and Y setting. 
 * Shadow register, updated on VFP start period of primary LCD or VFP start 
 * period of the secondary LCD or VFP start period of the third LCD or EVSYNC 
 * or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is 
 * finished (no more data in the write-back pipeline). The synchronization 
 * event is defined based on the output using the pipeline: primary LCD, 
 * secondary LCD, third LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_WB_FIR_COEF_V(n)                          (0x550U + ((n) * (0x4U)))

/* The register configures the attributes of the viwrite back pipeline. Shadow 
 * register, updated when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline) when the WB 
 * pipeline is directly connected to one of the pipelines (graphics or video), 
 * otherwise updated on VFP start period of primary LCD or VFP start period of 
 * secondary LCD or VFP start period of the third LCD or EVSYNC depending on 
 * which overlay output is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_ATTRS                                  (0x570U)

/* The register configures the color space conversion matrix coefficients for 
 * the write back pipeline (YUV444 to RGB24) Shadow register, updated when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline) when the WB pipeline is directly 
 * connected to one of the pipelines (graphics or video), otherwise updated on 
 * VFP start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_CONV_COEF0                             (0x574U)

/* The register configures the color space conversion matrix coefficients for 
 * the write back pipeline. Shadow register, updated when DISPC_CONTROL2.GOWB 
 * is set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline) when the WB pipeline is directly connected to one of 
 * the pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_CONV_COEF1                             (0x578U)

/* The register configures the color space conversion matrix coefficients for 
 * the write back pipeline. Shadow register, updated when DISPC_CONTROL2.GOWB 
 * is set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline) when the WB pipeline is directly connected to one of 
 * the pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_CONV_COEF2                             (0x57CU)

/* The register configures the color space conversion matrix coefficients for 
 * the write back pipeline. Shadow register, updated when DISPC_CONTROL2.GOWB 
 * is set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline) when the WB pipeline is directly connected to one of 
 * the pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_CONV_COEF3                             (0x580U)

/* The register configures the color space conversion matrix coefficients for 
 * the write back pipeline. Shadow register, updated when DISPC_CONTROL2.GOWB 
 * is set to 1 by SW and current WB frame is finished (no more data in the 
 * write-back pipeline) when the WB pipeline is directly connected to one of 
 * the pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_CONV_COEF4                             (0x584U)

/* The register defines the DMA buufer size for the write back pipeline. */
#define CSL_DSS_DISPC_WB_BUF_SIZE_STS                           (0x588U)

/* The register configures the DMA buffer associated with the write-back 
 * pipeline. Shadow register, updated when DISPC_CONTROL2.GOWB is set to 1 by 
 * SW and current WB frame is finished (no more data in the write-back 
 * pipeline) when the WB pipeline is directly connected to one of the 
 * pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_BUF_THR                                (0x58CU)

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the write back pipeline. It is used for ARGB and Y 
 * setting. Shadow register, updated when DISPC_CONTROL2.GOWB is set to 1 by 
 * SW and current WB frame is finished (no more data in the write-back 
 * pipeline) when the WB pipeline is directly connected to one of the 
 * pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_FIR                                    (0x590U)

/* The register configures the size of the write-back picture associated with 
 * the write back pipeline after up/down-scaling (size of the image stored in 
 * DDR memory, generated by WB pipe). Shadow register, updated when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline) when the WB pipeline is directly 
 * connected to one of the pipelines (graphics or video), otherwise updated on 
 * VFP start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_PICTURE_SIZE                           (0x594U)

/* The register configures the number of bytes to increment between two pixels 
 * for the buffer associated with the write back pipeline. The register is 
 * used only when the TILER is not present in the system in order to perform 
 * low performance rotation. When the TILER IP is present it is highly 
 * recommanded to use it for performing the rotation. Shadow register, updated 
 * when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished 
 * (no more data in the write-back pipeline) when the WB pipeline is directly 
 * connected to one of the pipelines (graphics or video), otherwise updated on 
 * VFP start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_PIXEL_INC                              (0x598U)

/* The register configures the number of bytes to increment at the end of the 
 * row for the buffer associated with the vwrite back pipeline. Shadow 
 * register, updated when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline) when the WB 
 * pipeline is directly connected to one of the pipelines (graphics or video), 
 * otherwise updated on VFP start period of primary LCD or VFP start period of 
 * secondary LCD or VFP start period of the third LCD or EVSYNC depending on 
 * which overlay output is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_ROW_INC                                (0x5A4U)

/* The register configures the size of the output of overlay connected to the 
 * write-back pipeline when the overlay output is only used by the write-back 
 * pipeline. When the overlay is output on the primary LCD or secondary LCD or 
 * TV outputs, the size of the frame is defined in the DISPC_SIZE_LCD1, 
 * DISPC_SIZE_LCD2, and DISPC_SIZE_TV respectively. Shadow register, updated 
 * when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished 
 * (no more data in the write-back pipeline) when the WB pipeline is directly 
 * connected to one of the pipelines (graphics or video), otherwise updated on 
 * VFP start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_SIZE                                   (0x5A8U)

/* The register configures the base address of the UV buffer for the video 
 * window #1. (DISPC_VID1_BA_UV__0 & DISPC_VID1_BA_UV__1 for ping-pong 
 * mechanism with external trigger, based on the field polarity otherwise only 
 * DISPC_VID1_BA_UV__0 is used)). Shadow register, updated on VFP start period 
 * of primary LCD or VFP start period of the secondary LCD or VFP start period 
 * of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW 
 * and current WB frame is finished (no more data in the write-back pipeline). 
 * The synchronization event is defined based on the output using the 
 * pipeline: primary LCD, secondary LCD, third LCD, TV output or write-back to 
 * the memory */
#define CSL_DSS_DISPC_VID1_BA_UV(i)                             (0x600U + ((i) * (0x4U)))

/* The register configures the base address of the UV buffer for the video 
 * window #2. (DISPC_VID2_BA_UV__0 & DISPC_VID2_BA_UV__1 for ping-pong 
 * mechanism with external trigger, based on the field polarity otherwise only 
 * DISPC_VID2_BA_UV__0 is used)). Shadow register, updated on VFP start period 
 * of primary LCD or VFP start period of the secondary LCD or VFP start period 
 * of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW 
 * and current WB frame is finished (no more data in the write-back pipeline). 
 * The synchronization event is defined based on the output using the 
 * pipeline: primary LCD, secondary LCD, third LCD, TV output or write-back to 
 * the memory */
#define CSL_DSS_DISPC_VID2_BA_UV(i)                             (0x608U + ((i) * (0x4U)))

/* The register configures the base address of the UV buffer for the video 
 * window #3. (DISPC_VID3_BA_UV__0 & DISPC_VID3_BA_UV__1 for ping-pong 
 * mechanism with external trigger, based on the field polarity otherwise only 
 * DISPC_VID3_BA_UV__0 is used)). Shadow register, updated on VFP start period 
 * of primary LCD or VFP start period of the secondary LCD or VFP start period 
 * of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW 
 * and current WB frame is finished (no more data in the write-back pipeline). 
 * The synchronization event is defined based on the output using the 
 * pipeline: primary LCD, secondary LCD, third LCD, TV output or write-back to 
 * the memory */
#define CSL_DSS_DISPC_VID3_BA_UV(i)                             (0x610U + ((i) * (0x4U)))

/* The register configures the base address of the UV buffer for the 
 * write-back pipeline. (DISPC_WB_BA_UV__0 & DISPC_WB_BA_UV__1 for ping-pong 
 * mechanism with external trigger, based on the field polarity otherwise only 
 * DISPC_WB_BA_UV__0 is used)). Shadow register, updated on VFP start period 
 * of primary LCD or VFP start period of the secondary LCD or VFP start period 
 * of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW 
 * and current WB frame is finished (no more data in the write-back pipeline). 
 * The synchronization event is defined based on the output using the 
 * pipeline: primary LCD, secondary LCD, third LCD, TV output or write-back to 
 * the memory */
#define CSL_DSS_DISPC_WB_BA_UV(i)                               (0x618U + ((i) * (0x4U)))

/* The control register configures the Display Controller module for the 
 * secondary LCD output. Shadow register, updated on VFP start period of 
 * secondary LCD or VFP start period of the third LCD or EVSYNC */
#define CSL_DSS_DISPC_CONFIG2                                   (0x620U)

/* The register configures the attributes of the video window #1. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID1_ATTRS2                               (0x624U)

/* The register configures the attributes of the video window #2. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID2_ATTRS2                               (0x628U)

/* The register configures the attributes of the video window #3. Shadow 
 * register, updated on VFP start period of primary LCD or VFP start period of 
 * the secondary LCD or VFP start period of the third LCD or EVSYNC or when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline). The synchronization event is defined 
 * based on the output using the pipeline: primary LCD, secondary LCD, third 
 * LCD, TV output or write-back to the memory */
#define CSL_DSS_DISPC_VID3_ATTRS2                               (0x62CU)

/* The register configures the look up table used as color look up table for 
 * BITMAP formats (1-, 2-, 4, and 8-bpp) on the graphics pipeline or as gamma 
 * table on the primary LCD output. */
#define CSL_DSS_DISPC_GAMMA_TBL0                                (0x630U)

/* The register configures the gamma table on the secondary LCD output. */
#define CSL_DSS_DISPC_GAMMA_TBL1                                (0x634U)

/* The register configures the gamma table on the TV output. */
#define CSL_DSS_DISPC_GAMMA_TBL2                                (0x638U)

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the video window #1. It is used for Crb and Cr setting. 
 * It is used only when the pixel format at the input of the filter is one of 
 * the YUV formats. If the pixel format at the input of the filter is ARGB 
 * (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space 
 * conversion before going to the filter is the color space conversion is done 
 * before the filter). When the register is not used by the HW, any value can 
 * be used for the bit-fields. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_FIR2                                 (0x63CU)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the video window #1 (DISPC_VID1_ACCU2__0 & 
 * DISPC_VID1_ACCU2__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity) It is used for Cb and Cr setting. It is used only when 
 * the pixel format at the input of the filter is one of the YUV formats. If 
 * the pixel format at the input of the filter is ARGB (all ARGB, RGB, RGBA 
 * are converted to ARGB32-8888 by the color space conversion before going to 
 * the filter is the color space conversion is done before the filter). When 
 * the register is not used by the HW, any value can be used for the 
 * bit-fields. Shadow register, updated on VFP start period of primary LCD or 
 * VFP start period of the secondary LCD or VFP start period of the third LCD 
 * or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_ACCU2(i)                             (0x640U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the video window #1 
 * for the phases from 0 to 7. It is used for Crb and Cr setting. It is used 
 * only when the pixel format at the input of the filter is one of the YUV 
 * formats. If the pixel format at the input of the filter is ARGB (all ARGB, 
 * RGB, RGBA are converted to ARGB32-8888 by the color space conversion before 
 * going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2(n)                       (0x648U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * video window #1 for the phases from 0 to 7. It is used for Crb and Cr 
 * setting. It is used only when the pixel format at the input of the filter 
 * is one of the YUV formats. If the pixel format at the input of the filter 
 * is ARGB (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color 
 * space conversion before going to the filter is the color space conversion 
 * is done before the filter). When the register is not used by the HW, any 
 * value can be used for the bit-fields. Shadow register, updated on VFP start 
 * period of primary LCD or VFP start period of the secondary LCD or VFP start 
 * period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 
 * by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2(n)                      (0x64CU + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the video window 
 * #1 for the phases from 0 to 7. It is used for Crb and Cr setting. It is 
 * used only when the pixel format at the input of the filter is one of the 
 * YUV formats. If the pixel format at the input of the filter is ARGB (all 
 * ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space conversion 
 * before going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2(n)                       (0x688U + ((n) * (0x4U)))

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the video window #2. It is used for Crb and Cr setting. 
 * It is used only when the pixel format at the input of the filter is one of 
 * the YUV formats. If the pixel format at the input of the filter is ARGB 
 * (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space 
 * conversion before going to the filter is the color space conversion is done 
 * before the filter). When the register is not used by the HW, any value can 
 * be used for the bit-fields. Shadow register, updated on VFP start period of 
 * primary LCD or VFP start period of the secondary LCD or VFP start period of 
 * the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and 
 * current WB frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_FIR2                                 (0x6A8U)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the video window #2 (DISPC_VID2_ACCU2__0 & 
 * DISPC_VID2_ACCU2__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity). It is used for Cb and Cr setting. It is used only when 
 * the pixel format at the input of the filter is one of the YUV formats. If 
 * the pixel format at the input of the filter is ARGB (all ARGB, RGB, RGBA 
 * are converted to ARGB32-8888 by the color space conversion before going to 
 * the filter is the color space conversion is done before the filter). When 
 * the register is not used by the HW, any value can be used for the 
 * bit-fields. Shadow register, updated on VFP start period of primary LCD or 
 * VFP start period of the secondary LCD or VFP start period of the third LCD 
 * or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_ACCU2(i)                             (0x6ACU + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the video window #2 
 * for the phases from 0 to 7. It is used for Crb and Cr setting. It is used 
 * only when the pixel format at the input of the filter is one of the YUV 
 * formats. If the pixel format at the input of the filter is ARGB (all ARGB, 
 * RGB, RGBA are converted to ARGB32-8888 by the color space conversion before 
 * going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2(n)                       (0x6B4U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * video window #2 for the phases from 0 to 7. It is used for Crb and Cr 
 * setting. It is used only when the pixel format at the input of the filter 
 * is one of the YUV formats. If the pixel format at the input of the filter 
 * is ARGB (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color 
 * space conversion before going to the filter is the color space conversion 
 * is done before the filter). When the register is not used by the HW, any 
 * value can be used for the bit-fields. Shadow register, updated on VFP start 
 * period of primary LCD or VFP start period of the secondary LCD or VFP start 
 * period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 
 * by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2(n)                      (0x6B8U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the video window 
 * #2 for the phases from 0 to 7. It is used for Crb and Cr setting. It is 
 * used only when the pixel format at the input of the filter is one of the 
 * YUV formats. If the pixel format at the input of the filter is ARGB (all 
 * ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space conversion 
 * before going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2(n)                       (0x6F4U + ((n) * (0x4U)))

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the video window #3.. It is used for Crb and Cr 
 * setting. It is used only when the pixel format at the input of the filter 
 * is one of the YUV formats. If the pixel format at the input of the filter 
 * is ARGB (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color 
 * space conversion before going to the filter is the color space conversion 
 * is done before the filter). When the register is not used by the HW, any 
 * value can be used for the bit-fields. Shadow register, updated on VFP start 
 * period of primary LCD or VFP start period of the secondary LCD or VFP start 
 * period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 
 * by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID3_FIR2                                 (0x724U)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the video window #3 (DISPC_VID3_ACCU2__0 & 
 * DISPC_VID3_ACCU2__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity). It is used for Cb and Cr setting. It is used only when 
 * the pixel format at the input of the filter is one of the YUV formats. If 
 * the pixel format at the input of the filter is ARGB (all ARGB, RGB, RGBA 
 * are converted to ARGB32-8888 by the color space conversion before going to 
 * the filter is the color space conversion is done before the filter). When 
 * the register is not used by the HW, any value can be used for the 
 * bit-fields. Shadow register, updated on VFP start period of primary LCD or 
 * VFP start period of the secondary LCD or VFP start period of the third LCD 
 * or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_ACCU2(i)                             (0x728U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the video window #3 
 * for the phases from 0 to 7. It is used for Crb and Cr setting. It is used 
 * only when the pixel format at the input of the filter is one of the YUV 
 * formats. If the pixel format at the input of the filter is ARGB (all ARGB, 
 * RGB, RGBA are converted to ARGB32-8888 by the color space conversion before 
 * going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2(n)                       (0x730U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * video window #3 for the phases from 0 to 7. It is used for Crb and Cr 
 * setting. It is used only when the pixel format at the input of the filter 
 * is one of the YUV formats. If the pixel format at the input of the filter 
 * is ARGB (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color 
 * space conversion before going to the filter is the color space conversion 
 * is done before the filter). When the register is not used by the HW, any 
 * value can be used for the bit-fields. Shadow register, updated on VFP start 
 * period of primary LCD or VFP start period of the secondary LCD or VFP start 
 * period of the third LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 
 * by SW and current WB frame is finished (no more data in the write-back 
 * pipeline). The synchronization event is defined based on the output using 
 * the pipeline: primary LCD, secondary LCD, third LCD, TV output or 
 * write-back to the memory */
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2(n)                      (0x734U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the video window 
 * #3 for the phases from 0 to 7. It is used for Crb and Cr setting. It is 
 * used only when the pixel format at the input of the filter is one of the 
 * YUV formats. If the pixel format at the input of the filter is ARGB (all 
 * ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space conversion 
 * before going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated on VFP start period of primary LCD 
 * or VFP start period of the secondary LCD or VFP start period of the third 
 * LCD or EVSYNC or when DISPC_CONTROL2.GOWB is set to 1 by SW and current WB 
 * frame is finished (no more data in the write-back pipeline). The 
 * synchronization event is defined based on the output using the pipeline: 
 * primary LCD, secondary LCD, third LCD, TV output or write-back to the 
 * memory */
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2(n)                       (0x770U + ((n) * (0x4U)))

/* The register configures the resize factors for horizontal and vertical 
 * up/down-sampling of the write-back pipeline. It is used for Crb and Cr 
 * setting. It is used only when the pixel format at the input of the filter 
 * is one of the YUV formats. If the pixel format at the input of the filter 
 * is ARGB (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color 
 * space conversion before going to the filter is the color space conversion 
 * is done before the filter). When the register is not used by the HW, any 
 * value can be used for the bit-fields. Shadow register, updated when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline) when the WB pipeline is directly 
 * connected to one of the pipelines (graphics or video), otherwise updated on 
 * VFP start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_FIR2                                   (0x790U)

/* The register configures the resize accumulator init values for horizontal 
 * and vertical up/down-sampling of the write back pipeline (DISPC_WB_ACCU2__0 
 * & DISPC_WB_ACCU2__1 for ping-pong mechanism with external trigger, based on 
 * the field polarity). It is used for Cb and Cr setting. It is used only when 
 * the pixel format at the input of the filter is one of the YUV formats. If 
 * the pixel format at the input of the filter is ARGB (all ARGB, RGB, RGBA 
 * are converted to ARGB32-8888 by the color space conversion before going to 
 * the filter is the color space conversion is done before the filter). When 
 * the register is not used by the HW, any value can be used for the 
 * bit-fields. Shadow register, updated when DISPC_CONTROL2.GOWB is set to 1 
 * by SW and current WB frame is finished (no more data in the write-back 
 * pipeline) when the WB pipeline is directly connected to one of the 
 * pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_ACCU2(i)                               (0x794U + ((i) * (0x4U)))

/* The bank of registers configure the up/down-scaling coefficients for the 
 * horizontal resize of the video picture associated with the write back 
 * pipeline for the phases from 0 to 7. It is used for Crb and Cr setting. It 
 * is used only when the pixel format at the input of the filter is one of the 
 * YUV formats. If the pixel format at the input of the filter is ARGB (all 
 * ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space conversion 
 * before going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated when DISPC_CONTROL2.GOWB is set to 
 * 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline) when the WB pipeline is directly connected to one of the 
 * pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_FIR_COEF_H2(n)                         (0x7A0U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical and horizontal resize of the video picture associated with the 
 * write back pipeline for the phases from 0 to 7. It is used for Crb and Cr 
 * setting. It is used only when the pixel format at the input of the filter 
 * is one of the YUV formats. If the pixel format at the input of the filter 
 * is ARGB (all ARGB, RGB, RGBA are converted to ARGB32-8888 by the color 
 * space conversion before going to the filter is the color space conversion 
 * is done before the filter). When the register is not used by the HW, any 
 * value can be used for the bit-fields. Shadow register, updated when 
 * DISPC_CONTROL2.GOWB is set to 1 by SW and current WB frame is finished (no 
 * more data in the write-back pipeline) when the WB pipeline is directly 
 * connected to one of the pipelines (graphics or video), otherwise updated on 
 * VFP start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2(n)                        (0x7A4U + ((n) * (0x8U)))

/* The bank of registers configure the down/up/down-scaling coefficients for 
 * the vertical resize of the video picture associated with the write back 
 * pipeline for the phases from 0 to 7. It is used for Crb and Cr setting. It 
 * is used only when the pixel format at the input of the filter is one of the 
 * YUV formats. If the pixel format at the input of the filter is ARGB (all 
 * ARGB, RGB, RGBA are converted to ARGB32-8888 by the color space conversion 
 * before going to the filter is the color space conversion is done before the 
 * filter). When the register is not used by the HW, any value can be used for 
 * the bit-fields. Shadow register, updated when DISPC_CONTROL2.GOWB is set to 
 * 1 by SW and current WB frame is finished (no more data in the write-back 
 * pipeline) when the WB pipeline is directly connected to one of the 
 * pipelines (graphics or video), otherwise updated on VFP start period of 
 * primary LCD or VFP start period of secondary LCD or VFP start period of the 
 * third LCD or EVSYNC depending on which overlay output is selected as an 
 * input to the WB pipeline */
#define CSL_DSS_DISPC_WB_FIR_COEF_V2(n)                         (0x7E0U + ((n) * (0x4U)))

/* The register configures the DMA buffers allocations to the pipeline 
 * (graphics, video1, video2, video3 and write-back) */
#define CSL_DSS_DISPC_GLOBAL_BUFFER                             (0x800U)

/* The register configures the divisor value for generating the core 
 * functional clock. There is a backward compatibility mode enabled by default 
 * in order to use DISPC_DIVISOR1.LCD value instead of DISPC_DIVISOR.LCD 
 * bit-field for generating the core functional clock. */
#define CSL_DSS_DISPC_DIVISOR                                   (0x804U)

/* The register set the counter to control the delay to flush the WB pipe 
 * after the end of the frame in capture mode. Shadow register, updated on VFP 
 * start period of primary LCD or VFP start period of secondary LCD or VFP 
 * start period of the third LCD or EVSYNC depending on which overlay output 
 * is selected as an input to the WB pipeline */
#define CSL_DSS_DISPC_WB_ATTRS2                                 (0x810U)

/* The control register allows to configure the default solid background color 
 * for the third LCD Shadow register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_DEFAULT_COLOR3                            (0x814U)

/* The register sets the transparency color value for the video/graphics 
 * overlays for the third LCD output. Shadow register, updated on VFP start 
 * period of the third LCD */
#define CSL_DSS_DISPC_TRANS_COLOR3                              (0x818U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Blue component. It is used for the secondary LCD output. Shadow 
 * register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_CPR3_COEF_B                               (0x81CU)

/* The register configures the color phase rotation matrix coefficients for 
 * the Green component. It is used for the secondary LCD output. Shadow 
 * register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_CPR3_COEF_G                               (0x820U)

/* The register configures the color phase rotation matrix coefficients for 
 * the Red component. Shadow register, updated on VFP start period of third 
 * LCD */
#define CSL_DSS_DISPC_CPR3_COEF_R                               (0x824U)

/* The control register configures the output data format for 1st cycle. 
 * Shadow register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_DATA3_CYCLE1                              (0x828U)

/* The control register configures the output data format for 2nd cycle. 
 * Shadow register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_DATA3_CYCLE2                              (0x82CU)

/* The control register configures the output data format for 3rd cycle. 
 * Shadow register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_DATA3_CYCLE3                              (0x830U)

/* The register configures the panel size (horizontal and vertical). It is 
 * used for the third LCD output. Shadow register, updated on VFP start period 
 * of third LCD. A delta value is used to indicate if the odd field has same 
 * vertical size as the even field or +/- one line. */
#define CSL_DSS_DISPC_SIZE_LCD3                                 (0x834U)

/* The register configures the divisors. It is used for the third LCD output. 
 * Shadow register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_DIVISOR3                                  (0x838U)

/* The register configures the signal configuration. It is used for the third 
 * LCD output. Shadow register, updated on VFP start period of third LCD */
#define CSL_DSS_DISPC_POL_FREQ3                                 (0x83CU)

/* The register configures the timing logic for the HSYNC signal. It is used 
 * for the third LCD output. Shadow register, updated on VFP start period of 
 * third LCD */
#define CSL_DSS_DISPC_TIMING_H3                                 (0x840U)

/* The register configures the timing logic for the VSYNC signal. It is used 
 * for the third LCD output. Shadow register, updated on VFP start period of 
 * third LCD */
#define CSL_DSS_DISPC_TIMING_V3                                 (0x844U)

/* The control register configures the Display Controller module for the third 
 * LCD output. */
#define CSL_DSS_DISPC_CTRL3                                     (0x848U)

/* The control register configures the Display Controller module for the third 
 * LCD output. Shadow register, updated on VFP start period of third LCD or 
 * EVSYNC */
#define CSL_DSS_DISPC_CONFIG3                                   (0x84CU)

/* The register configures the gamma table on the third LCD output. */
#define CSL_DSS_DISPC_GAMMA_TBL3                                (0x850U)

/* BA0_FLIPIMMEDIATE_EN */
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN                      (0x854U)

/* GLOBAL_MFLAG_ATTR */
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR                         (0x85CU)

/* GFX_MFLAG_THR */
#define CSL_DSS_DISPC_GFX_MFLAG_THR                             (0x860U)

/* VID1_MFLAG_THR */
#define CSL_DSS_DISPC_VID1_MFLAG_THR                            (0x864U)

/* VID2_MFLAG_THR */
#define CSL_DSS_DISPC_VID2_MFLAG_THR                            (0x868U)

/* VID3_MFLAG_THR */
#define CSL_DSS_DISPC_VID3_MFLAG_THR                            (0x86CU)

/* WB_MFLAG_THR */
#define CSL_DSS_DISPC_WB_MFLAG_THR                              (0x870U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* REVISION */

#define CSL_DSS_DISPC_REVISION_REV_MASK                         (0x000000FFU)
#define CSL_DSS_DISPC_REVISION_REV_SHIFT                        (0U)
#define CSL_DSS_DISPC_REVISION_REV_RESETVAL                     (0x00000051U)
#define CSL_DSS_DISPC_REVISION_REV_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_REVISION_RESETVAL                         (0x00000051U)

/* SYSCONFIG */

#define CSL_DSS_DISPC_SYSCONFIG_SOFTRESET_MASK                  (0x00000002U)
#define CSL_DSS_DISPC_SYSCONFIG_SOFTRESET_SHIFT                 (1U)
#define CSL_DSS_DISPC_SYSCONFIG_SOFTRESET_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_SOFTRESET_NMODE                 (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_SOFTRESET_RST                   (0x00000001U)

#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_MASK                  (0x00000018U)
#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_SHIFT                 (3U)
#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_FIDLE                 (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_NIDLE                 (0x00000001U)
#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_SIDLE                 (0x00000002U)
#define CSL_DSS_DISPC_SYSCONFIG_SIDLEMODE_RES                   (0x00000003U)

#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_MASK                  (0x00003000U)
#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_SHIFT                 (12U)
#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_FSTANDBY              (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_NSTANDBY              (0x00000001U)
#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_SSTANDBY              (0x00000002U)
#define CSL_DSS_DISPC_SYSCONFIG_MIDLEMODE_RES                   (0x00000003U)

#define CSL_DSS_DISPC_SYSCONFIG_AUTOIDLE_MASK                   (0x00000001U)
#define CSL_DSS_DISPC_SYSCONFIG_AUTOIDLE_SHIFT                  (0U)
#define CSL_DSS_DISPC_SYSCONFIG_AUTOIDLE_RESETVAL               (0x00000001U)
#define CSL_DSS_DISPC_SYSCONFIG_AUTOIDLE_CLKFREE                (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_AUTOIDLE_CLKGATED               (0x00000001U)

#define CSL_DSS_DISPC_SYSCONFIG_ENWAKEUP_MASK                   (0x00000004U)
#define CSL_DSS_DISPC_SYSCONFIG_ENWAKEUP_SHIFT                  (2U)
#define CSL_DSS_DISPC_SYSCONFIG_ENWAKEUP_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_ENWAKEUP_WAKEUPENB              (0x00000001U)
#define CSL_DSS_DISPC_SYSCONFIG_ENWAKEUP_WAKEUPDIS              (0x00000000U)

#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_MASK              (0x00000300U)
#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_SHIFT             (8U)
#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPFUNCOFF        (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPFUNCON         (0x00000003U)
#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_OCPOFF            (0x00000002U)
#define CSL_DSS_DISPC_SYSCONFIG_CLOCKACTIVITY_FUNCOFF           (0x00000001U)

#define CSL_DSS_DISPC_SYSCONFIG_WARMRESET_MASK                  (0x00000020U)
#define CSL_DSS_DISPC_SYSCONFIG_WARMRESET_SHIFT                 (5U)
#define CSL_DSS_DISPC_SYSCONFIG_WARMRESET_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_WARMRESET_NORMAL                (0x00000000U)
#define CSL_DSS_DISPC_SYSCONFIG_WARMRESET_WARMRESET             (0x00000001U)

#define CSL_DSS_DISPC_SYSCONFIG_RESETVAL                        (0x00000001U)

/* SYSSTS */

#define CSL_DSS_DISPC_SYSSTS_RESETDONE_MASK                     (0x00000001U)
#define CSL_DSS_DISPC_SYSSTS_RESETDONE_SHIFT                    (0U)
#define CSL_DSS_DISPC_SYSSTS_RESETDONE_RESETVAL                 (0x00000001U)
#define CSL_DSS_DISPC_SYSSTS_RESETDONE_RSTONGOING               (0x00000000U)
#define CSL_DSS_DISPC_SYSSTS_RESETDONE_RSTCOMP                  (0x00000001U)

#define CSL_DSS_DISPC_SYSSTS_RESETVAL                           (0x00000001U)

/* IRQSTS */

#define CSL_DSS_DISPC_IRQSTS_VID2ENDWINDOW_IRQ_MASK             (0x00002000U)
#define CSL_DSS_DISPC_IRQSTS_VID2ENDWINDOW_IRQ_SHIFT            (13U)
#define CSL_DSS_DISPC_IRQSTS_VID2ENDWINDOW_IRQ_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID2ENDWINDOW_IRQ_FALSE            (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID2ENDWINDOW_IRQ_TRUE             (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VID1BUFFERUNDERFLOW_IRQ_MASK       (0x00000400U)
#define CSL_DSS_DISPC_IRQSTS_VID1BUFFERUNDERFLOW_IRQ_SHIFT      (10U)
#define CSL_DSS_DISPC_IRQSTS_VID1BUFFERUNDERFLOW_IRQ_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID1BUFFERUNDERFLOW_IRQ_FALSE      (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID1BUFFERUNDERFLOW_IRQ_TRUE       (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_SYNCLOST1_IRQ_MASK                 (0x00004000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST1_IRQ_SHIFT                (14U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST1_IRQ_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST1_IRQ_FALSE                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST1_IRQ_TRUE                 (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_GFXENDWINDOW_IRQ_MASK              (0x00000080U)
#define CSL_DSS_DISPC_IRQSTS_GFXENDWINDOW_IRQ_SHIFT             (7U)
#define CSL_DSS_DISPC_IRQSTS_GFXENDWINDOW_IRQ_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_GFXENDWINDOW_IRQ_FALSE             (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_GFXENDWINDOW_IRQ_TRUE              (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VID1ENDWINDOW_IRQ_MASK             (0x00000800U)
#define CSL_DSS_DISPC_IRQSTS_VID1ENDWINDOW_IRQ_SHIFT            (11U)
#define CSL_DSS_DISPC_IRQSTS_VID1ENDWINDOW_IRQ_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID1ENDWINDOW_IRQ_FALSE            (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID1ENDWINDOW_IRQ_TRUE             (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_PALETTEGAMMALOADING_IRQ_MASK       (0x00000100U)
#define CSL_DSS_DISPC_IRQSTS_PALETTEGAMMALOADING_IRQ_SHIFT      (8U)
#define CSL_DSS_DISPC_IRQSTS_PALETTEGAMMALOADING_IRQ_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_PALETTEGAMMALOADING_IRQ_FALSE      (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_PALETTEGAMMALOADING_IRQ_TRUE       (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_PROGRAMMEDLINENUMBER_IRQ_MASK      (0x00000020U)
#define CSL_DSS_DISPC_IRQSTS_PROGRAMMEDLINENUMBER_IRQ_SHIFT     (5U)
#define CSL_DSS_DISPC_IRQSTS_PROGRAMMEDLINENUMBER_IRQ_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_PROGRAMMEDLINENUMBER_IRQ_FALSE     (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_PROGRAMMEDLINENUMBER_IRQ_TRUE      (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_OCPERROR_IRQ_MASK                  (0x00000200U)
#define CSL_DSS_DISPC_IRQSTS_OCPERROR_IRQ_SHIFT                 (9U)
#define CSL_DSS_DISPC_IRQSTS_OCPERROR_IRQ_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_OCPERROR_IRQ_FALSE                 (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_OCPERROR_IRQ_TRUE                  (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_EVSYNC_EVEN_IRQ_MASK               (0x00000004U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_EVEN_IRQ_SHIFT              (2U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_EVEN_IRQ_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_EVEN_IRQ_FALSE              (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_EVEN_IRQ_TRUE               (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_GFXBUFFERUNDERFLOW_IRQ_MASK        (0x00000040U)
#define CSL_DSS_DISPC_IRQSTS_GFXBUFFERUNDERFLOW_IRQ_SHIFT       (6U)
#define CSL_DSS_DISPC_IRQSTS_GFXBUFFERUNDERFLOW_IRQ_RESETVAL    (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_GFXBUFFERUNDERFLOW_IRQ_FALSE       (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_GFXBUFFERUNDERFLOW_IRQ_TRUE        (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_EVSYNC_ODD_IRQ_MASK                (0x00000008U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_ODD_IRQ_SHIFT               (3U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_ODD_IRQ_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_ODD_IRQ_FALSE               (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_EVSYNC_ODD_IRQ_TRUE                (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_FRMDONE1_IRQ_MASK                  (0x00000001U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE1_IRQ_SHIFT                 (0U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE1_IRQ_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE1_IRQ_FALSE                 (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE1_IRQ_TRUE                  (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS1_IRQ_MASK           (0x00000010U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS1_IRQ_SHIFT          (4U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS1_IRQ_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS1_IRQ_FALSE          (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS1_IRQ_TRUE           (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VSYNC1_IRQ_MASK                    (0x00000002U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC1_IRQ_SHIFT                   (1U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC1_IRQ_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC1_IRQ_FALSE                   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC1_IRQ_TRUE                    (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_SYNCLOSTTV_IRQ_MASK                (0x00008000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOSTTV_IRQ_SHIFT               (15U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOSTTV_IRQ_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOSTTV_IRQ_FALSE               (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOSTTV_IRQ_TRUE                (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VID2BUFFERUNDERFLOW_IRQ_MASK       (0x00001000U)
#define CSL_DSS_DISPC_IRQSTS_VID2BUFFERUNDERFLOW_IRQ_SHIFT      (12U)
#define CSL_DSS_DISPC_IRQSTS_VID2BUFFERUNDERFLOW_IRQ_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID2BUFFERUNDERFLOW_IRQ_FALSE      (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID2BUFFERUNDERFLOW_IRQ_TRUE       (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_WAKEUP_IRQ_MASK                    (0x00010000U)
#define CSL_DSS_DISPC_IRQSTS_WAKEUP_IRQ_SHIFT                   (16U)
#define CSL_DSS_DISPC_IRQSTS_WAKEUP_IRQ_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_WAKEUP_IRQ_FALSE                   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_WAKEUP_IRQ_TRUE                    (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VSYNC2_IRQ_MASK                    (0x00040000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC2_IRQ_SHIFT                   (18U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC2_IRQ_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC2_IRQ_FALSE                   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC2_IRQ_TRUE                    (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VID3ENDWINDOW_IRQ_MASK             (0x00080000U)
#define CSL_DSS_DISPC_IRQSTS_VID3ENDWINDOW_IRQ_SHIFT            (19U)
#define CSL_DSS_DISPC_IRQSTS_VID3ENDWINDOW_IRQ_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID3ENDWINDOW_IRQ_FALSE            (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID3ENDWINDOW_IRQ_TRUE             (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VID3BUFFERUNDERFLOW_IRQ_MASK       (0x00100000U)
#define CSL_DSS_DISPC_IRQSTS_VID3BUFFERUNDERFLOW_IRQ_SHIFT      (20U)
#define CSL_DSS_DISPC_IRQSTS_VID3BUFFERUNDERFLOW_IRQ_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID3BUFFERUNDERFLOW_IRQ_FALSE      (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VID3BUFFERUNDERFLOW_IRQ_TRUE       (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS2_IRQ_MASK           (0x00200000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS2_IRQ_SHIFT          (21U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS2_IRQ_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS2_IRQ_FALSE          (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS2_IRQ_TRUE           (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_SYNCLOST2_IRQ_MASK                 (0x00020000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST2_IRQ_SHIFT                (17U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST2_IRQ_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST2_IRQ_FALSE                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST2_IRQ_TRUE                 (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_FRMDONE2_IRQ_MASK                  (0x00400000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE2_IRQ_SHIFT                 (22U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE2_IRQ_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE2_IRQ_FALSE                 (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE2_IRQ_TRUE                  (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_FRMDONEWB_IRQ_MASK                 (0x00800000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONEWB_IRQ_SHIFT                (23U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONEWB_IRQ_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONEWB_IRQ_FALSE                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONEWB_IRQ_TRUE                 (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_FRMDONETV_IRQ_MASK                 (0x01000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONETV_IRQ_SHIFT                (24U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONETV_IRQ_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONETV_IRQ_FALSE                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONETV_IRQ_TRUE                 (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_WBBUFFEROVERFLOW_IRQ_MASK          (0x02000000U)
#define CSL_DSS_DISPC_IRQSTS_WBBUFFEROVERFLOW_IRQ_SHIFT         (25U)
#define CSL_DSS_DISPC_IRQSTS_WBBUFFEROVERFLOW_IRQ_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_WBBUFFEROVERFLOW_IRQ_FALSE         (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_WBBUFFEROVERFLOW_IRQ_TRUE          (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_WBUNCOMPLETEERROR_IRQ_MASK         (0x04000000U)
#define CSL_DSS_DISPC_IRQSTS_WBUNCOMPLETEERROR_IRQ_SHIFT        (26U)
#define CSL_DSS_DISPC_IRQSTS_WBUNCOMPLETEERROR_IRQ_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_WBUNCOMPLETEERROR_IRQ_FALSE        (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_WBUNCOMPLETEERROR_IRQ_TRUE         (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_SYNCLOST3_IRQ_MASK                 (0x08000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST3_IRQ_SHIFT                (27U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST3_IRQ_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST3_IRQ_FALSE                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_SYNCLOST3_IRQ_TRUE                 (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_VSYNC3_IRQ_MASK                    (0x10000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC3_IRQ_SHIFT                   (28U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC3_IRQ_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC3_IRQ_FALSE                   (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_VSYNC3_IRQ_TRUE                    (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_FRMDONE3_IRQ_MASK                  (0x40000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE3_IRQ_SHIFT                 (30U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE3_IRQ_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE3_IRQ_FALSE                 (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FRMDONE3_IRQ_TRUE                  (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS3_IRQ_MASK           (0x20000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS3_IRQ_SHIFT          (29U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS3_IRQ_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS3_IRQ_FALSE          (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_ACBIASCOUNTSTS3_IRQ_TRUE           (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_FLIPIMMEDIATEDONE_IRQ_MASK         (0x80000000U)
#define CSL_DSS_DISPC_IRQSTS_FLIPIMMEDIATEDONE_IRQ_SHIFT        (31U)
#define CSL_DSS_DISPC_IRQSTS_FLIPIMMEDIATEDONE_IRQ_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FLIPIMMEDIATEDONE_IRQ_FALSE        (0x00000000U)
#define CSL_DSS_DISPC_IRQSTS_FLIPIMMEDIATEDONE_IRQ_TRUE         (0x00000001U)

#define CSL_DSS_DISPC_IRQSTS_RESETVAL                           (0x00000000U)

/* IRQEN */

#define CSL_DSS_DISPC_IRQEN_EVSYNC_ODD_EN_MASK                  (0x00000008U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_ODD_EN_SHIFT                 (3U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_ODD_EN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_ODD_EN_MASKED                (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_ODD_EN_GENINT                (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_FRMDONE_EN_MASK                     (0x00000001U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE_EN_SHIFT                    (0U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE_EN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE_EN_MASKED                   (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE_EN_GENINT                   (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_EVSYNC_EVEN_EN_MASK                 (0x00000004U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_EVEN_EN_SHIFT                (2U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_EVEN_EN_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_EVEN_EN_MASKED               (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_EVSYNC_EVEN_EN_GENINT               (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VSYNC1_EN_MASK                      (0x00000002U)
#define CSL_DSS_DISPC_IRQEN_VSYNC1_EN_SHIFT                     (1U)
#define CSL_DSS_DISPC_IRQEN_VSYNC1_EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC1_EN_MASKED                    (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC1_EN_GENINT                    (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_SYNCLOSTTV_EN_MASK                  (0x00008000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOSTTV_EN_SHIFT                 (15U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOSTTV_EN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOSTTV_EN_MASKED                (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOSTTV_EN_GENINT                (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VID1BUFFERUNDERFLOW_EN_MASK         (0x00000400U)
#define CSL_DSS_DISPC_IRQEN_VID1BUFFERUNDERFLOW_EN_SHIFT        (10U)
#define CSL_DSS_DISPC_IRQEN_VID1BUFFERUNDERFLOW_EN_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID1BUFFERUNDERFLOW_EN_MASKED       (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID1BUFFERUNDERFLOW_EN_GENINT       (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VID2BUFFERUNDERFLOW_EN_MASK         (0x00001000U)
#define CSL_DSS_DISPC_IRQEN_VID2BUFFERUNDERFLOW_EN_SHIFT        (12U)
#define CSL_DSS_DISPC_IRQEN_VID2BUFFERUNDERFLOW_EN_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID2BUFFERUNDERFLOW_EN_MASKED       (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID2BUFFERUNDERFLOW_EN_GENINT       (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_SYNCLOST1_EN_MASK                   (0x00004000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST1_EN_SHIFT                  (14U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST1_EN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST1_EN_MASKED                 (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST1_EN_GENINT                 (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_PROGRAMMEDLINENUMBER_EN_MASK        (0x00000020U)
#define CSL_DSS_DISPC_IRQEN_PROGRAMMEDLINENUMBER_EN_SHIFT       (5U)
#define CSL_DSS_DISPC_IRQEN_PROGRAMMEDLINENUMBER_EN_RESETVAL    (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_PROGRAMMEDLINENUMBER_EN_MASKED      (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_PROGRAMMEDLINENUMBER_EN_GENINT      (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_GFXENDWINDOW_EN_MASK                (0x00000080U)
#define CSL_DSS_DISPC_IRQEN_GFXENDWINDOW_EN_SHIFT               (7U)
#define CSL_DSS_DISPC_IRQEN_GFXENDWINDOW_EN_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_GFXENDWINDOW_EN_MASKED              (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_GFXENDWINDOW_EN_GENINT              (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_OCPERROR_EN_MASK                    (0x00000200U)
#define CSL_DSS_DISPC_IRQEN_OCPERROR_EN_SHIFT                   (9U)
#define CSL_DSS_DISPC_IRQEN_OCPERROR_EN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_OCPERROR_EN_MASKED                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_OCPERROR_EN_GENINT                  (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_ENDVID1WINDOW_EN_MASK               (0x00000800U)
#define CSL_DSS_DISPC_IRQEN_ENDVID1WINDOW_EN_SHIFT              (11U)
#define CSL_DSS_DISPC_IRQEN_ENDVID1WINDOW_EN_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ENDVID1WINDOW_EN_MASKED             (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ENDVID1WINDOW_EN_GENINT             (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VID2ENDWINDOW_EN_MASK               (0x00002000U)
#define CSL_DSS_DISPC_IRQEN_VID2ENDWINDOW_EN_SHIFT              (13U)
#define CSL_DSS_DISPC_IRQEN_VID2ENDWINDOW_EN_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID2ENDWINDOW_EN_MASKED             (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID2ENDWINDOW_EN_GENINT             (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS1_EN_MASK             (0x00000010U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS1_EN_SHIFT            (4U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS1_EN_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS1_EN_MASKED           (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS1_EN_GENINT           (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_GFXBUFFERUNDERFLOW_EN_MASK          (0x00000040U)
#define CSL_DSS_DISPC_IRQEN_GFXBUFFERUNDERFLOW_EN_SHIFT         (6U)
#define CSL_DSS_DISPC_IRQEN_GFXBUFFERUNDERFLOW_EN_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_GFXBUFFERUNDERFLOW_EN_MASKED        (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_GFXBUFFERUNDERFLOW_EN_GENINT        (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_PALETTEGAMMA_EN_MASK                (0x00000100U)
#define CSL_DSS_DISPC_IRQEN_PALETTEGAMMA_EN_SHIFT               (8U)
#define CSL_DSS_DISPC_IRQEN_PALETTEGAMMA_EN_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_PALETTEGAMMA_EN_MASKED              (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_PALETTEGAMMA_EN_GENINT              (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_WAKEUP_EN_MASK                      (0x00010000U)
#define CSL_DSS_DISPC_IRQEN_WAKEUP_EN_SHIFT                     (16U)
#define CSL_DSS_DISPC_IRQEN_WAKEUP_EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_WAKEUP_EN_GENINT                    (0x00000001U)
#define CSL_DSS_DISPC_IRQEN_WAKEUP_EN_MASKED                    (0x00000000U)

#define CSL_DSS_DISPC_IRQEN_FRMDONE2_EN_MASK                    (0x00400000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE2_EN_SHIFT                   (22U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE2_EN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE2_EN_MASKED                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE2_EN_GENINT                  (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VSYNC2_EN_MASK                      (0x00040000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC2_EN_SHIFT                     (18U)
#define CSL_DSS_DISPC_IRQEN_VSYNC2_EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC2_EN_MASKED                    (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC2_EN_GENINT                    (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS2_EN_MASK             (0x00200000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS2_EN_SHIFT            (21U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS2_EN_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS2_EN_MASKED           (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS2_EN_GENINT           (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_SYNCLOST2_EN_MASK                   (0x00020000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST2_EN_SHIFT                  (17U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST2_EN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST2_EN_MASKED                 (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST2_EN_GENINT                 (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VID3ENDWINDOW_EN_MASK               (0x00080000U)
#define CSL_DSS_DISPC_IRQEN_VID3ENDWINDOW_EN_SHIFT              (19U)
#define CSL_DSS_DISPC_IRQEN_VID3ENDWINDOW_EN_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID3ENDWINDOW_EN_MASKED             (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID3ENDWINDOW_EN_GENINT             (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VID3BUFFERUNDERFLOW_EN_MASK         (0x00100000U)
#define CSL_DSS_DISPC_IRQEN_VID3BUFFERUNDERFLOW_EN_SHIFT        (20U)
#define CSL_DSS_DISPC_IRQEN_VID3BUFFERUNDERFLOW_EN_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID3BUFFERUNDERFLOW_EN_MASKED       (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VID3BUFFERUNDERFLOW_EN_GENINT       (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_FRMDONEWB_EN_MASK                   (0x00800000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONEWB_EN_SHIFT                  (23U)
#define CSL_DSS_DISPC_IRQEN_FRMDONEWB_EN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONEWB_EN_MASKED                 (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONEWB_EN_GENINT                 (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_FRMDONETV_EN_MASK                   (0x01000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONETV_EN_SHIFT                  (24U)
#define CSL_DSS_DISPC_IRQEN_FRMDONETV_EN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONETV_EN_MASKED                 (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONETV_EN_GENINT                 (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_WBBUFFEROVERFLOW_EN_MASK            (0x02000000U)
#define CSL_DSS_DISPC_IRQEN_WBBUFFEROVERFLOW_EN_SHIFT           (25U)
#define CSL_DSS_DISPC_IRQEN_WBBUFFEROVERFLOW_EN_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_WBBUFFEROVERFLOW_EN_MASKED          (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_WBBUFFEROVERFLOW_EN_GENINT          (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_WBUNCOMPLETEERROR_EN_MASK           (0x04000000U)
#define CSL_DSS_DISPC_IRQEN_WBUNCOMPLETEERROR_EN_SHIFT          (26U)
#define CSL_DSS_DISPC_IRQEN_WBUNCOMPLETEERROR_EN_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_WBUNCOMPLETEERROR_EN_MASKED         (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_WBUNCOMPLETEERROR_EN_GENINT         (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_SYNCLOST3_EN_MASK                   (0x08000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST3_EN_SHIFT                  (27U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST3_EN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST3_EN_MASKED                 (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_SYNCLOST3_EN_GENINT                 (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_VSYNC3_EN_MASK                      (0x10000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC3_EN_SHIFT                     (28U)
#define CSL_DSS_DISPC_IRQEN_VSYNC3_EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC3_EN_MASKED                    (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_VSYNC3_EN_GENINT                    (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_FRMDONE3_EN_MASK                    (0x40000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE3_EN_SHIFT                   (30U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE3_EN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE3_EN_MASKED                  (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FRMDONE3_EN_GENINT                  (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS3_EN_MASK             (0x20000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS3_EN_SHIFT            (29U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS3_EN_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS3_EN_MASKED           (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_ACBIASCOUNTSTS3_EN_GENINT           (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_FLIPIMMEDIATEDONE_EN_MASK           (0x80000000U)
#define CSL_DSS_DISPC_IRQEN_FLIPIMMEDIATEDONE_EN_SHIFT          (31U)
#define CSL_DSS_DISPC_IRQEN_FLIPIMMEDIATEDONE_EN_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FLIPIMMEDIATEDONE_EN_MASKED         (0x00000000U)
#define CSL_DSS_DISPC_IRQEN_FLIPIMMEDIATEDONE_EN_GENINT         (0x00000001U)

#define CSL_DSS_DISPC_IRQEN_RESETVAL                            (0x00000000U)

/* CTRL1 */

#define CSL_DSS_DISPC_CTRL1_STDITHEREN_MASK                     (0x00000080U)
#define CSL_DSS_DISPC_CTRL1_STDITHEREN_SHIFT                    (7U)
#define CSL_DSS_DISPC_CTRL1_STDITHEREN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_STDITHEREN_STDITHDIS                (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_STDITHEREN_STDITHENB                (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_MASK                   (0x00000300U)
#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_SHIFT                  (8U)
#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_OALSB12B               (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_OALSB16B               (0x00000001U)
#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_OALSB18B               (0x00000002U)
#define CSL_DSS_DISPC_CTRL1_TFTDATALINES_OALSB24B               (0x00000003U)

#define CSL_DSS_DISPC_CTRL1_STALLMODE_MASK                      (0x00000800U)
#define CSL_DSS_DISPC_CTRL1_STALLMODE_SHIFT                     (11U)
#define CSL_DSS_DISPC_CTRL1_STALLMODE_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_STALLMODE_NMODE                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_STALLMODE_RFBIMODE                  (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_GPIN0_MASK                          (0x00002000U)
#define CSL_DSS_DISPC_CTRL1_GPIN0_SHIFT                         (13U)
#define CSL_DSS_DISPC_CTRL1_GPIN0_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPIN0_GPIN0RST                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPIN0_GPIN0SET                      (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_MONOCOLOR_MASK                      (0x00000004U)
#define CSL_DSS_DISPC_CTRL1_MONOCOLOR_SHIFT                     (2U)
#define CSL_DSS_DISPC_CTRL1_MONOCOLOR_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_MONOCOLOR_COLOPENB                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_MONOCOLOR_MONOPENB                  (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_M8B_MASK                            (0x00000010U)
#define CSL_DSS_DISPC_CTRL1_M8B_SHIFT                           (4U)
#define CSL_DSS_DISPC_CTRL1_M8B_RESETVAL                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_M8B__4PIXTOPANEL                    (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_M8B__8PIXTOPANEL                    (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_GOTV_MASK                           (0x00000040U)
#define CSL_DSS_DISPC_CTRL1_GOTV_SHIFT                          (6U)
#define CSL_DSS_DISPC_CTRL1_GOTV_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GOTV_HFUISR                         (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GOTV_UFPSR                          (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_TVEN_MASK                           (0x00000002U)
#define CSL_DSS_DISPC_CTRL1_TVEN_SHIFT                          (1U)
#define CSL_DSS_DISPC_CTRL1_TVEN_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TVEN_DIGOPDIS                       (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TVEN_DIGOPENB                       (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_STNTFT_MASK                         (0x00000008U)
#define CSL_DSS_DISPC_CTRL1_STNTFT_SHIFT                        (3U)
#define CSL_DSS_DISPC_CTRL1_STNTFT_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_STNTFT_STNDISPENB                   (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_STNTFT_ATFTDISENB                   (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_GOLCD_MASK                          (0x00000020U)
#define CSL_DSS_DISPC_CTRL1_GOLCD_SHIFT                         (5U)
#define CSL_DSS_DISPC_CTRL1_GOLCD_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GOLCD_HFUISR                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GOLCD_UFPSR                         (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_LCDEN_MASK                          (0x00000001U)
#define CSL_DSS_DISPC_CTRL1_LCDEN_SHIFT                         (0U)
#define CSL_DSS_DISPC_CTRL1_LCDEN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_LCDEN_LCDOPDIS                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_LCDEN_LCDOPENB                      (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_MASK   (0xC0000000U)
#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_SHIFT  (30U)
#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_ONEFRAME  (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_TWOFRAMES  (0x00000001U)
#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_FOURFRAMES  (0x00000002U)
#define CSL_DSS_DISPC_CTRL1_SPATIALTEMPORALDITHERINGFRMS_RESERVED  (0x00000003U)

#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_MASK                  (0x06000000U)
#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_SHIFT                 (25U)
#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_LOWLEVEL              (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_HIGHLEVEL             (0x00000001U)
#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_UNCHANGED             (0x00000002U)
#define CSL_DSS_DISPC_CTRL1_TDMUNUSEDBITS_RES                   (0x00000003U)

#define CSL_DSS_DISPC_CTRL1_TDMEN_MASK                          (0x00100000U)
#define CSL_DSS_DISPC_CTRL1_TDMEN_SHIFT                         (20U)
#define CSL_DSS_DISPC_CTRL1_TDMEN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMEN_TDMDIS                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMEN_TDMENB                        (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_GPOUT0_MASK                         (0x00008000U)
#define CSL_DSS_DISPC_CTRL1_GPOUT0_SHIFT                        (15U)
#define CSL_DSS_DISPC_CTRL1_GPOUT0_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPOUT0_RESET                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPOUT0_SET                          (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE_MASK                (0x00600000U)
#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE_SHIFT               (21U)
#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE__8BPARAINT          (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE__9BPARAINT          (0x00000001U)
#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE__12BPARAINT         (0x00000002U)
#define CSL_DSS_DISPC_CTRL1_TDMPARALLELMODE__16BPARAINT         (0x00000003U)

#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT_MASK                    (0x01800000U)
#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT_SHIFT                   (23U)
#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT__1CYCPERPIX             (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT__2CYCPERPIX             (0x00000001U)
#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT__3CYCPERPIX             (0x00000002U)
#define CSL_DSS_DISPC_CTRL1_TDMCYCLEFMT__3CYCPER2PIX            (0x00000003U)

#define CSL_DSS_DISPC_CTRL1_HT_MASK                             (0x000E0000U)
#define CSL_DSS_DISPC_CTRL1_HT_SHIFT                            (17U)
#define CSL_DSS_DISPC_CTRL1_HT_RESETVAL                         (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_HT_MAX                              (0x00000007U)

#define CSL_DSS_DISPC_CTRL1_GPOUT1_MASK                         (0x00010000U)
#define CSL_DSS_DISPC_CTRL1_GPOUT1_SHIFT                        (16U)
#define CSL_DSS_DISPC_CTRL1_GPOUT1_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPOUT1_RESET                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPOUT1_SET                          (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_GPIN1_MASK                          (0x00004000U)
#define CSL_DSS_DISPC_CTRL1_GPIN1_SHIFT                         (14U)
#define CSL_DSS_DISPC_CTRL1_GPIN1_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPIN1_RESET                         (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_GPIN1_SET                           (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_OVLYOPTIMIZATION_MASK               (0x00001000U)
#define CSL_DSS_DISPC_CTRL1_OVLYOPTIMIZATION_SHIFT              (12U)
#define CSL_DSS_DISPC_CTRL1_OVLYOPTIMIZATION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_OVLYOPTIMIZATION_GDBVWFM            (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_OVLYOPTIMIZATION_GDBVWNFM           (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_SECURE_MASK                         (0x00000400U)
#define CSL_DSS_DISPC_CTRL1_SECURE_SHIFT                        (10U)
#define CSL_DSS_DISPC_CTRL1_SECURE_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_SECURE_NSECMODE                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_SECURE_SECMODE                      (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_PCKFREEEN_MASK                      (0x08000000U)
#define CSL_DSS_DISPC_CTRL1_PCKFREEEN_SHIFT                     (27U)
#define CSL_DSS_DISPC_CTRL1_PCKFREEEN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_PCKFREEEN_MAX                       (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_LCDENSIGNAL_MASK                    (0x10000000U)
#define CSL_DSS_DISPC_CTRL1_LCDENSIGNAL_SHIFT                   (28U)
#define CSL_DSS_DISPC_CTRL1_LCDENSIGNAL_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_LCDENSIGNAL_MAX                     (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_LCDENPOL_MASK                       (0x20000000U)
#define CSL_DSS_DISPC_CTRL1_LCDENPOL_SHIFT                      (29U)
#define CSL_DSS_DISPC_CTRL1_LCDENPOL_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CTRL1_LCDENPOL_MAX                        (0x00000001U)

#define CSL_DSS_DISPC_CTRL1_RESETVAL                            (0x00000000U)

/* CONFIG1 */

#define CSL_DSS_DISPC_CONFIG1_PIXELDATAGATED_MASK               (0x00000010U)
#define CSL_DSS_DISPC_CONFIG1_PIXELDATAGATED_SHIFT              (4U)
#define CSL_DSS_DISPC_CONFIG1_PIXELDATAGATED_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PIXELDATAGATED_PDGDIS             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PIXELDATAGATED_PDGENB             (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_HSYNCGATED_MASK                   (0x00000040U)
#define CSL_DSS_DISPC_CONFIG1_HSYNCGATED_SHIFT                  (6U)
#define CSL_DSS_DISPC_CONFIG1_HSYNCGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_HSYNCGATED_HGDIS                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_HSYNCGATED_HGENB                  (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_ACBIASGATED_MASK                  (0x00000100U)
#define CSL_DSS_DISPC_CONFIG1_ACBIASGATED_SHIFT                 (8U)
#define CSL_DSS_DISPC_CONFIG1_ACBIASGATED_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_ACBIASGATED_ACBGDIS               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_ACBIASGATED_ACBGENB               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_TCKLCDEN_MASK                     (0x00000400U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDEN_SHIFT                    (10U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDEN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDEN_DISTCK                   (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDEN_ENBTCK                   (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_TCKTVEN_MASK                      (0x00001000U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVEN_SHIFT                     (12U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVEN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVEN_DISTCK                    (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVEN_ENBTCK                    (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_PALETTEGAMMATBL_MASK              (0x00000008U)
#define CSL_DSS_DISPC_CONFIG1_PALETTEGAMMATBL_SHIFT             (3U)
#define CSL_DSS_DISPC_CONFIG1_PALETTEGAMMATBL_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PALETTEGAMMATBL_LUTPALLETTE       (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PALETTEGAMMATBL_LUTGTABLE         (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_PIXELCLOCKGATED_MASK              (0x00000020U)
#define CSL_DSS_DISPC_CONFIG1_PIXELCLOCKGATED_SHIFT             (5U)
#define CSL_DSS_DISPC_CONFIG1_PIXELCLOCKGATED_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PIXELCLOCKGATED_PCGDIS            (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PIXELCLOCKGATED_PCGENB            (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_VSYNCGATED_MASK                   (0x00000080U)
#define CSL_DSS_DISPC_CONFIG1_VSYNCGATED_SHIFT                  (7U)
#define CSL_DSS_DISPC_CONFIG1_VSYNCGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_VSYNCGATED_VGDIS                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_VSYNCGATED_VGENB                  (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_PIXELGATED_MASK                   (0x00000001U)
#define CSL_DSS_DISPC_CONFIG1_PIXELGATED_SHIFT                  (0U)
#define CSL_DSS_DISPC_CONFIG1_PIXELGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PIXELGATED_PCLKTOGA               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PIXELGATED_PCLKTOGV               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_LOADMODE_MASK                     (0x00000006U)
#define CSL_DSS_DISPC_CONFIG1_LOADMODE_SHIFT                    (1U)
#define CSL_DSS_DISPC_CONFIG1_LOADMODE_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_LOADMODE_PGTABLEFR                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_LOADMODE_PGTABUSETB               (0x00000001U)
#define CSL_DSS_DISPC_CONFIG1_LOADMODE_FRDATLEFR                (0x00000002U)
#define CSL_DSS_DISPC_CONFIG1_LOADMODE_DLOFRSW                  (0x00000003U)

#define CSL_DSS_DISPC_CONFIG1_GAMATBLEN_MASK                    (0x00000200U)
#define CSL_DSS_DISPC_CONFIG1_GAMATBLEN_SHIFT                   (9U)
#define CSL_DSS_DISPC_CONFIG1_GAMATBLEN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_GAMATBLEN_GAMMATABLEEN            (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_GAMATBLEN_GAMMATABLEDIS           (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_TCKLCDSELECTION_MASK              (0x00000800U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDSELECTION_SHIFT             (11U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDSELECTION_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDSELECTION_GDTK              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKLCDSELECTION_VSTK              (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_TCKTVSELECTION_MASK               (0x00002000U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVSELECTION_SHIFT              (13U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVSELECTION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVSELECTION_GDTCK              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TCKTVSELECTION_VSTCK              (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_BUFFERMERGE_MASK                  (0x00004000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERMERGE_SHIFT                 (14U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERMERGE_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERMERGE_MERGEDIS              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERMERGE_MERGEENB              (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_CPR_MASK                          (0x00008000U)
#define CSL_DSS_DISPC_CONFIG1_CPR_SHIFT                         (15U)
#define CSL_DSS_DISPC_CONFIG1_CPR_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_CPR_CPRDIS                        (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_CPR_CPRENB                        (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_BUFFERHANDCHECK_MASK              (0x00010000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERHANDCHECK_SHIFT             (16U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERHANDCHECK_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERHANDCHECK_HANDCHECKDIS      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERHANDCHECK_HANDCHECKENB      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_BUFFERFILLING_MASK                (0x00020000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERFILLING_SHIFT               (17U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERFILLING_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERFILLING_FIFOFILLINGDIS      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BUFFERFILLING_FIFOFILLINGENB      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_LCDALPHABLENDEREN_MASK            (0x00040000U)
#define CSL_DSS_DISPC_CONFIG1_LCDALPHABLENDEREN_SHIFT           (18U)
#define CSL_DSS_DISPC_CONFIG1_LCDALPHABLENDEREN_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_LCDALPHABLENDEREN_DISABLE         (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_LCDALPHABLENDEREN_ENABLE          (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_TVALPHABLENDEREN_MASK             (0x00080000U)
#define CSL_DSS_DISPC_CONFIG1_TVALPHABLENDEREN_SHIFT            (19U)
#define CSL_DSS_DISPC_CONFIG1_TVALPHABLENDEREN_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TVALPHABLENDEREN_DISABLE          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TVALPHABLENDEREN_ENABLE           (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_BT656EN_MASK                      (0x00100000U)
#define CSL_DSS_DISPC_CONFIG1_BT656EN_SHIFT                     (20U)
#define CSL_DSS_DISPC_CONFIG1_BT656EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BT656EN_DISABLE                   (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BT656EN_ENABLE                    (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_BT1120EN_MASK                     (0x00200000U)
#define CSL_DSS_DISPC_CONFIG1_BT1120EN_SHIFT                    (21U)
#define CSL_DSS_DISPC_CONFIG1_BT1120EN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BT1120EN_DISABLE                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_BT1120EN_ENABLE                   (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_OUTPUTMODEEN_MASK                 (0x00400000U)
#define CSL_DSS_DISPC_CONFIG1_OUTPUTMODEEN_SHIFT                (22U)
#define CSL_DSS_DISPC_CONFIG1_OUTPUTMODEEN_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_OUTPUTMODEEN_DISABLE              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_OUTPUTMODEEN_ENABLE               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_COLORCONVEN_MASK                  (0x01000000U)
#define CSL_DSS_DISPC_CONFIG1_COLORCONVEN_SHIFT                 (24U)
#define CSL_DSS_DISPC_CONFIG1_COLORCONVEN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_COLORCONVEN_COLSPCDIS             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_COLORCONVEN_COLSPCENB             (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_FULLRANGE_MASK                    (0x02000000U)
#define CSL_DSS_DISPC_CONFIG1_FULLRANGE_SHIFT                   (25U)
#define CSL_DSS_DISPC_CONFIG1_FULLRANGE_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_FULLRANGE_LIMRANGE                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_FULLRANGE_FULLRANGE               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_FIDFIRST_MASK                     (0x00800000U)
#define CSL_DSS_DISPC_CONFIG1_FIDFIRST_SHIFT                    (23U)
#define CSL_DSS_DISPC_CONFIG1_FIDFIRST_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_FIDFIRST_EVEN                     (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_FIDFIRST_ODD                      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG1_TVINTERLEAVE_MASK                 (0x30000000U)
#define CSL_DSS_DISPC_CONFIG1_TVINTERLEAVE_SHIFT                (28U)
#define CSL_DSS_DISPC_CONFIG1_TVINTERLEAVE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_TVINTERLEAVE_MAX                  (0x00000003U)

#define CSL_DSS_DISPC_CONFIG1_PLCDINTERLEAVE_MASK               (0x0C000000U)
#define CSL_DSS_DISPC_CONFIG1_PLCDINTERLEAVE_SHIFT              (26U)
#define CSL_DSS_DISPC_CONFIG1_PLCDINTERLEAVE_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG1_PLCDINTERLEAVE_MAX                (0x00000003U)

#define CSL_DSS_DISPC_CONFIG1_RESETVAL                          (0x00000000U)

/* CAPABLE */

#define CSL_DSS_DISPC_CAPABLE_TFTDITHERINGCAPABLE_MASK          (0x00000020U)
#define CSL_DSS_DISPC_CAPABLE_TFTDITHERINGCAPABLE_SHIFT         (5U)
#define CSL_DSS_DISPC_CAPABLE_TFTDITHERINGCAPABLE_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_TFTDITHERINGCAPABLE_MAX           (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_GFXTRANSDSTCAPABLE_MASK           (0x00000080U)
#define CSL_DSS_DISPC_CAPABLE_GFXTRANSDSTCAPABLE_SHIFT          (7U)
#define CSL_DSS_DISPC_CAPABLE_GFXTRANSDSTCAPABLE_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_GFXTRANSDSTCAPABLE_MAX            (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_VIDCAPABLE_MASK                   (0x00000001U)
#define CSL_DSS_DISPC_CAPABLE_VIDCAPABLE_SHIFT                  (0U)
#define CSL_DSS_DISPC_CAPABLE_VIDCAPABLE_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_VIDCAPABLE_MAX                    (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_VIDVERTFIRCAPABLE_MASK            (0x00000004U)
#define CSL_DSS_DISPC_CAPABLE_VIDVERTFIRCAPABLE_SHIFT           (2U)
#define CSL_DSS_DISPC_CAPABLE_VIDVERTFIRCAPABLE_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_VIDVERTFIRCAPABLE_MAX             (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_GFXGAMMATBLCAPABLE_MASK           (0x00000200U)
#define CSL_DSS_DISPC_CAPABLE_GFXGAMMATBLCAPABLE_SHIFT          (9U)
#define CSL_DSS_DISPC_CAPABLE_GFXGAMMATBLCAPABLE_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_GFXGAMMATBLCAPABLE_MAX            (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_VIDTRANSSRCCAPABLE_MASK           (0x00000010U)
#define CSL_DSS_DISPC_CAPABLE_VIDTRANSSRCCAPABLE_SHIFT          (4U)
#define CSL_DSS_DISPC_CAPABLE_VIDTRANSSRCCAPABLE_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_VIDTRANSSRCCAPABLE_MAX            (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_GFXLAYERCAPABLE_MASK              (0x00000100U)
#define CSL_DSS_DISPC_CAPABLE_GFXLAYERCAPABLE_SHIFT             (8U)
#define CSL_DSS_DISPC_CAPABLE_GFXLAYERCAPABLE_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_GFXLAYERCAPABLE_MAX               (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_STNDITHERINGCAPABLE_MASK          (0x00000040U)
#define CSL_DSS_DISPC_CAPABLE_STNDITHERINGCAPABLE_SHIFT         (6U)
#define CSL_DSS_DISPC_CAPABLE_STNDITHERINGCAPABLE_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_STNDITHERINGCAPABLE_MAX           (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_VIDHORFIRCAPABLE_MASK             (0x00000002U)
#define CSL_DSS_DISPC_CAPABLE_VIDHORFIRCAPABLE_SHIFT            (1U)
#define CSL_DSS_DISPC_CAPABLE_VIDHORFIRCAPABLE_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_VIDHORFIRCAPABLE_MAX              (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_VIDLAYERCAPABLE_MASK              (0x00000008U)
#define CSL_DSS_DISPC_CAPABLE_VIDLAYERCAPABLE_SHIFT             (3U)
#define CSL_DSS_DISPC_CAPABLE_VIDLAYERCAPABLE_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CAPABLE_VIDLAYERCAPABLE_MAX               (0x00000001U)

#define CSL_DSS_DISPC_CAPABLE_RESETVAL                          (0x00000000U)

/* DEFAULT_COLOR0 */

#define CSL_DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR_MASK          (0x00FFFFFFU)
#define CSL_DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR_SHIFT         (0U)
#define CSL_DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_DEFAULT_COLOR0_DEFAULTCOLOR_MAX           (0x00ffffffU)

#define CSL_DSS_DISPC_DEFAULT_COLOR0_RESETVAL                   (0x00000000U)

/* DEFAULT_COLOR1 */

#define CSL_DSS_DISPC_DEFAULT_COLOR1_DEFAULTCOLOR_MASK          (0x00FFFFFFU)
#define CSL_DSS_DISPC_DEFAULT_COLOR1_DEFAULTCOLOR_SHIFT         (0U)
#define CSL_DSS_DISPC_DEFAULT_COLOR1_DEFAULTCOLOR_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_DEFAULT_COLOR1_DEFAULTCOLOR_MAX           (0x00ffffffU)

#define CSL_DSS_DISPC_DEFAULT_COLOR1_RESETVAL                   (0x00000000U)

/* TRANS_COLOR0 */

#define CSL_DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY_MASK           (0x00FFFFFFU)
#define CSL_DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY_SHIFT          (0U)
#define CSL_DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_TRANS_COLOR0_TRANSCOLORKEY_MAX            (0x00ffffffU)

#define CSL_DSS_DISPC_TRANS_COLOR0_RESETVAL                     (0x00000000U)

/* TRANS_COLOR1 */

#define CSL_DSS_DISPC_TRANS_COLOR1_TRANSCOLORKEY_MASK           (0x00FFFFFFU)
#define CSL_DSS_DISPC_TRANS_COLOR1_TRANSCOLORKEY_SHIFT          (0U)
#define CSL_DSS_DISPC_TRANS_COLOR1_TRANSCOLORKEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_TRANS_COLOR1_TRANSCOLORKEY_MAX            (0x00ffffffU)

#define CSL_DSS_DISPC_TRANS_COLOR1_RESETVAL                     (0x00000000U)

/* LINE_STS */

#define CSL_DSS_DISPC_LINE_STS_LINENUMBER_MASK                  (0x00000FFFU)
#define CSL_DSS_DISPC_LINE_STS_LINENUMBER_SHIFT                 (0U)
#define CSL_DSS_DISPC_LINE_STS_LINENUMBER_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_LINE_STS_LINENUMBER_MAX                   (0x00000fffU)

#define CSL_DSS_DISPC_LINE_STS_RESETVAL                         (0x00000000U)

/* LINE_NUMBER */

#define CSL_DSS_DISPC_LINE_NUMBER_LINENUMBER_MASK               (0x00000FFFU)
#define CSL_DSS_DISPC_LINE_NUMBER_LINENUMBER_SHIFT              (0U)
#define CSL_DSS_DISPC_LINE_NUMBER_LINENUMBER_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_LINE_NUMBER_LINENUMBER_MAX                (0x00000fffU)

#define CSL_DSS_DISPC_LINE_NUMBER_RESETVAL                      (0x00000000U)

/* TIMING_H1 */

#define CSL_DSS_DISPC_TIMING_H1_HBP_MASK                        (0xFFF00000U)
#define CSL_DSS_DISPC_TIMING_H1_HBP_SHIFT                       (20U)
#define CSL_DSS_DISPC_TIMING_H1_HBP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H1_HBP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_H1_HFP_MASK                        (0x000FFF00U)
#define CSL_DSS_DISPC_TIMING_H1_HFP_SHIFT                       (8U)
#define CSL_DSS_DISPC_TIMING_H1_HFP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H1_HFP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_H1_HSW_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_TIMING_H1_HSW_SHIFT                       (0U)
#define CSL_DSS_DISPC_TIMING_H1_HSW_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H1_HSW_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_TIMING_H1_RESETVAL                        (0x00000000U)

/* TIMING_V1 */

#define CSL_DSS_DISPC_TIMING_V1_VBP_MASK                        (0xFFF00000U)
#define CSL_DSS_DISPC_TIMING_V1_VBP_SHIFT                       (20U)
#define CSL_DSS_DISPC_TIMING_V1_VBP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V1_VBP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_V1_VFP_MASK                        (0x000FFF00U)
#define CSL_DSS_DISPC_TIMING_V1_VFP_SHIFT                       (8U)
#define CSL_DSS_DISPC_TIMING_V1_VFP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V1_VFP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_V1_VSW_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_TIMING_V1_VSW_SHIFT                       (0U)
#define CSL_DSS_DISPC_TIMING_V1_VSW_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V1_VSW_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_TIMING_V1_RESETVAL                        (0x00000000U)

/* POL_FREQ1 */

#define CSL_DSS_DISPC_POL_FREQ1_ACBI_MASK                       (0x00000F00U)
#define CSL_DSS_DISPC_POL_FREQ1_ACBI_SHIFT                      (8U)
#define CSL_DSS_DISPC_POL_FREQ1_ACBI_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_ACBI_MAX                        (0x0000000fU)

#define CSL_DSS_DISPC_POL_FREQ1_IHS_MASK                        (0x00002000U)
#define CSL_DSS_DISPC_POL_FREQ1_IHS_SHIFT                       (13U)
#define CSL_DSS_DISPC_POL_FREQ1_IHS_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IHS_LCKPINAH                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IHS_LCKPINAL                    (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_IEO_MASK                        (0x00008000U)
#define CSL_DSS_DISPC_POL_FREQ1_IEO_SHIFT                       (15U)
#define CSL_DSS_DISPC_POL_FREQ1_IEO_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IEO_ACBAHIGH                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IEO_ACBALOW                     (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_ONOFF_MASK                      (0x00020000U)
#define CSL_DSS_DISPC_POL_FREQ1_ONOFF_SHIFT                     (17U)
#define CSL_DSS_DISPC_POL_FREQ1_ONOFF_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_ONOFF_DOPEDPCK                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_ONOFF_DBIT16                    (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_ACB_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_POL_FREQ1_ACB_SHIFT                       (0U)
#define CSL_DSS_DISPC_POL_FREQ1_ACB_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_ACB_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_POL_FREQ1_IVS_MASK                        (0x00001000U)
#define CSL_DSS_DISPC_POL_FREQ1_IVS_SHIFT                       (12U)
#define CSL_DSS_DISPC_POL_FREQ1_IVS_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IVS_FCKPINAH                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IVS_FCKPINAL                    (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_IPC_MASK                        (0x00004000U)
#define CSL_DSS_DISPC_POL_FREQ1_IPC_SHIFT                       (14U)
#define CSL_DSS_DISPC_POL_FREQ1_IPC_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IPC_DRPCK                       (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_IPC_DFPCK                       (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_RF_MASK                         (0x00010000U)
#define CSL_DSS_DISPC_POL_FREQ1_RF_SHIFT                        (16U)
#define CSL_DSS_DISPC_POL_FREQ1_RF_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_RF_DFEDPCK                      (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_RF_DRIEDPCK                     (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_ALIGN_MASK                      (0x00040000U)
#define CSL_DSS_DISPC_POL_FREQ1_ALIGN_SHIFT                     (18U)
#define CSL_DSS_DISPC_POL_FREQ1_ALIGN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_ALIGN_NOTALIGNED                (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ1_ALIGN_ALIGNED                   (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ1_RESETVAL                        (0x00000000U)

/* DIVISOR1 */

#define CSL_DSS_DISPC_DIVISOR1_PCD_MASK                         (0x000000FFU)
#define CSL_DSS_DISPC_DIVISOR1_PCD_SHIFT                        (0U)
#define CSL_DSS_DISPC_DIVISOR1_PCD_RESETVAL                     (0x00000001U)
#define CSL_DSS_DISPC_DIVISOR1_PCD_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR1_LCD_MASK                         (0x00FF0000U)
#define CSL_DSS_DISPC_DIVISOR1_LCD_SHIFT                        (16U)
#define CSL_DSS_DISPC_DIVISOR1_LCD_RESETVAL                     (0x00000004U)
#define CSL_DSS_DISPC_DIVISOR1_LCD_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR1_RESETVAL                         (0x00040001U)

/* GLOBAL_ALPHA */

#define CSL_DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA_MASK          (0x000000FFU)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA_SHIFT         (0U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA_RESETVAL      (0x000000ffU)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_GFXGLOBALALPHA_MAX           (0x000000ffU)

#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA_MASK         (0x00FF0000U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA_SHIFT        (16U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA_RESETVAL     (0x000000ffU)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID2GLOBALALPHA_MAX          (0x000000ffU)

#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA_MASK         (0xFF000000U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA_SHIFT        (24U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA_RESETVAL     (0x000000ffU)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID3GLOBALALPHA_MAX          (0x000000ffU)

#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA_MASK         (0x0000FF00U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA_SHIFT        (8U)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA_RESETVAL     (0x000000ffU)
#define CSL_DSS_DISPC_GLOBAL_ALPHA_VID1GLOBALALPHA_MAX          (0x000000ffU)

#define CSL_DSS_DISPC_GLOBAL_ALPHA_RESETVAL                     (0xffffffffU)

/* SIZE_TV */

#define CSL_DSS_DISPC_SIZE_TV_LPP_MASK                          (0x0FFF0000U)
#define CSL_DSS_DISPC_SIZE_TV_LPP_SHIFT                         (16U)
#define CSL_DSS_DISPC_SIZE_TV_LPP_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_SIZE_TV_LPP_MAX                           (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_TV_PPL_MASK                          (0x00000FFFU)
#define CSL_DSS_DISPC_SIZE_TV_PPL_SHIFT                         (0U)
#define CSL_DSS_DISPC_SIZE_TV_PPL_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_SIZE_TV_PPL_MAX                           (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_TV_DELTA_LPP_MASK                    (0x0000C000U)
#define CSL_DSS_DISPC_SIZE_TV_DELTA_LPP_SHIFT                   (14U)
#define CSL_DSS_DISPC_SIZE_TV_DELTA_LPP_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_SIZE_TV_DELTA_LPP_SAME                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_TV_DELTA_LPP_PLUSONE                 (0x00000001U)
#define CSL_DSS_DISPC_SIZE_TV_DELTA_LPP_MINUSONE                (0x00000002U)

#define CSL_DSS_DISPC_SIZE_TV_RESETVAL                          (0x00000000U)

/* SIZE_LCD1 */

#define CSL_DSS_DISPC_SIZE_LCD1_LPP_MASK                        (0x0FFF0000U)
#define CSL_DSS_DISPC_SIZE_LCD1_LPP_SHIFT                       (16U)
#define CSL_DSS_DISPC_SIZE_LCD1_LPP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD1_LPP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_LCD1_PPL_MASK                        (0x00000FFFU)
#define CSL_DSS_DISPC_SIZE_LCD1_PPL_SHIFT                       (0U)
#define CSL_DSS_DISPC_SIZE_LCD1_PPL_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD1_PPL_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_LCD1_DELTA_LPP_MASK                  (0x0000C000U)
#define CSL_DSS_DISPC_SIZE_LCD1_DELTA_LPP_SHIFT                 (14U)
#define CSL_DSS_DISPC_SIZE_LCD1_DELTA_LPP_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD1_DELTA_LPP_SAME                  (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD1_DELTA_LPP_PLUSONE               (0x00000001U)
#define CSL_DSS_DISPC_SIZE_LCD1_DELTA_LPP_MINUSONE              (0x00000002U)

#define CSL_DSS_DISPC_SIZE_LCD1_RESETVAL                        (0x00000000U)

/* GFX_BA */

#define CSL_DSS_DISPC_GFX_BA_BA_MASK                            (0xFFFFFFFFU)
#define CSL_DSS_DISPC_GFX_BA_BA_SHIFT                           (0U)
#define CSL_DSS_DISPC_GFX_BA_BA_RESETVAL                        (0x00000000U)
#define CSL_DSS_DISPC_GFX_BA_BA_MAX                             (0xffffffffU)

#define CSL_DSS_DISPC_GFX_BA_RESETVAL                           (0x00000000U)

/* GFX_POSITION */

#define CSL_DSS_DISPC_GFX_POSITION_POSX_MASK                    (0x000007FFU)
#define CSL_DSS_DISPC_GFX_POSITION_POSX_SHIFT                   (0U)
#define CSL_DSS_DISPC_GFX_POSITION_POSX_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_GFX_POSITION_POSX_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_GFX_POSITION_POSY_MASK                    (0x07FF0000U)
#define CSL_DSS_DISPC_GFX_POSITION_POSY_SHIFT                   (16U)
#define CSL_DSS_DISPC_GFX_POSITION_POSY_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_GFX_POSITION_POSY_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_GFX_POSITION_RESETVAL                     (0x00000000U)

/* GFX_SIZE */

#define CSL_DSS_DISPC_GFX_SIZE_SIZEY_MASK                       (0x0FFF0000U)
#define CSL_DSS_DISPC_GFX_SIZE_SIZEY_SHIFT                      (16U)
#define CSL_DSS_DISPC_GFX_SIZE_SIZEY_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_GFX_SIZE_SIZEY_MAX                        (0x00000fffU)

#define CSL_DSS_DISPC_GFX_SIZE_SIZEX_MASK                       (0x000007FFU)
#define CSL_DSS_DISPC_GFX_SIZE_SIZEX_SHIFT                      (0U)
#define CSL_DSS_DISPC_GFX_SIZE_SIZEX_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_GFX_SIZE_SIZEX_MAX                        (0x000007ffU)

#define CSL_DSS_DISPC_GFX_SIZE_RESETVAL                         (0x00000000U)

/* GFX_ATTRS */

#define CSL_DSS_DISPC_GFX_ATTRS_NIBBLEMODE_MASK                 (0x00000200U)
#define CSL_DSS_DISPC_GFX_ATTRS_NIBBLEMODE_SHIFT                (9U)
#define CSL_DSS_DISPC_GFX_ATTRS_NIBBLEMODE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_NIBBLEMODE_NIBMDIS              (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_NIBBLEMODE_NIBMENB              (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT_MASK                 (0x00000100U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT_SHIFT                (8U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT_LCDOPSEL             (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT_TVOPSEL              (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_REPLICATIONEN_MASK              (0x00000020U)
#define CSL_DSS_DISPC_GFX_ATTRS_REPLICATIONEN_SHIFT             (5U)
#define CSL_DSS_DISPC_GFX_ATTRS_REPLICATIONEN_RESETVAL          (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_REPLICATIONEN_GRLOGENB          (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_REPLICATIONEN_GRLOGDIS          (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_EN_MASK                         (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_EN_SHIFT                        (0U)
#define CSL_DSS_DISPC_GFX_ATTRS_EN_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_EN_GRAPHICSDIS                  (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_EN_GRAPHICSENB                  (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_MASK                  (0x000000C0U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_SHIFT                 (6U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_RESETVAL              (0x00000002U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_BURST2X128            (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_BURST4X128            (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_BURST8X128            (0x00000002U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTSIZE_RES                   (0x00000003U)

#define CSL_DSS_DISPC_GFX_ATTRS_FMT_MASK                        (0x0000001EU)
#define CSL_DSS_DISPC_GFX_ATTRS_FMT_SHIFT                       (1U)
#define CSL_DSS_DISPC_GFX_ATTRS_FMT_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_FMT_MAX                         (0x0000000fU)

#define CSL_DSS_DISPC_GFX_ATTRS_BUFPRELOAD_MASK                 (0x00000800U)
#define CSL_DSS_DISPC_GFX_ATTRS_BUFPRELOAD_SHIFT                (11U)
#define CSL_DSS_DISPC_GFX_ATTRS_BUFPRELOAD_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_BUFPRELOAD_HIGHTHRES            (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_BUFPRELOAD_DEFVAL               (0x00000000U)

#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_MASK                   (0x00003000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_SHIFT                  (12U)
#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_NOROT                  (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_ROT90                  (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_ROT180                 (0x00000002U)
#define CSL_DSS_DISPC_GFX_ATTRS_ROTATION_ROT270                 (0x00000003U)

#define CSL_DSS_DISPC_GFX_ATTRS_ARBITRATION_MASK                (0x00004000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ARBITRATION_SHIFT               (14U)
#define CSL_DSS_DISPC_GFX_ATTRS_ARBITRATION_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ARBITRATION_NORMALPRIO          (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ARBITRATION_HIGHPRIO            (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESH_MASK                (0x00008000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESH_SHIFT               (15U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESH_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESH_SELFREFRESHDIS      (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESH_SELFREFRESHENB      (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_MASK                (0xC0000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_SHIFT               (30U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_PRIMARYLCDSEL       (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_SECONDARYLCDSEL     (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_WRITEBACKSEL        (0x00000003U)
#define CSL_DSS_DISPC_GFX_ATTRS_CHANNELOUT2_THIRDLCDSEL         (0x00000002U)

#define CSL_DSS_DISPC_GFX_ATTRS_BURSTTYPE_MASK                  (0x20000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTTYPE_SHIFT                 (29U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTTYPE_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTTYPE_INC                   (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_BURSTTYPE_BLCK                  (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_MASK                     (0x0C000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_SHIFT                    (26U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_ZORDER0                  (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_ZORDER1                  (0x00000001U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_ZORDER2                  (0x00000002U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDER_ZORDER3                  (0x00000003U)

#define CSL_DSS_DISPC_GFX_ATTRS_ZORDEREN_MASK                   (0x02000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDEREN_SHIFT                  (25U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDEREN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDEREN_ZORDERDIS              (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ZORDEREN_ZORDERENB              (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_PREMULTIPLYALPHA_MASK           (0x10000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_PREMULTIPLYALPHA_SHIFT          (28U)
#define CSL_DSS_DISPC_GFX_ATTRS_PREMULTIPLYALPHA_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA  (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA  (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_ANTIFLICKER_MASK                (0x01000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ANTIFLICKER_SHIFT               (24U)
#define CSL_DSS_DISPC_GFX_ATTRS_ANTIFLICKER_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ANTIFLICKER_AFDIS               (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_ANTIFLICKER_AFENB               (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESHAUTO_MASK            (0x00020000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESHAUTO_SHIFT           (17U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESHAUTO_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTODIS  (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTOEN  (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_FORCE1DTILEDMODE_MASK           (0x00010000U)
#define CSL_DSS_DISPC_GFX_ATTRS_FORCE1DTILEDMODE_SHIFT          (16U)
#define CSL_DSS_DISPC_GFX_ATTRS_FORCE1DTILEDMODE_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS  (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS  (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_FRMPACKINGMODE_MASK             (0x00000400U)
#define CSL_DSS_DISPC_GFX_ATTRS_FRMPACKINGMODE_SHIFT            (10U)
#define CSL_DSS_DISPC_GFX_ATTRS_FRMPACKINGMODE_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_FRMPACKINGMODE_FPMDIS           (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_FRMPACKINGMODE_FPMENB           (0x00000001U)

#define CSL_DSS_DISPC_GFX_ATTRS_SUBSAMPLINGPATTERN_MASK         (0x001C0000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SUBSAMPLINGPATTERN_SHIFT        (18U)
#define CSL_DSS_DISPC_GFX_ATTRS_SUBSAMPLINGPATTERN_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_GFX_ATTRS_SUBSAMPLINGPATTERN_MAX          (0x00000007U)

#define CSL_DSS_DISPC_GFX_ATTRS_RESETVAL                        (0x000000a0U)

/* GFX_BUF_THR */

#define CSL_DSS_DISPC_GFX_BUF_THR_BUFLOWTHR_MASK                (0x0000FFFFU)
#define CSL_DSS_DISPC_GFX_BUF_THR_BUFLOWTHR_SHIFT               (0U)
#define CSL_DSS_DISPC_GFX_BUF_THR_BUFLOWTHR_RESETVAL            (0x000004f8U)
#define CSL_DSS_DISPC_GFX_BUF_THR_BUFLOWTHR_MAX                 (0x0000ffffU)

#define CSL_DSS_DISPC_GFX_BUF_THR_BUFHIGHTHR_MASK               (0xFFFF0000U)
#define CSL_DSS_DISPC_GFX_BUF_THR_BUFHIGHTHR_SHIFT              (16U)
#define CSL_DSS_DISPC_GFX_BUF_THR_BUFHIGHTHR_RESETVAL           (0x000004ffU)
#define CSL_DSS_DISPC_GFX_BUF_THR_BUFHIGHTHR_MAX                (0x0000ffffU)

#define CSL_DSS_DISPC_GFX_BUF_THR_RESETVAL                      (0x04ff04f8U)

/* GFX_BUF_SIZE_STS */

#define CSL_DSS_DISPC_GFX_BUF_SIZE_STS_BUFSIZE_MASK             (0x0000FFFFU)
#define CSL_DSS_DISPC_GFX_BUF_SIZE_STS_BUFSIZE_SHIFT            (0U)
#define CSL_DSS_DISPC_GFX_BUF_SIZE_STS_BUFSIZE_RESETVAL         (0x00000500U)
#define CSL_DSS_DISPC_GFX_BUF_SIZE_STS_BUFSIZE_MAX              (0x0000ffffU)

#define CSL_DSS_DISPC_GFX_BUF_SIZE_STS_RESETVAL                 (0x00000500U)

/* GFX_ROW_INC */

#define CSL_DSS_DISPC_GFX_ROW_INC_ROWINC_MASK                   (0xFFFFFFFFU)
#define CSL_DSS_DISPC_GFX_ROW_INC_ROWINC_SHIFT                  (0U)
#define CSL_DSS_DISPC_GFX_ROW_INC_ROWINC_RESETVAL               (0x00000001U)
#define CSL_DSS_DISPC_GFX_ROW_INC_ROWINC_MAX                    (0xffffffffU)

#define CSL_DSS_DISPC_GFX_ROW_INC_RESETVAL                      (0x00000001U)

/* GFX_PIXEL_INC */

#define CSL_DSS_DISPC_GFX_PIXEL_INC_PIXELINC_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_GFX_PIXEL_INC_PIXELINC_SHIFT              (0U)
#define CSL_DSS_DISPC_GFX_PIXEL_INC_PIXELINC_RESETVAL           (0x00000001U)
#define CSL_DSS_DISPC_GFX_PIXEL_INC_PIXELINC_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_GFX_PIXEL_INC_RESETVAL                    (0x00000001U)

/* GFX_WINDOW_SKIP */

#define CSL_DSS_DISPC_GFX_WINDOW_SKIP_WINDOWSKIP_MASK           (0xFFFFFFFFU)
#define CSL_DSS_DISPC_GFX_WINDOW_SKIP_WINDOWSKIP_SHIFT          (0U)
#define CSL_DSS_DISPC_GFX_WINDOW_SKIP_WINDOWSKIP_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_GFX_WINDOW_SKIP_WINDOWSKIP_MAX            (0xffffffffU)

#define CSL_DSS_DISPC_GFX_WINDOW_SKIP_RESETVAL                  (0x00000000U)

/* GFX_TBL_BA */

#define CSL_DSS_DISPC_GFX_TBL_BA_TBLBA_MASK                     (0xFFFFFFFFU)
#define CSL_DSS_DISPC_GFX_TBL_BA_TBLBA_SHIFT                    (0U)
#define CSL_DSS_DISPC_GFX_TBL_BA_TBLBA_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_GFX_TBL_BA_TBLBA_MAX                      (0xffffffffU)

#define CSL_DSS_DISPC_GFX_TBL_BA_RESETVAL                       (0x00000000U)

/* VID1_BA */

#define CSL_DSS_DISPC_VID1_BA_BA_MASK                           (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID1_BA_BA_SHIFT                          (0U)
#define CSL_DSS_DISPC_VID1_BA_BA_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_VID1_BA_BA_MAX                            (0xffffffffU)

#define CSL_DSS_DISPC_VID1_BA_RESETVAL                          (0x00000000U)

/* VID1_POSITION */

#define CSL_DSS_DISPC_VID1_POSITION_POSY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_POSITION_POSY_SHIFT                  (16U)
#define CSL_DSS_DISPC_VID1_POSITION_POSY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID1_POSITION_POSY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID1_POSITION_POSX_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID1_POSITION_POSX_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID1_POSITION_POSX_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID1_POSITION_POSX_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID1_POSITION_RESETVAL                    (0x00000000U)

/* VID1_SIZE */

#define CSL_DSS_DISPC_VID1_SIZE_SIZEY_MASK                      (0x0FFF0000U)
#define CSL_DSS_DISPC_VID1_SIZE_SIZEY_SHIFT                     (16U)
#define CSL_DSS_DISPC_VID1_SIZE_SIZEY_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_VID1_SIZE_SIZEY_MAX                       (0x00000fffU)

#define CSL_DSS_DISPC_VID1_SIZE_SIZEX_MASK                      (0x00000FFFU)
#define CSL_DSS_DISPC_VID1_SIZE_SIZEX_SHIFT                     (0U)
#define CSL_DSS_DISPC_VID1_SIZE_SIZEX_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_VID1_SIZE_SIZEX_MAX                       (0x00000fffU)

#define CSL_DSS_DISPC_VID1_SIZE_RESETVAL                        (0x00000000U)

/* VID1_ATTRS */

#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESHAUTO_MASK           (0x00020000U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESHAUTO_SHIFT          (17U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESHAUTO_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTODIS  (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTOEN  (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_FULLRANGE_MASK                 (0x00000800U)
#define CSL_DSS_DISPC_VID1_ATTRS_FULLRANGE_SHIFT                (11U)
#define CSL_DSS_DISPC_VID1_ATTRS_FULLRANGE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FULLRANGE_LIMRANGE             (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FULLRANGE_FULLRANGE            (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT_MASK                (0x00010000U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT_SHIFT               (16U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT_LCDOP               (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT_TVOP                (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_MASK                  (0x00003000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_SHIFT                 (12U)
#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_NOROT                 (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_ROT90                 (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_ROT180                (0x00000002U)
#define CSL_DSS_DISPC_VID1_ATTRS_ROTATION_ROT270                (0x00000003U)

#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_MASK                  (0x00000060U)
#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_SHIFT                 (5U)
#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_RESIZEPROC            (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_HRESIZE               (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_VRESIZE               (0x00000002U)
#define CSL_DSS_DISPC_VID1_ATTRS_RESIZEEN_HVRESIZE              (0x00000003U)

#define CSL_DSS_DISPC_VID1_ATTRS_REPLICATIONEN_MASK             (0x00000400U)
#define CSL_DSS_DISPC_VID1_ATTRS_REPLICATIONEN_SHIFT            (10U)
#define CSL_DSS_DISPC_VID1_ATTRS_REPLICATIONEN_RESETVAL         (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_REPLICATIONEN_VREPLDIS         (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_REPLICATIONEN_VREPLENB         (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_MASK                 (0x0000C000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_SHIFT                (14U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_RESETVAL             (0x00000002U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_BURST2X128B          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_BURST4X128B          (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_BURST8X128B          (0x00000002U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTSIZE_RES                  (0x00000003U)

#define CSL_DSS_DISPC_VID1_ATTRS_HRESIZECONF_MASK               (0x00000080U)
#define CSL_DSS_DISPC_VID1_ATTRS_HRESIZECONF_SHIFT              (7U)
#define CSL_DSS_DISPC_VID1_ATTRS_HRESIZECONF_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_HRESIZECONF_MAX                (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_COLORCONVEN_MASK               (0x00000200U)
#define CSL_DSS_DISPC_VID1_ATTRS_COLORCONVEN_SHIFT              (9U)
#define CSL_DSS_DISPC_VID1_ATTRS_COLORCONVEN_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_COLORCONVEN_COLSPCDIS          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_COLORCONVEN_COLSPCENB          (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_EN_MASK                        (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_EN_SHIFT                       (0U)
#define CSL_DSS_DISPC_VID1_ATTRS_EN_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_EN_VIDEODIS                    (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_EN_VIDEOENB                    (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_FMT_MASK                       (0x0000001EU)
#define CSL_DSS_DISPC_VID1_ATTRS_FMT_SHIFT                      (1U)
#define CSL_DSS_DISPC_VID1_ATTRS_FMT_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FMT_MAX                        (0x0000000fU)

#define CSL_DSS_DISPC_VID1_ATTRS_BUFPRELOAD_MASK                (0x00080000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BUFPRELOAD_SHIFT               (19U)
#define CSL_DSS_DISPC_VID1_ATTRS_BUFPRELOAD_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BUFPRELOAD_DEFVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BUFPRELOAD_HIGHTHRES           (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_VERTICALTAPS_MASK              (0x00200000U)
#define CSL_DSS_DISPC_VID1_ATTRS_VERTICALTAPS_SHIFT             (21U)
#define CSL_DSS_DISPC_VID1_ATTRS_VERTICALTAPS_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_VERTICALTAPS_TAPS3             (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_VERTICALTAPS_TAPS5             (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESH_MASK               (0x01000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESH_SHIFT              (24U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESH_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESH_SELFREFRESHDIS     (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_SELFREFRESH_SELFREFRESHENB     (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_ARBITRATION_MASK               (0x00800000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ARBITRATION_SHIFT              (23U)
#define CSL_DSS_DISPC_VID1_ATTRS_ARBITRATION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ARBITRATION_NORMALPRIO         (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ARBITRATION_HIGHPRIO           (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_ZORDEREN_MASK                  (0x02000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDEREN_SHIFT                 (25U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDEREN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDEREN_ZORDERDIS             (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDEREN_ZORDERENB             (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_MASK                    (0x0C000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_SHIFT                   (26U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_ZORDER0                 (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_ZORDER1                 (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_ZORDER2                 (0x00000002U)
#define CSL_DSS_DISPC_VID1_ATTRS_ZORDER_ZORDER3                 (0x00000003U)

#define CSL_DSS_DISPC_VID1_ATTRS_PREMULTIPHYALPHA_MASK          (0x10000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_PREMULTIPHYALPHA_SHIFT         (28U)
#define CSL_DSS_DISPC_VID1_ATTRS_PREMULTIPHYALPHA_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_PREMULTIPHYALPHA_NONPREMULTIPLIEDALPHA  (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_PREMULTIPHYALPHA_PREMULTIPLIEDALPHA  (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_BURSTTYPE_MASK                 (0x20000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTTYPE_SHIFT                (29U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTTYPE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTTYPE_INC                  (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_BURSTTYPE_BLCK                 (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_MASK               (0xC0000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_SHIFT              (30U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_PRIMARYLCDSEL      (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_SECONDARYLCDSEL    (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_WRITEBACKSEL       (0x00000003U)
#define CSL_DSS_DISPC_VID1_ATTRS_CHANNELOUT2_THIRDLCDSEL        (0x00000002U)

#define CSL_DSS_DISPC_VID1_ATTRS_DOUBLESTRIDE_MASK              (0x00400000U)
#define CSL_DSS_DISPC_VID1_ATTRS_DOUBLESTRIDE_SHIFT             (22U)
#define CSL_DSS_DISPC_VID1_ATTRS_DOUBLESTRIDE_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_DOUBLESTRIDE_INITIAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_DOUBLESTRIDE_DOUBLE            (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_FORCE1DTILEDMODE_MASK          (0x00100000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FORCE1DTILEDMODE_SHIFT         (20U)
#define CSL_DSS_DISPC_VID1_ATTRS_FORCE1DTILEDMODE_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS  (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS  (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_FRMPACKINGMODE_MASK            (0x00000100U)
#define CSL_DSS_DISPC_VID1_ATTRS_FRMPACKINGMODE_SHIFT           (8U)
#define CSL_DSS_DISPC_VID1_ATTRS_FRMPACKINGMODE_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FRMPACKINGMODE_FPMDIS          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS_FRMPACKINGMODE_FPMENB          (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS_RESETVAL                       (0x00008400U)

/* VID1_BUF_THR */

#define CSL_DSS_DISPC_VID1_BUF_THR_BUFLOWTHR_MASK               (0x0000FFFFU)
#define CSL_DSS_DISPC_VID1_BUF_THR_BUFLOWTHR_SHIFT              (0U)
#define CSL_DSS_DISPC_VID1_BUF_THR_BUFLOWTHR_RESETVAL           (0x000007f8U)
#define CSL_DSS_DISPC_VID1_BUF_THR_BUFLOWTHR_MAX                (0x0000ffffU)

#define CSL_DSS_DISPC_VID1_BUF_THR_BUFHIGHTHR_MASK              (0xFFFF0000U)
#define CSL_DSS_DISPC_VID1_BUF_THR_BUFHIGHTHR_SHIFT             (16U)
#define CSL_DSS_DISPC_VID1_BUF_THR_BUFHIGHTHR_RESETVAL          (0x000007ffU)
#define CSL_DSS_DISPC_VID1_BUF_THR_BUFHIGHTHR_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID1_BUF_THR_RESETVAL                     (0x07ff07f8U)

/* VID1_BUF_SIZE_STS */

#define CSL_DSS_DISPC_VID1_BUF_SIZE_STS_BUFSIZE_MASK            (0x0000FFFFU)
#define CSL_DSS_DISPC_VID1_BUF_SIZE_STS_BUFSIZE_SHIFT           (0U)
#define CSL_DSS_DISPC_VID1_BUF_SIZE_STS_BUFSIZE_RESETVAL        (0x00000800U)
#define CSL_DSS_DISPC_VID1_BUF_SIZE_STS_BUFSIZE_MAX             (0x0000ffffU)

#define CSL_DSS_DISPC_VID1_BUF_SIZE_STS_RESETVAL                (0x00000800U)

/* VID1_ROW_INC */

#define CSL_DSS_DISPC_VID1_ROW_INC_ROWINC_MASK                  (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID1_ROW_INC_ROWINC_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID1_ROW_INC_ROWINC_RESETVAL              (0x00000001U)
#define CSL_DSS_DISPC_VID1_ROW_INC_ROWINC_MAX                   (0xffffffffU)

#define CSL_DSS_DISPC_VID1_ROW_INC_RESETVAL                     (0x00000001U)

/* VID1_PIXEL_INC */

#define CSL_DSS_DISPC_VID1_PIXEL_INC_PIXELINC_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID1_PIXEL_INC_PIXELINC_SHIFT             (0U)
#define CSL_DSS_DISPC_VID1_PIXEL_INC_PIXELINC_RESETVAL          (0x00000001U)
#define CSL_DSS_DISPC_VID1_PIXEL_INC_PIXELINC_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_PIXEL_INC_RESETVAL                   (0x00000001U)

/* VID1_FIR */

#define CSL_DSS_DISPC_VID1_FIR_FIRVINC_MASK                     (0x1FFF0000U)
#define CSL_DSS_DISPC_VID1_FIR_FIRVINC_SHIFT                    (16U)
#define CSL_DSS_DISPC_VID1_FIR_FIRVINC_RESETVAL                 (0x00000400U)
#define CSL_DSS_DISPC_VID1_FIR_FIRVINC_MAX                      (0x00001fffU)

#define CSL_DSS_DISPC_VID1_FIR_FIRHINC_MASK                     (0x00001FFFU)
#define CSL_DSS_DISPC_VID1_FIR_FIRHINC_SHIFT                    (0U)
#define CSL_DSS_DISPC_VID1_FIR_FIRHINC_RESETVAL                 (0x00000400U)
#define CSL_DSS_DISPC_VID1_FIR_FIRHINC_MAX                      (0x00001fffU)

#define CSL_DSS_DISPC_VID1_FIR_RESETVAL                         (0x04000400U)

/* VID1_PICTURE_SIZE */

#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY_MASK           (0x0FFF0000U)
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY_SHIFT          (16U)
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEY_MAX            (0x00000fffU)

#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX_MASK           (0x000007FFU)
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX_SHIFT          (0U)
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_MEMSIZEX_MAX            (0x000007ffU)

#define CSL_DSS_DISPC_VID1_PICTURE_SIZE_RESETVAL                (0x00000000U)

/* VID1_ACCU */

#define CSL_DSS_DISPC_VID1_ACCU_HORIZONTALACCU_MASK             (0x000007FFU)
#define CSL_DSS_DISPC_VID1_ACCU_HORIZONTALACCU_SHIFT            (0U)
#define CSL_DSS_DISPC_VID1_ACCU_HORIZONTALACCU_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_ACCU_HORIZONTALACCU_MAX              (0x000007ffU)

#define CSL_DSS_DISPC_VID1_ACCU_VERTICALACCU_MASK               (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_ACCU_VERTICALACCU_SHIFT              (16U)
#define CSL_DSS_DISPC_VID1_ACCU_VERTICALACCU_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_ACCU_VERTICALACCU_MAX                (0x000007ffU)

#define CSL_DSS_DISPC_VID1_ACCU_RESETVAL                        (0x00000000U)

/* VID1_FIR_COEF_H */

#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC2_MASK               (0x00FF0000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC2_SHIFT              (16U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC2_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC1_MASK               (0x0000FF00U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC1_SHIFT              (8U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC1_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC1_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC0_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC0_SHIFT              (0U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC0_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC0_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC3_MASK               (0xFF000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC3_SHIFT              (24U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC3_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H_FIRHC3_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H_RESETVAL                  (0x00000000U)

/* VID1_FIR_COEF_HV */

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRHC4_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRHC4_SHIFT             (0U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRHC4_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRHC4_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0_SHIFT             (8U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC0_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1_MASK              (0x00FF0000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1_SHIFT             (16U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC1_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2_MASK              (0xFF000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2_SHIFT             (24U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_FIRVC2_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV_RESETVAL                 (0x00000000U)

/* VID1_CONV_COEF0 */

#define CSL_DSS_DISPC_VID1_CONV_COEF0_RCR_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF0_RCR_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID1_CONV_COEF0_RCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF0_RCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF0_RY_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID1_CONV_COEF0_RY_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID1_CONV_COEF0_RY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF0_RY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF0_RESETVAL                  (0x00000000U)

/* VID1_CONV_COEF1 */

#define CSL_DSS_DISPC_VID1_CONV_COEF1_GY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF1_GY_SHIFT                  (16U)
#define CSL_DSS_DISPC_VID1_CONV_COEF1_GY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF1_GY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF1_RCB_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID1_CONV_COEF1_RCB_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID1_CONV_COEF1_RCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF1_RCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF1_RESETVAL                  (0x00000000U)

/* VID1_CONV_COEF2 */

#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCB_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCB_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCR_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCR_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF2_GCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF2_RESETVAL                  (0x00000000U)

/* VID1_CONV_COEF3 */

#define CSL_DSS_DISPC_VID1_CONV_COEF3_BCR_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF3_BCR_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID1_CONV_COEF3_BCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF3_BCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF3_BY_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID1_CONV_COEF3_BY_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID1_CONV_COEF3_BY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF3_BY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF3_RESETVAL                  (0x00000000U)

/* VID1_CONV_COEF4 */

#define CSL_DSS_DISPC_VID1_CONV_COEF4_BCB_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID1_CONV_COEF4_BCB_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID1_CONV_COEF4_BCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_CONV_COEF4_BCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_CONV_COEF4_RESETVAL                  (0x00000000U)

/* VID2_BA */

#define CSL_DSS_DISPC_VID2_BA_BA_MASK                           (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID2_BA_BA_SHIFT                          (0U)
#define CSL_DSS_DISPC_VID2_BA_BA_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_VID2_BA_BA_MAX                            (0xffffffffU)

#define CSL_DSS_DISPC_VID2_BA_RESETVAL                          (0x00000000U)

/* VID2_POSITION */

#define CSL_DSS_DISPC_VID2_POSITION_POSY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_POSITION_POSY_SHIFT                  (16U)
#define CSL_DSS_DISPC_VID2_POSITION_POSY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID2_POSITION_POSY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID2_POSITION_POSX_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID2_POSITION_POSX_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID2_POSITION_POSX_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID2_POSITION_POSX_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID2_POSITION_RESETVAL                    (0x00000000U)

/* VID2_SIZE */

#define CSL_DSS_DISPC_VID2_SIZE_SIZEY_MASK                      (0x0FFF0000U)
#define CSL_DSS_DISPC_VID2_SIZE_SIZEY_SHIFT                     (16U)
#define CSL_DSS_DISPC_VID2_SIZE_SIZEY_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_VID2_SIZE_SIZEY_MAX                       (0x00000fffU)

#define CSL_DSS_DISPC_VID2_SIZE_SIZEX_MASK                      (0x00000FFFU)
#define CSL_DSS_DISPC_VID2_SIZE_SIZEX_SHIFT                     (0U)
#define CSL_DSS_DISPC_VID2_SIZE_SIZEX_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_VID2_SIZE_SIZEX_MAX                       (0x00000fffU)

#define CSL_DSS_DISPC_VID2_SIZE_RESETVAL                        (0x00000000U)

/* VID2_ATTRS */

#define CSL_DSS_DISPC_VID2_ATTRS_FULLRANGE_MASK                 (0x00000800U)
#define CSL_DSS_DISPC_VID2_ATTRS_FULLRANGE_SHIFT                (11U)
#define CSL_DSS_DISPC_VID2_ATTRS_FULLRANGE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FULLRANGE_LIMRANGE             (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FULLRANGE_FULLRANGE            (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_MASK                  (0x00003000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_SHIFT                 (12U)
#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_NOROT                 (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_ROT90                 (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_ROT180                (0x00000002U)
#define CSL_DSS_DISPC_VID2_ATTRS_ROTATION_ROT270                (0x00000003U)

#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_MASK                  (0x00000060U)
#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_SHIFT                 (5U)
#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_RESIZEPROC            (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_HRESIZE               (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_VRESIZE               (0x00000002U)
#define CSL_DSS_DISPC_VID2_ATTRS_RESIZEEN_HVRESIZE              (0x00000003U)

#define CSL_DSS_DISPC_VID2_ATTRS_REPLICATIONEN_MASK             (0x00000400U)
#define CSL_DSS_DISPC_VID2_ATTRS_REPLICATIONEN_SHIFT            (10U)
#define CSL_DSS_DISPC_VID2_ATTRS_REPLICATIONEN_RESETVAL         (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_REPLICATIONEN_VREPLDIS         (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_REPLICATIONEN_VREPLENB         (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_MASK                 (0x0000C000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_SHIFT                (14U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_RESETVAL             (0x00000002U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_BURST2X128B          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_BURST4X128B          (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_BURST8X128B          (0x00000002U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTSIZE_RES                  (0x00000003U)

#define CSL_DSS_DISPC_VID2_ATTRS_HRESIZECONF_MASK               (0x00000080U)
#define CSL_DSS_DISPC_VID2_ATTRS_HRESIZECONF_SHIFT              (7U)
#define CSL_DSS_DISPC_VID2_ATTRS_HRESIZECONF_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_HRESIZECONF_MAX                (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_COLORCONVEN_MASK               (0x00000200U)
#define CSL_DSS_DISPC_VID2_ATTRS_COLORCONVEN_SHIFT              (9U)
#define CSL_DSS_DISPC_VID2_ATTRS_COLORCONVEN_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_COLORCONVEN_COLSPCDIS          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_COLORCONVEN_COLSPCENB          (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_EN_MASK                        (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_EN_SHIFT                       (0U)
#define CSL_DSS_DISPC_VID2_ATTRS_EN_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_EN_VIDEODIS                    (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_EN_VIDEOENB                    (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_BUFPRELOAD_MASK                (0x00080000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BUFPRELOAD_SHIFT               (19U)
#define CSL_DSS_DISPC_VID2_ATTRS_BUFPRELOAD_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BUFPRELOAD_DEFVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BUFPRELOAD_HIGHTHRES           (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_VERTICALTAPS_MASK              (0x00200000U)
#define CSL_DSS_DISPC_VID2_ATTRS_VERTICALTAPS_SHIFT             (21U)
#define CSL_DSS_DISPC_VID2_ATTRS_VERTICALTAPS_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_VERTICALTAPS_TAPS5             (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_VERTICALTAPS_TAPS3             (0x00000000U)

#define CSL_DSS_DISPC_VID2_ATTRS_ARBITRATION_MASK               (0x00800000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ARBITRATION_SHIFT              (23U)
#define CSL_DSS_DISPC_VID2_ATTRS_ARBITRATION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ARBITRATION_NORMALPRIO         (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ARBITRATION_HIGHPRIO           (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESH_MASK               (0x01000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESH_SHIFT              (24U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESH_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESH_SELFREFRESHDIS     (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESH_SELFREFRESHENB     (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_FMT_MASK                       (0x0000001EU)
#define CSL_DSS_DISPC_VID2_ATTRS_FMT_SHIFT                      (1U)
#define CSL_DSS_DISPC_VID2_ATTRS_FMT_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FMT_MAX                        (0x0000000fU)

#define CSL_DSS_DISPC_VID2_ATTRS_ZORDEREN_MASK                  (0x02000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDEREN_SHIFT                 (25U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDEREN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDEREN_ZORDERDIS             (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDEREN_ZORDERENB             (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_MASK                    (0x0C000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_SHIFT                   (26U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_ZORDER0                 (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_ZORDER1                 (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_ZORDER2                 (0x00000002U)
#define CSL_DSS_DISPC_VID2_ATTRS_ZORDER_ZORDER3                 (0x00000003U)

#define CSL_DSS_DISPC_VID2_ATTRS_PREMULTIPLYALPHA_MASK          (0x10000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_PREMULTIPLYALPHA_SHIFT         (28U)
#define CSL_DSS_DISPC_VID2_ATTRS_PREMULTIPLYALPHA_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA  (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA  (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_BURSTTYPE_MASK                 (0x20000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTTYPE_SHIFT                (29U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTTYPE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTTYPE_INC                  (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_BURSTTYPE_BLCK                 (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_MASK               (0xC0000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_SHIFT              (30U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_PRIMARYLCDSEL      (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_SECONDARYLCDSEL    (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_WRITEBACKSEL       (0x00000003U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT2_THIRDLCDSEL        (0x00000002U)

#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT_MASK                (0x00010000U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT_SHIFT               (16U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT_LCDOP               (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_CHANNELOUT_TVOP                (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESHAUTO_MASK           (0x00020000U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESHAUTO_SHIFT          (17U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESHAUTO_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTODIS  (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTOEN  (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_DOUBLESTRIDE_MASK              (0x00400000U)
#define CSL_DSS_DISPC_VID2_ATTRS_DOUBLESTRIDE_SHIFT             (22U)
#define CSL_DSS_DISPC_VID2_ATTRS_DOUBLESTRIDE_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_DOUBLESTRIDE_INITIAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_DOUBLESTRIDE_DOUBLE            (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_FORCE1DTILEDMODE_MASK          (0x00100000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FORCE1DTILEDMODE_SHIFT         (20U)
#define CSL_DSS_DISPC_VID2_ATTRS_FORCE1DTILEDMODE_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS  (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS  (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_FRMPACKINGMODE_MASK            (0x00000100U)
#define CSL_DSS_DISPC_VID2_ATTRS_FRMPACKINGMODE_SHIFT           (8U)
#define CSL_DSS_DISPC_VID2_ATTRS_FRMPACKINGMODE_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FRMPACKINGMODE_FPMDIS          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS_FRMPACKINGMODE_FPMENB          (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS_RESETVAL                       (0x00008400U)

/* VID2_BUF_THR */

#define CSL_DSS_DISPC_VID2_BUF_THR_BUFLOWTHR_MASK               (0x0000FFFFU)
#define CSL_DSS_DISPC_VID2_BUF_THR_BUFLOWTHR_SHIFT              (0U)
#define CSL_DSS_DISPC_VID2_BUF_THR_BUFLOWTHR_RESETVAL           (0x000007f8U)
#define CSL_DSS_DISPC_VID2_BUF_THR_BUFLOWTHR_MAX                (0x0000ffffU)

#define CSL_DSS_DISPC_VID2_BUF_THR_BUFHIGHTHR_MASK              (0xFFFF0000U)
#define CSL_DSS_DISPC_VID2_BUF_THR_BUFHIGHTHR_SHIFT             (16U)
#define CSL_DSS_DISPC_VID2_BUF_THR_BUFHIGHTHR_RESETVAL          (0x000007ffU)
#define CSL_DSS_DISPC_VID2_BUF_THR_BUFHIGHTHR_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID2_BUF_THR_RESETVAL                     (0x07ff07f8U)

/* VID2_BUF_SIZE_STS */

#define CSL_DSS_DISPC_VID2_BUF_SIZE_STS_BUFSIZE_MASK            (0x0000FFFFU)
#define CSL_DSS_DISPC_VID2_BUF_SIZE_STS_BUFSIZE_SHIFT           (0U)
#define CSL_DSS_DISPC_VID2_BUF_SIZE_STS_BUFSIZE_RESETVAL        (0x00000800U)
#define CSL_DSS_DISPC_VID2_BUF_SIZE_STS_BUFSIZE_MAX             (0x0000ffffU)

#define CSL_DSS_DISPC_VID2_BUF_SIZE_STS_RESETVAL                (0x00000800U)

/* VID2_ROW_INC */

#define CSL_DSS_DISPC_VID2_ROW_INC_ROWINC_MASK                  (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID2_ROW_INC_ROWINC_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID2_ROW_INC_ROWINC_RESETVAL              (0x00000001U)
#define CSL_DSS_DISPC_VID2_ROW_INC_ROWINC_MAX                   (0xffffffffU)

#define CSL_DSS_DISPC_VID2_ROW_INC_RESETVAL                     (0x00000001U)

/* VID2_PIXEL_INC */

#define CSL_DSS_DISPC_VID2_PIXEL_INC_PIXELINC_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID2_PIXEL_INC_PIXELINC_SHIFT             (0U)
#define CSL_DSS_DISPC_VID2_PIXEL_INC_PIXELINC_RESETVAL          (0x00000001U)
#define CSL_DSS_DISPC_VID2_PIXEL_INC_PIXELINC_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_PIXEL_INC_RESETVAL                   (0x00000001U)

/* VID2_FIR */

#define CSL_DSS_DISPC_VID2_FIR_FIRVINC_MASK                     (0x1FFF0000U)
#define CSL_DSS_DISPC_VID2_FIR_FIRVINC_SHIFT                    (16U)
#define CSL_DSS_DISPC_VID2_FIR_FIRVINC_RESETVAL                 (0x00000400U)
#define CSL_DSS_DISPC_VID2_FIR_FIRVINC_MAX                      (0x00001fffU)

#define CSL_DSS_DISPC_VID2_FIR_FIRHINC_MASK                     (0x00001FFFU)
#define CSL_DSS_DISPC_VID2_FIR_FIRHINC_SHIFT                    (0U)
#define CSL_DSS_DISPC_VID2_FIR_FIRHINC_RESETVAL                 (0x00000400U)
#define CSL_DSS_DISPC_VID2_FIR_FIRHINC_MAX                      (0x00001fffU)

#define CSL_DSS_DISPC_VID2_FIR_RESETVAL                         (0x04000400U)

/* VID2_PICTURE_SIZE */

#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEY_MASK           (0x0FFF0000U)
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEY_SHIFT          (16U)
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEY_MAX            (0x00000fffU)

#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEX_MASK           (0x000007FFU)
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEX_SHIFT          (0U)
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEX_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_MEMSIZEX_MAX            (0x000007ffU)

#define CSL_DSS_DISPC_VID2_PICTURE_SIZE_RESETVAL                (0x00000000U)

/* VID2_ACCU */

#define CSL_DSS_DISPC_VID2_ACCU_HORIZONTALACCU_MASK             (0x000007FFU)
#define CSL_DSS_DISPC_VID2_ACCU_HORIZONTALACCU_SHIFT            (0U)
#define CSL_DSS_DISPC_VID2_ACCU_HORIZONTALACCU_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_ACCU_HORIZONTALACCU_MAX              (0x000007ffU)

#define CSL_DSS_DISPC_VID2_ACCU_VERTICALACCU_MASK               (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_ACCU_VERTICALACCU_SHIFT              (16U)
#define CSL_DSS_DISPC_VID2_ACCU_VERTICALACCU_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_ACCU_VERTICALACCU_MAX                (0x000007ffU)

#define CSL_DSS_DISPC_VID2_ACCU_RESETVAL                        (0x00000000U)

/* VID2_FIR_COEF_H */

#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC2_MASK               (0x00FF0000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC2_SHIFT              (16U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC2_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC1_MASK               (0x0000FF00U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC1_SHIFT              (8U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC1_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC1_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC0_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC0_SHIFT              (0U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC0_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC0_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC3_MASK               (0xFF000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC3_SHIFT              (24U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC3_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H_FIRHC3_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H_RESETVAL                  (0x00000000U)

/* VID2_FIR_COEF_HV */

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC1_MASK              (0x00FF0000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC1_SHIFT             (16U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC1_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC1_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC0_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC0_SHIFT             (8U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC0_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC0_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRHC4_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRHC4_SHIFT             (0U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRHC4_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRHC4_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC2_MASK              (0xFF000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC2_SHIFT             (24U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC2_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_FIRVC2_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV_RESETVAL                 (0x00000000U)

/* VID2_CONV_COEF0 */

#define CSL_DSS_DISPC_VID2_CONV_COEF0_RCR_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF0_RCR_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID2_CONV_COEF0_RCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF0_RCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF0_RY_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID2_CONV_COEF0_RY_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID2_CONV_COEF0_RY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF0_RY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF0_RESETVAL                  (0x00000000U)

/* VID2_CONV_COEF1 */

#define CSL_DSS_DISPC_VID2_CONV_COEF1_GY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF1_GY_SHIFT                  (16U)
#define CSL_DSS_DISPC_VID2_CONV_COEF1_GY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF1_GY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF1_RCB_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID2_CONV_COEF1_RCB_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID2_CONV_COEF1_RCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF1_RCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF1_RESETVAL                  (0x00000000U)

/* VID2_CONV_COEF2 */

#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCB_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCB_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCR_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCR_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF2_GCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF2_RESETVAL                  (0x00000000U)

/* VID2_CONV_COEF3 */

#define CSL_DSS_DISPC_VID2_CONV_COEF3_BCR_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF3_BCR_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID2_CONV_COEF3_BCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF3_BCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF3_BY_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID2_CONV_COEF3_BY_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID2_CONV_COEF3_BY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF3_BY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF3_RESETVAL                  (0x00000000U)

/* VID2_CONV_COEF4 */

#define CSL_DSS_DISPC_VID2_CONV_COEF4_BCB_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID2_CONV_COEF4_BCB_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID2_CONV_COEF4_BCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_CONV_COEF4_BCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_CONV_COEF4_RESETVAL                  (0x00000000U)

/* DATA1_CYCLE1 */

#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE1_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA1_CYCLE1_RESETVAL                     (0x00000000U)

/* DATA1_CYCLE2 */

#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE2_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA1_CYCLE2_RESETVAL                     (0x00000000U)

/* DATA1_CYCLE3 */

#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA1_CYCLE3_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA1_CYCLE3_RESETVAL                     (0x00000000U)

/* VID1_FIR_COEF_V */

#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC22_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC22_SHIFT             (8U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC22_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC22_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC00_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC00_SHIFT             (0U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC00_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V_FIRVC00_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_V_RESETVAL                  (0x00000000U)

/* VID2_FIR_COEF_V */

#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC22_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC22_SHIFT             (8U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC22_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC22_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC00_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC00_SHIFT             (0U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC00_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V_FIRVC00_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_V_RESETVAL                  (0x00000000U)

/* CPR1_COEF_R */

#define CSL_DSS_DISPC_CPR1_COEF_R_RB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR1_COEF_R_RB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_R_RR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_R_RG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_R_RG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_R_RESETVAL                      (0x00000000U)

/* CPR1_COEF_G */

#define CSL_DSS_DISPC_CPR1_COEF_G_GB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR1_COEF_G_GB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_G_GR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_G_GG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_G_GG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_G_RESETVAL                      (0x00000000U)

/* CPR1_COEF_B */

#define CSL_DSS_DISPC_CPR1_COEF_B_BB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR1_COEF_B_BB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_B_BR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_B_BG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR1_COEF_B_BG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR1_COEF_B_RESETVAL                      (0x00000000U)

/* GFX_PRELOAD */

#define CSL_DSS_DISPC_GFX_PRELOAD_PRELOAD_MASK                  (0x00000FFFU)
#define CSL_DSS_DISPC_GFX_PRELOAD_PRELOAD_SHIFT                 (0U)
#define CSL_DSS_DISPC_GFX_PRELOAD_PRELOAD_RESETVAL              (0x00000100U)
#define CSL_DSS_DISPC_GFX_PRELOAD_PRELOAD_MAX                   (0x00000fffU)

#define CSL_DSS_DISPC_GFX_PRELOAD_RESETVAL                      (0x00000100U)

/* VID1_PRELOAD */

#define CSL_DSS_DISPC_VID1_PRELOAD_PRELOAD_MASK                 (0x00000FFFU)
#define CSL_DSS_DISPC_VID1_PRELOAD_PRELOAD_SHIFT                (0U)
#define CSL_DSS_DISPC_VID1_PRELOAD_PRELOAD_RESETVAL             (0x00000100U)
#define CSL_DSS_DISPC_VID1_PRELOAD_PRELOAD_MAX                  (0x00000fffU)

#define CSL_DSS_DISPC_VID1_PRELOAD_RESETVAL                     (0x00000100U)

/* VID2_PRELOAD */

#define CSL_DSS_DISPC_VID2_PRELOAD_PRELOAD_MASK                 (0x00000FFFU)
#define CSL_DSS_DISPC_VID2_PRELOAD_PRELOAD_SHIFT                (0U)
#define CSL_DSS_DISPC_VID2_PRELOAD_PRELOAD_RESETVAL             (0x00000100U)
#define CSL_DSS_DISPC_VID2_PRELOAD_PRELOAD_MAX                  (0x00000fffU)

#define CSL_DSS_DISPC_VID2_PRELOAD_RESETVAL                     (0x00000100U)

/* CTRL2 */

#define CSL_DSS_DISPC_CTRL2_STDITHEREN_MASK                     (0x00000080U)
#define CSL_DSS_DISPC_CTRL2_STDITHEREN_SHIFT                    (7U)
#define CSL_DSS_DISPC_CTRL2_STDITHEREN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_STDITHEREN_STDITHDIS                (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_STDITHEREN_STDITHENB                (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_MASK                   (0x00000300U)
#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_SHIFT                  (8U)
#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_OALSB12B               (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_OALSB16B               (0x00000001U)
#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_OALSB18B               (0x00000002U)
#define CSL_DSS_DISPC_CTRL2_TFTDATALINES_OALSB24B               (0x00000003U)

#define CSL_DSS_DISPC_CTRL2_STALLMODE_MASK                      (0x00000800U)
#define CSL_DSS_DISPC_CTRL2_STALLMODE_SHIFT                     (11U)
#define CSL_DSS_DISPC_CTRL2_STALLMODE_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_STALLMODE_NMODE                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_STALLMODE_RFBIMODE                  (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_MONOCOLOR_MASK                      (0x00000004U)
#define CSL_DSS_DISPC_CTRL2_MONOCOLOR_SHIFT                     (2U)
#define CSL_DSS_DISPC_CTRL2_MONOCOLOR_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_MONOCOLOR_COLOPENB                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_MONOCOLOR_MONOPENB                  (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_M8B_MASK                            (0x00000010U)
#define CSL_DSS_DISPC_CTRL2_M8B_SHIFT                           (4U)
#define CSL_DSS_DISPC_CTRL2_M8B_RESETVAL                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_M8B__4PIXTOPANEL                    (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_M8B__8PIXTOPANEL                    (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_STNTFT_MASK                         (0x00000008U)
#define CSL_DSS_DISPC_CTRL2_STNTFT_SHIFT                        (3U)
#define CSL_DSS_DISPC_CTRL2_STNTFT_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_STNTFT_STNDISPENB                   (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_STNTFT_ATFTDISENB                   (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_GOLCD_MASK                          (0x00000020U)
#define CSL_DSS_DISPC_CTRL2_GOLCD_SHIFT                         (5U)
#define CSL_DSS_DISPC_CTRL2_GOLCD_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_GOLCD_HFUISR                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_GOLCD_UFPSR                         (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_LCDEN_MASK                          (0x00000001U)
#define CSL_DSS_DISPC_CTRL2_LCDEN_SHIFT                         (0U)
#define CSL_DSS_DISPC_CTRL2_LCDEN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_LCDEN_LCDOPDIS                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_LCDEN_LCDOPENB                      (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_MASK   (0xC0000000U)
#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_SHIFT  (30U)
#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_ONEFRAME  (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_TWOFRAMES  (0x00000001U)
#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_FOURFRAMES  (0x00000002U)
#define CSL_DSS_DISPC_CTRL2_SPATIALTEMPORALDITHERINGFRMS_RESERVED  (0x00000003U)

#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_MASK                  (0x06000000U)
#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_SHIFT                 (25U)
#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_LOWLEVEL              (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_HIGHLEVEL             (0x00000001U)
#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_UNCHANGED             (0x00000002U)
#define CSL_DSS_DISPC_CTRL2_TDMUNUSEDBITS_RES                   (0x00000003U)

#define CSL_DSS_DISPC_CTRL2_TDMEN_MASK                          (0x00100000U)
#define CSL_DSS_DISPC_CTRL2_TDMEN_SHIFT                         (20U)
#define CSL_DSS_DISPC_CTRL2_TDMEN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMEN_TDMDIS                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMEN_TDMENB                        (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE_MASK                (0x00600000U)
#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE_SHIFT               (21U)
#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE__8BPARAINT          (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE__9BPARAINT          (0x00000001U)
#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE__12BPARAINT         (0x00000002U)
#define CSL_DSS_DISPC_CTRL2_TDMPARALLELMODE__16BPARAINT         (0x00000003U)

#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT_MASK                    (0x01800000U)
#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT_SHIFT                   (23U)
#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT__1CYCPERPIX             (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT__2CYCPERPIX             (0x00000001U)
#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT__3CYCPERPIX             (0x00000002U)
#define CSL_DSS_DISPC_CTRL2_TDMCYCLEFMT__3CYCPER2PIX            (0x00000003U)

#define CSL_DSS_DISPC_CTRL2_OVLYOPTIMIZATION_MASK               (0x00001000U)
#define CSL_DSS_DISPC_CTRL2_OVLYOPTIMIZATION_SHIFT              (12U)
#define CSL_DSS_DISPC_CTRL2_OVLYOPTIMIZATION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_OVLYOPTIMIZATION_GDBVWFM            (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_OVLYOPTIMIZATION_GDBVWNFM           (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_GOWB_MASK                           (0x00000040U)
#define CSL_DSS_DISPC_CTRL2_GOWB_SHIFT                          (6U)
#define CSL_DSS_DISPC_CTRL2_GOWB_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_GOWB_HFUISR                         (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_GOWB_UFPSR                          (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_TVOVLYOPTIMIZATION_MASK             (0x00002000U)
#define CSL_DSS_DISPC_CTRL2_TVOVLYOPTIMIZATION_SHIFT            (13U)
#define CSL_DSS_DISPC_CTRL2_TVOVLYOPTIMIZATION_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TVOVLYOPTIMIZATION_GDBVWFM          (0x00000000U)
#define CSL_DSS_DISPC_CTRL2_TVOVLYOPTIMIZATION_GDBVWNFM         (0x00000001U)

#define CSL_DSS_DISPC_CTRL2_RESETVAL                            (0x00000000U)

/* GFX_POSITION2 */

#define CSL_DSS_DISPC_GFX_POSITION2_POSX_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_GFX_POSITION2_POSX_SHIFT                  (0U)
#define CSL_DSS_DISPC_GFX_POSITION2_POSX_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GFX_POSITION2_POSX_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_GFX_POSITION2_POSY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_GFX_POSITION2_POSY_SHIFT                  (16U)
#define CSL_DSS_DISPC_GFX_POSITION2_POSY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GFX_POSITION2_POSY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_GFX_POSITION2_RESETVAL                    (0x00000000U)

/* VID1_POSITION2 */

#define CSL_DSS_DISPC_VID1_POSITION2_POSY_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_POSITION2_POSY_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID1_POSITION2_POSY_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_POSITION2_POSY_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_POSITION2_POSX_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID1_POSITION2_POSX_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID1_POSITION2_POSX_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID1_POSITION2_POSX_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID1_POSITION2_RESETVAL                   (0x00000000U)

/* VID2_POSITION2 */

#define CSL_DSS_DISPC_VID2_POSITION2_POSY_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_POSITION2_POSY_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID2_POSITION2_POSY_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_POSITION2_POSY_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_POSITION2_POSX_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID2_POSITION2_POSX_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID2_POSITION2_POSX_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID2_POSITION2_POSX_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID2_POSITION2_RESETVAL                   (0x00000000U)

/* VID3_POSITION2 */

#define CSL_DSS_DISPC_VID3_POSITION2_POSY_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_POSITION2_POSY_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID3_POSITION2_POSY_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_POSITION2_POSY_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_POSITION2_POSX_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID3_POSITION2_POSX_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID3_POSITION2_POSX_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_POSITION2_POSX_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_POSITION2_RESETVAL                   (0x00000000U)

/* VID3_ACCU */

#define CSL_DSS_DISPC_VID3_ACCU_HORIZONTALACCU_MASK             (0x000007FFU)
#define CSL_DSS_DISPC_VID3_ACCU_HORIZONTALACCU_SHIFT            (0U)
#define CSL_DSS_DISPC_VID3_ACCU_HORIZONTALACCU_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_ACCU_HORIZONTALACCU_MAX              (0x000007ffU)

#define CSL_DSS_DISPC_VID3_ACCU_VERTICALACCU_MASK               (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_ACCU_VERTICALACCU_SHIFT              (16U)
#define CSL_DSS_DISPC_VID3_ACCU_VERTICALACCU_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ACCU_VERTICALACCU_MAX                (0x000007ffU)

#define CSL_DSS_DISPC_VID3_ACCU_RESETVAL                        (0x00000000U)

/* VID3_BA */

#define CSL_DSS_DISPC_VID3_BA_BA_MASK                           (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID3_BA_BA_SHIFT                          (0U)
#define CSL_DSS_DISPC_VID3_BA_BA_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_VID3_BA_BA_MAX                            (0xffffffffU)

#define CSL_DSS_DISPC_VID3_BA_RESETVAL                          (0x00000000U)

/* VID3_FIR_COEF_H */

#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC2_MASK               (0x00FF0000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC2_SHIFT              (16U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC2_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC1_MASK               (0x0000FF00U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC1_SHIFT              (8U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC1_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC1_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC0_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC0_SHIFT              (0U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC0_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC0_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC3_MASK               (0xFF000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC3_SHIFT              (24U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC3_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H_FIRHC3_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H_RESETVAL                  (0x00000000U)

/* VID3_FIR_COEF_HV */

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC0_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC0_SHIFT             (8U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC0_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC0_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4_SHIFT             (0U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRHC4_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC2_MASK              (0xFF000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC2_SHIFT             (24U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC2_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC2_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC1_MASK              (0x00FF0000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC1_SHIFT             (16U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC1_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_FIRVC1_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV_RESETVAL                 (0x00000000U)

/* VID3_FIR_COEF_V */

#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC22_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC22_SHIFT             (8U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC22_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC22_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC00_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC00_SHIFT             (0U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC00_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V_FIRVC00_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_V_RESETVAL                  (0x00000000U)

/* VID3_ATTRS */

#define CSL_DSS_DISPC_VID3_ATTRS_EN_MASK                        (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_EN_SHIFT                       (0U)
#define CSL_DSS_DISPC_VID3_ATTRS_EN_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_EN_VIDEODIS                    (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_EN_VIDEOENB                    (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_MASK                 (0x0000C000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_SHIFT                (14U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_RESETVAL             (0x00000002U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_BURST2X128B          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_BURST4X128B          (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_BURST8X128B          (0x00000002U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTSIZE_RES                  (0x00000003U)

#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESH_MASK               (0x01000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESH_SHIFT              (24U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESH_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESH_SELFREFRESHDIS     (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESH_SELFREFRESHENB     (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_COLORCONVEN_MASK               (0x00000200U)
#define CSL_DSS_DISPC_VID3_ATTRS_COLORCONVEN_SHIFT              (9U)
#define CSL_DSS_DISPC_VID3_ATTRS_COLORCONVEN_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_COLORCONVEN_COLSPCDIS          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_COLORCONVEN_COLSPCENB          (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_REPLICATIONEN_MASK             (0x00000400U)
#define CSL_DSS_DISPC_VID3_ATTRS_REPLICATIONEN_SHIFT            (10U)
#define CSL_DSS_DISPC_VID3_ATTRS_REPLICATIONEN_RESETVAL         (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_REPLICATIONEN_VREPLENB         (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_REPLICATIONEN_VREPLDIS         (0x00000000U)

#define CSL_DSS_DISPC_VID3_ATTRS_VERTICALTAPS_MASK              (0x00200000U)
#define CSL_DSS_DISPC_VID3_ATTRS_VERTICALTAPS_SHIFT             (21U)
#define CSL_DSS_DISPC_VID3_ATTRS_VERTICALTAPS_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_VERTICALTAPS_TAPS5             (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_VERTICALTAPS_TAPS3             (0x00000000U)

#define CSL_DSS_DISPC_VID3_ATTRS_FMT_MASK                       (0x0000001EU)
#define CSL_DSS_DISPC_VID3_ATTRS_FMT_SHIFT                      (1U)
#define CSL_DSS_DISPC_VID3_ATTRS_FMT_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FMT_MAX                        (0x0000000fU)

#define CSL_DSS_DISPC_VID3_ATTRS_ARBITRATION_MASK               (0x00800000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ARBITRATION_SHIFT              (23U)
#define CSL_DSS_DISPC_VID3_ATTRS_ARBITRATION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ARBITRATION_HIGHPRIO           (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_ARBITRATION_NORMALPRIO         (0x00000000U)

#define CSL_DSS_DISPC_VID3_ATTRS_FULLRANGE_MASK                 (0x00000800U)
#define CSL_DSS_DISPC_VID3_ATTRS_FULLRANGE_SHIFT                (11U)
#define CSL_DSS_DISPC_VID3_ATTRS_FULLRANGE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FULLRANGE_FULLRANGE            (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_FULLRANGE_LIMRANGE             (0x00000000U)

#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_MASK                  (0x00000060U)
#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_SHIFT                 (5U)
#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_HVRESIZE              (0x00000003U)
#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_VRESIZE               (0x00000002U)
#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_HRESIZE               (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_RESIZEEN_RESIZEPROC            (0x00000000U)

#define CSL_DSS_DISPC_VID3_ATTRS_HRESIZECONF_MASK               (0x00000080U)
#define CSL_DSS_DISPC_VID3_ATTRS_HRESIZECONF_SHIFT              (7U)
#define CSL_DSS_DISPC_VID3_ATTRS_HRESIZECONF_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_HRESIZECONF_MAX                (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_BUFPRELOAD_MASK                (0x00080000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BUFPRELOAD_SHIFT               (19U)
#define CSL_DSS_DISPC_VID3_ATTRS_BUFPRELOAD_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BUFPRELOAD_DEFVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BUFPRELOAD_HIGHTHRES           (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_MASK                  (0x00003000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_SHIFT                 (12U)
#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_ROT270                (0x00000003U)
#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_ROT180                (0x00000002U)
#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_ROT90                 (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_ROTATION_NOROT                 (0x00000000U)

#define CSL_DSS_DISPC_VID3_ATTRS_ZORDEREN_MASK                  (0x02000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDEREN_SHIFT                 (25U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDEREN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDEREN_ZORDERDIS             (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDEREN_ZORDERENB             (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_MASK                    (0x0C000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_SHIFT                   (26U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_ZORDER0                 (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_ZORDER1                 (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_ZORDER2                 (0x00000002U)
#define CSL_DSS_DISPC_VID3_ATTRS_ZORDER_ZORDER3                 (0x00000003U)

#define CSL_DSS_DISPC_VID3_ATTRS_PREMULTIPLYALPHA_MASK          (0x10000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_PREMULTIPLYALPHA_SHIFT         (28U)
#define CSL_DSS_DISPC_VID3_ATTRS_PREMULTIPLYALPHA_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_PREMULTIPLYALPHA_NONPREMULTIPLIEDALPHA  (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_PREMULTIPLYALPHA_PREMULTIPLIEDALPHA  (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_BURSTTYPE_MASK                 (0x20000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTTYPE_SHIFT                (29U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTTYPE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTTYPE_INC                  (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_BURSTTYPE_BLCK                 (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_MASK               (0xC0000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_SHIFT              (30U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_PRIMARYLCDSEL      (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_SECONDARYLCDSEL    (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_WRITEBACKSEL       (0x00000003U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT2_THIRDLCDSEL        (0x00000002U)

#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT_MASK                (0x00010000U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT_SHIFT               (16U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT_LCDOP               (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_CHANNELOUT_TVOP                (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESHAUTO_MASK           (0x00020000U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESHAUTO_SHIFT          (17U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESHAUTO_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTODIS  (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_SELFREFRESHAUTO_SELFREFRESHAUTOEN  (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_DOUBLESTRIDE_MASK              (0x00400000U)
#define CSL_DSS_DISPC_VID3_ATTRS_DOUBLESTRIDE_SHIFT             (22U)
#define CSL_DSS_DISPC_VID3_ATTRS_DOUBLESTRIDE_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_DOUBLESTRIDE_INITIAL           (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_DOUBLESTRIDE_DOUBLE            (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_FORCE1DTILEDMODE_MASK          (0x00100000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FORCE1DTILEDMODE_SHIFT         (20U)
#define CSL_DSS_DISPC_VID3_ATTRS_FORCE1DTILEDMODE_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS  (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS  (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_FRMPACKINGMODE_MASK            (0x00000100U)
#define CSL_DSS_DISPC_VID3_ATTRS_FRMPACKINGMODE_SHIFT           (8U)
#define CSL_DSS_DISPC_VID3_ATTRS_FRMPACKINGMODE_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FRMPACKINGMODE_FPMDIS          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS_FRMPACKINGMODE_FPMENB          (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS_RESETVAL                       (0x00008400U)

/* VID3_CONV_COEF0 */

#define CSL_DSS_DISPC_VID3_CONV_COEF0_RY_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID3_CONV_COEF0_RY_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID3_CONV_COEF0_RY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF0_RY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF0_RCR_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF0_RCR_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID3_CONV_COEF0_RCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF0_RCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF0_RESETVAL                  (0x00000000U)

/* VID3_CONV_COEF1 */

#define CSL_DSS_DISPC_VID3_CONV_COEF1_RCB_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID3_CONV_COEF1_RCB_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID3_CONV_COEF1_RCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF1_RCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF1_GY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF1_GY_SHIFT                  (16U)
#define CSL_DSS_DISPC_VID3_CONV_COEF1_GY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF1_GY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF1_RESETVAL                  (0x00000000U)

/* VID3_CONV_COEF2 */

#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCR_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCR_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCB_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCB_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF2_GCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF2_RESETVAL                  (0x00000000U)

/* VID3_CONV_COEF3 */

#define CSL_DSS_DISPC_VID3_CONV_COEF3_BY_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID3_CONV_COEF3_BY_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID3_CONV_COEF3_BY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF3_BY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF3_BCR_MASK                  (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF3_BCR_SHIFT                 (16U)
#define CSL_DSS_DISPC_VID3_CONV_COEF3_BCR_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF3_BCR_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF3_RESETVAL                  (0x00000000U)

/* VID3_CONV_COEF4 */

#define CSL_DSS_DISPC_VID3_CONV_COEF4_BCB_MASK                  (0x000007FFU)
#define CSL_DSS_DISPC_VID3_CONV_COEF4_BCB_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID3_CONV_COEF4_BCB_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_VID3_CONV_COEF4_BCB_MAX                   (0x000007ffU)

#define CSL_DSS_DISPC_VID3_CONV_COEF4_RESETVAL                  (0x00000000U)

/* VID3_BUF_SIZE_STS */

#define CSL_DSS_DISPC_VID3_BUF_SIZE_STS_BUFSIZE_MASK            (0x0000FFFFU)
#define CSL_DSS_DISPC_VID3_BUF_SIZE_STS_BUFSIZE_SHIFT           (0U)
#define CSL_DSS_DISPC_VID3_BUF_SIZE_STS_BUFSIZE_RESETVAL        (0x00000800U)
#define CSL_DSS_DISPC_VID3_BUF_SIZE_STS_BUFSIZE_MAX             (0x0000ffffU)

#define CSL_DSS_DISPC_VID3_BUF_SIZE_STS_RESETVAL                (0x00000800U)

/* VID3_BUF_THR */

#define CSL_DSS_DISPC_VID3_BUF_THR_BUFHIGHTHR_MASK              (0xFFFF0000U)
#define CSL_DSS_DISPC_VID3_BUF_THR_BUFHIGHTHR_SHIFT             (16U)
#define CSL_DSS_DISPC_VID3_BUF_THR_BUFHIGHTHR_RESETVAL          (0x000007ffU)
#define CSL_DSS_DISPC_VID3_BUF_THR_BUFHIGHTHR_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID3_BUF_THR_BUFLOWTHR_MASK               (0x0000FFFFU)
#define CSL_DSS_DISPC_VID3_BUF_THR_BUFLOWTHR_SHIFT              (0U)
#define CSL_DSS_DISPC_VID3_BUF_THR_BUFLOWTHR_RESETVAL           (0x000007f8U)
#define CSL_DSS_DISPC_VID3_BUF_THR_BUFLOWTHR_MAX                (0x0000ffffU)

#define CSL_DSS_DISPC_VID3_BUF_THR_RESETVAL                     (0x07ff07f8U)

/* VID3_FIR */

#define CSL_DSS_DISPC_VID3_FIR_FIRVINC_MASK                     (0x1FFF0000U)
#define CSL_DSS_DISPC_VID3_FIR_FIRVINC_SHIFT                    (16U)
#define CSL_DSS_DISPC_VID3_FIR_FIRVINC_RESETVAL                 (0x00000400U)
#define CSL_DSS_DISPC_VID3_FIR_FIRVINC_MAX                      (0x00001fffU)

#define CSL_DSS_DISPC_VID3_FIR_FIRHINC_MASK                     (0x00001FFFU)
#define CSL_DSS_DISPC_VID3_FIR_FIRHINC_SHIFT                    (0U)
#define CSL_DSS_DISPC_VID3_FIR_FIRHINC_RESETVAL                 (0x00000400U)
#define CSL_DSS_DISPC_VID3_FIR_FIRHINC_MAX                      (0x00001fffU)

#define CSL_DSS_DISPC_VID3_FIR_RESETVAL                         (0x04000400U)

/* VID3_PICTURE_SIZE */

#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEY_MASK           (0x0FFF0000U)
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEY_SHIFT          (16U)
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEY_MAX            (0x00000fffU)

#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEX_MASK           (0x000007FFU)
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEX_SHIFT          (0U)
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEX_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_MEMSIZEX_MAX            (0x000007ffU)

#define CSL_DSS_DISPC_VID3_PICTURE_SIZE_RESETVAL                (0x00000000U)

/* VID3_PIXEL_INC */

#define CSL_DSS_DISPC_VID3_PIXEL_INC_PIXELINC_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID3_PIXEL_INC_PIXELINC_SHIFT             (0U)
#define CSL_DSS_DISPC_VID3_PIXEL_INC_PIXELINC_RESETVAL          (0x00000001U)
#define CSL_DSS_DISPC_VID3_PIXEL_INC_PIXELINC_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_PIXEL_INC_RESETVAL                   (0x00000001U)

/* VID3_POSITION */

#define CSL_DSS_DISPC_VID3_POSITION_POSY_MASK                   (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_POSITION_POSY_SHIFT                  (16U)
#define CSL_DSS_DISPC_VID3_POSITION_POSY_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID3_POSITION_POSY_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID3_POSITION_POSX_MASK                   (0x000007FFU)
#define CSL_DSS_DISPC_VID3_POSITION_POSX_SHIFT                  (0U)
#define CSL_DSS_DISPC_VID3_POSITION_POSX_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_VID3_POSITION_POSX_MAX                    (0x000007ffU)

#define CSL_DSS_DISPC_VID3_POSITION_RESETVAL                    (0x00000000U)

/* VID3_PRELOAD */

#define CSL_DSS_DISPC_VID3_PRELOAD_PRELOAD_MASK                 (0x00000FFFU)
#define CSL_DSS_DISPC_VID3_PRELOAD_PRELOAD_SHIFT                (0U)
#define CSL_DSS_DISPC_VID3_PRELOAD_PRELOAD_RESETVAL             (0x00000100U)
#define CSL_DSS_DISPC_VID3_PRELOAD_PRELOAD_MAX                  (0x00000fffU)

#define CSL_DSS_DISPC_VID3_PRELOAD_RESETVAL                     (0x00000100U)

/* VID3_ROW_INC */

#define CSL_DSS_DISPC_VID3_ROW_INC_ROWINC_MASK                  (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID3_ROW_INC_ROWINC_SHIFT                 (0U)
#define CSL_DSS_DISPC_VID3_ROW_INC_ROWINC_RESETVAL              (0x00000001U)
#define CSL_DSS_DISPC_VID3_ROW_INC_ROWINC_MAX                   (0xffffffffU)

#define CSL_DSS_DISPC_VID3_ROW_INC_RESETVAL                     (0x00000001U)

/* VID3_SIZE */

#define CSL_DSS_DISPC_VID3_SIZE_SIZEY_MASK                      (0x0FFF0000U)
#define CSL_DSS_DISPC_VID3_SIZE_SIZEY_SHIFT                     (16U)
#define CSL_DSS_DISPC_VID3_SIZE_SIZEY_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_VID3_SIZE_SIZEY_MAX                       (0x00000fffU)

#define CSL_DSS_DISPC_VID3_SIZE_SIZEX_MASK                      (0x00000FFFU)
#define CSL_DSS_DISPC_VID3_SIZE_SIZEX_SHIFT                     (0U)
#define CSL_DSS_DISPC_VID3_SIZE_SIZEX_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_VID3_SIZE_SIZEX_MAX                       (0x00000fffU)

#define CSL_DSS_DISPC_VID3_SIZE_RESETVAL                        (0x00000000U)

/* DEFAULT_COLOR2 */

#define CSL_DSS_DISPC_DEFAULT_COLOR2_DEFAULTCOLOR_MASK          (0x00FFFFFFU)
#define CSL_DSS_DISPC_DEFAULT_COLOR2_DEFAULTCOLOR_SHIFT         (0U)
#define CSL_DSS_DISPC_DEFAULT_COLOR2_DEFAULTCOLOR_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_DEFAULT_COLOR2_DEFAULTCOLOR_MAX           (0x00ffffffU)

#define CSL_DSS_DISPC_DEFAULT_COLOR2_RESETVAL                   (0x00000000U)

/* TRANS_COLOR2 */

#define CSL_DSS_DISPC_TRANS_COLOR2_TRANSCOLORKEY_MASK           (0x00FFFFFFU)
#define CSL_DSS_DISPC_TRANS_COLOR2_TRANSCOLORKEY_SHIFT          (0U)
#define CSL_DSS_DISPC_TRANS_COLOR2_TRANSCOLORKEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_TRANS_COLOR2_TRANSCOLORKEY_MAX            (0x00ffffffU)

#define CSL_DSS_DISPC_TRANS_COLOR2_RESETVAL                     (0x00000000U)

/* CPR2_COEF_B */

#define CSL_DSS_DISPC_CPR2_COEF_B_BG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_B_BB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR2_COEF_B_BB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_B_BR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_B_BR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_B_RESETVAL                      (0x00000000U)

/* CPR2_COEF_G */

#define CSL_DSS_DISPC_CPR2_COEF_G_GG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_G_GB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR2_COEF_G_GB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_G_GR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_G_GR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_G_RESETVAL                      (0x00000000U)

/* CPR2_COEF_R */

#define CSL_DSS_DISPC_CPR2_COEF_R_RR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_R_RG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_R_RB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR2_COEF_R_RB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR2_COEF_R_RB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR2_COEF_R_RESETVAL                      (0x00000000U)

/* DATA2_CYCLE1 */

#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE1_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA2_CYCLE1_RESETVAL                     (0x00000000U)

/* DATA2_CYCLE2 */

#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE2_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA2_CYCLE2_RESETVAL                     (0x00000000U)

/* DATA2_CYCLE3 */

#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA2_CYCLE3_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA2_CYCLE3_RESETVAL                     (0x00000000U)

/* SIZE_LCD2 */

#define CSL_DSS_DISPC_SIZE_LCD2_LPP_MASK                        (0x0FFF0000U)
#define CSL_DSS_DISPC_SIZE_LCD2_LPP_SHIFT                       (16U)
#define CSL_DSS_DISPC_SIZE_LCD2_LPP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD2_LPP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_LCD2_PPL_MASK                        (0x00000FFFU)
#define CSL_DSS_DISPC_SIZE_LCD2_PPL_SHIFT                       (0U)
#define CSL_DSS_DISPC_SIZE_LCD2_PPL_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD2_PPL_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_LCD2_DELTA_LPP_MASK                  (0x0000C000U)
#define CSL_DSS_DISPC_SIZE_LCD2_DELTA_LPP_SHIFT                 (14U)
#define CSL_DSS_DISPC_SIZE_LCD2_DELTA_LPP_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD2_DELTA_LPP_SAME                  (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD2_DELTA_LPP_PLUSONE               (0x00000001U)
#define CSL_DSS_DISPC_SIZE_LCD2_DELTA_LPP_MINUSONE              (0x00000002U)

#define CSL_DSS_DISPC_SIZE_LCD2_RESETVAL                        (0x00000000U)

/* TIMING_H2 */

#define CSL_DSS_DISPC_TIMING_H2_HBP_MASK                        (0xFFF00000U)
#define CSL_DSS_DISPC_TIMING_H2_HBP_SHIFT                       (20U)
#define CSL_DSS_DISPC_TIMING_H2_HBP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H2_HBP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_H2_HSW_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_TIMING_H2_HSW_SHIFT                       (0U)
#define CSL_DSS_DISPC_TIMING_H2_HSW_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H2_HSW_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_TIMING_H2_HFP_MASK                        (0x000FFF00U)
#define CSL_DSS_DISPC_TIMING_H2_HFP_SHIFT                       (8U)
#define CSL_DSS_DISPC_TIMING_H2_HFP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H2_HFP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_H2_RESETVAL                        (0x00000000U)

/* TIMING_V2 */

#define CSL_DSS_DISPC_TIMING_V2_VSW_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_TIMING_V2_VSW_SHIFT                       (0U)
#define CSL_DSS_DISPC_TIMING_V2_VSW_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V2_VSW_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_TIMING_V2_VFP_MASK                        (0x000FFF00U)
#define CSL_DSS_DISPC_TIMING_V2_VFP_SHIFT                       (8U)
#define CSL_DSS_DISPC_TIMING_V2_VFP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V2_VFP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_V2_VBP_MASK                        (0xFFF00000U)
#define CSL_DSS_DISPC_TIMING_V2_VBP_SHIFT                       (20U)
#define CSL_DSS_DISPC_TIMING_V2_VBP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V2_VBP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_V2_RESETVAL                        (0x00000000U)

/* POL_FREQ2 */

#define CSL_DSS_DISPC_POL_FREQ2_RF_MASK                         (0x00010000U)
#define CSL_DSS_DISPC_POL_FREQ2_RF_SHIFT                        (16U)
#define CSL_DSS_DISPC_POL_FREQ2_RF_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_RF_DRIEDPCK                     (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ2_RF_DFEDPCK                      (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ2_IHS_MASK                        (0x00002000U)
#define CSL_DSS_DISPC_POL_FREQ2_IHS_SHIFT                       (13U)
#define CSL_DSS_DISPC_POL_FREQ2_IHS_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_IHS_LCKPINAL                    (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ2_IHS_LCKPINAH                    (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ2_ACB_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_POL_FREQ2_ACB_SHIFT                       (0U)
#define CSL_DSS_DISPC_POL_FREQ2_ACB_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_ACB_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_POL_FREQ2_IVS_MASK                        (0x00001000U)
#define CSL_DSS_DISPC_POL_FREQ2_IVS_SHIFT                       (12U)
#define CSL_DSS_DISPC_POL_FREQ2_IVS_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_IVS_FCKPINAH                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_IVS_FCKPINAL                    (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ2_IEO_MASK                        (0x00008000U)
#define CSL_DSS_DISPC_POL_FREQ2_IEO_SHIFT                       (15U)
#define CSL_DSS_DISPC_POL_FREQ2_IEO_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_IEO_ACBALOW                     (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ2_IEO_ACBAHIGH                    (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ2_IPC_MASK                        (0x00004000U)
#define CSL_DSS_DISPC_POL_FREQ2_IPC_SHIFT                       (14U)
#define CSL_DSS_DISPC_POL_FREQ2_IPC_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_IPC_DRPCK                       (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_IPC_DFPCK                       (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ2_ONOFF_MASK                      (0x00020000U)
#define CSL_DSS_DISPC_POL_FREQ2_ONOFF_SHIFT                     (17U)
#define CSL_DSS_DISPC_POL_FREQ2_ONOFF_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_ONOFF_DBIT16                    (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ2_ONOFF_DOPEDPCK                  (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ2_ACBI_MASK                       (0x00000F00U)
#define CSL_DSS_DISPC_POL_FREQ2_ACBI_SHIFT                      (8U)
#define CSL_DSS_DISPC_POL_FREQ2_ACBI_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_ACBI_MAX                        (0x0000000fU)

#define CSL_DSS_DISPC_POL_FREQ2_ALIGN_MASK                      (0x00040000U)
#define CSL_DSS_DISPC_POL_FREQ2_ALIGN_SHIFT                     (18U)
#define CSL_DSS_DISPC_POL_FREQ2_ALIGN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_ALIGN_NOTALIGNED                (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ2_ALIGN_ALIGNED                   (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ2_RESETVAL                        (0x00000000U)

/* DIVISOR2 */

#define CSL_DSS_DISPC_DIVISOR2_LCD_MASK                         (0x00FF0000U)
#define CSL_DSS_DISPC_DIVISOR2_LCD_SHIFT                        (16U)
#define CSL_DSS_DISPC_DIVISOR2_LCD_RESETVAL                     (0x00000004U)
#define CSL_DSS_DISPC_DIVISOR2_LCD_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR2_PCD_MASK                         (0x000000FFU)
#define CSL_DSS_DISPC_DIVISOR2_PCD_SHIFT                        (0U)
#define CSL_DSS_DISPC_DIVISOR2_PCD_RESETVAL                     (0x00000001U)
#define CSL_DSS_DISPC_DIVISOR2_PCD_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR2_RESETVAL                         (0x00040001U)

/* WB_ACCU */

#define CSL_DSS_DISPC_WB_ACCU_HORIZONTALACCU_MASK               (0x000007FFU)
#define CSL_DSS_DISPC_WB_ACCU_HORIZONTALACCU_SHIFT              (0U)
#define CSL_DSS_DISPC_WB_ACCU_HORIZONTALACCU_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_ACCU_HORIZONTALACCU_MAX                (0x000007ffU)

#define CSL_DSS_DISPC_WB_ACCU_VERTICALACCU_MASK                 (0x07FF0000U)
#define CSL_DSS_DISPC_WB_ACCU_VERTICALACCU_SHIFT                (16U)
#define CSL_DSS_DISPC_WB_ACCU_VERTICALACCU_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_ACCU_VERTICALACCU_MAX                  (0x000007ffU)

#define CSL_DSS_DISPC_WB_ACCU_RESETVAL                          (0x00000000U)

/* WB_BA */

#define CSL_DSS_DISPC_WB_BA_BA_MASK                             (0xFFFFFFFFU)
#define CSL_DSS_DISPC_WB_BA_BA_SHIFT                            (0U)
#define CSL_DSS_DISPC_WB_BA_BA_RESETVAL                         (0x00000000U)
#define CSL_DSS_DISPC_WB_BA_BA_MAX                              (0xffffffffU)

#define CSL_DSS_DISPC_WB_BA_RESETVAL                            (0x00000000U)

/* WB_FIR_COEF_H */

#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC2_MASK                 (0x00FF0000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC2_SHIFT                (16U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC2_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC2_MAX                  (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC1_MASK                 (0x0000FF00U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC1_SHIFT                (8U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC1_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC1_MAX                  (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC0_MASK                 (0x000000FFU)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC0_SHIFT                (0U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC0_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC0_MAX                  (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC3_MASK                 (0xFF000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC3_SHIFT                (24U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC3_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H_FIRHC3_MAX                  (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H_RESETVAL                    (0x00000000U)

/* WB_FIR_COEF_HV */

#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC0_MASK                (0x0000FF00U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC0_SHIFT               (8U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC0_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC0_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRHC4_MASK                (0x000000FFU)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRHC4_SHIFT               (0U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRHC4_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRHC4_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC2_MASK                (0xFF000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC2_SHIFT               (24U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC2_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC2_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC1_MASK                (0x00FF0000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC1_SHIFT               (16U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC1_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV_FIRVC1_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV_RESETVAL                   (0x00000000U)

/* WB_FIR_COEF_V */

#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC22_MASK                (0x0000FF00U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC22_SHIFT               (8U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC22_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC22_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC00_MASK                (0x000000FFU)
#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC00_SHIFT               (0U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC00_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V_FIRVC00_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_V_RESETVAL                    (0x00000000U)

/* WB_ATTRS */

#define CSL_DSS_DISPC_WB_ATTRS_EN_MASK                          (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_EN_SHIFT                         (0U)
#define CSL_DSS_DISPC_WB_ATTRS_EN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_EN_WBDIS                         (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_EN_WBENB                         (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_MASK                   (0x0000C000U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_SHIFT                  (14U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_RESETVAL               (0x00000002U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_BURST2X128B            (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_BURST4X128B            (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_BURST8X128B            (0x00000002U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTSIZE_RES                    (0x00000003U)

#define CSL_DSS_DISPC_WB_ATTRS_COLORCONVEN_MASK                 (0x00000200U)
#define CSL_DSS_DISPC_WB_ATTRS_COLORCONVEN_SHIFT                (9U)
#define CSL_DSS_DISPC_WB_ATTRS_COLORCONVEN_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_COLORCONVEN_COLSPCDIS            (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_COLORCONVEN_COLSPCENB            (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_TRUNCATIONEN_MASK                (0x00000400U)
#define CSL_DSS_DISPC_WB_ATTRS_TRUNCATIONEN_SHIFT               (10U)
#define CSL_DSS_DISPC_WB_ATTRS_TRUNCATIONEN_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_TRUNCATIONEN_WBTRUNCENB          (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_TRUNCATIONEN_WBTRUNCDIS          (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_VERTICALTAPS_MASK                (0x00200000U)
#define CSL_DSS_DISPC_WB_ATTRS_VERTICALTAPS_SHIFT               (21U)
#define CSL_DSS_DISPC_WB_ATTRS_VERTICALTAPS_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_VERTICALTAPS_TAPS5               (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_VERTICALTAPS_TAPS3               (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_FMT_MASK                         (0x0000001EU)
#define CSL_DSS_DISPC_WB_ATTRS_FMT_SHIFT                        (1U)
#define CSL_DSS_DISPC_WB_ATTRS_FMT_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_FMT_MAX                          (0x0000000fU)

#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_MASK                   (0x00070000U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_SHIFT                  (16U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_LCD2                   (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_LCD1                   (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_TV                     (0x00000002U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_GFX                    (0x00000003U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_VID1                   (0x00000004U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_VID2                   (0x00000005U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_VID3                   (0x00000006U)
#define CSL_DSS_DISPC_WB_ATTRS_CHANNELIN_LCD3                   (0x00000007U)

#define CSL_DSS_DISPC_WB_ATTRS_ARBITRATION_MASK                 (0x00800000U)
#define CSL_DSS_DISPC_WB_ATTRS_ARBITRATION_SHIFT                (23U)
#define CSL_DSS_DISPC_WB_ATTRS_ARBITRATION_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_ARBITRATION_HIGHPRIO             (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_ARBITRATION_NORMALPRIO           (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_BURSTTYPE_MASK                   (0x00000100U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTTYPE_SHIFT                  (8U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTTYPE_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTTYPE__1D_BURST              (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_BURSTTYPE__2D_BURST              (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_FULLRANGE_MASK                   (0x00000800U)
#define CSL_DSS_DISPC_WB_ATTRS_FULLRANGE_SHIFT                  (11U)
#define CSL_DSS_DISPC_WB_ATTRS_FULLRANGE_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_FULLRANGE_FULLRANGE              (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_FULLRANGE_LIMRANGE               (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_MASK                    (0x00000060U)
#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_SHIFT                   (5U)
#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_HVRESIZE                (0x00000003U)
#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_VRESIZE                 (0x00000002U)
#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_HRESIZE                 (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_RESIZEEN_RESIZEPROC              (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_HRESIZECONF_MASK                 (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_HRESIZECONF_SHIFT                (7U)
#define CSL_DSS_DISPC_WB_ATTRS_HRESIZECONF_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_HRESIZECONF_MAX                  (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_MASK                    (0x00003000U)
#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_SHIFT                   (12U)
#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_ROT270                  (0x00000003U)
#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_ROT180                  (0x00000002U)
#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_ROT90                   (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_ROTATION_NOROT                   (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_ALPHAEN_MASK                     (0x00000080U)
#define CSL_DSS_DISPC_WB_ATTRS_ALPHAEN_SHIFT                    (7U)
#define CSL_DSS_DISPC_WB_ATTRS_ALPHAEN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_ALPHAEN_DISABLE                  (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_ALPHAEN_ENABLE                   (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_MASK                 (0x07000000U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_SHIFT                (24U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ALL                  (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1                (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1_2              (0x00000002U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1_3              (0x00000003U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1_4              (0x00000004U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1_5              (0x00000005U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1_6              (0x00000006U)
#define CSL_DSS_DISPC_WB_ATTRS_CAPTUREMODE_ONLY1_7              (0x00000007U)

#define CSL_DSS_DISPC_WB_ATTRS_IDLESIZE_MASK                    (0x08000000U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLESIZE_SHIFT                   (27U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLESIZE_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLESIZE_IDLEBURST               (0x00000001U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLESIZE_IDLESINGLE              (0x00000000U)

#define CSL_DSS_DISPC_WB_ATTRS_IDLENUMBER_MASK                  (0xF0000000U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLENUMBER_SHIFT                 (28U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLENUMBER_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_IDLENUMBER_MAX                   (0x0000000fU)

#define CSL_DSS_DISPC_WB_ATTRS_DOUBLESTRIDE_MASK                (0x00400000U)
#define CSL_DSS_DISPC_WB_ATTRS_DOUBLESTRIDE_SHIFT               (22U)
#define CSL_DSS_DISPC_WB_ATTRS_DOUBLESTRIDE_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_DOUBLESTRIDE_INITIAL             (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_DOUBLESTRIDE_DOUBLE              (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_WRITEBACKMODE_MASK               (0x00080000U)
#define CSL_DSS_DISPC_WB_ATTRS_WRITEBACKMODE_SHIFT              (19U)
#define CSL_DSS_DISPC_WB_ATTRS_WRITEBACKMODE_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_WRITEBACKMODE_CAPTURE            (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_WRITEBACKMODE_MEM2MEM            (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_FORCE1DTILEDMODE_MASK            (0x00100000U)
#define CSL_DSS_DISPC_WB_ATTRS_FORCE1DTILEDMODE_SHIFT           (20U)
#define CSL_DSS_DISPC_WB_ATTRS_FORCE1DTILEDMODE_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS2DACCESS  (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS_FORCE1DTILEDMODE_TILEDREGIONS1DACCESS  (0x00000001U)

#define CSL_DSS_DISPC_WB_ATTRS_RESETVAL                         (0x00008000U)

/* WB_CONV_COEF0 */

#define CSL_DSS_DISPC_WB_CONV_COEF0_YR_MASK                     (0x000007FFU)
#define CSL_DSS_DISPC_WB_CONV_COEF0_YR_SHIFT                    (0U)
#define CSL_DSS_DISPC_WB_CONV_COEF0_YR_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF0_YR_MAX                      (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF0_YG_MASK                     (0x07FF0000U)
#define CSL_DSS_DISPC_WB_CONV_COEF0_YG_SHIFT                    (16U)
#define CSL_DSS_DISPC_WB_CONV_COEF0_YG_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF0_YG_MAX                      (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF0_RESETVAL                    (0x00000000U)

/* WB_CONV_COEF1 */

#define CSL_DSS_DISPC_WB_CONV_COEF1_YB_MASK                     (0x000007FFU)
#define CSL_DSS_DISPC_WB_CONV_COEF1_YB_SHIFT                    (0U)
#define CSL_DSS_DISPC_WB_CONV_COEF1_YB_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF1_YB_MAX                      (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF1_CRR_MASK                    (0x07FF0000U)
#define CSL_DSS_DISPC_WB_CONV_COEF1_CRR_SHIFT                   (16U)
#define CSL_DSS_DISPC_WB_CONV_COEF1_CRR_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF1_CRR_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF1_RESETVAL                    (0x00000000U)

/* WB_CONV_COEF2 */

#define CSL_DSS_DISPC_WB_CONV_COEF2_CRG_MASK                    (0x000007FFU)
#define CSL_DSS_DISPC_WB_CONV_COEF2_CRG_SHIFT                   (0U)
#define CSL_DSS_DISPC_WB_CONV_COEF2_CRG_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF2_CRG_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF2_CRB_MASK                    (0x07FF0000U)
#define CSL_DSS_DISPC_WB_CONV_COEF2_CRB_SHIFT                   (16U)
#define CSL_DSS_DISPC_WB_CONV_COEF2_CRB_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF2_CRB_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF2_RESETVAL                    (0x00000000U)

/* WB_CONV_COEF3 */

#define CSL_DSS_DISPC_WB_CONV_COEF3_CBR_MASK                    (0x000007FFU)
#define CSL_DSS_DISPC_WB_CONV_COEF3_CBR_SHIFT                   (0U)
#define CSL_DSS_DISPC_WB_CONV_COEF3_CBR_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF3_CBR_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF3_CBG_MASK                    (0x07FF0000U)
#define CSL_DSS_DISPC_WB_CONV_COEF3_CBG_SHIFT                   (16U)
#define CSL_DSS_DISPC_WB_CONV_COEF3_CBG_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF3_CBG_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF3_RESETVAL                    (0x00000000U)

/* WB_CONV_COEF4 */

#define CSL_DSS_DISPC_WB_CONV_COEF4_CBB_MASK                    (0x000007FFU)
#define CSL_DSS_DISPC_WB_CONV_COEF4_CBB_SHIFT                   (0U)
#define CSL_DSS_DISPC_WB_CONV_COEF4_CBB_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_WB_CONV_COEF4_CBB_MAX                     (0x000007ffU)

#define CSL_DSS_DISPC_WB_CONV_COEF4_RESETVAL                    (0x00000000U)

/* WB_BUF_SIZE_STS */

#define CSL_DSS_DISPC_WB_BUF_SIZE_STS_BUFSIZE_MASK              (0x0000FFFFU)
#define CSL_DSS_DISPC_WB_BUF_SIZE_STS_BUFSIZE_SHIFT             (0U)
#define CSL_DSS_DISPC_WB_BUF_SIZE_STS_BUFSIZE_RESETVAL          (0x00000800U)
#define CSL_DSS_DISPC_WB_BUF_SIZE_STS_BUFSIZE_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_WB_BUF_SIZE_STS_RESETVAL                  (0x00000800U)

/* WB_BUF_THR */

#define CSL_DSS_DISPC_WB_BUF_THR_BUFHIGHTHR_MASK                (0xFFFF0000U)
#define CSL_DSS_DISPC_WB_BUF_THR_BUFHIGHTHR_SHIFT               (16U)
#define CSL_DSS_DISPC_WB_BUF_THR_BUFHIGHTHR_RESETVAL            (0x000007ffU)
#define CSL_DSS_DISPC_WB_BUF_THR_BUFHIGHTHR_MAX                 (0x0000ffffU)

#define CSL_DSS_DISPC_WB_BUF_THR_BUFLOWTHR_MASK                 (0x0000FFFFU)
#define CSL_DSS_DISPC_WB_BUF_THR_BUFLOWTHR_SHIFT                (0U)
#define CSL_DSS_DISPC_WB_BUF_THR_BUFLOWTHR_RESETVAL             (0x000007f8U)
#define CSL_DSS_DISPC_WB_BUF_THR_BUFLOWTHR_MAX                  (0x0000ffffU)

#define CSL_DSS_DISPC_WB_BUF_THR_RESETVAL                       (0x07ff07f8U)

/* WB_FIR */

#define CSL_DSS_DISPC_WB_FIR_FIRVINC_MASK                       (0x1FFF0000U)
#define CSL_DSS_DISPC_WB_FIR_FIRVINC_SHIFT                      (16U)
#define CSL_DSS_DISPC_WB_FIR_FIRVINC_RESETVAL                   (0x00000400U)
#define CSL_DSS_DISPC_WB_FIR_FIRVINC_MAX                        (0x00001fffU)

#define CSL_DSS_DISPC_WB_FIR_FIRHINC_MASK                       (0x00001FFFU)
#define CSL_DSS_DISPC_WB_FIR_FIRHINC_SHIFT                      (0U)
#define CSL_DSS_DISPC_WB_FIR_FIRHINC_RESETVAL                   (0x00000400U)
#define CSL_DSS_DISPC_WB_FIR_FIRHINC_MAX                        (0x00001fffU)

#define CSL_DSS_DISPC_WB_FIR_RESETVAL                           (0x04000400U)

/* WB_PICTURE_SIZE */

#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY_MASK             (0x0FFF0000U)
#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY_SHIFT            (16U)
#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEY_MAX              (0x00000fffU)

#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX_MASK             (0x000007FFU)
#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX_SHIFT            (0U)
#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_WB_PICTURE_SIZE_MEMSIZEX_MAX              (0x000007ffU)

#define CSL_DSS_DISPC_WB_PICTURE_SIZE_RESETVAL                  (0x00000000U)

/* WB_PIXEL_INC */

#define CSL_DSS_DISPC_WB_PIXEL_INC_PIXELINC_MASK                (0x000000FFU)
#define CSL_DSS_DISPC_WB_PIXEL_INC_PIXELINC_SHIFT               (0U)
#define CSL_DSS_DISPC_WB_PIXEL_INC_PIXELINC_RESETVAL            (0x00000001U)
#define CSL_DSS_DISPC_WB_PIXEL_INC_PIXELINC_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_PIXEL_INC_RESETVAL                     (0x00000001U)

/* WB_ROW_INC */

#define CSL_DSS_DISPC_WB_ROW_INC_ROWINC_MASK                    (0xFFFFFFFFU)
#define CSL_DSS_DISPC_WB_ROW_INC_ROWINC_SHIFT                   (0U)
#define CSL_DSS_DISPC_WB_ROW_INC_ROWINC_RESETVAL                (0x00000001U)
#define CSL_DSS_DISPC_WB_ROW_INC_ROWINC_MAX                     (0xffffffffU)

#define CSL_DSS_DISPC_WB_ROW_INC_RESETVAL                       (0x00000001U)

/* WB_SIZE */

#define CSL_DSS_DISPC_WB_SIZE_SIZEY_MASK                        (0x0FFF0000U)
#define CSL_DSS_DISPC_WB_SIZE_SIZEY_SHIFT                       (16U)
#define CSL_DSS_DISPC_WB_SIZE_SIZEY_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_WB_SIZE_SIZEY_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_WB_SIZE_SIZEX_MASK                        (0x000007FFU)
#define CSL_DSS_DISPC_WB_SIZE_SIZEX_SHIFT                       (0U)
#define CSL_DSS_DISPC_WB_SIZE_SIZEX_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_WB_SIZE_SIZEX_MAX                         (0x000007ffU)

#define CSL_DSS_DISPC_WB_SIZE_RESETVAL                          (0x00000000U)

/* VID1_BA_UV */

#define CSL_DSS_DISPC_VID1_BA_UV_BA_MASK                        (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID1_BA_UV_BA_SHIFT                       (0U)
#define CSL_DSS_DISPC_VID1_BA_UV_BA_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_VID1_BA_UV_BA_MAX                         (0xffffffffU)

#define CSL_DSS_DISPC_VID1_BA_UV_RESETVAL                       (0x00000000U)

/* VID2_BA_UV */

#define CSL_DSS_DISPC_VID2_BA_UV_BA_MASK                        (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID2_BA_UV_BA_SHIFT                       (0U)
#define CSL_DSS_DISPC_VID2_BA_UV_BA_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_VID2_BA_UV_BA_MAX                         (0xffffffffU)

#define CSL_DSS_DISPC_VID2_BA_UV_RESETVAL                       (0x00000000U)

/* VID3_BA_UV */

#define CSL_DSS_DISPC_VID3_BA_UV_BA_MASK                        (0xFFFFFFFFU)
#define CSL_DSS_DISPC_VID3_BA_UV_BA_SHIFT                       (0U)
#define CSL_DSS_DISPC_VID3_BA_UV_BA_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_VID3_BA_UV_BA_MAX                         (0xffffffffU)

#define CSL_DSS_DISPC_VID3_BA_UV_RESETVAL                       (0x00000000U)

/* WB_BA_UV */

#define CSL_DSS_DISPC_WB_BA_UV_BA_MASK                          (0xFFFFFFFFU)
#define CSL_DSS_DISPC_WB_BA_UV_BA_SHIFT                         (0U)
#define CSL_DSS_DISPC_WB_BA_UV_BA_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_WB_BA_UV_BA_MAX                           (0xffffffffU)

#define CSL_DSS_DISPC_WB_BA_UV_RESETVAL                         (0x00000000U)

/* CONFIG2 */

#define CSL_DSS_DISPC_CONFIG2_PIXELDATAGATED_MASK               (0x00000010U)
#define CSL_DSS_DISPC_CONFIG2_PIXELDATAGATED_SHIFT              (4U)
#define CSL_DSS_DISPC_CONFIG2_PIXELDATAGATED_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_PIXELDATAGATED_PDGDIS             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_PIXELDATAGATED_PDGENB             (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_HSYNCGATED_MASK                   (0x00000040U)
#define CSL_DSS_DISPC_CONFIG2_HSYNCGATED_SHIFT                  (6U)
#define CSL_DSS_DISPC_CONFIG2_HSYNCGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_HSYNCGATED_HGDIS                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_HSYNCGATED_HGENB                  (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_ACBIASGATED_MASK                  (0x00000100U)
#define CSL_DSS_DISPC_CONFIG2_ACBIASGATED_SHIFT                 (8U)
#define CSL_DSS_DISPC_CONFIG2_ACBIASGATED_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_ACBIASGATED_ACBGDIS               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_ACBIASGATED_ACBGENB               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_PIXELCLOCKGATED_MASK              (0x00000020U)
#define CSL_DSS_DISPC_CONFIG2_PIXELCLOCKGATED_SHIFT             (5U)
#define CSL_DSS_DISPC_CONFIG2_PIXELCLOCKGATED_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_PIXELCLOCKGATED_PCGDIS            (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_PIXELCLOCKGATED_PCGENB            (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_VSYNCGATED_MASK                   (0x00000080U)
#define CSL_DSS_DISPC_CONFIG2_VSYNCGATED_SHIFT                  (7U)
#define CSL_DSS_DISPC_CONFIG2_VSYNCGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_VSYNCGATED_VGDIS                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_VSYNCGATED_VGENB                  (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_PIXELGATED_MASK                   (0x00000001U)
#define CSL_DSS_DISPC_CONFIG2_PIXELGATED_SHIFT                  (0U)
#define CSL_DSS_DISPC_CONFIG2_PIXELGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_PIXELGATED_PCLKTOGA               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_PIXELGATED_PCLKTOGV               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_BUFFERHANDCHECK_MASK              (0x00010000U)
#define CSL_DSS_DISPC_CONFIG2_BUFFERHANDCHECK_SHIFT             (16U)
#define CSL_DSS_DISPC_CONFIG2_BUFFERHANDCHECK_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_BUFFERHANDCHECK_HANDCHECKDIS      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_BUFFERHANDCHECK_HANDCHECKENB      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_TCKLCDEN_MASK                     (0x00000400U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDEN_SHIFT                    (10U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDEN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDEN_DISTCK                   (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDEN_ENBTCK                   (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_TCKLCDSELECTION_MASK              (0x00000800U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDSELECTION_SHIFT             (11U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDSELECTION_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDSELECTION_GDTK              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_TCKLCDSELECTION_VSTK              (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_BT656EN_MASK                      (0x00100000U)
#define CSL_DSS_DISPC_CONFIG2_BT656EN_SHIFT                     (20U)
#define CSL_DSS_DISPC_CONFIG2_BT656EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_BT656EN_DISABLE                   (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_BT656EN_ENABLE                    (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_BT1120EN_MASK                     (0x00200000U)
#define CSL_DSS_DISPC_CONFIG2_BT1120EN_SHIFT                    (21U)
#define CSL_DSS_DISPC_CONFIG2_BT1120EN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_BT1120EN_DISABLE                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_BT1120EN_ENABLE                   (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_OUTPUTMODEEN_MASK                 (0x00400000U)
#define CSL_DSS_DISPC_CONFIG2_OUTPUTMODEEN_SHIFT                (22U)
#define CSL_DSS_DISPC_CONFIG2_OUTPUTMODEEN_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_OUTPUTMODEEN_DISABLE              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_OUTPUTMODEEN_ENABLE               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_CPR_MASK                          (0x00008000U)
#define CSL_DSS_DISPC_CONFIG2_CPR_SHIFT                         (15U)
#define CSL_DSS_DISPC_CONFIG2_CPR_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_CPR_CPRDIS                        (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_CPR_CPRENB                        (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_FIDFIRST_MASK                     (0x00800000U)
#define CSL_DSS_DISPC_CONFIG2_FIDFIRST_SHIFT                    (23U)
#define CSL_DSS_DISPC_CONFIG2_FIDFIRST_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_FIDFIRST_EVEN                     (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_FIDFIRST_ODD                      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_COLORCONVEN_MASK                  (0x01000000U)
#define CSL_DSS_DISPC_CONFIG2_COLORCONVEN_SHIFT                 (24U)
#define CSL_DSS_DISPC_CONFIG2_COLORCONVEN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_COLORCONVEN_COLSPCDIS             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_COLORCONVEN_COLSPCENB             (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_FULLRANGE_MASK                    (0x02000000U)
#define CSL_DSS_DISPC_CONFIG2_FULLRANGE_SHIFT                   (25U)
#define CSL_DSS_DISPC_CONFIG2_FULLRANGE_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_FULLRANGE_LIMRANGE                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_FULLRANGE_FULLRANGE               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG2_SLCDINTERLEAVE_MASK               (0x0C000000U)
#define CSL_DSS_DISPC_CONFIG2_SLCDINTERLEAVE_SHIFT              (26U)
#define CSL_DSS_DISPC_CONFIG2_SLCDINTERLEAVE_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG2_SLCDINTERLEAVE_MAX                (0x00000003U)

#define CSL_DSS_DISPC_CONFIG2_RESETVAL                          (0x00000000U)

/* VID1_ATTRS2 */

#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_Y_MASK              (0x0000000EU)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_Y_SHIFT             (1U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_Y_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_Y_MAX               (0x00000007U)

#define CSL_DSS_DISPC_VID1_ATTRS2_VC1EN_MASK                    (0x00000001U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1EN_SHIFT                   (0U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1EN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1EN_VC1DIS                  (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1EN_VC1ENB                  (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_CBCR_MASK           (0x00000070U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_CBCR_SHIFT          (4U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_CBCR_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_VC1_RANGE_CBCR_MAX            (0x00000007U)

#define CSL_DSS_DISPC_VID1_ATTRS2_YUVCHROMARESAMPLING_MASK      (0x00000100U)
#define CSL_DSS_DISPC_VID1_ATTRS2_YUVCHROMARESAMPLING_SHIFT     (8U)
#define CSL_DSS_DISPC_VID1_ATTRS2_YUVCHROMARESAMPLING_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_YUVCHROMARESAMPLING_AVERAGE   (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_YUVCHROMARESAMPLING_FILTER    (0x00000001U)

#define CSL_DSS_DISPC_VID1_ATTRS2_SUBSAMPLINGPATTERN_MASK       (0x00000E00U)
#define CSL_DSS_DISPC_VID1_ATTRS2_SUBSAMPLINGPATTERN_SHIFT      (9U)
#define CSL_DSS_DISPC_VID1_ATTRS2_SUBSAMPLINGPATTERN_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_VID1_ATTRS2_SUBSAMPLINGPATTERN_MAX        (0x00000007U)

#define CSL_DSS_DISPC_VID1_ATTRS2_RESETVAL                      (0x00000000U)

/* VID2_ATTRS2 */

#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_Y_MASK              (0x0000000EU)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_Y_SHIFT             (1U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_Y_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_Y_MAX               (0x00000007U)

#define CSL_DSS_DISPC_VID2_ATTRS2_VC1EN_MASK                    (0x00000001U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1EN_SHIFT                   (0U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1EN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1EN_VC1DIS                  (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1EN_VC1ENB                  (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_CBCR_MASK           (0x00000070U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_CBCR_SHIFT          (4U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_CBCR_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_VC1_RANGE_CBCR_MAX            (0x00000007U)

#define CSL_DSS_DISPC_VID2_ATTRS2_YUVCHROMARESAMPLING_MASK      (0x00000100U)
#define CSL_DSS_DISPC_VID2_ATTRS2_YUVCHROMARESAMPLING_SHIFT     (8U)
#define CSL_DSS_DISPC_VID2_ATTRS2_YUVCHROMARESAMPLING_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_YUVCHROMARESAMPLING_AVERAGE   (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_YUVCHROMARESAMPLING_FILTER    (0x00000001U)

#define CSL_DSS_DISPC_VID2_ATTRS2_SUBSAMPLINGPATTERN_MASK       (0x00000E00U)
#define CSL_DSS_DISPC_VID2_ATTRS2_SUBSAMPLINGPATTERN_SHIFT      (9U)
#define CSL_DSS_DISPC_VID2_ATTRS2_SUBSAMPLINGPATTERN_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_VID2_ATTRS2_SUBSAMPLINGPATTERN_MAX        (0x00000007U)

#define CSL_DSS_DISPC_VID2_ATTRS2_RESETVAL                      (0x00000000U)

/* VID3_ATTRS2 */

#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_Y_MASK              (0x0000000EU)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_Y_SHIFT             (1U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_Y_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_Y_MAX               (0x00000007U)

#define CSL_DSS_DISPC_VID3_ATTRS2_VC1EN_MASK                    (0x00000001U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1EN_SHIFT                   (0U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1EN_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1EN_VC1DIS                  (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1EN_VC1ENB                  (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_CBCR_MASK           (0x00000070U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_CBCR_SHIFT          (4U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_CBCR_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_VC1_RANGE_CBCR_MAX            (0x00000007U)

#define CSL_DSS_DISPC_VID3_ATTRS2_YUVCHROMARESAMPLING_MASK      (0x00000100U)
#define CSL_DSS_DISPC_VID3_ATTRS2_YUVCHROMARESAMPLING_SHIFT     (8U)
#define CSL_DSS_DISPC_VID3_ATTRS2_YUVCHROMARESAMPLING_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_YUVCHROMARESAMPLING_AVERAGE   (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_YUVCHROMARESAMPLING_FILTER    (0x00000001U)

#define CSL_DSS_DISPC_VID3_ATTRS2_SUBSAMPLINGPATTERN_MASK       (0x00000E00U)
#define CSL_DSS_DISPC_VID3_ATTRS2_SUBSAMPLINGPATTERN_SHIFT      (9U)
#define CSL_DSS_DISPC_VID3_ATTRS2_SUBSAMPLINGPATTERN_RESETVAL   (0x00000000U)
#define CSL_DSS_DISPC_VID3_ATTRS2_SUBSAMPLINGPATTERN_MAX        (0x00000007U)

#define CSL_DSS_DISPC_VID3_ATTRS2_RESETVAL                      (0x00000000U)

/* GAMMA_TBL0 */

#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_R_MASK                   (0x00FF0000U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_R_SHIFT                  (16U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_R_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_R_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL0_IDX_MASK                       (0xFF000000U)
#define CSL_DSS_DISPC_GAMMA_TBL0_IDX_SHIFT                      (24U)
#define CSL_DSS_DISPC_GAMMA_TBL0_IDX_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL0_IDX_MAX                        (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_G_MASK                   (0x0000FF00U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_G_SHIFT                  (8U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_G_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_G_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_B_MASK                   (0x000000FFU)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_B_SHIFT                  (0U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_B_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL0_VALUE_B_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL0_RESETVAL                       (0x00000000U)

/* GAMMA_TBL1 */

#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_R_MASK                   (0x00FF0000U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_R_SHIFT                  (16U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_R_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_R_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL1_IDX_MASK                       (0xFF000000U)
#define CSL_DSS_DISPC_GAMMA_TBL1_IDX_SHIFT                      (24U)
#define CSL_DSS_DISPC_GAMMA_TBL1_IDX_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL1_IDX_MAX                        (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_G_MASK                   (0x0000FF00U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_G_SHIFT                  (8U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_G_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_G_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_B_MASK                   (0x000000FFU)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_B_SHIFT                  (0U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_B_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL1_VALUE_B_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL1_RESETVAL                       (0x00000000U)

/* GAMMA_TBL2 */

#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_R_MASK                   (0x3FF00000U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_R_SHIFT                  (20U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_R_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_R_MAX                    (0x000003ffU)

#define CSL_DSS_DISPC_GAMMA_TBL2_IDX_MASK                       (0x80000000U)
#define CSL_DSS_DISPC_GAMMA_TBL2_IDX_SHIFT                      (31U)
#define CSL_DSS_DISPC_GAMMA_TBL2_IDX_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL2_IDX_MAX                        (0x00000001U)

#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_G_MASK                   (0x000FFC00U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_G_SHIFT                  (10U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_G_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_G_MAX                    (0x000003ffU)

#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_B_MASK                   (0x000003FFU)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_B_SHIFT                  (0U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_B_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL2_VALUE_B_MAX                    (0x000003ffU)

#define CSL_DSS_DISPC_GAMMA_TBL2_RESETVAL                       (0x00000000U)

/* VID1_FIR2 */

#define CSL_DSS_DISPC_VID1_FIR2_FIRVINC_MASK                    (0x1FFF0000U)
#define CSL_DSS_DISPC_VID1_FIR2_FIRVINC_SHIFT                   (16U)
#define CSL_DSS_DISPC_VID1_FIR2_FIRVINC_RESETVAL                (0x00000400U)
#define CSL_DSS_DISPC_VID1_FIR2_FIRVINC_MAX                     (0x00001fffU)

#define CSL_DSS_DISPC_VID1_FIR2_FIRHINC_MASK                    (0x00001FFFU)
#define CSL_DSS_DISPC_VID1_FIR2_FIRHINC_SHIFT                   (0U)
#define CSL_DSS_DISPC_VID1_FIR2_FIRHINC_RESETVAL                (0x00000400U)
#define CSL_DSS_DISPC_VID1_FIR2_FIRHINC_MAX                     (0x00001fffU)

#define CSL_DSS_DISPC_VID1_FIR2_RESETVAL                        (0x04000400U)

/* VID1_ACCU2 */

#define CSL_DSS_DISPC_VID1_ACCU2_HORIZONTALACCU_MASK            (0x000007FFU)
#define CSL_DSS_DISPC_VID1_ACCU2_HORIZONTALACCU_SHIFT           (0U)
#define CSL_DSS_DISPC_VID1_ACCU2_HORIZONTALACCU_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_VID1_ACCU2_HORIZONTALACCU_MAX             (0x000007ffU)

#define CSL_DSS_DISPC_VID1_ACCU2_VERTICALACCU_MASK              (0x07FF0000U)
#define CSL_DSS_DISPC_VID1_ACCU2_VERTICALACCU_SHIFT             (16U)
#define CSL_DSS_DISPC_VID1_ACCU2_VERTICALACCU_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_ACCU2_VERTICALACCU_MAX               (0x000007ffU)

#define CSL_DSS_DISPC_VID1_ACCU2_RESETVAL                       (0x00000000U)

/* VID1_FIR_COEF_H2 */

#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2_MASK              (0x00FF0000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2_SHIFT             (16U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC2_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1_SHIFT             (8U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC1_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0_SHIFT             (0U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC0_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3_MASK              (0xFF000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3_SHIFT             (24U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_FIRHC3_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_H2_RESETVAL                 (0x00000000U)

/* VID1_FIR_COEF_HV2 */

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRHC4_MASK             (0x000000FFU)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRHC4_SHIFT            (0U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRHC4_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRHC4_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0_MASK             (0x0000FF00U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0_SHIFT            (8U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC0_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1_MASK             (0x00FF0000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1_SHIFT            (16U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC1_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2_MASK             (0xFF000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2_SHIFT            (24U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_FIRVC2_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_HV2_RESETVAL                (0x00000000U)

/* VID1_FIR_COEF_V2 */

#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22_MASK             (0x0000FF00U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22_SHIFT            (8U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC22_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00_MASK             (0x000000FFU)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00_SHIFT            (0U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_FIRVC00_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID1_FIR_COEF_V2_RESETVAL                 (0x00000000U)

/* VID2_FIR2 */

#define CSL_DSS_DISPC_VID2_FIR2_FIRVINC_MASK                    (0x1FFF0000U)
#define CSL_DSS_DISPC_VID2_FIR2_FIRVINC_SHIFT                   (16U)
#define CSL_DSS_DISPC_VID2_FIR2_FIRVINC_RESETVAL                (0x00000400U)
#define CSL_DSS_DISPC_VID2_FIR2_FIRVINC_MAX                     (0x00001fffU)

#define CSL_DSS_DISPC_VID2_FIR2_FIRHINC_MASK                    (0x00001FFFU)
#define CSL_DSS_DISPC_VID2_FIR2_FIRHINC_SHIFT                   (0U)
#define CSL_DSS_DISPC_VID2_FIR2_FIRHINC_RESETVAL                (0x00000400U)
#define CSL_DSS_DISPC_VID2_FIR2_FIRHINC_MAX                     (0x00001fffU)

#define CSL_DSS_DISPC_VID2_FIR2_RESETVAL                        (0x04000400U)

/* VID2_ACCU2 */

#define CSL_DSS_DISPC_VID2_ACCU2_HORIZONTALACCU_MASK            (0x000007FFU)
#define CSL_DSS_DISPC_VID2_ACCU2_HORIZONTALACCU_SHIFT           (0U)
#define CSL_DSS_DISPC_VID2_ACCU2_HORIZONTALACCU_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_VID2_ACCU2_HORIZONTALACCU_MAX             (0x000007ffU)

#define CSL_DSS_DISPC_VID2_ACCU2_VERTICALACCU_MASK              (0x07FF0000U)
#define CSL_DSS_DISPC_VID2_ACCU2_VERTICALACCU_SHIFT             (16U)
#define CSL_DSS_DISPC_VID2_ACCU2_VERTICALACCU_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_ACCU2_VERTICALACCU_MAX               (0x000007ffU)

#define CSL_DSS_DISPC_VID2_ACCU2_RESETVAL                       (0x00000000U)

/* VID2_FIR_COEF_H2 */

#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC2_MASK              (0x00FF0000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC2_SHIFT             (16U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC2_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC2_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC1_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC1_SHIFT             (8U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC1_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC1_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC0_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC0_SHIFT             (0U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC0_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC0_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC3_MASK              (0xFF000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC3_SHIFT             (24U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC3_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_FIRHC3_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_H2_RESETVAL                 (0x00000000U)

/* VID2_FIR_COEF_HV2 */

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC1_MASK             (0x00FF0000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC1_SHIFT            (16U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC1_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC1_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC0_MASK             (0x0000FF00U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC0_SHIFT            (8U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC0_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC0_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRHC4_MASK             (0x000000FFU)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRHC4_SHIFT            (0U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRHC4_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRHC4_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC2_MASK             (0xFF000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC2_SHIFT            (24U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC2_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_FIRVC2_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_HV2_RESETVAL                (0x00000000U)

/* VID2_FIR_COEF_V2 */

#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC22_MASK             (0x0000FF00U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC22_SHIFT            (8U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC22_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC22_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC00_MASK             (0x000000FFU)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC00_SHIFT            (0U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC00_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_FIRVC00_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID2_FIR_COEF_V2_RESETVAL                 (0x00000000U)

/* VID3_FIR2 */

#define CSL_DSS_DISPC_VID3_FIR2_FIRVINC_MASK                    (0x1FFF0000U)
#define CSL_DSS_DISPC_VID3_FIR2_FIRVINC_SHIFT                   (16U)
#define CSL_DSS_DISPC_VID3_FIR2_FIRVINC_RESETVAL                (0x00000400U)
#define CSL_DSS_DISPC_VID3_FIR2_FIRVINC_MAX                     (0x00001fffU)

#define CSL_DSS_DISPC_VID3_FIR2_FIRHINC_MASK                    (0x00001FFFU)
#define CSL_DSS_DISPC_VID3_FIR2_FIRHINC_SHIFT                   (0U)
#define CSL_DSS_DISPC_VID3_FIR2_FIRHINC_RESETVAL                (0x00000400U)
#define CSL_DSS_DISPC_VID3_FIR2_FIRHINC_MAX                     (0x00001fffU)

#define CSL_DSS_DISPC_VID3_FIR2_RESETVAL                        (0x04000400U)

/* VID3_ACCU2 */

#define CSL_DSS_DISPC_VID3_ACCU2_HORIZONTALACCU_MASK            (0x000007FFU)
#define CSL_DSS_DISPC_VID3_ACCU2_HORIZONTALACCU_SHIFT           (0U)
#define CSL_DSS_DISPC_VID3_ACCU2_HORIZONTALACCU_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_VID3_ACCU2_HORIZONTALACCU_MAX             (0x000007ffU)

#define CSL_DSS_DISPC_VID3_ACCU2_VERTICALACCU_MASK              (0x07FF0000U)
#define CSL_DSS_DISPC_VID3_ACCU2_VERTICALACCU_SHIFT             (16U)
#define CSL_DSS_DISPC_VID3_ACCU2_VERTICALACCU_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_ACCU2_VERTICALACCU_MAX               (0x000007ffU)

#define CSL_DSS_DISPC_VID3_ACCU2_RESETVAL                       (0x00000000U)

/* VID3_FIR_COEF_H2 */

#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC2_MASK              (0x00FF0000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC2_SHIFT             (16U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC2_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC2_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC1_MASK              (0x0000FF00U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC1_SHIFT             (8U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC1_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC1_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC0_MASK              (0x000000FFU)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC0_SHIFT             (0U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC0_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC0_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC3_MASK              (0xFF000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC3_SHIFT             (24U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC3_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_FIRHC3_MAX               (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_H2_RESETVAL                 (0x00000000U)

/* VID3_FIR_COEF_HV2 */

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC0_MASK             (0x0000FF00U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC0_SHIFT            (8U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC0_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC0_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4_MASK             (0x000000FFU)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4_SHIFT            (0U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRHC4_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC2_MASK             (0xFF000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC2_SHIFT            (24U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC2_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC2_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC1_MASK             (0x00FF0000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC1_SHIFT            (16U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC1_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_FIRVC1_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_HV2_RESETVAL                (0x00000000U)

/* VID3_FIR_COEF_V2 */

#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC22_MASK             (0x0000FF00U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC22_SHIFT            (8U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC22_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC22_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC00_MASK             (0x000000FFU)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC00_SHIFT            (0U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC00_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_FIRVC00_MAX              (0x000000ffU)

#define CSL_DSS_DISPC_VID3_FIR_COEF_V2_RESETVAL                 (0x00000000U)

/* WB_FIR2 */

#define CSL_DSS_DISPC_WB_FIR2_FIRVINC_MASK                      (0x1FFF0000U)
#define CSL_DSS_DISPC_WB_FIR2_FIRVINC_SHIFT                     (16U)
#define CSL_DSS_DISPC_WB_FIR2_FIRVINC_RESETVAL                  (0x00000400U)
#define CSL_DSS_DISPC_WB_FIR2_FIRVINC_MAX                       (0x00001fffU)

#define CSL_DSS_DISPC_WB_FIR2_FIRHINC_MASK                      (0x00001FFFU)
#define CSL_DSS_DISPC_WB_FIR2_FIRHINC_SHIFT                     (0U)
#define CSL_DSS_DISPC_WB_FIR2_FIRHINC_RESETVAL                  (0x00000400U)
#define CSL_DSS_DISPC_WB_FIR2_FIRHINC_MAX                       (0x00001fffU)

#define CSL_DSS_DISPC_WB_FIR2_RESETVAL                          (0x04000400U)

/* WB_ACCU2 */

#define CSL_DSS_DISPC_WB_ACCU2_HORIZONTALACCU_MASK              (0x000007FFU)
#define CSL_DSS_DISPC_WB_ACCU2_HORIZONTALACCU_SHIFT             (0U)
#define CSL_DSS_DISPC_WB_ACCU2_HORIZONTALACCU_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_WB_ACCU2_HORIZONTALACCU_MAX               (0x000007ffU)

#define CSL_DSS_DISPC_WB_ACCU2_VERTICALACCU_MASK                (0x07FF0000U)
#define CSL_DSS_DISPC_WB_ACCU2_VERTICALACCU_SHIFT               (16U)
#define CSL_DSS_DISPC_WB_ACCU2_VERTICALACCU_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_ACCU2_VERTICALACCU_MAX                 (0x000007ffU)

#define CSL_DSS_DISPC_WB_ACCU2_RESETVAL                         (0x00000000U)

/* WB_FIR_COEF_H2 */

#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC2_MASK                (0x00FF0000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC2_SHIFT               (16U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC2_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC2_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC1_MASK                (0x0000FF00U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC1_SHIFT               (8U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC1_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC1_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC0_MASK                (0x000000FFU)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC0_SHIFT               (0U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC0_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC0_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC3_MASK                (0xFF000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC3_SHIFT               (24U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC3_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_H2_FIRHC3_MAX                 (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_H2_RESETVAL                   (0x00000000U)

/* WB_FIR_COEF_HV2 */

#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC0_MASK               (0x0000FF00U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC0_SHIFT              (8U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC0_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC0_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRHC4_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRHC4_SHIFT              (0U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRHC4_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRHC4_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC2_MASK               (0xFF000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC2_SHIFT              (24U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC2_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC2_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC1_MASK               (0x00FF0000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC1_SHIFT              (16U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC1_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_FIRVC1_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_HV2_RESETVAL                  (0x00000000U)

/* WB_FIR_COEF_V2 */

#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC22_MASK               (0x0000FF00U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC22_SHIFT              (8U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC22_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC22_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC00_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC00_SHIFT              (0U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC00_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_FIR_COEF_V2_FIRVC00_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_FIR_COEF_V2_RESETVAL                   (0x00000000U)

/* GLOBAL_BUFFER */

#define CSL_DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_MASK             (0x0000003FU)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_SHIFT            (0U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_GFX_BUFFER_MAX              (0x0000003fU)

#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_MASK            (0x00000FC0U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_SHIFT           (6U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_RESETVAL        (0x00000009U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID1_BUFFER_MAX             (0x0000003fU)

#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_MASK            (0x0003F000U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_SHIFT           (12U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_RESETVAL        (0x00000012U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID2_BUFFER_MAX             (0x0000003fU)

#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_MASK            (0x00FC0000U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_SHIFT           (18U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_RESETVAL        (0x0000001bU)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_VID3_BUFFER_MAX             (0x0000003fU)

#define CSL_DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_MASK              (0x3F000000U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_SHIFT             (24U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_RESETVAL          (0x00000024U)
#define CSL_DSS_DISPC_GLOBAL_BUFFER_WB_BUFFER_MAX               (0x0000003fU)

#define CSL_DSS_DISPC_GLOBAL_BUFFER_RESETVAL                    (0x246d2240U)

/* DIVISOR */

#define CSL_DSS_DISPC_DIVISOR_LCD_MASK                          (0x00FF0000U)
#define CSL_DSS_DISPC_DIVISOR_LCD_SHIFT                         (16U)
#define CSL_DSS_DISPC_DIVISOR_LCD_RESETVAL                      (0x00000004U)
#define CSL_DSS_DISPC_DIVISOR_LCD_MAX                           (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR_EN_MASK                           (0x00000001U)
#define CSL_DSS_DISPC_DIVISOR_EN_SHIFT                          (0U)
#define CSL_DSS_DISPC_DIVISOR_EN_RESETVAL                       (0x00000000U)
#define CSL_DSS_DISPC_DIVISOR_EN_ENABLE                         (0x00000001U)
#define CSL_DSS_DISPC_DIVISOR_EN_DISABLE                        (0x00000000U)

#define CSL_DSS_DISPC_DIVISOR_RESETVAL                          (0x00040000U)

/* WB_ATTRS2 */

#define CSL_DSS_DISPC_WB_ATTRS2_WBDELAYCOUNT_MASK               (0x000000FFU)
#define CSL_DSS_DISPC_WB_ATTRS2_WBDELAYCOUNT_SHIFT              (0U)
#define CSL_DSS_DISPC_WB_ATTRS2_WBDELAYCOUNT_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_WB_ATTRS2_WBDELAYCOUNT_MAX                (0x000000ffU)

#define CSL_DSS_DISPC_WB_ATTRS2_RESETVAL                        (0x00000000U)

/* DEFAULT_COLOR3 */

#define CSL_DSS_DISPC_DEFAULT_COLOR3_DEFAULTCOLOR_MASK          (0x00FFFFFFU)
#define CSL_DSS_DISPC_DEFAULT_COLOR3_DEFAULTCOLOR_SHIFT         (0U)
#define CSL_DSS_DISPC_DEFAULT_COLOR3_DEFAULTCOLOR_RESETVAL      (0x00000000U)
#define CSL_DSS_DISPC_DEFAULT_COLOR3_DEFAULTCOLOR_MAX           (0x00ffffffU)

#define CSL_DSS_DISPC_DEFAULT_COLOR3_RESETVAL                   (0x00000000U)

/* TRANS_COLOR3 */

#define CSL_DSS_DISPC_TRANS_COLOR3_TRANSCOLORKEY_MASK           (0x00FFFFFFU)
#define CSL_DSS_DISPC_TRANS_COLOR3_TRANSCOLORKEY_SHIFT          (0U)
#define CSL_DSS_DISPC_TRANS_COLOR3_TRANSCOLORKEY_RESETVAL       (0x00000000U)
#define CSL_DSS_DISPC_TRANS_COLOR3_TRANSCOLORKEY_MAX            (0x00ffffffU)

#define CSL_DSS_DISPC_TRANS_COLOR3_RESETVAL                     (0x00000000U)

/* CPR3_COEF_B */

#define CSL_DSS_DISPC_CPR3_COEF_B_BG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_B_BB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR3_COEF_B_BB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_B_BR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_B_BR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_B_RESETVAL                      (0x00000000U)

/* CPR3_COEF_G */

#define CSL_DSS_DISPC_CPR3_COEF_G_GG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_G_GB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR3_COEF_G_GB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_G_GR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_G_GR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_G_RESETVAL                      (0x00000000U)

/* CPR3_COEF_R */

#define CSL_DSS_DISPC_CPR3_COEF_R_RR_MASK                       (0xFFC00000U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RR_SHIFT                      (22U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RR_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RR_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_R_RG_MASK                       (0x001FF800U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RG_SHIFT                      (11U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RG_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RG_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_R_RB_MASK                       (0x000003FFU)
#define CSL_DSS_DISPC_CPR3_COEF_R_RB_SHIFT                      (0U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RB_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_CPR3_COEF_R_RB_MAX                        (0x000003ffU)

#define CSL_DSS_DISPC_CPR3_COEF_R_RESETVAL                      (0x00000000U)

/* DATA3_CYCLE1 */

#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE1_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA3_CYCLE1_RESETVAL                     (0x00000000U)

/* DATA3_CYCLE2 */

#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE2_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA3_CYCLE2_RESETVAL                     (0x00000000U)

/* DATA3_CYCLE3 */

#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL1_MASK            (0x0000001FU)
#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL1_SHIFT           (0U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL1_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL1_MASK      (0x00000F00U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL1_SHIFT     (8U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL1_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL1_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL2_MASK            (0x001F0000U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL2_SHIFT           (16U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_NBBITSPIXEL2_MAX             (0x0000001fU)

#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL2_MASK      (0x0F000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL2_SHIFT     (24U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL2_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_DATA3_CYCLE3_BITALIGNMENTPIXEL2_MAX       (0x0000000fU)

#define CSL_DSS_DISPC_DATA3_CYCLE3_RESETVAL                     (0x00000000U)

/* SIZE_LCD3 */

#define CSL_DSS_DISPC_SIZE_LCD3_LPP_MASK                        (0x0FFF0000U)
#define CSL_DSS_DISPC_SIZE_LCD3_LPP_SHIFT                       (16U)
#define CSL_DSS_DISPC_SIZE_LCD3_LPP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD3_LPP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_LCD3_PPL_MASK                        (0x00000FFFU)
#define CSL_DSS_DISPC_SIZE_LCD3_PPL_SHIFT                       (0U)
#define CSL_DSS_DISPC_SIZE_LCD3_PPL_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD3_PPL_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_SIZE_LCD3_DELTA_LPP_MASK                  (0x0000C000U)
#define CSL_DSS_DISPC_SIZE_LCD3_DELTA_LPP_SHIFT                 (14U)
#define CSL_DSS_DISPC_SIZE_LCD3_DELTA_LPP_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD3_DELTA_LPP_SAME                  (0x00000000U)
#define CSL_DSS_DISPC_SIZE_LCD3_DELTA_LPP_PLUSONE               (0x00000001U)
#define CSL_DSS_DISPC_SIZE_LCD3_DELTA_LPP_MINUSONE              (0x00000002U)

#define CSL_DSS_DISPC_SIZE_LCD3_RESETVAL                        (0x00000000U)

/* DIVISOR3 */

#define CSL_DSS_DISPC_DIVISOR3_LCD_MASK                         (0x00FF0000U)
#define CSL_DSS_DISPC_DIVISOR3_LCD_SHIFT                        (16U)
#define CSL_DSS_DISPC_DIVISOR3_LCD_RESETVAL                     (0x00000004U)
#define CSL_DSS_DISPC_DIVISOR3_LCD_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR3_PCD_MASK                         (0x000000FFU)
#define CSL_DSS_DISPC_DIVISOR3_PCD_SHIFT                        (0U)
#define CSL_DSS_DISPC_DIVISOR3_PCD_RESETVAL                     (0x00000001U)
#define CSL_DSS_DISPC_DIVISOR3_PCD_MAX                          (0x000000ffU)

#define CSL_DSS_DISPC_DIVISOR3_RESETVAL                         (0x00040001U)

/* POL_FREQ3 */

#define CSL_DSS_DISPC_POL_FREQ3_RF_MASK                         (0x00010000U)
#define CSL_DSS_DISPC_POL_FREQ3_RF_SHIFT                        (16U)
#define CSL_DSS_DISPC_POL_FREQ3_RF_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_RF_DRIEDPCK                     (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ3_RF_DFEDPCK                      (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ3_IHS_MASK                        (0x00002000U)
#define CSL_DSS_DISPC_POL_FREQ3_IHS_SHIFT                       (13U)
#define CSL_DSS_DISPC_POL_FREQ3_IHS_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_IHS_LCKPINAL                    (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ3_IHS_LCKPINAH                    (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ3_ACB_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_POL_FREQ3_ACB_SHIFT                       (0U)
#define CSL_DSS_DISPC_POL_FREQ3_ACB_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_ACB_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_POL_FREQ3_IVS_MASK                        (0x00001000U)
#define CSL_DSS_DISPC_POL_FREQ3_IVS_SHIFT                       (12U)
#define CSL_DSS_DISPC_POL_FREQ3_IVS_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_IVS_FCKPINAH                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_IVS_FCKPINAL                    (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ3_IEO_MASK                        (0x00008000U)
#define CSL_DSS_DISPC_POL_FREQ3_IEO_SHIFT                       (15U)
#define CSL_DSS_DISPC_POL_FREQ3_IEO_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_IEO_ACBALOW                     (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ3_IEO_ACBAHIGH                    (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ3_IPC_MASK                        (0x00004000U)
#define CSL_DSS_DISPC_POL_FREQ3_IPC_SHIFT                       (14U)
#define CSL_DSS_DISPC_POL_FREQ3_IPC_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_IPC_DRPCK                       (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_IPC_DFPCK                       (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ3_ONOFF_MASK                      (0x00020000U)
#define CSL_DSS_DISPC_POL_FREQ3_ONOFF_SHIFT                     (17U)
#define CSL_DSS_DISPC_POL_FREQ3_ONOFF_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_ONOFF_DBIT16                    (0x00000001U)
#define CSL_DSS_DISPC_POL_FREQ3_ONOFF_DOPEDPCK                  (0x00000000U)

#define CSL_DSS_DISPC_POL_FREQ3_ACBI_MASK                       (0x00000F00U)
#define CSL_DSS_DISPC_POL_FREQ3_ACBI_SHIFT                      (8U)
#define CSL_DSS_DISPC_POL_FREQ3_ACBI_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_ACBI_MAX                        (0x0000000fU)

#define CSL_DSS_DISPC_POL_FREQ3_ALIGN_MASK                      (0x00040000U)
#define CSL_DSS_DISPC_POL_FREQ3_ALIGN_SHIFT                     (18U)
#define CSL_DSS_DISPC_POL_FREQ3_ALIGN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_ALIGN_NOTALIGNED                (0x00000000U)
#define CSL_DSS_DISPC_POL_FREQ3_ALIGN_ALIGNED                   (0x00000001U)

#define CSL_DSS_DISPC_POL_FREQ3_RESETVAL                        (0x00000000U)

/* TIMING_H3 */

#define CSL_DSS_DISPC_TIMING_H3_HBP_MASK                        (0xFFF00000U)
#define CSL_DSS_DISPC_TIMING_H3_HBP_SHIFT                       (20U)
#define CSL_DSS_DISPC_TIMING_H3_HBP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H3_HBP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_H3_HSW_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_TIMING_H3_HSW_SHIFT                       (0U)
#define CSL_DSS_DISPC_TIMING_H3_HSW_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H3_HSW_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_TIMING_H3_HFP_MASK                        (0x000FFF00U)
#define CSL_DSS_DISPC_TIMING_H3_HFP_SHIFT                       (8U)
#define CSL_DSS_DISPC_TIMING_H3_HFP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_H3_HFP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_H3_RESETVAL                        (0x00000000U)

/* TIMING_V3 */

#define CSL_DSS_DISPC_TIMING_V3_VSW_MASK                        (0x000000FFU)
#define CSL_DSS_DISPC_TIMING_V3_VSW_SHIFT                       (0U)
#define CSL_DSS_DISPC_TIMING_V3_VSW_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V3_VSW_MAX                         (0x000000ffU)

#define CSL_DSS_DISPC_TIMING_V3_VFP_MASK                        (0x000FFF00U)
#define CSL_DSS_DISPC_TIMING_V3_VFP_SHIFT                       (8U)
#define CSL_DSS_DISPC_TIMING_V3_VFP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V3_VFP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_V3_VBP_MASK                        (0xFFF00000U)
#define CSL_DSS_DISPC_TIMING_V3_VBP_SHIFT                       (20U)
#define CSL_DSS_DISPC_TIMING_V3_VBP_RESETVAL                    (0x00000000U)
#define CSL_DSS_DISPC_TIMING_V3_VBP_MAX                         (0x00000fffU)

#define CSL_DSS_DISPC_TIMING_V3_RESETVAL                        (0x00000000U)

/* CTRL3 */

#define CSL_DSS_DISPC_CTRL3_STDITHEREN_MASK                     (0x00000080U)
#define CSL_DSS_DISPC_CTRL3_STDITHEREN_SHIFT                    (7U)
#define CSL_DSS_DISPC_CTRL3_STDITHEREN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_STDITHEREN_STDITHDIS                (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_STDITHEREN_STDITHENB                (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_MASK                   (0x00000300U)
#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_SHIFT                  (8U)
#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_OALSB12B               (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_OALSB16B               (0x00000001U)
#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_OALSB18B               (0x00000002U)
#define CSL_DSS_DISPC_CTRL3_TFTDATALINES_OALSB24B               (0x00000003U)

#define CSL_DSS_DISPC_CTRL3_STALLMODE_MASK                      (0x00000800U)
#define CSL_DSS_DISPC_CTRL3_STALLMODE_SHIFT                     (11U)
#define CSL_DSS_DISPC_CTRL3_STALLMODE_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_STALLMODE_NMODE                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_STALLMODE_RFBIMODE                  (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_MONOCOLOR_MASK                      (0x00000004U)
#define CSL_DSS_DISPC_CTRL3_MONOCOLOR_SHIFT                     (2U)
#define CSL_DSS_DISPC_CTRL3_MONOCOLOR_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_MONOCOLOR_COLOPENB                  (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_MONOCOLOR_MONOPENB                  (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_M8B_MASK                            (0x00000010U)
#define CSL_DSS_DISPC_CTRL3_M8B_SHIFT                           (4U)
#define CSL_DSS_DISPC_CTRL3_M8B_RESETVAL                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_M8B__4PIXTOPANEL                    (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_M8B__8PIXTOPANEL                    (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_STNTFT_MASK                         (0x00000008U)
#define CSL_DSS_DISPC_CTRL3_STNTFT_SHIFT                        (3U)
#define CSL_DSS_DISPC_CTRL3_STNTFT_RESETVAL                     (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_STNTFT_STNDISPENB                   (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_STNTFT_ATFTDISENB                   (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_GOLCD_MASK                          (0x00000020U)
#define CSL_DSS_DISPC_CTRL3_GOLCD_SHIFT                         (5U)
#define CSL_DSS_DISPC_CTRL3_GOLCD_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_GOLCD_HFUISR                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_GOLCD_UFPSR                         (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_LCDEN_MASK                          (0x00000001U)
#define CSL_DSS_DISPC_CTRL3_LCDEN_SHIFT                         (0U)
#define CSL_DSS_DISPC_CTRL3_LCDEN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_LCDEN_LCDOPDIS                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_LCDEN_LCDOPENB                      (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_MASK   (0xC0000000U)
#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_SHIFT  (30U)
#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_RESETVAL  (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_ONEFRAME  (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_TWOFRAMES  (0x00000001U)
#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_FOURFRAMES  (0x00000002U)
#define CSL_DSS_DISPC_CTRL3_SPATIALTEMPORALDITHERINGFRMS_RESERVED  (0x00000003U)

#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_MASK                  (0x06000000U)
#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_SHIFT                 (25U)
#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_LOWLEVEL              (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_HIGHLEVEL             (0x00000001U)
#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_UNCHANGED             (0x00000002U)
#define CSL_DSS_DISPC_CTRL3_TDMUNUSEDBITS_RES                   (0x00000003U)

#define CSL_DSS_DISPC_CTRL3_TDMEN_MASK                          (0x00100000U)
#define CSL_DSS_DISPC_CTRL3_TDMEN_SHIFT                         (20U)
#define CSL_DSS_DISPC_CTRL3_TDMEN_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMEN_TDMDIS                        (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMEN_TDMENB                        (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE_MASK                (0x00600000U)
#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE_SHIFT               (21U)
#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE__8BPARAINT          (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE__9BPARAINT          (0x00000001U)
#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE__12BPARAINT         (0x00000002U)
#define CSL_DSS_DISPC_CTRL3_TDMPARALLELMODE__16BPARAINT         (0x00000003U)

#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT_MASK                    (0x01800000U)
#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT_SHIFT                   (23U)
#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT__1CYCPERPIX             (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT__2CYCPERPIX             (0x00000001U)
#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT__3CYCPERPIX             (0x00000002U)
#define CSL_DSS_DISPC_CTRL3_TDMCYCLEFMT__3CYCPER2PIX            (0x00000003U)

#define CSL_DSS_DISPC_CTRL3_OVLYOPTIMIZATION_MASK               (0x00001000U)
#define CSL_DSS_DISPC_CTRL3_OVLYOPTIMIZATION_SHIFT              (12U)
#define CSL_DSS_DISPC_CTRL3_OVLYOPTIMIZATION_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_OVLYOPTIMIZATION_GDBVWFM            (0x00000000U)
#define CSL_DSS_DISPC_CTRL3_OVLYOPTIMIZATION_GDBVWNFM           (0x00000001U)

#define CSL_DSS_DISPC_CTRL3_RESETVAL                            (0x00000000U)

/* CONFIG3 */

#define CSL_DSS_DISPC_CONFIG3_PIXELDATAGATED_MASK               (0x00000010U)
#define CSL_DSS_DISPC_CONFIG3_PIXELDATAGATED_SHIFT              (4U)
#define CSL_DSS_DISPC_CONFIG3_PIXELDATAGATED_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_PIXELDATAGATED_PDGDIS             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_PIXELDATAGATED_PDGENB             (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_HSYNCGATED_MASK                   (0x00000040U)
#define CSL_DSS_DISPC_CONFIG3_HSYNCGATED_SHIFT                  (6U)
#define CSL_DSS_DISPC_CONFIG3_HSYNCGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_HSYNCGATED_HGDIS                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_HSYNCGATED_HGENB                  (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_ACBIASGATED_MASK                  (0x00000100U)
#define CSL_DSS_DISPC_CONFIG3_ACBIASGATED_SHIFT                 (8U)
#define CSL_DSS_DISPC_CONFIG3_ACBIASGATED_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_ACBIASGATED_ACBGDIS               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_ACBIASGATED_ACBGENB               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_PIXELCLOCKGATED_MASK              (0x00000020U)
#define CSL_DSS_DISPC_CONFIG3_PIXELCLOCKGATED_SHIFT             (5U)
#define CSL_DSS_DISPC_CONFIG3_PIXELCLOCKGATED_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_PIXELCLOCKGATED_PCGDIS            (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_PIXELCLOCKGATED_PCGENB            (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_VSYNCGATED_MASK                   (0x00000080U)
#define CSL_DSS_DISPC_CONFIG3_VSYNCGATED_SHIFT                  (7U)
#define CSL_DSS_DISPC_CONFIG3_VSYNCGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_VSYNCGATED_VGDIS                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_VSYNCGATED_VGENB                  (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_PIXELGATED_MASK                   (0x00000001U)
#define CSL_DSS_DISPC_CONFIG3_PIXELGATED_SHIFT                  (0U)
#define CSL_DSS_DISPC_CONFIG3_PIXELGATED_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_PIXELGATED_PCLKTOGA               (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_PIXELGATED_PCLKTOGV               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_BUFFERHANDCHECK_MASK              (0x00010000U)
#define CSL_DSS_DISPC_CONFIG3_BUFFERHANDCHECK_SHIFT             (16U)
#define CSL_DSS_DISPC_CONFIG3_BUFFERHANDCHECK_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_BUFFERHANDCHECK_HANDCHECKDIS      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_BUFFERHANDCHECK_HANDCHECKENB      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_TCKLCDEN_MASK                     (0x00000400U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDEN_SHIFT                    (10U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDEN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDEN_DISTCK                   (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDEN_ENBTCK                   (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_TCKLCDSELECTION_MASK              (0x00000800U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDSELECTION_SHIFT             (11U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDSELECTION_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDSELECTION_GDTK              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_TCKLCDSELECTION_VSTK              (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_BT656EN_MASK                      (0x00100000U)
#define CSL_DSS_DISPC_CONFIG3_BT656EN_SHIFT                     (20U)
#define CSL_DSS_DISPC_CONFIG3_BT656EN_RESETVAL                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_BT656EN_DISABLE                   (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_BT656EN_ENABLE                    (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_BT1120EN_MASK                     (0x00200000U)
#define CSL_DSS_DISPC_CONFIG3_BT1120EN_SHIFT                    (21U)
#define CSL_DSS_DISPC_CONFIG3_BT1120EN_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_BT1120EN_DISABLE                  (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_BT1120EN_ENABLE                   (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_OUTPUTMODEEN_MASK                 (0x00400000U)
#define CSL_DSS_DISPC_CONFIG3_OUTPUTMODEEN_SHIFT                (22U)
#define CSL_DSS_DISPC_CONFIG3_OUTPUTMODEEN_RESETVAL             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_OUTPUTMODEEN_DISABLE              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_OUTPUTMODEEN_ENABLE               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_CPR_MASK                          (0x00008000U)
#define CSL_DSS_DISPC_CONFIG3_CPR_SHIFT                         (15U)
#define CSL_DSS_DISPC_CONFIG3_CPR_RESETVAL                      (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_CPR_CPRDIS                        (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_CPR_CPRENB                        (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_FIDFIRST_MASK                     (0x00800000U)
#define CSL_DSS_DISPC_CONFIG3_FIDFIRST_SHIFT                    (23U)
#define CSL_DSS_DISPC_CONFIG3_FIDFIRST_RESETVAL                 (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_FIDFIRST_EVEN                     (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_FIDFIRST_ODD                      (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_COLORCONVEN_MASK                  (0x01000000U)
#define CSL_DSS_DISPC_CONFIG3_COLORCONVEN_SHIFT                 (24U)
#define CSL_DSS_DISPC_CONFIG3_COLORCONVEN_RESETVAL              (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_COLORCONVEN_COLSPCDIS             (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_COLORCONVEN_COLSPCENB             (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_FULLRANGE_MASK                    (0x02000000U)
#define CSL_DSS_DISPC_CONFIG3_FULLRANGE_SHIFT                   (25U)
#define CSL_DSS_DISPC_CONFIG3_FULLRANGE_RESETVAL                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_FULLRANGE_LIMRANGE                (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_FULLRANGE_FULLRANGE               (0x00000001U)

#define CSL_DSS_DISPC_CONFIG3_TLCDINTERLEAVE_MASK               (0x0C000000U)
#define CSL_DSS_DISPC_CONFIG3_TLCDINTERLEAVE_SHIFT              (26U)
#define CSL_DSS_DISPC_CONFIG3_TLCDINTERLEAVE_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_CONFIG3_TLCDINTERLEAVE_MAX                (0x00000003U)

#define CSL_DSS_DISPC_CONFIG3_RESETVAL                          (0x00000000U)

/* GAMMA_TBL3 */

#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_R_MASK                   (0x00FF0000U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_R_SHIFT                  (16U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_R_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_R_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL3_IDX_MASK                       (0xFF000000U)
#define CSL_DSS_DISPC_GAMMA_TBL3_IDX_SHIFT                      (24U)
#define CSL_DSS_DISPC_GAMMA_TBL3_IDX_RESETVAL                   (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL3_IDX_MAX                        (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_G_MASK                   (0x0000FF00U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_G_SHIFT                  (8U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_G_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_G_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_B_MASK                   (0x000000FFU)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_B_SHIFT                  (0U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_B_RESETVAL               (0x00000000U)
#define CSL_DSS_DISPC_GAMMA_TBL3_VALUE_B_MAX                    (0x000000ffU)

#define CSL_DSS_DISPC_GAMMA_TBL3_RESETVAL                       (0x00000000U)

/* BA0_FLIPIMMEDIATE_EN */

#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_GFX_MASK             (0x00000001U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_GFX_SHIFT            (0U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_GFX_RESETVAL         (0x00000000U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_GFX_MAX              (0x00000001U)

#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID1_MASK            (0x00000002U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID1_SHIFT           (1U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID1_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID1_MAX             (0x00000001U)

#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID2_MASK            (0x00000004U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID2_SHIFT           (2U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID2_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID2_MAX             (0x00000001U)

#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID3_MASK            (0x00000008U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID3_SHIFT           (3U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID3_RESETVAL        (0x00000000U)
#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_VID3_MAX             (0x00000001U)

#define CSL_DSS_DISPC_BA0_FLIPIMMEDIATE_EN_RESETVAL             (0x00000000U)

/* GLOBAL_MFLAG_ATTR */

#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_CTRL_MASK         (0x00000003U)
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_CTRL_SHIFT        (0U)
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_CTRL_RESETVAL     (0x00000000U)
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_CTRL_MAX          (0x00000003U)

#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_START_MASK        (0x00000004U)
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_START_SHIFT       (2U)
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_START_RESETVAL    (0x00000000U)
#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_MFLAG_START_MAX         (0x00000001U)

#define CSL_DSS_DISPC_GLOBAL_MFLAG_ATTR_RESETVAL                (0x00000000U)

/* GFX_MFLAG_THR */

#define CSL_DSS_DISPC_GFX_MFLAG_THR_LT_MFLAG_MASK               (0x0000FFFFU)
#define CSL_DSS_DISPC_GFX_MFLAG_THR_LT_MFLAG_SHIFT              (0U)
#define CSL_DSS_DISPC_GFX_MFLAG_THR_LT_MFLAG_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_GFX_MFLAG_THR_LT_MFLAG_MAX                (0x0000ffffU)

#define CSL_DSS_DISPC_GFX_MFLAG_THR_HT_MFLAG_MASK               (0xFFFF0000U)
#define CSL_DSS_DISPC_GFX_MFLAG_THR_HT_MFLAG_SHIFT              (16U)
#define CSL_DSS_DISPC_GFX_MFLAG_THR_HT_MFLAG_RESETVAL           (0x00000000U)
#define CSL_DSS_DISPC_GFX_MFLAG_THR_HT_MFLAG_MAX                (0x0000ffffU)

#define CSL_DSS_DISPC_GFX_MFLAG_THR_RESETVAL                    (0x00000000U)

/* VID1_MFLAG_THR */

#define CSL_DSS_DISPC_VID1_MFLAG_THR_LT_MFLAG_MASK              (0x0000FFFFU)
#define CSL_DSS_DISPC_VID1_MFLAG_THR_LT_MFLAG_SHIFT             (0U)
#define CSL_DSS_DISPC_VID1_MFLAG_THR_LT_MFLAG_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_MFLAG_THR_LT_MFLAG_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID1_MFLAG_THR_HT_MFLAG_MASK              (0xFFFF0000U)
#define CSL_DSS_DISPC_VID1_MFLAG_THR_HT_MFLAG_SHIFT             (16U)
#define CSL_DSS_DISPC_VID1_MFLAG_THR_HT_MFLAG_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID1_MFLAG_THR_HT_MFLAG_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID1_MFLAG_THR_RESETVAL                   (0x00000000U)

/* VID2_MFLAG_THR */

#define CSL_DSS_DISPC_VID2_MFLAG_THR_LT_MFLAG_MASK              (0x0000FFFFU)
#define CSL_DSS_DISPC_VID2_MFLAG_THR_LT_MFLAG_SHIFT             (0U)
#define CSL_DSS_DISPC_VID2_MFLAG_THR_LT_MFLAG_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_MFLAG_THR_LT_MFLAG_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID2_MFLAG_THR_HT_MFLAG_MASK              (0xFFFF0000U)
#define CSL_DSS_DISPC_VID2_MFLAG_THR_HT_MFLAG_SHIFT             (16U)
#define CSL_DSS_DISPC_VID2_MFLAG_THR_HT_MFLAG_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID2_MFLAG_THR_HT_MFLAG_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID2_MFLAG_THR_RESETVAL                   (0x00000000U)

/* VID3_MFLAG_THR */

#define CSL_DSS_DISPC_VID3_MFLAG_THR_LT_MFLAG_MASK              (0x0000FFFFU)
#define CSL_DSS_DISPC_VID3_MFLAG_THR_LT_MFLAG_SHIFT             (0U)
#define CSL_DSS_DISPC_VID3_MFLAG_THR_LT_MFLAG_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_MFLAG_THR_LT_MFLAG_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID3_MFLAG_THR_HT_MFLAG_MASK              (0xFFFF0000U)
#define CSL_DSS_DISPC_VID3_MFLAG_THR_HT_MFLAG_SHIFT             (16U)
#define CSL_DSS_DISPC_VID3_MFLAG_THR_HT_MFLAG_RESETVAL          (0x00000000U)
#define CSL_DSS_DISPC_VID3_MFLAG_THR_HT_MFLAG_MAX               (0x0000ffffU)

#define CSL_DSS_DISPC_VID3_MFLAG_THR_RESETVAL                   (0x00000000U)

/* WB_MFLAG_THR */

#define CSL_DSS_DISPC_WB_MFLAG_THR_LT_MFLAG_MASK                (0x0000FFFFU)
#define CSL_DSS_DISPC_WB_MFLAG_THR_LT_MFLAG_SHIFT               (0U)
#define CSL_DSS_DISPC_WB_MFLAG_THR_LT_MFLAG_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_MFLAG_THR_LT_MFLAG_MAX                 (0x0000ffffU)

#define CSL_DSS_DISPC_WB_MFLAG_THR_HT_MFLAG_MASK                (0xFFFF0000U)
#define CSL_DSS_DISPC_WB_MFLAG_THR_HT_MFLAG_SHIFT               (16U)
#define CSL_DSS_DISPC_WB_MFLAG_THR_HT_MFLAG_RESETVAL            (0x00000000U)
#define CSL_DSS_DISPC_WB_MFLAG_THR_HT_MFLAG_MAX                 (0x0000ffffU)

#define CSL_DSS_DISPC_WB_MFLAG_THR_RESETVAL                     (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
