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
 *  \file vpscore_vpePriv.h
 *
 *  \brief VPS Core internal header file for VPE path.
 *
 */

#ifndef VPSCORE_VPEPRIV_H_
#define VPSCORE_VPEPRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_chrus.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dei.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_sc.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_m2m.h>
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_vpe.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Number of descriptors needed per window. This depends whether
 *  the input is 422P or 420T or 422T. Since VPE path supports 420T and 422T,
 *  this is set as 2 as both these formats requires two descriptors.
 */
#define VCORE_VPE_NUM_DESC_PER_WINDOW   (2U)

/** \brief Number of VPDMA frame start event regsiter. */
#define VCORE_VPE_MAX_VPDMA_FS_EVT_REG  (VCORE_VPE_MAX_IN_CH)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Typedef for VPE path instance object. */
typedef struct Vcore_VpeInstObj_t Vcore_VpeInstObj;

/**
 *  struct Vcore_VpeChObj
 *  \brief Per channel information.
 */
typedef struct
{
    Vcore_M2mStates     state;
    /**< Current state. */
    Vcore_VpeParams     corePrms;
    /**< VPE config parameters. */

    Vcore_M2mDeiCtxInfo ctxInfo;
    /**< DEI context information and state. */

    Vcore_M2mDescInfo   descInfo;
    /**< Data descriptor information to be used by driver to allocate
     *   data and config descriptor memories required by this core. */
    UInt32              numExtraDesc;
    /**< Number of extra descriptors needed at the end of the frame i.e. after
     *   the last mosaic data descriptor. This includes dummy data descriptor,
     *   SOCH descriptor on actual or last window free channel, abort
     *   descriptor on actual channel and abort descriptors on free channel of
     *   last window in all rows. Used in non-mosaic configuration. */
    Bool              isDummyNeeded;
    /**< Specifies if an dummy channel would be required. Used in non-mosaic
     *   configuration. */

    VpsHal_VpdmaFSEvent fsEvent;
    /**< Frame start event. */

    UInt32              isDescReq[VCORE_VPE_MAX_VPDMA_CH];
    /**< Flag to indicate whether a descriptor is required or not. */
    UInt32              isDescDummy[VCORE_VPE_MAX_VPDMA_CH];
    /**< Flag to indicate whether a descriptor is dummy or not. */

    UInt32              descOffset[VCORE_VPE_MAX_VPDMA_CH];
    /**< Byte offset to descriptor memory for each of the VPE descriptors. */
    UInt32              bufIndex[VCORE_VPE_NUM_DESC_PER_WINDOW];
    /**< Buffer index to program the channel address of the VPDMA. */

    VpsHal_ChrusConfig  chrusHalCfg;
    /**< Chroma upsampler HAL configuration. */
    VpsHal_DeiConfig    deiHalCfg;
    /**< Deinterlacer HAL configuration. */
    Vps_ScConfig        scHalCfg;
    /**< Scaler HAL configuration. */
    Vps_ScAdvConfig     scHalAdvCfg;
    /**< Scaler HAL advance configuration - used for allocation. */

    UInt32              numFsEvtReg;
    /**< Number of frame start event registers for this instance. */
    UInt32              fsCfgOvlySize;
    /**< Size (in bytes) of VPDMA register configuration overlay memory
     *   required for programming the frame start event. */
    UInt32             *fsRegOffset[VCORE_VPE_MAX_VPDMA_FS_EVT_REG];
    /**< Array of register offsets for all the frame start registers that
     *   needs to be programmed through VPDMA. */
    UInt32              fsVirRegOffset[VCORE_VPE_MAX_VPDMA_FS_EVT_REG];
    /**< Array of virtual register offsets in the VPDMA register configuration
     *   overlay memory corresponding to fsRegOffset member. */
} Vcore_VpeChObj;

/**
 *  struct Vcore_VpeHandleObj
 *  \brief Per handle information.
 */
typedef struct
{
    UInt32            isUsed;
    /**< Flag to indicate whether the handle object is already used. */
    Vcore_VpeInstObj *instObj;
    /**< Pointer to the instance object. */
    Vcore_VpeChObj   *chObjs[VCORE_VPE_MAX_CHANNELS];
    /**< Pointer to the channel information. Array of pointers is used so that
     *   memory for each channel could be allocated from the pool. */
    UInt32            numCh;
    /**< Number of channels for this handle. This determines the number of
     *   valid pointers in channel array. */
} Vcore_VpeHandleObj;

/**
 *  struct Vcore_VpeInstObj_t
 *  \brief Per instance information.
 */
struct Vcore_VpeInstObj_t
{
    UInt32                instId;
    /**< Instance number/ID. */
    UInt32                numHandle;
    /**< Number of handles for this instance. This determines the size of
     *   handle array. */
    VpsHal_VpdmaChannel   vpdmaCh[VCORE_VPE_MAX_VPDMA_CH];
    /**< Array to store the VPDMA channel number required by core. */
    VpsHal_Handle         halHandle[VCORE_VPE_MAX_HAL];
    /**< Array to store the HAL handles required by core. */
    VpsHal_VpdmaPath      vpdmaPath;
    /**< VPDMA Path name. */

    UInt32                openCnt;
    /**< Counter to keep track of number of open calls for an instance. */
    UInt32                numDescPerWindow;
    /**< Number of descriptors required per window. */

    Vcore_VpeHandleObj    hObjs[VCORE_VPE_MAX_HANDLES];
    /**< Pointer to the handle information. This is a contiguous memory of
     *   numHandle Vcore_VpeHandleObj structure. */

