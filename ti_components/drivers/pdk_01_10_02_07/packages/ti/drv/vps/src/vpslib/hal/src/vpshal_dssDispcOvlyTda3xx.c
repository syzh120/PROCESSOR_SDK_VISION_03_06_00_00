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
 *  \file vpshal_dssDispcOvlyTda3xx.c
 *
 *  \brief VPS DSS Dispc Overlay  HAL file.
 *  This file implements the HAL APIs of the DSS DISPC
 *  Overlay and Video Port For ADAS-Low.
 *
 */

/* TODO - Pending Items
 *   1. Transparency color key - range should be supported
 *   3. Check with scalar code - there are changes with respect to vayu need
 *       to review.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/csl/soc.h>

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dss.h>

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/include/dss/vps_cfgDss.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dssDispcOvly.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dssDispcVid.h>

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsHal_DssDispcOvlyRegOffset
 *  \brief structure to store register offsets of each Overlay.
 */
typedef struct
{
    UInt32 dispcVpControl;
    /**<  offset of Control register for an instance of Video Port */
    UInt32 dispcOvrControl;
    /**<  offset of Control register for an instance of overlay */
    UInt32 dispcVpConfig;
    /**<  offset of Config register for an instance of Video Port */
    UInt32 dispcOvrConfig;
    /**<  offset of Config register for an instance of overlay */
    UInt32 defaultcolor[2];
    /**<  offset of Default Color register for an instance*/
    UInt32 panelSize;
    /**<  offset of panel size register for an instance*/
    UInt32 pipeAttrib[VPSHAL_DSS_DISPC_PIPE_MAX_INST];
    /**<  Array of offset of attribute register for an instance*/
    UInt32 cprCoeff[3];
    /**<  Array of offset of CPR coefficients register for an instance*/
    UInt32 globalAlpha;
    /**<  offset of global alpha register for an instance*/
    UInt32 transColorMin[2];
    /**<  offset of Minimum trans color register for an instance*/
    UInt32 transColorMax[2];
    /**<  offset of Maximum trans color register for an instance*/
    UInt32 dataCycle1;
    /**<  offset of Tdm Data1 Cycle register for an instance*/
    UInt32 dataCycle2;
    /**<  offset of Tdm Data2 Cycle register for an instance*/
    UInt32 dataCycle3;
    /**<  offset of Tdm Data3 Cycle register for an instance*/
    UInt32 polFreq;
    /**<  offset of Pol  register for an instance*/
    UInt32 lcdTimingH;
    /**<  offset of horizontal Lcd Timing  register for an instance*/
    UInt32 lcdTimingV;
    /**<  offset of vertical Lcd Timing  register for an instance*/
    UInt32 lcdDivisor;
    /**<  offset of divior register for generating the freq for an instance*/
    UInt32 lineStatus;
    /**<  offset of Line status register to get the current line number for an
     *instance*/
} VpsHal_DssDispcOvlyRegOffset;

/**
 *  struct VpsHal_DssDispcOvlyObj
 *  \brief Per instance information about each Overlay  module.
 */
typedef struct
{
    UInt32                       halId;
    /**< Instance number/ID */
    UInt32                       openCnt;
    /**< Counter to keep track of number of open calls for an instance */
    VpsHal_DssDispcOvlyRegOffset regOffset;
    /**< Structure to store offsets of all the registers related to Overlay */
    VpsHal_DssDispcCprCoeff              cprCoeff;
    /**< Structure to store store the cpr coefficients for the overlay */
} VpsHal_DssDispcOvlyObj;

/* Coefficients for BT601-5 RGB to YUV conversion */
static const VpsHal_DssDispcCprCoeff gDssCprCoeff = {
    DSS_VP_CONFIG_CPR_CPRDIS, DSS_VP_CONFIG_COLORCONVENABLE_COLSPCDIS,
    77,            150,            29,
    -((Int16) 44), -((Int16) 87),  131,
    131,           -((Int16) 110), -((Int16) 21)};

Fvid2_ModeInfo gDssStdModeInfo[] = {
    {FVID2_STD_1080P_60,       1920, 1080, FVID2_SF_PROGRESSIVE, 148500, 60,
     88, 148, 44, 4, 36, 5},
    {FVID2_STD_1080P_50,       1920, 1080, FVID2_SF_PROGRESSIVE, 74250,  50,
     528, 148, 44, 4, 36, 5},
    {FVID2_STD_1080P_30,       1920, 1080, FVID2_SF_PROGRESSIVE, 74250,  30,
     88, 148, 44, 4, 36, 5},
    {FVID2_STD_720P_60,        1280, 720,  FVID2_SF_PROGRESSIVE, 74250,  60,
     110, 220, 40, 5, 20, 5},
    {FVID2_STD_720P_50,        1280, 720,  FVID2_SF_PROGRESSIVE, 74250,  50,
     440, 220, 40, 5, 20, 5},
    {FVID2_STD_XGA_60,         1024, 768,  FVID2_SF_PROGRESSIVE, 65000,  60,
     136, 160, 24, 3, 29, 6},
    {FVID2_STD_XGA_DSS_TDM_60, 1024, 768,  FVID2_SF_PROGRESSIVE, 64000,  60,
     136, 160, 24, 3, 29, 6},
    {FVID2_STD_XGA_75,         1024, 768,  FVID2_SF_PROGRESSIVE, 78750,  75,
     16, 176, 96, 1, 28, 3},
    {FVID2_STD_SXGA_60,        1280, 1024, FVID2_SF_PROGRESSIVE, 108000, 60,
     48, 248, 112, 1, 38, 3},
    {FVID2_STD_SXGA_75,        1280, 1024, FVID2_SF_PROGRESSIVE, 135000, 75,
     16, 248, 144, 1, 38, 3},
    {FVID2_STD_UXGA_60,        1600, 1200, FVID2_SF_PROGRESSIVE, 162000, 60,
     64, 304, 192, 1, 46, 3},
    {FVID2_STD_1080I_60,       1920, 540,  FVID2_SF_INTERLACED,  74250,  30,
     88, 148, 44, 2, 15, 5},
    {FVID2_STD_1080I_50,       1920, 540,  FVID2_SF_INTERLACED,  74250,  30,
     528, 148, 44, 2, 15, 5},
    {FVID2_STD_480P,           720,  480,  FVID2_SF_PROGRESSIVE, 27000,  60,
     16, 60, 62, 9, 30, 6},
    {FVID2_STD_576P,           720,  576,  FVID2_SF_PROGRESSIVE, 27000,  50,
     12, 68, 64, 5, 39, 5},
    {FVID2_STD_576I,           720,  288,  FVID2_SF_INTERLACED,  27000,  25,
     12, 69, 63, 2, 19, 3},
    {FVID2_STD_480I,           720,  240,  FVID2_SF_INTERLACED,  27000,  30,
     19, 57, 62, 4, 15, 3},
    {FVID2_STD_NTSC,           720,  240,  FVID2_SF_INTERLACED,  27000,  30,
     19, 57, 62, 4, 15, 3},
    {FVID2_STD_PAL,            720,  288,  FVID2_SF_INTERLACED,  27000,  25,
     12, 69, 63, 2, 19, 3},
    {FVID2_STD_WXGA_60,        1280, 800,  FVID2_SF_PROGRESSIVE, 83500,  60,
     128, 200, 72, 3, 22, 6},
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 halDispcOvlyInitInstance(VpsHal_DssDispcOvlyObj *dispcOvlyObj);

static void halDispcOvlyPipeConfZorder(VpsHal_Handle handle,
                                       UInt32        pipe,
                                       UInt32        zorder);

static void halDispcOvlyPipeSetGlobalAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        globalAlpha);

static void halDispcOvlyPipeSetPreMulAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        preMultiplyAlpha);

static void halDispcOvlyPipeSetChannelOut(VpsHal_Handle handle,
                                          UInt32        pipe);

static void halDispcOvlyPanelColorKeyConf(VpsHal_Handle handle,
                                          UInt32        colorKeyEnable,
                                          UInt32        colorKeySel);

static void halDispcOvlyPanelSetTransColorKey(VpsHal_Handle handle,
                                              UInt32        transColorKeyMin,
                                              UInt32        transColorKeyMax);

static void halDispcOvlyPanelDeltaLinesConf(VpsHal_Handle handle,
                                            UInt32        deltaLinesPerPanel);

static void halDispcOvlySetBgColor(VpsHal_Handle handle,
                                   UInt32        bgColor);

static void halDispcOvlySet48BitBgColor(VpsHal_Handle handle,
                                        UInt32        bgColor0,
                                        UInt32        bgColor1);

static void halDispcOvlyOptimizationConf(VpsHal_Handle handle,
                                         UInt32        ovlyOptimization);

static void halDispcOvlyGetChannelOutVal(UInt32  halId,
                                         UInt32 *chlout);

static void halDispcConfCprCoeff(VpsHal_Handle handle,
                                 const VpsHal_DssDispcCprCoeff *cprCoeff);

static Int32 halDispcOvlyBT656_1120Conf(VpsHal_Handle handle,
                                        UInt32        dvoFormat,
                                        UInt32        enable);

static void halDispcReset(void);

static void halDispcSetDefIntfWidth(void);

static Int32 halDispcOvlyGetTdmHblankFact(
    const VpsHal_DssDispcOvlyObj *dispcOvlyObj,
    UInt32                       *hBlankMultFact,
    UInt32                       *hBlankDivFact);

static Int32 halDispcOvlyValidateLcdBlankTiming(
    const VpsHal_DssDispcLcdBlankTimingParam *lcdBlankTimingParm,
    UInt32                                    hBlankMultFact,
    UInt32                                    hBlankDivFact);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 *  DISP OVL  objects - Module variable to store information about each Overlay
 *  instance .Note: If the number of Overlay  instance increase,
 *  then VPSHAL_DSS_DISPC_OVLY_MAX_INST macro should be changed accordingly.
 */
static VpsHal_DssDispcOvlyObj gDispcOvlyHalObj[VPSHAL_DSS_DISPC_OVLY_MAX_INST];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsHal_dssOvlyInit
 *  \brief DISPC OVL HAL init function.
 *
 *  Initializes OVL objects, gets the register overlay offsets for DISPC OVL
 *  registers.
 *  This function should be called before calling any of DISPC OVL HAL API's.
 *
 *  \param numInst          Number of instance objects to be initialized
 *  \param instPrms         Pointer to the instance parameter containing
 *                          instance specific information. If the number of
 *                          instance is greater than 1, then this pointer
 *                          should point to an array of init parameter
 *                          structure of size numInst.
 *                          This parameter should not be NULL.
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyInit(UInt32                            numInst,
                         const VpsHal_DispcOvlyInstParams *instPrms,
                         Ptr                               arg)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for errors */
    GT_assert(VpsHalTrace, (numInst <= VPSHAL_DSS_DISPC_OVLY_MAX_INST));
    GT_assert(VpsHalTrace, (instPrms != NULL));

    /* Initialize DISPC OVL Objects to zero */
    BspUtils_memset(gDispcOvlyHalObj, 0, sizeof (gDispcOvlyHalObj));

    for (instCnt = 0; instCnt < numInst; instCnt++)
    {
        GT_assert(VpsHalTrace,
                  (instPrms[instCnt].halId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX));

        dispcOvlyObj        = &gDispcOvlyHalObj[instCnt];
        dispcOvlyObj->halId = instPrms[instCnt].halId;

        /* Initialize the instance */
        retVal += halDispcOvlyInitInstance(dispcOvlyObj);
    }

    halDispcReset();

    halDispcSetDefIntfWidth();

    return (retVal);
}

