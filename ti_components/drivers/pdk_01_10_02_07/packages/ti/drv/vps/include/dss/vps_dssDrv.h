/*
 *  Copyright (c) Texas Instruments Incorporated 2013
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
 *  \file vps_dssDrv.h
 *
 *  \brief Baremetal interface file for DSS Display driver.
 *  Caution: This library cannot co-exist with VPS RTOS driver.
 *
 */
/**
* Below are the global requirements which are met by this ADC
* driver which can't be mapped to a particular source ID
*/
/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_021) DOX_DES_TAG(DES_VPS_DSS_001)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1793) DOX_REQ_TAG(PDK-788) DOX_REQ_TAG(PDK-99)
 */

#ifndef VPS_DSSDRV_H_
#define VPS_DSSDRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 *  Macros for different driver instance numbers to be passed as instance ID
 *  at the time of driver create.
 *  Note: These are read only macros. Don't modify the value of these macros.
 */

/**
 *  \name DSS Display Instance ID's
 *
 *  @{
 */
/** \brief Video Pipeline 1 display driver instance number. */
#define VPSDRV_DISP_INST_DSS_VID1          (0U)
/** \brief Video Pipeline 2 display driver instance number. */
#define VPSDRV_DISP_INST_DSS_VID2          (1U)
/**
 *  \brief Video Pipeline 3 display driver instance number.
 *  This video instance is not applicable for TDA3xx platform
 */
#define VPSDRV_DISP_INST_DSS_VID3          (2U)
/** \brief Graphics Pipeline 1 display driver instance number. */
#define VPSDRV_DISP_INST_DSS_GFX1          (3U)
/* @} */
/** \brief Max Number of disp instances for error check. */
#define VPS_DISP_INST_MAX                  (4U)

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DispInstObj_t VpsDrv_DispInstObj;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_DispInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32             drvInstId;
    /**< Instance ID. */
    /* Dc_NodeNum              dctrlNodeNum; */
    /**< Node number for registering to display controller. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
} VpsDrv_DispInitParams;

/**
 *  \brief Platform specific data containing base address information of
 *  DSS module.
 */
typedef struct
{
    VpsDrv_DispInitParams DispDrvInitPrms[VPS_DISP_INST_MAX];
    /**< Capture driver init parameters. */
} VpsDrv_DssPlatformData;

/**
 *  \brief Per instance information.
 */
struct VpsDrv_DispInstObj_t
{
    UInt32             drvInstId;
    /**< Instance ID. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
    VpsCore_Handle     coreHandle;
    /**< Core handle. */
    UInt32             isPrevBufRep;
    /**< Flag to check if previous buffer is repeated. */
    UInt32             standard;
    /**< VENC Standard like NTSC, 1080p etc to which the display driver
     *   path is connected. For valid values see FVID2_Standard. */
    UInt32             dispWidth;
    /**< Width of the display at the VENC in pixels to which the
     *   display driver path is connected. */
    UInt32             dispHeight;
    /**< Height of the display at the VENC in linesto which the
     *   display driver path is connected. */
    UInt32             vencId;
    /**< Venc ID to which this display instance is connected. */
};

/**
 *  \brief DSS parameters used in set/get DSS params.
 */
typedef struct
{
    Fvid2_Format           inFmt;
    /**< Input FVID frame format. */
    UInt32                 tarWidth;
    /**< Horizontal Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                 tarHeight;
    /**< Verticle Size of picture at output of video pipeline
     *   Not used in case of Graphics instance. */
    UInt32                 posX;
    /**< X position of the frame in the output Video Window . */
    UInt32                 posY;
    /**< Y position of the frame in the output Video Window . */
    UInt32                 memType;
    /**< Memory type. For valid values see #Vps_VpdmaMemoryType.
     *   Note: Tiler Memory is not supported as of now, user should set this
     *   to VPS_VPDMA_MT_NONTILEDMEM. */
    Vps_DssDispcVidConfig *vidCfg;
    /**< Video Configuration structure, applicable only for Video pipeline
     *   instances, if NULL default configuration will be used */
    Vps_DssDispcGfxConfig *gfxCfg;
    /**< Graphics Configuration structure, applicable only for Graphics pipeline
     *   instances, if NULL default configuration will be used */
} VpsDrv_DispDssParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vps_init
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param args               Pointer to arguments.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_init(Ptr args);

/**
 *  Vps_deInit
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param args               Pointer to arguments.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_deInit(Ptr args);

/**
 *  VpsDrv_dssOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param dssInstId         Dss Instance ID dssInstId
 *  \param OpenParams        Capture Driver parameters VpsCore_OpenPrms
 *  \param dssOpenParams     VIP specific parameters VpsCore_DssOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DispInstObj *VpsDrv_dssOpen(
    UInt32                 dssInstId,
    VpsCore_OpenPrms      *OpenParams,
    VpsCore_DssOpenParams *dssOpenParams);

/**
 *  VpsDrv_dssClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Dss Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssClose(VpsDrv_DispInstObj *pObj);

/**
 *  VpsDrv_dssStart
 *  \brief Start capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStart(VpsDrv_DispInstObj *pObj);

/**
 *  VpsDrv_dssStop
 *  \brief Stop capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStop(VpsDrv_DispInstObj *pObj);

/**
 *  VpsDrv_dssSetParams
 *  \brief Set capture params for specified handle
 *
 *  \param instObj           Capture Handle #VpsDrv_DispInstObj
 *  \param dssPrms        Path configuration #VpsDrv_DispDssParams
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssSetParams(VpsDrv_DispInstObj         *instObj,
                          const VpsDrv_DispDssParams *dssPrms);

/**
 *  VpsDrv_dssGetParams
 *  \brief Get capture params for specified handle. If not configured, this will
 *  return a default configuration
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *  \param dssParams    Pointer to VpsCore_DispDssParams where configuration
 *                                           will be copied
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssGetParams(VpsDrv_DispInstObj    *pObj,
                          VpsCore_DispDssParams *dssParams);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_DSSDRV_H_ */
