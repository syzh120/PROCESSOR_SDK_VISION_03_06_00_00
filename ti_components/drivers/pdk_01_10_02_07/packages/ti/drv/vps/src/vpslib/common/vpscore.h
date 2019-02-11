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
 *  \ingroup BSP_DRV_VPS_API
 *  \addtogroup BSP_DRV_VPS_CORE_API VPS - Core API for VIP/VPE/DSS
 *
 *  @{
 */

/**
 *  \file vpscore.h
 *
 *  \brief VPS core interface.
 *  This file defines the commom interface for the each of the core
 *  modules present in VPS.
 */

#ifndef VPS_CORE_H_
#define VPS_CORE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Global handle representation for CORE before CORE has been opened. */
#define VPSCORE_COMMON_HANDLE        (0xFFFFFFFFU)

/** \brief Typedef for Core driver instance handle returned by init function. */
typedef Ptr VpsCore_Inst;

/** \brief Typedef for Core driver handle returned by open function. */
typedef Ptr VpsCore_Handle;

/**
 *  enum VpsCore_Name
 *  \brief Enumerations for the core names.
 */
typedef enum
{
    VPSCORE_CAPT_VIP,
    /**< VIP core. */
    VPSCORE_CAPT_ISS,
    /**< ISS core. */
    VPSCORE_DISP_DSS,
    /**< DSS core. */
    VPSCORE_DISP_DCTRL,
    /**< DCTRL core. */
    VPSCORE_DISP_DSSWB,
    /**< DSSWB core. */
    VPSCORE_MAX
    /**< Should be the last value of this enumeration.
     *   Will be for validating the input parameters. */
} VpsCore_Name;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsCore_Property
 *  \brief Properties of a particular core.
 */
typedef struct
{
    VpsCore_Name name;
    /**< Core name. */
    Bool         isDropDataSupport;
    /**< Set this to TRUE if the hardware corresponding to the core supports
     *   drop data feature. This will be used by the driver to decide what
     *   to do when the application is not queueing data at the capture/display
     *   rate. */
} VpsCore_Property;

/**
 *  enum VpsCore_Frame
 *  \brief Frame structure containing information about video buffer exchanged
 *  between driver and core.
 */
typedef struct
{
    void  *drvData;
    /**< Driver specific data - used by driver, core can't modify or use. */
    UInt32 streamId;
    /**< 0 - STREAM ID MAX used in single channel,
     *   or for anc-data in multi-channel. */
    UInt32 chId;
    /**< 0-15 maps to actual VPDMA-channel – used in multi-channel. */
    Ptr    addr[FVID2_MAX_FIELDS][FVID2_MAX_PLANES];
    /**< Array of frame buffer pointers for given stream.
     *   Size of array shall be "numFrames"
     *   Each entry is equivalent to "addr" in #Fvid2_Frame. */
    UInt32 dropFrm;
    /**< If TRUE core should drop the frame. */
    Ptr    rtParams;
    /**< run time parameters that can be changed for each frames
     *   e.g height,width,position of frame etc  */

    /*
     * Below variables are output status from the core at the time of frame
     * done callback.
     */
    UInt32 fid;
    /**< Indicates whether this frame belong to top or bottom field.
     *   For valid values see #Fvid2_Fid. */
    UInt32 width;
    /**< Captured width in pixels. */
    UInt32 height;
    /**< Captured height in lines. */
    Ptr    coreStats;
    /**< Some additional statistics information which core can provide for
     *   debugging. eg: HW errors observed. */
    UInt32 status;
    /**< Status of the frame, see #Fvid2_FrameStatus for the valid values.
            This will be update by the cores to indicate validity of frame */
} VpsCore_Frame;

/**
 *  \brief Extern function to be implemented by driver to provide a new frame
 *  buffers from application to the core.
 */
typedef VpsCore_Frame * (*VpsCore_ReqFrameCb)(void  *drvData,
                                              UInt32 streamId,
                                              UInt32 chId);

/**
 *  \brief Extern callback function to be implemented by driver to free
 *  up buffers to the application specified by the core.
 */
typedef Int32 (*VpsCore_FrameDoneCb)(void                *drvData,
                                     const VpsCore_Frame *frm);

typedef Int32 (*VpsCore_FrameDoneNotifyCb)(void *drvData);

/**
 *  \brief Extern callback function to be implemented by driver to notify
 *      completion of reception of sub-frame
 */
typedef Int32 (*VpsCore_SubFrameCbFxn)(void                 *drvData,
                                        const VpsCore_Frame *frm,
                                        Fvid2_SubFrameInfo  *subFrmInfo);

/**
 *  enum VpsCore_Frame
 *  \brief Frame structure containing information about video buffer exchanged
 *  between driver and core.
 */
typedef struct
{
    void                     *drvData;
    /**< Driver specific data which will be passed during callback functions. */
    VpsCore_ReqFrameCb        reqFrmCb;
    /**< Request frame callback function. This cannot be NULL. */
    VpsCore_FrameDoneCb       frmDoneCb;
    /**< Frame complete callback function. This cannot be NULL. */
    VpsCore_FrameDoneNotifyCb frmDoneNotifyCb;
    /**< Frame completion notification to upper layer, can be NULL
     *   depending on the driver */
} VpsCore_OpenPrms;

/** \brief Typedef for core open function pointer. */
typedef VpsCore_Handle (*VpsCore_Open)(VpsCore_Inst            instObj,
                                       const VpsCore_OpenPrms *openPrms,
                                       const void             *coreOpenPrms,
                                       void                   *coreReturnPrms);

/** \brief Typedef for core close function pointer. */
typedef Int32 (*VpsCore_Close)(VpsCore_Handle handle);

/** \brief Typedef for core get property function pointer. */
typedef Int32 (*VpsCore_GetProperty)(VpsCore_Inst      instObj,
                                     VpsCore_Property *property);

/**
 *  \brief Typedef for core set parameters function pointer.
 *  Each core will have its own set of params and will be defined in the
 *  respective core header file.
 */
typedef Int32 (*VpsCore_SetParams)(VpsCore_Handle handle,
                                   const void    *params,
                                   void          *subFrameRetPrms);

/**
 *  \brief Typedef for core get parameters function pointer.
 *  Each core will have its own set of params and will be defined in the
 *  respective core header file.
 */
typedef Int32 (*VpsCore_GetParams)(VpsCore_Handle handle, void *params);

/** \brief Typedef for core control functions. */
typedef Int32 (*VpsCore_Control)(VpsCore_Handle handle,
                                 UInt32         cmd,
                                 void          *appArgs,
                                 void          *drvArgs);

/**
 *  \brief Typedef for core start function pointer.
 *  This will start the capture/display/m2m operation.
 */
typedef Int32 (*VpsCore_Start)(VpsCore_Handle handle);

/**
 *  \brief Typedef for core stop function pointer.
 *  This will stop the capture/display/m2mure operation.
 */
typedef Int32 (*VpsCore_Stop)(VpsCore_Handle handle);

/**
 *  \brief Typedef for core process function pointer.
 *  This should be called by the driver when it gets the VSYNC interrupt from
 *  the hardware.
 */
typedef Int32 (*VpsCore_ProcessIsr)(VpsCore_Handle handle, UInt32 chId);

/**
 *  \brief Typedef for core prog buffer function pointer.
 *  This should be called by the driver when it gets the buffer from app and if
 *  previous buffer is repeated.
 */
typedef Int32 (*VpsCore_progBuffer)(VpsCore_Handle handle,
                                    VpsCore_Frame *frm,
                                    UInt32 bypassLowLatencyCheck);

/**
 *  \brief Typedef for core to program multiple frame pointers.
 */
typedef Int32 (*VpsCore_putFrames)(VpsCore_Handle  handle,
                                   VpsCore_Frame **frm);

/**
 *  \brief Typedef for core to get multiple frame pointers back.
 */
typedef Int32 (*VpsCore_getFrames)(VpsCore_Handle  handle,
                                   VpsCore_Frame **frm);

/**
 *  \brief Typedef for core get Error Status function pointer.
 *  Each core will have its own set of params and will be defined in the
 *  respective core header file.
 */
typedef Int32 (*VpsCore_getErrorStat)(VpsCore_Handle handle,
                                      void          *retParams);

/**
 *  struct VpsCore_Ops
 *  \brief Structure to store core function pointers.
 */
typedef struct
{
    VpsCore_GetProperty  getProperty;
    /**< Get property function pointer. */
    VpsCore_Open         open;
    /**< Open function pointer. */
    VpsCore_Close        close;
    /**< Close function pointer. */
    VpsCore_SetParams    setParams;
    /**< Set parameters function pointer. */
    VpsCore_GetParams    getParams;
    /**< Get parameters function pointer. */
    VpsCore_Control      control;
    /**< Core control function pointer. */
    VpsCore_Start        start;
    /**< Core start function pointer. */
    VpsCore_Stop         stop;
    /**< Core stop function pointer. */
    VpsCore_ProcessIsr   proc;
    /**< Core Process ISR function pointer. */
    VpsCore_progBuffer   progBuffer;
    /**< Core prog Buffer function pointer. */
    VpsCore_putFrames    putFrames;
    /**< Core put Frames function pointer. */
    VpsCore_getFrames    getFrames;
    /**< Core get Frames function pointer. */
    VpsCore_getErrorStat getErrorStat;
} VpsCore_Ops;

/**
 *  \brief Copies a FVID2 Frame to VPS Frame
 *         Currently Copies only Addresses
 *
 *  \param vpsFrm       [IN] Pointer to VPS Frame.
 *  \param fvid2Frm     [IN] Pointer to FVID2 Frame.
 *
 */
static inline void VpsCore_copyFvid2ToVpsFrame(VpsCore_Frame *vpsFrm,
                                               const Fvid2_Frame   *fvid2Frm);

/**
 *  \brief Copies a VPS Frame to FVID2 Frame
 *         Currently Copies only buffer Addresses
 *
 *  \param fvid2Frm     [IN] Pointer to FVID2 Frame.
 *  \param vpsFrm       [IN] Pointer to VPS Frame.
 *
 */
static inline void VpsCore_copyVpsToFvid2Frame(Fvid2_Frame   *fvid2Frm,
                                               const VpsCore_Frame *vpsFrm);

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static inline void VpsCore_copyFvid2ToVpsFrame(VpsCore_Frame *vpsFrm,
                                               const Fvid2_Frame   *fvid2Frm)
{
    if((NULL != vpsFrm) && (NULL != fvid2Frm))
    {
        vpsFrm->addr[0U][0U] = fvid2Frm->addr[0U][0U];
        vpsFrm->addr[0U][1U] = fvid2Frm->addr[0U][1U];
        vpsFrm->addr[0U][2U] = fvid2Frm->addr[0U][2U];

        vpsFrm->addr[1U][0U] = fvid2Frm->addr[1U][0U];
        vpsFrm->addr[1U][1U] = fvid2Frm->addr[1U][1U];
        vpsFrm->addr[1U][2U] = fvid2Frm->addr[1U][2U];
    }
}

static inline void VpsCore_copyVpsToFvid2Frame(Fvid2_Frame   *fvid2Frm,
                                               const VpsCore_Frame *vpsFrm)
{
    if((NULL != vpsFrm) && (NULL != fvid2Frm))
    {
        fvid2Frm->addr[0U][0U] = vpsFrm->addr[0U][0U];
        fvid2Frm->addr[0U][1U] = vpsFrm->addr[0U][1U];
        fvid2Frm->addr[0U][2U] = vpsFrm->addr[0U][2U];

        fvid2Frm->addr[1U][0U] = vpsFrm->addr[1U][0U];
        fvid2Frm->addr[1U][1U] = vpsFrm->addr[1U][1U];
        fvid2Frm->addr[1U][2U] = vpsFrm->addr[1U][2U];
    }
}

#ifdef __cplusplus
}
#endif

#endif /* VPS_CORE_H_ */

/* @} */
