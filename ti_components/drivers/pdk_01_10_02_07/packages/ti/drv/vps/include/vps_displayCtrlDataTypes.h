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
 *  \addtogroup BSP_DRV_VPS_DCTRL_API
 *
 *  @{
 */

/**
 *  \file vps_displayCtrlDataTypes.h
 *
 *  \brief Display Controller Driver
 *  Generic Display Controller Driver Interface file.
 */

#ifndef VPS_DISPLAY_CTRL_DATA_TYPES_H_
#define VPS_DISPLAY_CTRL_DATA_TYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/vps_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Macros, Which can be used in the setconfig API to connect different
 * modules */

/** \brief Macro defining Video1 input path */
#define VPS_DCTRL_DSS_VID1_INPUT_PATH   (1U)

/** \brief Macro defining Video2 input path */
#define VPS_DCTRL_DSS_VID2_INPUT_PATH   (2U)

/** \brief Macro defining Graphics input path */
#define VPS_DCTRL_DSS_GFX1_INPUT_PATH   (4U)

/** \brief Macro defining LCD1 Blender */
#define VPS_DCTRL_DSS_LCD1_BLENDER      (6U)

/** \brief Macro defining LCD2 Blender */
#define VPS_DCTRL_DSS_LCD2_BLENDER      (7U)

/** \brief Macro defining DPI1 Output */
#define VPS_DCTRL_DSS_DPI1_OUTPUT       (10U)

/** \brief Macro defining DPI2 Output
     Not Available in Tda3xx platform */
#define VPS_DCTRL_DSS_DPI2_OUTPUT       (11U)

/** \brief Macro defining DPI3 Output
     Not Available in Tda3xx platform */
#define VPS_DCTRL_DSS_DPI3_OUTPUT       (12U)

/** \brief Macro defining HDMI Output
     Not Available in Tda3xx platform */
#define VPS_DCTRL_DSS_HDMI_OUTPUT       (13U)

/** \brief Macro defining Video3 input path
     Not Available in Tda3xx platform */
#define VPS_DCTRL_DSS_VID3_INPUT_PATH   (3U)

/** \brief Macro defining LCD3 Blender
     Not Available in Tda3xx platform */
#define VPS_DCTRL_DSS_LCD3_BLENDER      (8U)

/** \brief Macro defining HDMI Blender
     Not Available in Tda3xx platform */
#define VPS_DCTRL_DSS_HDMI_BLENDER      (9U)

/** \brief Macro defining Write Back Output */ /*TODO - Check if this should be
 * named as input or output*/
#define VPS_DCTRL_DSS_WB_OUTPUT         (5U)

/** \brief Defines maximum number of edges for allocation. */
#define VPS_DCTRL_MAX_EDGES             (50U)

/* Following macros define bitmasks for the Vencs. Here, bitmasks are
 * used for identifying Vencs so that tied vencs can be easily specified
 * and configured. Two vencs, which uses same pixel clock and whose
 * vsync are synchronized, can be tied together. In DSS Tied Venc concept is not
 * applicable */

/** \brief Bitmask for LCD1 VENC. */
#define VPS_DCTRL_DSS_VENC_LCD1         ((UInt32) 0x01U)
/** \brief Bitmask for LCD2 VENC. */
#define VPS_DCTRL_DSS_VENC_LCD2         ((UInt32) 0x02U)
/** \brief Bitmask for LCD3 VENC.
     Not available in Tda3xx platform. */
#define VPS_DCTRL_DSS_VENC_LCD3         ((UInt32) 0x04U)
/** \brief Bitmask for HDMI VENC
     Not available in Tda3xx platform */
#define VPS_DCTRL_DSS_VENC_HDMI         ((UInt32) 0x08U)

/** \brief Defines maximum number of vencs supported */
#define VPS_DCTRL_MAX_VENC              ((UInt32) 4U)

/** \brief Maximum number of characters in the string for specifying
 *  node name */
#define VPS_DCTRL_MAX_NODE_NAME         ((UInt32) 20U)

/* Following macros define output range for the Venc.
 * Applicable only in case of VPS_DCTRL_DSS_VENC_HDMI venc. */

/** \brief Full range output from HDMI. */
#define VPS_DCTRL_VENC_OUTPUT_FULL_RANGE     ((UInt32) 0x1U)

/** \brief Limited range output from HDMI. */
#define VPS_DCTRL_VENC_OUTPUT_LIMITED_RANGE  ((UInt32) 0x2U)
/**
 *  enum Vps_DctrlUseCase
 *  \brief Enum for selecting VPS configuration for the specific use
 *  case or user defined use case.
 *  Display Controller supports few pre-defined configurations. Pre-defined
 *  configurations configures all vps modules, including vencs, handled by
 *  display controller. Once a
 *  pre-defined configuration is used, all other parameters will be ignored
 *  in the Vps_DcConfig structure and display controller will be
 *  configured as per the pre-defined configuration.
 */
typedef enum
{
    VPS_DCTRL_DUALHDDISPLAY = 0,
    /**< DUALDISPLAY configuration: Pre-defined configuration in which
     *   HDMI and DPI are used to provide two HD outputs. Both
     *   the VENCs are running 1080p mode at 60 fps. */
    VPS_DCTRL_USERSETTINGS,
    /**< User Defined configuration */
    VPS_DCTRL_NUM_USECASE
    /**< This must be the last Enum */
} Vps_DctrlUseCase;

/**
 *  enum Vps_DctrlNodeType
 *  \brief Enum defining node types available in VPS. There are several
 *  modules available in VPS, which controls how and which display goes
 *  to perticulcar VENC. These path controller modules are Multiplexers,
 *  DeMultiplexers, splitters, overlays(compositer/blender).
 *  There modules are known as nodes in the display
 *  controller. This enum defines the type of the node.
 */
typedef enum
{
    VPS_DCTRL_NODETYPE_MUX = 0,
    /**< Multiplexer or Switch, takes N selectable inputs and
     *   provides one output */
    VPS_DCTRL_NODETYPE_DEMUX,
    /**< DeMultiplexer, takes one input and outputs on
     *   N selectable outputs. */
    VPS_DCTRL_NODETYPE_SPLITTER,
    /**< Splitter, takes one input and provides M identical outputs */
    VPS_DCTRL_NODETYPE_COMP,
    /**< Compositor, takes N inputs and provides one composited output */
    VPS_DCTRL_NODETYPE_INPUT,
    /**< Input Node, there is no node connected as input to this node */
    VPS_DCTRL_NODETYPE_OUTPUT,
    /**< Output Node,  there is no node connected as output from this node  */
    VPS_DCTRL_NODETYPE_MAX
    /**< This must be last enum */
} Vps_DctrlNodeType;

/**
 * enum Vps_DctrlDigitalFmt
 * \brief DVO Format, BT656 and BT1120 are two different type of embedded
 *  sync formats supported by the VPS module. It supportes Discrete sync format
 *  as well.
 */
typedef enum
{
    VPS_DCTRL_DVOFMT_BT656_EMBSYNC = 0,
    /**< Output data format is BT656 with embedded sync */
    VPS_DCTRL_DVOFMT_BT1120_EMBSYNC,
    /**< Ouptut data format is BT1120 with embedded sync */
    VPS_DCTRL_DVOFMT_GENERIC_DISCSYNC,
    /**< Output data format is for any discrete sync */
    VPS_DCTRL_DVOFMT_MAX
    /**< This should be the last Enum */
} Vps_DctrlDigitalFmt;

/**
 * enum  Vps_DctrlAnalogFmt
 * \brief Analog Format.
 */
typedef enum
{
    VPS_DCTRL_A_OUTPUT_COMPOSITE = 0,
    /**< Analog output format composite */
    VPS_DCTRL_A_OUTPUT_SVIDEO,
    /**< Analog output format svideo */
    VPS_DCTRL_A_OUTPUT_COMPONENT,
    /**< Analog output format component */
    VPS_DCTRL_A_OUTPUT_MAX
    /**< This should be the last Enum */
} Vps_DctrlAnalogFmt;

/**
 * \brief Signal polarity
 */
typedef enum
{
    VPS_DCTRL_POLARITY_ACT_LOW = 0,
    /**< Signal polarity Active high */
    VPS_DCTRL_POLARITY_ACT_HIGH = 1,
    /**< Signal polarity Active low */
    VPS_DCTRL_POLARITY_MAX = 2
                             /**< Signal polarity Max value */
}Vps_DctrlSignalPolarity;

/**
 * \brief DISPC Mode
 */
typedef enum
{
    VPS_DCTRL_DISPC_MODE_SLAVE = 0,
    /**< Display Controller Mode Slave */
    VPS_DCTRL_DISPC_MODE_MASTER = 1,
    /**< Display Controller Mode Master */
    VPS_DCTRL_DISPC_MODE_MAX = 2
                               /**< Display Controller Mode Max */
}Vps_DctrlDispcMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Structure containing the properties of a the processing node. Node
 *  represents a VPS module which controls how and which display goes
 *  to perticulcar VENC. This structure is for enumerating this processing
 *  modules one by one and get the properties of it.
 */
typedef struct
{
    UInt32 nodeIdx;
    /**< Index of the node. Node Index starting from 0 to maximum
     *   number of nodes. Used at the time of enumerating nodes.
     *   After max number of nodes, this function returns error. */
    UInt32 nodeId;
    /**< ID of the node. This ID should be used when enabling input
     *   of this node */
    UInt32 nodeType;
    /**< Type of the node, This type indicates whether this node can
     *   accept multiple input or output or not
     *   For valid values see #Vps_DctrlNodeType*/
    Char   nodeName[VPS_DCTRL_MAX_NODE_NAME];
    /**< Name of the processing node */
    UInt32 numInputs;
    /**< Number of all possible inputs for this node */
    UInt32 numOutputs;
    /**< Number of all possible outputs for this node */
} Vps_DctrlEnumNode;

/**
 * \brief Structure containing edge information. Edge is a connection
 *  between two nodes i.e. two modules (like CIG and Blend) in VPS.
 *  VPS can be represented by a graph, where each
 *  module is node and edge is present between two nodes if they are connected.
 *  All VPS paths can be configured in one shot by IOCTL
 *  IOCTL_VPSCORE_DCTRL_SET_CONFIG.
 *  This IOCTL takes the array of edges connected between nodes. This structure
 *  is used to specify individual edge information.
 */
typedef struct
{
    UInt32 startNode;
    /**< Starting node (VPS Module) of the edge */
    UInt32 endNode;
    /**< End node (VPS Module) of the edge */
} Vps_DctrlEdgeInfo;

/**
 * \brief Structure containing output information. This structure is used
 *  to set output in the output node. This structure is used as an argument to
 *  IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT ioctl.
 */
typedef struct
{
    UInt32 vencId;
    /**< Node Number of the Venc */
    UInt32 dataFormat;
    /**< Output Data format from Venc. Currently, valid values are
     *    FVID2_DF_RGB24_888, FVID2_DF_YUV422I_YUYV. */
    UInt32 dvoFormat;
    /**< digital output. See #Vps_DctrlDigitalFmt for the possible Values */
    UInt32 aFmt;
    /**< Analog output. See #Vps_DctrlAnalogFmt for the possible Values */
    UInt32 videoIfWidth;
    /**< [IN] Video interface mode. For valid values see #Fvid2_VideoIfWidth. */
    UInt32 fidPolarity;
    /**< Polarity for the field id signal for the digital output only
     *   valid values see #Vps_DctrlSignalPolarity
     *   TODO - Check if this is possible in DSS. */
    UInt32 vsPolarity;
    /**< Polarity for the vertical sync signal for the digital output only
     *   valid values see #Vps_DctrlSignalPolarity */
    UInt32 hsPolarity;
    /**< Polarity for the horizontal sync signal for the digital output only
     *   valid values see #Vps_DctrlSignalPolarity */
    UInt32 actVidPolarity;
    /**< Polarity for the active video signal for the digital output only
     *   valid values see #Vps_DctrlSignalPolarity */
    UInt32 pixelClkPolarity;
    /**< for valid values TODO
     *   0x0: Data is driven on the LCD data lines on the
     *      rising edge of the pixel clock.
     *   0x1: Data is driven on the LCD data lines on the
     *      falling edge of the pixel clock. */
} Vps_DctrlOutputInfo;

/**
 * \brief Structure containing Venc Divisor information for the LCDx
 *   overlays(LCD1,LCD2,LCD3) .
 *   DISPC_LCDx_PCLK = (LCDx_CLK/ divisorLCD) / divisorPCD.
 *   This structure is used as an argument to
 *   IOCTL_VPSCORE_DCTRL_SET_VENC_PCLK_DIVISORS ioctl.
 */
typedef struct
{
    UInt32 vencId;
    /**< VencID of the panel to which the divisor values have to be set. */
    UInt32 divisorLCD;
    /**< Display controller logic clock divisor value (from 1 to 255)
     *   to specify the intermediate pixel clock frequency based
     *   on the LCDx_CLK. The value 0 is invalid. */
    UInt32 divisorPCD;
    /**< Pixel clock divisor value (from 1 to 255) to specify the
     *   frequency of the pixel clock based on the LCDx_CLK.
     *   The values 0 is invalid */
} Vps_DctrlVencDivisorInfo;

/**
 * \brief Structure containing mode information.
 */
typedef struct
{
    UInt32         vencId;
    /**< Identifies the VENC on which mode parameters is to be applied.
     *   Use one of VPS_DCTRL_DSS_VENC_LCD1, VPS_DCTRL_DSS_VENC_LCD2,
     *   VPS_DCTRL_DSS_VENC_LCD3 macro for this variable. */
    Fvid2_ModeInfo mInfo;
    /**< Mode Information to be configured in VENC */
    UInt32         mode;
    /**< VENC mode */
    UInt32         isVencRunning;
    /**< Flag to indicate whether VENC is running or not. This is
     *   read only parameter returned from the display controller to
     *   indicated whether given venc is running or not. */
    UInt32         numInPath;
    /**< This is read only parameter returned from the display
     *   controller to inform number of input paths connected to
     *   the this vencs. */
    UInt32         outputRange;
    /**< This parameter is used to configure the output of the venc to be in
     *   full range or limited range. Use VPS_DCTRL_VENC_OUTPUT_FULL_RANGE or
     *   VPS_DCTRL_VENC_OUTPUT_LIMITED_RANGE macro for this variable.
     *   Applicable in case of Venc HDMI. */
} Vps_DctrlModeInfo;

/*TODO - Check if we need to mention about tied venc here */
/**
 * struct Vps_DctrlVencInfo
 * \brief Structure containing venc information. This structure is used is
 *  IOCTL_VPSCORE_DCTRL_SET_CONFIG API to configure mode in the Vencs.
 *  It also is used to inform
 *  which vencs are tied. Two vencs are tied when both are running on the
 *  same pixel clock and vsync signal for both the vencs are
 *  synchronized. If two vencs are tied, they will be enabled at the same
 *  time in order to have both synchronized. Note that if each of tied venc
 *  is configured with the different modes, display controller does not check
 *  whether venc synchronization is possible or not with the given modes.
 */
typedef struct
{
    UInt32            numVencs;
    /**< Number of valid entries in modeInfo array */
    Vps_DctrlModeInfo modeInfo[VPS_DCTRL_MAX_VENC];
    /**< Mode Information to be set the Venc. */
    UInt32            tiedVencs;
    /**< Bitmask of tied vencs. Two vencs, which uses same pixel clock and whose
     *   vsync are synchronized, can be tied together. */
} Vps_DctrlVencInfo;

/**
 * struct Vps_DctrlConfig
 * \brief Structure contaning set of edges and VENC information. Here,
 *  edge represents connection between two VPS modules. When an edge is
 *  enabled, output from a VPS modules is connected as an input to another
 *  VPS module.
 *  This structure is used in
 *  IOCTL_VPSCORE_DCTRL_SET_CONFIG API to configure Complete VPS
 *  connections statically in one shot. It
 *  has set of edges, which describes how individual modules are connected to
 *  each other and finally to the VENC. It also configures the mode in the
 *  VENCs and tells which vencs are tied.Tied Vencs are not supported in DSS.
 */
typedef struct
{
    UInt32            useCase;
    /**< Indicates which use case is to be configured for. Display
     *   Controller provides set of pre-defined configuration
     *   for some standard use cases. Application can
     *   directly specify the usecase here. If it is standard use case,
     *   there is no need to specify next arguments.
     *   Application can also specify user defined path configuration by
     *   specifying VPS_DCTRL_USERSETTINGS in this argument and providing
     *   list of edges.
     *   For valid values see #Vps_DctrlUseCase. */
    UInt32            numEdges;
    /**< Number edge in the edgeInfo array */
    Vps_DctrlEdgeInfo edgeInfo[VPS_DCTRL_MAX_EDGES];
    /**< List of edges connecting vps modules. Display controller parse these
     *   edges and enables/disables input/output path in the appropriate VPS
     *   module. This edge tells which module is connected to which module
     *   enabling output in edge start module and input in edge end module.*/
    Vps_DctrlVencInfo vencInfo;
    /**< Structure containing Venc Information like mode to be configured and
     *   which are tied. */
} Vps_DctrlConfig;

/**
 * \brief Structure containing Video standard information for SD-VENC
 *   This structure is used as an argument to
 *   IOCTL_VPSCORE_DCTRL_SET_SDVENC_MODE ioctl.
 */
typedef struct
{
    UInt32 videoStandard;
    /**< Video standard to which the SD-VENC should be configured for.
             For valid values see #Fvid2_Standard */
    void  *reserved;
    /**< For future use. Not used currently. Set this to NULL. */
} Vps_DctrlSDVencVideoStandard;


/**
 * \brief Structure containing the sync lost error counts
 *   This structure is used as an argument to
 *   IOCTL_VPSCORE_DCTRL_GET_ERROR_STATS ioctl.
 */
typedef struct
{
    UInt32 syncLost1;
    /**<SyncLost Error Count for LCD1 Overlay. */
    UInt32 syncLost2;
    /**<SyncLost Error Count for LCD2 Overlay.
    *   Not applicable for Tda3xx platform. */
    UInt32 syncLost3;
    /**<SyncLost Error Count for LCD3 Overlay.
       *    Not applicable for Tda3xx platform. */
    UInt32 syncLostTV;
    /**<SyncLost Error Count for TV Overlay.
       *    Not applicable for Tda3xx platform. */
    UInt32 ocpError;
    /**< Ocp Error Count. */
}Vps_DctrlErrorSyncLostStats;

typedef struct
{
    UInt32 vencId;
    /**< Identifies the VENC on which mode parameters is to be applied.
     *   Use one of VPS_DCTRL_DSS_VENC_LCD1, VPS_DCTRL_DSS_VENC_LCD2,
     *   VPS_DCTRL_DSS_VENC_LCD3 macro for this variable. */
    UInt32 hFrontPorch;
    /**< Horizontal front porch. Same for both fields in case of interlaced
     *   display. */
    UInt32 hBackPorch;
    /**< Horizontal back porch. */
    UInt32 hSyncLen;
    /**< Horizontal sync length. Same for both fields in case of interlaced
     *   display. */
    UInt32 vFrontPorch;
    /**< Vertical front porch for each field or frame. */
    UInt32 vBackPorch;
    /**< Vertical back porch for each field or frame. */
    UInt32 vSyncLen;
    /**< Vertical sync length for each field. */
}Vps_DctrlVencBlankTiming;

/* ========================================================================== */
/* ========================================================================== */
/*                      Part-3 Advanced Configuration                         */
/* ========================================================================== */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  \brief Vps_DctrlConfig structure init function.
 *
 *  \param  dctrlCfg  [IN]Pointer to #Vps_DctrlConfig structure.
 *
 */
static inline void VpsDctrlConfig_init(Vps_DctrlConfig *dctrlCfg);

/**
 *  \brief Vps_DctrlVencInfo structure init function.
 *
 *  \param  vencInfo  [IN]Pointer to #Vps_DctrlVencInfo structure.
 *
 */
static inline void VpsDctrlVencInfo_init(Vps_DctrlVencInfo *vencInfo);

/**
 *  \brief Vps_DctrlModeInfo structure init function.
 *
 *  \param  modeInfo  [IN]Pointer to #Vps_DctrlModeInfo structure.
 *
 */
static inline void VpsDctrlModeInfo_init(Vps_DctrlModeInfo *modeInfo);
/**
 *  \brief Vps_DctrlSDVencVideoStandard structure init function SD-VENC mode
 *         settings.
 *
 *  \param  vidStandard  [IN]Pointer to #Vps_DctrlSDVencVideoStandard structure.
 *
 */
static inline void VpsDctrlSDVencVideoStandard_init(
    Vps_DctrlSDVencVideoStandard *vidStandard);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */
static inline void VpsDctrlConfig_init(Vps_DctrlConfig *dctrlCfg)
{
    uint32_t i;
    if(dctrlCfg != NULL)
    {
        dctrlCfg->useCase = VPS_DCTRL_USERSETTINGS;
        dctrlCfg->numEdges = 0U;
        for(i=0; i<VPS_DCTRL_MAX_EDGES; i++)
        {
            dctrlCfg->edgeInfo[i].startNode = 0U;
            dctrlCfg->edgeInfo[i].endNode   = 0U;
        }
        VpsDctrlVencInfo_init(&dctrlCfg->vencInfo);
    }
}

static inline void VpsDctrlVencInfo_init(Vps_DctrlVencInfo *vencInfo)
{
    uint32_t i;
    if(vencInfo != NULL)
    {
        vencInfo->numVencs = 0U;
        for(i=0; i<VPS_DCTRL_MAX_VENC; i++)
        {
            VpsDctrlModeInfo_init(&(vencInfo->modeInfo[i]));
        }
        vencInfo->tiedVencs = 0U;
    }
}

static inline void VpsDctrlModeInfo_init(Vps_DctrlModeInfo *modeInfo)
{
    if(modeInfo != NULL)
    {
        modeInfo->vencId = 0U;
        Fvid2ModeInfo_init(&(modeInfo->mInfo));
        modeInfo->mode = 0U;
        modeInfo->isVencRunning = 0U;
        modeInfo->numInPath = 0U;
        modeInfo->outputRange = VPS_DCTRL_VENC_OUTPUT_FULL_RANGE;
    }
}

static inline void VpsDctrlSDVencVideoStandard_init(
    Vps_DctrlSDVencVideoStandard *vidStandard)
{
    if(vidStandard != NULL)
    {
        vidStandard->videoStandard = FVID2_STD_NTSC;
        vidStandard->reserved      = NULL;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_DISPLAY_CTRL_DATA_TYPES_H_ */

/* @} */