/**
 *  VpsHal_dssOvlyDeInit
 *  \brief DSS DISPC OVL HAL exit function.
 *
 *  Currently this function does not do anything.
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyDeInit(Ptr arg)
{
    UInt32 instCnt;

    for (instCnt = 0; instCnt < VPSHAL_DSS_DISPC_OVLY_MAX_INST; instCnt++)
    {
        gDispcOvlyHalObj[instCnt].halId   = 0;
        gDispcOvlyHalObj[instCnt].openCnt = 0;
    }

    return (BSP_SOK);
}

/**
 *  VpsHal_dssOvlyOpen
 *  \brief Returns the handle to the requested DISPC OVL(Overlay) instance.
 *
 *  This function should be called prior to calling any of the DISPC OVL HAL
 *  configuration APIs to get the instance handle.
 *
 *  \param halId            Requested DISPC OVL instance.
 *
 *  \return                 Returns DISPC OVL instance handle on success else
 *                          returns NULL.
 */
VpsHal_Handle VpsHal_dssOvlyOpen(
    const VpsHal_DispcOvlyOpenParams *openPrms)
{
    UInt32        cnt;
    VpsHal_Handle handle = NULL;

    /* Check if instance number is valid */
    GT_assert(VpsHalTrace, (NULL != openPrms));
    GT_assert(VpsHalTrace, (openPrms->halId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX));

    for (cnt = 0; cnt < VPSHAL_DSS_DISPC_OVLY_MAX_INST; cnt++)
    {
        /* Return the matching instance handle */
        if (openPrms->halId == gDispcOvlyHalObj[cnt].halId)
        {
            /* Check whether some one has already opened this instance */
            if (0U == gDispcOvlyHalObj[cnt].openCnt)
            {
                handle = (VpsHal_Handle) & gDispcOvlyHalObj[cnt];
                gDispcOvlyHalObj[cnt].openCnt++;
            }
            break;
        }
    }
    return (handle);
}

/**
 *  VpsHal_dssOvlyClose
 *  \brief Closes the DISPC OVL HAL instance.
 *
 *  Currently this function does not do anything. It is provided in case
 *  in the future resource management is done by individual HAL - using
 *  counters.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyClose(VpsHal_Handle handle)
{
    Int32 retVal = BSP_EFAIL;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    /* Decrement the open count */
    if (dispcOvlyObj->openCnt > 0U)
    {
        dispcOvlyObj->openCnt--;
        retVal = BSP_SOK;
    }

    return (retVal);
}

VpsHal_Handle VpsHal_dssOvlyGetHandle(UInt32 halId)
{
    UInt32        cnt;
    VpsHal_Handle handle = NULL;

    /* Check if instance number is valid */
    GT_assert(VpsHalTrace, halId < VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX);

    for (cnt = 0; cnt < VPSHAL_DSS_DISPC_OVLY_MAX_INST; cnt++)
    {
        /* Return the matching instance handle */
        if (halId == gDispcOvlyHalObj[cnt].halId)
        {
            /* Return only if already opened */
            if (0U != gDispcOvlyHalObj[cnt].openCnt)
            {
                handle = (VpsHal_Handle) & gDispcOvlyHalObj[cnt];
            }
            break;
        }
    }

    return (handle);
}

/**
 *  VpsHal_dssOvlyGetIRQStat
 *  \brief This function will give the details of the interrupt signals
 *  that are currently being set.in DSS5 and DSS6 the interrupts status
 *  registers are different, so to have a common core DSS6 interrupts are
 *  converted into DSS5 int status.
 *
 *  This function will give the details of the interrupt being set
 *
 *  \param            void
 *
 *  \return           Returns List of interrupts being set on success else zero.
 */
UInt64 VpsHal_dssOvlyGetIrqStat(void)
{
    UInt64 irqStatus    = 0;
    UInt32 irqStatusTop = 0, irqStatusModu = 0;

    irqStatusTop = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQSTATUS);

    if ((irqStatusTop & DSS_DISPC_IRQSTATUS_VP1_IRQ_MASK) ==
        DSS_DISPC_IRQSTATUS_VP1_IRQ_MASK)
    {
        irqStatusModu = HW_RD_REG32(SOC_DISPC_VP1_BASE + DSS_VP_IRQSTATUS);
        if ((irqStatusModu & DSS_VP_IRQSTATUS_VPVSYNC_IRQ_MASK) ==
            DSS_VP_IRQSTATUS_VPVSYNC_IRQ_MASK)
        {
            irqStatus |= 0x2U;
        }
        if ((irqStatusModu & DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ_MASK) ==
            DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ_MASK)
        {
            irqStatus |= 0x4000U;
        }
        if ((irqStatusModu &
             DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ_MASK) ==
            DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ_MASK)
        {
            irqStatus |= 0x20U;
        }
        if ((irqStatusModu &
             DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ_MASK) ==
            DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ_MASK)
        {
            irqStatus |= 0x400000000U;
        }
    }

    if ((irqStatusTop & DSS_DISPC_IRQSTATUS_VID1_IRQ_MASK) ==
        DSS_DISPC_IRQSTATUS_VID1_IRQ_MASK)
    {
        irqStatusModu = HW_RD_REG32(SOC_DISPC_VID1_BASE + DSS_VID_IRQSTATUS);

        if ((irqStatusModu & DSS_VID_IRQSTATUS_VIDBUFFERUNDERFLOW_IRQ_MASK) ==
            DSS_VID_IRQSTATUS_VIDBUFFERUNDERFLOW_IRQ_MASK)
        {
            irqStatus |= 0x400U;
        }
    }

    if ((irqStatusTop & DSS_DISPC_IRQSTATUS_VID2_IRQ_MASK) ==
        DSS_DISPC_IRQSTATUS_VID2_IRQ_MASK)
    {
        irqStatusModu = HW_RD_REG32(SOC_DISPC_VID2_BASE + DSS_VID_IRQSTATUS);

        if ((irqStatusModu & DSS_VID_IRQSTATUS_VIDBUFFERUNDERFLOW_IRQ_MASK) ==
            DSS_VID_IRQSTATUS_VIDBUFFERUNDERFLOW_IRQ_MASK)
        {
            irqStatus |= 0x1000U;
        }
    }

    if ((irqStatusTop & DSS_DISPC_IRQSTATUS_GFX1_IRQ_MASK) ==
        DSS_DISPC_IRQSTATUS_GFX1_IRQ_MASK)
    {
        irqStatusModu = HW_RD_REG32(SOC_DISPC_GFX1_BASE + DSS_GFX_IRQSTATUS);

        if ((irqStatusModu & DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_MASK) ==
            DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ_MASK)
        {
            irqStatus |= 0x40U;
        }
    }

    if ((irqStatusTop & DSS_DISPC_IRQSTATUS_WB_IRQ_MASK) ==
        DSS_DISPC_IRQSTATUS_WB_IRQ_MASK)
    {
        irqStatusModu = HW_RD_REG32(SOC_DISPC_WB_BASE + DSS_WB_IRQSTATUS);

        if ((irqStatusModu & DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_MASK) ==
            DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ_MASK)
        {
            irqStatus |= 0x02000000U;
        }

        if ((irqStatusModu & DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_MASK) ==
            DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ_MASK)
        {
            irqStatus |= 0x04000000U;
        }

        if ((irqStatusModu & DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ_MASK) ==
            DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ_MASK)
        {
            irqStatus |= 0x00800000U;
        }

        if ((irqStatusModu & DSS_WB_IRQENABLE_WBREGIONBASEDEVENT_EN_MASK) ==
            DSS_WB_IRQENABLE_WBREGIONBASEDEVENT_EN_MASK)
        {
            irqStatus |= 0x200000000U;
        }

        if ((irqStatusModu & DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ_MASK) ==
            DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ_MASK)
        {
            irqStatus |= 0x100000000U;
        }
    }

    return irqStatus;
}

/**
 *  VpsHal_dssOvlySetGoBit
 *  \brief GO command for the Overlay output. It is used to
 *   synchronized the pipelines (graphics and/or video ones)
 *   associated with the overlay output..
 *
 *  This function will Set the Go Bit of the overlay
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetGoBit(UInt32 ovlyId)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;

    if (ovlyId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* No separate Go bit for WB pipeline - WB can only be connected to
         *LCD1. */
        if ((ovlyId == VPSHAL_DSS_DISPC_LCD1) ||
            (ovlyId == VPSHAL_DSS_DISPC_WBOVR))
        {
            regVal = HW_RD_REG32(SOC_DISPC_VP1_BASE + DSS_VP_CONTROL);
            HW_SET_FIELD32(regVal, DSS_VP_CONTROL_GOBIT,
                           DSS_VP_CONTROL_GOBIT_UFPSR);
            HW_WR_REG32(SOC_DISPC_VP1_BASE + DSS_VP_CONTROL, regVal);
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Not valid for this LCD instance\r\n");
            retVal = BSP_EBADARGS;
        }
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyGetGoBit
 *  \brief Returns the Value of the GoBit.
 *
 *  This function will Return the status of the Go bit.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param bitVal           Pointer to a variable, varialbe is set to 0 if the
 *                          previous applied configuration by the software is
 *                          accepted by hardware.sets to 1 if Its not accepted.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetGoBit(VpsHal_Handle handle, UInt32 *bitVal)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != bitVal));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if (dispcOvlyObj->halId == VPSHAL_DSS_DISPC_LCD1)
        {
            regVal  = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpControl);
            *bitVal = HW_GET_FIELD(regVal, DSS_VP_CONTROL_GOBIT);
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Not valid for this LCD instance\r\n");
            retVal = BSP_EBADARGS;
        }
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyEnable
 *  \brief Configures the Video/Gfx pipeline params related to overlay.
 *
 *  This function will enable or disable the overlay
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                                  function
 *  \param enable           enable or disable the Overlay
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnable(VpsHal_Handle handle,
                           UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        if (dispcOvlyObj->halId == VPSHAL_DSS_DISPC_LCD1)
        {
            regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpControl);
            HW_SET_FIELD32(regVal, DSS_VP_CONTROL_VPENABLE,
                           enable);
            HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpControl, regVal);
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Not valid for this LCD instance\r\n");
            retVal = BSP_EBADARGS;
        }
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyPipeConfig
 *  \brief Configures the Video/Gfx pipeline params related to overlay.
 *
 *  This function will configure the pipeline parameters like to which overlay
 *  the pipeline should be connected to, z-order of displays, globalalpha and
 *  premultiply alpha
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param pipeCfg          Pointer to the Overlay Pipe config structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyPipeConfig(VpsHal_Handle                     handle,
                               const Vps_DssDispcOvlyPipeConfig *pipeCfg)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != pipeCfg));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (pipeCfg->pipeLine >= VPS_DSS_DISPC_PIPE_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Pipeline\r\n");
        retVal = BSP_EBADARGS;
    }

    if (pipeCfg->zorder > DSS_VID_ATTRIBUTES_ZORDER_ZORDER2)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Z-order value \r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        halDispcOvlyPipeConfZorder(handle, pipeCfg->pipeLine, pipeCfg->zorder);

        halDispcOvlyPipeSetGlobalAlpha(handle, pipeCfg->pipeLine,
                                       pipeCfg->globalAlpha);

        halDispcOvlyPipeSetPreMulAlpha(handle, pipeCfg->pipeLine,
                                       pipeCfg->preMultiplyAlpha);

        halDispcOvlyPipeSetChannelOut(handle, pipeCfg->pipeLine);
    }

    return retVal;
}

