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
 *  \file vpscore_dctrlIntr.h
 *
 *  \brief VPS CORE Display Controller internal header file
 *  This file exposes the APIs of the VPS Display Controller to the other
 *  drivers.
 *
 */

#ifndef VPSCORE_DCTRLINTR_H_
#define VPSCORE_DCTRLINTR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dssWb.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * enum VpscoreDctrl_NodeNum_t
 * \brief Enum defining input Node Number. Each pipeline can be input node to
 *  the display contoller.
 */
typedef enum VpscoreDctrl_NodeNum_t
{
    VPSCORE_DCTRL_NODE_VID1 = 1,
    VPSCORE_DCTRL_NODE_VID2 = 2,
    VPSCORE_DCTRL_NODE_VID3 = 3,
    VPSCORE_DCTRL_NODE_GFX  = 4,
    VPSCORE_DCTRL_NODE_WB   = 5,
    VPSCORE_DCTRL_NODE_LCD1 = 6,
    VPSCORE_DCTRL_NODE_LCD2 = 7,
    VPSCORE_DCTRL_NODE_LCD3 = 8,
    VPSCORE_DCTRL_NODE_HDMI = 9
} VpscoreDctrl_NodeNum;

/* Typedef for display controller client handle */
typedef void *VpscoreDctrlClientHandle;

/**
 * Int32 (*VpscoreDctrl_ClientCbFxn) (Ptr arg)
 * \brief Client call back function. This function will be called by the
 * Display Controller during Vsync event of LCD to whcih this node is connected
 * to. fid specified the field ID.Applicable only in case of Interlaced
 * display.
 */
