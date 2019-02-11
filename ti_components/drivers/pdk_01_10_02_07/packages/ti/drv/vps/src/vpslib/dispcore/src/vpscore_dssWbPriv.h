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
 *  \file vpscore_dssWbPriv.h
 *
 *  \brief Header file for DSS Writeback core
 *  This file includes data-structures and function declarations for the
 *  the VPS writeback core interface for DSS.
 *
 */

#ifndef DSSWBLIB_PRIV_H_
#define DSSWBLIB_PRIV_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define VPSCORE_DSSWB_DEF_ALIGN  ((uint32_t) 32U)
#define VPSCORE_DSSWB_CAPTURE_NOT_STARTED   (0xFFFFFFFFU)
#define VPSCORE_DSSWB_CAPTURE_STARTED       (0x0U)
#define VPSCORE_DSSWB_ODD_FIELD_CAPTURED    (0x1U)
#define VPSCORE_DSSWB_EVEN_FIELD_CAPTURED   (0x2U)
#define VPSCORE_DSSWB_BOTH_FIELDS_CAPTURED  (VPSCORE_DSSWB_ODD_FIELD_CAPTURED |\
                                             VPSCORE_DSSWB_EVEN_FIELD_CAPTURED)

/**
 *  \brief Writeback pipe disable status.
 */
typedef enum
{
    VPSCORE_DSSWB_PIPE_RUNNING = 0,
    /**< WB pipe is running. */
    VPSCORE_DSSWB_PIPE_DISABLE_COMPLETE,
    /**< WB pipe is Stopped. */
    VPSCORE_DSSWB_PIPE_DISABLE_INITIATED,
    /**< WB pipe is disabled by writing in shadow reg.
         will be effective next vsync */
    VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_1,
    /**< WB pipe to be disabled in next vsync. */
    VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_2,
    /**< WB pipe to be disabled after 2 vsyncs. */
    VPSCORE_DSSWB_PIPE_DISABLE_VSYNC_3
    /**< WB pipe to be disabled after 3 vsyncs. */
} VpsCore_DssWbDisableStatus;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsCore_DssWbObj
 *  \brief DSS WB Core Handle structure. This will be instantiated for each
 *  instance of DSS WB. (Currently there is only one instance of DSS WB)
 */

typedef struct
{
    UInt32               numHandles;
    VpsCore_Handle       pathObjPool[VPSHAL_DSS_DISPC_WB_MAX_INST];
    UInt32               dispcIrqNumber;
    /**< DISPC IRQ number at CPU level INTC. */
    VpscoreDctrl_NodeNum dcNodeNum[VPSHAL_DSS_DISPC_WB_MAX_INST];
    VpsHal_Handle        wbHandle[VPSHAL_DSS_DISPC_WB_MAX_INST];
    BspOsal_IntrHandle   intrHandle;
    /**< Handle to Hardware Interrupt. */
} VpsCore_DssWbObj;

typedef struct
{
    UInt32                      handleId;
    Ptr                         drvData;
    VpsCore_DssWbObj           *parent;
    VpsHal_Handle               pipeHandle;
    /**< HAL handle for WriteBack pipe. */
    VpsCore_ReqFrameCb          reqFrmCb;
    /**< Request frame callback function. This cannot be NULL. */
    VpsCore_FrameDoneCb         frmDoneCb;
    /**< Frame complete callback function. This cannot be NULL. */
    VpsCore_Frame              *progFrame;
    /**< Pointer to Programmed Frame buffer structure
     *   this frame will be programmed in the shadowed registers. */
    VpsCore_Frame              *curFrame;
    /**< Pointer to Current Frame buffer structure.
     *   this frame is currently being displayed */
    VpsHal_DssDispcWbPipeCfg    wbPipeCfg;
    /**< Writeback pipeline HAL structure configuration*/
    VpsHal_DssDispcAdvDmaConfig halAdvDmaCfg;
    /**< Advance dma configuration structure*/
    Bool                        isStarted;
    /**< Variable to indicated if streaming is started. */
    UInt32                      outScanFormat;
    /**< Output scan format, for valid values check #Fvid2_ScanFormat */
    UInt32                      isFieldMergeBuff;
    /**< Variable to check if out buffer should be field merged or not
     *       Valid only if outScanFormat is Interlaced. */
    UInt32                      currentFieldVal;
    /**< Variable to store current field is Top or Bottom. Used only in case of
     *   Interlaced display. */
    UInt32                      fieldsCaptured;
    /**< Variable to store which fields are captured. Used only in case of
     *   Interlaced display. */
    VpscoreDctrl_NodeNum        dcNode;
    /**< Display Controller Node number. */
    VpscoreDctrlClientHandle    dcHandle;
    /**< Display controller Handle. */
    UInt32                      regionBasedBit;
    /**< Region based bit value. */
    BspOsal_SemHandle           pipeDisableSem;
    VpsCore_DssWbDisableStatus  pipeDisableStatus;
} VpsCore_DssWbPathObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TODO - Add description*/
Int32 VpsCore_dssWbGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property);

VpsCore_Handle VpsCore_dssWbOpen(VpsCore_Inst            pDssWbHandle,
                                 const VpsCore_OpenPrms *openPrms,
                                 const void             *coreOpenPrms,
                                 void                   *coreReturnPrms);

Int32 VpsCore_dssWbPathSetConfig(VpsCore_Handle pathHandle,
                                 const void    *params,
                                 void          *retPrms);

Int32 VpsCore_dssWbPathGetConfig(VpsCore_Handle pathHandle,
                                 void          *params);

Int32 VpsCore_dssWbControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs);

Int32 VpsCore_dssWbIsr(VpsCore_Handle pathHandle, UInt32 chId);

Int32 VpsCore_dssWbStart(VpsCore_Handle pathHandle);

Int32 VpsCore_dssWbStop(VpsCore_Handle pathHandle);

Int32 VpsCore_dssWbClose(VpsCore_Handle pathHandle);

Int32 VpsCore_dssWbGetErrorStat(VpsCore_Handle pathHandle,
                                void          *params);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* DSSLIB_PRIV_H_ */
