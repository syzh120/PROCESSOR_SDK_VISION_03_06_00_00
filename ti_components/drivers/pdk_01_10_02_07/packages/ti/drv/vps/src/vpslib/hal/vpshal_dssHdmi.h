/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 */

/**
 *  \file vpshal_dssHdmi.h
 *
 *  \brief HAL layer for the DSS DISPC Video Pipeline Module.
 *  This file exposes the HAL APIs of the DISPC Video Pipeline .
 *  This HAL is meant to be used by other VPS driver. The application don't
 *  have to access this HAL module.
 *
 */

#ifndef VPSHAL_HDMI_H_
#define VPSHAL_HDMI_H_

/* ========================================================================== */
/*                          Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                        Macros & Typedefs                                */
/* ========================================================================== */

#define VPSHAL_DSS_HDMI_MAX_INST             (1U)

#define VPSHAL_HDMI_DEFAULT_REGN 16

#define VPSHAL_HDMI_DEFAULT_REGM2 1

typedef enum
{
    VPSHAL_HDMI_PLLPWRCMD_ALLOFF = 0,

    VPSHAL_HDMI_PLLPWRCMD_PLLONLY = 1,

    VPSHAL_HDMI_PLLPWRCMD_BOTHON_ALLCLKS = 2,

    VPSHAL_HDMI_PLLPWRCMD_BOTHON_NOPHYCLK = 3
}vpsHal_hdmiPllPwr;

typedef enum
{
    VPSHAL_HDMI_DVI = 0,

    VPSHAL_HDMI_HDMI = 1
} vpsHal_hdmiCoreHdmiDvi;

typedef enum
{
    VPSHAL_HDMI_PHYPWRCMD_OFF = 0,

    VPSHAL_HDMI_PHYPWRCMD_LDOON = 1,

    VPSHAL_HDMI_PHYPWRCMD_TXON = 2
}vpsHal_hdmiPhyPwr;

typedef enum
{
    VPSHAL_HDMI_LIMITED_RANGE = 0,

    VPSHAL_HDMI_FULL_RANGE
}vpsHal_hdmiRange;

typedef enum
{
    VPSHAL_HDMI_REFSEL_PCLK = 0,

    VPSHAL_HDMI_REFSEL_REF1 = 1,

    VPSHAL_HDMI_REFSEL_REF2 = 2,

    VPSHAL_HDMI_REFSEL_SYSCLK = 3
}vpsHal_hdmiClkRefsel;

typedef enum
{
    VPSHAL_HDMI_DEEP_COLOR_24BIT = 0,

    VPSHAL_HDMI_DEEP_COLOR_30BIT = 1,

    VPSHAL_HDMI_DEEP_COLOR_36BIT = 2
}vpsHal_hdmiDeepColorMode;

typedef enum
{
    VPSHAL_HDMI_INPUT_8BIT = 0,

    VPSHAL_HDMI_INPUT_10BIT = 1,

    VPSHAL_HDMI_INPUT_12BIT = 2
}vpsHal_hdmiInputBusWidth;

typedef enum
{
    VPSHAL_HDMI_PACK_10b_RGB_YUV444 = 0,

    VPSHAL_HDMI_PACK_24b_RGB_YUV444_YUV422 = 1,

    VPSHAL_HDMI_PACK_20b_YUV422 = 2,

    VPSHAL_HDMI_PACK_ALREADYPACKED = 7
}vpsHal_hdmiPackingMode;

typedef enum
{
    VPSHAL_HDMI_OUTPUTTRUNCATION_8BIT = 0,

    VPSHAL_HDMI_OUTPUTTRUNCATION_10BIT = 1,

    VPSHAL_HDMI_OUTPUTTRUNCATION_12BIT = 2,

    VPSHAL_HDMI_OUTPUTDITHER_8BIT = 3,

    VPSHAL_HDMI_OUTPUTDITHER_10BIT = 4,

    VPSHAL_HDMI_OUTPUTDITHER_12BIT = 5
}vpsHal_hdmiDitherTrunc;

typedef enum
{
    VPSHAL_HDMI_DEEPCOLORPACKECTDISABLE = 0,

    VPSHAL_HDMI_DEEPCOLORPACKECTENABLE = 1
}vpsHal_hdmiDeepcolorEn;

typedef enum
{
    VPSHAL_HDMI_PACKETMODERESERVEDVALUE = 0,

    VPSHAL_HDMI_PACKETMODE24BITPERPIXEL = 4,

    VPSHAL_HDMI_PACKETMODE30BITPERPIXEL = 5,

    VPSHAL_HDMI_PACKETMODE36BITPERPIXEL = 6,

    VPSHAL_HDMI_PACKETMODE48BITPERPIXEL = 7
}vpsHal_hdmiPacketMode;

typedef enum
{
    VPSHAL_HDMI_FPLL05IDCK = 0,

    VPSHAL_HDMI_FPLL10IDCK = 1,

    VPSHAL_HDMI_FPLL20IDCK = 2,

    VPSHAL_HDMI_FPLL40IDCK = 3
}vpsHal_hdmiTclkSelclkMult;

