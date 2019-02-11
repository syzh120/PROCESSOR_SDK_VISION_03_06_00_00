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
 *  \file vpscore_m2m.h
 *
 *  \brief VPS Core common header file.
 *  This file defines the commom interface for the each of the core modules
 *  present in VPS.
 *
 */

#ifndef VPSCORE_M2M_H_
#define VPSCORE_M2M_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/vps_dataTypes.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_vpdma.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_sc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Maximum number of in data descriptors used to allocate the
 *  descriptor pointer array in desc memory structure.
 */
#define VCORE_M2M_MAX_IN_DESC           (VPS_CFG_MAX_IN_DESC)

/**
 *  \brief Maximum number of out data descriptors used to allocate the
 *  descriptor pointer array in desc memory structure.
 */
#define VCORE_M2M_MAX_OUT_DESC          (VPS_CFG_MAX_OUT_DESC)

/**
 *  \brief Maximum number VPDMA channels returned in descriptor info structure.
 */
#define VCORE_M2M_MAX_VPDMA_CH          (20U)

/**
 *  \brief Typedef for Core driver handle.
 */
typedef Ptr Vcore_M2mHandle;

/** \brief IOCTL base address for the common IOCTLs listed below. */
#define VCORE_M2M_COMMON_IOCTL_BASE     (0x00000000U)
/** \brief IOCTL base address for the custom IOCTLs of each cores. */
#define VCORE_M2M_CUSTOM_IOCTL_BASE     (0x00000100U)

/** \brief Control command to get DEI configuration. */
#define VCORE_M2M_IOCTL_GET_DEI_CFG     (VCORE_M2M_COMMON_IOCTL_BASE + 0x0000U)
/** \brief Control command to set DEI configuration. */
#define VCORE_M2M_IOCTL_SET_DEI_CFG     (VCORE_M2M_COMMON_IOCTL_BASE + 0x0001U)
/** \brief Control command to get SC configuration. */
#define VCORE_M2M_IOCTL_GET_SC_CFG      (VCORE_M2M_COMMON_IOCTL_BASE + 0x0002U)
/** \brief Control command to set SC configuration. */
#define VCORE_M2M_IOCTL_SET_SC_CFG      (VCORE_M2M_COMMON_IOCTL_BASE + 0x0003U)
/** \brief Control command to get FMD status register configuration. */
#define VCORE_M2M_IOCTL_GET_DEI_FMD_STAT    (VCORE_M2M_COMMON_IOCTL_BASE + \
                                             0x0004U)
/** \brief Control command to set Range Map and Range Reduction configuration.*/
#define VCORE_M2M_IOCTL_SET_RANGE_MAP_REDUCT_CFG (VCORE_M2M_COMMON_IOCTL_BASE + \
                                                  0x0005U)
/** \brief Control command to get Range Map and Range Reduction configuration.*/
#define VCORE_M2M_IOCTL_GET_RANGE_MAP_REDUCT_CFG (VCORE_M2M_COMMON_IOCTL_BASE + \
                                                  0x0006U)

/**
 *  enum Vcore_M2mName
 *  \brief Enumerations for the core names.
 */
typedef enum
{
    VCORE_M2M_VPE = 0U,
    /**< VPE path core. */
    VCORE_M2M_DWB = 1U,
    /**< DEI writeback path core. */
    VCORE_M2M_FORCE_INT = 0x7FFFFFFFU
                          /**< This will ensure enum is not packed, will always be contained in int */
} Vcore_M2mName;

/**
 *  enum Vcore_M2mType
 *  \brief Enumerations for the core types.
 */
typedef enum
{
    VCORE_M2M_TYPE_INPUT = 0U,
    /**< Input core. */
    VCORE_M2M_TYPE_OUTPUT = 1U,
    /**< Output core. */
    VCORE_M2M_TYPE_INTERMEDIATE = 2U,
    /**< Intermediate core - doesn't consume input or output frames. */
    VCORE_M2M_TYPE_FORCE_INT = 0x7FFFFFFFU
                               /**< This will ensure enum is not packed, will always be contained in int */
} Vcore_M2mType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vcore_M2mProperty
 *  \brief Properties of a particular core.
 */