/**
 *  VpsHal_dssOvlyPanelConf
 *  \brief Configures the overlay.
 *
 *  This function will configure the pipeline parameters like to which overlay
 *  the pipeline should be connected to, z-order of displays, globalalpha and
 *  premultiply alpha
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param pipeConf         Pointer to the Overlay Pipe config structure.
 *                          This parameter should not be NULL.
 *  \param pipe             This specifies to which pipe this configuration
 *                           should be applied to
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyPanelConf(
    VpsHal_Handle handle,
    const Vps_DssDispcOvlyPanelConfig *
    panelConfig)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != panelConfig));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        halDispcOvlyPanelColorKeyConf(handle, panelConfig->colorKeyEnable,
                                      panelConfig->colorKeySel);

        halDispcOvlyPanelSetTransColorKey(handle,
                                          panelConfig->transColorKey,
                                          panelConfig->transColorKey);

        if (VPSHAL_DSS_DISPC_LCD1 == dispcOvlyObj->halId)
        {
            halDispcOvlyPanelDeltaLinesConf(handle,
                                            panelConfig->deltaLinesPerPanel);
        }

        halDispcOvlySetBgColor(handle,
                               panelConfig->backGroundColor);

        halDispcOvlyOptimizationConf(handle,
                                     panelConfig->ovlyOptimization);
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdAdvDispConfig
 *  \brief Configures the Advance LCD Overlay Display Params.
 *
 *  This function will configures Advance LCD Overlays Display parameters, like
 *  Stall Mode, number of data lines, fid sequence.
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTdmConfig     Pointer to the LCD Overlay Advance Display Param
 *                          structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdAdvDispConfig(
    VpsHal_Handle handle,
    const Vps_DssDispcLcdAdvDisplayConfig *
    lcdAdvDisplay)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lcdAdvDisplay));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not supported for instance other \
            than LCD1\r\n");
        retVal = BSP_EBADARGS;
    }
    if (retVal == BSP_SOK)
    {
        /* write CONFIG1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpConfig);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_FIDFIRST, lcdAdvDisplay->fidFirst);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BUFFERHANDSHAKE,
                       lcdAdvDisplay->buffHandCheck);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpConfig, regVal);

        /* write CONTROL1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpControl);
        HW_SET_FIELD32(regVal, DSS_VP_CONTROL_STALLMODE,
                       lcdAdvDisplay->stallModeEnable);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpControl, regVal);
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdTdmConfig
 *  \brief Configures the LCD TDM(Time division multiplexing) Params.
 *
 *  This function will configures LCD Overlay's TDM parameters, like Number of
 *  bits per each cycle, bit alignment for all pixels.
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTdmConfig     Pointer to the LCD Overlay TDM Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdTdmConfig(
    VpsHal_Handle handle,
    const Vps_DssDispcAdvLcdTdmConfig *
    lcdTdmConfig)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lcdTdmConfig));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not supported for instance other than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }
    if (retVal == BSP_SOK)
    {
        /* write DATA1_CYCLE1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dataCycle1);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_NBBITSPIXEL1,
                       lcdTdmConfig->noBitsPixel1Cycle1);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL1,
                       lcdTdmConfig->bitAlignPixel1Cycle1);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_NBBITSPIXEL2,
                       lcdTdmConfig->noBitsPixel2Cycle1);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL2,
                       lcdTdmConfig->bitAlignPixel2Cycle1);
        HW_WR_REG32(dispcOvlyObj->regOffset.dataCycle1, regVal);

        /* write DATA1_CYCLE2 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dataCycle2);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_NBBITSPIXEL1,
                       lcdTdmConfig->noBitsPixel1Cycle2);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL1,
                       lcdTdmConfig->bitAlignPixel1Cycle2);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_NBBITSPIXEL2,
                       lcdTdmConfig->noBitsPixel2Cycle2);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL2,
                       lcdTdmConfig->bitAlignPixel2Cycle2);
        HW_WR_REG32(dispcOvlyObj->regOffset.dataCycle2, regVal);

        /* write DATA1_CYCLE3 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dataCycle3);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_NBBITSPIXEL1,
                       lcdTdmConfig->noBitsPixel1Cycle3);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL1,
                       lcdTdmConfig->bitAlignPixel1Cycle3);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_NBBITSPIXEL2,
                       lcdTdmConfig->noBitsPixel2Cycle3);
        HW_SET_FIELD32(regVal, DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL2,
                       lcdTdmConfig->bitAlignPixel2Cycle3);
        HW_WR_REG32(dispcOvlyObj->regOffset.dataCycle3, regVal);

        /* write CONTROL1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpControl);
        HW_SET_FIELD32(regVal, DSS_VP_CONTROL_TDMUNUSEDBITS,
                       lcdTdmConfig->tdmUnusedBits);
        HW_SET_FIELD32(regVal, DSS_VP_CONTROL_TDMCYCLEFORMAT,
                       lcdTdmConfig->tdmCycleFormat);
        HW_SET_FIELD32(regVal, DSS_VP_CONTROL_TDMPARALLELMODE,
                       lcdTdmConfig->tdmParallelMode);
        HW_SET_FIELD32(regVal, DSS_VP_CONTROL_TDMENABLE,
                       lcdTdmConfig->tdmEnable);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpControl, regVal);
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdConfLineNum
 *  \brief Set the LineNumber at which the interrupt should be generated
 *
 *  This function will configures set the Line number in the overlay
 *  when the display reaches this line it will generate the Interrupt.
 *
 *  \param handle        Valid handle returned by VpsHal_dssOvlyOpen
 *                       function
 *  \param lineNum       Line Number that should be programmed in the register .
 *
 *  \return              Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdConfLineNum(
    VpsHal_Handle handle,
    UInt32        lineNum)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId != VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(VpsHalTrace, GT_ERR,
                  "Not applicable for Hal instance other than LCD1\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        HW_WR_REG32(SOC_DISPC_VP1_BASE + DSS_VP_LINE_NUMBER, lineNum);
    }

    return retVal;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_010)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-815) DOX_REQ_TAG(PDK-816) DOX_REQ_TAG(PDK-817)
 *          DOX_REQ_TAG(PDK-818) DOX_REQ_TAG(PDK-819) DOX_REQ_TAG(PDK-820)
 *          DOX_REQ_TAG(PDK-821)
 */
/**
 *  VpsHal_dssOvlyLcdSetTiming
 *  \brief Configures the LCD Timing Params.
 *
 *  This function will configures LCD Overlay Timing Parameters, like front
 *  porch, back porch , divider values
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdTimingParm    Pointer to the LCD Timing Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSetTiming(
    VpsHal_Handle handle,
    VpsHal_DssDispcLcdTimingParam *
    lcdTimingParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal, numStdModes, modeCnt;
    VpsHal_DssDispcLcdTimingParam      vpTimingParm;
    VpsHal_DssDispcLcdBlankTimingParam lcdBlankTimingParm;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lcdTimingParm));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for instance other \
                        than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }

    if (FVID2_STD_CUSTOM != lcdTimingParm->standard)
    {
        numStdModes = sizeof (gDssStdModeInfo) / sizeof (Fvid2_ModeInfo);

        for (modeCnt = 0U; modeCnt < numStdModes; modeCnt++)
        {
            if (lcdTimingParm->standard == gDssStdModeInfo[modeCnt].standard)
            {
                vpTimingParm.width  = gDssStdModeInfo[modeCnt].width;
                vpTimingParm.height = gDssStdModeInfo[modeCnt].height;
                lcdBlankTimingParm.hFrontPorch =
                    gDssStdModeInfo[modeCnt].hFrontPorch;
                lcdBlankTimingParm.hBackPorch =
                    gDssStdModeInfo[modeCnt].hBackPorch;
                lcdBlankTimingParm.hSyncLen =
                    gDssStdModeInfo[modeCnt].hSyncLen;
                lcdBlankTimingParm.vFrontPorch =
                    gDssStdModeInfo[modeCnt].vFrontPorch;
                lcdBlankTimingParm.vBackPorch =
                    gDssStdModeInfo[modeCnt].vBackPorch;
                lcdBlankTimingParm.vSyncLen =
                    gDssStdModeInfo[modeCnt].vSyncLen;

                /* Width and height is copied as this will be used by core for
                 * standard resolutions. */
                lcdTimingParm->width  = gDssStdModeInfo[modeCnt].width;
                lcdTimingParm->height = gDssStdModeInfo[modeCnt].height;

                if (gDssStdModeInfo[modeCnt].scanFormat == FVID2_SF_INTERLACED)
                {
                    vpTimingParm.scanFormat = 1;
                }
                else
                {
                    vpTimingParm.scanFormat = 0;
                }

                break;
            }
        }
        if (modeCnt == numStdModes)
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Mode not supported \r\n");
            retVal = BSP_EBADARGS;
        }
    }
    else
    {
        vpTimingParm.width  = lcdTimingParm->width;
        vpTimingParm.height = lcdTimingParm->height;
        lcdBlankTimingParm.hFrontPorch = lcdTimingParm->hFrontPorch;
        lcdBlankTimingParm.hBackPorch  = lcdTimingParm->hBackPorch;
        lcdBlankTimingParm.hSyncLen    = lcdTimingParm->hSyncLen;
        lcdBlankTimingParm.vFrontPorch = lcdTimingParm->vFrontPorch;
        lcdBlankTimingParm.vBackPorch  = lcdTimingParm->vBackPorch;
        lcdBlankTimingParm.vSyncLen    = lcdTimingParm->vSyncLen;
        if (lcdTimingParm->scanFormat == FVID2_SF_INTERLACED)
        {
            vpTimingParm.scanFormat = 1;
        }
        else
        {
            vpTimingParm.scanFormat = 0;
        }
    }
    if (retVal == BSP_SOK)
    {
        /* write TIMING_H1 and TIMING_V1 fields */
        retVal = VpsHal_dssOvlyLcdSetBlankTiming(handle, &lcdBlankTimingParm);

        /* write width and height */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.panelSize);
        HW_SET_FIELD32(regVal, DSS_VP_SIZE_SCREEN_LPP, (vpTimingParm.height - 1));
        HW_SET_FIELD32(regVal, DSS_VP_SIZE_SCREEN_PPL, (vpTimingParm.width - 1));
        HW_WR_REG32(dispcOvlyObj->regOffset.panelSize, regVal);

        /* set scan format */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpConfig);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_OUTPUTMODEENABLE,
                       vpTimingParm.scanFormat);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpConfig, regVal);
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdGetBlankTiming
 *  \brief returns the LCD Blank Timing Params.
 *
 *  This function will return the currently configured LCD Overlay Blank Timing
 *  Parameters, like front porch, back porch, sync values.
 *  \param handle               Valid handle returned by VpsHal_dssOvlyOpen
 *                              function
 *  \param lcdBlankTimingParm   Pointer to the LCD Blanking Timing Param
 *                              structure. This parameter should not be NULL.
 *  \return                     Returns BSP_SOK on success else returns error
 */