typedef enum
{
    VPSHAL_HDMI_PACKETENABLE = 1,

    VPSHAL_HDMI_PACKETDISABLE = 0,

    VPSHAL_HDMI_PACKETREPEATON = 1,

    VPSHAL_HDMI_PACKETREPEATOFF = 0
}vpsHal_hdmiPacketCtrl;

/* INFOFRAME_AVI_ and INFOFRAME_AUDIO_ definitions */

typedef enum
{
    VPSHAL_HDMI_INFOFRAME_AVI_DB1Y_RGB = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1Y_YUV422 = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1Y_YUV444 = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1A_ACTIVE_FORMAT_OFF = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1A_ACTIVE_FORMAT_ON = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1B_NO = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1B_VERT = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1B_HORI = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1B_VERTHORI = 3,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1S_0 = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1S_1 = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB1S_2 = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2C_NO = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2C_ITU601 = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2C_ITU709 = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2C_EC_EXTENDED = 3,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2M_NO = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2M_43 = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2M_169 = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2R_SAME = 8,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2R_43 = 9,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2R_169 = 10,

    VPSHAL_HDMI_INFOFRAME_AVI_DB2R_149 = 11,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3ITC_NO = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3ITC_YES = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3EC_XVYUV601 = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3EC_XVYUV709 = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3Q_DEFAULT = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3Q_LR = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3Q_FR = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3SC_NO = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3SC_HORI = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3SC_VERT = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB3SC_HORIVERT = 3,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_NO = 0,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_2 = 1,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_3 = 2,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_4 = 3,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_5 = 4,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_6 = 5,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_7 = 6,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_8 = 7,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_9 = 8,

    VPSHAL_HDMI_INFOFRAME_AVI_DB5PR_10 = 9
}vpsHal_hdmiAviInfoframe;

/* ========================================================================== */
/*                      Structure Declarations                             */
/* ========================================================================== */

typedef struct {
    UInt16 a1, a2, a3, a4;
    UInt16 b1, b2, b3, b4;
    UInt16 c1, c2, c3, c4;
}cscTable;

/**
 *  struct VpsHal_DssDispcLcdTimingParam
 *  \brief Timing Params for the LCD overlays(LCD1,LCD2,LCD3) .
 */
typedef struct
{
    UInt32 width;
    /**< Active video frame width in pixels. */
    UInt32 height;
    /**< Active video frame height in lines. */
    UInt32 scanFormat;
    /**< Scan format of standard. For valid values see #Fvid2_ScanFormat. */
    UInt32 pixel_clock;
    /**<Pixel clock to be set. */
    UInt32 hFrontPorch;
    /**< Horizontal Front Porch, specifies the number of pixel clock periods
     *   to add to the end of a line transmission before line clock is asserted.
     * */
    UInt32 hBackPorch;
    /**< Horizontal Back Porch, specifies the number of pixel clock periods
     *   to add to the beginning of a line transmission before the first set of
     *   pixels is output to the display. */
    UInt32 hSyncLen;
    /**< Horizontal synchronization pulse width, Encoded Value(from 1 to 256)to
     *   specify the number of pixel clock periods to pulse the line clock
     *   at the end of each line. */
    UInt32 vFrontPorch;
    /**< Vertical front porch encoded value (from 0 to 4095) to
     *   specify the number of line clock periods to add to the end
     *   of each frame. */
    UInt32 vBackPorch;
    /**< Vertical back porch encoded value (from 0 to 4095) to
     *   specify the number of line clock periods to add to the
     *   beginning of a frame. */
    UInt32 vSyncLen;
    /**< Vertical synchronization pulse width In active mode, RW 0x00
     *  encoded value (from 1 to 256) to specify the number of
     *  line clock periods (program to value minus 1) to pulse the
     *  frame clock (VSYNC) pin at the end of each frame after
     *  the end of frame wait (VFP) period elapses. Frame clock
     *  uses as VSYNC signal in active mode. */
    UInt32 mode;
    /**< VENC mode */
    UInt32 outputRange;
    /**< This parameter is used to configure the output of the venc to be in
     *   full range or limited range. Use VPS_DCTRL_VENC_OUTPUT_FULL_RANGE or
     *   VPS_DCTRL_VENC_OUTPUT_LIMITED_RANGE macro for this variable. */
} VpsHal_DssHdmiTimingParam;

/* HDMI PLL structure */
typedef struct
{
    UInt16               regn;
    UInt16               regm;
    UInt32               regmf;
    UInt16               regm2;
    UInt16               regsd;
    UInt16               dcofreq;
    vpsHal_hdmiClkRefsel refSel;
} VpsHal_DssHdmiPllInfo;

typedef struct
{
    UInt32 dataFormat;
    /**< Output Data format from Venc. Currently, valid values are TODO*/
    UInt32 vsPolarity;
    /**< VSYNC Polarity
     *  0x0: Frame clock pin is active high and inactive low.
     *  0x1: Frame clock pin is active low and inactive high. */
    UInt32 hsPolarity;
    /**< HSYNC Polarity
     *   0x0: Line clock pin is active high and inactive low.
     *   0x1: Line clock pin is active low and inactive high. */
} VpsHal_DssHdmiOutputInfo;