typedef struct
{
    UInt32        numInstance;
    /**< Number of instance supported by the core - This depends on the number
     *   of similar hardware paths available. Note: This is different from the
     *   software channel supported by each core. */
    Vcore_M2mName name;
    /**< Core name. */
    Vcore_M2mType type;
    /**< Core type. */
    Bool          internalContext;
    /**< Flag indicating whether the core has any internal context or not.
     *   This is used for core like DEI which has to update the internal
     *   context buffers. */
} Vcore_M2mProperty;

/**
 *  struct Vcore_M2mFormat
 *  \brief Core format information.
 */
typedef struct
{
    UInt32       frameWidth;
    /**< Frame width. */
    UInt32       frameHeight;
    /**< Frame height. */
    UInt32       startX;
    /**< Horizontal start position in pixels. */
    UInt32       startY;
    /**< Vertical start position in lines. */
    UInt32       secScanFmt;
    /** Secondary scan format. For input cores, this represents the scan format
     *  that needs to be sent out of the core. For output cores, this
     *  represents the input scan format for that core.
     *  For valid values see #Fvid2_ScanFormat. */
    UInt32       memType;
    /**< VPDMA Memory type. For valid values see #Vps_VpdmaMemoryType. */
    Fvid2_Format fmt;
    /**< FVID frame format. */
} Vcore_M2mFormat;

/**
 *  struct Vcore_M2mDescInfo
 *  \brief Data and config descriptor information required by the core.
 *  The values for these fields depends on the parameters set for each core.
 */
typedef struct
{
    UInt32                 numInDataDesc;
    /**< Number of inbound data descriptors required. This also includes the
     *   first row descriptors required in multiple window mode. */
    UInt32                 numOutDataDesc;
    /**< Number of outbound data descriptors required. */
    UInt32                 shadowOvlySize;
    /**< Size (in bytes) of the register overlay memory required to program
     *   shadow registers. */
    UInt32                 nonShadowOvlySize;
    /**< Size (in bytes) of the register overlay memory required to program
     *   non-shadow registers. */
    UInt32                 horzCoeffOvlySize;
    /**< Size (in bytes) of the coefficient overlay memory required to program
     *   horizontal scaling coefficients. This is required by cores which have
     *   scaler in their paths. */
    UInt32                 vertCoeffOvlySize;
    /**< Size (in bytes) of the coefficient overlay memory required to program
     *   vertical scaling coefficients. This is required by cores which have
     *   scaler in their paths. */
    UInt32                 vertBilinearCoeffOvlySize;
    /**< Size (in bytes) of the coefficient overlay memory required to program
     *   vertical bilinear scaling coefficients. This is required by cores which
     *   have HQ scaler in their paths. */
    VpsHal_VpdmaConfigDest coeffConfigDest;
    /**< VPDMA configuration register destination for the above coefficient.
     *   This will identify the scaler to which the coefficient needs to be
     *   applied. */
    VpsHal_VpdmaChannel    socChNum[VCORE_M2M_MAX_VPDMA_CH];
    /**< Client on which MLM should wait for the end of frame signal. */
    UInt32                 numChannels;
    /**< Number of valid vpdma channels in socChNum array */
} Vcore_M2mDescInfo;

/**
 *  struct Vcore_M2mDescMem
 *  \brief Data descriptor and config overlay memory information needed by the
 *  core to program/update the descriptors and register overlay memory.
 *  The memory for the descriptors and overlay should be allocated by the
 *  display/capture/mem2mem driver. The size of these memories should be
 *  allocated based on the descriptor information structure provided by
 *  the core.
 */
typedef struct
{
    Ptr inDataDesc[VCORE_M2M_MAX_IN_DESC];
    /**< Inbound data descriptor memory pointers. */
    Ptr outDataDesc[VCORE_M2M_MAX_OUT_DESC];
    /**< Outbound data descriptor memory pointers. */
    Ptr shadowOvlyMem;
    /**< Shadow register overlay memory pointer. */
    Ptr nonShadowOvlyMem;
    /**< Non-Shadow register overlay memory pointer. */
    Ptr coeffOvlyMem;
    /**< Coefficient overlay memory pointer. */
} Vcore_M2mDescMem;