Int32 VpsHal_dssOvlyLcdGetBlankTiming(
    VpsHal_Handle handle,
    VpsHal_DssDispcLcdBlankTimingParam *
    lcdBlankTimingParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;
    UInt32 hBlankMultFact, hBlankDivFact;
    UInt32 tempFieldVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdBlankTimingParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for instance other \
                        than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* read TIMING_H1 fields */
        halDispcOvlyGetTdmHblankFact(dispcOvlyObj, &hBlankMultFact,
                                     &hBlankDivFact);

        regVal       = HW_RD_REG32(dispcOvlyObj->regOffset.lcdTimingH);
        tempFieldVal = HW_GET_FIELD(regVal, DSS_VP_TIMING_H_HBP);
        lcdBlankTimingParm->hBackPorch =
            ((tempFieldVal + 1U) * hBlankDivFact) /
            hBlankMultFact;
        tempFieldVal = HW_GET_FIELD(regVal, DSS_VP_TIMING_H_HFP);
        lcdBlankTimingParm->hFrontPorch =
            ((tempFieldVal + 1U) * hBlankDivFact) /
            hBlankMultFact;
        tempFieldVal = HW_GET_FIELD(regVal, DSS_VP_TIMING_H_HSW);
        lcdBlankTimingParm->hSyncLen = ((tempFieldVal + 1U) * hBlankDivFact) /
                                       hBlankMultFact;

        /* read TIMING_V1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.lcdTimingV);
        lcdBlankTimingParm->vBackPorch = HW_GET_FIELD(regVal,
                                                      DSS_VP_TIMING_V_VBP);
        lcdBlankTimingParm->vFrontPorch = HW_GET_FIELD(regVal,
                                                       DSS_VP_TIMING_V_VFP);
        lcdBlankTimingParm->vSyncLen = HW_GET_FIELD(regVal,
                                                    DSS_VP_TIMING_V_VSW) + 1U;
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_013)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-811) DOX_REQ_TAG(PDK-812) DOX_REQ_TAG(PDK-813)
 *          DOX_REQ_TAG(PDK-814)
 */
/**
 *  VpsHal_dssOvlyLcdSetBlankTiming
 *  \brief Configures the LCD Blank Timing Params.
 *
 *  This function will configures LCD Overlay Blank Timing Parameters
 *  like front porch, back porch, sync values.
 *  \param handle               Valid handle returned by VpsHal_dssOvlyOpen
 *                              function
 *  \param lcdBlankTimingParm   Pointer to the LCD Blanking Timing Param
 *                              structure. This parameter should not be NULL.
 *  \return                     Returns BSP_SOK on success else returns error
 */
Int32 VpsHal_dssOvlyLcdSetBlankTiming(
    VpsHal_Handle handle,
    const VpsHal_DssDispcLcdBlankTimingParam *
    lcdBlankTimingParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;
    UInt32 hBlankMultFact, hBlankDivFact;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);
    GT_assert(VpsHalTrace, NULL != lcdBlankTimingParm);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for instance other \
                        than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        retVal = halDispcOvlyGetTdmHblankFact(dispcOvlyObj, &hBlankMultFact,
                                              &hBlankDivFact);

        retVal += halDispcOvlyValidateLcdBlankTiming(lcdBlankTimingParm,
                                                     hBlankMultFact,
                                                     hBlankDivFact);
    }

    if (retVal == BSP_SOK)
    {
        /* write TIMING_H1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.lcdTimingH);
        HW_SET_FIELD32(
            regVal,
            DSS_VP_TIMING_H_HBP,
            (((lcdBlankTimingParm->hBackPorch * hBlankMultFact) / hBlankDivFact)
             - 1U));
        HW_SET_FIELD32(
            regVal,
            DSS_VP_TIMING_H_HFP,
            (((lcdBlankTimingParm->hFrontPorch * hBlankMultFact) /
              hBlankDivFact) - 1U));
        HW_SET_FIELD32(
            regVal,
            DSS_VP_TIMING_H_HSW,
            (((lcdBlankTimingParm->hSyncLen * hBlankMultFact) /
              hBlankDivFact) - 1U));
        HW_WR_REG32(dispcOvlyObj->regOffset.lcdTimingH, regVal);

        /* write TIMING_V1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.lcdTimingV);
        HW_SET_FIELD32(
            regVal,
            DSS_VP_TIMING_V_VBP,
            lcdBlankTimingParm->vBackPorch);
        HW_SET_FIELD32(
            regVal,
            DSS_VP_TIMING_V_VFP,
            lcdBlankTimingParm->vFrontPorch);
        HW_SET_FIELD32(
            regVal,
            DSS_VP_TIMING_V_VSW,
            lcdBlankTimingParm->vSyncLen - 1U);
        HW_WR_REG32(dispcOvlyObj->regOffset.lcdTimingV, regVal);
    }

    return (retVal);
}

Int32 VpsHal_dssOvlyUpdatePanelSizeSdVenc(VpsHal_Handle handle)
{
    /* Lines per pixel in VP should increased by 2 pixels for sd venc display
     * in tda3xx (errata: i873) */
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal, pplVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.panelSize);
    pplVal = HW_GET_FIELD(regVal, DSS_VP_SIZE_SCREEN_PPL);
    HW_SET_FIELD32(regVal, DSS_VP_SIZE_SCREEN_PPL, (pplVal + 2U));
    HW_WR_REG32(dispcOvlyObj->regOffset.panelSize, regVal);

    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdSetClkDivisors
 *  \brief Configures the LCD Divisor Params - NA for ADAS-Low.
 *
 *  This function will configures LCD and PCD divisor values for
 *  the overlays. Resultant pixel clock is as per formula
 *  DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdDivisorParm    Pointer to the LCD Divisor Param structure,
 *                           VpsHal_DssDispcLcdDivisorParam.This parameter
 * should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSetClkDivisors(
    VpsHal_Handle handle,
    const VpsHal_DssDispcLcdDivisorParam *
    lcdDivisorParm)
{
    Int32 retVal = BSP_SOK;

    /* Stub for ADAS-Low */
    return retVal;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_011)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-804) DOX_REQ_TAG(PDK-805) DOX_REQ_TAG(PDK-806)
 */
/**
 *  VpsHal_dssOvlyLcdOutputConf
 *  \brief Configures the data format and interface width of LCD Overlay,
 *
 *  This function will configure Output parameters of LCD overlay.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdOutputConf(
    VpsHal_Handle handle,
    const VpsHal_DssDispcLcdOutputParam *
    lcdOutParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lcdOutParm));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for instance other \
                            than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write CONTROL1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpControl);
        HW_SET_FIELD32(regVal, DSS_VP_CONTROL_DATALINES,
                       lcdOutParm->videoIfWidth);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpControl, regVal);

        if (lcdOutParm->dvoFormat == VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
        {
            halDispcOvlyBT656_1120Conf(handle,
                                       (UInt32) VPS_DCTRL_DVOFMT_BT656_EMBSYNC,
                                       (UInt32) TRUE);
        }
        else if (lcdOutParm->dvoFormat == VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
        {
            halDispcOvlyBT656_1120Conf(handle,
                                       (UInt32) VPS_DCTRL_DVOFMT_BT1120_EMBSYNC,
                                       (UInt32) TRUE);
        }
        else if (lcdOutParm->dvoFormat == VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC)
        {
            halDispcOvlyBT656_1120Conf(
                handle,
                (UInt32)
                VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC,
                (UInt32) FALSE);
        }
        else
        {
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid DVO format \r\n");
            retVal = BSP_EBADARGS;
        }
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdSignalPolarityConf
 *  \brief Configures the Polarity of LCD Overlay signals(hsync,vsync,pclk,DE).
 *
 *  This function will configure Signal parameters like polarity of
 *  Pixel clock, Hsync, Vsync and active video.
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdSignalPolarityConf(
    VpsHal_Handle handle,
    VpsHal_DssDispcLcdSignalPolarityParam *
    lcdSignalPolParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lcdSignalPolParm));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for instance \
                other than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }

    /*High polarity for interface is low for LCD and
     *vice versa*/
    if (lcdSignalPolParm->vsPolarity ==
        VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->vsPolarity =
            VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->vsPolarity =
            VPS_DCTRL_POLARITY_ACT_HIGH;
    }
    if (lcdSignalPolParm->hsPolarity ==
        VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->hsPolarity =
            VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->hsPolarity =
            VPS_DCTRL_POLARITY_ACT_HIGH;
    }
    if (lcdSignalPolParm->pixelClkPolarity == VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->pixelClkPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    }
    if (lcdSignalPolParm->dvoActVidPolarity == VPS_DCTRL_POLARITY_ACT_HIGH)
    {
        lcdSignalPolParm->dvoActVidPolarity = VPS_DCTRL_POLARITY_ACT_LOW;
    }
    else
    {
        lcdSignalPolParm->dvoActVidPolarity = VPS_DCTRL_POLARITY_ACT_HIGH;
    }

    if (retVal == BSP_SOK)
    {
        /* write POL_FREQ1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.polFreq);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_IEO,
                       lcdSignalPolParm->dvoActVidPolarity);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_IPC,
                       lcdSignalPolParm->pixelClkPolarity);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_IHS,
                       lcdSignalPolParm->hsPolarity);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_IVS,
                       lcdSignalPolParm->vsPolarity);
        HW_WR_REG32(dispcOvlyObj->regOffset.polFreq, regVal);
    }

    return retVal;
}

/**
 *  VpsHal_dssOvlyLcdAdvSignalConf
 *  \brief Configures the LCD Overlay signal Params.
 *
 *  This function will configure Advance Signal parameters like polarity of
 *  Pixel clock, Hsync, Vsync data sampling at raising edge or falling edge
 *
 *  \param handle           Valid handle returned by VpsHal_dssOvlyOpen
 *                          function
 *  \param lcdSignalParm    Pointer to the Advance signal Param structure.
 *                          This parameter should not be NULL.
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyLcdAdvSignalConf(
    VpsHal_Handle handle,
    const Vps_DssDispcLcdAdvSignalConfig *
    lcdSignalParm)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));
    GT_assert(VpsHalTrace, (NULL != lcdSignalParm));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not supported for instance other \
                    than LCD1 \r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* write POL_FREQ1 fields */
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.polFreq);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_ALIGN, lcdSignalParm->hVAlign);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_ONOFF,
                       lcdSignalParm->hVClkControl);
        HW_SET_FIELD32(regVal, DSS_VP_POL_FREQ_RF, lcdSignalParm->hVClkRiseFall);
        HW_WR_REG32(dispcOvlyObj->regOffset.polFreq, regVal);
    }

    return retVal;
}