    UInt32                halShadowOvlySize[VCORE_VPE_MAX_HAL];
    /**< Array to store the shadow overlay size for each module. */
    VpsHal_GetCfgOvlySize getCfgOvlySize[VCORE_VPE_MAX_HAL];
    /**< Array to store the overlay size function pointer for each HAL. */
    VpsHal_CreateCfgOvly  createCfgOvly[VCORE_VPE_MAX_HAL];
    /**< Array to store the create overlay function pointer for each HAL. */
    UInt32                ovlyOffset[VCORE_VPE_MAX_HAL];
    /**< Byte offset to overlay memory for each HAL. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * VPE core common APIs
 */
Int32 vcoreVpeInit(UInt32 numInst, const Vcore_VpeInitParams *initPrms);
Int32 vcoreVpeDeInit(void);

Vcore_VpeHandleObj *vcoreVpeAllocHandleObj(UInt32 instId);
Int32 vcoreVpeFreeHandleObj(Vcore_VpeHandleObj *hObj);
Int32 vcoreVpeAllocChObjs(Vcore_VpeHandleObj *hObj, UInt32 numCh);
Int32 vcoreVpeFreeChObjs(Vcore_VpeHandleObj *hObj, UInt32 numCh);

Int32 vcoreVpeCheckParams(const Vcore_VpeInstObj *instObj,
                          const Vcore_VpeParams  *corePrms);

/*
 * VPE core deinterlacer related APIs
 */
Int32 vcoreVpeProgramDesc(const Vcore_VpeInstObj *instObj,
                           const Vcore_VpeChObj   *chObj,
                           const Vcore_M2mDescMem *descMem);
Int32 vcoreVpeProgramPrevFldDesc(const Vcore_VpeInstObj *instObj,
                                  const Vcore_VpeChObj   *chObj,
                                  const Vcore_M2mDescMem *descMem);
Int32 vcoreVpeProgramCurOutDesc(const Vcore_VpeInstObj *instObj,
                                 const Vcore_VpeChObj   *chObj,
                                 const Vcore_M2mDescMem *descMem);
Int32 vcoreVpeProgramMvDesc(const Vcore_VpeInstObj *instObj,
                             const Vcore_VpeChObj   *chObj,
                             const Vcore_M2mDescMem *descMem);
Int32 vcoreVpeProgramMvstmDesc(const Vcore_VpeInstObj *instObj,
                                const Vcore_VpeChObj   *chObj,
                                const Vcore_M2mDescMem *descMem);

Int32 vcoreVpeFigureOutState(const Vcore_VpeInstObj *instObj,
                             Vcore_VpeChObj         *chObj,
                             const Vcore_VpeParams  *corePrms);

Int32 vcoreVpeUpdateMode(Vcore_VpeInstObj       *instObj,
                         const Vcore_VpeChObj         *chObj,
                         const Vcore_M2mDescMem *descMem,
                         UInt32                  prevFldState);

/*
 * VPE core HAL APIs
 */
void vcoreVpeInitHalParams(Vcore_VpeInstObj          *instObj,
                           const Vcore_VpeInitParams *initPrms);
Int32 vcoreVpeSetChParams(const Vcore_VpeInstObj *instObj,
                          Vcore_VpeChObj         *chObj,
                          const Vcore_VpeParams  *corePrms);
Int32 vcoreVpeSetDescInfo(const Vcore_VpeInstObj *instObj,
                          const Vcore_VpeChObj   *chObj,
                          Vcore_M2mDescInfo      *descInfo,
                          UInt32                  numFirstRowDesc);
Int32 vcoreVpeSetFsEvent(const Vcore_VpeInstObj *instObj,
                         const Vcore_VpeChObj   *chObj,
                         const Vcore_M2mDescMem *descMem);
Int32 vcoreVpeProgramReg(const Vcore_VpeInstObj *instObj,
                         const Vcore_VpeChObj   *chObj,
                         const Vcore_M2mDescMem *descMem);
Int32 vcoreVpeProgramFmdReg(const Vcore_VpeHandleObj *hObj,
                            const Vps_DeiFmdConfig   *fmdCfg,
                            const Vcore_M2mDescMem   *descMem);
Int32 vcoreVpeProgramFmdUpdateReg(const Vcore_VpeHandleObj     *hObj,
                                  const Vps_DeiFmdUpdateConfig *fmdCfg,
                                  const Vcore_M2mDescMem       *descMem);
Int32 vcoreVpeGetAdvCfgIoctl(const Vcore_VpeHandleObj *hObj,
                             Vps_DeiRdWrAdvCfg  *advCfg);
Int32 vcoreVpeSetAdvCfgIoctl(const Vcore_VpeHandleObj      *hObj,
                             const Vps_DeiRdWrAdvCfg *advCfg);
Int32 vcoreVpeScGetAdvCfgIoctl(Vcore_VpeHandleObj   *hObj,
                               Vcore_M2mScCfgParams *scCfgPrms);
Int32 vcoreVpeScSetAdvCfgIoctl(Vcore_VpeHandleObj         *hObj,
                               const Vcore_M2mScCfgParams *scCfgPrms);
Int32 vcoreVpeGetFmdStatIoctl(const Vcore_VpeHandleObj  *hObj,
                              Vps_DeiFmdStatusReg *statusReg);
Int32 vcoreVpeSetRangMapRedtCfgIoctl(Vcore_VpeHandleObj     *hObj,
                                     const Vps_RngMapRdtCfg *rngMapRdtCfg);
Int32 vcoreVpeGetRangMapRedtCfgIoctl(Vcore_VpeHandleObj *hObj,
                                     Vps_RngMapRdtCfg   *rngMapRdtCfg);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSCORE_VPEPRIV_H_ */