/**
 *  struct Vcore_M2mStates
 *  \brief Different states of each channel.
 */
typedef struct
{
    UInt32 isFormatSet;
    /**< Flag to indicate that set format is called for this channel.
     *   Only after setting the format, the channel information could be
     *   used by the display/memory driver. */
    UInt32 isParamsSet;
    /**< Flag to indicate that set params is called for this channel. */
} Vcore_M2mStates;

/**
 *  struct Vcore_M2mDeiCtxInfo
 *  \brief DEI information and state.
 */
typedef struct
{
    UInt32 isDeinterlacing;
    /**< Flag to represent whether DEI is deinterlacing or not. */
    UInt32 isTnrMode;
    /**< Flag to represent whether TNR is enabled or not. */
    UInt32 numPrevFld;
    /**< Number of previous field input buffers needed. */
    UInt32 numCurFldOut;
    /**< Number of current field output buffers needed. */
    UInt32 numMvIn;
    /**< Number of previous MV input buffers needed. */
    UInt32 numMvOut;
    /**< Number of current MV output buffers needed. */
    UInt32 numMvstmIn;
    /**< Number of previous MVSTM input buffers needed. */
    UInt32 numMvstmOut;
    /**< Number of current MVSTM output buffers needed. */
} Vcore_M2mDeiCtxInfo;

/**
 *  Vcore_M2mScUserCoeffParams
 *  \brief Structure for programming the scaler coefficients.
 */
typedef struct
{
    UInt32       hScalingSet;
    /**< [IN] Scaling coefficient set for horizontal scaling.
     *   For valid values see #Vps_ScCoeffSet. */
    UInt32       vScalingSet;
    /**< [IN] Scaling coefficient set for the vertical scaling.
     *   For valid values see #Vps_ScCoeffSet. */
    Vps_ScCoeff *userCoeffPtr;
    /**< [IN] Pointer to the user provided scaling coefficients */
} Vcore_M2mScUserCoeffParams;

/**
 *  Vcore_M2mScGetCoeffParams
 *  \brief Structure for get the scaler coefficients memory pointers.
 */
typedef struct
{
    UInt32 hScalingSet;
    /**< [IN] Scaling coefficient set for horizontal scaling.
     *   For valid values see #Vps_ScCoeffSet. */
    UInt32 vScalingSet;
    /**< [IN] Scaling coefficient set for the vertical scaling.
     *   For valid values see #Vps_ScCoeffSet. */
    void  *horzCoeffMemPtr;
    /**< [OUT] Pointer to overlay memory for the horizontal scaler
     *   coefficients */
    void  *vertCoeffMemPtr;
    /**< [OUT] Pointer to overlay memory for the vertical scaler coefficients */
    void  *vertBilinearCoeffMemPtr;
    /**< [OUT] Pointer to overlay memory for the vertical bilinear scaler
     *   coefficients */
} Vcore_M2mScGetCoeffParams;

/**
 *  Vcore_M2mScCfgParams
 *  \brief Structure for programming the scaler advance configuration.
 */
typedef struct
{
    UInt32                  chNum;
    /**< Channel number for which the configuration is to be set/get.
     *   Used only in M2M mode, for display and capture mode set
     *   this to 0. */
    Vps_ScAdvConfig        *scAdvCfg;
    /**< Scaler HAL configuration.  This is for the advanced user. */
    Ptr                     ovlyPtr;
    /**< Overlay pointer for that channel number.
     *   TODO: Remove this for SWP core. */
    const Vcore_M2mDescMem *descMem;
    /**< Descriptor memory to update the configuration. */
} Vcore_M2mScCfgParams;

/** \brief Typedef for core open function pointer. */
typedef Vcore_M2mHandle (*Vcore_M2mOpen)(UInt32 instId, UInt32 numChannel);