/**
 *  VpsHal_dssOvlyEnableIntr
 *  \brief This function will Enable the Vync Interrupt of a particular Overlay
 *
 *  This function will Enable the interrupts related to particular overlay
 *
 *  \param     ovlHalId - Overlay HAL ID
 *
 *  \param     enable - enable or disable the interrupt
 *                  (1 to enable and 0 to disable)
 *
 *  \return    Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnableIntr(UInt32 ovlHalId, UInt32 enable)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;
    UInt32 irqEnableSetClearOffset = 0;

    if (ovlHalId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if ((enable != 0U) && (enable != 1U))
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid argument \r\n");
        retVal = BSP_EBADARGS;
    }
    if (retVal == BSP_SOK)
    {
        if(enable == 0)
        {
            irqEnableSetClearOffset = 4U;
        }
        switch (ovlHalId)
        {
            case VPSHAL_DSS_DISPC_LCD1:

                HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET +
                                irqEnableSetClearOffset),
                    ((UInt32) 1U <<  DSS_DISPC_IRQENABLE_SET_VP1_IRQ_SHIFT));

                /* For Programmed Line number interrupt need to enable a module
                **/
                HW_WR_FIELD32((SOC_DISPC_VP1_BASE + DSS_VP_CONTROL),
                              DSS_VP_CONTROL_VPPROGLINENUMBERMODULO,
                              enable);

                regVal = HW_RD_REG32(SOC_DISPC_VP1_BASE + DSS_VP_IRQENABLE);
                HW_SET_FIELD32(regVal, DSS_VP_IRQENABLE_VPVSYNC_EN, enable);
                HW_SET_FIELD32(regVal, DSS_VP_IRQENABLE_VPSYNCLOST_EN, enable);
                HW_SET_FIELD32(regVal,
                               DSS_VP_IRQENABLE_VPPROGRAMMEDLINENUMBER_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_VP_IRQENABLE_VPVSYNC_ODD_EN, enable);
                HW_WR_REG32((SOC_DISPC_VP1_BASE + DSS_VP_IRQENABLE), regVal);


                break;

            case VPSHAL_DSS_DISPC_WBOVR:

                regVal = HW_RD_REG32(
                    SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET);
                HW_SET_FIELD32(regVal, DSS_DISPC_IRQENABLE_SET_WB_IRQ, enable);
                HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQENABLE_SET),
                            regVal);

                regVal = HW_RD_REG32(SOC_DISPC_WB_BASE + DSS_WB_IRQENABLE);
                HW_SET_FIELD32(regVal, DSS_WB_IRQENABLE_WBBUFFEROVERFLOW_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQENABLE_WBUNCOMPLETEERROR_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQENABLE_WBFRAMEDONE_EN,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ,
                               enable);
                HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ,
                               enable);
                HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQENABLE), regVal);

                break;
            default:
                retVal = BSP_EFAIL;
                break;
        }
    }
    return retVal;
}

/**
 *  VpsHal_dssOvlyClearIrq
 *  \brief This function will clear the Interrupts.
 *
 *  This function will clear the list of interrupts
 *
 *  \param             irqstatus - list of interrupts to be cleared
 *
 *  \return            Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyClearIrq(UInt64 irqStatus)
{
    Int32  retVal = BSP_SOK;
    UInt32 regVal;

    /* VP1 IRQ's */
    if (((irqStatus & 0x2U) == 0x2U) || ((irqStatus & 0x20U) == 0x20U) ||
        ((irqStatus & 0x4000U) == 0x4000U) ||
        ((irqStatus & 0x400000000U) == 0x400000000U))
    {
        if ((irqStatus & 0x2U) == 0x2U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_VP_IRQSTATUS_VPVSYNC_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_VP1_BASE + DSS_VP_IRQSTATUS), regVal);
        }

        if ((irqStatus & 0x20U) == 0x20U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ,
                           1);
            HW_WR_REG32((SOC_DISPC_VP1_BASE + DSS_VP_IRQSTATUS), regVal);
        }

        if ((irqStatus & 0x4000U) == 0x4000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_VP1_BASE + DSS_VP_IRQSTATUS), regVal);
        }
        if ((irqStatus & 0x400000000U) == 0x400000000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_VP1_BASE + DSS_VP_IRQSTATUS), regVal);
        }
        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_DISPC_IRQSTATUS_VP1_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQSTATUS), regVal);
    }

    /* VID1 IRQ's */
    if ((irqStatus & 0x400U) == 0x400U)
    {
        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_VID_IRQSTATUS_VIDBUFFERUNDERFLOW_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_VID1_BASE + DSS_VID_IRQSTATUS), regVal);

        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_DISPC_IRQSTATUS_VID1_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQSTATUS), regVal);
    }

    /* VID2 IRQ's */
    if ((irqStatus & 0x1000U) == 0x1000U)
    {
        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_VID_IRQSTATUS_VIDBUFFERUNDERFLOW_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_VID2_BASE + DSS_VID_IRQSTATUS), regVal);

        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_DISPC_IRQSTATUS_VID1_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQSTATUS), regVal);
    }

    /* GFX1 IRQ */
    if ((irqStatus & 0x40U) == 0x40U)
    {
        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_GFX_IRQSTATUS_GFXBUFFERUNDERFLOW_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_GFX1_BASE + DSS_GFX_IRQSTATUS), regVal);

        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_DISPC_IRQSTATUS_GFX1_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQSTATUS), regVal);
    }

    /* WB IRQ */
    if (((irqStatus & 0x100000000U) == 0x100000000U) ||
        ((irqStatus & 0x02000000U) == 0x02000000U) ||
        ((irqStatus & 0x04000000U) == 0x04000000U) ||
        ((irqStatus & 0x00800000U) == 0x00800000U) ||
        ((irqStatus & 0x200000000U) == 0x200000000U))
    {
        if ((irqStatus & 0x02000000U) == 0x02000000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBBUFFEROVERFLOW_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQSTATUS), regVal);
        }

        if ((irqStatus & 0x04000000U) == 0x04000000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBUNCOMPLETEERROR_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQSTATUS), regVal);
        }

        if ((irqStatus & 0x00800000U) == 0x00800000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBFRAMEDONE_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQSTATUS), regVal);
        }

        if ((irqStatus & 0x100000000U) == 0x100000000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBFRAMESYNC_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQSTATUS), regVal);
        }

        if ((irqStatus & 0x200000000U) == 0x200000000U)
        {
            regVal = 0;
            HW_SET_FIELD32(regVal, DSS_WB_IRQSTATUS_WBREGIONBASEDEVENT_IRQ, 1);
            HW_WR_REG32((SOC_DISPC_WB_BASE + DSS_WB_IRQSTATUS), regVal);
        }

        regVal = 0;
        HW_SET_FIELD32(regVal, DSS_DISPC_IRQSTATUS_RAW_WB_IRQ, 1);
        HW_WR_REG32((SOC_DISPC_COMMON_BASE + DSS_DISPC_IRQSTATUS), regVal);
    }

    return retVal;
}

/**
 *  VpsHal_dssOvlySetParallelMux
 *  \brief Sets the Parallel Mux for DPI1 output - NA for TDA3xx
 *
 *  This function will Set Parallel Mux for DPI1 Output - NA for TDA3xx
 *
 *  \param                  ovlyId - Overlay HAL ID
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetParallelMux(UInt32 ovlyId)
{
    /* Stub for ADAS-Low */
    Int32 retVal = BSP_SOK;

    return retVal;
}

Int32 VpsHal_dssOvlySetSize(UInt32 ovlyId, UInt32 ovlyWidth, UInt32 ovlyHeight)
{
    /* Stub for ADAS-Low */
    Int32 retVal = BSP_SOK;

    return (retVal);
}

/**
 *  Vpshal_dssOvlySetTvRes
 *  \brief sets the resolution of the TV overlay
 *
 *  This function will set the resolution of the TV overlay
 *
 * \return Returns BSP_SOK on success else returns error value
 *
 */
Int32 Vpshal_dssOvlySetTvRes(UInt32 height, UInt32 width)
{
    /* Stub for ADAS-Low */
    Int32 retVal = BSP_SOK;

    return retVal;
}

/**
 *  VpsHal_dssOvlySetLoadMode
 *  \brief Selects the Load mode for graphics pipeline
 *
 *  This function will select the load mode for graphics pipeline
 *
 *  \param loadMode     0 - Palette/Gamma Table and data are loaded every frame
 *                      1 -  Palette/Gamma Table to be loaded
 *                      2 -  Frame data only loaded every frame
 *                      3 -  Palette/Gamma Table and frame data loaded on first
 *                                 frame then switch to 0x2 (Hardware)
 *
 *  \return             Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetLoadMode(UInt32 loadMode)
{
    /* Stub for ADAS-Low */
    Int32 retVal = BSP_SOK;

    return retVal;
}

/**
 *  VpsHal_dssOvlyBypassTvGamma
 *  \brief Enable or bypass Tv Gamma Table
 *
 *  This function will enable/bypass TV gamma table
 *
 *  \param enable          0 - bypass, 1- enable
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyEnableTvGamma(UInt32 enable)
{
    /* Stub for ADAS-Low */
    Int32 retVal = BSP_SOK;

    return retVal;
}

/**
 *  VpsHal_dssOvlySetDispcMode
 *  \brief Configures the DISPC Mode
 *
 *  This function will configure the DISPC into master/slave mode
 *
 *  \param enable          1 - master, 0 - slave
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlySetDispcMode(UInt32 dispcMode)
{
    Int32 retVal = BSP_SOK;

    if (dispcMode == VPS_DCTRL_DISPC_MODE_SLAVE)
    {
        HW_WR_FIELD32(SOC_DISPC_VP1_BASE + DSS_VP_CONFIG,
                      DSS_VP_CONFIG_EXTERNALSYNCEN,
                      DSS_VP_CONFIG_EXTERNALSYNCEN_ENABLE);
    }
    else if (dispcMode == VPS_DCTRL_DISPC_MODE_MASTER)
    {
        HW_WR_FIELD32(SOC_DISPC_VP1_BASE + DSS_VP_CONFIG,
                      DSS_VP_CONFIG_EXTERNALSYNCEN,
                      DSS_VP_CONFIG_EXTERNALSYNCEN_DISABLE);
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid DISPC Mode\r\n");
        retVal = BSP_EBADARGS;
    }

    return retVal;
}

/**
 *  VpsHal_dssOvlyDpiEnable
 *  \brief Enables/Disables the DPI output
 *
 *  This function will enable or disables the DPI output.
 *
 *  \param enable          TRUE - enable, FALSE - disable
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyDpiEnable(UInt32 dpiEnable)
{
    Int32 retVal = BSP_SOK;

    if (dpiEnable == TRUE)
    {
        HW_WR_REG32(SOC_DSSREG_BASE + DSS_DSSREG_DPI_CTRL,
                    DSS_DSSREG_DPI_CTRL_ENABLE);
    }
    else if (dpiEnable == FALSE)
    {
        HW_WR_REG32(SOC_DSSREG_BASE + DSS_DSSREG_DPI_CTRL,
                    DSS_DSSREG_DPI_CTRL_ENABLE_DISABLE);
    }
    else
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid DPI option\r\n");
        retVal = BSP_EBADARGS;
    }

    return retVal;
}

/**
 *  halDispcOvlyInitInstance
 *  Initialize the DISPC OVL instance by updating the register offsets
 */