typedef void (*Vpscore_dctrlClientCbFxn)(Ptr arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * struct VpscoreDctrl_ClientInfo_t
 * \brief Structure containing client information. All inputs are
 * considered as clients to the display controller Core. Each client
 * registers with the display controller Core by passing pointer to this
 * structure.
 */
typedef struct Vpscore_dctrlClientInfo_t
{
    Vpscore_dctrlClientCbFxn cbFxn;
    /**< Client call back function, which will be called by Display Controller
     *   to update buffer pointers */
    Ptr                      arg;
    /**< Private data of the client */
    UInt32                   inNode;
    /**< Node that is connected to client, applicable only for WB client. */
    UInt32                   clientMode;
    /**< Mode in which client operates, m2m/Capture WB mode
     *   applicable only for WB client. */
} Vpscore_dctrlClientInfo;

/**
 * struct Vpscore_dctrlPathInfo
 * \brief Structure for getting path information for the given client.
 *
 */
typedef struct
{
    UInt32 vencId;
    /**< Identifies the VENC on which mode parameters is to be applied.
     *   Use one of VPS_DCTRL_DSS_VENC_LCD1, VPS_DCTRL_DSS_VENC_LCD2,
     *   VPS_DCTRL_DSS_VENC_LCD3, VPS_DCTRL_DSS_VENC_HDMI macro for this
     *   variable. */
    UInt32 isVencRunning;
    /**< Flag to indicate whether VENC is running or not. This is
     *   read only parameter returned from the display controller to
     *   indicated whether given venc is running or not. */
    UInt32 standard;
    /**< [IN] Standard for which to get the info.
     *   For valid values see #FVID2_Standard. */
    UInt32 width;
    /**< Active video frame width in pixels. */
    UInt32 height;
    /**< Active video frame height in lines. */
    UInt32 scanFormat;
    /**< Scan format of standard. For valid values see #FVID2_ScanFormat. */
    Int32  shiftVidPosX;
    /**<Vid position in overlay to be shifted in Number of pixels. */
} Vpscore_dctrlPathInfo;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vpscore_dctrlRegisterClient
 *  \brief Function to register a client to display controller
 *
 *  This function registers the client callbacks with the display controller.
 *
 *  The client can be either present in the same core where master DC resides
 *  or it can reside in some other core. This is differentiated by the
 *  callback parameter value.
 *
 *  \param nodeNum      Input Node Number for which this client is to be
 *                      registered
 *  \param clientInfo   Pointer to client info structure containing client
 *                      information
 *  \param arg          Not used currently. For the future use
 *
 *  \return             Handle to the client if registered successfully
 *                      NULL if not able to register
 */
VpscoreDctrlClientHandle Vpscore_dctrlRegisterClient(
    VpscoreDctrl_NodeNum nodeNum,
    const Vpscore_dctrlClientInfo *
    clientInfo,
    Ptr
    arg);

/**
 *  Vpscore_dctrlUnRegisterClient
 *  \brief Unregisters the clients from display controller.
 *
 *  This function inregisters the display controller client and
 *  de-allocates client objects.
 *  If client is started, it cannot be unregistered. It returns error in
 *  this case
 *  Vpscore_dctrlRegisterClient should be called prior to this call.
 *  Client is freed.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return           Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlUnRegisterClient(VpscoreDctrlClientHandle handle);

/**
 *  Vpscore_dctrlGetPathInfo
 *  \brief Function to get the path information.
 *
 *  Input client driver needs to know the size of the frame and frame mode
 *  by which it should pump input frame data. This function returns the
 *  size of the frame and frame mode to the client at the input node.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *  \param pathInfo   Pointer to path information structure returned by
 *                    display controller
 *
 *  \return           Returns 0 on success else returns error value
 */
/* Change this Client Handle to node information */
Int32 Vpscore_dctrlGetPathInfo(VpscoreDctrlClientHandle handle,
                               Vpscore_dctrlPathInfo   *pathInfo);

/**
 *  Vpscore_dctrlStartClient
 *  \brief
 *
 *
 *  The state for the client changes to started.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return           Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlStartClient(VpscoreDctrlClientHandle handle);

/**
 *  Vpscore_dctrlStopClient
 *  \brief
 *
 *
 *  The state for the client changes to started.
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return           Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlStopClient(VpscoreDctrlClientHandle handle);

/**
 *  Vpscore_dctrlReadytoSetGoBit
 *  \brief All update of registers is done and its ready to set the go bit
 *
 *
 *  The Dss core has updated all the vid/gfx pipeline registers and its ready
 *  to set the go bit. Once all the pipelines connected to a particular Overlay
 *  manager are done with updating pipeline registes, display controller will
 *  will set the go bit of overlay manager
 *
 *  \param handle     Valid client handle returned by
 *                    Vpscore_dctrlRegisterClient function
 *
 *  \return                Returns 0 on success else returns error value
 */

Int32 Vpscore_dctrlReadyToSetGoBit(VpscoreDctrlClientHandle handle);

/**
 *  Vpscore_dctrlIsSafeToPush
 *  \brief check if it is safe to program the Buffer.Its safe
 *         to program before the line number interrupt and after the vsync
 *         interrupt. This is required for low latency display.
 *         This call should be gaurded by the disabling the interrupt.The same
 *         variable is modified in the interrupt.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *
 *  \return                Returns TRUE if its safe else FALSE
 */
UInt32 Vpscore_dctrlIsSafeToPush(VpscoreDctrlClientHandle handle);

/**
 *  Vpscore_dctrlGetCurLineNumber
 *  \brief Get the current Line Number of the corresponding LCD
 *
 *
 *  This is to Check if its safe to program the buffer in DSS registers.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *  \param lineNumber  Pointer to lineNumber Variable.
 *
 *  \return                Returns 0 on success else returns error value
 */

Int32 Vpscore_dctrlGetCurLineNumber(VpscoreDctrlClientHandle handle,
                                    UInt32                  *lineNumber);

/**
 *  Vpscore_dctrlGetDssVidErrorCount
 *  \brief Get the error count for VID/GFX pipeline instance.
 *
 *
 *  This is to get the error counts like underflow.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *  \param retParams  Pointer to error status register.
 *
 *  \return                Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlGetDssVidErrorCount(VpscoreDctrlClientHandle   handle,
                                       VpsCore_DssVidErrorStatus *retParams);

/**
 *  Vpscore_dctrlGetDssWbErrorCount
 *  \brief Get the error count for WB pipeline instance.
 *
 *
 *  This is to get the error counts like overflow/Incomplete error.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *  \param retParams  Pointer to error status register.
 *
 *  \return                Returns 0 on success else returns error value
 */
Int32 Vpscore_dctrlGetDssWbErrorCount(VpscoreDctrlClientHandle  handle,
                                      VpsCore_DssWbErrorStatus *retParams);

/**
 *  Vpscore_dctrlClrErrorCount
 *  \brief Clears the error count corresponding to particular instance.
 *
 *
 *  This is to clear the error counts like underflow/overflow count.
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *
 *  \return                Returns 0 on success else returns error value
 */
Int32  Vpscore_dctrlClrErrorCount(VpscoreDctrlClientHandle handle);

/**
 *  VpsCore_dctrlPipeUpdateOverlayNode
 *  \brief Update the overlay instance of a dctrl pipe.
 *
 *
 *  \param handle         Valid client handle returned by
 *                                  Vpscore_dctrlRegisterClient function
 *
 *  \param ovlyNode       Overlay Node to be updated for the pipe.
 *
 *  \return                Returns 0 on success else returns error value
 */
Int32 VpsCore_dctrlPipeUpdateOverlayNode(VpscoreDctrlClientHandle handle,
                                         UInt32                   ovlyNode);

#ifdef __cplusplus
}
#endif

#endif /* End of #ifndef VPSCORE_DCTRLINTR_H_ */