/** \brief Typedef for core close function pointer. */
typedef Int32 (*Vcore_M2mClose)(Vcore_M2mHandle handle);

/** \brief Typedef for core get property function pointer. */
typedef Int32 (*Vcore_M2mGetProperty)(Vcore_M2mHandle    handle,
                                      Vcore_M2mProperty *property);

/** \brief Typedef for core control functions. */
typedef Int32 (*Vcore_M2mControl)(Vcore_M2mHandle handle,
                                  UInt32          cmd,
                                  Ptr             args);

/** \brief Typedef for core set format function pointer. */
typedef Int32 (*Vcore_M2mSetFormat)(Vcore_M2mHandle        handle,
                                    UInt32                 chNum,
                                    const Vcore_M2mFormat *coreFmt);

/** \brief Typedef for core get format function pointer. */
typedef Int32 (*Vcore_M2mGetFormat)(Vcore_M2mHandle  handle,
                                    UInt32           chNum,
                                    Vcore_M2mFormat *coreFmt);

/**
 *  \brief Typedef for core set parameters function pointer.
 *  Each core will have its own set of params and will be defined in the
 *  respective core header file.
 */
typedef Int32 (*Vcore_M2mSetParams)(Vcore_M2mHandle handle,
                                    UInt32          chNum,
                                    const void     *params);

/**
 *  \brief Typedef for core get parameters function pointer.
 *  Each core will have its own set of params and will be defined in the
 *  respective core header file.
 */
typedef Int32 (*Vcore_M2mGetParams)(Vcore_M2mHandle handle,
                                    UInt32          chNum,
                                    void           *params);

/** \brief Typedef for core get descriptor info function pointer. */
typedef Int32 (*Vcore_M2mGetDescInfo)(Vcore_M2mHandle    handle,
                                      UInt32             chNum,
                                      Vcore_M2mDescInfo *descInfo);

/** \brief Typedef for core set frame start event function pointer. */
typedef Int32 (*Vcore_M2mSetFsEvent)(Vcore_M2mHandle         handle,
                                     UInt32                  chNum,
                                     VpsHal_VpdmaFSEvent     fsEvent,
                                     const Vcore_M2mDescMem *descMem);

/** \brief Typedef for core program descriptor function pointer. */
typedef Int32 (*Vcore_M2mProgramDesc)(Vcore_M2mHandle         handle,
                                      UInt32                  chNum,
                                      const Vcore_M2mDescMem *descMem);

/** \brief Typedef for core program register function pointer. */
typedef Int32 (*Vcore_M2mProgramReg)(Vcore_M2mHandle         handle,
                                     UInt32                  chNum,
                                     const Vcore_M2mDescMem *descMem);

/** \brief Typedef for core program FMD register function pointer. */
typedef Int32 (*Vcore_M2mProgramFmdReg)(Vcore_M2mHandle         handle,
                                        const Vps_DeiFmdConfig *fmdCfg,
                                        const Vcore_M2mDescMem *descMem);

/** \brief Typedef for core program FMD Update register function pointer. */
typedef Int32 (*Vcore_M2mProgramFmdUpdateReg)(Vcore_M2mHandle
                                              handle,
                                              const Vps_DeiFmdUpdateConfig *
                                              fmdCfg,
                                              const Vcore_M2mDescMem       *
                                              descMem);

/** \brief Typedef for core program user coefficient function pointer. */
typedef Int32 (*Vcore_M2mProgramUserCoeff)(const Vcore_M2mHandle handle,
                                           UInt32                chNum,
                                           const Vcore_M2mScUserCoeffParams *
                                           userCoeffPrms);

/** \brief Typedef for core get scaler coefficient function pointer. */
typedef Int32 (*Vcore_M2mGetScCoeff)(Vcore_M2mHandle            handle,
                                     UInt32                     chNum,
                                     Vcore_M2mScGetCoeffParams *getCoeffPrms);

/** \brief Typedef for core update descriptor function pointer. */
typedef Int32 (*Vcore_M2mUpdateDesc)(Vcore_M2mHandle         handle,
                                     const Vcore_M2mDescMem *descMem,
                                     const Fvid2_Frame      *frame,
                                     UInt32                  fid);