static Int32 halDispcOvlyInitInstance(VpsHal_DssDispcOvlyObj *dispcOvlyObj)
{
    Int32  retVal = BSP_SOK;
    UInt32 baseAddrOvr, baseAddrVp;

    switch (dispcOvlyObj->halId)
    {
        case VPSHAL_DSS_DISPC_LCD1:

            baseAddrOvr = SOC_DISPC_OVR1_BASE;
            baseAddrVp  = SOC_DISPC_VP1_BASE;
            dispcOvlyObj->regOffset.transColorMin[0] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MIN;
            dispcOvlyObj->regOffset.transColorMin[1] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MIN2;
            dispcOvlyObj->regOffset.transColorMax[0] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MAX;
            dispcOvlyObj->regOffset.transColorMax[1] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MAX2;
            dispcOvlyObj->regOffset.dispcOvrControl = baseAddrOvr +
                                                      DSS_OVR_CONTROL;
            dispcOvlyObj->regOffset.dispcOvrConfig = baseAddrOvr +
                                                     DSS_OVR_CONFIG;
            dispcOvlyObj->regOffset.defaultcolor[0] = baseAddrOvr +
                                                      DSS_OVR_DEFAULT_COLOR;
            dispcOvlyObj->regOffset.defaultcolor[1] = baseAddrOvr +
                                                      DSS_OVR_DEFAULT_COLOR2;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_VID1] =
                SOC_DISPC_VID1_BASE + DSS_VID_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_VID2] =
                SOC_DISPC_VID2_BASE + DSS_VID_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_GFX] =
                SOC_DISPC_GFX1_BASE + DSS_GFX_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_WB1] =
                SOC_DISPC_WB_BASE + DSS_WB_ATTRIBUTES;
            dispcOvlyObj->regOffset.panelSize = baseAddrVp +
                                                DSS_VP_SIZE_SCREEN;
            dispcOvlyObj->regOffset.dispcVpControl = baseAddrVp +
                                                     DSS_VP_CONTROL;
            dispcOvlyObj->regOffset.dispcVpConfig = baseAddrVp +
                                                    DSS_VP_CONFIG;
            dispcOvlyObj->regOffset.cprCoeff[0] = baseAddrVp +
                                                  DSS_VP_CPR_COEF_R;
            dispcOvlyObj->regOffset.cprCoeff[1] = baseAddrVp +
                                                  DSS_VP_CPR_COEF_G;
            dispcOvlyObj->regOffset.cprCoeff[2] = baseAddrVp +
                                                  DSS_VP_CPR_COEF_B;
            dispcOvlyObj->regOffset.dataCycle1 = baseAddrVp +
                                                 DSS_VP_DATA_CYCLE(0);
            dispcOvlyObj->regOffset.dataCycle2 = baseAddrVp +
                                                 DSS_VP_DATA_CYCLE(1);
            dispcOvlyObj->regOffset.dataCycle3 = baseAddrVp +
                                                 DSS_VP_DATA_CYCLE(2);
            dispcOvlyObj->regOffset.polFreq = baseAddrVp +
                                              DSS_VP_POL_FREQ;
            dispcOvlyObj->regOffset.lcdTimingH = baseAddrVp +
                                                 DSS_VP_TIMING_H;
            dispcOvlyObj->regOffset.lcdTimingV = baseAddrVp +
                                                 DSS_VP_TIMING_V;
            dispcOvlyObj->regOffset.lineStatus = baseAddrVp +
                                                 DSS_VP_LINE_STATUS;

            break;

        case VPSHAL_DSS_DISPC_LCD2:

            baseAddrOvr = SOC_DISPC_OVR2_BASE;
            dispcOvlyObj->regOffset.transColorMin[0] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MIN;
            dispcOvlyObj->regOffset.transColorMin[1] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MIN2;
            dispcOvlyObj->regOffset.transColorMax[0] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MAX;
            dispcOvlyObj->regOffset.transColorMax[1] = baseAddrOvr +
                                                       DSS_OVR_TRANS_COLOR_MAX2;
            dispcOvlyObj->regOffset.dispcOvrControl = baseAddrOvr +
                                                      DSS_OVR_CONTROL;
            dispcOvlyObj->regOffset.dispcOvrConfig = baseAddrOvr +
                                                     DSS_OVR_CONFIG;
            dispcOvlyObj->regOffset.defaultcolor[0] = baseAddrOvr +
                                                      DSS_OVR_DEFAULT_COLOR;
            dispcOvlyObj->regOffset.defaultcolor[1] = baseAddrOvr +
                                                      DSS_OVR_DEFAULT_COLOR2;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_VID1] =
                SOC_DISPC_VID1_BASE + DSS_VID_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_VID2] =
                SOC_DISPC_VID2_BASE + DSS_VID_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_GFX] =
                SOC_DISPC_GFX1_BASE +
                DSS_GFX_ATTRIBUTES;
            dispcOvlyObj->regOffset.pipeAttrib[VPSHAL_DSS_DISPC_WB1] =
                SOC_DISPC_WB_BASE +
                DSS_WB_ATTRIBUTES;

            break;

        default:
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
            retVal = BSP_EBADARGS;
            break;
    }
    if (retVal == BSP_SOK)
    {
        BspUtils_memcpy(&dispcOvlyObj->cprCoeff, &gDssCprCoeff,
                        sizeof (VpsHal_DssDispcCprCoeff));
    }

    return retVal;
}

/**
 *  halDispcOvlyOptimizationConf
 *  optimizes the fetching of the data for a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyOptimizationConf(VpsHal_Handle handle,
                                         UInt32        ovlyOptimization)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcOvrControl);
    HW_SET_FIELD32(regVal, DSS_OVR_CONTROL_OVERLAYOPTIMIZATION,
                   ovlyOptimization);
    HW_WR_REG32(dispcOvlyObj->regOffset.dispcOvrControl, regVal);
}

/**
 *  VpsHal_dssOvlyGetLineNum
 *  \brief Get the lineNumber of the overlay.
 *
 *  This function will give the current line number going on for an overlay
 *
 *  \param ovlyId           ovlyId - Overlay HAL ID
 *  \param lineNum          pointer to linenumber variable
 *
 *  \return                 Returns BSP_SOK on success else returns error value
 */
Int32 VpsHal_dssOvlyGetLineNum(UInt32  ovlyId,
                               UInt32 *lineNum)
{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != lineNum));

    if (ovlyId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* Currently this register is only available for LCD1 instance*/
        if (ovlyId == VPSHAL_DSS_DISPC_LCD1)
        {
            *lineNum = HW_RD_REG32(SOC_DISPC_VP1_BASE + DSS_VP_LINE_STATUS);
        }
        else
        {
            /* not supported for other LCD's. so returning max value so that
             * low latency will not be supported(i.e push mechanism will
             * not be applicable)*/
            *lineNum = 0x7FFU;
        }
    }

    return retVal;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_012)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-797)
 */
/**
 *  halDispcOvlySetBgColor
 *  Configures the background color of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlySetBgColor(VpsHal_Handle handle,
                                   UInt32        bgColor)
{
    UInt32 bgColor0, bgColor1;
    UInt32 bgRComp, bgGComp, bgBComp;

    /* Converting 8-bit depth to 12-bit color depth*/

    bgBComp = ((bgColor & 0xFFU) << 4);
    bgGComp = (((bgColor & 0xFF00U) >> 8) << 4);
    bgRComp = (((bgColor & 0xFF0000U) >> 16) << 4);

    bgColor0 = ((bgRComp & 0xFFU) << 24) | (bgGComp << 12) | (bgBComp);
    bgColor1 = ((bgRComp & 0xF00U) >> 8);

    halDispcOvlySet48BitBgColor(handle, bgColor0, bgColor1);
}

/**
 *  halDispcOvlySet48BitBgColor
 *  Configures the background color of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlySet48BitBgColor(VpsHal_Handle handle,
                                        UInt32        bgColor0,
                                        UInt32        bgColor1)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    HW_WR_REG32(dispcOvlyObj->regOffset.defaultcolor[0], bgColor0);
    HW_WR_REG32(dispcOvlyObj->regOffset.defaultcolor[1], bgColor1);
}

/**
 *  halDispcOvlyPanelSizeConf
 *  Configures the delta lines for a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPanelDeltaLinesConf(VpsHal_Handle handle,
                                            UInt32        deltaLinesPerPanel)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId == VPSHAL_DSS_DISPC_LCD1)
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.panelSize);
        HW_SET_FIELD32(regVal, DSS_VP_SIZE_SCREEN_DELTA_LPP, deltaLinesPerPanel);
        HW_WR_REG32(dispcOvlyObj->regOffset.panelSize, regVal);
    }
    else
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not applicable for Overlay Managers \
                other than LCD1 \r\n");
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_012)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-798) DOX_REQ_TAG(PDK-799)
 */
/**
 *  halDispcOvlyPanelSetTransColorKey
 *  Configures the transcolorkey of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPanelSetTransColorKey(VpsHal_Handle handle,
                                              UInt32        transColorKeyMin,
                                              UInt32        transColorKeyMax)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 transColorKeyMin0, transColorKeyMin1;
    UInt32 transColorKeyMax0, transColorKeyMax1;
    UInt32 transColorBComp, transColorGComp, transColorRComp;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    /* Converting 8-bit depth to 12-bit color depth*/

    transColorBComp = ((transColorKeyMin & 0xFFU) * 0x10U);
    transColorGComp = (((transColorKeyMin & 0xFF00U) >> 8) * 0x10U);
    transColorRComp = (((transColorKeyMin & 0xFF0000U) >> 16) * 0x10U);

    transColorKeyMin0 =
        ((transColorRComp &
          0xFFU) << 24) | (transColorGComp << 12) | (transColorBComp);
    transColorKeyMin1 = ((transColorRComp & 0xF00U) >> 8);

    /* Last Four Bits are set for MAX color
     * Here the range will be from 0xXX0 to 0xXXF for each color component. */
    transColorRComp |= 0xFU;
    transColorGComp |= 0xFU;
    transColorBComp |= 0xFU;

    transColorKeyMax0 =
        ((transColorRComp &
          0xFFU) << 24) | (transColorGComp << 12) | (transColorBComp);
    transColorKeyMax1 = ((transColorRComp & 0xF00U) >> 8);

    HW_WR_REG32(dispcOvlyObj->regOffset.transColorMin[0], transColorKeyMin0);
    HW_WR_REG32(dispcOvlyObj->regOffset.transColorMin[1], transColorKeyMin1);

    HW_WR_REG32(dispcOvlyObj->regOffset.transColorMax[0], transColorKeyMax0);
    HW_WR_REG32(dispcOvlyObj->regOffset.transColorMax[1], transColorKeyMax1);
}

/**
 *  halDispcOvlyPanelColorKeyConf
 *  Configures the colorkey of a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPanelColorKeyConf(VpsHal_Handle handle,
                                          UInt32        colorKeyEnable,
                                          UInt32        colorKeySel)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcOvrConfig);
    HW_SET_FIELD32(regVal, DSS_OVR_CONFIG_TCKLCDENABLE, colorKeyEnable);
    HW_SET_FIELD32(regVal, DSS_OVR_CONFIG_TCKLCDSELECTION, colorKeySel);
    HW_WR_REG32(dispcOvlyObj->regOffset.dispcOvrConfig, regVal);
}

/**
 *  halDispcOvlyPipeSetChannelOut
 *  Configures the pipeline to connect to a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeSetChannelOut(VpsHal_Handle handle,
                                          UInt32        pipe)
{
    UInt32 channelOut = 0;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    halDispcOvlyGetChannelOutVal(dispcOvlyObj->halId, &channelOut);

    if (pipe == VPS_DSS_DISPC_PIPE_WB)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not applicable for WB pipe line \r\n");
    }
    else if (pipe == VPS_DSS_DISPC_PIPE_GFX1)
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
        HW_SET_FIELD32(regVal, DSS_GFX_ATTRIBUTES_CHANNELOUT, channelOut);
        HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);
    }
    else
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
        HW_SET_FIELD32(regVal, DSS_VID_ATTRIBUTES_CHANNELOUT, channelOut);
        HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);
    }
}

/**
 *  halDispcOvlyGetChannelOutVal
 *  Returns the channel out value required for a particular overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyGetChannelOutVal(UInt32  halId,
                                         UInt32 *chlout)
{
    if (halId == VPSHAL_DSS_DISPC_LCD1)
    {
        *chlout = DSS_VID_ATTRIBUTES_CHANNELOUT_VP1SEL;
    }
    else if (halId == VPSHAL_DSS_DISPC_LCD2)
    {
        *chlout = DSS_VID_ATTRIBUTES_CHANNELOUT_WBSEL;
    }
    else
    {
        /* Nothing to be done here */
    }
}