/**
 *  struct VpsHal_DssDispcLcdTimingParam
 *  \brief Timing Params for the LCD overlays(LCD1,LCD2,LCD3) .
 */
typedef struct
{
    UInt32                standardCode;
    UInt32                deepColor;
    UInt32                Range;
    UInt32                packingMode;
    vpsHal_hdmiPacketMode pktMode;
} VpsHal_DssHdmiParam;

typedef struct
{
    vpsHal_hdmiInputBusWidth  busWidth;
    vpsHal_hdmiDitherTrunc    ditherTrunc;
    vpsHal_hdmiDeepcolorEn    deepColorPacketEn;
    vpsHal_hdmiTclkSelclkMult tclkSelClkMult;
} VpsHal_DssHdmiCoreVideoConfig;

/*
 * Refer to section 8.2 in HDMI 1.3 specification for
 * details about infoframe databytes
 */
typedef struct
{
    /* Y0, Y1 rgb,yCbCr */
    UInt8  db1Format;
    /* A0  Active information Present */
    UInt8  db1ActiveInfo;
    /* B0, B1 Bar info data valid */
    UInt8  db1BarInfoDv;
    /* S0, S1 scan information */
    UInt8  db1ScanInfo;
    /* C0, C1 colorimetry */
    UInt8  db2Colorimetry;
    /* M0, M1 Aspect ratio (4:3, 16:9) */
    UInt8  db2AspectRatio;
    /* R0...R3 Active format aspect ratio */
    UInt8  db2ActiveFmtAr;
    /* ITC IT content. */
    UInt8  db3Itc;
    /* EC0, EC1, EC2 Extended colorimetry */
    UInt8  db3Ec;
    /* Q1, Q0 Quantization range */
    UInt8  db3QRange;
    /* SC1, SC0 Non-uniform picture scaling */
    UInt8  db3NupScaling;
    /* VIC0..6 Video format identification */
    UInt8  db4Videocode;
    /* PR0..PR3 Pixel repetition factor */
    UInt8  db5PixelRepeat;
    /* Line number end of top bar */
    UInt16 db67LineEndofTop;
    /* Line number start of bottom bar */
    UInt16 db89LineStartofBottom;
    /* Pixel number end of left bar */
    UInt16 db1011PixelEofLeft;
    /* Pixel number start of right bar */
    UInt16 db1213PixelStartofRight;
}vpsHal_hdmiCoreAviInfoframe;

typedef struct
{
    VpsHal_DssHdmiTimingParam   timing;
    VpsHal_DssHdmiParam         advParam;
    vpsHal_hdmiCoreAviInfoframe aviInfo;
    VpsHal_DssHdmiOutputInfo    outputInfo;
}VpsHal_HdmiInfo;

typedef struct
{
    VpsHal_DssHdmiTimingParam timing;
    /**< Display mode select - 480i, 480p, 1080i, 720p, 576i or 576p. */
    UInt32                    stdCode;
} HdVenc_StdModeInfo;

/* ========================================================================== */
/*                       Function Declarations                             */
/* ========================================================================== */

void vpshal_HdmiComputePll(Int32 pixelClock, VpsHal_DssHdmiPllInfo *pllInfo);
Int32 vpshal_HdmiPllEnable(const VpsHal_DssHdmiPllInfo *pllInfo);
void vpshal_HdmiPllDisable(void);
Int32 vpshal_HdmiPhyEnable(UInt32 enable);
void vpshal_HdmiWpVideoStart(UInt32 start);
void VpsHal_hdmiVencOuptputConfig(const VpsHal_DssHdmiOutputInfo *opInfo);
void VpsHal_hdmiBasicConfigure(const VpsHal_DssHdmiTimingParam *hdmiCfg);
Int32 vpshal_HdmiPhyPowerOn(const VpsHal_DssHdmiTimingParam *timing);
Int32 VpsHal_hdmiGetTiming(UInt32                     standard,
                           VpsHal_DssHdmiTimingParam *hdmiConf);
void vpshal_HdmiReset(void);
void halHdmiWpVideoTimingConfig(const VpsHal_DssHdmiTimingParam *timing);
void halHdmiWpVideoFormatConfig(const VpsHal_DssHdmiTimingParam *timing,
                                const VpsHal_DssHdmiParam       *param,
                                const VpsHal_DssHdmiOutputInfo  *outputInfo);
void halHdmiVideoPathEnable(void);
Int32 halHdmiCoreConfigureRange(const VpsHal_DssHdmiParam   *advHdmi,
                                vpsHal_hdmiCoreAviInfoframe *aviInfoFrame);
void vpshal_HdmiFlipDataPnOrder(void);

/* ========================================================================== */
/*                    Static Function Definitions                          */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_DISPC_VID_H_ */