/** \brief Typedef for core update run time params to desc/overlay memory. */
typedef Int32 (*Vcore_M2mUpdateRtMem)(Vcore_M2mHandle         handle,
                                      const Vcore_M2mDescMem *descMem,
                                      UInt32                  chNum,
                                      const void             *rtParams,
                                      UInt32                  frmIdx);

/** \brief Typedef for core get DEI context info function pointer. */
typedef Int32 (*Vcore_M2mGetDeiCtxInfo)(Vcore_M2mHandle      handle,
                                        UInt32               chNum,
                                        Vcore_M2mDeiCtxInfo *ctxInfo);

/** \brief Typedef for core update internal context function pointer. */
typedef Int32 (*Vcore_M2mUpdateContext)(Vcore_M2mHandle         handle,
                                        UInt32                  chNum,
                                        const Vcore_M2mDescMem *descMem,
                                        const void             *ctx);

/**
 *  \brief Typedef for core updating DEI Mode for handling start up
 *  and reset condtions.
 */
typedef Int32 (*Vcore_M2mUpdateMode)(Vcore_M2mHandle         handle,
                                     UInt32                  chNum,
                                     const Vcore_M2mDescMem *cfgDescMem,
                                     UInt32                  frmCnt);

/**
 *  \brief Typedef for core function to get the scaling factor config for
 *  the specified channel number, and to program registers appropriately.
 */
typedef Int32 (*Vcore_M2mGetScFactorConfig)(Vcore_M2mHandle        handle,
                                            UInt32                 chNum,
                                            VpsHal_ScFactorConfig *scFactorCfg);

/**
 *  struct Vcore_M2mOps
 *  \brief Structure to store core function pointers.
 */
typedef struct
{
    Vcore_M2mGetProperty         getProperty;
    /**< Get property function pointer. */
    Vcore_M2mOpen                open;
    /**< Open function pointer. */
    Vcore_M2mClose               close;
    /**< Close function pointer. */
    Vcore_M2mSetFormat           setFormat;
    /**< Set format function pointer. */
    Vcore_M2mGetFormat           getFormat;
    /**< Get format function pointer. */
    Vcore_M2mGetDescInfo         getDescInfo;
    /**< Get descriptor info function pointer. */
    Vcore_M2mSetFsEvent          setFsEvent;
    /**< Set frame start event function pointer. */
    Vcore_M2mSetParams           setParams;
    /**< Set parameters function pointer. */
    Vcore_M2mGetParams           getParams;
    /**< Get parameters function pointer. */
    Vcore_M2mControl             control;
    /**< Core control function pointer. */
    Vcore_M2mProgramDesc         programDesc;
    /**< Core program descriptor function pointer. */
    Vcore_M2mProgramReg          programReg;
    /**< Core program register function pointer. */
    Vcore_M2mUpdateDesc          updateDesc;
    /**< Update descriptor function pointer. */
    Vcore_M2mGetDeiCtxInfo       getDeiCtxInfo;
    /**< Get DEI context info function pointer. */
    Vcore_M2mUpdateContext       updateContext;
    /**< Update context descriptor function pointer. */
    Vcore_M2mUpdateRtMem         updateRtMem;
    /**< Update the descriptor or overlay memory with runtime params */
    Vcore_M2mProgramUserCoeff    programUserCoeff;
    /**< Program user scaler coefficient funcion pointer. */
    Vcore_M2mGetScCoeff          getScCoeff;
    /**< Get scaler coefficient memory funcion pointer. */
    Vcore_M2mUpdateMode          updateMode;
    /**< Update DEI mode as per the frame number */
    Vcore_M2mGetScFactorConfig   getScFactorConfig;
    /**< Get the scaling factor config */
    Vcore_M2mProgramFmdReg       programFmdReg;
    /**< Core program FMD register function pointer. */
    Vcore_M2mProgramFmdUpdateReg programFmdUpdateReg;
    /**< Core program FMD Update register function pointer. */
} Vcore_M2mOps;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSCORE_M2M_H_ */