/**
 *  halDispcOvlyPipeSetPreMulAlpha
 *  Sets the Premultiply alpha value for a particular pipeline
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeSetPreMulAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        preMultiplyAlpha)

{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (pipe == VPS_DSS_DISPC_PIPE_WB)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not applicable for WB pipe line \r\n");
    }
    else
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
        HW_SET_FIELD32(regVal, DSS_VID_ATTRIBUTES_PREMULTIPLYALPHA,
                       preMultiplyAlpha);
        HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_012)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-800) DOX_REQ_TAG(PDK-802)
 */
/**
 *  halDispcOvlyPipeSetGlobalAlpha
 *  Sets the Global Alpha value for a particular pipeline
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeSetGlobalAlpha(VpsHal_Handle handle,
                                           UInt32        pipe,
                                           UInt32        globalAlpha)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    switch (pipe)
    {
        case VPS_DSS_DISPC_PIPE_VID1:
        case VPS_DSS_DISPC_PIPE_VID2:
            regVal =
                HW_RD_REG32(((dispcOvlyObj->regOffset.pipeAttrib[pipe] -
                              DSS_VID_ATTRIBUTES) + DSS_VID_GLOBAL_ALPHA));
            HW_SET_FIELD32(regVal, DSS_VID_GLOBAL_ALPHA_GLOBALALPHA,
                           globalAlpha);
            HW_WR_REG32(
                (dispcOvlyObj->regOffset.pipeAttrib[pipe] -
                 DSS_VID_ATTRIBUTES) +
                 DSS_VID_GLOBAL_ALPHA,
                regVal);
            break;

        case VPS_DSS_DISPC_PIPE_GFX1:
            regVal =
                HW_RD_REG32(((dispcOvlyObj->regOffset.pipeAttrib[pipe] -
                              DSS_GFX_ATTRIBUTES) + DSS_GFX_GLOBAL_ALPHA));
            HW_SET_FIELD32(regVal, DSS_GFX_GLOBAL_ALPHA_GLOBALALPHA,
                           globalAlpha);
            HW_WR_REG32(
                (dispcOvlyObj->regOffset.pipeAttrib[pipe] -
                 DSS_GFX_ATTRIBUTES) +
                 DSS_GFX_GLOBAL_ALPHA,
                regVal);
            break;

        default:
            GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
            break;
    }
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_012)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-801) DOX_REQ_TAG(PDK-803)
 */
/**
 *  halDispcOvlyPipeConfZorder
 *  Sets the Z-Order of a particular pipeline connected to this overlay
 *  Caller is responsible to pass correct parameters.No error checking is
 *  done here.
 */
static void halDispcOvlyPipeConfZorder(VpsHal_Handle handle,
                                       UInt32        pipe,
                                       UInt32        zorder)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (pipe == VPS_DSS_DISPC_PIPE_WB)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Not applicable for WB pipe line \r\n");
    }
    else
    {
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe]);
        HW_SET_FIELD32(regVal, DSS_VID_ATTRIBUTES_ZORDER, zorder);
        HW_WR_REG32(dispcOvlyObj->regOffset.pipeAttrib[pipe], regVal);
    }
}

/**
 *  halDssVidConfCprCoeff
 *  Configures the coefficients for color phase rotation
 */
static void halDispcConfCprCoeff(VpsHal_Handle handle,
                                 const VpsHal_DssDispcCprCoeff *cprCoeff)
{
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;
    UInt32 regVal;

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.cprCoeff[0]);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_R_RB, cprCoeff->rb);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_R_RG, cprCoeff->rg);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_R_RR, cprCoeff->rr);
    HW_WR_REG32(dispcOvlyObj->regOffset.cprCoeff[0], regVal);

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.cprCoeff[1]);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_G_GB, cprCoeff->gb);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_G_GG, cprCoeff->gg);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_G_GR, cprCoeff->gr);
    HW_WR_REG32(dispcOvlyObj->regOffset.cprCoeff[1], regVal);

    regVal = HW_RD_REG32(dispcOvlyObj->regOffset.cprCoeff[2]);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_B_BB, cprCoeff->bb);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_B_BG, cprCoeff->bg);
    HW_SET_FIELD32(regVal, DSS_VP_CPR_COEF_B_BR, cprCoeff->br);
    HW_WR_REG32(dispcOvlyObj->regOffset.cprCoeff[2], regVal);

    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.dispcVpConfig,
        DSS_VP_CONFIG_CPR,
        cprCoeff->enableCpr);
    HW_WR_FIELD32(
        dispcOvlyObj->regOffset.dispcVpConfig,
        DSS_VP_CONFIG_COLORCONVENABLE,
        cprCoeff->enableCsc);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_011)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-807) DOX_REQ_TAG(PDK-808)
 */
/**
 *  haldssOvlyBT656_1120Conf
 *  \brief Configures the BT656_1120
 *
 *  This function will configure BT656 or 1120  bit and CPR coefficients
 *  when BT656/1120 is enabled
 *
 *  \param handle           Valid handle returned by haldssOvlyBT656_1120Conf
 *                          function
 *  \param  dvoFormat   Format  BT656/1120
 *  \param  enable   Enable or disable BT656/1120
 *  \return                 Returns BSP_SOK on success else returns error value
 */
static Int32 halDispcOvlyBT656_1120Conf(
    VpsHal_Handle handle,
    UInt32        dvoFormat,
    UInt32        enable)
{
    Int32  retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj  *dispcOvlyObj;
    UInt32 regVal;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, (NULL != handle));

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }
    if (dispcOvlyObj->halId > VPSHAL_DSS_DISPC_LCD1)
    {
        GT_0trace(
            VpsHalTrace, GT_ERR,
            "Not applicable for Overlay Managers \
            other than LCD1\r\n");
        retVal = BSP_EBADARGS;
    }

    if ((retVal == BSP_SOK) && (enable == TRUE))
    {
        if (dvoFormat == VPS_DCTRL_DVOFMT_BT656_EMBSYNC)
        {
            /* For BT656 format disable CPR and enable CSC. */
            dispcOvlyObj->cprCoeff.enableCpr = DSS_VP_CONFIG_CPR_CPRDIS;
            dispcOvlyObj->cprCoeff.enableCsc = DSS_VP_CONFIG_COLORCONVENABLE_COLSPCENB;
            halDispcConfCprCoeff(handle, &dispcOvlyObj->cprCoeff);

            regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpConfig);
            HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BT656ENABLE,
                           DSS_VP_CONFIG_BT656ENABLE_ENABLE);
            HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BT1120ENABLE,
                           DSS_VP_CONFIG_BT1120ENABLE_DISABLE);
            HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpConfig, regVal);
        }
        else if (dvoFormat == VPS_DCTRL_DVOFMT_BT1120_EMBSYNC)
        {
            /* For BT1120 format disable CPR and enable CSC. */
            dispcOvlyObj->cprCoeff.enableCpr = DSS_VP_CONFIG_CPR_CPRDIS;
            dispcOvlyObj->cprCoeff.enableCsc = DSS_VP_CONFIG_COLORCONVENABLE_COLSPCENB;
            halDispcConfCprCoeff(handle, &dispcOvlyObj->cprCoeff);

            regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpConfig);
            HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BT656ENABLE,
                           DSS_VP_CONFIG_BT656ENABLE_DISABLE);
            HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BT1120ENABLE,
                           DSS_VP_CONFIG_BT1120ENABLE_ENABLE);
            HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpConfig, regVal);
        }
        else
        {
            /* Nothing to be done here */
        }
    }
    else if ((retVal == BSP_SOK) && (enable == FALSE))
    {
        /* Disable CPR and CSC. */
        dispcOvlyObj->cprCoeff.enableCpr = (UInt32) DSS_VP_CONFIG_CPR_CPRDIS;
        dispcOvlyObj->cprCoeff.enableCsc = (UInt32) DSS_VP_CONFIG_COLORCONVENABLE_COLSPCDIS;
        regVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpConfig);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BT656ENABLE,
                       DSS_VP_CONFIG_BT656ENABLE_DISABLE);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_BT1120ENABLE,
                       DSS_VP_CONFIG_BT1120ENABLE_DISABLE);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_CPR, dispcOvlyObj->cprCoeff.enableCpr);
        HW_SET_FIELD32(regVal, DSS_VP_CONFIG_COLORCONVENABLE,
                       dispcOvlyObj->cprCoeff.enableCsc);
        HW_WR_REG32(dispcOvlyObj->regOffset.dispcVpConfig, regVal);
    }
    else
    {
        /* Nothing to be done here */
    }
    return retVal;
}

/**
 *  halDispcSetDefIntfWidth
 *  Set the DPI interface width to 24bit, hardware default value is 12 bit.
 */
static void halDispcSetDefIntfWidth(void)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(SOC_DISPC_VP1_BASE + DSS_VP_CONTROL);
    HW_SET_FIELD32(
        regVal,
        DSS_VP_CONTROL_DATALINES,
        DSS_VP_CONTROL_DATALINES_OALSB24B);
    HW_WR_REG32(SOC_DISPC_VP1_BASE + DSS_VP_CONTROL, regVal);
}

/**
 *  halDispcReset
 *  Resets the DISPC module
 */
static void halDispcReset(void)
{
    UInt32 dispcStatus;
    UInt32 regVal;

    /* No Standby*/
    regVal = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG);
    HW_SET_FIELD32(regVal, DSS_DISPC_SYSCONFIG_MIDLEMODE,
                   DSS_DISPC_SYSCONFIG_MIDLEMODE_NSTANDBY);
    HW_WR_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG, regVal);

    /* Disable VP */
    regVal = HW_RD_REG32(SOC_DISPC_VP1_BASE + DSS_VP_CONTROL);
    HW_SET_FIELD32(regVal, DSS_VP_CONTROL_VPENABLE,
                   DSS_VP_CONTROL_VPENABLE_LCDOPDIS);
    HW_WR_REG32(SOC_DISPC_VP1_BASE + DSS_VP_CONTROL, regVal);

    /* Soft reset */
    regVal = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG);
    HW_SET_FIELD32(regVal, DSS_DISPC_SYSCONFIG_SOFTRESET,
                   DSS_DISPC_SYSCONFIG_SOFTRESET_RST);
    HW_WR_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG, regVal);

    /* Warm reset */
    regVal = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG);
    HW_SET_FIELD32(regVal, DSS_DISPC_SYSCONFIG_WARMRESET,
                   DSS_DISPC_SYSCONFIG_WARMRESET);
    HW_WR_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG, regVal);

    /* Smart Standby*/
    regVal = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG);
    HW_SET_FIELD32(regVal, DSS_DISPC_SYSCONFIG_MIDLEMODE,
                   DSS_DISPC_SYSCONFIG_MIDLEMODE_SSTANDBY);
    HW_WR_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG, regVal);

    /* Smart IDLE*/
    regVal = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG);
    HW_SET_FIELD32(regVal, DSS_DISPC_SYSCONFIG_SIDLEMODE,
                   DSS_DISPC_SYSCONFIG_SIDLEMODE_SIDLE);
    HW_WR_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG, regVal);

    dispcStatus = HW_RD_REG32(SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSSTATUS);

    /* TODO For now comment it, we need to check the status before starting */
    /* while(RD_REG_32(DISPC, DISPC__DISPC_SYSSTATUS) != 1); */
    if ((dispcStatus & 0x1U) != 0x1U)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "DSS Still in reset \r\n");
    }
}

/**
 *  halDispcOvlyGetTdmHblankFact
 *  Get the multiplication and division factors to be applied while programming
 *  the hblank values. It would be required for tdm modes. For non tdm modes
 *  both the factors will be 1.
 */
static Int32 halDispcOvlyGetTdmHblankFact(
    const VpsHal_DssDispcOvlyObj *dispcOvlyObj,
    UInt32                       *hBlankMultFact,
    UInt32                       *hBlankDivFact)
{
    UInt32 tdmRegVal, tdmCycleFormat, tdmEnable;

    /* If TDM mode is enabled The H Blank timing parameters should be
     * modified based on TDM Cycle format. */
    tdmRegVal = HW_RD_REG32(dispcOvlyObj->regOffset.dispcVpControl);
    tdmEnable = HW_GET_FIELD(tdmRegVal, DSS_VP_CONTROL_TDMENABLE);
    if (tdmEnable == TRUE)
    {
        tdmCycleFormat = HW_GET_FIELD(tdmRegVal,
                                      DSS_VP_CONTROL_TDMCYCLEFORMAT);

        if (tdmCycleFormat == 0x1U)
        {
            /* 2 Cycles for 1 Pixel: Multiply HBlank by 2. */
            *hBlankMultFact = 2U;
            *hBlankDivFact  = 1U;
        }
        else if (tdmCycleFormat == 0x2U)
        {
            /* 3 Cycles for 1 Pixel: Multiply HBlank by 3. */
            *hBlankMultFact = 3U;
            *hBlankDivFact  = 1U;
        }
        else if (tdmCycleFormat == 0x3U)
        {
            /* 3 Cycles for 2 Pixel: Multiply HBlank by 1.5. */
            *hBlankMultFact = 3U;
            *hBlankDivFact  = 2U;
        }
        else
        {
            /* Default to 1 cycle for 1 pixel: HBlank value should not be
             *modified. */
            *hBlankMultFact = 1U;
            *hBlankDivFact  = 1U;
        }
    }
    else
    {
        /* TDM is disabled HBlank value should not be modified. */
        *hBlankMultFact = 1U;
        *hBlankDivFact  = 1U;
    }

    return (BSP_SOK);
}

/**
 *  halDispcOvlyValidateLcdBlankTiming
 *  Validate whether the blanking values are within the acceptable range.
 */
static Int32 halDispcOvlyValidateLcdBlankTiming(
    const VpsHal_DssDispcLcdBlankTimingParam *lcdBlankTimingParm,
    UInt32                                    hBlankMultFact,
    UInt32                                    hBlankDivFact)
{
    Int32 retVal = BSP_SOK;
    /* Check hblank timing */
    if ((((lcdBlankTimingParm->hBackPorch * hBlankMultFact) / hBlankDivFact) >
         (DSS_VP_TIMING_H_HBP_MASK >> DSS_VP_TIMING_H_HBP_SHIFT)) ||
        (((lcdBlankTimingParm->hFrontPorch * hBlankMultFact) / hBlankDivFact) >
         (DSS_VP_TIMING_H_HFP_MASK >> DSS_VP_TIMING_H_HFP_SHIFT)) ||
        (((lcdBlankTimingParm->hSyncLen * hBlankMultFact) / hBlankDivFact) >
         (DSS_VP_TIMING_H_HSW_MASK >> DSS_VP_TIMING_H_HSW_SHIFT)))
    {
        retVal = BSP_EBADARGS;
    }

    /* Check hblank timing */
    if ((lcdBlankTimingParm->vBackPorch >
         (DSS_VP_TIMING_V_VBP_MASK >> DSS_VP_TIMING_V_VBP_SHIFT)) ||
        (lcdBlankTimingParm->vFrontPorch >
         (DSS_VP_TIMING_V_VFP_MASK >> DSS_VP_TIMING_V_VFP_SHIFT)) ||
        (lcdBlankTimingParm->vSyncLen >
         (DSS_VP_TIMING_V_VSW_MASK >> DSS_VP_TIMING_V_VSW_SHIFT)))
    {
        retVal = BSP_EBADARGS;
    }
    return retVal;
}

Int32 VpsHal_dssOvlySetCprCoeff(VpsHal_Handle handle,
                                const VpsHal_DssDispcCprCoeff *coeff)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* Save the passed Csc Coeff to pipe object */
        BspUtils_memcpy(&dispcOvlyObj->cprCoeff, coeff, sizeof (VpsHal_DssDispcCprCoeff));
        /* Set the Csc Coeff for the pipeline */
        halDispcConfCprCoeff(handle, &dispcOvlyObj->cprCoeff);
    }
    return retVal;
}

Int32 VpsHal_dssOvlyGetCprCoeff(VpsHal_Handle handle,
                                VpsHal_DssDispcCprCoeff *coeff)
{
    Int32 retVal = BSP_SOK;
    VpsHal_DssDispcOvlyObj *dispcOvlyObj;

    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != handle);

    dispcOvlyObj = (VpsHal_DssDispcOvlyObj *) handle;

    if (dispcOvlyObj->halId >= VPSHAL_DSS_DISPC_OVLY_INST_ID_MAX)
    {
        GT_0trace(VpsHalTrace, GT_ERR, "Invalid Hal instance\r\n");
        retVal = BSP_EBADARGS;
    }

    if (retVal == BSP_SOK)
    {
        /* Get the Cpr Coeff from pipe object */
        BspUtils_memcpy(coeff, &dispcOvlyObj->cprCoeff, sizeof (VpsHal_DssDispcCprCoeff));
    }
    return retVal;
}

void VpsHal_dssOvlySetMflagConfig(const VpsHal_DssDispcMflagConfigParam *mflagCfg)
{
    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != mflagCfg);

    HW_WR_FIELD32(SOC_DISPC_COMMON_BASE + DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE,
                  DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_START,
                  mflagCfg->globalMflagStart);
    HW_WR_FIELD32(SOC_DISPC_COMMON_BASE + DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE,
                  DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL,
                  mflagCfg->globalMflagCtrl);
    HW_WR_FIELD32(SOC_DISPC_GFX1_BASE + DSS_GFX_MFLAG_THRESHOLD,
                  DSS_GFX_MFLAG_THRESHOLD_HT,
                  mflagCfg->gfxMflagHighThreshold);
    HW_WR_FIELD32(SOC_DISPC_GFX1_BASE + DSS_GFX_MFLAG_THRESHOLD,
                  DSS_GFX_MFLAG_THRESHOLD_LT,
                  mflagCfg->gfxMflagLowThreshold);
    HW_WR_FIELD32(SOC_DISPC_VID1_BASE + DSS_VID_MFLAG_THRESHOLD,
                  DSS_VID_MFLAG_THRESHOLD_HT,
                  mflagCfg->vid1MflagHighThreshold);
    HW_WR_FIELD32(SOC_DISPC_VID1_BASE + DSS_VID_MFLAG_THRESHOLD,
                  DSS_VID_MFLAG_THRESHOLD_LT,
                  mflagCfg->vid1MflagLowThreshold);
    HW_WR_FIELD32(SOC_DISPC_VID2_BASE + DSS_VID_MFLAG_THRESHOLD,
                  DSS_VID_MFLAG_THRESHOLD_HT,
                  mflagCfg->vid2MflagHighThreshold);
    HW_WR_FIELD32(SOC_DISPC_VID2_BASE + DSS_VID_MFLAG_THRESHOLD,
                  DSS_VID_MFLAG_THRESHOLD_LT,
                  mflagCfg->vid2MflagLowThreshold);
    HW_WR_FIELD32(SOC_DISPC_WB_BASE + DSS_WB_MFLAG_THRESHOLD,
                  DSS_WB_MFLAG_THRESHOLD_HT,
                  mflagCfg->wbMflagHighThreshold);
    HW_WR_FIELD32(SOC_DISPC_WB_BASE + DSS_WB_MFLAG_THRESHOLD,
                  DSS_WB_MFLAG_THRESHOLD_LT,
                  mflagCfg->wbMflagLowThreshold);
}

void VpsHal_dssOvlyGetMflagConfig(VpsHal_DssDispcMflagConfigParam *mflagCfg)
{
    /* Check for NULL pointer */
    GT_assert(VpsHalTrace, NULL != mflagCfg);

    mflagCfg->globalMflagStart =
        HW_RD_FIELD32(SOC_DISPC_COMMON_BASE + DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE,
                      DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_START);
    mflagCfg->globalMflagCtrl =
        HW_RD_FIELD32(SOC_DISPC_COMMON_BASE + DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE,
                      DSS_DISPC_GLOBAL_MFLAG_ATTRIBUTE_CTRL);
    mflagCfg->gfxMflagHighThreshold =
        HW_RD_FIELD32(SOC_DISPC_GFX1_BASE + DSS_GFX_MFLAG_THRESHOLD,
                      DSS_GFX_MFLAG_THRESHOLD_HT);
    mflagCfg->gfxMflagLowThreshold  =
        HW_RD_FIELD32(SOC_DISPC_GFX1_BASE + DSS_GFX_MFLAG_THRESHOLD,
                      DSS_GFX_MFLAG_THRESHOLD_LT);
    mflagCfg->vid1MflagHighThreshold =
        HW_RD_FIELD32(SOC_DISPC_VID1_BASE + DSS_VID_MFLAG_THRESHOLD,
                      DSS_VID_MFLAG_THRESHOLD_HT);
    mflagCfg->vid1MflagLowThreshold  =
        HW_RD_FIELD32(SOC_DISPC_VID1_BASE + DSS_VID_MFLAG_THRESHOLD,
                      DSS_VID_MFLAG_THRESHOLD_LT);
    mflagCfg->vid2MflagHighThreshold =
        HW_RD_FIELD32(SOC_DISPC_VID2_BASE + DSS_VID_MFLAG_THRESHOLD,
                      DSS_VID_MFLAG_THRESHOLD_HT);
    mflagCfg->vid2MflagLowThreshold  =
        HW_RD_FIELD32(SOC_DISPC_VID2_BASE + DSS_VID_MFLAG_THRESHOLD,
                      DSS_VID_MFLAG_THRESHOLD_LT);
    mflagCfg->wbMflagHighThreshold =
        HW_RD_FIELD32(SOC_DISPC_WB_BASE + DSS_WB_MFLAG_THRESHOLD,
                      DSS_WB_MFLAG_THRESHOLD_HT);
    mflagCfg->wbMflagLowThreshold  =
        HW_RD_FIELD32(SOC_DISPC_WB_BASE + DSS_WB_MFLAG_THRESHOLD,
                      DSS_WB_MFLAG_THRESHOLD_LT);
    /* Vid3 pipe is not available in tda3xx, set these to 0 as the structure
     * interface is not platform specific. */
    mflagCfg->vid3MflagHighThreshold = 0U;
    mflagCfg->vid3MflagLowThreshold = 0U;
}

